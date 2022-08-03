#  include "options.h"
#  include "corn/string/strconv.hpp"
#  include "cs_scenario.h"
#  include "mgmt_param.h"
#  include "rot_param.h"
#  include "common/simulation/event.h"
#  include "corn/data_source/vv_file.h"
#  include "corn/OS/os.h"
#  include "common/simulation/exit_codes.h"
#include "project/cs_project_editor_params.h"
#include "cs_project_directory.h"
#include "Project\Optimization\carbon_sequestration\carbon_sequestration.h"
#include "Project\Optimization\carbon_sequestration\carbon_sequestration_param.h"
#include "CropSyst\GUI\Builder\multi_runner\multi_run_frm.h"
#include "CropSyst\GUI\Builder\project_editor\optimizers\carbon_sequestration\carbon_sequestration_optimizer_form.h"

bool LADSS_mode; //  not used for this program
//______________________________________________________________________________
Carbon_sequestration_optimization::Carbon_sequestration_optimization
(CropSyst_project_editor_parameters &_project
,CropSyst_project_directory   &_project_directory
,TGrazing_run_form            *_grazing_run_form)
: CropSyst_multirun(_project,_project_directory)
, Scenario_generator(_project_directory.get_carbon_sequestration_optimization_dir_qual(true).c_str())   // "Carbon sequestration optimization"
, project(_project)
, project_directory(_project_directory)
, grazing_run_form(_grazing_run_form)
{
   //create the database management and rotation directories
   database_directory.provide_management_directory(true);
   database_directory.provide_rotation_directory(true);
};
//______________________________________________________________________________
void Carbon_sequestration_optimization::setup_scenario(int16 herd_size,int16 plots,int16 days_on_field,int16 plot,bool replace_existing_scenario)
{
   Carbon_sequestration_optimization_parameters &parameters = project.carbon_sequestration_optimization_parameters;

   std::string step_name;
   parameters.compose_scenario_name(step_name,herd_size,plots,days_on_field,plot);

   CORN::File_name scenario_filename_unqual(step_name,"csn");
   gen_scenario_filename_qual.set
      (generate_scenario(scenario_filename_unqual.c_str()
      ,project.get_active_filename().c_str()));

   CORN::File_name management_filename(step_name,"mgt");
   management_filename.set_path(database_directory.provide_management_directory(true));

   // Construct management
   Management_parameters generated_grazing_management;

   // Each iteration of the optimization would vary the management by adding grazing events
   // (there would always be a single last clipping termination event -- unless natural death is implemented (b above))

   float32 plot_acreage_ha = parameters.pasture_size_ha / (float32)plots;

   if (plots == 1)
   {  // For a single plot, we only need to generate a single repeated grazing event
      days_on_field =   parameters.grazing_season_duration;
   };

   int grazing_period = 1;
   int trampling_period = 1;
   int start_grazing_interval = CORN_max(days_on_field * (plots/*-1*/),1);
   int first_grazing_days_after_emerge_for_plot
   = parameters.begin_grazing_after_emergence_days + (plot-1) * days_on_field;

   int end_grazing_season_days_after_emergence =  parameters.begin_grazing_after_emergence_days + parameters.grazing_season_duration;


   for (int days_after_emergence = first_grazing_days_after_emerge_for_plot
       ;days_after_emergence < end_grazing_season_days_after_emergence
       ;days_after_emergence += start_grazing_interval)
   {
      { // grazing
      Harvest_or_clipping_operation *harvest_or_clipping_op = new Harvest_or_clipping_operation;
      harvest_or_clipping_op->terminate_crop = false;
      harvest_or_clipping_op->min_LAI_required = 0.0;
      // There will be a minumum biomass required for grazing (to prevent the animals from over eating the crop):
      harvest_or_clipping_op->min_biomass_required_kg_ha = 0.0;
      harvest_or_clipping_op->reserve_biomass_kg_ha = parameters.reserve_biomass_kg_ha;
      harvest_or_clipping_op->harvest_fate_mode_labeled.set(HARVEST_GRAZE);
      harvest_or_clipping_op->harvest_amount_mode_labeled = HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS;

      // The animal grazing demand specifies the removed fixed amount of biomass.
      // This amount is the animal unit dry matter requirements  6.25 kg/day
      // So given the pasture size (i.e. 150 ha) divided plots (times the number of animalsby the requirements


      float32 dry_biomass_requirement_kg =  herd_size * parameters.dry_matter_requirements_animal_units;

      // #animals * 6.25 gives requirements (kg) per day

      // The removed fixed amount of biomass (for each schedule and repeated event) is requirements/plot size.

      float32 grazed_amount_kg_ha = dry_biomass_requirement_kg / plot_acreage_ha;

      harvest_or_clipping_op->remove_amount_kg_ha = grazed_amount_kg_ha;
//050829obs      harvest_or_clipping_op->biomatter_fate_percents.remove_amount_kg_ha = grazed_amount_kg_ha;
      // Because we are using a fixed amount of biomass, we specify the removed amount
      // all goes to grazing
      harvest_or_clipping_op->biomass_fate_percents.remove_for_use = 0;
      harvest_or_clipping_op->biomass_fate_percents.remove_for_grazing = 100;
      harvest_or_clipping_op->biomass_fate_percents.remain_as_residue =  0;
      harvest_or_clipping_op->biomass_fate_percents.remove_for_disposal = 0;
      harvest_or_clipping_op->biomass_fate_percents.remain_as_dead = 0;
      harvest_or_clipping_op->biomass_fate_percents.remain_as_live = 0;
      harvest_or_clipping_op->biomass_fate_percents.remove_roots_to_dead_residue = 0;
      harvest_or_clipping_op->biomass_fate_percents.remain_roots_live = 100;
      harvest_or_clipping_op->biomass_fate_percents.remove_roots_as_loss = 0;
      harvest_or_clipping_op->biomass_fate_percents.return_as_manure= parameters.biomass_return_to_field;

      harvest_or_clipping_op->grazing_percent_N_as_OM = 50;
      harvest_or_clipping_op->grazing_percent_N_as_NH3 = 50;

      harvest_or_clipping_op->pasture_composition_legumes_percent = 15; // %

      Common_event *event = new Common_event(harvest_or_clipping_op,true);
      // The grazing events would be scheduled by the number of plots, times the duration.
      // Each grazing event would be repeated for the duration (# of days on the field).

      event->begin_sync.set_normal_growth_stage_offset(NGS_EMERGENCE, days_after_emergence);
      event->ID.assign(step_name);
      event->ID.append("_grazing_period=");
//      event->ID.append("_grazing_event=");


      char int_buf[10];
      event->ID.append(CORN_int16_to_str(grazing_period++,int_buf,10));

      event->operation_type_label = ""; // I think this may be obsolete
      event->operation_name/*_or_filename*/ = "";
      event->resource_set_ID = 0; // not needed

      // setup period for duration
      event->period = new  Common_event::Period;
         event->period->event_repetitions = days_on_field;
         event->period->repeat_event = true;
         event->period->interval_timestep_labeled.set(TS_DAY);
         event->period->interval = 1;
         event->period->end_sync.set_normal_growth_stage_offset(NGS_EMERGENCE, days_after_emergence + days_on_field);

      event->contingency_labeled.set(STOP_CONTIGENCY);
         // 180104 (NOT_VIABLE_CONTINGENCY); // ABORT_CONTIGENCY

//      event->enabled = true;  should be the default
      generated_grazing_management.harvest_or_clipping_operations.append(event);

      // event is relinquished to generated_grazing_management so we don't delete it here

      // enable the new management option to abort the simulation
      // if grazing (requirement exceeds crop biomatter).
      }

#ifdef PERMANENT_DISABLED
This generates too many operations and too many manure pools.
Also, we now save all the manure applications up to the the end of the season
and use injection to insure incorporation
      if (parameters.trampling)
      { // trampling

         Tillage_operation *trampling_op = new Tillage_operation;
         trampling_op->SCS_code= 255;
         trampling_op->terminate_crop = false;

         Common_event *event = new Common_event(trampling_op,true);
         // The grazing events would be scheduled by the number of plots, times the duration.
         // Each grazing event would be repeated for the duration (# of days on the field).

         event->begin_sync.set_normal_growth_stage_offset(NGS_EMERGENCE, days_after_emergence);

         event->operation_type_label = ""; // I think this may be obsolete
         event->operation_name_or_filename = "";
         event->resource_set_ID = 0; // not needed

         event->ID.assign(step_name);
         event->ID.append("_trampling_period=");
         char int_buf[10];
         event->ID.append(CORN_int16_to_str(trampling_period++,int_buf,10));


         // setup period for duration
         event->period = new  Common_event::Period;
            event->period->event_repetitions = days_on_field;
            event->period->repeat_event = true;
            event->period->interval_timestep_labeled.set(TS_DAY);
            event->period->interval = 1;
            event->period->end_sync.set_normal_growth_stage_offset(NGS_EMERGENCE, days_after_emergence + days_on_field -1);

         //      event->enabled = true;  should be the default
         generated_grazing_management.tillage_operations.append(event);
      };
#endif
   };
   // Weadd a termination operation
   // currently presuming the crop will naturally die.
   { // terminating event
      Harvest_or_clipping_operation *harvest_or_clipping_op = new Harvest_or_clipping_operation;
      harvest_or_clipping_op->terminate_crop = true;
      harvest_or_clipping_op->min_LAI_required = 0.0;
      // There will be a minumum biomass required for grazing (to prevent the animals from over eating the crop):
      harvest_or_clipping_op->min_biomass_required_kg_ha = 0.0;
      harvest_or_clipping_op->reserve_biomass_kg_ha = 0.0;
      harvest_or_clipping_op->harvest_fate_mode_labeled.set(DEFOLIATION);
//050829      harvest_or_clipping_op->biomass_fate_percents.remove_fixed_amount = false;
      harvest_or_clipping_op->harvest_amount_mode_labeled = HARVEST_CROP_PARAMETER_BASED;

      harvest_or_clipping_op->remove_amount_kg_ha = 0.0;
      // Because we are using a fixed amount of biomass, we specify the removed amount
      // all goes to grazing
      harvest_or_clipping_op->biomass_fate_percents.remove_for_use = 0;
      harvest_or_clipping_op->biomass_fate_percents.remove_for_grazing = 0;
      harvest_or_clipping_op->biomass_fate_percents.remain_as_residue =  0;
      harvest_or_clipping_op->biomass_fate_percents.remove_for_disposal = 0;
      harvest_or_clipping_op->biomass_fate_percents.remain_as_dead = 100;
      harvest_or_clipping_op->biomass_fate_percents.remain_as_live = 0;
      harvest_or_clipping_op->biomass_fate_percents.remove_roots_to_dead_residue = 100;
      harvest_or_clipping_op->biomass_fate_percents.remain_roots_live = 0;
      harvest_or_clipping_op->biomass_fate_percents.remove_roots_as_loss = 0;
      harvest_or_clipping_op->biomass_fate_percents.return_as_manure= 0.0;

      harvest_or_clipping_op->grazing_percent_N_as_OM = 50;
      harvest_or_clipping_op->grazing_percent_N_as_NH3 = 50;

      Common_event *event = new Common_event(harvest_or_clipping_op,true);
      // The grazing events would be scheduled by the number of plots, times the duration.
      // Each grazing event would be repeated for the duration (# of days on the field).

      event->begin_sync.set_normal_growth_stage_offset(NGS_EMERGENCE, end_grazing_season_days_after_emergence);

      event->ID.append("termination_event=1");
      event->operation_type_label = ""; // I think this may be obsolete
      event->operation_name/*_or_filename*/ = "";
      event->resource_set_ID = 0; // not needed

      generated_grazing_management.harvest_or_clipping_operations.append(event);
   };

      if (parameters.trampling)
      { // trampling  to incorporate surface plant residue

         Tillage_operation *trampling_op = new Tillage_operation;
         trampling_op->SCS_code= 255;
         trampling_op->terminate_crop = false;

         Common_event *event = new Common_event(trampling_op,true);
         // The grazing events would be scheduled by the number of plots, times the duration.
         // Each grazing event would be repeated for the duration (# of days on the field).

         event->begin_sync.set_normal_growth_stage_offset(NGS_EMERGENCE,end_grazing_season_days_after_emergence +1);

         event->operation_type_label = ""; // I think this may be obsolete
         event->operation_name/*_or_filename*/ = "";
         event->resource_set_ID = 0; // not needed

         event->ID.assign(step_name);
         event->ID.append("_trampling_event=");
         char int_buf[10];
         event->ID.append(CORN_int16_to_str(trampling_period++,int_buf,10));

/*Now no longer a period, only a single even
         // setup period for duration
         event->period = new  Common_event::Period;
            event->period->event_repetitions = days_on_field;
            event->period->repeat_event = true;
            event->period->interval_timestep_labeled.set(TS_DAY);
            event->period->interval = 1;
            event->period->end_sync.set_normal_growth_stage_offset(NGS_EMERGENCE, days_after_emergence + days_on_field -1);


         //      event->enabled = true;  should be the default
*/
         generated_grazing_management.tillage_operations.append(event);
      };

   VV_File gen_management_file(management_filename.c_str());
   gen_management_file.set(generated_grazing_management);

   // We have already copied the template scenario file, now replace
   // the new rotation.
   const char *gen_scenario_filename_qual_c_str = gen_scenario_filename_qual.c_str();
//   CropSyst::Scenario_directory *scenario_directory = new CropSyst::Scenario_directory(gen_scenario_filename_qual_c_str);
   //050619  Note I think scenario_directory is relinquished to scenario but I need to verify (delete this comment once verified)

//051019 now no longer pass filename to constructor
//also shouldn't need scenario directory because we are just setting up parameters.


continue here, the scenario generator is obsolete,
the target scenario is now going to be a subdirectory of the template scenario
CropSyst will search for and load the template scenario
then the following overrides will either be
command line options or and override parameter file
in the generated scenario directory.


   CropSyst_scenario scenario;
   VV_File gen_scenario_file(gen_scenario_filename_qual_c_str /*gen_scenario_filename_qual.c_str()*/);
   gen_scenario_file.get(scenario);

   scenario.description.append(" ");
   scenario.description.append(step_name);

   //copy the rotation specified in the scenario to this database,
   //obs:   determine the rotation to build years from the simulation period

   CORN::File_name gen_rotation_filename(step_name,".rot");
   gen_rotation_filename.set_path(database_directory.provide_rotation_directory(true));
   OS_copy_file(scenario.rotation_filename.c_str(),gen_rotation_filename.c_str());

   scenario.rotation_filename.set(gen_rotation_filename.c_str());

   //    open and replace all management lines with the specifiied managemnt
   VV_File gen_rotation_file(scenario.rotation_filename.c_str());
   Rotation_parameters gen_rotation;
   gen_rotation_file.get(gen_rotation);

   FOR_EACH_IN(sowing, Sowing_event, gen_rotation.sowing_events,each_sowing)
   {  Sowing_operation *sow_op = sowing->get_sowing_operation();
      sow_op->management_filename.set(management_filename.c_str());
   } FOR_EACH_END(each_sowing);
   gen_rotation_file.set(gen_rotation);
   // Indicate the output we want to optimize
   scenario.model_options_from_parameter_editor.total_grazed_biomass = true;
   scenario.model_options_from_parameter_editor.carbon_sequestered = true;
   scenario.model_options_from_parameter_editor.fast_graph = true; // we need recorded database for recovery dynamics.
   scenario.field_number = plot;
   scenario.field_size_ha = plot_acreage_ha;
   gen_scenario_file.set(scenario);
   // currently not deleting scenario, checking to see if something is is not deallocating correctly
//   return  gen_scenario_filename_qual;
};
//______________________________________________________________________________
int16 Carbon_sequestration_optimization::generate_scenarios()
{
   Simulation_run_result run_result_failed = (Simulation_run_result)1;
   Carbon_sequestration_optimization_parameters &parameters = project.carbon_sequestration_optimization_parameters;

   int scenarios_generated =  project.carbon_sequestration_optimization_parameters.calc_scenarios_required();
   int gen_count = 0;
   run_form->set_progress(0,scenarios_generated);
   run_form->append_status("Generating scenarios");
   for (int16 herd_size = parameters.min_herd_size
       ; (herd_size <= parameters.max_herd_size)
         &&(!run_form->abort_requested)
       ;herd_size += parameters.step_herd_size)
   {  for (int plots=1; plots <= parameters.max_plot_count; plots += parameters.step_plot_count)
      {  int max_duration = parameters.max_duration;
         if (plots == 1) max_duration = 1;
         for (int days_on_field = 1; days_on_field <= max_duration; days_on_field += parameters.step_duration)
         {  int recovery_time = (plots-1) * days_on_field;
            if (recovery_time <= parameters.max_recovery_days)
            {  for (int plot = 1; plot <= plots; plot++)
               {  setup_scenario(herd_size,plots,days_on_field,plot,clear_old_scenarios);
                  run_form->set_progress(++gen_count,scenarios_generated);
                  if (clear_old_scenarios)
                  {  CORN::Smart_directory_name run_scenario_dir(gen_scenario_filename_qual.c_str());
                     run_scenario_dir.set_ext(""); // scenario directory is the same as the scenario filename without the extension
                     CORN::Ustring problem_files_SDF;
                     run_scenario_dir.delete_completely(problem_files_SDF,true);
               }; };
            }; // else we exclude simulations where the number of days the animals are off the field exceeds the max.
   }; }; };
   return run_form->abort_requested ? 0 : scenarios_generated;
};
//______________________________________________________________________________
int16 Carbon_sequestration_optimization::run_scenarios()
{
   Association_list scenario_filenames;
   project_directory.get_carbon_sequestration_optimization_dir_qual(true).list_contents_by_type
      (scenario_filenames  // The list to append contents to (association because dirent names are association
      ,false/*don't recurse*/
      ,true                // the known path is prepended to the listed file names (differs from show_path because the path is actually included in the filename)
      ,true                // true if the extension is included with the file name (usually true)
      ,false               // the known path is not to be prepended when the filename is displayed
      ,false               // true if the extension is to be appended when the filename is displayed
      ,Directory_entry_name::file_entry // types of files to list (file or directory names)
      ,"CSN"               // This can be used to limit the list to certain extensions
      );
   run_form->append_status("Running scenarios:");
   run_form->set_progress(0,scenario_filenames.count());
   int run_count = 0;
   FOR_EACH_IN(scenario_dir_ent_qual,Directory_entry_name,scenario_filenames,each_SFN)
   { //    for each csn file in the directory
      gen_scenario_filename_qual.set(scenario_dir_ent_qual->c_str());
      const char *gen_scenario_filename_qual_c_str = gen_scenario_filename_qual.c_str();
//      CropSyst_scenario_directory *scenario_directory = new CropSyst_scenario_directory(gen_scenario_filename_qual_c_str);
      //050619 Note I think scenario_directory is relinquished to scenario but I need to verify  (delete this comment once verified)

///051019 now no longer pass filename to constructor

      CropSyst_scenario scenario;
      VV_File scenario_file(gen_scenario_filename_qual_c_str);
      scenario_file.get(scenario);

      CORN::Smart_directory_name run_scenario_dir(gen_scenario_filename_qual_c_str);
      run_scenario_dir.set_ext(""); // scenario directory is the same as the scenario filename without the extension

      Simulation_run_result run_result_failed =  RUN_PENDING;
      CORN::File_name grazing_regimen_dat_filename("grazing_regimen.dat");
      CORN::Smart_directory_name run_scenario_output_dir("output");
      run_scenario_output_dir.set_path(run_scenario_dir);
      grazing_regimen_dat_filename.set_path(run_scenario_output_dir);

      if (!grazing_regimen_dat_filename.exists()) // if we already have an output file then the simulation has already been run
      {
         run_form->append_status(gen_scenario_filename_qual.get_name(true).c_str());
         CORN::Ustring command_line_parameters("\"");
#ifdef CHECK_OBSOLETE
//101103

// Need to verify that CropSyst_4.exe no longer needs project file filename.

          command_line_parameters.append(project_filename);
          command_line_parameters.append("\"");
          command_line_parameters.append(" \"");
#endif

          command_line_parameters.append(gen_scenario_filename_qual_c_str);
          command_line_parameters.append("\"");
          command_line_parameters.append(" nograph > NUL");

         run_result_failed = run_scenario(command_line_parameters.c_str(),run_scenario_minimized);
         if (run_form->abort_requested)
               return RUN_ABORT; // User pressed the [Abort] button
      };
      run_count += 1;
      {  // Load the results of the scenario and output to ranking grid
         if (grazing_regimen_dat_filename.exists())
         {  Carbon_sequestration_scenario_results_data_record results_datarec
            (gen_scenario_filename_qual.get_name(true).c_str(),run_result_failed,scenario.field_size_ha);
            VV_File results_file(grazing_regimen_dat_filename.c_str());
            results_file.get(results_datarec);
            results_datarec.Xexit_code_labeled.set(run_result_failed);
            grazing_run_form->append_results(results_datarec, run_count);
            run_form->update_time();
         } else
         {  // the grazing regimine file does not exists, the scenario may have been
            // cancelled, delete the results directory so that
            // the scenario will be regenerated if the simulation is run again
            CORN::Ustring problem_files_SDF;
            run_scenario_dir.delete_completely(problem_files_SDF,true);
            run_form->append_status("Cancelled (probably because the run window was closed before the simulation completed)");
            if (prompt_continue)
               if (Application->MessageBox("The scenario simulation run appears to have been cancelled, do you wish to abort the remaining scenarios?",
                 gen_scenario_filename_qual.get_name(false).c_str(),MB_YESNO) == IDYES)
                     return RUN_ABORT;
      }; };
      run_form->set_progress(run_count,scenario_filenames.count());
   } FOR_EACH_END(each_SFN);
   return true; // could return the number of scenarios run
};
//______________________________________________________________________________
Simulation_run_result Carbon_sequestration_optimization::run()
{
   int16 scenarios_generated = generate_scenarios();
   Simulation_run_result result =  scenarios_generated? (Simulation_run_result)run_scenarios():RUN_ABORT ;
   run_form->end_run();
   return result;
};
//______________________________________________________________________________

