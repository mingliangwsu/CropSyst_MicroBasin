#include <UED/convert/NCDC/NCDC_NOAA_global_surface_summary_of_the_day_convertor.h>
#include <UED/convert/station_database.h>
#include <corn/string/uiostring.h>
#include <UED/library/timeqry.h>
#include <corn/measure/measures.h>
#include <corn/math/compare.hpp>
using namespace std;
/*

REFERENCE

The NCDC Climate Services Branch (CSB) is responsible for
distribution of NCDC products to users.  NCDC's CSB can be
contacted via the following phone number, internet address, or
fax number.

Telephone Number:   828-271-4800
Fax Number:         828-271-4876
Internet Address:   ncdc.orders@noaa.gov

*/

/* Sample lines

After 2006 Aug 24 (version 7)
STN--- WBAN   YEARMODA    TEMP       DEWP      SLP        STP       VISIB      WDSP     MXSPD   GUST    MAX     MIN   PRCP   SNDP   FRSHTT
802590 99999  19860101    75.6 16    62.8 16  9999.9  0   905.1  6    8.5 16    4.6 16   14.0  999.9    84.6    64.0   0.00C 999.9  000000
802590 99999  19860102    73.6 20    62.9 20  9999.9  0   903.7  5    8.1 20    5.6 20   12.0  999.9    86.0*   62.4   0.00C 999.9  000000
This is the space delimited form
STN--- WBAN   YEARMODA    TEMP       DEWP      SLP        STP       VISIB      WDSP     MXSPD   GUST    MAX     MIN   PRCP   SNDP   FRSHTT
404620 99999  19740916    88.7  4    69.8  4  1003.9  4  9999.9  0    7.9  4    2.2  4    8.9  999.9    96.8*   84.2*  0.00I 999.9  000000
404620 99999  19750305    69.1  5    56.8  5  1014.8  5  9999.9  0    9.5  5    7.0  5    9.9  999.9    75.2    66.2   0.00I 999.9  000000
This is the comma delimited form
STN---,WBAN , YEARMODA,   TEMP,  ,   DEWP,  ,  SLP  ,  ,  STP  ,  , VISIB,  ,  WDSP,  , MXSPD,  GUST,   MAX  ,  MIN  ,PRCP  ,SNDP , FRSHTT,
727826,24141, 19420101,    9.0,16,   -2.5,16, 9999.9, 0, 9999.9, 0,  99.4,16,   3.6,16,   9.9, 999.9,   17.4*,   2.5*, 0.00I,999.9, 000000,
727826,24141, 19420102,   14.3,24,    2.3,24, 9999.9, 0, 9999.9, 0,  99.4,24,   3.2,24,   5.1, 999.9,   18.3*,   9.3*, 0.00I,999.9, 000000,


*/
//______________________________________________________________________________
#pragma pack(1)
struct NCDC_NOAA_global_surface_summary_of_the_day_format_V7
{  // Note that this format has two spaces filler before most values
   // and 1 space before the space filled 2 digit counts.
   // These spaces are included here in the field size since the the spaces should normally be ignored by the parser.

