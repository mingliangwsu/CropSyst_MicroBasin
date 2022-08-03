#include "soil/SCS/SCS.h"
#ifndef primitiveH
#  include "corn/primitive.h"
#endif

#define LABEL_STRAIGHT              "STRAIGHT"
#define LABEL_CONTOUR               "CONTOUR"
#define LABEL_TERRACE               "TERRACE"

#define DONT_KNOW 0
using namespace USDA_NRCS;                                                       //110216
//______________________________________________________________________________
classify condition_classifications[MAX_classifications+1] =
   {{FALLOW     ,NO_TREATMENT       ,POOR   ,A,{0 ,0 ,0 }}, // <- Spacer
    {FALLOW,STRAIGHT,POOR,A,{59,77,89}},
    {FALLOW,STRAIGHT,POOR,B,{72,86,94}},
    {FALLOW,STRAIGHT,POOR,C,{80,91,97}},
    {FALLOW,STRAIGHT,POOR,D,{85,94,98}},
    {ROW_CROPS,STRAIGHT,POOR,A,{53,72,86}},
    {ROW_CROPS,STRAIGHT,POOR,B,{64,81,92}},
    {ROW_CROPS,STRAIGHT,POOR,C,{75,88,95}},
    {ROW_CROPS,STRAIGHT,POOR,D,{80,91,97}},
    {ROW_CROPS,STRAIGHT,GOOD,A,{47,67,83}},
    {ROW_CROPS,STRAIGHT,GOOD,B,{60,78,90}},
    {ROW_CROPS,STRAIGHT,GOOD,C,{70,85,94}},
    {ROW_CROPS,STRAIGHT,GOOD,D,{76,89,96}},
    {ROW_CROPS,CONTOUR,POOR,A,{51,70,85}},
    {ROW_CROPS,CONTOUR,POOR,B,{62,79,91}},
    {ROW_CROPS,CONTOUR,POOR,C,{68,84,93}},
    {ROW_CROPS,CONTOUR,POOR,D,{75,88,95}},
    {ROW_CROPS,CONTOUR,GOOD,A,{45,65,82}},
    {ROW_CROPS,CONTOUR,GOOD,B,{57,75,88}},
    {ROW_CROPS,CONTOUR,GOOD,C,{66,82,92}},
    {ROW_CROPS,CONTOUR,GOOD,D,{72,86,94}},
    {ROW_CROPS,TERRACE,POOR,A,{46,66,82}},
    {ROW_CROPS,TERRACE,POOR,B,{55,74,88}},
    {ROW_CROPS,TERRACE,POOR,C,{63,80,91}},
    {ROW_CROPS,TERRACE,POOR,D,{66,82,92}},
    {ROW_CROPS,TERRACE,GOOD,A,{42,62,79}},
    {ROW_CROPS,TERRACE,GOOD,B,{52,71,86}},
    {ROW_CROPS,TERRACE,GOOD,C,{60,78,90}},
    {ROW_CROPS,TERRACE,GOOD,D,{64,81,92}},
    {SMALL_GRAIN,STRAIGHT,POOR,A,{45,65,82}},
    {SMALL_GRAIN,STRAIGHT,POOR,B,{58,76,89}},
    {SMALL_GRAIN,STRAIGHT,POOR,C,{70,84,93}},
    {SMALL_GRAIN,STRAIGHT,POOR,D,{75,88,95}},
    {SMALL_GRAIN,STRAIGHT,GOOD,A,{43,63,80}},
    {SMALL_GRAIN,STRAIGHT,GOOD,B,{57,75,88}},
    {SMALL_GRAIN,STRAIGHT,GOOD,C,{67,83,93}},
    {SMALL_GRAIN,STRAIGHT,GOOD,D,{73,87,95}},
    {SMALL_GRAIN,CONTOUR,POOR,A,{43,63,80}},
    {SMALL_GRAIN,CONTOUR,POOR,B,{55,74,88}},
    {SMALL_GRAIN,CONTOUR,POOR,C,{66,82,92}},
    {SMALL_GRAIN,CONTOUR,POOR,D,{70,85,94}},
    {SMALL_GRAIN,CONTOUR,GOOD,A,{41,61,78}},
    {SMALL_GRAIN,CONTOUR,GOOD,B,{54,73,87}},
    {SMALL_GRAIN,CONTOUR,GOOD,C,{64,81,92}},
    {SMALL_GRAIN,CONTOUR,GOOD,D,{68,84,93}},
    {SMALL_GRAIN,TERRACE,POOR,A,{41,61,78}},
    {SMALL_GRAIN,TERRACE,POOR,B,{53,72,86}},
    {SMALL_GRAIN,TERRACE,POOR,C,{62,79,91}},
    {SMALL_GRAIN,TERRACE,POOR,D,{66,82,92}},
    {SMALL_GRAIN,TERRACE,GOOD,A,{39,59,77}},
    {SMALL_GRAIN,TERRACE,GOOD,B,{51,70,85}},
    {SMALL_GRAIN,TERRACE,GOOD,C,{60,78,90}},
    {SMALL_GRAIN,TERRACE,GOOD,D,{64,81,92}},
    {CLOSE_SEED_LEGUMES,STRAIGHT,POOR,A,{46,66,82}},
    {CLOSE_SEED_LEGUMES,STRAIGHT,POOR,B,{59,77,89}},
    {CLOSE_SEED_LEGUMES,STRAIGHT,POOR,C,{70,85,94}},
    {CLOSE_SEED_LEGUMES,STRAIGHT,POOR,D,{76,89,96}},
    {CLOSE_SEED_LEGUMES,STRAIGHT,GOOD,A,{38,58,76}},
    {CLOSE_SEED_LEGUMES,STRAIGHT,GOOD,B,{53,72,86}},
    {CLOSE_SEED_LEGUMES,STRAIGHT,GOOD,C,{64,81,92}},
    {CLOSE_SEED_LEGUMES,STRAIGHT,GOOD,D,{70,85,94}},
    {CLOSE_SEED_LEGUMES,CONTOUR,POOR,A,{44,64,81}},
    {CLOSE_SEED_LEGUMES,CONTOUR,POOR,B,{59,75,88}},
    {CLOSE_SEED_LEGUMES,CONTOUR,POOR,C,{67,83,93}},
    {CLOSE_SEED_LEGUMES,CONTOUR,POOR,D,{70,85,94}},
    {CLOSE_SEED_LEGUMES,CONTOUR,GOOD,A,{35,55,74}},
    {CLOSE_SEED_LEGUMES,CONTOUR,GOOD,B,{50,69,84}},
    {CLOSE_SEED_LEGUMES,CONTOUR,GOOD,C,{60,78,90}},
    {CLOSE_SEED_LEGUMES,CONTOUR,GOOD,D,{67,83,93}},
    {CLOSE_SEED_LEGUMES,TERRACE,POOR,A,{43,63,80}},
    {CLOSE_SEED_LEGUMES,TERRACE,POOR,B,{54,73,87}},
    {CLOSE_SEED_LEGUMES,TERRACE,POOR,C,{63,80,91}},
    {CLOSE_SEED_LEGUMES,TERRACE,POOR,D,{67,83,93}},
    {CLOSE_SEED_LEGUMES,TERRACE,GOOD,A,{31,51,70}},
    {CLOSE_SEED_LEGUMES,TERRACE,GOOD,B,{47,67,83}},
    {CLOSE_SEED_LEGUMES,TERRACE,GOOD,C,{58,76,89}},
    {CLOSE_SEED_LEGUMES,TERRACE,GOOD,D,{63,80,91}},
    {PASTURE,NATURAL,POOR,A,{48,68,84}},
    {PASTURE,NATURAL,POOR,B,{62,79,91}},
    {PASTURE,NATURAL,POOR,C,{48,86,94}},
    {PASTURE,NATURAL,POOR,D,{76,89,96}},
    {PASTURE,NATURAL,FAIR,A,{30,49,69}},
    {PASTURE,NATURAL,FAIR,B,{50,69,84}},
    {PASTURE,NATURAL,FAIR,C,{62,79,91}},
    {PASTURE,NATURAL,FAIR,D,{68,84,93}},
    {PASTURE,NATURAL,GOOD,A,{21,39,59}},
    {PASTURE,NATURAL,GOOD,B,{41,61,78}},
    {PASTURE,NATURAL,GOOD,C,{55,74,88}},
    {PASTURE,NATURAL,GOOD,D,{63,80,91}},
    {PASTURE,CONTOUR,POOR,A,{28,47,67}},
    {PASTURE,CONTOUR,POOR,B,{47,67,83}},
    {PASTURE,CONTOUR,POOR,C,{64,81,92}},
    {PASTURE,CONTOUR,POOR,D,{75,88,95}},
    {PASTURE,CONTOUR,FAIR,A,{12,25,43}},
    {PASTURE,CONTOUR,FAIR,B,{39,59,77}},
    {PASTURE,CONTOUR,FAIR,C,{57,75,88}},
    {PASTURE,CONTOUR,FAIR,D,{67,83,93}},
    {PASTURE,CONTOUR,GOOD,A,{ 2, 6,15}},
    {PASTURE,CONTOUR,GOOD,B,{18,35,55}},
    {PASTURE,CONTOUR,GOOD,C,{51,70,85}},
    {PASTURE,CONTOUR,GOOD,D,{62,79,91}},
    //970731 Added missing meadow woods farmsteads and roads
    {MEADOW,NATURAL,GENERAL,A,{DONT_KNOW,30,DONT_KNOW}},
    {MEADOW,NATURAL,GENERAL,B,{DONT_KNOW,58,DONT_KNOW}},
    {MEADOW,NATURAL,GENERAL,C,{DONT_KNOW,71,DONT_KNOW}},
    {MEADOW,NATURAL,GENERAL,D,{DONT_KNOW,78,DONT_KNOW}},
    {FOREST,NATURAL,POOR,A,{DONT_KNOW,45,DONT_KNOW}},
    {FOREST,NATURAL,POOR,B,{DONT_KNOW,66,DONT_KNOW}},
    {FOREST,NATURAL,POOR,C,{DONT_KNOW,77,DONT_KNOW}},
    {FOREST,NATURAL,POOR,D,{DONT_KNOW,83,DONT_KNOW}},
    {FOREST,NATURAL,FAIR,A,{DONT_KNOW,36,DONT_KNOW}},
    {FOREST,NATURAL,FAIR,B,{DONT_KNOW,60,DONT_KNOW}},
    {FOREST,NATURAL,FAIR,C,{DONT_KNOW,73,DONT_KNOW}},
    {FOREST,NATURAL,FAIR,D,{DONT_KNOW,79,DONT_KNOW}},
    {FOREST,NATURAL,GOOD,A,{DONT_KNOW,25,DONT_KNOW}},
    {FOREST,NATURAL,GOOD,B,{DONT_KNOW,55,DONT_KNOW}},
    {FOREST,NATURAL,GOOD,C,{DONT_KNOW,70,DONT_KNOW}},
    {FOREST,NATURAL,GOOD,D,{DONT_KNOW,77,DONT_KNOW}},
#ifndef SPAW
    {FARMSTEAD,NATURAL,GENERAL,A,{DONT_KNOW,59,DONT_KNOW}},
    {FARMSTEAD,NATURAL,GENERAL,B,{DONT_KNOW,74,DONT_KNOW}},
    {FARMSTEAD,NATURAL,GENERAL,C,{DONT_KNOW,82,DONT_KNOW}},
    {FARMSTEAD,NATURAL,GENERAL,D,{DONT_KNOW,86,DONT_KNOW}},
    {DIRT_ROAD,NATURAL,GENERAL,A,{DONT_KNOW,72,DONT_KNOW}},
    {DIRT_ROAD,NATURAL,GENERAL,B,{DONT_KNOW,82,DONT_KNOW}},
    {DIRT_ROAD,NATURAL,GENERAL,C,{DONT_KNOW,87,DONT_KNOW}},
    {DIRT_ROAD,NATURAL,GENERAL,D,{DONT_KNOW,89,DONT_KNOW}},
    {PAVED_ROAD,NATURAL,GENERAL,A,{DONT_KNOW,74,DONT_KNOW}},
    {PAVED_ROAD,NATURAL,GENERAL,B,{DONT_KNOW,84,DONT_KNOW}},
    {PAVED_ROAD,NATURAL,GENERAL,C,{DONT_KNOW,90,DONT_KNOW}},
    {PAVED_ROAD,NATURAL,GENERAL,D,{DONT_KNOW,92,DONT_KNOW}},
#endif
};
//1997-07-31___________________________________________________________________'
const char *land_treatment_label_table[] =
{"NO_TREATMENT"
,LABEL_STRAIGHT
,LABEL_CONTOUR
,LABEL_TERRACE
,0};
//1997-07-31___________________________________________________________________'
const char *land_use_label_table[] =
{"FALLOW"
,"ROW_CROPS"
,"SMALL_GRAIN"
,"CLOSE_SEED_LEGUMES"
,"PASTURE"
,"MEADOW"
,"FOREST"
,"FARMSTEAD"
,"DIRT_ROAD"
,"PAVED_ROAD"
,0};
//1997-07-31___________________________________________________________________'
const char *hydrologic_condition_label_table[] =
{"POOR"
,"FAIR"
,"GOOD"
,0};
//1997-07-31___________________________________________________________________'
#ifdef MOVED
110216 to USDA/NRSC/soil/survey/domains.cpp
const char *hydrologic_group_label_table[] =
{"A"    //Low runoff potential.
,"B"    //Moderately low runoff potential.
,"C"    //Moderately high runoff potential.
,"D"    //High runoff potential.
 // Special cases (converted to A B C in CropSyst)
,"A/D"  //Low runoff potential when drained and high runoff potential undrained.  //000113
,"B/D"  //Moderately low runoff potential when drained and high runoff potential undrained. //000113
,"C/D"  //Moderately high runoff potential when drained and high runoff potential undrained //000113
,0
};
#endif
//1997-07-31___________________________________________________________________'
uint8 lookup_entry
(Land_use              land_use
,Land_treatment        treatment
,Hydrologic_condition  hydro_cond
,Hydrologic_group      hydro_group
)
{
   // Not all conditions in the table have a FAIR entry.
   // If FAIR is requested then GOOD will be returned.
   uint8 good_index     = 0;
   uint8 contour_index  = 0;
   uint8 target_index   = 0;
   uint8 index          = 1;
   bool done = false;
   if (land_use == FALLOW)
   { // 960311c Fallow entries are only available for STRAIGHT row and condition POOR }
     treatment  = STRAIGHT;   // This is a local change only
     hydro_cond = POOR;       // This is a local change only
   };
   while (!done)
   {  if ((land_use      == condition_classifications[index].land_use) &&
          (hydro_group   == condition_classifications[index].hydro_group))
      {  if ((treatment  == condition_classifications[index].land_treatment) &&
             (hydro_cond == condition_classifications[index].hydro_condition))
         {  // We have found the exact entry and we can stop
            target_index = index;
            done = true;
         }
         else // perhaps there is not the exact entry, let's remember a similar entry
         {
            if (treatment == CONTOUR)
               contour_index = index;
            if (hydro_cond == GOOD)
               good_index = index;
         }
      }
      index ++;
      if (index > 100) done = true;
   }
   return (target_index > 0)  ? target_index
        : (good_index > 0)    ? good_index
        : (contour_index > 0) ? contour_index
                              :  100; //  Entry 100 is about average
}
//1997-07-31___________________________________________________________________'
float64 SCS_lookup_curve_number
(Land_use              land_use
,Land_treatment        treatment
,Hydrologic_condition  hydro_cond
,Hydrologic_group      hydro_group
,uint8                 antecedent_moisture_content)
{  uint8 index = lookup_entry(land_use,treatment,hydro_cond,hydro_group);
   return condition_classifications[index].cn[antecedent_moisture_content];
}
//1997-07-31___________________________________________________________________'
