#include "corn/application/documentor.h"
#include "corn/OS/file_system_engine.h"
#include "corn/OS/uniform_resource_locator.h"
#include "corn/application/documentation_directory_OS_FS.h"
#include <assert.h>
#ifdef _WIN32
#include <shlobj.h>
#endif
namespace CORN {
//______________________________________________________________________________
Documentor::Documentor()
: documentation_directory(0)
{}
//_2013-11-18___________________________________________________________________
bool Documentor::know_documentation_directory
(const CORN::OS_FS::Documentation_directory *_documentation_directory
,const char *_URL_root)                                               cognition_
{  documentation_directory = _documentation_directory;
   if (_URL_root)
      URL_root = new CORN::OS::Uniform_resource_locator(_URL_root);
   return true;
}
//_2013-11-08___________________________________________________________________
CORN::OS::Uniform_resource_locator *Documentor::render_context_sensitive_help
(const char *partially_qualified_URI)                                 rendition_
{  if (!partially_qualified_URI) return 0;
   return new CORN::OS::Uniform_resource_locator
      (partially_qualified_URI
      /*150803 ,documentation_directory*/);
}
//_2013-11-18___________________________________________________________________
bool Documentor::view_context_sensitive_help(const char *help_URI)         const
{  CORN::OS::Uniform_resource_locator *help_URL
      = render_context_sensitive_help(help_URI);
   bool viewed = help_URL;
   if (help_URL)
   {  const CORN::OS::File_name *local_fname = help_URL->find_local_file_name
         (documentation_directory);                                              //150803
      viewed = local_fname;
      if (local_fname)
         viewed = CORN::OS::file_system_engine.view_file(*local_fname);
      else if (URL_root)
      {
         std::wstring HTTP_URL;
         CORN::string_to_wstring(URL_root->c_str(),HTTP_URL);
         HTTP_URL.append(L"/");
         documentation_directory->append_name_with_extension_to(HTTP_URL);
         HTTP_URL.append(L"/");
         // Currently context sensitive help is relative to
         // the editor program's associated manual directory
         documentation_directory->manual().append_name_with_extension_to(HTTP_URL);
         HTTP_URL.append(L"/");
         CORN::append_ASCIIZ_to_wstring(help_URI,HTTP_URL);
         #ifdef _WIN32
         return (int)ShellExecuteW(0,L"open",HTTP_URL.c_str(),NULL,NULL,SW_SHOW)>32;
         #else
         /// NYI  need to have Web context  (URI)
         assert(false);
         viewed = false;
         #endif
      } else viewed = false;
      delete help_URL;
   }
   return viewed;
}
//_2013-11-19___________________________________________________________________
Documentor documentor;
} // namespace CORN

