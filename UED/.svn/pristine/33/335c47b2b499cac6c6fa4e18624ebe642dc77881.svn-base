//---------------------------------------------------------------------------

#pragma hdrstop

#include "AgWeatherNet_convertor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include <UED/library/UED.h>
#include <UED/library/database_file.h>
#include <UED/library/timeqry.h>
#include <UED/library/locrec.h>
#include <corn/string/uiostring.h>
#include <corn/measure/measures.h>
#include <corn/container/SDF_list.h>
#include <corn/container/Text_list.h>
#include <UED/convert/station_database.h>
#include "CS_suite/application/CS_suite_directory.h"
using namespace std;

/*  As of Sept 1, 2009
Daily Data Report.,,,,,,,,,,,,,,,,
Data Extracted: 2009-08-31.,,,,,,,,,,,,,,,,
Station: Paterson.,,,,,,,,,,,,,,,,
Lat: 45.9 Lng: 119.5 Elevation:   410.,,,,,,,,,,,,,,,,
Date Range from 1988-1-1 to 2009-8-31.,,,,,,,,,,,,,,,,

Note: Values = 99999 indicate sensor failure.,,,,,,,,,,,,,,,,

Station Unit ID  , Date    (yyyy-mm-dd), Julian Day  , Avg Air Temp ( C), Max Air Temp ( C), Min Air Temp ( C), Avg Dew point ( C), Avg RH  (%), Avg Wind Speed (m/s), Avg Wind Dir (Degree), Total Solar Rad (MJ/m 2 ), Total Precip  (mm), Avg Leaf Wet (Unity), Avg Soil Temp8 ( C), Min Battery  (Volt), ETr Alfalfa  (mm),.
62, 1990-05-11,131,9.341894737,21.93,0,-4.118165205,29.48515789,1.79382042,123.7105263,17.8971975,0,0,10.58010526,12,5.745817328,.
62, 1990-05-12,132,14.22494737,20.75,9.59,6.847198246,62.77578947,2.593658883,223.7547368,25.6782573,0,0,18.31442105,12,5.910113631,.


For metric the column headers are
Station Unit ID  	 Date    (yyyy-mm-dd)	 Julian Day  	 Avg Air Temp ( F)	 Max Air Temp ( F)	 Min Air Temp ( F)	 Avg Dew point ( F)	 Avg RH  (%)	 Avg Wind Speed (mph)	 Avg Wind Dir (Degree)	 Total Solar Rad (MJ/m 2 )	 Total Precip  (in)	 Avg Leaf Wet (Unity)	 Avg Soil Temp8 ( F)	 Min Battery  (Volt)	 ETr Alfalfa  (in)	.


This is another format done with SQL query
UNIT_ID,Date,JulDay,AIR_TEMP,MaxAirTemp,MinAirTemp,DEWPOINT,REL_HUMIDITY,WIND_SPEED,WIND_DIR,SOLAR_RAD,PRECIP,SOIL_TEMP_8_IN,SOIL_MOIS_8_IN,recordCount
109,1989-01-08,8,38.178687500,53.27600,32.00000,31.390681250,33.372083333,3.898932917,132.428125000,3.0665124,0.00000,39.823625000,99999.000000000,96


Note, there may be multiple stations in the file.
These station data sets are separated by two blank line
*/

