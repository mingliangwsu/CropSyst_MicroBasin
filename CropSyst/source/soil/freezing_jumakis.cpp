#  include <math.h>
#  include "corn/math/moremath.h"
#  include "corn/math/compare.h"
#  include "corn/measure/measures.h"
#  include "soil/freezing_jumakis.h"
#  include "soil/soil_interface.h"
#  include "soil/hydrology_interface.h"
#  include "soil/structure_interface.h"
#  include "soil/temperature_interface.h"
#  include "soil/temperature_functions.h"
#  include "weather/snow_pack.h"
//______________________________________________________________________________
Soil_freezing_profile_jumakis::Lenses_manager::Lenses_manager()
:Unidirectional_list()
{}
//______________________________________________________________________________
Soil_freezing_profile_jumakis::Lenses_manager::Lens::Lens
(float64 i_top
,float64 i_bottom)
: Item()
, top(i_top)
, bottom(i_bottom)
{}
//______________________________________________________________________________
float64 Soil_freezing_profile_jumakis::Lenses_manager::Lens::
get_fract_frozen(float64 from_depth , float64 to_depth ) const
{  float64 result = 0.0;
   if (!((top > to_depth) || (bottom < from_depth) || ((to_depth - from_depth) == 0.0)))  //981018
   {  float64 common_top = std::max<float64>(from_depth,top);
      float64 common_bottom = std::min<float64>(to_depth,bottom);
      result = (common_bottom - common_top) / (to_depth - from_depth);
   }
   return result;
}
//______________________________________________________________________________
float64 Soil_freezing_profile_jumakis::Lenses_manager::
get_fract_frozen(float64 from_depth , float64 to_depth)                    const
{  float64 total_fract_frozen = 0.0;
/*for debugging
if (count())
{  std::cout << "\nfrom:" << from_depth << "to:" << to_depth << std::endl;
   std::cout << "\tlenses: \t";
}
*/
   FOR_EACH(lens,Lens,each_lens);                                                //030707
      total_fract_frozen += lens->get_fract_frozen(from_depth,to_depth);
/*for debugging
std::cout << "(t:" << lens->top << " b:" << lens->bottom << ")";
*/
   FOR_EACH_END(each_lens)
   return CORN_must_be_between(total_fract_frozen,0.0,1.0);
}
//______________________________________________________________________________
void Soil_freezing_profile_jumakis::Lenses_manager::
add_lens(float64 top , float64 bottom )
{  // Delete all lenses completely encompased by the new lense;
   Unidirectional_list good_lenses;                                              //030707
   Lens *lens_to_delete = (Lens *)pop_at_head();                                 //030707
   while (lens_to_delete)                                                        //030707
   {  // If the new lens completely encompases this lens, then delete this lens  //030707
      if ((top <= lens_to_delete->top) && (bottom >= lens_to_delete->bottom)) delete lens_to_delete;
      else good_lenses.append(lens_to_delete);                                   //030707
      lens_to_delete = (Lens *)pop_at_head();                                    //040401
   }
   transfer_all_from(good_lenses);                                               //030707
   // See if we can join this lense to an existing lens:
   FOR_EACH(lens,Lens,each_lense)                                                //030707
   {  // If the new lens completely encompases this lens, then delete this lens }
      if (((top >= lens->top) && (top <= lens->bottom)) ||
          ((bottom <= lens->bottom) && (bottom >= lens->top)))
      { //join_to_existing_lens
         lens->resize(std::min<float64>(top   ,lens->top)
                     ,std::max<float64>(bottom,lens->bottom));
         return;
      }
   } FOR_EACH_END(each_lense)
   append(new Lens(top,bottom));
}
//______________________________________________________________________________
Soil_freezing_profile_jumakis::Lenses_manager::Lens *
Soil_freezing_profile_jumakis::Lenses_manager::get_highest_lens() const
{  Lens *highest_lens = 0;
   FOR_EACH(lens,Lens,each_lens)                                                 //030707
       if (!highest_lens || (lens->top < highest_lens->top))                     //030707
             highest_lens = lens;
   FOR_EACH_END(each_lens)
   return highest_lens;
}
//______________________________________________________________________________
Soil_freezing_profile_jumakis::Lenses_manager::Lens *
Soil_freezing_profile_jumakis::Lenses_manager::get_next_highest_lens(Lens *below_lense ) const
{  Lens *highest_lens = below_lense;
   FOR_EACH(lens,Lens,each_lens)                                                 //030707
      if ((lens->top < highest_lens->top) && (lens->top > below_lense->top))     //030707
             highest_lens = lens;                                                //030707
   FOR_EACH_END(each_lens)
   return (highest_lens == below_lense) // No lenses below the specified lense }
   ? 0
   : highest_lens;
}
//______________________________________________________________________________
Soil_freezing_profile_jumakis::Lenses_manager::Lens *
Soil_freezing_profile_jumakis::Lenses_manager::get_lowest_lens()           const
{  Lens *lowest_lens = 0;
   FOR_EACH(lens,Lens,each_lens)                                                 //030707
       if (!lowest_lens || (lens->bottom > lowest_lens->bottom))
          lowest_lens = lens;
   FOR_EACH_END(each_lens)
   return lowest_lens;
}
//______________________________________________________________________________
float64 Soil_freezing_profile_jumakis::Lenses_manager
::get_highest_lens_top()                                                   const
{  Lens *highest_lens = get_highest_lens();
   return (highest_lens )  ? highest_lens->top  : 0.0;
}
//______________________________________________________________________________
float64 Soil_freezing_profile_jumakis::Lenses_manager
::get_lowest_lens_bottom()                                                 const
{  Lens *lowest_lens = get_lowest_lens();
   return (lowest_lens) ? lowest_lens->bottom : 0.0;
}
//______________________________________________________________________________
Soil_freezing_profile_jumakis::Lenses_manager::Lens *
Soil_freezing_profile_jumakis::Lenses_manager::
get_next_lowest_lens(Lens *above_lens )const
{  Lens *lowest_lens = 0;
   FOR_EACH(lens,Lens,each_lens)                                                 //030707
      if (!lowest_lens || ((lens->bottom > lowest_lens->bottom)                  //030707
         && (lens->bottom < above_lens->bottom)))
          lowest_lens = lens;
   FOR_EACH_END(each_lens)
   return (lowest_lens == above_lens) //  No lenses above the specified lens
   ? 0 : lowest_lens;
}
//______________________________________________________________________________
Soil_freezing_profile_jumakis::Soil_freezing_profile_jumakis                     //990308
(unmodifiable_ Soil_layers_interface               &_soil_layers                 //051201
,unmodifiable_ Soil_structure_interface            &_soil_structure              //070725
,unmodifiable_ Soil_hydraulic_properties_interface &_soil_hydraulic_properties   //051201
,  modifiable_ Soil_hydrology_interface            &_soil_hydrology              //051201
,unmodifiable_ Soil_temperature_interface          &_soil_temp_profile
,const         Air_temperature_average             &air_temperature_avg_         //151022
)          //080123
:Soil_freezing_profile_interface()                                               //070825
,  temperature_profile(_soil_temp_profile)
, air_temperature_avg(air_temperature_avg_)                                      //151128
, frozen_lenses()
, freezing_index(0.0)
, freezing_days(0)
, soil_layers(_soil_layers)                                                      //070825
   // These soil interfaces were moved from Soil_freezing_profile_abstract
