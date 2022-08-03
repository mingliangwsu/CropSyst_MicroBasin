#include "update_control_file_generator.h"
//---------------------------------------------------------------------------
int main(int argc, const char *argv[])
{
   Update_control_file_generator update_gen;
   return
   (update_gen.create
      (argv[1] // This is the fully qualified name of the update_control.inf file to create.
      ,argv[2] // This is the directory containing the files to be included in the installation.
      ,argv[3] // This is the directory on the users computer where the application is to be installed.
      ,argv[4] // This is the URL of the web site where the files will be found by the updater program.
      )
      > 0)
   ? 0 : 1;


};
//---------------------------------------------------------------------------
/* Example command line: options

c:\installation\CS_suite_4\distribution\cs_suite_4\update_control_CropSyst_complete.inf
c:\installation\CS_suite_4\distribution\cs_suite_4
{PF}\CS_suite_4
http://www.bsyse.wsu.edu/rnelson/CS_suite_4

*/
