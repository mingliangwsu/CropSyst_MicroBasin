
/*
   this is coded instead of using TDF because
   1. There are a quality markers
   2. The records are variable length  (for different versions)


   WPRO appears to be a decendent of WGEN but I don't know if it uses the same format.

   This is the weather file format for EPIC.

*/

/*
WTH sample
     STATION = ABERCROM  STA ID = 0005  STATE = ND  CO = RICHLAND          LAT =  46.450   LONG =  -96.733  ELEV =   285.0  Y-M-D 2006 119
  1960   1   1      999.00999.00   2.5
  1960   1   2      999.00999.00   7.6
  1960   1   3      999.00999.00   0.3
Same format as below but without RH and WS  (Rad is blank)


Year month day

DLY sample
     STATION = ABERCROM  STA ID = 0005  STATE = ND  CO = RICHLAND          LAT =  46.450   LONG =  -96.733  ELEV =   285.0  Y-M-D 2006 119
  1960   1   1   3.2-12.79-24.60  2.54  0.99  3.71
  1960   1   2   2.2-12.36-23.12  7.62  0.82  8.05

Year month day Rad Tx Tn RHavg(0-1?) WS(m/sec?)

There could be more formats, but this is what Armen provided me with.
Currently using record length to identify the format
999.00 is missing value

I am presuming the geolocation line if fixed column widths
*/

