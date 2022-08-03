#ifndef WP_atmospheric_pressureH
#define WP_atmospheric_pressureH
#include "physics/property/P_pressure.h"
#include "common/CS_parameter_float64.h"
class Geocoordinate;
//______________________________________________________________________________
class Atmospheric_pressure
: public implements_ Physical::Pressure_interface     // Eventually I should have a Pressure_parameter derived from these
, public extends_ CS::Parameter_float64
{
 protected:
   float64 elevation; // meter
 public:
   Atmospheric_pressure(float64 _elevation = 200.0);                             //150629
   virtual const CORN::Quality &update()                          rectification_;
 public:
   float64 estimate() const;
};
//_2008-11-11_________________________________________________________________
#endif

