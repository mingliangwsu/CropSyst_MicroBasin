#include "corn/math/numerical/interpolation/interpolation_A.h"

namespace CORN
{
//______________________________________________________________________________
/*180503
Interpolation_abstract::Interpolation_abstract()
: Interpolation                                                               ()
, observations_owned                                     (new Observations(0,0))
, observations                                             (*observations_owned)
{
}
//_Interpolation_abstract:constructor_______________________________2018-04-26_/
*/
Interpolation_abstract::Interpolation_abstract(const Observations &observations_)
: Interpolation                                                               ()
//180503 , observations_owned                                                         (0)
, observations                                                   (observations_)
{
}
/*180503
//_Interpolation_abstract:constructor_______________________________2018-04-26_/
Interpolation_abstract::Interpolation_abstract(Observations *observations_given)
: Interpolation                                                               ()
, observations_owned                                        (observations_given)
, observations                                             (*observations_owned)
{

}
*/
//_Interpolation_abstract:constructor_______________________________2018-04-26_/
/*180503
Interpolation_abstract::~Interpolation_abstract()
{
   delete observations_owned;
}
*/
//_Interpolation_abstract:destructor________________________________2018-04-26_/
float32 Interpolation_abstract::get_ordinate
(float32 abscissa
,bool extrapolate_terminal)        contribution_
{  // This method is common for step and linear
   // The spline class have novel implementions

   if (   abscissa < observations.last_point->get_abscissa()
       || abscissa > observations.next_point->get_abscissa())
   {  // x is not in the current range
      // find a new last point and next point which x will be between.
      observations.setup_current_range(abscissa);
   }

   // If x is still out of range, we return the end point.
   float32 last_x = observations.last_point->get_abscissa() ;
   if (abscissa < last_x)
      return observations.last_point->get_abscissa();
   float32 next_x = observations.next_point->get_abscissa();
   if (abscissa > next_x)
      return observations.next_point->get_ordinate();
   // Otherwise calculate the point on the line.

   float32 last_y = observations.last_point->get_ordinate();
   float32 next_y = observations.next_point->get_ordinate();
   float32 R = next_x - last_x;
   float32 Q = abscissa - last_x;
   float32 result = interpolate(last_y,next_y,R,Q);
   return result;
}
//_2015-01-11___________________________________________________________________


} // namespace CORN
