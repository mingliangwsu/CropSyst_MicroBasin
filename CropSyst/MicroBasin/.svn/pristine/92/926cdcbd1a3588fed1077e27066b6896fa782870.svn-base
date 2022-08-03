#include "MicroBasin_engine.h"
//______________________________________________________________________________
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
//______________________________________________________________________________
int main(int argc, char *argv[])
{
   CORN::OS::Directory_name_concrete CWD;
   CropSyst::MicroBasin_Engine microbasin_engine(CWD);
   return microbasin_engine.run();
}
//______________________________________________________________________________
