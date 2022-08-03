#ifndef layersH
#define layersH
#include "soil/layers_interface.h"
#include "soil/soil_param_class.h"
namespace CS
{
//______________________________________________________________________________
class Soil_layers
: public Soil_layers_interface   // <-- eventually move to soil_interface?
{
 public:
   inline virtual ~Soil_layers() {}                                              //150521
 public:
   virtual nat8   get_layer_at_depth(float64 a_given_depth_m)              const;
   virtual nat8   get_layer_at_depth_or_last_layer(float64 a_given_depth_m)const;
   // Returns the index of the layer at the specified depth.
   // if  a_given_depth_m is 0.0 (unspecified) the last layer is returned

   inline virtual nat8 get_horizon_at_layer(nat8 layer)                    const
      { return layer; }
      // In a basic layering system the horizons are layers.
      // This returns the layer (horizon) in which the specified layer/sublayer occurs.
   virtual float64 get_depth_profile_m()                                   const;
      // This returns the total depth of the soil profile in centimeters.
   virtual nat8    closest_layer_at(float64 a_given_depth)                 const;
      // Returns the closest layer at the specified depth.
 public: // Utilities for working with layer data
   virtual void copy_array64(soil_layer_array64(target),const soil_layer_array64(source)) const;
   virtual void copy_array32(soil_layer_array32(target),const soil_layer_array32(source)) const;
};
//______________________________________________________________________________
} // namespace CS

//______________________________________________________________________________
namespace CropSyst
{
//______________________________________________________________________________
class Soil_layers
: public extends_ CS::Soil_layers
{
 protected:
   const Soil_parameters_class  &parameters;                                     //160916
 public:
   Soil_layers(const Soil_parameters_class  &_parameters);                       //160916
 public: // Soil parameter accessors
   virtual nat8   get_max_number_layers()                                  const { return MAX_soil_horizons_alloc; }
   virtual nat8   get_number_layers()                                      const { return parameters.number_horizons;}
 public: // Soil profile parameter accessors (layer number is 1 based)
   virtual float64 get_thickness_m                       (nat8  layer)     const { return parameters.get_horizon_thickness(layer); }
      // These return the thickness of the specified layer
   virtual float64 get_depth_m                           (nat8  layer)     const { return parameters.get_horizon_depth(layer); }
      // These return the depths to the bottom of the specified layer.
   virtual bool  is_bound_by_impermeable_layer()                           const //160921
      { return parameters.bound_by_bedrock; }
};
//_2013-11-22___________________________________________________________________
} // namespace CropSyst

#endif
