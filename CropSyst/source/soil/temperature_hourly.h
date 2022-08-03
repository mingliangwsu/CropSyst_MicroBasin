#ifndef temperature_hourlyH
#define temperature_hourlyH

#ifdef DEBUG_DUMP
#include "corn/std/std_iostream.h"
#endif

#include "corn/chronometry/date_I.h"
//170524 #include "corn/chronometry/date_types.hpp"
#include "common/soil/layering.h"
#include "soil/temperature_hourly_interface.h"
#include "common/weather/weather_types.h"

class Soil_interface;
class Soil_layers_interface;
class Soil_temperature_profile;
class Solar_radiation;                                                           //151022
namespace CS
{
   class Solar_irradiance_extraterrestrial;                                      //151022
   class Land_unit_meteorological;                                               //151022
};
//______________________________________________________________________________
class Soil_temperature_profile_hourly
: public implements_ Soil_temperature_profile_hourly_interface                   //060216
{  // This class is normalized meters, kilogram, hour
 private:
   float64                 temperature[24][MAX_soil_layers_alloc];     // index 0 is midnight to 1:00
   float64                 avg_temperature[MAX_soil_layers_alloc]; // Average daily value
   soil_layer_array64     (node_depth);                                          //060229
   const Soil_interface          &soil;                                          //150424
   const Soil_layers_interface   &soil_layers;
   const CS::Land_unit_meteorological &meteorological;                           //151022
   const CS::Solar_irradiance_extraterrestrial  &ET_solar_irradiance;
   const Solar_radiation                        &solar_radiation;                //151022
   const CORN::Date_const                       &today;                          //140724
   mutable bool has_snow_cover;                                                  //160721
 private: // from scenario parameters
   const CS::Annual_temperature  &annual_temperature;                            //140524
 public:
   Soil_temperature_profile_hourly
      (const Soil_interface                               &soil
      ,const CS::Land_unit_meteorological                 &meteorological        //151022
      ,const CS::Solar_irradiance_extraterrestrial        &ET_solar_irradiance   //151022
      ,const CS::Annual_temperature                       &annual_temperature    //150424
      ,const CORN::Date_const                             &today);
   void update(float64 crop_leaf_area_index,float64 stubble_area_index,float64 residue_area_index);
#ifdef DEBUG_DUMP
   void dump_temporary(ostream &strm,Soil_temperature_profile &soil_temp_profile);//041110
#endif
   virtual bool initialize();                                                    //150422RLN
   bool initialize_nodes();                                                      //060229
   // Call incase the soil horizons change (I.e. erosion)
 public: // accessors
   inline virtual float64 get_avg_temperature(nat8 layer)                  const //041111
      { return avg_temperature[layer]; }
   inline virtual float64 get_temperature(CORN::Hour hour, nat8 layer)     const //060216
      { return temperature[hour][layer];}
   inline virtual bool know_has_snow_cover(bool has_snow_)            cognition_ //160721
      { return has_snow_cover = has_snow_; }
 protected:
   float64 calc_heat_conductivity
      (float64 bulk_density_g_cm3
      ,float64 volumetric_WC
      ,float64 fraction_clay) const;
   float64 estimate_soil_temperature
      (float64 node_depth
      ,CORN::DOY     doy) const;
   float64 calc_solar_irradiance_interception_fract                              // was FractionSunlitShadedRadiationInterception
      (float64 X
      // for crop canopy      use 0.5
      // for standing stubble use 0.0
      // for surface residue  use 10.0
      ,float64 area_index                 // (I.e. LAI)
      ,float64 absorbtivity               // 0-1
      // for crops use 0.5 which indicates photosynthetic and near infrared portion  of the spectrum (geometic mean)
      // for residue use 0.4
      ,float64 solar_zenith_angle_rad     // radians
      ,float64 solar_direct_irradiance
      ,float64 solar_diffuse_irradiance);
      // Irradiance can by any units of irradiance (I.e J/m2/sec or MJ/m2/day)
   float64 calc_direct_extinction_coef  // direct beam
      (float64 X
      ,float64 solar_zenith_angle_rad
      ,float64 absorptivity) const;
   float64 calc_diffuse_extinction_coef
      (float64 X
      ,float64 area_index // I.e. LAI
      ,float64 absorptivity) const;
};
//_2004-10-25___________________________________________________________________
#endif

