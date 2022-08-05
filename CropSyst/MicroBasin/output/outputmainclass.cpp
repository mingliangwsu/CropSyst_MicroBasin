#ifdef VB_SAME_CSV_OUTPUT
#include "outputmainclass.h"
#ifdef CROPSYST_VERSION
#include "crop/phenology_interface.h"
#include "crop/crop_interfaced_cropsyst.h"
#include "cs_accum.h"
#include "soil/chemical_balance.h"
#endif
#ifdef CROPSYST_WEATHER
#include "common/weather/hour/weather_hours.h"
#endif
#include "crop/crop_N_interface.h"
#include <iostream>
//#include "datetime/date.hpp"
#include "CropSyst/source/organic_matter/OM_residues_profile_abstract.h"
#include "corn/measure/measures.h"
#include "land_unit_sim.h"
#include "control/allcontrolclass.h"
#include "basin/basincellclass.h"
#include "common/residue/residues_interface.h"                                   //160616LML
#include "common/biometeorology/ET_reference_FAO.h"
#include "soil/temperature_hourly_interface.h"
#ifndef MBVB_SNOW
#  include "weather/snow_pack.h"
#endif
//______________________________________________________________________________
OutputMainClass::OutputMainClass
(const CORN::Date_const &today_                                                        //160225RLN
,BasinCellClass   *gridcell_ref_
//#ifndef CELL_METEOROLOGY
//,BasinClass     *basin_ref_
//#endif
)                                                //151005LML
:gridcell_ref  (gridcell_ref_)                                                   //151005LML
//#ifndef CELL_METEOROLOGY
//,basin_ref     (basin_ref_)                                                      //160810
//#endif
,today         (today_)                                                          //160225RLN
{
    //Here has some asumptions for allocate memory
    #ifdef VB_SAME_CSV_OUTPUT
    // The operator overrides are not working in BC++
    AllControlClass *control = &gridcell_ref->ControlRef;
    CORN::Date_32_clad tdata1(control->getStartDate());
    CORN::Date_32_clad tdata2(control->getEndDate());
    int Total_Days = tdata1.days_between(/*(const Date_time &)*/tdata2,true);                           //160224RLN
    int Total_Days_For_Hourly_Output;
    int Total_Hours(0);
    int Total_Years = tdata2.get_year() - tdata1.get_year() + 1;
    if (control->bWrite_Hourly_Output)
    {   Total_Days_For_Hourly_Output =
           control->Start_Date_Hourly_Output.days_between                        //160225RLN
          (/*(const Date_time &)*/control->End_Date_Hourly_Output,true);
        Total_Hours = Total_Days_For_Hourly_Output * 24;
    }
    Hour_Sequence = 0;
    Soil_Day_Sequence = 0;
    Growth_Day_Sequence = 0;
    Growth_Season_Sequence = 0;
    Annual_Sequence = 0;
    //if (AllcontrolRef.bWrite_Daily_Output) 
        //pDaily_Soil = new OutputDailySoilClass[Total_Days];       //For everyday
    //if (AllcontrolRef.bWrite_Growth_Daily_Output) 
        //pGrowth = new OutputGrowthClass[Total_Days];           //For everyday after crop exist
    //if (AllcontrolRef.bWrite_Growth_Season_Output) 
        //pGrowth_Season = new OutputGrowthSeasonClass[Total_Growth_Seasons];
    //if (AllcontrolRef.bWrite_Annual_Output) 
        //pAnnual = new OutputAnnualClass[Total_Years];
    //if (AllcontrolRef.bWrite_Hourly_Output) 
        //pHour = new OutputHourClass[Total_Hours];
    #endif
}
//______________________________________________________________________________
OutputMainClass::~OutputMainClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~OutputMainClass:pDaily_Soil..."<<std::endl;
#endif
    //if (AllcontrolRef.bWrite_Daily_Output) delete[] pDaily_Soil;
#ifdef Destruct_Monitor
    std::cout<<"~OutputMainClass:pGrowth ..."<<std::endl;
#endif
    //if (AllcontrolRef.bWrite_Growth_Daily_Output) delete[] pGrowth;
#ifdef Destruct_Monitor
    std::cout<<"~OutputMainClass:pGrowth_Season ..."<<std::endl;
#endif
    //if (AllcontrolRef.bWrite_Growth_Season_Output) delete[] pGrowth_Season;
#ifdef Destruct_Monitor
    std::cout<<"~OutputMainClass:pAnnual ..."<<std::endl;
#endif
    //if (AllcontrolRef.bWrite_Annual_Output) delete[] pAnnual;
#ifdef Destruct_Monitor
    std::cout<<"~OutputMainClass:pHour ..."<<std::endl;
#endif
    //if (AllcontrolRef.bWrite_Hourly_Output) delete[] pHour;
#ifdef Destruct_Monitor
    std::cout<<"~OutputMainClass done."<<std::endl;
#endif
}
//______________________________________________________________________________

