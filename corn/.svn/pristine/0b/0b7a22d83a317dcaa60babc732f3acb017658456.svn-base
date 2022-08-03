// This file is obsolete, remove it from your project  170828RLN

#include "corn/chronometry/date_time_64.h"
#include "corn/chronometry/date_32.h"
#include "corn/math/compare.hpp"
#include <assert.h>

namespace CORN
{
//______________________________________________________________________________
/*170815 moved to date_time_T
float64   Date_time_64_cowl::get_time64()                               const
   // Returns the time (fraction)
{  int32 date_part  = (int32)datetime_ref;
   datetime64 time_part = datetime_ref - (datetime64)date_part;
   return time_part;
}
*/
//_2017-04-30_______________________________________________________get_time64_/
/*170815 moved to date_time_cowl_T
datetime64 Date_time_64_cowl::set_datetime64(datetime64 value)      assignation_
{  return datetime_ref = value; }
//_2017-04-30_2003-07-17_______________________________________set_datetime64__/
datetime64 Date_time_64_cowl::set_date32(Date32 value)              assignation_
{ return datetime_ref = (Date32)value; }
//_2017-04-30_______________________________________________________set_date32_/
datetime64 Date_time_64_cowl::set_date
(const Date_interface &new_date)                                    assignation_
{ return datetime_ref = new_date.get_datetime64(); } // add option to set the entire value?
//_2017-04-30_2010-01-16_2003-07-17___________________________________set_date_/
void Date_time_64_cowl::split
(datetime64 &date_part, datetime64 &time_fract)                            const
{  nat32 value_int32 = (nat32)datetime_ref;
   date_part = value_int32;
   time_fract = datetime_ref - date_part;
}
//_2017-04-30_2004-09-09_2003-07-15______________________________________split_/
datetime64 Date_time_64_cowl::join(datetime64 date_part, datetime64 time_fract)
{  datetime_ref = date_part + time_fract;
   return datetime_ref;
}
//_2017-04-30_2003-07-15__________________________________________________join_/
datetime64 Date_time_64_cowl::inc_time_fract
(datetime64 time_fract)                                            modification_
{  datetime64 date;
   datetime64 time;
   split(date,time);
   time += time_fract;
   if (CORN::is_approximately<double>(time,1)) time = 1.0;                       //170621LML
   datetime64 days;
   datetime64 new_time;
   Date_time_64_cowl(time).split(days,new_time);
   //170525 Date_time_64_cowl new_date(date); //170430 ((int32)date);
   Date_32_clad new_date(date); //170430 ((int32)date);
   new_date.inc_days((int32)days);
   return join(new_date.get_datetime64(),new_time);
}
//_2017-04-30_2004-09-09_040909_2003-07-14______________________inc_time_fract_/
//______________________________________________________________________________
Date_time_64_clad::Date_time_64_clad()
: Date_time_64_cowl(datetime)
, datetime(0)
{  set_now(); // Current computer's date and time
}
//_2017-04-30_____________________________________________________constructor__/
Date_time_64_clad::Date_time_64_clad(datetime64 value)
: Date_time_64_cowl(datetime)
, datetime(value)
{}
//_2017-05-23_____________________________________________________constructor__/
Date_time_64_clad::Date_time_64_clad
(Date32 date_, nat32 time_)
: Date_time_64_cowl(datetime)
, datetime(0)
{
   //170621LML  join(date_,time_);
   join(date_,(float32) time_ / Seconds_per_day);
 }
//_2017-05-23_____________________________________________________constructor__/
//______________________________________________________________________________
*/
} // namespace CORN
