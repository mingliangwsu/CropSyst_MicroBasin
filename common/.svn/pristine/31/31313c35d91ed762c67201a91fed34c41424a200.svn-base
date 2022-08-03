#ifndef sun_daysH
#define sun_daysH
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "corn/chronometry/date_types.hpp"
//_____________________________________________________________________________
class Sun_days
{
   // These values are the same every year, we calculate them one time
 private: // These arrays are 1 based indexed (value at index 0 is unused)
   float64 sine_solar_declination[367];
   float64 solar_declination_rad [367];
   float64 earth_sun_distance_adj[367]; // RLN: Claudio says this may be a unitless adjustment
   float64 solar_noon            [367]; // This appears to be in hours           //071116
 public: // constructors
   Sun_days(float64 longitude_radians,float64 standard_meridian_radians);
 public: // accessors
   inline float64  get_sine_solar_declination(CORN::DOY doy) const { return sine_solar_declination [doy]; }
   inline float64  get_solar_declination_rad (CORN::DOY doy) const { return solar_declination_rad  [doy]; }
   inline float64  get_earth_sun_distance_adj(CORN::DOY doy) const { return earth_sun_distance_adj [doy]; }
   inline float64  get_solar_noon            (CORN::DOY doy) const { return solar_noon             [doy]; }  //071116
 private: // calculations
   float64 calc_solar_noon
      ( CORN::DOY doy
      , float64 longitude_radians
      , float64 standard_meridian_radians );
};
//_____________________________________________________________________________
#endif

