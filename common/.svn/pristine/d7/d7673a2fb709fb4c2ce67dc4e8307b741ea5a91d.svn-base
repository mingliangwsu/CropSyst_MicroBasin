#ifndef evaporatorH
#define evaporatorH

#include "common/physics/water_depth.h"
#include "corn/chronometry/time_types.hpp"
#include "CS_suite/observation/CS_observation.h"
#include "corn/dynamic_array/dynamic_array_T.h"
namespace CS
{  class Weather_hours;
}
//______________________________________________________________________________
namespace CS   // May want to be CS namespace because Residues would be CS
{
//______________________________________________________________________________
class Evaporator_intervals
{
 protected: // references to other objects
   modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining;
 protected:
   CORN::Dynamic_array<float64> evaporation_actual;         // m
   CORN::Dynamic_array<float64> evaporation_potential;      // m
 public: // only for output! Do not uses these for calculation!
   float64 output_evaporation_potential_daily;
   float64 output_evaporation_actual_daily;
 public:
   Evaporator_intervals
      (modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining);
   inline virtual ~Evaporator_intervals() {}                                     //170217
 public: // CS::Simulation_element implementations
   virtual bool start_day()                                        modification_;
   virtual bool end_day()                                          modification_;
 public:
   inline virtual bool is_hourly_enabled()                          affirmation_
      { return evaporation_potential_remaining.get_count() == 24; }
      //160717 {return weather_hourly != 0; }
   inline virtual bool is_daily_enabled()                           affirmation_
      { return evaporation_potential_remaining.get_count() == 1; }
   inline virtual float64 get_evaporation_actual_day()                     const
      { return evaporation_actual.sum(); }
   inline virtual float64 get_evaporation_potential_day()                  const
      { return evaporation_potential.sum(); }
   inline float64 get_output_evaporation_potential_daily()                 const
      { return output_evaporation_potential_daily; }
   inline float64 get_output_evaporation_actual_daily()                    const
      { return output_evaporation_actual_daily; }
   inline virtual float64 get_evaporation_actual_hour(CORN::Hour hour)     const
      { return evaporation_actual.get(hour); }
 public:
   virtual float64 evaporate_interval(nat8 interval)               modification_;
   inline virtual float64 evaporate_day()                          modification_
      { return evaporate_interval(0); }
   inline virtual float64 evaporate_hour(CORN::Hour hour)          modification_
      { return evaporate_interval(hour); }
 public: // inspection
   RENDER_INSPECTORS_DECLARATION;
};
//_2016-07-18___________________________________________________________________
} // namespace CS
#endif

