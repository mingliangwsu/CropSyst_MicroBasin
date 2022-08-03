#ifndef weatherH
#define weatherH
//This class will eventually become the top level weather class
// instead of weather_VP
// weather components such as sun, sky, wind, solar radiation etc will be moved
// here and allocated as needed.
#include "common/weather/day/weather_day.h"
#include "common/weather/day/sun_days.h"
#include "common/solar/irradiance_extraterrestrial.h"
class Weather_hours;
class Location_parameters;
//______________________________________________________________________________
class Weather
: public Weather_day  // currently deriving from Weather day so I don't have to write all the accessors
{
 public: // Constructor
   Weather
   (Weather_database    *weather_database                                        //050307
   ,modifiable_ Weather_provider &provider                                       //151201
   ,const Geocoordinate &geocoordinate                                           //150627
   ,float64              screening_height                                        //151128
   ,const CORN::Date_const &today                                                //150125
   ,Sun_days            *sun_days                                                //041112
   ,bool                 enable_hourly
   ,bool                 treat_valid_data_as_real                                //081109
   ,bool                 read_only = false);
   virtual ~Weather();
 public: //
   virtual bool update();
 public:
   Weather_day                &provide_daily();
 public:
};
//______________________________________________________________________________
#endif

