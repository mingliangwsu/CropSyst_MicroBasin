
#error Obsolete

The model has been replaced with   CropSyst_inspection.cpp


// This module only need to be included if using variable recorders

// This file uses 8 bit characters in literal text strings

#include "csvc.h"
#include "CS_suite/simulation/CS_inspector.h"
#include "crop/crop_cropsyst.h"
#include "crop/crop_interfaced_cropsyst.h"
#include "crop/crop_root_V4.h"
#include "crop/crop_n.h"
#include "crop/phenology_common.h"
#include "soil/chemicals_profile.h"
#include "soil/nitrogen_profile.h"
#include "soil/infiltration.h"
#include "soil.h"
#include "organic_matter/OM_pools_common.h"
#include "organic_matter/OM_residues_profile_common.h"
#include "cs_ET.h"
#include "UED/library/std_codes.h"

#include "land_unit_sim.h"
#  include "common/weather/weather.h"
/* NYI


// Management
CSVP_mgmt_irrig_applied
CSVP_mgmt_biomass_grazed
CSVP_mgmt_biomass_unsatisfied

// Nitrogen management
CSVP_mgmt_P_applied

CSVP_mgmt_N_organic_gaseous_loss
CSVP_mgmt_N_inorganic_gaseous_loss
CSVP_misc_N_total_mineralization

// Water table
CSVP_water_table_depth


Annual

[ ]CSVC_mgmt_N_organic_gaseous_loss_period_sum          ,UC_kg_ha}
[ ]CSVC_mgmt_N_inorganic_gaseous_loss_period_sum        ,UC_kg_ha}



[ ]CSVC_soil_C_SOM_profile                              ,UC_kg_ha}
[ ]CSVC_soil_C_SOM_30cm                                 ,UC_kg_ha}


[x]Annual runoff
[x]Annual drainage
[x]Annual precipitation
[x]Soil profile water depth at beginning of year
[x]Soil profile water depth at end of year?
[x]Annual Total N fertilization
[x]Annual N leaching
[x]Soil profile N mass at beginning of  year
[x]Soil profile N mass at end of year
[x]Annual denitrification
[x]Annual nitrification
[x]Annual volatilization
[x]Annual N2O emission from denitrification
[x]Annual N2O emission from nitrification
[x]Annual mineralization
[x]Annual actual ET
[x]Annual soil organic carbon down to 30 cm
[x]Annual profile soil organic carbon
[x]Annual mean temperature
[x]Annual solar radiation

Seasonal
[x]Yield
[x]Aboveground biomass at harvest
[x]Root biomass at harvest
[x]Potential transpiration
[x]Actual transpiration
[x]Season runoff
[x]Season drainage
[x]Season precipitation
[x]Soil profile water depth at beginning of season
[x]Soil profile water depth at harvest
[x]Total N fertilization
[x]Canopy N mass at harvest (just before harvest?)
[x]Seasonal N leaching
[x]Soil profile N mass at beginning of  season
[x]Soil profile N mass at harvest
[x]Seasonal denitrification
[x]Seasonal nitrification
[x]Seasonal volatilization
[x]Seasonal N2O emission from denitrification
[x]Seasonal N2O emission from nitrification
[x]Seasonal mineralization
[ ]Duration


#ifdef USE_VARIABLE_RECORDERS
namespace CS
{  class Variable_recorders;
}
#endif

#include "csvc.h"
Parameter_properties_literal PP_XXXXX                                ={"XXXXX"                            ,"XXXXX"                 ,"XXXXX","Xxxxx"                 ,"hint_NYN","URL_NYN",UC_actual               ,XXX"m"};

   recorders.append(new CS::Variable_recorder(XXXXX,CSVP_XXXXX,PP_XXXXX,UC_prefered,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));




// Residue potential recorders
CSVP_residue_ground_cover
CSVP_residue_water_storage
CSVP_residue_surface_biomass
CSVP_residue_pot_evap
CSVP_residue_act_evap
CSVP_residue_water_intrcpt
CSVP_residue_mineralized

CSVP_residue_incorporated 1-31

// Plant residue
CSVP_residue_plant_surface
CSVP_residue_plant_flat
CSVP_residue_plant_stubble

CSVP_residue_plant_incorporated 1-31

// Manure
CSVP_residue_manure_mineralized
CSVP_residue_manure_surface

CSVP_residue_manure_incorporated  1-31
*/

