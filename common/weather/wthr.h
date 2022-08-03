#ifndef wthrH
#define wthrH
/*
  This class is based on weather_file class.

  This class will try to provide actual weather data from the weather file,
  but if the data is not available, it will try to provide an estimated value.

  The Weather class can use either  .DAT (real weather) or
   .GEN (generated weather) data files.

   If a .GEN and a .DAT weather files for the same year exist in
   the same directory, .DAT is always used.


   The weather class can be used in an iterative mode.
   In this mode, date is the current date.
   start() should be used to begin the iterative mode on a specific
   date, otherwise it is started on Jan. 1 of the first year of
   .GEN or .DAT weather file data.
*/

#include "common/weather/daily.h"
#include "UED/library/timeqry.h"
#include "corn/dynamic_array/dynamic_array_T.h"
#define Dynamic_float_array Dynamic_array<float32>

#define WEATHER_GENERATION
#ifdef FOR_CAFE_DAIRY
#undef WEATHER_GENERATION
#endif
#if (defined(linux) || defined(__GNUC__))
//LML 150309 added "__GNUC__"
#undef WEATHER_GENERATION
#endif
#ifndef OFOOT_VERSION
#undef WEATHER_GENERATION
#endif

class Vapor_pressure;                                                            //041104
struct Solar_radiation_parameters;                                               //091214
//______________________________________________________________________________
class Weather_with_solar_rad_estimation
: public Weather_daily_deprecated                                                //991007
{
   friend class Vapor_pressure;                                                  //041105
 public:
   void check_solar_rad(); // for debugging
   // This is special for CropSyst
   contribute_ const Solar_radiation_parameters *generation_parameters;          //091214
 public:
   Weather_with_solar_rad_estimation                                             //990301
      (Weather_database    *weather_database_                                    //050307
      ,modifiable_ Weather_provider &provider_                                   //151201
      ,const Geocoordinate &geocoordinate_                                       //150630
      ,float64              screening_height_                                    //151128
      ,const CORN::Date_const &today_                                            //150125
#ifdef LOC_ONLY_FOR_GEN
      ,Location_parameters *location_for_generation)                             //070314
#endif
      ,bool treat_valid_data_as_real                                             //081109
      ,bool read_only = false);                                                  //000711
   inline virtual ~Weather_with_solar_rad_estimation() {}                        //151204
#ifdef WEATHER_GENERATION
   virtual void know_generation_parameters(const ClimGen_Parameters  &_ClimGen_parameters) contribution_;   //091214
      // Optional used for generation
   // The following are iterative mode functions:
#endif

// The following are only for the current date when using iterative mode.
 public: // The following accessors get the weather data returning the quality
   virtual void set_precipitation_intervals_mm                                   //*990425
      (const CORN::Date_const &date
      ,const CORN::Time &time                                                    //990505
      ,const Dynamic_float_array &precip_in_intervals
      ,CORN::Minutes interval_time_minutes                                       //990425
      ,CORN::Quality & attribute);
   virtual void set_temperature_intervals                                        //021124
      (const CORN::Date_const &date                                              //021124
      ,const Dynamic_float_array &temperature_in_intervals                       //021124
      ,CORN::Minutes interval_time_minutes                                       //021124
      ,CORN::Quality &attribute);
 public:  // The following give information about available weather files
   float64 delta_emissivity()                                              const;//990202
   float64 original_computed_solar_radiation                                     //970712
      (float64 temperature_range
      ,float64 pot_solar_rad
      ,float64 day_30_pot_solar_rad
      ,float64 B_solar_rad)                                                const;
   float64 donatelli_campbell_computed_solar_radiation                           //970712
      (float64 temperature_range,float64 pot_solar_rad)                    const;
   float64 simple_atmospheric_transmissivity
      ( float64 temperature_range
      , float64 day_30_pot_solar_rad
      , float64 B_solar_rad
      , float64 C = 2.0)                                                   const;
   float64 donatelli_atmospheric_transmissivity                                  //970711
      ( float64 temperature_range
      , float64 fitted_B_solar_rad
      , float64 adjusted_min_temp // fTnc
      , float64 adjusted_avg_temp /* faTvg */ )                            const;
};
//______________________________________________________________________________
#endif

