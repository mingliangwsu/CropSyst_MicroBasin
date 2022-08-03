#ifndef crop_root_V4H
#define crop_root_V4H
#include "crop/crop_root.h"

namespace CropSyst {
//______________________________________________________________________________
class Crop_root_vital_V4
: public Crop_root_vital                                                         //070131
{
public:
   Crop_root_vital_V4
      (const Crop_parameters_struct::Root      &_parameter                       //061212
      ,const Crop_parameters_struct::Phenology &_phenology_parameters            //080722
      ,const Thermal_time_immutable  &_thermal_time                              //151105
      //151106 ,const Crop_thermal_time   &_thermal_time
      ,const Soil_layers_interface &_soil_layers
      ,float32  _initial_root_length ); // This is used by  calc_max_N_update_per_unit_root_length()
      // This requires a soil layering system.  If the crop model does not have soil available, it could provide a dummy soil
   virtual float64 calc_root_biomass(float64 *output_root_biomass_by_layer=0)   const;//060612
};
//_2013-06-24_________________________________________class:Crop_root_vital_V5_/
} // namespace CropSyst

#endif

