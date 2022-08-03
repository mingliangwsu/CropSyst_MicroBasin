#ifndef current_elements_interfaceH
#define current_elements_interfaceH
#ifndef primitiveH
#  include <corn/primitive.h>
#endif
#include <corn/chronometry/date_types.hpp>
#include <corn/chronometry/time_types.hpp>
//______________________________________________________________________________
class Weather_current_interface
{
public:
   virtual CORN::Date32 get_today_date32()                                 const = 0;
public:  // Current date meterological accessors
//   virtual float64 get_curr_max_air_temperature()                          const = 0;
//   virtual float64 get_curr_min_air_temperature()                          const = 0;
//   virtual float64 get_curr_max_temperature()                              const = 0;
//   virtual float64 get_curr_min_temperature()                              const = 0;

//100929   virtual bool    get_temperature_hourly_quality()                        const = 0;
   virtual bool    is_temperature_hourly_valid()                        const = 0;   //100929
   virtual float64 get_est_temperature_at_hour(/*CORN::Hour*/ nat8 hour)   const = 0;
   // Not currently only estimated temperture is available,
   // but actually hourly temperature could be provided in the database.
};
//______________________________________________________________________________
#endif
