#include "corn/application/adjunct_directory_OS_FS.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include <assert.h>
//______________________________________________________________________________
namespace CORN    {
namespace OS_FS   {
//______________________________________________________________________________

Adjunct_directory::Adjunct_directory
(const OS::Directory_entry_name &_associated_program_filename_qualified_or_program_dir
,bool create_now_if_needed
)
: OS::File_system_logical::Directory
(_associated_program_filename_qualified_or_program_dir
/* If the parameter is a directory name then we simply use that name.
   Otherwise the directory takes the same name as the file.
   (we strip the extension below)*/

,_associated_program_filename_qualified_or_program_dir.is_directory()
? create_now_if_needed :false)
, associated_program_filename_qualified(0)
{
   if (_associated_program_filename_qualified_or_program_dir.is_file())
   {  extension.clear();                                                         //131207
      clear();                                                                   //140422
      construction_compose();                                                    //140422
      associated_program_filename_qualified =
         new OS::File_name_concrete
            (_associated_program_filename_qualified_or_program_dir);
   }
   else
      associated_program_filename_qualified =
            new OS::File_name_concrete(*this//_associated_program_filename_qualified_or_program_dir
            ,_associated_program_filename_qualified_or_program_dir.get_name()
            ,std::wstring(L"EXE"));

}
//_2012-03-19______________________________________________________constructor_/
const OS::File_name &Adjunct_directory::provide_associated_program_filename_qualified() provision_
{
   assert(false); // Not yet implemented
   return *associated_program_filename_qualified;
}
//_2012-03-19____________________provide_associated_program_filename_qualified_/
const OS::File_name *Adjunct_directory::find_and_render_file_extension
      (const wchar_t *filename_unqualified_no_ext)                         const
{
   assert(false); // Not yet implemented
      // This searches the program directory for a file with the specified
      // name with any extension and if found assigns this to target_fileame.
      // Returns true if anything is found and assigned to the target.
   return 0;
}
//_2012-03-19__________________________________find_and_render_file_extension__/
} // namespace OS_FS
} // namespace CORN

