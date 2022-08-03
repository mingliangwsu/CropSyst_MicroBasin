#include "crop/growth_stages.h"

// The code in this file is C compilable.
// If programming in C++ include only growth_stages.cpp
// (which #include's this file) in the project or make file.
//______________________________________________________________________________
const char *normal_crop_event_sequence_label_table[]=
{
"none"
,"sowing"
,"germination"
,"emergence"
,"restart"
,"active_growth"
,"end_canopy_growth"                                                             //130429
#if (CS_VERSION > 5)
,"anthesis"
#else
,"flowering"
#endif
,"filling"
,"ripening"
,"reserved_for_future_use_2"
,"maturity"
,"harvestable"
,"harvest"
#if (CS_VERSION != 4)
,"postharvest"
#endif
,"dormant"  // Or inactive
,"terminated"
,0
};
//______________________________________________________________________________
const char *fruit_tree_event_sequence_label_table[]=
{
"none",
"planting"            // when planted from seed or root stock
,"<reserved>"         // germination
,"<reserved>"         // emergence
,"bud_break"
,"active_growth"
,"end_canopy_growth"                                                             //130429
#if (CS_VERSION > 5)
,"anthesis"
#else
,"flowering"
#endif
,"fruit_development"
,"veraison"
,"rapid_fruit_development"
,"maturity"
,"harvestable"
,"harvest"
#if (CS_VERSION != 4)
,"postharvest"
#endif
,"dormant"  // or inactive
,"terminated"
,0
};

#ifdef CROPSYST_VERSION
#include "static_phrases.h"
//______________________________________________________________________________
const char *get_growth_stage_description(Normal_crop_event_sequence /*130903 unsigned long*/ growth_stage,bool is_fruit)
{
   const char *growth_stage_phrase = 0;                                          //040210
   switch (growth_stage)
   { case NGS_NONE  : growth_stage_phrase =TL_Preplanting_Fallow;       break;
     case NGS_GERMINATION     : growth_stage_phrase ="Germination";                  break;//041210
     //case GERMINATION  : growth_stage_phrase ="Germination";             break;//130425
     case NGS_EMERGENCE    : growth_stage_phrase ="Emergence";                 break;//041210
     case NGS_RESTART      : growth_stage_phrase ="Restart";                   break; //170314LML is_fruit ? "Bud break": "Restart";                   break;//041210

     case NGS_ACTIVE_GROWTH: growth_stage_phrase =TL_Active_Growth;            break;
     case NGS_END_CANOPY_GROWTH  : growth_stage_phrase ="End canopy growth";           break;//130429

     case NGS_ANTHESIS    : growth_stage_phrase ="Flowering(anthesis)";                break;
    //NYI case TUBER_INIT  : growth_stage_phrase ="Tuber initiation";      break;
     case NGS_FILLING:growth_stage_phrase=is_fruit ?"Initial fruit growth" : "Yield formation"; break;//130425 was Filling(grain or tuber)
          case FGS_VERAISON     :  growth_stage_phrase =is_fruit ? TL_Veraison : "Ripening";                break;//030521
     case FGS_RAPID_FRUIT_DEVELOPMENT : growth_stage_phrase ="Rapid fruit growth";  break;//030521
     case NGS_MATURITY     : growth_stage_phrase =TL_Maturity;                 break;
     case NGS_HARVESTABLE  : growth_stage_phrase =TL_Harvestable;              break;
     case NGS_DORMANT_or_INACTIVE : growth_stage_phrase ="Dormant or Inactive";break;//080401
     case NGS_HARVEST    : growth_stage_phrase =TL_Harvest;                  break;//030516
     case NGS_TERMINATED   : growth_stage_phrase ="Terminated";                break;//030516
     default  : growth_stage_phrase =TL_Preplanting_Fallow;                break;//041210
          // latest growth stage will initially be 0
   }
   return  growth_stage_phrase;
}
//2011-09-02____________________________________________________________________
#endif
