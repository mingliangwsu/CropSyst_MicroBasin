// Chemical profile for soil
#  include <math.h>
#  include "corn/math/moremath.h"
#  include "soil/chemical_balance.h"
#  include "soil/chemical_profile.h"
#  include "soil/chemical_mass_profile.h"
#  include "soil/chemicals_profile.h"
#  include "soil/nitrogen_profile.h"
#  include "soil/soil_base.h"
#  include "watertab.h"
#  include "static_phrases.h"
#include "common/chemistry/stoichiometry_composition.h"

#include "physics_constants.h"
#define SPACER 0
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#define HAVE_ELEMENTAL_FORM

// Only for debugging
//ofstream Nconc_dump ("N_conc.dat");

//______________________________________________________________________________
float32 XUa[6] = {SPACER, -1.28,-0.525,0.0,0.525,1.28};
// These variables are currently global until I can find a better place for them
//______________________________________________________________________________
Chemical_pool::Chemical_pool
(const CORN::date32 &today_                                                //170525
,const std::string      &chem_name                                               //001116
,float64                chem_to_element_factor_
,float64                element_to_chem_factor_
#if (CROPSYST_VERSION == 4)
,float64                control_transformation_adjustment_
#endif
,soil_layer_array64     (simulation_amount_E_)                                   //051120
   // For NO3 and NH4 this is mass for salt, this is concentration in dSm
#ifndef OLD_N_XFER
,Chemical_pool *receiver_                                                        //170502
#endif
,const Soil_layers_interface               &soil_layers_                         //150925
,const Soil_hydrology_interface            &soil_hydrology_                      //150925
,const Soil_hydraulic_properties_interface &soil_hydraulic_properties_           //150925
,const Soil_structure_interface            &soil_structure_                      //150925
,Infiltration_model      infiltration_model                                      //080117
)
:CS::Simulation_element_abstract(today_)                                         //170425
,name(chem_name)
,soil_layers              (soil_layers_)                                         //150925
,soil_hydrology           (soil_hydrology_)                                      //150925
,soil_hydraulic_properties(soil_hydraulic_properties_)                           //150925
,soil_structure           (soil_structure_)                                      //150925
,mass                      (0)                                                   //170425
,surface                   (0)                                                   //170425
,chem_to_element_factor(chem_to_element_factor_)
,element_to_chem_factor(element_to_chem_factor_)
#if (CROPSYST_VERSION == 4)
,control_transformation_adjustment(control_transformation_adjustment_)
#endif
#ifdef OLD_N_XFER
,profile_transformed_from_M(1.0)                                                 //010317
#else
,receiver(receiver_)                                                             //170502
#endif
#ifndef NEW_N_XFER_BAL
// as of 170503 this is still used
,ANNL_bal_accums(0)                                                              //990316
,GP_bal_accums_current(0)                                                        //990316
,CONT_bal_accums  (0)                                                            //990316
#if (REACCH_VERSION < 2)
,FALLOW_bal_accums(0)                                                            //990316
#endif
#endif
{
   soil_layer_array64(amount_M); //kg chem / m^2 soil molecular
      // rename this to M_mass_layer
   for (int sublayer_clear = 0; sublayer_clear <= MAX_soil_sublayers ; sublayer_clear++)  //981006
   {  amount_M[sublayer_clear] = 0.0;                                            //981007
      #ifdef OLD_N_XFER
      transformed_from_M[sublayer_clear] = 0; // transformed from something else //981007
      #endif
   }                                                                             //981007
//   #ifndef OLD_N_XFER
   transformed_E_output.clear();                                                 //170502
//   #endif
   nat8 soil_num_sublayers = soil_layers.get_number_layers();
   for (int layer = 1; layer <= soil_num_sublayers; layer ++)
   {  float64 amount_E_sl = simulation_amount_E_[layer];                         //020305
      {  float64 amount_chem_sl  = element_to_chem_factor
            * (per_ha_to_per_m2(amount_E_sl));                                   //981212
         amount_M[layer] = amount_chem_sl;
      }
   }
   #ifdef FINITE_DIFF
   if (infiltration_model == FINITE_DIFFERENCE_INFILTRATION)                     //080116
   {  Chemical_mass_profile_node_based *mass_nodal = new Chemical_mass_profile_node_based(soil_layers);
      mass_nodal->initialize(amount_M);
      mass = mass_nodal;
   } else
   #endif
   {  Chemical_mass_profile_layer_based *mass_layered = new Chemical_mass_profile_layer_based(soil_layers);
      mass_layered->initialize(amount_M);
      mass = mass_layered;
   }
}
//______________________________________________________________________________
Chemical_pool::~Chemical_pool()
{  if (mass) delete mass; mass = 0;
}
//_2008-01-16___________________________________________________________________
nat8 Chemical_pool::Surface::schedule_application
(float64    mass_applied //kg chem / m^2 soil molecular
,CORN::datetime64 start_time
,CORN::Seconds    operation_duration
,CORN::Seconds    interval_duration)
{
   nat8 intervals = operation_duration / interval_duration;
   //170502LML float64 mass_per_interval = mass_applied / interval_duration;
   float64 mass_per_interval = mass_applied / intervals;                         //170502LML
   CORN::Date_time_clad_64 at_start_time(start_time);
   CORN::datetime64 new_start_time = at_start_time.get_datetime64();        //170922
   for (nat8 interval = 0; interval < intervals; interval++)
   {
      pending_applications.append
         (new Pending_application(new_start_time/*170922 at_start_time.get_datetime64()*/,mass_per_interval));
      new_start_time = at_start_time.inc_seconds(interval_duration);
   }
   return intervals; // currently the number of events is the duration
}
//_2017-04-25___________________________________________________________________
nat8 Chemical_pool::apply_surface_mass
(float64    mass_applied //kg chem / m^2 soil molecular
,CORN::datetime64 start_time
,CORN::Seconds    operation_duration
,CORN::Seconds    interval_duration)
{  if (CORN::is_approximately<float64>(mass_applied, 0)) return (0);
   if (!surface) surface = new Surface;
   return surface->schedule_application
      (mass_applied,start_time,operation_duration,interval_duration);
}
//_2017-04-25___________________________________________________________________
float64 Chemical_pool::get_surface_mass()                                  const
{  return surface ? surface->get_mass() : 0;
}
//_2017-04-25___________________________________________________________________
float64 Chemical_pool::deduct_surface_mass(float64 mass_deduction) modification_
{  float64 actual_deduction = 0;
   if (surface) actual_deduction = surface->deduct_mass(mass_deduction);
   if (surface && surface->is_exhausted()) {delete surface; surface = 0; }
   return actual_deduction;
}
//_2017-04-25___________________________________________________________________
bool Chemical_pool::Surface::commit_pending_applications(CORN::datetime64 by_now)
{  FOR_EACH_IN(pending_appl,Pending_application,pending_applications,each_appl)
   {  if ((by_now >= pending_appl->time)
           || CORN::is_approximately(by_now,pending_appl->time))                 //170621LML if the time pretty close, use the pending pond
      {  mass += pending_appl->mass;
         each_appl->delete_current();
      }
   } FOR_EACH_END(each_appl)
   return true;
}
//_2017-04-25___________________________________________________________________
float64 Chemical_pool::Surface::get_pending_application() const
{
   float64 pending_application = 0;
   FOR_EACH_IN(pending_appl,Pending_application,pending_applications,each_appl)
   {
      pending_application += pending_appl->mass;
   } FOR_EACH_END(each_appl)
   return pending_application;
}
//_2017-04-25___________________________________________________________________
float64 Chemical_pool::Surface::deduct_mass(float64 mass_deduction)                 modification_
{  float64 mass_deduction_act = mass_deduction;
   if (mass_deduction > mass)
   {  mass_deduction_act = mass;
         // Removed the specified mass (must limited to the mass available).
         // Returns the actual mass removed.
   }
   mass -= mass_deduction_act;
   return mass_deduction_act;
}
//_2017-04-25___________________________________________________________________
bool Chemical_pool::commit_surface_pending_applications
(CORN::datetime64 by_now)                                          modification_
{  return surface ? surface->commit_pending_applications(by_now) : true;
}
//_2017-04-25___________________________________________________________________
void Chemical_pool::instanciate_accumulators()                   //contribution_
{  float64 original_profile_content_M = get_current_profile_content_M();
#ifndef NEW_N_XFER_BAL
   ANNL_bal_accums = new Chemical_balance_accumulators
   (original_profile_content_M,name,get_transformation_name(),chem_to_element_factor,has_uptake());
  GP_bal_accums_current = new Chemical_balance_accumulators
  (original_profile_content_M,name,get_transformation_name(),chem_to_element_factor,has_uptake());
  CONT_bal_accums = new Chemical_balance_accumulators
  (original_profile_content_M,name,get_transformation_name(),chem_to_element_factor,has_uptake());
#if (REACCH_VERSION < 2)
//HACK: Currently we have always activated these reporters, but I want to just have the accumulators
// and report only as necessary
  FALLOW_bal_accums = new Chemical_balance_accumulators
  (original_profile_content_M,name,get_transformation_name(),chem_to_element_factor,has_uptake());
#endif
#endif
}
//_2011-11-07__1999-03-19_______________________________________________________
#ifndef NEW_N_XFER_BAL
// as of 170503 this is still used
void Chemical_pool::update_YLY_bal_reporter()
{    if (ANNL_bal_accums) delete ANNL_bal_accums;
     ANNL_bal_accums= new Chemical_balance_accumulators
     (get_current_profile_content_M(),name,get_transformation_name(),chem_to_element_factor,has_uptake());
}
#endif
//_1999-03-19___________________________________________________________________
Chemical_profile::Chemical_profile
(const CORN::date32 &today_                                                //170525
,const std::string  &chem_name                                                   //001116
,chemical_types      chemical_type_
,float64             chem_to_element_factor_
,float64             element_to_chem_factor_
#if (CROPSYST_VERSION==4)
,float64             control_transformation_adjustment_
#endif
,soil_layer_array64                        (simulation_amount_E_)                //051120
#ifndef OLD_N_XFER
//#error check obsolete
,Chemical_pool                             *receiver_                            //170502
#endif
,const Soil_layers_interface               &soil_layers_                         //150925
,const Soil_hydrology_interface            &soil_hydrology_                      //150925
,const Soil_hydraulic_properties_interface &soil_hydraulic_properties_           //150925
,const Soil_structure_interface            &soil_structure_                      //150925
,Infiltration_model                         infiltration_model                   //080117
,Water_table_curve                         *water_table_curve_                   //000504
)
:Chemical_pool
   (today_,chem_name
   ,chem_to_element_factor_
   ,element_to_chem_factor_
   #if (CROPSYST_VERSION==4)
   ,control_transformation_adjustment_
   #endif
   ,simulation_amount_E_
   #ifndef OLD_N_XFER
   ,receiver_                                                                    //170502
   #endif
   ,soil_layers_
   ,soil_hydrology_
   ,soil_hydraulic_properties_
   ,soil_structure_
   ,infiltration_model)
