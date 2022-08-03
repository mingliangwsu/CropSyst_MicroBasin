#include "corn/format/HTML/form_IO/cgi_form_io.h"
#include <stdio.h>
namespace CORN
{
namespace HTML
{
//_2003-04-11___________________________________________________________________
bool CGI_form_IO::get_content(CORN_string &content,CORN_string &error_message)
{  bool result = true;
   switch (get_request_method())
   {
      case REQUEST_DEBUG :
      {
        content.assign("package=cropsyst&version=3.02.15&notify=rnelson@mail.wsu.edu&"
               "contact=Roger+Nelson+(ph:+509-335-1100+rnelson@mail.wsu.edu)&"
               "listserv=listserv@c100.bsyse.wsu.edu&listserv_add_command=add+cropsyst&"
               "database=cropsyst&name=test+name&title=test+title&institution=test+institution&department=test+dept&address=test+address"
               "&city=test+city&state=test+state&zip=test+zip&country=test+country&phone=test+phone&fax=test+fax&email=test@email&WWWpage=test+www+page&plans=test+plans");
      } break;
      case POST :
      {
         int content_length = atoi(getenv("CONTENT_LENGTH"));
         char *buffer = new char[content_length+1];                              //030415
         #ifdef NONSTANDARD_CGI
         // CONTENT_TYPE is only provided by web serv
         if(strcmp(getenv("CONTENT_TYPE"),"application/x-www-form-urlencoded"))
         {  out_stream << "This script can only be used to decode form results." << endl;
            out_stream << "Content_type:" << getenv("CONTENT_TYPE") << endl;
            exit(1);
         }
         FILE *content_stream;                                                   //030415
         if ((content_stream = fopen(getenv("CONTENT_FILE"), "r"))!= NULL)       //030415
            fread((void *)buffer,content_length,1,content_stream);               //030415
         #else
            fread((void *)buffer,content_length,1,stdin);                        //030415
         #endif
         buffer[content_length] = 0;                                             //030415
         content.assign(buffer);                                                 //030415
      }
       break;
       case GET :
       { // For some reason = is changed to ~ in QUERY_STRING!
          CORN_string query_string(getenv("QUERY_STRING"));
          replace_with(query_string,'~','=');
          content.assign(query_string);                                           //030411
       }
       break;
       default :
       {
          error_message.append("This script must be activated by form submission.\n");
          error_message.append("It was submitted by:");
          error_message.append(getenv("REQUEST_METHOD"));
         result = false;
      }
   }
   return result;                                                                //020208
}
//_2003-04-11___________________________________________________________________
Request_method CGI_form_IO::get_request_method()
{  return request_method_labeled.get();
}
//______________________________________________________________________________
CGI_form_IO::CGI_form_IO(/*HTML_form_request &form_request,*/bool i_cached, char *content_type)
:Common_form_IO()
,cached(i_cached)
{   char *env_request_method = getenv("REQUEST_METHOD");
    if (env_request_method)
       request_method_labeled.set_label(env_request_method);
   content_init(content_type);
}
//______________________________________________________________________________
void CGI_form_IO::content_init(char *content_type)
{
    #ifdef NOT_VALID
    char *user_agent = getenv("HTTP_USER_AGENT");
    std::cout << "HTTP_USER_AGENT = " <<(user_agent ? user_agent : "Unknown\n");
    char *http_host= getenv("HTTP_HOST");
    std::cout << "HTTP_HOST = " << (http_host ? http_host : "Unknown\n");
    #endif
    std::cout << "Content-type: " << content_type << endl << endl;

    // Pragma is being displayed, so not part of header.
    ///*______*/     if (!cached)
    ///*______*/         cout /**out_stream*/<< "Pragma: no-cache" << endl;
    std::cout << endl << endl;
}
//______________________________________________________________________________
void CGI_form_IO::write_error(const char *message1/*, const char *message2*/)
{
  // make this page look pretty
    std::cout << message1 << endl;
}
//______________________________________________________________________________
void CGI_form_IO::write_line(const char *line)
{
   std::cout << line << endl;
}
//______________________________________________________________________________
CGI_form_IO::~CGI_form_IO()
{
#ifdef NONSTANDARD_CGI
   out_stream->close();
#endif
}
//______________________________________________________________________________
} // namespace HTML
} // namespace CORN
