#ifndef date_constH
#define date_constH

#if (defined(date_typesH))
#   include "corn/chronometry/date_types.h"
#endif
/* The following functions are common to both the C and C++ versions */

bool date_leap_year(Year year);
/* returns TRUE (1) if year is leap year. */

DOM date_get_days_in_month(Year year,Month month);                               //130313
/* returns the number of days in month for that year */

#define date_days_in_year(year) (int)(date_is_leap_year(year) ? 366 : 365)
/* returns the number of days in the year */

const char *date_month_abbrev(Month month); // 990214
const char *date_month_name(Month month);   //990214
extern const char *date_month_names[13];    //000807
extern const char *date_month_abbrevs[13];  //000807

extern bool date_phrases_setup;
extern void date_setup_phrases();

extern const char *T_date_Day;
extern const char *T_date_Days;
extern const char *T_date_Day_of_month;
extern const char *T_date_Day_of_year;
extern const char *T_date_Month;
extern const char *T_date_Year;
extern const char *T_date_Years;
extern const char *T_date_Date;
extern const char *T_date_Sunday;
extern const char *T_date_Monday;
extern const char *T_date_Tuesday;
extern const char *T_date_Wednesday;
extern const char *T_date_Thursday;
extern const char *T_date_Friday;
extern const char *T_date_Saturday;

#endif

