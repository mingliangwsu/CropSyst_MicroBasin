#ifdef CO2_V4
#error 131205 This is now permanently obsolete
#ifndef crop_CO2H
#define crop_CO2H
/*
This class provides the optional crop CO2 response functions
*/
#include "crop/crop_param.h"
#if (CROPSYST_VERSION >= 5)
namespace CropSyst {
#endif
//______________________________________________________________________________
class Crop_CO2_response
{
   const Crop_parameters_struct::CO2_Response &parameters;
public:  // The following values are computed once
   //110913 check used    float64  CO2_adj_light_to_biomass;
   float64  CO2_adj_canopy_resistance;
   float64  actual_biomass_gain_ratio_in_response_to_CO2;
         //110913 adj_growth_ratio_current_to_baseline_conc_CO2
public:  // The following are recomputed daily
   //110913 moved to canopy    float64  leaf_area_growth_related_biomass_at_baseline_conc;
   float64  transpiration_reduction_factor_due_to_CO2;
      //110913 was daily_ratio_elevated_to_baseline_conc_CO2_ET;
public: // Constructor
   Crop_CO2_response
      (const Crop_parameters_struct::CO2_Response &i_parameters   // Crop parameters
      ,float64                         current_CO2_conc
      ,float64                         reference_light_to_biomass);
   void update(float64 current_CO2_conc);
   /*110913 moved to canopy_growth_LAI_+based
   inline void update_leaf_area_growth_related_biomass_at_baseline_conc(float64 leaf_area_growth_related_biomass)
      { leaf_area_growth_related_biomass_at_baseline_conc
         =  leaf_area_growth_related_biomass
         / actual_biomass_gain_ratio_in_response_to_CO2};
   inline void no_leaf_area_growth_related_biomass_at_baseline_conc()
      { leaf_area_growth_related_biomass_at_baseline_conc = 0.0; };
   */
   inline float64 get_canopy_resistance()                                  const //110904
      { return CO2_adj_canopy_resistance; }
   inline float64 get_TUE_adjustment()                                     const //110913
      {return actual_biomass_gain_ratio_in_response_to_CO2;}
};
//______________________________________________________________________________
#if (CROPSYST_VERSION >= 5)
} // namespace CropSyst
#endif
#endif
// crop_CO2.h

#endif
