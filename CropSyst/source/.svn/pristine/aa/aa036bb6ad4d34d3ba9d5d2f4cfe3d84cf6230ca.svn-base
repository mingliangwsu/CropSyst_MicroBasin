#include "corn/math/compare.h"
#include "crop/crop_emergence.h"
#include "crop/crop_param.h"
#include "seeding_param.h"
#include "soil/soil_abstract.h"
#include "soil/hydrology_interface.h"
#include "corn/measure/measures.h"
#include "corn/condcomp.h"
#ifdef DETAIL_FILE
#  define DETAIL
#else
#  define DETAIL _COMMENT_
#endif
#if (CROPSYST_VERSION >= 5)
namespace CropSyst {
#endif
//______________________________________________________________________________
Crop_emergence_hydrothermal_time::Crop_emergence_hydrothermal_time
(CropSyst::Crop_parameters_struct::Emergence_hydro_thermal &_parameters
,float32               _specific_leaf_area_m2_kg
,Seeding_parameters   *_seeding_parameters)
: Crop_emergence_abstract()
, parameters(_parameters)
, seeding_parameters(_seeding_parameters)
, owns_seeding_parameters(0)
, specific_leaf_area_m2_kg(_specific_leaf_area_m2_kg)
, first_day(false)
, emerged(false)
, at_anticipated_pot_emergence(false)
, anticipated_pot_emergence_seeds_m2(false)
, days_after_sowing(0)
, p_i_pending(1)
, cotyledon_GAI(0.0)
, cotyledon_biomass(0.0)
, emerged_seeds_m2(0.0)
{
   anticipated_pot_emergence_seeds_m2
   = seeding_parameters->rate_seeds_m2 * seeding_parameters->emergence_rate_percent / 100.0;
   if (seeding_parameters == 0)
   {   // seeding parameters not specified, using defaults
       seeding_parameters = new Seeding_parameters;
       owns_seeding_parameters = true;
   }
   for (int i = 0; i < 11; i++)
      poor_conditions_delay[i] = 0;
}
//______________________________________________________________________________
Crop_emergence_hydrothermal_time::~Crop_emergence_hydrothermal_time()
{  if (owns_seeding_parameters && seeding_parameters)
      delete seeding_parameters;
   seeding_parameters = 0;
}
//______________________________________________________________________________
void Crop_emergence_hydrothermal_time::process
(
Soil_interface &soil)
{
//   const float32 a =  22.35;  now parameters
//   const float32 b = 129.66;
   nat8     seed_layer = soil.ref_layers()->get_layer_at_depth(cm_to_m(seeding_parameters->sowing_depth_cm));
   float32  soil_temp_seed_layer = soil.get_temperature_C(seed_layer);
   float32  soil_water_pot_seed_layer_MPa = J_kg_to_MPa( soil.ref_hydrology()->get_water_potential(seed_layer)); //160412
   float32  mean_base_soil_water_pot_MPa  = J_kg_to_MPa(parameters.mean_base_soil_water_pot_J_kg);
   float32  stdev_base_soil_water_pot_MPa = J_kg_to_MPa(parameters.stdev_base_soil_water_pot_J_kg);
   float32  hydrothermal_time_const = parameters.a_slope * seeding_parameters->sowing_depth_cm + parameters.b_intercept;
   cotyledon_GAI=0.0;
   cotyledon_biomass=0.0;
   first_day = false;
   float32 max_p  = seeding_parameters->emergence_rate_percent/100.0;
   max_p = std::min<float32>(max_p,0.9995);
   float32 emerged_today = 0.0;
   float32 p = (float32)1.0/10.0;
   bool   past_probability = false;
#ifdef _Windows
   if (detail_txt_file) (*detail_txt_file) << "DAS=" <<days_after_sowing << "\t";
#endif
   for (int p_i = p_i_pending; p_i <= 10 && !past_probability/*p <= max_p*/; p_i++)
   {  p = (float32)p_i/10.0;
      if (p_i == 10) p = 0.999;
      float32 act_emergence_this_p = 0.1;
      if (p >= max_p)
      {  act_emergence_this_p = max_p - (p - 0.1);
         // at_anticipated_pot_emergence = true;
         p  = max_p;
         past_probability = true;
      }
      float32 probit_p = normal_distr.inverse_standard_CDF(p);
      float32 temperature_factor = (soil_temp_seed_layer - parameters.germination_base_temperature);
      float32 water_pot_factor = (soil_water_pot_seed_layer_MPa - mean_base_soil_water_pot_MPa
             - probit_p * stdev_base_soil_water_pot_MPa)
             +0.0000000001; // to avoid div 0 error
      float32 TE_p = hydrothermal_time_const /(temperature_factor * water_pot_factor);
      float32 TE_pi_mean = 0;
      if (TE_p > 0.0)
      {  TE[p_i].append(TE_p);
         TE_pi_mean = TE[p_i].get_mean();
         if (days_after_sowing >= (TE_pi_mean + (float32)poor_conditions_delay[p_i]))
         {  p_i_pending = p_i+1;
            float32 emerged_now = seeding_parameters->rate_seeds_m2 * act_emergence_this_p; //  0.1;
            emerged_today += emerged_now;
            first_day |= (p_i == 1);   // first cohort emerged
         }
      } else
         poor_conditions_delay[p_i] += 1;
#ifdef _Windows
      if (detail_txt_file)
      {
         (*detail_txt_file) << "{" << "p=" << p /*<< " probit(p)=" << probit_p */
                       << " T=" << soil_temp_seed_layer
                       << " htc=" << hydrothermal_time_const
                       << " TF=" << temperature_factor
                       << " WF=" << water_pot_factor
                       << " psi=" << soil_water_pot_seed_layer_MPa
                       << " rmTE(p)=" << TE_pi_mean
                       << " delay=" << (poor_conditions_delay[p_i])
                       << "}";
      }
#endif
   }
   if (emerged_today > 0.0)
   {  emerged_seeds_m2 += emerged_today;
      if  (emerged_seeds_m2 >= (anticipated_pot_emergence_seeds_m2-0.001))
         at_anticipated_pot_emergence = true;
      float32  seedling_leaf_area_m2 = cm2_to_m2(parameters.seedling_leaf_area_cm2);
      cotyledon_GAI = seedling_leaf_area_m2 * emerged_today;
      cotyledon_biomass = cotyledon_GAI / specific_leaf_area_m2_kg;
#ifdef _Windows
       if (detail_txt_file) (*detail_txt_file) << "\t emerged: GAI=" << cotyledon_GAI << " BM=" << cotyledon_biomass;
#endif
      emerged = true;
   }
   else
   {  cotyledon_GAI = 0.0;
      cotyledon_biomass = 0.0;
   }
#ifdef _Windows
   if (detail_txt_file) (*detail_txt_file) << std::endl;
#endif
   days_after_sowing += 1;
}
//______________________________________________________________________________
float64  Crop_emergence_hydrothermal_time::get_cotyledon_GAI() const
{  return  cotyledon_GAI; }
//______________________________________________________________________________
float64  Crop_emergence_hydrothermal_time::get_cotyledon_biomass() const
{  return cotyledon_biomass; }
//______________________________________________________________________________
bool Crop_emergence_hydrothermal_time::is_first_day() const
{  return first_day; }
//______________________________________________________________________________
bool Crop_emergence_hydrothermal_time::is_complete() const
{  return at_anticipated_pot_emergence; }
//______________________________________________________________________________
bool Crop_emergence_hydrothermal_time::has_emerged() const
{  return emerged;}
//______________________________________________________________________________
#if (CROPSYST_VERSION >= 5)
} // namespace CropSyst
#endif

