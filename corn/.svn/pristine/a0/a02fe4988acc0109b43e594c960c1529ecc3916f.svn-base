#ifndef date_time_AH
#define date_time_AH
#include "corn/chronometry/date_time_I.h"
#include "corn/chronometry/date_A.h"
#include "corn/chronometry/time_A.h"
namespace CORN {
//______________________________________________________________________________
class Date_time_abstract
: public implements_ Date_time
{
 public:
   Date_time_abstract();
 public: // conversions
   virtual const std::string &append_to_string
      (std::string &target
      ,const Date_format *target_date_format/*=0*/                               //180624
      ,const Time_format *target_time_format/*=0*/)                       const;
   virtual datetime64 set_c_str
      (const char *date_time_str
      ,const Date_format *from_date_format=0                                     //180625
      ,const Time_format *from_time_format=0)                      assignation_; //180625
   virtual DOY get_DOY()                                                  const;
 public: // assignations
   virtual datetime64 set_now();
};
//______________________________________________________________________________
} // namespace CORN
#endif