//______________________________________________________________________________
void OutputMainClass::initialize()
{
    //Implement later M.Liu
}
//______________________________________________________________________________
void OutputMainClass::WriteGrowingSeasonOutput
(/*clsCrop &Crop,clsSoil &Soil*/)
{
    OutputGrowthSeasonClass *pGrowth_Season_out = new OutputGrowthSeasonClass;//&pGrowth_Season[Growth_Season_Sequence];
    #ifdef CROPSYST_VERSION
    const CropSyst::Crop_interfaced &crop = *gridcell_ref->crop_at_end_season;
    const CropSyst::Land_unit_simulation &landunit = *gridcell_ref;
    const CropSyst::Period_accumulators &GP_accumulator = *landunit.GP_accumulators_active;
    std::wstring cropname;
    crop.get_name(cropname);
    CORN::wstring_to_string(cropname,pGrowth_Season_out->Crop_Name);
    //160415LML pGrowth_Season_out->Year_Planting               = crop.ref_phenology().get_initiation_date(NGS_PLANTING).get_year();
    //160415LML pGrowth_Season_out->DOY_Planting                = crop.ref_phenology().get_initiation_date(NGS_PLANTING).get_DOY();
    //160415LML pGrowth_Season_out->DOY_Emergence               = crop.ref_phenology().get_initiation_date(NGS_EMERGENCE).get_DOY();
    //160415LML pGrowth_Season_out->DOY_Flowering               = crop.ref_phenology().get_initiation_date(NGS_ANTHESIS).get_DOY();
    //160415LML pGrowth_Season_out->DOY_Begin_Yield_Formation   = crop.ref_phenology().get_initiation_date(NGS_FILLING).get_DOY();
    //160415LML pGrowth_Season_out->DOY_Physiological_Maturity  = crop.ref_phenology().get_initiation_date(NGS_MATURITY).get_DOY();
    //160415LML pGrowth_Season_out->Year_Harvest                = today.get_year();
    //160415LML pGrowth_Season_out->DOY_Harvest                 = today.get_DOY();//crop.ref_phenology().get_initiation_date(NGS_HARVEST).get_DOY();
    pGrowth_Season_out->planting_date.set_date32(crop.ref_phenology().get_initiation_date(NGS_PLANTING).get_date32());
    pGrowth_Season_out->emergence_date.set_date32(crop.ref_phenology().get_initiation_date(NGS_EMERGENCE).get_date32());
    pGrowth_Season_out->flowering_date.set_date32(crop.ref_phenology().get_initiation_date(NGS_ANTHESIS).get_date32());
    pGrowth_Season_out->begin_yield_formation_date.set_date32(crop.ref_phenology().get_initiation_date(NGS_FILLING).get_date32());
    pGrowth_Season_out->physiological_maturity_date.set_date32(crop.ref_phenology().get_initiation_date(NGS_MATURITY).get_date32());
    pGrowth_Season_out->harvest_date.set_date32(today.get_date32());
    pGrowth_Season_out->Cumulative_Biomass_At_Maturity      = per_m2_to_per_ha(crop.get_total_season_biomass_production_kg_m2());//get_canopy_biomass_kg_ha();                       //(kgDM/ha)
    pGrowth_Season_out->Cumulative_Root_Biomass_At_Maturity = crop.get_act_root_biomass_kg_ha();             //(kgDM/ha)
    pGrowth_Season_out->Crop_Yield      = per_m2_to_per_ha(crop.get_latest_yield_kg_m2());
    pGrowth_Season_out->Precipitation_mm = m_to_mm(GP_accumulator.precip_m);
    pGrowth_Season_out->Actual_Transpiration_mm = m_to_mm(GP_accumulator.act_transpiration);
    pGrowth_Season_out->Actual_ET_mm            = m_to_mm(GP_accumulator.act_evapotranspiration);
    pGrowth_Season_out->Water_Stress_Index      = GP_accumulator.water_stress_index;
    pGrowth_Season_out->Nitrogen_Stress_Index   = GP_accumulator.nitrogen_stress_index;


    //pGrowth_Season_out->N_Updake        = per_m2_to_per_ha(GP_accumulator.N_uptake);
    pGrowth_Season_out->N_Updake        = per_m2_to_per_ha(gridcell_ref->pSoilState->growth_season_N_uptake);



    pGrowth_Season_out->N_Fixation      = per_m2_to_per_ha(GP_accumulator.N_fixation);
    pGrowth_Season_out->N_Applied       = per_m2_to_per_ha(GP_accumulator.inorganic_N_applied);  //170414LML + GP_accumulator.organic_N_applied);
    pGrowth_Season_out->N_Mineralized   = per_m2_to_per_ha(GP_accumulator.OM_N_mineralization);
    pGrowth_Season_out->N_Volatilized   = per_m2_to_per_ha(GP_accumulator.inorganic_NH4_to_atmosphere + GP_accumulator.NH3_volatilization_loss);
    pGrowth_Season_out->N_Immobilized   = per_m2_to_per_ha(GP_accumulator.N_immobilization);
    pGrowth_Season_out->N_Nitrfication  = per_m2_to_per_ha(GP_accumulator.N_nitrification);
    pGrowth_Season_out->N_Denitrified   = per_m2_to_per_ha(GP_accumulator.N_denitrification);
    pGrowth_Season_out->N_N2O_loss_denitrification  = per_m2_to_per_ha(GP_accumulator.N2O_loss_denitrification);
    pGrowth_Season_out->N_N2O_loss_nitrification    = per_m2_to_per_ha(GP_accumulator.N2O_loss_nitrification);
    pGrowth_Season_out->N_N2O_loss      = per_m2_to_per_ha(GP_accumulator.N2O_loss_denitrification + GP_accumulator.N2O_loss_nitrification);
    double leached_N_kg = gridcell_ref->output_flow_solute_kg[SL_Nitrate][TACUM_GROWTHSEASON].Drainage * NO3_to_N_conv
                          + gridcell_ref->output_flow_solute_kg[SL_Ammonia][TACUM_GROWTHSEASON].Drainage * NH4_to_N_conv;
    pGrowth_Season_out->N_Leached       = per_m2_to_per_ha(gridcell_ref->get_kg_per_m2_from_total_kg(leached_N_kg)); //pSoilState->growth_season_N_leached);  //170207LML
    double total_N_runon_kg = (gridcell_ref->output_flow_solute_kg[SL_Ammonia][TACUM_GROWTHSEASON].SurfaceIn
                              + gridcell_ref->output_flow_solute_kg[SL_Ammonia][TACUM_GROWTHSEASON].LateralIn) * NH4_to_N_conv
                              + (gridcell_ref->output_flow_solute_kg[SL_Nitrate][TACUM_GROWTHSEASON].SurfaceIn
                                 + gridcell_ref->output_flow_solute_kg[SL_Nitrate][TACUM_GROWTHSEASON].LateralIn) * NO3_to_N_conv;
    double total_N_runof_kg = (gridcell_ref->output_flow_solute_kg[SL_Ammonia][TACUM_GROWTHSEASON].SurfaceOut
                              + gridcell_ref->output_flow_solute_kg[SL_Ammonia][TACUM_GROWTHSEASON].LateralOut) * NH4_to_N_conv
                              + (gridcell_ref->output_flow_solute_kg[SL_Nitrate][TACUM_GROWTHSEASON].SurfaceOut
                                 + gridcell_ref->output_flow_solute_kg[SL_Nitrate][TACUM_GROWTHSEASON].LateralOut) * NO3_to_N_conv;
    pGrowth_Season_out->N_runon         = per_m2_to_per_ha(gridcell_ref->get_kg_per_m2_from_total_kg(total_N_runon_kg));  //pSoilState->growth_season_N_runon);    //170417LML
    pGrowth_Season_out->N_runoff        = per_m2_to_per_ha(gridcell_ref->get_kg_per_m2_from_total_kg(total_N_runof_kg));  //pSoilState->growth_season_N_runoff);   //170417LML
    //gridcell_ref->pSoilState->growth_season_N_leached = 0;  //170207LML
    gridcell_ref->pSoilState->growth_season_N_uptake  = 0;  //170417LML
    //gridcell_ref->pSoilState->growth_season_N_runon   = 0;  //170417LML
    //gridcell_ref->pSoilState->growth_season_N_runoff  = 0;  //170417LML


    //170410LML
    Soil_chemicals_profile *soil_chemicals = gridcell_ref->LAND_UNIT_SIM_ get_soil_chemicals();
    if (soil_chemicals) {
        pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Planting = gridcell_ref->report_planting_date_soil_profile_NH4_N;
        pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Planting  = gridcell_ref->report_planting_date_soil_profile_NO3_N;
        pGrowth_Season_out->Surface_Ammonium_N_Mass_At_Planting    = gridcell_ref->report_planting_date_surface_NH4_N;  //170510LML
        pGrowth_Season_out->Surface_Nitrate_N_Mass_At_Planting     = gridcell_ref->report_planting_date_surface_NO3_N;  //170510LML
        pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Harvest  = per_m2_to_per_ha (soil_chemicals->sum_NH4_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)); //170410LML
        pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Harvest   = per_m2_to_per_ha (soil_chemicals->sum_NO3_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)); //170410LML
        pGrowth_Season_out->Surface_Ammonium_N_Mass_At_Harvest     = per_m2_to_per_ha (soil_chemicals->NH4->get_surface_mass() * NH4_to_N_conv);             //170510LML
        pGrowth_Season_out->Surface_Nitrate_N_Mass_At_Harvest      = per_m2_to_per_ha (soil_chemicals->NO3->get_surface_mass() * NO3_to_N_conv);             //170510LML
    }


    /*RLN NYI
    pGrowth_Season_out->Potential_Crop_Yield = Crop.pCropState->Potential_Yield * 10000;                                    //(kg/ha);
    pGrowth_Season_out->Crop_Yield = Crop.pCropState->Yield * 10000;                                                        //(kg/ha)
    pGrowth_Season_out->Cumulative_Crop_Potential_Transpiration_At_Maturity = mm_to_m(Crop.pCropState->Cumulative_Crop_Potential_Transpiration);
    pGrowth_Season_out->Cumulative_Actual_Crop_Transpiration_At_Maturity = mm_to_m(Crop.pCropState->Cumulative_Actual_Crop_Transpiration);
    pGrowth_Season_out->Cumulative_Nitrogen_Uptake_At_Maturity = Crop.pCropState->Cumulative_Nitrogen_Uptake * 10000;
    pGrowth_Season_out->Top_N_Mass_At_Maturity = Crop.pCropState->Top_N_Mass * 10000;
    pGrowth_Season_out->Root_N_Mass_At_Maturity = Crop.pCropState->Root_N_Mass * 10000;
    pGrowth_Season_out->Top_N_Mass_At_Emergence = Crop.pCropState->Top_N_Mass_At_Emergence * 10000;
    pGrowth_Season_out->Root_N_Mass_At_Emergence = Crop.pCropState->Root_N_Mass_At_Emergence * 10000;
    pGrowth_Season_out->Crop_N_Balance_At_Maturity = (Crop.pCropState->Cumulative_Nitrogen_Uptake
                                                      + Crop.pCropState->Top_N_Mass_At_Emergence
                                                      + Crop.pCropState->Root_N_Mass_At_Emergence
                                                      - Crop.pCropState->Top_N_Mass
                                                      - Crop.pCropState->Root_N_Mass
                                                      ) * 10000;
    clsSoil &Soil = *gridcell_ref->pSoil;
    //Happens when crop mature
    double N_Initial,N_Final,N_Uptake;
    //N_uptake+TopN_Emergence+RootN_Emergence-TopN_Matunity-RootN_Matunity
    pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Planting =
        Soil.pSoilState->Total_Nitrate_N_Mass_At_Planting * 10000;
    pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Maturity =
        Soil.pSoilState->Total_Nitrate_N_Mass * 10000;
    pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Planting =
        Soil.pSoilState->Total_Ammonium_N_Mass_At_Planting * 10000;
    pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Maturity =
        Soil.pSoilState->Total_Ammonium_N_Mass * 10000;

    pGrowth_Season_out->N_Applied = (Soil.pSoilState->Cumulative_Nitrate_N_Fertilization_Since_Planting
                                    + Soil.pSoilState->Cumulative_Ammonium_N_Fertilization_Since_Planting
                                    + Soil.pSoilState->Cumulative_Nitrate_N_Fertigation_Since_Planting
                                    + Soil.pSoilState->Cumulative_Ammonium_N_Fertigation_Since_Planting
                                    ) * 10000;

    pGrowth_Season_out->N_Mineralized = (Soil.pSoilState->Cumulative_Profile_OM_Mineralization_Since_Planting
                                        + Soil.pSoilState->Cumulative_Profile_Residue_Mineralization_Since_Planting
                                        ) * 10000;
    pGrowth_Season_out->N_Immobilized =
        Soil.pSoilState->Cumulative_Profile_Nitrogen_Immobilization_Since_Planting * 10000;
    N_Uptake = Crop.pCropState->Cumulative_Nitrogen_Uptake
            - Crop.pCropState->Top_N_Mass_At_Emergence
            - Crop.pCropState->Root_N_Mass_At_Emergence;
    pGrowth_Season_out->N_Leached = (Soil.pSoilState->Cumulative_Nitrate_Leaching_Since_Planting
                                    + Soil.pSoilState->Cumulative_Ammonium_Leaching_Since_Planting
                                    ) * 10000;
    pGrowth_Season_out->N_Volatilized =
        Soil.pSoilState->Cumulative_Ammonia_N_Mass_Volatilization_Since_Planting * 10000;
    pGrowth_Season_out->N_Denitrified =
        Soil.pSoilState->Cumulative_Profile_Denitrification_Since_Planting * 10000;
    N_Initial = pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Planting
                + pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Planting;
    N_Final = pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Maturity
              + pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Maturity;
    pGrowth_Season_out->Soil_Growing_Season_N_Balance = N_Initial
                                                        + pGrowth_Season_out->N_Applied
                                                        + pGrowth_Season_out->N_Mineralized
                                                        - N_Uptake
                                                        - pGrowth_Season_out->N_Leached
                                                        - pGrowth_Season_out->N_Volatilized
                                                        - pGrowth_Season_out->N_Denitrified
                                                        - pGrowth_Season_out->N_Immobilized
                                                        - N_Final;
    pGrowth_Season_out->Crop_Avg_Water_Stress_Index = Crop.pCropState->Cumulative_Water_Stress_Index;
    pGrowth_Season_out->Crop_Avg_Top_Nitrogen_Stress_Index = Crop.pCropState->Cumulative_Top_Nitrogen_Stress_Index;
    pGrowth_Season_out->Crop_Avg_Root_Nitrogen_Stress_Index = Crop.pCropState->Cumulative_Root_Nitrogen_Stress_Index;
    pGrowth_Season_out->Overall_Crop_Nitrogen_Balance = Crop.pCropState->Overall_Crop_Nitrogen_Balance * 10000;
    */

    #else
    clsSoil &Soil = *gridcell_ref->pSoil;
    //Happens when crop mature
    double N_Initial,N_Final,N_Uptake;
    pGrowth_Season_out->Crop_Name = Crop.pCropState->Crop_Name;
    pGrowth_Season_out->Year_Planting = Crop.pCropState->Year_Planting;
    pGrowth_Season_out->DOY_Planting = Crop.pCropState->DOY_Planting;
    pGrowth_Season_out->DOY_Emergence = Crop.pCropState->DOY_Emergence;
    pGrowth_Season_out->DOY_Flowering = Crop.pCropState->DOY_Flowering;
    pGrowth_Season_out->DOY_Begin_Yield_Formation = 
        Crop.pCropState->DOY_Begin_Yield_Formation;
    pGrowth_Season_out->DOY_Physiological_Maturity = 
        Crop.pCropState->DOY_Physiological_Maturity;
    pGrowth_Season_out->DOY_Harvest = 
        Crop.pCropState->DOY_Harvest;
    pGrowth_Season_out->Potential_Cumulative_Biomass_At_Maturity = 
        Crop.pCropState->Potential_Cumulative_Biomass * 10000;
    pGrowth_Season_out->Cumulative_Biomass_At_Maturity = 
        Crop.pCropState->Cumulative_Biomass * 10000;
    pGrowth_Season_out->Cumulative_Root_Biomass_At_Maturity = 
        Crop.pCropState->Cumulative_Root_Biomass * 10000;
    pGrowth_Season_out->Potential_Crop_Yield = 
        Crop.pCropState->Potential_Yield * 10000;            //(kg/ha);
    pGrowth_Season_out->Crop_Yield = 
        Crop.pCropState->Yield * 10000;                                //(kg/ha)
    pGrowth_Season_out->Cumulative_Crop_Potential_Transpiration_At_Maturity = 
        Crop.pCropState->Cumulative_Crop_Potential_Transpiration;
    pGrowth_Season_out->Cumulative_Actual_Crop_Transpiration_At_Maturity = 
        Crop.pCropState->Cumulative_Actual_Crop_Transpiration;
    pGrowth_Season_out->Cumulative_Nitrogen_Uptake_At_Maturity = 
        Crop.pCropState->Cumulative_Nitrogen_Uptake;
    pGrowth_Season_out->Top_N_Mass_At_Maturity = 
        Crop.pCropState->Top_N_Mass;
    pGrowth_Season_out->Root_N_Mass_At_Maturity = 
        Crop.pCropState->Root_N_Mass;
    pGrowth_Season_out->Top_N_Mass_At_Emergence = 
        Crop.pCropState->Top_N_Mass_At_Emergence;
    pGrowth_Season_out->Root_N_Mass_At_Emergence = 
        Crop.pCropState->Root_N_Mass_At_Emergence;
    pGrowth_Season_out->Crop_N_Balance_At_Maturity = 
            Crop.pCropState->Cumulative_Nitrogen_Uptake
            + Crop.pCropState->Top_N_Mass_At_Emergence
            + Crop.pCropState->Root_N_Mass_At_Emergence
            - Crop.pCropState->Top_N_Mass
            - Crop.pCropState->Root_N_Mass;
    //N_uptake+TopN_Emergence+RootN_Emergence-TopN_Matunity-RootN_Matunity
    pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Planting = 
        Soil.pSoilState->Total_Nitrate_N_Mass_At_Planting * 10000;
    pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Maturity = 
        Soil.pSoilState->Total_Nitrate_N_Mass * 10000;
    pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Planting = 
        Soil.pSoilState->Total_Ammonium_N_Mass_At_Planting * 10000;
    pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Maturity = 
        Soil.pSoilState->Total_Ammonium_N_Mass * 10000;

    pGrowth_Season_out->N_Applied = (Soil.pSoilState->Cumulative_Nitrate_N_Fertilization_Since_Planting
                                    + Soil.pSoilState->Cumulative_Ammonium_N_Fertilization_Since_Planting
                                    + Soil.pSoilState->Cumulative_Nitrate_N_Fertigation_Since_Planting
                                    + Soil.pSoilState->Cumulative_Ammonium_N_Fertigation_Since_Planting
                                    ) * 10000;

    pGrowth_Season_out->N_Mineralized = (Soil.pSoilState->Cumulative_Profile_OM_Mineralization_Since_Planting
                                        + Soil.pSoilState->Cumulative_Profile_Residue_Mineralization_Since_Planting
                                        ) * 10000;

    pGrowth_Season_out->N_Immobilized = 
        Soil.pSoilState->Cumulative_Profile_Nitrogen_Immobilization_Since_Planting * 10000;

    N_Uptake = Crop.pCropState->Cumulative_Nitrogen_Uptake
            - Crop.pCropState->Top_N_Mass_At_Emergence
            - Crop.pCropState->Root_N_Mass_At_Emergence;
    pGrowth_Season_out->N_Leached = (Soil.pSoilState->Cumulative_Nitrate_Leaching_Since_Planting
                                    + Soil.pSoilState->Cumulative_Ammonium_Leaching_Since_Planting
                                    ) * 10000;
    pGrowth_Season_out->N_Volatilized = 
        Soil.pSoilState->Cumulative_Ammonia_N_Mass_Volatilization_Since_Planting * 10000;
    pGrowth_Season_out->N_Denitrified = 
        Soil.pSoilState->Cumulative_Profile_Denitrification_Since_Planting * 10000;
    N_Initial = pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Planting
                + pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Planting;
    N_Final = pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Maturity
              + pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Maturity;
    pGrowth_Season_out->Soil_Growing_Season_N_Balance = N_Initial
                                                        + pGrowth_Season_out->N_Applied
                                                        + pGrowth_Season_out->N_Mineralized
                                                        - N_Uptake
                                                        - pGrowth_Season_out->N_Leached
                                                        - pGrowth_Season_out->N_Volatilized
                                                        - pGrowth_Season_out->N_Denitrified
                                                        - pGrowth_Season_out->N_Immobilized
                                                        - N_Final;
    pGrowth_Season_out->Crop_Avg_Water_Stress_Index = 
            Crop.pCropState->Cumulative_Water_Stress_Index;
    pGrowth_Season_out->Crop_Avg_Top_Nitrogen_Stress_Index = 
            Crop.pCropState->Cumulative_Top_Nitrogen_Stress_Index;
    pGrowth_Season_out->Crop_Avg_Root_Nitrogen_Stress_Index = 
            Crop.pCropState->Cumulative_Root_Nitrogen_Stress_Index;
    pGrowth_Season_out->Overall_Crop_Nitrogen_Balance = 
            Crop.pCropState->Overall_Crop_Nitrogen_Balance;
    #endif
    
    pGrowth_Season.push_back(*pGrowth_Season_out);
    delete pGrowth_Season_out; pGrowth_Season_out = 0;                           //160115LML
    Growth_Season_Sequence++;
}
//______________________________________________________________________________
void OutputMainClass::WriteDailySoilCropOutput
(
//#ifdef CROPSYST_VERSION
//const CORN::Date_const &ltoday
//#endif
                                               )
{
#ifndef CROPSYST_VERSION

    OutputDailySoilClass *pDaily_Soil_out = new OutputDailySoilClass;
    int num_layers = Soil.pSoilProfile->NumberOfLayers();
    pDaily_Soil_out->Current_Year = today.get_year();                            //151002LML (int)Simulation.pTimeState->getToday().get_year();
    pDaily_Soil_out->Current_DOY = today.get_DOY();                              //151002LML (int)Simulation.pTimeState->getToday().get_DOY();
    #ifdef CROPSYST_PROPER_CROP
   /*141005 NYI RLN
    if (Simulation.pSimulationRotation->getCropExist())
        pDaily_Soil_out->Crop_Name = Crop.pCropState->Crop_Name;            //LML 140829
   */
    #else
    if (
        #ifdef CROPSYST_VERSION
        pCrop
        #else
        Simulation.pSimulationRotation->getCropExist()
        #endif
        )
        pDaily_Soil_out->Crop_Name =
            #ifdef CROPSYST_VERSION
            pCrop
            #else
            Crop.pCropState->Crop_Name;            //LML 140829
            #endif
    #endif
    //150522 pDaily_Soil_out->Management_Name =
    //150522        Simulation.pSimulationRotation->getCurrentManagementName();
    for (int L = 1; L <= num_layers; L++) {
        pDaily_Soil_out->Layer_Water_Content[L] = 
                Soil.pSoilState->get_liquid_water_content_volumetric(L);
        pDaily_Soil_out->Layer_Ice_Content[L] = 
                Soil.pSoilState->Ice_Content[L];
        pDaily_Soil_out->Layer_Nitrate_N_Mass[L] = 
                Soil.pSoilState->Layer_Nitrate_N_Mass[L] * 10000.;
        pDaily_Soil_out->Layer_Ammonium_N_Mass[L] = 
                Soil.pSoilState->Layer_Ammonium_N_Mass[L] * 10000.;
        pDaily_Soil_out->Layer_Avg_Daily_Soil_T[L] = 
                Soil.pSoilState->Avg_Daily_Soil_T[L];
    }

    pDaily_Soil_out->Soil_Water_Actual_Evaporation = 
            Soil.pSoilState->Daily_Soil_Water_Actual_Evaporation_m;
    pDaily_Soil_out->Snow_Evaporation = 
            Soil.clsSnowRef.Daily_Sublimation_Or_Desublimation_m;
    #ifdef CROPSYST_PROPER_CROP
    /*141005 RLN NYI
    if (Simulation.pSimulationRotation->getCropExist())
        pDaily_Soil_out->Plant_Transpiration = Crop.pCropState->Actual_Crop_Transpiration / 1000.0; //LML 140902
    else
    */
    #else
    if (Simulation.pSimulationRotation->getCropExist())
        pDaily_Soil_out->Plant_Transpiration = 
                Crop.pCropState->Actual_Crop_Transpiration / 1000.0; //LML 140902
    else
    #endif
      pDaily_Soil_out->Plant_Transpiration = 0;
    
    pDaily_Soil_out->Daily_Runoff_Excess_Infiltration = 
            Soil.pSoilState->Daily_Runoff_infiltration_excess_m;
    pDaily_Soil_out->Daily_Runoff = Soil.pSoilState->Daily_Runoff_m;
    pDaily_Soil_out->Daily_Runon = Soil.pSoilState->Daily_Runon_m;
    pDaily_Soil_out->NO3_N_Fertilization = 
            Soil.pSoilState->Daily_Nitrate_N_Fertilization * 10000.0;
    pDaily_Soil_out->NH4_N_Fertilization = 
            Soil.pSoilState->Daily_Ammonium_N_Fertilization * 10000.0;
    pDaily_Soil_out->Nitrate_Leaching = 
            Soil.pSoilState->Daily_Nitrate_Leaching * 10000.;
    pDaily_Soil_out->Ammonium_Leaching = Soil.pSoilState->Daily_Ammonium_Leaching * 10000.;
    pDaily_Soil_out->Drainage = Soil.pSoilState->Daily_Drainage_m;
    pDaily_Soil_out->Fraction_Cover_Snow = Soil.clsSnowRef.Avg_Daily_Fraction_Cover_Snow;
    pDaily_Soil_out->Daily_Snow_Depth = Soil.clsSnowRef.Daily_Snow_Depth_m;

    pDaily_Soil_out->Snow_Melt_Amount = Soil.clsSnowRef.Daily_Snow_Melt_Amount_m;
    pDaily_Soil_out->Total_Snow_Amount = Soil.clsSnowRef.Total_SWE_m;
    pDaily_Soil_out->Avg_Snow_Surface_T = Soil.clsSnowRef.Avg_Daily_Snow_Surface_T;
    //pDaily_Soil_out->Avg_Snow_Below_Surface_T = Soil.clsSnowRef.Avg_Daily_Snow_Below_Surface_T;
    pDaily_Soil_out->Precipitation_m = Weather.getDailyPrecipitation_mm() / 1000.0;
    pDaily_Soil_out->Mean_Temperature = Weather.getDailyAverageTemperature();
    
    //LML 140829
    pDaily_Soil_out->Pond_m = Soil.pSoilState->pond.get_depth();
    //pDaily_Soil_out->Total_Snow_Amount;
    pDaily_Soil_out->Total_LiqW_m = Soil.pSoilState->getTotalSoilLiqWaterContent_m();     
    pDaily_Soil_out->Total_Ice_m = Soil.pSoilState->getTotalSoilIceContent_m();      
    pDaily_Soil_out->AG_Residue_C_Mass = 
            Soil.pOrganicResidue->getAboveGroungResidueCarbonMass() * 10000.0;
    pDaily_Soil_out->BG_Residue_C_Mass = 
            Soil.pOrganicResidue->getBellowGroungResidueCarbonMass() * 10000.0;
    pDaily_Soil_out->SOM_C_Mass = 
            Soil.pSOMResidueMaster->getProfileSOMCarbonMass() * 10000.0;       
    pDaily_Soil_out->AG_Residue_N_Mass = 
            Soil.pOrganicResidue->getAboveGroungResidueNitrogenMass() * 10000.0;
    pDaily_Soil_out->BG_Residue_N_Mass = 
            Soil.pOrganicResidue->getBellowGroungResidueNitrogenMass() * 10000.0;
    pDaily_Soil_out->SOM_N_Mass = 
            Soil.pSOMResidueMaster->getProfileSOMNitrogenMass() * 10000.0;       
    pDaily_Soil_out->NO3_N_Mass = Soil.pSoilState->getProfileNO3NMass() * 10000.0;       
    pDaily_Soil_out->NH4_N_Mass = Soil.pSoilState->getProfileNH4NMass() * 10000.0;       

    pDaily_Soil_out->Profile_SOM_Carbon_Lost_As_CO2 = 
            Soil.pSoilState->Profile_SOM_Carbon_Lost_As_CO2 * 1000.0; 
    pDaily_Soil_out->Profile_Residue_Carbon_Lost_As_CO2 = 
            Soil.pSoilState->Profile_Residue_Carbon_Lost_As_CO2 * 1000.0;
    if (Simulation.pSimulationRotation->getCropSeasonStarted() &&
         #ifdef CROPSYST_PROPER_CROP
         Crop.ref_phenology().has_emerged()
         #else
         !Crop.getWaitingForEmergence()
         #endif
         ) {
        pDaily_Soil_out->Maintenance_Respiration = Soil.pSoilState->Maintenance_Respiration;
        pDaily_Soil_out->Biosynthesi_Efficiency = Soil.pSoilState->Biosynthesi_Efficiency;
        pDaily_Soil_out->Gross_Canopy_Photosynthesis = Soil.pSoilState->Gross_Canopy_Photosynthesis;
        pDaily_Soil_out->CO2_by_Plant_Respiration = Soil.pSoilState->CO2_by_Plant_Respiration;
        pDaily_Soil_out->Biomass_Root_Today = Soil.pSoilState->Biomass_Root_Today;
        pDaily_Soil_out->Biomass_Top_Today = Soil.pSoilState->Biomass_Top_Today;
    } else {
        pDaily_Soil_out->Maintenance_Respiration = 0.0;
        pDaily_Soil_out->Biosynthesi_Efficiency = 0.0;
        pDaily_Soil_out->Gross_Canopy_Photosynthesis = 0.0;
        pDaily_Soil_out->CO2_by_Plant_Respiration = 0.0;
        pDaily_Soil_out->Biomass_Root_Today = 0.0;
        pDaily_Soil_out->Biomass_Top_Today = 0.0;
    }
    Soil_Day_Sequence++;
    pDaily_Soil.push_back(*pDaily_Soil_out);
    delete pDaily_Soil_out; pDaily_Soil_out = 0;                                 //150722RLN
#else
  OutputDailySoilClass *pDaily_Soil_out = new OutputDailySoilClass;
  BasinCellClass *cell = gridcell_ref;
  Soil_chemicals_profile *soil_chemicals = cell->LAND_UNIT_SIM_ get_soil_chemicals();//151208RLN
  Organic_matter_residues_profile_abstract *organic_matter_residues_profile_kg_m2    //151208RLN
     = cell->LAND_UNIT_SIM_ organic_matter_residues_profile_kg_m2;                   //151208RLN

  CropSyst::Crop_interfaced *current_crop = cell->LAND_UNIT_SIM_ crop_active_or_intercrop
                                            ? cell->LAND_UNIT_SIM_ crop_active_or_intercrop //160322LML
                                            : cell->LAND_UNIT_SIM_ crop_at_end_season       //160322LML
                                            ;
  std::wstring wactive_crop_name(L"NOCROP");
  bool cropnum
     = current_crop ? current_crop->get_name(wactive_crop_name) : false;
  std::string active_crop_name(wactive_crop_name.begin(),wactive_crop_name.end());
  int num_layers = cell->pSoilProfile->NumberOfLayers();
  //160415LML pDaily_Soil_out->Current_Year = today.get_year();                              //151002LML (int)Simulation.pTimeState->getToday().get_year();
  //160415LML pDaily_Soil_out->Current_Month = today.get_month();
  //160415LML pDaily_Soil_out->Current_DOM = today.get_DOM();
  //160415LML pDaily_Soil_out->Current_DOY = today.get_DOY();                                //151002LML (int)Simulation.pTimeState->getToday().get_DOY();
  pDaily_Soil_out->Current_Date.set_date32(today.get_date32());

  pDaily_Soil_out->Crop_Name = active_crop_name;
  pDaily_Soil_out->Development_Stage = current_crop ? current_crop->describe_growth_stage() : "NONE"; //151016LML
  pDaily_Soil_out->Leaf_Area_Index = current_crop ? current_crop->get_LAI(true) : 0; //151016LML
  for (int L = 1; L <= num_layers; L++) {
     #ifdef MBVB_SOIL
      pDaily_Soil_out->Layer_Water_Content[L]     = cell->pSoilState->get_liquid_water_content_volumetric(L);
      pDaily_Soil_out->Layer_Ice_Content[L]       = cell->pSoilState->Ice_Content[L];
     #else
      pDaily_Soil_out->Layer_Water_Content[L]     = cell->ref_soil()->ref_hydrology()->get_liquid_water_content_volumetric(L);   //160724RLN
      pDaily_Soil_out->Layer_Ice_Content[L]       = cell->ref_soil()->ref_hydrology()->get_ice_content_volumetric(L);            //160724RLN
     #endif
      if (soil_chemicals)                                                        //151208RLN
      {  pDaily_Soil_out->Layer_Nitrate_N_Mass[L]    = soil_chemicals->get_NO3_N_mass_kg_ha(L); //151208RLN
         pDaily_Soil_out->Layer_Ammonium_N_Mass[L]   = soil_chemicals->get_NH4_N_mass_kg_ha(L); //151208RLN
      }
      pDaily_Soil_out->Layer_Avg_Daily_Soil_T[L]  =
      #ifdef MBVB_SOIL_TEMPERATURE
            cell->pSoilState->Avg_Daily_Soil_T[L];
      #else
            cell->soil->ref_temperature_profile_hourly()->get_temperature(23,L); //160801LML 99999.9; //160721 Roger needs to provide
      #endif
  }
  pDaily_Soil_out->Soil_Water_Actual_Evaporation  = cell->pSoilState->Daily_Soil_Water_Actual_Evaporation_m;
  pDaily_Soil_out->Snow_Evaporation
  #ifdef MBVB_SNOW
     = mm_to_m(cell->pSnow->Daily_Sublimation_Or_Desublimation_mm);
  #else
     = 0.0;
  #endif
  pDaily_Soil_out->soil_evaporation               = cell->ref_soil()->get_act_evaporation(); //170624RLN pSoil->get_act_evaporation();  //(m) 160616LML
  pDaily_Soil_out->pond_evaporation               = cell->pond.get_evaporation_actual_day(); //(m) 160808RLN_160616LML
  pDaily_Soil_out->residue_evaporation            = organic_matter_residues_profile_kg_m2 ? organic_matter_residues_profile_kg_m2->ref_residues()->get_act_evaporation() : 0.0; //160616LML
  pDaily_Soil_out->Plant_Transpiration
     = current_crop ? current_crop->get_act_transpiration_m() :0;
  pDaily_Soil_out->Canopy_Interception
     = current_crop ? current_crop->get_intercepted_precipitation_m() : 0;
  pDaily_Soil_out->Daily_PET_MB =
     cell->meteorology.ref_ET_reference().get_m();                               //160801
     //160801 cell->ET_ref->get_m(ET_FAO_56_Penman_Monteith_CropSyst);                    //160606RLN
     //160606RLN   cell->soil->get_pot_evaporation();//160505 cell->pSoilState->Daily_PET_MB;                //160407LML
  pDaily_Soil_out->Daily_Runoff_Excess_Infiltration = cell->pSoilState->Daily_Runoff_infiltration_excess_m;
  pDaily_Soil_out->Daily_Surface_Runoff   = cell->get_m_from_m3(cell->output_flow_m3[TACUM_DAILY].SurfaceOut);
  pDaily_Soil_out->Daily_Surface_Runon    = cell->get_m_from_m3(cell->output_flow_m3[TACUM_DAILY].SurfaceIn);
  pDaily_Soil_out->Daily_Lateral_Runoff   = cell->get_m_from_m3(cell->output_flow_m3[TACUM_DAILY].LateralOut);
  pDaily_Soil_out->Daily_Lateral_Runon    = cell->get_m_from_m3(cell->output_flow_m3[TACUM_DAILY].LateralIn);
  pDaily_Soil_out->Daily_Lateral_Up       = cell->get_m_from_m3(cell->output_flow_m3[TACUM_DAILY].LateralUp);
  pDaily_Soil_out->NO3_N_Fertilization    = per_m2_to_per_ha(cell->nitrogen_daily_output.applied_inorganic_NO3_N); //160323LML pSoilState->Daily_Nitrate_N_Fertilization * 10000.0;
  pDaily_Soil_out->NH4_N_Fertilization    = per_m2_to_per_ha(cell->nitrogen_daily_output.applied_inorganic_NH4_N); //160323LML pSoilState->Daily_Ammonium_N_Fertilization * 10000.0;
  pDaily_Soil_out->org_N_Fertilization    = per_m2_to_per_ha(cell->nitrogen_daily_output.applied_organic);         //160323LML

#ifndef CROPSYST_CHEMICAL_TRANSPORT
  pDaily_Soil_out->Nitrate_Leaching       = cell->pSoilState->Daily_Nitrate_Leaching * 10000.;
  pDaily_Soil_out->Ammonium_Leaching      = cell->pSoilState->Daily_Ammonium_Leaching * 10000.;
#else
  pDaily_Soil_out->Nitrate_Leaching       = per_m2_to_per_ha(soil_chemicals ? (soil_chemicals->NO3->reported_leached_molecular * NO3_to_N_conv) : 0);
  pDaily_Soil_out->Ammonium_Leaching      = per_m2_to_per_ha(soil_chemicals ? (soil_chemicals->NH4->reported_leached_molecular * NH4_to_N_conv) : 0);
#endif
  pDaily_Soil_out->Drainage               = cell->get_m_from_m3(cell->output_flow_m3[TACUM_DAILY].Drainage);
  #ifdef MBVB_SNOW
  pDaily_Soil_out->Fraction_Cover_Snow    = cell->pSnow->Avg_Daily_Fraction_Cover_Snow;
  pDaily_Soil_out->Daily_Snow_Depth       = mm_to_m(cell->pSnow->Daily_Snow_Peak_Depth_mm);

  pDaily_Soil_out->Snow_Melt_Amount       = mm_to_m(cell->pSnow->Daily_Snow_Melt_Amount_mm);
  pDaily_Soil_out->Total_SWE              = mm_to_m(cell->pSnow->Current_Snow_Pack_SWE_mm);
  pDaily_Soil_out->Peak_SWE               = mm_to_m(cell->pSnow->Snow_Amount_Peak_Today_mm);
  pDaily_Soil_out->Avg_Snow_Surface_T     = cell->pSnow->Avg_Daily_Snow_Surface_T;
  //pDaily_Soil_out->Avg_Snow_Below_Surface_T = Soil.clsSnowRef.Avg_Daily_Snow_Below_Surface_T;
  #else
  pDaily_Soil_out->Fraction_Cover_Snow    = -9999;
  pDaily_Soil_out->Daily_Snow_Depth       = cell->meteorology_site.get_snow_pack() ? cell->meteorology_site.get_snow_pack()->ref_snow_pack_thickness() : 0;
  pDaily_Soil_out->Snow_Melt_Amount       = cell->meteorology_site.get_snow_pack() ? cell->meteorology_site.get_snow_pack()->get_melted() : 0;
  pDaily_Soil_out->Total_SWE              = cell->meteorology_site.get_snow_pack() ? cell->meteorology_site.get_snow_pack()->get_water_equivelent_depth() : 0;
  pDaily_Soil_out->Peak_SWE               = -9999;
  pDaily_Soil_out->Avg_Snow_Surface_T     = -9999;
  #endif
  pDaily_Soil_out->Precipitation_m        = cell->LAND_UNIT_SIM_ meteorology.ref_precipitation_actual().get_m();  //160414_151206RLN weather_provider->precipitation.get_mm() / 1000.0;
  pDaily_Soil_out->Mean_Temperature       = cell->LAND_UNIT_SIM_ meteorology.ref_air_temperature_avg().Celcius(); //151206 weather_provider->air_temperature_avg.Celcius();

  //LML 140829
  pDaily_Soil_out->Pond_m                 = cell->pSoilState->pond.ref_depth().get_m();
  //pDaily_Soil_out->Total_Snow_Amount;
  pDaily_Soil_out->Total_LiqW_m           = cell->pSoilState->getTotalSoilLiqWaterContent_m();
  pDaily_Soil_out->Total_Ice_m            = cell->pSoilState->getTotalSoilIceContent_m();
  if (organic_matter_residues_profile_kg_m2)                                     //151208RLN
  {  pDaily_Soil_out->AG_Residue_C_Mass      = per_m2_to_per_ha(organic_matter_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_RESIDUE_OM,0.0,true));
     pDaily_Soil_out->BG_Residue_C_Mass      = per_m2_to_per_ha(organic_matter_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_RESIDUE_OM,ENTIRE_PROFILE_DEPTH_as_9999,false));
     pDaily_Soil_out->SOM_C_Mass             = per_m2_to_per_ha(organic_matter_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_SOM_AND_MICROBIAL,ENTIRE_PROFILE_DEPTH_as_9999,false));
     pDaily_Soil_out->AG_Residue_N_Mass      = per_m2_to_per_ha(organic_matter_residues_profile_kg_m2->sum_nitrogen_to_depth_kg_m2(INCLUDE_RESIDUE_OM,0.0,true));
     pDaily_Soil_out->BG_Residue_N_Mass      = per_m2_to_per_ha(organic_matter_residues_profile_kg_m2->sum_nitrogen_to_depth_kg_m2(INCLUDE_RESIDUE_OM,ENTIRE_PROFILE_DEPTH_as_9999,false));
     pDaily_Soil_out->SOM_N_Mass             = per_m2_to_per_ha(organic_matter_residues_profile_kg_m2->sum_nitrogen_to_depth_kg_m2(INCLUDE_SOM_AND_MICROBIAL,ENTIRE_PROFILE_DEPTH_as_9999,false));
     pDaily_Soil_out->Profile_SOM_Carbon_Lost_As_CO2     = per_m2_to_per_ha(organic_matter_residues_profile_kg_m2->get_gaseous_CO2_C_loss_reported_daily(INCLUDE_SOM_AND_MICROBIAL));
     pDaily_Soil_out->Profile_Residue_Carbon_Lost_As_CO2 = per_m2_to_per_ha(organic_matter_residues_profile_kg_m2->get_gaseous_CO2_C_loss_reported_daily(INCLUDE_RESIDUE_OM));
  }
  if (soil_chemicals)                                                            //151208RLN
  {  pDaily_Soil_out->NO3_N_Mass             = per_m2_to_per_ha(soil_chemicals->sum_NO3_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)); //151208RLN
     pDaily_Soil_out->NH4_N_Mass             = per_m2_to_per_ha(soil_chemicals->sum_NH4_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)); //151208RLN
     pDaily_Soil_out->Profile_Mineral_N_Mass = pDaily_Soil_out->NO3_N_Mass + pDaily_Soil_out->NH4_N_Mass;  //170124LML
     pDaily_Soil_out->Top_One_Meter_Mineral_N_Mass = per_m2_to_per_ha(soil_chemicals->sum_NO3_to_depth(1.0,true))
                                                     + per_m2_to_per_ha(soil_chemicals->sum_NH4_to_depth(1.0,true));  //170124LML
  }
  if (current_crop) {
      pDaily_Soil_out->Maintenance_Respiration      = -9999.0;//151006LML NYI cell->pSoilState->Maintenance_Respiration;
      pDaily_Soil_out->Biosynthesis_Efficiency      = -9999.0;//151006LML NYI cell->pSoilState->Biosynthesi_Efficiency;
      pDaily_Soil_out->Gross_Canopy_Photosynthesis  = -9999.0;//151006LML NYI cell->pSoilState->Gross_Canopy_Photosynthesis;
      pDaily_Soil_out->CO2_by_Plant_Respiration     = -9999.0;//151006LML NYI cell->pSoilState->CO2_by_Plant_Respiration;
      pDaily_Soil_out->Biomass_Root_Today           = current_crop->get_act_root_biomass_kg_m2();
      pDaily_Soil_out->Biomass_Top_Today            = current_crop->get_canopy_biomass_kg_m2();
  } else {
      pDaily_Soil_out->Maintenance_Respiration      = 0.0;
      pDaily_Soil_out->Biosynthesis_Efficiency       = 0.0;
      pDaily_Soil_out->Gross_Canopy_Photosynthesis  = 0.0;
      pDaily_Soil_out->CO2_by_Plant_Respiration     = 0.0;
      pDaily_Soil_out->Biomass_Root_Today           = 0.0;
      pDaily_Soil_out->Biomass_Top_Today            = 0.0;
  }
  for (int s = 0; s < cell->ControlRef.getSoluteSpecies(); s++) {
      pDaily_Soil_out->dailyLateralInFlowSolute_kg[s] = cell->output_flow_solute_kg[s][TACUM_DAILY].LateralIn;
      pDaily_Soil_out->dailyLateralOutFlowSolute_kg[s] = cell->output_flow_solute_kg[s][TACUM_DAILY].LateralOut;
      pDaily_Soil_out->dailySurfaceInFlowSolute_kg[s] = cell->output_flow_solute_kg[s][TACUM_DAILY].SurfaceIn;
      pDaily_Soil_out->dailySurfaceOutFlowSolute_kg[s] = cell->output_flow_solute_kg[s][TACUM_DAILY].SurfaceOut;
  }

  //151028LML
  if (current_crop)
  {
     pDaily_Soil_out->Cumulative_Thermal_Time                      = current_crop->get_accum_degree_days(false);
     //pDaily_Soil_out->Potential_Cumulative_Biomass                 = -9999; //(t/ha)
     //pDaily_Soil_out->Actual_Cumulative_Biomass                    = kg_to_tonne(current_crop->get_canopy_biomass_kg_ha()); //(t/ha)
     //pDaily_Soil_out->Actual_Cumulative_Root_Biomass               = kg_to_tonne(current_crop->get_act_root_biomass_kg_ha()); //(t/ha)
     pDaily_Soil_out->Fraction_Solar_Rad_Intercepted_Green_Canopy
         = current_crop->get_intercepted_PAR_MJ_m2() /
         #ifdef CROPSYST_WEATHER
         gridcell_ref->meteorology.ref_solar_radiation().get_MJ_m2();            //160808RLN
         #else
         #ifdef CELL_METEOROLOGY
         gridcell_ref->pWeatherDaily->daily_provider.solar_radiation.get_MJ_m2(); // -9999;                          //LML 140826 Potential_Green_Area_Index;
         #else
         gridcell_ref->meteorology.ref_solar_radiation().get_MJ_m2();//160808RLN
         #endif
         #endif
     pDaily_Soil_out->Intercepted_Solar_Rad_MJ_m2                  = current_crop->get_intercepted_PAR_MJ_m2();
     pDaily_Soil_out->Green_Area_Index                             = current_crop->get_GAI(true);
     pDaily_Soil_out->Crop_Potential_Transpiration                 = current_crop->get_pot_transpiration_m(1);                    //(mm)

         // WARNING Mingliang check the units output here get_pot_transpiration_m is in meter 151208RLN

     pDaily_Soil_out->Actual_Nitrogen_Uptake                       = per_m2_to_per_ha(current_crop->get_nitrogen()->get_daily_uptake()); //(kgN/ha)
     pDaily_Soil_out->Water_Stress_Index                           = current_crop->get_water_stress_index() ;
     pDaily_Soil_out->Nitrogen_Stress_Index                        = current_crop->get_nitrogen()->get_stress_index_mean() ;
     pDaily_Soil_out->Temperature_Stress_Index                     = current_crop->get_temperature_stress_index();
     pDaily_Soil_out->Temperature_Stress_Index_Mean                = current_crop->get_temperature_stress_index_mean();
     pDaily_Soil_out->Temperature_Stress_Current                   = current_crop->get_temperature_stress();
     pDaily_Soil_out->Root_Depth                                   = current_crop->get_recorded_root_depth_m();                  //(m)
     //160322LML pDaily_Soil_out->yield                                        = cell->output_harvested_yield; //160322LML   per_m2_to_per_ha (kg_to_tonne(current_crop->get_latest_yield_kg_m2()));
  } else
  {
     pDaily_Soil_out->Cumulative_Thermal_Time                      = 0;
     //pDaily_Soil_out->Potential_Cumulative_Biomass                 = -9999; //(t/ha)
     //pDaily_Soil_out->Actual_Cumulative_Biomass                    = 0; //(t/ha)
     //pDaily_Soil_out->Actual_Cumulative_Root_Biomass               = 0; //(t/ha)
     pDaily_Soil_out->Fraction_Solar_Rad_Intercepted_Green_Canopy  = 0;                          //LML 140826 Potential_Green_Area_Index;
     pDaily_Soil_out->Intercepted_Solar_Rad_MJ_m2                  = 0;
     pDaily_Soil_out->Green_Area_Index                             = 0;
     pDaily_Soil_out->Crop_Potential_Transpiration                 = 0; //(mm)
     pDaily_Soil_out->Actual_Nitrogen_Uptake                       = 0; //(kgN/ha)
     pDaily_Soil_out->Water_Stress_Index                           = 0;
     pDaily_Soil_out->Nitrogen_Stress_Index                        = 0;
     pDaily_Soil_out->Root_Depth                                   = 0;                  //(m)
     //160322LML pDaily_Soil_out->yield                                        = 0;
  }
  pDaily_Soil_out->yield                                        = cell->output_harvested_yield; //160322LML   per_m2_to_per_ha (kg_to_tonne(current_crop->get_latest_yield_kg_m2()));
  cell->output_harvested_yield                                  = 0;             //160322LML
  if (soil_chemicals)                                                            //151208RLN
  {  pDaily_Soil_out->nitrification   = per_m2_to_per_ha(soil_chemicals->nitrification_N_E_output[0]); //(kgN/ha)
     pDaily_Soil_out->denitrification = per_m2_to_per_ha(soil_chemicals->denitrification_N_E_output[0]); //(kgN/ha)
     pDaily_Soil_out->mineralization  = per_m2_to_per_ha(organic_matter_residues_profile_kg_m2->get_soil_organic_matter_mineralization_profile_N()); //(kgN/ha)
  }
  pDaily_Soil_out->volatilization     = per_m2_to_per_ha(cell->LAND_UNIT_SIM_ nitrogen_daily_output.volatilization_total); //(kgNH4-N/ha)
  pDaily_Soil_out->N_N2O_loss         = per_m2_to_per_ha(soil_chemicals->NH4->get_N2O_loss() + soil_chemicals->NO3->get_N2O_loss());  //(kgN/ha) 170207LML

  Soil_Day_Sequence++;
  pDaily_Soil.push_back(*pDaily_Soil_out);
  delete pDaily_Soil_out; pDaily_Soil_out = 0;                                   //150722RLN
