#ifndef GIS_simulationH
#define GIS_simulationH

#include "project/multirun/batchrun.h"
#include "project/GIS/GIS_params.h"
#include "CS_Suite\CropSyst\PAT_run\PAT_tally_engine.h"

// forward declarations
class Avg_prob_map_tallier;
class CropSyst::Project_editor_parameters;
namespace CropSyst                                                               //120112
{  class Scenario_directory;                                                     //120112
   class Simulation_override_record;
}
/* Obsolete STATSGO1 is no longer availabled
namespace STATSGO                                                                //050822
{  class Database;
}
*/
//______________________________________________________________________________
class GIS_simulation
: public CropSyst_batch_run                                                      //060710
{
 private:
   const //140214 not sure yet if can be const
      GIS_Project_parameters        &GIS_project_params;
//131008 unused    TGIS_run_form                 *GIS_run_form;
   /* STATSGO1 is no longer available, may want to implement STATSGO2
   STATSGO::Database             *STATSGO_database;  // Will be instanciated if STATSGO is used //050729
   */
/*140222 moved to PAT_tally_engine
   bool                          aggregate_all_sequences_mode; // currently we determine this based on if there are not sequence numbers in the PAT, but it could be a check box or something the the project GIS editor.
   const CORN::OS::File_name &template_file_name;                                     //101129
*/
 private: // The following are for Donatelli analysis
   Polygon_attribute_table *coverage_PAT;
 public:
   GIS_simulation
      (
      const //140214 not sure yet if can be const
         CropSyst::Project_editor_parameters             &_project
      #ifdef OLD_GEN_SCENARIOS_DIR
      // project directory is no longer needed because we now
      // initiate simulation run from the (template) scenario *directory)
      ,CropSyst::Project_directory        &_project_directory                         //140203_060706
      #else
      ,
      const //140214 not sure yet if can be const
         CropSyst::Scenario_directory       &_scenario_directory
      #endif
      );
   virtual ~GIS_simulation();                                                    //050729
   virtual Simulation_run_result run();
   virtual const CORN::OS::Directory_name& get_generated_scenarios_directory_qual();
#ifdef MOVED
// moved to PAT_tally_engine
 private:
   Unidirectional_list unique_sim_combinations;  // This does not need storing in the file
   Unidirectional_list duplicate_sim_combinations;                               //050705
#endif
 private:
   nat32 generate_scenarios();
   nat32 run_scenarios();
   nat32 aggregate_scenarios();                                                  //050927
/*140222 moved to PAT_tally_engine
   virtual nat32 tally_scenarios();                                              //050629
   void setup_tally_files(bool equivalence_optimization);
*/
   Validation_status parameterize_and_run_scenario // was simulation_run was simulation_run_tally 990611
      (const CORN::File_name &simulation_model
      ,const CORN::File_name &template_filename
      ,const CORN::File_name &override_database_filename
      ,nat32 override_record_number
      ,nat32 scenario_ID                                                         //050919
      ,nat32 same_as_record_num
      ,sint32 polygon_ID     // signed because negative value indicates offsite
      ,sint32 same_as_scenario_ID                                                //050919
      ,bool equivalence_optimization);
/*140222 moved to PAT_tally_engine
   Validation_status tally_scenario_results                                      //990611
      (nat32 scenario_ID                                                         //050919
      ,nat32 same_as_record_num
      ,int32 polygon_ID      // signed because negative value indicates offsite
      ,int32 same_as_scenario_ID                                                //050919
      ,bool equivalence_optimization);
*/
 private:
 /*140222 moved
   void clean_up_tally_files
      (bool equivalence_optimization);                                           //001002
*/
   virtual void clean_up_scenario(CropSyst::Scenario_directory &polygon_scenario_directory); //050920
 private:
   int add_table_line
      (CropSyst::Simulation_override_record *sim_comb
      ,int32 &same_as_scenario_ID);                                              //050919
   uint8 get_range_of_MUID_sequence_numbers(const char *MUID);                   //050720
      // Returns the number of sequence numbers (highest sequence number) for this MUID.
      // Returns 0 if this MUID is not found or no sequences found.
      // Presume that if there is a sequence returned the lowest is always 1.
   bool check_run_STATGO_scenario(const char *MUID, int seq_num,std::string/*131007 CORN::Ustring*/ &COMPNAME) const; //050819
      // This also returns the COMPNAME since we have conveniently read the component
   /* STATSGO1 is no longer available, may want to implement STATSGO2
   STATSGO::Database *provide_STATSGO_database();                                //050819
   */
   Polygon_attribute_table *provide_coverage_PAT();
};
//______________________________________________________________________________
#endif

