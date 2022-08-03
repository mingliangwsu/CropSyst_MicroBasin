#  include <math.h>
#  include "corn/math/moremath.h"
#  include "corn/measure/measures.h"
#  include "common/weather/any_timestep/min_max_to_timestep_estimator.h"

#define Xminutes_per_day 1440
//______________________________________________________________________________
Min_max_to_timestep_estimator::Min_max_to_timestep_estimator
(Minutes interval_minutes)
: intervals(Xminutes_per_day / interval_minutes)
, twf(intervals+1,24,0.0)
, max_today(0.0)
, min_today(0.0)
{
/*this is wrong
   interval_5am = ((float64)intervals / 4.8 );
   interval_2pm = ((float64)intervals / 1.7142857);
*/
   float64 intervals_per_hour = intervals/24 / (interval_minutes/60);            //150618
   interval_5am = intervals_per_hour * 4 + 1;                                    //150618
   interval_2pm = intervals_per_hour * 13+ 1;                                    //150618
   // The original code as 1 based index, I have preserved that
   for (int i = 1; i <= intervals; i++)
   {  float32 twf_i =  0.44 - 0.46 * sin(i * CORN_pi / (intervals/2) + 0.9) + 0.11 * sin(2.0 * i * CORN_pi / (intervals/2) + 0.9);
      twf.set(i,twf_i);
   }
}
//______________________________________________________________________________
bool Min_max_to_timestep_estimator::get_by_interval
(Dynamic_array<float32> &value_by_X_minute)  const// <- Returned (0 indexed)
{
   for (int i = 1; i <= intervals; i++)
   {  // The original code as 1 based index, I have preserved that
      bool before_5am = i <= interval_5am;
      bool after_2pm  = i > interval_2pm;
      float32 twf_i = twf.get(i);
      float32 value_i = estimate_for_interval(twf_i,before_5am,after_2pm);
      value_by_X_minute.set(i-1,value_i);
      // We return 0 indexed array (This is different from the original V.B. code. which was 1 based index.
   }
   return true;                                                                  //140715
}
//______________________________________________________________________________

