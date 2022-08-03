#include "crop_param_configured.h"
#include "corn/data_source/datarec.h"
//---------------------------------------------------------------------------
//  Parameter_properties XXX_param_props = {"key",field_width,"caption","hint","%PROG_HOME%:path/document.HTM#anchor",};  Parameter_number_properties XXX_param_props_numeric = {_units_code,"units_units_or_NULL",_min_warning,_max_warning,_min_error,_max_error,optional_precision,optional_radix};
//
//Note that Field widths are as used in LADSS
//if the field width has /*9!*/ 9 is the field with used in LADSS but this is not adequate
// - indicates not yet implemented in LADSS
// / indicates not needed in LADSS
// ? indicates not sure what field width to use.
#define NO_HINT 0
#define NoAltFieldName 0
#define NotYetSubsection "NotYetSubsection"
#include "static_phrases.h"

#ifdef LADSS_MODE
extern bool LADSS_mode;
#endif
using namespace CORN;
//______________________________________________________________________________
namespace CropSyst
{
//______________________________________________________________________________
CropSyst::Crop_parameters::Crop_parameters()
: Crop_parameters_class()
{}
//______________________________________________________________________________
CropSyst::Crop_parameters_configured::Crop_parameters_configured(modifiable_ Crop_parameters &parameters_)
: CS::Document_configured()
, parameters(parameters_)
{
}
//______________________________________________________________________________
bool CropSyst::Crop_parameters_configured::initialize_parameter_associations() initialization_
{

//The following line is for debug only delete it
//   parameter_associations.append(new CS::Parameter_association_bool   (parameters.tolerance.enabled                          ,"ecophysiology/tolerance/temperature/enabled"));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.continuous_cultivation_impact_factor,"biomass/production/continuous_cultivation_impact"  ,ADJUSTABLE,POT_OBSERVABLE));

//The following line is for debug only delete it
//   parameter_associations.append(new CS::Parameter_association_numeric(parameters.tolerance.temperature_cold_fruit_damage    ,"ecophysiology/tolerance/temperature/cold/fruit/damage"      ,POT_ADJUSTABLE,POT_OBSERVABLE));



//#ifdef TEMP_DISABLED

   //NYI enum RUE basis
   #if (CROPSYST_VERSION==4)
   // always PAR based in V5
   parameter_associations.append(new CS::Parameter_association_enum   (parameters.biomass_production.RUE_basis_cowl                      ,"biomass/production/RUE/basis"));
   #endif
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.RUE_global                          ,"biomass/production/RUE/global"                     ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.RUE_PAR                             ,"biomass/production/RUE/PAR"                        ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.low_threshold_limit_temp            ,"biomass/production/RUE/temperature/threshold/low"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.high_threshold_limit_temp           ,"biomass/production/RUE/temperature/threshold/high" ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.min_tolerable_temp                  ,"biomass/production/RUE/temperature/tolerable/min"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.max_tolerable_temp                  ,"biomass/production/RUE/temperature/tolerable/maximum"  ,POT_ADJUSTABLE,POT_OBSERVABLE));

   // obsolete in V5 bool WUE_changes

   //V4 parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.early_growth_limit_temp             ,"biomass/production/RUE/temperature/optimal"   ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_enum  (parameters.biomass_production.TUE_equation_cowl                              ,"biomass/production/TUE/equation"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.TUE_at_1kPa_VPD_adjustable                     ,"biomass/production/TUE/at_1kPa_VPD"           ,ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.reference_biomass_transpiration_coef_adjustable,"biomass/production/TUE/biomass_transpiration_coef",ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.TUE_scaling_coef_adjustable                    ,"biomass/production/TUE/scaling_coef"          ,ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.biomass_production.water_productivity_adjustable                  ,"biomass/production/TUE/water_productivity"    ,ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_cover_based.initial_cover                   ,"canopy/cover/initial"             ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_cover_based.maximum_cover_no_CO2_adj        ,"canopy/cover/maximum/no_CO2_adj"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_cover_based.maximum_cover_CO2_adj           ,"canopy/cover/maximum/CO2_adj"     ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_cover_based.mature_total_cover              ,"canopy/cover/mature/total"              ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.morphology.reduce_canopy_expansion_LWP                 ,"canopy/expansion/LWP/reduces" ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.morphology.stop_canopy_expansion_LWP                   ,"canopy/expansion/LWP/stops"   ,POT_ADJUSTABLE,POT_OBSERVABLE));

   //parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_cover_based.full_senescence_green_cover_obsolete_150210                  ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_cover_based.fract_season_to_reach_cover_max_half  ,"canopy/growth/cover_based/fract_season_to_reach_cover_max_half"               ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_characteristics_hedge_row.initial_height           ,"canopy/height/initial"            ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_characteristics_hedge_row.final_height             ,"canopy/height/final"              ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_enum   (parameters.morphology.canopy_growth_cowl                           ,"canopy/growth/model"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.morphology.max_canopy_height                           ,"canopy/height/max"            ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.morphology.kc                                          ,"canopy/light_extinction_coef" ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_characteristics_hedge_row.initial_breadth          ,"canopy/breadth/initial"           ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_characteristics_hedge_row.final_breadth            ,"canopy/breadth/final"             ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_characteristics_hedge_row.initial_width            ,"canopy/width/initial"             ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_characteristics_hedge_row.final_width              ,"canopy/width/final"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_characteristics_hedge_row.branch_insertion_height  ,"canopy/branch_insertion_height"   ,POT_ADJUSTABLE,POT_OBSERVABLE));

   // NYI parameter_associations.append(new CS::Parameter_association_enum(parameters.phenology.stages                                      ,"phenology/stages"));

   parameter_associations.append(new CS::Parameter_association_bool(parameters.phenology.clipping_resets                             ,"phenology/clipping_resets"));
   // NYI phenology.maturity significant
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.phenologic_sensitivity_water_stress       ,"phenology/stress_sensitivity/water",POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.emergence                      ,"phenology/emergence/initiation"   ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.tuber                          ,"phenology/tuber/initiation"       ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.flowering                      ,"phenology/anthesis/initiation"    ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.filling                        ,"phenology/filling/initiation"     ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.rapid_fruit_growth             ,"phenology/rapid_fruit_growth/initiation"     ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.maturity                       ,"phenology/maturity/initiation"    ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.senescence                     ,"phenology/senescence/initiation"  ,NOT_ADJUSTABLE,    OBSERVABLE));
   //parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.rapid_fruit_growth             ,"phenology/initiation/structure",NOT_ADJUSTABLE,    OBSERVABLE));
   //parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.peak_LAI_or_rapid_fruit_growth ,"phenology/initiation/structure",NOT_ADJUSTABLE,    OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.culmination.accrescence                   ,"phenology/accrescence/culmination",NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.culmination.senescence                    ,"phenology/senescence/culmination" ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.culmination.root_depth                    ,"phenology/root_elongation/culmination" ,NOT_ADJUSTABLE,    OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_enum(parameters.emergence.emergence_model_cowl             ,"phenology/germination/model"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.emergence.a_slope                       ,"phenology/germination/hydrothermaltime/constant/slope"        ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.emergence.b_intercept                   ,"phenology/germination/hydrothermaltime/constant/intercept"    ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.emergence.seedling_leaf_area_cm2        ,"phenology/germination/hydrothermaltime/seedling_leaf_area"    ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.emergence.germination_base_temperature  ,"phenology/germination/hydrothermaltime/base_temperature"      ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.emergence.mean_base_soil_water_pot_J_kg ,"phenology/germination/hydrothermaltime/base_SWP/mean"         ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.emergence.stdev_base_soil_water_pot_J_kg,"phenology/germination/hydrothermaltime/base_SWP/stdev"        ,POT_ADJUSTABLE,POT_OBSERVABLE));


