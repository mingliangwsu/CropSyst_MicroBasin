#include "weather/parameter/WC_humidity_specific.h"
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#include "corn/quality.hpp"
/*check needed
#include "weather/weather_types.h"
#include "weather/loc_param.h"

#include "weather/parameter/WP_precipitation.h"

#include "weather/parameter/WP_air_temperature.h"
#include "weather/parameter/WP_dew_point_temperature.h"
#include "weather/parameter/WP_vapor_pressure_deficit.h"
*/

using namespace CORN;

#ifdef DETAIL_TRACE
#include <fstream>
using namespace std;
extern int trace_indent;
extern std::ofstream trace;
#endif
//______________________________________________________________________________
Humidity_specific_calculator::Humidity_specific_calculator
(
/*check needed
 Dew_point_temperature_average *_dew_point_temperature_avg
, Vapor_pressure_deficit_max    *_vapor_pressure_deficit_max
,Air_temperature_maximum         *_air_temperature_max
*/
)
: Humidity_specific()
/*
, dew_point_temperature_avg(_dew_point_temperature_avg)
, vapor_pressure_deficit_max(_vapor_pressure_deficit_max)
, air_temperature_max(_air_temperature_max)
, generation_parameters(0)
*/
{}
//_constructor______________________________________________________2018-08-08_/
/*probably not needed
float64 Humidity_specific_calculator::set_value_quality
(float64 _value
,const CORN::Quality &new_quality
,bool override_safety)                                                  mutation_
{  // Require Rel humidity to be between 0 and 100.
   // We don't even allow valid values to be out of range
   // but if it is valid sofar, change the quality to indicate that it has been interpolated.
   // we do preserve measured values at this point. (probably should mark it out of range, but this is left to validator).
   float64 result = 0;
   if (new_quality.is_valid())
   {  CORN::Quality_code swapped_quality = new_quality.get_quality_code();
      if (_value > max_valid_relative_humidity)
      {  _value = max_valid_relative_humidity; swapped_quality = quality_interpolated_from_quality(new_quality); }
      else if (_value < min_valid_relative_humidity)
      {  _value =min_valid_relative_humidity;  swapped_quality = quality_interpolated_from_quality(new_quality); }
      result = update_value_qualified_code(_value,swapped_quality);
   }
   return result;
}
*/

const CORN::Quality & Humidity_specific_calculator::update()      rectification_
{  if (is_empty())  // this is a litle hack until I fix setting invalid quality in the UED weather editor 091204
      assume_code(missing_quality);
   if (is_valid())
   {}
   else
   {  if (updating)
      {  // We are already updating, so don't come here yet again
      } else
      {  updating = true;
         CORN::Quality_clad RHmax_quality;

      }
   }
   return get_quality();
}
//_Humidity_specific_calculator::update_____________________________2018-08-08_/

//==============================================================================
