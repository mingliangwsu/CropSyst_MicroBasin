#include "CS_suite/common_program_main_inc.cpp"
#include "corn/application/user/appdata_directory_OS_FS.h"
#include "corn/OS/directory_entry_name_concrete.h"
#if (__BCPLUSPLUS__ >= 0x0610)
// RadStudio 2009 or greater with RNAutoControls
#  include "GUI/parameter/form_param_file_RS.h"
#else
// BCB5 with AutoControls
#  include "GUI/parameter/form_param_file.h"
#endif

// ______________________________________________________________________________
/*141119
#define DECLARE_EDITOR_DIRECTORY                                               \
   CORN::OS_FS::Program_directory *editor_directory  = 0;  //131202
*/
// ______________________________________________________________________________
#define INSTANCIATE_EDITOR_DIRECTORIES                                         \
   INSTANCIATE_CS_SUITE_DIRECTORY
/*141119
   editor_directory = new CORN::OS_FS::Program_directory(program_file_name);  //131202
*/
// ______________________________________________________________________________
#define BIND_PARAMETERS_TO_EDITOR_FORM(file_parameters,editor_form)            \
   editor_form->bind_to(&file_parameters,parameter_file_form);                 
//______________________________________________________________________________
#define BIND_EDITOR_FORM_AND_PARAMETERS_TO_PARAMETER_FILE_FORM(file_parameters,editor_form,parameter_file_name,filename_filters) \
   parameter_file_name.qualify();                                              \
   bool filename_specified_on_command_line =  (ParamCount() >= 1)              \
      || CORN::OS::file_system_engine.exists(parameter_file_name);             \
   Application_data_directory user_app_dir(program_file_name);                 \
   parameter_file_form->know_program_directory(program_directory);             \
   /* NYI    parameter_file_form->know_application_directory(CS::Suite_directory->CropSyst());   */ \
   parameter_file_form->know_suite_directory(CS::Suite_directory);             \
   parameter_file_form->bind_to                                                \
       (editor_form                                                            \
       ,&file_parameters                                                       \
       ,&parameter_file_name                                                   \
       ,filename_filters                                                       \
       ,editor_form->get_main_page_control()                                   \
       ,filename_specified_on_command_line                                     \
       ,&user_app_dir                                                          \
       ,"en");                                                                 \
   parameter_file_form->know_directory_context_explorer_program                \
         (CS::Suite_directory->CS_explorer_executable());                      \
   parameter_file_form->restore_active_control();
// ______________________________________________________________________________
#define BIND_EDITOR_FORM_DIRECTORY_AND_PARAMETERS_TO_PARAMETER_FILE_FORM(file_parameters,parameters_directory,editor_form)                          \
   parameter_file_form->set_Web_documentation_URL                              \
         (CS_SUITE_4_Web_root_dir,CS::Suite_directory->c_str());               \
   Application_data_directory user_app_dir(program_file_name);                 \
   parameter_file_form->know_program_directory(program_directory);             \
   /* NYI parameter_file_form->know_application_directory(CS::Suite_directory->CropSyst());  */  \
   parameter_file_form->know_suite_directory(CS::Suite_directory);             \
   parameter_file_form->bind_to_parameters_directory                           \
       (editor_form                                                            \
       ,&file_parameters                                                       \
       ,parameters_directory                                                   \
       ,0                                                                      \
       ,editor_form->get_main_page_control()                                   \
       ,false                                                                  \
       ,&user_app_dir                                                          \
       ,"en");                                                                 \
   parameter_file_form->know_directory_context_explorer_program                \
         (CS::Suite_directory->CS_explorer_executable());                      \
   parameter_file_form->restore_active_control();
// ______________________________________________________________________________
#define BIND_FORM_TO_PARAMETERS(file_parameters,editor_form,parameter_file_name,filename_filters)               \
        BIND_EDITOR_FORM_AND_PARAMETERS_TO_PARAMETER_FILE_FORM(file_parameters,editor_form,parameter_file_name,filename_filters)\
        BIND_PARAMETERS_TO_EDITOR_FORM(file_parameters,editor_form)
// ______________________________________________________________________________
#define BIND_FORM_TO_PARAMETERS_AND_DIRECTORY(file_parameters,parameters_directory,editor_form)               \
        /*BIND_PARAMETERS_TO_EDITOR_FORM(file_parameters,editor_form)  */                          \
        BIND_EDITOR_FORM_DIRECTORY_AND_PARAMETERS_TO_PARAMETER_FILE_FORM(file_parameters,parameters_directory,editor_form)
// ______________________________________________________________________________


