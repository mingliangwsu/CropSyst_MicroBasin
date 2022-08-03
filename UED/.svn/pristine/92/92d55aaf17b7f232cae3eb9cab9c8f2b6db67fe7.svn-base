#include "UED/convert/APSIM/APSIM_convertor.h"
#include "UED/convert/station_database.h"
#include "UED/library/locrec.h"
#include "UED/library/timeqry.h"
#include "UED/library/std_codes.h"
#include "UED/library/database_file.h"
#include "common/weather/database/common_weather_creators.h"
#include "common/weather/parameter/WP_precipitation.h"
#include "common/weather/parameter/WP_air_temperature.h"
#include "common/weather/parameter/WP_solar_radiation.h"
#include <iomanip.h>
#include <ctype.h>

/* example format

APSIM format produced SILO  (may be an older format)
See
http://www.apsim.info/apsim/publish/Docs/shared/Apsim for apprentices.htm

[weather.input.weather]
!station number = 085000
!station name = ABERFELDY
!latitude = -37.70  (DECIMAL DEGREES)
!longitude = 146.37  (DECIMAL DEGREES)
!Data extracted from Silo on 10 , 2006
!As evaporation is read at 9am, it has been shifted to day before
!ie The evaporation measured on 20 April is in row for 19 April
!The 6 digit code indicates the source of the 6 data columns
!0 actual observation, 1 actual observation composite station
!2 daily raster, 7 long term average raster
!more detailed two digit codes are available
!
!For further information see the documentation on the datadrill
!  http://www.nrm.qld.gov.au/silo/datadril.html
!
Year  Day Radn  MaxT   MinT  Rain  Evap    VP   Code    // These may be upper or lower case
1889   1   22.0  19.0   7.5  37.9   4.0  11.0 777277
1889   2   23.0  19.0   7.5  65.6   4.0  11.0 777277


APSIM format documented by SILO

[weather.met.weather]
!Your Ref:  APSIM"
!latitude = -30.00  (DECIMAL DEGREES)
!longitude =  145.00  (DECIMAL DEGREES)
tav = 20.50 (oC) ! Annual average ambient temperature
amp = 17.94 (oC) ! Annual amplitude in mean monthly temperature
!As evaporation is read at 9am, it has been shifted to day before
!ie The evaporation measured on 20 April is in row for 19 April
!The 6 digit code indicates the source of the 6 data columns
!0 actual observation, 1 actual observation composite station
!2 interpolated from daily observations
!3 interpolated from daily observations using anomaly interpolation method for CLIMARC data
!7 interpolated long term averages
!more detailed two digit codes are available in SILO's 'Standard' format files
!
!For further information see the documentation on the datadrill
!  http://www.dnr.qld.gov.au/silo/datadril.html
!
year  day radn  maxt   mint  rain  evap    vp   code
 ()   () (mj/m2) (oC)  (oC)  (mm)  (mm) (hPa)     ()
1970   1   21.0  19.0  14.5   0.0   8.8   9.0 222222
1970   2   13.0  21.5  13.0   1.1   7.4  12.0 222222

APSIM met files may also have a column
site
  ()
CODE
where code is the location ID?

Presumable the columns can be in any order.

!--------------GAT9091.met-------------------
[weather.met.weather]
amp      =   15.0   (oC)       ! temperature amplitude (oC) - difference between
                               ! highest and lowest mean monthly air temperatures
tav      =   20.0   (oC)       ! mean annual air temperature (oC)
latitude =  -27.0   (decimal degrees north)
site year   day  radn   maxt   mint   rain    evap
  ()   ()    () (MJ/m2) (oC)   (oC)   (mm)    (mm)
GATT 1990     1 20.74   33.0   17.4    0.2    7.41
GATT 1990     2 23.43   33.8   23.0    0.0    7.41
GATT 1990     3 23.79   32.5   21.0    0.0    7.41
 "     "      "   "      "       "      "      "
GATT 1991   361 26.64   34.2   21.2    0.0    7.51
GATT 1991   362 26.56   31.4   16.4    0.0    7.51
GATT 1991   363 26.97   31.6   15.8    0.0    7.51
GATT 1991   364 26.79   31.2   15.6    0.0    7.51
GATT 1991   365 27.18   32.3   15.5    0.0    7.51
!--------end---GAT9091.met-------------------

The following is sample provided by Prakash Dixit
!Title  =       Katumani 1957-2004
[weather.met.weather]
!renamedfrom    kat_k.met
latitude=             -1(deg)
!       TAV     and     AMP     insertedon      10/6/200at         12:17for     period  from      Jan-86to      365/2002(ddd/yyyy)
   ! TAV and AMP inserted by "tav_amp" on 16/05/2008 at 20:08 for period from   1/1957 to 152/2004 (ddd/yyyy)
 tav =  19.12 (oC)     ! annual average ambient temperature
 amp =   4.19 (oC)     ! annual amplitude in mean monthly temperature

site    year    day     radn    maxt    mint    rain
()      ()      ()      (MJ/M2) (oC)    (oC)    (mm)
Katu        1988       1   24.56    28.5    16.0     0.0
Katu        1988       2   22.82    26.5    15.1     8.4
Katu        1988       3   18.99    25.2    15.4    20.5
Katu        1988       4   18.55    23.6    14.8     4.4
Katu        1988       5   22.72    24.5    14.1     5.8
Katu        1988       6   25.38    24.9    15.0     0.6
Katu        1988       7   25.04    26.1    14.7     6.6
Katu        1988       8   23.06    25.0    14.5     0.0
Katu        1988       9   25.19    26.3    15.0    29.3
Katu        1988      10   22.33    24.3    15.6     4.6
Katu        1988      11   25.96    26.0    15.1     0.0
Katu        1988      12   28.39    26.6    14.1     0.0
Katu        1988      13   26.79    26.5    13.3     0.0
Katu        1988      14   24.22    26.0    13.6     0.1
Katu        1988      15   26.40    26.7    15.3     0.5




*/
/* Reference

Agricultural Production Systems Research Unit (including SILO APSIM PPD format)

Jeffrey, S.J., Carter, J.O., Moodie, K.M and Beswick, A.R..
"Using spatial interpolation to construct a comprehensive archive of Australian climate data",
Environmental Modelling and Software, Vol 16/4, pp 309-330, 2001.
*/
//______________________________________________________________________________
APSIM_PPD_convertor::APSIM_PPD_convertor(int argc, const char *argv[])
: UED::Convertor(argc, argv)
, columns(0)
, site_col(256)
, year_col(256)
, doy_col (256)
, code_col(256)
, SILO_generated_data(false)
, first_element_column(0)
{
   for (int i = 0; i < 256; i++)
   {
      element_creator[i] = 0;
      element_units	[i] = 0;
   }
}
//______________________________________________________________________________
bool APSIM_PPD_convertor::is_data_line(const char *line) const
{
   bool is_data = true;
   if ((line[0] == '!') || (line[0] == 0)) is_data = false;
   else
   { 	int alpha_count = 0;
   	int digit_count = 0;
      for (int i = 0; i < strlen(line); i++)
      {  if (isalpha(line[i])) alpha_count += 1;
      	if (isdigit(line[i])) digit_count += 1;
      }
      is_data = digit_count > alpha_count;
   }
   return is_data;
}
//______________________________________________________________________________
bool APSIM_PPD_convertor::is_column_header_line(const char *line) const
{
   bool is_column_header = false;
   if (strstr(line,"year") && strstr(line,"day")) // probably should also check for a common element i.e. maxt
   	is_column_header = true;
   return is_column_header;
}
//______________________________________________________________________________
bool APSIM_PPD_convertor::is_units_line(const char *line) const
{
   bool is_units = true;
   if (strstr(line,"()"))
      is_units = true;
   return  is_units;
}
//______________________________________________________________________________
uint16 APSIM_PPD_convertor::identify_columns(const char *col_header_line)
{  uint16 col_count = 0;
   char curr_col_header[256];
   uint16 col_header_i = 0;
   uint16 col_i = 0;

   if (strstr(col_header_line,"code") != 0)   SILO_generated_data = true;
   for (uint16 i = 0; i<=strlen(col_header_line); i++)
   {  char char_i = col_header_line[i];
      if ((col_header_line[i] == ' ') || (col_header_line[i] == 0))
      {
         curr_col_header[col_header_i] = 0;
         col_header_i = 0;
         // Assuming case insenstive
         if (curr_col_header[0])
         {
              if (stricmp(curr_col_header,"site")==0) 	{site_col = col_i;                              				element_units[col_i] = 0;  }
         else if (stricmp(curr_col_header,"year")==0) 	{year_col = col_i;                              				element_units[col_i] = 0;  }
         else if (stricmp(curr_col_header,"day")==0) 		{doy_col  = col_i;                              				element_units[col_i] = 0;  }
         else if (stricmp(curr_col_header,"radn")==0) 	{element_creator[col_i] = &solar_radiation_creation; 							element_units[col_i] = UC_MJ_m2; 	}
         else if (stricmp(curr_col_header,"maxt")==0) 	{element_creator[col_i] = &max_temperature_creation; 							element_units[col_i] = UC_Celcius;  }
         else if (stricmp(curr_col_header,"mint")==0) 	{element_creator[col_i] = &min_temperature_creation; 							element_units[col_i] = UC_Celcius;  }
         else if (stricmp(curr_col_header,"rain")==0) 	{element_creator[col_i] = &precipitation_creation; 								element_units[col_i] = UC_mm;  		}
         else if (stricmp(curr_col_header,"evap")==0) 	{element_creator[col_i] = &pot_evapotranspiration_creation; 					element_units[col_i] = UC_mm;  		}
         else if (stricmp(curr_col_header,"vp")==0) 		{element_creator[col_i] = &avg_daytime_vapor_pressure_deficit_creation; 	element_units[col_i] = UC_hPa;  		}
         else if (stricmp(curr_col_header,"code")==0) 	{code_col = col_i; }
         if (!first_element_column && element_creator[col_i])
             first_element_column =  col_i;
             // This is for SILO files. I am assuming the site and date columns precede the data elements.
             // I am accomodating for the possability that SILO may in the future add data elements
             // and that the order of the SILO quality code indicators are in any same order as the data elements
         col_i++;
         col_count ++;
         }
      } else
      {
         curr_col_header[col_header_i++] = char_i;
      }
   }
   return col_count;
}
//______________________________________________________________________________
uint32 APSIM_PPD_convertor::perform_import()
{  uint32 record_count = 0;
   std::ifstream input_file(parameters.target_filename.c_str());
   std::cout << "Reading input file(s):" <<  parameters.target_filename << std::endl;
   // Presumably only one station per file
   long buffer_read = 0;
   std::string buffer_str;

   bool added_just_now = false;
   std::string station_ID;
   if (!station_ID.length())                                                  //110805
   {  // ICASA file may have multiple station weather data set in
         // a single file, in this case an ID will/should be provided for each
         // If not specified, assuming a single station in a single file
         // with the name of the file identifing the site.
         CORN::wstring_to_string(parameters.target_filename.get_name(),station_ID);
   }
   //140911    Station_database *station_database = provide_station_database(parameters.target_filename,added_just_now);
   Station_database *station_database = provide_station_database(station_ID,added_just_now);
   UED::Database_file_indexed *ued_file = &(station_database->ued_file);
   if (station_database) // should always be provided
   {
         UED_file = &(station_database->ued_file);                               //140527

   if (!input_file.eof())
   {  UED::Geolocation_record  *station_geolocation = ued_file->get_geolocation_record();
      bool already_has_station_geolocation = (bool)station_geolocation;
      if (!already_has_station_geolocation)
      {  // The UED doesn't already have geolocation so we will added it.
         station_geolocation = new UED::Geolocation_record;
      }
      getline(input_file,buffer_str);  // [weather.input.weather]     file type indicator?
      //140911 buffer_str.read_to_delim(input_file);  // [weather.input.weather]     file type indicator?

      std::string station_number;
      std::string station_name ;
      std::string latitude_str_dec_deg;
      std::string longitude_str_dec_deg;
      std::string latitude_str_deg_min;     //I.e. -26.97
      std::string longitude_str_deg_min;     //I.e. -26.97
      std::string data_source;
      float32 tav;
      float32 amp;

      uint32  file_pos = 0;
      bool at_data_line = false;
      do
      {  file_pos = input_file.tellg();
         getline(input_file,buffer_str);  // [weather.input.weather]     file type indicator?
         //140911 buffer_str.read_to_delim(input_file);
         const char *buffer_cstr = buffer_str.c_str();

         if (strncmp(buffer_cstr,"!station number" ,15) == 0)        station_number .assign(std::string(buffer_str,18));  // !station number = 085000
         if (strncmp(buffer_cstr,"!station name"   ,13) == 0)        station_name   .assign(std::string(buffer_str,19));  // !station name = ABERFELDY
         if (strncmp(buffer_cstr,"!latitude"       , 9) == 0)        latitude_str_dec_deg   .assign(std::string(buffer_str,12,9));//  !latitude = -37.70  (DECIMAL DEGREES)
         if (strncmp(buffer_cstr,"!longitude"      ,10) == 0)        longitude_str_dec_deg  .assign(std::string(buffer_str,12,7));// !longitude = 146.37  (DECIMAL DEGREES)
         if (strncmp(buffer_cstr,"latitude"        , 8) == 0)
            if (buffer_str.find("DECIMAL DEGREES") != std::string::npos)    // 070424 these may need to be find_substring
               latitude_str_dec_deg   .assign(std::string(buffer_str,11,8));//  !latitude = -37.70  (DECIMAL DEGREES)
            else
               latitude_str_deg_min   .assign(std::string(buffer_str,11,8));//  latitude = -26.97  (DEG.MIN)
         if (strncmp(buffer_cstr,"longitude"        , 8) == 0)
         {   if (buffer_str.find("DECIMAL DEGREES") != std::string::npos)  // 070424 these may need to be find_substring
               longitude_str_dec_deg   .assign(std::string(buffer_str,11,8));//  longitude_str_dec_deg = 146.37  (DECIMAL DEGREES)
            else
               longitude_str_deg_min   .assign(std::string(buffer_str,11,8));//  longitude_str_dec_deg = 146.37  (DEG.MIN)
         }

         if (strncmp(buffer_cstr,"tav"             , 3) == 0)        tav=atof(std::string(buffer_str,0,3).c_str());
         if (strncmp(buffer_cstr,"amp"             , 3) == 0)        amp=atof(std::string(buffer_str,0,3).c_str());
         // All other lines starting with ! are comment or unknown to this convertor.

         if (is_column_header_line(buffer_cstr))
         	   columns = identify_columns(buffer_cstr);
         if (is_units_line(buffer_cstr))
         {	// Note that the units line may be optional (only appears in later versions)
            // An any case the units appear to be fixed
            // and this line is probably only informational.
            // so currently we just eat it.
         	// set_units(buffer_cstr);
         }

         if (is_data_line(buffer_cstr))
         {  // This appears to be the data line, set the record pointer back to the beginning
            at_data_line=true;
            input_file.seekg(file_pos);
         }

      } while (!at_data_line);


         if (!already_has_station_geolocation)
         {
            // not provided          station_geolocation->set_elevation           (atof(xxx.c_str()));
            station_geolocation->set_country_code_ISO3166        (36);
            station_geolocation->set_country_name        ("Australia");
            if (latitude_str_dec_deg.length())  station_geolocation->set_latitude_dec_deg_32 (atof(latitude_str_dec_deg.c_str()));
            if (longitude_str_dec_deg.length()) station_geolocation->set_longitude_dec_deg_32(atof(longitude_str_dec_deg.c_str()));
            if (latitude_str_deg_min.length())
            {
               float32 latitude_deg_min = atof(latitude_str_deg_min.c_str());
//               float32 degree = (float32((int)latitude_deg_min);
               float32 latitude_dec_deg = latitude_deg_min;
               // Warning I am not sure what they mean by DEG.MIN,
               // it looks simply like Decimal degrees,
               // so I am not attempting a conversion here.
               station_geolocation->set_latitude_dec_deg_32(latitude_dec_deg);
            }
            if (longitude_str_deg_min.length())
            {
               float32 longitude_deg_min = atof(longitude_str_deg_min.c_str());
//               float32 degree = (float32((int)latitude_deg_min);
               float32 longitude_dec_deg = longitude_deg_min;
               // Warning I am not sure what they mean by DEG.MIN,
               // it looks simply like Decimal degrees,
               // so I am not attempting a conversion here.
               station_geolocation->set_longitude_dec_deg_32(longitude_dec_deg);
            }
            ued_file->take_geolocation_record(station_geolocation);
         }

//NYI      Weather_validator *weather_data_validator = station_database->provide_weather_data_validator();

      // The quality code applies only to files created by SILO
      // if there is no code field we assume measured data.
      Quality_clad /*_code*/ element_quality[256];
      for (int i = 0; i < 256; i++)
         element_quality[i].assume_code(CORN::measured_quality); // Assuming measured unless we detect SILO code field
      do
      {
         Year  year;
         DOY   doy;
         std::string code;
         std::string site;
         float64 value[256];
//obs now can be any order         input_file >> year >> doy >> Radn >> MaxT >> MinT >> Rain >> Evap >> VP >> Code;
/*
         float32 Radn = 0;   Quality_code &Radn_qual = quality[0]; Radn_qual = missing_quality;   Units_code  Radn_units = UC_MJ_m2;
         float32 MaxT = 0;   Quality_code &MaxT_qual = quality[1]; MaxT_qual = missing_quality;   Units_code  MaxT_units = UC_celcius;
         float32 MinT = 0;   Quality_code &MinT_qual = quality[2]; MinT_qual = missing_quality;   Units_code  MinT_units = UC_celcius;
         float32 Rain = 0;   Quality_code &Rain_qual = quality[3]; Rain_qual = missing_quality;   Units_code  Rain_units = UC_mm;
         float32 Evap = 0;   Quality_code &Evap_qual = quality[4]; Evap_qual = missing_quality;   Units_code  Evap_units = UC_mm;
         float32 VP   = 0;     Quality_code &VP_qual = quality[5]; VP_qual   = missing_quality;   Units_code  VP_units   = UC_hPa;

*/

         for (uint16 col = 0; col < columns; col++)
         {


                 if (col == site_col)	input_file >> site; // Assuming site is a code of contiguous characters terminated by a white space character (or end of line)
            else if (col == year_col)	input_file >> year;
            else if (col == doy_col)	input_file >> doy;
            else if (col == code_col)	input_file >> code; // Assuming the code is a contiguous set of characters terminated by a white space character (probably end of line for SILO output file)

            else if (element_creator[col] != NULL)
            { 	// the column is an identified data element
               input_file >> value[col];
            }
         }
         for (uint16 col = 0; col < columns; col++)
         {
            if (SILO_generated_data)
            {
               for (int i = 0; i < 6; i++)
               {
                  switch (code.c_str()[i])
                  {  case '0' : element_quality[first_element_column + i].assume_code(measured_quality); break;     // actual observation
                     // Not sure about the following
                     case '1' : element_quality[first_element_column + i].assume_code(interpolated_quality); break; // actual observation composite station
                     case '2' : element_quality[first_element_column + i].assume_code(interpolated_quality); break;     // daily raster interplated from daily observations
                     case '3' : element_quality[first_element_column + i].assume_code(other_real_quality); break;     //  interplated from daily observations using anomaly interpolatio method for CLIMARC data
                     case '7' : element_quality[first_element_column + i].assume_code(quality_generated_from(interpolated_quality)) /*quality_interpolated_from(forecasted_quality)*/ ; break;     // interpolated long term average raster
                  }
               }
            } // else we assume measured data

/* NYI
It appears that APSIM data is assumed to be valid
            if (UED_is_valid(Srad_qual))     Srad_qual   = weather_data_validator->validate(record_doy,Srad ,solar_radiation_creation.variable_code        ,Srad_units ,UT_day,file_qual,col_qual);
            if (UED_is_valid(Tmax_qual))     Tmax_qual   = weather_data_validator->validate(record_doy,Tmax ,max_temperature_creation.variable_code        ,Tmax_units ,UT_day,file_qual,col_qual);
            if (UED_is_valid(Tmin_qual))     Tmin_qual   = weather_data_validator->validate(record_doy,Tmin ,min_temperature_creation.variable_code        ,Tmin_units ,UT_day,file_qual,col_qual);
            if (UED_is_valid(Rain_qual))     Rain_qual = weather_data_validator->validate(record_doy,precip,precipitation_creation.variable_code         ,precip_units,UT_day,file_qual,col_qual);
            if (UED_is_valid(Evap_qual))     Evap_qual = weather_data_validator->validate(record_doy,precip,xxxx_creation.variable_code         ,precip_units,UT_day,file_qual,col_qual);
            if (UED_is_valid(VP_qual))       VP_qual = weather_data_validator->validate(record_doy,precip,xxxx_creation.variable_code         ,precip_units,UT_day,file_qual,col_qual);
*/

            if (year && doy && element_creator[col])
            {  bool created;
               CORN::Date record_date(year,doy);
               UED::Time_query set_query(record_date.get_datetime64(),record_date.get_datetime64(),record_date.get_datetime64(),UED::Time_query::at);
               if (element_quality[col].get_quality_code() != missing_quality)  ued_file->set_value(value[col]   ,set_query,element_units[col]     ,element_quality[col]   ,*element_creator[col]        ,created);
               record_count ++;
               std::cout << year << ' ' << doy << '\r';
            }
         }
      } while (!input_file.eof());
   }
   }
   std::cout << "Writing UED file:" << std::endl;
   return record_count;
}
//______________________________________________________________________________
nat32 APSIM_PPD_convertor::perform_export()
{  nat32 records_exported = 0;

   UED::Database_file_indexed UED_file(parameters.UED_filename.c_str(),std::ios::in,parameters.allow_16bit_floats_in_UED); //150307
   Geolocation *geoloc = UED_file.get_geolocation_record();
   if (!geoloc)
   {
      std::cerr << parameters.UED_filename << " has no geolocation meta information" << std::endl;
      geoloc = new Geolocation; // Providing dummy geolocation so we can proceed.
   }
//   CORN::Text_list descriptions; UED_file.get_descriptions(descriptions);  std::string description_str;  descriptions.string_items(description_str,'\t');
//   CORN::Text_list comments;     UED_file.get_comments(comments);          std::string comments_str;     comments    .string_items(comments_str,'\t');

   std::ofstream met_file(parameters.target_filename.c_str());

   std::string name;
   CORN::wstring_to_string(parameters.UED_filename.get_name(),name);

   float32 TAV;
   float32 AMP;
   calc_TAV_and_AMP(UED_file,parameters.year_earliest,parameters.year_latest,TAV, AMP);

   met_file << "[weather.input.weather]" <<std::endl;
   met_file << "! site: " << name << std::endl;
   met_file << std::fixed
      << "longitude = "
         <<std::setw(9)
         <<std::setprecision(3)
         << geoloc->get_longitude_dec_deg_32 () << std::endl
      << "latitude = "
         <<std::setw(9)
         << geoloc->get_latitude_dec_deg_32()
//         <<std::setw(6) <<std::setprecision(0)
//            << geoloc->get_elevation()
         << std::endl
      << "tav = "
         <<std::setw(6)<<std::setprecision(1)
         << TAV  << " (oC)"
         << std::endl
      << "amp = "
         <<std::setw(6)<<std::setprecision(1)
         << AMP  << " (oC)"
         << std::endl;
   met_file << "year day     radn     rain     maxt     mint"/*    Ddays*/ << std::endl;
   met_file << "()    () (MJ/m^2)     (mm)     (oC)     (oC)"/*    ()*/ << std::endl;

   CORN::Date earliest_date   = UED_file.get_earliest_date_time();
   CORN::Date latest_date     = UED_file.get_latest_date_time();

   Precipitation                             precipitation;
   Air_temperature_maximum                   air_temperature_max;
   Air_temperature_minimum                   air_temperature_min;
   Solar_radiation                           solar_radiation;

   for (CORN::Date date(earliest_date)
       ;date <= latest_date
       ;date.inc())
   {
      CORN::Year date_year = date.get_year();

      if ((date_year >= parameters.year_earliest) && (date_year <= parameters.year_latest))
      {
         precipitation           .invalidate();
         air_temperature_max     .invalidate();
         air_temperature_min     .invalidate();

         UED::Time_query_single_date time_qry(date.get_datetime64(),(UED_units_code)UT_day);
         bool override_set_safety = false;

         CORN::Quality_clad RAIN_quality    (CORN::measured_quality);
         CORN::Quality_clad TMAX_quality    (CORN::measured_quality);
         CORN::Quality_clad TMIN_quality    (CORN::measured_quality);
         CORN::Quality_clad SRAD_quality    (CORN::measured_quality);

         UED_units_code RAIN_units     = UC_mm;
         UED_units_code TMAX_units     = UC_Celcius;
         UED_units_code TMIN_units     = UC_Celcius;
         UED_units_code SRAD_units     = UC_MJ_per_m2;

         float32 tmax = UED_file.get_no_create
               (UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
               ,UED::STD_VC_max_temperature.get(),time_qry,TMAX_units,TMAX_quality);
         float32 tmin = UED_file.get_no_create
               (UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
               ,UED::STD_VC_min_temperature             .get()
               ,time_qry,TMIN_units,TMIN_quality);
         if (tmax < tmin)
         {  tmax += 0.1;
            tmin -= 0.1; //some models do not DSSAT does not accept Tmax and Tmin having same value.
//            air_temperature_max.set_Celcius(tmax,TMAX_quality);
//            air_temperature_min.set_Celcius(tmin,TMAX_quality);
         }
         precipitation.set_mm
            (UED_file.get_no_create
               (UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
               ,UED::STD_VC_precipitation.get()
               ,time_qry,RAIN_units,RAIN_quality)     ,RAIN_quality);
         air_temperature_max   .set_Celcius(tmax,TMAX_quality);
         air_temperature_min   .set_Celcius(tmin,TMIN_quality);
         solar_radiation       .set_MJ_m2  (UED_file.get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_solar_radiation_global      .get(),time_qry,SRAD_units,SRAD_quality)     ,SRAD_quality);

         if (!SRAD_quality.is_valid())
            solar_radiation       .set_MJ_m2  (UED_file.get_no_create(UED::Record_type_distinguisher_interface::UED_data_set_year_var_units ,UED::STD_VC_solar_radiation_ERRONEOUS      .get(),time_qry,SRAD_units,SRAD_quality)     ,SRAD_quality);
         CORN::DOY doy = date.get_DOY();
         met_file
            << date_year
            << std::setw(4) << (int)doy
            << std::setw(9) << std::setprecision(2)<< (solar_radiation            .is_valid() ? solar_radiation          .get_MJ_m2()   : -99)
            << std::setw(9) << std::setprecision(2)<< (precipitation              .is_valid() ? precipitation            .get_mm()      : -99)
            << std::setw(9) << std::setprecision(2)<< (air_temperature_max        .is_valid() ? air_temperature_max      .Celcius() : -99)
            << std::setw(9) << std::setprecision(2)<< (air_temperature_min        .is_valid() ? air_temperature_min      .Celcius() : -99)
            << std::endl;
         records_exported++;
      }
   }
   return records_exported;
}
//______________________________________________________________________________

