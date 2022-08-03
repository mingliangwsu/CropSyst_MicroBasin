#define UED_SIMPLE_USE_EXTERN_C
#include "UED/simple/DLL/UED_simple.h"
#include <fstream.h>
#include "corn/measure/units.h"
#include <stdlib.h>
#include "corn/datetime/date.h"
#include "UED/library/UED_types.h"
//______________________________________________________________________________
int common_main(int argc, char *argv[])
{

//  test command line
// C:\dev\UED\simple\DLL\example\BC5\season.ued  0x80210007

   char *UED_filename = argv[1];    // I.e. "C:\dev\UED\DLL\example\BCB5\test.ued"
   char *variable_code = argv[2];   // Variable code in hexidecimal I.e. 0x85000001 which is CropSyst precipitation.

   unsigned long test_handle = UED_simple_open(UED_filename);

   unsigned long copy_handle = UED_simple_open("C:\\dev\\UED\\simple\\DLL\\example\\BC5\\copy.ued");

   int created = UED_set_geolocation
   (copy_handle
   ,45.0    // _latitude_dec_deg
   ,-117.5  // _longitude_dec_deg
   ,500     // _elevation_m
   ,2.0     // _screening_height_m
   ,"Pullman");

   double earliest_date_time = UED_simple_get_earliest_date_time(test_handle);
   double latest_date_time = UED_simple_get_latest_date_time(test_handle);

   // Convert hexidecimal code to unsigned long
   unsigned long variable  = strtoul(variable_code, 0 ,16);

//float test_value=1;

   if (test_handle)
   {
      for (CORN::Date date(earliest_date_time); date.get() <= (signed long)latest_date_time; date.inc())
      {
         unsigned long units     =  0;
         unsigned long quality   = 0;
         unsigned long status    = 0;
         float value = UED_simple_get_for_date(test_handle, date.get_datetime64(), variable, units,quality,status);

         if (UED_is_valid(quality))
         {
            CORN::Units_clad smart_units(units);
            char units_description[100];
            char units_abbreviation[50];
            smart_units.compose_description(units_description, units_abbreviation);

//float value = test_value; test_value+=1;

            cout << date << " = " << value
            << " " << units_abbreviation
            << endl;


            quality   = 0;
            status    = 0;

            UED_simple_set_for_date(copy_handle,value, date.get_datetime64(), variable, units,quality);
         }
      }
      UED_simple_close(test_handle);
      UED_simple_close(copy_handle);
   }
   return 0;
}
//______________________________________________________________________________
