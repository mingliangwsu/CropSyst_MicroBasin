#include "UED/convert/IRIMO/IRIMO_convertor.h"
#include "UED/convert/station_database.h"
#include "UED/library/locrec.h"
#include "UED/library/timeqry.h"
#include "corn/measure/measures.h"
using namespace std;

//______________________________________________________________________________
nat32 IRIMO_convertor::perform_import()
{  nat32 records_imported = 0;
   nat32 records_read = 0;
   // Open input file
   ifstream input_file(parameters.target_filename.c_str());

   cout << "Reading input file(s):" << endl;
   long buffer_read = 0;
   CORN::UIO_string buffer_str;
//   buffer_str.read_line(input_file);   // Read the header line
   do
   {
      if (!at_next_monthly_record)
         skip_to_next_monthly_record(input_file);
      if (at_next_monthly_record)
         records_read += read_monthly_record(input_file);
      // else at end of file or other condition.
   }
   while (!input_file.eof() && input_file.good());
   cout << endl << "Writing UED files:" << endl;
   cout << "Month records read    :" << records_read << endl;
   cout << "Month records imported:" << records_imported << endl;
  return records_imported;
}
//______________________________________________________________________________
IRIMO_convertor::IRIMO_Record_type IRIMO_convertor::read_month_record_header
(istream &input_file
,CORN::Ustring &station_ID
,Year &year ,Month &month)
{
/* The header always has the following format
1                                            ISLAMIC REPUBLIC OF IRAN
                                         METEOROLOGICAL ORGANIZATION (IRIMO)
 STATION KERMANSHAH
 LATITUDE   34  21  N                         DATA PROCESSING CENTER
 LONGITUDE  47   9  E
 ELEVATION  1318.6 MET.
                                             MONTH  JANUARY     YEAR 1996
                                   { One line of text unique to the record type }

*/
   std::stringbuffer_str;

   // The first line of the record is already read
   // 1 ... ISLAMIC REPUBLIC OF IRAN
   getline(input_file,buffer_str);  // read  METEOROLOGICAL ORGANIZATION (IRIMO)
//091212   buffer_str.read_line(input_file); // read  METEOROLOGICAL ORGANIZATION (IRIMO)
   getline(input_file,buffer_str); // read station line
   station_ID = buffer_str.substr(9); // station ID starts in char pos 9

   getline(input_file,buffer_str);   // read latitude line
   float latitude_degrees= atof(buffer_str.c_str()+10);
   float latitude_minutes= atof(buffer_str.c_str()+14);
   char  north_south= buffer_str.c_str()[20];
   if (north_south == 'S') latitude_degrees = -latitude_degrees;

   getline(input_file,buffer_str);   // read longitude line
   float longitude_degrees= atof(buffer_str.c_str()+10);
   float longitude_minutes= atof(buffer_str.c_str()+14);
   char  east_west= buffer_str.c_str()[20];
   if (east_west == 'W') longitude_degrees = -longitude_degrees;
   getline(input_file,buffer_str);   // read elevation line
   float elevation = atof(buffer_str.c_str()+11);
   // The units follow the elevation values, it is presumed always meters.
   // Setup Geolocation
   bool added_just_now = false;
   Station_database *station_database = provide_station_database(station_ID,added_just_now);
   // station_database guareented to be provided
   weather_data_validator = station_database->provide_weather_data_validator();
   ued_file = &(station_database->ued_file);
   // ued guareented.
   if (ued_file)
   {
      UED_geolocation_record  *station_geolocation = ued_file->get_geolocation_record();
      if (!station_geolocation)
      {  // The UED doesn't already have geolocation so we will added it.

         station_geolocation = new UED_geolocation_record;
         station_geolocation->set_elevation_meter           (elevation);
         station_geolocation->set_country_code_ISO3166(364);  // Iran
         station_geolocation->set_country_name        ("Iran");  // Presume Iran
               // Use ISO 3166 codes

         // NA station_geolocation->set_state_code          (state_number);
         // NA station_geolocation->set_state_name          (xxxxx);

         // NA station_geolocation->set_county_name         (string(COUNTY.strip()).c_str());
         // NA station_geolocation->set_station_ID_code     (xSTA_ID.c_str());
         station_geolocation->set_station_name        (station_ID.c_str());

         station_geolocation->set_latitude_DMS(latitude_degrees,latitude_minutes,0);
         station_geolocation->set_longitude_DMS(longitude_degrees,longitude_minutes,0);

         ued_file->take_geolocation_record(station_geolocation);
      }
   }
   //    read month and year line
   CORN::Ustring  month_name;
   input_file >> buffer_str >> month_name;
   input_file >> buffer_str >> year;
   for (uint8 m = 1; m<=12;m++)
      if (stricmp(month_name.c_str(),date_month_names[m]) == 0) month = m;
   getline(input_file,buffer_str);   // read record description line
   cout <<  station_ID << '\t' << year << '\t' << month_name << '\t' << buffer_str<< '\r';
   //determine month record type
   IRIMO_Record_type record_type = IRIMO_UNKNOWN_record_type;
   if      (buffer_str.find("HOURLY DDFF IN KNOT")                                        != CORN_npos) record_type = IRIMO_wind;   // 070424 these may need to be find_substring
   else if (buffer_str.find("HOURLY DRY BULB AND WET BULB TEMPERATURE")                   != CORN_npos) record_type = IRIMO_temperature;
   else if (buffer_str.find("HOURLY  RELATIVE HUMIDITY AND DAILY PRECIPITATION")          != CORN_npos) record_type = IRIMO_reletive_humidity_and_precipitation;
   else if (buffer_str.find("DAILY SOIL-TEMP., RADIATION (JULE), SUNSHINE & EVAPORATION") != CORN_npos) record_type = IRIMO_soil_temp_radiation_sunshine_evaporation;
   else if (buffer_str.find("HOURLY PRESSURE QFE AND QFF IN MILLIBAR")                    != CORN_npos) record_type = IRIMO_pressure;
   else if (buffer_str.find("HOURLY AMOUNT OF CLOUD(N) ,  PRESENT WEATHER(WW) ,  VV")     != CORN_npos) record_type = IRIMO_cloud;
//   else if (buffer_str.find("XXXXXX") != CORN_npos)      record_type = XXXXXXXX;
   return record_type;
}
//______________________________________________________________________________
nat32 IRIMO_convertor::read_monthly_record(istream &input_file)
{  nat32 records_read = 0;  // usually 1
   CORN::Ustring station_ID;
   CORN::Year year;
   CORN::Month month;
   IRIMO_Record_type record_type = read_month_record_header(input_file,station_ID,year ,month);
   if ((  (parameters.station_IDs_filter.length() == 0)
        ||(parameters.station_IDs_filter.contains(station_ID.c_str()))
        ||(parameters.station_IDs_filter == "all")
        ||(parameters.station_IDs_filter == "")
        )
         && ued_file)
   {  // the station is selected
         at_next_monthly_record = false;
            switch (record_type)
            {
               case IRIMO_wind :                                     records_read += (nat32)read_monthly_wind_record_body                         (input_file,*ued_file,year,month); break;
               case IRIMO_temperature :                              records_read += (nat32)read_monthly_temperature_record_body                  (input_file,*ued_file,year,month); break;
               case IRIMO_reletive_humidity_and_precipitation :      records_read += (nat32)read_monthly_relative_humidity_and_precipitation_body (input_file,*ued_file,year,month); break;
               case IRIMO_soil_temp_radiation_sunshine_evaporation : records_read += (nat32)read_soil_temp_radiation_sunshine_evaporation_body    (input_file,*ued_file,year,month); break;
               case IRIMO_pressure  :  // NYI
               case IRIMO_cloud     :  // NYI
               default              : records_read += (nat32)skip_to_next_monthly_record(input_file); break;
            }
            records_read++;

   }
   return records_read;
}
//______________________________________________________________________________
bool IRIMO_convertor::read_monthly_wind_record_body(istream &input_file,UED_indexed_database &ued_file,Year year,Month month)
{
   // Already read the header
   // Already read the line containing  HOURLY DDFF IN KNOT
   std::string /* 091212    UIO_string */buffer_str;
   do
   {  // read until the line: HOUR     00         03         06         09         12         15         18         21     MEAN   HIGHEST      MAX   GUSTY
      // is encountered because there may or may not be blank lines and the line with: HOURLY DDFF AND MAX WIND AND GUSTY WIND IN KNOT
      getline(input_file,buffer_str); // read blank line
   } while (buffer_str.find("HOUR ") == CORN_npos);   // 070424 these may need to be find_substring
   getline(input_file,buffer_str); // read       --------   --------   --------   --------   --------   --------   --------   --------          VALUE       WIND   WIND
   getline(input_file,buffer_str); // read         GMT.       GMT.       GMT.       GMT.       GMT.       GMT.       GMT.       GMT.     --  -----------   -----  ------
   getline(input_file,buffer_str); // read DAY   DD   FF    DD   FF    DD   FF    DD   FF    DD   FF    DD   FF    DD   FF    DD   FF    FF  DD   FF HOUR  DD  FF  DD FF
   getline(input_file,buffer_str); // read blank line
   for (DOM expected_dom = 1; expected_dom <= CORN::date_days_in_month(year,month); expected_dom++)
   {  getline(input_file,buffer_str);
      DOM dom  = atoi(buffer_str.c_str());  // atoi() should pick out the first number on the line as an integer
      if (dom != expected_dom) return false; // read failure, the file must be messed up
      CORN::Date record_date(year,month,dom);
      DOY doy = record_date.get_DOY();

//      float32 DD_unused;
//      float32 FF_unused;
//      for (uint8 hour = 0; hour <= 21; hour += 3)
//      {
//         input_file >> DD_unused >> FF_unused;
//      }

      // The DD (direction?) and FF (knot?) for the all the 3 hour are currently ignored.

      Ustring FF_str(buffer_str.substr(92,7).c_str());
      float32 FF_mean = atof(FF_str.c_str());
//      input_file >> FF_mean;
//      getline(input_file,buffer_str/*buffer_str.read_line(input_file)*/; // The remainder of the line is ignored.
      float32 windspeed_m_sec = knots_to_m_per_sec(FF_mean); // convert FF_mean from knots to m/sec


      Units_code windspeed_units = UC_meters_per_second;
      // Check data quality
      Quality windspeed_smart_quality(measured_quality);

      CORN::Ustring  quality_description;
         weather_data_validator->validate_float32
         (doy,windspeed_m_sec
         ,wind_speed_creation.variable_code
         ,windspeed_units,UT_day
         ,CORN::measured_quality,CORN::measured_quality,windspeed_smart_quality,quality_description);
      CORN::Quality windspeed_quality(windspeed_smart_quality); //  = windspeed_smart_quality.get();
      if (FF_str.find("*") != CORN_npos) windspeed_quality = CORN::missing_quality; // 070424 these may need to be find_substring
      //  determine query date
      UED::Time_query set_query(record_date.get_datetime64(),record_date.get_datetime64(),record_date.get_datetime64(),UED::Time_query::at);
      bool created;  // to catch the result of set_values
      // Store value in UED file
      ued_file.set_value(windspeed_m_sec       ,set_query,windspeed_units       ,windspeed_quality ,wind_speed_creation               ,created);
   }
   // The following lines are ignored

   getline(input_file,buffer_str/*buffer_str.read_line(input_file)*/); // read ------------------------------------------------------------------------------------------------------------------------------
   getline(input_file,buffer_str/*buffer_str.read_line(input_file)*/); // read MEAN        5.1        5.1        6.3        7.7        8.4        6.5        5.9        5.6   6.3
   return true;
/* example of format
                                                   HOURLY DDFF IN KNOT

                                   HOURLY DDFF AND MAX WIND AND GUSTY WIND IN KNOT

 HOUR     00         03         06         09         12         15         18         21     MEAN   HIGHEST      MAX   GUSTY
       --------   --------   --------   --------   --------   --------   --------   --------          VALUE       WIND   WIND
         GMT.       GMT.       GMT.       GMT.       GMT.       GMT.       GMT.       GMT.     --  -----------   -----  ------
 DAY   DD   FF    DD   FF    DD   FF    DD   FF    DD   FF    DD   FF    DD   FF    DD   FF    FF  DD   FF HOUR  DD  FF  DD FF

   1    0    0   290    2   280    6   160    6   100    4    60    4    70    4    60    4    3.8  280   6   6  200  7 *** ***
   2   90    4     0    0   160    6   110   10   160    8   120    8   140    4   120    8    6.0  110  10   9  120 15 *** ***
   :     Values for each day of month omitted from this example.
  31   90    4     0    0   230    2   250    2   140    4     0    0    20    4    70    4    2.5   90   4   0   90  4 *** ***
 ------------------------------------------------------------------------------------------------------------------------------
 MEAN        5.1        5.1        6.3        7.7        8.4        6.5        5.9        5.6   6.3
*/
}
//______________________________________________________________________________
bool IRIMO_convertor::read_monthly_temperature_record_body(istream &input_file,UED_indexed_database &ued_file,Year year,Month month)
{
   // Already read the header
   // Already read the line containing  HOURLY DRY BULB AND WET BULB TEMPERATURE
   std::string buffer_str;
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read  HOUR      00          03          06          09          12          15          18          21         MEAN
   getline(input_file,buffer_str); // read       ---------   ---------   ---------   ---------   ---------   ---------   ---------   ---------   ---------
   getline(input_file,buffer_str); // read          GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.                            MEAN
   getline(input_file,buffer_str); // read DAY   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET  MIN.  MAX.  DAILY
   getline(input_file,buffer_str); // read blank line

   for (DOM expected_dom = 1; expected_dom <= CORN::date_days_in_month(year,month); expected_dom++)
   {  getline(input_file,buffer_str);
      DOM dom  = atoi(buffer_str.c_str());  // atoi() should pick out the first number on the line as an integer
      if (dom != expected_dom) return false; // read failure, the file must be messed up
      CORN::Date record_date(year,month,dom);
      DOY doy = record_date.get_DOY();
      float32 bulb_temperature_dry;
      float32 bulb_temperature_wet;
      // The 3 hour bulb temperature currently not imported
      // The mean bulb temperature (currently not imported)

      Ustring temperature_min_str(buffer_str.substr(112,6));
      Ustring temperature_max_str(buffer_str.substr(118,6));
      Ustring temperature_mean_str(buffer_str.substr(124,6));

      float32 temperature_min = atof(temperature_min_str.c_str());
      float32 temperature_max = atof(temperature_max_str.c_str());
      float32 temperature_mean = atof(temperature_mean_str.c_str());

      Units_code temperature_min_units = UC_celcius;
      Units_code temperature_max_units = UC_celcius;
      Units_code temperature_mean_units = UC_celcius;
      // Check data quality
      Quality temperature_min_smart_quality(measured_quality);
      //091212 temperature_min_smart_quality.set(
      CORN::Ustring  quality_description;
      weather_data_validator->validate_float32
         (doy,temperature_min
         ,min_temperature_creation.variable_code,temperature_min_units,UT_day
         ,CORN::measured_quality,CORN::measured_quality,temperature_min_smart_quality,quality_description);
//      Quality_code temperature_min_quality = temperature_min_smart_quality.get();
      Quality temperature_min_quality ( temperature_min_smart_quality);
      if (temperature_min_str.find("*") != CORN_npos)   temperature_min_quality  = CORN::missing_quality; // 070424 these may need to be find_substring
      Quality temperature_max_smart_quality(measured_quality);
//091212       temperature_max_smart_quality.set(
      weather_data_validator->validate_float32
         (doy,temperature_max,max_temperature_creation.variable_code,temperature_max_units
         ,UT_day,CORN::measured_quality,CORN::measured_quality
         ,temperature_max_smart_quality,quality_description);
      Quality temperature_max_quality(temperature_max_smart_quality.get());
      if (temperature_max_str.find("*") != CORN_npos)   temperature_max_quality  = CORN::missing_quality; // 070424 these may need to be find_substring
      //NYI      Quality temperature_mean_smart_quality(measured_quality);
      //NYI      temperature_mean_smart_quality.set(weather_data_validator->validate(doy,temperature_mean,temperature_mean_creation.variable_code,temperature_mean_units,UT_day,CORN::measured_quality,CORN::measured_quality));
      //NYI      if (temperature_mean_str.find("*") != CORN_npos)  temperature_mean_quality = CORN::missing_quality;

      //  determine query date
      UED::Time_query set_query(record_date.get_datetime64(),record_date.get_datetime64(),record_date.get_datetime64(),UED::Time_query::at);
      bool created;  // to catch the result of set_values
      // Store value in UED file
      ued_file.set_value(temperature_min ,set_query,temperature_min_units ,temperature_min_quality ,min_temperature_creation ,created);
      ued_file.set_value(temperature_max ,set_query,temperature_max_units ,temperature_max_quality ,max_temperature_creation ,created);
//      ued_file->set_value(temperature_mean,set_query,temperature_mean_units,temperature_mean_quality,mean_temperature_creation,created);
   }
   // The following lines are ignored
   getline(input_file,buffer_str); // read -----------------------------------------------------------------------------------------------------------------------------------
   getline(input_file,buffer_str); // read MEAN -1.2  -2.7  -1.6  -3.1   0.1  -1.8   3.7   0.4   5.0   1.1   2.4  -0.2   0.7  -1.3  -0.4  -2.0   1.1  -1.2  -3.3   6.1   1.4
   getline(input_file,buffer_str); // read -----------------------------------------------------------------------------------------------------------------------------------
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read LOWEST  TEMPERATURE -13.0 AT DAY 22
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read HIGHEST TEMPERATURE  15.2 AT DAY  1
   return true;
/* example of format
                                         HOURLY DRY BULB AND WET BULB TEMPERATURE

 HOUR      00          03          06          09          12          15          18          21         MEAN
       ---------   ---------   ---------   ---------   ---------   ---------   ---------   ---------   ---------
          GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.                            MEAN
 DAY   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET   DRY   WET  MIN.  MAX.  DAILY

  1   -0.7  -2.8   0.0  -1.8   4.2   1.2  11.4   5.6  13.2   6.0   8.5   2.7   7.0   2.4   5.8   1.8   6.2   1.9  -2.4  15.2   6.4
   :     Values for each day of month omitted from this example.
 31    0.6  -0.3   1.1   0.2   2.5   1.0  10.2   5.6  12.6   6.1   8.6   4.1   5.6   3.1   2.8   1.4   5.5   2.6  -0.5  14.3   6.9
 -----------------------------------------------------------------------------------------------------------------------------------
 MEAN -1.2  -2.7  -1.6  -3.1   0.1  -1.8   3.7   0.4   5.0   1.1   2.4  -0.2   0.7  -1.3  -0.4  -2.0   1.1  -1.2  -3.3   6.1   1.4
 -----------------------------------------------------------------------------------------------------------------------------------



 LOWEST  TEMPERATURE -13.0 AT DAY 22

 HIGHEST TEMPERATURE  15.2 AT DAY  1
*/
}
//______________________________________________________________________________
bool IRIMO_convertor::read_monthly_relative_humidity_and_precipitation_body(istream &input_file,UED_indexed_database &ued_file,Year year,Month month)
{
   // Already read the header
   // Already read the line containingHOURLY  RELATIVE HUMIDITY AND DAILY PRECIPITATION
   std::string /buffer_str;
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read HOUR      00          03          06          09          12          15          18          21         MEAN
   getline(input_file,buffer_str); // read       ---------   ---------   ---------   ---------   ---------   ---------   ---------   ---------   ---------
   getline(input_file,buffer_str); // read          GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.           SUN
   getline(input_file,buffer_str); // read DAY   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM  TGTG  SHINE  RRR
   getline(input_file,buffer_str); // read  blank line
   for (DOM expected_dom = 1; expected_dom <= CORN::date_days_in_month(year,month); expected_dom++)
   {  getline(input_file,buffer_str);
      DOM dom  = atoi(buffer_str.c_str());  // atoi() should pick out the first number on the line as an integer
      if (dom != expected_dom) return false; // read failure, the file must be messed up
      CORN::Date record_date(year,month,dom);
      DOY doy = record_date.get_DOY();

      Quality_code any_dew_pt_temp_quality = missing_quality;
      Quality_code any_relhumid_quality = missing_quality;
      float32 dew_pt_max = -99999;
      float32 dew_pt_min = 99999;
      float32 rel_humid_max = -99999;
      float32 rel_humid_min = 99999;
      int dew_pos = 4;
      int hum_pos = 10;
      for (uint8 hour = 0; hour <= 21; hour += 3)
      {
         Ustring dew_pt_temp_3hour_str(buffer_str.substr(dew_pos,6));
         if (dew_pt_temp_3hour_str.find("*") == CORN_npos) // 070424 these may need to be find_substring
         {
            float32 dew_pt_temp_3hour = atof(dew_pt_temp_3hour_str.c_str());
            dew_pt_max = CORN_max(dew_pt_max,dew_pt_temp_3hour);
            dew_pt_min = CORN_min(dew_pt_min,dew_pt_temp_3hour);
            any_dew_pt_temp_quality = measured_quality;
         }
         Ustring rel_humid_3hour_str(buffer_str.substr(hum_pos,6));
         if (rel_humid_3hour_str.find("*") == CORN_npos) // 070424 these may need to be find_substring
         {
            float32 rel_humid_3hour = atof(rel_humid_3hour_str.c_str());
            rel_humid_max = CORN_max(rel_humid_max,rel_humid_3hour);
            rel_humid_min = CORN_min(rel_humid_min,rel_humid_3hour);
            any_relhumid_quality = measured_quality;
         }
         dew_pos += 12;
         hum_pos += 12;
      }
    Ustring dew_pt_mean_str(buffer_str.substr(100,6));
    float32 dew_pt_mean = atof(dew_pt_mean_str.c_str());

//NYI    Ustring rel_humid_mean_str(buffer_str.substr(106,6));
//NYI         also check for missing (any *)
//NYI    float32 rel_humid_mean = atof(rel_humid_mean_str.c_str());

      //NYI float32 TGTG;     // Total ground temperature
      //NYI float32 sunshine; // Sunshine hours
      Ustring RRR_str(buffer_str.substr(124,6));
      float32 RRR = atof(RRR_str.c_str()); // precipitation mm

      Units_code dew_pt_min_units = UC_celcius;
      Units_code dew_pt_max_units = UC_celcius;
      Units_code dew_pt_mean_units = UC_celcius;

      Units_code rel_humid_min_units = UC_percent;
      Units_code rel_humid_max_units = UC_percent;
//NYI      Units_code rel_humid_mean_units = UC_percent;
      Units_code precipitation_units = UC_mm;

      // Check data quality
      CORN::Ustring  quality_description;

      Quality dew_pt_min_smart_quality(any_dew_pt_temp_quality);
//091212      dew_pt_min_smart_quality   .set(
      weather_data_validator->validate_float32(doy,dew_pt_min     ,min_dew_point_temperature_creation .variable_code,dew_pt_min_units     ,UT_day,CORN::measured_quality,CORN::measured_quality,dew_pt_min_smart_quality,quality_description);
//      Quality_code dew_pt_min_quality = dew_pt_min_smart_quality.get();
      Quality dew_pt_min_quality(dew_pt_min_smart_quality);

      Quality dew_pt_max_smart_quality(any_dew_pt_temp_quality);
//091212      dew_pt_max_smart_quality   .set(
      weather_data_validator->validate_float32(doy,dew_pt_max     ,max_dew_point_temperature_creation .variable_code,dew_pt_max_units     ,UT_day,CORN::measured_quality,CORN::measured_quality,dew_pt_max_smart_quality,quality_description);
//      Quality_code dew_pt_max_quality = dew_pt_max_smart_quality.get();
      Quality dew_pt_max_quality(dew_pt_max_smart_quality);


      Quality dew_pt_mean_smart_quality(measured_quality);
      //091212 dew_pt_mean_smart_quality   .set(
      weather_data_validator->validate_float32(doy,dew_pt_mean     ,avg_dew_point_temperature_creation .variable_code,dew_pt_mean_units     ,UT_day,CORN::measured_quality,CORN::measured_quality,dew_pt_mean_smart_quality,quality_description);
      Quality dew_pt_mean_quality(dew_pt_mean_smart_quality);
//      Quality_code dew_pt_mean_quality = dew_pt_mean_smart_quality.get();
      if (dew_pt_mean_str.find("*") != CORN_npos)   dew_pt_mean_quality  = CORN::missing_quality; // 070424 these may need to be find_substring

      Quality rel_humid_min_smart_quality(any_relhumid_quality);
//091212      rel_humid_min_smart_quality.set(
      weather_data_validator->validate_float32(doy,rel_humid_min  ,min_relative_humidity_creation     .variable_code,rel_humid_min_units  ,UT_day,CORN::measured_quality,CORN::measured_quality,rel_humid_min_smart_quality,quality_description);
//      Quality_code rel_humid_min_quality = rel_humid_min_smart_quality.get();
      Quality rel_humid_min_quality (rel_humid_min_smart_quality);
      Quality rel_humid_max_smart_quality(any_relhumid_quality);
      //091212 rel_humid_max_smart_quality.set(
      weather_data_validator->validate_float32(doy,rel_humid_max  ,max_relative_humidity_creation     .variable_code,rel_humid_max_units  ,UT_day,CORN::measured_quality,CORN::measured_quality,rel_humid_max_smart_quality,quality_description);
      Quality rel_humid_max_quality ( rel_humid_max_smart_quality);
//      Quality_code rel_humid_max_quality = rel_humid_max_smart_quality.get();
      Quality precipitation_smart_quality(measured_quality);
      // WARNING presuming RRR is precipitation in mm
      //091212 precipitation_smart_quality.set(
      weather_data_validator->validate_float32(doy,RRR/*precipitation*/            ,precipitation_creation             .variable_code,precipitation_units  ,UT_day,CORN::measured_quality,CORN::measured_quality,precipitation_smart_quality,quality_description);
//      Quality_code precipitation_quality = precipitation_smart_quality.get();
      Quality precipitation_quality(precipitation_smart_quality);
      if (RRR_str.find("*") != CORN_npos)   precipitation_quality  = CORN::missing_quality; // 070424 these may need to be find_substring
      //  determine query date

      UED::Time_query set_query(record_date.get_datetime64(),record_date.get_datetime64(),record_date.get_datetime64(),UED::Time_query::at);
      bool created;  // to catch the result of set_values
      // Store value in UED file
      ued_file.set_value(dew_pt_min   ,set_query,dew_pt_min_units   ,dew_pt_min_quality     ,min_dew_point_temperature_creation    ,created);
      ued_file.set_value(dew_pt_max   ,set_query,dew_pt_max_units   ,dew_pt_max_quality     ,max_dew_point_temperature_creation    ,created);
      ued_file.set_value(dew_pt_mean  ,set_query,dew_pt_mean_units  ,dew_pt_mean_quality    ,avg_dew_point_temperature_creation   ,created);
      ued_file.set_value(rel_humid_min,set_query,rel_humid_min_units,rel_humid_min_quality  ,min_relative_humidity_creation ,created);
      ued_file.set_value(rel_humid_max,set_query,rel_humid_max_units,rel_humid_max_quality  ,max_relative_humidity_creation ,created);
      ued_file.set_value(RRR/*precipitation*/,set_query,precipitation_units,precipitation_quality  ,precipitation_creation ,created);
   }
   // The following lines are ignored
   getline(input_file,buffer_str); // read -----------------------------------------------------------------------------------------------------------------------------------
   getline(input_file,buffer_str); // read MEAN -6.0  70.9  -6.6  70.3  -5.7  65.2  -5.5  52.5  -5.7  47.2  -5.5  57.8  -5.6  65.3  -5.5  69.8  -5.8  62.4  -4.6   4.2
   getline(input_file,buffer_str); // read -----------------------------------------------------------------------------------------------------------------------------------
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read TOTAL OF SUNSHINE 129.0
   getline(input_file,buffer_str); // read MOST-DAY PRECIPITATION  27.3  AT DAY  5
   getline(input_file,buffer_str); // read TOTAL OF PRECIPITATION  87.0

   return true;
/* example
1                                            ISLAMIC REPUBLIC OF IRAN
                                         METEOROLOGICAL ORGANIZATION (IRIMO)
 STATION KERMANSHAH
 LATITUDE   34  21  N                         DATA PROCESSING CENTER
 LONGITUDE  47   9  E
 ELEVATION  1318.6 MET.
                                             MONTH  JANUARY     YEAR 1996
                                    HOURLY  RELATIVE HUMIDITY AND DAILY PRECIPITATION

 HOUR      00          03          06          09          12          15          18          21         MEAN
       ---------   ---------   ---------   ---------   ---------   ---------   ---------   ---------   ---------
          GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.        GMT.           SUN
 DAY   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM   DEW   HUM  TGTG  SHINE  RRR

  1   -7.3  61.0  -5.2  68.0  -3.9  56.0  -2.8  37.0  -4.8  28.0  -6.8  33.0  -5.3  41.0  -5.4  46.0  -5.2  46.3  -6.0   5.0   0.0
  2   -6.0  52.0  -5.3  50.0  -4.0  48.0  -3.2  30.0  -3.4  31.0  -5.0  35.0  -4.0  39.0  -0.5  54.0  -3.9  42.4  -2.0   2.2   0.0
   :     Values for each day of month omitted from this example.
 31   -1.8  84.0  -1.3  84.0  -1.2  76.0  -0.2  48.0  -2.4  35.0  -2.4  46.0  -0.2  65.0  -0.8  77.0  -1.3  64.4  -1.0   7.4   0.0
 -----------------------------------------------------------------------------------------------------------------------------------
 MEAN -6.0  70.9  -6.6  70.3  -5.7  65.2  -5.5  52.5  -5.7  47.2  -5.5  57.8  -5.6  65.3  -5.5  69.8  -5.8  62.4  -4.6   4.2
 -----------------------------------------------------------------------------------------------------------------------------------



 TOTAL OF SUNSHINE 129.0
 MOST-DAY PRECIPITATION  27.3  AT DAY  5
 TOTAL OF PRECIPITATION  87.0
*/
}
//______________________________________________________________________________
bool IRIMO_convertor::read_soil_temp_radiation_sunshine_evaporation_body(istream &input_file,UED_indexed_database &ued_file,Year year,Month month)
{
   // Already read the header
   // Already read the line containing DAILY SOIL-TEMP., RADIATION (JULE), SUNSHINE & EVAPORATION
   std::string buffer_str;
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read                SOIL-TEMP.(03)                      SOIL-TEMP.(09)                      SOIL-TEMP.(15)
   getline(input_file,buffer_str); // read       ---------------------------------   ---------------------------------   ---------------------------------        SUN
   getline(input_file,buffer_str); // read DAY    5    10    20    30    50    100    5    10    20    30    50    100    5    10    20    30    50    100  RAD. SHINE  EVA.
   getline(input_file,buffer_str); // read       ---------------------------------   ---------------------------------   --------------------------------- ----- ----- -----

   for (DOM expected_dom = 1; expected_dom <= CORN::date_days_in_month(year,month); expected_dom++)
   {  getline(input_file,buffer_str);
      DOM dom  = atoi(buffer_str.c_str());  // atoi() should pick out the first number on the line as an integer
      if (dom != expected_dom) return false; // read failure, the file must be messed up
      CORN::Date record_date(year,month,dom);
      DOY doy = record_date.get_DOY();
      //NYI not currently using 3 hour soil temperature
      Ustring radiation_str(buffer_str.substr(112,6));
      float32 radiation_J_cm2_day = atof(radiation_str.c_str()); // Joule/cm²/day
      //NYI float32 sunshine_hour;
      //NYI float32 evap;

      float32 radiation_MJ_m2_day =  J_cm2_to_MJ_m2(radiation_J_cm2_day);

      Units_code radiation_units = UC_MJ_m2;
      CORN::Ustring  quality_description;

      Quality radiation_smart_quality(measured_quality);
      //091212 radiation_smart_quality.set(
      weather_data_validator->validate_float32 (doy,radiation_MJ_m2_day,solar_radiation_creation.variable_code,radiation_units  ,UT_day,CORN::measured_quality,CORN::measured_quality,radiation_smart_quality,quality_description);
//      Quality_code radiation_quality = radiation_smart_quality.get();
      Quality radiation_quality ( radiation_smart_quality);
      if (radiation_str.find("*") != CORN_npos)   radiation_quality  = CORN::missing_quality; // 070424 these may need to be find_substring

      UED::Time_query set_query(record_date.get_datetime64(),record_date.get_datetime64(),record_date.get_datetime64(),UED::Time_query::at);
      bool created;  // to catch the result of set_values
      // Store value in UED file
      ued_file.set_value(radiation_MJ_m2_day   ,set_query,radiation_units   ,radiation_quality     ,solar_radiation_creation    ,created);
   }
   getline(input_file,buffer_str); // read ---------------------------------------  ----------------------------------  ----------------------------------  ----- ----- -----
   getline(input_file,buffer_str); // read MEAN  0.2   1.9   4.0   5.3   8.0  10.8   2.8   2.7   3.9   5.1   7.8  10.7   4.1   4.1   4.3   5.1   7.9  10.7   168   4.2   1.0
   getline(input_file,buffer_str); // read ---------------------------------------  ----------------------------------  ----------------------------------  ----- ----- -----
   getline(input_file,buffer_str); // read     TOTAL OF SUNSHINE = 129.0
   getline(input_file,buffer_str); // read blank line
   getline(input_file,buffer_str); // read     TOTAL OF RADIATION =  5232
/*example
1                                            ISLAMIC REPUBLIC OF IRAN
                                         METEOROLOGICAL ORGANIZATION (IRIMO)
 STATION KERMANSHAH
 LATITUDE   34  21  N                         DATA PROCESSING CENTER
 LONGITUDE  47   9  E
 ELEVATION  1318.6 MET.
                                             MONTH  JANUARY     YEAR 1996
                                         DAILY SOIL-TEMP., RADIATION (JULE), SUNSHINE & EVAPORATION

                SOIL-TEMP.(03)                      SOIL-TEMP.(09)                      SOIL-TEMP.(15)
       ---------------------------------   ---------------------------------   ---------------------------------        SUN
 DAY    5    10    20    30    50    100    5    10    20    30    50    100    5    10    20    30    50    100  RAD. SHINE  EVA.
       ---------------------------------   ---------------------------------   --------------------------------- ----- ----- -----
  1    2.6   4.8   5.8   7.0   8.6  11.8   6.0   4.4   5.4   7.2   9.6  11.8  10.0   9.2   7.0   7.2   9.6  11.7   173   5.0 *****
   :     Values for each day of month omitted from this example.
 31   -0.6   0.0   1.2   2.8   5.4   9.0   9.6   4.2   3.6   3.9   5.8   8.8  10.0   9.2   5.8   4.0   5.6   9.2   233   7.4 *****
 ---------------------------------------  ----------------------------------  ----------------------------------  ----- ----- -----
 MEAN  0.2   1.9   4.0   5.3   8.0  10.8   2.8   2.7   3.9   5.1   7.8  10.7   4.1   4.1   4.3   5.1   7.9  10.7   168   4.2   1.0
 ---------------------------------------  ----------------------------------  ----------------------------------  ----- ----- -----
     TOTAL OF SUNSHINE = 129.0

     TOTAL OF RADIATION =  5232
*/
   return true;
}
//______________________________________________________________________________
/* Not implemented
1                                            ISLAMIC REPUBLIC OF IRAN
                                         METEOROLOGICAL ORGANIZATION (IRIMO)
 STATION KERMANSHAH
 LATITUDE   34  21  N                         DATA PROCESSING CENTER
 LONGITUDE  47   9  E
 ELEVATION  1318.6 MET.
                                             MONTH  JANUARY     YEAR 1996
                                          HOURLY PRESSURE QFE AND QFF IN MILLIBAR

 HOUR      00            03            06            09            12            15            18            21           MEAN
       -----------   -----------   -----------   -----------   -----------   -----------   -----------   -----------   -----------
          GMT.          GMT.          GMT.          GMT.          GMT.          GMT.          GMT.          GMT.          GMT.
 DAY   QFE    QFF    QFE    QFF    QFE    QFF    QFE    QFF    QFE    QFF    QFE    QFF    QFE    QFF    QFE    QFF    QFE    QFF

   1   872.8 1023.7  872.9 1025.0  874.7 1026.9  874.1 1025.6  872.1 1023.2  872.1 1024.4  873.6 1025.1  874.0 1024.0  873.3 1024.7
   :     Values for each day of month omitted from this example.
  31   872.3 1023.9  872.2 1024.6  873.2 1026.5  872.5 1024.2  870.7 1021.1  870.4 1022.0  871.4 1023.7  871.4 1022.2  871.8 1023.5
 -----------------------------------------------------------------------------------------------------------------------------------
 MEAN  870.0 1023.3  869.8 1023.8  871.1 1025.4  870.6 1024.2  869.2 1022.3  869.6 1023.6  870.2 1024.4  870.2 1023.6  870.1 1023.8
 -----------------------------------------------------------------------------------------------------------------------------------



 LOWEST  QFE  860.4 AT DAY  6 AT HOUR 12

 LOWEST  QFF 1009.6 AT DAY  6 AT HOUR  3

 HIGHEST QFE  878.0 AT DAY 26 AT HOUR  6

 HIGHEST QFF 1036.5 AT DAY 26 AT HOUR  6
*/
//______________________________________________________________________________
/* Not implemented
1                                            ISLAMIC REPUBLIC OF IRAN
                                         METEOROLOGICAL ORGANIZATION (IRIMO)
 STATION KERMANSHAH
 LATITUDE   34  21  N                         DATA PROCESSING CENTER
 LONGITUDE  47   9  E
 ELEVATION  1318.6 MET.
                                             MONTH  JANUARY     YEAR 1996
                             HOURLY AMOUNT OF CLOUD(N) ,  PRESENT WEATHER(WW) ,  VV

 HOUR        00              03              06              09              12              15              18              21
        ------------    ------------    ------------    ------------    ------------    ------------    ------------    ------------
            GMT.            GMT.            GMT.            GMT.            GMT.            GMT.            GMT.            GMT.
 DAY    N  WW    VV     N  WW    VV     N  WW    VV     N  WW    VV     N  WW    VV     N  WW    VV     N  WW    VV     N  WW    VV

   1    3  **  10000    4  **  10000    6  **  10000    4  **  10000    3  **  10000    6  **  10000    7  **  10000    6  **  10000
   :     Values for each day of month omitted from this example.
  31    3  **  10000    4  10   8000    5   5   8000    3   5  10000    5  **  10000    3  **  10000    1  **  10000    0  **  10000
  ----------------------------------------------------------------------------------------------------------------------------------
*/
//______________________________________________________________________________
bool IRIMO_convertor::skip_to_next_monthly_record(istream &input_file)
{  at_next_monthly_record = false;
   //UIO_string buffer_str;
   std::string buffer_str;
   do // just read lines until   1  is encountered in first character position
   {
      getline(input_file,buffer_str);
      if (input_file.eof() || !input_file.good()) return false;
   } while (buffer_str.c_str()[0] != '1');
   at_next_monthly_record = true;
   return true;
}
//______________________________________________________________________________
IRIMO_convertor::IRIMO_convertor(int argc, const char *argv[])
:UED_convertor(argc,argv)
,ued_file(0)
,weather_data_validator(0)
,at_next_monthly_record(false)
{ }
//______________________________________________________________________________


/* example
*/

