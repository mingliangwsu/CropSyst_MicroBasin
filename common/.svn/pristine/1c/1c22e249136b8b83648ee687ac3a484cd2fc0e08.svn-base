#ifndef snowH
#define snowH
//140118 #include "corn/std/std_fstream.h"
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#ifndef skyH
#  include "common/weather/sky.h"
#endif
#ifndef weather_typesH
#  include "common/weather/weather_types.h"
#endif
class Weather_base;
class Weather_with_solar_rad_estimation;

//150125 (Time step could actually be a member

//______________________________________________________________________________
class Snow_pack_base
{
   friend class Weather_base; // temporary until we implement snow in database
   friend class Weather_with_solar_rad_estimation;
protected:
   float64  liquid_water_m;   // In the simple model this will always be 0      //1999-01-11
   float64  ice_water_m;                                                        //1999-01-11
   // This the depth of water in the form of snow.
   // This is not the depth of the snow, but the depth of water.
   bool     new_snow_this_time_step;                                             //2000-03-15
   bool     observed_snow_pack_thickness_today;                                  //1999-02-04
   float64  observed_snow_pack_thickness;                                        //1999-02-04
   float64 snow_pack_thickness_m;                                                //141205 // was local
   float64  snow_melted_today; // m                                              //1998-10-19
protected: // sun and sky object
   Weather_base &weather;
public:
   Snow_pack_base(Weather_base &i_weather);
   virtual ~Snow_pack_base();                                                    //130515
   virtual float64 precipitate();
   // This function takes the daily recorded preciptation in equilvalent water depth
   // and either adds the value to the snow pack and returns 0 liquid water precipitation
   // or melts the snow pack (if any) and returns the precipitation + snow melt.
protected:
   virtual float64 get_rain_to_snow_temperature();
   inline virtual bool convert_rain_to_snow(float64 air_temperature) { return air_temperature  < get_rain_to_snow_temperature();}
   float64 snow_fall(float64 precip);
      ///< \return precipitation that was taken as snow.
   virtual float64 snow_melt
      (float64 average_air_temperature
      , float64 rain
      , Seconds timestep = Seconds_per_day) = 0;                                 //150125
 public:
   bool update();                                                                //140215
      // probably should return quality
   virtual float64 &get_snow_pack_thickness();                                   //141205_991004
   inline virtual float64 get_snow_melted()                                const { return snow_melted_today; }
   inline virtual float64 get_curr_snow_water_equivelent_depth()           const { return liquid_water_m + ice_water_m; }
   inline bool snowed()                                                    const { return new_snow_this_time_step;}  //2000-03-15
};
//______________________________________________________________________________
class Snow_pack_temperature_based                                                //2001-10-19
: public Snow_pack_base
{public:
   Snow_pack_temperature_based
      (Weather_base &_weather)
      : Snow_pack_base(_weather)
      {}
   virtual float64 snow_melt(float64 average_air_temperature, float64 rain      , Seconds timestep = Seconds_per_day); //150125
      ///< \return snow melted plus any rain
};
//______________________________________________________________________________
// This method can only be used if longitude is not 0
class Snow_pack_energy_based // was Snow_pack_Erin_Brooks
: public Snow_pack_base
{private: // soil parameters
   float64  reference_elevation;  // m this is the elevation of the weather station
   float64  site_elevation;       // m this is the actual elevation of the site
   float64  site_aspect_deg;     // I believe this is degrees from north   float64  soil_slope_percent;
   float64  soil_slope_percent;
private:
   bool     forest_vegetation;
private:  // Values to be remembered for next day.
   float64 snow_temperature_last_timestep_C;
public:
   inline Snow_pack_energy_based
      (Weather_base &_weather
      ,float64       _soil_slope_percent
      ,float64       _site_aspect_deg
      ,bool          _forest_vegetation)
      : Snow_pack_base      (_weather)
      , reference_elevation (0)
      , site_elevation      (0)
      , site_aspect_deg     (_site_aspect_deg)
      , soil_slope_percent  (_soil_slope_percent)
      , forest_vegetation   (_forest_vegetation)
      , snow_temperature_last_timestep_C(0)
      {}
private:
   inline virtual float64 get_rain_to_snow_temperature() { return 1.0; }
   float64 adjust_temperature_by_elevation
      (float64 temperature
      ,float64 target_elevation_meter);                                          //140723
   virtual float64 snow_melt(float64 average_air_temperature,float64 rain      , Seconds timestep = Seconds_per_day); //150125
   float64 enhanced_snow_melt // This should work for any time step
      (float64 precipitation_m       // Currently if we are melting
      ,float64 air_temperature       // then all it is warm enough for
      ,float64 solar_radiation_MJ_m2 // all precipitation to go to rain
      ,float64 dew_point_temperature
      ,float64 wind_roughness_ts
      ,float64 sun_elevation_angle_rad
      ,float64 albedo
      ,CORN::Seconds time_step);
   inline void set_soil_slope_percent(float64 new_soil_slope_percent)
                  { soil_slope_percent = new_soil_slope_percent;}
      // This is only used by CropSyst V3 because of the old sequence of soil allocation and loading
      //2005-07-18
};
//______________________________________________________________________________
#endif
// snow.h

