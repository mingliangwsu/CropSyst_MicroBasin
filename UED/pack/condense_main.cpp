#include "corn/OS/directory_entry_name_concrete.h"
#include "UED/library/database_file.h"

#include "corn/OS/file_system_engine.h"
#include "corn/OS/file_system_logical.h"
//#include <UED/library/database_file.h>
//#include <corn/file_sys/smart_filename.h>
//#include <fstream>
//#include <corn/format/binary/binary_record.h>

/*
   This command line mode program
   makes a copy of the first named UED file
   having the second filename.
   All free records (marked as free or deleted)
   are expunged from the copy.

   If only one UED filename is specified on the command line
   the new file will be given the same name prepended with "Copy of "


*/
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
//______________________________________________________________________________
nat32 pack_UED_file
   (const CORN::OS::File_name &original_file_name
   ,const CORN::OS::File_name &copy_file_name_preferred)
{
   CORN::OS::File_name_concrete *temporary_file_name = 0;
   const CORN::OS::File_name *target_file_name = 0;
   if (copy_file_name_preferred.compare_including(original_file_name))
   {
      temporary_file_name
         = new CORN::OS::File_name_concrete(std::tmpnam(0));
      target_file_name = temporary_file_name;

   } else
      target_file_name = &copy_file_name_preferred;
   nat32 record_count = 0;
   {
   UED::Database_file *original_file = new UED::Database_file
      (original_file_name.c_str(),std::ios::in,true);
      // Note that I am using new for original file because
      // I have giving the original records to the copy
      // but then both objects are pointing to the original records.
      // I should 'take' or copy the records from the original, but I don't
      // currently have a mechanism for that in UED::Database_file.
      // Hence this hack.


   UED::Database_file copy_file(target_file_name->c_str(),std::ios::out,true);

   while (UED::Record_base *original_rec = original_file->goto_next())
   {
      Record_code original_rec_code = original_rec->get_code();
      if (original_rec_code != original_file->get_free_code(original_rec_code))
      {
         copy_file.append_record(original_rec,true);

         // Warning UED::Database_file expects appended records to be relinquished
         // to it, so both databases will be pointing to the original record.
         // This should not be a problem as long as I don't delete original_file
         // (Using Database_file_indexed would likely be problemactic.
         record_count++;
      }
      // else we don't copy the record
   }
   }
   if (temporary_file_name)
   {  //
      CORN::OS::file_system_engine.copy_file
         (*temporary_file_name,copy_file_name_preferred,false);
   }
   return record_count;
};
//______________________________________________________________________________

int main(int argc, const char *argv[])
{  int result = EXIT_FAILURE;

   if (argc > 1)
   {  CORN::OS::File_name_concrete original_file_name(argv[1]);
      // originally if no target filename was specified, the target filename
      // was named "copy of XXX";
//      std::string copy_of_name("copy of ");
//      CORN::append_wstring_to_string(original_file_name.get_name(),copy_of_name);
      CORN::OS::File_name_concrete copy_file_name(original_file_name);

      if (argc == 3)
      {
         copy_file_name.set_cstr(argv[2]);
      }
      std::cout << "Packing:" << original_file_name << " to " << copy_file_name << std::endl;
      result = pack_UED_file(original_file_name,copy_file_name) > 0
         ? EXIT_SUCCESS
         : EXIT_FAILURE;
   } else
   {
      /* NYI print usage
      arg 1 is the source (original) UED file to be condensed
      arg 2 is the target UED file (optional) is new UED file to be created
         if the target is omitted the original file is replaced

      */

   }
   return result;
};
//______________________________________________________________________________
