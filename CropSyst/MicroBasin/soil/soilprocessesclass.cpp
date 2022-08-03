#ifdef MBVB_SOIL
#include "soilprocessesclass.h"
#include "soilstateclass.h"

#include "util/constants.h"
#include "util/pubtools.h"
//#include "corn/datetime/date.hpp"
#ifdef CROPSYST_VERSION
#include "soil/chemicals_profile.h"
//160801 #include "common/biometeorology/ET_reference_FAO.h"
#endif
#ifdef CROPSYST_PROPER_CROP
#include "crop/phenology_interface.h"
#endif
#include "control/allcontrolclass.h"
#include "math.h"
#include <algorithm>
#include "pond.h"

#include "common/physics/standard_constants.h"
#ifdef CHECK_MASS_BALANCE
#include "control/balanceitem.h"
#endif

//#define m_P_kPa  0.102
//______________________________________________________________________________
SoilProcessesClass::SoilProcessesClass
( SoilStateClass        &SoilStateRef_
, AllControlClass       &control_
, const CORN::Date_const/*170615LML _const_interface*/      &today_                  //150630RLN
, SoilProfileClass      &soilpf_
//160720RLN , modifiable_ Physical::Water_depth &evaporation_potential_remaining_            //160414RLN
,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining_      //160720RLN
//160808RLN #ifdef CROPSYST_WEATHER
//160808RLN ,const Precipitation    &precipitation_                                          //140218
//160808RLN #else
//160808RLN #endif
#ifdef MBVB_SNOW
,clsSnow                &SnowRef_
#endif
,CropSyst::Pond         &pond_                                                   //140606
,CropSyst::Soil_runoff  *runoff_
#if (defined(CHEMICAL_TRANSPORT) && defined(CROPSYST_VERSION))
,Soil_chemicals_profile *chemicals_ // 0 if not running chemicals
#endif
#ifdef CROPSYST_VERSION
//160801 ,ET_Reference_FAO       *ET_ref_
,const CS::Solar_irradiance_extraterrestrial/*160808RLN _hourly*/  &solar_irradiance_extraterrestrial_basin_ //160808RLN
,const Relative_humidity   &relative_humidity_min_ref_                           //151222
#endif
)
:SoilProfileRef                  (soilpf_)
,infiltration_cascade_hourly     (0)                                             //160722RLN
,infiltration_finite_difference  (0)                                             //160722RLN
,infiltration                    (0)                                             //160722RLN
//160722 ,evaporation_potential_remaining (evaporation_potential_remaining_)              //160414RLN
,evaporator                      (0)                                             //160722RLN
,control                         (control_)
,today                           (today_)                                        //150630
,SoilStateRef                    (SoilStateRef_)
//160808RLN #ifdef CROPSYST_WEATHER
//160808RLN ,precipitation                   (precipitation_)                                //140218
//160808RLN #endif
#ifdef MBVB_SNOW
,SnowRef                         (SnowRef_)
#endif
,pond                            (pond_)                                         //140606
#if (defined(CHEMICAL_TRANSPORT) && defined(CROPSYST_VERSION))
,chemicals_optional              (chemicals_)                                    //150812RLN
#endif
#ifndef CROPSYST_CHEMICAL_TRANSPORT
,pChemTransport_optional         (0)                                             //151212RLN
#endif
#ifdef CROPSYST_VERSION
//160801 ,ET_ref                          (ET_ref_)
,solar_irradiance_extraterrestrial_basin(solar_irradiance_extraterrestrial_basin_)
,relative_humidity_min_ref(relative_humidity_min_ref_)                           //151222RLN
#endif
{
    Num_Soil_Layers = SoilProfileRef.NumberOfLayers();
   #ifdef MBVB_INFILTRATION
    initMem();
    All_Hourly_Water_In = 0.0;                                                   //140417LML
   #endif

   // Always instanciate cascade because  if FD fails to converge cascade is used
   infiltration_cascade_hourly = new Soil_infiltration_cascade_hourly             //140423
              (soilpf_  // layers
              ,soilpf_ // texture
              ,soilpf_ // hydraulic properties
              ,*SoilStateRef_.hydrology
              ,runoff_ // NYI runoff  *_runoff
              ,SoilStateRef_.pond);

   if (control_.infiltration_model_labeled.get() == CASCADE_HOURLY_INFILTRATION) //150709
   {  infiltration = infiltration_cascade_hourly;
      evaporator =                                                               //160606RLN
         new Evaporator_soil
            (evaporation_potential_remaining_
            ,soilpf_ //layers
            ,soilpf_ // hydraulic properties
            ,*SoilStateRef_.hydrology_cascade);
    }
    else
    {
      Soil_evaporation_without_vapor_path *evaporator_WO_vapor_path =            //160606RLN
         new Soil_evaporation_without_vapor_path
            (evaporation_potential_remaining_
            ,soilpf_ //layers
            ,&soilpf_ // hydraulic properties
            ,*SoilStateRef_.hydrology_FD);
      evaporator = evaporator_WO_vapor_path;
      infiltration = infiltration_finite_difference
        = new Soil_infiltration_finite_difference                                //140509
        (soilpf_
        ,soilpf_ // texture
        ,soilpf_ // hydraulic properties
        //160606RLN,SoilStateRef_.Daily_Soil_Water_Actual_Evaporation_m
        ,*evaporator_WO_vapor_path                                               //160606RLN
        //160414RLN obs ,SoilStateRef_.Daily_Soil_Water_Potential_Evaporation_m              //141005RLN
        /*160606RLN moved to evaporator
        ,evaporation_potential_remaining                                     //160414RLN
        */
        ,0 // NYI runoff  *_runoff
        ,SoilStateRef_.pond
        ,*SoilStateRef_.hydrology_FD
        ,relative_humidity_min_ref                                               //151220
        ,true ); // numerical_runoff_mode
    }

   /*160606RLN  This was always instanciating BOTH cascade and finite diff, instanciate on or the other
   #ifndef MSVB_CASCADE_INFILTRATION_HOUR
   infiltration_cascade_hourly = new Soil_infiltration_cascade_hourly         //140423
       (soilpf_  // layers
       ,soilpf_ // texture
       ,soilpf_ // hydraulic properties
       ,*SoilStateRef_.hydrology

       //160414RLN ,evaporation_
       ,runoff_ // NYI runoff  *_runoff
       ,SoilStateRef_.pond);
   #endif
   #ifdef CROPSYST_FD
    infiltration_finite_difference = new Soil_infiltration_finite_difference                                             //140509
        (soilpf_
        ,soilpf_ // texture
        ,soilpf_ // hydraulic properties
        ,SoilStateRef_.Daily_Soil_Water_Actual_Evaporation_m
        //160414RLN obs ,SoilStateRef_.Daily_Soil_Water_Potential_Evaporation_m              //141005RLN

        ,0 // NYI runoff  *_runoff
        ,SoilStateRef_.pond
        ,*SoilStateRef_.hydrology_FD
        ,relative_humidity_min_ref                                               //151220
        ,true ); // numerical_runoff_mode

   #endif
   #ifndef MBVB_FD
         infiltration =
            (control_.infiltration_model_labeled.get() == CASCADE_HOURLY_INFILTRATION) //150709
            ? (Soil_infiltration *) infiltration_cascade_hourly :
              (Soil_infiltration *) infiltration_finite_difference;
   #else
         infiltration = (Soil_infiltration *) infiltration_cascade_hourly;       //150530LML
   #endif

   */

    //for (int L = 0; L < num_layers; L++) {
        //m[layer] = SoilProfileRef.m_Value[layer];
        //b[layer] = SoilProfileRef.b_Value[layer];
        //dep[layer] = SoilProfileRef.Layer_Bottom_Depth[layer];
        //thick[layer] = SoilProfileRef.Layer_Thickness[layer];
        //vwc_fc[layer] = SoilProfileRef.vwc_fc[layer];
        //vwc_sat[layer] = SoilProfileRef.vwc_sat[layer];
        //K_Sat[layer] = SoilProfileRef.K_Sat[layer];
        //Psi_Air[layer] = SoilProfileRef.Psi_Air[layer];
        //Psi_fc[layer] = SoilProfileRef.Psi_fc[layer];
        //hr_fc[layer] = SoilProfileRef.Hours_To_Field_Capacity[layer];
        //Apparent_K_Sat[layer] = SoilProfileRef.Apparent_K_Sat[layer];
    //}
    //assignApparentKsat();
}
//______________________________________________________________________________
bool SoilProcessesClass::initialize()
{

   #ifdef MSVB_CASCADE_INFILTRATION_HOUR
   #else
   SoilProfileRef.initialize();       //Soil Profile
   SoilStateRef.initialize();
   if (infiltration)
       infiltration->initialize();                                                   //140527
   #endif
   #ifdef LIU_FD_RICHARD
   InitializeFDRichard();
   #endif
   return true;
}
//_2014-05-02_RLN__________________________________________________initialize__/
void SoilProcessesClass::setNumSoilLayers(int soil_num)
{
    Num_Soil_Layers = soil_num;
}
//______________________________________________________________________________

