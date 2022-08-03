#ifndef stormgenH
#define stormgenH
#include "CS_suite/simulation/CS_simulation_element.h"
#include "common/weather/parameter/WP_precipitation.h"
#include "corn/chronometry/time_conversion.h"
//170525#include "corn/datetime/time.h"
#include "corn/dynamic_array/dynamic_array_T.h"
namespace CS
{
namespace meteorology
{
//______________________________________________________________________________
class Storm_generator
: public extends_ CS::Simulation_element_abstract

// This would probably be more accurately names storm Energy

{private:
   float64 alpha0_5;   // 0.0208-1.0
   float64 peak_precip_intensity_mm;   // actually mm/hour or mm/halfhour (need to check 160512)
   const float32 *mean_peak_rainfall_fract;                                      //090303
      // For each month 13 element array index 0 not used
 protected:
   const Precipitation &precipitation; // reference to weather
 private:
   float64 calc_event_peak_precip_intensity()                      calculation_;
   float64 calc_duration()                                         calculation_;
      // The alpha associated with the precip intensity
   float64 calc_storm_energy()                                     calculation_; //990318
   nat16   get_peak_interval(nat16 intervals)                             const; //140602
   float64 triangular_random_sample(float64 mean_peak_rainfall_month_fract)const;//990219
 public:
   Storm_generator
      (const CORN::date32  &today
      ,const Precipitation &precipitation
      ,const float32        mean_peak_rainfall[]);                               //090303
   inline virtual ~Storm_generator() {}                                          //151015
 public: // Simulation element implementations
   virtual bool start_day()                                       modification_; //151015
   inline virtual bool   has_event_today()                         affirmation_  //160506
      { return precipitation.get_mm() > 0.00001; }
 public: // accessors

   float64 get_storm_energy            ()                                 const; //140217_000615
   float64 get_peak_precip_intensity_mm()                                 const; //140602_140217_0000615
   virtual float64 get_precipitation_mm_by_interval
      (bool                          generate_intensity
      ,CORN::Minutes                 interval_minutes
      ,CORN::Time                   &event_start_time // time the event starts is generated. //990505
      ,CORN::Dynamic_array<float32> &precip_X_minute)                     const; //0000615
      // precip_X_minute returned

   // This function generates a precipitation period for the specified date.
   // The length of each interval can be specified in minutes
   // (I.e.  30 minute intervals will return a precip_X_minute array with 48 intervals)
   // The function returns the total precipitation for the day
   // precip_X_minute.count() will have the number of intervals containing precip.

   // For generated data, the precip always starts are hour 0 (midnight).
   // For read data the precip may start at any time of the day.
   // precip_X_minute array may be 0 to 48 intervals
   // but will not exceed the number of intervals from the event start time to the end of the day.
   // Although real storm events may cross the midnight hour to a second (or more days)
   // they are treated a descrete events because the generation is
   // based on the daily value.
};
//______________________________________________________________________________
} } // namespace CS:: meteorology
#endif
//stormgen.h

