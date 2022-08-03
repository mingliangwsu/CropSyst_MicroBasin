#ifdef USE_PCH
#  include <common/weather/weather_pch.h>
#else
#  include <common/weather/v_locfile.h>
#endif
#include <common/weather/v_locfile.h>
#include <cropsyst/cpp/static_phrases.h>
//______________________________________________________________________________
Valid_location_parameters::Valid_location_parameters(uint8 version_major,uint8 version_release,uint8 version_minor)
: Location_parameters("noname.ued",version_major,version_release,version_minor) // the correct filename should be loaded
, status(unknown_status)
, v_weather_file_htm(CORN::File_name(weather_filename,"htm").c_str())
, weather_file_status(unknown_status)
{};
//_2004-04-16_____________________________________________________________________________
Validation_status Valid_location_parameters::validate(const LOC_filename &file_name, bool mean_peak_rainfall_required)
{  status = file_name.exists()?unknown_status:missing_status;                    //000305
   File_name validation_filename_htm(file_name,"htm");
   ofstream vf(validation_filename_htm.c_str());                                 //020424
   CORN_string vs;
   // vf is the validation output file.
   Parameter_file_validation val(file_name,vf);
   val.existence_check();
   val.description_check((description != ""));
   val.start_parameter_check_table();
   val.set_worst_status(v_latitude_dec_deg.validate(vs,true));
   val.set_worst_status(v_longitude_dec_deg.validate(vs,true));                  //991004
   val.set_worst_status(v_aridity_factor.validate(vs,true));                     //980303
   val.set_worst_status(v_mean_peak_rainfall_1.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_2.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_3.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_4.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_5.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_6.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_7.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_8.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_9.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_10.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_11.validate(vs,true));
   val.set_worst_status(v_mean_peak_rainfall_12.validate(vs,true));
   val.end_parameter_check_table();
   vf << vs;                                                                     //020424
   if (mean_peak_rainfall_required)
   {  bool missing_mean_peak_rainfall = FALSE;
      for (int m=1; m<= 12;m++)
         missing_mean_peak_rainfall |= (mean_peak_rainfall[m] == 0.0);
      if (missing_mean_peak_rainfall)
           vf << (TL_Error) << ':'
           << (TL__Erosion_simulation) << ' ' << (TL_enabled) <<", "
           << (TL_Mean_peak_1_2_hour_rainfall) << ' ' << "must be greater than" /*(TL_must_be_greater_than)*/ << " 0" << endl;   //020424
   };
   return val.get_status();
};
//______________________________________________________________________________
