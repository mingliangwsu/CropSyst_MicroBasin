#include "common/residue/residue_V4_common.h"
#include "organic_matter/OM_pools_common.h"
#include <math.h>
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#include "soil/soil_interface.h"
#ifndef REACCH_VERSION
//130711 we dont bother with the detailed balance check
#include "common/residue/residue_balancer.h"
#endif
#include "USDA/NRCS/RUSLE2/SDR_field_ops.h"
//______________________________________________________________________________
Residues_V4_common::Residues_V4_common
(Organic_matter_pools_common        &organic_matter_pools_
,Soil_interface                     &soil_                                       //060122
,Soil_abiotic_environment_profile   &soil_abiotic_environment_profile_
,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining_      //160719
,const Air_temperature_average      &temperature_air_avg_                        //150427
,const Wind_speed                   &wind_speed_                                 //150427
,const CORN::date32                 &today_
,std::ostream                       *detail_log_)                                //020307
:Residues_common
   (soil_,evaporation_potential_remaining_                                       //160412
   ,temperature_air_avg_,wind_speed_,today_,detail_log_)                         //060330
,organic_matter_pools               (organic_matter_pools_)                      //070707
,soil_abiotic_environment_profile   (soil_abiotic_environment_profile_)          //060330
{}
//______________________________________________________________________________
void Residues_V4_common::update_totals_sum_pools()
{  // DOES NOT account for overlapping straws.
   float64 curr_surface_residue_mass = 0.0;                                                              //080303
   float64 curr_subsurface_residue_mass = 0.0;                                                           //080303
    //130711 we dont bother with the detailed balance check
   #ifdef DETAILED_BALANCES
   for (int pos = 0; pos < OM_POSITION_COUNT;  pos++)                                                    //090408
      residue_mass_balance[pos]->current = 0;                                                            //090408
    #endif
   FOR_EACH_IN(curr_pool,Organic_biomatter_common,organic_matter_pools,each_pool)                        //030707
   {  if (curr_pool->is_straw_or_manure_residue())
      {  bool                    is_above_ground   = curr_pool->is_above_ground();                       //060228
         float64                 pool_mass         = curr_pool->kg();                                    //060328
         Organic_matter_position position          = curr_pool->position;                                //060328
         if (is_above_ground )
         {  float64 pool_surface_mass        = pool_mass;                                                //060302
            float64 pool_area_per_mass       = curr_pool->get_area_per_mass();                           //060302
            float64 pool_residue_area_index  = pool_surface_mass * pool_area_per_mass;                   //060302
            total_residue_area_index[position] += pool_residue_area_index;                               //060228
            total_residue_area_index_both_flat_and_standing += pool_residue_area_index;                  //000609
            curr_surface_residue_mass    += pool_mass;                                                   //080229
         } else                                                                                          //080229
         {  curr_subsurface_residue_mass += pool_mass;                                                   //080229
         }                                                                                              //080229
         #ifdef DETAILED_BALANCES
         //130711 we dont bother with the detailed balance check (actually we should have a flag if we want the residue balance at all
         residue_mass_balance[curr_pool->position]->current += curr_pool->kg();                          //090408
         #endif
      }  } FOR_EACH_END(each_pool)
// The following balance checks are for debugging
//float64 surface_stubble_balance = residue_mass_balance[OM_stubble_surface_position]->update_balance();
//cout << "residue stubble bal:" << surface_stubble_balance << endl;
//   {OM_subsurface_position
//   ,OM_flat_surface_position
//   ,OM_stubble_surface_position
}
//______________________________________________________________________________
float64 Residues_V4_common::get_biomass_output(uint32 include_positions,uint32 include_residue_types  ) const
{  return organic_matter_pools.get_mass(BIOMASS_TOTAL                            //060331
      ,include_residue_types
      ,include_positions); //Don't include what is attached to plant!
}
//_2005-01-16___________________________________________________________________
float64 Residues_V4_common::get_surface_all_biomass()               const
{  return organic_matter_pools.get_mass(BIOMASS_TOTAL                            //060331
      ,(INCLUDE_STRAW_RESIDUE_OM|INCLUDE_MANURE_RESIDUE_OM)
      ,(INCLUDE_POSITION_FLAT_SURFACE|INCLUDE_POSITION_STUBBLE_SURFACE));
      //Don't include what is attached to plant!
}
//______________________________________________________________________________
float64 Residues_V4_common::get_surface_plant_biomass
(nat32 include_positions)                                                  const //170107
{  return organic_matter_pools.get_mass(BIOMASS_TOTAL                            //060331
      ,(INCLUDE_STRAW_RESIDUE_OM)
      ,include_positions /*170107 (INCLUDE_POSITION_FLAT_SURFACE|INCLUDE_POSITION_STUBBLE_SURFACE)*/);
      //Don't include what is attached to plant!
}
//______________________________________________________________________________
float64 Residues_V4_common::get_subsurface_all_biomass()                   const
{  return organic_matter_pools.get_mass(BIOMASS_TOTAL                            //060331
      ,(INCLUDE_STRAW_RESIDUE_OM|INCLUDE_MANURE_RESIDUE_OM)
      ,INCLUDE_POSITION_SUBSURFACE);
}
//_2006-01-16___________________________________________________________________
float64 Residues_V4_common::get_total_surface_biomass()                    const
{  // This is actually the same as  get_surface_all_biomass()
   return organic_matter_pools.get_mass(BIOMASS_TOTAL                            //060331
      ,(INCLUDE_STRAW_RESIDUE_OM)
      ,(INCLUDE_POSITION_FLAT_SURFACE|INCLUDE_POSITION_STUBBLE_SURFACE)); //Don't include what is attached to plant!
}
//_2001-10-11___________________________________________________________________
float64 Residues_V4_common::get_subsurface_XXXX_biomass(soil_sublayer_array_64(layer_residues),Organic_matter_type residue_type)
{  float64 all_subsurface_residue_biomass = 0;
   if (layer_residues)
   {  // by layer is wanted
      FOR_EACH_IN(om_pool,Organic_biomatter_common, organic_matter_pools, each_om_pool)
      {  if ((om_pool->type == residue_type) && (om_pool->position == OM_subsurface_position))
         {  float64 residue_biomass = om_pool->kg();
            layer_residues[om_pool->layer] += residue_biomass;
            all_subsurface_residue_biomass += residue_biomass;
         }
      } FOR_EACH_END(each_om_pool)
   } else // Simply get return the totals
      all_subsurface_residue_biomass = organic_matter_pools.get_mass
         (BIOMASS_TOTAL
         ,((residue_type == STRAW_RESIDUE) ? INCLUDE_STRAW_RESIDUE_OM :INCLUDE_MANURE_RESIDUE_OM)
         ,INCLUDE_POSITION_SUBSURFACE);
   return all_subsurface_residue_biomass;
}
//_2000-08-10__________________________________________________________________/
float64 Residues_V4_common::get_subsurface_plant_biomass(soil_sublayer_array_64(plant_residues))
{ return get_subsurface_XXXX_biomass(plant_residues,STRAW_RESIDUE); }
//_2000-08-10__________________________________________________________________/
float64 Residues_V4_common::get_subsurface_manure_biomass(soil_sublayer_array_64(manure_residues))
{ return get_subsurface_XXXX_biomass(manure_residues,MANURE_RESIDUE); }
//_2000-08-10__________________________________________________________________/
void Residues_V4_common::balance(bool run_nitrogen)
{  update_totals_all();
}
//_2008-07-18__________________________________________________________________/
void Residues_V4_common::recalibrate_surface_residue
(float64 surface_residue_param
,float64 incorp_residue_param                                                    //010202
,const Residue_decomposition_parameters &residue_decomposition_params            //060219
#ifdef NITROGEN
,float64 residue_N_conc_param
#endif
)
{
   evaporation_actual.clear();                                                   //160719
   evaporation_potential.clear();                                                //260719

   curr_water_hold         = 0.0;// m3/kg
   water_storage           = 0.0;                                                //170104
   interception            = 0.0;// m
   // delete all residues
   float64 deleted_mass = 0.0;
   FOR_EACH_IN(popped_pool,Organic_biomatter_common ,organic_matter_pools,each_pool) //070418
   {  if ( popped_pool->is_straw_or_manure_residue())
      {  float64 pool_biomass = popped_pool->kg();
         deleted_mass += deleted_mass;                                           //170217
         each_pool->detach_current();                                            //070418
         delete popped_pool;                                                     //070418
      }
   } FOR_EACH_END(each_pool)
   { soil_sublayer_array_64(subsurface_residue);
     clear_sublayer_array(subsurface_residue);
     for (int sl = 0; sl <= MAX_soil_sublayers; sl++)
         subsurface_residue[sl] = 0;
     subsurface_residue[2] = incorp_residue_param;                               //010202
     add_surface_plant_pool
        (OM_flat_surface_position                                                //040517
            // Currently assuming initial surface residue is laying flat (compatibility with previous versions)
        ,OM_ORIGINAL_CYCLING
        ,surface_residue_param                                                   //010202
        #ifdef NITROGEN
        ,residue_N_conc_param
        #endif
        ,residue_decomposition_params);                                          //060219
     add_subsurface_plant_pool
        (subsurface_residue                                                      //040517
        #ifdef NITROGEN
        ,residue_N_conc_param
        #endif
        ,residue_decomposition_params);                                          //060219
  }
}
//_2000-03-12___________________________________________________________________
void Residues_V4_common::redistribute_all
(float64 fract_surface_to_surface
,float64 fract_surface_to_shallow)
{
   if (!CORN::is_approximately<float64>(fract_surface_to_shallow,0.0,0.0000001))
   {  float64 fract_surface_to_deep = 1.0 - (fract_surface_to_surface + fract_surface_to_shallow);
      float64 fract_shallow_to_deep = (fract_surface_to_deep != 0.0)
      ? fract_surface_to_shallow / 2.0
      : 0.0;
      if (! CORN::is_approximately<float64>(fract_surface_to_surface,1.0,0.000001)) //980504
      {  bool no_deep_horizon = has_such_horizon(DEEP_HORIZON);
         if (no_deep_horizon)                                                    //060330
         {  fract_surface_to_shallow += fract_surface_to_deep;
            fract_surface_to_deep = 0.0;
            fract_shallow_to_deep = 0.0;
         }
         CORN::Unidirectional_list redistributed_pools;
         for (Organic_biomatter_common *popped_pool = (Organic_biomatter_common *)organic_matter_pools.pop_at_head()
             ; popped_pool
             ; popped_pool = (Organic_biomatter_common *)organic_matter_pools.pop_at_head())
         {  if ( popped_pool->is_straw_or_manure_residue())
               redistribute(redistributed_pools,popped_pool
               ,fract_shallow_to_deep
               ,fract_surface_to_deep
               ,fract_surface_to_shallow
               ,shallow_horizon_thickness                                        //980217
               ,deep_horizon_thickness);                                         //980217
            else redistributed_pools.append(popped_pool); // This isn't a residue dont try to redistribute
         }
         for (Organic_biomatter_common *popped_pool = (Organic_biomatter_common *)redistributed_pools.pop_at_head()
             ; popped_pool
             ; popped_pool = (Organic_biomatter_common *)redistributed_pools.pop_at_head())
         {  Organic_biomatter_common *comparable_pool = organic_matter_pools.find_similar_organic_biomatter(*popped_pool);
            if (comparable_pool)
            {  comparable_pool->add_mass(popped_pool->kg()); delete popped_pool; popped_pool = 0;
            } else organic_matter_pools.append(popped_pool);
         }
      }
   }
//WARNING not sure if fract_ground_cover is obsolete, check if this needs to be done
///*990217P*/    fract_ground_cover = 1 - exp(-area_per_mass * biomatter_profile.get_surface_mass());

//float64 debug_residue_mass_after = get_surface_all_biomass() + get_subsurface_all_biomass();
//cout << "RMA:" << debug_residue_mass_after << endl;
}
//______________________________________________________________________________
void Residues_V4_common::redistribute
(CORN::Unidirectional_list &redistributed_pools                                  //980924
,Organic_biomatter_common *pool_to_redistributed
,float64 fract_shallow_to_deeps
,float64 fract_surface_to_deeps                                                  //980924
,float64 fract_surface_to_shallow
,float64 _shallow_horizon_thickness                                              //990217
,float64 _deep_horizon_thickness)                                                //990217
{  // Check if there are indeed any deep horizons
   // If not, then we need to dont put the fraction
   float64 fract_stays      = 1.0;
   float64 fract_to_shallow = 1.0;
   float64 fract_to_deeps   = 1.0;
   Organic_biomatter_common *to_shallow = 0;                                     //060330
   Organic_biomatter_common *to_deeps   = 0;                                     //060330
   if (pool_to_redistributed->is_above_ground())                                 //060330
   {  // it is surface
      fract_to_shallow = fract_surface_to_shallow;
      fract_to_deeps   = fract_surface_to_deeps;
      fract_stays = 1.0 - fract_to_shallow - fract_to_deeps;
      Organic_biomatter_common *to_surface =
//170303       #ifdef OLD_SINGLE_RESIDUES_POOL
//170303          duplicate_residue(pool_to_redistributed);
//170303       #else
         pool_to_redistributed->clone();                                          //111001
//170303       #endif
      to_surface->multiply_by(fract_stays);
      redistributed_pools.append(to_surface);
      setup_contribution(*to_surface);                                           //060728
   } else // it is subsurface
   {  switch (horizons[pool_to_redistributed->layer])                            //060330
      {  case  SHALLOW_HORIZON   :
         {  fract_to_deeps    = fract_shallow_to_deeps;
            fract_to_shallow  = 1.0 - fract_shallow_to_deeps;
         } break;
         default : // DEEP_HORIZON
         {  // We can't move deep up
            fract_to_deeps    = 1.0;
            fract_to_shallow  = 0.0;
         }
      }
   }
   if (fract_to_shallow > 0.0)                                                   //060605
   {
//170303       #ifdef OLD_SINGLE_RESIDUES_POOL
//170303       to_shallow = duplicate_residue(pool_to_redistributed);                     //060330
//170303       #else
      to_shallow = pool_to_redistributed->clone();                               //111001
//170303       #endif
      to_shallow->multiply_by(fract_to_shallow);                                 //060330
      to_shallow->set_contact_fraction(subsurface_contact_fraction);             //060330
   }
   if (fract_to_deeps > 0.0)                                                     //060605
   {                                                                             //060330
//170303       #ifdef OLD_SINGLE_RESIDUES_POOL
//170303       to_deeps = duplicate_residue(pool_to_redistributed);                       //060330
//170303       #else
      to_deeps = pool_to_redistributed->clone();                                  //111001
//170303       #endif
      to_deeps->multiply_by(fract_to_deeps);                                     //060330
      to_deeps->set_contact_fraction(subsurface_contact_fraction);
   }
   // Deduct
   for (nat8 layer = 1; layer <= soil_layers.get_number_layers(); layer++)
   {  Organic_biomatter_common *to_this_layer = 0;
      {  float64 layer_thickness = soil_layers.get_thickness_m(layer);
         float64 fract_apportion_this_layer = 0;
         switch (horizons[layer])
         {  case SHALLOW_HORIZON :
            if (to_shallow)                                                      //060605
            {  fract_apportion_this_layer=  layer_thickness / _shallow_horizon_thickness;
               //170303 #ifdef OLD_SINGLE_RESIDUES_POOL
               //170303 to_this_layer =duplicate_residue(to_shallow);
               //170303 #else
               to_this_layer = to_shallow->clone();                              //111001
               //170303 #endif
            } break;
            case DEEP_HORIZON : // case  DEEP_HORIZON      :
            if (to_deeps)                                                        //060605
            {  fract_apportion_this_layer =  layer_thickness / _deep_horizon_thickness;
               //170303 #ifdef OLD_SINGLE_RESIDUES_POOL
               //170303 to_this_layer = duplicate_residue(to_deeps);
               //170303 #else
               to_this_layer = to_deeps->clone();                               //111001
               //170303 #endif
            } break;
            default : break; // DEEPER_HORIZON
         }
         if (to_this_layer)
         {  to_this_layer->multiply_by(fract_apportion_this_layer);
            to_this_layer->layer= layer;                                         //060605
            to_this_layer->set_position(OM_subsurface_position);                 //060613
            to_this_layer->set_contact_fraction(subsurface_contact_fraction);    //060605
            // Go ahead and append event if it is negligable, It will be cleaned up with exhaust
            setup_contribution(*to_this_layer);                                  //060728
            redistributed_pools.append(to_this_layer);
         }
      }
   }
   delete pool_to_redistributed;                                                 //060404
   // Go ahead and append event if it is negligable, It will be cleaned up with exhaust
}
//=1999-02-17===================================================================
float64 Residues_V4_common::remove_from_surface
(float64    fract_to_remove // 0-1
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
,int16      SCS_code
#endif
)
{  // This method may return null if not usable biomass is available for disposal
   // or disposal method
   if (is_approximately(fract_to_remove,0.0,0.00001))
      return 0;
   // for each pool remove and accumulate to removed biomass pool.
   float64 removed_biomass_amount = 0.0;                                         //060122
   FOR_EACH_IN(curr_pool,Organic_biomatter_common,organic_matter_pools,each_pool)//030707
   {  if (curr_pool->is_above_ground())
      {  removed_biomass_amount +=  curr_pool->kg() * fract_to_remove;
         #ifdef DETAILED_BALANCES
         //130711 we dont bother with the detailed balance check (actually we should have a flag if we want the residue balance at all
         if (residue_mass_balance[curr_pool->position])                          //090408
             residue_mass_balance[curr_pool->position]->removed += removed_biomass_amount;   //090407
         #endif
         curr_pool->multiply_by(1.0-fract_to_remove);
   }  } FOR_EACH_END(each_pool)
   organic_matter_pools.set_modified(true);  // should also invalidate (WARNING if it doesn't then need to call invalidate())
#ifdef NYI
May in the future need to have a biomass fate, but even then we are just removing it from the system
   //To clean up balance:

   removed_biomass->set_contact_fraction(DEFAULT_SURFACE_ORGANIC_RESIDUE_CONTACT_FRACTION);  //040818

   // Some residues are eliminated or nothing collected to be disposed of.
   if (  (SCS_code == SCS_residue_flail_chop_bust)  // <- 060122 RLN not sure why flail was was deleting when it could be going to residue?
                                                   // Now that we have stubble residue type, this should send stubble to surface, reather than remove
       ||(SCS_code == SCS_residue_burning))
   {
      delete removed_biomass;
      removed_biomass = 0;
   }
   // In the future we may want to do something with this biomass
   // (when it is not burrend
   // but currently it is just disposed.
   if (removed_biomass)                                                          //060116
       delete removed_biomass;                                                   //060122
#endif
   return removed_biomass_amount;
}
//_2000-05-01___________________________________________________________________
Unidirectional_list &Residues_V4_common::get_pool_list()
{ return organic_matter_pools;}
   // Not needed but need to return something
   // Eventually this function is obsolete, make sure there is no caller
