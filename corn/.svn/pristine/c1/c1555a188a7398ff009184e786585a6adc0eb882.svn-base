#ifndef ISAI_form_IOH
#define ISAI_form_IOH

#include "corn/format/HTML/form_IO/common_form_IO.h"
#include "corn/format/HTML/form_IO/content.h"

class TEXTENSION_CONTROL_BLOCK;

namespace HTML
{
//______________________________________________________________________________
class ISAPI_form_IO
: virtual public Common_form_IO
{
  TEXTENSION_CONTROL_BLOCK * LpEcb;
 public:
   inline ISAPI_form_IO(TEXTENSION_CONTROL_BLOCK * i_LpEcb)
      : Common_form_IO()
      , LpEcb(i_LpEcb)
      {}
 protected:
   virtual bool get_content(CORN::Ustring &content, CORN::Ustring &error_message);     //030411
   virtual Request_method get_request_method();
 public:
   virtual void write_error(const char *message1);
   virtual void write_line(const char *line);
};
//______________________________________________________________________________
} // namespace HTML

#endif
