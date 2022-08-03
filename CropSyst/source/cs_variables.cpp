#error This was never really used, now using CORN::Parameter_properties
#include "cs_variables.h"
#include "csvc.h"
/*170725
#define NA_min MINFLOAT
#define NA_max MAXFLOAT
*/
#define NA_min std::numeric_limits<float32>::min()
#define NA_max std::numeric_limits<float32>::max()

                                                                    //{ record_type, stored_units_code, time_step_units_code,time_stamp_step_units_code,default_attribute_code}
UED::Data_record_creation_options daily_mass_datarec_creation_options        ={ UED::Record_type_distinguisher_interface::UED_data_set_year_var_units, UC_kg_m2, UT_day,UT_arbitrary_date,simulated_quality};
UED::Data_record_creation_options daily_water_depth_datarec_creation_options ={ UED::Record_type_distinguisher_interface::UED_data_set_year_var_units, UC_meter, UT_day,UT_arbitrary_date,simulated_quality};
UED::Data_record_creation_options concentration_datarec_creation_options     ={ UED::Record_type_distinguisher_interface::UED_data_set_year_var_units, UC_kg_kg, UT_day,UT_arbitrary_date,simulated_quality};

#define DEFAULT_PRECISION 2


struct CropSyst_variable_definition_and_creation CSVDC_crop_N_canopy_gaseous_loss = {CSVC_crop_N_canopy_gaseous_loss              ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_kg_ha,DEFAULT_PRECISION,"label64XXXX","label3?XXXX","label11XXXX"},&daily_mass_datarec_creation_options,"crop_N","entryXXXX"    };


