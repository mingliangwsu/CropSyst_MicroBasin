//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("..\..\..\form_update.cpp", form_install_update);
//---------------------------------------------------------------------------
bool reg_file_types_mode = false;
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
   try
   {
      if (ParamStr(1) == "reg_file_types")
         reg_file_types_mode = true;
       Application->Initialize();
       Application->CreateForm(__classid(Tform_install_update), &form_install_update);
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

