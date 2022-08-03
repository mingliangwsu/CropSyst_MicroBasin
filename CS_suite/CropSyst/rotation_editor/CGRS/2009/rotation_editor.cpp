//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("..\form_sowing_event.cpp", sowing_event_form);
USEFORM("..\form_rotation_editor.cpp", rotation_editor_form);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
   try
   {
       Application->Initialize();
       Application->MainFormOnTaskBar = true;
       Application->CreateForm(__classid(Trotation_editor_form), &rotation_editor_form);
       Application->CreateForm(__classid(Tsowing_event_form), &sowing_event_form);
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
