#ifndef scenario_generatorH
#define scenario_generatorH

// This class is used by CropSyst projects to generate scenarios
// and manage generated scenario input and output files
// for CropSyst projects such as optimization, ArcCS, Watershed etc..

// A directory will be created in the project directory to store
// generated scenarios and related input and output files.
// The generated generation directory may have its own database directory for
// parameter files generated for the model.

// Generally the active scenario is used as a template to generate
//

//140203 #include "database_dir.h"
#include "CS_Suite/file_system/database_directory.h"
#include "common/simulation/exit_codes.h"
//______________________________________________________________________________
class Scenario_generator
{
protected:
   CORN::OS::Directory_name_concrete generation_directory_qual;
   // This is the name of the directory to store the generated scenarios
   // For GIS function this used to be "Generated scenarios" in the Project directory
   // This is now moved to the directory GIS subdirectory of the template scenario
public:
   Scenario_generator(const char *_generator_directory_qual);
   CORN::OS::Directory_name *                                                    //140210
   generate_scenario
      (const char *scenario_name // unqualified
      ,CORN::OS::File_name &template_scenario_name) rendition_;
        // template is either fully qualified or relative to

   // This copies the template_scenario to the new generated scenario_name
   // in the generation directory.
   // Returns the fully qualified scenario name.
   // In most cases the model override this method and will open the generated file,
   // make any necessary changes and save the generated file.
   // Changes parameter file names so they are fully qualified.

   Simulation_run_result run_scenario
      (const char *command_line_parameters
      ,bool minimize_window);
   // This will run the simulation, note that the project will be
   //
   // returns true if the simulation completed successfully.
   // Note that the simulation may abort under certain conditions

   inline virtual const CORN::OS::Directory_name &get_generated_scenarios_directory_qual() { return generation_directory_qual; }
};
//______________________________________________________________________________


#endif
