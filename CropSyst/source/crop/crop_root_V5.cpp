#include "crop/crop_root_V5.h"
#include "crop/thermal_time.h"
#include "soil/soil_interface.h"

namespace CropSyst {
//______________________________________________________________________________
Crop_root_vital_V5::Crop_root_vital_V5
(const Crop_parameters_struct::Root      &_parameters
,const Crop_parameters_struct::Phenology &_phenology_parameters
,const Thermal_time_immutable             &_thermal_time
,const Soil_layers_interface &_soil_layers
,float32  _initial_root_length) // This is used by  calc_max_N_update_per_unit_root_length()
: Crop_root_vital
   (_parameters,_phenology_parameters,_thermal_time,_soil_layers,_initial_root_length)
, above_ground_biomass(0)
{  biomass = 0.00001;
   // this is just to prevent a div 0 on the first day
}
//_2013-06-24___________________________________constructor:Crop_root_vital_V5_/
float64 Crop_root_vital_V5::calc_root_biomass(float64 *output_root_biomass_by_layer) const
{  // if root_biomass_by_layer array is passed, record the root biomass values by layer
   float64 accum_thermal_time = thermal_time.get_accum_degree_days(false);
   float64 root_shoot_ratio =
      (accum_thermal_time > phenology_parameters.culmination.root_depth)
      ? parameters.root_shoot_full_ratio
      : parameters.root_shoot_full_ratio +
         (parameters.root_shoot_emergence_ratio - parameters.root_shoot_full_ratio)
            *  pow((  (phenology_parameters.culmination.root_depth - accum_thermal_time)
                    / (phenology_parameters.culmination.root_depth - phenology_parameters.initiation.emergence))
                  , 3.0);
   float64 calced_root_biomass = above_ground_biomass * root_shoot_ratio;
   calced_root_biomass = std::max<float64>(calced_root_biomass,biomass);
   if (output_root_biomass_by_layer)
      for (uint8 lyr = rooting_layer; (lyr <= soil_layers.get_number_layers()); lyr++)
      {  float64 root_biomass_lyr = total_fract_root_length[lyr] * calced_root_biomass;
         output_root_biomass_by_layer[lyr] = root_biomass_lyr;
      }
   return calced_root_biomass;
}
//_2006-06-12___________________________________________________________________
} // namespace CropSyst

