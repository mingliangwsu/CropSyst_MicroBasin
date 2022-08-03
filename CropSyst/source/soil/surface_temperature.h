#ifndef surface_temperatureH
#define surface_temperatureH

// This class is not currently in CropSyst used but it may be useful
// in the future.  These methods used to be in Soil_temperature_profile

#include "corn/primitive.h"
//______________________________________________________________________________
class Soil_surface_temperature
{public:
   float64 max_surface_temp     // rename to calc_maximum
      ( float64 moisture_component   //Moisture component of temperature
      , float64 radiation_component
      , float64 cover_component
      , float64 a
      , float64 max_temp);
   float64 min_surface_temp     // rename to calc_minimum
      ( float64 f
      , float64 cover
      , float64 g
      , float64 min_temp);
   float64 mean_surface_temp    // rename to calc_mean
      ( float64 max_surface_temp
      , float64 h
      , float64 min_surface_temp
      , float64 i);
   float64 actual_surface_temp // rename to calc_actual
      (float64 max_temp, float64 min_temp
      ,float64 solar_radiation_MJ_m2,float64 snow_depth_m
      ,float64 leaf_area_index
      ,float64 residue_mass
      ,bool    winter_time);
#ifdef CHECK_USED
// I think these were at one time used to compute reference ET.
// I am not sure what happened to the implementation code
   float64 moisture_component(float64 x , float64 z);
   float64 radiation_component(float64 d , float64 e,float64 solar_radiation_MJ_m2);
   float64 cover_component(float64 b, float64 cover, float64 c);
#endif
};
//_1998-06-01___________________________________________________________________

#endif
