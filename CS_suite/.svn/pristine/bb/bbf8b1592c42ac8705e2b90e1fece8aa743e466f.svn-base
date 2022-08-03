//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("CS_explorer.res");
USEFORM("..\..\..\GUI\explorer\form_explorer_common.cpp", common_explorer_form);
USEUNIT("..\CS_explorer_engine.cpp");
USEUNIT("..\..\..\cropsyst\cpp\cs_paths.cpp");
USEUNIT("..\..\..\cropsyst\cpp\cs_project_directory.cpp");
USEUNIT("..\..\..\cropsyst\cpp\database_dir.cpp");
USEUNIT("..\..\..\cropsyst\cpp\cs_scenario.cpp");
USEUNIT("..\..\..\cropsyst\cpp\model_options.cpp");
USEUNIT("..\..\..\ued\library\UED_fname.cpp");
USEUNIT("..\..\..\common\weather\weather_types.cpp");
USEUNIT("..\..\..\cropsyst\cpp\static_phrases.cpp");
USEUNIT("..\..\..\cropsyst\cpp\cs_operation_codes.cpp");
USEUNIT("..\..\..\CropSyst\cpp\output.cpp");
USEFORM("..\..\..\GUI\explorer\frame_navigation_ShellShock_BCB5.cpp", navigation_frame); /* TFrame: File Type */
USEUNIT("..\..\..\cropsyst\cpp\organic_matter\OM_types.cpp");
USEUNIT("..\..\..\corn\file_sys\smart_filename.cpp");
USEUNIT("..\..\..\cropsyst\cpp\organic_matter\OM_params.cpp");
USEUNIT("..\..\..\corn\OS\Windows\VCL\registry.cpp");
USELIB("C:\temp\lib\BCB5\release\application_static.lib");
USELIB("C:\temp\lib\BCB5\release\container_static.lib");
USELIB("C:\temp\lib\BCB5\release\corn_static.lib");
USELIB("C:\temp\lib\BCB5\release\CS_directory.lib");
USELIB("C:\temp\lib\BCB5\release\datetime_static.lib");
USELIB("C:\temp\lib\BCB5\release\file_sys_static.lib");
USELIB("C:\temp\lib\BCB5\release\format_static.lib");
USELIB("C:\temp\lib\BCB5\release\parameters_static.lib");
USELIB("C:\temp\lib\BCB5\release\common_sim_static.lib");
USEFORM("..\frame_CS_context_functions.cpp", frame_CS_context); /* TFrame: File Type */
USEUNIT("..\..\..\GUI\explorer\explorer_engine_abstract.cpp");
USEUNIT("..\..\..\GUI\explorer\navigation_responder.cpp");
USEUNIT("..\..\..\cropsyst\cpp\crop\growth_stages.cpp");
USEUNIT("..\..\..\common\biometeorology\ET_model.cpp");
USEUNIT("..\..\..\cropsyst\cpp\crop\crop_types.c");
USEFORM("..\..\..\GUI\explorer\frame_current_directory_common.cpp", navigation_current_frame); /* TFrame: File Type */
//---------------------------------------------------------------------------
bool LADSS_mode = false;
#include "../includes_frames_forms.cpp_incl"
#include "../common_program_main_inc.cpp"
#include "GUI/explorer/frame_navigation_ShellShock_BCB5.h"

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
      INSTANCIATE_CS_SUITE_DIRECTORY
       Application->Initialize();
       Application->CreateForm(__classid(Tcommon_explorer_form), &common_explorer_form);
       #include "../main_instanciate_bind_frames.cpp_incl"
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   delete CS::Suite_directory; //100616 CS_Suite_directory;
   return 0;
}
//---------------------------------------------------------------------------

