#include "UED/convert/convertor_weather.h"
#include "UED/convert/station_database.h"
#include "UED/convert/ED_tabular_format.h"
#include "UED/convert/text_dBase_Excel_with_TDF/import_column.h"
#include "UED/library/std_codes.h"
#include "UED/library/timeqry.h"
#include "UED/library/UED_codes.h"
#include "corn/container/SDF_list.h"
#include "common/weather/parameter/WP_air_temperature.h"
#include "ClimGen/source/GUI/setup.cpp"
#include "UED/library/locrec.h"
#include "corn/math/statistical/sample_cumulative_T.h"
#include "corn/OS/file_system_logical.h"
#include "corn/OS/file_system_engine.h"
#include "corn/tabular/delineated_datarec.h"
#include "corn/chronometry/date_time_64.h"

class Data_record_creation_layout;
namespace UED
{
//______________________________________________________________________________
Convertor_weather::Convertor_weather
(Convertor_arguments &arguments)                                                //170725
:Convertor
(arguments)                                                                      //170725
,Common_weather_creators(CORN::measured_quality)                                 //050419
,station_databases()
, stats_curr_date((Year)0,(DOY)0)                                                //050419
{}
//_2015-12-29___________________________________________________________________
Convertor_weather::~Convertor_weather()
{  FOR_EACH_IN(station_database,Station_database,station_databases,each_station_db)
      station_database->ued_file.finish();
   FOR_EACH_END(each_station_db)
}
//_2015-12-29___________________________________________________________________
bool Convertor_weather::setup_stations_from_response_UED_filenames()
{  bool loaded_any = false;
   bool added_now = false;
   UED_File_name single_ued_filename(parameters.UED_filename);
   provide_station_database_from_UED_filename(single_ued_filename,added_now);
   if (added_now) loaded_any = true;
   if (parameters.UED_filenames.length())
   {  // Automatically setup any listed UED files.
      CORN::SDF_List UED_filenames(parameters.UED_filenames.c_str());
      FOR_EACH_IN(ued_filename, /*180119 SDF_List::*/Item,  UED_filenames,each_UED_filename)
      {
         std::string ued_filename_raw; ued_filename->key_string(ued_filename_raw); //180119
         UED_File_name listed_UED_filename(ued_filename_raw.c_str());            //180119
         provide_station_database_from_UED_filename(listed_UED_filename,added_now);
         if (added_now) loaded_any = true;
      } FOR_EACH_END(each_UED_filename)
   }
   return loaded_any;
}
//_2008-01-08______________________setup_stations_from_response_UED_filenames__/
void Convertor_weather::notify_climgen()
{  setdown_climgen_options();
}
//_2009-08-27___________________________________________________________________
Geolocation *Convertor_weather::render_geolocation(const std::string &station_ID) const // renders
{  const Geolocation *known_geoloc = all_known_weather_stations.render_geolocation(station_ID);
   Geolocation *geoloc_copy =
      known_geoloc
      ? new Geolocation (*known_geoloc)
      : new Geolocation;
   // I am in the process of replacing all_known_weather_stations
   // because rarely are all weather stations needed in a particular program.
   // Instead derived convertors will implement render_geolocation
   return geoloc_copy;
}
//_2009-09-22___________________________________________________________________
Station_database *Convertor_weather::provide_station_database
(const std::string &station_ID,bool &added_now,const CORN::OS::File_name *known_UED_filename)
{  // Either retrieves a previoulsy openned UED file or
   // opens, or creates a new one as needed.
   // created is return value set to true if the database was added in memory now.
   if (station_ID.empty()) return 0;                                             //180309
   added_now = false;
   Station_database *station_database = (Station_database *)station_databases.find_string(station_ID);
   if (station_database)
   {  added_now = false;
   } else
   {  Geolocation *geoloc = render_geolocation(station_ID);                      //050501
      std::string station_name(geoloc?geoloc->get_station_name():station_ID);    //060117
      CORN::strip_string(station_name);                                          //140112
      /*170309 disabled communicating to import utility using ClimGen Settings


      CORN::OS::File_name_concrete composed_UED_file_name(ued_file_path,(parameters.use_station_name && station_name.length()? station_name : station_ID).c_str(),"UED"); //120214
      // May want to reimplement this.
      if (known_UED_filename)
         ClimGen_settings->recent_database.set_DEN(*known_UED_filename);
      else
         ClimGen_settings->recent_database.set_DEN(composed_UED_file_name);
      */
/*
      ClimGen_settings->recent_database.set_DEN
         ((known_UED_filename)
         ? *known_UED_filename
         : composed_UED_file_name);
*/
      station_database = new Station_database
         (station_ID,ClimGen_settings->recent_database.c_str()
         ,(std::ios_base::in | std::ios_base::out));                             //130322_090622
      station_databases.append(station_database);
      UED::Database_file_indexed *ued_file = &(station_database->ued_file);
      added_now = true;
      if (geoloc)                                                                //050501
      {  UED::Geolocation_record *ued_loc_rec = new UED::Geolocation_record(*geoloc); //050501
         ued_file->take_geolocation_record(ued_loc_rec);
         delete geoloc;                                                          //050501
      } else if (response_file_or_command_line_specified_geolocation_parameters  //090306
                  &&   (parameters.geolocation.has_geopolitical_names()          //090922
                    || parameters.geolocation.has_station_number()               //090922
                    || parameters.geolocation.has_station_ID_code()              //090922
                    || parameters.geolocation.has_station_name()                 //090922
                    || parameters.geolocation.has_geocoordinates()))             //090922
      {  // geolocation parameters were entered in the response file or on the command line  //090306
         UED::Geolocation_record *ued_loc_rec = new UED::Geolocation_record
            (parameters.geolocation);                                            //090306
         ued_file->take_geolocation_record(ued_loc_rec);                         //090306
      }                                                                          //090306
      ued_file->write_generating_application(get_version(),get_application_name()); //060729
   }
   return station_database;
}
//_2005?_____________________________________________provide_station_database__/
Station_database *Convertor_weather::provide_station_database_from_UED_filename
(const CORN::OS::File_name &known_UED_filename,bool &added_now)
{  std::string station_ID;
   CORN::wstring_to_string(known_UED_filename.get_name(),station_ID);
   return provide_station_database(station_ID.c_str(), added_now,&known_UED_filename);
}
//_2008-01-08______________________provide_station_database_from_UED_filename__/
bool Convertor_weather::done_with_station(const std::string &station_ID)   modification_
{  Station_database *done_station_database = dynamic_cast<Station_database *>
      (station_databases.find_string(station_ID));
   if (done_station_database)
      station_databases.remove(done_station_database);
   return done_station_database != 0;
}
//_2014-06-09___________________________________________________________________
#ifdef NYI
050419 currently this is done by  Text_dBase_Excel_with_TDF_convertor
as the file is imported
void Convertor_weather::calculate_daily_values()
{
               for each database
               scan the database for records where the time step is < 1 day.
               daily_record = locate or create for the respective day of the subday_record
UED_STD_VC_precipitation
UED_STD_VC_avg_temperature
UED_STD_VC_avg_relative_humidity
UED_STD_VC_solar_radiation
UED_STD_VC_wind_speed
UED_STD_VC_wind_direction
               if record is precip
                  sum the subday_values
               if record is avg air temperature get the max to tmax
               if record is avg_air temp get the min for tmin
               if record is rel_humid get the max for max rel humid
               if the record is rel_hum get the min for min rel humid
               if the record is solar radiation
                  for each value multiply by seconds in subday_record's time step
                  and divide by 1000000 to get MJ/m2
}
#endif
//______________________________________________________________________________
bool Convertor_weather::calc_TAV_and_AMP
(UED::Database_file_indexed &UED_file
,CORN::Year start_year
,CORN::Year stop_year
,float32 &TAV, float32 &AMP)
{  Air_temperature_maximum                   air_temperature_max;
   Air_temperature_minimum                   air_temperature_min;
   CORN::Date_clad_32 start_date((CORN::Year)start_year,1);
   CORN::Date_clad_32 stop_date ((CORN::Year)stop_year,365);
   CORN::Statistical_sample_cumulative<float32,float32> Tavg_avg[13]; // index 0 not used
   for (CORN::Date_clad_32 date(start_date)
       ;date <= stop_date
       ;date.inc_day())
   {  UED::Time_query_single_date time_qry(date.get_datetime64(),(UED_units_code)UT_day);
      air_temperature_max     .invalidate();
      air_temperature_min     .invalidate();
      CORN::Quality_clad TMAX_quality    (CORN::measured_quality);
      CORN::Quality_clad TMIN_quality    (CORN::measured_quality);
      UED_units_code TMAX_units     = UC_Celcius;
      UED_units_code TMIN_units     = UC_Celcius;
      air_temperature_max   .set_Celcius
         (UED_file.get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_max_temperature             .get(),time_qry,TMAX_units,TMAX_quality)
         ,TMAX_quality);
      air_temperature_min   .set_Celcius
         (UED_file.get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_min_temperature             .get(),time_qry,TMIN_units,TMIN_quality)
         ,TMIN_quality);
      float64 air_temperature_avg = (air_temperature_max + air_temperature_min) / 2.0;
      nat8 month = date.get_month();
      Tavg_avg[month].append(air_temperature_avg);
   }
   CORN::Statistical_sample_cumulative<float32,float32>Tavgs;
   for (int m = 1; m <= 12; m++)
      Tavgs.append(Tavg_avg[m].provide_arithmetic_mean());
   TAV = Tavgs.get_mean();
   float32 Tavgs_min = Tavgs.provide_min();
   float32 Tavgs_max = Tavgs.provide_max();
   AMP = Tavgs_max - Tavgs_min;
   return true;
}
//_2014-09-11__________________________________________________________________/
Atmospheric_CO2_change_recalibration *Convertor_weather::render_atmospheric_CO2_change
(const CORN::OS::Directory_name  &UED_filename
,const CORN::date32 /*180101 Date_const */         &today_ref)        rendition_
{  Atmospheric_CO2_change_recalibration *atmopheric_CO2_change = 0;
   CORN::OS::File_name *CO2_RCP_recalibration_filename = 0;
   std::string UED_filename_with_RCP(parameters.UED_filename.c_str());
   size_t RCP_pos = UED_filename_with_RCP.find("RCP");                           //150909
   if (RCP_pos != std::string::npos)
   {  std::string RCPxx(UED_filename_with_RCP,RCP_pos,5);
      // First check that the file is on the new NAS2 drive:
      CORN::OS::Directory_name_concrete *CO2_directory
         = new Directory_name_concrete("N:\\REACCH2\\Simulation\\Database\\Weather\\CO2",CORN::OS::directory_entry);
      if (!CORN::OS::file_system_engine.exists(*CO2_directory))
      {  //Now check the file on the old NAS1 drive
         delete CO2_directory;
         CO2_directory = new Directory_name_concrete("P:\\REACCH\\Simulation\\Database\\Weather\\CO2",CORN::OS::directory_entry);
         if (!CORN::OS::file_system_engine.exists(*CO2_directory))
         {  delete CO2_directory; CO2_directory = 0;
            std::clog << "Unable to find REACCH CO2 directory, not including RCP CO2." << std::endl;
         }
      }
      if (CO2_directory)
         CO2_RCP_recalibration_filename = new CORN::OS::Directory_name_concrete
            (*CO2_directory,RCPxx,"rcl",CORN::OS::directory_entry);
         // Presuming if the CO2 directory exists, so does the recalibration file.
      if (CO2_RCP_recalibration_filename)
      {  bool CO2_data_encountered = false;
         CORN::Date_clad_32 earliest_date   = UED_file->get_earliest_date_time();
         CORN::Date_clad_32 latest_date     = UED_file->get_latest_date_time();
         atmopheric_CO2_change = new Atmospheric_CO2_change_recalibration
            (CO2_RCP_recalibration_filename->c_str()   // CO2_recalibration_filename
            ,earliest_date
            ,latest_date
            ,today_ref
            ,350.0// initial_CO2_conc used for default absissa in the interpolation
            ,CO2_data_encountered);
         if (!CO2_data_encountered)
         {  delete atmopheric_CO2_change; atmopheric_CO2_change = 0; }
      }
   }
   return atmopheric_CO2_change;
}
//_2015-03-30___________________________________________________________________
float32 Convertor_weather::get_valid_element_amount
(const UED::Column_elements::Element *element
,CORN::Quality_clad  &identified_quality)                                  const
{  CORN::datetime64 detail_line_datetime = get_detail_line_datetime();           //140606
   CORN::Date_clad_32 validation_date(detail_line_datetime);                     //140606
   Weather_validator * weather_data_validator = provide_weather_data_validator();
   CORN::Quality_clad value_quality(measured_quality);
   bool                    record_created;
   CORN::Units_code        value_units(element->parameter.get_units());
   // now returned parameter CORN::Quality_clad  identified_quality;
   std::string             quality_description;
   float32 validated_amount =
      (weather_data_validator)
      ?  weather_data_validator->validate_float32
         (validation_date.get_DOY()
         ,(float32) element->parameter.in_prescribed_units()
         ,element->creation_layout.variable_code      // variable
         ,value_units // element->creation_layout.options.stored_units_code
         ,element->creation_layout.options.timestep_units_code
         ,CORN::measured_quality   // file_quality Actually should call a virtual function to get this
         ,CORN::measured_quality   // column_quality Actually should call a virtual function to get this
         ,identified_quality
         ,quality_description)
                  // <- NYI I should allow the user to specify the data quality in the TDF
      : (float32) element->parameter.in_prescribed_units();
   return validated_amount;
}
//_2015-12-29___________________________________________________________________
const Data_record_creation_layout                                                //160212
*Convertor_weather::get_recognized_creation_layout(UED::Variable_code variable_code)
{
   return find_recognized_creation(variable_code);
}
//_2016-02-12___________________________________get_recognized_creation_layout_/
bool Convertor_weather::is_import_data_record
(const Delineated_data_record &data_rec
,const ED_tabular_file_format &format
,const Bidirectional_list /*180101 Association_list*/ &import_columns
,const UED::Geolocation_record *header_identified_geolocation)     contribution_
{  std::string station_ID_filter(parameters.station_IDs_filter.c_str());
   std::string station_ID;                                                       //100614
   const char *station_ID_cstr = get_station_ID_from_data_record
      (data_rec
      ,format                                                                    //160212
      ,import_columns                                                            //160212
      ,station_ID);
   std::string station_ID_to_use;                                                //050526
   if (station_ID_cstr) // If there is still no station ID in the record then presume
       station_ID_to_use.assign(station_ID_cstr);
   else                   // the station ID specified as the station filter is the only station_ID
   {   if (station_ID_filter.length())
           station_ID_to_use.assign(station_ID_filter);
   }
   if (!station_ID_to_use.length())
   {  //    The station ID can also come from curr_geolocation record that may be indicated in header fields
      if (header_identified_geolocation)                                      //100116
      {  station_ID_to_use.assign(header_identified_geolocation->get_station_ID_code());
         if (!station_ID_to_use.length())  // if there was no ID in the geolocation info, try the name
              station_ID_to_use.assign(header_identified_geolocation->get_station_name());
      }
      else  // if still no station ID presume it is the target filename
         wstring_to_string(parameters.target_filename.get_name(),station_ID_to_use); //120413
   }
   return (!station_ID_filter.length() || (station_ID_filter == station_ID_to_use));
}
//_2016-02-12_____________________________________________is_import_data_record
UED::Database_file_indexed *Convertor_weather::provide_UED_file()
{  if (!UED_file)
   {  // At this point we have the station ID get the UED file from the convertor stations list
      bool added_now = false;
      std::string UED_or_station_ID(station_ID_to_use);                          //050426
      if (!UED_or_station_ID.length()) // If there is no station ID specified within the record or as a fielder,
         //Then presume the specified UED filename is the station ID.
          wstring_to_string(parameters.UED_filename.get_name(),UED_or_station_ID);
      Station_database *station_database = provide_station_database(UED_or_station_ID,added_now);  //050602
      if (UED_or_station_ID != last_encountered_station_ID)                      //140609
         done_with_station(last_encountered_station_ID);                         //140609
      UED_file = &station_database->ued_file;                                    //050602_140530
      last_encountered_station_ID = UED_or_station_ID;                           //140609
   }
   return UED_file;
}
//__2016-02-12__________________________________________________________________
const char *Convertor_weather::get_station_ID_from_data_record
(const CORN::Delineated_data_record &data_rec  // obsolete, should pass import_column
,const ED_tabular_file_format &format
,const Bidirectional_list /*180101 Association_list*/ &import_columns
,std::string &record_station_ID_result)                            contribution_
{  // May return 0 if station ID is not stored in the data record
   nat32  station_ID_or_name_column_num = format.ID_column_number_1based;     // first check if there is a station_ID_column specified
   if (!station_ID_or_name_column_num)
        station_ID_or_name_column_num = format.name_column_number_1based;  // if not check if there is a station_name specified
   if (station_ID_or_name_column_num)
   {
      nat32  column_index =  station_ID_or_name_column_num - 1; //  columns are 1 indexed, containers are 0 indexed
      Tabular_data_column  *station_ID_or_name_column = (Tabular_data_column  *)import_columns.get_at(column_index);
      if (station_ID_or_name_column)  // This should almost always be non 0
      {  // first try to get it as a string
         record_station_ID_result.assign(station_ID_or_name_column->value_string);
         if (record_station_ID_result.length() ==0 )                             //100614
         {
            CORN::append_int16_to_string(station_ID_or_name_column->value_int16, record_station_ID_result);//140922
         }
      }
   }
   else
   {   // The format doesn't specify which column has the station ID
      FOR_EACH_IN(data_column,Tabular_data_column ,import_columns,each_column)
      {
         switch (data_column->TC_layout.data_type_labeled.get()) // data_type)
         {
            case CORN::DT_string  : // character string
            {
            // Currently presume the first string field encountered is the
            // station ID (this is a weak supposition) but
            // it is better than nothing
            // hopefully the TDF file specifies the station ID column!
               if (record_station_ID_result.length() == 0)
                  record_station_ID_result.assign(data_column->value_string);
//NYN                      (could check if the column name or description has ID
//NYN                           in the string. taking only the first encounted
//NYN                           string column if there are none others with ID).
            } break;
         }
      } FOR_EACH_END(each_column)
   }
   return
      record_station_ID_result.length()                                          //100614_
      ? record_station_ID_result.c_str()                                         //100614_
      : 0;                                                                       //100614_
}
//__2016-02-12___________________________________________________________________
bool Convertor_weather::set_validated_elements
(const CORN::Date_time        &row_date_time
,CORN::Delineated_data_record &data_rec
,bool                          calculate_daily_values)
{  assert(station_database); // Station database should have been provided at this point
         Weather_validator *weather_data_validator = station_database->provide_weather_data_validator();  //050602
         // At this point geolocation should already be set
         char date_str_buffer[100];
         if ((stats_curr_date.get_date32() != row_date_time.get_date32()) && stats_curr_date.get_date32())
         {
            std::clog << stats_curr_date.as_string() << "   " << '\r'; // just a status output
            if (calculate_daily_values)                                          //050419
            {  // This presumes data records are in sequence
               //   save each of the following stats 050419
               UED::Time_query_single_date set_daily_time_query(stats_curr_date.get_datetime64()); //050404
               float32 daily_precipitation_mm= daily_precipitation_mm_stats      .sum();        CORN::Units_code precip_units = UC_mm;
               float32 daily_max_temperature = daily_avg_temperature_stats       .get_max();    CORN::Units_code Tmax_units = UC_Celcius;
               float32 daily_min_temperature = daily_avg_temperature_stats       .get_min();    CORN::Units_code Tmin_units = UC_Celcius;
               float32 daily_max_rel_humid   = daily_avg_relative_humidity_stats .get_max();    CORN::Units_code RHmax_units = UC_percent;
               float32 daily_min_rel_humid   = daily_avg_relative_humidity_stats .get_min();    CORN::Units_code RHmin_units = UC_percent;
               float32 daily_solar_rad_MJ_m2 = daily_solar_radiation_MJ_m2_stats .sum();        CORN::Units_code SRad_units = UC_MJ_m2;
               float32 daily_wind_speed_m_sec= daily_wind_speed_m_sec_stats      .get_mean();   CORN::Units_code windspeed_units = UC_meters_per_second;
               float32 daily_wind_direction  = daily_wind_direction_stats        .get_mean();   CORN::Units_code winddir_units = UC_degree_from_north;

               if (CORN::is_approximately<float32>(daily_max_temperature,daily_min_temperature,0.0001))
               {  daily_max_temperature += 0.1;
                  daily_min_temperature -= 0.1;
               }
               bool created = true; // set below
               if (daily_precipitation_mm_stats       .get_count()) UED_file->set_value(daily_precipitation_mm   ,set_daily_time_query,precip_units   ,daily_precipitation_attribute         ,precipitation_creation   ,created);
               if (daily_avg_temperature_stats        .get_count()){UED_file->set_value(daily_max_temperature    ,set_daily_time_query,Tmax_units     ,daily_avg_temperature_attribute       ,max_temperature_creation ,created);
                                                                    UED_file->set_value(daily_min_temperature    ,set_daily_time_query,Tmin_units     ,daily_avg_temperature_attribute       ,min_temperature_creation ,created);}
               if (daily_avg_relative_humidity_stats  .get_count()){UED_file->set_value(daily_max_rel_humid      ,set_daily_time_query,RHmax_units    ,daily_avg_relative_humidity_attribute ,avg_relative_humidity_creation   ,created);
                                                                    UED_file->set_value(daily_min_rel_humid      ,set_daily_time_query,RHmin_units    ,daily_avg_relative_humidity_attribute ,min_relative_humidity_creation   ,created);}
               if (daily_solar_radiation_MJ_m2_stats  .get_count()) UED_file->set_value(daily_solar_rad_MJ_m2    ,set_daily_time_query,SRad_units     ,daily_solar_radiation_attribute       ,solar_radiation_creation ,created);
               if (daily_wind_speed_m_sec_stats       .get_count()) UED_file->set_value(daily_wind_speed_m_sec   ,set_daily_time_query,windspeed_units,daily_wind_speed_attribute            ,wind_speed_creation      ,created);
               if (daily_wind_direction_stats         .get_count()) UED_file->set_value(daily_wind_direction     ,set_daily_time_query,winddir_units  ,daily_wind_direction_attribute        ,wind_direction_creation  ,created);

                  // NYI: min&max dewpt, daytime and full day VPD, snow depth, snowfall
                  daily_precipitation_mm_stats      .reset();
                  daily_avg_temperature_stats       .reset();
                  daily_avg_temperature_stats       .reset();
                  daily_avg_relative_humidity_stats .reset();
                  daily_avg_relative_humidity_stats .reset();
                  daily_solar_radiation_MJ_m2_stats .reset();
                  daily_wind_speed_m_sec_stats      .reset();
                  daily_wind_direction_stats        .reset();
            }
         }
         stats_curr_date.set_date32(row_date_time.get_date32());
         /*160212  This was a temporary hack to provide RHmax and or RHavg
                  This functionality moved to to ClimGen (or relative humidity calculators).

         float64 RHmax = 0.0; bool RHmax_provided = false;
         float64 RHmin = 0.0; bool RHmin_provided = false;
         float64 RHavg = 0.0; bool RHavg_provided = false;
   // Special RHmax calculation for Kwang-Hyung Kim [sospicy77@gmail.com]
   // this should actually be done in ClimGen
         */
         float64 act_hours_of_sunshine_in_day = 0.0;                             //100222
         bool all_data_values_zero = true;                                       //050802
         FOR_EACH_IN(data_column,Import_column ,data_rec.tabular_data_columns,each_column)  //050802
         {
               float32 value = data_column->get_value_as_float32();              //050802
               UED_variable_code variable= data_column->TFFC_layout.smart_variable_code.get();
               if (!CORN::is_approximately<float32>(value,0.0,0.000001))         //100602
               {  if  (variable> 0)
                     all_data_values_zero = false;
               }
               // in some cases the daily solar radiation may be                 //100220
               // given in Watt_hours
               // and may be the hourly average for the day.
               // In this case there must be an hour of sunshine specified for the day
               // and the values for solar radiation would be consistently about
               // 10 times less than potential global solar radiation.
               // So the solar radiation would need to be
               if (variable == UED_STD_VC_sunhours)
                  act_hours_of_sunshine_in_day = value;

               /*160212  This was a temporary hack to provide RHmax and or RHavg
                  This functionality moved to to ClimGen (or relative humidity calculators).
               switch (data_column->TFFC_layout.smart_variable_code.get())              //140610
               {
                  case UED_STD_VC_RHmax      : RHmax = value; RHmax_provided = true; break;
                  case UED_STD_VC_RHmin      : RHmin = value; RHmin_provided = true; break;
                  case UED_STD_VC_RHavg      : RHavg = value; RHavg_provided = true; break;
               }
               */
               #ifdef NYI
               //160212  I moved the validation here, but I haven't check this
               if (attribute.is_valid() && weather_data_validator) // preserve any invalid code already detected.
               {
                  // Note that the validator is geolocated at allocation.  050602
                  std::string quality_description_unused;                        //091210
                  weather_data_validator->validate_float32(row_date_time.get_DOY(),value,variable,units_in_target_file,format.detail_lines_delineation.time_step_units_enum.get()
                  ,CORN::measured_quality,CORN::measured_quality,attribute,quality_description_unused);  // <- NYI I should allow the user to specify the data quality in the TDF
               }
               if (variable == UED_STD_VC_SradAvgHrly)                           //100222
               {  if ((act_hours_of_sunshine_in_day > 0.0001)
                    && (!data_record_time_step_less_than_1_day))

                  {  // The input file has hours of sunshine, this is assumed to indicate that the hourly radiation is the average of the sunshine hour
                     value *= act_hours_of_sunshine_in_day;
                  }
                  else                                                           //100301
                  {  // otherwise assume it is the average of sunshine in a full 24 hour period
                     // although is possible that it is daylight hours,
                     // if that is the case we need to indicate so in the
                     // TDF file (I.e. have a different variable code (or units code)
                     // I.e. Watt-Hour/daylight hours
                     // Would need to calculate the daylight hours for the day of year
                     // (available in the weather classes).
                     value *= 24.0;
                  }
                  actual_set_creation_layout = &solar_radiation_creation;
                  units_in_target_file = UC_watt_hour_per_m2;
                  if ((value > 1) && ( value < 10000)) // just a quick and dirty validation because I don't yet have this in the validator
                     attribute.assume_code(CORN::measured_quality);
               }
               #endif
         } FOR_EACH_END(each_column)
   return true;
}
//__2016-02-12___________________________________________________________________
bool Convertor_weather::inject_calculated_values()
{
#ifdef NYI

Need to reimplement this
                  Units_code units_in_UED_file = data_column->creation_layout->options.stored_units_code; //050518
                  switch (data_column->creation_layout->variable_code)
                  {  case UED_STD_VC_precip    : daily_precipitation_mm_stats.append(value_set);       daily_precipitation_attribute         .assume(attribute);        break;
                     case UED_STD_VC_Tavg       : daily_avg_temperature_stats.append(value_set);       daily_avg_temperature_attribute       .assume(attribute);        break;
                     case UED_STD_VC_RHavg      : daily_avg_relative_humidity_stats.append(value_set); daily_avg_relative_humidity_attribute .assume(attribute);        break;
                     case UED_STD_VC_Srad       :
                     {
                        float32 solar_rad_MJ_m2 = 0.0;
                        daily_solar_radiation_attribute.assume(attribute);
                        if (UED_file->convert_with_time_step
                              (format.detail_lines_delineation.time_step_units_enum.get()
                              ,value_set, units_in_UED_file,UT_unit_time ,solar_rad_MJ_m2,  UC_MJ_m2  ))
                           daily_solar_radiation_MJ_m2_stats.append(solar_rad_MJ_m2);
                        else
                        {  press_return_before_exit = true;
                           cerr << "Unable to convert solar radiation units." << endl;
                        }
                     } break;
                     case UED_STD_VC_ws      : daily_wind_speed_m_sec_stats.append(value_set); daily_wind_speed_attribute     .assume ( attribute);        break;
                     case UED_STD_VC_WindDir : daily_wind_direction_stats.append(value_set);   daily_wind_direction_attribute .assume( attribute);        break;
                  } // switch variable_code
#endif
   return true;
}
//__2016-02-12___________________________________________________________________
Geolocation_record  *Convertor_weather::get_geolocation_record()
{  return station_database
      ? station_database->ued_file.Database_file::provide_geolocation_record()
      : 0;
}
//______________________________________________________________________________
} // namespace UED /

