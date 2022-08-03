//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "form_soil_convertor_VCL_BCB5.h"
USERES("soil_convertor.res");
USEFORM("form_soil_convertor_VCL_BCB5.cpp", soil_convertor_form);
USEUNIT("..\..\..\..\..\..\Common\geolocation\geolocation.cpp");
USEUNIT("..\..\..\..\..\..\Common\soil\layering.cpp");
USEUNIT("..\..\..\..\..\..\Common\soil\SCS\SCS.cpp");
USELIB("..\..\..\..\..\..\ICASA\library\BCB5\ICASA_static.lib");
USEUNIT("..\..\..\..\..\..\cropsyst\cpp\static_phrases.cpp");
USELIB("..\..\..\..\..\..\STATSGO\library\BCB5\statsgo_static.lib");
USEUNIT("..\..\..\..\..\..\STATSGO\soil_generator\soil_generator.cpp");
USEUNIT("..\..\..\..\..\..\common\soil\texture.cpp");
USEUNIT("..\..\..\..\..\..\common\soil\texttri.cpp");
USEUNIT("..\..\..\..\..\..\common\soil\hydrology\pedotransfer_saxton_1986.cpp");
USEUNIT("..\..\..\..\..\..\common\soil\USDA_texture.cpp");
USEUNIT("..\..\..\..\..\..\common\geolocation\USA_state_FIPS_code.cpp");
USEUNIT("..\..\..\..\..\..\STATSGO\soil_convertor\STATSGO_soil_convertor.cpp");
USEUNIT("..\..\..\..\..\..\STATSGO\soil_processor\STATSGO_soil_processor.cpp");
USEUNIT("..\..\..\..\..\..\common\soil\txtrhydr.cpp");
USEUNIT("..\..\..\..\..\..\cropsyst\cpp\soil\soil_param_with_STATSGO.cpp");
USEUNIT("..\..\..\..\..\..\cropsyst\cpp\soil\soil_param_V4.cpp");
USEUNIT("..\..\..\..\..\..\cropsyst\cpp\soil\soil_param_class.cpp");
USEUNIT("..\..\..\..\..\..\cropsyst\cpp\soil\soil_param.cpp");
USEUNIT("..\..\..\..\..\..\cropsyst\cpp\soil\soil_param_struct.cpp");
USELIB("C:\temp\lib\BCB5\release\corn_complete_static.lib");
USELIB("C:\temp\lib\BCB5\release\format_static.lib");
USEUNIT("..\..\..\..\..\..\USDA\NRCS\soil\survey\domains.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {

       Application->Initialize();
       Application->CreateForm(__classid(Tsoil_convertor_form), &soil_convertor_form);
       if (ParamCount() >= 1)
          soil_convertor_form->set_destination_dir(  ParamStr(1).c_str());
// optional ArgV[1]  the name of the default target directory to store imported
// soil parameter files

       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
