
// Format described in  CS_Suite_4\UED\convert\format\description\SAIH_INM_CHE.txt

#include <UED/convert/convertor.h>
#include <ued/datasetrec.h>
#include <UED/UED.h>
#include <UED/locrec.h>
#include <corn/datetime/datetime64.h>
#include <corn/datetime/date.h>
#include <corn/datetime/time.h>


class INM_CHE_UED_convertor
: public UED_convertor
{

   enum Record_format
   {  UNRECOGNIZED_FORMAT
   ,  INM_T1_MAX_TEMPERATURE     //
   ,  INM_T2_MIN_TEMPERATURE     //
   ,  INM_P1_PRECIPITATION       //
   ,  INM_P2_METEO               //
   ,  INM_DTS_MAX_TEMPERATURE    // DTS is because this code prefixed all the filenames
   ,  INM_DTS_MIN_TEMPERATURE    // DTS is because this code prefixed all the filenames
   ,  INM_DTS_PRECIPITATION      // DTS is because this code prefixed all the filenames
   ,  INM_DTS_STATIONS           // DTS is because this code prefixed all the filenames
   ,  INM_CHE_PRECIPITATION      //
   };

   struct INM_T_or_P_header_raw
   {  // Holerinth layout
      char  meteo_record_type;
      char  meteo_record_subtype;
      char  station_ID[5];
      // The station ID is composed of three fields  BNNN?
      // The first character is the river basin number
      // the next three characters are the station number and
      // the last character (I don't know) is often blank, I have also seen 'E'
      char  year[2];
      char  month[2];  // zero filled
      char  space2;
      char  decenas;   // 1 = days 1 to 10, 2 = days 11 to 20, 3 = 21 to 28,30 or 31
   };

   struct INM_T1_or_T2_temperature_record_body_raw
   {
      char  daily_value[11][5];  // space filled  (10 daily values)
                                 // Both temperature and precip data is left justified
                                 // The temperature data uses all 5 character spaces
      char  checksum[5];
   };
   struct INM_P1_precipitation_record_body_raw
   {  char daily_value[11][5];  // the precipitation data uses 4 character spaces with a following space tenth of a mm
      char checksum[4];
   };
   struct INM_P2_meteo_record_body_raw
   {  char meteo_code[11][6];
   };

   struct INM_T1_or_T2_temperature_record_raw
   {
      INM_T_or_P_header_raw            header;
      INM_T1_or_T2_temperature_record_body_raw  body;
   };
   struct INM_P1_precipitation_record_raw
   {
      INM_T_or_P_header_raw              header;
      INM_P1_precipitation_record_body_raw  body;
   };

   struct INM_P2_meteo_record_raw
   {
      INM_T_or_P_header_raw              header;
      INM_P2_meteo_record_body_raw          body;
   };

   //--------------------------------------------------------------------

   struct  INM_DTS_record_header_raw
   {
      char variable_code[6];
      char  station_ID[5];
      // The station ID is composed of three fields  BNNN?
      // The first character is the river basin number
      // the next three characters are the station number and
      // the last character (I don't know) is often blank, I have also seen 'E'
      char year[4];
      char month[2];
      char decenas;
   };

   struct INM_DTS_temperature_record_body_raw
   {
      char daily_value[11][4];
      char checksum[5];
   };

   struct INM_DTS_precipitation_wind_direction_pair_raw
   {  char precipitation[5];
      char wind_direction[2];
   };

   struct INM_DTS_precipitation_record_body_raw
   {
      INM_DTS_precipitation_wind_direction_pair_raw daily_pair[11];
      char checksum[6];
   };

   struct INM_DTS_temperature_record_raw
   {
      INM_DTS_record_header_raw            header;
      INM_DTS_temperature_record_body_raw   body;
   };

   class INM_header
   {
   public:
      Ustring  variable_code;   // INM 2 character code
      Ustring  station_ID;
      Year     year;
      Month    month;
      int /*uint8*/    decenas;
   public:
      INM_header(INM_T_or_P_header_raw       &header_raw);
      INM_header(INM_DTS_record_header_raw   &header_raw);
   };

   class INM_decena_data
   {
   public:
      float32     Xvalue[11];       // In raw units
      int16       checksum;         // The value read in (in raw units)
      int16       checksum_tally;   // Calculated value
      CORN::Quality_code quality[11];

      Units_code  raw_units;
   public:
      INM_decena_data(INM_T1_or_T2_temperature_record_body_raw  &body_raw,Units_code _raw_units);
      INM_decena_data(INM_P1_precipitation_record_body_raw      &body_raw,Units_code _raw_units);
      INM_decena_data(INM_DTS_temperature_record_body_raw       &body_raw,Units_code _raw_units);
      INM_decena_data(bool precipitation  // false is windspeed
         ,INM_DTS_precipitation_record_body_raw     &body_raw,Units_code _raw_units);

      bool checksum_valid() const;
   private:
      void clear();
   };

   //--------------------------------------------------------------------
   struct CHE_record_header_raw
   {
      char variable_code;
      char station_ID[5];
      char time_step;
      char unknown_code;
      char measurement;
      char units[2];
      char decimal_points;
      char year[2];
      char month[2];
   };

   //--------------------------------------------------------------------


   struct INM_station_identification_raw
   {  // It appears the river basin number and station_ID combined make the station code
      char river_basin_number;            // River basin number
      char station_ID[4];                 // Station ID
      char station_name[50];              // Station name
      char municipio_name[30];            // Municipio name (county scale)
      char provincia_name[12];            // Province name
      char meteologic_center_name[20];    // Meteorologic center
      char station_type_actuale[9];       // Station type (current?)
      char station_type_antiguos[9];      // Station time (previous?)
      char subcatchment_code[4];          // Sub catchment code
      char longitude_degrees[2];          // Coordinates longitude
      char longitude_minutes[2];
      char longitude_seconds[2];          // 1=East  2 = West
      char longitude_orientation;
      char latitude_degrees[2];           // Coordinates latitude
      char latitude_minutes[2];
      char latitude_seconds[2];
      // I don't think latitude had north south orientation, everything is north
      char altitude[4];                   // Altitude
      char barometric_reference_level[4]; // Reference barometric level
      char map_50000_number[4];           // Location in map as scale 1/50000
      char map_200000_number[3];          // Location in map as scale 1/200000
      char category[3];                   // Station category
      char functioning;                   // Functioning indicator (S-Yes N-No)
   };


private: // Buffers
#ifdef OBSOLETE
050329 now using INM_decena_data
   // The precipitation and meteo records always come in pairs
   // with 'P1' type followed by 'P2'
   INM_P1_precipitation_record_raw           last_P1_precipitation_record;
   INM_P2_meteo_record_raw                   last_P2_meteo_record;
   // Temperature records aways come in pairs
   // with 'T1' type followed by 'T1'
   INM_T1_or_T2_temperature_record_raw       last_T1_temperature_max_record;
   INM_T1_or_T2_temperature_record_raw       last_T2_temperature_min_record;

#endif

public:

   INM_CHE_UED_convertor(int argc, char *argv[]);

   virtual int perform_import();
   virtual int perform_export();
   // both import and export return 0 if no errors encountered otherwise the error code.
private:
   bool import_record_INM(Record_format format,CORN::Ustring /*const char **/&raw_record,INM_T_or_P_header_raw &record_header);

   bool import_record_DTS_max_temperature (CORN::Ustring &raw_record);
   bool import_record_DTS_min_temperature (CORN::Ustring &raw_record);
   bool import_record_DTS_precipitation   (CORN::Ustring &raw_record);
   bool import_record_DTS_stations        (CORN::Ustring &raw_record);
   bool import_record_CHE_precipitation   (CORN::Ustring &raw_record);

   datetime64 get_record_datetime64(Year year,Month month,uint8 decenas,uint8   i) const;
   datetime64 get_record_datetime64(INM_T_or_P_header_raw record_header,int i);
   float32 get_INM_P1_precip_value_mm(INM_P1_precipitation_record_body_raw &precipitation_body,int i);
   float32 get_INM_Tx_temperature_C(INM_T1_or_T2_temperature_record_body_raw &temperature_body, int i);

   bool check_last_precipitation_record_checksum() const;
   bool check_temperature_record_checksum(INM_T1_or_T2_temperature_record_body_raw &temperature_body) const;

   Record_format  identify_record_format(const char *raw_record_c_str);

   bool set_UED_with_decena_data(UED_indexed_database &ued_file,const INM_header &header,const INM_decena_data &decena_data,const UED_data_record_creation_layout &creation_layout);
};

