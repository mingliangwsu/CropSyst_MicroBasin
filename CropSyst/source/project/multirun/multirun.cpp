#include "project/multirun/multirun.h"
//#include "cs_project_directory.h"
#include "CS_suite/CropSyst/file_system/project_directory_CropSyst.h"
//______________________________________________________________________________
CropSyst_multirun::CropSyst_multirun
(const CropSyst::Project_editor_parameters& _project
#ifdef OLD_GEN_SCENARIOS_DIR
,const CropSyst::Project_directory& /*1040203 CropSyst_project_directory&*/   _project_directory
#else
,const // not sure yet if can be const
 CropSyst::Scenario_directory       &_scenario_directory                         //140214
#endif
)                   //101118
: project_parameters(_project)
/*140213 generated scenario filenames are now rendered
, gen_scenario_filename_qual()
*/
, run_form(0)
#ifdef OLD_GEN_SCENARIOS_DIR
, project_directory(_project_directory)                                          //101103
#else
,scenario_directory(_scenario_directory)                                         //140214
#endif
, run_scenario_minimized(false)
, clear_old_scenarios(false)
, prompt_continue(false)
{}
//______________________________________________________________________________
void CropSyst_multirun::set_run_form(TMulti_run_form* _run_form)
{  run_form = _run_form;
}
//______________________________________________________________________________
bool CropSyst_multirun::was_launched_by_CS_explorer()                      const
{  return true;
/*No longer supporting old CSP projects, so now the project files is always a module
   std::string potential_project_name;                                           //131008
   project_directory.get_name_with_extension(potential_project_name);
   return project_directory == ".CS_project";
*/
}
//_2010-11-16_____________________________________was_launched_by_CS_explorer__/
