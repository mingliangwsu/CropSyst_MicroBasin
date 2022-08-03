#error obsolete

#include <fstream>
#include "corn/math/compare.hpp"
#include "common/residue/residue_decomposition_param.h"
#include "common/residue/residues_interface.h"
#include "crop/crop_N_interface.h"
#include "crop/canopy_portion.h"
#include "crop/crop_canopy_biomass_GAI.h"
#include "crop/crop_biomass.h"
#include "crop/crop_types.hpp"
//___________________________________________________________________constructor
Canopy_biomass_GAI::Canopy_biomass_GAI
(
 #if (CS_VERSION==4)
 Senesced_biomass_fate              _senesced_biomass_fate_param
 #else
 Abscission                         _abscission                                  //110911
 #endif
,float64                             _regrowth_GAI                               //080222
,Residue_decomposition_parameters   &_residue_decomposition_params
,Residues_interface                 *_residues
,Crop_nitrogen_interface            *_nitrogen
,bool                                _is_continuous_grass)                       //080515
#if (CS_VERSION==4)
: canopy_vital                      (_senesced_biomass_fate_param,false)         //060911
, canopy_effete                     (_senesced_biomass_fate_param,true)          //060911
, senesced_biomass_fate_param       (_senesced_biomass_fate_param)               //060817
#else
: canopy_vital                      (_abscission,false)         //060911
, canopy_effete                     (_abscission,true)          //060911
, abscission                        (_abscission)                                //110911
#endif
, residue_decomposition_params      (_residue_decomposition_params)
, residues                          (_residues)
, nitrogen                          (_nitrogen)
, untouchable_portion               (0)                                          //071126
, regrowth_GAI                      (_regrowth_GAI)                              //080222
, is_continuous_grass               (_is_continuous_grass)                       //080515
, GAI_has_died_off (false) ,  resets(0)                                          //080415
{};
//___________________________________________________________________constructor
Canopy_biomass_GAI::~Canopy_biomass_GAI()
{  if (untouchable_portion) delete untouchable_portion; untouchable_portion = 0;
};
//___________________________________________________________________constructor
bool Canopy_biomass_GAI::is_valid()                            const
{  return(canopy_vital.accum_today!= 0)                                          //060911
      && (canopy_effete.accum_today!= 0)                                         //080314
      && (untouchable_portion != 0);                                             //071126
};
//___________________________________________________________________constructor
bool Canopy_biomass_GAI::take_portion                              modification_
(Canopy_portion  *todays_portion
,bool initial_restart_vital
,bool protect_it)
{  bool portion_valid = todays_portion &&  todays_portion->is_valid();
   if (portion_valid)
   {
      if (initial_restart_vital)
            untouchable_portion = todays_portion;
      else
      {  if (protect_it)
            canopy_vital.prepend(todays_portion);
         else
         {  if (untouchable_portion)
            {  // skim off some GAI for regrowth
               float64 more_GAI_needed_for_regrowth = regrowth_GAI - untouchable_portion->get_GAI();
               float64 portion_GAI = todays_portion->get_GAI();
               if ((more_GAI_needed_for_regrowth > 0.0) && (portion_GAI < more_GAI_needed_for_regrowth))
               {  untouchable_portion->increment_by(*todays_portion);
                  delete todays_portion; todays_portion = 0;
               }
               else
               {  // if started to senesce any GAI (Any GAI has died off)
                  // This is for the case when we have continuous
                  // annual grasses (Mike Rivington),
                  // the GAI curve was dipping down after peak LAI
                  // but then recovering
                  //080515 disabled
                  //080515    if (GAI_has_died_off && is_continuous_grass)
                  //080515    todays_portion->clear_GAI_related_biomass();
               }
            }
            if (todays_portion) // may be NULL if we added it to the untouchable portion
               canopy_vital.append(todays_portion);
         }
      }
   }
   else  delete todays_portion;
   invalidate();
   return portion_valid;
}
//_2008_______________________________________________________________take_portion_/
void Canopy_biomass_GAI::respond_to_clipping()                     modification_
{  GAI_has_died_off = false;
   // This allow continued accumulation of GAI related biomass
}
//_2008-05-15______________________________________________respond_to_clipping_/
void Canopy_biomass_GAI::restart()                                      mutates_
{  GAI_has_died_off = false;
   // This allow continued accumulation of GAI related biomass
}
//_2008-05-15______________________________________________respond_to_clipping_/
void Canopy_biomass_GAI::terminate()
{  // Makes the untouchable portion available for removal with biomass fate.
   if (untouchable_portion)
   {  canopy_vital.append(untouchable_portion);
      untouchable_portion = 0;
   }
}
//_2008-02-22_____________________________________________________take_portion_/
Canopy_biomass_GAI::Canopy::~Canopy()
{  if (accum_today) delete accum_today; accum_today= 0;
}
//_2006-09-11__________________________________________________________~Canopy_/
void Canopy_biomass_GAI::Canopy::invalidate()                           mutates_
{  if (accum_today)  delete accum_today;  accum_today= 0;
}
//_2006-09-11_______________________________________________Canopy::invalidate_/
void Canopy_biomass_GAI::invalidate()                                   mutates_
{
   canopy_vital.invalidate();
   canopy_effete.invalidate();
}
//_2006-09-11_______________________________________________________invalidate_/
void Canopy_biomass_GAI::age_by
(float64 daily_age_deg_day
,float64 leaf_duration_deg_day_f32)                        modification_
{  FOR_EACH_IN(vital_portion,Canopy_portion,canopy_vital,each_vital_portion)
   {  bool just_died = vital_portion->age_by(daily_age_deg_day,leaf_duration_deg_day_f32);
      if (just_died)
         GAI_has_died_off = true;
   } FOR_EACH_END(each_vital_portion);
   FOR_EACH_IN(effet_portion,Canopy_portion,canopy_effete,each_effete_portion)
   {  bool just_died = effet_portion->age_by(daily_age_deg_day,leaf_duration_deg_day_f32);
   } FOR_EACH_END(each_effete_portion)
   // Do not age untouchable portion.
   invalidate();
   if ((GAI_has_died_off && resets == 0) && is_continuous_grass)
   {  //go through and clear the GAI_related canopy biomasses for all vital portions

      // This is intended quickly replaced short lived leaves.
      // May need a parameter to enable this mode (I.e. any short lived grass)

      // 081108 We need to revisit if this is still necessary,
      // may be able to simply set stem leaf partion to 0.0???

      FOR_EACH_IN(vital_portion,Canopy_portion,canopy_vital,each_vital_portion)
         {  vital_portion->clear_GAI_related_biomass();
      } FOR_EACH_END(each_vital_portion)
      resets ++;
      GAI_has_died_off = false;
   }
}
//_2008_________________________________________________________________age_by_/
void Canopy_biomass_GAI::die_back(float64 fraction_to_die) modification_
{  // This sets the specified fraction of live biomass to effete
   // The biomass remains associated with the plant (it is not sent to residue)
   float64 GAI_remaining_to_die = get_GAI(include_vital|include_effete) * fraction_to_die;
   // Killing of effete first
   FOR_EACH_IN(effete_portion,Canopy_portion,canopy_effete,each_effete_portion)
   {  float64 GAI_this_portion = effete_portion->get_GAI();
      if (GAI_remaining_to_die > 0.0)
         effete_portion->die();
       GAI_remaining_to_die -= GAI_this_portion;
   } FOR_EACH_END(each_effete_portion);
   FOR_EACH_IN(vital_portion,Canopy_portion,canopy_vital,each_vital_portion)
   {  float64 GAI_this_portion = vital_portion->get_GAI();
      if (GAI_remaining_to_die > 0.0)
         vital_portion->die();
       GAI_remaining_to_die -= GAI_this_portion;
   } FOR_EACH_END(each_vital_portion);
   // do not die back untouchable_portion 071126_
   invalidate();
};
//____________________________________________________________________  die_back
float64 Canopy_biomass_GAI::Canopy::update()                 mutates_
{
   float64 sloughed_biomass = 0;                                                 //060816
   accum_today = new Canopy_portion;
   FOR_EACH(portion,Canopy_portion,each_portion)
   {
      if (portion && portion->is_dead())                                         //060824
      {  Days days_dead = portion->inc_days_dead();                              //060824
         #if (CS_VERSION==4)
         switch (senesced_biomass_fate_param)                                    //060824
         {  case senesced_biomass_linger :                                       //060824
         #else
         switch (abscission)                                                     //110911
         {  case semi_deciduous :                                                //110911
         #endif
            { if (days_dead > 90)                                                //060824
              {    sloughed_biomass += portion->slough();                        //060824
                  each_portion->detach_current();                                //070418
                  delete portion; portion = 0;                                   //070328
              };                                                                 //070328
            } break;                                                             //060824
            #if (CS_VERSION==4)
            case senesced_biomass_shed :                                         //060825
            #else
            case deciduous :                                                     //110911
            #endif
            {  if (from_previous_season)                                         //060824
               {  sloughed_biomass += portion->slough();                         //060824
                  each_portion->detach_current();                                //070418
                  delete portion; portion = 0;                                   //070328
               };                                                                //070328
            } break;                                                             //060824
        }; // end switch                                                         //060824
      }; // if is_dead                                                           //060824
      if (portion) // may be deleted if depleted above                           //060824
      {                                                                          //070328
         accum_today->increment_by(*portion);
      };                                                                         //070328
   } FOR_EACH_END(each_portion);
   return sloughed_biomass;
};
//________________________________________________________________Canopy::update
bool Canopy_biomass_GAI::update()                            mutates_
{
   invalidate();
   float64 vital_sloughed_biomass = canopy_vital.update();                       //060816
   if (vital_sloughed_biomass > 0.0 && residues)                                 //060824
      residues->add_surface_plant_pool                                           //060824
      (
       #if (CS_VERSION==4)
       (senesced_biomass_fate_param == senesced_biomass_linger)                  //040517
       #else
       (abscission == semi_deciduous)
       #endif
         ?  OM_flat_surface_position : OM_stubble_surface_position
      ,OM_ORIGINAL_CYCLING                                                       //060219
      ,vital_sloughed_biomass                                                    //______
NITRO ,nitrogen ? nitrogen->get_canopy_concentration(include_vital) : 0.0
      ,residue_decomposition_params                                              //060219
      ,0);                                                                       //060816
   float64 sloughed_biomass_effete =  canopy_effete.update();                    //060816
   if (sloughed_biomass_effete > 0.0 && residues)                                //060824
      residues->add_surface_plant_pool                                           //060824
      ((senesced_biomass_fate_param == senesced_biomass_linger)                  //040517
         ?  OM_flat_surface_position : OM_stubble_surface_position
      ,OM_ORIGINAL_CYCLING                                                       //060219
      ,sloughed_biomass_effete                                                   //______
NITRO ,nitrogen ? nitrogen->get_canopy_concentration(include_effete) : 0.0
      ,residue_decomposition_params                                              //060219
      ,0);                                                                       //060816
   // Do nothing to untouchable portion                                          //071126
   return true;                                                                  //080728
};
//________________________________________________________________________update
float64 Canopy_biomass_GAI::Canopy::remove_biomass
(float64 GAI_remaining_available
,float64 biomass_to_remove
,float64 retain_vital_GAI        // biomass won't be removed if it takes the GAI below this level
,bool remove_newest_first
,bool reserve_todays_history
) modification_
{
   if (CORN::is_approximately<float64>(biomass_to_remove,0.0,0.0000001)) return 0.0;
   float64 more_biomass_to_remove = biomass_to_remove;
   // Now loop through the GAI_ages from the tail and remove the newest leaves
   float64 act_removed_biomass = 0.0;
   //We can now either remove the newest biomass first or the oldest biomass first
   Canopy_portion  *curr_daily = 0;
   for (curr_daily = remove_newest_first ?(Canopy_portion *)pop_at_tail(): (Canopy_portion *)pop_at_head()
      ;(curr_daily && (more_biomass_to_remove > 0.0))
      ;curr_daily = remove_newest_first ?(Canopy_portion *)pop_at_tail(): (Canopy_portion *)pop_at_head())
   {
      float64 daily_canopy_biomass = curr_daily->get_biomass_current();
      float64 daily_GAI                     = curr_daily->get_GAI();
      bool need_to_retain_GAI = from_previous_season ? false :
           ((GAI_remaining_available - daily_GAI) < retain_vital_GAI);   // Don't allow the GAI to go below the limit
      if (!need_to_retain_GAI)
      {  if  (more_biomass_to_remove > daily_canopy_biomass)
         { //  Remove the whole daily bit
            more_biomass_to_remove -= daily_canopy_biomass;
            act_removed_biomass += daily_canopy_biomass;
            delete curr_daily; curr_daily = 0;
            GAI_remaining_available -= daily_GAI;
         } else // We just have a little bit left to remove, we just won't bother to do it
         {  float32 GAI_to_remove = curr_daily->get_GAI() * more_biomass_to_remove / curr_daily->get_biomass_current();
            curr_daily->dec_green_area_index(GAI_to_remove);
            GAI_remaining_available -= GAI_to_remove;
            curr_daily->dec_biomass_current(more_biomass_to_remove);
            act_removed_biomass += more_biomass_to_remove;
            more_biomass_to_remove = 0.0;
         }
      }
   }
   if (curr_daily )
   {  // We had a tad left so we need to push it back onto the list
      if  (remove_newest_first)
            append(curr_daily);
      else  prepend(curr_daily);
   }
   invalidate();
   // remove biomass N is now processed with biomatter fate
 return act_removed_biomass;
}
//_2004-06-23_2006_2007_2007____________________________________remove_biomass_/
float64 Canopy_biomass_GAI::remove_biomass
(float64 biomass_to_remove       // don't pass by reference even though it is decremented locally
,float64 retain_vital_GAI        // biomass won't be removed if it takes the GAI below this level
,bool remove_newest_first
,bool reserve_todays_history
,Crop_biomass &accumulated_removed_biomass // Return about of biomass removed
)   modification_
{
   float64 vital_GAI_remaining_available = get_GAI(include_vital);
   float64 effete_GAI_remaining_available = get_GAI(include_effete);
   float64 act_effete_removed_biomass = canopy_effete.remove_biomass(effete_GAI_remaining_available,biomass_to_remove,retain_vital_GAI,remove_newest_first,  reserve_todays_history);
   biomass_to_remove -= act_effete_removed_biomass;
   float64 act_vital_removed_biomass = canopy_vital.remove_biomass(vital_GAI_remaining_available,biomass_to_remove,retain_vital_GAI,remove_newest_first,  reserve_todays_history);
   biomass_to_remove -= act_vital_removed_biomass;
   // At this point biomass_to_remove should be 0.0 if the specified biomass exists
   // otherwise the requested amount was not available.
   float64 act_removed_biomass = act_effete_removed_biomass + act_vital_removed_biomass;
      float64 act_removed_N_mass = 0;
   if (nitrogen)
   {
      float64 act_vital_removed_N_mass    = nitrogen->remove_canopy_nitrogen_for(act_vital_removed_biomass ,include_vital);
      float64 act_effete_removed_N_mass   = nitrogen->remove_canopy_nitrogen_for(act_effete_removed_biomass,include_effete);
      act_removed_N_mass = act_vital_removed_N_mass + act_effete_removed_N_mass;
   }
   Crop_biomass removed_now(act_removed_biomass,act_removed_N_mass);
   accumulated_removed_biomass.add_crop_biomass(removed_now);
   // remove biomass N is now processed with biomatter fate
   // The untouchable_portion is not removable
   return act_removed_biomass;
}
//_2004-06-23_2006_2007_________________________________________remove_biomass_/
float64 Canopy_biomass_GAI::remove_all_biomass
(Crop_biomass &accumulated_removed_biomass)                        modification_
{
   // This removes all canopy biomass from the plant (I.e. in the case of termination)
   // Returnsabout of biomass removed
   float64 act_effete_removed_biomass = canopy_effete.remove_biomass(999999.0,999999.0,0,true,  false);
   float64 act_vital_removed_biomass = canopy_vital.remove_biomass(999999.0,999999.0,0,true,  false);
   // the untouchable portion is not removable
   float64 act_removed_biomass = act_effete_removed_biomass + act_vital_removed_biomass;
   float64 act_removed_N_mass    = 0;
   if (nitrogen)
   {  float64 act_removed_N_mass    = nitrogen->remove_canopy_nitrogen_for(999999.0 ,include_vital|include_effete);
   };
   Crop_biomass removed_now(act_removed_biomass,act_removed_N_mass);
   accumulated_removed_biomass.add_crop_biomass(removed_now);
   invalidate();
 return act_removed_biomass;
}
//_2007-06-27_______________________________________________remove_all_biomass_/
float64 Canopy_biomass_GAI::get_GAI(uint8 include_GAI)                     const
{  if (!is_valid()) update();
   float64 GAI_vital  = (include_GAI & include_vital)  ? canopy_vital.accum_today->get_GAI() : 0.0;
   float64 GAI_effete = (include_GAI & include_effete) ? canopy_effete.accum_today->get_GAI() : 0.0;
   float64 GAI_untouchable = (include_GAI & include_vital)  && untouchable_portion ? untouchable_portion->get_LAI() : 0.0;
   return GAI_vital + GAI_effete + GAI_untouchable;
}
//_____________________________________________________________________get_GAI_/
float64 Canopy_biomass_GAI::get_LAI()                                      const
{  if (!is_valid()) update();
   float64 sum_LAI
      = canopy_vital.accum_today->get_LAI()
      + canopy_effete.accum_today->get_LAI()
      + (untouchable_portion ? untouchable_portion->get_LAI() : 0.0);
   return sum_LAI;
}
//_2006-08-24__________________________________________________________get_LAI_/
float64 Canopy_biomass_GAI::get_biomass_current(uint8 include_biomass)     const
{  if (!is_valid()) update();
   bool include_dead = include_biomass & include_canopy_dead;
   float64 biomass_current_vital = (include_biomass & include_vital) ? canopy_vital.accum_today->get_biomass_current() : 0.0;
   float64 biomass_current_effete =(include_biomass & include_effete) ?  canopy_effete.accum_today->get_biomass_current() : 0.0;
   float64 biomass_untouchable = (include_biomass & include_vital) && untouchable_portion ? untouchable_portion->get_biomass_current() : 0.0;
   return biomass_current_vital + biomass_current_effete + biomass_untouchable;
}
//_2007____________________________________________________get_biomass_current_/
float64 Canopy_biomass_GAI::get_biomass_produced(uint8 include_biomass) const
{  if (!is_valid()) update();
   float64 biomass_produced_vital = (include_biomass & include_vital) ? canopy_vital.accum_today->get_biomass_produced() : 0.0;
   float64 biomass_produced_effete =(include_biomass & include_effete) ?  canopy_effete.accum_today->get_biomass_produced() : 0.0;
   float64 biomass_untouchable = (include_biomass & include_vital) && untouchable_portion ? untouchable_portion->get_biomass_produced() : 0.0;
   return biomass_produced_vital + biomass_produced_effete + biomass_untouchable;
}
//_2007___________________________________________________get_biomass_produced_/
float64 Canopy_biomass_GAI::get_GAI_related_biomass() const
{  if (!is_valid()) update();
   float64 GAI_related_biomass_vitale     = canopy_vital.accum_today->get_GAI_related_biomass() ;
   float64 GAI_related_biomass_effete     = canopy_effete.accum_today->get_GAI_related_biomass();
   float64 GAI_related_biomass_untouchable= untouchable_portion ? untouchable_portion->get_GAI_related_biomass() : 0.0;
   return
   //080515 disabled  (GAI_has_died_off && is_continuous_grass) ? 0.0 :
      GAI_related_biomass_vitale + GAI_related_biomass_effete + GAI_related_biomass_untouchable; // Note the effete may already be 0
}
//_______________________________________________________get_GAI_related_biomass
#ifdef CO2_CHANGE
float64 Canopy_biomass_GAI::get_GAI_at_baseline_ppm() const
{  if (!is_valid()) update();
   float64 GAI_at_baseline_ppm = 0.0;
   GAI_at_baseline_ppm += canopy_vital.accum_today->get_GAI_at_baseline_ppm();
   GAI_at_baseline_ppm += canopy_effete.accum_today->get_GAI_at_baseline_ppm();
   GAI_at_baseline_ppm +=  untouchable_portion ? untouchable_portion->get_GAI_at_baseline_ppm() : 0.0;
   return GAI_at_baseline_ppm;
};
//_2007-11-26__________________________________________get_GAI_at_baseline_ppm_/
float64 Canopy_biomass_GAI::get_GAI_related_biomass_at_baseline_ppm() const
{  if (!is_valid()) update();
   float64 GAI_related_biomass_at_baseline_ppm = 0;
   GAI_related_biomass_at_baseline_ppm += canopy_vital.accum_today->get_GAI_related_biomass_at_baseline_ppm();
   GAI_related_biomass_at_baseline_ppm += canopy_effete.accum_today->get_GAI_related_biomass_at_baseline_ppm();
   GAI_related_biomass_at_baseline_ppm += untouchable_portion ? untouchable_portion->get_GAI_related_biomass_at_baseline_ppm() : 0.0;
   return  GAI_related_biomass_at_baseline_ppm ;
};
//_2007-11-26___________________get_GAI_related_canopy_biomass_at_baseline_ppm_/
#endif
float64 Canopy_biomass_GAI::get_live_green_biomass(bool include_vital,bool include_effete) const
{  // Note, could make the live_biomass a property of portion
 // and simply add this with the reset or update()
   if (!is_valid()) update();                                                    //060316
   float64 live_biomass = 0.0;  // kg_m2
   if (include_vital)                                                            //060911
   {
      FOR_EACH_IN(portion,Canopy_portion ,canopy_vital,each_portion)
      {  if (!portion->is_dead()) // obs caller should make sure senescence does not apply duration already checked to determine if dead(then don't call this function) (parameters->has_leaf_senescence()  && (curr_daily->age > parameters->leaf_duration_deg_day_f32))
         live_biomass += portion->get_biomass_current();  // produced and current should be the same for live  //060601
      } FOR_EACH_END(each_portion);
      live_biomass += untouchable_portion ? untouchable_portion->get_biomass_current() : 0.0;   //071126
   };
   if (include_effete)                                                           //060911
   FOR_EACH_IN(portion,Canopy_portion ,canopy_effete,each_portion)
   {  if (!portion->is_dead()) // obs caller should make sure senescence does not apply duration already checked to determine if dead(then don't call this function) (parameters->has_leaf_senescence()  && (curr_daily->age > parameters->leaf_duration_deg_day_f32))
      live_biomass += portion->get_biomass_current();  // produced and current should be the same for live  //060601
   } FOR_EACH_END(each_portion);
 return live_biomass;
};
//_2006-03-13___________________________________________get_live_green_biomass_/
float64 Canopy_biomass_GAI::get_live_and_or_dead_biomass(bool include_vital,bool include_effete,bool include_dead) const
{  // Note, could make the live_biomass a property of portion
 // an simply add this with the reset or update()
   if (!is_valid()) update();
   float64 biomass = 0.0;  // kg_m2
   FOR_EACH_IN(portion,Canopy_portion ,canopy_vital,each_vital_portion)
   {
      if (include_dead && portion->is_dead())
         biomass += portion->get_biomass_current();  // produced and current should be the same for live
      if (include_vital && (portion->get_GAI() > 0.0000001))
         biomass += portion->get_biomass_current();  // produced and current should be the same for live
   } FOR_EACH_END(each_vital_portion);
   FOR_EACH_IN(portion,Canopy_portion ,canopy_effete,each_effete_portion)
   {
      if (include_dead && portion->is_dead())
         biomass += portion->get_biomass_current();  // produced and current should be the same for live
      if (include_effete && (portion->get_GAI() > 0.0000001))
         biomass += portion->get_biomass_current();  // produced and current should be the same for live
   } FOR_EACH_END(each_effete_portion);
   biomass += untouchable_portion ? untouchable_portion->get_biomass_current() : 0.0; //071126
   return biomass;
};
//_2006-09-07___________________________________________get_live_green_biomass_/
bool Canopy_biomass_GAI::end_season(bool apply_dormancy)           modification_ //080401
{  // At this point there may be some effete portions from previous years that have been exhausted they can be cleaned now
   while (Canopy_portion *portion = (Canopy_portion*)canopy_vital.pop_at_head()) //060911
   {  if (apply_dormancy)                                                        //080401
         portion->dormancy();                                                    //060911
      canopy_effete.append(portion);                                             //060911
   }
   return true;
}
//_2006-08-25_________________________________________________________dormancy_/
void Canopy_biomass_GAI::dump_ages(std::ofstream &tostream)
{  static nat32 day=0;
   day++;
   if (canopy_effete.count())
   {
      tostream << "day" <<'\\t'<< (int)day << " effete:\n";
      FOR_EACH_IN(effete_portion,Canopy_portion ,canopy_effete,each_effete_portion)
         effete_portion->write(tostream);
      FOR_EACH_END(each_effete_portion);
   }
   tostream << "day" << '\\t' << (int)day << "vital:\n";
   FOR_EACH_IN(vital_portion,Canopy_portion ,canopy_vital,each_vital_portion)
         vital_portion->write(tostream);
   FOR_EACH_END(each_vital_portion);
   if (untouchable_portion)                                                      //071126
      tostream << "untouchable portion:\nUa=" << (int)untouchable_portion << "\t"<< untouchable_portion->get_age() << " GAI=" << untouchable_portion->get_GAI()<< " BM=" << untouchable_portion->get_biomass_current();
   tostream << std::endl;
};
//_2007-07-05________________________________________________________dump_ages_/
// 060911 350 lines
// 070806 488 lines
// 080727 537 lines

