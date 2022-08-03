#include "scenarios_scheduler_engine.h"
#include "corn/OS/file_system_logical.h"
#include "corn/data_source/command_options_datasrc.h"
//______________________________________________________________________________
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
//______________________________________________________________________________
int main(int argc, const char *argv[])
{

   CORN::Command_options_data_source command_line_options(argc,argv);
   CS::Scenarios_scheduler_engine::Arguments arguments;
   command_line_options.get(arguments);


   CS::Scenarios_scheduler_engine *engine
      = new CS::Scenarios_scheduler_engine(arguments);
/*
   command_line_options.get(engine->arguments.seclusion.arguments);
   if (!engine->arguments.seclusion.count())
      engine->arguments.seclusion.arguments.find_and_read_seclusion_files();
*/
   bool processed
      = engine->initialize()
      #ifdef PROCESS_PENULTIMATES
      &&engine->process_penultimates();
      #else
      &&engine->process_ultimates();
      #endif
   delete engine;
   return processed ? EXIT_SUCCESS : EXIT_FAILURE;
}
//_2016-10-01___________________________________________________________________
