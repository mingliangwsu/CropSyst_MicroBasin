#ifndef requestH
#define requestH

#define POST 1
#define GET 0

// Using these macros will allow code to support
// both Windows and non-Windows (Linux) platforms
//______________________________________________________________________________
#if (defined(_WIN32)  || defined(_WIN64))
// BCplusplus, MSVisualStudio and MinG compilers provide WinINet library
#include "corn/Internet/HTTP/request_WinINet.h"
#define REQUEST_TO_CSTR   WinINet_request_to_cstr
#else
#include "corn/Internet/HTTP/request_cURL.h"
#define REQUEST_TO_CSTR   cURL_request_to_cstr
// cURL is available for everybody else
#endif
//_2014-08-04___________________________________________________________________
#endif
