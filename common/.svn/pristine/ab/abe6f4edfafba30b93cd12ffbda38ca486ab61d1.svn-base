#  include "common/simulation/paths.h"
//#ifdef USE_OS_FS
// This class is being replaced with Simulation_directory
/*
#else
#ifdef USE_PCH
#  include "common/simulation/common_sim_pch.h"
//#  pragma hdrstop
#else
//#  pragma hdrstop
#  include "common/simulation/paths.h"
#  include "corn/data_source/vv_file.h"
#endif
*/
//#  include "common/simulation/paths.h"
//using namespace CORN;
Simulation_paths *simulation_paths = 0;
//________________________________________________________________________________/
Simulation_paths::Master_simulation_parameters::Master_simulation_parameters(nat8 _major,nat8 _release,nat8 _minor,const char *simulation_application_primary_section_name )
      : Common_parameters_data_record(
      OPTIONAL_ASSOCIATED_DIRECTORY
//NYI      _major<<16|_release<<8|_minor
      ,simulation_application_primary_section_name
      )  // Note, might use Common_parameters::directory_qual
      , master_simulation_dir(
         //_major,_release,_minor,

#ifdef _Windows
         "C:\\Simulation"
#endif
#ifdef __unix
         "~/Simulation"
#endif
         )
      {};
//_____________________________________________________________________________/
Simulation_paths::Simulation_paths(nat8 _major,nat8 _release,nat8 _minor,const char *simulation_application_primary_section_name)
: master_simulation_parameters( _major, _release, _minor,simulation_application_primary_section_name)
, database_directory(0)
, database_weather_NCDC_dir()
, database_weather_NCDC_sodstn_txt("sodstn.txt")
, database_weather_NCDC_globalSOD_stnlist_sorted_txt("globalSOD_stnlist-sorted.txt")
, database_weather_UCAR_dir()
, database_weather_UCAR_stationslib_txt("UCAR ds512.0 stationlib.txt")
, database_weather_Canadian_Climatological_dir()
, database_weather_CC_StationCat_dbf("StationCatOct20_99.dbf")
, application_ini_filename
   (simulation_application_primary_section_name,"ini")    //150929
{  set_simulation_root(master_simulation_parameters.master_simulation_dir.c_str());
//150929   application_ini_filename.set_ext("ini");
}
//_______________________________________________Simulation_paths_constructor__/
void Simulation_paths::set_simulation_root(const char *simulation_root)
{  master_simulation_parameters.master_simulation_dir.set_str(simulation_root);
   if (!master_simulation_parameters.master_simulation_dir.exists())
      find_and_correct_simulation_directories();
   master_simulation_parameters.master_simulation_dir.subdirectory_path("Projects",projects_dir,false);
   projects_dir.create();
};
//________________________________________________________set_simulation_root__/
void Simulation_paths::find_and_correct_simulation_directories()
{  char drive_designator[2]; drive_designator[1] = 0;
   bool drive_found = false;
   for (drive_designator[0]='C'; (drive_designator[0]<='Z') && !drive_found; drive_designator[0]++)
   {  master_simulation_parameters.master_simulation_dir.set_drive(drive_designator);
      if (master_simulation_parameters.master_simulation_dir.exists())
         drive_found = true;
   };
   // couldn't find the directory, just use c:
   if (!drive_found)
      drive_designator[0] = 'C';
   master_simulation_parameters.master_simulation_dir.set_drive(drive_designator);
// 090520 Not sure if this will now be relevent since we use the provide_XXX() idiom to get the database_directory
// but I need to check that the database is not provided before this point.

};
//____________________________________find_and_correct_simulation_directories__/
void Simulation_paths::Master_simulation_parameters::expect_structure(bool for_write)
{ Common_parameters_data_record ::expect_structure(for_write);
  structure_defined = false;                                                     //120314
  expect_string("master_simulation_directory",master_simulation_dir _this_name,255); //080312_
  structure_defined = true;                                                      //120314
};
//_2002-05-17____________________________________Master_simulation_parameters__/
void setup_simulation_paths(nat8 _major,nat8 _release,nat8 _minor,const char *simulation_application_primary_section_name)
{  simulation_paths = new Simulation_paths(_major,_release,_minor,simulation_application_primary_section_name);
   // Each user may specify is own master simulation folder
   // This is stored in their personal account folder

   CORN::Smart_directory_name personal_local_appdata_folder; // I think will default to CWD
   personal_local_appdata_folder.set_special_folder(0x001c /*CSIDL_LOCAL_APPDATA*/ );

   // Currently the application name and the primary section are the same string
   CORN::Smart_directory_name personal_local_application(simulation_application_primary_section_name); // "CS_suite_4");
   personal_local_application.set_path(personal_local_appdata_folder);
   personal_local_application.create();
   simulation_paths->application_ini_filename.set_path(personal_local_application);


   VV_File application_ini(simulation_paths->application_ini_filename.c_str());
   application_ini.get(simulation_paths->master_simulation_parameters);

   simulation_paths->set_simulation_root(simulation_paths->master_simulation_parameters.master_simulation_dir.c_str());
};
//_____________________________________________________setup_simulation_paths__/
void setdown_simulation_paths()
{  //    save the application ini
   VV_File application_ini(simulation_paths->application_ini_filename.c_str());
   application_ini.set(simulation_paths->master_simulation_parameters);
   delete simulation_paths;
   simulation_paths=0;
};
//___________________________________________________setdown_simulation_paths__/
Database_directory &Simulation_paths
::provide_database_directory(bool create_if_necessary)                provision_
{  if (!database_directory)
        database_directory = new Database_directory(master_simulation_parameters.master_simulation_dir);
   if (create_if_necessary)
      database_directory->create();
   return *database_directory;
};
//_2009-05-20______________________________________provide_database_directory__/
#endif

