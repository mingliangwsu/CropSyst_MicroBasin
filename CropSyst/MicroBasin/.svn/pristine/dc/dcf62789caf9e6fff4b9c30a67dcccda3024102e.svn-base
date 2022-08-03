#include "soilprocessesclass.h"
#include "common/physics/standard_constants.h"
#include "util/pubtools.h"
//#include "util/cout_mp.h"
#ifdef MBVB_FD
void SoilProcessesClass::Adjust_FD_Drainage_Error(double Drainage_Error_mm,double Drainage,double Flux)
{
    //Drainage mm/s, drainage error mm/h
    int layer;
    int Nu_of_L;
    double Avail_2B_filled_mm;
    double Maximum_Drainage;
    double Water_2B_moved;

    double Profile_Water_Change;

    Nu_of_L = Num_Soil_Layers;

    Minimum_K_sat[Nu_of_L + 1] = 1000;  //just an arbitrary starting value

    for (layer = Nu_of_L; layer >= 1; layer--) {
        SAT[layer] = SoilProfileRef.Saturation_Water_Content[layer];
        HalfLayer_Thickness[layer] = SoilProfileRef.Layer_Thickness_m[layer] / 2;
        K_Sat[layer] = SoilProfileRef.K_Sat[layer];
        //Minimum K_sat is the lowest K of the considered layer downwards, i.e. the layer constraining saturated flow
        Minimum_K_sat[layer] = std::min<double>(Minimum_K_sat[layer+1], K_Sat[layer]);
    }

    Minimum_K_sat[Nu_of_L + 1] = Minimum_K_sat[Nu_of_L];  //set back the arbitrary starting value


    //drainage error in mm/h
    if (Drainage_Error_mm > 0) {

        //define first, initial value of maximum drainage (mm/s)
        Maximum_Drainage = K_Sat[Nu_of_L] * 9.8;

        for (layer = Nu_of_L; layer >= 1; layer--) {

            // 1.) start with new lower water content of considered layer
            Avail_2B_filled_mm = (SAT[layer] - wnl[layer]) * HalfLayer_Thickness[layer] * 1000;

            //update maximum drainage (mm/s): use either maximum drainage value of previous L or Ks of L, whatever is lower
            Maximum_Drainage = std::min<double>(Maximum_Drainage, K_Sat[layer] * 9.8);

            if (Drainage_Error_mm > Avail_2B_filled_mm) {
                wnl[layer] = SAT[layer];
                Drainage_Error_mm -= Avail_2B_filled_mm;
            } else {
                wnl[layer] += Drainage_Error_mm / (HalfLayer_Thickness[layer] * 1000.0);
                Drainage_Error_mm = 0; //split drainage error  among layers done!
                //Soil.BackWater = 0
            }

            SoilStateRef.New_Lower_Water_Content[layer] = wnl[layer];
            SoilStateRef.Lower_Water_Content[layer] = wnl[layer];

            // 2.) continue with new upper water content of same layer
            Avail_2B_filled_mm = (SAT[layer] - wnu[layer]) * HalfLayer_Thickness[layer] * 1000.0;

            if (Drainage_Error_mm > Avail_2B_filled_mm) {
                wnu[layer] = SAT[layer];
                Drainage_Error_mm -= Avail_2B_filled_mm;
            } else {
                wnu[layer] += Drainage_Error_mm / (HalfLayer_Thickness[layer] * 1000.0);
                Drainage_Error_mm = 0; //split drainage error  among layers done!
                //Soil.BackWater = 0
            }

            SoilStateRef.New_Upper_Water_Content[layer] = wnu[layer];
            SoilStateRef.Upper_Water_Content[layer] = wnu[layer];


            //flux (mm/s) of layer L is equal to the change in water content, old minus new
            Jl[layer] = -((wl[layer] + wu[layer]) / 2.0 - (wnl[layer] + wnu[layer]) / 2.0)
                         * (2.0 * HalfLayer_Thickness[layer] * 1000.0)
                         / 3600.0
                         - Minimum_K_sat[layer+1] * 9.8;
            if (CORN::is_approximately<double>(Drainage_Error_mm,0,1.0e-8)) layer = 0; //no need to further loop thru layers
        }//Next L

        //The following kicks-in when the soil is completely saturated
        if (Drainage_Error_mm > 0) {
            //calculate change in water content of whole soil profile (mm)
            for (layer = 1; layer <= Nu_of_L; layer++) {
                Profile_Water_Change += ((wl[layer] + wu[layer]) / 2.0 - (wnl[layer] + wnu[layer]) / 2.0) * (2.0 * HalfLayer_Thickness[layer] * 1000.0);
            }
            Jl[0] = Profile_Water_Change / 3600.0 + Jl[Nu_of_L];
            Flux = -Jl[0];
            Drainage_Error_mm = 0;
        }
    }
    else{ //Drainage Error is negative which means an (erroneous) upward flow of water
        for(layer = Nu_of_L; layer >= 1; layer--){
            //!!!maximum drainage here in mm/h
            Maximum_Drainage = K_Sat[layer] * 9.8 * 3600.0;
            //water to be moved in mm/h
            Water_2B_moved = std::min<double>(Maximum_Drainage, -Drainage_Error_mm);

            wnl[layer] -= (Water_2B_moved / (HalfLayer_Thickness[layer] * 1000.0));
            SoilStateRef.New_Lower_Water_Content[layer] = wnl[layer];
            SoilStateRef.Lower_Water_Content[layer] = wnl[layer];

            Drainage_Error_mm += Water_2B_moved;

            //flux (mm/s) of layer L is equal to the change in water content, old minus new
            Jl[layer] = Jl[layer] + Water_2B_moved / 3600.0;

            //repeat above procedure for  new upper water content (wnu)of same layer
            Water_2B_moved = std::min<double>(Maximum_Drainage, -Drainage_Error_mm);
            wnu[layer] -= (Water_2B_moved / (HalfLayer_Thickness[layer] * 1000.0));
            SoilStateRef.New_Upper_Water_Content[layer] = wnu[layer];
            SoilStateRef.Upper_Water_Content[layer] = wnu[layer];

            Drainage_Error_mm += Water_2B_moved;

            //flux (mm/s) of layer L is equal to the change in water content, old minus new
            Jl[layer] = Jl[layer] + Water_2B_moved / 3600.0;

            if (CORN::is_approximately<double>(Drainage_Error_mm,0,1.0e-8)) layer = 0;
        }
    }
    SoilStateRef.setSoilWaterByNewUpperAndLower(Nu_of_L);
}
#endif
//_____________________________________________________________________________/
#ifdef LIU_FD_RICHARD
void SoilProcessesClass::performFDRichard(clsSimulation &Simulation,clsManagement &Management)
{
    int HourOfDay = Simulation.pTimeState->getHourOfDay();  //0-23

    //int N_Soil = Num_Soil_Layers;
    //int L_Soil; //soil layer index
    int N_Nodes = fd_nodes;
    int ntime = 3600/fd_delt;

    int ntime_recharge;
    int ntime_drainage;
    double total_infiltrated = 0.0;     //(m) include imidiate fill to top node
    double total_infiltrated_from_mass_balance;
    double total_drainage = 0.0;        //(m)
    double infiltrated = 0.0;           //(m) Infiltration after filling the top nodes
    double extra_infiltrated = 0.0;
    double initial_soil_water_m;
    double finale_soil_water_m;
    double left_water_to_infiltration;  //(m)
    double water_to_fill;               //(m)

    double infiltrated_per_loop;
    double infiltrated_per_loop_from_massbalance;

    double initial_soil_water_per_loop_m;
    double final_soil_water_per_loop_m;
    double intent_infiltration;
    double total_soil_moisture_change;
    double extra_ponded;

    double Darcy_Calculated_Drainage = 0.0;         //Positive: drainage Negtive: recharge
    double calculated_infiltration_from_mass_balance;

    int i,it,j;

    Hourly_Non_Intercepted_Rain_m = SnowRef.Hourly_Rain_mm[HourOfDay+1] / 1000.0; // FMS 10/16/2013
    Hourly_Irrigation_m = Management.pManagementState->Irrigation_Amount / 24.0 / 1000.0;
    Hourly_Snow_Melt_m = SnowRef.Hourly_Snow_Melt_Amount[HourOfDay+1] / 1000.0;
    Hourly_Ponded_m = pond.get_depth();//SoilStateRef.Hourly_Ponded_Water_m;
    Hourly_Runoff_m = SoilStateRef.Hourly_Runoff_m;
    //double Storage = SoilProfileRef.SurfaceStorage;//SoilStateRef.Surface_Storage; M.Liu Mar 20 2014

    Hourly_Water_In_m = Hourly_Non_Intercepted_Rain_m + Hourly_Irrigation_m + Hourly_Snow_Melt_m +
                             Hourly_Ponded_m;// + Hourly_Runoff;   //M.Liu Mar 20, 2014 assume all runoff stay as pond but may flowout at next overlandflow loop

    //Initial conditions
    //if (bFirst_FD) {
        WaterFromSoilLayerToNodes();
        bFirst_FD = false;
    //}

    initial_soil_water_m = getTotalSoilWaterFromNodes();
    double water_to_fill_bottom_node = std::max<double>((fd_WS[1] - fd_theta[1]) * fd_delx / 2.0,0.0);
    double water_to_fill_top_node = std::max<double>((fd_WS[N_Nodes] - fd_theta[N_Nodes]) * fd_delx / 2.0,0.0);  //(m)

    //Testing mass balance for transfering between nodes and soil layer
    /*
    WaterFromNodesToSoilLayer();
    double dd = SoilStateRef.getTotalSoilWaterContent_mm()/1000.0;
    WaterFromSoilLayerToNodes();
    dd = getTotalSoilWaterFromNodes();
    */

    //std::cout<<"Hour:"<<HourOfDay<<" Hourly_Water_In_m:"<<Hourly_Water_In_m<<" Hourly_Ponded_m:"<<Hourly_Ponded_m<<std::endl;

    //start wetting (recharge conditions)

    it = 0;     //Initialize loop number
    left_water_to_infiltration = 0.0;
    ntime_recharge = 0;

    if (Hourly_Water_In_m > 0.0) {

        left_water_to_infiltration = Hourly_Water_In_m;   //M.Liu Mar 21, 2014

        for (it = 1; it <= ntime; it++)
        {
            if (left_water_to_infiltration > 1.0e-12) {
                //Real infiltration process
                for (i = 1;i <= N_Nodes; i++) {
                    if (it == 1) {     //Assume other processes have changed the soil moistures of each nodes
                        fd_u[i] = SoilStateRef.calc_h_Theta(fd_theta[i],fd_pe[i],fd_WS[i],fd_b_value[i]);//(m)
                    }
                    fd_pu[i] = fd_u[i];
                }
                for (j = 1;j <= 5; j++) { //M.Liu 5 Picard iterations
                    if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_NOFLOW) {
                        fd_pu[0] = fd_pu[1] + fd_delx;    //No flow at the bottom node
                        fd_u[0] = fd_u[1] + fd_delx;
                    }
                    else if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_FREEDRAIN) {
                        fd_pu[0] = fd_pu[1];
                        fd_u[0] = fd_u[1];
                    }

                    //cal K & CC
                    for (i = /*1*/0;i <= N_Nodes + 1; i++) {
                        fd_theta[i] = calcWaterContentFDRichard(i,fd_u[i],fd_CC[i]);
                        fd_K[i] = calcConductFDRichard(i,fd_theta[i]);//(m/s)
                    }
                    for (i = /*2*/1;i <= N_Nodes/*-1*/; i++) {
                        fd_f1 = 1.0/fd_delt * fd_CC[i];
                        fd_f2 = 1.0/(2.0*fd_delx*fd_delx) * (fd_K[i] + fd_K[i+1]);
                        fd_f3 = -1.0 / (2.0*fd_delx*fd_delx) * (fd_K[i] + fd_K[i-1]);
                        fd_f4 = 1.0 / (2.0*fd_delx) * (fd_K[i+1] - fd_K[i-1]);

                        if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_NOFLOW && i == 1) {    //Non-flow bottom BC
                            fd_a[1] = 0.0;
                            fd_b[1] = -fd_f2 - fd_f1;
                            fd_c[1] = fd_f2;
                            fd_d[1] = -fd_f1 * fd_pu[1] - fd_f4 + fd_f3 * fd_delx;
                        }
                        else if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_FREEDRAIN && i == 1) {    //Free drainage bottom BC
                            fd_a[1] = 0.0;
                            fd_b[1] = -fd_f2 - fd_f1;
                            fd_c[1] = fd_f2;
                            fd_d[1] = -fd_f1 * fd_pu[1] - fd_f4;
                        } else {
                            fd_a[i] = -fd_f3;
                            fd_b[i] = -fd_f2 + fd_f3 - fd_f1;
                            fd_c[i] = fd_f2;
                            fd_d[i] = -fd_f1 * fd_pu[i] - fd_f4;
                        }
                    }

                    //Water table bottom BC
                    if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_WATERTABLE) {
                        fd_a[1] = 0.0;
                        fd_b[1] = 1.0;
                        fd_c[1] = 0.0;
                        fd_d[1] = fd_pe[1];
                    }
                    //Top node BC
                    fd_a[N_Nodes] = 0.0;
                    fd_b[N_Nodes] = 1.0;
                    fd_c[N_Nodes] = 0.0;
                    fd_d[N_Nodes] = fd_pe[N_Nodes];


                    //if (HourOfDay == 0) std::cout<<" out wet fd_K[1]:"<<fd_K[1]<<" theta:"<<fd_theta[1]<<std::endl;
                    //Calculate drainage
                    if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_FREEDRAIN && j == 5) {
                        Darcy_Calculated_Drainage += fd_K[1] * fd_delt;
                        //if (HourOfDay == 0) std::cout<<" fd_K[1]:"<<fd_K[1]<<" theta:"<<fd_theta[1]<<std::endl;
                    }
                    else if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_WATERTABLE && j == 5) {
                        Darcy_Calculated_Drainage += (fd_K[1] + fd_K[2]) / 2.0
                                                    * ((fd_u[2] - fd_u[1]) / fd_delx + 1.0)
                                                    * fd_delt;
                    }

                    //Calculate infiltration
                    if (j == 5) {
                        intent_infiltration = (fd_K[N_Nodes] + fd_K[N_Nodes-1]) / 2.0
                                * ((fd_u[N_Nodes] - fd_u[N_Nodes-1]) / fd_delx + 1.0)
                                * fd_delt;
                    }


                    Tridiagonal(N_Nodes,fd_a,fd_b,fd_c,fd_d,fd_v,fd_tempa,fd_tempb);
                    //Transferring new values
                    for (i = 1;i <= N_Nodes; i++) {
                        fd_u[i] = fd_v[i];
                    }
                }//End picard iteration

                //std::cout<<" it:"<<it<<" ";
                for (i = 1;i <= N_Nodes; i++) {
                    fd_theta[i] = calcWaterContentFDRichard(i,fd_u[i],fd_CC[i]);
                    //std::cout<<" "/*vwc["<<i<<"] "*/<<fd_theta[i];
                }
                //std::cout<<std::endl;
