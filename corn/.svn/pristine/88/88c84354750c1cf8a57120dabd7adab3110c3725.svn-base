#ifndef common_form_IOH
#define common_form_IOH

#include "corn/format/HTML/form_IO/HTML_form_request.h"
#include "corn/format/HTML/form_IO/content.h"
namespace HTML
{
//______________________________________________________________________________
class Common_form_IO
{
protected:
   virtual bool get_content(std::string &content, std::string &error_message) = 0; //030411
   virtual bool generate_reply(std::string &reply) = 0;                        //030418
   virtual bool convert_content_to_data_record() = 0;
   virtual HTML_form_request &get_form_request() = 0;
public:
   Common_form_IO();
   virtual bool process();
   virtual Request_method get_request_method() = 0;
   bool initialize();
   virtual void write_error(const char *message1/*, const char *message2*/) = 0;
   virtual void write_line(const char *line)=0;
};
//______________________________________________________________________________
} // namespace HTML
#endif

