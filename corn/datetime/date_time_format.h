/*141120 obsolete because now the Date time classes keep separate date and time format


#ifndef date_time_formatH
#define date_time_formatH
#include "corn/datetime/date_format.h"
#include "corn/datetime/time_format.h"
namespace CORN
{  // Currently presuming date always preceeds time
//______________________________________________________________________________
class XDate_time_format
: public Date_format
, public Time_format
{
public:
   XDate_time_format();
   XDate_time_format(const Date_format &_date_format,const Time_format &_time_format);
   XDate_time_format(const Date_time_format &_date_format);
   XDate_time_format(const char *format_string);
   virtual bool set_format_string(const std::string& format_string) contribution_;//141120
   virtual bool set_format_cstr  (const char *       format_string) contribution_;//141120
};
//______________________________________________________________________________
} // namespace CORN

#endif
*/

