#include "CS_suite/observation/CS_inspection.h"

namespace CS
{
nat32 debug_inspection_count = 0;
char  inspection_level_codes [] = "CA";
char *inspection_level_labels[] =
{"continual"
,"annual"};
//______________________________________________________________________________
int Period::compare(const CORN::Item &other_item)                          const
{
   const Period &other_period = dynamic_cast<const Period &>(other_item);
   int compare_result
   = (this->level_or_period != other_period.level_or_period)
     ? -1
     : (this->initiation_datetime != other_period.initiation_datetime)
       ? -1
       : 0;
   // conceptual:  may also need to compare context
   return compare_result;
}
//______________________________________________________________________________
Inspection::Inspection
(const Inspector_abstract     &inspector_
,const Period                 &period_                                           //171115
,CORN::Units_code             timestep_code_                                     //170319
,const Desired_variables *desired_vars_daily
,nat32                desired_descriptive_summary_elements)
: CORN::Item()
, inspector       (inspector_)
, period          (period_)                                                      //171115
, timestep        (timestep_code_)                                               //170319
, tally           (0)
, tally_as_float  (0)
, debug_ID(++debug_inspection_count)
{
   const Inspector_scalar &as_scalar = dynamic_cast<const Inspector_scalar &>
         (inspector_);


/* Temp disabled for the CAMO project because

the daily values are being written in the season.


I should


   if ((desired_vars_daily && (desired_vars_daily->timestep == timestep_code_)   //170319
        && desired_vars_daily->is_desired(inspector_.variable_code_clad.get())   //180404
       ))
      // Although desired_vars_daily always has UT_day timestep
      // eventually I may have a loop for lists of other desired time steps
       //NYN && (desired_descriptive_summary_elements & STAT_value_bit)          //170318
   {  // STAT_value_bit is used to indicate that values are to be recorded
      //170317 record_dataset = true;
      //180404 moved to outer if
      //180404 if (desired_vars_daily->is_desired(inspector_.variable_code_clad.get()))   //170319
      switch(inspector_.get_mode())                                              //170314
      {  case CORN::DT_nat8    : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_with_dataset<nat8    ,float32,float32>(*(as_scalar.value.as_const_nat8)   ,desired_descriptive_summary_elements); break;
         case CORN::DT_nat16   : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_with_dataset<nat16   ,float32,float32>(*(as_scalar.value.as_const_nat16)  ,desired_descriptive_summary_elements); break;
         case CORN::DT_nat32   : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_with_dataset<nat32   ,float32,float32>(*(as_scalar.value.as_const_nat32)  ,desired_descriptive_summary_elements); break;
         case CORN::DT_int8    : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_with_dataset<int8    ,float32,float32>(*(as_scalar.value.as_const_int8)   ,desired_descriptive_summary_elements); break;
         case CORN::DT_int16   : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_with_dataset<int16   ,float32,float32>(*(as_scalar.value.as_const_int16)  ,desired_descriptive_summary_elements); break;
         case CORN::DT_int32   : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_with_dataset<int32   ,float32,float32>(*(as_scalar.value.as_const_int32)  ,desired_descriptive_summary_elements); break;
         case CORN::DT_float32 : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_with_dataset<float32 ,float32,float32>(*(as_scalar.value.as_const_float32),desired_descriptive_summary_elements); break;
         case CORN::DT_float64 :
            {  tally_as_float = new CORN::Statistical_sample_with_dataset<float64,float32,float32>(*(as_scalar.value.as_const_float64),desired_descriptive_summary_elements);
               tally = (CORN::Statistical_sample_interface *)tally_as_float;
            } break;
         default: break;                                                         //170216
      }
   }
   else


*/

   {  switch(as_scalar.mode)
      {  case CORN::DT_nat8    : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_cumulative<nat8   ,float32>(*(as_scalar.value.as_const_nat8   ),desired_descriptive_summary_elements); break;
         case CORN::DT_nat16   : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_cumulative<nat16  ,float32>(*(as_scalar.value.as_const_nat16  ),desired_descriptive_summary_elements); break;
         case CORN::DT_nat32   : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_cumulative<nat32  ,float32>(*(as_scalar.value.as_const_nat32  ),desired_descriptive_summary_elements); break;
         case CORN::DT_int8    : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_cumulative<int8   ,float32>(*(as_scalar.value.as_const_int8   ),desired_descriptive_summary_elements); break;
         case CORN::DT_int16   : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_cumulative<int16  ,float32>(*(as_scalar.value.as_const_int16  ),desired_descriptive_summary_elements); break;
         case CORN::DT_int32   : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_cumulative<int32  ,float32>(*(as_scalar.value.as_const_int32  ),desired_descriptive_summary_elements); break;
         case CORN::DT_float32 : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_cumulative<float32,float32>(*(as_scalar.value.as_const_float32),desired_descriptive_summary_elements); break;
         case CORN::DT_float64 : tally = (CORN::Statistical_sample_interface *)new CORN::Statistical_sample_cumulative<float64,float32>(*(as_scalar.value.as_const_float64),desired_descriptive_summary_elements); break;
         default: break;
      }
   }
}
//_2016-06-4____________________________________________________________________
Inspection::~Inspection()
{  delete tally_as_float;
}
//_2015-11-11_______________________________________________________destructor_/
int   Inspection::compare(const CORN::Item &other_item)                    const
{  const Inspection &other = dynamic_cast<const Inspection &>(other_item);
   nat32 other_inspector_addr = (nat32)(&other.inspector);
   nat32 this_inspector_addr  = (nat32)(&this ->inspector);
   int compare_result =
      (other_inspector_addr != this_inspector_addr)
      ? -1 //not the same
      : period.compare(other.period);
   return compare_result;
}
//__2016-06-17__________________________________________________________________
bool Inspection::is_tally_statistic_applicable
(CORN::Statistic statistic)                                         affirmation_
{  bool applicable = false;
   if (tally) applicable = tally->is_applicable(statistic);
   return applicable;
}
//__2016-06-17__________________________________________________________________
float64 Inspection::get_tally_statistic(CORN::Statistic statistic)         const
{  float64 statistic_value = std::numeric_limits<double>::quiet_NaN();
   if (tally) statistic_value = tally->get_statistic(statistic);
   return statistic_value;
}
//__2016-06-17__________________________________________________________________
bool Inspection::commit()                                          modification_
{  if ((inspector.context.get_status() != Emanator::deleted_status) && tally)    //170404
      tally->commit();
/*
nat32 count = tally->get_count();
if (count > 365)
std::clog << "count:" << count << std::endl;
*/
   return true;
}
//_2016-06-15___________________________________________________________________
bool Inspections::commit()                                        rectification_
{  bool all_commited = true;
   FOR_EACH (inspection,Inspection,each_inspection)
      if (inspection->inspector.context.get_status() == Emanator::normal_status)
      all_commited &= inspection->commit();
   FOR_EACH_END(each_inspection)
   return all_commited;
}
//_2013-07-30___________________________________________________________commit_/
bool Inspections::reset()                                          modification_
{  bool reseted = true;
   FOR_EACH (inspection,Inspection,each_inspection)
      inspection->reset();
   FOR_EACH_END(each_inspection)
   return reseted;
}
//_2015-08-19____________________________________________________________reset_/
CORN::Dynamic_array<float32> *Inspection::mod_tally_as_float32()
{
   if (!tally_as_float)
      return 0; // probably tally of integers
   CORN::Dynamic_array<float32> *as_DA_float32 =
   tally_as_float                                                                //170216
   ? dynamic_cast<CORN::Dynamic_array<float32>*>(&tally_as_float->mod_dataset())
   : 0;
   return as_DA_float32;
}
//_2016-06-09___________________________________________________________________
} // namespace CS
