#include "common/physics/water_depth.h"

namespace Physical
{
//______________________________________________________________________________
 float64 Water_depth::deduct(float64 amount_depth)
{  float64 act_deduction = amount_depth;
   if (act_deduction > depth_m)
      act_deduction = depth_m;
   dec_m(act_deduction); //160408 depth -= act_deduction;
   return act_deduction;
}
//______________________________________________________________________________
float64 Water_depth::dec_m(float64 reduction_m)
{  depth_m -= reduction_m;
   if (depth_m < -0.0000001)
      std::cerr << "neg water depth:" << depth_m << " (very small neg values are probably OK)" << std::endl;
   //assert (depth_m >= 0.0);
   return depth_m;
}
//______________________________________________________________________________
} // namespace Physical
