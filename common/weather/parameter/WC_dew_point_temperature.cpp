#include "weather/parameter/WC_dew_point_temperature.h"
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#include <math.h>
#include "corn/math/moremath.h"
#include "weather/weather_types.h"
#include "weather/parameter/WP_vapor_pressure.h"
#include "weather/parameter/WP_vapor_pressure_deficit.h"
#include "weather/parameter/WP_air_temperature.h"
#ifndef qualityHPP
#  include "corn/quality.hpp"
#endif
#ifndef constH
#  include "corn/const.h"
#endif
#include "weather/parameter/WP_relative_humidity.h"
#include <iostream>

using namespace CORN;
//______________________________________________________________________________
Dew_point_temperature_calculator::Dew_point_temperature_calculator()
: Dew_point_temperature()                                                        //140220
{}
//________________________________Dew_point_temperature_calculator::constructor_/
Dew_point_temperature_calculator::Dew_point_temperature_calculator(float64 _value, CORN::Quality_code _quality)
: Dew_point_temperature()                                                        //140220
{}
//________________________________Dew_point_temperature_calculator::constructor_/
float64 Dew_point_temperature_calculator::calculate(float64 max_or_min_rel_humid, float64 min_or_max_temp) calculation_
{  // At this point max_or_min_rel_humid  and min_or_max_temp will be vetted as valid
   //float32 VP_data; CORN::Units_code VP_units =UC_kPa;  CORN::Quality_code VP_quality;
/*
//netCDF_to_UED downloading bad data
if (min_or_max_temp < -100)
return 10.0;
*/

if (min_or_max_temp > 100)
{  std::cerr << "X";
   return 10.0;  // This shouldn't happen.
}


   Vapor_pressure_base vapor_pressure;                                           //150123_050602
      // Doesn't need to set parameters
   float64 VPsat_airtemp = vapor_pressure.calc_saturation_kPa                    //050901
         (min_or_max_temp,min_or_max_temp, OVER_WATER_ONLY );
   float64 VPsat_dewpt = max_or_min_rel_humid / 100.0 * VPsat_airtemp;           //081031
   float64 dew_pt_temp = vapor_pressure.saturation_temperature
      (VPsat_dewpt,min_or_max_temp,OVER_WATER_ONLY);                             //040114
   return dew_pt_temp;
}
//_2000-07-13________________________________________________________calculate_/
/*
There are several different constant sets in use.
These are taken from Journal of Applied Meteorology and Climatology [Arden Buck]
Have accuracy of < 0.05%
// Ref: http://en.wikipedia.org/wiki/Dew_point
*/
static const float64 a     = 6.112;       // I believe this is in millibar
static const float64 b[2]  = {  17.368 , 17.966 };
static const float64 c[2]  = { 238.88 , 247.15 };  // celcius
static const float64 d     = 234.5;                // celcius
// Index 0 = above freezing
// Index 1 = freezing
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
float64 Dew_point_temperature_calculator::estimate_Magnus
(float64 relative_humidity
,float64 air_temperature)                                                  const
{  // Ref: http://en.wikipedia.org/wiki/Dew_point
   bool freezing = air_temperature < 0.0;
   float64 g = CORN_ln(relative_humidity/100.0)
      +     b[freezing] * air_temperature
        / ( c[freezing] + air_temperature);
   float64 dew_pt_temp = (c[freezing] * g) / ( b[freezing] - g );
   return dew_pt_temp;
}
//_2013-02-18__________________________________________________estimate_Magnus_/
float64 Dew_point_temperature_calculator::estimate_Arden_Buck
(float64 relative_humidity
,float64 air_temperature)                                                  const
{  // Ref: http://en.wikipedia.org/wiki/Dew_point
   bool freezing = air_temperature < 0.0;
   float64 g = CORN_ln(relative_humidity/100.0
      * exp (( b[freezing] - (air_temperature / d))
            *(air_temperature / ( c[freezing] + air_temperature))));
   float64 dew_pt_temp = (c[freezing] * g) / ( b[freezing] - g );
   return dew_pt_temp;
}
//_2013-02-18______________________________________________estimate_Arden_Buck_/
float64 Dew_point_temperature_calculator::estimate_crude
(float64 relative_humidity
, float64 air_temperature_dry_bulb
, CORN::Quality &quality)                                                  const
{  float64 dew_pt_temp = 0.0;
   dew_pt_temp = air_temperature_dry_bulb - ((100.0 - relative_humidity) / 5.0);
   if (relative_humidity > 50.0)
   {
   /*  http://en.wikipedia.org/wiki/Dew_point
      Very simple approximation.
      This approach is accurate to within about ±1°C as long as the relative humidity is above 50%:
   */
      quality.assume_code(CORN::estimated_quality);
   }
   else if (relative_humidity > 30.0)
      quality.assume_code(quality_estimated_from(CORN::estimated_quality));
   else
      quality.assume_code(not_valid_quality);
   return dew_pt_temp;
}
//_2013-02-18___________________________________________________estimate_crude_/
//==============================================================================
Dew_point_temperature_maximum_calculator::Dew_point_temperature_maximum_calculator
(Relative_humidity               *_relative_humidity_min
,Air_temperature_maximum         *_air_temperature_max
,Vapor_pressure_deficit_max      *_vapor_pressure_deficit_max
,Dew_point_temperature_average   *_dew_point_temperature_avg)                    //081106
: Dew_point_temperature_calculator  ()
, relative_humidity_min             (_relative_humidity_min)
, air_temperature_max               (_air_temperature_max)
, vapor_pressure_deficit_max        (_vapor_pressure_deficit_max)
, dew_point_temperature_avg         (_dew_point_temperature_avg)                 //081106
{}
//______________________________________________________________________________
#ifdef NYN
float64 Dew_point_temperature_maximum_calculator::set
   (float64 _value,not_const CORN::Quality_code &_quality,bool allow_calculate_or_estimate)
{  Dew_point_temperature_calculator::set(_value,_quality,allow_calculate_or_estimate);
}
#endif
//______________________________________________________________________________
const CORN::Quality & Dew_point_temperature_maximum_calculator::update() rectification_
{  if (is_empty())                                                               //091204
      // this is a litle hack until I fix setting invalid quality in the UED weather editor
       assume_code(missing_quality);                                             //150123_091204
    if (!is_optimal())                                                           //081028
      // probably don't need to recalculate this (!is_measured())
   {  if (!updating)                                                             //081027
      {  updating = true;                                                        //081027
         {  CORN::Quality_clad calc_quality;
            float64 calc_value = calculate_from_min_relative_humidity(calc_quality);
            Dew_point_temperature_calculator::update_value_qualified(calc_value,calc_quality);   //150121
         }
#ifdef OBSOLETE
091226 Claudio decided not to try to estimate from avg DewPt temperature
/*081106_*/          if (dew_point_temperature_avg)
/*081106_*/          {
/*081106_*/             Quality dewpt_avg_qual;
/*081106_*/             float64 dewpt_avg = dew_point_temperature_avg->get(dewpt_avg_qual);
/*081106_*/             if (dewpt_avg_qual.is_real())          // Even though avg dewtp may be real, we are only using it as an approximate
/*081106_*/             {  dewpt_avg_qual.set(other_real_quality);  // But it must be considered 'real' in order to allow parameterization
/*081106_*/                Dew_point_temperature_calculator::set(dewpt_avg,dewpt_avg_qual/*081111 obsolete we now get as needed ,false *//*,false*/);
/*081106_*/             }
/*081106_*/          }
#endif
         updating = false;
      }
   }
   return get_quality(); //150121measure.quality;
}
//_2008-09-08_________________Dew_point_temperature_maximum_calculator::update_/
float64 Dew_point_temperature_maximum_calculator::calculate_from_min_relative_humidity
(CORN::Quality &calculated_quality)                                 calculation_
{  float64 dewpnt_max = 0.0;
   if (relative_humidity_min && air_temperature_max)
   {
      float64 RH_min = relative_humidity_min->get_value_update_if_necessary();   //150125
      float64 Tmax   = air_temperature_max  ->get_value_update_if_necessary();   //150125_070605
      const CORN::Quality &worst_qual   = relative_humidity_min->worst(*air_temperature_max); //150125_070605
      //190719 calculated_quality.assume(worst_qual);                                     //150123_091209
      calculated_quality.assume_code(quality_calculated_from_quality(worst_qual));    //190719_150123_091209
      // Dew point and relative humidity are always the same quality (in the real world measured relative humidity is actually typically calculateded directly from dewpoint temperature_
      dewpnt_max =  (calculated_quality.is_valid())
      ? Dew_point_temperature_calculator::calculate(RH_min,Tmax)
      : 0.0;                                                                     //010602
      // Don't bother calculating if the input data is unusable (but don't let it be 0.0)
   } else                                                                        //081030
      calculated_quality.assume_code(CORN::missing_quality);                     //150123_081030
   return dewpnt_max;                                                            //081030
}
//_2000-07-13_____________________________calculate_from_min_relative_humidity_/
float64 Dew_point_temperature_maximum_calculator::generate(CORN::Quality &gen_max_dew_point_temperature_quality) //  C  This is max dewpt temp
{  float64 dewpt_max = 0.0;
   if (vapor_pressure_deficit_max)  // Air temperature is optional
   {
      const CORN::Quality &VPD_max_qual = vapor_pressure_deficit_max->get_quality()/*150120 .get()*/;      //050609
      if (VPD_max_qual.is_valid())
      {  // Normally we will have air temperature, but if reading measured data set, it is possible that there is dewpt but not air temperature (perhaps only for a day)
         // In this case we assume it is not freezing for the saturation_temperature calculation.
         float64 Tmax = air_temperature_max
            ? air_temperature_max->get_value_update_if_necessary() : 10.0;       //150126_081106
         if (!air_temperature_max || !air_temperature_max->is_valid()) Tmax =  10.0; //150126
         dewpt_max = vapor_pressure_deficit_max->                                               //990423
            saturation_temperature(                                                             //980317
               vapor_pressure_deficit_max->saturation_at_max_dew_point(OVER_WATER_ONLY)         //050602
               ,Tmax,OVER_WATER_ONLY);                                                          //040114
         gen_max_dew_point_temperature_quality.assume_code(quality_generated_from_quality(VPD_max_qual/*.get_code()*/)); //150123
      };
   } else
      gen_max_dew_point_temperature_quality.assume_code(CORN::missing_quality);  //150123
   return dewpt_max;                                                             //980305
}
//_1999-10-12_________________________________________________________generate_/
//==============================================================================
Dew_point_temperature_minimum_calculator::Dew_point_temperature_minimum_calculator
(Relative_humidity               *_relative_humidity_max
,Air_temperature_minimum         *_air_temperature_min
,Dew_point_temperature_maximum   *_dew_point_temperature_max
,const Location_parameters                *_location                             //090303
,Season_S_W_SF                            *_season
,Vapor_pressure_nighttime       *_vapor_pressure_min                             //081027
,Dew_point_temperature_average  *_dew_point_temperature_avg)                     //081106
: Dew_point_temperature_calculator()
, relative_humidity_max(_relative_humidity_max)
, air_temperature_min(_air_temperature_min)
, dew_point_temperature_max(_dew_point_temperature_max)
, location(_location)
, season(_season)
, vapor_pressure_min(_vapor_pressure_min)                                        //081027
, dew_point_temperature_avg(_dew_point_temperature_avg)                          //081106
{}
//_______________________Dew_point_temperature_minimum_calculator::constructor_/
float64 Dew_point_temperature_minimum_calculator::calculate_from_max_relative_humidity(CORN::Quality &calculated_quality) calculation_
{  calculated_quality.assume_code(unknown_quality);                              //150123
   float64 dewpt_temp_min = 0.0;
   if (relative_humidity_max && air_temperature_min)
   {  float64 RH_max = relative_humidity_max->get_value_update_if_necessary();   //150126_081028
      float64 Tmin   = air_temperature_min->get_value_update_if_necessary();     //150126_081028
      const CORN::Quality &worst_qual = relative_humidity_max->worst(*air_temperature_min);  //150126_091209
      //190719 calculated_quality.assume(worst_qual);                                     //150123_091209
      calculated_quality.assume_code(quality_calculated_from_quality(worst_qual));    //190719_150123_091209
      // Dew point and relative humidity are always the same quality (in the real world measured relative humidity is actually typically calculateded directly from dewpoint temperature_
      dewpt_temp_min =  (calculated_quality.is_valid())
      ? Dew_point_temperature_calculator::calculate(RH_max,Tmin)
      : 0.00;  // Don't bother calculating if the input data is unusable (but don't let it be 0.0) //010602
   } else calculated_quality.assume_code(missing_quality);                       //150123_081030
   return dewpt_temp_min;                                                        //081030
}
//_2000-07-13____________________________calculate_from_max_relative_humidity__/
/*150126
float64 Dew_point_temperature_minimum_calculator::calculate_from_max_relative_humidity(CORN::Quality &calculated_quality) calculation_
{  calculated_quality.assume_code(unknown_quality);                              //150123
   float64 dewpt_temp_min = 0.0;
   if (relative_humidity_max && air_temperature_min)
   {  Quality_clad RHmax_qual;  float64 RH_max = relative_humidity_max->get_with_quality(RHmax_qual); //081028
      Quality_clad Tmin_qual;   float64 Tmin   = air_temperature_min->get_with_quality(Tmin_qual); //081028
      const CORN::Quality &worst_qual     = RHmax_qual.worst(Tmin_qual);   //091209
      calculated_quality.assume(worst_qual);                                     //150123_091209
      // Dew point and relative humidity are always the same quality (in the real world measured relative humidity is actually typically calculateded directly from dewpoint temperature_
      dewpt_temp_min =  (calculated_quality.is_valid())
      ? Dew_point_temperature_calculator::calculate(RH_max,Tmin)
      : 0.00;  // Don't bother calculating if the input data is unusable (but don't let it be 0.0) //010602
   } else calculated_quality.assume_code(missing_quality);                       //150123_081030
   return dewpt_temp_min;                                                        //081030
}
//_2000-07-13____________________________calculate_from_max_relative_humidity__/

*/
float64 Dew_point_temperature_minimum_calculator::calculate_from_vapor_pressure_min(CORN::Quality &calculated_quality) calculation_
{  float64 dewpt_min = 0.0;
   if (vapor_pressure_min)
   {
      float64 VP_nighttime = vapor_pressure_min->get_value_update_if_necessary();
      calculated_quality.assume_code(quality_calculated_from_quality(*vapor_pressure_min));
      if (vapor_pressure_min->is_valid())
      {  float Tmin =  air_temperature_min ? air_temperature_min->get_value_update_if_necessary() : 10.0;
         if (Tmin > 100)                                                         //180616
         {  calculated_quality=assume_code(out_of_range_pot_high_error_quality); //180616
            std::cerr << "X";
            return 10.0;                                                         //180616
         }
          dewpt_min = vapor_pressure_min->saturation_temperature // C
            (VP_nighttime
            ,Tmin // Air temperature is not critical, if not available we assume it is not freezing conditions
            ,OVER_WATER_ONLY );
         CORN::Quality_clad dewpt_min_quality(quality_calculated_from_quality(*vapor_pressure_min));  //081028
         update_value_qualified(dewpt_min,dewpt_min_quality);                    //150123_081028
      }
   } else calculated_quality.assume_code(missing_quality);                       //150123
   return dewpt_min;
}
/*150126
float64 Dew_point_temperature_minimum_calculator::calculate_from_vapor_pressure_min(CORN::Quality &calculated_quality) calculation_
{  float64 dewpt_min = 0.0;
   if (vapor_pressure_min)
   {  Quality_clad VP_nighttime_quality;
      float64 VP_nighttime = vapor_pressure_min->get_with_quality(VP_nighttime_quality);
      calculated_quality.assume_code(quality_calculated_from(VP_nighttime_quality.get_code()));
      if (VP_nighttime_quality.is_valid())
      {  Quality_clad Tmin_qual; float Tmin =  air_temperature_min ? air_temperature_min->get_with_quality(Tmin_qual) : 10.0;
          dewpt_min = vapor_pressure_min->saturation_temperature // C
            (VP_nighttime
            ,Tmin // Air temperature is not critical, if not available we assume it is not freezing conditions
            ,OVER_WATER_ONLY );
         CORN::Quality_clad dewpt_min_quality(quality_calculated_from(VP_nighttime_quality.get_code()));  //081028
         update_value_qualified(dewpt_min,dewpt_min_quality);                    //150123_081028
      }
   } else calculated_quality.assume_code(missing_quality);                       //150123
   return dewpt_min;
}
*/
//_2008-10-28________________________________calculate_from_vapor_pressure_min_/
const CORN::Quality & Dew_point_temperature_minimum_calculator::update()        rectification_
{  // Here we calculate Dew_pt a couple of ways given available data, the value with the best quality is the one set.
   if (is_empty()) //150122 CORN::is_approximately<float64>(get_amount()/*150122 value*/,0.0,0.000001))  // this is a litle hack until I fix setting invalid quality in the UED weather editor
      assume_code(missing_quality);                                      //091204
   if (!is_optimal())                                 //150121_081028
   {  if (relative_humidity_max && relative_humidity_max->is_updating())         //091212
         return get_quality(); //Don't attempt to update until RHmax has been updated.
      if (!updating)                                                             //081027
      {  updating = true;
         {  CORN::Quality_clad calc_quality;
            float64 calc_value = calculate_from_max_relative_humidity(calc_quality);
            Dew_point_temperature_calculator::update_value_qualified(calc_value,calc_quality);//150123
         }
         {  // we may get vapor pressure from the regression                     //081027
            CORN::Quality_clad calc_quality;
            float64 calc_value = calculate_from_vapor_pressure_min(calc_quality);
            Dew_point_temperature_calculator::update_value_qualified(calc_value,calc_quality);//150123
         };
#ifdef OBSOLETE
Claudio decided not to attempt to estimate from avg_DewPt temperature
         if (dew_point_temperature_avg)                                          //081106
         {  // Even though avg dewtp may be real, we are only using it as an approximate
            // But it must be considered 'real' in order to allow parameterization
            Quality DP_qual;
            float64 dewpt_avg = dew_point_temperature_avg->get(DP_qual);
            if (DP_qual.is_measured())
            {  DP_qual.set(other_real_quality);
               Dew_point_temperature_calculator::set(dewpt_avg,DP_qual);
            }
         }
#endif
         updating = false;                                                       //081027
      }
   }
   return get_quality();
}
//____________________________Dew_point_temperature_minimum_calculator::update_/
const CORN::Quality &Dew_point_temperature_average_calculator::update()        rectification_
{  if (is_valid())
   {}
   else
   {  if (updating)
      {  // We are already updating, so don't come here yet again
      } else
      {  updating = true;
         if (air_temperature_avg && relative_humidity_avg)
         {  float64 RHavg = relative_humidity_avg->get_value_update_if_necessary(); //150121
            float64 Tavg = air_temperature_avg->get_value_update_if_necessary(); //150121
            if (relative_humidity_avg->is_valid() && air_temperature_avg->is_valid())
            {  update_value_qualified_code
                  (estimate_Arden_Buck(RHavg,Tavg)
                  ,quality_estimated_from_quality(air_temperature_avg->worst(*relative_humidity_avg)/*150127 .get_code()*/));
            }
         }
         /*150126
         {  CORN::Quality_clad RHavg_qual; float64 RHavg = relative_humidity_avg->get_with_quality(RHavg_qual); //150121
            CORN::Quality_clad Tavg_qual;  float64 Tavg = air_temperature_avg->get_with_quality(Tavg_qual); //150121
            if (RHavg_qual.is_valid() && Tavg_qual.is_valid())
            {  update_value_qualified_code
                  (estimate_Arden_Buck(RHavg,Tavg)
                  ,quality_estimated_from(air_temperature_avg->worst(*relative_humidity_avg).get_code()));
            }
         }
         */
         updating = false;
      }
   }
   return get_quality();
}
//_2013-02-18__________________Dew_point_temperature_average_parameter::update_/

