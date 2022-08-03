#ifndef weather_databaseH
#define weather_databaseH

#include "corn/const.h"
#include "UED/library/codes.h"
#include "corn/chronometry/date_I.h"
#include "corn/container/item.h"
#include "corn/dynamic_array/dynamic_array_T.h"
#include "corn/quality.hpp"
#include "UED/library/varcodes.h"
#include "common/weather/parameter/WP_solar_radiation.h"
#include "common/CS_parameter.h"
// included because there are several local UED objects

class Location_parameters;
class Geolocation;
class Weather_provider;
//______________________________________________________________________________
interface_ Weather_database      // deprecated
{
  //140711  Date if needed should be a reference to the controlling object
   virtual bool start()                                         modification_=0; //140126_050111

   virtual void invalidate(bool absolutely) = 0;                                 //091216
   # define weather_database_get_formals_header CORN::Quality &, const CORN::Date_const &
   # define weather_database_get_formals CORN::Quality &attribute, const CORN::Date_const &date_time_
   # define weather_database_set_formals_header  const CORN::Date_const  &,float64 , CORN::Quality &
   # define weather_database_set_formals  const CORN::Date_const &date_time_,float64 value, CORN::Quality &attribute

   virtual bool get_to    (Weather_provider &provider) = 0;                      //110910
   virtual bool set_from  (Weather_provider &provider) = 0;                      //110910
public:
   // set data methods that must be implemented in derived classes
   virtual bool get_parameter_on                                                 //151122
      (modifiable_ CS::Parameter &parameter
      ,nat32                      variable_code // Typically the variable code will be UED variable code
      ,const CORN::Date_const    &on_date)                     rectification_=0; //151119
/*151122 conceptual
   virtual bool setup_parameter_reference
      (modifiable_ CS::Parameter_cowl &parameter
      ,nat32                     variable_code // Typically the variable code will be UED variable code
      ,const CORN::Date         &on_date)                          rectification_=0;//151119
*/
   virtual void set_precipitation_intervals_mm                                   //990425
      (const CORN::Date_const &date_
      ,const CORN::Time &_time                                                   //990505
      ,const CORN::Dynamic_array<float32> &precip_in_intervals
      ,CORN::Minutes interval_time_minutes                                       //990425
      ,CORN::Quality &attribute)                                             =0;
   virtual void set_temperature_intervals                                        //021124
      ( const CORN::Date_const &date_                                            //021124
      ,const CORN::Dynamic_array<float32> &temperature_in_intervals              //021124
      ,CORN::Minutes interval_time_minutes                                       //990425
      ,CORN::Quality &attribute)                                             =0;
   inline virtual void set_preferred_ext(const char */*pref_ext*/)            {} //001010
   inline virtual bool is_daily_data_available_for
      (CORN::Year /*year*/
      ,UED_variable_code /*variable_to_check = 0*/)
      { return true; }
   inline virtual void reset_buffers()                                        {}
   inline virtual void set_override_safety
      (bool _override_set_safety)                               modification_=0; // actually this is a contribute
#ifndef LOC_ONLY_FOR_GEN
   virtual const Location_parameters *get_location_parameters()         const=0; //090303
      // This needs to be pointers (does not necessarily have location)
#endif
   virtual const Geolocation         *get_geolocation_constant()        const=0; //050525
      // This needs to be pointers (does not necessarily have location)
   virtual const char *get_description(std::string &return_buffer)      const=0; //050525
   //180830 virtual const wchar_t  *get_key_wide()      const { assert(false); return 0;} //130406
   inline virtual bool is_today_valid()                   const { return true; } //111106 added for REACCH
   virtual CORN::date32 get_earliest_available_date()                   const=0; //140911
   virtual bool is_good()                                               const=0; //140728
   virtual bool done_with_dates_before
      (const CORN::Date_const &/*earliest_date*/)               { return true; } //141103
};
//______________________________________________________________________________
class Annual_data_status
: public CORN::Item
{
   enum statuses {UNKNOWN,FILE_NOT_EXISTS,FILE_EXISTS,AVAILABLE_DATA_KNOWN};
   CORN::Year   year;
   statuses    status;
   bool        has_precipitation;
   bool        has_max_temperature;
   bool        has_min_temperature;
   bool        has_solar_radiation;
   bool        has_max_relative_humidity;
   bool        has_min_relative_humidity;
   bool        has_max_dewpoint_temperature;
   bool        has_min_dewpoint_temperature;
   bool        has_wind_speed;
   bool        has_pot_evapotranspiration;
   bool        has_avg_daytime_vapor_pressure_deficit;
   bool        has_avg_fullday_vapor_pressure_deficit;                           //011009
//NYI               bool        has_max_vapor_pressure_deficit;
 public:
   inline Annual_data_status
      (CORN::Year _year
      ,statuses   _status)
      : year   (_year)
      , status (_status)
      {}
 public: // inherited methods
   inline virtual int compare(const CORN::Item &other) const                     //980511
   {  Annual_data_status other_annual_data_status = (Annual_data_status &)other;
      return (year < other_annual_data_status.year)
      ? -1
      : (year > other_annual_data_status.year) ? 1 : 0;
   }
};
//______________________________________________________________________________
#endif

