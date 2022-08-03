#include "weather/parameter/WC_vapor_pressure.h"
#include <math.h>
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#include "weather/weather_types.h"
#include "weather/loc_param.h"
#include "weather/parameter/WP_vapor_pressure_act.h"
#include "weather/parameter/WP_air_temperature.h"
#include "weather/parameter/WP_relative_humidity.h"
#include "weather/parameter/WP_dew_point_temperature.h"
#include "corn/math/moremath.h"
#include "corn/math/random.hpp"
#ifndef measuresH
#  include "corn/measure/measures.h"
#endif
using namespace CORN;
//______________________________________________________________________________
Vapor_pressure_parameter::Vapor_pressure_parameter
(Dew_point_temperature_maximum   *_dew_point_temperature_max// May be 0 if unknown
,Relative_humidity               *_relative_humidity_min    // May be 0 if unknown
,Air_temperature_maximum         *_air_temperature_max      // May be 0 if unknown
,Air_temperature_minimum         *_air_temperature_min)     // May be 0 if unknown
:dew_point_temperature_max (_dew_point_temperature_max)     // used by Vapor_pressure_deficit_parameter and Vapor_pressure_actual_parameter
,relative_humidity_min     (_relative_humidity_min)         // used by Vapor_pressure_deficit_parameter and Vapor_pressure_actual_parameter
,air_temperature_max       (_air_temperature_max)
,air_temperature_min       (_air_temperature_min)
{}
//______________________________________________________________________________
Vapor_pressure_daytime_calculator::Vapor_pressure_daytime_calculator
   (Dew_point_temperature_maximum  *_dew_point_temperature_max
   ,Air_temperature_maximum         *_air_temperature_max)
: Vapor_pressure_daytime()                                                       //140220
, dew_point_temperature_max(_dew_point_temperature_max)
, air_temperature_max(_air_temperature_max)
   // optional, if not provided we presume non freezing conditions
, relative_humidity_min(0)                                                       //081027
{}
//______________________________________________________________________________
Vapor_pressure_daytime_calculator::Vapor_pressure_daytime_calculator
(Relative_humidity      *_relative_humidity_min
,Air_temperature_maximum         *_air_temperature_max)
: Vapor_pressure_daytime()                                                       //140220
, dew_point_temperature_max(0)
, air_temperature_max(_air_temperature_max)
   // optional, if not provided we presume non freezing conditions
