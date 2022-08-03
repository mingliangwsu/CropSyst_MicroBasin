#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

#include "CS_Suite/common_editor_main_inc.cpp"
#include "CropSyst/source/rot_param.h"
#include "../../form_rotation_editor.h"
//______________________________________________________________________________
USEFORM("..\..\form_rotation_editor.cpp", rotation_editor_form);
USEFORM("..\..\form_planting_event.cpp", planting_event_form);
USEFORM("..\..\..\..\..\..\GUI\parameter\form_param_file_RS.cpp", parameter_file_form);
USEFORM("..\..\..\..\..\..\components\RNAutoControls\corn\RNAutoCalendarForm.cpp", RNAutoCalendarForm);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
   try
   {
      INSTANCIATE_EDITOR_DIRECTORIES(ParamStr(0).c_str());                       //150519

       Application->Initialize();
       Application->MainFormOnTaskBar = true;
       Application->Title = "CropSyst rotation";
       Application->CreateForm(__classid(Tparameter_file_form), &parameter_file_form);
         // parameter_file_form MUST BE FIRST
       Application->CreateForm(__classid(Trotation_editor_form), &rotation_editor_form);
       Application->CreateForm(__classid(Tplanting_event_form), &planting_event_form);
       Application->CreateForm(__classid(TRNAutoCalendarForm), &RNAutoCalendarForm);
       CORN::OS::File_name_concrete    rotation_filename(ParamStr(1).c_str());
      CropSyst::Rotation_parameters   rotation_params;
      Bidirectional_list file_type_descriptions;

#  define CS_rotation_wildcard_V4      "*." CS_rotation_EXT_V4
      file_type_descriptions.append(new File_type_description
         (CS_rotation_EXT_V4         ,"CropSyst rotation" ,CS_rotation_wildcard_V4));

       BIND_FORM_TO_PARAMETERS(rotation_params,rotation_editor_form
         ,rotation_filename
         ,&file_type_descriptions)

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
//__tWinMain__________________________________________________________18-03-26_/