#include <UED/convert/convertor.h>
#include <UED/convert/station_database.h>
#include <UED/library/UED.h>
#include <UED/library/locrec.h>
#include <common/geolocation/USA_state_FIPS_code.h>
//______________________________________________________________________________
class WPRO_format_convertor
: public UED_convertor
{
   bool input_file_is_generated;
public:
   WPRO_format_convertor(int argc, char *argv[],bool _input_file_is_generated)
   : UED_convertor(argc, argv)
   , input_file_is_generated(_input_file_is_generated)
   {}
   virtual uint32 perform_import() ;
   virtual uint32 perform_export() { /* NYI */ }
private:
   bool is_blank(const char *field) const;

};
//______________________________________________________________________________
bool WPRO_format_convertor::is_blank(const char *field) const
{
   bool blank = true;
   for (int i = 0; i < strlen(field); i++)
      if (field[i] != ' ') return blank =false;
   return blank;
}
//______________________________________________________________________________
uint32 WPRO_format_convertor::perform_import()
{  uint32 record_count = 0;
   ifstream input_file(parameters.target_filename.c_str());
   cout << "Reading input file(s):" <<  parameters.target_filename << endl;
   // Presumably only one station per file
   long buffer_read = 0;
   CORN::Ustring buffer_str;
   if (!input_file.eof())
   {
   // The first line is geolocation

      140516 replace read_to_delim with getline(input_file,buffer_str)

      buffer_str.read_to_delim(input_file);

     CORN::Ustring xSTA_ID (buffer_str,34,4);
     CORN::Ustring STATE  (buffer_str,48,2);

      // The station IDs appear to be unique only by state.
      // I am appending the state name to make sure the UED files are unique.
     CORN::Ustring STA_state_ID (STATE);
     STA_state_ID.append(xSTA_ID);

      bool added_just_now = false;
      Station_database *station_database = provide_station_database(STA_state_ID,added_just_now);
      UED_indexed_database *ued_file = &(station_database->ued_file);

      UED_geolocation_record  *station_geolocation = ued_file->get_geolocation_record();
      if (!station_geolocation)
      {  // The UED doesn't already have geolocation so we will added it.

         station_geolocation = new UED_geolocation_record;

         CORN::Ustring STATION(buffer_str,15,10);
         CORN::Ustring STATE  (buffer_str,48,2);
         CORN::Ustring COUNTY (buffer_str,57,17);
         CORN::Ustring LAT    (buffer_str,81,7);
         CORN::Ustring LONG   (buffer_str,98,8);
         CORN::Ustring ELEV   (buffer_str,116,7);
         // The remainder of the line is the generate date  YYYYMMDD  ?


         station_geolocation->set_elevation           (atof(ELEV.c_str()));
         station_geolocation->set_country_code        (840);
         station_geolocation->set_country_name        ("USA");
               // Use ISO 3166 codes
         uint16 state_number = lookup_USA_state_FIPS_number(STATE.c_str());
         station_geolocation->set_state_code          (state_number);
         station_geolocation->set_state_name          (USA_state_FIPS[state_number].name);
               // For the US, use FIPS code
         station_geolocation->set_county_name         (string(COUNTY.strip()).c_str());
         station_geolocation->set_station_ID_code     (xSTA_ID.c_str());
         station_geolocation->set_station_name        (string(STATION.strip()).c_str());

         station_geolocation->set_latitude_dec_deg_32 (atof(LAT.c_str()));
         station_geolocation->set_longitude_dec_deg_32(atof(LONG.c_str()));

         ued_file->take_geolocation_record(station_geolocation);
      }
      Weather_validator *weather_data_validator = station_database->provide_weather_data_validator();
      char token_buffer[100];
      do
      {
      140516 replace read_to_delim with getline(input_file,buffer_str)

         buffer_str.read_to_delim(input_file);
         int buffer_length = buffer_str.length();
         record_count += (int)(buffer_length > 0);
         if (buffer_length >  2) strcpy(token_buffer,buffer_str.substr(2,4).c_str());  token_buffer[4] = 0;  Year  year     =  atoi(token_buffer);
         if (buffer_length >  8) strcpy(token_buffer,buffer_str.substr(8,2).c_str());  token_buffer[2] = 0;  Month month    =  atoi(token_buffer);
         if (buffer_length > 12) strcpy(token_buffer,buffer_str.substr(12,2).c_str()); token_buffer[2] = 0;  DOM   dom      =  atoi(token_buffer);                                               // Using other real quality because we want it better than ClimGen generation
         if (buffer_length > 14) strcpy(token_buffer,buffer_str.substr(14,6).c_str()); token_buffer[6] = 0;  float32 Srad   = atof(token_buffer);  Units_code Srad_units = UC_MJ_m2;             Quality_code Srad_qual  = is_blank(token_buffer) ? missing_quality : (input_file_is_generated ? other_real_quality : measured_quality);
         if (buffer_length > 20) strcpy(token_buffer,buffer_str.substr(20,6).c_str()); token_buffer[6] = 0;  float32 Tmax   = atof(token_buffer);  Units_code Tmax_units = UC_celcius;           Quality_code Tmax_qual  = is_blank(token_buffer) ? missing_quality : (input_file_is_generated ? other_real_quality : measured_quality);
         if (buffer_length > 26) strcpy(token_buffer,buffer_str.substr(26,6).c_str()); token_buffer[6] = 0;  float32 Tmin   = atof(token_buffer);  Units_code Tmin_units = UC_celcius;           Quality_code Tmin_qual  = is_blank(token_buffer) ? missing_quality : (input_file_is_generated ? other_real_quality : measured_quality);
         if (buffer_length > 32) strcpy(token_buffer,buffer_str.substr(32,6).c_str()); token_buffer[6] = 0;  float32 precip = atof(token_buffer);  Units_code precip_units= UC_mm;               Quality_code precip_qual= is_blank(token_buffer) ? missing_quality : (input_file_is_generated ? other_real_quality : measured_quality);
         if (buffer_length > 38) strcpy(token_buffer,buffer_str.substr(38,6).c_str()); else  token_buffer[0] = 0; token_buffer[6] = 0;  float32 RHavg  = atof(token_buffer);  Units_code RHavg_units= UC_decimal_percent;   Quality_code RHavg_qual = is_blank(token_buffer) ? missing_quality : (input_file_is_generated ? other_real_quality : measured_quality);
         if (buffer_length > 44) strcpy(token_buffer,buffer_str.substr(44,6).c_str()); else  token_buffer[0] = 0; token_buffer[6] = 0;  float32 WS     = atof(token_buffer);  Units_code WS_units   = UC_meters_per_second; Quality_code WS_qual    = is_blank(token_buffer) ? missing_quality : (input_file_is_generated ? other_real_quality : measured_quality);

         Quality_code file_qual = input_file_is_generated ? other_real_quality : measured_quality;
         Quality_code col_qual = input_file_is_generated ? other_real_quality : measured_quality;

         CORN::Date record_date(year,month,dom);
         DOY record_doy =record_date.get_DOY();

         if (weather_data_validator)
         {
            if (UED_is_valid(Srad_qual))     Srad_qual   = weather_data_validator->validate(record_doy,Srad ,solar_radiation_creation.variable_code        ,Srad_units ,UT_day,file_qual,col_qual);
            if (UED_is_valid(Tmax_qual))     Tmax_qual   = weather_data_validator->validate(record_doy,Tmax ,max_temperature_creation.variable_code        ,Tmax_units ,UT_day,file_qual,col_qual);
            if (UED_is_valid(Tmin_qual))     Tmin_qual   = weather_data_validator->validate(record_doy,Tmin ,min_temperature_creation.variable_code        ,Tmin_units ,UT_day,file_qual,col_qual);
            if (UED_is_valid(precip_qual))   precip_qual = weather_data_validator->validate(record_doy,precip,precipitation_creation.variable_code         ,precip_units,UT_day,file_qual,col_qual);
            if (UED_is_valid(RHavg_qual))    RHavg_qual  = weather_data_validator->validate(record_doy,RHavg,avg_relative_humidity_creation.variable_code  ,RHavg_units ,UT_day,file_qual,col_qual);
            if (UED_is_valid(WS_qual))       WS_qual     = weather_data_validator->validate(record_doy,WS   ,wind_speed_creation.variable_code             ,WS_units ,UT_day,file_qual,col_qual);
//          if (UED_is_valid(XXXXX_qual))    XXXXX_qual = weather_data_validator->validate(record_doy,XXXX ,XXXXXXXXXXXXXXX_creation.variable_code,XXXX_units ,UT_day,file_qual,col_qual);
         }

         UED_time_query set_query(record_date.get_datetime64(),record_date.get_datetime64(),record_date.get_datetime64(),UED_time_query::at);
         bool created;  // to catch the result of set_values
         if (Srad_qual != missing_quality)   ued_file->set_value(Srad   ,set_query,Srad_units     ,Srad_qual   ,solar_radiation_creation        ,created);
         if (Tmax_qual != missing_quality)   ued_file->set_value(Tmax   ,set_query,Tmax_units     ,Tmax_qual   ,max_temperature_creation        ,created);
         if (Tmin_qual != missing_quality)   ued_file->set_value(Tmin   ,set_query,Tmin_units     ,Tmin_qual   ,min_temperature_creation        ,created);
         if (precip_qual != missing_quality) ued_file->set_value(precip ,set_query,precip_units   ,precip_qual ,precipitation_creation          ,created);
         if (RHavg_qual != missing_quality)  ued_file->set_value(RHavg  ,set_query,RHavg_units    ,RHavg_qual  ,avg_relative_humidity_creation  ,created);
         if (WS_qual != missing_quality)     ued_file->set_value(WS     ,set_query,WS_units       ,WS_qual     ,wind_speed_creation             ,created);
      } while (!input_file.eof());
   }

   cout << "Writing UED files:" << endl;
   return record_count;
}
//______________________________________________________________________________
int main(int argc, char *argv[])
{
// test command lines
//   C:\dev\UED\convert\test\convert_UCAR_ds512.0.dlynew.rsp

//   prompt the user if the file contains real or generated data.
   bool input_file_is_generated = false;

   WPRO_format_convertor convertor(argc,argv,input_file_is_generated);
   int result =  convertor.convert();
   convertor.notify_climgen();
   return result;
}
//______________________________________________________________________________

