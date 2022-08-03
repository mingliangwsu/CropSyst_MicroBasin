#include "CS_application_directory.h"
#include "CS_suite/application/CS_suite_directory.h"
namespace CS {
//______________________________________________________________________________
Application_directory::Application_directory
(const wchar_t *directory_name)
: CORN::OS_FS::Application_directory(directory_name/*,documentation_index_filename*/)
,CS_Suite_directory(0),  CS_Suite_directory_owned(true)
{}
//________________________________________________________________constructor__/
Application_directory::Application_directory
(const CS::Suite_Directory *_CS_Suite_directory
,const wchar_t *directory_name)
: CORN::OS_FS::Application_directory(*_CS_Suite_directory,directory_name)
,CS_Suite_directory(const_cast<CS::Suite_Directory *>(_CS_Suite_directory)),  CS_Suite_directory_owned(false)
{}
//_2014-10-10_____________________________________________________constructor__/
Application_directory::Application_directory
(const OS::Directory_name &path
,const wchar_t *directory_name)
: CORN::OS_FS::Application_directory
   (path,directory_name)
{}
//_2014-10-10_____________________________________________________constructor__/
const // 141119
CS::Suite_Directory &Application_directory::provide_CS_Suite_directory() provision_
{  if (!CS::Suite_directory)
   {  CS_Suite_directory = new CS::Suite_Directory(*provide_suite_directory_const());//141119 
      // For CropSyst we are guarenteed to have a suite directory
      // NYI const char *documentation_index_filename
      CS_Suite_directory_owned = true;
   }
   return *CS_Suite_directory;
}
//_________________________________________________provide_CS_Suite_directory__/
}; // namespace CS