#ifdef OLDFD

                final_soil_water_per_loop_m = getTotalSoilWaterFromNodes();

                /*infiltrated_per_loop = (fd_K[N_Nodes+1] + fd_K[N_Nodes]) / 2.0
                        * ((fd_pe[N_Nodes+1] - fd_u[N_Nodes]) / fd_delx + 1.0) * fd_delt;*/

                infiltrated_per_loop_from_massbalance = final_soil_water_per_loop_m - initial_soil_water_per_loop_m;

                //infiltrated += infiltrated_per_loop;

                /*std::cout<<"infiltrated_per_loop:"<<infiltrated_per_loop
                        <<" infiltrated_from_massbalance:"<<infiltrated_per_loop_from_massbalance
                        <<" difference:"<<fabs(infiltrated_per_loop_from_massbalance-infiltrated_per_loop)
                        <<" left_water_to_infiltration:"<<left_water_to_infiltration
                        <<std::endl;*/

                //std::cout<<" it:"<<it<<" "<<" Infiltrated:"<<infiltrated_per_loop_from_massbalance<<std::endl;

                if (/*infiltrated_per_loop*/infiltrated_per_loop_from_massbalance >= left_water_to_infiltration) {
                    ntime_recharge = it - 1;
                    //Restore last time moisture
                    for (i = 1;i <= N_Nodes; i++) {
                        fd_u[i] = fd_pu[i];
                        fd_theta[i] = calcWaterContentFDRichard(i,fd_u[i],fd_CC[i]);
                    }
                    it = ntime + 1;
                } else {
                    //Test output for debuging M.Liu March 22, 2014
                    /*std::cout<<" it:"<<it<<" ";
                    for (i = 1;i <= N_Nodes; i++) {
                        fd_theta[i] = calcWaterContentFDRichard(i,fd_u[i],fd_CC[i]);
                        std::cout<<" "<<fd_theta[i];
                    }
                    std::cout<<std::endl;*/

                    left_water_to_infiltration -= /*infiltrated_per_loop*/infiltrated_per_loop_from_massbalance;
                    total_infiltrated += infiltrated_per_loop_from_massbalance;
                }
#else
                if (intent_infiltration >= left_water_to_infiltration) {
                    ntime_recharge = it - 1;
                    //Restore last time moisture
                    for (i = 1;i <= N_Nodes; i++) {
                        fd_u[i] = fd_pu[i];
                        fd_theta[i] = calcWaterContentFDRichard(i,fd_u[i],fd_CC[i]);
                    }
                    it = ntime + 1;
                } else {
                    ntime_recharge = it;
                    left_water_to_infiltration -= intent_infiltration;
                    total_infiltrated += intent_infiltration;
                }
#endif
            }   //End if
        }//End wet loop
    }//End if hourly_water_in


    //Process extrainfiltration and minor  water
    //if (extra_infiltrated > 0.0) {
        //RemoveExtraWaterFromNodes(extra_infiltrated);
    //}

    if ((ntime_recharge < ntime) && left_water_to_infiltration > 1.0e-12) {
        //Water not enough to infiltrate for a wet loop
        extra_ponded = AddExtraWaterToNodes(left_water_to_infiltration);    //All water enter soil
        total_infiltrated += left_water_to_infiltration;                    //Check only
    }

    ntime_drainage = ntime - ntime_recharge;

    //infiltrated -= extra_infiltrated;
    //total_infiltrated += infiltrated;

    //std::cout<<" ntime_recharge:"<<ntime_recharge<<" ntime_drainage:"<<ntime_drainage<<std::endl;

    //For drinage period
    for (it = ntime_recharge+1; it <= ntime; it++) {
        for (i = 1;i <= N_Nodes; i++) {
            if (it == ntime_recharge+1) {
                fd_u[i] = SoilStateRef.calc_h_Theta(fd_theta[i],fd_pe[i],fd_WS[i],fd_b_value[i]);//(m)
            }
            fd_pu[i] = fd_u[i];
        }
        for (j = 1;j <= 5; j++) { //M.Liu 5 Picard iterations
            fd_pu[N_Nodes+1] = fd_pu[N_Nodes] - fd_delx;    //No flow at the nth node (surface node)
            fd_u[N_Nodes+1] = fd_u[N_Nodes] - fd_delx;
            //fd_u[N_Nodes+1] = fd_pu[N_Nodes] - fd_delx;

            if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_NOFLOW) {
                fd_pu[0] = fd_pu[1] + fd_delx;    //No flow at the 1th node (bottom node)
                fd_u[0] = fd_u[1] + fd_delx;
            } else if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_FREEDRAIN) {
                fd_pu[0] = fd_pu[1];
                fd_u[0] = fd_u[1];
            }


            for (i = /*1*/0;i <= N_Nodes+1; i++) {
                fd_theta[i] = calcWaterContentFDRichard(i,fd_u[i],fd_CC[i]);
                fd_K[i] = calcConductFDRichard(i,fd_theta[i]);//(m/s)
            }

            for (i = /*2*/1;i <= N_Nodes; i++) {
                fd_f1 = 1.0/fd_delt * fd_CC[i];
                fd_f2 = 1.0/(2.0*fd_delx*fd_delx) * (fd_K[i] + fd_K[i+1]);
                fd_f3 = -1.0 / (2.0*fd_delx*fd_delx) * (fd_K[i] + fd_K[i-1]);
                fd_f4 = 1.0 / (2.0*fd_delx) * (fd_K[i+1] - fd_K[i-1]);

                if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_NOFLOW && i == 1) {
                    fd_a[1] = 0.0;
                    fd_b[1] = -fd_f2 - fd_f1;
                    fd_c[1] = fd_f2;
                    fd_d[1] = -fd_f1 * fd_pu[1] - fd_f4 + fd_f3 * fd_delx;
                } else if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_FREEDRAIN && i == 1) {    //Free drainage bottom BC u[1] = u[0]
                    fd_a[1] = 0.0;
                    fd_b[1] = -fd_f2 - fd_f1;
                    fd_c[1] = fd_f2;
                    fd_d[1] = -fd_f1 * fd_pu[1] - fd_f4;
                } else {
                    fd_a[i] = -fd_f3;
                    fd_b[i] = -fd_f2 + fd_f3 - fd_f1;
                    fd_c[i] = fd_f2;
                    fd_d[i] = -fd_f1 * fd_pu[i] - fd_f4;
                }
            }

            //The bottom boundary condition
            if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_WATERTABLE) {
                //water table boundary
                fd_a[1] = 0.0;
                fd_b[1] = 1.0;
                fd_c[1] = 0.0;
                fd_d[1] = fd_pe[1];
            }
            //the upper boundary condition: none flow
            fd_a[N_Nodes] = -fd_f3;
            fd_b[N_Nodes] = fd_f3 - fd_f1;
            fd_c[N_Nodes] = 0.0;
            fd_d[N_Nodes] = -fd_f1 * fd_pu[N_Nodes] - fd_f4 + fd_f2 * fd_delx;

            //if (HourOfDay == 0) std::cout<<" out dry fd_K[1]:"<<fd_K[1]<<" theta:"<<fd_theta[1]<<std::endl;

            if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_FREEDRAIN && j == 5) {
                Darcy_Calculated_Drainage += fd_K[1] * fd_delt;
                //if (HourOfDay == 0) std::cout<<" fd_K[1]:"<<fd_K[1]<<" theta:"<<fd_theta[1]<<std::endl;
            } else if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_WATERTABLE && j == 5) {
                Darcy_Calculated_Drainage += (fd_K[1] + fd_K[2]) / 2.0
                                            * ((fd_u[2] - fd_u[1]) / fd_delx + 1.0)
                                            * fd_delt;
            }

            Tridiagonal(N_Nodes,fd_a,fd_b,fd_c,fd_d,fd_v,fd_tempa,fd_tempb);
            //Transferring new values
            for (i = 1;i <= N_Nodes; i++) {
                fd_u[i] = fd_v[i];
            }
        }//End picard iteration

        //Output for debuging

        //std::cout<<" it:"<<it<<" ";
        //for (i = 1;i <= N_Nodes; i++) {
            //fd_theta[i] = calcWaterContentFDRichard(i,fd_u[i],fd_CC[i]);
            //std::cout<<" "<<fd_theta[i];
        //}
        //std::cout<</*"u[n]:"<<fd_u[N_Nodes]<<*/std::endl;

    }//End drainage loop

    SetNodesThetaFromPressure(fd_u);

    finale_soil_water_m = getTotalSoilWaterFromNodes();

    total_soil_moisture_change = finale_soil_water_m - initial_soil_water_m;
    total_drainage = Darcy_Calculated_Drainage;
    //if (total_infiltrated > Hourly_Water_In_m) total_infiltrated = Hourly_Water_In_m;

    //Adjust infiltration
    //Assume estimated drainage is right
    calculated_infiltration_from_mass_balance = total_soil_moisture_change + total_drainage;
    if (calculated_infiltration_from_mass_balance > Hourly_Water_In_m) {
        extra_infiltrated = calculated_infiltration_from_mass_balance - Hourly_Water_In_m;
        RemoveExtraWaterFromNodes(extra_infiltrated);
        Hourly_Infiltration_m = Hourly_Water_In_m;
        Hourly_Ponded_m = 0.0;
    } else {
        if (calculated_infiltration_from_mass_balance > 0.0) {
            Hourly_Infiltration_m = calculated_infiltration_from_mass_balance;
            Hourly_Ponded_m = Hourly_Water_In_m - Hourly_Infiltration_m;
        } else {
            Hourly_Infiltration_m = 0.0;
            Hourly_Ponded_m = Hourly_Water_In_m - calculated_infiltration_from_mass_balance;
        }
    }

    finale_soil_water_m = getTotalSoilWaterFromNodes();
    total_soil_moisture_change = finale_soil_water_m - initial_soil_water_m;


#ifdef OLDFD
    //At end of this hour, clean up water balance error be carefull the drainage!
    if (control.FD_Bottom_BC_type == FD_BC_BOTTOM_NOFLOW) //No drainge
        total_soil_moisture_change = finale_soil_water_m - initial_soil_water_m;
    else total_infiltrated_from_mass_balance = finale_soil_water_m - initial_soil_water_m + total_drainage;

    if (total_infiltrated_from_mass_balance < 0.0) {
        AddExtraWaterToNodes(-total_infiltrated_from_mass_balance);
        total_infiltrated_from_mass_balance = 0.0;
        finale_soil_water_m = getTotalSoilWaterFromNodes();
    }

    //std::cout<<"Original  Hourly_Ponded_m:"<<Hourly_Ponded_m<<"Hourly_water_in:"<<Hourly_Water_In_m<<std::endl;

    if (total_infiltrated_from_mass_balance > Hourly_Water_In_m) {
        extra_infiltrated = total_infiltrated_from_mass_balance - Hourly_Water_In_m;
        RemoveExtraWaterFromNodes(extra_infiltrated);
        Hourly_Ponded_m = 0.0;
    } else {
        Hourly_Infiltration_m = total_infiltrated_from_mass_balance;
        Hourly_Ponded_m = Hourly_Water_In_m - total_infiltrated_from_mass_balance;
    }
