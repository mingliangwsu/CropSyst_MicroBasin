#include "crop/crop_element.h"
#include "CS_suite/observation/CS_examination.h"
#include "crop/growth_stages.hpp"
namespace CropSyst {
//______________________________________________________________________________
Crop_element::Crop_element
(const CORN::date32                    &today_)
: CS::Simulation_element_composite     (today_)
, emanator_known(0)                                                              //160613
{}
//_2017-12-12___________________________________________________________________
bool Crop_element::start_period(nat8 phenologic_stage)             modification_
{  bool started = true;
   if (emanator_known)
   {  CS::Examination &examination = CS::get_examination_global();               //171115
      CS::Period *crop_season = new CS::Period                                   //171115
         (today,phenologic_stage
         ,phenologic_stage==0 ? "seasonal"
          : normal_crop_event_sequence_label_table[phenologic_stage]
         ,*emanator_known);                                                      //171116
      examination.periods.append(crop_season);                                   //171115
      started &= examination                                                     //171115_161202
         .add_period_inspection
         (*crop_season                                                           //171115
         ,UT_day
         ,*emanator_known
         ,STAT_BASIC_ELEMENTS_INIT_FINAL_bits);
   }
   return started;
}
//_2016-06-13___________________________________________________________________
bool Crop_element::end_period(nat8 period)                          modification_
{  bool ended = true;
   if (emanator_known)
      ended &= CS::get_examination_global()                                      //171114_161202
         .complete_period_inspection(period,*emanator_known,true);               //171222

         // Warning checking if end_period is occuring before daily inspection commit.

   return ended;
}
//_2016-06-13___________________________________________________________________
} // namespace CropSyst


