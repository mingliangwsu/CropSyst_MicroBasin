#include <vcl.h>
#pragma hdrstop
USERES("crop_editor.res");
USEFORM("..\crop_editor_frm.cpp", Crop_editor_form);
USEUNIT("..\..\..\..\..\Common\soil\SCS\SCS.CPP");
USERC("..\..\..\..\..\components\AutoControls\resources\buttons.rc");
USEUNIT("..\..\..\..\..\Common\residue\residue_decomposition_param.cpp");
USEFORM("..\..\..\..\..\GUI\parameter\form_param_file.cpp", parameter_file_form);
USEUNIT("..\..\..\..\..\GUI\recent\recent.cpp");
USEUNIT("..\..\..\..\..\common\residue\residue_const.cpp");
USEUNIT("..\..\..\CropSyst_directory.cpp");
USELIB("C:\Program Files\Borland\CBuilder5\Lib\wininet.lib");
USELIB("C:\temp\lib\BCB5\release\common_sim_static.lib");
USEUNIT("..\..\..\..\..\GUI\translator\translator_windows.cpp");
USEUNIT("..\..\..\..\..\GUI\parameter\form_param_file_common.cpp");
USEUNIT("..\..\form_crop_editor_common_VCL.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\crop\crop_param_class.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\crop\crop_param_struct.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\crop\crop_param_V4.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\static_phrases.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\database_dir.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\crop\crop_types.cpp");
USELIB("C:\temp\lib\BCB5\release\corn_complete_static.lib");
USEUNIT("..\..\..\..\..\CropSyst\source\crop\growth_stages.cpp");
USEUNIT("..\..\..\..\..\corn\application\program_directory_OS_FS.cpp");
USEUNIT("..\..\..\..\..\corn\application\adjunct_directory_OS_FS.cpp");
USEUNIT("..\..\..\..\..\corn\OS\directory_entry_name_concrete.cpp");
USEUNIT("..\..\..\..\..\corn\OS\directory_entry_name_abstract.cpp");
USEUNIT("..\..\..\..\..\corn\OS\file_system_types.cpp");
USEUNIT("..\..\..\..\..\corn\OS\file_system_logical.cpp");
USEUNIT("..\..\..\..\..\corn\application\suite_directory_OS_FS.cpp");
USEUNIT("..\..\..\..\..\corn\application\documentor.cpp");
USEUNIT("..\..\..\..\..\corn\OS\Uniform_resource_identifier.cpp");
USEUNIT("..\..\..\..\..\corn\OS\uniform_resource_locator.cpp");
USEUNIT("..\..\..\..\..\components\AutoControls\AutoFloat32EditBar.cpp");
USEUNIT("..\..\..\..\..\corn\container\container.cpp");
USEUNIT("..\..\..\..\..\corn\container\unilist.cpp");
USEUNIT("..\..\..\..\..\corn\container\association.cpp");
USEUNIT("..\..\..\..\..\corn\container\bilist.cpp");
USEUNIT("..\..\..\..\CS_application_directory.cpp");
USEUNIT("..\..\..\..\..\corn\application\application_directory_OS_FS.cpp");
USEUNIT("..\..\..\..\CANMS\CANMS_directory.cpp");
USEUNIT("..\..\..\..\ClimGen\ClimGen_directory.cpp");
USE("..\..\..\..\build\BCB5\CS_directory.bpf", BPF);
USEUNIT("..\..\..\..\CS_suite_directory.cpp");
USEUNIT("..\..\..\..\UED\UED_directory.cpp");
USEUNIT("..\..\..\..\..\corn\application\translations.cpp");
USEUNIT("..\..\..\..\..\corn\data_source\datarec.cpp");
//---------------------------------------------------------------------------
#include "GUI/parameter/form_param_file.h"
#include "CropSyst/source/options.h"
#include "crop_editor_frm.h"
#include "CropSyst/source/crop/crop_param.h"
#include "CropSyst/GUI/help/crop.h"
#include "corn/application/documentor.h"
//---------------------------------------------------------------------------
#include "CS_Suite/common_editor_main_inc.cpp"

namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}

// Command line options example for
// Fruit crop:   C:\Simulation\Projects\YakimaGrapes\Database\Crop\concord.crp
// CropGro crop: "c:\temp\test.crp" cropgro

// 141119 DECLARE_EDITOR_DIRECTORY

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
      INSTANCIATE_EDITOR_DIRECTORIES(ParamStr(0).c_str());                       //150519
         // This is only to get the master simulation folder stored by CS_suite
      Application->Initialize();
       Application->CreateForm(__classid(Tparameter_file_form), &parameter_file_form);
       Application->CreateForm(__classid(TCrop_editor_form), &Crop_editor_form);
       CropSyst::Crop_parameters *file_parameters_pointer = new CropSyst::Crop_parameters;
       CropSyst::Crop_parameters &file_parameters = *file_parameters_pointer;

      file_parameters.parameter_editor_mode = true;

      CORN::OS::File_name_concrete parameter_file_name(ParamStr(1).c_str());

      Association_list file_type_descriptions;
      file_type_descriptions.append(new File_type_description(CS_crop_EXT         ,"CropSyst Crop"              ,CS_crop_wildcard));
      if (ParamCount() == 2)  // Crop filename and model
      {
         Crop_editor_form->bind_to(&file_parameters,parameter_file_form,ParamStr(2).c_str());
         BIND_EDITOR_FORM_AND_PARAMETERS_TO_PARAMETER_FILE_FORM
         (file_parameters,Crop_editor_form
         ,parameter_file_name
         ,&file_type_descriptions); //130318
      }
      if (ParamCount() == 1)  // parameter filename
         BIND_FORM_TO_PARAMETERS
         (file_parameters,Crop_editor_form
         ,parameter_file_name
         ,&file_type_descriptions); //130318

//debug CORN::documentor.view_context_sensitive_help("growth.htm");

      Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
char *CORN_float32_to_str(float32 value, int decimals)
{  return CORN::float32_to_cstr( value,  decimals);
}
//______________________________________________________________________________
