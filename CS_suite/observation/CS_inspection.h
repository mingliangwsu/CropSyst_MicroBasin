#ifndef CS_InspectionH
#define CS_InspectionH
#include "corn/container/item.h"
#include "CS_suite/observation/CS_inspector.h"
#include "CS_suite/observation/CS_desired_vars.h"
#include "corn/math/statistical/sample_cumulative_T.h"
#include "corn/math/statistical/sample_dataset_T.h"
#include "corn/metrology/units_clad.h"
//______________________________________________________________________________
namespace CS
{
   enum Inspection_level
      { continuous_inspection
      , annual_inspection
      , COUNT_inspection
      };

   #define ANY_INSPECTION COUNT_inspection
   extern char  inspection_level_codes[];
   extern char *inspection_level_labels[];
//______________________________________________________________________________
class Period
: public implements_ CORN::Item
{
 public:
   // const CORN::Temporal &temporality;
   CORN::datetime64  initiation_datetime; // was inception
   CORN::datetime64  completion_datetime;                                      //171114
            // completion_date is 0 until the period is completed
   nat8                  level_or_period;
   std::string           name;

   const Emanator         &context;
   // May need reference to emanator
   // so when the period is completed we only complete periods for the emanator which is completed

   // conceptual period probably should offer all the elements of
   // UED periods.

 public:
   inline Period
      (const CORN::Temporal   &temporality_
      ,nat8                    level_or_period_
      ,const std::string      &period_name_
      ,const Emanator         &context_)
      : CORN::Item()
      //171116, temporality        (temporality_)
      , initiation_datetime(temporality_.get_datetime64())
      , completion_datetime(0)   //will be set on period completion
      , level_or_period    (level_or_period_)
      , name               (period_name_)
      , context            (context_)
      {}
   virtual int compare(const CORN::Item &)                                const;
   inline bool complete(CORN::datetime64 datetime)
      {  completion_datetime = datetime;
         return true;
      }
};
//_2017-11-15___________________________________________________________________
class Inspection
: public extends_ CORN::Item
{
public:
int32 debug_ID;
 public:
   const Inspector_abstract  &inspector;
   const Period              &period;                                            //171115
   CORN::Units_clad  timestep;                                                   //170319
      // The timestep may be better suited in the inspector
      // on the otherhand Inspection deals with time (period)
/*171115 move to period
   nat8              level_or_period;
   std::string       period_name;
   std::string       dataset_name;  // I.e. journal
   CORN::datetime64  initiation_dateX;
   CORN::datetime64  completion_date;                                            //171114
      // completion_date will be 0 until the period is committed
      //171114 rename these to xxx_datetime
*/
 private:
   CORN::Statistical_sample_interface *tally;
   CORN::Statistical_sample_with_dataset<float64,float32,float32> *tally_as_float;
 public:
   Inspection
      (const Inspector_abstract &inspector
      ,const Period             &period                                          //171115
      ,CORN::Units_code    timestep                                              //170319
      /*1711115 moved to Period
      ,nat8                level_or_period
      // bitmask corresponding to STAT_XX_bits flags
      // indicating what to record
      // the STAT_value_bit indicates write all the items in the inspected tally
      ,CORN::datetime64    initiation_date
      ,const std::string  &period_name
      */
      ,const Desired_variables *desired_vars_daily                               //170319
      ,nat32            applicable_descriptive_summary_elements);
      // The instanciator of the inspector list
      // may specify the types of statistics that will be tallied.
      // However certain statistics may only be applicable to a variable
      // This inspector's instanciator will further filter
      // the desired descriptive summary elements to what is actually applicable.
      // The record dataset if provided will recording all the commited values.
      // This is useful to apply additional analysis or output collected data.
   virtual ~Inspection();
   virtual int   compare(const CORN::Item &)                              const;

   virtual bool commit()                                          modification_;
   /*conceptual write desired tally elements
   virtual bool write(std::ostream &)                              performs_IO_;
      // Currently this write simply identifies the qualified string
      // Eventually I may have a write 'mode'
      // to optionally write the observed value (or values) and statistics.
   */
   inline virtual bool reset()
      { bool sat = true; if (tally) sat &= tally->reset(); return sat; }         //170404_170323
   inline bool records_dataset()                                    affirmation_
      { return tally_as_float != 0; }                                            //170318
/*170317
   inline bool has_dataset()                                        affirmation_
      { return record_dataset; }
*/
   CORN::Dynamic_array<float32> *mod_tally_as_float32()           modification_; //160609
   bool is_tally_statistic_applicable(CORN::Statistic statistic)   affirmation_; //160617
   float64 get_tally_statistic(CORN::Statistic statistic)                 const; //160617
};
//_2016-06-13___________________________________________________________________
class Inspections
: public CORN::Unidirectional_list // of Inspection (Inspector_tally)
{
 public:
   nat32 desired_descriptive_summary_elements;                                   //150818
 public:
   inline Inspections()
      : CORN::Unidirectional_list(true)
      {}
   bool reset()                                                   modification_; //150819
   bool commit()                                                 rectification_;
};
//_2016-06-13__________________________________________________________________/
} // namespace CS

#endif
