#ifndef WP_vapor_pressureH
#define WP_vapor_pressureH
#include "common/CS_parameter_float64.h"
#include "physics/property/P_vapor_pressure.h"
//_______________________________________________________________________________
class Vapor_pressure_base       // Rename this to simply Vapor_pressure and move to physics/
: public extends_interface_ Physical::Vapor_pressure_interface
, public extends_ CS::Parameter_float64
{
 public:
   inline Vapor_pressure_base
      (float64 default_value = 0.0
       ,CORN::Quality_code  default_quality_code = CORN::unknown_quality)
      : CS::Parameter_float64 (INTENSIVE,default_value,UC_kPa,default_quality_code)
      {}
 private:
   inline virtual float64 get_value()                                      const //150123
      { return get_amount(); };
   virtual float64 force_value(float64 new_value)                 rectification_ //150123
      { return force_amount(new_value); }
};
//_2015-01-22__2005-06-02_______________________________________________________
class Vapor_pressure_daytime
: public extends_ Vapor_pressure_base
{public:
   inline Vapor_pressure_daytime()
      : Vapor_pressure_base()
      {}
};
//_2014-02-20__________________________________________________________________/
class Vapor_pressure_nighttime
: public extends_ Vapor_pressure_base
{public:
   inline Vapor_pressure_nighttime()
      : Vapor_pressure_base()
      {}
};
//_2014-02-20__________________________________________________________________/
#endif

