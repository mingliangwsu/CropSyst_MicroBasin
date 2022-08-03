#include "soil_param_NET.h"

//#include <msclr\marshal_cppstd.h>

//using namespace msclr::interop;

using namespace System::Runtime::InteropServices; 


namespace CropSyst_parameters_NET
{
//______________________________________________________________________________
Soil_with_sublayering::Soil_with_sublayering(System::String ^soil_file_name)
: soil(0)
{
   soil = new CropSyst_parameters::Soil_with_sublayering();

   std::string filename_std_string;
   const char *soil_filename_cstr  = 0;
   #if (_MSC_VER > 1600)
   // The following is for VC2010
      filename_std_string = marshal_as<std::string>(soil_file_name);
      soil_filename_cstr = filename_std_string.c_str();
   #else
      soil_filename_cstr = (const char*) (Marshal::StringToHGlobalAnsi(soil_file_name)).ToPointer();
/*
   IntPtr p = Marshal::StringToHGlobalAnsi(soil_file_name); 
   char *pNewCharStr = static_cast<char*>(p.ToPointer()); 
   cout << pNewCharStr << endl; 
   Marshal::FreeHGlobal(p); 
*/
/*
   // The following is for VC2008
   using namespace Runtime::InteropServices;
   const char* filename_cstr =
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   filename_std_string = filename_cstr;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
*/
   #endif
   soil->read_file(soil_filename_cstr);
};
//______________________________________________________________________________
Soil_with_sublayering::~Soil_with_sublayering()
{
   if (soil) delete soil; soil = 0;
};
//______________________________________________________________________________
}; //namespace