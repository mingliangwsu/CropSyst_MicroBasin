#ifndef sun_hoursH
#define sun_hoursH
#include "corn/chronometry/date_types.hpp"
#include "corn/chronometry/time_types.hpp"
class Sun_days;  // forward declaration
//______________________________________________________________________________
class Sun_hours
{private:
   const Sun_days &sun_days;
 public:
   // These values are the same every year so calculate one time and provide accessors
   // day index is 1 based hour index is 0 based
   float64 solar_zenith_angle_rad[367][24];
      // may want to store these also as cosines
      // used by: hourly soil temperature, Orchard_interception_Oyarzun_Stockle
   float64 solar_azimuth_angle_radians[367][24];
      // less than 0 is south with west positive                                 //071116
      // used by: Orchard_interception_Oyarzun_Stockle
 public:
   Sun_hours
      (const Sun_days &sun_days
      ,float64         latitude_deg);
   inline float64 get_solar_zenith_angle_rad
      (CORN::DOY doy, CORN::Hour hour)                                     const
      { return solar_zenith_angle_rad[doy][hour]; }
   float64 get_cosine_solar_zenith_angle
      (CORN::DOY doy, CORN::Hour hour)                                     const;
   inline float64 get_solar_azimuth_angle_radians
      (CORN::DOY doy, CORN::Hour hour)                                     const
      { return solar_azimuth_angle_radians[doy][hour]; }
 private:
   float64 calc_solar_azimuth_angle_radians
      (CORN::DOY  doy
      ,CORN::Hour hour
      ,float64    latitude_radians
      ,float64    solar_zenith_angle_radians_hourly_param)                 const;
   float64 calc_solar_zenith_angle
      (CORN::DOY doy, CORN::Hour hour,float64 latitude_radians)            const;//071116
};
//______________________________________________________________________________
#endif

