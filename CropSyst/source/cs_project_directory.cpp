#include "cs_project_directory.h"
//130326#include "cs_paths.h"
#include "database_dir.h"
#include "CS_suite/application/CS_suite_directory.h"
//______________________________________________________________________________
CropSyst_project_directory::CropSyst_project_directory
(const char *cropsyst_project_filename
/*160801 obsolete
#if (CS_VERSION==4)
,CropSyst_project_type  _project_type // So we know what kind of icon to assign. //060614
#endif
*/
)
: Common_simulation_project_directory(cropsyst_project_filename)
/*160801 obsolete
#if (CS_VERSION==4)
, project_type(_project_type)                                                    //060614
#endif
*/
, database_directory(0)                                                          //090518
#ifndef linux
, generate_scenarios_log_filename(0)                                             //101118
#ifndef LADSS_UNIX
, selected_scenarios("selected_scenarios.dat")                                   //060710
#endif
#endif
{
#ifndef LADSS_UNIX
// not needed for LADSS
   GIS_dir_qual.set_cstr("GIS");                                                 //130123_050203
   GIS_dir_qual.set_path(*this) ;                                                //050203
   GIS_aggregation_dir_qual.set_cstr("aggregation");                             //130123_050930
   GIS_aggregation_dir_qual.set_path(GIS_dir_qual);                              //050930
   // optimization models are at the same directory level as scenarios           //040806
   carbon_sequestration_optimization_dir_qual.set_cstr("Carbon_sequestration_optimization");//130123_040806
   carbon_sequestration_optimization_dir_qual.set_path(*this);                   //040806
   selected_scenarios.set_path(*this) ;                                          //060710
   scenario_comparison_dir_qual.set_cstr("scenario_comparison");                 //130123_070423
   scenario_comparison_dir_qual.set_path(*this);                                 //070423
#endif
}
//______________________________________________________________________________
CropSyst_project_directory::CropSyst_project_directory
(const CORN::OS::File_name_concrete &dir_name
/*160801 obsolete
#if (CS_VERSION==4)
,CropSyst_project_type  _project_type // So we know what kind of icon to assign.    //060614
#endif
*/
)
: Common_simulation_project_directory(dir_name)
/*160801 obsolete
#if (CS_VERSION==4)
, project_type(_project_type)                                                    //060614
#endif
*/
, database_directory(0)                                                          //090518
#ifndef linux
, generate_scenarios_log_filename(0)                                             //101118
#ifndef LADSS_UNIX
, selected_scenarios("selected_scenarios.dat")                                   //060710
#endif
#endif
{
#ifndef LADSS_UNIX
// not needed for LADSS
   GIS_dir_qual.set_str("GIS");                                                  //130123_050203
   GIS_dir_qual.set_path(*this) ;                                                //050203
   GIS_aggregation_dir_qual.set_cstr("aggregation");                             //130123_050930
   GIS_aggregation_dir_qual.set_path(GIS_dir_qual);                              //050930
   // optimization models are at the same directory level as scenarios           //040806
   carbon_sequestration_optimization_dir_qual.set_cstr("Carbon_sequestration_optimization");//130123_040806
   carbon_sequestration_optimization_dir_qual.set_path(*this);                   //040806
   selected_scenarios.set_path(*this) ;                                          //060710
   scenario_comparison_dir_qual.set_cstr("scenario_comparison");               //130123_070423
   scenario_comparison_dir_qual.set_path(*this);                                 //070423
#endif
}
//_2010-02-09__2005-02-03_________________________________________constructor__/
CropSyst_project_directory::~CropSyst_project_directory()
{  if (database_directory) delete database_directory; database_directory = 0;
   if (generate_scenarios_log_filename) delete generate_scenarios_log_filename; generate_scenarios_log_filename = 0; //101118
}
//_2009-05-18___________________________________________________________________
const Database_directory &CropSyst_project_directory
::provide_database_directory(bool create_if_not_exists)               provision_
{  if (!database_directory)   database_directory = new Database_directory(*this);
   if (create_if_not_exists)  database_directory->create();
   return *database_directory;
}
//_2009-05-18______________________________________provide_database_directory__/
/*160801 obsolete
#if (CS_VERSION==4)
// In version 5, There is simply a project folder, If one wants to use the GIS or watershed functions, those files will
// be added to the project and the the files will simply have the icons.
// we no longer indicates this is a change in the nature of the project.

const CORN::Smart_file_name &CropSyst_project_directory
::get_folder_icon_filename(CORN::Smart_file_name &icon_filename,int &icon_index) const
{
   //090625 obsolete in version 5 because projects are created with CS_explorer which will set up the context
   icon_index = 0;
   switch (project_type)
   {  case GIS_PROJECT        : CS::Suite_directory->qualify_icon_filename("CSGIS_project_folder.ico",icon_filename); break;
      case WATERSHED_PROJECT  : CS::Suite_directory->qualify_icon_filename("wmp.ico",icon_filename);  break;
   //NYI   case GRAZING_PROJECT    : folder_icon_filename = XXXXXX; break;
      case CROPSYST_PROJECT   :
      default                 : CS::Suite_directory->qualify_icon_filename("folder_project.ico",icon_filename); break;
   };
   return icon_filename;
}
//_2006-06_14__2005-02-02____________________________get_folder_icon_filename__/
const char *CropSyst_project_directory::get_infotip()
{  //090625 obsolete in version 5 because projects are created with CS_explorer which will set up the context
   return "CropSyst Suite project";
}
//_2006-06-14_____________________________________________________get_infotip__/
#endif
*/

