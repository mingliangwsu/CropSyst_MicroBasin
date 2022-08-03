#  include "UED/library/UED.h"
#  include "UED/library/std_codes.h"
#  include "common/weather/wthrbase.h"
#  include "common/weather/database/weather_database.h"
#  include "common/weather/loc_param.h"
#  include "common/weather/any_timestep/min_max_to_timestep_estimator.h"
#  include "common/weather/atmospheric_CO2_change.h"

#  ifndef compareHPP
#     include "corn/math/compare.hpp"
#  endif

#ifdef WEATHER_GENERATION
#include "ClimGen/source/ClimGenF.h"
#endif

#include <assert.h>
#ifdef DETAIL_TRACE
#include <fstream>
using namespace std;
extern int trace_indent;
extern std::ofstream trace;
bool dump_it = true;
#endif

#define get_now() today
//150125 eventually replace get_now() with today
// get_now was when Sun was the temporal driver
//______________________________________________________________________________
Weather_base::Weather_base
(Weather_database    *weather_database_                                          //050307
,modifiable_ Weather_provider &provider_                                         //151201
,const CORN::Date_const &today_                                                  //150125
,const Geocoordinate &geocoordinate_                                             //150629
,float64              screening_height                                           //151128
,bool                 treat_valid_data_as_real_                                  //081108
,bool                 read_only_                                                 //000711
,CORN::Seconds)      /*unused time_step_seconds may be used in derived classes need to check*/ // 000711
: Weather_interface()                                                            //151027
,CS::Weather_subdaily                                                            //151212
   (*this //weather_database_
   ,today_
   ,provider_.air_temperature_max
   ,provider_.air_temperature_min
   ,provider_.relative_humidity_max
   ,provider_.relative_humidity_min
   )
#if ((CS_VERSION>=1) && (CS_VERSION<=4))
,Wind(provider_.wind_speed,2.0)                                                  //151202_150209
#endif
,CS::Seasons
   (today_
   ,(geocoordinate_.get_latitude_dec_deg() < 0)                                  //150629
   )
,provider(provider_)                                                             //151201
,database_read_only        (read_only_)                                          //010726
,treat_valid_data_as_real  (treat_valid_data_as_real_)                           //081109
,geocoordinate             (geocoordinate_)                                      //151027
,weather_data              (weather_database_)                                   //050307
,avg_DOY_with_min_annual_temperature(15)                                         //060427
,updated_for_year          (0)                                                   //130515
,annual_temperature_avg    (0)                                                   //130515

