#include "corn/OS/uniform_resource_locator.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/OS/file_system_engine.h"
#include "corn/OS/file_system_logical.h"

#include <assert.h>
namespace CORN { namespace OS {
//______________________________________________________________________________
Uniform_resource_locator::Uniform_resource_locator
      (const Uniform_resource_identifier &_URI)
: Uniform_resource_identifier(_URI)
, local_file_name(0)
{}
//______________________________________________________________________________
Uniform_resource_locator::Uniform_resource_locator
(const char *_URI)
: Uniform_resource_identifier(_URI)
, local_file_name(0)
{}
//______________________________________________________________________________
Uniform_resource_locator::Uniform_resource_locator
(const Uniform_resource_locator &_URL)
: Uniform_resource_identifier(_URL)
, local_file_name(0)
{}
//__________________________________________________________ copy constructor _/
Uniform_resource_locator::Uniform_resource_locator
(const wchar_t *_URL)
: Uniform_resource_identifier(_URL)
, local_file_name(0)
{}
//_______________________________________________________________ constructor _/
const CORN::OS::File_name *Uniform_resource_locator::find_local_file_name
   (const CORN::OS::File_system::Directory *context_directory)        provision_
{
   if (!local_file_name)
   {
      CORN::OS::File_name_concrete *local_file_name_instanciated = 0;
      if (context_directory)
      {
         local_file_name = local_file_name_instanciated = new CORN::OS::File_name_concrete(*context_directory,*path);

         // Attempts to resolve the URL as a filename available on this
         // machine (or mounted drives)
         // returns the provided file name or 0 if the identified
         //file could not be located.
         if (!CORN::OS::file_system_engine.exists(*local_file_name))
         {
            delete local_file_name_instanciated; local_file_name = local_file_name_instanciated = 0;
            std::wstring name_and_ext;
            local_file_name = context_directory->find_file_name
               (path->get_name_with_extension(name_and_ext)
               ,OS::File_system::subdirectory_recursion_inclusive                //150908
               //150908 ,true
               //,OS::Directory_entry_name::full_qualification                     //150908
               // I think these were originally fully qualified,
               // but may want the qualifiction mode optional (add parameter)
               );
            // it is possible the filename doesn't exist at all (return 0)
         }
      } else
      {  CORN::OS::Directory_name_concrete CWD;
         local_file_name = local_file_name_instanciated =new CORN::OS::File_name_concrete(CWD,*path);
         if (!CORN::OS::file_system_engine.exists(*local_file_name) && context_directory)
         {  delete local_file_name_instanciated; local_file_name = local_file_name_instanciated = 0;
            // it is possible the filename doesn't exist at all (return 0)
         }
      }
   }
   return local_file_name;
}
//______________________________________________________________________________
} }// namespace CORN::OS