,chemical_type(chemical_type_)
#ifdef WATERTABLE
,water_table_curve(water_table_curve_)                                           //000504
,water_table_concentration(0.0)                                                  //071218
#endif
,reported_leached_molecular(0.0)
,balance_leached_molecular(0.0)
,daily_requirements(0.0)
,total_requirements(0.0)                                                         //010416
,applied_irrig_soil_M(0.0)
,nu(0.6)                                                                         //080606
{}
//______________________________________________________________________________
Chemical_profile::~Chemical_profile()
{
#ifdef WATERTABLE
   if (water_table_curve) delete water_table_curve;
#endif
}
//_2000-05-04___________________________________________________________________
Chemical_uptake_profile::Chemical_uptake_profile
(const CORN::date32 &today_                                                //170525
,const std::string     &chem_name
,chemical_types         chemical_type_
,float64                chem_to_element_factor_
,float64                element_to_chem_factor_
#if (CROPSYST_VERSION==4)
,float64                control_transformation_adjustment_
#endif
,soil_layer_array64    (simulation_amount_E_)                                    //051120
#ifndef OLD_N_XFER
,Chemical_pool *        receiver_                                                //170502
#endif
,const Soil_layers_interface               &soil_layers_                         //150925
,const Soil_hydrology_interface            &soil_hydrology_                      //150925
,const Soil_hydraulic_properties_interface &soil_hydraulic_properties_           //150925
,const Soil_structure_interface            &soil_structure_                      //150925
,Infiltration_model     infiltration_model_                                      //080117
,Water_table_curve     *water_table_curve_                                       //000504
)
: Chemical_profile
   (today_
   ,chem_name
   ,chemical_type_
   ,chem_to_element_factor_
   ,element_to_chem_factor_
   #if (CROPSYST_VERSION==4)
   ,control_transformation_adjustment_
   #endif
   ,simulation_amount_E_
   #ifndef OLD_N_XFER
   ,receiver_                                                                    //170502
   #endif
   ,soil_layers_
   ,soil_hydrology_
   ,soil_hydraulic_properties_
   ,soil_structure_
   ,infiltration_model_                                                          //080117
   ,water_table_curve_)                                                          //000504
{}
//______________________________________________________________________________
float64 Chemical_uptake_profile::uptake_elemental
(nat8 layer, float64 requested_elemental_N_uptake)
{
   float64 elemental_amount_available = chem_to_element_factor*
      mass->get_layer(layer);
   float64 actual_N_uptake = (requested_elemental_N_uptake > elemental_amount_available)
      ? elemental_amount_available
      : requested_elemental_N_uptake;

//130911 Warning I am not sure why I am not incrementing the uptakes because
//this is called for each layer and uptake would be cumulative for the profile!!!

   float64 uptake_molecular  = element_to_chem_factor*(actual_N_uptake) ;        //130911
   mass->dec_layer(layer,uptake_molecular);                                      //080117
   #ifndef NEW_N_XFER_BAL
   if (ANNL_bal_accums)       ANNL_bal_accums   ->inc_uptake(uptake_molecular);          //990317
   if (GP_bal_accums_current) GP_bal_accums_current     ->inc_uptake(uptake_molecular);  //990317
   if (CONT_bal_accums)       CONT_bal_accums   ->inc_uptake(uptake_molecular);          //990317
#if (REACCH_VERSION < 2)
   if (FALLOW_bal_accums)     FALLOW_bal_accums ->inc_uptake(uptake_molecular);          //990317
#endif
   #endif
   return  actual_N_uptake;
}
//_1998-07-03_____________________________________________________________________________
#ifdef NOT_YET_IMPLEMENTED
potassium_profile.initialize()                                   initialization_
{  Chemical_uptake_profile.initialize
      (chem_name,_kind
      ,_control_transformation_adjustment
      ,simulation_amount_E,layer_divisions,soil_num_sublayers,soil_in_layer_of);
   constantC = 800.0;
   constantQ = 0.008;
}
//______________________________________________________________________________
phosphorus_profile.initialize()                                  initialization_
{  Chemical_uptake_profile.initialize(chem_name,_kind,
     _control_transformation_adjustment,simulation_amount_E,layer_divisions,soil_num_sublayers,soil_in_layer_of);
      constantC = 300000.0;
      constantQ = 0.0002;
}
#endif
//______________________________________________________________________________
void Chemical_profile::update_balance_pending_infiltration()
{  float64 surface_mass_pending_infiltration_M =
      surface ? surface->get_pending_application() : 0;                          //170425
   #ifndef NEW_N_XFER_BAL
   if (ANNL_bal_accums)       ANNL_bal_accums      ->know_pending_infiltration(surface_mass_pending_infiltration_M); //990317
   if (GP_bal_accums_current) GP_bal_accums_current->know_pending_infiltration(surface_mass_pending_infiltration_M); //070801
   if (CONT_bal_accums)       CONT_bal_accums      ->know_pending_infiltration(surface_mass_pending_infiltration_M); //990317
   #if (REACCH_VERSION < 2)
   if (FALLOW_bal_accums)     FALLOW_bal_accums    ->know_pending_infiltration(surface_mass_pending_infiltration_M); //990317
   #endif
   #endif
}
//_2007-10-16___________________________________________________________________
bool Chemical_profile::inc_applied(float64 addition_M)
{  bool applied = true;                                                          //170426
   if (CORN::is_approximately<float64>(addition_M,0.0))                          //170426_120704
      applied = false;                                                           //170426
   else
   {
      #ifndef NEW_N_XFER_BAL
      if (ANNL_bal_accums)     ANNL_bal_accums ->inc_applied(addition_M);
      if (GP_bal_accums_current) GP_bal_accums_current->inc_applied(addition_M); //070801
      if (CONT_bal_accums)     CONT_bal_accums ->inc_applied(addition_M);
      #if (REACCH_VERSION < 2)
      if (FALLOW_bal_accums) FALLOW_bal_accums ->inc_applied(addition_M);
      #endif
      #endif
   }
   return applied;                                                               //170426
}
//_1999-03-17____________________________________________________________________
bool  Chemical_profile::inc_applied_irrig_soil(float64 addition_M)
{  bool applied = true;                                                          //170426
   if (CORN::is_approximately<float64>(addition_M,0.0))                          //170426_120704
      applied = false;                                                           //170426
   else
   {  applied_irrig_soil_M += addition_M;
      #ifndef NEW_N_XFER_BAL
      if (ANNL_bal_accums)    ANNL_bal_accums   ->inc_applied_irrig_soil(addition_M);
      if (GP_bal_accums_current) GP_bal_accums_current->inc_applied_irrig_soil(addition_M);
      if (CONT_bal_accums)    CONT_bal_accums   ->inc_applied_irrig_soil(addition_M);
      #if ( REACCH_VERSION < 2)
      if (FALLOW_bal_accums)  FALLOW_bal_accums ->inc_applied_irrig_soil(addition_M);
      #endif
      #endif
   }
   return applied;
}
//_1999-03-17____________________________________________________________________
bool Chemical_profile::inc_applied_and_applied_irrig_soil_subsurface(float64 addition_M)
{  return inc_applied(addition_M)
       && inc_applied_irrig_soil(addition_M);
}
//_1999-03-17____________________________________________________________________
void Chemical_profile::application
(float64 addition
,nat8 layer
,nat8 split_into_layers
,nat8 soil_num_layers
,bool is_elemental)
{  float64 addition_M = (is_elemental)
      ? element_to_chem_factor*(addition)
      : addition;
   // If there are not enough sublayers for the desired splitting,}
   // determine a splitting that will work;                            }
   while (split_into_layers > (soil_num_layers - layer + 1))
       split_into_layers--;
   for (nat8 split = 0; split < split_into_layers; split++)
   {  float64 split_amount = addition_M / split_into_layers;                     //080117
      mass->inc_layer(layer+split,split_amount);                                 //080117
   }
   mass->commit_diffs();                                                         //120731
   inc_applied_and_applied_irrig_soil_subsurface(addition_M);                    //990317
}
//_1993-03-01?__________________________________________________________________
void Chemical_profile::application_at_layer
(float64 addition
,nat8 at_layer
,bool is_elemental)
{  float64 addition_M = (is_elemental)
      ? element_to_chem_factor*(addition)
      : addition;
   // If there are not enough sublayers for the desired splitting,}
   // determine a splitting that will work;                            }
   mass->inc_layer(at_layer,addition_M);
   mass->commit_diffs();
   inc_applied_and_applied_irrig_soil_subsurface(addition_M);
}
//_2016-01-20___________________________________________________________________
void Chemical_profile::application_concentration
(float64 addition_concentration , float64 irrigation ) // kg/m3<- need convert to molecular in caller
{  float64 addition_M = addition_concentration * irrigation;
   inc_applied_and_applied_irrig_soil_subsurface(addition_M);
}
//_1999-03-17____________________________________________________________________
#ifdef WATERTABLE
float64 Chemical_profile::get_water_table_concentration()
{  // For some chemical profiles, water table is not considered.
   float64 water_table_conc = (water_table_curve)
   ? water_table_curve->get_for_today()                                          //150925
     // already in concentration * 0.64
   : 0.0;
   return  water_table_conc;
}
//______________________________________________________________________________
bool Chemical_profile::adjust_water_table_concentration
(nat8 number_FD_soluation_layers
,nat8 number_of_real_plus_extended_layers)
{  water_table_concentration = get_water_table_concentration();                  //000504
   float64 water_table_mass_input = 0.0;
   for (nat8 layer = number_FD_soluation_layers+2 /*2 is top_inundated_layer?*/
         // 080219 RLN not sure why not from the top inundated layers
       ; layer <= number_of_real_plus_extended_layers-1; layer++)                //080218
   {  float64 layer_thickness_m = soil_layers.get_thickness_m(layer);
      float64 sat_WC_layer = soil_hydraulic_properties.get_saturation_water_content_volumetric(layer,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822);
      float64 before_inundation_layer_mass = mass->get_layer(layer);
      float64 inundated_layer_mass = water_table_concentration * sat_WC_layer * layer_thickness_m;
      mass->set_layer(layer,inundated_layer_mass);
      water_table_mass_input += (before_inundation_layer_mass - inundated_layer_mass);
   }
   mass->commit_diffs();                                                         //120731
   inc_balance_leached_M(water_table_mass_input); // Simply treat any watertable innundation as immediate upflow.
   return true;
}
//_2007-12-14____________________________________________________________________
#endif
void Chemical_profile::resolution_of_Thomas_agorithm
(nat8 num_slots_eff    // This will be either the number of layers or nodes
,soil_node_array64(a_term)    // layer or nodal array
,soil_node_array64(b_term)    // layer or nodal array
,soil_node_array64(c_term)    // layer or nodal array
,soil_node_array64(d_term)    // layer or nodal array
,soil_node_array64(new_water_depth_slotal)
,soil_layer_array64(slot_concentration)
,soil_node_array64(sorbed_chemical_mass) // layer or nodal array                 //080606
,soil_layer_array64(slot_chemical_mass))                                         //080606
{
   // Resolution of the system by Thomas algorithm. New concentration computation
   // Soil Physics with BASIC Pg 35 (G.S. Campbell)                              //071220
   // This code works with either layer or nodal systems
   // the term 'slot' is used to refer to layer or node
#ifdef _DEBUG
soil_node_array64(DEBUG_d_term_E);   clear_node_array64(DEBUG_d_term_E); // for debugging only
soil_node_array64(DEBUG_chemical_conc_E); clear_node_array64(DEBUG_chemical_conc_E);
soil_node_array64(DEBUG_chemical_mass_slot_E); clear_node_array64(DEBUG_chemical_mass_slot_E); // only for debugging
#endif
   for (nat8 slot = 1; slot <=  (num_slots_eff - 1) ; slot++)
   {  //' Condition added to avoid division by 0
       if (CORN::is_approximately<float64>(b_term[slot],0.0,0.0000001))          //080114
           b_term[slot] = 0.0000000001;                                          //080114
       // Condition added to avoid division by 0
       // (may occur in completely frozen soil layer).
       c_term[slot] /= b_term[slot];
       d_term[slot] /= b_term[slot];
       b_term[slot+1] -= a_term[slot+1] * c_term[slot];
       d_term[slot+1] -= a_term[slot+1] * d_term[slot];
       // This is added by RLN to avoid slightly negative numbers
       // This is not in the V.B. version but probably should be.
       if (CORN::is_approximately<float64>(a_term[slot],0.0,0.0000000000001)) a_term[slot] = 0.0;
       if (CORN::is_approximately<float64>(b_term[slot],0.0,0.0000000000001)) b_term[slot] = 0.0;
       if (CORN::is_approximately<float64>(c_term[slot],0.0,0.0000000000001)) c_term[slot] = 0.0;
       if (CORN::is_approximately<float64>(d_term[slot],0.0,0.0000000000001)) d_term[slot] = 0.0;
#ifdef _DEBUG
DEBUG_d_term_E[slot] = d_term[slot] *  chem_to_element_factor;  // This simply for debugging to view values in elemental
DEBUG_chemical_conc_E[slot] =  slot_concentration[slot] *  chem_to_element_factor;
#endif
  }
  if (CORN::is_approximately<float64>(b_term[num_slots_eff],0.0,0.0000001))      //080114
      b_term[num_slots_eff] = 0.0000000001; // Again check for div0              //080114
   soil_node_array64(new_slot_concentration); clear_node_array64(new_slot_concentration); //070924
   // for last effective node
   new_slot_concentration[num_slots_eff]
      = d_term[num_slots_eff] / b_term[num_slots_eff];
   slot_concentration[num_slots_eff] = new_slot_concentration[num_slots_eff]; // 080114 Added by RLN wasn't in V.B. code
   slot_chemical_mass[num_slots_eff]                                             //080114
      = sorbed_chemical_mass[num_slots_eff]                                      //080114
      + new_slot_concentration[num_slots_eff] * new_water_depth_slotal[num_slots_eff];  //080114
#ifdef _DEBUG
DEBUG_chemical_conc_E[num_slots_eff] =  slot_concentration[num_slots_eff] *  chem_to_element_factor;
DEBUG_chemical_mass_slot_E[num_slots_eff] = slot_chemical_mass[num_slots_eff] * chem_to_element_factor;  // debug only
#endif
   for (nat8 slot = (num_slots_eff - 1); slot >= 1; slot --)
   {  new_slot_concentration[slot]
         = d_term[slot] - c_term[slot] * new_slot_concentration[slot+1];
      slot_concentration[slot] = new_slot_concentration[slot];                   //080114
      slot_chemical_mass[slot]                                                   //080114
         = sorbed_chemical_mass[slot]                                            //080114
         + new_slot_concentration[slot] * new_water_depth_slotal[slot];          //080114
#ifdef _DEBUG
DEBUG_chemical_conc_E[slot] =  slot_concentration[slot] *  chem_to_element_factor;
DEBUG_chemical_mass_slot_E[slot] = slot_chemical_mass[slot] * chem_to_element_factor;  // debug only
#endif
   }                                                                                  //Next Layer
   // Determination of leaching and mass balance check is done by the caller
}
//_2008-06-06_________________________resolution_of_Thomas_agorithm_and_update_/
void Chemical_profile::transport_unidirectional
(nat8 num_layers_eff
,soil_layer_array64(flow)  // m3 water/m2 soil (m water depth)   flow out of the layer
,soil_layer_array64(old_liquid_water_content)
,soil_layer_array64(new_liquid_water_content)
,float64 water_entering
,Seconds                at_time
,Seconds                duration // seconds of duration
,bool override_drainage_depth
,nat8 drainage_sublayer_unused
)
{ // This should work with any timestep - RLN
   //Replaces transport_unidirectional_original in version 4.11.03
   CORN::Date_time_clad_64 now(today.get_date32(),at_time);                      //170425

   soil_layer_array64(layer_concentration);     clear_layer_array64(layer_concentration); //070924
   soil_layer_array64(sorbed_chemical_mass);    clear_layer_array64(sorbed_chemical_mass);//070924
   soil_layer_array64(bypass_chemical_mass);    clear_layer_array64(bypass_chemical_mass);//081001
   /*nu is now a member static const float64 nu = 0.6;   */
   /*Water_Density is a common constant   */
   float64 initial_chemical_mass = mass->sum_profile();
   //170425RLN flow[0] = water_entering;
   // Chemical concentration in irrigation water (kg chem/m3 water)
   // (In the V.B. code this is pass in the parameter Fertigation.)
   commit_surface_pending_applications(now.get_datetime64());                    //170425
   float64 surface_M = get_surface_mass(); //  kg/m2                             //170425
   float64 surface_water_entering_concentration
      = (water_entering > 0.0) ? surface_M / water_entering : 0.0;

//WARNING negative flow is causing instability
//Im not sure if clearing flow[0] will cause loss of information needed
//for runoff/ponding particularly for in MicroBasin.                             //171008
if (flow[0] < 0 )
flow[0] = 0;
for (nat8 layer = 1; layer <= num_layers_eff; layer++)
if (flow[layer] < 0 )
flow[layer] = 0;


   float64 infiltrated_M = flow[0] * surface_water_entering_concentration;       //170425
   float64 surface_removed = deduct_surface_mass(infiltrated_M);                 //170425


/*170425
   float64 actual_surface_infiltrated_M  //  kg/m2
      = relinquish_surface_mass_pending_infiltration_M(at_time,duration);
   float64 surface_water_entering_concentration
      = (water_entering > 0.0)
      ? actual_surface_infiltrated_M / water_entering
      : 0.0;
 */
   float64 conc_in = surface_water_entering_concentration;
   layer_concentration[0] = conc_in;
   soil_layer_array64(new_water_depth);clear_layer_array64(new_water_depth);
   soil_layer_array64(old_water_depth);clear_layer_array64(old_water_depth);
   for (nat8 layer = 1; layer <= num_layers_eff; layer++)
   {
      float64 thickness_layer  = soil_layers.get_thickness_m(layer);
      float64 layer_domain_thickness = thickness_layer;
      // This next two lines yield units of meter (m3 water/m2 soil)
      new_water_depth[layer]
         = new_liquid_water_content[layer] * layer_domain_thickness;
      old_water_depth[layer]
         = old_liquid_water_content[layer] * layer_domain_thickness;
      //  water content for the node domain at the beginning of the current time step, before FD solution for the current time step
      float64 old_water_content_layer = old_liquid_water_content[layer];
      float64 chemical_mass_in_layer = mass->get_layer(layer);
      // Added adjustment for bypass. Bypassed chemical mass will stay in the layer (not available for transport)
      float64 bypass_coef      = soil_hydraulic_properties.get_bypass_coef(layer);
      bypass_chemical_mass[layer]
         = chemical_mass_in_layer * bypass_coef;
      float64 chemical_mass_available_for_transport
         =  chemical_mass_in_layer -  bypass_chemical_mass[layer];

// The following line is here only so we can see the amount of element N when debugging
//float64 chemical_mass_in_layer_E =  chemical_mass_available_for_transport *  chem_to_element_factor;
//cout << chemical_mass_in_layer_E;

      if (chemical_mass_available_for_transport > 0)
      {
          bool is_NH4 = dynamic_cast<NH4_Profile *>(this) != 0;
         if (is_NH4 /*NYI || is_phosphorus Eventually we will have phosphorus*/)
         {
            float64 bulk_density =soil_structure.get_bulk_density_g_cm3(layer);
            // Layer concentration in kg Chem/m3 water
            float64 chem_mass_fraction_in_solution = 0; //  kg Chem / m3 water  // <-- returned by calc_Langmuir_solute_equilibrium_concentration
            layer_concentration[layer]
               =  calc_Langmuir_solute_equilibrium_concentration
                  (chemical_mass_available_for_transport
                  ,bulk_density
                  ,layer_domain_thickness
                  ,old_water_content_layer
                  ,chem_mass_fraction_in_solution);
            sorbed_chemical_mass[layer] =chemical_mass_available_for_transport
                          *(1.0 - chem_mass_fraction_in_solution);
         }
//  I dont know why this has now been disabled in the V.B. version
         else
         {
            layer_concentration[layer] = chemical_mass_available_for_transport
                  / (layer_domain_thickness * old_water_content_layer);
            sorbed_chemical_mass[layer] = 0.0;
         }

      } else // (This else is not really needed because we initialize to zero
      {  layer_concentration[layer] = 0.0;
         sorbed_chemical_mass[layer] = 0.0;
      }
      /* In the C++ code, the flow array is passed  */
      /* whereas in the V.B. code it is obtained from soil*/
   }
   // Compute coefficients to build the tridiagonal matrix.
   soil_layer_array64(a_term);   clear_layer_array64(a_term);
   soil_layer_array64(b_term);   clear_layer_array64(b_term);
   soil_layer_array64(c_term);   clear_layer_array64(c_term);
   soil_layer_array64(d_term);   clear_layer_array64(d_term);
   for (nat8 layer = 1; layer <= num_layers_eff; layer++)
   { // Unlike the F.D. flow is always downward so we have only one case
      a_term[layer] = flow[layer-1]  * nu;
      b_term[layer] = - new_water_depth[layer] - flow[layer]  * nu;
      c_term[layer] = 0.0;
      float64 one_minus_nu = (1.0-nu);
      float64 nu_term = layer == 1 ? 1.0 : one_minus_nu;
      d_term[layer] =
         - old_water_depth[layer]        * layer_concentration[layer]
         + flow[layer]   * one_minus_nu  * layer_concentration[layer]
         - flow[layer-1] * nu_term       * layer_concentration[layer-1];
      if (d_term[layer]  > 0)
      {  if (is_approximately<float64>(flow[layer],0.0,0.00001))
         {  std::cerr << "flow 0" << std::endl;
         } else layer_concentration[layer]
            -=  d_term[layer] / (flow[layer] * one_minus_nu);
         d_term[layer] = 0.0;
      }
   }
   soil_layer_array64(new_chemical_mass);clear_layer_array64(new_chemical_mass); //080606
   resolution_of_Thomas_agorithm
      (num_layers_eff
      ,a_term    // layer or nodal array
      ,b_term    // layer or nodal array
      ,c_term    // layer or nodal array
      ,d_term    // layer or nodal array
      ,new_water_depth
      ,layer_concentration
      ,sorbed_chemical_mass                                                      //080606
      ,new_chemical_mass);                                                       //080606

// debugging only 150924
//soil_layer_array64(new_N_mass); clear_layer_array64(new_N_mass);
//float64 sum_N_mass = 0.0;
//nat32 hour = at_time/3600;
//std::cout << std::endl << hour << '(' << (hour+1) << ')' << std::endl;

   for (nat8 layer = 1; layer <= num_layers_eff; layer++)                        // as of 081001 not in V.B. Code
   {
      new_chemical_mass[layer] += bypass_chemical_mass[layer];                   // as of 081001 not in V.B. Code
// debugging only 150924
//new_N_mass[layer] = element_to_chem_factor* new_chemical_mass[layer];
//sum_N_mass += new_N_mass[layer];
//std::cout << new_N_mass[layer] << std::endl;
   }
//debug
//Nconc_dump << layer_concentration[ num_layers_eff] << "\t";
//bool is_NH4 = dynamic_cast<NH4_Profile *>(this) != 0;

//std::cout << "prof:" << sum_N_mass << std::endl;


   // Update and save chemical mass per node and chemical species for next hour
   float64 step_final_chemical_mass
      = mass->set_layers(new_chemical_mass ); // set_layers replaces for loop    //080609
 /*for (nat8 layer = 1; layer <= num_layers_eff; layer++)   */
 /*{                                                        */
 /*                                                         */
 /*                                                         */
 /*                                                         */
 /*   step_final_chemical_mass += new_chemical_mass[layer]; */
 /*   mass->set_layer(layer,new_chemical_mass[layer]);      */
 /*} // for layer                                           */
   float64 chemical_mass_inflow_now = flow[0] * layer_concentration[0];
   float64 chemical_mass_leached_now
      = initial_chemical_mass - step_final_chemical_mass + chemical_mass_inflow_now;      //080114

/*170925 RLN This may be needed check with Claudio

   chemical_mass_leached_now = must_be_0_or_greater<float64>(chemical_mass_leached_now); //170923RLN

*/

   inc_balance_leached_M(chemical_mass_leached_now); //kg/m2/h                   //080115
   // WARNING Used to be able to report leaching at layer,
   // but we no longer have chem flows by layer.

/*
if ((chemical_mass_leached_now < 0.0) && (chemical_mass_leached_now > -0.0000000001))
std::cerr << "error: negative chemical_mass_leached_now=" << chemical_mass_leached_now << "kgN/m2" <<std::endl;
*/

if (chemical_mass_leached_now > 100.0)
std::cerr << "error: unrealistic chemical_mass_leached_now=" << chemical_mass_leached_now<< "kgN/m2"  << std::endl;


   inc_reported_leached_M(chemical_mass_leached_now);                            //080115
   // Sum_Solute_Inflow and Sum_Solute_Leaching  not used in C++ version
}
//_2008-06-05__________________________________________________________
#ifdef OBSOLETE
// was resplaced in version 4.11.03
void Chemical_profile::transport_unidirectional_original
(nat8 num_layers_eff
,soil_layer_array64(flow)  // m3 water/m2 soil (m water depth)   flow out of the layer //070117
,soil_layer_array64(old_liquid_water_content)
,soil_layer_array64(new_liquid_water_content)
,float64 water_entering
,Seconds                at_time                                                  //071015
,Seconds                duration // seconds of duration                          //071015
,bool override_drainage_depth
,nat8 drainage_sublayer)
{ // This should work with any timestep - RLN

   soil_layer_array64(new_concentration); clear_layer_array64(new_concentration); // concentration of chemical in water kg/m3 //070924
   soil_layer_array64(new_amount);        clear_layer_array64(new_amount);       //070924
      mass->get_layers(new_amount);                                              //080117
//inf   Drainage = 0 'Initialize drainage flux

//C++ inf     'Calculates initial soil water profile (kg/m2 or mm) and total chemical mass in the soil profile (kg/m2)

//C++ handled    Initial_Profile_Chemical_Mass = 0
//C++ inf    Initial_Soil_Water_Profile = 0
//C++ inf    For L = 1 To Number_Of_Layers
//C++ inf    Initial_Soil_Water_Profile = Initial_Soil_Water_Profile + WC(L) * DZ(L) * Water_Density
//C++ handled    Initial_Profile_Chemical_Mass = Initial_Profile_Chemical_Mass + Chem_Mass(L)
//C++ inf    Next L

   // Equilibrate soil solution
   float64 K = get_constantC();
   float64 Q = get_constantQ();
   float64 unused_chem_mass_fraction_in_solution = 0;
   bool use_langmuir = (K > 0) && (Q > 0);
   for (nat8 layer = 1; layer < num_layers_eff; layer++)
   {
      float64 chemical_mass   = mass->get_layer(layer);
      float64 thickness_layer  = soil_layers.get_thickness_m(layer);
      new_concentration[layer] = use_langmuir
         ? calc_Langmuir_solute_equilibrium_concentration
            (chemical_mass
            ,soil_structure.get_bulk_density_Mg_m3(layer)            // 071001 Warning Claudio check units,
            ,thickness_layer
            ,old_liquid_water_content[layer]                         // 071001 Warning Claudio not sure if this should be new or old WC
            ,unused_chem_mass_fraction_in_solution)
         : chemical_mass / (thickness_layer * old_liquid_water_content[layer] * water_density);
   }

/* C++ inf
    'Calculate pore volume equivalent of each water pulse
    If Number_Of_Pulses = 0 Then
        Water_Depth_Equivalent_Of_One_Pore_Volume = water_density * DZ(1) * FC(1)
        Number_Of_Pulses = 1 + Int(Water_Flux_In / (0.2 * Water_Depth_Equivalent_Of_One_Pore_Volume))
    End If
*/
//C++ inf    For i = 1 To Number_Of_Pulses

   flow[0] = water_entering;                                                     //071001
   float64 actual_surface_infiltrated_M  //  kg/m2                               //071015
      = relinquish_surface_mass_pending_infiltration_M(at_time,duration);        //071015
   float64 surface_water_entering_concentration                                  //071015
      = actual_surface_infiltrated_M / water_entering;                           //071015

//C++ inf         ___________     Win = Water_Flux_In / Number_Of_Pulses
   float64 conc_in = surface_water_entering_concentration;  // Chemical concentration in irrigation water (kg chem/m3 water)

   float64 mass_out = 0;
   float64 conc_out = 0;
   for (nat8 layer = 1; layer <= num_layers_eff; layer++)
   {  float64 thickness_layer  = soil_layers.get_thickness_m(layer);
      float64 bypass_coef      = soil_hydraulic_properties.get_bypass_coef(layer);  //980102
      float64 Win  = flow[layer-1]; // m3 water/m2 soil (m water depth)
      float64 Wout = flow[layer];   // m3 water/m2 soil (m water depth)
      float64 mass_in  = Win * conc_in;        // kg/m2                          //071001
      conc_out = 0;
//C++ inf         Water_Depth_To_Reach_Field_Capacity = (FC(layer) - WC(layer)) * DZ(layer) * water_density
//C++ inf           'Determine water and chemical transport
//C++ inf         If Win > Water_Depth_To_Reach_Field_Capacity Then
      if (Wout > 0.0)
      {
//C++ inf               Wout = Win - Water_Depth_To_Reach_Field_Capacity

            conc_out =
               (  (1.0 - bypass_coef) * thickness_layer
                  /** water_density*/ * old_liquid_water_content[layer]
                  * new_concentration[layer]
                 + mass_in)
               / (Win  + (1.0 - bypass_coef) * thickness_layer
                        /** water_density*/ * old_liquid_water_content[layer]);

          // Note that this is different from the V.B. version because
          // the V.B. version concentrations are kg/kg not kg/m3.

//Conc_Out = ((1 - Bypass_Fraction) * DZ(j) * WD * WC(j) * C(j) + Win * Conc_In) / (Win + (1 - Bypass_Fraction) * DZ(j) * WD * WC(j))

//C++ inf               new_liquid_water_content(layer) = FC(layer)
      // else default  conc_out = 0;
//C++ inf               Wout = 0
//C++ default___________             conc_out = 0;
//C++ inf               new_liquid_water_content(layer) = old_liquid_water_content(layer) + Win / (water_density * DZ(layer))
      } // end if Wout
      mass_out = Wout * conc_out;                                                //071001
      float64 mass_change = mass_in - mass_out;
      float64 mass_layer  = mass->get_layer(layer);                              //080117
      if ((mass_change < 0) && (fabs(mass_change) > mass_layer ) )
      {  // In this case we moved all the chemical out of the layer
         mass_change = -mass_layer;
         mass_out = mass_in - mass_change;                                       //071001
         conc_out = mass_out / Wout;
         new_amount        [layer] = 0.0;
         new_concentration [layer] = 0.0;
      } else
      {  new_amount[layer] = mass_layer + mass_change;
         new_concentration[layer] = (new_liquid_water_content[layer] > 0.0)      //080601
             ? new_amount[layer] / (thickness_layer * new_liquid_water_content[layer] * water_density)
             : 0;                                                                //080601
      }
//C++ inf         Win = Wout
      conc_in = conc_out;

      if (override_drainage_depth)                                               //981230
            inc_reported_leached_M(mass_out);                                    //990317
   } // for layer
   for (nat8 layer = 1; layer <= num_layers_eff; layer++)                        //080115
   {                                                                             //080115
      mass->set_layer(layer,new_amount[layer]);                                  //080117
   } // for layer                                                               //080115
   mass->commit_diffs();                                                         //120731

//C++ inf      Drainage = Drainage + Wout     'in mm/day = kg/m2/day
   float64 leaching = mass_out;  /*leaching +Wout * Conc_Out */

//C++ handled     Next i 'Next pulse
//C++ handled     For i = 1 To Number_Of_Layers
//C++ handled     'Equilibrate soil solution
//C++ handled     If (K > 0) And (Q > 0) Then
//C++ handled        For L = 1 To layer - 1
//C++ handled          new_concentration(L) = EquilibriumConcentration(Chem_Mass(L), new_liquid_water_content(L), DZ(L), BD(L), K, Q)
//C++ handled        Next L
//C++ handled          Else
//C++ handled          For L = 1 To Number_Of_Layers
//C++ handled          new_concentration(L) = Chem_Mass(L) / (DZ(L) * new_liquid_water_content(L) * water_density)
//C++ handled          Next L
//C++ handled     End If

//C++ inf  Next i 'Next layer

//C++ handled 'Calculates Final total chemical mass in the soil profile (kg/m2)

//C++ handled   Final_Profile_Chemical_Mass = 0
//C++ handled   For L = 1 To Number_Of_Layers
//C++ handled     Final_Profile_Chemical_Mass = Final_Profile_Chemical_Mass + Chem_Mass(L)
//C++ handled   Next L

//C++ handled    Chemical_Balance = Chemical_Balance + (Initial_Profile_Chemical_Mass + Water_Flux_In * Chem_Conc_Irrigation _
//C++ handled                    - (Final_Profile_Chemical_Mass + leaching)) * 10000 'transform kg/m2 to kg/ha

//C++ handled  'Calculates final soil water profile (kg/m2 or mm)

//C++ inf    Final_Soil_Water_Profile = 0
//C++ inf    For L = 1 To Number_Of_Layers
//C++ inf    Final_Soil_Water_Profile = Final_Soil_Water_Profile + new_liquid_water_content(L) * DZ(L) * water_density
//C++ inf    Next L

//    Water_Balance = Water_Balance + (Initial_Soil_Water_Profile + Water_Flux_In - (Final_Soil_Water_Profile + Drainage))

   inc_balance_leached_M(leaching);
   inc_reported_leached_M(leaching);                                             //080115
   //For cascade method, nothing is done with water_table_conc.
}   // end of local function transport
//______________________________________________________________________________
#endif
// Thomas algorithm using a system of equations
#ifdef FINITE_DIFF
void Chemical_profile::transport_bidirectional_by_node
(nat8 num_nodes_eff
,nat8 number_of_real_plus_extended_nodes                                        //080219
,bool water_table_condition                                                      //080206
,soil_layer_array64(flow) // m3 water/m2 soil (m) in the day  flow out of the layer  from one node to the next (through the layer) Positive is downward.  (RLN not sure if nodal or layer)   //070117
,soil_node_array64(old_water_depth_nodal)  // Claudio what were the units of this?
,soil_node_array64(new_water_depth_nodal)
,float64 water_entering
,Seconds at_time                                                                 //071015
,Seconds duration // seconds of duration                                         //071015
,bool    override_leaching_depth                                                 //981230
,nat8   leaching_sublayer // for recording at an observation depth              //981230
)
{ // This should work with any timestep - RLN
  // Used for finite difference                                                  //071001
   CORN::Date_time_clad_64 now(today.get_date32(),at_time);                      //170425
   float64 init_mass = 0.0;
   bool is_NH4 = dynamic_cast<NH4_Profile *>(this) != 0;
   if (!is_NH4)
   {  init_mass = mass->sum_profile();
      // cout << init_mass;
   }
   // Convert layer chemical mass system to nodal system.
   //170217unused nat8 soil_num_layers   = soil_layers.get_number_layers();                    //071217
   Chemical_mass_profile_node_based &mass_node = (Chemical_mass_profile_node_based &)*mass;  //071217
   static const float64 nu = 0.6;
   soil_node_array64(sorbed_chemical_mass); clear_node_array64(sorbed_chemical_mass);  //080114
   soil_node_array64(bypass_chemical_mass); clear_node_array64(bypass_chemical_mass);  //080114

   //We need to get a common units for water_flow because water flux
   //  units are different in finite diff and cascade:
/*170424
   flow[0] = water_entering;
   // RLN Warning I think at this point water_entering is the value
   // of all the water entering the soil, but at this point
   // flow has already been accounted for

   // Get solute from application waiting on the surface:
   float64 actual_surface_infiltrated_M  // kg/ha                                //071015
      = relinquish_surface_mass_pending_infiltration_M(at_time,duration);        //071015
   float64 surface_water_entering_concentration  // kg chem / m3 water  Claudio check  //071015
      = CORN::is_approximately<float64>(water_entering,0.0,0.000001) ? 0.0
         : actual_surface_infiltrated_M / water_entering;                        //071015
*/


   commit_surface_pending_applications(now.get_datetime64());                    //170425
   float64 surface_M = get_surface_mass(); //  kg/m2                             //170425
   float64 surface_water_entering_concentration
      = (water_entering > 0.0) ? surface_M / water_entering : 0.0;
   float64 infiltrated_M = flow[0] * surface_water_entering_concentration;       //170425
   float64 surface_removed = deduct_surface_mass(infiltrated_M);                 //170425
   soil_layer_array64(node_concentration); clear_layer_array64(node_concentration);  // kg chem/m^3 water   //070924
   node_concentration[0] = surface_water_entering_concentration;                 //071220


#ifdef WATERTABLE
   if (water_table_condition)                                        // If Not FDWaterTransport.FreeDrainage Then //080206
   {
#ifdef NYI
      for (int8 node = num_nodes_eff + 1; node <= MAX_soil_layers; node++)
         node_concentration[node]                         //     Node_Concentration(Number_Of_Nodes + 1) = Water_Table_Concentration
          = water_table_concentration;
#endif
       node_concentration[num_nodes_eff + 1]                         //     Node_Concentration(Number_Of_Nodes + 1) = Water_Table_Concentration //080206
          = water_table_concentration;                                           //080206
   }
#endif
   float64 initial_chemical_mass = 0.0;                                          //080114
   float64 sorbed_chemical_mass_sum = 0.0;                                       //080114

#ifdef _DEBUG
soil_node_array64(DEBUG_chemical_mass_node_E); clear_node_array64(DEBUG_chemical_mass_node_E); // only for debugging
soil_node_array64(DEBUG_chemical_conc_E); clear_node_array64(DEBUG_chemical_conc_E);
#endif
   soil_node_array64(node_chemical_mass); clear_node_array64(node_chemical_mass);                     //080219
   soil_node_array64(node_bypassed_chemical_mass); clear_node_array64(node_bypassed_chemical_mass);   //081001
   for (nat8 node =  1 ; node <= number_of_real_plus_extended_nodes; node ++)                        //080219
   {  // RLN The following is consistent with the V.B. but I am not sure the V.B. code is right.      //080219
      node_chemical_mass[node] = mass_node.get_node(node,number_of_real_plus_extended_nodes);         //080220
      initial_chemical_mass +=                                                                        //080114
         node_chemical_mass[node];
#ifdef _DEBUG
DEBUG_chemical_mass_node_E[node] = node_chemical_mass[node]* chem_to_element_factor; // only for debugging
DEBUG_chemical_conc_E[node] =  node_concentration[node] *  chem_to_element_factor;
#endif
   }
   for (nat8 node =  1 ; node <= num_nodes_eff ; node ++)                       //071220
   {  nat8 layer = node;                                                        //071220
      float64      thickness_layer  = soil_layers.get_thickness_m(layer); // should be 0 for    num_nodes_eff
      float64 thickness_prev_layer =  soil_layers.get_thickness_m(layer-1);      //071220
      float64 node_domain_thickness = (thickness_layer  + thickness_prev_layer) / 2.0; //071220
      // water content for the node domain at the beginning of the current time step, before FD solution for the current time step
      float64 old_water_content_node = old_water_depth_nodal[node] / node_domain_thickness;  //080114
      float64 chemical_mass_in_node   // kg chem/ m^2 soil                       //080114
         =  node_chemical_mass[node];                                            //080219
      // Added adjustment for bypass. Bypassed chemical mass will stay in the layer (not available for transport) 081001
      float64 bypass_coef      = soil_hydraulic_properties.get_bypass_coef(layer);   // RLN: Warning I am presuming we can simply use the layer bypass coefficient for the node
      bypass_chemical_mass[node]                                                 //081001 120516 now in V.B. Code
         = node_chemical_mass[node] * bypass_coef;                               //081001 120516 now in V.B. Code
      float64 chemical_mass_in_node_available_for_transport                      //081001 120516 now in V.B. Code
         =  chemical_mass_in_node -  bypass_chemical_mass[node];                 //081001
      #ifdef _DEBUG
      DEBUG_chemical_mass_node_E[node] = chemical_mass_in_node * chem_to_element_factor;
      #endif

      node_concentration[node]   = 0.0;                                          //080114
      sorbed_chemical_mass[node] = 0.0;                                          //080114
      if (chemical_mass_in_node_available_for_transport > 0)                     //080114
      {  bool is_NH4 = dynamic_cast<NH4_Profile *>(this) != 0;
         if (is_NH4 /*NYI || is_phosphorus*/ ) // Eventually we will have phosphorus
         {
            float64 bulk_density =
            (node == 1)
            ?  soil_structure.get_bulk_density_g_cm3(1)
            :  (node == num_nodes_eff)
               ? soil_structure.get_bulk_density_g_cm3(layer-1)
               :  (soil_structure.get_bulk_density_g_cm3(layer - 1) * thickness_prev_layer
                   + soil_structure.get_bulk_density_g_cm3(layer) * thickness_layer)
                  / (thickness_layer + thickness_prev_layer);
            // Node concentration in kg Chem/m3 water
            float64 chem_mass_fraction_in_solution = 0; //  kg Chem / m3 water
            node_concentration[node]
               = calc_Langmuir_solute_equilibrium_concentration
                  (chemical_mass_in_node_available_for_transport                 //081001
                  ,bulk_density
                  ,node_domain_thickness
                  ,old_water_content_node
                  ,chem_mass_fraction_in_solution);  // <-- returned by calc_Langmuir_solute_equilibrium_concentration
            sorbed_chemical_mass[node]                                           //081001
               = chemical_mass_in_node_available_for_transport
                     * (1.0 - chem_mass_fraction_in_solution);
            sorbed_chemical_mass_sum += sorbed_chemical_mass[node];
            // sorbed_chemical_mass is chemical mass not available for movement
         } else
         {  // Not NH4
            node_concentration[node] = chemical_mass_in_node_available_for_transport // 081001 chemical_mass_in_node
                  / (node_domain_thickness * old_water_content_node);
            sorbed_chemical_mass[node] = 0.0;
         }
      }
#ifdef _DEBUG
DEBUG_chemical_conc_E[node] =  node_concentration[node] *  chem_to_element_factor; // for debugging only
#endif
   }
   // Compute coefficients to build the tridiagonal matrix.
   soil_node_array64(a_term);   clear_node_array64(a_term);                      //070924
   soil_node_array64(b_term);   clear_node_array64(b_term);                      //070924
   soil_node_array64(c_term);   clear_node_array64(c_term);                      //070924
   soil_node_array64(d_term);   clear_node_array64(d_term);                      //070924

soil_node_array64(DEBUG_d_term_E);   clear_node_array64(DEBUG_d_term_E); // for debugging only

   for (nat8 node =  1 ; node <= num_nodes_eff; node ++)
   {  // System of equations   4 euqations 2 unknowns with a fixed concentration above and below as boundary conditions
     if (flow[node] > 0)  //flow from current layer is downward
     {  if (flow[node-1] > 0 )  // Case 1: flow from current layer is downward and flow from upper layer is downward or zero  //080206
        {  a_term[node] = flow[node-1]  * nu;
           b_term[node] = - new_water_depth_nodal[node] - flow[node]  * nu;
           c_term[node] = 0.0;
           float64 nu_term = node == 1 ? 1.0 : (1.0-nu);                         //080206
           d_term[node] =  - old_water_depth_nodal[node] * node_concentration[node]
                           + flow[node]   * (1.0 - nu) * node_concentration[node]
                           - flow[node-1] * nu_term    * node_concentration[node-1];   //080206
        } else  // Case 2: if flow[node-1] <= 0 THEN flow from current layer is downward and flow from upper layer is upward
        {  a_term[node] = 0.0;
           b_term[node] = - new_water_depth_nodal[node] + nu * (flow[node-1] - flow[node]);
           c_term[node] = 0.0;
           d_term[node] =  - old_water_depth_nodal[node] * node_concentration[node]
                           + flow[node]   * (1.0 - nu) * node_concentration[node]
                           - flow[node-1] * (1.0 - nu) * node_concentration[node] ;
        }
        if (d_term[node] > 0) // avoid negative chemical mass
            node_concentration[node] -= d_term[node] / flow[node] * (1.0 - nu);
     }   // end  of downward flow
     else  // if flow[node] < 0 THEN flow from current layer is upward
     {  if (flow[node-1] > 0) // Case 3: flow from current layer is upward and flow from upper layer is downward or zero   //080206
        {  a_term[node] = flow[node-1] * nu;
           b_term[node] = - new_water_depth_nodal[node];
           c_term[node] = - flow[node] * nu;
           float64 nu_term = node == 1 ? 1.0 : (1.0-nu);                         //080206
           d_term[node] =  - old_water_depth_nodal[node] * node_concentration[node]
                           + flow[node]   * (1.0 - nu) * node_concentration[node+1]
                           - flow[node-1] * nu_term    * node_concentration[node-1];  //080206
        } else //Case 4: if flow[i-1] <= 0 THEN  flow from current layer is upward and flow from upper layer is upward
        {  a_term[node] = 0;
           b_term[node] = - new_water_depth_nodal[node] + flow[node-1] * nu;
           c_term[node] = - flow[node] * nu;
           d_term[node] =  - old_water_depth_nodal[node] * node_concentration[node]
                           + flow[node]   * (1.0 - nu) * node_concentration[node+1]
                           - flow[node-1] * (1.0 - nu) * node_concentration[node]  ;
        }
        if (d_term[node] > 0) // avoid negative chemical mass                      //120517
            node_concentration[node+1] -= d_term[node] / flow[node] * (1.0 - nu);
     }  /*end flow upward*/

DEBUG_d_term_E[node] = d_term[node] *  chem_to_element_factor;
                 if (CORN::is_approximately<float64>(a_term[node],0.0,0.0000000000001)) a_term[node] = 0.0;
                 if (CORN::is_approximately<float64>(b_term[node],0.0,0.0000000000001)) b_term[node] = 0.0;
                 if (CORN::is_approximately<float64>(c_term[node],0.0,0.0000000000001)) c_term[node] = 0.0;
                 if (CORN::is_approximately<float64>(d_term[node],0.0,0.0000000000001)) d_term[node] = 0.0;


  } /*end of for i=1 to nl_effective*/
   soil_node_array64(new_node_chemical_mass); clear_node_array64(new_node_chemical_mass); //080114
   resolution_of_Thomas_agorithm                                                          //080606
      (num_nodes_eff                                                                      //080606
      ,a_term
      ,b_term
      ,c_term
      ,d_term
      ,new_water_depth_nodal
      ,node_concentration
      ,sorbed_chemical_mass // layer or nodal array                              //080606
      ,new_node_chemical_mass                                                    //081001
      );                                                                         //080606
   for (nat8 node =  1 ; node <= num_nodes_eff ; node ++)                        //081001
   {
      new_node_chemical_mass[node] += bypass_chemical_mass[node];                         // as of 081001 not in V.B. Code

      if (new_node_chemical_mass[node] < 0.0)
         std::cout << "Reached" << std::endl;
   }
#ifdef WATERTABLE
   if (water_table_curve)
      for (nat8 node = num_nodes_eff + 1; node <= number_of_real_plus_extended_nodes ; node++)           //110330
      {  /* make sure with have chemical mass from water table */                    //110330
         nat8 layer = node;
         float64 thickness_layer  = soil_layers.get_thickness_m(layer);
         float64 thickness_prev_layer =  soil_layers.get_thickness_m(layer-1);
         float64 node_domain_thickness = (thickness_layer  + thickness_prev_layer) / 2.0;
         float64 saturation_WC = soil_hydraulic_properties.get_saturation_water_content_volumetric(node,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822);
         float64 water_table_conc = water_table_curve->get_for_today();  // kg/m³
         float64 chem_mass = water_table_conc * (node_domain_thickness * saturation_WC); //110330
         	//       kg/m² = kg/m³ * ( m * m³/m³)
         new_node_chemical_mass[node]  = chem_mass;  // kg/m²
      } // for each node
#endif
   float64 final_chemical_mass_eff = mass_node.set_nodes                         //080220
      (new_node_chemical_mass                                                    //080220
      //090923 I think this line is needed instead of the next but will need to fixup balance /*090923_*/       ,num_nodes_eff
      ,number_of_real_plus_extended_nodes                                        //080220
      ,chem_to_element_factor);                                                  //080220
   float64 chemical_mass_inflow_now = flow[0] * node_concentration[0];           //080114
   float64 chemical_mass_leached_now = initial_chemical_mass - final_chemical_mass_eff + chemical_mass_inflow_now;   //080114
   //UNUSED     sum_solute_inflow += chemical_mass_inflow_now;                   //080114
   inc_balance_leached_M(chemical_mass_leached_now); //kg/m2/h                   //080115

   // WARNING Used to be able to report leaching at layer,                       //080115
   // but we no longer have chem flows by layer.                                 //080115

   inc_reported_leached_M(chemical_mass_leached_now);                            //080115

/* for debugging:
float64 final_mass = mass->sum_profile() + chemical_mass_leached_now;
float64 final_mass_E =  final_mass * chem_to_element_factor;
*/
}   // end of local function transport
#endif
//______________________________________________________________________________
void Chemical_profile::inc_balance_leached_M(float64 leached_molecular)
{  if (! CORN::is_approximately<float64>(leached_molecular,0.0,0.00000001))              //120704
   {  balance_leached_molecular +=leached_molecular;

      #ifndef NEW_N_XFER_BAL
      if (ANNL_bal_accums)       ANNL_bal_accums   ->inc_balance_leached_M(leached_molecular);
      if (GP_bal_accums_current) GP_bal_accums_current->inc_balance_leached_M(leached_molecular);
      if (CONT_bal_accums)       CONT_bal_accums  ->inc_balance_leached_M(leached_molecular);
      #if (REACCH_VERSION < 2)
      if (FALLOW_bal_accums)     FALLOW_bal_accums->inc_balance_leached_M(leached_molecular);
      #endif
      #endif
   }
}
//_1999-03-17___________________________________________________________________
void Chemical_profile::inc_reported_leached_M(float64 leached_molecular)
{  if (! CORN::is_approximately<float64>(leached_molecular,0.0,0.00000001))              //120704
   {  reported_leached_molecular +=leached_molecular;
      #ifndef NEW_N_XFER_BAL
      if (ANNL_bal_accums)       ANNL_bal_accums      ->inc_reported_leached_M(leached_molecular);
      if (GP_bal_accums_current) GP_bal_accums_current->inc_reported_leached_M(leached_molecular);
      if (CONT_bal_accums)       CONT_bal_accums      ->inc_reported_leached_M(leached_molecular);
      #if ( REACCH_VERSION < 2)
      if (FALLOW_bal_accums)     FALLOW_bal_accums    ->inc_reported_leached_M(leached_molecular);
      #endif
      #endif
   }
}
//_1999-03-17___________________________________________________________________
void Chemical_profile::set_reported_leached_M()
{  reported_leached_molecular       = balance_leached_molecular;
   #ifndef NEW_N_XFER_BAL
   if (ANNL_bal_accums)       ANNL_bal_accums      ->set_reported_leached_M();
   if (GP_bal_accums_current) GP_bal_accums_current->set_reported_leached_M();
   if (CONT_bal_accums)       CONT_bal_accums      ->set_reported_leached_M();
   #if (REACCH_VERSION < 2)
   if (FALLOW_bal_accums)     FALLOW_bal_accums    ->set_reported_leached_M();
   #endif
   #endif
}
//_1999-03-17___________________________________________________________________
float64 Chemical_pool::water_content_correction
(float64 //sublayer_saturation_water_content // unused parameter given for virtual compatibility
,float64 //sublayer_water_content            // unused parameter given for virtual compatibility
,float64 //sublayer_reference_water_content  // unused parameter given for virtual compatibility
,float64 //sublayer_bulk_density             // unused parameter given for virtual compatibility
)
{ return 1.0; }
//______________________________________________________________________________
float64 Chemical_pool::get_current_profile_content_M()
{  float64 current_profile_content_M =
   mass->sum_profile();                                                          //080117
   return current_profile_content_M;
}
//_1998-10-06___________________________________________________________________
bool Chemical_pool::reinitialize_for_sowing_or_restart() // 960806P   (sowing or reemergence
{  // moved to GP_rprt_accums
   //GP_original_profile_content_M := current_profile_content_M;
   // Through away the fallow and start the growing season accums
   #if (REACCH_VERSION < 2)
   delete FALLOW_bal_accums; FALLOW_bal_accums = 0;                              //170628_990317
   #endif
   if (GP_bal_accums_current)  delete GP_bal_accums_current;                     //120503
   GP_bal_accums_current = 0;                                                    //070801
   GP_bal_accums_current= new Chemical_balance_accumulators
      (get_current_profile_content_M()
      ,name
      ,get_transformation_name()
      ,chem_to_element_factor
      ,has_uptake());
   return true;                                                                  //131217
}
//______________________________________________________________________________
bool Chemical_pool::reinitialize_at_end_season()
{
   // Throw away the growing season and start the fallow                         //041001
   #if (REACCH_VERSION < 2)
//   if (GP_bal_accums_at_end_season)     delete GP_bal_accums_at_end_season; GP_bal_accums_at_end_season=   GP_bal_accums_current;  //070801
//   GP_bal_accums_current = 0;                                                    //070801
   FALLOW_bal_accums = new Chemical_balance_accumulators                         //050114
      (get_current_profile_content_M(),name,get_transformation_name(),chem_to_element_factor,has_uptake());
   #endif
   return true;                                                                  //131217
}
//_1996-09-02___________________________________________________________________
void Chemical_pool::remove_sublayer_2(nat8 num_layers)
{
   if (num_layers >= 3)
   {  // Move any residual chemical to the next layer.
      mass->set_layer(3,mass->get_layer(2));                                     //080117
      #ifdef OLD_N_XFER
      //removed 170502
      transformed_from_M[3] += transformed_from_M[2];
      #else
      transformed_E_output.set(3,transformed_E_output.get(2));                   //170502
      transformed_E_output.remove_at(3);                                         //170502
      #endif
      for (nat8 layer = 2; layer <=num_layers - 1 ; layer++)
      {  mass->set_layer(layer,mass->get_layer(layer+1));                        //080117
         #ifdef OLD_N_XFER
         transformed_from_M[layer] = transformed_from_M[layer+1];
         #else
         // remove_at moves/copies values
         #endif
      }
      mass->set_layer(num_layers,0.0);                                           //080117
      #ifdef OLD_N_XFER
      transformed_from_M[num_layers] = 0;
      #else
         // remove_at moves/copies values
      #endif
   } else   // In the unlikely event that we deplete all the soil, just put
   {        // the residual in the evaporative layer which we dont remove.
      mass->set_layer(1,mass->get_layer(2));                                     //080117
      #ifdef OLD_N_XFER
      transformed_from_M[1] = transformed_from_M[2];
      #else
      transformed_E_output.set(1,transformed_E_output.get(2));                   //170502
      #endif
   }
   mass->commit_diffs();                                                         //120731
}
//_1996-08-28___________________________________________________________________
float64 Chemical_pool::moisture_function
(float64 // unused water_field_porosity
,float64) //unused sublayer_bulk_density
{ return NO_MOISTURE_FUNCTION; }
//______________________________________________________________________________
float64  Chemical_pool::transformation_rate
(float64 //unused soil_temperature
,float64) //unused water_content_correct)
{ return 0.0; }
//______________________________________________________________________________
void Chemical_pool::transformation
(nat8 layer
,float64 sublayer_water_content
,float64 sublayer_saturation_water_content
,float64 sublayer_reference_water_content
,float64 sublayer_temperature
,float64 sublayer_bulk_density
,Seconds preferred_transformation_time_step_used_by_subclasses                   //060510
   // The original transformation time step is 86400 seconds (1 day)
   // When using  Organic_matter_residues_profile_V4_4,
   // the nitrification and denitrification transformation timestep is 1 hour
   // (or the timestep of the infiltration model).
#ifdef OLD_N_XFER
,float64 &transformed_to_M
#endif
)
{  float64 trans_rate =                                                          //981212
        transformation_rate
         (sublayer_temperature,
          water_content_correction
             (sublayer_saturation_water_content,
              sublayer_water_content,sublayer_reference_water_content,sublayer_bulk_density));
   float64 water_filled_porosity
      = sublayer_water_content / (1.0 - sublayer_bulk_density / 2.65);           //060629
   float64 moist_funct = moisture_function                                       //060629
         (water_filled_porosity,1.0);                                            //060629
   float64 mass_before_transformation = mass->get_layer(layer);                  //170502
   float64 transformed_M =
      mass_before_transformation                                                 //170502
      //170502 mass->get_layer(layer)                                            //080117
      * (1- exp(- trans_rate )) *  moist_funct;
   inc_transformed_to(transformed_M);                                            //990317
   mass->dec_layer(layer,transformed_M);                                         //120731_080117
#ifdef OLD_N_XFER
  transformed_to_M += transformed_M;   // Incremented because there may be two sources of transformation
#else
   if (receiver)                                                                 //170524
   {  float64 loss = mass_before_transformation - transformed_M;                 //170502
      receiver->take_elemental_from_transformation(layer,loss);                  //170502
   }
#endif
}
//______________________________________________________________________________
#ifndef OLD_N_XFER
float64 Chemical_pool::take_elemental_from_transformation
(nat8   layer
,float64 elemental_given)
{
   float64 mass_given = element_to_chem_factor * elemental_given;
   mass->inc_layer(layer,mass_given);
   return elemental_given;
}
#endif
//_2017-05-02_______________________________take_elemental_from_transformation_/
void Chemical_pool::inc_transformed_to(float64 transformed_M)
{
   #ifdef OLD_N_XFER
   if (transformed_M != 0)                                                       //120704
   #else
   if (!CORN::is_approximately<float64>(transformed_M,0.0,0.00000001))           //170503
   #endif
   {
      if (ANNL_bal_accums)       ANNL_bal_accums   ->inc_transformed_to(transformed_M);
      if (GP_bal_accums_current) GP_bal_accums_current->inc_transformed_to(transformed_M);
      if (CONT_bal_accums)       CONT_bal_accums   ->inc_transformed_to(transformed_M);
      #if ( REACCH_VERSION < 2)
      if (FALLOW_bal_accums)     FALLOW_bal_accums ->inc_transformed_to(transformed_M);
      #endif
   }
}
//_1999-03-17___________________________________________________________________
void Chemical_pool::dec_residue(float64 _amount_M)
{
   if (_amount_M != 0)                                                           //120704
   {
      if (ANNL_bal_accums)       ANNL_bal_accums   ->dec_residue(_amount_M);
      if (GP_bal_accums_current) GP_bal_accums_current->dec_residue(_amount_M);
      if (CONT_bal_accums)       CONT_bal_accums   ->dec_residue(_amount_M);
      #if ( REACCH_VERSION < 2)
      if (FALLOW_bal_accums)     FALLOW_bal_accums ->dec_residue(_amount_M);
      #endif
   }
}
//_1999-03-17___________________________________________________________________
void Chemical_pool::recalibrate
( soil_layer_array64(new_amount_E_by_layer)                                      //011119
, bool for_initialization)
{  nat8 soil_num_layers = soil_layers.get_number_layers();
   soil_layer_array64(new_mass_layers); clear_layer_array64(new_mass_layers);    //080208
   for (int layer = 1; layer <= soil_num_layers; layer ++)
   {  float64 amount_E_sl = new_amount_E_by_layer[layer];                        //020305
         // Note that amount_E could either be mass or ECw depending on the context
      new_mass_layers[layer] =
         element_to_chem_factor * (per_ha_to_per_m2(amount_E_sl));               //080206
   }
   recalibrate_set_mass(new_mass_layers, for_initialization);                    //080402
}
//_2001-11-15___________________________________________________________________
void Chemical_pool::recalibrate_set_mass
(soil_layer_array64(new_mass_layers),bool for_initialization)
{  recalibration = 0.0;
   nat8 soil_num_layers = soil_layers.get_number_layers();
   for (int layer = 1; layer <= soil_num_layers; layer ++)
   {  float64 curr_mass_layer = mass->get_layer(layer);                          //080208
      float64 diff =curr_mass_layer - new_mass_layers[layer];                    //080403
      recalibration += diff;
   }
   mass->set_layers(new_mass_layers);
   if (for_initialization)
      recalibration = 0.0;                                                       //011119
      // When we are initializing the chemical profile, we just set the new values (no recalibration adjustment to the balance).
   else                                                                             //011119
   {
      if (ANNL_bal_accums)       ANNL_bal_accums      ->recalibrate(recalibration); //011115
      if (GP_bal_accums_current) GP_bal_accums_current->recalibrate(recalibration); //011115
      if (CONT_bal_accums)       CONT_bal_accums      ->recalibrate(recalibration); //011115
      #if (REACCH_VERSION < 2)
      if (FALLOW_bal_accums)     FALLOW_bal_accums    ->recalibrate(recalibration); //011115
      #endif
   }
}
//_2008-04-03___________________________________________________________________
float64 Chemical_profile::
calc_Langmuir_solute_equilibrium_concentration
(float64 chemical_mass                    // Note that these are currently used by node but this function should be compatible with by layer
,float64 soil_bulk_density_g_per_cm3                // Therefore, make sure to pass these as parameters,
,float64 layer_thickness                  // and not get them from soil structure or soil hydrology.
,float64 water_content_volumetric
,float64 &chem_mass_fraction_in_solution)                                  const
{  if (CORN::is_approximately<float64>(chemical_mass,0.0,0.0000001)) return 0.0;
   static const float64 g_per_cm3_to_kg_per_m3 = 1000.0;
   float64 bulk_density_kg_m3 =  soil_bulk_density_g_per_cm3 * g_per_cm3_to_kg_per_m3; //080128
   float64 water_content_gravimetric // kg water/kg soil
      = water_content_volumetric * water_density / (bulk_density_kg_m3);
   float64 K = get_constantC();
   float64 Q = get_constantQ();
   float64 w = water_content_gravimetric;  // kg water/kg soil
   float64 chem_mass_sorbed_and_in_solution   // kg salt/kg soil
      = chemical_mass / (bulk_density_kg_m3 * layer_thickness);      // THe bulk density is simply for convertion for volume
   float64 S = chem_mass_sorbed_and_in_solution;
      // equivelent to XS + w[S]
      // [S] is salt in solution (kg salt/kg water)
      // XS is sorbed salt(kg salt/kg soil)
   float64 A = w * K;
   float64 B = K * Q + w - K * S;
   float64 C = -S;
   float64 concentration_kgChem_per_kgH2O = CORN_quadratic1(A,B,C,1); // (-B + Sqr(B * B - 4 * A * C)) / (2 * A)
   chem_mass_fraction_in_solution = concentration_kgChem_per_kgH2O * w / S;
   // Converted from kgChem/kg Soil to kgChem/m3 water
   return concentration_kgChem_per_kgH2O * water_density;
}
//_2008-01-15___________________________________________________________________
/*
Private Function EquilibriumConcentration(ByVal Chemical_Mass As Single, _
  WC As Single, DZ As Single, BD As Single, K As Single, Q As Single) As Single
 Const water_density = 1000 'Water density (kg/m3)
 Dim Gravimetric_WC As Single, A As Single, B As Single, C As Single

Gravimetric_WC = WC * water_density / BD
                 get_water_plus_ice_content_gravimetric(layer)

Chemical_Mass = Chemical_Mass / (DZ * BD)
A = K * Gravimetric_WC
B = K * Q + Gravimetric_WC - K * Chemical_Mass
C = -Chemical_Mass
EquilibriumConcentration = (-B + Sqr(B * B - 4 * A * C)) / (2 * A)

End Function
*/
//______________________________________________________________________________
void Chemical_pool::inc_transformed_from(float64 transformed_M)
{  if (transformed_M != 0.0)
   {  if (ANNL_bal_accums)       ANNL_bal_accums      ->inc_transformed_from(transformed_M);
      if (GP_bal_accums_current) GP_bal_accums_current->inc_transformed_from(transformed_M);
      if (CONT_bal_accums)       CONT_bal_accums      ->inc_transformed_from(transformed_M);
      #if (REACCH_VERSION < 2)
      if (FALLOW_bal_accums)     FALLOW_bal_accums    ->inc_transformed_from(transformed_M);
      #endif
   }
}
//_1999-03-17___________________________________________________________________
float64 Chemical_pool::balance(nat8 soil_num_layers)
{  nat8 layer;
/*170531 obs
   #ifdef OLD_N_XFER
   profile_transformed_from_M= 0;
   for (layer = 1; layer <= soil_num_layers; layer ++)
   {  inc_transformed_from(transformed_from_M[layer]);
      profile_transformed_from_M+= transformed_from_M[layer];
   }
   #else
   // I think profile_transformed_from_M is obsolete
   #endif
*/
   float64 balance_error = 0.0;
   if (name != LABEL_POT_MINERALIZABLE_N) // <- No need to balance pot min N     //980304
   {  float64 current_profile_content = get_current_profile_content_M();
      if (ANNL_bal_accums) balance_error = ANNL_bal_accums   ->balance(current_profile_content);
      if (GP_bal_accums_current) GP_bal_accums_current->balance(current_profile_content);
      if (CONT_bal_accums)       CONT_bal_accums   ->balance(current_profile_content);
      #if (REACCH_VERSION < 2)
      if (FALLOW_bal_accums)     FALLOW_bal_accums ->balance(current_profile_content);
      #endif
      recalibration = 0.0;                                                       //011119
   }
   return    balance_error ;
}
//_1999-03-17?__________________________________________________________________
bool Chemical_pool::start_day()                                    modification_
{
   transformed_E_output.clear();
   #ifndef OLD_N_XFER
   #endif
   return CS::Simulation_element_abstract::start_day();
}
//_2007-10-15___________________________________________________________________/
bool Chemical_profile::start_day()
{  //080308 Now nothing to do, the mass pending just remains pending, to this new day, any applications today will simply increase the mass pending and the application rate respectively
   bool started = true;
   balance_leached_molecular = 0.0;                                              //981230
   reported_leached_molecular = 0.0;                                             //981230
   #ifdef WATERTABLE
   if (water_table_curve)
      started &= water_table_curve->start_day();                                 //151113_150925
      // Because water_table_curve is currently owned by this
      // this should be reponsible for starting it.
      // However, the the water table curves are now simulation elements
      // and probably should be owned and maintained by the instanciator.
      // Note the chemical profile probable should be Simulation_element_composite
   #endif
   return Chemical_pool::start_day();                                            //170502_151113
}
//_2007-10-15___________________________________________________________________


/* Notes for salinity

 conc =    Elec cond of soil solution * 0.64
// 0.64 is the typical conversion factor to convert salinity to concentration
 ^- kg salt / m^3 water

amount =  conc * water_cont * thickness

salinity only moves
has no transformation
no exchange
no uptake

Is applied as a flux
osmoticpot_soilsolut = - 56.25 * conc
osmoticpot_sat_extract =  osmoticpot_soilsolut * water_cont / (2.0 * field_cap)
root permeability
*/
//______________________________________________________________________________

//060207 1600 lines
//060502 1245 lines
//080920 2250 lines
//110704 1499 lines