INM_CHE_UED_convertor::INM_CHE_UED_convertor(int argc, char *argv[])
:  UED_convertor(argc, argv)
{

};


Record_format  INM_CHE_UED_convertor::identify_record_format(const char *raw_record_c_str)
{
   Record_format format = UNRECOGNIZED_FORMAT;
         if (strncmp(raw_record_c_str,"T1",2) == 0)      format = INM_T1_MAX_TEMPERATURE;
   else  if (strncmp(raw_record_c_str,"T2",2) == 0)     format = INM_T2_MIN_TEMPERATURE;
   else  if (strncmp(raw_record_c_str,"P1",2) == 0)      format = INM_P1_PRECIPITATION;
   else  if (strncmp(raw_record_c_str,"P2",2) == 0)      format = INM_P2_METEO;
   else  if (strncmp(raw_record_c_str,"020101",6) == 0)  format = INM_DTS_MAX_TEMPERATURE;
   else  if (strncmp(raw_record_c_str,"020102",6) == 0)  format = INM_DTS_MIN_TEMPERATURE;   // WARNING I DON'T KNOW THIS YET
   else  if (strncmp(raw_record_c_str,"030201",6) == 0)  format = INM_DTS_PRECIPITATION;
   else  if ((strlen(raw_record_c_str) == 171) && ((raw_record_c_str[170] == 'S') || (raw_record_c_str[170] == 'N')))   format = INM_DTS_STATIONS;
   else  if ((raw_record_c_str[0] == 'P') && (raw_record_c_str[16] == ' '))                                       format = INM_CHE_PRECIPITATION;
   return format;
};


