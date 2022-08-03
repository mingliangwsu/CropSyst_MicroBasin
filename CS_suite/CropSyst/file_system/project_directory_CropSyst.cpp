#include "project_directory_CropSyst.h"
#include "CS_suite/file_system/CS_database_directory.h"
#include "CS_suite/application/CS_suite_directory.h"
namespace CropSyst {
//______________________________________________________________________________
#ifndef REACCH_VERSION
#ifdef CHECK_NEEDED
// I am not sure if this is needed anymore because projects are now defined by directories
Project_directory::Project_directory
(const wchar_t *cropsyst_project_filename,bool create_now_if_needed)
: Common_simulation_project_directory(cropsyst_project_filename,create_now_if_needed)
, database_directory(0)                                                          //090518
#ifndef __linux__
, generate_scenarios_log_fname(0)                                                //101118
#endif
#ifndef LADSS_UNIX
, GIS_dirname(0)
, GIS_aggregation_dirname(0)
, selected_scenarios_fname(0) //("selected_scenarios.dat")                                   //060710
, GIS_polygon_scenarios_fname(0)
, scenario_comparison_fname(0)
, carbon_sequestration_optimization_dirname(0)
#endif
{}
#endif
#endif
//______________________________________________________________________________
Project_directory::Project_directory
(const CORN::OS::Directory_name &dir_name,bool create_now_if_needed)
: CS::Project_directory (dir_name,create_now_if_needed)                          //140214
, database_directory(0)                                                          //090518
#ifndef __linux__
, generate_scenarios_log_fname(0)                                                //101118
#endif
#ifndef LADSS_UNIX
, GIS_dirname(0)
, GIS_aggregation_dirname(0)
, selected_scenarios_fname(0) //("selected_scenarios.dat")                                   //060710
, GIS_polygon_scenarios_fname(0)
, scenario_comparison_fname(0)
, carbon_sequestration_optimization_dirname(0)
#endif
{}
//_2010-02-09__2005-02-03_________________________________________constructor__/
Project_directory::~Project_directory()
{
#ifndef __linux__
   delete generate_scenarios_log_fname;
#endif
   delete database_directory;
   delete GIS_dirname;
   delete GIS_aggregation_dirname;
   delete selected_scenarios_fname;
   delete GIS_polygon_scenarios_fname;
   delete scenario_comparison_fname;
   delete carbon_sequestration_optimization_dirname;
}
//_2009-05-18___________________________________________________________________
const CS::Database_directory_logical &Project_directory
::database(bool create_if_not_exists)                                 provision_ //130118
{  if (!database_directory)   database_directory = new CS::Database_directory_logical(*this,L"Database");
   if (create_if_not_exists)  database_directory->create();
   return *database_directory;
}
//_2009-05-18______________________________________provide_database_directory__/
#ifndef LADSS_UNIX
const CORN::OS::Directory_name &Project_directory::GIS(bool create)   provision_ //120321_040810
{
   if (!GIS_dirname)
      GIS_dirname = new CORN::OS::Directory_name_concrete(GIS(),L"GIS",CORN::OS::directory_entry); //161029
   return *GIS_dirname;
}
//_2015-07-23__________________________________________________________________/
const CORN::OS::Directory_name &Project_directory::GIS_aggregation()  provision_
{  if (!GIS_aggregation_dirname)
      GIS_aggregation_dirname = new CORN::OS::Directory_name_concrete(GIS(),L"aggregation",CORN::OS::directory_entry); //161029
   return *GIS_aggregation_dirname;
}
//_2012-03-24__2004-08-10______________________________________________________/
const CORN::OS::File_name &Project_directory::GIS_polygon_scenarios_filename() provision_
{  if (!GIS_polygon_scenarios_fname)
      GIS_polygon_scenarios_fname = new CORN::OS::File_name_concrete(GIS(),"LGIS_scenarios.dbf");
   return *GIS_polygon_scenarios_fname;
}
//_2005-02-06___________________________________________________________________
const CORN::OS::Directory_name &Project_directory::carbon_sequestration_optimization()   provision_
{  if (!carbon_sequestration_optimization_dirname)
      carbon_sequestration_optimization_dirname = new CORN::OS::Directory_name_concrete(*this,"Carbon_sequestration_optimization",CORN::OS::directory_entry); //161029
   return *carbon_sequestration_optimization_dirname;
}
//_2004-08-10___________________________________________________________________
const CORN::OS::Directory_name &Project_directory::scenario_comparison_filename()  provision_
{  if (!scenario_comparison_fname)
      scenario_comparison_fname = new CORN::OS::Directory_name_concrete(*this,"scenario_comparison",CORN::OS::directory_entry); //161029
   return *scenario_comparison_fname;
}
//_2007-04-23___________________________________________________________________
#endif
const CORN::OS::File_name &Project_directory::generate_scenarios_log(const wchar_t *extension) provision_
{  if (!generate_scenarios_log_fname)
      generate_scenarios_log_fname= new CORN::OS::File_name_concrete(*this,L"generated_scenarios_log",extension);
   return *generate_scenarios_log_fname;
}
//_2010-11-18_____________________________________generate_scenarios_log_file__/
} // namespace CropSyst

