#ifndef environment_baseH
#define environment_baseH
#include "corn/primitive.h"
#include "physics/property/P_temperature.h"
#include "common/weather/weather_provider.h"

class Weather_provider;
class Soil_interface;

//______________________________________________________________________________
class Environment_base
{
 public:                                                                         //130506
   Soil_interface    *soil;      // Soil may be null inside buildings etc.       //020620
   bool               owns_soil;                                                 //030710
      // True if this is responsible for deleting the soil.

   Weather_provider  *weather_today;                                             //141016
public:
   Environment_base();
   virtual ~Environment_base();                                                  //030710
   void set_soil(Soil_interface *soil,bool owns_soil);                           //060703

   virtual float32 get_precipitation_today_m()                             const;
   bool snowed()                                                           const;//141016
   inline virtual const Physical::Temperature &ref_ambient_temperature()   const;//150217
   inline virtual Wind_speed &ref_wind_speed();                                  //151109BRC
   virtual float32 get_curr_wind_speed_m_s()                               const;
      // meters per second
   virtual float64 get_curr_wind_speed_m_s(float64 height)                 const;//151014BRC
   virtual float32 get_vapor_pressure_deficit_daily_kPa()                  const;//151014BRC
 public: // This functions aredeprecated, used ref_ambient_temperature()
   virtual float32 get_avg_temperature()                                   const;
      // C current temperature in the environment
   inline virtual float32 get_ambient_temperature()                        const //100303
      { return get_avg_temperature(); }
      // currently just an alias
};
//______________________________________________________________________________
#endif

