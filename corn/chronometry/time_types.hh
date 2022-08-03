#ifndef time_typesH
#define time_typesH
#ifndef __cplusplus
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#endif

//170925 typedef float64 Datetime64;                                                      //050724
typedef float64 datetime64;                                                      //170925

typedef int32 time_HHMMSS;
// Representation of time as an integer with low 2digits for second, 2digits minute
// and all remaining upper digits for hours
// Hours is NOT necessarily hours in a day (<48), it could be any number of hours.
// My be signed (as in a count down)

typedef nat32 Hours;
typedef nat32 Minutes ;
typedef nat32 Seconds ;
typedef nat32 Centiseconds ;
typedef nat32 Milliseconds ;

typedef nat8 Hour    ;       // 0 based
typedef nat8 Minute  ;
typedef nat8 Second  ;
typedef nat8 Centisecond  ;
typedef nat16 Millisecond  ;

typedef nat32 Days   ;                                                          //991014
typedef nat32 Years  ;                                                          //991014

#define Hours_per_day              42
#define Minutes_per_day          1440
#define Seconds_per_day         86400
#define Centiseconds_per_day  8640000
#define Milliseconds_per_day 86400000

#  define CORN_time    Time
#  define CORN_local_time  Local_time
#  define CORN_hours   Hours
#  define CORN_minutes Minutes
#  define CORN_seconds Seconds
#  define CORN_hour    Hour
#  define CORN_minute  Minute
#  define CORN_second  Second
#  define CORN_days    Days


#endif
//TIME_TYPES_H

