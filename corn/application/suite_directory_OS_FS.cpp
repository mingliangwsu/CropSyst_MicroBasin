#include "suite_directory_OS_FS.h"
#include "corn/OS/file_system_engine.h"
namespace CORN {
namespace OS_FS {
//______________________________________________________________________________

Suite_directory::Suite_directory
(const OS::Directory_name &directory_name
,const wchar_t *_prefered_documentation_dir_name
,const wchar_t *_prefered_manual_dir_name
,const wchar_t *_prefered_icons_dir_name)
: OS::File_system_logical::Directory(directory_name,false)
   // Suite directory is usually prexisting                                      //130116
, prefered_documentation_dir_name       (_prefered_documentation_dir_name)
, prefered_manual_dir_name              (_prefered_manual_dir_name)
, prefered_icons_dir_name               (_prefered_icons_dir_name)
, current_program(0)
, common_directory         (0)
, documentation_directory  (0)
, manual_directory        (0)
, icons_directory          (0)
, install_or_update_filename(0)                                                  //120112
{}
//_constructor_________________________________________________________________/
void Suite_directory::reset()                                          provision_ // provides because only modifies provided contributes;
{  if (documentation_directory)  delete documentation_directory;  documentation_directory = 0;
   if (manual_directory)         delete manual_directory;         manual_directory=0;
   if (icons_directory)          delete icons_directory;          icons_directory = 0;
   if (common_directory)         delete common_directory;         common_directory = 0;   //101114
   if (install_or_update_filename)delete install_or_update_filename; install_or_update_filename=0;      //120112
}
//_reset_subentries____________________________________________________________/
void Suite_directory::know_initiating_program(const char *initiating_program)
{  if (current_program) delete current_program;
   current_program = new CORN::OS::File_name_concrete(initiating_program);
}
//_know_initiating_program_____________________________________________________/
Documentation_directory    &Suite_directory
::documentation()                                                      provision_
{  if (!documentation_directory)
   {  OS::Directory_name_concrete dir(*this,prefered_documentation_dir_name);
      documentation_directory = new Documentation_directory(dir);
   }
   return *documentation_directory;
}
//_documentation_______________________________________________________________/
provide_directory_name_implementation(Suite_directory,common,common_directory,"common")
provide_directory_name_implementation(Suite_directory,manual,manual_directory,prefered_manual_dir_name)
provide_directory_name_implementation(Suite_directory,icons,icons_directory,prefered_icons_dir_name)
//______________________________________________________________________________
const OS::File_name &Suite_directory::install_or_update()             provision_
{  if (!install_or_update_filename)
   {  OS::Directory_name_concrete installation_dir(*this,"installation");
      install_or_update_filename = new OS::File_name_concrete(installation_dir
         ,L"install_or_update"
         #ifdef _Windows
         ,L"exe"
         #else
         ,L""
         #endif
         );
   }
   return *install_or_update_filename;
}
//_install_or_update________________________________________________2012-01-12_/
} } // namespace OS_FS CORN

