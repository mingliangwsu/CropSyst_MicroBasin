#ifndef WC_ET_referenceH
#define WC_ET_referenceH
#include "weather/parameter/WP_ET_reference.h"
//______________________________________________________________________________
class Reference_evapotranspiration_model_set;
class Weather_provider;
class Geolocated_solar_irradiance;
class Aerodynamics;
class Slope_saturated_vapor_pressure_plus_psychrometric_resistance;
//______________________________________________________________________________
class ET_Reference_calculator
: public ET_Reference
{
protected: friend class Weather_provider;
   Reference_evapotranspiration_model_set *ET_reference_models;
public:
   ET_Reference_calculator
      (float32             _elevation                                            //150617
      ,const float64 &_day_length_hours_today                                    //150627
      ,Weather_provider   &_weather);
   virtual const CORN::Quality &update()                          rectification_;

   virtual const Slope_saturated_vapor_pressure_plus_psychrometric_resistance            //160731
      &ref_slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference() const;

   virtual const float64  &ref_aerodynamic_resistance_ref_plants()         const;//160731
};
//______________________________________________________________________________

#endif

