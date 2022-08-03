#include "crop/crop_root_V4.h"
#include "soil/soil_interface.h"
namespace CropSyst {
//______________________________________________________________________________
Crop_root_vital_V4::Crop_root_vital_V4
(const Crop_parameters_struct::Root      &_parameters
,const Crop_parameters_struct::Phenology &_phenology_parameters
//151106 ,const Crop_thermal_time   &_thermal_time
,const Thermal_time_immutable             &_thermal_time                         //151106
,const Soil_layers_interface &_soil_layers
,float32  _initial_root_length // This is used by  calc_max_N_update_per_unit_root_length()
)
: Crop_root_vital
   (_parameters,_phenology_parameters,_thermal_time,_soil_layers,_initial_root_length)
{}
//_2013-06-24___________________________________constructor:Crop_root_vital_V4_/
float64 Crop_root_vital_V4::calc_root_biomass(float64 *output_root_biomass_by_layer) const
{  // if root_biomass_by_layer array is passed, record the root biomass values by layer
   float64 calced_root_biomass = 0.0;
   uint8 number_soil_layers = soil_layers.get_number_layers();
   for (uint8 lyr = rooting_layer; (lyr < number_soil_layers); lyr++)
   {  float64 root_lengths_lyr = root_lengths[lyr];                              //061129
      float64 root_length_per_unit_mass_m_kg =  km_to_m(parameters.length_per_unit_mass_km_kg_V4);
      float64 root_biomass_lyr = root_lengths_lyr / root_length_per_unit_mass_m_kg;
      if (output_root_biomass_by_layer) output_root_biomass_by_layer[lyr] = root_biomass_lyr;
      calced_root_biomass += root_biomass_lyr;
   }
   return calced_root_biomass;
}
//_2006-06-12___________________________________________________________________
} // namespace CropSyst