INM_header::INM_header(INM_T_or_P_header_raw       &header_raw)
{
   char variable_code_cstr[10];
   variable_code_cstr[0] = header_raw.meteo_record_type;
   variable_code_cstr[1] = header_raw.meteo_record_subtype;
   variable_code_cstr[2] = 0;
   variable_code.assign(variable_code_cstr);

   char station_ID_cstr[10];
   strncpy(station_ID_cstr,header_raw.station_ID,5);
   station_ID_cstr[5] = 0;
   if (station_ID_cstr[4] ==' ')  station_ID_cstr[4] = 0;
   station_ID.assign(station_ID_cstr);
   station_ID.strip();

   year = (int)(header_raw.year[0] - '0') * 10+
          (int)(header_raw.year[1] - '0');
   year += 1900;

   month=
                (  (header_raw.month[0] == ' ') // Some records use leading space and some use leading 0
                  ? 0
                  : (int)(header_raw.month[0] - '0') * 10
                  )
               +(int)(header_raw.month[1] - '0');
   decenas=(int)(header_raw.decenas - '0');
};


INM_header::INM_header(INM_DTS_record_header_raw   &header_raw)
{
   char variable_code_cstr[10];
   strncpy(variable_code_cstr,header_raw.variable_code,6);
   variable_code_cstr[6] = 0;
   variable_code.assign(variable_code_cstr);

   char station_ID_cstr[10];
   strncpy(station_ID_cstr,header_raw.station_ID,5);
   station_ID_cstr[5] = 0;
   if (station_ID_cstr[4] ==' ')  station_ID_cstr[4] = 0;
   station_ID.assign(station_ID_cstr);
   station_ID.strip();

   char year_cstr[10];
   strncpy(year_cstr,header_raw.year,4);
   year_cstr[4] = 0;
   year = atoi(year_cstr);

   month=
                (  (header_raw.month[0] == ' ') // Some records use leading space and some use leading 0
                  ? 0
                  : (int)(header_raw.month[0] - '0') * 10
                  )
               +(int)(header_raw.month[1] - '0');
   int decenas_int  =  (int)(header_raw.decenas - '0');
   decenas=decenas_int;
};


/*NYI
INM_header::INM_header(INM_DTS_record_header_raw   &header_raw)
{
   NYI

};
*/

bool INM_decena_data::checksum_valid() const
{
   return checksum == checksum_tally;
};

INM_decena_data::INM_decena_data
(INM_T1_or_T2_temperature_record_body_raw  &body_raw,Units_code _raw_units)
: raw_units(_raw_units)
{
   clear();
   char raw_value_cstr[10];
   for (int i = 0; i < 11; i++)
   {
      strncpy(raw_value_cstr,body_raw.daily_value[i],5);
      raw_value_cstr[5] = 0;
      int temperature = atoi(raw_value_cstr);
      Xvalue[i] = temperature;
      if (temperature == 1000)
      {  // 1000 appears to be a marker probably for missing data
         quality[i] = CORN::missing_quality;
      }
      else
      {  quality[i] =  UED_measured;
         checksum_tally += temperature;   // dont checksum missing values
      }
      // I haven't figured out exactly why the checksum fails with some negative numbers
      // They provided no documentation of this format checksums
      // May be they don't sum negative numbers.
   };
   strncpy(raw_value_cstr,body_raw.checksum,5);
   checksum = atoi(raw_value_cstr); // in tenth of a degree celcius
};

INM_decena_data::INM_decena_data
(INM_P1_precipitation_record_body_raw      &body_raw,Units_code _raw_units)
: raw_units(_raw_units)
{
   clear();
   char raw_value_cstr[10];
   for (int i = 0; i < 11; i++)
   {
      strncpy(raw_value_cstr,body_raw.daily_value[i],5);
      raw_value_cstr[5] = 0;
      int precip_mm10 = atoi(raw_value_cstr); // in tenth of a millimeter
      Xvalue[i] = precip_mm10;
      // Warning, there may be maker values for missing data (these are not documented)
      // I am presuming negative values are missing
      if (precip_mm10 < 0)
         quality[i] = CORN::missing_quality;
      else
      {  // also presuming that negative (missing values are not checksumed)
         quality[i] =  UED_measured;
         checksum_tally += precip_mm10;
      };
   };
   strncpy(raw_value_cstr,body_raw.checksum,5);
   checksum = atoi(raw_value_cstr); // in tenth of a millimeter
};

INM_decena_data::INM_decena_data
(INM_DTS_temperature_record_body_raw       &body_raw,Units_code _raw_units)
: raw_units(_raw_units)

{
   clear();
   char raw_value_cstr[10];
   for (int i = 0; i < 11; i++)
   {
      strncpy(raw_value_cstr,body_raw.daily_value[i],4);
      raw_value_cstr[5] = 0;
      int temperature = atoi(raw_value_cstr); // in tenth of a degree celcius
      Xvalue[i] = temperature;
      if (temperature >= 1000)  // presuming large values are missing (missing values are not checksumed)  (the other format uses 1000 raw value a missing data marker)
         quality[i] = CORN::missing_quality;
      else
      {
         quality[i] =  UED_measured;
         checksum_tally += temperature;
      };
   };
   strncpy(raw_value_cstr,body_raw.checksum,5);
   checksum = atoi(raw_value_cstr); // in tenth of a degree celcius
};

INM_decena_data::INM_decena_data
(bool precipitation  // false is windspeed
,INM_DTS_precipitation_record_body_raw     &body_raw,Units_code _raw_units)
: raw_units(_raw_units)

