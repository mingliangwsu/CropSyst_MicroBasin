#include "WC_solar_radiation.h"
#include "weather/parameter/WP_air_temperature.h"
#include "solar/irradiance_extraterrestrial.h"
#include "corn/math/moremath.h"
#include "weather/loc_param.h"
#include <math.h>
//______________________________________________________________________________
Solar_radiation_with_estimation_parameter::Solar_radiation_with_estimation_parameter
(const Solar_radiation_parameters   &_generation_parameters
,const CS::Solar_irradiance_extraterrestrial  &_ET_solar_irradiance_new          //150625
,Air_temperature_maximum   &_air_temperature_max
,Air_temperature_minimum   &_air_temperature_min
,Air_temperature_average   &_air_temperature_avg
)
:Solar_radiation()
,generation_parameters(_generation_parameters)
,ET_solar_irradiance_new(_ET_solar_irradiance_new)                               //150625
,air_temperature_max(_air_temperature_max)
,air_temperature_min(_air_temperature_min)
,air_temperature_avg(_air_temperature_avg)
,temperature_range(0)
,pot_solar_rad(0)
{}
//_2010-12-08___________________________________________________________________
Solar_radiation_with_Donatelli_Campbell_estimation_parameter
::Solar_radiation_with_Donatelli_Campbell_estimation_parameter
(const Solar_radiation_parameters   &_generation_parameters

,const CS::Solar_irradiance_extraterrestrial &_ET_solar_irradiance_new           //150625
,Air_temperature_maximum   &_air_temperature_max
,Air_temperature_minimum   &_air_temperature_min
,Air_temperature_average   &_air_temperature_avg
)
:Solar_radiation_with_estimation_parameter(_generation_parameters
,_ET_solar_irradiance_new                                                        //150625
,_air_temperature_max,_air_temperature_min,_air_temperature_avg)
, min_temp_adjacent_day(0)
{}
//_2010-12-08___________________________________________________________________
Solar_radiation_with_Campbell_estimation_parameter
::Solar_radiation_with_Campbell_estimation_parameter
(const Solar_radiation_parameters   &_generation_parameters
,const CORN::Date_const             &_today                                      //150627
,float64            _latitude
,const CS::Solar_irradiance_extraterrestrial &_ET_solar_irradiance_new           //150625
,Air_temperature_maximum  &_air_temperature_max
,Air_temperature_minimum  &_air_temperature_min
,Air_temperature_average  &_air_temperature_avg
)
:Solar_radiation_with_estimation_parameter
   (_generation_parameters
   ,_ET_solar_irradiance_new                                                     //150625
   ,_air_temperature_max,_air_temperature_min,_air_temperature_avg)
