#ifndef CS_context_directoryH
#define CS_context_directoryH
#include "corn/application/context_directory_OS_FS.h"
#include "CS_suite/CropSyst/file_system/project_directory_CropSyst.h"
#include "cs_scenario_directory.h"
//#include "cs_scenario_directory.h"

// This class is being replaced by CS::File_system class
// In V5 there with no longer be .CS_project file
// Instead directory context will be stored in
//
// .directory (Linux) desktop.ini

namespace CS
{

//   class Common_scenario_directory;
//______________________________________________________________________________
class Context_directory
: public extends_ CORN::OS_FS::Context_directory
{
//NYI   provided_ Master_directory       *master_directory;
   provided_ CropSyst::Project_directory  *project_directory;
      // Note that this pointer is an alias to the project directory
      // which is owned by  CORN::OS_FS::Context_directory
      // but of this specific type.
   provided_ Scenario_directory     *scenario_directory;
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
    virtual Project_directory  *provide_project_directory() provision_;
      // Attempts to find the current project directory that might be
      // either this directory or more likely an ancestor of this directory.
      // \return 0 if no project could be found.
      // A project directory is found by either:
      //    A directory containing a .CS_project file
      //    A directory containing a desktop.ini with an section and entry
      //    with a section [.ShellClassInfo]
      //    with an entry: context=project
      //    or an entry IconFile= {path}\folder_project.ico
      //       for exampleC:\CS_Suite_4\Icons\folder_project.ico
      //       (the test for folder_project.ico is for early
      //       version 4 that did not have the context entry
      //       this text will be obsolete in version 5.)
//NYI   provided_ Master_directory   *provided_master_directory()          provision_;
      // Attempts to find the master directory (specified by xxxx)
      // Returns 0 if no such directory.
   Scenario_directory *provide_scenario_directory()         provision_;
      // Attempts to find the current project directory that might be
      // either this directory or more likely an ancestor of this directory.
 protected: // provide project support methods
   inline virtual const wchar_t *get_canonical_project_file_name()                const { return L".CS_project"; }
   #if (CS_VERSION == 4)
   // Obsolete in V5 because all CS contexts directories have context entry
   virtual bool is_project_directory(const CORN::OS::Directory_name &dir_name) affirmation_;
      // Early CropSyst version 4 did not have context entry in the desktop.ini
      // But it did have in the section [.ShellClassInfo] an entry
      //       IconFile= {path}\folder_project.ico
      //          for exampleC:\CS_Suite_4\Icons\folder_project.ico
   #endif
   virtual CS::Project_directory *render_project_directory(const CORN::OS::Directory_name &dir_name,bool create_now_if_needed)            rendition_;

 protected: // provide scenario support methods
   virtual Common_scenario_directory *render_scenario_directory
      (const CORN::OS::Directory_name &dir_name,bool create_now_if_needed)  rendition_=0;
      // Derived classes must override this to render the specific project directory type
   virtual const wchar_t *get_canonical_scenario_file_name()               const { return L".CS_scenario"; }
   virtual bool is_scenario_directory(const CORN::OS::Directory_name &dir_name) affirmation_;
      // A scenario directory is identified by either:
      //    A directory containing a canonical project filename (I.e. for CropSyst .CropSyst_scenario file)
      //    A directory containing a desktop.ini with an section and entry
      //       with a section [.ShellClassInfo]
      //       with an entry: context=scenario
      // Derived class projects may have other or additional criteria.
   Common_scenario_directory *find_scenario_directory(const CORN::OS::Directory_name_concrete *current_dir) rendition_;
      // returns 0 if not found otherwise find renders

};
//_2014-01-25___________________________________________________________________
}
// Need to moved this to another file
//_2014-01-25___________________________________________________________________


namespace CropSyst
{

class Context_directory
: public CS::Context_directory
{
 protected:
   virtual const wchar_t *get_canonical_scenario_file_name()               const { return L".CropSyst_scenario"; } 
   virtual CropSyst::Project_directory *render_project_directory
      (const CORN::OS::Directory_name &dir_name,bool create_now_if_needed) rendition_;
   virtual CropSyst::Scenario_directory *render_scenario_directory
      (const CORN::OS::Directory_name &dir_name,bool create_now_if_needed) rendition_;

};
//_2014-01-25___________________________________________________________________
}




#endif
