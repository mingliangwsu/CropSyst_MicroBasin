#ifndef layers_interfaceH
#define layers_interfaceH
#ifndef layeringH
#   include "soil/layering.h"
#endif
#include "corn/const.h"
#include "corn/measure/measures.h"
//____________________________________________________________________________
interface_ Soil_layers_interface
{
   inline virtual ~Soil_layers_interface() {}                                           //150318
 public: // Soil parameter accessors
   virtual nat8   get_max_number_layers()                                  const = 0;
      // This is the absolute maximum number of layers
      // (array dimension) that are reserved to store soil profile data by layer.
   virtual nat8   get_number_layers()                                      const = 0;
      // This is the number of layers identified in the soil profile.
      //13112 I am thinking of replacing get_number_layers() with count.
   inline virtual nat8 count()                                             const
      { return get_number_layers(); }
   inline virtual nat8 get_number_uninundated_layers()                     const
      { return get_number_layers(); }                                            //131122
      // This is usually the same value returned by get_number_layers()
      // however, in the CropSyst finite difference model when there is a water
      // table extending up into the vadose zone, this is the number of layers
      // (from the top of the profile) that are not inundated
      // [used to be called get_number_effective_layers]
      // Generally this represents the vadose zone, but there could
      // indeed by soil layers below the simulated soil profile and the water table.
   virtual nat8   get_layer_at_depth
      (float64 a_given_depth_m
      /*, bool limit_to_MAX_trans_layers=false*/)                          const = 0;
      // Returns the index of the layer at the specified depth.

      // Note  need to get ride of   bool limit_to_MAX_trans_layers=false
      // Instead, caller should take the min of the layer at depth
      // or layer at max_transformation_depth

   virtual nat8   get_layer_at_depth_or_last_layer
      (float64 a_given_depth_m
      /*, bool limit_to_MAX_trans_layers=false*/)                          const = 0;
      // Returns the index of the layer at the specified depth.
      // if  a_given_depth_m is 0.0 (unspecified) the last layer is returned
   virtual nat8  get_horizon_at_layer(nat8 layer)                          const = 0;
      // This returns the layer (horizon) in which the specified layer/sublayer occurs.
   virtual bool  is_bound_by_impermeable_layer()                           const = 0; //160921
 public: // Soil profile parameter accessors (layer number is 1 based)
   // The following return the thickness of the specified layer in the respective units.
   virtual float64 get_thickness_m                      (nat8  layer)      const = 0;
   inline virtual float64 get_thickness_cm              (nat8  layer)      const { return m_to_cm(get_thickness_m(layer)); }  //131122
   inline virtual float64 get_thickness_mm              (nat8  layer)      const { return m_to_mm(get_thickness_m(layer)); }  //131122

   virtual float64 get_depth_m(nat8  layer = 0)                            const = 0;
   inline virtual float64 get_depth_cm        (nat8  layer)                const { return m_to_cm(get_depth_m(layer));};   //131122
   inline virtual float64 get_depth_mm        (nat8  layer)                const { return m_to_mm(get_depth_m(layer));};   //131122_101026
      // These return the depths to the bottom of the specified layer.
   virtual float64 get_depth_profile_m                  ()                 const = 0;
      // This returns the total depth of the soil profile in meters.
   inline virtual float64 get_depth_profile_cm                  ()         const
      { return m_to_cm(get_depth_profile_m()); }
      // This returns the total depth of the soil profile in centimeters.
   inline virtual float64 get_depth_profile_mm()                           const
      { return m_to_mm(get_depth_profile_m()); }
      // This returns the total depth of the soil profile in millimeters.
    virtual nat8    closest_layer_at(float64 a_given_depth)                const = 0;
      // Returns the closest layer at the specified depth.
   virtual float64 get_layer_center_depth(nat8  sublayer)                  const  // m
      { return get_depth_m(sublayer) - (get_thickness_m(sublayer)/2.0); }
 public: // set accessors
   inline virtual nat8  set_number_uninundated_layers
      (nat8  new_uninundated_layers)                               modification_
       { return 0; }                                                             //131122
 public: // Utilities for working with layer data
   virtual void copy_array64(soil_layer_array64(target),const soil_layer_array64(source)) const = 0;
   virtual void copy_array32(soil_layer_array32(target),const soil_layer_array32(source)) const = 0;
};
//______________________________________________________________________________
#endif
