#ifndef weather_crop_interfaceH
#define weather_crop_interfaceH

#include "weather/current_elements_interface.h"

#ifndef constH
#   include <corn/const.h>
#endif
#ifndef date_typesHPP
#  include <corn/chronometry/date_types.hpp>
#endif
#ifndef qualityHPP
#  include <corn/quality.hpp>
#endif
#ifndef timeH
#  include <corn/datetime/time.h>
#endif
class Weather_hours;
class Atmospheric_CO2_change_interface;                                          //140508
//_____________________________________________________________________________
interface_ Weather_for_crop_interface
: public virtual Weather_current_interface
{
   virtual float64 get_max_temperature(const CORN::Date &on_date)          const = 0;
   virtual float64 get_min_temperature(const CORN::Date &on_date)          const = 0;
   virtual float64 get_curr_max_vapor_pressure_deficit()                   const = 0;     // kPa?
   // CO2
   virtual float64 get_curr_CO2_conc_ppm()                                 const = 0;

      // As of Feb 2010 world wide average CO2 concentration is 390ppm
      // rising aproximately 2ppm annually but accelerating.

   // Accessors for a specified date.

   virtual float64 get_day_length_hours( nat16 on_day_of_year)             const = 0;
   // Solar radiation accessors
   virtual float64 get_cloud_cover_fraction()                              const = 0;// decimal % ?
   virtual bool has_atmospheric_CO2_change()                               const = 0;
   virtual const Atmospheric_CO2_change_interface *get_atmospheric_CO2()   const = 0;//140508
};
//_____________________________________________________________________________
#endif