CORN::Parameter_properties_literal PP_crop_base_dry_biomass_deprecate                     ={"dry_biomass_deprecate"                 ,"BM_dry"                     ,"BM_dry"                     ,"dry biomass(deprecate)"                   ,"hint_NYN","URL_NYN",UC_kg_m2              ,"units"};
CORN::Parameter_properties_literal PP_crop_base_green_biomass                             ={"green_biomass"                         ,"BM_green"                   ,"BM_green"                   ,"green biomass"                            ,"hint_NYN","URL_NYN",UC_kg_m2              ,"units"};
CORN::Parameter_properties_literal PP_crop_base_fruit_biomass                             ={"fruit_biomass"                         ,"BM_fruit"                   ,"BM_fruit"                   ,"fruit biomass"                            ,"hint_NYN","URL_NYN",UC_kg_m2              ,"units"};
CORN::Parameter_properties_literal PP_crop_base_fruit_canopy_biomass                      ={"fruit_canopy_biomass"                  ,"BM_fruit_canopy"            ,"BM_fruit_canopy"            ,"fruit&canopy biomass"                     ,"hint_NYN","URL_NYN",UC_kg_m2              ,"units"};
//CORN::Parameter_properties_literal PP_crop_base_orchard_solid_canopy_interception       ={"orchard_solid_canopy_interception"     ,"intrcpt_orchard"            ,"intrcpt_orchard"            ,"orchard solid canopy interception"        ,"hint_NYN","URL_NYN",???UC_MJ_m2???,"units"};
CORN::Parameter_properties_literal PP_crop_base_orchard_shaded_area_GAI                   ={"orchard_shaded_area_GAI"               ,"shaded_area_GAI_orchard"    ,"shaded_area_GAI_orchard"    ,"orchard shaded_area GAI"                 ,"hint_NYN","URL_NYN",UC_index               ,"units"};
//CORN::Parameter_properties_literal PP_crop_base_orchard_canopy_porosity                 ={"orchard_canopy_porosity"               ,"porosity_canopy_orchard"    ,"porosity_canopy_orchard"    ,"orchard canopy porosity"                 ,"hint_NYN","URL_NYN",???units_code???,"units"};
CORN::Parameter_properties_literal PP_crop_base_leaf_area_index                           ={"leaf_area_index"                       ,"LAI"                        ,"LAI"                        ,"leaf area index"                         ,"hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_green_area_index                          ={"green_area_index"                      ,"GAI"                        ,"GAI"                        ,"green area index"                        ,"hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_water_stress_factor                       ={"water_stress_factor"                   ,"water_stress_fct"           ,"water_stress_fct"           ,"water stress factor"                     ,"hint_NYN","URL_NYN",UC_factor              ,"units"};
CORN::Parameter_properties_literal PP_crop_base_temperature_stress_factor                 ={"temperature_stress_factor"             ,"temp_stress_fct"            ,"temp_stress_fct"            ,"temperature stress factor"               ,"hint_NYN","URL_NYN",UC_factor              ,"units"};
CORN::Parameter_properties_literal PP_crop_base_tuber_init_temp_stress_index              ={"tuber_init_temp_stress_index"          ,"tuber_init_temp_stress_idx" ,"tuber_init_temp_stress_idx" ,"tuber initiation temperature stress index","hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_tuber_fill_temp_stress_index              ={"tuber_fill_temp_stress_index"          ,"tuber_fill_temp_stress_idx" ,"tuber_fill_temp_stress_idx" ,"tuber filling_temperature stress index"  ,"hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_water_stress_index                        ={"water_stress_index"                    ,"water_stress_idx"           ,"water_stress_idx"           ,"water stress index"                      ,"hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_temperature_stress_index                  ={"temperature_stress_index"              ,"temp_stress_idx"            ,"temp_stress_idx"            ,"temperature stress index"                ,"hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_flower_temperature_stress_index           ={"flower_temperature_stress_index"       ,"flower_temp_stress_idx"     ,"flower_temp_stress_idx"     ,"flowering temperature stress index"      ,"hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_flower_water_stress_index                 ={"flower_water_stress_index"             ,"flower_water_stress_idx"    ,"flower_water_stress_idx"    ,"flowering water stress index"            ,"hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_flower_N_stress_index                     ={"flower_N_stress_index"                 ,"flower_N_stress_idx"        ,"flower_N_stress_idx"        ,"flowering N stress index"                ,"hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_filling_duration_index                    ={"filling_duration_index"                ,"filling_dur_idx"            ,"filling_dur_idx"            ,"filling duration index"                  ,"hint_NYN","URL_NYN",UC_index               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_fract_canopy_cover                        ={"fract_canopy_cover"                    ,"fract_canopy_cover"         ,"fract_canopy_cover"         ,"canopy cover fraction"                   ,"hint_NYN","URL_NYN",UC_fraction            ,"units"};
CORN::Parameter_properties_literal PP_crop_base_leaf_water_pot                            ={"leaf_water_pot"                        ,"leaf_water_pot"             ,"leaf_water_pot"             ,"leaf water potential"                    ,"hint_NYN","URL_NYN",UC_J_kg                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_water_intrcpt                             ={"water_intrcpt"                         ,"water_intrcpt"              ,"water_intrcpt"              ,"crop water interception"                 ,"hint_NYN","URL_NYN",UC_meter               ,"units"};
//CORN::Parameter_properties_literal PP_crop_base_growth_stage                            ={"growth_stage"                          ,"growth_stage"               ,"growth_stage"               ,"growth stage"                            ,"hint_NYN","URL_NYN",units_code               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_planting_date_YD                          ={"planting_date_YD"                      ,"planting"                   ,"planting"                   ,"planting date"                           ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_emergence_date_YD                         ={"emergence_date_YD"                     ,"emergence"                  ,"emergence"                  ,"emergence date"                          ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_flowering_date_YD                         ={"flowering_date_YD"                     ,"flowering"                  ,"flowering"                  ,"flowering date"                          ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_tuber_init_date_YD                        ={"tuber_init_date_YD"                    ,"tuber_init"                 ,"tuber_init"                 ,"tuber init date"                         ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_grain_filling_date_YD                     ={"grain_filling_date_YD"                 ,"grain_fill"                 ,"grain_fill"                 ,"grain filling date"                      ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_peak_LAI_date_YD                          ={"peak_LAI_date_YD"                      ,"peak_LAI"                   ,"peak_LAI"                   ,"peak LAI date"                           ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_maturity_date_YD                          ={"maturity_date_YD"                      ,"maturity"                   ,"maturity"                   ,"maturity date"                           ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_harvest_date_YD                           ={"harvest_date_YD"                       ,"harvest"                    ,"harvest"                    ,"harvest date"                            ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_restart_date_YD                           ={"restart_date_YD"                       ,"restart"                    ,"restart"                    ,"restart date"                            ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_bud_break_date_YD                         ={"bud_break_date_YD"                     ,"bud_break"                  ,"bud_break"                  ,"bud break date"                          ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_initial_fruit_growth_date_YD              ={"initial_fruit_growth_date_YD"          ,"initl_fruit_growth"         ,"initl_fruit_growth"         ,"initial fruit growth date"               ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_rapid_fruit_growth_date_YD                ={"rapid_fruit_growth_date_YD"            ,"rapid_fruit_growth"         ,"rapid_fruit_growth"         ,"rapid fruit growth date"                 ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_inactive_begin_date_YD                    ={"inactive_begin_date_YD"                ,"inactive_begin"             ,"inactive_begin"             ,"inactive begin date"                     ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_inactive_end_date_YD                      ={"inactive_end_date_YD"                  ,"inactive_end"               ,"inactive_end"               ,"inactive end date"                       ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_base_chill_requirement_satisfied_date_YD       ={"chill_requirement_satisfied_date_YD"   ,"chill_req_sat"              ,"chill_req_sat"              ,"chill requirement satisfied date"        ,"hint_NYN","URL_NYN",UT_date                ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_yield                                  ={"biomass_yield"                         ,"yield"                      ,"yield"                      ,"yield biomass"                           ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_useful                                 ={"biomass_useful"                        ,"useful"                     ,"useful"                     ,"useful biomass"                          ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_disposal                               ={"biomass_disposal"                      ,"disposal"                   ,"disposal"                   ,"disposal biomass"                        ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_chaff                                  ={"biomass_chaff"                         ,"chaff"                      ,"chaff"                      ,"chaff biomass"                           ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_stubble                                ={"biomass_stubble"                       ,"stubble"                    ,"stubble"                    ,"stubble biomass"                         ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_grazing_to_manure                      ={"biomass_grazing_to_manure"             ,"graze_to_manure"            ,"graze_to_manure"            ,"grazing_to_manure biomass"               ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_grazing_to_disposal                    ={"biomass_grazing_to_disposal"           ,"graze_to_dispsl"            ,"graze_to_dispsl"            ,"grazing_to_disposal biomass"             ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_uncut_canopy                           ={"biomass_uncut_canopy"                  ,"uncut_canopy"               ,"uncut_canopy"               ,"uncut canopy biomass"                    ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_canopy                                 ={"biomass_canopy"                        ,"canopy"                     ,"canopy"                     ,"canopy biomass"                          ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_removed_canopy                         ={"biomass_removed_canopy"                ,"rmvd_canopy"                ,"rmvd_canopy"                ,"removed canopy biomass"                  ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_removed_non_yield                      ={"biomass_removed_non_yield"             ,"rmvd_non_yield"             ,"rmvd_non_yield"             ,"removed non-yield biomass"               ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_removed_residue                        ={"biomass_removed_residue"               ,"rmvd_residue"               ,"rmvd_residue"               ,"removed residue biomass"                 ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_removed_grazing                        ={"biomass_removed_grazing"               ,"rmvd_grazing"               ,"rmvd_grazing"               ,"removed grazing biomass"                 ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_roots_live                             ={"biomass_roots_live"                    ,"roots_live"                 ,"roots_live"                 ,"roots live biomass"                      ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_roots_dead                             ={"biomass_roots_dead"                    ,"roots_dead"                 ,"roots_dead"                 ,"roots dead biomass"                      ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_produced_above_ground                  ={"biomass_produced_above_ground"         ,"produced_AG"                ,"produced_AG"                ,"produced above ground biomass"           ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_removed_above_ground                   ={"biomass_removed_above_ground"          ,"rmvd_AG"                    ,"rmvd_AG"                    ,"removed above ground biomass"            ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_removed_grazing_to_manure              ={"biomass_removed_grazing"               ,"rmvd_grazing"               ,"rmvd_grazing"               ,"removed grazing biomass to manure"       ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_biomass_removed_residue_to_residue             ={"biomass_removed_residue"               ,"rmvd_residue"               ,"rmvd_residue"               ,"removed residue biomass"                 ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_intercepted_PAR                           ={"intercepted_PAR"                       ,"intcpt_PAR"                 ,"intcpt_PAR"                 ,"intercepted PAR"                         ,"hint_NYN","URL_NYN",UC_MJ_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_base_VPD_daytime                               ={"VPD_daytime"                           ,"VPD_daytime"                ,"VPD_daytime"                ,"vapor pressure deficit daytime"          ,"hint_NYN","URL_NYN",UC_kPa                 ,"units"};
CORN::Parameter_properties_literal PP_crop_P_mass_uptake                                  ={"crop_P_mass_uptake"                    ,"P_uptake"                   ,"P_uptake"                   ,"P mass_uptake"                           ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_N_stress_factor                                ={"crop_N_stress_factor"                  ,"N_stress_fct"               ,"N_stress_fct"               ,"N stress_factor"                         ,"hint_NYN","URL_NYN",UC_factor              ,"units"};
CORN::Parameter_properties_literal PP_crop_N_stress_index                                 ={"crop_N_stress_index"                   ,"N_stress_idx"               ,"N_stress_idx"               ,"N stress_index"                          ,"hint_NYN","URL_NYN",UC_index               ,"units"};

CORN::Parameter_properties_literal PP_crop_N_mass_canopy                                  ={"crop_N_mass_canopy"                    ,"N_canopy"                   ,"N_canopy"                   ,"N mass_canopy"                           ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_N_canopy_gaseous_loss                          ={"crop_N_canopy_gaseous_loss"            ,"N_canopy_loss"              ,"N_canopy_loss"              ,"N canopy_gaseous_loss"                   ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_N_automatic_uptake                             ={"crop_N_automatic_uptake"               ,"N_auto_upt"                 ,"N_auto_upt"                 ,"N automatic_uptake"                      ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_N_fixation                                     ={"crop_N_fixation"                       ,"N_fix"                      ,"N_fix"                      ,"N fixation"                              ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_N_flower_mature_conc_ratio                     ={"crop_N_flower_mature_conc_ratio"       ,"N_flwr_mtr_conc_rat"        ,"N_flwr_mtr_conc_rat"        ,"N flower_mature_conc_ratio"              ,"hint_NYN","URL_NYN",UC_ratio               ,"units"};
CORN::Parameter_properties_literal PP_crop_N_uptake_excess_or_deficit                     ={"crop_N_uptake_excess_or_deficit"       ,"N_upt_exs_def"              ,"N_upt_exs_def"              ,"N uptake_excess_or_deficit"              ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_N_conc_min                                     ={"crop_N_conc_min"                       ,"N_BM_conc_min"              ,"N_BM_conc_min"              ,"N conc_min"                              ,"hint_NYN","URL_NYN",UC_kg_kg               ,"units"};
CORN::Parameter_properties_literal PP_crop_N_conc_max                                     ={"crop_N_conc_max"                       ,"N_BM_conc_max"              ,"N_BM_conc_max"              ,"N conc_max"                              ,"hint_NYN","URL_NYN",UC_kg_kg               ,"units"};
CORN::Parameter_properties_literal PP_crop_N_conc_critical                                ={"crop_N_conc_critical"                  ,"N_crit"                     ,"N_crit"                     ,"N conc_critical"                         ,"hint_NYN","URL_NYN",UC_kg_kg               ,"units"};
CORN::Parameter_properties_literal PP_crop_C_mass_canopy                                  ={"C_mass_canopy"                         ,"C_canopy"                   ,"C_canopy"                   ,"C mass canopy"                           ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
CORN::Parameter_properties_literal PP_crop_C_mass_roots_live                              ={"C_mass_roots_live"                     ,"C_root_live"                ,"C_root_live"                ,"C mass roots live"                       ,"hint_NYN","URL_NYN",UC_kg_m2               ,"units"};
//_____________________________________________________________________________/

namespace CropSyst {
const CS::Reporter &Crop_complete::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{

   const CS::Reporter &reporter =
      Crop_common::render_inspectors(inspectors,context,instance_description,statistic);
      //150915       render_listeners(recorders,desired_descriptive_summary_elements)
   thermal_time    .render_inspectors(inspectors,&reporter,"thermal_time",statistic);
   roots_current  ->render_inspectors(inspectors,&reporter,"roots",statistic);
   phenology       .render_inspectors(inspectors,&reporter,"phenology",statistic);
   if (nitrogen) nitrogen->render_inspectors(inspectors,&reporter,"nitrogen",statistic);
/*NYI
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_dry_biomass_deprecate                             ,PP_crop_base_dry_biomass_deprecate                                    ,desired_descriptive_summary_elements));
//NYI because need one value   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_green_biomass                                     ,PP_crop_base_green_biomass                                            ,desired_descriptive_summary_elements));
//NYI not needed for REACCH   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_fruit_biomass                                     ,PP_crop_base_fruit_biomass                                            ,desired_descriptive_summary_elements));
//NYI not needed for REACCH   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_fruit_canopy_biomass                              ,PP_crop_base_fruit_canopy_biomass                                     ,desired_descriptive_summary_elements));
//NYI not needed for REACCH   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_orchard_solid_canopy_interception                 ,PP_crop_base_orchard_solid_canopy_interception                        ,desired_descriptive_summary_elements));
//NYI not needed for REACCH   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_orchard_shaded_area_GAI                           ,PP_crop_base_orchard_shaded_area_GAI                                  ,desired_descriptive_summary_elements));
//NYI not needed for REACCH   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_orchard_canopy_porosity                           ,PP_crop_base_orchard_canopy_porosity                                  ,desired_descriptive_summary_elements));
//NYI not needed for REACCH daily   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_leaf_area_index                                   ,PP_crop_base_leaf_area_index                                          ,desired_descriptive_summary_elements));
//NYI not needed for REACCH daily   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_green_area_index                                  ,PP_crop_base_green_area_index                                         ,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_water_stress_factor                               ,PP_crop_base_water_stress_factor                                      ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_temperature_stress_factor                         ,PP_crop_base_temperature_stress_factor                                ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_tuber_init_temp_stress_index                      ,PP_crop_base_tuber_init_temp_stress_index                             ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_tuber_fill_temp_stress_index                      ,PP_crop_base_tuber_fill_temp_stress_index                             ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_water_stress_index                                ,PP_crop_base_water_stress_index                                       ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_temperature_stress_index                          ,PP_crop_base_temperature_stress_index                                 ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_flower_temperature_stress_index                   ,PP_crop_base_flower_temperature_stress_index                          ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_flower_water_stress_index                         ,PP_crop_base_flower_water_stress_index                                ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_flower_N_stress_index                             ,PP_crop_base_flower_N_stress_index                                    ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_filling_duration_index                            ,PP_crop_base_filling_duration_index                                   ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_fract_canopy_cover                                ,PP_crop_base_fract_canopy_cover                                       ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_leaf_water_pot                                    ,PP_crop_base_leaf_water_pot                                           ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_water_intrcpt                                     ,PP_crop_base_water_intrcpt                                            ,prefered_units,desired_descriptive_summary_elements));
//NYI not a float   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_growth_stage                     ,PP_crop_base_growth_stage                                             ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_planting_date_YMD                                 ,PP_crop_base_planting_date_YMD                                        ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_emergence_date_YMD                                ,PP_crop_base_emergence_date_YMD                                       ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_flowering_date_YMD                                ,PP_crop_base_flowering_date_YMD                                       ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_tuber_init_date_YMD                               ,PP_crop_base_tuber_init_date_YMD                                      ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_grain_filling_date_YMD                            ,PP_crop_base_grain_filling_date_YMD                                   ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_peak_LAI_date_YMD                                 ,PP_crop_base_peak_LAI_date_YMD                                        ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_maturity_date_YMD                                 ,PP_crop_base_maturity_date_YMD                                        ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_harvest_date_YMD                                  ,PP_crop_base_harvest_date_YMD                                         ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_restart_date_YMD                                  ,PP_crop_base_restart_date_YMD                                         ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_bud_break_date_YMD                                ,PP_crop_base_bud_break_date_YMD                                       ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_initial_fruit_growth_date_YMD                     ,PP_crop_base_initial_fruit_growth_date_YMD                            ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_rapid_fruit_growth_date_YMD                       ,PP_crop_base_rapid_fruit_growth_date_YMD                              ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_inactive_begin_date_YMD                           ,PP_crop_base_inactive_begin_date_YMD                                  ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_inactive_end_date_YMD                             ,PP_crop_base_inactive_end_date_YMD                                    ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_base_chill_requirement_satisfied_date_YMD         ,PP_crop_base_base_chill_requirement_satisfied_date_YMD                ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_planting_date_YD                                  ,PP_crop_base_planting_date_YD                                         ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_emergence_date_YD                                 ,PP_crop_base_emergence_date_YD                                        ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_flowering_date_YD                                 ,PP_crop_base_flowering_date_YD                                        ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_tuber_init_date_YD                                ,PP_crop_base_tuber_init_date_YD                                       ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_grain_filling_date_YD                             ,PP_crop_base_grain_filling_date_YD                                    ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_peak_LAI_date_YD                                  ,PP_crop_base_peak_LAI_date_YD                                         ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_maturity_date_YD                                  ,PP_crop_base_maturity_date_YD                                         ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_harvest_date_YD                                   ,PP_crop_base_harvest_date_YD                                          ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_restart_date_YD                                   ,PP_crop_base_restart_date_YD                                          ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_bud_break_date_YD                                 ,PP_crop_base_bud_break_date_YD                                        ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_initial_fruit_growth_date_YD                      ,PP_crop_base_initial_fruit_growth_date_YD                             ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_rapid_fruit_growth_date_YD                        ,PP_crop_base_rapid_fruit_growth_date_YD                               ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_inactive_begin_date_YD                            ,PP_crop_base_inactive_begin_date_YD                                   ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_inactive_end_date_YD                              ,PP_crop_base_inactive_end_date_YD                                     ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_chill_requirement_satisfied_date_YD               ,PP_crop_base_chill_requirement_satisfied_date_YD                      ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_intercepted_PAR                                   ,PP_crop_base_intercepted_PAR                                          ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_VPD_daytime                                       ,PP_crop_base_VPD_daytime                                              ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_P_mass_uptake                                          ,PP_crop_P_mass_uptake                                                 ,prefered_units,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_C_mass_canopy                                          ,PP_crop_C_mass_canopy                                                 ,prefered_unit,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(_value,CSVP_crop_C_mass_roots_live                                      ,PP_crop_C_mass_roots_live                                             ,prefered_units,desired_descriptive_summary_elements));
*/
   return reporter;
}
} //namespace CropSyst
//_2013-07-30________________________________________render_variable_recorders_/
Parameter_properties_literal PP_crop_base_transp_pot ={"transpiration_pot","transp:pot",SUBSECTION_UNUSED,"transpiration potential",HINT_UNUSED,"URL_NYN",UC_meter               ,"m"};
Parameter_properties_literal PP_crop_base_transp_act ={"transpiration_act","transp:act",SUBSECTION_UNUSED,"transpiration actual"   ,HINT_UNUSED,"URL_NYN",UC_meter               ,"m"};
//_2013-07-31___________________________________________________________________

namespace CropSyst {
const CS::Reporter &Crop_common::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   const CS::Reporter &reporter = CS::provide_global_reporters().know
      ((nat32)this,instance_description,context/*containment*/);
   inspectors.append(new CS::Inspector(pot_transpiration_m          ,reporter,PP_crop_base_transp_pot,UC_meter,inspectors.desired_descriptive_summary_elements,statistic));
   inspectors.append(new CS::Inspector(recorded_act_transpiration_m ,reporter,PP_crop_base_transp_act,UC_meter,inspectors.desired_descriptive_summary_elements,statistic));
   return reporter;
}
} // namespace CropSyst

//_2013-07-30________________________________________render_variable_recorders_/
Parameter_properties_literal PP_crop_N_uptake      ={"N_uptake","N_uptk","uptake","nitrogen uptake","hint_NYN","URL_NYN",UC_kg_m2,"kg/ha"};
/*
nitrogen
CSVP_crop_N_stress_factor
CSVP_crop_N_stress_index
CSVP_crop_N_mass_canopy
CSVP_crop_N_canopy_gaseous_loss
CSVP_crop_N_automatic_uptake
CSVP_crop_N_fixation
CSVP_crop_N_flower_mature_conc_ratio
CSVP_crop_N_uptake_excess_or_deficit
CSVP_crop_N_conc_min
CSVP_crop_N_conc_max
CSVP_crop_N_conc_critical

CSVP_crop_N_mass_yield
CSVP_crop_N_mass_useful
CSVP_crop_N_mass_disposal
CSVP_crop_N_mass_chaff
CSVP_crop_N_mass_stubble
CSVP_crop_N_mass_grazing_to_manure
CSVP_crop_N_mass_grazing_to_disposal
CSVP_crop_N_mass_uncut_canopy
CSVP_crop_N_mass_canopy
CSVP_crop_N_mass_removed_canopy
CSVP_crop_N_mass_removed_non_yield
CSVP_crop_N_mass_removed_residue
CSVP_crop_N_mass_removed_grazing
CSVP_crop_N_mass_roots_live
CSVP_crop_N_mass_roots_dead
*/

Parameter_properties_literal PP_crop_canopy_N_mass                                ={"canopy_N_mass_final"                            ,"canopy_N_mass"                 ,"canopy_N_mass","canopy N mass at harvest"                 ,"hint_NYN","URL_NYN",UC_kg_m2               ,"kgN/m�"};
/*
CSVP_crop_N_mass_removed_above_ground
CSVP_crop_N_mass_removed_grazing
CSVP_crop_N_mass_removed_residue
CSVP_crop_N_conc_yield
CSVP_crop_N_conc_useful
CSVP_crop_N_conc_disposal
CSVP_crop_N_conc_chaff
CSVP_crop_N_conc_stubble
CSVP_crop_N_conc_grazing_to_manure
CSVP_crop_N_conc_grazing_to_disposal
CSVP_crop_N_conc_uncut_canopy
CSVP_crop_N_conc_canopy
CSVP_crop_N_conc_removed_canopy
CSVP_crop_N_conc_removed_non_yield
CSVP_crop_N_conc_removed_residue
CSVP_crop_N_conc_removed_grazing
CSVP_crop_N_conc_roots_live
CSVP_crop_N_conc_roots_dead
CSVP_crop_N_conc_produced_above_ground
CSVP_crop_N_conc_removed_above_ground
CSVP_crop_N_conc_removed_grazing
CSVP_crop_N_conc_removed_residue
*/




namespace CropSyst {
const CS::Reporter &Crop_nitrogen::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   // Note sure if I need to create a new report or simply use context
   //const CS::Reporter &reporter = CS::provide_global_reporters().know
   //   ((nat32)this,instance_description,context/*containment*/);
   inspectors.append(new CS::Inspector(daily.uptake          ,*context,PP_crop_base_transp_pot,UC_kg_ha,inspectors.desired_descriptive_summary_elements,statistic));

   //   recorders.append(new CS::Variable_recorder(daily.uptake, CSVP_crop_N_uptake, PP_crop_N_uptake,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));


   return *context; // NYI
}

} // namespace CropSyst

//_2013-07-30________________________________________render_variable_recorders_/

/* NYI
CSVP_soil_base_evap_pot
CSVP_soil_base_water_drainage
CSVP_soil_base_water_depletion
CSVP_soil_base_water_balance
CSVP_soil_erosion_clod_rate
CSVP_soil_erosion_loss
CSVP_soil_erosion_loss
CSVP_soil_erosion_index
CSVP_soil_erosion_RUSLE_C_factor

CSVP_soil_runoff_surface_water_runon
CSVP_soil_C_SOM_profile
CSVP_soil_C_SOM_5cm
CSVP_soil_C_SOM_10cm
CSVP_soil_C_SOM_15cm
CSVP_soil_C_SOM_30cm
CSVP_soil_C_SOM_60cm
CSVP_soil_C_SOM_90cm
CSVP_soil_C_microbial_profile
CSVP_soil_C_microbial_5cm
CSVP_soil_C_microbial_10cm                                   
CSVP_soil_C_microbial_15cm
CSVP_soil_C_microbial_30cm                                   
CSVP_soil_C_microbial_60cm                                   
CSVP_soil_C_microbial_90cm                                   
CSVP_soil_C_labile_profile
CSVP_soil_C_labile_5cm                                       
CSVP_soil_C_labile_10cm
CSVP_soil_C_labile_15cm
CSVP_soil_C_labile_30cm
CSVP_soil_C_labile_60cm
CSVP_soil_C_labile_90cm
CSVP_soil_C_metastable_profile
CSVP_soil_C_metastable_5cm
CSVP_soil_C_metastable_10cm
CSVP_soil_C_metastable_15cm
CSVP_soil_C_metastable_30cm
CSVP_soil_C_metastable_60cm
CSVP_soil_C_metastable_90cm
CSVP_soil_C_passive_profile
CSVP_soil_C_passive_5cm
CSVP_soil_C_passive_10cm
CSVP_soil_C_passive_15cm
CSVP_soil_C_passive_30cm
CSVP_soil_C_passive_60cm
CSVP_soil_C_passive_90cm                                     
CSVP_soil_C_residues_surface
CSVP_soil_C_residues_profile
CSVP_soil_C_residues_5cm
CSVP_soil_C_residues_10cm
CSVP_soil_C_residues_15cm                                    
CSVP_soil_C_residues_30cm
CSVP_soil_C_residues_60cm
CSVP_soil_C_residues_90cm
CSVP_soil_C_residues_surface
CSVP_soil_C_residues_profile
CSVP_soil_C_residues_5cm
CSVP_soil_C_residues_10cm
CSVP_soil_C_residues_15cm
CSVP_soil_C_residues_30cm
CSVP_soil_C_residues_60cm
CSVP_soil_C_residues_90cm
CSVP_soil_C_decomposed_residue_profile
CSVP_soil_C_decomposed_residue_5cm
CSVP_soil_C_decomposed_residue_10cm
CSVP_soil_C_decomposed_residue_15cm
CSVP_soil_C_decomposed_residue_30cm
CSVP_soil_C_decomposed_residue_60cm                          
CSVP_soil_C_decomposed_residue_90cm
CSVP_soil_C_decomposed_residue_flat
CSVP_soil_C_decomposed_residue_stubble                       
CSVP_soil_C_decomposed_residue_attached
CSVP_soil_C_incorporated_by_tillage                          
CSVP_soil_C_removed_by_harvest
CSVP_soil_C_decomposed_SOM_profile
CSVP_soil_C_decomposed_SOM_5cm
CSVP_soil_C_decomposed_SOM_10cm
CSVP_soil_C_decomposed_SOM_15cm
CSVP_soil_C_decomposed_SOM_30cm
CSVP_soil_C_decomposed_SOM_60cm
CSVP_soil_C_decomposed_SOM_90cm

// soil nitrogen

CSVP_soil_N_available

CSVP_soil_N_input
CSVP_soil_N_output
// Soil pond
CSVP_soil_pond_water_depth

CSVP_soil_base_water_content 1-31
CSVP_soil_base_plant_avail_water 1-31
CSVP_soil_base_water_potential 1-31
CSVP_soil_base_lateral_in_flow_depth 1-31
CSVP_soil_base_lateral_out_flow_depth 1-31
CSVP_soil_base_temperature   1-31

CSVP_soil_N_mineralization 1-31


CSVP_soil_P_P_amount 1-31
CSVP_soil_base_salinity 1-31
CSVP_soil_base_salt 1-31
*/
CORN::Parameter_properties_literal PPL_act_evaporation                           ={"soil_evap_act"       ,"Ea"       ,"evap_act","evaporation actual","hint_NYN","URL_NYN",UC_m,"prefered_units_caption_or_date_time_format"};
CORN::Parameter_properties_literal PPL_act_water_entering_soil                   ={"soil_water_entering" ,"wes"      ,"water_entering","water entering actual","hint_NYN","URL_NYN",UC_m,"prefered_units_caption_or_date_time_format"};
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

150915 continue here

#ifndef MICROBASIN_VERSION
const CS::Reporter &Soil_base::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
)                      /*rendition_*/
{  recorders.append(new CS::Variable_recorder(act_evaporation         ,CSVP_soil_base_evap_act      ,PPL_act_evaporation          ,UC_mm,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));
   recorders.append(new CS::Variable_recorder(act_water_entering_soil ,CSVP_soil_base_water_entering,PPL_act_water_entering_soil  ,UC_mm,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));
   Soil_hydrology_interface *hydrology = mod_hydrology();
   if (hydrology) hydrology->render_listeners(recorders,desired_descriptive_summary_elements);
   return true; // NYI
}
#endif
//_2013-09-09___________________________________________________________________
Parameter_properties_literal PP_soil_water_depth_profile_LEQ                     ={"soil_water_depth_profile_LEQ"                            ,"water_depth"                 ,"water_depth_profile","Soil water depth profile"                 ,"liquid water and ice (liquid water equivelent)","URL_NYN",UC_meter               ,"m"};


//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#ifndef MICROBASIN_VERSION
const CS::Reporter &Soil_hydrology_abstract::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   // for start of period
   recorders.append(new CS::Variable_recorder(depth_profile_water[1].amount,CSVP_soil_base_water_depth,PP_soil_water_depth_profile_LEQ,UC_mm,desired_descriptive_summary_elements&STAT_initial_bit,initial_statistic));  // WARNING verify statistics to use
   //for end of period
   recorders.append(new CS::Variable_recorder(depth_profile_water[1].amount,CSVP_soil_base_water_depth,PP_soil_water_depth_profile_LEQ,UC_mm,desired_descriptive_summary_elements&STAT_value_bit,value_statistic));  // WARNING verify statistics to use
   return true; // NYI
}
#endif
//_2013-09-30___________________________________________________________________

Parameter_properties_literal PP_soil_N_leached           ={"leached"                ,"lchd_N"      ,"leached"        ,"nitrogen leached"      ,"hint_NYN"                      ,"http://en.wikipedia.org/wiki/Leaching_(agriculture)#Nitrogen_leaching",UC_kg_m2,"kg/m�"};
Parameter_properties_literal PP_soil_N_denitrification   ={"soil_N_denitrification" ,"dntrfctn_N"  ,"denitrification","soil denitrification N","hint_NYN"                      ,"http://en.wikipedia.org/wiki/Denitrification"                         ,UC_kg_m2,"kgN/m�"};
Parameter_properties_literal PP_soil_N_nitrification     ={"soil_N_nitrification"   ,"ntrfctn_N"   ,"nitrification"  ,"soil nitrification N"  ,"hint_NYN"                      ,"http://en.wikipedia.org/wiki/Nitrification"                           ,UC_kg_m2,"kgN/m�"};

Parameter_properties_literal PP_soil_N_NO3               ={"soil_N_NO3"             ,"NO3_N"       ,"NO3"          ,"Soil profile NO3 N"    ,"nitrate nitrogen"              ,"http://en.wikipedia.org/wiki/Nitrate"                                 ,UC_kg_m2,"kgN/m�"};
Parameter_properties_literal PP_soil_N_NH4               ={"soil_N_NH4"             ,"NH4_N"       ,"NH4"          ,"Soil profile NH4 N"    ,"ammonia nitrogen"              ,"http://en.wikipedia.org/wiki/"                                        ,UC_kg_m2,"kgN/m�"};
Parameter_properties_literal PP_soil_N_total             ={"soil_N_total"           ,"total_N"     ,"total"        ,"Soil profile total N"  ,"nitrate and ammonia nitrogen"  ,"http://en.wikipedia.org/wiki/Soil#Nitrogen"                           ,UC_kg_m2,"kgN/m�"};
//______________________________________________________________________________
const CS::Reporter &Soil_chemicals_profile::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{  bool rendered = true;
   rendered &= recorders.append(new CS::Variable_recorder( daily_N_leached                ,CSVP_soil_N_leached          ,PP_soil_N_leached,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)) != NULL;
   rendered &= recorders.append(new CS::Variable_recorder((denitrification_N_E_output[0]) ,CSVP_soil_N_denitrification  ,PP_soil_N_denitrification ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)) != NULL;  // WARNING verify statistics to use
   rendered &= recorders.append(new CS::Variable_recorder((nitrification_N_E_output  [0]) ,CSVP_soil_N_nitrification    ,PP_soil_N_nitrification   ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)) != NULL;  // WARNING verify statistics to use
   // For start of period
   rendered &= recorders.append(new CS::Variable_recorder(total_N_E[0]     ,CSVP_soil_N_N_amount   ,PP_soil_N_total  ,UC_kg_ha,desired_descriptive_summary_elements&STAT_initial_bit,initial_statistic))  != NULL; // Not sure if STAT_initial_bit or STAT_value_bit
   rendered &= recorders.append(new CS::Variable_recorder(NO3_N_E_output[0],CSVP_soil_N_NO3_amount ,PP_soil_N_NO3    ,UC_kg_ha,desired_descriptive_summary_elements&STAT_initial_bit,initial_statistic))  != NULL; // Not sure if STAT_initial_bit or STAT_value_bit
   rendered &= recorders.append(new CS::Variable_recorder(NH4_N_E_output[0],CSVP_soil_N_NH4_amount ,PP_soil_N_NH4    ,UC_kg_ha,desired_descriptive_summary_elements&STAT_initial_bit,initial_statistic))  != NULL; // Not sure if STAT_initial_bit or STAT_value_bit
   // For end of period
   rendered &= recorders.append(new CS::Variable_recorder(total_N_E[0]     ,CSVP_soil_N_N_amount   ,PP_soil_N_total  ,UC_kg_ha,desired_descriptive_summary_elements&STAT_value_bit,value_statistic))  != NULL;
   rendered &= recorders.append(new CS::Variable_recorder(NO3_N_E_output[0],CSVP_soil_N_NO3_amount ,PP_soil_N_NO3    ,UC_kg_ha,desired_descriptive_summary_elements&STAT_value_bit,value_statistic))  != NULL;
   rendered &= recorders.append(new CS::Variable_recorder(NH4_N_E_output[0],CSVP_soil_N_NH4_amount ,PP_soil_N_NH4    ,UC_kg_ha,desired_descriptive_summary_elements&STAT_value_bit,value_statistic))  != NULL;
   return rendered;
}
//_2013-09-11___________________________________________________________________
CORN::Parameter_properties_literal PP_crop_season_duration                       ={"season_duration"                 ,"duration"                     ,"duration"                     ,"Season duration"                   ,"hint_NYN","URL_NYN",UT_day              ,"days"};
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
const CS::Reporter &Phenology_common::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   //NYI crashes recorders.append(new CS::Variable_recorder(days_since_start_of[NGS_GERMINATION],CSVP_crop_base_season_duration,PP_crop_season_duration,UT_day,STAT_value_bit,CORN::mean_statistic) ); /* not sure if I want max or mean for the annual aggregation, I think it is not applicable to annual aggregation*/
   return true;
}
//_2013-09-18________________________________________render_variable_recorders_/
Parameter_properties_literal PP_crop_base_root_depth                                ={"root_depth"                            ,"root_depth"                 ,"root:depth"    ,"root depth"                              ,"hint_NYN","URL_NYN",UC_meter               ,"units"};
Parameter_properties_literal PP_crop_base_root_biomass_current                      ={"root_biomass"                          ,"root_BM"                    ,"root:biomass"  ,"root biomass"                             ,"hint_NYN","URL_NYN",UC_kg_m2              ,"units"};
/*NYN
Parameter_properties_literal PP_crop_base_root_fraction 1-31                            ={"root_fraction"                         ,"root_frct"                  ,"root fraction"                           ,"hint_NYN","URL_NYN",UC_fraction            ,"units"};
*/
const CS::Reporter &Crop_root_common::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
/*NYI
CSVP_crop_base_root_fraction   1-31
*/
   recorders.append(new CS::Variable_recorder(biomass,CSVP_crop_base_root_biomass_current,PP_crop_base_root_biomass_current,UC_kg_ha,desired_descriptive_summary_elements&STAT_value_bit,value_statistic)); // the annual value is the value at the end of the year
   return true;
}
//_2013-09-09__________________________________________________________________/
const CS::Reporter &Crop_root_vital::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   recorders.append(new CS::Variable_recorder(apparent_root_depth,CSVP_crop_base_root_depth,PP_crop_base_root_depth,UC_m,desired_descriptive_summary_elements&STAT_value_bit,value_statistic));
   return Crop_root_common::render_listeners(recorders,desired_descriptive_summary_elements);
}
//_2013-09-09__________________________________________________________________/
//NYN Parameter_properties_literal PP_crop_base_growing_degree_day               ={"growing_degree_day"                   ,"GDD"                       ,"GDD"        ,"growing degree day"                      ,"hint_NYN","URL_NYN",UC_Celcius_degree_days,"units"};
Parameter_properties_literal PP_crop_base_growing_degree_days                    ={"growing_degree_days"                  ,"GDDs"                      ,"GDDs"       ,"growing degree days"                     ,"hint_NYN","URL_NYN",UC_Celcius_degree_days,"units"};
Parameter_properties_literal PP_crop_base_seasonal_thermal_time                  ={"seasonal_thermal_time"                ,"GDDseasonal"               ,"GDDseasonal","seasonal thermal time"                ,"hint_NYN","URL_NYN",UC_Celcius_degree_days,"units"};

const CS::Reporter &Crop_thermal_time::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   //NYN  recorders.append(new CS::Variable_recorder(_value,CSVP_crop_base_growing_degree_day                               ,PP_crop_base_growing_degree_day                                      ,desired_descriptive_summary_elements));
   recorders.append(new CS::Variable_recorder(accum_degree_days_clipped[0]          ,CSVP_crop_base_growing_degree_days                               ,PP_crop_base_growing_degree_days                                      ,UC_Celcius_degree_days,desired_descriptive_summary_elements&STAT_value_bit,value_statistic)); // the
   recorders.append(new CS::Variable_recorder(accum_degree_days_normal[0]           ,CSVP_crop_base_seasonal_thermal_time                             ,PP_crop_base_seasonal_thermal_time                                    ,UC_Celcius_degree_days,desired_descriptive_summary_elements&STAT_value_bit,value_statistic));
   return true;
}
//_2013-09-09__________________________________________________________________/
Parameter_properties_literal PP_soil_base_water_drainage                         ={"soil_water_drainage"                            ,"drainage"                 ,"drainage","soil water drainage"                 ,"hint_NYN","URL_NYN",UC_meter               ,"m"};
const CS::Reporter &Soil_infiltration_nominal::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   recorders.append(new CS::Variable_recorder(reported_drainage,CSVP_soil_base_water_drainage,PP_soil_base_water_drainage,UC_mm,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));
   return true;
}
//_2013-07-30_______________________________________render_variable_recorders__/
const CS::Reporter &CropSyst::Soil::render_listener::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   if (chemicals) chemicals->render_listeners(recorders,desired_descriptive_summary_elements);
   //NYI if (erosion) erosion->render_listeners(recorders,desired_descriptive_summary_elements);
   //NYI if (tillage_effect) tillage_effect->render_listeners(recorders,desired_descriptive_summary_elements);
   return Soil_base::render_listeners(recorders,desired_descriptive_summary_elements);
}
//_2013-09-11___________________________________________________________________
namespace CropSyst {
const CS::Reporter &Crop_interfaced_complete::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{   return Crop_CropSyst::render_listeners(recorders,desired_descriptive_summary_elements);
}
#if (CROPSYST_VERSION >= 5)
} //namespace CropSyst
#endif
//______________________________________________________________________________
Parameter_properties_literal PP_N2O_emmission_denitrification                    ={"N_N2O_emission_denitrification"                            ,"N2Oemissdenitr"                 ,"N2Odenitr","N2O emission from denitrification"                 ,"hint_NYN","URL_NYN",UC_kg_m2               ,"kg/m�"};
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
const CS::Reporter &NO3_with_CO2_Profile::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   recorders.append(new CS::Variable_recorder(N2O_N_loss_daily,CSVP_soil_N_N2O_loss_denitrification,PP_N2O_emmission_denitrification,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));
   return true;
}
//______________________________________________________________________________
Parameter_properties_literal PP_N2O_emmission_nitrification                      ={"N_N2O_emission_nitrification"                            ,"N2Oemissnitr"                 ,"N2Onitr","N2O emission from nitrification"                 ,"hint_NYN","URL_NYN",UC_kg_m2               ,"kg/m�"};
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
const CS::Reporter &NH4_Profile_with_pH::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   recorders.append(new CS::Variable_recorder(N2O_N_loss_daily,CSVP_soil_N_N2O_loss_nitrification,PP_N2O_emmission_nitrification,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));
   return true;
}
//______________________________________________________________________________
Parameter_properties_literal PP_N_OM_mineralization_profile                      ={"OM_N_mineralization_profile"             ,"mnrlztn_N"                 ,"mineralization_N"    ,"Organic matter mineralization N soil profile","hint_NYN","URL_NYN",UC_kg_m2               ,"kgN/m�"};
Parameter_properties_literal PP_N_OM_immobilization_profile                      ={"OM_N_immobilization_profile"             ,"immblztn_N"                ,"immobilization_N"    ,"Immobilization N soil profile"               ,"hint_NYN","URL_NYN",UC_kg_m2               ,"kgN/m�"};
Parameter_properties_literal PP_organic_matter_CO2_C_loss_OM                     ={"CO2_C_loss_OM"                           ,"CO2_C_loss_OM"             ,"CO2_C_loss"          ,"Organic matter CO2 C loss"                   ,"includes residue and stable organic matter decomposition","URL_NYN",UC_kg_m2 ,"kgC/m�"};
Parameter_properties_literal PP_organic_matter_CO2_C_loss_SOM                    ={"CO2_C_loss_SOM"                          ,"CO2_C_loss_SOM"            ,"CO2_C_loss_stable"   ,"Stable Organic matter CO2 C loss"            ,"hint_NYN","URL_NYN",UC_kg_m2               ,"kgC/m�"};
Parameter_properties_literal PP_organic_matter_CO2_C_loss_residue                ={"CO2_C_loss_residue"                      ,"CO2_C_loss_residue"        ,"CO2_C_loss_residue"  ,"Residue CO2 C loss"                          ,"hint_NYN","URL_NYN",UC_kg_m2               ,"kgC/m�"};

/* NYI



CSVP_organic_matter_percent     1-31
CSVP_organic_matter_N_mineralization_5cm
CSVP_organic_matter_N_mineralization_10cm
CSVP_organic_matter_N_mineralization_15cm
CSVP_organic_matter_N_mineralization_30cm
CSVP_organic_matter_N_mineralization_60cm
CSVP_organic_matter_N_mineralization_90cm
CSVP_soil_N_immobilization_5cm
CSVP_soil_N_immobilization_10cm
CSVP_soil_N_immobilization_15cm
CSVP_soil_N_immobilization_30cm
CSVP_soil_N_immobilization_60cm
CSVP_soil_N_immobilization_90cm
*/
const CS::Reporter &Organic_matter_residues_profile_common::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{  bool rendered = true;

   if (organic_matter_pools_profile_owned) rendered |= organic_matter_pools_profile_owned->render_listeners(recorders,desired_descriptive_summary_elements);
   // NYN rendered |= residues.render_listeners(recorders,desired_descriptive_summary_elements);
   return true;
}
//______________________________________________________________________________
const CS::Reporter &Organic_matter_pools_common::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   recorders.append(new CS::Variable_recorder(today_OM_mineralized_kgN_m2        ,CSVP_organic_matter_N_mineralization_profile,PP_N_OM_mineralization_profile        ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)); // WARNING verify statistics to use
   recorders.append(new CS::Variable_recorder(today_N_immobilized                ,CSVP_soil_N_immobilization_profile          ,PP_N_OM_immobilization_profile        ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)); // WARNING verify statistics to use
   recorders.append(new CS::Variable_recorder(CO2_C_loss_daily[0]                ,CSVP_organic_matter_CO2_C_loss_OM           ,PP_organic_matter_CO2_C_loss_OM       ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)); // WARNING verify statistics to use
   recorders.append(new CS::Variable_recorder(CO2_C_loss_daily[1]                ,CSVP_organic_matter_CO2_C_loss_SOM          ,PP_organic_matter_CO2_C_loss_SOM      ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)); // WARNING verify statistics to use
   recorders.append(new CS::Variable_recorder(CO2_C_loss_daily[2]                ,CSVP_organic_matter_CO2_C_loss_residue      ,PP_organic_matter_CO2_C_loss_residue  ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)); // WARNING verify statistics to use
   return true;
}
//______________________________________________________________________________
Parameter_properties_literal PP_runoff_surface_water        ={"runoff_surface_water"   ,"runoff"   ,"runoff"               ,"surface water runoff"  ,"hint_NYN","http://en.wikipedia.org/wiki/Surface_runoff",UC_m       ,"m"};
Parameter_properties_literal PP_NH3_volatilization_loss     ={"volatilization_N_NH3"   ,"vol_N_NH3","volatilization_N_NH3" ,"volatilization N (NH3)","hint_NYN","URL_NYN"                                    ,UC_kg_m2   ,"kg/m�"};
Parameter_properties_literal PP_total_volatilization_loss   ={"volatilization_N_total" ,"vol_N"    ,"volatilization_N"     ,"volatilization N","applied organic and inorganic atmospheric losses","URL_NYN"                ,UC_kg_m2   ,"kg/m�"};
Parameter_properties_literal PP_N_applied_total             ={"application_N_total"    ,"appl_N_total","appl_N_total"      ,"Total application N","applied organic and inorganic","URL_NYN"                ,UC_kg_m2   ,"kg/m�"};