{
   clear();
   char raw_value_cstr[10];
   for (int i = 0; i < 11; i++)
   {
      if (precipitation)
      {
         strncpy(raw_value_cstr,body_raw.daily_pair[i].precipitation,5);
         int precip_mm10 = atoi(raw_value_cstr); // in tenth of a millimeter
         Xvalue[i] = precip_mm10;
         quality[i] =  UED_measured;
         if (precip_mm10 >= 0)  // Negative values are special codes
            checksum_tally += precip_mm10;
         else
         {
             if (precip_mm10 == -1)  // missing
                quality[i] = CORN::missing_quality;
             if (precip_mm10 == -3)  //impreceptiable
                 Xvalue[i] = 0.0001;   // Just to indicate that it is a small value
//NYI       if (precip_mm10 == -4)  precipitation accumulatored (don't know what this means)
            if (precip_mm10 == -888) // quality is erroneous
                quality[i] = UED_not_valid;
         };
      }
      else
      {
         strncpy(raw_value_cstr,body_raw.daily_pair[i].wind_direction,2);
         int wind_dir_code = atoi(raw_value_cstr);;
         quality[i] =  UED_measured;

         switch (wind_dir_code)
         {
            case  0 : Xvalue[i] = 0.0; quality[i] = CORN::missing_quality;  break;
            case 88 : Xvalue[i] = 0.0;  break;  //calm  should set a data quality
            case 99 : Xvalue[i] = 0.0;  break; // variable

            case  4 : Xvalue[i] =  45;  break; // NE
            case  9 : Xvalue[i] =  90;  break; //  E
            case 14 : Xvalue[i] = 135;  break; //  SE
            case 18 : Xvalue[i] = 180;  break; //  S
            case 23 : Xvalue[i] = 225;  break; //  SW
            case 27 : Xvalue[i] = 270;  break; //  W
            case 32 : Xvalue[i] = 315;  break; //  NW
            case 36 : Xvalue[i] = 360;  break; //  N
            default : Xvalue[i] = wind_dir_code * 10; break; // Just in case they allow other values
            break;
         };
         // checksum is only applied to precipitation value
      }
   };


   strncpy(raw_value_cstr,body_raw.checksum,6);
   checksum = atoi(raw_value_cstr); // in tenth of a millimeter

   // RLN: This particular format includes error maker in check sum (at least the -3  value);
   // If there are only -3 values then the checksum is set to -3 no matter how many -3 value occur
   // We simply accept negative checksum what ever it is (because I can't figure out exactly how their checksums work.
   if (checksum < 0) checksum_tally = checksum;


};

void INM_decena_data::clear()
{
   checksum = 0;
   checksum_tally = 0;
   for (int i = 0; i < 11; i++)
   {  Xvalue[i] = 0;
      quality[i] =  UED_unknown_quality;
   };
};



bool INM_CHE_UED_convertor::set_UED_with_decena_data(UED_indexed_database &ued_file,const INM_header &header,const INM_decena_data &decena_data,const UED_data_record_creation_layout &creation_layout)
{
   bool result = false;
   if (decena_data.checksum_valid())
   {
      for (int i = 0; i < 11; i++)
      {
         datetime64 set_date = get_record_datetime64(header.year,header.month,header.decenas,i);
         // returns a negative number for short records
         if (set_date > 0)
         {
            UED_time_query_single_date set_date_query(set_date);
            float32 value = decena_data.Xvalue[i];
//            CORN::Quality_code attribute = UED_measured;
            Units_code units = decena_data.raw_units;
            bool created;
            ued_file.set_value(value,set_date_query,units,decena_data.quality[i],creation_layout,created);
         }
      };
      result = true;
   }
   else
   {
      cerr << "Warning invalid checksum or record not formatted correctly";
      cerr << " in file:" << parameters.target_filename<< " record:";
      cerr << "variable="<<header.variable_code << " station=" << header.station_ID << " year:="<<header.year << "month:" << (int)header.month << "decenas:" << (int)header.decenas;
      cerr <<  " (" <<decena_data.checksum<< "<>" << decena_data.checksum_tally << ")";
      cerr << endl;
      press_return_before_exit = true;
      result =false;
   };
   return result;
};

