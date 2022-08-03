#include "corn/measure/measures.h"
#include "weather/database/weather_UED_database.h"
#include "UED/library/std_codes.h"
#include "weather/storm_event.h"
#include "corn/OS/file_system_engine.h"
#include "corn/chronometry/time_conversion.h"
#ifndef REACCH
#include "common/weather/loc_param.h"
#endif
#include "corn/data_source/vv_file.h"
#include "UED/library/timeqry.h"
#include "corn/chronometry/date_time_64.h"
using namespace UED;
#  include "common/weather/weather_provider.h"
//______________________________________________________________________________
Weather_UED_database::Weather_UED_database
(const char *filename
,std::ios_base::openmode _openmode
,CORN::Quality_code attribute
,const CORN::OS::File_name *location_filename_to_provide_geolocation)            //091117
: Weather_database()
, Common_weather_creators(attribute)                                             //050421
, database_file(0)                                                               //101008
, owns_database(true)                                                            //101008
, override_set_safety(false)                                                     //991014
#ifndef LOC_ONLY_FOR_GEN
,owns_location_parameters(false)                                                 //050912
,location_parameters(0)                                                          //050912
#endif
{  database_file = new CS_UED::Database_file_indexed(filename,_openmode,false);  //170329_101008
      //140613 In version 5 may want to allow float16
   if (database_file->initialize())                                              //060712
   {
      #ifndef LOC_ONLY_FOR_GEN
      initialize_location(filename,location_filename_to_provide_geolocation);
      #endif
   }      
   else
   {  delete database_file; database_file = 0; }                                 //140728
       // Currently we presume at this point there will be a related
       // location file (from ClimGen)
       // with location estimation parameters
       // normally the UED weather will be complete for CropSyst
       // and these parameters wouldn't be necessary.
}
//_constructor______________________________________________________2003-02-01_/
Weather_UED_database::Weather_UED_database
(CS_UED::Database_file_indexed *_database_file
,bool take_database
,CORN::Quality_code attribute
,const CORN::OS::File_name *location_filename_to_provide_geolocation)            //091117
:database_file(_database_file)
, owns_database(take_database)
, Common_weather_creators(attribute)                                             //050421
, override_set_safety(false)                                                     //991014
#ifndef LOC_ONLY_FOR_GEN
, owns_location_parameters(false)                                                //050912
, location_parameters(0)                                                         //050912
#endif
{  database_file->initialize();
#ifndef LOC_ONLY_FOR_GEN
   initialize_location(database_file->get_file_name(),location_filename_to_provide_geolocation);
#endif
}
//_constructor______________________________________________________2010-10-08_/
#ifndef LOC_ONLY_FOR_GEN
void Weather_UED_database::initialize_location(const char *filename
,const CORN::OS::File_name *location_filename_to_provide_geolocation)
{  bool UED_has_geolocation = database_file->get_geolocation_record_immutable();
   if (location_filename_to_provide_geolocation
       && CORN::OS::file_system_engine.exists(*location_filename_to_provide_geolocation)) //050817
   {  // We have an associated location file with the name name as the UED file. //050817
      // (In V4 this now only occurs if this is a ClimGen parameter location file or an old location/ued file pair) //050817
      location_parameters = new Location_parameters
         (filename
         ,!UED_has_geolocation // Normally UED database stores geolocation, but there may have been some UEDs where geolocation was only in a .LOC file //050525
         /*180626 , 0,0,0*/);  // need to get these from options version number for calling program  //040416
      VV_File loc_file(location_filename_to_provide_geolocation->c_str());
      loc_file.get(*location_parameters);
      owns_location_parameters = true;                                           //050912
   }
}
#endif
//_initialize_location_________________________________________________________/
Weather_UED_database::~Weather_UED_database()
{  database_file->finish();                                                      //171110
   if (owns_database) delete database_file; database_file = 0;                   //101008
#ifdef DISABLED
090313 This is crashing when there is a LOC file with the UED file,
dont see exactly why but it is probably related to the LOC option file override in the constructor
   if (owns_location_parameters && location_parameters) delete  location_parameters;
#endif
}
//_destructor___________________________________________________________________
#ifndef LOC_ONLY_FOR_GEN
const Location_parameters *Weather_UED_database::get_location_parameters() const
{ return location_parameters; }
#endif
//_get_location_parameters__________________________________________2005-05-25_/
#ifndef LOC_ONLY_FOR_GEN
void Weather_UED_database::use_location_parameters(const Location_parameters *_location_parameters)
{
#ifdef DISABLED
090313 This is crashing when there is a LOC file with the UED file,
dont see exactly why but it is probably related to the LOC option file override in the constructor
    if (owns_location_parameters && location_parameters) delete  location_parameters;
#endif
   location_parameters = (Location_parameters *)_location_parameters; owns_location_parameters = false;
}
#endif
//_use_location_parameters__________________________________________2005-09-12_/
const Geolocation *Weather_UED_database::get_geolocation_constant()        const
{  const Geolocation *geoloc_rec = database_file->get_geolocation_record_immutable();
   if (geoloc_rec) return geoloc_rec;
   Geolocation *loc_param_geoloc_rec = 0;
#ifndef LOC_ONLY_FOR_GEN
   if (location_parameters) loc_param_geoloc_rec =                               //050911
      location_parameters->geolocation;
#endif
   return loc_param_geoloc_rec;
}
//_get_geolocation_constant_________________________________________2005-05-25_/
const char *Weather_UED_database::get_description(std::string& return_buffer) const
{  // NYI first check the UED primary comment record
   return_buffer.assign(
      #ifndef LOC_ONLY_FOR_GEN
      location_parameters? location_parameters->get_description():
      #endif
      "");                                                                       //050916
   if (!return_buffer.length())
   {  const Geolocation *geolocation =  get_geolocation_constant();              //050912
      if (geolocation)                                                           //050912
         return_buffer.assign(geolocation->get_station_name());
   }
   return return_buffer.c_str();
}
//_get_description__________________________________________________2005-05-25_/
void Weather_UED_database::invalidate(bool absolutely)
{  override_set_safety = true;
}
//_invalidate_______________________________________________________2009-12-16_/
bool Weather_UED_database::get_to(Weather_provider& provider)
{  UED::Time_query_single_date time_qry
      (provider.date.get_datetime64(),(UED_units_code)UT_day);                   //030714
   override_set_safety = false;                                                  //991013
   CORN::Units_code actual_units;

   //110910 The elements used to need to be loaded (by Weather_base) in this order
   // but I don't know if that is still the case using the new weather provider
   actual_units = UC_meter;         provider.precipitation_actual.set_m                (database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_precipitation.get()             ,time_qry,actual_units,provider.precipitation_actual         ),provider.precipitation_actual);
   actual_units = UC_Celcius;       provider.air_temperature_max.update_value_qualified(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_max_temperature.get()           ,time_qry,actual_units,provider.air_temperature_max   ),provider.air_temperature_max    );
   actual_units = UC_Celcius;       provider.air_temperature_min.update_value_qualified(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_min_temperature.get()           ,time_qry,actual_units,provider.air_temperature_min   ),provider.air_temperature_min    );
   actual_units = UC_Celcius;       provider.air_temperature_avg.update_value_qualified(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_avg_temperature.get()           ,time_qry,actual_units,provider.air_temperature_avg   ),provider.air_temperature_avg    );
   actual_units = UC_MJ_per_m2;     provider.solar_radiation.set_MJ_m2                 (database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_solar_radiation_global.get()             ,time_qry,actual_units,provider.solar_radiation       ),provider.solar_radiation); //151115
   #if (CS_VERSION < 6)
   if (!provider.solar_radiation.is_valid()) // This may be a V4 UED file
      provider.solar_radiation.set_MJ_m2(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_solar_radiation_ERRONEOUS.get()             ,time_qry,actual_units,provider.solar_radiation       ),provider.solar_radiation);
   #endif
   actual_units = UC_Celcius;       provider.dew_point_temperature_max           .update_value_qualified(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_max_dew_point_temperature.get() ,time_qry,actual_units,provider.dew_point_temperature_max) ,provider.dew_point_temperature_max);
   actual_units = UC_Celcius;       provider.dew_point_temperature_min           .update_value_qualified(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_min_dew_point_temperature.get() ,time_qry,actual_units,provider.dew_point_temperature_min) ,provider.dew_point_temperature_min);
   actual_units = UC_percent;       provider.relative_humidity_max               .set_value_quality     (database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_max_relative_humidity.get()     ,time_qry,actual_units,provider.relative_humidity_max ),provider.relative_humidity_max );
   actual_units = UC_percent;       provider.relative_humidity_min               .set_value_quality     (database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_min_relative_humidity.get()     ,time_qry,actual_units,provider.relative_humidity_min ),provider.relative_humidity_min  );
   actual_units = UC_meters_per_second; provider.wind_speed                      .set_m_s               (database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_wind_speed.get()                ,time_qry,actual_units,provider.wind_speed            ),provider.wind_speed);
