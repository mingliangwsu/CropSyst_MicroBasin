#ifndef HTML_CONTENT_H
#define HTML_CONTENT_H
#include <string>
#ifndef labeled_enumH
#include <corn/labeled_enum.h>
#endif
/* now presume this is the same directory the program is in
#ifdef NONSTANDARD_CGI
#error
#define CGI_dir "c:\\httpd\\cgi-dos\\"
#else
#define CGI_dir ""
                    // The current working directory
                    // which will usually be the cgi-bin directory /home/webmaster/cgi-bin/
#endif
*/
/*_980426*/ enum Request_method {REQUEST_DEBUG,GET,POST};
            extern const char *request_method_label_table[];
            DECLARE_LABELED_ENUM(Request_method_labeled,Request_method,request_method_label_table);

#define CONTENT_TYPE_TEXT "text/plain"
#define CONTENT_TYPE_HTML "text/html"
#define CONTENT_TYPE_VRML "x-\?\?\?/x-vrml"

extern char x2c(const char *what);
extern void unescape_url(std::string &url);
extern void replace_with(std::string &str,char oldc, char newc);

#endif

