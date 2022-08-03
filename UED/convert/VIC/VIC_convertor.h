#ifndef VIC_convertorH
#define VIC_convertorH
//---------------------------------------------------------------------------
#include "UED/convert/convertor.h"
// Forward declarations
namespace UED
{  class Database_file_indexed;
}
namespace CORN
{  class Binary_file_fstream;
}
//______________________________________________________________________________
class VIC_convertor
: public UED::Convertor
{
public: // constructor
   VIC_convertor(int argc, const char *argv[]);
   virtual nat32 perform_import();
   virtual nat32 perform_export();
   inline virtual nat16 get_version()                                      const { return 0x0100; }
public:
   inline virtual const char *get_application_name()                       const { return "VIC import utility (Roger Nelson rnelson@wsu.edu)"; }
private:
   nat32 VIC_convertor::import_precip_tmax_tmin_wind(ifstream &infile);
   nat32 VIC_convertor::import_rad_relhumid_file(ifstream &infile);              //080303

   nat32 perform_import_binary();
   nat32 perform_import_text();

   bool read_VIC_forcing_file_line
      (CORN::Binary_file_fstream  &bin_file
      ,float32 &precip , CORN::Quality &precip_quality
      ,float32 &tmax   , CORN::Quality &tmax_quality
      ,float32 &tmin   , CORN::Quality &tmin_quality
      ,float32 &wind   , CORN::Quality &wind_quality);
};
//______________________________________________________________________________
#endif
