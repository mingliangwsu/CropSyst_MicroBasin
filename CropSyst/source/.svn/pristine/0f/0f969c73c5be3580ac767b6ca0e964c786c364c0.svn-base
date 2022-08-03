#ifndef hydrology_interfaceH
#define hydrology_interfaceH
#ifndef primitiveH
#   include "corn/primitive.h"
#endif
#ifndef time_typesH
#   include "corn/chronometry/time_types.hpp"
#endif
#include "common/physics/standard_constants.h"
#include "CS_suite/observation/CS_observation.h"
#include "soil/layering.h"
#include "model_options.h"
#define ICE_WATER_CONTENT_IRRELEVENT 0.0
#define ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822 0.0

//______________________________________________________________________________
class Soil_hydraulic_properties_interface
{
public: // may be computed by pedotransfer functions
   // The default units system is metric MKS unless otherwise noted in the variable name or code comments
   // Volumetric values  are  volume of water per volume of (soil + water)
   // in units of m3/m3 (Equivelent to cm3/cm3)
   virtual float64 get_field_capacity_volumetric             ( nat8 layer) const = 0;
   virtual float64 get_permanent_wilt_point_volumetric       ( nat8 layer) const = 0;
   virtual float64 get_drained_upper_limit_volumetric        ( nat8 layer) const = 0;
   // Note: I think this may be field capacity
   virtual float64 get_lower_limit_volumetric                ( nat8 layer) const = 0;
   // Note: I think this may be PWP
   virtual float64 get_saturation_water_content_volumetric   ( nat8 layer,float64 current_ice_water_content) const = 0;
   //    Usually {  return 1.0 - get_bulk_density_g_cm3(layer) / 2.65;
   virtual float64 get_unsaturated_conductivity_function_slope( nat8 layer)const = 0;
   virtual float64 get_bypass_coef                           ( nat8 layer) const = 0;
   virtual float64 get_sat_hydraul_cond_kg_s_m3              ( nat8 layer) const = 0;  // rename to get_saturated_hydraulaulic_conductivity_kg_s_m3
   inline virtual float64 get_sat_hydraul_cond_m_hr          ( nat8 layer) const
      { return  get_sat_hydraul_cond_kg_s_m3(layer) *
         standard_gravity/1000.0
         //170501 0.00981
         * 3600.0; }
      //< \return sat_hydraul_cond converted to m/hr
/*NYN
   virtual float64 get_sat_hydraul_cond_lateral_flow_kg_s_m3 ( nat8 layer) const = 0;  // rename to get_saturated_hydraulaulic_conductivity_kg_s_m3
   inline virtual float64 get_sat_hydraul_cond_lateral_flow_m_hr ( nat8 layer) const
      { return  get_sat_hydraul_cond_lateral_flow_kg_s_m3(layer) * standard_gravity/1000.0 * 3600.0; }
      //< \return sat_hydraul_cond converted to m/hr
*/
   virtual float64 get_Campbell_b          ( nat8 layer,bool FC_PWP_based) const = 0;
   virtual float64 get_air_entry_potential ( nat8 layer,bool FC_PWP_based) const = 0;
   virtual float64 get_water_pot_at_FC     ( nat8 layer)                   const = 0;
   virtual const float64 *ref_soil_water_pot_at_FC() /* profile array */   const = 0;//170501
};
//______________________________________________________________________________
class Soil_hydrology_interface
{
 public: // Soil profile state accessors
   inline virtual ~Soil_hydrology_interface() {}                                 //170217
   // Water content is a measurement of the quality of water
   // It can be either volumetric or gravimetric.
   //    Volumetric is (water_volume / bulk_material_volume)
   //    Gravimetric is (water_mass / bulk_material_mass)
   // Water amounts are reported in meters of depth which is equivelent to (I think kg/m3 ?) and
   // some variables/functions refer to water amount as water depth.
   virtual float64 get_water_plus_ice_content_gravimetric   ( nat8 layer)  const = 0;
   virtual float64 get_liquid_water_content_volumetric      ( nat8 layer)  const = 0;
   virtual float64 get_water_plus_ice_content_volumetric_at ( nat8 layer,CORN::Hour hour)  const = 0;
   virtual float64 get_water_plus_ice_content_volumetric    ( nat8 layer)  const = 0;
   virtual float64 get_water_filled_porosity( nat8 layer, CORN::Hour for_hour)   const = 0;  // for_hour=24 for daily value
   virtual float64 get_water_potential                      ( nat8 layer)  const = 0;
   virtual float64 provide_water_depth_profile(bool all_water)        provision_ = 0; //130930
   virtual float64 get_plant_avail_water( nat8 layer)                      const = 0;
      // Need to check if this is volumetric or depth
   virtual float64 calc_water_depth_profile(bool all_water)                const = 0; //170601
   virtual float64 calc_available_water_fraction(nat8 layer, bool real_wilt_based) const = 0; //160601
   virtual float64 calc_available_water_depth_to(float64 depth)     calculation_ = 0; //160601
   virtual float64 calc_ice_depth_to(float64 depth = 9999)          calculation_ = 0; //160724
   virtual float64 get_K_Theta
      (nat8 layer
      ,float64 Theta, float64 Theta_s)                                     const = 0;
   virtual float64 *get_liquid_water_content_layers_volumetric                   //140527
      (soil_layer_array64(water_content_layers))                           const
      {  for ( nat8 layer = 0; layer < MAX_soil_layers; layer++)
            water_content_layers[layer] = get_liquid_water_content_volumetric(layer);
         return water_content_layers;
      }
      // This is a valid interface method because it uses only interface methods.
   virtual float64 get_reference_water_content(nat8  sublayer)             const = 0;
   virtual float64 get_air_entry_pot
      (nat8 layer,bool consider_ice_content,bool FC_PWP_based)             const = 0; //140610_990321
   virtual float64 get_real_wilt_point(nat8 layer)                         const = 0; //140610
   virtual float64* ref_plant_avail_water()                                      = 0; //140610
   //_2008-01-27________________________________________________________________
 public: // soil freezing accessors
   // Derived classes may return 0 in the case of no soil freezing simulation.
   virtual float64 get_ice_content_volumetric                ( nat8 layer) const = 0;  //140822 was get_ice_content
   virtual float64 get_ice_content_volumetric_yesterday      ( nat8 layer) const = 0;  //140822 was get_ice_content_yesterday
   virtual bool is_frozen                                    ( nat8 layer) const = 0;
 protected: friend class Soil_freezing_profile_jumakis; // set state accessors
 public: // set state accessors
   virtual float64 initialize_moisture                                           //170320
      (nat8 layer
      ,Moisture_characterization moisture
      ,float64 water_content_initial)                           modification_=0;
   virtual float64 set_water_content_volumetric_layer
      (nat8 layer, float64 new_water_content)                   modification_=0;
   virtual float64 change_liquid_water_content_by_volumetric
      (nat8 layer, float64 change_WC)                           modification_=0;
      // Pass a positive value to increase the WC and negative to decrease.
      // Returns the new water content.
      // Note that change_WC is probably always liquid so this will work for either liquid or total water basis.
   virtual float64 set_plant_avail_water       (nat8 layer, float64 PAW)      modification_=0; //140610
   virtual float64 set_real_wilt_point         (nat8 layer, float64 real_WP)  modification_=0; //140610
   virtual float64 set_reference_water_content (nat8 layer, float64 ref_WC)   modification_=0; //140610
 public: // processes
   virtual float64 extract_water_mm(float64 water_uptake_mm[] , nat8 start_layer) = 0;//140624
      // takes values in mm and returns mm
   virtual float64 extract_water(float64 water_uptake_m[] , nat8 start_layer) = 0;
      // takes values in m and returns m
   // These functions should remove the specified soil water (in depth) from each of the layers.
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
 public:  // calculators
   virtual float64 calc_water_potential                                          //140610
      ( nat8 layer,bool consider_ice,bool FC_PWP_based)                    const = 0;
 public:  // process daily
   virtual bool start_day()                                        modification_ = 0;
   virtual void update_liquid_and_ice_water_content()              modification_ = 0;
   virtual void record_water_content_for_hour(CORN::Hour hour)                  =0; //140527
      // this is just for output do nothing by defaut
   virtual Soil_hydrology_interface *copy(float32 fraction)                const=0; //140610
   virtual void expand_last_layer_for_boundary_conditions
      ( nat8 number_layers, nat8 number_expanded_layers)           modification_=0; //140610
   RENDER_INSPECTORS_DECLARATION_PURE;                                           //150929
};
//______________________________________________________________________________
#endif