,ClimGen_parameters(0)                                                           //091214
{
   //010726			get_end() will be called after we load the location parameters
   //					but I now also allow a default location with default weather
   //					parameters but with a weather filename (specified in constructor)
   //					so call get_end() now to load that weather database with
   //					simple snow pack model.
}
//_1999-03-01___________________________________________________________________
Weather_base::~Weather_base()
{  // We can't delete the abstract class, it doesn't call the virtual destructor!
   weather_data = 0; // just a reference pointer, don't delete                   //041130
}
//_2000-07-10___________________________________________________________________
bool Weather_base::done_with_dates_before(const CORN::Date_const &earliest_date) const
{  return weather_data->done_with_dates_before(earliest_date);
}
//_2014-11-03___________________________________________________________________
#if (CS_VERSION < 5)
const Location_parameters *Weather_base::get_location_parameters()         const //090303
{  return weather_data->get_location_parameters();}
#endif
//_2005-07-13___________________________________________________________________
const Geolocation         *Weather_base::get_geolocation_constant()        const
{return weather_data->get_geolocation_constant();}                               //050713
//_2005-05-25___________________________________________________________________
const CORN::Quality &Weather_base::load_wind_speed_estimate_if_necessary
(Wind_speed &wind_speed,const Date_const *_date)
{
//160706 #ifdef WEATHER_PROVIDER_VERSION
   assert(false); // NYI
/*
#else
   if (_date.get() == 0) _date.set(today.get_date32());
   float64 WS_m_s = load_wind_speed(wind_speed,_date);
   if (WS_m_s < 0.00001) wind_speed.invalidate();
   if (!wind_speed.is_valid())
   {
      float64 WS_m_d = forecast_wind_speed_m_d(_date.get_DOY());
      wind_speed.set_m_d(WS_m_d,quality_forecasted_from(CORN::estimated_quality));//150811
      // Note that forcasted from is worse quality generated
      // This will allow ClimGen's generated wind speed to
      // override this forecast from seasonal conditions
   }
#endif
*/
   return wind_speed;
}
//_2015-01-26__1997-03-03_______________load_wind_speed_estimate_if_necessary__/
float64 Weather_base::forecast_wind_speed_m_d(CORN::DOY doy)
{  float64 result = 0.0;
   const Location_parameters *location= weather_data->get_location_parameters(); //090303
   switch (location?location->wind_speed_classification_labeled.get():WIND_SPEED_MEDIUM )
   {  case WIND_SPEED_UNKNOWN    : result = 0.0; break;                          //091217
      case WIND_SPEED_VERY_LOW   : result = 1.0; break; // m/s                   //980311
      case WIND_SPEED_LOW        : result = 2.0; break; // m/s                   //980311
      case WIND_SPEED_MEDIUM     : result = 3.0; break; // m/s                   //980311
      case WIND_SPEED_MEDIUM_HIGH: result = 4.0; break; // m/s                   //980311
      case WIND_SPEED_HIGH       : result = 6.0; break; // m/s                   //980311
      case WIND_SPEED_VERY_HIGH  : result = 8.0; break; // m/s                   //980311
      case WIND_SPEED_SPECIFIED  :
         {  // Don't need to check location exists here (done above)
             result =
               is_spring_or_summer_time(doy)                                     //140813
               ? location->get_wind_speed_spring_summer_ms() // m/s
               : location->get_wind_speed_fall_winter_ms() ; // m/s
         } break;
   }
   result *= seconds_per_day;  // convert m/s -> m/d
   result = CORN::must_be_greater_or_equal_to<float64>(result,0.0001);           //980710
   return result;
}
//_1997-03-03___________________________________________________________________
const char *Weather_base::get_description(std::string &return_buffer)    const
{ return weather_data->get_description(return_buffer); }                         //050525
//_2004-11-09_________________________________________________get_description__/
void Weather_base::load()
{
   // load the data for the time step

   weather_data->get_to(provider);
   if (treat_valid_data_as_real)                                                 //081109
   {
      // Now using assume quality because we don't want to mark
      // the property as modified, otherwise a new record may be instanciated    //141101

      if (provider.precipitation_actual   .get_quality().is_valid()) provider.precipitation_actual .assume_code(measured_quality);
      if (provider.solar_radiation        .get_quality().is_valid()) provider.solar_radiation      .assume_code(measured_quality);  //081109
      if (provider.wind_speed             .get_quality().is_valid()) provider.wind_speed           .assume_code(measured_quality);  //081109
      if (curr_max_temperature            .get_quality().is_valid()) curr_max_temperature          .assume_code(measured_quality);  //081109
      if (curr_min_temperature            .get_quality().is_valid()) curr_min_temperature          .assume_code(measured_quality);  //081109
      if (curr_max_dew_point_temperature  .get_quality().is_valid()) curr_max_dew_point_temperature.assume_code(measured_quality);  //081109
      if (curr_min_dew_point_temperature  .get_quality().is_valid()) curr_min_dew_point_temperature.assume_code(measured_quality);  //081109
      if (curr_avg_dew_point_temperature  .get_quality().is_valid()) curr_avg_dew_point_temperature.assume_code(measured_quality);  //081109
      if (curr_max_relative_humidity      .get_quality().is_valid()) curr_max_relative_humidity    .assume_code(measured_quality);  //081109
      if (curr_min_relative_humidity      .get_quality().is_valid()) curr_min_relative_humidity    .assume_code(measured_quality);  //081109
      if (provider.ET_reference           .get_quality().is_valid()) provider.ET_reference         .assume_code(measured_quality);  //180806
   }
}
//_load________________________________________________________________________/
bool Weather_base::start_day()
{  bool started = true;                                                          //150126
   load();
   started &= update();                                                          //150126
   started &= CS::Weather_subdaily::start_day(); // do last because needs loaded weather
   return started;                                                               //150125_140709
}
//_start_day________________________________________________________2009-12-16_/
bool Weather_base::update()                       /* should be  rectification_*/ //151212
{  bool updated = true;

   // Probably should call sky.update() here, but need to check
   // if where I have it now is needed there.

//050604       curr_max_vapor_pressure_deficit requires dewpt and rel humidity
//             see if we can get atleast estimated values
   //   curr_max_relative_humidity and curr_min_dew_point_temperature now both can be calculated
   //   from VPD_max (aridity factor) and Tmax I am updating curr_max_vapor_pressure_deficit_kPa first
   //   so it will be ready for use by curr_max_relative_humidity and  curr_min_relative_humidity.
   //  This is kind of a hack doing this here, I should use a provide idiom.      081016

//TRACE trace << get_now().get_year() << ' ' << doy ;
//TRACE trace << "\t Tmax = " << get_curr_max_temperature();
//TRACE trace << "\t Tmin = " << get_curr_min_temperature();
//TRACE trace << endl;

//if (dump_it)
//{
//dump  <<  get_now().get_year() << ' ' << doy << '\t' << get_curr_max_temperature() << '\t' << get_curr_min_temperature();
//}

   //151202 curr_vapor_pressure_nighttime.know_DOY_unused(doy);                  //081030
   // Update minimum relative humidity first because
   // it has the most stable estimation
   // and we need it first if we need to use the regression parameters
   // to produce vapor_pressure_minimum.

   season_S_S_F_W=(Season_S_S_F_W)get_season_S_S_F_W();                          //050801

   #if ((CS_VERSION>=1) && (CS_VERSION<=4))
      Wind::update_aerodynamic_resistance();
   #endif

   provider.aerodynamics.update();                                               //110104
   updated &= CS::Weather_subdaily::update();                                    //151212
   return updated;                                                               //140709
}
//_update___________________________________________________________1999-10-08_/

