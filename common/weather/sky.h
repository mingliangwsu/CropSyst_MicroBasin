#ifndef skyH
#define skyH

#ifndef sunH
#include "common/weather/sun.h"
#endif

#ifndef irradiance_extraterrestrialH
#include "common/solar/irradiance_extraterrestrial.h"
#endif
#ifndef qualityHPP
#include "corn/quality.hpp"
#endif
#include "corn/const.h"
//_forward_declarations_________________________________________________________
class Soil_temperature_profile_hourly;
class Solar_radiation;
class Air_temperature_average;
class Precipitation;
//______________________________________________________________________________
class Sky
{  // ET solar rad should be a member
 protected:
   const CS::Solar_irradiance_extraterrestrial &ET_solar_irradiance_new;   //150626
   const Solar_radiation         &solar_radiation;                               //151023
   const Air_temperature_average &air_temperature_avg;                           //151023
   const Precipitation           &precipitation;                                 //151023
 private:
   contribute_ float64 albedo_last_time_step;                                    //000315
   float64 albedo;               // 0-1
   float64 cloud_emissivity;     // 0-1 ????
 protected:  friend class Soil_temperature_profile_hourly; // temporary
 public:
   float64 curr_cloud_cover_fraction;                                            //991022
   mutable CORN::Quality_clad  cloud_cover_quality;
 protected:
   float64 calc_clear_sky_emissivity(float64 avg_air_temperature)          const;//041025_131104
   float64 calc_clear_sky_emissivity_2(float64 avg_air_temperature_kelvin,float64 vapor_pressure) const; //041025_131104
   float64 calc_cloud_emissivity
      (float64 avg_air_temperature
      ,float64 cloud_fract
      ,float64 clear_sky_emissivity = 0.0 // If 0.0, then this will be calculated based on air temperature
      ) const; // This works for any time step
public:
   float64 calc_cloud_cover_fraction                                             //000308
      (float64 pot_solar_rad     // any solar rad units I.e. MJ/m2
      ,float64 solar_rad         // any solar rad units I.e. MJ/m2
      ,float64 min_atmospheric_transmission_coef = 0.4)                    const;//070213_131104
public: // Solar radiation equations
   float64  calc_albedo
      (bool       any_new_snow
      ,Seconds    for_time_step)                                           const;//131104
   float64 calc_shortwave_net_radiation
      (float64    albedo      // Need to pass albedo because ET uses different value than snow
      ,float64    sol_rad    // Need to pass sol rad because ET uses different value than snow
      ) const;
      // This will work for any units of solar radiation (I.e. KJ/m2)
public:
   Sky
      (const CS::Solar_irradiance_extraterrestrial &ET_solar_irradiance_new      //150626
      ,const Air_temperature_average   &air_temperature_avg                      //151023
      ,const Solar_radiation           &solar_radiation                          //151023
      ,const Precipitation             &precipitation                            //151023
      );                                                                         //150125
   virtual bool update_clouds();
   virtual void invalidate(bool absolutely)                       modification_; //091216
   inline float64 get_albedo()                                             const { return albedo; }
   inline float64 get_cloud_emissivity()                                   const { return cloud_emissivity; }
   inline virtual float64 get_cloud_cover_fraction()                       const { return curr_cloud_cover_fraction; } //991022
   inline virtual const CORN::Quality  &get_cloud_cover_quality()          const { return cloud_cover_quality; } //991012
};
//_____________________________________________________________________________

#endif

