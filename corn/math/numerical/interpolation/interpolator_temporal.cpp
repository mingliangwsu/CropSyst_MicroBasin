#include "corn/math/numerical/interpolation/linear.h"
#include "corn/math/numerical/interpolation/interpolator_temporal.h"
#include "corn/math/numerical/interpolation/step.h"
namespace CORN
{

//______________________________________________________________________________
Interpolator_temporal::Interpolator_temporal
(Interpolation_curve_type   curve_type_
,float32                    default_ordinate_
,const CORN::Date_const    *reference_date_
)
: reference_date  ()
, last_date       ()
, last_ordinate   (default_ordinate_)
, interpolation_step      (0)
, interpolation_linear    (0)
, interpolation           (0)
//, curveX(0)
, observations    (0.0,default_ordinate_) // (new Observations(0.0,default_ordinate_))
{
   if (reference_date) set_reference_date(*reference_date);
   switch (curve_type_)
   {
      case step_curve   : interpolation = interpolation_step   = new Interpolation_step  (observations); break;
      case linear_curve : interpolation = interpolation_linear = new Interpolation_linear(observations); break;
   } // switch
}
//_Interpolator_temporal:constructor______________________________2015-01-11_/
Interpolator_temporal::~Interpolator_temporal()
{  delete reference_date;
   delete interpolation_step;
   delete interpolation_linear;
}
//_Interpolator_temporal:destructor_______________________________2015-01-11_/
float32 Interpolator_temporal::get_ordinate_by_date
(const Date_const &for_date
,bool extrapolate_terminal
) contribution_
{  if (for_date != last_date && reference_date && interpolation)                         //180503_150310
   {  // We may have already just computed this, no need to redo the whole interplocation if we already have today's value.
      last_date.set(for_date);
      // Convert for_date to a days from reference date so we have a continuous x axis.
      float32 day_abscissa = reference_date->days_between(for_date,false);
      last_ordinate = interpolation->get_ordinate(day_abscissa,extrapolate_terminal);
   }
   return last_ordinate;
}
//_2015-01-11___________________________________________________________________
bool Interpolator_temporal::set_by_date
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
      observations.append(day_abscissa,ordinate);
   } else was_set = false;
   return was_set;
}
//_2015-01-11___________________________________________________________________
bool Interpolator_temporal::set_reference_date
(const Date_const &reference_date_)                                contribution_
{  reference_date = new CORN::Date_clad_32(reference_date_.get_date32());        //170524
   return true;
}
//_2015-03-10__________________________________________________________________/
} // namespace CORN

