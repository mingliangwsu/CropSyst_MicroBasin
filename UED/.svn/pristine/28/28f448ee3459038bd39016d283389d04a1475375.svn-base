#include <UED/library/database_file.h>
#include <corn/file_sys/smart_filename.h>
#include <fstream>
#include "C:/CS_Suite_4/UED/simple/DLL/UED_codes.h"
/*
   This command line mode program
   makes a copy of the first named UED file
   having the second filename.
   All free records (marked as free or deleted)
   are expunged from the copy.

   If only one UED filename is specified on the command line
   the new file will be given the same name prepended with "Copy of "
*/
//______________________________________________________________________________
uint32 UED_file_delete_elements
(const CORN::Smart_file_name &original_file_name
,const CORN::Smart_file_name &copy_file_name
,const nat32 element_variable_codes_to_delete[]
)
{
   UED::Database_file *original_file = new UED::Database_file(original_file_name.c_str(),true);           // open the original file readonly
      // Note that I am using new for original file because
      // I have giving the original records to the copy
      // but then both objects are pointing to the original records.
      // I should 'take' or copy the records from the original, but I don't
      // currently have a mechanism for that in UED::Database_file.
      // Hence this hack.
   UED::Database_file copy_file(copy_file_name.c_str(),false);                  // open the copy
   uint32 deleted_record_count = 0;
   while (UED::Record_base *original_rec = original_file->goto_next())
   {
      bool keep_record = true;
      Record_code original_rec_code = original_rec->get_code();
      if (original_rec_code == original_file->get_free_code(original_rec_code))
         keep_record = false;
      else
      {
         UED::Smart_record_code smart_original_rec_code(original_rec_code);
         if (smart_original_rec_code.has_variable_code())
         {
            if (  smart_original_rec_code.is_data_set()
                ||smart_original_rec_code.is_data_scalar()
                ||smart_original_rec_code.is_data_vector())
            {
               UED::Data_record_header *as_datarec = dynamic_cast<UED::Data_record_header *>(original_rec);
               if (as_datarec)
               {
                  UED::Variable_code varcode = as_datarec->get_variable_code();
                  int e;
                  int var_code_e;
                  for ( e = 0,  var_code_e = element_variable_codes_to_delete[e]
                      ;var_code_e
                      ;e++,  var_code_e = element_variable_codes_to_delete[e])
                  {
                     if (varcode == var_code_e)
                     {
                        keep_record = false;
                     };
                  };
               };
            };
         };
         // Warning UED::Database_file expects appended records to be relinquished
         // to it, so both databases will be pointing to the original record.
         // This should not be a problem as long as I don't delete original_file
         // (Using Database_file_indexed would likely be problemactic.
      };

      if (keep_record)
         copy_file.append_record(original_rec,true);
      else
         deleted_record_count++;
      // else we don't copy the record
   };
   return deleted_record_count;
};
//______________________________________________________________________________
int main(int argc, const char *argv[])
{  int result = EXIT_FAILURE;

   if (argc > 1)
   {  CORN::Smart_file_name original_file_name(argv[1]);
      CORN::Ustring copy_of_name("copy of ");
      copy_of_name.append(original_file_name.get_name(false));
      CORN::Smart_file_name copy_file_name(original_file_name);
      copy_file_name.set_name(copy_of_name);
      if (argc > 2)
      {
         copy_file_name.set(argv[2]);
      };
      UED::Variable_code elements_to_delete[] =
         {UED_STD_VC_Tdewmax,UED_STD_VC_Tdewmin,UED_STD_VC_Tdewavg
         ,UED_STD_VC_RHmax,UED_STD_VC_RHmin,UED_STD_VC_RHavg
         #if (CS_VERSION >= 5)
         ,UED_STD_VC_Srad_total
         ,UED_STD_VC_Srad_ERRONEOUS
         #else
         ,UED_STD_VC_Srad
         #endif
         ,0};

      std::cout << "Packing:" << original_file_name << " to " << copy_file_name << std::endl;
      result = UED_file_delete_elements
            (original_file_name,copy_file_name
            ,elements_to_delete) > 0
         ? EXIT_SUCCESS
         : EXIT_FAILURE;
   };
   return result;
};
//______________________________________________________________________________
