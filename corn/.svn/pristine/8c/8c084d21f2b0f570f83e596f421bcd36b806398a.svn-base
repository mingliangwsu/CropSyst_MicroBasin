#if (!defined(_WIN32) && ! defined(_WIN64))
#error Windows only
// These functions are only available under development environments for Windows
// For Linux or other, use request_cURL.hpp
#endif
#ifndef request_WinINetHPP
#define request_WinINetHPP

#include <Windows.h>
#include <string>
#include <stdio.h>
#include "corn/OS/uniform_resource_identifier.h"

namespace CORN     {
namespace Internet {
#include "CORN/Internet/HTTP/request_WinINet.h"
//______________________________________________________________________________
extern bool WinINet_request_to_string
   (int Method
   ,LPCSTR Host, LPCSTR url, LPCSTR header, LPSTR data
   ,std::string &result);
//_2016-10-18___________________________________________________________________
extern bool WinINet_request_URI_to_stream
   (int Method
   ,const CORN::OS::Uniform_resource_identifier &URI
   ,LPCSTR header, LPSTR data
   ,std::ostream &write_stream );
//_2016-08-02___________________________________________________________________
extern bool WinINet_request_URI_to_FILE
   (int Method
   ,const CORN::OS::Uniform_resource_identifier &URI
   ,LPCSTR header, LPSTR data
   ,FILE *to_file);
//_2016-10-18___________________________________________________________________
} // namespace CORN
} // namespace Internet
#endif
