#include "WC_psychrometric_const.h"
#include "WP_atmospheric_pressure.h"
#include "WP_latent_heat_vaporization.h"
#include <iostream>

//______________________________________________________________________________
Psychrometric_constant_calculator::Psychrometric_constant_calculator
(const Latent_heat_vaporization  &_latent_heat_vaporization
,const Atmospheric_pressure      &_atmospheric_pressure
,float64 _specific_heat_air)
: Psychrometric_constant()
, latent_heat_vaporization (_latent_heat_vaporization)
, atmospheric_pressure     (_atmospheric_pressure)
, specific_heat_air     (_specific_heat_air)
{}
//_2014-05-08___________________________________________________________________
const CORN::Quality &Psychrometric_constant_calculator::update()  rectification_
{  float64 PC = calc();
   const CORN::Quality_clad PC_quality(quality_calculated_from_quality(atmospheric_pressure.get_quality().worst(latent_heat_vaporization.get_quality())));
   update_kPa_per_C(PC);
   return get_quality();
}
//_2014-05-08___________________________________________________________________
float64 Psychrometric_constant_calculator::calc()                          const
{
   // In the Kimberly model, this is 0.001005 (at constant pressure).
   float64 atmospheric_pressure_ =                                               //011009
      atmospheric_pressure.get_kPa();                                            //100420
   static const float64 water_to_air_molecular_weight_ratio = 0.622;             //110415
   float64 psychrometric =
      (specific_heat_air * atmospheric_pressure_)
      / (  latent_heat_vaporization.get_MJ_per_kg()
         * water_to_air_molecular_weight_ratio);                                 //011008
  return psychrometric;  // kPa/C
}
//_2014-05-08___________________________________________________________________
