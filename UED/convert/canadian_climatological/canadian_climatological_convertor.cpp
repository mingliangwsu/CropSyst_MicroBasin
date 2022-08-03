#include <math.h>
#include <iostream.h>
#include "corn/std/std_iomanip.h"
#include "UED/convert/station_database.h"

#include "UED/convert/canadian_climatological/canadian_climatological_convertor.h"
#include "ued/std_codes.h"
#include "ued/ued.h"
#include "corn/measure/units.h"

#include "corn/string/uiostring.h"
#include "corn/math/statistical/stats.h"
#include "common/geolocation/geolocation.h"
#include "ued/locrec.h"

#include "corn/file_sys/filename.h"
namespace canadian_climatological_convertor_NS                                   //060616
{
//______________________________________________________________________________
struct Element_conversion
{
   nat16  element_number;
   UED_variable_code var_code;
            // In cases where there is no standard UED code,
            // a non-standard code will be created from the element number
            #define COMPOSE_NONSTANDARD 0

   UED_units_code    units_code;

   float32  normalization_factor;
            // Many element values are scaled to allow the value to be entered as an integer
            // Multiplying the raw record value by this factor will give the value in the prefered units
   char *description;
   char *relevent_flags; // These are the element flags that are relevent to records
   bool encountered_in_this_database;

} element_conversions[] =
{
//ELEM VARIABLE            UNITS                            Normalization            code           DESCRIPTION                      FLAGS
 {  0,UED_variableless                       ,UC_unitless                      , 1   ,                               0                                  ,0}
//DAILY CLIMATOLOGICAL DATA (DLY02,DLY04) - (NOTE 16)
,{  1,UED_STD_VC_max_temperature.get()       ,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Daily Maximum Temperature"         ,"E"}    //(DLY02,DLY04)
,{  2,UED_STD_VC_min_temperature.get()       ,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Daily Minimum Temperature"         ,"ENY"}  //(DLY02,DLY04)
,{  3,UED_STD_VC_avg_temperature.get()       ,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Daily Mean Temperature"            ,"E"}    //(DLY02,DLY04)
,{  4,UED_STD_VC_max_relative_humidity.get() ,UC_percent                       ,  1.0  ,/*  %                        */"Daily Max. Relative Humidity"      ,""}     //(DLY02,DLY04)
,{  5,UED_STD_VC_min_relative_humidity.get() ,UC_percent                       ,  1.0  ,/*  %                        */"Daily Min. Relative Humidity"      ,""}     //(DLY02,DLY04)
// 006-009                       (.....6 hrly. Precipitation ending) (.....See Note 15)
,{  6,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Precipitation ending: 1200 GMT"    ,"T"}    //(DLY02,DLY04)
,{  7,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Precipitation ending: 1800 GMT"    ,"T"}    //(DLY02,DLY04)
,{  8,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Precipitation ending: 0000 GMT"    ,"T"}    //(DLY02,DLY04)
,{  9,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Precipitation ending: 0600 GMT"    ,"T"}    //(DLY02,DLY04)
,{ 10,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Precipitation ending: Total Rainfall","ETCLAF"}      //(DLY02,DLY04)
,{ 11,COMPOSE_NONSTANDARD,UC_cm/*_depth*/                , 0.1 ,/*  0.1cm                    */"Precipitation ending: Total Snowfall","ETCLAF"}      //(DLY02,DLY04)
,{ 12,UED_STD_VC_precipitation.get()      ,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Precipitation ending: Total Precipitation","ETCLAF"} //(DLY02,DLY04)//(DLY21 (FISCHER/PORTER) DATA )
,{ 13,COMPOSE_NONSTANDARD,UC_cm/*_depth*/                ,  1  ,/*  whole cm                 */" Precipitation ending: Snow on the Ground","ET"}      //(DLY02,DLY04)(Note 8)
//014-022                       (....Day with ....See Note 14)
,{ 14,COMPOSE_NONSTANDARD,UC_unit                          ,  1  ,/*               1=Yes, 0=No */"Thunderstorms"                     ,""}             //(DLY02,DLY04)
,{ 15,COMPOSE_NONSTANDARD,UC_unit                          ,  1  ,/*               1=Yes, 0=No */"Freezing Rain"                     ,""}             //(DLY02,DLY04)
,{ 16,COMPOSE_NONSTANDARD,UC_unit                          ,  1  ,/*               1=Yes, 0=No */"Hail"                              ,""}             //(DLY02,DLY04)
,{ 17,COMPOSE_NONSTANDARD,UC_unit                          ,  1  ,/*               1=Yes, 0=No */"Fog or Ice Fog"                    ,""}             //(DLY02,DLY04)
,{ 18,COMPOSE_NONSTANDARD,UC_unit                          ,  1  ,/*               1=Yes, 0=No */"Smoke or Haze"                     ,""}             //(DLY02,DLY04)
,{ 19,COMPOSE_NONSTANDARD,UC_unit                          ,  1  ,/*               1=Yes, 0=No */"Blowing Dust or Sand"              ,""}             //(DLY02,DLY04)
,{ 20,COMPOSE_NONSTANDARD,UC_unit                          ,  1  ,/*               1=Yes, 0=No */"Blowing Snow"                      ,""}             //(DLY02,DLY04)
,{ 21,COMPOSE_NONSTANDARD,UC_unit                          ,  1  ,/*               1=Yes, 0=No */"Wind Speed >= 28 Knots"            ,""}             //(DLY02,DLY04)
,{ 22,COMPOSE_NONSTANDARD,UC_unit                          ,  1  ,/*               1=Yes, 0=No */"Wind Speed >= 34 Knots"            ,""}             //(DLY02,DLY04)
,{ 23,COMPOSE_NONSTANDARD,UC_degree_from_north       , 10  ,/*  10's of deg              */"Direction of Extreme Gust (16 pts)","SE"} //used to Dec. 1976 (Note 5) (See 157) //(DLY02,DLY04)
,{ 24,COMPOSE_NONSTANDARD,UC_kilometers_per_hour    ,  1  ,/*  km                       */"Speed of Extreme Gust (Earliest)"  ,"SE"}                                    //(DLY02,DLY04)
,{ 25,COMPOSE_NONSTANDARD,0,0,0,0} // Not defined
//MONTHLY CLIMATOLOGICAL DATA (MLY04) - (NOTE 16)
//ELEM UNITS        CODE        DESCRIPTION                        FLAGS
//026-038                       (.....Number of Days With.....)
,{ 26,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Frost"                             ,""}        //(MLY04)
,{ 27,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Thunderstorms"                     ,""}        //(MLY04)
,{ 28,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Rain or Drizzle"                   ,""}        //(MLY04)
,{ 29,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Freezing Rain or Drizzle"          ,""}        //(MLY04)
,{ 30,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Hail"                              ,""}        //(MLY04)
,{ 31,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Snow"                              ,""}        //(MLY04)
,{ 32,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Measurable Precipitation"          ,""}        //(MLY04)
,{ 33,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Fog or Ice Fog"                    ,""}        //(MLY04)
,{ 34,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Smoke or Haze"                     ,""}        //(MLY04)
,{ 35,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Blowing Dust or Sand"              ,""}        //(MLY04)
,{ 36,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Blowing Snow"                      ,""}        //(MLY04)
,{ 37,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Wind Speed >= 28 Knots"            ,""}        //(MLY04)
,{ 38,COMPOSE_NONSTANDARD,UT_day                      ,  1  ,/*                           */"Wind >= 34 Knots"                  ,""}        //(MLY04)
,{ 39,COMPOSE_NONSTANDARD,UC_cm/*_depth*/                ,  1  ,/*  whole cm                 */"Snow Cover - Last Day of Month"    ,"ET"}      //(MLY04)
,{ 40,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Mean Maximum Temperature"          ,"E"}       //(MLY04)
,{ 41,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Mean Minimum Temperature"          ,"E"}       //(MLY04)
,{ 42,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Mean Monthly Temperature"          ,"E"}       //(MLY04)
,{ 43,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Mean Monthly Temperature Difference from Normal","E"}//(MLY04)(Note 18)
,{ 44,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Extreme Maximum Temperature"       ,"ESB"}           //(MLY04)
,{ 45,COMPOSE_NONSTANDARD,0 /*Dont know: day of year?*/     ,  1  ,/*                           */"Date of Extreme Maximum Temperature (Earliest)",""}  //(MLY04)
,{ 46,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Extreme Minimum Temperature"       ,"ESB"}           //(MLY04)
,{ 47,COMPOSE_NONSTANDARD,0 /*Dont know: day of year?*/     ,  1  ,/*                           */"Date of Extreme Minimum Temperature (Earliest)",""}  //(MLY04)
,{ 48,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Total Rainfall"                    ,"ET"}            //(MLY04)
,{ 49,COMPOSE_NONSTANDARD,UC_cm/*_depth*/                , 0.1 ,/*  0.1cm                    */"Total Snowfall"                    ,"ET"}            //(MLY04)
,{ 50,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Total Precipitation"               ,"ET"}            //(MLY04)
,{ 51,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Total Precipitation (diff. from norm.)","ET"}        //(MLY04)(Note 18)
,{ 52,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Greatest Rainfall"                 ,"ETSB"}    //(MLY04)
,{ 53,COMPOSE_NONSTANDARD,0 /*Dont know: day of year?*/     ,  1  ,/*                           */"Date of Greatest Rainfall (Earliest)",""}      //(MLY04)
,{ 54,COMPOSE_NONSTANDARD,UC_cm/*_depth*/                , 0.1 ,/*  0.1cm                    */"Greatest Snowfall"                 ,"ETSB"}    //(MLY04)
,{ 55,COMPOSE_NONSTANDARD,0 /*Dont know: day of year?*/     ,  1  ,/*                           */"Date of Greatest Snowfall (Earliest)",""}      //(MLY04)
//MONTHLY CLIMATOLOGICAL DATA (MLY04) - (NOTE 16)
//ELEM UNITS        CODE        DESCRIPTION                        FLAGS
,{ 56,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Greatest Precipitation"            ,"ETSB"}    //(MLY04)
,{ 57,COMPOSE_NONSTANDARD,0,0,0,0} // Not defined
,{ 58,COMPOSE_NONSTANDARD,UC_degree_from_north       , 10  ,/*  10's of deg              */"Direction of Extreme Gust (16 pts)","ESB"}     //(MLY04)to Dec. 1976 (Note 9)
,{ 59,COMPOSE_NONSTANDARD,UC_kilometers_per_hour    ,  1  ,/*  km/hr                    */"Speed of Extreme Gust"             ,"ESB"}     //(MLY04)(Note 9)
,{ 60,COMPOSE_NONSTANDARD,0 /*Dont know: day of year?*/     ,  1  ,/*                           */"Date of Extreme Gust (Earliest)"   ,"ESB"}     //(MLY04)(Note 9)
//SOLAR RADIATION (HLY11)
//ELEM       UNITS        CODE        DESCRIPTION                        FLAGS
,{  61,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*    .001 MJ/m^2       *RF1 */"Global Solar Radiation"  ,"DUVWXYZ"} //(HLY11)
,{  62,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*         "            *RF2 */"Sky (diffuse) Rad."      ,""}        //(HLY11)
,{  63,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*         "            *RF3 */"Reflected Solar Rad."    ,""}        //(HLY11)
,{  64,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*         "             RF4 */"Net All Wave Rad."       ,""}        //(HLY11)
,{  65,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*         "            *RF5 */"Total Downward Rad."     ,""}        //(HLY11)
,{  66,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*         "            *RF6 */"Total Upward Rad."       ,""}        //(HLY11)
,{  67,COMPOSE_NONSTANDARD,UC_kilo_lux               ,0.01 ,/*    .01 Kilolux_hrs   *RF7 */"Daylight Illumination"   ,""}        //(HLY11)
,{  68,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*    .001 MJ/m^2       *RF8 */"Direct Solar Rad."       ,""}        //(HLY11)
//WIND (HLY15)
//ELEM UNITS        CODE        DESCRIPTION                         FLAGS
,{ 69,COMPOSE_NONSTANDARD,UC_degree_from_north       , 10  ,/*  10's of deg              */"Wind Direction - 45B Anemometer (8 pts)","E"}  //(HLY15)(Note 11, 17)
,{ 70,COMPOSE_NONSTANDARD,UC_kilometers_per_hour    ,  1  ,/*  km/hr                    */"Wind Run Per Hour - 45B Anemometer"     ,"E"}  //(HLY15)(Note 17)
//HOURLY WEATHER (HLY01)
,{ 71,COMPOSE_NONSTANDARD,UC_m/*_height*/                , 30  ,/*  30's of metres           */"Ceiling"                        ,""}//(HLY01) (Note 6)
,{ 72,COMPOSE_NONSTANDARD,UC_m/*meter_distance*/          , 0.1 ,/*  0.1 km                   */"Visibility"                     ,""}//(HLY01) (Note 7)
,{ 73,COMPOSE_NONSTANDARD,UC_kPa/*UC_kilo_pascal_atmospheric_pressure*/, 0.01,/*0.01 kilopascals   */"Sea Level Pressure"             ,""}//(HLY01)
,{ 74,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Dew Point Temperature"          ,""}//(HLY01)
,{ 75,COMPOSE_NONSTANDARD,UC_degree_from_north       , 10  ,/*  10's of deg              */"Wind Direction - U2A (16 pts)"  ,""}//to Dec. 1970 (Note 5, 17) (see 156) //(HLY01)
,{ 76,UED_STD_VC_wind_speed.get(),UC_kilometers_per_hour     ,  1  ,/*  km/hr                    */"Wind Speed - U2A Anemometer"            ,"E"}  //(HLY15)(HLY01) (Note 17)
,{ 77,COMPOSE_NONSTANDARD,UC_kPa/*UC_kilo_pascal_atmospheric_pressure*/, 0.01,/*.01 Kilopascals    */"Station Pressure"               ,""}//(HLY01)
,{ 78,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Dry Bulb Temperature"           ,""}//(HLY01)
,{ 79,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Wet Bulb Temperature"           ,""}//(HLY01)
,{ 80,COMPOSE_NONSTANDARD,UC_percent                       ,  1  ,/*  %                        */"Relative Humidity (mean?)"              ,""}//(HLY01)
,{ 81,COMPOSE_NONSTANDARD,0/*dont know what this is*/       , 10  ,/*  tenths  (of what?)       */"Total Cloud Opacity"            ,""}//(HLY01)
,{ 82,COMPOSE_NONSTANDARD,0/*dont know what this is*/       , 10  ,/*  tenths  (of what?)       */"Total Cloud Amount"             ,""}//(HLY01)
,{ 83,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*           1=Yes, 0=No     */"Weather Indicator"              ,""}//(HLY01)(Note 1)
,{ 84,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1, 2, 3    */"Tornado"                        ,""}//=1 (TOR), Waterspout=2 Funnel Cloud=3 (Note 2)  //(HLY01)
,{ 85,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               2, 3        */"Thunderstorms"                  ,""}// 2=(T) Normal,  3=(T+) Heavy  (Note 2)   //(HLY01)
//086-098                         (.....See Notes 2,3........)
,{ 86,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Rain (R)"                        ,""}//(HLY01)
,{ 87,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Rain Showers (RW)"               ,""}//(HLY01)
,{ 88,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Drizzle (L)"                     ,""}//(HLY01)
,{ 89,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Freezing Rain (ZR)"              ,""}//(HLY01)
,{ 90,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Freezing Drizzle (ZL)"           ,""}//(HLY01)
,{ 91,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Snow (S)"                        ,""}//(HLY01)
,{ 92,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Snow Grains (SG)"                ,""}//(HLY01)
,{ 93,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1          */"Ice Crystals (IC)"               ,""}//(HLY01)
,{ 94,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Ice Pellets (IP)"                ,""}//(HLY01)
,{ 95,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Ice Pellet Showers (IPW)"        ,""}//(HLY01)
,{ 96,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Snow Showers (SW)"               ,""}//(HLY01)
,{ 97,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Snow Pellets (SP)"               ,""}//(HLY01)
,{ 98,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               1-3         */"Hail (A)"                        ,""}//(HLY01)
//099-106,260                   (.....See Note 2......)
,{ 99,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1          */"Fog (F)"                         ,""}//(HLY01)
,{100,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1          */"Ice Fog (IF)"                    ,""}//(HLY01)(Note 23)
,{101,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1          */"Smoke (K)"                      ,""}//(HLY01)
,{102,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1          */"Haze (H)"                       ,""}//(HLY01)
,{103,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1          */"Blowing Snow (BS)"              ,""}//(HLY01)
,{104,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1          */"Blowing Sand (BN)"              ,""}//(HLY01)
,{105,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1          */"Blowing Dust (BD)"              ,""}//(HLY01)
,{106,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*                1          */"Dust (D)"                       ,""}//(HLY01)
//HOURLY WEATHER (HLY01)
//ELEM   UNITS       CODE            DESCRIPTION                   FLAGS
//107-110                       (.....Lowest Cloud Layer.....)
,{107,COMPOSE_NONSTANDARD,0/*dont know what this is*/       ,  10 ,/*  tenths  ?                */"Cloud layer 1: Opacity"            ,"G"} //(HLY01)(Note 12, 10)
,{108,COMPOSE_NONSTANDARD,0/*dont know what this is*/       ,  10 ,/*  tenths  ?                */"Cloud layer 1: Amount or Condition","G"} //(HLY01)(Notes 12, 13, 19)
,{109,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               0-16        */"Cloud layer 1: Type"               ,"G"} //(HLY01) (Notes 4, 12, 19)
,{110,COMPOSE_NONSTANDARD,UC_m/*_height*/                ,  30 ,/*  30's of meters           */"Cloud layer 1: Height"             ,"G"} //(HLY01)(Notes 12, 19)
//111-114                       (......Second Cloud Layer.....)
,{111,COMPOSE_NONSTANDARD,0/*dont know what this is*/       ,  10 ,/*  tenths  ?                */"Cloud layer 2: Opacity"            ,"G"} //(HLY01)(Notes 12, 19)
,{112,COMPOSE_NONSTANDARD,0/*dont know what this is*/       ,  10 ,/*  tenths  ?                */"Cloud layer 2: Amount or Condition","G"} //(HLY01)(Notes 12, 13, 19)
,{113,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               0-16        */"Cloud layer 2: Type"               ,"G"} //(HLY01)(Notes 4, 12, 19)
,{114,COMPOSE_NONSTANDARD,UC_m/*_height*/                ,  30 ,/*  30's of meters           */"Cloud layer 2: Height"             ,"G"} //(HLY01)(Notes 12, 19)
//115-118                       (....Third Cloud Layer....)
,{115,COMPOSE_NONSTANDARD,0/*dont know what this is*/       ,  10 ,/*  tenths  ?                */"Cloud layer 3: Opacity"            ,"G"} //(HLY01)(Notes 12, 19)
,{116,COMPOSE_NONSTANDARD,0/*dont know what this is*/       ,  10 ,/*  tenths  ?                */"Cloud layer 3: Amount or Condition","G"} //(HLY01)(Notes 12, 13, 19)
,{117,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               0-16        */"Cloud layer 3: Type"               ,"G"} //(HLY01)(Notes 4, 12, 19)
,{118,COMPOSE_NONSTANDARD,UC_m/*_height*/                ,  30 ,/*  30's of meters           */"Cloud layer 3: Height"             ,"G"} //(HLY01)(Note 12, 19)
//119-223                       (.....Fourth Cloud Layer.....)
,{119,COMPOSE_NONSTANDARD,0/*dont know what this is*/       ,  10 ,/*  tenths  ?                */"Cloud layer 4: Opacity"            ,"G"} //(HLY01)(Notes 12, 19)
,{120,COMPOSE_NONSTANDARD,0/*dont know what this is*/       ,  10 ,/*  tenths  ?                */"Cloud layer 4: Amount or Condition","G"} //(HLY01)(Notes 12, 13, 19)
,{121,COMPOSE_NONSTANDARD,UC_code                          ,  1  ,/*               0-16        */"Cloud layer 4: Type"               ,"G"} //(HLY01)(Notes 4, 12, 19)
,{122,COMPOSE_NONSTANDARD,UC_m/*_height*/                ,  30 ,/*  30's of meters           */"Cloud layer 4: Height"             ,"G"} //(HLY01)(Notes 12, 19)
//RATE OF RAINFALL
//ELEM UNITS       CODE          DESCRIPTION                     FLAGS
,{123,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Rainfall rate Hourly"             ,"HIJ"} //(HLY03)((FISCHER/PORTER) DATA  HLY21)
//RATE OF RAINFALL (DLY03) (SEE ALSO DLY21)
//ELEM UNITS        CODE        DESCRIPTION                      FLAGS
,{124,COMPOSE_NONSTANDARD,UC_adjustment                    , 0.01,/*  0.01                     */"Rainfall rate Adjustment Factor"   ,""}  //(DLY03)(Note 20)
// 125-132           (Since Last Chart Change, Greatest Amount of Precipitation in......)
,{125,UED_STD_VC_precipitation.get()         ,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Rainfall rate 5 Minutes"           ,"HIJ"}  //(DLY03)
,{126,UED_STD_VC_precipitation.get()         ,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Rainfall rate 10 Minutes"          ,"HIJ"}  //(DLY03)
,{127,UED_STD_VC_precipitation.get()         ,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Rainfall rate 15 Minutes"          ,"HIJ"}  //(DLY03)
,{128,UED_STD_VC_precipitation.get()         ,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Rainfall rate 30 Minutes"          ,"HIJ"}  //(DLY03)
,{129,UED_STD_VC_precipitation.get()         ,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Rainfall rate 1 Hours"             ,"HIJ"}  //(DLY03)
,{130,UED_STD_VC_precipitation.get()         ,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Rainfall rate 2 Hours"             ,"HIJ"}  //(DLY03)
,{131,UED_STD_VC_precipitation.get()         ,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Rainfall rate 6 Hours"             ,"HIJ"}  //(DLY03)
,{132,UED_STD_VC_precipitation.get()         ,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Rainfall rate 12 Hours"            ,"HIJ"}  //(DLY03)
  ///PRECIPITATION (FISCHER/PORTER) DATA (DLY21)
///ELEM UNITS        CODE        DESCRIPTION                         FLAGS
//,{127,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                  */"Greatest Amount of Precipitation 15 Minutes" ,"HIJ"}    //(DLY21)
//,{128,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                  */"Greatest Amount of Precipitation 30 Minutes" ,"HIJ"}    //(DLY21)
//,{129,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                  */"Greatest Amount of Precipitation 1 Hour"     ,"HIJ"}    //(DLY21)
//,{130,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                  */"Greatest Amount of Precipitation 2 Hours"    ,"HIJ"}    //(DLY21)
//,{131,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                  */"Greatest Amount of Precipitation 6 Hours"    ,"HIJ"}    //(DLY21)
//,{132,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                  */"Greatest Amount of Precipitation 12 Hours"   ,"HIJ"}    //(DLY21)
//BRIGHT SUNSHINE (HLY10)
//ELEM UNITS        CODE        DESCRIPTION                        FLAGS
,{133,COMPOSE_NONSTANDARD,UT_hour                     , 0.1 ,/*  0.1 hrs                  */"Sunshine"                          ,"E"}       //(HLY10)(Note 21)
//SOIL TEMPERATURE (DLY12)
//ELEM UNITS        CODE        DESCRIPTION                         FLAGS
//134-141                       (......AM Soil Temperatures at.....)
,{134,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 1 cm"             ,""} //(DLY12)(Note 10)
,{135,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 5 cm"             ,""}       //(DLY12)
,{136,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 10 cm"            ,""}       //(DLY12)
,{137,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 20 cm"            ,""}       //(DLY12)
,{138,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 50 cm"            ,""}        //(DLY12)
,{139,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 100 cm"           ,""}       //(DLY12)
,{140,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 150 cm"           ,""}       //(DLY12)
,{141,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 300 cm"           ,""}       //(DLY12)
,{142,COMPOSE_NONSTANDARD,UC_cm/*_depth*/                ,  1  ,/*  whole cm                 */"Soil temperature AM Snow Depth"    ,""}       //(DLY12)
//143-149                       (.....PM Soil Temperatures at......)
,{143,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 1 cm"             ,""} //(DLY12)(Note 10)
,{144,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 5 cm"             ,""}       //(DLY12)
,{145,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 10 cm"            ,""}       //(DLY12)
,{146,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 20 cm"            ,""}       //(DLY12)
,{147,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 50 cm"            ,""} //(DLY12)(Note 10)
,{148,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 100 cm"           ,""} //(DLY12)(Note 10)
,{149,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Soil temperature 150 cm"           ,""} //(DLY12)(Note 10)
,{150,COMPOSE_NONSTANDARD,UC_cm/*_depth*/                ,  1  ,/*  whole cm                 */"Soil temperature PM Snow Depth"    ,""} //(DLY12)(Note 10)
//PAN EVAPORATION (DLY13)
//ELEM UNITS        CODE        DESCRIPTION                         FLAGS
,{151,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Pan Evaporation"                   ,"E"}   //(DLY13)
,{152,COMPOSE_NONSTANDARD,UC_kilometers_per_day/*?*/ ,  1  ,/*  km                       */"Wind Mileage (evaporation)"        ,"E"}   //(DLY13)
,{153,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Water Temperature (evaporation)"   ,"E"}   //(DLY13)
,{154,COMPOSE_NONSTANDARD,UC_celcius                 , 0.1 ,/*  0.1 deg C                */"Air Temperature   (evaporation)"   ,"E"}   //(DLY13)
,{155,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Lake Evaporation"                  ,"E"}   //(DLY13)
//HOURLY WEATHER (HLY01)
//ELEM   UNITS       CODE            DESCRIPTION                   FLAGS
,{156,COMPOSE_NONSTANDARD,UC_degree_from_north       , 10  ,/*  10's of deg              */"Wind Direction - U2A Anemometer(36 pts)"  ,""}//from Jan. 1971 (Note 17) (see 075) //(HLY01)(HLY15)
//DAILY CLIMATOLOGICAL DATA (DLY02,DLY04) - (NOTE 16)
//ELEM UNITS        CODE        DESCRIPTION                      FLAGS
,{157,COMPOSE_NONSTANDARD,UC_degree_from_north       , 10  ,/*  10's of deg              */"Direction of Extreme Gust (36 pts)","SE"} //used from Jan. 1977 (see 023)        //(DLY02,DLY04)
//MONTHLY CLIMATOLOGICAL DATA (MLY04) - (NOTE 16)
//ELEM UNITS        CODE        DESCRIPTION                        FLAGS
,{158,COMPOSE_NONSTANDARD,UC_degree_from_north       , 10  ,/*  10's of deg              */"Direction of Extreme Gust (36 pts)","ESB"}     //(MLY04)from Jan. 1977
//PRECIPITATION (FISCHER/PORTER) DATA (FIF21)
//ELEM UNITS        CODE        DESCRIPTION                         FLAGS
,{159,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Precipitation"            ,"AKL"}   //(FIF21)
//HOURLY WEATHER (HLY01)
//ELEM   UNITS       CODE            DESCRIPTION                   FLAGS
,{160,COMPOSE_NONSTANDARD,0 /*don't know what this is*/     ,  1  ,/*                           */"Rainfall rate Chart Change Hour (Local Standard Time)",""}//(DLY03)
,{161,COMPOSE_NONSTANDARD,UC_mm/*_depth*/                , 0.1 ,/*  0.1mm                    */"Greatest Amount of Precipitation 24 Hours"   ,"HIJ"}    //(DLY21)
,{162,0,0,0,0,0}
,{163,0,0,0,0}
,{164,0,0,0,0,0}
,{165,0,0,0,0,0}
,{166,0,0,0,0,0}
,{167,0,0,0,0,0}
,{168,0,0,0,0,0}
//SOLAR RADIATION (HLY11)
//ELEM       UNITS        CODE        DESCRIPTION                        FLAGS
,{ 169,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*         "             RF9 */"Incident Longwave Rad. (shaded)",""} //(HLY11)(note 22)
,{ 170,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*         "             RFB */"Emitted Longwave Rad."   ,""}        //(HLY11)(note 22)
,{ 171,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*         "            *RFC */"Incident Solar Rad. -green",""}      //(HLY11)(note 22)
,{ 172,COMPOSE_NONSTANDARD,UC_MJ_m2_solar_radiation  ,0.001,/*         "            *RFD */"Incident Solar Rad. -red",""}        //(HLY11)(note 22)
//HOURLY WEATHER (HLY01)
//ELEM   UNITS       CODE            DESCRIPTION                   FLAGS
// NYI,{260,COMPOSE_NONSTANDARD,UC_code                    ,  1  ,/*                1          */"Freezing Fog(FZFG)"             ,""}//(HLY01)(Note 23)
//PRECIPITATION (FISCHER/PORTER) DATA (DLY21)
//ELEM UNITS        CODE        DESCRIPTION                         FLAGS
,{0,0,0,0,0,0}
};
//______________________________________________________________________________
struct Flag_conversion
{
   char                    flag;
   CORN::Quality_code  quality;
} flag_conversion [] =
{
 {    ' ',UED_measured     }
,{    'A',UED_measured     } //Accumulated amount; previous value      010, 011, 012, 159
                 //C or L for elements 010, 011, 012
                 //K or L for elements 159
,{    'B',UED_estimated     } //More than one occurrence & estimated    044, 046, 052, 054,
                 //                                     056, 058, 059
,{    'C',CORN::missing_quality     } //Precipitation occurred, amount          010, 011, 012
                 //uncertain; value is 0
,{    'D',UED_generated     } //Derived                                 061-068
,{    'E',UED_estimated     } //Estimated                               all except 061-068
,{    'F',UED_estimated     } //Accumulated and estimated               010, 011, 012
,{    'G',UED_measured     } //Uncorrected                             107-122
,{    'H',UED_measured     } //Freezing                                123, 125-132
,{    'I',UED_measured     } //Unadjusted                              123, 125-132
,{    'J',UED_measured     } //Freezing and unadjusted                 123, 125-132
,{    'K',CORN::missing_quality     } //First occurrence when precip. may       159
                 //or may not have occurred;
                 //value is 0.
,{    'L',CORN::missing_quality     } //Precipitation may or may not have       010, 011, 012, 159
                 //occurred; value is 0
,{    'M',CORN::missing_quality     } //Missing                                 all
,{    'N',UED_unknown_quality     } //Time uncertain                          159
,{    'N',CORN::missing_quality     } //Temperature missing, but known to be
                 //ABOVE freezing.                         002
,{    'O',UED_unknown_quality     } //Not assigned
,{    'P',UED_unknown_quality     } //Not assigned
,{    'Q',UED_unknown_quality     } //Not assigned
,{    'R',UED_unknown_quality     } //Not assigned
,{    'S',UED_measured     } //More than one occurrence                023, 024, 044, 046,
                 //                                      052, 054, 056, 058,
                 //                                      059, 157, 158
,{    'T',UED_measured     } //Trace.  Value is zero                   006-013, 039, 048-
                 //                                      052, 054, 056
,{    'U',UED_measured     } //Valid datum, unknown snow               061-068
,{    'V',UED_measured     } //Valid datum, no snow cover              061-068
,{    'W',UED_measured     } //Valid datum, with snow cover            061-068
,{    'X',UED_estimated     } //Estimated, unknown snow                 061-068
,{    'Y',UED_estimated     } //Estimated, no snow cover                061-068
,{    'Y',CORN::missing_quality     } //Temperature missing, but known to be
                 //BELOW freezing.                         002
,{    'Z',UED_estimated     } //Estimated, with snow cover              061-068
,{0,UED_not_valid}
};
//______________________________________________________________________________
//   export_location_parameters can be replaced with   here we can use CC_stations
Canadian_climatological_format_convertor::Canadian_climatological_format_convertor
(int argc, const char *argv[])
: UED_convertor(argc,argv)
, export_month_daily_records_encountered(false)
, export_day_hourly_records_encountered(false)
, export_day_15min_records_encountered(false)
{}
//______________________________________________________________________________
int Canadian_climatological_format_convertor::convert()
{
   element_conversions[1].var_code = UED_STD_VC_max_temperature.get();
   element_conversions[2].var_code = UED_STD_VC_min_temperature.get();
   element_conversions[3].var_code = UED_STD_VC_avg_temperature.get();
   element_conversions[4].var_code = UED_STD_VC_max_relative_humidity.get();
   element_conversions[5].var_code = UED_STD_VC_min_relative_humidity.get();
   element_conversions[76].var_code = UED_STD_VC_wind_speed.get();
   element_conversions[ 12].var_code = UED_STD_VC_precipitation.get();
   element_conversions[125].var_code = UED_STD_VC_precipitation.get();
   element_conversions[126].var_code = UED_STD_VC_precipitation.get();
   element_conversions[127].var_code = UED_STD_VC_precipitation.get();
   element_conversions[128].var_code = UED_STD_VC_precipitation.get();
   element_conversions[129].var_code = UED_STD_VC_precipitation.get();
   element_conversions[130].var_code = UED_STD_VC_precipitation.get();
   element_conversions[131].var_code = UED_STD_VC_precipitation.get();
   element_conversions[132].var_code = UED_STD_VC_precipitation.get();
   for (int i = 0; i <= 172; i++)
   {
      if (element_conversions[i].var_code == 0)
      {  // Create  nonstandard code based on the element number
         UED_smart_variable_code element_based_code(0,element_conversions[i].element_number,true);
         element_conversions[i].var_code  = element_based_code.get();
      }
      element_conversions[i].encountered_in_this_database = false;
   }
   return  UED_convertor::convert();
}
//______________________________________________________________________________
// 060105  this works but we can now use the new common all_known_stations

class Canadian_element_record
: public Item
{
 protected:
   CORN::UIO_string       station_ID;
   CORN::Year        year;
   Element           element;
 public:  // data will be stored in a UED_data_record on import (not used for export)
   UED_data_record   *Xued_record; // this is not used for export and set to nil

 public:  // values and flags for export
   CORN::Dynamic_float_array  values;                                            //031208
   CORN::Dynamic_uint8_array  attributes;                                        //031208
 public: // constructors for import
   Canadian_element_record
     (const CORN::Ustring &raw_record,uint16 elements,uint16 element_pos
      , Record_code        _rec_type
      , UED_units_code     _time_step_units_code);
   Canadian_element_record
      (uint16 elements
      ,const char         *station_ID
      ,CORN::Year          year
      ,Element             element
      ,datetime64          time_stamp
      ,Record_code         rec_type
      ,UED_variable_code   variable_code
      ,UED_units_code      units_code
      ,UED_units_code      time_step_units_code);
 public: // constructors for export
   Canadian_element_record
   (const char        * i_station_ID
   ,CORN::Year          i_year
   ,Element             i_element);
 public: // destructor
   virtual ~Canadian_element_record();
 public: // accessors (used by import)
   inline const CORN::Ustring &get_station_ID() const { return station_ID;}
   inline CORN::Year get_year() const { return year; }
   inline Element get_element() const { return element; }
 public: // accessors (used by export)
   float32 set_value_attribute(uint16 index,float32 value, CORN::Quality_code flag); //031208
   virtual uint16 get_value_count()                                        const = 0;
      // Derived classes must return the number of value/flag pairs to output //031208

   virtual void write(ostream &)                                     performs_IO;      //980511
   virtual void write_date_stamp(ostream &)                          performs_IO = 0;  //980511
};
//______________________________________________________________________________
Canadian_element_record::~Canadian_element_record()
{  if (Xued_record) delete Xued_record; Xued_record = 0;
}
//______________________________________________________________________________
Canadian_element_record::Canadian_element_record
(const char *i_station_ID
,CORN::Year          i_year
,Element             i_element)
: Item()
, station_ID(i_station_ID)
, year(i_year)
, element(i_element)
, Xued_record(0) // Not used for export
{}
//______________________________________________________________________________
void Canadian_element_record::write(ostream &out_file) performs_IO
{
   out_file << setfill('0') << setw(6) << station_ID.c_str();
   write_date_stamp(out_file);
   out_file <<  setfill('0') << setw(3) << (int)element;
   for (int i = 1; i <= get_value_count(); i++)
   {
      float32 value = values.get_no_resize(i);
      out_file << ((value < 0.0) ? '-' : '0');
      value = fabs(value);
      float32 scale_factor = element_conversions[element].normalization_factor;
      value /= scale_factor;
      int32 value_int = value ;
      out_file <<  setfill('0') << setw(5) << value_int;
      // out_file attribute to flag
      char flag = ' ';
      CORN::Quality_code attribute = attributes.get_no_resize(i);
      switch(attribute)
      {  case UED_measured : flag = ' '; break;
         case CORN::missing_quality  : flag = 'M'; break;
         case UED_estimated: flag = 'E'; break;
         case UED_generated: flag = 'D'; break;
      }
      out_file << flag;
   }
   out_file << endl;                                                             //040107
}
//_1998-05-11___________________________________________________________________
Canadian_element_record::Canadian_element_record
(const CORN::Ustring &raw_record
,uint16 value_count
,uint16 element_pos
, Record_code  _rec_type
, UED_units_code        _time_step_units_code
)
: station_ID(raw_record.substr(0,7))
,Item()
, year((CORN::Year)atoi(raw_record.substr(7,4).c_str()))
, element((uint16)atoi(raw_record.substr(element_pos,3).c_str()))
, Xued_record(new UED_data_record(
   UED_data_record_creation_layout
   (
     _rec_type
    ,((element <= 172) ? element_conversions[element].var_code : 0)   // element_conversions[element].var_code
    ,((element <= 172) ? element_conversions[element].units_code : 0) // element_conversions[element].units_code
    ,_time_step_units_code
    , UT_year  // 060616   WARNING  This is a new parameter, I think it should be year There is a new parameter here for time stamp time step . I haven't bother to fix this yet (it is probably year)
    ,UED_measured)
   ,0.0 /*Date_time(Date((CORN::Year)0,(CORN::DOY)0))*/) // to be determined latter
   )
{  int element_index = (element <= 172) ? element : 1;
   element_conversions[element_index].encountered_in_this_database = true;
   int sign_pos    = element_pos + 3;
   int value_pos   = element_pos + 4;
   int flag_pos    = element_pos + 9;
   for (uint16 i = 0 ;i < value_count ;i++)
   {
      float32 value = (float)atoi(raw_record.substr(value_pos,5).c_str());
      //040104_*/       // I have found some records where missing data was incorrectly flagged. -9999 is always missing data.
      bool definitely_missing = is_essentially(value, 99999.0,0.00001);          //040104


      value *= element_conversions[element_index].normalization_factor;
      if (raw_record.c_str()[sign_pos] == '-')
         value = -value;  // signed negative

      Dynamic_float_array   &values  = Xued_record->get_data_values();
      Dynamic_uint8_array        &qualities = Xued_record->get_attributes();

      values.set(i,value);

      char flag = (raw_record.c_str()[flag_pos]);

      CORN::Quality_code quality = UED_measured;
      bool flag_matched = false;
      for (int fi = 0; !flag_matched && flag_conversion[fi].flag; fi++)
      {
         if (flag_conversion[fi].flag == flag)
         {
            quality = flag_conversion[fi].quality;
            flag_matched = true;
         }
      }
      //040104_*/       // I have found some records where missing data was incorrectly flagged. -9999 is always missing data.
      if (definitely_missing)                                                    //040104
         quality = CORN::missing_quality;
      qualities.set(i,(uint8)quality);

      sign_pos += 7;
      value_pos+= 7;
      flag_pos += 7;
   }
   //Set the time stamp
   CORN::Date time_stamp_date((Year)year,(DOY)1);
   Xued_record->set_time_stamp(time_stamp_date.get_datetime64());
}
//______________________________________________________________________________
float32 Canadian_element_record::set_value_attribute(uint16 index,float32 value, CORN::Quality_code attribute)
{  values.set(index,value);
   attributes.set(index,attribute);
   return value;
}
//_2003-12-08___________________________________________________________________
Canadian_element_record::Canadian_element_record
(nat16               elements
,const char *        i_station_ID
,CORN::Year          i_year
,Element             i_element
,datetime64          i_time_stamp_check_used
,Record_code         i_rec_type
,UED_variable_code   i_variable_code
,UED_units_code      i_units_code
,UED_units_code      i_time_step_units_code
)
: station_ID(i_station_ID)
,Item()
, year(i_year)
, element(i_element)
, Xued_record( new UED_data_record(
   UED_data_record_creation_layout
   ( i_rec_type
    ,i_variable_code   // element_conversions[element].var_code
    ,i_units_code // element_conversions[element].units_code
    ,i_time_step_units_code
    , UT_year  // 060616   WARNING  This is a new parameter, I think it should be year , 050401 There is a new parameter here for time stamp time step . I haven't bother to fix this yet (it is probably year)
    ,UED_measured
   )
   ,Date(year,1).get_datetime64())) //0.0 /*Date_time(Date((CORN::Year)0,(CORN::DOY)0))*/) // to be determined latter
{
}
//______________________________________________________________________________
class Canadian_day_interval_record
: public Canadian_element_record
{
   CORN::Month    month;
   CORN::DOM       dom;
public:
   CORN::DOY       doy;
public: // constructor for import
   Canadian_day_interval_record
   (const CORN::Ustring &raw_record
   ,uint16 value_count
   ,Record_code      i_rec_type
   ,UED_units_code            i_time_step_units_code
   )
   : Canadian_element_record(raw_record,value_count,15,i_rec_type,i_time_step_units_code)
   , month((CORN::Month)atoi(raw_record.substr(11,2).c_str()))
   , dom((CORN::DOM)atoi(raw_record.substr(13,2).c_str()))
   {
      CORN::Date date(year,month,dom);
      doy = date.get_DOY();
      Xued_record->set_time_stamp(date.get_datetime64());
   }
public: // constructor for export
   Canadian_day_interval_record
   (const char *i_station_ID
   ,CORN::Year    i_year
   ,CORN::DOY     i_doy
   ,Element       i_element
   )
   : Canadian_element_record(i_station_ID,i_year,i_element)
   , month(0) // not used for export
   , dom(0)   // not used for export
   , doy(i_doy)
   {
      CORN::Date date(year,month,dom);
      month = date.get_month();
      dom = date.get_DOM();
   }

public:
   inline CORN::Month get_month() const { return month; }

public: // for export
      virtual void         write_date_stamp(ostream &) performs_IO;           //031208
};
//______________________________________________________________________________
class Canadian_daily_by_month_data_record
: public Canadian_element_record
{
 public:
   CORN::Month     month;
 public:  // constructor for import
   Canadian_daily_by_month_data_record(const CORN::Ustring &raw_record);
 public: // constructor for export
   Canadian_daily_by_month_data_record(const char *i_station_ID, Year i_year, Month i_month,Element i_element);
 public:
   inline CORN::Month get_month()                                          const { return month; }
   inline virtual uint16 get_value_count()                                 const { return 31;}  // I think this goes here //031208
 public: // for export
   virtual void         write_date_stamp(ostream &)                  performs_IO; //980511
};
//______________________________________________________________________________
void Canadian_daily_by_month_data_record::write_date_stamp(ostream &out_file) performs_IO
{  out_file << setfill('0') << setw(4) << (int)year
            << setfill('0') << setw(2) << (int)month;
}
//_2003-12-08___________________________________________________________________
Canadian_daily_by_month_data_record::Canadian_daily_by_month_data_record(const CORN::Ustring &raw_record)
:  Canadian_element_record(raw_record,31,13
, UED_record_type_distinguisher::UED_data_set_year_var_units
, 0 //       _time_step_units_code
)
{  // read month from record
   month = (CORN::Month)atoi(raw_record.substr(11,2).c_str());
}
//______________________________________________________________________________
Canadian_daily_by_month_data_record::Canadian_daily_by_month_data_record
(const char *i_station_ID, Year i_year, Month i_month,Element i_element)
: Canadian_element_record(i_station_ID,i_year,i_element)
, month(i_month)
{}
//______________________________________________________________________________
class Canadian_15min_data_record
: public Canadian_day_interval_record
{
   char           day_flag;
 public: // Constructor for import
   Canadian_15min_data_record(const CORN::Ustring &raw_record)
   :Canadian_day_interval_record(raw_record,96
     ,UED_record_type_distinguisher::UED_data_set_date_var_units
     ,UT_15_minutes)
   , day_flag(raw_record[raw_record.length()-1])
   {}
 public: // Constructor for export
   Canadian_15min_data_record(const char *station_ID
   ,CORN::Year    _year
   ,CORN::DOY     _doy
   ,Element       _element)
   :Canadian_day_interval_record(_station_ID,_year,_doy,_element)
   {}
   inline virtual uint16 get_value_count()                                 const { return 96;} //031208
   virtual void write(ostream &)                                     performs_IO; //980511
};
//______________________________________________________________________________
void Canadian_15min_data_record::write(ostream &outfile) performs_IO
{  Canadian_day_interval_record::write(outfile);
   outfile << day_flag;
}
//_1998-05-11___________________________________________________________________
void Canadian_day_interval_record::write_date_stamp(ostream &out_file) performs_IO
{  CORN::Date date_stamp(year,doy,D_YMD,D_YYYY|D_M|D_lead_zero,0,false);
   char date_str[50];
   out_file << date_stamp.text_str(date_str);
}
//_2003-12-08___________________________________________________________________
class Canadian_hourly_data_record
: public Canadian_day_interval_record
{public: // Constructor for import
   Canadian_hourly_data_record(const CORN::Ustring &raw_record)
   :  Canadian_day_interval_record(raw_record, 24
      ,UED_record_type_distinguisher::UED_data_set_date_var_units
      ,UT_60_minutes
      )
   {
      Xued_record->set_time_stamp(Date(year,doy).get_datetime64());
   }
 public: // Constructor for export
   Canadian_hourly_data_record
   (const char   *i_station_ID
   ,CORN::Year    i_year
   ,CORN::DOY     i_doy
   ,Element       i_element
   )
   :Canadian_day_interval_record(i_station_ID,i_year,i_doy,i_element)
   {}
 public:
   inline virtual uint16 get_value_count() const { return 24;} //031208
 public: // for export
   // already done by Canadian_day_interval_record/*_980511*/       virtual void         write_date_stamp(ostream &) performs_IO;
};
//______________________________________________________________________________
class Canadian_monthly_data_record
: public Canadian_element_record
{
 public:
   Canadian_monthly_data_record(const CORN::Ustring &raw_record)
   :  Canadian_element_record(raw_record,12,11
      ,UED_record_type_distinguisher::UED_data_set_year_var_units
      ,UT_month
      )
   {}
   inline virtual uint16 get_value_count() const { return 12;} //031208
 public: // for export
   virtual void write_date_stamp(ostream &)                          performs_IO; //980511
};
//______________________________________________________________________________
void Canadian_monthly_data_record::write_date_stamp(ostream &out_file) performs_IO
{  out_file << setfill('0') << setw(4) << year;
}
//_1998-05-11___________________________________________________________________
// Because the canadian daily data is separated by month,
// we need to build daily data records on the fly.
// Once the data has been extracted from the raw record,
// search the pending daily data record list for matching station and year.
// Create record is necessary.
// put the day of month data into the respective day of year data slots.

class Daily_data_record
: public Canadian_element_record
{
   bool days_completed[367];
public:
   Daily_data_record
   (
   const CORN::Ustring &raw_record
   ,CORN::Year   _year
   )
   :Canadian_element_record(raw_record,CORN_date_days_in_year(_year),13
      ,UED_record_type_distinguisher::UED_data_set_year_var_units
      ,UT_day
      )
   {
      clear();
   }

   Daily_data_record
   (
    uint16 elements
   ,const char *  i_station_ID
   ,CORN::Year      i_year
   ,Element        i_element
   ,datetime64  i_time_stamp
   ,UED_smart_variable_code    i_variable_code
   ,CORN::Units_clad       i_units_code
   )
   :Canadian_element_record(
     CORN_date_days_in_year(i_year)
    ,i_station_ID
    ,i_year
    ,i_element
    ,i_time_stamp
    ,UED_record_type_distinguisher::UED_data_set_year_var_units
    ,i_variable_code.get()
    ,i_units_code.get()
    ,UT_day
   )
   {  clear();
   }
   void clear()
   {  for (int i = 0; i <=366; i++)
          days_completed[i] = false;
   }
   void add(const Canadian_daily_by_month_data_record &monthly_data);
   void add(const Canadian_hourly_data_record &hourly_data);
   bool complete()
   {  bool result = true;
      for (CORN::DOY doy = 1; doy <= CORN_date_days_in_year(year); doy++)
         if (!days_completed[doy])
            result = false;
      return result;
   }
   inline virtual uint16 get_value_count() const { return CORN_date_days_in_year(year);} //031208
  virtual void         write_date_stamp(ostream &) performs_IO; //980511
};
//______________________________________________________________________________
void Daily_data_record::write_date_stamp(ostream &) performs_IO
{
   // I this is just a stub we don't export this type of record
}
//_1998-05-11___________________________________________________________________
void Daily_data_record::add(const Canadian_daily_by_month_data_record &monthly_data)
{  Dynamic_float_array   &values  = Xued_record->get_data_values();
   Dynamic_uint8_array   &qualities = Xued_record->get_attributes();
   Dynamic_float_array   &monthly_values  = monthly_data.Xued_record->get_data_values();
   Dynamic_uint8_array   &monthly_qualities = monthly_data.Xued_record->get_attributes();
   for (DOM dom = 1
       ; dom <= CORN::date_days_in_month(monthly_data.get_year(),monthly_data.get_month())
       ; dom++)
   {  CORN_date date(monthly_data.get_year(),monthly_data.get_month(),dom);
      float32 value_dom = monthly_values.get_no_resize(dom-1);
      CORN::DOY doy = date.get_DOY();
      days_completed[doy] = true;
      values.set(doy-1,value_dom); // UED records are 0 indexed;
      CORN::Quality_code quality_dom =monthly_qualities.get_no_resize(dom-1);
      qualities.set(doy-1,quality_dom);
   }
}
//______________________________________________________________________________
void Daily_data_record::add(const Canadian_hourly_data_record &hourly_data)
{
   CORN::DOY doy = hourly_data.doy;
   Dynamic_float_array  &values  = Xued_record->get_data_values();
   Dynamic_uint8_array  &qualities = Xued_record->get_attributes();

   Dynamic_float_array  &hourly_values  = hourly_data.Xued_record->get_data_values();
   Dynamic_uint8_array  &hourly_qualities = hourly_data.Xued_record->get_attributes();

   Statistical_running_tally daily_tally; // This could be sum, max or avg depending of the element
   CORN::Quality_code daily_quality = CORN::measured_quality; // 060616 UED_real;
   for (CORN_hour hour = 0  // value array is 0 indexed
       ; hour <= 23
       ; hour++)
   {
      //CORN_date date(monthly_data.get_year(),monthly_data.get_month(),dom);
      float32 value_hour = hourly_values.get_no_resize(hour);
      CORN::Quality_code quality_hour = hourly_qualities.get_no_resize(hour);
      if (UED_is_valid(quality_hour))
         daily_tally.append(value_hour);
      daily_quality = UED_worst_quality(daily_quality,quality_hour);
   }

   float32 daily_value = 0;
   if (element == 75)
   {  // 75 is supposed to be wind direction
         daily_value = daily_tally.sum();  // This should be avg
   }
   if (element == 76)
   { // 76 is wind speed
         daily_value = daily_tally.sum();//obs: / 86.4; // Will give km/day convert to m/s
         Xued_record->units_code = UC_kilometers_per_day;
   }
   values.set(doy-1,daily_value); // UED records are 0 indexed;
   qualities.set(doy-1,daily_quality);
   days_completed[doy] = true;
}
//______________________________________________________________________________
class Pending_daily_data_record_list
: public Unidirectional_list
{
public:
   Pending_daily_data_record_list()
   : Unidirectional_list()
   {}

   Daily_data_record *find_or_create
   (const char *station_ID
   ,CORN::Year year
   ,Element element_code
   ,UED_variable_code   variable_code
   ,UED_units_code      units_code
   );
}
//______________________________________________________________________________
Daily_data_record *Pending_daily_data_record_list::find_or_create
   (const char *station_ID
   ,CORN::Year year
   ,Element element_code
   ,UED_variable_code   variable_code
   ,UED_units_code      units_code
//000720   ,const Canadian_daily_by_month_data_record &monthly_data_info

   )
{
   FIND_FOR_EACH(found_dd_rec,dd_rec,Daily_data_record,true,each_dd_rec)
//   for (Daily_data_record *dd_rec = (Daily_data_record *)move_to_head()
//         ; dd_rec
//         ; dd_rec = (Daily_data_record *)move_to_next())
   {
      if ( (dd_rec->get_station_ID() == station_ID)
         &&(dd_rec->get_year() == year)
         &&(dd_rec->get_element() == element_code))
            found_dd_rec = dd_rec;
//030723            return dd_rec;
   }
   FOR_EACH_END(each_dd_rec);
   if (found_dd_rec) return found_dd_rec;

   Daily_data_record *new_dd_rec =
   new   Daily_data_record
   (CORN_date_days_in_year(year)
   ,station_ID // monthly_data_info.get_station_ID()
   ,year
   ,element_code
   ,Date(year,1).get_datetime64() // Date_time(year,1)
   ,variable_code
   ,units_code
//000720obs ,monthly_data_info.Xued_record->get_variable_code()
//000720obs    ,monthly_data_info.Xued_record->get_units_code()
   );
   append(new_dd_rec);
   return new_dd_rec;
}
//______________________________________________________________________________
Pending_daily_data_record_list pending_daily_data_records;
//______________________________________________________________________________
Canadian_daily_by_month_data_record *Canadian_climatological_format_convertor::get_month_daily_record(Element search_element,const Date_time_64 &date_time)
{
   Year  search_year = date_time.get_year();
   Month search_month= date_time.get_month();

   // This little optimization quickly returns if the most recent record is the one we want (often the case)
   static Year recent_year = 0;
   static Month recent_month = 0;
   static Element recent_element = 0;
   static Canadian_daily_by_month_data_record *recent_rec = 0;
   if (recent_rec && (recent_element==search_element) && (recent_year == search_year) && (recent_month == search_month))
      return recent_rec;
   FIND_FOR_EACH_IN(found_rec,rec,Canadian_daily_by_month_data_record,pending_export_month_daily_records[search_month],true,each_rec)
   {
      if ((rec->get_element() == search_element) && (rec->get_year() == search_year) && (rec->month == search_month))
         found_rec = rec;
   }
   FOR_EACH_END(each_rec);
   if (!found_rec)
   {
      //create new rec and append
      found_rec = new Canadian_daily_by_month_data_record
      (export_station_ID.c_str(), search_year, search_month,search_element);
      pending_export_month_daily_records[search_month].append(found_rec);
      export_month_daily_records_encountered = true;                             //040104
   }
   recent_year = search_year;
   recent_month = search_month;
   recent_element = search_element;
   recent_rec = found_rec;
   return found_rec;
}
//______________________________________________________________________________
Canadian_hourly_data_record         *Canadian_climatological_format_convertor::get_day_hourly_record(Element search_element,const Date_time_64 &search_date_time)
{
   // This little optimization quickly returns if the most recent record is the one we want (often the case)
   static Date32 recent_date = 0;                                                //040104
   static Element recent_element = 0;
   static Canadian_hourly_data_record *recent_rec = 0;
   if (recent_rec && (recent_element==search_element) && (recent_date == search_date_time.get_date32())/* && (recent_year == search_year) && (recent_doy == search_doy)*/)
      return recent_rec;

   Year  search_year = search_date_time.get_year();
   DOY   search_doy  = search_date_time.get_DOY();
   FIND_FOR_EACH_IN(found_rec,rec,Canadian_hourly_data_record,pending_export_day_hourly_records[search_doy],true,each_rec)
   {
      if ((rec->get_element() == search_element) &&(rec->get_year() == search_year) /*&& (rec->doy == search_doy)*/) //040104
         found_rec = rec;
   }
   FOR_EACH_END(each_rec);
   if (!found_rec)
   {
      //create new rec and append
      found_rec = new Canadian_hourly_data_record(export_station_ID.c_str(),search_year,search_doy,search_element);
      pending_export_day_hourly_records[search_doy].append(found_rec);
      export_day_hourly_records_encountered = true;                              //040104
   }
   recent_date = search_date_time.get_date32();                                  //040104
   recent_element = search_element;
   recent_rec = found_rec;
   return found_rec;
}
//______________________________________________________________________________
Canadian_15min_data_record          *Canadian_climatological_format_convertor::get_day_15min_record(Element search_element,const Date_time_64 &search_date_time)
{
   static Date32 recent_date = 0;                                                //040104
   static Element recent_element = 0;
   static Canadian_15min_data_record *recent_rec = 0;
   if (recent_rec && (recent_element==search_element) && (recent_date == search_date_time.get_date32())/*&& (recent_year == search_year) && (recent_doy == search_doy)*/)
      return recent_rec;
   Year  search_year = search_date_time.get_year();
   DOY   search_doy  = search_date_time.get_DOY();
   FIND_FOR_EACH_IN(found_rec,rec,Canadian_15min_data_record,pending_export_day_15min_records[search_doy],true,each_rec) //040104
   {
      if ((rec->get_element() == search_element) &&(rec->get_year() == search_year)) //040104
         found_rec = rec;
   }
   FOR_EACH_END(each_rec)
   if (!found_rec)
   {
      //create new rec and append
      found_rec = new Canadian_15min_data_record(export_station_ID.c_str(),search_year,search_doy,search_element);
      pending_export_day_15min_records[search_doy].append(found_rec);
      export_day_15min_records_encountered = true;                               //040104
   }
   recent_date = search_date_time.get_date32();                                  //040104
   recent_element = search_element;
   recent_rec = found_rec;
   return found_rec;
}
//______________________________________________________________________________
void Canadian_climatological_format_convertor::append_or_update_record
(UED_indexed_database *ued_file
,UED_data_record      *ued_record)
{  Record_code       rec_type = ued_record->get_code();
   UED_variable_code var_code = ued_record->get_variable_code();
   UED_time_query_single_date time_query(ued_record->get_time_stamp());          //040720
   UED_data_record *existing_datarec = ued_file->locate_data_record              //990114
            (rec_type,var_code,time_query);
   if (existing_datarec)
   {  // A matching datarecord already exists in the database, we need to preserve any better quality data
      uint16 data_count = existing_datarec->data_values_get_count();
      for (int i = 0; i < data_count; i++)
      {  datetime64 date_i = ued_record->get_date_time_for_index(i);
         CORN::Quality_code quality_i;
         float32 value_i = ued_record->get_value(quality_i,date_i);
         existing_datarec->set_value(value_i,quality_i,date_i,false);
      }
   }
   else // this is new data we can just add the record
      ued_file->append_record(ued_record,true);
}
//______________________________________________________________________________
/*_______*/ nat32 Canadian_climatological_format_convertor::perform_import()
/*_______*/ {
/*060616_*/    nat32 records_imported = 0;                                                   //060616
/*_______*/    // Open input file
/*060616_*/    ifstream input_file(parameters.target_filename.c_str());
/*_______*/
/*_______*/    // Open UED file
/*_______*/ //030731   UED_indexed_database ued_file(ued_filename.c_str(),false);
/*_______*/ //030701   ued_file.initialize();
/*_______*/
/*_______*/    while (!input_file.eof())
/*_______*/    {
/*_______*/       CORN::Ustring buffer;
/*_______*/       buffer.read_line(input_file);
/*_______*/       Canadian_element_record *element_record = 0;
/*_______*/
/*_______*/       // based on record length determine format
/*_______*/       switch (buffer.length())
/*_______*/       {
/*_______*/          // instaciate the respective record format
/*_______*/          case 186 :
/*_______*/          {
/*_______*/             element_record = new Canadian_hourly_data_record(buffer);
/*_______*/             Canadian_hourly_data_record *hourly_record = (Canadian_hourly_data_record *)element_record;
/*031220_*/             if (element_record->get_element() == 76)
/*031220_*/             {
/*031220_*/                // Currently we only import hourly wind data all other elements are not needed by ClimGen
//*_______*/                cout << hourly_record->doy << ' ';
/*_______*/ //if (hourly_record->get_element() == 76)
/*_______*/ //cout << "reached" << endl;
/*_______*/
/*_______*/                Daily_data_record *annual_daily_data_record = pending_daily_data_records.find_or_create
/*_______*/                (hourly_record->get_station_ID().c_str(),hourly_record->get_year(),hourly_record->get_element()
/*_______*/                ,hourly_record->Xued_record->get_variable_code()
/*_______*/                ,hourly_record->Xued_record->get_units_code()
/*_______*/                );
/*_______*/                annual_daily_data_record->add(*hourly_record);
/*_______*/                if (annual_daily_data_record->complete() &&
/*_______*/                    (annual_daily_data_record->get_element() != 75)
/*_______*/                    // UED does not have degrees from north, and not sure how to tally hourly values to a daily value
/*_______*/             	   )
/*_______*/                {
/*060616_*/                   if (  (parameters.station_IDs_filter.length() == 0)
/*060616_*/                    ||(parameters.station_IDs_filter.contains(element_record->get_station_ID().c_str()))
/*060616_*/                    ||(parameters.station_IDs_filter == "all")
/*060616_*/                    ||(parameters.station_IDs_filter == "")
/*060616_*/                    )
/*060616_*/                   {
/*_______*/                   UED_data_record *ued_record = new UED_data_record(*annual_daily_data_record->Xued_record);
//060616/*_______*/                   UED_indexed_database *ued_file = provide_station_database(element_record->get_station_ID().c_str(),station_ID_filter);

/*060616_*/                   bool added_just_now = false;
/*060616_*/                   Station_database *station_database = provide_station_database(element_record->get_station_ID().c_str(),added_just_now);
/*060616_*/                   // station_database guareented to be provided
/*060616_*/                   UED_indexed_database *ued_file = &(station_database->ued_file);
//060616 /*_______*/                   if (ued_file)   060616  station_database guareented to be provided
/*031219_*/                   append_or_update_record(ued_file,ued_record);
/*060616_*/                   }
/*_______*/                }
/*_______*/             }
/*031220_*/             else // if (element_record->get_element() != 76)
/*031220_*/             {
/*031220_*/                static nat32 last_omitted_element = 0;
                           if (element_record->get_element() != last_omitted_element)
                           {
/*031220_*/                   cout << "Omitting records not used by ClimGen..."
                                << element_record->get_element()
                                << " "
                                << element_conversions[element_record->get_element()].element_number
                                << " "
                                << element_conversions[element_record->get_element()].description
                                << "\r" ;
                           }
                           last_omitted_element = element_record->get_element() ;
/*031220_*/                // Currently we only import hourly wind data all other elements are not needed by ClimGen
/*031220_*/                // We import hourly wind because we need to export the hourly values
/*031220_*/                // the hourly values are the only wind speed currently provided in canadian climatological database
/*031220_*/                // We want to preserve actual data values on export.
//                         I need to optimize UED data record index lookup (faster search)
//                         when that occurs I should be able to restore all data records.
/*031220_*/             }
                        // I would like to import hourly wind so I can preserve the
                        // real data in export, but there are to many records
                        // to index so it is too slow for ClimGen.
/*031220_*/                delete element_record;
/*031220_*/                element_record = 0;
//031219_obs we now store hourly data because we now have export mode, we want to preserve that mode. element_record = 0;  // Currently don't store hourly data in the database
/*_______*/          } break;
/*_______*/
/*_______*/          case 233 :
/*_______*/          {  Canadian_daily_by_month_data_record monthly_data(buffer);
/*_______*/             //create or update respective annual daily data record;
/*_______*/             Daily_data_record *annual_daily_data_record = pending_daily_data_records.find_or_create
/*_______*/             (monthly_data.get_station_ID().c_str(),monthly_data.get_year(),monthly_data.get_element()
/*_______*/             ,monthly_data.Xued_record->get_variable_code()
/*_______*/             ,monthly_data.Xued_record->get_units_code()
/*_______*/ //000717            ,monthly_data
/*_______*/             );
/*_______*/             annual_daily_data_record->add(monthly_data);
/*_______*/             element_record = annual_daily_data_record->complete()
/*_______*/             ? annual_daily_data_record
/*_______*/             : 0;
/*_______*/          }  break;
/*_______*/
/*_______*/          case  98 : new Canadian_monthly_data_record(buffer);  break;
/*_______*/          case 691 : element_record = new Canadian_15min_data_record(buffer);           break;
/*_______*/       }


/*_______*/       if (element_record)
/*_______*/       // create equvelent UED record
/*_______*/       {  UED_data_record *ued_record =// element_record ?
/*_______*/           new UED_data_record(*element_record->Xued_record); // create a copy of the record buffer for UED to have
//obs/*_______*/          : 0;
/*_______*/
///*_______*/ cout << buffer.substr(0,20) << '\n';
/*_______*/          int element_for_status_output = element_record->get_element();
/*_______*/          cout << element_record->get_year() /*year_for_status_output*/ << ' ' << element_conversions[element_for_status_output].description << endl;
/*_______*/

/*060616_*/          bool added_just_now = false;
/*060616_*/          Station_database *station_database = provide_station_database(element_record->get_station_ID().c_str(),added_just_now);
/*060616_*/          // station_database guareented to be provided
/*060616_*/          UED_indexed_database *ued_file = &(station_database->ued_file);

//060616 /*_______*/          UED_indexed_database *ued_file = provide_station_database(element_record->get_station_ID().c_str(),station_ID_filter/*.c_str()*/);
//060616 /*_______*/          if (ued_file)   060616 station_database guareented to be provided
/*_______*/          {
/*031219_*/             append_or_update_record(ued_file,ued_record);

/*_______*/          }
/*_______*/       }
/*060616_*/       records_imported++;
/*_______*/    }
/*_______*/
/*_______*/
/*_______*/ //element_conversions[12].encountered_in_this_database = true;
/*_______*/ #ifdef TEMP_DISABLED
//_______//    Output variable codes for elements for which there may not be UED standard codes
/*_______*/    for (int i = 0; i <= 172; i++)
/*_______*/       if (element_conversions[i].encountered_in_this_database)
/*_______*/       {
/*_______*/          UED_smart_variable_code element_var_code(element_conversions[i].var_code);
/*_______*/ //         if (!element_var_code.is_standard())
/*_______*/          {
/*_______*/              UED_variable_definition_format_0_record *element_var_def =
/*_______*/             new
/*_______*/             UED_variable_definition_format_0_record
/*_______*/             (element_var_code.get()
/*_______*/             ,&ued_file.get_units_definition(element_conversions[i].units_code)
/*_______*/             ,-999999.9,999999.9
/*_______*/             ,-999999999.9,99999999.9
/*_______*/             ,element_conversions[i].description
/*_______*/             );
/*_______*/             ued_file.append_record(element_var_def);
/*_______*/             ued_file.finished_with(element_var_def);
/*_______*/
/*_______*/          }
/*_______*/       }
/*_______*/ #endif
/*060616_*/    return records_imported; // 060616  return 0;
/*_______*/ }
//______________________________________________________________________________
/*_______*/ nat32 Canadian_climatological_format_convertor::perform_export()
//060616 export(const char *UED_filename/*,const char *i_station_ID*/)
/*_______*/ {
/*060616_*/    nat32 records_exported = 0;
/*_______*/    cout << "Openning and indexing database..." << '\r';

/*_______*/    UED_indexed_database ued_file(parameters.ued_filename.c_str()/*060616 UED_filename*/,true);
/*_______*/    CORN::Quality_code datum_attribute;


/*_______*/    // First assume the UED_filename file matches the station ID:
/*_______*/    char filename_only[255];
//060616/*_______*/    CORN::File_name smart_UED_filename(UED_filename);
//060616/*_______*/    smart_UED_filename.get_file(filename_only);

/*_______*/    strcpy(filename_only,parameters.ued_filename.get_name(false).c_str());
/*_______*/    filename_only[7] = 0;
/*_______*/    export_station_ID.assign(filename_only);

//060616/*_______*/    CORN::File_name wind_filename(UED_filename);
//060616/*_______*/    wind_filename.set_file(filename_only);
/*_______*/    CORN::File_name wind_filename(parameters.ued_filename.c_str());
/*_______*/    wind_filename.set_name(filename_only);
/*_______*/    wind_filename.set_ext("windspeed");
/*_______*/    ofstream wind_output(wind_filename.c_str());
/*_______*/    // This is a special output file for  "Rafael Munoz-Marquez" <ramunozm@sympatico.ca>
/*_______*/    wind_output << "Date" << '\t' << "Windspeed"<< endl;
/*_______*/    wind_output << "YYYYDDD" << '\t' << "km/day"<< endl;


///*_______*/    export_station_ID.assign(i_station_ID);
/*_______*/       // station ID taken from UED file location record, if it exists, but currently import wizard prompts user for it

//_______//    Get the location record for the UED
//060616/*_______*/    UED_location_record *location_rec = (UED_location_record *)ued_file.goto_next(UED_location_information);

/*060616_*/    UED_geolocation_record  *location_rec= ued_file.get_geolocation_record();
/*_______*/    if (location_rec) // if it exists
/*_______*/    {  // extract the station ID from the location record
/*_______*/       // if the extracted ID is value then use that IDo
/*_______*/           if (strlen(location_rec->get_station_ID_code()))
/*_______*/              export_station_ID.assign(location_rec->get_station_ID_code());
/*_______*/    }
/*_______*/    ued_file.goto_BOF();
/*_______*/    cout << "Indexing completed." << endl;

/*_______*/    char for_time_cstr[100];
/*_______*/    // for each data record record in the database.
/*_______*/    for  (UED_data_record *data_rec = ued_file.goto_next_data_record();data_rec ;data_rec = ued_file.goto_next_data_record())
/*_______*/    {
/*_______*/       Date_time_64 for_time(data_rec->get_time_stamp());
/*_______*/       uint16 num_values = data_rec->get_num_values();
/*_______*/       UED_units_code &time_step_units_code = data_rec->get_time_step_units_code();
/*_______*/
/*_______*/       Element element = 0;
/*_______*/       // need to convert data_rec variable to code element code
/*_______*/       UED_variable_code variable_code = data_rec->get_variable_code();
/*_______*/       int element_index = 0;
/*_______*/       for (int i = 1;element_conversions[i].element_number && !element;i++)
/*_______*/          if (element_conversions[i].var_code == variable_code)
/*_______*/          {
/*_______*/             element = element_conversions[i].element_number;
/*_______*/             element_index = i;
/*_______*/          }
//                  for_time.text_str(for_time_cstr);
/*_______*/       cout << for_time.get_year();
/*_______*/       cout << " " << element_conversions[element_index].description << endl;
/*_______*/       for (int TS_count = 1; TS_count <= num_values; TS_count++)
/*_______*/       {
/*_______*/          if (time_step_units_code == UT_day)
/*_______*/          {  // record is daily resolution
/*_______*/             // add values to Canadian_daily_by_month_data_record list:
 // get Canadian_daily_by_month_data_record from list
/*_______*/             // that can store the data value for the time step
/*_______*/             // (create if necessary)
/*_______*/             float32 value = data_rec->get_value
/*_______*/             (datum_attribute
/*_______*/             ,for_time.get_datetime64());
/*_______*/             if (variable_code == UED_STD_VC_wind_speed.get())
/*_______*/             {  // we need to  convert to from daily values to hourly
/*_______*/                // because  canadian climatological format does not have daily windspeed.
/*_______*/                // Canadian climatological does not have daily windspeed
/*_______*/                // These need to be converted to hourly for the .HLY15 file.

//obs #define m_sec_to_kg_day(m_sec) (m_sec * 86400.0 / 1000.0)

                          float32 value_km_day = value;
/*031221_*/               wind_output << for_time.get_date32() << '\t' << value_km_day << endl;


/*
This is disabled because the current UED indexing is slow and there
may be a lot of records, it currently isn't needed
but I would like to implement it in the future because this
is the only windspeed data in the canadian climatological format
most often used by people.
*/
               float32 windspeed_km_hr = value_km_day / 24.0;
               // Currently we simply divide the daily windspeed into hours.
               for (Hour hour = 0; hour < 24; hour++)
               {
                  Date_time_64 for_hour_time(for_time);
                  for_hour_time.set_HMS(hour,0,0);
                  /*static*/ Canadian_hourly_data_record  *elem_rec = 0;
                     elem_rec = get_day_hourly_record(element,for_hour_time);

   //                   Because the hourly value is calculated from the
   //                   daily value we need to lower the data quality
   //                   (there could already be hourly data in the database which we would not want to override).
            datum_attribute = UED_calculated_from(datum_attribute);           //031218

                  // Set the data value for the time step
                  // assigning attribute as needed:
                  // Canadian Climatological elements are 1 based so hour+1
                  elem_rec->set_value_attribute(hour+1,windspeed_km_hr,datum_attribute);
                  for_hour_time.inc_hour(1);
               }

               for_time.inc_day(1);
            }
            else
            {
               Canadian_daily_by_month_data_record *elem_rec = get_month_daily_record(element,for_time/*.get_datetime64()*/);
               DOM dom = for_time.get_DOM();
               // Set the data value for the time step
               // assigning attribute as needed:
               elem_rec->set_value_attribute(dom,value,datum_attribute);
               for_time.inc_day(1);
            }
         }
         else  if (time_step_units_code == UT_60_minutes)
         {  // record has hourly resolution
            // add values to Canadian_hourly_data_record list
            Canadian_hourly_data_record  *elem_rec = get_day_hourly_record(element,for_time/*.get_datetime64()*/);
            Hour hour = for_time.get_hour();
            float32 value = data_rec->get_value
            (datum_attribute
            ,for_time.get_datetime64());
            // Set the data value for the time step
            // assigning attribute as needed:
                  // Canadian Climatological elements are 1 based so hour+1
            elem_rec->set_value_attribute(hour+1,value,datum_attribute);
            for_time.inc_hour(1);
         }
         else  if (time_step_units_code == UT_15_minutes)
         {  // record is 15 resolution
            // add values to Canadian_15min_data_record lists
            Canadian_15min_data_record  *elem_rec = get_day_15min_record(element,for_time/*.get_datetime64()*/);
            Minutes minutes = for_time.get_minutes();
            float32 value = data_rec->get_value
            (datum_attribute
            ,for_time.get_datetime64());
            // Set the data value for the time step
            // assigning attribute as needed:
            // Canadian Climatological elements are 1 based so increment index by 1
            int16 index_15_min = (minutes / 15) + 1;
            elem_rec->set_value_attribute(index_15_min,value,datum_attribute);
            for_time.inc_minute(15);
         }
#ifdef NYI
031208 Here we could output monthly summaries to the annual record, but it is not needed at this time.
         else  if (time_step_units_code == xxxx)
         { record is daily resolution
            add values to Canadian_annual_data_record list
         }
#endif
      }
      records_exported++; // Currently counting the number of UED records encountered
   }
   if (export_month_daily_records_encountered)
   {
      // Candadian climatological has two
      // similar formats DLY02 and DLY04
      // the DLY04 is generally more reliable/complete
      // DOY02 may have incomplete precipitation
      // So I am exporting as DLY04
      CORN::File_name DLY04_filename(parameters.ued_filename.c_str()); // 060616 (UED_filename);
      DLY04_filename.set_ext(".DLY04");
      ofstream DLY04_file(DLY04_filename.c_str());
      for (int month = 1; month <=12; month++)                                   //040104
         pending_export_month_daily_records[month].write(DLY04_file);
   }
   if (export_day_hourly_records_encountered)
   {
      CORN::File_name HLY15_filename(parameters.ued_filename.c_str()); // 060616 (UED_filename);
      HLY15_filename.set_ext(".HLY15");  // WIND
      ofstream HLY15_file(HLY15_filename.c_str());
      for (int doy = 1; doy <=366; doy++)                                        //040104
      pending_export_day_hourly_records[doy].write(HLY15_file);
   }
   if (export_day_15min_records_encountered) // pending_export_day_15min_records.count())
   {
      CORN::File_name FIF21_filename(parameters.ued_filename.c_str());
      FIF21_filename.set_ext(".FIF21");  // only 15minute precipitation
      ofstream FIF21_file(FIF21_filename.c_str());
      for (int doy = 1; doy <=366; doy++)                                        //040104
      pending_export_day_15min_records[doy].write(FIF21_file);
   }
   //NYI could generate monthly summaries from the daily data
   return records_exported;
}
//______________________________________________________________________________
}

