#include "common/weather/stations/PAWS_stations.h"
#include "corn/string/strconv.hpp"
#include <stdlib.h>
   // stdlib is for itoa
PAWS_Geolocation PAWS_geolocation[] =
{//Station               Latitude Longitude Elevation StartDate Location                                 State
 {true,650,"AHTANUM"                ,46.55 ,-120.71 ,1560 , "4/10/1998" ,"10 MI W of Union Gap"                   ,"Wa"}
,{true,660,"BASIN CITY"             ,46.64 ,-119.16 , 874 , "1/1/1989"  ,"3.9 MI N of Basin City"                 ,"Wa"}
,{true,671,"CARLSON"                ,46.14 ,-119.46 ,1426 , "3/15/1989" ,"8 MI S of Benton City"                  ,"Wa"}
,{true,822,"R. EBY"                 ,46.08 ,-119.08 ,1176 , "3/30/1989" ,"6 MI S of Finley"                       ,"Wa"}
,{true,651,"Alderdale"              ,45.85 ,-119.88 , 736 , "3/26/1999" ,"Alderdale Wa. "                         ,"Wa"}
,{true,665,"BENTON CITY"            ,46.26 ,-119.45 , 637 , "7/14/1995" ,"2.5 MI E of Benton City"                ,"Wa"}
,{true,673,"CBC-PASCO"              ,46.25 ,-119.12 , 339 , "6/21/1995" ,"On CBC Campus; Pasco"                   ,"Wa"}
,{true,690,"ELLENSBURG"             ,46.9  ,-120.41 ,1856 , "1/1/1989"  ,"8.2 MI SE of Ellensburg"                ,"Wa"}
,{true,700,"FISHHOOK"               ,46.29 ,-118.74 , 767 , "5/6/1992"  ,"2 MI S of Fishhook Park"                ,"Wa"}
,{true,702,"FOURMILE"               ,45.99 ,-119.33 , 576 , "3/19/1993" ,"3.5 MI N of Plymouth"                   ,"Wa"}
,{true,714,"GRAYLAND"               ,46.78 ,-124    ,   7 ,""           ,"5 MI S of Grayland"                     ,"Wa"}
,{true,721,"HORRIGAN"               ,46.07 ,-119.76 , 882 , "3/21/1989" ,"6.8 MI S of Prosser"                    ,"Wa"}
,{true,762,"LONG BEACH"             ,46.33 ,-124    ,  22 ,""           ,"5 MI NW of Long Beach"                  ,"Wa"}
,{true,775,"MCNARY"                 ,45.97 ,-119.25 , 717 , "5/11/1992" ,"5.5 MI NE of Plymouth"                  ,"Wa"}
,{true,781,"NACHES"                 ,46.72 ,-120.67 ,1373 , "4/2/1994"  ,"1 MI E of Naches"                       ,"Wa"}
,{true,802,"PATERSON"               ,45.93 ,-119.48 , 359 , "5/11/1990" ,"5 MI E of Paterson"                     ,"Wa"}
,{true,810,"QUINCY"                 ,47.22 ,-119.95 ,1427 , "1/1/1989"  ,"4 MI W of Quincy"                       ,"Wa"}
,{true,830,"SUNNYSIDE"              ,46.39 ,-119.99 , 876 , "1/1/1989"  ,"4.2 MI N of Sunnyside"                  ,"Wa"}
,{true,873,"WALLA WALLA"            ,46.08 ,-118.27 ,1186 , "7/21/1992" ,"1 MI E of Walla Walla"                  ,"Wa"}
,{true,720,"WSU-IAREC-HQ"           ,46.25 ,-119.74 , 842 , "1/1/1986"  ,"4 MI NE of Prosser"                     ,"Wa"}
,{true,820,"WSU-ROZA"               ,46.29 ,-119.73 ,1126 , "1/1/1989"  ,"7 MI NNE of Prosser"                    ,"Wa"}
,{true,772,"MATHEWS CNR."           ,46.42 ,-119.19 , 905 , "1/1/1989"  ,"2 MI S of Mathews Corner"               ,"Wa"}
,{true,773,"McWHORTER"              ,46.31 ,-119.61 ,1337 , "4/14/1989" ,"8 MI NW of Benton City"                 ,"Wa"}
,{true,793,"OROVILLE"               ,48.94 ,-119.41 , 912 , "4/13/1994" ,"0.75 MI E of Oroville"                  ,"Wa"}
,{true,805,"POGUE FLAT"             ,48.42 ,-119.55 ,1218 , "5/20/1994" ,"1.5 MI NW of Omak"                      ,"Wa"}
,{true,821,"ROYAL CITY"             ,46.91 ,-119.62 ,1078 , "1/1/1989"  ,"0.5 MI N of Royal City"                 ,"Wa"}
,{true,832,"SWITZLER"               ,45.99 ,-119.47 , 598 , "5/11/1992" ,"7 MI NE of Paterson"                    ,"Wa"}
,{true,870,"WAPATO"                 ,46.43 ,-120.5  , 849 , "1/1/1989"  ,"3.2 MI W of Wapato"                     ,"Wa"}
,{true,860,"WSU MT. VERNON"         ,48.43 ,-122.38 ,  10 ,"10/16/1991" ,"2.5 MI W of Mt Vernon"                  ,"Wa"}
,{true,843,"WSU TRI-CITIES"         ,46.32 ,-119.26 , 317 , "6/13/1995" ,"at WSU Tri-Cities Campus; Richland"     ,"Wa"}
,{true,664,"BADGER CANYON (Sleater)",46.17 ,-119.27 , 591 , "7/12/1995" ,"4.0 MI SW of Kennewick"                 ,"Wa"}
,{true,663,"BREWSTER"               ,48.07 ,-119.84 , 660 , "5/20/1994" ,"3.0 MI SW of Brewster"                  ,"Wa"}
,{true,672,"COLLEGE PLACE"          ,46.02 ,-118.39 , 691 , "4/27/1992" ,"1 MI S of College Place"                ,"Wa"}
,{true,693,"ELLISFORDE"             ,48.79 ,-119.39 , 892 , "4/14/1994" ,"0.5 MI N of Ellisforde"                 ,"Wa"}
,{true,713,"GLEED"                  ,46.68 ,-120.63 ,1476 , "5/19/1994" ,"1.5 MI NNW of Gleed"                    ,"Wa"}
,{true,750,"K2H"                    ,46.28 ,-118.64 ,1009 , "5/6/1992"  ,"2 MI S of Eureka"                       ,"Wa"}
,{true,770,"MATTAWA"                ,46.7  ,-119.79 , 781 , "1/1/1989"  ,"5.4 MI SE of Mattawa"                   ,"Wa"}
,{true,771,"MOSES LAKE"             ,47    ,-119.23 ,1084 , "1/1/1989"  ,"7 MI SE of Moses Lake"                  ,"Wa"}
,{false,794,"OUTLOOK"                ,46.42 ,-120.13 ,1300 , "3/12/1998" ,"5 Miles North of Outlook"               ,"Wa"}
,{true,800,"POMONA"                 ,46.69 ,-120.47 ,1360 , "1/1/1989"  ,"0.5 MI E of Pomona"                     ,"Wa"}
,{true,803,"PRIOR STATION 2"        ,45.96 ,-119.45 , 503 , "3/19/1993" ,"5 MI NW of Plymouth"                    ,"Wa"}
,{true,842,"TONASKET"               ,48.69 ,-119.45 , 862 , "4/14/1994" ,"1.0 MI S of Tonasket"                   ,"Wa"}
,{true,872,"WELLAND"                ,46.21 ,-118.73 , 926 , "5/6/1992"  ,"13 MI E of Burbank"                     ,"Wa"}
,{true,790,"OTHELLO"                ,46.79 ,-119.04 ,1154 , "1/1/1989"  ,"8 MI ESE of Othello"                    ,"Wa"}
,{true,841,"WSU TFREC"              ,47.43 ,-120.34 , 730 ,"10/6/1993"  ,"Tree Fr. Res. and Ext. Ctr.; Wenatchee" ,"Wa"}
,{true,662,"BAKER FLAT"             ,47.49 ,-120.29 , 599 ,"10/6/1993"  ,"4.0 MI N of Wenatchee"                  ,"Wa"}
,{true,661,"BUENA"                  ,46.43 ,-120.29 , 854 , "1/1/1989"  ,"1.6 MI N of Buena"                      ,"Wa"}
,{true,670,"COWICHE"                ,46.66 ,-120.71 ,1770 , "1/1/1989"  ,"0.5 MI W of Cowiche"                    ,"Wa"}
,{true,701,"FINLEY"                 ,46.13 ,-119.05 , 755 , "6/1/1992"  ,"1.5 MI S of Finley"                     ,"Wa"}
,{true,710,"GRAMLING"               ,46.12 ,-119.21 ,1267 , "3/30/1989" ,"7.5 MI S of Kennewick"                  ,"Wa"}
,{true,751,"KENNEWICK (Stewart)"    ,46.2  ,-119.19 , 429 , "7/11/1995" ,"Edison and 8th; Kennewick"              ,"Wa"}
,{true,691,"MCCLURE  (E. HAMILTON)" ,46.37 ,-119.72 ,2515 , "3/14/1989" ,"11.2 MI N of Prosser"                   ,"Wa"}
,{true,774,"MOXEE"                  ,46.56 ,-120.39 ,1036 , "9/1/1989"  ,"1.5 MI E of Moxee"                      ,"Wa"}
,{true,801,"PARKER"                 ,46.51 ,-120.47 , 876 , "1/1/1989"  ,"1 MI NW of Parker"                      ,"Wa"}
,{true,804,"PORT OF SUNNYSIDE"      ,46.28 ,-120    , 631 , "4/21/1993" ,"2.6 MI S of Sunnyside"                  ,"Wa"}
,{true,831,"STATION 4"              ,46.04 ,-119.41 ,1152 , "4/23/1992" ,"12 MI NE of Paterson"                   ,"Wa"}
,{true,840,"TOUCHET"                ,46.01 ,-118.67 , 492 , "1/1/1989"  ,"1.5 MI S of Touchet"                    ,"Wa"}
,{true,871,"WHEELHOUSE"             ,46.02 ,-119.52 , 828 , "4/23/1992" ,"6.7 MI NNE of Paterson"                 ,"Wa"}
,{true,806,"WSU PUYALLUP"           ,47.18 ,-122.32 , 200 , "5/31/1995" ,"at WSU WWREC; Puyallup"                 ,"Wa"}
,{false, 0,0                        , 0    ,   0    ,  0  , 0           ,0                                        ,0   }

/*
CARLSON               671
CBC PASCO             673
EBY                   822
HUNDRED CIRCLES       725
ECHO                  692
GEORGE                711
GOLDENDALE            712
HARRAH                722
HERMISTON             723
HOODRIVER             724
LEGROW                760
LIND                  761
ODESSA                791
OMAK                  792
*/
};
//______________________________________________________________________________
Geolocation *render_PAWS_geolocation(uint16 unit_ID)
{  Geolocation *paws_loc = 0;  // relinquished to caller
   for (int i = 0; PAWS_geolocation[i].unit_ID && ! paws_loc;i++)
   {  if (PAWS_geolocation[i].unit_ID == unit_ID)
      {  paws_loc =  new Geolocation;
         // Currently all PAWS stations are in Washington
         paws_loc->set_latitude_dec_deg_32  (PAWS_geolocation[i].latitude_dec_deg);
         paws_loc->set_longitude_dec_deg_32 (PAWS_geolocation[i].longitude_dec_deg);
         paws_loc->set_elevation_meter      (PAWS_geolocation[i].elevation_m);
         paws_loc->set_country_code_ISO3166         (840); // USA
               // Use ISO 3166 codes
         paws_loc->set_state_code           (53); // Washington
         //No county info         paws_loc->set_county_code(0)
         paws_loc->set_station_number       (PAWS_geolocation[i].unit_ID);
         char unit_ID_cstr[10];
         //140923 itoa
         CORN::nat16_to_cstr(PAWS_geolocation[i].unit_ID,unit_ID_cstr,10);

         paws_loc->set_station_ID_code      (unit_ID_cstr);
         paws_loc->set_country_name         ("USA");
         paws_loc->set_state_name           ("Washington");
         //No county info paws_loc->set_county_name ();
         paws_loc->set_station_name(PAWS_geolocation[i].station_name);
      };
   };
   return paws_loc;
};
//______________________________________________________________________________
