#include "file_system_CropSyst.h"
#include "corn/string/strconv.h"
namespace CropSyst
{
//______________________________________________________________________________
File_system::File_system()
: CORN::OS::File_system_logical()
{}
//______________________________________________________________________________
const Scenario_directory &File_system::provide_scenario_directory_string
(const std::string &fully_qualified_scenario_dir_name)                provision_
{  return
   provide_scenario_directory(CORN::OS::Directory_name_logical(fully_qualified_scenario_dir_name));
}
//______________________________________________________________________________
const Scenario_directory &File_system::provide_scenario_directory_Unicode
(const_Unicodez fully_qualified_scenario_dir_name)                    provision_
{  CORN::OS::Directory_name_logical dir_name(fully_qualified_scenario_dir_name);
   return provide_scenario_directory(dir_name);
}
//______________________________________________________________________________
const Scenario_directory &File_system::provide_scenario_directory
(const CORN_Directory_name &scenario_directory_name)                  provision_
{
   Scenario_directory *scenario_dir = dynamic_cast<Scenario_directory *>
      (recognized_directories.find_cstr(scenario_directory_name.c_str()));
   if (!scenario_dir)
   {  scenario_dir = new Scenario_directory(scenario_directory_name,true);       //130808
      recognized_directories.append(scenario_dir);
   };
   return *scenario_dir;
}
//_2012-02-07___________________________________________________________________
File_system file_system;
//______________________________________________________________________________
} // namespace CropSyst

