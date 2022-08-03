#ifdef USE_PCH
#  include <CropSyst/GUI/OWL/headers.h>
#else
#  include "v_cropfile.h"
#include <corn/validate/parameter_file.h>
#endif
#pragma hdrstop

#include "static_phrases.h"
//______________________________________________________________________________
/*_______*/ Valid_crop_parameters::Valid_crop_parameters()
: Crop_parameters()
, status(unknown_status) // i_filename.exists()?unknown_status:missing_status)
{};
//______________________________________________________________________________
Validation_status Valid_crop_parameters::validate(const CRP_filename &file_name)
{
  status = file_name.exists()?unknown_status:missing_status; // presume good then find any problems
   File_name validation_filename_htm(file_name,"htm");
   ofstream vf(validation_filename_htm.c_str());
   // vf is the validation output file.
   Parameter_file_validation val(file_name,vf);
   val.existence_check();
   val.description_check((description != ""));
   if (deg_day_base_temp > opt_temp_for_growth)
   {
    vf << (TL_Error) << ':' << (TL_Base_temperature) << " (" <<
        (TL_Degree_days) << ") (";
    vf.width(6); vf.precision(3);
    vf << deg_day_base_temp << ')' << endl <<
        (TL_must_be_less_than) << ' ' <<
        (TL_Optimum_mean_daily_temperature_for_growth) << " (";
    vf.width(6); vf.precision(3);
    vf << opt_temp_for_growth << ")"
    << "<P>"
    << endl;
      status = error_high_status;
   };
   if (deg_day_cutoff_temp < opt_temp_for_growth)
   { vf << (TL_Error) << ':' << (TL_Cutoff_temperature)
      << " (" << (TL_Degree_days) << ") (";
   vf.width(6); vf.precision(3);
   vf << deg_day_cutoff_temp << ')' << endl
      << (TL_must_be_greater_than) << ' '
      << (TL_Optimum_mean_daily_temperature_for_growth) << " (";
   vf.width(6); vf.precision(3);
   vf << opt_temp_for_growth << ')'
    << "<P>"
   << endl;
   status = error_low_status;                                                    //000305
   };
   if (hardiness && (hardiness->damage_cold_temp < hardiness->lethal_cold_temp)) //991029
   { vf << (TL_Error) << ':' << (TL_Cold_temperature_damage_crop)
      << " (" << (TU_degrees_C) << ") (";
   vf.width(6); vf.precision(3);
   vf << hardiness->damage_cold_temp << ')' << endl
      << (TL_must_be_greater_than) << ' '
      << (TL_Cold_temperature_lethal_crop) << " (";
   vf.width(6); vf.precision(3);
   vf << hardiness->lethal_cold_temp << ')'
    << "<P>"
    << endl;
   status = error_low_status;
   };
   if (deg_day_emerge > deg_day_begin_flower)
   { vf << (TL_Error) << ':' << (TL_Degree_days) << ": "
      << (TL_Emergence) << " (" << deg_day_emerge << ')'<<endl << '-'
      << (TL_must_be_less_than_degree_days_of) <<' '
      << (TL_Begin_flowering) << " (" << deg_day_begin_flower << ")."
      << "<P>"
      << endl;
      status = error_high_status;
   };
   val.start_parameter_check_table();
   CORN_string vs;
   val.set_worst_status(v_deg_day_base_temp.validate(vs,true));
   val.set_worst_status(v_deg_day_cutoff_temp.validate(vs,true));
   val.set_worst_status(v_deg_day_emerge.validate(vs,true));
   if (! perennial)
      val.set_worst_status(v_deg_day_leaf_duration.validate(vs,true));
   val.set_worst_status(v_deg_day_begin_flower.validate(vs,true));
   val.set_worst_status(v_deg_day_peak_LAI.validate(vs,true));
   val.set_worst_status(v_deg_day_tuber_initiation.validate(vs,true));
   val.set_worst_status(v_deg_day_begin_grain_filling.validate(vs,true));
   val.set_worst_status(v_deg_day_begin_maturity.validate(vs,true));
   val.set_worst_status(v_deg_day_begin_veraison.validate(vs,true));
   if (fruit)
   {  val.set_worst_status(fruit->v_max_fruit_load_kg_ha.validate(vs,true));
      val.set_worst_status(fruit->v_max_fruit_load_kg_ha.validate(vs,true));
      val.set_worst_status(fruit->v_fract_total_solids.validate(vs,true));
   };
   val.set_worst_status(v_max_root_depth.validate(vs,true));
   val.set_worst_status(v_max_canopy_height.validate(vs,true));
   val.set_worst_status(v_max_water_uptake.validate(vs,true));
   val.set_worst_status(v_max_LAI.validate(vs,true));
   val.set_worst_status(v_fract_LAI_mature.validate(vs,true));
   val.set_worst_status(v_specific_leaf_area.validate(vs,true));
   val.set_worst_status(v_stem_leaf_partition.validate(vs,true));
   val.set_worst_status(v_leaf_duration_sensitivity_stress.validate(vs,true));
   val.set_worst_status(ET_crop_coef_check_used.validate(vs,true));
   val.set_worst_status(v_biomass_water_ratio.validate(vs,true));
   val.set_worst_status(v_light_to_biomass.validate(vs,true));
   val.set_worst_status(v_at_pt_limit.validate(vs,true));
   val.set_worst_status(v_at_pt_root_limit.validate(vs,true));
   val.set_worst_status(v_opt_temp_for_growth.validate(vs,true));
   if (hardiness)
   {   val.set_worst_status(hardiness->v_damage_cold_temp.validate(vs,true));
      val.set_worst_status(hardiness->v_lethal_cold_temp.validate(vs,true));
      val.set_worst_status(hardiness->v_salvageable_days_before_maturity.validate(vs,true));
   };
   val.set_worst_status(v_stomatal_closure_leaf_water_pot.validate(vs,true));
   val.set_worst_status(v_wilt_leaf_water_pot.validate(vs,true));
   val.set_worst_status(v_phenologic_sensitivity_water_stress.validate(vs,true));
   val.set_worst_status(v_kc.validate(vs,true));
   if (residue_decomposition)
   {  val.set_worst_status(residue_decomposition->v_decomposition_time.validate(vs,true));
      val.set_worst_status(residue_decomposition->v_area_covered_to_mass_ratio.validate(vs,true));
   };

   if (harvest_index)
   {  val.set_worst_status(harvest_index->v_unstressed.validate(vs,true));
      val.set_worst_status(harvest_index->v_flowering_sensitivity.validate(vs,true));
      val.set_worst_status(harvest_index->v_filling_sensitivity.validate(vs,true));
      val.set_worst_status(harvest_index->v_tuber_growth_sensitivity.validate(vs,true));
      val.set_worst_status(harvest_index->v_tuber_init_sensitivity.validate(vs,true));
      val.set_worst_status(harvest_index->v_translocation_factor.validate(vs,true));
   };
   if (vernalization)
   {
      val.set_worst_status(vernalization->v_start.validate(vs,true));
      val.set_worst_status(vernalization->v_end.validate(vs,true));

      val.set_worst_status(vernalization->v_low_temp.validate(vs,true));
      val.set_worst_status(vernalization->v_high_temp.validate(vs,true));
      val.set_worst_status(vernalization->v_min_factor.validate(vs,true));
   };
   if (photoperiod)
   {
   val.set_worst_status(photoperiod->v_start.validate(vs,true));
   val.set_worst_status(photoperiod->v_end.validate(vs,true));
   };
   if (nitrogen)
   {  val.set_worst_status(nitrogen->v_uptake_adjust.validate(vs,true));
      val.set_worst_status(nitrogen->v_availability_adjust.validate(vs,true));
      val.set_worst_status(nitrogen->v_residual.validate(vs,true));
      val.set_worst_status(nitrogen->v_max_concentration_emerge.validate(vs,true));
      val.set_worst_status(nitrogen->v_max_concentration_mature.validate(vs,true));
      val.set_worst_status(nitrogen->v_max_concentration_mature.validate(vs,true));
      val.set_worst_status(nitrogen->v_min_concentration_harvest.validate(vs,true));
      val.set_worst_status(nitrogen->v_max_stubble.validate(vs,true));
   };
   if (salinity)
   {  val.set_worst_status(salinity->v_osmotic_pot_50.validate(vs,true));
      val.set_worst_status(salinity->v_salt_tolerance_P.validate(vs,true));
   };
   if (CO2_response)
   {  val.set_worst_status(CO2_response->v_growth_ratio_elevated_to_baseline_ppm.validate(vs,true));
      val.set_worst_status(CO2_response->v_elevated_reference_conc.validate(vs,true));
      val.set_worst_status(CO2_response->v_baseline_reference_conc.validate(vs,true));
   };
   vf << vs;
   val.end_parameter_check_table();
   if (vernalization)
   {
     if (vernalization->start >= vernalization->end)
     {
       vf << (TL_Error) << ':' << (TL_Vernalization_starts) << " (";
       vf.width(10);vf.precision(5);
       vf << vernalization->start << " ) " << (TL_must_be_less_than)<<' '
          << (TL_Vernalization_complete) << " (";
       vf.width(6); vf.precision(2);
       vf << vernalization->end << ')' << endl;
         val.set_worst_status(error_high_status);
     };
     if (vernalization->low_temp >= vernalization->high_temp)
     {
       vf << (TL_Error) << ':' << (TL_Low_temp_for_opt_vern) << " (";
       vf.width(6);vf.precision(2);
       vf << vernalization->low_temp <<") " << (TL_must_be_less_than) << ' '
          << (TL_High_temp_for_opt_vern) << " (";
       vf.width(6);vf.precision(2);
       vf << vernalization->high_temp << ')' << endl;
         val.set_worst_status(vernalization->v_low_temp.status =error_high_status);
     };
   };
   return val.get_status();
};
//______________________________________________________________________________
