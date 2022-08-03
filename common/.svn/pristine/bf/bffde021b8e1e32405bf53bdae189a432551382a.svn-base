#ifndef weather_UED_databaseH
#define weather_UED_databaseH

/*

There are some old model code and utilities where these are still used.
Especially when writing to UED files (I.e. convertors and ClimGen)
Although I would like to eventually replace that functionality.

When using CS Simulation classes and for new models (reading weather data),
use
CS_weather_daily_UED (for simple raw data access)
or
CS_land_unit_meteorological
(for more complete weather processing such as calcuating ETref).

- Roger 2018-04-02

*/

#include "common/weather/database/weather_database.h"
#include "common/weather/database/common_weather_creators.h"
#include "corn/dynamic_array/dynamic_array_T.h"
#include "UED/library/database_file.h"
#include "UED/library/locrec.h"
#include "corn/OS/directory_entry_name.h"
#include "CS_suite/UED/database_file_substitution.h"

class Storm_event_data_record;
class Weather_provider;

// included because there are several local UED objects

// now always a delagate

// SunStudio is complaining that get_XXXX() are const but call not const UED methods
// I probably should change all these to performs_IO, but am going to just make
// UED_indexed_database a mutable member (delegate) so I don't have to change all the accessors
// besides the get_methods() don't really modify the file.
// I probably should make UED_indexed_database a member for all compilers

