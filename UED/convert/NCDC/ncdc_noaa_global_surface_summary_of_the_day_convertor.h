#ifndef ncdc_noaa_global_surface_summary_of_the_day_convertorH
#define ncdc_noaa_global_surface_summary_of_the_day_convertorH

#include "UED/convert/convertor.h"

class NCDC_NOAA_global_surface_summary_of_the_day_format_V6;
class NCDC_NOAA_global_surface_summary_of_the_day_format_V7;
//______________________________________________________________________________
class NCDC_NOAA_global_surface_summary_of_the_day_convertor
: public UED_convertor
{
   bool  metric;  // True if metric units;
public:
   NCDC_NOAA_global_surface_summary_of_the_day_convertor(int argc,const char *argv[]);
   virtual nat32 perform_import() ;
   virtual nat32 perform_export() ;
   inline virtual nat16 get_version()                                      const
      { return 0x0100; };
   virtual const char *get_application_name()                              const
      { return "NCDC NOAA global surface summary of the day UED import utility (Roger Nelson rnelson@wsu.edu)"; };
private:
   void import_record_V6(NCDC_NOAA_global_surface_summary_of_the_day_format_V6 &element_record, CORN::OS::Directory_name &ued_file_path);
   void import_record_V7(NCDC_NOAA_global_surface_summary_of_the_day_format_V7 &element_record, CORN::OS::Directory_name &ued_file_path);
};
//______________________________________________________________________________

#endif

