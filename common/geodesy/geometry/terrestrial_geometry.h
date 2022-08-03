#ifndef terrestrial_geometryH
#define terrestrial_geometryH
//______________________________________________________________________________
#ifndef geolocationH
#  include "geodesy/geolocation.h"
#endif
#define EARTH_MEAN_RADIUS_km  6371.0
// Another source says: 6378 km.
//______________________________________________________________________________
class Terrestrial_geometry
{
public:
   float64 distance_between_km
      (const Geocoordinate &point_a
      ,const Geocoordinate &point_b)                                      const;
   inline float64 distance_between_m
      (const Geocoordinate &point_a
      ,const Geocoordinate &point_b)                                      const
      { return km_to_m(distance_between_km(point_a,point_b)); }
   bool latitude_delta_km (float32 km,modifiable_ Geocoordinate &point);
   bool longitude_delta_km(float32 km,modifiable_ Geocoordinate &point);
   inline bool latitude_delta_m (float32 m,modifiable_ Geocoordinate &point)
      { return latitude_delta_km(m_to_km(m),point); }
   bool longitude_delta_m(float32 m,modifiable_ Geocoordinate &point)
      { return longitude_delta_km(m_to_km(m),point); }
};
//______________________________________________________________________________
#endif

