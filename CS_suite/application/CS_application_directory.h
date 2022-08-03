#ifndef CS_application_directoryH
#define CS_application_directoryH
//---------------------------------------------------------------------------
#include "corn/application/application_directory_OS_FS.h"
using namespace CORN::OS;
namespace CS
{
class Suite_Directory;  //forward decl
//______________________________________________________________________________
class Application_directory        // May want to have CropSyst namespace and name this CropSyst::Application_directory
: public
   CORN::OS_FS::Application_directory
{  // This is an abstract class for CropSyst_directory and CANMS_directory.
protected:
   provided_ CS::Suite_Directory *CS_Suite_directory;  provided_ bool CS_Suite_directory_owned;
public: // 'structors
   Application_directory(const wchar_t *directory_name);
   Application_directory
      (const CS::Suite_Directory *CS_Suite_directory
      ,const wchar_t *directory_name);
   Application_directory
      (const CORN::OS::Directory_name &path
      ,const wchar_t *directory_name);
public:
   const //141119 
   CS::Suite_Directory &provide_CS_Suite_directory()                   provision_;
};
//______________________________________________________________________________
};
#endif