//          In the following load methods, the quality request will be any valid quality
//          The load with return the actual quality

bool Weather_base::load_weather_provider(Weather_provider &weather_provider) mutation_
{  return weather_data->get_to(weather_provider);

   //110910 Note probably should set up treat_valid_data_as_real
   // as in load(), but this wasn't previously done,
   // so carefully check where needed
   // for example, see where Daily::get_solar_radiation(const CORN::Date  & _date)
   // is used

}
//_load_weather_provider____________________________________________2011-09-10_/
void Weather_base::commit( const Date_const &now)
{  // Save any modifications (Call this before advancing to the next timestep).
   if (curr_max_temperature.is_modified()
   ||curr_min_temperature.is_modified()
   ||curr_max_relative_humidity.is_modified()
   ||curr_min_relative_humidity.is_modified()
   ||curr_max_dew_point_temperature.is_modified()
   ||curr_min_dew_point_temperature.is_modified())
      weather_data->set_from(provider);
}
//_2005-06-16___________________________________________________________________
void Weather_base::fix_up_relative_humidity()
{  //CORN::Quality_clad curr_max_relative_humidity_quality(curr_max_relative_humidity.get_quality());
   float32 max_rel_humid = curr_max_relative_humidity.percent();
   //CORN::Quality_clad curr_min_relative_humidity_quality(curr_min_relative_humidity.get_quality());
   float32 min_rel_humid = curr_min_relative_humidity.percent();
   if (max_rel_humid < min_rel_humid)
   {
      float32 hold =  min_rel_humid;
      min_rel_humid = max_rel_humid;
      max_rel_humid = hold;
      curr_max_relative_humidity.force_amount(max_rel_humid);
      curr_min_relative_humidity.force_amount(min_rel_humid);
   }
}
//______________________________________________________________________________
bool Weather_base::any_valid_data_today()
{  return
      get_precipitation_quality()            .is_valid()
   || get_max_temperature_quality()          .is_valid()
   || get_min_temperature_quality()          .is_valid()
   || curr_solar_radiation                   .is_valid()                         //140715
   || get_max_dew_point_temperature_quality().is_valid()
   || get_min_dew_point_temperature_quality().is_valid()
   || get_max_relative_humidity_quality()    .is_valid()
   || get_min_relative_humidity_quality()    .is_valid();
}
//_any_valid_data_today_______________________________________________________/
float64 Weather_base::get_curr_max_air_temperature()                       const
{return curr_max_temperature;}     //LML 140916
//______________________________________________________________________________
float64 Weather_base::get_air_temperature_min_tomorrow()                   const
{  return Tmin_tomorrow;
}
//_2015-12-01___________________________________________________________________
float64 Weather_base::get_air_temperature_max_yesterday()                  const
{  return Tmax_yesterday;
}
//_2015-12-01___________________________________________________________________
#ifdef WEATHER_GENERATION
void Weather_base::know_generation_parameters
(const ClimGen_Parameters &ClimGen_parameters_)                    contribution_
{  ClimGen_parameters = &ClimGen_parameters_;
   curr_vapor_pressure_nighttime  .know_generation_parameters(ClimGen_parameters_.vapor_pressure_nighttime_parameters);
   curr_max_vapor_pressure_deficit.know_generation_parameters(ClimGen_parameters_.VPD_parameters);
   curr_max_relative_humidity     .know_generation_parameters(ClimGen_parameters_.relative_humidity_extremes,season_for_dew_point);
   curr_min_relative_humidity     .know_generation_parameters(ClimGen_parameters_.relative_humidity_extremes,season_for_dew_point);
}
//_2009-12-14___________________________________________________________________
#endif
//______________________________________________________________________________
CORN::date32 Weather_base::get_earliest_available_date()                   const //150209
{  return weather_data->get_earliest_available_date();
}
//_2014-02-09___________________________________________________________________
//#ifdef WEATHER_PROVIDER_VERSION
// Actually this can be all versions
bool Weather_base::get_parameter_on
(modifiable_ CS::Parameter  &property
,nat32                       variable_code // Typically the variable code will be UED variable code
,const CORN::Date_const     &on_date)                             rectification_
{
   return weather_data->get_parameter_on(property,variable_code,on_date);
}
//_2015-11-22___________________________________________________________________
/*151122 conceptual
bool Weather_base::setup_property_reference
(Physical::Property_cowl  &property
,nat32                     variable_code // Typically the variable code will be UED variable code
,const CORN::Date         &on_date)                               rectification_
{
   return weather_data->setup_property_reference(property,variable_code,on_date);
}
*/
//_2015-11-19___________________________________________________________________*

//#endif

//060613 1157 lines
//090707  973 lines

