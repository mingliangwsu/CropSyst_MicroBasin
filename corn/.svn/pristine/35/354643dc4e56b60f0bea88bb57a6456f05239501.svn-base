#ifndef uniform_resource_locatorH
#define uniform_resource_locatorH
#include "corn/OS/uniform_resource_identifier.h"
#include "corn/OS/file_system.h"
//______________________________________________________________________________
namespace CORN { namespace OS {
//______________________________________________________________________________
class Uniform_resource_locator
: public Uniform_resource_identifier
{
   // cognate_ const CORN::OS::File_system::Directory *context_directory;
 public:
   provided_ CORN::OS::File_name *local_file_name;
      // The URL as resolved as a fully qualified filename resource available
      // locally on this machine.
      // Will be 0 if local file name does not exist.
      // Does not include query and fragment
 public:
   Uniform_resource_locator
      (const Uniform_resource_identifier &_URI);
      // Uniform_resource_locator URI to URL
   Uniform_resource_locator
      (const char *_URI);
      // Uniform_resource_locator URI to URL
   Uniform_resource_locator
      (const Uniform_resource_locator &_URL);
      // copy constructor
   Uniform_resource_locator
      (const wchar_t *_URL);
   const CORN::OS::File_name *find_local_file_name
      (const CORN::OS::File_system::Directory *context_directory)     provision_;//150727
      // Attempts to resolve the URL as a filename available on this
      // machine (or mounted drives)
      // returns the provided file name or 0 if the identified
      // file could not be located.
};
//_2013-11-18___________________________________________________________________
} }// namespace CORN::OS
#endif

