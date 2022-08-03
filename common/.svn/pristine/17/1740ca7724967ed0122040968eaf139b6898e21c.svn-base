#ifndef logH
#define logH
#include <fstream>
#include "corn/primitive.h"
#include "corn/chronometry/date_32.h"
//170525 #include "corn/datetime/date.hpp"

//______________________________________________________________________________
class Common_simulation_log
: public std::ofstream
{
public:
   bool     daily;
   bool     detail;
private:
   mutable nat32  log_count;                                                     //110712
   mutable CORN::Date_clad_32  simulation_today;                                 //130823
   public:
      inline void know_today(const CORN::Date_const &today_)          cognition_
         { simulation_today.set(today_); }                                       //130823
public:
   Common_simulation_log(const char *log_filename);
   Common_simulation_log();  // Use this constructor when the file will be open later.
   bool reset();                                                                 //110712
   nat32 record
      (nat32      object_ID    // This is the ID (can be pointer to) of the object reporting this loc record.
      ,const char *prefix
      ,const char *type = 0
      ,const char *description = 0);
   // Outputs:
   //  [prefix_99] (where 99 is the current log count) to the file (1 based index);
   //
   // the caller may output additional text in the format  variable=value
   // returns the log_count number for the created record.

//   inline const CORN::Date &get_date() const { return date; };
//   inline void set_date(const CORN::Date &new_date) {date.set(new_date);};
};
//______________________________________________________________________________

extern Common_simulation_log CS_event_log;
extern nat8 CS_event_log_cycle;

#endif