Parameter_properties_literal PP_C_profile                   ={"C_profile"  ,"C_prof","C_profile","organic matter C soil profile"                 ,"hint_NYN","http://en.wikipedia.org/wiki/Soil_carbon",UC_kg_m2               ,"kg/m�"};
//NYI Parameter_properties_literal PP_C_5cm                 ={"C_5cm"      ,"C_5cm" ,"C_5cm","organic matter C to depth 5cm"                 ,"hint_NYN","http://en.wikipedia.org/wiki/Soil_carbon",UC_kg_m2               ,"kg/m�"};
//NYI Parameter_properties_literal PP_C_10cm                ={"C_10cm"     ,"C_10cm","C_10cm","organic matter C to depth  10cm"                 ,"hint_NYN","http://en.wikipedia.org/wiki/Soil_carbon",UC_kg_m2               ,"kg/m�"};
//NYI Parameter_properties_literal PP_C_15cm                ={"C_15cm"     ,"C_15cm","C_15cm","organic matter C to depth  15cm"                 ,"hint_NYN","http://en.wikipedia.org/wiki/Soil_carbon",UC_kg_m2               ,"kg/m�"};
Parameter_properties_literal PP_C_30cm                      ={"C_30cm"     ,"C_30cm","C_30cm","organic matter C 30cm"                 ,"hint_NYN","http://en.wikipedia.org/wiki/Soil_carbon",UC_kg_m2               ,"kg/m�"};
//NYI Parameter_properties_literal PP_C_60cm                ={"C_60cm"     ,"C_60cm","C_60cm","organic matter C to depth  60cm"                 ,"hint_NYN","http://en.wikipedia.org/wiki/Soil_carbon",UC_kg_m2               ,"kg/m�"};
//NYI Parameter_properties_literal PP_C_90cm                ={"C_90cm"     ,"C_15cm","C_90cm","organic matter C to depth  90cm"                 ,"hint_NYN","http://en.wikipedia.org/wiki/Soil_carbon",UC_kg_m2               ,"kg/m�"};