, soil_structure(_soil_structure)                                                //070825
, soil_hydraulic_properties(_soil_hydraulic_properties)                          //070825
, soil_hydrology(_soil_hydrology)                                                //070825
{}
//_1999-03-08___________________________________________________________________
float64 Soil_freezing_profile_jumakis::get_fract_frozen(nat8 layer) const
{ return frozen_lenses.get_fract_frozen(soil_layers.get_depth_m(layer) - soil_layers.get_thickness_m(layer),soil_layers.get_depth_m(layer)); }
//_1998-10-14___________________________________________________________________
#ifdef OBSOLETE
//990318_ now using deVries method
enum directions {a,b,c};
enum soil_components {MINERAL,ICE,WATER};
float64 specific_thermal_conductivity[] = {0.007,0.0052,0.00139}; // cal/cm sec deg.celcius
//______________________________________________________________________________
float64 depolarisation_factor(directions direction,float64 bulk_density,double_float water_content)
{  if (direction == c)
      return 1.0 - depolarisation_factor(b,bulk_density,water_content) - depolarisation_factor(a,bulk_density,water_content);
   else
   {  float64 porosity = 1.0 - (bulk_density/2.65);
      float64 soil_air_vol_content = porosity - water_content; // Is this really the same for b
      return 0.333 - (soil_air_vol_content / 0.427) * (0.333 - 0.035);
   }
}
//______________________________________________________________________________
#define continuous_medium  WATER

