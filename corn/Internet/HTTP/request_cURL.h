#ifndef request_cURLH
#define request_cURLH

#define POST 1
#define GET 0
/*_________________________________________________________________________*/
extern bool cURL_request_to_cstr
   (int Method
   , const char */*LPCSTR*/ Host
   , const char */*LPCSTR*/ url
   , const char */*LPCSTR*/ header
   , char */*LPSTR*/  data
   ,char *result);
/*_________________________________________________________________________*/
#endif

