

#include <corn/format/HTML/form_IO/ISAPI_form_IO.h>
#include <stdio.h>

namespace HTML
{
/*030411_*/ bool ISAPI_form_IO::get_content(CORN_string &content,CORN_string &error_message)
/*______*/  {  bool result = true;
#ifdef NYI

/*______*/     switch (get_request_method())
/*______*/     {
/*______*/        case REQUEST_DEBUG :
/*______*/        {
/*______*/          content.assign("package=cropsyst&version=3.02.15&notify=rnelson@mail.wsu.edu&"
                           "contact=Roger+Nelson+(ph:+509-335-1100+rnelson@mail.wsu.edu)&"
/*______*/                 "listserv=listserv@c100.bsyse.wsu.edu&listserv_add_command=add+cropsyst&"
/*______*/                 "database=cropsyst&name=test+name&title=test+title&institution=test+institution&department=test+dept&address=test+address"
/*______*/                 "&city=test+city&state=test+state&zip=test+zip&country=test+country&phone=test+phone&fax=test+fax&email=test@email&WWWpage=test+www+page&plans=test+plans");
/*______*/        } break;
/*______*/        case POST :
/*______*/        {
/*______*/           int content_length = atoi(getenv("CONTENT_LENGTH"));
/*030415*/           char *buffer = new char[content_length+1];
#ifdef NONSTANDARD_CGI
/*______*/           // CONTENT_TYPE is only provided by web serv
/*______*/           if(strcmp(getenv("CONTENT_TYPE"),"application/x-www-form-urlencoded"))
/*______*/           {  out_stream << "This script can only be used to decode form results." << endl;
/*______*/              out_stream << "Content_type:" << getenv("CONTENT_TYPE") << endl;
/*______*/              exit(1);
/*______*/           };
/*030415*/
/*030415*/           FILE *content_stream;
/*030415*/           if ((content_stream = fopen(getenv("CONTENT_FILE"), "r"))!= NULL)
/*030415*/           {
/*030415*/              fread((void *)buffer,content_length,1,content_stream);
/*030415*/           };
#else
/*030415*/           fread((void *)buffer,content_length,1,stdin);
#endif
/*030415*/           buffer[content_length] = 0;
/*030415*/           content.assign(buffer);
/*______*/        }
/*______*/        break;
/*______*/        case GET :
/*______*/        { // For some reason = is changed to ~ in QUERY_STRING!
/*______*/           CORN_string query_string(getenv("QUERY_STRING"));
/*______*/           replace_with(query_string,'~','=');
/*030411*/           content.assign(query_string);
/*______*/        }
/*______*/        break;
/*______*/        default :
/*______*/        {
/*______*/           error_message.append("This script must be activated by form submission.\n");
/*______*/           error_message.append("It was submitted by:");
/*______*/           error_message.append(getenv("REQUEST_METHOD"));
//obs                   out_stream << "This script must be activated by form submission." << endl;
//obs/*______*/           out_stream << "It was submitted by:" << getenv("REQUEST_METHOD") << endl;
/*______*/           result = false;
///*______*/           exit(1);
/*______*/        };
/*______*/     };
#endif
/*020208*/     return result;
/*______*/  };

/*_______*/ Request_method ISAPI_form_IO::get_request_method()
            {
//NYI               return request_method_labeled.get();
            }

/*______*/ CGI_form_IO::CGI_form_IO(/*HTML_form_request &form_request,*/bool i_cached, char *content_type)
/*______*/ :Common_form_IO()
/*______*/ ,cached(i_cached)
#ifdef local_debug
/*______*/ ,out_stream(new ofstream("debug.htm"))
#else
#  ifdef NONSTANDARD_CGI
/*______*/ ,out_stream(new ofstream(getenv("OUTPUT_FILE")))
#  else
            ,out_stream(&cout)
#  endif
#endif
/*______*/ {
#ifdef NYI
/*______*/     char *env_request_method = getenv("REQUEST_METHOD");
/*______*/     if (env_request_method)
/*______*/        request_method_labeled.set_label(env_request_method);
/*______*/    content_init(content_type);
#endif
/*______*/ };
/*______*/ void ISAPI_form_IO::content_init(char *content_type)
/*______*/ {
#ifdef NYI
/*______*/      *out_stream << "Content-type: " << content_type << endl;
/*______*/      if (!cached)
/*______*/         *out_stream << "Pragma: no-cache" << endl;
/*______*/      *out_stream << endl << endl;
#endif
/*______*/ };

/*______*/ void ISAPI_form_IO::write_error(const char *message1/*, const char *message2*/)
/*______*/ {
#ifdef NYI
/*______*/   // make this page look pretty
///*______*/   out_stream << "<H2>" << endl;
/*______*/   *out_stream << message1 << endl;
///*______*/   if (message2) out_stream << message2;
///*______*/   out_stream << "</H2>" <<endl;
#endif
/*______*/ };

/*______*/ void CGI_form_IO::write_line(const char *line)
/*______*/ {
#ifdef NYI
/*______*/    *out_stream << line << endl;
#endif
/*______*/ };





