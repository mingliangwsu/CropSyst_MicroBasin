#include "corn/math/numerical/interpolation/linear.h"
namespace CORN
{
//____________________________________________________________
float32 Interpolation_linear::interpolate(float32 Ay, float32 Cy,float32 R, float32 Q) const
{  return
      R == 0.0 ? Ay :  // If no first or last, just return Ay
        (Q * (Cy - Ay)/R +Ay);
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
}
//_2000-05-02___________________________________________________________________

//____________________________________________________________
} // namespace CORN
