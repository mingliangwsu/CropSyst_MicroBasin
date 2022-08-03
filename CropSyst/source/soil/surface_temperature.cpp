#ifdef USE_PCH
#  include "simulation/CropSyst_sim_pch.h"
#else
#  include <math.h>
#  include "soil/surface_temperature.h"
#endif
#include "corn/measure/measures.h"
//______________________________________________________________________________
float64 Soil_surface_temperature
:: mean_surface_temp
( float64 max_surface_temp
, float64 h
, float64 min_surface_temp
, float64 i)
{  return max_surface_temp * h + min_surface_temp * i;
}
//_1998-06-01___________________________________________________________________
float64 Soil_surface_temperature
::actual_surface_temp
(float64 max_temp
,float64 min_temp
,float64 solar_radiation_MJ_m2  // unused
,float64 snow_depth_m
,float64 leaf_area_index
,float64 residue_mass
,bool    winter_time)                                                           //980921
{  float64 residue_mass_kg_ha = (residue_mass / 0.0001);  // convert per m2 to per ha
   float64 max_surface_temp_residue = max_temp + (0.7654921 * max_temp) * exp(-0.0002534 *  residue_mass_kg_ha);
   float64 min_surface_temp_residue = min_temp +  0.0001704 *residue_mass_kg_ha + 1.0380467; //990611P
   float64 mean_surface_temp_residue = mean_surface_temp
     (max_surface_temp_residue
     ,0.43
     ,min_surface_temp_residue
     ,0.57);
   float64 max_surface_temp_crop  = max_temp + (0.437209 * max_temp) * exp(-0.86102 * leaf_area_index);  //990611
   float64 min_surface_temp_crop =min_temp + 0.057832*leaf_area_index + 0.95832; //990611
   float64  mean_surface_temp_crop = mean_surface_temp
        (max_surface_temp_crop,0.458,min_surface_temp_crop,0.542);               //990611
   float64 snow_depth_cm = m_to_cm(snow_depth_m);
   float64 mean_air_temp = (max_temp + min_temp) / 2.0;
   float64 result_actual_surface_temp = mean_surface_temp_residue;
  //  Residue equation works for bare soil.
   if (winter_time)
   { result_actual_surface_temp = mean_air_temp;
     if (leaf_area_index> 0)  result_actual_surface_temp =  mean_surface_temp_crop;
     if (residue_mass   > 0)  result_actual_surface_temp = mean_surface_temp_residue;
     if (snow_depth_cm  > 0)  result_actual_surface_temp =  -0.5;  // mean_surface_temp_snow;
   } else
      if (leaf_area_index > 0)
         result_actual_surface_temp =  mean_surface_temp_crop;
   return result_actual_surface_temp;
}
//_1998-09-14___________________________________________________________________

