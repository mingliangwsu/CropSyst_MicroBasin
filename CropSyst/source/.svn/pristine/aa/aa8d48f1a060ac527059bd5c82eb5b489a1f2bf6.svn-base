#ifndef profile_textureH
#define profile_textureH
#include "soil/texture_interface.h"
#include "soil/layering.h"
class Soil_layers_interface;
class Soil_parameters_class;
//______________________________________________________________________________
class Soil_profile_texture
: public Soil_texture_interface
{
protected:
   soil_layer_array64(sand);
   soil_layer_array64(clay);
   soil_layer_array64(silt);
public:
   Soil_profile_texture();
   Soil_profile_texture                                                          //150926
      (const Soil_layers_interface &_layers
      ,const Soil_parameters_class &parameters);
      // This constructure is used by scrutinize infiltration
      // where the soil layers match the soil horizon
public: // Accessors
   inline virtual float64 get_clay_percent      (nat8  layer)  const { return clay[layer];} //080313
   inline virtual float64 get_sand_percent      (nat8  layer)  const { return sand[layer];} //080313
   inline virtual float64 get_silt_percent      (nat8  layer)  const { return silt[layer];}
public:
   virtual void set_sand_clay_silt(nat8  layer, float64 _sand, float64 _clay, float64 _silt);
   virtual void set_sand_clay(nat8  layer, float64 _sand, float64 _clay);
};
//_2006-07-24___________________________________________________________________
#endif
