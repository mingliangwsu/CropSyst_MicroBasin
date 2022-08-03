
#ifdef USE_PCH
#  include <CropSyst/GUI/OWL/headers.h>
#else
#  include <corn/std/std_fstream.h>
#  include "v_soilfile.h"
#  include <corn/validate/parameter_file.h>
#endif
//______________________________________________________________________________
Valid_soil_parameters::Valid_soil_parameters()
: Smart_soil_parameters()
, status(unknown_status)
{};
//______________________________________________________________________________
Validation_status Valid_soil_parameters::validate(const SIL_filename &file_name)
{
   status = file_name.exists()?unknown_status:missing_status; // presume good then find any problems
   File_name validation_filename_htm(file_name,"htm");
   CORN_string vs;
   ofstream vf(validation_filename_htm.c_str());
   Parameter_file_validation val(file_name,vf);
   val.existence_check();
   val.description_check((description != ""));
   val.start_parameter_check_table();

   for (int i = 1; i <= number_horizons; i++)
   {
   val.set_worst_status(v_layer_thickness[i]->validate(vs,true));
   val.set_worst_status(v_perm_wilt_point[i]->validate(vs,true));
   val.set_worst_status(v_field_capacity[i]->validate(vs,true));
   val.set_worst_status(v_vol_WC_at_1500[i]->validate(vs,true));
   val.set_worst_status(v_vol_WC_at_33[i]->validate(vs,true));
   val.set_worst_status(v_bulk_density[i]->validate(vs,true));
   val.set_worst_status(v_bypass_coef[i]->validate(vs,true));
   val.set_worst_status(v_sand[i]->validate(vs,true));
   val.set_worst_status(v_clay[i]->validate(vs,true));
   val.set_worst_status(v_silt[i]->validate(vs,true));
   val.set_worst_status(v_sat_hydraul_cond_m_d[i]->validate(vs,true));
   val.set_worst_status(v_air_entry_pot[i]->validate(vs,true));
   val.set_worst_status(v_soil_b[i]->validate(vs,true));
   val.set_worst_status(v_pH[i]->validate(vs,true));
   val.set_worst_status(v_cation_exchange_capacity[i]->validate(vs,true));

   };
   if (override_curve_number_16)
      val.set_worst_status(v_override_curve_number.validate(vs,true));
   if (user_fallow_curve_number_16)
      val.set_worst_status(v_user_fallow_curve_number.validate(vs,true));
   val.set_worst_status(v_steepness.validate(vs,true));
   val.set_worst_status(v_slope_length.validate(vs,true));

   vf << vs;
   val.end_parameter_check_table();

   vf << "<P>Curve number will be ";
   if (override_curve_number_16)
      vf << "Fixed to the specified value" << endl;
   else
      vf << "Computed base on current conditions" << endl;

   vf << "<P>Curve number during fallow will be ";
   if (user_fallow_curve_number_16)
      vf << "Fixed to the specified value" << endl;
   else
      vf << "Computed base on current conditions" << endl;


   return val.get_status();
};
//______________________________________________________________________________