/*150603 ET model should be provided by the class that needs it
   actual_units = UC_m;             provider.ET_reference.set_m               (database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_pot_evapotranspiration.get()    ,time_qry,actual_units,provider.ET_reference          )    ,provider.ET_reference);
*/
   actual_units = UC_Celcius;       provider.dew_point_temperature_avg           .update_value_qualified(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_avg_dew_point_temperature.get() ,time_qry,actual_units,provider.dew_point_temperature_avg) ,provider.dew_point_temperature_avg);
   actual_units = UC_kPa;           provider.vapor_pressure_deficit_max          .update_value_qualified(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_max_vapor_pressure_deficit.get(),time_qry,actual_units,provider.vapor_pressure_deficit_max),provider.vapor_pressure_deficit_max);
   actual_units = UC_kPa;           provider.vapor_pressure_deficit_fullday_avg  .update_value_qualified(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_avg_fullday_vapor_pressure_deficit.get(),time_qry,actual_units,provider.vapor_pressure_deficit_fullday_avg),provider.vapor_pressure_deficit_fullday_avg);
   actual_units = UC_kPa;           provider.vapor_pressure_deficit_daytime      .update_value_qualified(database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_avg_daytime_vapor_pressure_deficit.get(),time_qry,actual_units,provider.vapor_pressure_deficit_daytime),provider.vapor_pressure_deficit_daytime);
