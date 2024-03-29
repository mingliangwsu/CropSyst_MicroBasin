#include "crop/transpiration_dependent_growth_V4.h"
#include <math.h>
#ifndef moremathH
#  include "corn/math/moremath.h"
using namespace std;
#endif
#include "corn/math/compare.hpp"
#include "corn/measure/measures.h"

namespace CropSyst {
//______________________________________________________________________________
Biomass_production_transpiration_dependent_V4
::Biomass_production_transpiration_dependent_V4
(const Crop_parameters                 &parameters_
,const Vapor_pressure_deficit_daytime  &daytime_vapor_pressure_deficit_
,const float64                         &pot_ref_evapotranspiration_
,const float64                         &CO2_TUE_adjustment_
,const nat8                            &season_                                  //180111
,const bool                            &before_WUE_change_                       //180111
)
: Biomass_production_transpiration_dependent_common        (CO2_TUE_adjustment_)
, parameters                                                       (parameters_)
, daytime_vapor_pressure_deficit               (daytime_vapor_pressure_deficit_)
, pot_ref_evapotranspiration                       (pot_ref_evapotranspiration_)
, season                                                               (season_) //180111
, before_WUE_change                                         (before_WUE_change_) //180111
{}
//______________________________________________________________________________
float64 Biomass_production_transpiration_dependent_V4::get_transpiration_use_efficiency_unadj() const
{  float64 sane_daytime_vapor_pressure_deficit =
      CORN::must_be_greater_or_equal_to<float64>
         (daytime_vapor_pressure_deficit.get_kPa(),0.00001);
   float64 transpiration_use_efficiency = 0.0;                                         //080505
   switch (parameters.biomass_production.TUE_equation)                                 //080505
   {case TUE_Tanner_Sinclair :
   {  // The original                                                                  //080428
      float64  biomass_water_ratio_Pa = get_biomass_water_ratio(before_WUE_change);
            // Input in Pascal (or Pa kg biomass/kg water)
      float64  biomass_water_ratio_kPa =  biomass_water_ratio_Pa / 1000;               //080505
            // convert to kilo Pascal
         // pot_transpiration is actually kg water/m^2 ground                          //080505
      transpiration_use_efficiency  // kg biomass / kg H2O                             //080505
         = biomass_water_ratio_kPa/sane_daytime_vapor_pressure_deficit;                             //080505
      // vapor_pressure_deficit is in kPa                                              //080505
   } break;
   case TUE_curve :                                                                    //080505
   {  float64 scaling_coef =  get_TUE_scaling_coef(before_WUE_change);                 //080428
         /// unitless   b parameter is a scaling coef.
      float64 TUE_at_1kPa_VPA = get_TUE_at_1kPa_VPD(before_WUE_change);                //080428
            // g biomass / kg water
            // Although TUE_at_1kPa_VPA is in g BM/kg water                            //080429
            // transpiration is in 1000's kg                                           //080429
            // so mathmatically the units of the equation works out the same           //080429
            // No need to convert units of TUE_at_1kPa_VPA                             //080429
      float64 scaling_factor =  pow(sane_daytime_vapor_pressure_deficit,-scaling_coef);//080505
      transpiration_use_efficiency // kg biomass / kg H2O                              //080428
         = g_to_kg(TUE_at_1kPa_VPA) * scaling_factor;                                  //080428
      //printf("TUE_at_1kPa_VPA:%f\tVPD:%f\tscaling_coef:%f\tscaling_factor:%f \n",TUE_at_1kPa_VPA,sane_daytime_vapor_pressure_deficit, scaling_coef, scaling_factor);
      //std::clog << "\tTUE_at_1kPa_VPA:" << TUE_at_1kPa_VPA
      //          << "\tVPD:" << sane_daytime_vapor_pressure_deficit
      //          << "\tscaling_factor:" << scaling_factor
      //          << std::endl;
   } break;
   case TUE_water_productivity :                                                       //080505
   {  float64 AquaCrop_water_productivity = get_water_productivity(before_WUE_change); //080428
         // g/m�    // Warning need to get this by season as in get_TUE_at_1kPa_VPD
            // Although TUE_at_1kPa_VPA is in g BM/kg water                            //080429
            // transpiration is in 1000's kg                                           //080429
            // so mathmatically the units of the equation works out the same           //080429
            // No need to convert units of TUE_at_1kPa_VPA                             //080429
      float64 pot_ref_evapotranspiration_kg_m2 // kg/m2                                //080505
         =pot_ref_evapotranspiration /*_local*/  * 1000.0; // m to  kg/m�              //080505
      transpiration_use_efficiency = g_to_kg(AquaCrop_water_productivity)              //080505
         / pot_ref_evapotranspiration_kg_m2;
   } break;
   } // switch
   return transpiration_use_efficiency; // unadjusted (no CO2 effect);
}
//_2015-10-29_____________________________________________________________________________
// 151101 caller may be able to just get the parameter directly
float64 Biomass_production_transpiration_dependent_V4::get_biomass_water_ratio(bool before_WUE_change) const
{  float64 reference_biomass_water_ratio =                                       //981204
        parameters.param_reference_biomass_transpiration_coef(before_WUE_change);//040729
   return reference_biomass_water_ratio;
}
//_1998-02-20___________________________________________________________________
float64 Biomass_production_transpiration_dependent_V4::get_TUE_at_1kPa_VPD(bool before_WUE_change) const
{  float64 TUE_at_1kPa = parameters.param_TUE_at_1kPa_VPD(before_WUE_change );
   return TUE_at_1kPa;
}
//_2008-04-28___________________________________________________________________
float64 Biomass_production_transpiration_dependent_V4::get_water_productivity(bool before_WUE_change) const
{  float64 water_productivity = parameters.param_water_productivity (before_WUE_change);// NYI we may want this by season
   return water_productivity ;
}
//_2008-04-28___________________________________________________________________
float64 Biomass_production_transpiration_dependent_V4::get_TUE_scaling_coef(bool before_WUE_change) const
{  float64 TUE_scaling_coef = parameters.param_TUE_scaling_coef (before_WUE_change);
   return TUE_scaling_coef ;
}
//_2009-12-01___________________________________________________________________
/*180111 obsolete because now using references
void Biomass_production_transpiration_dependent_V4::know_daily_parameters
(int16   season_
,bool    before_WUE_change_)
{  season                     = season_;
   before_WUE_change          = before_WUE_change_;
}
//_2013-06-27___________________________________________________________________
*/
} // namespace CropSyst

