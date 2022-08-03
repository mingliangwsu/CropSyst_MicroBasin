#ifndef interpolation_AH
#define interpolation_AH

#include "corn/math/numerical/observation.h"
#include <limits>
namespace CORN
{
//______________________________________________________________________________
interface_ Interpolation
{
   virtual float32 get_ordinate
      (float32 abscissa
      ,bool extrapolate_terminal = true)                                const=0;
      // probably rename to get_interpolate
      // if extrapolate_terminal (need to rename) is true
      // if the abscissa exceeds the observed dataset
      // return the first/last ordinate of the first/last spline

      // shouldn't need to be a contribute if initialize is implemented.
      // would be const

   bool initialize()                              initialization_ {return true;}
};
//_interface_Interpolation__________________________________________2018-04-26_/
class Interpolation_abstract
: public implements_ Interpolation
{
 protected:
   //Observations *observations_owned;  //owned/given
   const Observations &observations;
 protected:
   virtual float32 interpolate(float32 A, float32 C,float32 R, float32 Q)  const
      { return std::numeric_limits<float32>::quiet_NaN(); }

 public:
   //180503 Interpolation_abstract();   // <- Check needed
   Interpolation_abstract(const Observations &observations);
   //180503 Interpolation_abstract(Observations *observations_given);
   //180503 virtual ~Interpolation_abstract();

   virtual float32 get_ordinate
      (float32 abscissa
      ,bool extrapolate_terminal = true)                          contribution_;

};
//_class_Interpolation_abstract_____________________________________2018-04-26_/

} // namespace CORN
#endif