#include "CS_suite/simulation/CS_simulation_control.h"
#include "corn/math/statistical/statistics_types.hpp"
//______________________________________________________________________________
DECLARE_CONTAINER_ENUMERATED_SECTION(Common_event,comment_event_section_VV,true);
//NYI not sure if Common_event goes in CS namespace
namespace CS {
//______________________________________________________________________________
bool Simulation_control::expect_structure(bool for_write)
{  bool expected = Common_parameters_data_record::expect_structure(for_write);   //11023
   structure_defined = false;                                                    //120314
   EXPECT_ENUMERATED_SECTION("event",comment_event_section_VV,control_event_list);//131020
   set_current_section("simulation");
      expect_int32("start_date",start_date_raw);                                 //170628_170525_110101
      expect_int32("stop_date" ,stop_date_raw);                                  //170628_170525_110101
      #if (CS_VERSION <= 5)
      // In version 4 it used to be called starting_date and ending_date
      // we will continue to recognize in version 5
      if (!for_write)
      {
         expect_int32("starting_date",start_date_raw);                           //170628_170525_110101
         expect_int32("ending_date" ,stop_date_raw);                             //170628_170525_110101
      }
      #endif
      expect_bool("rotation_cycling",rotation_cycling);                          //160219_151008
      expect_nat32("inspection",inspection_levels,2);                            //150919
   structure_defined = true;                                                     //120314
   return expected;                                                              //161023
}
//______________________________________________________________________________
Simulation_control::Simulation_control
(
//180626 nownat8  _major using date ,nat8  _release,nat8  _minor
)
: Common_parameters_data_record(OPTIONAL_ASSOCIATED_DIRECTORY,"section",CS_VERSION) //180626
//180626 now using date _major, _release, _minor

,ID(0)
,start_date_raw(0)
,stop_date_raw(0)
,start_date    (start_date_raw)                                                  //170525
,stop_date     (stop_date_raw)                                                   //170525
,control_event_list()
,rotation_cycling(false)                                                         //151008
,inspection_levels(0)                                                            //151013
,UED_recording(true)
{
   start_date.set_now();                                                         //180102
   stop_date.set_now();                                                          //180102
}
//______________________________________________________________________________
Simulation_control::~Simulation_control()
{  control_event_list.delete_all(); }
//______________________________________________________________________________
} // namespace CS
// Simulation_control.cpp

