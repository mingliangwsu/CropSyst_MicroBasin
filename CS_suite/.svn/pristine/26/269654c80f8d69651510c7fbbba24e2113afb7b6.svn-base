#include <vcl.h>
#pragma hdrstop
#include "CropSyst/source/mgmt_param.h"

USERES("biomatter_editor.res");
USEFORM("..\form_biomatter_editor.cpp", form_organic_matter_editor);
USEUNIT("..\..\..\..\..\common\residue\residue_const.cpp");
USEFORM("..\..\..\..\..\GUI\parameter\form_param_file.cpp", parameter_file_form);
USEFORM("..\..\..\..\..\GUI\recent\form_recent_file.cpp", recent_file_selector_form);
USEUNIT("..\..\..\..\..\common\biomatter\biomass_decomposition_param.cpp");
USEFORM("..\..\..\..\..\components\AutoControls\AutoFileEditBar.cpp", AutoFileEditBar); /* TFrame: File Type */
USEFORM("..\..\..\..\..\components\AutoControls\AutoFloat32EditBar.cpp", AutoFloat32EditBar); /* TFrame: File Type */
USEUNIT("..\..\..\..\..\GUI\parameter\form_param_file_common.cpp");
USEUNIT("..\..\..\..\..\GUI\translator\translator_windows.cpp");
USELIB("C:\temp\lib\BCB5\release\corn_complete_static.lib");
USELIB("C:\temp\lib\BCB5\release\CS_directory.lib");
USELIB("..\..\..\..\..\components\TMS_4.7\source_BCB5\wininet.lib");
USEUNIT("..\..\..\..\..\components\AutoControls\AutoStringEdit.cpp");
//---------------------------------------------------------------------------
#include "organic_matter_editor_frm.h"
#include <common/biomatter/biomass_decomposition_param.h>
#include "CS_Suite/common_editor_main_inc.cpp"
//150403 DECLARE_EDITOR_DIRECTORY
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
      INSTANCIATE_EDITOR_DIRECTORIES
       Application->Initialize();
       Application->CreateForm(__classid(Tparameter_file_form), &parameter_file_form);
       Application->CreateForm(__classid(Tform_organic_matter_editor), &form_organic_matter_editor);
       Application->CreateForm(__classid(Trecent_file_selector_form), &recent_file_selector_form);
       Biomass_decomposition_parameters bio_decomp_params(default_source);
       Biomass_decomposition_parameters_filename  organic_matter_filename(ParamStr(1).c_str());
       BIND_FORM_TO_PARAMETERS(bio_decomp_params,form_organic_matter_editor,organic_matter_filename)
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
