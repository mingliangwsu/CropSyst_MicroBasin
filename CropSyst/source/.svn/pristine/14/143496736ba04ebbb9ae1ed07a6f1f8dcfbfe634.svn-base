#ifndef sublayersH
#define sublayersH

#include "soil/soil_interface.h"
#include "soil/layers.h"
#include "corn/measure/measures.h"
//_Forward declarations_________________________________________________________
class Soil_parameters;
//_______________________________________________________Forward declarations__/
class Soil_sublayers
: public extends_ CropSyst::Soil_layers
{
   friend class Soil_base;                                                       //061003
   friend class Soil_cropsyst_specific;                                          //061003
   friend class Soil_tillage_effect;                                             //061003
   friend class Soil_properties_sublayers;                                       //101104
 protected:
   const Soil_parameters               &parameters;                              //160916_060206
      // parameters doesn't appear to be used
   nat8 num_sublayers;
   nat8 num_uninundated_sublayers;      // Number of effective sublayers (this is 1 minus the number of the layer that is saturated by the water table) 080211_
 public:
   soil_layering(in_horizon_of);
   soil_layering(divisions);           // how many times the horizon is subdivided
   soil_sublayer_array_64(depth);
   soil_sublayer_array_64(thickness);
 public:
   Soil_sublayers(const Soil_parameters &_parameters);
   void copy(const Soil_sublayers &copy_from);
   virtual void expand_last_layer_for_boundary_conditions                           //080130
      (uint8 number_layers,nat8 number_expanded_layers)            modification_; // initialization 080211_
      // This is used by the finite difference
 public: // Soil parameter accessors
   virtual nat8   get_max_number_sublayers()                               const { return MAX_soil_sublayers; }
      // This is the absolute maximum number of layers
      // (array dimension) that are reserved to store soil profile data by sublayer.
   inline virtual nat8    get_number_sublayers()                           const { return num_sublayers; }
      // This is the number of sublayers identified in the soil profile.
   virtual nat8   get_number_uninundated_sublayers()                       const { return num_uninundated_sublayers; }  //080208
   inline virtual nat8   get_max_number_layers()                           const {return get_max_number_sublayers(); }
      // This is the absolute maximum number of layers
      // (array dimension) that are reserved to store soil profile data by sublayer.
   inline virtual nat8   get_number_layers()                               const { return get_number_sublayers(); }
      // This is the number of sublayers identified in the soil profile.
   inline virtual nat8   get_number_uninundated_layers()                   const { return get_number_uninundated_sublayers(); }
   inline virtual nat8  get_horizon_at_layer(nat8  sublayer)               const { return in_horizon_of[sublayer];}
#ifdef PESTICIDE
   inline virtual const nat8  *get_divisions()                             const { return divisions; }
   inline virtual const nat8  *get_in_layer_of()                           const { return in_horizon_of; }
#endif
 public: // being replaced with get_layer_at_depth()
   virtual nat8  sublayer_at(float64 a_given_depth_m,bool limit_to_MAX_trans_sublayers = false) const;
 public:
   inline virtual float64 get_thickness_m     (nat8  sublayer)             const { return thickness[sublayer]; }
   virtual float64 get_depth_m(nat8  sublayer = 0)                         const;
      // if sublayer is not specified, the total soil profile depth is returned
   inline virtual const float64 *get_thickness_profile()                   const { return thickness ; }  // m
   inline virtual const float64 *get_depth_profile()                       const { return depth; }
 public:
   inline virtual nat8  set_number_uninundated_layers                            //061004
      (nat8  new_uninundated_layers)                               modification_ { num_uninundated_sublayers = new_uninundated_layers; return new_uninundated_layers; }
 public: // Miscellaneous applies only to sublayers for horizon to sublayer conversion
   float64 distribute_amount                                                     //070606
      (const      soil_horizon_array32  (from_horizon_amount)
      ,modifiable_  soil_sublayer_array_64(to_sublayer_amount))           const;
      // This is used for amounts which are divided into the respetive sublayers for each horizon
      // Returns the total amount for the profile.
   float64 distribute_property                                                   //070606
      (const      soil_horizon_array32  (from_horizon_property)
      ,modifiable_  soil_sublayer_array_64(to_sublayer_property))         const;
      // This is used for percentage and concentrations where the percentage or  concentration for the sublayer is the same as the horizon.
      // Currently returns 0.0 (not sure what useful information could be return (maybe mean concentration?)

/*
// Maybe try to move these to Crop?
   virtual nat8  get_rooting_sublayer() const = 0;
   // This is the soil layer (from the top) where the plant root may sprout from.
   // Usually you can simply return 2 (This is what CropSyst uses).
   virtual nat8  set_rooting_sublayer(nat8  rooting_sl) = 0;
   // This can be used to set the rooting layer.
*/
};
//_2005-11-16__________________________________________________Soil_sublayers__/
#endif