// Problem solar radiation
struct Date_range_quality
{  CORN::Date32 start;
   CORN::Date32 end;
   CORN::Quality_code quality;
};
struct
{  const char *ID;
   const char *station;
   Date_range_quality quality_range;
} AgWeatherNet_solar_radiation_quality[] =
{{"100031","McNary",{2003060 /*   MAR  */,2005141 /*Late MAY*/ ,out_of_range_pot_low_error_quality}}

,{"100037","Coffin",{1995001 /*   JAN  */,1998365 /*   Dec  */ ,out_of_range_pot_low_error_quality}}
,{"100037","Coffin",{1999001 /*   JAN  */,1999264 /*Late SPT*/ ,out_of_range_pot_low_error_quality}}
,{"100037","Coffin",{2003001 /*   JAN  */,2005104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"100037","Coffin",{2008134 /* Mid MAY*/,2008219 /*Erly AUG*/ ,out_of_range_pot_low_error_quality}}

,{"100039","Triple-S",{2003060 /*   MAR  */,2003104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"100039","Triple-S",{2003165 /* mid JUN*/,2005134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}}
,{"100039","Triple-S",{2005202 /*Late JUL*/,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100039","Triple-S",{2006172 /*Late JUN*/,2006334 /*   NOV  */ ,out_of_range_pot_low_error_quality}}
,{"100039","Triple-S",{2007152 /*   JUN  */,2007304 /*   OCT  */ ,out_of_range_pot_low_error_quality}}

,{"100059","Carlson",{1989001 /*   JAN  */,2008366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}  // The entire solar radiation data is invalid

,{"100062","Paterson",{1991060 /*   MAR  */,1991195 /* mid JUL*/ ,out_of_range_pot_low_error_quality}}
,{"100062","Paterson",{1992001 /*   JAN  */,1992090 /*   MAR  */ ,out_of_range_pot_low_error_quality}}
,{"100062","Paterson",{1993080 /*Late MAR*/,1993127 /*Erly MAY*/ ,out_of_range_pot_low_error_quality}}
,{"100062","Paterson",{2001001 /*   JAN  */,2003365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100062","Paterson",{2004001 /*   JAN  */,2004080 /*Late MAR*/ ,out_of_range_pot_low_error_quality}}
,{"100062","Paterson",{2006233 /*Late AUG*/,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100062","Paterson",{2007001 /*   JAN  */,2007251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}

,{"100064","Station4",{2003001 /*   JAN  */,2003121 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"100064","Station4",{2004001 /*   JAN  */,2004121 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"100064","Station4",{2006001 /*   JAN  */,2006052 /*Late FEB*/ ,out_of_range_pot_low_error_quality}}
,{"100064","Station4",{2006060 /*   MAR  */,2006111 /*Late APR*/ ,out_of_range_pot_low_error_quality}}
,{"100064","Station4",{2006213 /*   AUG  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100064","Station4",{2007001 /*   JAN  */,2007251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}
,{"100064","Station4",{2007134 /* Mid MAY*/,2007334 /*   NOV  */ ,out_of_range_pot_low_error_quality}}

,{"100066","Station2",{1995001 /*   JAN  */,1995090 /*   MAR  */ ,out_of_range_pot_low_error_quality}}
,{"100066","Station2",{1998121 /*   MAY  */,1998181 /*   JUN  */ ,out_of_range_pot_low_error_quality}}
,{"100066","Station2",{2000165 /* mid JUN*/,2000243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}
,{"100066","Station2",{2007001 /*   JAN  */,2007104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}


,{"100067","Fourmile",{2004121 /*   MAY  */,2004165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"100067","Fourmile",{2004202 /*Late JUL*/,2004365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100067","Fourmile",{2005226 /* mid AUG*/,2005264 /*Late SEP*/ ,out_of_range_pot_low_error_quality}}

,{"100069","FishHook",{2007001 /*   JAN  */,2007073 /* mid MAR*/ ,out_of_range_pot_low_error_quality}}

,{"100071","K2H.UED",{2004001 /*   JAN  */,2006366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100071","K2H.UED",{2007001 /*   JAN  */,2007120 /*   APR  */ ,out_of_range_pot_low_error_quality}}

,{"100113","Finley.UED",{2006080 /*Late MAR*/,2006165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"100113","Finley.UED",{2007001 /*   JAN  */,2007104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}

,{"100114","Benton City.UED",{2005060 /*   MAR  */,2005141 /*Late MAY*/ ,out_of_range_pot_low_error_quality}}
,{"100114","Benton City.UED",{2006134 /* Mid MAY*/,2006165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"100114","Benton City.UED",{2007080 /*Late MAR*/,2007251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}
,{"100114","Benton City.UED",{2008213 /*   AUG  */,2008365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"100128","Touchet.UED",{1992001 /*   JAN  */,1992066 /*Erly MAR*/ ,out_of_range_pot_low_error_quality}}
,{"100128","Touchet.UED",{1998121 /*   MAY  */,1998165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"100128","Touchet.UED",{2007001 /*   JAN  */,2007073 /* mid MAR*/ ,out_of_range_pot_low_error_quality}}
,{"100128","Touchet.UED",{2007274 /*   OCT  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100128","Touchet.UED",{2008001 /*   JAN  */,2008134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}}

,{"100134","Eby.UED",{1989134 /* Mid MAY*/,1989365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100134","Eby.UED",{1990001 /*   JAN  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"100139","Gramling.UED",{1989001 /*   JAN  */,2008365  ,out_of_range_pot_low_error_quality}}

,{"100140","Hundred Circles.UED",{2005060 /*   MAR  */,2005104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"100140","Hundred Circles.UED",{2007001 /*   JAN  */,2007073 /* mid MAR*/ ,out_of_range_pot_low_error_quality}}

,{"100147","CBC Pasco.UED",{1998060 /*   MAR  */,1998195 /* mid JUL*/ ,out_of_range_pot_low_error_quality}}
,{"100147","CBC Pasco.UED",{2001073 /* mid MAR*/,2001104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"100147","CBC Pasco.UED",{2005073 /* mid MAR*/,2005181 /*   JUN  */ ,out_of_range_pot_low_error_quality}}
,{"100147","CBC Pasco.UED",{2006001 /*   JAN  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100147","CBC Pasco.UED",{2007001 /*   JAN  */,2007181 /*   JUN  */ ,out_of_range_low_error_quality}}
,{"100147","CBC Pasco.UED",{2007152 /*   JUN  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"100148","WSU TC.UED",{2004001 /*   JAN  */,2004365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100148","WSU TC.UED",{2005001 /*   JAN  */,2005195 /* mid JUL*/  ,out_of_range_pot_low_error_quality}}
,{"100148","WSU TC.UED",{2006152 /*   JUN  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100148","WSU TC.UED",{2007007 /* Mid JAN*/,2007127 /*Erly MAY*/ ,out_of_range_low_error_quality}}
,{"100148","WSU TC.UED",{2008165 /* mid JUN*/,2008219 /*Erly AUG*/ ,out_of_range_pot_low_error_quality}}

,{"110029","WSU Hamilton.UED",{2003001 /*   JAN  */,2003181 /*   JUN  */ ,out_of_range_pot_low_error_quality}}
,{"110029","WSU Hamilton.UED",{2004121 /*   MAY  */,2004165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"110029","WSU Hamilton.UED",{2005073 /* mid MAR*/,2005165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"110029","WSU Hamilton.UED",{2005274 /*   OCT  */,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110029","WSU Hamilton.UED",{2006001 /*   JAN  */,2006251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}
,{"110029","WSU Hamilton.UED",{2006134 /* Mid MAY*/,2006165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"110029","WSU Hamilton.UED",{2006158 /*Erly JUL*/,2006226 /* mid AUG*/ ,out_of_range_high_warning_quality}}
,{"110029","WSU Hamilton.UED",{2006305 /*   NOV  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110029","WSU Hamilton.UED",{2007001 /*   JAN  */,2007251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}

,{"310112","Ahtanum.UED",{2004173 /*  22 JUN*/,2004366 /*   DEC  */ ,not_valid_quality}}
,{"310112","Ahtanum.UED",{2007001 /*   JAN  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310112","Ahtanum.UED",{2008001 /*   JAN  */,2008165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}

,{"310136","Cowiche.UED",{2003165 /* mid JUN*/,2003243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}
,{"310136","Cowiche.UED",{2007001 /*   JAN  */,2007127 /*Erly MAY*/ ,out_of_range_pot_low_error_quality}}
,{"310136","Cowiche.UED",{2008172 /*Late JUN*/,2008366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"310142","Pomona.UED",{1989098 /*   8 APR*/,1989115 /*  25 APR*/ ,out_of_range_pot_low_error_quality}}
,{"310142","Pomona.UED",{1990257 /* mid SEP*/,1990365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310142","Pomona.UED",{1991244 /*   SPT  */,1991318 /* mid NOV*/ ,out_of_range_pot_low_error_quality}}
,{"310142","Pomona.UED",{1993244 /*   SPT  */,1993334 /*Late NOV*/ ,out_of_range_pot_low_error_quality}}

,{"310143","Moxee.UED",{1997264 /*Late SEP*/,1997280 /*Erly OCT*/ ,out_of_range_pot_low_error_quality}}
,{"310143","Moxee.UED",{2006158 /*Erly JUN*/,2006212 /*   JUL  */ ,out_of_range_pot_low_error_quality}}

,{"999144","Tonasket.UED",{2003202 /*Late JUL*/,2003273 /*   SEP  */ ,out_of_range_pot_low_error_quality}}
,{"999144","Tonasket.UED",{2004111 /*Late APR*/,2004204 /*   OCT  */ ,out_of_range_pot_low_error_quality}} /*Erratic*/

,{"999146","Oroville.UED",{1994001 /*   JAN  */,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}  /*(all solar radiation is low) */


// The following are for the new station ID's (renumbered sometime in 2009)
,{"330074","Brewster",{1994202 /*Late JUL*/,1994158 /*Erly JUN*/ ,out_of_range_low_warning_quality}}
,{"330074","Brewster",{1995111 /*Late APR*/,1995127 /*Erly MAY*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{1997134 /* Mid MAY*/,1997158 /*Erly JUN*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{1997172 /*Late JUN*/,1997287 /* mid OCT*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{1998127 /*Erly MAY*/,1998195 /* mid JUL*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{1999104 /* Mid APR*/,1999219 /*Erly AUG*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{2002097 /*Erly APR*/,2002294 /*Late OCT*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{2003097 /*Erly APR*/,2003226 /* mid AUG*/ ,out_of_range_pot_low_error_quality}} /*year generally poor with missing periods*/
,{"330074","Brewster",{2004032 /*   FEB  */,2004111 /*Late APR*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{2004226 /* mid AUG*/,2004233 /*Late AUG*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{2005073 /* mid MAR*/,2005097 /*Erly APR*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{2005141 /*Late MAY*/,2005158 /*Erly JUN*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{2005287 /* mid OCT*/,2005318 /* mid NOV*/ ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{2007038 /*Erly FEB*/,2007041 /*  10 FEB*/  ,out_of_range_pot_low_error_quality}}
,{"330074","Brewster",{2007165 /* mid JUN*/,2007202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}

,{"310138","Buena",{2008165 /* mid JUN*/,2008219 /*Erly AUG*/ ,out_of_range_high_warning_quality}}

,{"330141","WSU TFREC",{2006165 /* mid JUN*/,2006202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}
,{"330141","WSU TFREC",{2006134 /* Mid MAY*/,2006195 /* mid JUL*/  ,out_of_range_low_error_quality}}
,{"330141","WSU TFREC",{2007001 /*   JAN  */,2007120 /*   APR  */ ,out_of_range_pot_low_error_quality}}

,{"330145","Ellisforde",{2004202 /*Late JUL*/,2004294 /*Late OCT*/ ,out_of_range_pot_low_error_quality}}
,{"330145","Ellisforde",{2007165 /* mid JUN*/,2007287 /* mid OCT*/ ,out_of_range_pot_low_error_quality}}
,{"330145","Ellisforde",{2008121 /*   MAY  */,2008219 /*Erly AUG*/ ,out_of_range_pot_low_error_quality}}

,{"300070","Welland",{1993001 /*   JAN  */,1998365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300070","Welland",{2004091 /*   APR  */,2004365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300070","Welland",{2005001 /*   JAN  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300070","Welland",{2007001 /*   JAN  */,2007080 /*Late MAR*/ ,out_of_range_pot_low_error_quality}}
,{"300070","Welland",{2007121 /*   MAY  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"300116","BASIN City.UED",{004001 /*   JAN  */,2004365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300116","BASIN City.UED",{2005121 /*   MAY  */,2005181 /*   JUN  */ ,out_of_range_pot_low_error_quality}}
,{"300116","BASIN City.UED",{2006274 /*   OCT  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"300033","WSU HQ.UED",{2003001 /*   JAN  */,2003366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300033","WSU HQ.UED",{2004001 /*   JAN  */,2004366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300033","WSU HQ.UED",{2005134 /* Mid MAY*/,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300033","WSU HQ.UED",{2006001 /*   JAN  */,2006104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"300033","WSU HQ.UED",{2006287 /* mid OCT*/,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300033","WSU HQ.UED",{2007001 /*   JAN  */,2007134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}}

,{"310111","Gleed.UED",{1998001 /*   JAN  */,1998120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{1998244 /*   SPT  */,1998365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{1999001 /*   JAN  */,1999120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{1999244 /*   SPT  */,1999365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2000001 /*   JAN  */,2000104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2000233 /*Late AUG*/,2000365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2001001 /*   JAN  */,2001251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2001233 /*Late AUG*/,2001365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2002001 /*   JAN  */,2002111 /*Late APR*/ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2003111 /*Late APR*/,2003202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2005165 /* mid JUN*/,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2006001 /*   JAN  */,2006273 /*   SEP  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2007001 /*   JAN  */,2007212 /*   JUL  */ ,out_of_range_pot_low_error_quality}}
,{"310111","Gleed.UED",{2008001 /*   JAN  */,2008165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}

,{"300117","McClure.UED",{1989001 /*   JAN  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300117","McClure.UED",{2008001 /*   JAN  */,2008120 /*   APR  */ ,out_of_range_pot_low_error_quality}}

,{"300118","McWhorter.UED",{1989001 /*   JAN  */,2007265 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300118","McWhorter.UED",{2008001 /*   JAN  */,2008104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}

,{"310120","Port of Sunnyside.UED",{2003104 /* Mid APR*/,2003181 /*   JUN  */ ,out_of_range_pot_low_error_quality}}
,{"310120","Port of Sunnyside.UED",{2005073 /* mid MAR*/,2005141 /*Late MAY*/ ,out_of_range_pot_low_error_quality}}
,{"310120","Port of Sunnyside.UED",{2005172 /*Late JUN*/,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310120","Port of Sunnyside.UED",{2006001 /*   JAN  */,2006104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"310120","Port of Sunnyside.UED",{2007001 /*   JAN  */,2007251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}

,{"310131","Wapato.UED",{1993001 /*   JAN  */,1993111 /*Late APR*/ ,out_of_range_pot_low_error_quality}}
,{"310131","Wapato.UED",{1997001 /*   JAN  */,1997080 /*Late MAR*/ ,out_of_range_pot_low_error_quality}}
,{"310131","Wapato.UED",{1998001 /*   JAN  */,1998111 /*Late APR*/ ,out_of_range_pot_low_error_quality}}
,{"310131","Wapato.UED",{1999001 /*   JAN  */,1999120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"310131","Wapato.UED",{2000001 /*   JAN  */,2000120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"310131","Wapato.UED",{2001001 /*   JAN  */,2001073 /* mid MAR*/ ,out_of_range_pot_low_error_quality}}
,{"310131","Wapato.UED",{2006001 /*   JAN  */,2006104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"310131","Wapato.UED",{2006172 /*Late JUN*/,2006294 /*Late OCT*/ ,out_of_range_high_warning_quality}}
,{"310131","Wapato.UED",{2008001 /*   JAN  */,2008120 /*   APR  */ ,out_of_range_pot_low_error_quality}}

,{"310132","Parker.UED",{1989001 /*   JAN  */,1999365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310132","Parker.UED",{2000001 /*   JAN  */,2000243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}
,{"310132","Parker.UED",{2003001 /*   JAN  */,2003212 /*   JUL  */ ,out_of_range_pot_low_error_quality}}
,{"310132","Parker.UED",{2004001 /*   JAN  */,2005202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}
,{"310132","Parker.UED",{2007001 /*   JAN  */,2007251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}
,{"310132","Parker.UED",{2008001 /*   JAN  */,2008120 /*   APR  */ ,out_of_range_pot_low_error_quality}}

,{"310135","Outlook.UED",{2007121 /*   MAY  */,2007264 /*Late SEP*/ ,out_of_range_pot_low_error_quality}}

,{"310136","Sunnyside.UED",{2006001 /*   JAN  */,2006120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"310136","Sunnyside.UED",{2007001 /*   JAN  */,2007073 /* mid MAR*/ ,out_of_range_pot_low_error_quality}}

,{"330073","Quincy.UED",{1990141 /*Late MAY*/,1990165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"330073","Quincy.UED",{2007121 /*   MAY  */,2007165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"330073","Quincy.UED",{2005073 /* mid MAR*/,2005104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"330073","Quincy.UED",{2005274 /*   OCT  */,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"330073","Quincy.UED",{2007001 /*   JAN  */,2008165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}

,{"330121","Mattawa.UED",{2006001 /*   JAN  */,2006152 /*   9 SPT*/ ,out_of_range_pot_low_error_quality}}
,{"330121","Mattawa.UED",{2006244 /*   SPT  */,2006275 /*   2 OCT*/ ,out_of_range_pot_low_error_quality}}
,{"330121","Mattawa.UED",{2006275 /*   2 OCT*/,2006339 /*   5 DEC*/ ,not_valid_quality}}
,{"330121","Mattawa.UED",{2007001 /*   JAN  */,2007080 /*Late MAR*/ ,out_of_range_pot_low_error_quality}}
,{"330121","Mattawa.UED",{2007134 /* Mid MAY*/,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"300122","WSU Othello.UED",{1989134 /* Mid MAY*/,1989365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300122","WSU Othello.UED",{1990001 /*   JAN  */,1991365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300122","WSU Othello.UED",{1992001 /*   JAN  */,1992104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"300122","WSU Othello.UED",{2003001 /*   JAN  */,2003365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"300122","WSU Othello.UED",{2005001 /*   JAN  */,2005134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}}

,{"330127","Moses Lake.UED",{2005134 /* Mid MAY*/,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"330127","Moses Lake.UED",{2006001 /*   JAN  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"330127","Moses Lake.UED",{2007001 /*   JAN  */,2007127 /*Erly MAY*/ ,out_of_range_pot_low_error_quality}}

,{"310102","WSU Puyallup.UED",{1996134 /* Mid MAY*/,1996202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}
,{"310102","WSU Puyallup.UED",{1997141 /*Late MAY*/,1997334 /*   NOV  */ ,out_of_range_pot_low_error_quality}}
,{"310102","WSU Puyallup.UED",{1998104 /* Mid APR*/,1998264 /*Late SEP*/ ,out_of_range_pot_low_error_quality}}
,{"310102","WSU Puyallup.UED",{1999001 /*   JAN  */,1999090 /*   MAR  */ ,out_of_range_pot_low_error_quality}}
,{"310102","WSU Puyallup.UED",{1999104 /* Mid APR*/,1999304 /*   OCT  */ ,out_of_range_pot_low_error_quality}}
,{"310102","WSU Puyallup.UED",{2000104 /* Mid APR*/,2000226 /* mid AUG*/ ,out_of_range_pot_low_error_quality}}
,{"310102","WSU Puyallup.UED",{2004001 /*   JAN  */,2004257 /* mid SEP*/ ,out_of_range_pot_low_error_quality}}
,{"310102","WSU Puyallup.UED",{2005152 /*   JUN  */,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"310102","WSU Puyallup.UED",{2006001 /*   JAN  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"300045","Roza.UED",{2002060 /*   MAR  */,2002120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"300045","Roza.UED",{2006060 /*   MAR  */,2006104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"300045","Roza.UED",{2007001 /*   JAN  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"330061","Nooksack.UED",{2006134 /* Mid MAY*/,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"330061","Nooksack.UED",{2007001 /*  JAN  */- 2008366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"330063","Lynden.UED",{2000060 /*   MAR  */,2000226 /* mid AUG*/ ,out_of_range_pot_low_error_quality}}
,{"330063","Lynden.UED",{2001001 /*   JAN  */,2001134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}} // (only a few date in this period but all low)
,{"330063","Lynden.UED",{2001134 /* Mid MAY*/,2001273 /*   SEP  */ ,out_of_range_pot_low_error_quality}}
,{"330063","Lynden.UED",{2002121 /*   MAY  */,2002165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"330063","Lynden.UED",{2003060 /*   MAR  */,2003294 /*Late OCT*/ ,out_of_range_pot_low_error_quality}}
,{"330063","Lynden.UED",{2004001 /*   JAN  */,2004251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}
,{"330063","Lynden.UED",{2005121 /*   MAY  */,2005195 /* mid JUL*/ ,out_of_range_pot_low_error_quality}}
,{"330063","Lynden.UED",{2006121 /*   MAY  */,2006165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"330063","Lynden.UED",{2008001 /*   JAN  */,2008243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}

,{"330104","Pogue Flat.UED",{1995134 /* Mid MAY*/,1995226 /* mid AUG*/ ,out_of_range_pot_low_error_quality}}
,{"330104","Pogue Flat.UED",{1996104 /* Mid APR*/,1996243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}
,{"330104","Pogue Flat.UED",{1997121 /*   MAY  */,1997304 /*   OCT  */ ,out_of_range_pot_low_error_quality}}
,{"330104","Pogue Flat.UED",{1998001 /*   JAN  */,1999366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"330104","Pogue Flat.UED",{2000001 /*   JAN  */,2000243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}
,{"330104","Pogue Flat.UED",{2001001 /*   JAN  */,2001134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}} // (only a few date in this period but all low)
,{"330104","Pogue Flat.UED",{2001134 /* Mid MAY*/,2001365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"330104","Pogue Flat.UED",{2003091 /*   APR  */,2003365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"330104","Pogue Flat.UED",{2004001 /*   JAN  */,2004251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}

// The following are for the old station ID's (renumbered sometime in 2009)
, {"074","Brewster",{1994202 /*Late JUL*/,1994158 /*Erly JUN*/ ,out_of_range_low_warning_quality}}
,{"074","Brewster",{1995111 /*Late APR*/,1995127 /*Erly MAY*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{1997134 /* Mid MAY*/,1997158 /*Erly JUN*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{1997172 /*Late JUN*/,1997287 /* mid OCT*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{1998127 /*Erly MAY*/,1998195 /* mid JUL*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{1999104 /* Mid APR*/,1999219 /*Erly AUG*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{2002097 /*Erly APR*/,2002294 /*Late OCT*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{2003097 /*Erly APR*/,2003226 /* mid AUG*/ ,out_of_range_pot_low_error_quality}} /*year generally poor with missing periods*/
,{"074","Brewster",{2004032 /*   FEB  */,2004111 /*Late APR*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{2004226 /* mid AUG*/,2004233 /*Late AUG*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{2005073 /* mid MAR*/,2005097 /*Erly APR*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{2005141 /*Late MAY*/,2005158 /*Erly JUN*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{2005287 /* mid OCT*/,2005318 /* mid NOV*/ ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{2007038 /*Erly FEB*/,2007041 /*  10 FEB*/  ,out_of_range_pot_low_error_quality}}
,{"074","Brewster",{2007165 /* mid JUN*/,2007202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}

,{"138","Buena",{2008165 /* mid JUN*/,2008219 /*Erly AUG*/ ,out_of_range_high_warning_quality}}

,{"141","WSU TFREC",{2006165 /* mid JUN*/,2006202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}
,{"141","WSU TFREC",{2006134 /* Mid MAY*/,2006195 /* mid JUL*/  ,out_of_range_low_error_quality}}
,{"141","WSU TFREC",{2007001 /*   JAN  */,2007120 /*   APR  */ ,out_of_range_pot_low_error_quality}}

,{"145","Ellisforde",{2004202 /*Late JUL*/,2004294 /*Late OCT*/ ,out_of_range_pot_low_error_quality}}
,{"145","Ellisforde",{2007165 /* mid JUN*/,2007287 /* mid OCT*/ ,out_of_range_pot_low_error_quality}}
,{"145","Ellisforde",{2008121 /*   MAY  */,2008219 /*Erly AUG*/ ,out_of_range_pot_low_error_quality}}

,{"100070","Welland",{1993001 /*   JAN  */,1998365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100070","Welland",{2004091 /*   APR  */,2004365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100070","Welland",{2005001 /*   JAN  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100070","Welland",{2007001 /*   JAN  */,2007080 /*Late MAR*/ ,out_of_range_pot_low_error_quality}}
,{"100070","Welland",{2007121 /*   MAY  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"100116","BASIN City.UED",{004001 /*   JAN  */,2004365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"100116","BASIN City.UED",{2005121 /*   MAY  */,2005181 /*   JUN  */ ,out_of_range_pot_low_error_quality}}
,{"100116","BASIN City.UED",{2006274 /*   OCT  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"110033","WSU HQ.UED",{2003001 /*   JAN  */,2003366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110033","WSU HQ.UED",{2004001 /*   JAN  */,2004366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110033","WSU HQ.UED",{2005134 /* Mid MAY*/,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110033","WSU HQ.UED",{2006001 /*   JAN  */,2006104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"110033","WSU HQ.UED",{2006287 /* mid OCT*/,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110033","WSU HQ.UED",{2007001 /*   JAN  */,2007134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}}

,{"110111","Gleed.UED",{1998001 /*   JAN  */,1998120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{1998244 /*   SPT  */,1998365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{1999001 /*   JAN  */,1999120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{1999244 /*   SPT  */,1999365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2000001 /*   JAN  */,2000104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2000233 /*Late AUG*/,2000365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2001001 /*   JAN  */,2001251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2001233 /*Late AUG*/,2001365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2002001 /*   JAN  */,2002111 /*Late APR*/ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2003111 /*Late APR*/,2003202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2005165 /* mid JUN*/,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2006001 /*   JAN  */,2006273 /*   SEP  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2007001 /*   JAN  */,2007212 /*   JUL  */ ,out_of_range_pot_low_error_quality}}
,{"110111","Gleed.UED",{2008001 /*   JAN  */,2008165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}

,{"110117","McClure.UED",{1989001 /*   JAN  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110117","McClure.UED",{2008001 /*   JAN  */,2008120 /*   APR  */ ,out_of_range_pot_low_error_quality}}

,{"110118","McWhorter.UED",{1989001 /*   JAN  */,2007265 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110118","McWhorter.UED",{2008001 /*   JAN  */,2008104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}

,{"110120","Port of Sunnyside.UED",{2003104 /* Mid APR*/,2003181 /*   JUN  */ ,out_of_range_pot_low_error_quality}}
,{"110120","Port of Sunnyside.UED",{2005073 /* mid MAR*/,2005141 /*Late MAY*/ ,out_of_range_pot_low_error_quality}}
,{"110120","Port of Sunnyside.UED",{2005172 /*Late JUN*/,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110120","Port of Sunnyside.UED",{2006001 /*   JAN  */,2006104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"110120","Port of Sunnyside.UED",{2007001 /*   JAN  */,2007251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}

,{"110131","Wapato.UED",{1993001 /*   JAN  */,1993111 /*Late APR*/ ,out_of_range_pot_low_error_quality}}
,{"110131","Wapato.UED",{1997001 /*   JAN  */,1997080 /*Late MAR*/ ,out_of_range_pot_low_error_quality}}
,{"110131","Wapato.UED",{1998001 /*   JAN  */,1998111 /*Late APR*/ ,out_of_range_pot_low_error_quality}}
,{"110131","Wapato.UED",{1999001 /*   JAN  */,1999120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"110131","Wapato.UED",{2000001 /*   JAN  */,2000120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"110131","Wapato.UED",{2001001 /*   JAN  */,2001073 /* mid MAR*/ ,out_of_range_pot_low_error_quality}}
,{"110131","Wapato.UED",{2006001 /*   JAN  */,2006104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"110131","Wapato.UED",{2006172 /*Late JUN*/,2006294 /*Late OCT*/ ,out_of_range_high_warning_quality}}
,{"110131","Wapato.UED",{2008001 /*   JAN  */,2008120 /*   APR  */ ,out_of_range_pot_low_error_quality}}

,{"110132","Parker.UED",{1989001 /*   JAN  */,1999365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"110132","Parker.UED",{2000001 /*   JAN  */,2000243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}
,{"110132","Parker.UED",{2003001 /*   JAN  */,2003212 /*   JUL  */ ,out_of_range_pot_low_error_quality}}
,{"110132","Parker.UED",{2004001 /*   JAN  */,2005202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}
,{"110132","Parker.UED",{2007001 /*   JAN  */,2007251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}
,{"110132","Parker.UED",{2008001 /*   JAN  */,2008120 /*   APR  */ ,out_of_range_pot_low_error_quality}}

,{"110135","Outlook.UED",{2007121 /*   MAY  */,2007264 /*Late SEP*/ ,out_of_range_pot_low_error_quality}}

,{"110136","Sunnyside.UED",{2006001 /*   JAN  */,2006120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"110136","Sunnyside.UED",{2007001 /*   JAN  */,2007073 /* mid MAR*/ ,out_of_range_pot_low_error_quality}}

,{"131073","Quincy.UED",{1990141 /*Late MAY*/,1990165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"131073","Quincy.UED",{2007121 /*   MAY  */,2007165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"131073","Quincy.UED",{2005073 /* mid MAR*/,2005104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"131073","Quincy.UED",{2005274 /*   OCT  */,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"131073","Quincy.UED",{2007001 /*   JAN  */,2008165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}

,{"131131","Mattawa.UED",{2006001 /*   JAN  */,2006152 /*   9 SPT*/ ,out_of_range_pot_low_error_quality}}
,{"131131","Mattawa.UED",{2006244 /*   SPT  */,2006275 /*   2 OCT*/ ,out_of_range_pot_low_error_quality}}
,{"131131","Mattawa.UED",{2006275 /*   2 OCT*/,2006339 /*   5 DEC*/ ,not_valid_quality}}
,{"131131","Mattawa.UED",{2007001 /*   JAN  */,2007080 /*Late MAR*/ ,out_of_range_pot_low_error_quality}}
,{"131131","Mattawa.UED",{2007134 /* Mid MAY*/,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"131122","WSU Othello.UED",{1989134 /* Mid MAY*/,1989365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"131122","WSU Othello.UED",{1990001 /*   JAN  */,1991365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"131122","WSU Othello.UED",{1992001 /*   JAN  */,1992104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"131122","WSU Othello.UED",{2003001 /*   JAN  */,2003365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"131122","WSU Othello.UED",{2005001 /*   JAN  */,2005134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}}

,{"131127","Moses Lake.UED",{2005134 /* Mid MAY*/,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"131127","Moses Lake.UED",{2006001 /*   JAN  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"131127","Moses Lake.UED",{2007001 /*   JAN  */,2007127 /*Erly MAY*/ ,out_of_range_pot_low_error_quality}}

,{"142102","WSU Puyallup.UED",{1996134 /* Mid MAY*/,1996202 /*Late JUL*/ ,out_of_range_pot_low_error_quality}}
,{"142102","WSU Puyallup.UED",{1997141 /*Late MAY*/,1997334 /*   NOV  */ ,out_of_range_pot_low_error_quality}}
,{"142102","WSU Puyallup.UED",{1998104 /* Mid APR*/,1998264 /*Late SEP*/ ,out_of_range_pot_low_error_quality}}
,{"142102","WSU Puyallup.UED",{1999001 /*   JAN  */,1999090 /*   MAR  */ ,out_of_range_pot_low_error_quality}}
,{"142102","WSU Puyallup.UED",{1999104 /* Mid APR*/,1999304 /*   OCT  */ ,out_of_range_pot_low_error_quality}}
,{"142102","WSU Puyallup.UED",{2000104 /* Mid APR*/,2000226 /* mid AUG*/ ,out_of_range_pot_low_error_quality}}
,{"142102","WSU Puyallup.UED",{2004001 /*   JAN  */,2004257 /* mid SEP*/ ,out_of_range_pot_low_error_quality}}
,{"142102","WSU Puyallup.UED",{2005152 /*   JUN  */,2005365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"142102","WSU Puyallup.UED",{2006001 /*   JAN  */,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}


,{"310028","Roza.UED",{2002060 /*   MAR  */,2002120 /*   APR  */ ,out_of_range_pot_low_error_quality}}
,{"310028","Roza.UED",{2006060 /*   MAR  */,2006104 /* mid APR*/ ,out_of_range_pot_low_error_quality}}
,{"310028","Roza.UED",{2007001 /*   JAN  */,2007365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"340061","Nooksack.UED",{2006134 /* Mid MAY*/,2006365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"340061","Nooksack.UED",{2007001 /*  JAN  */- 2008366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}

,{"340063","Lynden.UED",{2000060 /*   MAR  */,2000226 /* mid AUG*/ ,out_of_range_pot_low_error_quality}}
,{"340063","Lynden.UED",{2001001 /*   JAN  */,2001134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}} // (only a few date in this period but all low)
,{"340063","Lynden.UED",{2001134 /* Mid MAY*/,2001273 /*   SEP  */ ,out_of_range_pot_low_error_quality}}
,{"340063","Lynden.UED",{2002121 /*   MAY  */,2002165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"340063","Lynden.UED",{2003060 /*   MAR  */,2003294 /*Late OCT*/ ,out_of_range_pot_low_error_quality}}
,{"340063","Lynden.UED",{2004001 /*   JAN  */,2004251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}
,{"340063","Lynden.UED",{2005121 /*   MAY  */,2005195 /* mid JUL*/ ,out_of_range_pot_low_error_quality}}
,{"340063","Lynden.UED",{2006121 /*   MAY  */,2006165 /* mid JUN*/ ,out_of_range_pot_low_error_quality}}
,{"340063","Lynden.UED",{2008001 /*   JAN  */,2008243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}

,{"999104","Pogue Flat.UED",{1995134 /* Mid MAY*/,1995226 /* mid AUG*/ ,out_of_range_pot_low_error_quality}}
,{"999104","Pogue Flat.UED",{1996104 /* Mid APR*/,1996243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}
,{"999104","Pogue Flat.UED",{1997121 /*   MAY  */,1997304 /*   OCT  */ ,out_of_range_pot_low_error_quality}}
,{"999104","Pogue Flat.UED",{1998001 /*   JAN  */,1999366 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"999104","Pogue Flat.UED",{2000001 /*   JAN  */,2000243 /*   AUG  */ ,out_of_range_pot_low_error_quality}}
,{"999104","Pogue Flat.UED",{2001001 /*   JAN  */,2001134 /* Mid MAY*/ ,out_of_range_pot_low_error_quality}} // (only a few date in this period but all low)
,{"999104","Pogue Flat.UED",{2001134 /* Mid MAY*/,2001365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"999104","Pogue Flat.UED",{2003091 /*   APR  */,2003365 /*   DEC  */ ,out_of_range_pot_low_error_quality}}
,{"999104","Pogue Flat.UED",{2004001 /*   JAN  */,2004251 /*   MAY  */ ,out_of_range_pot_low_error_quality}}

,{0,0,{0,0,0}}};

//______________________________________________________________________________/
AgWeatherNet_format_convertor::AgWeatherNet_format_convertor(int argc,const char *argv[])
: UED_convertor            (argc,argv)
, curr_station_database    (0)
, curr_geo_location_record  (0)
//091027, curr_UED                  (0)
, metric_units              (true)
, elevation_arbitrary_units (0.0)
, curr_column_headers      (0)
{

//100303   CORN::File_name program_directory(argv[0]);
//100303 moved to UED_convertor constructor   CS::Suite_directory = new CS::Suite_Directory(program_directory);
   all_known_weather_stations.set_reporting_agency(All_known_weather_stations::AgWeatherNet_REPORTING_AGENCY);
};
//__________________________________AgWeatherNet_format_convertor constructor__/
uint32 AgWeatherNet_format_convertor::perform_import()
{
  uint32 record_count = 0;
   // Open input file
   ifstream input_file(parameters.target_filename.c_str());
   cout << "Reading input file(s):" << parameters.target_filename.c_str() << endl;
//   long buffer_read = 0;
   CORN::UIO_string buffer_str;
   bool at_EOF = false;
   curr_station_database = 0;
   CORN::Ustring file_validation_description;
//091021   curr_UED = 0;;
   do
   {
      getline(input_file,buffer_str); ///buffer_str.read_line(input_file);
      if (buffer_str.length())
      {
         if (buffer_str.find("Daily Data Report") != CORN_npos)  // This signals the start of station
         {
            read_header(input_file);
            getline(input_file,buffer_str); // .read_line(input_file);
            parse_column_headers(buffer_str);
/* now using station database
            if (curr_UED)
            {  // open data base for station
//               curr_UED->finish();
               delete curr_UED;
               curr_UED = 0;
            };
*/
/*Moved to part_detail_line because there could be multiple stations in the file
            UED_File_name ued_filename(parameters.target_filename);
            ued_filename.set_name(curr_geo_location_record->station_name);
            ued_filename.set_ext("UED");
            bool UED_added_now;
            Station_database *station_database = provide_station_database(curr_geo_location_record->station_name,UED_added_now,&ued_filename);
            curr_UED = &(station_database->ued_file);
            curr_UED->take_geolocation_record(curr_geo_location_record);
*/
         } else if ((buffer_str.find("UNIT_ID") != CORN_npos)
                  || (buffer_str.find("Station Num") != CORN_npos) )
         {  // this is a SQL_query form UNIT_ID,Date,JulDay,AIR_TEMP,MaxAirTemp,MinAirTemp,DEWPOINT,REL_HUMIDITY,WIND_SPEED,WIND_DIR,SOLAR_RAD,PRECIP,SOIL_TEMP_8_IN,SOIL_MOIS_8_IN,recordCount

            UED_File_name ued_filename(parameters.target_filename);
//            ued_filename.set_name(curr_detail_line_station_ID); // 090921 (curr_geo_location_record->station_name);
            ued_filename.set_ext("UED");
            bool UED_added_now;
               curr_station_database = provide_station_database_from_UED_filename(ued_filename,UED_added_now);
            Geolocation *geoloc = curr_station_database->ued_file.get_geolocation_record();

            // Initially we assumed the target file name is the unit_ID
            if (!geoloc)
            {  // Apparently the target file name is the unit_ID.
               // AWN seems to have inconsistent enumeration of unit numbers
               // (Probably changed over time)
               // The unit_ID filename may either be:
               // - a zero filled 3 digit number.
               // - a 6 digit (zerofilled?) number.
               // It appears that there was a period of time that there were 4 digit unit_ID
               // but I haven't seen any files named this way.


               // Perhaps the filename is 3 character 0 filled form:
               CORN::Ustring unit_ID_non_zero_filled(parameters.target_filename.get_name(false));
//               unit_ID_non_zero_filled.strip(Ustring::Leading,'0');
               geoloc = render_geolocation(unit_ID_non_zero_filled);
               if (!geoloc)
               {  // still not found, try the last three digit of the file name (non-zero filled)
                  CORN::Ustring target_name(parameters.target_filename.get_name(false));
                  CORN::Ustring unit_ID_three_digit_integer(target_name,target_name.length()-3,3);
//                  unit_ID_three_digit_integer.strip(Ustring::Leading,'0');
                  geoloc = render_geolocation(unit_ID_three_digit_integer);
               };
               if (geoloc)
               {
                  curr_station_database->ued_file.know_geolocation(*geoloc);
               };
            }
//               provide_station_database(parameters.target_filename.get_name(false).c_str() ,UED_added_now,&ued_filename);
            // We have no geolocation data in this file type curr_UED->take_geolocation_record(curr_geo_location_record);

            parse_column_headers(buffer_str);

            Weather_validator *weather_validator = curr_station_database->provide_weather_data_validator();
            if (!weather_validator)
            {
               cerr << "Unable to provide weather validator, unvalidated data will not be imported for file:" << parameters.target_filename << endl;
               return 0;
            };
         } else // this is a detail line for the current station
         {  CORN::Ustring detail_line_validation_description;
            parse_detail_line(buffer_str,detail_line_validation_description);
            if (detail_line_validation_description.length())
            {
               if (!file_validation_description.length())
               {
                  file_validation_description.append(parameters.target_filename);
                  file_validation_description.append("\n");
               };
               file_validation_description.append(detail_line_validation_description);
               file_validation_description.append("\n");
            };
            record_count ++;
//cout << endl;

         };
      }; // else blank lines are ignored (there may be blank lines between station data sets.
      at_EOF =  !input_file.good();
   } while (!at_EOF);
   if (file_validation_description.length())
   {
      CORN::Smart_file_name import_log_fname(parameters.target_filename);
      import_log_fname.set_ext("UED_import_log");
      ofstream import_log(import_log_fname.c_str());
      import_log << file_validation_description;
   };
//   if (curr_UED) delete curr_UED;
  return record_count;
};
//_____________________________________________________________perform_import__/
void AgWeatherNet_format_convertor::read_header(ifstream &input_file)
{
   curr_geo_location_record = new UED::Geolocation_record;
   CORN::UIO_string buffer_str;
   // The first line has already been read
   // buffer_str.read_line(input_file);   // Daily Data Report.,,,,,,,,,,,,,,,,
   getline(input_file,buffer_str); //buffer_str.read_line(input_file);   // Data Extracted: 2009-08-31.,,,,,,,,,,,,,,,,
   getline(input_file,buffer_str); //   buffer_str.read_line(input_file);   // Station: Paterson.,,,,,,,,,,,,,,,,
   {  // extract the station
      CORN_pos period_pos = buffer_str.find(".");
      CORN::Ustring station_name(buffer_str,9,period_pos - 9);
      curr_geo_location_record->set_station_name(station_name);
      cout << station_name << endl;
   }
   getline(input_file,buffer_str); //   buffer_str.read_line(input_file);   // Lat: 45.9 Lng: 119.5 Elevation:   410.,,,,,,,,,,,,,,,,
   {  // extract the geoloc
      CORN::Ustring latitude_str(buffer_str,4,5);
      float32 latitude = atof(latitude_str.c_str());
      curr_geo_location_record->set_latitude_dec_deg_32(latitude);

      CORN::Ustring longitude_str(buffer_str,14,6);
      float32 longitude = atof(longitude_str.c_str());
      // The longitude is assumed to be west even though there is no sign or westward indicator.
      curr_geo_location_record->set_longitude_dec_deg_32( -longitude);   // west has negative sign

      CORN::Ustring elevation_str(buffer_str,31);
      elevation_arbitrary_units = atof(elevation_str.c_str());

      // There is no state indicator, but most stations are in washington.
   }
   CORN::Ustring buffer_possibly_blank;
   getline(input_file,buffer_possibly_blank); // buffer_possibly_blank.getline(input_file);   // Date Range from 1988-1-1 to 2009-8-31.,,,,,,,,,,,,,,,,
//   char EOL;
//   input_file >> EOL;
   getline(input_file,buffer_possibly_blank);    //buffer_possibly_blank.getline(input_file);   // blank line
   getline(input_file,buffer_possibly_blank);    //buffer_possibly_blank.getline(input_file);   // Note: Values = 99999 indicate sensor failure.,,,,,,,,,,,,,,,,
   getline(input_file,buffer_possibly_blank);    //buffer_possibly_blank.getline(input_file);   // blank line
//   input_file >> EOL;                        // blank line
};
//________________________________________________________________read_header__/
void AgWeatherNet_format_convertor::parse_column_headers(const CORN::Ustring &buffer_str)
{
   // Station Unit ID  , Date    (yyyy-mm-dd), Julian Day  , Avg Air Temp ( C), Max Air Temp ( C), Min Air Temp ( C), Avg Dew point ( C), Avg RH  (%), Avg Wind Speed (m/s), Avg Wind Dir (Degree), Total Solar Rad (MJ/m 2 ), Total Precip  (mm), Avg Leaf Wet (Unity), Avg Soil Temp8 ( C), Min Battery  (Volt), ETr Alfalfa  (mm),.
   metric_units = buffer_str.find("(mm)") != CORN_npos;
   if (curr_geo_location_record) // May be null if reading a SQL dump file
      curr_geo_location_record->set_elevation_meter(
         (metric_units)
         ? elevation_arbitrary_units
         : foot_to_m(elevation_arbitrary_units));
   if (curr_column_headers)
      delete curr_column_headers;
   curr_column_headers = new CORN::SDF_List(buffer_str.c_str(),false);
};
//________________________________________________________read_column_headers__/
void AgWeatherNet_format_convertor::parse_detail_line
(const CORN::Ustring &buffer_str
,CORN::Ustring &detail_line_validation_description
)
{
   CORN::SDF_List detail_elements(buffer_str.c_str(),false);
   UED::Time_query_single_date  *set_query = 0;
   CORN::Date record_date;

   Weather_validator *weather_validator = curr_station_database->provide_weather_data_validator();

   FOR_EACH_IN(column_header,CORN::SDF_List::Item,(*curr_column_headers),each_column_header)
   {
      UED_data_record_creation_layout *creation = 0;
      CORN::Units_code raw_data_units;


      CORN::SDF_List::Item *element_value = (CORN::SDF_List::Item *)detail_elements.pop_at_head();
      if       ((column_header->value.find("Unit ID")     != CORN_npos) || ((column_header->value.find("UNIT_ID")     != CORN_npos)))
      {
//         if (curr_geo_location_record)
//            curr_geo_location_record->station_ID_code = element_value->value;
      }
      else if  (column_header->value.find("Date")   != CORN_npos)
      {
         if (element_value->value.find("-") != CORN_npos)
         {  record_date.set_format(D_YMD,D_YYYY|D_M|D_lead_zero,'-',false);
         } else   if (element_value->value.find("/") != CORN_npos)
         {  record_date.set_format(D_MDY,D_YYYY|D_M|D_lead_zero,'/',false);
         };
         record_date.set_c_str(element_value->value.c_str());
         set_query = new UED::Time_query_single_date(record_date.get_datetime64());
         cout << element_value->value.c_str() << '\r';
      }
      else if  ((column_header->value.find("Julian")   != CORN_npos) || (column_header->value.find("JulDay")   != CORN_npos)){ /* do nothing with the Julian day because we already have the full date */ }
      else if  (column_header->value.find("Year")!= CORN_npos)
      {  CORN::Year year = atoi(element_value->value.c_str());
         record_date.set_year(year);
      }
      else if  (column_header->value.find("DOY")!= CORN_npos)
      {  if (set_query) delete set_query;  // Prefer to use Year and DOY because there has been a wide variety of date format in these files.
         CORN::DOY doy = atoi(element_value->value.c_str());
         record_date.set_DOY(doy);
         set_query = new UED::Time_query_single_date(record_date.get_datetime64());
      }
      else if  ((column_header->value.find("Avg Air Temp")   != CORN_npos) || (column_header->value.find("AIR_TEMP")   != CORN_npos) || (column_header->value.find("TavgF")   != CORN_npos) )
      {
         creation       = &avg_temperature_creation;
         raw_data_units = metric_units ? UC_celcius : UE_Farenheit;
      }
      else if  ((column_header->value.find("Max Air Temp")   != CORN_npos) || (column_header->value.find("MaxAirTemp")   != CORN_npos)|| (column_header->value.find("TmaxF")   != CORN_npos))
      {
         creation       = &max_temperature_creation;
         raw_data_units = metric_units ? UC_celcius : UE_Farenheit;
      }
      else if ((column_header->value.find("Min Air Temp")   != CORN_npos) ||  (column_header->value.find("MinAirTemp")   != CORN_npos)||  (column_header->value.find("TminF")   != CORN_npos))
      {
         creation       = &min_temperature_creation;
         raw_data_units = metric_units ? UC_celcius : UE_Farenheit;
      }
      else if  ((column_header->value.find("Avg Dew point")   != CORN_npos) || (column_header->value.find("DEWPOINT")   != CORN_npos) || (column_header->value.find("TdewF")   != CORN_npos))
      {
         creation       = &avg_dew_point_temperature_creation;
         raw_data_units = metric_units ? UC_celcius : UE_Farenheit;
      }
      else if  ((column_header->value.find("Avg RH")   != CORN_npos) || (column_header->value.find("REL_HUMIDITY")   != CORN_npos))
      {
         creation       = &avg_relative_humidity_creation;;
         raw_data_units = UC_percent;
      }
      else if  ((column_header->value.find("Avg Wind Speed")   != CORN_npos) || (column_header->value.find("WIND_SPEED")   != CORN_npos)||(column_header->value.find("WindAvg_mph")   != CORN_npos))
      {
         creation       = &wind_speed_creation;;
         raw_data_units = metric_units ? UC_meters_per_second : UE_miles_per_hour;
      }
      else if  ((column_header->value.find("Avg Wind Dir")   != CORN_npos) || (column_header->value.find("WIND_DIR")   != CORN_npos))
      {
         creation       = &wind_direction_creation;
         raw_data_units = UC_degree_angle;  // UC_degree_from_north;  // Warning it is not known the wind direction orientation
      }
      else if  ((column_header->value.find("Rs_Langley")   != CORN_npos) )
      {
         creation       = &solar_radiation_creation;
         raw_data_units = UC_MJ_per_m2; //  These were incorrectly marked as UE_Langley;
      }
      else if  ((column_header->value.find("Total Solar Rad")   != CORN_npos) || (column_header->value.find("SOLAR_RAD")   != CORN_npos))
      {
         creation       = &solar_radiation_creation;
         raw_data_units = UC_MJ_per_m2; // (MJ/m 2 is used for both english and metric units.
      }
      else if  ((column_header->value.find("Total Precip")   != CORN_npos) || (column_header->value.find("PRECIP")   != CORN_npos) || (column_header->value.find("Rain_in")   != CORN_npos))
      {
         creation       = &precipitation_creation;
         raw_data_units = metric_units ? UC_mm : UE_inch_linear;
      }
      else if  (column_header->value.find("Avg Leaf Wet")   != CORN_npos)
      { // This element is not used
         creation       = 0;
         // raw_data_units = metric_units ? xxx : xxxx;     (Unity)
      }
      else if  (column_header->value.find("Avg Soil Temp")   != CORN_npos)
      {  // The soil temperature is not currently used.
         creation       = 0;
         raw_data_units = metric_units ? UC_celcius : UE_Farenheit;
      }
      else if  (column_header->value.find("Min Battery")   != CORN_npos)
      {  // (Volt)
         // station battery life is not used
         creation       = 0;
         raw_data_units = UC_volt;
      }
      else if  (column_header->value.find("ETr Alfalfa")   != CORN_npos)
      {  // ET is not currently used.
         creation       = 0;
         raw_data_units = metric_units ? UC_mm : UE_inch_linear;
      }
      // else Ignore the column I.e.
      // SOIL_TEMP_8_IN SOIL_MOIS_8_IN recordCount

      CORN::Quality attribute = CORN::measured_quality;      // first assume measured quality

      {//________________________________________________________________________
         if (creation && set_query)
         {
            float32 value = 0;
            CORN::Ustring validation_description;
            if (weather_validator)
              // Validate the data value
               value =weather_validator->validate_string
               (record_date.get_DOY()
               ,element_value->value
               ,creation->variable_code
               ,raw_data_units
               ,UT_day  // timestep
               ,CORN::measured_quality
               ,CORN::measured_quality
               , attribute // return
               ,validation_description
               );

            // Validate known station problems
            Date32 record_date_32 = record_date.get_date32();
            if (strstr(curr_station_database->ued_file.get_file_name(),"110111" /*Gleed*/) != 0)
            {
               if ( (creation       == &min_temperature_creation) // Problem minimum temperature data
                  &&((record_date_32 == 1997200)
                     || ((record_date_32 >= 1997208) && (record_date_32 <= 1997203) )))
               {
                  attribute.set(not_valid_quality);
                  validation_description.assign("Minimum temperature specifically deemed invalid");
               }
            };
            if (strstr(curr_station_database->ued_file.get_file_name(),"310112" /*Ahtanum*/) != 0)
            {  // All data appears to be invalid after  June 22 in 2004
               if ((record_date_32 >= 2004173) && (record_date_32 <= 2004366))
               {
                  attribute.set(not_valid_quality);
                  validation_description.assign("All elements specifically deemed invalid");
               };
            };
            if (strstr(curr_station_database->ued_file.get_file_name(),"999108" /*OldWSU Long Beach*/) != 0)
            {
               // Omit this, the entire dataset looks poor
                  attribute.set(not_valid_quality);
            };
            // Many of the AgWeatherNet files have problematic solar radiation data
            if ((creation       == &solar_radiation_creation))
            {
               for (int SRQ_i = 0; AgWeatherNet_solar_radiation_quality[SRQ_i].ID; SRQ_i++)
               {
                  if (strstr(curr_station_database->ued_file.get_file_name(),AgWeatherNet_solar_radiation_quality[SRQ_i].ID) != 0)
                  {  // This is a station with problematic data
                        if ( (record_date_32 >= AgWeatherNet_solar_radiation_quality[SRQ_i].quality_range.start)
                           &&(record_date_32 <= AgWeatherNet_solar_radiation_quality[SRQ_i].quality_range.end))
                        {
                                  attribute.set(AgWeatherNet_solar_radiation_quality[SRQ_i].quality_range.quality);

                           validation_description.assign("Solar radiation specifically deemed out of range");

                        }
                  };
               };
            };
            bool created;
            curr_station_database->ued_file.
               set_value(value,*set_query,raw_data_units,attribute,*creation,created,true);

            if (validation_description.length())
            {
               if (!detail_line_validation_description.length())
               {  // Only print this date once
                  detail_line_validation_description.append(record_date.c_str());
               };
               detail_line_validation_description.append(",");
               detail_line_validation_description.append(validation_description);
            };
         };
      }//_______________________________________________________________________

      delete element_value;
   } FOR_EACH_END(each_column_header);
   delete set_query;
};
//___________________________________________________________read_detail_line__/
uint32 AgWeatherNet_format_convertor::perform_export()
{
/* Not yet implemented
*/
   cerr << "Export for UED -> AgWeatherNet is not currently implemented. At this time there are no known programs that read this format." << endl;
   press_return_before_exit = true;
   return 0;
};
//_____________________________________________________________perform_export__/

const char *renamed_station_ID_prefix[] =
{"100"
,"110"
,"130"
,"131"
,"140"
,"142"
,"300"
,"310"
,"311"
,"340"
,"999"
,0
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Geolocation *AgWeatherNet_format_convertor
::render_geolocation(const CORN::Ustring &raw_station_ID)                               const // renders
{
   // AWN stations are a 3 or 6 digit number
   // If there is text after the number is may have been Troy Peters cleaned file
   CORN::Ustring station_ID(raw_station_ID);
   size_t space_hypen_pos = raw_station_ID.find(" -");
   if (space_hypen_pos != CORN_npos)
   {
      station_ID.assign(raw_station_ID.substr(0,space_hypen_pos));
   };

   // I am in the process of replacing all_known_weather_stations
   // because rarely are all weather stations needed in a particular program.
   // Instead derived convertors will implement render_geolocation
   CORN::File_name AgWeatherNet_csv;
   CS::Suite_directory->UED().find_file_name("AgWeatherNet.csv",AgWeatherNet_csv);
   ifstream AWN_stations(AgWeatherNet_csv.c_str());
   CORN::Ustring column_header_row;
   std::getline(AWN_stations,column_header_row);
   CORN::Text_list col_headers(column_header_row.c_str(),',');

   Geolocation *geoloc = new Geolocation;
   bool unit_ID_found = false;
   for (unit_ID_found = false; !unit_ID_found && AWN_stations.good() && !AWN_stations.eof(); )
   {
      CORN::Ustring detail_line_row;
      getline(AWN_stations,detail_line_row);
      CORN::Text_list detail_line_values(detail_line_row.c_str(),',');
      FOR_EACH_IN(col_header,Text_list::Item,col_headers,each_col_header)
      {
         Text_list::Item *col_value  = (Text_list::Item *)detail_line_values.pop_at_head();
         if (col_value)
         {
         if ((col_header->find("UNIT_ID")       != CORN_npos) ||  // These two attributes appear to be duplicate data
             // In 2009 UNIT_ID's changed  ()


             (col_header->find("STATION_ID")    != CORN_npos)   // Either UNIT_ID or STATION_ID may be deprecated
             )
         {  unit_ID_found = station_ID.compare(*col_value) == 0 ;
            if (!unit_ID_found)
            {
               int station_ID_length = station_ID.length();
               int col_value_length =  col_value->length();
               CORN::Ustring station_ID_6digit; if (station_ID_length == 6) station_ID_6digit.assign(station_ID);
               CORN::Ustring col_value_6digit;  if (col_value_length  == 6) col_value_6digit.assign(*col_value);
               if (station_ID_length != col_value_length)
               {
                  for (int i = 0; renamed_station_ID_prefix[i] && !unit_ID_found; i++)
                  {

                     if (station_ID_length != 6)
                     {  station_ID_6digit.assign(renamed_station_ID_prefix[i]);
                        station_ID_6digit.append(station_ID);
                     };
                     if (col_value_length  != 6)
                     {  col_value_6digit.assign(renamed_station_ID_prefix[i]);
                        if (col_value_length == 1)
                           col_value_6digit.append("00");
                        if (col_value_length == 2)
                           col_value_6digit.append("0");
                        col_value_6digit.append(*col_value);
                     };
                     unit_ID_found = station_ID_6digit.compare(col_value_6digit) == 0 ;
                  }
               }
            }
if (unit_ID_found)
cout << col_value->c_str() << '\r';
         };

         if (unit_ID_found)
         {
            if      (col_header->find("UNIT_ID")               != CORN_npos)
               { geoloc->set_station_ID_code(col_value->c_str()); }
            else if (col_header->find("STATION_NAME")          != CORN_npos)
               { geoloc->set_station_name(*col_value); }
            else  if (col_header->find("COUNTY")               != CORN_npos)
               { geoloc->set_county_name (*col_value); }
            else  if (col_header->find("STATION_LATDEG")       != CORN_npos)
               { geoloc->set_latitude_dec_deg_cstr(col_value->c_str()); }
            else  if (col_header->find("STATION_LNGDEG")       != CORN_npos)
               {  // the longitude in the CSV file are not signed correctly!
                  float32 long_dec_deg = - (atof(col_value->c_str()));
                  geoloc->set_longitude_dec_deg_32(long_dec_deg);
               }
            else  if (col_header->find("STATION_ELEVATION")    != CORN_npos)
               { geoloc->set_elevation_feet_cstr(col_value->c_str()); }
            else  if (col_header->find("STATION_DESCRIPTION")  != CORN_npos)
               { /*As of Sept 2009, not many entries have description text */ }
            else  if (col_header->find("STATION_LOCATION")     != CORN_npos)
            {  // Most AWN stations are in Washington
               //NYN if find ("OR") "Oregon"
               //NYN or find ("ID") "Idaho"
               //else
              geoloc->set_state_name("Washington");
              geoloc->set_country_name("USA");
              geoloc->set_comment(col_value->c_str());
            }
            else
            {  /* Attribute is not geolocation */
            };

         }; // if unit_ID_found
         delete col_value;
         };

      } FOR_EACH_END(each_col_header);
   };
   if (!unit_ID_found) { delete geoloc; geoloc = 0; };
   return geoloc;
};
//_________________________________________________________render_geolocation__/




