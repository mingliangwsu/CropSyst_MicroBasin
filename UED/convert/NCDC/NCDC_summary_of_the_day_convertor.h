#ifndef NCDC_summary_of_the_day_convertorH
#define NCDC_summary_of_the_day_convertorH

#include "UED/convert/convertor.h"

class NCDC_summary_of_the_day_element_record;
//______________________________________________________________________________
class NCDC_summary_of_the_day_format_convertor
: public UED_Convertor
{
 public:
   NCDC_summary_of_the_day_format_convertor(int argc,const char *argv[]);
   virtual nat32 perform_import() ;
   virtual nat32 perform_export() ;
   inline virtual nat16 get_version()                                      const
      { return 0x0100; }
   inline virtual const char *get_application_name()                       const
      { return "NCDC summary of the day UED import utility (Roger Nelson rnelson@wsu.edu)"; }
 private:
   void import_record
      (NCDC_summary_of_the_day_element_record &element_record
      ,CORN::OS::Directory_name &ued_file_path);
};
//______________________________________________________________________________

#endif

