//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("..\..\form_soil_editor.cpp", soil_editor_form);
USEFORM("..\..\..\..\..\..\GUI\parameter\form_param_file_RS.cpp", parameter_file_form);
//---------------------------------------------------------------------------
#include "RNAutoCheckBox.h"
//______________________________________________________________________________
//#include "CropSyst/source/soil/soil_param_V5.h"
#include "CropSyst/source/soil/soil_param.h"
#include "form_soil_editor.h"
#include "CS_Suite/common_editor_main_inc.cpp"
//DECLARE_EDITOR_DIRECTORY
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

   try
   {

   CORN::OS::File_name_concrete program_file_name(ParamStr(0).w_str());
   CORN::OS::Directory_name_concrete this_program_path(program_file_name,CORN::OS::Directory_entry_name::include_path_designated);

   CS::Suite_directory = new CS::Suite_Directory(this_program_path);

       Application->Initialize();
       Application->MainFormOnTaskBar = true;
       Application->CreateForm(__classid(Tparameter_file_form), &parameter_file_form);
       Application->CreateForm(__classid(Tsoil_editor_form), &soil_editor_form);
       std::wstring ParamStr_wstring(ParamStr(1).c_str());
       std::string  ParamStr_string;
       wstring_to_string(ParamStr_wstring,ParamStr_string);
       SIL_filename parameter_file_name(ParamStr_string.c_str());
       Smart_soil_parameters  soil_parameters;

      Bidirectional_list /*180101 Association_list*/ file_type_descriptions;
      file_type_descriptions.append(new File_type_description
         (CS_soil_EXT,"CropSyst Soil",CS_soil_wildcard));
       BIND_FORM_TO_PARAMETERS
         (soil_parameters,soil_editor_form
         ,parameter_file_name,&file_type_descriptions)
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   catch (...)
   {
       try
       {
          throw Exception("");
       }
       catch (Exception &exception)
       {
          Application->ShowException(&exception);
       }
   }
   return 0;
}
//---------------------------------------------------------------------------
