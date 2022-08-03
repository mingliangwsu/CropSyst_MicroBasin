#ifndef CROPSYST_MULTIRUN_H
#define CROPSYST_MULTIRUN_H
#include "CS_suite/CropSyst/CropSyst_directory.h"
//#include "CORN/OS/directory_entry_name_concrete.h"
#include "common/simulation/exit_codes.h"

class TMulti_run_form;

namespace CropSyst
{
   #ifdef OLD_GEN_SCENARIOS_DIR
   class Project_directory;                                                      //140203
   #else
   class Scenario_directory;                                                     //140203
   #endif
   class Project_editor_parameters;                                        //070921 CropSyst_project;
}
//class TForm;

// This class is used by CropSyst suite modules that perform simulation numerous simulation runs
// I.e.  GIS simulation, Crop production function, grazing optimization.
// This interface controls the runs and updates the status.
//______________________________________________________________________________
class CropSyst_multirun
{public:
   const //140214 not sure yet if can be const
      CropSyst::Scenario_directory       &scenario_directory;
 public:
    const //140214 not sure yet if can be const
   CropSyst::Project_editor_parameters  &project_parameters;
 protected:
   TMulti_run_form *run_form;  // pointer to run form so we can update the status
 public: // for parameter editor binding
   bool run_scenario_minimized;
   bool clear_old_scenarios;
   bool prompt_continue;
public:
   CropSyst_multirun
      (
         const //140214 not sure yet if can be const
      CropSyst::Project_editor_parameters& _project
      #ifdef OLD_GEN_SCENARIOS_DIR
      ,const CropSyst::Project_directory&  _project_directory
      #else
     , const //140214 not sure yet if can be const
      CropSyst::Scenario_directory       &scenario_directory
      #endif
      );                  //101118

   void set_run_form(TMulti_run_form* _run_form);
   virtual Simulation_run_result run() = 0;
   virtual const CORN::OS::Directory_name& /*140203 Smart_directory_name& */ get_generated_scenarios_directory_qual() = 0;

   const CORN::OS::File_name &get_generate_scenarios_log()                 const;//140214
   virtual bool was_launched_by_CS_explorer()                              const;//101116
};
//______________________________________________________________________________
#endif

