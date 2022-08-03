#ifndef relhumid_estH
#define relhumid_estH
#  include "common/weather/any_timestep/min_max_to_timestep_estimator.h"
using namespace CORN;
//______________________________________________________________________________
class Relative_humidity_estimator
: public Min_max_to_timestep_estimator
{
private:
   float64 min_yesterday;
   float64 max_tomorrow;
protected:
   virtual float64 estimate_for_interval(float64 twf_i,bool before_5am, bool after_2pm) const;
public:
   Relative_humidity_estimator(Minutes interval_minutes);
   void set_min_today_max_tomorrow(float64 _min_today,float64 _max_tomorrow);
   virtual void reset(float64 max_today,float64 max_yesterday,float64 min_today, float64 min_tomorrow);
};
//______________________________________________________________________________
#endif

