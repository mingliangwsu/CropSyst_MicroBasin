#include "MicroBasin_engine.h"
namespace CropSyst
{
//______________________________________________________________________________
MicroBasin_Engine::MicroBasin_Engine
(const CORN::OS::Directory_name_concrete &_scenario_directory)
: CS::Simulation_engine (simulation_control,0)
, CS::Land_unit         (0) // Not currently using ID
, cell_scenario         (&scenario_directory)
, simulation_control    (5,0,0)
, scenario_directory    (_scenario_directory,false) // scenario directory should already exist
, model_name            ("MicroBasin_CS5")
, cells                 (sub_elements)
{
}
//______________________________________________________________________________
bool MicroBasin_Engine::start()                                    modification_
{

   // load up the cells
   for (int c = 0; c < 100; c++) // simple test
   {
      // identify the soil for the cell
      cells.append(new Cell
         (c                        //cell ID
         ,cell_scenario
         ,today
         ,&scenario_directory));
   }
   return true;
}
//______________________________________________________________________________
bool MicroBasin_Engine::process_day()                              modification_ //150611RLN
{  bool processed = true;
   for (CORN::Hour hour = 0; hour < 24; hour++)
   {
      #pragma omp parallel for
      FOR_EACH_IN(cell,Cell,cells,each_cell)
      {
         cell->process_hourly(hour);
      } FOR_EACH_END(each_cell)
      // end parallel;
      lateral_flow();
   }
   processed &= CS::Simulation_engine::process_day();                            //150611RLN
      // should be looping through the cells in parallel
   return processed;
}
//______________________________________________________________________________
bool MicroBasin_Engine::lateral_flow()                             modification_
{
   // NYI
   return true;
}
//______________________________________________________________________________
//______________________________________________________________________________
/* NYN
MicroBasin_Engine::Scenario_directory::Scenario_directory(const CORN::OS::Directory_name &_scenario_directory)
:  CropSyst::Scenario_directory
   (_scenario_directory
   ,false) //should already exist at this point
{
}
*/
//______________________________________________________________________________
//______________________________________________________________________________
MicroBasin_Engine::Simulation_control::Simulation_control
(nat8  major,nat8  release,nat8  minor)
: CS::Simulation_control(major,release,minor)
{

}
//______________________________________________________________________________
//______________________________________________________________________________
char cell_ID_str_buffer[256];

MicroBasin_Engine::Cell::Cell
   (sint32                        _LBF_ID
   ,CropSyst::Scenario           &_scenario_control_and_model_options
   ,const CORN::Date             &_today
   ,Scenario_directory           *_scenario_directory)
:Land_unit_simulation
   (_LBF_ID
   ,_scenario_control_and_model_options
   ,_today
   ,event_log
   ,_scenario_directory)
, output_directory_name(*_scenario_directory,CORN::int32_to_cstr(_LBF_ID,cell_ID_str_buffer,10))
{}
//______________________________________________________________________________
bool MicroBasin_Engine::Cell::process_hourly(CORN::Hour hour)
{
   //NYI
   return true;
}
//______________________________________________________________________________
} //namespace CropSyst

