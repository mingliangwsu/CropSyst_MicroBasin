#ifndef WP_relative_humidityH
#define WP_relative_humidityH
#include "common/CS_parameter_float64.h"
//______________________________________________________________________________
class Relative_humidity
: public extends_ CS::Parameter_float64
{
 public:
   inline Relative_humidity()
      : CS::Parameter_float64(false,0.0,UC_percent,CORN::unknown_quality)
      {}
   inline float64 percent()                                                const
      { return in_prescribed_units(); }
};
//_2014-02-20___________________________________________________________________
#endif