bool INM_CHE_UED_convertor::import_record_INM(Record_format format, CORN::Ustring /*const char **/&Xraw_record,INM_T_or_P_header_raw &record_header_raw)
{
   INM_header header(record_header_raw);
   bool added_now = false;
   UED_indexed_database *ued_file = get_station_UED_file(header.station_ID.c_str(),added_now);

   switch (format)
   {


            case INM_P1_PRECIPITATION :
            {
               INM_P1_precipitation_record_body_raw           P1_precipitation_record_body;
               Xraw_record.resize(sizeof(INM_P1_precipitation_record_raw));
               const char *record_cstr =  Xraw_record.c_str();
               const char *start_of_body_raw = record_cstr + sizeof(INM_T_or_P_header_raw);
               memcpy((void *)&P1_precipitation_record_body
                     ,(void *)start_of_body_raw
                     ,sizeof(INM_P1_precipitation_record_body_raw));
               INM_decena_data precip_decena_data(P1_precipitation_record_body,UC_tenth_mm);
               set_UED_with_decena_data(*ued_file,header,precip_decena_data,precipitation_creation);
            } break;
            case INM_P2_METEO :
            {
/*
               // We currently don't do anything with the P2 record
               if (check_last_precipitation_record_checksum())
               {
                  for (int i = 0; i < 11; i++)
                  {
                     datetime64 set_date = get_record_datetime64(record_header,i);
                     // returns a negative number for short records
                     if (set_date > 0)
                     {
                        UED_time_query_single_date set_date_query(set_date);
                        float32 precip_mm = get_INM_P1_precip_value_mm(last_P1_precipitation_record.body,i);
                        CORN::Quality_code attribute = UED_measured;
                        Units_code units = UC_mm;
                        bool created;
                        ued_file->set_value(precip_mm,set_date_query,units,attribute,precipitation_creation,created);
                     };
                  };
               } else
               {
                  cerr << "Warning invalid checksum or precipitation record not formatted correctly";
                  cerr << " in file:" << target_filename<< " record:";
                  for (int i = 0; i < sizeof(INM_T_or_P_header_raw); i++)
                     cerr << Xraw_record[i];
                  cerr << endl;
               };
*/
            } break;
         case INM_T1_MAX_TEMPERATURE:
         {
            INM_T1_or_T2_temperature_record_body_raw  T1_max_temperature_record_body;
            Xraw_record.resize(sizeof(INM_T1_or_T2_temperature_record_raw));
            const char *record_cstr =  Xraw_record.c_str();
            const char *start_of_body_raw = record_cstr + sizeof(INM_T_or_P_header_raw);
            memcpy((void *)&T1_max_temperature_record_body
                     ,(void *)start_of_body_raw
                     ,sizeof(INM_T1_or_T2_temperature_record_body_raw));
            INM_decena_data Tmax_decena_data(T1_max_temperature_record_body,UC_decicelcius);
            set_UED_with_decena_data(*ued_file,header,Tmax_decena_data,max_temperature_creation/*temperature_max_creation*/);

         } break;
         case INM_T2_MIN_TEMPERATURE :
         {
            INM_T1_or_T2_temperature_record_body_raw  T2_max_temperature_record_body;
            Xraw_record.resize(sizeof(INM_T1_or_T2_temperature_record_raw));
            const char *record_cstr =  Xraw_record.c_str();
            const char *start_of_body_raw = record_cstr + sizeof(INM_T_or_P_header_raw);
            memcpy((void *)&T2_max_temperature_record_body
                     ,(void *)start_of_body_raw
                     ,sizeof(INM_T1_or_T2_temperature_record_body_raw));
            INM_decena_data Tmin_decena_data(T2_max_temperature_record_body,UC_decicelcius);
            set_UED_with_decena_data(*ued_file,header,Tmin_decena_data,min_temperature_creation/*temperature_min_creation*/);
         } break;
   };
   return true;
};

