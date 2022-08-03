#ifndef soil_abstractH
#define soil_abstractH

/* 031111
This abstract class provides an interface for working with soil objects
for various crop models (CropSyst)
*/

#ifndef primitiveH
#  include <corn/primitive.h>
#endif
#include "soil/soil_interface.h"
#define ENTIRE_PROFILE_DEPTH_as_9999 9999

class Soil_abstract
: public Soil_layers_interface
{
public: // Constructors
//   xSoil_abstract() {};

#ifndef NYI

public: // Soil parameter accessors
   virtual nat8   get_max_number_sublayers() const = 0;
   // This is the absolute maximum number of layers
   // (array dimension) that are reserved to store soil profile data by layer.
   virtual nat8   get_number_sublayers()     const = 0;
   // This is the number of sublayers identified in the soil profile.
   virtual nat8   sublayer_at(float64 a_given_depth_m = ENTIRE_PROFILE_DEPTH, bool limit_to_MAX_trans_sublayers=false) const = 0;
   // Returns the index of the layer at the specified depth.

   virtual nat8  get_layer_at_sublayer(nat8  layer) const  = 0;
   // This returns the layer (horizon) in which the specified layer    occurs.

   virtual nat8  get_rooting_sublayer() const = 0;
   // This is the soil layer (from the top) where the plant root may sprout from.
   // Usually you can simply return 2 (This is what CropSyst uses).
   virtual nat8  set_rooting_sublayer(nat8  rooting_sl) = 0;
   // This can be used to set the rooting layer.

   virtual float64 get_SLPF()                const = 0;
   // This is used by the CropGro submodel.
   // If never using the CropGro model, simply return 0.92.

public: // Soil profile parameter accessors (layer    number is 1 based)
   virtual float64 get_root_hospitality_factor           (nat8  layer   )  const = 0;
   // This is used by the CropGro submodel.
   // If never using the CropGro model, simply return 1.0.

   virtual float64 get_bulk_density_g_cm3                (nat8  layer   )  const = 0;
   // This returns the bulk density of the specified layer in grams per cubic centimeter.
   virtual float64 get_thickness_mm                      (nat8  layer   )  const = 0;
   virtual float64 get_thickness_cm                      (nat8  layer   )  const = 0;
   virtual float64 get_thickness_m                       (nat8  layer   )  const = 0;
   // These return the thickness of the specified layer   

   virtual float64 get_depth_cm                          (nat8  layer   )  const = 0;
   virtual float64 get_depth_m                           (nat8  layer   )  const = 0;
   // These return the depths to the bottom of the specified layer   

   virtual float64 get_depth_profile_cm                  ()                const = 0;
   // This returns the total depth of the soil profile in centimeters

   virtual float64 get_saturation_water_content_volumetric  (nat8  layer   ,float64 current_ice_water_conten)  const = 0;

   virtual float64 get_field_capacity_volumetric         (nat8  layer   )  const = 0;
   // Field capacity is either cm3/cm3 or m3/m3

   virtual float64 get_drained_upper_limit_volumetric    (nat8  layer)     const = 0;
   // Note: I think this may be field capacity

   virtual float64 get_lower_limit_volumetric            (nat8  layer)     const = 0;
   // Note: I think this may be PWP
#ifdef CHECK_OBSOLETE
101104 now we pass texture where needed
   virtual float64 get_clay_percent                      (nat8  layer   )  const = 0;
   virtual float64 get_sand_percent                      (nat8  layer   )  const = 0;
   virtual float64 get_silt_percent                      (nat8  layer   )  const = 0;
#endif
public: // Soil profile state accessors
   virtual float64 get_temperature_C                     (nat8  layer   )  const = 0;

//NYI virtual float64 get_liquid_water_content_volumetric(nat8  layer   )  const = 0;
   virtual float64 get_liquid_water_content_volumetric   (nat8  layer   )  const = 0;
   virtual float64 get_water_filled_porosity             (nat8  layer   )  const = 0;
   virtual float64 get_water_pot                         (nat8  layer   )  const = 0;
   virtual const float64 *get_water_pot_array            ()                const = 0;
   // Provide here an array of the soil water potential.
   // Index 0 is not used (the value for index 0 should be 0.0).
   // The arrays must be dimensioned no less than the count get_max_number_sublayers() returns.

//   virtual float64 get_available_water(nat8  layer   , bool real_wilt_based) const = 0;
   virtual float64 get_plant_avail_water(nat8  layer   )                   const = 0;

   virtual float64 get_albedo()                                            const = 0;
   // Returns the current albedo of the soil surface.
   // You may return a designated constant or a user specified soil parameter.
   // Often this value is adjusted for soil moisture

public: // Soil salinity accessors

   virtual float64 get_salt_stress_function
   (nat8  layer   ,float64 osmotic_pot_50,float64 salt_tolerance_P )       const = 0;
   // Derived classes can return 1.0 if not interested in salinity

   virtual float64 get_osmotic_pot_solution(nat8  layer   )                const = 0;
   // Derived classes can return 0.0 if not interested in salinity


public:
   virtual float64 get_act_evaporation()                                   const = 0;
   // Return the computed actual soil water evaporation in meters

public: // processes
   virtual float64 extract_water(float64 water_uptake_m[],nat8  start_layer) = 0;
   // This function should removed the specified soil water (in depth) from each of the layers.
   // The specified water uptake is usually extracted do to crop transpiration,
   // but this function may also be used for other functions such as evaporation
   // or other water fates.
   // The function should return the actual water uptake.
   // The caller of this function will normally only specify the amount to exctract
   // based on the current water content for the respective layers.
   // So the returned value should usually match the sum of the passed water_uptake_m
   // array.
   // If for some reason, there was not enough water in the soil, then
   // the returned value may be less than the sum of the passed array indicating that there
   // was not enough water.
   // It is suggested to change the array values to the actual
   // values that could be uptaken from each layer.
   // This function should also update water potentials (if used).
#endif
};

#endif