//______________________________________________________________________________
#ifdef MBVB_INFILTRATION
void SoilProcessesClass::initMem()
{
    //nat8 num_layers = soil.properties.layers.count();                                        //131126 RLN
    int nmax = SoilProfileRef.NumberOfLayers() + 5;
    b.resize(nmax,0);                         
    Jl.resize(nmax,0);                        
    KS.resize(nmax,0);                        
    N.resize(nmax,0);                         
    p.resize(nmax,0);                         
    pe.resize(nmax,0);                        
    Soil_Vapor_Conductance.resize(nmax,0);    
    wl.resize(nmax,0);                        
    wnl.resize(nmax,0);                       
    wnu.resize(nmax,0);                       
    WS.resize(nmax,0);                        
    wu.resize(nmax,0);                        
    z.resize(nmax,0);                         
    WC_ICE.resize(nmax,0);                    
    #ifdef MBVB_FD
    a.resize(nmax,0);                         
    bx.resize(nmax,0);                        
    C.resize(nmax,0);                         
    f.resize(nmax,0);                         
    dp.resize(nmax,0);                        
    cpu.resize(nmax,0);                       
    cpl.resize(nmax,0);                       
    DZ.resize(nmax,0);                        
    djdpu.resize(nmax,0);                     
    djdpl.resize(nmax,0);                     
    V_Lower.resize(nmax,0);                   
    V_Upper.resize(nmax,0);                   
    v.resize(nmax,0);                         
    SAT.resize(nmax,0);                       
    HalfLayer_Thickness.resize(nmax,0);       
    Minimum_K_sat.resize(nmax,0);             
    Initial_SavePot.resize(nmax,0);           
    Initial_Save_wu.resize(nmax,0);           
    Initial_Save_wl.resize(nmax,0);           
    #endif
    WC_Temp.resize(nmax,0);                  
    Air_Entry_Potential.resize(nmax,0);      
    b_Value.resize(nmax,0);                  
    m.resize(nmax,0);                        
    K_Sat.resize(nmax,0);                    
    Apparent_K_Sat.resize(nmax,0);           
    WC_Sat.resize(nmax,0);                   
    FC.resize(nmax,0);                       
    WPFC.resize(nmax,0);                     
    Water_Content.resize(nmax,0);            
    WC_Max.resize(nmax,0);                   
    Layer_Thickness.resize(nmax,0);          
    Soil_Depth.resize(nmax,0);               
    #ifdef MSVB_CASCADE_INFILTRATION_HOUR
    Hours_To_Field_Capacity.resize(nmax,0);  
    #endif
    Ponded_Initial.resize(25,0);             
    Ponded_Final.resize(25,0);
}
#endif
//______________________________________________________________________________
#ifdef MBVB_INFILTRATION
void SoilProcessesClass::clearMem()
{
    /*140507RLN  vwc is never used or calculated
    delete[] vwc;
    */
    #ifdef MSVB_CASCADE_INFILTRATION_HOUR
    // RLN obsolete
    //delete[] Hours_To_Field_Capacity;
    #endif
    //delete[] Ponded_Initial;
    //delete[] Ponded_Final;
#ifdef LIU_FD_RICHARD
    //M.Liu's method for FD soil moisture flow
    //delete[] fd_a;
    //delete[] fd_b;
    //delete[] fd_c;
    //delete[] fd_d;
    //delete[] fd_v;
    //delete[] fd_tempa;
    //delete[] fd_tempb;
    //delete[] fd_u;
    //delete[] fd_pu;
    //delete[] fd_K;
    //delete[] fd_CC;
    //delete[] fd_theta;
    //delete[] fd_soil_layer_index;
    //delete[] fd_pe;
    //delete[] fd_WS;
    //delete[] fd_WPW;
    //delete[] fd_KS;
    //delete[] fd_b_value;
    //delete[] fd_theta_b;
    //delete[] fd_thick;
    delete_2d_array<double>(fd_fraction,fd_nodes+2); //M.Liu an error occured. March 22, 2014
#endif

}
#endif
//______________________________________________________________________________

