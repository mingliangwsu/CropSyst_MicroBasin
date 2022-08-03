//Method implementations common to both the CropSyst V4 and V5 soil editor form
#if (__BCPLUSPLUS__>0x600)
#define _UNICODE
#endif
#include <corn/data_source/vv_file.h>
#include "CropSyst/source/cs_filenames.h"
#include "CropSyst/source/crop/crop_types.h"
#include "CS_suite/application/CS_suite_directory.h"

//#if (CS_VERSION==4)
#if (CROPSYST_VERSION==4)
#  include "CropSyst/GUI/help/crop.h"
#  include "CropSyst/source/crop/crop_param_V4.h"
#  include "crop_editor_frm.h"
#  define Tcrop_editor_form TCrop_editor_form
#  define residue_decomposition_ residue_decomposition.
#  define p_kc                   v_kc
#  define p_ET_coef              v_ET_coef
#  define p_stomatal_closure_LWP v_stomatal_closure_LWP
#  define p_wilt_LWP  v_wilt_leaf_water_pot
#  define p_max_water_uptake     v_max_water_uptake

#  define p_max_LAI              v_max_LAI
#  define p_initial_GAI          v_initial_GAI
#  define p_regrowth_GAI         v_regrowth_GAI
#  define p_specific_leaf_area   v_specific_leaf_area
#  define p_stem_leaf_partition  v_stem_leaf_partition
#  define p_fract_LAI_mature     v_fract_LAI_mature
#  define p_senesce_LAI_unit_per_deg_day  v_senesce_LAI_unit_per_deg_day
#  define p_cover_initial             v_canopy_cover_initial
#  define p_cover_maximum             v_canopy_cover_maximum
#  define p_full_senescence_green_cover        v_canopy_cover_full_senescence_green
#  define p_cover_total_season_end         v_canopy_cover_total_season_end
//171221 #  define p_mature_total_cover        v_canopy_cover_mature_total
#  define p_fract_season_to_reach_half_max_cover v_relative_thermal_time_at_half_canopy_cover_maximum

#  define p_leaf_duration_sensitivity_stress v_leaf_duration_sensitivity_stress
#  define p_leaf_duration_deg_day            v_leaf_duration_deg_day

#  define p_max_depth                        v_max_depth
#  define p_length_per_unit_mass             v_length_per_unit_mass
#  define p_surface_density                  v_surface_density
#  define p_density_distribution_curvature   v_density_distribution_curvature
#  define p_max_root_depth_deg_day           v_max_root_depth_deg_day

#  define p_root_shoot_emergence_ratio       v_root_shoot_emergence_ratio
#  define p_root_shoot_full_ratio            v_root_shoot_full_ratio
#  define p_sensitivity_to_water_stress      v_sensitivity_to_water_stress

#  define p_seedling_leaf_area               v_seedling_leaf_area
#  define p_germination_base_temperature     v_germination_base_temperature
#  define p_mean_base_soil_water_pot         v_mean_base_soil_water_pot
#  define p_stdev_base_soil_water_pot        v_stdev_base_soil_water_pot
#  define p_a v_a
#  define p_b v_b

#  define p_season_biomass_adjustment_2 v_season_biomass_adjustment_2
#  define p_season_biomass_adjustment_3 v_season_biomass_adjustment_3
#  define p_season_biomass_adjustment_4 v_season_biomass_adjustment_4
#  define p_season_biomass_adjustment_5 v_season_biomass_adjustment_5

//110907 #  define p_RUE_max v_RUE_max
#  define p_RUE_global v_RUE_global
//110907#  define p_light_to_biomass_deprecated v_light_to_biomass_deprecated

#  define p_TUE_scaling_coef                 v_TUE_scaling_coef
#  define p_TUE_at_1kPa_VPD                  v_TUE_at_1kPa_VPD
#  define p_water_productivity               v_water_productivity
#  define p_biomass_transpiration_coef       v_biomass_transpiration_coef

#  define p_WUE_change_deg_day               v_WUE_change_deg_day

#  define p_reduce_canopy_expansion_LWP      v_reduce_canopy_expansion_LWP
#  define p_stop_canopy_expansion_LWP        v_stop_canopy_expansion_LWP
#  define p_early_growth_limit_temp          v_early_growth_limit_temp

#  define p_min_tolerable_temp               v_min_tolerable_temp
#  define p_max_tolerable_temp               v_max_tolerable_temp
#  define p_low_threshold_limit_temp         v_low_threshold_limit_temp
#  define p_high_threshold_limit_temp        v_high_threshold_limit_temp



#  define p_emergence_deg_day                v_emergence_deg_day
#  define p_tuber_initiation_deg_day         v_tuber_initiation_deg_day
#  define p_end_canopy_growth_deg_day        v_end_canopy_growth_deg_day
#  define p_begin_flowering_deg_day          v_begin_flowering_deg_day
#  define p_begin_filling_deg_day            v_begin_filling_deg_day
#  define p_begin_rapid_fruit_growth_deg_day v_begin_rapid_fruit_growth_deg_day
#  define p_begin_maturity_deg_day           v_begin_maturity_deg_day
#  define p_begin_senescence_deg_day         v_begin_senescence_deg_day
#  define p_full_senescence_deg_day          v_full_senescence_deg_day

#  define p_phenologic_sensitivity_water_stress v_phenologic_sensitivity_water_stress

#  define p_base_temperature     v_base_temperature
#  define p_cutoff_temperature   v_cutoff_temperature
#  define p_opt_temperature      v_opt_temperature
#  define p_max_temperature      v_max_temperature

// photoperiod
#  define p_stop v_stop
#  define p_unconstrain v_unconstrain
// fruit
#  define p_fract_total_solids                     v_fract_total_solids
#  define p_max_fruit_load_kg_ha                   v_max_fruit_load_kg_ha
#  define p_initial_growth_fraction_to_fruit       v_initial_growth_fraction_to_fruit
#  define p_rapid_growth_fraction_to_fruit         v_rapid_growth_fraction_to_fruit

#  define p_initial_fruit_mass                     v_initial_fruit_mass
#  define p_initial_reserves_release_rate          v_initial_reserves_release_rate
#  define p_clusters_per_vine                      v_clusters_per_vine
#  define p_berries_per_cluster                    v_berries_per_cluster
#  define p_fruits_per_tree                        v_fruits_per_tree

#  define p_harvest_temperature                    v_harvest_temperature
#  define p_harvest_temperature_days               v_harvest_temperature_days
#  define p_harvest_DOY_earliest                   v_harvest_DOY_earliest
#  define p_harvest_DOY_latest                     v_harvest_DOY_latest

#  define p_max_water_uptake_before_fruiting       v_max_water_uptake_before_fruiting
#  define p_max_water_uptake_during_initial_fruit  v_max_water_uptake_during_initial_fruit
#  define p_max_water_uptake_during_radid_fruit    v_max_water_uptake_during_radid_fruit
#  define p_max_water_uptake_during_veraison       v_max_water_uptake_during_veraison
#  define p_max_water_uptake_after_maturity        v_max_water_uptake_after_maturity
//nitrogen
#  define p_residual_N_not_available_for_uptake    v_residual_N_not_available_for_uptake
#  define p_soil_N_conc_where_N_uptake_decreases   v_soil_N_conc_where_N_uptake_decreases
#  define p_PAW_where_N_uptake_rate_decreases      v_PAW_where_N_uptake_rate_decreases
#  define p_stubble_max_conc                       v_stubble_max_conc
#  define p_root_conc                              v_root_conc
#  define p_max_uptake_daily_rate                  v_max_uptake_daily_rate
#  define p_N_mature_max_conc                      v_N_mature_max_conc
#  define p_dilution_curve_slope                   v_dilution_curve_slope
#  define p_end_dilution_curve                     v_end_dilution_curve


#  define p_emergence_max_conc                     v_emergence_max_conc
#  define p_emergence_crit_conc                    v_emergence_crit_conc
#  define p_biomass_to_start_dilution_crit_N_conc  v_biomass_to_start_dilution_crit_N_conc

//salinity
#  define p_osmotic_pot_50    v_osmotic_pot_50
#  define p_salt_tolerance_P  v_salt_tolerance_P
//CO2
#  define p_TUE_reference_conc      v_TUE_reference_conc
#  define p_RUE_reference_conc      v_RUE_reference_conc
#  define p_alpha                   v_alpha
#  define p_theta                   v_theta
#  define p_growth_ratio_asymptotic v_growth_ratio_asymptotic
//vernalization
#  define p_low_temp    v_low_temp
#  define p_high_temp   v_high_temp
#  define p_start       v_start
#  define p_end         v_end
#  define p_min_factor  v_min_factor
//dormancy
#  define p_chill_hours                         v_chill_hours
#  define p_deg_day_bud_break_chill_req_sat     v_deg_day_bud_break_chill_req_sat
#  define p_deg_day_bud_break_chill_req_not_sat v_deg_day_bud_break_chill_req_not_sat
#  define p_senesce_percent                     v_senesce_percent
#  define p_leaf_damage_cold_temp               v_leaf_damage_cold_temp
#  define p_leaf_lethal_cold_temp               v_leaf_lethal_cold_temp
//#  define p_  fruit_damage_cold_temp
//#  define p_   eruit_lethal_cold_temp
#  define p_salvageable_days_before_maturity    v_salvageable_days_before_maturity
#  define p_salvageable_deg_day                 v_salvageable_deg_day

