#ifndef dynamic_water_enteringH
#define dynamic_water_enteringH

#include "corn/dynamic_array/dynamic_array_T.h"
//______________________________________________________________________________
class Dynamic_water_entering_soil
: public CORN::Dynamic_array<float32>
// This is 32bit because if we get the array values from UED file
// those are stored 32bit
{public:
    inline Dynamic_water_entering_soil(nat8 max_intervals)
       :CORN::Dynamic_array<float32>(max_intervals,1,0)
       {}
    float64 deduct(float64 deduction);
};
//_1999-04-02___________________________________________________________________
#endif
// soilentr.h

