#ifndef CS_explorer_engineH
#define CS_explorer_engineH
#include "GUI/explorer/explorer_engine_abstract.h"
#include "corn/application/user/settings.h"
#  include "corn/application/user/appdata_directory_OS_FS.h"
#include "CS_suite/CropSyst/export/scenario_export_engine.h"
#include "CS_suite/file_system/CS_directory_contexts.hpp"
#include "CS_suite/application/CS_contextualization.h"
#include "corn/OS/uniform_resource_locator.h"
//______________________________________________________________________________
namespace CORN
{
   class Text_list;
   namespace OS
   {  class File_name_concrete;
   }
}
namespace CS
{
   class Suite_directory;
}
namespace CropSyst
{  class Project_directory;
};
#define CropSyst_Project_directory CropSyst::Project_directory
namespace CropSyst
{  class Scenario_output_options;                                                //120313
};
using namespace CORN;
using namespace CORN::OS_FS;
using namespace CORN::OS;
//______________________________________________________________________________
/*161110 not currently used, but don't delete, may need something like this for something else
class Pending_download
: public Item
{public:
   CORN::OS::Uniform_resource_locator  URL; // I.e. http://modeling.bsyse.wsu.edu/xxxx/filename.exe
      // note: I do have a URL class
   CORN::OS::File_name_concrete         target; // where to download the file to
   nat8                             tries_remaining;
      // We only try to download so many times before giving up.
 public:
   Pending_download
      (const std::wstring                       &_URL
      ,const CORN::OS::Directory_name_concrete   &_target_directory
      ,nat8                                      _tries_remaining = 3);
   Pending_download
      (const std::string                        &_URL
      ,const CORN::OS::Directory_name_concrete   &_target_directory
      ,nat8                                      _tries_remaining = 3);
};
*/
//_2014-08-04___________________________________________________________________
class CS_Explorer_engine
: public Explorer_engine_abstract
{
 protected:
   provided_ CS::Contextualization *CS_contextualization;                        //180723
 private:
   contribute_ bool                 CS_contextualization_owned;                  //180723
 protected:
   contribute_ CORN::OS::Directory_entry_name_concrete
      recently_selected_DEN[CS::CONTEXT_COUNT];
   CropSyst::Project_directory                 *project_directory;  // null if we are not currently in a project context.
   provided_ CropSyst::Scenario_output_options *output_options;
   mutable CS::Directory_context                identified_context;
   contribute_ CORN::Unidirectional_list        pending_downloads;
   contribute_ CORN::OS::File_name_concrete    *preferred_model_executable_qual; //171121
      // 0 indicates NYI
 public: // temporarily public for convenience.
   CORN::OS_FS::Application_data_directory      user_application_directory;
   CORN::User_settings                          user_settings;
   CORN::OS::File_name_concrete                 report_filename;                 //171227
 public: // public for UI binding
   bool  UED_tools_mode; // This mode will display UED tools for arbitrary directorys
   nat32 CPF_percents_water;                                                     //150418
 public: // contextualization overrides
   covariant_ CS::Contextualization &provide_contextualization()   provision_;   //180723
 public:
   inline CS::Directory_context get_identified_context()                  const { return identified_context; };
   CS::Directory_context identify_context()                               const;
      // Identifies the current directory context by either:
      // - The name of the directory.
      // - The presence of key files.
      // - The key extension of some files.
   CS::Directory_context identify_context_of
      (const CORN::OS::Directory_name &directory)                         const;

   CS::Directory_context identify_context_of                                     //171231
      (const std::string &dir_name_unqual)                                const;

   CS::Directory_context assume_context
      (CS::Directory_context assumed_context
      ,bool permanently)                                          modification_; //161104

   nat8 get_model_version()                                               const; //180326

 public: // For arbitrary context
   const CORN::OS::Directory_name *create_simulation_directory
      (const STRING_WITH_FILENAME &simulation_folder_name
      ,const STRING_WITH_FILENAME &projects_folder_name);
 public: // For project context
   bool project_create_scenario(const std::wstring &new_scenario_name);
      ///\return the scenarios directory the scenario was created in or null if failed
   bool project_GIS_simulation();
   bool project_watershed_simulation();
   bool project_carbon_sequestration_for_grazing_regimen();

   CropSyst_Project_directory *provide_project_directory();
      /// Although  provide_project_directory is currently usually used in the project context,
      /// it may be useful in other contexts.
 public: // For scenario context
   bool scenario_edit()           const;
      // This is deprecated (only in V4)
   bool scenario_edit_model(nat8 model_index)                             const; //171228
   bool scenario_run_check_obsolete
      (bool display_runtime_graph)                                        const;
   bool scenario_run_GIS()                                                const; //140214

   nat16 instantiate_daily_output_formats()                               const; //171125
      ///< When (daily) (TDF) files are present in a scenario the simulation
      /// engine will add the daily output variables as desired .
      /// Uses current instiation_mode.
      /// /returns the number of formats instantiated.

 public: // For scenario output context
   bool launch_output_fast_graph()                                        const;
   bool launch_output_schedule_viewer()                                   const;
   bool launch_output_schedule_text_viewer()                              const;
   bool launch_output_harvest_report_viewer()                             const;
   bool scenario_output_has_file(const char *filename)                    const;
   bool output_export_UED_to_XLS_file_command_line
      (const CORN::OS::File_name &XXXXX_ued
      ,const CORN::OS::File_name &XXXXX_xxx
      ,const CORN::OS::File_name &XXXXX_tdf
      ,bool include_full_year)                                            const;
   const CropSyst::Scenario_output_options *provide_output_options() provision_;

   nat16 compare_directory                                                       //180127
      (const CORN::OS::Directory_name &source_dir // primary
      ,const CORN::OS::Directory_name &other_dir
      ,const CORN::OS::Directory_name &compare_dir)                       const;
   bool compare_scenario_output(const wchar_t *other_scenario_output_dir) const; //171121

   virtual nat16 compare_multiple_directories                                    //180128
      (const CORN::OS::Directory_name &primary_dir
      ,const CORN::Container &other_dirs)                                 const;
      // Usually the primary_dir and other_dirs are in the same directory (CWD)
      // (from the exporer UI), but this isn't necessarily the case.
      // The comparison directory will be created in CWD.

   // Report generation
   bool CS_Explorer_engine::output_generate_report
      (const char *format_TDF          // I.e. "annual_Excel.TDF"
      ,const char *pattern_UED         // I.e. "*@annual$d.UED" "*@seasonal$d.UED"
      ,const char *report_xls) const;  // I.e. "annual.xls"
   bool output_generate_annual_report()                                   const; //180107
   bool output_generate_season_report()                                   const; //180107

 public: // For Database parameter contexts
   const CORN::OS::Directory_name
      *add_database_context
         (const STR_WITH_FILENAME parameter_file_directory_name_unqual
         ,bool set_parameter_directory_as_current);
   bool database_has_directory(const char *subdirectory_name)              const;
 public: // For soil context
   bool launch_soil_convertor()                                           const;
 public: // For weather context
   bool launch_ClimGen()                                                  const;
   bool launch_UED_import()                                               const;
   bool launch_UED_export()                                               const;
   bool launch_UED_spatial_interpolator()                                 const;
   bool map_UED_locations()                                               const;
   bool launch_UED_condense()                                             const;
      /// \return the respective launch command.
   nat32 UED_file_quality_import_or_export
      (const std::string &command // import or export
      ,const CORN::Text_list  &selected_UED_filenames_qual_or_unqual);

   bool netCDF_to_UED
      (const std::wstring &geocoordinates_filename
      ,const std::wstring &bounding_box_coord1
      ,const std::wstring &bounding_box_coord2
      ,const std::wstring &cell_size_and_units
      ,const CORN::Date &date_from
      ,const CORN::Date &date_to);
 public: // for scenarios context
   bool project_scenarios_create_scenario
      (const STRING_WITH_FILENAME &new_scenario_name
      ,const STRING_WITH_FILENAME &scenario_file_name_or_extension
      ,const CORN::OS::File_name &scenario_editor_exe);
   nat32 run_potential_scenarios                                                 //180110
      (const CORN::Unidirectional_list &pot_scenarios_qual
      ,bool                    runtime_graph
      ,bool                    parallel);
   bool prefer_model_executable                                                  //171121
      (const wchar_t *model_executable_qual)                     rectification_;
 public: // beneath scenarios context
   bool run_ultimate_scenario_with_CPF                                                    //180110
      (const CORN::OS::Directory_name &ultimate_scenario
      //now member ,bool &abort_run
      ,bool parallel)                                                     const;
 public: // CANMS Enterprises context
   // NYN const std::string &project_create_enterprise(const char *new_scenario_name);
      // Currently if the user wants to create an enterprise, he should do it in the enterprises folder
   bool CANMS_scenario_edit()                                             const;
   bool project_enterprises_create_enterprise
      (const STRING_WITH_FILENAME &new_enterprise_name);
   bool is_installed_CANMS()                                       affirmation_; //171206
 public: // For most contexts:
   bool edit_parameter_file
      (const STRING_WITH_FILENAME &name
      ,const_ASCIIZ extension
      ,const_ASCIIZ editor_name_unqual
      ,const_UnicodeZ option = 0)                                         const;
   bool edit_context_file
      (const STRING_WITH_FILENAME &name
      ,const_UnicodeZ option = 0)                                         const;
   bool edit_database_parameter_file
      (const CORN::OS::Directory_name &database_dirname // fully qualified
      ,CS::Directory_context           parameter_context
      ,const STRING_WITH_FILENAME     &name)                              const;//141122
   bool edit_file_if_known_type
      (const STRING_WITH_FILENAME &filename)                              const;
      /// Edit the specified file using CropSyst parameter editor if it is
      /// a recognized file type.
      /// Returns the command if recognized.
      /// Returns empty string if not edited.

   bool edit_CWD_parameter_file
      (CS::Directory_context           parameter_context
      ,const STRING_WITH_FILENAME     &name)                              const;
   virtual bool launch_notepad()                                          const;
      // NYI replace this with launch_text_editor
 public:
   // response to navigator_frame actions:
   virtual bool navigator_double_clicked_file(const STRING_WITH_FILENAME &item_path) const;
      ///< \return true if the double click action performed something.
   virtual bool navigator_single_clicked_file(const STRING_WITH_FILENAME &item_path) const;
      ///< \return true if the double click action performed something.
 public: // structors
   CS_Explorer_engine();
   ~CS_Explorer_engine();
 public: // Explorer_engine_abstract overrides
   virtual bool get_context_icon_filename
      (CORN::OS::File_name &icon_filename,int &icon_index)                const;
      ///< The derived class should override to set the fully qualified icon file name
      ///  that will be used to represent the folder.
      ///   By default no icon filename is assigned.
      /// If there are multiple icons in the file then set icon_index to the index.
      ///\return false if this folder does not need or should not be assigned an icon.
   virtual bool get_context_description(std::string &description)         const;
      ///< The derived class should override to set the brief one line description. (Currently this codes in the desktop infotip).
      ///  By default no description is assigned.
      ///\return false if this folder does not need or should not have a description.
   virtual bool get_specified_context(std::string &context)               const; //171231
   virtual nat32 render_relevent_composition                                     //180117
      (CORN::Unidirectional_list &relevent_composition)              rendition_;
 public:
   virtual bool update_application_suite()                                const; //120112
   bool translate_AgMIP_ACE
      (const CORN::OS::File_name &translator_exe
      ,const CORN::OS::File_name &JSON_filename)                          const; //130418
   nat16 translate_AgMIP_ACE_JSON_files
      (const CORN::Text_list &selected_JSON_filenames_presumed)           const; //130418
   int export_scenarios
      (const CropSyst::Scenario_export_engine::Arguments &export_args
      ,nat8 format_index);
      // Returns the number of scenarios exported
   bool download_pending_URLs();
      // might be applicable to all in Explorer_engine_abstract
   bool launch_CropSyst_wizard()                                          const; //141022
   bool generate_scenarios
      (const CORN::Text_list &selected_scenario_filenames_unqual)         const; //161103
/*170723 moved to CS_contextualization
   bool is_scenario_level(const CORN::OS::Directory_name *dir = 0) affirmation_; //171227
      // underneath Scenarios but not under Output
   bool is_scenario_ultimate
      (const CORN::OS::Directory_name *dir = 0)                    affirmation_; //171227
   bool has_any_subscenario
      (const CORN::OS::Directory_name *dir = 0)                    affirmation_; //171227
   nat32 list_ultimate_scenarios                                                 //180110
      (const CORN::OS::Directory_name &level_or_ultimate_scenario
      ,CORN::Container &ultimates_list
      ,bool exclude_percent_dirs);
*/
   bool BlackBoard_promotion()                                    modification_; //180101

   bool ultimate_Output_backup();                                                //180406
};
//______________________________________________________________________________
#endif

