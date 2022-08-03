#ifndef P_vapor_pressureH
#define P_vapor_pressureH
#include "common/physics/property/P_pressure.h"
#include "corn/measure/measures.h"
#include "corn/const.h"

#define        OVER_WATER_ONLY      true
#define        OVER_ICE_IF_FREEZING false

namespace Physical
{
//_________________________________________________________________________________________
class Vapor_pressure_interface
: public extends_interface_ Physical::Pressure_interface // intensive
{
 public:
   float64 calc_saturation_kPa(float64 at_temperature_C, float64 air_temp_C, bool over_water_only) const;
   float64 saturation_temperature // C      // rename this to  calc_saturation_temperature    //980305
      (float64 saturation_vapor_pressure // kPa
      ,float64 airtemp                                                           //040114
      ,bool over_water_only)                                              const; //040114
   float64 calc_slope_of_saturation(float64 avg_air_temp)                 const;
};
//_2015-01-22___________________________________________________________________
extern float64 calc_saturation_kPa(float64 at_temperature_C  ,float64 air_temp_C, bool over_water_only); //kPa
}

#endif

