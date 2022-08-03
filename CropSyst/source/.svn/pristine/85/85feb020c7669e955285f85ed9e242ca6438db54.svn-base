#ifndef CropSyst_engine_V5H
#define CropSyst_engine_V5H
#include "CS_suite/simulation/CS_simulation_rotator.h"
#include "arguments_CropSyst.h"
/*170225 moved to CS::Simulation_engine
#include "CS_suite/observation/CS_desired_vars.h"
*/
#include "common/weather/daily.h"
#include "CS_suite/file_system/CS_database_directory.h"
#include "CS_suite/parameters/param_stores.h"
#include "corn/data_source/vv_file.h"
//______________________________________________________________________________
namespace CS { class Weather_daily; }
class ET_Reference_calculator;
//______________________________________________________________________________
namespace CropSyst {
namespace version5 {
//______________________________________________________________________________
class Simulation_engine
: public extends_ CS::Cycler
{
 protected:                                                                      //160908
   std::string                          model_name;
   provided_ CORN::OS::Directory_name_concrete  *output_dir;
   std::wstring                      control_filename_extension;                 //160308
   std::wstring                      scenario_filename_extension;                //160219
   CS::Identification ID;                                                        //160513
   CropSyst::Arguments arguments;                                                //160513
/*Currently template_scenario is in CS::Cycler because is currently CropSyst specific
  but it should be here as this Simulation_engine is actually CropSyst specific
 protected:
   CropSyst::Scenario template_scenario;                                         //160514
*/
 private:
   // These filenames are temporary
   // eventually in V5 we will have parameter (file) composition
   // When implemented, parameters will be loaded from accessable
   // data sources (which may be parameter files).
   // Once implemented these filename will be obsolete, and
   // at that time I will probably also migrate to YAML document format
   // see composition.html documentation.
   provided_ CORN::OS::File_name_concrete *template_rotation_file_name;
      // The template rotation filename is unsed for OFoot.
      // It is not currently used by CropSyst proper
 protected:
   CS::Land_unit_meteorological  *meteorology;                                   //151023
 private:
   CS::Weather_daily *weather_daily;                                             //160731
 protected: // Databases and stores are optional
   CS::Parameter_stores  *stores;                                                //160916
 public: // structors
   Simulation_engine
      (Command_options_data_source &command_line_options_ );                     //160902_160513
   virtual ~Simulation_engine();
 public: // CS::Simulation_engine implementations
   virtual bool initialize()                                     initialization_;//160515
   virtual bool start()                                            modification_;//160731
   //NYN virtual bool process_day()                                      modification_;//160515
 public:
   virtual bool is_detailed_output_cell(const CS::Identification &ID) affirmation_ { return false; }
      // is_detailed_output_cell is used for debugging.
   virtual const CORN::OS::Directory_name &provide_scenario_directory_name() provision_;
   virtual const CORN::OS::Directory_name &get_output_directory_name()     const;
   inline virtual const std::string &get_model_name()                      const //120925
      { return model_name; }
   virtual const CORN::OS::File_name &provide_template_rotation_file_name() provision_;
      // provide_template_rotation_file_name is temporary,
      // in V5 there will be parameter file discovery and composition
   inline virtual const std::wstring &get_scenario_file_name_extension()   const //160219
      { return scenario_filename_extension; }
   inline virtual modifiable_ CropSyst::Arguments *mod_arguments() modification_ //180118
      { return &arguments; } //180118 was get_arguments()
   inline virtual const CropSyst::Arguments *ref_arguments()               const //180118
      { return &arguments; }
   virtual const CropSyst::Scenario_directory *provide_scenario_directory() provision_;
 public: // eventually may move stores to CS::Simulation_engine
   Parameter_stores  &provide_stores();
   inline virtual bool is_rotation_cycling_enabled()                affirmation_ //161207
      { return template_scenario.rotation_cycling; }

 protected:
   CORN::OS::File_name *find_equilibrated                                        //170421
      (const std::string &equilibration
      ,const char *equilibrated_filename_unqual) rendition_;
 protected:
   nat16 desire_AgMIP_variables()                               initialization_; //160312
};
//_2015-10-08___________________________________________________________________
}} // name CropSyst::V5
#endif
