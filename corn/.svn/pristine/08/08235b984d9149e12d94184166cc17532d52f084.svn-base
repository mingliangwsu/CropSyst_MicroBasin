// Rename this to interpolator

#error the interpolate unit is obsolete,
/* include intrepolator_temporal.h
These classes have been replaced with Interpolation and
Interpolation specializations
Interpolation_curve_dated_linear has been replaed with and Interpoator_temporal



*/

#ifndef interpolateH
#define interpolateH
#ifndef bi_listH
#  include "corn/container/bilist.h"
#endif
#include "corn/chronometry/date_32.h"
#include "interpolation.h"

namespace CORN {
//______________________________________________________________________________
/* 180426 moved to interpolator_temporal.cpp
enum Interpolation_curve_type
{ step_curve
// , proximal (nearest neighbor)    Conceptual:
, linear_curve
// Conceptual:
, quadradic
, cubic
, Lagrange
, Gaussian
, polnomial
, conservative
};
*/
//______________________________________________________________________________
/*180426 moved to interpolation
class Coordinate
: public Item
{  float32  abscissa;   // X  dependent
   float32  ordinate;   // Y  independent
public:
   Coordinate(float32  _abcissa,float32  _ordinate);
   inline virtual float32  get_abscissa()                               mutation_{ return abscissa; };
   inline virtual float32  get_ordinate()                           contribution_{ return ordinate; };  // Pure must be provided in derived point class.
   inline virtual int          compare(const Item &other)                  const
   {  float32 other_abscissa = ((Coordinate &)other).get_abscissa();
      return (abscissa < other_abscissa ) ? -1 : (abscissa > other_abscissa ) ? 1 : 0;
   };  // I had abcissa and ordinate swapped

};
//______________________________________________________________________________
*/
/* reimplemented separated to Observations and Interpolation_abstract
class Interpolation_curve
: public extends_ Bidirectional_list // container of Interpolation points (must be sortabled)
{protected:
   mutable Coordinate  initial_value;
   mutable Coordinate *last_point;
   mutable Coordinate *next_point;
public:
   Interpolation_curve(float32 initial_abscissa,float32 initial_ordinate);
   // In case there are no additional points provided, we need to have
   // at least one point to provided a default value.
   Interpolation_curve                                                           //140623
      (const float32 priming_abscissa[]
      ,const float32 priming_ordinates[]
      ,nat32 points_alloc);
   virtual float32 set(float32 initial_abscissa, float32 ordinate);
   void setup_current_range(float32 abscissa)                      contribution_;
   virtual nat32 delete_all(Item::Filter filter = Item::filter_all);
   // Returns the number of items deleted
   virtual float32 get_ordinate(float32 abscissa)                  contribution_;
 protected:
   virtual float32 interpolate(float32 A, float32 C,float32 R, float32 Q)  const = 0;
};
//______________________________________________________________________________
*/
/*180426 reimplemented in interpolation/linear
class Interpolation_curve_linear    // was Interpolation_linear_curve
: public extends_ Interpolation_curve
{public:
   Interpolation_curve_linear(float32 initial_abscissa, float32 initial_ordinate);
   Interpolation_curve_linear                                                    //140623
      (const float32 priming_abscissa[]
      ,const float32 priming_ordinates[]
      ,nat32 points_alloc);
 protected:
   virtual float32 interpolate(float32 A, float32 C,float32 R, float32 Q)  const;
};
//______________________________________________________________________________
*/
/*180426 reimplemented in interpolation/step
class Interpolation_curve_step
: public extends_ Interpolation_curve
{
 public:
   Interpolation_curve_step(float32 initial_abscissa, float32 initial_ordinate);
   Interpolation_curve_step                                                      //140623
      (const float32 priming_abscissa[]
      ,const float32 priming_ordinates[]
      ,nat32 points_alloc);
 protected:
   virtual float32 interpolate(float32 A, float32 C,float32 R, float32 Q)  const;
};
//_2015-01-11_________________________________________Interpolation_curve_step_/
*/
/*180426 replaced with Interpolator_temporal
class Interpolation_curve_dated   // rename this to Interpolator_temporal or Interpolator_time_series
{  contribute_ CORN::Date_clad_32 *reference_date; // This is the date at the origin of the axis
      // The reference date may be known up front (and provided in the constructor)
      // Or it may be taken from the first entry in the provided dataset.
 protected: // These are for optimization to prevent recomputing an iterpolation we may have just done
   contribute_ CORN::Date_clad_32 last_date;
   contribute_ float32   last_ordinate;
   //180426 Interpolation_curve  *curve;
   Interpolation *curve;  // rename to interpolation
 public:
   Interpolation_curve_dated
      (Interpolation_curve_type curve_type
      ,float32 default_ordinate
      ,const CORN::Date_const *_reference_date = 0 // optional
      );
      // If reference date is not specified, the first set date
      // will be presumed.
   virtual ~Interpolation_curve_dated();
   virtual float32 get_ordinate_by_date(const Date_const&for_date) contribution_;
   virtual bool set_by_date(const Date_const &for_date, float32 ordinate)modification_;
 protected:
   virtual bool set_reference_date(const Date_const &reference_date) contribution_;
};
//_2015-01-11_________________________________________Interpolation_curve_step_/
/*150111 obsolete replaced with Interpolation_curve_dated
class Interpolation_curve_dated_linear    // was Dated_interpolation_linear_curve
: public extends_ Interpolation_curve_linear
, public extends_ Interpolation_curve_dated_abstract
{
public:
   Interpolation_curve_dated_linear(Year reference_year, float32 default_ordinate);
   // Reference year can by any year if working with dates in another century,
   // it might be more convenient to specify a date other than the default.
   virtual float32 get_ordinate_by_date(const Date &for_date)      contribution_;
   virtual bool set_by_date(const Date &for_date, float32 ordinate)modification_;
};
//______________________________________________________________________________
class Interpolation_curve_dated_step    // was Dated_interpolation_linear_curve
: public extends_ Interpolation_curve_step
, public extends_ Interpolation_curve_dated_abstract
{
public:
   Interpolation_curve_dated_step(Year reference_year, float32 default_ordinate);
   // Reference year can by any year if working with dates in another century,
   // it might be more convenient to specify a date other than the default.
   virtual float32 get_ordinate_by_date(const Date &for_date)      contribution_;
   virtual bool set_by_date(const Date &for_date, float32 ordinate)modification_;
};
//_2015-01-15___________________________________________________________________
*/
} // namespace CORN;
#endif

