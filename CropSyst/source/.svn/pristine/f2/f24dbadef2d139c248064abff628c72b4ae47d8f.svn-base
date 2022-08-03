#include "project/optimization/scenario_results.h"
//______________________________________________________________________________
Scenario_results_data_record::Scenario_results_data_record
(const char *i_scenario_name,Simulation_run_result i_exit_code)
: CORN::Data_record("scenario")
, scenario_name(i_scenario_name)
, Xexit_code_labeled(i_exit_code)
, days_not_viable(0)
{ };
//______________________________________________________________________________
void Scenario_results_data_record::expect_structure(bool for_write)
{  CORN::Data_record::expect_structure(for_write);
   structure_defined = false;                                                    //120314
   set_current_section("scenario");
   expect_enum("exit_code",Xexit_code_labeled);
   expect_int16("days_not_viable",days_not_viable);
   structure_defined = true;                                                     //120314
};
//______________________________________________________________________________
