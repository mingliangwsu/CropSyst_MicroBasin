//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("example_prj.res");
USEFORM("example_frm.cpp", Form1);
USEUNIT("..\..\workbook_datasrc.cpp");
USEUNIT("..\Excel_OLE_late_workbook.cpp");
USELIB("..\..\..\BCB5\corn.lib");
USELIB("..\..\..\struct\BCB5\struct_static.lib");
USELIB("..\..\..\datetime\BCB5\datetime_static.lib");
USELIB("..\..\..\file_sys\BCB5\file_sys_static.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->CreateForm(__classid(TForm1), &Form1);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
