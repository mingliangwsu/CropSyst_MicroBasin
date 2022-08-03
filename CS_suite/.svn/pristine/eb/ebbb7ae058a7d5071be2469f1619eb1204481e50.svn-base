#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("..\form_event.cpp", event_editor_form);
USEFORM("..\form_operation_event.cpp", operation_event_form);
USEFORM("..\form_sync.cpp", sync_form);
USEFORM("..\form_clipping2.cpp", clipping_form);
USEFORM("..\..\..\..\..\GUI\parameter\form_param_file_RS.cpp", parameter_file_form);
USEFORM("..\form_auto_NO3_appl.cpp", form_auto_NO3_application);
USEFORM("..\form_organic_N_appl.cpp", organic_N_application_form);
USEFORM("..\form_manure_appl.cpp", manure_application_form);
USEFORM("..\form_irrig_appl.cpp", Irrigation_application_form);
USEFORM("..\form_auto_clipping.cpp", auto_clipping_form);
USEFORM("..\form_inorganic_N_appl.cpp", inorganic_N_application_form);
USEFORM("..\form_tillage_residue.cpp", tillage_residue_form);
USEFORM("..\form_management_editor.cpp", Management_editor_form);
//---------------------------------------------------------------------------
#include "CS_suite/common_editor_main_inc.cpp"
#include "form_management_editor.h"
#include "CropSyst/source/mgmt_param.h"
#include "CropSyst/source/mgmt_param.h"
#include "corn/string/strconv.hpp"
#  include "corn/application/program_directory_OS_FS.h"
//DECLARE_EDITOR_DIRECTORY
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
   try
   {
      INSTANCIATE_EDITOR_DIRECTORIES(ParamStr(0).c_str());
       Application->Initialize();
       Application->MainFormOnTaskBar = true;
       Application->CreateForm(__classid(Tparameter_file_form), &parameter_file_form);
       Application->CreateForm(__classid(Tevent_editor_form), &event_editor_form);
       Application->CreateForm(__classid(Tform_auto_NO3_application), &form_auto_NO3_application);
       Application->CreateForm(__classid(Toperation_event_form), &operation_event_form);
       Application->CreateForm(__classid(TManagement_editor_form), &Management_editor_form);
       Application->CreateForm(__classid(Ttillage_residue_form), &tillage_residue_form);
       Application->CreateForm(__classid(Torganic_N_application_form), &organic_N_application_form);
       Application->CreateForm(__classid(Tmanure_application_form), &manure_application_form);
       Application->CreateForm(__classid(Tinorganic_N_application_form), &inorganic_N_application_form);
       Application->CreateForm(__classid(TIrrigation_application_form), &Irrigation_application_form);
       Application->CreateForm(__classid(Tauto_clipping_form), &auto_clipping_form);
       Application->CreateForm(__classid(Tsync_form), &sync_form);
       Application->CreateForm(__classid(Tclipping_form), &clipping_form);
       std::wstring ParamStr_wstring(ParamStr(1).c_str());
       std::string  ParamStr_string;
       CORN::wstring_to_string(ParamStr_wstring,ParamStr_string);
       //170620 MGT_filename parameter_file_name(ParamStr_string.c_str());

      CORN::OS::File_name_concrete parameter_file_name(ParamStr(1).c_str());

      CropSyst::Management_parameters  mgmt_parameters;



      Bidirectional_list /*180101 Association_list*/ file_type_descriptions;
      file_type_descriptions.append(new File_type_description(CS_management_EXT         ,"CropSyst Management"              ,CS_management_wildcard));

      //170617 BIND_FORM_TO_PARAMETERS(mgmt_parameters,Management_editor_form,parameter_file_name)

      BIND_FORM_TO_PARAMETERS
         (mgmt_parameters,Management_editor_form
         ,parameter_file_name
         ,&file_type_descriptions);

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
