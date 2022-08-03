#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("..\..\frame_CS_context_functions.cpp", frame_CS_context); /* TFrame: File Type */
USEFORM("..\..\..\..\GUI\explorer\frame_navigation_JAM.cpp", navigation_frame); /* TFrame: File Type */
USEFORM("..\..\..\..\GUI\explorer\form_explorer_common.cpp", common_explorer_form);
USEFORM("..\..\..\..\GUI\explorer\frame_current_directory_common.cpp", navigation_current_frame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#include "../common_program_main_inc.cpp"
#include "../includes_frames_forms.cpp_incl"
#include "GUI/explorer/frame_navigation_JAM.h"
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
//______________________________________________________________________________
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
   try
   {
      INSTANCIATE_CS_SUITE_DIRECTORY(ParamStr(0).c_str())                        //150417_101021
       Application->Initialize();
       Application->MainFormOnTaskBar = true;
       Application->CreateForm(__classid(Tcommon_explorer_form), &common_explorer_form);
       #include "../main_instanciate_bind_frames.cpp_incl"
       Application->Run();
   }
   catch (Exception &exception)
   {  Application->ShowException(&exception);
   }
   catch (...)
   {  try
       { throw Exception("");
       }
       catch (Exception &exception)
       { Application->ShowException(&exception);
       }
   }
/*140424
disbled because something must not be deallocating correctly.
Whatever it is should be fixed but it is not critical to CS explorer at this point.

   delete CS::Suite_directory; CS::Suite_directory = 0; //must be nillified
*/
   return 0;
}
//---------------------------------------------------------------------------

