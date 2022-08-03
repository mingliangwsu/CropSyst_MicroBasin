//______________________________________________________________________________
#include "soil/hydrology_finite_diff.h"
#include "soil/soil_interface.h"
#include "corn/math/compare.hpp"
#include <math.h>
#ifndef moremathH
#  include "corn/math/moremath.h"
   using namespace std;
#endif
//_____________________________________________________________________________/
void Soil_hydrology_finite_difference::initialize(float64 *_node_depth)
{  node_depth = _node_depth;                                                     //080211
   update_soil_volume
      (soil_layers_ref.get_number_layers()+2
      ,soil_layers_ref.get_number_layers()+3);
}
//_2008-02-11__2006-05-08__________________________________________initialize__/
float64 Soil_hydrology_finite_difference
::calc_water_depth_profile                                                       //130930 was get_water_depth_profile
(bool liquid_and_ice)                                                      const
{  float64 WD_profile = 0.0;
   for (nat8 i = 1 ; i <= soil_layers_ref.get_number_layers(); i++)             //980724
   {  float64 wc_sl = liquid_and_ice
            ? get_water_plus_ice_content_volumetric(i)                           //990316
            : get_liquid_water_content_volumetric(i);                            //990316
      float64 WD_layer = wc_sl * soil_layers_ref.get_thickness_m(i);
      //080319 Warning this may be wrong, may need to be:
      //080319  WD_layer =  ((wu(i) * V_Upper(i) + wl(i) * V_Lower(i)) / (V_Upper(i) + V_Lower(i))) * dz(i) * wd;
      WD_profile += WD_layer;
   }
   return WD_profile;
}
//_2008-01-21_________________________________________get_water_depth_profile__/
float64 Soil_hydrology_finite_difference
::get_liquid_water_depth_profile()                                         const
{  float64 WD_profile = 0;                                              //  IWC = 0
   for (nat8 layer = 1; layer <=soil_layers_ref.get_number_uninundated_layers(); layer ++)          //  For i = 1 To m 'initial water depth for all effective soil layers
   {  WD_profile += calc_liquid_water_content_layer           //  IWC = IWC + ((wu(i) * V_Upper(i) + wl(i) * V_Lower(i)) / (V_Upper(i) + V_Lower(i))) * dz(i) * wd
         (layer
         ,get_upper_water_content_liquid(layer)
         ,get_lower_water_content_liquid(layer))
            * soil_layers_ref.get_thickness_m(layer);                           //080314
   }                                                                //  Next i
   return WD_profile;
}
//_2008-01-21__________________________________get_liquid_water_depth_profile__/
float64 Soil_hydrology_finite_difference
::extract_water(soil_layer_array64(amount_to_extract_m),nat8 start_layer)
{  // Extraction could be water uptake or evaporation
   float64 act_total_amount_to_extract = 0.0;
   nat8 num_sublayers = soil_layers_ref.get_number_layers();
   for (nat8 layer = 1; layer <= num_sublayers; layer++)
   {
      float64 liquid_WC = get_liquid_water_content_volumetric(layer);            //070813
      float64 extract_volumetric = amount_to_extract_m[layer] / soil_layers_ref.get_thickness_m(layer);
      float64 act_extract_volumetric = std::min<float64>(liquid_WC,extract_volumetric);
      if (act_extract_volumetric > 0)                                            //070817
      {  float64 act_extract_depth =  act_extract_volumetric * soil_layers_ref.get_thickness_m(layer);
         act_total_amount_to_extract += act_extract_depth;
         change_liquid_water_content_by_volumetric(layer, - act_extract_volumetric); // Negative for extraction   //070814
      }
   }
   return act_total_amount_to_extract;
}
//_2001-05-22___________________________________________________extract_water__/
Soil_hydrology_finite_difference::Soil_hydrology_finite_difference
      (const Soil_layers_interface                 &_soil_layers_ref
      , const Soil_hydraulic_properties_interface  &_hydraulic_properties_ref
      ,const Soil_structure_interface              &_soil_structure)
