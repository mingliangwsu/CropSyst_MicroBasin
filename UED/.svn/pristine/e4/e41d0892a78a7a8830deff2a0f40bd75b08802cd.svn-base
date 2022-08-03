#include "UED/convert/text_dBase_Excel_with_TDF/text_dbase_excel_with_tdf_convertor.h"
#include "corn/tabular/delineated_datarec.h"
#include "common/weather/gen_dat_filename.h"
#include "common/weather/storm_event.h"
#include <sstream>
#include "corn/OS/file_system_logical.h"
#include "corn/data_source/command_options_datasrc.h"
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
//______________________________________________________________________________
int main(int argc, const char *argv[])
{
   CORN::Command_options_data_source command_line_options(argc,argv);
   Convertor_arguments arguments;                                                //171120
   bool processed = true;
   processed &= command_line_options.get(arguments);
   Text_dBase_Excel_with_TDF_convertor convertor(arguments);
   return convertor.convert();
}
//______________________________________________________________________________

