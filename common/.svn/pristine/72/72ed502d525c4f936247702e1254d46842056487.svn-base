#ifndef WC_air_temperatureH
#define WC_air_temperatureH
#include "weather/parameter/WP_air_temperature.h"
//______________________________________________________________________________
class Air_temperature_average_calculator
: public Air_temperature_average
{  const Air_temperature_maximum *air_Tmax;  // Not owned (optional)
   const Air_temperature_minimum *air_Tmin;  // Not owned (optional)
public:
   inline
      Air_temperature_average_calculator()
      : Air_temperature_average()
      , air_Tmax(0)
      , air_Tmin(0)
      {}
   inline
      Air_temperature_average_calculator
      (float64 value_, CORN::Quality_code quality_)
      : Air_temperature_average(value_,quality_)
      , air_Tmax(0)
      , air_Tmin(0)
      {}
    inline Air_temperature_average_calculator
      (const Air_temperature_maximum &Tmax_param_
      ,const Air_temperature_minimum &Tmin_param_)
      : Air_temperature_average()
      ,  air_Tmax(&Tmax_param_)
      ,  air_Tmin(&Tmin_param_)
      {}
   virtual const CORN::Quality &update()                         rectification_;
};
//______________________________________________________________________________

#endif

