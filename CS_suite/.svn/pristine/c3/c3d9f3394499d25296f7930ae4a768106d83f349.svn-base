#ifndef CropSyst_directoryH
#define CropSyst_directoryH
//______________________________________________________________________________
#include "CS_suite/application/CS_application_directory.h"
using namespace CORN::OS;

using namespace CORN;
namespace CS
{
//______________________________________________________________________________
// Forward declarations
class Suite_Directory;
//_______________________________________________________Forward_declarations__/
class CropSyst_Directory        // May want to have CropSyst namespace and name this CropSyst::Application_directory
: public CS::Application_directory
{
private:
   provided_ CORN::OS::File_name *cropsyst_model_exe;
   provided_ CORN::OS::File_name *crop_editor_exe;
   provided_ CORN::OS::File_name *crop_calibrator_exe;
   provided_ CORN::OS::File_name *soil_editor_exe;
   provided_ CORN::OS::File_name *management_editor_exe;
   provided_ CORN::OS::File_name *biomatter_editor_exe;
   provided_ CORN::OS::File_name *rotation_editor_exe;
   provided_ CORN::OS::File_name *scenario_editor_exe;
   provided_ CORN::OS::File_name *CPF_runner_exe;                                //110725
   provided_ CORN::OS::File_name *schedule_viewer_exe;
   provided_ CORN::OS::File_name *fastgraph_exe;
   provided_ CORN::OS::File_name *soil_convertor_exe;
   provided_ CORN::OS::File_name *CropSyst_wizard_exe;                           //141022

   provided_ CORN::OS::File_name *carbon_sequestration_optimizer_exe;
   provided_ CORN::OS::File_name *carbon_sequestration_viewer_exe;
/*
   Directory_name watershed_dir;
   Directory_name watershed_manual_dir;
   Directory_name watershed_manual_whatnow_dir;
   File_name watershed_edit_exe;

   Smart_file_name      UED_import_export_format_editor_exe;
   File_name      pesticide_txt;
   File_name      phrasesc_lng;
*/

/*
   Directory_name cropsyst_template_dir;    unused
   Directory_name GIS_dir;
   Directory_name GIS_manual_dir;
*/
   provided_ CORN::OS::File_name *GIS_runner_exe;
/*
#ifdef NEW_CS_PATHS
   Directory_name cropsyst_manual_dir[2];
#else
   Directory_name cropsyst_manual_dir;
#endif
   Directory_name cropsyst_manual_whatnow_dir;     unused
   Directory_name cropsyst_manual_editors_dir;       unused
   Directory_name cropsyst_manual_parameters_dir;     unused
   Directory_name cropsyst_manual_parameters_crop_dir; unused

   Directory_name cropsyst_manual_project_dir;     unused
   Directory_name cropsyst_crop_calibrator_dir;   unused

   File_name      SOILPAR2_exe;

   Directory_name icon_dir;
   File_name icon_project;
   File_name icon_project_folder;
   File_name icon_CS_GIS_project;
   File_name icon_CS_GIS_project_folder;
   File_name icon_CS_WS_project;
   File_name icon_CS_WS_project_folder;

   Directory_name cropsyst_icon_dir;
   Directory_name cropsyst_icon_operation_dir;
   Directory_name cropsyst_icon_operation_48x24_dir;

   File_name create_simulation_directory_exe;

   File_name cs_suite_about_htm;
   File_name project_editor_instructions_htm;   // unused
   File_name scenario_editor_instructions_htm;  // unused
   File_name management_editor_instructions_htm;// unused

   File_name database_editor_instructions_htm;  // This is used, but replace with find_file

   File_name cs_suite_manual_edit_project_htm;    // unused
   Smart_file_name cs_suite_manual_projects_htm;  // This is used in CS_suite, but replace with find_file
   File_name cs_suite_manual_utilities_htm;       // This is used in CS_suite, but replace with find_file

   File_name project_CPF_instructions_htm;
*/
   #if (CS_VERSION == 4)
   // Inversion 5 there will be no location files.
   provided_ CORN::OS::File_name *location_editor_exe;
   // Version 5 will not have format files.
   provided_ CORN::OS::File_name *format_editor_exe;
   provided_ CORN::OS::File_name *database_editor_exe;
   provided_ CORN::OS::File_name *project_editor_exe;
   #endif
   provided_ CORN::OS::File_name *output_manager_advanced_exe;
 public:
   CropSyst_Directory(const CS::Suite_Directory &path_name,const wchar_t * directory_name);
   virtual ~CropSyst_Directory();
 protected:
   virtual void reset()                                              provision_;
 public:
   const CORN::OS::File_name &cropsyst_model_executable()                      provision_;
   const CORN::OS::File_name &crop_editor_executable()                         provision_;
   const CORN::OS::File_name &crop_calibrator_executable()                     provision_;
   const CORN::OS::File_name &soil_editor_executable()                         provision_;
   const CORN::OS::File_name &management_editor_executable()                   provision_;
   const CORN::OS::File_name &biomatter_editor_executable()                    provision_;
   const CORN::OS::File_name &rotation_editor_executable()                     provision_;
   #if (CS_VERSION == 4)
   // Inversion 5 there will be no location files.
   const CORN::OS::File_name &location_editor_executable()                     provision_;
   // Version 5 will not have format files.
   const CORN::OS::File_name &format_editor_executable()                       provision_;
   const CORN::OS::File_name &database_editor_executable()                     provision_;
   const CORN::OS::File_name &project_editor_executable()                      provision_;
   #endif
   const CORN::OS::File_name &output_manager_advanced_executable()             provision_;
   const CORN::OS::File_name &scenario_editor_executable()                     provision_;
   const CORN::OS::File_name &CPF_controller_executable()                      provision_; //110725 deprecated
   const CORN::OS::File_name &CPF_runner_executable()                          provision_; //110725
   const CORN::OS::File_name &schedule_viewer_executable()                     provision_;
   const CORN::OS::File_name &fastgraph_executable()                           provision_;
   const CORN::OS::File_name &soil_convertor_executable()                      provision_;
   const CORN::OS::File_name &carbon_sequestration_optimizer_executable()      provision_;
   const CORN::OS::File_name &carbon_sequestration_viewer_executable()         provision_;
   const CORN::OS::File_name &GIS_runner_executable()                          provision_;
   const CORN::OS::File_name &CropSyst_wizard_executable()                     provision_;

};
//______________________________________________________________________________
//090909 Eventually this will not be needed,
// Now should be able to get this from CS_Suite_directory.
// But some of the editor still use this
//check_obsolete extern CropSyst_Directory *CropSyst_directory;
// This must be instanciated in the 'main' for the CropSyst application that uses it.

} // namespace CS
//______________________________________________________________________________
#endif