#ifndef LADSS_UNIX
// not needed for LADSS
const CORN::OS::File_name_concrete &CropSyst_project_directory::get_GIS_dir_qual(bool create_if_necessary) const
{  if (create_if_necessary)   GIS_dir_qual.create();                             //051117
   return GIS_dir_qual;
}
//_2004-08-10___________________________________________________________________
void CropSyst_project_directory::set_GIS_dir(const CORN::Ustring &GIS_dir_unqual)
{  // This was provided so the user can specify the name of the GIS dir
   GIS_dir_qual.set_name(GIS_dir_unqual);
}
//_2009-11-05___________________________________________________________________
const CORN::OS::File_name_concrete &CropSyst_project_directory::get_GIS_aggregation_dir_qual(bool create_if_necessary) const
{  if (create_if_necessary)   GIS_aggregation_dir_qual.create();                 //051117
   return GIS_aggregation_dir_qual;
}
//_2004-08-10_____________________________________________________________________________
const CORN::File_name &CropSyst_project_directory::get_GIS_polygon_scenarios_filename() const
{   return get_filename(true ,"GIS_scenarios.dbf",get_GIS_dir_qual(true));
}
//_2005-02-06___________________________________________________________________
const CORN::OS::File_name_concrete &CropSyst_project_directory::get_carbon_sequestration_optimization_dir_qual(bool create_if_necessary) const
{  if (create_if_necessary) carbon_sequestration_optimization_dir_qual.create(); //051117
   return carbon_sequestration_optimization_dir_qual;
}
//_2004-08-10___________________________________________________________________
const CORN::OS::File_name_concrete &CropSyst_project_directory::get_scenario_comparison_dir_qual(bool create_if_necessary) const
{  if (create_if_necessary)   scenario_comparison_dir_qual.create();
   return scenario_comparison_dir_qual;
}
//_2007-04-23___________________________________________________________________
#endif
bool CropSyst_project_directory
::get_associated_filename(CORN::Smart_file_name &return_filename)          const //101116
{  return_filename.set_name_ext(".CS_project");
   return_filename.set_path(*this);
   bool assoc_file_exists = return_filename.exists();
/*160801 obsolete
#if (CS_VERSION==4)
   if (!return_filename.exists())
   {  // maybe its an old version 4 project file.
      return_filename.set_DEN(*this);                                            //130123
      return_filename.set_ext("csp");
      assoc_file_exists = return_filename.exists();
   };
#endif
*/
   return assoc_file_exists;
}
//_2010-11-18_________________________________________get_associated_filename__/
const CORN::Smart_file_name &CropSyst_project_directory
::generate_scenarios_log_file(const char *extension)                  provision_
{  if (!generate_scenarios_log_filename)
   {  generate_scenarios_log_filename = new CORN::Smart_file_name("generated_scenarios_log",extension);
      generate_scenarios_log_filename->set_path(*this);
   }
   return *generate_scenarios_log_filename;
}
//_2010-11-18_____________________________________generate_scenarios_log_file__/

