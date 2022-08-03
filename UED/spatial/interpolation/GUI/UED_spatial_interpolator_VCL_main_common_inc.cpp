#ifdef USE_OS_FS
#include "corn/application/user/appdata_directory_OS_FS.h"
#else
#include "corn/application/user/appdata_directory.h"
#endif
#include "UED/spatial/interpolation/UED_database_interpolate_datarec.h"
#define HELP_UED_spatial_interpolator  "spatial\\interpolation\\manual\\UED_spatial_interpolator.htm"
#include "corn/data_source/vv_file.h"
//#include "corn/OS/file_system_logical.h"

#include "corn/string/strconv.hpp"
UED_database_interpolate_data_record  interp_options_record;

// This file should be included in WinMain
bool spatial_interpolator_setup()
{

      CORN_File_name_instance program_file_name(ParamStr(0).c_str());
      UED_spatial_interpolator_form->bind_to(&interp_options_record,parameter_file_form);
      int param_count = ParamCount();
      bool filename_specified_on_command_line =  param_count >= 1;
      std::string parameter_filename_raw("no_name");
      #ifdef UNICODE
      if (filename_specified_on_command_line)
         CORN::append_Unicodez_to_string(ParamStr(1).c_str(),parameter_filename_raw);
      #else
      parameter_filename_raw.assign(ParamStr(1).c_str());
      #endif

      #ifdef USE_OS_FS
      CORN::OS::File_name_logical parameter_filename(parameter_filename_raw.c_str());
      CORN::OS_FS::Application_data_directory *user_app_dir = new CORN::OS_FS::Application_data_directory(program_file_name);
      CORN::Association_list file_name_filters;
      file_name_filters.append(new CORN::OS::File_system_logical::File_type_description
         ("UED_response",interp_options_record.get_type_label()));
      //continue here need to come up with a scheme for file name filters
      #else
      Filtered_file_name parameter_filename
      (parameter_filename_raw.c_str()
      ,"UED_response"
      ,interp_options_record.get_type_label()
      ,"*.UED_response");
      CORN::Application_data_directory *user_app_dir = new CORN::Application_data_directory(program_file_name);
      #endif

      if (!filename_specified_on_command_line)
         Application->MessageBox
            (_TEXT("The next window will prompt for the name of a UED interpolator response file.\n"
             "It will be used to store interpolation options and selections.\n\n"
             "Typically this is a new file to be created now unless you want to load options from a previous session.\n"
             "You can put this temporary file in any folder but you may find it convenient to create this file in the folder where you store your UED files.\n"
             "To select a folder press the [Select] button, go to the desired folder, enter new name for the response file to create and press [open] button.")
            ,_TEXT("Response file explaination")
            ,ID_OK);

   return (parameter_file_form->bind_to
         (UED_spatial_interpolator_form
         ,&interp_options_record
         ,&parameter_filename // now prompts for recent file   ParamStr(1).c_str()
         #ifdef USE_OS_FS
         ,&file_name_filters
         #else
         ,parameter_filename.get_filters()
         #endif
         ,UED_spatial_interpolator_form->get_main_page_control()
         ,filename_specified_on_command_line
         ,user_app_dir
         ));

};
