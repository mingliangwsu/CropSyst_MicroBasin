#ifndef CS_examinationH
#define CS_examinationH
//______________________________________________________________________________
#include "corn/math/statistical/statistics_types.hpp"
#include "corn/seclusion.h"
#include "CS_suite/observation/CS_inspection.h"
#include "CS_suite/observation/CS_desired_vars.h"
#include "CS_suite/simulation/CS_simulation_element.h"
#include <ostream>
//#define DEBUG_INSPECTORS

/*171115 ToDo:

There is currently redundent information stored about period
(In each inspection)
When an emanator initiates (and defines) a period
There only needs to be one of these.
The inspections instanciated for that period context
can then have reference to the common period definition.
Note how I currently have to ensure that the UED recorder only
enters a single period definition

*/


//______________________________________________________________________________
namespace CS
{
extern Emanators &provide_inactive_emanators();
//______________________________________________________________________________
class Examination                                                                //170529
: public extends_ Simulation_element_abstract                                    //180529
{  // singleton
 public:
   class Inspection_tally_store
   : public implements_ CORN::Item
      {  // This is used to tally inspection tally statistical descriptors
         // (tallies of tallies)
       public:
         const Inspector_scalar  &inspector;
         CORN::Units_clad  timestep;                                             //170318

         // consideration: The timestep could either be
         // be intrinsic to the overall examination context (I.e. simulation models timestep)
         // but probably should be the contexted of the inspectors' emanator
         // or the period (probably not this case)

         const Period &period;                                                   //171115
            // reference to the inspection of which this set of tallies originates
         // NYI even though we specify what stats are applicable
         // for tallying when the inspector is created
         // the user may further control what is actually to be examined/reported
         CORN::Statistical_sample_with_dataset<float64,float32,float32>
            *stat_tally[CORN::statistic_COUNT];
         // We can have tallies of tallies, but that is not currently used
            // Of the tallied elements
       public:
         Inspection_tally_store
            (const Inspector_scalar &inspector
            ,const Period           &period_                                     //171115
            ,CORN::Units_code        timestep_code);                             //170318
         bool commit(const Inspection &Inspection)                modification_; //171114
            // It might be better to reference the processing date
            // the pass the completion date, but at this time
            // the tally store doesn't need to otherwise known the processing date;
         virtual int compare(const CORN::Item &)                          const;

         virtual bool is_key_string(const std::string &key_)       affirmation_;//180823
      };
 protected:
   CS::Desired_variables     *desired_variables_daily; // not owned
 public:
   CORN::Seclusion seclusion;
   nat32 desired_stats;
      // There might be 2 (or more) levels of stats
      // one for basic inspections and one for
      // tallies of tallies (or even tallies of tallied tallies)

   modifiable_ CORN::Unidirectional_list  singles;
      // Single events  for which there would not
      // be daily inspection (I.e. Crop season output).
   modifiable_ CORN::Unidirectional_list  inspectors;
   modifiable_ CS::Inspections            inspections;

   modifiable_ CORN::Unidirectional_list  inspectors_completed;
   modifiable_ CORN::Unidirectional_list  inspections_completed_periodic;
   modifiable_ CORN::Unidirectional_list  inspections_completed_annual;
      // During the run there may be ephemeral inspections
      // I.e. for crop growing season tallies.
      // as the periods finish the inspections are moved to inspections_completed
      // The consumer of the inspections will moved the completed inspections
      // to the deleted lists when the inspection when no longer needed
      // The annual list is used by recorders to optimize annual processing.
   modifiable_ CORN::Unidirectional_list deletable;
      // Inspector and Inspection consumers may moved completed items
      // to deleted lists indicating that everything has been recorded
      // and may be deleted.
      // The Examination will clear these lists at it leisure.
      // Because there will usually not be too many large items in these
      // lists these are only cleared each year.
   mutable modifiable_ CORN::Unidirectional_list  inspection_tallies;
      // inspection_tallies are not separated periodic and annual
      // because currently UED recorder only outputs these at the end.
      // this list is unique.
   /*NYN
     modifiable_ CORN::Unidirectional_list  inspector_tallies_annual;
     modifiable_ CORN::Unidirectional_list  inspector_tallies_periods;
   */
   #ifdef DEBUG_INSPECTORS
   CORN::Text_list debug_unique_inspector_instances;
   CORN::Text_list debug_unique_inspector_ontologies;
   #endif
   CORN::Unidirectional_list periods;                                            //171115
 private:
      // just reference the simulation element abstract refence
 public:
   Examination(const CORN::date32 &processing_date_ref);                         //171114
   Examination(const Inspection &copy_from);
   virtual ~Examination();
   inline nat32 desire_tally_statistics(nat32 desired_stats_)
      { return desired_stats = desired_stats_; }
      // This allows the user to control which statistics to actually maintain.
      // This is checked (XOR) against what statistics in a period are applicable
   inline bool know_desired_variables_daily                                      //170319
      (CS::Desired_variables *desired_variables_daily_)
      { desired_variables_daily = desired_variables_daily_; return true;}
   bool add_period_inspection
      (const Period &period                                                      //171115
      //171115 nat8               period // or level
      ,CORN::Units_code   timestep_code                                          //170319
      ,const Emanator    &context
      ,nat32 applicable_descriptive_summary_elements=STAT_BASIC_ELEMENTS_INIT_FINAL_bits);  //160613
      // Any object can inform the Examination that there is a new
      // period in effect that should have its own tally (for the object's emanator).
   bool complete_period_inspection
      (nat32 period,const Emanator &context                                      //160613
      ,bool before_end_day);                                                     //171222
      // When an object end its current period,
      // commit the tally (I.e. to output) and remove from inspector_tallies
   virtual bool start_year()                                      modification_;
   virtual bool end_day()                                         modification_;
   virtual bool end_year()                                        modification_;
   virtual bool filter()                                          modification_;
      // Applies filters specified with seclusion
      // to remove inspectors (and inspections)
      // so only relevent/desired observation occurs.
 protected:
   Inspection_tally_store &provide_inspection_tally_store
      (const Inspection &inspection
      ,CORN::Units_code  timestep)                                   provision_;
   bool inspection_tally_commit
      (const Inspection &inspection)                              modification_;
};
//______________________________________________________________________________

   // Currently instance, but should be provided

extern Examination &instantiate_examination_global                               //171115
(const CORN::date32 &processing_date);
extern Examination &get_examination_global();                                    //171115
} // namespace CS
//______________________________________________________________________________
#endif

// Classes that render inspectors need to include this file
// #include "CS_suite/simulation/CS_inspection.h"
