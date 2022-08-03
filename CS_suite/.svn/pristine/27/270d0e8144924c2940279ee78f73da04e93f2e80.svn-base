//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#pragma link "gdiplus.lib"
USERES("soil_editor.res");
USEFORM("..\form_soil_editor.cpp", soil_editor_form);
USEUNIT("..\..\..\..\..\common\soil\hydrology\pedotransfer_saxton_1986.cpp");
USEUNIT("..\..\..\..\..\Common\soil\SCS\SCS.CPP");
USERC("..\..\..\..\..\components\AutoControls\resources\buttons.rc");
USEUNIT("..\..\..\..\..\Common\soil\texture.cpp");
USEUNIT("..\..\..\..\..\common\soil\layering.cpp");
USEUNIT("..\..\..\..\..\GUI\recent\recent.cpp");
USEUNIT("..\..\..\..\..\common\soil\hydrology\pedotransfer_interface.cpp");
USEUNIT("..\..\..\..\..\common\soil\hydrology\pedotransfer_abstract.cpp");
USEUNIT("..\..\..\..\..\common\soil\hydrology\pedotransfer_saxton_2006.cpp");
USEUNIT("..\..\..\..\..\common\soil\txtrhydr.cpp");
USEFORM("..\form_triangle_selector.cpp", form_texture_selector);
USEFORM("..\..\..\..\..\GUI\parameter\form_param_file.cpp", parameter_file_form);
USEUNIT("..\..\..\..\..\GUI\parameter\form_param_file_common.cpp");
USELIB("C:\temp\lib\BCB5\release\corn_complete_static.lib");
USELIB("C:\temp\lib\BCB5\release\CS_directory.lib");
USELIB("C:\Program Files\Borland\CBuilder5\Lib\wininet.lib");
USEUNIT("..\..\..\..\..\GUI\translator\translator_windows.cpp");
USEFORM("..\form_soil_texture.cpp", soil_texture_form);
USEUNIT("..\..\..\..\..\CropSyst\source\soil\soil_param.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\soil\soil_param_V4.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\soil\soil_param_class.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\static_phrases.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\cs_project.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\cs_project_directory.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\cs_scenario_directory.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\database_dir.cpp");
USEUNIT("..\..\..\..\..\CropSyst\source\project\CS_project_editor_params.cpp");
USEFORM("..\..\..\convert\soil\VCL\soil_water_characteristics_form.cpp", form_soil_water_characteristics);
USEUNIT("..\..\form_soil_editor_common_VCL.cpp");
USEUNIT("..\..\..\..\..\USDA\NRCS\soil\survey\domains.cpp");
USEUNIT("..\..\..\..\..\corn\application\program_directory.cpp");
USEUNIT("..\..\..\..\..\corn\file_sys\dir_ent.cpp");
USEUNIT("..\..\..\..\..\corn\file_sys\filtered_filename.cpp");
USEUNIT("..\..\..\..\..\common\parameter.cpp");
//---------------------------------------------------------------------------
#include "CropSyst/source/soil/soil_param.h"
#include "form_soil_editor.h"
#include "../../help/soil.h"

#include "CS_Suite/common_editor_main_inc.cpp"

//______________________________________________________________________________
DECLARE_EDITOR_DIRECTORY
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
//      INSTANCIATE_EDITOR_DIRECTORIES

   CORN::Smart_file_name program_file_name(ParamStr(0).c_str());                     \
   CORN::program_directory = new CORN::Program_directory(program_file_name);               \
      CS::Suite_directory = new CS::Suite_Directory(program_file_name);

      Application->Initialize();
       Application->CreateForm(__classid(Tparameter_file_form), &parameter_file_form);
       Application->CreateForm(__classid(Tsoil_editor_form), &soil_editor_form);
       Application->CreateForm(__classid(Tform_texture_selector), &form_texture_selector);
       Application->CreateForm(__classid(Tsoil_texture_form), &soil_texture_form);
       Application->CreateForm(__classid(Tform_soil_water_characteristics), &form_soil_water_characteristics);
       SIL_filename parameter_file_name(ParamStr(1).c_str());

continue here replace Smart_soil_parameters with new soil property providers

      Smart_soil_parameters  soil_parameters;
      BIND_FORM_TO_PARAMETERS(soil_parameters,soil_editor_form,parameter_file_name
        ,&parameter_file_name.get_file_type_descriptions())
      Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------

