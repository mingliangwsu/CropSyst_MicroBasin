
#ifndef CS_event_schedulerH
#define CS_event_schedulerH

#include "CS_suite/simulation/CS_simulation_element.h"
#ifndef event_statusH
#  include "common/simulation/event_status.h"
#endif
#ifndef eventH
#  include "common/simulation/event.h"
#endif
#if (CROPSYST_VERSION==4)
#include "crop/crop_param_V4.h"
// For Crop parameter adjustments, version 5 will have adjustable parameters
#else
#include "corn/container/enumlist.h"
#endif

#ifndef balancerH
#  include "common/simulation/balancer.h"
#endif
#include <assert.h>
//______________________________________________________________________________
class Common_simulation_log;

// simulation_today is global.
// It is used for debugging and quick and dirty output with out having to pass the date around

#define NO_NEED_TO_LOG 0
// This define can be used when performing operations when it is not necessary to log the event or event parameters/results

namespace CS {
//______________________________________________________________________________
interface_ Event_scheduler
//: public extends_interface_ Simulation_element
{
 public:
   inline virtual ~Event_scheduler() {}                                          //151204
   virtual nat16  synchronize
      (const Synchronization  &sync
      ,const CORN::Date_const &date_to_synchronize_to)          modification_=0;
      // we can optionally syncronized only if the associated object matches
   virtual nat32 take_events(modifiable_ CORN::Container &events) modification_=0;
   virtual bool is_aborted()                      affirmation_ { return false; }
   virtual bool is_viable()                       affirmation_ { return true;  }
   virtual bool start()                           modification_ { return true; }
   virtual bool start_year()                      modification_ { return true; }
   virtual bool start_day()                       modification_ { return true; }
   virtual bool process_day()                     modification_ { return true; } //151016
   virtual bool end_day()                         modification_ { return true; } //151016
   virtual bool end_year()                        modification_ { return true; } //151016
   virtual bool stop()                            modification_=0;
};
//_2015-10-10________________________________________interface_Event_scheduler_/
class Event_scheduler_common
: public implements_ Event_scheduler
//, public extends_ Simulation_element //_composite
{
 public:
   class Performable_operation
   : public implements_ Item
   {public:
      Common_event &operation_event;
         // performers need to set the event status and the owner of the event
         // will later need to call aftermath.
      Event_status_indicator event_status;
         //users of this object may reset event_status
      nat32 owner_ID;
      bool  terminate;                                                           //170310
    public:
      inline Performable_operation
         (Common_event &operation_event_
         //,Event_status_indicator event_status_
         ,nat32 owner_ID_
         ,bool  terminate_)                                                      //170310
         : Item()
         , operation_event (operation_event_)
         , event_status    ((Event_status_indicator)event_status_pending)
         , owner_ID        (owner_ID_)
         , terminate       (terminate_)                                          //170310
         {}
   };
   //_2015-01-03_______________________________________class Perform_operation_/
 protected:
   const CORN::Date_const &today_scheduled;
 public:
 protected:
   Common_event_list queueA;
   Common_event_list queueB;
   /**<\fn As we identify pending events they are swapped from one queue to the
      other for the next day (this improves performance because removes
      the need to copy pending event queue).
   **/
   Common_event_list completed_events;
   /**<\fn This is a list of events that have been completed.
      Events are completed when the actual date has been assigned (syncronized)
      and the date has passed.
      For event periods the events will be moved to this list when
      the end date has been assigned and passed,
      or the repetitions count is 0.
      We no longer use them, these events are no longer used,
      but there may still be object that continue to reference
      the operation parameters from these events so we can't delete
      any event until the simulation ends.
   **/
   Common_event_list *active_queue; // points to the active queue (A or B)
   // This references the scenerio event list for easy access.
   Common_event_list  *pending_events; // points to the inactive queue (A or B)

   Common_event_list events_for_next_season;
   /**< This is a list of completed events that are to be rescheduled at the start
   of the next season.
   See the related functions reschedule_growing_season_events(crop) and clear_growing_season_events(crop)
   **/
 protected:
   CORN::Unidirectional_list &performable_operations;
      // Owned by simulation engine
 protected:
   bool  aborted;    // if set true, some condition (management could not be applied contigency)
   bool  viable;     // if set false, this indicates a management could not be applied and specified a not viable contigency.
 public:
   Event_scheduler_common
      (const CORN::Date_const    &today
      ,CORN::Unidirectional_list &performable_operations);                       //151003
   virtual ~Event_scheduler_common();
 public: // Event_scheduler implementations
   virtual bool start()                           modification_ { return true; }
   virtual bool start_year()                      modification_ { return true; }
   virtual bool start_day()                                       modification_;
   virtual bool end_day()                                         modification_; //151004
   virtual bool stop()                            modification_ { return true; }
 public:
   virtual nat32 take_events(modifiable_ CORN::Container &events) modification_;
   virtual nat16  synchronize
      (const Synchronization &sync
      ,const CORN::Date_const &date_to_synchronize_to)            modification_;
   /**<\fn This function scans the scenario events list for
      matching syncronizations.
      It creates new actual date events based on the date to syncronize to.
      The actual events operation pointer currently is normally
      set to the potential event, because syncronization may
      produce multiple actual events based on the potential
      event definition, we dont delete or convert potential
      events to actual events, we do move the potential events
      to the synced_pot_events so we can optimize the matching
      process not having to scan for events that have already
      been syncronized and probably already processed.
      \return the number of events added to the act_events
      list for the syncronization.
   **/
   bool aftermath
      (Common_event           &operation_event
      ,Event_status_indicator &event_status)                      modification_; //151003
   inline virtual bool is_aborted()                                affirmation_  //150930
      { return aborted; }
   inline virtual bool is_viable()                                 affirmation_  //150930
      { return viable; }
protected: // The following methods may be be overridden by derived classes.
   inline virtual bool end_operation_period
      (Common_operation &op
      , const CORN::Date_const &date_period_ends)  modification_{ return true; }
   /**<\fn This is used to indicate the end of an event period.
      Derived classes may use this method to perform any additional processing to
      discontinue the operation, or as an opportunity to perform the operation "one more time".
      Normally this function should return true since it is intended as a single to the simulation
      that the event is to be disabled, but the derived object may elect to return false
      to 'postpone' the disable.  The simulation will continue to call the end_operation_period
      every time step until this function returns true
   **/
   inline virtual Event_status_indicator process_model_specific_event            //130428
      (const Simple_event *event)
      { return ES_COMPLETE; }                                                    //150627
 protected:
   virtual bool log_contingency(Contingency contingency)           modification_;
   /**<\fn Record to the log file the contingency
   **/
};
//________________________________________________class Event_scheduler_common_/
class Event_scheduler_simulation_unit
: public extends_ Event_scheduler_common
// Event scheduler intended for simulation unit.
// In V5 the crop has its own event scheduler
// Features events pending for future years store in separate in lists
// to reduce unecessary traversal of event queue.
{protected:
   const CORN::Date_const &ref_start_date;  // These are references the dates stored in the user parameter
   const CORN::Date_const &ref_stop_date;                                        //101221
   CORN::Enumeration_list  year_event_lists;                                     //151203_151004
 public:
   Event_scheduler_simulation_unit
      (const CORN::Date_const &today
      ,const CORN::Date_const &start_date                                        //101221
      ,const CORN::Date_const &end_date                                          //101221
      ,CORN::Unidirectional_list    &performable_operations);
   virtual ~Event_scheduler_simulation_unit();                                   //090409
 public:
   virtual bool start()                                           modification_;
   /**<\fn This function can be overridden to do any special
      setup at the start of the simulation.
      This will be called one time at the beginning of run().
      \return true if start was ok (and run loop can begin).
      I.e. CropSyst Start recording to output file.
   **/
   virtual bool start_year()                                      modification_; //151004
   /**<\fn transfers events pending the corresponding year to the
      current event queue
   **/
   virtual bool stop()                                            modification_;
   /**<\fn Overridden to do any special setup at the end of the simulation.
      This will be called one time at the end of run()
      but only if start was true and run loop was started.
      It will be called even if
      I.e. CropSyst Stop recording to output file
   **/
 public: // The following are for working with event lists
   nat16  reschedule_growing_season_events(void *object);
   /**<\fn The object is usually a crop
      When a crop restarts after dormancy, call this function specifying the related crop.
      The synchronizations will be clear
   **/
   nat16 clear_growing_season_events(void *object)                modification_;
   /**<\fn The object is usually a crop
      When a crop is terminated, call this function specifying the related crop.
      This calls remove_events_associated_with
      and also clears events_for_next_season
      Note we dont simply clear the list, because their may be
      multiple event (I.e. CANMS or intercropping etc.)
   **/
   nat16 disassociate_events(void *object,nat16  operation_type_code);
   inline virtual Common_operation *get_operation
      (const char                   *operation_type_str
      ,const std::string            &operation_ID  // filename may be updated with qualification so not const
      ,modifiable_ CORN::OS::File_name   &operation_filename    // the fully qualified operation filename may be returned (to be output to the schedule)
      ,int32       resource_set_ID,  bool &relinquish_op_to_event)
      { return 0; }                                                              //150629
   /**<\fn Derived classes must override
      operations may be stored/located by operation ID and/or filename
   **/
   nat32 take_balancer(Simulation::Balancer *balancer);                         //070227
   /**<\fn This gives the balancer to the simulation to maintain accumulators.
      Balancers are optional.
      \return handle of balance.                                                  070227
   **/
 protected: // The following methods must be overridden by derived classes.
   inline virtual Event_status_indicator perform_operation
      (Common_operation &op
      ,const void *associated_with_obj)                            modification_
      { return ES_COMPLETE; }                                                    //150627
   /**<\fn The derived class should determine the operation type and route the operation
      to the appropriate objects for processing.
      Events may be associated with a particular object
      the associated object may be used to route an operation
      \return true if the operation could be performed
   **/

protected: // The following methods may be be overridden by derived classes.
   inline nat32 get_ID()                                                   const
      { return (nat32)
         #if (__LP64__ || _M_X64)
         (int64_t)                                                               //120511
         #endif
         this;}
};
//_2015__________________________________class Event_scheduler_simulation_unit_/
} // namespace CS
#endif
//CS_event_scheduler.h
