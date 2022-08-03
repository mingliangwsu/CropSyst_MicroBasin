#include "CS_suite/file_system/CS_context_directory.h"
#include "CS_suite/file_system/CS_directory_contexts.hpp"
namespace CS {
//______________________________________________________________________________

bool Context_directory::is_project_directory
(const CORN::OS::Directory_name &dir_name)                           affirmation_
{
   bool is_project = CORN::OS_FS::Context_directory::is_project_directory(dir_name);
   if (!is_project)
   {
      is_project = get_directory_context(dir_name) == project_context;
   }
   return is_project;
}
//_2014-01-25___________________________________________________________________
CS::Project_directory *Context_directory::render_project_directory
(const CORN::OS::Directory_name &dir_name,bool create_now_if_needed)  rendition_
{  return new CropSyst::Project_directory(dir_name,create_now_if_needed);
}
//_2014-01-25___________________________________________________________________
/* NYN and Common_scenario_directory is currently abstract
Common_scenario_directory *Context_directory::render_scenario_directory
      (const CORN::OS::Directory_name &dir_name,bool create_now_if_needed)  rendition_
{
   return new Common_scenario_directory(dir_name,create_now_if_needed);
}
//_2014-01-25___________________________________________________________________
Scenario_directory *Context_directory::find_scenario_directory(const CORN::OS::Directory_name_concrete *current_dir) rendition_
{  return current_dir
      ?  (is_scenario_directory(current_dir))
         ? render_scenario_directory(current_dir,false)
         : find_scenario_directory(current_dir.get_path_directory_name());
      : 0; // we are at the root dir, didn't find a scenario
}
//_2014-01-25___________________________________________________________________
*/

//_2014-01-25___________________________________________________________________
bool Context_directory::is_scenario_directory(const CORN::OS::Directory_name &dir_name) affirmation_
{
   const wchar_t *canonical_scenario_file_name =  get_canonical_scenario_file_name();
   // A directory containing a canonical project filename (I.e. for CropSyst .CS_project file)
   bool is_scenario =
      (canonical_scenario_file_name != 0) &&
      CORN::OS::file_system_engine.exists( CORN::OS::Directory_name_concrete(dir_name,*canonical_scenario_file_name));
   if (!is_scenario)
   {  is_scenario = get_directory_context(dir_name) == scenario_context;
   }
   return is_scenario;
}
//_2014-01-25___________________________________________________________________
} // namespace CS

namespace CropSyst
{
CropSyst::Project_directory *Context_directory::render_project_directory
(const CORN::OS::Directory_name &dir_name,bool create_now_if_needed)  rendition_
{  return new CropSyst::Project_directory(dir_name,create_now_if_needed);
}
//_2014-01-25___________________________________________________________________
CropSyst::Scenario_directory *Context_directory::render_scenario_directory
(const CORN::OS::Directory_name &dir_name,bool create_now_if_needed) rendition_
{  return new CropSyst::Scenario_directory(dir_name,create_now_if_needed);
}
//_2014-01-25___________________________________________________________________
} // namesace CS

