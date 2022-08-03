#ifndef WC_solar_radiationH
#define WC_solar_radiationH
#include "weather/parameter/WP_solar_radiation.h"
#include "corn/chronometry/date_I.h"
#include "common/geodesy/geocoordinate.h"
//______________________________________________________________________________
namespace CS
{
   class Solar_irradiance_extraterrestrial;                                      //151022
   class Solar_irradiance_extraterrestrial_daily;
}
class Solar_radiation_parameters;
class Air_temperature_maximum ;
class Air_temperature_minimum ;
class Air_temperature_average ;
//______________________________________________________________________________
class Solar_radiation_with_estimation_parameter       // Rename to Solar_radiation_with_estimation_calculator
: public Solar_radiation
{
protected: // from weather_provider
   const Solar_radiation_parameters    &generation_parameters;
   const CS::Solar_irradiance_extraterrestrial  &ET_solar_irradiance_new;        //150625
      // can be Solar_irradiance_extraterrestrial_daily or hourly
   Air_temperature_maximum    &air_temperature_max;
   Air_temperature_minimum    &air_temperature_min;
   Air_temperature_average    &air_temperature_avg;
protected: // contributes
   contribute_ float64 temperature_range;
   contribute_ float64 pot_solar_rad;
   contribute_ CORN::Quality_clad estimation_quality;
public:
   Solar_radiation_with_estimation_parameter
      (const Solar_radiation_parameters   &_generation_parameters
      ,const CS::Solar_irradiance_extraterrestrial &_ET_solar_irradiance_new     //150625
      // daily
      ,Air_temperature_maximum   &_air_temperature_max
      ,Air_temperature_minimum   &_air_temperature_min
      ,Air_temperature_average   &_air_temperature_avg);
   virtual const CORN::Quality &update()                         rectification_;
};
//_2010-12-08___________________________________________________________________
class Solar_radiation_with_Donatelli_Campbell_estimation_parameter
: public Solar_radiation_with_estimation_parameter
{contribute_ float64 min_temp_adjacent_day;
public:
   Solar_radiation_with_Donatelli_Campbell_estimation_parameter
      (const Solar_radiation_parameters   &_generation_parameters

      ,const CS::Solar_irradiance_extraterrestrial &_ET_solar_irradiance_new     //150625
         // daily
      ,Air_temperature_maximum   &_air_temperature_max
      ,Air_temperature_minimum   &_air_temperature_min
      ,Air_temperature_average   &_air_temperature_avg
      );
   virtual const CORN::Quality &update()                         rectification_;
 private:
   float64 compute()                                                      const;
 public: // because used by climgen
   float64 calc_atmospheric_transmissivity                                       //101208
      ( float64 temperature_range
      , float64 fitted_B_solar_rad
      , float64 adjusted_min_temp
      , float64 adjusted_avg_temp)                                        const;
};
//_2010-12-08___________________________________________________________________
class Solar_radiation_with_Campbell_estimation_parameter
: public Solar_radiation_with_estimation_parameter
{private:
   const CORN::Date_const &today;                                                //150627
   float64 latitude;                                                             //150627
 public:
   Solar_radiation_with_Campbell_estimation_parameter
      (const Solar_radiation_parameters   &generation_parameters_
      ,const CORN::Date_const &today_                                            //150627
      ,float64            latitude_
      ,const CS::Solar_irradiance_extraterrestrial &ET_solar_irradiance_new_     //110414
         //daily
      ,Air_temperature_maximum   &air_temperature_max_
      ,Air_temperature_minimum   &air_temperature_min_
      ,Air_temperature_average   &air_temperature_avg_);
   virtual const CORN::Quality &update()                         rectification_;
 private:
   float64 compute(float64 day_30_pot_solar_rad,float64 B_solar_rad)      const;
   float64 calc_atmospheric_transmissivity
      ( float64 temperature_range
      , float64 day_30_pot_solar_rad
      , float64 B_solar_rad
      , float64 C = 2.0)                                                  const;
   bool summer_B_period()                                                 const;
   float64 estimate_summer_B_solar_rad()                                  const;
   float64 estimate_winter_B_solar_rad()                                  const;
};
//_2010-12-08___________________________________________________________________
#endif

