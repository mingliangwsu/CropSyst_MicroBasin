#ifdef USE_PCH
#  include <CropSyst/GUI/OWL/headers.h>
#else
#  include "v_mgmtfile.h"
#  include <corn/validate/parameter_file.h>
#endif
//______________________________________________________________________________
Valid_management_parameters::Valid_management_parameters ()
: Management_parameters()
, status(unknown_status)
{};
//______________________________________________________________________________
// Enabled for parameter editor
Validation_status Valid_management_parameters::validate(const MGS_MGT_filename &file_name)
{
  status = file_name.exists()?unknown_status:missing_status;

   File_name validation_filename_htm(file_name,"htm");
   ofstream vf(validation_filename_htm.c_str());
   // vf is the validation output file.
   Parameter_file_validation val(file_name,vf);
   val.existence_check();
   val.description_check((description != ""));

   val.start_parameter_check_table();

   CORN_string vs;
   val.set_worst_status(v_soil_conservation_factor.validate(vs,true));
   val.set_worst_status(v_straw_to_residue.validate(vs,true));

//             Planting:
   if (sowing_date_mode_labeled.get() > FIXED_DATE)
   {
      val.set_worst_status(v_sowing_avg_temp.validate(vs,true));
      val.set_worst_status(v_sowing_min_PAW.validate(vs,true));
      val.set_worst_status(v_sowing_max_PAW.validate(vs,true));
      val.set_worst_status(v_expected_days_to_emerge.validate(vs,true));
      val.set_worst_status(v_delay_after_precip.validate(vs,true));
      val.set_worst_status(v_appreciable_precip_mm.validate(vs,true));
   };

#ifdef NYI
   val.set_worst_status(v_trim_biomass_removed.validate(vs,true));
   val.set_worst_status(v_clipping_frequency.validate(vs,true));
#endif
   val.set_worst_status(v_straw_to_residue.validate(vs,true));

   val.set_worst_status(v_soil_conservation_factor.validate(vs,true));
#ifdef NYI
   val.set_worst_status(v_target_yield_N_uptake_kg_ha.validate(vs,true));
   val.set_worst_status(v_critical_soil_NO3_for_no_response_kg_ha.validate(vs,true));
   val.set_worst_status(v_soil_N_sampling_depth.validate(vs,true));
   val.set_worst_status(v_fertilizer_use_efficiency.validate(vs,true));
   val.set_worst_status(v_adjust_relative_growth_rate_for_clipping.validate(vs,true));
   val.set_worst_status(v_minimum_biomass_required_for_clipping.validate(vs,true));
   val.set_worst_status(v_biomass_forces_clipping.validate(vs,true));
   val.set_worst_status(v_minimum_LAI_required_for_clipping.validate(vs,true));

   val.set_worst_status(v_max_allowable_depletion.validate(vs,true));
   val.set_worst_status(v_depletion_observe_depth.validate(vs,true));
   val.set_worst_status(v_net_irrigation_mult.validate(vs,true));
   val.set_worst_status(v_max_application.validate(vs,true));
   val.set_worst_status(v_chem_concentration.validate(vs,true));
   val.set_worst_status(v_salinity.validate(vs,true));
#endif

   // validate irrigation period
   // also validate the chemicals
    vf << vs;
    val.end_parameter_check_table();
 //               auto_NO3_applications must sum to 100
    return val.get_status();
};
//______________________________________________________________________________
