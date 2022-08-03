#include "soil/hydraulic_properties.h"
#include "soil/soil_interface.h"
#include "corn/math/compare.hpp"
#include "soil/soil_param_class.h"
#include "common/physics/standard_constants.h"
//______________________________________________________________________________
Soil_hydraulic_properties::Soil_hydraulic_properties(const Soil_layers_interface &_layers)
: layers(_layers)
{  clear();                                                                      //061108
}
//_2005-12-04_____________________________________________________constructor__/
Soil_hydraulic_properties::Soil_hydraulic_properties(const Soil_hydraulic_properties &copy_from,const Soil_layers_interface    &_layers)
: layers(_layers)
{  clear();                                                                      //061108
   copy(copy_from);
}
//_2005-12-04________________________________________________copy_constructor__/
Soil_hydraulic_properties::Soil_hydraulic_properties
(const Soil_layers_interface &_layers
,const Soil_parameters_class &parameters)
: layers(_layers)
{
   clear();
   for (nat8 layer=1 ; layer <= layers.get_number_layers(); layer ++)
   {
      set_field_capacity_volumetric                (layer,parameters.get_horizon_field_capacity_volumetric       (layer));
      set_permanent_wilt_point_volumetric          (layer,parameters.get_horizon_permanent_wilt_point_volumetric (layer));
      set_water_pot_at_FC                          (layer,parameters.get_horizon_water_pot_at_FC                 (layer));
         // I dont yet have accessor method for water_pot_at_FC
      set_saturation_water_content_volumetric      (layer,parameters.get_horizon_saturation_WC                   (layer));
      set_Campbell_b_parameter                     (layer,parameters.get_horizon_Campbell_b                      (layer));
      set_air_entry_potential_parameter            (layer,parameters.get_horizon_air_entry_pot                   (layer));
      set_Campbell_b_FC_PWP_based                  (layer,parameters.get_horizon_Campbell_b                      (layer));
      set_air_entry_potential_FC_PWP_based         (layer,parameters.get_horizon_air_entry_pot                   (layer));
      set_bypass_coef                              (layer,parameters.get_horizon_bypass_coef                     (layer));
      // saturated_hydraulic_conductivity must be set after air_entry_potential
      set_saturated_hydraulic_conductivity_m_d     (layer,parameters.get_horizon_sat_hydraul_cond_m_d            (layer));
   }
}
//_2015-09-26__________________________________________________________________/
void Soil_hydraulic_properties::clear()
{
#ifdef _Windows
   clear_layer_array64(saturation_water_content_volumetric);
   clear_layer_array64(field_capacity_volumetric);
   clear_layer_array64(permanent_wilt_point_volumetric);
   clear_layer_array64(saturated_hydraulic_conductivity_kg_s_m3);  // kg s/m3
   clear_layer_array64(Campbell_b_parameter);
   clear_layer_array64(air_entry_pot_parameter);       // air entry potential J/kg }
   clear_layer_array64(Campbell_b_FC_PWP_based);       // Used for Cascade model
   clear_layer_array64(air_entry_pot_FC_PWP_based);    // air entry potential J/kg }
   clear_layer_array64(unsaturated_conductivity_function_slope);
   clear_layer_array64(bypass_coef);                                             //110825
   clear_layer_array64(water_pot_at_FC);                                         //130228
#else
// CODE::Blocks is not finding clear_layer_array64
#endif
   unsaturated_conductivity_function_slope_valid = false;                        //080118
}
//_2005-12-04___________________________________________________________clear__/
void Soil_hydraulic_properties
::copy(const Soil_hydraulic_properties &copy_from)
{  // Copy constructor
   layers.copy_array64(saturation_water_content_volumetric     ,copy_from.saturation_water_content_volumetric);
   layers.copy_array64(field_capacity_volumetric               ,copy_from.field_capacity_volumetric);
   layers.copy_array64(permanent_wilt_point_volumetric         ,copy_from.permanent_wilt_point_volumetric);
   layers.copy_array64(saturated_hydraulic_conductivity_kg_s_m3,copy_from.saturated_hydraulic_conductivity_kg_s_m3);
   layers.copy_array64(Campbell_b_parameter                    ,copy_from.Campbell_b_parameter);
   layers.copy_array64(air_entry_pot_parameter                 ,copy_from.air_entry_pot_parameter);
   layers.copy_array64(Campbell_b_FC_PWP_based                 ,copy_from.Campbell_b_FC_PWP_based);
   layers.copy_array64(air_entry_pot_FC_PWP_based              ,copy_from.air_entry_pot_FC_PWP_based);
   layers.copy_array64(unsaturated_conductivity_function_slope ,copy_from.unsaturated_conductivity_function_slope);
   layers.copy_array64(water_pot_at_FC                         ,copy_from.water_pot_at_FC);
   unsaturated_conductivity_function_slope_valid =              copy_from.unsaturated_conductivity_function_slope_valid;   //080118
}
//_2005-12-04____________________________________________________________copy__/
void Soil_hydraulic_properties
::expand_last_layer_for_boundary_conditions
(nat8 number_layers,nat8 number_expanded_layers)                      modification_
{
   for (nat8 extend_layer = number_layers+1; extend_layer <= number_expanded_layers; extend_layer++) //080211
   {
      saturation_water_content_volumetric     [extend_layer]=saturation_water_content_volumetric      [number_layers];
      field_capacity_volumetric               [extend_layer]=field_capacity_volumetric                [number_layers];
      permanent_wilt_point_volumetric         [extend_layer]=permanent_wilt_point_volumetric          [number_layers];
      saturated_hydraulic_conductivity_kg_s_m3[extend_layer]=saturated_hydraulic_conductivity_kg_s_m3 [number_layers];
      Campbell_b_parameter                    [extend_layer]=Campbell_b_parameter                     [number_layers];
      air_entry_pot_parameter                 [extend_layer]=air_entry_pot_parameter                  [number_layers];
      Campbell_b_FC_PWP_based                 [extend_layer]=Campbell_b_FC_PWP_based                  [number_layers];
      air_entry_pot_FC_PWP_based              [extend_layer]=air_entry_pot_FC_PWP_based               [number_layers];
      unsaturated_conductivity_function_slope [extend_layer]=unsaturated_conductivity_function_slope  [number_layers];
      water_pot_at_FC                         [extend_layer]=water_pot_at_FC                          [number_layers]; //130228
   }
}
//_2008-13-30_______________________expand_last_layer_for_boundary_conditions__/
float64 Soil_hydraulic_properties
::get_field_capacity_volumetric(nat8 layer)                                const
{ return field_capacity_volumetric[layer];}
//_2005-12-04___________________________________get_field_capacity_volumetric__/
float64 Soil_hydraulic_properties
::set_field_capacity_volumetric(nat8 layer,float64 _field_capacity)
{  field_capacity_volumetric[layer] = _field_capacity;
   return _field_capacity;
}
//_2005-12-04___________________________________set_field_capacity_volumetric__/
float64 Soil_hydraulic_properties
::get_permanent_wilt_point_volumetric(nat8 layer)                          const
   { return permanent_wilt_point_volumetric[layer];}
