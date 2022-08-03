#include <ued/convert/convertor.h>
#include <ued/convert/ncdc/stations.h>
#include <ued/ued.h>
#include <ued/locrec.h>
#include <ued/timeqry.h>
#include <corn/datetime/date.h>

#include <stdio.h>

// There is also an earthinfo daily ascii  may eventually want to define this convertor
// creating an superclass  Earthinfo_daily_UED_convertor to derive the ascii and binary from

class EarthInfo_daily_binary_UED_convertor
: public UED_convertor
{  // EarthInfo export format
public:
   struct EarthInfo_daily_binary_record
   {
      uint16   ID;
      char     station_name[23];
      char     county[20];
      char     latitude[4];
      char     longitude[5];
      unsigned char  parameter;    // Need to identify these codes
      unsigned char  start_month;
      unsigned char  start_year_1800;  // offset from 1800   to obtain the correct year add 1800 to the char.
      unsigned char  end_month;
      unsigned char  end_year_1800;    // offset from 1800   to obtain the correct year add 1800 to the char.
      unsigned char  observation_time;
      unsigned char  miss_days_critrn;  // The missing days criterion is 9; a month is valid with up to 9 missing days.
      unsigned char  miss_mons_critrn;  // The missing months criterion is 0; a year is valid only if there are no months missing or invalid.
      unsigned char  filler;
      unsigned char  state_FIPS; // Earth info state code (The State char contains the state FIPS code)
      unsigned char  year_1800;        // offset from 1800   to obtain the correct year add 1800 to the char.
      // Year is the year of the current record.
      int16          record_years;
      float32        percent_coverage;
      float32        elevation;
      int16          data[12][31]; // Row major order (the second element increments to 31 before the first element advances to 2.).
      // Data values are exported in imperial units of measurement only,
      // data values for Prcp and Evap are in hundredths of an inch;
      // data values for Snow are in tenths of an inch; and,
      // data values for TMax and TMin are in degrees Fahrenheit.
      // Data values that are trace amounts are exported as -8194, and no flag is exported.
      // Fields containing NOVALUEs are exported as -8193.
      // NOVALUEs, -8193, are written both for missing daily observations and for month ends in the short months.
      // The value for "trace" is -8194.
   };

public:
   EarthInfo_daily_binary_UED_convertor(int argc, char *argv[]);
   float32 deg_minute_to_dec_deg(const char * deg_minute_str) const;

   bool import_EarthInfo_daily_binary_record(EarthInfo_daily_binary_record &raw_record);
   virtual uint32 perform_import();
   virtual uint32 perform_export();
};

float32 EarthInfo_daily_binary_UED_convertor::deg_minute_to_dec_deg(const char * deg_minute_str) const
{
   int16 deg_minute = atoi(deg_minute_str);
   float32 deg = deg_minute/100;
   float32 min = deg_minute % 100;
   float32 dec_deg = min / 60.0  + deg;
   return dec_deg;
};

