#include "geodesy/geometry/terrestrial_geometry.h"
#include <math.h>
//______________________________________________________________________________
float64 Terrestrial_geometry::distance_between_km
(const Geocoordinate &point_a
,const Geocoordinate &point_b)                                             const
{
   // This uses the Haversine format, which is well conditioned for numerical computation even at small dinstance.
   // Ref: R. W. Sinnott  Sky and Telescope, 1984
   // The half-versed-sine is (1- cos(theta))/2  or  sin^2(theta/2)
   //(This is not using the law of cosines)

   // Note this equation does not take into account the
   // fact that the Earth is an oblate spheroid, not a perfect sphere.
   // I believe the error is at maximum 1 meter in 1 kilometer.
   // This error should not be significant for short distances
   // and when not crossing the equator.

/*original code in JavaScript
   http://www.movable-type.co.uk/scripts/LatLong.html
*/
   float64 point_a_latitude_rad = point_a.get_latitude_radians();
   float64 point_b_latitude_rad = point_b.get_latitude_radians();
   float64 dLat  = point_b_latitude_rad  - point_a_latitude_rad;
   float64 dLong = point_b.get_longitude_radians() - point_a.get_longitude_radians();
   float64 a = sin(dLat/2.0) * sin(dLat/2.0) +
          cos(point_a_latitude_rad) * cos(point_b_latitude_rad) * sin(dLong/2) * sin(dLong/2);
   float64 c = 2 * atan2(sqrt(a), sqrt(1-a));
   float64 d = EARTH_MEAN_RADIUS_km * c;
   return d;
}
//______________________________________________________________________________

// http://stackoverflow.com/questions/7477003/calculating-new-longtitude-latitude-from-old-n-meters


bool Terrestrial_geometry::latitude_delta_km (float32 delta_km,modifiable_ Geocoordinate &point)
{
   /* The number of kilometers per degree of latitude is approximately the same at all locations,
      (2*pi/360) * r_earth = 111 km / degree
   */

   float32 new_latitude  = point.get_latitude_dec_deg()  + (delta_km / EARTH_MEAN_RADIUS_km) * (180.0 / M_PI);
   point.set_latitude_dec_deg_f32(new_latitude);
   return true;
}
//______________________________________________________________________________


bool Terrestrial_geometry::longitude_delta_km(float32 delta_km,modifiable_ Geocoordinate &point)
{
   /*
 The number of kilometers per degree of longitude is approximately

(2*pi/360) * r_earth * cos(theta)
where theta is the latitude in degrees and r_earth is approximately 6378 km.
   */

   float32 new_longitude = point.get_longitude_dec_deg()
      + (delta_km / EARTH_MEAN_RADIUS_km) * (180.0 / M_PI)
      / cos(point.get_latitude_dec_deg() * M_PI/180.0);
   point.set_longitude_dec_deg_f32(new_longitude);
   return true;
}
//______________________________________________________________________________







