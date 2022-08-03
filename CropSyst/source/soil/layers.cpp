#include "soil/layers.h"
#include "corn/math/compare.hpp"
namespace CS
{
//______________________________________________________________________________
nat8 Soil_layers::get_layer_at_depth(float64 a_given_depth_m)              const
{  float64 layerdepth = 0.0;
   nat8 layer = 0;
   do
   { layer++;
     layerdepth += get_thickness_m(layer);
   } while ((layerdepth < a_given_depth_m) && (layer < get_number_layers()));
   return layer;                                                                 //970509
}
//_________________________________________________________get_layer_at_depth__/
nat8 Soil_layers::get_layer_at_depth_or_last_layer
(float64 a_given_depth_m)                                                  const
{  // Returns the index of the layer at the specified depth.
   // if  a_given_depth_m is 0.0 (unspecified) the last layer is returned
   return (CORN::is_approximately<float64>(a_given_depth_m,0.0,0.0000001))       //040524
   ? get_number_layers()                                                         //131122_040524
   : get_layer_at_depth(a_given_depth_m);
}
//___________________________________________get_layer_at_depth_or_last_layer__/
nat8 Soil_layers::closest_layer_at(float64 a_given_depth)                  const
{  float64 layer_depth = 0.0;
   bool done = false;
   nat8 layer = 0;
   while (! done)
   {  layer++;
      float64 thickness_layer = get_thickness_m(layer);
      layer_depth += thickness_layer;
      if (layer == get_number_layers()) done = true;                             //131122
      if (layer_depth >= a_given_depth)
      {  done = true;
         if ((layer_depth - a_given_depth) > thickness_layer / 2.0)
         layer--;
      }
   }
   return layer;
}
//_1996-06-03________________________________________________closest_layer_at__/
void Soil_layers::copy_array64
(soil_layer_array64(target)
,const soil_layer_array64(source))                                         const
{  for (nat8 layer = 0; layer <= MAX_soil_sublayers; layer++)
      target[layer] = source[layer];
}
//_1999-02-14____________________________________________________copy_array64__/
void Soil_layers::copy_array32
(soil_layer_array32(target)
,const soil_layer_array32(source))                                         const
{  for (nat8 layer = 0; layer <= MAX_soil_sublayers; layer++)
      target[layer] = source[layer];
}
//_1999-02-14____________________________________________________copy_array32__/
float64 Soil_layers::get_depth_profile_m()                                 const
{  float64 depth = 0;
   for (nat8 layer = 1; layer <= get_number_layers(); layer++)
      depth += get_thickness_m(layer);
   return depth;
}
//_2013-11-22_1998-12-17________________________________________________________
//______________________________________________________________________________
} // CS
namespace CropSyst
{
//______________________________________________________________________________
Soil_layers::Soil_layers(const Soil_parameters_class  &_parameters)            //160916
: parameters(_parameters)
{}
//______________________________________________________________________________
} // namespace CropSyst