bool EarthInfo_daily_binary_UED_convertor::import_EarthInfo_daily_binary_record
(EarthInfo_daily_binary_record &raw_record)
{
   uint16 NCDC_state_number = FIPS_to_NCDC_state_number[raw_record.state_FIPS];
   uint16 station_ID        = raw_record.ID;

   char state_number_code[3];
   itoa(NCDC_state_number,state_number_code,10);
   char station_ID_code[6];
   itoa(station_ID,station_ID_code,10);
   Ustring coopid; // we convert
   if (strlen(state_number_code)==1)   coopid.append("0");
   coopid.append(state_number_code);
   if (strlen(station_ID_code) == 1)    coopid.append("000");
   if (strlen(station_ID_code) == 2)    coopid.append("00");
   if (strlen(station_ID_code) == 3)    coopid.append("0");
   coopid.append(station_ID_code);

   bool UED_file_added_now = false;
   UED_indexed_database *ued_file = get_station_UED_file(station_ID_code,UED_file_added_now);

   if (ued_file)
   {

      if (UED_file_added_now)
      {  // compose location record and append to database
      UED_location_record *loc_rec = new UED_location_record;

      // Warning need to determine how to convert latitude and longitude
      char lat_str[10];  strncpy(lat_str,raw_record.latitude,4); lat_str[4]= 0;
      char long_str[10];  strncpy(long_str,raw_record.longitude,5); long_str[5]= 0;
      float32 latitude = deg_minute_to_dec_deg(lat_str); //
      float32 longitude = deg_minute_to_dec_deg(long_str); //
      loc_rec->set_latitude_dec_deg_32  (latitude);
      loc_rec->set_longitude_dec_deg_32 (longitude);

      float32 elevation_m = foot_to_m(raw_record.elevation);
      loc_rec->set_elevation            (elevation_m);

      loc_rec->set_country_code(840);  // Always in the United states
//       Using country code: set_country_name(const CORN::Ustring &i_country_name)
      loc_rec->set_state_code           (uint16 (raw_record.state_FIPS));
//       Using country code:set_state_name  (const CORN::Ustring &i_state_name)

//    we don't have county codes: set_county_code(uint16 i_county_code)
      Ustring county_name(raw_record.county,0,20);
      county_name.strip(Ustring::Trailing);
      loc_rec->set_county_name (county_name);

      loc_rec->set_station_number(raw_record.ID);
      loc_rec->set_station_ID_code(coopid.c_str());

      Ustring station_name(raw_record.station_name,0,23);
      loc_rec->set_station_name(station_name);
      ued_file->append_record(loc_rec,false);
      };
   };

   UED_data_record_creation_layout *creation = 0;

   float32 data_float[12][31];
   Units_code raw_data_units = 0;
   for (int mi = 0; mi < 12; mi++)
      for (int di = 0; di < 31; di++)
         data_float[mi][di] = raw_record.data[mi][di];
   switch (raw_record.parameter)
   {
      case 4 :  // Tmax
      {  creation = &max_temperature_creation;
         raw_data_units = UE_Farenheit;
         // The data values are not scaled
      } break;
/*NYI
      case ??? :  // Tmin
      {  creation = &min_temperature_creation;
         raw_data_units = UE_Farenheit;
         // The data values are not scaled
      } break;
      case ??? :  // precip
      {  creation = &precipitation_creation;
         raw_data_units = UE_inch;
            for (int mi = 0; mi < 12; mi++)
               for (int di = 0; di < 31; di++)
                  data_float[mi][di] = raw_record.data[mi][di] * 100.0;  //convert from hundredths of an inch
      } break;
      case ??? :  // Tmax
      {  creation = &snow_fall_creation; // Warning I believe this is snow fall and not snow pillow depth
         raw_data_units = UE_inch;
            for (int mi = 0; mi < 12; mi++)
               for (int di = 0; di < 31; di++)
                  data_float[mi][di] = raw_record.data[mi][di] * 10.0; // convert from tenths of an insh
      } break;
*/
      default :
         cerr << "unrecognized parameter encountered:" << raw_record.parameter << endl;
      break;
   };

   Year year = raw_record.year_1800 + 1800;
   for (Month month = 1; month <= 12; month++)
      for (DOM dom = 1; dom <=  date_days_in_month( year, month); dom++)
      {
         CORN::Date set_date(year,month,dom);
         UED_time_query set_query(set_date.get_datetime64(),set_date.get_datetime64(),set_date.get_datetime64(),UED_time_query::at);

         float32 value = data_float[month-1][dom-1];

         CORN::Quality_code attribute = UED_measured;
         int16 raw_quality_code = raw_record.data[month-1][dom-1];
         if (raw_quality_code == -8194) {attribute = CORN::missing_quality; value = 0.0; }; // actually inperceptaible
         if (raw_quality_code == -8193) {attribute = CORN::missing_quality; value = 0.0; };
         bool created = true;
         if (creation)
            ued_file->set_value(value,set_query,raw_data_units,attribute,*creation,created);
      };

   return true; // always return true because there should be no reason not to be successful.
};



uint32 EarthInfo_daily_binary_UED_convertor::perform_import()
{  // Open input file
   ifstream input_file(parameters.target_filename.c_str());   // make sure file type is binary

//   FILE *finput_file;
//   finput_file = fopen(parameters.target_filename.c_str(),"r");


//input_file.seekg(0,istream::end);
//cout << "eofP:" << input_file.tellg() << endl;
//input_file.seekg(0,istream::beg);

   EarthInfo_daily_binary_UED_convertor::EarthInfo_daily_binary_record buffer;

   long record_len = sizeof(EarthInfo_daily_binary_record);
   uint32 raw_records_encountered = 0;
   while (!input_file.eof())
//   while (!feof(finput_file))
   {
//      void *buffer_ptr = (void *)&buffer;
      input_file.read((char *)&buffer,record_len);
//      fread(buffer_ptr,record_len,1,finput_file);
//cout << "state:" << input_file.rdstate();
      // There is only a single record format in this file type
//      import_EarthInfo_daily_binary_record(buffer);
      raw_records_encountered += 1;
//cout << "FP:" << input_file.tellg() << endl;
//cout << "FP:" << ftell(finput_file) << endl;
   };
//   fclose(finput_file);
   return raw_records_encountered;
};

uint32 EarthInfo_daily_binary_UED_convertor::perform_export()
{
   //NYI
   cerr << "This convertor does not currently support UED -> EarthInfo binary format." << endl
        << "EarthInfo does not appear to provide a facility to import this format so an export function will probably never be needed." << endl
        << "Contact Roger Nelson (rnelson@mail.wsu.edu) if you need to export to these formats" << endl;
   press_return_before_exit = true;
};

EarthInfo_daily_binary_UED_convertor::EarthInfo_daily_binary_UED_convertor(int argc, char *argv[])
:  UED_convertor(argc, argv)
{

};

int main(int argc, char *argv[])
{
   EarthInfo_daily_binary_UED_convertor convertor(argc,argv);
   int result =  convertor.convert();
   convertor.notify_climgen();
   return result;
};

