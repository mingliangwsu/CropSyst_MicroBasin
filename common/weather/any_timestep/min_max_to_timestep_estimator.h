#ifndef min_max_to_timestep_estimatorH
#define min_max_to_timestep_estimatorH

#ifndef time_typesHPP
#  include "corn/chronometry/time_types.hpp"
#endif
#ifndef dynamic_array_TH
#  include "corn/dynamic_array/dynamic_array_T.h"
//#  define Dynamic_float_array Dynamic_array<float32>
#endif
using namespace CORN;
//______________________________________________________________________________
class Min_max_to_timestep_estimator
{
protected:
   int   intervals; // must preceed twf because twf size is allocated from intervals!
   int   interval_5am;
   int   interval_2pm;
protected:
   float64 max_today;
   float64 min_today;
//   Dynamic_float_array  twf; // This only needs to be computed once
   Dynamic_array<float32>twf;
public:
   Min_max_to_timestep_estimator(Minutes interval_minutes);
   inline virtual ~Min_max_to_timestep_estimator() {}                            //170531
   virtual bool get_by_interval(Dynamic_array<float32> &value_by_X_minute) const; // <- Returned.
protected:
   inline virtual float64 get_max_today()                                  const { return max_today;}
   // CropSyst thermal time with hourly resolution overrides this
   // to get and adjusted plant temperature
   virtual float64 estimate_for_interval(float64 twf_i, bool before_5am, bool after_2pm) const = 0;
public:
   inline int get_intervals()                                              const {return intervals; }
};
//______________________________________________________________________________
#endif

