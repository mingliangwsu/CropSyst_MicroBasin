#include "corn/math/numerical/observation.h"

namespace CORN
{
//______________________________________________________________________________
Coordinate::Coordinate(float32  _abscissa, float32 _ordinate)
: Item()
, abscissa(_abscissa)
, ordinate(_ordinate)
{}

//______________________________________________________________________________
Observations::Observations
(float32 initial_abscissa
,float32 initial_ordinate
)
:initial_value(initial_abscissa,initial_ordinate)
,last_point(&initial_value)
,next_point(&initial_value)
{}
//_Observations:constructor_________________________________________2018-04-26_/
Observations::Observations
(const float32 priming_abscissa[]
,const float32 priming_ordinates[]
,nat32   points_alloc)
:initial_value(priming_abscissa[0],priming_ordinates[0])
,last_point(&initial_value)
,next_point(&initial_value)
{  for (nat32 p = 0; p < points_alloc; p++)
      append(priming_abscissa[p], priming_ordinates[p]);
}
//_Observations:constructor_____________________________2018-04-26__2014-06-23_/
void Observations::setup_current_range(float32 abscissa)           contribution_
{  Container::Iterator *iter = iterator();
   last_point = (Coordinate *)iter->first();
   if (!last_point)  // There may be no points
      last_point = &initial_value;
   next_point = (Coordinate *)iter->next();
   if (!next_point)   // there may be one or no points
   {  next_point = last_point;
      return;
   }
   while (next_point && (next_point->get_abscissa() < abscissa))
   {  last_point = next_point;
      next_point = (Coordinate *)iter->next(); // move_to_next();
   }
   if (!next_point)
      next_point = last_point;
   delete iter;
}
//_Observations::setup_current_range____________________________18-04-26__2014_/
nat32 Observations::delete_all(Item::Filter filter)         modification_
{  nat32 count_deleted = Bidirectional_list::delete_all(filter);
   last_point = &initial_value;
   next_point = &initial_value;
   return count_deleted;
}
//_Observations::delete_all_____________________________________18-04-26__2014_/
Coordinate */*180430 float32 */Observations::append(float32 x, float32 y)
{  Coordinate *new_point = new Coordinate (x,y);

   take(new_point);
/* Not sure if working
   add_sorted(new_point);
*/
   return new_point;
}
//_Observations::set____________________________________________18-04-26__2014_/



//______________________________________________________________________________
} // namespace CORN


