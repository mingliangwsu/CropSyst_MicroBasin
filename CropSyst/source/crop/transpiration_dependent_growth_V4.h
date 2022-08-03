#ifndef transpiration_dependent_growth_V4H
#define transpiration_dependent_growth_V4H
#include "crop/transpiration_dependent_growth.h"

namespace CropSyst {
//______________________________________________________________________________
class Biomass_production_transpiration_dependent_V4 // was Transpiration_dependent_growth_V4
: public extends_ Biomass_production_transpiration_dependent_common
{
   const Crop_parameters  &parameters;      // Owned by crop object
   // Currently this includes all the CropSyst crop parameters
   // But I should narrow down to just the parameters relevent to attainable growth.
   // TUE = transpiration use efficiency

   const Vapor_pressure_deficit_daytime &daytime_vapor_pressure_deficit;
      // used by curve and Tanner-Sinclair models (not AquaCrop)

   const float64  &pot_ref_evapotranspiration;                                   //130627 moved from crop_common
      // ref to crop_common ET_ref_pot_local
      // Used only by AquaCrop

   /*180111
   //130628 these daily parameters I think should be references so we
   // dont have to pass every time step
   int16    season;                                                              //130627
   bool     before_WUE_change;                                                   //130627
   */

   const nat8 &season;                                                                 //180111
   const bool &before_WUE_change;                                                      //180111

 public:
   Biomass_production_transpiration_dependent_V4
      (const Crop_parameters                 &parameters_
      ,const Vapor_pressure_deficit_daytime  &daytime_vapor_pressure_deficit_
      ,const float64                         &pot_ref_evapotranspiration_
      ,const float64                         &CO2_TUE_adjustment_
      ,const nat8                            &season_                            //180111
      ,const bool                            &before_WUE_change_);               //180111
   /*180111
   void know_daily_parameters                                                    //130627
      (int16   _season
      ,bool    _before_WUE_change);
   */
 public:
   float64 get_biomass_water_ratio               (bool before_WUE_change) const; //980220
 protected:
   float64 get_TUE_at_1kPa_VPD                   (bool before_WUE_change) const; //080428
   float64 get_water_productivity                (bool before_WUE_change) const; //080428
   float64 get_TUE_scaling_coef                  (bool before_WUE_change) const; //091201
   virtual float64 get_transpiration_use_efficiency_unadj()               const; //151029
};
//_2008-07-21___________________________________________________________________
}
#endif

