#include "VIC_convertor.h"

#include "UED/convert/text_dBase_Excel_with_TDF/export.h"
#include "corn/data_source/vv_file.h"
#include "UED/library/UED_PCH.h"
#include "corn/string/uiostring.h"
#include "corn/container/SDF_list.h"
#include "UED/convert/station_database.h"
#include "common/weather/database/weather_UED_database.h"
#include "corn/format/binary/binary_file_fstream.h"
#include "VIC_forcing_reader.h"

using namespace UED;
//______________________________________________________________________________
VIC_convertor::VIC_convertor(int argc, const char *argv[])
:UED::Convertor(argc,argv)
{  parameters.geolocation_is_provided_by_caller=true;                            //080326
}
//______________________________________________________________________________
nat32 VIC_convertor::import_precip_tmax_tmin_wind
(ifstream &infile)
{  nat32 record_count = 0;
   CORN::Date record_date((Year)
      (parameters.date_time_earliest/1000)   // 1918  now 1960             080919
      ,(DOY)1);
   bool finished_importing_desired_years = false;                                //080610
   while (!infile.eof() && !finished_importing_desired_years)
   {  float32 precip;
      float32 tmax;
      float32 tmin;
      float32 wind;
      infile >> precip >> tmax >> tmin >> wind;
      CORN::Quality_clad value_quality(calculated_quality);
                  // I presume this data is from GCM
                  // I needed to use calculated quality because we later
                  // perform UED spatial interpolation and need to preserved this data a 'more real'
      std::cout << record_date.as_string() ;                                         //080326
      if ((record_date.get_year() >= parameters.year_earliest) && (record_date.get_year() <= parameters.year_latest)) //080326
      {
         bool override_safety = false;
         bool record_created  = false;
         UED::Time_query_single_date  time_query
               (record_date.get_datetime64(),UT_day,Time_query::at);

         CORN::Units_code precip_units = UC_mm;                                  //100914
         CORN::Units_code Tmax_units   = UC_Celcius;                             //100914
         CORN::Units_code Tmin_units   = UC_Celcius;                             //100914
         CORN::Units_code wind_units   = UC_meters_per_second;                   //100914

         value_quality.assume_code(calculated_quality); UED_file->set_value(precip  ,time_query ,precip_units  ,value_quality ,precipitation_creation    ,record_created   ,override_safety );
         value_quality.assume_code(calculated_quality); UED_file->set_value(tmax    ,time_query ,Tmax_units    ,value_quality ,max_temperature_creation  ,record_created   ,override_safety );
         value_quality.assume_code(calculated_quality); UED_file->set_value(tmin    ,time_query ,Tmin_units    ,value_quality ,min_temperature_creation  ,record_created   ,override_safety );
         value_quality.assume_code(calculated_quality); UED_file->set_value(wind    ,time_query ,wind_units    ,value_quality ,wind_speed_creation       ,record_created   ,override_safety );
      std::cout << " imported";                                                  //080326
      }                                                                         //080326
      std::cout << '\r';
      record_date.inc();
      record_count++;
      finished_importing_desired_years = (record_date.get_year() > parameters.year_latest);  //080610
   } // while !eof
   return record_count;
}
//______________________________________________________________________________
nat32 VIC_convertor::import_rad_relhumid_file(ifstream &infile)
{  nat32 record_count = 0;
#ifdef OBSOLETE
080616 The files as of June 3 do not have these header lines
   CORN::UIO_string header_line;
   for (int h = 0; h < 6; h++)
      header_line.read_line(infile);
               // currently there is always 6 header lines which we simply ignore
               // but there could eventually be more, they all start with # character
/*
# NRECS: 33603
# DT: 24
# STARTDATE: 1915-01-01 00:00:00
# ALMA_OUTPUT: 0
# NVARS: 3
# OUT_SHORTWAVE	 OUT_LONGWAVE	 OUT_REL_HUMID
*/
#endif
   CORN::Date record_date((Year)
      (parameters.date_time_earliest/1000) ,(DOY)1);   // 1918  now 1960         //080919

   while (!infile.eof())
   {
      int year;   CORN::UIO_string year_str;                                     //080910
      int month;  CORN::UIO_string month_str;                                    //080910
      int dom;    CORN::UIO_string dom_str;                                      //080910
      float32 incoming_longwave_radiation;   // Watt/m�                          //080910
      float32 incoming_shortwave_radiation;  // Watt/m�                          //080910
      float32 relative_humidity;             // percent                          //080910
      float32 vapor_pressure_deficit;         // kPa     (RLN: I don't know if this is daytime or full day (I think daytime

//080910          // The May 20th data set has a different format
//080910      float32 OUT_SHORTWAVE_W_m2;   // Watt/m�
//080910      float32 OUT_LONGWAVE_W_m2;    // Watt/m�
//080910      float32 OUT_REL_HUMID;        // percent
//080910      infile >> OUT_SHORTWAVE_W_m2 >> OUT_LONGWAVE_W_m2>> OUT_REL_HUMID;


      infile >> year_str >> month_str >> dom_str                                 //080910
         >> incoming_longwave_radiation                                          //080910
         >> incoming_shortwave_radiation                                         //080910
         >> relative_humidity                                                    //080910
         >> vapor_pressure_deficit;                                              //080910
                   year = atoi(year_str.c_str());
                   month = atoi(month_str.c_str());
                   dom  = atoi(dom_str.c_str());
       record_date.set_YMD((CORN::Year)year,(CORN::Month)month,(CORN::DOM)dom);  //080910

      std::cout << record_date.as_string();                                      //150307_080326
      if ((record_date.get_year() >= parameters.year_earliest) && (record_date.get_year() <= parameters.year_latest))   //080326
      {

      CORN::Quality_clad value_quality(calculated_quality);
                  // I presume this data is from GCM
                  // I needed to use calculated quality because we later
                  // perform UED spatial interpolation and need to preserved this data a 'more real'

      bool override_safety = false;
      bool record_created  = false;
      UED::Time_query_single_date  time_query
               (record_date.get_datetime64(),UT_day,Time_query::at);
      value_quality.assume_code(calculated_quality);
                  CORN::Units_code sortwave_rad_units = UC_watt_second_per_m2;
      float32 solar_rad_MJ_m2           // MJ/m�  Note that UED should automatically convert
         = UED_file->set_value(incoming_shortwave_radiation  ,time_query ,sortwave_rad_units ,value_quality ,solar_radiation_creation        ,record_created   ,override_safety );

      override_safety = false;
      record_created  = false;
#ifdef DISABLED
// 080916 the VPD data appears to be invalid
      value_quality = not_valid_quality; calculated_quality;
/*080610_*/       float32 VPD
         = UED_file->set_value(vapor_pressure_deficit  ,time_query ,UC_kPa ,value_quality ,avg_fullday_vapor_pressure_deficit_creation    ,record_created   ,override_safety );
#endif

                        // Warning need to check these units conversion.
//      value_quality = calculated_quality; UED_file->set_value(OUT_REL_HUMID    ,time_query ,UC_percent                   ,value_quality ,avg_relative_humidity_creation  ,record_created   ,override_safety );
         CORN::Units_code relative_humidity_units  = UC_percent;
         value_quality.assume_code(calculated_quality); UED_file->set_value(relative_humidity    ,time_query ,relative_humidity_units                   ,value_quality ,avg_relative_humidity_creation  ,record_created   ,override_safety ); //150307_080610
         std::cout << " imported";                                               //080326
      }
      std::cout << '\r';
      record_date.inc();
      record_count++;
   } // while !eof
   return record_count;
}
//_2008-03-03___________________________________________________________________
nat32 VIC_convertor::perform_import_binary()
{
   nat32 record_count = 0;
/*
FORCING1	bin_
GRID_DECIMAL	5	# Number of digits after decimal point in forcing file names
FORCE_FORMAT	BINARY
FORCE_ENDIAN	LITTLE
N_TYPES	4	# Number of variables (columns)
FORCE_TYPE	PREC	UNSIGNED	40
FORCE_TYPE	TMAX	SIGNED	100
FORCE_TYPE	TMIN	SIGNED	100
FORCE_TYPE	WIND	UNSIGNED	100
FORCE_TYPE	SHORTWAVE	UNSIGNED	100
FORCE_DT	24	# Forcing time step length (hours)
FORCEYEAR	1990	# Year of first forcing record
FORCEMONTH	1	# Month of first forcing record
FORCEDAY	1	# Day of first forcing record
FORCEHOUR	0	# Hour of first forcing record
WIND_H	2	# height of wind speed measurement (m)
MEASURE_H	2	# height of humidity measurement (m)
ALMA_INPUT	FALSE	# TRUE = ALMA-compliant input variable units; FALSE = standard VIC units
*/
   CORN::Date record_date((Year)1915,(DOY)1);
   bool finished_importing_desired_years = false;
   Binary_file_fstream  bin_file
   (
//   "C:\\Projects\\VIC\\validation\\weather\\othello\\data_46.78125_-119.03125",false); //Othello
//   "C:\\Projects\\VIC\\validation\\weather\\othello\\data_46.84375_-119.03125",false); //Othello
   "C:\\Projects\\VIC\\validation\\weather\\data_46.71875_-119.03125",false,(std::ios_base::in | std::ios_base::out)/*130401 false*/); //Othello
//   "C:\\Projects\\VIC\\validation\\weather\\data_46.71875_-119.03125",false); //Othello

   //"C:\\Projects\\VIC\\weather validation\\data_46.84375_-117.09375",false); // pullman
   //("C:\\Projects\\VIC\\weather validation\\thermal_time\\data_46.78125_-119.03125",false); //othello?
   while (!bin_file.at_eof() && !finished_importing_desired_years)
   {
      float32 precip;    CORN::Quality_clad precip_quality(calculated_quality);
      float32 tmax;      CORN::Quality_clad tmax_quality(calculated_quality);
      float32 tmin;      CORN::Quality_clad tmin_quality(calculated_quality);
      float32 wind;      CORN::Quality_clad wind_quality(calculated_quality);
      finished_importing_desired_years =!read_VIC_forcing_file_line
         (bin_file
         ,precip , precip_quality
         ,tmax   , tmax_quality
         ,tmin   , tmin_quality
         ,wind   , wind_quality);
      if (!finished_importing_desired_years)
      {
         if (  (record_date.get_year() >= parameters.year_earliest)
             &&(record_date.get_year() <= parameters.year_latest))
         {

         // I presume this data is from GCM
         // I needed to use calculated quality because we later
         // perform UED spatial interpolation and need to preserved this data a 'more real'
         CORN::Units_code precip_units = UC_mm;
         CORN::Units_code Tmax_units   = UC_Celcius;
         CORN::Units_code Tmin_units   = UC_Celcius;
         CORN::Units_code wind_units   = UC_meters_per_second;
         std::cout << record_date.as_string() ;
         bool override_safety = false;
         bool record_created  = false;
         UED::Time_query_single_date  time_query
         (record_date.get_datetime64(),UT_day,Time_query::at);
         CORN::Quality_clad value_quality(calculated_quality);
         value_quality.assume_code(calculated_quality); UED_file->set_value(precip  ,time_query ,precip_units  ,precip_quality ,precipitation_creation    ,record_created   ,override_safety );
         value_quality.assume_code(calculated_quality); UED_file->set_value(tmax    ,time_query ,Tmax_units    ,tmax_quality ,max_temperature_creation  ,record_created   ,override_safety );
         value_quality.assume_code(calculated_quality); UED_file->set_value(tmin    ,time_query ,Tmin_units    ,tmin_quality ,min_temperature_creation  ,record_created   ,override_safety );
         value_quality.assume_code(calculated_quality); UED_file->set_value(wind    ,time_query ,wind_units    ,wind_quality ,wind_speed_creation       ,record_created   ,override_safety );

std::cout <<'\t' << wind << std::endl;

         std::cout << '\r';
         record_date.inc();
         record_count++;
         finished_importing_desired_years = (record_date.get_year() > parameters.year_latest);
         }
      }
   } // while !eof
   return record_count;
};
//_2010-10-13___________________________________________________________________
bool VIC_convertor::read_VIC_forcing_file_line
(CORN::Binary_file_fstream  &bin_file // &std::ifstream &forcing_file
,float32 &precip_mm  , CORN::Quality &precip_quality
,float32 &tmax_C     , CORN::Quality &tmax_quality
,float32 &tmin_C     , CORN::Quality &tmin_quality
,float32 &wind_ms    , CORN::Quality &wind_quality)
{  bool success = false;

   // warning these format and scalings are acutally variable

   int16 precip_scaled_raw = bin_file.read_int16();
   int16 Tmax_scaled_raw   = bin_file.read_int16();
   int16 Tmin_scaled_raw   = bin_file.read_int16();
   int16 WS_scaled_raw     = bin_file.read_int16();

   if (precip_scaled_raw== 65536) precip_quality.assume_code(missing_quality);
   if (Tmax_scaled_raw  == 65536) tmax_quality.assume_code(missing_quality);
   if (Tmin_scaled_raw  == 65536) tmin_quality.assume_code(missing_quality);
   if (WS_scaled_raw    == 65536) wind_quality.assume_code(missing_quality);

   // warning the scalings should be taken from the global control file
   precip_mm         = (float32)precip_scaled_raw / 40.0;
   tmax_C            = (float32)Tmax_scaled_raw   /100.0;
   tmin_C            = (float32)Tmin_scaled_raw   /100.0;
   wind_ms           = (float32)WS_scaled_raw     /100.0;

   // warning Other elements are not currently implemented

   success = bin_file.good();
   return success;
}
//_2011-04-08___________________________________________________________________
nat32 VIC_convertor::perform_import_text(/*140527 now member of Convertor UED::Database_file_indexed &ued_file*/)
{  nat32 records_read = 0;
std::ifstream infile(parameters.target_filename.c_str());
#ifdef OBSOLETE
080616 UW keeps changing the format can count on this!
   CORN::UIO_string firstline;
   firstline.read_line(infile);
   bool is_rad_relhumid_file = firstline.length() > 30; // The additional forcings file with radiation is about 47 characters long. The historical data is about 27 character give or take
#endif
   bool is_rad_relhumid_file = parameters.format == "force";                     //080616_
//080610 The change the format removing the # comment/header lines.
//       Now I identify the file type by the line length.
//080610 (firstline.c_str()[0] == '#'); // Currently the rad_relhumid_file had header, precip_tmax_tmin_wind does not.
   if (is_rad_relhumid_file)
   {  infile.seekg(0,ios::beg);  // rewind();
      records_read = import_rad_relhumid_file(infile);
   }else
   {  infile.seekg(0,ios::beg);  // rewind();
      records_read = import_precip_tmax_tmin_wind(infile);
   }
   parameters.location_info_imported = true; // Actually geolocation was passed through response file on import.
   return records_read; // NYI
}
//_2008-03-03_____________________________________________________________________________
nat32 VIC_convertor::perform_import()
{

   // NYI need to open the VIC configuration file
   // to identify the format
   bool added_now = false;

   Station_database * station_database = provide_station_database_from_UED_filename(parameters.UED_filename,added_now);
      UED_file = &                                                               //140527
      station_database->ued_file;
   UED::Geolocation_record *geoloc_rec = new UED::Geolocation_record(parameters.geolocation);   //080326_
   UED_file->take_geolocation_record(geoloc_rec);                                 //080326_

   std::cout << "Currently the import reads only a specific fixed format\n"
             << "The format can actually be specified in the VIC Global configuration file\n"
             << "That options is currently not implemented.\n";

   bool format_is_binary = true;  // currently using the binary format

   return format_is_binary
      ? perform_import_binary()
      : perform_import_text();
}
//_2008-03-03___________________________________________________________________
nat32 VIC_convertor::perform_export()                                          //
{  nat32 records_written = 0;
   Weather_UED_database weather_DB(parameters.UED_filename.c_str(),(std::ios_base::in | std::ios_base::out)/*130401 false*/);
         // location_filename_to_provide_geolocation is used only by ClimGen.
         // when generating a new UED file we get the geolocation parameters    091117_

    //UED::Database_file_indexed &ued_file =  &weather_DB.get_database();
               const Geolocation         *geoloc = weather_DB.get_geolocation_constant();

   CORN::Datetime64 earliest_date_time =                                      //_970915
                  std::max<Datetime64>(weather_DB.get_earliest_date_time(),parameters.date_time_earliest);
               CORN::Date earliest_date(earliest_date_time);

   CORN::Datetime64 latest_date_time =                                        //_970915
                  std::min<Datetime64>(weather_DB.get_latest_date_time(),parameters.date_time_latest);

               CORN::Date latest_date(latest_date_time);

               ofstream global_control_file_forcing ("D:\\assist\\climgen\\kiran\\VIC.conf_forcing");

               global_control_file_forcing
                  << "FORCING1\t" << parameters.prefix <<std::endl
                  << "GRID_DECIMAL\t5\t# Number of digits after decimal point in forcing file names" <<std::endl;
               if (parameters.subformat == "binary")
               {  global_control_file_forcing
                  << "FORCE_FORMAT\tBINARY" << std::endl
                  << "FORCE_ENDIAN\tLITTLE" << std::endl ;
               } else
               {  global_control_file_forcing
                  << "FORCE_FORMAT\tASCII" << std::endl;
               }

               global_control_file_forcing
                  << "N_TYPES\t4\t# Number of variables (columns)" << std::endl;
               if (parameters.subformat == "binary")
               {  global_control_file_forcing
                  << "FORCE_TYPE\tPREC\tUNSIGNED\t40" << std::endl
                  << "FORCE_TYPE\tTMAX\tSIGNED\t100" << std::endl          // TMAX daily maximum temperature (C)
                  << "FORCE_TYPE\tTMIN\tSIGNED\t100" << std::endl          // TMIN daily minimum temperature (C)
                  << "FORCE_TYPE\tWIND\tUNSIGNED\t100" << std::endl        // PREC precipitation (mm)
                  << "FORCE_TYPE\tSHORTWAVE\tUNSIGNED\t100" << std::endl  ; // SHORTWAVE shortwave radiation (W/m2)
               }
               else
               {
                  global_control_file_forcing
                  << "FORCE_TYPE\tPREC" << std::endl
                  << "FORCE_TYPE\tTMAX" << std::endl          // TMAX daily maximum temperature (C)
                  << "FORCE_TYPE\tTMIN" << std::endl          // TMIN daily minimum temperature (C)
                  << "FORCE_TYPE\tWIND" << std::endl        // PREC precipitation (mm)
                  << "FORCE_TYPE\tSHORTWAVE" << std::endl ;  // SHORTWAVE shortwave radiation (W/m2)
               }
               global_control_file_forcing
                  // AIR_TEMP sub-daily air temperature (C)
                  // ALBEDO surface albedo (fraction)
                  // DENSITY atmospheric density (kg/m3)
                  // PRESSURE atmospheric pressure (kPa)
                  // VP atmospheric vapor pressure (kPa)
                  // WIND wind speed (m/s)
                  // SKIP
                  << "FORCE_DT\t24\t# Forcing time step length (hours)" << std::endl
                  << "FORCEYEAR\t"  << (int)earliest_date.get_year()  << "\t# Year of first forcing record" << std::endl
                  << "FORCEMONTH\t" << (int)earliest_date.get_month() << "\t# Month of first forcing record" << std::endl
                  << "FORCEDAY\t"   << (int)earliest_date.get_DOY()   << "\t# Day of first forcing record" << std::endl
                  << "FORCEHOUR\t0\t# Hour of first forcing record" << std::endl
                  << "WIND_H\t"     << (geoloc ? geoloc->get_screening_height() : 10.0) <<"\t# height of wind speed measurement (m)" << std::endl
                  << "MEASURE_H\t"  << (geoloc ? geoloc->get_screening_height() : 2.0)  <<"\t# height of humidity measurement (m)" << std::endl
                  << "ALMA_INPUT\tFALSE\t# TRUE = ALMA-compliant input variable units; FALSE = standard VIC units" << std::endl;
               // NYI

               std::string filename(parameters.prefix);
               filename.append(CORN::float32_to_cstr(geoloc->get_latitude_dec_deg_32(), 5));
               filename.append("_");
               filename.append(CORN::float32_to_cstr(geoloc->get_longitude_dec_deg_32(), 5));
               //150307 parameters.target_filename.set_name_ext(filename.c_str());
               CORN::OS::File_name_concrete target_filename_geolocated(parameters.target_filename,filename); //150307
               parameters.target_filename.set_DEN(target_filename_geolocated); //150307

               // Need to verify this new filename set works

               CORN::Binary_file_fstream VIC_weather
                  (parameters.target_filename.c_str(),false
                  ,std::ios_base::in | std::ios_base::out);                       //150307
                  // using in out to allow the file to be expanded

               // Format documentation for VIC model
               // http://www.hydro.washington.edu/Lettenmaier/Models/VIC/Documentation/ForcingData.shtml

               for (CORN::Date today(earliest_date); today.get() <= latest_date.get(); today.inc())
               {
                  CORN::Quality_clad Tmax_quality;
                  CORN::Quality_clad Tmin_quality;
                  CORN::Quality_clad Srad_quality;
                  CORN::Quality_clad precip_quality;
                  CORN::Quality_clad wind_quality;

                  float64 Tmax =  weather_DB.get_max_temperature(Tmax_quality,today);
                  float64 Tmin =  weather_DB.get_min_temperature(Tmin_quality,today);

                  int16 Tmax_scaled = (100.0 * Tmax);
                  int16 Tmin_scaled = (100.0 * Tmin);
                  /*150307
                  float64 Srad_MJ_m2 = weather_DB.get_solar_radiation            (Srad_quality,today);
                  float64 Srad_wattsec_m2 = Srad_MJ_m2 * 1000000.0 / 86400.0;
                  nat16   Srad_wattsec_m2_scaled =  (100.0 *Srad_wattsec_m2);
                  */

                  Solar_radiation Srad;                                          //150317
                  weather_DB.get_solar_radiation(Srad,today);                    //150317
                  //140307 float64 Srad_wattsec_m2 = Srad.get_MJ_m2() * 1000000.0 / 86400.0; //150317
                  float64 Srad_wattsec_m2 = Srad.get_wattsec_m2(); //150317
                  nat16   Srad_wattsec_m2_scaled =  (100.0 *Srad_wattsec_m2);


                  //float64 RHmax= scale * weather_DB.get_max_relative_humidity    (quality,today);
                  //float64 RHmin= weather_DB.get_min_relative_humidity    (quality,today);
                  float64 precip_mm=m_to_mm(weather_DB.get_precipitation_m           (precip_quality,today) );

                  nat16 precip_mm_scaled= 40.0 * precip_mm_scaled;
                  float64 WS_ms=  m_per_day_to_m_per_sec(weather_DB.get_wind_speed_m_d(wind_quality,today));

                  nat16 WS_ms_scaled= 100.0 * WS_ms;
                  //float64 xxx = scale *  weather_DB.get_max_dew_point_temperature  (quality,today);
                  //float64 xxx = scale *  weather_DB.get_min_dew_point_temperature  (quality,today);
                  //float64 xxx = scale *  weather_DB.get_avg_dew_point_temperature  (quality,today);
                  //float64 xxx = scale *  weather_DB.get_cloud_cover_percent        (quality,today);
                  //float64 xxx = scale *  weather_DB.get_isothermal_longwave_net_radiation(quality,today);
                  //float64 xxx = scale *  weather_DB.get_net_radiation              (quality,today);
                  //float64 xxx = scale *  weather_DB.get_pot_evapotranspiration_m   (quality,today);
                  //float64 xxx = scale *  weather_DB.get_avg_daytime_vapor_pressure_deficit_kPa  (quality,today);
                  //float64 xxx = scale *  weather_DB.get_avg_fullday_vapor_pressure_deficit_kPa  (quality,today);

                  if (!Tmax_quality.is_valid())    Tmax_scaled     = SHRT_MAX;
                  if (!Tmin_quality.is_valid())    Tmin_scaled     = SHRT_MIN;
                  if (!Srad_quality.is_valid())    Srad_wattsec_m2_scaled     = SHRT_MAX;
                  if (!precip_quality.is_valid())  precip_mm_scaled   = SHRT_MAX;
                  if (!wind_quality.is_valid())    WS_ms_scaled    = SHRT_MAX;

                  if (parameters.subformat == "binary")
                  {

                     VIC_weather.write_nat16(precip_mm_scaled);
                     VIC_weather.write_int16(Tmax_scaled);
                     VIC_weather.write_int16(Tmin_scaled);
                     VIC_weather.write_nat16(WS_ms_scaled);
                     VIC_weather.write_nat16(Srad_wattsec_m2_scaled);
                  }
                  else
                  {  std::iostream // 110828 fstream
                     &strm = VIC_weather.provide_stream();
                     strm
                     <<precip_mm   << ' '
                     << Tmax << ' '
                     << Tmin << ' '
                     << WS_ms << ' '
                     << Srad_wattsec_m2 << std::endl;
                  }
                  records_written++;
               }
   return records_written;
}
//_100914__________________________________________________________________
/*
The files are named according the lat long grid coordinates.
Currently data starts on 1915 Jan 1

There are two daily files:
one containing:
precip(mm)
tmax(degC)
tmin(degD)
wind(m/s)

The second
Dataset format is (daily): incoming_longwave_rad(W/m2) incoming_shortware_rad (W/m2) relhumidity(percent) - files contain 1-line header

# NRECS: 33603
# DT: 24
# STARTDATE: 1915-01-01 00:00:00
# ALMA_OUTPUT: 0
# NVARS: 3
# OUT_SHORTWAVE	 OUT_LONGWAVE	 OUT_REL_HUMID
101.2024	 201.5484	 65.2280
102.2599	 200.8288	 64.7015
*/