// actual_units = UC_XXXX;                   provider.xxxxxx.set_UNITS                 (database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_xxxx.get()             ,time_qry,actual_units,provider.xxx.quality),provider.xxx.quality);

   //180806 Not working mult inherit problem? actual_units = UC_meter;         provider.ET_reference.set_m                (database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_ref_ET_Penman_Monteith.get()             ,time_qry,actual_units,provider.ET_reference        ),provider.ET_reference); //180806
   //actual_units = UC_meter;

   database_file->get_parameter_on
      (provider.ET_reference
      ,UED::STD_VC_ref_ET_Penman_Monteith.get()
      ,time_qry
      ,UED::Record_type_distinguisher_interface::UED_data_set_year_var_units);   //180806

   bool any_valid
   =  provider.precipitation_actual       .is_valid()
   || provider.air_temperature_max        .is_valid()
   || provider.air_temperature_min        .is_valid()
   || provider.air_temperature_avg        .is_valid()
   || provider.solar_radiation            .is_valid()
   || provider.dew_point_temperature_max  .is_valid()
   || provider.dew_point_temperature_min  .is_valid()
   || provider.relative_humidity_max      .is_valid()
   || provider.relative_humidity_min      .is_valid()
   || provider.wind_speed                 .is_valid()
   || provider.dew_point_temperature_avg  .is_valid()
   || provider.ET_reference               .is_valid()                            //180806
