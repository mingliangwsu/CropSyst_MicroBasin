#pragma hdrstop
#include <iostream.h>
#include <CropSyst/Project/multirun/multi_run_console.h>
#include <corn/primitive.h>

//______________________________________________________________________________
Multi_run_console::Multi_run_console()
:step_number(0)
,max_steps(100)
//, multirun(0)
, abort_requested(false)
, estimated_minutes_remaining(0)
,run_time_tally_seconds()
,act_runtime_minutes(0)
{};
//______________________________________________________________________________
void Multi_run_console::bind_to(CropSyst_multirun *_multirun/*,TForm *model_output_form*/)
{
   multirun = _multirun;
   start_all_time = time(NULL);
};
//______________________________________________________________________________
void Multi_run_console::append_status(const char *status)
{
   cout << status << endl;
   start_scenario_time = time(NULL);
};
//______________________________________________________________________________
void Multi_run_console::set_progress(int _step_number, int _max_steps)
{
   step_number = _step_number;
   max_steps = _max_steps;
   float percent_complete = (float)step_number/(float)max_steps * 100.0;
   cout << "Complete:" << percent_complete << "%" << endl;
};
//______________________________________________________________________________
void Multi_run_console::update_time()
{
   end_scenario_time = time(NULL);
   end_all_time = time(NULL);

   float32 run_time_seconds = (float32)difftime(end_scenario_time,start_scenario_time);
   run_time_tally_seconds.append(run_time_seconds);
   mean_run_time_seconds = run_time_tally_seconds.get_mean();
   cout << "Mean run time: " << mean_run_time_seconds << " seconds" << endl;

   float32 esimated_seconds_remaining =  (max_steps - step_number) * mean_run_time_seconds;
   estimated_minutes_remaining = (int)(esimated_seconds_remaining / 60.0);
   cout << "Est. time remaining: " << estimated_minutes_remaining << " Minutes" << endl;


   start_scenario_time = time(NULL);

   float32 all_runtime_seconds = (float32)difftime(end_all_time,start_all_time);
   act_runtime_minutes = (int)(all_runtime_seconds/60);
   cout << "Act. run time: " << act_runtime_minutes << " Minutes" << endl;


};
//______________________________________________________________________________
void Multi_run_console::end_run()
{
// Shouldn't need to do anything.
};
//______________________________________________________________________________
void Multi_run_console::update_command_line(const char *commandline)
{
   cout << commandline << endl;
};
//______________________________________________________________________________

