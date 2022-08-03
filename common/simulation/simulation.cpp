#error 151204 This class is now obsolete, replaced with CS::Simulation_engine
# include "common/simulation/operation.h"
# include "common/simulation/log.h"
# include "common/simulation/simulation.h"
# include "common/simulation/balancer.h"
//______________________________________________________________________________
CORN::Date simulation_today;                                                     //070227
//______________________________________________________________________________
const char *database_location_mode_label_table[] =
{"ANYWHERE"
,"MASTER"
,"PROJECT"
,"SCENARIO"
,0};
//______________________________________________________________________________
Common_simulation::Common_simulation
(CORN::Date              &_today
,const Date             &_start_date                                             //101221_021214_ now const
,const Date             &_stop_date                                              //101221_021214_ now const
,Common_simulation_log  *_event_log)                                             //030306
: start_date            (_start_date)
, stop_date             (_stop_date)
, Ytoday                (_today)                                                 //150920
, event_queue           (&queueA)                                                //040820
, queueA                ()                                                       //090309
, queueB                ()                                                       //090309
, completed_events      ()                                                       //090309
, events_for_next_season()                                                       //090309
//151003 appears to be obsolete, operatable_objects    ()
, balancers             ()                                                       //090309
, aborted               (false)                                                  //040806
, viable                (true)                                                   //040816
, event_log             (_event_log)
, balance_file_daily    (0)                                                      //090409
, balance_file_annual   (0)                                                      //090409
//NYI , balance_file_seasonal (0)
{}
//______________________________________________________________________________
Common_simulation::~Common_simulation()
{
   queueA.delete_all();
   events_for_next_season.delete_all();
//151003 appears to be obsolete   operatable_objects.delete_all();
   balancers.delete_all();
   queueB.delete_all();
   completed_events.delete_all();
   if (balance_file_daily)    delete balance_file_daily;
   if (balance_file_annual)   delete balance_file_annual;
//NYI  if (balance_file_seasonal) delete balance_file_seasonal;
}
//_2009-04-09___________________________________________________________________
bool Common_simulation::initialize()                             initialization_
{
   return true;
}
//_2015-05-05___________________________________________________________________
bool Common_simulation::start()                                    modification_
{  // Note that the start date is always the target start date
   simulation_today.set(Ytoday);                                                  //070227
   if (event_log)
   {  start_date.set_format(D_YMD,D_YYYY|D_Mmm|D_lead_zero,'/',true);
      event_log->record(get_ID(),"event","start","start of simulation");         //030306
      *event_log << "status=start"<< std::endl; // This shows the start icon in the schedule viewer
      *event_log << "model=simulation"<< std::endl;
   }
   if (balancers.count())
   {
      CORN::OS::File_name_concrete balance_daily_filename    (get_output_directory_name(),"balance_daily.dat");  //120320
      CORN::OS::File_name_concrete balance_annual_filename   (get_output_directory_name(),"balance_annual.dat");  //120320
//NYI      CORN::File_name balance_seasonal_filename ("balance_daily.dat");   balance_seasonal_filename.set_path(output_dirname);
      balance_file_daily   = new std::ofstream(balance_daily_filename.c_str());
      balance_file_annual  = new std::ofstream(balance_annual_filename.c_str());
//NYI      balance_file_seasonal= new std::ofstream(balance_seasonal_filename.c_str());
      (*balance_file_daily) << "\"date\"\t";
      (*balance_file_annual) << "\"year\"\t";
//NYI      balance_file_seasonal << "\"season\"\t";

      FOR_EACH_IN(balancer, Simulation::Balancer, balancers,each_balancer)
      {  balancer->write_column_headers(*balance_file_daily);
         (*balance_file_daily) << "\t";
         balancer->write_column_headers(*balance_file_annual);
         (*balance_file_annual) << "\t";
//NYI         balancer->write_column_headers(*balance_file_seasonal);
//NYI          (*balance_file_seasonal) << "\t";
      } FOR_EACH_END(each_balancer)
      (*balance_file_daily)    << std::endl;
      (*balance_file_annual)   << std::endl;
//NYI       (*balance_file_seasonal) << std::endl;
   }
//151203   #if (CS_VERSION != 4)
   {  Synchronization rel_to_start_date_sync(SIMULATION_BEGIN_DATE,0);           //030605_110505 moved from run()
      synchronize(rel_to_start_date_sync,start_date,SYNCHRONIZE_ALL_OBJECTS);    //031010
   }
   {  Synchronization rel_to_end_date_sync(SIMULATION_END_DATE,0);               //030605
      synchronize(rel_to_end_date_sync,stop_date,SYNCHRONIZE_ALL_OBJECTS);       //031010
   }
//151203   #endif
   return true;
}
//_2009-04-09___________________________________________________________________
bool Common_simulation::stop()                                     modification_
{  // Note that the actual stop date may not be the desired/target stop date
   if (event_log)
   {
      event_log->record((nat32)
         get_ID(),"event","stop","end of simulation");                           //030306
      *event_log << "date=" <<Ytoday.get() << " (" << Ytoday.as_string() << ")" << std::endl;
      *event_log << "status=stop"<<std:: endl;
      *event_log << "model=simulation"<< std::endl;
   }
   return true;
}
//______________________________________________________________________________
bool Common_simulation::log_contingency(Contingency contingency)   modification_
{  if (event_log)
   {
      event_log->record((nat32)
         get_ID(),"event",contingency_label_table[contingency]," contingency");  //030306
      *event_log << "status="<< contingency_label_table[contingency]<<std::endl;
      *event_log << "model=simulation"<< std::endl;
   }
   return true;
}
//_2006-08-06_________________________________________________log_contingency__/
bool Common_simulation::start_year()                                 modification_
{  bool started = true;
   // Balancer start_year() must be done before start_year() to
   // make sure accumulators are clear for the start of the year.
   // Components may then reset with any initial values.
   FOR_EACH_IN(balancer, Simulation::Balancer, balancers,each_balancer)          //070227
      started &= balancer->start_year();                                         //070227
   FOR_EACH_END(each_balancer)                                                   //070228
   return started;
}
//_2015-05-01___________________________________________________________________
bool Common_simulation::start_day()                                modification_
{  bool started = true;
   FOR_EACH_IN(balancer, Simulation::Balancer, balancers,each_balancer)
      started &= balancer->start_day();                                          //070227
   FOR_EACH_END(each_balancer)                                                   //041220
   return started;
}
//_2015-05-01___________________________________________________________________
CS::Simulation_run_result Common_simulation::run()
{  Ytoday.set(start_date);                                                           //150920_131011
   bool started_OK
      =  initialize()                                                             //150505
      && start();   // Start date already available                              //060808
   bool stopped_OK = false;
/*151203
   #if (CS_VERSION==4)
   //110505 Moved to start in V5 (probably would work OK for V4 also, but need to test
   {  Synchronization rel_to_start_date_sync(SIMULATION_BEGIN_DATE,0);           //030605
      synchronize(rel_to_start_date_sync,start_date,SYNCHRONIZE_ALL_OBJECTS);    //031010
   }                                                                             //030605
   {  Synchronization rel_to_end_date_sync(SIMULATION_END_DATE,0);               //030605
      synchronize(rel_to_end_date_sync,stop_date,SYNCHRONIZE_ALL_OBJECTS);       //031010
   }                                                                             //030605
   #endif
*/
   bool terminate = false;                                                       //030106
   if (started_OK)
   {  for (Ytoday = start_date
          ; (Ytoday <= stop_date) && !terminate && !aborted                       //040806
          ; Ytoday.inc())
      {
         std::clog << Ytoday.as_string() << "\r";
         simulation_today.set(Ytoday);                                            //070227
         if (Ytoday.get_DOY() == 1)
            terminate = !start_year();                                           //150501
         start_day();
         terminate = !process_day();                                             //150611_050115
         end_day();
         if ( balance_file_daily&&balancers.count())
            (*balance_file_daily) << Ytoday.as_string() << '\t';
         FOR_EACH_IN(balancer, Simulation::Balancer, balancers,each_balancer)    //070227
         {
            balancer->know_balance_file_daily(balance_file_daily);               //130823
            // Note I have put this here temporarily
            // This doesn't shouldn't need to be known every day
            // only needs to be done when the balancer is added
            // make sure to eventually move.
            balancer->end_day();                                                 //130823
         } FOR_EACH_END(each_balancer)
#ifndef linux
//090717 Not sure why this is crashing in linux.
         if (balance_file_daily) (*balance_file_daily)    << std::endl;          //090409
#endif
         if (Ytoday.is_last_DOY())                                                //040524
         {  end_year();                                                          //070228
            // Balancer end_year() must be done after end_year() to make sure the components have added any
            // last minute accumulations.
            if (balance_file_annual && balancers.count()) (*balance_file_annual) << Ytoday.get_year() << '\t';
            FOR_EACH_IN(balancer, Simulation::Balancer, balancers,each_balancer) //070227
            {
                balancer->know_balance_file_annual(balance_file_annual);         //30823
                // Note I have put this here temporarily
                // This doesn't shouldn't need to be known every year
                // only needs to be done when the balancer is added
                // make sure to eventually move this.
               balancer->end_year();                                             //070227
            } FOR_EACH_END(each_balancer)
            if (balance_file_annual) (*balance_file_annual)   << std::endl;      //090409
         }
      }
      stopped_OK = stop();                                                       //131010
   }
   CS::Simulation_run_result result = (Ytoday >= stop_date) && stopped_OK ? CS::RUN_SUCCESS : CS::RUN_FAILURE;  //040806
   if (!viable)      result = CS::RUN_NOT_VIABLE;                                    //040816
   if (terminate)    result = CS::RUN_TERMINATE;                                     //040806
   if (aborted)      result = CS::RUN_ABORT;

//120314 For debugging only trying to find why queue destruction crashes
queueB.delete_all();
completed_events.delete_all();
   return result;                                                                //040806
}
//______________________________________________________________________________
#ifndef EVENT_SCHEDULER_VERSION
nat16  Common_simulation::synchronize_thermal_time
(float32 thermal_time_today
,void *associated_object) // we can optionally syncronized only if the associated object matches
{
   // This function scans the scenario events list for thermal time
   // matching syncronizations.
   // It creates new actual date events based on the date to syncronize to.
   // The actual events operation pointer currently is normally
   // set to the potential event, because syncronization may
   // produce multiple actual events based on the potential
   // event definition, we don't delete or convert potential
   // events to actual events, we do move the potential events
   // to the synced_pot_events so we can optimize the matching
   // process not having to scan for events that have already
   // been syncronized and probably already processed.
   // Returns the number of events added to the act_events
   // list for the syncronization.
   nat16  sync_count = 0;
   Common_event_list &queue = *event_queue;
   FOR_EACH_IN(event,Simple_event,queue,each_thermal_time_sync)
   {
      bool synchronize_associateded_object =
         (  (associated_object==SYNCHRONIZE_ALL_OBJECTS)
          ||(event->get_associated_object() == associated_object)
          ); //060412_
      bool event_needs_synchronization = !event->is_synchronized();              //060412
      if (event_needs_synchronization && synchronize_associateded_object)        //060412
      {  // Check the start date
         int32 synced_date = event->begin_sync.determine_from_thermal_time(thermal_time_today,Ytoday);
         if (synced_date)                                                        //060412
         {  sync_count ++;
            event->date.set(synced_date);                                        //120314
         }
         // Check the end date
         Common_event *operation_event = dynamic_cast<Common_event *>(event);
         if (operation_event && operation_event->period)                         //120725
         {  int32 synced_date = operation_event->period->end_sync.determine_from_thermal_time(thermal_time_today,Ytoday);
            sync_count += synced_date != 0;
            operation_event->period->end_date.set(synced_date);
         }
   }  } FOR_EACH_END(each_thermal_time_sync)
   return sync_count;   // 021103 not sure how sync_count is used, it may be obsolete now
}
//_2003-06-09___________________________________________________________________
#endif
nat16  Common_simulation::synchronize
(const Synchronization &sync
,const Date &date_to_synchronize_to
,void *associated_object) // we can optionally syncronized only if the associated object matches
{
   // This function scans the scenario events list for
   // matching syncronizations.
   // It creates new actual date events based on the date to
   // syncronize to.
   // The actual events operation pointer currently is normally
   // set to the potential event, because syncronization may
   // produce multiple actual events based on the potential
   // event definition, we don't delete or convert potential
   // events to actual events, we do move the potential events
   // to the synced_pot_events so we can optimize the matching
   // process not having to scan for events that have already
   // been syncronized and probably already processed.
   // Returns the number of events added to the act_events
   // list for the syncronization.

   return event_queue->synchronize(sync,date_to_synchronize_to
      #ifndef EVENT_SCHEDULER_VERSION
      ,associated_object
      #endif
      );//030609
}
//______________________________________________________________________________
bool Common_simulation::process_day()
{
   Common_event_list  *pending_events = (event_queue == &queueA) ? &queueB : &queueA;  // Any events not processed today get put here and then back on the event list at the end of the loop
   Simple_event *event = 0;
   while (event = dynamic_cast<Simple_event  *>(event_queue->pop_first()))
   {  bool event_time_passed = (event->is_synchronized() ) && (event->date.get() < Ytoday.get()); //120719_120314
      Common_event  *operation_event = dynamic_cast<Common_event  *>(event);
      bool can_be_performed_simulation_start_date = true;
      if (operation_event)
      {  Common_operation *op = operation_event->get_operation();
         if (!op)
         {  // The operation is not yet loaded or not stored in the event list
            // the scenario may know how to load the operation.
            bool relinquish_op_to_event;
            op = get_operation(operation_event->get_operation_type_label(),operation_event->operation_name,operation_event->operation_filename,operation_event->resource_set_ID,relinquish_op_to_event);
            operation_event->set_operation(op,relinquish_op_to_event);
         }
         if (op)                                                                 //120719
            can_be_performed_simulation_start_date                               //120719
               = op->can_be_performed_before_simulation_start_date();            //120719
         else { delete event; event = operation_event = 0; }                     //120719

         // Events which the user has marked as not checked
         // can be removed since they are not to be simulated.
         // Also events must have an operation.
         // Also events that are not periods whose start date has passed.
         if (operation_event)
         {
            bool is_period = operation_event->is_period(true);
            if (is_period) event_time_passed = false;                            //120719
            bool event_checked = operation_event->is_checked();
            if (!event_checked)
            { delete event; event = operation_event = 0; }
         }
      }
      if (event)                                                                 //120719
      {
      if (event_time_passed)
         delete event;
      else if (!event->is_enabled() || !event->is_checked())                     //130430
         completed_events.append(event); // Disabled events go to completed events
      else
      {  bool iniciate_event = (event->date.get() == Ytoday.get())                //120314
            || (   (event->date.get() > 0)                                       //120725
                && (event->date.get() <= Ytoday.get())                            //120314
                &&(can_be_performed_simulation_start_date ));
         if (operation_event)                                                    //120719
         {
            bool repeat_event = false;
            bool end_event    = false;
            bool is_period = operation_event->is_period(true);                   //120719
            Common_operation *op = operation_event->get_operation();
            if (is_period)
            {  if (!operation_event->period->initialized && iniciate_event)
                  operation_event->period->initialize(Ytoday);
               else // else is needed othewise we decrement the event repetitions countdown immediately
                  repeat_event = operation_event->period->update_event_repetition();
               if (repeat_event)
                     operation_event->date.set(Ytoday);   // Update the event date so it shows the current date. //120314
               end_event = operation_event->period->update_end_period(Ytoday);
               if (end_event)
               {
                  operation_event->date.set(operation_event->period->end_date); // This will allow the end date to show in the output log (instead of the period start date) //120314
               }
            }
                // Note we use >= in end event because the simulation may request
               // the event to remain enabled a little bit longer
            if (iniciate_event|| (repeat_event
                && !end_event))  // I had this commented out on Nov 11 2004, a problem Luca had but this causes problems for events generated by grazing optimization model.
                               // This is right for the optimization model.
                               // Indeed completed periods are not moved to completed with out this.
                               // I think the problem was with only the irrigation on the very last date of the period I fixed this
   // I don't think I want to perform the operation
   //                      ,on the end date (don't want to do it if it is a repeated event and the repetition was not scheduled for this day)
   //                         the end operation period can do this if specific operations need it.
            {  if (event_log)
               {  event_log->record((nat32)
            #if (__LP64__ || _M_X64)
            (uint64_t)
            #endif
                     this,"event");
                     operation_event->log(*event_log,false);
                  *event_log<< "repeated="<< (repeat_event? "true": "false") << std::endl;
               }
               Event_status_indicator event_status =                             //151129
                  perform_operation(*op
                     #ifdef EVENT_SCHEDULER_VERSION
                     ,0 // crop is now never associated object because crop has its own event scheduler
                     #else
                     ,operation_event->get_associated_object()
                     #endif
                     ); //030902
                  // Perform operation may produce new actual events (I.e. sowing loads managements)
                  // so we need to synchronize:
               //Event_status_labeled event_status_labeled(event_status);          //151129_030519

               if (event_status /*151128 event_status_labeled.get()*/ == ES_FAIL)                        //040806
               {  switch (operation_event->contingency_labeled.get())
                  {  case ABORT_CONTIGENCY     : log_contingency(operation_event->contingency_labeled.get()); aborted = true; break;
                     case POSTPONE_CONTINGENCY  : event_status = /*151128 event_status_labeled.set*/(ES_POSTPONE); break;
                     case NOT_VIABLE_CONTINGENCY: log_contingency(operation_event->contingency_labeled.get()); viable = false; break;
                     case NONE_CONTINGENCY    	:
                     default :  // Do nothing, the event will just be eaten
                     break;
                  }
               }
               if (event_status/*151128 event_status_labeled.get()*/ == ES_POSTPONE)                    //040702
               {  Date delay_date(Ytoday);
                  delay_date.inc_day(1);
                  Common_event  *postponed_event = new Common_event(delay_date,op);
                  postponed_event->ID = operation_event->ID; // Make sure we keep the reference to the original event for the schedule viewer.
                  postponed_event->operation_name.assign(operation_event->operation_name); // Make sure we keep the reference to the original event for the schedule viewer.
                  postponed_event->operation_filename.assign(operation_event->operation_filename); // Make sure we keep the reference to the original event for the schedule viewer.
                  postponed_event->contingency_labeled.set(POSTPONE_CONTINGENCY);
                  pending_events->append(postponed_event);
               }
               if ((event_status < ES_ERROR) && is_period && iniciate_event)
                  event_status= (ES_START);
               // For event periods we disable the event when this date is reached.
               if (is_period)
                     pending_events->append(event);
               else  // single event:
               {  switch (event->begin_sync.get_reschedule_mode())               //060412
                  {  case MULTIPLE_RESCHEDULE :                                  //060412
                        event->date.set(NO_DATE);                                //120314
                        pending_events->append(event);
                     break;
                     case ONE_RESCHEDULE : // schedule once each season (year)
                        event->date.set(NO_DATE); // reset the synchronization for the next year. //120314
                        events_for_next_season.append(event);
                     break;
                     default : //  NO_RESCHEDULE
                        completed_events.append(event);
                     break;
                  }
               }
               if (event_log)
               {
                  #ifdef EVENT_SCHEDULER_VERSION
                  // Need new mechanism to output event status
                  #else
                  Event_status_labeled event_status_labeled(event_status);       //151129
                  *event_log << "status=" << event_status_labeled.get_label() << std::endl; //041210
                  #endif
               }
            } else                                                               //030614
               if (end_event)
               {  // we give the simulation the opportunity to close down other things.
                  bool ended  = end_operation_period(*op,Ytoday);
                  //151128 Event_status_labeled event_status_labeled(ES_STOP);
                  if (event_log)
                  { *event_log << "period_end=" << (ended ? "true" : "false") << std::endl; //041117
                    *event_log << "status=stop"   << std::endl;  //030519
                  };
                  event->date.clear(); //180822 set_YD((Year)0,(DOY)0);                            //120314_041117
                  bool seasonal = operation_event->reinitialize_for_period();    //041117
                  if (seasonal)  events_for_next_season.append(event);           //041117
                  else           completed_events.append(event);                 //041117
               }
               else              pending_events->append(event);
         } // operation_event
         else
         {
            if (iniciate_event)                                                  //130429
            {
               #ifdef EVENT_SCHEDULER_VERSION
               // process_model_specific_event was to handle crop parameter
               // adjustments this is now handled by the crop event scheduler
               #else
               Event_status event_status = process_model_specific_event(event);
               if (event_status == ES_COMPLETE)                                  //130428
               {  completed_events.append(event);                                //130428
                  event = 0;                                                     //130428
               }
               #endif
            } else pending_events->append(event);                                 //120719
         } //else operation_event
      } // event_time_passed
      } // event
   } // while
   event_queue = (event_queue == &queueA) ? &queueB : &queueA;                   //040820
   return true;
}
//_2000_________________________________________________________________________
#ifdef EVENT_SCHEDULER_VERSION
// associated object with only used with crop model, simulation elements can now have their own event scheduler
#else
nat16  Common_simulation::remove_events_associated_with(void *object)
{  nat16  remove_count = 0;
   Common_event_list &queue = *event_queue;                                      //040820
   FOR_EACH_IN(event,Simple_event,queue,event_iter)
   {  if (event->is_associated_with(object))
      {  event_iter->detach_current();                                           //030709
         completed_events.append(event);
         remove_count++;
      }
   } FOR_EACH_END(event_iter)                                                    //030709
   // Note we must not remove synced pot event since they may be
   // sharing operations.
   return remove_count;
}
//______________________________________________________________________________
nat16  Common_simulation::reschedule_growing_season_events(void *object)
{
   // The object is usually a crop
   // When a crop restarts after dormancy, call this function specifying the related crop.
   // The synchronizations will be clear
   Common_event_list unscheduled_events;                                         //030614
   nat16  rescheduled_count = 0;
   while (!events_for_next_season.is_empty())                                    //030614
   {  Common_event  *event = dynamic_cast<Common_event  *>                       //120314
         (events_for_next_season.pop_first());                                   //011207
      if (event->is_associated_with(object))
         // Note that the event date should have been cleared when it gets put in events_for_next_season.
         rescheduled_count += event_queue->append(event) != 0;                   //131217
      else
         unscheduled_events.append(event);
   }
   events_for_next_season.transfer_all_from(unscheduled_events);  // These events were not associated with this object
   return rescheduled_count;
}
//______________________________________________________________________________
nat16  Common_simulation::clear_growing_season_events(void *object)
{  // The object is usually a crop
   // When a crop is terminated, call this function specifying the related crop.
   // This calls remove_events_associated_with
   // and also clears events_for_next_season
   // Note we don't simply clear the list, because their may be
   // multiple event (I.e. CANMS or intercropping etc.)
   nat16  clear_count = 0;
   FOR_EACH_IN(event,Simple_event,events_for_next_season,event_iter)
   {  if (event->is_associated_with(object))
      {  event_iter->detach_current();                                           //030709
         completed_events.append(event);
         clear_count++;
      }
   } FOR_EACH_END(event_iter)                                                    //030709
   // Note we must not remove synced pot event since they may be
   // sharing operations.
   return clear_count + remove_events_associated_with(object);
}
//______________________________________________________________________________
nat16  Common_simulation::disassociate_events(void *object,nat16  operation_type_code)
{  nat16  disassociate_count = 0;
   Common_event_list &queue = *event_queue;                                      //040820
   FOR_EACH_IN(event,Common_event,queue,event_iter)
   {  Common_operation *event_op = event->get_operation();
      if (event->is_associated_with(object) && event_op && (event_op->get_type() == operation_type_code))
         disassociate_count += event->set_associated_with(0);                    //131217
   } FOR_EACH_END(event_iter)
   return disassociate_count;
}
//_2004-05-07___________________________________________________________________
#endif

nat32 Common_simulation::take_balancer(Simulation::Balancer *balancer)
{  // This gives the balancer to the simulation to maintain accumulators.
   balancers.append(balancer);
   return (nat32)balancer;
}
//_2007-02-27___________________________________________________________________