bool INM_CHE_UED_convertor::import_record_DTS_max_temperature(CORN::Ustring &raw_record)
{
   bool result = false;
   INM_DTS_record_header_raw record_header_raw;
   memcpy((void *)&record_header_raw,raw_record.c_str(),sizeof(INM_DTS_record_header_raw));
   INM_header header(record_header_raw);

   INM_DTS_temperature_record_body_raw   DTS_temperature_record_body;
   int record_size = sizeof(INM_DTS_record_header_raw) +  sizeof(INM_DTS_temperature_record_body_raw) ;
   raw_record.resize(record_size);
   const char *record_cstr =  raw_record.c_str();
   const char *start_of_body_raw = record_cstr + sizeof(INM_DTS_record_header_raw);
   memcpy((void *)&DTS_temperature_record_body
   ,(void *)start_of_body_raw
   ,sizeof(INM_DTS_temperature_record_body_raw));
   INM_decena_data max_temp_decena_data(DTS_temperature_record_body,UC_decicelcius);
   bool added_now = false;
   UED_indexed_database *ued_file = get_station_UED_file(header.station_ID.c_str(),added_now);
   if (ued_file && (max_temp_decena_data.checksum_valid()))
         result = set_UED_with_decena_data(*ued_file,header,max_temp_decena_data,max_temperature_creation/*temperature_max_creation*/);
   else
      {
         cerr << "Warning invalid checksum or record not formatted correctly";
         cerr << " in file:" << parameters.target_filename<< " record:";
         cerr << "variable="<<header.variable_code << " station=" << header.station_ID << " year:="<<header.year << "month:" << (int)header.month << "decenas:" << (int)header.decenas;
         cerr <<  " (" <<max_temp_decena_data.checksum<< "<>" << max_temp_decena_data.checksum_tally << ")";
         cerr << endl;
         press_return_before_exit = true;
      };

   return result;  // returns true if successful
};
bool INM_CHE_UED_convertor::import_record_DTS_min_temperature(CORN::Ustring &raw_record)
{
   bool result = false;
   INM_DTS_record_header_raw record_header_raw;
   memcpy((void *)&record_header_raw,raw_record.c_str(),sizeof(INM_DTS_record_header_raw));
   INM_header header(record_header_raw);

   INM_DTS_temperature_record_body_raw   DTS_temperature_record_body;
   int record_size = sizeof(INM_DTS_record_header_raw) +  sizeof(INM_DTS_temperature_record_body_raw) ;
   raw_record.resize(record_size);

   const char *record_cstr =  raw_record.c_str();
   const char *start_of_body_raw = record_cstr + sizeof(INM_DTS_record_header_raw);
   memcpy((void *)&DTS_temperature_record_body
   ,(void *)start_of_body_raw
   ,sizeof(INM_DTS_temperature_record_body_raw));
   INM_decena_data min_temp_decena_data(DTS_temperature_record_body,UC_decicelcius);
   bool added_now = false;
   UED_indexed_database *ued_file = get_station_UED_file(header.station_ID.c_str(),added_now);
   if (ued_file && (min_temp_decena_data.checksum_valid()))
         result = set_UED_with_decena_data(*ued_file,header,min_temp_decena_data,min_temperature_creation/*temperature_min_creation*/);
   else
      {
         cerr << "Warning invalid checksum or record not formatted correctly";
         cerr << " in file:" << parameters.target_filename<< " record:";
         cerr << "variable="<<header.variable_code << " station=" << header.station_ID << " year:="<<header.year << "month:" << (int)header.month << "decenas:" << (int)header.decenas;
         cerr <<  " (" <<min_temp_decena_data.checksum<< "<>" << min_temp_decena_data.checksum_tally << ")";
         cerr << endl;
         press_return_before_exit = true;
      };

   return result;  // returns true if successful
};
bool INM_CHE_UED_convertor::import_record_DTS_precipitation(CORN::Ustring &raw_record)
{
   bool result = false;
   INM_DTS_record_header_raw record_header_raw;
   memcpy((void *)&record_header_raw,raw_record.c_str(),sizeof(INM_DTS_record_header_raw));
   INM_header header(record_header_raw);

   INM_DTS_precipitation_record_body_raw   DTS_precipitation_record_body;
   int record_size = sizeof(INM_DTS_record_header_raw) + sizeof(INM_DTS_precipitation_record_body_raw);
   raw_record.resize(record_size);
   const char *record_cstr =  raw_record.c_str();
   const char *start_of_body_raw = record_cstr + sizeof(INM_DTS_record_header_raw);
   memcpy((void *)&DTS_precipitation_record_body
   ,(void *)start_of_body_raw
   ,sizeof(INM_DTS_precipitation_record_body_raw));
   bool added_now = false;
   UED_indexed_database *ued_file = get_station_UED_file(header.station_ID.c_str(),added_now);
   // The precipitation and wind direction data are in the same record.
   { // First extract the precipitation data
      INM_decena_data precip_decena_data(true,DTS_precipitation_record_body,UC_tenth_mm);
      if (ued_file && (precip_decena_data.checksum_valid()))
            result = set_UED_with_decena_data(*ued_file,header,precip_decena_data,precipitation_creation);
      else
      {
         cerr << "Warning invalid checksum or record not formatted correctly";
         cerr << " in file:" << parameters.target_filename<< " record:";
         cerr << "variable="<<header.variable_code << " station=" << header.station_ID << " year:="<<header.year << "month:" << (int)header.month << "decenas:" << (int)header.decenas;
         cerr <<  " (" <<precip_decena_data.checksum<< "<>" << precip_decena_data.checksum_tally << ")";
         cerr << endl;
         press_return_before_exit = true;
      };
   };
#ifdef NYI
   { // now the wind direction
      INM_decena_data wind_dir_decena_data(false,DTS_precipitation_record_body,UC_degree_from_north);
      if (ued_file && (wind_dir_decena_data.checksum_valid()))
            result = set_UED_with_decena_data(*ued_file,header,wind_dir_decena_data,wind_direction_creation);
   };
#endif
   return result;  // returns true if successful
};
bool INM_CHE_UED_convertor::import_record_DTS_stations(CORN::Ustring &raw_record)
{
   // instanciated location record
   // get the ued file for the station code
   // append location record

   INM_station_identification_raw  station_rec_raw;
   memcpy((void *)&station_rec_raw,raw_record.c_str(),sizeof(INM_station_identification_raw));

   char station_ID_cstr[10];
   strncpy(station_ID_cstr,raw_record.c_str(),5);
   if (station_ID_cstr[4] ==' ')  station_ID_cstr[4] = 0;
   CORN::Ustring  station_ID_code(station_ID_cstr,0,5);

   station_ID_code.strip(CORN::Ustring::Trailing,' ');


   UED_location_record *ued_loc_rec = new UED_location_record();

   // No station number set_station_number()
   ued_loc_rec->set_station_ID_code(station_ID_code.c_str());
   ued_loc_rec->set_station_name(CORN::Ustring(station_rec_raw.station_name,0,50));
   ued_loc_rec->set_county_name(CORN::Ustring(station_rec_raw.municipio_name,0,30));
   ued_loc_rec->set_state_name(CORN::Ustring(station_rec_raw.provincia_name,0,12));
   ued_loc_rec->set_country_name("España");

   char int_cstr[10];
   int degrees_int;  float32 degrees;
   int minutes_int;  float32 minutes;
   int seconds_int;  float32 seconds;
   strncpy(int_cstr,station_rec_raw.longitude_degrees,2); int_cstr[2] = 0;   degrees_int = atoi(int_cstr); degrees = degrees_int;
   strncpy(int_cstr,station_rec_raw.longitude_minutes,2); int_cstr[2] = 0;   minutes_int = atoi(int_cstr); minutes = minutes_int;
   strncpy(int_cstr,station_rec_raw.longitude_seconds,2); int_cstr[2] = 0;   seconds_int = atoi(int_cstr); seconds = seconds_int;
   if (station_rec_raw.longitude_orientation = '2');  degrees = -degrees;
   ued_loc_rec->set_longitude_DMS( degrees, minutes,  seconds);

   strncpy(int_cstr,station_rec_raw.latitude_degrees,2); int_cstr[2] = 0;   degrees_int = atoi(int_cstr); degrees = degrees_int;
   strncpy(int_cstr,station_rec_raw.latitude_minutes,2); int_cstr[2] = 0;   minutes_int = atoi(int_cstr); minutes = minutes_int;
   strncpy(int_cstr,station_rec_raw.latitude_seconds,2); int_cstr[2] = 0;   seconds_int = atoi(int_cstr); seconds = seconds_int;
   // This format has no latitude orientation
   ued_loc_rec->set_latitude_DMS( degrees, minutes,  seconds);

   int elevation_int=0; float elevation = 0; // m
   strncpy(int_cstr,station_rec_raw.altitude,4);   elevation_int = atoi(int_cstr); elevation = elevation_int;
   ued_loc_rec->set_elevation(elevation);

   // The following infomration is not currently saved in the UED location record

   //   char meteologic_center_name[20];    // Meteorologic center
   //   char station_type_actuale[9];       // Station type (current?)
   //   char station_type_antiguos[9];      // Station time (previous?)
   //   char subcatchment_code[4];          // Sub catchment code
   //   char barometric_reference_level[4]; // Reference barometric level
   //   char map_50000_number[4];           // Location in map as scale 1/50000
   //   char map_200000_number[4];          // Location in map as scale 1/200000
   //   char category[3];                   // Station category
   //   char functioning;                   // Functioning indicator (S-Yes N-No)

   bool added_now;
   UED_indexed_database *ued_file = get_station_UED_file(station_ID_code.c_str(),added_now);
   if (ued_file)
   {  ued_file->append_record(ued_loc_rec,false);
      generate_climgen_location(*ued_loc_rec,ued_file->get_file_name());
   };
   return true;   // NYI
};

