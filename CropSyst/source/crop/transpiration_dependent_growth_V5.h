#ifndef transpiration_dependent_growth_V5H
#define transpiration_dependent_growth_V5H
#include "crop/transpiration_dependent_growth.h"
namespace CropSyst {
//______________________________________________________________________________
class Biomass_production_transpiration_dependent_V5
// Rename this to Biomass_production_transpiration_dependent_V5
: public extends_ Biomass_production_transpiration_dependent_common
{
   // TUE = transpiration use efficiency
   //___________________________________________________________________________
   private: interface_ TUE_Equation
   {
    public:
      virtual float64 calculate()                                calculation_=0;
         // kg biomass / kg H2O
   };
   //___________________________________________________________________________
   private: class TUE_Equation_Tanner_Sinclair
   : public implements_ TUE_Equation
   {
      const float32                        &param_biomass_water_ratio_Pa;
      const Vapor_pressure_deficit_daytime &curr_daytime_vapor_pressure_deficit;
    public:
      inline TUE_Equation_Tanner_Sinclair
         (const float32                        &param_biomass_water_ratio_Pa_
         ,const Vapor_pressure_deficit_daytime &daytime_vapor_pressure_deficit_)
         : TUE_Equation()
         , param_biomass_water_ratio_Pa(param_biomass_water_ratio_Pa_)
         , curr_daytime_vapor_pressure_deficit(daytime_vapor_pressure_deficit_)
         {}
      virtual float64 calculate()                                  calculation_;
   };
   //___________________________________________________________________________
   private: class TUE_Equation_curve
   : public implements_ TUE_Equation
   {
      const float32 &param_TUE_scaling_coef; // unitless
      const float32 &param_TUE_at_1kPa_VPA;  // g biomass /kg H20
      const Vapor_pressure_deficit_daytime &curr_daytime_vapor_pressure_deficit;
    public:
      inline TUE_Equation_curve
         (const float32 &_param_TUE_scaling_coef
         ,const float32 &_param_TUE_at_1kPa_VPA
         ,const Vapor_pressure_deficit_daytime &_daytime_vapor_pressure_deficit)
         : TUE_Equation()
         , param_TUE_scaling_coef(_param_TUE_scaling_coef)
         , param_TUE_at_1kPa_VPA (_param_TUE_at_1kPa_VPA)
         , curr_daytime_vapor_pressure_deficit(_daytime_vapor_pressure_deficit)
         {}
      virtual float64 calculate()                                  calculation_;
   };
   //___________________________________________________________________________
   private: class TUE_Equation_AquaCrop_water_productivity
   : public implements_ TUE_Equation
   {
      const float32 &param_AquaCrop_water_productivity;
      const float64 &pot_ref_evapotranspiration;
    public:
       inline TUE_Equation_AquaCrop_water_productivity
         (const float32 &_param_AquaCrop_water_productivity
         ,const float64 &_pot_ref_evapotranspiration
         )
         : TUE_Equation()
         , param_AquaCrop_water_productivity(_param_AquaCrop_water_productivity)
         , pot_ref_evapotranspiration(_pot_ref_evapotranspiration)
         {}
      virtual float64 calculate()                                  calculation_;
   };
   //___________________________________________________________________________
 private:
   const Crop_parameters_struct::Biomass_production   &parameters;
   TUE_Equation   *TUE_equation;
 //___________________________________________________________________________
 public:
   Biomass_production_transpiration_dependent_V5
      (Crop_parameters_struct::Biomass_production   &parameters_
      ,const Vapor_pressure_deficit_daytime  &daytime_vapor_pressure_deficit_
      ,const float64  &pot_ref_evapotranspiration_
      ,const float64  &CO2_TUE_adjustment_
      //151104 ,const float64  &CO2_transpiration_adjustment_factor_
      );
 protected:
   virtual float64 get_transpiration_use_efficiency_unadj()                const; //151029
};
//_2015-10-30___________________________________________________________________
} //namespace CropSyst
#endif
