//______________________________________________________________________________
#include <vcl.h>
#pragma hdrstop
#include "CS_explorer_engine.h"

#include "CropSyst/source/options.h"
#include "CS_suite/CropSyst/file_system/project_directory_CropSyst.h"
#include "CS_suite/application/CS_suite_directory.h"
#include "corn/container/text_list.h"
#include "corn/data_source/vv_file.h"
#include "corn/OS/OS.h"
#include "corn/OS/directory_entry_name.h"
#include "corn/OS/file_system_engine.h"
#include "corn/string/strconv.hpp"
#include "UED/convert/convert_response.h"
#include "UED/library/UED_fname.h"
#include "CropSyst/source/cs_filenames.h"
#include "CropSyst/source/cs_scenario.h"
#include "CropSyst/source/output.h"

#include <assert.h>
#include <fstream>

using namespace std;
using namespace CS;
#include "corn/Internet/HTTP.h"
#include "corn/Internet/HTTP/request.hpp"
//______________________________________________________________________________
CS_Explorer_engine::CS_Explorer_engine()
: Explorer_engine_abstract
   (&user_settings
   ,&user_application_directory
   ,&CS::Suite_directory->CS_Explorer()
   ,(CS::Suite_directory))
, CS_contextualization                                                       (0) //180723
, CS_contextualization_owned                                             (false) //180723
, user_application_directory     (CS::Suite_directory->CS_explorer_executable())
, project_directory                                                          (0)
, output_options                                                             (0)
, identified_context                                           (UNKNOWN_context)
, UED_tools_mode                                                         (false)
, preferred_model_executable_qual                                            (0) //171121
{
   preferred_model_executable_qual = new CORN::OS::File_name_concrete            //171121
      (CS::Suite_directory->CropSyst().cropsyst_model_executable());             //171121
}
//_constructor_________________________________________________________________/
CS_Explorer_engine::~CS_Explorer_engine()
{  delete project_directory;
   delete output_options;
   delete preferred_model_executable_qual;                                       //171121
   if (CS_contextualization_owned) delete CS_contextualization;                  //180723
}
//_destructor__________________________________________________________________/
CS::Contextualization &CS_Explorer_engine
::provide_contextualization()                                         provision_
{  if (!CS_contextualization)
   {
      CORN_contextualization = CS_contextualization = new CS::Contextualization;
      CS_contextualization_owned = true;
   }
   return *CS_contextualization;
}
//_provide_contextualization________________________________________2018-07-23_/
Directory_context CS_Explorer_engine::identify_context_of
(const std::string &dir_name_unqual)                                      const
{
   {  // check if database
      if (dir_name_unqual == "Database")
          return identified_context = database_context;
   }
   {  // check if scenarios
      if (dir_name_unqual == "Scenarios"  )
          return identified_context = scenarios_context;
   }
   {  // check if enterprises
      if (dir_name_unqual == "Enterprises"  )
          return identified_context = enterprises_context;
   }
   {  // check if scenario output
      //180406 if (dir_name_unqual == "Output"  )
      if (dir_name_unqual.find("Output") != std::string::npos  )                 //180506
          return identified_context = scenario_output_context;
      // NYI Should also check if the parent folder is a scenario context
   }
   {  // check if database weather
      if (dir_name_unqual == "Weather"  )
          return identified_context = weather_context;
      // NYI Should also check if the parent folder is a database context
   }
   {  // check if database rotation
      if (dir_name_unqual == "Rotation"  )
          return identified_context = rotation_context;
      // NYI Should also check if the parent folder is a database context
   }
   {  // check if database crop
      if (dir_name_unqual == "Crop"  )
          return identified_context = crop_context;
      // NYI Should also check if the parent folder is a database context
   }
   {  // check if database management
      if (dir_name_unqual == "Management"  )
          return identified_context = management_context;
      // NYI Should also check if the parent folder is a database context
   }
   {  // check if database Biomatter
      if (dir_name_unqual == "Biomatter"  )
          return identified_context = biomatter_context;
      // NYI Should also check if the parent folder is a database context
   }
   return 0;
}
//______________________________________________________________________________
Directory_context CS_Explorer_engine::identify_context_of
(const CORN::OS::Directory_name &dir_name_qualified)                       const
{
   identified_context =
      UED_tools_mode ? weather_context : arbitrary_context ;
   std::string directory_name;                                                   //120614
   dir_name_qualified.append_components_to_string
      (directory_name,CORN::OS::Directory_entry_name::include_name_extension);
      // Identifies the current directory context by either:
      // - The name of the directory.
      // - The presence of key files.
      // - The key extension of some files.
      // - The desktop.ini file has a CS context description InfoTip
      //      or one of the CS icons.
   {  // Check for CS version 5 project file
      CORN::OS::File_name_concrete CS_project_filename
         (dir_name_qualified,L"","CS_project");                                  //120515
      if (CORN::OS::file_system_engine.exists(CS_project_filename))
         return  identified_context = project_context;
   }
   {  // Check for CS_version 4 project file
      CORN::OS::File_name_concrete CS_project_filename
       (dir_name_qualified,dir_name_qualified.get_name(),OS::Extension("csp"));
      if (CORN::OS::file_system_engine.exists(CS_project_filename))
         return  identified_context = project_context;
   }

   identified_context = identify_context_of(directory_name);
   if (identified_context)
      return identified_context;
   {  // check if CropSyst scenario context
      CORN::OS::File_name_concrete CS_scenario_filename
         (dir_name_qualified,L"",L"CropSyst_scenario");
      if (CORN::OS::file_system_engine.exists(CS_scenario_filename))
         return  identified_context = scenario_context;
   }
   {  // check if CANMS scenario context
      CORN::OS::File_name_concrete CANMS_scenario_filename
         (dir_name_qualified,L"",L"CANMS_scenario");
      if (CORN::OS::file_system_engine.exists(CANMS_scenario_filename))
         return  identified_context = scenario_context;
   }
   {  // check if CAFE dairy scenario context
      CORN::OS::File_name_concrete CAFE_dairy_scenario_filename
         (dir_name_qualified,L"",L"CAFE_dairy_scenario");
      if (CORN::OS::file_system_engine.exists(CAFE_dairy_scenario_filename))
         return  identified_context = scenario_context;
   }
   {  // check if NIFA dairy scenario context                                    //141111
      CORN::OS::File_name_concrete NIFA_dairy_scenario_filename
         (dir_name_qualified,L"",L"NIFA_dairy_scenario");
      if (CORN::OS::file_system_engine.exists(NIFA_dairy_scenario_filename))
         return  identified_context = scenario_context;
   }
   {  // check if CS project context                                             //141025
      CORN::OS::Directory_name_concrete project_scenarios_dirname
         (dir_name_qualified,L"Scenarios",CORN::OS::directory_entry); //121029
      if (CORN::OS::file_system_engine.exists(project_scenarios_dirname))
         return  identified_context = project_context;
   }
   {  // Check for CS_version 4 project file
      CORN::OS::File_name_concrete CS_scenario_filename
        (dir_name_qualified,dir_name_qualified.get_name(),OS::Extension("csn"));
      if (CORN::OS::file_system_engine.exists(CS_scenario_filename))
         return identified_context = scenario_context;
   }
   {  // check if database soil
      if (directory_name.compare("Soil"  ) == 0)
      {  // We need to distinguish between database soil directory and output soil directory   (090803)
         return identified_context
            //180406 = (dir_name_qualified.get_parent_directory_name_qualified().get_name()==L"Output")
            = (dir_name_qualified.get_parent_directory_name_qualified().get_name().find(L"Output") != std::string::npos)
            ? scenario_output_context
            : soil_context;
      }
      // NYI Should also check if the parent folder is a database context
   }
   {  // check if database Biomatter
      if (directory_name.compare("Initial"  ) == 0)
          return identified_context = initial_context;
      // NYI Should also check if the parent folder is a database context
   }

   #if (CS_VERSION==4)
   {  // check if database format
      if (directory_name.compare("Format"  ) == 0)
          return identified_context = format_context;
      // NYI Should also check if the parent folder is a database context
   }
   #endif

   //171231 warning, the following Output and Scenarios are probably obsolete for V5
   // because in CS_exporer(5) uses beneath checks, but need to check how this case is handled
   if (dir_name_qualified.has_in_path_cstr("Output",CORN::OS::Directory_entry_name::include_all)) //180407_171124
      // Output can now be in the extension i.e. backup                          //180407
      return identified_context = scenario_output_context;                       //171124

   if (dir_name_qualified.has_in_path_cstr("Scenarios",CORN::OS::Directory_entry_name::include_all)) //180407_171121
      return identified_context = scenario_context;                              //171121

/* NYI need to implement provide_monuments  171231

   std::string monumement_name;                                                  //171231
   if (provide_monuments().identify(directory_name,monument_name))               //171231
   {  identified_context = identify_context_of(monument_name);                   //171231
      if (identified_context)                                                    //171231
         return identified_context;                                              //171231
   }
   // NYI check .directory file
*/

   {  // This checks the desktop.ini                                             //101124
      CORN::OS::File_name_concrete desktop_ini_filename("desktop.ini");
      char infotip[512];
      GetPrivateProfileString(".ShellClassInfo","InfoTip","",infotip,sizeof(infotip),desktop_ini_filename.c_str());
      char iconfile[512];
      GetPrivateProfileString(".ShellClassInfo","IconFile","",iconfile,sizeof(iconfile),desktop_ini_filename.c_str());
      for (nat8 context_index = 0;  context_index < CONTEXT_COUNT; context_index++)
      {
         if (strcmp(infotip,context_strings[context_index].description) == 0)
            identified_context = context_index;
         if (strcmp(iconfile,context_strings[context_index].icon) == 0)
            identified_context = context_index;
      }
   }
   if (identified_context == arbitrary_context)
   {  // If we still haven't found the context it is possible that we are in a subdirectory
      // of a context (For example we often of subdirectories of the weather database)
      if (directory_name.find("\\Weather\\")    != std::string::npos) identified_context = weather_context;
      if (directory_name.find("\\Soil\\")       != std::string::npos) identified_context = soil_context;
      if (directory_name.find("\\Crop\\")       != std::string::npos) identified_context = crop_context;
      if (directory_name.find("\\Output\\")     != std::string::npos) identified_context = scenario_output_context;
      if (directory_name.find("\\Management\\") != std::string::npos) identified_context = management_context;
      if (directory_name.find("\\Rotation\\")   != std::string::npos) identified_context = rotation_context;
      if (directory_name.find("\\Biomatter\\")  != std::string::npos) identified_context = biomatter_context;
      if (directory_name.find("\\Scenarios\\")  != std::string::npos) identified_context = scenarios_context;
      if (directory_name.find("\\Enterprises\\")!= std::string::npos) identified_context = enterprises_context;
      // Don't check here for the following contexts:
      // arbitrary_context            //  0
      // project_context              //  1
      // database_context             //  2
      // scenario_context             //  5
      // generated_scenarios_context  //  6
   }
   if (UED_tools_mode)
      identified_context = weather_context;
   return identified_context;
}
//______________________________________________________________________________
CS::Directory_context CS_Explorer_engine::identify_context()               const
{  return identify_context_of(get_active_directory()/*180723 *directory_name_qualified*/);
}
//______________________________________________________________________________
bool CS_Explorer_engine::project_create_scenario(const std::wstring &new_scenario_name)
{  // in this case we are in the project directory
   // Setup the scenarios directory (if it doesn't aready exist)
   CORN::OS::Directory_name_concrete scenarios_dir
      (get_active_directory() //180723 *directory_name_qualified
      ,L"Scenarios",L"",CORN::OS::directory_entry);    //161029
   if (CORN::OS::file_system_engine.exists(scenarios_dir))
   {  CORN::OS::file_system_engine.provide_directory(scenarios_dir); // if the Scenarios directory doesn't already exist.

      //180723 directory_name_qualified->set_DEN(scenarios_dir);                          //130123
      provide_contextualization().change_active_directory                        //180723
         (scenarios_dir.c_str());                                                //180723

      /*180723 now done by change_active_directory
      CORN::OS::file_system_engine.set_current_working_directory(scenarios_dir);
      */
      setup_context_CWD();
   }
   // Now set up the scenario directory (probably will be creating but this doesn't hurt if it already exists).
   // 090624 Although the version 4 scenario editor will create the scenario directory
   // it doesn't currently setup the context.
   CORN::OS::Directory_name_concrete scenario_directory
      (scenarios_dir,new_scenario_name,L"",CORN::OS::directory_entry);           //161029
   bool scenario_already_exists = CORN::OS::file_system_engine
      .exists(scenario_directory);                                               //140213
   CORN::OS::file_system_engine.provide_directory(scenario_directory);
   provide_contextualization().change_active_directory(scenario_directory.c_str());      //180723
   //180723directory_name_qualified->set_DEN(scenario_directory);                        //130123
   CORN::OS::File_name_concrete  created_scenario_filename(scenarios_dir,L"",OS::Extension(CS_scenario_EXT));
   // In version 4 I don't want to create a context because

   CORN::OS::File_name_concrete  scenario_editor
      (CS::Suite_directory->CropSyst().scenario_editor_executable()
         /*I.e. "C:\\CS_suite_4\\CropSyst\\scenario_editor.exe"*/);
   #ifdef _Windows
   WritePrivateProfileString("scenario","","",created_scenario_filename.c_str()); // This is to ensure that a scenario file exists so we can recognize the context
   #endif
   setup_context_CWD(); // Setup the scenario directory context
   // May need to be setup_context_in  180625

   return run_program_with_primary_DEN
      ( scenario_editor
      , created_scenario_filename
      , L""
      , false // dont wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);
}
//______________________________________________________________________________
bool CS_Explorer_engine::project_scenarios_create_scenario  // rename, nolonger necessarily the Scenario directory
(const STRING_WITH_FILENAME & new_scenario_name
,const STRING_WITH_FILENAME & scenario_file_name_or_extension
,const CORN::OS::File_name  & scenario_editor_exe)
// In version 4 we use extension, in version 5 it is just the name
{  // In this case we are already in the scenarios directory

   if (new_scenario_name.empty()) return false; // we need a name to create       //180330

   /*180330
   CORN::OS::Directory_name_concrete scenarios_dir
      (*directory_name_qualified,CORN::OS::directory_entry);                     //161029
   CORN::OS::file_system_engine.provide_directory(scenarios_dir);

   directory_name_qualified->set_DEN(scenarios_dir);                             //130123
   */
   setup_context_CWD();
   // In most cases the scenarios directory will already have been setup but this could be the first scenario.

   /* 180330
   CORN::OS::file_system_engine.set_current_working_directory(scenarios_dir); // setting this CWD is probably not needed.
   CORN::OS::Directory_name_concrete scenario_dir
      (scenarios_dir,new_scenario_name,CORN::OS::directory_entry);               //161029
   */
   CORN::OS::Directory_name_concrete scenario_dir
      (get_active_directory()/*180723 *directory_name_qualified*/,new_scenario_name,CORN::OS::directory_entry);   //161029
   CORN::OS::file_system_engine.provide_directory(scenario_dir);
   provide_contextualization().change_active_directory(scenario_dir);            //180723
   //180723 directory_name_qualified->set_DEN(scenario_dir);                              //130123

//   NYI the scenario will be a scenario directory with an associated directory file: .CropSyst_scenario .
   /*180330
   CORN::OS::file_system_engine.set_current_working_directory(scenarios_dir);
   */

   CORN::OS::file_system_engine.set_current_working_directory(scenario_dir);


   CORN::OS::File_name_concrete created_scenario_filename
      (scenario_dir,scenario_file_name_or_extension); // the filename is simply .CropSyst_scenario
   // Use the last selected scenario file as the template to copy to this new scenario
   if (CORN::OS::file_system_engine.exists
       (recently_selected_DEN[scenarios_context]))
      CORN::OS::file_system_engine.copy_file
         (recently_selected_DEN[scenarios_context],created_scenario_filename,true);
#ifdef _Windows
   WritePrivateProfileString("scenario","","",created_scenario_filename.c_str()); // This is to ensure that a scenario file exists so we can recognize the context
#else
   NYI , open the file name and write [scenario]
#endif
   setup_context_CWD(); // Although the version 4 scenario editor will create the scenario directory as needed it might not setup the directory context
   return run_program_with_primary_DEN
      ( scenario_editor_exe
      , created_scenario_filename
      , L""
      , false // not wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);
}
//______________________________________________________________________________
/*NYN
const std::string &CS_Explorer_engine::project_scenarios_create_scenario
(const wchar_t *new_scenario_name
,const char *scenario_file_name_or_extension
,const CORN::Smart_file_name &scenario_editor_exe)
{
   std::wstring new_scenario_name_wstr(new_scenario_name);
   std::string  new_scenario_name_str;
   wstring_to_string(new_scenario_name_wstr,new_scenario_name_str);
   return project_scenarios_create_scenario(new_scenario_name_str.c_str(),scenario_file_name_or_extension,scenario_editor_exe);
}
*/
//______________________________________________________________________________
bool CS_Explorer_engine::project_enterprises_create_enterprise
(const std::wstring &new_enterprise_name)
{  // In this case we are already in the scenarios directory
   CORN::OS::Directory_name_concrete enterprises_dir(get_active_directory()/*180723 *directory_name_qualified*/,CORN::OS::directory_entry); //161029
   change_active_directory(enterprises_dir);                                     //180723

   /*180723 now done  by change_active_directory
   CORN::OS::file_system_engine.provide_directory(enterprises_dir); // if the enterpries  directory doesn't already exist.
   directory_name_qualified->set_DEN(enteprises_dir);                            //130123
   CORN::OS::file_system_engine.set_current_working_directory(enteprises_dir); // setting this CWD is probably not needed.
   */
   setup_context_CWD(); // In most cases the scenarios directory will already have been setup but this could be the first scenario.
   CORN::OS::Directory_name_concrete enterprise_dir(enterprises_dir,new_enterprise_name,CORN::OS::directory_entry); //161029
   change_active_directory(enterprise_dir);                                      //180723
/*170923
   CORN::OS::file_system_engine.provide_directory(enterprise_dir);
   directory_name_qualified->set_DEN(enterprise_dir);                            //130123
   CORN::OS::file_system_engine.set_current_working_directory(enteprises_dir);
*/
   CORN::OS::File_name_concrete created_enterprise_filename(enterprise_dir,".CANMS_enterprise");
#ifdef _Windows
   WritePrivateProfileString("enterprise","","",created_enterprise_filename.c_str()); // This is to ensure that a scenario file exists so we can recognize the context
#else
   NYI file the files doesn't exists, just create a file with the [enterprise] section
#endif
   setup_context_CWD(); // Although the version 4 scenario editor will create the scenario directory as needed it might not setup the directory context
   return run_program_with_primary_DEN
      ( CS::Suite_directory->CANMS().scenario_editor_exe // the scenario editor also edits enterprises
      , created_enterprise_filename
      , L""
      , false // dont wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);
}
//______________________________________________________________________________
//180128 const STRING_WITH_FILENAME &
bool CS_Explorer_engine::project_GIS_simulation()
{  // In this case I may still need to update the desktop file icon
   return edit_parameter_file(CS_PROJECT_FILENAME,"","GIS_project_editor",L"");  //120515
}
//______________________________________________________________________________
//180128 const STRING_WITH_FILENAME &
bool CS_Explorer_engine::project_watershed_simulation()
{
#if (CROPSYST_VERSION == 4)
   CORN::OS::File_name_concrete
      project_filename(*directory_name_qualified);
#endif

// In this case I may still need to update the desktop file  icon
   return edit_parameter_file
      (CS_PROJECT_FILENAME,"","project_editor",L"Watershed");                    //120515
}
//______________________________________________________________________________
//180128 const STRING_WITH_FILENAME &
bool CS_Explorer_engine::project_carbon_sequestration_for_grazing_regimen()
{  return edit_parameter_file(CS_PROJECT_FILENAME,"","project_editor",L"Grazing");
}
//______________________________________________________________________________
const CORN::OS::Directory_name *CS_Explorer_engine::create_simulation_directory
(const STRING_WITH_FILENAME &simulation_folder_name
,const STRING_WITH_FILENAME &projects_folder_name)
{  CORN::OS::Directory_name_concrete simulation_dir
      (get_active_directory() //180723 *directory_name_qualified
      ,simulation_folder_name,CORN::OS::directory_entry);                        //161029
   change_active_directory(simulation_dir);                                      //180723
   /*180723 now done by change_active_directory
   CORN::OS::file_system_engine.provide_directory(simulation_dir);
   directory_name_qualified->set_DEN(simulation_dir);
   */
   setup_context_in(arbitrary_context,simulation_dir);                                             //180625
   CORN::OS::Directory_name_concrete projects_dir(simulation_dir,projects_folder_name,CORN::OS::directory_entry); //161029
   CORN::OS::file_system_engine.provide_directory(projects_dir);
   CORN::OS::Directory_name_concrete database_dir(simulation_dir,"Database",CORN::OS::directory_entry); //161029
   change_active_directory(database_dir);                                        //180723
   /*180723
   CORN::OS::file_system_engine.provide_directory(database_dir);
   directory_name_qualified->set_DEN(database_dir);
   */
   setup_context_in(database_context,database_dir);                                               //180625
   CORN::OS::File_name_concrete database_desktop_ini(database_dir,"desktop.ini");
   std::ofstream desktop_ini(database_desktop_ini.c_str());
   const CORN::OS::File_name *database_ico_fname_ptr
      = CS::Suite_directory->find_file_name //161103 this has been updated, need to check if this is still working
         (L"database.ico"
         ,CORN::OS::File_system::subdirectory_recursion_inclusive);
   if (database_ico_fname_ptr)
      desktop_ini << "[.ShellClassInfo]" << endl
               << "IconFile=" << database_ico_fname_ptr->c_str() << endl // NYI warning, need to get the icon file from CS_suite icons path
               << "IconIndex=0" << endl
               << "InfoTip=CropSyst Suite project" << endl;
   // Go into the projects directory because the next likely thing to
   // do is create a project.
   change_active_directory(projects_dir);                                           //180723
   //180723 directory_name_qualified->set_DEN(projects_dir);
   setup_context_in(arbitrary_context,projects_dir);                             //180625
   return &get_active_directory(); //180723 directory_name_qualified;
}
//______________________________________________________________________________
const CORN::OS::Directory_name *CS_Explorer_engine::add_database_context
(const STR_WITH_FILENAME parameter_file_directory_name_unqual
,bool set_parameter_directory_as_current)                                        //110423
{
   CORN::OS::Directory_name_concrete database_dir
      (get_active_directory()//180723 *directory_name_qualified
      ,CORN::OS::directory_entry);                     //161029_110423
   CORN::OS::Directory_name_concrete database_param_dir
      (database_dir //180723 *directory_name_qualified
      ,parameter_file_directory_name_unqual,CORN::OS::directory_entry); //161029
   change_active_directory(database_param_dir);                                  //180723
   setup_context_CWD();                                                          //180624
/*180723
   CORN::OS::file_system_engine.provide_directory(database_param_dir);
   // Set the database parameter directory to the new context.
   directory_name_qualified->set_DEN(database_param_dir);
*/
/*108723
   change_current_directory(set_parameter_directory_as_current                   //110423
      ? database_param_dir.c_str()                                               //110423
      : database_dir.c_str());                                                   //110423
*/
   if (!set_parameter_directory_as_current)                                      //180723
      change_active_directory(database_dir);                                     //180723
   //180723    setup_context_CWD();                                         //180624
   return &get_active_directory(); //180723 directory_name_qualified;
}
//______________________________________________________________________________
bool CS_Explorer_engine::database_has_directory(const char *subdirectory_name) const
{  CORN::OS::Directory_name_concrete subdirectory(get_active_directory() //180723 *directory_name_qualified
      ,subdirectory_name,CORN::OS::directory_entry);//161029
   return CORN::OS::file_system_engine.exists(subdirectory);
}
//______________________________________________________________________________
bool CS_Explorer_engine::edit_parameter_file
(const STRING_WITH_FILENAME & name
,const_ASCIIZ extension
,const_ASCIIZ editor_name  /* without .exe extension */
,const_UnicodeZ option)                                                    const
{  bool result = false;
      STRING_WITH_FILENAME unqualified_editor_name;
      CORN::ASCIIZ_to_wstring(editor_name,unqualified_editor_name);
      #ifdef _WIN32
      append_ASCIIZ_to_wstring(".exe",unqualified_editor_name);  // Windows executables have .exe extension
      #endif
   std::wstring options(option? option:L"");
   CORN::OS::File_name_concrete *parameter_file_name = new CORN::OS::File_name_concrete (name);   // First assume name is fully qualified
   if (!CORN::OS::file_system_engine.exists(*parameter_file_name))
   {  // Probably then the name is unqualified name with no extension.
      delete parameter_file_name;
      parameter_file_name = new CORN::OS::File_name_concrete
         (get_active_directory() //180723 *directory_name_qualified
         ,name,extension);
   }
   CORN::OS::File_name *parameter_editor = CS::Suite_directory->find_file_name
      (unqualified_editor_name
      ,CORN::OS::File_system::subdirectory_recursion_inclusive);                 //161103
   if (parameter_editor)
      //180128 const STRING_WITH_FILENAME &command =
      result = run_program_with_primary_DEN
      ( *parameter_editor
      , *parameter_file_name
      , options
      , false // wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);
   //else  should output status message that the parameter editor could not be found
   delete parameter_editor;
   delete parameter_file_name;
   //180128 return command;
   return result;
}
//______________________________________________________________________________
bool CS_Explorer_engine::edit_context_file
(const STRING_WITH_FILENAME &name,const_UnicodeZ option)                   const
{
   const char *parameter_file_ext_or_name = context_strings[identified_context].
            #if (CS_VERSION == 4)
            parameter_file_ext;
            #else
            parameter_file_ext_or_name;
            #endif
   CORN::OS::File_name_concrete *parameter_file_name =
      (context_strings[identified_context].parameter_directory)
      ? new CORN::OS::File_name_concrete
         (get_active_directory() //180723 *directory_name_qualified
         ,name,parameter_file_ext_or_name)
      : new CORN::OS::File_name_concrete
         (get_active_directory() //180723 *directory_name_qualified
         ,context_strings[identified_context].parameter_directory);
   CORN::OS::File_name_concrete parameter_editor(*CS::Suite_directory,context_strings[identified_context].editor);
   bool result =
      run_program_with_primary_DEN
      ( parameter_editor
      ,*parameter_file_name
      , option ? option : L"" // options
      , false // wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);
   delete parameter_file_name;                                                   //141122
   return result;
}
//______________________________________________________________________________
bool CS_Explorer_engine::edit_database_parameter_file
(const CORN::OS::Directory_name  &database_dirname // fully qualified
,CS::Directory_context           parameter_context
,const STRING_WITH_FILENAME     &name)                                     const
{  // This is used by CropSyst Wizard
   CORN::OS::Directory_name_concrete parameter_directory
      (database_dirname,context_strings[parameter_context].context
      ,CORN::OS::directory_entry);                                               //161029
   const char *parameter_file_ext_or_name = context_strings[parameter_context].
            #if (CS_VERSION == 4)
            parameter_file_ext;
            #else
            parameter_file_ext_or_name;
            #endif
   CORN::OS::File_name_concrete parameter_file_name
      (parameter_directory,name,parameter_file_ext_or_name);
   CORN::OS::File_name_concrete parameter_editor(*CS::Suite_directory,context_strings[parameter_context].editor);
   return run_program_with_primary_DEN
      ( parameter_editor
      ,parameter_file_name
      ,  L"" // options
      , false // wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);
}
//_2014-11-22__________________________________________________________________/
bool CS_Explorer_engine::edit_CWD_parameter_file
(CS::Directory_context           parameter_context
,const STRING_WITH_FILENAME     &name)                                     const
{  // This is used by CS_explorer parameter panel
   const char *parameter_file_ext = context_strings[parameter_context]
      .parameter_file_ext;

   CORN::OS::File_name_concrete parameter_file_name
      (get_active_directory() //180723 (*directory_name_qualified)
      ,name,parameter_file_ext);
   CORN::OS::File_name_concrete parameter_editor(*CS::Suite_directory,context_strings[parameter_context].editor);
   return run_program_with_primary_DEN
      ( parameter_editor
      ,parameter_file_name
      ,  L"" // options
      , false // wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);
}
//_20117-01-02_________________________________________________________________/
bool CS_Explorer_engine::launch_UED_import()                               const
{  return run_program                                                            //120411
         (CS::Suite_directory->UED().import_wizard_executable()
         ,get_active_directory(). //180723 directory_name_qualified ? directory_name_qualified->
            w_str() //180723  : L""     //120411
         , false // do not wait for termination
         , true /*visible was SW_SHOWNORMAL*/);
}
//______________________________________________________________________________
bool CS_Explorer_engine::launch_UED_export()                               const
{  return run_program_with_primary_DEN
         (CS::Suite_directory->UED().export_wizard_executable()
         ,recently_selected_DEN[identify_context()]
         , L"" // no options
         , false // do not wait for termination
         , true /*visible was SW_SHOWNORMAL*/);
}
//______________________________________________________________________________
bool CS_Explorer_engine::launch_UED_spatial_interpolator()                 const
{  return run_program                                                            //120411
         (CS::Suite_directory->UED().spatial_interpolator_executable()
         , L"" // no options
         , false // do not wait for termination
         , SW_SHOWNORMAL);
}
//______________________________________________________________________________
bool CS_Explorer_engine::launch_ClimGen()                                  const
{  // If the current selected file in the file list is a UED file.
   // setproviteprofile string the associated location file with the database filename
   // to the ued file
   bool parameterization_mode = false;
   if (!CORN::OS::file_system_engine.exists(recently_selected_DEN[identify_context()]))
       recently_selected_DEN[identify_context()].set_DEN
         (CORN::OS::File_name_concrete(get_active_directory() //180723 directory_name_qualified
            ,"unnamed","UED"));
   CORN::OS::File_name_concrete location_filename(recently_selected_DEN[identify_context()] ,Extension("loc"));
   if (recently_selected_DEN[identify_context()].is_extension_ASCII("UED"))
   {  parameterization_mode = CORN::OS::file_system_engine.exists(location_filename);
      WritePrivateProfileString("[location]","database", recently_selected_DEN[identify_context()].c_str() ,location_filename.c_str());
   }
   return run_program_with_primary_DEN
         (CS::Suite_directory->ClimGen().ClimGen_exe()
         ,location_filename
         ,L"" // location_filename.exists() ? (parameterization_mode ? "PARAMETERIZE" : "GENERATE") : "" // no options
         , false // do not wait for termination
         , SW_SHOWNORMAL);
}
//______________________________________________________________________________
bool CS_Explorer_engine::launch_soil_convertor()    const
{
   bool result = false;
   if (CORN::OS::file_system_engine.exists(recently_selected_DEN[identify_context()])) //140311
      result = run_program_with_primary_DEN
         (CS::Suite_directory->CropSyst().soil_convertor_executable()
         ,recently_selected_DEN[identify_context()]
         ,L"" // no options
         , false // do not wait for termination
         , SW_SHOWNORMAL);
   return result;
}
//______________________________________________________________________________
nat32 CS_Explorer_engine::run_potential_scenarios                                //180110
(
 const CORN::Unidirectional_list &pot_scenarios_qual
,bool                    runtime_graph
,bool                    parallel)
{  nat32 actual_run_count = 0;
   if (!preferred_model_executable_qual) return 0;
   CORN::Unidirectional_list ultimate_scenarios;
   FOR_EACH_IN(pot_scenario_qual,CORN::OS::Directory_name, pot_scenarios_qual,each_pot_scenario)
   {
      provide_contextualization().list_ultimate_scenarios
         (*pot_scenario_qual,ultimate_scenarios,CPF_percents_water);
   } FOR_EACH_END(each_pot_scenario)
   if (CPF_percents_water) // NYI  && preferred model is CropSyst_X
   {
      FOR_EACH_IN(ultimate_scenario,CORN::OS::Directory_name,ultimate_scenarios,each_ultimate)
      {
         actual_run_count += run_ultimate_scenario_with_CPF(*ultimate_scenario,parallel);
      } FOR_EACH_END(each_ultimate)
   } else
   {
         actual_run_count = ultimate_scenarios.count();
         nat32 queued_count = run_program_multiple_DENS
               (*preferred_model_executable_qual
               ,ultimate_scenarios
               , L"" // currently no options but eventually will have
               , parallel);
      // WARNING  should return the number of DENs to run
      // and the script filename for the Explorer to confirm
      // from the user to run all those
   }
   return actual_run_count;
}
//_2018-01-10___________________________________________________________________run_potential_scenarios/
/*
nat16 CS_Explorer_engine::project_scenarios_run_scenarios
(const CORN::Text_list  &selected_scenario_file_or_dir_names_qual_or_unqual
,bool                   &abort_run
,bool                    runtime_graph
,bool                    run_simulateously)                                const //171121
{  nat16 scenarios_run = 0;
   CORN::Bidirectional_list  actual_scenario_dirnames_qual(true);
   // Unique keys so that we don't duplicate scenario runs if the user selected both the .CSN file and its associated folder.
   std::wstring scenario_run_options;                                            //150421_110106
   // First assume the scenario run program is CropSyst

//171020 Actually the user should specify the model

   CORN::OS::File_name_concrete &scenario_run_executable                         //171121
      = *preferred_model_executable_qual;                                        //171121
    //171121 abandoned  (CS::Suite_directory->CropSyst().cropsyst_model_executable());

   FOR_EACH_IN(scenario_entry_qual_or_unqual,CORN::Text_list::Item,selected_scenario_file_or_dir_names_qual_or_unqual,each_scenario)
   {
      // Note that selected_scenario_file_or_dir_names_qual_or_unqual could be any directory entry
      // that happens to be in the scenarios (or generated_scenarios) folder.
      // In most situations these will be scenarios directories (and/or in the case of V4 .CSN files)
      // but the user may have put arbitrary files in this directory.
      CORN::OS::Directory_entry_name_concrete *scenario_dirent_qual
         = new CORN::OS::Directory_entry_name_concrete(*scenario_entry_qual_or_unqual);
      if (!scenario_dirent_qual->is_qualified(false))                            //120212
      {  delete scenario_dirent_qual;
         scenario_dirent_qual = new CORN::OS::Directory_entry_name_concrete
            (*directory_name_qualified,*scenario_entry_qual_or_unqual);
      }
      actual_scenario_dirnames_qual.append(scenario_dirent_qual);                //171029

//   171029 now scenario directories dont necessarily have to have scenario
      file because there may now be fragments, scenario composition and
      directory names may specify scenario elements.
      CORN::OS::File_system::Directory_entry::Type dir_entry_type = CORN::OS::file_system_engine.identify_type(*scenario_dirent_qual);
      switch (dir_entry_type)
      {  case CORN::OS::directory_entry :
         {  //if it is a directory, then compose the various possible recognized scenario file names
            CORN::OS::File_name_concrete CropSyst_scenario_filename(*scenario_dirent_qual,".CropSyst_scenario");
            if (CORN::OS::file_system_engine.exists(CropSyst_scenario_filename))
               actual_scenario_dirnames_qual.append(scenario_dirent_qual);
            else
            {  // this isn't a CropSyst simulation
               // May be it is a CAFE dairy scenario                             //110106
               //150410 delete scenario_parameter_filename;
               CORN::OS::File_name_concrete CAFE_dairy_scenario_parameter_filename(*scenario_dirent_qual,".CAFE_dairy_scenario"); //110106
               if (CORN::OS::file_system_engine.exists(CAFE_dairy_scenario_parameter_filename)) //120412
               {  actual_scenario_dirnames_qual.append(scenario_dirent_qual);
                  scenario_run_executable.set_DEN(CS::Suite_directory->CAFE().Dairy().scenario_editor_executable());//110106
                  scenario_run_options.assign(L" run ");
               } else                                                            //110106
               {  // Maybe is is NIFA dairy
                  CORN::OS::File_name_concrete NIFA_dairy_scenario_parameter_filename(*scenario_dirent_qual,".NIFA_dairy_scenario"); //110106
                  if (CORN::OS::file_system_engine.exists(NIFA_dairy_scenario_parameter_filename)) //120412
                  {  actual_scenario_dirnames_qual.append(scenario_dirent_qual);
                     scenario_run_executable.set_DEN(CS::Suite_directory->NIFA().Dairy().scenario_editor_executable());//110106
                     scenario_run_options.assign(L" run ");
                  }  else
                     {
                     // May be it is a CANMS scenario                               //110106
                     //delete scenario_parameter_filename;
                     CORN::OS::File_name_concrete CANMS_scenario_filename(*scenario_dirent_qual,".CANMS_scenario");                      //110106
                     if (CORN::OS::file_system_engine.exists(CANMS_scenario_filename)) //120412
                     {  actual_scenario_dirnames_qual.append(scenario_dirent_qual);
                        assert(false); //                                           //110106
                        // need to add the CANMS executable to CANMS directory
                        // scenario_run_executable.set(CS::Suite_directory->CANMS().xxxxx_executable);  //110106
                     }
                  }
               }                                                                 //110106
            }                                                                    //110106
         } break;
         #if (CS_VERSION < 6)
         case CORN::OS::file_entry :
         {  //if the selected item is a file and has extension .CSN then it is a .CSN style scenario file
            CORN::OS::File_name_concrete CropSyst_CSN_scenario_filename(*scenario_dirent_qual);
            if (CropSyst_CSN_scenario_filename.has_extension_ASCII("csn",false)) //170225_150420
            {  delete scenario_dirent_qual; scenario_dirent_qual = 0;            //150420
               scenario_dirent_qual = new CORN::OS::Directory_entry_name_concrete//150420
                  (*(CropSyst_CSN_scenario_filename.get_path_directory_name())); //150420
               actual_scenario_dirnames_qual.append(scenario_dirent_qual);       //150420
               //scenario_parameter_filename = scenario_dirent_qual;             //150420
            }
         } break;
         default :   // This was some other kind of file we don't recognize in this context
         {  // scenario_parameter_filename = 0;                                     //150420
         } break;
         #endif
      } // switch

   } FOR_EACH_END(each_scenario)

   if (CPF percents checked)
   {
      FOR_EACH_IN(scenario_dirent_qual,
            CORN::OS::Directory_entry_name_concrete
            ,actual_scenario_dirnames_qual,each_scenario_qual);
      {

         run_ultimate_scenario_with_CPF

      if (abort_run) continue;                                                   //150419


//NYI     171122
// run the general scenario
// generate crop production function subscenarios each will have a fixed
//  management file created to
// the run each of the subscenarios.
// Perhaps run the collator
//    (which will use TDF file(s) defined specifically for CPF output analysis)


// The following will be deprecated

      CORN::OS::File_name_concrete crop_production_function_irrigation_adjustments_filename
         (get_directory_name_qualified(),"irrigation_adjustments.dat");
      if (CORN::OS::file_system_engine.exists(crop_production_function_irrigation_adjustments_filename))             //150418
      {
         //171121 scenario_run_executable.set_DEN(CS::Suite_directory->CropSyst().CPF_runner_executable());
         scenario_run_executable = CS::Suite_directory->CropSyst().CPF_runner_executable(); //171121
         crop_production_function_irrigation_adjustments_filename.append_components_to(scenario_run_options);
      } else if (CPF_percents_water)                                             //150418
      {
         //scenario_run_options.append(L"irrigation_adjustments_percent=");
         for (nat8 percent_index = 0; percent_index < 16; percent_index++)
         {
            //171121 scenario_run_executable.set_DEN(CS::Suite_directory->CropSyst().CPF_runner_executable());
            scenario_run_executable = CS::Suite_directory->CropSyst().CPF_runner_executable(); //171121
            if ((1 << percent_index) & CPF_percents_water)
            {
               nat8 percent = percent_index * 10;
               CORN::append_nat32_to_wstring(percent,scenario_run_options);
               scenario_run_options.append(L" ");
            }
         }
      }
      command_history.
         add_wstring
         ((report_filename.length()) //171227 report_format_filename_optional                                        //131006
            ?run_program_with_primary_and_secondary_DEN
               (scenario_run_executable                                          //171121
               ,*scenario_dirent_qual
               ,report_filename//171227 *report_format_filename_optional                                 //131006_130610
               ,scenario_run_options
               , !run_simulateously // don't wait for termination if simultaneous run
               , SW_SHOWNORMAL)
            : run_program_with_primary_DEN                                       //131006
               (scenario_run_executable                                          //171121
               ,*scenario_dirent_qual
               ,scenario_run_options
               , !run_simulateously // don't wait for termination if simultaneous run
               , SW_SHOWNORMAL)
         );



      scenarios_run++;
   } FOR_EACH_END(each_scenario_qual)
   return scenarios_run;
}
*/
//______________________________________________________________________________
bool CS_Explorer_engine::run_ultimate_scenario_with_CPF
(const CORN::OS::Directory_name &ultimate_scenario
,bool parallel)                                                            const
{
//   if (is_scenario_ultimate(pot_ultimate_scenario_dirname)) // actually I think caller has already checked
   {

//NYI     171122
// run the general scenario
// generate crop production function subscenarios each will have a fixed
//  management file created to
// the run each of the subscenarios.
// Perhaps run the collator
//    (which will use TDF file(s) defined specifically for CPF output analysis)


 /*180110
  This needs to be redone

  Run the primary simulation
  generate the CPF percents subscenarios
  find the percent scenario dirs and run (in parallel)

 */
   CORN::OS::File_name_concrete &scenario_run_executable                         //171121
      = *preferred_model_executable_qual;                                        //171121
   std::wstring scenario_run_options;                                            //150421_110106

      CORN::OS::File_name_concrete crop_production_function_irrigation_adjustments_filename
         (get_directory_name_qualified(),"irrigation_adjustments.dat");
      if (CORN::OS::file_system_engine.exists(crop_production_function_irrigation_adjustments_filename))             //150418
      {
         //171121 scenario_run_executable.set_DEN(CS::Suite_directory->CropSyst().CPF_runner_executable());


         // I Dont think I need runner any more,
         // just run the primary ultimate scenarios in sequence
         // need to wait for all of these to finish,
         // then can generate the CPF percent scenarios
         // which can be run in parallel.


         scenario_run_executable = CS::Suite_directory->CropSyst().CPF_runner_executable(); //171121
         crop_production_function_irrigation_adjustments_filename.append_components_to(scenario_run_options);
      } else if (CPF_percents_water)                                             //150418
      {
         //scenario_run_options.append(L"irrigation_adjustments_percent=");
         for (nat8 percent_index = 0; percent_index < 16; percent_index++)
         {
            //171121 scenario_run_executable.set_DEN(CS::Suite_directory->CropSyst().CPF_runner_executable());
            scenario_run_executable = CS::Suite_directory->CropSyst().CPF_runner_executable(); //171121
            if ((1 << percent_index) & CPF_percents_water)
            {
               nat8 percent = percent_index * 10;
               CORN::append_nat32_to_wstring(percent,scenario_run_options);
               scenario_run_options.append(L" ");
            }
         }
      }

/*180110 This needs to be redone

      command_history.
         add_wstring
         ((report_filename.length()) //171227 report_format_filename_optional                                        //131006
            ?run_program_with_primary_and_secondary_DEN
               (scenario_run_executable                                          //171121
               ,ultimate_scenario
               ,report_filename//171227 *report_format_filename_optional                                 //131006_130610
               ,scenario_run_options
               , !run_simulateously // don't wait for termination if simultaneous run
               , SW_SHOWNORMAL)
            : run_program_with_primary_DEN                                       //131006
               (scenario_run_executable                                          //171121
               ,ultimate_scenario
               ,scenario_run_options
               , !run_simulateously // don't wait for termination if simultaneous run
               , SW_SHOWNORMAL)
         );
*/
   }
   return true;
}
//_2018-01-10___________________________________________________________________
CropSyst::Project_directory
*CS_Explorer_engine::provide_project_directory()
{  if (identify_context() == project_context)
   {  if (project_directory)
      {  // If we have already setup a project directory, check that it matches the current project directory
         // If it doesn't then we have entered a different project context,
         // and we will and a new project directory
         if (get_active_directory(). //180723 directory_name_qualified->
             compare_including(*project_directory)!= 0)
         {  delete project_directory;
            project_directory = 0;
         }
      }
      if (!project_directory)
      {  project_directory = new
            CropSyst::Project_directory(get_active_directory() //180723 *directory_name_qualified
               ,CROPSYST_PROJECT) ;
      }
   }
   return project_directory;
}
//______________________________________________________________________________
bool CS_Explorer_engine::launch_output_fast_graph()                        const
{
   CORN::OS::File_name_concrete daily_UED_filename(get_active_directory() //180723 *directory_name_qualified
      ,"daily","UED"); //130123
   return run_program_with_primary_DEN
      (CS::Suite_directory->CropSyst().fastgraph_executable()
      ,daily_UED_filename
      , L""
      , false // don't wait_for_termination
      , SW_SHOWNORMAL);
}
//______________________________________________________________________________
bool CS_Explorer_engine::launch_output_schedule_viewer()                   const
{
   CORN::OS::File_name_concrete schedule_filename(get_active_directory()/*180723 *directory_name_qualified*/,"schedule","txt"); //130123
   return run_program_with_primary_DEN
      (CS::Suite_directory->CropSyst().schedule_viewer_executable()
      ,schedule_filename
      , L""
      , false // don't wait_for_termination
      , SW_SHOWNORMAL);
}
//______________________________________________________________________________
bool CS_Explorer_engine::launch_output_schedule_text_viewer()              const
{  CORN::OS::File_name_concrete schedule_filename(get_active_directory()/*180723 *directory_name_qualified*/,"schedule","txt");  //130123
   return CORN::OS::file_system_engine.view_file(schedule_filename);
}
//______________________________________________________________________________
bool CS_Explorer_engine::launch_output_harvest_report_viewer()             const
{  CORN::OS::File_name_concrete harvest_filename(get_active_directory()/*180723 *directory_name_qualified*/,"harvest","htm");  //130123
   return CORN::OS::file_system_engine.view_file(harvest_filename);
}
//______________________________________________________________________________
bool CS_Explorer_engine::scenario_output_has_file(const char *filename_unqual)    const
{  CORN::OS::File_name_concrete output_filename(get_active_directory()/*180723 *directory_name_qualified*/,filename_unqual); //120518
   return CORN::OS::file_system_engine.exists(output_filename);
}
//____________________________________________________scenario_output_has_file_/
class Simulation_run_period_data_record
: public CORN::Data_record
{  // NOTE: This class is duplicated in CS_explorer_engine,  I only really need one

 public:  // "simulation" section
   CORN::Date_clad_32 starting_date;
   CORN::Date_clad_32 ending_date;
   CORN::OS::File_name_concrete output_options_filename_rel;
 public:  //
   inline Simulation_run_period_data_record()
      : CORN::Data_record("simulation")
      , starting_date((CORN::Year)2000,(CORN::DOY)1) //170826 ,D_YMD,D_YYYY|D_Mmm|D_lead_zero,'/')
      , ending_date  ((CORN::Year)2001,(CORN::DOY)1) //170826 ,D_YMD,D_YYYY|D_Mmm|D_lead_zero,'/')
   {}
public:  //
   inline virtual bool expect_structure(bool for_write)
   {  bool expected = CORN::Data_record::expect_structure(for_write);            //120314
      set_current_section(LABEL_simulation);
      expect_int32(LABEL_starting_date,starting_date.mod_date32());              //171117_170532
      expect_int32(LABEL_ending_date,ending_date.mod_date32());                  //171117_170532
      set_current_section("output");
      expect_file_name("options",output_options_filename_rel);
      structure_defined = true;                                                  //130123
      return expected;
   }
};
//______________________________________________________________________________
bool CS_Explorer_engine::output_export_UED_to_XLS_file_command_line
(const CORN::OS::File_name &XXXXX_ued
,const CORN::OS::File_name &XXXXX_xxx
,const CORN::OS::File_name &XXXXX_tdf
,bool include_full_year)                                                   const
{
   Simulation_run_period_data_record sum_run_period;
   CORN::OS::Directory_name_concrete scenario_dir
      (get_active_directory()/*180723 *directory_name_qualified*/
      ,CORN::OS::Directory_entry_name::include_ancestors_path_designated);       //161029
   CORN::OS::File_name_concrete scenario_filename(scenario_dir,".CropSyst_scenario");
   #if (CS_VERSION == 4)
   // We don't have a new scenario file, it may be and old version 4 scenario
   // so just use the backup file to get the path
   if (!CORN::OS::file_system_engine.exists(scenario_filename))
      scenario_filename.set_cstr("backup.csn");  // This is sort of a hack: Version 4 makes this backup copy of the scenario file, I am using this as a convenient way to find the parameter file
   #endif
   VV_File scenario_file(scenario_filename.c_str());
   scenario_file.get(sum_run_period);
   CORN::Date_clad_32 include_starting_date(sum_run_period.starting_date);
   if (include_full_year) include_starting_date.set_DOY(1);
   CORN::Date_clad_32 include_endinging_date(sum_run_period.ending_date);
   if (include_full_year) include_endinging_date.set_DOY(sum_run_period.ending_date.days_in_this_year());
   CORN::OS::File_name_concrete ued_filename(get_active_directory()/*180723 *directory_name_qualified*/,XXXXX_ued.w_str()); //130123
   CORN::OS::File_name_concrete xxx_filename(get_active_directory()/*180723 *directory_name_qualified*/,XXXXX_xxx.w_str()); //130123
   CORN::OS::File_name_concrete tdf_filename(get_active_directory()/*180723 *directory_name_qualified*/,XXXXX_tdf.w_str()); //130123
   if (xxx_filename.has_in_path_cstr("soil",CORN::OS::Directory_entry_name::include_path,false))
   {
      CORN::OS::Directory_name_concrete output_soil_dir(get_active_directory()/*180723 *directory_name_qualified*/,"soil",CORN::OS::directory_entry); //161029
      CORN::OS::file_system_engine.provide_directory/*180321 create_directory*/(output_soil_dir);

      // NYI at this point we are in the output directory
      // CropSyst run does not create a context for the scenario output
      // but we could do it now if it doesn't already exist

   }
   #define USE_convert_text_dBase_Excel_with_TDF_executable
   #ifdef USE_convert_text_dBase_Excel_with_TDF_executable
// Eventually I will implement the Excel tabular file in the UED convertor
   UED::Convertor_arguments response;
   response.operation         ="export";
   response.UED_filename      .set_DEN(ued_filename);                            //130123
   response.station_IDs_filter="";
   response.use_station_name  = false; // default UED will match the location
   response.year_earliest     = include_starting_date.get_year();
   response.year_latest       = include_endinging_date.get_year();
   response.date_time_earliest= include_starting_date.get_datetime64();
   response.date_time_latest  = include_endinging_date.get_datetime64();
   // N/A   response.prefix            = cropsyst_prefix_edit->Text.c_str();
   response.target_filename   .set_DEN(xxx_filename);                            //130123
   response.format_filename   .set_DEN(tdf_filename);                            //130123
   CORN::OS::File_name_concrete convert_rsp(Directory_name_concrete(),"convert.rsp");
   CORN::VV_File response_file(convert_rsp.c_str());
   response_file.set(response);
   return run_program_with_primary_DEN                                                  //120412
      (CS::Suite_directory->UED().convert_text_dBase_Excel_with_TDF_executable() //120313
      ,convert_rsp
      ,L"" // options
      ,true // wait for termination
      ,SW_MINIMIZE);
   #else
   // 070621  This will eventually be replaced with UED with TDF convertor
   // but I haven't implemented the Excel tabular file
   if (ued_filename.exists()      && tdf_filename.exists())
   {  char date_num_buf[10];
      Ustring options("\"");
      options.append(xxx_filename);  // File name is quoted (I.e. xls file)
      options.append("\" ");
      if (xxx_filename.find("nnual") != SUBSTRING_NOT_FOUND)
      {  // if the output is annual and the starting data is jan 1
         // then hack the start date to be dec31 of previous year to get the effective initial condintions
         // in the annual reprochange this to
         if (include_starting_date.get_DOY() == 1)
            include_starting_date.dec();
      }
      options.append(ltoa(include_starting_date.get_date32(),date_num_buf,10));
      options.append(" ");
      options.append(ltoa(include_endinging_date.get_date32(),date_num_buf,10));
      return run_program_with_file_with_primary_and_secondary_file
      (CS::Suite_directory->UED().convert_export_executable()
      ,ued_filename
      ,tdf_filename
      ,options
      ,true // wait for termination
      ,SW_MINIMIZE);
   }
   return true;
   #endif
}
//______________________________________________________________________________
const CropSyst::Scenario_output_options* CS_Explorer_engine::provide_output_options() provision_
{  if (output_options) delete output_options;
   if (identify_context() == scenario_output_context)
   {  Simulation_run_period_data_record sum_run_period;
      CORN::OS::File_name_concrete scenario_filename(get_active_directory()/*180723 *directory_name_qualified*/,".CropSyst_scenario");
      VV_File   scenario_file(scenario_filename.c_str());
      scenario_file.get(sum_run_period);
      if (CORN::OS::file_system_engine.exists(sum_run_period.output_options_filename_rel))

         //130123 WARNING, may need to resolve output_options_filename_rel if it is relative

      {  output_options = new CropSyst::Scenario_output_options ;
         VV_File output_options_file(sum_run_period.output_options_filename_rel.c_str());
         output_options_file.get(*output_options);
      }
   }
   return output_options;
}
//______________________________________________________________________________
bool CS_Explorer_engine
::edit_file_if_known_type(const STRING_WITH_FILENAME &filename)            const
{  bool result = false;
   CORN::OS::File_name_concrete  file_name_to_edit(filename);
   command.clear();
   if      (file_name_to_edit.has_extension_ASCII(CS_scenario_EXT,true))       /*180128 command.assign(*/ result = edit_parameter_file(filename,CS_scenario_EXT  ,context_strings[scenario_context]  .editor /*"scenario_editor"   */,0); //);
   else if (file_name_to_edit.has_extension_ASCII(CS_crop_EXT,true))           /*180128 command.assign(*/ result = edit_parameter_file(filename,CS_crop_EXT      ,context_strings[crop_context]      .editor /*"crop_editor"       */,0); // );
   else if (file_name_to_edit.has_extension_ASCII(CS_soil_EXT,true))           /*180128 command.assign(*/ result = edit_parameter_file(filename,CS_soil_EXT      ,context_strings[soil_context]      .editor /*"soil_editor"       */,0); //);
   else if (file_name_to_edit.has_extension_ASCII(CS_rotation_EXT,true))       /*180128 command.assign(*/ result = edit_parameter_file(filename,CS_rotation_EXT  ,context_strings[rotation_context]  .editor /*"rotation_editor"   */,0); //);
   else if (file_name_to_edit.has_extension_ASCII(CS_management_EXT,true))     /*180128 command.assign(*/ result = edit_parameter_file(filename,CS_rotation_EXT  ,context_strings[management_context].editor /*"management_editor" */,0); //);
   else if (file_name_to_edit.has_extension_ASCII("UED",false))                /*180128 command.assign(*/ result = edit_parameter_file(filename,"UED"            ,context_strings[weather_context]   .editor /*"weather_editor"    */,0); //);
   else if (file_name_to_edit.has_extension_ASCII(CS_biomatter_EXT,true))      /*180128 command.assign(*/ result = edit_parameter_file(filename,CS_biomatter_EXT ,context_strings[biomatter_context] .editor /*"biomatter_editor"  */,0); //);
#if (CS_VERSION==4)
   else if (file_name_to_edit.has_extension_ASCII("LOC",true))                 /*180128 command.assign(*/ result = edit_parameter_file(filename,"LOC"            ,"CropSyst\\location_editor"   ,0); //);
   else if (file_name_to_edit.has_extension_ASCII("FMT",true))                 /*180128 command.assign(*/ result = edit_parameter_file(filename,"FMT"            ,context_strings[format_context]    .editor /*"format_editor"     */,0); //);
   // In version 4, the following file types are text files so should be picked up as simply open
//NYI      :   (file_name_to_edit.has_extension_ASCII(CS_water_table_EXT))    ? edit_parameter_file(filename,CS_water_table_EXT,"xxxxx",0)
//NYI      :   (file_name_to_edit.has_extension_ASCII(CS_recalibration_EXT))     ? edit_parameter_file(filename,CS_recalibration_EXT,"xxxxx",0)
#endif
   else
   {
      std::string file_name; file_name_to_edit.append_components_to_string(file_name,CORN::OS::Directory_entry_name::include_name);     //130123
      std::string file_ext;
      CORN::wstring_to_string(file_name_to_edit.get_extension(),file_ext);       //140111
      bool has_filename = file_name.length();
      bool has_ext      = file_ext .length();
      for (int context = 0; context < CONTEXT_COUNT; context++)
      {  // For each context type, check if the filename matches the name or extension for the context
         bool valid_context_file_ext_or_name = context_strings[context].parameter_file_ext_or_name;
         bool valid_context_ext              = context_strings[context].parameter_file_ext;
         if (  (has_filename && valid_context_file_ext_or_name && (file_name == context_strings[context].parameter_file_ext_or_name))
             ||(has_filename && valid_context_ext              && (file_name == context_strings[context].parameter_file_ext        ))
             ||(has_ext      && valid_context_file_ext_or_name && (file_ext  == context_strings[context].parameter_file_ext_or_name))
             ||(has_ext      && valid_context_ext              && (file_ext  == context_strings[context].parameter_file_ext        )))
         {
            //180128 command.assign (
                  return edit_parameter_file
                  (filename
                  ,context_strings[context].parameter_file_ext
                  ,context_strings[context].editor ,0); // );
         }
      }
   }
   if (!command.length()) // Not a CS_suite file
      result = Explorer_engine_abstract::edit_file_if_known_type(filename);
   return result;
}
//______________________________________________________________________________
bool CS_Explorer_engine::scenario_edit()                                   const
{
   CORN::OS::File_name_concrete scenario_file_name;                              //171228
   CORN::OS::File_name_concrete scenario_editor(CS::Suite_directory->CropSyst().scenario_editor_executable());
   bool is_version_5_CropSyst_scenario = true;
   {  // Support for version 5
      CORN::OS::File_name_concrete curr_scenario_filename(get_active_directory()/*180723 *directory_name_qualified*/,L".CropSyst_scenario"); //171228
      is_version_5_CropSyst_scenario = CORN::OS::file_system_engine.exists(curr_scenario_filename);


      if (is_version_5_CropSyst_scenario)
         scenario_file_name.set_DEN(curr_scenario_filename);
      if (!CORN::OS::file_system_engine.exists(scenario_editor))
           scenario_editor.set_DEN(CS::Suite_directory->CAFE().Dairy().field_editor_executable()); //140111
   }
   if (!is_version_5_CropSyst_scenario)
   {  // Support for version 4:
      CORN::OS::File_name_concrete scenario_file_name(L".CropSyst_scenario");
      CORN::OS::File_name_concrete csn_scenario_filename(get_active_directory()/*180723 *directory_name_qualified*/,L"csn");
      if (CORN::OS::file_system_engine.exists(csn_scenario_filename))
         scenario_file_name.set_DEN(csn_scenario_filename);
      else
      {                                                                           //110106
         CORN::OS::File_name_concrete CAFE_dairy_scenario_filename(get_directory_name_qualified(),L".CAFE_dairy_scenario");
         if (CORN::OS::file_system_engine.exists(CAFE_dairy_scenario_filename))
         {
            scenario_file_name.set_DEN(CAFE_dairy_scenario_filename);
            scenario_editor.set_DEN(CS::Suite_directory->CAFE().Dairy().scenario_editor_executable());
         }
      }
   }
   return run_program_with_primary_DEN                                           //180128
      ( scenario_editor
      , scenario_file_name
      , L""
      , false // wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL
      );
}
//______________________________________________________________________________
bool CS_Explorer_engine::scenario_edit_model(nat8 model_index) const
{  bool result = false;                                                          //180128
   CORN::OS::File_name_concrete *single_scenario_file_name = 0;
   CORN::OS::File_name_concrete *scenario_editor = 0;
   switch (model_index)
   {
      case 0 : // CropSyst
         single_scenario_file_name = new CORN::OS::File_name_concrete(get_directory_name_qualified(),".CropSyst_scenario");
         scenario_editor = new CORN::OS::File_name_concrete(CS::Suite_directory->CropSyst().scenario_editor_executable());

         // When only NIFA (or CAFE or CANMS) is installed,
         // then we are probably in a field directory
         // use the simple field editor
         if (!CORN::OS::file_system_engine.exists(*scenario_editor))
         {
            delete scenario_editor;
            scenario_editor = new CORN::OS::File_name_concrete
               (CS::Suite_directory->CAFE().Dairy().field_editor_executable());
         }
      break;
      case 1 : // NIFA dairy
         single_scenario_file_name = new CORN::OS::File_name_concrete
            (get_directory_name_qualified(),L".NIFA_dairy_scenario");
         scenario_editor = new CORN::OS::File_name_concrete(CS::Suite_directory->CAFE().Dairy().scenario_editor_executable());
         // CAFE and NIFA dairy editor are the same
         //NYI CS::Suite_directory->XXX.scenario_editor_executable());
      break;
      case 2 : // CAFE dairy
         single_scenario_file_name = new CORN::OS::File_name_concrete
            (get_directory_name_qualified(),L".CAFE_dairy_scenario");
         // CAFE and NIFA dairy editor are the same
         scenario_editor = new CORN::OS::File_name_concrete(CS::Suite_directory->CAFE().Dairy().scenario_editor_executable());
      break;
      case 3 : // CANMS
         single_scenario_file_name = new CORN::OS::File_name_concrete
            (get_directory_name_qualified(),L".CAFE_dairy_scenario");
         //NYI scenario_editor = new CORN::OS::File_name_concrete(CS::Suite_directory->CANMS .scenario_editor_executable());
      break;
   }

   if (   single_scenario_file_name
       && CORN::OS::file_system_engine.exists(*single_scenario_file_name))
   {  result =
      (run_program_with_primary_DEN
      ( *scenario_editor
      , *single_scenario_file_name
      , L""
      , false // wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL
      ));                                                                        //130123
   } // else caller setups for editing compositional scenario in nativation composition tab
   return result;
}
//_2017-12-28__________________________________________________________________/
bool CS_Explorer_engine::scenario_run_GIS()                                const
{  std::wstring no_options;
   run_program_with_primary_DEN                                                  //120411
         (CS::Suite_directory->CropSyst().GIS_runner_executable()
         ,get_active_directory()/*180723 *directory_name_qualified*/
         ,no_options
         , false // do not wait for termination
         , true /*visible was SW_SHOWNORMAL*/);
   return true;
}
//_2014-02-14__________________________________________________________________/
bool CS_Explorer_engine
::get_context_icon_filename(CORN::OS::File_name &icon_filename,int &icon_index) const
{  bool icon_filename_available = true;
   icon_index = 0;
   switch (context_strings[identify_context()].mode)
   {  case 0 : icon_filename_available = false;  break; // no icon for arbitrary context
      case 1 : icon_filename_available =  false; break; // don't yet have UED icons directory
      case 2 :
      {  CORN::OS::File_name_concrete icon_fname(CS::Suite_directory->icons(),context_strings[identify_context()].icon,"ico");
         icon_filename.set_DEN(icon_fname);
      } break;
      case 3 :
      {  CORN::OS::File_name_concrete icon_fname(CS::Suite_directory->CropSyst(),context_strings[identify_context()].icon,"ico");
         icon_filename.set_DEN(icon_fname);
      } break;
   }
   if (icon_filename_available) // so far so good
       icon_filename_available = context_strings[identify_context()].icon != 0;
   return icon_filename_available;
}
//__________________________________________________get_context_icon_filename__/
bool CS_Explorer_engine
::get_context_description(std::string &description)                        const
{  description.assign(context_strings[identify_context()].description);
      ///< The derived class should override to set the brief one line description. (Currently this codes in the desktop infotip).
      ///  By default no description is assigned.
      ///\return false if this folder does not need or should not have a description.
   return true;
}
//____________________________________________________get_context_description__/
bool CS_Explorer_engine::get_specified_context
(modifiable_ std::string &context) const
{
   nat16 context_index = identify_context();
   bool got = (bool)context_index;
   if (got)
      context.assign(context_strings[identify_context()].context);
   else
      got = //180723 Explorer_engine_abstract::
         provide_contextualization().get_specified_context(context);
   return got;
}
//_2017-12-31___________________________________________________________________
bool CS_Explorer_engine
::navigator_double_clicked_file(const STRING_WITH_FILENAME &item_path)     const
{  bool did_something = false;
   CORN::OS::File_name_concrete file_name_to_process(item_path);                 //130418
   if (edit_file_if_known_type(item_path)/*180128 .length()*/)
         did_something = true;
   else
   {  int open_status = CORN::OS::file_system_engine.open_file(file_name_to_process);
#ifdef NYI
         switch (open_status < 32)
         {
/* NYI
ERROR_FILE_NOT_FOUND The specified file was not found.
ERROR_PATH_NOT_FOUND The specified path was not found.
ERROR_BAD_FORMAT The .exe file is invalid (non-Microsoft Win32 .exe or error in .exe image).
SE_ERR_ACCESSDENIED The operating system denied access to the specified file.
SE_ERR_ASSOCINCOMPLETE The file name association is incomplete or invalid.
SE_ERR_DDEBUSY The Dynamic Data Exchange (DDE) transaction could not be completed because other DDE transactions were being processed.
SE_ERR_DDEFAIL The DDE transaction failed.
SE_ERR_DDETIMEOUT The DDE transaction could not be completed because the request timed out.
SE_ERR_DLLNOTFOUND The specified DLL was not found.
SE_ERR_FNF The specified file was not found.
SE_ERR_NOASSOC There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable.
SE_ERR_OOM There was not enough memory to complete the operation.
SE_ERR_PNF The specified path was not found.
SE_ERR_SHARE A sharing violation occurred.
*/
            case 0: case default:
            {  // Invoke open failed
               // NYI
            }
            break;
         }
#endif
         did_something = open_status > 32;                                       //130416
         command.clear(); // invoke_open uses Windows API ShellExecute so the command is not available
         // Set explorer_engine recently selected file because it may be used
         // in the next invoked function.
         recently_selected_DEN[identify_context()].set_wstr(item_path.c_str());
   }
   return did_something;
}
//_navigator_double_clicked_file_______________________________________________/
bool CS_Explorer_engine
::navigator_single_clicked_file(const STRING_WITH_FILENAME &item_path)     const
{
   // Set explorer_engine recently selected file because it may be used
   // in the next invoked function.
   nat8 identified_context = identify_context();
   if (identified_context < CONTEXT_COUNT)
      recently_selected_DEN[identified_context].set_wstr(item_path.c_str());
   return true;
}
//_navigator_single_clicked_file_______________________________________________/

bool CS_Explorer_engine::CANMS_scenario_edit()      const
{
   CORN::OS::File_name_concrete *scenario_file_name_ptr= new CORN::OS::File_name_concrete(get_directory_name_qualified(),L".CANMS_scenario");
   if (!CORN::OS::file_system_engine.exists(*scenario_file_name_ptr))
   {  // this is a version 4 scenario
      delete scenario_file_name_ptr;
      scenario_file_name_ptr = new  CORN::OS::File_name_concrete(L".CANMS_scenario");
   } //else  this is a version 5 scenario
   CORN::OS::File_name_concrete &scenario_file_name = *scenario_file_name_ptr;
   CORN::OS::File_name_concrete scenario_editor(CS::Suite_directory->CropSyst().scenario_editor_executable());
   //180128 const STRING_WITH_FILENAME &result =
   return run_program_with_primary_DEN
      ( scenario_editor
      ,  scenario_file_name
      , L""
      , false // wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL
      );
   //180128 return result;
}
//_CANMS_scenario_edit_________________________________________________________/
Directory_context CS_Explorer_engine
::assume_context(Directory_context assumed_context,bool permanently) modification_
{  identified_context = assumed_context;
   return identified_context;
}
//_assume_context______________________________________________________________/
nat8 CS_Explorer_engine::get_model_version()                               const
{  return (preferred_model_executable_qual
      && (preferred_model_executable_qual->get_name() == L"CropSyst_4"))
      ? 4: 5;
}
//_get_model_version________________________________________________2018-03-26_/
//180128 const STRING_WITH_FILENAME &
bool CS_Explorer_engine::map_UED_locations()                               const
{  bool result = run_program_with_primary_DEN                                    //180128
      ( CS::Suite_directory->UED().map_google_executable()
      , get_active_directory()/*180723 *directory_name_qualified*/
      , L"" //options
      , false // wait_for_termination     // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);
   CORN::OS::File_name_concrete location_map(get_active_directory()/*180723 *directory_name_qualified*/,L"locations_map.htm");
   result &= CORN::OS::file_system_engine.view_file(location_map);               //180128
   //180128 return command;
   return result;
}
//______________________________________________________________________________
bool CS_Explorer_engine::launch_notepad()          const
{  return
      CORN::OS::file_system_engine.exists(recently_selected_DEN[identified_context])
      ?  run_program_with_primary_DEN
         ( //"notepad.exe"           // fully qualified name of the program to run (unquoted)
          CORN::OS::File_name_concrete("notepad.exe")
         , recently_selected_DEN[identified_context] // primary_file
         , L"" // no options
         , false // don't wait_for_termination     // True if this editor is held until the other program exits
         , true   // visible
         )
      : Explorer_engine_abstract::launch_notepad();
}
//_____________________________________________________________launch_notepad__/
bool CS_Explorer_engine::launch_UED_condense()     const
{
   //101136 This should probably launch all selected UED files.
   return
      (CORN::OS::file_system_engine.exists(recently_selected_DEN[identified_context])
       && recently_selected_DEN[identified_context].has_extension_ASCII("UED",false)) // Only condense UED filenames
      ?  run_program_with_primary_DEN                                            //120516
         (CS::Suite_directory->UED().condense_executable()
         , recently_selected_DEN[identified_context] // primary_file
         , L"" // no options
         , false // don't wait_for_termination     // True if this editor is held until the other program exits
         , true   // visible
         )
      : false; //180128 command;
}
//_______________________________________________________________UED_condense__/
bool CS_Explorer_engine::launch_CropSyst_wizard()                          const
{  run_program(CS::Suite_directory->CropSyst().CropSyst_wizard_executable(),L"",false,true);
   return true;
}
//_2014-10-22_______________________________________________________________launch_CropSyst_wizard___/
bool CS_Explorer_engine::update_application_suite()                        const
{  return (int)ShellExecuteW(0,L"runas",CS::Suite_directory->install_or_update().w_str(),NULL,NULL,SW_SHOW)>32;
}
//_2012-01-12________________________________________update_application_suite__/
bool CS_Explorer_engine::translate_AgMIP_ACE     // actually this could be renamed to indicate any translator program
(const CORN::OS::File_name &translator_exe
,const CORN::OS::File_name &JSON_filename)    const
{
   return run_program_with_primary_DEN
      ( translator_exe, JSON_filename
      , L"" , true  , SW_SHOWNORMAL);
}
//_2013-04-18_____________________________________________translate_AgMIP_ACE__/
nat16 CS_Explorer_engine::translate_AgMIP_ACE_JSON_files
(const CORN::Text_list &selected_JSON_filenames_presumed)                  const
{  nat16 translated = 0;
   bool ACE_to_CropSyst_translator_installed = true;
   CORN::OS::File_name *ACE_to_CropSyst_translator =
      (CS::Suite_directory->find_file_name
         (L"ACE_to_CropSyst.exe" ,CORN::OS::File_system::subdirectory_recursion_exclusive));  //161003
   if (ACE_to_CropSyst_translator_installed)
   FOR_EACH_IN(selected_filename,Item_wstring ,selected_JSON_filenames_presumed,each_JSON_file)
   {
      CORN::OS::File_name_concrete selected_filename_instance(get_directory_name_qualified(),*selected_filename); //130513
      if (selected_filename_instance.has_extension_ASCII("json",false))
      {  translated += translate_AgMIP_ACE(*ACE_to_CropSyst_translator,selected_filename_instance);
      }
   } FOR_EACH_END(each_JSON_file)
   return translated;
}
//_2013-04-18___________________________________________________________________
int CS_Explorer_engine::export_scenarios
(const CropSyst::Scenario_export_engine::Arguments &export_args
,nat8 format_index)
{
   CORN::OS::File_name *exporter_exe =
      (CS::Suite_directory->find_file_name
         ((format_index == 1)
            ?L"CropSyst_to_ACMO.exe"
            :L"CropSyst_to_ACE.exe"
         ,true));
   // NYI should append command to command history
   if (exporter_exe)                                                             //150503
      run_program                                                                //120411
      ( *exporter_exe
      , export_args.compose()
      , false // dont wait_for_termination
      , true); // visible
   delete exporter_exe;
   return 1;
}
//_2013-01-11___________________________________________________________________
nat32 CS_Explorer_engine::UED_file_quality_import_or_export
(const std::string &command
,const CORN::Text_list  &selected_UED_filenames_qual_or_unqual)
{  nat32 files_processed=0;
   FOR_EACH_IN(UED_qual_or_unqual,Item_wstring /*180115 CORN::Text_list::Item*/,selected_UED_filenames_qual_or_unqual,each_UED)
   {
      // Note that selected_UED_filenames_qual_or_unqual could be any file
      // that happens to be in the weather folder.
      // In most situations these will be UED files
      // but the user may have put arbitrary files in this directory.
      // so we filter only UED files
      CORN::OS::File_name_concrete *UED_qual = new CORN::OS::File_name_concrete(*UED_qual_or_unqual);
      if (!UED_qual->is_qualified(false))                                        //120212
      {  delete UED_qual;
         UED_qual = new CORN::OS::File_name_concrete(get_active_directory()/*180723 *directory_name_qualified*/,*UED_qual_or_unqual);
      }
      // UED filename  should now be qualified.
      if (UED_qual->has_extension_ASCII("UED",false))
      {  CORN::OS::File_name_concrete UED_quality_filename(*UED_qual,CORN::OS::Extension("UED_quality"));
         std::wstring args = L"operation=";                                      //171120
         CORN::append_string_to_wstring(command,args);
         CORN::append_string_to_wstring(" UED_filename=\"",args);
         UED_qual->append_to_wstring(args);
         CORN::append_ASCIIZ_to_wstring("\" target_filename=\"",args);
         UED_quality_filename.append_to_wstring(args);
         CORN::append_ASCIIZ_to_wstring("\"",args);
         files_processed += run_program
            (CS::Suite_directory->UED().quality_import_export_executable()
            ,args, true,SW_SHOWNORMAL);
      }
      delete UED_qual;
   } FOR_EACH_END(each_UED)
   return files_processed;
}
//_2014-06-29___________________________________________________________________
bool CS_Explorer_engine::generate_scenarios
(const CORN::Text_list &selected_scenario_filenames_unqual)                const
{  bool generated = true;
   std::wstring args;
   FOR_EACH_IN(dir_name,CORN::Item_wstring,selected_scenario_filenames_unqual,each_scenario)
   {
      args.append(L" --template=");
      args.append((*dir_name));
   } FOR_EACH_END(each_scenario)

   CORN::OS::File_name *generator_exe =
      (CS::Suite_directory->find_file_name
         (L"generator.exe"
         ,CORN::OS::File_system::subdirectory_recursion_exclusive));
   // NYI should append command to command history
   if (generator_exe)                                                             //150503
   {  generated = //180128 true;
      run_program                                                                //120411
      ( *generator_exe
      , args
      , true // dont wait_for_termination
      , true); // visible
   }
   delete generator_exe;
   return generated;
}
//_2016-11-03___________________________________________________________________
bool CS_Explorer_engine::netCDF_to_UED
(const std::wstring &geocoordinates_filename
,const std::wstring &bounding_box_coord1
,const std::wstring &bounding_box_coord2
,const std::wstring &cell_size_and_units
,const CORN::Date &date_from
,const CORN::Date &date_to)
{
   std::wstring args;
   args + geocoordinates_filename;                                args += L" ";
   args += bounding_box_coord1;                                   args += L" ";
   args += bounding_box_coord2;                                   args += L" ";
   args += cell_size_and_units;                                   args += L" ";
   CORN::append_int32_to_wstring(date_from.get_date32(),args);    args += L" ";
   CORN::append_int32_to_wstring(date_to  .get_date32(),args);    args += L" ";
   CORN::OS::File_name *netCDF_to_UED_exe = CS::Suite_directory->find_file_name
      (L"netCDF_to_UED"
      ,CORN::OS::File_system::subdirectory_recursion_exclusive);
   return (netCDF_to_UED_exe)
      ? run_program(*netCDF_to_UED_exe,args,false,true)
      : false;
}
//_2016-11-13___________________________________________________________________
bool CS_Explorer_engine::prefer_model_executable                                                     //171121
(const wchar_t *model_executable_qual)                            rectification_
{
   delete preferred_model_executable_qual;
   preferred_model_executable_qual
      = new CORN::OS::File_name_concrete(model_executable_qual);
   return true;
}
//_2017-11-21__________________________________preferred_model_executable_qual_/
nat16 CS_Explorer_engine::compare_directory
(const CORN::OS::Directory_name &source_dir
,const CORN::OS::Directory_name &other_dir
,const CORN::OS::Directory_name &compare_dir)                              const
{
   nat16 compared_UED_file_count = 0;
   CORN::Text_list source_filenames_unqual;
   CORN::Text_list source_dirnames_unqual;
   nat32 DEN_count = file_system_engine.list_names_in
      ( source_dir
      ,&source_filenames_unqual
      ,&source_dirnames_unqual);
   if (!DEN_count) return 0;
   CORN::OS::file_system_engine.provide_directory(compare_dir);
   FOR_EACH_IN(filename_unqual,std::wstring,source_filenames_unqual,each_file)
   {
      CORN::OS::File_name *other_filename = CORN::OS::file_system_engine.find_DEN
         (*filename_unqual,CORN::OS::file_entry,other_dir
         ,CORN::OS::File_system::none_recursion_inclusive);
      if (other_filename && (other_filename->has_extension_ASCII("UED",true))) //case insensitive
      {
         CORN::OS::File_name_concrete source_filename (source_dir ,(*filename_unqual));
         CORN::OS::File_name_concrete compare_filename(compare_dir,(*filename_unqual));

         const CORN::OS::File_name &UED_comparer = CS::Suite_directory->UED().UED_compare_executable();
         std::wstring options(L"\"");
         source_filename.append_components_to(options);
         options.append(L"\" \"");
         other_filename->append_components_to(options);
         options.append(L"\" \"");
         compare_filename.append_components_to(options);
         options.append(L"\"");

         run_program(UED_comparer,options,false,true); // dont wait but show window
         compared_UED_file_count += 1; // eventually increment if run_program success
      }
      delete other_filename;
   } FOR_EACH_END(each_file)
   FOR_EACH_IN(dirname_unqual,std::wstring,source_dirnames_unqual,each_dir)
   {
      CORN::OS::Directory_name_concrete source_sub (source_dir ,*dirname_unqual);
      CORN::OS::Directory_name_concrete other_sub  (other_dir  ,*dirname_unqual);
      if (CORN::OS::file_system_engine.exists(other_sub))
      {
         CORN::OS::Directory_name_concrete compare_sub(compare_dir,*dirname_unqual);
         CORN::OS::file_system_engine.provide_directory/*180321 create_directory*/(compare_sub);
         compared_UED_file_count += compare_directory(source_sub,other_sub,compare_sub);
      }
   } FOR_EACH_END(each_dir)
   return compared_UED_file_count;
}
//_2018-01-27___________________________________________________________________
nat16 CS_Explorer_engine::compare_multiple_directories
(const CORN::OS::Directory_name &primary_dir
,const CORN::Container &other_dirnames)                                    const
{
   nat16 compared_dir_count = 0;
   // Put the comparison results directory in
   CORN::OS::Directory_name_concrete comparison_dir
      (get_directory_name_qualified(),"Comparison");
   FOR_EACH_IN(other_dir,CORN::OS::Directory_name,other_dirnames,each_other)
   {
      std::wstring diff_dir_unqual;
      primary_dir.append_name_with_extension_to(diff_dir_unqual);
      diff_dir_unqual.append(L"-");
      std::wstring other_dir_unqual;
      other_dir->append_name_with_extension_to(other_dir_unqual);
      diff_dir_unqual.append(other_dir_unqual);

      CORN::OS::Directory_name_concrete diff_dir(comparison_dir,diff_dir_unqual);

      // Check if compare_directory creates diff_dir
      compared_dir_count += compare_directory
         (primary_dir,(*other_dir),diff_dir);
   } FOR_EACH_END(each_other)
   return compared_dir_count;
}
//_2018-01-28___________________________________________________________________
nat16 CS_Explorer_engine::instantiate_daily_output_formats()               const
{  nat16 instantiate_count = 0;
   CORN::Unidirectional_list format_files;
   CORN::OS::Directory_name_concrete CS_Database_Format
      (CS::Suite_directory->Database(),"Format");

   CORN::Inclusion daily_TDFs("daily_Excel.TDF",true);                            //180117
   //NYI daily_TDFs.include_pattern("*daily*.TDF")
   CORN::OS::file_system_engine.list_DENs
      ( CS_Database_Format // may want to put this under Database
      ,&format_files,0,daily_TDFs
      ,CORN::OS::File_system::subdirectory_recursion_inclusive);
   FOR_EACH_IN(format_filename,CORN::OS::File_name,format_files,each_format)
   {
      std::wstring format_name_with_ext;;                                        //180125
      CORN::OS::File_name_concrete target
         (get_directory_name_qualified(),format_filename->
            get_name_with_extension(format_name_with_ext));                      //180125
      instantiate_count += instanciate_DEN(*format_filename,target);
      // instantiate_count += instanciate_wstr(format_filename->w_str(),target.w_str());
   } FOR_EACH_END(each_format)
   return instantiate_count;
}
//_2017-11-24___________________________________________________________________
bool CS_Explorer_engine::is_installed_CANMS()                       affirmation_
{
   return CORN::OS::file_system_engine.exists(CS::Suite_directory->CANMS());
}
//_2017-12-06__________________________________________________________________/
/*180723 moved to CS_contextualization
bool CS_Explorer_engine::is_scenario_ultimate
(const CORN::OS::Directory_name *dir)                               affirmation_
{

//   const CORN::OS::Directory_name &dir = (specified_dir != NULL)
//      ? *specified_dir
//      : get_directory_name_qualified();


   return ! is_beneath("*Output",dir)                                            //180406
      &&  (has_monument("*Output",dir)                                           //180406

//   return ! is_beneath("*utput*",dir)                                            //180404
//      &&  (has_monument("*utput*",dir)                                           //180404

      ||  !has_any_subscenario   (dir));
}
//_2017-12-27__________________________________________________________________/
bool CS_Explorer_engine::is_scenario_level
(const CORN::OS::Directory_name *dir)                               affirmation_
{  return is_underneath("Scenarios",dir)
      && !is_beneath("*Output",dir);                                             //180406
}
//_2017-12-27__________________________________________________________________/
bool CS_Explorer_engine::has_any_subscenario
(const CORN::OS::Directory_name *specified_dir)                     affirmation_
{
   bool has_subscenario = is_scenario_level(specified_dir);
      // For far dir is a scenario
   if (has_subscenario)
   {
      const CORN::OS::Directory_name &dir
         = (specified_dir)
            ? *specified_dir
            : get_directory_name_qualified();
      CORN::Text_list subdirs;
      nat32 subdir_count = CORN::OS::file_system_engine
         .list_names_in(dir,0,&subdirs);
      has_subscenario = subdir_count;
      //* NYI
      //   Currently assuming any other subdirs are subscenarios
      //   but should check that any of the subdirs are actually scnearios

   }
   return has_subscenario;
}
//_2017-12-27__________________________________________________________________/
*/
/*171231 NYI
CS_Explorer_engine::provide_monuments()
{
   Stream_Unicode
}
*/
//_2017-12-31________________________________________________provide_monuments_/
bool CS_Explorer_engine::BlackBoard_promotion()                    modification_
{
   CORN::OS::Directory_name_concrete blackboard_dir
      (get_directory_name_qualified(),"BlackBoard");
   CORN::OS::file_system_engine.provide_directory/*180321 create_directory*/(blackboard_dir);
   return true;
}
//_2018-01-01___________________________________________________________________
bool CS_Explorer_engine::output_generate_report
(const char *format_TDF    // I.e. "annual_Excel.TDF"
,const char *pattern_UED   // I.e. "*@annual$d.UED" "*@seasonal$d.UED"
,const char *report_xls    // I.e. "annual.xls"
)                                                                          const
{

   //operation=export format_filename="C:\CS_Suite_5\Database\Format\annual_Excel.TDF" UED_filenames="G:\FVSC\potato\Simulation\Scenarios\test_roger\Historical\CO2_360\CA\35.06N118.90W\Output\0\land_unit@annual$d.UED","G:\FVSC\potato\Simulation\Scenarios\test_roger\Historical\CO2_360\CA\35.06N118.90W\Output\0\soil\soil@annual$d.UED","G:\FVSC\potato\Simulation\Scenarios\test_roger\Historical\CO2_360\CA\35.06N118.90W\Output\0\SOM\organic_matter@annual$d.UED","G:\FVSC\potato\Simulation\Scenarios\test_roger\Historical\CO2_360\CA\35.06N118.90W\Output\meteorology\meteorology@annual$d.UED","G:\FVSC\potato\Simulation\Scenarios\test_roger\Historical\CO2_360\CA\35.06N118.90W\Output\0\annual.UED"  target_filename="annual_test.xls"

   //180108 std::string gen_command("\"");
   //180108 gen_command.append
   //180108    (CS::Suite_directory->UED().convert_text_dBase_Excel_with_TDF_executable().c_str()); //131106

   //180108 gen_command.append("\" ");

   std::wstring gen_options;
   gen_options.append(L"operation=export format_filename=\"");             //171120
   //180113 gen_options.append(L"\"operation=export\" \"format_filename=\"");             //171120

   // For V5 CS_Suite_5/Database/
   CS::Suite_directory->Database().append_components_to(gen_options);
   gen_options += DEFAULT_DIRECTORY_SEPARATORw_chr;
   gen_options.append(L"Format");
   gen_options += DEFAULT_DIRECTORY_SEPARATORw_chr;
   CORN::append_ASCIIZ_to_wstring(format_TDF, gen_options);
   gen_options += L'"';

   /*This was for V4
   gen_command.append("C:\\Simulation\\Database\\Format\\all\\annual.tdf");
   gen_command.append("\" \"UED_filename=");
   CORN::OS::File_name_concrete annual_ued(explorer_engine->get_directory_name_qualified(),"annual.ued");
   gen_command.append(annual_ued.c_str());
   gen_command.append("\" ");  */
   // Eventually search for the .TDF file


   CORN::Unidirectional_list UED_filenames;
   CORN::OS::file_system_engine.list_DENs
      (get_directory_name_qualified()
      ,&UED_filenames
      ,0
      ,CORN::Inclusion(pattern_UED,true)
      ,CORN::OS::File_system::subdirectory_recursion_inclusive);

   gen_options.append( L" UED_filenames=");
   bool first= true;
   FOR_EACH_IN(annual_UED,CORN::OS::File_name,UED_filenames,each_UED)
   {
      if (!first)
         gen_options += L',';
      gen_options += L'"';
      annual_UED->append_components_to(gen_options);
      gen_options += L'"';
      first = false;
   } FOR_EACH_END(each_UED)

   gen_options.append(L" target_filename=\"");
   CORN::OS::File_name_concrete xxxx_xls(get_directory_name_qualified(),report_xls);
   gen_options.append(xxxx_xls.w_str());
   gen_options += L'"';

   //NYI command_history.add_string
   run_program
      ( CS::Suite_directory->UED().convert_text_dBase_Excel_with_TDF_executable()
      , gen_options, false, true);
   // use run_program instead of WinExec
   // WinExec(gen_command.c_str(),SW_NORMAL);

   return true;
}
//_2018-01-07_______________________________________output_generate_report_/
bool CS_Explorer_engine::output_generate_annual_report()                  const //180107
{
   return output_generate_report
      ("annual_Excel.TDF"
      ,"*annual*.UED" // ,"*@annual$d.UED"
      ,"annual.xls");
}
//_2018-01-07____________________________________output_generate_annual_report_/
bool CS_Explorer_engine::output_generate_season_report()                  const //180107
{  return output_generate_report
      ("season_Excel.TDF","*season*.UED","season.xls");
      //"*@seasonal$d.UED"
}
//_2018-01-07____________________________________output_generate_season_report_/
/*180723 moved to CS_contextualization
nat32 CS_Explorer_engine::list_ultimate_scenarios                                                 //180110
(const CORN::OS::Directory_name &level_or_ultimate_scenario
,CORN::Container &ultimates_list
,bool dont_include_percent_dirs)
{
   CORN::Unidirectional_list this_and_subscenarios_pot;

   if (is_scenario_ultimate(&level_or_ultimate_scenario))
      ultimates_list.append(new CORN::OS::Directory_name_concrete(level_or_ultimate_scenario));
   else
   {
      this_and_subscenarios_pot.append(new CORN::OS::Directory_name_concrete(level_or_ultimate_scenario));

      CORN::Seclusion potential_ultimate_pattern
         ("*Output",true,false);
      potential_ultimate_pattern.include_pattern_cstr("*");

      CORN::OS::file_system_engine.list_DENs
         (level_or_ultimate_scenario,0,&this_and_subscenarios_pot
         ,potential_ultimate_pattern
         ,CORN::OS::File_system::subdirectory_recursion_inclusive);
      FOR_EACH_IN(pot_subscenario,CORN::OS::Directory_name,this_and_subscenarios_pot,each_pot_subcenario)
      {
         if (is_scenario_ultimate(pot_subscenario))
         {
            ultimates_list.take(each_pot_subcenario->detach_current());
         }
      } FOR_EACH_END(each_pot_subcenario)
   }
   return ultimates_list.count();
}
//_2018-01-10__________________________________________list_ultimate_scenarios_/
*/
nat32 CS_Explorer_engine::render_relevent_composition
(CORN::Unidirectional_list &relevent_composition)                     rendition_
{
   nat32 rendered_count = 0;
   CORN::Inclusion *relevent_filename_patterns = 0;
   switch (get_identified_context())
   {
      case scenario_context :
      {
         relevent_filename_patterns = new CORN::Inclusion("*.CS_control",true);
         relevent_filename_patterns->include_pattern_cstr("*.CropSyst_scenario");
         relevent_filename_patterns->include_pattern_cstr(".CropSyst_scenario");
         relevent_filename_patterns->include_pattern_cstr(".CropSyst_scenario");
         relevent_filename_patterns->include_pattern_cstr("*/");
         /* Not sure if I want to include geolocation/geocooridanate
            and parameter files.
         */
      }
      break;
      /* NYI
      Eventually all parameter files will be composable especially crop,
      but I havent yet started using composposition for parameter files
      other than scenarios

      */
      /*
      default :
         find all accessible files that have extension associated
         with this directory context type
         (this should handle most parameter files).
      break;
      */
   }
   if (relevent_filename_patterns)
   {
      rendered_count
         =  CORN::OS::file_system_engine.list_DENs
            (get_directory_name_qualified()
            ,&relevent_composition
            ,0 // ignore dirs
            ,*relevent_filename_patterns
            ,CORN::OS::File_system::superdirectory_recursion_inclusive
            ,0 // eventually might want to get the primary project as the logical root
            );
      delete relevent_filename_patterns;
   }
   return rendered_count; // relevent_composition.count();
}
//_render_relevent_composition______________________________________2018-01-18_/
bool CS_Explorer_engine::ultimate_Output_backup()
{
   // Copies the Output directory  to {date}.Output
   CORN::Date_time_clad_64 now;
   std::wstring now_str; now.append_to_wstring(now_str);
   // The standard time includes : but these are not valid for DEN
   std::replace(now_str.begin(),now_str.end(),':','_');

   CORN::OS::Directory_name_concrete source_dir(get_directory_name_qualified(),"Output");
   CORN::OS::Directory_name_concrete target_dir(get_directory_name_qualified(),now_str,"Output");
   return CORN::OS::file_system_engine
      .copy_directory(source_dir,target_dir,true);
      //.copy_directory_contents(source_dir,target_dir);
}
//_ultimate_Output_backup___________________________________________2018-04-06_/

/* info on compressing and uncompressing folders (ZIP)

https://stackoverflow.com/questions/118547/creating-a-zip-file-on-windows-xp-2003-in-c-c/121720#121720
https://stackoverflow.com/questions/17546016/how-can-you-zip-or-unzip-from-the-script-using-only-windows-built-in-capabiliti
https://stackoverflow.com/questions/17546016/how-can-you-zip-or-unzip-from-the-script-using-only-windows-built-in-capabiliti/26843122#26843122
https://stackoverflow.com/questions/16458730/powershell-move-files-to-zip-with-system-io-compression-filesystem

____________________________________________________________
VB:

'Get command-line arguments.
Set objArgs = WScript.Arguments
Set FS = CreateObject("Scripting.FileSystemObject")
InputFolder = FS.GetAbsolutePathName(objArgs(0))
ZipFile = FS.GetAbsolutePathName(objArgs(1))

'Create empty ZIP file.
CreateObject("Scripting.FileSystemObject").CreateTextFile(ZipFile, True).Write "PK" & Chr(5) & Chr(6) & String(18, vbNullChar)

Set objShell = CreateObject("Shell.Application")

Set source = objShell.NameSpace(InputFolder).Items

objShell.NameSpace(ZipFile).CopyHere(source)

'Required to let the zip command execute
'If this script randomly fails or the zip file is not complete,
'just increase to more than 2 seconds
wScript.Sleep 2000
________________________________________________
Powershell
########################################################
# out-zip.ps1
#
# Usage:
#    To zip up some files:
#       ls c:\source\*.txt | out-zip c:\target\archive.zip $_
#
#    To zip up a folder:
#       gi c:\source | out-zip c:\target\archive.zip $_
########################################################

$path = $args[0]
$files = $input

if (-not $path.EndsWith('.zip')) {$path += '.zip'}

if (-not (test-path $path)) {
  set-content $path ("PK" + [char]5 + [char]6 + ("$([char]0)" * 18))
}

$ZipFile = (new-object -com shell.application).NameSpace($path)
$files | foreach {$zipfile.CopyHere($_.fullname)}
_______________________________________________
Other powershell  (as of .net 4.5)

Add-Type -AssemblyName System.IO.Compression.FileSystem

Add-Type -A System.IO.Compression.FileSystem
[IO.Compression.ZipFile]::CreateFromDirectory('foo', 'foo.zip')
[IO.Compression.ZipFile]::ExtractToDirectory('foo.zip', 'bar')




*/
