#include "CO2_response.h"
#include "crop_param_struct.h"
#include "weather/parameter/WP_vapor_pressure_saturation_slope.h"
#include "weather/parameter/WP_psychrometric_const.h"
#include "weather/atmospheric_CO2_change.h"
#include <math.h>
#include "corn/math/moremath.h"
#include "canopy_cover_continuum.h"
#include "corn/math/compare.hpp"
namespace CropSyst
{
   static const float64 CO2_conc_at_saturated_photosynthesis = 1100.0;           //Atmospheric CO2 Concentration at Saturated Photosynthesis

//_____________________________________________________________________________/
Crop_CO2_response::Crop_CO2_response
(const Crop_parameters_struct::CO2_Response &_CO2_response_parameters
,const Vapor_pressure_saturation_slope      &_vapor_pressure_saturation_slope    //140507
,const Psychrometric_constant               &_psychrometric_constant             //140508
,const float64                              &_aerodynamic_resistance_ref_plants  //140508
,const CS::CO2_atmospheric_concentration    &_ref_atmospheric_CO2_conc)          //150507
: CO2_response_parameters        (_CO2_response_parameters)
, canopy_conductance_at_FAO_CO2_359                               (0.0)
, canopy_conductance_at_saturation_CO2                            (0.0)
, growth_at_CO2_when_TUE_was_determined_relative_to_baseline_CO2  (0.0)
, growth_at_CO2_when_RUE_was_determined_relative_to_baseline_CO2  (0.0)
, actual_biomass_gain_ratio_in_response_to_CO2_TUE                (1.0)
, atmospheric_CO2_conc_ppm_yesterday                              (360)          //150311
   //initial value is not significant
, actual_biomass_gain_ratio_in_response_to_CO2_RUE                (1.0)
, TUE_adjustment                                                  (1.0)          //160314
, transpiration_adjustment_factor                                 (1.0)          //160314
, vapor_pressure_saturation_slope      (_vapor_pressure_saturation_slope)        //140507
, psychrometric_constant               (_psychrometric_constant)                 //140508
, aerodynamic_resistance_ref_plants    (_aerodynamic_resistance_ref_plants)      //140508
, ref_atmospheric_CO2_conc             (_ref_atmospheric_CO2_conc)               //140508
, FAO56_canopy_resistance              (0.00081) // actually constant
, CO2_adjusted_FAO56_canopy_resistance (0.00081) // will be adjusted in initialize
{ initialize();
}
//_____________________________________________________________________________/
float64 Crop_CO2_response::calc_canopy_conductance_at(float64 CO2_conc)    const
{  // Allen (1990) Canopy Conductance equation
   return
        0.0485
      - 0.00007 * CO2_conc
      + 0.000000034 * CORN_sqr(CO2_conc);                                       //151028
   //on 131205 it was 0.000000034
}
//_____________________________________________________________________________/
bool Crop_CO2_response::initialize()
{  // This is done only one time.
   // It is not dependent on current CO2

   // Determine the ratio of change between the base line and elevated CO2
   // parameters.

   //'Determine canopy resistance adjusted for CO2
   //151028 unused static const float64 CO2_concentration_FAO56_330 = 330.0;

   static const float64 CO2_conc_1998           = 359.0; // ppm                  //131205
   canopy_conductance_at_FAO_CO2_359  = calc_canopy_conductance_at(CO2_conc_1998);                                            //131205
   canopy_conductance_at_saturation_CO2 = calc_canopy_conductance_at(CO2_conc_at_saturated_photosynthesis); //151028

   float64 alpha            = CO2_response_parameters.non_rectagular_hyperbola_solution.alpha;
   float64 theta            = CO2_response_parameters.non_rectagular_hyperbola_solution.theta;
   float64 growth_ratio_max = CO2_response_parameters.non_rectagular_hyperbola_solution.growth_ratio_asymptotic;
   float64 at_specified_CO2_conc_RUE = CO2_response_parameters.CO2_concentration_when_measured.RUE;
   float64 at_specified_CO2_conc_TUE = CO2_response_parameters.CO2_concentration_when_measured.TUE;

/*
//These are only for comparing with the original spreadsheet model:
alpha = 0.004263626;
theta = 0.788391267;
growth_ratio_max = 1.758135293;
at_specified_CO2_conc_RUE =330;
at_specified_CO2_conc_TUE =330;
*/
   growth_at_CO2_when_TUE_was_determined_relative_to_baseline_CO2 //Growth at CO2 when TUE and RUE were determined relative to baseline CO2
      = (alpha * at_specified_CO2_conc_TUE
         + growth_ratio_max
         - sqrt
            (CORN_sqr(alpha * at_specified_CO2_conc_TUE + growth_ratio_max)
             - 4.0 *theta*alpha * at_specified_CO2_conc_TUE *growth_ratio_max))
            /(2.0*theta);
   growth_at_CO2_when_RUE_was_determined_relative_to_baseline_CO2
      = (alpha * at_specified_CO2_conc_RUE
         + growth_ratio_max
         - sqrt
            (CORN_sqr(alpha * at_specified_CO2_conc_RUE + growth_ratio_max)
             - 4.0 *theta*alpha * at_specified_CO2_conc_RUE *growth_ratio_max))
            /(2.0*theta);
   return true;
}
//_2011-06-28__________________________________________________________________/
void Crop_CO2_response::update_with_new_atmphospheric_CO2()       rectification_
{  // Currently this is called when the crop canopy is instanciated
   // It could be called more frequently if daily CO2 levels were to fluctuate
   // significantly during the year.
   // This would likely only be significant in controlled (greenhouse)
   //    environments
   float64 curr_CO2_conc = ref_atmospheric_CO2_conc.ppm();                       //150507_140508
   float64 alpha            = CO2_response_parameters.non_rectagular_hyperbola_solution.alpha;
   float64 theta            = CO2_response_parameters.non_rectagular_hyperbola_solution.theta;
   float64 growth_ratio_asymptotic = CO2_response_parameters.non_rectagular_hyperbola_solution.growth_ratio_asymptotic;
   float64 plus =  CORN_sqr(alpha*curr_CO2_conc+growth_ratio_asymptotic);
   float64 minus = 4.0 * theta *alpha * curr_CO2_conc *growth_ratio_asymptotic;
   float64 sqrt_term = sqrt(plus - minus);
   float64 growth_relative_to_baseline                                           //131205
   = (alpha * curr_CO2_conc
      + growth_ratio_asymptotic
      - sqrt_term )
    /(2.0 * theta);
   float64 canopy_conductance_at_curr =calc_canopy_conductance_at(curr_CO2_conc);//151028
   canopy_cond_adj_relative_to_FAO56  //Can. Cond. Adj. Relative to FAO 56 (C)
      = ((curr_CO2_conc >= CO2_conc_at_saturated_photosynthesis)                 //151028
         ? canopy_conductance_at_saturation_CO2
         : canopy_conductance_at_curr)                                           //151028
        / canopy_conductance_at_FAO_CO2_359;                                     //151028
   actual_biomass_gain_ratio_in_response_to_CO2_TUE
         =  growth_relative_to_baseline
          / growth_at_CO2_when_TUE_was_determined_relative_to_baseline_CO2;
   actual_biomass_gain_ratio_in_response_to_CO2_RUE
         =  growth_relative_to_baseline
          / growth_at_CO2_when_RUE_was_determined_relative_to_baseline_CO2;
}
//_2013-12-09__________________________________________________________________/
void Crop_CO2_response::update()                                  rectification_
{  // This is done daily because aerodynamic resistance changes daily.
   if (ref_atmospheric_CO2_conc.ppm() != atmospheric_CO2_conc_ppm_yesterday)     //150311
      update_with_new_atmphospheric_CO2();                                       //150311

   CO2_adjusted_FAO56_canopy_resistance  // (day/m)
         = FAO56_canopy_resistance / canopy_cond_adj_relative_to_FAO56;
   float64 gamma = psychrometric_constant.get_kPa_per_C();                       //150531_140508
   float64 delta = vapor_pressure_saturation_slope.get_kPa_per_C();              //150531_140507
   float64 ra    = aerodynamic_resistance_ref_plants;                            //140508
/*
//These are only for comparing with the original spreadsheet model:
gamma = 0.063;
delta = 0.2;
ra = 0.001;
*/
   // Determine transpiration reduction due to CO2-induced increased canopy resistance
   transpiration_adjustment_factor =
             (delta + gamma * (FAO56_canopy_resistance              + ra) / ra)
           / (delta + gamma * (CO2_adjusted_FAO56_canopy_resistance + ra) / ra);
   TUE_adjustment = actual_biomass_gain_ratio_in_response_to_CO2_TUE
      / transpiration_adjustment_factor;
   atmospheric_CO2_conc_ppm_yesterday = ref_atmospheric_CO2_conc.ppm();          //150507
      // This would go in end_day() method.
}
//_____________________________________________________________________________/
} // namespace namespace CropSyst

