#ifndef carbon_sequestrationH
#define carbon_sequestrationH
#include "project/multirun/multirun.h"
//140210 #include "project/scenario_generator.h"
#include "Project/Optimization/carbon_sequestration/carbon_sequestration.h"
#include "Project/Optimization/carbon_sequestration/carbon_sequestration_results.h"
class Carbon_sequestration_optimization_parameters;
class CropSyst_project_editor_parameters;
namespace CropSyst
{
#if (CS_VERSION==5)
140214 continue here optimization is now going to be specific to scenario
#endif
   class Project_directory;                                            //140203
}
//140203 class CropSyst_project_directory;
class TGrazing_run_form;
//______________________________________________________________________________
class Carbon_sequestration_optimization
: public CropSyst_multirun
/*140210  Scenario generator is obsolete, now generated
scenarios are to be created in subdirectories of the template (target)
scenario, CropSyst searchs up the path to find the template which is loaded
first
, public Scenario_generator
*/
{private:
   CropSyst_project_editor_parameters  &project; // Will have  Carbon_sequestration_optimization_parameters
   CropSyst::Project_directory          &project_directory;
   TGrazing_run_form                   *grazing_run_form;
 public:
   Carbon_sequestration_optimization
      (CropSyst_project_editor_parameters             &_project
      ,CropSyst::Project_directory   &_project_directory                         //140203
      ,TGrazing_run_form            *_grazing_run_form);
   virtual Simulation_run_result run();
 private:
   void setup_scenario(int16 herd_size,int16 plots,int16 days_on_field,int16 plot,bool replace_existing_scenario);
   inline virtual const CORN::OS::Directory_name& get_generated_scenarios_directory_qual() { return generation_directory_qual; };
   int16 generate_scenarios();
   int16 run_scenarios();
};
//______________________________________________________________________________
#endif