: Soil_hydrology_abstract(_soil_layers_ref,_hydraulic_properties_ref,_soil_structure)
{  for (nat8 layer = 0; layer <= MAX_soil_sublayers; layer ++)
   {  upper_water_content_liquid[layer] = 0;
      lower_water_content_liquid[layer] = 0;
      soil_volume_node[layer] =0;   // These must be updated daily (actually only when soil layering changes I.e. erosion and may be dust mulch)
      upper_soil_volume[layer]=0 ; // RLN This name does not seem reasonable.
      lower_soil_volume[layer]=0 ;
   }
   // update_soil_volume();  Would like to do this here, but soil depth has not been computed yet
}
//________________________________Soil_hydrology_finite_difference_constructor_/
Soil_hydrology_finite_difference::Soil_hydrology_finite_difference
(const Soil_hydrology_finite_difference &copy_from
,float32 fraction)
:Soil_hydrology_abstract(copy_from,fraction)
{
   copy_layer_array64(upper_water_content_liquid     ,copy_from.upper_water_content_liquid);
   copy_layer_array64(lower_water_content_liquid     ,copy_from.lower_water_content_liquid );
   copy_layer_array64(soil_volume_node               ,copy_from.soil_volume_node);
   copy_layer_array64(upper_soil_volume              ,copy_from.upper_soil_volume);
   copy_layer_array64(lower_soil_volume              ,copy_from.lower_soil_volume);
/*140610 Warning, not sure if these are intensive or extensive to apply the fraction
   for (nat8 layer = 0; layer <= MAX_soil_sublayers; layer ++)
   {
      soil_volume_node[layer] *= fraction;
      upper_soil_volume[layer]*= fraction;
      lower_soil_volume[layer]*= fraction;
   }
*/
}
//_2014-06-09________________Soil_hydrology_finite_difference_copy_constructor_/
float64 Soil_hydrology_finite_difference
::set_upper_and_lower_water_content_liquid
(nat8 layer,float64 new_upper_WC,float64 new_lower_WC) modification_
{  upper_water_content_liquid[layer] = new_upper_WC;
   lower_water_content_liquid[layer] = new_lower_WC;
   float liquid_WC =((new_upper_WC + new_lower_WC ) / 2.0);
   invalidate();                                                                 //130930
   return liquid_WC;
};
//_2007-10-10________________________set_upper_and_lower_water_content_liquid__/
float64 Soil_hydrology_finite_difference
::calc_liquid_water_content_layer
(nat8 layer
,float64 upper_water_content_layer
,float64 lower_water_content_layer)                                        const
{  float64 upper_soil_volume_layer = upper_soil_volume[layer];
   float64 lower_soil_volume_layer = lower_soil_volume[layer];
   float64 denominator =  (upper_soil_volume_layer + lower_soil_volume_layer);
   float64 liquid_WC_layer = (denominator > 0.0000001)
      ? (( upper_water_content_layer * upper_soil_volume_layer
         + lower_water_content_layer * lower_soil_volume_layer)
         / denominator )
      : 0.0;
    return liquid_WC_layer;
}
//_2008-01-31__2007-08-30_____________________calc_liquid_water_content_layer__/
float64 Soil_hydrology_finite_difference
::get_liquid_water_content_volumetric(nat8 layer)                          const
{  return calc_liquid_water_content_layer
      (layer
      ,upper_water_content_liquid[layer]
      ,lower_water_content_liquid[layer]);
}
//_2006-05-08_____________________________get_liquid_water_content_volumetric__/
bool Soil_hydrology_finite_difference
::set_upper_and_lower_liquid_water_content_volumetric(nat8 layer, float64 layer_liquid_WC)
{  upper_water_content_liquid[layer] = layer_liquid_WC;
   lower_water_content_liquid[layer] = layer_liquid_WC;
   invalidate();                                                                 //130930
   return true;
}
//________________________set_upper_and_lower_liquid_water_content_volumetric__/
float64 Soil_hydrology_finite_difference::set_water_content_volumetric_layer     //010522
(nat8 layer, float64 new_water_content)
{  upper_water_content_liquid[layer] = new_water_content;
   lower_water_content_liquid[layer] = new_water_content;
   ice_water_content[layer] = 0;
//Note that this should also clear ice_content.
// I am pretty sure this is called for initialization only
// but I need to check, if it is also called by reinitialization
// and/or recalibration, then I should invalidate freezing profile.
   invalidate();                                                                 //130930
   return new_water_content;
}
//_2007-08-27_____________set_upper_and_lower_liquid_water_content_volumetric__/
float64 Soil_hydrology_finite_difference
::change_liquid_water_content_by_volumetric(nat8 layer, float64 change_WC) modification_
{  upper_water_content_liquid[layer] += change_WC;
   lower_water_content_liquid[layer] += change_WC;
   invalidate();                                                                 //130930
   return get_liquid_water_content_volumetric(layer);
}
//_2008-01-27__2007-08-15___________change_liquid_water_content_by_volumetric__/
float64 Soil_hydrology_finite_difference
::get_upper_water_content_liquid(nat8 layer)                               const
{  return upper_water_content_liquid[layer];
}
//_2007-10-10__________________________________get_upper_water_content_liquid__/
float64 Soil_hydrology_finite_difference
::get_lower_water_content_liquid(nat8 layer)                               const
{  return lower_water_content_liquid[layer];
}
//_2007-10-10__________________________________get_lower_water_content_liquid__/
float64 Soil_hydrology_finite_difference
::set_upper_water_content_liquid(nat8 layer,float64 new_WC) modification_
{  return upper_water_content_liquid[layer] = new_WC;
}
//_2009-01-07__________________________________set_upper_water_content_liquid__/
float64 Soil_hydrology_finite_difference
::set_lower_water_content_liquid(nat8 layer,float64 new_WC) modification_
{  return lower_water_content_liquid[layer] = new_WC;
}
//_2009-01-07__________________________________set_lower_water_content_liquid__/
bool Soil_hydrology_finite_difference
::update_soil_volume                                                             //080211
(float64 number_expanded_layers
,float64 number_extended_nodes)                                    modification_
{  // Note that this only really needs to be called whenever the soil layering changes
   for (nat8 node = 1; node <= number_extended_nodes-1; node++)
   {  nat8 layer = node;
      float64 depth_next = node_depth[node+1];
      float64 depth_prev= (layer > 1)
         ? node_depth[node-1]
         : 0.0;
      float64 node_domain_thickness =
         ( depth_next
          -depth_prev) / 2.0;
      soil_volume_node[node]  = water_density * node_domain_thickness;// VB: v(i) = wd * z(i + 1) - z(i - 1)) / 2.0;
      // Domain thickness for last node at the bottom of the soil profile           //080131
   };
   for (nat8 layer = 1; layer <=
      #ifdef MICROBASIN_VERSION
      number_extended_nodes                                                      //140604
      #else
      number_expanded_layers
      #endif
      ; layer++)
   {  // Determine thickness of upper and lower element in each soil layer
      float64 soil_volume_half_layer
         = water_density * soil_layers_ref.get_thickness_m(layer) / 2.0;
      upper_soil_volume[layer]= soil_volume_half_layer;                          // VB:  V_Upper(i) = wd * dz(i) / 2
      lower_soil_volume[layer]= soil_volume_half_layer;                          // VB:  V_Lower(i) = wd * dz(i) / 2
   };
   return true;
}
//_2008-01-30______________________________________________update_soil_volume__/
bool Soil_hydrology_finite_difference
::get_liquid_water_depth_nodes
(soil_node_array64(water_depth_nodal),nat8 num_nodes_eff)                  const
{  float64 thickness_prev_layer = 0.0;                                           //080114
   for (nat8 node = 1; node <= num_nodes_eff ; node++)
   {  nat8 layer = node;
      // Note that we should have setup an extra layer with expand_last_layer_for_boundary_conditions
      float64 thickness_layer = soil_layers_ref.get_thickness_m(layer); // Node corresponds to the layers here.  //080114
      water_depth_nodal[node]
               = (upper_water_content_liquid[layer] * thickness_layer / 2.0)           //080114
               + (lower_water_content_liquid[layer - 1] * thickness_prev_layer / 2.0); //080114
      thickness_prev_layer = thickness_layer;                                          //080114
   }
   return true;
}
//_2008-02-01____________________________________get_liquid_water_depth_nodes__/
void Soil_hydrology_finite_difference::expand_last_layer_for_boundary_conditions
(nat8 number_layers,nat8 number_expanded_layers)                             modification_
{  Soil_hydrology_abstract::expand_last_layer_for_boundary_conditions(number_layers,number_expanded_layers);
   for (nat8 extend_layer = number_layers+1; extend_layer <= number_expanded_layers; extend_layer++)
   {  soil_volume_node           [extend_layer] = soil_volume_node            [number_layers];
      upper_soil_volume          [extend_layer] = upper_soil_volume           [number_layers];
      lower_soil_volume          [extend_layer] = lower_soil_volume           [number_layers];
      upper_water_content_liquid [extend_layer] = upper_water_content_liquid  [number_layers];
      lower_water_content_liquid [extend_layer] = lower_water_content_liquid  [number_layers];
   }
   #ifdef MICROBASIN_VERSION
   soil_volume_node           [number_expanded_layers+1] = soil_volume_node            [number_layers];
   upper_soil_volume          [number_expanded_layers+1] = upper_soil_volume           [number_layers];
   upper_water_content_liquid [number_expanded_layers+1] = upper_water_content_liquid  [number_layers]; //140604
   #endif
   invalidate();                                                                 //130930
}
//_2008-02-12_______________________expand_last_layer_for_boundary_conditions__/
float64 Soil_hydrology_finite_difference::calc_water_potential_with_respect_to_layer
(float64 water_content_volumetric      // The WC is passed because it could be upper or lower or in the case of evaporation, the evaporation of the layer
,nat8 layer)                                                  const
{  
   float64 air_entry_pot   = hydraulic_properties_ref.get_air_entry_potential(layer,false);
   float64 Campbell_b      = hydraulic_properties_ref.get_Campbell_b(layer,false);
   float64 sat_water_cont  = hydraulic_properties_ref.get_saturation_water_content_volumetric(layer,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822);
   float64 water_pot =
      (  CORN::is_approximately<float64>(water_content_volumetric,0.0,0.00000001)
      || CORN::is_approximately<float64>(sat_water_cont,0.0,0.00000001))
      ? 0.0  // Most likely due to freezing conditions.
      : air_entry_pot * pow((water_content_volumetric / sat_water_cont) , (-Campbell_b));
   //RLN : While this is similar to the Soil_base::waterpotential
   //This is used for xxx soil layer in F.D. calc_act_evaporation_mm
   //This does not account for Ice content (Not sure if it should).
   return water_pot;
} //080118 Checked against VB version (Infiltration_Clean_010908)
//_2009-01-07______________________calc_water_potential_with_respect_to_layer__/

