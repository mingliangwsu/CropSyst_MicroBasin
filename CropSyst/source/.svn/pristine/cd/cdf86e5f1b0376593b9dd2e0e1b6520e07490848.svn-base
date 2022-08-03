#include "Project/multirun/batchrun.h"
#include "Project/cs_project_editor_params.h"
#ifdef OLD_GEN_SCENARIOS_DIR
#include "cs_project_directory.h"
#endif
#include "CS_suite/CropSyst/file_system/project_directory_CropSyst.h"
#include "cs_scenario_directory.h"
#include <CropSyst/GUI/builder/multi_runner/multi_run_frm.h>
//______________________________________________________________________________
CropSyst_batch_run::CropSyst_batch_run
(const CropSyst::Project_editor_parameters  &_project
//140214 not sure yet if can be const
#ifdef OLD_GEN_SCENARIOS_DIR
,const CropSyst::Project_directory   &_project_directory
#else
,const CropSyst::Scenario_directory  &_scenario_directory
//140214 not sure yet if can be const
#endif
)                        //140203_060706
: CropSyst_multirun(_project,_scenario_directory/*140214 _project_directory*/)
, PAT_tally_engine(_scenario_directory.GIS())                                //140222
#ifdef OLD_GEN_SCENARIOS_DIR
, Scenario_generator(_project_directory.GIS()/*140203 get_GIS_dir_qual(true)*/.c_str())
#endif
, project(_project)
, Y_tally_file(0)                                                                //050629
, separate_crop_tallies()                                                        //050708
{  error_log.open("errors.txt");
}
//______________________________________________________________________________
const CORN::OS::Directory_name /*140203 Smart_directory_name*/ &CropSyst_batch_run::get_generated_scenarios_directory_qual()
{ return project_directory.get_generated_scenarios_dir_qual(true); }
//______________________________________________________________________________
Simulation_run_result CropSyst_batch_run::run()
{
   Simulation_run_result result =  RUN_ABORT ;
   Validation_status status = unavailable_status;
   ifstream selected_scenario_filenames(project_directory.get_selected_scenarios_filename_cstr());
   char select_scenario_filename_cstr[1024];
   run_count = 0;
   while (!selected_scenario_filenames.eof())
   {   // for each selected scenario
      selected_scenario_filenames >> select_scenario_filename_cstr;
         // Run the simulation
      CSN_filename selected_scenario_filename(select_scenario_filename_cstr);
      selected_scenario_filename.set_path(project_directory.get_GIS_dir_qual(true).c_str());
      CropSyst::Scenario_directory selected_scenario_directory(selected_scenario_filename.c_str());  //030220
      // purge output
      // Only run the simulation file if no outputs already exists, we don't need to rerun the simulation
      bool annual_UED_exists = selected_scenario_directory.annual_ued.exists();  //050920
      bool harvest_UED_exists = selected_scenario_directory.harvest_ued.exists();//050920
      {
            CORN::Ustring status_note("Running polygon/cell/scenario:");
            status_note.append(select_scenario_filename_cstr);                   //050919
            run_form->append_status(status_note.c_str());
			   CORN::File_name qualified_report_format_filename(project.report_format_filename_rel.c_str()); //000627
			   qualified_report_format_filename.qualify();                          //000627
            CORN::Ustring sim_command_params("\"");                              //050629
            sim_command_params.append(select_scenario_filename_cstr);
            sim_command_params.append("\" ");
            // We do need the project filename incase the template filename was selected from another project's folder
#if (CS_VERSION >= 5)
   //101103 In version 5 the project file should become obsolete
   // but I need to check if there are any project parameters still used
   // may need to pass the GIS parameter file anyway.
   // once verified, delete this entire section.

   assert(false); // Need to verify neither the project nor GIS parameters are needed

   #ifdef CHECK_OBSOLETE
            sim_command_params.append("\"");
            sim_command_params.append(project_directory);            //101103
            sim_command_params.append("\\.CS_project");
            sim_command_params.append("\" ");
   #endif
#else
            sim_command_params.append("\"");
            sim_command_params.append(project_directory);            //101103
            sim_command_params.append(".CSP");
            sim_command_params.append("\" ");
#endif
            sim_command_params.append(" NOGRAPH");
            run_scenario(sim_command_params.c_str(),run_scenario_minimized);     //050629
            status = good_status;
      }
      // Currently not doing any clean up  (should be an option in multirun form)
      clean_up_scenario(selected_scenario_directory); //Delete output files and folders that are not used by GIS //050920
      run_count ++;
      result = (status == good_status) ? RUN_SUCCESS : RUN_FAILURE;
   }
   nat32 tally_count = tally_scenarios();                                        //050629
   run_form->end_run();
   return result;
}
//______________________________________________________________________________
/*050629_*/ nat32 CropSyst_batch_run::tally_scenarios()
/*_______*/ {  nat32 tally_count = 0;
#ifdef NYI
/*050630_*/    run_form->append_status("Tallying results");
/*990611_*/    setup_tally_files(true /* 050631 now always do equiv opt GIS_project_params.equivalence_optimization*/);
/*_______*/    ifstream selected_scenario_filenames(project_directory.get_selected_scenarios_filename_cstr());
/*_______*/    char select_scenario_filename_cstr[1024];
/*_______*/    while (!selected_scenario_filenames.eof())
/*_______*/    {   // for each selected scenario
/*_______*/       selected_scenario_filenames >> select_scenario_filename_cstr;
/*_______*/          // Run the simulation
/*_______*/          CSN_filename selected_scenario_filename(select_scenario_filename_cstr);
/*_______*/          selected_scenario_filename.set_path(project_directory.get_GIS_dir_qual(true).c_str());
/*030220_*/          CropSyst::Scenario_directory /*120112 CropSyst_scenario_directory*/ selected_scenario_directory(selected_scenario_filename.c_str());
//if (sim_run->parameter_overrides.polygon_ID == 2233)
//cout << "debug Reached" << endl;
/*_______*/      run_form->set_progress(tally_count,run_count);
/*050729_*/       if (sim_run->run_it || sim_run->same_as_record_num)
/*_______*/       {  tally_scenario_results
/*050919_*/          (sim_run->scenario_ID
/*_______*/          ,sim_run->same_as_record_num
/*_______*/          ,sim_run->parameter_overrides.polygon_ID
/*_______*/          ,sim_run->same_as_ID
/*_______*/          ,true /*050631 now always to equiv opt GIS_project_params.equivalence_optimization*/
/*_______*/          );
                  };// else don't tally because the simulation was invalid (couldn't find parameter file or not agricultural MUID/SEQNUM)
/*_______*/       tally_count += 1;
/*_______*/    } FOR_EACH_END(each_unique_sim_run);
/*_______*/
/*001002_*/   clean_up_tally_files(true );
/*050630_*/    run_form->append_status("Tally complete");
#endif
   return  tally_count;
}
//_2005-06-29___________________________________________________________________
void CropSyst_batch_run::clean_up_scenario(CropSyst::Scenario_directory &polygon_scenario_directory)
{ //Delete output files and folders that are not used by GIS
   polygon_scenario_directory.totals_txt.delete_completely();
#ifdef SOIL_TEMP_DEBUG
   polygon_scenario_directory.soil_temp_hourly_dat.delete_completely();
#endif
   polygon_scenario_directory.detail_txt.delete_completely();
   polygon_scenario_directory.grazing_regimen_dat.delete_completely();

   // This file is currently a temporary file.
   Smart_file_name daily_grazing_txt( polygon_scenario_directory.schedule_txt.c_str());
   daily_grazing_txt.set_name("daily_grazing.txt");
   daily_grazing_txt.delete_completely();

// Keep the following
#ifdef DONT_DELETE
   Filtered_file_name harvest_htm;
   Smart_file_name    recorded_ued;
   Smart_file_name   ;
   Smart_file_name   season_ued;
   Smart_file_name   annual_ued;
   Smart_file_name   harvest_ued;
   Smart_file_name   ;

   polygon_scenario_directory.xxxxxx.delete_completely();
   polygon_scenario_directory.xxxxxx.delete_completely();
   polygon_scenario_directory.xxxxxx.delete_completely();
   polygon_scenario_directory.xxxxxx.delete_completely();
   polygon_scenario_directory.xxxxxx.delete_completely();
   polygon_scenario_directory.xxxxxx.delete_completely();
   polygon_scenario_directory.xxxxxx.delete_completely();
   polygon_scenario_directory.xxxxxx.delete_completely();
#endif
}
//_2005-09-20___________________________________________________________________


