#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

#include "crop/crop_param_v5.h"
//---------------------------------------------------------------------------
USEFORM("..\..\..\..\..\GUI\parameter\form_param_file_RS.cpp", parameter_file_form);
USEFORM("..\form_crop_editor.cpp", crop_editor_form);
//---------------------------------------------------------------------------
#include "corn/OS/file_system_engine.h"
#include "CropSyst/source/crop/crop_param_V5.h"
#include "form_crop_editor.h"
#include "CS_Suite/common_editor_main_inc.cpp"
DECLARE_EDITOR_DIRECTORY
//---------------------------------------------------------------------------

WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

   try
   {
      INSTANCIATE_EDITOR_DIRECTORIES                                             //110524
      #if (CS_VERSION==4)
      setup_simulation_paths(CS_VERSION_NUMBERS,LABEL_CS_suite /*"CropSyst crop editor"*/);
      #endif

       Application->Initialize();
       Application->MainFormOnTaskBar = true;
       Application->CreateForm(__classid(Tparameter_file_form), &parameter_file_form);
       Application->CreateForm(__classid(Tcrop_editor_form), &crop_editor_form);
       std::wstring ParamStr_wstring(ParamStr(1).c_str());                       //110524
       std::string  ParamStr_string;                                             //110524
       wstring_to_string(ParamStr_wstring,ParamStr_string);                      //110524
       CRP_filename parameter_file_name(ParamStr_string.c_str());                //110524
       CropSyst::Crop_parameters file_parameters;                                //110524
       if (ParamCount() == 2)  // Crop filename and model
       {  std::wstring ParamStr2_wstring(ParamStr(2).c_str());
         std::string ParamStr2_string;
         wstring_to_string(ParamStr2_wstring,ParamStr2_string);
          crop_editor_form->bind_to(&file_parameters,parameter_file_form,ParamStr2_string.c_str());
          BIND_EDITOR_FORM_AND_PARAMETERS_TO_PARAMETER_FILE_FORM
            (file_parameters,crop_editor_form,parameter_file_name,0)
       } else //;

      //110605 if (ParamCount() == 1)  // parameter filename
         BIND_FORM_TO_PARAMETERS(file_parameters,crop_editor_form,parameter_file_name,0);
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
