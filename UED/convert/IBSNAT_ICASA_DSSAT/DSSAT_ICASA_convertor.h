#ifndef DSSAT_ICASA_convertorH
#define DSSAT_ICASA_convertorH
#include "UED/convert/convertor_weather.h"
#include "ICASA/library/weather/ICASA_weather.h"
using namespace ICASA;

//______________________________________________________________________________
class DSSAT_ICASA_Convertor
: public UED::Convertor_weather //180308 Convertor
{
   std::string site_code;
      // This is for lack of better name
 public:
   DSSAT_ICASA_Convertor
      (UED::Convertor_arguments &arguments);                                     //180308
   //180308      (int argc,const  char *argv[]);                                 //170328
   virtual uint32 perform_import();
   virtual uint32 perform_export();
   virtual uint16 get_version()                 const { return 0x0000; }
   virtual const char *get_application_name()   const { return "IBSNAT_ICASA_DSSAT_AgMIP UED import utility (Roger Nelson rnelson@wsu.edu)"; }
   inline virtual const char* get_daily_weather_target_file_extension()    const { return "wth"; }
 private:
   uint32 import_weather_unit(ICASA::Weather_unit &weather_unit);                //140627
   // returns the number of lines encountered in this unit.
};
//______________________________________________________________________________
#endif
