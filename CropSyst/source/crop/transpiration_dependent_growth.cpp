
#include "crop/transpiration_dependent_growth.h"
#include <math.h>
#ifndef moremathH
#  include "corn/math/moremath.h"
using namespace std;
#endif
#include "corn/measure/measures.h"
namespace CropSyst {
//______________________________________________________________________________
Biomass_production_transpiration_dependent_common
::Biomass_production_transpiration_dependent_common
(const float64 &CO2_TUE_adjustment_)
: CO2_TUE_adjustment(CO2_TUE_adjustment_)
, TUE_CO2_adjusted(1.0)
{}
//______________________________________________________________________________
float64 Biomass_production_transpiration_dependent_common
::calc_potential_biomass_production
(float64 pot_transpiration_m_CO2_adj)                                      const
{
   float64 pot_transpiration_CO2_adjusted_kg_m2 = pot_transpiration_m_CO2_adj * 1000.0;
   float64 TUE = get_transpiration_use_efficiency_unadj();
   TUE_CO2_adjusted = TUE * CO2_TUE_adjustment;
      // CO2_TUE_adjustment will be 1 when no CO2 model
   float64 pot_transpiration_dependent_growth // kg/m²
      = pot_transpiration_CO2_adjusted_kg_m2
      * TUE_CO2_adjusted;
   if (pot_transpiration_dependent_growth <= 0.0) // avoid div 0:                //981207
       pot_transpiration_dependent_growth = 0.00001;
   return pot_transpiration_dependent_growth;                                    //080722
}
//_2008-07-21___________________________________________________________________
} // namespace CropSyst

