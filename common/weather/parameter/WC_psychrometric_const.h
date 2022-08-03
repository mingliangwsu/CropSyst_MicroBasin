#ifndef WC_psychrometric_constH
#define WC_psychrometric_constH
#include "weather/parameter/WP_psychrometric_const.h"
class Latent_heat_vaporization;
class Atmospheric_pressure;
//______________________________________________________________________________
class Psychrometric_constant_calculator
: public extends_ Psychrometric_constant
{private:
   const Latent_heat_vaporization   &latent_heat_vaporization;
   const Atmospheric_pressure       &atmospheric_pressure;
   float64                           specific_heat_air;  /*  MJ/(kg C) */
 public:
   Psychrometric_constant_calculator
      (const Latent_heat_vaporization  &latent_heat_vaporization
      ,const Atmospheric_pressure      &atmospheric_pressure
      ,float64 specific_heat_air = 0.001013);  /*  MJ/(kg C) */
   virtual const CORN::Quality &update()                          rectification_;
 private:
   float64 calc()                                                          const;
};
//______________________________________________________________________________
#endif
