//---------------------------------------------------------------------------

#ifndef SWAT_convertorH
#define SWAT_convertorH
//---------------------------------------------------------------------------

#include <UED/convert/convertor.h>
#include <corn/format/binary/oldbinrec/oldbinrec_s.h>

class SWAT_convertor
: public UED_convertor
{
// SWAT Soil Water and Assessment Tool
//  http://www.brc.tamus.edu/swat/soft_model.html
private:
/*Check needed

private:
      Weather_validator    *weather_data_validator;
      UED_indexed_database *ued_file;  // The Current UED file for the monthly record being processed.
*/
public:

   SWAT_convertor(int argc, const char *argv[]);
   virtual inline uint32 perform_import() { return 0;/* Not yet implemented */ };
   virtual        uint32 perform_export();
   virtual inline uint16 get_version()                                const { return 0x0100; };
   virtual inline const char *get_application_name()                  const { return "SWAT (Soil Water and Assessment Tool) - UED import utility (Roger Nelson rnelson@wsu.edu)"; };
private:
};

//---------------------------------------------------------------------------



#endif
