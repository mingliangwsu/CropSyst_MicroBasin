#include "corn/data_source/vv_file.h"
#include "project/CS_project_editor_params.h"
#ifdef OLD_GEN_SCENARIOS_DIR
#include "CS_suite/CropSyst/file_system/project_directory_CropSyst.h"
#else
#include "cs_scenario_directory.h"
#endif
#include "rot_param.h"
#include "crop/crop_param.h"
#include "project/GIS/GIS_simulation.h"
#include "project/GIS/GIS_table.h"
#include "project/GIS/avgprob.h"
#if (__BCPLUSPLUS__ >= 0x0550)
// Buider GUI version
   #include "CropSyst/GUI/builder/multi_runner/multi_run_frm.h"
#else
// Console mode
   #include "Project/multirun/multi_run_console.h"
#endif

#include "Project/GIS/aggregate.h"
#include <assert.h>

bool LADSS_mode; //  not used for this program
//_____________________________________________________________________________
GIS_simulation::GIS_simulation
(
      const //140214 not sure yet if can be const

CropSyst::Project_editor_parameters &_project
#ifdef OLD_GEN_SCENARIOS_DIR
,CropSyst::Project_directory  &_project_directory
#else
,const //140214 not sure yet if can be const
         CropSyst::Scenario_directory       &_scenario_directory

#endif
)                               //060706
: GIS_project_params(_project.GIS_project_params)
, CropSyst_batch_run(_project
#ifdef OLD_GEN_SCENARIOS_DIR
,_project_directory
#else
,_scenario_directory
#endif
)
/*140222 moved to PAT_tally_engine
, coverage_PAT(0)
*/
, unique_sim_combinations()
, duplicate_sim_combinations()                                                   //050605
/* STATSGO1 is no longer available, may want to implement STATSGO2
, STATSGO_database(0)                                                            //050720
*/
, aggregate_all_sequences_mode(false)                                            //050919
/*140222 moved to PAT_tally_engine
, template_file_name(_scenario_directory.associated_filename())                                 //140214
*/
{
#ifdef OLD_GEN_SCENARIOS_DIR
_project_directory.set_GIS_dir(_project.GIS_project_params.output_directory); //091105
#endif
}
//_____________________________________________________________________________
GIS_simulation::~GIS_simulation()
{
   /*140215   STATSGO1 is no longer available, may want to implement STATSGO2
   if (STATSGO_database) delete STATSGO_database; STATSGO_database = 0;
   */
   if (coverage_PAT)     delete coverage_PAT; coverage_PAT = 0;                  //050927
}
//_2005-07-29_____________________________________________________________________________
Simulation_run_result GIS_simulation::run()
{  nat32 scenarios_generated = generate_scenarios();
   Simulation_run_result result =  RUN_ABORT ;
   if (scenarios_generated)                                                      //050629
   {  result = (Simulation_run_result)run_scenarios() > 0 ? RUN_SUCCESS : RUN_FAILURE;  //050629
      {                                                                          //050919

    // Tally scenarios only applies to GIS simulations                           //050919
               // where a single scenario is run for each polygon
               // It does not apply to regional soil weather database
               // simulation where multiple sequence are run for each polygon MUID
               // Eventually tally could be a separate program.
               // as aggregation will be.
         nat32 tally_count =  tally_scenarios();                                 //050629
         nat32 aggregate_files_count = (aggregate_all_sequences_mode)? aggregate_scenarios() : 0;   //050927
      }                                                                         //050629
   }                                                                            //050919
   run_form->end_run();
   return result;
}
//_____________________________________________________________________________
int GIS_simulation::add_table_line
(CropSyst::Simulation_override_record *sim_comb
,int32 &same_as_scenario_ID)                                                     //050919
{  const CropSyst::Simulation_override_record *existing_comb
      = dynamic_cast<const CropSyst::Simulation_override_record *>
         (unique_sim_combinations.find_matching(*sim_comb));
   int32 same_as_record = 0;                                                     //980216
   if (existing_comb)
   {  same_as_record = existing_comb->get_position();                            //010514
      same_as_scenario_ID = existing_comb->scenario_ID;                          //050919
      duplicate_sim_combinations.append(sim_comb);                               //050705
   } else  // record num will be obtained when the record is written
      unique_sim_combinations.append(sim_comb);
   return same_as_record;                                                        //980216
}
//_____________________________________________________________________________
nat32 GIS_simulation::generate_scenarios()
{  std::ofstream generate_scenarios_log
      #ifdef OLD_GEN_SCENARIOS_DIR
      (project_directory.generate_scenarios_log_file("txt").c_str());  //050926
      #else
      (get_generate_scenarios_log().c_str());
      #endif

   Simulation_run_result run_result_failed = (Simulation_run_result)1;
   // Delete the combinations lists incase the user started the run again without closing the run window. //051116
   unique_sim_combinations.delete_all();                                         //051116
   duplicate_sim_combinations.delete_all();                                      //050605
   nat32 scenarios_generated =  0;     // This count includes optimized scenarios
   nat32 polygons_read = 0;
   run_form->append_status("Generating scenarios");
   if (!provide_coverage_PAT())                                                  //050927
      generate_scenarios_log << "Coverage PAT does not exist:"
         << GIS_project_params.coverage_PAT_filename << endl;      //050926
   int multiple_crops = 0;                                                       //980721
   bool at_eof = !coverage_PAT->goto_BOF();
   int32 max_polygon_count = coverage_PAT->get_record_count(); // This is the total number of polygons including the offsite region
   run_form->set_progress(0,max_polygon_count);
   generate_scenarios_log << "Max polygon count:" <<max_polygon_count <<endl;    //050926

   Association_list control_and_tally_files_to_be_deleted;                       //091104
   CORN::OS::file_system_engine.list_file_names                                   //140215
      (GIS(),false,control_and_tally_files_to_be_deleted);
   /* 140215
   project_directory.get_GIS_dir_qual(false).list_contents_by_type               //091104
      (control_and_tally_files_to_be_deleted                                     //091104
      ,false   // not recursive                                                  //091104
      ,true    // qualify                                                        //091104
      ,true    // with_extension                                                 //091104
      ,true    // show_path                                                      //091104
      ,true    // show_extension                                                 //091104
      ,Directory_entry_name::file_entry                                          //091104
      // all files extension                                                     //091104
      ) ;                                                                        //091104
   */
   FOR_EACH_IN(filename,CORN::OS::File_name,control_and_tally_files_to_be_deleted,each_delete_file)     //091104
   {  CORN::OS::file_system_engine.recycle(*filename,true);                      //140214
      //140214 filename->recycle(true);                                                   //091104
   } FOR_EACH_END(each_delete_file)                                              //091104
   {                                                                             //050629
      Data_source_dBase override_dbase(project_directory.get_GIS_polygon_scenarios_filename().c_str(),std::ios::out); //010129
      // First build the table of simulation overrides
      // Load the simulation template file.                                      //010509
      template_file_name.set_DEN(project.template_scenario_filename);            //101129
      #if (CS_VERSION==4)
      if (!template_file_name.exists())                     // Perhaps this is an old CS4 .CSP project file //101129
         template_file_name.set_DEN(project.get_active_filename());                     //101129
      #endif

      if (template_file_name.exists())//050618 the active scenario is now the template (GIS_project_params.template_simulation_filename.exists())
      {  generate_scenarios_log << "Template scenario file:" << template_file_name <<endl;  //050926

         //051019 now no longer pass filename to constructor

         CropSyst::Scenario template_sim_params;                                  //051109_010609
         {  // Load the template simulation parameters                           //010609
            VV_File template_sim_file(template_file_name.c_str());               //050618_010609
            template_sim_file.get(template_sim_params);                          //010609
            //000312                Need to make sure the template rotation file is fully qualified.
         }                                                                      //010609
         if (at_eof)                                                             //050926
            generate_scenarios_log << "PAT table empty?" <<endl;                 //050926
         while (!at_eof /*moved: need to check but I think the multirun should handle continuation && continue_run*/)  //    for each simulation possibility   //971024
         {
            Polygon_attribute_data_record  polygon_attr_DR                       //030224
            (GIS_project_params.polygon_ID_attribute.c_str()
            ,GIS_project_params.soil_attribute.c_str()
            ,GIS_project_params.steepness_attribute.c_str()
            ,GIS_project_params.uniform_sand_attribute.c_str()                   //050630
            ,GIS_project_params.uniform_clay_attribute.c_str()                   //050630
            ,GIS_project_params.soil_depth_attribute.c_str()                     //050630
            ,GIS_project_params.init_PAW_attribute.c_str()
            ,GIS_project_params.init_NO3_attribute.c_str()
            ,GIS_project_params.weather_attribute.c_str()
            ,GIS_project_params.rotation_attribute.c_str()
            ,GIS_project_params.recalibration_attribute.c_str()
            ,GIS_project_params.water_table_attribute.c_str());
            //In this case we need the default SEQNUM to be 0 indicating it was not read from the PAS     //050921
            polygon_attr_DR.sim_params.SEQNUM = 0;                               //050921
            coverage_PAT->get(polygon_attr_DR);                                  //030224
            int16 polygon_ID = polygon_attr_DR.sim_params.polygon_ID;            //

            generate_scenarios_log << "Generating polygon:" << polygon_ID << endl;//050926

            //000125 For Javier Marcos' project, we compose the polygon (cell) ID from the X Y fields.
             int32 cell_X = polygon_attr_DR.X;                                   //051117
             int32 cell_Y = polygon_attr_DR.Y;                                   //051117
             if (cell_X && cell_Y && !polygon_ID)                                //000125
                polygon_ID = cell_X * 100 + cell_Y;                              //000125
             Validation_status polygon_run_status = missing_status;              //000627
            //                      The user may select the range polygons to run in the parameter editor

            // NYI need to check if scenario has been selected (or omitted from run) by user

            {

               // In normal GIS run using STATSGO, the user will probably select a specifice
               // sequence number (not 0) for the polygon and we will only need to run
               // the simulation for that MUID/SEQNUM
               // In the regional simulation, we run the simulation
               // for all sequences which will later be aggregated
               // using weight average of the sequence result
               // to give a single values for the polygon.
               // In this case there will not be a SEQNUM specified (it will be 0)
               // so we need to iterate for all the sequences     //050729
               uint8 low_SEQNUM    = polygon_attr_DR.sim_params.SEQNUM;
               uint8 high_SEQNUM   = polygon_attr_DR.sim_params.SEQNUM;

               // Aggregate_all_sequences_mode was added for the regional soil weather database simulations
               // based on STATSGO in this case we need to run a simulation
               // for each sequence (component) so essentially there
               // may be multiple simulation runs for each polygon (MUID)
               // Therefore the scenario ID cannot be the polygon ID (MUID)
               // but must also be unique for each sequence.
               // Later the aggegations of the data will give a single weighted average for all values for each MUID.
               // In this case we will use the record number as the scenario ID //050919_
               nat32 scenario_ID = polygon_ID;                                   //050919
               if (polygon_attr_DR.sim_params.MUID.length() // MUID has been mapped     //050919
                   &&
                     (   (high_SEQNUM == 0)
                      || !polygon_attr_DR.was_entry_encountered("PAT","SEQNUM")))
                       aggregate_all_sequences_mode = true;
               if (aggregate_all_sequences_mode)
                   //  need to look up in STATSGO database the number of sequences for this MUID
               {  high_SEQNUM = get_range_of_MUID_sequence_numbers(polygon_attr_DR.sim_params.MUID.c_str());
                  if (high_SEQNUM) low_SEQNUM = 1;
                  generate_scenarios_log << "Sequence range:" << (int)low_SEQNUM << " to " << (int)high_SEQNUM <<endl;      //050926
               }
               // If MUID (and sequence number) is not specified
               // then we aren't using STATSGO, so low and high SEQNUM can just be 0.
               for (uint8 seqnum = low_SEQNUM; seqnum <= high_SEQNUM; seqnum++)
                {
                  if (aggregate_all_sequences_mode)
                     scenario_ID = scenarios_generated + 1;                      //050919
                  // Here we check if we really want to run this scenario
                  // I.e. is the STATSGO component is not agricultural soil then we probably don't want to run.
                  // bool run_this_scenario = true;   050729
                  CropSyst::Simulation_override_record *override_record = new CropSyst::Simulation_override_record(scenario_ID,polygon_attr_DR.sim_params,seqnum); //050919
                  if (!override_record) return 0; // this should never happen (out of memory?)   //060303
                  override_record->parameter_overrides.combine_similar_sequences = GIS_project_params.combine_similar_sequences;  //051115
                  // if the sequence is similar to another in the map unit then  //051115
                  // make this a single cropable_component.                      //051115
               if (seqnum)                                                       //050729
                  override_record->run_it  = check_run_STATGO_scenario
                     (polygon_attr_DR.sim_params.MUID.c_str(),seqnum
                     ,override_record->parameter_overrides.COMPNAME);            //050729
               //060303 Not sure why I had this should be OK to run it is just not a STATSGO run else  override_record->run_it  = false;
               if (!override_record->run_it)                                     //050922
                  override_record->notes.append("This polygon could not be simulated (Soil component not agricultural?).");
               if (override_record)
               {  bool sim_valid = override_record->setup_record
                  (template_sim_params                                           //010609
                  ,GIS_project_params.soils_mapped                               //010520
                  ,GIS_project_params.uniform_soil_profile_mapped                //050531
                  ,1.0     // i_cell_width not used by Arccs                     //990528
                  ,false   // No subsurface flow                                 //990604
                   ,false   // steepness_mapped  // slope/steepness override at this level done by watershed model only  //010129
                  ,0    //horizon_thickness_override watershed only              //991004
                   ,GIS_project_params.init_PAW_mapped                           //010129
                   ,GIS_project_params.init_NO3_mapped                           //010129
                   ,GIS_project_params.weather_mapped                            //
                   ,GIS_project_params.rotations_mapped                          //010129
                   ,GIS_project_params.recalibration_mapped                      //060411
                   ,GIS_project_params.water_table_mapped                        //060706
                   ,error_log);

                  if (override_record->notes.length())
                  generate_scenarios_log << override_record->notes << endl;

                  // At this point if MUID is specified, we must have a seqnum if not then the scenario is not valid     //050922
                  if (polygon_attr_DR.sim_params.MUID.length() && (seqnum == 0)) //050922
                  {  override_record->run_it = false;                            //050922
                     sim_valid = false;                                          //050922
                     override_record->notes.append("MUID or sequence number invalid.");    //050922
                     generate_scenarios_log << "MUID (" << polygon_attr_DR.sim_params.MUID << ") or sequence number (" << seqnum << ")invalid." << endl;  //050926
                  }                                                             //050922
                  if (sim_valid)
                  {
                     if (override_record->run_it)
                     {
                     int32 same_as_scenario_ID = 0;
                     // Currently I do want to add the scenario (if value and even if not running it)
                     int32 same_as_record_num = add_table_line(override_record,same_as_scenario_ID);      //980928
                     override_record->same_as_ID         =same_as_scenario_ID;
                     override_record->same_as_record_num =same_as_record_num;
                          polygon_run_status = same_as_record_num ? ready_status: good_status;      //010609
                      }else // don't run but may still be valid
                         // we don't add this to the list override record table because we will not be running it.
                         polygon_run_status = good_status; // good because we process but don't need to run     //010609
                     scenarios_generated += 1;                                   //050619
                  } else  // sim not valid
                  {  override_record->scenario_ID = 0;
                     override_record->run_it = false;
                     polygon_run_status = error_status;
                     override_record->notes.append("Not valid.");
                     generate_scenarios_log << "Scenario not valid:" << scenario_ID << endl;  //050926
                  }
               } else  // override record not allocated
                  generate_scenarios_log << "Override record not allocated." <<endl; //050926
               // Now always output the potential scenario even if it isn't run (so we can see notes and tracking).
               override_dbase.set(*override_record);                             //050922
               } // for each sequence number                                    //050729
               //NYIBUILDERAPI                    app->ProcessMessages();
            }
            run_form->set_progress((int32)polygons_read++, max_polygon_count);   //050619
            at_eof = !coverage_PAT->goto_next();
         } // while !eof
      } // endif template simulation filename exists   // Override table database closed at this point
      else
         generate_scenarios_log << "Unable to find template scenario file:" << template_file_name <<endl;  //050926
   } // generation block
   run_form->set_progress(max_polygon_count, max_polygon_count);                 //050919
   at_eof = !coverage_PAT->goto_BOF();
   if (run_form->abort_requested)                                                //050926
      generate_scenarios_log << "Aborted generation."<<endl;
   return run_form->abort_requested ? 0 : scenarios_generated;
}
//_____________________________________________________________________________
STATSGO::Database *GIS_simulation::provide_STATSGO_database()
{  // allocate the database (we only need to do this once, we will keep it until this is deleted.
/*131008 I may want to reimplement this for new STATSGO2
   if (!STATSGO_database)
      STATSGO_database = new STATSGO::Database(project.STATSGO_path.c_str());
   return STATSGO_database;
*/
   return 0;
}
//_2005-08-19__________________________________________________________________
Polygon_attribute_table *GIS_simulation::provide_coverage_PAT()                  //050927
{
   if (!coverage_PAT && GIS_project_params.coverage_PAT_filename.exists())       //990422
      coverage_PAT = new Polygon_attribute_table                                 //981217
      (GIS_project_params.coverage_PAT_filename.c_str()
      ,GIS_project_params.polygon_ID_attribute.c_str()
      ,GIS_project_params.soil_attribute.c_str()
      ,GIS_project_params.steepness_attribute.c_str()
      ,GIS_project_params.uniform_sand_attribute.c_str()                         //050630
      ,GIS_project_params.uniform_clay_attribute.c_str()                         //050630
      ,GIS_project_params.soil_depth_attribute.c_str()                           //050630
      ,GIS_project_params.init_PAW_attribute.c_str()
      ,GIS_project_params.init_NO3_attribute.c_str()
      ,GIS_project_params.weather_attribute.c_str()
      ,GIS_project_params.rotation_attribute.c_str()
      ,GIS_project_params.recalibration_attribute.c_str()                        //060511
      ,GIS_project_params.water_table_attribute.c_str()                          //060706
      );
   return coverage_PAT;
}
//_____________________________________________________________________________
bool GIS_simulation::check_run_STATGO_scenario(const char *MUID, int seqnum,std::string &COMPNAME) const   //050819
{  //Look in the STATSGO COMP.DBF to get the soil capability class for this MUID SEQNUM component
/*131008 May want to reimplement this for STATSGO2
   provide_STATSGO_database();
   STATSGO::Map_unit_component_data_record map_unit_component;
   bool run_scenario = (STATSGO_database->get_map_unit_component(MUID,  seqnum,map_unit_component));
   if (run_scenario)
   {  // The component was found in the database
      // Currently GIS parameters has the option specifying dryland or irrigated conditions.
      // (we could look up in the management, but that would take bit to do,
      //  and there could be irrigation specified to test capability if there were more water available).
      COMPNAME =  map_unit_component.COMPNAME; // pick up the COMPNAME since we are already here //051115
      if (!map_unit_component.is_potential_cropland_deprecated(GIS_project_params.max_capability_class,!GIS_project_params.dryland_simulation))  //051115
         run_scenario = false;                                                   //051115
      // NYI the GIS parameters could specify an option for the compatibility class subcode.
   }
   return run_scenario;
*/
   return false;
}
//_____________________________________________________________________________
#ifdef MOVED
// 140222 moved to PAT_tally_engine
void GIS_simulation::setup_tally_files
(bool equivalence_optimization)                                                  //010114
{
   separate_crop_tallies.delete_all();
   CORN::OS::File_name_logical annual_tally_filename(project_directory.GIS(),L"annual_tally.DBF"); //140203
   CORN::OS::file_system_engine.recycle(annual_tally_filename,true);             //140203
   /*140203
   CORN::Smart_file_name annual_tally_filename("annual_tally.DBF");
   annual_tally_filename.set_path(project_directory.get_GIS_dir_qual(true));
   annual_tally_filename.delete_completely();                                    //050705
   */
   Y_tally_file = new Avg_prob_map_tallier
      (  annual_tally_filename.c_str()
      ,&project                                                                  //060706
      ,&GIS_project_params                                                       //050629
      ,true // annual tally                                                      //050630
      ,aggregate_all_sequences_mode);
#ifdef NYI
  // SRO tabled 1 based
  for (int hopt = 1; hopt <= format.HRV_options.num_vars_to_print; hopt++)       //980926
  {
       CS_UED_variable_code var_code = format.HRV_options.sel_var_code[hopt];    //000926
       if (var_code == HRV_crop_name)                                            //000926
          HRV_report_crop_variable_column = hopt;                                //000926
       shrink_to(8,lookup_description(HRV_report_var_opts,HRV_MAX_IDS,var_code),var_name_buffer);   //000926
       uint16 var_tally_options = harvest_tally_options[hopt];                   //001002
     single_H_tally_file->add_variable_option_set(var_name_buffer,hopt,var_tally_options);
  }
  single_H_tally_file->tally_table.goto_first();
#endif

   // open rotation for this scenario                                            //050708
   CropSyst::Scenario template_sim_params; // 051107 now no longer pass filename to constructor(project.get_active_filename().c_str()); 050708
   {  // Load the template simulation parameters                                 //050708
      VV_File template_sim_file(template_file_name.c_str());                     //050708
      template_sim_file.get(template_sim_params);                                //050708
   }                                                                             //050708

   Association_list identified_rotation_files;
   Association_list identified_crop_files; // Used to prevent having to reopen all the crop files
   FOR_EACH_IN(sim_run,CropSyst::Simulation_override_record,unique_sim_combinations,each_sim_run)
   {
                  ROT_filename *rotation_fname = new  ROT_filename(template_sim_params.rotation_filename);
                  if (sim_run->parameter_overrides.rotation_code.length())
                  {  ROT_filename override_rotation_fname(template_sim_params.rotation_filename.c_str());
                     override_rotation_fname.set_file(sim_run->parameter_overrides.rotation_code.c_str());
                     if (override_rotation_fname.exists())
                        rotation_fname->set_DEN(override_rotation_fname);
                  }
                  if (identified_rotation_files.find_string(*rotation_fname))
                     delete rotation_fname;
                  else
                  {  identified_rotation_files.append(rotation_fname);
                     CropSyst::Rotation_parameters rotation;
                     {  VV_File rot_file(rotation_fname->c_str());
                        rot_file.get(rotation);
                     } FOR_EACH_IN(sowing,CropSyst::Sowing_event,rotation.sowing_events,each_sowing)
                     {  const CropSyst::Sowing_operation &sow_op = sowing->provide_sowing_operation(); //131008
                        Crop_parameters crop;
                        if (!identified_crop_files.find_string(sow_op.crop_filename))
                        {  CORN::Smart_file_name *sow_crop_filename = new CORN::Smart_file_name(sow_op.crop_filename.c_str());
                           identified_crop_files.append(sow_crop_filename);
                           VV_File crop_file(sow_op.crop_filename.c_str());
                           crop_file.get(crop);
//                     Separate_crop_tally *existing_crop_tally = (Separate_crop_tally *)separate_crop_tallies.find(crop.get_description());
//                     if (!existing_crop_tally)
                           {  //if we don't already have a crop tally for this crop
                              //   append a new tally to separate_crop_tallies.list;

                  CORN::Smart_file_name season_tally_filename(sow_op.crop_filename.c_str(),"DBF");    //060320
                  season_tally_filename.set_path(project_directory.get_GIS_dir_qual(true));   //050705
                  season_tally_filename.delete_completely();                     //050705
                  Avg_prob_map_tallier *crop_tallier = new Avg_prob_map_tallier  //050705
                  ( season_tally_filename.c_str()                                //050705
                  ,&project                                                      //060706
                  ,&GIS_project_params                                           //050629
                  ,false// annual tally                                          //050630
                  ,aggregate_all_sequences_mode                                  //050920
                  );                                                             //050705
                  Separate_crop_tally *new_crop_tally = new Separate_crop_tally(crop.get_description(),crop_tallier); //050705
                  separate_crop_tallies.append(new_crop_tally);                  //050705
               }
            }
         } FOR_EACH_END(each_sowing)
      }
   } FOR_EACH_END(each_sim_run)
}
//_1999-06-11__________________________________________________________________
#endif
nat32 GIS_simulation::run_scenarios()
{
   // Need to make sure the STATSGO_database is close so CropSyst can open it    //051116
   if (STATSGO_database) delete STATSGO_database; STATSGO_database = 0;          //051116
   run_form->append_status("Running scenarios");                                 //050630
   int32 unique_sims = unique_sim_combinations.count();                          //091214
   int32 run_count = 0;                                                          //091214
   FOR_EACH_IN(sim_run,CropSyst::Simulation_override_record,unique_sim_combinations,each_sim_run)
   {
      run_form->set_progress(run_count,unique_sims);
      if (sim_run->run_it)                                                       //050729
      {   parameterize_and_run_scenario // was simulation_run_tally
         (project.cropping_system_model                                          //030220
         ,template_file_name
         ,project_directory.get_GIS_polygon_scenarios_filename()  // GIS_parameters_DBF // override_dbase_fname //050206
         ,sim_run->get_position() // record_num32  This parameter may be obsolete //010514
         ,sim_run->scenario_ID                                                   //050919
         ,sim_run->same_as_record_num
         ,sim_run->parameter_overrides.polygon_ID
         ,sim_run->same_as_ID
         ,true // 050631 always do optimization (this parameter can eventually be removed) GIS_project_params.equivalence_optimization
         );
         run_count += 1;
      }
      run_form->update_time();                                                   //050629
   } FOR_EACH_END(each_sim_run)
   return run_count; // could return the number of scenarios run
}
//_____________________________________________________________________________
nat32 GIS_simulation::tally_scenarios()
{
   run_form->append_status("Tallying results unique scenarios");                 //050630
   nat32 result = PAT_tally_engine::tally_scenarios()
   error_log.close();                                                            //990611
   return result;
}
//_____________________________________________________________________________
#ifdef MOVED
140222 moved to PAT_tally_engine
nat32 GIS_simulation::tally_scenarios()                                          //050629
{  nat32 tally_count = 0;
   run_form->append_status("Tallying results unique scenarios");                 //050630
   setup_tally_files(true ); /* now always do equivalence_optimization*/         //050631_990611
   int32 unique_sims = unique_sim_combinations.count();
   FOR_EACH_IN(sim_run,CropSyst::Simulation_override_record,unique_sim_combinations,each_unique_sim_run)
   {
//if (sim_run->parameter_overrides.polygon_ID == 2233)
//cout << "debug Reached" << endl;
     run_form->set_progress(tally_count,unique_sims);
      if (sim_run->run_it || sim_run->same_as_record_num)                        //050729
      {  tally_scenario_results
         (sim_run->scenario_ID                                                   //050919
         ,sim_run->same_as_record_num
         ,sim_run->parameter_overrides.polygon_ID
         ,sim_run->same_as_ID
         ,true ); /*050631 now always do equivalence_optimization*/
      }// else don't tally because the simulation was invalid (couldn't find parameter file or not agricultural MUID/SEQNUM)
      tally_count += 1;
   } FOR_EACH_END(each_unique_sim_run)
   run_form->append_status("Tallying results for duplicate scenarios");          //050630
    tally_count = 0;
   int32 duplicate_sims = duplicate_sim_combinations.count();
   FOR_EACH_IN(sim_run,CropSyst::Simulation_override_record,duplicate_sim_combinations,each_duplicate_sim_run)
   {
     run_form->set_progress(tally_count,duplicate_sims);
      if (sim_run->run_it || sim_run->same_as_record_num)                        //050729
      {  tally_scenario_results
         (sim_run->scenario_ID                                                   //030220
         ,sim_run->same_as_record_num
         ,sim_run->parameter_overrides.polygon_ID
         ,sim_run->same_as_ID
         ,true /*050631 now always to equiv opt GIS_project_params.equivalence_optimization*/
         );
         tally_count += 1;
      } // else don't tally because the simulation was invalid (couldn't find parameter file or not agricultural MUID/SEQNUM)
   } FOR_EACH_END(each_duplicate_sim_run)
   clean_up_tally_files(true);  /*050631 now always do equivalence_optimization*/ //001002
   run_form->append_status("Tally complete");                                    //050630
   return  tally_count;
}
#endif
//_____________________________________________________________________________
nat32 GIS_simulation::aggregate_scenarios()                                      //050927
{  nat32 files_aggregated = 0;
   STATSGO::Database *STATSGO_database = provide_STATSGO_database();
   if (!STATSGO_database) return 0; // error
   //    Get list of all dbf files in the GIS folder.
   Association_list dbf_filenames;
   project_directory.get_GIS_dir_qual(true).list_contents_by_type
      (dbf_filenames
      ,false // don't recurse
      ,true                // the known path is prepended to the listed file names (differs from show_path because the path is actually included in the filename)
      ,true                // true if the extension is included with the file name (usually true)
      ,false               // the known path is not to be prepended when the filename is displayed
      ,false               // true if the extension is to be appended when the filename is displayed
      ,Directory_entry_name::file_entry // types of files to list (file or directory names)
      ,"dbf"               // This can be used to limit the list to certain extensions
      );
   //_____________________________________________________________________________
   Dynamic_int32_indexed_dBase_data_source GIS_override_table(project_directory.get_GIS_polygon_scenarios_filename().c_str(),"scenario_ID",std::ios::in);
   FOR_EACH_IN(dbf_filename,CORN::File_name, dbf_filenames,each_dbf_file)
   {  // Ignore the scenerio parameters override table.
      if (*dbf_filename != project_directory.get_GIS_polygon_scenarios_filename())
      {  // instanciate tally aggregator for the dbf
         Tally_aggregator
         (dbf_filename->c_str()
         ,GIS_project_params.polygon_ID_attribute.c_str()
         ,GIS_override_table
         ,*STATSGO_database
         ,project.GIS_project_params.max_capability_class
         ,!project.GIS_project_params.dryland_simulation)
         .aggregate();
         files_aggregated += 1;
      }
   } FOR_EACH_END(each_dbf_file)
   return files_aggregated;
}
//_____________________________________________________________________________
Validation_status GIS_simulation::parameterize_and_run_scenario  // was simulation_run_tally
(const CORN::File_name &simulation_model
,const CORN::File_name &template_filename
,const CORN::File_name &override_database_filename
,nat32 override_record_number
,nat32 scenario_ID                                                               //050919
,nat32 same_as_record_num
,sint32 polygon_ID                // signed because negative value indicates offsite
,sint32 same_as_scenario_ID
,bool equivalence_optimization
)
{
   Validation_status status = unavailable_status;                                //000627
   char scenario_ID_str[10];
   CORN::nat32_to_cstr(scenario_ID,scenario_ID_str,10);                            //140203_990322
   char record_num_str[10];
   CORN::nat32_to_cstr(override_record_number,record_num_str,10);                  //140203
   // If we aren't simulating the polygon, we don't create a record for the polygon
   if (same_as_record_num)                                                       //990611
   {
         status = ready_status;                                                  //000627
   }
   else
   {
      // Run the simulation
      CSN_filename polygon_scenario_filename(scenario_ID_str);                   //050919
      polygon_scenario_filename.set_path(project_directory.get_GIS_dir_qual(true).c_str());
      CropSyst::Scenario_directory polygon_scenario_directory(polygon_scenario_filename.c_str()); //030220
//            purge output
//                   Only run the simulation file if no outputs already exists, we don't need to rerun the simulation
      bool annual_UED_exists = polygon_scenario_directory.annual_ued.exists();   //050920
      bool harvest_UED_exists = polygon_scenario_directory.harvest_ued.exists(); //050920
      bool output_already_exists = annual_UED_exists ||  harvest_UED_exists;     //030220
      if (!output_already_exists)                                                //990412
      {
         std::string status_note("Running polygon/cell/scenario:");

         status_note.append(scenario_ID_str);                                    //050919
         run_form->append_status(status_note.c_str());
			CORN::File_name qualified_report_format_filename(project.report_format_filename_rel.c_str()); //000627
			qualified_report_format_filename.qualify();                             //000627
         std::string/*131007 CORN::Ustring*/ sim_command_params("\"");                                 //050629
         template_filename.qualify();

         sim_command_params.append(template_filename);
         sim_command_params.append("\" ");

         // We do need the project filename incase the template filename was selected from another project's folder
         // It is also needed for the tally variables
         sim_command_params.append("\"");
         #ifdef USE_OS_FS
         sim_command_params.append(project_directory.associated_filename());     //120321
         #else
         CORN::Smart_file_name project_parameters_filename;
         project_directory.get_associated_filename(project_parameters_filename);
         sim_command_params.append(project_parameters_filename);                            //000627
         #endif

         sim_command_params.append("\" ");

         sim_command_params.append(" TABLE \"");
         sim_command_params.append(override_database_filename);                  //000627
         sim_command_params.append("\" SCENARIO ");
         sim_command_params.append(scenario_ID_str);                             //010609
         sim_command_params.append(" NOGRAPH");
         run_form->append_status(sim_command_params.c_str());
         run_scenario(sim_command_params.c_str(),run_scenario_minimized);        //050629
         status = good_status;
      }                                                                          //990412
      else                                                                       //000627
      {
         std::string/*131007 CORN::Ustring*/ status_note("Using previously run polygon/cell/scenario:");
         status_note.append(scenario_ID_str);                                    //050919
         run_form->append_status(status_note.c_str());
               status = ready_status;                                            //000627
      }
      clean_up_scenario(polygon_scenario_directory); //Delete output files and folders that are not used by GIS //050920
   }
   return status;                                                                //000627
}
//_1999-06-11__________________________________________________________________
#ifdef MOVED
140222 moved to PAT_tally_engine
Validation_status GIS_simulation::tally_scenario_results
(nat32 scenario_ID                                                               //050919
,nat32 same_as_record_num
,sint32 polygon_ID             // signed because negative values indicate offsite
,sint32 same_as_scenario_ID    // signed because negative values indicate offsite    //050919
,bool equivalence_optimization
)
{
   Validation_status status = unavailable_status;                                //000627
   char tally_scenario_ID_str[10];                                               //050919
   CORN::nat32_to_cstr((int)same_as_record_num ? same_as_scenario_ID :scenario_ID,tally_scenario_ID_str,10); //140203
   // If we aren't simulating the polygon, we don't create a record for the polygon

   CSN_filename polygon_scenario_filename(tally_scenario_ID_str);
   polygon_scenario_filename.set_path(project_directory.get_GIS_dir_qual(true).c_str());
   CropSyst::Scenario_directory polygon_scenario_directory(polygon_scenario_filename.c_str()); //030220
   std::stringstatus_line(tally_scenario_ID_str);                                //091104
   status_line.append(" : annual");                                              //091104
   run_form->append_status(polygon_scenario_directory.annual_ued.c_str());       //091104
   status_line.assign("");
   Y_tally_file->tally_UED_file(polygon_scenario_directory.annual_ued.c_str()    //990612
               ,scenario_ID                                                      //050920
               ,polygon_ID
               ,0
               ,status_line);
   {  // we have to do this here because we don't yet have the list of unique crop descriptions until we have one harvest report
                           // read the harvest file and get all the unique crop descriptions
   }
   FOR_EACH_IN (crop_tally,Separate_crop_tally,separate_crop_tallies,each_crop_tally)
   {  std::stringstatus_line(tally_scenario_ID_str);                             //091104
      status_line.append(" : ");                                                 //091104
      status_line.append(crop_tally->crop_name.c_str());                         //091104
      run_form->append_status(status_line.c_str());                              //091104
      status_line.assign("");
      crop_tally->crop_tally_file->tally_UED_file(
               polygon_scenario_directory.season_ued.c_str()
               ,scenario_ID                                                      //050920
               ,polygon_ID,crop_tally->crop_name.c_str(),status_line);
      if (status_line.length()) run_form->append_status(status_line.c_str());    //091104
   } FOR_EACH_END(each_crop_tally)
   return status;                                                                //000627
}
#endif
//_1999-06-11__________________________________________________________________
#ifdef MOVED
void GIS_simulation::clean_up_tally_files
(bool      equivalence_optimization)                                             //001002
{
   delete Y_tally_file; Y_tally_file = 0;
   separate_crop_tallies.delete_all();                                           //050531
   error_log.close();                                                            //990611
}
#endif
//_____________________________________________________________________________
uint8 GIS_simulation::get_range_of_MUID_sequence_numbers(const char *MUID)
{
   // Returns the number of sequence numbers (highest sequence number) for this MUID.
   // Returns 0 if this MUID is not found or no sequences found.
   // Presume that if there is a sequence returned the lowest is always 1.
/*131008  May want to remimplement this for STATSGO2
   provide_STATSGO_database();
   return STATSGO_database->get_range_of_MUID_sequence_numbers(MUID);
*/
return 0;
}
//_2005-07-20__________________________________________________________________
void GIS_simulation::clean_up_scenario(CropSyst::Scenario_directory &polygon_scenario_directory)
{
   std::string/*131007 CORN::Ustring*/ error_log;
   CropSyst_batch_run::clean_up_scenario(polygon_scenario_directory);            //060710

/*Needed for Watershed but can be delete if not running watershed
               polygon_scenario_directory.output_watershed_dir.delete_completely();
               polygon_scenario_directory.output_watershed_channel_dir.delete_completely();
               polygon_scenario_directory.output_watershed_in_ued.delete_completely();
               polygon_scenario_directory.output_watershed_out_ued.delete_completely();
*/
               polygon_scenario_directory.schedule_txt   .delete_completely();
               polygon_scenario_directory.daily_xls      .delete_completely();
               polygon_scenario_directory.season_xls     .delete_completely();
               polygon_scenario_directory.annual_xls     .delete_completely();
               polygon_scenario_directory.harvest_xls    .delete_completely();
               polygon_scenario_directory.fallow_xls     .delete_completely();
               polygon_scenario_directory.daily_N_xls    .delete_completely();
               polygon_scenario_directory.season_N_xls   .delete_completely();
               polygon_scenario_directory.annual_N_xls   .delete_completely();
               polygon_scenario_directory.fallow_N_xls   .delete_completely();
               polygon_scenario_directory.FD_status_txt  .delete_completely();


               // The following are in the soils dir,
               // I think deleting these files, before the soil dir will release the soil dir to be deleted
               polygon_scenario_directory.hydraulic_properties_xls.delete_completely();
               polygon_scenario_directory.water_content_xls       .delete_completely();
               polygon_scenario_directory.water_potential_xls     .delete_completely();
               polygon_scenario_directory.root_fraction_xls       .delete_completely();
               polygon_scenario_directory.temperature_xls         .delete_completely();
               polygon_scenario_directory.plant_residue_xls       .delete_completely();
               polygon_scenario_directory.manure_residue_xls      .delete_completely();
               polygon_scenario_directory.organic_matter_xls      .delete_completely();
               polygon_scenario_directory.nitrate_xls             .delete_completely();
               polygon_scenario_directory.ammonium_xls            .delete_completely();
               polygon_scenario_directory.NH4_mineralization_xls  .delete_completely();
               polygon_scenario_directory.nitrification_xls       .delete_completely();
               polygon_scenario_directory.denitrification_xls     .delete_completely();
               polygon_scenario_directory.salinity_xls            .delete_completely();

               Association_list deleted_files; Association_list undeleted_files;
               polygon_scenario_directory.output_soil_dir.delete_all(deleted_files,undeleted_files,error_log);

               polygon_scenario_directory.grazing_regimen_dat.delete_completely();
               polygon_scenario_directory.daily_ued.delete_completely();

// Keep the following
#ifdef DONT_DELETE
   Filtered_file_name harvest_htm;                                               //030516
   Smart_file_name    recorded_ued;                                              //020426
   Smart_file_name   ;                                                           //030716
   Smart_file_name   season_ued;                                                 //040921
   Smart_file_name   annual_ued;                                                 //040921
   Smart_file_name   harvest_ued;                                                //040921
   Smart_file_name   ;                                                           //040812

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
const CORN::OS::Directory_name& GIS_simulation::get_generated_scenarios_directory_qual()
      { return
         #ifdef OLD_GEN_SCENARIOS_DIR
         generation_directory_qual;
         #else
         scenario_directory.GIS();
         #endif
      }
//_2014-02-14___________________________________________________________________

// 060710 was 1020 lines