   char  WMO_STN[6];    char  delimA;    // WMO_DATSAV3_station_number
   char  WBAN[5];			char  delimB[2]; // The WBAN (Weather Bureau Air Force Navy) number was added in version 7
   char  YEAR[4];       // year
   char  MO[2];         // month
   char  DA[2];         // day of month
                        char  delimC;
   char  TEMP[7];       char  delimD;     // Mean temperature. Missing = 9999.9    (Fahrenheit to tenths or Celsius to tenths )
   char  TEMP_count[2]; char  delimE;     // Number of observations used in calculating mean temperature.
   char  DEWP[7];       char  delimF;     // Mean dew point for the day in degrees. Missing = 9999.9
   char  DEWP_count[2]; char  delimG;     // Number of observations used in calculating mean dew point.
   char  SLP[7];        char  delimH;     // Mean sea level pressure for the day in millibars to tenths.  Missing = 9999.9
   char  SLP_count[2];  char  delimI;     // Number of observations used in calculating mean sea level pressure.
   char  STP[7];        char  delimJ;     // Mean station pressure for the day in millibars to tenths.  Missing = 9999.9
   char  STP_count[2];  char  delimK;     // Number of observations used in calculating mean station pressure.
   char  VISIB[6];      char  delimL;     // Mean visibility for the day in miles to tenths.  Missing = 999.9 (Kilometers to tenths for metric version.)
   char  VISIB_count[2];char  delimM;     // Number of observations used in calculating mean visibility.
   char  WDSP[6];       char  delimN;     // Mean wind speed for the day in knots to tenths.  Missing = 999.9 (Meters/second to tenths for metric version.)
   char  WDSP_count[2]; char  delimO;     // Number of observations used in calculating mean wind speed.
   char  MXSPD[6];      char  delimP;     // Maximum sustained wind speed reported for the day in knots to tenths. Missing = 999.9 (Meters/second to tenths for metric version.)
   char  GUST[6];       char  delimQ;     // Maximum wind gust reported for the day in knots to tenths.  Missing = 999.9 (Meters/second to tenths for metric version.)
   char  MAX[7];                          // Maximum temperature reported during the day in Fahrenheit to tenths--time of max temp report varies by country and region, so this will sometimes not be the max for the calendar day.  Missing = 9999.9 (Celsius to tenths for metric version.)
   char  MAX_flag;      char  delimR;     // Blank indicates max temp was taken from the explicit max temp report and not from the 'hourly' data.  * indicates max temp was derived from the hourly data (i.e., highest hourly or synoptic-reported temperature).
   char  MIN[6];        // Minimum temperature reported during the day in Fahrenheit to tenths--time of min temp report varies by country and region, so this will sometimes not be the min for the calendar day.  Missing = 9999.9 (Celsius to tenths for metric version.)
   char  MIN_flag;      char  delimS;     // Blank indicates min temp was taken from the explicit min temp report and not from the 'hourly' data.  * indicates min temp was derived from the hourly data (i.e., lowest hourly or synoptic-reported temperature).
   char  PRCP[5];       // Total precipitation (rain and/or melted snow)  Missing = 99.99 (For metric version, units = millimeters to tenths & missing = 999.9.)
   char  PRCP_flag;     char  delimT;
   /*                    PRCP flags
                         A = 1 report of 6-hour precipitation amount.
                         B = Summation of 2 reports of 6-hour precipitation amount.
                         C = Summation of 3 reports of 6-hour precipitation amount.
                         D = Summation of 4 reports of 6-hour precipitation amount.
                         E = 1 report of 12-hour precipitation amount.
                         F = Summation of 2 reports of 12-hour precipitation amount.
                         G = 1 report of 24-hour precipitation amount.
                         H = Station reported '0' as the amount for the day (eg, from 6-hour reports), but also reported at least one occurrence of precipitation in hourly observations--this could indicate a trace occurred, but should be considered as incomplete data for the day.
                         I = Station did not report any precip data for the day and did not report any occurrences of precipitation in its hourly observations--it's still possible that precip occurred but was not reported.
   */
   char  SNDP[5];       char  delimU[2];        // Snow depth in inches to tenths--last report for the day if reported more than once.  Missing = 999.9 (Centimeters to tenths for metric version.) Note:  Most stations do not report '0' on days with no snow on the ground--therefore, '999.9' will often appear on these days.
   char  FRSHTT[6];     // Indicators
   /*                   Indicators (1 = yes, 0 = no/not reported) for the occurrence during the day of:
                         Fog ('F' - 1st digit).
                         Rain or Drizzle ('R' - 2nd digit).
                         Snow or Ice Pellets ('S' - 3rd digit).
                         Hail ('H' - 4th digit).
                         Thunder ('T' - 5th digit).
                         Tornado or Funnel Cloud ('T' - 6th digit).
   */
   char filler3;        // 090512 There may or may not be a trailing comma or white space.
};
//______________________________________________________________________________
/* Sample lines
Before 2006:    (I presume this was Version 6)
STN---  YEARMODA    TEMP       DEWP      SLP        STP       VISIB      WDSP     MXSPD   GUST    MAX     MIN   PRCP   SNDP   FRSHTT
010010  19950201    13.5  8     2.1  8   986.8  8   985.5  8    6.8  8   18.6  8   27.0  999.9    15.6*   12.0*   .01F 999.9  001000
010010  19950202    12.2  8    -1.2  8  1000.9  8   999.7  8   16.5  8    7.1  8    9.9  999.9    16.3*   10.4    .00F 999.9  001000
010010  19950203    23.9  8    21.1  8   986.1  8   984.9  8    2.8  8   26.8  8   35.9  999.9    27.3    11.1    .06F 999.9  001000
Note that there is also a comma delimited form
STN---, YEARMODA,   TEMP,  ,   DEWP,  ,  SLP  ,  ,  STP  ,  , VISIB,  ,  WDSP,  , MXSPD,  GUST,   MAX  ,  MIN  ,PRCP  ,SNDP , FRSHTT,
010010, 19950202,   12.2, 8,   -1.2, 8, 1000.9, 8,  999.7, 8,  16.5, 8,   7.1, 8,   9.9, 999.9,   16.3*,  10.4*,  .00F,999.9, 001000,
010010, 19950203,   23.9, 8,   21.1, 8,  986.1, 8,  984.9, 8,   2.8, 8,  26.8, 8,  35.9, 999.9,   27.3 ,  11.1 ,  .06F,999.9, 001000,
*/
struct NCDC_NOAA_global_surface_summary_of_the_day_format_V6
{  // Note that this format has two spaces filler before most values
   // and 1 space before the space filled 2 digit counts.
   // These spaces are included here in the field size since the the spaces should normally be ignored by the parser.

