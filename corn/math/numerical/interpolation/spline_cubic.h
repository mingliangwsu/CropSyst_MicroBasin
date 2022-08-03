#ifndef spline_cubicH
#define spline_cubicH

#include "corn/math/numerical/interpolation/interpolation_A.h"

namespace CORN
{
//___________________________________________________________________________
class Interpolation_spline_cubic
: public extends_ Interpolation_abstract
{
   CORN::Unidirectional_list splines;
   bool clamped;
   bool initialized; // temporary until I implement initialize consistently

 protected:
   class Spline
   : public implements_ Item
   {
    public:
      float32 x;    // low and high are not good names
      float32 y;    // low and high are not good names
      float32 x_next;
      float32 y_next;
      float32 h; // interval width
      float32 slope;       // S
      float32 curvature;   // R The first and last spline will always be 0
      float32 A,B,C,D;

    public:
      Spline
         (float32 x_
         ,float32 y_
         ,float32 x_next_
         ,float32 y_next_
         );
      float32 calc_y(float32 x)                                           const;
   };
 public:
   Interpolation_spline_cubic
      (const Observations &observations_
      ,bool clamped_ = false)
      : Interpolation_abstract(observations_)
      , initialized(false)
      , clamped(clamped_)
      {}
/*180503
   Interpolation_spline_cubic
      (Observations *observations_given
      ,bool clamped_ = false)
      : Interpolation_abstract(observations_given)
      , initialized(false)
      , clamped(clamped_)
      {}
*/
 public:
   bool initialize()                                            initialization_;
   virtual float32 get_ordinate
      (float32 abscissa
      ,bool extrapolate_terminal = true)          const; // contribution_;
};
//___________________________________________________________________________
extern float64 determinant_value_order_N(float32 **major, nat16 order);
//___________________________________________________________________________

} // namespace CORN
#endif

