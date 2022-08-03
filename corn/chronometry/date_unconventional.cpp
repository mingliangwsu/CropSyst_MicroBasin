
/* date.cpp    C++ version of date library

   Written by Roger Nelson
   Comments, suggestions, questions and bug reports can be sent to:

      Biological Systems Engr. Dept.
      Washington State University
      Pullman, WA 99164-6120

      rnelson@mail.wsu.edu
*/

#  include "corn/chronometry/date_unconventional.h"

namespace CORN {

DOM unconventional_360_day_year_month_lengths[13] =
{ 0,30,30,30,30,30,30,30,30,30,30,30,30};
//_2013-03-26___________________________________________________________________
nat32 Date_unconventional::days_between
(const Date_const &that_date ,bool inclusive) const
{
   Date_unconventional that_date_unconv(that_date ,calendar);
   // We need to have this and that dates in this calendar system.
   return Date_clad_32::days_between(that_date_unconv,inclusive);
}
//_2013-03-26___________________________________________________________________
Date_unconventional::Date_unconventional()
: Date_clad_32()
, calendar(calendar_ISO8601)
{};
//_2013-02-25___________________________________________________________________
Date_unconventional::Date_unconventional
(const CORN::Date_const &copy_from,Calendar _calendar)
: Date_clad_32 (copy_from.get_year(),copy_from.get_month(), copy_from.get_DOM())
, calendar(_calendar)
{  Year year = copy_from.get_year();
    Month month = copy_from.get_month();
    DOM dom = get_DOM();
    Days days_in_mnth = get_days_in_month(year,month);
    if (dom > days_in_mnth)
        dom = days_in_mnth;
    set_YMD(year,month,dom);
}
//_2013-03-26___________________________________________________________________
Date_unconventional::~Date_unconventional()
{}
//_2013-03-26___________________________________________________________________
Date_unconventional::Date_unconventional(Calendar &_calendar)
: Date_clad_32()
, calendar(_calendar)
{}
//_2013-03-26___________________________________________________________________
bool Date_unconventional::is_leap_year(Year year)                       affirmation_
{  Year year_abs = abs(get_year());
   bool is_leap = false;
   switch(calendar)
   {
     case calendar_no_leap_year :
     case calendar_360_day :
        { is_leap = false; }
        break;
     calendar_all_leap_year :  // Gregorian calendar with every year being a leap year, i.e., all years are 366 days long.
        { is_leap = true; }
        break;
     case calendar_julian_revised :
         {  // ref: http://en.wikipedia.org/wiki/Revised_Julian_calendar

            nat16 century = (year_abs / 100) % 9;
            is_leap = ((year_abs % 4) == 0)
                ? ((year % 100)  == 0)
                  ? ((century == 2) || (century == 6))
                  : false
                : false;
        } break;
     case calendar_julian_traditional:   // Also Coptic and Ethiopian
     {
        is_leap = (year_abs == 0)      ? false :
           ((year_abs % 4) > 0)   ? false : true;
           // the ISO standard specifies that dates prior to year 1582 are the proleptic gregorian calendar
     }
     default: is_leap = Date_clad_32::is_leap_year(year); break;
   }
   return is_leap;
}
//_2013-02-22___________________________________________________________________
const nat8 *Date_unconventional::get_month_lengths_in_year(Year year)                  const
{
   switch (calendar)
   {  case calendar_360_day         : return unconventional_360_day_year_month_lengths; //no break;
      case calendar_no_leap_year    : return common_year_month_lengths; //no break;
      case calendar_all_leap_year   : return leap_year_month_lengths; //no break;
      // NYI  calendar_julian_revised  // Used since 1923 (also known as the Milankovic
      // NYI  calendar_julian_traditional
      default: return Date_clad_32::get_month_lengths_in_year(year); break;
   }
   return common_year_month_lengths;
}
//_2013-02-22___________________________________________________________________
nat16 Date_unconventional::days_in_year(Year year)                         const
{  nat16 days = 0;
   switch (calendar)
   {  case calendar_360_day         : days = 360; break;
      case calendar_no_leap_year    : days = 365; break;
      case calendar_all_leap_year   : days = 366; break;
      // NYI  calendar_julian_revised  // Used since 1923 (also known as the Milankovic
      // NYI  calendar_julian_traditional
      default: days = Date_clad_32::days_in_year(year);
   }
   return days;
}
//_2013-02-25___________________________________________________________________
} // namespace CORN
