//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("UED_components_package.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("AutoProfilePlotter.cpp");
USEUNIT("AutoGraphPlotter.cpp");
USEUNIT("AutoTimeSeriesPlotter.cpp");
USEUNIT("..\..\corn\image\clrramp.cpp");
USEPACKAGE("Vclx50.bpi");
USELIB("C:\temp\lib\BCB5\release\corn_static.lib");
USELIB("C:\temp\lib\BCB5\release\container_static.lib");
USELIB("C:\temp\lib\BCB5\release\datetime_static.lib");
USELIB("C:\temp\lib\BCB5\release\file_sys_static.lib");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
   return 1;
}
//---------------------------------------------------------------------------
