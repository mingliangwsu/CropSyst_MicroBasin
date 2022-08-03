#ifndef CS_simulation_unitH
#define CS_simulation_unitH
#ifndef simulation_elementH
#  include "CS_suite/simulation/CS_simulation_element.h"
#endif
#ifndef parameters_datarecH
#  include "corn/parameters/parameters_datarec.h"
#endif
#ifndef event_schedulerH
#  include "CS_suite/simulation/CS_event_scheduler.h"
#endif
#ifndef CS_simulation_controlH
#  include "CS_suite/simulation/CS_simulation_control.h"
#endif

#  include "corn/OS/directory_entry_name.h"
#ifndef BALANCER_H
#  include "common/simulation/balancer.h"
#endif
#define LABEL_scenario "scenario"
#include "common/simulation/log.h"
namespace CS {
//______________________________________________________________________________
class Simulation_unit
: public extends_ Simulation_element_composite
{
// Each simulation unit can have its own start and stop date
// the Simulation engine will only process units
// when the current date falls in between the start date and stop date
 public:
   CORN::Unidirectional_list performable_operations;
      // These are operations that have been scheduled for today.
      // They are shared will all simulation_elements
      // which will contribute to this list of operations.
      // Derived class(s) which perform operations should scan this
      // list (during process_day) and perform operations they are responsible
      // and set the event status for operations that were performed.
 protected:
   modifiable_ Simulation_control &simulation_control;                           //140714
 protected:
   std::ofstream         *balance_file_daily;                                    //090409
   std::ofstream         *balance_file_annual;                                   //090409
   Unidirectional_list  &balancers;  // List of Balancer                         //070227
   /**<\fn This is a list of balancers simulation components may
   relinquish their accumulation responsability to the master simulation to
   optimally perform accumulations, this ensures the accumulation
   is performed after all daily processing settles.
   For CropSyst, season accumulation is performed by the Land_unit_simulation.
   Because Simulation_engine does not have the concept of season.
   Although Cropping_system_simulation has the concept of season
   each LBU will have its own season (since it has its own rotation).
   Balancers are owned by this Simulation_engine list and will
   be deleted when the simulation ends.
   simulation elements may keep pointers (or references) to the balancers
   they create and/or use but must not delete them.
   **/

   Common_simulation_log *CS_event_log;                                          //160713
   nat32 event_count;                                                            //160713
      // The log should be temporary until I have explainations 160713
 public:
   Simulation_unit
      (modifiable_ Simulation_control  &simulation_control
      ,const CORN::date32              &today);
   virtual ~Simulation_unit();
   virtual const OS::Directory_name &get_output_directory_name()        const=0;
   /**<\fn The default output directory is the current working directory.
      However, typically (as in CropSyst), there should be a directory specifically for output,
      so this method should be overloaded.
   **/
 public: // Simulation_element overrides
   virtual bool initialize()                                    initialization_;
      // provides default event scheduler if not already provided
   virtual bool start()                                           modification_;
   /** This specialization would open the optional balances files (NYI.
   **/
   virtual bool process_day()                                     modification_; //150611RLN
   virtual bool end_day()                                         modification_;
   /**<\fn This is called each day after process_day().
      Derived classes can use this to setup for the current day.
      Normally clearing daily state and or accumlators.
   **/
   virtual bool end_year()                                        modification_;
 public: // Introduced methods
   inline virtual Event_status_indicator perform_operation
      (Common_operation &op)                modification_ { return ES_COMPLETE;}
   inline virtual Event_status_indicator terminate_operation
      (Common_operation &op)                modification_ { return ES_COMPLETE;}
 public:
   nat32 take_balancer(Simulation::Balancer *balancer);                          //070227
   /**<\fn This gives the balancer to the simulation to maintain accumulators.
      Balancers are optional.
      \return handle of balance.                                                  070227
   **/
};
//_2003-02-03___________________________________________________________________
} // namespace CS
#endif
