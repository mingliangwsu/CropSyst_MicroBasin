#include "UED/convert/NCDC/NCDC_summary_of_the_day_convertor.h"
#include "UED/library/UED.h"
#include "UED/library/timeqry.h"
#include "UED/convert/station_database.h"
#include "corn/string/uiostring.h"
using namespace std;
#include "NCDC_element.h"
#include "NCDC_UED_units_conv.h"
#include "NCDC_UED_flag_conv.h"
/*
As documented by EarthInfo Inc.  NCDC summary of the day export format.

NCDC

The NCDC export format has one record for a month's data, so each station-year contains 12 NCDC records.
The Element Type is "TMAX", "TMIN", "SNOW", "PRCP", or "EVAP".  The Element Unit is degrees Fahrenheit
or inches in hundredths ("F" or "HI").  Note that these are the required units of measurement for NCDC format
data.  If you have switched the units toggle to metric units(Ctrl-U or File|Units Toggle), the values will still be
exported in imperial units.

The NCDC export format exports NCDC State Codes.  NCDC codes vary from the FIPS codes.  If your
software expects FIPS state codes, you will need to alter it to use the NCDC codes.
NOVALUEs are exported as -99999 followed by an "M" flag.  Data values tagged with accumulation flags ("A")
are exported as the value followed by an "A" flag, and data values that are trace amounts are exported as
00000 followed by a "T" flag.

NCDC Daily


Variable Type	Field Name			Offset	Length
char		Record Type (always "DLY")	  0	    3
char		Station ID			  3	    8
char		Element Type			11	    4
char		Element Unit			15	    2
char		Year				17	    4
char		Month				21	    2
char		Filler "9999"			23	    4
char		 # of Values			27	    3
struct		Data Values [31]		30	31 x 12 =372
							Total Length=402

The structure of a Data Values array element is as follows:


Variable Type	Field Name	Offset	Length
char			Day	  0	2
char			Hour	  2	2
char			Sign	  4	1
char			Value	  5	5
char			Flag 1	10	1
char			Flag 2	11	1
					Total Length=12

NCDC Flags and Conventions
Hour always contains ASCII 98.
Flag 1 can contain any of these in ASCII:

A	accumulation; amount reported is an accumulation since last observation
M	missing data.  NOVALUEs are exported as 99999M.
T	trace.  The data value if Flag 1 is T is always 00000, thus the trace amount is 00000T.
blank	flag not needed
Flag 2 only has this possibility in ASCII:

1	valid data element.
*/

// A NCDC file can contain multiple stations
// UED can only store one station so we need to have a
// seperate file for each.
//______________________________________________________________________________
struct Data_values
{
   char day[2];
   char hour[2];
   char sign;
   char value[5];
   char flag1;     // Measurement flag
   char flag2;
};
//______________________________________________________________________________
struct NCDC_summary_of_the_day_format
{
   char record_type[3];
   // The next 8 digits are the station_ID this has been split into two parts
   char cooperative_station_number[6];    // The First 6 digits match the cooperative station number in the sodstn.txt file
   char station_IDb[2];    // Don't know what these to digits represent
   char element_type[4];
   char element_unit[2];
   char year[4];
   char month[2];
   char filler[4];
   char num_values[3];
   struct Data_values data_values[31];
};
//______________________________________________________________________________
class NCDC_summary_of_the_day_element_record
{
public:
   //record type is currently ignored, it is assumed to be dly.
   CORN::Ustring          cooperative_station_number;
   // The next 8 digits are the station_ID this has been split into two parts
   CORN::Ustring          unused_station_IDb;

   NCDC_element_labeled meteorological_element_type_labeled;
   Element              element;