#ifdef MBVB_INFILTRATION
void SoilProcessesClass::initHourlyFluxes() // rename to start_hour
{
    //Hourly_Ponded = 0;
    //Hourly_Drainage = 0;
	//140303 RLN unused check later LML
    Hourly_Infiltration_Capacity_Limited_Runoff = 0; 
    Hourly_Excess_Infiltration_Runoff = 0;
    //LML 14/04/18
    Hourly_Non_Intercepted_Rain_m = 0.0;
    Hourly_Ponded_m = 0.0;
    Hourly_Irrigation_m = 0.0;
    Hourly_Snow_Melt_m = 0.0;
    Hourly_Drainage_m = 0.0;
    Hourly_Water_In_m = 0.0;
    Hourly_Runoff_m = 0.0;
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_WEATHER
void SoilProcessesClass::DetermineEffectivePrecipitation
(
WeatherStateDailyClass &Weather
#ifndef CROPSYST_VERSION
,clsSimulation          &Simulation
#ifdef CROPSYST_PROPER_CROP
,const CropSyst::Crop_interfaced &crop
#else
,clsCrop                &Crop
#endif
#else
,const double fraction_cover_total_canopy                                        //150909LML
#endif
)
{
    //Implement later M.Liu Feb 4, 2014
    //double Rain;
    //double Snow; // FMS 10/15/2013
    //double Canopy_Intercepted_Precipitation; //RS moved up
    //int Current_Year,year,doy,DACE;
    //int hour; //FMS 9/5/2013
    #ifndef CROPSYST_VERSION
    bool Crop_Emerged = Simulation.pSimulationRotation->getCropEmerged(); //RS changed, was: .CropExist
    #endif
    #ifdef WEATHER_PROVIDER_VERSION
    double Precipitation = Weather.daily_provider.precipitation_actual.get_mm(); //160414RLN_141222
    //printf("PPT(%f)\n",Precipitation);
    #else
    #error obsolete
    double Precipitation = Weather.getDailyPrecipitation_mm();
    #endif
    //Precipitation = DetermineSnowAndRainDaily(Current_Year, DOY, Weather)  //FMS add 10/07/2013 Determine if (Precipitation is Rain (or snow)
    // FMS this assumes that the snow is intercepted is available the same day it was intercepted by the crop
    //Rain = Weather.WeatherData.GetPrecipitation_mm(Current_Year, DOY) // FMS add 10/07/2013
    //Rain = SnowRef.DailyRainmm(DOY) //FMS 10/10/2013
    //
    //if (SnowIsInterceptedForCrop) { // FMS 10/15/2013
    //Snow = SnowRef.TotalSnowAmount(DOY)
    //Precipitation = Snow + Rain
    //Else
    //Precipitation = Rain
    //End If
    //
    double Fraction_Canopy_Interception = 0;
    double Full_Canopy_Rain_Interception_Capacity = 1; //Assumes that full canopy intercepts 1 kg/m2 = 1 mm of rain
    #ifndef CROPSYST_VERSION
    #ifndef CROPSYST_PROPER_CROP
    if (Crop_Emerged) 
        Fraction_Canopy_Interception = Crop.pCropState->Fraction_Solar_Rad_Intercepted_Total_Canopy;
    //150317RLN else    //RLN default already initalized above
    #endif
    #else
    Fraction_Canopy_Interception = fraction_cover_total_canopy;
    //std::clog<<"fraction_cover_total_canopy:"<<fraction_cover_total_canopy<<std::endl;
    #endif
    //150317RLN         Fraction_Canopy_Interception = 0; //RLN default already initalized above
    //Calculate precipitation intercepted by the crop canopy
    double Canopy_Intercepted_Precipitation =                                    //140303 RLN
    (Precipitation > Full_Canopy_Rain_Interception_Capacity * Fraction_Canopy_Interception)
         ? Full_Canopy_Rain_Interception_Capacity * Fraction_Canopy_Interception
         : Precipitation;
    double Non_Intercepted_Precipitation = CORN::must_be_0_or_greater<double>(Precipitation - Canopy_Intercepted_Precipitation); //160412RLN
    SoilStateRef.Non_Intercepted_Precipitation_mm = Non_Intercepted_Precipitation;
    SoilStateRef.output_daily_canopy_interception_water_mm = Canopy_Intercepted_Precipitation;
    #ifdef MBVB_SNOW
    SnowRef.Non_Intercepted_Precipitation = Non_Intercepted_Precipitation;       //131016FMS
    #else
    // Uses snow pack model provided by Land_unit_meteorological                 //160721RLN
    #endif
    //Call calHourlyNonInterceptedPrecipitation(Weather, Simulation, Crop, Non_Intercepted_Precipitation, Precipitation) //131007FMS
}
#endif
//______________________________________________________________________________
double SoilProcessesClass::CalculateMaximumWaterContentDuringInfiltration
(double Win,double KSat
,double AirEntryPotential,double bValue,double WCSat,int Time_Step)
{
    const double Gr = standard_gravity; //Gravitational constant in m/s2
    double N = 2.0 + 3.0 / bValue;
    double UnsaturatedConductivity = (Win * WaterDensity_kg_m3 / Time_Step) / Gr;
    double WaterPotential = AirEntryPotential / pow((UnsaturatedConductivity / KSat), (1.0 / N));
    double WCmax(0);
    if (WaterPotential >= AirEntryPotential) WCmax = WCSat;
    else WCmax = WCSat * pow((WaterPotential / AirEntryPotential), (-1.0 / bValue));
    return WCmax;
}
//______________________________________________________________________________
bool SoilProcessesClass::performFD_InfiltrationAndTransport
(bool Run_Chemical_Transport
,float64 eff_rain_m_ts
,float64 irrig_m_ts
,float64 runon_m_ts
,float64 &actually_infiltrated_time_step_m
,float64 &actually_evaporated_time_step_m_ts
,float64 &actually_balance_drainage_m_ts
,float64 &surface_runoff_m_ts
,float64 &error_FD_m_ts
)
{
    //Old name of this Sub in CropSystSMR.xlsm was: fddaystep()
    bool Success = false;
    int HourOfDay = control.hour;   //Simulation.pTimeState->getHourOfDay();  //0-23

    actually_infiltrated_time_step_m = 0.0;                              //140509 RLN
    actually_evaporated_time_step_m_ts = 0.0;                            //140509 RLN
    //actually_reported_drainage_m_ts = 0.0;
    actually_balance_drainage_m_ts = 0.0;
    #ifdef CHECK_MASS_BALANCE
    BalanceItem bal_totalwater;
    //bal_totalwater.SetFluxIn(Hourly_Non_Intercepted_Rain_m + Hourly_Snow_Melt_m + Hourly_Irrigation_m);
    bal_totalwater.SetInitPool(SoilStateRef.hydrology_FD->get_liquid_water_depth_profile());
    #endif
    Soil_infiltration_finite_difference::FD_status status =                      //140509RLN
      infiltration_finite_difference->                                           //140527
       infiltrate_and_transport_timestep
       ((Hour)HourOfDay
       ,eff_rain_m_ts//Hourly_Non_Intercepted_Rain_m + Hourly_Snow_Melt_m // eff_precip_interval
       ,irrig_m_ts//Hourly_Irrigation_m // irrigation_entering_this_time_step
       ,runon_m_ts//0 // not used by this model runon_interval
       // return values
       ,actually_infiltrated_time_step_m
       ,actually_evaporated_time_step_m_ts
       //,actually_reported_drainage_m_ts
       ,actually_balance_drainage_m_ts
       ,surface_runoff_m_ts);
    //if (Success) SoilStateRef.Daily_Infiltration += actually_infiltrated_time_step_m;         //140509 RLN
    // WARNING where to put actually_evaporated_time_step_m_ts?                  //140509 RLN
    Success = status == Soil_infiltration_finite_difference::CONVERGED;          //140527_140509 RLN
    error_FD_m_ts = infiltration_finite_difference                               //160606RLN
       ? infiltration_finite_difference->current_error_dt                        //141028LML
       : 99999;                                                                   //160606RLN
    #ifdef CHECK_MASS_BALANCE
    bal_totalwater.SetFluxIn(actually_infiltrated_time_step_m);
    bal_totalwater.SetFluxOut(actually_evaporated_time_step_m_ts + actually_balance_drainage_m_ts);
    bal_totalwater.SetFinalPool(SoilStateRef.hydrology_FD->get_liquid_water_depth_profile());
    if (!bal_totalwater.IsMassBalance())
        bal_totalwater.PrintMassBalanceTerms("total water during FD_infiltration");
    #endif
    return Success;
}
//______________________________________________________________________________
void SoilProcessesClass::PerformHourlyCascadeInfiltrationAndTransport
(
float64 eff_rain_m_ts
,float64 irrig_m_ts
,float64 runon_m_ts
,float64 &actually_infiltrated_time_step_m
,float64 &actually_balance_drainage_m_ts
,float64 &surface_runoff_m_ts
,float64 &balance_leached_NH4_N_kg_ts                                            //170417LML
,float64 &balance_leached_NO3_N_kg_ts                                            //170417LML
)
{
    #ifdef LIU_DEBUG
    double debug_new_water[20];
    double debug_old_water[20];
    #endif
    //float64 surface_out_flow = 0.0;               //(m/hr) LML 140829
    #ifdef CHECK_MASS_BALANCE
    BalanceItem bal_soilwater;
    BalanceItem bal_NO3;
    #endif
    int hour =
		#ifdef CROPSYST_VERSION
		control.hour; 
		#else
		Simulation.pTimeState->getHourOfDay();   //0-23
		#endif
    //Hourly_Non_Intercepted_Rain_m = SnowRef.Hourly_Rain_mm[hour] / 1000.0;               //(mm/h)
    //Hourly_Ponded_m = SoilStateRef.Hourly_Ponded_Water_m;//SheetOfWaterAvailableToInfiltrate_mm;          //(mm/h)
    //if (hour > 0)    //FMS Feb 19, 2014
    //Hourly_Ponded_m = pond.get_depth_m();//140606 SoilStateRef.Hourly_Ponded_Water_m;     //(m) 'FMS Jan 25, 2014 LML 14/04/18
    //SoilStateRef.Hourly_Ponded_Water_m = 0.0;                 //LML 14/04/24 all water has been processes
    //pond.set_depth(0.0);
    //else            //FMS Feb 19, 2014
        //Hourly_Ponded_m = SoilStateRef.Sheet_Of_Water_Available_To_Infiltrate_m;  //(m) //FMS Feb 19, 2014
    //#ifndef CROPSYST_PROPER_MANAGEMENT
	//Hourly_Irrigation_m = Management.pManagementState->Irrigation_Amount / 24.0 / 1000.0;    //(mm/h)
    //#endif
	//SoilStateRef.Hourly_Irrigation_m = Hourly_Irrigation_m;
    //Hourly_Snow_Melt_m = SnowRef.Hourly_Snow_Melt_Amount[hour] / 1000.0;                  //(mm/h)
    //Hourly_Water_In_m = Hourly_Non_Intercepted_Rain_m + Hourly_Ponded_m
    //        #ifndef CROPSYST_VERSION
	//		+ Hourly_Irrigation_m
	//		#endif
	//		+ Hourly_Snow_Melt_m; //(mm/h)
    //Hourly_Prec_Irrig_SnowMelt_m = Hourly_Non_Intercepted_Rain_m + Hourly_Irrigation_m + Hourly_Snow_Melt_m; //FMS 10/01/2013
    //SoilStateRef.Hourly_Prec_Irrig_SnowMelt_m = Hourly_Prec_Irrig_SnowMelt_m;       //LML 140917

    //For overall watershed balance calculations LML 14/04/17 moved here
    // Gross_Water_In_m =
    //         #ifndef CROPSYST_VERSION
    //         Hourly_Irrigation_m +
    //         #endif
    //         Hourly_Non_Intercepted_Rain_m + Hourly_Snow_Melt_m;
    //Cumulative_Gross_Water_In += Gross_Water_In_m;
    //kg/m2
    #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_MANAGEMENT))
    #else
    SoilStateRef.Sum_Solute_N_In += irrig_m_ts * Management.pManagementState->Irrigation_NO3_Conc +
                                        irrig_m_ts * Management.pManagementState->Irrigation_NH4_Conc +
                                        Management.pManagementState->Fertilization_NO3_N / 10000.0 / 24.0 +
                                        Management.pManagementState->Fertilization_NH4_N / 10000.0 / 24.0; // kg/ha * FMS  add 10/28/2013
    #endif
    for (nat8 layer = 1; layer <= Num_Soil_Layers; layer++)
    {  //140429 This save of old water content is temporary unit
        // CropSyst chemical transport is inserted
        SoilStateRef.Old_Water_Content[layer] = SoilStateRef.get_liquid_water_content_volumetric(layer);//Water_Content[layer];
        /*std::clog<<"Old_Water_Content L:"<<(int)layer<<" "<<SoilStateRef.Old_Water_Content[layer]
                 <<"\tice:"<<SoilStateRef.Ice_Content[layer]
                 <<std::endl;*/
        //DebugPrintVariable(__FILE__,__LINE__,"Old_Water_Content",SoilStateRef.Old_Water_Content[layer],layer);
        assert(SoilStateRef.Old_Water_Content[layer] >= 0.0);
        #ifdef LIU_DEBUG
        debug_old_water[layer] = SoilStateRef.Old_Water_Content[layer];
        #endif
        #ifdef CHECK_MASS_BALANCE
        bal_soilwater.AddInitPool(SoilStateRef.Old_Water_Content[layer] * SoilProfileRef.get_thickness_m(layer));
        #endif
    }
    #ifdef MSVB_CASCADE_INFILTRATION_HOUR
      //140423 This implementation of houly cascade inflitration will be obsolete. RLN
    DetermineHourlyWaterRedistribution(hour
            ,Hourly_Water_In_m
			#ifndef CROPSYST_VERSION
			, Management
			#endif
			);   //Hourly_Ponded_Water and soil moisture will be updated
    surface_out_flow += Hourly_Ponded_m;
    #else
    //surface_out_flow = 0.0;   //(m/T)
    //140603 #ifndef CROPSYST_HYDROLOGY
    //140527 Soil_infiltration_cascade_hourly::
    clear_layer_array64(infiltration_cascade_hourly->water_flow); //LML 140902 
    double originalKat_lastlayer;       //LML 141008 for none free drainage condition
    if (!SoilProfileRef.Free_Drainage_Boundary) {
        originalKat_lastlayer = SoilProfileRef.K_Sat[Num_Soil_Layers];
        SoilProfileRef.K_Sat[Num_Soil_Layers] = 0;
    }
    Hourly_Water_In_m = //160616LML eff_rain_m_ts + irrig_m_ts + runon_m_ts + SoilStateRef.pond.get_depth();
                        eff_rain_m_ts;
    //std::cerr << "Hourly_Water_In_m:" << Hourly_Water_In_m << std::endl;
    //160616LML SoilStateRef.pond.relinquish_depth();   //All pond water involed into infiltration
    /*****************************************************************
     * LML 141205 need update the aboveground nutrients concentration 
     * based on new total water depth
     * ***************************************************************/
    #ifdef CROPSYST_VERSION
    // CropSyst Proper currently doesn't have surface chemical, need to implement.
    //151027LML the following concentration is used for cascade_chemical transport.
    Soil_chemicals_profile *chemicals = SoilStateRef.chemicals_optional;         //151212
    double pond_NH4_conc = 0;                                                  //170418LML
    double pond_NO3_conc = 0;                                                  //170418LML
    double orig_pond_NH4_N = 0;                                                    //170419LML
    double orig_pond_NO3_N = 0;                                                    //170419LML
    if (chemicals)                                                               //151212
    { // Chemicals are optional in CropSyst
    double pond_NH4_N_kg_m2 = chemicals->get_NH4_N_mass_kg_m2(0);
    double pond_NO3_N_kg_m2 = chemicals->get_NO3_N_mass_kg_m2(0);
    //170418LML
    if (Hourly_Water_In_m <= 1e-12 && (pond_NH4_N_kg_m2 > 1e-12 || pond_NO3_N_kg_m2 > 1e-12)) {
        Hourly_Water_In_m = 0;
        chemicals->add_NH4_N_mass(1,pond_NH4_N_kg_m2);
        chemicals->add_NO3_N_mass(1,pond_NO3_N_kg_m2);
        chemicals->set_NH4_N_mass_kg_m2(0,0);
        chemicals->set_NO3_N_mass_kg_m2(0,0);
    } else if (Hourly_Water_In_m > 1e-12){
        pond_NH4_conc = (pond_NH4_N_kg_m2 * N_to_NH4_conv) / Hourly_Water_In_m;
        pond_NO3_conc = (pond_NO3_N_kg_m2 * N_to_NO3_conv) / Hourly_Water_In_m;
    }  //end 170418LML

    orig_pond_NH4_N = chemicals->get_NH4_N_mass_kg_m2(0);                        //170419LML
    orig_pond_NO3_N = chemicals->get_NO3_N_mass_kg_m2(0);                        //170419LML

    //chemicals->NH4->inc_applied_and_applied_irrig_soil_surface()

    /*std::clog << "Hourly_Water_In_m:" << Hourly_Water_In_m
              << "\tpond_NH4_N_kg_m2:" << pond_NH4_N_kg_m2
              << "\tpond_NO3_N_kg_m2:" << pond_NO3_N_kg_m2
              << "\torig_pond_NH4:" << orig_pond_NH4_N
              << "\torig_pond_NO3:" << orig_pond_NO3_N
              << std::endl;*/





#ifndef CROPSYST_CHEMICAL_TRANSPORT
    if (!is_approximately(Hourly_Water_In_m,0.0)) {
        SoilStateRef.Layer_Ammonium_N_Conc[0] = pond_NH4_N_kg_m2 / Hourly_Water_In_m;
        SoilStateRef.Layer_Nitrate_N_Conc[0] = pond_NO3_N_kg_m2 / Hourly_Water_In_m;
    } else {
        chemicals->add_NH4_N_mass(1,pond_NH4_N_kg_m2);
        chemicals->add_NO3_N_mass(1,pond_NO3_N_kg_m2);
        SoilStateRef.Layer_Ammonium_N_Conc[0] = 0.0;
        SoilStateRef.Layer_Nitrate_N_Conc[0]  = 0.0;
        chemicals->set_NH4_molecular_mass_kg_m2(0,0.0);
        chemicals->set_NO3_molecular_mass_kg_m2(0,0.0);
    }
#endif
    }
    /*if (SoilStateRef.Layer_Ammonium_N_Conc[0] > 0)
        std::clog<<"Layer_Ammonium_N_Conc[0]:"<<SoilStateRef.Layer_Ammonium_N_Conc[0]
             <<"\tHourly_Water_In_m:"<<Hourly_Water_In_m
             <<"\tpond_NH4_N_kg_m2:"<<pond_NH4_N_kg_m2
             <<std::endl;*/
    #else
    if (CORN::is_approximately<double>(Hourly_Water_In_m,0.0,1e-12)) {
        SoilStateRef.TransferNutrientsBetweenLayers(SL_Ammonia,1.0,0,1);
        SoilStateRef.TransferNutrientsBetweenLayers(SL_Nitrate,1.0,0,1);
        SoilStateRef.TransferNutrientsBetweenLayers(SL_Phosphate,1.0,0,1);
        SoilStateRef.Layer_Ammonium_N_Conc[0] = 0.0;
        SoilStateRef.Layer_Nitrate_N_Conc[0] = 0.0;
        SoilStateRef.Layer_Phosphorus_Conc[0] = 0.0;
    } else {
        SoilStateRef.Layer_Ammonium_N_Conc[0] = SoilStateRef.Layer_Ammonium_N_Mass[0] / Hourly_Water_In_m;
        SoilStateRef.Layer_Nitrate_N_Conc[0] = SoilStateRef.Layer_Nitrate_N_Mass[0] / Hourly_Water_In_m;
        SoilStateRef.Layer_Phosphorus_Conc[0] = SoilStateRef.Layer_Phosphorus_Mass[0] / Hourly_Water_In_m;
    }
    #endif
    surface_runoff_m_ts = 0.0;                                                 //LML 141031

    clear_layer_array64(infiltration_cascade_hourly->water_flow);
    //std::clog<<"DUBUG ONLY!!! hourly cascade infiltration!!!\n";


    #ifdef NO_INFILTRATION
    std::clog<<"NO INFILTRATION!!!\n";
    double test = Hourly_Water_In_m;//t
    Hourly_Water_In_m = 0;//t
    #endif
    infiltration_cascade_hourly->                                                //140527
      process_hour(hour,Hourly_Water_In_m,surface_runoff_m_ts);                  //140425RLN


    //std::clog << "surface_runoff_m_ts:" << surface_runoff_m_ts << std::endl;


    #ifdef NO_INFILTRATION
    surface_runoff_m_ts += test;//t
    Hourly_Water_In_m = test;//t
    #endif

    //160616LML SoilStateRef.pond.set_depth(surface_runoff_m_ts);
    if (!SoilProfileRef.Free_Drainage_Boundary) {
        SoilProfileRef.K_Sat[Num_Soil_Layers] = originalKat_lastlayer;
    }

    //LML 140618 #ifdef MBVB_FD
    for (nat8 layer = 1; layer <= Num_Soil_Layers/*  soil_layers.count()*/; layer++)
    {  //140429 This save of new water content is temporary unit
        // CropSyst chemical transport is inserted
        SoilStateRef.New_Water_Content[layer] = SoilStateRef.get_liquid_water_content_volumetric(layer);//Water_Content[layer];
        assert(SoilStateRef.New_Water_Content[layer] >= 0.0);
        #ifdef LIU_DEBUG
        debug_new_water[layer] = SoilStateRef.New_Water_Content[layer];
        #endif
        #ifdef CHECK_MASS_BALANCE
        bal_soilwater.AddFinalPool(SoilStateRef.New_Water_Content[layer] * SoilProfileRef.get_thickness_m(layer));
        #endif
        #ifndef MSVB_CASCADE_INFILTRATION_HOUR
        SoilStateRef.Water_Flow[layer] = infiltration_cascade_hourly->water_flow[layer];
        if (layer == Num_Soil_Layers) Hourly_Drainage_m = infiltration_cascade_hourly->get_balance_drainage(); //140829_141204LML
        #endif
    }
    SoilStateRef.Water_Flow[0] = infiltration_cascade_hourly->water_flow[0];      //140911LML

    if (SoilStateRef.Water_Flow[0] < -1e-4)
        std::cerr << "Negtive water_flow[0]:" << SoilStateRef.Water_Flow[0] << "!\n";

    //pond.set_depth(surface_out_flow);       //LML 140813 add runoff water to pond
    #endif  //MSVB_CASCADE_INFILTRATION_HOUR
    #ifdef CHECK_MASS_BALANCE
    bal_soilwater.AddFluxIn(Hourly_Water_In_m);
    bal_soilwater.AddFluxOut(surface_runoff_m_ts+Hourly_Drainage_m);
    if (!bal_soilwater.IsMassBalance(1e-4)) {
        #pragma omp critical
        {
        bal_soilwater.PrintMassBalanceTerms("Soilwater during Cascade");
        std::clog<<" surface_runoff_m_ts:"<<surface_runoff_m_ts
                 <<" Hourly_Drainage_m:"<<Hourly_Drainage_m
                 <<std::endl;
        }
    }
    #endif
    //SaveResultsVerticalFlow(hour,Hourly_Drainage_m, Hourly_Ponded_m + Hourly_Runoff_m
    //                        , Hourly_Runoff_m, Hourly_Water_In_m, Gross_Water_In_m); //FMS Mar 10, 2014
    #ifdef CROPSYST_CHEMICAL_TRANSPORT
    #ifdef CROPSYST_VERSION
    if (chemicals)                                                               //151212_150812RLN
    {
        nat8 number_layers = SoilProfileRef.get_number_layers();     //150812RLN
        float64 precip_and_irrigation_hourly_m = Hourly_Water_In_m;  //150812RLN
        double original_acum_balanc_leached_NH4_N = chemicals->NH4->balance_leached_molecular * NH4_to_N_conv;
        double original_acum_balanc_leached_NO3_N = chemicals->NO3->balance_leached_molecular * NO3_to_N_conv;
        chemicals->chemical_transport_and_exchange                   //150812RLN
           (CASCADE_HOURLY_INFILTRATION
           ,number_layers
           ,number_layers // this parameter is dummy it is used only for F.D.
           ,3600*hour  // start time
           ,3600 // 1 hour duration
           ,SoilStateRef.Old_Water_Content         // 070813  Warning (I don't know if this should be only liquid water content or total water content - was liquid only)
           ,SoilStateRef.New_Water_Content   //070813_990311  Warning (I don't know if this should be only liquid water content or total water content - was liquid only)
           ,precip_and_irrigation_hourly_m
           ,SoilStateRef.Water_Flow
           ,0.0 // no deferment in cascade model
           ,false // not override_leaching_depth
//170425LML            ,pond_NH4_conc
//170425LML            ,pond_NO3_conc
           ,0.0   // not override_leaching_depth
           );
        balance_leached_NH4_N_kg_ts = chemicals->NH4->balance_leached_molecular * NH4_to_N_conv - original_acum_balanc_leached_NH4_N;  //170417LML
        balance_leached_NO3_N_kg_ts = chemicals->NO3->balance_leached_molecular * NO3_to_N_conv - original_acum_balanc_leached_NO3_N;  //170417LML
    } // if running chemicals
    #endif
    #else
    /*std::clog<<"BEFORE CascadeChemicalTransport:"
             <<"\thour:"<<control.hour
             <<"\tcell:"<<SnowRef.RefGridID
             <<"\tamount[NH4][layer=0]:"<<chemicals->get_NH4_molecular_mass_kg_m2(0)
             <<"\tamount[NO3][layer=0]:"<<chemicals->get_NO3_molecular_mass_kg_m2(0)
             <<std::endl;*/
    if (pChemTransport_optional)                                                          //151212RLN
    {
        pChemTransport_optional->CascadeChemicalTransport(hour, SL_Nitrate);
        pChemTransport_optional->CascadeChemicalTransport(hour, SL_Ammonia);
        pChemTransport_optional->CascadeChemicalTransport(hour, SL_Phosphate);
    }
    /*std::clog<<"AFTER CascadeChemicalTransport:"
             <<"\thour:"<<control.hour
             <<"\tcell:"<<SnowRef.RefGridID
             <<"\tamount[NH4][layer=0]:"<<chemicals->get_NH4_molecular_mass_kg_m2(0)
             <<"\tamount[NO3][layer=0]:"<<chemicals->get_NO3_molecular_mass_kg_m2(0)
             <<std::endl;*/
    #endif
    actually_infiltrated_time_step_m = infiltration_cascade_hourly->water_flow[0];
    actually_balance_drainage_m_ts = Hourly_Drainage_m;  
    //actually_reported_drainage_m_ts = Hourly_Drainage_m;


    //170418LML
    //170425LML chemicals->set_NH4_N_mass_kg_m2(0,orig_pond_NH4_N);
    //170425LML chemicals->set_NO3_N_mass_kg_m2(0, orig_pond_NO3_N);
    //170425LML double infiltrated_NH4 = actually_infiltrated_time_step_m * pond_NH4_conc;
    //170425LML double infiltrated_NO3 = actually_infiltrated_time_step_m * pond_NO3_conc;
    //170425LML chemicals->subtract_NH4_molecular_mass(0,infiltrated_NH4);
    //170425LML chemicals->subtract_NO3_molecular_mass(0,infiltrated_NO3);

    /*std::clog << "actually_infiltrated_time_step_m:" << actually_infiltrated_time_step_m
              << "infiltrated_NH4_N:" << infiltrated_NH4 * NH4_to_N_conv
              << "infiltrated_NO3_N:" << infiltrated_NO3 * NO3_to_N_conv
              << std::endl;*/

    //end 170418LML
}
//______________________________________________________________________________
SoilProcessesClass::~SoilProcessesClass()
{
   #ifdef Destruct_Monitor
    std::clog<<"~SoilProcessesClass:"<<std::endl;
   #endif
   #ifdef MBVB_INFILTRATION
    clearMem();
   #endif
   #ifdef CROPSYST_FD
    delete infiltration_finite_difference;
   #endif
   #ifndef MSVB_CASCADE_INFILTRATION_HOUR
    delete infiltration_cascade_hourly;
   #endif
   #ifdef Destruct_Monitor
    std::clog<<"~SoilProcessesClass done."<<std::endl;
   #endif
}
//______________________________________________________________________________
#ifdef MBVB_INFILTRATION
#ifdef CHEMICAL_TRANSPORT
double SoilProcessesClass::getFlow(int layer) {return Jl[layer];}
#endif
void SoilProcessesClass::DistributeExcessFlowUpwards(int tolayer,double &Excess_Flow_In,double &Sum_Ponded)
{
    //Sum_Ponded (m)
    //Excess_Flow_In (m)
    for (int layer = tolayer; layer >= 1; layer--) {
        if (layer == 1) {
            Sum_Ponded += Excess_Flow_In;
            Excess_Flow_In = 0; //FMS Jan 13, 2014
        } else {
            //Available_Porosity = (WC_Sat(L - 1) - Water_Content(L - 1)) * Layer_Thickness(L) //m //FMS Jan 9, 2014
            double Available_Porosity = (WC_Sat[layer-1] - Water_Content[layer-1]) 
                                        * Layer_Thickness[layer-1];
            if (Excess_Flow_In > Available_Porosity) {
                Water_Content[layer-1] = WC_Sat[layer-1];
                Excess_Flow_In -= Available_Porosity;
            } else {
                Water_Content[layer-1] += Excess_Flow_In / Layer_Thickness[layer-1];
                Excess_Flow_In = 0;
                layer = 1;
            }
        }
    }
}
#endif
//______________________________________________________________________________
void SoilProcessesClass::SaveResultsVerticalFlow(int hour, double hourly_drainage, double hourly_ponded
                        , double hourly_runoff, double hourly_water_in
                        , double gross_water_in)   //FMS Mar 10, 2014
{
    // New sub for save result by FD and Hourly Cascade
    // FMS Mar 10, 2014
    //LML 14/04/17 Question: is hourly_water_in is infiltrated water or total water in?
    //SoilStateRef.Hourly_Ponded_Water_m = hourly_ponded;     //(m)
    pond.set_depth(hourly_ponded);
    if (hour == 0) {
        SoilStateRef.Daily_Runoff_m = hourly_runoff;
        SoilStateRef.Daily_Drainage_m = hourly_drainage;       //(m)
    } else {
        SoilStateRef.Daily_Runoff_m += hourly_runoff;           //(m)
        SoilStateRef.Daily_Drainage_m += hourly_drainage;       //(m)
    }
    SoilStateRef.Hourly_Drainage_m = hourly_drainage;       //(m)
    SoilStateRef.Cumulative_Drainage += hourly_drainage;    //(m)
    control.debug.water_applied += hourly_water_in;               //(m)          //140114FMS
    control.debug.excess_water += hourly_ponded;                  //(m)          //140113FMS
    control.debug.infiltrated += hourly_water_in - hourly_ponded; //(m)          //140418LML
    control.debug.water_in_vertical += hourly_water_in;           //(m) Debug only
    Cumulative_Gross_Water_In += gross_water_in;            //(m)                //140310FMS
}
//______________________________________________________________________________
/*160606 RLN Evaporator_soil now handles this  The code can be moved to soilprocess_class_MBVB.cpp
double SoilProcessesClass::DetermineSoilWaterEvaporationHourly(double Pot_Soil_Evap_mm)
{
    //FMS Aug 20, 2014
    double Layer_Thickness = SoilProfileRef.get_thickness_m(1);
    double PWP_Top_Layer = SoilProfileRef.get_permanent_wilt_point_volumetric(1);
    double Water_Content_Top_layer = SoilStateRef.get_liquid_water_content_volumetric(1);
    double Air_Dry_WC = PWP_Top_Layer / 3.0;                       //This is an approximation to air-dry water content
    double Maximum_Attainable_Soil_Water_Evaporation(0.0);
    if (Water_Content_Top_layer > Air_Dry_WC)
        Maximum_Attainable_Soil_Water_Evaporation = 
            (Water_Content_Top_layer - Air_Dry_WC) * Layer_Thickness * WaterDensity_kg_m3;
    double Soil_Water_Evaporation(0.0);
    if (Water_Content_Top_layer > PWP_Top_Layer)
        Soil_Water_Evaporation = Pot_Soil_Evap_mm;  //Soil evaporation in mm/day = kg/m2/day
    else if (Water_Content_Top_layer > Air_Dry_WC)
        Soil_Water_Evaporation = Pot_Soil_Evap_mm 
                                * pow(((Water_Content_Top_layer - Air_Dry_WC) 
                                      / (PWP_Top_Layer - Air_Dry_WC)),2);
    if (Soil_Water_Evaporation > Maximum_Attainable_Soil_Water_Evaporation) {
        Soil_Water_Evaporation = Maximum_Attainable_Soil_Water_Evaporation;
        Water_Content_Top_layer = Air_Dry_WC;
    } else {
        Water_Content_Top_layer -= (Soil_Water_Evaporation / 1000.0) / Layer_Thickness; // * WD)
    }
    SoilStateRef.set_water_content_volumetric_layer(1,Water_Content_Top_layer);
    return Soil_Water_Evaporation;          //(mm/hour)
}
*/
//______________________________________________________________________________

/*160505RLN LML will use CropSyst Crop Proper    The code can be moved to soilprocess_class_MBVB.cpp
double SoilProcessesClass::calcPotSoilWaterEvaporationHourly
(int hour_of_day
,WeatherStateDailyClass & Weather
,clsSnow & Snow
#if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
,double Total_Canopy_Solar_Radiation_Interception_Fraction
#else
,clsSimulation & Simulation
,clsCrop & Crop
#endif
)
{
    int HourOfDay = hour_of_day;
    double FractionSnowCover = Snow.Avg_Daily_Fraction_Cover_Snow;  //RS added
    #if (defined (CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
    double Fraction_Solar_Irradiance =
          solar_irradiance_extraterrestrial_basin.get_insolation_fraction_today  //151214
             ((CORN::Hour)hour_of_day);
    #else
    double Fraction_Solar_Irradiance = Weather.getHourlyFractionOfSolarIrradiance(HourOfDay);//140820FMS
    bool Crop_Emerged = Simulation.pSimulationRotation->getCropExist();          //140723FMS_140903LML need double check!!!
    double Total_Canopy_Solar_Radiation_Interception_Fraction = (Crop_Emerged)   //141204RLN
      ? Crop.pCropState->Fraction_Solar_Rad_Intercepted_Total_Canopy
      : 0.0;                                                                     //141204RLN
    #endif
    double Mulch_Solar_Radiation_Interception = 0.3; //to be implemented OJO 160120FMS was 0
    double ET_refer =
         #ifdef WEATHER_PROVIDER_VERSION
            ET_ref->get_mm(ET_FAO_56_Penman_Monteith_CropSyst);                  //150724_141222RLN
         #else
            Weather.getReferenceCropET();
         #endif
    ET_refer = CORN::must_be_greater_or_equal_to<double>(ET_refer,0);

    #ifdef CHECK_SOIL_EVAPORATION_FOR_DEBUG
    ET_refer = 2.0;
    std::clog<<"ET_refer IS SET AT 2 MM/DAY FOR DEBUGING!!!\n";
    #endif

    double Pot_Soil_Water_Evaporation =
                                 ET_refer
                                 * (1 - Total_Canopy_Solar_Radiation_Interception_Fraction)
                                 * (1 - Mulch_Solar_Radiation_Interception)
                                 * (1 - FractionSnowCover)
                                 * (Fraction_Solar_Irradiance);                  //140820FMS
    //std::clog<<"hour:"    <<HourOfDay
    //         <<"\tFrac:"    <<Fraction_Solar_Irradiance
    //         <<"\tET_ref:"  <<ET_refer
    //         <<"\tPET_hour:"<<Pot_Soil_Water_Evaporation
    //         <<std::endl;

    return Pot_Soil_Water_Evaporation;      //(mm/hour)
}
*/
//______________________________________________________________________________
void SoilProcessesClass::UpdateSoilAndCropOutputsOnSoilEvap(
                                         int hour_of_day
                                         #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
                                         #else
                                         ,bool crop_emerged
                                         ,clsCrop & Crop
                                         #endif
                                         ,double soil_evap_mm)
{
    SoilStateRef.Hourly_Soil_Water_Evaporation_m = mm_to_m(soil_evap_mm);
    if (hour_of_day == 0)
        SoilStateRef.Daily_Soil_Water_Actual_Evaporation_m = mm_to_m(soil_evap_mm);
    else
        SoilStateRef.Daily_Soil_Water_Actual_Evaporation_m += mm_to_m(soil_evap_mm);
    //150921LML SoilStateRef.Cumulative_Actual_Soil_Evaporation_m += mm_to_m(soil_evap_mm);
   #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
      // In CropSyst proper, soil evap is not stored in crop object.
      // It shouldn't be in MicroBasin version either  141203RLN
   #else
    if (crop_emerged) {
      Crop.pCropState->Actual_Soil_Evaporation = soil_evap_mm;
      Crop.pCropState->Cumulative_Actual_Soil_Evaporation += soil_evap_mm;
    }
   #endif
}
//______________________________________________________________________________
void SoilProcessesClass::UpdateSoilAndCropOutputsOnSoilPotEvap(
                                         int hour_of_day
                                         #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
                                         #else
                                         ,bool crop_emerged
                                         ,clsCrop & Crop
                                         #endif
                                         ,double Pot_soil_evap_mm)
{

//160414RLN Actually this entire function is probably obsolete

   /*160414RLN obsolete, now using evaporation_potential_remaining
    if (hour_of_day == 0)
        SoilStateRef.Daily_Soil_Water_Potential_Evaporation_m = mm_to_m(Pot_soil_evap_mm);
    else 
        SoilStateRef.Daily_Soil_Water_Potential_Evaporation_m += mm_to_m(Pot_soil_evap_mm);
   */
   #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
      // In CropSyst proper, soil evap is not stored in crop object.
      // It shouldn't be in MicroBasin version either                            141203RLN
   #else
    if (crop_emerged) {
      Crop.pCropState->Potential_Soil_Evaporation = Pot_soil_evap_mm;
      Crop.pCropState->Cumulative_Potential_Soil_Evaporation += Pot_soil_evap_mm;
    }
   #endif
}
//______________________________________________________________________________
#endif
