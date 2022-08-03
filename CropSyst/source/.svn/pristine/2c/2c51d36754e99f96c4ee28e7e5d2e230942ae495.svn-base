#ifndef MULTI_RUN_CONSOLE_H
#define MULTI_RUN_CONSOLE_H

#include <time.h>
#include <corn/math/statistical/stats.h>

class CropSyst_multirun;

class Multi_run_console
{
public:
   bool abort_requested;
   time_t start_scenario_time, end_scenario_time;
   time_t start_all_time, end_all_time;
   CORN::Statistical_running_tally  run_time_tally_seconds;
   int16                      estimated_minutes_remaining;
   int32                      act_runtime_minutes;
   float32                    mean_run_time_seconds;

private:
   int step_number;
   int max_steps;
   CropSyst_multirun *multirun;

public:
   Multi_run_console();


   void bind_to(CropSyst_multirun *i_multirun/*,TForm *model_output_form*/);
   void append_status(const char *status);
   void set_progress(int step_number, int max_steps);

   void update_time();
   void end_run();
   void update_command_line(const char *commandline);

};



class TMulti_run_form : public Multi_run_console
{
// This allows the interface to work either with
// the TMulti_run_form  of Multi_run_console

};

#endif