Parameter_properties_literal PP_weather_precipitation       ={"precipitation"    ,"precip"      ,"precipitation"  ,"precipitation"      ,"liquid water equilvelent"                        ,"http://en.wikipedia.org/wiki/Precipitation"            ,UC_m       ,"m"};
Parameter_properties_literal PP_weather_ET_actual           ={"ET_act"           ,"ET_act"      ,"ET_act"         ,"evapotranspiration" ,"actual"                                          ,"http://en.wikipedia.org/wiki/Evapotranspiration"       ,UC_m       ,"m"};
Parameter_properties_literal PP_weather_air_temperature     ={"air_temperature"  ,"Tair"        ,"Tair"           ,"air temperature"    ,"daily mean"                                      ,"http://en.wikipedia.org/wiki/Atmospheric_temperature"  ,UC_Celcius ,"�C"};
// I need to standarize the solar radiation variable name
Parameter_properties_literal PP_weather_solar_radiation     ={"solar_radiation"  ,"solar_rad"   ,"solar_radiation","solar radiation"    ,"global solar irradiance,insolation (shortwave)"  ,"http://en.wikipedia.org/wiki/Insolation"               ,UC_MJ_m2   ,"MJ/m�"};


//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#if (CROPSYST_VERSION >= 5)
namespace CropSyst {
#endif
const CS::Reporter &Land_unit_simulation_VX::render_inspectors
      (CS::Inspectors      &inspectors
      ,const CS::Reporter  *context
      ,const char          *instance_description
      ,CORN::Statistic      statistic)                                rendition_
{
   if (runoff) // Eventually move this to runoff
      recorders.append(new CS::Variable_recorder(runoff->estimated_runoff                       ,CSVP_soil_runoff_surface_water_runoff ,PP_runoff_surface_water      ,UC_mm   ,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)); // WARNING verify statistics to use
   recorders   .append(new CS::Variable_recorder(nitrogen_daily_output.volatilization_loss_NH3  ,CSVP_soil_N_NH3_volatilization        ,PP_NH3_volatilization_loss   ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)); // WARNING verify statistics to use
   recorders   .append(new CS::Variable_recorder(nitrogen_daily_output.volatilization_total     ,CSVP_soil_N_volatilization_total      ,PP_total_volatilization_loss ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)); // WARNING verify statistics to use
   recorders   .append(new CS::Variable_recorder(nitrogen_daily_output.applied_total            ,CSVP_mgmt_N_applied                   ,PP_N_applied_total           ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic)); // WARNING verify statistics to use

//NYI CSVP_soil_C_all_surface
   recorders.append(new CS::Variable_recorder(profile_carbon_output.sum_profile  ,CSVP_soil_C_all_profile,PP_C_profile  ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
//NYI recorders.append(new CS::Variable_recorder(XXXXX                           ,CSVP_soil_C_all_5cm    ,PP_C_5cm      ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
//NYI recorders.append(new CS::Variable_recorder(XXXXX                           ,CSVP_soil_C_all_10cm   ,PP_C_10cm     ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
//NYI recorders.append(new CS::Variable_recorder(XXXXX                           ,CSVP_soil_C_all_15cm   ,PP_C_15cm     ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
   recorders.append(new CS::Variable_recorder(profile_carbon_output.sum_30cm     ,CSVP_soil_C_all_30cm   ,PP_C_30cm     ,UC_kg_ha,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
//NYI CSVP_soil_C_all_60cm
//NYI CSVP_soil_C_all_90cm

//NYI CSVP_mgmt_N_organic_applied
//NYI CSVP_mgmt_N_inorganic_applied

   recorders.append(new CS::Variable_recorder(ET->act_crop_evapotransp_m         ,UED::STD_VC_act_evapotranspiration.get(),PP_weather_ET_actual       ,UC_mm      ,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use


#ifdef USE_WEATHER_PROVIDER
/*NYI
   recorders.append(new CS::Variable_recorder(XXXXX                              ,UED::STD_VC_precipitation         .get(),PP_weather_precipitation   ,UC_mm      ,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
   recorders.append(new CS::Variable_recorder(XXXXX                              ,UED::STD_VC_avg_temperature       .get(),PP_weather_air_temperature ,UC_celcius ,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
   recorders.append(new CS::Variable_recorder(XXXXX                              ,UED::STD_VC_solar_radiation_global.get(),PP_weather_solar_radiation ,UC_MJ_m2   ,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
   */
#else
   recorders.append(new CS::Variable_recorder(weather->curr_precipitation_m      ,UED::STD_VC_precipitation         .get(),PP_weather_precipitation   ,UC_mm      ,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
/*140513 Need to reimplements because now using Weather_parameter
   recorders.append(new CS::Variable_recorder(weather->curr_avg_air_temperature  ,UED::STD_VC_avg_temperature       .get(),PP_weather_air_temperature ,UC_Celcius ,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
   recorders.append(new CS::Variable_recorder
      (&weather->curr_solar_radiation                       //140715
      //140715 curr_solar_radiation_MJ_m2
      ,UED::STD_VC_solar_radiation_global.get(),PP_weather_solar_radiation ,UC_MJ_m2   ,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
*/
#endif

   return true;
}
} // namespace CropSyst
//______________________________________________________________________________
/*
Parameter_properties_literal PP_XXXXX                                ={"XXXXX"                            ,"XXXXX"                 ,"XXXXX","Xxxxx"                 ,"hint_NYN","URL_NYN",UC_actual               ,XXX"m"};
recorders.append(new CS::Variable_recorder(XXXXX,CSVP_XXXXX,PP_XXXXX,UC_prefered,desired_descriptive_summary_elements&(STAT_sum_bit|STAT_value_bit),sum_statistic));  // WARNING verify statistics to use
*/


