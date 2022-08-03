#include "common/simulation/simulation_project_directory.h"
#define Operations_dirname    "Operations"
#define Enterprises_dirname   "Enterprises"
#define Scenarios_dirname     "Scenarios"
#define Optimization_dirname  "Optimization"

#define operations_dirname    "operations"
#define enterprises_dirname   "enterprises"
#define scenarios_dirname     "scenarios"
#define optimization_dirname  "optimization"
namespace CS {
//______________________________________________________________________________
Project_directory::Project_directory
(const CORN::OS::Directory_name &project_directory_name,bool create_now_if_needed)
:CORN::OS_FS::Project_directory(project_directory_name,create_now_if_needed)
,operations_directory         (0)
,enterprises_directory        (0)
,created_scenarios_directory  (0)
,generated_scenarios_directory(0)
{}
//______________________________________________________________________________
provide_directory_name_implementation(Project_directory,operations         ,operations_directory         ,Operations_dirname)
provide_directory_name_implementation(Project_directory,enterprises        ,enterprises_directory        ,Enterprises_dirname)
provide_directory_name_implementation(Project_directory,created_scenarios  ,created_scenarios_directory  ,Scenarios_dirname)
provide_directory_name_implementation(Project_directory,generated_scenarios,generated_scenarios_directory,"Generated_scenarios")
//______________________________________________________________________________
} // namespace CS

