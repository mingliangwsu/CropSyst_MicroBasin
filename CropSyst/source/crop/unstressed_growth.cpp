#error This class is obsolete, this file can be removed from your project/Makefile //160414

#  include "unstressed_growth.h"
#  include "corn/math/compare.h"
#  include "crop/growth_stages.hpp"
#  include "corn/math/moremath.h"
#include <algorithm>
namespace CropSyst {
//______________________________________________________________________________
Unstressed_growth::Unstressed_growth
(
 #ifdef YAML_PARAM_VERSION
 Crop_parameters_struct::Biomass_production   &parameters_
 #else
 const Crop_parameters   &parameters_                                           //130627
 #endif
,const Vapor_pressure_deficit_daytime  &daytime_vapor_pressure_deficit_
,const float64                         &pot_ref_evapotranspiration_
,const float64                         &CO2_TUE_adjustment_
,const float64                         &CO2_transpiration_adjustment_factor_)
: transpiration_dependent_growth_model
   (parameters_
   ,daytime_vapor_pressure_deficit_
   ,pot_ref_evapotranspiration_
   ,CO2_TUE_adjustment_)
,CO2_transpiration_adjustment_factor(CO2_transpiration_adjustment_factor_)       //151031
{}
//______________________________________________________________________________
void Unstressed_growth::initialize()
{  O_fract_green_cover       = 0;
   O_biomass                 = 0.000001; // cannot be 0
   O_attainable_top_growth   = 0;
   O_GAI                     = 0;
   O_pot_transpiration_CO2_adjusted = 0;                                         //151031
   O_light_depend_growth     = 0;
}
//_2001-10-16___________________________________________________________________
void Unstressed_growth::restart
(float64 init_biomass
,float64 init_GAI
,float64 init_fract_green_cover)
{  O_biomass                = init_biomass;
   O_attainable_top_growth  = init_biomass;
   O_GAI                    = init_GAI;
   O_fract_green_cover      = init_fract_green_cover;
}
//______________________________________________________________________________
void Unstressed_growth::daily_setup
(Normal_crop_event_sequence  growth_stage
,float64 unstressed_fract_canopy_cover // total radiation based with unstressed GAI
,float64 act_GAI)  // current actual green area index
{  if (growth_stage >= NGS_GERMINATION)
      O_fract_green_cover= unstressed_fract_canopy_cover;                        //011016
                                 // total radiation based with unstressed GAI
   // if we are not growing and no GAI, clear the potential transpiraton
   if (!(  (growth_stage >= NGS_ACTIVE_GROWTH)
         &&(growth_stage <=  NGS_HARVESTABLE)                                    //000625
         &&(act_GAI > 0.0)))
               O_pot_transpiration_CO2_adjusted = 0.0;                           //151031_011016
}
//______________________________________________________________________________
void Unstressed_growth::accumulate_GAI_and_biomass
(Normal_crop_event_sequence growth_stage
,float64       param_specific_leaf_area   // Crop parameter
,float64       param_stem_leaf_partition) // Crop parameter
{  // NOTE at this time we do not need to maintain
   // The daily history pools because the nitrogen model
   // only accumulates to about the time until about flowering,
   // before any GAI die off.
   if ((growth_stage > NGS_GERMINATION) && (growth_stage < NGS_DORMANT_or_INACTIVE))
      O_GAI += O_attainable_top_growth * param_specific_leaf_area                //011023
           / CORN_sqr(param_stem_leaf_partition * O_biomass + 1);
   else
      O_GAI = 0.0;
   O_biomass += O_attainable_top_growth;                                         //011023
}
//______________________________________________________________________________
void Unstressed_growth::update_attainable_top_growth
(float64 est_solar_rad     // Estimated solar radiation.
// Now takes referenece ,float64 vapor_pressure_def
,float64 biomass_water_ratio
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
// This mode is for compatibility with previous versions
// These parameters are deprecated and will be removed in version 5
,bool    RUE_PAR_based                                                           //080801
,float64 RUE_PAR_kg_MJ
#endif
,float64 RUE_global_kg_MJ                                                        //080730
,float64 unstressed_fract_canopy_cover_PAR // photosynthetically active radiation based!!!
,float64 unstressed_GAI_fract_canopy_cover_TR  // total solar radiation based    //080730
,float64 temperature_limitation)
{  // For N concentration calculations we need an optimal attainable top growth
   float64 O_intercepted_radiation_dependent_growth = 0;                         //080801
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
// This mode is for compatibility with previous versions
// These parameters are deprecated and will be removed in version 5
   if (RUE_PAR_based)                                                            //080801
   {  float64 photosynthetic_active_radiation = est_solar_rad / 2.0;             //011022
      float64 O_GAI_fract_canopy_cover_for_PAR = unstressed_fract_canopy_cover_PAR; //020624
       O_intercepted_radiation_dependent_growth = RUE_PAR_kg_MJ                  //011022
          * photosynthetic_active_radiation * O_GAI_fract_canopy_cover_for_PAR;  //011016
   } else                                                                        //080801
#endif
   {  float64 total_radiation = (est_solar_rad);  // MJ/m2 ?                     //080428
      float64 intercepted_radiation = total_radiation * unstressed_GAI_fract_canopy_cover_TR;   //080428
      O_intercepted_radiation_dependent_growth = intercepted_radiation * RUE_global_kg_MJ;  //080428
   }
   // Claudio confirmed that we need to use the temperature limitation
   // for this unstress potential growth 020626
   float64 O_temperature_corrected_radiation_dependent_growth
      = O_intercepted_radiation_dependent_growth * temperature_limitation;       //011022
   float64 O_pot_transpiration_dependent_growth                                  //011022
      = transpiration_dependent_growth_model.calc_potential_biomass_production
         (O_pot_transpiration_CO2_adjusted);                                     //151031
   O_attainable_top_growth = std::min<float64>                                   //011022
         (O_temperature_corrected_radiation_dependent_growth
         ,O_pot_transpiration_dependent_growth);
}
//_2005-05-05___________________________________________________________________
float64 Unstressed_growth::update_pot_evapotranspiration(float64 pot_crop_ET,float64 act_GAI)
{  // Note, I am not sure why this is multiplied by fraction of green cover.
   O_pot_transpiration_CO2_adjusted = (act_GAI > 0.0)
   ? (O_fract_green_cover * pot_crop_ET) * CO2_transpiration_adjustment_factor   //151031
   : 0.0;
   return pot_crop_ET;
}
//_2001-10-16___________________________________________________________________
void Unstressed_growth::adjust_for_removal(float64 new_biomass,float64 new_GAI)
{  O_biomass = new_biomass;
   O_GAI = new_GAI;
}
//_2004-12-06___________________________________________________________________
}// namespace CropSyst                                                           //131106

