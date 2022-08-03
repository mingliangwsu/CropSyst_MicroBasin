#ifndef date_typesHPP
#define date_typesHPP

#ifndef primitiveH
#   include "corn/primitive.h"
#endif


namespace CORN {

/*170430 moved to date_types.hh
typedef float64 datetime64;                                                      //170427

//deprecated use datetime64
typedef float64 Datetime64;                                                      //050724
*/

#include "corn/chronometry/date_types.hh"
//  Class forward declaration
//170525 class Date;     // This is deprecated
class Date_time_64;

}; // namespace CORN

#endif
