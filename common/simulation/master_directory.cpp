#  include "common/simulation/master_directory.h"
namespace CS
{
//________________________________________________________________________________/
Simulation_master_directory::Master_simulation_parameters  master_simulation_parameters           //120214
(CS_VERSION_NUMBERS,"CS_suite");
//_____________________________________________________________________________/
Simulation_master_directory::Simulation_master_directory()
: CORN::OS::File_system_logical::Directory()
, database_directory(0)
, projects_dir      (0)
{  set_simulation_root(master_simulation_parameters.master_simulation_dir.c_str());
   application_ini_filename.set_ext("ini");
}
//_______________________________________________Simulation_paths_constructor__/
void Simulation_master_directory::set_simulation_root(const char *simulation_root)
{  master_simulation_parameters.master_simulation_dir.set(simulation_root);
   if (!master_simulation_parameters.master_simulation_dir.exists())
      find_and_correct_simulation_directories();
   master_simulation_parameters.master_simulation_dir.subdirectory_path("Projects",projects_dir,false);
   projects_dir.create();
}
//________________________________________________________set_simulation_root__/
void Simulation_master_directory::find_and_correct_simulation_directories()
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

}
//____________________________________find_and_correct_simulation_directories__/
void setup_simulation_paths(nat8 _major,nat8 _release,nat8 _minor,const char *simulation_application_primary_section_name)
{  simulation_paths = new Simulation_master_directory(_major,_release,_minor,simulation_application_primary_section_name);
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
   application_ini.get(master_simulation_parameters);

   simulation_paths->set_simulation_root(simulation_paths->master_simulation_parameters.master_simulation_dir.c_str());
}
//_____________________________________________________setup_simulation_paths__/
extern void setdown_simulation_paths()
{  //    save the application ini
   VV_File application_ini(simulation_paths->application_ini_filename.c_str());
   application_ini.set(simulation_paths->master_simulation_parameters);
   delete simulation_paths;
   simulation_paths=0;
}
//___________________________________________________setdown_simulation_paths__/
CS::Database_directory &Simulation_master_directory::database()       provision_
{
   if (!database_directory)
        database_directory = new CS::Database_directory(master_simulation_parameters.master_simulation_dir);
   if (create_if_necessary)
      database_directory->create();
   return *database_directory;
}
//_2009-05-20______________________________________provide_database_directory__/
} // namespace CS
