#include "crop/crop_root.h"
#include "soil/soil_interface.h"
#include "crop/thermal_time.h"
#include "crop/crop_param.h"
#include <math.h>
#include "corn/math/compare.hpp"
#include "corn/measure/measures.h"

#include "CS_suite/observation/CS_inspector.h"
#include "csvc.h"
//#define DEBUG_ROOT
#include <fstream>
#ifdef DEBUG_ROOT
extern CORN::Date simulation_today;
std::ofstream roots_txt("roots.txt");
#endif
namespace CropSyst {
//______________________________________________________________________________
Crop_root_common::Crop_root_common()
: root_length(0)
, biomass(0)
{}
//_Crop_root_common:constructor_____________________________________2013-09-09_/
Crop_root_dormant::Crop_root_dormant
(float64 _dormant_root_length
,float64 _biomass
,soil_layer_array64(_biomass_by_layer))
{  biomass     = _biomass;                                                       //130909
   root_length = _dormant_root_length;                                           //130909
   copy_layer_array64(biomass_by_layer,_biomass_by_layer);
}
//_Crop_root_dormant:constructor_______________________________________________/
Crop_root_vital::Crop_root_vital
(const Crop_parameters_struct::Root       &_parameters
,const Crop_parameters_struct::Phenology  &_phenology_parameters                 //080722
,const Thermal_time_immutable             &_thermal_time                         //151106
,const Soil_layers_interface              &_soil_layers
,float32  _initial_root_length) // This is used by  calc_max_N_update_per_unit_root_length()

:soil_layers         (_soil_layers)
,thermal_time        (_thermal_time)                                             //061212
,parameters          (_parameters)                                               //061212
,phenology_parameters(_phenology_parameters)                                     //080733
,apparent_root_depth              (_initial_root_length)
,growth_biomass                  (0)                                             //070130
,normalized_thermal_time_today   (0)                                             //061212
,normalized_thermal_time_yesterday(0)                                            //061212
,root_length_unstressed_today    (_initial_root_length)
,root_length_unstressed_yesterday(_initial_root_length)
,biomass_yesterday               (0)                                             //070410
,rooting_layer       (2)
,start_rooting_depth             (_soil_layers.get_thickness_m(1) )
,total_root_lengths              (0.000001)                                      //150601
//180727 abandoned ,root_distribution_unadjust       (30,10)                                         //180727
{
   root_length                     =_initial_root_length;                        //130909
   for (short int sublayer = 0; sublayer <= MAX_soil_sublayers; sublayer++)
   {  root_density            [sublayer] = 0.0;
      total_fract_root_length [sublayer] = 0.0;                                  //010322
      root_lengths            [sublayer] = 0.0;                                  //061129
   }
}
//_Crop_root_vital:constructor__________________________________________________
void Crop_root_vital::initialize(float64 root_length_to_initialize_to)
{  for (short int sublayer = 0; sublayer <= MAX_soil_sublayers; sublayer++)
   {  root_density            [sublayer] = 0.0;
      total_fract_root_length [sublayer] = 0.0;                                  //010322
      root_lengths            [sublayer] = 0.0;                                  //061129
   }
}
//_initialize__________________________________________________________________/
float64 Crop_root_vital::update_root_length
(float64 stress_factor /*Currently only the water stress factor!*/ )
{  // after end of LAI development no more root growth
   float64 accum_thermal_time = thermal_time.get_accum_degree_days(false);
   if (accum_thermal_time > phenology_parameters.culmination.root_depth) return root_length;
   // no root growth until emergence
#ifdef OBSOLETE
2010?
// In the V.B. version the stress factor is based on the potential cumulative biomass for unstressed crop
// in the C++ version this value is not available (sort of is  when N model is available.
// Claudio says just to use the water_stress_factor
   float64 stress_factor =
      (potential_cumulative_biomass > 0)
      ? pow((current_cumulative_biomass / potential_cumulative_biomass),(parameters.sensitivity_to_water_stress))
      : 1.0;
#endif
   // Calculate length depth gain today
   // When we reach deg days of max root depth the normalized_thermal_time_today will be 1.
   normalized_thermal_time_today
      = (accum_thermal_time - phenology_parameters.initiation.emergence)
      / (phenology_parameters.culmination.root_depth                             //150913
        -phenology_parameters.initiation.emergence);                             //070321
   float64 max_seasonal_root_length_gain
      = (parameters.max_depth - start_rooting_depth)
        - cm_to_m(parameters.length_at_emergence_cm);
   root_length_unstressed_today = cm_to_m(parameters.length_at_emergence_cm)
      + max_seasonal_root_length_gain * normalized_thermal_time_today;
   float64 stress_adjustment =
      (stress_factor < 0.000001) ? 1.0 :                                         //131011
      pow(stress_factor,(float64)parameters.sensitivity_to_water_stress);        //121004
   float64  root_depth_gain // Today's growth
      = (root_length_unstressed_today - root_length_unstressed_yesterday)
       * stress_adjustment;
   if (root_depth_gain < 0.0)                                                    //070105
      root_depth_gain = 0;                                                       //070105
   root_length += root_depth_gain;
   root_length = std::min<float64>(root_length,parameters.max_depth - start_rooting_depth); //070321
   return root_length;
}
//_update_root_length_______________________________________________2006-12-12_/
bool Crop_root_vital::start_day()
{  normalized_thermal_time_yesterday = normalized_thermal_time_today;
   root_length_unstressed_yesterday  = root_length_unstressed_today;
   biomass_yesterday = biomass;                                                  //070130
   return true;
}
//_start_day________________________________________________________2006-12-12_/
float64 Crop_root_vital::update_root_depth(bool terminate_pending)
{  if (!terminate_pending)
   {  // When terminate has been started (process biomatter fate) the root_length will have been reset
      apparent_root_depth = (root_length > 0.0)                                  //981208
      ? root_length + start_rooting_depth                                        //981208
      : 0.0;                                                                     //981208
      float64 limit_to_depth =soil_layers.get_depth_profile_m();
      if (limit_to_depth > 0.00001)          // Could be 0 if dummy soil         //981208
         apparent_root_depth = std::min<float64>(apparent_root_depth, limit_to_depth );   //981208
   }
   return apparent_root_depth;                                                   //981208
}
//_update_root_depth________________________________________________1998-10-23_/
float64 Crop_root_vital::update_root_densities
(/*180726 float64 density_area[]*/)
{
   //180726clear_layer_array64(L);                                //030722
   clear_layer_array64(root_distribution_unadjust); root_distr_unadjust_sum=0;   //180727
   //180727 root_distribution_unadjust.clear();                                  //180726
   //L should be renamed as unadjusted_root_distribution
   //soil_sublayer_array_64(root_density_at_layer_bottom); clear_layer_array64(root_density_at_layer_bottom); //030722
   float64 depth_top_soil_layer = 0;                                             //030722
   float64 density_area_sum = 0;                                                 //030722
   float64 max_root_length = (parameters.max_depth - start_rooting_depth);       //030722

   max_root_density = parameters.surface_density * root_length / max_root_length; //030722

   //L[rooting_layer-1] = -(1.0 - exp(para7meters.density_distribution_curvature * ( root_length - depth_top_soil_layer)));   //030722
   //root_density_at_layer_bottom[rooting_layer-1] = max_root_density;             //030722
   nat8  number_effective_layers = soil_layers.get_number_uninundated_layers();  //061208
   //180726 cleared by clear() L_sum = 0.0;
   for (nat8  layer = rooting_layer; layer <= number_effective_layers; layer++)  //030722
   {  float64 layer_thickness = soil_layers.get_thickness_m(layer);              //061208
      float64 density_distribution_curvature = parameters.density_distribution_curvature; //061212
      float64 exp_term = exp(density_distribution_curvature * (root_length - depth_top_soil_layer) / parameters.surface_density); //030722

      float64 root_distr_unadjust_layer = CORN::must_be_0_or_greater<float64>    //180727
         (  - max_root_density * (1.0 - exp_term));                              //180727
      //180727 abandoned root_distribution_unadjust.set(layer,root_distr_unadjust_layer);           //030722
      root_distribution_unadjust[layer] = root_distr_unadjust_layer;             //180727
      root_distr_unadjust_sum += root_distr_unadjust_layer;                      //180727
      /* Need to update sum
      root_distribution_unadjust[layer] = - max_root_density * (1.0 - exp_term);                                        //030722
      root_distribution_unadjust[layer] = CORN::must_be_0_or_greater<float64>(root_distribution_unadjust[layer]);
      */
      //180726 L_sum += L[layer];

//      root_density_at_layer_bottom[layer] =                                      //030722
//         L[rooting_layer-1] > 0.00001                                            //110705
//         ? max_root_density * L[layer] / L[rooting_layer-1]
//         : 0.0;
//      root_density[layer] = (root_density_at_layer_bottom[layer] + root_density_at_layer_bottom[layer-1])/2.0; //030722
//      density_area[layer] = layer_thickness * (L[layer] + (L[layer-1] - L[layer])/2);
//
//      std::clog << "L:" << (int)layer
//                << "\root_distribution_unadjust:" << root_distribution_unadjust[layer]
//                << std::endl;

//      density_area_sum += density_area[layer];
      depth_top_soil_layer += layer_thickness;                                      //030722
   }
   return root_distr_unadjust_sum; //180727 abandoned root_distribution_unadjust.sum(); //180726 L_sum;
}
//_update_root_densities____________________________________________2006-12-08_/
float64 Crop_root_vital::update_root_fractions()
{
   // In CropSyst, we use density area, for CropGro, use simply density.
   nat8 layers_eff = soil_layers.get_number_uninundated_layers();                //080211_031202_031202
      // usually the number of sublayers (but may be less in water table conditions)
   //if (CORN::is_approximately<float64>(density_area_sum,0.0,0.00001))
   //{  nat8  max_layers = soil_layers.get_max_number_layers();
   //   for (nat8  layer = 1; layer <= max_layers; layer++)
   //      density_area_sum += density_area[layer];
   //}
   //180727 float64 root_distr_unadjust_sum = root_distribution_unadjust.sum();       //180727
   clear_sublayer_array(total_fract_root_length);                                //051013
   if (CORN::is_approximately<float64>(root_distr_unadjust_sum,0.0,1e-12))
      //031203  180727LML at the start of growing season the L_sum is very small
      return 1.0; // no roots yet (this may happen in CropGro).                  //031203
   float64 sum_fract_root = 0.0;
   for (nat8  layer = rooting_layer; layer <= layers_eff; layer++)               //981021
   {  total_fract_root_length[layer] =                                           //010322
         root_distribution_unadjust[layer] /  root_distr_unadjust_sum;           //180726_030721
      sum_fract_root += total_fract_root_length[layer];                          //010322
   }
   if (is_approximately(sum_fract_root,0.0,0.0000001))                           //981023
      sum_fract_root = 1.0;                                                      //981023
   float64 soil_depth_limit = soil_layers.get_depth_m(layers_eff)                //981009
      - (soil_layers.get_thickness_m(layers_eff)/2.0);
   if (((root_length + soil_layers.get_depth_m(rooting_layer-1)) > soil_depth_limit)
#ifdef VIC_CROPSYST_VERSION
           || //180521LML &&   //981009
#else
           &&
#endif
      (! CORN::is_approximately<float64>(sum_fract_root,1.0,0.000000001)))
   {  for (nat8  layer = rooting_layer; layer <= layers_eff; layer++)
        total_fract_root_length[layer] *= 1.0 / sum_fract_root;                  //010322
      for (nat8  layer = layers_eff+1; layer <=  MAX_soil_layers ;layer++)       //981021
        total_fract_root_length[layer] = 0.0;                                    //010322
      sum_fract_root = 1.0;                                                      //061208
   }
   return sum_fract_root;
}
//_update_root_fractions________________________________________________________
float64 Crop_root_vital::update_root_lengths()
{  float64 root_length_remaining = root_length;
   nat8  number_soil_layers = soil_layers.get_number_layers();
   total_root_lengths = 0;
   for (nat8  lyr = rooting_layer; (lyr <= number_soil_layers) && (root_length_remaining > 0.0); lyr++) //120514
   {  float64 soil_layer_thickness = soil_layers.get_thickness_m(lyr);
      float64 soil_layer_root_length
         = (root_length_remaining > soil_layer_thickness)
         ? soil_layer_thickness
         : root_length_remaining;
      root_density[lyr] = max_root_density * total_fract_root_length[lyr] / total_fract_root_length[rooting_layer];
      root_length_remaining -= soil_layer_root_length;
      float64 root_density_lyr_m_m3 = cm_per_cm3_to_m_per_m3(root_density[lyr]);  // 060612 cm/cm3
      float64 root_lengths_lyr // This is the length of all root pieces in this layer
         = root_density_lyr_m_m3 * soil_layer_root_length;  // usually layer thickness execpt for the last
      root_lengths[lyr] = root_lengths_lyr;                                      //061129
      total_root_lengths += root_lengths_lyr;
#ifdef DEBUG_ROOT
roots_txt <<
simulation_today.get()
<<  '\t'  <<
(int) lyr << '\t' <<soil_layer_root_length << '\t' << root_density_lyr_m_m3
   << '\t' <<  root_lengths_lyr<< '\t' << total_root_lengths << '\t'
   <<total_fract_root_length[lyr]<< std::endl;
#endif
   }
   return total_root_lengths;
}
//_update_root_lengths______________________________________________2006-12-08_/
void Crop_root_vital::update(bool terminate_pending)
{  /*float64 root_depth_unused = */ update_root_depth(terminate_pending);        //130909_981023
   //180726 soil_layer_array64(density_area); clear_layer_array64(density_area); //030722
   float64 density_area_sum = update_root_densities(/*180726 density_area*/);    //061208
   update_root_fractions(/*180726 density_area,density_area_sum*/);              //031102
   update_root_lengths();                                                        //061208
   biomass = calc_root_biomass(0);                                               //070130
   growth_biomass = (biomass > biomass_yesterday)
      ? biomass - biomass_yesterday : 0.0;                                       //070130
}
//_update_______________________________________________________________2003?__/
float64 Crop_root_dormant::calc_root_biomass(float64 *output_root_biomass_by_layer) const
{  // if root_biomass_by_layer array is passed, record the root biomass values by layer
   float64 calced_root_biomass = 0.0;
   for (nat8  lyr = 0; (lyr < MAX_soil_layers); lyr++)
   {  if (output_root_biomass_by_layer)
         output_root_biomass_by_layer[lyr] = biomass_by_layer[lyr];
      calced_root_biomass +=  biomass_by_layer[lyr];
   }
   return calced_root_biomass;
}
//_calc_root_biomass________________________________________________2006-06-12_/
void Crop_root_vital::kill()
{  clear_layer_array64(root_density);
   clear_layer_array64(total_fract_root_length);
   clear_layer_array64(root_lengths);
   root_length = 0;
}
//_kill_____________________________________________________________2006-06-12_/
RENDER_INSPECTORS_DEFINITION(CropSyst::Crop_root_common)
{
/*NYI
CSVP_crop_base_root_fraction   1-31
*/
   // uses crop emanator                                                         //160616
   // Now the root object simply uses the context emanator

   inspectors.append(new CS::Inspector_scalar(biomass,UC_kg_m2,*context
      ,"root/biomass" ,value_statistic,CSVP_crop_base_root_biomass_current));
   return 0;
}
//_RENDER_INSPECTORS_DEFINITION_____________________________________2013-09-09_/
RENDER_INSPECTORS_DEFINITION(CropSyst::Crop_root_vital)
{
   // Crop_root_vital uses the crop's emanator.                                  //160616
   inspectors.append(new CS::Inspector_scalar(apparent_root_depth,UC_meter
      ,*context,"root/depth",value_statistic,CSVP_crop_base_root_depth));
   return 0;
}
//_RENDER_INSPECTORS_DEFINITION_____________________________________2013-09-09_/
} // namespace CropSyst


