#include "common/weather/stations/CC_station_datarec.h"
//______________________________________________________________________________
bool Canadian_climatological_station_record::expect_structure(bool for_write)
{
   expect_string("STATIONID"  ,STATIONID,7);
   expect_string("NAME"       ,NAME,80);
   expect_string("PROVINCE"   ,PROVINCE,4);
   // NYI expect_float64("LATDEG" ,LATDEG);
   // NYI expect_float64("LATMIN" ,LATMIN);
   expect_float64("LATDD"     ,LATDD);
   // NYI expect_float64("LONGDEG",LONGDEG);
   // NYI expect_float64("LONGMIN",LONGMIN);
   expect_float64("LONGDD"    ,LONGDD);
   expect_float64("ELEV"      ,ELEV);
   // NYI expect_datetime("DATEBEGAN",DATEBEGAN);
   // NYI expect_string("SEASON",SEASON,1);
   // NYI expect_datetime("DATEENDED",DATEENDED);
   // NYI expect_string("SYNO",SYNO,1);
   // NYI expect_string("HLY",HLY,1);
   // NYI expect_string("TEMP",TEMP,1);
   // NYI expect_string("PRECIP",PRECIP,1);
   // NYI expect_string("RATE",RATE,1);
   // NYI expect_string("WIND",WIND,1);
   // NYI expect_string("SOIL",SOIL,1);
   // NYI expect_string("EVAP",EVAP,1);
   // NYI expect_string("SUN",SUN,1);
   // NYI expect_string("RAD",RAD,1);
   // NYI expect_string("O3",O3,1);
   // NYI expect_string("UA",UA,1);
   // NYI expect_string("SURVEY",SURVEY,1);
   // NYI expect_string("TOWER",TOWER,1);
   // NYI expect_string("AQ",AQ,1);
   // NYI expect_string("NIPHER,NIPHER,1);
   // NYI expect_string("REGION",REGION,1);
   structure_defined = true;                                                     //120314
   return true;
}
//______________________________________________________________________________

