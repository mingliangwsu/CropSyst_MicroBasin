#include "crop_N_V4.h"
#include "crop/crop_cropsyst.h"
#include "common/biometeorology/parameter/slope_SVP_curve_psychrometric_resistance.h"
namespace CropSyst
{
//______________________________________________________________________________
//                                                                       // C3       C4      CAM (crassulacean acid metabolism)
#if (CROPSYST_VERSION == 4)
static const float64 N_max_conc_at_emergence_species              [3] = { 0.07   ,  0.055 ,  0.055 };
static const float64 scaling_factor_critical_N_conc_species       [3] = { 0.65   ,  0.65  ,  0.65  }; // to scale maximum to critical
static const float64 scaling_factor_min_N_conc_species_N_max_based[3] = { 0.45   ,  0.45  ,  0.45  }; // to scale maximum to minimum
// warning currently the CAM coefficients are the same as C4 these need to be checked
#endif
namespace deprecated // This NS is temporary to see if Crop_nitrogen_V4 is still used DELETE THIS NS
{

//______________________________________________________________________________
Crop_nitrogen_V4::Crop_nitrogen_V4
(CropSyst::Crop_parameters::Nitrogen &_parameters
,Crop_complete             &_crop                                                //020505
,Soil_interface            *_soil                                                //050721
,Soil_nitrogen_interface   *_chemicals                                           //050721
,const Slope_saturated_vapor_pressure_plus_psychrometric_resistance              //150601
      *slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference_   //150601
,const float64 &transpiration_use_efficiency_unused) // Not used in this version //151104
: Crop_nitrogen_common
   (_parameters,_crop,_soil,_chemicals
   ,slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference_)     //150601
,slope_saturated_vapor_pressure_plus_psychrometric_resistance_stressed(0)        //150601
,slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference
   (slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference_)     //180805
{
   if (slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference)    //150601
   slope_saturated_vapor_pressure_plus_psychrometric_resistance_stressed
      = new Slope_saturated_vapor_pressure_plus_psychrometric_resistance
      (*slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference);
}
//______________________________________________________________________________
Crop_nitrogen_V4::~Crop_nitrogen_V4()
{
   delete slope_saturated_vapor_pressure_plus_psychrometric_resistance_stressed; //150601
}
//______________________________________________________________________________
bool Crop_nitrogen_V4::initialize()                              initialization_ //150601
{  bool initialized = Crop_nitrogen_common::initialize();
   // Must call Crop_nitrogen_common::initialize() first
   //121219 deprecated in version 4.1.17
   if (crop.parameters->nitrogen.dilution_curve_based_on_max_conc)
   {  // This mode is really obsolete and should not be used anymore
      float64 biomass_to_start_dilution_max_N_conc = 0.0;
      float64 biomass_to_start_dilution_crit_N_conc = 0.0;
      biomass_to_start_dilution_max_N_conc   = parameters.biomass_to_start_dilution_max_N_conc_T_ha;                                //120505
      biomass_to_start_dilution_crit_N_conc  = parameters.calc_biomass_to_start_dilution_crit_N_conc_T_ha(photosynthetic_pathway);  //120505
      float64 scaling_factor_critical_N_conc = scaling_factor_critical_N_conc_species[photosynthetic_pathway];
      float64 scaling_factor_min_N_conc      = scaling_factor_min_N_conc_species_N_max_based[photosynthetic_pathway];      //121219
      N_min_conc_at_emergence                = N_max_conc_at_emergence * scaling_factor_min_N_conc;
      N_crit_conc_at_emergence               = N_max_conc_at_emergence * scaling_factor_critical_N_conc;
      float64 biomass_to_start_dilution_min_N_conc = parameters.calc_biomass_to_start_dilution_min_N_conc_T_ha (photosynthetic_pathway);  //120505
      /*160409
      Amax  = N_max_conc_at_emergence   / pow(biomass_to_start_dilution_max_N_conc,concentration_slope);
      Acrit = N_crit_conc_at_emergence  / pow(biomass_to_start_dilution_crit_N_conc,concentration_slope);
      Amin  = N_min_conc_at_emergence   / pow(biomass_to_start_dilution_min_N_conc,concentration_slope);
      */
   }
   return initialized;
}
//______________________________________________________________________________
bool Crop_nitrogen_V4::start_season()
{
   #if (CROPSYST_VERSION==4)
   start_change_today = false;                                                   //070129_121221(was start_flowering_today)
   #endif
   return Crop_nitrogen_common::start_season();
}
//______________________________________________________________________________
bool Crop_nitrogen_V4::start_day()
{
   bool started = Crop_nitrogen_common::start_day();
   { // setup for N_limited_pot_transpiration                                    //150601
   float64 canopy_resistance= crop.get_canopy_resistance();                      //040604
   float64 canopy_resistance_when_stomate_closed                                 //031203
   = 30.0 * canopy_resistance; // value when stomates are closed                 //031203
   float64 N_stress = stress_factor_stats.get_current();                              //040604
   float64 corrected_N_stress = is_approximately(N_stress,0.0, 0.000001)         //040714
   ? 0.01 //Need to provided something for div by zero, not sure what to use     //040714
   : N_stress;                                                                   //040714
   float64 N_stress_canopy_resistance =  0.3 * canopy_resistance                 //040714
         + 0.7 * canopy_resistance / corrected_N_stress;
   // Not affecting the whole canopy resistance during stress conditions.        //050317
   // 70% is subject to correction
   canopy_resistance_under_N_stress                                              //150601_031203
      = std::min<float64>(N_stress_canopy_resistance                             //031203
        , canopy_resistance_when_stomate_closed );                               //031203
   if (slope_saturated_vapor_pressure_plus_psychrometric_resistance_stressed)
       slope_saturated_vapor_pressure_plus_psychrometric_resistance_stressed->update();//150602
   }
   return started;
}
//_2015-10-29___________________________________________________________________
float64 Crop_nitrogen_V4::get_N_max_conc_at_emergence()                    const
{  float64 param_N_max_conc_emerge  = Crop_nitrogen_common::get_N_max_conc_at_emergence(); //151029
#if (CROPSYST_VERSION == 4)
//deprecated121219
   if (crop_parameters.nitrogen.dilution_curve_based_on_max_conc)
   {  param_N_max_conc_emerge = N_max_conc_at_emergence_species[crop_parameters.photosynthetic_pathway_labeled.get()];   //120427
      if (crop_parameters.nitrogen.demand_adjust < 1.0)                         //120427
         // only apply this correction when less than 1 (do not adjust up)
         param_N_max_conc_emerge *= crop_parameters.nitrogen.demand_adjust;     //120427
   }
#endif
  return param_N_max_conc_emerge;
}
//_2006-12-12______________________________________get_N_max_conc_at_emergence_/
float64 Crop_nitrogen_V4::update_limited_pot_transpiration()       modification_
{
   float64 normal_vapor_pressure_plus_resistance   = 1.0;
   float64 stressed_vapor_pressure_plus_resistance = 1.0;
   if (slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference)
   {  normal_vapor_pressure_plus_resistance   = slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference->get_kPa_per_C(); //150601
      stressed_vapor_pressure_plus_resistance = slope_saturated_vapor_pressure_plus_psychrometric_resistance_stressed->get_kPa_per_C(); //150601
   }
   float64 transp_correction_factor
      =   normal_vapor_pressure_plus_resistance
     / stressed_vapor_pressure_plus_resistance;
   float64 N_limited_transp = crop.pot_transpiration_m[1 /*CO2adj*/] * transp_correction_factor; //151031
   return N_limited_transp;
}
//_2001-11-17_________________________________get_N_limited_pot_transpiration__/
#if (CROPSYST_VERSION==4)
   // 130408 obsolete in because now change is iniciated by new end_dilution_curve parameter
void Crop_nitrogen_V4::know_start_flowering()                      modification_
{  if (parameters.dilution_curve_based_on_max_conc)                              //130406
   {  before_change = false;                                                     //130406
      start_change_today = true;                                                 //121221
   }
}
#endif
//_2007-01-26____________________________________________know_start_flowering__/
float64 Crop_nitrogen_V4::calc_limited_growth
(float64 attainable_growth_transp_or_RUE
,float64 act_to_pot_transpiration_ratio                                          //020719
,float64 root_activity_factor)                                     modification_ //080728
{
   float64 N_limited_growth = update_limited_growth                              //151030
      (attainable_growth_transp_or_RUE
      ,root_activity_factor);
   stress_factor = 1.0;                                                          //020719
   if (!(automatic_nitrogen_to_plant                                             //160329_020719
         || CORN::is_approximately<float64>(crop.get_attainable_top_growth(),0.0,0.000001)))
   {  if (CORN::is_approximately<float64>  (act_to_pot_transpiration_ratio,1.0,0.0001))          //020719
         stress_factor = N_limited_growth / crop.get_attainable_top_growth();    //020719
      else
         stress_factor = (attainable_growth_transp_or_RUE == 0.0)                //020719
         ? 1.0                                                                   //020719
         : N_limited_growth / attainable_growth_transp_or_RUE;                   //020719
   }
   stress_factor_stats.append(stress_factor);                                    //020719
   return N_limited_growth;                                                      //011016
}
//_2001-10-22_____________________________________________calc_limited_growth__/
}
} // namespace deprecated // This NS is temporary to see if Crop_nitrogen_V4 is still used DELETE THIS NS


// namespace CropSyst

