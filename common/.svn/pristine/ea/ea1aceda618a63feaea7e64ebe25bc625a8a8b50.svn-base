#ifndef exit_codesH
#define exit_codesH

#ifndef labeled_enumH
#  include "corn/labeled_enum.h"
#endif
#include <stdlib.h>
// for EXIT_SUCCESS
namespace CS {
//______________________________________________________________________________
enum  Simulation_run_result
{  RUN_SUCCESS = EXIT_SUCCESS   // Usually defined as 0
,  RUN_FAILURE                = EXIT_FAILURE   // Usually defined as 1
,  RUN_TERMINATE        // Terminated gracefully
,  RUN_BAD_PARAMETER    // Some parameter precluded proper simulation run.
,  RUN_ABORT            // Simulation terminated because of an untenable situation, I.e. management could not be applied with contingency abort
,  RUN_ERROR            // Program would have crashed if error not checked
,  RUN_NOT_VIABLE       // The simulation was allowed to complete, but at least one management could not be completed correctly (not necessarily an error)
,  RUN_PENDING          // This simulation has not been run yet (this is used for multi run analysis status) it is not a value returned by CropSyst exit
,  RUN_EXIT_CODE_COUNT
};
extern char *simulation_run_result_label_table[];
DECLARE_LABELED_ENUM(Simulation_run_result_labeled,Simulation_run_result,simulation_run_result_label_table)
//______________________________________________________________________________
} // namespace CS
#endif
// exit_codes.h
