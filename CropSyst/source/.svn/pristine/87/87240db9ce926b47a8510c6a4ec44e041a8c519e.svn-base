#include "rotation.h"
#include "corn/OS/file_system_engine.h"
#include "common/weather/database/CS_weather_daily_UED.h"
#include "corn/data_source/vv_file.h"
#include "UED/library/timeqry.h"
#include "UED/library/std_codes.h"
namespace CropSyst {
//______________________________________________________________________________
Rotation::Rotation
#ifdef PLANTING_SCHEDULER
(const CORN::OS::File_name &rotation_filename_
,const Weather_provider    &weather_provider_
,const CORN::date32        &today_raw_
,const CORN::date32        &start_date_raw_
,const CORN::date32        &stop_date_raw_
)
: CS::Simulation_element_abstract                                   (today_raw_)
, weather_provider                                          (&weather_provider_)
, start_date(start_date_raw_)
, stop_date (stop_date_raw_)
#else
(const CORN::OS::File_name &rotation_filename_)
: CORN::Item                                                                  ()
//, weather                                                             (weather_)
#endif
, parameters                                                                  ()
, cyclable                                                               (false)
, template_rotation_file_name                               (rotation_filename_)
, cycle                                                                      (0) //180529
{
   // Probably should have initialize (construct) method
   CORN::VV_File rotation_file(rotation_filename_.c_str(),true);
      // Need to preserver struture to resolve directory name
   if (rotation_file.get(parameters))
   {

//std::clog << "debug rot filename:" << rotation_filename_.c_str() << std::endl;

      parameters.resolve_directory_entry_names                                   //171204
         (rotation_filename_.get_parent_directory_name_qualified());             //171204

   }
   else
      std::cerr << "error: Unable to load rotation: "
      << template_rotation_file_name << std::endl;
}
//_2016-07-07___________________________________________________________________
nat32 Rotation::render_planting_events
(modifiable_ CORN::Container &event_list
,CORN::Year start_year
,CORN::Year stop_year
,nat8 cycle)                                                               const
{  // Generates cycle shifted sowing events
   nat8 build_years = parameters.years;
   bool rotation_schedule_relative = build_years > 0;                            //140227
   // Note that phenology adjustment could be moved to Rotator::start() but current
   nat16 i;

      // After determining phenology adjustments,
      // we need to restart the weather for the starting date because
      // the soil temperature initialization that follows needs
      // the weather setup for the first day of the simulation.
   CropSyst::Sowing_event *sow_events[SOW_EVENTS_ARRAY_ALLOC]; // an arbitrary large number
   for (i = 0; i < SOW_EVENTS_ARRAY_ALLOC-1; i++)
      { sow_events[i] = 0; }
   nat8 template_sow_index = 0;
   nat8 sowing_count = 0;
   FOR_EACH_IN(sow_event,CropSyst::Sowing_event,parameters.planting_events,each_sowing)
   {  sow_events[template_sow_index] = sow_event;
      rotation_schedule_relative &= sow_event->begin_sync.is_relative();         //140227
      template_sow_index ++;
      sowing_count++;
   } FOR_EACH_END(each_sowing)
   const CORN::OS::Directory_name &rotation_dir                                  //170929
      = template_rotation_file_name.get_parent_directory_name_qualified();       //170929
   if (rotation_schedule_relative)                                               //140227
   {
      char build_year_shift_index_cstr[10];  // rename to cycle_cstr
      CORN::nat8_to_cstr((int)cycle,build_year_shift_index_cstr,10);
      nat8 target_seq_year_index = cycle;
      for (Year year = start_year                                                //151008
          ;year <= stop_year                                                     //151008
          ;year ++)
      {  for (nat8 sow_index = 0; sow_index < sowing_count ;sow_index++)
         {  CropSyst::Sowing_event *template_sow_event = sow_events[sow_index];
            Year template_sow_seq_year =  template_sow_event->begin_sync.get_year();
            if ((template_sow_event) && (template_sow_seq_year == target_seq_year_index))
            {  CropSyst::Sowing_event *gen_event = new CropSyst::Sowing_event(); //130611
               CropSyst::Sowing_operation &template_sow_op =  dynamic_cast<CropSyst::Sowing_operation &>(*(template_sow_event->get_operation()));
               char sow_year_cstr[10]; CORN::nat16_to_cstr((int)year,sow_year_cstr,10);
               gen_event->ID = "Sowing:";  gen_event->ID.append(build_year_shift_index_cstr); gen_event->ID.append(":");gen_event->ID.append(sow_year_cstr);
               // We have to have a copy of the sowing operation because
               // loaded events are transfer for each sowing event.
               CropSyst::Sowing_operation *gen_sow_op =new CropSyst::Sowing_operation(template_sow_op);
               gen_event->set_operation(gen_sow_op,true);                        //130906_130611
               Year gen_event_year = year;                                       //130611
               CORN::DOY gen_event_DOY =template_sow_event->begin_sync.get_DOY();//130611
               gen_event->begin_sync.set_YD(gen_event_year,gen_event_DOY);       //130611
               gen_event->begin_sync.sync_mode_labeled.set(ACTUAL_DATE_MODE);    //130611
               gen_event->date.set_YD(gen_event_year,gen_event_DOY);             //130830
               //180528 CORN::Date_clad_32 planting_date (year,gen_event_DOY);
                  //180529 actually planting_date is unused and can probably be deleted
               #ifdef PLANTING_SCHEDULER
               // Dont need to resolve filenames because
               // this is scenario setup and we dont want qualified filenames
               // in generated scenario files
               #else
               resolve_crop_and_management(*gen_sow_op,rotation_dir);
               #endif
               event_list.append(gen_event);                                     //160708
         }  }
         target_seq_year_index ++;                                               //130611
         if (target_seq_year_index >= build_years)                               //130611
            target_seq_year_index = 0;                                           //130611
      } // for build year
   } // rotation_schedule_relative
   else // not building relative rotation                                        //170929
   {
      FOR_EACH_IN(entry,CropSyst::Sowing_event,parameters.planting_events,each_event)
      {
         if (entry->is_checked())
         {
            /*this would here always be actual date
            entry->synchronize(Synchronization(SIMULATION_BEGIN_DATE,0),scenario_control_and_model_options.start_date ASSOCIATE_THIS); //030609
            entry->synchronize(Synchronization(ACTUAL_DATE_MODE),scenario_control_and_model_options.start_date ASSOCIATE_THIS);     //030609
            */
            date32 planting_date(entry->begin_sync.get_date32());
            CropSyst::Sowing_event *gen_event = new CropSyst::Sowing_event(*entry);
            gen_event->date.set_date32(planting_date);
            CropSyst::Sowing_operation *sowing_op = gen_event->sowing_op;
            #ifdef PLANTING_SCHEDULER
            // Dont need to resolve filenames because
            // this is scenario setup and we dont want qualified filenames
            // in generated scenario files
            #else
            resolve_crop_and_management(*sowing_op,rotation_dir);
            #endif
            event_list.append(gen_event);
         }
      } FOR_EACH_END(each_event)
   }
   return event_list.count();
}
//_2016-07-07___________________________________________________________________
nat32 Rotation::render_planting_events_adjusted_for_weather_conditions
(CS::Weather_database_daily   &weather
,modifiable_ CORN::Container  &computed_plantings_
,CORN::Year start_year
,CORN::Year stop_year
,nat8 cycle_)                                                               //const
{
   CORN::Date_clad_32 start_date(start_year,1);
   CORN::Date_clad_32 stop_date (stop_year,365);
   cycle = cycle_;
/*
   CORN::Date_clad_32 start_date(start_year,1);
   CORN::Date_clad_32 stop_date (stop_year,365);
*/
/*moved to start
   CORN::Bidirectional_list plantings_fixed_or_computable;
   render_planting_events
      (plantings_fixed_or_computable,start_year,stop_year,cycle);
   //180529 now member
   //CORN::Statistical_sample_with_dataset<float32,float32,float32>
   //      sowing_precipitation_window_meter;
   //CORN::Statistical_sample_with_dataset<float32,float32,float32>
   //      avg_air_temp_for_window;

   #define sowing_window_days 15
    int sowing_window_days_midpoint = sowing_window_days / 2;                    //170316brc
   Sowing_event *next_sowing_event = dynamic_cast<Sowing_event *>
      (plantings_fixed_or_computable.pop_first());
   if (!next_sowing_event) return false; // (rotation not loaded?)
   //180529 Sowing_operation
   sowing_operation = dynamic_cast<Sowing_operation *>
         (next_sowing_event->get_operation());
   CORN::Date_clad_32 plant_by_date_actual(0);
   if (sowing_operation->plant_by_date)                                          //170602
   {  plant_by_date_actual.set_date32(sowing_operation->plant_by_date);          //170602
      plant_by_date_actual.inc_years(start_year);                                //170602
   }
   //180529 now member CORN::Date_clad_32 clear_window_date(next_sowing_event->date);
   clear_window_date.set(next_sowing_event->date);                               //180529
   clear_window_date.dec_days(sowing_window_days_midpoint);                      //170316brc
*/
   start();                                                                      //180529

   /*Weather_provider **/weather_provider = const_cast <Weather_provider *>
      (&weather.ref_weather_provider());
   for (
        CORN::Date_clad_32 today(start_date)
       ;(today <= stop_date) && next_sowing_event
       ; today.inc_day())
   {
      weather.override_today(today.ref_date32());                                //170525
      weather.start_day();
      process_day();                                                             //180529
      /*180529 Moved to process_day
      if (today == clear_window_date)
      {
         sowing_precipitation_window_meter.reset();
         avg_air_temp_for_window.reset();
      }
      float32 precip = 0.0;                                                      //160726
      precip = weather_provider.precipitation_actual.get_m();
      sowing_precipitation_window_meter.append(precip);

      // See if there has been any appreciable preciptation in the last X days   //000330
      while (sowing_precipitation_window_meter.get_count()                       //141105
             > (Days)sowing_operation->delay_after_precip)
         sowing_precipitation_window_meter.remove_at(0);                         //141105
      bool warm_enough = true;
      nat8 window_size = 0;
      Sowing_date_mode planting_date_mode                                        //170331
         = sowing_operation->sowing_date_mode_labeled.get();
      if (plant_by_date_actual.get_date32() && (today >= plant_by_date_actual))  //170602
      {  // event may specify date to plant by (0 disables)
         next_sowing_event->date.set(today);                                     //170602
         planting_date_mode = FIXED_DATE;
      }
      switch (planting_date_mode)
      {
         case MIN_TEMP_REQ    :
         {
            float64 air_temp_avg = 0;
            air_temp_avg = weather_provider.air_temperature_avg.Celcius();
            avg_air_temp_for_window.append(air_temp_avg);
            while ((window_size = avg_air_temp_for_window.get_count()) > (Days)sowing_window_days) // 15//160708
               avg_air_temp_for_window.remove_at(0);
            float64 avg_temps = avg_air_temp_for_window.get_mean();              //131219
            warm_enough = (avg_temps >= sowing_operation->sowing_avg_temp);
           //NYI  bool appreciable_rain_in_X_days = sowing_precipitation_window_meter.provide_max() > appreciable_precip_m; //141105
            if ((today >= next_sowing_event->date)
                && (window_size == sowing_window_days)) // 15
            {
                // NYI && appreciable_rain_in_X_days
               if (warm_enough)
               {  CORN::Date_clad_32 computed_sowing_date(today);
                  computed_sowing_date.dec_days(sowing_window_days_midpoint);    //170316brc
                  next_sowing_event->date.set(computed_sowing_date);
                  //next_sowing_event->sync_mode_labeled.set(ACTUAL_DATE_MODE);
                  next_sowing_event->begin_sync.set(computed_sowing_date);
                  next_sowing_event->begin_sync.sync_mode_labeled.set(ACTUAL_DATE_MODE);
                  sowing_operation->adjusted_for_weather_conditions = true;      //170220
                  computed_plantings.append(next_sowing_event);

   //std::clog << "planting adjusted:" << next_sowing_event->date.as_string() << std::endl;

                  next_sowing_event = dynamic_cast<Sowing_event *>
                     (plantings_fixed_or_computable.pop_first());
                  if (next_sowing_event)
                  {
                     sowing_operation = dynamic_cast<Sowing_operation *>         //170602
                        (next_sowing_event->get_operation());                    //170602
                     if (sowing_operation->plant_by_date)                        //170602
                     {  plant_by_date_actual.set_date32(sowing_operation->plant_by_date); //170602
                        plant_by_date_actual.inc_years(today.get_year());        //170602
                     } else plant_by_date_actual.clear();                        //170602
                     clear_window_date.set(next_sowing_event->date);
                     clear_window_date.dec_days(sowing_window_days_midpoint);    //170316brc
                  }
                  sowing_precipitation_window_meter.reset();
                  avg_air_temp_for_window.reset();
               }
               else
               {
                  // Need to explain that could not be accurately determined
                  // because weather data unavailable.
                  // This is not necessarily an error because we may be nearing
                  // the end of a simulation period so planting may not be
                  // relevent anyway.
               }
            } // else haven't reach sowing window time.
         } break;
         default :
         {  // The other sowing date mode events a simply added to the planting events
            sowing_operation->adjusted_for_weather_conditions = true;            //170220
            computed_plantings.append(next_sowing_event);
            next_sowing_event = dynamic_cast<Sowing_event *>
               (plantings_fixed_or_computable.pop_first());
            if (next_sowing_event)
            {  // The next sowinging event may be a computed date mode
               // So we have to clear the window
               sowing_operation = dynamic_cast<Sowing_operation *>
                     (next_sowing_event->get_operation());
               if (sowing_operation->plant_by_date)                              //170602
               {  plant_by_date_actual.set_date32(sowing_operation->plant_by_date); //170602
                  plant_by_date_actual.inc_years(today.get_year());              //170602
               } else plant_by_date_actual.clear();                              //170602
               clear_window_date.set(next_sowing_event->date);
               clear_window_date.dec_days(sowing_window_days_midpoint);          //170316brc
            }
         }
      }
      */
      weather.end_day();
   } // date loop
   weather.override_today(0); //go back to normal mode                           //170525
   computed_plantings_.transfer_all_from(computed_plantings);                         //180529
   return computed_plantings.count();
}
//_2016-07-07___________________________________________________________________

bool Rotation::start()                                             modification_
{
   //CORN::Bidirectional_list plantings_fixed_or_computable;
   render_planting_events
      (plantings_fixed_or_computable
      ,start_date.get_year(),stop_date.get_year(),cycle);
   /* now member
   CORN::Statistical_sample_with_dataset<float32,float32,float32>
         sowing_precipitation_window_meter;
   CORN::Statistical_sample_with_dataset<float32,float32,float32>
         avg_air_temp_for_window;
   */
   #define sowing_window_days 15
    /*int*/ sowing_window_days_midpoint = sowing_window_days / 2;                    //170316brc
   /*Sowing_event **/next_sowing_event = dynamic_cast<Sowing_event *>
      (plantings_fixed_or_computable.pop_first());
   if (!next_sowing_event) return false; // (rotation not loaded?)
   /*180529 Sowing_operation **/sowing_operation = dynamic_cast<Sowing_operation *>
         (next_sowing_event->get_operation());
   CORN::Date_clad_32 plant_by_date_actual(0);
   if (sowing_operation->plant_by_date)                                          //170602
   {  plant_by_date_actual.set_date32(sowing_operation->plant_by_date);          //170602
      plant_by_date_actual.inc_years(start_date.get_year()/*180529 start_year*/);//170602
   }
   //180529 now member CORN::Date_clad_32 clear_window_date(next_sowing_event->date);
   clear_window_date.set(next_sowing_event->date);                               //180529
   clear_window_date.dec_days(sowing_window_days_midpoint);                      //170316brc


   return true;
}
//_start____________________________________________________________2018-05-29_/

bool Rotation::process_day()                                       modification_
{

      if (today == clear_window_date)
      {
         sowing_precipitation_window_meter.reset();
         avg_air_temp_for_window.reset();
      }
      float32 precip = 0.0;                                                      //160726
      precip = weather_provider->precipitation_actual.get_m();
      sowing_precipitation_window_meter.append(precip);

      // See if there has been any appreciable preciptation in the last X days   //000330
      while (sowing_precipitation_window_meter.get_count()                       //141105
             > (Days)sowing_operation->delay_after_precip)
         sowing_precipitation_window_meter.remove_at(0);                         //141105
      bool warm_enough = true;
      nat8 window_size = 0;
      Sowing_date_mode planting_date_mode                                        //170331
         = sowing_operation->sowing_date_mode_labeled.get();
      if (plant_by_date_actual.get_date32() && (today >= plant_by_date_actual))  //170602
      {  // event may specify date to plant by (0 disables)
         next_sowing_event->date.set(today);                                     //170602
         planting_date_mode = FIXED_DATE;
      }
      switch (planting_date_mode)
      {
         case MIN_TEMP_REQ    :
         {
            float64 air_temp_avg = 0;
            air_temp_avg = weather_provider->air_temperature_avg.Celcius();
            avg_air_temp_for_window.append(air_temp_avg);
            while ((window_size = avg_air_temp_for_window.get_count()) > (Days)sowing_window_days) // 15//160708
               avg_air_temp_for_window.remove_at(0);
            float64 avg_temps = avg_air_temp_for_window.get_mean();              //131219
            warm_enough = (avg_temps >= sowing_operation->sowing_avg_temp);
           //NYI  bool appreciable_rain_in_X_days = sowing_precipitation_window_meter.provide_max() > appreciable_precip_m; //141105
            if ((today >= next_sowing_event->date)
                && (window_size == sowing_window_days)) // 15
            {
                /* NYI && appreciable_rain_in_X_days*/
               if (warm_enough)
               {  CORN::Date_clad_32 computed_sowing_date(today);
                  computed_sowing_date.dec_days(sowing_window_days_midpoint);    //170316brc
                  next_sowing_event->date.set(computed_sowing_date);
                  //next_sowing_event->sync_mode_labeled.set(ACTUAL_DATE_MODE);
                  next_sowing_event->begin_sync.set(computed_sowing_date);
                  next_sowing_event->begin_sync.sync_mode_labeled.set(ACTUAL_DATE_MODE);
                  sowing_operation->adjusted_for_weather_conditions = true;      //170220
                  computed_plantings.append(next_sowing_event);

   //std::clog << "planting adjusted:" << next_sowing_event->date.as_string() << std::endl;

                  next_sowing_event = dynamic_cast<Sowing_event *>
                     (plantings_fixed_or_computable.pop_first());
                  if (next_sowing_event)
                  {
                     sowing_operation = dynamic_cast<Sowing_operation *>         //170602
                        (next_sowing_event->get_operation());                    //170602
                     if (sowing_operation->plant_by_date)                        //170602
                     {  plant_by_date_actual.set_date32(sowing_operation->plant_by_date); //170602
                        plant_by_date_actual.inc_years(today.get_year());        //170602
                     } else plant_by_date_actual.clear();                        //170602
                     clear_window_date.set(next_sowing_event->date);
                     clear_window_date.dec_days(sowing_window_days_midpoint);    //170316brc
                  }
                  sowing_precipitation_window_meter.reset();
                  avg_air_temp_for_window.reset();
               }
               else
               {
                  // Need to explain that could not be accurately determined
                  // because weather data unavailable.
                  // This is not necessarily an error because we may be nearing
                  // the end of a simulation period so planting may not be
                  // relevent anyway.
               }
            } // else haven't reach sowing window time.
         } break;
         default :
         {  // The other sowing date mode events a simply added to the planting events
            sowing_operation->adjusted_for_weather_conditions = true;            //170220
            computed_plantings.append(next_sowing_event);
            next_sowing_event = dynamic_cast<Sowing_event *>
               (plantings_fixed_or_computable.pop_first());
            if (next_sowing_event)
            {  // The next sowinging event may be a computed date mode
               // So we have to clear the window
               sowing_operation = dynamic_cast<Sowing_operation *>
                     (next_sowing_event->get_operation());
               if (sowing_operation->plant_by_date)                              //170602
               {  plant_by_date_actual.set_date32(sowing_operation->plant_by_date); //170602
                  plant_by_date_actual.inc_years(today.get_year());              //170602
               } else plant_by_date_actual.clear();                              //170602
               clear_window_date.set(next_sowing_event->date);
               clear_window_date.dec_days(sowing_window_days_midpoint);          //170316brc
            }
         }
      }
   return true;
}

//_process_day______________________________________________________2018-05-29_/
#ifndef PLANTING_SCHEDULER
bool Rotation::resolve_crop_and_management
(CropSyst::Sowing_operation &sow_op
,const CORN::OS::Directory_name &rotation_dir)                             const
{
   CORN::OS::File_name_concrete crop_filename_unresolved(sow_op.crop_filename.c_str());
   CORN::OS::Directory_entry_name *crop_filename_reset
      = CORN::OS::file_system_engine.render_resolved_absolute_DEN
         (CORN::OS::Directory_entry_name_concrete(sow_op.crop_filename.c_str()),rotation_dir);
   if (crop_filename_reset)
      sow_op.crop_filename.set_DEN(*crop_filename_reset);
   delete crop_filename_reset;
   CORN::OS::Directory_entry_name *management_filename_reset
      = CORN::OS::file_system_engine.render_resolved_absolute_DEN
         (CORN::OS::Directory_entry_name_concrete(sow_op.management_filename.c_str()),rotation_dir);
   if (management_filename_reset)
      sow_op.management_filename.set_DEN(*management_filename_reset);
   delete management_filename_reset;
   return true;
}
//_2017-09-29___________________________________________________________________

Rotations::Rotations()
: CORN::Unidirectional_list(true) // unique
{}
//_2016-07-07___________________________________________________________________
/*180529 const */Rotation *Rotations::provide
(const CORN::OS::File_name &rotation_filename
,bool rotation_cycling_enabled)
{  Rotation *existing_rotation = dynamic_cast<Rotation *>
      (find_wstring(rotation_filename.w_str()));
   if (!existing_rotation)
   {
      if (rotation_filename.is_valid())                                          //180201
      {

//std::clog << "rot file:" << rotation_filename.c_str() << std::endl;

         existing_rotation = new Rotation(rotation_filename);
         take(existing_rotation);
      }
   }
   return existing_rotation; // NYI
}
//_2016-07-07___________________________________________________________________
Rotations rotations_global;
#endif
} // namespace CropSyst
