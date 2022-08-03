#ifndef WC_dew_point_temperatureH
#define WC_dew_point_temperatureH
#include "weather/parameter/WP_dew_point_temperature.h"

#ifdef ALREADY_DEFINED
#include "weather/parameter/WP_temperature.h"
#include "weather/weather_types.h"

class Vapor_pressure_deficit_max;
class Vapor_pressure_nighttime;
class Vapor_pressure_nighttime_calculator;
class Relative_humidity;                                                         //140220
class Air_temperature_maximum ;
class Air_temperature_minimum ;
class Air_temperature_average ;
class Dew_point_temperature_average;
class Location_parameters;
#endif
//______________________________________________________________________________
class Dew_point_temperature_calculator
: public Dew_point_temperature
{public:
   Dew_point_temperature_calculator();
   Dew_point_temperature_calculator(float64 _value, CORN::Quality_code   _quality);
   float64 calculate          (float64 max_or_min_rel_humid_valid, float64 min_or_max_temp_valid) calculation_;
   float64 estimate_crude     (float64 rel_humid, float64 air_temperature_dry_bulb, CORN::Quality &quality) calculation_; //130218
   float64 estimate_Magnus    (float64 relative_humidity,float64 air_temperature)    calculation_; //130218
   float64 estimate_Arden_Buck(float64 relative_humidity,float64 air_temperature)calculation_; //130218
};
//______________________________________________________________________________
class Dew_point_temperature_maximum_calculator                                   //140220
: public Dew_point_temperature_calculator
{  Relative_humidity             *relative_humidity_min;       // May be 0 if unknown
   Air_temperature_maximum       *air_temperature_max;         // May be 0 if unknown
   Vapor_pressure_deficit_max    *vapor_pressure_deficit_max;  // May be 0 if unknown
   Dew_point_temperature_average *dew_point_temperature_avg;                     //081106
 public:
   Dew_point_temperature_maximum_calculator
      (Relative_humidity            *_relative_humidity_min
      ,Air_temperature_maximum      *_air_temperature_max
      ,Vapor_pressure_deficit_max   *_vapor_pressure_deficit_max
      ,Dew_point_temperature_average*_dew_point_temperature_avg               //081106
      );
   virtual float64 calculate_from_min_relative_humidity(CORN::Quality &calculated_quality) calculation_;
   virtual const CORN::Quality &update()                          rectification_;//080908
   virtual float64 generate(CORN::Quality &gen_max_dew_point_temperature_quality);
};
//______________________________________________________________________________
class Dew_point_temperature_average_calculator
: public Dew_point_temperature_calculator
{public:
   Air_temperature_average *air_temperature_avg;
   Relative_humidity       *relative_humidity_avg;
 public:
   inline
      Dew_point_temperature_average_calculator
      (Air_temperature_average   *_air_temperature_avg=0
      ,Relative_humidity         *_relative_humidity_avg =0)
      : Dew_point_temperature_calculator()
      , air_temperature_avg(_air_temperature_avg)
      , relative_humidity_avg(_relative_humidity_avg)
      {}
   virtual const CORN::Quality &update()                          rectification_;
};
//______________________________________________________________________________
class Dew_point_temperature_minimum_calculator                                   //140220
: public Dew_point_temperature_calculator
{private : // parameters for estimation
   Relative_humidity          *relative_humidity_max;    // May be 0 if unknown owned by caller
   Air_temperature_minimum    *air_temperature_min;      // May be 0 if unknown owned by caller
private : // parameters for generation
   const Location_parameters  *location;// May be 0 if unknown owned by caller
   Season_S_W_SF              *season;  // May be 0 if unknown owned by caller
   // NOTE: this is the weather_base season for dew pt temperature not the normal season
   Dew_point_temperature_maximum *dew_point_temperature_max;// May be 0 if unknown owned by caller
   Dew_point_temperature_average *dew_point_temperature_avg;                     //081106
private: // for the case when when need to VPmin from regression of VPmax
   Vapor_pressure_nighttime      *vapor_pressure_min;  // may be null if unknown //081027
public:
   Dew_point_temperature_minimum_calculator
      (Relative_humidity               *_relative_humidity_max
      ,Air_temperature_minimum         *_air_temperature_min
      ,Dew_point_temperature_maximum   *_dew_point_temperature_max
      ,const Location_parameters       *_location
      ,Season_S_W_SF                   *_season
      ,Vapor_pressure_nighttime        *_vapor_pressure_min                      //081027
      ,Dew_point_temperature_average   *dew_point_temperature_avg);              //081106
   virtual const CORN::Quality &update()                          rectification_;//080908
   virtual float64 calculate_from_max_relative_humidity(CORN::Quality &calculated_quality) calculation_;
   virtual float64 calculate_from_vapor_pressure_min(CORN::Quality &calculated_quality) calculation_; //081027
};
//______________________________________________________________________________
#endif

