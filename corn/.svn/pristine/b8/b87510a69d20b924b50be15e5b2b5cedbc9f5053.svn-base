

#error the interpolate unit is obsolete,
/* include intrepolator_temporal.cpp and interpolation.cpp and the
specific interpolation classes in corn/math/numerical/interpolation directory

#include "corn/math/numerical/interpolate.h"
namespace CORN {
//______________________________________________________________________________
/* 180426 moved to interpolation.cpp
Coordinate::Coordinate(float32  _abscissa, float32 _ordinate)
: Item()
, abscissa(_abscissa)
, ordinate(_ordinate)
{}
//______________________________________________________________________________
*/
/* 180426 obsolete now using Observations
Interpolation_curve_linear::Interpolation_curve_linear
(float32 initial_abscissa,float32 initial_ordinate)
: Interpolation_curve(initial_abscissa, initial_ordinate)
{}
*/
//______________________________________________________________________________
/* 180426 obsolete now using Observations
Interpolation_curve_step::Interpolation_curve_step
(float32 initial_abscissa,float32 initial_ordinate)
: Interpolation_curve(initial_abscissa, initial_ordinate)
{}
//_2015-01-11___________________________________________________________________
*/
/* 180426 moved to Observations
Interpolation_curve::Interpolation_curve
(const float32 priming_abscissa[]
,const float32 priming_ordinates[]
,nat32   points_alloc)
:initial_value(priming_abscissa[0],priming_ordinates[0])
,last_point(&initial_value)
,next_point(&initial_value)
{  for (nat32 p = 0; p <= points_alloc; p++)
      set(priming_abscissa[p], priming_ordinates[p]);
}
//_2014-06-23___________________________________________________________________
*/
/* 180426 moved to Observations
Interpolation_curve_linear::Interpolation_curve_linear
(const float32 priming_abscissa[]
,const float32 priming_ordinates[]
,nat32 points_alloc)
:Interpolation_curve
(priming_abscissa
,priming_ordinates
,points_alloc)
{}
*/
//_2014-06-23___________________________________________________________________
/* 180426 moved to Observations
Interpolation_curve_step::Interpolation_curve_step
(const float32 priming_abscissa[]
,const float32 priming_ordinates[]
,nat32 points_alloc)
:Interpolation_curve
(priming_abscissa
,priming_ordinates
,points_alloc)
{}
*/
//_2015-01-11___________________________________________________________________

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

