#include <math.h>
//#include "corn/math/moremath.h"
#include "corn/math/random.hpp"
//#include "stdlib.h"
// for rand() function
namespace CORN
{
//#  include "corn/math/random.c_cpp"
float64 triangle_random(float64 L, float64 H, float64 M )
{
   float64 A1 = (M-L) / (H-L);
   float64 RA = CORN_uniform_random();
   return (RA <= A1)
   ? L + sqrt(RA * (M - L) * (H - L))
   : H - sqrt((1.0 - RA) * (H - M) * (H - L));
}

} // namespace CORN
 
