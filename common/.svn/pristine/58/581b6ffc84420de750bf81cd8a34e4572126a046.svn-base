//140125 Rename this file to project_directory_CS

// This class is becoming obsolete, it is replaced with CS::File_system_discovery

#ifndef simulation_project_directoryH
#define simulation_project_directoryH

#include "corn/application/project_directory_OS_FS.h"
namespace CS {                                                                   //140125
class Scenario_directory;
//______________________________________________________________________________
class Project_directory // was Common_simulation_project_directory               //140125
: public CORN::OS_FS::Project_directory
{public:
 protected:
   // NYI
   provided_ CORN::OS::Directory_name   *operations_directory;
   provided_ CORN::OS::Directory_name   *enterprises_directory;
   provided_ CORN::OS::Directory_name   *created_scenarios_directory;
   provided_ CORN::OS::Directory_name   *generated_scenarios_directory;
 public:
   Project_directory
      (const CORN::OS::Directory_name &project_directory_name
      ,bool create_now_if_needed);
   const CORN::OS::Directory_name &operations()                      provision_;
   const CORN::OS::Directory_name &enterprises()                     provision_;
   const CORN::OS::Directory_name &created_scenarios()               provision_;
   const CORN::OS::Directory_name &generated_scenarios()             provision_;
   Scenario_directory *render_scenario_directory();
};
//______________________________________________________________________________
   //NYI  render_simulation_project_directory
// The function is used by parameter editors to locate the project directory the passed parameter file is located in.
//______________________________________________________________________________
} // namespace CS

#endif