bool INM_CHE_UED_convertor::import_record_CHE_precipitation   (CORN::Ustring &raw_record)
{
   bool result = false;
   CHE_record_header_raw  header_raw;
   memcpy((void *)&header_raw,raw_record.c_str(),sizeof(CHE_record_header_raw));
   const char *record_cstr =  raw_record.c_str();
   int year = (int)(header_raw.year[0] - '0') * 10+
          (int)(header_raw.year[1] - '0');
   year += 1900;

   int month=   (  (header_raw.month[0] == ' ') // Some records use leading space and some use leading 0
                  ? 0
                  : (int)(header_raw.month[0] - '0') * 10
                  )
               +(int)(header_raw.month[1] - '0');

   char data_raw[31][7];
   int dim =  date_days_in_month(year,month) * 7;
   int record_data_length = dim;
   const char *start_of_body_raw = record_cstr + sizeof(CHE_record_header_raw);
   memcpy((void *)&data_raw
   ,(void *)start_of_body_raw
   ,record_data_length);


/* Header raw format
      char variable_code;
      char station_ID[5];
      char time_step;
      char unknown_code;
      char measurement;
      char units[2];
      char decimal_points;
      char year[2]
      char month[2]
*/

   // Currently only precipitation data is known to be in this format.

   char station_ID_cstr[10];
   strncpy(station_ID_cstr,header_raw.station_ID,5); station_ID_cstr[5]=0;
   if (station_ID_cstr[4] == ' ') station_ID_cstr[4] = 0;
   CORN::Ustring station_ID(station_ID_cstr);
   station_ID.strip();

   // Currently presuming units are always millimeters, but should check the header and convert
   Units_code units = ((header_raw.units[0] == 'M') && (header_raw.units[1] == 'M'))
   ? UC_mm
   : UC_mm ;  // Not sure what other units codes there are, presuming this file format only accomodated precipitation

   int decimals = (int)(header_raw.decimal_points - '0');

   bool added_now = false;
   UED_indexed_database *ued_file = get_station_UED_file(station_ID.c_str(),added_now);
   if (ued_file)
   {
      for (DOM dom = 1; dom < dim; dom++)
      {
         int value_int = atoi(data_raw[dom-1]);
         float32 value = value_int;
         if (decimals)  value /= (decimals * 10);

         Date set_date(year,month,dom,D_YMD);
         Time set_time(0.0);
         Date_time_64 set_datetime(set_date,set_time);
         datetime64 set_datetime64 = set_datetime.get_datetime64();
         UED_time_query_single_date set_date_query(set_datetime64);
         CORN::Quality_code attribute = UED_measured;  // There are no known missing data indicators for this format
         bool created;
         ued_file->set_value(value,set_date_query,units,attribute,precipitation_creation,created);
      };
      result = true;
   };
   return result;  // returns true if successful
};



#ifdef OBSOLETE
bool INM_CHE_UED_convertor::check_last_precipitation_record_checksum() const
{
   int precip_sum_mm10 = 0;
   for (int i = 0; i < 11; i++)
   {
      // Not sure if checksum is on all digit or only the last 3
      char precip_cstr[10];
      strncpy(precip_cstr,last_P1_precipitation_record.body.daily_value[i],5);
      precip_cstr[5] = 0;
      int precip_mm10 = atoi(precip_cstr); // in tenth of a millimeter


      precip_sum_mm10 += precip_mm10; // (int)(get_INM_P1_precip_value_mm(last_precipitation_record.body,i) * 10);
   };

   char checksum_cstr[10];
   strncpy(checksum_cstr,last_P1_precipitation_record.body.checksum,5);
   int checksum = atoi(checksum_cstr); // in tenth of a millimeter
   return  checksum == precip_sum_mm10;
};

