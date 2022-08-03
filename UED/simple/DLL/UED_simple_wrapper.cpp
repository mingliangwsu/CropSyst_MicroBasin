//---------------------------------------------------------------------------
// MicroSoft VC++ notes:
// This is pure C++ code, we do not need the MFC stdafx.h file for precompiled headers:
//	- From the Project menu, select Settings ....
//	- Make sure the Settings for selection reflects the project you are building. By default, this will likely be "Win32 Debug".
//	- Expand the Source Files folder in the list on the left, and click once on the source file that you don't want to use precompiled headers.
//	- On the right, select the C/C++ tab.
//	- In the Category combo box, select Precompiled headers.
//  - Select the Not using precompiled headers option.
//  - Repeat for any other files for which you wish to disable precompiled headers (but not for any files created by the Developer Studio AppWizard).
//  - Click OK to close the project settings dialog.

#define UED_SIMPLE_USE_EXTERN_C
#include "UED_simple.h"

#include "UED/library/database_file.h"
#include "UED/library/timeqry.h"
#include "UED/library/datasetrec_creation.h"
#include "UED/library/locrec.h"
#include "common/geodesy/geolocation.h"

using namespace UED;
//______________________________________________________________________________
#pragma package(smart_init)

unsigned long /*UED_units_code*/          UED_simple_latest_units    =0;
unsigned long /*UED_quality_attribute*/   UED_simple_latest_quality  =UED_measured;
unsigned long           UED_simple_latest_status   =0;
//______________________________________________________________________________
extern "C"  __export __stdcall
unsigned long UED_simple_open(const char *UED_filename)
{  unsigned long opend_db_handle = 0;
   {  Database_file_indexed *opened_db = new Database_file_indexed(UED_filename,(std::ios_base::in | std::ios_base::out));
      opend_db_handle = (unsigned long)opened_db;
   };
   return opend_db_handle;
}; // Returns the UED_database handle
//______________________________________________________________________________
extern "C"  __export __stdcall
int UED_simple_close(unsigned long UED_database_handle)
{  Database_file_indexed *UED_db = (Database_file_indexed *)UED_database_handle;
   UED_db->finish();
   delete UED_db;
   return 0;
};
//______________________________________________________________________________
extern "C"  __export __stdcall
float UED_simple_get_for_date
(unsigned long UED_database_handle
,signed   long date
,unsigned long variable_code
,unsigned long &units_code
,unsigned long &quality
,unsigned long &status)
{  // Returns the the value for the specified variable on the specified date in the specified units.
   // It also returns the quality of the data and the status of the value.
   Database_file_indexed *UED_db = (Database_file_indexed *)UED_database_handle;
   Datetime64 date_time = date;
   UED_units_code actual_units = units_code;
   CORN::Quality attribute(UED_measured);                                        //140117
   float32 result = 0;
   {  Time_query_single_date  time_query(date_time,UT_day,Time_query::at);
      result =  UED_db->get_no_create
      (Record_type_distinguisher_interface::UED_data_set_year_var_units,(UED_variable_code)variable_code,time_query,actual_units,attribute);
   }
   if (!attribute.is_valid()) // This may be a scalar (I.e. CropSyst growing season output) //140117
   { Time_query_single_date  time_query_scalar(date_time,0,Time_query::at);; // Scalars don't have a timestep.
      result =  UED_db->get_no_create(Record_type_distinguisher_interface::UED_data_value_date_var_units,(UED_variable_code)variable_code,time_query_scalar,actual_units,attribute);
   }
   units_code = actual_units;
   quality = attribute.get();                                                    //140117
   status = 0;
   return result;
};
//______________________________________________________________________________
extern "C"  __export __stdcall
float UED_simple_get_for_date_quick(unsigned long UED_database_handle, signed long date, unsigned long variable_code, unsigned long units_code)
{  // date is in date32 integer format
   return
   UED_simple_get_for_date(UED_database_handle, date, variable_code, UED_simple_latest_units,UED_simple_latest_quality,UED_simple_latest_status);
};
//______________________________________________________________________________
extern "C"  __export __stdcall
float UED_simple_get_for_date_short(unsigned long UED_database_handle, signed long date, unsigned long variable_code, unsigned long units_code)
{  // deprecated
   return UED_simple_get_for_date_quick(UED_database_handle, date, variable_code, units_code);
};
//______________________________________________________________________________
extern "C"  __export __stdcall
float UED_simple_get_for_year(unsigned long UED_database_handle, signed int year, unsigned long variable_code, unsigned long &units_code,unsigned long &quality,unsigned long &status)
{  // Returns the the value for the specified variable on the specified date in the specified units.
   // It also returns the quality of the data and the status of the value.
   Database_file_indexed *UED_db = (Database_file_indexed *)UED_database_handle;
   Datetime64 date_time = year*1000 + date_days_in_year(year);
   UED_units_code actual_units = units_code;
   CORN::Quality attribute(UED_measured);                                        //140117
   float32 result = 0;
   {  Time_query_single_date  time_query(date_time,UT_year,Time_query::at);
      result =  UED_db->get_no_create
      (Record_type_distinguisher_interface::UED_data_set_year_var_units,(UED_variable_code)variable_code,time_query,actual_units,attribute);
   }
   if (!attribute.is_valid()) // This may be a scalar (I.e. CropSyst growing season output) //140117
   { Time_query_single_date  time_query_scalar(date_time,0,Time_query::at);; // Scalars don't have a timestep.
      result =  UED_db->get_no_create(Record_type_distinguisher_interface::UED_data_value_date_var_units,(UED_variable_code)variable_code,time_query_scalar,actual_units,attribute);
   };
   units_code = actual_units;
   quality = attribute.get();                                                    //140117
   status = 0;
   return result;
};
//______________________________________________________________________________
extern "C"  __export __stdcall
float UED_simple_get_for_year_quick(unsigned long UED_database_handle, signed int year, unsigned long variable_code, unsigned long units_code)
{
// date is in date32 integer format
   return
   UED_simple_get_for_year(UED_database_handle, year, variable_code, UED_simple_latest_units,UED_simple_latest_quality,UED_simple_latest_status);
};
//______________________________________________________________________________
extern "C"  __export __stdcall
unsigned long UED_simple_get_last_units()    { return UED_simple_latest_units; };
extern "C"  __export __stdcall
unsigned long UED_simple_get_last_quality()  { return UED_simple_latest_quality; };
extern "C"  __export __stdcall
unsigned long UED_simple_get_last_status()   { return UED_simple_latest_status; };
//______________________________________________________________________________
extern "C"  __export __stdcall
float UED_simple_set_for_date(unsigned long UED_database_handle, float value, signed long date, unsigned long variable_code, unsigned long units_code,unsigned long quality)
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

   UED_simple_latest_units    =units_code;
   UED_simple_latest_quality  =quality;
   UED_simple_latest_status   =0;
   Database_file_indexed *UED_db = (Database_file_indexed *)UED_database_handle;
   Datetime64 date_time = date;
   Time_query_single_date  time_query(date_time,UT_day,Time_query::at);
   UED_variable_code  var_code = variable_code;
   Record_code record_type_code = Record_type_distinguisher_interface::UED_data_set_year_var_units;
   Data_record_creation_layout creation_layout
   (record_type_code,var_code,UED_simple_latest_units,UT_day
   ,UT_year // 070718need time stamp record step here!!
   ,(CORN::Quality_code)UED_simple_latest_quality);

   bool created;
   CORN::Quality UED_simple_latest_quality_attribute((Quality_code) UED_simple_latest_quality); //140117
   float32 result =  UED_db->set_value
    (value
    ,time_query
    ,UED_simple_latest_units     // actual_units
    ,UED_simple_latest_quality_attribute   // attribute
    ,creation_layout
    ,created
    ,false);
   UED_simple_latest_quality= UED_simple_latest_quality_attribute.get();         //140117
   return result;
};
//______________________________________________________________________________
extern "C"  __export __stdcall
float UED_simple_set_for_year(unsigned long UED_database_handle, float value, signed int year, unsigned long variable_code, unsigned long units_code,unsigned long quality)
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

   UED_simple_latest_units    =units_code;
   UED_simple_latest_quality  =quality;
   UED_simple_latest_status   =0;
   Database_file_indexed *UED_db = (Database_file_indexed *)UED_database_handle;
   Datetime64 date_time = year *1000 + date_days_in_year(year);
   Time_query_single_date  time_query(date_time,UT_year,Time_query::at);
   UED_variable_code  var_code = variable_code;
   Record_code record_type_code = Record_type_distinguisher_interface::UED_data_set_year_var_units;
   Data_record_creation_layout creation_layout
   (record_type_code,var_code,UED_simple_latest_units,UT_year
   ,UT_year // 070718  need time stamp step here
   ,(CORN::Quality_code)UED_simple_latest_quality);
   bool created;
   //140117 CORN::Quality_code UED_simple_latest_quality_attribute = (CORN::Quality_code )UED_simple_latest_quality;
   CORN::Quality UED_simple_latest_quality_attribute((CORN::Quality_code )UED_simple_latest_quality); //140117
   float32 result =  UED_db->set_value
    (value
    ,time_query
    ,UED_simple_latest_units     // actual_units
    ,UED_simple_latest_quality_attribute   // attribute
    ,creation_layout
    ,created
    ,false);
   UED_simple_latest_quality= UED_simple_latest_quality_attribute.get();         //140117
   return result;
};
//______________________________________________________________________________
extern "C"  __export __stdcall
double UED_simple_get_earliest_date_time(unsigned long UED_database_handle)
{
   Database_file_indexed *UED_db = (Database_file_indexed *)UED_database_handle;
   return (double)UED_db->get_earliest_date_time
   (UED_FOR_ALL_RECORD_TYPES
   ,UED_FOR_ALL_VARIABLES);
}
//______________________________________________________________________________
extern "C"  __export __stdcall
double UED_simple_get_latest_date_time(unsigned long UED_database_handle)
{
   Database_file_indexed *UED_db = (Database_file_indexed *)UED_database_handle;
   return (double)UED_db->get_latest_date_time
      (UED_FOR_ALL_RECORD_TYPES
      , UED_FOR_ALL_VARIABLES);
}
//______________________________________________________________________________
extern "C"  __export __stdcall
int UED_set_geolocation
(unsigned long UED_database_handle
,float _latitude_dec_deg
,float _longitude_dec_deg
,float _elevation_m
,float _screening_height_m
,const char *station_ID_code)
{
/*
   This function adds the specified geolocation parameters to the UED database file.
   The Geolocation record is optional in the UED database file;
   but it is strongly recommended to provide these geolocation parameter.
   If the geolocation record exists, it will be updated with with the parameter
   values passed to this function.
   Otherwise the geolocation record will be created and added to the UED file.
   The station_ID_code parameter is optional pass a null pointer 0 if
   there is no station ID.
   Returns 1 if the record was created. 0 if it already exists and was updated.
*/
   bool geoloc_rec_created = false;
   Database_file_indexed *UED_db = (Database_file_indexed *)UED_database_handle;
   Geolocation_record  *geoloc_rec = UED_db->get_geolocation_record();
   if (!geoloc_rec)
   {  // Create a new record for the database
      Geolocation geoloc;
      geoloc_rec = new Geolocation_record(geoloc);
      UED_db->take_geolocation_record(geoloc_rec);
      geoloc_rec_created = true;
   };
   geoloc_rec->set_latitude_dec_deg_32  ((float32)_latitude_dec_deg);
   geoloc_rec->set_longitude_dec_deg_32 ((float32)_longitude_dec_deg);
   geoloc_rec->set_elevation_meter      ((float32)_elevation_m);
   geoloc_rec->set_screening_height     ((float32)_screening_height_m);
   // NYI geoloc_rec->set_country_code         (uint16 i_country_code)
   // NYI geoloc_rec->set_state_code           (uint16 i_state_code)
   // NYI geoloc_rec->set_county_code          (uint16 i_county_code)
   // NYI geoloc_rec->set_station_number       (uint32 i_station_num)
   if (station_ID_code)
      geoloc_rec->set_station_ID_code  (station_ID_code);
   // NYI geoloc_rec->set_country_name(const CORN::Ustring &i_country_name);
   // NYI geoloc_rec->set_state_name  (const CORN::Ustring &i_state_name);
   // NYI geoloc_rec->set_county_name (const CORN::Ustring &i_county_name);
   // NYI geoloc_rec->set_station_name(const CORN::Ustring &i_station_name);
   return (int)geoloc_rec_created;
};
//______________________________________________________________________________

