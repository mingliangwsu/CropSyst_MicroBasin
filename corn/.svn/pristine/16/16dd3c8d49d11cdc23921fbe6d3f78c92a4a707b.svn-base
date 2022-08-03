#ifndef documentorH
#define documentorH
#include "corn/const.h"
namespace CORN {
namespace OS
{  class Uniform_resource_locator;
}
namespace OS_FS
{  class Documentation_directory;
}
//______________________________________________________________________________
class Documentor
{
   cognate_ const CORN::OS_FS::Documentation_directory *documentation_directory;
   cognate_ CORN::OS::Uniform_resource_locator   *URL_root;
 public:
   Documentor();
   bool know_documentation_directory
      (const CORN::OS_FS::Documentation_directory *_documentation_directory
      ,const char *URL_root = 0)                                     cognition_;
      // URL root is the (usually) http path to the application directory
      // (The parent of the documentation directory, which is often the same
      // where the documentation directory is often the same
      // as the program's associated directory).
      // I.e.  http://www.bsyse.wsu.edu/CS_Suite_4/CropSyst
      // where the program directory is
      //       http://www.bsyse.wsu.edu/CS_Suite_4/CropSyst/crop_editor

   CORN::OS::Uniform_resource_locator *render_context_sensitive_help
      (const char *partially_qualified_URI)                          rendition_;
   bool view_context_sensitive_help(const char *help_URI)                 const;
};
//_2013-11-18___________________________________________________________________
extern Documentor documentor;
} // namespace CORN
#endif
