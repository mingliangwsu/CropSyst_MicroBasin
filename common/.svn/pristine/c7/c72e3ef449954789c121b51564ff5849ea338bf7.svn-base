#include "common/residue/residue_decomposition_limitations.h"
#include "corn/math/compare.hpp"
#include "corn/math/moremath.h"
//______________________________________________________________________________
float64 temp_limiting(float64 layer_temp )
{  float64 a = 6.1;
   float64 opt_temp = 30.0;
   return CORN::must_be_between<float64>
      (1.32 * (2.0 * CORN_sqr(layer_temp + a) *
                     CORN_sqr(opt_temp + a)-
                     CORN_sqr(CORN_sqr(layer_temp + a)))
              / CORN_sqr(CORN_sqr(opt_temp + a)),0.1,1.0);
}
//______________________________________________________________________________
float64 water_temp_limiting2
(float64 fc
,float64 wc
,float64 temp_limiting)
{  float64 water_limiting = CORN::must_be_between<float64>(wc/fc,0.1,1.0);
   return std::min<float64>(water_limiting,temp_limiting);
}
//______________________________________________________________________________