   Units_code           raw_data_units;
   Year                 year;
   Month                month;
   // filler is unused
   // num_values is assumed to always be 31
   struct Data_values data_values[31];
   // This contains one month of data as read from the input file.
public:
   Hour                    hour[32];
   float32                 value[32];
   CORN::Quality_code   ued_quality[32];   // Flag1
// unused always 1 in import   char                    data_quality_flag[32];     // Flag2

public:
   NCDC_summary_of_the_day_element_record(NCDC_summary_of_the_day_format &i_data_buffer);
   // This constructor is used for reading files.
};
//______________________________________________________________________________
NCDC_summary_of_the_day_element_record::NCDC_summary_of_the_day_element_record
(  NCDC_summary_of_the_day_format &data_buffer)
: meteorological_element_type_labeled(PRCP)
,cooperative_station_number((const char *)data_buffer.cooperative_station_number,(size_t)0,(size_t)6)
,unused_station_IDb((const char *)data_buffer.station_IDb,0,2)
,year(0)    // set below
,month(0)   // set below
{
   CORN::Ustring element_str(data_buffer.element_type,0,4);
   meteorological_element_type_labeled.set_label(element_str.c_str());
   CORN::Ustring units_str(data_buffer.element_unit,0,2);
   float32 scale_factor = 1.0;
   bool units_found = false;
   for (int i = 0; element_units_conversion[i].NCDC_units_code && !units_found; i++)
   {  if (element_units_conversion[i].NCDC_units_code == units_str)
      {  raw_data_units = element_units_conversion[i].UED_units_code;
         scale_factor   = element_units_conversion[i].scale_factor;
         units_found = true;
   } }
   CORN::Ustring year_str(data_buffer.year,0,4);
   year = (Year)atoi(year_str.c_str());
   CORN::Ustring month_str(data_buffer.month,0,2);
   month = (Month)atoi(month_str.c_str());
   // filler is unused
   // num_values is assumed to always be 31
   for (DOM dom = 1; dom <= 31; dom++)
   {  CORN::Ustring hr_str(data_buffer.data_values[dom-1].day,0,2);  // hr are not currently used (earth info always exports as 98)
      hour[dom] =  (Hour)atoi(hr_str.c_str());
      switch (data_buffer.data_values[dom-1].flag1)
      {  case 'E' : ued_quality[dom] = UED_estimated; break;
         case 'M' : ued_quality[dom] = CORN::missing_quality;  break;
         // trace case 'T' :
         case 'B' : ued_quality[dom] = UED_estimated; break;
         default :   ued_quality[dom] = UED_measured; break;
      }
      CORN::Ustring value_str(data_buffer.data_values[dom-1].value);
      float32 raw_value = (float32)atoi(value_str.c_str());
      if (data_buffer.data_values[dom-1].sign == '-') raw_value = -raw_value;
      value[dom]  = (float)raw_value * scale_factor;
   }
}
//______________________________________________________________________________
void NCDC_summary_of_the_day_format_convertor::import_record
(NCDC_summary_of_the_day_element_record &element_record
,CORN::OS::Directory_name &ued_file_path)
{
   bool added_just_now;
   Station_database *station_database = provide_station_database(element_record.cooperative_station_number,added_just_now);
   UED_indexed_database *ued_file = &(station_database->ued_file);

      Year  year  = element_record.year;
      Month month = element_record.month;

//cout << '\r' << (int)year << ' ' << (int)month << ' ' <<element_record.meteorological_element_type_labeled.get_label() << "              ";
//cout << (int)year << ' ';

      for (DOM dom = 1; dom <=  date_get_days_in_month( year, month); dom++)
      {  CORN::Date set_date(year,month,dom);
         UED::Time_query_single_date set_query(set_date.get_datetime64());
         bool created;
         CORN::Quality attribute(element_record.ued_quality[dom]);
         UED_data_record_creation_layout *creation = 0;
         switch (element_record.meteorological_element_type_labeled.get())
         {  case  TMAX : creation = &max_temperature_creation;           break;
            case  TMIN : creation = &min_temperature_creation;           break;
            case  SNOW : creation = &snow_fall_creation;                 break;
            case  SNWD : creation = &snow_depth_creation;                break;
            case  TOBS : creation = &instantaneous_temperature_creation; break;
            case  PRCP : creation = &precipitation_creation;             break;
         }

         {//____________________________________________________________________
         // 091027 added validation
         Weather_validator *weather_data_validator = station_database->provide_weather_data_validator();
         if (weather_data_validator)
         {  // Double check data quality for erroneous data that has been marked valid
            CORN::Ustring validation_description;
            CORN::DOY record_doy = set_date.get_DOY();
            if (attribute .is_valid())  element_record.value[dom] = weather_data_validator->validate_float32
                  (record_doy
                  ,element_record.value[dom]
                  ,creation->variable_code
                  ,element_record.raw_data_units
                  ,UT_day
                  ,CORN::measured_quality
                  ,CORN::measured_quality
                  ,attribute
                  ,validation_description);
         }
         }//____________________________________________________________________

         if (creation)
            ued_file->set_value(element_record.value[dom],set_query,element_record.raw_data_units,attribute,*creation,created);
      }
}
//______________________________________________________________________________
nat32 NCDC_summary_of_the_day_format_convertor::perform_import()
{  nat32 record_count = 0;
   // Open input file
   ifstream input_file(parameters.target_filename.c_str());
   NCDC_summary_of_the_day_format data_buffer;
   int buffer_size = sizeof(data_buffer);
   cout << "Reading input file(s):" << endl;
   long buffer_read = 0;
   CORN::UIO_string buffer_str;
   do
   {
      buffer_str.read_line(input_file);
      memcpy((char *)&data_buffer,buffer_str.c_str(),buffer_size);
      buffer_read = buffer_str.length(); // input_file.gcount();
      if (buffer_read == buffer_size)
      {
         NCDC_summary_of_the_day_element_record element_record(data_buffer);
         if (  (parameters.station_IDs_filter.length() == 0)
             ||(parameters.station_IDs_filter.find(element_record.cooperative_station_number.c_str())!=std::string::npos)
             ||(parameters.station_IDs_filter == "all")
             ||(parameters.station_IDs_filter == "")
             )
         {  cout << element_record.cooperative_station_number << '\r';
            import_record(element_record,*ued_file_path);  //051213  ued_file_path may be obsolete
         }
         record_count++;
      }
   } while (buffer_read == buffer_size);
   cout << "Writing UED files:" << endl;
   return record_count;
}
//______________________________________________________________________________
nat32 NCDC_summary_of_the_day_format_convertor::perform_export()
{
/* Not yet implemented
*/
   cerr << "Export for UED -> NCDC is not currently implemented. At this time there are no known programs that read this format." << endl;
   press_return_before_exit = true;
   return 0;
}
//______________________________________________________________________________
NCDC_summary_of_the_day_format_convertor::NCDC_summary_of_the_day_format_convertor(int argc, const char *argv[])
:  UED_convertor(argc, argv)
{  all_known_weather_stations.set_reporting_agency(All_known_weather_stations::NCDC_REPORTING_AGENCY);
}
//______________________________________________________________________________

