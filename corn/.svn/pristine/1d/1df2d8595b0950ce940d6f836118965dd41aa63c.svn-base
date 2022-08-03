#include "corn/chronometry/date_time_A.h"
#include <assert.h>
namespace CORN {
//______________________________________________________________________________
Date_time_abstract::Date_time_abstract()
{}
//______________________________________________________________________________
const std::string &Date_time_abstract::append_to_string
(std::string &target
,const Date_format *from_date_format                                             //180624
,const Time_format *from_time_format)                                      const //180624
{
   ref_date().append_to_string(target,from_date_format,from_time_format);
   std::string time_str;                                                         //171017
   ref_time().append_to_string(time_str,0,from_time_format/*NYI,from_time_format*/);//171017
   if (time_str.length())                                                        //171017
   {  target += "T"; // ISO format separates with T                              //180208_171017
      target += time_str;                                                        //171017
   }
   return target;
}
//_append_to_string______________________________________2014-11-20_2014-06-15_/
DOY Date_time_abstract::get_DOY()                                          const
   // extracts the day of year from the Date date
{  return ref_date().get_DOY();
}
//_get_DOY__________________________________________________________2017-08-15_/
// assignations
datetime64 Date_time_abstract::set_now()
{
   mod_date().set_now();
   mod_time().set_now();
   return get_datetime64();
}
//_170815_____________________________________________________________set_now__/
datetime64 Date_time_abstract::set_c_str
(const char *date_time_str
,const Date_format *from_date_format                                             //180625
,const Time_format *from_time_format)                               assignation_ //180625
{
    mod_date().set_c_str(date_time_str,from_date_format);                        //180625

    //continue here need to implement
    // need to get the time pos and mod_time() for the time substring!!!

   return get_datetime64();
}
//______________________________________________________________________________
} // namespace CORN