//hardiness
#  define p_leaf_damage_cold_temp               v_leaf_damage_cold_temp
#  define p_leaf_lethal_cold_temp               v_leaf_lethal_cold_temp
//#  define p_   fruit_damage_cold_temp
//#  define p_   fruit_lethal_cold_temp
#  define p_salvageable_days_before_maturity    v_salvageable_days_before_maturity
//harveset
#  define p_index_unstressed  v_unstressed
#  define p_growth_sensitivity v_growth_sensitivity
#  define p_flowering_sensitivity v_flowering_sensitivity
#  define p_tuber_init_sensitivity v_tuber_init_sensitivity
#  define p_tuber_growth_sensitivity v_tuber_growth_sensitivity
#  define p_temperature_stress_sensitivity_check_obsolete v_temperature_stress_sensitivity_check_obsolete
#  define p_translocation_fraction v_translocation_fraction
//orchard
#  define p_branch_insertion_height v_branch_insertion_height
#  define p_row_azimuth v_row_azimuth
#  define p_row_spacing v_row_spacing
#  define p_col_spacing v_col_spacing
//Hedge row
// Note that V4 use simple float edit
#  define p_initial_width  initial_width
#  define p_final_width    final_width
#  define p_final_breadth  final_breadth
#  define p_initial_height initial_height
#  define p_final_height   final_height
//residue
#  define p_carbon_fraction v_carbon_fraction
#  define p_stubble_area_covered_to_mass_ratio v_stubble_area_covered_to_mass_ratio
#  define p_surface_area_covered_to_mass_ratio v_surface_area_covered_to_mass_ratio

#  define p_linger_days v_linger_days

#else
//#  include "form_crop_editor.h"
#  include "../../crop_editor_frm.h"

#  include "CropSyst/source/crop/crop_param_V5.h"
#  define residue_decomposition_ residue_decomposition.
   using namespace CropSyst;
#endif
#include "corn/math/compare.hpp"

#include "corn/application/program_directory_OS_FS.h"
#include "corn/OS/file_system_engine.h"
#include "corn/application/documentor.h"

