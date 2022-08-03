#include "corn/math/compare.hpp"
#include "corn/math/numerical/solver.h"
namespace CORN {
//______________________________________________________________________________
float64 Solver_bisection_method::solve(float64 y, float64 min_x, float64 max_x, float64 precision, uint16 iterations) const
{  float64 found_x = 0;
   if (!iterations)
      solved = false;
   else
   {  float64 mid_x = (min_x + max_x)/2.0;
      float64 general_f_minx = general_form_f(y,min_x);
      float64 general_f_midx = general_form_f(y,mid_x);
      float64 product = general_f_minx * general_f_midx;
      solved = CORN::is_approximately<float64>(product,0.0,precision)
            || CORN::is_approximately<float64>(min_x,mid_x,precision);
      found_x = solved
      ? mid_x
      : (product < 0.0)
         ? solve(y,min_x,mid_x,precision,((uint16)((int16)iterations - (int16)1)))
         : solve(y,mid_x,max_x,precision,((uint16)((int16)iterations - (int16)1)));
   }
   return found_x;
}
//______________________________________________________________________________
} // namespace CORN
// solver.cpp

