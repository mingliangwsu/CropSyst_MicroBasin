#  include "corn/string/strconv.hpp"
#  include "common/simulation/synchronization.h"
#  include "corn/data_source/datarec.h"
#include <algorithm>
//______________________________________________________________________________
Synchronization::Synchronization(const CORN::Date_const &actual_date_)
:CORN::Date_clad_32(actual_date_.get_date32())
,days_offset(0)                                                                  //991130
,thermal_time(0)                                                                 //010716
,sync_mode_labeled(ACTUAL_DATE_MODE)
#if ((CS_VERSION > 0) && (CS_VERSION <= 3))
,sync_labeled_V3(V3_NOSYNC)                                                      //030606
#endif
,reschedule_mode_labeled(NO_RESCHEDULE)                                          //060413
{
   prefer_date_format();                                                         //170525
}
//             This constructor is used for rotation, etc.
//             This is used for actual and relative dates
//______________________________________________________________________________
Synchronization::Synchronization(Simulation_event sim_event,CORN::Days days_offset)
: CORN::Date_clad_32(0)                                                          //170525
,days_offset((int16)days_offset)  // eventually will be Days type                //991130
,thermal_time(0)                                                                 //130429
,sync_mode_labeled(RELATIVE_TO_SIMULATION_EVENT_MODE)
,simulation_event_labeled(sim_event)                                             //030627
#if ((CS_VERSION > 0) && (CS_VERSION <= 3))
,sync_labeled_V3(V3_NOSYNC)
#endif
,reschedule_mode_labeled(NO_RESCHEDULE)                                          //060413
{}
//_2003-06-05___________________________________________________________________
Synchronization::Synchronization
(Normal_crop_event_sequence normal_crop_event_sequence                           //130425
,CORN::Days offset_days)
: CORN::Date_clad_32(0)                                                          //170525
,days_offset((int16)offset_days)  // eventually will be Days type
,thermal_time(0)                                                                 //010716
,normal_crop_event_sequence_labeled(normal_crop_event_sequence)                  //130425
,sync_mode_labeled(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE)                          //030609
#if ((CS_VERSION > 0) && (CS_VERSION <= 3))
,sync_labeled_V3(V3_NOSYNC)                                                      //030606
#endif
,reschedule_mode_labeled(NO_RESCHEDULE)                                          //060413
{}
//_1999-11-22___________________________________________________________________
Synchronization::Synchronization(Synchronization_mode mode)
: CORN::Date_clad_32(0)                                                          //170525
,days_offset(0)  // eventually will be Days type
,thermal_time(0)
,sync_mode_labeled(mode)
#if ((CS_VERSION > 0) && (CS_VERSION <= 3))
,sync_labeled_V3(V3_NOSYNC)
#endif
,reschedule_mode_labeled(NO_RESCHEDULE)                                          //060413
{}
// This constructor is used to create a synchronization type (for searches)
//_2003-06-09___________________________________________________________________
Synchronization::Synchronization(Simulation_event sync_to_sim_event)
: CORN::Date_clad_32(0)                                                          //170525
,days_offset(0)  // eventually will be Days type
,thermal_time(0)
,sync_mode_labeled(RELATIVE_TO_SIMULATION_EVENT_MODE)
#if ((CS_VERSION > 0) && (CS_VERSION <= 3))
,sync_labeled_V3(V3_NOSYNC)
#endif
,reschedule_mode_labeled(NO_RESCHEDULE)                                          //060413
,simulation_event_labeled(sync_to_sim_event)
{}
// This constructor is used to create a synchronization relative to simulation event
//_2003-06-09___________________________________________________________________
CORN::datetime64 Synchronization::set(const CORN::Date_const &new_date) assignation_//170524
{  sync_mode_labeled.set(ACTUAL_DATE_MODE);
   return CORN::Date_clad_32::set(new_date);                                     //170525
}
//_2003-10-25__1999-03-17_______________________________________________________
const char *synchronization_mode_label_table[] =
{  LABEL_actual_date
,  LABEL_relative_to_simulation_event
,  LABEL_relative_to_sow_date
,  LABEL_before_planting
,  LABEL_after_normal_crop_growth_stage
,  LABEL_after_fruit_tree_growth_stage
,  LABEL_thermal_time
, 0};
//______________________________________________________________________________
const char *simulation_event_label_table[] =
{  LABEL_begin
,  LABEL_end
, 0};
//______________________________________________________________________________
#if ((CS_VERSION > 0) && (CS_VERSION <= 3))
// The synchronizations_V3_label_table label table is obsolete, remove this code when CropSyst goes to version 5
const char *synchronizations_V3_label_table[] =
{  LABEL_no_sync
,  LABEL_before_planting
,  LABEL_after_planting
,  LABEL_after_bud_break
,  LABEL_after_emergence
,  LABEL_after_flowering
,  LABEL_after_grain_filling                                                     //000120
,  "after_initial_fruit_growth"                                                  //030521
,  "after_veraison"                                                              //030521
,  "rapid_fruit_growth"                                                          //030521
,  LABEL_after_maturity
,  LABEL_after_harvest
,  LABEL_after_dormancy                                                          //021216
,  "after_termination"                                                           //030516
,  LABEL_thermal_time                                                            //010716
,  LABEL_actual_date
,  LABEL_relative_date
,  LABEL_relative_to_start_date                                                  //011204
,  LABEL_relative_to_end_date                                                    //011204
,  0};
//_2003-06-06___________________________________________________________________
Phrase_ID_or_label synchronizations_V3_strings[]=
{ ""
, "Before planting"
, "After planting"
, "After bud break"
, "After emergence"
, "After flowering(anthesis)"
, "After grain filling"                                                          //000120
, "After initial fruit growth"                                                   //030521
, "After veraison"                                                               //030521
, "After rapid fruit_growth"                                                     //030521
, "After maturity"
, "After harvest"
, "After dormancy"                                                               //021216
, "After termination"                                                            //010716
, "Thermal time"                                                                 //010716
, "Actual date"
, "Relative date"
, "Relative to start date"                                                       //011204
, "Relative to end date"                                                         //011204
, 0                                                                              //011204
};
#endif
//______________________________________________________________________________
const char *reschedule_label_table[] =
{ "no"
, "once"
, "multiple"
, 0};
#ifndef USE_CORN_TRANSLATOR_CLASS
#define common_translate(x) x
#endif
//_2006-04-13___________________________________________________________________
const std::string& Synchronization::append_to_string
(std::string &target
,const CORN::Date_format *target_date_format
,const CORN::Time_format *target_time_format)                              const
{  Synchronization_mode sync_mode = sync_mode_labeled.get();
   std::string sync_str;
   switch (sync_mode)                                                            //030606
   {  case ACTUAL_DATE_MODE :
      case RELATIVE_TO_SOWING_MODE :
         CORN::Date_clad_32::append_to_string                                    //020211
            (sync_str,target_date_format,target_time_format);                    //180626
      break;
      case RELATIVE_TO_SIMULATION_EVENT_MODE :
      case BEFORE_PLANTING_MODE :
      case AFTER_NORMAL_CROP_GROWTH_STAGE_MODE :
      case AFTER_FRUIT_TREE_GROWTH_STAGE_MODE :
         CORN::append_int16_to_string(days_offset,sync_str,10);                  //140606_991130
         sync_str.append(" ");
         sync_str.append("Days");
         sync_str.append(" ");
      break;
   }
   switch (sync_mode)                                                            //030606
   {  case ACTUAL_DATE_MODE :
         sync_str.append(" (actual date)");
      break;
      case RELATIVE_TO_SIMULATION_EVENT_MODE :
         sync_str.append(simulation_event_labeled.get_label());
      break;
      case RELATIVE_TO_SOWING_MODE :
         sync_str.append(" (relative to planting)");
      break;
      case BEFORE_PLANTING_MODE :
         sync_str.append(" (before planting)");
      break;
      case AFTER_NORMAL_CROP_GROWTH_STAGE_MODE :
         sync_str.append("after ");
         sync_str.append(normal_crop_event_sequence_labeled.get_label());
      break;
      case AFTER_FRUIT_TREE_GROWTH_STAGE_MODE :
         sync_str.append("after ");
         sync_str.append(fruit_tree_event_sequence_labeled.get_label());
      break;
      case THERMAL_TIME_MODE :                                                   //010716
      {  CORN::append_int16_to_string(thermal_time,sync_str);                    //140616
         sync_str.append(" ");
         sync_str.append("Degree days");
      }
      break;
   }
   std::replace( sync_str.begin(), sync_str.end(),'_', ' ');                     //140616
   target.append(sync_str);
   return target;
}
//_2014-06-16__2003-01-08_replaces_text_str___________________append_to_string_/
void Synchronization::validate()
{  Synchronization_mode sync_mode = sync_mode_labeled.get();
   if (  (days_offset == 0)   // days after xxx, cannot be 0
       &&(  (sync_mode   == AFTER_NORMAL_CROP_GROWTH_STAGE_MODE)
         || (sync_mode == AFTER_FRUIT_TREE_GROWTH_STAGE_MODE)))                  //030605
         days_offset = 1;
}
//______________________________________________________________________________
void Synchronization::set_as_actual(const CORN::Date_const &new_date)
{  sync_mode_labeled.set(ACTUAL_DATE_MODE);
   days_offset = 0;
   /*180202
      It looks like I broke this because the set would do nothing
      CORN::Date_clad_32 set(new_date.get_date32());                              //180202
   */
   CORN::Date_clad_32::set_date32(new_date.get_date32());                        //180202
}
//_2002-07-20___________________________________________________________________
bool Synchronization::is_before_planting()                          affirmation_
   // relative or phenologically
{  //		Note that thermal time is never before planting. 010716
   Synchronization_mode sync = sync_mode_labeled.get();                          //020322
   return (sync == BEFORE_PLANTING_MODE) ||                                      //030605
      ((sync == RELATIVE_TO_SOWING_MODE) &&                                      //030605
      (get_year() < 0));
}
//_2000-04-06___________________________________________________________________
void Synchronization::copy(const Synchronization &to_be_copied)
{  CORN::Date_clad_32::set(to_be_copied);                                        //170524
   days_offset                        = to_be_copied.days_offset;
   thermal_time                       = to_be_copied.thermal_time;
   sync_mode_labeled               .set(to_be_copied.sync_mode_labeled.get());
   normal_crop_event_sequence_labeled.set(to_be_copied.normal_crop_event_sequence_labeled.get());
   fruit_tree_event_sequence_labeled .set(to_be_copied.fruit_tree_event_sequence_labeled.get());
   simulation_event_labeled        .set(to_be_copied.simulation_event_labeled.get());
   reschedule_mode_labeled.set(to_be_copied.reschedule_mode_labeled.get());      //060413
}
//_2002-09-16___________________________________________________________________
CORN::date32 Synchronization::determine_from_relative
(const CORN::Date_const &reference_date
, Synchronization_mode relative_sync)                                      const
{  CORN::date32 actual_date_num = 0;
   if (sync_mode_labeled.get() == relative_sync)
   {  // Applies only to relative date syncs.
      CORN::Date_clad_32 actual_date(get_date32());                              //170525
      CORN::Year relative_year = get_year();
        if (is_leap_this_year() != reference_date.is_leap_this_year())           //120320_130225
            actual_date.dec_day();
       CORN::Year composed_year = (CORN::Year)(reference_date.get_year() + relative_year);
       actual_date.set_year(composed_year);
      actual_date_num = actual_date.get_date32();                                //170525
   }
   return actual_date_num;
}
//_2003-06-10___________________________________________________________________
CORN::date32 Synchronization::determine_from_thermal_time
(int16 current_thermal_time
, const CORN::Date_const &date_to_synchronize_to)                          const
{  // This checks the current thermal time against the thermal time requirements for synchronization
   // if the thermal time requirements have been satisfied, the date is synchronized and
   // the function returns true.
   if (get_sync_mode() != THERMAL_TIME_MODE) return 0; // not a thermal time sync.
   if (current_thermal_time < thermal_time) return 0; // requirements not satisfied.
   // condition satisfied, do the sync
   return date_to_synchronize_to.get_date32(); // thermal time has been satisfied, we'll accept this date
}
//_2003-06-10___________________________________________________________________
CORN::date32 Synchronization::determine
(const CORN::Date_const &date_to_synchronize_to)                           const
{  Synchronization_mode sync_mode = sync_mode_labeled.get();
   if (sync_mode == ACTUAL_DATE_MODE) return get_date32();   // no need to synchronize actual dates
   CORN::Date_clad_32 sync_date(date_to_synchronize_to.get_date32());
   switch (sync_mode)
   {  case BEFORE_PLANTING_MODE :   sync_date.dec_days(days_offset);  break;
      case AFTER_NORMAL_CROP_GROWTH_STAGE_MODE :
      case AFTER_FRUIT_TREE_GROWTH_STAGE_MODE:
         sync_date.inc_days(days_offset); break;
      // case THERMAL_TIME implemented with syncronize(float32 thermal_time)
      case RELATIVE_TO_SOWING_MODE  :
      {  CORN::Year  relative_year = get_year();
         CORN::Year  act_year = (CORN::Year)((int)sync_date.get_year() + (int)relative_year);
         CORN::DOY   act_doy = get_DOY();
         if (//!is_relative() &&                                                   //140624
             (is_leap_this_year() != date_to_synchronize_to.is_leap_this_year()) && (act_doy > 60)) //120320_130225
               act_doy--;
         sync_date.set_YD(act_year,act_doy);
      }  break;
      case RELATIVE_TO_SIMULATION_EVENT_MODE :
      {  // to date will either be the start or end simulation date.
         switch (simulation_event_labeled.get())
         {  case SIMULATION_BEGIN_DATE :  sync_date.inc_days(days_offset);  break;
            case SIMULATION_END_DATE :    sync_date.dec_days(days_offset);  break;
         }
      }  break;
   }
   return sync_date.get_date32();
}
//_2003-06-10___________________________________________________________________
bool Synchronization::setup_structure(CORN::Data_record &data_rec,bool for_write,const char *optional_prefix) modification_
{  // This is used for data record I/O.
   const char *prefix = optional_prefix ? optional_prefix : "";
   std::string  prefixed_synchronization              (prefix);
   std::string  prefixed_date                         (prefix);
   std::string  prefixed_offset                       (prefix);
   std::string  prefixed_thermal_time                 (prefix);
   std::string  prefixed_phenologic_normal            (prefix);
   std::string  prefixed_phenologic_fruit             (prefix);
   std::string  prefixed_relative_to_simulation_event (prefix);
   std::string  prefixed_repeat_each_season           (prefix);

   prefixed_date                        += LABEL_date;
   prefixed_synchronization             += LABEL_synchronization;
   prefixed_offset                      += LABEL_offset;
   prefixed_thermal_time                += LABEL_thermal_time;
   prefixed_phenologic_normal           += LABEL_phenologic;
   prefixed_phenologic_fruit            += "phenologic(fruit)";
   prefixed_relative_to_simulation_event+= LABEL_relative_to_simulation_event;
   prefixed_repeat_each_season          +=LABEL_repeat_each_season;

   // synchronization always expected
   // When reading, we expect every thing because mode is not yet known
   bool date_expected               = !for_write;
   bool offset_expected             = !for_write;
   bool rel_to_sim_expected         = !for_write;
   bool thermal_time_expected       = !for_write;
   bool phenologic_normal_expected  = !for_write;
   bool phenologic_fruit_expected   = !for_write;
   switch (sync_mode_labeled.get())
   {  case ACTUAL_DATE_MODE                     :  date_expected = true; break;  //030614
      case RELATIVE_TO_SOWING_MODE              :  date_expected = true; break;
      case RELATIVE_TO_SIMULATION_EVENT_MODE    :  offset_expected = true; rel_to_sim_expected = true; break;  //0609061
      case BEFORE_PLANTING_MODE                 :  offset_expected = true; break;
      case AFTER_NORMAL_CROP_GROWTH_STAGE_MODE  :  offset_expected = true; phenologic_normal_expected = true; break;
      case AFTER_FRUIT_TREE_GROWTH_STAGE_MODE   :  offset_expected = true; phenologic_fruit_expected = true; break;
      case THERMAL_TIME_MODE                    :  thermal_time_expected = true; break;
   }
   data_rec.expect_enum(prefixed_synchronization.c_str(),sync_mode_labeled);     //030605
   if (date_expected)               data_rec.expect_int32(prefixed_date.c_str(),date_num);                                          //170628_170524
         // make sure any date is clear because it will override
   if (offset_expected)             data_rec.expect_int16(prefixed_offset.c_str(),days_offset);                                     //030605
   if (rel_to_sim_expected)         data_rec.expect_enum (prefixed_relative_to_simulation_event.c_str(),simulation_event_labeled);  //030605
   if (phenologic_normal_expected)  data_rec.expect_enum (prefixed_phenologic_normal.c_str(),normal_crop_event_sequence_labeled);     //030605
   if (phenologic_fruit_expected)   data_rec.expect_enum (prefixed_phenologic_fruit.c_str(),fruit_tree_event_sequence_labeled);       //030605
   if (thermal_time_expected)       data_rec.expect_int16(prefixed_thermal_time.c_str(),thermal_time);                              //030605
   if (phenologic_normal_expected || phenologic_fruit_expected || thermal_time_expected)                                            //030608
      data_rec.expect_enum("reschedule",reschedule_mode_labeled);                                                                   //060413
   if (!for_write && (!prefix || (prefix &&(strcmp(prefix,"end_") != 0))))                                                          //030605
   {  // The following are for CS versions 0-3, Remove this if block when CropSyst goes to Version 5                                //030605
      #if ((CS_VERSION > 0) && (CS_VERSION <= 3))
      data_rec.expect_enum(LABEL_sync_old,sync_labeled_V3);                                                                         //030605
      #endif
      data_rec.expect_int16(LABEL_offset,days_offset);                                                                              //031123
      data_rec.expect_int16(LABEL_thermal_time,thermal_time);                                                                       //031123
      data_rec.expect_int32(LABEL_date,this->date_num);       // both "event_date" and "start_date" used to be "date"     //170628_030605
      #if ((CS_VERSION > 0) && (CS_VERSION <= 3))
      data_rec.expect_enum(LABEL_phen_sync_obsolete,sync_labeled_V3); // For backwards compatibility                                //030310
      data_rec.expect_enum(LABEL_synchronization,sync_labeled_V3);  // for LADSS                                                    //030310
      data_rec.expect_enum(LABEL_synchronisation,sync_labeled_V3);  // for LADSS UK spelling                                        //030310
      #endif
//180102 obsolete       data_rec.alias_entry(LABEL_sync_old,LABEL_phen_sync_obsolete);                                                                //011027
   }
   return true;
}
//_2003-06-05___________________________________________________________________
bool Synchronization::sync_type_matches(const Synchronization &other_sync) const
{  // Returns true if the other_sync has the same mode, and
   // if a phen sync or simulation event, the same sub sync mode.
   // Derived classes can override this if they add their own modes.
   bool mode_matches = (sync_mode_labeled.get() == other_sync.sync_mode_labeled.get() );
   if (mode_matches)
   {  // so far so good, but some sync modes have sub sync categories that need to be checked.
      switch (sync_mode_labeled.get())
      {        case RELATIVE_TO_SIMULATION_EVENT_MODE    :  mode_matches = simulation_event_labeled.get() ==  other_sync.simulation_event_labeled.get();                break;
               case AFTER_NORMAL_CROP_GROWTH_STAGE_MODE  :  mode_matches = normal_crop_event_sequence_labeled.get() ==  other_sync.normal_crop_event_sequence_labeled.get();break;
               case AFTER_FRUIT_TREE_GROWTH_STAGE_MODE   :  mode_matches = fruit_tree_event_sequence_labeled.get() ==  other_sync.fruit_tree_event_sequence_labeled.get();  break;
      }
   }
   return mode_matches;
}
//_2003-06-05___________________________________________________________________
// Eventually move this to CropSyst_synchronization class
// This constructor is used for synchronizing events based on synchronization triggers.
/*130903 Now using growth stage sequence
Synchronization::Synchronization(bool fruit_crop_model, nat32 growth_stage_bitmask)
:CORN::Date(CORN::Year(0),CORN::DOY(0))
,days_offset(0)  // eventually will be Days type                                 //991130
,thermal_time(0)                                                                 //010716
,sync_mode_labeled(fruit_crop_model ? AFTER_FRUIT_TREE_GROWTH_STAGE_MODE : AFTER_NORMAL_CROP_GROWTH_STAGE_MODE)   //030606
#if ((CS_VERSION > 0) && (CS_VERSION <= 3))
,sync_labeled_V3(V3_NOSYNC)                                                      //030606
#endif
//,repeat_each_season_obs_060413(false)                                            //060413
,reschedule_mode_labeled(NO_RESCHEDULE)                                          //060413
{  if (fruit_crop_model)
   {  switch (growth_stage_bitmask)
      {
//NA      case  PREPLANTING           : fruit_tree_event_sequence_labeled.set(xxxxxx); break;
      case  PLANTING              : fruit_tree_event_sequence_labeled.set(FGS_PLANTING); break;
//NA      case  PREEMERGENCE          : fruit_tree_event_sequence_labeled.set(xxxxxx); break;
//NA      case  EMERGENCE             : fruit_tree_event_sequence_labeled.set(xxxxxx); break;
//NA      case  RESTART               : fruit_tree_event_sequence_labeled.set(xxxxxx); break;
      case  BUD_BREAK             : fruit_tree_event_sequence_labeled.set(FGS_BUD_BREAK); break;
      case  ACTIVE_GROWTH         : fruit_tree_event_sequence_labeled.set(FGS_ACTIVE_GROWTH); break;
      case  END_CANOPY_GROWTH       : fruit_tree_event_sequence_labeled.set(NGS_END_CANOPY_GROWTH); break; //130429
      case  ANTHESIS              : fruit_tree_event_sequence_labeled.set(FGS_ANTHESIS); break;
//NA      case  GRAIN_FILLING         : fruit_tree_event_sequence_labeled.set(xxxxxx); break;
      case  INITIAL_FRUIT_GROWTH  : fruit_tree_event_sequence_labeled.set(FGS_INFRUCTESCENCE); break;
      case  VERAISON              : fruit_tree_event_sequence_labeled.set(FGS_VERAISON); break;
      case  RAPID_FRUIT_GROWTH    : fruit_tree_event_sequence_labeled.set(FGS_RAPID_FRUIT_DEVELOPMENT); break;
      case  MATURITY              : fruit_tree_event_sequence_labeled.set(FGS_MATURITY); break;
      case  DORMANT_or_INACTIVE   : fruit_tree_event_sequence_labeled.set(FGS_DORMANT); break;
      case  HARVESTABLE           : fruit_tree_event_sequence_labeled.set(FGS_HARVESTABLE); break;
      case  HARVESTED             : fruit_tree_event_sequence_labeled.set(FGS_HARVEST); break;
//NA      case  TERMINATED            : fruit_tree_event_sequence_labeled.set(xxxxxx); break;
      }
   } else
   {  switch (growth_stage_bitmask)
      {
//NYI      case  PREPLANTING          : normal_crop_event_sequence_labeled.set(xxxxxx); break;
      case  PLANTING             : normal_crop_event_sequence_labeled.set(NGS_SOWING); break;
//NYI      case  PREEMERGENCE         : normal_crop_event_sequence_labeled.set(xxxxxx); break;
      case  EMERGENCE            : normal_crop_event_sequence_labeled.set(NGS_EMERGENCE); break;
      case  RESTART              : normal_crop_event_sequence_labeled.set(NGS_RESTART); break;
//NA      case  BUD_BREAK            : normal_crop_event_sequence_labeled.set(xxxxxx); break;
      case  ACTIVE_GROWTH        : normal_crop_event_sequence_labeled.set(NGS_ACTIVE_GROWTH); break;
      case  END_CANOPY_GROWTH    : normal_crop_event_sequence_labeled.set(NGS_END_CANOPY_GROWTH); break; //130429
      case  ANTHESIS             : normal_crop_event_sequence_labeled.set(NGS_ANTHESIS); break;
      case  FILLING_OR_BULKING        : normal_crop_event_sequence_labeled.set(NGS_FILLING); break;
//NA      case  INITIAL_FRUIT_GROWTH : normal_crop_event_sequence_labeled.set(xxxxxx); break;
//NA      case  VERAISON             : normal_crop_event_sequence_labeled.set(xxxxxx); break;
//NA      case  RAPID_FRUIT_GROWTH   : normal_crop_event_sequence_labeled.set(xxxxxx); break;
      case  MATURITY             : normal_crop_event_sequence_labeled.set(NGS_MATURITY); break;
      case  DORMANT_or_INACTIVE              : normal_crop_event_sequence_labeled.set(NGS_DORMANT_or_INACTIVE); break;
      case  HARVESTABLE          : normal_crop_event_sequence_labeled.set(NGS_HARVESTABLE); break;
      case  HARVESTED            : normal_crop_event_sequence_labeled.set(NGS_HARVEST); break;
      case  TERMINATED           : normal_crop_event_sequence_labeled.set(NGS_TERMINATED); break;
      }
   }
}
*/
//_2003-06-06_____________________________________________________constructor__/
Synchronization::Synchronization(bool fruit_crop_model, Normal_crop_event_sequence growth_stage_sequence)
: CORN::Date_clad_32(0)                                                          //170525
,days_offset(0)  // eventually will be Days type
,thermal_time(0)
,sync_mode_labeled(fruit_crop_model ? AFTER_FRUIT_TREE_GROWTH_STAGE_MODE : AFTER_NORMAL_CROP_GROWTH_STAGE_MODE)
,reschedule_mode_labeled(NO_RESCHEDULE)
{  if (fruit_crop_model)
      fruit_tree_event_sequence_labeled.set(growth_stage_sequence);
   else
      normal_crop_event_sequence_labeled.set(growth_stage_sequence);
}
//_2013-09-03_____________________________________________________constructor__/
bool Synchronization::is_growing_season_synchronization()           affirmation_
{  Synchronization_mode sync_mode = sync_mode_labeled.get();
   return (sync_mode == RELATIVE_TO_SOWING_MODE)
       || (sync_mode == BEFORE_PLANTING_MODE)
       || (sync_mode == AFTER_NORMAL_CROP_GROWTH_STAGE_MODE)
       || (sync_mode == AFTER_FRUIT_TREE_GROWTH_STAGE_MODE)
       || (sync_mode == THERMAL_TIME_MODE);
}
//_2003-06-06___________________________________________________________________
bool Synchronization::is_phenologic_synchronization()               affirmation_
{  Synchronization_mode sync_mode = sync_mode_labeled.get();
   return (sync_mode == AFTER_FRUIT_TREE_GROWTH_STAGE_MODE)
       || (sync_mode == THERMAL_TIME_MODE);
}
//_2003-06-06___________________________________________________________________
bool Synchronization::is_actual_date_synchronization()              affirmation_
{  Synchronization_mode sync_mode = sync_mode_labeled.get();
   return (sync_mode == ACTUAL_DATE_MODE);
}
//_2003-06-06___________________________________________________________________
#if ((CS_VERSION > 0) && (CS_VERSION <= 3))
bool Synchronization::convert_from_CropSystV3()
{  bool was_CS_V3 = false;
   // This is provided for compatibility of CropSyst V3 and V4.1 files
   switch (sync_labeled_V3.get())
   {  // Version 3 did not have fruit crop model, relative to simulation events, and thermal time so those are not converted.
      case V3_BEFORE_PLANTING            :  was_CS_V3 = true; sync_mode_labeled.set(BEFORE_PLANTING_MODE);      break;
      case V3_AFTER_PLANTING             :  was_CS_V3 = true; sync_mode_labeled.set(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);      normal_crop_event_sequence_labeled.set(NGS_SOWING); break;
      case V3_AFTER_EMERGENCE            :  was_CS_V3 = true; sync_mode_labeled.set(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);      normal_crop_event_sequence_labeled.set(NGS_EMERGENCE); break;
      case V3_AFTER_FLOWERING            :  was_CS_V3 = true; sync_mode_labeled.set(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);      normal_crop_event_sequence_labeled.set(NGS_ANTHESIS); break;
      case V3_AFTER_GRAIN_FILLING        :  was_CS_V3 = true; sync_mode_labeled.set(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);      normal_crop_event_sequence_labeled.set(NGS_FILLING); break;
      case V3_AFTER_MATURITY             :  was_CS_V3 = true; sync_mode_labeled.set(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);      normal_crop_event_sequence_labeled.set(NGS_MATURITY); break;
      case V3_AFTER_HARVEST              :  was_CS_V3 = true; sync_mode_labeled.set(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);      normal_crop_event_sequence_labeled.set(NGS_HARVEST); break;
      case V3_AFTER_DORMANCY             :  was_CS_V3 = true; sync_mode_labeled.set(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);      normal_crop_event_sequence_labeled.set(NGS_DORMANT_or_INACTIVE); break;
      case V3_ACTUAL_DATE                :  was_CS_V3 = true; sync_mode_labeled.set(ACTUAL_DATE_MODE);     break;
      case V3_RELATIVE_TO_SOW_DATE       :  was_CS_V3 = true; sync_mode_labeled.set(RELATIVE_TO_SOWING_MODE);     break;
   }
   return was_CS_V3;
}
#endif
//______________________________________________________________________________
void Synchronization::set_relative_to_simulation_mode(int16 days_offset)
{  sync_mode_labeled.set(RELATIVE_TO_SIMULATION_EVENT_MODE);
   days_offset = days_offset;
}
//_2003-06-23___________________________________________________________________
void Synchronization::set_normal_growth_stage_offset
(Normal_crop_event_sequence normal_crop_event_sequence
,CORN::Days _offset_days)
{  clear(); //180822 set_YD(0,0);
   days_offset = _offset_days;  // eventually will be Days type
   thermal_time = 0;
   normal_crop_event_sequence_labeled.set(normal_crop_event_sequence);
   sync_mode_labeled.set(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);
   #if ((CS_VERSION > 0) && (CS_VERSION <= 3))
   sync_labeled_V3 =V3_NOSYNC;
   #endif
   reschedule_mode_labeled.set(NO_RESCHEDULE);
}
//_2004-08-02___________________________________________________________________
Reschedule_mode Synchronization::get_reschedule_mode()                     const
{  Reschedule_mode mode = reschedule_mode_labeled.get();
   // The following is to accomodate older files it can be removed in version 5.
   /*120130
   if ((mode == NO_RESCHEDULE) && (repeat_each_season_obs_060413))
      mode = ONE_RESCHEDULE;
   */
   return mode;
}
//_2006-04-13___________________________________________________________________
bool Synchronization::is_valid()                                    affirmation_
// Used by the event parameter editor to make sure the user remembered to schedule and event
{  bool valid = true;
   bool isa_date = is_date();
   bool date_is_0 = (get_date32() == 0);
   if (isa_date && date_is_0)
     valid = false;
   // I am pretty sure other other syncronizations are always valid
   return valid;
}
//_2006-07-26___________________________________________________________________
bool Synchronization::is_date()                                     affirmation_
{  Synchronization_mode sync = (Synchronization_mode)sync_mode_labeled.get();
   return (sync == ACTUAL_DATE_MODE); 
}
//_2001-12-07___________________________________________________________________
bool   Synchronization::is_synchronized_relatively()                affirmation_
{  Synchronization_mode sync = (Synchronization_mode)sync_mode_labeled.get();
   return (sync >= RELATIVE_TO_SIMULATION_EVENT_MODE) && (sync <= RELATIVE_TO_SOWING_MODE);
}
//_2002-03-22___________________________________________________________________
// was 762 lines
// 060413 470 lines
// 061109 547 lines