//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to_V4_and_V5(CropSyst_Crop_parameters *_crop,Tparameter_file_form *_parameter_form,const char *_crop_model)
{
   CORN::documentor.know_documentation_directory(&program_directory->Documentation()); //131118
   crop_model = _crop_model;
   crop = _crop;
   crop->parameter_editor_mode = true;
   parameter_file_form = _parameter_form;
      if (crop_model)
      {
         // we don't instanciate crop_filename so that Ok handler will
         // make sure to prompt for a filename.
         crop->crop_model_labeled.set_label(crop_model);
         radiogroup_crop_model->Visible = false;
      }
      else
      {  // it must be a file name
      }
   if (crop_model)
      radiogroup_crop_model->Visible = false;
   button_calibrate->Visible = true;

   // Classification
   radiogroup_crop_model                  ->bind_to(&(crop->crop_model_labeled) V4_HELP_URL(HELP_P_crop_general));
   radiogroup_landuse                     ->bind_to(&(crop->land_use_labeled) V4_HELP_URL(HELP_P_crop_landuse));
   radiogroup_photosynthetic              ->bind_to(&(crop->photosynthetic_pathway_labeled) V4_HELP_URL(HELP_P_crop_photosynthetic_pathway));
   radiogroup_life_cycle                  ->bind_to(&(crop->life_cycle_labeled) V4_HELP_URL(HELP_P_crop_life_cycle));
   radiogroup_harvested_biomass           ->bind_to(&(crop->harvested_part_labeled) V4_HELP_URL(HELP_P_crop_harvest_class));


// This checkbox has been moved to the parameter form
//   checkbox_advanced                      ->bind_to(&(crop->advanced_mode),0/*NO HELP YET*/);
   parameter_file_form->advanced_mode_checkbox();

   edit_TUE_at_1kPa_VPD_vegetative     ->bind_to(&(crop->biomass_production.TUE_at_1kPa_VPD[1])     ,2     V4_HELP_URL(HELP_P_crop_TUE_at_1kPa_VPD) );
   edit_water_productivity_vegetative  ->bind_to(&(crop->biomass_production.water_productivity[1])  ,2    V4_HELP_URL(HELP_P_crop_water_productivity) );
   edit_reference_biomass_transp_coef_vegetative_0->bind_to(&(crop->biomass_production.reference_biomass_transpiration_coef[1]),2 V4_HELP_URL(HELP_P_crop_k_Tanner_Sinclair) );
   radiogroup_WUE_submodel       ->bind_to(&(crop->biomass_production.TUE_equation_cowl/*TUE_equation_labeled*/),0);

   checkbox_WUE_changes          ->bind_to(&(crop->biomass_production.WUE_changes)/*NO_HELP_YET_*/);
   edit_WUE_change_deg_day       ->bind_to(&(crop->phenology.p_WUE_change_deg_day)/*NO_HELP_YET_*/);
   edit_TUE_scaling_coef_vegetative ->bind_to(&(crop->biomass_production.TUE_scaling_coef[1]),2 V4_HELP_URL(HELP_P_crop_TUE_scaling_coef                ));
                                                                                                                          // 080428 Warning, I need new help codes for these new parameters
   edit_TUE_at_1kPa_VPD                ->bind_to(&(crop->biomass_production.p_TUE_at_1kPa_VPD)            V4_HELP_URL(HELP_P_crop_TUE_at_1kPa_VPD                ));
   edit_water_productivity             ->bind_to(&(crop->biomass_production.p_water_productivity)         V4_HELP_URL(HELP_P_crop_water_productivity             ));
   edit_reference_biomass_transp_coef_0->bind_to(&(crop->biomass_production.p_biomass_transpiration_coef) V4_HELP_URL(HELP_P_crop_k_Tanner_Sinclair              ));

   bind_to_vernalization();
   // Photoperiod
//   has_photoperiod = crop->photoperiod;

   bind_to_photoperiod();

   // Harvest Index
   // The same translocation factor is used for grain and fruit
   bind_to_harvest_index();

   // Fruit
   bool has_fruit = true;
   if (has_fruit) bind_to_fruit();

   bool has_residue_decomposition = true;
   radiogroup_RULSE2_residue_type            ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ RUSLE2_type_labeled)                   : 0,0);
   edit_fast_cycling_top_fraction            ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ fast_cycling_top_fraction)           : 0,2 V4_HELP_URL(HELP_P_crop_residue_cycling_biomass_fraction) /*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_cycling_biomass_fraction).c_str()*/);
   edit_slow_cycling_top_fraction            ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ slow_cycling_top_fraction)           : 0,2 V4_HELP_URL(HELP_P_crop_residue_cycling_biomass_fraction) /*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_cycling_biomass_fraction).c_str()*/);
   edit_lignified_top_fraction               ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ lignified_top_fraction)              : 0,2 V4_HELP_URL(HELP_P_crop_residue_cycling_biomass_fraction) /*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_cycling_biomass_fraction).c_str()*/);
   edit_fast_cycling_root_fraction           ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ fast_cycling_root_fraction)          : 0,2 V4_HELP_URL(HELP_P_crop_residue_cycling_biomass_fraction) /*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_cycling_biomass_fraction).c_str()*/);
   edit_slow_cycling_root_fraction           ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ slow_cycling_root_fraction)          : 0,2 V4_HELP_URL(HELP_P_crop_residue_cycling_biomass_fraction) /*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_cycling_biomass_fraction).c_str()*/);
   edit_lignified_root_fraction              ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ lignified_root_fraction)             : 0,2 V4_HELP_URL(HELP_P_crop_residue_cycling_biomass_fraction) /*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_cycling_biomass_fraction).c_str()*/);

   top_biomass_checksum ->bind_to(&top_checksum,2 /*,0 NO_HELP_YET_*/);
   root_biomass_checksum->bind_to(&root_checksum,2 /*,0 NO_HELP_YET_*/);

   edit_fast_cycling_decomposition_time_50   ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ fast_cycling_decomposition_time_50)  : 0,2 V4_HELP_URL(HELP_P_crop_residue_decomp_time)/*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_decomp_time).c_str()*/);
   edit_slow_cycling_decomposition_time_50   ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ slow_cycling_decomposition_time_50)  : 0,2 V4_HELP_URL(HELP_P_crop_residue_decomp_time)/*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_decomp_time).c_str()*/);
   edit_lignified_decomposition_time_50      ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ lignified_decomposition_time_50)     : 0,2 V4_HELP_URL(HELP_P_crop_residue_decomp_time)/*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_decomp_time).c_str()*/);
   //deprecated in V4 edit_decomposition_time_50                ->bind_to(has_residue_decomposition ? &(crop->residue_decomposition_ decomposition_time_50)               : 0 V4_HELP_URL(HELP_P_crop_residue_decomp_time)/*,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_residue_decomp_time).c_str()*/);


   // Transpiration
   edit_kc->bind_to(&(crop->morphology.p_kc) V4_HELP_URL(HELP_P_crop_transpiration_extinct_coef));
   edit_ET_crop_coef                      ->bind_to(&(crop->transpiration.p_ET_coef)              V4_HELP_URL(HELP_P_crop_transpiration_ET_crop_coef));
   edit_leaf_water_pot_stomatal_closure   ->bind_to(&(crop->transpiration.p_stomatal_closure_LWP) V4_HELP_URL(HELP_P_crop_transpiration_crit_leaf_water_pot));
   edit_wilt_leaf_water_pot               ->bind_to(&(crop->transpiration.p_wilt_LWP)             V4_HELP_URL(HELP_P_crop_transpiration_wilt_leaf_water_pot));
   edit_max_water_uptake_mm               ->bind_to(&(crop->transpiration.p_max_water_uptake)     V4_HELP_URL(HELP_P_crop_transpiration_max_water_uptake));

   // Leaf
   edit_max_LAI                           ->bind_to(&(crop->canopy_growth_LAI_based.p_max_LAI)              V4_HELP_URL(HELP_P_crop_leaf_max_LAI));
   edit_initial_GAI                       ->bind_to(&(crop->canopy_growth_LAI_based.p_initial_GAI)          V4_HELP_URL(HELP_P_crop_leaf_initial_GAI));
   edit_regrowth_GAI                      ->bind_to(&(crop->canopy_growth_LAI_based.p_regrowth_GAI)         V4_HELP_URL(HELP_P_crop_leaf_regrowth_GAI));
   edit_specific_leaf_area                ->bind_to(&(crop->canopy_growth_LAI_based.p_specific_leaf_area)   V4_HELP_URL(HELP_P_crop_leaf_spec_leaf_area));
   edit_stem_leaf_partition               ->bind_to(&(crop->canopy_growth_LAI_based.p_stem_leaf_partition)  V4_HELP_URL(HELP_P_crop_leaf_stem_part));
   edit_fract_LAI_mature                  ->bind_to(&(crop->canopy_growth_LAI_based.p_fract_LAI_mature)     V4_HELP_URL(HELP_P_crop_leaf_fract_max_LAI_mature));
   // canopy cover
   edit_canopy_cover_initial              ->bind_to(&(crop->canopy_growth_cover_based.p_cover_initial)            V4_HELP_URL(HELP_P_canopy_cover_initial));
   edit_canopy_cover_maximum              ->bind_to(&(crop->canopy_growth_cover_based.p_cover_maximum)            V4_HELP_URL(HELP_P_canopy_cover_maximum));
   //171219 edit_canopy_cover_total_mature         ->bind_to(&(crop->canopy_growth_cover_based.p_cover_total_mature)       V4_HELP_URL(HELP_P_canopy_canopy_cover_mature));
   edit_canopy_cover_total_season_end     ->bind_to(&(crop->canopy_growth_cover_based.p_cover_total_season_end)       V4_HELP_URL(HELP_P_canopy_canopy_cover_mature)); //171219 // need to rename help

   edit_canopy_cover_green_season_end     ->bind_to(&(crop->canopy_growth_cover_based.p_cover_green_season_end)       V4_HELP_URL(0)); //171219_171009
   edit_thermal_time_season_end           ->bind_to(&(crop->canopy_growth_cover_based.p_thermal_time_season_end)       V4_HELP_URL(0)); //171219_171009

   edit_shape_accrescent                  ->bind_to(&(crop->canopy_growth_cover_based.p_shape_coef_accrescent)       V4_HELP_URL(0)); //171221
   edit_shape_senescent                   ->bind_to(&(crop->canopy_growth_cover_based.p_shape_coef_senescent)       V4_HELP_URL(0)); //171221

   // senescence
   edit_leaf_duration_sensitivity_stress  ->bind_to(&(crop->canopy_growth_LAI_based.p_leaf_duration_sensitivity_stress) V4_HELP_URL(HELP_P_crop_senescence_leaf_duration_sens));
   edit_deg_day_leaf_duration             ->bind_to(&(crop->canopy_growth_LAI_based.p_leaf_duration_deg_day)            V4_HELP_URL(HELP_P_crop_senescence_leaf_duration));

   radiogroup_abscission                  ->bind_to(&(crop->abscission_labeled)      V4_HELP_URL(HELP_P_crop_senescence_senesced_biomass_fate));

   // Root
   edit_max_root_depth                    ->bind_to(&(crop->root.p_max_depth)                                  V4_HELP_URL(HELP_P_crop_root_max_root_depth));
   #if (CROPSYST_VERSION == 4)
   edit_root_length_per_unit_mass         ->bind_to(&(crop->root.p_length_per_unit_mass)                       V4_HELP_URL(HELP_P_crop_root_length_per_unit_mass));
   #endif
   edit_surface_root_density              ->bind_to(&(crop->root.p_surface_density)                            V4_HELP_URL(HELP_P_crop_root_max_surface_density));
   edit_root_density_distribution_curvature->bind_to(&(crop->root.p_density_distribution_curvature)            V4_HELP_URL(HELP_P_crop_root_density_distribution_curvature));
   edit_max_root_depth_dd                 ->bind_to(&(crop->phenology.p_max_root_depth_deg_day)                V4_HELP_URL(HELP_P_crop_root_max_root_depth_dd));
   edit_root_shoot_emergence_ratio        ->bind_to(&(crop->root.p_root_shoot_emergence_ratio)     /*NO_HELP_YET_*/); //130626
   edit_root_shoot_full_ratio             ->bind_to(&(crop->root.p_root_shoot_full_ratio)          /*NO_HELP_YET_*/); //130626
   edit_root_sensitivity_to_water_stress  ->bind_to(&(crop->root.p_sensitivity_to_water_stress)   /*NO_HELP_YET_*/);

   // Emergence
   radiogroup_emergence_model             ->bind_to(&(crop->emergence.emergence_model_cowl)        /*NO_HELP_YET_*/);  // NO_HELP_YET   emergence_model_labeled
   edit_seedling_leaf_area                ->bind_to(&(crop->emergence.p_seedling_leaf_area)        /*NO_HELP_YET_*/);  // NO_HELP_YET
   edit_germination_base_temperature      ->bind_to(&(crop->emergence.p_germination_base_temperature)/*NO_HELP_YET_*/);  // NO_HELP_YET
   edit_mean_base_soil_water_pot          ->bind_to(&(crop->emergence.p_mean_base_soil_water_pot)  /*NO_HELP_YET_*/);  // NO_HELP_YET
   edit_stdev_base_soil_water_pot         ->bind_to(&(crop->emergence.p_stdev_base_soil_water_pot) /*NO_HELP_YET_*/);  // NO_HELP_YET
   edit_a                                 ->bind_to(&(crop->emergence.p_a)                         /*NO_HELP_YET_*/);  // NO_HELP_YET
   edit_b                                 ->bind_to(&(crop->emergence.p_b)                         /*NO_HELP_YET_*/);  // NO_HELP_YET
   // Growth

   edit_seasonal_adjustment_2    ->bind_to(&(crop->biomass_production.p_season_biomass_adjustment_2)/*NO_HELP_YET_*/);  // NO_HELP_YET
   edit_seasonal_adjustment_3    ->bind_to(&(crop->biomass_production.p_season_biomass_adjustment_3)/*NO_HELP_YET_*/);  // NO_HELP_YET
   edit_seasonal_adjustment_4    ->bind_to(&(crop->biomass_production.p_season_biomass_adjustment_4)/*NO_HELP_YET_*/);  // NO_HELP_YET
   edit_seasonal_adjustment_5    ->bind_to(&(crop->biomass_production.p_season_biomass_adjustment_5)/*NO_HELP_YET_*/);  // NO_HELP_YET