, relative_humidity_min(_relative_humidity_min)                                  //081027
{}
//______________________________________________________________________________
Vapor_pressure_daytime_calculator::Vapor_pressure_daytime_calculator
// use this constructor when ether dew_point_temperature_max or relative_humidity_minis available
(Dew_point_temperature_maximum  *_dew_point_temperature_max
,Relative_humidity      *_relative_humidity_min
,Air_temperature_maximum        *_air_temperature_max)
: Vapor_pressure_daytime()                                                       //140220
, dew_point_temperature_max(_dew_point_temperature_max)
, air_temperature_max(_air_temperature_max)  // optional, if not provided we presume non freezing conditions
, relative_humidity_min(_relative_humidity_min)                                  //081027
{}
//______________________________________________________________________________
const CORN::Quality &Vapor_pressure_daytime_calculator::update()   rectification_
{  if (!updating)                                                                //081027
   {  updating = true;                                                           //081027
   if (!dew_point_temperature_max && !relative_humidity_min)
      assume_code(CORN::missing_quality);                                        //150123
   else
   {  // If relative humidity and dew_point temperature both have the same quality,
      // give preference to min relative humidity because it will be the basis of all calculations if it was generated from aridity factor and VPDmax
      if (dew_point_temperature_max)
      {  float64 DPmax = dew_point_temperature_max->Celcius();
         float64 VP_DewPt_max = calc_saturation_kPa  // The saturation vapor pressure at dewpt_max is vapor pressure max
            (DPmax
            ,air_temperature_max ? air_temperature_max->Celcius() : 10.0
            // air_temperature_max is used only to select the
            // freezing/nonfreezing coefficients
            // This is not to critical, so if air temp is not provided,
            // we assume non-freezing conditions.
            ,OVER_WATER_ONLY);
         Quality_clad calc_from_dewtp_max_qual(quality_calculated_from_quality(*dew_point_temperature_max));
         update_value_qualified(VP_DewPt_max,calc_from_dewtp_max_qual);          //150121
      }
      if (relative_humidity_min && air_temperature_max)
      {  CORN::Quality_clad calc_from_RHmin_VPsat_at_Tmax_qual;
         float64 VP_max = calc_from_RHmin_VPsat_at_Tmax(calc_from_RHmin_VPsat_at_Tmax_qual);

                // 091207  VP_max should be called VP_noon

         update_value_qualified(VP_max,calc_from_RHmin_VPsat_at_Tmax_qual);      //150121
      }
   }
    updating = false ; }                                                         //081027
   return get_quality();
}
//_2008-10-24___________________________________________________________________
float64 Vapor_pressure_daytime_calculator::calc_from_RHmin_VPsat_at_Tmax
(CORN::Quality &calc_from_RHmin_VPsat_at_Tmax_qual) const
{  float64 VP_max = 0.0;        // rename to VP_daytime
   if (relative_humidity_min && air_temperature_max)
   {  //150123 Quality_clad RHmin_qual;
      const Quality &contrib_qual = relative_humidity_min->worst(*air_temperature_max);//150123
      if (contrib_qual.is_valid())
      {  calc_from_RHmin_VPsat_at_Tmax_qual.assume_code
            (quality_calculated_from_quality(contrib_qual));                     //150123
         float64 RHmin = relative_humidity_min->percent();                       //150123
         float64 Tmax =  air_temperature_max->Celcius();                         //150123
         VP_max = RHmin * calc_saturation_kPa(Tmax, Tmax,OVER_WATER_ONLY) / 100.0;
      }
   } else
      calc_from_RHmin_VPsat_at_Tmax_qual.assume_code(missing_quality);              //150123
   return  VP_max;
}
//_2008-10-24___________________________________________________________________
float64 Vapor_pressure_nighttime_calculator::calc_from_RHmax_VPsat_at_Tmin
(CORN::Quality &calc_from_RHmax_VPsat_at_Tmin_qual) const
{  float64 VP_nighttime = 0.0;
   if (relative_humidity_max && air_temperature_min)
   {  const Quality &contrib_qual = relative_humidity_max->worst(*air_temperature_min);
      if (contrib_qual.is_valid())
      {  calc_from_RHmax_VPsat_at_Tmin_qual.assume_code(quality_calculated_from_quality(contrib_qual)); //150123
         float64 RHmax = relative_humidity_max->percent();
         float64 Tmin  = air_temperature_min  ->Celcius();
         VP_nighttime = RHmax * calc_saturation_kPa(Tmin, Tmin, OVER_WATER_ONLY) / 100.0;
      };
   } else
      calc_from_RHmax_VPsat_at_Tmin_qual.assume_code(missing_quality);
   return VP_nighttime;
}
//_2008-10-24___________________________________________________________________
const CORN::Quality & Vapor_pressure_nighttime_calculator::update()rectification_
{
   if (!updating)                                                                //081027
   {  updating = true;                                                           //081027
      // When generating we must first calculate VP night time from              //091210
      CORN::Quality_clad calc_from_RHmax_VPsat_at_Tmin_qual;                //081027
      float64 VP_nighttime = calc_from_RHmax_VPsat_at_Tmin
            (calc_from_RHmax_VPsat_at_Tmin_qual);
      update_value_qualified(VP_nighttime,calc_from_RHmax_VPsat_at_Tmin_qual);        //150121
      if (vapor_pressure_daytime && generation_parameters)                       //091212
      {  if (!CORN::is_approximately<float32>(generation_parameters->intercept,0.0,0.000001))
         {  // First estimate based on site analysis regression
            //150123 CORN::Quality_clad VP_daytime_quality;

            if (vapor_pressure_daytime->is_valid())
            {  // estimate from regression // First estimate
               float64 VP_daytime = vapor_pressure_daytime->get_kPa();              //150123
               VP_nighttime = VP_daytime * generation_parameters->slope + generation_parameters->intercept;
               CORN::Quality_clad VP_nighttime_quality(quality_estimated_from_quality(*vapor_pressure_daytime));  //091210
               update_value_qualified( VP_nighttime, VP_nighttime_quality); // This will have the same quality  //091217
#ifdef OBSOLETE
091215 but keep may need again
               {  // Apply a randomized component (second estimate)

                  // Half the time the random component will be above the regression line,
                  // half the time it will be below
                  float64 random_range = VP_nighttime * generation_parameters->random_range_slope;
                  float64 above_or_below_regression_line =  (rand() > 0.5) ? 1.0 : -1.0;
                  float64 random_component = random_range * above_or_below_regression_line;
                  VP_nighttime += random_component;
                  CORN::Quality_clad VP_nighttime_quality(CORN::quality_estimated_from_quality(*vapor_pressure_daytime));
                  set(VP_nighttime,VP_nighttime_quality); // This will have the same quality
               }
#endif
            }
         }
      } // else we just just the result of calc_from_RHmax_VPsat_at_Tmin
      updating = false;                                                          //081027
   }
   return get_quality();
}
//_2008-10-24___________________________________________________________________
Vapor_pressure_nighttime_calculator::Vapor_pressure_nighttime_calculator
// Use when dew point temperature is available
(Dew_point_temperature_minimum  *_dew_point_temperature_min
,Air_temperature_minimum         *_air_temperature_min)
: Vapor_pressure_nighttime()                                                     //140220
, dew_point_temperature_min      (_dew_point_temperature_min)
, air_temperature_min            (_air_temperature_min)
, vapor_pressure_daytime         (0)
, generation_parameters             (0)                                          //091210
{}
//______________________________________________________________________________
Vapor_pressure_nighttime_calculator::Vapor_pressure_nighttime_calculator
// Use when vapor pressure has been parameterized by ClimGen (for generation)
(Vapor_pressure_daytime         *_vapor_pressure_daytime
,Dew_point_temperature_maximum  *_dew_point_temperature_max)                     //081030
: Vapor_pressure_nighttime()                                                     //140220
, dew_point_temperature_min      (0)
, air_temperature_min            (0)
, generation_parameters          (0)                                             //091214_091210
{}
//______________________________________________________________________________
Vapor_pressure_nighttime_calculator::Vapor_pressure_nighttime_calculator
// Use when relative humidity maximum and min air temperature is known
(Relative_humidity  *_relative_humidity_max
,Air_temperature_minimum   *_air_temperature_min)
: Vapor_pressure_nighttime()                                                     //140220
, air_temperature_min   (_air_temperature_min)
, relative_humidity_max (_relative_humidity_max)
, generation_parameters (0)                                                      //091210
, vapor_pressure_daytime         (0)
, dew_point_temperature_min      (0)
{}
//______________________________________________________________________________
Vapor_pressure_nighttime_calculator::Vapor_pressure_nighttime_calculator
// Use when there may be dew point temperature and/or ClimGen parameters
(Dew_point_temperature_minimum   *_dew_point_temperature_min
,Dew_point_temperature_maximum   *_dew_point_temperature_max                     //081030
,Air_temperature_minimum         *_air_temperature_min
,Vapor_pressure_daytime          *_vapor_pressure_daytime
,Relative_humidity               *_relative_humidity_max)
: Vapor_pressure_nighttime()                                                     //140220
, dew_point_temperature_min      (_dew_point_temperature_min)
, dew_point_temperature_max      (_dew_point_temperature_max)                    //081030
, air_temperature_min            (_air_temperature_min)
, vapor_pressure_daytime         (_vapor_pressure_daytime)
, relative_humidity_max          (_relative_humidity_max)
, generation_parameters          (0)                                             //091210
{}
//______________________________________________________________________________
void Vapor_pressure_nighttime_calculator::know_generation_parameters
(const Vapor_pressure_night_time_parameters &_generation_parameters) contribution_
{  generation_parameters = &_generation_parameters;
}
//_2009-12-14___________________________________________________________________