/*
   || provider.vapor_pressure_deficit_max .is_valid()
   || provider.vapor_pressure_deficit_fullday_avg.is_valid()
   || provider.vapor_pressure_deficit_daytime.is_valid()
*/
   ;
   return any_valid;
}
//_get_to___________________________________________________________2011-09-10_/
bool Weather_UED_database::set_from  (Weather_provider& provider)
{  UED::Time_query_single_date time_qry(provider.date.get_datetime64(),(UED_units_code)UT_day);
   UED_units_code actual_units;
   bool record_created = false;
   actual_units = UC_mm;               database_file->set_value(provider.precipitation_actual                .get_mm()         ,time_qry,actual_units,provider.precipitation_actual              ,precipitation_creation              ,record_created,override_set_safety);
   actual_units = UC_Celcius;          database_file->set_value(provider.air_temperature_max                 .Celcius()        ,time_qry,actual_units,provider.air_temperature_max               ,max_temperature_creation            ,record_created,override_set_safety);
   actual_units = UC_Celcius;          database_file->set_value(provider.air_temperature_min               .Celcius()        ,time_qry,actual_units,provider.air_temperature_min             ,min_temperature_creation            ,record_created,override_set_safety);
   actual_units = UC_Celcius;          database_file->set_value(provider.air_temperature_avg                 .Celcius()        ,time_qry,actual_units,provider.air_temperature_avg               ,avg_temperature_creation            ,record_created,override_set_safety);
   actual_units = UC_MJ_per_m2;        database_file->set_value(provider.solar_radiation                     .get_MJ_m2()      ,time_qry,actual_units,provider.solar_radiation                   ,solar_radiation_creation            ,record_created,override_set_safety);
   actual_units = UC_percent;          database_file->set_value(provider.relative_humidity_max               .percent()        ,time_qry,actual_units,provider.relative_humidity_max             ,max_relative_humidity_creation      ,record_created,override_set_safety);
   actual_units = UC_percent;          database_file->set_value(provider.relative_humidity_min               .percent()        ,time_qry,actual_units,provider.relative_humidity_min             ,min_relative_humidity_creation      ,record_created,override_set_safety);
   actual_units = UC_meters_per_second;database_file->set_value(provider.wind_speed                          .get_m_s()        ,time_qry,actual_units,provider.wind_speed                        ,wind_speed_creation                 ,record_created,override_set_safety);
   actual_units = UC_Celcius;          database_file->set_value(provider.dew_point_temperature_max           .Celcius()        ,time_qry,actual_units,provider.dew_point_temperature_max         ,max_dew_point_temperature_creation  ,record_created,override_set_safety);
   actual_units = UC_Celcius;          database_file->set_value(provider.dew_point_temperature_min           .Celcius()        ,time_qry,actual_units,provider.dew_point_temperature_min         ,min_dew_point_temperature_creation  ,record_created,override_set_safety);
   actual_units = UC_Celcius;          database_file->set_value(provider.dew_point_temperature_avg           .Celcius()        ,time_qry,actual_units,provider.dew_point_temperature_avg         ,avg_dew_point_temperature_creation  ,record_created,override_set_safety);
/*150603 ET model should be provided by the class that needs it
   actual_units = UC_m;                database_file->set_value(provider.ET_reference                        .get_m()          ,time_qry,actual_units,provider.ET_reference                      ,pot_evapotranspiration_creation     ,record_created,override_set_safety);
*/
//NYI need vapor_pressure_deficit_max_creation
//   actual_units = UC_kPa;              database_file->set_value(provider.vapor_pressure_deficit_max          .get_kPa()      ,time_qry,actual_units,provider.vapor_pressure_deficit_max        ,XXXX_creation                       ,record_created,override_set_safety);
   actual_units = UC_kPa;              database_file->set_value(provider.vapor_pressure_deficit_fullday_avg  .get_kPa()        ,time_qry,actual_units,provider.vapor_pressure_deficit_fullday_avg,avg_fullday_vapor_pressure_deficit_creation  ,record_created,override_set_safety);
   actual_units = UC_kPa;              database_file->set_value(provider.vapor_pressure_deficit_daytime      .get_kPa()        ,time_qry,actual_units,provider.vapor_pressure_deficit_daytime    ,avg_daytime_vapor_pressure_deficit_creation  ,record_created,override_set_safety);
   actual_units = UC_mm;               database_file->set_value(provider.ET_reference                        .get_mm()         ,time_qry,actual_units,provider.ET_reference                     ,pot_evapotranspiration_FAO_Penman_Monteith_reference_creation              ,record_created,override_set_safety); //180806

   return true;
}
//_set_from_________________________________________________________2011-09-10_/
float64 Weather_UED_database::get_cloud_cover_percent(weather_database_get_formals) const
{  // Not yet implemented (Need to derive a cloud cover variable)
   UED::Time_query_single_date time_qry(date_time_.get_datetime64(),(UED_units_code)UT_day);
   UED_units_code actual_units = UC_percent;
   override_set_safety = false;                                                  //991013
   return (float64) database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_cloud_cover.get(),time_qry,actual_units,attribute);  //000710
}
//_get_cloud_cover_percent__________________________________________1999-10-22_/
float64 Weather_UED_database::get_net_radiation(weather_database_get_formals) const
{  // Not yet implemented (Need to derive a cloud cover variable)
   UED::Time_query_single_date time_qry(date_time_.get_datetime64(),(UED_units_code)UT_day);
   UED_units_code actual_units = UC_percent;
   override_set_safety = false;                                                  //991013
   #if ((CS_VERSION>0)&&(CS_VERSION<=4))
   return (float64) database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_net_radiation.get(),time_qry,actual_units,attribute); //000710
   #else
   float64 net_rad = database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_net_radiation.get(),time_qry,actual_units,attribute); //110125
      #if (CS_VERSION==5)
      if (!attribute.is_valid())
         net_rad = (float64) database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_net_radiation_ERRONEOUS.get(),time_qry,actual_units,attribute);
      #endif
   return net_rad;
   #endif
}
//_get_net_radiation________________________________________________1999-10-22_/
float64 Weather_UED_database::get_isothermal_longwave_net_radiation(weather_database_get_formals) const
{  // Not yet implemented (Need to derive a cloud cover variable)
   UED::Time_query_single_date time_qry(date_time_.get_datetime64(),(UED_units_code)UT_day);
   UED_units_code actual_units = UC_percent;
   override_set_safety = false;                                                  //991013
   #if ((CS_VERSION>0)&&(CS_VERSION<=4))
   return (float64) database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_isothermal_longwave_net_radiation.get(),time_qry,actual_units,attribute); // 000710
   #else
   float64 LWnet_rad = database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_isothermal_longwave_net_radiation.get(),time_qry,actual_units,attribute); // 000710
      #if (CS_VERSION==5)
      if (!attribute.is_valid())
         LWnet_rad =  (float64) database_file->get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_isothermal_longwave_net_radiation_ERRONEOUS.get(),time_qry,actual_units,attribute); // 000710
      #endif
   return LWnet_rad;
   #endif
}
//_get_isothermal_longwave_net_radiation____________________________1999-10-22_/
float64 Weather_UED_database::set_pot_evapotranspiration_FAO_Penman_Monteith_reference_mm
(const CORN::Date_const &date_time_
,float64 pot_ET_mm
,CORN::Quality &attribute)
{  UED::Time_query_single_date time_qry(date_time_.get_datetime64(),(UED_units_code)UT_day);
   UED_units_code actual_units = UC_mm;                                          //040715
   bool record_created = false;                                                  //050524
   return (float64) database_file->set_value(pot_ET_mm,time_qry,actual_units,attribute,pot_evapotranspiration_FAO_Penman_Monteith_reference_creation,record_created,override_set_safety);
}
//_set_pot_evapotranspiration_FAO_Penman_Monteith_reference_mm______1999-04-24_/
float64 Weather_UED_database::set_avg_fullday_vapor_pressure_deficit_kPa
(const CORN::Date_const &date_time_
,float64 avg_VPD_kPa
,CORN::Quality &attribute)
{  UED::Time_query_single_date time_qry(date_time_.get_datetime64(),(UED_units_code)UT_day);
   UED_units_code actual_units = UC_kPa;                                         //040715
   bool record_created = false;                                                  //050524
   return (float64) database_file->set_value(avg_VPD_kPa,time_qry,actual_units,attribute,avg_fullday_vapor_pressure_deficit_creation,record_created,override_set_safety); //010125
}
//_set_avg_fullday_vapor_pressure_deficit_kPa_______________________2001-10-09_/
float64 Weather_UED_database::set_cloud_cover_percent
(const CORN::Date_const &date_time_,float64 cloud_cover_percent  ,CORN::Quality &attribute)
{  UED::Time_query_single_date time_qry(date_time_.get_datetime64(),(UED_units_code)UT_day);
   UED_units_code actual_units = UC_percent;                                     //040715
   bool record_created = false;                                                  //050524
   return (float64) database_file->set_value(cloud_cover_percent,time_qry,actual_units,attribute,cloud_cover_creation,record_created,override_set_safety);
}
//_set_cloud_cover_percent__________________________________________1999-04-24_/
float64 Weather_UED_database::set_isothermal_longwave_net_radiation
(const CORN::Date_const &date_time_,float64 isothermal_longwave_net_radiation  ,CORN::Quality &attribute)
{  UED::Time_query_single_date time_qry(date_time_.get_datetime64(),(UED_units_code)UT_day);
   UED_units_code actual_units = UC_MJ_per_m2;                                   //040715
   bool record_created = false;                                                  //050524
   return (float64) database_file->set_value(isothermal_longwave_net_radiation,time_qry,actual_units,attribute,isothermal_longwave_net_radiation_creation,record_created,override_set_safety);
}
//_set_isothermal_longwave_net_radiation____________________________2007-02-03_/
float64 Weather_UED_database::set_net_radiation
(const CORN::Date_const &date_time_,float64 net_radiation  ,CORN::Quality &attribute)
{  UED::Time_query_single_date time_qry(date_time_.get_datetime64(),(UED_units_code)UT_day);
   UED_units_code actual_units = UC_MJ_per_m2;                                   //040715
   bool record_created = false;                                                  //050524
   return (float64) database_file->set_value(net_radiation,time_qry,actual_units,attribute,net_radiation_creation,record_created,override_set_safety);
}
//_set_net_radiation________________________________________________2007-02-03_/
// ued database doesnt use the average Rel Humix
void Weather_UED_database::set_precipitation_intervals_mm
(const CORN::Date_const &date_
,const CORN::Time &time_                                                        //990505
,const CORN::Dynamic_array<float32> &precip_in_intervals
,CORN::Minutes interval_time_minutes // For time step                            //990425
,CORN::Quality & attribute)
{  nat32 interval_count = precip_in_intervals.get_count();
   bool record_created;                                                          //000405
   Storm_event_creation_layout creation_layout(Storm_event_UED_record_type_form1,UC_mm,UT_0_minutes + interval_time_minutes,attribute.get_quality_code());   //050415
   CORN::Date_time_clad_64 starting_date_time(date_.get_date32(),time_.get_seconds());
   CORN::Time_second_clad ending_time(time_);                                    //170825
   ending_time.
      //170427 plus_minutes
      inc_minutes
      ((CORN::Minutes)(interval_time_minutes * interval_count));
   CORN::Date_time_clad_64 ending_date_time(date_.get_date32(),ending_time.get_seconds());
   //             There may already be 30minute precip generated, this new storm event
   //             might have more or less values old one in the file, so we will replace it.
   //             Warning, this is not save for real data in the database, we must do something different.
   //             to prevent unexpected erase.

   UED::Time_search time_query(starting_date_time.get_datetime64(),starting_date_time.get_datetime64(),ending_date_time.get_datetime64(),UED::Time_query::at);
   UED::Binary_data_record_cowl *interval_precip_record = database_file->locate_or_create_data_record(time_query,creation_layout,record_created);
   CORN::Dynamic_array<float32> &to_data =  interval_precip_record->ref_data_values();
   to_data.copy(precip_in_intervals);                                            //020201
}
//_set_precipitation_intervals_mm___________________________________1999-04-24_/
Storm_event_data_record *Weather_UED_database::get_precipitation_intervals_mm
(const CORN::Date_const &_date
,CORN::Minutes _desired_interval_time_minutes // For time step                   //990425
,CORN::Quality & attribute)
{
//This method returns the daily precipitation in intervals with the specified interval duration
//with the specified interval

//if there are no precipitation records with the specified iterval (I.e. 30 minutes)
//the scan the database for shorter intervals (I.e. 15, 10, and 5 minutes)
//and if any of those are found, then use those and sum the values.

   Storm_event_data_record *storm_event = 0;
   CORN::Date_time_clad_64 starting_date_time(_date.get_date32(),0);
   CORN::Date_time_clad_64 ending_date_time(_date.get_date32(),86400-1);
   UED::Time_search time_query(starting_date_time.get_datetime64(),starting_date_time.get_datetime64(),ending_date_time.get_datetime64(),UED_QUERY_ANY_TIME_STEP,UED::Time_query::between);

               // storm events
//              for each 5 minutes of the specified date starting from hour 0, query for a precipitation record
//                 with that starting time. (it should not have a day or greater time step)
//                 These records can be either full (sparce datasets starting at hour 0)
//                 or consolidated storm events  that may start at any arbitrary time.
//                 This procedure with handle both options.
    bool record_created;
    // First try 1 storm events
    UED::Binary_data_record_cowl *interval_precip_record
    =    database_file->locate_data_record
         (Storm_event_UED_record_type_form1
         ,UED::STD_VC_precipitation.get()
         ,time_query);                                                           //990118
    if (!interval_precip_record)
       interval_precip_record
      =    database_file->locate_data_record
         (Storm_event_UED_record_type_form2
         ,UED::STD_VC_precipitation.get()
         ,time_query);                                                           //990118
    if (interval_precip_record)
    {  // we found an storm event in the database
       // Instanciate return Storm_event_data_record this will be relinquished
       // to the caller who will be responsible for deleting it.
       storm_event = new Storm_event_data_record(interval_precip_record->get_code(),UC_mm,UT_0_minutes+_desired_interval_time_minutes,attribute.get_quality_code());
       // Determine the actual stored interval by looking at the data records time step
       Units_code act_stored_interval = interval_precip_record->get_time_step_units_code();
       Minutes act_interval_minutes = act_stored_interval - UT_0_minutes;
       // need to make sure the time stamp matches the existing record.
       storm_event->set_time_stamp(interval_precip_record->get_time_stamp());
       int act_intervals = 1440/act_interval_minutes;
       int desired_intervals = 1440 / _desired_interval_time_minutes;
       if  (act_stored_interval >= UT_0_minutes+ _desired_interval_time_minutes)
       {
          // The stored intervals are longer that the desired intervals  (I.e. hour instead of half hour)
          // we will simply divide the precipitation in to the respective
          // number of intervals (this is a rough estimate)
          // we should mark the quality (I.e. estimated) but
          // this will be used for ClimGen parameter generation so we will give it
          // the same quality (should make too much difference).

          // Simply copy the interval record
          // This only makes sense if the stored interval is a multiple of the desired interval
          // which should normally be the case, but this should work event if it isn't
          float32 divide_by  =  act_interval_minutes / _desired_interval_time_minutes;
          for (nat16 desired_i = 0; desired_i < desired_intervals;desired_i++)
          {  int act_i = (int)(desired_i / divide_by);
             CORN::Quality_clad quality;
             float32 act_value = interval_precip_record->get_at(act_i,quality);
             act_value /= divide_by; // convert the value to this time step
             // divide_by will be 1 if they have the same time step
             storm_event->set_at(desired_i,act_value,quality,false);
          }
       } else  // the actual interval length is
       {  // sorter than the desired (I.e.  15 minute instead of 30)
          // Note this only really works if the actual
          // is a even division of the desired time interval
          Dynamic_array<float32>combined_values(act_intervals,act_intervals,0);  //120804
          for (int act_i = 0; act_i < act_intervals; act_i++)
          {
//                    for each of the intervals add the value into the respective interval
//                    in the storm_event_data_record to be returned.
//                    (I.e. if the desired interval is 30 minutes and the actual interval
//                    is 15 minutes, then every pairs of intervals will be added to one desired interval).
            float32 divide_by  =  _desired_interval_time_minutes / act_interval_minutes;
            int desired_i = act_i/ divide_by;
            float32 curr = combined_values.get(desired_i);
            CORN::Quality_clad quality;
            float32 act_value = interval_precip_record->get_at(act_i,quality);
            curr += act_value;
            combined_values.set(desired_i,curr);
         };
         for (uint16 des_i = 0; des_i < desired_intervals; des_i++)
         {  CORN::Quality_clad quality;
            storm_event->set_at(des_i,combined_values.get(des_i),quality,true);
         }
      }
   }
   //  else
   // none found there must not have been a storm event on this day interval_precip_record
   //storm_event remains 0
   return storm_event;
}
//_get_precipitation_intervals_mm___________________________________2005-04-15_/
void Weather_UED_database::take_geolocation_information(UED::Geolocation_record *loc_rec)
{  database_file->take_geolocation_record(loc_rec);
}
//_take_geolocation_information_____________________________________2010-01-05_/
void Weather_UED_database::set_temperature_intervals
(const CORN::Date_const &date_                                                   //021124
,const Dynamic_array<float32> &temperature_in_intervals                          //120806_021124
,CORN::Minutes interval_time_minutes                                             //990425
,CORN::Quality &attribute)
{  nat32 interval_count = temperature_in_intervals.get_count();
   bool record_created;                                                          //000405
   UED::Data_record_creation_layout creation_layout
    (UED::Record_type_distinguisher_interface::UED_data_set_date_time_var_units // currently this is a single file dedicated to one variable
    ,UED::STD_VC_obs_temperature.get()
    ,UC_Celcius
    ,UT_0_minutes + interval_time_minutes
    ,UT_arbitrary_datetime
    ,attribute.get_quality_code());
   // Determine the period to be stored by the data record.
    CORN::Date_time_clad_64 starting_date_time(date_.get_date32(),0);            //030713
    CORN::Time_second_clad  ending_time((Hour)1440);                             //170825
    CORN::Date_time_clad_64 ending_date_time(date_.get_date32(),ending_time.get_seconds()); //030713
    UED::Time_search time_query(starting_date_time.get_datetime64(),starting_date_time.get_datetime64(),ending_date_time.get_datetime64(),UT_day,UED::Time_query::at);
    UED::Binary_data_record_cowl *detailed_temperature_record = database_file->locate_or_create_data_record(time_query,creation_layout,record_created);
    Dynamic_array<float32> &to_data =  detailed_temperature_record->ref_data_values(); //120806
    to_data.copy(temperature_in_intervals);                                      //020201
}
//_set_temperature_intervals________________________________________1999-04-24_/
#if (CS_VERSION==4)
bool Weather_UED_database::is_key_string(const std::string &key)      affirmation_  //180820
      { return ref_database_file().get_file_name() == key; }

