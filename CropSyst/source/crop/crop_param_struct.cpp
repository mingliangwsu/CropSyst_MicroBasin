#include "crop_param_struct.h"
#include "corn/math/compare.hpp"
#include <math.h>
namespace CropSyst {

// These became deprecated in version 4.17.00
#if (CROPSYST_VERSION == 4)
const float biomass_to_start_dilution_max_N_conc_default [] = { 1.5    ,  1.0   ,  1.0   }; // T/ha  make this a parameter  Biomass to start dilution
const float biomass_to_start_dilution_max_to_crit_mult   [] = { 0.6666666,  0.75  ,  0.75  };
const float biomass_to_start_dilution_max_to_min_mult    [] = { 0.3333333,  0.5   ,  0.5   };
#endif
const float biomass_to_start_dilution_crit_N_conc_default[] = { 1.5   ,  0.75  ,  0.75  };     // T/ha  make this a parameter  Biomass to start dilution

// Now these multipliers are the same for all species
const float biomass_to_start_dilution_crit_to_max_mult   [] = { 1.0   ,  1.0   ,  1.0   };
const float biomass_to_start_dilution_crit_to_min_mult   [] = { 0.33333333,  0.333333333, 0.33333333  };

const float N_mature_max_conc_default     []= { 0.0235   ,  0.018 ,  0.018 };
const float N_mature_max_to_crit_mult     []= {0.64680851,  0.65  ,  0.65 };
const float N_mature_max_to_min_mult      []= {0.27659574,  0.2777777,0.2777777};

const float N_dilution_curve_slope_default[]= {0.45   , 0.38  , 0.38  };         //121219
   // N_conc_slope these are now entered as positive values but the equation uses them as negative
}
namespace CropSyst {
//______________________________________________________________________________
Crop_parameters_struct::Canopy_growth_cover_based::Canopy_growth_cover_based()
: cover_maximum_CO2_adj(0.9)
{}
//_2014-02-05__________________________________________________________________/
bool Crop_parameters_struct::Canopy_growth_cover_based::initialize
(float64 actual_biomass_gain_ratio_in_response_to_CO2)           initialization_
{
   if (CORN::is_approximately<float64>(actual_biomass_gain_ratio_in_response_to_CO2,1.0,0.00000001)) //131206
      cover_maximum_CO2_adj =  cover_maximum_no_CO2_adj;
   else
   {
      // adjustment of CO2_adj_maximum_cover is not needed for LAI based mode    //131208 moved from CO2_response

      float64 cover_maximum          = cover_maximum_no_CO2_adj;

//actual_biomass_gain_ratio_in_response_to_CO2 = 1.41; // test

      float64 extinction_coef = 0.5;  // This should actually be from the crop parameters kc

      float64 LAI_CO2_Adj = (-log(1.0 - cover_maximum) /extinction_coef)
         * (1.0 + (actual_biomass_gain_ratio_in_response_to_CO2 - 1.0) / 3.0 /*180111 2.0*/ );
      cover_maximum_CO2_adj      = 1.0 - exp(-extinction_coef * LAI_CO2_Adj);
      cover_maximum_CO2_adj = CORN::must_be_less_or_equal_to<float64>(cover_maximum_CO2_adj,1.0);
   }
   return true;
}
//_initialize_______________________________________________________2014-02-05_/
} // namespace CropSyst

