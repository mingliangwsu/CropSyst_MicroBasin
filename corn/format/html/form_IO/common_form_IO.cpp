#include "corn/format/HTML/form_IO/common_form_IO.h"
#include "corn/std/std_fstream.h"

namespace HTML
{
//______________________________________________________________________________
Common_form_IO::Common_form_IO()
{}
//______________________________________________________________________________
bool Common_form_IO::initialize()
{
   std::string get_errors;
   return get_content(get_form_request().content,get_errors) &&
          convert_content_to_data_record();
}
//______________________________________________________________________________
bool Common_form_IO::process()
{
   std::string error_buffer;
   bool valid = get_form_request().validate(error_buffer);
   if (valid)
   {
      std::string reply;
      generate_reply(reply);
      cout << reply;
   }
   else
      write_error(error_buffer.c_str());
   return valid;
};
//______________________________________________________________________________
}
//______________________________________________________________________________

