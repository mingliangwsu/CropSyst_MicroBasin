#ifndef WP_air_temperatureH
#define WP_air_temperatureH
#include "common/weather/parameter/WP_temperature.h"
//______________________________________________________________________________
class Air_temperature
: public CS::Temperature
{public:
   inline Air_temperature()
      : CS::Temperature()
      {}
   inline Air_temperature(float64 value_, CORN::Quality_code quality_)
      : CS::Temperature(value_, quality_)
      {}
   inline virtual ~Air_temperature() {}                                          //151204
};
//_2015-11-19___________________________________________________________________
class Air_temperature_minimum
: public Air_temperature
{public:
   inline Air_temperature_minimum()
      : Air_temperature()
      {}
   inline Air_temperature_minimum(float64 value_, CORN::Quality_code quality_)
      :  Air_temperature(value_,  quality_)
      {}
   inline virtual ~Air_temperature_minimum() {}                                  //151204
};
//______________________________________________________________________________
class Air_temperature_maximum
: public Air_temperature
{public:
   inline Air_temperature_maximum()
      : Air_temperature()
      {}
   inline Air_temperature_maximum(float64 value_, CORN::Quality_code quality_)
      :  Air_temperature( value_,  quality_)
      {}
   inline virtual ~Air_temperature_maximum() {}                                  //151204
};
//______________________________________________________________________________
class Air_temperature_average
: public Air_temperature
{public:
   inline Air_temperature_average()
      : Air_temperature()
      {}
   inline Air_temperature_average(float64 value_, CORN::Quality_code quality_)
      :  Air_temperature(value_, quality_)
      {}
   inline virtual ~Air_temperature_average() {}                                  //151204
};
//_2014-02-20___________________________________________________________________

#endif

