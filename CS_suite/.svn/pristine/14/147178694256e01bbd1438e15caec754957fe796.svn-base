#ifndef CANMS_directoryH
#define CANMS_directoryH
//______________________________________________________________________________
#include "corn/OS/directory_entry_name_concrete.h"
#include "CS_suite/application/CS_application_directory.h"
//_______________________________________________________Forward_declarations__/
namespace CS
{
class CANMS_Directory;
//______________________________________________________________________________

class CANMS_Database_directory            // Eventually derive the from CropSyst_Database_directory
: public extends_ CORN::OS::File_system_logical::Directory                       //140313
{private:
   provided_ CORN::OS::Directory_name *equipment_directory;
   provided_ CORN::OS::Directory_name *facility_directory;
   provided_ CORN::OS::Directory_name *feed_directory;
 public: // 'structors
   CANMS_Database_directory(const CANMS_Directory  &CANMS_dir);
   const CORN::OS::Directory_name &Equipment()                       provision_;
   const CORN::OS::Directory_name &Facility()                        provision_;
   const CORN::OS::Directory_name &Feed()                            provision_;
};
//______________________________________________________________________________
class CANMS_Directory        // May want to have CropSyst namespace and name this CropSyst::Application_directory
: public CS::Application_directory
{public:
   CANMS_Database_directory      database_directory;  //120320 This should be provided
   CORN::OS::File_name_concrete   scenario_editor_exe; //120320 This should be provided
/*
   Directory_name dir_init_buffer;
   Smart_directory_name CANMS_dir;
   // This is the master database for equipement and facility parameters
   // (No the project's equipment and facility operations
   Directory_name CANMS_scenario_editor_help_dir;
   Directory_name CANMS_scenario_operations_editor_dir;

   Directory_name CANMS_project_dir;
   Directory_name CANMS_project_scenario_dir;
   Directory_name CANMS_project_optimization_dir;
   Directory_name CANMS_project_optimization_spreadsheets_dir;
   Directory_name CANMS_manual_dir;
   File_name project_editor_exe;
   File_name scenario_run_exe;
   File_name CANMS_database_feed_CANMS_feed_composition_dbf;
   Directory_name icon_dir;
   File_name icon_project;
   File_name icon_project_folder;
*/
 public:
   CANMS_Directory
      (const CS::Suite_Directory &path_name
      ,const wchar_t * directory_name);
};
//______________________________________________________class CANMS_Directory__/
extern CANMS_Directory *CANMS_directory;
// This directory must be instanciated in the program's main().

} // namespace CS
#endif