class Air_temperature_maximum_parameter;
//______________________________________________________________________________
class Weather_UED_database
: public implements_ Weather_database                                            //130406
, public Common_weather_creators                                                 //050419
{
public: // temporarily public so I could get the filename for a debug
   mutable CS_UED::Database_file_indexed *database_file;                         //060713
   bool owns_database;
   mutable bool override_set_safety;                                             //081117
#ifndef LOC_ONLY_FOR_GEN
   Location_parameters  *location_parameters; // for any additional   // 090303 checking const, may not be const   // 090318 cannot be const, g++ doesn't like it //050525_
   // do not delete, this is owned by the UED database
   // or (in the case of legacy CropSyst) by the CropSyst model.
   bool owns_location_parameters;                                                //050912
#endif
public:
   Weather_UED_database
      (const char *filename
      ,std::ios_base::openmode _openmode /* = (std::ios_base::in | std::ios_base::out)*/
      ,CORN::Quality_code attribute = CORN::unknown_quality
      ,const CORN::OS::File_name *location_filename_to_provide_geolocation =0);  //091117
   Weather_UED_database                                                          //101008
      (CS_UED::Database_file_indexed *database                                   //170329
      ,bool take_database
      ,CORN::Quality_code attribute = CORN::unknown_quality
      ,const CORN::OS::File_name *location_filename_to_provide_geolocation =0);  //091117
         // location_filename_to_provide_geolocation is used only by ClimGen
         // (check, I think only generation).
         // when generating a new UED file we get the geolocation parameters
   virtual ~Weather_UED_database();
   inline bool enable_substitute_dates
      (CORN::Year substitute_base_year
      ,CORN::Year simulation_start_year
      ,int8 substitute_year_offset_                                              //161212
      ,bool allow_substitute_dates_ = true)                        contribution_
      {return  database_file->enable_substitution
         (substitute_base_year
         ,simulation_start_year
         ,substitute_year_offset_);}                                             //160407_160331_141031
   virtual bool done_with_dates_before(const CORN::Date_const &earliest_date);   //141103
   virtual bool start()      modification_{ return true; }                       //050111
   virtual void invalidate(bool absolutely);                                     //091216
 public: // get recorded data for a date
   virtual bool get_parameter_on                                                 //151122
      (modifiable_ CS::Parameter &parameter
      ,nat32                      variable_code // Typically the variable code will be UED variable code
      ,const CORN::Date_const    &on_date)                       rectification_; //151119
   /*151122 conceptual
   virtual bool setup_parameter_reference
      (modifiable_ CS::Parameter_cowl &parameter
      ,nat32                     variable_code // Typically the variable code will be UED variable code
      ,const CORN::Date         &on_date)                        rectification_;//151119
   */

   bool get_to    (Weather_provider &provider);                                  //110910

   virtual float64 get_cloud_cover_percent(weather_database_get_formals)  const; //991022
   virtual float64 get_isothermal_longwave_net_radiation(weather_database_get_formals) const ;//070204
   virtual float64 get_net_radiation(weather_database_get_formals)        const; //070204
 public: // set data methods
   bool set_from  (Weather_provider &provider);                                  //110910
   virtual float64 set_cloud_cover_percent      (const CORN::Date_const &i_date_time,float64 cloud_cover_percent  ,CORN::Quality &attribute);  //991022
   virtual float64 set_isothermal_longwave_net_radiation      (const CORN::Date_const &i_date_time,float64 isothermal_longwave_net_radiation  ,CORN::Quality &attribute);                  //070203
   virtual float64 set_net_radiation            (const CORN::Date_const &i_date_time,float64 net_radiation  ,CORN::Quality &attribute); //070203
   virtual float64 set_pot_evapotranspiration_FAO_Penman_Monteith_reference_mm(weather_database_set_formals);                                                                                      //070525
   virtual float64 set_avg_fullday_vapor_pressure_deficit_kPa  (const CORN::Date_const &date_time,float64 precip_mm,CORN::Quality &attribute);                               //011009
//NYI/*000612*/     virtual float64 set_max_vapor_pressure_deficit_kPa  (const CORN::Date_time &i_date_time,float64 precip_mm            ,CORN::Quality_code &attribute);
   virtual void set_precipitation_intervals_mm                                   //990425
      (const CORN::Date_const &i_date
      ,const CORN::Time &i_time
      ,const Dynamic_array<float32> &precip_in_intervals                         //120806
      ,CORN::Minutes interval_time_minutes
      ,CORN::Quality & attribute);
   Storm_event_data_record *get_precipitation_intervals_mm                       //050415
      (const CORN::Date_const &_date
      ,CORN::Minutes _desired_interval_time_minutes // For time step
      ,CORN::Quality & attribute);
   virtual void set_temperature_intervals                                        //021124
      ( const CORN::Date_const &i_date
      ,const Dynamic_array<float32> &temperature_in_intervals                    //120806
      ,CORN::Minutes interval_time_minutes
      ,CORN::Quality &attribute);
   virtual void take_geolocation_information(UED::Geolocation_record *loc_rec);
#ifndef LOC_ONLY_FOR_GEN
   virtual const Location_parameters *get_location_parameters()           const; //090303
   void use_location_parameters(const Location_parameters *location_parameters); //050517
#endif
   //NYI virtual bool  get_geolocation(Geolocation &geoloc_receiver)             const;//151027
   virtual const Geolocation         *get_geolocation_constant()          const; //050525
   virtual const char *get_description(std::string &return_buffer)        const; //050525
   #if (CS_VERSION==4)
   inline virtual bool is_key_string(const std::string &key)              affirmation_;  //180820


/*180820  was probably only used for find_cstr now using is_key
   
   virtual const char          *get_key()                                 const; //130406
   */
   #else
   inline virtual bool is_key_wstring(const std::wstring &key)              affirmation_;  //180820
/*   
   virtual const wchar_t  *get_key_wide()                                 const; //130406
*/   
   #endif
   inline virtual void set_override_safety(bool _override_set_safety) modification_ { override_set_safety = _override_set_safety;}//050525
   inline UED::Database_file_indexed &get_database_file()          modification_ {return *database_file; }  //070724
   inline const UED::Database_file_indexed &ref_database_file()            const {return *database_file; }  //161212
 public: // delegate overrides
   inline const UED::Geolocation_record *get_geolocation_record_immutable()const { return database_file->get_geolocation_record_immutable(); }   //050429
   inline UED::Record_base *goto_next(Record_code record_type)                   { return database_file->goto_next_record_of_type(record_type); } //991210
   inline virtual datetime64 get_earliest_date_time                              //970915
      ( Record_code  for_record_type_code = UED_FOR_ALL_RECORD_TYPES
      , UED_variable_code for_var_code = UED_FOR_ALL_VARIABLES)                  { return database_file->get_earliest_date_time(for_record_type_code,for_var_code); }
   inline virtual datetime64 get_latest_date_time                                //970915
      ( Record_code  for_record_type_code = UED_FOR_ALL_RECORD_TYPES
      , UED_variable_code for_var_code = UED_FOR_ALL_VARIABLES)                  { return database_file->get_latest_date_time(for_record_type_code,for_var_code); }
   inline virtual CORN::date32 get_earliest_available_date()               const
      { return database_file->get_earliest_date_time(UED_FOR_ALL_RECORD_TYPES,UED_FOR_ALL_VARIABLES); } //140822
      //140828 GCC doesn't like this{ return (CORN::date32)get_earliest_date_time(); } //140711
   virtual bool is_good()                                                  const { return database_file != 0; } //130728
 private:
#ifndef LOC_ONLY_FOR_GEN
   void initialize_location
      (const char *filename
      ,const  CORN::OS::File_name
         *location_filename_to_provide_geolocation);                             //101008
#endif
};
//______________________________________________________________________________
#endif