bool INM_CHE_UED_convertor::check_temperature_record_checksum(INM_T1_or_T2_temperature_record_body_raw &temperature_body) const
{
   bool matches = true;

   int temp_sum = 0;
   for (int i = 0; i < 11; i++)
   {
      char temp_cstr[10];  // checksum is only on the three least significant digits.
      strncpy(temp_cstr,temperature_body.daily_value[i]+2,3);
      temp_cstr[5] = 0;
      int temp_C10 = atoi(temp_cstr); // in tenth of a millimeter
      temp_sum += temp_C10 ;
   };
   char checksum_cstr[10];
   strncpy(checksum_cstr,temperature_body.checksum,5);
   int checksum = atoi(checksum_cstr); // in tenth of a millimeter
   matches = (checksum == temp_sum)
        | (temp_sum < 0);
        // This is kind of a hack, I haven't figured out exactly why the checksum fails with some negative numbers
        // They provided no documentation of this format checksums
   if (!matches)
      cerr << checksum<< ':' << temp_sum<< endl;
   return matches;
};

#endif


datetime64 INM_CHE_UED_convertor::get_record_datetime64
(Year    year
,Month   month
,uint8   decenas
,uint8   i
) const
{
   datetime64 result = 0;
   if ((decenas < 3) && (i == 10))
      result = -1;
      // For decenas 1 and 2 there are only 10 values on the line.
      // so when i = 10 then there is no value to store in the database
   else
   {  // for decenas 3 there could be 8 9 10 or 11 values
      // we check for the number of days in the month
      DOM   dom = (decenas/*(decenas - '0')*/ -1) * 10 + i+1;
      CORN::DOM days_in_month = date_days_in_month(year,month);
      if (dom > days_in_month)
         result = -1.0;
      else
      {
         CORN::Date date(year,month,dom);
         result = date.get_datetime64();
      };
   };
   return result;
};
#ifdef OBSOLETE
now down in INM_decena_data constructor
float32 INM_CHE_UED_convertor::get_INM_P1_precip_value_mm(INM_P1_precipitation_record_body_raw &precipitation_body,int i)
{
   char precip_cstr[10];
   strncpy(precip_cstr,precipitation_body.daily_value[i],5);
   precip_cstr[5] = 0;
   int precip_mm10 = atoi(precip_cstr); // in tenth of a millimeter
   float32 precip_mm = ((float32)precip_mm10)/10.0;
   return precip_mm;
};
#endif


int INM_CHE_UED_convertor::perform_import()
{  // Open input file
   ifstream input_file(parameters.target_filename.c_str());
   CORN::Ustring buffer;
   while (!input_file.eof())
   {  buffer.read_line(input_file);
      if (buffer.length() && (buffer.c_str()[0] != '*'))
      {
         Record_format format = identify_record_format(buffer.c_str());
         switch (format)
         {
            case INM_T1_MAX_TEMPERATURE :
            case INM_T2_MIN_TEMPERATURE :
            case INM_P1_PRECIPITATION   :
            case INM_P2_METEO           :
            {
            INM_T_or_P_header_raw record_header;
            memcpy((void *)&record_header,buffer.c_str(),sizeof(record_header));
            if (  (parameters.station_ID_filter.length() == 0)
                ||(strncmp(record_header.station_ID,parameters.station_ID_filter.c_str(),4) == 0)
                ||(parameters.station_ID_filter == "all")
                )
               import_record_INM(format,buffer,record_header);
            } break;
            case INM_DTS_MAX_TEMPERATURE : import_record_DTS_max_temperature(buffer); break;
            case INM_DTS_MIN_TEMPERATURE : import_record_DTS_min_temperature(buffer); break;
            case INM_DTS_PRECIPITATION   : import_record_DTS_precipitation(buffer);   break;
            case INM_DTS_STATIONS        : import_record_DTS_stations(buffer);        break;
            case INM_CHE_PRECIPITATION   : import_record_CHE_precipitation(buffer);   break;
            default : cerr << "Unrecognized record format:" << buffer /*raw_record_c_str*/ << endl; // Could output line number
                           press_return_before_exit = true;
            break;
         };
      }; // else it is a comment line which we ignore
   };
   return 1;
};

int INM_CHE_UED_convertor::perform_export()
{
   //NYI
   cerr << "This convertor does not currently support UED -> INM, or CHE formats." << endl
        << "Contact Roger Nelson (rnelson@mail.wsu.edu) if you need to export to these formats" << endl;
   press_return_before_exit = true;
};

int main(int argc, char *argv[])
{
// test command lines

// import example\database.ued "example\P759.CON"
// import example\database.ued "example\P759.COM"
// import example\database.ued "example\dts_plu.txt"
// import example\database.ued "example\dts_tmn.txt"
// import example\database.ued "example\dts_tmx.txt"
// import example\database.ued "example\mre_est.txt"
// import example\database.ued "example\P9758DO.txt"
// import example\database.ued "example\P9759DO.txt"

   INM_CHE_UED_convertor convertor(argc,argv);
   int result =  convertor.convert();
   convertor.notify_climgen();
    return result;
};

