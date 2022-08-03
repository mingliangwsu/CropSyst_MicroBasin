#ifndef adjunct_directory_OS_FSH
#define adjunct_directory_OS_FSH
#  include "corn/OS/file_system_logical.h"
#  include "corn/OS/directory_entry_name_concrete.h"
namespace CORN    {
namespace OS_FS   {
//______________________________________________________________________________
class Adjunct_directory
: public extends_ OS::File_system_logical::Directory  // may eventually make this
{protected:
   OS::File_name_concrete *associated_program_filename_qualified;
      // rename this to associated filename, because the adjunct directory
      // may not necessariy be a program.
 public: // could be protected, but may be generally useful, and it is idempotent
   Adjunct_directory
      (const OS::Directory_entry_name &_associated_program_filename_qualified_or_program_dir
      ,bool create_now_if_needed);                                               //130116
   const OS::File_name *find_and_render_file_extension
      (const wchar_t *filename_unqualified_no_ext)                        const;
      // This searches the program directory for a file with the specified
      // name with any extension and if found assigns this to target_fileame.
      // Returns true if anything is found and assigned to the target.
   const OS::File_name &provide_associated_program_filename_qualified() provision_;
 public:
   inline virtual bool find_and_setup_file_extensions()             modification_{ return true;};
      // overridden by derived classes
};
//______________________________________________________________________________
}; // namespace OS_FS
}; // namespace CORN
#endif
