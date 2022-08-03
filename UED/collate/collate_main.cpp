//#include "corn/chronometry/date_time_64.h"


#include "collate_engine.h"
#include "corn/OS/file_system_logical.h"
#include "corn/data_source/command_options_datasrc.h"

using namespace UED;

namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}

//______________________________________________________________________________
int main(int argc, const char *argv[])
{
   CORN::Command_options_data_source command_line_options(argc,argv);
   Collate_engine::Arguments arguments;
   if (argc == 1) arguments.write_help();
   bool processed = true;
   processed &= command_line_options.get(arguments);                             //170328
   Collate_engine   collate(arguments);                                          //170328
   processed &= collate.process();
   return processed ? EXIT_SUCCESS : EXIT_FAILURE;
}
//______________________________________________________________________________

