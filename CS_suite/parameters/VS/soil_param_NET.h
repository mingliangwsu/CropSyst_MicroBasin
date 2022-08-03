#ifndef soil_param_NETH
#define soil_param_NETH

namespace CropSyst_parameters
{
   class Soil_with_sublayering;
};

//#include <corn/primitive.h>
#include <CS_suite/parameters/soil_param_with_sublayers.h>

#define const_
namespace CropSyst_parameters_NET
{
//______________________________________________________________________________
public ref class Soil_with_sublayering
{
private:
   CropSyst_parameters::Soil_with_sublayering *soil;
public:
   Soil_with_sublayering(System::String ^soil_file_name);
   ~Soil_with_sublayering();
public: // layering accessors
   inline uint8  get_max_number_layers()                           const_ { return soil->get_max_number_layers(); };
      // This is the absolute maximum number of layers
      // (array dimension) that are reserved to store soil profile data by sublayer.
   inline uint8  get_number_layers()                               const_ { return soil->get_number_layers(); };
      // This is the number of sublayers identified in the soil profile.
   inline uint8  get_number_uninundated_layers()                   const_ { return soil->get_number_uninundated_layers(); };
   inline uint8 get_horizon_at_layer(uint8 layer   )               const_ { return soil->get_horizon_at_layer(layer   );};
//   inline virtual uint8 *get_divisions()                                   const_ { return soil->get_divisions(); };
//   inline virtual uint8 *get_in_layer_of()                                 const_ { return soil->get_in_layer_of(); };
   inline uint8 get_layer_at_depth(float64 a_given_depth_m)        const_ { return soil->get_layer_at_depth(a_given_depth_m);};   // 070828  { return sublayer_at(a_given_depth_m};
   inline uint8 get_layer_at_depth_or_last_layer
      (float64 a_given_depth_m)                                            const_ { return soil->get_layer_at_depth_or_last_layer(a_given_depth_m);};
      // Returns the index of the layer at the specified depth.
      // if  a_given_depth_m is 0.0 (unspecified) the last layer is returned
/*101105 OBSOLETE
 public: // being replaced with get_layer_at_depth()
   inline virtual uint8 sublayer_at
      (float64 a_given_depth_m,bool limit_to_MAX_trans_sublayers = false)  const_{ return soil->sublayer_at( a_given_depth_m, limit_to_MAX_trans_sublayers ) ;};
*/
 public: // layering parameters
   inline float64 get_thickness_m     (uint8 layer   )             const_ { return soil->get_thickness_m(layer   );};
   inline float64 get_thickness_cm    (uint8 layer   )             const_ { return soil->get_thickness_cm(layer   );};
   inline float64 get_thickness_mm    (uint8 layer   )             const_ { return soil->get_thickness_mm(layer   );};
   inline float64 get_depth_m(uint8 layer   )                  const_ { return soil->get_depth_m(layer   );};
      // if layer    is not specified, the total soil profile depth is returned
   inline float64 get_depth_cm        (uint8 layer   )             const_ { return soil->get_depth_cm( layer   );};
   inline float64 get_depth_mm        (uint8 layer   )             const_ { return soil->get_depth_mm( layer   );};
   inline float64 get_depth_profile_m()                            const_ { return soil->get_depth_profile_m();};
   inline float64 get_depth_profile_cm()                           const_ { return soil->get_depth_profile_cm();};
   inline float64 get_depth_profile_mm()                           const_ { return soil->get_depth_profile_mm();};
//   inline virtual float64 const *get_thickness_profile()                   const_ { return layering->get_thickness_profile();};
//   inline virtual float64 const *get_depth_profile()                       const_ { return layering->get_depth_profile();};
   inline uint8 closest_layer_at(float64 a_given_depth)             const_ { return soil->closest_layer_at(a_given_depth);};
 public: // texture parameters
   inline float64 get_sand_percent                      (uint8 layer)     const_ { return soil->get_sand_percent(layer); };
   inline float64 get_clay_percent                      (uint8 layer)     const_ { return soil->get_clay_percent(layer); };
   inline float64 get_silt_percent                      (uint8 layer)     const_ { return soil->get_silt_percent(layer); };
 public: // hydraulic parameters
   inline float64 get_saturation_water_content_volumetric
      (nat8 layer,float64 current_ice_water_content)                      const_{ return soil->get_saturation_water_content_volumetric(layer,current_ice_water_content);};
   inline float64 get_field_capacity_volumetric     (nat8 layer)   const_ { return soil->get_field_capacity_volumetric(layer) ;};
   inline float64 get_permanent_wilt_point_volumetric(nat8 layer)  const_ { return soil->get_permanent_wilt_point_volumetric(layer);};
   inline float64 get_lower_limit_volumetric        (nat8 layer)   const_ { return soil->get_lower_limit_volumetric(layer) ;};
   inline float64 get_drained_upper_limit_volumetric(nat8 layer)   const_ { return soil->get_drained_upper_limit_volumetric(layer);};
   // Note: Currently just returning field capacity but it is actually based on triangular distribution?
   inline float64 get_sat_hydraul_cond_kg_s_m3      (nat8 layer)   const_ { return soil->get_sat_hydraul_cond_kg_s_m3(layer);};
   inline float64 get_unsaturated_conductivity_function_slope(nat8 layer) const_{ return soil->get_unsaturated_conductivity_function_slope(layer);};
   // Note that this air entry potential is from the soil parameters
   // In CropSyst this is adjusted for ice content.
   inline float64 get_bypass_coef         (nat8 layer)                   const_ { return soil->get_bypass_coef(layer);};
   inline float64 get_Campbell_b          (nat8 layer,bool FC_PWP_based) const_{ return soil->get_Campbell_b           (layer,FC_PWP_based);};
   inline float64 get_air_entry_potential (nat8 layer,bool FC_PWP_based) const_{ return soil->get_air_entry_potential  (layer,FC_PWP_based);};

 public: // accessor properties (properties use PascalCase .NET naming convention
   property int MaxNumberLayers                 { int get()          { return get_max_number_layers(); }};
      // This is the absolute maximum number of layers
      // (array dimension) that are reserved to store soil profile data by layer   .
   property int NumberLayers                    { int get()          { return soil->get_number_layers(); }};
   property int NumberUninundatedLayers         { int get()          { return soil->get_number_uninundated_layers(); }};
   property int HorizonAtLayer[int]             { int get(int layer) { return soil->get_horizon_at_layer(layer);}};
   property double Thickness_m[int]             { double get(int layer) { return soil->get_thickness_m(layer);}};
   property double Thickness_cm[int]            { double get(int layer) { return soil->get_thickness_cm(layer);}};
   property double Thickness_mm[int]            { double get(int layer) { return soil->get_thickness_mm(layer);}};
   property double Depth_m[int]                 { double get(int layer) { return soil->get_depth_m(layer);}};
   property double Depth_cm[int]                { double get(int layer) { return soil->get_depth_cm( layer);}};
   property double Depth_mm[int]                { double get(int layer) { return soil->get_depth_mm( layer);}};
   property double DepthProfile_m               { double get() { return soil->get_depth_profile_m();}};
   property double DepthProfile_cm              { double get() { return soil->get_depth_profile_cm();}};
   property double DepthProfile_mm              { double get() { return soil->get_depth_profile_mm();}};
 public: // texture properties
   property double Sand_percent[int]            { double get(int layer) { return soil->get_sand_percent(layer); }};
   property double Clay_percent[int]            { double get(int layer) { return soil->get_clay_percent(layer); }};
   property double Silt_percent[int]            { double get(int layer) { return soil->get_silt_percent(layer); }};
 public: // hydraulic properties
   property double SaturationWaterContent_volumetric[int]   { double get(int layer) { return soil->get_saturation_water_content_volumetric(layer,0.0);}};
   property double FieldCapacity_volumetric[int]            { double get(int layer) { return soil->get_field_capacity_volumetric(layer) ;}};
   property double PermanentWiltPoint_volumetric[int]       { double get(int layer) { return soil->get_permanent_wilt_point_volumetric(layer);}};
   property double SaturationWaterContent[int]              { double get(int layer) { return soil->get_saturation_water_content_volumetric(layer,0.0);}};
   property double FieldCapacity[int]                       { double get(int layer) { return soil->get_field_capacity_volumetric(layer) ;}};
   property double PermanentWiltPoint[int]                  { double get(int layer) { return soil->get_permanent_wilt_point_volumetric(layer);}};
   property double FC[int]                                  { double get(int layer) { return soil->get_field_capacity_volumetric(layer) ;}};
   property double PWP[int]                                 { double get(int layer) { return soil->get_permanent_wilt_point_volumetric(layer);}};
   property double SaturatedHydraulicConductivity_kg_s_m3[int]{ double get(int layer) { return soil->get_sat_hydraul_cond_kg_s_m3(layer);}};
   property double Ksat[int]                                { double get(int layer) { return soil->get_sat_hydraul_cond_kg_s_m3(layer);}};
   property double UnsaturatedConductivityFunction_slope[int]{double get(int layer) { return soil->get_unsaturated_conductivity_function_slope(layer);}};
   property double BypassCoef[int]                          { double get(int layer) { return soil->get_bypass_coef(layer);}};
   property double CampbellB[int]                           { double get(int layer) { return soil->get_Campbell_b           (layer,false);}};
   property double AirEntryPotential[int]                   { double get(int layer) { return soil->get_air_entry_potential  (layer,false);}};
   // Note that this air entry potential is from the soil parameters
   // In CropSyst this is adjusted for ice content.
};
//______________________________________________________________________________
}; // namespace
#undef const_
#endif
