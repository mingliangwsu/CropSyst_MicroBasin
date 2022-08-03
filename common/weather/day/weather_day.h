#ifndef weather_dayH
#define weather_dayH
#ifndef wthrH
#   include "common/weather/wthr.h"
#endif
#ifndef sun_daysH
#   include "common/weather/day/sun_days.h"
#endif
#ifndef sun_hoursH
#   include "common/weather/hour/sun_hours.h"
#endif
#ifndef WP_atmospheric_pressureH
#   include "common/weather/parameter/WP_atmospheric_pressure.h"
#endif
#ifndef constH
#   include "corn/const.h"
#endif
#ifndef geolocationH
#  include "common/geodesy/geolocation.h"
#endif
class Vapor_pressure;
//______________________________________________________________________________
class Weather_day
: public Weather_with_solar_rad_estimation   // eventually this will be broken out in components
{protected:
 public:
   Atmospheric_pressure   atmospheric_pressure_parameter;                        //081111
 public: // constructor
   Weather_day
   (Weather_database    *weather_database_                                       //050307
   ,modifiable_ Weather_provider &provider_                                      //151201
   ,const Geocoordinate &geocoordinate_                                          //150627
   ,float64              screening_height_                                       //151128
   ,const CORN::Date_const &today_                                               //150125
   ,bool                 treat_valid_data_as_real_                               //081109
   ,bool                 read_only_ = false);                                    //000711
   inline virtual ~Weather_day() {}                                              //151204
 public:
   virtual bool update();                                                        //991012
   virtual void invalidate(bool absolutely)                        modification_;//091216
 public: // Component accessors
   Vapor_pressure    &get_vapor_pressure();
 public: // Vapor pressure accessors
   virtual float64 get_curr_act_vapor_pressure()                           const;
   virtual float64 get_atmospheric_pressure_est_kPa()                      const;
   virtual float64 get_curr_avg_daytime_vapor_pressure_deficit()           const;//050801
   virtual float64 get_curr_avg_fullday_vapor_pressure_deficit(Quality &quality) const; //050801
   float64 curr_vapor_pressure_actual_calc_saturation_kPa(float64 at_temperature_C, float64 air_temp_C, bool over_water_only) modification_;  //050802
 private:
   void require_vapor_pressure();
};
//______________________________________________________________________________
#endif

