#include "CS_simulation_rotator.h"
#ifdef OLD_ROTATION
#include "corn/data_source/vv_file.h"
#endif
#include "crop/crop_interfaced.h"
#include "crop/phenology_interface.h"
#include "common/weather/weather.h"
#include "soil.h"
#include "CS_suite/UED/aggregation/aggregate_UEDs.h"
#include "csvc.h"
#include <assert.h>
#include <iostream>
#include "CS_suite/observation/CS_desired_vars.h"
#include "cs_scenario_directory.h"
#include "rotation.h"
//______________________________________________________________________________
extern CORN::Parameter_properties_literal PP_crop_biomass_yield;
extern CORN::Parameter_properties_literal PP_crop_biomass_useful;
extern CORN::Parameter_properties_literal PP_crop_biomass_disposal;
extern CORN::Parameter_properties_literal PP_crop_biomass_produced_above_ground;
extern CORN::Parameter_properties_literal PP_crop_canopy_N_mass;
//______________________________________________________________________________
bool prevent_multiple_harvests_in_same_day;                                      //141230
namespace CS
{
//______________________________________________________________________________
Cycler::Cycler
(Command_options_data_source    &command_line_options_                           //160829
,const CS::Identification       &ID_
,bool                            CPF_mode_)                                      //151026
: Simulation_engine     (command_line_options_)                                  //160829_160222
, ID                    (ID_)                                                    //151028
, template_scenario     (CPF_mode_)                                              //150513
, geolocation           ()
, weather_DB_daily      (0)                                                      //160708
, meteorological_ref    (0)                                                      //160525
, land_unit_simulations (sub_elements)                                           //160304_160222
{}
//_Cycler:constructor_______________________________________________2013-06-20_/
bool Cycler::initialize()                                       initialization_
{
   bool initialized = true;                                                      //150209_140722
   if (verbose) //creation
   {
      std::clog
         << "info: creating directory" << std::endl
         << "dir=  " << get_output_directory_name().c_str() << std::endl;
   }
   CORN::date32 hold_today(today_raw);                                           //170525_170220
   CORN::OS::file_system_engine.provide_directory(get_output_directory_name());
   const CORN::OS::File_name &template_rotation_file_name
      = provide_template_rotation_file_name();

   /*180529 const*/ CropSyst::Rotation *rotation // There is not necessarily a rotation
      = CropSyst::rotations_global.provide
      (template_rotation_file_name,is_rotation_cycling_enabled());               //160708
   nat8 cycles = 1;                                                              //180201
   nat16 computed_planting_count = 0;
   if (rotation) // There is not necessarily a rotation                          //180201
   {  computed_planting_count                                                    //180522
      = rotation->count_computed_plantings();                                    //170310
      cycles = is_rotation_cycling_enabled() ? rotation->get_cycles() : 1;       //170211
   }
   nat8 cycle = 0;
   do
   {  Cycled_scenario_simulation *cycled_scenario = render_scenario_simulation(cycle);
      if (!cycled_scenario)
      {  std::clog << "Cycler::initialize failed to render shifted_scenario"<< std::endl;
         return false;                                                           //151227
      }
      land_unit_simulations.append(cycled_scenario);
      if (computed_planting_count && rotation)                                   //180201
      {  CORN::Unidirectional_list cycled_plantings;
         if (verbose)   // level or program-entry
            std::clog << "Rendering planting events adjusted for weather conditions cycle=" << (int)cycle << std::endl;
            // Render planting events uses today for the iteration
            // we need to restore after rendering.
         rotation->render_planting_events_adjusted_for_weather_conditions
            (provide_weather_database_daily_with_meteorology()                   //170311
            ,cycled_plantings
            ,ref_start_date().get_year()
            ,ref_stop_date().get_year()
            ,cycle);
         CropSyst::Sowing_event *cycled_planting = 0;
         while ((cycled_planting = dynamic_cast<CropSyst::Sowing_event *>(cycled_plantings.pop_at_head())))
         {  cycled_scenario->scenario_event_list.append(cycled_planting);
            CropSyst::Sowing_operation *sow_op = cycled_planting->sowing_op;
            cycled_scenario->schedule_planting_event
               (cycled_planting->date.get_date32(),*sow_op,cycled_planting->ID.c_str());
            know_sowing_for_phenology_adjustment(*sow_op,cycled_planting->date.get_date32());
         }
      } else cycled_scenario->CropSyst:: LAND_UNIT_SIMULATION_SUPERCLASS::setup_cropping_system();
      cycle ++;                                                                  //170311
   } while (cycle < cycles);                                                     //170310
   today_driving_raw = hold_today;                                                //170525170220
   initialized &= Simulation_engine::initialize();                               //150731
   if (!initialized) std::clog << "Cycler::initialize Simulation_engine::initialize failed" << std::endl;
   return initialized;
}
//_initialize__________________________________________________________________/
bool Cycler::stop()                                               modification_
{  bool stopped = true;
   stopped &= Simulation_engine::stop();
      // Engine must be stopped first because we need UED outputs to be written.
   #ifdef AGGREGATE_CYCLES_SEASONAL
   CORN::OS::File_name_concrete aggregated_season_UED_filename
      (get_output_directory_name(),"season.UED");                                //140119
   UED::Aggregator season_aggregator(UED::Aggregator::merge
      , aggregated_season_UED_filename.c_str(),true);                            //140119_140829 now writing 16bit floats
   #if (CROPSYST_VERSION < 5)
   FOR_EACH_IN(scenario_sim,Rotated_scenario_simulation,land_unit_simulations,each_rotated_scenario_simulation)
   {
      if (scenario_sim->season_UED_db)
         season_aggregator.append_source(*scenario_sim->season_UED_db);          //140119
   } FOR_EACH_END(each_rotated_scenario_simulation)
   #endif
   // else each rotated cycle has its own enumerated directory for the outputs
   stopped &= season_aggregator.finalize();
   #endif
   //NYN    CORN::OS::File_name_concrete harvest_UED_filename(output_dir,"harvest.UED");
   CORN::OS::File_name_concrete aggregated_annual_UED_filename
      (get_output_directory_name(),"annual_aggr.UED");                           //140119
   //NYN UED::Aggregator harvest_aggregator
   //    (UED::Aggregator::merge,harvest_UED_filename.);
   #if (CROPSYST_VERSION < 5)
   UED::Aggregator annual_aggregator
      (UED::Aggregator::average, aggregated_annual_UED_filename.c_str(),true);   //140119_140829 now writing 16bit floats
   FOR_EACH_IN(scenario_sim,Rotated_scenario_simulation,land_unit_simulations
      ,each_rotated_scenario_simulation)
   {
      CORN::OS::File_name_concrete cycle_annual_UED
         (scenario_sim->get_output_directory_name(),"annual.UED");
      annual_aggregator.append_source_file(cycle_annual_UED.c_str());
   } FOR_EACH_END(each_rotated_scenario_simulation)
   stopped &= annual_aggregator.finalize();
   #endif
   return stopped;                                                               //160308_140728
}
//_stop_____________________________________________________________2013-10-30_/
bool Cycler::end_year()                                           modification_
{  bool ended = Simulation_engine::end_year();                                   //170528_151218
   #ifndef REACCH_VERSION
   // I think REACCH was having a problem because multiple years in one record
   #if (CROPSYST_PROPER==4)

   // This may be applicable to all CROPSYST_PROPER versions but need to check

   // Don't need to keep lots weather data in memory
   CORN::Date_clad_32 over_a_year_ago                                            //141103
      ((CORN::Year)(today.get_year()-1),(CORN::DOY)1);
   weather->done_with_dates_before(over_a_year_ago);                             //141103
   #endif
   #endif
   /*170528 must be done first, because subelements could potentially be using
      previous year
   ended &= Simulation_engine::end_year();                                       //140105
   */
   return ended;
}
//_end_year_____________________________________________________________________
char buffer_numeric_conversion[20];
//______________________________________________________________________________
Cycler::Cycled_scenario_simulation::Cycled_scenario_simulation                   //180106
(const CS::Identification &LBF_ID_                                               //151026
,nat32                     cycle_shift_                                          //151026
,CropSyst::Scenario  &scenario_control_and_model_options_
,const CORN::date32 &today_                                                      //170525
,const Geocoordinate &geocoordinate_                                             //151116
,const Land_unit_meteorological &meteorology_
,const CropSyst::Scenario_directory *scenario_directory_
,bool want_detailed_output_
,const CORN::OS::Directory_name &rotator_output_directory_                       //160311
,CS::Desired_variables *desired_variables_daily_)                                //170227
: CropSyst::LAND_UNIT_SIMULATION_SUPERCLASS
   (LBF_ID_
   ,cycle_shift_                                                                 //151026
   ,scenario_control_and_model_options_
   ,today_
   ,geocoordinate_                                                               //151116
   ,meteorology_
   #if (CS_VERSION==4)
   // Need to remove this replace with explainations
   ,event_log_currently_unused
   #endif
   ,scenario_directory_
   #if (LAND_UNIT_SIMULATION_SUPERCLASS==Land_unit_with_output)
   ,desired_variables_daily_                                                     //170225_150225
   #endif
   )
, rotator_output_directory(rotator_output_directory_)                            //160311
, provided_cycle_directory(0)                                                    //160310
{}
//_Cycled_scenario_simulation:constructor______________________________________/
const CORN::OS::Directory_name &Cycler::Cycled_scenario_simulation::
provide_cycle_directory()                                             provision_ //160310
{  if (!provided_cycle_directory)
      provided_cycle_directory = new CORN::OS::Directory_name_concrete
         (rotator_output_directory
         ,CORN::nat32_to_cstr(cycle_shift,buffer_numeric_conversion,10));
   CORN::OS::file_system_engine.provide_directory(*provided_cycle_directory);
   return *provided_cycle_directory;
}
//_provide_cycle_directory__________________________________________2016-03-11_/
bool Cycler::Cycled_scenario_simulation::setup_cropping_system()
{  // We disable the cropping system mode because we generate from
   // rotation template which sets up the cropping system
   scenario_control_and_model_options.cropping_system_mode_labeled.set(rotation_cropping_system);
   return true;
}
//_setup_cropping_system________________________________________________________
bool Cycler::Cycled_scenario_simulation::end_day()               modification_
{  perform_triggered_synchronizations_today(); // triggered sync may need to be in process method as it is with
   return CropSyst::  LAND_UNIT_SIMULATION_SUPERCLASS::end_day();
   // Not sure if I should commit before or after Land_unit_simulation::end_day
   // after because there may be last minute cleanup and variables to be settled
   // however before because end day might
}
//_end_day__________________________________________________________2013-08-02_/
const CORN::OS::Directory_name &Cycler::Cycled_scenario_simulation
::get_output_directory_name()                                              const
{ return provide_cycle_directory();                                              //160311
}
//_Cycled_scenario_simulation_______________________________________2015-01-08_/
bool Cycler::start_day()
{  prevent_multiple_harvests_in_same_day = false;                                //141231
   // weather_DB_daily currently is not on elements list
   return weather_DB_daily->start_day()                                          //160802
      && Simulation_engine::start_day();
}
//_start_day________________________________________________________2013-08-30_/
bool Cycler::end_day()
{  return
      // weather_DB_daily currently is not on elements list
       weather_DB_daily->end_day()                                               //160802
   && Simulation_engine::end_day();
}
//_end_day__________________________________________________________2013-08-30_/
modifiable_ Cycler::Cycled_scenario_simulation *Cycler::
render_scenario_simulation(nat32 cycle_shift_)                      //rendition_
{
   const CropSyst::Scenario_directory *scenario_directory                        //160530
      = provide_scenario_directory();
   return new Cycler::Cycled_scenario_simulation
      (ID
      ,cycle_shift_
      ,template_scenario
      ,today_raw                                                                 //170525
      ,geolocation
      ,*meteorological_ref                                                       //160525
      ,scenario_directory
      ,true // CropSyst Proper and OFoot we want_detail_output
      ,get_output_directory_name()
      ,desired_variables_daily);                                                 //170225
}
//_render_scenario_simulation_______________________________________2016-05-14_/
CS::Weather_database_daily &Cycler::provide_weather_database_daily() provision_
{  if (!weather_DB_daily)
   {
      CORN::date32 actual_preclude_date                                          //170310
      = (template_scenario.weather_preclude_date > 1000000)
      ? template_scenario.weather_preclude_date
      : (template_scenario.weather_preclude_date)                                //170420
        ? template_scenario.start_date.get_year() * 1000
         + template_scenario.weather_preclude_date
        : 0 ;                                                                    //170420
      weather_DB_daily = new Weather_database_daily_UED
           (template_scenario.weather_filename,today_raw                         //170525
           ,template_scenario.extend_available_weather
           ,template_scenario.substitute_year_base                               //170323
           ,template_scenario.start_date.get_year()                              //170331
           ,template_scenario.substitute_year_offset                             //161207
           ,actual_preclude_date);                                               //170310
   }
   return *weather_DB_daily;
}
//_provide_weather_database_daily___________________________________2016-07-29_/
CS::Weather_database_daily &Cycler::provide_weather_database_daily_with_meteorology() provision_
{  provide_weather_database_daily();
   weather_DB_daily->know_weather_provider(&(meteorological_ref->mod_weather_provider()));
   return *weather_DB_daily;
}
//_provide_weather_database_daily_with_meteorology__________________2017-03-11_/
} //namespace CS