/*
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.emergence                      ,"phenology/initiation/emergence"   ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.tuber                          ,"phenology/initiation/tuber"       ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.flowering                      ,"phenology/initiation/anthesis"    ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.filling                        ,"phenology/initiation/filling"     ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.maturity                       ,"phenology/initiation/maturity"    ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.senescence                     ,"phenology/initiation/senescence"  ,NOT_ADJUSTABLE,    OBSERVABLE));
   //parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.rapid_fruit_growth             ,"phenology/initiation/structure",NOT_ADJUSTABLE,    OBSERVABLE));
   //parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.initiation.peak_LAI_or_rapid_fruit_growth ,"phenology/initiation/structure",NOT_ADJUSTABLE,    OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.culmination.accrescence                   ,"phenology/culmination/accrescence",NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.culmination.senescence                    ,"phenology/culmination/senescence" ,NOT_ADJUSTABLE,    OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.phenology.culmination.root_depth                    ,"phenology/culmination/root_depth" ,NOT_ADJUSTABLE,    OBSERVABLE));
*/

   parameter_associations.append(new CS::Parameter_association_enum   (parameters.thermal_time.thermal_response_cowl   ,"ecophysiology/thermal_time/response"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.thermal_time.base_temperature        ,"ecophysiology/thermal_time/threshold/base"     ,ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.thermal_time.cutoff_temperature      ,"ecophysiology/thermal_time/threshold/cutoff"   ,ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.thermal_time.opt_temperature         ,"ecophysiology/thermal_time/threshold/optimal"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.thermal_time.max_temperature         ,"ecophysiology/thermal_time/threshold/maximum"  ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_bool   (parameters.vernalization.enabled                ,"ecophysiology/vernalization/enabled"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.vernalization.low_temp               ,"ecophysiology/vernalization/temperature_optimal/low"   ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.vernalization.high_temp              ,"ecophysiology/vernalization/temperature_optimal/high"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.vernalization.start                  ,"ecophysiology/vernalization/day_requirement/start"       ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.vernalization.end                    ,"ecophysiology/vernalization/day_requirement/end"         ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.vernalization.min_factor             ,"ecophysiology/vernalization/minimum_factor"            ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_enum   (parameters.photoperiod.photoperiodism_cowl      ,"ecophysiology/photoperiodism"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.photoperiod.stop_day_length          ,"ecophysiology/photoperiod/day_length/stop"            ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.photoperiod.unconstrained_day_length ,"ecophysiology/photoperiod/day_length/unconstrained"   ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.transpiration.ET_coef                               ,"transpiration/ET_coef"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.transpiration.LWP_wilt_point                        ,"transpiration/LWP_wilt"              ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.transpiration.LWP_stomatal_closure                  ,"transpiration/LWP_stomatal_closure"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.transpiration.normal_max_water_uptake_mm            ,"transpiration/maximum"               ,    ADJUSTABLE,POT_OBSERVABLE));
   // Special adjustment to ET_coef by VPD for Jordi Marsal (not sure if still needed)
   //parameter_associations.append(new CS::Parameter_association_numeric(parameters.transpiration.a1                                    ,"transpiration/intercept"             ,POT_ADJUSTABLE,POT_OBSERVABLE));
   //parameter_associations.append(new CS::Parameter_association_numeric(parameters.transpiration.a2                                    ,"transpiration/slope"                 ,POT_ADJUSTABLE,POT_OBSERVABLE));


   parameter_associations.append(new CS::Parameter_association_bool   (parameters.harvest.apply_adjustment_to_unstressed_harvest_index, "yield/harvest_index/apply_adjustments"));
   parameter_associations.append(new CS::Parameter_association_bool   (parameters.harvest.apply_heat_extreme_adjustment_to_unstressed_harvest_index, "yield/harvest_index/extreme_heat_sensitivity"));
   //probably obsolete in V5 editor_grain_stress_sensitivity
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.harvest.index_unstressed             ,"yield/harvest_index/unstressed"            ,POT_ADJUSTABLE,POT_OBSERVABLE));
//   parameter_associations.append(new CS::Parameter_association_numeric(harvest.stress_sensitivity_growth           ,"yield/stress_sensitivity/water_nitrogen"   ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.harvest.stress_sensitivity_growth     ,"yield/stress_sensitivity/accrescence"     ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.harvest.stress_sensitivity_tuber_init ,"yield/stress_sensitivity/tuber_initiation",    ADJUSTABLE,POT_OBSERVABLE)); // applies only to tuber model
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.harvest.tuber_growth_sensitivity      ,"yield/stress_sensitivity/tuber_filling"   ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.harvest.translocation_fraction_max   ,"yield/translocation/maximum"               ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.initial_depth                   ,"root/depth/initial"               ,    ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.max_depth                       ,"root/depth/maximum"                 ,    ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.length_at_emergence_cm          ,"root/length/emergence"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.surface_density                 ,"root/density/surface"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.density_distribution_curvature  ,"root/density/distribution_curvature",NOT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.length_per_unit_mass_km_kg_V4   ,"root/length/per_unit_mass"          ,POT_ADJUSTABLE,POT_OBSERVABLE));
   /*conceptual I think this should be an interpolatable curve, but need to work it out
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.root_shoot_emergence_ratio      ,"root/shoot_ratio"                      ,ADJUSTABLE,POT_OBSERVABLE));
   */
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.root_shoot_emergence_ratio      ,"root/shoot_ratio/emergence"         ,NOT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.root_shoot_full_ratio           ,"root/shoot_ratio/culmination"              ,NOT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.root.sensitivity_to_water_stress     ,"root/stress_sensitivity/water"    ,POT_ADJUSTABLE,POT_OBSERVABLE));
   //was for VIC parameter_associations.append(new CS::Parameter_association_numeric(root.sow_depth                       ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   // not used in CropSyst proper? parameter_associations.append(new CS::Parameter_association_numeric(root.at_pt_root_limit                ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_bool   (parameters.canopy_growth_LAI_based.clipping_removes_newest_first     ,"leaf/clip_newest_first"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_LAI_based.initial_GAI                       ,"leaf/area/index/GAI/initial"          ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_LAI_based.regrowth_GAI                      ,"leaf/area/index/GAI/regrowth"         ,    ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_LAI_based.max_LAI                           ,"leaf/area/index/LAI/maximum"          ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_LAI_based.fract_LAI_mature                  ,"canopy/growth/LAI_based/fract_LAI_mature"   ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_LAI_based.specific_leaf_area                ,"leaf/area/specific/optimum"           ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_LAI_based.leaf_duration_deg_day             ,"leaf/area/duration"                   ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_LAI_based.leaf_duration_sensitivity_stress  ,"leaf/area/duration/stress_sensitivity",POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.canopy_growth_LAI_based.stem_leaf_partition               ,"leaf/stem_leaf_partition"             ,POT_ADJUSTABLE,POT_OBSERVABLE));


   parameter_associations.append(new CS::Parameter_association_numeric(parameters.quiescence.consider_inactive_days           ,"ecophysiology/quiescence/consider_inactive_days"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.quiescence.start_DOY                        ,"ecophysiology/quiescence/inducement/valid/start"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.quiescence.end_DOY                          ,"ecophysiology/quiescence/inducement/valid/end"    ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.quiescence.inducement_temperature           ,"ecophysiology/quiescence/inducement/temperature"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   /*150913 Not sure what this was doesn't appear to be used
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.inactive_period.value                            ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   */

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.dormancy.chill_hours                             ,"ecophysiology/dormancy/chill/requirement/hours"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.dormancy.deg_day_bud_break_chill_req_sat         ,"ecophysiology/dormancy/chill/requirement/budbreak/satisfied"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.dormancy.deg_day_bud_break_chill_req_not_sat     ,"ecophysiology/dormancy/chill/requirement/budbreak/unsatisfied",POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.dormancy.senesce                                 ,"ecophysiology/dormancy/senesce"                               ,NOT_ADJUSTABLE,POT_OBSERVABLE));

