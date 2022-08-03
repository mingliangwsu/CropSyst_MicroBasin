#ifndef WC_vapor_pressure_actH
#define WC_vapor_pressure_actH

#include "weather/parameter/WC_vapor_pressure.h"
#include "weather/parameter/WP_vapor_pressure_act.h"
// Forward declarations
class Dew_point_temperature_minimum;
class Dew_point_temperature_average;
class Relative_humidity;

class Vapor_pressure_deficit_max;
class Vapor_pressure_deficit;
//______________________________________________________________________________
class Vapor_pressure_actual_calculator    // rename this to Vapor_pressure_actual_calculator
: public extends_ Vapor_pressure_actual
, public extends_ Vapor_pressure_parameter
{  // This may be use for daily or instantaneous values
   Vapor_pressure_deficit_max       *vapor_pressure_deficit_max;                 //050506
   Dew_point_temperature_minimum    *dew_point_temperature_min; // May be 0 if unknown
   Relative_humidity                *relative_humidity_max;     // May be 0 if unknown
   Vapor_pressure_deficit           *vapor_pressure_deficit;    // fullday May be 0 if unknown (used calculating from VPD)  //080617
   Dew_point_temperature_average    *dew_point_temperature_avg; // May be 0 if unknown  //100230
 public:
   //140220 Vapor_pressure_actual_parameter
   Vapor_pressure_actual_calculator                                              //140220
      (Vapor_pressure_deficit_max      *_vapor_pressure_deficit_max
      ,Vapor_pressure_deficit          *_vapor_pressure_deficit      // May be 0 if unknwon //080617
      ,Dew_point_temperature_maximum   *_dew_point_temperature_max   // May be 0 if unknown  // used by Vapor_pressure_deficit_parameter and Vapor_pressure_actual_parameter
      ,Dew_point_temperature_minimum   *_dew_point_temperature_min   // May be 0 if unknown
      ,Relative_humidity               *_relative_humidity_max       // May be 0 if unknown
      ,Relative_humidity               *_relative_humidity_min       // May be 0 if unknown  // used by Vapor_pressure_deficit_parameter and Vapor_pressure_actual_parameter
      ,Air_temperature_maximum         *_air_temperature_max         // May be 0 if unknown
      ,Air_temperature_minimum         *_air_temperature_min         // May be 0 if unknown
      ,Dew_point_temperature_average   *_dew_point_temperature_avg);             //100302

      // Use this constructor if any potential combination of relative humidity, or dewpt, or only temperature is known

   Vapor_pressure_actual_calculator                                              //140220
      (Vapor_pressure_deficit_max   &_vapor_pressure_deficit_max
      ,Relative_humidity            &_relative_humidity_max
      ,Relative_humidity            &_relative_humidity_min
         // used by Vapor_pressure_deficit_parameter and Vapor_pressure_actual_parameter
      ,Air_temperature_maximum      &_air_temperature_max
      ,Air_temperature_minimum      &_air_temperature_min);
      // Use this constructor if relative humidity and air temperature are known

      // NYI could also have a constructor if only average daily dewpoint temperature is known  //100322

   // NYI could also have a constructor for known dewpt temperature max and min, but not currently needed
   // NYI could also have a constructor if only RH_average is known
   //     however calc from RH_average should be used at last resort

   Vapor_pressure_actual_calculator                                              //140220
      (Vapor_pressure_deficit_max   &_vapor_pressure_deficit_max
      ,Air_temperature_maximum      &_air_temperature_max
      ,Air_temperature_minimum      &_air_temperature_min
      ,Vapor_pressure_deficit       *_vapor_pressure_deficit);    // May be 0 if unknown
   virtual const CORN::Quality &update()                          rectification_;//080908
   float64 calc_from_dew_point
      (float64 min_dew_point_temp
      ,float64 max_dew_point_temp
      ,float64 min_air_temp
      ,float64 max_air_temp
      ,bool over_water_only = true)                                        const;
   float64 calc_from_relative_humidity                                           //020725
      (float64 min_rel_humid
      ,float64 max_rel_humid
      ,float64 min_temp
      ,float64 max_temp
      ,bool over_water_only = true)                                        const;
   float64 calc_from_dew_point_avg                                               //100322
      (float64 avg_dew_point_temp
      ,bool over_water_only = true)                                        const;
   float64 calc_from_vapor_pressure_deficit                                      //080617
      (float64 VPD
      ,float64 max_temp
      ,float64 min_temp
      ,bool over_water_only = true)                                        const;
 private: // accessors
   bool is_valid_dew_point_temperature()                                   const;
   bool is_relative_humidity_better_than_derived()                         const;//100412
   bool is_valid_temperature()                                             const;
};
//______________________________________________________________________________
#endif

