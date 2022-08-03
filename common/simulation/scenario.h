#ifndef scenarioH
#define scenarioH
#ifndef COMMON_EVENT_H
#  include "common/simulation/event.h"
#endif
#ifndef SIM_PARAMETERS_H
#  include "corn/parameters/parameters_datarec.h"
#endif
#include "corn/OS/directory_entry_name.h"
#include "geodesy/geolocation.h"
#define LABEL_scenario "scenario"
namespace CS {                                                                   //150416
//______________________________________________________________________________
class Common_scenario
: public Common_parameters_data_record                                           //051102 Simulation_parameters
{
 public:
   CORN::date32 start_date_raw; CORN::Date_cowl_32 start_date;                   //170525_110101
   CORN::date32 stop_date_raw;  CORN::Date_cowl_32 stop_date;                    //170525_110101
   Common_event_list parameter_event_list;  // For event parameters
 public:
   Common_scenario();                                                            //180626
      //180626 (nat8  major,nat8  release,nat8  minor);
   virtual ~Common_scenario();
   virtual bool expect_structure(bool for_write = false);                        //161023
   inline virtual const char *get_primary_section_name()                   const { return LABEL_scenario;}
   virtual Common_operation *get_operation                                       //030808
      (const char *operation_type_str
      ,const std::string &operation_ID
      ,modifiable_ CORN::OS::File_name &operation_filename                       //120913
         // the fully qualified operation filename may be returned (to be output to the schedule)
      ,int32 resource_set_ID,bool &relinquish_op_to_event) = 0;
    // Derived classes (I.e. CANMS) may store operation parameters in separate files.
};
//_2003-02-03___________________________________________________________________
} // namespace CS
#endif
// common/scenario.h

