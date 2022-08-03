#include "USDA/NRCS/RUSLE2/SDR_field_ops.h"

#include <math.h>
#include <string.h>
#include "corn/measure/measures.h"
#include "corn/math/compare.hpp"

#include <iostream>
namespace USDA { namespace NRCS { namespace RUSLE2 {                             //120406
SDR_Field_operations SDR_field_operations;                                       //120406
#ifdef USE_NEW_RUSLE2

#define UNKNOWN_invert  256
#define UNKNOWN_mix     256
#define UNKNOWN_lift    256
#define UNKNOWN_shatter 256
#define UNKNOWN_aerate  256
#define UNKNOWN_compact 256
// ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact}
#else
//______________________________________________________________________________
struct SDR_Field_operation_parameters
{  // The following are from the NRCS_SDR table
   nat16   NRCS_SDR_number_dont_use;                          // field operation number numbers greater than 255 indicate codes we added in CropSyst to accomodate operation not defined by NRCS
   char   *description;
   Disturbance disturbance;                                                      //141023
/*141023
   nat8    invert;
   nat8    mix;
   nat8    lift;
   nat8    shatter;
   nat8    aerate;
   nat8    compact;
*/
};
//______________________________________________________________________________
SDR_Field_operation_parameters SDR_field_operation_parameters_table[] =
{
//NUMBER		                     INVERT	MIX	LIFT	SHATTER	AERATE  COMPACT
 {  0,"unknown"                                                ,0,0,0,0,0,0,Armen_source}
,{  1,"Add mulch"                                              ,0,0,0,0,0,5,Armen_source}
,{  2,"Aerator, field surface, ground driven"                  ,1,1,2,3,4,1,Armen_source}
,{  3,"Aerial seeding"                                         ,0,0,0,0,0,0,Armen_source}
,{  4,"Bale straw or residue"                                  ,0,0,0,0,0,3,Armen_source}
,{  5,"Bed shaper"                                             ,1,1,1,1,1,2,Armen_source}
,{  6,"Bed shaper, 12 in"                                      ,1,1,1,1,1,2,Armen_source}
,{  7,"Bedder, hipper, disk hiller"                            ,5,5,5,5,5,4,Armen_source}
,{  8,"Bedder, hipper, hiller 12 in high"                      ,5,5,5,5,5,4,Armen_source}
,{  9,"Bedder, hipper, hiller 15 in high"                      ,5,5,5,5,5,4,Armen_source}
,{ 10,"Bedder, hipper, hiller 18 in high"                      ,5,5,5,5,5,4,Armen_source}
,{ 11,"Begin growth"                                           ,0,0,0,0,0,0,Armen_source}
,{ 12,"Begin new growth"                                       ,0,0,0,0,0,0,Armen_source}
,{ 13,"Begin weed growth"                                      ,0,0,0,0,0,0,Armen_source}
,{ 14,"Bulldozer, clearing"                                    ,5,5,5,5,5,5,Armen_source}
,{ 15,"Burn residue"                                           ,0,0,0,0,0,0,Armen_source}
,{ 16,"Burn residue, high intensity"                           ,0,0,0,0,0,0,Armen_source}
,{ 17,"Burn residue, low intensity"                            ,0,0,0,0,0,0,Armen_source}
,{ 18,"Chisel, st. pt."                                        ,2,3,4,4,4,2,Armen_source}
,{ 19,"Chisel, st. pt. 12 in deep"                             ,2,3,4,4,4,2,Armen_source}
,{ 20,"Chisel, st. pt. 15 in deep"                             ,2,3,4,4,4,2,Armen_source}
,{ 21,"Chisel, sweep shovel"                                   ,2,3,5,4,4,3,Armen_source}
,{ 22,"Chisel, twisted shovel"                                 ,3,4,5,5,5,2,Armen_source}
,{ 23,"Chop veg. with machete"                                 ,0,1,0,0,1,0,Armen_source}
,{ 24,"Cultipacker, roller"                                    ,2,3,2,5,3,4,Armen_source}
,{ 25,"Cultivate, manually"                                    ,2,2,2,2,2,1,Armen_source}
,{ 26,"Cultivator, field 6-12 in sweeps"                       ,2,2,4,5,4,3,Armen_source}
,{ 27,"Cultivator, field w/ spike points"                      ,3,3,3,4,3,2,Armen_source}
,{ 28,"Cultivator, hipper, disk hiller on beds"                ,4,4,3,5,5,2,Armen_source}
,{ 29,"Cultivator, off bar w/disk hillers on beds"             ,3,2,1,3,3,1,Armen_source}
,{ 30,"Cultivator, row - 1st pass ridge till"                  ,3,2,2,5,5,2,Armen_source}
,{ 31,"Cultivator, row - 2nd pass ridge till"                  ,4,4,3,5,5,2,Armen_source}
,{ 32,"Cultivator, row 1 in ridge"                             ,3,2,2,5,5,2,Armen_source}
,{ 33,"Cultivator, row 3 in ridge"                             ,4,3,2,5,5,2,Armen_source}
,{ 34,"Cultivator, row, high residue"                          ,3,2,2,4,4,1,Armen_source}
,{ 35,"default"                                                ,0,0,0,0,0,0,Armen_source}
,{ 36,"Disk, offset, heavy"                                    ,4,5,4,5,5,4,Armen_source}
,{ 37,"Disk, offset, heavy 12 in depth"                        ,5,5,4,5,5,4,Armen_source}
,{ 38,"Disk, offset, heavy 15 in depth"                        ,5,5,4,5,5,4,Armen_source}
,{ 39,"Disk, tandem heavy primary op."                         ,4,5,4,4,5,4,Armen_source}
,{ 40,"Disk, tandem light finishing"                           ,2,3,3,3,4,3,Armen_source}
,{ 41,"Disk, tandem secondary op."                             ,2,3,3,3,4,3,Armen_source}
,{ 42,"Do all"                                                 ,2,3,2,5,4,4,Armen_source}
,{ 43,"Do all, on beds"                                        ,2,3,2,5,4,4,Armen_source}
,{ 44,"Drill or air seeder single disk openers 7-10 in spac."  ,1,1,0,1,2,1,Armen_source}
,{ 45,"Drill or air seeder, hoe opener in hvy residue"         ,4,3,1,4,3,1,Armen_source}
,{ 46,"Drill or air seeder, hoe/chisel openers 6-12 in spac."  ,5,3,1,4,3,1,Armen_source}
,{ 47,"Drill or airseeder, double disk"                        ,4,3,1,4,3,2,Armen_source}
,{ 48,"Drill or airseeder, double disk opener, w/ fert openers",5,3,3,5,5,2,Armen_source}
,{ 49,"Drill or airseeder, double disk, w/ fluted coulters"    ,5,3,1,4,3,2,Armen_source}
,{ 50,"Drill or airseeder, offset double disk openers"         ,3,1,0,1,2,1,Armen_source}
,{ 51,"Drill, air seeder, sweep or band opener"                ,4,3,3,5,5,2,Armen_source}
,{ 52,"Drill, deep furrow  12 to 18 in spacing"                ,4,3,2,4,3,1,Armen_source}
,{ 53,"Drill, heavy, direct seed, dbl disk opnr"               ,5,3,3,5,5,2,Armen_source}
,{ 54,"Drill, heavy, direct seed, dbl disk opnr w/row cleaners",5,3,3,5,5,2,Armen_source}
,{ 55,"Drill, semi-deep furrow  12 to 18 in spacing"           ,4,3,2,4,3,1,Armen_source}
,{ 56,"Fert applic. anhyd knife 12 in"                         ,2,3,2,3,2,1,Armen_source}
,{ 57,"Fert applic. deep plcmt hvy shnk"                       ,3,3,2,4,2,2,Armen_source}
,{ 58,"Fert applic. surface broadcast"                         ,0,0,0,0,0,5,Armen_source}
,{ 59,"Fert. applic. anhyd knife 30 in"                        ,1,2,1,2,1,1,Armen_source}
,{ 60,"Fert. applic., strip-till 30 in"                        ,2,3,2,3,2,1,Armen_source}
,{ 61,"Furrow diker"                                           ,2,3,2,3,3,2,Armen_source}
,{ 62,"Furrow shaper, torpedo"                                 ,0,0,0,3,0,4,Armen_source}
,{ 63,"Graze, continuous"                                      ,0,1,0,0,0,3,Armen_source}
,{ 64,"Graze, intensive rotational"                            ,0,1,0,0,0,3,Armen_source}
,{ 65,"Graze, rotational"                                      ,0,1,0,0,0,3,Armen_source}
,{ 66,"Graze, stubble or residue"                              ,0,1,0,0,0,3,Armen_source}
,{ 67,"Harrow, coiled tine"                                    ,1,2,0,2,3,3,Armen_source}
,{ 68,"Harrow, heavy"                                          ,2,3,2,2,2,4,Armen_source}
,{ 69,"Harrow, rotary"                                         ,2,3,2,2,2,4,Armen_source}
,{ 70,"Harrow, spike tooth"                                    ,0,2,0,2,3,3,Armen_source}
,{ 71,"Harrow, tine, on beds"                                  ,1,2,0,2,3,3,Armen_source}
,{ 72,"Harvest, banana"                                        ,0,0,0,0,0,1,Armen_source}
,{ 73,"Harvest, banana remove stem"                            ,0,0,0,0,0,5,Armen_source}
,{ 74,"Harvest, broccoli and cauliflower"                      ,0,0,0,0,0,1,Armen_source}
,{ 75,"Harvest, cabbage and head lettuce"                      ,0,0,0,0,0,1,Armen_source}
,{ 76,"Harvest, corn silage with cover crop"                   ,0,0,0,0,0,5,Armen_source}
,{ 77,"Harvest, cotton"                                        ,0,0,0,0,0,5,Armen_source}
,{ 78,"Harvest, cotton and shred"                              ,0,0,0,0,0,5,Armen_source}
,{ 79,"Harvest, cut flowers"                                   ,0,0,0,0,0,1,Armen_source}
,{ 80,"Harvest, forage sorghum"                                ,0,0,0,0,0,5,Armen_source}
,{ 81,"Harvest, grain, grow cover"                             ,0,0,0,0,0,5,Armen_source}
,{ 82,"Harvest, grass or legume seed, leave forage"            ,0,0,0,0,0,3,Armen_source}
,{ 83,"Harvest, grass seed, remove forage"                     ,0,0,0,0,0,3,Armen_source}
,{ 84,"Harvest, hand pick"                                     ,0,0,0,0,0,1,Armen_source}
,{ 85,"Harvest, hand pull"                                     ,0,0,1,0,1,3,Armen_source}
,{ 86,"Harvest, hay, grass"                                    ,0,0,0,0,0,3,Armen_source}
,{ 87,"Harvest, hay, legume"                                   ,0,0,0,0,0,3,Armen_source}
,{ 88,"Harvest, hay, no regrowth"                              ,0,0,0,0,0,3,Armen_source}
,{ 89,"Harvest, kenaf"                                         ,0,0,0,0,0,5,Armen_source}
,{ 90,"Harvest, killing crop"                                  ,0,0,0,0,0,5,Armen_source}
,{ 91,"Harvest, leafy veg."                                    ,0,0,0,0,0,3,Armen_source}
,{ 92,"Harvest, legume seed, remove forage"                    ,0,0,0,0,0,5,Armen_source}
,{ 93,"Harvest, peanut digger"                                 ,5,5,3,5,5,2,Armen_source}
,{ 94,"Harvest, plantains"                                     ,0,0,0,0,0,1,Armen_source}
,{ 95,"Harvest, root crops, digger"                            ,5,5,3,5,5,2,Armen_source}
,{ 96,"Harvest, rootcrops, manually"                           ,2,2,2,2,2,1,Armen_source}
,{ 97,"Harvest, silage"                                        ,0,0,0,0,0,5,Armen_source}
,{ 98,"Harvest, snapper header"                                ,0,0,0,0,0,5,Armen_source}
,{ 99,"Harvest, stripper header"                               ,0,0,0,0,0,5,Armen_source}
,{100,"Harvest, sugarcane, after burning"                      ,0,0,0,0,0,5,Armen_source}
,{101,"Harvest, sugarcane, modern"                             ,0,0,0,0,0,5,Armen_source}
,{102,"Harvest, sugarcane, old type"                           ,0,0,0,0,0,5,Armen_source}
,{103,"Harvest, tobacco, burley"                               ,0,0,0,0,0,1,Armen_source}
,{104,"Harvest, tobacco, flue cured"                           ,0,0,0,0,0,1,Armen_source}
,{105,"Kill crop"                                              ,0,0,0,0,0,3,Armen_source}
,{106,"Knife, windrow dry beans"                               ,0,0,5,5,4,3,Armen_source}
,{107,"Land plane"                                             ,1,1,0,1,0,2,Armen_source}
,{108,"Lister, 40 in"                                          ,4,4,3,5,5,2,Armen_source}
,{109,"Manure injector"                                        ,3,4,3,4,3,4,Armen_source}
,{110,"Manure spreader"                                        ,0,0,0,0,0,5,Armen_source}
,{111,"Middle buster, digger"                                  ,5,5,3,5,5,2,Armen_source}
,{112,"Mower, swather, windrower"                              ,0,0,0,0,0,3,Armen_source}
,{113,"Mulch treader"                                          ,3,3,2,2,3,1,Armen_source}
,{114,"No operation"                                           ,0,0,0,0,0,0,Armen_source}
,{115,"Para-plow or para-till"                                 ,1,2,1,3,3,1,Armen_source}
,{116,"Permeable weed barrier applicator"                      ,2,2,0,2,2,1,Armen_source}
,{117,"Planter, double disk opnr"                              ,1,1,0,1,1,1,Armen_source}
,{118,"Planter, double disk opnr w/fluted coulter"             ,1,1,0,1,1,1,Armen_source}
,{119,"Planter, double disk opnr, 18 in rows"                  ,1,2,0,1,2,1,Armen_source}
,{120,"Planter, in-row subsoiler"                              ,1,2,1,3,3,1,Armen_source}
,{121,"Planter, ridge till"                                    ,3,4,2,3,3,2,Armen_source}
,{122,"Planter, runner opener"                                 ,0,0,0,0,0,1,Armen_source}
,{123,"Planter, small veg seed"                                ,0,0,0,1,1,2,Armen_source}
,{124,"Planter, strip till"                                    ,1,2,1,2,1,1,Armen_source}
,{125,"Planter, sugarcane"                                     ,0,1,0,1,1,3,Armen_source}
,{126,"Planter, transplanter, vegetable"                       ,0,1,0,1,1,3,Armen_source}
,{127,"Planter, transplanter, vegetable, no-till"              ,0,1,0,1,1,3,Armen_source}
,{128,"Planting, broadcast seeder"                             ,0,0,0,0,0,3,Armen_source}
,{129,"Planting, hand 10 percent dist."                        ,0,1,0,0,1,0,Armen_source}
,{130,"Planting, hand 5 percent dist."                         ,0,1,0,0,1,0,Armen_source}
,{131,"Planting, manual"                                       ,0,1,0,0,1,0,Armen_source}
,{132,"Planting, no-til manually"                              ,0,1,0,0,1,0,Armen_source}
,{133,"Plastic mulch applic. 40 inch beds 100 percent cover"   ,2,2,0,2,2,1,Armen_source}
,{134,"Plastic mulch applic. 40 inch beds 75 percent cover"    ,2,2,0,2,2,1,Armen_source}
,{135,"Plastic mulch applic. 48 inch beds 100 percent cover"   ,2,2,0,2,2,1,Armen_source}
,{136,"Plastic mulch applic. 48 inch beds 80 percent cover"    ,2,2,0,2,2,1,Armen_source}
,{137,"Plastic mulch applic. 54 inch beds 100 percent cover"   ,2,2,0,2,2,1,Armen_source}
,{138,"Plastic mulch applic. 54 inch beds 80 percent cover"    ,2,2,0,2,2,1,Armen_source}
,{139,"Plastic mulch applic. 64 inch beds 100 percent cover"   ,2,2,0,2,2,1,Armen_source}
,{140,"Plastic mulch applic. 64 inch beds 85 percent cover"    ,2,2,0,2,2,1,Armen_source}
,{141,"Plastic mulch applicator 100 percent cover"             ,2,2,0,2,2,1,Armen_source}
,{142,"Plastic mulch applicator 40 percent cover"              ,2,2,0,2,2,1,Armen_source}
,{143,"Plastic mulch applicator 75 percent cover"              ,2,2,0,2,2,1,Armen_source}
,{144,"Plastic mulch, 05 percent removal"                      ,2,2,0,2,2,1,Armen_source}
,{145,"Plastic mulch, 10 percent removal"                      ,2,2,0,2,2,1,Armen_source}
,{146,"Plastic mulch, 25 percent removal"                      ,2,2,0,2,2,1,Armen_source}
,{147,"Plastic mulch, 50 percent  removal"                     ,2,2,0,2,2,1,Armen_source}
,{148,"Plastic mulch, remove"                                  ,2,2,0,2,2,1,Armen_source}
,{149,"Plow, disk"                                             ,4,5,4,4,5,4,Armen_source}
,{150,"Plow, moldboard"                                        ,5,5,5,5,5,4,Armen_source}
,{151,"Plow, moldboard, conservation"                          ,4,5,5,4,5,4,Armen_source}
,{152,"Plow, moldboard, up hill"                               ,3,5,5,4,5,4,Armen_source}
,{153,"Plow, reversable"                                       ,5,5,5,5,5,4,Armen_source}
,{154,"Pruning"                                                ,0,0,0,0,0,0,Armen_source}
,{155,"Regrow"                                                 ,0,0,0,0,0,0,Armen_source}
,{156,"Residue, row cleaner"                                   ,2,3,1,2,2,2,Armen_source}
,{157,"Rodweeder"                                              ,2,3,1,1,3,2,Armen_source}
,{158,"Roller, corrugated packer"                              ,2,1,0,2,2,4,Armen_source}
,{159,"Roller, on beds"                                        ,0,0,0,1,0,2,Armen_source}
,{160,"Roller, residue"                                        ,0,1,0,0,0,3,Armen_source}
,{161,"Roller, smooth"                                         ,0,1,0,0,0,3,Armen_source}
,{162,"Root rake"                                              ,1,3,2,3,3,3,Armen_source}
,{163,"Rotary hoe"                                             ,1,1,1,4,3,1,Armen_source}
,{164,"Rototiller, field"                                      ,5,5,5,5,5,4,Armen_source}
,{165,"Rototiller, field, add residue"                         ,5,5,5,5,5,4,Armen_source}
,{166,"Rototiller, row cult add residue"                       ,5,5,5,5,5,4,Armen_source}
,{167,"Rototiller, row cultivator"                             ,5,5,5,5,5,4,Armen_source}
,{168,"Sand fighter"                                           ,3,3,3,4,3,2,Armen_source}
,{169,"Seedbed finisher"                                       ,2,3,2,5,3,4,Armen_source}
,{170,"Shredder, flail or rotary"                              ,0,0,0,0,0,3,Armen_source}
,{171,"Shredder, rotary, regrow veg"                           ,0,0,0,0,0,3,Armen_source}
,{172,"Shredder, rotary, remove residue"                       ,0,0,0,0,0,3,Armen_source}
,{173,"Sprayer, kill crop"                                     ,0,0,0,0,0,3,Armen_source}
,{174,"Sprayer, post emergence"                                ,0,0,0,0,0,3,Armen_source}
,{175,"Stalk puller"                                           ,2,1,0,1,1,1,Armen_source}
,{176,"Striptiller w/middlebuster on beds"                     ,4,4,3,4,4,4,Armen_source}
,{177,"Subsoiler"                                              ,1,2,2,4,5,1,Armen_source}
,{178,"Subsoiler bedder (ripper/hipper)"                       ,5,5,5,5,5,4,Armen_source}
,{179,"Subsoiler ripper, 24 to 40 in. deep"                    ,1,2,2,5,5,1,Armen_source}
,{180,"Sweep plow 20-40 in wide"                               ,0,0,5,5,4,3,Armen_source}
,{181,"Sweep plow wider  than 40 in w/ mulch treader"          ,0,0,5,5,3,3,Armen_source}
,{182,"Sweep plow, wider than 40 in"                           ,0,0,5,5,3,3,Armen_source}
,{183,"Water mulch; off"                                       ,0,0,0,0,0,5,Armen_source}
,{184,"Water mulch; on"                                        ,0,0,0,0,0,5,Armen_source}
,{185,"Weed control, manual hoe"                               ,0,1,0,0,1,0,Armen_source}
,{999,   ""                                                    ,0,0,0,0,0,0,Armen_source}
};
#endif
//______________________________________________________________________________
#define NA 0
// NA = not applicable
#define MSG 0
// MSG = Missing
#define NO false
#define YES true
Field_operation_parameters
field_operation_parameters[]=
{
// Note if you make any changes to this table,
// dont forget the modify the file: NRCS field operations.xls
//                                                                                             speed   |      |    depth  |      |RidgeRough|surf|residue flatten         |    residue burial             |    Residue resurfacing                  |Kill|
//                                                                                ICASA     rec min max|intens|rec min max|height|init final|dist|fragmodtononfrwoodystony| fragilmod.tononfrawoody stony | fragilmod.tononfrawoody stony           |veg |
// Operation                                                                      code      MPH MPH MPH|fracti|   inch    | inch |  inch    |   %|    ratio               |         ratio                 |       faction                           |    |   effect     |
#ifdef USE_NEW_RUSLE2
  {  0,"unknown"                                                                 ,"unknwn",{0.0,0.0,0.0}, NA ,{NA ,NA ,NA },NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },        { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT,{/*SDR*/0,0,0,0,0,0}}

/* This is a new composite
,{169,"Seedbed finisher"                                       ,2,3,2,5,3,4}
The following were missing / removed from RULSE2 database
,{ 95,"Harvest, root crops, digger" ,{5,5,3,5,5,2}
//obs ,{ 93,"Harvest, peanut digger" ,{5,5,3,5,5,2}
*/
// Entries marked with RLN indicate the disturbance numbers are unknown
// Roger entered values corresponding to similarly named operations.

, {1,"Install Compost Sock"                                                      ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {2,"Install Silt Fence"                                                        ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {3,"Install Straw Bale",                                                        "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {4,"Remove Compost Sock",                                                       "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {5,"Remove Silt Fence",                                                         "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {6,"Remove Straw Bale",                                                         "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {7,"Add PAM",                                                                   "unknwn",{4.0,3.0,8.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {8,"Add mulch",                                                                 "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {9,"Aerator, field surface, ground driven"                                     ,"unknwn",{6.0,3.5,6.5},0.00,{0.0,3.0,8.0},0.0,{0.60,0.00}, 50,{0.85,0.70,0.60,0.50,1.00},  {0.25,0.15,0.13,0.13,0.19},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/1,1,2,3,4,1,Armen_source}}
, {10,"Aerator, field surface, ground driven 0 degree offset",                    "unknwn",{6.0,3.5,6.5},0.00,{0.0,3.0,8.0},0.0,{0.60,0.00}, 30,{0.85,0.70,0.60,0.50,1.00},  {0.2 ,0.12,0.1 ,0.1 ,0.15},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {11,"Aerator, field surface, ground driven 10 degree offset",                   "unknwn",{6.0,3.5,6.5},0.00,{0.0,3.0,8.0},0.0,{0.60,0.00},100,{0.85,0.70,0.60,0.50,1.00},  {0.35,0.3 ,0.25,0.15,0.25},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {12,"Aerator, field surface, ground driven 5 degree offset",                    "unknwn",{6.0,3.5,6.5},0.00,{0.0,3.0,8.0},0.0,{0.60,0.00}, 50,{0.85,0.70,0.60,0.50,1.00},  {0.25,0.15,0.13,0.13,0.19},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {13,"Aerator, single drum, lugs, angle 0",                                      "unknwn",{6.0,3.0,11.},1.00,{0.0,3.0,6.0},0.0,{0.60,0.00}, 33,{0.95,0.90,0.85,0.90,1.00},  {0.2 ,0.12,0.1 ,0.1 ,0.15},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {14,"Aerator, tandem drum, lugs, angle 10",                                     "unknwn",{6.0,3.0,11.},1.00,{0.0,3.0,6.0},0.0,{0.60,0.00},100,{0.95,0.90,0.90,0.90,1.00},  {0.35,0.3 ,0.25,0.15,0.25},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {15,"Aerator, tandem drum, lugs, angle 5",                                      "unknwn",{6.0,3.0,11.},1.00,{0.0,3.0,6.0},0.0,{0.60,0.00}, 80,{0.95,0.90,0.90,0.90,1.00},  {0.25,0.15,0.13,0.13,0.19},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {16,"Aerial interseeding",                                                      "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {17,"Aerial seeding",                                                           "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,0,Armen_source}}
, {18,"BFM applicaton",                                                           "unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {19,"Bale Corn husk, cob and chaff windrows",                                   "unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.12,0.12,0.12,0.12,0.12},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {20,"Bale Corn stalk strips",                                                   "unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.12,0.12,0.12,0.12,0.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {21,"Bale combine windrows",                                                    "unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.12,0.12,0.12,0.12,0.12},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {22,"Bale corn stover",                                                         "unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.12,0.12,0.12,0.12,0.12},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {23,"Bale straw or residue",                                                    "unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.12,0.12,0.12,0.12,0.12},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {24,"Bed shaper",                                                               "unknwn",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},8.0,{0.60,0.24}, 75,{0.50,0.45,0.40,0.30,1.00},  {0.375,0.3,0.225,0.195,0.285},          {0.02,0.02,0.02,0.07,0.02}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/1,1,1,1,1,2,Armen_source}}
, {25,"Bed shaper high disturbance",                                              "unknwn",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},8.0,{0.60,0.24},100,{0.50,0.45,0.40,0.30,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.02,0.02,0.02,0.07,0.02}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {26,"Bed shaper, 12 in",                                                        "unknwn",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},12.,{0.60,0.24}, 75,{0.95,0.80,0.75,0.30,1.00},  {0.375,0.3,0.225,0.195,0.285},          {0.02,0.02,0.02,0.07,0.02}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/1,1,1,1,1,2,Armen_source}}
, {27,"Bed shaper, 12 in, low flattening",                                        "unknwn",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},12.,{0.60,0.24}, 75,{0.10,0.10,0.10,0.10,1.00},  {0.375,0.3,0.225,0.195,0.285},          {0.02,0.02,0.02,0.07,0.02}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/1,1,1,1,1,2,Armen_source}}
, {28,"Bed shaper, low flattening, high disturbance",                             "unknwn",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},8.0,{0.60,0.24},100,{0.10,0.10,0.10,0.10,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.02,0.02,0.02,0.07,0.02}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/1,1,1,1,1,2,Roger_source}}
, {29,"Bedder, hipper, disk hiller",                                              "TI017" ,{5.0,3.0,6.0},0.90,{0.0,2.0,5.0},8.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.85,0.5,0.6},                                       {0.02,0.02,0.02,0.05,0.03}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,5,5,5,5,4,Armen_source}}
, {30,"Bedder, hipper, hiller 12 in high",                                        "TI017" ,{5.0,3.0,6.0},1.00,{0.0,4.0,8.0},12.,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.85,0.5,0.6},                                       {0.02,0.02,0.02,0.05,0.03}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/5,5,5,5,5,4,Armen_source}}
, {31,"Bedder, hipper, hiller 15 in high",                                        "TI017" ,{5.0,3.0,6.0},1.00,{0.0,5.0,9.0},15.,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.9,0.5,0.6},                                        {0.02,0.02,0.02,0.05,0.03}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/5,5,5,5,5,4,Armen_source}}
, {32,"Bedder, hipper, hiller 18 in high",                                        "TI017" ,{5.0,3.0,6.0},1.00,{0.0,6.0,10.},18.,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.9,0.5,0.6},                                        {0.02,0.02,0.02,0.05,0.03}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/5,5,5,5,5,4,Armen_source}}
, {33,"Begin growth",                                                             "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                     { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,0,Armen_source}}
, {34,"Begin new growth",                                                         "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                     { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,0,Armen_source}}
, {35,"Begin weed growth",                                                        "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                     { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,0,Armen_source}}
, {36,"Bulldozer, clearing/cutting",                                              "unknwn",{2.0,1.0,3.0},1.00,{0.0,3.0,10.},0.0,{0.80,0.00},  0,{0.95,0.95,0.95,0.95,1.00},  {0.9,0.9,0.9,0.9,0.9},                                          {0,0,0,0,0}                      ,YES,INVERSION_SOME_MIXING ,{/*SDR*/5,5,5,5,5,5,Roger_source}}
, {37,"Bulldozer, clearing/cutting light",                                        "unknwn",{2.0,1.0,3.0},1.00,{0.0,0.0,3.0},2.0,{0.60,0.00}, 85,{0.95,0.95,0.95,0.95,1.00},  {0.646,0.5695,0.493,0.3655,0.7225},     {0,0,0,0,0}                      ,YES,COMPRESSION           ,{/*SDR*/5,5,5,5,5,5,Roger_source}}
, {38,"Bulldozer, filling/leveling",                                              "unknwn",{2.0,1.0,3.0},1.00,{0.0,0.0,4.0},2.0,{0.30,0.00},  0,{1.00,0.99,0.99,0.95,0.99},  {0.99,0.99,0.99,0.95,0.9},                                      {0,0,0,0,0}                      ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,5,5,5,5,5,Roger_source}}
, {39,"Burn residue",                                                             "unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                     { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {40,"Burn residue, high intensity"                                             ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                    { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {41,"Burn residue, low intensity"                                              ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                   { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {42,"Burn residue, mod. high intensity"                                        ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                   { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {43,"Burn residue, moderate intensity"                                         ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                   { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {44,"Burn sugarcane"                                                           ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                   { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{/*SDR*/UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
//NYI , {45,"Burrowing, heavy, Prairie dog",                                      "unknwn",{1.0,1.0,1.0},1.00,{0.0,12.0,0.0},5.0,{0.50,0.00},70,{ NA , NA , NA , NA , NA },  {0.7,0.6,0.5,0.4,0.5},                                          {0,0,0,0,0}                      ,NO ,}
//NYI , {46,"Burrowing, light, Prairie dog",                                      "unknwn",{1.0,1.0,1.0},0.10,{0.0,12.0,0.0},5.0,{0.50,0.00},15,{ NA , NA , NA , NA , NA },  {0.15,0.15,0.12,0.5,0.5},                                       {0,0,0,0,0}                      ,NO ,}
//NYI , {47,"Burrowing, moderate, Prairie dog",                                   "unknwn",{1.0,1.0,1.0},1.00,{0.0,12.0,0.0},5.0,{0.50,0.00},45,{ NA , NA , NA , NA , NA },  {0.45,0.4,0.35,0.25,0.4},                                       {0,0,0,0,0}                      ,NO ,}
, {48,"Chisel, 12-16 in. low crown sweep 3 to 4  in. depth"                      ,"TI004" ,{5.5,4.0,7.0},0.70,{0.0,2.0,5.0},2.0,{0.40,0.24},100,{0.50,0.30,0.20,0.15,1.00},  {0.4,0.35,0.3,0.2,0.85},                                        {0.03,0.04,0.06,0.07,0.03}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {49,"Chisel, st. pt."                                                          ,"TI005" ,{5.0,3.5,6.5},0.75,{0.0,4.0,8.0},3.0,{1.50,0.24},100,{0.60,0.40,0.25,0.10,1.00},  {0.76,0.68,0.58,0.5,0.9},                                     {0.05,0.06,0.07,0.2,0.05}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/2,3,4,4,4,2,Armen_source}}
, {50,"Chisel, st. pt. 12 in deep"                                               ,"TI005" ,{4.0,3.0,5.0},0.75,{0.0,10.,14.},4.0,{1.70,0.24},100,{0.70,0.50,0.40,0.25,1.00},  {0.8,0.7,0.6,0.6,0.9},                                          {0.05,0.06,0.07,0.2,0.05}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/2,3,4,4,4,2,Armen_source}}
, {51,"Chisel, st. pt. 15 in deep"                                               ,"TI005" ,{4.0,3.0,5.0},0.75,{0.0,12.,18.},5.0,{1.80,0.24},100,{0.75,0.60,0.50,0.40,1.00},  {0.85,0.75,0.65,0.65,0.9},                                      {0.05,0.06,0.07,0.2,0.05}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/2,3,4,4,4,2,Armen_source}}
, {52,"Chisel, st. pt. 5 in deep"                                                ,"TI005" ,{5.0,3.5,6.5},0.75,{0.0,4.0,6.0},3.0,{1.50,0.24},100,{0.60,0.40,0.25,0.10,1.00},  {0.65,0.55,0.45,0.5,0.9},                                       {0.05,0.06,0.07,0.2,0.05}        ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {53,"Chisel, sweep shovel"                                                     ,"TI004" ,{5.0,3.5,6.5},0.85,{0.0,5.0,9.0},3.0,{1.20,0.24},100,{0.50,0.30,0.20,0.15,1.00},  {0.6,0.45,0.3,0.2,0.6},                                         {0.05,0.06,0.07,0.15,0.05}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {54,"Chisel, sweep shovel 5 in. depth"                                         ,"TI004" ,{5.0,3.5,6.5},0.85,{0.0,4.0,7.0},3.0,{1.20,0.24},100,{0.50,0.30,0.20,0.15,1.00},  {0.55,0.4,0.3,0.2,0.6},                                         {0.05,0.06,0.07,0.15,0.05}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/2,3,5,4,4,3,Roger_source}}
, {55,"Chisel, twisted shovel"                                                   ,"TI006" ,{5.0,3.5,6.5},0.90,{0.0,4.0,8.0},6.0,{1.90,0.24},100,{0.85,0.80,0.70,0.60,1.00},  {0.9,0.8,0.75,0.6,0.93},                                        {0.05,0.06,0.07,0.15,0.05}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/3,4,5,5,5,2,Armen_source}}
, {56,"Chop veg. with machete"                                                   ,"unknwn",{1.0,1.0,1.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.85,0.80,0.75,0.75,1.00},  { NA , NA , NA , NA , NA },                                     { NA , NA , NA , NA , NA }       ,NO ,MIXING_RLN            ,{/*SDR*/0,1,0,0,1,0,Armen_source}}
, {57,"Coulter caddy, dbl gang w/ fluted coulters"                               ,"unknwn",{6.0,5.0,8.0},0.40,{0.0,2.0,4.0},2.0,{0.30,0.24},100,{0.95,0.85,0.75,0.15,1.00},  {0.2,0.18,0.15,0.1,1},                                          {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {58,"Coulter caddy, w/ fluted coulters"                                        ,"unknwn",{6.0,5.0,8.0},0.40,{0.0,1.5,2.5},2.0,{0.30,0.24}, 55,{0.65,0.50,0.45,0.15,1.00},  {0.1925,0.1375,0.11,0.055,0.11},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {59,"Coulter caddy, with smooth coulters"                                      ,"unknwn",{6.0,5.0,8.0},0.40,{0.0,1.5,2.5},0.5,{0.30,0.24}, 25,{0.65,0.50,0.45,0.15,1.00},  {0.1925,0.1375,0.11,0.055,0.11},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING                ,{UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {60,"Cover crop underseeder"                                                   ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},1.0,{0.30,0.24}, 10,{0.60,0.40,0.35,0.15,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.05,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {61,"Cultivate, manually"                                                      ,"unknwn",{1.0,1.0,1.0},0.90,{0.0,0.0,6.0},0.0,{0.80,0.24},100,{0.90,0.80,0.70,0.50,1.00},  {0.5,0.3,0.25,0.1,0.1},                                         {0.02,0.02,0.02,0.02,0.02}       ,YES,INVERSION_MIXING_RLN /*UNSPECIFIED_EFFECT   */ ,{UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {62,"Cultivate, manually, low intensity"                                       ,"unknwn",{1.0,1.0,1.0},0.90,{0.0,0.0,6.0},0.0,{0.80,0.24}, 50,{0.90,0.80,0.70,0.50,1.00},  {0.5,0.3,0.25,0.1,0.1},                                         {0.02,0.02,0.02,0.02,0.02}       ,YES,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,2,2,2,1,Roger_source} }
, {63,"Cultivate, manually, moderate intensity"                                  ,"unknwn",{1.0,1.0,1.0},0.90,{0.0,0.0,6.0},0.0,{0.80,0.24}, 75,{0.90,0.80,0.70,0.50,1.00},  {0.5,0.3,0.25,0.1,0.1},                                         {0.02,0.02,0.02,0.02,0.02}       ,YES,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,2,2,2,1,Roger_source} }
, {64,"Cultivate, rows manually"                                                 ,"unknwn",{1.0,1.0,1.0},0.90,{0.0,0.0,6.0},0.0,{0.80,0.24},100,{ NA , NA , NA , NA , NA },  {0.5,0.3,0.25,0.1,0.1},                                         {0.02,0.02,0.02,0.02,0.02}       ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,2,2,2,1,Roger_source}}
, {65,"Cultivator, between beds, add residue"                                    ,"unknwn",{5.0,3.0,6.0},0.90,{0.0,2.0,4.0},8.0,{0.60,0.24}, 50,{1.00,0.90,0.90,0.50,1.00},  {0.57,0.5025,0.435,0.3225,0.6375},      {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {66,"Cultivator, field 6-12 in shovels C"                                      ,"unknwn",{6.0,3.0,8.0},0.50,{0.0,2.0,6.0},2.0,{0.60,0.24},100,{0.80,0.70,0.40,0.30,1.00},  {0.72,0.61,0.52,0.2,0.85},                                      {0.05,0.06,0.07,0.2,0.05}        ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {67,"Cultivator, field 6-12 in sweeps"                                         ,"TI011" ,{5.0,3.5,6.5},0.40,{0.0,2.0,6.0},2.0,{0.60,0.24},100,{0.70,0.40,0.30,0.20,1.00},  {0.4,0.35,0.3,0.2,0.85},                                        {0.05,0.06,0.07,0.2,0.05}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/2,2,4,5,4,3,Armen_source}}
, {68,"Cultivator, field w/ spike points"                                        ,"TI018" ,{6.0,3.0,8.0},0.50,{0.0,2.0,6.0},2.0,{0.80,0.24},100,{0.80,0.70,0.40,0.30,1.00},  {0.5,0.4,0.35,0.2,0.85},                                        {0.05,0.06,0.07,0.2,0.05}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/3,3,3,4,3,2,Armen_source}}
, {69,"Cultivator, flame"                                                        ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                     { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {70,"Cultivator, hipper, disk hiller on beds"                                  ,"unknwn",{5.0,3.0,6.0},0.90,{0.0,1.0,4.0},8.0,{0.60,0.24}, 50,{1.00,0.90,0.90,0.50,1.00},  {0.57,0.5025,0.435,0.3225,0.6375},      {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/4,4,3,5,5,2,Armen_source}}
, {71,"Cultivator, off bar w/disk hillers on beds"                               ,"unknwn",{5.0,2.0,5.5},0.50,{0.0,2.0,4.0},8.0,{0.80,0.24}, 65,{0.70,0.30,0.30,0.10,1.00},  {0.494,0.4355,0.377,0.2795,0.5525},     {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/3,2,1,3,3,1,Armen_source}}
, {72,"Cultivator, rotary"                                                       ,"unknwn",{4.0,2.0,5.5},0.00,{0.0,1.0,2.0},1.5,{0.40,0.00}, 85,{0.80,0.75,0.70,0.50,1.00},  {0.4,0.35,0.3,0.4,0.73},                {0.01,0.01,0.01,0.07,0.02}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {73,"Cultivator, rotary on beds"                                               ,"unknwn",{4.0,2.0,5.5},0.00,{0.0,1.0,2.0},8.0,{0.40,0.00}, 85,{0.80,0.75,0.70,0.50,1.00},  {0.4,0.35,0.3,0.4,0.73},                {0.01,0.01,0.01,0.07,0.02}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {74,"Cultivator, row - 1st pass ridge till"                                    ,"TI012" ,{5.0,3.5,6.5},0.75,{0.0,1.0,4.0},3.0,{0.70,0.24}, 90,{0.80,0.70,0.70,0.40,1.00},  {0.684,0.603,0.522,0.387,0.765},        {0.04,0.04,0.04,0.06,0.04}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/3,2,2,5,5,2,Armen_source}}
, {75,"Cultivator, row - 2nd pass ridge till"                                    ,"TI013" ,{5.0,3.5,6.5},0.75,{0.0,2.0,4.0},6.0,{0.70,0.24},100,{0.80,0.70,0.70,0.40,1.00},  {0.95,0.92,0.85,0.5,0.6},               {0.02,0.02,0.02,0.05,0.03}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/4,4,3,5,5,2,Armen_source}}
, {76,"Cultivator, row 1 in ridge"                                               ,"TI012" ,{5.0,2.0,5.5},0.00,{0.0,2.0,4.0},1.0,{0.30,0.00}, 75,{0.70,0.30,0.30,0.10,1.00},  {0.57,0.5025,0.435,0.3225,0.6375},      {0,0,0,0,0}                      ,NO ,UNSPECIFIED_EFFECT    ,{/*SDR*/3,2,2,5,5,2,Armen_source}}
, {77,"Cultivator, row 3 in ridge"                                               ,"TI012" ,{5.0,2.0,5.5},0.50,{0.0,2.0,4.0},3.0,{0.60,0.24}, 90,{0.70,0.30,0.30,0.10,1.00},  {0.684,0.603,0.522,0.387,0.765},        {0.04,0.04,0.04,0.06,0.04}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/4,3,2,5,5,2,Armen_source}}
, {78,"Cultivator, row between beds"                                             ,"unknwn",{5.0,2.0,5.5},0.50,{0.0,2.0,4.0},8.0,{0.80,0.24}, 65,{0.70,0.30,0.30,0.10,1.00},  {0.494,0.4355,0.377,0.2795,0.5525},     {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {79,"Cultivator, row, high residue"                                            ,"unknwn",{5.0,2.0,6.0},0.50,{0.0,2.0,4.0},1.0,{0.80,0.24}, 50,{0.70,0.30,0.30,0.10,1.00},  {0.25,0.2,0.15,0.13,0.19},                                      {0.04,0.04,0.04,0.06,0.04}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/3,2,2,4,4,1,Armen_source}}
, {80,"Detasseler, seed corn"                                                    ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                     { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {81,"Disk, inter row strips"                                                   ,"unknwn",{5.0,3.0,6.0},0.65,{0.0,2.0,4.0},1.0,{0.60,0.24}, 85,{0.85,0.70,0.60,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},                                      {0.02,0.04,0.02,0.05,0.02}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {82,"Disk, offset, heavy"                                                      ,"TI007" ,{5.0,3.0,6.0},1.00,{0.0,4.0,7.0},4.0,{1.50,0.24},100,{1.00,0.90,0.80,0.50,1.00},  {0.95,0.85,0.8,0.6,0.95},                                       {0.05,0.06,0.07,0.08,0.05}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,5,4,5,5,4,Armen_source}}
, {83,"Disk, offset, heavy 12 in depth"                                          ,"TI007" ,{5.0,3.0,6.0},1.00,{0.0,10.0,14},5.0,{1.70,0.24},100,{1.00,0.90,0.80,0.50,1.00},  {0.99,0.9,0.85,0.8,0.95},                                       {0.025,0.04,0.055,0.09,0.04}     ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,5,4,5,5,4,Armen_source}}
, {84,"Disk, offset, heavy 15 in depth"                                          ,"TI007" ,{4.0,2.0,5.0},1.00,{0.0,12.0,18},6.0,{1.90,0.24},100,{1.00,0.90,0.80,0.50,1.00},  {0.99,0.98,0.98,0.85,0.97},                                     {0.01,0.02,0.04,0.1,0.02}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,5,4,5,5,4,Armen_source}}
, {85,"Disk, oxen, strip 30 pct disturb"                                         ,"unknwn",{2.0,1.0,3.0},0.85,{0.0,3.0,8.0},4.0,{0.60,0.24}, 30,{0.95,0.80,0.70,0.50,1.00},  {0.85,0.75,0.7,0.5,0.6},                                        {0.02,0.02,0.02,0.05,0.05}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {86,"Disk, oxen, strip 60 pct disturb"                                         ,"unknwn",{2.0,1.0,3.0},0.85,{0.0,3.0,6.0},4.0,{0.60,0.00}, 60,{0.95,0.80,0.70,0.50,1.00},  {0,0,0,0,0},                                                    {0,0,0,0,0}                      ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {87,"Disk, single gang"                                                        ,"TI009" ,{5.0,3.0,6.0},0.50,{0.0,2.0,4.0},1.0,{0.60,0.24},100,{0.85,0.70,0.60,0.50,1.00},  {0.6,0.5,0.4,0.4,0.6},                                          {0.01,0.02,0.03,0.03,0.02}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {88,"Disk, tandem heavy primary op."                                           ,"TI009" ,{5.0,3.0,6.0},1.00,{0.0,4.0,7.0},4.0,{1.50,0.24},100,{1.00,0.90,0.80,0.50,1.00},  {0.95,0.85,0.8,0.6,0.95},                                       {0.05,0.06,0.07,0.08,0.05}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,5,4,4,5,4,Armen_source}}
, {89,"Disk, tandem light finishing"                                             ,"TI009" ,{5.0,3.0,6.0},0.65,{0.0,2.0,4.0},1.0,{0.60,0.24},100,{0.85,0.70,0.60,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},                                      {0.02,0.04,0.02,0.05,0.02}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/3,3,3,4,4,3,Stewart_source}}
, {90,"Disk, tandem secondary op."                                               ,"TI010" ,{5.0,3.0,6.0},0.75,{0.0,3.0,6.0},2.0,{0.60,0.24},100,{0.85,0.70,0.60,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},                                      {0.02,0.04,0.02,0.05,0.02}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,3,3,4,4,3,Stewart_source}}
, {91,"Dozer track walking"                                                      ,"unknwn",{2.0,1.0,3.0},0.90,{0.0,1.0,2.0},2.0,{0.32,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.05,0.05,0.05,0.05,0.05},                                     {0.01,0.01,0.01,0.01,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {92,"Drill or air seeder single disk openers 7-10 in spac."                    ,"TI031" ,{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},1.0,{0.30,0.24}, 15,{0.60,0.40,0.35,0.15,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.05,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,1,0,1,2,1,Armen_source}}
, {93,"Drill or air seeder single disk openers, + fert. opnrs 7-10 in spac."     ,"TI031" ,{5.0,3.5,6.5},0.60,{0.0,2.0,4.0},2.0,{0.30,0.24}, 35,{0.65,0.50,0.45,0.15,1.00},  {0.1225,0.0875,0.07,0.035,0.07},        {0.01,0.01,0.01,0.05,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,1,0,1,2,1,Roger_source}}
, {94,"Drill or air seeder tee slot openers 7-10 in spac."                       ,"TI031",{5.0,3.5,6.5},0.40,{0.0,1.0,3.0},0.5,{0.30,0.24}, 15,{0.60,0.40,0.35,0.15,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.005,0.005,0.005,0.005,0.005}  ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {95,"Drill or air seeder, combo single disk-hoe openers, 10 in spac"           ,"TI031",{6.0,4.0,7.0},0.60,{0.0,2.0,4.0},3.0,{0.50,0.24}, 70,{0.65,0.50,0.45,0.15,1.00},  {0.85,0.7,0.6,0.5,0.5},                 {0.01,0.01,0.01,0.03,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {96,"Drill or air seeder, hoe opener in hvy residue"                           ,"TI032",{5.0,3.5,6.5},0.80,{0.0,3.0,6.0},3.0,{0.50,0.24}, 65,{0.60,0.40,0.30,0.30,1.00},  {0.325,0.26,0.195,0.169,0.247},         {0.01,0.01,0.01,0.03,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,3,1,4,3,1,Armen_source}}
, {97,"Drill or air seeder, hoe/chisel openers 12-15 in spac."                   ,"TI032",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},3.0,{0.50,0.24}, 80,{0.60,0.40,0.30,0.30,1.00},  {0.4,0.32,0.24,0.208,0.304},            {0.01,0.01,0.01,0.03,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {98,"Drill or air seeder, hoe/chisel openers 6-12 in spac."                    ,"TI032",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},3.0,{0.50,0.24}, 90,{0.60,0.40,0.30,0.30,1.00},  {0.45,0.36,0.27,0.234,0.342},           {0.01,0.01,0.01,0.03,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,3,1,4,3,1,Armen_source}}
, {99,"Drill or air seeder, paired, opposing single disk openers 6x9 in spac."   ,"TI032",{8.0,6.0,12.},0.40,{0.0,1.0,3.0},0.5,{0.30,0.24}, 80,{0.60,0.40,0.35,0.15,1.00},  {0.2975,0.2125,0.17,0.085,0.17},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {100,"Drill or airseeder, dble disk opnr w/ fluted coult 5x10 paired row"      ,"TI032",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.30,0.24}, 75,{0.60,0.40,0.35,0.15,1.00},  {0.2625,0.1875,0.15,0.075,0.15},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {101,"Drill or airseeder, double disk"                                         ,"TI025" ,{5.0,3.5,6.5},0.40,{0.0,1.0,2.0},1.0,{0.30,0.24}, 65,{0.60,0.40,0.35,0.15,1.00},  {0.2275,0.1625,0.13,0.065,0.13},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,3,1,4,3,2,Armen_source}}
, {102,"Drill or airseeder, double disk opener, w/ fert openers"                 ,"TI025" ,{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.30,0.24}, 85,{0.65,0.50,0.45,0.15,1.00},  {0.2975,0.2125,0.17,0.085,0.17},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,3,3,5,5,2,Armen_source}}
, {103,"Drill or airseeder, double disk, w/ fluted coulters"                     ,"TI025" ,{5.0,3.5,6.5},0.40,{0.0,1.5,2.5},2.0,{0.30,0.24}, 55,{0.65,0.50,0.45,0.15,1.00},  {0.1925,0.1375,0.11,0.055,0.11},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,3,1,4,3,2,Armen_source}}
, {104,"Drill or airseeder, offset double disk openers"                          ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},1.0,{0.30,0.24}, 25,{0.40,0.25,0.20,0.10,1.00},  {0.0875,0.0625,0.05,0.025,0.05},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/3,1,0,1,2,1,Armen_source}}
, {105,"Drill, air seeder, 4 inch stealth openers on 12 in spac"                 ,"unknwn",{5.0,3.5,6.5},0.50,{0.0,2.0,4.0},2.0,{0.60,0.24}, 60,{0.70,0.40,0.30,0.10,1.00},  {0.3,0.24,0.18,0.156,0.228},            {0.04,0.04,0.04,0.06,0.04}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {106,"Drill, air seeder, 6 inch stealth openers on 12 in spac"                 ,"unknwn",{5.0,3.5,6.5},0.50,{0.0,1.5,6.0},3.0,{0.60,0.24}, 80,{0.70,0.40,0.30,0.10,1.00},  {0.3,0.24,0.18,0.156,0.228},            {0.04,0.04,0.04,0.06,0.04}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {107,"Drill, air seeder, sweep or band opener"                                 ,"unknwn",{5.0,3.5,6.5},0.50,{0.0,2.0,4.0},2.0,{0.60,0.24}, 60,{0.70,0.40,0.30,0.10,1.00},  {0.3,0.24,0.18,0.156,0.228},            {0.04,0.04,0.04,0.06,0.04}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,3,3,5,5,2,Armen_source}}
, {108,"Drill, deep furrow  12 to 18 in spacing"                                 ,"TI026" ,{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},4.0,{0.50,0.24}, 90,{0.80,0.60,0.50,0.40,1.00},  {0.45,0.36,0.27,0.234,0.342},           {0.03,0.03,0.04,0.1,0.05}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,3,2,4,3,1,Armen_source}}
, {109,"Drill, deep furrow  7 to 10 in spacing"                                  ,"TI026" ,{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},4.0,{0.50,0.24}, 95,{0.85,0.70,0.60,0.50,1.00},  {0.6,0.5,0.4,0.5,0.9},                  {0.05,0.06,0.07,0.2,0.05}        ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {110,"Drill, double disk, 7-8 in packer C"                                     ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},1.0,{0.30,0.24}, 85,{0.60,0.40,0.35,0.15,1.00},  {0.3,0.25,0.15,0.1,0.15},               {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {111,"Drill, double disk, orchard vineyard cover"                              ,"unknwn",{5.0,3.5,6.5},0.00,{0.0,0.0,0.0},0.0,{0.00,0.00},  0,{0.00,0.00,0.00,0.00,0.00},  {0,0,0,0,0},                            {0,0,0,0,0}                      ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {112,"Drill, heavy, direct seed, dbl disk opnr"                                ,"unknwn",{5.0,4.0,6.0},0.95,{0.0,2.0,4.0},2.0,{0.40,0.24}, 85,{0.90,0.85,0.80,0.80,1.00},  {0.425,0.34,0.255,0.221,0.323},         {0.01,0.01,0.01,0.03,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,3,3,5,5,2,Armen_source}}
, {113,"Drill, heavy, direct seed, dbl disk opnr w/row cleaners"                 ,"unknwn",{5.0,4.0,6.0},0.95,{0.0,2.0,4.0},2.0,{0.40,0.24}, 90,{0.90,0.85,0.80,0.80,1.00},  {0.45,0.36,0.27,0.234,0.342},           {0.01,0.01,0.01,0.03,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,3,3,5,5,2,Armen_source}}
, {114,"Drill, range"                                                            ,"unknwn",{0.0,0.0,0.0},0.00,{0.0,0.0,3.0},2.0,{0.40,0.24}, 60,{0.70,0.30,0.30,0.10,1.00},  {0.3,0.24,0.18,0.156,0.228},            {0.01,0.01,0.01,0.01,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {115,"Drill, semi-deep furrow  12 to 18 in spacing"                            ,"unknwn",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},3.0,{0.40,0.24}, 85,{0.80,0.60,0.50,0.40,1.00},  {0.425,0.34,0.255,0.221,0.323},         {0.03,0.03,0.04,0.1,0.05}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,3,2,4,3,1,Armen_source}}
, {116,"Drip tape extractor"                                                     ,"unknwn",{5.0,3.0,6.0},0.60,{0.0,3.0,6.0},8.0,{0.60,0.24}, 20,{1.00,0.90,0.90,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.02,0.02,0.02,0.05,0.03}       ,YES,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {117,"Drip tape injection shank"                                               ,"unknwn",{5.0,3.0,6.0},0.60,{0.0,3.0,6.0},2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.05,0.05,0.05,0.07,0.05}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {118,"Drip tape injection shank on beds"                                       ,"unknwn",{5.0,3.0,6.0},0.60,{0.0,3.0,6.0},8.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.05,0.05,0.05,0.07,0.05}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {119,"Drip tape injector bed shaper"                                           ,"unknwn",{5.0,3.0,6.0},1.00,{0.0,3.0,6.0},8.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.85,0.5,0.6},               {0.02,0.02,0.02,0.05,0.03}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {120,"Erosion blanket application"                                             ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {121,"Fert applic. anhyd knife 12 in"                                          ,"AP009" ,{5.0,3.5,6.5},0.80,{0.0,3.0,6.0},2.0,{0.60,0.24}, 50,{0.50,0.45,0.40,0.40,1.00},  {0.25,0.2,0.15,0.13,0.19},              {0.06,0.06,0.06,0.01,0.06}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/2,3,2,3,2,1,Armen_source}}
, {122,"Fert applic. coulter, high press. inject  12 in"                         ,"unknwn",{5.0,3.5,6.5},0.10,{0.0,4.0,8.0},1.0,{0.40,0.24}, 10,{0.50,0.45,0.40,0.40,1.00},  {0.05,0.04,0.03,0.026,0.038},           {0.01,0.01,0.01,0.05,0.01}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {123,"Fert applic. deep plcmt hvy shnk"                                        ,"AP020" ,{5.0,3.5,6.5},0.80,{0.0,5.0,10.},3.0,{1.50,0.24}, 50,{0.70,0.55,0.50,0.40,1.00},  {0.25,0.2,0.15,0.13,0.19},              {0.05,0.05,0.05,0.01,0.05}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/3,3,2,4,2,2,Armen_source}}
, {124,"Fert applic. shank low disturbance, 12 in"                               ,"AP019" ,{5.0,3.5,6.5},0.80,{0.0,3.0,6.0},2.0,{0.60,0.24}, 25,{0.50,0.45,0.40,0.40,1.00},  {0.2,0.15,0.1,0.08,0.14},               {0.06,0.06,0.06,0.01,0.06}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {125,"Fert applic. shank low disturbance, 15 in spacing"                       ,"AP019" ,{5.0,3.5,6.5},0.80,{0.0,3.0,6.0},2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.40,1.00},  {0.165,0.132,0.099,0.0858,0.1254},      {0.04,0.04,0.04,0.06,0.04}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {126,"Fert applic. surface broadcast"                                          ,"AP001" ,{5.0,3.5,6.5},0.00,{0.0,0.0,1.0},2.0,{0.35,0.00},  5,{0.25,0.20,0.15,0.10,1.00},  {0.003,0.003,0.003,0.003,0.003},        {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {127,"Fert. applic. anhyd knife 15 in spacing"                                 ,"AP009" ,{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},2.0,{0.60,0.24}, 40,{0.50,0.45,0.40,0.30,1.00},  {0.2,0.15,0.1,0.08,0.14},               {0.06,0.06,0.06,0.01,0.06}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {128,"Fert. applic. anhyd knife 15 in spacing high disturbance"                ,"AP009" ,{5.0,3.5,6.5},0.60,{0.0,4.0,8.0},2.0,{0.60,0.24}, 90,{0.50,0.45,0.40,0.30,1.00},  {0.45,0.35,0.25,0.25,0.5},              {0.05,0.05,0.05,0.01,0.06}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {129,"Fert. applic. anhyd knife 30 in"                                         ,"AP009" ,{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.05,0.05,0.05,0.07,0.05}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/1,2,1,2,1,1,Armen_source}}
, {130,"Fert. applic. anhyd knife 30 in, bedded"                                 ,"AP009" ,{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},10.,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.05,0.05,0.05,0.07,0.05}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {131,"Fert. applic. double shot knife 15 in spacing high disturbance"          ,"AP019" ,{5.0,3.5,6.5},0.60,{0.0,4.0,8.0},2.0,{0.60,0.24}, 90,{0.50,0.45,0.40,0.30,1.00},  {0.45,0.35,0.25,0.25,0.5},              {0.05,0.05,0.05,0.01,0.06}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {132,"Fert. applic. sugarcane"                                                 ,"unknwn",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},2.0,{0.60,0.24}, 12,{0.50,0.45,0.40,0.30,1.00},  {0.035,0.025,0.02,0.01,0.02},           {0.01,0.01,0.01,0.01,0.01}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {133,"Fert. applic., strip-till 30 in"                                         ,"unknwn",{5.0,3.5,6.5},0.60,{0.0,4.0,10.},4.0,{0.60,0.24}, 33,{0.50,0.45,0.40,0.30,1.00},  {0.165,0.132,0.099,0.0858,0.1254},      {0.04,0.04,0.04,0.06,0.04}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/2,3,2,3,2,1,Armen_source}}
, {134,"Furrow diker"                                                            ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,3.0,5.0},8.0,{0.50,0.24}, 35,{0.60,0.50,0.30,0.10,1.00},  {0.175,0.14,0.105,0.091,0.133},         {0.04,0.04,0.04,0.06,0.04}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/2,3,2,3,3,2,Armen_source}}
, {135,"Furrow shaper, torpedo"                                                  ,"unknwn",{5.0,3.5,6.5},1.00,{0.0,2.0,4.0},8.0,{0.24,0.24}, 60,{0.50,0.45,0.40,0.30,1.00},  {0.3,0.24,0.18,0.156,0.228},            {0.01,0.01,0.01,0.02,0.01}       ,NO ,COMPRESSION           ,{/*SDR*/0,0,0,3,0,4,Armen_source}}
, {136,"Germination of dormant seeding"                                          ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {137,"Graze, continuous"                                                       ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,0.0,3.0},0.0,{0.60,0.60},  0,{ NA , NA , NA , NA , NA },  {0.2,0.15,0.1,0.05,1},                  {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,1,0,0,0,3,Armen_source}}
, {138,"Graze, continuous overgrazing"                                           ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,0.0,3.0},0.0,{0.60,0.24},100,{ NA , NA , NA , NA , NA },  {0.2,0.15,0.1,0.05,1},                  {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {139,"Graze, continuous, heavy hoof traffic"                                   ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,0.0,3.0},0.0,{0.60,0.24},100,{ NA , NA , NA , NA , NA },  {0.2,0.15,0.1,0.05,1},                  {0,0,0,0,0}                      ,NO ,MIXING                ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {140,"Graze, continuous, light hoof traffic"                                   ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,0.0,3.0},0.0,{0.60,0.60}, 50,{ NA , NA , NA , NA , NA },  {0.2,0.15,0.1,0.05,1},                  {0,0,0,0,0}                      ,NO ,MIXING                ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {141,"Graze, continuous, moderate hoof traffic"                                ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,0.0,3.0},0.0,{0.60,0.60}, 80,{ NA , NA , NA , NA , NA },  {0.2,0.15,0.1,0.05,1},                  {0,0,0,0,0}                      ,NO ,MIXING                ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {142,"Graze, intensive rotational"                                             ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,0.0,3.0},0.0,{0.60,0.60},  0,{ NA , NA , NA , NA , NA },  {0.2,0.15,0.1,0.05,1},                  {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,1,0,0,0,3,Armen_source}}
, {143,"Graze, rotational"                                                       ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,0.0,3.0},0.0,{0.60,0.60},  0,{ NA , NA , NA , NA , NA },  {0.2,0.15,0.1,0.05,1},                  {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,1,0,0,0,3,Armen_source}}
, {144,"Graze, stubble or residue"                                               ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,1.0,3.0},0.0,{0.60,0.24},  0,{0.20,0.15,0.10,0.01,0.01},  {0.2,0.15,0.1,0.05,0.5},                {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,1,0,0,0,3,Armen_source}}
, {145,"Graze, stubble or residue 25 pct"                                        ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,1.0,3.0},0.0,{0.60,0.24},  0,{0.30,0.25,0.20,0.01,0.01},  {0.2,0.15,0.1,0.05,0.5},                {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,1,0,0,0,3,Roger_source}}
, {146,"Graze, stubble or residue 50 pct"                                        ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,1.0,3.0},0.0,{0.60,0.24},  0,{0.50,0.40,0.30,0.01,0.01},  {0.2,0.15,0.1,0.05,0.5},                {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,1,0,0,0,3,Roger_source}}
, {147,"Graze, stubble or residue 75 pct"                                        ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,1.0,3.0},0.0,{0.60,0.24},  0,{0.70,0.60,0.50,0.01,0.01},  {0.2,0.15,0.1,0.05,0.5},                {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,1,0,0,0,3,Roger_source}}
, {148,"Harrow, coiled tine"                                                     ,"TI015" ,{6.0,3.0,7.0},0.25,{0.0,1.0,3.0},1.0,{0.40,0.24},100,{0.50,0.30,0.20,0.10,1.00},  {0.25,0.2,0.15,0.1,0.25},               {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,2,0,2,3,3,Armen_source}}
, {149,"Harrow, coiled tine weeder"                                              ,"TI015" ,{6.0,3.0,7.0},0.25,{0.0,1.0,2.0},0.5,{0.35,0.24},100,{0.50,0.30,0.20,0.10,1.00},  {0.1,0.1,0.075,0.1,0.25},               {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {150,"Harrow, heavy"                                                           ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,2.0,4.0},2.0,{0.40,0.24},100,{0.80,0.70,0.60,0.60,1.00},  {0.35,0.3,0.25,0.2,0.5},                {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/2,3,2,2,2,4,Armen_source}}
, {151,"Harrow, heavy on heavy resdue"                                           ,"unknwn",{6.0,5.0,0.0},0.10,{0.0,0.0,1.0},0.0,{0.24,0.00}, 10,{0.80,0.70,0.60,0.60,1.00},  {0.035,0.025,0.02,0.01,0.02},           {0,0,0,0,0}                                              ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {152,"Harrow, rotary"                                                          ,"unknwn",{6.0,3.0,10.},0.50,{0.0,1.0,2.5},1.0,{0.40,0.24},100,{0.85,0.70,0.60,0.50,1.00},  {0.3,0.25,0.15,0.1,0.15},               {0.01,0.01,0.01,0.07,0.02}       ,NO ,MIXING                ,{/*SDR*/2,3,2,2,2,4,Armen_source}}
, {153,"Harrow, rotary, light, fluff fragile residue"                            ,"unknwn",{6.0,3.0,10.},0.10,{0.0,1.0,1.0},0.0,{0.30,0.24}, 65,{0.85,0.70,0.60,0.50,1.00},  {0.2,0.15,0.1,0.05,0.15},               {0.01,0.01,0.01,0.01,0.01}       ,NO ,MIXING                ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {154,"Harrow, rotary, light, fluff residue"                                    ,"unknwn",{6.0,3.0,10.},0.10,{0.0,1.0,1.0},0.0,{0.30,0.24}, 50,{0.85,0.70,0.60,0.50,1.00},  {0.05,0.035,0.02,0.01,0.02},            {0.01,0.01,0.01,0.01,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {155,"Harrow, spike tooth"                                                     ,"TI014" ,{6.0,3.0,7.0},0.40,{0.0,1.0,3.0},1.0,{0.40,0.24},100,{0.60,0.40,0.25,0.10,1.00},  {0.3,0.25,0.2,0.1,0.3},                 {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/0,2,0,2,3,3,Armen_source}}
, {156,"Harrow, spike tooth, cover seed"                                         ,"unknwn",{6.0,3.0,7.0},0.40,{0.0,1.0,3.0},1.0,{0.40,0.24},100,{0.60,0.40,0.25,0.10,1.00},  {0.3,0.25,0.2,0.1,0.3},                 {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/0,2,0,2,3,3,Roger_source}}
, {157,"Harrow, tine, on beds"                                                   ,"unknwn",{5.0,3.5,6.5},0.25,{0.0,1.0,3.0},8.0,{0.30,0.24}, 60,{0.50,0.30,0.20,0.10,1.00},  {0.21,0.15,0.12,0.06,0.12},             {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/1,2,0,2,3,3,Armen_source}}
, {158,"Harvest, banana"                                                         ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.50,0.50,0.70,0.50,0.50},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN        ,{/*SDR*/0,0,0,0,0,1,Armen_source}}
, {159,"Harvest, banana remove stem"                                             ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.00,0.00,0.00,0.00,0.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN        ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {160,"Harvest, broccoli and cauliflower"                                       ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN        ,{/*SDR*/0,0,0,0,0,3,Stewart_source}}
, {161,"Harvest, cabbage and head lettuce"                                       ,"unknwn",{1.0,0.5,1.5},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.20,0.15,0.10,0.10,0.50},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN        ,{/*SDR*/0,0,0,0,0,1,Armen_source}}
, {162,"Harvest, cabbage and head lettuce, hand"                                 ,"unknwn",{0.2,0.1,0.3},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.05,0.05,0.01,0.01,0.50},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN        ,{/*SDR*/0,0,0,0,0,1,Roger_source}}
, {163,"Harvest, combine windrows"                                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{1.00,1.00,1.00,1.00,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {164,"Harvest, corn cobbage or earlage"                                        ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.50,0.50,0.50,0.80,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {165,"Harvest, corn grain and 60pct of residue mass"                           ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.33,0.30,0.10,0.20,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {166,"Harvest, corn grain and cobs"                                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.50,0.50,0.50,0.50,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {167,"Harvest, corn grain and part of stover, 14 inch stubble"                 ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.33,0.30,0.10,0.20,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {168,"Harvest, corn silage with cover crop"                                    ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {169,"Harvest, cotton"                                                         ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.10,0.10,0.10,0.10,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {170,"Harvest, cotton and shred"                                               ,"unknwn",{4.0,0.0,8.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.90,0.90,0.90,0.85,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {171,"Harvest, cranberries"                                                    ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {172,"Harvest, cut flowers"                                                    ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,1,Armen_source}}
, {173,"Harvest, forage sorghum"                                                 ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.60,0.50,0.40,0.30,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {174,"Harvest, fruit crops"                                                    ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {175,"Harvest, grain, grow cover"                                              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.95,0.50,0.85,0.80,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {176,"Harvest, grass or legume seed, burn forage"                              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.55,0.40,0.35,0.80,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {177,"Harvest, grass or legume seed, leave forage"                             ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.40,0.40,0.40,0.75,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {178,"Harvest, grass or legume seed, remove forage"                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.65,0.50,0.45,0.80,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {179,"Harvest, grass seed, remove forage"                                      ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.65,0.50,0.45,0.80,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {180,"Harvest, hand pick"                                                      ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,1,Armen_source}}
, {181,"Harvest, hand pick vegetables"                                           ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,1,Roger_source}}
, {182,"Harvest, hand pull"                                                      ,"unknwn",{1.0,1.0,1.0},0.40,{0.0,0.0,10.},0.0,{1.20,0.00}, 35,{ NA , NA , NA , NA , NA },  {0,0,0,0,0},                            {0,0,0,0,0}                      ,YES,COMPRESSION_AERATION  ,{/*SDR*/0,0,1,0,1,1,Stewart_source}}
, {183,"Harvest, hay, grass"                                                     ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.60,0.50,0.40,0.50,0.50},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {184,"Harvest, hay, legume"                                                    ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.60,0.50,0.40,0.50,0.50},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {185,"Harvest, hay, no regrowth"                                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {186,"Harvest, hops"                                                           ,"unknwn",{1.0,0.5,1.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {187,"Harvest, kenaf"                                                          ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {188,"Harvest, killing crop 10pct standing stubble"                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.90,0.90,0.90,0.90,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN unknown based on old Harvest, Killing crop*/}}
, {189,"Harvest, killing crop 20pct standing stubble"                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.80,0.80,0.80,0.90,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN unknown based on old Harvest, Killing crop*/}}
, {190,"Harvest, killing crop 20pct standing stubble, release cover crop"        ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.80,0.80,0.80,0.80,1.00},  { NA , NA , NA , NA , NA },                                        { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN unknown based on old Harvest, Killing crop*/}}
, {191,"Harvest, killing crop 30pct standing stubble"                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.70,0.70,0.70,0.85,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN unknown based on old Harvest, Killing crop*/}}
, {192,"Harvest, killing crop 50pct standing stubble"                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.50,0.50,0.50,0.80,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN unknown based on old Harvest, Killing crop*/}}
, {193,"Harvest, killing crop 50pct standing stubble, release cover crop"        ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.50,0.50,0.50,0.80,1.00},  { NA , NA , NA , NA , NA },                                        { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN unknown based on old Harvest, Killing crop*/}}
, {194,"Harvest, killing crop 60pct standing stubble"                            ,"unknwn",{5.0,4.0,8.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.40,0.40,0.40,0.75,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN unknown based on old Harvest, Killing crop*/}}
, {195,"Harvest, killing crop 70pct standing stubble"                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.30,0.30,0.30,0.65,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN unknown based on old Harvest, Killing crop*/}}
, {196,"Harvest, lavender bundles"                                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {197,"Harvest, leafy veg."                                                     ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {198,"Harvest, leafy veg. mechanical"                                          ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {199,"Harvest, legume seed, remove forage"                                     ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.65,0.50,0.45,0.80,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {200,"Harvest, orchard and nut crops"                                          ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.30,0.20,0.15,0.10,0.01},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {201,"Harvest, plantains,stalks left"                                          ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.00,0.00,0.00,0.00,0.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,1,Roger_source/* RLN based on old Harvest, plantains*/}}
, {202,"Harvest, plantains,stalks removed"                                       ,"unknwn",{5.0,4.0,6.0},NA  ,{NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.00,0.00,0.00,0.00,0.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,1,Roger_source/* RLN based on old Harvest, plantains*/}}
, {203,"Harvest, residue, forage chopper, complete"                              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.12,0.12,0.12,0.12,0.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {204,"Harvest, residue, forage chopper, incomplete"                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.12,0.12,0.12,0.12,0.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{0,0,0,0,0,3,Stewart_source}}
, {205,"Harvest, residue, forage chopper, intermediate"                          ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.12,0.12,0.12,0.12,0.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {206,"Harvest, rootcrops, manually"                                            ,"unknwn",{1.0,1.0,1.0},0.70,{0.0,0.0,0.0},0.0,{1.90,0.24}, 40,{0.00,0.00,0.00,0.00,0.00},  {0.304,0.268,0.232,0.172,0.34},         {0.07,0.08,0.1,0.12,0.07}        ,YES,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,2,2,2,1,Armen_source}}
, {207,"Harvest, rootcrops, manually, 25pct of field disturbed"                  ,"unknwn",{1.0,1.0,1.0},0.70,{0.0,0.0,0.0},0.0,{1.90,0.24}, 25,{0.95,0.95,0.95,0.90,1.00},  {0.304,0.268,0.232,0.172,0.34},         {0.07,0.08,0.1,0.12,0.07}        ,YES,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {208,"Harvest, rootcrops, manually, 33pct of field disturbed"                  ,"unknwn",{1.0,1.0,1.0},0.70,{0.0,0.0,0.0},0.0,{1.90,0.24}, 33,{0.95,0.95,0.95,0.90,1.00},  {0.304,0.268,0.232,0.172,0.34},         {0.07,0.08,0.1,0.12,0.07}        ,YES,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {209,"Harvest, rootcrops, manually, 50pct of field disturbed"                  ,"unknwn",{1.0,1.0,1.0},0.70,{0.0,0.0,0.0},0.0,{1.90,0.24}, 50,{0.95,0.95,0.95,0.90,1.00},  {0.304,0.268,0.232,0.172,0.34},         {0.07,0.08,0.1,0.12,0.07}        ,YES,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {210,"Harvest, rootcrops, manually, one third"                                 ,"unknwn",{1.0,1.0,1.0},0.70,{0.0,0.0,0.0},0.0,{1.90,0.24}, 30,{ NA , NA , NA , NA , NA },  {0.304,0.268,0.232,0.172,0.34},         {0.07,0.08,0.1,0.12,0.07}        ,NO ,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {211,"Harvest, seed heads by hand"                                             ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{0,0,0,0,0,1,Stewart_source}}
, {212,"Harvest, silage"                                                         ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, { NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {213,"Harvest, silage 3ft stubble"                                             ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, { NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Roger_source/* RLN based on harvest silage */}}
, {214,"Harvest, small grain haylage 5 in ht"                                    ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.25,0.25,0.20,0.10,0.10},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {215,"Harvest, small grain silage with cover crop"                             ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.20,0.20,0.20,0.20,0.20},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {216,"Harvest, small grain, release understory"                                ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.50,0.50,0.50,0.80,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {217,"Harvest, snapper header"                                                 ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.50,0.50,0.50,0.80,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {218,"Harvest, sprig rototiller digger"                                        ,"unknwn",{4.0,1.0,5.0},1.00,{0.0,1.0,4.0},3.0,{0.30,0.24},100,{1.00,0.90,1.00,0.70,1.00},  {0.9,0.8,0.75,0.5,1},                   {0.07,0.08,0.1,0.12,0.07}       ,YES,MIXING                ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {219,"Harvest, stalk chopping corn header"                                     ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.93,0.93,0.93,0.90,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {220,"Harvest, stripper header"                                                ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.10,0.10,0.10,0.10,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {221,"Harvest, sugarcane, after burning"                                       ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.05,0.05,0.05,0.05,0.05},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {222,"Harvest, sugarcane, after burning, no regrowth"                          ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.05,0.05,0.05,0.05,0.05},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {223,"Harvest, sugarcane, modern"                                              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {224,"Harvest, sugarcane, old type"                                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {225,"Harvest, sugarcane, root rake"                                           ,"unknwn",{0.0,0.0,0.0},0.75,{0.0,4.0,8.0},3.0,{1.00,0.24},100,{0.98,0.98,0.95,0.75,1.00},  {0.8,0.7,0.6,0.5,1},                    {0.05,0.06,0.07,0.02,0.05}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {226,"Harvest, timber remove tops"                                             ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {227,"Harvest, tobacco, burley"                                                ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,1,Armen_source}}
, {228,"Harvest, tobacco, flue cured"                                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,1,Armen_source}}
, {229,"Harvest, tree buck"                                                      ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {230,"Harvest, tree length logs"                                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {231,"Harvest, tree pulpwood cut"                                              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {232,"Harvest, tree, Christmas grow cover"                                     ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {233,"Harvest, trees, chipper"                                                 ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {234,"Harvest, vine crops"                                                     ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {235,"Harvest, vine crops, mechanical"                                         ,"unknwn",{5.0,4.0,6.0},0.20,{0.0,0.0,4.0},0.5,{0.35,0.00}, 20,{1.00,1.00,1.00,1.00,1.00},  {0.05,0.04,0.03,0.5,0.5},               {0,0,0,0,0}                      ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {236,"Harvest, windrows"                                                       ,"unknwn",{5.0,4.0,6.0},0.20,{0.0,0.0,1.0},0.0,{0.24,0.00},  5,{1.00,1.00,1.00,1.00,1.00},  {0,0,0,0,0},                            {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {237,"Hilling, manual hoe"                                                     ,"unknwn",{1.0,1.0,1.0},0.90,{0.0,0.0,4.0},12.0,{0.50,0.00},85,{ NA , NA , NA , NA , NA },  {0.425,0.34,0.255,0.221,0.323},         {0.04,0.04,0.04,0.06,0.04}       ,NO ,MIXING_RLN            ,{0,1,0,0,0,1,Stewart_source}}
, {238,"Hydro-seeder"                                                            ,"unknwn",{6.0,3.5,6.5},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {239,"Install Compost Sock"                                                    ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {240,"Install Silt Fence"                                                      ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {241,"Install Straw Bale"                                                      ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {242,"Kill crop"                                                               ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.70,0.60,0.50,0.50,0.50},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {243,"Knife, windrow dry beans"                                                ,"unknwn",{5.0,3.5,6.5},0.50,{0.0,2.0,3.0},3.0,{0.40,0.24},100,{1.00,0.90,1.00,0.70,0.50},  {0.25,0.15,0.1,0.05,0.25},              {0.02,0.03,0.05,0.07,0.02}       ,YES,LIFTING_FRACTURING    ,{/*SDR*/0,0,5,5,4,3,Armen_source}}
, {244,"Land plane"                                                              ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,1.0,4.0},0.1,{0.30,0.24},100,{0.95,0.95,0.95,0.95,0.95},  {0.4,0.35,0.3,0.2,0.85},                {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/1,1,0,1,0,2,Armen_source}}
, {245,"Land plane; orchard and vine crops"                                      ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,1.0,4.0},0.1,{0.30,0.24}, 60,{0.95,0.95,0.95,0.95,0.95},  {0.24,0.21,0.18,0.12,0.6},              {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {246,"Laser Land leveler"                                                      ,"unknwn",{0.0,0.0,6.0},0.50,{0.0,1.0,8.0},0.1,{0.30,0.24},100,{0.95,0.95,0.95,0.95,0.95},  {0.4,0.35,0.3,0.2,0.85},                {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {247,"Lister, 30 in"                                                           ,"TI016" ,{4.5,3.5,5.0},1.00,{0.0,4.0,7.0},8.0,{0.80,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.9,0.6,0.9},                {0.02,0.02,0.02,0.05,0.03}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,4,3,5,5,2,Roger_source/*RLN based on lister 40 in*/ }}
, {248,"Lister, 40 in"                                                           ,"TI016" ,{4.5,3.5,5.0},1.00,{0.0,4.0,7.0},8.0,{0.80,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.9,0.6,0.9},                {0.02,0.02,0.02,0.05,0.03}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,4,3,5,5,2,Armen_source}}
, {249,"Log skidder"                                                             ,"unknwn",{2.0,1.0,3.0},1.00,{0.0,3.0,10.},0.0,{0.80,0.00}, 75,{0.95,0.95,0.95,0.95,1.00},  {0.57,0.5025,0.435,0.3225,0.6375},      {0,0,0,0,0}                      ,YES,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {250,"Manure injector, liquid high disturb.30 inch"                            ,"TI020" ,{4.0,3.5,6.5},0.80,{0.0,4.0,10.},4.0,{1.50,0.24}, 50,{0.60,0.50,0.45,0.40,1.00},  {0.38,0.335,0.29,0.215,0.425},          {0.05,0.05,0.05,0.1,0.05}        ,NO ,LIFTING_FRACTURING    ,{/*SDR*/3,4,3,4,3,4,Roger_source/*RLN based on old Manure injector*/}}
, {251,"Manure injector, liquid low disturb.15 inch"                             ,"TI020" ,{4.0,3.5,6.5},0.40,{0.0,4.0,8.0},3.0,{0.50,0.24}, 30,{0.80,0.65,0.60,0.40,1.00},  {0.228,0.201,0.174,0.129,0.255},        {0.05,0.05,0.05,0.1,0.05}        ,NO ,LIFTING_FRACTURING    ,{/*SDR*/3,4,3,4,3,4,Roger_source/*RLN based on old Manure injector*/}}
, {252,"Manure injector, liquid low disturb.30 inch"                             ,"TI020" ,{4.0,2.0,5.0},0.40,{0.0,4.0,8.0},2.0,{0.40,0.24}, 15,{0.70,0.55,0.50,0.40,1.00},  {0.114,0.1005,0.087,0.0645,0.1275},     {0.05,0.05,0.05,0.1,0.05}        ,NO ,LIFTING_FRACTURING    ,{/*SDR*/3,4,3,4,3,4,Roger_source/*RLN based on old Manure injector*/}}
, {253,"Manure spreader, liquid"                                                 ,"unknwn",{4.0,3.0,8.0},0.10,{0.0,1.0,2.0},0.1,{0.24,0.00}, 20,{0.40,0.30,0.20,0.15,1.00},  {0.07,0.05,0.04,0.02,0.04},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN based on old manure spreader*/}}
, {254,"Manure spreader, slurry"                                                 ,"unknwn",{4.0,3.0,8.0},0.10,{0.0,0.0,2.0},0.1,{0.24,0.00}, 20,{0.40,0.30,0.20,0.15,1.00},  {0.07,0.05,0.04,0.02,0.04},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN based on old manure spreader*/}}
, {255,"Manure spreader, solid and semi-solid"                                   ,"unknwn",{4.0,3.0,8.0},0.10,{0.0,0.0,1.0},1.0,{0.24,0.00}, 20,{0.40,0.30,0.20,0.15,1.00},  {0.07,0.05,0.04,0.02,0.04},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,0,0,0,0,5,Roger_source/*RLN based on old manure spreader*/}}
, {256,"Manure, liquid irrigation"                                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.15,0.15,0.10,0.15,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {257,"Middle buster, digger"                                                   ,"unknwn",{5.0,3.0,6.0},1.00,{0.0,4.0,12.},8.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.9,0.5,0.6},                {0.02,0.02,0.02,0.05,0.03}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,5,3,5,5,2,Armen_source}}
, {258,"Mower, swather, on stubble"                                              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.85,0.60,0.50,0.70,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {259,"Mower, swather, on stubble 4in"                                          ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {0.65,0.40,0.35,0.70,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {260,"Mower, swather, windrower"                                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA, {1.00,0.90,1.00,0.70,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {261,"Mulch crimper"                                                           ,"unknwn",{0.0,0.0,0.0},0.20,{0.0,1.0,3.0},0.5,{0.30,0.24}, 15,{0.60,0.50,0.40,0.50,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.07,0.02}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {262,"Mulch treader"                                                           ,"TI022" ,{0.0,0.0,0.0},0.50,{0.0,1.0,3.0},0.0,{0.40,0.24},100,{0.85,0.70,0.60,0.50,1.00},  {0.4,0.35,0.3,0.4,0.73},                {0.01,0.01,0.01,0.07,0.02}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/3,3,2,2,3,1,Armen_source}}
, {263,"No operation"                                                            ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,NEGLIGIBLE_EFFECT     ,{/*SDR*/0,0,0,0,0,0,Armen_source}}
, {264,"Para-plow or para-till"                                                  ,"unknwn",{3.0,2.0,5.0},0.25,{0.0,10.,15.},0.0,{1.90,0.00}, 75,{0.60,0.50,0.45,0.40,1.00},  {0.375,0.3,0.225,0.195,0.285},          {0.02,0.02,0.02,0.03,0.02}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/1,2,1,3,3,1,Armen_source}}
, {265,"Pasture renovator"                                                       ,"unknwn",{0.0,0.0,0.0},0.40,{0.0,1.0,3.0},0.5,{0.30,0.24}, 50,{0.60,0.50,0.40,0.50,1.00},  {0.2275,0.1625,0.13,0.065,0.13},        {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {266,"Paving"                                                                  ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {267,"Permeable weed barrier applicator"                                       ,"unknwn",{2.0,1.0,3.0},0.60,{0.0,2.0,5.0},0.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,UNSPECIFIED_EFFECT    ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {268,"Planter, RELAY INTERCROP,  double disk opnr w/fluted coulter"            ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},1.0,{0.40,0.24}, 15,{0.30,0.25,0.15,0.10,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {269,"Planter, double disk opener on 12 inch high beds"                        ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},10.,{0.40,0.24}, 15,{0.30,0.25,0.20,0.10,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {270,"Planter, double disk opener on 15 inch high beds"                        ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},14.,{0.40,0.24}, 15,{0.30,0.25,0.20,0.10,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {271,"Planter, double disk opener on 18 inch high beds"                        ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},16.,{0.40,0.24}, 15,{0.30,0.25,0.20,0.10,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {272,"Planter, double disk opener on 8 inch high beds"                         ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},6.0,{0.40,0.24}, 15,{0.30,0.25,0.20,0.10,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {273,"Planter, double disk opnr"                                               ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.40,0.24}, 15,{0.30,0.25,0.20,0.10,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,1,0,1,1,1,Armen_source}}
, {274,"Planter, double disk opnr w/fluted coulter"                              ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},1.0,{0.40,0.24}, 15,{0.30,0.25,0.15,0.10,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,1,0,1,1,1,Armen_source}}
, {275,"Planter, double disk opnr w/fluted coulter, 15 inch row spacing"         ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},1.0,{0.40,0.24}, 30,{0.30,0.25,0.15,0.10,1.00},  {0.106,0.076,0.06,0.03,0.06},           {0.02,0.02,0.02,0.04,0.02}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,1,0,1,1,1,Roger_source}}
, {276,"Planter, double disk opnr, 15 inch row spacing"                          ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.40,0.24}, 30,{0.30,0.25,0.20,0.10,1.00},  {0.106,0.076,0.06,0.03,0.06},           {0.02,0.02,0.02,0.04,0.02}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {277,"Planter, double disk opnr, 18 in rows"                                   ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.40,0.24}, 25,{0.30,0.25,0.20,0.10,1.00},  {0.0875,0.0625,0.05,0.025,0.05},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,2,0,1,2,1,Armen_source}}
, {278,"Planter, double disk opnr, 40 in rows"                                   ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.40,0.24}, 10,{0.30,0.25,0.20,0.10,1.00},  {0.04,0.045,0.02,0.01,0.01},            {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,2,0,1,2,1,Roger_source}}
, {279,"Planter, furrow opener in 4 inch deep furrows"                           ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,5.0},4.0,{0.40,0.24}, 30,{0.30,0.25,0.20,0.10,1.00},  {0.15,0.12,0.09,0.078,0.114},           {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {280,"Planter, furrow opener in 6 inch deep furrows"                           ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,4.0,8.0},6.0,{0.40,0.24}, 60,{0.30,0.25,0.20,0.10,1.00},  {0.3,0.24,0.18,0.156,0.228},            {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {281,"Planter, furrow opener in 8 inch deep furrows"                           ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,5.0,10.},8.0,{0.40,0.24}, 80,{0.30,0.25,0.20,0.10,1.00},  {0.4,0.32,0.24,0.208,0.304},            {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {282,"Planter, in-row subsoiler"                                               ,"TI033" ,{3.0,2.0,5.0},0.25,{0.0,12.,18.},0.0,{1.50,0.00}, 40,{0.60,0.50,0.45,0.40,1.00},  {0.304,0.268,0.232,0.172,0.34},         {0.01,0.01,0.01,0.1 ,0.01}       ,YES,LIFTING_FRACTURING    ,{/*SDR*/1,2,1,3,3,1,Armen_source}}
, {283,"Planter, in-row subsoiler low disturbace"                                ,"TI033" ,{3.0,2.0,5.0},0.25,{0.0,8.0,15.},1.0,{0.40,0.00}, 10,{0.60,0.50,0.45,0.40,1.00},  {0.05,0.04,0.03,0.026,0.038},           {0.01,0.01,0.01,0.1 ,0.01}       ,YES,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {284,"Planter, in-row subsoiler w/ residue mgr."                               ,"TI033" ,{3.0,2.0,5.0},0.25,{0.0,8.0,15.},1.0,{0.40,0.00}, 25,{0.60,0.50,0.45,0.40,1.00},  {0.125,0.1,0.075,0.065,0.095},          {0.01,0.01,0.01,0.1 ,0.01}       ,YES,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {285,"Planter, narrow slot w/smooth or rippled coulter"                        ,"unknwn",{5.0,3.5,6.5},0.20,{0.0,2.0,4.0},1.0,{0.30,0.24},  5,{0.30,0.25,0.15,0.10,1.00},  {0.0175,0.0125,0.01,0.005,0.01},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {286,"Planter, ridge till"                                                     ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},4.0,{0.40,0.24}, 65,{ NA , NA , NA , NA , NA },  {0.15,0.12,0.09,0.078,0.114},           {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/3,4,2,3,3,2,Armen_source}}
, {287,"Planter, runner opener"                                                  ,"unknwn",{4.0,2.0,6.0},0.50,{0.0,1.0,3.5},3.0,{0.40,0.24}, 20,{0.30,0.25,0.20,0.10,1.00},  {0.07,0.05,0.04,0.02,0.04},             {0.01,0.01,0.01,0.05,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/0,0,0,0,0,1,Armen_source}}
, {288,"Planter, small veg seed"                                                 ,"TI034" ,{2.0,1.0,3.0},0.40,{0.0,1.0,2.0},1.0,{0.30,0.24}, 15,{ NA , NA , NA , NA , NA },  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.05,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/0,0,0,1,1,2,Armen_source}}
, {289,"Planter, small veg seed on 8 inch high beds"                             ,"TI034" ,{2.0,1.0,3.0},0.40,{0.0,1.0,2.0},8.0,{0.30,0.24}, 15,{ NA , NA , NA , NA , NA },  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.05,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/0,0,0,1,1,2,Roger_source}}
, {290,"Planter, sprig conventional"                                             ,"unknwn",{5.0,3.0,6.0},0.65,{0.0,1.0,3.0},1.0,{0.60,0.24},100,{0.85,0.70,0.60,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.07,0.08,0.1 ,0.12,0.07}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {291,"Planter, sprig, no-till"                                                 ,"unknwn",{0.0,0.0,0.0},0.00,{0.0,0.0,3.0},0.0,{0.40,0.24},  5,{0.00,0.00,0.00,0.00,0.00},  {0.73,0.63,0.55,0.4,0.73},              {0.07,0.08,0.1 ,0.12,0.07}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {292,"Planter, sprigs on beds"                                                 ,"unknwn",{5.0,3.0,6.0},1.00,{0.0,2.0,5.0},5.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.85,0.5,0.6},               {0.02,0.02,0.02,0.05,0.03}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {293,"Planter, strip till"                                                     ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.40,0.24}, 30,{0.30,0.25,0.20,0.10,1.00},  {0.105,0.075,0.06,0.03,0.06},           {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,2,1,2,1,1,Armen_source}}
, {294,"Planter, strip till, 22 inch"                                            ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.40,0.24}, 50,{0.30,0.25,0.20,0.10,1.00},  {0.105,0.075,0.06,0.03,0.06},           {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,2,1,2,1,1,Roger_source}}
, {295,"Planter, sugarcane"                                                      ,"unknwn",{2.0,1.0,3.0},0.40,{0.0,4.0,8.0},2.0,{0.40,0.24}, 20,{0.30,0.25,0.20,0.10,1.00},  {0.2,0.15,0.15,0.1,0.1},                {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/0,1,0,1,1,3,Armen_source}}
, {296,"Planter, transplanter, vegetable"                                        ,"unknwn",{2.0,1.0,3.0},0.40,{0.0,4.0,8.0},2.0,{0.40,0.24}, 20,{0.30,0.25,0.20,0.10,1.00},  {0.07,0.05,0.04,0.02,0.04},             {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/0,1,0,1,1,3,Armen_source}}
, {297,"Planter, transplanter, vegetable on 8 inch high beds"                    ,"unknwn",{2.0,1.0,3.0},0.40,{0.0,4.0,8.0},8.0,{0.40,0.24}, 20,{0.30,0.25,0.20,0.10,1.00},  {0.07,0.05,0.04,0.02,0.04},             {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/0,1,0,1,1,3,Roger_source}}
, {298,"Planter, transplanter, vegetable, no-till"                               ,"unknwn",{2.0,1.0,3.0},0.40,{0.0,4.0,8.0},1.0,{0.40,0.24}, 20,{0.30,0.25,0.15,0.10,1.00},  {0.07,0.05,0.04,0.02,0.04},             {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/0,1,0,1,1,3,Armen_source}}
, {299,"Planter, tree, mechanical transplanter"                                  ,"unknwn",{3.0,2.0,5.0},0.25,{0.0,8.0,12.},2.0,{0.80,0.00}, 12,{0.30,0.30,0.30,0.20,1.00},  {0.06,0.048,0.036,0.0312,0.0456},       {0,0,0,0,0}                      ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {300,"Planting, broadcast seeder"                                              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {301,"Planting, hand 10 percent dist."                                         ,"TI035" ,{1.0,1.0,1.0},0.00,{0.0,0.0,3.0},1.0,{0.30,0.50}, 10,{ NA , NA , NA , NA , NA },  {0.05,0.04,0.03,0.026,0.038},           {0.01,0.01,0.01,0.05,0.01}       ,NO ,UNSPECIFIED_EFFECT    ,{/*SDR*/0,0,0,0,1,1,Stewart_source}}
, {302,"Planting, hand 5 percent dist."                                          ,"TI035" ,{1.0,1.0,1.0},0.00,{0.0,0.0,3.0},1.0,{0.30,0.24},  5,{ NA , NA , NA , NA , NA },  {0.025,0.02,0.015,0.013,0.019},         {0.07,0.08,0.1 ,0.12,0.07}       ,NO ,UNSPECIFIED_EFFECT    ,{/*SDR*/0,0,0,0,1,0,Stewart_source}}
, {303,"Planting, manual"                                                        ,"TI036" ,{1.0,1.0,1.0},0.00,{0.0,1.0,3.0},1.0,{0.90,0.24}, 30,{ NA , NA , NA , NA , NA },  {0.15,0.12,0.09,0.078,0.114},           {0.007,0.008,0.01,0.12,0.01}     ,NO ,UNSPECIFIED_EFFECT    ,{/*SDR*/0,1,0,0,1,0,Armen_source}}
, {304,"Planting, manual on 8 inch high beds"                                    ,"TI036" ,{1.0,1.0,1.0},0.00,{0.0,0.0,3.0},8.0,{0.30,0.24}, 30,{ NA , NA , NA , NA , NA },  {0.15,0.12,0.09,0.078,0.114},           {0,0,0,0,0}                      ,NO ,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {305,"Planting, no-til manually"                                               ,"TI036" ,{1.0,1.0,1.0},0.00,{0.0,1.0,3.0},1.0,{0.30,0.24}, 30,{ NA , NA , NA , NA , NA },  {0.105,0.075,0.06,0.03,0.06},           {0.01,0.01,0.01,0.02,0.01}       ,NO ,UNSPECIFIED_EFFECT    ,{/*SDR*/0,0,0,0,1,0,Stewart_source}}
, {306,"Plastic hoop tunnel installation 100 percent cover"                      ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,1.0,2.0},6.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.01,0.01,0.01,0.01,0.01},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {307,"Plastic hoop tunnel installation 50 percent cover"                       ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,1.0,2.0},0.5,{0.60,0.00}, 10,{ NA , NA , NA , NA , NA },  {0.01,0.01,0.01,0.01,0.01},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {308,"Plastic hoop tunnel installation 75 percent cover"                       ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,1.0,2.0},0.5,{0.60,0.00}, 15,{ NA , NA , NA , NA , NA },  {0.01,0.01,0.01,0.01,0.01},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {309,"Plastic hoop tunnel installation on beds 50 percent cover"               ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,1.0,2.0},6.0,{0.60,0.00}, 10,{ NA , NA , NA , NA , NA },  {0.01,0.01,0.01,0.01,0.01},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {310,"Plastic hoop tunnel installation on beds 75 percent cover"               ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,1.0,2.0},6.0,{0.60,0.00}, 15,{ NA , NA , NA , NA , NA },  {0.01,0.01,0.01,0.01,0.01},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {311,"Plastic hoop tunnel removal on beds"                                     ,"unknwn",{2.0,3.0,4.0},0.10,{0.0,1.0,2.0},6.0,{0.30,0.24}, 20,{0.25,0.20,0.15,0.10,0.10},  {0.01,0.01,0.01,0.01,0.01},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {312,"Plastic hoop tunnel, removal"                                            ,"unknwn",{2.0,3.0,4.0},0.10,{0.0,1.0,3.0},0.5,{0.30,0.24}, 20,{0.25,0.20,0.15,0.10,0.10},  {0.01,0.01,0.01,0.01,0.01},             {0.01,0.01,0.01,0.01,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {313,"Plastic mulch applic. 40 inch beds 100 percent cover"                    ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},8.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {314,"Plastic mulch applic. 40 inch beds 75 percent cover"                     ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},8.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {315,"Plastic mulch applic. 48 inch beds 100 percent cover"                    ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},8.0,{0.60,0.00}, 17,{ NA , NA , NA , NA , NA },  {0.083,0.0664,0.0498,0.04316,0.06308},  {.0166,.0166,.0166,.0415 ,.0249} ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {316,"Plastic mulch applic. 48 inch beds 80 percent cover"                     ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},8.0,{0.60,0.00}, 17,{ NA , NA , NA , NA , NA },  {0.083,0.0664,0.0498,0.04316,0.06308},  {.0166,.0166,.0166,.0415 ,.0249} ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {317,"Plastic mulch applic. 54 inch beds 100 percent cover"                    ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},8.0,{0.60,0.00}, 15,{ NA , NA , NA , NA , NA },  {0.074,0.0592,0.0444,0.03848,0.05624},  {.0148,.0148,.0148,.037  ,.0222} ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {318,"Plastic mulch applic. 54 inch beds 80 percent cover"                     ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},8.0,{0.60,0.00}, 15,{ NA , NA , NA , NA , NA },  {0.074,0.0592,0.0444,0.03848,0.05624},  {.0148,.0148,.0148,.037  ,.0222} ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {319,"Plastic mulch applic. 64 inch beds 100 percent cover"                    ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},8.0,{0.60,0.00}, 13,{ NA , NA , NA , NA , NA },  {0.0625,0.05,0.0375,0.0325,0.0475},     {.0125,.0125,.0125,.03125,.01875},NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {320,"Plastic mulch applic. 64 inch beds 85 percent cover"                     ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},8.0,{0.60,0.00}, 13,{ NA , NA , NA , NA , NA },  {0.0625,0.05,0.0375,0.0325,0.0475},     {.0125,.0125,.0125,.03125,.01875},NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {321,"Plastic mulch applicator 100 percent cover"                              ,"unknwn",{2.0,1.0,4.0},0.00,{0.0,2.0,4.0},2.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {322,"Plastic mulch applicator 40 percent cover"                               ,"unknwn",{2.0,1.0,4.0},0.60,{0.0,2.0,4.0},2.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.1,0.08,0.06,0.052,0.076},            {0.05,0.05,0.05,0.07,0.05}       ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {323,"Plastic mulch applicator 50 percent cover"                               ,"unknwn",{2.0,1.0,4.0},0.60,{0.0,2.0,4.0},2.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.1,0.08,0.06,0.052,0.076},            {0.05,0.05,0.05,0.07,0.05}       ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {324,"Plastic mulch applicator 75 percent cover"                               ,"unknwn",{2.0,1.0,4.0},0.60,{0.0,2.0,4.0},2.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,INVERSION_MIXING_RLN  ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {325,"Plastic mulch, 05 percent removal"                                       ,"unknwn",{2.0,3.0,4.0},0.60,{0.0,0.0,3.0},2.0,{0.60,0.00}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {326,"Plastic mulch, 10 percent removal"                                       ,"unknwn",{2.0,3.0,4.0},0.60,{0.0,0.0,3.0},2.0,{0.60,0.00}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {327,"Plastic mulch, 25 percent removal"                                       ,"unknwn",{2.0,3.0,4.0},0.60,{0.0,1.0,3.0},2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {328,"Plastic mulch, 50 percent  removal"                                      ,"unknwn",{2.0,3.0,4.0},0.60,{0.0,1.0,3.0},2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {329,"Plastic mulch, remove"                                                   ,"unknwn",{2.0,3.0,4.0},0.60,{0.0,1.0,3.0},2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.02,0.02,0.02,0.05,0.03}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/2,2,0,2,2,1,Armen_source}}
, {330,"Plastic weed barrier 40 inch beds 100 percent cover"                     ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},8.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.5,0.45,0.35,0.3,0.6},                {0.02,0.02,0.02,0.05,0.03}       ,NO ,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {331,"Plastic weed barrier 40 inch beds 50 percent cover"                      ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},2.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.5,0.45,0.35,0.3,0.6},                {0.02,0.02,0.02,0.05,0.03}       ,NO ,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {332,"Plastic weed barrier 40 inch beds 75 percent cover"                      ,"unknwn",{2.0,1.0,4.0},0.10,{0.0,2.0,4.0},2.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.5,0.45,0.35,0.3,0.6},                {0.02,0.02,0.02,0.05,0.03}       ,NO ,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {333,"Plastic weed barrier applicator 100 percent cover"                       ,"unknwn",{2.0,1.0,4.0},0.00,{0.0,2.0,4.0},2.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.5,0.45,0.35,0.3,0.6},                {0.02,0.02,0.02,0.05,0.03}       ,NO ,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {334,"Plastic weed barrier applicator 50 percent cover"                        ,"unknwn",{2.0,1.0,4.0},0.00,{0.0,2.0,4.0},2.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.5,0.45,0.35,0.3,0.6},                {0.02,0.02,0.02,0.05,0.03}       ,NO ,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {335,"Plastic weed barrier applicator 75 percent cover"                        ,"unknwn",{2.0,1.0,4.0},0.00,{0.0,2.0,4.0},2.0,{0.60,0.00}, 20,{ NA , NA , NA , NA , NA },  {0.5,0.45,0.35,0.3,0.6},                {0.02,0.02,0.02,0.05,0.03}       ,NO ,UNSPECIFIED_EFFECT    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {336,"Plow, deep, large, moldboard"                                            ,"TI042" ,{3.0,2.0,4.0},1.00,{0.0,24.,36.},10.,{2.50,0.24},100,{1.00,1.00,1.00,0.75,1.00},  {0.99,0.99,0.99,0.85,0.97},             {0.01,0.01,0.01,0.01,0.02}       ,YES,MIXING                ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {337,"Plow, disk"                                                              ,"unknwn",{5.0,3.5,6.0},1.00,{0.0,4.0,8.0},1.0,{1.90,0.24},100,{0.98,0.98,0.95,0.75,1.00},  {0.89,0.88,0.88,0.75,1},                {0.01,0.02,0.04,0.1,0.02}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,5,4,4,5,4,Armen_source}}
, {338,"Plow, moldboard"                                                         ,"TI003" ,{5.0,3.5,6.0},1.00,{0.0,6.0,10.},1.0,{1.90,0.24},100,{1.00,1.00,1.00,0.75,1.00},  {0.99,0.99,0.99,0.85,0.97},             {0.01,0.02,0.04,0.1,0.02}        ,YES,INVERSION_SOME_MIXING ,{/*SDR*/5,5,5,5,5,4,Armen_source}}
, {339,"Plow, moldboard 10 inch depth"                                           ,"TI041" ,{5.0,3.5,6.0},1.00,{0.0,8.0,12.},1.0,{1.90,0.24},100,{1.00,1.00,1.00,0.75,1.00},  {0.99,0.99,0.99,0.85,0.97},             {0.01,0.02,0.04,0.1,0.02}        ,YES,INVERSION_SOME_MIXING ,{/*SDR*/5,5,5,5,5,4,Roger_source}}
, {340,"Plow, moldboard 6-7 inch depth"                                          ,"TI003" ,{5.0,3.5,6.0},1.00,{0.0,4.0,8.0},1.0,{1.90,0.24},100,{0.98,0.98,0.95,0.75,1.00},  {0.99,0.98,0.98,0.85,0.97},             {0.01,0.02,0.04,0.1,0.02}        ,YES,INVERSION_SOME_MIXING ,{/*SDR*/5,5,5,5,5,4,Roger_source}}
, {341,"Plow, moldboard, conservation"                                           ,"TI003" ,{0.0,0.0,0.0},1.00,{0.0,6.0,10.},2.0,{1.90,0.24},100,{0.85,0.85,0.85,0.50,1.00},  {0.85,0.85,0.85,0.85,0.85},             {0.01,0.02,0.04,0.1,0.02}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,5,5,4,5,4,Armen_source}}
, {342,"Plow, moldboard, up hill"                                                ,"TI003" ,{5.0,3.5,6.0},1.00,{0.0,6.0,10.},4.0,{2.10,0.24},100,{0.90,0.75,0.95,0.75,1.00},  {0.75,0.75,0.75,0.75,0.85},             {0.01,0.02,0.04,0.1,0.02}        ,YES,MIXING_SOME_INVERSION ,{/*SDR*/3,5,5,4,5,4,Armen_source}}
, {343,"Plow, oxen 12 in ridge"                                                  ,"unknwn",{2.0,1.0,3.0},1.00,{0.0,6.0,7.0},12.,{0.80,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.9,0.85,0.8,0.5,0.6},                 {0.02,0.02,0.02,0.05,0.03}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {344,"Plow, oxen 18 in ridge"                                                  ,"unknwn",{2.0,1.0,3.0},1.00,{0.0,6.0,9.0},18.,{0.80,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.95,0.92,0.9,0.5,0.6},                {0.02,0.02,0.02,0.05,0.03}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {345,"Plow, oxen on 6 in ridge"                                                ,"unknwn",{2.0,1.0,3.0},1.00,{0.0,4.0,7.0},6.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.9,0.85,0.8,0.5,0.6},                 {0.02,0.02,0.02,0.05,0.03}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {346,"Plow, oxen, strip 30 pct disturb"                                        ,"unknwn",{2.0,1.0,3.0},1.00,{0.0,4.0,7.0},4.0,{0.60,0.24}, 30,{1.00,0.90,0.80,0.50,1.00},  {0.9,0.85,0.85,0.5,0.6},                {0.02,0.02,0.02,0.05,0.05}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {347,"Plow, oxen, strip 60 pct disturb"                                        ,"unknwn",{2.0,1.0,3.0},1.00,{0.0,4.0,7.0},4.0,{0.60,0.00}, 60,{1.00,0.90,0.80,0.50,1.00},  {0.9,0.85,0.85,0.5,0.6},                {0.02,0.02,0.02,0.05,0.05}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {348,"Plow, reversable"                                                        ,"unknwn",{5.0,4.0,6.0},1.00,{0.0,6.0,10.},1.0,{1.90,0.24},100,{0.85,0.80,0.70,0.60,1.00},  {0.9,0.88,0.85,0.6,0.93},               {0.05,0.06,0.07,0.15,0.05}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,5,5,5,5,4,Armen_source}}
, {349,"Power mulcher bed conditioner"                                           ,"unknwn",{3.0,1.0,5.0},0.80,{0.0,2.0,4.0},3.0,{0.70,0.24}, 85,{1.00,0.90,1.00,0.70,1.00},  {0.9,0.8,0.75,0.5,1},                   {0.07,0.08,0.1,0.12,0.07}        ,YES,MIXING_SOME_INVERSION ,{4,5,4,4,4,4,Stewart_source}}
, {350,"Pruning"                                                                 ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,NEGLIGIBLE_EFFECT     ,{/*SDR*/0,0,0,0,0,0,Armen_source}}
, {351,"Rake or windrower"                                                       ,"unknwn",{6.0,4.0,0.0},0.10,{0.0,1.0,1.0},0.0,{0.30,0.00}, 15,{0.12,0.12,0.12,0.10,0.00},  {0,0,0,0,0},                            {0,0,0,0,0}                      ,NO ,MIXING                ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {352,"Regrow"                                                                  ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,NEGLIGIBLE_EFFECT     ,{/*SDR*/0,0,0,0,0,0,Armen_source}}
, {353,"Remove Compost Sock"                                                     ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {354,"Remove Silt Fence"                                                       ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {355,"Remove Straw Bale"                                                       ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {356,"Residue, row cleaner"                                                    ,"unknwn",{5.0,3.5,6.5},0.20,{0.0,1.0,2.0},1.0,{0.30,0.00}, 20,{0.50,0.45,0.40,0.30,1.00},  {0.07,0.05,0.04,0.02,0.04},             {0,0,0,0,0}                      ,NO ,MIXING                ,{/*SDR*/2,3,1,2,2,2,Armen_source}}
, {357,"Rice residue stomper"                                                    ,"unknwn",{4.0,5.5,8.0},1.00,{0.0,2.0,5.0},0.0,{0.30,0.24},100,{1.00,0.90,1.00,0.70,1.00},  {0.7,0.6,0.5,0.5,1},                    {0.07,0.08,0.1,0.12,0.07}        ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {358,"Ripper, intra row"                                                       ,"unknwn",{4.5,4.0,6.0},0.25,{0.0,12.,18.},1.0,{0.60,0.00}, 30,{0.60,0.50,0.45,0.40,1.00},  {0.304,0.268,0.232,0.172,0.34},         {0.01,0.01,0.01,0.1,0.01}        ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {359,"Road grader"                                                             ,"unknwn",{2.0,1.0,3.0},1.00,{0.0,0.0,4.0},2.0,{0.30,0.00},  0,{1.00,0.99,0.99,0.95,0.99},  {0.99,0.99,0.99,0.95,0.9},              {0,0,0,0,0}                      ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {360,"Rodweeder"                                                               ,"TI037" ,{5.0,4.0,6.0},0.25,{0.0,2.0,4.0},0.0,{0.30,0.24},100,{0.40,0.20,0.10,0.10,1.00},  {0.15,0.15,0.1,0.05,0.15},              {0.05,0.05,0.05,0.07,0.05}       ,YES,MIXING                ,{/*SDR*/2,2,1,1,2,2,Stewart_source}}
, {361,"Roller, corrugated packer"                                               ,"TI024" ,{0.0,0.0,0.0},0.50,{0.0,1.0,2.0},1.0,{0.32,0.24},100,{0.95,0.95,0.95,0.95,1.00},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,0,0,0,1,3,Stewart_source}}
, {362,"Roller, corrugated packer 6 by 16"                                       ,"TI024" ,{0.0,0.0,0.0},1.00,{0.0,2.0,5.0},6.0,{0.40,0.24},100,{0.95,0.95,0.95,0.95,1.00},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/2,1,0,2,2,4,Roger_source}}
, {363,"Roller, on beds"                                                         ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,1.0,1.0},8.0,{0.30,0.24}, 40,{0.95,0.95,0.95,0.95,0.95},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,0,0,0,1,2,Stewart_source}}
, {364,"Roller, residue"                                                         ,"unknwn",{0.0,0.0,0.0},0.40,{0.0,1.0,1.0},0.1,{0.30,0.24}, 10,{0.95,0.95,0.95,0.95,0.95},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,YES,COMPRESSION           ,{/*SDR*/0,1,0,0,0,3,Armen_source}}
, {365,"Roller, residue incorporator"                                            ,"unknwn",{0.0,0.0,0.0},0.80,{0.0,1.0,3.0},0.0,{0.30,0.24}, 80,{0.95,0.95,0.95,0.95,0.95},  {0.35,0.3,0.25,0.25,0.5},               {0.05,0.05,0.05,0.05,0.05}       ,YES,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {366,"Roller, row shaper"                                                      ,"unknwn",{0.0,0.0,0.0},1.00,{0.0,1.0,1.0},8.0,{0.30,0.24},100,{0.95,0.95,0.95,0.95,0.95},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {367,"Roller, smooth"                                                          ,"unknwn",{0.0,0.0,0.0},0.40,{0.0,1.0,1.0},0.1,{0.30,0.24},100,{0.95,0.95,0.95,0.95,0.95},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{/*SDR*/0,0,0,0,0,2,Stewart_source}}
, {368,"Rolling basket incorporator"                                             ,"unknwn",{4.0,3.0,10.},0.50,{0.0,1.0,2.0},1.0,{0.40,0.24},100,{0.95,0.90,0.80,0.50,1.00},  {0.2,0.15,0.1,0.1,0.15},                {0.05,0.05,0.05,0.07,0.02}       ,NO ,MIXING                ,{1,3,1,1,1,0,Stewart_source}}
, {369,"Root rake"                                                               ,"unknwn",{0.0,0.0,0.0},0.75,{0.0,4.0,8.0},3.0,{1.00,0.24},100,{0.98,0.98,0.95,0.75,1.00},  {0.8,0.7,0.6,0.5,1},                    {0.05,0.06,0.07,0.02,0.05}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/1,3,2,3,3,3,Armen_source}}
, {370,"Rotary hoe"                                                              ,"TI038" ,{10.,6.0,15.},0.50,{0.0,1.0,2.5},0.0,{0.40,0.24}, 85,{0.25,0.20,0.15,0.10,1.00},  {0.2975,0.2125,0.17,0.085,0.17},                                   {0.05,0.05,0.05,0.07,0.05}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/1,1,1,3,3,1,Stewart_source}}
, {371,"Rotary hoe, on  heavy soil"                                              ,"TI038" ,{10.,6.0,15.},0.50,{0.0,1.0,2.5},0.0,{0.60,0.24}, 85,{0.25,0.20,0.15,0.10,1.00},  {0.2975,0.2125,0.17,0.085,0.17},        {0.05,0.05,0.05,0.07,0.05}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {372,"Rotary hoe, residue"                                                     ,"TI038" ,{10.,6.0,15.},0.10,{0.0,1.0,1.0},0.0,{0.30,0.24}, 85,{0.25,0.20,0.15,0.10,1.00},  {0.15,0.1,0.05,0.085,0.17},             {0.05,0.05,0.05,0.07,0.05}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {373,"Rototiller, field"                                                       ,"unknwn",{4.0,1.0,5.0},1.00,{0.0,2.0,6.0},0.0,{0.40,0.24},100,{1.00,0.90,1.00,0.70,1.00},  {0.9,0.8,0.75,0.5,1},                   {0.07,0.08,0.1,0.12,0.07}        ,YES,MIXING                ,{/*SDR*/5,5,5,5,5,4,Armen_source}}
, {374,"Rototiller, field, add residue"                                          ,"unknwn",{0.0,0.0,0.0},1.00,{0.0,2.0,6.0},0.0,{0.40,0.24},100,{1.00,0.90,1.00,0.70,1.00},  {0.9,0.8,0.75,0.5,1},                   {0.07,0.08,0.1,0.12,0.07}        ,YES,MIXING                ,{/*SDR*/5,5,5,5,5,4,Armen_source}}
, {375,"Rototiller, on beds"                                                     ,"unknwn",{3.0,1.0,5.0},0.80,{0.0,3.0,5.0},6.0,{0.70,0.24}, 60,{1.00,0.90,1.00,0.70,1.00},  {0.54,0.48,0.45,0.3,0.6},               {0.04,0.048,0.06,0.072,0.042}    ,YES,MIXING                ,{/*SDR*/5,5,5,5,5,4,Roger_source}}
, {376,"Rototiller, row cult add residue"                                        ,"unknwn",{0.0,0.0,0.0},0.80,{0.0,2.0,4.0},0.0,{0.70,0.24}, 85,{1.00,0.90,1.00,0.70,1.00},  {0.9,0.8,0.75,0.5,1},                   {0.07,0.08,0.1,0.12,0.07}        ,NO ,MIXING                ,{/*SDR*/4,4,4,4,4,4,Stewart_source}}
, {377,"Rototiller, row cultivator"                                              ,"unknwn",{3.0,1.0,5.0},0.80,{0.0,2.0,4.0},3.0,{0.70,0.24}, 85,{1.00,0.90,1.00,0.70,1.00},  {0.9,0.8,0.75,0.5,1},                   {0.07,0.08,0.1,0.12,0.07}        ,NO ,MIXING                ,{/*SDR*/4,4,4,4,4,4,Stewart_source}}
, {378,"Sand fighter"                                                            ,"unknwn",{6.0,3.0,7.0},0.50,{0.0,1.0,4.0},1.0,{0.70,0.24}, 85,{0.60,0.40,0.25,0.10,1.00},  {0.425,0.34,0.255,0.221,0.323},         {0.05,0.05,0.05,0.07,0.05}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/3,3,3,4,3,2,Armen_source}}
, {379,"Scalper, tree"                                                           ,"unknwn",{3.0,1.0,4.0},0.65,{0.0,1.0,4.0},3.0,{0.50,0.24}, 33,{0.50,0.50,0.40,0.40,1.00},  {0.6,0.45,0.3,0.2,0.6},                 {0.05,0.06,0.07,0.15,0.05}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {380,"Scarifier"                                                               ,"unknwn",{0.0,0.0,0.0},0.75,{0.0,4.0,8.0},0.0,{1.50,0.24},100,{0.60,0.40,0.25,0.10,1.00},  {0.75,0.7,0.6,0.5,0.9},                 {0.05,0.06,0.07,0.2,0.05}        ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {381,"Scraper/pan/grader, clearing/cutting"                                    ,"unknwn",{2.0,1.0,3.0},1.00,{0.0,3.0,10.},0.0,{0.80,0.00},  0,{0.95,0.95,0.95,0.95,1.00},  {0.99,0.99,0.99,0.85,0.97},             {0.01,0.02,0.04,0.1,0.02}        ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {382,"Seeder, corrugated packer"                                               ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,1.0,2.0},1.0,{0.40,0.24},100,{0.95,0.95,0.95,0.95,1.00},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {383,"Seeder, dormant, corrugated packer"                                      ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,1.0,2.0},1.0,{0.40,0.24},100,{0.95,0.95,0.95,0.95,1.00},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {384,"Seeder, high density vegetable"                                          ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,1.0,1.0},6.0,{0.30,0.24}, 75,{0.95,0.95,0.95,0.95,1.00},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {385,"Shred residue, 6 inch stubble"                                           ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.70,0.70,0.70,0.50,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {386,"Shredder, flail or rotary"                                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.90,0.90,0.90,0.85,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {387,"Shredder, flail or rotary, add other cover"                              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.60,0.60,0.60,0.85,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {388,"Shredder, flail or rotary, filberts and pecans"                          ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.60,0.60,0.60,0.85,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {389,"Shredder, rotary mower"                                                  ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {390,"Shredder, rotary, regrow veg"                                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.90,0.90,0.90,0.85,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {391,"Shredder, rotary, remove residue"                                        ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {392,"Slip plow 48 to 60 in. deep"                                             ,"unknwn",{4.5,3.0,5.0},0.40,{0.0,24.,24.},4.0,{1.20,0.24}, 30,{0.60,0.50,0.45,0.40,1.00},  {0.25,0.2,0.15,0.3225,0.4},             {0.03,0.04,0.04,0.1,0.03}        ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {393,"Sod cutter"                                                              ,"unknwn",{1.0,0.5,2.0},1.00,{0.0,0.5,1.5},0.5,{0.30,0.24},100,{ NA , NA , NA , NA , NA },  {0.001,0.001,0.001,0.001,0.001},        {0.001,0.001,0.001,0.001,0.001}  ,YES,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {394,"Sod installation"                                                        ,"unknwn",{0.0,0.0,0.0},0.00,{0.0,0.0,1.5},0.0,{0.10,0.00},  0,{ NA , NA , NA , NA , NA },  {0,0,0,0,0},                            {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {395,"Spader"                                                                  ,"unknwn",{3.5,2.0,4.0},1.00,{0.0,5.0,10.},0.0,{0.40,0.24},100,{1.00,0.90,1.00,0.70,1.00},  {0.76,0.68,0.58,0.5,0.9},               {0.05,0.06,0.07,0.2,0.05}        ,YES,LIFTING_FRACTURING    ,{5,5,5,4,5,3,Stewart_source}}
, {396,"Sprayer, defoliant"                                                      ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {397,"Sprayer, insecticide post emergence"                                     ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {398,"Sprayer, kill cover in growing crop"                                     ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.05,0.05,0.05,0.05,0.05},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {399,"Sprayer, kill cover in growing vegetables"                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.05,0.05,0.05,0.05,0.05},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {400,"Sprayer, kill crop"                                                      ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.05,0.05,0.05,0.05,0.05},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {401,"Sprayer, kill strips"                                                    ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {402,"Sprayer, post emergence"                                                 ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Armen_source}}
, {403,"Sprayer, pre-emergence"                                                  ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,3,Roger_source/*RLN based on sprayer pre emergence */}}
, {404,"Stalk chopper, rolling"                                                  ,"unknwn",{12.,10.,15.},0.75,{0.0,1.0,4.0},2.0,{0.60,0.24},100,{0.95,0.90,0.80,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.02,0.04,0.02,0.05,0.02}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {405,"Stalk chopper, rolling, on ridgetill ridges"                             ,"unknwn",{12.,10.,15.},0.75,{0.0,1.0,4.0},4.0,{0.60,0.24}, 65,{0.95,0.90,0.80,0.50,1.00},  {0.6,0.5,0.45,0.4,0.5},                 {0.01,0.01,0.01,0.01,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {406,"Stalk chopper, rolling, strip"                                           ,"unknwn",{12.,10.,15.},0.75,{0.0,1.0,4.0},2.0,{0.60,0.24}, 80,{0.95,0.90,0.80,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.02,0.04,0.02,0.05,0.02}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {407,"Stalk chopper, rotary"                                                   ,"unknwn",{12.,5.0,15.},0.75,{0.0,1.0,4.0},2.0,{0.60,0.24},100,{0.95,0.90,0.80,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.02,0.04,0.02,0.05,0.02}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {408,"Stalk chopper, strip rotary"                                             ,"unknwn",{12.,10.,15.},0.75,{0.0,1.0,4.0},2.0,{0.60,0.24}, 80,{0.95,0.90,0.80,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.02,0.04,0.02,0.05,0.02}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {409,"Stalk puller"                                                            ,"unknwn",{12.,10.,14.},0.40,{0.0,1.0,4.0},1.0,{0.90,0.24}, 40,{0.75,0.80,0.90,0.10,1.00},  {0.2,0.16,0.12,0.104,0.152},            {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{/*SDR*/2,1,0,1,1,1,Armen_source}}
, {410,"Stalk puller high disturbance"                                           ,"unknwn",{12.,10.,15.},0.65,{0.0,2.0,5.0},1.0,{0.60,0.24}, 65,{0.95,0.95,0.90,0.10,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.02,0.04,0.02,0.05,0.02}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {411,"Stalk slicer"                                                            ,"unknwn",{8.5,5.0,12.},0.40,{0.0,1.0,2.5},0.5,{0.40,0.24}, 40,{0.90,0.90,0.90,0.85,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {412,"Strip till bed conditioner"                                              ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.40,0.24}, 30,{0.30,0.25,0.20,0.10,1.00},  {0.15,0.12,0.09,0.078,0.114},           {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {413,"Striptiller w/middlebuster on beds"                                      ,"unknwn",{3.0,1.0,5.0},1.00,{0.0,4.0,7.0},8.0,{0.60,0.24}, 30,{1.00,0.90,1.00,0.70,1.00},  {0.228,0.201,0.174,0.129,0.255},        {0.07,0.08,0.10,0.12,0.07}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/4,4,3,4,4,4,Armen_source}}
, {414,"Subsoiler"                                                               ,"TI002" ,{4.5,3.0,5.0},0.80,{0.0,12.,18.},4.0,{1.20,0.24}, 75,{0.60,0.50,0.45,0.40,1.00},  {0.304,0.268,0.232,0.172,0.34},         {0.01,0.01,0.01,0.10,0.01}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/1,2,2,4,5,1,Armen_source}}
, {415,"Subsoiler bedder (ripper/hipper)"                                        ,"TI001" ,{5.0,3.0,6.0},0.90,{0.0,4.0,8.0},8.0,{1.20,0.24},100,{1.00,0.90,0.90,0.50,1.00},  {0.76,0.67,0.58,0.43,0.85},             {0.02,0.02,0.02,0.05,0.03}       ,YES,MIXING_SOME_INVERSION ,{/*SDR*/5,5,5,5,5,4,Armen_source}}
, {416,"Subsoiler ripper, 24 to 40 in. deep"                                     ,"TI001" ,{4.5,3.0,5.0},0.80,{0.0,24.,40.},4.0,{1.20,0.24}, 30,{0.60,0.50,0.45,0.40,1.00},  {0.57,0.5025,0.435,0.3225,0.6375},      {0.03,0.04,0.04,0.10,0.03}       ,NO ,LIFTING_FRACTURING    ,{/*SDR*/1,2,2,5,5,1,Armen_source}}
, {417,"Subsoiler, 12 foot spacing"                                              ,"TI002" ,{4.5,3.5,6.0},0.10,{0.0,12.,18.},3.0,{1.20,0.24}, 15,{0.30,0.25,0.20,0.20,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {418,"Subsoiler, in row"                                                       ,"TI033" ,{3.0,2.0,5.0},0.25,{0.0,12.,18.},0.0,{1.50,0.00}, 40,{0.60,0.50,0.45,0.40,1.00},  {0.304,0.268,0.232,0.172,0.34},         {0.01,0.01,0.01,0.10,0.01}       ,YES,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {419,"Subsoiler, inline heavy shanks with coulter caddy"                       ,"TI002" ,{4.5,0.0,6.0},0.80,{0.0,12.,18.},4.0,{1.20,0.00}, 90,{0.60,0.50,0.45,0.40,1.00},  {0.57,0.5025,0.435,0.3225,0.6375},      {0.03,0.04,0.04,0.10,0.03}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {420,"Subsoiler, inline with coulter caddy"                                    ,"TI002" ,{4.5,0.0,6.0},0.80,{0.0,12.,18.},4.0,{1.20,0.00}, 80,{0.60,0.50,0.45,0.40,1.00},  {0.304,0.268,0.232,0.172,0.34},         {0.01,0.01,0.01,0.10,0.01}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {421,"Subsoiler, wide spacing"                                                 ,"TI002" ,{4.5,3.5,6.0},0.10,{0.0,10.,15.},2.0,{1.20,0.24}, 25,{0.50,0.45,0.40,0.30,1.00},  {0.2,0.15,0.1,0.08,0.14},               {0.01,0.01,0.01,0.10,0.01}       ,NO ,LIFTING_FRACTURING    ,{0,1,0,2,2,1,Stewart_source}}
, {422,"Sweep plow 20-40 in wide"                                                ,"unknwn",{5.0,3.5,6.5},0.50,{0.0,2.0,5.0},2.0,{0.40,0.24},100,{0.40,0.25,0.15,0.15,1.00},  {0.3,0.2,0.15,0.05,0.25},               {0.02,0.03,0.05,0.07,0.02}       ,YES,LIFTING_FRACTURING    ,{/*SDR*/2,3,5,5,4,3,Stewart_source}}
, {423,"Sweep plow wider  than 40 in w/ mulch treader"                           ,"unknwn",{0.0,0.0,0.0},0.65,{0.0,2.0,5.0},2.0,{0.35,0.24},100,{0.85,0.70,0.60,0.50,1.00},  {0.35,0.25,0.2,0.05,0.25},              {0.02,0.03,0.05,0.07,0.02}       ,YES,COMPRESSION           ,{/*SDR*/0,0,5,5,3,3}}
, {424,"Sweep plow, under bed"                                                   ,"unknwn",{4.5,3.5,5.0},0.50,{0.0,4.0,7.0},12.,{0.40,0.24},100,{0.40,0.25,0.15,0.15,1.00},  {0.2,0.15,0.15,0.05,0.25},              {0.02,0.03,0.05,0.07,0.02}       ,YES,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {425,"Sweep plow, wider than 40 in"                                            ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,2.0,5.0},2.0,{0.40,0.24},100,{0.40,0.25,0.15,0.15,1.00},  {0.2,0.15,0.15,0.05,0.25},              {0.02,0.03,0.05,0.07,0.02}       ,YES,LIFTING_FRACTURING    ,{/*SDR*/0,0,5,5,3,3}}
, {426,"Sweep, single under row"                                                 ,"unknwn",{6.0,3.0,7.0},0.40,{0.0,2.0,6.0},1.0,{0.90,0.24}, 30,{0.75,0.80,0.90,0.10,1.00},  {0.2,0.16,0.12,0.104,0.152},            {0.01,0.01,0.01,0.02,0.01}       ,YES,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {427,"Sweep, single under row, regrow perennial"                               ,"unknwn",{6.0,3.0,7.0},0.40,{0.0,1.0,3.0},1.0,{0.90,0.24}, 50,{0.75,0.80,0.90,0.10,1.00},  {0.2,0.16,0.12,0.104,0.152},            {0.01,0.01,0.01,0.02,0.01}       ,YES,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {428,"Tree spade, holes left"                                                  ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,24.,48.},0.0,{0.00,0.00}, 40,{ NA , NA , NA , NA , NA },  {0.1,0.1,0.1,0.1,0.1},                  {0,0,0,0,0}                      ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {429,"Tree spade, holes plugged"                                               ,"unknwn",{1.0,1.0,1.0},1.00,{0.0,24.,48.},1.0,{0.30,0.00}, 10,{ NA , NA , NA , NA , NA },  {0.1,0.1,0.1,0.1,0.1},                  {0,0,0,0,0}                      ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {430,"Water mulch; off"                                                        ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {431,"Water mulch; on"                                                         ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{/*SDR*/0,0,0,0,0,5,Armen_source}}
, {432,"Weed control, manual hoe"                                                ,"unknwn",{1.0,1.0,1.0},0.90,{0.0,0.0,4.0},0.0,{0.50,0.00}, 85,{ NA , NA , NA , NA , NA },  {0.425,0.34,0.255,0.221,0.323},         {0.04,0.04,0.04,0.06,0.04}       ,NO ,MIXING_RLN            ,{/*SDR*/0,1,0,0,1,0,Armen_source}}
, {433,"Weed control, string trimmer"                                            ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {434,"Weeder, finger weeder"                                                   ,"unknwn",{0.5,0.3,1.0},0.50,{0.0,1.0,2.0},1.0,{0.70,0.24}, 50,{1.00,0.90,1.00,0.70,1.00},  {0.25,0.2,0.15,0.13,0.19},              {0.04,0.04,0.04,0.06,0.04}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {435,"Winter kill annual crop"                                                 ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.60,0.60,0.60,0.50,0.50},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {436,"default"                                                                 ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,0,Armen_source}}
, {437,"default"                                                                 ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{/*SDR*/0,0,0,0,0,0,Armen_source}}
, {438,"Stalk chopper, rolling, light disturbance"                               ,"unknwn",{12.,10.,15.},0.75,{0.0,1.0,2.0},1.0,{0.30,0.24}, 30,{0.95,0.90,0.80,0.50,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.07,0.02}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {439,"Harrow, rotary paddle wheel and spike gangs"                             ,"unknwn",{11.,8.0,15.},0.75,{0.0,0.5,2.0},1.0,{0.60,0.24},100,{0.95,0.90,0.80,0.50,1.00},  {0.73,0.63,0.55,0.4,0.73},              {0.02,0.04,0.02,0.05,0.02}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {440,"Spader, shallow depth"                                                   ,"unknwn",{3.5,2.0,4.0},1.00,{0.0,3.0,7.0},0.0,{0.40,0.24},100,{1.00,0.90,1.00,0.70,1.00},  {0.76,0.68,0.58,0.5,0.9},               {0.05,0.06,0.07,0.2,0.05}        ,YES,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {441,"temp"                                                                    ,"unknwn",{0.0,0.0,0.0},0.50,{0.0,1.0,2.0},1.0,{0.32,0.24},100,{0.95,0.95,0.95,0.95,1.00},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {442,"Fert applic. broadcast by hand"                                          ,"unknwn",{1.0,1.0,1.0},0.00,{0.0,0.0,1.0},2.0,{0.35,0.00},  5,{ NA , NA , NA , NA , NA },  {0.0003,0.0003,0.0003,0.0003,0.0003},   {0,0,0,0,0}                      ,NO ,COMPRESSION           ,{0,0,0,0,0,1,Stewart_source}}
, {443,"Sprayer, backpack, kill vegetation"                                      ,"unknwn",{1.0,1.0,1.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {444,"Sprayer, backpack, post emergence"                                       ,"unknwn",{1.0,1.0,1.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{0,0,0,0,0,1,Stewart_source}}
, {445,"Roller, crimp, covercrop"                                                ,"unknwn",{0.0,0.0,0.0},0.40,{0.0,1.0,1.0},0.1,{0.30,0.24}, 10,{0.95,0.95,0.95,0.95,0.95},  {0.05,0.05,0.05,0.05,0.05},             {0,0,0,0,0}                      ,YES,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {446,"Fert applic. side-dress, liquid"                                         ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {447,"Sprayer, post emergence and fert. tank mix"                              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{0,0,0,0,0,3,Stewart_source}}
, {448,"Weed control, hoeing in row"                                             ,"unknwn",{1.0,1.0,1.0},0.90,{0.0,0.0,4.0},0.0,{0.50,0.00}, 15,{ NA , NA , NA , NA , NA },  {0.425,0.34,0.255,0.221,0.323},         {0.04,0.04,0.04,0.06,0.04}       ,NO ,MIXING_RLN            ,{0,1,0,0,1,1,Stewart_source}}
, {449,"Sprayer, fungicide"                                                      ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {450,"Sprayer, growth regulator"                                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {451,"Planter, double disk opnr w/fluted coulter with starter fertilizer"      ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},1.0,{0.40,0.24}, 20,{0.30,0.25,0.15,0.10,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {452,"Planter, double disk opnr with starter fertilizer"                       ,"unknwn",{5.0,3.5,6.5},0.40,{0.0,2.0,4.0},2.0,{0.40,0.24}, 20,{0.30,0.25,0.20,0.10,1.00},  {0.0525,0.0375,0.03,0.015,0.03},        {0.01,0.01,0.01,0.02,0.01}       ,YES,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {453,"Harvest, onions"                                                         ,"unknwn",{5.0,4.0,6.0},0.20,{0.0,1.0,3.0},3.0,{0.30,0.24},100,{0.95,0.90,0.90,0.20,1.00},  {0.15,0.15,0.1,0.05,0.15},              {0.05,0.05,0.05,0.07,0.05}       ,YES,MIXING_SOME_INVERSION ,{2,2,1,1,2,3,Stewart_source}}
, {454,"Fert applic., aerial"                                                    ,"unknwn",{20.,20.,20.},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,NEGLIGIBLE_EFFECT     ,{0,0,0,0,0,0,Stewart_source}}
, {455,"Fert. applic. shallow anhyd knife 38 in"                                 ,"AP009" ,{5.0,3.5,6.5},0.50,{0.0,1.5,4.0},2.0,{0.60,0.24}, 15,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.05,0.05,0.05,0.07,0.05}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {456,"Harvest, tobacco, burley, mechanical harvester"                          ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {457,"Harvest, tobacco, flue cured, 1 pass mechanical"                         ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,YES,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {458,"Harvest, tobacco, flue cured, selective mechanical harvest"              ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {459,"Residue removal by wind"                                                 ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {460,"Sprayer, fungicide and insecticide tank mix"                             ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {461,"Harvest, hand pick multiple times"                                       ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {462,"Planting, broadcast interseeder"                                         ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {463,"Fert. applic. single disk opener, low disturbance, 30 inch spac"         ,"unknwn",{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},2.0,{0.60,0.24}, 15,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.05,0.05,0.05,0.07,0.05}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {464,"Grazing, set season, start ht, end ht, rate, then mowed"                 ,"unknwn",{2.7,2.0,4.1},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {465,"Grazing, set season, start ht, end ht, time on, then mowed"              ,"unknwn",{2.7,2.0,4.1},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {466,"Grazing set season, time on, time off, rate"                             ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {467,"Grazing, continuous, high traffic, set season, rate"                     ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {468,"Grazing, continuous, set season, rate"                                   ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {469,"Grazing, continuous, severe hoof traffic, set season, rate"              ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {470,"Grazing, continuous, time on, time off, rate"                            ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {471,"Grazing, frost kill"                                                     ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {472,"Grazing, set end ht, and rate"                                           ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {473,"Grazing, set end ht, and time on"                                        ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,COMPRESSION_RLN       ,{0,0,0,0,1,1,Stewart_source}}
, {474,"Grazing, set harvest portion and time on"                                ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {475,"Grazing, set harvest portion, and removal rate"                          ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {476,"Grazing, set season, harvest portion, removal rate and start mass"       ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },                                        { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {477,"Grazing, set season, start ht, end ht, rate"                             ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {478,"Grazing, set season, start ht, end ht, time on"                          ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {479,"Grazing,set season, harvest portion, start mass, and time on"            ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {480,"Harvest, hay set date"                                                   ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {481,"Harvest, hay set season, start and end ht"                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {482,"Fert. applic. anhyd, liq, dry, minimal dist. precision placmnt, 30 in"   ,"AP009" ,{6.0,4.0,8.0},0.10,{0.0,4.0,6.0},0.0,{0.30,0.24},  7,{0.40,0.40,0.40,0.40,0.40},  {0.03,0.03,0.03,0.015,0.03},                                       {0.01,0.01,0.01,0.05,0.01}       ,NO ,COMPRESSION           ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {483,"Fert. applic. anhyd, low dist. single disk opener, 30 in"                ,"AP009" ,{5.0,3.5,6.5},0.60,{0.0,3.0,6.0},2.0,{0.60,0.24}, 15,{0.50,0.45,0.40,0.30,1.00},  {0.1,0.08,0.06,0.052,0.076},            {0.05,0.05,0.05,0.07,0.05}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {484,"Mow pasture"                                                             ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {485,"Shred standing residue in live cover crop"                               ,"unknwn",{5.0,4.0,6.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{0.65,0.40,0.35,0.70,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {486,"Stop Grazing"                                                            ,"unknwn",{0.0,0.0,0.0},NA,  {NA ,NA ,NA },NA, {NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {487,"Manure injector, low disturb.15 inch"                                    ,"TI020" ,{4.0,3.5,6.5},0.40,{0.0,4.0,8.0},3.0,{0.50,0.24}, 30,{0.80,0.65,0.60,0.40,1.00},  {0.228,0.201,0.174,0.129,0.255},        {0.05,0.05,0.05,0.1 ,0.05}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {488,"Manure injector, low disturb.30 inch"                                    ,"TI020" ,{4.0,2.0,5.0},0.40,{0.0,4.0,8.0},2.0,{0.40,0.24}, 15,{0.70,0.55,0.50,0.40,1.00},  {0.114,0.1005,0.087,0.0645,0.1275},     {0.05,0.05,0.05,0.1 ,0.05}       ,NO ,LIFTING_FRACTURING    ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {489,"Harrow, disk chain"                                                      ,"unknwn",{7.5,6.0,9.0},0.50,{0.0,1.0,3.0},1.0,{0.40,0.24},100,{0.85,0.70,0.60,0.50,1.00},  {0.6,0.5,0.4,0.4,0.6},                  {0.01,0.02,0.03,0.03,0.02}       ,NO ,MIXING_SOME_INVERSION ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {490,"Harvest, woody biomass"                                                  ,"unknwn",{2.0,1.0,3.0},NA,  {NA ,NA ,NA },NA ,{NA  ,NA  },NA ,{0.60,0.50,0.40,0.30,1.00},  { NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}
, {491,"Spray, glysophate on resistant growing crop"                             ,"unknwn",{5.0,4.0,6.0},NA  ,{NA ,NA ,NA },NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },  {  NA ,  NA ,  NA ,  NA ,  NA },        { NA , NA , NA , NA , NA }       ,NO ,UNKNOWN_EFFECT        ,{UNKNOWN_invert,UNKNOWN_mix,UNKNOWN_lift,UNKNOWN_shatter,UNKNOWN_aerate,UNKNOWN_compact,UNKNOWN_SOURCE}}

// The following were removed from the original RUSLE set
// They were added here for compatibility with previous version of CS
,{ 990,"Harvest, root crops, digger"  /*peanut digger */                         ,"unknwn",{3.0,3.5,6.5},1.00,{ 7.0,6.0,8.0}, 4.0,{0.30,0.15},100,{1.00,0.90,1.00,0.70,1.00},{0.150,0.100,0.050,0.050,1.000},        {0.070,0.080,0.100,0.120,0.070} ,YES,MIXING_SOME_INVERSION   ,{4,4,3,2,4,2,Stewart_source}}
,{ 991,"Harvest, killing crop"                                                   ,"unknwn",{MSG,MSG,MSG},MSG ,{MSG ,MSG,MSG},MSG ,{MSG ,MSG },MSG,{MSG ,MSG ,MSG ,MSG ,MSG },{ MSG , MSG , MSG , MSG , MSG },        { MSG , MSG , MSG , MSG , MSG } ,YES,COMPRESSION             ,{0,0,0,0,0,3,Stewart_source}}
,{ 992,"Manure spreader"                                                         ,"unknwn",{4.0,3.0,8.0},0.10,{ 1.5,1.0,2.0}, 0.1,{0.24,0.24}, 20,{0.40,0.30,0.20,0.15,1.00},{0.070,0.050,0.040,0.020,0.040},        {0.010,0.010,0.010,0.010,0.010} ,NO ,COMPRESSION             ,{0,0,0,0,0,3,Stewart_source}}
,{ 993,"Sprayer, aerial"                                                         ,"unknwn",{20.,20.,20.},NA,  {NA ,NA ,NA } ,NA  ,{NA  ,NA  },NA ,{ NA , NA , NA , NA , NA },{ NA , NA , NA , NA , NA },             { NA , NA , NA , NA , NA }      ,NO ,NEGLIGIBLE_EFFECT       ,{0,0,0,0,0,0,Stewart_source}}
,{ 994,"Cultipacker, roller"                                                     ,"TI039" ,{4.0,3.0,8.0},0.50,{ 2.0,1.0,3.0}, 1.5,{0.40,0.24},100,{0.95,0.95,0.95,0.95,1.00},{0.250,0.200,0.150,0.100,0.250},        {0.010,0.010,0.010,0.020,0.010} ,YES,COMPRESSION             ,{0,0,0,0,0,3,Roger_source}}
,{  0,"unknown"                                                                  ,"unknwn",{0.0,0.0,0.0},NA  ,{NA ,NA ,NA } ,NA  ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },        { NA , NA , NA , NA , NA }      ,NO ,UNKNOWN_EFFECT          ,{/*SDR*/0,0,0,0,0,0,UNKNOWN_SOURCE}}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ __ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ __ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ __ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ __ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

#else
 {  0,"unknown"                                                ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{  1,"Add mulch"                                              ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{  2,"Aerator, field surface, ground driven"                  ,{6.0,3.5,6.5},0.50,{ 6.0,3.0,8.0}, 0.0,{0.60,0.26}, 50,{0.85,0.70,0.60,0.50,1.00},{0.250,0.200,0.150,0.130,0.190},{0.010,0.010,0.010,0.010,0.010},NO ,LIFTING_FRACTURING}
,{  3,"Aerial seeding"                                         ,{0.0,0.0,0.0},0.00,{ 0.0,0.0,0.0}, 0.0,{0.00,0.00},  0,{0.00,0.00,0.00,0.00,0.00},{0.000,0.000,0.000,0.000,0.000},{0.000,0.000,0.000,0.000,0.000},NO ,NEGLIGIBLE_EFFECT}
,{  4,"Bale straw or residue"                                  ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.30,0.20,0.50,0.50,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{  5,"Bed shaper"                                             ,{5.0,3.5,6.5},0.60,{ 4.0,3.0,6.0}, 8.0,{0.60,0.24}, 75,{0.50,0.45,0.40,0.30,1.00},{0.380,0.300,0.230,0.200,0.280},{0.020,0.020,0.020,0.700,0.200},NO ,MIXING_SOME_INVERSION}
,{  6,"Bed shaper, 12 in"                                      ,{5.0,0.4,6.5},0.60,{ 4.0,3.0,6.0},12.0,{0.60,0.24}, 75,{0.95,0.80,0.75,0.30,1.00},{0.380,0.300,0.230,0.200,0.280},{0.020,0.020,0.020,0.700,0.200},YES,MIXING_SOME_INVERSION}
,{  7,"Bedder, hipper, disk hiller"                            ,{5.0,3.0,6.0},0.90,{ 4.0,2.0,5.0}, 8.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},{0.950,0.920,0.850,0.500,0.600},{0.020,0.020,0.020,0.050,0.030},YES,MIXING_SOME_INVERSION}
,{  8,"Bedder, hipper, hiller 12 in high"                      ,{5.0,3.0,6.0},1.00,{ 6.0,4.0,8.0},12.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},{0.950,0.920,0.850,0.500,0.600},{0.020,0.020,0.020,0.050,0.030},YES,MIXING_SOME_INVERSION}
,{  9,"Bedder, hipper, hiller 15 in high"                      ,{5.0,3.0,6.0},1.00,{ 7.0,5.0,9.0},15.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},{0.950,0.920,0.900,0.500,0.600},{0.020,0.020,0.020,0.050,0.030},YES,MIXING_SOME_INVERSION}
,{ 10,"Bedder, hipper, hiller 18 in high"                      ,{5.0,3.0,6.0},1.00,{ 8.0,6.0,10.},18.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},{0.950,0.920,0.900,0.500,0.600},{0.020,0.020,0.020,0.050,0.030},YES,MIXING_SOME_INVERSION}
,{ 11,"Begin growth"                                           ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,NEGLIGIBLE_EFFECT}
,{ 12,"Begin new growth"                                       ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,NEGLIGIBLE_EFFECT}
,{ 13,"Begin weed growth"                                      ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,NEGLIGIBLE_EFFECT}
,{ 14,"Bulldozer, clearing"                                    ,{2.0,1.0,3.0},1.00,{ 5.0,3.0,10.}, 3.0,{0.80,0.24},100,{0.95,0.95,0.95,0.95,1.00},{0.100,0.100,0.100,0.100,0.100},{0.010,0.010,0.010,0.010,0.010},YES,COMPRESSION}
,{ 15,"Burn residue"                                           ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,REMOVE_RESIDUE}
,{ 16,"Burn residue, high intensity"                           ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,REMOVE_RESIDUE}
,{ 17,"Burn residue, low intensity"                            ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,REMOVE_RESIDUE}
,{ 18,"Chisel, st. pt."                                        ,{5.0,3.5,6.5},0.75,{ 7.0,4.0,8.0}, 3.0,{1.50,0.24},100,{0.60,0.40,0.25,0.10,1.00},{0.760,0.680,0.580,0.500,0.900},{0.050,0.060,0.070,0.200,0.050},YES,MIXING_SOME_INVERSION}
,{ 19,"Chisel, st. pt. 12 in deep"                             ,{5.0,3.5,6.5},0.75,{12.0,10.,4.0}, 4.0,{1.70,0.24},100,{0.70,0.50,0.40,0.25,1.00},{0.800,0.700,0.600,0.600,0.900},{0.050,0.060,0.070,0.200,0.050},YES,MIXING_SOME_INVERSION}
,{ 20,"Chisel, st. pt. 15 in deep"                             ,{5.0,3.5,6.5},0.75,{15.0,12.,18.}, 5.0,{1.80,0.24},100,{0.75,0.60,0.50,0.40,1.00},{0.850,0.750,0.650,0.650,0.900},{0.050,0.060,0.070,0.200,0.050},YES,MIXING_SOME_INVERSION}
,{ 21,"Chisel, sweep shovel"                                   ,{5.0,3.5,6.5},0.85,{ 7.0,5.0,9.0}, 3.0,{1.20,0.24},100,{0.50,0.30,0.20,0.15,1.00},{0.600,0.450,0.300,0.200,0.600},{0.050,0.060,0.070,0.150,0.050},YES,MIXING_SOME_INVERSION}
,{ 22,"Chisel, twisted shovel"                                 ,{5.0,3.5,6.5},0.90,{ 7.0,6.0,8.0}, 6.0,{1.90,0.24},100,{0.85,0.80,0.90,0.60,1.00},{0.900,0.800,0.750,0.600,0.930},{0.050,0.060,0.070,0.150,0.050},YES,MIXING_SOME_INVERSION}
,{ 23,"Chop veg. with machete"                                 ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.85,0.80,0.75,0.75,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,ADD_OTHER_EFFECT}
,{ 24,"Cultipacker, roller"                                    ,{4.0,3.0,8.0},0.50,{ 2.0,1.0,3.0}, 1.5,{0.40,0.24},100,{0.95,0.95,0.95,0.95,1.00},{0.250,0.200,0.150,0.100,0.250},{0.010,0.010,0.010,0.020,0.010},YES,COMPRESSION}
,{ 25,"Cultivate, manually"                                    ,{1.0,1.0,1.0},0.90,{ 3.0,1.0,6.0}, 3.0,{0.80,0.24},100,{0.90,0.80,0.70,0.50,1.00},{0.500,0.300,0.250,0.100,0.100},{0.020,0.020,0.020,0.020,0.020},YES,MIXING_SOME_INVERSION}
,{ 26,"Cultivator, field 6-12 in sweeps"                       ,{6.0,3.0,8.0},0.50,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24},100,{0.80,0.70,0.60,0.30,1.00},{0.400,0.350,0.300,0.200,0.850},{0.050,0.060,0.070,0.200,0.050},YES,MIXING_SOME_INVERSION}
,{ 27,"Cultivator, field w/ spike points"                      ,{6.0,3.0,8.0},0.50,{ 4.0,2.0,6.0}, 2.0,{0.80,0.24},100,{0.80,0.70,0.40,0.30,1.00},{0.800,0.700,0.600,0.200,9.000},{0.050,0.060,0.070,0.200,0.050},YES,MIXING_SOME_INVERSION}
,{ 28,"Cultivator, hipper, disk hiller on beds"                ,{5.0,3.0,6.0},0.90,{ 2.0,1.0,4.0}, 8.0,{0.60,0.24}, 50,{1.00,0.90,0.90,0.50,1.00},{0.570,0.500,0.440,0.320,0.640},{0.010,0.010,0.010,0.020,0.010},NO ,MIXING_SOME_INVERSION}
,{ 29,"Cultivator, off bar w/disk hillers on beds"             ,{5.0,2.0,5.5},0.50,{ 2.5,2.0,4.0}, 8.0,{0.80,0.24}, 65,{0.70,0.30,0.30,0.10,1.00},{0.490,0.440,0.380,0.280,0.550},{0.010,0.010,0.010,0.020,0.010},NO ,MIXING_SOME_INVERSION}
,{ 30,"Cultivator, row - 1st pass ridge till"                  ,{5.0,3.5,6.5},0.75,{ 2.5,1.0,4.0}, 4.0,{0.70,0.24}, 85,{0.80,0.70,0.70,0.40,1.00},{0.430,0.340,0.260,0.220,0.320},{0.040,0.045,0.050,0.060,0.040},NO ,MIXING_SOME_INVERSION}
,{ 31,"Cultivator, row - 2nd pass ridge till"                  ,{5.0,3.5,6.5},0.75,{ 3.0,2.0,4.0}, 6.0,{0.70,0.24}, 85,{0.80,0.70,0.70,0.40,1.00},{0.430,0.340,0.260,0.220,0.320},{0.040,0.045,0.050,0.060,0.040},NO ,MIXING_SOME_INVERSION}
,{ 32,"Cultivator, row 1 in ridge"                             ,{5.0,2.0,5.5},0.50,{ 3.0,2.0,4.0}, 1.0,{0.30,0.24}, 75,{0.70,0.30,0.30,0.10,1.00},{0.570,0.500,0.440,0.320,0.640},{0.010,0.010,0.010,0.010,0.010},NO ,MIXING_SOME_INVERSION}
,{ 33,"Cultivator, row 3 in ridge"                             ,{5.0,2.0,5.5},0.50,{ 3.0,2.0,4.0}, 3.0,{0.60,0.24}, 90,{0.70,0.30,0.30,0.10,1.00},{0.680,0.600,0.520,0.390,0.770},{0.040,0.040,0.040,0.060,0.040},NO ,MIXING_SOME_INVERSION}
,{ 34,"Cultivator, row, high residue"                          ,{5.0,2.0,6.0},0.50,{ 2.5,2.0,4.0}, 1.0,{0.80,0.24}, 50,{0.70,0.30,0.30,0.10,1.00},{0.250,0.200,0.150,0.130,0.190},{0.040,0.040,0.040,0.060,0.040},NO ,MIXING_SOME_INVERSION}
,{ 35,"default"                                                ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{ 36,"Disk, offset, heavy"                                    ,{5.0,3.0,6.0},1.00,{ 6.0,4.0,7.0}, 4.0,{1.50,0.24},100,{1.00,0.90,0.80,0.50,1.00},{0.950,0.850,0.800,0.600,0.950},{0.050,0.060,0.070,0.080,0.050},YES,MIXING_SOME_INVERSION}
,{ 37,"Disk, offset, heavy 12 in depth"                        ,{5.0,3.0,6.0},1.00,{12.0,10.,14.}, 5.0,{1.70,0.24},100,{1.00,0.90,0.80,0.50,1.00},{0.990,0.900,0.850,0.800,0.950},{0.050,0.030,0.070,0.080,0.050},YES,MIXING_SOME_INVERSION}
,{ 38,"Disk, offset, heavy 15 in depth"                        ,{5.0,3.0,6.0},1.00,{15.0,12.,18.}, 6.0,{1.90,0.24},100,{0.98,0.98,0.95,0.75,1.00},{0.990,0.980,0.980,0.850,0.970},{0.010,0.020,0.040,0.100,0.020},YES,MIXING_SOME_INVERSION}
,{ 39,"Disk, tandem heavy primary op."                         ,{5.0,3.0,6.0},1.00,{ 6.0,4.0,7.0}, 4.0,{1.50,0.24},100,{1.00,0.90,0.80,0.50,1.00},{0.950,0.850,0.800,0.600,0.950},{0.050,0.060,0.070,0.080,0.050},YES,MIXING_SOME_INVERSION}
,{ 40,"Disk, tandem light finishing"                           ,{5.0,3.0,6.0},0.65,{ 3.0,2.0,4.0}, 1.0,{0.60,0.24},100,{0.85,0.70,0.60,0.50,1.00},{0.730,0.670,0.550,0.400,0.730},{0.020,0.040,0.020,0.050,0.020},YES,MIXING_SOME_INVERSION}
,{ 41,"Disk, tandem secondary op."                             ,{5.0,3.0,6.0},0.75,{ 5.0,3.0,6.0}, 2.0,{0.60,0.24},100,{0.85,0.70,0.60,0.50,1.00},{0.730,0.630,0.550,0.400,0.730},{0.020,0.040,0.020,0.050,0.020},YES,MIXING_SOME_INVERSION}
,{ 42,"Do all"                                                 ,{5.0,3.0,6.0},0.80,{ 4.0,3.0,6.0}, 1.0,{0.50,0.24},100,{1.00,0.90,0.80,0.50,1.00},{0.800,0.700,0.600,0.400,0.850},{0.030,0.040,0.040,0.050,0.030},YES,MIXING_SOME_INVERSION}
,{ 43,"Do all, on beds"                                        ,{5.0,3.0,6.0},0.50,{ 3.0,1.0,3.0}, 6.0,{0.40,0.24}, 80,{1.00,0.90,0.80,0.50,1.00},{0.610,0.540,0.460,0.340,0.680},{0.030,0.040,0.040,0.050,0.030},YES,MIXING_SOME_INVERSION}
,{ 44,"Drill or air seeder single disk openers 7-10 in spac."  ,{5.0,3.5,6.5},0.40,{ 0.3,2.0,4.0}, 1.0,{0.30,0.24}, 15,{0.60,0.40,0.35,0.15,1.00},{0.053,0.038,0.030,0.015,0.030},{0.010,0.010,0.010,0.050,0.010},YES,MIXING_SOME_INVERSION}
,{ 45,"Drill or air seeder, hoe opener in hvy residue"         ,{5.0,3.5,6.5},0.80,{ 4.0,3.0,6.0}, 3.0,{0.50,0.24}, 65,{0.60,0.40,0.50,0.30,1.00},{0.330,0.260,0.200,0.170,0.250},{0.010,0.010,0.010,0.030,0.010},YES,MIXING_SOME_INVERSION}
,{ 46,"Drill or air seeder, hoe/chisel openers 6-12 in spac."  ,{5.0,3.5,6.5},0.60,{ 4.0,3.0,6.0}, 3.0,{0.50,0.24}, 90,{0.60,0.40,0.50,0.30,1.00},{0.450,0.360,0.270,0.230,0.340},{0.010,0.010,0.010,0.030,0.010},YES,MIXING_SOME_INVERSION}
,{ 47,"Drill or airseeder, double disk"                        ,{5.0,3.5,6.5},0.40,{ 4.5,1.0,2.0}, 1.0,{0.30,0.24}, 65,{0.60,0.40,0.35,0.15,1.00},{0.230,0.160,0.130,0.065,0.130},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{ 48,"Drill or airseeder, double disk opener, w/ fert openers",{5.0,3.5,6.5},0.40,{ 2.5,2.0,4.0}, 2.0,{0.30,0.24}, 85,{0.65,0.50,0.45,0.15,1.00},{0.300,0.210,0.170,0.085,0.170},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{ 49,"Drill or airseeder, double disk, w/ fluted coulters"    ,{5.0,3.5,6.5},0.40,{ 0.2,1.5,2.5}, 2.0,{0.30,0.24}, 55,{0.65,0.50,0.45,0.15,1.00},{0.190,0.140,0.110,0.055,0.110},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{ 50,"Drill or airseeder, offset double disk openers"         ,{5.0,3.5,6.5},0.40,{ 2.5,2.0,4.0}, 1.0,{0.30,0.24}, 25,{0.04,0.24,0.20,0.10,1.00},{0.088,0.063,0.050,0.025,0.050},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{ 51,"Drill, air seeder, sweep or band opener"                ,{5.0,3.5,6.5},0.50,{ 2.5,2.0,4.0}, 2.0,{0.60,0.24}, 60,{0.70,0.30,0.30,0.10,1.00},{0.300,0.240,0.180,0.160,0.230},{0.040,0.040,0.040,0.060,0.040},YES,MIXING_SOME_INVERSION}
,{ 52,"Drill, deep furrow  12 to 18 in spacing"                ,{5.0,3.5,6.5},0.60,{ 4.0,3.0,6.0}, 4.0,{0.50,0.24}, 90,{0.80,0.60,0.50,0.40,1.00},{0.450,0.360,0.270,0.230,0.340},{0.030,0.030,0.040,0.100,0.500},YES,MIXING_SOME_INVERSION}
,{ 53,"Drill, heavy, direct seed, dbl disk opnr"               ,{5.0,4.0,6.0},0.95,{ 3.0,2.0,4.0}, 2.0,{0.40,0.24}, 85,{0.90,0.85,0.80,0.80,1.00},{0.430,0.340,0.260,0.220,0.320},{0.010,0.010,0.010,0.010,0.320},YES,MIXING_SOME_INVERSION}
,{ 54,"Drill, heavy, direct seed, dbl disk opnr w/row cleaners",{5.0,4.0,6.0},0.95,{ 3.0,2.0,4.0}, 2.0,{0.40,0.24}, 90,{0.90,0.85,0.80,0.80,1.00},{0.450,0.360,0.270,0.230,0.340},{0.010,0.010,0.010,0.030,0.010},YES,MIXING_SOME_INVERSION}
,{ 55,"Drill, semi-deep furrow  12 to 18 in spacing"           ,{5.0,3.5,6.5},0.60,{ 4.0,3.0,4.0}, 3.0,{0.40,0.24}, 85,{0.80,0.60,0.50,0.40,1.00},{0.430,0.340,0.260,0.220,0.320},{0.030,0.030,0.040,0.100,0.050},YES,MIXING_SOME_INVERSION}
,{ 56,"Fert applic. anhyd knife 12 in"                         ,{5.0,3.5,6.5},0.80,{ 4.0,3.0,6.0}, 2.0,{0.60,0.24}, 50,{0.50,0.45,0.40,0.40,1.00},{0.250,0.200,0.150,0.130,0.190},{0.060,0.060,0.060,0.010,0.060},NO ,LIFTING_FRACTURING}
,{ 57,"Fert applic. deep plcmt hvy shnk"                       ,{5.0,3.5,6.5},0.80,{ 8.0,5.0,10.}, 3.0,{1.50,0.24}, 50,{0.70,0.55,0.50,0.40,1.00},{0.250,0.200,0.150,0.130,0.190},{0.050,0.050,0.050,0.010,0.050},NO ,LIFTING_FRACTURING}
,{ 58,"Fert applic. surface broadcast"                         ,{5.0,3.5,6.5},0.00,{ 1.0,1.0,1.0}, 2.0,{0.35,0.24},  5,{0.25,0.20,0.15,0.10,1.00},{0.050,0.050,0.050,0.050,0.050},{0.010,0.010,0.010,0.010,0.010},NO ,COMPRESSION}
,{ 59,"Fert. applic. anhyd knife 30 in"                        ,{5.0,3.5,6.5},0.60,{ 4.0,3.0,6.0}, 2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},{0.100,0.080,0.060,0.052,0.076},{0.050,0.050,0.050,0.070,0.050},NO ,LIFTING_FRACTURING}
,{ 60,"Fert. applic., strip-till 30 in"                        ,{5.0,3.5,6.5},0.60,{ 5.0,4.0,10.}, 4.0,{0.60,0.24}, 33,{0.50,0.45,0.40,0.30,1.00},{0.170,0.130,0.099,0.086,0.130},{0.040,0.040,0.040,0.060,0.040},NO ,LIFTING_FRACTURING}
,{ 61,"Furrow diker"                                           ,{4.0,3.0,8.0},0.50,{ 4.0,3.0,5.0}, 8.0,{0.50,0.24}, 35,{0.60,0.50,0.30,0.10,1.00},{0.180,0.140,0.110,0.091,0.130},{0.040,0.040,0.040,0.060,0.040},NO ,MIXING_SOME_INVERSION}
,{ 62,"Furrow shaper, torpedo"                                 ,{5.0,3.5,6.5},1.00,{ 3.0,2.0,4.0}, 8.0,{0.24,0.24}, 60,{0.50,0.45,0.40,0.30,1.00},{0.300,0.240,0.180,0.160,0.230},{0.100,0.010,0.010,0.020,0.010},NO ,COMPRESSION}
,{ 63,"Graze, continuous"                                      ,{1.0,1.0,1.0},1.00,{ 2.0,1.0,3.0}, 0.0,{0.60,0.60},100,{ NA , NA , NA , NA , NA },{0.200,0.150,0.100,0.050,1.000},{0.000,0.000,0.000,0.000,0.000},NO ,COMPRESSION}
,{ 64,"Graze, intensive rotational"                            ,{1.0,1.0,1.0},1.00,{ 2.0,1.0,3.0}, 0.0,{0.60,0.60},100,{ NA , NA , NA , NA , NA },{0.200,0.150,0.100,0.050,1.000},{0.000,0.000,0.000,0.000,0.000},NO ,COMPRESSION}
,{ 65,"Graze, rotational"                                      ,{1.0,1.0,1.0},1.00,{ 2.0,1.0,3.0}, 0.0,{0.60,0.60},100,{ NA , NA , NA , NA , NA },{0.200,0.150,0.100,0.050,1.000},{0.000,0.000,0.000,0.000,0.000},NO ,COMPRESSION}
,{ 66,"Graze, stubble or residue"                              ,{1.0,1.0,1.0},1.00,{ 2.0,1.0,3.0}, 0.0,{0.60,0.60},100,{ NA , NA , NA , NA , NA },{0.200,0.150,0.100,0.050,0.500},{0.000,0.000,0.000,0.000,0.000},NO ,COMPRESSION}
,{ 67,"Harrow, coiled tine"                                    ,{6.0,3.0,7.0},0.25,{ 2.0,1.0,3.0}, 1.0,{0.40,0.24},100,{0.50,0.30,0.20,0.10,1.00},{0.250,0.200,0.150,0.100,0.250},{0.010,0.010,0.010,0.200,0.010},YES,MIXING_SOME_INVERSION}
,{ 68,"Harrow, heavy"                                          ,{4.0,3.0,8.0},0.50,{ 3.0,2.0,4.0}, 2.0,{0.40,0.24},100,{0.80,0.70,0.60,0.60,1.00},{0.350,0.300,0.250,0.200,0.500},{0.010,0.010,0.010,0.200,0.010},YES,MIXING_SOME_INVERSION}
,{ 69,"Harrow, rotary"                                         ,{6.0,3.0,10.},0.50,{ 1.5,1.0,2.5}, 1.0,{0.40,0.24},100,{0.85,0.70,0.60,0.50,1.00},{0.300,0.250,0.150,0.100,0.150},{0.010,0.010,0.010,0.070,0.020},NO ,MIXING_SOME_INVERSION}
,{ 70,"Harrow, spike tooth"                                    ,{6.0,3.0,7.0},0.40,{ 2.0,1.0,3.0}, 1.0,{0.40,0.24},100,{0.60,0.40,0.25,0.10,1.00},{0.300,0.250,0.200,0.100,0.300},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{ 71,"Harrow, tine, on beds"                                  ,{5.0,3.5,6.5},0.25,{ 0.2,1.0,3.0}, 8.0,{0.30,0.24}, 60,{0.50,0.30,0.20,0.10,1.00},{0.210,0.150,0.120,0.060,0.120},{0.010,0.010,0.010,0.020,0.010},NO ,MIXING_SOME_INVERSION}
,{ 72,"Harvest, banana"                                        ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.50,0.50,0.70,0.50,0.50},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{ 73,"Harvest, banana remove stem"                            ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.50,0.50,0.50,0.50,0.50},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{ 74,"Harvest, broccoli and cauliflower"                      ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 75,"Harvest, cabbage and head lettuce"                      ,{1.0,0.5,1.5}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.20,0.15,0.10,0.10,0.50},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 76,"Harvest, corn silage with cover crop"                   ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.20,0.20,0.20,0.20,0.20},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{ 77,"Harvest, cotton"                                        ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.10,0.10,0.10,0.10,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 78,"Harvest, cotton and shred"                              ,{4.0,0.0,8.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.90,0.90,0.90,0.85,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 79,"Harvest, cut flowers"                                   ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 80,"Harvest, forage sorghum"                                ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.60,0.50,0.40,0.30,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{ 81,"Harvest, grain, grow cover"                             ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.95,0.50,0.85,0.80,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 82,"Harvest, grass or legume seed, leave forage"            ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.65,0.50,0.45,0.80,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 83,"Harvest, grass seed, remove forage"                     ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.50,0.50,0.50,0.50,0.50},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{ 84,"Harvest, hand pick"                                     ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{ 85,"Harvest, hand pull"                                     ,{1.0,1.0,1.0},0.40,{ 5.0,1.0,10.}, 3.0,{2.00,0.24},100,{0.95,0.95,0.95,0.95,1.00},{0.500,0.500,0.500,0.500,0.500},{0.010,0.010,0.010,0.010,0.010},YES,MIXING_SOME_INVERSION}
,{ 86,"Harvest, hay, grass"                                    ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 87,"Harvest, hay, legume"                                   ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 88,"Harvest, hay, no regrowth"                              ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 89,"Harvest, kenaf"                                         ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 90,"Harvest, killing crop"                                  ,{MSG,MSG,MSG},MSG ,{MSG ,MSG,MSG},MSG ,{MSG ,MSG },MSG,{MSG ,MSG ,MSG ,MSG ,MSG },{ MSG , MSG , MSG , MSG , MSG },{ MSG , MSG , MSG , MSG , MSG },YES,UNKNOWN_EFFECT}
,{ 91,"Harvest, leafy veg."                                    ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 92,"Harvest, legume seed, remove forage"                    ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.50,0.50,0.50,0.50,0.50},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{ 93,"Harvest, peanut digger"                                 ,{3.0,3.5,6.5},1.00,{ 7.0,6.0,8.0}, 4.0,{0.30,0.15},100,{1.00,0.90,1.00,0.70,1.00},{0.150,0.100,0.050,0.050,1.000},{0.070,0.080,0.100,0.120,0.070},YES,MIXING_SOME_INVERSION}
,{ 94,"Harvest, plantains"                                     ,{MSG,MSG,MSG},MSG ,{MSG ,MSG,MSG},MSG ,{MSG ,MSG },MSG,{MSG ,MSG ,MSG ,MSG ,MSG },{ MSG , MSG , MSG , MSG , MSG },{ MSG , MSG , MSG , MSG , MSG },YES,UNKNOWN_EFFECT}
,{ 95,"Harvest, root crops, digger"  /*peanut digger */        ,{3.0,3.5,6.5},1.00,{ 7.0,6.0,8.0}, 4.0,{0.30,0.15},100,{1.00,0.90,1.00,0.70,1.00},{0.150,0.100,0.050,0.050,1.000},{0.070,0.080,0.100,0.120,0.070},YES,MIXING_SOME_INVERSION}
,{ 96,"Harvest, rootcrops, manually"                           ,{1.0,1.0,1.0},0.70,{ 8.0,1.0,24.}, 3.0,{1.90,0.24}, 40,{0.50,0.50,0.50,0.50,0.50},{0.300,0.270,0.230,0.170,0.240},{0.070,0.080,0.100,0.120,0.070},YES,MIXING_SOME_INVERSION}
,{ 97,"Harvest, silage"                                        ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 98,"Harvest, snapper header"                                ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.30,0.30,0.30,0.30,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{ 99,"Harvest, stripper header"                               ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.10,0.10,0.10,0.10,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{100,"Harvest, sugarcane, after burning"                      ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{101,"Harvest, sugarcane, modern"                             ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{102,"Harvest, sugarcane, old type"                           ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{103,"Harvest, tobacco, burley"                               ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.95,0.50,0.85,0.80,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{104,"Harvest, tobacco, flue cured"                           ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{105,"Kill crop"                                              ,{NA ,NA ,NA }, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,UNKNOWN_EFFECT}
,{106,"Knife, windrow dry beans"                               ,{5.0,3.5,6.5},0.50,{ 2.0,2.0,3.0}, 3.0,{0.40,0.24},100,{1.00,0.90,1.00,0.70,1.00},{0.250,0.150,0.100,0.050,0.250},{0.020,0.030,0.050,0.070,0.020},YES,LIFTING_FRACTURING}
,{107,"Land plane"                                             ,{4.0,3.0,8.0},0.50,{ 2.0,1.0,6.0}, 0.1,{0.30,0.24},100,{0.95,0.95,0.95,0.95,0.95},{0.050,0.050,0.050,0.050,0.050},{0.010,0.010,0.010,0.010,0.010},NO ,COMPRESSION}
,{108,"Lister, 40 in"                                          ,{4.5,3.5,5.0},1.00,{ 6.0,4.0,7.0}, 8.0,{0.80,0.24},100,{1.00,0.90,0.90,0.50,1.00},{0.950,0.920,0.900,0.600,0.900},{0.020,0.020,0.020,0.050,0.030},YES,MIXING_SOME_INVERSION}
,{109,"Manure injector"                                        ,{4.0,0.4,6.5},0.80,{ 6.0,4.0,10.}, 6.0,{1.50,0.24}, 50,{0.60,0.50,0.45,0.40,1.00},{0.380,0.340,0.290,0.220,0.430},{0.050,0.050,0.050,0.100,0.050},NO ,LIFTING_FRACTURING}
,{110,"Manure spreader"                                        ,{4.0,3.0,8.0},0.10,{ 1.5,1.0,2.0}, 0.1,{0.24,0.24}, 20,{0.40,0.30,0.20,0.15,1.00},{0.070,0.050,0.040,0.020,0.040},{0.010,0.010,0.010,0.010,0.010},NO ,COMPRESSION}
,{111,"Middle buster, digger"                                  ,{5.0,3.0,6.0},1.00,{ 8.0,4.0,12.}, 8.0,{0.60,0.24},100,{1.00,0.90,0.90,0.50,1.00},{0.950,0.920,0.900,0.500,0.600},{0.020,0.020,0.020,0.050,0.030},YES,MIXING_SOME_INVERSION}
,{112,"Mower, swather, windrower"                              ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{1.00,0.90,1.00,0.70,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO /*130501 YES*/,UNKNOWN_EFFECT}
,{113,"Mulch treader"                                          ,{4.0,3.0,8.0},0.50,{ 2.0,1.0,3.0}, 0.0,{0.40,0.24},100,{0.85,0.70,0.60,0.50,1.00},{0.400,0.500,0.300,0.400,0.730},{0.010,0.010,0.010,0.070,0.020},NO ,MIXING_SOME_INVERSION}
,{114,"No operation"                                           ,{0.0,0.0,0.0},0.00,{ 0.0,0.0,0.0}, 0.0,{0.00,0.00},  0,{0.00,0.00,0.00,0.00,0.00},{0.000,0.000,0.000,0.000,0.000},{0.000,0.000,0.000,0.000,0.000},NO ,UNKNOWN_EFFECT}
,{115,"Para-plow or para-till"                                 ,{3.0,2.0,5.0},0.25,{12.0,10.,15.}, 3.0,{1.90,0.24}, 75,{0.60,0.50,0.45,0.40,1.00},{0.380,0.300,0.230,0.200,0.280},{0.020,0.020,0.020,0.030,0.020},NO ,LIFTING_FRACTURING}
,{116,"Permeable weed barrier applicator"                      ,{2.0,1.0,3.0},0.60,{ 3.0,2.0,5.0}, 3.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{117,"Planter, double disk opnr"                              ,{5.0,3.5,6.5},0.40,{ 2.5,2.0,4.0}, 2.0,{0.40,0.24}, 15,{0.30,0.25,0.20,0.10,1.00},{0.053,0.038,0.030,0.015,0.030},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{118,"Planter, double disk opnr w/fluted coulter"             ,{5.0,3.5,6.5},0.40,{ 2.5,2.0,4.0}, 1.0,{0.40,0.24}, 15,{0.30,0.25,0.15,0.10,1.00},{0.053,0.038,0.030,0.015,0.030},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{119,"Planter, double disk opnr, 18 in rows"                  ,{5.0,3.5,6.5},0.40,{ 2.5,2.0,4.0}, 2.0,{0.40,0.24},  0,{0.30,0.25,0.20,0.10,1.00},{0.880,0.063,0.050,0.025,0.050},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{120,"Planter, in-row subsoiler"                              ,{3.0,2.0,5.0},0.25,{15.0,12.,0.2}, 3.0,{1.50,0.24}, 40,{0.60,0.50,0.45,0.40,1.00},{0.300,0.270,0.230,0.170,0.340},{0.010,0.010,0.010,0.100,0.010},YES,LIFTING_FRACTURING}
,{121,"Planter, ridge till"                                    ,{5.0,3.5,6.5},0.40,{ 2.5,2.0,4.0}, 4.0,{0.40,0.24}, 30,{ NA , NA , NA , NA , NA },{0.150,0.120,0.090,0.078,0.110},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{122,"Planter, runner opener"                                 ,{4.0,2.0,6.0},0.50,{ 2.5,1.0,3.5}, 3.0,{0.40,0.24}, 20,{0.30,0.25,0.20,0.10,1.00},{0.070,0.050,0.040,0.020,0.040},{0.010,0.010,0.010,0.050,0.010},NO ,MIXING_SOME_INVERSION}
,{123,"Planter, small veg seed"                                ,{2.0,1.0,3.0},0.40,{ 1.5,1.0,2.0}, 1.0,{0.30,0.24}, 15,{ NA , NA , NA , NA , NA },{0.053,0.038,0.030,0.015,0.030},{0.010,0.010,0.010,0.050,0.010},NO ,MIXING_SOME_INVERSION}
,{124,"Planter, strip till"                                    ,{5.0,3.5,6.5},0.40,{ 2.5,2.0,4.0}, 2.0,{0.40,0.24}, 30,{0.30,0.25,0.20,0.10,1.00},{0.100,0.075,0.060,0.030,0.060},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{125,"Planter, sugarcane"                                     ,{2.0,1.0,3.0},0.40,{ 6.0,4.0,8.0}, 2.0,{0.40,0.24}, 20,{0.30,0.25,0.20,0.10,1.00},{0.100,0.080,0.060,0.052,0.076},{0.010,0.010,0.010,0.020,0.010},NO ,MIXING_SOME_INVERSION}
,{126,"Planter, transplanter, vegetable"                       ,{2.0,1.0,3.0},0.40,{ 6.0,4.0,8.0}, 2.0,{0.40,0.24}, 20,{0.30,0.25,0.20,0.10,1.00},{0.070,0.050,0.040,0.020,0.040},{0.010,0.010,0.010,0.020,0.010},NO ,MIXING_SOME_INVERSION}
,{127,"Planter, transplanter, vegetable, no-till"              ,{2.0,1.0,3.0},0.40,{ 6.0,4.0,8.0}, 1.0,{0.40,0.24}, 20,{0.30,0.25,0.15,0.10,1.00},{0.070,0.050,0.040,0.020,0.040},{0.010,0.010,0.010,0.020,0.010},NO ,MIXING_SOME_INVERSION}
,{128,"Planting, broadcast seeder"                             ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,NEGLIGIBLE_EFFECT}
,{129,"Planting, hand 10 percent dist."                        ,{1.0,1.0,1.0},0.50,{ 2.0,1.0,3.0}, 1.0,{0.30,0.50}, 10,{ NA , NA , NA , NA , NA },{0.050,0.040,0.030,0.020,0.038},{0.010,0.010,0.010,0.050,0.010},NO ,MIXING_SOME_INVERSION}
,{130,"Planting, hand 5 percent dist."                         ,{1.0,1.0,1.0},0.50,{ 2.0,1.0,3.0}, 1.0,{0.30,0.24}, 10,{ NA , NA , NA , NA , NA },{0.025,0.020,0.015,0.013,0.019},{0.070,0.080,0.100,0.120,0.070},NO ,MIXING_SOME_INVERSION}
,{131,"Planting, manual"                                       ,{1.0,1.0,1.0},0.50,{ 2.0,1.0,3.0}, 1.0,{0.90,0.24}, 30,{ NA , NA , NA , NA , NA },{0.150,0.120,0.090,0.078,0.110},{0.007,0.008,0.010,0.120,0.010},NO ,MIXING_SOME_INVERSION}
,{132,"Planting, no-til manually"                              ,{1.0,1.0,1.0},0.50,{ 2.0,1.0,3.0}, 1.0,{0.30,0.24}, 30,{ NA , NA , NA , NA , NA },{0.110,0.075,0.060,0.030,0.060},{0.010,0.010,0.010,0.020,0.010},NO ,MIXING_SOME_INVERSION}
,{133,"Plastic mulch applic. 40 inch beds 100 percent cover"   ,{2.0,1.0,4.0},0.10,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{134,"Plastic mulch applic. 40 inch beds 75 percent cover"    ,{2.0,1.0,4.0},0.10,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{135,"Plastic mulch applic. 48 inch beds 100 percent cover"   ,{2.0,1.0,4.0},0.10,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{136,"Plastic mulch applic. 48 inch beds 80 percent cover"    ,{2.0,1.0,4.0},0.10,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{137,"Plastic mulch applic. 54 inch beds 100 percent cover"   ,{2.0,1.0,4.0},0.10,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{138,"Plastic mulch applic. 54 inch beds 80 percent cover"    ,{2.0,1.0,4.0},0.10,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{139,"Plastic mulch applic. 64 inch beds 100 percent cover"   ,{2.0,1.0,4.0},0.10,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{140,"Plastic mulch applic. 64 inch beds 85 percent cover"    ,{2.0,1.0,4.0},0.10,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{141,"Plastic mulch applicator 100 percent cover"             ,{2.0,1.0,4.0},0.50,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{142,"Plastic mulch applicator 40 percent cover"              ,{2.0,1.0,4.0},0.60,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.050,0.050,0.050,0.070,0.050},NO ,MIXING_SOME_INVERSION}
,{143,"Plastic mulch applicator 75 percent cover"              ,{2.0,1.0,4.0},0.60,{ 3.0,2.0,4.0}, 2.0,{0.60,0.24}, 20,{ NA , NA , NA , NA , NA },{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,MIXING_SOME_INVERSION}
,{144,"Plastic mulch, 05 percent removal"                      ,{2.0,3.0,4.0},0.60,{ 2.0,1.0,3.0}, 2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,LIFTING_FRACTURING}
,{145,"Plastic mulch, 10 percent removal"                      ,{2.0,3.0,4.0},0.60,{ 2.0,1.0,3.0}, 2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,LIFTING_FRACTURING}
,{146,"Plastic mulch, 25 percent removal"                      ,{2.0,3.0,4.0},0.60,{ 2.0,1.0,3.0}, 2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,LIFTING_FRACTURING}
,{147,"Plastic mulch, 50 percent  removal"                     ,{2.0,3.0,4.0},0.60,{ 2.0,1.0,3.0}, 2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,LIFTING_FRACTURING}
,{148,"Plastic mulch, remove"                                  ,{2.0,3.0,4.0},0.60,{ 2.0,1.0,3.0}, 2.0,{0.60,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},{0.100,0.080,0.060,0.052,0.076},{0.020,0.020,0.020,0.050,0.030},NO ,LIFTING_FRACTURING}
,{149,"Plow, disk"                                             ,{5.0,3.5,6.0},1.00,{ 6.0,4.0,8.0}, 1.0,{1.90,0.24},100,{0.98,0.98,0.95,0.75,1.00},{0.890,0.880,0.880,0.750,1.000},{0.010,0.020,0.040,0.100,0.020},YES,MIXING_SOME_INVERSION}
,{150,"Plow, moldboard"                                        ,{5.0,3.5,6.0},1.00,{ 8.0,6.0,10.}, 1.0,{1.90,0.24},100,{1.00,1.00,1.00,0.75,1.00},{0.990,0.990,0.990,0.850,0.970},{0.010,0.020,0.040,0.100,0.020},YES,INVERSION_SOME_MIXING}
,{151,"Plow, moldboard, conservation"                          ,{4.0,3.0,8.0},1.00,{ 8.0,6.0,10.}, 2.0,{1.90,0.24},100,{0.85,0.85,0.85,0.50,1.00},{0.850,0.850,0.850,0.850,0.850},{0.010,0.020,0.040,0.100,0.020},YES,MIXING_SOME_INVERSION}
,{152,"Plow, moldboard, up hill"                               ,{5.0,3.5,6.0},1.00,{ 8.0,6.0,10.}, 4.0,{2.10,0.24},100,{0.90,0.75,0.95,0.75,1.00},{0.750,0.750,0.750,0.750,0.850},{0.010,0.020,0.040,0.100,0.020},YES,MIXING_SOME_INVERSION}
,{153,"Plow, reversable"                                       ,{5.0,4.0,6.0},1.00,{ 8.0,6.0,10.}, 1.0,{1.90,0.24},100,{0.85,0.80,0.70,0.60,1.00},{0.900,0.880,0.850,0.600,0.930},{0.050,0.060,0.070,0.150,0.050},YES,MIXING_SOME_INVERSION}
,{154,"Pruning"                                                ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,NEGLIGIBLE_EFFECT}
,{155,"Regrow"                                                 ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
,{156,"Residue, row cleaner"                                   ,{5.0,3.5,6.5},0.20,{ 1.0,1.0,2.0}, 1.0,{0.30,0.24}, 20,{0.50,0.45,0.40,0.30,1.00},{0.070,0.050,0.040,0.020,0.040},{0.010,0.010,0.010,0.010,0.010},NO ,MIXING_SOME_INVERSION}
,{157,"Rodweeder"                                              ,{5.0,4.0,6.0},0.25,{ 3.0,2.0,4.0}, 0.0,{0.40,0.24},100,{0.40,0.20,0.10,0.10,1.00},{0.150,0.150,0.100,0.050,0.150},{0.050,0.050,0.050,0.070,0.050},YES,MIXING_SOME_INVERSION}
,{158,"Roller, corrugated packer"                              ,{4.0,3.0,8.0},0.50,{ 1.5,1.0,2.0}, 1.0,{0.40,0.24},100,{0.95,0.95,0.95,0.95,1.00},{0.050,0.050,0.050,0.050,0.050},{0.010,0.010,0.010,0.010,0.010},NO ,COMPRESSION}
,{159,"Roller, on beds"                                        ,{4.0,3.0,8.0},0.50,{ 1.0,1.0,1.0}, 8.0,{0.30,0.24}, 40,{0.95,0.95,0.95,0.95,0.95},{0.050,0.050,0.050,0.050,0.050},{0.010,0.010,0.010,0.010,0.010},NO ,COMPRESSION}
,{160,"Roller, residue"                                        ,{4.0,3.0,8.0},0.40,{ 1.0,1.0,1.0}, 0.1,{0.30,0.24},100,{0.95,0.95,0.95,0.95,0.95},{0.050,0.050,0.050,0.050,0.050},{0.010,0.010,0.010,0.010,0.010},YES,COMPRESSION}
,{161,"Roller, smooth"                                         ,{4.0,3.0,8.0},0.40,{ 1.0,1.0,1.0}, 0.1,{0.30,0.24},100,{0.95,0.95,0.95,0.95,0.95},{0.050,0.050,0.050,0.050,0.050},{0.010,0.010,0.010,0.010,0.010},NO ,COMPRESSION}
,{162,"Root rake"                                              ,{4.0,3.0,8.0},0.75,{ 7.0,4.0,8.0}, 3.0,{1.00,0.24},100,{0.98,0.98,0.95,0.75,1.00},{0.800,0.700,0.600,0.400,1.000},{0.050,0.060,0.070,0.020,0.050},YES,MIXING_SOME_INVERSION}
,{163,"Rotary hoe"                                             ,{10.,6.0,15.},0.50,{ 1.5,1.0,2.5}, 0.0,{0.40,0.24}, 85,{0.25,0.20,0.15,0.10,1.00},{0.300,0.210,0.170,0.085,0.170},{0.050,0.050,0.050,0.070,0.050},NO ,MIXING_SOME_INVERSION}
,{164,"Rototiller, field"                                      ,{4.0,1.0,5.0},1.00,{ 4.0,2.0,6.0}, 0.0,{0.40,0.24},100,{1.00,0.90,1.00,0.70,1.00},{0.900,0.800,0.750,0.500,1.000},{0.070,0.080,0.100,0.120,0.070},YES,MIXING_SOME_INVERSION}
,{165,"Rototiller, field, add residue"                         ,{4.0,3.0,8.0},1.00,{ 4.0,2.0,6.0}, 0.0,{0.40,0.24},100,{1.00,0.90,1.00,0.70,1.00},{0.900,0.800,0.750,0.500,1.000},{0.070,0.080,0.100,0.120,0.070},YES,MIXING_SOME_INVERSION}
,{166,"Rototiller, row cult add residue"                       ,{4.0,3.0,8.0},0.80,{ 3.0,2.0,4.0}, 3.0,{0.70,0.24}, 85,{1.00,0.90,1.00,0.70,1.00},{0.900,0.800,0.750,0.500,1.000},{0.070,0.080,0.100,0.120,0.070},NO ,MIXING_SOME_INVERSION}
,{167,"Rototiller, row cultivator"                             ,{3.0,1.0,5.0},0.80,{ 3.0,2.0,4.0}, 3.0,{0.70,0.24}, 85,{1.00,0.90,1.00,0.70,1.00},{0.900,0.800,0.750,0.500,1.000},{0.070,0.080,0.100,0.120,0.070},NO ,MIXING_SOME_INVERSION}
,{168,"Sand fighter"                                           ,{6.0,3.0,7.0},0.50,{ 3.0,1.0,4.0}, 1.0,{0.40,0.24}, 85,{0.60,0.40,0.25,0.10,1.00},{0.430,0.340,0.260,0.220,0.320},{0.050,0.050,0.050,0.070,0.050},NO ,MIXING_SOME_INVERSION}
,{169,"Seedbed finisher"                                       ,{4.0,3.0,8.0},0.25,{ 2.0,1.0,3.0}, 1.0,{0.40,0.24},100,{0.80,0.70,0.60,0.60,1.00},{0.250,0.200,0.150,0.100,0.250},{0.010,0.010,0.010,0.020,0.010},YES,MIXING_SOME_INVERSION}
,{170,"Shredder, flail or rotary"                              ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.90,0.90,0.90,0.85,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO /*130501*/,NEGLIGIBLE_EFFECT}
,{171,"Shredder, rotary, regrow veg"                           ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.90,0.90,0.90,0.85,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO /*130501*/,NEGLIGIBLE_EFFECT}
,{172,"Shredder, rotary, remove residue"                       ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,NEGLIGIBLE_EFFECT}
,{173,"Sprayer, kill crop"                                     ,{5.0,4.0,6.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{0.15,0.10,0.10,0.50,1.00},{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },YES,NEGLIGIBLE_EFFECT}
,{174,"Sprayer, post emergence"                                ,{5.0,6.0,4.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,ADD_OTHER_EFFECT}
,{175,"Stalk puller"                                           ,{6.0,3.0,7.0},0.40,{ 4.0,2.0,6.0}, 1.0,{0.90,0.24}, 40,{0.75,0.80,0.90,0.10,1.00},{0.200,0.160,0.120,0.100,0.150},{0.010,0.010,0.010,0.020,0.010},NO ,MIXING_SOME_INVERSION}
,{176,"Striptiller w/middlebuster on beds"                     ,{3.0,1.0,5.0},1.00,{ 6.0,4.0,7.0}, 8.0,{0.60,0.24}, 30,{1.00,0.90,1.00,0.70,1.00},{0.230,0.200,0.170,0.130,0.260},{0.070,0.080,0.100,0.120,0.070},YES,MIXING_SOME_INVERSION}
,{177,"Subsoiler"                                              ,{4.5,3.0,5.0},0.08,{15.0,12.,15.}, 4.0,{1.20,0.24}, 75,{0.60,0.50,0.45,0.40,1.00},{0.570,0.580,0.440,0.320,0.640},{0.030,0.040,0.040,0.100,0.030},NO ,LIFTING_FRACTURING}
,{178,"Subsoiler bedder (ripper/hipper)"                       ,{5.0,3.0,6.0},0.90,{ 7.0,4.0,8.0}, 8.0,{1.20,0.24},100,{1.00,0.90,0.90,0.50,1.00},{0.760,0.670,0.580,0.430,0.850},{0.020,0.020,0.020,0.050,0.030},YES,MIXING_SOME_INVERSION}
,{179,"Subsoiler ripper, 24 to 40 in. deep"                    ,{4.5,3.0,5.0},0.80,{24.0,24.,24.}, 4.0,{1.20,0.24}, 30,{0.60,0.50,0.45,0.40,1.00},{0.570,0.500,0.440,0.320,0.640},{0.030,0.040,0.040,0.100,0.030},NO ,LIFTING_FRACTURING}
,{180,"Sweep plow 20-40 in wide"                               ,{5.0,3.5,6.5},0.50,{ 3.0,2.0,5.0}, 2.0,{0.40,0.24},100,{0.40,0.25,0.15,0.15,1.00},{0.300,0.200,0.150,0.050,0.250},{0.020,0.030,0.050,0.070,0.020},YES,LIFTING_FRACTURING}
,{181,"Sweep plow wider  than 40 in w/ mulch treader"          ,{4.0,3.0,8.0},0.65,{ 3.0,2.0,5.0}, 2.0,{0.35,0.24},100,{0.85,0.70,0.60,0.50,1.00},{0.350,0.250,0.200,0.050,0.250},{0.020,0.030,0.050,0.070,0.020},YES,LIFTING_FRACTURING}
,{182,"Sweep plow, wider than 40 in"                           ,{4.0,3.0,8.0},0.50,{ 3.0,2.0,4.0}, 2.0,{0.,0.24},100,{0.40,0.25,0.15,0.15,1.00},{0.200,0.150,0.150,0.050,0.250},{0.020,0.030,0.050,0.070,0.020},YES,LIFTING_FRACTURING}
,{183,"Water mulch; off"                                       ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ N40A , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,ADD_OTHER_EFFECT}
,{184,"Water mulch; on"                                        ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,ADD_OTHER_EFFECT}
,{185,"Weed control, manual hoe"                               ,{1.0,1.0,1.0},0.90,{ 3.0,1.0,4.0}, 3.0,{0.50,0.24}, 85,{ NA , NA , NA , NA , NA },{0.430,0.340,0.260,0.220,0.320},{0.040,0.040,0.040,0.060,0.040},NO ,MIXING_SOME_INVERSION}
,{999,"Seedbed finisher (stage 2)"                             ,{4.0,3.0,8.0},0.50,{ 1.5,1.0,2.0}, 1.0,{0.40,0.24},100,{0.85,0.70,0.60,0.50,1.00},{0.300,0.250,0.150,0.100,0.150},{0.010,0.010,0.010,0.070,0.020},YES,MIXING}
,{  0,"unknown"                                                ,{0.0,0.0,0.0}, NA ,{ NA ,NA ,NA }, NA ,{ NA , NA },NA ,{ NA , NA , NA , NA , NA },{  NA ,  NA ,  NA ,  NA ,  NA },{  NA ,  NA ,  NA ,  NA ,  NA },NO ,UNKNOWN_EFFECT}
#endif

};
//______________________________________________________________________________field_operation_parameters_/
#ifdef USE_NEW_RUSLE2
Field_operation_composite_parameters
field_operation_composite_parameters[]=
{

//						speed						Kills		Operation
//						rec		min		max		vegetation		strings
//	number			Operation		MPH		MPH		MPH
  {	0	,	"",{	5.0	,	3.5	,	6.5	},	YES	,{"","",""}}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
, {	1	,"Chisel plow, coulter, st. pts."                                       ,{	5.0	,	3.5	,	6.5	},	YES	,{"Coulter caddy, w/ fluted coulters","Chisel, st. pt.",0}}
, {	2	,"Chisel plow, coulter, st. pts., cover disks"                          ,{	5.0	,	3.5	,	6.5	},	YES	,{"Coulter caddy, w/ fluted coulters","Chisel, st. pt.","Disk, single gang",0}}
, {	3	,"Chisel plow, coulter, st. pts., cover disks, rlng basket"             ,{	6.0	,	5.0	,	7.5	},	YES	,{"Harrow, rotary, light, fluff residue","Chisel plow, coulter, st. pts., cover disks","Rolling basket incorporator",0}}
, {	4	,"Chisel plow, coulter, sweeps"                                         ,{	5.0	,	3.5	,	6.5	},	YES	,{"Coulter caddy, w/ fluted coulters","Chisel, sweep shovel",0}}
, {	5	,"Chisel plow, coulter, twst. pts."                                     ,{	5.0	,	3.5	,	6.5	},	YES	,{"Coulter caddy, w/ fluted coulters","Chisel, twisted shovel",0}}
, {	6	,"Chisel plow, coulter, twst. pts., cover disks"                        ,{	5.0	,	3.5	,	6.5	},	YES	,{"Coulter caddy, w/ fluted coulters","Chisel, twisted shovel","Disk, single gang",0}}
, {	7	,"Chisel plow, disk, st. pts."                                          ,{	5.0	,	3.5	,	6.5	},	YES	,{"Disk, single gang","Chisel, st. pt.","Disk, single gang",0}}
, {	8	,"Chisel plow, disk, st. pts., cover disks"                             ,{	5.0	,	3.5	,	6.5	},	YES	,{"Disk, single gang","Chisel, st. pt.","Disk, single gang",0}}
, {	9	,"Chisel plow, disk, twst. pts."                                        ,{	5.0	,	3.5	,	6.5	},	YES	,{"Disk, single gang","Chisel, twisted shovel",0}}
, {	10	,"Chisel plow, disk, twst. pts., cover disks"                           ,{	5.0	,	3.5	,	6.5	},	YES	,{"Disk, single gang","Chisel, twisted shovel","Disk, single gang",0}}

, {	11	,"Continuous disturbance and smoothing"                                 ,{	4.0	,	1.0	,	5.0	},	YES	,{"Continuous disturbance and smoothing",0}}
, {	12	,"Coulter tiller and spike harrow"                                      ,{	6.0	,	5.0	,	8.0	},	YES	,{"Coulter caddy, dbl gang w/ fluted coulters","Harrow, spike tooth",0}}
, {	13	,"Coulter tiller, 10 degree angle, coiled tine harrow, rolling basket"  ,{	6.0	,	5.0	,	8.0	},	YES	,{"Coulter caddy, dbl gang w/ fluted coulters","Harrow, coiled tine","Rolling basket incorporator",0}}
, {	14	,"Cultipacker, roller"                                                  ,{	6.0	,	0.0	,	0.0	},	NO	,{"Roller, corrugated packer","Cultivator, field w/ spike points","Roller, corrugated packer",0}}
, {	15	,"Do all"                                                               ,{	4.0	,	3.0	,	8.0	},	YES	,{"Disk, single gang","Cultivator, field 6-12 in sweeps","Harrow, coiled tine","Rolling basket incorporator",0}}
, {	16	,"Do all, on beds"                                                      ,{	5.0	,	3.0	,	6.0	},	NO	,{"Cultivator, hipper, disk hiller on beds","Bed shaper",0}}
, {	17	,"Harvest, knife, windrow, combine"                                     ,{	5.0	,	3.5	,	6.5	},	YES	,{"Knife, windrow dry beans","Harvest, windrows",0}}
, {	18	,"Planter, potato, 6 in beds"                                           ,{	4.5	,	3.5	,	5.0	},	YES	,{"Bedder, hipper, disk hiller","Planter, double disk opener on 8 inch high beds",0}}
, {	19	,"Reel disk vertical tiller"                                            ,{	6.0	,	5.0	,	8.0	},	YES	,{"Coulter caddy, with smooth coulters","Stalk chopper, rolling","Harrow, spike tooth","Rolling basket incorporator",0}}
, {	20	,"Residue conditioner, coil tine har, rlng bskt",{	0.0	,	0.0	,	0.0	},	NO	,{"Harrow, heavy on heavy resdue","Rolling basket incorporator",0}}
, {	21	,"Ripper, intra row and furrow diker",{	4.5	,	4.0	,	6.0	},	NO	,{"Ripper, intra row","Furrow diker",0}}
, {	22	,"Roller harrow",{	0.0	,	0.0	,	0.0	},	YES	,{"Roller, corrugated packer","Cultivator, field w/ spike points","Roller, corrugated packer",0}}
, {	23	,"Seedbed conditioner, coil tine har, rlng bskt",{	5.0	,	4.0	,	0.0	},	YES	,{"Harrow, coiled tine","Rolling basket incorporator",0}}
, {	24	,"Seedbed conditioner, coulter caddy, coil tine har",{	6.0	,	5.0	,	0.0	},	YES	,{"Coulter caddy, dbl gang w/ fluted coulters","Harrow, coiled tine",0}}
, {	25	,"Seedbed conditioner, coulter caddy, coil tine har, rlng bskt",{	6.0	,	5.0	,	0.0	},	YES	,{"Coulter caddy, dbl gang w/ fluted coulters","Harrow, coiled tine","Rolling basket incorporator",0}}
, {	26	,"Seedbed conditioner, coulter caddy, field cult, spike harrow",{	6.0	,	5.0	,	0.0	},	YES	,{"Coulter caddy, dbl gang w/ fluted coulters","Cultivator, field 6-12 in sweeps","Harrow, spike tooth",0}}
, {	27	,"Seedbed conditioner, coulter caddy, rtry har",{	6.0	,	5.0	,	0.0	},	YES	,{"Coulter caddy, dbl gang w/ fluted coulters","Harrow, rotary",0}}
, {	28	,"Seedbed conditioner, coulter caddy, rtry har, rlng bskt",{	6.0	,	5.0	,	8.0	},	YES	,{"Coulter caddy, dbl gang w/ fluted coulters","Harrow, rotary","Rolling basket incorporator",0}}
, {	29	,"Seedbed conditioner, coulter caddy, spk har",{	6.0	,	5.0	,	0.0	},	YES	,{"Coulter caddy, dbl gang w/ fluted coulters","Harrow, spike tooth",0}}
, {	30	,"Seedbed conditioner, coulter caddy, spk har, rlng bskt",{	6.0	,	5.0	,	0.0	},	YES	,{"Coulter caddy, dbl gang w/ fluted coulters","Harrow, spike tooth","Rolling basket incorporator",0}}
, {	31	,"Seedbed finisher",{	0.0	,	0.0	,	0.0	},	YES	,{"Cultivator, field w/ spike points","Rolling basket incorporator",0}}
, {	32	,"Seedbed finisher, fld cult, chop, spk har, rlng bskt",{	6.0	,	0.0	,	0.0	},	YES	,{"Cultivator, field 6-12 in sweeps","Stalk chopper, rolling","Harrow, spike tooth","Rolling basket incorporator",0}}
, {	33	,"Seedbed finisher, fld cult, mlch trdr",{	0.0	,	0.0	,	0.0	},	YES	,{"Cultivator, field 6-12 in sweeps","Cultivator, rotary",0}}
, {	34	,"Seedbed finisher, fld cult, rtry har",{	0.0	,	0.0	,	0.0	},	YES	,{"Cultivator, field 6-12 in sweeps","Harrow, rotary",0}}
, {	35	,"Seedbed finisher, sngl disk, fld cult, coil tine har, rollng bskt",{	0.0	,	0.0	,	0.0	},	YES	,{"Disk, single gang","Cultivator, field 6-12 in sweeps","Harrow, coiled tine","Rolling basket incorporator",0}}
, {	36	,"Seedbed finisher, sngl disk, rotry har",{	0.0	,	0.0	,	0.0	},	YES	,{"Disk, single gang","Harrow, rotary",0}}
, {	37	,"Seedbed finisher, sngl dsk, fld cult, coil tine har",{	0.0	,	0.0	,	0.0	},	YES	,{"Disk, single gang","Cultivator, field 6-12 in sweeps","Harrow, coiled tine",0}}
, {	38	,"Subsoil disk ripper",{	0.0	,	0.0	,	0.0	},	YES	,{"Disk, tandem secondary op.","Subsoiler","Disk, single gang",0}}
, {	39	,"Subsoiler leveler",{	4.5	,	0.0	,	5.0	},	NO	,{"Subsoiler","Roller, on beds",0}}
, {	40	,"Subsoiler, in row strip conditioner",{	3.0	,	2.0	,	5.0	},	NO	,{"Subsoiler, in row","Strip till bed conditioner",0}}
, {	41	,"Subsoiler, rlng stlk chpr, roller, mulch treader",{	4.0	,	3.0	,	6.0	},	YES	,{"Coulter caddy, with smooth coulters","Subsoiler, wide spacing","Subsoiler, wide spacing","Stalk chopper, rolling","Coulter caddy, with smooth coulters","Subsoiler, wide spacing","Subsoiler, wide spacing","Stalk chopper, rolling","Roller, corrugated packer","Mulch treader",0}}
, {	42	,"Drill or air seeder, combo field cult, dd openers",{	0.0	,	0.0	,	0.0	},	YES	,{"Cultivator, field 6-12 in sweeps","Rolling basket incorporator","Drill or airseeder, double disk",0}}
, {	43	,"Chisel, winged with furrow diker",{	5.0	,	3.5	,	6.5	},	YES	,{"Chisel, winged with furrow diker","Furrow diker",0}}
, {	44	,"Chisel, st. pt. 5 in deep, coil tine har",{	5.0	,	3.5	,	6.5	},	YES	,{"Chisel, st. pt. 5 in deep","Harrow, coiled tine",0}}
, {	45	,"Chisel, st. pt., coil tine har",{	5.0	,	3.5	,	6.5	},	YES	,{"Chisel, st. pt.","Harrow, coiled tine",0}}
, {	46	,"Chisel, sweep shovel 5 in. depth, coil tine har",{	5.0	,	3.5	,	6.5	},	YES	,{"Chisel, sweep shovel 5 in. depth","Harrow, coiled tine",0}}
, {	47	,"Chisel, sweep shovel, coil tine har"                                  ,{	5.0	,	3.5	,	6.5	},	YES	,{"Chisel, sweep shovel","Harrow, coiled tine",0}}
, {	48	,"Chisel, twisted shovel, coil tine har"                                ,{	5.0	,	3.5	,	6.5	},	YES	,{"Chisel, twisted shovel","Harrow, coiled tine",0}}
, {	49	,"Cultivator, field 6-12 in sweeps, coil tine har"                      ,{	5.0	,	3.5	,	6.5	},	YES	,{"Cultivator, field 6-12 in sweeps","Harrow, coiled tine",0}}
, {	50	,"Cultivator, field w/ spike points, coil tine har"                     ,{	6.0	,	3.0	,	8.0	},	YES	,{"Cultivator, field w/ spike points","Harrow, coiled tine",0}}
, {	51	,"Cultivator, rotary on beds, Bedder, hipper, disk hiller"              ,{	4.0	,	2.0	,	5.5	},	NO	,{"Cultivator, rotary on beds","Bedder, hipper, disk hiller",0}}
, {	52	,"Disk, offset, heavy, roller, smooth"                                  ,{	5.0	,	3.0	,	6.0	},	YES	,{"Disk, offset, heavy","Roller, smooth",0}}
, {	53	,"Disk, tandem heavy primary op., roller, smooth"                       ,{	5.0	,	3.0	,	6.0	},	YES	,{"Disk, tandem heavy primary op.","Roller, smooth",0}}
, {	54	,"Drill or air seeder, hoe opener in hvy residue w/ fert openers"       ,{	5.0	,	3.5	,	6.5	},	YES	,{"Fert applic. shank low disturbance, 12 in","Drill or air seeder, hoe opener in hvy residue",0}}
, {	55	,"Drill or air seeder, hoe/chisel openers 12-15 in spac. w/ fert openers",{	5.0	,	3.5	,	6.5	},	YES	,{"Fert applic. shank low disturbance, 12 in","Drill or air seeder, hoe/chisel openers 12-15 in spac.",0}}
, {	56	,"Drill or air seeder, hoe/chisel openers 6-12 in spac. w/fert openers" ,{	5.0	,	3.5	,	6.5	},	YES	,{"Fert applic. shank low disturbance, 12 in","Drill or air seeder, hoe/chisel openers 6-12 in spac.",0}}
, {	57	,"Fert applic. anhyd knife 12 in, coil tine har"                        ,{	5.0	,	3.5	,	6.5	},	YES	,{"Fert applic. anhyd knife 12 in","Harrow, coiled tine",0}}
, {	58	,"Fert applic. shank low disturbance, 12 in, coil tine har"             ,{	5.0	,	3.5	,	6.5	},	YES	,{"Fert applic. shank low disturbance, 12 in","Harrow, coiled tine",0}}
, {	59	,"Fert. applic. anhyd knife 15 in spacing high disturbance, coil tine har",{	5.0	,	3.5	,	6.5	},	YES	,{"Fert. applic. anhyd knife 15 in spacing high disturbance","Harrow, coiled tine",0}}
, {	60	,"Fert. applic. anhyd knife 15 in spacing, coil tine har"               ,{	5.0	,	3.5	,	6.5	},	YES	,{"Fert. applic. anhyd knife 15 in spacing","Harrow, coiled tine",0}}
, {	61	,"Harrow, rolling"                                                      ,{	4.0	,	3.0	,	10.0	},	YES	,{"Harrow, coiled tine","Rolling basket incorporator",0}}
, {	62	,"Lister, 30 in with fert applic."                                      ,{	4.5	,	3.5	,	5.0	},	YES	,{"Fert applic. shank low disturbance, 15 in spacing","Lister, 30 in",0}}
, {	63	,"Lister, 40 in with fert applic."                                      ,{	4.5	,	3.5	,	5.0	},	YES	,{"Fert applic. shank low disturbance, 15 in spacing","Lister, 40 in",0}}
, {	64	,"Planter, strip till, shallow subsoiler"                               ,{	5.0	,	3.5	,	6.5	},	YES	,{"Subsoiler, in row strip conditioner","Planter, double disk opnr",0}}
, {	65	,"Planter, strip till, subsoiler"                                       ,{	5.0	,	3.5	,	6.5	},	YES	,{"Subsoiler, in row strip conditioner","Planter, double disk opnr",0}}
, {	66	,"Rodweeder, harrow, spike tooth"                                       ,{	5.0	,	4.0	,	6.0	},	YES	,{"Rodweeder","Harrow, spike tooth",0}}
, {	67	,"Seedbed finisher, fld cult, coil tine har, rollng bskt"               ,{	6.0	,	0.0	,	0.0	},	YES	,{"Cultivator, field 6-12 in sweeps","Harrow, coiled tine","Rolling basket incorporator",0}}
, {	68	,"Subsoil disk ripper, coulter smooth, rlng bskt"                       ,{	5.5	,	0.0	,	0.0	},	YES	,{"Coulter caddy, with smooth coulters","Subsoiler","Disk, tandem light finishing","Rolling basket incorporator",0}}
, {	69	,"Subsoil disk ripper, roller smooth"                                   ,{	0.0	,	0.0	,	0.0	},	YES	,{"Disk, tandem secondary op.","Subsoiler","Disk, single gang","Roller, smooth",0}}
, {	70	,"Subsoiler, in row strip conditioner, 40 in row"                       ,{	3.0	,	2.0	,	5.0	},	NO	,{"Subsoiler, in row","Strip till bed conditioner",0}}
, {   71 ,"Subsoiler; Stalk chopper, rolling"                                    ,{4.5,3.0,5.0},false,{"Subsoiler", "Stalk chopper, rolling"}}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
, {	0	,	"",{	5.0	,	3.5	,	6.5	},	YES	,{"","",""}}
};
#endif
//_2013-07-10___________________________field_operation_composition_parameters_/
SDR_Field_operations::SDR_Field_operations()
{
}
//______________________________________________________________________________
nat16 SDR_Field_operations::lookup_operation_number(const char *_description)  const
{  nat16 found = 0;
   const char *SDR_field_op_description;                                         //140515
   for (nat16 i = 1;
      #ifdef USE_NEW_RUSLE2
      field_operation_parameters[i].number_dont_use                           //150309
      #else
      SDR_field_operation_parameters_table[i].number_dont_use                 //150309
      #endif
      ; i++)
   {  SDR_field_op_description =
      #ifdef USE_NEW_RUSLE2
      field_operation_parameters[i].operation_name;                               //140522
      #else
      SDR_field_operation_parameters_table[i].description;
      #endif

      int compare = strcmp(SDR_field_op_description,_description);               //140515
      if (compare == 0)
         return found = i;
   }
   return found;
}
//______________________________________________________________________________
#ifdef USE_NEW_RUSLE2
nat16 SDR_Field_operations::lookup_composite_operation_number(const char *_description)  const
{  nat16 found = 0;
   for (nat16 i = 0; field_operation_composite_parameters[i].number_dont_use /*141215 operation_name*/ ; i++)
   {  if (strcmp(field_operation_composite_parameters[i].operation_name,_description) == 0)
         return found = i;
   }
   return found;
}
#endif
//_2013-07-13_____________________________________________________________________________
const char *SDR_Field_operations::get_description(nat16 op_number) const
{  return
      #ifdef USE_NEW_RUSLE2
      field_operation_parameters[op_number].operation_name;                      //140522
      #else
      SDR_field_operation_parameters_table[op_number].description;
      #endif
}
//______________________________________________________________________________
float32 SDR_Field_operations::get_disturbance_depth_avg_m(nat16 op_number) const
{  return inch_to_m(
          (field_operation_parameters[op_number].depth_inch.min
         + field_operation_parameters[op_number].depth_inch.max)/2.0);
}
//______________________________________________________________________________
float32 SDR_Field_operations::get_roughness_initial_m(nat16 op_number)     const
{  return inch_to_m(field_operation_parameters[op_number].roughness.initial_inch);
}
//______________________________________________________________________________
float32 SDR_Field_operations::get_mixing_fraction(nat16 op_index)       contribution_ //141204 const
{
   Field_operation_parameters &field_op_param = field_operation_parameters[op_index];//141031
   #ifdef USE_NEW_RUSLE2
   Disturbance                &disturbance    = field_op_param.disturbance;      //141031
   if (disturbance.invert==UNKNOWN_invert)                                       //141031
      estimate_disturbance_parameters(field_op_param);                           //141031
   float32 invert = disturbance.invert;
   float32 mix    = disturbance.mix;
   #else
   Disturbance                &disturbance    = SDR_field_operation_parameters_table[op_index].disturbance;      //141031

   float32 invert = disturbance.invert;
   float32 mix    = disturbance.mix;
   #endif
/*141031
   if (field_operation_parameters[op_index].disturbance.invert==UNKNOWN_invert)  //141031
      estimate_disturbance_parameters(field_operation_parameters[op_index]);      //141031
   #ifdef USE_NEW_RUSLE2
   float32 invert = field_operation_parameters[op_index].disturbance.invert;
   float32 mix    = field_operation_parameters[op_index].disturbance.mix;
   #else
   float32 invert = SDR_field_operation_parameters_table[op_index].disturbance.invert;
   float32 mix    = SDR_field_operation_parameters_table[op_index].disturbance.mix;
   #endif

*/
   float32 fraction
      = 0.5 * pow((invert/5.0),1.5)
      + 0.3 * pow((mix   /5.0),1.5);
   return fraction;
}
//______________________________________________________________________________
Soil_disturbance_effect   SDR_Field_operations::get_soil_disturbance_effect(nat16 op_index) const
{  Soil_disturbance_effect effect = field_operation_parameters[op_index].soil_disturbance_effect;
   switch (effect)
   {
      case  LIFTING_FRACTURING  :  // Not currently handled by tillage submodel
      case  COMPRESSION         :  // Not currently handled by tillage submodel
      case  REMOVE_COVER        :  // Not currently handled by tillage submodel (removing plastic cover)
      case  REMOVE_RESIDUE      :  // Not currently handled by tillage submodel Remove residue
      case  ADD_OTHER_EFFECT    :  // Some operations dont disturb
       effect = NEGLIGIBLE_EFFECT;
      break;
      default: /* Other effects are handled */ break;
   }
   return effect;
}
//______________________________________________________________________________
nat8 SDR_Field_operations::get_disturbance_rating(nat16 op_index) contribution_ //141204 const
{
   #ifdef USE_NEW_RUSLE2


   if (  (field_operation_parameters[op_index].disturbance.invert   == UNKNOWN_invert) //141023
      )
   {  estimate_disturbance_parameters(field_operation_parameters[op_index]);      //141023

   }
   return (nat8)
   (
     field_operation_parameters[op_index].disturbance.invert
   + field_operation_parameters[op_index].disturbance.mix
   + field_operation_parameters[op_index].disturbance.lift
   + field_operation_parameters[op_index].disturbance.shatter
   + field_operation_parameters[op_index].disturbance.aerate
   + field_operation_parameters[op_index].disturbance.compact);
   #else
   return
     (nat8)SDR_field_operation_parameters_table[op_index].disturbance.invert
   + (nat8)SDR_field_operation_parameters_table[op_index].disturbance.mix
   + (nat8)SDR_field_operation_parameters_table[op_index].disturbance.lift
   + (nat8)SDR_field_operation_parameters_table[op_index].disturbance.shatter
   + (nat8)SDR_field_operation_parameters_table[op_index].disturbance.aerate
   + (nat8)SDR_field_operation_parameters_table[op_index].disturbance.compact;
   #endif
}
//______________________________________________________________________________
#ifdef USE_NEW_RUSLE2
Disturbance general_disturbance_parameters[COUNT_SD_EFFECT]
=
/*
  invert
  | mix
  | | lift
  | | | shatter
  | | | | aerate
  | | | | | compact
  V V V V V V */
{{0,1,0,0,1,1}  //UNKNOWN_EFFECT       // or No effect
,{5,3,5,5,5,3}  // INVERSION_SOME_MIXING
,{4,4,3,2,4,2}  // MIXING_SOME_INVERSION
,{2,5,3,2,3,0}  // MIXING
,{0,0,0,0,0,1}  // NEGLIGIBLE_EFFECT
,{0,0,5,5,0,0}  // LIFTING_FRACTURING    // Not currently handled by tillage submodel
,{0,0,0,0,0,5}  // COMPRESSION           // Not currently handled by tillage submodel
,{1,2,3,0,0,1}  // REMOVE_COVER          // Not currently handled by tillage submodel (removing plastic cover)
,{1,1,2,1,1,0}  // REMOVE_RESIDUE        // Not currently handled by tillage submodel Remove residue
,{0,0,0,0,0,0}  // ADD_OTHER_EFFECT      // Some operations dont disturb
,{0,0,0,0,3,3}  // COMPRESSION AERATION  // Not currently handled by tillage submodel, COMPRESSION_AERATION

//These values are purely guesses by RLN
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool SDR_Field_operations::estimate_disturbance_parameters
(modifiable_ Field_operation_parameters &field_op_param)
contribution_                                                                    //141204
{
   // This estimation function is completely created by Roger Nelson.
   // It has no basis other than presumed affect based on the general effect
   Disturbance &general_disturb_param = general_disturbance_parameters[field_op_param.soil_disturbance_effect];
   float64 surf_area_distr_fraction =
      (field_op_param.surface_area_distributed > 0.0)
      ? field_op_param.surface_area_distributed/100.0
      : 1.0;
   float64 intensity_fraction = field_op_param.intensity_fraction;
   field_op_param.disturbance.invert = general_disturb_param.invert;
   field_op_param.disturbance.mix    = general_disturb_param.mix;
   field_op_param.disturbance.lift   = general_disturb_param.lift;
   field_op_param.disturbance.shatter= general_disturb_param.shatter;
   field_op_param.disturbance.aerate = general_disturb_param.aerate;
   field_op_param.disturbance.compact= general_disturb_param.compact;

   if (field_op_param.intensity_fraction > 0.00001)
   {
      field_op_param.disturbance.invert *= intensity_fraction;
      field_op_param.disturbance.mix    *= intensity_fraction * surf_area_distr_fraction;
      field_op_param.disturbance.lift   *= intensity_fraction * field_op_param.residue_resurfacing_fraction[1] *10.0;
      field_op_param.disturbance.shatter*= intensity_fraction;
      field_op_param.disturbance.aerate *= intensity_fraction * surf_area_distr_fraction;
      field_op_param.disturbance.compact*= intensity_fraction * field_op_param.residue_flatten_ratio[1];
   }
   // Some of the coefficient from the table may be 0 (NA)
   // In this case, dont adjust the general general_disturb_param
   if (CORN::is_approximately<float32>(field_op_param.disturbance.invert ,0.0,0.00001)) field_op_param.disturbance.invert   = general_disturb_param.invert;
   if (CORN::is_approximately<float32>(field_op_param.disturbance.mix    ,0.0,0.00001)) field_op_param.disturbance.mix      = general_disturb_param.mix;
   if (CORN::is_approximately<float32>(field_op_param.disturbance.lift   ,0.0,0.00001)) field_op_param.disturbance.lift     = general_disturb_param.lift;
   if (CORN::is_approximately<float32>(field_op_param.disturbance.shatter,0.0,0.00001)) field_op_param.disturbance.shatter  = general_disturb_param.shatter;
   if (CORN::is_approximately<float32>(field_op_param.disturbance.aerate ,0.0,0.00001)) field_op_param.disturbance.aerate   = general_disturb_param.aerate;
   if (CORN::is_approximately<float32>(field_op_param.disturbance.compact,0.0,0.00001)) field_op_param.disturbance.compact  = general_disturb_param.compact;

   field_op_param.disturbance.invert   = CORN::must_be_less_or_equal_to<float32>(field_op_param.disturbance.invert   ,5.0);
   field_op_param.disturbance.mix      = CORN::must_be_less_or_equal_to<float32>(field_op_param.disturbance.mix      ,5.0);
   field_op_param.disturbance.lift     = CORN::must_be_less_or_equal_to<float32>(field_op_param.disturbance.lift     ,5.0);
   field_op_param.disturbance.shatter  = CORN::must_be_less_or_equal_to<float32>(field_op_param.disturbance.shatter  ,5.0);
   field_op_param.disturbance.aerate   = CORN::must_be_less_or_equal_to<float32>(field_op_param.disturbance.aerate   ,5.0);
   field_op_param.disturbance.compact  = CORN::must_be_less_or_equal_to<float32>(field_op_param.disturbance.compact  ,5.0);
   return true;
}
//_2014-10-23___________________________________________________________________
#endif
//______________________________________________________________________________

const float32 *SDR_Field_operations::get_residue_flatten_ratio(nat16 number) const
{  return field_operation_parameters[number].residue_flatten_ratio;
}
//______________________________________________________________________________
const   float32 *SDR_Field_operations::get_residue_burial_ratio(nat16 number) const
{  return  field_operation_parameters[number].residue_burial_ratio;
}
//______________________________________________________________________________
#ifdef NYN
Currently we pass the array because the residue type is not known at this point.
until we process each residue
float32 SDR_Field_operations::get_standing_to_flat_residue_fraction(nat16 op_index,RUSLE2_Residue_type residue_type) const
{  if (residue_type == UNKNOWN_RESIDUE_TYPE) residue_type = MODERATE_RESIDUE_TYPE;
   return  field_operation_parameters[op_index].residue_flatten_ratio[residue_type-1];
}
//______________________________________________________________________________
float32 SDR_Field_operations::get_residue_fraction_not_incorporated(nat16 op_index,RUSLE2_Residue_type residue_type) const
{  if (residue_type == UNKNOWN_RESIDUE_TYPE) residue_type = MODERATE_RESIDUE_TYPE;
   return  1.0 - field_operation_parameters[op_index].residue_burial_ratio[residue_type-1];
}
//______________________________________________________________________________
#endif
#ifdef USE_NEW_RUSLE2
const char ** SDR_Field_operations::lookup_composite_operations(const char *NRCS_operation_description) const //130710
{
   uint16 NRCS_SDR_composition_operation_number = 0;                             //130710                                                                                                       //060802
   NRCS_SDR_composition_operation_number = lookup_composite_operation_number(NRCS_operation_description); //060802
   return (NRCS_SDR_composition_operation_number)                                //130710
      ? field_operation_composite_parameters[NRCS_SDR_composition_operation_number].operations
      : 0;
}
//______________________________________________________________________________
char *Soil_disturbance_effect_labels[] =
{ "UNKNOWN_EFFECT"
, "INVERSION_SOME_MIXING"
, "MIXING_SOME_INVERSION"
, "MIXING"
, "NEGLIGIBLE_EFFECT"
, "LIFTING_FRACTURING"
, "COMPRESSION"
, "REMOVE_COVER"
, "REMOVE_RESIDUE"
, "ADD_OTHER_EFFECT"
, "COMPRESSION_AERATION"
, "COUNT_SD_EFFECT"
};

char *source_labels[]=
{ "heuristic/Roger"
, "Armen"
, "Stewart"
, "Roger"
};

nat16 SDR_Field_operations::dump_disturbance_ratings(std::ostream &strm)   const
{  nat16 op;

      strm
         << "number" << '\t'
         << "effect" <<  '\t'
         << "rating" << '\t'
         << "invert"   << '\t'
         << "mix"      << '\t'
         << "lift"     << '\t'
         << "shatter"  << '\t'
         << "aerate"   << '\t'
         << "compact"  << '\t' << std::endl;

   for (int effect = 0; effect <=COMPRESSION; effect++)
   {

      strm
         << "Generalization" << '\t'
         << (int)(general_disturbance_parameters[effect].sum()) << " =" << '\t'
         << general_disturbance_parameters[effect].invert   << '\t'
         << general_disturbance_parameters[effect].mix      << '\t'
         << general_disturbance_parameters[effect].lift     << '\t'
         << general_disturbance_parameters[effect].shatter  << '\t'
         << general_disturbance_parameters[effect].aerate   << '\t'
         << general_disturbance_parameters[effect].compact  << '\t'
         << Soil_disturbance_effect_labels[effect] << '\t'
         << std::endl;

   }
      strm
         << "number" << '\t'
         << "effect" << '\t'
         << "source" << '\t'
         << "rating" << '\t'
         << "invert"   << '\t'
         << "mix"      << '\t'
         << "lift"     << '\t'
         << "shatter"  << '\t'
         << "aerate"   << '\t'
         << "compact"  << '\t'
         << "intensity" << '\t'
         << "surface_disturb"<< '\t'
         << "resurf(residue)*10" << '\t'
         << "flatten(residue)" << '\t'
         << "operation"       << std::endl;

   for ( op = 1; field_operation_parameters[op].number_dont_use != 0; op++)
   {
      nat8 disturbance_rating = (int)get_disturbance_rating(op);
      strm
         << op << '\t'
         << Soil_disturbance_effect_labels[field_operation_parameters[op].soil_disturbance_effect] << '\t'
         << source_labels[field_operation_parameters[op].disturbance.source] << '\t'
         << (int)disturbance_rating << " =" << '\t'
         << field_operation_parameters[op].disturbance.invert   << '\t'
         << field_operation_parameters[op].disturbance.mix      << '\t'
         << field_operation_parameters[op].disturbance.lift     << '\t'
         << field_operation_parameters[op].disturbance.shatter  << '\t'
         << field_operation_parameters[op].disturbance.aerate   << '\t'
         << field_operation_parameters[op].disturbance.compact  << '\t'
         << (field_operation_parameters[op].intensity_fraction)   << '\t'
         << (field_operation_parameters[op].surface_area_distributed/100.0)    << '\t'
         << (field_operation_parameters[op].residue_resurfacing_fraction[1] *10.0)    << '\t'
         << (field_operation_parameters[op].residue_flatten_ratio[1])    << '\t'
         << field_operation_parameters[op].operation_name       << std::endl;
   }

   return op;
}
#endif
//_2013-07-10___________________________________________________________________lookup_composite_operations_/
}}} // namespace USDA { namespace NRCS { namespace RUSLE2 {                             //120406