CropSyst_variable_definition_and_creation
*CropSyst_daily_variable_definition_and_creation[] =
{//               warning error
//{CSVC_xxxxxxxx,{min,max,min,max,"DescriptionXXXX","AbbreviationXXXX",0,2,"lable64","label30 ","label11XXXX"},&daily_mass_datarec_creation_options,"sectionXXXX","entryXXXX"    }
// Crop nitrogen balance
&CSVDC_crop_N_canopy_gaseous_loss

  /*
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_kg_ha,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_mass_datarec_creation_options,"crop_N", "N_uptake"   }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_kg_ha,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_mass_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_kg_ha,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_mass_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_kg_ha,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_mass_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_kg_ha,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_mass_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_kg_ha,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_mass_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_kg_ha,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_mass_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_kg_ha,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_mass_datarec_creation_options,"sectionXXXX","entryXXXX"    }


, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_mm,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_water_depth_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_mm,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_water_depth_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_mm,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&daily_water_depth_datarec_creation_options,"sectionXXXX","entryXXXX"    }

, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_XXXX,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&concentration_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_XXXX,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&concentration_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_XXXX,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&concentration_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_XXXX,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&concentration_datarec_creation_options,"sectionXXXX","entryXXXX"    }
, {CSVC_xxxxxxxx                                ,{NA_min,NA_max,NA_min,NA_max,"DescriptionXXXX","AbbreviationXXXX",UC_XXXX,DEFAULT_PRECISION,"label64XXXX","labelXXXX","label11XXXX"},&concentration_datarec_creation_options,"sectionXXXX","entryXXXX"    }


   {CSVC_crop_base_root_biomass_current                        ,"crop_base",    "rootbiomass",                    UC_kg_ha          ,UC_kg_m2}     // This had previously been output preferred as UC_kg_ha I don't think this is necessary anymore and can probably be UC_kg_m2. Waiting to test this.  // was /*CSVC_crop_base_root_biomass
,  {CSVC_crop_base_water_stress_factor                         ,"crop_base",    "waterstress",                    UC_decimal_percent,UC_decimal_percent} // Actually I think I want these units to be UC_index
,  {CSVC_crop_base_temperature_stress_factor                   ,"crop_base",    "tempstress",                     UC_decimal_percent,UC_decimal_percent}// Actually I think I want these units to be UC_index
,  {CSVC_crop_base_growing_degree_days_period_accum            ,"crop_base",    "degdays",                        UT_day            ,UT_day}
,  {CSVC_crop_N_mass_canopy                                    ,"crop_base",    "canopy_BM",                      UC_kg_ha          ,UC_kg_m2}     // This had previously been output preferred as UC_kg_ha I don't think this is necessary anymore and can probably be UC_kg_m2. Waiting to test this.  // was CSVC_crop_base_dry_biomass
,  {CSVC_crop_base_green_biomass                               ,"crop_base",    "green_canopy_BM",                 UC_kg_ha          ,UC_kg_m2}     // This had previously been output preferred as UC_kg_ha I don't think this is necessary anymore and can probably be UC_kg_m2. Waiting to test this. // was CSVC_crop_base_live_biomass
,  {CSVC_crop_base_fruit_biomass                               ,"crop_base",    "fruit_BM",                       UC_kg_m2          ,UC_kg_m2}
,  {CSVC_crop_base_fruit_canopy_biomass                        ,"crop_base",    "fruit_canopy_BM",                UC_kg_m2          ,UC_kg_m2}
//  CSVC_crop_base_orchard_solid_canopy_interception
//  CSVC_crop_base_orchard_shaded_area
//  CSVC_crop_base_orchard_canopy_porosity

,  {CSVC_crop_base_leaf_area_index                             ,"crop_base",    "LAI",                            UC_index          ,UC_index}
,  {CSVC_crop_base_green_area_index                            ,"crop_base",    "GAI",                            UC_index          ,UC_index}
,  {CSVC_crop_base_root_depth                                  ,"crop_base",    "root_depth",                     UC_meter          ,UC_meter}
,  {CSVC_crop_base_water_stress_index                          ,"crop_base",    "water_stress_index",             UC_index          ,UC_index}
,  {CSVC_crop_base_temperature_stress_index                    ,"crop_base",    "temperature_stress_index",       UC_index          ,UC_index}
,  {CSVC_crop_base_VPD_daytime                                 ,"crop_base",    "VPD_daytime",                    UC_kPa            ,UC_kPa}   // check units
,  {CSVC_crop_base_intercepted_PAR                             ,"crop_base",    "intercepted_PAR",                UC_MJ_m2          ,UC_MJ_m2}   // need to check units
,  {CSVC_crop_base_intercepted_PAR_accum_to_date_time          ,"crop_base",    "intercepted_PAR_accum",          UC_MJ_m2          ,UC_MJ_m2}         //  need to check units
,  {CSVC_crop_base_fract_canopy_cover                          ,"crop_base",    "canopy_ground_cover",            UC_decimal_percent,UC_decimal_percent}   // Actually I think the units need to be a faction, when changed, check fast graph also
,  {CSVC_crop_base_transp_pot_time_step_sum                    ,"crop_base",    "transp_pot",                     UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_crop_base_transp_act_time_step_sum                    ,"crop_base",    "transp_act",                     UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_crop_base_water_intrcpt_time_step_sum                 ,"crop_base",    "crop_water_intrcpt",             UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_crop_N_stress_factor                                  ,"crop_N",       "N_stress",                       UC_factor         ,UC_factor}
,  {CSVC_crop_N_stress_index                                   ,"crop_N",       "N_stress_index",                 UC_index          ,UC_index}
,  {CSVC_crop_N_stress_index_period_avg                        ,"crop_N",       "N_stress_index_avg",             UC_index          ,UC_index}
,  {CSVC_crop_N_uptake_accum_to_date_time                      ,"crop_N",       "N_uptake_accum",                 UC_kg_m2          ,UC_kg_m2}
,  {CSVC_crop_N_mass_canopy_accum_to_date_time                 ,"crop_N",       "N_mass_canopy",                  UC_kg_m2          ,UC_kg_m2}
//110915,  {CSVC_crop_N_canopy_assimilation_accum_to_date_time ,"crop_N",       "N_canopy_assimilation",                 UC_kg_m2          ,UC_kg_m2}
//,  {CSVC_crop_N_conc_canopy                                  ,"crop_N",       "N_canopy_concentration",          UC_kg_kg          ,UC_kg_kg}  // kgN/kgBM
,  {CSVC_crop_N_conc_canopy                                    ,"crop_N",       "N_canopy_concentration",          UC_kg_kg          ,UC_kg_kg}  // kgN/kgBM
,  {CSVC_crop_N_conc_roots_live                                ,"crop_N",       "N_root_concentration",          UC_kg_kg          ,UC_kg_kg}  // kgN/kgBM
,  {CSVC_crop_N_automatic_uptake_time_step_sum                 ,"crop_N",       "N_auto_uptake",                  UC_kg_m2          ,UC_kg_m2}
,  {CSVC_crop_N_fixation                                       ,"crop_N",       "N_fixation",                     UC_kg_m2          ,UC_kg_m2}

,  {CSVC_crop_N_conc_min                                       ,"crop_N",       "N_plant_min_concentration",      UC_kg_kg          ,UC_kg_kg}  // kgN/kgBM
,  {CSVC_crop_N_conc_max                                       ,"crop_N",       "N_plant_max_concentration",      UC_kg_kg          ,UC_kg_kg}  // kgN/kgBM
,  {CSVC_crop_N_conc_critical                                  ,"crop_N",       "N_plant_critical_concentration", UC_kg_kg          ,UC_kg_kg}  // kgN/kgBM

,  {CSVC_mgmt_irrig_applied_time_step_sum                      ,"management",   "irrigation",                     UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_mgmt_biomass_unsatisfied_time_step_sum                ,"management",   "biomass_unsatisfied",            UC_kg_m2          ,UC_kg_m2}

,  {CSVC_soil_pond_water_depth                                 ,"soil_runoff",  "pond_water",                     UC_meter          ,UC_meter}
,  {CSVC_soil_runoff_surface_water_runoff_time_step_sum        ,"soil_runoff",  "surface_water_runoff",           UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_soil_erosion_clod_rate                                ,"soil_erosion", "soil_clod_rate",                 UC_m              ,UC_m}         // Not sure about units!!!
,  {CSVC_soil_base_evap_pot_time_step_sum                      ,"soil_base",    "soil_evap_pot",                  UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_soil_base_evap_act_time_step_sum                      ,"soil_base",    "soil_evap_act",                  UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_soil_base_water_entering_time_step_sum                ,"soil_base",    "soil_water_entering",            UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_soil_base_water_drainage_time_step_sum                ,"soil_base",    "soil_water_drainage",            UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_soil_base_water_depletion_accum_to_date_time          ,"soil_base",    "soil_water_depletion",           UC_meter          ,UC_meter}
,  {CSVC_soil_base_water_balance_accum_to_date_time            ,"soil_base",    "soil_water_balance",             UC_meter          ,UC_meter}
,  {CSVC_weather_ET_pot_time_step_sum                          ,"weather",      "ET_pot",                         UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_weather_ET_act_time_step_sum                          ,"weather",      "ET_act",                         UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
   //130723 ET_ref would go here
,  {CSVC_weather_precipitation_time_step_sum                   ,"weather",      "precipitation",                  UC_mm             ,UC_meter}     // This had previously been output preferred as UC_mm I don't think this is necessary anymore and can probably be UC_m. Waiting to test this.
,  {CSVC_weather_temperature_time_step_min                     ,"weather",      "temperature_min",                UC_celcius        ,UC_celcius}
,  {CSVC_weather_temperature_time_step_max                     ,"weather",      "temperature_max",                UC_celcius        ,UC_celcius}
,  {CSVC_weather_solar_radiation                               ,"weather",      "solar_radiation",                UC_MJ_per_m2_solar_radiation,UC_MJ_per_m2_solar_radiation}
,  {CSVC_weather_snow_storage                                  ,"weather",      "snow_storage",                           UC_meter          ,UC_meter}
,  {CSVC_residue_pot_evap_time_step_sum                        ,"residue",      "residue_evap_pot",               UC_meter          ,UC_meter}
,  {CSVC_residue_act_evap_time_step_sum                        ,"residue",      "residue_evap_act",               UC_meter          ,UC_meter}
,  {CSVC_residue_ground_cover                                  ,"residue",      "residue_ground_cover",           UC_decimal_percent,UC_decimal_percent}
,  {CSVC_residue_water_storage                                 ,"residue",      "residue_water_storage",          UC_meter          ,UC_meter}
,  {CSVC_residue_surface_biomass                               ,"residue",      "residue_surface_BM",             UC_kg_m2          ,UC_kg_m2}
,  {CSVC_residue_plant_incorporated                            ,"residue",      "residue_straw_incorp",           UC_kg_m2          ,UC_kg_m2}
,  {CSVC_residue_manure_incorporated                           ,"residue",      "residue_manure_incorp",          UC_kg_m2          ,UC_kg_m2}
,  {CSVC_residue_water_intrcpt_time_step_sum                   ,"residue",      "residue_water_intrcpt",          UC_meter          ,UC_meter}

,  {CSVC_mgmt_N_applied_time_step_sum                          ,"management"  , "N_applied",                      UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_crop_N_uptake_time_step_sum                           ,"crop_N"      , "N_uptake",                       UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_soil_N_leached_time_step_sum                          ,"soil_N"      , "N_leached",                      UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_residue_mineralized_time_step_sum                     ,"residue"     , "N_straw_mineralization",         UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_residue_manure_mineralized_time_step_sum              ,"residue"     , "N_manure_mineralization",        UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_organic_matter_mineralized_time_step_sum              ,"organic_matter","N_OM_mineralization",           UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_mgmt_N_organic_applied_time_step_sum                  ,"management"  , "N_OM_applied",                   UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_soil_N_immobilization_time_step_sum                   ,"soil_N"      , "N_immobilization",               UC_kg_m2          ,UC_kg_m2}  // kgN/m2

//  The following are accumulations
,  {CSVC_weather_ET_pot_accum_to_date_time                     ,"weather"     , "ET_pot_accum",                   UC_m           ,UC_m}
,  {CSVC_weather_ET_act_accum_to_date_time                     ,"weather"     , "ET_act_accum",                   UC_m           ,UC_m}
   //130723 ET_ref would go here
,  {CSVC_weather_precipitation_accum_to_date_time              ,"weather"     , "precipitation_accum",            UC_m           ,UC_m}
,  {CSVC_crop_base_transp_pot_accum_to_date_time               ,"crop_base"   , "transp_pot_accum",               UC_m           ,UC_m}
,  {CSVC_crop_base_transp_act_accum_to_date_time               ,"crop_base"   , "transp_act_accum",               UC_m           ,UC_m}
,  {CSVC_crop_base_water_intrcpt_accum_to_date_time            ,"crop_base"   , "crop_water_intrcpt_accum",       UC_m           ,UC_m}
,  {CSVC_soil_base_evap_pot_accum_to_date_time                 ,"soil_base"   , "soil_evap_pot_accum",            UC_m           ,UC_m}
,  {CSVC_soil_base_evap_act_accum_to_date_time                 ,"soil_base"   , "soil_evap_act_accum",            UC_m           ,UC_m}
,  {CSVC_soil_base_water_entering_accum_to_date_time           ,"soil_base"   , "soil_water_entering_accum",      UC_m           ,UC_m}
,  {CSVC_soil_base_water_drainage_accum_to_date_time           ,"soil_base"   , "soil_water_drainage_accum",      UC_m           ,UC_m}
,  {CSVC_residue_pot_evap_accum_to_date_time                   ,"residue"     , "residue_evap_pot_accum",         UC_m           ,UC_m}
,  {CSVC_residue_act_evap_accum_to_date_time                   ,"residue"     , "residue_evap_act_accum",         UC_m           ,UC_m}
,  {CSVC_residue_water_intrcpt_accum_to_date_time              ,"residue"     , "residue_water_intrcpt_accum",    UC_m           ,UC_m}
,  {CSVC_mgmt_irrig_applied_accum_to_date_time                 ,"management"  , "irrigation_accum",               UC_m           ,UC_m}
,  {CSVC_soil_runoff_surface_water_runoff_accum_to_date_time   ,"soil_runoff" , "surface_water_runoff_accum",     UC_m           ,UC_m}
,  {CSVC_mgmt_N_applied_accum_to_date_time                     ,"management"  , "N_applied_accum",                UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_soil_N_leached_accum_to_date_time                     ,"soil_N"      , "N_leached_accum",                UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_organic_matter_mineralized_accum_to_date_time         ,"organic_matter", "N_mineralization_accum",         UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_residue_mineralized_accum_to_date_time                ,"residue"     , "N_straw_mineralization_accum",   UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_residue_manure_mineralized_accum_to_date_time         ,"residue"     , "N_manure_mineralization_accum",  UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_mgmt_N_organic_applied_accum_to_date_time             ,"management"  , "N_OM_applied_accum",             UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_crop_N_automatic_uptake_accum_to_date_time            ,"crop_N"      , "N_auto_uptake_accum",            UC_kg_m2          ,UC_kg_m2}  // kgN/m2
,  {CSVC_crop_N_fixation_time_step_sum                         ,"crop_N"      , "N_fixation_accum",               UC_kg_m2          ,UC_kg_m2}  // kgN/m2
};

*/

,0
};


