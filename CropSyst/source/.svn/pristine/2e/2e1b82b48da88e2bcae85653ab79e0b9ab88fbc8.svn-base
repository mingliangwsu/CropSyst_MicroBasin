#ifndef SOIL_TEMPERATURE_HOURLY_INTERFACE_H
#define SOIL_TEMPERATURE_HOURLY_INTERFACE_H
#include "corn/chronometry/time_types.hpp"
#include "corn/const.h"
//______________________________________________________________________________
class Soil_temperature_profile_hourly_interface
{
public:
   virtual ~Soil_temperature_profile_hourly_interface() {}
   virtual float64 get_temperature(CORN::Hour hour, nat8 layer)            const = 0;
   virtual bool initialize()                                     initialization_ = 0;
   virtual bool know_has_snow_cover(bool has_snow_)                   cognition_ = 0;  //160721
};
//_2015-04-22___________________________________________________________________
#endif