#endif

    //Update state
    //SoilStateRef.Hourly_Ponded_Water_m = Hourly_Ponded_m;
    pond.set_depth(Hourly_Ponded_m);
    SoilStateRef.Hourly_Drainage_m = total_drainage;
    WaterFromNodesToSoilLayer();

    if (!IsMassBalance(Hourly_Water_In_m,total_drainage+Hourly_Ponded_m,initial_soil_water_m,finale_soil_water_m,0.001)) {
    //if (!is_approximately<double>(infiltrated,total_infiltrated)) {
        std::cout
                        <<"SoilProcessesClass::performFDRichard FD mass not balanced!"
                        <<" Real Total Water In:"<<Hourly_Water_In_m
                        <<" Real Total Water Out:"<<" Drain:"<<total_drainage<<" pond:"<<Hourly_Ponded_m
                        <<" Soil water change(m):"<<finale_soil_water_m - initial_soil_water_m
                        <<" Difference:"<<finale_soil_water_m - initial_soil_water_m-Hourly_Water_In_m+Hourly_Ponded_m+Hourly_Drainage_m
                        <<std::endl;

    }

    //Check water balance and update ponded water, infiltration, and drainage M.Liu implement later!!!
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
void SoilProcessesClass::SetNodesThetaFromPressure(double *parrNodePressure)
{
    for (int i = 1;i <= fd_nodes; i++) {
        fd_theta[i] = calcWaterContentFDRichard(i,parrNodePressure[i],fd_CC[i]);
        //std::cout<<" "<<fd_theta[i];
    }
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
double SoilProcessesClass::AddExtraWaterToNodes(double water_to_add)
{
    //Return the left that can't added into the soil
    double leftwater = water_to_add;
    for (int i = fd_nodes; i >= 1; i--) {
        //std::cout<<"i:"<<i<<"Theta:"<<fd_theta[i]<<" WPW:"<<fd_WPW[i]<<std::endl;
        if (leftwater > ((fd_WS[i] - fd_theta[i]) * fd_thick[i])) {
            if (fd_theta[i] < fd_WS[i]) {
                leftwater -= (fd_WS[i] - fd_theta[i])*fd_thick[i];
                fd_theta[i] = fd_WS[i];
            }
        } else {
            fd_theta[i] += leftwater/fd_thick[i];
            leftwater = 0.0;
        }
    }
    //if (leftwater > 1.0e-6) {
        //std::cout<<"Extra water:"<<leftwater<<" can't added to soil nodes."<<std::endl;
        //nrerror("Can't add extra water to nodes!");
    //}
    return leftwater;
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
void SoilProcessesClass::WaterFromNodesToSoilLayer()
{
    for (int layer = 1; layer <= Num_Soil_Layers; layer++) {
        SoilStateRef.Water_Content[layer] = 0.0;
    }
    for (int i = 1;i <= fd_nodes; i++) {
        for (int layer = 1; layer <= Num_Soil_Layers; layer++) {
            SoilStateRef.Water_Content[layer] += fd_theta[i] * fd_thick[i] * fd_fraction[i][layer];
        }
    }
    for (int layer = 1; layer <= Num_Soil_Layers; layer++) {
        SoilStateRef.Water_Content[layer] /= SoilProfileRef.Layer_Thickness_m[layer];
    }
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
void SoilProcessesClass::WaterFromSoilLayerToNodes()
{
    for (int i = 1;i <= fd_nodes; i++) {
        fd_theta[i] = 0.0;
    }

    for (int layer = 1; layer <= Num_Soil_Layers; layer++) {
        for (int i = 1;i <= fd_nodes; i++) {
            fd_theta[i] += fd_fraction[i][layer] * SoilStateRef.Water_Content[layer];
        }
    }

    for (int i = 1;i <= fd_nodes; i++) {
        fd_u[i] = SoilStateRef.calc_h_Theta(fd_theta[i],fd_pe[i],fd_WS[i],fd_b_value[i]);
    }
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
double SoilProcessesClass::getTotalSoilWaterFromNodes()
{
    double water_m = 0; //(m)
    for (int i = 1;i <= fd_nodes; i++) {
        water_m += fd_theta[i] * fd_thick[i];
    }
    return water_m;
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
void SoilProcessesClass::RemoveExtraWaterFromNodes(double extra_infiltrated)
{
    double leftwater;
    double total_avw = 0;
    double rate;

    for (int i = fd_nodes; i >= 1; i--) {
        //std::cout<<"i:"<<i<<"Theta:"<<fd_theta[i]<<" WPW:"<<fd_WPW[i]<<std::endl;
        total_avw += std::max<double>((fd_theta[i] - fd_WPW[i]) * fd_thick[i],0.0);
    }
    if ((total_avw > extra_infiltrated) && (total_avw > 1.0e-8)) {
        rate = extra_infiltrated / total_avw;
        leftwater = 0.0;
    } else {
        rate = 1.0;
        leftwater = extra_infiltrated - total_avw;
    }

    for (int i = fd_nodes; i >= 1; i--) {
        fd_theta[i] -= std::max<double>((fd_theta[i] - fd_WPW[i]) * rate,0.0);
    }
    if (leftwater > 1.0e-8) {
        std::cout<<"Extra water:"<<leftwater<<" can't removed from soil nodes."<<std::endl;
        nrerror("Can't remove extra water from nodes!");
    }
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
void SoilProcessesClass::InitializeFDRichard()
{
    int L_Soil;
    double thick;
    bFirst_FD = true;
    fd_delx = control.FD_Delx;//0.05;     //(meter) M.Liu Mar 20, 2014
    fd_delt = control.FD_Delt;//72;//36;      //(seconds) M.Liu Mar 20, 2014
    fd_nodes = (int)floor(SoilProfileRef.getTotoalSoilDepth_m() / fd_delx + 0.5) + 1;

    fd_a.resize(fd_nodes+2,0);                 
    fd_b.resize(fd_nodes+2,0);                 
    fd_c.resize(fd_nodes+2,0);                 
    fd_d.resize(fd_nodes+2,0);                 
    fd_v.resize(fd_nodes+2,0);                 
    fd_tempa.resize(fd_nodes+2,0);             
    fd_tempb.resize(fd_nodes+2,0);             
    fd_u.resize(fd_nodes+2,0);                 
    fd_pu.resize(fd_nodes+2,0);                
    fd_K.resize(fd_nodes+2,0);                 
    fd_CC.resize(fd_nodes+2,0);                
    fd_theta.resize(fd_nodes+2,0);             
    fd_soil_layer_index.resize(fd_nodes+2,0);  
    fd_pe.resize(fd_nodes+2,0);                
    fd_WS.resize(fd_nodes+2,0);                
    fd_WPW.resize(fd_nodes+2,0);               
    fd_KS.resize(fd_nodes+2,0);                
    fd_b_value.resize(fd_nodes+2,0);           
    fd_theta_b.resize(fd_nodes+2,0);           
    fd_thick.resize(fd_nodes+2,0);             

    fd_fraction = alloc_2d_array<double>(fd_nodes+2,Num_Soil_Layers+1,"SoilProcessClass::FD_RICHARD");

    for (int i = 0; i <= (fd_nodes+1); i++) {
        if (i == 1 || i == fd_nodes) thick = fd_delx/2.0;
        else thick = fd_delx;
        fd_thick[i] = thick;
    }

    setFDNodesFraction();
    setFDLayerIndex();

    for (int i = 0; i <= (fd_nodes+1); i++) {
        L_Soil = fd_soil_layer_index[i];
        //L_Soil = 1;//Debug only!!
        //std::cout<<"i:"<<i<<" Layer_Index:"<<L_Soil<<std::endl;
        fd_pe[i] = SoilProfileRef.Air_Entry_Potential[L_Soil] * m_P_kPa;
        fd_WS[i] = SoilProfileRef.Saturation_Water_Content[L_Soil];
        fd_WPW[i] = SoilProfileRef.Permanent_Wilting_Point[L_Soil];
        fd_KS[i] = SoilProfileRef.K_Sat[L_Soil] * m_h_P_KgS_m3 / 3600.0;    //(m/s)
        fd_b_value[i] = SoilProfileRef.b_Value[L_Soil];
        fd_theta_b[i] = SoilProfileRef.Theta_b[L_Soil];
        //std::cout<<"i:"<<i<<" Layer_Index:"<<L_Soil<<" fd_theta_b:"<<fd_theta_b[i]<<" WS:"<<fd_WS[i]<<std::endl;
    }
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
void SoilProcessesClass::setFDLayerIndex()
{
    //Identify the soil layer holds the majority of node's domain or the toppart
    double f1,f2;
    int t1,t2;
    bool found_first;
    bool found_two_layers;

    for (int i = 1;i <= fd_nodes; i++) {
        found_first = false;
        found_two_layers = false;
        for (int layer = 1; layer <= Num_Soil_Layers; layer++) {
            if (fd_fraction[i][layer] > 1.0e-6) {
                if (!found_first) {
                    f1 = fd_fraction[i][layer];
                    t1 = layer;
                    found_first = true;
                } else {
                    f2 = fd_fraction[i][layer];
                    t2 = layer;
                    found_two_layers = true;
                }
            }
        }
        if (!found_two_layers) {
            fd_soil_layer_index[i] = t1;
        } else {
            if (!is_approximately<double>(f1,f2)) {
                fd_soil_layer_index[i] = std::min<int>(t1,t2);
            } else {
                if (f1 > f2) fd_soil_layer_index[i] = t1;
                else fd_soil_layer_index[i] = t2;
            }
        }
    }

    fd_soil_layer_index[0] = Num_Soil_Layers;
    fd_soil_layer_index[fd_nodes + 1] = 1;
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
void SoilProcessesClass::setFDNodesFraction()
{
    //Set fractions of nodes in each soil layer
    int soil_layers = Num_Soil_Layers;
    double top_part,node_low,node_high;
    int current_soil_layer;
    for (int i = 1;i <= fd_nodes; i++) {
        for (int layer = 1; layer <= Num_Soil_Layers; layer++) {
            fd_fraction[i][layer] = 0.0;
        }
    }

    current_soil_layer = soil_layers;
    node_low = SoilProfileRef.Layer_Bottom_Depth_m[soil_layers];    //depth
    for (int i = 1;i < fd_nodes; i++) {
        node_high = node_low - fd_thick[i];
        if (node_high <= SoilProfileRef.Layer_Bottom_Depth_m[current_soil_layer-1]) {
            current_soil_layer--;
            top_part = SoilProfileRef.Layer_Bottom_Depth_m[current_soil_layer] - node_high;
            fd_fraction[i][current_soil_layer] = top_part / fd_thick[i];
            fd_fraction[i][current_soil_layer+1] = 1.0 - top_part / fd_thick[i];
        } else {
            fd_fraction[i][current_soil_layer] = 1.0;
        }
        node_low -= fd_thick[i];    //for next node
    }
    fd_fraction[fd_nodes][1] = 1.0;

    /*for (int i = 1;i <= fd_nodes; i++) {
        for (int L = 1; L <= soil_layers; L++) {
            std::cout<<"i:"<<i<<" L:"<<L<<" f:"<<fd_fraction[i][layer]<<std::endl;
        }
    }*/

}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
int SoilProcessesClass::getSoilLayerIndex(double bottom_depth_m)
{
    int layer_index = -1;
    double soil_bottom_layer_depth;

    for (int layer = 1; layer <= Num_Soil_Layers; layer++) {
        soil_bottom_layer_depth = SoilProfileRef.Layer_Bottom_Depth_m[layer];
        if ((fabs(bottom_depth_m-soil_bottom_layer_depth) <= 0.005) || bottom_depth_m <= soil_bottom_layer_depth) {
            layer_index = layer;
            layer = Num_Soil_Layers;
        }
    }
    return layer_index;
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
double SoilProcessesClass::calcConductFDRichard(int node_index,double theta)
{
    double k;   //(same unit with fd_KS)

    k = calc_K_Theta(theta
                     ,fd_WS[node_index]
                     ,fd_KS[node_index]
                     ,fd_b_value[node_index]
                     ,fd_theta_b[node_index]
                     /*,0.0*/);
    return k;
}
#endif
//______________________________________________________________________________
#ifdef LIU_FD_RICHARD
double SoilProcessesClass::calcWaterContentFDRichard(int node_index,double p,double &dwdp)
{
    //i is element number
    //p:
    double w,B1;
    if (p < fd_pe[node_index]) {
        B1 = 1.0 / fd_b_value[node_index];
        w = fd_WS[node_index] * pow((fd_pe[node_index] / p), B1);
        dwdp = -w * B1 / p;
    } else {
      w = fd_WS[node_index];
      dwdp = 0.00001;
    }
    return w;
}
#endif
#ifdef MBVB_FD
double SoilProcessesClass::calcWaterContent(int i,double p,double &dwdp)
{
    //i is element number
    double w,B1;
    if (p < pe[i]) {
        B1 = 1 / b[i];
        w = WS[i] * pow((pe[i] / p), B1);
        dwdp = -w * B1 / p;
    } else {
      w = WS[i];
      dwdp = 0.00001;
    }

    w = std::min<double>(w,WS[i] - WC_ICE[i]);  //FMS Mar 14, 2014
    return w;
}
//______________________________________________________________________________
#endif
#ifdef MBVB_FD
double SoilProcessesClass::elementflux(int i,double &djdpu,double &djdpl)
{
    //i is element number; upper p is i, lower is i+1

    const double Gr = standard_gravity;      //gravitational constant
    double kbar,ku,kl,dkdpu,dkdpl;
    double phiu,phil;
    double element_flux;
    int nn = SoilProfileRef.Number_Of_Effective_Soil_Nodes;

    double water_pot_ip1 = (i==nn) ? p[i] : p[i+1];       //140604RLN

    double tt_p_iplus = water_pot_ip1;
    double tt_p_i = p[i];

    if (water_pot_ip1/*p[i+1]*/ < pe[i]) {
        kl = KS[i] * pow((pe[i] / water_pot_ip1/*p[i+1]*/), N[i]);
        kl = (kl * Soil_Vapor_Conductance[i]) / (kl + Soil_Vapor_Conductance[i]);
        phil = kl * water_pot_ip1/*p[i+1]*/ / (1 - N[i]);
    } else {
        kl = KS[i];
        kl = (kl * Soil_Vapor_Conductance[i]) / (kl + Soil_Vapor_Conductance[i]);
        phil = kl * (pe[i] * N[i] / (1 - N[i]) + water_pot_ip1/*p[i+1]*/);
    }

    if (p[i] < pe[i]) {
        ku = KS[i] * pow((pe[i] / p[i]), N[i]);
        ku = (ku * Soil_Vapor_Conductance[i]) / (ku + Soil_Vapor_Conductance[i]);
        phiu = ku * p[i] / (1 - N[i]);
    } else {
        ku = KS[i];
        ku = (ku * Soil_Vapor_Conductance[i]) / (ku + Soil_Vapor_Conductance[i]);
        phiu = ku * (pe[i] * N[i] / (1 - N[i]) + p[i]);
    }

    if (fabs(p[i] - water_pot_ip1/*p[i+1]*/) < 0.1) {
        kbar = 0.5 * (ku + kl);
        dkdpu = -N[i] * ku / p[i];
        dkdpl = -N[i] * kl / water_pot_ip1/*p[i+1]*/;
        if (dkdpu == 0.0/*is_approximately<double>(dkdpu,0,1.0e-20)*/) dkdpu = 1.0e-20;//1E-20; M.Liu
    } else {
        kbar = (phiu - phil) / (p[i] - water_pot_ip1/*p[i+1]*/);
        dkdpu = (kbar - ku) / (water_pot_ip1/*p[i+1]*/ - p[i]);
        dkdpl = (kl - kbar) / (water_pot_ip1/*p[i+1]*/ - p[i]);

        if (dkdpl == 0.0/*is_approximately<double>(dkdpl,0,1.0e-20)*/) dkdpl = 1.0e-20;//1E-20; M.Liu
    }

    element_flux = (phil - phiu) / (z[i+1] - z[i]) - Gr * kbar;
    djdpl = kl / (z[i+1] - z[i]) + Gr * dkdpl;
    djdpu = ku / (z[i+1] - z[i]) + Gr * dkdpu;
    return element_flux;
}
//______________________________________________________________________________
#endif
#ifdef MBVB_FD
bool SoilProcessesClass::SolveLayerInf(int hour,double dt,double &Flux,double &Drainage,double Actual_Evaporation,
                   bool &Sat_BC,/* LML 14/05/07 WeatherStateDailyClass &Weather,*/double &Finite_Difference_Error)
{
    //flux is passed in as the flux into the surface and is returned as the computed flux through element 1
    bool Success;
    const int maxits = 2000;  //maximum number of iterations
    const double WD = 1000;     //density of water


    int m;            //number of effective soil layers for FD calculations (depends on bottom boundary condition)
    int nn;           //number of effective nodes for FD calculations (depends on bottom boundary condition)
    int NNmax;        //Absolute maximum number of nodes defined for the simulation
    int NLFWT;        //number of real soil layers not affected by a water table


    double abv;
    double Air_Dry_Water_Content_1;
    double Air_Dry_Water_Content_2;
    double Atmospheric_Water_Potential;
    double Balance;
    int count;
    double dwdpu,dwdpl;
    double Drainage_Error_mm;
    double Expected_Lower_Boundary_Water_Potential;
    double fde;
    double FWC; //initial water content
    double Hourly_Relative_Humidity;
    int i;
    double im;  //maximum allowable mass balance error
    double IWC; //final water content
    double lim;
    double Max_Drainage;
    int nits;
    double PWC;
    double SE;
    double sum_dt;
    double temporary_drainage;
    double temporary_flux;
    double Vapor_Path_Length;
    double Water_Content_Change_Due_To_Soil_Water_Evaporation;
    double WC_Threshold;
    double wcdif;

    double Initial_Profil_WC = 0.0;       //(m) FMS Feb 26, 2014
    double Final_Profil_WC = 0.0;         //(m)FMS Feb 26, 2014
    int NL;                         //FMS Feb 26, 2014
    int layer;                          //FMS Feb 26, 2014
    double wc_node;

    NL = Num_Soil_Layers; //FMS Feb 26, 2014
    m = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    nn = SoilProfileRef.Number_Of_Effective_Soil_Nodes;
    NNmax = SoilProfileRef.Number_Of_Total_Nodes;
    NLFWT = SoilProfileRef.Number_Of_Uninundated_Soil_Layers;

    //Initial_Profil_WC = SoilStateRef.getTotalSoilWaterContent_m();    //FMS Feb 26, 2014
    for (layer = 1; layer <= NL; layer++) {   //FMS Feb 26, 2014
        Initial_Profil_WC += SoilStateRef./*LML 140611 Hourly_*/Water_Content[layer] * SoilProfileRef.Layer_Thickness_m[layer];    //FMS Feb 26, 2014
    }



    SoilStateRef.setSoilWater();
    /*std::cout<<"Hourly_Water_Content[1]:"<<SoilStateRef.Hourly_Water_Content[1]
             <<"Water_Content[1]:"<<SoilStateRef.Water_Content[1]
             <<std::endl;*/

    for (i = 1; i <= nn; i++) {
        pe[i] = SoilProfileRef.Air_Entry_Potential[i];
        v[i] = SoilProfileRef.Node_Soil_Volume[i];
        V_Upper[i] = SoilProfileRef.Upper_Node_Soil_Volume[i];  //M.Liu don't know if the node's upper & lower is the same as soil's upper and lower layer
        V_Lower[i] = SoilProfileRef.Lower_Node_Soil_Volume[i];
        z[i] = SoilProfileRef.Node_Depth[i];
        b[i] = SoilProfileRef.b_Value[i];
        WS[i] = SoilProfileRef.Saturation_Water_Content[i];
        KS[i] = SoilProfileRef.K_Sat[i];
        N[i] = SoilProfileRef.n_Value[i];
        DZ[i] = SoilProfileRef.Layer_Thickness_m[i];
        wu[i] = SoilStateRef.Upper_Water_Content[i];
        wl[i] = SoilStateRef.Lower_Water_Content[i];

        //if (i > 1) wc_node = (wl[i-1]*V_Lower[i-1] + wu[i]*V_Upper[i])/(V_Lower[i-1]+V_Upper[i]);    //M.Liu Mar 20, 2014
        //else wc_node = wu[i];                                                                       //M.Liu Mar 20, 2014
        //p[i] = SoilStateRef.calc_h_Theta(wc_node, pe[i], WS[i], b[i]);                              //M.Liu Mar 20, 2014

        p[i] = SoilStateRef.calc_h_Theta(wu[i], pe[i], WS[i], b[i]);    //M. Liu Q: should use (wl[i-1]*V_Lower[i-1] + wu[i]*V_Upper[i])/(V_Lower[i-1]+V_Upper[i])?

        Soil_Vapor_Conductance[i] = 9999.; //This is a large, non limiting conductance value
        WC_ICE[i] = SoilStateRef.Ice_Content[i];    //FMS Mar 14, 2014

        //LML 14/05/13 debug
        /*std::cout<<"pe["<<i<<"]:"<<pe[i]<<std::endl
                 <<"v["<<i<<"]:"<<v[i]<<std::endl
                 <<"V_Upper["<<i<<"]:"<<V_Upper[i]<<std::endl
                 <<"V_Lower["<<i<<"]:"<<V_Lower[i]<<std::endl
                 <<"z["<<i<<"]:"<<z[i]<<std::endl
                 <<"b["<<i<<"]:"<<b[i]<<std::endl
                 <<"WS["<<i<<"]:"<<WS[i]<<std::endl
                 <<"KS["<<i<<"]:"<<KS[i]<<std::endl
                 <<"N["<<i<<"]:"<<N[i]<<std::endl
                 <<"DZ["<<i<<"]:"<<DZ[i]<<std::endl
                 <<"wu["<<i<<"]:"<<wu[i]<<std::endl
                 <<"wl["<<i<<"]:"<<wl[i]<<std::endl
                 //<<"wc_node:"<<wc_node<<std::endl
                 <<"p["<<i<<"]:"<<p[i]<<std::endl
                 <<"Soil_Vapor_Conductance["<<i<<"]:"<<Soil_Vapor_Conductance[i]<<std::endl
                 <<"WC_ICE["<<i<<"]:"<<WC_ICE[i]<<std::endl;
         */
    }

    //Depth of very last node at the bottom of soil profile plus two layers
    z[nn + 1] = SoilProfileRef.Node_Depth[nn + 1];

    //RS: needs attention!!!
    //Call CalculateSoilWaterEvaporation(Flux, Actual_Evaporation, Atmospheric_Water_Potential, dt, Hour, _
                                       //Process, Soil, Weather)
    //for the time-being:
    Atmospheric_Water_Potential = -70000;   //LML 14/06/04 In CropSyst it is calculated


    if (Sat_BC) {
        p[1] = pe[1];
        Jl[0] = 0;
    } else {
        Jl[0] = -Flux; //Flux downward is negative by convention
    }

    if (SoilProfileRef.Water_Table_Boundary) {//LML 14/06/03 need check!!!
        for (i = nn + 1; i <= NNmax - 1; i++) {
            p[i] = pe[i];
        }
    } else {
        Expected_Lower_Boundary_Water_Potential = -14.219 * log(SoilProfileRef.Clay_Percentage[nn]) + 6.;
    }


    IWC = 0;
    for (i = 1; i <= NLFWT/*FMS Feb 28, 2014 + 2*/; i++) { //initial water depth for all effective soil layers
      IWC += ((wu[i] * V_Upper[i] + wl[i] * V_Lower[i]) / (V_Upper[i] + V_Lower[i])) * DZ[i] * WD;
    }


    temporary_flux = 0;
    nits = 0;
    im = 1.0e-6;


    do{
        //Begin to iterate and find a solution at given time step
        SE = 0;
        nits++;
        fde = 0;

        #ifdef LIU_DEBUG
        double tt_vi;
        double tt_a;
        double tt_C;
        double tt_bx;
        double tt_f;
        double tt_J1_i_mnus;
        double tt_J1_i;
        double tt_wnu_i;
        double tt_wu_i;
        double tt_wnl_i_minus;
        double tt_wl_i_minus;
        double tt_djdpu;
        double tt_djdpl;
        #endif

        for (i = 1;i <= nn; i++) {

            if (i == 1) {     //LML 15/05/13 need check with Fidel
                djdpu[i-1] = 0;
                djdpl[i-1] = 0;
                cpl[i-1] = 0;
                wnl[i-1] = 0;
                wl[i-1] = 0;
            }

            Jl[i] = elementflux(i, djdpu[i], djdpl[i]);
            wnu[i] = calcWaterContent(i, p[i], dwdpu);
            wnl[i] = calcWaterContent(i, p[i+1], dwdpl);    //LML 14/06/03 need check node nn

            cpl[i] = v[i] * dwdpl / (2 * dt);
            cpu[i] = v[i] * dwdpu / (2 * dt);

            a[i] = -djdpu[i-1];
            C[i] = -djdpl[i];
            bx[i] = djdpl[i-1] + djdpu[i] + cpu[i] + cpl[i-1];

            //if ((i == 1)) f[i] = Jl[i-1] - Jl[i] + v[i] * (wnu[i] - wu[i] + wnl[i-1] - wl[i-1]) / (dt);  //M.Liu what's wnl[0] & wl[0]?
            if ((i == 1)) f[i] = Jl[i-1] - Jl[i] + v[i] * (wnu[i] - wu[i]) / (dt);  //M.Liu what's wnl[0] & wl[0]?
            else f[i] = Jl[i-1] - Jl[i] + v[i] * (wnu[i] - wu[i] + wnl[i-1] - wl[i-1]) / (2.0 * dt);

            #ifdef LIU_DEBUG
            tt_djdpu = djdpu[i];
            tt_djdpl = djdpl[i];
            tt_vi = v[i];
            tt_a = a[i];
            tt_C = C[i];
            tt_bx = bx[i];
            tt_f = f[i];
            tt_J1_i_mnus = Jl[i-1];
            tt_J1_i = Jl[i];
            tt_wnu_i = wnu[i];
            tt_wu_i = wu[i];
            tt_wnl_i_minus = wnl[i-1];
            tt_wl_i_minus = wl[i-1];
            #endif

            SE += fabs(f[i]);
            fde += f[i];

            //LML 15/05/13 Debug
            /*std::cout<<"nit:"<<nits<<std::endl
                    <<"i:"<<i<<std::endl
                    <<" Jl[i]:"<<Jl[i]<<std::endl
                    <<" wnu[i]:"<<wnu[i]<<std::endl
                    <<" wnl[i]:"<<wnl[i]<<std::endl
                    <<" cpl[i]:"<<cpl[i]<<std::endl
                    <<" cpu[i]:"<<cpu[i]<<std::endl
                    <<" a[i]:"<<a[i]<<std::endl
                    <<" C[i]:"<<C[i]<<std::endl
                    <<" bx[i]:"<<bx[i]<<std::endl
                    <<" f[i]:"<<f[i]<<std::endl
                    <<" SE:"<<SE<<std::endl
                    <<" fde:"<<fde<<std::endl;
            */
        }

        if (Sat_BC) {
            SE -= fabs(f[1]);
            fde -= f[1];
            f[1] = 0;
            C[1] = 0;
        }

        for (i = 1; i <= nn - 1; i++) {
            C[i] /= bx[i];
            f[i] /= bx[i];
            bx[i+1] -= a[i+1] * C[i];
            if (bx[i+1] < 0.00001) bx[i+1] = 0.00001;
            f[i+1] -= a[i+1] * f[i];
            //LML 15/05/13 Debug
            /*std::cout<<"nit:"<<nits<<std::endl
                    <<"i:"<<i<<std::endl
                    <<" C[i]:"<<C[i]<<std::endl
                    <<" f[i]:"<<f[i]<<std::endl
                    <<" bx[i]:"<<bx[i]<<std::endl
                    <<" bx[i+1]:"<<bx[i+1]<<std::endl
                    <<" a[i+1]:"<<a[i+1]<<std::endl
                    <<" f[i+1]:"<<f[i+1]<<std::endl;
            */
        }

        dp[nn] = f[nn] / bx[nn];
        p[nn] -= dp[nn];


        for (i = nn - 1; i>= 1; i--) {
            dp[i] = f[i] - C[i] * dp[i+1];
            lim = 0.8 * fabs(p[i]);
            abv = fabs(dp[i]);
            if (abv > lim) dp[i] = lim * dp[i] / abv;
            p[i] -= dp[i];
            if (p[i] > (pe[i] / 10000.0)) p[i] = pe[i] / 10000.0; //NEW CONDITION
        }

        if (p[1] < Atmospheric_Water_Potential) p[1] = Atmospheric_Water_Potential;

        if (!SoilProfileRef.Water_Table_Boundary) p[nn + 1] = std::min<double>(p[nn], Expected_Lower_Boundary_Water_Potential);

        //if (p(nn) > p(nn - 1)) { Stop
        p[nn] = p[nn-1];
        if (p[nn] > pe[nn]) p[nn] = pe[nn];

        //This to get off the loop when se<im but it is clear that top layer potential is less than air entry potential
        if (!Sat_BC && pe[1] < p[1]) {
            if ((SE < im) || (nits > 50)) {
                nits = maxits + 1;
                Sat_BC = true;      //FMS Mar 5, 2014
            }
        }

        //if (nits > 500) im = 0.05;   //new
        //else if (nits > 300) im = 0.005;  //was 0.05
        //else if (nits > 250) im = 0.0025; //was 0.005
        //else if (nits > 200) im = 0.00025; //was 0.0005
        //else */if (nits > 150) im = 0.0001;
        //else if (nits > 100) im = 0.00001;
        if (nits > 150) im = 1.0e-4;
        else if (nits > 100) im = 1.0e-5;

        //LML debug only
        /*std::cout<<"nits:"<<nits
                 <<" SE:"<<SE
                 <<" im:"<<im
                 <<" pe[1]:"<<pe[1]
                 <<" p[1]:"<<p[1]
                 <<std::endl;*/
    }while ((nits < maxits) && ((SE >= im) || (pe[1] < p[1]))); //End of iteration to find a solution at given time step

    if (nits < maxits) { //set up for successful completion of iterative solution
        Success = true;

        //RS: needs attention!!!
        //    SumEvap = SumEvap + Actual_Evaporation //in mm/hr

        //Set new layer water content at solution node water potentials
        for (i = 1; i <= m + 1; i++) {
            wnu[i] = calcWaterContent(i, p[i], dwdpu);          //M.Liu Q: wnu[i] is layer i?
            wnl[i] = calcWaterContent(i, p[i+1], dwdpl);

            SoilStateRef.Old_Upper_Water_Content[i] = wu[i];
            SoilStateRef.Old_Lower_Water_Content[i] = wl[i];
            SoilStateRef.New_Upper_Water_Content[i] = wnu[i];
            SoilStateRef.New_Lower_Water_Content[i] = wnl[i];
        }

        //Needed for chemical transport
        //set water content above first soil layer (an abstraction) to zero
        SoilStateRef.Old_Upper_Water_Content[0] = 0;
        SoilStateRef.Old_Lower_Water_Content[0] = 0;
        SoilStateRef.New_Upper_Water_Content[0] = 0;
        SoilStateRef.New_Lower_Water_Content[0] = 0;


        if (Sat_BC) Flux = (-Jl[1] + v[1] * (wnu[1] - wu[1]) / dt);
        else Flux = -Jl[0];

        FWC = 0;
        for (i = 1; i <= NLFWT/*FMs Feb 28, 2014 + 2*/; i++) { //Final water depth for all effective soil layers
            FWC += (wnu[i] * V_Upper[i] + wnl[i] * V_Lower[i]) / (V_Upper[i] + V_Lower[i]) * DZ[i] * WD;
        }

        if (Sat_BC) Drainage = (IWC - FWC) / dt + (-Jl[1] + v[1] * (wnu[1] - wu[1]) / dt);
        else Drainage = (IWC - FWC) / dt + (-Jl[0]); //drainage (mm/s)

        for (i = 1;i <= m + 1; i++) { //Roger includes extra soil layer
          SoilStateRef.Upper_Water_Content[i] = wnu[i];
          SoilStateRef.Lower_Water_Content[i] = wnl[i];
        }

        //CalculateLayerSoilWater_Content - RS: this used to be a separate Function, now integrated
        for (i = 1;i <= m + 1; i++) {
            SoilStateRef./*LML 140611 Hourly_*/Water_Content[i] = (wnu[i] * V_Upper[i] + wnl[i] * V_Lower[i]) / (V_Upper[i] + V_Lower[i]);
        }

        for (layer = 1; layer <= NL; layer++) {
            Final_Profil_WC += SoilStateRef./*LML 140611 Hourly_*/Water_Content[layer] * SoilProfileRef.Layer_Thickness_m[layer];  //FMS Feb 26, 2014
        }

        if (SoilProfileRef.Water_Table_Boundary) {
            for (i = m + 2; i <= NNmax - 2; i++) {
                SoilStateRef./*LML 140611 Hourly_*/Water_Content[i] = SoilProfileRef.Saturation_Water_Content[i];
            }
        }

        Balance_Profile_FD = -Jl[0] * dt + IWC - FWC - Drainage * dt;   //mm FMS Feb 26, 2014


        //NEW------------------------------------------------------------------------------------------
        Max_Drainage = KS[nn-3] * 9.8; //converting (kg*s/m3) into (kg/m2/s) which is equal to (mm/s)

        if (Drainage < 0) {
            //negative drainage (=upward movement)
            Drainage_Error_mm = Drainage * 3600;
            Drainage = 0;
            Adjust_FD_Drainage_Error(Drainage_Error_mm, Drainage, Flux);
        } else {
            //drainage is bigger than Ks
            if (Drainage > Max_Drainage) {
                Drainage_Error_mm = (Drainage - Max_Drainage) * 3600; //Drainage_Error_mm (mm/h)
                Drainage = Max_Drainage;
                Adjust_FD_Drainage_Error(Drainage_Error_mm, Drainage, Flux);
            } else {
                //no problem encountered, all water infiltrated as described by FD-routine
                //if (Sat_BC = True) { Stop
                //SoilStateRef.Hourly_Ponded_Water_m = 0;
                pond.set_depth(0.0);
            }
        }

        SoilStateRef.setSoilWaterByNewUpperAndLower(NLFWT);// ' FMS Mar 3, 2014
        FWC = 0;    // 'FMS Feb 28, 2014
        for (i = 1; i <= NLFWT; i++) {    //  'Final water depth for all effective soil layers 'FMS Feb 28, 2014
            FWC += (SoilStateRef.New_Upper_Water_Content[i] * V_Upper[i] + SoilStateRef.New_Lower_Water_Content[i] * V_Lower[i])
                    / (V_Upper[i] + V_Lower[i]) * DZ[i] * WD  ;//'FMS Feb 28, 2014
        }

    } else {
        Success = false;
        //SoilStateRef.ResetSoilWaterStatus(Initial_SavePot, Initial_Save_wu, Initial_Save_wl, wu, wl); LML do nothing
    }

    Finite_Difference_Error = fde;  //LML 14/06/04
    return Success;
}
#endif
//_____________________________________________________________________________/
#ifdef MBVB_FD
void SoilProcessesClass::setSoilWater(int NLmax)
{
    //New sub FMS Mar 5, 2014
    int i;
    double dwdp;

    wu[1] = SoilStateRef./*LML 140611 Hourly_*/Water_Content[1];
    wnu[1] = wu[1];
    wl[1] = SoilStateRef./*LML 140611 Hourly_*/Water_Content[1];
    wnl[1] = SoilStateRef./*LML 140611 Hourly_*/Water_Content[1];
    //p[1] = SoilStateRef.calc_h_Theta(CSng(wu[1]), CSng(pe[1]), SoilProfileRef.SaturationWaterContent[1], b[1])

    //This sets the water content for layers 2 to number of soil layers
    //For i = 2 To NLmax + 1
    for (i = 2; i <= NLmax; i++) {    //FMS Mar 11, 2014
        wu[i] = SoilStateRef./*LML 140611 Hourly_*/Water_Content[i];
        wnu[i] = wu[i];
        wl[i] = SoilStateRef./*LML 140611 Hourly_*/Water_Content[i];
        wnl[i] = wu[i];
        //p[i] = WaterPotential(wu[i], pe[i], b[i], SoilProfileRef.SaturationWaterContent[i])
        //p[i] = SoilStateRef.calc_h_Theta(CSng(wu[i]), CSng(pe[i]), SoilProfileRef.SaturationWaterContent[i], b[i])
    }
    for (i = NLmax + 1; i <= NLmax + 3; i++) {    //FMS Mar 11, 2014
      wu[i] = SoilStateRef./*LML 140611 Hourly_*/Water_Content[NLmax];
      wnu[i] = wu[i - 1];
      wl[i] = SoilStateRef./*LML 140611 Hourly_*/Water_Content[i-1];
      wnl[i] = SoilStateRef./*LML 140611 Hourly_*/Water_Content[i-1];
      //p[i] = SoilStateRef.calc_h_Theta(CSng(wu[i-1]), CSng(pe[i-1]), SoilProfileRef.SaturationWaterContent[i-1], b[i-1])
    }   //FMS Mar 11, 2014

    if (SoilProfileRef.Water_Table_Boundary) {
        for (i = SoilProfileRef.Number_Of_Uninundated_Soil_Layers + 1; i <= NLmax + 1; i++) {
            wu[i] = SoilProfileRef.Saturation_Water_Content[i];
            wl[i] = SoilProfileRef.Saturation_Water_Content[i];
            //p[i] = pe[i]
        }
    }

    //Roger
    //If Not SoilProfileRef.WaterTableBoundary Then p(NLmax + 2) = p(NLmax + 1) 'Last node at the bottom of the "extended" soil profile (may not be needed)
}
//______________________________________________________________________________
#endif
#ifdef MBVB_FD
//140511 This is actually not used anymore
void SoilProcessesClass::SaveSoilWaterStatus()
{
    int m = SoilProfileRef.Number_Of_Effective_Soil_Layers;;
    for (int layer = 1; layer <= m + 1; layer++) {
        Initial_SavePot[layer] = SoilStateRef.Water_Potential[layer];     //this was calculated at the end of previous time step
        Initial_Save_wu[layer] = SoilStateRef.New_Upper_Water_Content[layer]; //this was calculated at the end of previous time step
        Initial_Save_wl[layer] = SoilStateRef.New_Lower_Water_Content[layer]; //this was calculated at the end of previous time step
    }
}
#endif
//_____________________________________________________________________________/



/* //140429 commened out by M.Liu ????   RLN appears to be obsolete
void SoilProcessesClass::assignApparentKsat()
{
    //(m/h) Determine apparent hydraulic conductivity that matches field capacity characteristics
    for (int L = 0; L<num_layers; L++) {
        Apparent_K_Sat[layer] = thick[layer] * water_density
                    * pow(vwc_sat[layer],m[layer])
                    * (pow(vwc_fc[layer],(1 - m[layer])) - pow(vwc_sat[layer],(1 - m[layer])))
                    / (Gravity * hr_fc[layer] * 3600 * (m[layer] - 1));
        if (Apparent_K_Sat[layer] < 0) Apparent_K_Sat[layer] = 1.e-10;
    }
};
*/
//______________________________________________________________________________

/*#ifdef MBVB_INFILTRATION
//140303 RLN obsolete
double SoilProcessesClass::calDeltaVWC(const double tvwc,const int layer, const double timestep_s)
{
    //Calculating the potential outflow from soil when vwc > field capacity
    //(second) timestep_s
    double thickness_layer = SoilProfileRef.get_thickness_m(layer);      // soil.properties.layers.get_thickness_m(layer);
    double WC_sat_layer =
            SoilProfileRef.get_saturation_water_content_volumetric(layer,SoilStateRef.Ice_Content[layer]);
            // Saturation_Water_Content[layer];  // soil.properties.hydraulics.get_saturation_water_content_volumetric(layer);
    //double FC_layer =  SoilProfileRef.Field_Capacity[layer];               //soil.properties.hydraulics.get_field_capacity_volumetric(layer);
    //double PWP_layer = SoilProfileRef.Permanent_Wilting_Point[layer];      // soil.properties.hydraulics.get_permanent_wilt_point_volumetric(layer);
    //double water_pot_at_FC_layer = SoilProfileRef.FC_WPot[layer];          //soil.properties.hydraulics.get_water_pot_at_FC(layer);
    //double b_value_layer = SoilProfileRef.b_Value[layer];                  //soil.properties.hydraulics.get_Campbell_b(layer,false);
      // RLN Warning I am not sure Saturation_Water_Contentto use the specifically calculated b_value
      // or the one from parameters.
            //(CORN_ln(1500.0) - CORN_ln(-water_pot_at_FC_layer) )/ (CORN_ln(FC_layer / WC_sat_layer) - CORN_ln(PWP_layer / WC_sat_layer));
    double m_layer = SoilProfileRef.m_Value[layer];//2.0 * b_value_layer + 3.0;
    double one_minus_m_layer = 1.0 - m_layer;
    double m_minus_one_layer = m_layer - 1.0;
    //double hours_to_field_capacity_layer = hours_to_field_capacity[layer];
#ifdef MSVB_CASCADE_INFILTRATION_HOUR
//140429 RLN this should eventually be replaced by Roger's code
// RLN actually I think this whole function is obsolete
    double apparent_K_sat_layer = SoilProfileRef.Apparent_K_Sat[layer];
#endif
    double dhvwc = tvwc
                   - pow(pow(tvwc,one_minus_m_layer)
                         + (standard_gravity * apparent_K_sat_layer * m_minus_one_layer * timestep_s)
                           / (thickness_layer * WaterDensity_kg_m3 * pow(WC_sat_layer, m_layer))
                        ,(1.0 / one_minus_m_layer)); //Need validate the equation
    if (dhvwc < 0) dhvwc = 0;
    return dhvwc;
};
#endif
*/
//______________________________________________________________________________
//#ifdef MBVB_INFILTRATION
//void SoilProcessesClass::FDVerticalFlow(const CORN::Date today,const double avw_mm,const double t_start,const double t_length)
//{
//}
//#endif
//______________________________________________________________________________
/*140507RLN  printState is not used anywhere,
furthermore, vwc is never provided
void SoilProcessesClass::printState()
{
    std::clog<<"------Soil State in soil process:-----\n";
    for (int layer = 1; layer <= SoilStateRef.getSoilLayers() ; layer++) {
        std::clog<<" Layer:"<<layer<<"\tVWC:"<<vwc[layer]
                   //<<"\tZ_f:"<<Wetting_Front_Depth
                   //<<"\tK_sat_min:"<<Minimum_Saturated_Hydraulic_Conductivity
                   //<<"\tPsi_t:"<<Top_Water_Potential_m
                   //<<"\tInf:"<<Infiltration_Rate
                    <<std::endl;
    }
    std::clog<<"------End Soil State in soil process.-----\n";
}
*/
//______________________________________________________________________________
#if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_MANAGEMENT))
#else
void SoilProcessesClass::TillageEffectOnSoilProperties(clsManagement &Management)
{
    double Clay_Mass_Fraction[6];
    double Sand_Mass_Fraction[6];
    double Nitrate_Content[6];
    double Ammonium_Content[6];
    double Phosphorus_Content[6];

    double New_Clay_Fraction[6];
    double New_Sand_Fraction[6];
    double New_Nitrate_Content[6];
    double New_Ammonium_Content[6];
    double New_Phophorus_Content[6];

    double Soil_Layer_Thickness[6];
    double Layer_Bottom_Depth[6];   // meter

#ifdef CHECK_MASS_BALANCE
    BalanceItem bal_NO3,bal_NH4;
    bal_NO3.SetInitPool(SoilStateRef.getProfileNO3NMass());
    bal_NH4.SetInitPool(SoilStateRef.getProfileNH4NMass());
#endif
    //ROGER
    bool Tillage_Application = Management.pManagementState->Tillage_Event;
    if (Tillage_Application) {
        //Load tillage depth and mixing fraction
        double T_Mix = Management.pManagementState->Tillage_Mixing_Fraction;
        double T_Depth = Management.pManagementState->Tillage_Depth;
        int Last_Tilled_Layer = Management.pManagementState->Last_Layer_Tilled;
        //Retrieve mass-base contents.  All in unit of kg per kg of soil
        for (int layer = 1; layer <= Last_Tilled_Layer; layer++) {
            Layer_Soil_Mass[layer] = SoilProfileRef.get_bulk_density_g_cm3(layer)
                                     * SoilProfileRef.get_thickness_m(layer) * 1000;
                                     //in kg/m2. 1000 converts g/cm3 to kg/m3
            Clay_Mass_Fraction[layer] = SoilProfileRef.get_clay_percent(layer) / 100.0;
            Sand_Mass_Fraction[layer] = SoilProfileRef.get_sand_percent(layer) / 100.0;

            Nitrate_Content[layer] = SoilStateRef.Layer_Nitrate_N_Mass[layer] / Layer_Soil_Mass[layer];
            Ammonium_Content[layer] = SoilStateRef.Layer_Ammonium_N_Mass[layer] / Layer_Soil_Mass[layer];
            Phosphorus_Content[layer] = SoilStateRef.Layer_Phosphorus_Mass[layer] / Layer_Soil_Mass[layer];
            Layer_Bottom_Depth[layer] = SoilProfileRef.Layer_Bottom_Depth_m[layer];
            Soil_Layer_Thickness[layer] = SoilProfileRef.get_thickness_m(layer);
        }
        double Total_Soil_Mass_Mixed = 0;
        double Clay_Content_Mixed = 0;
        double Sand_Content_Mixed = 0;
        //Water_Content_Mixed = 0;
        double Nitrate_Content_Mixed = 0;
        double Ammonium_Content_Mixed = 0;
        double Phophorus_Content_Mixed = 0;
        for (int layer = 1; layer <= Last_Tilled_Layer; layer++) {
            if (Layer_Bottom_Depth[layer] <= T_Depth) {   // // tillage apply for the full depth of the layer
                Layer_Soil_Mass_Remaining_After_Tillage[layer] = (1 - T_Mix) * Layer_Soil_Mass[layer];
                Layer_Soil_Mass_Mixed_After_Tillage[layer] = Layer_Soil_Mass[layer] * T_Mix;
            }
            else if ((Layer_Bottom_Depth[layer] > T_Depth) && (Layer_Bottom_Depth[layer-1] < T_Depth)) {
                Layer_Soil_Mass_Mixed_After_Tillage[layer] = T_Mix * Layer_Soil_Mass[layer] * (T_Depth - Layer_Bottom_Depth[layer-1]) / Soil_Layer_Thickness[layer];  // // weights the mixing by the fraction of the layer affected by tillage
                Layer_Soil_Mass_Remaining_After_Tillage[layer] = Layer_Soil_Mass[layer] - Layer_Soil_Mass_Mixed_After_Tillage[layer];
            } else {   // // this else is redundant, as if (there is no tillage there is no mixing, keep it here for clarity
                Layer_Soil_Mass_Remaining_After_Tillage[layer] = Layer_Soil_Mass[layer];
                Layer_Soil_Mass_Mixed_After_Tillage[layer] = 0;
            }
            Clay_Content_Mixed = (Total_Soil_Mass_Mixed * Clay_Content_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer] * Clay_Mass_Fraction[layer])
                            / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer]);
            Sand_Content_Mixed = (Total_Soil_Mass_Mixed * Sand_Content_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer] * Sand_Mass_Fraction[layer])
                            / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer]);
            Nitrate_Content_Mixed = (Total_Soil_Mass_Mixed * Nitrate_Content_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer] * Nitrate_Content[layer])
                            / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer]);
            Ammonium_Content_Mixed = (Total_Soil_Mass_Mixed * Ammonium_Content_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer] * Ammonium_Content[layer])
                            / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer]);
            Phophorus_Content_Mixed = (Total_Soil_Mass_Mixed * Phophorus_Content_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer] * Phosphorus_Content[layer])
                            / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer]);
            Total_Soil_Mass_Mixed += Layer_Soil_Mass_Mixed_After_Tillage[layer];
        }

        for (int layer = 1; layer <= Last_Tilled_Layer; layer++) {
            New_Clay_Fraction[layer] = (Clay_Mass_Fraction[layer] * Layer_Soil_Mass_Remaining_After_Tillage[layer] + Clay_Content_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[layer])
                                        / Layer_Soil_Mass[layer];
            SoilProfileRef.horizon_clay[layer] = New_Clay_Fraction[layer] * 100;
            New_Sand_Fraction[layer] = (Sand_Mass_Fraction[layer] * Layer_Soil_Mass_Remaining_After_Tillage[layer] + Sand_Content_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[layer])
                                        / Layer_Soil_Mass[layer];
            SoilProfileRef.horizon_sand[layer] = New_Sand_Fraction[layer] * 100;
            New_Nitrate_Content[layer] = (Nitrate_Content[layer] * Layer_Soil_Mass_Remaining_After_Tillage[layer] + Nitrate_Content_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[layer])
                                        / Layer_Soil_Mass[layer];
            SoilStateRef.Layer_Nitrate_N_Mass[layer] = New_Nitrate_Content[layer] * Layer_Soil_Mass[layer];
            assert(SoilStateRef.Layer_Nitrate_N_Mass[layer] >= 0.0);
            New_Ammonium_Content[layer] = (Ammonium_Content[layer] * Layer_Soil_Mass_Remaining_After_Tillage[layer] + Ammonium_Content_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[layer])
                                        / Layer_Soil_Mass[layer];
            SoilStateRef.Layer_Ammonium_N_Mass[layer] = New_Ammonium_Content[layer] * Layer_Soil_Mass[layer];
            assert(SoilStateRef.Layer_Ammonium_N_Mass[layer] >= 0.0);
            New_Phophorus_Content[layer] = (Phosphorus_Content[layer] * Layer_Soil_Mass_Remaining_After_Tillage[layer] + Phophorus_Content_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[layer])
                                        / Layer_Soil_Mass[layer];
            SoilStateRef.Layer_Phosphorus_Mass[layer] = New_Phophorus_Content[layer] * Layer_Soil_Mass[layer];
            assert(SoilStateRef.Layer_Phosphorus_Mass[layer] >= 0.0);
        }
    }
    #ifdef CHECK_MASS_BALANCE
    bal_NO3.SetFinalPool(SoilStateRef.getProfileNO3NMass());
    bal_NH4.SetFinalPool(SoilStateRef.getProfileNH4NMass());
    if (!bal_NO3.IsMassBalance()) bal_NO3.PrintMassBalanceTerms("NO3 during tillage");
    if (!bal_NH4.IsMassBalance()) bal_NH4.PrintMassBalanceTerms("NH4 during tillage");
    #endif
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
void SoilProcessesClass::DetermineSCSRunoff
(
#ifdef CROPSYST_PROPER_CROP
const CropSyst::Crop_interfaced &crop                                                      //140502
#else
clsCrop &crop
#endif
,clsSimulation &Simulation,clsManagement &Management
)
{
    //Calculate runoff using the SCS curve number approach
    //double Slope;
    static double Full_Crop_CN_I(0);
    static double Full_Crop_CN_II(0);
    static double Full_Crop_CN_III(0);
    static double Old_Crop_CN_I(0);
    static double Old_Crop_CN_II(0);
    static double Old_Crop_CN_III(0);
    static double Fallow_CN_I(0);
    static double Fallow_CN_II(0);
    static double Fallow_CN_III(0);
    static double Residue_CN_I_10Mg_per_Ha(0);
    static double Residue_CN_II_10Mg_per_Ha(0);
    static double Residue_CN_III_10Mg_per_Ha(0);
    double PAW[20];
    double Runoff_mm(0);                                                      //140221; //RS Runoff changed to Runoff_mm
    double Ponded_mm(0);
//RLN moved where used    double Hourly_Non_Intercepted_Rain = 0.0;                                    //140221 // FMS 10/16/2013
//RLN moved where used    double Hourly_Ponded = 0.0;                                                  //140221
    //double Hourly_Irrigation = 0.0;                                              //140221
//RLN moved wehre used    double Hourly_Snow_Melt = 0.0;                                               //140221
    //double Hourly_Runoff = 0.0;                                                  //140221
    static bool Initialized(false);
    if (Initialized == false) {
        Fallow_CN_I = SoilStateRef.Fallow_CN_I;
        Fallow_CN_II = SoilStateRef.Fallow_CN_II;
        Fallow_CN_III = SoilStateRef.Fallow_CN_III;
        Residue_CN_I_10Mg_per_Ha = SoilStateRef.Residue_CN_I_10Mg_per_Ha;
        Residue_CN_II_10Mg_per_Ha = SoilStateRef.Residue_CN_II_10Mg_per_Ha;
        Residue_CN_III_10Mg_per_Ha = SoilStateRef.Residue_CN_III_10Mg_per_Ha;
        Initialized = true;
    }
    //140214 unused DACE = Simulation.pTimeState->getDaysAfterCropExists();
    /*140214 UNUSED
    Year = Simulation.pTimeState->getToday().get_year();
    DOY = Simulation.pTimeState->getToday().get_DOY() ;
    */
    #ifndef CROPSYST_VERSION
    int DAGSS = Simulation.pTimeState->getDaysAfterGrowingSeasonStarted();
    bool Crop_Emerged = Simulation.pSimulationRotation->getCropEmerged();
    #endif
    bool Frozen(false);
    if (SoilStateRef.Ice_Content[2] > 0) {
        //assuming that topsoil layer is frozen when second layer starts building ice
        Frozen = true;
    }
    else Frozen = false;
    //Slope = 5  //in percent.  XXX This needs to be an input parameter
    #ifndef TRIVIAL_VERSION
    #ifdef CROPSYST_VERSION
    #else
    #ifndef CROPSYST_PROPER_CROP
    if (Crop_Emerged && DAGSS == 2) {
        std::string Hydrologic_Group = SoilStateRef.Hydrologic_Group;
        //Determine full grown crop curve number for given soil hydrologic group and antecedent rainfall condition II
        if (Hydrologic_Group.compare("A") == 0) Full_Crop_CN_II = crop.pCropParameters->Crop_CN_IIA;
        else if (Hydrologic_Group.compare("B") == 0) Full_Crop_CN_II = crop.pCropParameters->Crop_CN_IIB;
        else if (Hydrologic_Group.compare("C") == 0) Full_Crop_CN_II = crop.pCropParameters->Crop_CN_IIC;
        else if (Hydrologic_Group.compare("D") == 0) Full_Crop_CN_II = crop.pCropParameters->Crop_CN_IID;
        //Calculate full grown crop curve number for antecedent rainfall conditions I and III
        Full_Crop_CN_I = (0.00003 * pow(Full_Crop_CN_II,2) + 0.0032 * Full_Crop_CN_II + 0.3745) * Full_Crop_CN_II;
        Full_Crop_CN_III = (-0.5236 * log(Full_Crop_CN_II) + 3.4326) * Full_Crop_CN_II;
    }
    #endif
    #endif
    #endif
    //RS added ###########################################################################
    if (control.useHourlyRunoff()) {
        //calculate runoff hourly
        int HourOfDay = Simulation.pTimeState->getHourOfDay();   //0-23
        //Hourly_Non_Intercepted_Precip = HourlyNonInterceptedPrecipitation(Year, DOY, HourOfDay) // FMS 9/5/2013
        Hourly_Non_Intercepted_Rain_m = SnowRef.Hourly_Rain_mm[HourOfDay] / 1000.0; //FMS 10/16/2013
        #ifdef CROPSYST_PROPER_MANAGEMENT
        #else
        Hourly_Irrigation_m = Management.pManagementState->Irrigation_Amount / 24.0 / 1000.0;
        #endif
        //Hourly_Non_Intercepted_Precip = SoilStateRef.NonInterceptedPrecipitation(Year, DOY) / 24 //(mm)
        #ifndef CROPSYST_FD
        Hourly_Ponded_m = pond.get_depth();//SoilStateRef.Hourly_Ponded_Water_m; //(m)
        #endif
        SoilStateRef.Hourly_Irrigation_m = Hourly_Irrigation_m;
        Hourly_Snow_Melt_m = SnowRef.Hourly_Snow_Melt_Amount[HourOfDay] / 1000.0;
        double Hourly_Still_Running_Off(0);
        if (control.isInstantOverlandFLow()) {
            Hourly_Still_Running_Off = SoilStateRef.Hourly_Runoff_m * 1000.0; //(mm ) water still running off the gridcell
        } else {
            //runoff is removed immediately in single-cell mode
            Hourly_Still_Running_Off = 0;
        }
        //Amount of water that may(!) infiltrate into the soil (mm)
        //Hourly_Water_In = Hourly_Non_Intercepted_Precip + Hourly_Ponded + Hourly_Still_Running_Off _
        //                      + Hourly_Irrigation + Hourly_Snow_Melt
        Hourly_Water_In_m = Hourly_Non_Intercepted_Rain_m + Hourly_Ponded_m + Hourly_Still_Running_Off/1000.0
                          + Hourly_Irrigation_m + Hourly_Snow_Melt_m;
        //hand over to variable that is later-on used in the original code
        Water_In = Hourly_Water_In_m * 1000.0;     //(mm)
        //calculate new concentration of water on top of the soil, before runoff and infiltration is calculated
        //units are Layer_Nitrate_N_Conc (kg/m3), IrrigationNO3Conc (kg/m3), all others (mm)
        if (CORN::is_approximately<double>(Hourly_Water_In_m,0.0,1e-12)) {
            SoilStateRef.Layer_Nitrate_N_Conc[0] = 0;
            SoilStateRef.Layer_Ammonium_N_Conc[0] = 0;
        } else {
            SoilStateRef.Layer_Nitrate_N_Conc[0] =
            (SoilStateRef.Layer_Nitrate_N_Conc[0] * (Hourly_Ponded_m * 1000.0 + Hourly_Still_Running_Off)
            #ifndef CROPSYST_PROPER_MANAGEMENT
                + Hourly_Irrigation_m * 1000.0 * Management.pManagementState->Irrigation_NO3_Conc
            #endif
            )
                / (Hourly_Ponded_m * 1000.0 + Hourly_Still_Running_Off + Hourly_Irrigation_m * 1000.0
                   + Hourly_Non_Intercepted_Rain_m * 1000.0 + Hourly_Snow_Melt_m * 1000.0);
            SoilStateRef.Layer_Ammonium_N_Conc[0] =
            (SoilStateRef.Layer_Ammonium_N_Conc[0] * (Hourly_Ponded_m * 1000.0 + Hourly_Still_Running_Off)
                #ifndef CROPSYST_PROPER_MANAGEMENT
            + Hourly_Irrigation_m * 1000.0 * Management.pManagementState->Irrigation_NH4_Conc
            #endif
            )
                / (Hourly_Ponded_m * 1000.0 + Hourly_Still_Running_Off + Hourly_Irrigation_m * 1000.0
                   + Hourly_Non_Intercepted_Rain_m * 1000.0 + Hourly_Snow_Melt_m * 1000.0);
        }
        //just for balance calculations
      //140303 unused RNL check later LML
        Gross_Water_In_m = Hourly_Irrigation_m + Hourly_Non_Intercepted_Rain_m + Hourly_Snow_Melt_m;
        Cumulative_Gross_Water_In += Gross_Water_In_m;
    } else {
        //calculate runoff on a daily basis
        Ponded_mm = SoilStateRef.Daily_Ponded_Water;
        double Non_Intercepted_Rain(0);
      #ifdef CROPSYST_WEATHER
      Non_Intercepted_Rain = precipitation.mm();                               //140219
        #else
        #ifndef CROPSYST_PROPER_MANAGEMENT
        double Irrigation_mm = Management.pManagementState->Irrigation_Amount;
        #endif
        //if (Irrigation_mm > 0) { Stop
        double SnowMelt_mm = SnowRef.Daily_Snow_Melt_Amount_m * 1000.0;
        double Non_Intercepted_Precipitation(0);        //TODO (LML) 150114
        //    Non_Intercepted_Precipitation = SoilStateRef.NonInterceptedPrecipitation(Year, DOY)
        Non_Intercepted_Rain = SnowRef.Daily_Rain_mm; // FMS 10/16/2013
      #endif
        //    //RS new: Water prone to runoff includes now all sources
        //    Water_In = Ponded_mm + Irrigation_mm + Non_Intercepted_Precipitation + SnowMelt_mm
        Water_In = Ponded_mm + Irrigation_mm + Non_Intercepted_Rain + SnowMelt_mm;
        //calculate new concentration of water on top of the soil, before runoff and infiltration is calculated
        //units are Layer_Nitrate_N_Conc (kg/m3), IrrigationNO3Conc (kg/m3), all others (mm)
        if (CORN::is_approximately<double>(Water_In,0.0,1e-12)) {
            SoilStateRef.Layer_Nitrate_N_Conc[0] = 0;
            SoilStateRef.Layer_Ammonium_N_Conc[0] = 0;
        } else {
            SoilStateRef.Layer_Nitrate_N_Conc[0] =
            (SoilStateRef.Layer_Nitrate_N_Conc[0] * (Ponded_mm)
                #ifndef CROPSYST_PROPER_MANAGEMENT
            + Irrigation_mm * Management.pManagementState->Irrigation_NO3_Conc
            #endif
            )
                / (Ponded_mm + Irrigation_mm + Non_Intercepted_Precipitation + SnowMelt_mm);

            SoilStateRef.Layer_Ammonium_N_Conc[0] =
            (SoilStateRef.Layer_Ammonium_N_Conc[0] * (Ponded_mm)
                #ifndef CROPSYST_PROPER_MANAGEMENT
            + Irrigation_mm * Management.pManagementState->Irrigation_NH4_Conc
                #endif
            )
                / (Ponded_mm + Irrigation_mm + Non_Intercepted_Precipitation + SnowMelt_mm);
        }

        //just for balance calculations
        Gross_Water_In_m = mm_to_m(Irrigation_mm + Non_Intercepted_Precipitation) + Hourly_Snow_Melt_m;
        Cumulative_Gross_Water_In += Gross_Water_In_m;
    }
    //end added###########################################################################
    //************ Calculate runoff if (non intercepted precipitation is greater than zero
     //Non_Intercepted_Precipitation = SoilStateRef.NonInterceptedPrecipitation(Year, DOY)
    if (CORN::is_approximately<double>(Water_In,0.0,1e-12)) { //RS: Non_Intercepted_Precipitation replaced throughout procedure by Water_In
        Runoff_mm = 0;
    } else {
        double Fraction_Canopy_Interception(0);
        double Surface_Residue_Mass(0);
        #ifndef CROPSYST_VERSION
        #ifndef CROPSYST_PROPER_CROP
        if (Crop_Emerged)
            Fraction_Canopy_Interception = crop.pCropState->Yesterday_Fraction_Solar_Rad_Intercepted_Green_Canopy;
        #endif
        #endif
        double Top_Layer_Water_Content = SoilStateRef.get_liquid_water_content_volumetric(1)/*Water_Content[1]*/;
        double Top_Layer_Field_Capacity = SoilProfileRef.get_field_capacity_volumetric(1);
        const int Number_Of_Layers = Num_Soil_Layers;
        for (int layer = 1; layer <= Number_Of_Layers; layer++) {
            PAW[layer] = (SoilStateRef.get_liquid_water_content_volumetric(layer) - SoilProfileRef.get_permanent_wilt_point_volumetric(layer))
                / (SoilProfileRef.get_field_capacity_volumetric(layer) - SoilProfileRef.get_permanent_wilt_point_volumetric(layer));
            if (PAW[layer] > 1) PAW[layer] = 1;
            if (PAW[layer] < 0) PAW[layer] = 0;
            Layer_Thickness[layer] = SoilProfileRef.get_thickness_m(layer);
        }//Next L
        #ifndef CROPSYST_VERSION
    //This prorates CN between bare soil and crop cover based on fraction of interception
        double Crop_CN_I(0),Crop_CN_II(0),Crop_CN_III(0);
        if (Crop_Emerged) {
            if (Fraction_Canopy_Interception < 0.85) {
               Crop_CN_I = Fallow_CN_I - (Fallow_CN_I - Full_Crop_CN_I) * Fraction_Canopy_Interception / 0.85;
               Crop_CN_II = Fallow_CN_II - (Fallow_CN_II - Full_Crop_CN_II) * Fraction_Canopy_Interception / 0.85;
               Crop_CN_III = Fallow_CN_III - (Fallow_CN_III - Full_Crop_CN_III) * Fraction_Canopy_Interception / 0.85;
            } else {
                Crop_CN_I = Full_Crop_CN_I;
                Crop_CN_II = Full_Crop_CN_II;
                Crop_CN_III = Full_Crop_CN_III;
            }
            //Check that crop CN does not increase once the canopy start senescing
            if (Crop_CN_I > Old_Crop_CN_I) Crop_CN_I = Old_Crop_CN_I;
            if (Crop_CN_II > Old_Crop_CN_II) Crop_CN_II = Old_Crop_CN_II;
            if (Crop_CN_III > Old_Crop_CN_III) Crop_CN_III = Old_Crop_CN_III;
            Old_Crop_CN_I = Crop_CN_I;
            Old_Crop_CN_II = Crop_CN_II;
            Old_Crop_CN_III = Crop_CN_III;
        } else {
            Crop_CN_I = Fallow_CN_I;
            Crop_CN_II = Fallow_CN_II;
            Crop_CN_III = Fallow_CN_III;
            Old_Crop_CN_I = Fallow_CN_I;
            Old_Crop_CN_II = Fallow_CN_II;
            Old_Crop_CN_III = Fallow_CN_III;
        }
        //This prorates CN between bare soil and residue covered soil based on the mass of residue present (10 ton/ha provides minimum CN)
        double Residue_CN_I(0),Residue_CN_II(0),Residue_CN_III(0);
        if (Surface_Residue_Mass > 1) {
            Residue_CN_I = Residue_CN_I_10Mg_per_Ha;
            Residue_CN_II = Residue_CN_II_10Mg_per_Ha;
            Residue_CN_III = Residue_CN_III_10Mg_per_Ha;
        } else {
            Residue_CN_I = Fallow_CN_I - (Fallow_CN_I - Residue_CN_I_10Mg_per_Ha) * Surface_Residue_Mass;
            Residue_CN_II = Fallow_CN_II - (Fallow_CN_II - Residue_CN_II_10Mg_per_Ha) * Surface_Residue_Mass;
            Residue_CN_III = Fallow_CN_III - (Fallow_CN_III - Residue_CN_III_10Mg_per_Ha) * Surface_Residue_Mass;
        }
        double CN_I(0),CN_II(0),CN_III(0);
        if (Surface_Residue_Mass > 0) {
            if (Crop_Emerged) {
             //This prorates CN when crops and residues co-exist
                if (Surface_Residue_Mass < 1) {
                    CN_I = Crop_CN_I - (Crop_CN_I - Residue_CN_I_10Mg_per_Ha) * Surface_Residue_Mass;
                    CN_II = Crop_CN_II - (Crop_CN_II - Residue_CN_II_10Mg_per_Ha) * Surface_Residue_Mass;
                    CN_III = Crop_CN_III - (Crop_CN_III - Residue_CN_III_10Mg_per_Ha) * Surface_Residue_Mass;
                } else {
                    CN_I = Residue_CN_I_10Mg_per_Ha;
                    CN_II = Residue_CN_II_10Mg_per_Ha;
                    CN_III = Residue_CN_III_10Mg_per_Ha;
                }
                if (CN_I > Crop_CN_I) CN_I = Crop_CN_I;
                if (CN_I < Residue_CN_I_10Mg_per_Ha) CN_I = Residue_CN_I_10Mg_per_Ha;

                if (CN_II > Crop_CN_II) CN_II = Crop_CN_II;
                if (CN_II < Residue_CN_II_10Mg_per_Ha) {
                    CN_II = Residue_CN_II_10Mg_per_Ha;
                    if (CN_III > Crop_CN_III) CN_III = Crop_CN_III;
                    if (CN_III < Residue_CN_III_10Mg_per_Ha) CN_III = Residue_CN_III_10Mg_per_Ha;
                } else {
                    CN_I = Residue_CN_I;
                    CN_II = Residue_CN_II;
                    CN_III = Residue_CN_III;
                }
            } else {
                if (Crop_Emerged) {
                    CN_I = Crop_CN_I;
                    CN_II = Crop_CN_II;
                    CN_III = Crop_CN_III;
                } else {
                    CN_I = Fallow_CN_I;
                    CN_II = Fallow_CN_II;
                    CN_III = Fallow_CN_III;
                }
            }
            //This corrects curve number for the effect of frozen soil. This applies to cascade water transport
            if (Frozen) {
                CN_I += (100 - CN_I) * Top_Layer_Water_Content / Top_Layer_Field_Capacity;
                CN_II += (100 - CN_II) * Top_Layer_Water_Content / Top_Layer_Field_Capacity;
                CN_III += (100 - CN_III) * Top_Layer_Water_Content / Top_Layer_Field_Capacity;
            }
            //Calculate surface storage for each moisture antecedent condition
            double Surface_Storage_I = CalculateSurfaceStorage(CN_I);
            double Surface_Storage_II = CalculateSurfaceStorage(CN_II);
            double Surface_Storage_III = CalculateSurfaceStorage(CN_III);
            //Calculate shape parameters and FFC following J.R. Williams (EPIC)
            double Shape_Param2 = 2. * (log(fabs(0.5 / (1. - (Surface_Storage_II / Surface_Storage_I))))
                    - 0.5 - log(1. / (1. - (Surface_Storage_III / Surface_Storage_I)) - 1.));
            double Shape_Param1 = log(1. / (1. - (Surface_Storage_III / Surface_Storage_I)) - 1.) + Shape_Param2;
            #endif
            int layer = 1;
            double Depth = Layer_Thickness[layer];
            double Sum_Layer_Weight = 0;
            double Weighted_PAW = 0;
            while (Depth < 1.0 && layer < Number_Of_Layers) {
                double Layer_Weight = Layer_Thickness[layer] / Depth;
                Sum_Layer_Weight += Layer_Weight;
                Weighted_PAW += Layer_Weight * PAW[layer];
                layer++;
                Depth += Layer_Thickness[layer];
            };
            double PAW_Factor = Weighted_PAW / Sum_Layer_Weight;
            //Calculate weighted surface storage based on antecedent moisture conditions I, II, and III
            double weighted_Surface_Storage = Surface_Storage_I * (1. - (PAW_Factor / (PAW_Factor
                                              + exp(Shape_Param1 - Shape_Param2 * PAW_Factor))));
            //Calculate runoff
            if (Water_In <= (0.2 * weighted_Surface_Storage)) {
                Ponded_mm = 0; //RS: Runoff replaced by Ponded_mm
            } else {
                Ponded_mm = pow((Water_In - 0.2 * weighted_Surface_Storage),2)
                            / (Water_In + 0.8 * weighted_Surface_Storage);
                if (Ponded_mm > Water_In) Ponded_mm = Water_In;
            }
            //RS added----------------------------------
            double Surface_Store = SoilStateRef.Surface_Storage; //(mm)
            if (Ponded_mm > Surface_Store) {
                Runoff_mm = Ponded_mm - Surface_Store;
                Ponded_mm = Surface_Store;
            } else {
                Runoff_mm = 0;
            }
            Water_In -= (Ponded_mm + Runoff_mm);
            Hourly_Water_In_m = Water_In / 1000.0;
            //end added---------------------------------
        } //end Surface_Residue_Mass > 0
            //RS added
        if (control.useHourlyRunoff()) {
        SoilStateRef.Hourly_Runoff_m = Runoff_mm/1000.0;
        #ifndef CROPSYST_FD
        //SoilStateRef.Hourly_Ponded_Water_m = Ponded_mm/1000.0;
        pond.set_depth(Ponded_mm/1000.0);
        #endif
        SoilStateRef.Daily_Runoff_m += Runoff_mm/1000.0;
        SoilStateRef.Daily_Ponded_Water += Ponded_mm;
        SoilStateRef.Daily_Infiltration += Water_In;
        } else {
            SoilStateRef.Daily_Runoff_m = Runoff_mm/1000.0;
            SoilStateRef.Cumulative_Runoff += Runoff_mm;
            SoilStateRef.Daily_Ponded_Water = Ponded_mm;
            SoilStateRef.Daily_Infiltration = Water_In;
        }
        //end added
    }//End else   //TODO (Roger) LML 150105
}
//______________________________________________________________________________
#endif
#ifndef CROPSYST_VERSION
double SoilProcessesClass::CalculateSurfaceStorage(double Curve_Number)
{
    //Units: kg/m2 or mm
    return 25400. / Curve_Number - 254.;
}
//______________________________________________________________________________
#endif