/*180820  was probably only used for find_cstr now using is_key

const char  *Weather_UED_database::get_key()                               const
{ return ref_database_file()
      .get_file_name();
}
*/
#else
bool Weather_UED_database::is_key_wstring(const std::wstring &key)              affirmation_  //180820
      {
         static std::wstring name_wide;
         CORN::ASCIIZ_to_wstring(ref_database_file()
            .get_file_name(),name_wide);
         return name_wide == key;
      }

/*180820  was probably only used for find_cstr now using is_key

const wchar_t  *Weather_UED_database::get_key_wide()                       const
{  static std::wstring name_wide;
   CORN::ASCIIZ_to_wstring(ref_database_file()
      .get_file_name(),name_wide);
   return name_wide.c_str();
}
*/
#endif

//_get_key__________________________________________________________2013-04-06_/
bool Weather_UED_database::done_with_dates_before
(const CORN::Date_const &earliest_date)
{
   return database_file->done_with_dates_before(earliest_date);
}
//_done_with_dates_before___________________________________________2014-11-03_/
bool Weather_UED_database::get_parameter_on
(modifiable_ CS::Parameter &parameter
,nat32                      variable_code // Typically the variable code will be UED variable code
,const CORN::Date_const    &on_date)                              rectification_
{
   UED::Time_query_single_date time_qry(on_date.get_datetime64(),(UED_units_code)UT_day);
   return database_file->get_parameter_on
      (parameter
      ,variable_code
      ,time_qry
      ,UED::Record_type_distinguisher_interface::UED_data_set_year_var_units);
}
//_get_parameter_on_________________________________________________2015-11-19_/
/*151122 conceptual
bool Weather_UED_database::setup_parameter_reference
(modifiable_ CS::Parameter_cowl &parameter
,nat32                     variable_code // Typically the variable code will be UED variable code
,const CORN::Date         &on_date)                               rectification_
{
   UED::Time_query_single_date time_qry(on_date,(UED_units_code)UT_day);
   return database_file->setup_property_reference
      (property
      ,variable_code
      ,time_qry
      ,UED::Record_type_distinguisher_interface::UED_data_set_year_var_units);
}
*/
//_2015-11-19___________________________________________________________________

