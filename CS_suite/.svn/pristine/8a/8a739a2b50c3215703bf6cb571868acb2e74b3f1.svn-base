//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "form_soil_convertor.h"
USEFORM("form_soil_convertor.cpp", soil_convertor_form);
//---------------------------------------------------------------------------
#include "corn/OS/file_system_logical.h"
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; };            //130224
}};
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{  try
   {

       Application->Initialize();
// optional ArgV[1]  the name of the default target directory to store imported
// soil parameter files

       Application->CreateForm(__classid(Tsoil_convertor_form), &soil_convertor_form);
       if (ParamCount() >= 1)
          soil_convertor_form->set_destination_dir(  ParamStr(1).c_str());
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
