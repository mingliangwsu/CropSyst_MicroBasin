#include "corn/chronometry/date_const.hpp"
/*
   Include this file in your project if you want to use static
   phrases text in your program.

   If you don't include this file in your project,
   You will need to provide and instance of
   RUI::common_translator("phrase_directory")
   global variable in your program.

   phrase_directory can be located any where,
   usually a subdirectory of your program's home directory.
*/

namespace CORN
{
bool        date_phrases_setup = false;                                          //170525
const char *T_date_Day            = "Day";
const char *T_date_Days           = "Days";
const char *T_date_Day_of_month   = "Day of the month";
const char *T_date_Day_of_year    = "Day of the year";
const char *T_date_Month          = "Month";
const char *T_date_Year           = "Year";
const char *T_date_Years          = "Years";
const char *T_date_Date           = "Date";
const char *T_date_Sunday         = "Sunday";
const char *T_date_Monday         = "Monday";
const char *T_date_Tuesday        = "Tuesday";
const char *T_date_Wednesday      = "Wednesday";
const char *T_date_Thursday       = "Thursday";
const char *T_date_Friday         = "Friday";
const char *T_date_Saturday       = "Saturday";

//______________________________________________________________________________
/*180628 obsolete now usings static autoinitialization
void date_setup_phrases()
{
   // I dont really like this because it requires main() to call this function
   // But it allows foreign language overriding.
   date_phrases_setup =true;
   date_month_abbrevs[1]   = "Jan";
   date_month_abbrevs[2]   = "Feb";
   date_month_abbrevs[3]   = "Mar";
   date_month_abbrevs[4]   = "Apr";
   date_month_abbrevs[5]   = "May";
   date_month_abbrevs[6]   = "Jun";
   date_month_abbrevs[7]   = "Jul";
   date_month_abbrevs[8]   = "Aug";
   date_month_abbrevs[9]   = "Sep";
   date_month_abbrevs[10]  = "Oct";
   date_month_abbrevs[11]  = "Nov";
   date_month_abbrevs[12]  = "Dec";

   date_month_names[1]     = "January";
   date_month_names[2]     = "February";
   date_month_names[3]     = "March";
   date_month_names[4]     = "April";
   date_month_names[5]     = "May";
   date_month_names[6]     = "June";
   date_month_names[7]     = "July";
   date_month_names[8]     = "August";
   date_month_names[9]     = "September";
   date_month_names[10]    = "October";
   date_month_names[11]    = "November";
   date_month_names[12]    = "December";

   T_date_Sunday      = "Sunday";
   T_date_Monday      = "Monday";
   T_date_Tuesday     = "Tuesday";
   T_date_Wednesday   = "Wednesday";
   T_date_Thursday    = "Thursday";
   T_date_Friday      = "Friday";
   T_date_Saturday    = "Saturday";

   T_date_Day         = "Day";
   T_date_Days        = "Days";
   T_date_Day_of_month= "Day of the month";
   T_date_Day_of_year = "Day of the year";
   T_date_Month       = "Month";
   T_date_Year        = "Year";
   T_date_Years       = "Years";
   T_date_Date        = "Date";
};
*/

//______________________________________________________________________________
} // namespace CORN

