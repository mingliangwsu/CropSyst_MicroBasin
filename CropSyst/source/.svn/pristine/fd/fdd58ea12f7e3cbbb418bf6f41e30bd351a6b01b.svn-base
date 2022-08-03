
#include "options.h"
#include "crop/crop_interfaced.h"
#include "crop/crop_N_interface.h"
#include "crop/phenology_interface.h"
#include "soil.h"
#include "pond.h"
#include "cs_accum.h"
#include "soil/erosion_RUSLE.h"
#include "common/residue/residues_interface.h"
#include "soil/chemicals_profile.h"
#include "soil/chemical_balance.h"
#include "corn/measure/measures.h"
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#ifndef biomassH
#  include "common/biomatter/biomass.h"
#endif
#include "cs_UED_season.h"
#include "csvc.h"
#include "csvc_special.h"
#ifdef LADSS_MODE
extern uint16 LADSS_harvest_sequence;                                            //020923
#endif

#include "crop/crop_cropsyst.h"

//______________________________________________________________________________
// These are special for REACCH
/*
3 3 22 2222 2211 1111 1111 11
1 0 98 7654 3210 9876 5432 1098 7654 3210
- - -- ---- ---- ---- ---- ---- ---- ----

1 1 00 1110 0001 0001 0001 0111 0000 0000  (0xCE111700)
*/

#define CSVP_soil_base_water_depth_initial  0xCE111700
// deriviation :
// CSV      = CSVP_soil_base_water_depth
// qualifier= UED_period_init
// nonstandard
// layer

#define CSVP_soil_base_water_depth_final    0xC0111700
// deriviation :
// CSV      = CSVP_soil_base_water_depth
// qualifier= at timestep (final date)
// nonstandard
// layer

#define CSVC_soil_N_N_amount_initial         0xcE131000
#define CSVC_soil_N_N_amount_final           0xc0131000
//______________________________________________________________________________
Season_data_record::Season_data_record()
: CORN::Data_record(season_section)
,  crop_name()
,  s_out_ID(0)
,  alloc_ID(0)
,  land_use_ID(0)                                                                //030331
,  planting_date()                                                               //041205
,  restart_date()                                                                //041205
,  emergence_date()
,  flowering_date()
,  tuber_init_date()                                                             //081111
,  grain_filling_date()
,  peak_LAI_date()
,  maturity_date()
,  harvest_date()
#ifdef CROP_ORCHARD
,  bud_break_date()                                                              //081013
,  initial_fruit_growth_date()                                                   //081013
,  rapid_fruit_growth_date()                                                     //081013
,  chill_requirement_satisfied_date()                                            //081013
,  fruit_canopy_biomass(0)                                                       //091104
,  nonfruit_canopy_biomass(0)                                                    //091104
#endif
,  inactive_begin_date()                                                         //081013
,  inactive_end_date()                                                           //081013
,  peak_LAI(0)
,  yield(0)
,  used_biomass(0)
,  grazed_biomass(0)
,  residue_biomass(0)
,  disposed_biomass(0)
,  dry_biomass(0)
,  daytime_VPD_avg(0)
,  intercepted_PAR_accum(0)
,  root_depth(0)
,  root_biomass(0)                                                               //091104
,  surface_residue_biomass(0)
,  surface_plant_residue_biomass(0)                                              //091104
,  surface_manure_biomass(0)                                                     //091104
,  incorporated_residue(0)                                                       //091104
,  incorporated_plant_residue(0)
,  incorporated_manure(0)
,  erosion_index(0)
,  soil_loss(0)
,  ET_pot(0)
,  ET_act(0)
,  ET_ref(0)                                                                     //130723
,  transp_pot(0)
,  transp_act(0)
,  evap_soil_pot(0)
,  evap_soil_act(0)
,  evap_residue_pot(0)
,  evap_residue_act(0)
,  irrig(0)
,  precip(0)
,  air_temp_avg_mean(0)                                                          //160324
,  crop_water_intrcpt_today(0)      // remove _today                             //160419
,  residue_water_intrcpt(0)
,  surface_water_runoff(0)
,  ponded_water(0)
,  water_enter_soil(0)
,  soil_water_drainage(0)
,  soil_water_profile_init(0)                                                    //151227
,  soil_water_profile_final(0)                                                   //151227
,  soil_available_water_15_init  (0)                                             //160601
,  soil_available_water_15_final (0)                                             //160601
,  avg_water_stress_index(0)
,  avg_temperature_stress_index(0)
,  avg_flower_temperature_stress_index(0)                                        //091103
#ifdef NITROGEN
,  N_leached(0)
,  N_total_applied(0)
,  N_auto_uptake(0)
,  N_available(0)
,  N_mineralized_residue(0)
,  N_mineralized_org_fert(0)
,  N_mineralized_OM(0)
,  N_immobilization(0)
,  N_mineralization(0)
,  N_inorganic_applied(0)
,  N_organic_applied(0)
,  N_organic_gaseous_loss(0)
,  N_inorganic_gaseous_loss(0)
,  N_fixation(0)

,  N_stress_index_avg(0)
,  N_uptake(0)
,  N_mass_canopy(0)                                                              //070209
,  N_mass_yield(0)                                                               //120117

