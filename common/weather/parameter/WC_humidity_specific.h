#ifndef WC_humidity_specificH
#define WC_humidity_specificH
#include "weather/parameter/WP_humidity_specific.h"

/* check needed
#include "weather/weather_types.h"
//170525 #include "corn/datetime/date.hpp"
#include "corn/chronometry/time_types.hpp"
#include "weather/parameter/WP_dew_point_temperature.h"

#ifdef ALREADY_INCLUDED
#include "weather/parameter/weather_parameter.h"

   // for Season_S_W_SF
#include "UED/library/codes.h"
#include "corn/const.h"
#endif
// Forward declarations:
class Precipitation;                                                             //101215
class Dew_point_temperature_minimum;
class Dew_point_temperature_average;
class Dew_point_temperature_maximum;
class Air_temperature_minimum ;
class Air_temperature_maximum ;
class Vapor_pressure_deficit_max;
//140220 class Vapor_pressure_nighttime_parameter;
class Vapor_pressure_nighttime;                                                  //140220

//struct Relative_humidity_extremes;                                               //091216
*/
//______________________________________________________________________________

class Humidity_specific_calculator
: public extends_ Humidity_specific
{
 protected:
/* check Needed
   Dew_point_temperature_average   *dew_point_temperature_avg;   // May be 0 if unknown
   Vapor_pressure_deficit_max      *vapor_pressure_deficit_max;                  //081016
   Air_temperature_maximum         *air_temperature_max;  // May be 0 if unknown   081016
   contribute_ const Relative_humidity_extremes *generation_parameters;          //091216
      // Only applies to ClimGen generation
   contribute_ const Season_S_W_SF              *current_season_known;           //091217
      // reference the weather season
*/      
 public:
   inline Humidity_specific_calculator                                           //070212
      (float64 _value, const CORN::Quality &_quality)                            //070212
      : Humidity_specific()                                                      //140220
/*check needed      
      , dew_point_temperature_avg(0)                                             //081016
      , vapor_pressure_deficit_max(0)                                            //081016
      , air_temperature_max(0)                                                   //081016
      , generation_parameters(0)                                                 //091216
*/      
      {  /*set_value_quality(_value,_quality,true);*/ }                              //151001

   Humidity_specific_calculator                                                  //140220
      (
      /* Check needed
      Dew_point_temperature_average   *_dew_point_temperature_avg
      ,Vapor_pressure_deficit_max      *_vapor_pressure_deficit_max              //081016
      ,Air_temperature_maximum         *_air_temperature_max
      */
      );  // May be 0 if unknown //081016
  virtual const CORN::Quality &update()                          rectification_; //080908

/*
   virtual float64 set_value_quality                                             //150121
      (float64 _value
      ,const CORN::Quality &_quality
      ,bool override_safety = false)                                   mutation_;//090312
*/
/*probably not needed      
   void know_generation_parameters                                               //091216
      (const Relative_humidity_extremes &generation_parameters
      ,const Season_S_W_SF &current_season_known)                  contribution_;
*/
};
//______________________________________________________________________________
/*
class Humidity_mixing_ratio_calculator
: public extends_ Humidity_mixing_ratio
{
 public:
   Humidity_mixing_ratio_calculator
      (
      );
};
//______________________________________________________________________________
*/


#endif
