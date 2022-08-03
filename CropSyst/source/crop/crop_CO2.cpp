#if (CO2_RESPONSE_VERSION==4)
131209 obsolete

//131205 This is now permanently obsolete

/* I think this was the model based on

Michaelis Menten_kinetics
http://en.wikipedia.org/wiki/Michaelis%E2%80%93Menten_kinetics

*/
#ifdef USE_PCH
#  include "simulation/CropSyst_sim_pch.h"
#else
#include "crop/crop_CO2.h"
#include <common/biometeorology/ET_reference_FAO.h>
#endif

#if (CROPSYST_VERSION != 4)
#error Only include this in version 4
#endif

#if (CROPSYST_VERSION >= 5)
namespace CropSyst {
#endif
//______________________________________________________________________________
Crop_CO2_response::Crop_CO2_response
(const Crop_parameters_struct::CO2_Response &_parameters
,float64                         current_CO2_conc
,float64                         reference_light_to_biomass
)
: parameters(_parameters)
, CO2_adj_canopy_resistance(0.0)          // initialized here
{  update(current_CO2_conc);                                                     //081113
}
//_2002-04-09___________________________________Crop_CO2_response::constructor_/
void Crop_CO2_response::update(float64 current_CO2_conc)
{     // Since we use the following parameters several times get a local copy.
   float64 baseline_reference_CO2_conc = parameters.baseline_reference_conc;
   float64 elevated_reference_CO2_conc = parameters.elevated_reference_conc;
   float64 growth_ratio_elevated_to_baseline_conc_CO2 = parameters.growth_ratio_elevated_to_baseline_conc;
   float64 final_term = - growth_ratio_elevated_to_baseline_conc_CO2             //980224
         * (baseline_reference_CO2_conc - elevated_reference_CO2_conc)           //000811
          / (elevated_reference_CO2_conc                                         //970219
              - baseline_reference_CO2_conc * growth_ratio_elevated_to_baseline_conc_CO2); //000811
   float64 slope = - final_term /( baseline_reference_CO2_conc * (1.0 - final_term));  //000811
   actual_biomass_gain_ratio_in_response_to_CO2                                  //110913
     =     (slope * current_CO2_conc * final_term)                               //010202
         / (slope * current_CO2_conc + final_term);                              //010202
   static const float64 sensitivity_factor = 0.001212;
   float64 adj_factor = 1.0 / ( 1.0 - (current_CO2_conc - baseline_reference_CO2_conc) * sensitivity_factor);  //081118
   CO2_adj_canopy_resistance =  canopy_resistance_constant * adj_factor;         //081118
}
//_2008-11-13___________________________________________________________update_/
#if (CROPSYST_VERSION >= 5)
} // namespace CropSyst
#endif

#endif
