#include "UED/convert/IBSNAT_ICASA_DSSAT/DSSAT_ICASA_convertor.h"
#include "corn/data_source/command_options_datasrc.h"
#include "corn/OS/file_system_logical.h"
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}

//______________________________________________________________________________
int main(int argc, const char *argv[])
{
   bool processed = true;
   CORN::Command_options_data_source command_line_options(argc,argv);
   UED::Convertor_arguments arguments;
   processed &= command_line_options.get(arguments);

   //180308 DSSAT_ICASA_Convertor convertor(argc,argv);
   DSSAT_ICASA_Convertor convertor(arguments);
   int result =  convertor.convert();
   //180309 convertor.notify_climgen();
   //180309 return result;
   return processed ? EXIT_SUCCESS : EXIT_FAILURE;
}
//_main__________________________________________________________________180308_/
/*
WEATHER:KSAS  Kansas - for illustration purposes

*GENERAL
@ NAME
  Example weather dataset
@ PEOPLE
  Wagger,M.G. Agronomy,Kansas State Univ,Manhattan,Kansas
  Kissel,D. Agronomy,Kansas State Univ,Manhattan,Kansas
  Hunt,L.A. Plant Ag.,Univ.Guelph,Guelph,Ontario Thunt@Plant.Uoguelph.Ca
@ VERSION
  31-08-99(LAH,Guelph);26-08-99(LAH,Guelph);30-07-99(LAH,Guelph)

! The above are recommended as a minimum. Additional data items, as illustrated
! below, can be added for comprehensive documentation.


@ SOURCES
  IBSNAT DSSAT 3.0
@ MEASUREMENTS
  Temperature,solar radiation and precipitation
@ METHODS
  Standard Met Station instruments
@ PROBLEMS
  No formal check therefore unknown
@ NOTES
  Wind and dewpoint included; wind in m/s as average over 24h
@ QUALITY
  No missing values; wind is unusually high
@ PUBLICATIONS
  None of direct application
@ DISTRIBUTION
  Public

! One or more data groups similar to the following are necessary in all files.
! All clusters except the one beginning with WBYR are also necessary.


*WEATHER:KSAS  Ashland,Kansas

@ SITE
  Ashland,Kansas fictitious weather station
@ INSI  WTHLAT  WTHLONG  WELEV   TAV  TAMP  TEMHT  WNDHT
  KSAS   37.11   -90.45     81   8.5  18.9    2.0    2.0
@ WBYR   WBDAY     WTYR  WTDAY
  1980       1     1980      2
@ WEYR   WEDAY     SRAD   TMAX  TMIN  RAIN
  1980       1     11.5    1.4  -1.4   3.5
  1980       2     11.4    0.0  -2.1   2.5

! Additional data items can be added to clusters as illustrated below:

@ WEYR  WEDAY  SRAD  TMAX  TMIN  RAIN  WIND  TDEW
  1980      1  11.5   1.4  -1.4   3.5   4.2   0.6
  1980      2  11.4   0.0  -2.1   2.5   5.4   0.5

=

*/
//______________________________________________________________________________