,today(_today)                                                                   //150627
,latitude(_latitude)                                                             //150627
{}
//_2010-12-08___________________________________________________________________
const CORN::Quality &Solar_radiation_with_estimation_parameter::update() rectification_
{
   const CORN::Quality &worst_temperature_quality = air_temperature_max.worst(air_temperature_min);   //081024
   estimation_quality.assume_code(quality_estimated_from_quality(worst_temperature_quality));
   temperature_range = air_temperature_max.Celcius() - air_temperature_min.Celcius();
   pot_solar_rad = ET_solar_irradiance_new.get_MJ_per_m2_day();                      //150625_011009
/*150627
   // new will replace old, but need to check that it has same value

   pot_solar_rad = ET_solar_irradiance_old.get_extraterrestrial_irradiance_today();  //011009
*/   
   return estimation_quality;
}
//_2010-12-08___________________________________________________________________
const CORN::Quality &Solar_radiation_with_Donatelli_Campbell_estimation_parameter::update() rectification_
{
   if (!is_valid())
   {const CORN::Quality &result_quality = Solar_radiation_with_estimation_parameter::update();
   float64 temperature_differential
      =  air_temperature_max.Celcius()
      - (air_temperature_min.Celcius()
         + min_temp_adjacent_day) / 2.0;                                         //980331
   bool use_temperature_differential = true;
      // In ClimGen generation this was always true, I think that was the only
      // occurance (The default or first update in ClimGen uses false, but the true is used later to override)
   float64 est_value = compute();
   update_value_qualified(est_value,result_quality);                             //150121
   min_temp_adjacent_day = air_temperature_min.Celcius();
   }
   return get_quality();
}
//_2010-12-08___________________________________________________________________
const CORN::Quality &Solar_radiation_with_Campbell_estimation_parameter::update() rectification_
{  const CORN::Quality &result_quality = Solar_radiation_with_estimation_parameter::update();
   float64 summer_B_solar_rad = estimate_summer_B_solar_rad();                   //070313
   float64 winter_B_solar_rad = estimate_winter_B_solar_rad();                   //980312
   // This B summer and winter are not really the summer, but rather what
   // half of the year summer falls in.
   float64 B_solar_rad = summer_B_period()
      ? summer_B_solar_rad
      : winter_B_solar_rad;
   CORN::Date_clad_32 date_minus_30(today.get_date32()); date_minus_30 -= 30;    //970617
   float64 pot_solar_rad_last_month = 0.0;
   pot_solar_rad_last_month = ET_solar_irradiance_new.get_MJ_per_m2_day(date_minus_30.get_DOY());  //150625_011009
   float64 est_value = compute
      (pot_solar_rad_last_month,B_solar_rad);                                    //970712
   update_value_qualified(est_value,result_quality);                             //150121
   return result_quality;
}
//_2010-12-08___________________________________________________________________
float64 Solar_radiation_with_Donatelli_Campbell_estimation_parameter::compute
() const
{  float64 Tnc = generation_parameters.Tnc;
   float64 Tn = (air_temperature_min.Celcius() + min_temp_adjacent_day) / 2.0;   //110112
   float64 Tx = air_temperature_max.Celcius();
   float64 adjusted_min_temp = exp(Tn / Tnc);                                    //110112
   float64 temperature_difference = Tx - Tn;
   float64 avg_temp = ( Tx + Tn) / 2.0;
   float64 adjusted_avg_temp  = 0.017 * exp(exp(-0.053 * avg_temp));
   float64 fitted_B_solar_rad = generation_parameters.fitted_B;
   float64 act_atmospheric_transmissivity = calc_atmospheric_transmissivity
     (temperature_difference,fitted_B_solar_rad,adjusted_min_temp,adjusted_avg_temp);
   float64 act_solar_rad = pot_solar_rad * act_atmospheric_transmissivity;
   return CORN_must_be_greater_or_equal_to(act_solar_rad,0.8);                   //010609
}
//_2010-12-08__980331__________________________________________________________________
float64 Solar_radiation_with_Campbell_estimation_parameter::estimate_summer_B_solar_rad() const
{  float64 zero_safe_lat_dec_deg = latitude;                                     //150627_981207
   if (zero_safe_lat_dec_deg == 0.0)  zero_safe_lat_dec_deg = 0.0001;            //981207
   return  0.282 * pow(fabs(dec_degrees_to_radians(zero_safe_lat_dec_deg)),-0.431);
}
//_2010-12-08___________________________________________________________________
float64 Solar_radiation_with_Campbell_estimation_parameter::estimate_winter_B_solar_rad() const
{  float64 zero_safe_lat_dec_deg = latitude;                                     //150627_981207
   if (zero_safe_lat_dec_deg == 0.0)  zero_safe_lat_dec_deg = 0.0001;            //981207
   return  0.170 * pow(fabs(dec_degrees_to_radians(zero_safe_lat_dec_deg)),-0.979);
}
//_2010-12-08___________________________________________________________________
bool Solar_radiation_with_Campbell_estimation_parameter::summer_B_period() const
{  CORN::DOY doy = today.get_DOY();
   return (latitude < 0 )
    ? ((doy < 81) || (doy > 265)) // Southern hemisphere
    : ((doy > 81) && (doy < 265)); // Northern hemisphere
}
//_2010-12-08___________________________________________________________________
float64 Solar_radiation_with_Campbell_estimation_parameter::compute // was original_computed_solar_radiation
(float64 day_30_pot_solar_rad
,float64 B_solar_rad)                                                      const
{  float64 simple_atmos_transm =   calc_atmospheric_transmissivity
    (temperature_range,day_30_pot_solar_rad,B_solar_rad);
  return pot_solar_rad * simple_atmos_transm;
}
//_2010-12-08___________________________________________________________________
float64 Solar_radiation_with_Campbell_estimation_parameter::calc_atmospheric_transmissivity
( float64 temperature_range
, float64 day_30_pot_solar_rad
, float64 estimated_B_solar_rad                                                  //970711
, float64 C)                                                               const
{  float64 clear_sky_transm_coef = generation_parameters.clear_sky_transmission_coef;  //091214
   return clear_sky_transm_coef
      * ( 1.0 - exp((-estimated_B_solar_rad * pow((temperature_range),C))
         / day_30_pot_solar_rad));
}
//_2010-12-08___________________________________________________________________
float64 Solar_radiation_with_Donatelli_Campbell_estimation_parameter::calc_atmospheric_transmissivity
( float64 temperature_range
, float64 fitted_B_solar_rad
, float64 adjusted_min_temp
, float64 adjusted_avg_temp) const
{  float64 clear_sky_transm_coef = generation_parameters.clear_sky_transmission_coef;  //091214
   float64 to_power = -fitted_B_solar_rad * adjusted_avg_temp
      * CORN_sqr(temperature_range) * adjusted_min_temp;                         //040106
   float64 atmosph_transm = 0.8;                                                 //040106
   atmosph_transm = clear_sky_transm_coef * ( 1.0 - exp(to_power));
   return atmosph_transm;
}
//_1997-07-11___________________________________________________________________