//_2006-02-02___________________________________________________________________
void Residues_V4_common::decompose_all_without_N(/*150427 float64 avg_air_temperature*/)
{
    assert(false);                          //LML 140909
   // NYI
   // Currently presuming always using nitrogen
   // But it is possible to implement decomposition without N
}
//_2004-06-08___________________________________________________________________
float64 Residues_V4_common::calc_carbon_nitrogen_ratio
(float64 biomass                 //  any mass/area units
,float64 nitrogen_concentration
,float64 carbon_fraction
,float64 default_carbon_nitrogen_ratio // incase N mass is unavailable
) const        // fraction of biomass that is elemental carbon mass
{
   float64 C_mass =  biomass * carbon_fraction;
   float64 N_mass =  biomass * nitrogen_concentration;  // Warning check this
   float64 carbon_nitrogen_ratio =(N_mass > 0.000001)
      ? C_mass / N_mass:default_carbon_nitrogen_ratio ;
   return  carbon_nitrogen_ratio;
}
//______________________________________________________________________________
              // Eventually make this function a member
float64 calc_cumulative_residue_incorporation_fraction(float64 layer_bottom_depth, float64 tillage_depth)
{  float64 ratio = layer_bottom_depth / tillage_depth;
   float64 cum_fraction =
      (ratio <= 0.6)
      ? 0.28 * exp(1.83 * ratio - 1.0)
      : 1 - 0.441 * pow(((1 - ratio) / 0.4) , 1.4);
   return cum_fraction;
}
//_2006-07-28_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Residues_V4_common::respond_to_field_operation                      // VB RedistributeResiduesAfterTillage()
(float32  tillage_op_depth_m                                        //VB  T_Depth = ManagementState.TillageDepth
,USDA::NRCS::RUSLE2::Soil_disturbance_effect    operation_soil_disturbance_effect       // VB Operation_Soil_Disturbance_Effect
,const float32  residue_flatten_ratio[RUSLE2_RESIDUE_TYPE_COUNT]
,const float32  residue_burial_ratio[RUSLE2_RESIDUE_TYPE_COUNT])     // 64 Residue_Fraction_Not_Incorporated = ManagementState.SurfaceResidueFractionRemainingAfterTillage
{  Unidirectional_list created_flattened_residue_pools;
//cout << "RMB:" << get_surface_all_biomass() << '\t' << get_subsurface_all_biomass() << endl;
   FOR_EACH_IN(potential_standing_stubble_residue_pool,Organic_biomatter_common,organic_matter_pools,each_standing_stubble) //090309
   {
      if (potential_standing_stubble_residue_pool->is_straw_or_manure_residue() &&
         (potential_standing_stubble_residue_pool->is_standing_stubble()))       //090309
      {  Organic_biomatter_common *stubble =  potential_standing_stubble_residue_pool;
         int RUSLE2_residue_type_index =  stubble->get_RUSLE2_residue_type() - 1;  // get_RUSLE2_residue_type() ranges from 1 (0 unknown is not used) but   residue_flatten_ratio is 0 index //090311
         if (RUSLE2_residue_type_index < 0) RUSLE2_residue_type_index = 0;  // If the crop did not specify the residue type, we just use the first one //090312
         // Reduce the stubble by fraction not transferred
         float64 flatten_ratio =residue_flatten_ratio[RUSLE2_residue_type_index];//090311
         Organic_biomatter_common *stubble_converted_to_flat =                   //070802
         stubble->clone();
         stubble_converted_to_flat->multiply_by(flatten_ratio);                  //070802
         stubble_converted_to_flat->set_position(OM_flat_surface_position);      //090413
         stubble_converted_to_flat->set_area_per_mass(stubble->get_area_per_mass() * 2.0 ); // area to mass ratio doubles when standing residues are flattened //070802
         stubble->multiply_by(1.0 - flatten_ratio);     
        #ifdef DETAILED_BALANCES
         if (residue_mass_balance[OM_flat_surface_position])                     //090408
             residue_mass_balance[OM_flat_surface_position]->flattened += stubble_converted_to_flat->kg();  //090407
         if (residue_mass_balance[OM_stubble_surface_position])                  //090408
             residue_mass_balance[OM_stubble_surface_position]->flattened += stubble_converted_to_flat->kg();  //090407
        #endif
         setup_contribution(*stubble_converted_to_flat);
         created_flattened_residue_pools.append(stubble_converted_to_flat);
      } // if is standing stubble
   } FOR_EACH_END(each_standing_stubble)
   // Transfer now so just flattend pools can be mixed, etc..
   organic_matter_pools.take_pools(created_flattened_residue_pools);             //070808

//070802 WARNING CANNOT JUST TRANSFER BECAUSE SINGLE POOLS ONLY HAS A SINGLE RESIDUE POOL
// NEED TO CREATE A FUNCTION FOR ALL DERIVED ORGANIC MATTER POOLS
// IN V4_4 this will simply transfer
// IN single pool, we will add to existing residue pools or
// if needed create a new residue pool correctly assocated with the organic matter pool for the layer

   Unidirectional_list new_mixed_pools;                                          //060808
   bool mixing_and_or_inversion = (operation_soil_disturbance_effect >= USDA::NRCS::RUSLE2::INVERSION_SOME_MIXING) && (operation_soil_disturbance_effect <= USDA::NRCS::RUSLE2::MIXING);   //060803
   if (mixing_and_or_inversion && (tillage_op_depth_m > 0.0))   // Normally the tillage op depth will be > 0 if mixing and/or inversion, but this is just extra check for input.
   {  nat8 last_tilled_layer = soil_layers.get_layer_at_depth(tillage_op_depth_m); //070828
      // This section calculates the "sifting" of residues (push down existing residues) by tillage
      // Calculate transfer coefficient
      soil_layer_array64(transfer_coefficient); clear_layer_array64(transfer_coefficient);
      float64 bottom_depth_layer_above = 0;
      for (nat8 layer = 1; layer <= last_tilled_layer; layer++)
      {  float64 bottom_depth_layer = soil_layers.get_depth_m(layer);
         float64 ratio = ((bottom_depth_layer + bottom_depth_layer_above) / 2.0) / tillage_op_depth_m;
         switch (operation_soil_disturbance_effect)
         {  case USDA::NRCS::RUSLE2::INVERSION_SOME_MIXING : transfer_coefficient[layer] = 0.6;                             break;// Inversion with some mixing
            case USDA::NRCS::RUSLE2::MIXING_SOME_INVERSION : transfer_coefficient[layer] = 1.0 - (0.7539 * ratio + 0.2413); break;// Mixing with some inversion
            case USDA::NRCS::RUSLE2::MIXING : transfer_coefficient[layer] = 1 - (0.55152 * ratio + 0.44667); break;// 'Mixing
            default: /*Note that there are other effects which are not currently handled here */ break;
         }
         bottom_depth_layer_above = bottom_depth_layer;
      }
      // Calculate residue mass transfer during "sifting"
      // Transfer subsurface residues (fast, low and lignified)
      for (nat8 /*Organic_matter_type */ residue_type= STRAW_RESIDUE
          ; residue_type <= MANURE_RESIDUE; residue_type++)
      {
         for (nat8 /*Organic_matter_cycling */ cycling= get_first_OM_cycling()
             ; cycling <= get_last_OM_cycling(); cycling++)
         {  Organic_biomatter_common *residue_in = 0;                            //070707
            for (nat8 layer = 1; layer <= last_tilled_layer; layer++)
            {  Organic_biomatter_common *sub_residue = find
                  ((Organic_matter_type)residue_type,OM_subsurface_position
                  ,(Organic_matter_cycling)cycling,layer);
               if (sub_residue)
               {  float64 residue_mass_layer = sub_residue->kg();              // VB Current_Pool_Residue_Mass = Residue_Pool(40 + i).ResidueMass
                  float64 residue_mass_out = residue_mass_layer * transfer_coefficient[layer];
                  // Note that for layer 1 residue_mass_in will be 0
                  if (residue_in)
                  {  sub_residue->add_different_mass(*residue_in);                                   // VB    Call AddMassToExistingResiduePool(40 + i, Residue_Mass_In, Residue_Pool(40 + i - 1).CarbonFraction, Residue_Pool(40 + i - 1).CNRatio, Residue_Pool(40 + i - 1).AreaToMassRatio)
                     #ifdef DETAILED_BALANCES
                     //130711 we dont bother with the detailed balance check (actually we should have a flag if we want the residue balance at all
                     if (residue_mass_balance[OM_subsurface_position])           //090408
                         residue_mass_balance[OM_subsurface_position]->added += residue_in->kg();  //090407
                    #endif
                  }
                  if (residue_mass_out > 0.0)
                  {  sub_residue->subtract_mass(residue_mass_out);
                     #ifdef DETAILED_BALANCES
                     //130711 we dont bother with the detailed balance check
                     if (residue_mass_balance[OM_subsurface_position])           //090408
                         residue_mass_balance[OM_subsurface_position]->removed += residue_mass_out;   //090407
                     #endif
                  }
                  residue_in // The residue in for the next layer is this layer's out
                     = (!CORN::is_approximately<float64>(residue_mass_out,0.0,0.000001))
                     ? sub_residue->clone()                         //111001 copy this layer's pool
                     : 0;
                  if (residue_in)
                  {  residue_in->reset_mass(residue_mass_out);         // and set it to the mass to be removed
                     setup_contribution(*residue_in);
                  }
               } else if (residue_in)
               {  new_mixed_pools.append(residue_in);
                  residue_in = 0;
               } // else residue_in (for next layer) is 0
            } // layer
         } // cycling
      } // residue type
   organic_matter_pools.take_pools(new_mixed_pools);                             //070808

//070802 WARNING CANNOT JUST TRANSFER BECAUSE SINGLE POOLS ONLY HAS A SINGLE RESIDUE POOL
// NEED TO CREATE A FUNCTION FOR ALL DERIVED ORGANIC MATTER POOLS
// IN V4_4 this will simply transfer
// IN single pool, we will add to existing residue pools or
// if needed create a new residue pool correctly assocated with the organic matter pool for the layer

      // This section calculates the incorporation of surface (flat) residues into the soil layers affected by tillage

      soil_layer_array64(surface_residue_mass_fraction_into); clear_layer_array64(surface_residue_mass_fraction_into);
      float64 factor
         = (operation_soil_disturbance_effect == USDA::NRCS::RUSLE2::MIXING_SOME_INVERSION /*2*/  ) ? 0.5
         : (operation_soil_disturbance_effect == USDA::NRCS::RUSLE2::MIXING /*3*/) ? 0.3
          /*operation_soil_disturbance_effect == 1*/: 1.0; // factor is not used in this case

      switch (operation_soil_disturbance_effect)
      {  case USDA::NRCS::RUSLE2::INVERSION_SOME_MIXING/* 1*/ : // Inversion with some mixing
         {  float64 layer_top_accumulation   = 0.0;
            float64 layer_bottom_accumulation= 0.0;
            for (nat8 layer = 1; layer < last_tilled_layer; layer++)   // dont included last tilled layer
            {  float64 layer_bottom_depth = soil_layers.get_depth_m(layer);
               layer_bottom_accumulation = calc_cumulative_residue_incorporation_fraction(layer_bottom_depth, tillage_op_depth_m);
               surface_residue_mass_fraction_into[layer] = layer_bottom_accumulation - layer_top_accumulation;
               layer_top_accumulation = layer_bottom_accumulation;
            } surface_residue_mass_fraction_into[last_tilled_layer] = 1.0 - layer_top_accumulation;
         } break;
         case USDA::NRCS::RUSLE2::MIXING_SOME_INVERSION/* 2*/ : // 'Mixing with some inversion (factor = 0.5)
         case USDA::NRCS::RUSLE2::MIXING/*3*/  : // 'Mixing                     (factor = 0.3)
         {  // The two modes are the same, they just have a different factor
            float64 prev_layer_bottom_depth = 0;
            for (nat8 layer = 1; layer < last_tilled_layer; layer++) // dont included last tilled layer
            {  float64 layer_bottom_depth = soil_layers.get_depth_m(layer);
               surface_residue_mass_fraction_into[layer]
                  = pow((layer_bottom_depth / tillage_op_depth_m) , factor)
                  - pow((prev_layer_bottom_depth / tillage_op_depth_m) , factor);
               prev_layer_bottom_depth = layer_bottom_depth; // setup for next layer
            }  surface_residue_mass_fraction_into[last_tilled_layer] = 1.0 - pow((prev_layer_bottom_depth / tillage_op_depth_m) , factor);
         } break;
         default : /* Other effects are negligible */ break;                     //090416
      } // switch operation_soil_disturbance_effect

      // Determine which residue pools are surface (flat) pools
      // (e.i., those with pool position = 0 (surface residue))
      // (We dont bury stubble)
      Unidirectional_list buried_flat_residues;
      FOR_EACH_IN(flat_surface_residue_pool,Organic_biomatter_common,organic_matter_pools,each_flat_surface_straw_or_manure)
      {
      if (flat_surface_residue_pool->is_straw_or_manure_residue() &&
         (flat_surface_residue_pool->is_flat_surface()))
      {
         float64 flat_surface_residue_pool_mass = flat_surface_residue_pool->kg();
         int RUSLE2_residue_type_index =  flat_surface_residue_pool->get_RUSLE2_residue_type() - 1;  // get_RUSLE2_residue_type() ranges from 1 (0 unknown is not used) but   residue_flatten_ratio is 0 index //090311
         if (RUSLE2_residue_type_index < 0) RUSLE2_residue_type_index = 0;  // If the crop did not specify the residue type, we just use the first one   //090312
         //                Pool_CN_Ratio = .CNRatio
         //                Pool_Carbon_Fraction = .CarbonFraction
         //                Pool_Position = .ResiduePosition
         //
         //                Pool_Decomposition_Constant = .DecompositionConstant
         //                Pool_Area_To_Mass_Ratio = .AreaToMassRatio
         //                Pool_Residue_Mass_Remaining = flat_surface_residue_pool_mass * residue_fraction_not_incorporated
         for (nat8 layer = 1; layer <= last_tilled_layer; layer++)
         {
            if (surface_residue_mass_fraction_into[layer] > 0.0)
            {
               float64 burial_ratio =  residue_burial_ratio[RUSLE2_residue_type_index] ;
               float64 surface_mass_fraction_into = surface_residue_mass_fraction_into[layer];
               float64 pool_residue_mass_to_soil_layer = flat_surface_residue_pool_mass *
                  burial_ratio * surface_mass_fraction_into;                     //060731
               Organic_biomatter_common *residue_from_surface_to_layer =         //070802
                  flat_surface_residue_pool->clone();                            //111001
               residue_from_surface_to_layer->reset_mass(pool_residue_mass_to_soil_layer);
               organic_matter_pools.C_incorporated_by_tillage += residue_from_surface_to_layer->get_carbon_kg();  //060817
               Organic_biomatter_common *existing_similar_residue_pool
               = find
                  (flat_surface_residue_pool->type
                  ,OM_subsurface_position
                  ,flat_surface_residue_pool->get_carbon_cycling()
                  ,layer);
               if (existing_similar_residue_pool)
               {  // We already have a residue pool in this layer with similar properties.
                  existing_similar_residue_pool->add_different_mass(*residue_from_surface_to_layer);
                  #ifdef DETAILED_BALANCES
                    //130711 we dont bother with the detailed balance check (actually we should have a flag if we want the residue balance at all
                  if (residue_mass_balance[OM_subsurface_position])   // Note, for subsurface, incorporated is what is added from the surface   //090408_
                      residue_mass_balance[OM_subsurface_position]->incorporated += residue_from_surface_to_layer->kg();   //090407
                  #endif
                  delete residue_from_surface_to_layer;
               } else // We need to add
               {  setup_contribution(*residue_from_surface_to_layer);            //060728
                  residue_from_surface_to_layer->set_position(OM_subsurface_position); // 090413 position = OM_subsurface_position;
                  residue_from_surface_to_layer->layer = layer;
                  buried_flat_residues.append(residue_from_surface_to_layer);
                  #ifdef DETAILED_BALANCES
                  //130711 we dont bother with the detailed balance check (actually we should have a flag if we want the residue balance at all
                  if (residue_mass_balance[OM_subsurface_position])    // Note, for subsurface, incorporated is what is added from the surface  //090408
                      residue_mass_balance[OM_subsurface_position]->incorporated += residue_from_surface_to_layer->kg();   //090407
                  #endif
               }
   //                        If Index = 52 Then 'Slow-cycling aboveground surface (flat) residue pools
   //                        If Pool_Exist(40 + i) Then
   //                                Call AddMassToExistingResiduePool(40 + i, pool_residue_mass_to_soil_layer, Pool_Carbon_Fraction, Pool_CN_Ratio, 999.9)
   //                                Else
   //                                Call AddResiduePool(i, pool_residue_mass_to_soil_layer, _
   //                                    Pool_Decomposition_Constant, Pool_CN_Ratio, _
   //                                    Pool_Carbon_Fraction, 999.9, True, 40 + i, SimConstants, OrganicResidueState, TimeState)
   //                            End If
   //                        ElseIf Index = 112 Then 'Lignified aboveground surface (flat) residue pools
   //                            If Pool_Exist(100 + i) Then
   //                                Call AddMassToExistingResiduePool(100 + i, pool_residue_mass_to_soil_layer, Pool_Carbon_Fraction, Pool_CN_Ratio, 999.9)
   //                                Else
   //                                Call AddResiduePool(i, pool_residue_mass_to_soil_layer, _
   //                                    Pool_Decomposition_Constant, Pool_CN_Ratio, _
   //                                    Pool_Carbon_Fraction, 999.9, True, 100 + i, SimConstants, OrganicResidueState, TimeState)
//                            End If
//                        ElseIf Index = 172 Then 'Fast-cycling aboveground surface (flat) residue pools
//                            If Pool_Exist(160 + i) Then
//                                Call AddMassToExistingResiduePool(160 + i, pool_residue_mass_to_soil_layer, Pool_Carbon_Fraction, Pool_CN_Ratio, 999.9)
//                                Else
//                                Call AddResiduePool(i, pool_residue_mass_to_soil_layer, _
//                                    Pool_Decomposition_Constant, Pool_CN_Ratio, _
//                                    Pool_Carbon_Fraction, 999.9, True, 160 + i, SimConstants, OrganicResidueState, TimeState)
//                            End If
//                        End If
               } // endif surface mass into this layer
            } // for layer
            // Reduce pool to remaining residue amount
            float64 burial_ratio = residue_burial_ratio[RUSLE2_residue_type_index]; //080303
            float64 reduction_fraction = (1.0 - burial_ratio);                      //060731
            #ifdef DETAILED_BALANCES
            float64 reduced_mass_for_balance = flat_surface_residue_pool->kg() * reduction_fraction;  //080303
            float64 mass_reduction =   flat_surface_residue_pool->kg() - reduced_mass_for_balance; //080303
            //130711 we dont bother with the detailed balance check (actually we should have a flag if we want the residue balance at all
            if (residue_mass_balance[flat_surface_residue_pool->position]) // Note for surface residues, incorporated is what is removed from the surface //090408
                residue_mass_balance[flat_surface_residue_pool->position]->incorporated += mass_reduction;  //090407
            #endif
            flat_surface_residue_pool->multiply_by(reduction_fraction);
         }
      }  FOR_EACH_END(each_flat_surface_straw_or_manure)
      organic_matter_pools.take_pools(buried_flat_residues);                     //070808
   }
   return true; // currently always performed
}
//_2006-07-28_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
Organic_biomatter_common *Residues_V4_common::find
(Organic_matter_type residue_type_to_find
,Organic_matter_position flat_or_stubble
,Organic_matter_cycling fast_slow_or_lignified_cycling
,nat8 layer_optional)
{  FIND_FOR_EACH_IN(found_residue,om_pool,Organic_biomatter_common,organic_matter_pools,true,each_residue)
   {  if (  (om_pool->type          == residue_type_to_find)
          &&(om_pool->position      == flat_or_stubble)
          &&(om_pool->get_carbon_cycling()== fast_slow_or_lignified_cycling)     //070707
          &&((layer_optional == 0) || (om_pool->layer == layer_optional)))
         found_residue = om_pool;
   } FOR_EACH_END(each_residue)
   return found_residue;
}
//_2006-07-27___________________________________________________________________

/*used for debugging
void Residues_V4_common::debug_put_everything_in_layer2()
{
   FOR_EACH_IN(residue_pool,Organic_biomatter_common,organic_matter_pools,each_residue)
   {
      if (residue_pool->is_straw_or_manure_residue())
      {
      residue_pool->position = OM_subsurface_position;
      residue_pool->layer = 2;
      }
   } FOR_EACH_END(each_residue)
}
*/



//080225 592 lines
//110928 712 lines
