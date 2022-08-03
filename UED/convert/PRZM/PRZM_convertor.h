#ifndef PRZM_convertorH
#define PRZM_convertorH
#include <UED/convert/convertor.h>
//______________________________________________________________________________
class PRZM_convertor
: public UED_convertor
{
public:
   PRZM_convertor(int argc,const char *argv[]);
   virtual uint32 perform_import() ;
   virtual uint32 perform_export() ;

   virtual uint16 get_version()           const { return 0x0100; };
   virtual const char *get_application_name()  const { return "PRZM UED import utility (Roger Nelson rnelson@wsu.edu)"; };

//private:
//   void import_record(NCDC_summary_of_the_day_element_record &element_record,Directory_name &ued_file_path);
}
//_2007-05-21___________________________________________________________________

#endif