//   edit_max_RUE_total                  ->bind_to(&(crop->biomass_production.p_RUE_max)    V4_HELP_URL(HELP_P_crop_RUE_max));
   edit_RUE_global_basis   ->bind_to(&(crop->biomass_production.p_RUE_global)V4_HELP_URL(HELP_P_crop_RUE_max));

   //V4 only edit_max_RUE_PAR                    ->bind_to(&(crop->p_light_to_biomass_deprecated)   V4_HELP_URL(HELP_P_crop_RUE_max));

   edit_TUE_scaling_coef         ->bind_to(&(crop->biomass_production.p_TUE_scaling_coef)V4_HELP_URL(HELP_P_crop_TUE_scaling_coef                ));



   edit_LWP_that_reduces_canopy_expansion ->bind_to(&(crop->morphology.p_reduce_canopy_expansion_LWP)          V4_HELP_URL(HELP_P_crop_LWP_reduces_canopy_expansion));
   edit_LWP_that_stops_canopy_expansion   ->bind_to(&(crop->morphology.p_stop_canopy_expansion_LWP)            V4_HELP_URL(HELP_P_crop_LWP_stops_canopy_expansion));
   #if (CROPSYST_VERSION == 4)
   edit_opt_temp_for_growth               ->bind_to(&(crop->biomass_production.p_early_growth_limit_temp)      V4_HELP_URL(HELP_P_crop_growth_opt_temp));
   #endif

   edit_min_tolerable_temp          ->bind_to(&(crop->biomass_production.p_min_tolerable_temp)        /*NO_HELP_YET_*/); //130531
   edit_max_tolerable_temp          ->bind_to(&(crop->biomass_production.p_max_tolerable_temp)        /*NO_HELP_YET_*/); //130513
   edit_low_threshold_limit_temp    ->bind_to(&(crop->biomass_production.p_low_threshold_limit_temp)  /*NO_HELP_YET_*/); //130513
   edit_high_threshold_limit_temp   ->bind_to(&(crop->biomass_production.p_high_threshold_limit_temp) /*NO_HELP_YET_*/); //130513

   // Phenology
   checkbox_clipping_resets                  ->bind_to(&(crop->phenology.clipping_resets)                       V4_HELP_URL(HELP_P_crop_pheno_clipping_resets));
   edit_deg_day_emerge                       ->bind_to(&(crop->phenology.p_emergence_deg_day)                   V4_HELP_URL(HELP_P_crop_pheno_thermal_time_req));
   edit_deg_day_tuber_initiation             ->bind_to(&(crop->phenology.p_tuber_initiation_deg_day)            V4_HELP_URL(HELP_P_crop_pheno_thermal_time_req));
   edit_deg_day_end_vegetative_growth        ->bind_to(&(crop->phenology.p_max_canopy_deg_day /*161004 p_end_canopy_growth_deg_day*/ )           V4_HELP_URL(HELP_P_crop_pheno_thermal_time_req));
   edit_deg_day_begin_flower                 ->bind_to(&(crop->phenology.p_begin_flowering_deg_day)             V4_HELP_URL(HELP_P_crop_pheno_thermal_time_req));
   edit_deg_day_begin_filling_grain_or_fruit ->bind_to(&(crop->phenology.p_begin_filling_deg_day)               V4_HELP_URL(HELP_P_crop_pheno_thermal_time_req));
   edit_deg_day_begin_rapid_fruit_growth     ->bind_to(&(crop->phenology.p_begin_rapid_fruit_growth_deg_day)    V4_HELP_URL(HELP_P_crop_pheno_thermal_time_req));
   edit_deg_day_begin_maturity               ->bind_to(&(crop->phenology.p_begin_maturity_deg_day)              V4_HELP_URL(HELP_P_crop_pheno_thermal_time_req));
   edit_begin_senescence_deg_day             ->bind_to(&(crop->phenology.p_begin_senescence_deg_day)            V4_HELP_URL(HELP_P_canopy_cover_begin_senescence_deg_day));
   edit_full_senescence_deg_day              ->bind_to(&(crop->phenology.p_full_senescence_deg_day)             V4_HELP_URL(HELP_P_canopy_cover_begin_senescence_deg_day)); //131024

   checkbox_maturity_significant             ->bind_to(&(crop->phenology.maturity_significant)                  /*NO_HELP_YET_*/);
   edit_phenologic_sensitivity_water_stress  ->bind_to(&(crop->phenology.p_phenologic_sensitivity_water_stress) V4_HELP_URL(HELP_P_crop_pheno_water_stress_sensitivity));
   // Thermal time accumulation mode
   edit_base_temp             ->bind_to(&(crop->thermal_time.p_base_temperature)  V4_HELP_URL(HELP_P_crop_thermal_time_accum_base_temp));
   edit_cutoff_temp           ->bind_to(&(crop->thermal_time.p_cutoff_temperature)V4_HELP_URL(HELP_P_crop_thermal_time_accum_cutoff_temp));
   edit_opt_temp              ->bind_to(&(crop->thermal_time.p_opt_temperature)   V4_HELP_URL(HELP_P_crop_thermal_time_accum_base_temp));
   edit_max_temp              ->bind_to(&(crop->thermal_time.p_max_temperature)   V4_HELP_URL(HELP_P_crop_thermal_time_accum_max_temp));
