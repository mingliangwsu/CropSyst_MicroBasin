#ifndef request_cURLHPP
#define request_cURLHPP

#include "corn/OS/uniform_resource_identifier.h"
// These functions are for use with the cURL library
// which is available for all/most platforms (Linux).
// However for Windows it is recommended to use the request_WinINet version.
namespace CORN     {
namespace Internet {
//______________________________________________________________________________
extern bool cURL_request_URI_to_FILE
   (int Method
   ,const CORN::OS::Uniform_resource_identifier &URI
   ,const char *header, char *data
   ,FILE *to_file);
//_2016-10-18___________________________________________________________________
bool cURL_request_URI_to_stream
   (int Method
   ,const CORN::OS::Uniform_resource_identifier &URI
   ,const char *header, char *data
   ,std::ostream &to_stream);
//_2016-10-18___________________________________________________________________
} // namespace CORN
} // namespace Internet
#endif
