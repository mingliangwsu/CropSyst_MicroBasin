#error obsolete This has been replaced by CS::Weather::Storms

#ifndef stormH
#define stormH
#include "common/weather/stormgen.h"
#include "UED/library/UED_fname.h"
// When using numerical runoff model with 30 rainfall intensity option enabled,
// CropSyst will perform infiltation in 30 minute intervals, this requires
// 30minute storm data.
// The storm data can either be prepared in a UED database, or generated at run time.

// Forward declarations

namespace UED
{  class Database_file_indexed;
}
//______________________________________________________________________________
class Storm_database_or_generator
: public Storm_generator
{  UED::Database_file_indexed* storm_database;
   bool                        can_generate_storms;
   Weather_base&               daily_weather;
 public:
   Storm_database_or_generator
      (const UED_File_name &  storm_database_filename                            //990830
      ,Weather_daily &        daily_weather);
   virtual ~Storm_database_or_generator();                                       //030107
   virtual float64 get_eff_precipitation_mm_by_interval
      (bool          generate_intensity
      ,Minutes       interval_minutes
      ,Minutes       default_event_duration_minutes                              //080801
      ,CORN::Time &  event_start_time   // time the event starts is generated.   //990505
      ,Dynamic_float_array &precip_X_minute // <- returned
      ,const CORN::Date &_date);                                                 //030103
   inline bool good() const                                                      //990527
   {  // if not storm database and no daily then we distributes
      return can_generate_storms || storm_database;                              //000303
   }
};
//_1999-04-28___________________________________________________________________
#endif
//storm.h

