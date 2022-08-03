#ifndef requestHPP
#define requestHPP

#include "corn/Internet/HTTP/request.h"


// Using these macros will allow code to support
// both Windows and non-Windows (Linux) platforms

#if (defined(_WIN32)  || defined(_WIN64))
// BCplusplus, MSVisualStudio and MinG compilers provide WinINet library
#include "corn/Internet/HTTP/request_WinINet.hpp"
#define REQUEST_TO_STRING WinINet_request_to_string
#define REQUEST_URI_TO_STRING WinINet_request_URI_to_string
//NYI #define REQUEST_TO_CSTR   WinINet_request_URI_to_cstr
#define REQUEST_URI_TO_STREAM WinINet_request_URI_to_stream
#define REQUEST_URI_TO_FILE   WinINet_request_URI_to_FILE
#else
// cURL is available for everybody else
#include "corn/Internet/HTTP/request_cURL.hpp"
#define REQUEST_URI_TO_STRING cURL_request_URI_to_string
//NYI #define REQUEST_TO_CSTR   cURL_request_URI_to_cstr
#define REQUEST_URI_TO_STREAM cURL_request_URI_to_stream
#define REQUEST_URI_TO_FILE   cURL_request_URI_to_FILE
#endif
#endif
