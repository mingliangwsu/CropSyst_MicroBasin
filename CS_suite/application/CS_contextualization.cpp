#include "CS_suite/application/CS_contextualization.h"
#include "corn/OS/file_system_engine.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/seclusion.h"
namespace CS
{
//______________________________________________________________________________
bool Contextualization::is_scenario_ultimate
(const CORN::OS::Directory_name *dir)                               affirmation_
{
   bool has_subscenarios = has_any_subscenario(dir);
/*
   return !is_beneath("*Output",dir)                                             //180406
      &&  (has_monument("*Output",dir)                                           //180406
*/
   return ! is_beneath("*utput*",dir)                                            //180404
      &&  (has_monument("*utput*",dir)                                           //180404
      ||  !has_subscenarios);
}
//_is_scenario_ultimate_____________________________________________2017-12-27_/
bool Contextualization::is_scenario_level
(const CORN::OS::Directory_name *dir)                               affirmation_
{  return is_underneath("Scenarios",dir)
      && !is_beneath("*Output",dir);                                             //180406
}
//_is_scenario_level________________________________________________2017-12-27_/
bool Contextualization::has_any_subscenario
(const CORN::OS::Directory_name *specified_dir)                     affirmation_
{
   bool has_subscenario = is_scenario_level(specified_dir);
      // For far dir is a scenario
   if (has_subscenario)
   {
      const CORN::OS::Directory_name &dir
         = (specified_dir)
            ? *specified_dir
            : get_active_directory(); //180723get_directory_name_qualified();
      CORN::Text_list subdirs;
      nat32 subdir_count = CORN::OS::file_system_engine
         .list_names_in(dir,0,&subdirs);
      has_subscenario = subdir_count;
      /* NYI
         Currently assuming any other subdirs are subscenarios
         but should check that any of the subdirs are actually scnearios
      */
   }
   return has_subscenario;
}
//_has_any_subscenario______________________________________________2017-12-27_/
nat32 Contextualization::list_ultimate_scenarios
(const CORN::OS::Directory_name &level_or_ultimate_scenario
,CORN::Container &ultimates_list
,bool dont_include_percent_dirs)
{
   CORN::Unidirectional_list this_and_subscenarios_pot;

std::clog << "level_or_ultimate_scenario:" << level_or_ultimate_scenario.c_str() << std::endl;

   if (is_scenario_ultimate(&level_or_ultimate_scenario))
      ultimates_list.append(new CORN::OS::Directory_name_concrete(level_or_ultimate_scenario));
   else
   {
      this_and_subscenarios_pot.append(new CORN::OS::Directory_name_concrete(level_or_ultimate_scenario));
      CORN::Seclusion potential_ultimate_pattern
         ("*Output",true,false);
      potential_ultimate_pattern.include_pattern_cstr("*");
      CORN::OS::file_system_engine.list_DENs
         (level_or_ultimate_scenario,0,&this_and_subscenarios_pot
         ,potential_ultimate_pattern
         ,CORN::OS::File_system::subdirectory_recursion_inclusive);
      FOR_EACH_IN(pot_subscenario,CORN::OS::Directory_name,this_and_subscenarios_pot,each_pot_subcenario)
      {  if (is_scenario_ultimate(pot_subscenario))
            ultimates_list.take(each_pot_subcenario->detach_current());
      } FOR_EACH_END(each_pot_subcenario)
   }
   return ultimates_list.count();
}
//_list_ultimate_scenarios__________________________________________2018-01-10_/
} // namespace CS

