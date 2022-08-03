#include "CS_UED_recorder.h"
#include "CS_suite/observation/CS_examination.h"
#include "UED/library/database_file.h"
#include "UED/library/varcodes.h"
#include "UED/library/varrec.h"
#include "UED/library/controls.h"
#include "corn/OS/file_system_engine.h"
namespace CS
{
//______________________________________________________________________________
Recorder_abstract::Recorder_abstract()
: examination(get_examination_global())                                          //171115
, ended_year(false)
{}
//_2017-03-19___________________________________________________________________
const char *Recorder_abstract::compose_conventional_name
(std::string            &composed
,const std::string      &ontology
,nat8                    level_or_period
,const std::string      &period_name // optional may be empty
,bool                    stats
,const CORN::Units_clad &timestep)                                         const
{
   composed += ontology;
   // Append period indicator
   composed+="@";
   if (period_name.empty())
         composed+=inspection_level_labels[level_or_period];
   else  composed+=period_name;
   composed+="$"; // tally_store is always stats
   // conceptual may want to output tally timestep
   std::string timestep_dscr_unused; //unused
   timestep.compose_description_str(timestep_dscr_unused, composed);
   return composed.c_str();
}
//______________________________________________________________________________
bool Recorder_abstract::start_year()                               modification_
{  ended_year = false;
   return true;
}
//______________________________________________________________________________
bool Recorder_abstract::end_year()                                 modification_
{  ended_year = true;
   return true;
}
//______________________________________________________________________________
bool Recorder_UED::UED_File_association::append_variable_definition
(UED::Variable_code  var_code
,CORN::Units_code    units_code
,const std::string  &ontology)
{  nat32 unused_array_index=0;
   if (!committed_variables.is_in_array(var_code, unused_array_index))
   {
      UED::Variable_definition_format_ontological_record *var_dev_rec
         = new UED::Variable_definition_format_ontological_record
            (var_code,units_code,ontology.c_str());
      UED_file->append_record(var_dev_rec,true); // UED_file should already be provided
      committed_variables.append(var_code);
   }
   return true;
}
//_2016-06-19__________________________________________________________________
Recorder_UED::Recorder_UED
(const CORN::OS::Directory_name &output_directory_)                              //171114
: Recorder_abstract        ()                                                    //171114
, output_directory         (output_directory_)
{}
//_2016-06-16___________________________________________________________________
bool Recorder_UED::end_day()                                       modification_
{  if (examination.inspections_completed_periodic.count())
      commit_inspections(examination.inspections_completed_periodic);
   return true;
}
//_2016-06-16___________________________________________________________________
bool Recorder_UED::end_year()                                      modification_
{  if (examination.inspections_completed_annual.count())
      commit_inspections(examination.inspections_completed_annual);
   return Recorder_abstract::end_year();
}
//_2016-06-16___________________________________________________________________
bool Recorder_UED::stop()                                          modification_ //171114
{  bool stopped = true;                                                          //170413
   // All inspections can now be written to UED file
   // The inspections_completed should at this point have been processed by end_day
   // but just incase we will put them back on to the inspections list for final processing.
   commit_inspections(examination.inspections       );
   commit_tallies    (examination.inspection_tallies);
   nat32 options = 0
      // UED_period_start_time_option
       | UED_period_start_date_option
      // UED_period_start_date_time_option
      // UED_period_end_time_option
       | UED_period_end_date_option
      // UED_period_end_date_time_option
      // UED_period_application_code_option
       | UED_period_enumeration_option
      // UED_period_index_option
      // UED_period_variable_code_option
      ;
   FOR_EACH_IN(UED_file_assoc,Recorder_UED::UED_File_association, UED_files, each_UED_file_assoc)
   {  FOR_EACH_IN(period,Period,examination.periods,each_period)
      {
      // WARNING currently I am outputting all periods encountered in the simulation
      // in all UED files, but originally I output only periods relevent
      // to the type of information stored in the  UED file (I.e. crop growth stages)
      // I Don't think it will cause problems with exisiting utilities
         CORN::datetime64 period_datetime = period->completion_datetime;
         UED::Period_record UED_period_rec
            (period->name.c_str(),options,period->initiation_datetime
            ,period_datetime,0,period->level_or_period,0,0);
         UED_file_assoc->UED_file->set_period(UED_period_rec);
      } FOR_EACH_END(each_period)
   } FOR_EACH_END(each_UED_file_assoc)
   UED_files.delete_all();
   if (!ended_year) stopped &= end_year();                                       //170413
   return true;
}
//_2016-06-16___________________________________________________________________
bool Recorder_UED::commit_inspections(CORN::Container &inspections)
{
   FOR_EACH_IN(inspection,Inspection,inspections,each_inspection)
   {
      if (inspection->records_dataset())
      {  // inspection requested to record the data set
         UED_File_association &UED_file_assocation
            = provide_inspection_UED_file_association(*inspection);
         UED::Database_file &UED_file = *UED_file_assocation.UED_file;
         UED::Data_record_creation_layout creation_layout
            (UED::Record_type_distinguisher_interface
               ::UED_data_set_date_var_units,inspection->inspector.get_variable_code()
            ,inspection->inspector.value_units_code.get(),UT_day,UT_date,simulated_quality);
         CORN::Dynamic_array<float32> *tally_as_float32 = inspection->mod_tally_as_float32();
         if (tally_as_float32)
         {  // Currently only adding float32 data records to CropSyst UED files
            UED::Binary_data_record_cowl *tally_record = new UED::Binary_data_record_cowl
               (*tally_as_float32,creation_layout
               ,inspection->period.initiation_datetime,false);                   //171115
            UED_file.append_record(tally_record,true); // actually submit_record
             UED_file_assocation.append_variable_definition
               (inspection->inspector.variable_code_clad.get()
               ,inspection->inspector.value_units_code.get()
               ,inspection->inspector.provide_ontology_qualified('/'));
         }
         // Actually I just want to delete the inspection, but need to check deletions





      }
      examination.deletable.take(each_inspection->detach_current());
   } FOR_EACH_END(each_inspection)
   return true;
}
//______________________________________________________________________________
bool Recorder_UED::commit_tallies(CORN::Container &inspection_tallies)
{
   FOR_EACH_IN(tally_store ,Examination::Inspection_tally_store,inspection_tallies,each_tally)
   {
      UED_File_association &UED_file_assocation = provide_tally_UED_file_association(*tally_store);
      UED::Database_file &UED_file = *UED_file_assocation.UED_file;
      if (tally_store->inspector.already_statistic)                              //171031
      {
         UED::Variable_code_clad variable_code
            (tally_store->inspector.get_variable_code() ,0,true);
         int8 tally_store_period_or_level = tally_store->period.level_or_period; //171115
         UED::Data_record_creation_layout creation_layout
            (tally_store_period_or_level == annual_inspection                    //171115
             ? UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
             : UED::Record_type_distinguisher_interface::UED_data_set_date_var_units
            ,variable_code.get()
            ,tally_store->inspector.value_units_code.get()
            ,(tally_store_period_or_level == annual_inspection) ? UT_year : UT_arbitrary_date //171115
            ,(tally_store_period_or_level == annual_inspection) ? UT_year : UT_date
            ,simulated_quality); // Quality is actually calculated from simulated_quality
         if (tally_store->stat_tally[0])                                         //180118
         {
            CORN::Dynamic_array<float32> *store_as_float32 =
                dynamic_cast<CORN::Dynamic_array<float32> *>
                  (&tally_store->stat_tally[0]->mod_dataset());
            UED::Binary_data_record_cowl *store_record = new UED::Binary_data_record_cowl
               (*store_as_float32,creation_layout,tally_store->period.initiation_datetime,false);
            UED_file.append_record(store_record,true); // actually submit_record
         }
         std::string ontology(tally_store->inspector.provide_ontology_qualified('/'));
             UED_file_assocation.append_variable_definition
               (variable_code.get()
               ,tally_store->inspector.value_units_code.get()
               ,ontology);
      }
      else
      for (nat8 stat = count_statistic; stat < CORN::statistic_COUNT; stat++)
      {
        if (tally_store->stat_tally[stat])
        {
         // augment variable code to include statistic
         UED::Variable_code_clad variable_code_with_stat
            (tally_store->inspector.get_variable_code() ,stat,true);

         int8 tally_store_period_or_level = tally_store->period.level_or_period; //171115
         UED::Data_record_creation_layout creation_layout
            (tally_store_period_or_level == annual_inspection
             ? UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
             : UED::Record_type_distinguisher_interface::UED_data_set_date_var_units
            ,variable_code_with_stat.get()
            ,tally_store->inspector.value_units_code.get()
            ,(tally_store_period_or_level == annual_inspection) ? UT_year : UT_arbitrary_date
            ,(tally_store_period_or_level == annual_inspection) ? UT_year : UT_date
            ,simulated_quality); // Quality is actually calculated from simulated_quality
         CORN::Dynamic_array<float32> *store_as_float32 =
                dynamic_cast<CORN::Dynamic_array<float32> *>
                (&tally_store->stat_tally[stat]->mod_dataset());
         UED::Binary_data_record_cowl *store_record = new UED::Binary_data_record_cowl
            (*store_as_float32,creation_layout,tally_store->period.initiation_datetime,false);
         std::string ontology_with_stat(tally_store->inspector.provide_ontology_qualified('/'));
         ontology_with_stat.append(".");
         ontology_with_stat.append(CORN::statistic_label_table[stat]);
             UED_file_assocation.append_variable_definition
               (variable_code_with_stat.get()
               ,tally_store->inspector.value_units_code.get()
               ,ontology_with_stat);
         UED_file.append_record(store_record,true); // actually submit_record
        } // if stat_tally
      }
   } FOR_EACH_END(each_tally)
   return true;
}
//______________________________________________________________________________
Recorder_UED::UED_File_association &Recorder_UED::provide_UED_file_association
(CORN::OS::File_name_concrete *target_UED_filename_given)             provision_
{  Recorder_UED::UED_File_association *provided
      = dynamic_cast<UED_File_association *>
         (UED_files.find_wstring(*target_UED_filename_given));
   if (!provided)
   {
      CORN::OS::file_system_engine.provide_directory/*180321 create_directory*/
         (target_UED_filename_given->get_parent_directory_name_qualified());
      UED::Database_file *provided_UED_file = new UED::Database_file
         (target_UED_filename_given->c_str(),std::ios::app,false);
      provided = new UED_File_association
         (target_UED_filename_given,provided_UED_file);
      UED_files.append(provided);
   } else
      delete target_UED_filename_given;
   return *provided;
}
//_2016-06-16___________________________________________________________________
Recorder_UED::UED_File_association &Recorder_UED::provide_inspection_UED_file_association
(const Inspection &inspection)
{
   CORN::Text_list context_qualified_instance;
   inspection.inspector.context.list_instance_path(context_qualified_instance);
   std::string context_name_qualified;
   context_qualified_instance.string_items
      (context_name_qualified,DEFAULT_DIRECTORY_SEPARATORa_chr);
   CORN::OS::Directory_name_concrete target_directory
      (output_directory,context_name_qualified);
   std::string UED_name;
   compose_conventional_name
      (UED_name
      ,inspection.inspector.context.ontology_domain
      ,inspection.period.level_or_period                                         //171115
      ,inspection.period.name // optional may be empty                           //171115
      ,!inspection.is_tally_statistic_applicable(value_statistic)
      ,inspection.timestep);
   CORN::OS::File_name_concrete *target_UED_filename = new
      CORN::OS::File_name_concrete(target_directory,UED_name,L"UED");
   return provide_UED_file_association(target_UED_filename);
}
//_2016-06-17___________________________________________________________________
Recorder_UED::UED_File_association &Recorder_UED::provide_tally_UED_file_association
(const Examination::Inspection_tally_store &tally_store)
{
   CORN::Text_list context_qualified_instance;
   tally_store.inspector.context.list_instance_path(context_qualified_instance);
   std::string context_name_qualified;
   context_qualified_instance.string_items
      (context_name_qualified,DEFAULT_DIRECTORY_SEPARATORa_chr);
   CORN::OS::Directory_name_concrete target_directory
      (output_directory,context_name_qualified);
   std::string UED_name;
   compose_conventional_name
      (UED_name
      ,tally_store.inspector.context.ontology_domain
      ,tally_store.period.level_or_period
      ,tally_store.period.name
      ,true  // tally_store is always stats
      ,tally_store.timestep);
   CORN::OS::File_name_concrete *target_UED_filename = new
      CORN::OS::File_name_concrete(target_directory,UED_name,L"UED");
   return provide_UED_file_association(target_UED_filename);
}
//_2016-06-16___________________________________________________________________
Recorder_UED *UED_recorder_global = 0;
//_2016-06-16___________________________________________________________________
Recorder_UED &provide_global_UED_recorder
(const CORN::OS::Directory_name  &output_directory)
{  if (!UED_recorder_global)
      UED_recorder_global= new Recorder_UED(output_directory);                   //171114
   return *UED_recorder_global;
}
//_2016-06-16___________________________________________________________________
Recorder_UED &ref_global_UED_recorder()
{  return *UED_recorder_global; }
//_2016-06-16___________________________________________________________________
} // namespace CS