/*140206 temp disabled crashing
   edit_linger->bind_to(&(crop->p_linger_days) ,0);
*/

   bind_to_nitrogen();
   bind_to_salinity();
   bind_to_CO2_response();
   bind_to_dormancy();
   bind_to_hardiness();
   bind_to_orchard();
   // CropGro
   /* Not currently in V5
   if (crop->cropgro)
   cropgro_input_filebar->bind_to(&(crop->cropgro->model_input_file));
   */
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to_photoperiod()
{  radiogroup_photoperiod_consideration->bind_to(&(crop->photoperiod.photoperiodism_cowl)V4_HELP_URL(HELP_P_crop_photoperiod_consideration));
   edit_stop_daylength                 ->bind_to(&(crop->photoperiod.p_stop)             V4_HELP_URL(HELP_P_crop_photoperiod));
   edit_constrained_daylength          ->bind_to(&(crop->photoperiod.p_unconstrain)      V4_HELP_URL(HELP_P_crop_photoperiod));
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to_fruit()
{
   edit_fruit_fract_total_solids          ->bind_to(&(crop->fruit.p_fract_total_solids)               V4_HELP_URL(HELP_P_crop_fract_total_solids));
   edit_fruit_load_max                    ->bind_to(&(crop->fruit.p_max_fruit_load_kg_ha)             V4_HELP_URL(HELP_P_crop_max_fruit_load));
   #if (CS_VERSION==4)
   development_fract_biomass_edit_obsolete->bind_to(&(crop->fruit.p_initial_growth_fraction_to_fruit) V4_HELP_URL(HELP_P_crop_development_fraction_to_fruit));
   veraison_fract_biomass_edit_obsolete   ->bind_to(&(crop->fruit.p_rapid_growth_fraction_to_fruit)   V4_HELP_URL(HELP_P_crop_veraison_fraction_to_fruit));
   #endif
   checkbox_grape                         ->bind_to(&(crop->fruit.grape)                              V4_HELP_URL(HELP_P_crop_model));

   /*180601 never implemented
   edit_initial_fruit_mass                ->bind_to(&(crop->fruit.p_initial_fruit_mass)               V4_HELP_URL(HELP_P_crop_model));
   edit_initial_reserves_release_rate     ->bind_to(&(crop->fruit.p_initial_reserves_release_rate)    V4_HELP_URL(HELP_P_crop_model));
   edit_clusters_per_vine                 ->bind_to(&(crop->fruit.p_clusters_per_vine)                V4_HELP_URL(HELP_P_crop_model));
   edit_berries_per_cluster               ->bind_to(&(crop->fruit.p_berries_per_cluster)              V4_HELP_URL(HELP_P_crop_model));
   edit_fruits_per_tree                   ->bind_to(&(crop->fruit.p_fruits_per_tree)                  V4_HELP_URL(HELP_P_crop_model));
   */

   radiogroup_fruit_harvest_condition     ->bind_to(&(crop->fruit.harvest_condition_mode_cowl)        V4_HELP_URL(HELP_P_crop_model));
   edit_harvest_temperature               ->bind_to(&(crop->fruit.p_harvest_temperature)              V4_HELP_URL(HELP_P_crop_model));
   edit_harvest_temperature_days          ->bind_to(&(crop->fruit.p_harvest_temperature_days)         V4_HELP_URL(HELP_P_crop_model));
   edit_harvest_DOY_earliest              ->bind_to(&(crop->fruit.p_harvest_DOY_earliest)             V4_HELP_URL(HELP_P_crop_model));
   edit_harvest_DOY_latest                ->bind_to(&(crop->fruit.p_harvest_DOY_latest)               V4_HELP_URL(HELP_P_crop_model));
   #if (CROPSYST_VERSION==4)
   edit_max_water_upake_before_fruit         ->bind_to(&(crop->fruit.p_max_water_uptake_before_fruiting)       V4_HELP_URL(HELP_P_crop_transpiration_max_water_uptake));
   edit_max_water_uptake_during_intial_fruit ->bind_to(&(crop->fruit.p_max_water_uptake_during_initial_fruit)  V4_HELP_URL(HELP_P_crop_transpiration_max_water_uptake));
   edit_max_water_uptake_during_rapid_fruit  ->bind_to(&(crop->fruit.p_max_water_uptake_during_radid_fruit)    V4_HELP_URL(HELP_P_crop_transpiration_max_water_uptake));
   edit_max_water_uptake_during_veraison     ->bind_to(&(crop->fruit.p_max_water_uptake_during_veraison)       V4_HELP_URL(HELP_P_crop_transpiration_max_water_uptake));
   edit_max_water_uptake_after_maturity      ->bind_to(&(crop->fruit.p_max_water_uptake_after_maturity)        V4_HELP_URL(HELP_P_crop_transpiration_max_water_uptake));
   #endif
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to_nitrogen()
{  button_nitrogen_fixation                  ->bind_to(&(crop->nitrogen.fixating)                                V4_HELP_URL(HELP_P_crop_N_fixation));
   edit_residual_N_not_available_for_uptake  ->bind_to(&(crop->nitrogen.p_residual_N_not_available_for_uptake)   V4_HELP_URL(HELP_P_crop_N_uptake_adj));  // Warning needs help label
   edit_soil_N_conc_where_N_uptake_decreases ->bind_to(&(crop->nitrogen.p_soil_N_conc_where_N_uptake_decreases)  V4_HELP_URL(HELP_P_crop_N_uptake_adj));  // Warning needs help label
   edit_PAW_where_N_uptake_rate_decreases    ->bind_to(&(crop->nitrogen.p_PAW_where_N_uptake_rate_decreases)     V4_HELP_URL(HELP_P_crop_N_uptake_adj));  // Warning needs help label
   edit_N_max_stubble                        ->bind_to(&(crop->nitrogen.p_stubble_max_conc)                      V4_HELP_URL(HELP_P_crop_N_N_cont_stubble));
   edit_root_N_conc                          ->bind_to(&(crop->nitrogen.p_root_conc)                             V4_HELP_URL(HELP_P_crop_N_N_cont_stubble));  // Warning need to add root conc text
   edit_N_max_daily_uptake_rate              ->bind_to(&(crop->nitrogen.p_max_uptake_daily_rate)                 /*NO_HELP_YET_*/);
   radiogroup_nitrogen_leaf_stress_mode      ->bind_to(&(crop->nitrogen.nitrogen_leaf_stress_mode_cowl) );
// now only V4   edit_BM_start_dilution_max_conc           ->bind_to(&(crop->nitrogen.p_biomass_to_start_dilution_max_N_conc)                 ,0/*NO_HELP_YET_*/);   //130320
   edit_N_mature_max_conc                    ->bind_to(&(crop->nitrogen.p_N_mature_max_conc)                 /*NO_HELP_YET_*/);  //120505
   edit_conc_slope                           ->bind_to(&(crop->nitrogen.p_dilution_curve_slope) /*NO_HELP_YET_*/);  //120507
   edit_end_dilution_curve                   ->bind_to(&(crop->nitrogen.p_end_dilution_curve) /*NO_HELP_YET*/); //130408

   edit_BM_start_dilution_crit_conc          ->bind_to(&(crop->nitrogen.p_biomass_to_start_dilution_crit_N_conc)  /* no help yet */ ); //130319
   edit_N_emerge_crit_conc                   ->bind_to(&(crop->nitrogen.p_emergence_crit_conc)  /* no help yet */ ); //130319
   edit_N_emerge_max_conc                    ->bind_to(&(crop->nitrogen.p_emergence_max_conc)  /* no help yet */ ); //130319
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to_salinity()
{  edit_osmotic_pot_50     ->bind_to( &(crop->salinity.p_osmotic_pot_50)    V4_HELP_URL(HELP_P_crop_salinity_osmotic_pot));
   edit_salt_tolerance_P   ->bind_to( &(crop->salinity.p_salt_tolerance_P)  V4_HELP_URL(HELP_P_crop_salinity_tolerance_exp));
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to_CO2_response()
{
/*140509 obsolete
   edit_CO2_growth_ratio_elevated_to_baseline->bind_to(&(crop->CO2_response.p_growth_ratio_elevated_to_baseline_conc)  V4_HELP_URL(HELP_P_crop_CO2_ratio_of_growth));
   edit_CO2_elevated_reference_conc->bind_to( &(crop->CO2_response.p_elevated_reference_conc)  V4_HELP_URL(HELP_P_crop_CO2_elev_ref_conc));
   edit_CO2_baseline_reference_conc->bind_to( &(crop->CO2_response.p_baseline_reference_conc)  V4_HELP_URL(HELP_P_crop_CO2_base_ref_conc));
*/
   edit_TUE_reference_conc->bind_to( &(crop->CO2_response.p_TUE_reference_conc)  V4_HELP_URL(HELP_P_crop_CO2_base_ref_conc)); //131206
   edit_RUE_reference_conc->bind_to( &(crop->CO2_response.p_RUE_reference_conc)  V4_HELP_URL(HELP_P_crop_CO2_base_ref_conc)); //131206
   edit_CO2_alpha                   ->bind_to( &(crop->CO2_response.p_alpha)     /*NO_HELP_YET_*/); //131206
   edit_CO2_theta                   ->bind_to( &(crop->CO2_response.p_theta)     /*NO_HELP_YET_*/); //131206
   edit_CO2_growth_ratio_asymptotic        ->bind_to( &(crop->CO2_response.p_growth_ratio_asymptotic)/*NO_HELP_YET_*/); //131206
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to_vernalization()
{  edit_vern_low_temp      ->bind_to(&(crop->vernalization.p_low_temp)    V4_HELP_URL(HELP_P_crop_vernal_vern_Tlow));
   edit_vern_high_temp     ->bind_to(&(crop->vernalization.p_high_temp)   V4_HELP_URL(HELP_P_crop_vernal_vern_Thigh));
   edit_vern_start         ->bind_to(&(crop->vernalization.p_start)       V4_HELP_URL(HELP_P_crop_vernal_req_to_start));
   edit_vern_end           ->bind_to(&(crop->vernalization.p_end)         V4_HELP_URL(HELP_P_crop_vernal_req_to_complete));
   edit_vern_min_factor    ->bind_to(&(crop->vernalization.p_min_factor)  V4_HELP_URL(HELP_P_crop_vernal_min_factor));
   checkbox_vernalization  ->bind_to(&(crop->vernalization.enabled)       V4_HELP_URL(HELP_P_crop_vernal_enable_checkbox));
}
//_________________________________________________________bind_to_vernalization
void __fastcall TCrop_editor_form::bind_to_dormancy()
{  edit_chill_requirement                  ->bind_to(&(crop->dormancy.p_chill_hours)                          V4_HELP_URL(HELP_P_crop_dormancy));
   edit_deg_day_bud_break_chill_req_sat    ->bind_to(&(crop->dormancy.p_deg_day_bud_break_chill_req_sat)      V4_HELP_URL(HELP_P_crop_dormancy));
   edit_deg_day_bud_break_chill_req_not_sat->bind_to(&(crop->dormancy.p_deg_day_bud_break_chill_req_not_sat)  V4_HELP_URL(HELP_P_crop_dormancy));
   edit_dormancy_senesce                   ->bind_to(&(crop->dormancy.p_senesce_percent)                      V4_HELP_URL(HELP_P_crop_dormancy_senesce));
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to_hardiness()
{
   checkbox_sensitive_to_cold             ->bind_to(&(crop->tolerance.enabled)                  V4_HELP_URL(HELP_P_crop_hardiness));

   //170524 edit_salvageable_deg_day               ->bind_to(&(crop->tolerance.p_salvageable_deg_day) );
   edit_damage_cold_temperature           ->bind_to(&(crop->tolerance.p_leaf_damage_cold_temp)  V4_HELP_URL(HELP_P_crop_hardiness_damage_cold_temp));
   edit_lethal_cold_temperature           ->bind_to(&(crop->tolerance.p_leaf_lethal_cold_temp)  V4_HELP_URL(HELP_P_crop_hardiness_lethal_cold_temp));

   edit_hardiness_fruit_damage            ->bind_to(&(crop->tolerance.temperature_cold_fruit_damage),2 V4_HELP_URL(HELP_P_crop_hardiness_damage_cold_temp));
   edit_hardiness_fruit_lethal            ->bind_to(&(crop->tolerance.temperature_cold_fruit_lethal),2 V4_HELP_URL(HELP_P_crop_hardiness_lethal_cold_temp));

//   edit_hardiness_fruit_damage            ->bind_to(&(crop->tolerance.p_fruit_damage_cold_tempX)),2 V4_HELP_URL(HELP_P_crop_hardiness_damage_cold_temp));
//   edit_hardiness_fruit_lethal            ->bind_to(&(crop->tolerance.p_fruit_lethal_cold_tempX)),2 V4_HELP_URL(HELP_P_crop_hardiness_lethal_cold_temp));

/*161004
   checkbox_sensitive_to_cold             ->bind_to(&(crop->hardiness.enabled)  V4_HELP_URL(HELP_P_crop_hardiness));
   edit_damage_cold_temperature           ->bind_to(&(crop->hardiness.p_leaf_damage_cold_temp)  V4_HELP_URL(HELP_P_crop_hardiness_damage_cold_temp));
   edit_lethal_cold_temperature           ->bind_to(&(crop->hardiness.p_leaf_lethal_cold_temp)  V4_HELP_URL(HELP_P_crop_hardiness_lethal_cold_temp));
   edit_hardiness_fruit_damage            ->bind_to(&(crop->hardiness.fruit_damage_cold_temp) ,2 V4_HELP_URL(HELP_P_crop_hardiness_damage_cold_temp));
   edit_hardiness_fruit_lethal            ->bind_to(&(crop->hardiness.fruit_lethal_cold_temp) ,2 V4_HELP_URL(HELP_P_crop_hardiness_lethal_cold_temp));
   edit_salvageable_deg_day               ->bind_to(&(crop->hardiness.p_salvageable_deg_day) ,0  V4_HELP_URL(HELP_P_crop_hardiness_damage_cold_temp));
*/
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to_orchard()
{  if (!crop) return;
   edit_branch_insertion_height           ->bind_to( &(crop->canopy_characteristics_hedge_row.p_branch_insertion_height) V4_HELP_URL(HELP_P_crop_layout_canopy_characteristics));
   // Layout
   edit_row_azimuth                       ->bind_to( &(crop->layout.p_row_azimuth)  V4_HELP_URL(HELP_P_crop_layout_orientation));
   edit_row_spacing                       ->bind_to( &(crop->layout.p_row_spacing)  V4_HELP_URL(HELP_P_crop_layout_orientation));
   edit_tree_spacing                      ->bind_to( &(crop->layout.p_col_spacing)  V4_HELP_URL(HELP_P_crop_layout_orientation));
   //Hedge row
   #if CS_VERSION==4
   edit_initial_row_width                 ->bind_to(&(crop->canopy_characteristics_hedge_row.initial_width)  ,2 V4_HELP_URL(HELP_P_crop_layout_canopy_characteristics));
   edit_final_row_width                   ->bind_to(&(crop->canopy_characteristics_hedge_row.final_width)    ,2 V4_HELP_URL(HELP_P_crop_layout_canopy_characteristics));
   edit_initial_tree_breadth              ->bind_to(&(crop->canopy_characteristics_hedge_row.initial_breadth),2 V4_HELP_URL(HELP_P_crop_layout_canopy_characteristics));
   edit_final_tree_breadth                ->bind_to(&(crop->canopy_characteristics_hedge_row.final_breadth)  ,2 V4_HELP_URL(HELP_P_crop_layout_canopy_characteristics));
   edit_initial_row_height                ->bind_to(&(crop->canopy_characteristics_hedge_row.initial_height) ,2 V4_HELP_URL(HELP_P_crop_layout_canopy_characteristics));
   edit_final_row_height                  ->bind_to(&(crop->canopy_characteristics_hedge_row.final_height)   ,2 V4_HELP_URL(HELP_P_crop_layout_canopy_characteristics));
   standard_row_image->Visible   = false; // May use this for future work crop_standard_row ;
   #else
   edit_initial_row_width                 ->bind_to(&(crop->canopy_characteristics_hedge_row.initial_width)  ,2);
   edit_final_row_width                   ->bind_to(&(crop->canopy_characteristics_hedge_row.final_width)    ,2);
   edit_initial_tree_breadth              ->bind_to(&(crop->canopy_characteristics_hedge_row.initial_breadth),2);
   edit_final_tree_breadth                ->bind_to(&(crop->canopy_characteristics_hedge_row.final_breadth),2  );
   edit_initial_row_height                ->bind_to(&(crop->canopy_characteristics_hedge_row.initial_height) ,2);
   edit_final_row_height                  ->bind_to(&(crop->canopy_characteristics_hedge_row.final_height) ,2  );
   #endif
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::Update_V4_and_V5()
{
   if (!crop) return;
   TForm::Update();
   if (parameter_file_form)
      parameter_file_form->Update();

   radiogroup_crop_model                     ->Update();
   radiogroup_landuse                        ->Update();
   radiogroup_photosynthetic                 ->Update();
   radiogroup_life_cycle                     ->Update();
   radiogroup_harvested_biomass              ->Update();
   radiogroup_stem_type                      ->Update();

   edit_kc                                   ->Update();
   edit_ET_crop_coef                         ->Update();
   edit_max_water_uptake_mm                  ->Update();

   edit_max_water_upake_before_fruit         ->Update();
   edit_max_water_uptake_during_intial_fruit ->Update();
   edit_max_water_uptake_during_rapid_fruit  ->Update();
   edit_max_water_uptake_during_veraison     ->Update();
   edit_max_water_uptake_after_maturity      ->Update();

   edit_leaf_water_pot_stomatal_closure      ->Update();
   edit_wilt_leaf_water_pot                  ->Update();
   edit_max_LAI                              ->Update();
   edit_initial_GAI                          ->Update();
   edit_regrowth_GAI                         ->Update();
   edit_specific_leaf_area                   ->Update();
   edit_stem_leaf_partition                  ->Update();
   edit_fract_LAI_mature                     ->Update();

   // Canopy cover based  canopy growth
   // canopy cover
   edit_canopy_cover_initial                 ->Update();
   edit_canopy_cover_maximum                 ->Update();
   edit_canopy_cover_total_season_end        ->Update();                         //171219
   edit_begin_senescence_deg_day             ->Update();
   edit_full_senescence_deg_day              ->Update();                         //131024

   radiogroup_abscission                     ->Update();                         //141120

   // Root
   edit_max_root_depth                       ->Update();
   edit_root_length_per_unit_mass            ->Update();
   edit_surface_root_density                 ->Update();
   edit_root_density_distribution_curvature  ->Update();
   edit_max_root_depth_dd                    ->Update();

   edit_root_shoot_emergence_ratio           ->Update();                         //130627
   edit_root_shoot_full_ratio                ->Update();                         //130627
   edit_root_sensitivity_to_water_stress     ->Update();                         //130628

   // Water use efficiency
   checkbox_WUE_changes                      ->Update();
   edit_WUE_change_deg_day                   ->Update();
   edit_TUE_scaling_coef                     ->Update();
   edit_TUE_scaling_coef_vegetative          ->Update();
   edit_TUE_at_1kPa_VPD                      ->Update();
   edit_TUE_at_1kPa_VPD_vegetative           ->Update();
   edit_water_productivity                   ->Update();
   edit_water_productivity_vegetative        ->Update();
   edit_reference_biomass_transp_coef_0      ->Update();
   edit_reference_biomass_transp_coef_vegetative_0->Update();
   edit_seasonal_adjustment_2    ->Update();
   edit_seasonal_adjustment_3    ->Update();
   edit_seasonal_adjustment_4    ->Update();
   edit_seasonal_adjustment_5    ->Update();

   edit_RUE_global_basis                              ->Update();                //110825
   // Only in V4   edit_RUE_PAR_basis                                ->Update();              //110825

   edit_LWP_that_reduces_canopy_expansion    ->Update();
   edit_LWP_that_stops_canopy_expansion      ->Update();

   //170525obs edit_opt_temp_for_growth                  ->Update();

   edit_min_tolerable_temp          ->Update();                                  //130531
   edit_max_tolerable_temp          ->Update();
   edit_low_threshold_limit_temp    ->Update();
   edit_high_threshold_limit_temp   ->Update();


   edit_at_pt_root_limit                     ->Update();
   checkbox_clipping_resets                  ->Update();
   edit_deg_day_emerge                       ->Update();
   edit_deg_day_tuber_initiation             ->Update();
   edit_deg_day_end_vegetative_growth        ->Update();
   edit_deg_day_begin_flower                 ->Update();
   edit_deg_day_begin_filling_grain_or_fruit ->Update();
   edit_deg_day_begin_rapid_fruit_growth     ->Update();
   edit_deg_day_begin_maturity               ->Update();
   checkbox_maturity_significant             ->Update();

   radiogroup_thermal_response->Update();                                        //170402
   edit_base_temp             ->Update();
   edit_cutoff_temp           ->Update();
   edit_opt_temp              ->Update();
   edit_max_temp              ->Update();
   edit_phenologic_sensitivity_water_stress->Update();

   checkbox_vernalization  ->Update();
   {
      edit_vern_low_temp      ->Update();
      edit_vern_high_temp     ->Update();
      edit_vern_start        ->Update();
      edit_vern_end           ->Update();
      edit_vern_min_factor         ->Update();
   }

   radiogroup_photoperiod_consideration       ->Update();
   edit_stop_daylength                       ->Update();
   edit_constrained_daylength                ->Update();

   edit_HI_unstressed                     ->Update();
   checkbox_HI_general_adjustments        ->Update(); //150210

   edit_HI_growth_sensitivity             ->Update();
   checkbox_HI_extreme_adjustments        ->Update(); //150210_110907
   edit_HI_tuber_init_sensitivity         ->Update();
   edit_HI_tuber_growth_sensitivity       ->Update();

   edit_grain_translocation_fraction        ->Update(); // was edit_grain_translocation_factor

/*currently only in V4
   edit_cold_stress_no_stress_threshold_temperature   ->Update();                //130416
   edit_cold_stress_max_stress_threshold_temperature  ->Update();                //130416
   edit_cold_stress_sensitivity                       ->Update();                //130416
   edit_cold_stress_exposure_damaging_hours           ->Update();                //130416

   edit_heat_stress_no_stress_threshold_temperature   ->Update();                //130416
   edit_heat_stress_max_stress_threshold_temperature  ->Update();                //130416
   edit_heat_stress_sensitivity                       ->Update();                //130416
   edit_heat_stress_exposure_damaging_hours           ->Update();                //130416
*/

   {
      edit_fruit_fract_total_solids          ->Update();
      edit_fruit_load_max                    ->Update();
      checkbox_grape                         ->Update();
      edit_initial_fruit_mass                ->Update();
      edit_initial_reserves_release_rate     ->Update();
      edit_clusters_per_vine                 ->Update();
      edit_berries_per_cluster               ->Update();
      edit_fruits_per_tree                ->Update();

   radiogroup_fruit_harvest_condition     ->Update();
   edit_harvest_temperature               ->Update();
   edit_harvest_temperature_days          ->Update();
   edit_harvest_DOY_earliest              ->Update();
   edit_harvest_DOY_latest                ->Update();
   }
   {
      radiogroup_RULSE2_residue_type           ->Update();
      edit_carbon_fraction                      ->Update();
      edit_stubble_area_covered_to_mass_ratio   ->Update();
      edit_surface_area_covered_to_mass_ratio   ->Update();
      edit_fast_cycling_top_fraction            ->Update();
      edit_slow_cycling_top_fraction            ->Update();
      edit_lignified_top_fraction               ->Update();
      edit_fast_cycling_root_fraction           ->Update();
      edit_slow_cycling_root_fraction           ->Update();
      edit_lignified_root_fraction              ->Update();
      edit_fast_cycling_C_N_ratio               ->Update();
      edit_slow_cycling_C_N_ratio               ->Update();
      edit_lignified_C_N_ratio                  ->Update();
      edit_fast_cycling_decomposition_time_50   ->Update();
      edit_slow_cycling_decomposition_time_50   ->Update();
      edit_lignified_decomposition_time_50      ->Update();
      edit_detrition_time                       ->Update();
   }
   {
      button_nitrogen_fixation               ->Update();
      edit_residual_N_not_available_for_uptake  ->Update();
      edit_soil_N_conc_where_N_uptake_decreases ->Update();
      edit_PAW_where_N_uptake_rate_decreases    ->Update();

      edit_BM_start_dilution_crit_conc       ->Update();                         //130319
      edit_N_emerge_crit_conc                ->Update();                         //130319
      edit_N_emerge_max_conc                 ->Update();                         //130319

      edit_N_max_stubble                     ->Update();
      edit_root_N_conc                       ->Update();

      edit_N_max_daily_uptake_rate           ->Update();
      radiogroup_nitrogen_leaf_stress_mode   ->Update();
      edit_N_mature_max_conc                 ->Update();                         //120505
      crop->nitrogen.provide_concentration_slope(crop->photosynthetic_pathway_labeled.get()); //120505
      edit_conc_slope                        ->Update();                         //120505
      edit_end_dilution_curve                ->Update();                         //130408
   }
   edit_osmotic_pot_50                       ->Update();
   edit_salt_tolerance_P                     ->Update();
   edit_CO2_growth_ratio_elevated_to_baseline->Update();
   edit_CO2_elevated_reference_conc          ->Update();
   edit_CO2_baseline_reference_conc          ->Update();

   edit_TUE_reference_conc                   ->Update();                         //131206
   edit_RUE_reference_conc                   ->Update();                         //131206
   edit_CO2_alpha                            ->Update();                         //131206
   edit_CO2_theta                            ->Update();                         //131206
   edit_CO2_growth_ratio_asymptotic          ->Update();                         //131206

   edit_inducement_temperature               ->Update();
   edit_quiescence_end_DOY                   ->Update();                         //161004
   edit_quiescence_start_DOY                 ->Update();                         //161004
//161004   button_start_valid_date                   ->Update();  // 080401 eventually rename this to inactive_period_start_date_button
//161004   button_leave_valid_date                   ->Update();  // 080401 eventually rename this to inactive_period_end_date_button
   edit_chill_requirement                    ->Update();
   edit_deg_day_bud_break_chill_req_sat      ->Update();
   edit_deg_day_bud_break_chill_req_not_sat  ->Update();
   edit_dormancy_senesce->Update();
   edit_consider_inactive_days            ->Update();
   checkbox_sensitive_to_cold             ->Update();
   edit_damage_cold_temperature           ->Update();
   edit_lethal_cold_temperature           ->Update();
   edit_hardiness_fruit_damage            ->Update();
   edit_hardiness_fruit_lethal            ->Update();

   edit_salvageable_deg_day               ->Update();
   edit_branch_insertion_height           ->Update();
   edit_branch_insertion_height           ->Update();
   edit_row_azimuth                       ->Update();
   edit_row_spacing                       ->Update();
   edit_tree_spacing                      ->Update();
   edit_initial_row_width                 ->Update();
   edit_final_row_width                   ->Update();
   edit_initial_tree_breadth              ->Update();
   edit_final_tree_breadth                ->Update();
   edit_initial_row_height                ->Update();
   edit_final_row_height                  ->Update();
   edit_leaf_duration_sensitivity_stress->Update();
   edit_deg_day_leaf_duration             ->Update();

   radiogroup_emergence_model             ->Update();
   edit_seedling_leaf_area                ->Update();
   edit_germination_base_temperature      ->Update();
   edit_mean_base_soil_water_pot          ->Update();
   edit_stdev_base_soil_water_pot         ->Update();
   edit_a                                 ->Update();
   edit_b                                 ->Update();
   checkbox_HI_general_adjustments        ->Update(); //150210
   checkbox_HI_extreme_adjustments        ->Update(); //150210
   edit_linger->Update();
   //180601 pagecontrol_season_dormancy_mode
   pagecontrol_inactivity
      ->ActivePageIndex = crop->season_dormancy_mode_labeled.get_int32();
   radiogroup_WUE_submodel->Update();
   update_root_biomass_checksum(0);
   update_top_biomass_checksum(0);
   show_hide_controls();
}
//______________________________________________________________________________
void TCrop_editor_form::show_hide_controls_V4_and_V5()
{
   if (!crop) return;
   bool CROPSYST_OR_CROPGRO_MODEL = ((crop->crop_model_labeled.get() == CROPSYST_CROP_MODEL) || (crop->crop_model_labeled.get() == CROPGRO_MODEL));
   bool CROPSYST_FRUIT = (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);
   checkbox_grape->Visible             = crop->harvested_part_labeled.get()==fruit_part;
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
   edit_HI_unstressed->Visible = crop->applies_harvest_index();
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
   //170524obs edit_opt_temp_for_growth               ->Visible = CROPSYST_OR_CROPGRO_MODEL;

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

   bool hardness_enabled = crop->tolerance.enabled;
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

   bool photoperiod_enabled = crop->photoperiod.photoperiodism /*.consideration_cowl.get()*/ > no_photoperiod; //110606
   groupbox_photoperiod_daylength->Visible = photoperiod_enabled;
   edit_stop_daylength        ->Enabled = photoperiod_enabled;
   edit_constrained_daylength ->Enabled = photoperiod_enabled;

   switch (crop->photoperiod.photoperiodism/*consideration_cowl.get()*/)
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
   bool canopy_growth_leaf_area_index_based =
        (crop->morphology.canopy_growth_cowl.get() == leaf_area_index_based_duration)
      ||(crop->morphology.canopy_growth_cowl.get() == canopy_architecture);
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
//______________________________________________________________________________
void TCrop_editor_form::handle_update_root_biomass_checksum()
{  bool valid =  CORN::is_approximately<float32>(root_checksum,1.0,0.000001);
   root_biomass_checksum->Color = valid ? clLime: clRed;
   root_biomass_checksum->Update();
}
//______________________________________________________________________________
void TCrop_editor_form::handle_update_top_biomass_checksum()
{  bool valid =  CORN::is_approximately<float32>(top_checksum,1.0,0.000001);
   top_biomass_checksum->Color = valid ? clLime: clRed;
   top_biomass_checksum->Update();
}
//______________________________________________________________________________
void TCrop_editor_form::handle_crop_model_radiogroup_onclick()
{  if (!crop) return;
   crop->harvested_part_labeled.set
      ((crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)
      ? fruit_part: grain_part);
   radiogroup_harvested_biomass->Update();
   show_hide_controls();
}
//_2011-05-23____________________________handle_crop_model_radiogroup_onclick__/
void __fastcall  TCrop_editor_form::bind_to_harvest_index()
{
   if (!crop)
      return;
   edit_HI_unstressed                     ->bind_to( &(crop->harvest.p_index_unstressed) V4_HELP_URL(HELP_P_crop_harvest_index));
   edit_HI_unstressed->Visible = crop->applies_harvest_index();

   tabsheet_harvest_grain->TabVisible = true;  // We need to have all the tabs visible
   tabsheet_harvest_tuber->TabVisible = true;   // before we hide them incase we hide the only one that is visible (VCL compains)
   tabsheet_harvest_fruit->TabVisible = true;

   tabsheet_harvest_grain->TabVisible = crop->harvested_part_labeled.get()==grain_part;
   tabsheet_harvest_tuber->TabVisible = crop->harvested_part_labeled.get()==tuber_part; // Maybe also root crop
   bool is_fruit = (crop->harvested_part_labeled.get() == fruit_part) || (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);
   tabsheet_harvest_fruit->TabVisible = crop->is_fruit_tree();
   tabsheet_harvest_other->TabVisible = !tabsheet_harvest_grain->TabVisible && !tabsheet_harvest_tuber->TabVisible  && !    tabsheet_harvest_fruit->TabVisible; // 110907

   edit_HI_growth_sensitivity             ->bind_to(&(crop->harvest.p_growth_sensitivity)  V4_HELP_URL(HELP_P_crop_harvest_sens_water_stress));
   edit_HI_growth_sensitivity             ->Visible =
      (((crop->harvested_part_labeled.get()==leaf_part)
//140122        || crop->tea
       )
      &&(crop->crop_model_labeled.get() == CROPSYST_CROP_MODEL ));

   // The following will be hidden using sheets
//150210obs   edit_HI_flowering_sensitivity             ->bind_to( &(crop->harvest.p_flowering_sensitivity) V4_HELP_URL(HELP_P_crop_harvest_sens_water_stress));

   edit_HI_tuber_init_sensitivity            ->bind_to( &(crop->harvest.p_tuber_init_sensitivity)  V4_HELP_URL(HELP_P_crop_harvest_sens_water_stress));
   edit_HI_tuber_growth_sensitivity          ->bind_to( &(crop->harvest.p_tuber_growth_sensitivity)  V4_HELP_URL(HELP_P_crop_harvest_sens_water_stress));

   checkbox_HI_general_adjustments->bind_to(&(crop->harvest.apply_adjustment_to_unstressed_harvest_index)); //150210
   checkbox_HI_extreme_adjustments->bind_to(&(crop->harvest.apply_heat_extreme_adjustment_to_unstressed_harvest_index)); //150210


   edit_grain_translocation_fraction->bind_to(&(crop->harvest.p_translocation_fraction_max/*161004 p_translocation_fraction*/)/*NO_HELP_YET_*/ );            //120316

/* Currently only in V4, in V5 there will be more generalized scheduling of parameter adjustments
   edit_heat_stress_no_stress_threshold_temperature   ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity.heat.no_stress_threshold_temperature),1,0);
   edit_heat_stress_max_stress_threshold_temperature  ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity.heat.max_stress_threshold_temperature),1,0 );
   edit_heat_stress_sensitivity                       ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity.heat.sensitivity ),2,0 );
   edit_heat_stress_exposure_damaging_hours           ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity.heat.exposure_damaging_hours ),1,0 );
   edit_heat_stress_exposure_initial_hour             ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity.heat.exposure_initial_hour ),1,0 );

   edit_cold_stress_no_stress_threshold_temperature   ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.no_stress_threshold_temperature),1,0 );
   edit_cold_stress_max_stress_threshold_temperature  ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.max_stress_threshold_temperature),1,0 );
   edit_cold_stress_sensitivity                       ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.sensitivity),2,0 );
   edit_cold_stress_exposure_damaging_hours           ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.exposure_damaging_hours),1,0 );
   edit_colc_stress_exposure_initial_hour             ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.exposure_initial_hour),1,0 );
*/
}
//_2011-06-04___________________________________________________________________
void __fastcall TCrop_editor_form::show_hide_dormancy()
{  if (!crop) return;
   bool CROPSYST_FRUIT (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);
   groupbox_chill_requirements->Visible = CROPSYST_FRUIT;
}
//_2011-06-04___________________________________________________________________
void TCrop_editor_form::handle_crop_class_combobox_onchange()
{

   CORN::OS::Directory_name_concrete database_crop_default_dir
      (*program_directory,L"default");
   // Note that default_crops_list entries should now be fully qualified names
   // although they are displayed unqualified and without extensions
   // I should be able to simply get the resepectivye entry and not
   // need to construct the file name as follows: TComboBox
   std::wstring default_name(crop_class_combobox->Items->Strings[crop_class_combobox->ItemIndex].c_str());

   CORN::OS::File_name_concrete default_filename(database_crop_default_dir,default_name,CS_crop_EXT );
   if (Application->MessageBox(_TEXT("Loading defaults will change all current crop parameters. Continue?"),_TEXT("Load default crop parameters"),MB_YESNO) == IDYES)
   {  CORN::VV_File default_file(default_filename.c_str());
      default_file.get(*crop);
      bind_to(crop,parameter_file_form,crop_model);
      Update();
      parameter_file_form->edit_description->Update();
   }
   CORN::OS::file_system_engine.set_current_working_directory(crop_directory);
}
//______________________________________________________________________________
void TCrop_editor_form::handle_calibrate_button_on_click()
{
   // Need to save the file so the crop calibrator can load
   parameter_file_form-> WindowState = wsMinimized;
   parameter_file_form->run_file_with_program
      (CS::Suite_directory->CropSyst().crop_calibrator_executable().c_str()
      ,0    // const char *secondary_file = 0
      ,0    // const char *options = 0
      ,true //  bool  wait_for_termination = true   // True if this editor is held until the other program exits
      ,SW_SHOWNORMAL);  // or SW_MINIMIZE  SW_MAXIMIZE
   parameter_file_form-> WindowState = wsNormal;
   parameter_file_form->get_parameters();
   Update();
}
//______________________________________________________________________________
void TCrop_editor_form::handle_radiogroup_photosynthetic_click()
{  int photopath = radiogroup_photosynthetic->ItemIndex;
   crop->nitrogen.p_N_mature_max_conc.initial_value
      //161004 Warning, I dont remember if initial_value replaced  default_value
      //161004 default_value
      = CropSyst::N_mature_max_conc_default[photopath];
   crop->nitrogen.dilution_curve_slope = 0.0;
   crop->nitrogen.p_dilution_curve_slope.initial_value
   //161004 Warning, I dont remember if initial_value replaced  default_value
      //161004 default_value
      = crop->nitrogen.provide_concentration_slope(photopath);
   crop->nitrogen.p_biomass_to_start_dilution_crit_N_conc.initial_value
   //161004 Warning, I dont remember if initial_value replaced  default_value
      //161004 default_value
      = CropSyst::biomass_to_start_dilution_crit_N_conc_default[photopath];      //130320
   edit_N_emerge_max_conc  ->Update();                                           //130320
   edit_N_emerge_crit_conc ->Update();                                           //130320
   edit_BM_start_dilution_crit_conc  ->Update();                                 //130320
   edit_N_mature_max_conc  ->Update();
   edit_conc_slope         ->Update();
}
//_2012-05-05___________________________________________________________________
void TCrop_editor_form::handle_preset_end_dilution()
{  switch (radiogroup_preset_end_dilution->ItemIndex)
   {  case 0 : crop->nitrogen.end_dilution_curve_deg_day = 0; break; // (Never ends)
      case 1 : crop->nitrogen.end_dilution_curve_deg_day = crop->phenology.initiation.flowering    /*161004 begin_flowering_deg_day*/;        break; // Begin flowering
      case 2 : crop->nitrogen.end_dilution_curve_deg_day = crop->phenology.initiation.filling      /*161004begin_filling_deg_day*/;           break; // Yield formation
      case 3 : crop->nitrogen.end_dilution_curve_deg_day = crop->phenology.culmination.accrescence /*161004max_canopy_deg_day*/;              break; // End of vegetative growth
      case 4 : crop->nitrogen.end_dilution_curve_deg_day = crop->phenology.initiation.senescence   /*161004begin_senescence_deg_day*/;        break; // Physiological maturity
      case 5 : crop->nitrogen.end_dilution_curve_deg_day = crop->phenology.initiation.maturity     /*161004begin_maturity_deg_day*/;          break; // Begin senescence
   }
   edit_end_dilution_curve->Update();
}
//_2013-04-08__________________________________________________________________/
void __fastcall TCrop_editor_form::radiogroup_abscissionClick(TObject *Sender)
{  edit_linger->Visible = (crop->abscission_labeled.get() == semi_deciduous );
}
//---------------------------------------------------------------------------



/* Todo
continue here.

Move the senecense degree days to Phenology (from canopy growth copy cover)
(this is now applicable to all crops).

Emergence and max root depth degree days should be optional
(With checkbox like maturity).




Nitrogen demand adjustment (delete)


Biomass to start dilution of max N conc
replace with  new parameter
Biomass to start dilution of critical N concentration



Concentration curve slope
replace with (rename to)
Dilution curve slope


N_max_conc_at_emergence_species  will be an input



parameters.calc_biomass_to_start_dilution_crit_N_conc_T_ha
will now just be a parameter

scaling_factor_critical_N_conc_species obsolete


*/




