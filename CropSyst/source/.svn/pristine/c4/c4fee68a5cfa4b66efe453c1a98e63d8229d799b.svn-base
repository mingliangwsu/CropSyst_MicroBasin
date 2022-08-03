
// This class is obsolete, now using soil_evaporation.h

#ifndef evaporation_abstractH
#define evaporation_abstractH
#include "soil/evaporation_interface.h"
#include "corn/primitive.h"
#include "corn/chronometry/time_types.hpp"
//______________________________________________________________________________

//160525 I now have have the new Evaporator class which distributes
// daily evaporation by hour (based on radiation)

class Soil_evaporation_abstract
: virtual public Soil_evaporation_interface
{
 public:
   inline Soil_evaporation_abstract()
      : Soil_evaporation_interface() {};
   float64 get_hourly_fraction_of_daily_demand(CORN::Hour hour)            const; //051130
};
//______________________________________________________________________________
#endif

