#ifndef CS_simulation_elementH
#define CS_simulation_elementH
#include "corn/container/unilist.h"
#include "corn/chronometry/date_types.hpp"
#include "corn/chronometry/date_32.h"
#include "CS_suite/observation/CS_observation.h"
//______________________________________________________________________________
#define NO_SPECIFIC_STATISTIC CORN::value_statistic
//______________________________________________________________________________
namespace CS
{
class Simulation_control;
class Event_scheduler;
//______________________________________________________________________________
interface_ Simulation_element
: public implements_ CORN::Item  // This probably should be extends_interface_
{
   Simulation_element();
   inline virtual ~Simulation_element() {}                                       //151204
   virtual bool is_valid()                                       affirmation_=0; //150925
   virtual bool initialize()                                  initialization_=0; //150429
   virtual bool start()                                         modification_=0;
   /**<\fn This function can be overridden to do any special
      setup at the start of the simulation.
      This will be called one time usually at the beginning of run()
      or soon after the simulation_element is instanciated
      during the course of the simulation run.
      \return true if start was ok (and run loop can begin).
      I.e. CropSyst Start recording to output file.
   **/
   virtual bool start_year()                                    modification_=0;
   /**<\fn This is called at the beginning of the first day of the year before process_day()
      Derived classes may override this method to perform special processing
      (such as annual accumulator setup)
      \return true if successful
   **/
   virtual bool start_day()                                     modification_=0;
   /**<\fn This is called each day before process_day().
      Derived classes can use this to setup for the current day.
      Normally clearing daily state and or accumlators.
   **/
   virtual bool process_day()                                   modification_=0;
   /**<\fn This the call done by the daily loop.
      It will check for any events that can be processed on this day.
      This method is often overridden for any special processing
      that is specific to the model.
      If overridden the Simulation_engine::process_day() method should
      be called first so the events get processed.
      Returns false if the process cause substantial errors
      or the simulation should be terminated.
   **/
   virtual bool end_day()                                       modification_=0;
   /**<\fn This is called each day after process_day().
      Derived classes can use this to setup for the current day.
      Normally clearing daily state and or accumlators.
   **/
   virtual bool end_year()                                      modification_=0;
   /**<\fn This is called at the end of the last day of the year after process_day()
      Derived classes may override this method to perform special processing
      (such as annual report generation and annual accumulator setdown )
      Returns true if successful
   **/
   virtual bool stop()                                          modification_=0;
   /**<\fn Overridden to do any special setup at the end of the simulation.
      This will be called one time at the end of run()
      but only if start was true and run loop was started.
      It will be called even if
      I.e. CropSyst Stop recording to output file
   **/
 public:
   RENDER_INSPECTORS_DECLARATION_PURE;
   /**<\fn
      Derived classes can override this method to add variable inspection
      to the list of inspectors.
      Instance description is a caption/label identifying the recorder.
      The caller (usually the owner) of the object will provide the
      the instance description because it will likely know the specific
      name or ID of the object to be recorded where as the recording
      object might not have much meta information about itself.
      The recorder may override this description and provide it's own.
      The recorder_instance description may be 0, in which case
      the recorder is expected to provide its own description;
      otherwise the recorder would be anonymous .
      The description should not be a type, but some identifier
      unique to the instance of the object.
      The object is given the context with which it is possible
      to identify the objects position in its instanciation,
      so it is generally not necessary to carry/compose such information
      in the description.
      The statistic indicates if the recorder is used as a container of
      a statistical element values  (I.e. an accumulator).
      For example, in the dairy model, a facility may have gas emission value
      produced for the day; in this case the gasses are daily value so the statistic is "value_statistic".
      The facility will have unreleased gasses which are cumulative so the statistic is "sum_statistic".
   **/
   inline virtual const char *get_ontology()                const { return ""; } //160606
   inline virtual const Emanator *get_emanator()             const { return 0; }  //160606
      // Observation inspector emanation is optional,
   inline virtual const Emanator *get_emanator_annual()                    const //160606
      { return get_emanator(); }
      // There isn't actually a special annual emanator.
      // and some elements dont necessarily have a yearly context
      // Derived class will simply returns the emanator indicating that annual
      // inspection is relevant to the model's output regimen.
      // (I.e. crop have growing season)
};
//_2013-06-18___________________________________________________________________
class Simulation_element_abstract
: public implements_ Simulation_element
{
 protected:
   const CORN::date32 &today_raw;                                                //170524

      //Conceptual: The date (today) should probably be any temporal class

   CORN::Date_cowl_const_32 today;                                               //170524
   cognate_ Event_scheduler *event_scheduler; // optional
   contribute_ bool ended_year;                                                  //170413
 public:
   Simulation_element_abstract
      (const CORN::date32 &today_raw);                                           //170524
   virtual ~Simulation_element_abstract();                                       //151204
   virtual bool is_valid()                                         affirmation_;
   inline virtual bool initialize()             initialization_ { return true; } //161201
   virtual bool start()                                           modification_;
   virtual bool start_year()                                      modification_;
   virtual bool start_day()                                       modification_;
   virtual bool process_day()                                     modification_;
   virtual bool end_day()                                         modification_;
   virtual bool end_year()                                        modification_;
   virtual bool stop()                                            modification_;
   virtual nat32 take_events(modifiable_ CORN::Container &events) modification_; //150930
   inline virtual const CORN::Date_const &ref_today()     const {return today; } //170524_150107_151208
   RENDER_INSPECTORS_DECLARATION;                                                //150917
};
//_2015-06-08___________________________________________________________________
class Simulation_element_composite      // abstract class
: public extends_ Simulation_element_abstract                                    //150608
{
 protected:
   CORN::Bidirectional_list sub_elements;                                        //170528
      // Bidirectional allows end/stop methods to be processed in reverse.
      // Processing in reverse allows elements to be consistently
      // deconstructed in the reverse order they were instanciated/started.
 public:
   Simulation_element_composite
      (const CORN::date32 &today_raw);
   inline virtual ~Simulation_element_composite()                             {}
   //NYI Should implement    virtual bool is_valid()               affirmation_; //150925
   virtual bool initialize()                                    initialization_; //150429
   /**<\fn Override this method for operations performed  after construction.
      Initialization of external resources.
      Typically input and output files are open and read.
      Submodels would be instanciated here.
      \return true true if initialization successful
   **/
   virtual bool start()                                           modification_;
   /**<\fn Override this function for setup at the start of the simulation.
      Typically counters and accumulators would be cleared here.
      This will be called one time usually at the beginning of run()
      or soon after the simulation_element is instanciated and initialized
      during the course of the simulation run.
      \return true if start was ok (and run loop can begin).
      I.e. CropSyst Start recording to output file.
   **/
   virtual bool start_year()                                      modification_;
   /**<\fn This is called at the beginning of the first day of the year before process_day()
      Derived classes may override this method to perform special processing
      (such as annual accumulator setup)
      \return true if successful
   **/
   virtual bool start_day()                                       modification_;
   /**<\fn This is called each day before process_day().
      Derived classes can use this to setup for the current day.
      Normally clearing daily state and or accumlators.
   **/
   virtual bool process_day()                                     modification_;
   /**<\fn This the call done by the daily loop.
      It will check for any events that can be processed on this day.
      This method is often overridden for any special processing
      that is specific to the model.
      If overridden the Simulation_engine::process_day() method should
      be called first so the events get processed.
      Returns false if the process cause substantial errors
      or the simulation should be terminated.
   **/
   virtual bool end_day()                                         modification_;
   /**<\fn This is called each day after process_day().
      Derived classes can use this to setup for the current day.
      Normally clearing daily state and or accumlators.
   **/
   virtual bool end_year()                                        modification_;
   /**<\fn This is called at the end of the last day of the year after process_day()
      Derived classes may override this method to perform special processing
      (such as annual report generation and annual accumulator setdown )
      Returns true if successful
   **/
   virtual bool stop()                                            modification_;
   /**<\fn Overridden to do any special setup at the end of the simulation.
      This will be called one time at the end of run()
      but only if start was true and run loop was started.
      It will be called even if
      I.e. CropSyst Stop recording to output file
   **/
   inline bool append (Simulation_element *subelement)
      { return sub_elements.append(subelement); }
      // actually this is submission
   RENDER_INSPECTORS_DECLARATION;                                                //150917
};
//_2013-06-18___________________________________________________________________
} // namespace CS
#endif

