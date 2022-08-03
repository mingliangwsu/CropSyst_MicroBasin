#ifndef CGI_form_IOH
#define CGI_form_IOH
#include "corn/format/HTML/form_IO/common_form_IO.h"
#include "corn/format/HTML/form_IO/content.h"
namespace CORN
{
namespace HTML
{
//______________________________________________________________________________
class CGI_form_IO
: public Common_form_IO
{
   bool cached;
   Request_method_labeled request_method_labeled;
protected:
   virtual bool get_content(CORN_string &content, CORN_string &error_message);
   virtual Request_method get_request_method();
   void content_init(char *content_type);
public:
   CGI_form_IO(bool i_cached=true, char *content_type = CONTENT_TYPE_HTML);
   virtual ~CGI_form_IO();
   virtual void write_error(const char *message1);
   virtual void write_line(const char *line);
};
//_2003-04-11___________________________________________________________________
} // namespace HTML
} // namespace CORN
#endif

