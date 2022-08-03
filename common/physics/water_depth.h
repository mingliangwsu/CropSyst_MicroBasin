#ifndef water_depthH
#define water_depthH
#include "corn/measure/measures.h"
#include "common/physics/property.h"
#include <iostream>
namespace Physical
{
//______________________________________________________________________________
class Water_depth
{
   float64 depth_m; // meter
 public:
   Water_depth()
      : depth_m(0)
      {}
 public:
   inline float64 get_mm() const { return m_to_mm(get_m()); }                    //140527_110910
   inline float64 get_m()  const { return depth_m; }                             //110910
   inline float64 set_mm(float64 millimeter)  { return depth_m = mm_to_m(millimeter);}
   inline float64 set_m(float64 meter)        { return depth_m = meter;}
   inline float64 clear() { return depth_m = 0; }
   float64 dec_m(float64 reduction_m);
    /*moved to cpp
      {  depth_m -= reduction_m;
         if (depth_m < 0.0)
            std::cerr << "neg water depth" << std::endl;
         //assert (depth_m >= 0.0);
         return depth_m;
      }
      */
   inline float64 dec_mm(float64 reduction_mm)
      { return dec_m(mm_to_m(reduction_mm)); }
   float64 deduct(float64 amount_depth)                            modification_;
};
//_2016-04-08___________________________________________________________________
} // namespace Physical

#endif
