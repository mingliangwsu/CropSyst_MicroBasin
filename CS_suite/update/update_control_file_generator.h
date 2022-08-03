//---------------------------------------------------------------------------
#include <corn/primitive.h>
#ifndef update_control_file_generatorH
#define update_control_file_generatorH
//---------------------------------------------------------------------------

class Update_control_file_generator
{

public:
   uint32 create
      (const char *control_file_name_cstr          // This is the fully qualified name of the update_control.inf file to create.
      ,const char *app_distribution_directory_cstr // This is the directory containing the files to be included in the installation.
      ,const char *app_installation_directory_cstr // This is the directory on the users computer where the application is to be installed.
      ,const char *app_URL_directory_cstr          // This is the URL of the web site where the files will be found by the updater program.
      );


};
#endif