,  N_max_expected_conc_at_flowering       (0)                                    //061213
,  N_max_expected_conc_at_maturity        (0)                                    //061213
,  N_max_expected_conc_flower_mature_ratio(0)                                    //061213
,  N_uptake_excess_or_deficit             (0)                                    //061213
,  nitrification                          (0)                                    //110917
,  denitrification                        (0)
,  N_soil_profile_initial                 (0)                                    //161130
,  N_soil_profile_final                   (0)
,  N_N2O_loss_denitrification             (0)                                    //150624
,  N_N2O_loss_nitrification               (0)                                    //150624
#endif
#ifdef PHOSPHORUS
,  P_applied(0)                                                                  //110801
,  P_uptake(0)                                                                   //110801
,  P_soil_profile(0)                                                             //110801
#endif
{}
//_____________________________________________Constructor Season_data_record__/
void Season_data_record::clear()
{  crop_name.assign("");
  s_out_ID=0;
  alloc_ID=0;
  land_use_ID=0;

#ifdef CROP_ORCHARD

  fruit_canopy_biomass=0;
  nonfruit_canopy_biomass=0;
#endif
  peak_LAI=0;
  yield=0;
  used_biomass=0;
  grazed_biomass=0;
  residue_biomass=0;
  disposed_biomass=0;
  dry_biomass=0;
  daytime_VPD_avg=0;
  intercepted_PAR_accum=0;
  root_depth=0;
  root_biomass=0;
  surface_residue_biomass=0;
  surface_plant_residue_biomass=0;
  surface_manure_biomass=0;
  incorporated_residue=0;
  incorporated_plant_residue=0;
  incorporated_manure=0;
  erosion_index=0;
  soil_loss=0;
  ET_pot=0;
  ET_act=0;
  ET_ref=0;                                                                      //130723
  transp_pot=0;
  transp_act=0;
  evap_soil_pot=0;
  evap_soil_act=0;
  evap_residue_pot=0;
  evap_residue_act=0;
  irrig=0;
  precip=0;
  air_temp_avg_mean = 0;                                                         //160324
  crop_water_intrcpt_today =0;  // remove_today  160419
  residue_water_intrcpt=0;
  surface_water_runoff=0;
  ponded_water=0;
  water_enter_soil=0;
  soil_water_drainage=0;
  soil_water_profile_init = 0;                                                   //151227
  soil_water_profile_final = 0;                                                  //151227

  soil_available_water_15_init   = 0;                                            //160601
  soil_available_water_15_final  = 0;                                            //160601

  avg_water_stress_index=0;
  avg_temperature_stress_index=0;

  avg_flower_temperature_stress_index=0;

#ifdef NITROGEN
  N_leached=0;
  N_total_applied=0;
  N_auto_uptake=0;
  N_available=0;
  N_mineralized_residue=0;
  N_mineralized_org_fert=0;
  N_mineralized_OM=0;
  N_immobilization=0;
  N_mineralization=0;
  N_inorganic_applied=0;
  N_organic_applied=0;
  N_organic_gaseous_loss=0;
  N_inorganic_gaseous_loss=0;
  N_fixation=0;

  N_stress_index_avg=0;
  N_uptake=0;
  N_mass_canopy=0;
  N_mass_yield =0;                                                               //120117

  N_max_expected_conc_at_flowering        =0;
  N_max_expected_conc_at_maturity         =0;
  N_max_expected_conc_flower_mature_ratio =0;
  N_uptake_excess_or_deficit              =0;
  nitrification                           =0;                                    //110917
  denitrification                         =0;
  N_soil_profile_initial                  =0;                                    //161130
  N_soil_profile_initial                  =0;
  N_N2O_loss_denitrification              =0;                                    //150624
  N_N2O_loss_nitrification                =0;                                    //150624
#endif
#ifdef PHOSPHORUS
  P_uptake=0;
  P_applied=0;
  P_soil_profile=0;
#endif
}
//_2011-01-15__________________________________________________________________/
void Season_data_record::update
(const CropSyst::Crop_interfaced &crop                                           //131008_130717
,const CropSyst::Soil &soil
,CropSyst::Period_accumulators    *GP_accumulators
#ifdef NITROGEN
,Chemical_balance_accumulators  *NO3_GP_bal_accums // 0 if not simulating N      //050114
,Chemical_balance_accumulators  *NH4_GP_bal_accums // 0 if not simulating N      //050114
#endif
,CropSyst::Pond          &pond                                                   //130308_040921
,Residues_interface      *residue_pools_kg_m2 // rename this to residues_kg_m2   //050726
,int32                    _alloc_ID)  // Only for LADSS
{
#ifdef LADSS_MODE
   s_out_ID = (int32)_alloc_ID * (int32)10000 + (int32)LADSS_harvest_sequence ; // Note, this now actually generated by Oracle
#endif
   alloc_ID = _alloc_ID;
   land_use_ID = crop.get_LADSS_land_use_ID();
   crop_name.assign(crop.get_description());
   planting_date.set(crop.get_planting_date());                                  //041205
   restart_date.set(crop.get_restart_date());                                    //041205
   emergence_date.set(crop.get_emergence_date());
   flowering_date.set(crop.get_flowering_date());
   tuber_init_date.set(crop.get_tuber_init_date());                              //081111
   grain_filling_date.set(
#ifdef CROP_ORCHARD
          (crop.get_crop_model() == CROPSYST_ORCHARD_MODEL)
          ? crop.get_initial_fruit_growth_date() :
#endif
          crop.get_grain_filling_date());
   peak_LAI_date.set(crop.ref_GAI_max_date());                                   //180413
   //180413 peak_LAI_date.set(crop.get_largest_GAI_date());
   maturity_date.set(crop.get_maturity_date());
   harvest_date.set(crop.get_harvest_date());
   const Crop_mass_fate *biomass_fate_season = crop.get_biomass_fate_season();   //150803_040920
#ifdef CROP_ORCHARD
   bud_break_date.set(crop.get_bud_break_date());                                //081013
   initial_fruit_growth_date.set(crop.get_initial_fruit_growth_date());          //081013
   rapid_fruit_growth_date.set(crop.get_rapid_fruit_growth_date());              //081013
   chill_requirement_satisfied_date.set(crop.get_chill_requirement_satisfied_date());  //081013
   if (biomass_fate_season)                                                      //051228
   {  // if in dormancy there might not be biomass_fate_season;
      fruit_canopy_biomass       = biomass_fate_season->yield;                   //091104
      nonfruit_canopy_biomass    = biomass_fate_season->uncut_canopy;            //091104
   }
#endif
   inactive_begin_date.set(crop.get_inactive_begin_date());                      //081013
   inactive_end_date.set(crop.get_inactive_end_date());                          //081013
   peak_LAI                            = crop.get_peak_LAI(true);                //040930
   if (biomass_fate_season)                                                      //051228
   {  // if in dormancy there might not be biomass_fate_season;                  //051228
      yield             = biomass_fate_season->yield;                            //041001
      used_biomass      = biomass_fate_season->useful;                           //040920
      grazed_biomass    = biomass_fate_season->get_removed_for_grazing();        //040920
      residue_biomass   = biomass_fate_season->chaff_or_leaf_litter + biomass_fate_season->stubble_dead; //040920
      disposed_biomass  = biomass_fate_season->disposal;                         //040920
   }
   dry_biomass                         = crop.get_total_season_biomass_production_kg_m2();
   daytime_VPD_avg                     = crop.get_VPD_daytime_mean();
   intercepted_PAR_accum               = crop.get_intercepted_PAR_season_accum_MJ_m2();
   root_depth                          = crop.get_recorded_root_depth_m();       //160531
           //160531 crop.get_root_length_m() + soil.ref_layers()->get_thickness_m(1); //150424
   root_biomass                        = crop.get_act_root_biomass_kg_m2();      //091104
   #ifdef RESIDUES
   if (residue_pools_kg_m2)
   {  surface_residue_biomass             = residue_pools_kg_m2->get_surface_all_biomass();  // Perhaps replace with:  residue_pools_kg_m2->get_biomass_output(INCLUDE_POSITION_FLAT_SURFACE|INCLUDE_POSITION_STUBBLE_SURFACE,(INCLUDE_STRAW_RESIDUE_OM | INCLUDE_MANURE_RESIDUE_OM)   //050726
      surface_plant_residue_biomass       = residue_pools_kg_m2->get_biomass_output(INCLUDE_POSITION_FLAT_SURFACE|INCLUDE_POSITION_STUBBLE_SURFACE,INCLUDE_STRAW_RESIDUE_OM); //091104
      surface_manure_biomass              = residue_pools_kg_m2->get_biomass_output(INCLUDE_POSITION_FLAT_SURFACE|INCLUDE_POSITION_STUBBLE_SURFACE,INCLUDE_MANURE_RESIDUE_OM);//091104
      incorporated_residue                = residue_pools_kg_m2->get_biomass_output(INCLUDE_POSITION_SUBSURFACE,INCLUDE_STRAW_RESIDUE_OM|INCLUDE_MANURE_RESIDUE_OM);          //091104
      incorporated_plant_residue          = residue_pools_kg_m2->get_subsurface_plant_biomass();// Perhaps replace with: residue_pools_kg_m2->get_biomass_output(INCLUDE_POSITION_SUBSURFACE,INCLUDE_STRAW_RESIDUE_OM)
      incorporated_manure                 = residue_pools_kg_m2->get_subsurface_manure_biomass(); //  Perhaps replace with: residue_pools_kg_m2->get_biomass_output(INCLUDE_POSITION_SUBSURFACE,INCLUDE_MANURE_RESIDUE_OM)
      // 091105 I may need to get these from organic matter residues pool
      if (GP_accumulators)                                                       //091202
      {  N_mineralized_residue  = GP_accumulators->straw_mineralization_V4_1 ;   //091104
         N_mineralized_org_fert = GP_accumulators->manure_mineralization_V4_1;   //091104
      }
   }
   #endif
   if (soil.erosion)
   {  erosion_index                    = soil.erosion->C_factor_tally.get_sum() * 10.0 ;  // Not sure why multiply by 10   //0505
      soil_loss                        = soil.erosion->total_soil_loss ;
   } else
   {  erosion_index                    = 0.0;
      soil_loss                        = 0.0;
   }
   if (GP_accumulators)                                                          //070612
   {  ET_pot                     =GP_accumulators->pot_evapotranspiration;
      ET_act                     =GP_accumulators->act_evapotranspiration;
      ET_ref                     =GP_accumulators->ref_evapotranspiration;       //130723
      transp_pot                 =GP_accumulators->pot_transpiration;
      transp_act                 =CORN::must_be_greater_or_equal_to<float32>
                                    (GP_accumulators->act_transpiration,0);
      evap_soil_pot              =GP_accumulators->pot_soil_evaporation;
      evap_soil_act              =GP_accumulators->act_soil_evaporation;
      evap_residue_pot           =GP_accumulators->pot_residue_evaporation;
      evap_residue_act           =GP_accumulators->act_residue_evaporation;
      irrig                      =GP_accumulators->irrigation;
      precip                     =GP_accumulators->precip_m;
      air_temp_avg_mean          =GP_accumulators->air_temperature_stats.provide_arithmetic_mean(); //1603224
      crop_water_intrcpt_today   =GP_accumulators->crop_intercept;               //160419
      //160419 crop_water_intrcpt_stored                  =GP_accumulators->crop_intercept_stored; //160414
      //160414crop_water_intrcpt                  =GP_accumulators->crop_intercept;
      residue_water_intrcpt               =GP_accumulators->residue_interception;
      surface_water_runoff                =GP_accumulators->runoff;
      water_enter_soil                    =GP_accumulators->act_water_entering_soil;
      soil_water_drainage                 =GP_accumulators->reported_drainage;
   }
   // soil_water_profile_init is setup in clear


   soil_water_profile_final      = soil.ref_hydrology()->provide_water_depth_profile(true); //160412_151227
   soil_available_water_15_final = soil.ref_hydrology()->calc_available_water_depth_to(1.5); //160601

   ponded_water                 = pond.get_depth();
   avg_water_stress_index       = crop.get_water_stress_index_mean();
   avg_temperature_stress_index = crop.get_temperature_stress_index_mean();

#ifdef NITROGEN
   N_leached = 0.0;                                                              //050114
   N_total_applied = 0.0;                                                        //050114
   N_inorganic_applied = 0.0;                                                    //160323
   if (NO3_GP_bal_accums && NH4_GP_bal_accums)                                   //050114
   {
      N_leached = NO3_GP_bal_accums->get_reported_leached(true)                  //981230
                 +NH4_GP_bal_accums->get_reported_leached(true);                 //981230
      N_inorganic_applied                                                        //160323
         = NO3_GP_bal_accums->get_applied(true)
          +NH4_GP_bal_accums->get_applied(true);
      N_total_applied = N_inorganic_applied + N_organic_applied;                 //160323
      float64 GP_accum_N_fert_requirements = GP_accumulators? GP_accumulators->N_fert_requirements : 0.0;   //070612
      N_auto_uptake        = GP_accum_N_fert_requirements;
      N_available                  =
         (NO3_GP_bal_accums->get_original_profile_content(true)
         +NH4_GP_bal_accums->get_original_profile_content(true)
         +NH4_GP_bal_accums->get_transformed_from(true)//{ GP_mineralization}
         +NO3_GP_bal_accums->get_applied(true)
         +NH4_GP_bal_accums->get_applied(true)
         +GP_accum_N_fert_requirements);
      if (GP_accumulators)                                                       //070612
      {  N_mineralized_OM           = GP_accumulators->OM_N_mineralization;      //970814
         N_immobilization           = GP_accumulators->N_immobilization;         //040209
         N_mineralization           = GP_accumulators->OM_N_mineralization;      //970814
         N_total_applied            = GP_accumulators->total_N_applied;          //160323
         N_inorganic_applied        = GP_accumulators->inorganic_N_applied;      //160323
         N_organic_applied          = GP_accumulators->organic_N_applied;
         N_organic_gaseous_loss     = GP_accumulators->NH3_volatilization_loss;  //021212
         N_inorganic_gaseous_loss   = GP_accumulators->inorganic_NH4_to_atmosphere;
         N_fixation                 = GP_accumulators->N_fixation;
         N_mass_yield               = GP_accumulators->N_mass_yield;             //120117
      } // endif GP_accumulators
   }
   const CropSyst::Crop_nitrogen_interface *crop_N_kg_m2 = crop.get_nitrogen();  //050722
   if (crop_N_kg_m2)                                                             //050722
   {
      N_uptake                 = crop_N_kg_m2->get_season_uptake();              //050722
      N_stress_index_avg       = crop_N_kg_m2->get_stress_index_mean();          //050722
      N_mass_canopy            = crop.get_N_mass_canopy_kg_m2(true);             //110915
      N_max_expected_conc_at_flowering = crop_N_kg_m2->get_max_expected_concentration_at_change(); // currently always at flowering                      //061213
      N_max_expected_conc_at_maturity  = crop_N_kg_m2->get_max_expected_concentration_at_maturity();                                                     //061213
      N_uptake_excess_or_deficit       = crop_N_kg_m2->calc_uptake_excess_or_deficit();                                                                  //061213
      if (!CORN::is_approximately<float32>(N_max_expected_conc_at_maturity,0.0,0.0000001)) // Could rarely be the case if the season ends before maturity//061214
         N_max_expected_conc_flower_mature_ratio = N_max_expected_conc_at_flowering/N_max_expected_conc_at_maturity;                                     //061213
#ifdef PHOSPHORUS
      P_uptake    = crop_nitrogen_phosphorus_ratio * crop_N_kg_m2->get_season_uptake(); //110801
//NYI   P_applied   = xxxxx
      P_soil_profile = soil.chemicals ? soil.chemicals->phosphorus : 0.0;
#endif
   }
   // The following are outputs for Luca, eventually all the N balance will go here
   // NH3_volatilization = GP_accumulators->NH3_volatilization_loss; already output as organic gaseous loss

   if (NO3_GP_bal_accums && NH4_GP_bal_accums)                                   //041005
   {  denitrification = NO3_GP_bal_accums->get_transformed_to(true);
      nitrification = NH4_GP_bal_accums->get_transformed_to(true);               //160323
      if (GP_accumulators)                                                       //170530
      {
      N_N2O_loss_denitrification = GP_accumulators->N2O_loss_denitrification;    //150624
      N_N2O_loss_nitrification   = GP_accumulators->N2O_loss_nitrification;      //150624
      }
      N_soil_profile_final                                                       //161130
         = NO3_GP_bal_accums->get_current_profile_content(true)
         + NH4_GP_bal_accums->get_current_profile_content(true);      // Mineral N in the soil    (mineral profile N)
   }
#ifdef NYI
   N_soil_inputs = VATE_soil_N_input;  // total N inputs to the soil     (check that N applied include organic N) // this is only for luca
   N_soil_output = VATE_soil_N_output; // total N outputs from the soil  // this is only for luca
#endif
#endif

   // Special output (in V5 we will use inspector idiom)                         //160521
   const CropSyst::Crop_complete &crop_complete = dynamic_cast<const CropSyst::Crop_complete &>(crop);
   degree_hours_above_30_flowering_fortnight
      = (float32)crop_complete.output_season_tally.degree_hours_above_30_flowering.sum_last(14);
   degree_hours_above_34_flowering_fortnight
      = (float32)crop_complete.output_season_tally.degree_hours_above_34_flowering.sum_last(14);
   Srad_mean = (float32)crop_complete.output_season_tally.Srad.get_mean();
   Tmax_mean = (float32)crop_complete.output_season_tally.Tmax.get_mean();
   Tmin_mean = (float32)crop_complete.output_season_tally.Tmin.get_mean();
   Tavg_mean = (float32)crop_complete.output_season_tally.Tavg.get_mean();
   WUE = (float32)crop_complete.output_season_tally.water_use_efficiency;
   days_to_flowering    = crop.ref_phenology().get_start_day_in_season(NGS_ANTHESIS);//160523
   duration_season      = crop.ref_phenology().get_days_since_start_of(NGS_PLANTING);//160627
   canopy_cover_max           = crop_complete.reported_canopy_cover_max;         //180413
   canopy_cover_green_final   = crop_complete.reported_canopy_cover_green;       //180413
}
//______________________________________________________________________________
bool Season_data_record::expect_structure(bool for_write)
{  bool expected = CORN::Data_record::expect_structure(for_write);
   expect_int32   ("s_out_id"                      ,s_out_ID);
   expect_int32   ("alloc_id"                      ,alloc_ID);
   expect_int32   ("land_use_id"                   ,land_use_ID);                //030331
   expect_string  ("crop_name"                     ,crop_name,255);

   expect_int32   ("planting_date"     ,planting_date       .mod_date32());      //041205
   expect_int32   ("restart_date"      ,restart_date        .mod_date32());      //041205
   expect_int32   ("emergence_date"    ,emergence_date      .mod_date32());
   expect_int32   ("flowering_date"    ,flowering_date      .mod_date32());
   expect_int32   ("tuber_init_date"   ,tuber_init_date     .mod_date32());      //081111
   expect_int32   ("filling_date"      ,grain_filling_date  .mod_date32());
   expect_int32   ("peak_LAI_date"     ,peak_LAI_date       .mod_date32());
   expect_int32   ("maturity_date"     ,maturity_date       .mod_date32());
   expect_int32   ("harvest_date"      ,harvest_date        .mod_date32());

#ifdef CROP_ORCHARD

   expect_int32("bud_break_date"           ,bud_break_date           .mod_date32());
   expect_int32("initial_fruit_growth_date",initial_fruit_growth_date.mod_date32());
   expect_int32("rapid_fruit_growth_date"  ,rapid_fruit_growth_date  .mod_date32());
   expect_int32("chill_req_satisfied_date" ,chill_requirement_satisfied_date.mod_date32());

   expect_float32 ("fruit_canopy_biomass"          ,fruit_canopy_biomass);       //091104
   expect_float32 ("nonfruit_canopy_biomass"       ,nonfruit_canopy_biomass);    //091104
#endif

   expect_int32   ("inactive_begin_date"           ,inactive_begin_date.mod_date32());//170529
   expect_int32   ("inactive_end_date"             ,inactive_end_date.mod_date32());   //170529

   expect_float32 ("peak_LAI"                      ,peak_LAI);
   expect_float32 ("yield"                         ,yield);
   expect_float32 ("used_biomass"                  ,used_biomass);
   expect_float32 ("grazed_biomass"                ,grazed_biomass);
   expect_float32 ("residue_biomass"               ,residue_biomass);
   expect_float32 ("disposed_biomass"              ,disposed_biomass);

   expect_float32 ("produced_biomass"              ,dry_biomass);
   expect_float32 ("daytime_VPD_avg"               ,daytime_VPD_avg);
   expect_float32 ("intercepted_PAR_accum"         ,intercepted_PAR_accum);
   expect_float32 ("root_depth"                    ,root_depth);
   expect_float32 ("root_biomass"                  ,root_biomass);               //091104
   expect_float32 ("surface_residue_BM"            ,surface_residue_biomass);
   expect_float32 ("surface_plant_residue_BM"      ,surface_plant_residue_biomass);
   expect_float32 ("surface_manure_BM"             ,surface_manure_biomass);
   expect_float32 ("incorporated_BM"               ,incorporated_residue);
   expect_float32 ("incorporated_plant_residue_BM" ,incorporated_plant_residue);
   expect_float32 ("incorporated_manure_BM"        ,incorporated_manure);

   expect_float32 ("erosion_index"                 ,erosion_index);
   expect_float32 ("soil_loss"                     ,soil_loss);
   expect_float32 ("ET_pot"                        ,ET_pot);
   expect_float32 ("ET_act"                        ,ET_act);
   expect_float32 ("ET_ref"                        ,ET_ref);                     //130723
   expect_float32 ("transp_pot"                    ,transp_pot);
   expect_float32 ("transp_act"                    ,transp_act);
   expect_float32 ("evap_soil_pot"                 ,evap_soil_pot);
   expect_float32 ("evap_soil_act"                 ,evap_soil_act);
   expect_float32 ("evap_residue_pot"              ,evap_residue_pot);
   expect_float32 ("evap_residue_act"              ,evap_residue_act);
   expect_float32 ("irrig"                         ,irrig);
   expect_float32 ("precip"                        ,precip);
   expect_float32 ("air_temp_avg"                  ,air_temp_avg_mean);
   expect_float32 ("crop_water_intrcpt"            ,crop_water_intrcpt_today ); //was crop_water_intrcpt  remove _today  // 160419
   expect_float32 ("residue_water_intrcpt"         ,residue_water_intrcpt);
   expect_float32 ("surface_water_runoff"          ,surface_water_runoff);
   expect_float32 ("ponded_water"                  ,ponded_water);
   expect_float32 ("water_enter_soil"              ,water_enter_soil);
   expect_float32 ("soil_water_drainage"           ,soil_water_drainage);
   expect_float32 ("soil_water_profile_init"       ,soil_water_profile_init);    //151217
   expect_float32 ("soil_water_profile_final"      ,soil_water_profile_final);   //151217

   expect_float32 ("AW_150cm_init"                  ,soil_available_water_15_init);
   expect_float32 ("AW_150cm_final"                 ,soil_available_water_15_final);

   expect_float32 ("avg_water_stress_index"        ,avg_water_stress_index);
   expect_float32 ("avg_temperature_stress_index"  ,avg_temperature_stress_index);


   expect_float32 ("avg_flower_temp_stress_index"  ,avg_flower_temperature_stress_index); //091103
#if (CROPSYST_VERSION==4)
   expect_float32 ("avg_filling_duration_index"    ,avg_filling_duration_index); //091103
#endif


   /*150825 dont delete  eventually reimplement this with inspector idiom
   expect_float32 ("avg_tuber_init_temp_stress_index"    ,avg_tuber_init_temp_stress_index);    //091103
   expect_float32 ("avg_tuber_filling_temp_stress"       ,avg_tuber_filling_temp_stress);       //091103
   */

#ifdef NITROGEN
   {
      expect_float32 ("N_leached"      ,N_leached);
      expect_float32 ("N_applied"      ,N_total_applied);
      expect_float32 ("N_auto_uptake"  ,N_auto_uptake);
      expect_float32 ("N_available"    ,N_available);

      expect_float32 ("N_mineralized_residue"   ,N_mineralized_residue);
      expect_float32 ("N_mineralized_org_fert"  ,N_mineralized_org_fert);
      expect_float32 ("N_mineralized_OM"        ,N_mineralized_OM);
      expect_float32 ("N_immobilization"        ,N_immobilization);
      expect_float32 ("N_mineralization"        ,N_mineralization );
      expect_float32 ("N_inorganic_applied"     ,N_inorganic_applied);           //160323
      expect_float32 ("N_organic_applied"       ,N_organic_applied);
      expect_float32 ("N_organic_gaseous_loss"  ,N_organic_gaseous_loss);
      expect_float32 ("N_inorganic_gaseous_loss",N_inorganic_gaseous_loss);
      expect_float32 ("N_fixation"              ,N_fixation);
   }
   {  expect_float32 ("N_stress_index_avg"      ,N_stress_index_avg);
      expect_float32 ("N_uptake"                ,N_uptake);
      expect_float32 ("N_mass_canopy"           ,N_mass_canopy);
      expect_float32 ("N_mass_yield"            ,N_mass_yield);                  //120117
   }
   expect_float32 ("N_nitrification"            ,nitrification);                 //110917
   expect_float32 ("N_denitrification"          ,denitrification);
   expect_float32 ("N_soil_profile_initial"     ,N_soil_profile_initial);        //161130
   expect_float32 ("N_soil_profile_final"       ,N_soil_profile_final);
   expect_float32 ("N_N2O_loss_denitrification" ,N_N2O_loss_denitrification);     //150624
   expect_float32 ("N_N2O_loss_nitrification",N_N2O_loss_nitrification);         //150624
#endif
#ifdef PHOSPHORUS
   expect_float32 ("P_uptake"       ,P_uptake);
   expect_float32 ("P_applied"      ,P_applied);
   expect_float32 ("P_soil_"        ,P_soil_profile);
#endif

   expect_float32 ("DegHr_above_30",degree_hours_above_30_flowering_fortnight);
   expect_float32 ("DegHr_above_34",degree_hours_above_34_flowering_fortnight);
   expect_float32 ("WUE"           ,WUE);
   expect_float32 ("Srad"          ,Srad_mean);
   expect_float32 ("Tmax"          ,Tmax_mean);
   expect_float32 ("Tmin"          ,Tmin_mean);
   expect_float32 ("Tavg"          ,Tavg_mean);
   expect_float32 ("days_to_flowering" ,days_to_flowering);                      //160523
   expect_float32 ("duration_season"   ,duration_season);                        //160523
   expect_float32 ("canopy_cover_max"  ,canopy_cover_max);                       //180413
   expect_float32 ("canopy_cover_green_final",canopy_cover_green_final);         //180413

   structure_defined = true;                                                     //120314
   return expected;
}
//______________________________________________________________________________
Season_data_source::Season_data_source(UED::Database_file_indexed *_database )
: UED::Tuple_data_source(_database,UED::Record_type_distinguisher_interface::UED_data_value_date_var_units,0,simulated_quality)
, Season_data_record()
{
//    Season records have no time step
//    s_out_ID       // for ladss, should not be needed for UED output
//    alloc_ID       // for ladss, should not be needed for UED output
//    land_use_ID    // for ladss, should not be needed for UED output
//    The following are dates

   add_field2(season_section,"planting_date"                 ,CSVC_crop_base_planting_date_YD      ,UT_date,UT_arbitrary_date);
   add_field2(season_section,"restart_date"                  ,CSVC_crop_base_restart_date_YD       ,UT_date,UT_arbitrary_date); //041205
   add_field2(season_section,"emergence_date"                ,CSVC_crop_base_emergence_date_YD     ,UT_date,UT_arbitrary_date);
   add_field2(season_section,"flowering_date"                ,CSVC_crop_base_flowering_date_YD     ,UT_date,UT_arbitrary_date);
   add_field2(season_section,"tuber_init_date"               ,CSVC_crop_base_tuber_init_date_YD    ,UT_date,UT_arbitrary_date); //081111
   add_field2(season_section,"filling_date"                  ,CSVC_crop_base_grain_filling_date_YD ,UT_date,UT_arbitrary_date);
   add_field2(season_section,"peak_LAI_date"                 ,CSVC_crop_base_peak_LAI_date_YD      ,UT_date,UT_arbitrary_date);
   add_field2(season_section,"maturity_date"                 ,CSVC_crop_base_maturity_date_YD      ,UT_date,UT_arbitrary_date);
   add_field2(season_section,"harvest_date"                  ,CSVC_crop_base_harvest_date_YD       ,UT_date,UT_arbitrary_date);

#ifdef CROP_ORCHARD
   add_field2(season_section,"bud_break_date"                  ,CSVC_crop_base_bud_break_date_YD                  ,UT_date,UT_arbitrary_date); //081013
   add_field2(season_section,"initial_fruit_growth_date"       ,CSVC_crop_base_initial_fruit_growth_date_YD       ,UT_date,UT_arbitrary_date); //081013
   add_field2(season_section,"rapid_fruit_growth_date"         ,CSVC_crop_base_rapid_fruit_growth_date_YD         ,UT_date,UT_arbitrary_date); //081013
   add_field2(season_section,"inactive_begin_date"             ,CSVC_crop_base_inactive_begin_date_YD             ,UT_date,UT_arbitrary_date); //081013
   add_field2(season_section,"inactive_end_date"               ,CSVC_crop_base_inactive_end_date_YD               ,UT_date,UT_arbitrary_date); //081013
   add_field2(season_section,"chill_req_satisfied_date"      ,CSVC_crop_base_chill_requirement_satisfied_date_YD,UT_date,UT_arbitrary_date); //081013

   add_field2(season_section,"fruit_canopy_biomass"             ,CSVC_crop_base_fruit_biomass       ,UC_kg_m2,UT_arbitrary_date);              //091104
   add_field2(season_section,"nonfruit_canopy_biomass"          ,CSVC_crop_base_fruit_canopy_biomass,UC_kg_m2,UT_arbitrary_date);              //091104
#endif

//   The following are values for an event during the season
//   Currently the peak LAI is recorded here as the peak value found until the end of season, even though it actually occurs on some other date
   add_field2(season_section,"peak_LAI"                      ,CSVC_crop_base_peak_LAI_time_step_max         ,UC_m2_m2,UT_arbitrary_date);  // Note that index may be  something^2/something^2
   add_field2(season_section,"daytime_VPD_avg"               ,CSVC_crop_base_VPD_daytime_period_avg         ,UC_kPa  ,UT_arbitrary_date);

// The following are accumulated values
   add_field2(season_section,"yield"                         ,CSVC_crop_biomass_yield_period_sum            ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"used_biomass"                  ,CSVC_crop_biomass_useful_period_sum           ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"grazed_biomass"                ,CSVC_crop_biomass_removed_grazing_period_sum  ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"residue_biomass"               ,CSVC_crop_biomass_removed_residue_period_sum  ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"disposed_biomass"              ,CSVC_crop_biomass_disposal_period_sum         ,UC_kg_m2,UT_arbitrary_date);

   add_field2(season_section,"intercepted_PAR_accum"         ,CSVC_crop_base_intercepted_PAR_period_sum     ,UC_MJ_m2,UT_arbitrary_date);

   add_field2(season_section,"soil_loss"                     ,CSVC_soil_erosion_loss_period_sum             ,UC_tn_ha,UT_arbitrary_date);
   add_field2(season_section,"ET_pot"                        ,CSVC_weather_ET_pot_period_sum                ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"ET_act"                        ,CSVC_weather_ET_act_period_sum                ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"ET_ref"                        ,CSVC_weather_ET_ref_period_sum                ,UC_m    ,UT_arbitrary_date); //130723
   add_field2(season_section,"transp_pot"                    ,CSVC_crop_base_transp_pot_period_sum          ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"transp_act"                    ,CSVC_crop_base_transp_act_period_sum          ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"evap_soil_pot"                 ,CSVC_soil_base_evap_pot_period_sum            ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"evap_soil_act"                 ,CSVC_soil_base_evap_act_period_sum            ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"evap_residue_pot"              ,CSVC_residue_pot_evap_period_sum              ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"evap_residue_act"              ,CSVC_residue_act_evap_period_sum              ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"irrig"                         ,CSVC_mgmt_irrig_applied_period_sum            ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"precip"                        ,CSVC_weather_precipitation_period_sum         ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"air_temp_avg"                  ,CSVC_weather_temperature_time_step_avg      ,UC_Celcius,UT_arbitrary_date);//160324
   add_field2(season_section,"crop_water_intrcpt"            ,CSVC_crop_base_water_intrcpt_period_sum       ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"residue_water_intrcpt"         ,CSVC_residue_water_intrcpt_period_sum         ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"surface_water_runoff"          ,CSVC_soil_runoff_surface_water_runoff_period_sum,UC_m  ,UT_arbitrary_date);
   add_field2(season_section,"ponded_water"                  ,CSVC_soil_pond_water_depth                    ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"water_enter_soil"              ,CSVC_soil_base_water_entering_period_sum      ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"soil_water_drainage"           ,CSVC_soil_base_water_drainage_period_sum      ,UC_m    ,UT_arbitrary_date);

   add_field2(season_section,"soil_water_profile_init"       ,CSVP_soil_base_water_depth_initial            ,UC_m    ,UT_arbitrary_date);//151227
   add_field2(season_section,"soil_water_profile_final"      ,CSVP_soil_base_water_depth_final              ,UC_m    ,UT_arbitrary_date);//151227

   // The following are status at end of season (harvest or dormancy or termination)
   add_field2(season_section,"produced_biomass"              ,CSVC_crop_biomass_produced_above_ground_period_sum ,UC_kg_m2,UT_arbitrary_date);
                                                                                                                                                               //070207
   add_field2(season_section,"root_depth"                    ,CSVC_crop_base_root_depth                     ,UC_m    ,UT_arbitrary_date);
   add_field2(season_section,"root_biomass"                  ,CSVC_crop_base_root_biomass_current           ,UC_kg_m2,UT_arbitrary_date);                      //091104

   add_field2(season_section,"surface_residue_BM"           ,CSVC_residue_surface_biomass                  ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"surface_plant_residue_BM"     ,CSVC_residue_plant_surface                    ,UC_kg_m2,UT_arbitrary_date);                       //091104
   add_field2(season_section,"surface_manure_BM"            ,CSVC_residue_manure_surface                   ,UC_kg_m2,UT_arbitrary_date);                       //091104
   add_field2(season_section,"incorporated_BM"              ,CSVC_residue_incorporated                     ,UC_kg_m2,UT_arbitrary_date);                       //091104
   add_field2(season_section,"incorporated_plant_residue_BM",CSVC_residue_plant_incorporated               ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"incorporated_manure_BM"       ,CSVC_residue_manure_incorporated              ,UC_kg_m2,UT_arbitrary_date);
            // Warning not sure about units for erosion index (it may be kg/ha)
   add_field2(season_section,"erosion_index"                 ,CSVC_soil_erosion_index_period_sum            ,UC_index,UT_arbitrary_date);
                                                                                                                                                               //050309
   add_field2(season_section,"avg_water_stress_index"        ,CSVC_crop_base_water_stress_index_period_avg    ,UC_index,UT_arbitrary_date);                    //050309
   add_field2(season_section,"avg_temperature_stress_index"  ,CSVC_crop_base_temperature_stress_index_period_avg ,UC_index,UT_arbitrary_date);                 //050309
                                                                                                                                                               //091103
   add_field2(season_section,"avg_flower_temp_stress_index"   ,CSVC_crop_base_flower_temperature_stress_index_period_avg  ,UC_index,UT_arbitrary_date); //091103

   /*150825 Don't delete, eventually reimplement this with the listener idiom
   add_field2(season_section,"avg_tuber_init_temp_stress_index"      ,CSVC_crop_base_tuber_init_temp_stress_index                ,UC_index,UT_arbitrary_date); //091103
   add_field2(season_section,"avg_tuber_filling_temp_stress"         ,CSVC_crop_base_tuber_fill_temp_stress_index                ,UC_index,UT_arbitrary_date); //091103
   */
#ifdef NITROGEN
   add_field2(season_section,"N_leached"                     ,CSVC_soil_N_leached_period_sum                ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_applied"                     ,CSVC_mgmt_N_applied_period_sum                ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_auto_uptake"                 ,CSVC_crop_N_automatic_uptake_period_sum       ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_available"                   ,CSVC_soil_N_available_period_sum              ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_mineralized_residue"         ,CSVC_residue_mineralized_period_sum           ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_mineralized_org_fert"        ,CSVC_residue_manure_mineralized_period_sum    ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_mineralized_OM"              ,CSVC_organic_matter_mineralized_period_sum    ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_immobilization"              ,CSVC_soil_N_immobilization_period_sum         ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_mineralization"              ,CSVC_soil_N_mineralization_period_sum         ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_organic_applied"             ,CSVC_mgmt_N_organic_applied_period_sum        ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_organic_gaseous_loss"        ,CSVC_mgmt_N_organic_gaseous_loss_period_sum   ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_inorganic_gaseous_loss"      ,CSVC_mgmt_N_inorganic_gaseous_loss_period_sum ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_fixation"                    ,CSVC_crop_N_fixation_period_sum               ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_uptake"                      ,CSVC_crop_N_uptake_period_sum                 ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_mass_yield"                  ,CSVC_crop_N_mass_yield_period_sum             ,UC_kg_m2,UT_arbitrary_date); //120117
   add_field2(season_section,"N_stress_index_avg"            ,CSVC_crop_N_stress_index_period_avg           ,UC_index,UT_arbitrary_date);

   add_field2(season_section,"N_nitrification"               ,CSVC_soil_N_nitrification_period_sum          ,UC_kg_m2,UT_arbitrary_date); //110917
   add_field2(season_section,"N_denitrification"             ,CSVC_soil_N_denitrification_period_sum        ,UC_kg_m2,UT_arbitrary_date); //110917

   add_field2(season_section,"N_soil_profile_initial"        ,CSVC_soil_N_N_amount_initial                          ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_soil_profile_final"          ,CSVC_soil_N_N_amount_final                          ,UC_kg_m2,UT_arbitrary_date);
//161130   add_field2(season_section,"N_soil_profile"                ,CSVC_soil_N_N_amount                          ,UC_kg_m2,UT_arbitrary_date);
#ifdef NYI
   add_field2(season_section,"N_soil_inputs"                 ,CSVC_soil_N_input_period_sum                  ,UC_kg_m2,UT_arbitrary_date);
   add_field2(season_section,"N_soil_output"                 ,CSVC_soil_N_output_period_sum                 ,UC_kg_m2,UT_arbitrary_date);
#endif
#endif
#ifdef PHOSPHORUS
   add_field2(season_section,"P_soil_profile"                ,CSVC_soil_P_P_amount                          ,UC_kg_m2,UT_arbitrary_date); //110801
   add_field2(season_section,"P_uptake"                      ,CSVC_crop_P_mass_uptake_period_sum            ,UC_kg_m2,UT_arbitrary_date); //110801
   add_field2(season_section,"P_applied"                     ,CSVC_mgmt_P_applied_period_sum                ,UC_kg_m2,UT_arbitrary_date); //110801
#endif
   add_field2(season_section,"DegHr_above_30",CSVC_crop_degree_hours_above_30_flowering_fortnight,UC_Celcius_degree_hours,UT_arbitrary_date);
   add_field2(season_section,"DegHr_above_34",CSVC_crop_degree_hours_above_34_flowering_fortnight,UC_Celcius_degree_hours,UT_arbitrary_date);
   add_field2(season_section,"WUE"           ,CSVC_crop_WUE_seasonal,UC_g_kg,UT_arbitrary_date);
   add_field2(season_section,"Srad"          ,CSVC_Srad_seasonal,UC_MJ_per_m2,UT_arbitrary_date);
   add_field2(season_section,"Tmax"          ,CSVC_Tmax_seasonal,UC_Celcius,UT_arbitrary_date);
   add_field2(season_section,"Tmin"          ,CSVC_Tmin_seasonal,UC_Celcius,UT_arbitrary_date);
   add_field2(season_section,"Tavg"          ,CSVC_Tavg_seasonal,UC_Celcius,UT_arbitrary_date);
   add_field2(season_section,"days_to_flowering"  ,CSVC_crop_days_to_flowering,UT_day,UT_arbitrary_date);
   add_field2(season_section,"duration_season",CSVC_crop_duration,UT_day,UT_arbitrary_date);

   add_field2(season_section,"AW_150cm_init"  ,CSVC_PAW_15_init_seasonal,UC_meter,UT_arbitrary_date);
   add_field2(season_section,"AW_150cm_final" ,CSVC_PAW_15_final_seasonal  ,UC_meter,UT_arbitrary_date);

   add_field2(season_section,"canopy_cover_max"    ,CSVC_canopy_cover_max  ,UC_fraction,UT_arbitrary_date); //180413
   add_field2(season_section,"canopy_cover_green_final"  ,CSVC_canopy_cover_green_final,UC_fraction,UT_arbitrary_date); //180413

}
//_2004-09-21___________________________________________________________________
void Season_data_source::record(datetime64 date_time)
{  set_date(date_time);
   set((*this));
   clear();                                                                      //110117
}
//______________________________________________________________________________
