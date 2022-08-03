#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/OS/file_system_logical.h"
#include "corn/OS/file_system_engine.h"

namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
//______________________________________________________________________________
int main(int argc, char *argv[])
{
   //CORN::OS::File_system_engine FS_engine;
   CORN::Unidirectional_list file_name_list;
   CORN::Unidirectional_list directory_name_list;
   CORN::OS::Directory_name_concrete temp_dir
      #ifdef __unix__
      ("/tmp");
      #else
      ("C:\\temp");
      #endif

   nat32 den_count = CORN::OS::file_system_engine.list_entry_names
      (temp_dir
      //150909 ,true // recurse_subdirectories                                               //121231
      ,&file_name_list
      ,&directory_name_list
      ,CORN::OS::File_system::subdirectory_recursion_inclusive                   //150909
      ,CORN::OS::Directory_entry_name::full_qualification                        //150909
      );
      //,const wchar_t *name_wild_card      = 0
      //,const wchar_t *extension_filter    = 0
      //,const CORN::Text_list *exclude_directories = 0)                     const = 0; //130103

   FOR_EACH_IN(filename, CORN::OS::Directory_entry_name,file_name_list,each_filename)
   {
      std::cout << filename->c_str() << std::endl;
   } FOR_EACH_END(each_filename)
   FOR_EACH_IN(dirname, CORN::OS::Directory_entry_name,directory_name_list,each_dirname)
   {
      std::cout << dirname->c_str() << std::endl;
   } FOR_EACH_END(each_dirname)


};
//______________________________________________________________________________
