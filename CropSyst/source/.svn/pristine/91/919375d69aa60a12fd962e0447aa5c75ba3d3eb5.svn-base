
#include "transpiration_dependent_growth_V5.h"
#include "corn/math/compare.hpp"
#ifndef moremathH
#  include "corn/math/moremath.h"
using namespace std;
#endif

namespace CropSyst
{
//______________________________________________________________________________
Biomass_production_transpiration_dependent_V5::Biomass_production_transpiration_dependent_V5
(Crop_parameters_struct::Biomass_production   &parameters_
,const Vapor_pressure_deficit_daytime  &daytime_vapor_pressure_deficit_
,const float64                         &pot_ref_evapotranspiration_
,const float64                         &CO2_TUE_adjustment_
)
: Biomass_production_transpiration_dependent_common(CO2_TUE_adjustment_)
, parameters                                       (parameters_)
{
#ifdef YAML_PARAM_VERSION
   switch (parameters.TUE_equation)
   {case TUE_Tanner_Sinclair     : TUE_equation = new TUE_Equation_Tanner_Sinclair
      (parameters_.reference_biomass_transpiration_coef_adjustable
      ,daytime_vapor_pressure_deficit_);
    break;
    case TUE_curve               : TUE_equation = new TUE_Equation_curve
      (parameters_.TUE_scaling_coef_adjustable
      ,parameters_.TUE_at_1kPa_VPD_adjustable
      ,daytime_vapor_pressure_deficit_);
    break;
    case TUE_water_productivity  : TUE_equation = new TUE_Equation_AquaCrop_water_productivity
      (parameters.water_productivity_adjustable
      ,pot_ref_evapotranspiration_);
      break;
   } // switch
#else
assert(false);
#endif
}
//______________________________________________________________________________
float64 Biomass_production_transpiration_dependent_V5::TUE_Equation_Tanner_Sinclair
:: calculate()                                                      calculation_
{  // The original
   float64 sane_daytime_vapor_pressure_deficit =
      CORN::must_be_greater_or_equal_to<float64>
         (curr_daytime_vapor_pressure_deficit.get_kPa()
         ,0.00001);
   float64  biomass_water_ratio_kPa =  param_biomass_water_ratio_Pa / 1000.0;
            // convert to kilo Pascal
         // pot_transpiration is actually kg water/m^2 ground
   return biomass_water_ratio_kPa/sane_daytime_vapor_pressure_deficit;
}
//_2015-09-05_2008-05-05 ______________TUE_Equation_Tanner_Sinclair::calculate_/
float64 Biomass_production_transpiration_dependent_V5::TUE_Equation_curve
:: calculate()                                                      calculation_
{
   // g biomass / kg water
   // Although TUE_at_1kPa_VPA is in g BM/kg water
   // transpiration is in 1000's kg
   // so mathmatically the units of the equation works out the same
   // No need to convert units of TUE_at_1kPa_VPA

   float64 sane_daytime_vapor_pressure_deficit =
      CORN::must_be_greater_or_equal_to<float64>
         (curr_daytime_vapor_pressure_deficit.get_kPa()
         ,0.00001);
   float64 scaling_factor = pow
      (sane_daytime_vapor_pressure_deficit
      ,(float64)(-param_TUE_scaling_coef));
   return g_to_kg(param_TUE_at_1kPa_VPA) * scaling_factor;
}
//_2015-09-05_2008-04-28_________________________TUE_Equation_curve::calculate_/
float64 Biomass_production_transpiration_dependent_V5::TUE_Equation_AquaCrop_water_productivity
:: calculate()                                                      calculation_
{
   float64 pot_ref_evapotranspiration_kg_m2 // kg/m2
         =pot_ref_evapotranspiration * 1000.0; // m to  kg/m²
   return g_to_kg(param_AquaCrop_water_productivity)
         / pot_ref_evapotranspiration_kg_m2;
}
//_2015-09-05_2008-04-28___TUE_Equation_AquaCrop_water_productivity::calculate_/
float64 Biomass_production_transpiration_dependent_V5::get_transpiration_use_efficiency_unadj() const
{ return TUE_equation->calculate(); }
//_2015-10-30___________________________________________________________________
/*
#else
#error Remove this file from your project, it is not yet fully implemented,
#error use instead transpiration_dependent_growth_V4.cpp
#endif
*/
} // namespace Cropsyst