// duplicate but should be here   parameter_associations.append(new CS::Parameter_association_bool   (parameters.tolerance.enabled                          ,"ecophysiology/tolerance/temperature/enabled"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.tolerance.temperature_cold_fruit_damage    ,"ecophysiology/tolerance/temperature/cold/fruit/damage"      ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.tolerance.temperature_cold_fruit_lethal    ,"ecophysiology/tolerance/temperature/cold/fruit/lethal"      ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.tolerance.temperature_cold_leaf_damage     ,"ecophysiology/tolerance/temperature/cold/leaf/damage"       ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.tolerance.temperature_cold_leaf_lethal     ,"ecophysiology/tolerance/temperature/cold/leaf/lethal"       ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.tolerance.temperature_heat_tuber_critical  ,"ecophysiology/tolerance/temperature/heat/tuber/critical"    ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.tolerance.salvageable_deg_day              ,"ecophysiology/tolerance/temperature/cold/yield/salvageable" ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.salinity.osmotic_pot_50                    ,"ecophysiology/tolerance/salinity/van_Genuchten/Pi50"  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.salinity.salt_tolerance_P                  ,"ecophysiology/tolerance/salinity/van_Genuchten/P"     ,POT_ADJUSTABLE,POT_OBSERVABLE));


   // Layout should be planting parameter
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.layout.row_spacing                               ,"layout/spacing/row"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.layout.col_spacing                               ,"layout/spacing/col"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.layout.row_azimuth_true_north_deg                ,"layout/azimuth/row"               ,POT_ADJUSTABLE,POT_OBSERVABLE));


   parameter_associations.append(new CS::Parameter_association_bool(parameters.fruit.grape                            ,"fruit/grape"));
   parameter_associations.append(new CS::Parameter_association_enum(parameters.fruit.harvest_condition_mode_cowl      ,"fruit/harvest_condition"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.fract_total_solids            ,"fruit/fract_total_solids"            ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.max_fruit_load_kg_ha          ,"fruit/load_maximum"                  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.initial_fruit_mass            ,"fruit/mass_initial"                  ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.initial_reserves_release_rate ,"fruit/reserves_release_rate/initial" ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.clusters_per_vine             ,"fruit/clusters_per_vine"             ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.berries_per_cluster           ,"fruit/berries_per_cluster"           ,POT_ADJUSTABLE,POT_OBSERVABLE));
   /*never used
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.fruits_per_tree               ,"fruit/fruits_per_tree"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   */
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.harvest_temperature           ,"fruit/harvest/temperature"           ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.harvest_temperature_days      ,"fruit/harvest/temperature_days"      ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.harvest_DOY_earliest          ,"harvest/earliest"                    ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.harvest_DOY_latest            ,"harvest/latest"                      ,POT_ADJUSTABLE,POT_OBSERVABLE));

   // The following are probably going to be obsolete with the new fruit model
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.growth_fraction_to_fruit       ,"fruit/growth_fraction_to_fruit"      ,    ADJUSTABLE,POT_OBSERVABLE));
   /* now using adjustable parameter idiom
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.initial_growth_fraction_to_fruit  ,"fruit/structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.rapid_growth_fraction_to_fruit    ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   */
   /* The following should use new adjustment mechanism
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.max_water_uptake_before_fruiting_mm           ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.max_water_uptake_during_initial_fruit_mm      ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.max_water_uptake_during_radid_fruit_mm        ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.max_water_uptake_during_veraison_mm           ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.fruit.max_water_uptake_after_maturity_mm            ,"structure"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   */

   parameter_associations.append(new CS::Parameter_association_bool(parameters.nitrogen.fixating                                      ,"nitrogen/fixation"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.legume_fraction                            ,"nitrogen/legume_fraction"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_enum(parameters.nitrogen.nitrogen_leaf_stress_mode_cowl                ,"nitrogen/leaf_stress"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.max_uptake_daily_rate_kg_ha                ,"nitrogen/uptake_rate/maximum"           ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.residual_N_not_available_for_uptake        ,"nitrogen/residual"                      ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.soil_N_conc_where_N_uptake_decreases       ,"nitrogen/soil_conc_decreases_uptake"    ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.PAW_where_N_uptake_rate_decreases          ,"nitrogen/PAW_decreases_uptake"          ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.stubble_max_conc                           ,"nitrogen/concentration/stubble/maximum" ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.root_conc                                  ,"nitrogen/concentration/root"            ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.dilution_curve_max_conc_mature             ,"nitrogen/dilution/maximum/concentration/mature"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.emergence_max_conc                         ,"nitrogen/dilution/maximum/concentration/emergence"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.emergence_crit_conc                        ,"nitrogen/dilution/critical/concentration/emergence"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.biomass_to_start_dilution_crit_N_conc_T_ha ,"nitrogen/dilution/critical/biomass_to_start"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.nitrogen.end_dilution_curve_deg_day                 ,"nitrogen/dilution/end"               ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_numeric(parameters.CO2_response.CO2_concentration_when_measured.TUE                         ,"CO2/reference_conc/TUE"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.CO2_response.CO2_concentration_when_measured.RUE                         ,"CO2/reference_conc/RUE"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.CO2_response.non_rectagular_hyperbola_solution.alpha                     ,"CO2/non_rectagular_hyperbola/alpha"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.CO2_response.non_rectagular_hyperbola_solution.theta                     ,"CO2/non_rectagular_hyperbola/theta"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.CO2_response.non_rectagular_hyperbola_solution.growth_ratio_asymptotic   ,"CO2/non_rectagular_hyperbola/growth_ratio_asymptotic"               ,POT_ADJUSTABLE,POT_OBSERVABLE));

   parameter_associations.append(new CS::Parameter_association_enum   (parameters.residue_decomposition.RUSLE2_type_labeled /*NYI as cowl*/                  ,"residue/RUSLE2_type"));
   parameter_associations.append(new CS::Parameter_association_bool   (parameters.residue_decomposition.decompose_senesced_canopy             ,"residue/decomposition/decompose_senesced_canopy"));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.decomposition_time_50               ,"residue/decomposition/halflife"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.fast_cycling_top_fraction           ,"residue/top/fast_cycling"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.slow_cycling_top_fraction           ,"residue/top/slow_cycling"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.lignified_top_fraction              ,"residue/top/lignified"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.fast_cycling_root_fraction          ,"residue/root/fast_cycling"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.slow_cycling_root_fraction          ,"residue/root/slow_cycling"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.lignified_root_fraction             ,"residue/root/lignified"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.fast_cycling_decomposition_time_50  ,"residue/decomposition/halflife/fast_cycling"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.slow_cycling_decomposition_time_50  ,"residue/decomposition/halflife/slow_cycling"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.lignified_decomposition_time_50     ,"residue/decomposition/halflife/lignified"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.detrition_time_50                   ,"residue/detrition/halflife"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.fast_cycling_C_N_ratio              ,"residue/CN_ratio/fast_cycling"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.slow_cycling_C_N_ratio              ,"residue/CN_ratio/slow_cycling"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.lignified_C_N_ratio                 ,"residue/CN_ratio/lignified"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.carbon_fraction                     ,"residue/carbon_fraction"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.stubble_area_covered_to_mass_ratio  ,"residue/area_covered_to_mass_ratio/stubble"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.surface_area_covered_to_mass_ratio  ,"residue/area_covered_to_mass_ratio/flat"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
      // need to check if this is indeed max_decomposition_rate_single_pool  halflife
   parameter_associations.append(new CS::Parameter_association_numeric(parameters.residue_decomposition.max_decomposition_rate_single_pool  ,"residue/decomposition/rate/max/single"               ,POT_ADJUSTABLE,POT_OBSERVABLE));
//#endif
   // NYI harvest_part
   return true;
}
//______________________________________________________________________________
bool CropSyst::Crop_parameters_configured::initialize_parameter_pertinencies() initialization_
{
   parameter_pertinencies.take(new CS::Document_configured::Parameter_pertinence("biomass/production/continuous_cultivation_impact"                 ,parameters.life_cycle_labeled,perennial_life_cycle));

/* The following options have yet to set pertinencies
crop->residue_decomposition.RUSLE2_type_labeled));
crop->biomass_production.TUE_equation_cowl));
//V4 crop->RUE_basis_cowl
crop->morphology.canopy_growth_cowl
crop->harvested_part_labeled
crop->life_cycle_labeled
crop->season_dormancy_mode_labeled
crop->photosynthetic_pathway_labeled
crop->emergence.emergence_model_cowl
crop->thermal_time.thermal_response_cowl
crop->photoperiod.photoperiodism_cowl
   // checkboxes
//crop->xxx)); orchard
crop->harvest.apply_adjustment_to_unstressed_harvest_index
crop->harvest.apply_heat_extreme_adjustment_to_unstressed_harvest_index
crop->tolerance.enabled
//crop->xxx)); // salinity
crop->nitrogen.fixating
crop->vernalization.enabled
*/

   //NYI parameter_pertinencies.take(new Parameter_pertinence("ontogeny/abscission/??linger_duration???"  ,parameters.abscission_labeled,semi_deciduous));


/*
_______________________________________________________________________________
V4&V5 editor logic to be reomplemented using pertinencies
if (!crop) return;
   bool CROPSYST_OR_CROPGRO_MODEL = ((crop->crop_model_labeled.get() == CROPSYST_CROP_MODEL) || (crop->crop_model_labeled.get() == CROPGRO_MODEL));
   bool CROPSYST_FRUIT = (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);
   checkbox_grape->Visible             = crop->harvested_part_labeled.get()==fruit_part;
//140122    checkbox_tea->Visible               = crop->harvested_part_labeled.get() == leaf_part;
   edit_deg_day_tuber_initiation->Visible = crop->harvested_part_labeled.get() == tuber_part;
   edit_deg_day_begin_filling_grain_or_fruit->Visible
      =  crop->harvested_part_labeled.get()==grain_part
      || crop->harvested_part_labeled.get()==fruit_part;
   groupbox_max_water_uptake->Visible = CROPSYST_FRUIT;
   edit_max_water_uptake_mm->Visible = !CROPSYST_FRUIT;
   radiogroup_life_cycle            ->Visible = CROPSYST_OR_CROPGRO_MODEL;


   edit_deg_day_begin_filling_grain_or_fruit->Visible = !crop->harvested_part_labeled.get() != leaf_part;
   // Always shown
   // growth_sheet
   // leaf_root_sheet
   // transpiration_sheet
   // harvest_sheet
   // dormancy_sheet
   // hardiness_sheet
   // CO2_sheet
   // dormancy_sheet
   // phenology_sheet
   Harvested_part harvested_part = crop->harvested_part_labeled.get();
   edit_HI_unstressed->Visible = crop->apply_harvest_index();
   bool is_seed_crop = crop->harvested_part_labeled.get() == grain_part;
   tabsheet_harvest_grain->TabVisible = true;   // It is necessary to enable all the tabsheets
   tabsheet_harvest_tuber->TabVisible = true;   // Otherwise all could be disabled
   tabsheet_harvest_fruit->TabVisible = true;   // as we switch and that will cause an error.
   tabsheet_harvest_other->TabVisible = true;
   tabsheet_harvest_grain->TabVisible = is_seed_crop;
   tabsheet_harvest_tuber->TabVisible = crop->harvested_part_labeled.get() == tuber_part; // Maybe also root crop
   tabsheet_harvest_fruit->TabVisible = (crop->harvested_part_labeled.get() == fruit_part) || (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);
   tabsheet_harvest_other->TabVisible = !tabsheet_harvest_grain->TabVisible && !tabsheet_harvest_tuber->TabVisible  && !    tabsheet_harvest_fruit->TabVisible; // 110907
   // The following yields are needed
   // ROOT_CROP,LEAF_CROP
   // TEA_CROP

   radiogroup_life_cycle->Update();
   radiogroup_harvested_biomass           ->Visible = CROPSYST_OR_CROPGRO_MODEL;
   edit_opt_temp_for_growth               ->Visible = CROPSYST_OR_CROPGRO_MODEL;

   edit_min_tolerable_temp          ->Visible = CROPSYST_OR_CROPGRO_MODEL;       //130531
   edit_max_tolerable_temp          ->Visible = CROPSYST_OR_CROPGRO_MODEL;
   edit_low_threshold_limit_temp    ->Visible = CROPSYST_OR_CROPGRO_MODEL;
   edit_high_threshold_limit_temp   ->Visible = CROPSYST_OR_CROPGRO_MODEL;

   edit_fract_LAI_mature                  ->Visible = CROPSYST_OR_CROPGRO_MODEL;
   edit_deg_day_emerge                    ->Visible = CROPSYST_OR_CROPGRO_MODEL;
   edit_deg_day_end_vegetative_growth     ->Visible = true;
   edit_max_root_depth_dd     ->Visible = crop->crop_model_labeled.get() != CROPSYST_ORCHARD_MODEL ;
   edit_deg_day_begin_rapid_fruit_growth  ->Visible = (crop->harvested_part_labeled.get() == fruit_part);
   show_hide_dormancy();
   groupbox_inactive_period->Visible = crop->season_dormancy_mode_labeled.get() >= multiple_season;
   radiogroup_landuse            ->Visible = CROPSYST_OR_CROPGRO_MODEL;
   if (crop->harvested_part_labeled.get()==fruit_part)
   {
      crop->land_use_labeled.set(FALLOW); // Claudio decided to use fallow for orchard model.
      groupbox_fruit_grape->Visible =  crop->fruit.grape;
      groupbox_fruit_other->Visible = !crop->fruit.grape;
   }
   checkbox_clipping_resets->Visible = !CROPSYST_FRUIT;
   groupbox_hardiness_fruit->Visible = CROPSYST_FRUIT;
   groupbox_hydrothermal_time->Visible = crop->emergence.emergence_model_cowl.get() == EMERGENCE_HYDROTHERMAL_TIME;
   edit_N_max_daily_uptake_rate->Visible = true; ;

   // For the following phenology edits, the input fields are shifted up
   // when stages are not applicable (visible)

    note_harvested_biomass->Visible = crop->harvested_part_labeled.get() >= HARVEST_PART_COUNT;
    if (CROPSYST_FRUIT) // maturity is always significant for fruit crops.
      panel_maturity_significant             ->Visible = false;
   edit_deg_day_begin_maturity->Visible = crop->phenology.maturity_significant || CROPSYST_FRUIT;

   bool hardness_enabled = crop->hardiness.enabled;
   groupbox_cold_temperature_sensitivity->Enabled = hardness_enabled;
   edit_damage_cold_temperature->Enabled = hardness_enabled;
   edit_lethal_cold_temperature->Enabled = hardness_enabled;
   edit_salvageable_deg_day->Enabled = hardness_enabled;                         //140509

   edit_hardiness_fruit_damage->Enabled = hardness_enabled;
   edit_hardiness_fruit_lethal->Enabled = hardness_enabled;

   edit_salvageable_deg_day->Enabled = hardness_enabled;
   edit_salvageable_deg_day->Enabled = hardness_enabled;
   bool vernalization_enabled = crop->vernalization.enabled;
   edit_vern_low_temp->Enabled   = vernalization_enabled;
   edit_vern_high_temp->Enabled  = vernalization_enabled;
   edit_vern_start->Enabled      = vernalization_enabled;
   edit_vern_end->Enabled        = vernalization_enabled;
   edit_vern_min_factor->Enabled = vernalization_enabled;

   bool photoperiod_enabled = crop->photoperiod.consideration_cowl.get() > no_photoperiod; //110606
   groupbox_photoperiod_daylength->Visible = photoperiod_enabled;
   edit_stop_daylength        ->Enabled = photoperiod_enabled;
   edit_constrained_daylength ->Enabled = photoperiod_enabled;

   switch (crop->photoperiod.consideration_cowl.get())
   {  case short_day_photoperiod :
         caption_at_which_stopped->Caption      = "day length above which";
         caption_at_which_constrained->Caption  = "day length below which";
      break;
      case long_day_photoperiod :
         caption_at_which_stopped->Caption      = "day length below which";
         caption_at_which_constrained->Caption  = "day length above which";
      break;
   }
   checkbox_senesces->Visible = (crop->life_cycle_labeled.get() != annual_life_cycle);
   // Annuals always senesce
   edit_linger->Visible = (crop->abscission_labeled.get() == semi_deciduous);

   bool has_leaf_senescence = crop->has_leaf_senescence();
   bool canopy_growth_leaf_area_index_based = (crop->morphology.canopy_growth_cowl.get() == leaf_area_index_based_V4);
   groupbox_LAI_duration->Visible =  canopy_growth_leaf_area_index_based;   // && has_leaf_senescence
   bool WUE_changes_visible = crop->biomass_production.WUE_changes;
   edit_WUE_change_deg_day->Visible = WUE_changes_visible;
   edit_water_productivity_vegetative              ->Visible = WUE_changes_visible;
   edit_TUE_at_1kPa_VPD_vegetative                 ->Visible = WUE_changes_visible;
   edit_reference_biomass_transp_coef_vegetative_0 ->Visible = WUE_changes_visible;
   edit_TUE_scaling_coef_vegetative                ->Visible = WUE_changes_visible;
   groupbox_tanner_sinclair->Visible   = crop->biomass_production.TUE_equation_cowl.get() == TUE_Tanner_Sinclair;
   groupbox_aquacrop->Visible          = crop->biomass_production.TUE_equation_cowl.get() == TUE_water_productivity;
   groupbox_TUE_curve->Visible         = crop->biomass_production.TUE_equation_cowl.get() == TUE_curve;
   groupbox_adjustments_enabled->Visible
   = crop->harvest.apply_adjustment_to_unstressed_harvest_index                  //110907
   || CROPSYST_FRUIT                                                             //110907
   || crop->harvested_part_labeled.get()==fruit_part;                            //120510

   page_control_harvest ->Visible
   = crop->harvest.apply_heat_extreme_adjustment_to_unstressed_harvest_index     //150210
   || CROPSYST_FRUIT                                                             //150210
   || crop->harvested_part_labeled.get()==fruit_part;                            //150210

   edit_grain_translocation_fraction->Visible = crop->harvested_part_labeled.get() == grain_part;
}

   bool CROPSYST_FRUIT (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);
   groupbox_chill_requirements->Visible = CROPSYST_FRUIT;

____________________
V4 editor logice to be  reimplemented using pertinencies
bool CROPSYST_OR_CROPGRO_MODEL = ((crop->crop_model_labeled.get() == CROPSYST_CROP_MODEL) || (crop->crop_model_labeled.get() == CROPGRO_MODEL));
   bool CROPSYST_FRUIT (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);
   crop->setup_optional_parameters();
   crop_class_groupbox->Visible  = (crop->crop_model_labeled.get() != CROPGRO_MODEL);
   general_crop_image->Visible   = (crop->crop_model_labeled.get() == CROPSYST_CROP_MODEL) ;
   fruit_image->Visible          = (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL) && !crop->fruit.grape ;
   cropgro_image->Visible        = (crop->crop_model_labeled.get() == CROPGRO_MODEL);
   grape_crop_image->Visible     = (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL && crop->fruit.grape );

//NYI   initial_growth_radiogroup->Visible  = CROPSYST_FRUIT;

   residue_sheet        ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   nitrogen_sheet       ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   salinity_sheet       ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   vernalization_sheet  ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   photoperiod_sheet    ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   layout_sheet         ->TabVisible = CROPSYST_FRUIT;
   tabsheet_fruit       ->TabVisible = CROPSYST_FRUIT;
   salinity_sheet       ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   emergence_tabsheet   ->TabVisible = CROPSYST_OR_CROPGRO_MODEL; // does not apply to orchard
   if (CROPSYST_FRUIT)
      crop->life_cycle_labeled.set(PERENNIAL_WOODY);
   deciduous_checkbox                     ->Visible = CROPSYST_FRUIT && ! crop->fruit.grape;
   bool is_annual = crop->life_cycle_labeled.get() == ANNUAL;
   tabsheet_seasonal_adjustment->TabVisible = !is_annual;
   bool vernalization_enabled = crop->vernalization.enabled;
   panel_vernalization_parameters->Enabled = vernalization_enabled;
   radiogroup_RUE_basis_mode ->bind_to(&(crop->biomass_production.RUE_basis_cowl)              ,0); //max_RUE_mode_labeled
   edit_RUE_global_basis->Visible =  crop->biomass_production.RUE_basis_cowl.get() ==total_radiation; //110907
   edit_RUE_PAR_basis->Visible =  crop->biomass_production.RUE_basis_cowl.get() ==photosynthetically_active_radiation;; //110907
   bool crop_was_edited_using_old_HI =!CORN::is_approximately<float32>(crop->harvest.filling_sensitivity,0.0,0.0001);
   panel_harvest_index_upgrade->Top = 0;
   panel_harvest_index_upgrade->Height = (crop_was_edited_using_old_HI)? 33 : 0;
      // crashing Visible = crop_was_edited_using_old_HI;          //111006
   edit_grain_translocation_fraction->Visible = true;

   groupbox_harvest_index_grain_temperature_stress->Visible = !crop_was_edited_using_old_HI; //130416
   bool use_new_temperature_limitation =                                         //130513
      CORN::is_approximately<float32>(crop->biomass_production.early_growth_limit_temp,0.0,0.00001);//130513
   groupbox_temperature_limit_new->Visible = use_new_temperature_limitation;     //130513
   groupbox_temperature_limit_old->Visible = !use_new_temperature_limitation;    //130513
   groupbox_flowering_stress->Visible = listbox_harvest_temperature_stress_events->ItemIndex >= 0; //150519


_______________________

*/



   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/RUE/global"                                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/RUE/PAR"                                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/RUE/temperature/threshold/low"                 ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/RUE/temperature/threshold/high"                ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/RUE/temperature/tolerable/min"                 ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/RUE/temperature/tolerable/maximum"             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/RUE/temperature/optimal"                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/TUE/at_1kPa_VPD"                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/TUE/biomass_transpiration_coef"                ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/TUE/scaling_coef"                              ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("biomass/production/TUE/water_productivity"                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/cover/initial"                                             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/cover/maximum/no_CO2_adj"                                  ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/cover/maximum/CO2_adj"                                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/cover/mature/total"                                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/expansion/LWP/reduces"                                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/expansion/LWP/stops"                                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/growth/cover_based/fract_season_to_reach_cover_max_half"   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/height/initial"                                            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/height/final"                                              ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/height/max"                                                ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/light_extinction_coef"                                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/breadth/initial"                                           ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/breadth/final"                                             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/width/initial"                                             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/width/final"                                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/branch_insertion_height"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/stress_sensitivity/water"                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/emergence/initiation"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/tuber/initiation"                                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/anthesis/initiation"                                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/filling/initiation"                                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/rapid_fruit_growth/initiation"                          ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/maturity/initiation"                                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/senescence/initiation"                                  ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/structure"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/structure"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/accrescence/culmination"                                ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/senescence/culmination"                                 ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/root_elongation/culmination"                            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/germination/hydrothermaltime/constant/slope"            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/germination/hydrothermaltime/constant/intercept"        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/germination/hydrothermaltime/seedling_leaf_area"        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/germination/hydrothermaltime/base_temperature"          ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/germination/hydrothermaltime/base_SWP/mean"             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/germination/hydrothermaltime/base_SWP/stdev"            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/emergence"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/tuber"                                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/anthesis"                                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/filling"                                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/maturity"                                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/senescence"                                  ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/structure"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/initiation/structure"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/culmination/accrescence"                                ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/culmination/senescence"                                 ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("phenology/culmination/root_depth"                                 ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/thermal_time/response"));                           ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/thermal_time/threshold/base"                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/thermal_time/threshold/cutoff"                      ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/thermal_time/threshold/optimal"                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/thermal_time/threshold/maximum"                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/vernalization/temperature_optimal/low"              ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/vernalization/temperature_optimal/high"             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/vernalization/day_requirement/start"                ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/vernalization/day_requirement/end"                  ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/vernalization/minimum_factor"                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/photoperiod/day_length/stop"                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/photoperiod/day_length/unconstrained"               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("transpiration/ET_coef"                                            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("transpiration/LWP_wilt"                                           ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("transpiration/LWP_stomatal_closure"                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("transpiration/maximum"                                            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("transpiration/intercept"                                          ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("transpiration/slope"                                              ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("yield/harvest_index/unstressed"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("yield/stress_sensitivity/water_nitrogen"                          ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("yield/stress_sensitivity/accrescence"                             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("yield/stress_sensitivity/tuber_initiation"                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("yield/stress_sensitivity/tuber_filling"                           ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("yield/translocation/maximum"                                      ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/depth/initial"                                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/depth/maximum"                                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/length/emergence"                                            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/density/surface"                                             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/density/distribution_curvature"                              ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/length/per_unit_mass"                                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/shoot_ratio"                                                 ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/shoot_ratio/emergence"                                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/shoot_ratio/culmination"                                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("root/stress_sensitivity/water"                                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("leaf/clip_newest_first"));                                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("leaf/area/index/GAI/initial"                                      ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("leaf/area/index/GAI/regrowth"                                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("leaf/area/index/LAI/maximum"                                      ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("canopy/growth/LAI_based/fract_LAI_mature"                         ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("leaf/area/specific/optimum"                                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("leaf/area/duration"                                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("leaf/area/duration/stress_sensitivity"                            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("leaf/stem_leaf_partition"                                         ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/quiescence/consider_inactive_days"                  ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/quiescence/inducement/valid/start"                  ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/quiescence/inducement/valid/end"                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/quiescence/inducement/temperature"                  ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/dormancy/chill/requirement/hours"                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/dormancy/chill/requirement/budbreak/satisfied"      ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/dormancy/chill/requirement/budbreak/unsatisfied"    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/dormancy/senesce"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/tolerance/temperature/enabled"));                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/tolerance/temperature/cold/fruit/damage"            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/tolerance/temperature/cold/fruit/lethal"            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/tolerance/temperature/cold/leaf/damage"             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/tolerance/temperature/cold/leaf/lethal"             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/tolerance/temperature/heat/tuber/critical"          ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/tolerance/temperature/cold/yield/salvageable"       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/tolerance/salinity/van_Genuchten/Pi50"              ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("ecophysiology/tolerance/salinity/van_Genuchten/P"                 ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("layout/spacing/row"                                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("layout/spacing/col"                                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("layout/azimuth/row"                                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/fract_total_solids"                                         ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/load_maximum"                                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/mass_initial"                                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/reserves_release_rate/initial"                              ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/clusters_per_vine"                                          ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/berries_per_cluster"                                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/fruits_per_tree"                                            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/harvest/temperature"                                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/harvest/temperature_days"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("harvest/earliest"                                                 ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("harvest/latest"                                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("fruit/growth_fraction_to_fruit"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/legume_fraction"                                         ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/uptake_rate/maximum"                                     ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/residual"                                                ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/soil_conc_decreases_uptake"                              ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/PAW_decreases_uptake"                                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/concentration/stubble/maximum"                           ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/concentration/root"                                      ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/dilution/maximum/concentration/mature"                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/dilution/maximum/concentration/emergence"                ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/dilution/critical/concentration/emergence"               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/dilution/critical/biomass_to_start"                      ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("nitrogen/dilution/end"                                            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("CO2/reference_conc/TUE"                                           ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("CO2/reference_conc/RUE"                                           ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("CO2/non_rectagular_hyperbola/alpha"                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("CO2/non_rectagular_hyperbola/theta"                               ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("CO2/non_rectagular_hyperbola/growth_ratio_asymptotic"             ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/decomposition/halflife"                                   ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/top/fast_cycling"                                         ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/top/slow_cycling"                                         ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/top/lignified"                                            ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/root/fast_cycling"                                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/root/slow_cycling"                                        ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/root/lignified"                                           ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/decomposition/halflife/fast_cycling"                      ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/decomposition/halflife/slow_cycling"                      ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/decomposition/halflife/lignified"                         ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/detrition/halflife"                                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/CN_ratio/fast_cycling"                                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/CN_ratio/slow_cycling"                                    ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/CN_ratio/lignified"                                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/carbon_fraction"                                          ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/area_covered_to_mass_ratio/stubble"                       ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/area_covered_to_mass_ratio/flat"                          ,enumeration,value));
   //NYA parameter_pertinencies.take(new Parameter_pertinence("residue/decomposition/rate/max/single"                            ,enumeration,value));


   return true;
}
//______________________________________________________________________________
bool CropSyst::Crop_parameters_configured::initialize_parameter_essentials() initialization_
{
   // conducive (indicates the variable is not essential, default will generally suffice).
   // essential (critical parameter that varies by cultivar).
   // FUNDAMENTAL indicates that it hasn't been determined yet if the parameter is essential

   //not essential parameter_essentials.take(new CS::Document_configured::Parameter_essential("biomass/production/continuous_cultivation_impact"));

   //NYA parameter_essentials.take(new Parameter_essential ("biomass/production/RUE/global"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/RUE/PAR"                                       ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/RUE/temperature/threshold/low"                 ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/RUE/temperature/threshold/high"                ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/RUE/temperature/tolerable/min"                 ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/RUE/temperature/tolerable/maximum"             ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/RUE/temperature/optimal"                       ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/TUE/at_1kPa_VPD"                               ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/TUE/biomass_transpiration_coef"                ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/TUE/scaling_coef"                              ));
   //NYA parameter_essentials.take(new parameter_essential("biomass/production/TUE/water_productivity"                        ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/cover/initial"                                             ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/cover/maximum/no_CO2_adj"                                  ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/cover/maximum/CO2_adj"                                     ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/cover/mature/total"                                        ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/expansion/LWP/reduces"                                     ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/expansion/LWP/stops"                                       ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/growth/cover_based/fract_season_to_reach_cover_max_half"   ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/height/initial"                                            ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/height/final"                                              ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/height/max"                                                ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/light_extinction_coef"                                     ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/breadth/initial"                                           ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/breadth/final"                                             ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/width/initial"                                             ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/width/final"                                               ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/branch_insertion_height"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/stress_sensitivity/water"                               ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/emergence/initiation"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/tuber/initiation"                                       ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/anthesis/initiation"                                    ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/filling/initiation"                                     ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/rapid_fruit_growth/initiation"                          ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/maturity/initiation"                                    ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/senescence/initiation"                                  ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/structure"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/structure"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/accrescence/culmination"                                ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/senescence/culmination"                                 ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/root_elongation/culmination"                            ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/germination/hydrothermaltime/constant/slope"            ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/germination/hydrothermaltime/constant/intercept"        ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/germination/hydrothermaltime/seedling_leaf_area"        ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/germination/hydrothermaltime/base_temperature"          ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/germination/hydrothermaltime/base_SWP/mean"             ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/germination/hydrothermaltime/base_SWP/stdev"            ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/emergence"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/tuber"                                       ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/anthesis"                                    ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/filling"                                     ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/maturity"                                    ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/senescence"                                  ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/structure"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/initiation/structure"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/culmination/accrescence"                                ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/culmination/senescence"                                 ));
   //NYA parameter_essentials.take(new parameter_essential("phenology/culmination/root_depth"                                 ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/thermal_time/response"));                           ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/thermal_time/threshold/base"                        ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/thermal_time/threshold/cutoff"                      ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/thermal_time/threshold/optimal"                     ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/thermal_time/threshold/maximum"                     ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/vernalization/temperature_optimal/low"              ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/vernalization/temperature_optimal/high"             ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/vernalization/day_requirement/start"                ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/vernalization/day_requirement/end"                  ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/vernalization/minimum_factor"                       ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/photoperiod/day_length/stop"                        ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/photoperiod/day_length/unconstrained"               ));
   //NYA parameter_essentials.take(new parameter_essential("transpiration/ET_coef"                                            ));
   //NYA parameter_essentials.take(new parameter_essential("transpiration/LWP_wilt"                                           ));
   //NYA parameter_essentials.take(new parameter_essential("transpiration/LWP_stomatal_closure"                               ));
   //NYA parameter_essentials.take(new parameter_essential("transpiration/maximum"                                            ));
   //NYA parameter_essentials.take(new parameter_essential("transpiration/intercept"                                          ));
   //NYA parameter_essentials.take(new parameter_essential("transpiration/slope"                                              ));
   //NYA parameter_essentials.take(new parameter_essential("yield/harvest_index/unstressed"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("yield/stress_sensitivity/water_nitrogen"                          ));
   //NYA parameter_essentials.take(new parameter_essential("yield/stress_sensitivity/accrescence"                             ));
   //NYA parameter_essentials.take(new parameter_essential("yield/stress_sensitivity/tuber_initiation"                        ));
   //NYA parameter_essentials.take(new parameter_essential("yield/stress_sensitivity/tuber_filling"                           ));
   //NYA parameter_essentials.take(new parameter_essential("yield/translocation/maximum"                                      ));
   //NYA parameter_essentials.take(new parameter_essential("root/depth/initial"                                               ));
   //NYA parameter_essentials.take(new parameter_essential("root/depth/maximum"                                               ));
   //NYA parameter_essentials.take(new parameter_essential("root/length/emergence"                                            ));
   //NYA parameter_essentials.take(new parameter_essential("root/density/surface"                                             ));
   //NYA parameter_essentials.take(new parameter_essential("root/density/distribution_curvature"                              ));
   //NYA parameter_essentials.take(new parameter_essential("root/length/per_unit_mass"                                        ));
   //NYA parameter_essentials.take(new parameter_essential("root/shoot_ratio"                                                 ));
   //NYA parameter_essentials.take(new parameter_essential("root/shoot_ratio/emergence"                                       ));
   //NYA parameter_essentials.take(new parameter_essential("root/shoot_ratio/culmination"                                     ));
   //NYA parameter_essentials.take(new parameter_essential("root/stress_sensitivity/water"                                    ));
   //NYA parameter_essentials.take(new parameter_essential("leaf/clip_newest_first"));                                        ));
   //NYA parameter_essentials.take(new parameter_essential("leaf/area/index/GAI/initial"                                      ));
   //NYA parameter_essentials.take(new parameter_essential("leaf/area/index/GAI/regrowth"                                     ));
   //NYA parameter_essentials.take(new parameter_essential("leaf/area/index/LAI/maximum"                                      ));
   //NYA parameter_essentials.take(new parameter_essential("canopy/growth/LAI_based/fract_LAI_mature"                         ));
   //NYA parameter_essentials.take(new parameter_essential("leaf/area/specific/optimum"                                       ));
   //NYA parameter_essentials.take(new parameter_essential("leaf/area/duration"                                               ));
   //NYA parameter_essentials.take(new parameter_essential("leaf/area/duration/stress_sensitivity"                            ));
   //NYA parameter_essentials.take(new parameter_essential("leaf/stem_leaf_partition"                                         ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/quiescence/consider_inactive_days"                  ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/quiescence/inducement/valid/start"                  ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/quiescence/inducement/valid/end"                    ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/quiescence/inducement/temperature"                  ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/dormancy/chill/requirement/hours"                   ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/dormancy/chill/requirement/budbreak/satisfied"      ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/dormancy/chill/requirement/budbreak/unsatisfied"    ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/dormancy/senesce"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/tolerance/temperature/enabled"));                   ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/tolerance/temperature/cold/fruit/damage"            ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/tolerance/temperature/cold/fruit/lethal"            ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/tolerance/temperature/cold/leaf/damage"             ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/tolerance/temperature/cold/leaf/lethal"             ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/tolerance/temperature/heat/tuber/critical"          ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/tolerance/temperature/cold/yield/salvageable"       ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/tolerance/salinity/van_Genuchten/Pi50"              ));
   //NYA parameter_essentials.take(new parameter_essential("ecophysiology/tolerance/salinity/van_Genuchten/P"                 ));
   //NYA parameter_essentials.take(new parameter_essential("layout/spacing/row"                                               ));
   //NYA parameter_essentials.take(new parameter_essential("layout/spacing/col"                                               ));
   //NYA parameter_essentials.take(new parameter_essential("layout/azimuth/row"                                               ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/fract_total_solids"                                         ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/load_maximum"                                               ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/mass_initial"                                               ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/reserves_release_rate/initial"                              ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/clusters_per_vine"                                          ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/berries_per_cluster"                                        ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/fruits_per_tree"                                            ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/harvest/temperature"                                        ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/harvest/temperature_days"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("harvest/earliest"                                                 ));
   //NYA parameter_essentials.take(new parameter_essential("harvest/latest"                                                   ));
   //NYA parameter_essentials.take(new parameter_essential("fruit/growth_fraction_to_fruit"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/legume_fraction"                                         ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/uptake_rate/maximum"                                     ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/residual"                                                ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/soil_conc_decreases_uptake"                              ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/PAW_decreases_uptake"                                    ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/concentration/stubble/maximum"                           ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/concentration/root"                                      ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/dilution/maximum/concentration/mature"                   ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/dilution/maximum/concentration/emergence"                ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/dilution/critical/concentration/emergence"               ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/dilution/critical/biomass_to_start"                      ));
   //NYA parameter_essentials.take(new parameter_essential("nitrogen/dilution/end"                                            ));
   //NYA parameter_essentials.take(new parameter_essential("CO2/reference_conc/TUE"                                           ));
   //NYA parameter_essentials.take(new parameter_essential("CO2/reference_conc/RUE"                                           ));
   //NYA parameter_essentials.take(new parameter_essential("CO2/non_rectagular_hyperbola/alpha"                               ));
   //NYA parameter_essentials.take(new parameter_essential("CO2/non_rectagular_hyperbola/theta"                               ));
   //NYA parameter_essentials.take(new parameter_essential("CO2/non_rectagular_hyperbola/growth_ratio_asymptotic"             ));
   //NYA parameter_essentials.take(new parameter_essential("residue/decomposition/halflife"                                   ));
   //NYA parameter_essentials.take(new parameter_essential("residue/top/fast_cycling"                                         ));
   //NYA parameter_essentials.take(new parameter_essential("residue/top/slow_cycling"                                         ));
   //NYA parameter_essentials.take(new parameter_essential("residue/top/lignified"                                            ));
   //NYA parameter_essentials.take(new parameter_essential("residue/root/fast_cycling"                                        ));
   //NYA parameter_essentials.take(new parameter_essential("residue/root/slow_cycling"                                        ));
   //NYA parameter_essentials.take(new parameter_essential("residue/root/lignified"                                           ));
   //NYA parameter_essentials.take(new parameter_essential("residue/decomposition/halflife/fast_cycling"                      ));
   //NYA parameter_essentials.take(new parameter_essential("residue/decomposition/halflife/slow_cycling"                      ));
   //NYA parameter_essentials.take(new parameter_essential("residue/decomposition/halflife/lignified"                         ));
   //NYA parameter_essentials.take(new parameter_essential("residue/detrition/halflife"                                       ));
   //NYA parameter_essentials.take(new parameter_essential("residue/CN_ratio/fast_cycling"                                    ));
   //NYA parameter_essentials.take(new parameter_essential("residue/CN_ratio/slow_cycling"                                    ));
   //NYA parameter_essentials.take(new parameter_essential("residue/CN_ratio/lignified"                                       ));
   //NYA parameter_essentials.take(new parameter_essential("residue/carbon_fraction"                                          ));
   //NYA parameter_essentials.take(new parameter_essential("residue/area_covered_to_mass_ratio/stubble"                       ));
   //NYA parameter_essentials.take(new parameter_essential("residue/area_covered_to_mass_ratio/flat"                          ));
   //NYA parameter_essentials.take(new parameter_essential("residue/decomposition/rate/max/single"                            ));


   return true;
}
//______________________________________________________________________________

} // namespace CropSyst
//140811 1030 lines
