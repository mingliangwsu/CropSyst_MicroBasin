#include "soilprocessesclass.h"
//______________________________________________________________________________
#ifdef MSVB_CASCADE_INFILTRATION_HOUR
//140423 This will eventually be permentanty replaced by Roger's implementation
//Do not do any further work in this function.
void SoilProcessesClass::DetermineHourlyWaterRedistribution
(int hour
 ,double WaterIn_m_hr
#ifndef CROPSYST_VERSION
,clsManagement &Management
#endif
)
{
    //COS-FMS New vertical infiltration routine 01/02/2014
    //Hour: 0-23
    //WaterIn_m_hr: Other sources of input M.Liu
    int layer,Time_Step,L,year,doy;
    double One_Hour_Water_Content_Change;
    double Flow_Out;    //(m/h)
    double WC_At_Water_Potential_After_Drainage;
    double Excess;
    double Over_Field_Capacity;
    double K_based_WC;
    double Flow_In;
    int Number_Of_Layers;

    double Sum_Flow_Out;
    double Water_Potential_After_Drainage;
    double One_Hour_Water_Content_Change_At_Saturation;
    double Excess_Flow_In;
    double Available_Porosity;
    double Water_Potential_Above_Wetting_Front_m; //in m  NEW 03/16/13
    double Water_Potential_Below_Wetting_Front_m; //in m  NEW 03/16/13
    double Infiltration_Rate;  //in m/h  NEW 03/16/13
    double Runoff;
    double Water_Depth_To_Infiltrate;  //(m) NEW 03/16/13
    double Minimum_Saturated_Hydraulic_Conductivity; //in m  NEW July 31, 2013
    //double Profile_Init; //Needed to calculate hourly water balance

    double Water_Available_To_Potentially_Infiltrate_m;
    double Available_Storage_To_Saturation;
    double First_Drainable_Layer = 1;   //default M.liu
    bool Redistribution = false;        //default M.Liu
    double Mean_Time_Step_Water_Content;
    double Water_Content_Change_For_Equilibrium_Water_Potential = 0.0;
    double Sum_Ponded = 0;      //(m) FMS 1/2/2014
    //double Profile_Final; //Needed to calculate hourly water balance
    //double Balance; //Hourly water balance in mm
    double Water_Depth_To_Infiltrate_for_Chemical_Trasport;
    double Sat_Cond_Limited_Flow_In;
    double Flow_In_Max;

    //const double Gr = 9.8; //Gravitational constant in m/s2
    //const double Water_Density = 1000; //kg/m3

    Time_Step = 3600; //seconds
    //DOY = Simulation.pTimeState->getToday().get_DOY();
    //Year = Simulation.pTimeState->getToday().get_year();

    Number_Of_Layers = Num_Soil_Layers;

    Minimum_Saturated_Hydraulic_Conductivity =  SoilStateRef.Minimum_Hydraulic_Conductivity; //FMS Feb 25,  2014

    Ponded_Initial[hour] = Hourly_Ponded_m * 1000.0; //FMS Jan 21, 2014

    //Hourly_Water_In = 0.01; //FOR DEBUG!!! M.Liu


    //For overall watershed balance calculations LML 14/04/17 moved outsides
    //Gross_Water_In_m = Hourly_Irrigation_m + Hourly_Non_Intercepted_Rain_m + Hourly_Snow_Melt_m;
    //Cumulative_Gross_Water_In += Gross_Water_In_m;


    Hourly_Drainage_m = 0;    //M.Liu check later!!
    #ifdef MBVB_INFILTRATION
    //140303 RLN obsolete
    Soil_Depth[0] = 0;  //NEW 03/16/13 RLN_OK

    for (layer = 1; layer <= Number_Of_Layers; layer++) {
        Water_Content[layer] = SoilStateRef.Water_Content[layer];
        SoilStateRef.Old_Water_Content[layer] = Water_Content[layer];
        Layer_Thickness[layer] = SoilProfileRef.Layer_Thickness_m[layer];
        Soil_Depth[layer] = Soil_Depth[layer - 1] + Layer_Thickness[layer]; //NEW 03/16/13 RLN_OK
        WC_Sat[layer] = SoilProfileRef.Saturation_Water_Content[layer] - SoilStateRef.Ice_Content[layer]; //FMS Mar 14, 2014 because limited max water content by ice
        K_Sat[layer] = SoilProfileRef.K_Sat[layer];
        m[layer] = SoilProfileRef.m_Value[layer];
        FC[layer] = SoilProfileRef.Field_Capacity[layer];
        b_Value[layer] = SoilProfileRef.b_Value[layer];
        Air_Entry_Potential[layer] = SoilProfileRef.Air_Entry_Potential[layer];
        #ifdef MSVB_CASCADE_INFILTRATION_HOUR
        Hours_To_Field_Capacity[layer] = SoilProfileRef.Hours_To_Field_Capacity[layer];
        #endif
        WPFC[layer] = SoilProfileRef.FC_WPot[layer];
        //New 03/17/13: The name of variable K_Sat previously used was changed to Apparent_K_Sat. Now K_Sat is coming from pedotransfer function RLN_OK
        //Determine apparent hydraulic conductivity that matches field capacity characteristics
        if (SoilStateRef.Ice_Content[layer] < 1.0e-6) Apparent_K_Sat[layer] = SoilProfileRef.Apparent_K_Sat[layer];
        else Apparent_K_Sat[layer] = SoilProfileRef.calcApparentKSat(Layer_Thickness[layer],WC_Sat[layer],m[layer],FC[layer],Hours_To_Field_Capacity[layer]);

        SoilStateRef.Water_Flow[layer] = 0; //m/h

        //std::cout<<"layer:"<<layer<<" WC:"<<Water_Content[layer]<<" air_entry:"<<Air_Entry_Potential[layer]<<std::endl;
    //END New 03/17/13
    }

    #ifdef CHECK_MASS_BALANCE
    double Profile_Init = SoilStateRef.getTotalWaterStorage_m();
    #endif

    //BEGIN NEW 03/16/13  RLN_OK
    //Determine darcian infiltration rate given current water front depth. Water potential of the weting front is the
    //average of water potentials (in m) immediately above and below the water front (1 J/kg = 0.102 m).
    //The saturated hydraulic conductivity is the minimum above the wetting front.

    //Hourly_Water_In = 20;//M.LIU DEBUG

    All_Hourly_Water_In += /*Hourly_Water_In*/WaterIn_m_hr;

    if (/*LML 14/04/17 Hourly_Water_In_m*/WaterIn_m_hr > 0) {
        if (/*(Hour == 0) && */First_Hour_Of_Watering) {  //FMS Feb 21, 2014
            //Set initial wetting front depth and minimum sat hydr cond
            Minimum_Saturated_Hydraulic_Conductivity = K_Sat[1] * m_h_P_KgS_m3/*LML 14/04/25 0.00981 * 3600*/; //Convert kg*s/m3 to m/h

            SoilStateRef.Minimum_Hydraulic_Conductivity = Minimum_Saturated_Hydraulic_Conductivity;

            Water_Potential_Above_Wetting_Front_m = Air_Entry_Potential[1] * 0.102; //Convert J/kg to m
            //OJO fidel add abs...it is bad
            Water_Potential_Below_Wetting_Front_m = Air_Entry_Potential[1] * pow((Water_Content[1] / WC_Sat[1]), (-b_Value[1])) * 0.102; //Convert J/kg to m
            Top_Water_Potential_m = Water_Potential_Above_Wetting_Front_m;
            Average_Water_Potential_Wetting_Front_m = (Water_Potential_Above_Wetting_Front_m + Water_Potential_Below_Wetting_Front_m) / 2.;
            //in m, actually m/h
            First_Hour_Of_Watering = false;
        }
        if (Wetting_Front_Depth < 0.001) Wetting_Front_Depth = 0.001; //set minimum water front depth = 1 mm
        Infiltration_Rate = Minimum_Saturated_Hydraulic_Conductivity * (Top_Water_Potential_m - (Average_Water_Potential_Wetting_Front_m - Wetting_Front_Depth)) / Wetting_Front_Depth;
        if (Infiltration_Rate < 0) Infiltration_Rate = 0; //FMS Jan 14, 2014
    } else {
        Infiltration_Rate = 0; //in m, actually m/h
        First_Hour_Of_Watering = true; //Reset the boolean variable to be ready for the next watering event
    }

    SoilStateRef.Current_Infiltration_Rate = Infiltration_Rate;

    Water_Depth_To_Infiltrate = std::min<double>(Infiltration_Rate, /*LML 14/04/17 Hourly_Water_In_m*/WaterIn_m_hr);   //in m, actually m/h

    SoilStateRef.Water_Flow[0] = Water_Depth_To_Infiltrate; //M.Liu added Feb. 28, 2014


    /*std::cout<<"Hour:"<<hour<<" Hourly_Water_In:"<<WaterIn_m_hr
                <<" Water_Depth_To_Infiltrate:"<<Water_Depth_To_Infiltrate
                <<" Infiltration_Rate:"<<Infiltration_Rate
                <<" First_Hour_Of_Watering:"<<First_Hour_Of_Watering
                <<std::endl;*/

    //Determine if there is any runoff
    if (Water_Depth_To_Infiltrate < /* LML 14/04/17 Hourly_Water_In_m*/WaterIn_m_hr) {
        Sum_Ponded = /* LML 14/04/17 Hourly_Water_In_m*/WaterIn_m_hr - Water_Depth_To_Infiltrate;   //m
    }

    Water_Depth_To_Infiltrate_for_Chemical_Trasport = Water_Depth_To_Infiltrate; //FMS Mar 6, 2014

    if (Water_Depth_To_Infiltrate > 0) {

        //Cascade water available to infiltrate first, leaving layers at saturation. Redistribution is applied later below.
        for (layer = 1; layer <= Number_Of_Layers; layer++) {
            Sat_Cond_Limited_Flow_In = Apparent_K_Sat[layer] * m_h_P_KgS_m3/*LML 14/04/25 0.00981 * 3600*/;  //m/h
            if (Water_Depth_To_Infiltrate > Sat_Cond_Limited_Flow_In) {
                Excess_Flow_In = Water_Depth_To_Infiltrate - Sat_Cond_Limited_Flow_In;
                Water_Depth_To_Infiltrate = Sat_Cond_Limited_Flow_In;
                DistributeExcessFlowUpwards(layer, Excess_Flow_In, Sum_Ponded); //FMS Jan 10, 2014
            }
            else Excess_Flow_In = 0;

            Available_Storage_To_Saturation = (WC_Sat[layer] - Water_Content[layer]) * Layer_Thickness[layer];
            if (Water_Depth_To_Infiltrate > Available_Storage_To_Saturation) {
                Water_Content[layer] = WC_Sat[layer];
                Water_Depth_To_Infiltrate -= Available_Storage_To_Saturation;
                SoilStateRef.Water_Flow[layer] = Water_Depth_To_Infiltrate; //m/h
                Wetting_Front_Depth = Soil_Depth[layer];
                Water_Potential_Above_Wetting_Front_m = Air_Entry_Potential[layer] * 0.102; //Convert J/kg to m

                if (layer == Number_Of_Layers) Water_Potential_Below_Wetting_Front_m = Water_Potential_Above_Wetting_Front_m;
                else Water_Potential_Below_Wetting_Front_m = Air_Entry_Potential[layer + 1] * pow((Water_Content[layer + 1] / WC_Sat[layer + 1]),(-b_Value[layer + 1])) * 0.102; //Convert J/kg to m

                Average_Water_Potential_Wetting_Front_m = (Water_Potential_Above_Wetting_Front_m + Water_Potential_Below_Wetting_Front_m) / 2.;
                Minimum_Saturated_Hydraulic_Conductivity = std::min<double>(Minimum_Saturated_Hydraulic_Conductivity, K_Sat[layer] * m_h_P_KgS_m3/*LML 14/04/25* 0.00981 * 3600*/); //Ksat converted from kg*s/m3 to m/h
            } else {
                Water_Content[layer] += Water_Depth_To_Infiltrate / Layer_Thickness[layer];
                Wetting_Front_Depth = Soil_Depth[layer - 1] + Layer_Thickness[layer] * Water_Depth_To_Infiltrate / Available_Storage_To_Saturation;
                Water_Potential_Above_Wetting_Front_m = Air_Entry_Potential[layer] * 0.102; //Convert J/kg to m
                Water_Potential_Below_Wetting_Front_m = Air_Entry_Potential[layer] * pow((Water_Content[layer] / WC_Sat[layer]),(-b_Value[layer])) * 0.102; //Convert J/kg to m
                Average_Water_Potential_Wetting_Front_m = (Water_Potential_Above_Wetting_Front_m + Water_Potential_Below_Wetting_Front_m) / 2;
                Minimum_Saturated_Hydraulic_Conductivity = std::min<double>(Minimum_Saturated_Hydraulic_Conductivity, K_Sat[layer] * m_h_P_KgS_m3/*LML 14/04/25* 0.00981 * 3600*/); //Ksat converted from kg*s/m3 to m/h
                Water_Depth_To_Infiltrate = 0;
                SoilStateRef.Water_Flow[layer] = Water_Depth_To_Infiltrate; //m/h
                layer = Number_Of_Layers;
            }
        }//Next Layer
        SoilStateRef.Minimum_Hydraulic_Conductivity = Minimum_Saturated_Hydraulic_Conductivity;

        //If there is water remaining, add it to drainage
        if (Water_Depth_To_Infiltrate > 0) {
                Hourly_Drainage_m += Water_Depth_To_Infiltrate;
                Water_Depth_To_Infiltrate = 0;
        }
    }
    else Wetting_Front_Depth = 0;

    if (/*LML 14/04/17 Hourly_Water_In_m*/WaterIn_m_hr > 0) {
        First_Drainable_Layer = 1;
        Redistribution = true;
    } else {
        for (layer = 1; layer <= Number_Of_Layers; layer++) {
            if (Water_Content[layer] > (FC[layer] + 1e-12)) {
                First_Drainable_Layer = layer;
                Redistribution = true;
                layer = Number_Of_Layers;
                /*std::cout<<"L:"<<Layer
                        <<" VWC:"<<Water_Content[layer]
                          <<" FC:"<<FC[layer]
                            <<std::endl;*/
            }
        }
    }

    Flow_In = 0;    //M.Liu moved outside Feb.18
    Flow_Out = 0;
    Sum_Flow_Out = 0;

    if (Redistribution) {
        for (layer = First_Drainable_Layer; layer <= Number_Of_Layers; layer++) {
            One_Hour_Water_Content_Change_At_Saturation = calDeltaVWC(WC_Sat[layer],layer,Time_Step);

            Excess_Flow_In = 0;
            Flow_In_Max = ((WC_Sat[layer] - Water_Content[layer]) + One_Hour_Water_Content_Change_At_Saturation) * Layer_Thickness[layer];
            Sat_Cond_Limited_Flow_In = K_Sat[layer] * m_h_P_KgS_m3/*0.00981 * 3600*/; //Convert kg*s/m3 to m/h //FMS-COS Jan 16, 2014
            Flow_In_Max = std::min<double>(Flow_In_Max,Sat_Cond_Limited_Flow_In);

            if (Flow_In > Flow_In_Max) {
                Excess_Flow_In = Flow_In - Flow_In_Max;
                Flow_In = Flow_In_Max;
                DistributeExcessFlowUpwards(layer, Excess_Flow_In, Sum_Ponded);
            }

            WC_Temp[layer] = std::min<double>(Water_Content[layer] + Flow_In / Layer_Thickness[layer], WC_Sat[layer]);
            Mean_Time_Step_Water_Content = (Water_Content[layer] + WC_Temp[layer]) / 2.0;

            if (Mean_Time_Step_Water_Content > FC[layer]) {
                One_Hour_Water_Content_Change = calDeltaVWC(Mean_Time_Step_Water_Content,layer,Time_Step);
                if (One_Hour_Water_Content_Change > (Mean_Time_Step_Water_Content - FC[layer])) One_Hour_Water_Content_Change = Mean_Time_Step_Water_Content - FC[layer];
            }
            else One_Hour_Water_Content_Change = 0;

            if (One_Hour_Water_Content_Change < 0) One_Hour_Water_Content_Change = 0;

            if (layer > First_Drainable_Layer) {
                WC_At_Water_Potential_After_Drainage = WC_Sat[layer] * pow((Water_Potential_After_Drainage / Air_Entry_Potential[layer]),(-1 / b_Value[layer]));
                if (WC_At_Water_Potential_After_Drainage > WC_Sat[layer]) WC_At_Water_Potential_After_Drainage = WC_Sat[layer];
                else if (WC_At_Water_Potential_After_Drainage < FC[layer]) WC_At_Water_Potential_After_Drainage = FC[layer];

                Water_Content_Change_For_Equilibrium_Water_Potential = Water_Content[layer] + Flow_In / Layer_Thickness[layer] - WC_At_Water_Potential_After_Drainage;

                if (Water_Content_Change_For_Equilibrium_Water_Potential < 0) Water_Content_Change_For_Equilibrium_Water_Potential = 0;

                if (Water_Content_Change_For_Equilibrium_Water_Potential > One_Hour_Water_Content_Change) {
                    Water_Content[layer] = WC_At_Water_Potential_After_Drainage;
                    Flow_Out = Water_Content_Change_For_Equilibrium_Water_Potential * Layer_Thickness[layer];
                } else {
                    Water_Content[layer] += Flow_In / Layer_Thickness[layer] - One_Hour_Water_Content_Change;
                    Flow_Out = One_Hour_Water_Content_Change * Layer_Thickness[layer];
                }

                if (Flow_Out > 0.01) {
                    Flow_Out = Flow_Out;
                }
            } else {
                Water_Content[layer] += Flow_In / Layer_Thickness[layer] - One_Hour_Water_Content_Change;
                Flow_Out = One_Hour_Water_Content_Change * Layer_Thickness[layer];
                Water_Potential_After_Drainage = Air_Entry_Potential[layer] * pow((Water_Content[layer] / WC_Sat[layer]),(-b_Value[layer]));
                Water_Potential_After_Drainage = std::max<double>(Water_Potential_After_Drainage, WPFC[layer]);
                //Water_Potential_After_Drainage = Minimum(Water_Potential_After_Drainage, Air_Entry_Potential[layer])
                Water_Potential_After_Drainage = std::min<double>(Water_Potential_After_Drainage, 0.0); //FMS-COS Jan16, 2014
            }

            SoilStateRef.Water_Flow[layer] += Flow_Out; //flow is in m/h

            /*std::cout<<" L:"<<layer
                     <<" F_D_Layer:"<<First_Drainable_Layer
                     <<" 1_Hour_WC_Ch:"<<One_Hour_Water_Content_Change
                     <<" WC_sat:"<<WC_Sat[layer]
                     <<" WC:"<<Water_Content[layer]
                     <<" WC_At_WP_Aft_D(mm):"<<WC_At_Water_Potential_After_Drainage
                     <<" WP_Aft_D:"<<Water_Potential_After_Drainage
                     <<" WC_Ch_EqWaP:"<<Water_Content_Change_For_Equilibrium_Water_Potential
                     <<" flowin(mm):"<<Flow_In*1000
                     <<" flowout(mm):"<<Flow_Out*1000
                     <<" sumpond(mm):"<<Sum_Ponded*1000
                     <<std::endl;*/

            Flow_In = Flow_Out;
            Sum_Flow_Out += Flow_Out;
            SoilStateRef.New_Water_Content[layer] = Water_Content[layer];


        }//next layer
    }//end redistribution

    for (layer = 1; layer <= Number_Of_Layers; layer++) {
        //SoilStateRef.Water_Content[layer] = SoilStateRef.Hourly_Water_Content[layer];
        //SoilStateRef.Hourly_Water_Content[layer] = Water_Content[layer];

        SoilStateRef.Water_Content[layer] = Water_Content[layer];//SoilStateRef.Hourly_Water_Content[layer];
        SoilStateRef.Hourly_Water_Content[layer] = Water_Content[layer];
    }
    SoilStateRef.Hourly_Ponded_Water_m = Sum_Ponded;        //LML 14/04/24
    SoilStateRef.Water_Flow[0] = Water_Depth_To_Infiltrate_for_Chemical_Trasport - Sum_Ponded;  //m/h FMS Jan 28, 2014


    Hourly_Drainage_m += Flow_Out;      //(m) FMS Mar 10, 2014
    Hourly_Ponded_m = Sum_Ponded;       //(m) FMS Mar 10, 2014
    Hourly_Runoff_m = 0.0;              //(m) FMS Mar 10, 2014
    //SoilStateRef.Hourly_Ponded_Water_m = Sum_Ponded; //(m) Update ponded water
    Hourly_Water_In_m = Water_Depth_To_Infiltrate_for_Chemical_Trasport;    //(m) LML 14/04/17 should be infiltrated water
    Ponded_Final[hour] = Hourly_Ponded_m * 1000;

    //SoilStateRef.Hourly_Drainage_m = Hourly_Drainage_m; // (mm) FMS 10/23/2013
    //SoilStateRef.Cumulative_Drainage += Hourly_Drainage_m * 1000.0;

    //M.Liu put hourly runoff at here Feb.4, 2014 May cause some confusions
    //SoilStateRef.Hourly_Runoff_m = std::max<double>(SoilStateRef.Hourly_Ponded_Water_m - SoilProfileRef.SurfaceStorage/1000.0,0.0);
                                                                     //Convert Flow out from m/hour to mm/hour

    //if (hour == 0) SoilStateRef.Daily_Drainage_m = Hourly_Drainage_m;
    //else SoilStateRef.Daily_Drainage_m += Hourly_Drainage_m;

    #ifdef CHECK_MASS_BALANCE
    double Profile_Final = SoilStateRef.getTotalWaterStorage_m();
    #endif


    #else
    float64 runoff = 0;  // meter

    if (infiltration_cascade_hourly)                                             //140225
      infiltration_cascade_hourly->process_hourly_infiltration      // Sub Infiltrate
      (hour  /* CropSyst uses standard 24 hours count from 0 */
      ,Hourly_Water_In /* pass by value only local copy updated */ //    (ByVal Hourly_Irrigation As Single
      ,runoff);
    #endif

    #ifdef CHECK_MASS_BALANCE
    double Balance = Profile_Init + /*LML 14/04/17 Hourly_Water_In_m*/WaterIn_m_hr - Hourly_Drainage_m - Profile_Final; //FMS Jan 16, 2014
    double flux_in = WaterIn_m_hr;
    if (!IsMassBalance(flux_in,Hourly_Drainage_m,Profile_Init,Profile_Final,1.0e-5)) {
        std::cout
                <<"SoilProcessesClass::DetermineHourlyWaterRedistribution Massbalance problem!\n"
                <<"Profile_Init (mm):"<<Profile_Init * 1000.0
                <<" Hourly_Water_In(mm):"<<WaterIn_m_hr * 1000.0
                <<" Sum_Ponded (mm):"<<Sum_Ponded * 1000
                <<" Hourly_Drainage (mm):"<<Hourly_Drainage_m * 1000.0
                <<" Profile_Final (mm):"<<Profile_Final * 1000.0
                <<"Balance (mm):"<<fabs(Balance * 1000.0)
                <<std::endl;
        nrerror("Water NOT balance!");
    }
    #endif  //CHECK_MASS_BALANCE



    #ifdef CHEMICAL_TRANSPORT
    Hourly_Prec_Irrig_SnowMelt_m = Hourly_Non_Intercepted_Rain_m
        #ifndef CROPSYST_VERSION
         + Hourly_Irrigation_m
        #endif
         + Hourly_Snow_Melt_m; // FMS 10/01/2013
    #endif
    SoilStateRef.Hourly_Prec_Irrig_SnowMelt_m = Hourly_Prec_Irrig_SnowMelt_m;
    #ifdef CHECK_MASS_BALANCE
    SoilStateRef.Vertical_flow_balance_allLayers = Balance / 1000; //SoilStateRef.Vertical_flow_balance_allLayers + Balance / 1000 //Hourly_Water_Balance
    #endif
}
#endif