//______________________________________________________________________________
#ifndef CROPSYST_FD
The following was inside bool SoilProcessesClass::performFD_InfiltrationAndTransport


    //double Actual_Flux;
    //int Day_Number;
    //double Drainage;  //(mm/s)
    double dt;
    //double FD_Water_Balance;
    //double Final_Soil_Water_Profile_Hourly; //FMS Feb 27, 2014
    //double FiniteDifferenceError;
    //double Flux;    //(mm/s)
    //double Flux_In_mm;
    //double Hourly_Drainage_mm; // (mm/h)
    double Hourly_Evaporation_mm;
    //double Hourly_Irrigation_mm;
    //double Hourly_Ponded;
    //double Hourly_Runoff_mm;
    //double Hourly_Snow_Melt;
    //double Hourly_Water_In;
    double Hourly_Water_In_FD;      //(m) FMS Mar 10, 2014
    //double Initial_Ponded;
    //double Initial_Runoff;
    //double Initial_Soil_Water_Profile_Hourly;
    //double Initial_sumdrain;
    //double Initial_sumrunoff;
    //double Intended_flux;
    int Maximum_Number_Of_Iterations;
    int NuL;
    int Number_Of_Iterations;
    //double Original_Ponded_Amount;
    double Storage_m;
    //double FWC;             //FMS Mar 11, 2014
    //int i;                  //FMS Mar 11, 2014
    //int NL;                 //FMS Mar 11, 2014
    dt = 3600.0;    //second
    NuL = Num_Soil_Layers;
    //RS: not sure what for initial and final soil water profile is needed; let's try without :-)
    #ifndef CROPSYST_FD
    #ifdef MBVB_FD
    Initial_Soil_Water_Profile_Hourly = SoilStateRef.calcFDProfileWater();      //(m) FMS Feb 27, 2014
    #endif
    #endif
    #endif


    // XXX CHECK OJO
    //Hourly_Non_Intercepted_Precip_mm = HourlyNonInterceptedPrecipitation(Year, DOY, HourOfDay) // FMS 9/5/2013
    //Hourly_Non_Intercepted_Precip_mm = SoilStateRef.NonInterceptedPrecipitation(Year, DOY) / 24
    //Hourly_Non_Intercepted_Rain_m = SnowRef.Hourly_Rain_mm[HourOfDay] / 1000.0; // FMS 10/16/2013
    //#ifndef CROPSYST_PROPER_MANAGEMENT
   //Hourly_Irrigation_m = Management.pManagementState->Irrigation_Amount / 24.0 / 1000.0;
    //#endif
    //Hourly_Snow_Melt_m = SnowRef.Hourly_Snow_Melt_Amount[HourOfDay] / 1000.0;
    //Hourly_Runoff_m = SoilStateRef.Hourly_Runoff_m;
    #ifndef CROPSYST_FD
    Hourly_Ponded_m = pond.get_depth();//SoilStateRef.Hourly_Ponded_Water_m;
    Hourly_Evaporation_mm = SoilStateRef.Daily_Soil_Water_Actual_Evaporation_m * 1000.0 / 24.0; //RS: OJO!!!
    Storage_m = mm_to_m(SoilProfileRef.SurfaceStorage);//SoilStateRef.Surface_Storage; M.Liu Mar 20 2014 Need Check!!!
    #endif
    //saving initial values in case FD-routine does not succeed //M.Liu deleted Mar 20, 2014
    //Initial_sumdrain = SoilStateRef.Daily_Drainage;
    //Initial_sumrunoff = SoilStateRef.Daily_Runoff;
    //Initial_Ponded = SoilStateRef.Hourly_Ponded_Water;
    //Initial_Runoff = SoilStateRef.Hourly_Runoff;
    //Initial_sumevap = Hourly_Evaporation_mm //RS: has no meaning as long as ETa isn//t calculated within this procedure
    //#ifndef CROPSYST_PROPER_MANAGEMENT
    //SoilStateRef.Sum_Solute_N_In += Hourly_Irrigation_m * Management.pManagementState->Irrigation_NO3_Conc +
    //                                    Hourly_Irrigation_m * Management.pManagementState->Irrigation_NH4_Conc +
    //                                    Management.pManagementState->Fertilization_NO3_N / 10000.0 / 24.0 +
    //                                    Management.pManagementState->Fertilization_NH4_N / 10000.0 / 24.0; //kg/ha  FMS  Mar 6, 2014
    //#endif

    #ifndef CROPSYST_FD
    Maximum_Number_Of_Iterations = 600; // This could be user defined
    Number_Of_Iterations = Maximum_Number_Of_Iterations; //that is, no need to iterate during first attempt for convergence //M.Liu changed Mar 20, 2014
    //140508 RLN obsolete unused Smaller_Time_Step = false;
    if (control.isDoSoilLaterFlow()/*LML 02192015 isDoSpatialSimulation()*/) //LML 021915 TODO need check!!!
        //runoff may not have run-off yet, or has run-on to neighboured cell where it is counted as runoff; OK I admit the terminology is odd...
        Hourly_Water_In_FD = Hourly_Non_Intercepted_Rain_m + Hourly_Irrigation_m + Hourly_Snow_Melt_m +
                             Hourly_Ponded_m + Hourly_Runoff_m;
    else
        //in single-cell mode runoff of previous hour is assumed to have run-off
        Hourly_Water_In_FD = Hourly_Non_Intercepted_Rain_m + Hourly_Irrigation_m + Hourly_Snow_Melt_m +
                             Hourly_Ponded_m;
    #endif
    #ifndef CROPSYST_FD
    #ifdef MBVB_FD
    Initial_Soil_Water_Profile_Hourly = SoilStateRef.calcFDProfileWater() * 1000; //FMS Feb 27, 2014
    //140509 RLN  Initial_Soil_Water_Profile_Hourly does not appear to be used
    #endif
    #endif
    //std::clog<<"Hourly_Water_In_FD:"<<Hourly_Water_In_FD<<std::endl;
    //for hourly water balance outputs
    //Hourly_Prec_Irrig_SnowMelt_m = Hourly_Non_Intercepted_Rain_m + Hourly_Irrigation_m + Hourly_Snow_Melt_m;
    //SoilStateRef.Hourly_Prec_Irrig_SnowMelt_m = Hourly_Prec_Irrig_SnowMelt_m;

    //just for balance calculations
    //Gross_Water_In_m = Hourly_Prec_Irrig_SnowMelt_m;
    //Cumulative_Gross_Water_In += Gross_Water_In;  //M.Liu Mar 20, 2014

    #ifdef MBVB_FD
    Success = false;
    do{ //RS: currently this Do-Loop is actually not required (see end of loop)!!!
       Number_Of_Iterations++;
       Flux = Hourly_Water_In_FD * 1000.0 / 3600.0; // (mm/s)
       Intended_flux = Flux;
       Drainage = 0;
       Hourly_Drainage_m = 0.0;
       Finite_Difference_Error_mm = 0;
       SaveSoilWaterStatus();
       Sat_BC = false;
       //Success = SolveLayerInf(HourOfDay, dt, Flux, Drainage, Hourly_Evaporation_mm, Sat_BC, Weather, FiniteDifferenceError);
       Success = SolveLayerInf(HourOfDay, dt, Flux, Drainage, Hourly_Evaporation_mm, Sat_BC,/* LML 14/05/07  Weather, */FiniteDifferenceError); //FiniteDifferenceError no use. M.Liu Mar 20, 2014
       if (Success) {
            Actual_Flux = Flux;
            Hourly_Ponded_m = std::max<double>((Intended_flux - Actual_Flux) * 3600,0.0) / 1000.0;
            //LML 15/05/14 removed the Hourly_runoff term and all ponded water will be routed in spatial overland flow process
            /*if (Hourly_Ponded_m > Storage_m) {
                Hourly_Runoff_m = Hourly_Ponded_m - Storage_m;
                Hourly_Ponded_m = Storage_m;
            }
            else*/ Hourly_Runoff_m = 0;
            Finite_Difference_Error_mm = FiniteDifferenceError * 3600;
            Flux_In_mm = Actual_Flux * 3600;
            Hourly_Drainage_m = Drainage * 3600.0 / 1000.0;
            Final_Soil_Water_Profile_Hourly = SoilStateRef.calcFDProfileWater();   //(m) FMS Feb 27, 2014
            #ifdef CHEMICAL_TRANSPORT
            #ifdef CROPSYST_VERSION
            /*
               pChemTransport->FDChemicalTransport(dt, "NO3");
               pChemTransport->FDChemicalTransport(dt, "NH4");
               pChemTransport->FDChemicalTransport(dt, "Phosp");
             */
            if (chemicals)                                                       //150812
            {

            RLN: need to provide the respective parameters 150812

               chemicals->chemical_transport_and_exchange                        //150812
                   (FINITE_DIFFERENCE_INFILTRATION
                   ,number_FD_solution_nodes // number_of_real_plus_extended_nodes
                   ,number_of_real_plus_extended_nodes
                   ,time_elapsed
                   ,time_step
                   ,old_water_depth_nodal
                   ,new_water_depth_nodal
                   ,actually_infiltrated_time_step
                   ,water_flow_nodal
                   ,deferment_fraction
                   ,false // not override_leaching_depth
                  ,0.0   // not override_leaching_depth
                   ,water_table_boundary_condition
                   );
            }
            #else
            if (Run_Chemical_Transport)
            {

               pChemTransport->FDChemicalTransport(dt, "NO3", Management,Simulation);
               pChemTransport->FDChemicalTransport(dt, "NH4", Management,Simulation);
               pChemTransport->FDChemicalTransport(dt, "Phosp", Management,Simulation);
            }
            #endif
            #endif

            //RS: Claudio, do you want to include "Salt" here as well?
            //#endif
            FWC = 0;     //FMS Mar 11, 2014
            //mode 1
            for (i = 1; i <= NuL; i++) {   //FMS Mar 11, 2014
                 FWC += ((SoilStateRef.New_Upper_Water_Content[i] * V_Upper[i] + SoilStateRef.New_Lower_Water_Content[i] * V_Lower[i])
                         / (V_Upper[i] + V_Lower[i])) * SoilProfileRef.Layer_Thickness_m[i] * 1000;    //FMS Mar 11, 2014
            }
        }
        else if (Intended_flux > 0) {
            //Switch to ponding
            Flux = 0;
            //Sat_BC = True ' FMS Mar 5, 2014 Change to True in SolveLayerInf
            //If HourOfDay = 6 Then Stop
            //Success = SolveLayerInf(HourOfDay, dt, Flux, Drainage, Hourly_Evaporation_mm, Sat_BC, Weather, FiniteDifferenceError);
            Success = SolveLayerInf(HourOfDay, dt, Flux, Drainage, Hourly_Evaporation_mm, Sat_BC,/* LML 14/05/07  Weather,*/ FiniteDifferenceError);
            if (Success) {
                Actual_Flux = Flux;
                Hourly_Ponded_m = std::max<double>((Intended_flux - Actual_Flux) * 3600,0.0) / 1000.0;
                if (Hourly_Ponded_m > Storage_m) {
                    Hourly_Runoff_m = Hourly_Ponded_m - Storage_m;
                    Hourly_Ponded_m = Storage_m;
                }
                else Hourly_Runoff_m = 0;
                Finite_Difference_Error_mm = FiniteDifferenceError * 3600.0;
                Flux_In_mm = Actual_Flux * 3600;
                //Hourly_Infiltration_m = Actual_Flux * 3600.0 / 1000.0;
                Hourly_Drainage_m = Drainage * 3600.0 / 1000.0;
                Final_Soil_Water_Profile_Hourly = SoilStateRef.calcFDProfileWater();      //FMS Feb 27, 2014
                #ifdef CROPSYST_CHEMICAL_TRANSPORT
                #ifdef CROPSYST_VERSION
                    /*150812
                    pChemTransport->FDChemicalTransport(dt, "NO3");
                    pChemTransport->FDChemicalTransport(dt, "NH4");
                    pChemTransport->FDChemicalTransport(dt, "Phosp");
                    */
                chemicals->chemical_transport_and_exchange                        //150812
                   (FINITE_DIFFERENCE_INFILTRATION
                   ,number_FD_solution_nodes // number_of_real_plus_extended_nodes
                   ,number_of_real_plus_extended_nodes
                   ,time_elapsed
                   ,time_step
                   ,old_water_depth_nodal
                   ,new_water_depth_nodal
                   ,actually_infiltrated_time_step
                   ,water_flow_nodal
                   ,deferment_fraction
                   ,override_leaching_depth
                   ,leaching_sublayer
                   ,water_table_boundary_condition
                   );
                #endif
                #else
                if (Run_Chemical_Transport) {
                    pChemTransport->FDChemicalTransport(dt, "NO3", Management,Simulation);
                    pChemTransport->FDChemicalTransport(dt, "NH4", Management,Simulation);
                    pChemTransport->FDChemicalTransport(dt, "Phosp", Management,Simulation);
                }
                    //RS: Claudio, do you want to include "Salt" here as well?
                #endif
                FWC = 0;     //FMS Mar 11, 2014
                //mode 2
                for (i = 1; i <= NuL; i++) {   //FMS Mar 11, 2014
                    FWC += ((SoilStateRef.New_Upper_Water_Content[i] * V_Upper[i] + SoilStateRef.New_Lower_Water_Content[i] * V_Lower[i])
                            / (V_Upper[i] + V_Lower[i])) * SoilProfileRef.Layer_Thickness_m[i] * 1000;    //FMS Mar 11, 2014
                }
            }
        }
    }while (!Success && Number_Of_Iterations < Maximum_Number_Of_Iterations);
    if (Success) {
        //write results into soil properties and add up for daily or cumulative quantities
        if (HourOfDay == 0) {
            SoilStateRef.Daily_Infiltration = Actual_Flux * dt / 1000.0;
        } else {
            SoilStateRef.Daily_Infiltration += Actual_Flux * dt / 1000.0;
        }
        FD_Water_Balance += Finite_Difference_Error_mm;

        SaveResultsVerticalFlow(HourOfDay,Hourly_Drainage_m, Hourly_Ponded_m + Hourly_Runoff_m, Hourly_Runoff_m, Hourly_Water_In_FD, Gross_Water_In_m);     //FMS Mar 10, 2014
        //SoilStateRef.Hourly_Ponded_Water_m = Hourly_Ponded_m;
        //SoilStateRef.Hourly_Runoff = Hourly_Runoff_mm;
        //SoilStateRef.Daily_Runoff += Hourly_Runoff_mm;
        //SoilStateRef.Hourly_Drainage_m = Hourly_Drainage_m;
        //SoilStateRef.Daily_Drainage_m += Hourly_Drainage_m; //New! saving cumul. drainage for daily output
        // SoilStateRef.Cumulative_Drainage += Hourly_Drainage_m * 1000.0;
        //Initial_Soil_Water_Profile = Final_Soil_Water_Profile
    }
    #endif  // MBVB_FD
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
double SoilProcessesClass::SDRDecay(double Water_Filled_Porosity)
{
    const double Decay_Rate = 0.1;
    return exp(-Decay_Rate * Water_Filled_Porosity);
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
double SoilProcessesClass::TillageIntensity(double Clay,double SDR)
{
    // this function computes EMPIRICALLY a multiplier for soil decomposition rate based on
    // tillage intensity and soil type for a single year
    // clay is expressed fractionally
    // SDR is the sum for the year of NRCS// Soil Disturbance Rating
    const double A_clay = 0.5; // the maximum (lots of tillage) multiplier in a 100% clay soil is (0.5 + 1)
    const double A_sand = 1.5; // the maximum multiplier in 100% sand soil is (1.5 + 1)
    const double k_clay = 5.5; // a curvature factor
    const double k_tillage = 1.0 / 40.0; // the curvature of the response to the Cumulative Soil Disturbance Rating for a single year
    double Term1 = A_clay + (A_sand - A_clay) * exp(-k_clay * Clay); // clay dependent term
    double Term2 = 1 - exp(-k_tillage * SDR); // SDR dependent term
    return Term1 * Term2;
}
#endif
//______________________________________________________________________________

#if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_MANAGEMENT))
#else
void SoilProcessesClass::DecompositionRateAdjustmentByTillage(clsManagement &Management)
{
    //double Residue_Fraction_Incorporated_Soil_Layer[5];
    //double Tillage_Multiplier;
    //double Daily_Decay_Rate;
    bool Tillage_Application = Management.pManagementState->Tillage_Event;
    int Last_Tilled_Layer = Management.pManagementState->Last_Layer_Tilled;
    for (int layer = 1; layer <= Last_Tilled_Layer; layer++) {
        double Soil_Disturbance_Rating = SoilStateRef.Soil_Disturbance_Rating[layer];
        if (Tillage_Application == true)
            Soil_Disturbance_Rating += Management.pManagementState->Tillage_Soil_Disturbance_Rate;
        else
            Soil_Disturbance_Rating *= SDRDecay(SoilStateRef.get_liquid_water_content_volumetric(layer) / SoilProfileRef.get_saturation_water_content_volumetric(layer,SoilStateRef.Ice_Content[layer]));
        SoilStateRef.Soil_Disturbance_Rating[layer] = Soil_Disturbance_Rating;
        double Tillage_Decomposition_Adjustment_Factor = 1 + TillageIntensity(SoilProfileRef.get_clay_percent(layer) / 100, Soil_Disturbance_Rating);
        SoilStateRef.Tillage_Decomposition_Adjustment_Factor[layer] = Tillage_Decomposition_Adjustment_Factor;
    }
    //Aqui
}
//______________________________________________________________________________
#endif
void SoilProcessesClass::TillageEffectOnWCHourly(clsManagement &Management)
{
#ifndef CROPSYST_VERSION
   #ifdef CROPSYST_PROPER_MANAGEMENT
    assert(false);  // CropSyst proper doesn't yet have tillage effect on WC
   #else
    //FMS Aug 20, 2014
    double Mass_Water_Content[6];   //(kg/kg soil)
    //double Fraction_Solar_Irradiance = Weather.getHourlyFractionOfSolarIrradiance(HourOfDay);      //FMS Aug 20, 2014
    bool Tillage_Application = Management.pManagementState->Tillage_Event;
    if (Tillage_Application) {
        //Load tillage depth and mixing fraction
        //const double T_Mix = Management.pManagementState->Tillage_Mixing_Fraction;
        //const double T_Depth = Management.pManagementState->Tillage_Depth;
        const int Last_Tilled_Layer = Management.pManagementState->Last_Layer_Tilled;
        //Retrieve mass-base contents.  All in unit of kg per kg of soil
        for (int layer = 1; layer <= Last_Tilled_Layer; layer++) {
            //Layer_Soil_Mass(L) = SoilProfileRef.BulkDensity(L) * SoilProfileRef.LayerThickness(L) * 1000 //in kg/m2. 1000 converts g/cm3 to kg/m3
            Mass_Water_Content[layer] = SoilStateRef.get_liquid_water_content_volumetric(layer)
                                        / SoilProfileRef.get_bulk_density_g_cm3(layer);     // [1000 (Water Density, kg/m3) / 1000 (convert g/cm3 to kg/m3)]
            //If L = 1 Then // FMS Aug 19, 2014
            //Mass_Water_Content(L) = SoilStateRef.TempWaterContent(Year, DOY) / SoilProfileRef.BulkDensity(L) // (convert g/cm3 to kg/m3)] // FMS Aug 19, 2014
            //Else
            //Mass_Water_Content(L) = SoilStateRef.WaterContent(Year, DOY, L) / SoilProfileRef.BulkDensity(L) // (convert g/cm3 to kg/m3)]// FMS Aug 19, 2014
            //End If
        }
        double Total_Soil_Mass_Mixed = 0;
        double Water_Content_Mixed = 0;
        for (int layer = 1; layer <= Last_Tilled_Layer; layer++) {
            //If Layer_Bottom_Depth(L) <= T_Depth Then // tillage apply for the full depth of the layer
            //Layer_Soil_Mass_Remaining_After_Tillage(L) = (1 - T_Mix) * Layer_Soil_Mass(L)
            //Layer_Soil_Mass_Mixed_After_Tillage(L) = Layer_Soil_Mass(L) * T_Mix
            //ElseIf Layer_Bottom_Depth(L) > T_Depth And Layer_Bottom_Depth(L - 1) < T_Depth Then
            //Layer_Soil_Mass_Mixed_After_Tillage(L) = T_Mix * Layer_Soil_Mass(L) * (T_Depth - Layer_Bottom_Depth(L - 1)) / Soil_Layer_Thickness(L) // weights the mixing by the fraction of the layer affected by tillage
            //Layer_Soil_Mass_Remaining_After_Tillage(L) = Layer_Soil_Mass(L) - Layer_Soil_Mass_Mixed_After_Tillage(L)
            //Else // this else is redundant, as if there is no tillage there is no mixing, keep it here for clarity
            //Layer_Soil_Mass_Remaining_After_Tillage(L) = Layer_Soil_Mass(L)
            //Layer_Soil_Mass_Mixed_After_Tillage(L) = 0
            //End If
            Water_Content_Mixed = (Total_Soil_Mass_Mixed * Water_Content_Mixed
                                   + Layer_Soil_Mass_Mixed_After_Tillage[layer] * Mass_Water_Content[layer]
                                  ) / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[layer]);
            Total_Soil_Mass_Mixed += Layer_Soil_Mass_Mixed_After_Tillage[layer];
        }
        for (int layer = 1; layer <= Last_Tilled_Layer; layer++) {
                double Old_Water_Content = SoilStateRef.get_liquid_water_content_volumetric(layer);
                double Delta_New_Water_Content =
                        (Mass_Water_Content[layer] * Layer_Soil_Mass_Remaining_After_Tillage[layer]
                         + Water_Content_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[layer]
                        ) / Layer_Soil_Mass[layer];
                Delta_New_Water_Content =
                        -(Old_Water_Content - Delta_New_Water_Content * SoilProfileRef.get_bulk_density_g_cm3(layer))
                        / 24.0;          //FMS Aug 20, 2014
                SoilStateRef.change_liquid_water_content_by_volumetric(layer,Delta_New_Water_Content);
                //SoilStateRef.HourlyWaterContent[layer] = New_Water_Content //FMS Aug 20, 2014
                //SoilStateRef.ChangeWCForTillage(Year, DOY, L) = SoilStateRef.WaterContent(Year, DOY, L) - New_Water_Content * SoilProfileRef.BulkDensity(L) // FMS Aug 19, 2014
        }
    }
   #endif
#endif
}
//______________________________________________________________________________

