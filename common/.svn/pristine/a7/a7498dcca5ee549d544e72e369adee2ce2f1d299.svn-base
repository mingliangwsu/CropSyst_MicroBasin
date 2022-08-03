#ifndef WP_vapor_pressure_deficitH
#define WP_vapor_pressure_deficitH
#include "weather/parameter/WP_vapor_pressure.h"
#include "weather/weather_types.h"
//170803 class Vapor_pressure_deficit_parameters;
//______________________________________________________________________________
class Vapor_pressure_deficit
: public extends_ Vapor_pressure_base
{
};
//_2014-02-20___________________________________________________________________
class Vapor_pressure_deficit_max
: public extends_ Vapor_pressure_deficit
{public:
   virtual float64 saturation_at_max_dew_point(bool over_water_only)       const { assert(false); return 0.0; }
      // probably rename this to calc_saturation?
};
//_2014-02-20___________________________________________________________________
class Vapor_pressure_deficit_fullday
: public extends_ Vapor_pressure_deficit
{
};
//_2014-02-20___________________________________________________________________
class Vapor_pressure_deficit_daytime
: public extends_ Vapor_pressure_deficit
{
};
//_2014-02-20___________________________________________________________________

#endif

