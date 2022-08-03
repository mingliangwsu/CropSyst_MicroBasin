#include "common/weather/day/sun_days.h"
#include <math.h>
#include "corn/math/moremath.h"
//______________________________________________________________________________
Sun_days::Sun_days(float64 longitude_radians,float64 standard_meridian_radians)
{  for (CORN::DOY doy = 1; doy <= 366; doy++)
   {  sine_solar_declination[doy]
         = 0.39785 * sin(4.869 + 0.0172*doy + 0.03345*sin(6.224 + 0.0172*doy));
      solar_declination_rad[doy] = asin(sine_solar_declination[doy]);
      earth_sun_distance_adj[doy] = 1.0 + 0.0334 * cos(0.01721 * doy - 0.0552);
      solar_noon[doy]
         = calc_solar_noon(doy,longitude_radians,standard_meridian_radians);
   }
}
//______________________________________________________________________________
float64 Sun_days::calc_solar_noon
( CORN::DOY doy
, float64 longitude_radians
, float64 standard_meridian_radians )
{  // This function calculates the actual time of solar noon
   float64 f = (279.575 + 0.9856 * doy) * CORN_pi / 180.0;
   float64 ET = (-104.7 * sin(f) + 596.2 * sin(2.0 * f) + 4.3 * sin(3.0 * f)
        - 12.7 * sin(4.0 * f) - 429.3 * cos(f) - 2.0
        * cos(2.0 * f) + 19.3 * cos(3.0 * f)) / 3600.0;
   float64 longitude_correction   // radians or unitless?
      = ((standard_meridian_radians - longitude_radians) / 15.0);
   // longitude correction, +1/15 hour for each degree you are EAST of the
   // Standard Meridian, and -1/15 hour for each degree WEST of the Std. Mer.
   // (Campbell and Norman, 1997)
   float64 solar_noon_doy = 12.0 - longitude_correction - ET;
   return solar_noon_doy;   // This appears to be standard 24 hour time.
}
//______________________________________________________________________________

