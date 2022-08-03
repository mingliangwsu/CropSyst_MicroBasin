
#include "canopy_cover_curve.h"
#include <math.h>
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#ifndef moremathH
#  include "corn/math/moremath.h"
   // using namespace std;
#endif

namespace CropSyst
{
//______________________________________________________________________________
bool Canopy_cover_curve_common::parameterize
(float64 cover_maximum_CO2_adj_
,float64 cover_initial_)                                          initialization_
{
   cover_maximum_CO2_adj = cover_maximum_CO2_adj_;
   cover_initial = cover_initial_;
   return true;
}
//______________________________________________________________________________
/*180601 obsolete but dont delete until 2020
bool Canopy_cover_curve_2013::parameterize
(float64 cover_maximum_CO2_adj_
,float64 cover_initial_)                                          initialization_
{  bool paramed = Canopy_cover_curve_common::parameterize                        //171220
      (cover_maximum_CO2_adj_,cover_initial_);
   if (cover_maximum_CO2_adj <= 0.000001) return true;                           //130821
   if (cover_initial < 0.0000001) cover_initial = 0.00001;                       //130610

   { // DetermineCanopyGrowthParameters
      float64 new_asym_CC = cover_maximum_CO2_adj;
         do
         {  asym_CC = new_asym_CC;
            shape_factor = -log(1.0 / (asym_CC / cover_initial - 1.0))           //110628
                 / fract_season_to_reach_half_max_cover;
            b_Coefficient = 1.0
               / exp(-shape_factor * fract_season_to_reach_half_max_cover);
            new_asym_CC = -(cover_initial                                        //110628
               - (1.0 + b_Coefficient) * cover_maximum_CO2_adj) / b_Coefficient;
         } while (fabs(new_asym_CC - asym_CC) > 0.0001);
         actual_CC_max = asym_CC / (1.0 + b_Coefficient * exp(-shape_factor));
   }
   return paramed;
}
//_2013-06-11_____________________________________________________parameterize_/
bool Canopy_cover_curve_2013::start_senescence()
{
   in_senescence = true;
   {  // determine senescence parameters
      float64 check;
      float64 new_C_low = 0.0;
      float64 cover_at_max_canopy = cover_latest_vegetative;                     //171221
      do
      {  C_low = new_C_low;
         asym_CC_senescence
          = -(C_low - cover_at_max_canopy * (1.0 + b_Coefficient)) / b_Coefficient;
         new_C_low = asym_CC_senescence-(1.0+b_Coefficient*exp(-shape_factor))
             * (asym_CC_senescence - canopy_cover_season_end);                   //171009_110628
            // originally was mature_total_cover, then changed to 0 (110628)

//         new_C_low = CORN::must_be_between<float64>(new_C_low,0.00000001,1.0);

         check = fabs(new_C_low - C_low);
      } while (check > 0.0001);
   }
   return true;
}
*/
//_2014-11-24___________________________________________________________________
float64 Canopy_cover_curve_common
::calculate(float64 _cumulative_thermal_time)                       calculation_
{  cumulative_thermal_time = _cumulative_thermal_time;                           //130703
   return
      (cumulative_thermal_time >= thermal_time_start_season)
      ?  ( cumulative_thermal_time <= thermal_time_end_vegetative_growth)
         ?  calc_during_cresence()                                               //141123
         :  in_senescence
            ? calc_during_senescence()
            : calc_during_culminescence()
      : 0.0;
}
//_2013-06-11________________________________________________________calculate_/
/*180601 obsolete but dont delete until 2020
float64 Canopy_cover_curve_2013::calc_during_cresence()                    const //141123
{  float64 relative_thermal_time
         = (cumulative_thermal_time - thermal_time_start_season)
            / (thermal_time_end_vegetative_growth - thermal_time_start_season);
   float64 calculated_cover
      = asym_CC
        / (1.0 + b_Coefficient * exp(-shape_factor * relative_thermal_time));
   return calculated_cover;
}
//_2013-06-11____________________________________calc_during_vegetative_growth_/
float64 Canopy_cover_curve_2013::calc_during_culminescence()               const
{  return cover_latest_vegetative;                                               //171221
}
//_2013-06-11___________________________________________calc_during_quiescence_/
float64 Canopy_cover_curve_2013::calc_during_senescence()                  const
{  float64 calculated_cover = 0.0;
   float64 thermal_time_season_end_corrected                                     //171123
      = (thermal_time_season_end == thermal_time_beginning_senescence)           //171123
      ? thermal_time_season_end + 1.0 //avoid div 0                              //171123
      : thermal_time_season_end;                                                 //171123
   float64 relative_thermal_time =
        (cumulative_thermal_time - thermal_time_beginning_senescence)
      / (  thermal_time_season_end_corrected
         - thermal_time_beginning_senescence);
   calculated_cover = asym_CC_senescence - (asym_CC_senescence - C_low)
      / (1.0 + b_Coefficient * exp(-shape_factor * relative_thermal_time));
   calculated_cover =CORN::must_be_greater_or_equal_to<float64>
      (calculated_cover,canopy_cover_season_end );
   return calculated_cover;
}
//______________________________________________________calc_during_senescence_/
Canopy_cover_curve_2013::Canopy_cover_curve_2013
(float64 thermal_time_end_vegetative_growth_
,float64 thermal_time_beginning_senescence_
,float64 thermal_time_start_season_
,float64 thermal_time_season_end_                                                //171009
,float64 canopy_cover_season_end_                                                //171009
,float64 fract_season_to_reach_half_max_cover_
,const float64 &cover_latest_vegetative_
)
:Canopy_cover_curve_common                                                       //171220
   (thermal_time_end_vegetative_growth_
   ,thermal_time_beginning_senescence_
   ,thermal_time_start_season_
   ,thermal_time_season_end_
   ,canopy_cover_season_end_)
,fract_season_to_reach_half_max_cover  (fract_season_to_reach_half_max_cover_)
, b_Coefficient         (0.0)                                                    //141125
, asym_CC               (0.0)                                                    //141125
, asym_CC_senescence    (0.0)                                                    //141124
, shape_factor          (0.0)                                                    //141125
, C_low                 (0.0)                                                    //141124
, actual_CC_max         (0.0)                                                    //141125
, cover_latest_vegetative(cover_latest_vegetative_)                              //171221
{}
//______________________________________________________________________________
*/
Canopy_cover_curve_common::Canopy_cover_curve_common
(float64 thermal_time_end_vegetative_growth_
,float64 thermal_time_beginning_senescence_
,float64 thermal_time_start_season_
,const float32 &/*180713 float64 */ thermal_time_season_end_
,const float32 &/*180713 float64 */ canopy_cover_season_end_
)
:cumulative_thermal_time               (0)
,thermal_time_end_vegetative_growth    (thermal_time_end_vegetative_growth_)
,thermal_time_beginning_senescence     (thermal_time_beginning_senescence_)
,thermal_time_start_season             (thermal_time_start_season_)
,thermal_time_season_end               (thermal_time_season_end_)
,canopy_cover_season_end               (canopy_cover_season_end_)
,cover_maximum_CO2_adj                 (0)
,cover_initial                         (0)
, in_senescence                        (false)
{}
//_2017-12-20___________________________Canopy_cover_curve_common_|constructor_/
Canopy_cover_curve_2017::Canopy_cover_curve_2017
   (float64 thermal_time_end_vegetative_growth_
   ,float64 thermal_time_beginning_senescence_
   ,float64 thermal_time_start_season_
   ,const float32 &/*180713 float64 */ thermal_time_season_end_
   ,const float32 &/*180713 float64 */ canopy_cover_season_end_
   ,float64 shape_coef_accrescent_
   ,float64 shape_coef_senescent_)
: Canopy_cover_curve_common
   (thermal_time_end_vegetative_growth_
   ,thermal_time_beginning_senescence_
   ,thermal_time_start_season_
   ,thermal_time_season_end_
   ,canopy_cover_season_end_)
, cover_current         (0)
, B1                    (0)
, B2                    (0)
, shape_coef_vegetative (shape_coef_accrescent_) //(9.0)  // may need to be in UI
, shape_coef_senescent  (shape_coef_senescent_) // (9.0)  // may need to be in UI
, CCmax2_actual         (0)
, CCmax_asymptotic      (0)
, CCend_asymptotic      (0)
{}
//_2017-12-20_____________________________Canopy_cover_curve_2017_|constructor_/
bool Canopy_cover_curve_2017::parameterize
(float64 cover_maximum_CO2_adj_
,float64 cover_initial_)                                         initialization_
{  bool paramed = Canopy_cover_curve_common::parameterize
      (cover_maximum_CO2_adj_,cover_initial_);
   static const float64 thermal_time_fractional_at_half_cover_max         = 0.5;
   static const float64 thermal_time_fractional_at_half_cover_senescence  = 0.5;
   B1 = 1.0 / exp(-shape_coef_vegetative * thermal_time_fractional_at_half_cover_max);
   B2 = 1.0 / exp(-shape_coef_senescent * thermal_time_fractional_at_half_cover_senescence);
   CCmax_asymptotic = (cover_maximum_CO2_adj_ - cover_initial_)
      * (1.0 + B1 * exp(-shape_coef_vegetative * 1.0)) + cover_initial_;

//   cover_yesterday=cover_initial_;                                               //171221
//   cover_cum      =cover_initial_;                                               //171221

   return paramed;
      // Not currently needed because shape parameters
      // are calculated ?daily?
}
//_2017-12-20____________________________Canopy_cover_curve_2017::parameterize_/
float64 Canopy_cover_curve_2017::calc_during_cresence()                    const //141123
{
   // The VB version was this Relative_TT_Vegetative = CTT / CTT_End_Canopy_Growth
   // but I think in needs to be:
   /*
   float64 relative_thermal_time
         = (cumulative_thermal_time - thermal_time_start_season)
            / (thermal_time_end_vegetative_growth - thermal_time_start_season);
   */
   float64 relative_thermal_time
      =  cumulative_thermal_time
       / thermal_time_end_vegetative_growth;
   float64 calculated_cover
       = cover_initial + (CCmax_asymptotic - cover_initial)
       / (1.0 + B1 * exp(-shape_coef_vegetative * relative_thermal_time));
   cover_current = calculated_cover;
   return calculated_cover;
}
//_2017-12-20_____________________________________________calc_during_cresence_/
float64 Canopy_cover_curve_2017::calc_during_culminescence()               const
{  return cover_current;
}
//_2017-12-20________________________________________calc_during_culminescence_/
bool Canopy_cover_curve_2017::start_senescence()                   modification_
{
   in_senescence = true;
   float64 CCmax1_actual
      = cover_initial
       +  (CCmax_asymptotic - cover_initial)
        / (1.0 + B1 * exp(-shape_coef_vegetative));
   CCmax2_actual
      = (CCmax1_actual * (1.0 + B2) - canopy_cover_season_end) / B2;
   CCend_asymptotic
      =   CCmax2_actual
        + (canopy_cover_season_end - CCmax2_actual)
         *(1.0 + B2 * exp(-shape_coef_senescent));
   return true;
}
//_2017-12-20_________________________________________________start_senescence_/
float64 Canopy_cover_curve_2017::calc_during_senescence()                  const
{
   float64 relative_thermal_time
      =  (cumulative_thermal_time - thermal_time_beginning_senescence)
       / (thermal_time_season_end - thermal_time_beginning_senescence);
   float64 calculated_cover
      = CCmax2_actual
       - (CCmax2_actual - CCend_asymptotic)
        /(1.0 + B2 * exp(-shape_coef_senescent * relative_thermal_time));
   if (calculated_cover < canopy_cover_season_end )
      calculated_cover = canopy_cover_season_end;
   if (calculated_cover > CCmax2_actual )
      calculated_cover = CCmax2_actual;
   return calculated_cover;
}
//_2017-12-20___________________________________________calc_during_senescence_/
} // namespace CropSyst

