#ifndef crop_N_V5H
#define crop_N_V5H
#include "crop/crop_N_common.h"
namespace CropSyst
{
//______________________________________________________________________________
class Crop_nitrogen_V5
: public extends_ Crop_nitrogen_common
{
   const float64 &transpiration_use_efficiency_CO2_adjusted;
 public:
   Crop_nitrogen_V5
      (Crop_parameters::Nitrogen &_parameters
      ,Crop_complete             &_crop
      ,Soil_interface            *_soil
      ,Soil_nitrogen_interface   *_chemicals
      ,const Slope_saturated_vapor_pressure_plus_psychrometric_resistance
         *_slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference
         // although _slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference
         // is optional, if it is not specified, there will be no correction for transpiration
      ,const float64 &transpiration_use_efficiency_CO2_adjusted                  //151104
         // adjusted when CO2 is enabled otherwise unadjusted
      );
   inline virtual ~Crop_nitrogen_V5() {}                                         //151204
 public:
   virtual float64 update_limited_pot_transpiration()              modification_;
   virtual float64 update_limited_growth
      (float64 attainable_growth_transp_or_RUE
      ,float64 root_activity_factor)                               modification_;
};
//_2015-10-29___________________________________________________________________
} // namespace CropSyst
#endif

