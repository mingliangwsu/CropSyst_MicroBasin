#ifndef LARS_WG_convertorH
#define LARS_WG_convertorH

#include "UED/convert/text_dBase_Excel_with_TDF/text_dbase_excel_with_tdf_convertor.h"
#include "UED/library/locrec.h"
//______________________________________________________________________________
class LARS_WG_format_convertor
: public Text_dBase_Excel_with_TDF_convertor                                     //060616
{
 private:
   CORN::OS::File_name_concrete /*140918 CORN::Smart_file_name*/ st_filename;
   CORN::OS::File_name_concrete /*140918 CORN::Smart_file_name*/ sr_filename;
 private: // Import
   UED::Geolocation_record    *geoloc_record_import;  // Provided by UED file
   UED_variable_code          variable_codes[10];                                //080303
   Units_code                 units_codes[10];                                   //080303
   nat8                       element_column_count;                              //080303
 public: // constructor
   LARS_WG_format_convertor(int argc,const char *argv[]);
 public:
   virtual nat32 perform_import();
   virtual nat32 perform_export();
   inline virtual nat16 get_version()                                      const { return 0x0100; };
   inline virtual const char *get_application_name()                       const { return "LARS-WG import/export utility (Roger Nelson rnelson@wsu.edu)"; };
 private:
   bool export_ST_file(const char *filename_st,const char *filename_sr);
   bool import_ST_file();                                                        //080303
   bool import_SR_file();                                                        //080303
};
//______________________________________________________________________________

#endif

