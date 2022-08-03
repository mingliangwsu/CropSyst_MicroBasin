#ifndef stepH
#define stepH

#include "corn/math/numerical/interpolation/interpolation_A.h"
// In step interpolation, the domain of the iterpolant function
// extends from the previous observed point forward to the next observed point.
// The interpolated value is constantly assigned to the previous ?indeterminant? point
namespace CORN
{
//____________________________________________________________
class Interpolation_step
: public extends_ Interpolation_abstract
{
 public:
/*Probably not used / needed

   Interpolation_step(float32 initial_abscissa, float32 initial_ordinate);
   Interpolation_step                                                            //140623
      (const float32 priming_abscissa[]
      ,const float32 priming_ordinates[]
      ,nat32 points_alloc);
*/
   Interpolation_step(const Observations &observations_)
      : Interpolation_abstract(observations_)
      {}
/*180503
   Interpolation_step(Observations *observations_given)
      : Interpolation_abstract(observations_given)
      {}
*/
 protected:
   virtual float32 interpolate(float32 A, float32 C,float32 R, float32 Q)  const;



};
//_class_Interpolation_step_____________________________2018-04-26__2015-01-11_/
} // namespace CORN



#endif