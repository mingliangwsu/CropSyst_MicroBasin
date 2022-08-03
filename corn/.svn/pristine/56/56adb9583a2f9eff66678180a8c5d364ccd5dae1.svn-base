#ifndef interpolator_temporalH
#define interpolator_temporalH
#include "corn/chronometry/date_32.h"
#include "corn/math/numerical/observation.h"

namespace CORN
{
class Interpolation;
class Interpolation_linear;
class Interpolation_step;
//____________________________________________________________
enum Interpolation_curve_type
{ step_curve
//NYI , proximal // (nearest neighbor)
, linear_curve
, cubic_curve
/* Conceptual:
, quadradic_curve

, Lagrange_curve
, Gaussian_curve
, polnomial_curve
, conservative_curve
*/
};
//______________________________________________________________________________
// This class replaces Interpolation_curve_dated
class Interpolator_temporal
{
 protected:
   contribute_ CORN::Date_clad_32 *reference_date; // This is the date at the origin of the axis
      // The reference date may be known up front (and provided in the constructor)
      // Or it may be taken from the first entry in the provided dataset.
 protected: // These are for optimization to prevent recomputing an iterpolation we may have just done
   contribute_ CORN::Date_clad_32 last_date;
   contribute_ float32   last_ordinate;
   Observations observations;                                                    //180426
   //180426 Interpolation_curve  *curve;
//   Interpolation *curveX;  // rename to interpolation

   // Could put these in a union because only one will be selected based on type
   Interpolation_step   *interpolation_step;
   Interpolation_linear *interpolation_linear;
   Interpolation        *interpolation;
 public:
   Interpolator_temporal
      (Interpolation_curve_type curve_type
      ,float32 default_ordinate
      ,const CORN::Date_const *_reference_date = 0 // optional
      );
      // If reference date is not specified, the first set date
      // will be presumed.
   virtual ~Interpolator_temporal();
   virtual float32 get_ordinate_by_date
      (const Date_const&for_date
      ,bool extrapolate_terminal = false)                         contribution_;
   virtual bool set_by_date(const Date_const &for_date, float32 ordinate)modification_;
 protected:
   virtual bool set_reference_date(const Date_const &reference_date) contribution_;
};
//_class_Interpolator_temporal________________________________2018-04-26__2015_/
} // namespace CORN


#endif
