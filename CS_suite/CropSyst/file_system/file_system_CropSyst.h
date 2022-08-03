#ifndef file_system_CropSystH
#define file_system_CropSystH
#include "corn/OS/file_system_logical.h"
#include "cs_scenario_directory.h"

namespace CropSyst
{
//______________________________________________________________________________
class File_system
: public CORN::OS::File_system_logical
{public:
   File_system();
 public:
   const Scenario_directory &provide_scenario_directory_Unicode
      (const_Unicodez fully_qualified_scenario_dir_name)              provision_;
   const Scenario_directory &provide_scenario_directory_string
      (const std::string &fully_qualified_scenario_dir_name)          provision_;
      /**< Use this when the first input is a scenario directory.
           Used when setting up a scenario.
      Used by:
      - REACCH scenario exporter
      **/
   const Scenario_directory &provide_scenario_directory
      (const CORN_Directory_name &scenario_directory_name_given)     provision_; //120207
};
//_2012-02-05___________________________________________________________________
extern File_system file_system;
}; //namespace CropSyst

#endif
