#include "common/weather/stations/AgriMet_stations.h"
#include "common/geomatics/USA_state_FIPS_code.h"
#include "corn/measure/measures.h"
#include "corn/string/strconv.h"
//______________________________________________________________________________
AgriMet_Geolocation AgriMet_geolocation[] =
{
// Station                                   (DMS)   (DMS)
//  ID    Name                  ,State,Elev,Latitude,Longitude,Install Date
 {true,"ABEI","Aberdeen"              ,"ID",4400,42,57,12,-112,49,36,"3/20/1991"}
,{true,"AGKO","Agency Lake"           ,"OR",4150,42,33,55,-121,58,57,"5/3/2000"}
,{true,"AFTY","Afton"                 ,"WY",6210,42,44, 0,-110,56, 9,"10/20/1987"}
,{true,"AHTI","Ashton"                ,"ID",5300,44, 1,30,-111,28, 0,"6/2/1987"}
,{true,"ARAO","Aurora"                ,"OR", 140,45,16,55,-122,45, 1,"10/22/1998"}
,{true,"BKVO","Baker Valley"          ,"OR",3420,44,52,55,-117,57,49,"5/11/2001"}
,{true,"BANO","Bandon"                ,"OR",  80,43, 5,28,-124,25, 2,"5/15/1985"}
,{true,"BATO","Beatty"                ,"OR",4320,42,28,41,-121,16,26,"10/19/2004"}
,{true,"BEWO","Bend"                  ,"OR",3620,44, 2,51,-121,19,13,"5/1/2003"}
,{true,"BNDW","Bonneville Dam"        ,"WA",  80,45,38,52,-121,55,52,"4/13/2002"}
,{true,"BOII","Boise"                 ,"ID",2720,43,36, 1,-116,10,37,"7/31/1995"}
,{true,"BRKO","Brookings"             ,"OR",  80,42, 1,48,-124,14,27,"9/28/1999"}
,{true,"CEDC","Cedarville"            ,"CA",4600,41,35, 7,-120,10,17,"4/24/1985"}
,{true,"CHVO","Christmas Valley"      ,"OR",4305,43,14,29,-120,43,41,"4/22/1985"}
,{true,"CJDW","Chief Joseph Dam"      ,"WA", 990,47,59,27,-119,38, 8,"4/16/2002"}
,{true,"COVM","Corvallis"             ,"MT",3597,46,20, 0,-114, 5, 0,"4/27/1984"}
,{true,"CRSM","Creston"               ,"MT",2950,48,11,15,-114, 7,40,"5/4/1988"}
,{true,"CRVO","Corvallis"             ,"OR", 230,44,38, 3,-123,11,24,"2/27/1990"}
,{true,"DEFO","Dee Flat"              ,"OR",1150,45,35,11,-121,38,26,"2/21/1990"}
,{true,"DENI","Dworshak-Dent Acres"   ,"ID",1660,46,37,24,-116,13,14,"4/20/2002"}
,{true,"DRLM","Deer Lodge"            ,"MT",4680,46,20, 8,-112,46, 0,"6/4/1998"}
,{true,"DTRO","Detroit Lake"          ,"OR",1675,44,43,48,-122,10,45,"9/26/2002"}
,{true,"ECHO","Echo"                  ,"OR", 760,45,43, 7,-119,18,40,"3/24/1988"}
,{true,"EURN","Eureka"                ,"NV",5897,39,41, 7,-115,58,43,"8/8/2001"}
,{true,"FAFI","Fairfield"             ,"ID",5038,43,18,30,-114,49,30,"6/25/1987"}
,{true,"FALN","Fallon"                ,"NV",3965,39,27,29,-118,46,37,"3/27/2001"}
,{true,"FOGO","Forest Grove"          ,"OR", 180,45,33,11,-123, 5, 1,"8/29/1991"}
,{true,"FTHI","Fort Hall"             ,"ID",4445,43, 4,17,-112,25,52,"4/2/1993"}
,{true,"GCDW","Grand Coulee Dam"      ,"WA",1320,47,56,43,-118,57,13,"4/17/2002"}
,{true,"GDVI","Grand View"            ,"ID",2580,42,54,45,-116, 3,22,"2/10/1993"}
,{true,"GERW","George"                ,"WA",1150,47, 2,38,-119,38,32,"5/15/1986"}
,{true,"GFRI","Glenns Ferry"          ,"ID",3025,42,52, 0,-115,21,25,"4/13/1993"}
,{true,"GOLW","Goldendale"            ,"WA",1680,45,48,43,-120,49,28,"11/27/1991"}
,{true,"HCKO","Hills Creek Dam"       ,"OR",1560,43,42,35,-122,25,17,"9/24/2002"}
,{true,"HERO","Hermiston"             ,"OR", 550,45,49,16,-119,31,17,"5/17/1983"}
,{true,"HOXO","Hood River"            ,"OR", 510,45,41, 4,-121,31, 5,"5/19/1987"}
,{true,"HRFO","Hereford"              ,"OR",3600,44,29,17,-118, 1,12,"4/29/1998"}
,{true,"HRHW","Harrah"                ,"WA", 850,46,23, 5,-120,34,28,"5/27/1987"}
,{true,"HRMO","Hermiston (Harec)"     ,"OR", 607,45,49,10,-119,17, 0,"7/15/1993"}
,{true,"IMBO","Imbler"                ,"OR",2750,45,26, 0,-117,58, 0,"4/5/1994"}
,{true,"KFLO","Klamath Falls"         ,"OR",4100,42, 9,53,-121,45,18,"3/31/1999"}
,{true,"KFLW","Kettle Falls"          ,"WA",1340,48,35,42,-118, 7,27,"4/18/2002"}
,{true,"KTBI","Kettle Butte"          ,"ID",5135,43,32,55,-112,19,33,"10/1/1996"}
,{true,"LAKO","Lakeview"              ,"OR",4770,42, 7,20,-120,31,23,"4/19/1988"}
,{true,"LBRW","Lake Bryan-Rice Bar"   ,"WA", 630,46,41,51,-117,39,15,"4/19/2002"}
,{true,"LEGW","Legrow"                ,"WA", 580,46,12,19,-118,56,10,"7/17/1986"}
,{true,"LIDW","Lind"                  ,"WA",1475,46,52, 2,-118,44,22,"5/18/1983"}
,{true,"LKPO","Lookout Point Dam"     ,"OR", 940,43,54,56,-122,45, 8,"9/24/2002"}
,{true,"LORO","Lorella"               ,"OR",4160,42, 4,40,-121,13,27,"3/31/2001"}
,{true,"MALI","Malta"                 ,"ID",4410,42,26,15,-113,24,50,"6/2/1983"}
,{true,"MASW","Manson"                ,"WA",1972,47,55, 1,-120, 7,28,"11/9/1993"}
,{true,"MDFO","Medford"               ,"OR",1340,42,19,52,-122,56,16,"5/23/1989"}
,{true,"MNTI","Monteview"             ,"ID",4855,44, 0,54,-112,32, 9,"10/1/1996"}
,{true,"MRSO","Madras"                ,"OR",2440,44,40,48,-121, 8,55,"5/2/1984"}
,{true,"NMPI","Nampa"                 ,"ID",2634,43,26,30,-116,38,13,"3/11/1996"}
,{true,"ODSW","Odessa"                ,"WA",1650,47,18,32,-118,52,43,"4/24/1984"}
,{true,"OMAW","Omak"                  ,"WA",1235,48,24, 9,-119,34,34,"1/25/1989"}
,{true,"ONTO","Ontario"               ,"OR",2260,43,58,40,-117, 0,55,"4/30/1992"}
,{true,"PARO","Parkdale"              ,"OR",1480,45,32,40,-121,37, 0,"10/20/1989"}
,{true,"PCYO","Prairie City"          ,"OR",3752,44,26,27,-118,37,40,"4/12/1989"}
,{true,"PICI","Picabo"                ,"ID",4900,43,18,42,-114, 9,57,"4/21/1993"}
,{true,"PMAI","Parma"                 ,"ID",2305,43,48, 0,-116,56, 0,"3/28/1986"}
,{true,"PNGO","Pinegrove"             ,"OR", 620,45,39, 8,-121,30,33,"10/20/1989"}
,{true,"POBO","Powell Butte"          ,"OR",3200,44,14,54,-120,56,59,"9/21/1993"}
,{true,"RDBM","Roundbutte"            ,"MT",3040,47,32,22,-114,16,50,"5/23/1989"}
,{true,"RPTI","Rupert"                ,"ID",4155,42,35,42,-113,50,17,"3/9/1988"}
,{true,"RXGI","Rexburg"               ,"ID",4875,43,51, 0,-111,46, 0,"6/3/1987"}
,{true,"SBMW","Seven Bays Marina"     ,"WA",1370,47,51,19,-118,20,28,"4/17/2002"}
,{true,"SIGM","St. Ignatius"          ,"MT",2990,47,18,48,-114, 5,53,"3/28/1991"}
,{true,"SILW","Silcott Island"        ,"WA", 825,46,25, 7,-117,11, 5,"7/17/2002"}
,{true,"TWFI","Twin Falls (Kimberly)" ,"ID",3920,42,32,46,-114,20,43,"5/4/1990"}
,{true,"WRDO","Worden"                ,"OR",4080,42, 1, 1,-121,47,13,"4/19/2000"}
,{false, 0    ,0                       ,0   ,0   ,0 , 0, 0,0  , 0, 0,0}
};
//______________________________________________________________________________
Geolocation *render_AgriMet_geolocation(const char *station_ID)
{  Geolocation *AgriMet_loc = 0; // relinquished to caller
   for (int i = 0; AgriMet_geolocation[i].station_ID && !AgriMet_loc;i++)
   {  if (stricmp(AgriMet_geolocation[i].station_ID,station_ID) == 0)
      {  AgriMet_loc = new Geolocation;
         AgriMet_loc->set_latitude_DMS (AgriMet_geolocation[i].latitude_deg  ,AgriMet_geolocation[i].latitude_min  ,AgriMet_geolocation[i].latitude_sec);
         AgriMet_loc->set_longitude_DMS(AgriMet_geolocation[i].longitude_deg ,AgriMet_geolocation[i].longitude_min ,AgriMet_geolocation[i].longitude_sec);
//100117         AgriMet_loc->set_elevation_meter            (foot_to_m(AgriMet_geolocation[i].elevation_ft));
         AgriMet_loc->set_elevation_feet            (AgriMet_geolocation[i].elevation_ft);
         AgriMet_loc->set_country_code_ISO3166         (840); // USA
               // Use ISO 3166 codes
         uint16 state_FIPS_number = lookup_USA_state_FIPS_number(AgriMet_geolocation[i].state_FIPS_code);
         AgriMet_loc->set_state_code           (state_FIPS_number);
         //No county info         AgriMet_loc->set_county_code(0)
//no Station Number for AgriMet number for thi
//         AgriMet_loc->set_station_number       (0);
         AgriMet_loc->set_station_ID_code      (AgriMet_geolocation[i].station_ID);
         AgriMet_loc->set_country_name         ("USA");
         AgriMet_loc->set_state_name           (USA_state_FIPS[state_FIPS_number].name);
         //No county info AgriMet_loc->set_county_name ();
         AgriMet_loc->set_station_name(AgriMet_geolocation[i].station_name);
      };
   };
   return AgriMet_loc;
};
//______________________________________________________________________________
