#ifndef slope_SVP_curve_psychrometric_resistanceH
#define slope_SVP_curve_psychrometric_resistanceH
#include "common/CS_parameter_float64.h"
#include "common/weather/parameter/WP_psychrometric_const.h"
#include "common/weather/parameter/WP_vapor_pressure_saturation_slope.h"
#include "common/biometeorology/aerodynamics.h"
//---------------------------------------------------------------------------
class Slope_saturated_vapor_pressure_plus_psychrometric_resistance
: public extends_ CS::Parameter_float64   // not sure if intensive ?
{
   const Vapor_pressure_saturation_slope  &vapor_pressure_saturation_slope;
   const Psychrometric_constant           &psychrometric_constant;
   const Aerodynamics                     &aerodynamics;
   float64                                 bulk_resistance_d_m;                  //151104
 public:
   Slope_saturated_vapor_pressure_plus_psychrometric_resistance
      (const Vapor_pressure_saturation_slope  &_vapor_pressure_saturation_slope
      ,const Psychrometric_constant           &_psychrometric_constant
      ,const Aerodynamics                     &_aerodynamics

      ,const float64                           _bulk_resistance_d_m);
   // Copy constructure (used by CropSyst::Crop_nitrogen)
   Slope_saturated_vapor_pressure_plus_psychrometric_resistance
      (const Slope_saturated_vapor_pressure_plus_psychrometric_resistance &from_copy
      ,float64                                 _bulk_resistance_d_m);
   inline float64 get_kPa_per_C()        const { return in_prescribed_units(); }
   inline float64 set_kPa_per_C(float64 value_kPa_C) modification_
      {  return update_value_with_units(value_kPa_C,UC_kPa_per_C);
      }
   virtual const CORN::Quality &update()                         rectification_;
   inline float64 update_kPa_per_C(float64 value_kPa_C)          rectification_
      {  return update_value_with_units(value_kPa_C,UC_kPa_per_C);
      }
 private:
   float64 calc()                                                         const;
};
//_2015-05-31___________________________________________________________________
#endif
