#include "WC_vapor_pressure_saturation_slope.h"
#include "common/weather/weather_types.h"
#include "corn/math/moremath.h"
#include "physics/property/P_vapor_pressure.h"
//______________________________________________________________________________
Vapor_pressure_saturation_slope_calculator::Vapor_pressure_saturation_slope_calculator
(const Air_temperature_average &_air_temperature_avg)
: Vapor_pressure_saturation_slope()
, air_temperature_avg            (_air_temperature_avg)
{}
//______________________________________________________________________________
float64 Vapor_pressure_saturation_slope_calculator::calc_from_avg_air_temperature()  const
{ // slope in kPa/C ; airtemp in degrees celcius }
   // RLN check with Claudio: I don't know if we will want to consider over ice here, we originally only had OVER_WATER_ONLY!!!! 040114_
   float64 air_temp_avg = air_temperature_avg.Celcius();
   float64 svp = Physical::calc_saturation_kPa(air_temp_avg,air_temp_avg,OVER_WATER_ONLY); //150303 040114
   float64 num = svp * 4098.0;
   float64 denum = air_temp_avg + 237.3;   // WARNING I think this needs to be  avg_air_temp + kelvin - b  from saturation_vapor_pressure
   float64 sqr_denum = CORN_sqr(denum);
   float64 ssvp = num/sqr_denum;
   return ssvp;
}
//______________________________________________________________________________
const CORN::Quality &Vapor_pressure_saturation_slope_calculator::update() rectification_
{
   CORN::Quality_clad VPSS_quality(quality_calculated_from(air_temperature_avg.get_quality_code()));
   float64 VPSS = calc_from_avg_air_temperature();
   update_kPa_per_C(VPSS,VPSS_quality);
   return get_quality();
}
//______________________________________________________________________________
