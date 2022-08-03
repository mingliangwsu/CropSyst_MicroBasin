#ifndef soil_texture_interfaceH
#define soil_texture_interfaceH
#include "corn/const.h"
#include "corn/primitive.h"
//______________________________________________________________________________
class Soil_texture_interface
{
public: // Texture parameters
   virtual float64 get_clay_percent                      (nat8 layer) const = 0;
   virtual float64 get_sand_percent                      (nat8 layer) const = 0;
   virtual float64 get_silt_percent                      (nat8 layer) const = 0;
public: // set
   virtual void set_sand_clay
      (nat8 layer, float64 _sand, float64 _clay)              modification_ = 0;
public: // Values for the entire profile
};
//______________________________________________________________________________
#endif