//_2005-12-04_____________________________get_permanent_wilt_point_volumetric__/
float64 Soil_hydraulic_properties
::get_water_pot_at_FC(nat8 layer)                                          const
{  return water_pot_at_FC[layer];}
//_2013-02-28___________________________________________________________________
const float64 *Soil_hydraulic_properties::ref_soil_water_pot_at_FC()       const
{  return water_pot_at_FC; }
//_2017-05-01___________________________________________________________________
float64 Soil_hydraulic_properties
::set_permanent_wilt_point_volumetric(nat8 layer,float64 _perm_wilt_point_volumetric)
{  permanent_wilt_point_volumetric[layer] = _perm_wilt_point_volumetric;
   return _perm_wilt_point_volumetric;
}
//________________________________________set_permanent_wilt_point_volumetric__/
float64 Soil_hydraulic_properties
::set_water_pot_at_FC(nat8 layer,float64 _water_pot_at_FC)                       //130228
{  water_pot_at_FC[layer] = _water_pot_at_FC;
   return _water_pot_at_FC;
}
//_2013-02-28___________________________________________________________________
float64 Soil_hydraulic_properties
::get_sat_hydraul_cond_kg_s_m3(nat8 layer)                                 const  // rename to get_saturated_hydraulaulic_conductivity_kg_s_m3
{  return saturated_hydraulic_conductivity_kg_s_m3[layer];
}
//_______________________________________________get_sat_hydraul_cond_kg_s_m3__/
float64 Soil_hydraulic_properties
::set_saturated_hydraulic_conductivity_kg_s_m3
(nat8 layer,float64 _sat_hydraul_cond_kg_s_m3)
{  saturated_hydraulic_conductivity_kg_s_m3[layer] = _sat_hydraul_cond_kg_s_m3;
   return _sat_hydraul_cond_kg_s_m3;
}
//_______________________________set_saturated_hydraulic_conductivity_kg_s_m3__/
float64 Soil_hydraulic_properties
::get_Campbell_b(nat8 layer,bool FC_PWP_based)                            const
{ return
       FC_PWP_based ? Campbell_b_FC_PWP_based[layer] :
       Campbell_b_parameter[layer];
}
//_____________________________________________________________get_Campbell_b__/
float64 Soil_hydraulic_properties
::get_unsaturated_conductivity_function_slope(nat8 layer)                 const
{
   if (!unsaturated_conductivity_function_slope_valid)
   {  for (nat8 l = 0; l <= MAX_soil_layers; l++)
      {  float64 b = get_Campbell_b(l,false);
         unsaturated_conductivity_function_slope[l]
         =  (CORN::is_approximately<float64>(b,0.0,0.0000001))
         ? 0.0
         : 2.0 + 3.0 / b;
      }
      unsaturated_conductivity_function_slope_valid = true;
   }
   return unsaturated_conductivity_function_slope[layer];
}
//_2008-01-18_____________________get_unsaturated_conductivity_function_slope__/
float64 Soil_hydraulic_properties
::set_Campbell_b_parameter(nat8 layer,float64 _Campbell_b)            modification_
{  Campbell_b_parameter[layer] = _Campbell_b;
   unsaturated_conductivity_function_slope_valid = false;                        //080118
   return _Campbell_b;
}
//___________________________________________________set_Campbell_b_parameter__/
float64 Soil_hydraulic_properties
::get_air_entry_potential(nat8 layer,bool FC_PWP_based)                   const
{ return
   FC_PWP_based ? air_entry_pot_FC_PWP_based[layer] :
   air_entry_pot_parameter[layer];
}
//_1999-03-21P________________________________________get_air_entry_potential__/
float64 Soil_hydraulic_properties
::set_air_entry_potential_parameter
(nat8 layer,float64 _air_entry_pot)
{  air_entry_pot_parameter[layer] = _air_entry_pot;
   return _air_entry_pot;
}
//__________________________________________set_air_entry_potential_parameter__/
float64 Soil_hydraulic_properties
::set_Campbell_b_FC_PWP_based
(nat8 layer,float64 _Campbell_b)
{  Campbell_b_FC_PWP_based[layer] = _Campbell_b;
   unsaturated_conductivity_function_slope_valid = false;                        //080118
   return _Campbell_b;
}
//________________________________________________set_Campbell_b_FC_PWP_based__/
float64 Soil_hydraulic_properties
::set_air_entry_potential_FC_PWP_based
(nat8 layer,float64 _air_entry_pot)
{  air_entry_pot_FC_PWP_based[layer] = _air_entry_pot;
   return _air_entry_pot;
}
//_______________________________________set_air_entry_potential_FC_PWP_based__/
float64 Soil_hydraulic_properties
::change_bulk_density_g_cm3(nat8 layer,float64 _bulk_density_g_cm3)
{  float64 sat_WC = calc_saturation_water_content_volumetric((float64) _bulk_density_g_cm3);
   saturation_water_content_volumetric[layer] = sat_WC;
   return (float64) _bulk_density_g_cm3;
}
//_2005-12-04___________________________________________________________________
float64 Soil_hydraulic_properties
::calc_saturation_water_content_volumetric(float64 _bulk_density_g_cm3)    const
{  return 1.0 - _bulk_density_g_cm3 / 2.65; }                                   //031122
//_2005-12-04___________________________________________________________________
float64 Soil_hydraulic_properties
::set_saturation_water_content_volumetric
(nat8 layer,float64 _saturation_volumetric)
{    saturation_water_content_volumetric[layer] = _saturation_volumetric;        //031122
     return  _saturation_volumetric;
}
//_2005-12-04__________________________________________________________________
float64 Soil_hydraulic_properties
::get_saturation_water_content_volumetric
(nat8 layer
,float64 current_ice_water_content)                                        const //140822
{  float64 sat_WC = saturation_water_content_volumetric[layer] - current_ice_water_content; //031122
   return sat_WC; // saturation_water_content_volumetric[layer] ; //
      // This is actually constant but needs to be updated when layers are eroded
      // eventually put this in an array.
}
//_2005-12-04_________________________get_saturation_water_content_volumetric__/
float64 Soil_hydraulic_properties
::set_bypass_coef(nat8 layer,float64 _bypass_coef)
{  bypass_coef[layer] = _bypass_coef;
   return (float64) _bypass_coef;
}
//_2007-01-17_________________________________________________set_bypass_coef__/
float64 Soil_hydraulic_properties::get_bypass_coef(nat8 layer)            const
{  return (float64) bypass_coef[layer];
}
//_2007-01-17_________________________________________________get_bypass_coef__/
float64 Soil_hydraulic_properties::set_saturated_hydraulic_conductivity_m_d
(nat8 layer,float64 _sat_hydraul_cond_m_day)
{
   bool has_air_entry_pot = !CORN::is_approximately<float64>(air_entry_pot_parameter[layer],0.0,0.000001);
   if (!has_air_entry_pot)
   {  std::cerr << "trying to set_saturated_hydraulic_conductivity_m_d before air entry potential" << std::endl;
   }
   float64 sat_hydraul_cond_kg_s_m3 =                                                                                                                          //051205
         is_approximately(_sat_hydraul_cond_m_day,0.0,0.000001)                                                                                              //980526
         ? 1.0e-3 / CORN_sqr(air_entry_pot_parameter[layer]) //saturated hydraulic conductivity, Kgsec/m3                                                       //990331
         : _sat_hydraul_cond_m_day
            / (standard_gravity * 86.4);
         // convert to flux unit?
   return set_saturated_hydraulic_conductivity_kg_s_m3(layer,sat_hydraul_cond_kg_s_m3);
}
//_2015-09-26__________________________________________________________________/
