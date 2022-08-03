//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("UED_components_package.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("AutoProfilePlotter.cpp");
USEUNIT("AutoGraphPlotter.cpp");
USEUNIT("AutoTimeSeriesPlotter.cpp");
USELIB("..\..\corn\datetime\BCB5\datetime_static.lib");
USELIB("..\..\corn\file_sys\BCB5\file_sys_static.lib");
USEUNIT("..\..\corn\image\clrramp.cpp");
USEPACKAGE("Vclx50.bpi");
USELIB("..\..\corn\BCB5\corn_static.lib");
USELIB("..\..\corn\container\BCB5\container_static.lib");
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
