#include "corn/math/numerical/interpolation/step.h"

namespace CORN
{
//____________________________________________________________
/*  Returns B
      |                 Point A is last point
-  Ay |  A              Point B is point to interpolate
|     |                 Point C is next point
|   y |            B-
T     |             s
|     |             |
- Cy  |             -               C
      |
      |
      +-----------------------------------------
         |----Q----|
         |-------------R------------|
         Ax        x                Cx
*/

float32 Interpolation_step::interpolate(float32 Ay, float32 Cy,float32 R, float32 Q) const
{  return Ay;
}
//2015-01-11___________________________________________________________________

//____________________________________________________________
} // namespace CORN
