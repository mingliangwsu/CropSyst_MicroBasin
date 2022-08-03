#ifndef WP_wind_speedH
#define WP_wind_speedH
#include "common/CS_parameter_float64.h"
#include "corn/measure/measures.h"
#include "corn/chronometry/time_types.hpp"
#define measurement_height_wind_speed_standard_agronomic_m 2.0
//______________________________________________________________________________
class Wind_speed
: public extends_ CS::Parameter_float64
{  // Also know as wind velocity and wind run
 public:
 private:
   float32 reference_height_m;                                                   //150427
      // also called screening height
 public:
   inline Wind_speed(float32 reference_height_m_)                                //150427
      : CS::Parameter_float64
         (INTENSIVE,0.0,UC_meters_per_second,CORN::unknown_quality)
      , reference_height_m(reference_height_m_)                                  //150427
      {}
   inline Wind_speed()
      : CS::Parameter_float64
         (INTENSIVE,0.0,UC_meters_per_second,CORN::unknown_quality)
      , reference_height_m(measurement_height_wind_speed_standard_agronomic_m)   //150427
      {}
   inline float64 get_m_s()  const { return in_prescribed_units();}
   inline float64 get_m_d()  const { return m_per_sec_to_m_per_day(get_m_s());}
   inline float64 get_km_d() const { return m_to_km(get_m_d()); }
   inline float64 set_m_s(float64 value_m_s     ,const CORN::Quality &_quality)   { assume(_quality);      return force_amount(value_m_s); }
   inline float64 set_m_d(float64 value_m_d     ,const CORN::Quality &_quality)   { return set_m_s(m_per_day_to_m_per_sec(value_m_d),_quality); }
   inline float64 set_km_d(float64 value_km_d   ,const CORN::Quality &_quality)   { return set_m_s(km_per_day_to_m_per_sec(value_km_d),_quality); } //140627
   inline float64 set_m_s(float64 value_m_s     ,CORN::Quality_code _quality)     { assume_code(_quality); return force_amount(value_m_s); }
   inline float64 set_m_d(float64 value_m_d     ,CORN::Quality_code _quality)     { return set_m_s(m_per_day_to_m_per_sec(value_m_d),_quality); }
   inline float64 set_km_d(float64 value_km_d   ,CORN::Quality_code _quality)     { return set_m_s(km_per_day_to_m_per_sec(value_km_d),_quality); } //140627

   float64 calc_normalized(float64 wind_speed_m_ts)                        const;//150426
   float64 normalized_m_per_timestep(CORN::Seconds time_step)              const;//150531
   float64 get_at_height_m_per_s(float64 height)                           const;//151014BRC
   inline float64 get_reference_height_m()                                 const { return (float64)reference_height_m;}
};
//______________________________________________________________________________
#endif

