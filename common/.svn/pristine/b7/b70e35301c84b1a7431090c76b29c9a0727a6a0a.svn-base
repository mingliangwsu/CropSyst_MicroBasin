#include "common/weather/any_timestep/temperature_est.h"
//______________________________________________________________________________
Temperature_estimator::Temperature_estimator
(Minutes interval_minutes)
: Min_max_to_timestep_estimator(interval_minutes)
, max_yesterday(0.0)
, min_tomorrow(0.0)
{}
//______________________________________________________________________________
float64 Temperature_estimator::estimate_for_interval(float64 twf_i, bool before_5am, bool after_2pm) const
{  float64 Tn = before_5am //   (i < ((float64)intervals / 4.8))        // 5 am    not sure why I had 4.0
              ?  min_today
              : after_2pm //(i > ((float64)intervals / 1.7142857))      // 2:00PM  (14:00)
                ? min_tomorrow
                : min_today;
   float64 Tx = before_5am // (i < ((float64)intervals / 4.8))      // 5 am   not sure why I had 4.0
              ?  max_yesterday
              : after_2pm // (i > ((float64)intervals / 1.7142857))
                ? get_max_today()     // For stress adjusted temperature for thermal time
                : get_max_today() ;   // Tmax_today is adjusted based on VPD and stress
   float64 temperature_i = twf_i * Tx + (1.0 - twf_i) * Tn ;

//std::clog << "twf=" << twf_i << " tn=" << Tn << " tx=" << Tx << std::endl;

   return temperature_i;
}
//______________________________________________________________________________
void Temperature_estimator::set_max_today_min_tomorrow(float64 max_today_new, float64 min_tomorrow_new)
{  max_yesterday = max_today;
   min_today = min_tomorrow;
   max_today = max_today_new;
   min_tomorrow = min_tomorrow_new;
}
//______________________________________________________________________________
void Temperature_estimator::reset
(float64 _max_today
,float64 _max_yesterday
,float64 _min_today
,float64 _min_tomorrow)
{  max_today      = _max_today;
   max_yesterday  = _max_yesterday;
   min_today      = _min_today;
   min_tomorrow   = _min_tomorrow;
}
//______________________________________________________________________________



