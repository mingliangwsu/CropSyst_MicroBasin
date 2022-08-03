#include "weather/weather.h"
#include "common/weather/weather.h"
#include "common/weather/hour/weather_hours.h"
#include "common/weather/database/weather_database.h"
#include "solar/irradiance_extraterrestrial.h"

//______________________________________________________________________________
Weather::Weather
(Weather_database             *weather_database_                                 //050307
,modifiable_ Weather_provider &provider_                                         //151201
,const Geocoordinate          &geocoordinate_                                    //150627
,float64                       screening_height_                                 //151128
,const CORN::Date_const       &today_                                            //150125
,Sun_days   *sun_days_                                                           //041112
,bool        enable_hourly_
,bool        treat_valid_data_as_real_                                           //081109
,bool        read_only_)                                                         //000711
: Weather_day(weather_database_
   ,provider_                                                                    //151202
   ,geocoordinate_
   ,screening_height_                                                            //151120
   ,today_
   ,treat_valid_data_as_real_,read_only_)
{}
//______________________________________________________________________________
Weather::~Weather()
{}
//______________________________________________________________________________
bool Weather::update()
{  bool updated = Weather_day::update();
   return updated;
}
//______________________________________________________________________________
Weather_day &Weather::provide_daily()
{  return (Weather_day &)*this;
}
//______________________________________________________________________________

