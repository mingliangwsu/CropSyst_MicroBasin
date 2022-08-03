#ifndef crop_root_V5H
#define crop_root_V5H
#include "crop/crop_root.h"
namespace CropSyst {
//______________________________________________________________________________
class Crop_root_vital_V5
: public Crop_root_vital
{
   contribute_ float64 above_ground_biomass; // provided by caller
public:
   Crop_root_vital_V5
      (const Crop_parameters_struct::Root      &_parameter                       //061212
      ,const Crop_parameters_struct::Phenology &_phenology_parameters            //080722
      ,const Thermal_time_immutable   &_thermal_time
      ,const Soil_layers_interface &_soil_layers
      ,float32  _initial_root_length      ); // This is used by  calc_max_N_update_per_unit_root_length()
      // This requires a soil layering system.  If the crop model does not have soil available, it could provide a dummy soil
   virtual float64 calc_root_biomass(float64 *output_root_biomass_by_layer=0)   const;//060612
   virtual float64 know_above_ground_biomass(float64 _above_ground_biomass)  cognition_ //130625
      { above_ground_biomass = _above_ground_biomass; return above_ground_biomass; }
};
//_2013-06-24_________________________________________class:Crop_root_vital_V5_/
} // namespace CropSyst
#endif