/* 180426 moved to interpolation/linear
float32 Interpolation_curve_linear::interpolate(float32 Ay, float32 Cy,float32 R, float32 Q) const
{  return
      R == 0.0 ? Ay :  // If no first or last, just return Ay
        (Q * (Cy - Ay)/R +Ay);
}
//_2000-05-02___________________________________________________________________
*/
/*180426 moved to interpolation/step
float32 Interpolation_curve_step::interpolate(float32 Ay, float32 Cy,float32 R, float32 Q) const
{  return Ay;
}
//2015-01-11___________________________________________________________________
*/
/* 180426 moved to Observations
Interpolation_curve::Interpolation_curve(float32 initial_abscissa,float32 initial_ordinate)
:initial_value(initial_abscissa,initial_ordinate)
,last_point(&initial_value)
,next_point(&initial_value)
{}
*/
//______________________________________________________________________________
/* 180426  move to observations
void Interpolation_curve::setup_current_range(float32 abscissa)    contribution_
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
//______________________________________________________________________________
*/
/* 180426 moved to Observations
nat32 Interpolation_curve::delete_all(Item::Filter filter)         modification_
{  nat32 count_deleted = Bidirectional_list::delete_all(filter);
   last_point = &initial_value;
   next_point = &initial_value;
   return count_deleted;
}
//______________________________________________________________________________
*/
/*150111
float32 Interpolation_curve_linear::get_ordinate(float32 abscissa) mutates_
{  if (abscissa < last_point->get_abscissa() || abscissa > next_point->get_abscissa())
   {  // x is not in the current range
      // find a new last point and next point which x will be between.
      setup_current_range(abscissa);
   }
   // If x is still out of range, we return the end point.
   float32 last_x = last_point->get_abscissa() ;
   if (abscissa < last_x)
      return last_point->get_abscissa();
   float32 next_x = next_point->get_abscissa();
   if (abscissa > next_x)
      return next_point->get_ordinate();
   // Otherwise calculate the point on the line.

   float32 last_y = last_point->get_ordinate();
   float32 next_y = next_point->get_ordinate();
   float32 R = next_x - last_x;
   float32 Q = abscissa - last_x;
   float32 result = interpolate(last_y,next_y,R,Q);
   return result;
}
*/
//______________________________________________________________________________
/* 180426 moved to Interplation_abstract
float32 Interpolation_curve::get_ordinate(float32 abscissa)        contribution_
{  if (abscissa < last_point->get_abscissa() || abscissa > next_point->get_abscissa())
   {  // x is not in the current range
      // find a new last point and next point which x will be between.
      setup_current_range(abscissa);
   }

   // If x is still out of range, we return the end point.
   float32 last_x = last_point->get_abscissa() ;
   if (abscissa < last_x)
      return last_point->get_abscissa();
   float32 next_x = next_point->get_abscissa();
   if (abscissa > next_x)
      return next_point->get_ordinate();
   // Otherwise calculate the point on the line.

   float32 last_y = last_point->get_ordinate();
   float32 next_y = next_point->get_ordinate();
   float32 R = next_x - last_x;
   float32 Q = abscissa - last_x;
   float32 result = interpolate(last_y,next_y,R,Q);
   return result;
}
//_2015-01-11___________________________________________________________________
*/
/* 180426 moved to Observations
float32 Interpolation_curve::set(float32 x, float32 y)
{  Coordinate *new_point = new Coordinate (x,y);
   add_sorted(new_point);
   return y;
}
//______________________________________________________________________________
*/
/* 180426 moved to Interpolator_temporal
Interpolation_curve_dated::Interpolation_curve_dated
(Interpolation_curve_type   curve_type_
,float32                    default_ordinate_
,const CORN::Date_const    *reference_date_
)
: reference_date  ()
, last_date       ()
, last_ordinate   (default_ordinate_)
, curve           (0)
{
   if (reference_date) set_reference_date(*reference_date);
   switch (curve_type_)
   {  case step_curve   : curve = new  Interpolation_curve_step   (0.0,default_ordinate_); break;
      case linear_curve : curve = new  Interpolation_curve_linear (0.0,default_ordinate_); break;
   } // switch
}
//_2015-01-11___________________________________________________________________
Interpolation_curve_dated::~Interpolation_curve_dated()
{  delete reference_date;
   delete curve;
}
//_2015-01-11___________________________________________________________________
float32 Interpolation_curve_dated::get_ordinate_by_date(const Date_const &for_date) contribution_
{  if (for_date != last_date && reference_date)                                  //150310
   {  // We may have already just computed this, no need to redo the whole interplocation if we already have today's value.
      last_date.set(for_date);
      // Convert for_date to a days from reference date so we have a continuous x axis.
      float32 day_abscissa = reference_date->days_between(for_date,false);
      last_ordinate = curve->get_ordinate(day_abscissa);
   }
   return last_ordinate;
}
//_2015-01-11___________________________________________________________________
bool Interpolation_curve_dated::set_by_date
(const Date_const &for_date
, float32 ordinate)                                                modification_
{  bool was_set = true;
   // If the reference date hasn't be previously set, assume the
   // first date loaded/encountered will be the reference date.
   if (!reference_date) set_reference_date(for_date);
   // Convert for_date to a days from reference date so we have a continuous x axis.
   if (for_date >= (*reference_date))
   {  float32 day_abscissa = reference_date->days_between(
         for_date,false);
      curve->set(day_abscissa,ordinate);
   } else was_set = false;
   return was_set;
}
//_2015-01-11___________________________________________________________________
bool Interpolation_curve_dated::set_reference_date
(const Date_const &reference_date_)                                contribution_
{  reference_date = new CORN::Date_clad_32(reference_date_.get_date32());        //170524
   return true;
}
//_2015-03-10__________________________________________________________________/
*/
} // namespace CORN

