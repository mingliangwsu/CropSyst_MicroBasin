#ifndef soil_param_with_sublayersH
#define soil_param_with_sublayersH

#include "soil/soil_properties_sublayers.h"


namespace CropSyst_parameters
{
//______________________________________________________________________________
class Soil_with_sublayering
: public Soil_properties_sublayers
{
   Smart_soil_parameters parameters;
 public:
    Soil_with_sublayering();
    bool read_file(const char *filename);
public:
   inline virtual nat8  get_max_number_sublayers()                         const { return layers->get_max_number_sublayers() ; };
      // This is the absolute maximum number of layers
      // (array dimension) that are reserved to store soil profile data by sublayer.
   inline virtual nat8   get_number_sublayers()                            const { return layers->get_number_sublayers(); } ;
      // This is the number of sublayers identified in the soil profile.
   inline virtual nat8  get_number_uninundated_sublayers()                 const { return layers->get_number_uninundated_sublayers(); };
   inline virtual nat8  get_max_number_layers()                            const { return layers->get_max_number_layers(); };
      // This is the absolute maximum number of layers
      // (array dimension) that are reserved to store soil profile data by sublayer.
   inline virtual nat8  get_number_layers()                                const { return layers->get_number_layers(); };
      // This is the number of sublayers identified in the soil profile.
   inline virtual nat8  get_number_uninundated_layers()                    const { return layers->get_number_uninundated_layers(); };
   inline virtual nat8 get_horizon_at_layer(nat8 sublayer)                 const { return layers->get_horizon_at_layer(sublayer);};
//   inline virtual nat8 *get_divisions()                                   const { return layers->get_divisions(); };
//   inline virtual nat8 *get_in_layer_of()                                 const { return layers->get_in_layer_of(); };
   inline virtual nat8 get_layer_at_depth(float64 a_given_depth_m)         const { return layers->get_layer_at_depth(a_given_depth_m); };  // 070828
   inline virtual nat8 get_layer_at_depth_or_last_layer
      (float64 a_given_depth_m)                                            const { return layers->get_layer_at_depth_or_last_layer(a_given_depth_m);};
      // Returns the index of the layer at the specified depth.
      // if  a_given_depth_m is 0.0 (unspecified) the last layer is returned

 public: // being replaced with get_layer_at_depth()
   inline virtual nat8 sublayer_at
      (float64 a_given_depth_m,bool limit_to_MAX_trans_sublayers = false)  const{ return layers->sublayer_at( a_given_depth_m, limit_to_MAX_trans_sublayers ) ;};
 public: // layering
   inline virtual float64 get_thickness_m     (nat8 sublayer)              const { return layers->get_thickness_m(sublayer);};
   inline virtual float64 get_thickness_cm    (nat8 sublayer)              const { return layers->get_thickness_cm(sublayer);};
   inline virtual float64 get_thickness_mm    (nat8 sublayer)              const { return layers->get_thickness_mm(sublayer);};
   inline virtual float64 get_depth_m(nat8 sublayer = 0)                   const { return layers->get_depth_m(sublayer);};
      // if sublayer is not specified, the total soil profile depth is returned
   inline virtual float64 get_depth_cm        (nat8 sublayer)              const { return layers->get_depth_cm( sublayer);};
   inline virtual float64 get_depth_mm        (nat8 sublayer)              const { return layers->get_depth_mm( sublayer);};
   inline virtual float64 get_depth_profile_m()                            const { return layers->get_depth_profile_m();};
   inline virtual float64 get_depth_profile_cm()                           const { return layers->get_depth_profile_cm();};
   inline virtual float64 get_depth_profile_mm()                           const { return layers->get_depth_profile_mm();};
   inline virtual float64 const *get_thickness_profile()                   const { return layers->get_thickness_profile();};
   inline virtual float64 const *get_depth_profile()                       const { return layers->get_depth_profile();};
   inline virtual nat8 closest_layer_at(float64 a_given_depth)             const { return layers->closest_layer_at(a_given_depth);};

 public: // texture
   virtual float64 get_sand_percent                      (nat8  layer)     const { return texture.get_sand_percent(layer); };
   virtual float64 get_clay_percent                      (nat8  layer)     const { return texture.get_clay_percent(layer); };
   virtual float64 get_silt_percent                      (nat8  layer)     const { return texture.get_silt_percent(layer); };
 public: // texture set
   // NYN virtual void set_sand_clay(uint8 layer, float64 _sand, float64 _clay) modification_ = 0;
 public: // hydraulic properties
   inline virtual float64 get_saturation_water_content_volumetric(nat8 layer, float64 current_ice_water_content)const{ return hydraulic_properties->get_saturation_water_content_volumetric(layer, current_ice_water_content);};
   inline virtual float64 get_field_capacity_volumetric     (nat8 layer)   const { return hydraulic_properties->get_field_capacity_volumetric(layer) ;};
   virtual float64 get_permanent_wilt_point_volumetric      (nat8 layer)   const { return hydraulic_properties->get_permanent_wilt_point_volumetric(layer);};
   inline virtual float64 get_lower_limit_volumetric        (nat8 layer)   const { return hydraulic_properties->get_lower_limit_volumetric(layer) ;};
   inline virtual float64 get_drained_upper_limit_volumetric(nat8 layer)   const { return hydraulic_properties->get_drained_upper_limit_volumetric(layer);};
   // Note: Currently just returning field capacity but it is actually based on triangular distribution?
   inline virtual float64 get_sat_hydraul_cond_kg_s_m3      (nat8 layer)   const { return hydraulic_properties->get_sat_hydraul_cond_kg_s_m3(layer);};
   inline virtual float64 get_unsaturated_conductivity_function_slope(nat8 layer) const{ return hydraulic_properties->get_unsaturated_conductivity_function_slope(layer);};
   // Note that this air entry potential is from the soil parameters
   // In CropSyst this is adjusted for ice content.
   inline virtual float64 get_bypass_coef                   (nat8 layer)   const { return hydraulic_properties->get_bypass_coef(layer);};
   inline virtual float64 get_Campbell_b          (nat8 layer,bool FC_PWP_based) const{ return hydraulic_properties->get_Campbell_b           (layer,FC_PWP_based);};
   inline virtual float64 get_air_entry_potential (nat8 layer,bool FC_PWP_based) const{ return hydraulic_properties->get_air_entry_potential  (layer,FC_PWP_based);};
};
//______________________________________________________________________________
}; // namespace
#endif

