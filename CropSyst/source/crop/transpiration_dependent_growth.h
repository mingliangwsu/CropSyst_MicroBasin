#ifndef transpiration_dependent_growthH
#define transpiration_dependent_growthH

#include "corn/primitive.h"
#include "cmmnopts.h"
#include "crop/crop_param.h"
#include "common/weather/parameter/WP_vapor_pressure_deficit.h"
namespace CropSyst {
//______________________________________________________________________________
class Biomass_production_transpiration_dependent_common
{
   mutable float64 TUE_CO2_adjusted;
   const float64 &CO2_TUE_adjustment;
 public:
   Biomass_production_transpiration_dependent_common
      (const float64 &CO2_TUE_adjustment_);
   float64 calc_potential_biomass_production
      (float64 pot_transpiration_m_CO2_adjusted)                           const;
   inline const float64 &ref_transpiration_use_efficiency_CO2_adjusted()   const
      { return TUE_CO2_adjusted; }
      // The crop nitrogen model needs this;
 protected:
   virtual float64 get_transpiration_use_efficiency_unadj()                const = 0;
};
//_2008-07-21___________________________________________________________________
}
#endif

