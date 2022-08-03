//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("..\..\..\GUI\explorer\frame_navigation_JAM.cpp", navigation_frame); /* TFrame: File Type */
USEFORM("..\..\..\GUI\explorer\form_explorer_common.cpp", common_explorer_form);
USEFORM("..\frame_CS_context_functions.cpp", frame_CS_context); /* TFrame: File Type */
//---------------------------------------------------------------------------
#  include <CS_suite/application/CS_suite_directory.h>
CS::Suite_Directory *CS::Suite_directory = 0;
#include "../includes_frames_forms.cpp_incl"
#include "../common_program_main_inc.cpp"
//#undef NO_WIN32_LEAN_AND_MEAN
#define Shortint unsigned char
#include <GUI/explorer/frame_navigation_JAM.h>
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   //101021 #include "../../main_instanciate_CS_suite_directory.cpp_incl"
   INSTANCIATE_CS_SUITE_DIRECTORY

/*100628
   CS::Suite_directory = new CS::Suite_Directory(this_program_path);
   CORN::Smart_file_name this_program_filename(ParamStr(0).c_str());
   CORN::Smart_directory_name this_program_path;
   this_program_filename.get_path(this_program_path);
*/

   try
   {
/*100630 moved to  main_instanciate_bind_frames.cpp_incl
       Application->Initialize();
       Application->HelpFile = "C:\\CS_Suite_4\\CS_explorer\\help.htm";
       Application->Title = "CS_explorer";
*/
       Application->CreateForm(__classid(Tcommon_explorer_form), &common_explorer_form);
       #include "../main_instanciate_bind_frames.cpp_incl"

       Application->Run();
   }
   #if (__BCPLUSPLUS__ >= 0x0600)
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   #endif
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
   delete CS::Suite_directory; //100616 CS_Suite_directory;

   return 0;
}
//---------------------------------------------------------------------------
