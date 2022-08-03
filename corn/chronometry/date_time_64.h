#ifndef date_time_64H
#define date_time_64H

#include "corn/chronometry/date_time_T.h"
namespace CORN
{
//______________________________________________________________________________

typedef Date_time_cowl<datetime64> Date_time_cowl_64;                            //170815
typedef Date_time_clad<datetime64> Date_time_clad_64;                            //170815

//The following are temporary aliases to transition from the previous class names
//These will eventually be removed. 170828
#define Date_time_64_cowl Date_time_cowl_64
#define Date_time_64_clad Date_time_clad_64

} // namespace CORN
// Roger Nelson rnelson@wsu.edu

#endif
