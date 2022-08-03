#include "CS_suite/observation/CS_emanator.h"
#include "CS_suite/observation/CS_examination.h"
#include <assert.h>

#include <iostream>
namespace CS {
CORN::Unidirectional_list inactive_emanators_global;
//______________________________________________________________________________
Emanator::Emanator
(nat32                ID_
,const std::string   &instance_name_
,const std::string   &ontology_
,bool                 ephemeral_
,const Emanator      *context_)
: CORN::Enumeration()
, ephemeral             (ephemeral_)                                             //160616
, ID                    (ID_)
, instance_name         (instance_name_)
, ontology_domain       (ontology_)
, context               (context_)
, status                (normal_status)
{}
//______________________________________________________________________________
Emanator::~Emanator()
{
   // Since we are going out of scope make sure any
   // continuous inspections are closed.
      // In most cases the examination will have already been instanciated
      // (if an examination is instanciated now, it is just going to be a dummy
      // so the date is completely irrelevent at this point).                    //171114
   CS::get_examination_global()                                                  //171114
      .complete_period_inspection(CS::continuous_inspection,*this,true);         //170319
}
//______________________________________________________________________________
/*170322 currently just listing the current domain, although I may need to restore this
nat16 Emanator::list_ontology_path(CORN::Text_list &qualified_ontology)    const
{  if (context)
       context->list_ontology_path(qualified_ontology);
   if (ontology_domain.length())      qualified_ontology.add_string(ontology_domain);
   return qualified_ontology.count();
}
*/
//_2016-06-10___________________________________________________________________
const char *Emanator::append_ontology_domain_name_to
(std::string &append_to,char delimiter)                                    const
{  if (!ontology_domain.empty())
   {  append_to.append(ontology_domain);
      if (delimiter) append_to += delimiter;
   }
   return append_to.c_str();
}
//_2017-03-22___________________________________________________________________
nat16 Emanator::list_instance_path(CORN::Text_list &qualified_instance)    const
{
   if (context) context->list_instance_path(qualified_instance);
   if (instance_name.length()) qualified_instance.add_string(instance_name);
   return qualified_instance.count();
}
//_2016-06-10___________________________________________________________________
Emanators::Emanators
(const CORN::Temporal &temporality_curr_)                                        //171115
: CORN::Enumeration_list(true)
, temporality_curr(temporality_curr_)                                            //171115
{}
//_2015-08-18___________________________________________________________________
Emanator &Emanators::know
(nat32              emanator_ID
,const std::string &instance_name
,const std::string &ontology
,bool               ephemeral                                                    //160616
,const Emanator    *context
,const CORN::Temporal &temporality)                                              //171115
{  Emanator *new_emanator = new Emanator
      (emanator_ID,instance_name,ontology,ephemeral,context);
   take(new_emanator);
   // It is presumed that all emanators on becoming known
   // will be inspected continuously through out the duration.

   CS::Period *complete_examination_period                                       //171115
      // I think the complete examination period
      = new CS::Period(temporality,CS::continuous_inspection,"",*context);       //171116
   CS::get_examination_global().periods.take(complete_examination_period);       //171115
   CS::get_examination_global().add_period_inspection                            //170319
         (*complete_examination_period                                           //171115
         ,UT_day //timestep of the inspected data
            // Currently only daily emanators
            // but should be parameter
         ,*new_emanator
         ,STAT_BASIC_ELEMENTS_INIT_FINAL_bits);
   return *new_emanator;
}
//_2015-08-18___________________________________________________________________
bool Emanators::forget
(nat32 emanator_ID)                                                 //cognition_
{  bool forgot = false;
   Emanator *identified_emanator = dynamic_cast<Emanator *>
      (find_nat32(emanator_ID));
   if (identified_emanator)
   {
      forgot = CS::get_examination_global()                                      //171115
         .complete_period_inspection                                             //170521
         (ANY_INSPECTION,*identified_emanator,true);                             //171222
      identified_emanator->set_status(Emanator::deleted_status);
      Emanator *detached_emanator = dynamic_cast<Emanator *>
         (detach(identified_emanator));                                          //170521
      inactive_emanators_global.take(detached_emanator);                         //170522
   }
   return forgot;
}
//_2015-08-18___________________________________________________________________
Emanator::Status Emanators::get_status_of(nat32 emanator_ID)               const
{  Emanator::Status identified_status = Emanator::unknown_status;
   const Emanator *identified_emanator = dynamic_cast<const Emanator *>
      (find_nat32(emanator_ID));
   if (identified_emanator)
      identified_status = identified_emanator->get_status();
   return identified_status;
}
//_2015-08-18___________________________________________________________________
Emanators *emanators_global;
Emanators &instantiate_emanators(const CORN::Temporal &temporality_curr)
{  if (!emanators_global)
      emanators_global = new Emanators(temporality_curr);                        //171114
   return *emanators_global;
}
//_2017-11-15___________________________________________________________________
Emanators &get_emanators()
{  if (!emanators_global)
   {  std::cerr << "error(programming): emanators have not been instanciated" << std::endl;
      exit(1); // should use a specific standard error code
   }
   return *emanators_global;
}
//_2017-11-15___________________________________________________________________
bool Emanators::start_year()                                       modification_
{  bool started = true;
   FOR_EACH(emanator,Emanator,each_emanator)
   {
      if (emanator->is_relevant_annually())
      {
         CS::Examination &examination = CS::get_examination_global();            //171115
         CS::Period *annual_period = new Period                                  //171115
            (temporality_curr,CS::annual_inspection,"",*emanator);               //171116
         examination.periods.take(annual_period);                                //171115
         started &= examination                                                  //171115
         .add_period_inspection
         (*annual_period,UT_day                                                  //171115
          //timestep of the inspected data
         ,*emanator,STAT_BASIC_ELEMENTS_INIT_FINAL_bits);
      }
   } FOR_EACH_END(each_emanator)
   return started;
}
//_2017-3-19____________________________________________________________________
bool Emanators::end_year()                                         modification_
{  bool ended = true;
   FOR_EACH(emanator,Emanator,each_emanator)
   {
      if (emanator->is_relevant_annually())
        ended &= CS::get_examination_global()                                    //171115
         .complete_period_inspection
         (CS::annual_inspection,*emanator,false);                                //171222
   } FOR_EACH_END(each_emanator)
   return ended;
}
//_2017-3-19____________________________________________________________________
bool Emanators::start(CORN::datetime64 inception_date)             modification_
{  bool started = true;
   FOR_EACH(emanator,Emanator,each_emanator)
   {
      Examination &examination = get_examination_global();                       //171115
      Period *examination_period = new Period                                    //171115
         (temporality_curr,CS::continuous_inspection,"",*emanator);              //171116
      examination.periods.take(examination_period);                              //171115
        started &= examination                                                   //171115
         .add_period_inspection
         (*examination_period
         ,UT_day //timestep of the inspected data
         ,*emanator,STAT_BASIC_ELEMENTS_INIT_FINAL_bits);
   } FOR_EACH_END(each_emanator)
   return started;
}
//_2017-04-14____________________________________________________________________
bool Emanators::stop()
{  bool stopped = true;
   FOR_EACH(emanator,Emanator,each_emanator)
   {
        stopped &= CS::get_examination_global()                                  //171115
         .complete_period_inspection
         (ANY_INSPECTION,*emanator,false);                                       //171222
      emanator->set_status(Emanator::stopped_status);
   } FOR_EACH_END(each_emanator)
   return stopped;
}
//_2017-03-24___________________________________________________________________
} // namespace CS

