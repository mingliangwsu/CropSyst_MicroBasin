//______________________________________________________________________________

#ifndef UED_simpleH
#define UED_simpleH

#ifdef UED_SIMPLE_USE_EXTERN_C
// When the DLL is compiled it needs the extern "C"
#  define EXTERN_C_EXPORT_STDCALL extern "C"  __export __stdcall
#else
// When the DLL header is imported in MatLab (for example),
// the extern "C" must be omitted.
#  define EXTERN_C_EXPORT_STDCALL
#endif

//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
unsigned long UED_simple_open(const char *UED_filename);
/*
 Returns the UED_database handle
 Returns 0 if the open fails.
*/
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
int UED_simple_close(unsigned long UED_database_handle);
/*
 Usually return 0 indicating the database close successfully
 Any other value can be assumed an error.
 Currently no error codes are enumerated.
*/
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
double UED_simple_get_earliest_date_time(unsigned long UED_database_handle);
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
double UED_simple_get_latest_date_time(unsigned long UED_database_handle);
/*
 Returns the earliest and latest time stamp encountered in the database
 The integer part of the returned double is the year and day of year.
 I.e.  2003001 is Jan 1, 2003.
 The fraction part of the returned double is the time.

   0 is midnight
   1 second after midnight is 1/86400

   1:00am is 1/24
*/
/*Not yet implemented
EXTERN_C_EXPORT_STDCALL
float UED_simple_get_for_datetime(unsigned long UED_database_handle, double datetime, unsigned long variable_code, unsigned long &units_code,unsigned long &quality,unsigned long &status);

// double datetime is in  datetime64 double float format
*/
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
float UED_simple_get_for_date(unsigned long UED_database_handle, signed long date, unsigned long variable_code, unsigned long &units_code,unsigned long &quality,unsigned long &status);
// date is in date32 integer format
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
float UED_simple_get_for_year(unsigned long UED_database_handle, signed int year, unsigned long variable_code, unsigned long &units_code,unsigned long &quality,unsigned long &status);
// date is in date32 integer format
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
float UED_simple_get_for_date_quick(unsigned long UED_database_handle, signed long date, unsigned long variable_code, unsigned long units_code);
// date is in date32 integer format
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
float UED_simple_get_for_date_short(unsigned long UED_database_handle, signed long date, unsigned long variable_code, unsigned long units_code);
// UED_simple_get_for_date_short deprecated
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
float UED_simple_get_for_year_quick(unsigned long UED_database_handle, signed int year, unsigned long variable_code, unsigned long units_code);
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
unsigned long UED_simple_get_last_units();
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
unsigned long UED_simple_get_last_quality();
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
unsigned long UED_simple_get_last_status();
//______________________________________________________________________________
/*Not yet implemented
EXTERN_C_EXPORT_STDCALL
float UED_simple_get_for_year(unsigned long UED_database_handle, int year, unsigned long variable_code, unsigned long &units_code,unsigned long &quality,unsigned long &status);
// year is integer (I.e. 2003)
*/

/* For all the UED_simple_get_.....() methods,
 the method returns the the value for the specified variable on the specified date in the specified units.

 It also returns the quality of the data and the status of the value.
 You should always check the quality of the data returned.
*/
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
float UED_simple_set_for_date(unsigned long UED_database_handle, float value, signed long date, unsigned long variable_code, unsigned long units_code,unsigned long quality);
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
float UED_simple_set_for_year(unsigned long UED_database_handle, float value, signed int year, unsigned long variable_code, unsigned long units_code,unsigned long quality);
//______________________________________________________________________________
// For the UED_simple_set_XXXX() function:

// These set the specified value for the specified date for the specified variable code, with the specified units,
// and data quality.

// This function returns the the value for the specified variable on the specified date in the specified units.
// Use the functions UED_simple_get_last_units(), UED_simple_get_last_quality() and UED_simple_get_last_status()
// to check the actual units and quality stored and the status.

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

/*  For all the UED_simple_get...() and UED_simple_set...() data methods, the following notes apply

 UED_database_handle is the database handle (obtained when the database is openned with UED_simple_open).

 date is the date of the data to retrieve expressed as long integer
     (year * 1000) + day_of_year
 datetime is the date and time (or simply time) (year *1000) + day_of_year + day_fraction
 where day_fraction is the timestep index divided by the number of time steps
 (I.e.  for 1:00am, the day fraction would be  1/24 (Midnight would be 0);
   1 minute after midnight would have day fraction 1/1440.)

 variable code is the UED variable code of the data to retrieve.

 units code is the desired units the value is to be returned in.
   The program can specify the desired units.
   UED will try to convert to those units, if it can't units will be set to the units available
   Use the value 0 if you don't know the units (the actual units will be returned).

 quality is the quality of the data that is returned
    0 indicates the data is real measured data,
    any quality < 128 is indicates usable data (see below)
    any quality >= 128 is an an erroneous value (see below)
 status indicates if the data was returned successfully
    0 indicates no error
    any other value should be assumed as an error (the error codes currently are not enumerated).
*/
/* The quality codes are
 0h   measured/real
 1h   estimated/calculated  (from real)
 2h   forecasted/simulated  (from real)
 3h   generated             (from real)

05h   estimated/calculated from estimated/calculated
06h   forecasted/simulated from estimated/calculated
07h   generated            from estimated/calculated
08h   reserved
09h   estimated/calculated from forecasted/simulated
0Ah   forecasted/simulated from forecasted/simulated
0Bh   generated            from forecasted/simulated
0Ch   reserved
0Dh   estimated/calculated from generated
0Eh   forecasted/simulated from generated
0Fh   generated            from generated

40h   (reserved - This value is used for internal processing)

80h   not valid
81h   out of range
82h   missing
BFh   unknown quality (presumed erroneous)

*/
//______________________________________________________________________________
EXTERN_C_EXPORT_STDCALL
int UED_set_geolocation
(unsigned long UED_database_handle
,float _latitude_dec_deg
,float _longitude_dec_deg
,float _elevation_m
,float _screening_height_m
,const char *station_ID_code);
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

#endif
