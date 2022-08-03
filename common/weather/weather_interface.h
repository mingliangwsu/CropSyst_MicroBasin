#ifndef weather_interfaceH
#define weather_interfaceH
#ifndef primitiveH
#   include "corn/primitive.h"
#endif
#ifndef constH
#   include "corn/const.h"
#endif
#   include "corn/chronometry/date_I.h"
#include "common/biometeorology/parameter/CO2_atmospheric_conc.h"
#include "common/weather/parameter/WP_air_temperature.h"
#include "common/weather/parameter/WP_precipitation.h"
#include "common/CS_parameter.h"
#include "UED/library/UED_types.h"

#include <string>
//_____________________________________________________________________________
namespace CORN
{  // forward declarations
   class Quality;
}
//_____________________________________________________________________________
interface_ Weather_spanning_interface  // This should be moved to a separate file because CropSyst V5 doesn't use Weather_interface
{
   inline virtual ~Weather_spanning_interface() {}                               //151204
   virtual bool get_parameter_on
      (modifiable_ CS::Parameter &parameter
      ,nat32  variable_code // Typically the variable code will be UED variable code
      ,const CORN::Date_const &on_date)                        rectification_=0;
   virtual float64 get_air_temperature_min_tomorrow()                   const=0;
   virtual float64 get_air_temperature_max_yesterday()                  const=0;
   inline virtual float64 get_next_min_temperature()                    const
      { return get_air_temperature_min_tomorrow(); }
      // get_next_min_temperature is deprecated, use get_air_temperature_min_tomorrow
};
//_2015-11-30____________________________________________________________________________
interface_ Weather_interface
: public extends_interface_ Weather_spanning_interface                           //151130
{
public:
   inline Weather_interface() {}
   inline virtual ~Weather_interface() {}                                        //151204
   virtual const char *get_description(std::string &return_buffer)      const=0;
public:  // Current date meterological accessors
 public: // Solar radiation accessors
public: // vapor pressure accessors
   virtual float64 get_curr_act_vapor_pressure()                        const=0;
   virtual float64 get_atmospheric_pressure_est_kPa()                   const=0;
   virtual float64 get_curr_avg_fullday_vapor_pressure_deficit(CORN::Quality &quality) const=0;
public:  // Accessors for a specified date.
   virtual float64 calc_normalized_wind_speed(float64 wind_speed_m_ts)  const=0;
   virtual float64 calc_slope_of_saturation(float64 avg_air_temperature)const=0;
   // if day of year is 0 then the day length of the current day is returned
   // otherwise it returns the values for the specified day of the year
public: // Data quality accessors
#ifdef NYI
   virtual CORN::Quality_code get_max_temperature_quality()             const=0;
   virtual CORN::Quality_code get_min_temperature_quality()             const=0;
   virtual CORN::Quality_code get_solar_radiation_quality()             const=0;
   virtual CORN::Quality_code get_wind_speed_quality()                  const=0;
   virtual CORN::Quality_code get_max_relative_humidity_quality()       const=0;
#endif
};
//_____________________________________________________________________________
#endif