float64 directional_contribution(directions direction,soil_components component,float64 bulk_density,double_float water_content)
{  return (1.0/3.0) /  //Warning the original equation missed a paran.
	       ((1.0 + (specific_thermal_conductivity[component]/
		      specific_thermal_conductivity[continuous_medium] - 1.0) *
		   depolarisation_factor(direction,bulk_density,water_content)));
}
//______________________________________________________________________________
float64 avg_temp_grad_ratio(soil_components component,float64 bulk_density,float64 water_content)
{
  return directional_contribution(a,component,bulk_density,water_content) +
         directional_contribution(b,component,bulk_density,water_content) +
         directional_contribution(c,component,bulk_density,water_content);
}
//______________________________________________________________________________
float64 thermal_conductivity    //cal /(cm * sec * C')}
(double_float water_content, float64 ice_content,float64 bulk_density)
{  float64 volume_content;
   soil_components soil_component;
   float64 sum_dividend = 0.0;
   float64 sum_divisor = 0.0;   // These need new names
   for (soil_component = MINERAL; soil_component <= WATER; soil_component++)
   {  switch (soil_component)
      {  case MINERAL : volume_content = bulk_density / 2.65; break;
 	      case WATER   : volume_content = water_content;       break;
 	      case ICE     : volume_content = ice_content;         break;//should be frozen_WC
 	   }
 	   float64 divisor = avg_temp_grad_ratio(soil_component,bulk_density,water_content) * volume_content;
 	   float64 dividend = divisor * specific_thermal_conductivity[soil_component];
 	   sum_dividend += dividend;
 	   sum_divisor += divisor;
   }
   return (sum_divisor != 0.0) ? (sum_dividend / sum_divisor) : 0.0;
}
//__________________________________________________________Thermal conductivity
#endif
float64 Soil_freezing_profile_jumakis::heat_capacity
(nat8    layer
,float64 water_content_layer
,bool    get_frozen_heat_capacity)
{  static const float64 mineral_vol_specific_heat_capacity = 0.46;
   static const float64 ice_vol_specific_heat_capacity     = 0.45;
   static const float64 air_vol_specific_heat_capacity     = 0.0003;
   static const float64 water_vol_specific_heat_capacity   = 1.0;
   float64 bulk_density_layer= soil_structure.get_bulk_density_g_cm3(layer);
   float64 mineral_content = bulk_density_layer / 2.65;
   float64 porosity =   1 - (bulk_density_layer / 2.65);
   float64 soil_air_vol_content = porosity - soil_hydrology.get_water_plus_ice_content_volumetric(layer); //Is this really the same for b //990315
      // Note that water or ice exclusively will have a value.
      // it the case of water unfrozen heat capacity is returned,
      // in the case of ice, frozen heat capacity is returned. */
   float64 vol_heat_capacity = (get_frozen_heat_capacity)
      ? ice_vol_specific_heat_capacity
      : water_vol_specific_heat_capacity;
   return
        mineral_content * mineral_vol_specific_heat_capacity                     //980917
      + soil_air_vol_content * air_vol_specific_heat_capacity
      + water_content_layer * vol_heat_capacity;
}
//_1998-06-12___________________________________________________________________
float64 Soil_freezing_profile_jumakis::get_frozen_thickness_m(nat8 layer) const
{  return soil_layers.get_thickness_m(layer) * get_fract_frozen(layer);
}
//______________________________________________________________________________
float64 Soil_freezing_profile_jumakis::calc_liquid_and_ice_water_content_volumentric
(nat8      layer
,float64   &liquid_water_content_volumetric
,float64   &ice_content_volumetric)                                 calculation_
{  float64 fract_frozen = get_fract_frozen(layer);  //  portion of the soil that contains some ice and water
   float64 all_water_content = soil_hydrology.get_water_plus_ice_content_volumetric(layer) ;
   float64 perm_wilt_point_sl = soil_hydraulic_properties.get_permanent_wilt_point_volumetric(layer);
   ice_content_volumetric =
            CORN_must_be_greater_or_equal_to((all_water_content- perm_wilt_point_sl),0.0)
                      * fract_frozen;
   liquid_water_content_volumetric
      =  all_water_content - ice_content_volumetric;

// Note: Don't set liquid and ice member array,  This will be done at the end of freezing_and_thaw

   return fract_frozen;
}
//_1999-03-11___________________________________________________________________
static const nat8 snow_layer = 0;
static const float64 latent_heat_of_fusion  = 80.0; // cal/cm3
void Soil_freezing_profile_jumakis::perform_freezing()
{
   if (freezing_index  < 0.0) freezing_days--;
   else                       freezing_days++;
   if (freezing_days < 0)     freezing_days = 0;
   float64 thermal_snow_resistance = 0.0;  // (cm^2 s C)/ cal
   soil_layer_array64(required_freezing_index);
   required_freezing_index[snow_layer] = 0.0;
   float64 cum_profile_energy = 0.0;
   float64 weighted_thermal_conductivity = 0.0;
   soil_layer_array64(latent_heat_fusion);
   for (int8 layer = 1; layer <= soil_layers.get_number_layers(); layer++)
   {  float64 depth_cm =  m_to_cm(soil_layers.get_depth_m(layer));
      float64 thickness_cm = m_to_cm(soil_layers.get_thickness_m(layer));
      float64 liquid_water_content_volumetric = 0;
      float64 ice_content_volumetric = 0;
      float64 fract_frozen = calc_liquid_and_ice_water_content_volumentric
         (layer,liquid_water_content_volumetric,ice_content_volumetric);
      float64 thermal_conductivity_layer = DeVries_thermal_conductivity
         (liquid_water_content_volumetric
         ,ice_content_volumetric
         ,soil_structure.get_bulk_density_g_cm3(layer)) /  418.4;
                    //{ cal /(cm * sec * C') -> J/(m sec 'C) }
      weighted_thermal_conductivity += thermal_conductivity_layer * thickness_cm;
      float64 cum_profile_thermal_resistance
         =  thermal_snow_resistance + CORN_sqr(depth_cm) / weighted_thermal_conductivity;
      float64 frozen_heat_capacity_layer =   //as if whole layer were frozen
          heat_capacity(layer, ice_content_volumetric ,true);    // Warning check this why not soil_hydrology.get_water_plus_ice_content_volumetric(layer)
      float64 unfrozen_heat_capacity_layer = //{as if whole layer were thaw }
          heat_capacity(layer, soil_hydrology.get_water_plus_ice_content_volumetric(layer) ,false);
      float64 energy_needed_to_lower_temperature = (temperature_profile.get_temperature(layer) > 0)
      ? (unfrozen_heat_capacity_layer * (1.0-fract_frozen))* temperature_profile.get_temperature(layer)
      : 0.0;
      float64 frozen_layer_index_requirement =
         ((soil_hydrology.get_ice_content_volumetric(layer)> 0.0) && (freezing_days != 0))
      ?  frozen_heat_capacity_layer * freezing_index / (2.0 * freezing_days)
      :   0.0;
      latent_heat_fusion[layer] =
         latent_heat_of_fusion * (soil_hydrology.get_water_plus_ice_content_volumetric(layer)  // Current
                                  - ice_content_volumetric
                                  - soil_hydraulic_properties.get_permanent_wilt_point_volumetric(layer));
      float64 layer_energy = (latent_heat_fusion[layer] + frozen_layer_index_requirement
        + energy_needed_to_lower_temperature);
      cum_profile_energy += layer_energy ;   //  now doing full layer
       required_freezing_index[layer] =
             cum_profile_energy
           * (depth_cm /  86400.0)
           * cum_profile_thermal_resistance;
   }
   float64 comp_frost_depth_cm  = 0.0;
   nat8 frozen_layer = 0;
   do // Skip down to non frozen layer
   {  frozen_layer ++;
      comp_frost_depth_cm += m_to_cm(soil_layers.get_thickness_m(frozen_layer));
      layer_freeze_or_thaw_occured[frozen_layer] = true ;
   } while ((required_freezing_index[frozen_layer] < freezing_index) &&
      (frozen_layer != soil_layers.get_number_layers()));
   float64 total_frost_depth_cm = 0.0;
   if (frozen_layer == soil_layers.get_number_layers())
      total_frost_depth_cm = comp_frost_depth_cm; // whole profile is frozen
   else //{ layer is partially or not frozen:}
   {  float64 thickness_cm =  m_to_cm(soil_layers.get_thickness_m(frozen_layer)) ;
      float64 diff_required_freezing_index =  (required_freezing_index[frozen_layer]   //980618
         - required_freezing_index[frozen_layer-1]);                             //980618c
      total_frost_depth_cm = (comp_frost_depth_cm -
        thickness_cm+
         (freezing_index - required_freezing_index[frozen_layer - 1])
            / diff_required_freezing_index * thickness_cm);
   }
   frozen_lenses.add_lens(0,cm_to_m(total_frost_depth_cm));                      //981015
}
//_2007-08-08_________________________________________________perform_freezing_/
bool Soil_freezing_profile_jumakis::thaw
(Soil_freezing_profile_jumakis::Lenses_manager::Lens *lens
,bool from_top
,float64 &thawing_index_left
,soil_layer_array64(required_thawing_index))
{
   nat8 top_layer     = soil_layers.get_layer_at_depth(lens->top);               //981014
   nat8 bottom_layer  = soil_layers.get_layer_at_depth(lens->bottom);            //981014
   int layer = (from_top)
   ? top_layer                                                                   //981014
   : bottom_layer;
   float64 total_thawed = 0.0;
   float64 prev_layer_required_thawing_index = 0.0;                              //981210
   float64 layer_require_thawing_index = required_thawing_index[layer] ;
   bool at_other_end_of_lens =  top_layer == bottom_layer;
   while ((thawing_index_left >layer_require_thawing_index)  && !at_other_end_of_lens) //981014
   {  thawing_index_left -= layer_require_thawing_index;
      float64 thawed_in_layer = get_frozen_thickness_m((nat8)layer);
      total_thawed += thawed_in_layer;
      layer += from_top ? +1 : -1;
      at_other_end_of_lens = from_top
      ? (layer == bottom_layer)
      : (layer == top_layer);
      layer_require_thawing_index = CORN_must_be_greater_or_equal_to
             (required_thawing_index[layer] - prev_layer_required_thawing_index,0.0);
      prev_layer_required_thawing_index = required_thawing_index[layer] ;        //000711
      if (layer < soil_layers.get_number_layers())                               //070827
         layer_freeze_or_thaw_occured[layer] = thawed_in_layer > 0.0 ;           //070827
    }
    if (layer_require_thawing_index != 0)
    {
      float64 thawed_in_layer =
         thawing_index_left * soil_layers.get_thickness_m((nat8)layer) / (layer_require_thawing_index);
      total_thawed += thawed_in_layer;
      layer_freeze_or_thaw_occured[layer] = thawed_in_layer > 0.0 ;              //070827
    }
    if (from_top) lens->top += total_thawed;
    else          lens->bottom -= total_thawed;
    return lens->top >= lens->bottom;
}
//_1998-10-14__________________________________________________________________/
void Soil_freezing_profile_jumakis::perform_thawing(bool thaw_from_both_top_and_bottom)
{  float64 thawing_index = - freezing_index;                                     //981002
   float64 bottom_thawing_index = thawing_index * 0.7;                           //981019
   float64 top_thawing_index = thawing_index - bottom_thawing_index;             //981002
   soil_layer_array64(required_thawing_index);
   for (int8 clear_layer = 1; clear_layer <= MAX_soil_layers; clear_layer++)
      required_thawing_index[clear_layer] = 0.0;
   int8 last_frozen_layer = soil_layers.get_number_layers();                     //981015
   for (int8 check_frozen_layer = 1
       ; check_frozen_layer <= soil_layers.get_number_layers()
       ; check_frozen_layer++)                                                   //981015
      if (get_fract_frozen(check_frozen_layer) > 0.0)                            //981015
           last_frozen_layer = check_frozen_layer;                               //981015
   // Fusion is accumulated bottom up
   float64 cum_latent_heat_fusion = 0;
   float64 weighted_thermal_conductivity = 0.0;
   float64 pot_thaw_depth_cm = 0.0;
   soil_layer_array64(latent_heat_fusion);
   for (nat8 layer = 1; layer <= last_frozen_layer; layer++)                     //981005
   {  float64 liquid_water_content_volumetric = 0;                               //981014
      float64 ice_content_volumetric = 0;                                        //981014
      float64 fract_frozen = calc_liquid_and_ice_water_content_volumentric
         (layer,liquid_water_content_volumetric,ice_content_volumetric);         //990311
      latent_heat_fusion[layer] =
           latent_heat_of_fusion *  ice_content_volumetric ;                     //990126
      cum_latent_heat_fusion  += latent_heat_fusion[layer];
      float64 thickness_cm = m_to_cm(soil_layers.get_thickness_m(layer));
      pot_thaw_depth_cm += thickness_cm * fract_frozen;
      float64 thermal_conductivity_layer = DeVries_thermal_conductivity          //990315
         (liquid_water_content_volumetric                                        //990315
         ,ice_content_volumetric                                                 //990315
         ,soil_structure.get_bulk_density_g_cm3(layer)) /  418.4;
                    // cal /(cm * sec * C') -> J/(m sec 'C) //070725
      weighted_thermal_conductivity +=
            thermal_conductivity_layer * thickness_cm;
      float64 cum_profile_thermal_resistance  = //  dont include snow layer
              CORN_sqr(pot_thaw_depth_cm) / weighted_thermal_conductivity;
   // now compose required thawing index
      required_thawing_index[layer] =
               cum_latent_heat_fusion
             * ( pot_thaw_depth_cm  /  86400.0)
             * cum_profile_thermal_resistance;
   }
   // Thaw each of the frozen lenses from the top
   if (thaw_from_both_top_and_bottom)
   {  float64 thawing_index_left = top_thawing_index;
      for (Soil_freezing_profile_jumakis::Lenses_manager::Lens *lens = frozen_lenses.get_highest_lens()
          ;lens && (thawing_index_left > 0.0)
          ;lens = frozen_lenses.get_next_highest_lens(/*below*/lens))
      {  bool lens_thawed_completely = thaw(lens,true/*from_top*/,thawing_index_left,required_thawing_index);
         if (lens_thawed_completely)
            frozen_lenses.remove(lens); // We have completely thawed this lens
      }
   }
   // Always thaw from bottom
   // Now thow each of the frozen lenses from the bottom
   {  float64 thawing_index_left = bottom_thawing_index;
      for (Soil_freezing_profile_jumakis::Lenses_manager::Lens *lens = frozen_lenses.get_lowest_lens()
         ;lens && (thawing_index_left > 0.0)
         ;lens = frozen_lenses.get_next_lowest_lens(/*above*/lens))
      {  bool lens_thawed_completely = thaw(lens,false/*from_bottom*/,thawing_index_left,required_thawing_index);
         if (lens_thawed_completely)
          frozen_lenses.remove(lens); // We have completely thawed this lens
      }
   }
}
//_1998-10-15__________________________________________________________________/
void Soil_freezing_profile_jumakis::freezing_and_thawing
(const Snow_pack *snow_pack)                                       modification_ //151022
// May be 0 if no snow
{
   //NYN static const float64 snow_density               = 0.1;                  //070808
   //NYN static const float64 snow_vol_heat_capacity     = 0.5;                  //070808
      /*Warning need to look up this value*/
   //NYN static const float64 snow_thermal_conductivity  = 0.00022;              //070808
   //NYN static const float64 daily_decay_coefficient    = 0.97;                 //070808
   static const float64 snow_reduction_coefficient = 0.08;                       //070808
   for (nat8 layer = 0; layer < MAX_soil_layers_alloc; layer++)                  //070827
      layer_freeze_or_thaw_occured[layer] = false;                               //070827

   //151022 Snow pack actually has ref_snow_pack_thickness()
   //but I am not sure if it matches snow_water_equivelent_depth * 10, need to check

   float64 snow_depth_today_cm =
      snow_pack
      ? m_to_cm(snow_pack->get_water_equivelent_depth() * 10.0)  //water -> snow -> cm //980612
      : 0.0;
   freezing_index =
    -(air_temperature_avg.Celcius()                                              //151022
      * exp(-1.6 * snow_reduction_coefficient * snow_depth_today_cm));           //981029
   if (freezing_index > 0)                                                       //980929
      perform_freezing();                                                        //981015
   if ((freezing_index < 0) && any_frozen_zones())                               //980929
      perform_thawing((snow_depth_today_cm <= 0.0));                             //981015

/*for debugging
FOR_EACH_IN(lens,Soil_freezing_profile_jumakis::Lenses_manager::Lens,frozen_lenses,each_lens)
float64 fract_frozen = lens->get_fract_frozen(0.0,3.0);
std::clog << "(t:" << lens->top << " b:" << lens->bottom << ") ff:" << fract_frozen;
FOR_EACH_END(each_lens)
std::clog << std::endl;
*/

}
//_1998-10-15___________________________________________________________________
bool Soil_freezing_profile_jumakis::is_frozen(nat8 layer)                  const
{  bool frozen = get_fract_frozen(layer) > 0.5;
   return frozen;
}
//_1998-10-14___________________________________________________________________

