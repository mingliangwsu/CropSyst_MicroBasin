#error this class is obsolete now use CWPF

#include <vcl.h>
#pragma hdrstop
#include "cs_project.h"
#include "cs_scenario.h"
#include "management/management_param_V4.h"
#include "corn/OS/os.h"
#include "corn/data_source/vv_file.h"
#include "corn/dynamic_array/da_uint32.h"
#include "UED/library/UED_PCH.h"
#include "csvc.h"
#include "project/optimization/crop_production_function/cropprod.h"
#include "CS_suite/application/CS_suite_directory.h"
#include "mgmtevnt.h"
#include "cs_scenario_directory.h"
#include "CS_Suite/CropSyst/file_system/project_directory_CropSyst.h"
#include <fstream>
using namespace std;
//______________________________________________________________________________
Crop_production_function_simulation::Crop_production_function_simulation
(const CORN::OS::Directory_name &_primary_scenario_dirname)                      //150417
: irrig_event_list()
, primary_scenario_directory(_primary_scenario_dirname,false) // should already exist
{}
//______________________________________________________________________________
void Crop_production_function_simulation::collect_automatic_irrigation
( const char *ued_filename)
{  UED::Database_file_indexed ued_database(ued_filename,std::ios_base::in,false);//150417
   ued_database.initialize();
   Date_time_64 earliest_date(ued_database.get_earliest_date_time());// all records all variable
   Date_time_64 latest_date(ued_database.get_latest_date_time());    // all records all variable
   int irrig_count = 0;
   for (Date_time_64 date(earliest_date); date.get_datetime64() <= latest_date.get_datetime64(); date.inc())   //031218
    {
      UED::Time_query_single_date          query_date(date.get_datetime64());    //040217
      Units_code          requested_units = UC_mm;                               //040716
      CORN::Quality_clad attribute(UED_generated);                               //150417_110725
       float32     irrigation_mm
       = ued_database.get_no_create(UED::Record_type_distinguisher_interface::
         UED_data_set_year_var_units
         // UED_data_set_date_var_units
         ,CSVC_mgmt_irrig_applied_time_step_sum,query_date,requested_units,attribute);
      if (! CORN::is_approximately<float32>(irrigation_mm ,0.0,0.00001))
      {
         CPF_Irrigation_event *irrig_event = new CPF_Irrigation_event(date.get_datetime64(),irrigation_mm); //081118
          irrig_event_list.append(irrig_event);
          irrig_count++;
      }
   }
}
//______________________________________________________________________________
CORN::OS::Directory_name *Crop_production_function_simulation::create_scenario
(nat8 percent_of_optimal
,const CORN::Dynamic_array<float32>*irrig_adj_fraction                           //081117
   // Each element in the array represents the amount to adjust
   // irrigation
   // If 0 the percent of optimal value is used
,const CORN::Dynamic_array<nat32>*irrig_adj_dates                                //081117
   // The corresponding dates as date32 values
) rendition_
{   // Note that this method has two modes depending on if irrig_adj_fraction is provided 081117
   bool irrig_adj_mode = (irrig_adj_fraction && irrig_adj_dates);                //081117
   CORN::OS::Directory_name_concrete *rendered_CPF_scenario =                        //150417
      primary_scenario_directory.render_crop_production_function_adjustment      //150417
         (irrig_adj_mode,percent_of_optimal);                                    //150417


   // CPF runs are not at the same dir level as the primary, so we need to qualify  //030517
   //060112  Need to check that  directory trees are right
   // CPF runs are not at the same dir level as the primary, so we need to qualify 030517

   /*
      construct a simulation management with specific date from
      this irrigation events list with 0 to 90% of the irrigation amount
      add these management events to the simulation file itself.
   */
   // irrigation.mgs is stored in the scenario directory so it does not need a path.

   CORN::OS::File_name_concrete CPF_irrigation_filename((*rendered_CPF_scenario),"irrigation",CS_management_LEXT);
   CropSyst::Management_parameters irrig_mgmt;                                   //131007_010112
   irrig_mgmt.description.brief.assign("crop production function simulation ");
   CORN::append_wstring_to_string(rendered_CPF_scenario->get_name(),irrig_mgmt.description.brief); //150417
   irrig_mgmt.description.brief.append("% of optimal irrigation amount");
   if (percent_of_optimal || irrig_adj_mode)   // We don't want to have any irrigations for 0% (otherwise cropsyst will refill on amount=0). //000401
   {
      FOR_EACH_IN(irrig_event,CPF_Irrigation_event,irrig_event_list,each_irrig)  //031218
       {
         float32 irrig_adj_fract = percent_of_optimal / 100.0;                   //081117
         if (irrig_adj_mode)                                                     //081117
         {  irrig_adj_fract = 1.0;   // Default to 1 if no adjustments dates     //081117
            Date32 irrig_event_date = irrig_event->date.get_date32();            //120316_081117
            if (!irrig_event_date) // it may be setup in begin_sync              //081117
               irrig_event_date = irrig_event->begin_sync.get_date32();          //081117
            nat32 date_index;                                                    //081117
            irrig_adj_dates->is_in_array(irrig_event_date, date_index);
            irrig_adj_fract = irrig_adj_fraction->get(date_index);               //081117
         }
         CropSyst::Irrigation_operation *irrig_op = new CropSyst::Irrigation_operation(); //131007_021203
         irrig_op->amount_mm = irrig_event->amount * irrig_adj_fract;            //081117
         //NYI irrig_op->salinity_32 = 0.0;
         //NYI irrig_op->chemical_concentration_32 = 0.0;
         //NYI irrig_op->net_irrigation_mult_32 = 0.0;
         //NYI irrig_op->chemical_name = "";
         Common_event *irrig_op_record
            = new Common_event(irrig_event->begin_sync,irrig_op,true);
          irrig_mgmt.irrigation_operations.append(irrig_op_record);
       } FOR_EACH_END(each_irrig)
   }
   // simply put the management file in the CPF scenario directory               //150417
   VV_File irrig_mgmt_file(CPF_irrigation_filename.c_str());
   irrig_mgmt_file.set(irrig_mgmt);
   return rendered_CPF_scenario;                                                 //150417
}
//______________________________________________________________________________
void Crop_production_function_simulation::run
(bool &CPF_abort
//150417 ,bool run_from_scenario
)
{
   // The simulation must have automatic irrigation management
   // and daily irrigation output

   // Run the primary simulation (should be with auto irrigation)
   // Delete the crop production function directories from previous run
   // Note we want to make sure all the directories are deleted
   // so we can tell that all the simulations were completely run.
   /*150417 obsolete CPF percents now specified on command line
     and CPF irrigation file is now written directly to the scenario directory
     which CropSyst will find.
   VV_File active_sim_filename(primary_scenario_filename .c_str());
   active_sim_filename.get(active_sim);
   */
   std::cout << "running primary scenario:" << primary_scenario_directory.c_str() << std::endl; //150417
   run_simulation(primary_scenario_filename);
   // Current directory will be set by sim_rerun and should be for the primary simulation.
   // Collect the irrigation into a list of irrigation events
   std::cout << "loading primary scenario parameters:" << primary_scenario_filename << std::endl;
   CropSyst::Scenario_directory primary_scenario_dir
      (primary_scenario_dirname);                                                //150417_081118
      //150417 (primary_scenario_filename.c_str());    // scenario_filename or scenario_dirname  081118
   std::cout << "collecting automatic irrigation "<< std::endl;
   collect_automatic_irrigation(primary_scenario_dir.daily_ued .c_str());


   180416 Reimplement, find this irrigation adjustments file in the context
   This will be a fixed filename created by the model
   when the primary scenario is run (by CS explorer when CPF percents checked)
   (I think explorer/runner would generate this file from recorded
    irrigation events)

   bool specifically_scheduled_adjustments = active_sim.irrigation_adjustment_filename.exists();   //081117
   if (specifically_scheduled_adjustments)                                       //081117
   {  std::cout << "running with specifically scheduled adjustments" << std::endl;
      CORN::Dynamic_array<float32>  irrig_adj_fraction(20000,366);               //101018
      CORN::Dynamic_array<nat32>    irrig_adj_dates   (20000,366,0);             //101018
      // Each element in the array represents the amount to adjust               //081117
      // irrigation                                                              //081117
      ifstream irrig_adj_file(active_sim.irrigation_adjustment_filename.c_str()); //open the irrigation_adjustments file //081117_
      int      year;
      int      DOY;
      float32  irrig_adj;
      int adj_index = 0;
      while (!irrig_adj_file.eof())                                              //081117_
      {  // read the year DOY and irrig_adj_fraction
         irrig_adj_file >> year >> DOY >> irrig_adj;
         uint32 irrig_adj_date = year * 1000 + DOY;
         irrig_adj_fraction.set(adj_index,irrig_adj);
         irrig_adj_dates   .set(adj_index,irrig_adj_date);
         adj_index++;
      }
      // Make sure that we start in the correct directory for each run. 081117_

      std::cout << "creating scenario:" << scenario_filename << std::endl;
      CORN::OS::Directory_name *adj_scenario_dirname_rendered
         = create_scenario(0,&irrig_adj_fraction,&irrig_adj_dates);              //150417
      std::cout << "running simulation:" << adj_scenario_dirname_rendered->c_str() << std::endl;
      run_scenario(*adj_scenario_dirname_rendered);
      // std::cout << "recycling database:" << scenario_database_dirname << std::endl;
      // scenario_database_dirname.recycle(false);  // might want to delete forever but for now just recycle incase user want's to look at the processing

   } else
   {  // CPF_water_percents is a bit array selecting the percentages to run //081117
      std::cout << "running with selected adjustments" << std::endl;
      nat32 CPF_water_percents = active_sim.CPF_water_percents;                  //030530
      {  // We have to do this inside the loop because the scenario may override the project's CPF preferences
         int progress_steps = 0;
         for (int j = 0; (j < 16) && (!CPF_abort) ; j++)                         //030530
         {  // Count how many steps to run to setup the progress bar
            progress_steps += (CPF_water_percents & (1 << j)) > 0;
         }
         //110725NYN sim_run_progressbar->Max = progress_steps;                              //030530
      }
      //Used to go to just 90 now need up to 150%
      for (int i = 0; (i < 16) && (!CPF_abort) ; i++)                            //030530_
      {
         nat8 percent_of_optimal =  i * 10;                                     //030530_
         {
            char percent_of_optimal_cstr[10];
            itoa((int)percent_of_optimal,percent_of_optimal_cstr,10);
            CORN::Smart_directory_name scenarios_99_dir;
            primary_scenario_dir.CPF_water_dir.subdirectory_path(percent_of_optimal_cstr,scenarios_99_dir); //081118_
            Ustring unused_problem_files_SDF;
            std::cout << "clearing previous run output:"<< scenarios_99_dir << std::endl;
            scenarios_99_dir.delete_completely(unused_problem_files_SDF,true);
         }
         bool run_percent = CPF_water_percents & (1 << i);                       //030530
         if (run_percent)                                                        //030530
         // We repeat the optimal case to check generation
         { // Make sure that we start in the correct directory for each run.
            std::cout << "creating scenario:"<< (int)percent_of_optimal << std::endl; //150417
            CORN::OS::Directory_name *adj_scenario_dirname_rendered              //150417
               = create_scenario(percent_of_optimal,NULL,NULL); //150417_030720
            std::cout << "running scenario:"<< (int)percent_of_optimal << std::endl; //150417
            run_scenario(*adj_scenario_dirname_rendered);                        //150417
            delete adj_scenario_dirname_rendered;                                //150417
            // std::cout << "recycling database:"<< scenario_database_dirname << std::endl;
            // scenario_database_dirname.recycle(false);  // might want to delete forever but for now just recycle incase user want's to look at the processing   //030720_

         }
      }
   }
}
//______________________________________________________________________________
void Crop_production_function_simulation::run_scenario(CORN::OS::Directory_name &scenario_dirname)
{  Ustring command("\"");
   command.append(CS::Suite_directory->CropSyst().cropsyst_model_executable());
   command.append("\" ");  command.append(" \"");                                //030516
   command.append(scenario_dirname); // Make sure names are quoted               //150317

   command.append("\" NOGRAPH");
   PROCESS_INFORMATION process_info;
   STARTUPINFO  startup_info;
   GetStartupInfo(&startup_info);
   startup_info.dwFlags |= STARTF_USESHOWWINDOW;
   startup_info.wShowWindow = SW_NORMAL; // SW_HIDE; // SW_NORMAL;
   bool result = true;
      if (CreateProcess
            (0
            ,(char *)command.c_str()
            ,0 // default security
            ,0 // default security
            ,true
            ,CREATE_SEPARATE_WOW_VDM|NORMAL_PRIORITY_CLASS
            ,0  // current environment block
            ,0  // pointer to current directory name  (should be current)
            ,&startup_info // pointer to STARTUPINFO
            ,&process_info // pointer to PROCESS_INFORMATION
            ))
         WaitForSingleObject(process_info.hProcess,INFINITE);
      else
         result =  false;
      // Must close process and thread handles or you get a memory leak.
   std::cout << "closing handles" << std::endl;
      CloseHandle(process_info.hProcess);
      CloseHandle(process_info.hThread);
}
//______________________________________________________________________________
//081116 400 lines
