#ifndef date_unconventionalH
#define date_unconventionalH

#include "corn/chronometry/date_32.h"

/*
   Extends the Date class to recognize unconventional date calendars.
   Specifically the class was added to support various calendar type
   in CF netCDF file conventions.

                     Added relative year style
*/

namespace CORN {
enum Calendar                                                                    //130222
{  calendar_ISO8601
,  calendar_proleptic_gregorian      // A Gregorian calendar extended to dates before 1582-10-15. That is, a year is a leap year if either (i) it is divisible by 4 but not by 100 or (ii) it is divisible by 400.
,  calendar_gregorian
,  calendar_no_leap_year    // all years have 365 days
,  calendar_all_leap_year   // Gregorian calendar with every year being a leap year, i.e., all years are 366 days long.
,  calendar_360_day         // All years are 360 days divided into 30 day months.
,  calendar_julian_revised  // Used since 1923 (also known as the Milankovic)
,  calendar_julian_traditional
};

#define calendar_365_day calendar_no_leap_year
#define calendar_366_day calendar_all_leap_year
//______________________________________________________________________________
class Date_unconventional
: public extends_ Date_clad_32
{public:
   Calendar calendar;
   bool   scientific;   // Astronomical years with -/0/+
 public:
   Date_unconventional();
   Date_unconventional(Calendar &_calendar);
   Date_unconventional
      (const CORN::Date_const &copy_from
      ,Calendar _calendar);
   virtual ~Date_unconventional();
   virtual nat16 days_in_year(Year year)                                  const;
   virtual bool  is_leap_year(Year year)                           affirmation_;
   virtual const nat8 *get_month_lengths_in_year(Year year)               const;
   virtual nat32 days_between
      (const Date_const &that
      ,bool inclusive=false)                                              const;
};
//_2013-02-22___________________________________________________________________
} // namespace CORN
#endif

