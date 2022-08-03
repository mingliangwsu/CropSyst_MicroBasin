#ifndef linearH
#define linearH
#include "corn/math/numerical/interpolation/interpolation_A.h"
namespace CORN
{
//____________________________________________________________
class Interpolation_linear
: public extends_ Interpolation_abstract
{
 public:

   inline Interpolation_linear(const Observations &observations_)
      : Interpolation_abstract(observations_)
      {}
/*180503
   inline Interpolation_linear(Observations *observations_given)
      : Interpolation_abstract(observations_given)
      {}
*/
 protected:
   virtual float32 interpolate(float32 A, float32 C,float32 R, float32 Q) const;

};
//_class_Interpolation_linear___________________________2018-04-26__2014-06-23_/
} // namespace CORN
#endif