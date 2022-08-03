#ifndef context_directory_OS_FSH
#define context_directory_OS_FSH

#include "corn/application/project_directory_OS_FS.h"
#include "corn/OS/file_system_types.h"
namespace CORN
{
namespace OS_FS
{
//______________________________________________________________________________
class Context_directory
: public extends_ CORN::OS::Directory_name_concrete
{
   provided_ Project_directory  *project_directory;
 public: // structors
   Context_directory();
      // constructor sets up context to CWD
   Context_directory
      (const CORN::OS::Directory_entry_name &DEN
      ,CORN::OS::Directory_entry_type DEN_type);
      // constructor sets up context.
      // If the directory entry name (DEN) is a file.
      // the context directory is the parent directory of the file.
      // If the DEN is a directory, that directory is the context.
 public:
   virtual Project_directory  *provide_project_directory()            provision_;
      // Attempts to find the current project directory that might be
      // either this directory or more likely an ancestor of this directory.
      // \return 0 if no project could be found.
 protected: // provide project support methods
   virtual Project_directory *render_project_directory
      (const CORN::OS::Directory_name &dir_name,bool create_now_if_needed)  rendition_=0;
      // Derived classes must override this to render the specific project directory type
   virtual const wchar_t *get_canonical_project_file_name()                const =0;
   virtual bool is_project_directory(const CORN::OS::Directory_name &dir_name) affirmation_;
      // A project directory is identified by either:
      //    A directory containing a canonical project filename (I.e. for CropSyst .CS_project file)
      //    A directory containing a desktop.ini with an section and entry
      //       with a section [.ShellClassInfo]
      //       with an entry: context=project
      // Derived class projects may have other or additional criteria.
   Project_directory *find_project_directory(const CORN::OS::Directory_name *current_dir) rendition_;
      // returns 0 if not found otherwise find renders


};
//_2014-01-25___________________________________________________________________
} } // namespace CORN OS_FS
#endif
