#ifndef scenario_resultsH
#define scenario_resultsH
#include <corn/data_source/datarec.h>
#include <common/simulation/exit_codes.h>
//______________________________________________________________________________
class Scenario_results_data_record
: public CORN::Data_record
{public:
   std::string scenario_name;  // scenario filename without path and extension
   Simulation_run_result_labeled Xexit_code_labeled;
   int16          days_not_viable;
 public:
   Scenario_results_data_record(const char *i_scenario_name,Simulation_run_result i_exit_code);
   inline virtual int16 get_days_not_viable() const { return days_not_viable; };
   virtual float32      get_result(int index) const = 0;
   virtual void         expect_structure(bool for_write);
};
//______________________________________________________________________________
#endif