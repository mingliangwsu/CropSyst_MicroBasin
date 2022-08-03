#ifndef date_typesHH
#define date_typesHH
#ifndef __cplusplus
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#endif

#ifdef __GNUC__
#  define OPTIONAL_DATE 0
#else
#  define OPTIONAL_DATE 0L
#endif

//170815typedef int32 Date32;
typedef int32 date32;                                                            //170815
typedef int16 Year;    // Year must not be signed!
typedef nat16 DOY;     /* Day Of Year*/
typedef nat8  Month;
typedef nat8  DOM;     /* Day Of Month */
typedef nat8  DOW;     /* Day of Week */
typedef nat8  Week;    /* week in the year */

//170815 typedef float64 Datetime64;                                                      //050724
typedef float64 datetime64;                                                      //170815

#define CORN_date_get_doy(date32) (date32 % 1000)

#endif
