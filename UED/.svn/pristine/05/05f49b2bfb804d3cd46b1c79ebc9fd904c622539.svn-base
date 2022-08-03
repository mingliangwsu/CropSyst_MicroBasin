#include "UED/convert/cropsyst/cropsyst_convertor.h"
#include "corn/OS/file_system_logical.h"
#include "corn/data_source/command_options_datasrc.h"
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
// Standalone (eventually being replaced by all_in_one
//______________________________________________________________________________
int main(int argc,const  char *argv[])
{  //170725 date_setup_phrases();


   CORN::Command_options_data_source command_line_options(argc,argv);            //170725
   UED::Convertor_arguments /*180101 CropSyst_text_convertor::Arguments*/ arguments;                                 //170725
   //conceptual if (argc == 1) arguments.write_help();
   bool processed = true;                                                        //170725
   processed &= command_line_options.get(arguments);                             //170725

   CropSyst_text_convertor  convertor(arguments); //170725 (argc,argv);
   int result =  convertor.convert();
   convertor.notify_climgen();
   return result;
};
//______________________________________________________________________________
