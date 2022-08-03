
#include "common/solar/irradiance_extraterrestrial.h"
#include "common/weather/hour/solar_irrad_hour.h"
#include "common/weather/parameter/WP_solar_radiation.h"
#include <math.h>
#include "corn/math/moremath.h"
#include "corn/math/compare.h"
#include "corn/chronometry/time_types.hpp"
//______________________________________________________________________________
Solar_irradiance_hour::Solar_irradiance_hour
(const Solar_radiation &_solar_irradiance_daily                                  //140715
,const CS::Solar_irradiance_extraterrestrial_hourly &_extraterrestrial_solar_irradiance)
: solar_irradiance_daily(_solar_irradiance_daily)                                //140715
, extraterrestrial_solar_irradiance(_extraterrestrial_solar_irradiance)          //150627
{  for (int h = 0; h < 24; h++)
   {  diffuse_solar_irradiance[h] = 0;
      direct_solar_irradiance[h] = 0;
      solar_irradiance[h] = 0;
   }
}
//______________________________________________________________________________
bool Solar_irradiance_hour::update()
{  // move the following to act_solar_rad
   if (!solar_irradiance_daily.is_valid()) return false;                         //140715
   float64 act_solar_irradiance_daily  = solar_irradiance_daily.get_MJ_m2();     //140715
   float64 ET_irradiance_daily         =
      extraterrestrial_solar_irradiance.get_MJ_per_m2_day();                     //150627
   float64 fraction_diffuse_irradiance = 1.0 - exp(1.0 - 0.96 / (std::min<float64>(0.8, act_solar_irradiance_daily / ET_irradiance_daily)));
   for (CORN::Hour hour= 0; hour < 24; hour++)
   {
      solar_irradiance        [hour] = act_solar_irradiance_daily *
         extraterrestrial_solar_irradiance.get_insolation_fraction_today(hour);  //150627
      diffuse_solar_irradiance[hour] = solar_irradiance[hour] * fraction_diffuse_irradiance;
      direct_solar_irradiance [hour] = solar_irradiance[hour] - diffuse_solar_irradiance[hour];
   }
   return true;                                                                  //140715
}
//______________________________________________________________________________

