#include "soil/profile_texture.h"
#include "soil/layers_interface.h"
#include "soil/soil_param_class.h"
//______________________________________________________________________________
Soil_profile_texture::Soil_profile_texture()
: Soil_texture_interface()
{
   clear_layer_array64(sand);
   clear_layer_array64(clay);
   clear_layer_array64(silt);
}
//______________________________________________________________________________
void Soil_profile_texture::set_sand_clay_silt
(nat8  layer, float64 sand_, float64 clay_, float64 silt_)
{  sand[layer] = sand_;
   clay[layer] = clay_;
   silt[layer] = silt_;
}
//______________________________________________________________________________
void Soil_profile_texture::set_sand_clay(nat8  layer, float64 sand_, float64 clay_)
{  float64 silt_ = 100.0 - (sand_ + clay_);                                      //160830
   set_sand_clay_silt(layer,sand_,clay_,silt_);
}
//______________________________________________________________________________
Soil_profile_texture::Soil_profile_texture
(const Soil_layers_interface &layers
,const Soil_parameters_class &parameters)
{
   for (nat8 layer = 1; layer <= layers.get_number_layers(); layer ++)           //160830
   {
      set_sand_clay_silt
         (layer
         ,parameters.get_horizon_sand(layer)
         ,parameters.get_horizon_clay(layer)
         ,parameters.get_horizon_silt(layer));
   }
}
//_2015-09-26___________________________________________________________________

