#include "CS_suite/observation/CS_examination.h"
#include "CS_suite/observation/CS_emanator.h"

namespace CS
{
//______________________________________________________________________________
Examination::Examination(const CORN::date32 &processing_date_ref_)               //171114
: Simulation_element_abstract(processing_date_ref_)                              //171114_170528
, seclusion                      ()
, desired_stats                  (0xFFFF)
, inspectors                     (true)
, inspections                    ()
, inspectors_completed           ()
, inspections_completed_periodic ()
, inspections_completed_annual   ()
, deletable                      ()
, inspection_tallies             (true) // unique
{
#ifdef DEBUG_INSPECTORS
   debug_unique_inspector_instances.set_unique_keys(true);
   debug_unique_inspector_ontologies.set_unique_keys(true);
#endif
}
//_2016-06-06_____________________________________________________constructor__/
/*nyn
Examination::Examination(const Examination &copy_from)
//: emanator(copy_from.emanator)
{
}
//_2016-06-06_____________________________________________________constructor__/
*/
Examination::~Examination()
{
   // It is not necessary to clear the lists because corn container
   // destructors clear themselves.
   #ifdef DEBUG_INSPECTORS
   debug_unique_inspector_instances.sort();
   debug_unique_inspector_ontologies.sort();
   std::ofstream instances("instances.dat");
   std::ofstream ontologies("ontologies.dat");
   debug_unique_inspector_instances.write(instances);
   debug_unique_inspector_ontologies.write(ontologies);
   #endif
}
//_2016-06-06_______________________________________________________destructor_/
bool Examination::start_year()                                     modification_
{  bool started = true;
   FOR_EACH_IN(inspection,Inspection,inspections,each_inspection)
      if (inspection->period.level_or_period == annual_inspection)               //171115
         started &= inspection->reset();
   FOR_EACH_END(each_inspection)
   return Simulation_element_abstract::start_year() && started;                  //170528
}
//_2016-06-13___________________________________________________________________
bool Examination::end_year()                                       modification_
{  deletable.delete_all();
   return Simulation_element_abstract::end_year();
}
//_2016-06-16___________________________________________________________________
bool Examination::end_day()                                        modification_
{  bool ended = true;
   // Note that we must process the inpections before the inspectors.
   FOR_EACH_IN(inspection,Inspection,inspections,each_inspection)
   {
      ended &= inspection->commit();
      if (inspection->inspector.context.get_status() == Emanator::deleted_status)
      {  // The inspection's inspector's emanator has been marked for deletion
         // so the inspection is complete.
         // This shouldn't be needed because emanating objects should call
         // complete_period_inspection, this is just in case they dont.
         CORN::Unidirectional_list &detach_from_inspections                      //170528
            = (inspection->period.level_or_period == annual_inspection)          //171115
            ? inspections_completed_annual
            : inspections_completed_periodic;
         detach_from_inspections.append(each_inspection->detach_current());      //170528
      }
   } FOR_EACH_END(each_inspection)
   FOR_EACH_IN(inspector,Inspector_abstract,inspectors,each_inspector)
   {  if (inspector->context.get_status() == Emanator::deleted_status)
      {  // Transfer inspector whose emanating object has been deleted so the inspector is complete
         inspectors_completed.append(each_inspector->detach_current());
      }
   } FOR_EACH_END(each_inspector)
   return Simulation_element_abstract::end_day() && ended;                       //170528
}
//_2016-06-13___________________________________________________________________
bool Examination::add_period_inspection
(const Period       &period
,CORN::Units_code    timestep_code                                               //170319
,const Emanator     &context
,nat32               applicable_descriptive_summary_elements)
{  bool added = false;
   FOR_EACH_IN(inspector,Inspector_abstract,inspectors,each_inspector)
   {  if (inspector->is_scalar() &&                                              //170330
           (context.is_ephemeral() == inspector->context.is_ephemeral()))
      //was test if (context.instance_name == inspector->context.instance_name)  //170321
      {  // We are not saying that both the context and the inspectors context
         // needs to be ephemeral.
         // It is simply that both the context and the inspectors context
         // should have the same ephemorality (both always present, or both ephemeral).
         nat32 desired_applicable_descriptive_summary_elements                   //170318
            = desired_stats & applicable_descriptive_summary_elements;
         Inspection *inspection = new Inspection
            (dynamic_cast<CS::Inspector_scalar &>(*inspector)
            ,period
            ,timestep_code                                                       //170319
            ,desired_variables_daily                                             //170319
            ,desired_applicable_descriptive_summary_elements);                   //170318
         inspections.append(inspection); //uniquely
         added = true;
      } // else we don't tally vectors
      #ifdef DEBUG_INSPECTORS
      debug_unique_inspector_instances .add_string(inspector->provide_instance_name_qualified());
      debug_unique_inspector_ontologies.add_string(inspector->provide_ontology_qualified());
      #endif
   } FOR_EACH_END(each_inspector)
   return added;
}
//_2016-06-13___________________________________________________________________
bool Examination::complete_period_inspection
(nat32 level_period
,const Emanator &context
,bool before_end_day)                                                            //171222

{  bool completed = true;
   // Currently always true because not having any inspections is not an error

/* for debug
CORN::Text_list context_qualified_instance; // for debug output
context.list_instance_path(context_qualified_instance);
*/
   FOR_EACH_IN(period,Period,periods,each_period)
   {
      if (&period->context == &context)
          period->complete(today_raw);
   } FOR_EACH_END(each_period)
   FOR_EACH_IN(inspection,Inspection,inspections,each_inspection)
   {
/*
std::clog << "i_CD:" << inspection->inspector.context.ontology_domain
<< "\tCD:" << context.ontology_domain << std::endl;
*/

      if (&inspection->inspector.context == &context)
      {
      if (   (inspection->period.level_or_period == level_period)
          || (inspection->period.level_or_period == ANY_INSPECTION))             //170521

      {


         // Complete period inspection probably occurs before
         // the emanating object gets to end_day() so the daily
         // values would not otherwise have been commited
         if (before_end_day)
            inspection->commit();



         inspection_tally_commit(*inspection);
         Inspection *detached_inspection
            = dynamic_cast<Inspection *>(each_inspection->detach_current());     //170521
         switch (inspection->period.level_or_period  == annual_inspection)       //170521
         {  case annual_inspection :
               inspections_completed_annual  .append(detached_inspection);       //170521 each_inspection->detach_current());
            break;
            case continuous_inspection  :
               inspections_completed_periodic.append(detached_inspection);       //170521 each_inspection->detach_current());
            break;
            default:
               std::clog << "warning: examination inspection period case not handled (programming error?)" << std::endl;
            break;
         } // switch
         completed = true;
      }
      }
   } FOR_EACH_END(each_inspection)
   return completed ;
}
//_2016-06-13___________________________________________________________________
bool Examination::filter()                                        modification_
{
   // First remove unwanted inspections because inspections reference
   // inspectors, deleting an inspector will leave dangling reference.
   FOR_EACH_IN(inspection,Inspection,inspections,each_inspection)
   {
      // Currently I have a single seculsion filter for both
      // instance names and ontology
      const CORN::Text_list &inspector_instance_name_path
         = inspection->inspector.provide_instance_qualification_list();
      const CORN::Text_list &inspector_context_path_path
         = inspection->inspector.provide_ontology_qualification_list();
      if     (seclusion.is_excluded_text_list(inspector_instance_name_path))
         each_inspection->delete_current();
      else if(seclusion.is_excluded_text_list(inspector_context_path_path))
         each_inspection->delete_current();
   } FOR_EACH_END(each_inspection)
   FOR_EACH_IN(inspector,Inspector_abstract,inspectors,each_inspector)
   {
      // Currently I have a single seculsion filter for both
      // instance names and ontology
      const CORN::Text_list &inspector_instance_name_path
         = inspector->provide_instance_qualification_list();
      const CORN::Text_list &inspector_context_path_path
         = inspector->provide_ontology_qualification_list();
      if     (seclusion.is_excluded_text_list(inspector_instance_name_path))
         each_inspector->delete_current();
      else if(seclusion.is_excluded_text_list(inspector_context_path_path))
         each_inspector->delete_current();
   } FOR_EACH_END(each_inspector)
   return true;
}
//_2015-10-13___________________________________________________________________
Examination::Inspection_tally_store &Examination::provide_inspection_tally_store
(const Inspection &inspection
,CORN::Units_code  timestep_)                                         provision_
// I think the timestep of the tally store is/could be different from the inspection 170319
{  Examination::Inspection_tally_store *new_inpection_tally
      = new Examination::Inspection_tally_store
         (dynamic_cast<const Inspector_scalar &>(inspection.inspector)
         ,inspection.period                                                      //171115
         ,timestep_);
   Examination::Inspection_tally_store *listed_inpection_tally
      = dynamic_cast<Examination::Inspection_tally_store *>
      (inspection_tallies.append(new_inpection_tally));
   return *listed_inpection_tally;
}
//_2016-06-17___________________________________________________________________
bool Examination::inspection_tally_commit
(const Inspection   &inspection)                                   modification_ //171114
{  Inspection_tally_store &inspection_tally
   = provide_inspection_tally_store(inspection,inspection.timestep.get());
      // Not sure what the timestep would be (so far here I only see inspection.timestep
   return inspection_tally.commit(inspection);
}
//_2016-06-17___________________________________________________________________
Examination::Inspection_tally_store::Inspection_tally_store
(const Inspector_scalar    &inspector_
,const Period              &period_                                              //171115
,CORN::Units_code           timestep_code)                                       //170319
: CORN::Item()
,inspector        (inspector_)
,timestep         (timestep_code)                                                //170319
,period           (period_)                                                      //171115
{  for (nat8 s = 0; s < CORN::statistic_COUNT; s++)
      stat_tally[s] = 0;
}
//_2016-06-17___________________________________________________________________
bool Examination::Inspection_tally_store::commit
(const Inspection &inspection)                                     modification_
{
   for (nat8 s = 0; s < CORN::statistic_COUNT; s++)
   {  CORN::Statistic stat = (CORN::Statistic)s;                                 //160812
      bool is_desired_stat = inspection.is_tally_statistic_applicable(stat);
      if (is_desired_stat)
      {  if (!stat_tally[s]) stat_tally[s]
           = new CORN::Statistical_sample_with_dataset<float64,float32,float32>;
         if (stat_tally[s])
            stat_tally[s]->append(inspection.get_tally_statistic(stat));
      }
   }
   return true;
}
//_2016-06-17___________________________________________________________________
int Examination::Inspection_tally_store::compare
(const CORN::Item &other_item)                                             const
{  int comparison = -1;
   const Examination::Inspection_tally_store &other =
      dynamic_cast<const Examination::Inspection_tally_store &>(other_item);
   if (&(this->inspector) == &(other.inspector))
   {
      if (this->period.compare(other.period) == 0) comparison = 0;               //171115
   }
   return comparison;
}
//_2016-06-19___________________________________________________________________
bool Examination::Inspection_tally_store::is_key_string(const std::string &key_) affirmation_ //180823
{  return inspector.Inspector_abstract::is_key_string(key_); }
//_is_key_string____________________________________________________2018-08-23_/

Examination *examination_global = 0;                                             //161202
//_2016-06-14___________________________________________________________________
Examination &instantiate_examination_global
(const CORN::date32 &processing_date)
{  if (!examination_global)
        examination_global = new Examination(processing_date);
   return *examination_global;
}
//_2017-11-15___________________________________________________________________
Examination &get_examination_global()
{  if (!examination_global)
   {  std::cerr << "error(programming): examination have not been instanciated." << std::endl;
      exit(1); // should use a specific standard error code
   }
   return *examination_global;
}
//_2017-11-15___________________________________________________________________
} // namespace CS

