#include <math.h>
#include "common/weather/day/sun_days.h"
#include "common/weather/hour/sun_hours.h"
#include "corn/measure/measures.h"
#include "corn/math/moremath.h"
#include "corn/math/compare.hpp"
//______________________________________________________________________________
Sun_hours::Sun_hours
(const Sun_days &sun_days_
,float64         latitude_deg)
: sun_days(sun_days_)
{
/*
debug_sun_hours
<< "doy" << '\t'
<< "hour" << '\t'
<< "noon" << '\t'
<< "declination_radians"  << '\t'
<< "solar_zenith_angle" << '\t'
<< "solar_azimuth_angle" << '\t'
<< "latitude_radians" << '\t'
<< "cos_solar_zenith" << '\t'
<< "sin_solar_zenith" << '\t'
<< '\n';
*/
   for (CORN::DOY doy = 1; doy <= 366 ; doy++)
   {  for (CORN::Hour hour = 0; hour < 24; hour++)
      {
         // I think the VB code hour offset is wrong.
/*
if (doy == 105)
solar_zenith_angle_rad[0][0] = 0;
*/

// RLN: I think this could be generalized for any timestep by adusting the 0.2618 coef accordingly.

         //_____________________________________________________________________
         // Begin This differs from Visual Basic version
         // this calc of solar zenith angle could be moved to Sun_hour.
         float64 latitude_rad = deg_to_rad(latitude_deg);
         float64 hour_1 = hour+1; // Claudio's VB code uses hours 1 to 24 my ours are 0-23
         float64 cosine_solar_zenith_angle
          = sin(latitude_rad) * sun_days.get_sine_solar_declination(doy)
          + cos(latitude_rad) * cos(sun_days.get_solar_declination_rad(doy))
            * cos(0.2618 * (hour_1 - 12));
         // Warning: 0.2618 * (hour_1 - 12) I don't know if this is radians or degrees
         // Also in the CropSyst VB code this is  0.2618 * hour_1  !!!!
         float64 solar_zenith_angle_rad_doy_hour =  acos(cosine_solar_zenith_angle);
         //_____________________________________________________________________
         solar_zenith_angle_rad_doy_hour = calc_solar_zenith_angle
            (doy,hour,latitude_rad);
         solar_zenith_angle_rad[doy][hour] = solar_zenith_angle_rad_doy_hour;
         // dependency: solar_zenith_angle_rad must be calculated before solar_azimuth_angle_radians
         solar_azimuth_angle_radians[doy][hour]=calc_solar_azimuth_angle_radians
            (doy,hour,latitude_rad,solar_zenith_angle_rad_doy_hour);
      }
   }
}
//______________________________________________________________________________
float64 Sun_hours::get_cosine_solar_zenith_angle(CORN::DOY doy, CORN::Hour hour) const
{  float64 cos_solar_zenith_angle = cos(solar_zenith_angle_rad[doy][hour]);
   return  cos_solar_zenith_angle;
}
//______________________________________________________________________________
// This was introduced and used by Orchard_interception_Oyarzun_Stockle
float64 Sun_hours::calc_solar_zenith_angle(CORN::DOY doy, CORN::Hour hour,float64 latitude_radians) const
{  // this calc of solar zenith angle could be moved to Sun_hour.
   CORN::Hour hour_1 = hour+1; //The original V.B. code indexs hour from 1 not 0
   float64 declination_radians_daily = sun_days.get_solar_declination_rad(doy);
   float64 t0 = sun_days.get_solar_noon(doy);
   // Estimate auxiliary trigonom. functions for calculation purposes
   float64 cosz = sin(latitude_radians) * sin(declination_radians_daily) + cos(latitude_radians)
        * cos(declination_radians_daily) * cos(0.2618 * (hour_1 - t0));
   float64 sinz = sqrt(1.0 - cosz * cosz);
   float64 solar_zenith_angle = M_PI_2 - atan(cosz / sinz);
   if (cosz < 0) solar_zenith_angle = M_PI_2;
   return solar_zenith_angle;
}
//_2007-11-17___________________________________________________________________
// This was introduced and used by Orchard_interception_Oyarzun_Stockle
float64 Sun_hours::calc_solar_azimuth_angle_radians
(CORN::DOY doy
,CORN::Hour hour            // Note that this is 0 based hour
,float64  latitude_radians
,float64  solar_zenith_angle_radians_hourly_param)                         const
{  // This function calculates the solar azimuth for a given day
   // and hour, with respect to due south
   CORN::Hour hour_1 = hour+1; // The original V.B. code offsets hour from 1 not 0 //071117
// this calc of solar azimuth angle could be moved to Sun_hour.

   // The following adjuncts should have already been calculated:
   //    doy
   //    hour
   //    latitude_radians
   //    longitude_radians
   //    standard_meridian_radians
   //    declination_radians_daily
   float64 noon = 12; // 071119 Using solar noon causes a discontinuity in
   //071119 = sun_days.get_solar_noon(doy) ; // noon is 24 hour time
   float64 declination_radians_daily = sun_days.get_solar_declination_rad(doy);
   float64 cosAz
      = (solar_zenith_angle_radians_hourly_param <  M_PI_2 )         /* RLN PI/2 was 1.57079637050628*/
      ? -(sin(declination_radians_daily) - cos(solar_zenith_angle_radians_hourly_param) * sin(latitude_radians)) / ((cos(latitude_radians) * sin(solar_zenith_angle_radians_hourly_param)))
      : 0.0;
   cosAz = (hour_1 <= noon) ? cosAz : -cosAz;
   if (fabs(cosAz) > 1.0) cosAz = 0.9999;
   float64 sinAz = sqrt((1.0 - cosAz * cosAz));
   if (CORN::is_approximately<float64>(sinAz,0.0,0.00001)) sinAz = 0.000001;
   float64 solar_azimuth_angle_rad = 0;
      if (hour_1 < noon)
         solar_azimuth_angle_rad =  (CORN_pi/2.0 - atan(cosAz / sinAz));
      else
       solar_azimuth_angle_rad =  ((3.0 / 2.0) * CORN_pi - atan(cosAz / sinAz));
/*
debug_sun_hours
<< (int)doy << '\t'
<< (int)hour << '\t'
<< noon << '\t'
<< declination_radians_daily << '\t'
<< solar_zenith_angle_radians_hourly_param << '\t'
<< solar_azimuth_angle_rad << '\t'
<< latitude_radians << '\t'
<< cosAz << '\t'
<< sinAz << '\t'
<< '\n';
*/
   return solar_azimuth_angle_rad;
}
//______________________________________________________________________________

