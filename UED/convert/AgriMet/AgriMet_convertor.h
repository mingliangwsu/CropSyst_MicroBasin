#ifndef AgriMet_convertorH
#define AgriMet_convertorH
//---------------------------------------------------------------------------
#include "UED/convert/convertor.h"
// Forward declarations
namespace UED
{
   class Database_file_indexed;
}
namespace CORN
{
   class Binary_file_fstream;
}
//---------------------------------------------------------------------------
class AgriMet_convertor
: public UED::Convertor
{
public: // constructor
   AgriMet_convertor(int argc, const char *argv[]);
   virtual uint32 perform_import();
   inline virtual nat32 perform_export()                                         { return 0; /*NYI */ }
   inline virtual nat16 get_version()                                      const { return 0x0100; }
public:
   inline virtual const char *get_application_name()                       const { return "AgriMet import utility (Roger Nelson rnelson@wsu.edu)"; }
   nat32 AgriMet_convertor::read(ifstream &datastream);
};
//_2011-06-11___________________________________________________________________
#endif