   char  STN[6];        char  delimA;   // WMO_DATSAV3_station_number
                        char  fillerA;
   char  YEAR[4];       // year
   char  MO[2];         // month
   char  DA[2];         // day of month
                        char  delimB;
   char  TEMP[7];       char  delimC;  // Mean temperature. Missing = 9999.9    (Fahrenheit to tenths or Celsius to tenths )
   char  TEMP_count[2]; char  delimD;  // Number of observations used in calculating mean temperature.
   char  DEWP[7];       char  delimE;  // Mean dew point for the day in degrees. Missing = 9999.9
   char  DEWP_count[2]; char  delimF;  // Number of observations used in calculating mean dew point.
   char  SLP[7];        char  delimG;  // Mean sea level pressure for the day in millibars to tenths.  Missing = 9999.9
   char  SLP_count[2];  char  delimH;  // Number of observations used in calculating mean sea level pressure.
   char  STP[7];        char  delimI;  // Mean station pressure for the day in millibars to tenths.  Missing = 9999.9
   char  STP_count[2];  char  delimJ;  // Number of observations used in calculating mean station pressure.
   char  VISIB[6];      char  delimK;  // Mean visibility for the day in miles to tenths.  Missing = 999.9 (Kilometers to tenths for metric version.)
   char  VISIB_count[2];char  delimL;  // Number of observations used in calculating mean visibility.
   char  WDSP[6];       char  delimM;  // Mean wind speed for the day in knots to tenths.  Missing = 999.9 (Meters/second to tenths for metric version.)
   char  WDSP_count[2]; char  delimN;  // Number of observations used in calculating mean wind speed.
   char  MXSPD[6];      char  delimO;  // Maximum sustained wind speed reported for the day in knots to tenths. Missing = 999.9 (Meters/second to tenths for metric version.)
   char  GUST[6];       char  delimP;  // Maximum wind gust reported for the day in knots to tenths.  Missing = 999.9 (Meters/second to tenths for metric version.)
   char  MAX[7];                       // Maximum temperature reported during the day in Fahrenheit to tenths--time of max temp report varies by country and region, so this will sometimes not be the max for the calendar day.  Missing = 9999.9 (Celsius to tenths for metric version.)
   char  MAX_flag;      char  delimR;  // Blank indicates max temp was taken from the explicit max temp report and not from the 'hourly' data.  * indicates max temp was derived from the hourly data (i.e., highest hourly or synoptic-reported temperature).
   char  MIN[6];                       // Minimum temperature reported during the day in Fahrenheit to tenths--time of min temp report varies by country and region, so this will sometimes not be the min for the calendar day.  Missing = 9999.9 (Celsius to tenths for metric version.)
   char  MIN_flag;      char  delimS;  // Blank indicates min temp was taken from the explicit min temp report and not from the 'hourly' data.  * indicates min temp was derived from the hourly data (i.e., lowest hourly or synoptic-reported temperature).
   char  PRCP[5];                      // Total precipitation (rain and/or melted snow)  Missing = 99.99 (For metric version, units = millimeters to tenths & missing = 999.9.)
   char  PRCP_flag;     char  delimT;
   /*                    PRCP flags
                         A = 1 report of 6-hour precipitation amount.
                         B = Summation of 2 reports of 6-hour precipitation amount.
                         C = Summation of 3 reports of 6-hour precipitation amount.
                         D = Summation of 4 reports of 6-hour precipitation amount.
                         E = 1 report of 12-hour precipitation amount.
                         F = Summation of 2 reports of 12-hour precipitation amount.
                         G = 1 report of 24-hour precipitation amount.
                         H = Station reported '0' as the amount for the day (eg, from 6-hour reports), but also reported at least one occurrence of precipitation in hourly observations--this could indicate a trace occurred, but should be considered as incomplete data for the day.
                         I = Station did not report any precip data for the day and did not report any occurrences of precipitation in its hourly observations--it's still possible that precip occurred but was not reported.
   */
   char  SNDP[5];       char delimU[2];// Snow depth in inches to tenths--last report for the day if reported more than once.  Missing = 999.9 (Centimeters to tenths for metric version.) Note:  Most stations do not report '0' on days with no snow on the ground--therefore, '999.9' will often appear on these days.
   char  FRSHTT[6];     char delimV;        // 090512 There may or may not be a trailing comma or white space.
   /* Indicators (1 = yes, 0 = no/not reported) for the occurrence during the day of:
                         Fog ('F' - 1st digit).
                         Rain or Drizzle ('R' - 2nd digit).
                         Snow or Ice Pellets ('S' - 3rd digit).
                         Hail ('H' - 4th digit).
                         Thunder ('T' - 5th digit).
                         Tornado or Funnel Cloud ('T' - 6th digit).
   */
};
#pragma pack()
//______________________________________________________________________________
void NCDC_NOAA_global_surface_summary_of_the_day_convertor::import_record_V6( NCDC_NOAA_global_surface_summary_of_the_day_format_V6 &element_record, CORN::OS::Directory_name &ued_file_path)
{
   element_record.delimA = 0; // Quick and dirty way to extract STN as null terminated string
   bool added_just_now = false;
   if (element_record.STN)
   {
      cout << "Invalid station number.  Geolocation lookup based on WBAN number is not yet implemented." << endl;
      // when the station number is 999999 I have no geolocation data in globalSOD_stnlist-sorted.txt
      // However for version 7 files we have the WBAN number which we can look up in the ISH-HISTORY.TXT
      // file.  I haven't bothered to read this file yet.
      return ;
   };

   Station_database *station_database = provide_station_database(CORN::Ustring(element_record.STN),added_just_now);



   // station_database guareented to be provided
   UED_indexed_database *ued_file = &(station_database->ued_file);
   // ued guareented.

   // The date is pack together 19950201
   // I read in this order clearing the buffer so that the next number can be
   // read without having to extract each substring.
   DOM   dom   = atoi(element_record.DA);    element_record.DA[0] = 0;
   Month month = atoi(element_record.MO);    element_record.MO[0] = 0;
   Year  year  = atoi(element_record.YEAR);

   CORN::Date record_date(year,month,dom);
   DOY record_doy = record_date.get_DOY();

cout << year << ' ' << element_record.STN << '\r';
   if ((year < parameters.year_earliest) || (year > parameters.year_latest))
      cout << year << " record year out of selected year range.\r";
   else
   {

   // NYI   TEMP   (average temperature can be calculated from min and max
   float32 mean_dew_point = atof(element_record.DEWP);   Units_code mean_dew_point_units = UC_celcius;      Quality mean_dew_point_smart_quality(measured_quality);
   // DEWP_count  not used
   // SLP         not imported
   // SLP_count   not used
   // STP         not imported
   // STP_count   not used
   // VISIB       not imported
   // VISIB_count not used
   float32 windspeed = atof(element_record.WDSP);        Units_code windspeed_units = UC_meters_per_second; Quality windspeed_smart_quality(measured_quality);
   // WDSP_count  not used
   // MXSPD       not imported
   // GUST        not imported
   float32 temperature_max = atof(element_record.MAX);   Units_code temperature_max_units = UC_celcius;     Quality temperature_max_smart_quality(measured_quality);
   // MAX_flag    not used
   float32 temperature_min = atof(element_record.MIN);   Units_code temperature_min_units = UC_celcius;     Quality temperature_min_smart_quality(measured_quality);
   // MIN_flag    not used
   float32 precipitation   = atof(element_record.PRCP);  Units_code precipitation_units = UC_mm;            Quality precipitation_smart_quality(measured_quality);
   // PRCP_flag   not used   (although I could set the trace marker)
   float32 snow_depth      = atof(element_record.SNDP);  Units_code snow_depth_units = UC_cm;               Quality snow_depth_smart_quality(measured_quality);
   // FRSHTT      not used  (current UED does not provide an indicator

   // Note that the metric and English  value quality marker may not be the same!
   if (!metric)
   {  // Convert to metric
      if (mean_dew_point   == 9999.9)  mean_dew_point_smart_quality  .set(missing_quality);  else mean_dew_point    = F_to_C(mean_dew_point);          //mean_dew_point_units    = UE_Farenheit;
      if (windspeed        ==  999.9)  windspeed_smart_quality       .set(missing_quality);  else windspeed         = knots_to_m_per_sec(windspeed);   //windspeed_units         = UE_knots;
      if (temperature_max  == 9999.9)  temperature_max_smart_quality .set(missing_quality);  else temperature_max   = F_to_C(temperature_max);         //temperature_max_units   = UE_Farenheit;
      if (temperature_min  == 9999.9)  temperature_min_smart_quality .set(missing_quality);  else temperature_min   = F_to_C(temperature_min);         //temperature_min_units   = UE_Farenheit;
      if (precipitation    ==   99.9)  precipitation_smart_quality   .set(missing_quality);  else precipitation     = inch_to_mm(precipitation);       //precipitation_units     = UE_inch_linear;
      if (snow_depth       ==  999.9)  snow_depth_smart_quality      .set(missing_quality);  else snow_depth        = inch_to_cm(snow_depth);          //snow_depth_units        = UE_inch_linear;
   }
   else
   {
      if (mean_dew_point   == 9999.9)  mean_dew_point_smart_quality  .set(missing_quality);
      if (windspeed        ==  999.9)  windspeed_smart_quality       .set(missing_quality);
      if (temperature_max  == 9999.9)  temperature_max_smart_quality .set(missing_quality);
      if (temperature_min  == 9999.9)  temperature_min_smart_quality .set(missing_quality);
      if (precipitation    ==  999.9)  precipitation_smart_quality   .set(missing_quality);
      if (snow_depth       ==  999.9)  snow_depth_smart_quality      .set(missing_quality);
   };
   Weather_validator *weather_data_validator = station_database->provide_weather_data_validator();
   if (weather_data_validator)
   {  // Double check data quality for erroneous data that has been marked valid
      CORN::Ustring validation_description;
      if (mean_dew_point_smart_quality .is_valid()) weather_data_validator->validate_float32(record_doy,mean_dew_point   ,avg_dew_point_temperature_creation .variable_code,mean_dew_point_units ,UT_day,CORN::measured_quality,CORN::measured_quality,mean_dew_point_smart_quality,validation_description);
      if (windspeed_smart_quality      .is_valid()) weather_data_validator->validate_float32(record_doy,windspeed        ,wind_speed_creation                .variable_code,windspeed_units      ,UT_day,CORN::measured_quality,CORN::measured_quality,windspeed_smart_quality,validation_description);
      if (temperature_max_smart_quality.is_valid()) weather_data_validator->validate_float32(record_doy,temperature_max  ,max_temperature_creation           .variable_code,temperature_max_units,UT_day,CORN::measured_quality,CORN::measured_quality,temperature_max_smart_quality,validation_description);
      if (temperature_min_smart_quality.is_valid()) weather_data_validator->validate_float32(record_doy,temperature_min  ,min_temperature_creation           .variable_code,temperature_min_units,UT_day,CORN::measured_quality,CORN::measured_quality,temperature_min_smart_quality,validation_description);
      if (precipitation_smart_quality  .is_valid()) weather_data_validator->validate_float32(record_doy,precipitation    ,precipitation_creation             .variable_code,precipitation_units  ,UT_day,CORN::measured_quality,CORN::measured_quality,precipitation_smart_quality,validation_description);
      if (snow_depth_smart_quality     .is_valid()) weather_data_validator->validate_float32(record_doy,snow_depth       ,snow_depth_creation                .variable_code,snow_depth_units     ,UT_day,CORN::measured_quality,CORN::measured_quality,snow_depth_smart_quality,validation_description);

/*091102
      if (mean_dew_point_smart_quality .is_valid()) mean_dew_point_smart_quality .set(weather_data_validator->validate_float32(record_doy,mean_dew_point   ,avg_dew_point_temperature_creation .variable_code,mean_dew_point_units ,UT_day,CORN::measured_quality,CORN::measured_quality));
      if (windspeed_smart_quality      .is_valid()) windspeed_smart_quality      .set(weather_data_validator->validate_float32(record_doy,windspeed        ,wind_speed_creation                .variable_code,windspeed_units      ,UT_day,CORN::measured_quality,CORN::measured_quality));
      if (temperature_max_smart_quality.is_valid()) temperature_max_smart_quality.set(weather_data_validator->validate_float32(record_doy,temperature_max  ,max_temperature_creation           .variable_code,temperature_max_units,UT_day,CORN::measured_quality,CORN::measured_quality));
      if (temperature_min_smart_quality.is_valid()) temperature_min_smart_quality.set(weather_data_validator->validate_float32(record_doy,temperature_min  ,min_temperature_creation           .variable_code,temperature_min_units,UT_day,CORN::measured_quality,CORN::measured_quality));
      if (precipitation_smart_quality  .is_valid()) precipitation_smart_quality  .set(weather_data_validator->validate_float32(record_doy,precipitation    ,precipitation_creation             .variable_code,precipitation_units  ,UT_day,CORN::measured_quality,CORN::measured_quality));
      if (snow_depth_smart_quality     .is_valid()) snow_depth_smart_quality     .set(weather_data_validator->validate_float32(record_doy,snow_depth       ,snow_depth_creation                .variable_code,snow_depth_units     ,UT_day,CORN::measured_quality,CORN::measured_quality));
*/
   };
   UED_time_query set_query(record_date.get_datetime64(),record_date.get_datetime64(),record_date.get_datetime64(),UED_time_query::at);
   bool created;  // to catch the result of set_values

   CORN::Quality mean_dew_point_quality  = mean_dew_point_smart_quality.get();
   CORN::Quality windspeed_quality       = windspeed_smart_quality.get();
   CORN::Quality temperature_max_quality = temperature_max_smart_quality.get();
   CORN::Quality temperature_min_quality = temperature_min_smart_quality.get();
   CORN::Quality precipitation_quality   = precipitation_smart_quality.get();
   CORN::Quality snow_depth_quality      = snow_depth_smart_quality.get();

   ued_file->set_value(mean_dew_point  ,set_query,mean_dew_point_units  ,mean_dew_point_quality ,avg_dew_point_temperature_creation,created);
   ued_file->set_value(windspeed       ,set_query,windspeed_units       ,windspeed_quality      ,wind_speed_creation               ,created);
   ued_file->set_value(temperature_max ,set_query,temperature_max_units ,temperature_max_quality,max_temperature_creation          ,created);
   ued_file->set_value(temperature_min ,set_query,temperature_min_units ,temperature_min_quality,min_temperature_creation          ,created);
   ued_file->set_value(precipitation   ,set_query,precipitation_units   ,precipitation_quality  ,precipitation_creation            ,created);
   ued_file->set_value(snow_depth      ,set_query,snow_depth_units      ,snow_depth_quality     ,snow_depth_creation               ,created);
//   ued_file->set_value(xxxxx_value      ,set_query,xxxx_units,xxx_quality,*XXXX_creation,created);
   };
};
//______________________________________________________________________________
void NCDC_NOAA_global_surface_summary_of_the_day_convertor::import_record_V7( NCDC_NOAA_global_surface_summary_of_the_day_format_V7 &element_record, CORN::OS::Directory_name &ued_file_path)
{
   element_record.delimA = 0; // Quick and dirty way to extract STN as null terminated string
   element_record.delimB[0] = 0;
   bool added_just_now = false;
   CORN::Ustring station_ID(element_record.WMO_STN);
   if (station_ID == "999999")
   {
      station_ID.assign(element_record.WBAN);
      all_known_weather_stations.set_reporting_agency(All_known_weather_stations::WBAN_REPORTING_AGENCY);
   }
   else
      all_known_weather_stations.set_reporting_agency(All_known_weather_stations::WMO_REPORTING_AGENCY);

   Station_database *station_database = provide_station_database
      (//100320 CORN::Ustring(element_record.STN)
       station_ID
      ,added_just_now);
   // station_database guareented to be provided
   // WBAN is not currently used
   UED_indexed_database *ued_file = &(station_database->ued_file);
   // ued guareented.

   // The date is pack together 19950201
   // I read in this order clearing the buffer so that the next number can be
   // read without having to extract each substring.
   DOM   dom   = atoi(element_record.DA);    element_record.DA[0] = 0;
   Month month = atoi(element_record.MO);    element_record.MO[0] = 0;
   Year  year  = atoi(element_record.YEAR);

   CORN::Date record_date(year,month,dom);
   DOY record_doy = record_date.get_DOY();

   cout << year << ' ' << element_record.WMO_STN <<' '<< element_record.WBAN << "                           \r";
   if ((year < parameters.year_earliest) || (year > parameters.year_latest))
      cout << year << " record year out of selected year range.\r";
   else
   {

   // NYI   TEMP   (average temperature can be calculated from min and max
   float32 mean_dew_point = atof(element_record.DEWP);   Units_code mean_dew_point_units = UC_celcius;      Quality mean_dew_point_smart_quality(measured_quality);
   // DEWP_count  not used
   // SLP         not imported
   // SLP_count   not used
   // STP         not imported
   // STP_count   not used
   // VISIB       not imported
   // VISIB_count not used
   float32 windspeed = atof(element_record.WDSP);        Units_code windspeed_units = UC_meters_per_second; Quality windspeed_smart_quality(measured_quality);
   // WDSP_count  not used
   // MXSPD       not imported
   // GUST        not imported
   float32 temperature_max = atof(element_record.MAX);   Units_code temperature_max_units = UC_celcius;     Quality temperature_max_smart_quality(measured_quality);
   // MAX_flag    not used
   float32 temperature_min = atof(element_record.MIN);   Units_code temperature_min_units = UC_celcius;     Quality temperature_min_smart_quality(measured_quality);
   // MIN_flag    not used
   float32 precipitation   = atof(element_record.PRCP);  Units_code precipitation_units = UC_mm;            Quality precipitation_smart_quality(measured_quality);
   // PRCP_flag   not used   (although I could set the trace marker)
   float32 snow_depth      = atof(element_record.SNDP);  Units_code snow_depth_units = UC_cm;               Quality snow_depth_smart_quality(measured_quality);
   // FRSHTT      not used  (current UED does not provide an indicator

   // Note that the metric and English  value quality marker may not be the same!
   if (!metric)
   {  // Convert to metric
      if (mean_dew_point > 9999.0)  mean_dew_point_smart_quality  .set(missing_quality);  else mean_dew_point    = F_to_C(mean_dew_point);          //mean_dew_point_units    = UE_Farenheit;
      if (windspeed      >  999.0)  windspeed_smart_quality       .set(missing_quality);  else windspeed         = knots_to_m_per_sec(windspeed);   //windspeed_units         = UE_knots;
      if (temperature_max> 9999.0)  temperature_max_smart_quality .set(missing_quality);  else temperature_max   = F_to_C(temperature_max);         //temperature_max_units   = UE_Farenheit;
      if (temperature_min> 9999.0)  temperature_min_smart_quality .set(missing_quality);  else temperature_min   = F_to_C(temperature_min);         //temperature_min_units   = UE_Farenheit;
      if (precipitation  >   99.0)  precipitation_smart_quality   .set(missing_quality);  else precipitation     = inch_to_mm(precipitation);       //precipitation_units     = UE_inch_linear;
      if (snow_depth     >  999.0)  snow_depth_smart_quality      .set(missing_quality);  else snow_depth        = inch_to_cm(snow_depth);          //snow_depth_units        = UE_inch_linear;

/*111129obs
      if (CORN::is_approximately<float32>(mean_dew_point   , 9999.9,0.001))  mean_dew_point_smart_quality  .set(missing_quality);  else mean_dew_point    = F_to_C(mean_dew_point);          //mean_dew_point_units    = UE_Farenheit;
      if (CORN::is_approximately<float32>(windspeed        ,  999.9,0.001))  windspeed_smart_quality       .set(missing_quality);  else windspeed         = knots_to_m_per_sec(windspeed);   //windspeed_units         = UE_knots;
      if (CORN::is_approximately<float32>(temperature_max  , 9999.9,0.001))  temperature_max_smart_quality .set(missing_quality);  else temperature_max   = F_to_C(temperature_max);         //temperature_max_units   = UE_Farenheit;
      if (CORN::is_approximately<float32>(temperature_min  , 9999.9,0.001))  temperature_min_smart_quality .set(missing_quality);  else temperature_min   = F_to_C(temperature_min);         //temperature_min_units   = UE_Farenheit;
      if (CORN::is_approximately<float32>(precipitation    ,   99.9,0.001)   precipitation_smart_quality   .set(missing_quality);  else precipitation     = inch_to_mm(precipitation);       //precipitation_units     = UE_inch_linear;
      if (CORN::is_approximately<float32>(snow_depth       ,  999.9,0.001))  snow_depth_smart_quality      .set(missing_quality);  else snow_depth        = inch_to_cm(snow_depth);          //snow_depth_units        = UE_inch_linear;
*/
   }
   else
   {
      if (mean_dew_point > 9999.0)  mean_dew_point_smart_quality  .set(missing_quality);
      if (windspeed      >  999.0)  windspeed_smart_quality       .set(missing_quality);
      if (temperature_max> 9999.0)  temperature_max_smart_quality .set(missing_quality);
      if (temperature_min> 9999.0)  temperature_min_smart_quality .set(missing_quality);
      if (precipitation  >   99.0)  precipitation_smart_quality   .set(missing_quality);
      if (snow_depth     >  999.0)  snow_depth_smart_quality      .set(missing_quality);

/*111129obs
      if (CORN::is_approximately<float32>(mean_dew_point   , 9999.9,0.001))  mean_dew_point_smart_quality  .set(missing_quality);
      if (CORN::is_approximately<float32>(windspeed        ,  999.9,0.001))  windspeed_smart_quality       .set(missing_quality);
      if (CORN::is_approximately<float32>(temperature_max  , 9999.9,0.001))  temperature_max_smart_quality .set(missing_quality);
      if (CORN::is_approximately<float32>(temperature_min  , 9999.9,0.001))  temperature_min_smart_quality .set(missing_quality);
      if (CORN::is_approximately<float32>(precipitation    ,  999.9,0.001))  precipitation_smart_quality   .set(missing_quality);
      if (CORN::is_approximately<float32>(snow_depth       ,  999.9,0.001))  snow_depth_smart_quality      .set(missing_quality);
*/

   };
   Weather_validator *weather_data_validator = station_database->provide_weather_data_validator();
   if (weather_data_validator)
   {  // Double check data quality for erroneous data that has been marked valid
      CORN::Ustring validation_description;
      if (mean_dew_point_smart_quality .is_valid()) weather_data_validator->validate_float32(record_doy,mean_dew_point   ,avg_dew_point_temperature_creation .variable_code,mean_dew_point_units ,UT_day,CORN::measured_quality,CORN::measured_quality,mean_dew_point_smart_quality    ,validation_description);
      if (windspeed_smart_quality      .is_valid()) weather_data_validator->validate_float32(record_doy,windspeed        ,wind_speed_creation                .variable_code,windspeed_units      ,UT_day,CORN::measured_quality,CORN::measured_quality,windspeed_smart_quality         ,validation_description);
      if (temperature_max_smart_quality.is_valid()) weather_data_validator->validate_float32(record_doy,temperature_max  ,max_temperature_creation           .variable_code,temperature_max_units,UT_day,CORN::measured_quality,CORN::measured_quality,temperature_max_smart_quality   ,validation_description);
      if (temperature_min_smart_quality.is_valid()) weather_data_validator->validate_float32(record_doy,temperature_min  ,min_temperature_creation           .variable_code,temperature_min_units,UT_day,CORN::measured_quality,CORN::measured_quality,temperature_min_smart_quality   ,validation_description);
      if (precipitation_smart_quality  .is_valid()) weather_data_validator->validate_float32(record_doy,precipitation    ,precipitation_creation             .variable_code,precipitation_units  ,UT_day,CORN::measured_quality,CORN::measured_quality,precipitation_smart_quality     ,validation_description);
      if (snow_depth_smart_quality     .is_valid()) weather_data_validator->validate_float32(record_doy,snow_depth       ,snow_depth_creation                .variable_code,snow_depth_units     ,UT_day,CORN::measured_quality,CORN::measured_quality,snow_depth_smart_quality        ,validation_description);
   };
   UED_time_query set_query(record_date.get_datetime64(),record_date.get_datetime64(),record_date.get_datetime64(),UED_time_query::at);
   bool created;  // to catch the result of set_values

   CORN::Quality mean_dew_point_quality  = mean_dew_point_smart_quality.get();
   CORN::Quality windspeed_quality       = windspeed_smart_quality.get();
   CORN::Quality temperature_max_quality = temperature_max_smart_quality.get();
   CORN::Quality temperature_min_quality = temperature_min_smart_quality.get();
   CORN::Quality precipitation_quality   = precipitation_smart_quality.get();
   CORN::Quality snow_depth_quality      = snow_depth_smart_quality.get();

   ued_file->set_value(mean_dew_point  ,set_query,mean_dew_point_units  ,mean_dew_point_quality ,avg_dew_point_temperature_creation,created);
   ued_file->set_value(windspeed       ,set_query,windspeed_units       ,windspeed_quality      ,wind_speed_creation               ,created);
   ued_file->set_value(temperature_max ,set_query,temperature_max_units ,temperature_max_quality,max_temperature_creation          ,created);
   ued_file->set_value(temperature_min ,set_query,temperature_min_units ,temperature_min_quality,min_temperature_creation          ,created);
   ued_file->set_value(precipitation   ,set_query,precipitation_units   ,precipitation_quality  ,precipitation_creation            ,created);
   ued_file->set_value(snow_depth      ,set_query,snow_depth_units      ,snow_depth_quality     ,snow_depth_creation               ,created);
//   ued_file->set_value(xxxxx_value      ,set_query,xxxx_units,xxx_quality,*XXXX_creation,created);
   };
};
//______________________________________________________________________________
nat32 NCDC_NOAA_global_surface_summary_of_the_day_convertor::perform_import()
{  nat32 records_imported = 0;
   nat32 records_read = 0;
   nat32 records_not_imported = 0;
   all_known_weather_stations.set_reporting_agency(All_known_weather_stations::WMO_REPORTING_AGENCY);

   // Open input file
   ifstream input_file(parameters.target_filename.c_str());
   NCDC_NOAA_global_surface_summary_of_the_day_format_V6 data_buffer_V6;
   NCDC_NOAA_global_surface_summary_of_the_day_format_V7 data_buffer_V7;
   int buffer_size_V6 = sizeof(data_buffer_V6);
   int buffer_size_V7 = sizeof(data_buffer_V7);
   cout << "Reading input file(s):" << endl;
   long buffer_read = 0;
   CORN::UIO_string buffer_str;
   buffer_str.read_line(input_file);   // Read the header line
   do
   {
      buffer_str.read_line(input_file);
		buffer_read = buffer_str.length(); // input_file.gcount();

      if (buffer_read > 6) // The line should have at least the station
      {
		char station[10];
      strncpy(station,buffer_str.c_str(),6);
      station[6] = 0;
      if (strcmp(station,"STN---") != 0)  // It appears that in some files, the header appears throughout the file
		{  CORN::Ustring station_IDs_filter(parameters.station_IDs_filter);
			if (  ( parameters.station_IDs_filter.length() == 0)
	             ||(station_IDs_filter/*parameters.station_IDs_filter.*/.contains(station))

	             ||(parameters.station_IDs_filter == "all")
	             ||(parameters.station_IDs_filter == "")
	             )
         {
		      if (   (buffer_read == buffer_size_V6)
                || (buffer_read == buffer_size_V6 -1)) // The file may or may not have trailing spaces
		      {
   				memcpy((char *)&data_buffer_V6,buffer_str.c_str(),buffer_size_V6);
		         import_record_V6(data_buffer_V6,*ued_file_path);  //051213  ued_file_path may be obsolete
		         records_imported++;
		      }
            else if (   (buffer_read == buffer_size_V7)
                     || (buffer_read == buffer_size_V7-1)) // The file may or may not have trailing spaces
		      {
               memcpy((char *)&data_buffer_V7,buffer_str.c_str(),buffer_size_V7);
		       	import_record_V7(data_buffer_V7,*ued_file_path);  //051213  ued_file_path may be obsolete
		         records_imported++;
		      } else 	records_not_imported ++;
         } else		records_not_imported ++;
      } else 			records_not_imported ++;
      } else records_not_imported++;
		records_read ++;

   } while ((buffer_read == buffer_size_V6) || (buffer_read == buffer_size_V7));
   cout << endl << "Writing UED files:" << endl;
   cout << "Records read    :" << records_read << endl;
   cout << "Records imported:" << records_imported << endl;
   cout << "Records not imported:" << records_not_imported << endl;
  return records_imported;
};
//______________________________________________________________________________
nat32 NCDC_NOAA_global_surface_summary_of_the_day_convertor::perform_export()
{
/* Not yet implemented
*/
   cerr << "Export for UED -> NCDC is not currently implemented. At this time there are no known programs that read this format." << endl;
   press_return_before_exit = true;
   return 0;
};
//______________________________________________________________________________
NCDC_NOAA_global_surface_summary_of_the_day_convertor::NCDC_NOAA_global_surface_summary_of_the_day_convertor(int argc,const char *argv[])
:UED_convertor(argc,argv)
{
   metric = (parameters.units_system == "metric") || (parameters.units_system == "Metric");
//   if (!metric)
//   {
//      if (parameters.subformat == "")
//   };
};
//______________________________________________________________________________

