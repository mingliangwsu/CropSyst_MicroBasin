// This is the main DLL file.

//#include "Stdafx.h"
#include "UED_simple_NET.h"
//#include "msclr/marshal.h"

using namespace System::Runtime::InteropServices; 

#include "UED/library/timeqry.h"
#include "UED/library/controls.h"
#include "UED/library/datasetrec_creation.h"
#include "UED/library/locrec.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)

namespace UED_simple
{   
Database::Database(System::String ^UED_filename)
: UED_db(0)
,latest_quality(new CORN::Quality)
,geoloc_rec(0)
{
	const char *UED_filename_cstr = 0;
	
	#if (_MSC_VER > 1600 && _MSC_VER < 1700)
	// The following is for VC2010
      std::string UED_filename_string;
      UED_filename_string = marshal_as<std::string>(UED_filename);

      UED_filename_cstr = UED_filename_string.c_str();
	#else
      UED_filename_cstr = (const char*) (Marshal::StringToHGlobalAnsi(UED_filename)).ToPointer();
	#endif
	  UED_db = new UED::Database_file_indexed(UED_filename_cstr, (std::ios_base::in | std::ios_base::out));
};
//____________________________________________________________________________
Database::~Database()
{   if (UED_db) delete UED_db; UED_db = 0;
};
//____________________________________________________________________________
void Database::close()
{
   if (!UED_db) return;
   UED_db->finish();  // Must have to finish because of .NET's messed up garbage collection!
   delete UED_db; UED_db = 0;
};
//____________________________________________________________________________
float Database::get_for_date(signed long date, unsigned long variable_code, unsigned long &units_code,unsigned long &quality,unsigned long &status) 
{  // Returns the the value for the specified variable on the specified date in the specified units.
   // It also returns the quality of the data and the status of the value.
   CORN::Datetime64 date_time = date;
   UED_units_code actual_units = units_code;
   CORN::Quality attribute(measured_quality);                                   //110926
   float32 result = 0;
   {  UED::Time_query_single_date  time_query(date_time,UT_day,UED::Time_query::at);
      result = UED_db->get_no_create
     (UED::Record_type_distinguisher_interface::UED_data_set_year_var_units,(UED::Variable_code)variable_code,time_query,actual_units,attribute);
   };
   if (!attribute.is_valid())// This may be a scalar (I.e. CropSyst growing season output)
   { UED::Time_query_single_date  time_query_scalar(date_time,0,UED::Time_query::at);; // Scalars don't have a timestep.
      result =  UED_db->get_no_create(UED::Record_type_distinguisher_interface::UED_data_value_date_var_units,(UED::Variable_code)variable_code,time_query_scalar,actual_units,attribute);
   };
   units_code = actual_units;
   quality = attribute.get();
   status = 0;
   return result;
};
//____________________________________________________________________________
float Database::get_for_date_quick( signed long date, unsigned long variable_code, unsigned long units_code) 
{  // date is in date32 integer format
   unsigned long latest_units_code = units_code;
   unsigned long latest_quality_attribute = latest_quality->get(); //110926 unsigned long latest_quality_attribute = (CORN::Quality_code )latest_quality;
   unsigned long latest_status_code = latest_status;
   float value = get_for_date(date, variable_code, latest_units_code,latest_quality_attribute,latest_status_code);
   latest_units = latest_units_code;
   latest_quality->set_int32(latest_quality_attribute);
   latest_status = latest_status_code;
   return value;
};
//____________________________________________________________________________
float Database::get_for_date_vector(unsigned long index, signed long date, unsigned long variable_code, unsigned long &units_code, unsigned long &quality,unsigned long &status )
{
   latest_units    =units_code;
   latest_quality->set_int32(quality); //110926 latest_quality  =quality;
   latest_status   =0;
   CORN::Datetime64 date_time = date;
   UED::Time_query_single_date  time_query(date_time,UT_day,UED::Time_query::at);   
   UED::Variable_code  var_code = variable_code;
   Record_code record_type_code = UED::Record_type_distinguisher_interface::UED_data_vector_date_var_units;
//   UED::Data_record_creation_layout creation_layout
//   (record_type_code,var_code,latest_units,UT_day
//   ,UT_year // 070209 need time stamp step here, but wasn't sure which to use
//   ,(CORN::Quality_code)latest_quality);
   bool created;
   CORN::Quality latest_quality_attribute(latest_quality->get()); //110926 CORN::Quality_code latest_quality_attribute = (CORN::Quality_code )latest_quality;
   nat32 latest_units_code = latest_units;
   float vector_data[1000]; // An arbitrary large number
   unsigned long vector_size =UED_db->get_vector(vector_data,record_type_code,var_code,time_query,latest_units_code,latest_quality_attribute,created);
   float value_at = 0.0;
   if (index < vector_size)
   {
      value_at = vector_data[index];
      latest_quality->set(latest_quality_attribute);
      status = 0;      
   } else
   {
      latest_quality->set(CORN::missing_quality);
      status = 1;
   }
   latest_units_code = latest_units_code  ;
   return value_at;
};
//____________________________________________________________________________
float Database::get_for_year(signed int year,  unsigned long variable_code, unsigned long &units_code,unsigned long &quality,unsigned long &status) 
{  CORN::Datetime64 date_time = year * 1000 + date_days_in_year(year);
   CORN::Units_code actual_units = units_code;
   CORN::Quality attribute(measured_quality);
   float32 result =0;
   {  UED::Time_query_single_date  time_query(date_time,UT_year,UED::Time_query::at);
      result =  UED_db->get_no_create
		  (UED::Record_type_distinguisher_interface::UED_data_set_year_var_units,(UED::Variable_code)variable_code,time_query,actual_units,attribute);
   }
   if (!attribute.is_valid()) // This may be a scalar (I.e. CropSyst growing season output)
   { UED::Time_query_single_date  time_query_scalar(date_time,0,UED::Time_query::at);; // Scalars don't have a timestep.
      result =  UED_db->get_no_create(UED::Record_type_distinguisher_interface::UED_data_value_date_var_units,(UED::Variable_code)variable_code,time_query_scalar,actual_units,attribute);
   };
   units_code = actual_units;
   quality = attribute.get_int32();
   status = 0;
   return result;
};
//____________________________________________________________________________
float Database::get_for_year_quick(signed int year, unsigned long variable_code, unsigned long units_code) 
{  // date is in date32 integer format
   unsigned long latest_units_code = units_code;
   unsigned long latest_quality_attribute = latest_quality->get(); //110926 unsigned long latest_quality_attribute = (CORN::Quality_code )latest_quality;
   unsigned long latest_status_code = latest_status;
   float value = get_for_year(year, variable_code, latest_units_code,latest_quality_attribute,latest_status_code);
   latest_units = latest_units_code;
   latest_quality->set_int32(latest_quality_attribute);
   latest_status = latest_status_code;
   return value;
};
//____________________________________________________________________________
      // year is a 16 bit signed integer format

unsigned long Database::get_last_units()    { return latest_units; };
unsigned long Database::get_last_quality()  { return latest_quality->get_int32(); };
unsigned long Database::get_last_status()   { return latest_status; };
//____________________________________________________________________________
float Database::set_for_date( float value, signed long date, unsigned long variable_code, unsigned long units_code,unsigned long quality) 
{
// Sets the specified value for the specified date for the specified variable code, with the specified units,
// and data quality.

// This function returns the the value for the specified variable on the specified date in the specified units.
// It also returns the quality of the data and the status of the value.

// The data may actually be stored in the database in different units
// (Depending how values were previously stored) in this case the
// return value will be the actual value stored and the units
// passed in the units_code parameter will be updated to indicate the
// units actually stored. (Generally it is not necessary to check the
// units and returned variable after calling this function unless you
// want to confirm the conversion was done correctly).

// You should specify the quality of the data (0 indicate real data).
// there may be a quality check (I.e. a check of valid range of input value)
// Generall the quality will be the same as the passed value, but
// the quality will be updated if the value is out of range.
// If a data value already exists in the database the database will only
// be updated if the specified value has a better quality than the value
// already in the data base (an existing value of the same quality will be
// replaced by the specified value)..
// The value actually stored in the database (and its quality) will be returned,
// so although, generally the returned value will be the same as the passed value,
// the returned value will be different if there is a units conversion, or
// the value in the database is of better quality.

   latest_units    =units_code;
   latest_quality->set_int32(quality); // latest_quality  =quality;
   latest_status   =0;
   CORN::Datetime64 date_time = date;
   UED::Time_query_single_date  time_query(date_time,UT_day,UED::Time_query::at);
   UED::Variable_code  var_code = variable_code;
   Record_code record_type_code = UED::Record_type_distinguisher_interface::UED_data_set_year_var_units;
   UED::Data_record_creation_layout creation_layout
   (record_type_code,var_code,latest_units,UT_day
   ,UT_year // 070209 need time stamp step here, but wasn't sure which to use
   ,latest_quality->get());
   bool created;
   CORN::Quality latest_quality_attribute(latest_quality->get());
   nat32 latest_units_code = latest_units;
   float32 result =  UED_db->set_value(value,time_query,latest_units_code,latest_quality_attribute,creation_layout,created,false);
   latest_quality->set(latest_quality_attribute);
   latest_units_code = latest_units_code  ;

//040512   units_code = actual_units;
//040512   quality = attribute;
//040512l   status = 0;
   return result;
};
//____________________________________________________________________________
float Database::set_for_date_scalar(float value, signed long date, unsigned long variable_code, unsigned long units_code,unsigned long quality)
{  latest_units    =units_code;
   latest_quality->set_int32(quality); //110926latest_quality  =quality;
   latest_status   =0;
   CORN::Datetime64 date_time = date;
   UED::Time_query_single_date  time_query(date_time,UT_day,UED::Time_query::at);
   UED::Variable_code  var_code = variable_code;
   Record_code record_type_code = UED::Record_type_distinguisher_interface::UED_data_value_year_var_units;
   UED::Data_record_creation_layout creation_layout
   (record_type_code,var_code,latest_units,0
   ,UT_year  // 070209 need time stamp step here, but wasn't sure which to use
   ,latest_quality->get());
   bool created;
   CORN::Quality latest_quality_attribute(latest_quality->get()); //110926CORN::Quality_code latest_quality_attribute = (CORN::Quality_code )latest_quality;
   nat32 latest_units_code = latest_units;
   float32 result =  UED_db->set_value(value,time_query,latest_units_code,latest_quality_attribute,creation_layout,created,false);
   latest_quality->set(latest_quality_attribute);
   latest_units_code = latest_units_code  ;
   return result;
};
//____________________________________________________________________________
double Database::get_earliest_date_time() 
{  return (double)UED_db->get_earliest_date_time
   (UED_FOR_ALL_RECORD_TYPES,UED_FOR_ALL_VARIABLES);
}
//____________________________________________________________________________
double Database::get_latest_date_time() 
{   return (double)UED_db->get_latest_date_time
      (UED_FOR_ALL_RECORD_TYPES, UED_FOR_ALL_VARIABLES);
}
//____________________________________________________________________________
const char *Database::get_units_abbreviation(unsigned long units_code)
{  static std::string units_abbr_buffer;
   Units_clad smart_units(units_code); //110926U_smart_units_code smart_units(units_code);
   char units_description[100];
   char units_abbreviation[50];
   smart_units.compose_description(units_description, units_abbreviation);
   units_abbr_buffer.assign(units_abbreviation);
   return units_abbr_buffer.c_str();
};
//____________________________________________________________________________
float Database::set_for_year(float value, signed int year, unsigned long variable_code, unsigned long units_code,unsigned long quality)
{  // Sets the specified value for the specified date for the specified variable code, 
   // with the specified units, and data quality.

// This function returns the the value for the specified variable on the specified date in the specified units.
// It also returns the quality of the data and the status of the value.

// The data may actually be stored in the database in different units
// (Depending how values were previously stored) in this case the
// return value will be the actual value stored and the units
// passed in the units_code parameter will be updated to indicate the
// units actually stored. (Generally it is not necessary to check the
// units and returned variable after calling this function unless you
// want to confirm the conversion was done correctly).

// You should specify the quality of the data (0 indicate real data).
// there may be a quality check (I.e. a check of valid range of input value)
// Generall the quality will be the same as the passed value, but
// the quality will be updated if the value is out of range.
// If a data value already exists in the database the database will only
// be updated if the specified value has a better quality than the value
// already in the data base (an existing value of the same quality will be
// replaced by the specified value)..
// The value actually stored in the database (and its quality) will be returned,
// so although, generally the returned value will be the same as the passed value,
// the returned value will be different if there is a units conversion, or
// the value in the database is of better quality.

   latest_units    =units_code;
   latest_quality->set_int32(quality);
   latest_status   =0;
   CORN::Datetime64 date_time = year *1000 + date_days_in_year(year);
   UED::Time_query_single_date  time_query(date_time,UT_year,UED::Time_query::at);

   UED::Variable_code  var_code = variable_code;
   Record_code record_type_code = UED::Record_type_distinguisher_interface::UED_data_set_year_var_units;

   UED::Data_record_creation_layout creation_layout
   (record_type_code,var_code,latest_units,UT_year
   ,UT_year  // 070209 need time stamp step here, but wasn't sure which to use
   ,latest_quality->get());
   //   (record_type_code,var_code,UED_simple_latest_units,UT_day,(CORN::Quality_code)UED_simple_latest_quality);

   bool created;
   CORN::Quality latest_quality_attribute(latest_quality->get()); //110926CORN::Quality_code latest_quality_attribute = (CORN::Quality_code )latest_quality;
   nat32 latest_units_code = latest_units;
   float32 result =  UED_db->set_value(value,time_query,latest_units_code,latest_quality_attribute,creation_layout,created,false);
   latest_quality->set(latest_quality_attribute);
   latest_units = latest_units_code;
   return result;
};
//____________________________________________________________________________
bool Database::get_period(bool next,double at_date,  nat32 &consider_options, double &start_date_time, double &end_date_time, unsigned long &application_code, unsigned long &enumeration, unsigned long &index, unsigned long &variable_code, char *description,unsigned long max_description_length)
{  const UED::Period_record *found_period = UED_db->get_period(consider_options,at_date,application_code,enumeration,index,variable_code);
   if (found_period)
   {  consider_options  = found_period->options;
      start_date_time   = found_period->start_date_time;
      end_date_time     = found_period->end_date_time;
      application_code  = found_period->application_code;
      enumeration       = found_period->enumeration;
      variable_code     = found_period->variable_code;
      if (description)  // description is optional
         strncpy(description,found_period->text.c_str(),max_description_length);
   }; // else result_description remains 0 indicating no period record found.
   return (found_period != 0);
};
//____________________________________________________________________________
bool Database::set_period(nat32 consider_options,double start_date_time, double end_date_time, unsigned long application_code, unsigned long enumeration, unsigned long index, unsigned long variable_code,const char *description)
{  // Either appends or updates (an existing period record) with the specified attributes.
   // Returns true if the record is updated or appended (successful)
   const UED::Period_record period_to_set(description,consider_options,start_date_time,end_date_time,application_code, enumeration,index,variable_code  );
   const UED::Period_record *period_that_was_set = UED_db->set_period(period_to_set);
   bool result  = period_that_was_set ? true : false;
   return result;
};
//____________________________________________________________________________
UED::Geolocation_record *Database::provide_geolocation()
{  if (!geoloc_rec)
   { geoloc_rec = UED_db->get_geolocation_record();
	  if (!geoloc_rec)
	     geoloc_rec = new UED::Geolocation_record;
      /*
      station_ID.
      station_name;
      country;
      state_or_province;
      county;
      comment;
      */
   }
   return geoloc_rec;      
};
//2012-03-03___________________________________________________________________
bool Database::set_geolocation
(double latitude_dec_deg 
,double longitude_dec_deg
,double elevation        
,double screening_height 
,System::String ^station_ID
,System::String ^station_name
,System::String ^country
,System::String ^state_or_provence
,System::String ^county
,System::String ^comment)
{
   UED::Geolocation_record *new_geoloc_rec= new UED::Geolocation_record;
   
   new_geoloc_rec->set_latitude_dec_deg_32  ((float)latitude_dec_deg);
   new_geoloc_rec->set_longitude_dec_deg_32 ((float)longitude_dec_deg);
   new_geoloc_rec->set_screening_height     ((float)screening_height);
   new_geoloc_rec->set_elevation_meter      ((float)elevation);
   
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
	const char *station_ID_cstr = 0;
	#if (_MSC_VER > 1600 && _MSC_VER < 1700)
      std::string station_ID_string; station_ID_string = marshal_as<std::string>(station_ID); station_ID_cstr = station_ID_string.c_str(); //VC2010
	#else
      station_ID_cstr = (const char*) (Marshal::StringToHGlobalAnsi(station_ID)).ToPointer();
	#endif
   new_geoloc_rec->set_station_ID_code  (station_ID_cstr);                //031217
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
	const char *country_cstr = 0;
	#if (_MSC_VER > 1600 && _MSC_VER < 1700)
      std::string country_string; country_string = marshal_as<std::string>(country); country_cstr = country_string.c_str(); //VC2010
   #else
      country_cstr = (const char*) (Marshal::StringToHGlobalAnsi(country)).ToPointer();
   #endif
   new_geoloc_rec->set_country_name     (country_cstr);
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
	const char *state_or_provence_cstr = 0;
	#if (_MSC_VER > 1600 && _MSC_VER < 1700)
      std::string state_or_provence_string; state_or_provence_string = marshal_as<std::string>(state_or_provence); state_or_provence_cstr = state_or_provence_string.c_str(); //VC2010
   #else
      state_or_provence_cstr = (const char*) (Marshal::StringToHGlobalAnsi(state_or_provence)).ToPointer();
   #endif
   new_geoloc_rec->set_state_name  (state_or_provence_cstr);
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
	const char *county_cstr = 0;
	#if (_MSC_VER > 1600 && _MSC_VER < 1700)
      std::string county_string; county_string = marshal_as<std::string>(county); county_cstr = county_string.c_str(); //VC2010
   #else
      county_cstr = (const char*) (Marshal::StringToHGlobalAnsi(county)).ToPointer();
   #endif
   new_geoloc_rec->set_county_name (county_cstr);
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
	const char *station_name_cstr = 0;
	#if (_MSC_VER > 1600 && _MSC_VER < 1700)
      std::string station_name_string; station_name_string = marshal_as<std::string>(station_name); station_name_cstr = station_name_string.c_str(); //VC2010
   #else
      station_name_cstr = (const char*) (Marshal::StringToHGlobalAnsi(station_name)).ToPointer();
   #endif
   new_geoloc_rec->set_station_name(station_name_cstr);
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
	const char *comment_cstr = 0;
	#if (_MSC_VER > 1600 && _MSC_VER < 1700)
      std::string comment_string; comment_string = marshal_as<std::string>(comment); comment_cstr = comment_string.c_str(); //VC2010
   #else
      comment_cstr = (const char*) (Marshal::StringToHGlobalAnsi(comment)).ToPointer();
   #endif
   new_geoloc_rec->set_comment  (comment_cstr);  
   UED_db->take_geolocation_record(new_geoloc_rec);
   new_geoloc_rec = 0;
   return true;
};
//2011-10-01__________________________________________________________________         
System::String^ std_string_to_system_string( const std::string& input ) 
{
   return System::Runtime::InteropServices::Marshal::PtrToStringAnsi( (IntPtr)(char *)input.c_str() );

//was return System::Runtime::InteropServices::Marshal::PtrToStringAnsi( static_cast<LPVOID>( input.c_str() ) );
}
//2012-03-03___________________________________________________________________
double Database::get_geolocation_latitude_dec_deg()
{  provide_geolocation();
   return geoloc_rec->get_latitude_dec_deg();
};
//2012-03-03___________________________________________________________________
double Database::get_geolocation_longitude_dec_deg()
{  provide_geolocation();
   return geoloc_rec->get_longitude_dec_deg();
};
//2012-03-03___________________________________________________________________
double Database::get_geolocation_elevation_m()
{  provide_geolocation();
   return geoloc_rec->get_elevation();
};
//2012-03-03___________________________________________________________________
double Database::get_geolocation_screening_height_m()
{  provide_geolocation();
   return geoloc_rec->get_screening_height();
};
//2012-03-03___________________________________________________________________
System::String ^ Database::get_geolocation_station_ID()
{  provide_geolocation();
   System::String ^station_ID = std_string_to_system_string(geoloc_rec->get_station_ID_code());
   return station_ID;
};
//2012-03-03___________________________________________________________________
System::String ^ Database::get_geolocation_station_name()
{  provide_geolocation();
   System::String ^ station_name = std_string_to_system_string(geoloc_rec->get_station_name().c_str());
   return station_name;
};
//2012-03-03___________________________________________________________________
System::String ^ Database::get_geolocation_country()
{  provide_geolocation();
   System::String ^country = std_string_to_system_string(geoloc_rec->get_county_name().c_str());
   return country;
};
//2012-03-03___________________________________________________________________
System::String ^ Database::get_geolocation_state_or_province()
{  provide_geolocation();
   System::String ^ state_or_province = std_string_to_system_string(geoloc_rec->get_state_name().c_str());
   return state_or_province;
};
//2012-03-03___________________________________________________________________
System::String ^ Database::get_geolocation_county()
{  provide_geolocation();
   System::String ^ county_name = std_string_to_system_string(geoloc_rec->get_county_name().c_str());
   return county_name;
};
//2012-03-03___________________________________________________________________
System::String ^ Database::get_geolocation_comment()
{  provide_geolocation();
   System::String ^ comment = std_string_to_system_string(geoloc_rec->get_comment().c_str());
   return comment;
};
//2012-03-03___________________________________________________________________

/*disabled
unsigned long Database::copy_periods_to_database(Database &target_database)
{  return UED_db->copy_periods_to_database(*target_database.UED_db);
};
*/
//____________________________________________________________________________
};  // namespace

