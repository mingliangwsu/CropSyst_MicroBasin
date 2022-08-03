#ifndef snow_packH
#define snow_packH
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#ifndef skyH
#  include "common/weather/sky.h"
#endif
#ifndef sunH
#  include "common/weather/sun.h"
#endif
#ifndef weather_typesH
#  include "common/weather/weather_types.h"
#endif
#include "weather/parameter/WP_precipitation.h"
#include "weather/parameter/WP_air_temperature.h"
#include "weather/parameter/WP_dew_point_temperature.h"
#include "weather/parameter/WP_solar_radiation.h"
#include "common/biometeorology/aerodynamics.h"

class Weather_base;
class Weather_with_solar_rad_estimation;
//______________________________________________________________________________
interface_ Snow_pack
{
   inline virtual ~Snow_pack() {}
   virtual const CORN::Quality &update()                          rectification_=0;
   virtual float64 ref_snow_pack_thickness()                               const=0;
   virtual float64 get_water_equivelent_depth()                            const=0;
   virtual float64 get_melted()                                            const=0;
   virtual inline bool snowed()                                            const=0;
   inline virtual bool is_melted_completely()                       affirmation_=0;
   virtual float64 get_liquid_water_m()                                    const=0;//160725
   virtual float64 get_ice_water_m()                                       const=0;//160725
};
//_2014-12-05__________________________________________________________________/
class Snow_pack_common
: public implements_ Snow_pack
{
 protected:
   modifiable_ Precipitation     &liberated_water;
   const Precipitation           &precipitation;
   const Air_temperature_average &air_temperature_avg;
 protected:
   contribute_ float64  liquid_water_m;   // In the simple model this will always be 0      //1999-01-11
   contribute_ float64  ice_water_m;                                                        //1999-01-11
   // This the depth of water in the form of snow.
   // This is not the depth of the snow, but the depth of water.
   contribute_ bool     new_snow_this_time_step;                                             //2000-03-15
   contribute_ float64  snow_pack_thickness_m;                                               //141205
   contribute_ float64  snow_melted_today; // m                                              //1998-10-19
public:
   Snow_pack_common
      (modifiable_ Precipitation     &liberated_water
      ,const Precipitation           &precipitation
      ,const Air_temperature_average &air_temperature_avg
      );
   virtual const CORN::Quality &update()                          rectification_;//141205
protected:
   virtual float64 get_rain_to_snow_temperature()                          const;
   inline virtual bool should_convert_rain_to_snow()                affirmation_
      { return air_temperature_avg.Celcius()  < get_rain_to_snow_temperature();}
   float64 snow_fall(float64 recip)                                contribution_;
      ///< \return precipitation that was taken as snow.
   virtual float64 snow_melt(float64 actual_rain_m)                        const = 0;
   float64 update_snow_pack_thickness()                           rectification_;//141205
 public:
   inline virtual float64 ref_snow_pack_thickness()                        const { return snow_pack_thickness_m; }
   inline virtual float64 get_melted()                                     const { return snow_melted_today; }
   inline virtual float64 get_water_equivelent_depth()                     const { return liquid_water_m + ice_water_m; } //151022
   inline virtual bool snowed()                                            const { return new_snow_this_time_step;}  //2000-03-15
   inline virtual bool is_melted_completely()                       affirmation_;//160117
   virtual float64 get_liquid_water_m()                                    const { return liquid_water_m; }//160725
   virtual float64 get_ice_water_m()                                       const { return ice_water_m;    }//160725
};
//_____________________________________________________class:Snow_pack_common__/
class Snow_pack_temperature_based                                                //2001-10-19
: public extends_ Snow_pack_common
{public:
   Snow_pack_temperature_based
      (modifiable_ Precipitation     &liberated_water
      ,const Precipitation           &precipitation
      ,const Air_temperature_average &air_temperature_avg
      );

   virtual float64 snow_melt(float64 actual_rain_m)                        const;
      ///< \return snow melted plus any rain
};
//__________________________________________class:Snow_pack_temperature_based__/
// This method can only be used if longitude is not 0
class Snow_pack_energy_based // was Snow_pack_Erin_Brooks
: public extends_ Snow_pack_common
{private: // soil parameters
   const Dew_point_temperature_average &dew_point_temperature_avg;               //141205
   const Solar_radiation               &solar_radiation;                         //141205
   const Sky &sky;                                                               //141205
   const Sun &sun;                                                               //141205
   const Aerodynamics                  &aerodynamics;                            //141205
   CORN::Seconds time_step;                                                      //141205
   float64  site_aspect_deg;     // I believe this is degrees from north   float64  soil_slope_percent;
   float64  soil_slope_percent;
   bool     forest_vegetation;
 private:
 private:  // Values to be remembered for next day.
   contribute_ float64 snow_temperature_last_timestep_C;
public:
   Snow_pack_energy_based
      (
      modifiable_ Precipitation     &liberated_water
      ,const Precipitation           &precipitation
      ,const Air_temperature_average &air_temperature_avg
      ,const Dew_point_temperature_average &dew_point_temperature_avg
      ,const Solar_radiation         &solar_radiation
      ,const Sky                     &sky                                                            //141205
      ,const Sun                     &sun
      ,const Aerodynamics            &aerodynamics
      ,CORN::Seconds                  time_step
      ,float64       _soil_slope_percent  = 0
      ,float64       _site_aspect_deg     = 180
      ,bool          _forest_vegetation   = false
      );
private:
   inline virtual float64 get_rain_to_snow_temperature()                   const { return 1.0; }
   float64 adjust_temperature_by_elevation
      (float64 temperature
      ,float64 target_elevation_meter);                                          //140723
   virtual float64 snow_melt(float64 actual_rain_m)                        const;
   float64 enhanced_snow_melt // This should work for any time step
      (float64 actual_rain_m) const;
      // Currently if we are melting
   inline void set_soil_slope_percent(float64 new_soil_slope_percent)
                  { soil_slope_percent = new_soil_slope_percent;}
      // This is only used by CropSyst V3 because of the old sequence of soil allocation and loading
      //2005-07-18
};
//_______________________________________________class:Snow_pack_energy_based__/
#endif
// snow.h

