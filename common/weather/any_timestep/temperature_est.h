#ifndef temperature_estH
#define temperature_estH
#  include "common/weather/any_timestep/min_max_to_timestep_estimator.h"
using namespace CORN;
//______________________________________________________________________________
class Temperature_estimator
: public Min_max_to_timestep_estimator
{
private:
   float64 min_tomorrow;
   float64 max_yesterday;
public:
   virtual void set_max_today_min_tomorrow(float64 max_today, float64 min_tomorrow);
   virtual void reset(float64 max_today,float64 max_yesterday,float64 min_today, float64 min_tomorrow);
protected:
   virtual float64 estimate_for_interval(float64 twf_i, bool before_5am, bool after_2pm) const;
public:
   Temperature_estimator(Minutes interval_minutes);
   inline virtual void get_temperature_by_interval
      (Dynamic_array<float32> &temperature_X_minute)
      {  get_by_interval(temperature_X_minute); }
   // <- Returned.
};
//______________________________________________________________________________
#endif

