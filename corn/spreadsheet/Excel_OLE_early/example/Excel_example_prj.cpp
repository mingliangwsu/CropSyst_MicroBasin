//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Excel_example_prj.res");
USEFORM("Excel_example_frm.cpp", Form1);
USEUNIT("..\..\workbook_datasrc.cpp");
USEUNIT("..\Excel_OLE_early_workbook.cpp");
USELIB("..\..\..\BCB5\corn.lib");
USELIB("..\..\..\datetime\BCB5\datetime_static.lib");
USELIB("..\..\..\file_sys\BCB5\file_sys_static.lib");
USELIB("..\..\..\struct\BCB5\struct_static.lib");
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
