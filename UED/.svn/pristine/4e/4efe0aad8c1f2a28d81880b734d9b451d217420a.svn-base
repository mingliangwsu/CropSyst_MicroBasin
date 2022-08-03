#include "UED/convert/convert_response.h"
#include "import_export_engine.h"
#include "corn/OS/file_system_logical.h"
#include "corn/data_source/command_options_datasrc.h"
#include "UED/collate/collate_engine.h"
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
//______________________________________________________________________________
int main (int argc, const char *argv[])
{
   CORN::Command_options_data_source command_line_options(argc,argv);            //170616
   Collate_engine::Arguments arguments;                                          //170616
   UED::Convertor_arguments/*171120 Convert_response_data_record*/ parameters;
   command_line_options.get(parameters);                                         //170616
   bool geolocation_encountered_not_used=false;
   //170616  parameters.read_from_command_line(argc,argv,geolocation_encountered_not_used);
   return UED::Quality_import_export_engine(parameters).process();
}
//_2014-06-14___________________________________________________________________