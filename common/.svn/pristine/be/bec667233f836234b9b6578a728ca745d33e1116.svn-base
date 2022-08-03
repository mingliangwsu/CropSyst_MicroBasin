#include "weather/parameter/WP_atmospheric_pressure.h"
#include "common/geodesy/geocoordinate.h"
#include <math.h>
//______________________________________________________________________________
Atmospheric_pressure::Atmospheric_pressure
(float64 _elevation)
: Physical::Pressure_interface()
, CS::Parameter_float64(INTENSIVE,0.0,UC_kPa,CORN::unknown_quality)              //150206
, elevation(_elevation)                                                          //150629
{}
//______________________________________________________________________________
const CORN::Quality &Atmospheric_pressure::update()               rectification_
{  update_value_qualified_code(estimate(),CORN::estimated_quality);              //150126
   return (*this);
}
//______________________________________________________________________________
float64 Atmospheric_pressure::estimate()                                   const
{  float64 atmos_pressure_kPa
      = 101.3 * pow(((293.0 - 0.0065 * elevation) / 293.0), 5.26);
   return  atmos_pressure_kPa;
}
//______________________________________________________________________________

