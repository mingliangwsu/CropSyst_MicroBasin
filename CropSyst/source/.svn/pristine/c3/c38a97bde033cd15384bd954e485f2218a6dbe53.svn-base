#  include "UED/library/std_codes.h"
#  include "storm.h"
#  include "common/weather/loc_param.h"
#  include "UED/library/database_file.h"
#  include "common/weather/database/weather_database.h"
#  include "corn/OS/file_system_engine.h"
//______________________________________________________________________________
Storm_database_or_generator::Storm_database_or_generator
(const UED_File_name &_storm_database_filename,Weather_daily &_daily_weather)
:Storm_generator
(
#if (CS_VERSION == 4)
_daily_weather.get_location_parameters() ? _daily_weather.get_location_parameters()->mean_peak_rainfall :
#else
//131008 NYI need to decide where I am going to store peek rainfall in V5
#endif
 0
 ) //120529

,daily_weather(_daily_weather)
,storm_database
   (CORN::OS::file_system_engine.exists(_storm_database_filename)
   ? new UED::Database_file_indexed(_storm_database_filename.c_str(),(std::ios_base::in ))
   : 0 )
//160706 #ifdef WEATHER_PROVIDER_VERSION
,can_generate_storms(                                                            //050619
         _daily_weather.weather_data->get_location_parameters()                  //110910
         ? _daily_weather.weather_data->get_location_parameters()->has_mean_peak_rainfall() //110910
         : false // If a UED file is selected, it won't necessarily have an associted .LOC file
                  // In this case no mean peak_rain_fall parameters so no storms generaion.
         )
//160706 #else
//160706 ,can_generate_storms(                                                            //050619
//160706          _daily_weather.weather_data->get_location_parameters()
//160706          ? _daily_weather.weather_data->get_location_parameters()->has_mean_peak_rainfall()
//160706          : false // If a UED file is selected, it won't necessarily have an associted .LOC file
//160706                   // In this case no mean peak_rain_fall parameters so no storms generaion.
//160706          )
//160706 #endif
{
//000303          UED database should now be setup to initialize itself so this may be superfluous, need to test
   if (storm_database) storm_database->initialize();
}
//______________________________________________________________________________
Storm_database_or_generator::~Storm_database_or_generator()
{  if (storm_database) delete storm_database;
}
//_2000-03-03___________________________________________________________________
float64 Storm_database_or_generator::get_eff_precipitation_mm_by_interval
(bool          generate_intensity
,Minutes       interval_minutes
,Minutes       default_event_duration_minutes                                          //080801
,CORN::Time          &event_start_time   // time the event starts is generated.           //990505
,Dynamic_float_array &precip_X_minute // <- returned
,const CORN::Date    &i_date)
{
   float64 eff_precip_mm = m_to_mm(0);
   assert(false); // I need to get eff_precip  from weather_provide
   nat16 intervals = default_event_duration_minutes/interval_minutes;           //080715
   if (storm_database)
   {
      Storm_event_search search_date(i_date);
      UED::Binary_data_record *target_date_storm_record =
      storm_database->locate_data_record
      (UED::Record_type_distinguisher_interface::UED_data_set_date_time_var_units
      ,UED::STD_VC_precipitation.get()
      ,search_date
      );
      // If there is no such record then there is not precip for the day
      if (target_date_storm_record)
            precip_X_minute.copy(target_date_storm_record->get_data_values());
      else  precip_X_minute.clear();
   } else if (can_generate_storms) // We generate on the fly
   {
//000303_         We could record the generated precip in the newly created
//                database for future reference and to be used by successive
//                simulation runs.
      Storm_generator::get_precipitation_mm_by_interval
      (generate_intensity,interval_minutes,event_start_time,precip_X_minute,i_date,eff_precip_mm);
   } else
   {  // Distribute evenly
      float32 precip_in_ts = eff_precip_mm/intervals;
      for (int i = 0 ; i< intervals; i++)
         precip_X_minute.set(i,precip_in_ts);
   };
#ifdef CHECKING
delete this
    if (eff_precip_mm == 0)                                                      //990501
           precip_X_minute.clear(); // Either no precip or snow                  //990501
    // Apportion melting
    float64 snow_melt_today = daily_weather.get_snow_melted();
    for (int i = 0; i < intervals; i++)                                          //990501
                precip_X_minute.increment_by(i,snow_melt_today/intervals ); // spread it out over about 20 intervals  //990501
#endif
   float64 total_precip_mm = precip_X_minute.sum(); // Includes snow             //990501
   if (eff_precip_mm == 0)                                                       //990501
         precip_X_minute.clear(); // Either no precip or snow                    //990501
   else                                                                          //990501
      if (total_precip_mm > 0.0)                                                 //000306
      {  // This could be melting or snow storage                                //990501
         float64 ratio = eff_precip_mm/total_precip_mm;                          //000306
         precip_X_minute.multiply_by(ratio);                                     //000306
      }
   else
      {  float64 diff = eff_precip_mm - total_precip_mm;                         //990501
         for (int i = 0; i < intervals ; i++)                                    //990501
            precip_X_minute.increment_by(i,diff/intervals);                      //990501
                    // spread it out over intervals
      }
   float64 distributed_eff_precip_mm = precip_X_minute.sum();                    //000217
   return distributed_eff_precip_mm;
}
//______________________________________________________________________________
