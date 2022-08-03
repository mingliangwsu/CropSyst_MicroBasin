#include "common/weather/any_timestep/relhumid_est.h"
//______________________________________________________________________________
Relative_humidity_estimator::Relative_humidity_estimator
(Minutes interval_minutes)
: Min_max_to_timestep_estimator(interval_minutes)
, min_yesterday(0.0)
, max_tomorrow(0.0)
{}
//______________________________________________________________________________
float64 Relative_humidity_estimator::estimate_for_interval(float64 twf_i, bool before_5am, bool after_2pm) const
{  float64 RH_min = before_5am        // 5 am    not sure why I had 4.0
                 ?  min_yesterday
                 : after_2pm      // 2:00PM  (14:00)
                   ? min_today
                   : min_today;
   float64 RH_max = before_5am      // 5 am   not sure why I had 4.0
                 ?  max_today
                 : after_2pm
                   ? max_tomorrow     // For stress adjusted temperature for thermal time
                   : max_today ;   // Tmax_today is adjusted based on VPD and stress
   float64 RH_i = twf_i * RH_min + (1.0 - twf_i) * RH_max ;
   return RH_i;
}
//______________________________________________________________________________
void Relative_humidity_estimator::set_min_today_max_tomorrow(float64 _min_today,float64 _max_tomorrow)
{  min_yesterday  = min_today;
   min_today      = _min_today;
   max_today      =  max_tomorrow;
   max_tomorrow   = _max_tomorrow;
}
//______________________________________________________________________________
void Relative_humidity_estimator::reset
(float64 _max_today
,float64 _max_tomorrow
,float64 _min_today
,float64 _min_yesterday)
{  max_today      = _max_today;
   max_tomorrow   = _max_tomorrow;
   min_today      = _min_today;
   min_yesterday  = _min_yesterday;
}
//______________________________________________________________________________