#endif
}
//______________________________________________________________________________
void OutputMainClass::WriteDailyGrowthOutput(/*clsSimulation &Simulation,clsCrop &Crop*/)
{
#ifndef CROPSYST_VERSION
    //OutputGrowthClass *pGrowth_out = &pGrowth[Growth_Day_Sequence];
    OutputGrowthClass *pGrowth_out = new OutputGrowthClass;
    CropStateClass &cropstate      = *Crop.pCropState;
    #ifdef CROPSYST_PROPER_CROP
    /*141005 RLN NYI
    pGrowth_out->Current_Year = Simulation.pTimeState->getToday().get_year();
    pGrowth_out->Current_DOY = Simulation.pTimeState->getToday().get_DOY();
    pGrowth_out->Crop_Name = Crop.pCropState->Crop_Name;
    pGrowth_out->Days_After_Crop_Planting = Simulation.pTimeState->getDaysAfterPlanting();
    pGrowth_out->Development_Stage = Crop.pCropState->Development_Stage;             //
    pGrowth_out->Cumulative_Thermal_Time = Crop.pCropState->Cumulative_Thermal_Time;
    pGrowth_out->Potential_Cumulative_Biomass = Crop.pCropState->Potential_Cumulative_Biomass * 10000.;    //kg/m2 ->kg/ha
    pGrowth_out->Actual_Cumulative_Biomass = Crop.pCropState->Cumulative_Biomass * 10000;
    pGrowth_out->Fraction_Solar_Rad_Intercepted_Green_Canopy = Crop.pCropState->Fraction_Solar_Rad_Intercepted_Green_Canopy;    //LML 140826
    pGrowth_out->Green_Area_Index = Crop.pCropState->Green_Area_Index_Today;
    pGrowth_out->Potential_Crop_Potential_Transpiration = mm_to_m(Crop.pCropState->Potential_Crop_Potential_Transpiration);
    pGrowth_out->Crop_Potential_Transpiration = mm_to_m(Crop.pCropState->Crop_Potential_Transpiration);
    pGrowth_out->Actual_Crop_Transpiration = mm_to_m(Crop.pCropState->Actual_Crop_Transpiration);
    pGrowth_out->Actual_Nitrogen_Uptake = Crop.pCropState->Actual_Nitrogen_Uptake * 10000.;
    pGrowth_out->Water_Stress_Index = Crop.pCropState->Water_Stress_Index;
    pGrowth_out->Top_Nitrogen_Stress_Index = Crop.pCropState->Top_Nitrogen_Stress_Index;
    pGrowth_out->Root_Nitrogen_Stress_Index = Crop.pCropState->Root_Nitrogen_Stress_Index;
    pGrowth_out->Root_Depth = Crop.pCropState->Root_Depth;
    */
    #else
    pGrowth_out->Current_Year                                   = Simulation.pTimeState->getToday().get_year();
    pGrowth_out->Current_DOY                                    = Simulation.pTimeState->getToday().get_DOY();
    pGrowth_out->Crop_Name                                      = cropstate.Crop_Name;
    pGrowth_out->Days_After_Crop_Planting                       = Simulation.pTimeState->getDaysAfterPlanting();
    pGrowth_out->Development_Stage                              = cropstate.Development_Stage;             //
    pGrowth_out->Cumulative_Thermal_Time                        = cropstate.Cumulative_Thermal_Time;
    pGrowth_out->Potential_Cumulative_Biomass                   = cropstate.Potential_Cumulative_Biomass * 10.;    //kg/m2 ->t/ha
    pGrowth_out->Actual_Cumulative_Biomass                      = cropstate.Cumulative_Biomass * 10;
    pGrowth_out->Fraction_Solar_Rad_Intercepted_Green_Canopy    = cropstate.Fraction_Solar_Rad_Intercepted_Green_Canopy;    //LML 140826
    pGrowth_out->Leaf_Area_Index                                = cropstate.Leaf_Area_Index;             //150601
    pGrowth_out->Green_Area_Index                               = cropstate.Green_Area_Index_Today;
    pGrowth_out->Potential_Crop_Potential_Transpiration         = cropstate.Potential_Crop_Potential_Transpiration;
    pGrowth_out->Crop_Potential_Transpiration                   = cropstate.Crop_Potential_Transpiration;
    pGrowth_out->Actual_Crop_Transpiration                      = cropstate.Actual_Crop_Transpiration;
    pGrowth_out->Actual_Nitrogen_Uptake                         = cropstate.Actual_Nitrogen_Uptake * 10000.;
    pGrowth_out->Water_Stress_Index                             = cropstate.Water_Stress_Index;
    pGrowth_out->Top_Nitrogen_Stress_Index                      = cropstate.Top_Nitrogen_Stress_Index;
    pGrowth_out->Root_Nitrogen_Stress_Index                     = cropstate.Root_Nitrogen_Stress_Index;
    pGrowth_out->Root_Depth                                     = cropstate.Root_Depth;
    #endif
    pGrowth.push_back(*pGrowth_out);
    Growth_Day_Sequence++;
#endif
}
//______________________________________________________________________________
void OutputMainClass::WriteHourlyOutput(const int current_hour)
{
#ifndef CROPSYST_VERSION
    int hour_index = cell->pSimulation->pTimeState->getHourOfDay();
    const int numlayers = cell->pSoilProfile->NumberOfLayers() + 1; //LML 150205 Node_Depth need [layer+1]
    //if (cell->pSimulation->pTimeState->getToday().get_DOY() == 1)
    //    pHour.clear();  //LML 150205 at the beginning of year, clear all hourly output
    //LML 150222 now after print the vector will be cleared.
    OutputHourClass *pHour_out = new OutputHourClass;
    
    pHour_out->Current_Year = cell->pSimulation->pTimeState->getToday().get_year();
    pHour_out->Current_DOY = cell->pSimulation->pTimeState->getToday().get_DOY();
    pHour_out->Current_Hour = cell->pSimulation->pTimeState->getHourOfDay();
    if (!pHour_out->b_set_vector_size) { //LML 150205
        pHour_out->Node_Depth.resize(numlayers,0);
        pHour_out->Layer_Water_Content.resize(numlayers,0);
        pHour_out->Layer_Ice_Content.resize(numlayers,0);
        pHour_out->Layer_Temperature.resize(numlayers,0);
        pHour_out->Layer_Nitrate_N_Mass.resize(numlayers,0);    
        pHour_out->Layer_Nitrate_N_Conc.resize(numlayers,0);    
        pHour_out->Layer_Ammonium_N_Mass.resize(numlayers,0);
        pHour_out->Layer_Ammonium_N_Conc.resize(numlayers,0);
        pHour_out->b_set_vector_size = true;
    }
    for (int layer = 1; layer <= cell->pSoilProfile->NumberOfLayers(); layer++) {
        pHour_out->Node_Depth[layer] = (cell->pSoilProfile->Node_Depth[layer] 
                                        + cell->pSoilProfile->Node_Depth[layer+1])
                                        / 2.0;
        pHour_out->Layer_Water_Content[layer] = 
                cell->pSoilState->get_liquid_water_content_volumetric(layer);/*LML 140611 Hourly_Water_Content[layer]*/;
        pHour_out->Layer_Ice_Content[layer] = cell->pSoilState->Ice_Content[layer];                 //LML 140814
        pHour_out->Layer_Temperature[layer] = cell->pSoilState->Soil_Temperature[hour_index][layer];//LML 140814
        pHour_out->Layer_Nitrate_N_Mass[layer] = cell->pSoilState->Layer_Nitrate_N_Mass[layer];     //(kg/m2)
        pHour_out->Layer_Nitrate_N_Conc[layer] = cell->pSoilState->Layer_Nitrate_N_Conc[layer];     //(kg/m3)
        pHour_out->Layer_Ammonium_N_Mass[layer] = cell->pSoilState->Layer_Ammonium_N_Mass[layer];     //(kg/m2)
        pHour_out->Layer_Ammonium_N_Conc[layer] = cell->pSoilState->Layer_Ammonium_N_Conc[layer];     //(kg/m3)
    }
    pHour_out->Prec_Irrig_SnowMelt_m = cell->pSoilState->Hourly_Prec_Irrig_SnowMelt_m;
    pHour_out->Ponded_Water = cell->pond.get_depth();                             //pSoilState->Hourly_Ponded_Water_m;
    pHour_out->Runoff = cell->pSoilState->Hourly_Runoff_infiltration_excess_m;      //Hourly_Runoff_m;
    pHour_out->Drainage = cell->pSoilState->Hourly_Drainage_m;
    pHour_out->Evaporation = cell->pSoilState->Hourly_Soil_Water_Evaporation_m;   
    #ifdef MBVB_FD
    pHour_out->FD_Water_Balance = cell->pSoilProcess->Finite_Difference_Error_mm;
    #else
        #ifdef CROPSYST_FD
        cell->pSoilProcess->infiltration_finite_difference                       //140527RLN
            ? cell->pSoilProcess->infiltration_finite_difference->daily_error    //140527RLN
            : 0.0;
        #endif
    #endif
    pHour_out->Temperature = cell->pWeatherDaily->getHourlyTemperature(hour_index);
    pHour_out->Precipitation = mm_to_m(cell->pWeatherDaily->getHourlyPrecipitation(hour_index));
    pHour_out->Fraction_Cover_Snow = cell->pSnow->Fraction_Cover_Snow[hour_index];
    pHour_out->Snow_Water_Equavalent = mm_to_m(cell->pSnow->Hourly_Snow_Pack_SWE[hour_index]);     //LML 04/05/02
    pHour_out->Snow_Melt = mm_to_m(cell->pSnow->Hourly_Snow_Melt_Amount[hour_index]);
    pHour_out->Sublimation = mm_to_m(cell->pSnow->Hourly_Sublimation_mm[hour_index]);              //LML 04/05/02
    pHour_out->Sat_Boundary =
    #ifdef MBVB_FD
        cell->pSoilProcess->Sat_BC;
    #else
        /* 140527 Status is currently not accessable
        cell->pSoilProcess->infiltration_finite_difference                       //140527RLN
            ? cell->pSoilProcess->infiltration_finite_difference->               //140527RLN
              FD_status == Soil_infiltration_finite_difference::SATURATED_BOUNDARY :
        */
             false;                                                             //140527RLN
    #endif
    /*150825LML obs.
    pHour_out->hourlySurfaceOutFlow_m3 = cell->hourlySurfaceOutFlow_m3;
    pHour_out->hourlySurfaceInFlow_m3 = cell->hourlySurfaceInFlow_m3;
    pHour_out->hourlyDrainage_m3 = cell->get_m3_from_m(pHour_out->Drainage);//cell->hourlyDrainage_m3;
    pHour_out->hourlyLateralInFlow_m3 = cell->hourlyLateralInFlow_m3;
    pHour_out->hourlyLateralOutFlow_m3 = cell->hourlyLateralOutFlow_m3; ;
    pHour_out->hourlyLateralUpFlow_m3 = cell->hourlyLateralUpFlow_m3;
    //std::cout<<" Hour_Sequence:"<<Hour_Sequence
            //<<" hourlyLateralInFlowSolute_kg:" <<pHour[Hour_Sequence].hourlyLateralInFlowSolute_kg[0]
              //<<std::endl;
    for (int s = 0; s < cell->ControlRef.getSoluteSpecies(); s++) {
        pHour_out->hourlyLateralInFlowSolute_kg[s] = cell->hourlyLateralInFlowSolute_kg[s];
        pHour_out->hourlyLateralOutFlowSolute_kg[s] = cell->hourlyLateralOutFlowSolute_kg[s];
        pHour_out->hourlySurfaceInFlowSolute_kg[s] = cell->hourlySurfaceInFlowSolute_kg[s];
        pHour_out->hourlySurfaceOutFlowSolute_kg[s] = cell->hourlySurfaceOutFlowSolute_kg[s];
    }
    */

    Hour_Sequence++;
    pHour.push_back(*pHour_out);
    delete pHour_out; pHour_out = 0;
#else
  int hour_index = current_hour;
  BasinCellClass *cell = gridcell_ref;
  const int numlayers = cell->pSoilProfile->NumberOfLayers() + 1; //LML 150205 Node_Depth need [layer+1]
  //if (cell->pSimulation->pTimeState->getToday().get_DOY() == 1)
  //    pHour.clear();  //LML 150205 at the beginning of year, clear all hourly output
  //LML 150222 now after print the vector will be cleared.
  OutputHourClass *pHour_out = new OutputHourClass;

  pHour_out->Current_Year = today.get_year();
  pHour_out->Current_DOY = today.get_DOY();
  pHour_out->Current_Hour = current_hour;
  if (!pHour_out->b_set_vector_size) { //LML 150205
      pHour_out->Node_Depth.resize(numlayers,0);
      pHour_out->Layer_Water_Content.resize(numlayers,0);
      pHour_out->Layer_Ice_Content.resize(numlayers,0);
      pHour_out->Layer_Temperature.resize(numlayers,0);
      pHour_out->Layer_Nitrate_N_Mass.resize(numlayers,0);
      pHour_out->Layer_Nitrate_N_Conc.resize(numlayers,0);
      pHour_out->Layer_Ammonium_N_Mass.resize(numlayers,0);
      pHour_out->Layer_Ammonium_N_Conc.resize(numlayers,0);
      pHour_out->b_set_vector_size = true;
  }
  for (int layer = 1; layer <= cell->pSoilProfile->NumberOfLayers(); layer++) {
      pHour_out->Node_Depth[layer] = (cell->pSoilProfile->Node_Depth[layer]
                                      + cell->pSoilProfile->Node_Depth[layer+1])
                                      / 2.0;
      pHour_out->Layer_Water_Content[layer] =
              cell->pSoilState->get_liquid_water_content_volumetric(layer);      //140611LML;
      pHour_out->Layer_Ice_Content[layer] = cell->pSoilState->Ice_Content[layer];//140814LML
      pHour_out->Layer_Temperature[layer] =
         #ifdef MBVB_SOIL_TEMPERATURE
            cell->pSoilState->Soil_Temperature[hour_index][layer];//140814LML
         #else
            9999.9; //160721 Roger needs to provide
         #endif
      pHour_out->Layer_Nitrate_N_Mass[layer] = cell->LAND_UNIT_SIM_ get_soil_chemicals()->get_NO3_N_mass_kg_m2(layer);     //(kg/m2)
      //pHour_out->Layer_Nitrate_N_Conc[layer] = cell->pSoilState->Layer_Nitrate_N_Conc[layer];     //(kg/m3)
      pHour_out->Layer_Ammonium_N_Mass[layer] = cell->LAND_UNIT_SIM_ get_soil_chemicals()->get_NH4_N_mass_kg_m2(layer);     //(kg/m2)
      //pHour_out->Layer_Ammonium_N_Conc[layer] = cell->pSoilState->Layer_Ammonium_N_Conc[layer];     //(kg/m3)
  }
  pHour_out->Prec_Irrig_SnowMelt_m = cell->pSoilState->Hourly_Prec_Irrig_SnowMelt_m;
  pHour_out->Ponded_Water = cell->pond.get_depth();                             //pSoilState->Hourly_Ponded_Water_m;
  pHour_out->Runoff = cell->pSoilState->Hourly_Runoff_infiltration_excess_m;      //Hourly_Runoff_m;
  pHour_out->Drainage = cell->pSoilState->Hourly_Drainage_m;
  pHour_out->Evaporation = cell->pSoilState->Hourly_Soil_Water_Evaporation_m;
  #ifdef MBVB_FD
  pHour_out->FD_Water_Balance = cell->pSoilProcess->Finite_Difference_Error_mm;
  #else
      #ifdef CROPSYST_FD
      cell->pSoilProcess->infiltration_finite_difference                       //140527RLN
          ? cell->pSoilProcess->infiltration_finite_difference->daily_error    //140527RLN
          : 0.0;
      #endif
  #endif
  #ifdef CROPSYST_WEATHER
  pHour_out->Temperature = mm_to_m(cell->meteorology.provide_hourly()->get_air_temperature(hour_index));
  pHour_out->Precipitation = mm_to_m(999 /*NYI cell->pWeatherDaily->getHourlyPrecipitation(hour_index)*/);

     // need to get the precipitation in intervals

  #else
  #ifdef CELL_METEOROLOGY
  pHour_out->Temperature = cell->pWeatherDaily->getHourlyTemperature(hour_index);
  pHour_out->Precipitation = mm_to_m(cell->pWeatherDaily->getHourlyPrecipitation(hour_index));
  #else
/*NYI  RLN
  pHour_out->Temperature = cell->meteorology.provide_hourly().get_air_temperature(hour_index);
  pHour_out->Precipitation = mm_to_m( cell->pWeatherDaily->getHourlyPrecipitation(hour_index));
*/
    #endif
  #endif
  #ifdef MBVB_SNOW
  pHour_out->Fraction_Cover_Snow = cell->pSnow->Fraction_Cover_Snow[hour_index];
  pHour_out->Snow_Water_Equavalent = mm_to_m(cell->pSnow->Hourly_Snow_Pack_SWE[hour_index]); //120504LML
  pHour_out->Snow_Melt = mm_to_m(cell->pSnow->Hourly_Snow_Melt_Amount[hour_index]);
  pHour_out->Sublimation = mm_to_m(cell->pSnow->Hourly_Sublimation_mm[hour_index]);          //120504LML
  #endif
  pHour_out->Sat_Boundary =
  #ifdef MBVB_FD
      cell->pSoilProcess->Sat_BC;
  #else
      /* 140527 Status is currently not accessable
      cell->pSoilProcess->infiltration_finite_difference                         //140527RLN
          ? cell->pSoilProcess->infiltration_finite_difference->               //140527RLN
            FD_status == Soil_infiltration_finite_difference::SATURATED_BOUNDARY :
      */
           false;                                                                //140527RLN
  #endif
  //*150825LML obs.
  pHour_out->hourlySurfaceOutFlow_m3 = cell->hourly_flow_m3.SurfaceOut;
  pHour_out->hourlySurfaceInFlow_m3 = cell->hourly_flow_m3.SurfaceIn;
  pHour_out->hourlyDrainage_m3 = cell->hourly_flow_m3.Drainage;
  pHour_out->hourlyLateralInFlow_m3 = cell->hourly_flow_m3.LateralIn;
  pHour_out->hourlyLateralOutFlow_m3 = cell->hourly_flow_m3.LateralOut; ;
  pHour_out->hourlyLateralUpFlow_m3 = cell->hourly_flow_m3.LateralUp;
  //std::cout<<" Hour_Sequence:"<<Hour_Sequence
          //<<" hourlyLateralInFlowSolute_kg:" <<pHour[Hour_Sequence].hourlyLateralInFlowSolute_kg[0]
            //<<std::endl;
  for (int s = 0; s < cell->ControlRef.getSoluteSpecies(); s++) {
      pHour_out->hourlyLateralInFlowSolute_kg[s] = cell->hourly_flow_solute_kg[s].LateralIn;
      pHour_out->hourlyLateralOutFlowSolute_kg[s] = cell->hourly_flow_solute_kg[s].LateralOut;
      pHour_out->hourlySurfaceInFlowSolute_kg[s] = cell->hourly_flow_solute_kg[s].SurfaceIn;
      pHour_out->hourlySurfaceOutFlowSolute_kg[s] = cell->hourly_flow_solute_kg[s].SurfaceOut;
  }
  //*/
  Hour_Sequence++;
  pHour.push_back(*pHour_out);
  delete pHour_out; pHour_out = 0;                                               //151006LML
#endif
}
//______________________________________________________________________________
void OutputMainClass::WriteAnnualSoilOutput()
{
    OutputAnnualClass *pAnnual_out = new OutputAnnualClass;
    BasinCellClass *cell = gridcell_ref;
    SoilStateClass *psoilstate = cell->pSoilState;
    Soil_chemicals_profile *soil_chemicals = cell->LAND_UNIT_SIM_ get_soil_chemicals();//151208RLN
    Organic_matter_residues_profile_abstract *OM_residues_profile_kg_m2          //151208RLN
       = cell->LAND_UNIT_SIM_ organic_matter_residues_profile_kg_m2;             //151208RLN
    const CropSyst::Land_unit_simulation &landunit = *gridcell_ref;
    const CropSyst::Period_accumulators &AN_accumulator = *landunit.ANNL_accumulators_active;
    
    if(landunit.ANNL_accumulators_active == 0) std::clog << "landunit.ANNL_accumulators_active isnot initilized!\n";

    #ifdef CROPSYST_VERSION
    pAnnual_out->Current_Year       = cell->ref_today().get_year();
    pAnnual_out->Precipitation      = psoilstate->Annual_Precipitation_m;        //161101LML
    pAnnual_out->Potential_ET       = AN_accumulator.pot_evapotranspiration;
    pAnnual_out->Actual_ET          = psoilstate->Annual_Actual_Crop_Transpiration_m
                                    + psoilstate->Annual_Actual_Soil_Evaporation_m;   //160119LML NEED CHECK!!!
    pAnnual_out->Soil_Residue_Evap  = psoilstate->Annual_Actual_Soil_Evaporation_m;   //160119LML NEED CHECK!!!
    pAnnual_out->Transpiration      = psoilstate->Annual_Actual_Crop_Transpiration_m;
    pAnnual_out->Irrigation         = psoilstate->Annual_Irrigation_m;
    pAnnual_out->Drainage           = psoilstate->Annual_Drainage_m;
    if (OM_residues_profile_kg_m2)                                               //151208RLN
    {
        pAnnual_out->Profile_SOM_Carbon_Mass    = per_m2_to_per_ha(OM_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_SOM_AND_MICROBIAL,ENTIRE_PROFILE_DEPTH_as_9999,false));
        pAnnual_out->Profile_SOM_Nitrogen_Mass  = per_m2_to_per_ha(OM_residues_profile_kg_m2->sum_nitrogen_to_depth_kg_m2(INCLUDE_SOM_AND_MICROBIAL,ENTIRE_PROFILE_DEPTH_as_9999,false));
        pAnnual_out->Profile_Residue_Carbon_Mass    = per_m2_to_per_ha
           ( OM_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_RESIDUE_OM,0.0,true)
           + OM_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_RESIDUE_OM,ENTIRE_PROFILE_DEPTH_as_9999,false));
        pAnnual_out->Profile_Residue_Nitrogen_Mass  = per_m2_to_per_ha
           ( OM_residues_profile_kg_m2->sum_nitrogen_to_depth_kg_m2(INCLUDE_RESIDUE_OM,0.0,true)
           + OM_residues_profile_kg_m2->sum_nitrogen_to_depth_kg_m2(INCLUDE_RESIDUE_OM,ENTIRE_PROFILE_DEPTH_as_9999,false));
        pAnnual_out->SOM_Carbon_Lost_As_CO2         = per_m2_to_per_ha(AN_accumulator.gaseous_CO2_C_loss_SOM);
        pAnnual_out->Residue_Carbon_Lost_As_CO2     = per_m2_to_per_ha(AN_accumulator.gaseous_CO2_C_loss_residue);
        pAnnual_out->Last_Day_Of_Year_Total_Aboveground_Residue_Carbon_Mass = per_m2_to_per_ha
           ( OM_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_RESIDUE_OM,0.0,true));
        pAnnual_out->Last_Day_Of_Year_Total_Aboveground_Residue_Nitrogen_Mass = per_m2_to_per_ha
           ( OM_residues_profile_kg_m2->sum_nitrogen_to_depth_kg_m2(INCLUDE_RESIDUE_OM,0.0,true));
        if (soil_chemicals)                                                      //160121RLN
        {  NO3_Profile *soil_NO3 = soil_chemicals->NO3;
           if (soil_NO3)
           {  Chemical_balance_accumulators *soil_NO3_ANNL_accums = soil_NO3->ANNL_bal_accums;
              if (soil_NO3_ANNL_accums)
              {  //160405LML pAnnual_out->Nitrate_N_Fertilization = per_m2_to_per_ha(soil_NO3_ANNL_accums->get_applied(true));
                 //160405LML pAnnual_out->Denitrification         = per_m2_to_per_ha(soil_NO3_ANNL_accums->get_transformed_to(true));
                 //160405LML pAnnual_out->Nitrate_N_Leaching       = per_m2_to_per_ha(soil_NO3_ANNL_accums->get_reported_leached(true));
                 pAnnual_out->Nitrate_N_Fertilization = per_m2_to_per_ha(psoilstate->Annual_Nitrate_N_Fertilization); //160405LML
                 pAnnual_out->Denitrification         = per_m2_to_per_ha(psoilstate->Annual_Denitrification);
                 pAnnual_out->Nitrate_N_Leaching      = per_m2_to_per_ha(psoilstate->Annual_Nitrate_Leaching);
              }
           }
           NH4_Profile *soil_NH4 = soil_chemicals->NH4;                          //160121RLN
           Chemical_balance_accumulators *soil_NH4_ANNL_accums = soil_NH4->ANNL_bal_accums;
           if (soil_NH4)
           {  //160405LML pAnnual_out->Ammonium_N_Fertilization   = per_m2_to_per_ha(soil_NH4_ANNL_accums->get_applied(true));
              //160405LML pAnnual_out->Ammonium_N_Leaching        = per_m2_to_per_ha(soil_NH4_ANNL_accums->get_reported_leached(true));
              //160405LML pAnnual_out->Nitrification              = per_m2_to_per_ha(soil_NH4_ANNL_accums->get_transformed_to(true));
              pAnnual_out->Nitrification              = per_m2_to_per_ha(psoilstate->Annual_Nitrification);
              pAnnual_out->Ammonium_N_Fertilization   = per_m2_to_per_ha(psoilstate->Annual_Ammonium_N_Fertilization);
              pAnnual_out->Ammonium_N_Leaching        = per_m2_to_per_ha(psoilstate->Annual_Ammonium_Leaching);
           }
        }
        //pAnnual_out->Nuptake                    = per_m2_to_per_ha(AN_accumulator.N_uptake);
        pAnnual_out->Nuptake                    = per_m2_to_per_ha(psoilstate->Annual_N_uptake);
        pAnnual_out->Organic_N_Fertilization    = per_m2_to_per_ha(AN_accumulator.organic_N_applied);
        pAnnual_out->N_Mineralization           = per_m2_to_per_ha(AN_accumulator.OM_N_mineralization);//residue + SOM
        pAnnual_out->N_Immobilization           = per_m2_to_per_ha(AN_accumulator.N_immobilization);  //160405LML
        pAnnual_out->Ammonia_N_Mass_Volatilization = per_m2_to_per_ha(AN_accumulator.NH3_volatilization_loss + AN_accumulator.inorganic_NH4_to_atmosphere);  //160405LML
        pAnnual_out->N2O_Loss_denitrification   = per_m2_to_per_ha(AN_accumulator.N2O_loss_denitrification);
        pAnnual_out->N2O_Loss_nitrification     = per_m2_to_per_ha(AN_accumulator.N2O_loss_nitrification);
        pAnnual_out->N2O_Loss                   = per_m2_to_per_ha(AN_accumulator.N2O_loss_denitrification + AN_accumulator.N2O_loss_nitrification);
        pAnnual_out->plant_Carbon_Mass_Canopy   = per_m2_to_per_ha(AN_accumulator.plant_C_mass_canopy);
        //pAnnual_out->Ammonia_N_Mass_Volatilization;
    }
    if (soil_chemicals)                                                          //151208RLN
    {
        pAnnual_out->Profile_NH4_Nitrogen_Mass  = per_m2_to_per_ha (soil_chemicals->sum_NH4_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)); //151208RLN
        pAnnual_out->Profile_NO3_Nitrogen_Mass  = per_m2_to_per_ha (soil_chemicals->sum_NO3_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)); //151208RLN
        pAnnual_out->Surface_NH4_N_Mass         = per_m2_to_per_ha (soil_chemicals->NH4->get_surface_mass() * NH4_to_N_conv);   //170510LML
        pAnnual_out->Surface_NO3_N_Mass         = per_m2_to_per_ha (soil_chemicals->NO3->get_surface_mass() * NO3_to_N_conv);   //170510LML
        double total_cell_kg_to_kg_per_ha = 1.0 / cell->getArea() * 10000.;
        pAnnual_out->Surface_Runon_NO3_kgN_ha      = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Nitrate][TACUM_ANNUAL].SurfaceIn * NO3_to_N_conv;
        pAnnual_out->Surface_Runon_NH4_kgN_ha      = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Ammonia][TACUM_ANNUAL].SurfaceIn * NH4_to_N_conv;
        pAnnual_out->Lateral_Runon_NO3_kgN_ha      = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Nitrate][TACUM_ANNUAL].LateralIn * NO3_to_N_conv;
        pAnnual_out->Lateral_Runon_NH4_kgN_ha      = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Ammonia][TACUM_ANNUAL].LateralIn * NH4_to_N_conv;
        pAnnual_out->Total_Runon_NO3_kgN_ha        = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Nitrate][TACUM_ANNUAL].get_total_In() * NO3_to_N_conv;
        pAnnual_out->Total_Runon_NH4_kgN_ha        = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Ammonia][TACUM_ANNUAL].get_total_In() * NH4_to_N_conv;
        pAnnual_out->Surface_Runoff_NO3_kgN_ha     = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Nitrate][TACUM_ANNUAL].SurfaceOut * NO3_to_N_conv;
        pAnnual_out->Surface_Runoff_NH4_kgN_ha     = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Ammonia][TACUM_ANNUAL].SurfaceOut * NH4_to_N_conv;
        pAnnual_out->Lateral_Runoff_NO3_kgN_ha     = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Nitrate][TACUM_ANNUAL].LateralOut * NO3_to_N_conv;
        pAnnual_out->Lateral_Runoff_NH4_kgN_ha     = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Ammonia][TACUM_ANNUAL].LateralOut * NH4_to_N_conv;
        pAnnual_out->Total_Runoff_NO3_kgN_ha       = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Nitrate][TACUM_ANNUAL].get_total_Out() * NO3_to_N_conv;
        pAnnual_out->Total_Runoff_NH4_kgN_ha       = total_cell_kg_to_kg_per_ha * cell->output_flow_solute_kg[SL_Ammonia][TACUM_ANNUAL].get_total_Out() * NH4_to_N_conv;
        //170414LML pAnnual_out->Drainage_NO3_kgN           = cell->output_flow_solute_kg[SL_Nitrate][TACUM_ANNUAL].Drainage;
        //170414LML pAnnual_out->Darinage_NH4_kgN           = cell->output_flow_solute_kg[SL_Ammonia][TACUM_ANNUAL].Drainage;
        pAnnual_out->Initial_Profile_NO3_N      = cell->report_Initial_Profile_NO3_N;     //170413LML
        pAnnual_out->Initial_Profile_NH4_N      = cell->report_Initial_Profile_NH4_N;     //170413LML
        pAnnual_out->Initial_Surface_NH4_N      = cell->report_Initial_Surface_NH4_N;     //170510LML
        pAnnual_out->Initial_Surface_NO3_N      = cell->report_Initial_Surface_NO3_N;     //170510LML
    }
    pAnnual_out->Surface_Runon_m3               = cell->output_flow_m3[TACUM_ANNUAL].SurfaceIn;
    pAnnual_out->Lateral_Runon_m3               = cell->output_flow_m3[TACUM_ANNUAL].LateralIn;
    pAnnual_out->Total_Runon_m3                 = cell->output_flow_m3[TACUM_ANNUAL].get_total_In();
    pAnnual_out->Surface_Runoff_m3              = cell->output_flow_m3[TACUM_ANNUAL].SurfaceOut;
    pAnnual_out->Lateral_Runoff_m3              = cell->output_flow_m3[TACUM_ANNUAL].LateralOut;
    pAnnual_out->Total_Runoff_m3                = cell->output_flow_m3[TACUM_ANNUAL].get_total_Out();
    pAnnual_out->Drainage_m3                    = cell->output_flow_m3[TACUM_ANNUAL].Drainage;
    int num_layers = cell->pSoilProfile->NumberOfLayers();
    for (int L = 1; L <= num_layers; L++) {
      pAnnual_out->Last_Day_Of_Year_Layer_Water_Content[L]     = cell->pSoilState->get_liquid_water_content_volumetric(L);
      pAnnual_out->Last_Day_Of_Year_Layer_Ice_Content[L]       = cell->pSoilState->Ice_Content[L];
      if (soil_chemicals)                                                        //151208RLN
      {  pAnnual_out->Last_Day_Of_Year_Layer_Nitrate_N_Mass[L]    = soil_chemicals->get_NO3_N_mass_kg_ha(L); //151208RLN
         pAnnual_out->Last_Day_Of_Year_Layer_Ammonium_N_Mass[L]   = soil_chemicals->get_NH4_N_mass_kg_ha(L); //151208RLN
      }
    }
    #else
    pAnnual_out->Current_Year = Simulation.pTimeState->getToday().get_year();
    pAnnual_out->Nitrate_N_Fertilization = 
            Soil.pSoilState->Cumulative_Nitrate_N_Fertilization * 10000.;
    pAnnual_out->Ammonium_N_Fertilization = 
            Soil.pSoilState->Cumulative_Ammonium_N_Fertilization * 10000.;
    pAnnual_out->Organic_N_Fertilization = 
            Soil.pSoilState->Cumulative_Organic_N_Fertilization * 10000.;
    pAnnual_out->Nitrate_N_Fertigation = 
            Soil.pSoilState->Cumulative_Nitrate_N_Fertigation * 10000.;
    pAnnual_out->Ammonium_N_Fertigation = 
            Soil.pSoilState->Cumulative_Ammonium_N_Fertigation * 10000.;
    pAnnual_out->Nitrate_Leaching = 
            Soil.pSoilState->Cumulative_Nitrate_Leaching * 10000.;
    pAnnual_out->Ammonium_Leaching = 
            Soil.pSoilState->Cumulative_Ammonium_Leaching * 10000.;
    pAnnual_out->Drainage = 
            Soil.pSoilState->Cumulative_Drainage;
    pAnnual_out->Water_Balance = 
            BalanceRef.Cumulative_Water_Balance;
    pAnnual_out->Nitrate_Balance = 
            BalanceRef.Cumulative_Nitrate_Balance * 10000.;
    pAnnual_out->Ammonium_Balance = 
            BalanceRef.Cumulative_Ammonium_Balance * 10000.;
    pAnnual_out->Organic_Matter_Carbon_Balance = 
            BalanceRef.Cumulative_Organic_Matter_Carbon_Balance * 10000.;
    pAnnual_out->Organic_Matter_Nitrogen_Balance = 
            BalanceRef.Cumulative_Organic_Matter_Nitrogen_Balance * 10000.;
    pAnnual_out->Residue_Carbon_Balance = 
            BalanceRef.Cumulative_Organic_Residue_Carbon_Balance * 10000.;
    pAnnual_out->Residue_Nitrogen_Balance = 
            BalanceRef.Cumulative_Organic_Residue_Nitrogen_Balance * 10000.;
    pAnnual_out->Profile_SOM_Carbon_Mass = 
            Soil.pSoilState->Profile_SOM_Carbon_Mass * 10000.;    //End of year
    pAnnual_out->Profile_SOM_NitrogenMass = 
            Soil.pSoilState->Profile_SOM_Nitrogen_Mass * 10000.;
    /*
    pAnnual_out->Top5cm_SOM_Carbon_Mass = 
            Soil.pSoilState->Top_5cm_SOM_Carbon_Mass * 10000.;
    pAnnual_out->Top30cm_Soil_Carbon_Mass = 
            Soil.pSoilState->Top_30cm_Soil_Carbon_Mass * 10000.;
    */
    pAnnual_out->Profile_Residue_Carbon_Mass = 
            Soil.pSoilState->Profile_Residue_Carbon_Mass * 10000.;
    pAnnual_out->Profile_Residue_Nitrogen_Mass = 
            Soil.pSoilState->Profile_Residue_Nitrogen_Mass * 10000.;
    pAnnual_out->OM_Mineralization = 
            Soil.pSoilState->Cumulative_Profile_OM_Mineralization * 10000.;
    pAnnual_out->Residue_Mineralization = 
            Soil.pSoilState->Cumulative_Profile_Residue_Mineralization * 10000.;
    pAnnual_out->Nitrogen_Immobilization = 
            Soil.pSoilState->Cumulative_Profile_Nitrogen_Immobilization * 10000.;
    pAnnual_out->Nitrification = 
            Soil.pSoilState->Cumulative_Profile_Nitrification * 10000.;
    pAnnual_out->Denitrification = 
            Soil.pSoilState->Cumulative_Profile_Denitrification * 10000.;
    pAnnual_out->N2O_Loss = 
            Soil.pSoilState->Cumulative_Profile_N2O_Loss * 10000.;
    pAnnual_out->Ammonia_N_Mass_Volatilization = 
            Soil.pSoilState->Cumulative_Ammonia_N_Mass_Volatilization * 10000.;
    pAnnual_out->Last_Day_Of_Year_Standing_Stubble_Carbon_Mass = 
            Soil.pOrganicResidueState->Standing_Stubble_Carbon_Mass * 10000.;
    pAnnual_out->Last_Day_Of_Year_Surface_Residue_Carbon_Mass = 
            Soil.pOrganicResidueState->Surface_Residue_Carbon_Mass * 10000.;
    pAnnual_out->Last_Day_Of_Year_Soil_Residue_Carbon_Mass = 
            Soil.pOrganicResidueState->Soil_Residue_Carbon_Mass * 10000.;
    pAnnual_out->Last_Day_Of_Year_Cumulative_Decomposed_Standing_Stubble_Carbon_Mass = 
            Soil.pOrganicResidueState->Cumulative_Decomposed_Standing_Stubble_Carbon_Mass * 10000.;
    pAnnual_out->Last_Day_Of_Year_Cumulative_Decomposed_Surface_Residue_Carbon_Mass = 
            Soil.pOrganicResidueState->Cumulative_Decomposed_Surface_Residue_Carbon_Mass * 10000.;
    pAnnual_out->Last_Day_Of_Year_Cumulative_Decomposed_Soil_Residue_Carbon_Mass = 
            Soil.pOrganicResidueState->Cumulative_Decomposed_Soil_Residue_Carbon_Mass * 10000.;
    pAnnual_out->SOM_Carbon_Lost_As_CO2 = 
            Soil.pSoilState->Cumulative_Profile_SOM_Carbon_Lost_As_CO2 * 10000.;
    pAnnual_out->Residue_Carbon_Lost_As_CO2 = 
            Soil.pSoilState->Cumulative_Profile_Residue_Carbon_Lost_As_CO2 * 10000.;
    #endif
    Annual_Sequence++;
    pAnnual.push_back(*pAnnual_out);
    delete pAnnual_out; pAnnual_out = 0;
}
//______________________________________________________________________________
int OutputMainClass::getHourSequence()         {return Hour_Sequence;}
int OutputMainClass::getSoilDaySequence()      {return Soil_Day_Sequence;}
int OutputMainClass::getGrowthDaySequence()    {return Growth_Day_Sequence;}
int OutputMainClass::getGrowthSeasonSequence() {return Growth_Season_Sequence;}
int OutputMainClass::getAnnualSequence()       {return Annual_Sequence;}
//______________________________________________________________________________
#endif
