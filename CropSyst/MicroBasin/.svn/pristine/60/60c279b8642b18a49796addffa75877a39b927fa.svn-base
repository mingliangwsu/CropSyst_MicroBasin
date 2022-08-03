#ifndef MBVB_SOIL
#include "soil_MicroBasin.h"
namespace MicroBasin
{
//______________________________________________________________________________
Soil_tallies::Soil_tallies()
: comb_Share_Flow()
, Hydro_Standard_Slope()
/*NYI WARNING
    std::vector<std::vector<double> > comb_Share_Flow;                           //[layer][direction] adjusted shareflow direction 0-7: fraction each direction 8:total fraction
       // I think this is output
*/
,Vertical_flow_balance_allLayers (0) //(m)
,Hourly_Runoff_m                 (0)                                                     //(m) Overlandflow runoff
,Hourly_Runon_m                  (0)                                    //(m) Overlandflow runon from upstream grid cells
,Daily_Runoff_m                  (0)
,Daily_Runon_m                   (0)
,Daily_LaterFlowIn_m             (0)
,Daily_LaterFlowOut_m            (0)
{
}
//_2016-07-22___________________________________________________________________
bool Soil_tallies::start_day()                                       modification_
{
    Daily_Runoff_m = 0;
    Daily_Runon_m = 0;
    Daily_LaterFlowIn_m = 0;
    Daily_LaterFlowOut_m = 0;
    return true;
}
//_2016-07-22___________________________________________________________________
bool Soil_tallies::start_hour()                                      modification_
{
   //Hourly_Irrigation_m = 0;
   Hourly_Runoff_m = 0;
   Hourly_Runon_m = 0;
   //NYI Hourly_Runoff_infiltration_excess_m = 0
   //NYI Hourly_Infiltration_m = 0;

   return true;
}
//_2016-07-22___________________________________________________________________
Soil::Soil
(const CORN::Date             &today_
,const CORN::Hour             &hour_
,const CS::Annual_temperature &annual_temperature_
#ifdef PROVIDES_SOIL_TEMPERATURE_PROFILE
,const CS::Land_unit_meteorological &meteorological_                       //151022
#endif
)
: CropSyst::Soil
   (0 // NYI Smart_soil_parameters          *_parameters check if parameter are needed
   ,today_
   ,annual_temperature_                                                          //150424RLN
   #ifdef PROVIDES_SOIL_TEMPERATURE_PROFILE
   ,meteorological_                                                              //160721RLN
   #endif
   )
, hour(hour_)
{
}
//_2016-07-22___________________________________________________________________
Soil::~Soil()
{
}
//_2016-07-22___________________________________________________________________
bool Soil::process_hour()                                          modification_
{

    bool success_FD(false);
    #ifndef CROPSYST_VERSION
    #ifdef CROPSYST_PROPER_CROP
    #else
    bool Crop_Emerged = Simulation.pSimulationRotation->getCropExist();
    #endif
    #endif
    //now use hour int current_hour = ControlRef.hour;
    float64 actually_infiltrated_time_step_m(0.0);
    float64 actually_evaporated_time_step_m_ts(0.0);
    //float64 actually_reported_drainage_m_ts;
    float64 actually_balance_drainage_m_ts(0.0);
    float64 surface_runoff_m_ts(0.0);
    //float64 runoff_m_ts(0.0);
    double error_FD_m_ts(-9999.0);
    //double pot_soil_evap_mm(0.0);
    #ifdef CHECK_MASS_BALANCE
    BalanceItem water_bal;
    double water_storage = pSoilState->pond.ref_depth().get_m() // 160411RLN pond.get_depth()
                           + pSoilState->getTotalSoilWaterContent_m();
    water_bal.SetInitPool(water_storage);
    #ifndef CROPSYST_VERSION
    BalanceItem nitrate_bal,amonia_bal;
    #endif
    #endif
    /*LML 141022 need treatments on the pond, i.e. seperate runon and surface water storage*/
    double eff_rain_m_ts =
        //160616LML mm_to_m(Snow.Hourly_Rain_mm[hour] + Snow.Hourly_Snow_Melt_Amount[hour]);
        pSoilState->pond.relinquish_depth();                                     //160616LML

    double irrig_m_ts = 0;
    #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_MANAGEMENT))
    #else
    irrig_m_ts = mm_to_m(Management.pManagementState->Irrigation_Amount / 24.0);
    #endif
    double runon_m_ts(0.0);
    double yesterday_hourly_transpiration_m(0);

    /*160606RLN  CropSyst handles transipration
    pSoilProcesses->UpdateHourlySoilWaterContentByDailyTranspiration
         (weather
         #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
         ,fract_canopy_cover                                                     //150317RLN
         #else
         ,crop
         #endif
         ,yesterday_hourly_transpiration_m);                                     //150310LML_140904FMS
    */
    /*160505RLN
    if (hour == 0)
    {  // calculate daily potential evaporation (for CROPSYST_FD method)         //141022LML
        for (int hour_of_day = 0;hour_of_day < 24; hour_of_day++) {
            double temp = pSoilProcesses->calcPotSoilWaterEvaporationHourly
               (hour_of_day
               ,Weather
               ,Snow
               #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
               ,fract_canopy_cover                                               //141212
               #else
               ,Simulation
               ,crop
               #endif
               );
            assert(temp >= 0.0);
            pSoilProcesses->UpdateSoilAndCropOutputsOnSoilPotEvap
               (hour_of_day
               #ifndef CROPSYST_VERSION
               #ifndef CROPSYST_PROPER_CROP
               ,Crop_Emerged
               ,crop
               #endif
               #endif
               ,temp);

               //160414RLN UpdateSoilAndCropOutputsOnSoilPotEvap is probably obsolete

            if (hour_of_day == hour) pot_soil_evap_mm = temp;
        }
    } else {
        pot_soil_evap_mm = pSoilProcesses->calcPotSoilWaterEvaporationHourly
        (hour
        ,Weather
        ,Snow
        #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
        ,fract_canopy_cover                                                      //141212
        #else
         ,Simulation
         ,crop
        #endif
        );
    } */

    //TODO: soil hourly evaporation

    //std::clog<<"hour:"<< (int)hour<<"\tpot_soil_evap_mm:"<<pot_soil_evap_mm<<std::endl;
    #if (defined(CHECK_OVERLANDFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_HOURLY_CASCADE_FOR_DEBUG))
    pot_soil_evap_mm = 0;
    std::clog<<"DEBUG!!! SET pot_soil_evap_mm = 0!!!\n";
    #endif
    /*160505RLN soil evaporation will be from Crop Proper
    if (ControlRef.infiltration_model_labeled.get() == CASCADE_HOURLY_INFILTRATION) //150709
    {
        actually_evaporated_time_step_m_ts =
            mm_to_m(pSoilProcesses->DetermineSoilWaterEvaporationHourly(pot_soil_evap_mm));
        assert(actually_evaporated_time_step_m_ts >= 0);
    }
    */
    //pSoilState->Daily_PET_MB += mm_to_m(pot_soil_evap_mm);                       //160407LML
    #ifndef CROPSYST_VERSION
    pSoilProcesses->TillageEffectOnWCHourly(Management);
    #ifdef CHECK_MASS_BALANCE
    nitrate_bal.SetInitPool(pSoilState->getProfileNO3NMass()+pSoilState->Layer_Nitrate_N_Mass[0]);
    amonia_bal.SetInitPool(pSoilState->getProfileNH4NMass()+pSoilState->Layer_Ammonium_N_Mass[0]);
    #endif
    #endif

    if (ControlRef.infiltration_model_labeled.get() == FINITE_DIFFERENCE_INFILTRATION) //150709RLN
    {
#ifndef LIU_FD_RICHARD
        success_FD = pSoilProcesses->performFD_InfiltrationAndTransport
            (false
            ,eff_rain_m_ts
            ,irrig_m_ts
            ,runon_m_ts
            ,actually_infiltrated_time_step_m
            ,actually_evaporated_time_step_m_ts
            //,actually_reported_drainage_m_ts
            ,actually_balance_drainage_m_ts
            ,surface_runoff_m_ts
            ,error_FD_m_ts
            //#ifndef CROPSYST_VERSION
            //,Management
            //,Simulation
            //#endif
            );

        #ifdef LIU_DEBUG
        if(!success_FD) std::clog<<" DOY:"<<(int)today.get_DOY()
                                <<" Hour:"<<(int)ControlRef.hour
                                <<" Unsucess FD verticle flow counted!"<<std::endl;
        #endif
#else
        #ifdef MBVB_FD
        pSoilProcesses->performFDRichard(Simulation, Management);
        success_FD = true;
        #endif
#endif
    }
    pSoilProcesses->UpdateSoilAndCropOutputsOnSoilEvap
        (ControlRef.hour
        #if (defined(CROPSYST_PROPER_CROP) || defined(CROPSYST_VERSION))
        #else
        ,Crop_Emerged
        ,crop
        #endif
        ,m_to_mm(actually_evaporated_time_step_m_ts));                           //141021LML
    // moved after FD cascade for calculating soil evaporation                   //141021LML

    #ifdef MBVB_SOIL_TEMPERATURE
    pSoilTemperature->CalculateHourlySoilTemperature
        #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
        (fract_canopy_cover
        #ifdef MBVB_SNOW
        ,clsSnowRef
        #endif
        ,crop_height);                             //141212
        #else
        (Simulation, Snow, crop);
        #endif
    #endif

    //160616LML moved under clsSnowRef.HourlySnowRoutine(hour);                                  //160224RLN
        //160224RLN  (weather,BasinCellRefX);                                    //160211LML
    //if (cellid == 106) {
    //    std::clog<<"beforre cascade: NO3_amount[0]"<<pSoilState->Layer_Nitrate_N_Mass[0]
    //            <<" NO3_con[0]"<<pSoilState->Layer_Nitrate_N_Conc[0]<<std::endl;
    //}
    if (!success_FD)
    {
        /*std::clog<<"BEFORE PerformHourlyCascadeInfiltrationAndTransport:"
                 <<"\thour:"<<ControlRef.hour
                 <<"\tcell:"<<clsSnowRef.RefGridID
                 <<"\tamount[NH4][layer=0]:"<<chemicals->get_NH4_molecular_mass_kg_m2(0)
                 <<"\tamount[NO3][layer=0]:"<<chemicals->get_NO3_molecular_mass_kg_m2(0)
                 <<std::endl;*/
        pSoilProcesses->PerformHourlyCascadeInfiltrationAndTransport(
                eff_rain_m_ts//DEBUG ONLY!!!
                ,irrig_m_ts
                ,runon_m_ts
                ,actually_infiltrated_time_step_m
                //,actually_reported_drainage_m_ts
                ,actually_balance_drainage_m_ts
                ,surface_runoff_m_ts
            #ifndef CROPSYST_VERSION
            ,Simulation
                ,Management
            #endif
            );
        /*std::clog<<"AFTER PerformHourlyCascadeInfiltrationAndTransport:"
                 <<"\thour:"<<ControlRef.hour
                 <<"\tcell:"<<clsSnowRef.RefGridID
                 <<"\tamount[NH4][layer=0]:"<<chemicals->get_NH4_molecular_mass_kg_m2(0)
                 <<"\tamount[NO3][layer=0]:"<<chemicals->get_NO3_molecular_mass_kg_m2(0)
                 <<std::endl;*/

    }
    pSoilState->pond.set_depth(surface_runoff_m_ts);                             //160616LML
    #ifdef MBVB_SNOW
    clsSnowRef.HourlySnowRoutine(hour);                                  //160224RLN_160616LML moved here
    #endif
    //if (cellid == 106) {
    //    std::clog<<"after cascade: NO3[0]"<<pSoilState->Layer_Nitrate_N_Mass[0]
    //             <<" NO3_con[0]"<<pSoilState->Layer_Nitrate_N_Conc[0]<<std::endl;
    //}
    //Hourly_Prec_Irrig_SnowMelt_m = Hourly_Non_Intercepted_Rain_m +
    //Hourly_Irrigation_m + Hourly_Snow_Melt_m;                                  //130110FMS
    pSoilState->Hourly_Prec_Irrig_SnowMelt_m         = eff_rain_m_ts + irrig_m_ts;  //140917LML
    pSoilState->Daily_Irrigation_m                  += irrig_m_ts;
    pSoilState->Daily_Drainage_m                    += actually_balance_drainage_m_ts;         //140509 RLN
    pSoilState->Hourly_Drainage_m                    = actually_balance_drainage_m_ts;         //140509 RLN
    pSoilState->Hourly_Infiltration_m                = actually_infiltrated_time_step_m;
    pSoilState->Daily_Infiltration                  += actually_infiltrated_time_step_m;
    pSoilState->Hourly_Runoff_infiltration_excess_m  = surface_runoff_m_ts;
    pSoilState->Daily_Runoff_infiltration_excess_m  += surface_runoff_m_ts;
    //pSoilState->Hourly_Runoff_m

    if (ControlRef.infiltration_model_labeled.get()==CASCADE_HOURLY_INFILTRATION) //150709RLN
        pSoilProcesses->Finite_Difference_Error_mm = -9999.0;
    else if (!success_FD)
        pSoilProcesses->Finite_Difference_Error_mm = m_to_mm(error_FD_m_ts);
    // Set hourly WC
    for (int layer = 1; layer <= pSoilProfile->get_number_layers(); layer ++) {
        if (ControlRef.hour == 23)
            pSoilState->Yesterday_WC[layer] = pSoilState->get_water_plus_ice_content_volumetric(layer);
        pSoilState->Today_Hourly_WC[layer][ControlRef.hour] = pSoilState->get_water_plus_ice_content_volumetric(layer);
    }
    #ifdef CHECK_MASS_BALANCE
    water_storage
       = pSoilState->pond.ref_depth().get_mm()                                   //160411RLN
       + pSoilState->getTotalSoilWaterContent_m();
    water_bal.SetFluxIn(eff_rain_m_ts+irrig_m_ts);
    water_bal.SetFluxOut(actually_balance_drainage_m_ts+actually_evaporated_time_step_m_ts+yesterday_hourly_transpiration_m);
    water_bal.SetFinalPool(water_storage);
    #ifndef CROPSYST_VERSION
    if (pSoilState->chemicals_optional)                                           //151212RLN
    {
    nitrate_bal.SetFinalPool(pSoilState->getProfileNO3NMass()+pSoilState->Layer_Nitrate_N_Mass[0]);
    nitrate_bal.SetFluxOut(pChemTransport->Chemical_Mass_Leaching_NO3);
    amonia_bal.SetFinalPool(pSoilState->getProfileNH4NMass()+pSoilState->Layer_Ammonium_N_Mass[0]);
    amonia_bal.SetFluxOut(pChemTransport->Chemical_Mass_Leaching_NH4);
    }
    #endif
    if (!water_bal.IsMassBalance()) {
        #pragma omp critical
        water_bal.PrintMassBalanceTerms("clssoil::HourlySoilProcesses");
    }
    #endif


   return true;
}
//_2016-07-22___________________________________________________________________

} // namespace MicroBasin
#endif
