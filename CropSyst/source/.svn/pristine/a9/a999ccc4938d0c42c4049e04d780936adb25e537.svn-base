#error check_obsolete

#if (defined(USE_OS_FS) || (CROPSYST_VERSION == 5))
//#error This is being replaced by CS_Suite/files_sysem/database_directory.h
#else
#include "database_dir.h"
//______________________________________________________________________________
Database_directory::Database_directory(const CORN::OS::Directory_name &simulation_project_or_scenario_dir)
: CORN::OS::Directory_name_concrete     ("Database")
, crop_directory                 (0)
, output_directory               (0)
, soil_directory                 (0)
, weather_directory              (0)
, management_directory           (0)
, biomatter_directory            (0)
, rotation_directory             (0)
, format_directory               (0)
, recalibration_directory        (0)
, water_table_directory          (0)
, initialization_directory       (0)
, initialization_H2O_directory   (0)
, initialization_NO3_directory   (0)
, initialization_NH4_directory   (0)
, initialization_OM_directory    (0)
, STATSGO_states_directory (0)
{
   set_path(simulation_project_or_scenario_dir);                                 //090615
};
//______________________________________________________________________________
Database_directory::~Database_directory()
{  delete crop_directory                  ;
   delete output_directory                ;
   delete soil_directory                  ;
   delete weather_directory               ;
   delete management_directory            ;
   delete biomatter_directory             ;
   delete rotation_directory              ;
   delete format_directory                ;
   delete recalibration_directory         ;
   delete water_table_directory;          ;
   delete initialization_directory        ;
   delete initialization_H2O_directory    ;
   delete initialization_NO3_directory    ;
   delete initialization_NH4_directory    ;
   delete initialization_OM_directory     ;
   delete STATSGO_states_directory  ;
};
//______________________________________________________________________________
CORN::OS::Directory_name *Database_directory::provide_XXXX_directory                (const char *subdir_name,bool create_if_doesnt_exist)provision_
{
   CORN::OS::Directory_name *XXX_dir = new CORN::OS::Directory_name(subdir_name);
   XXX_dir->set_path(*this);                                                     //090614
   if (create_if_doesnt_exist)
      XXX_dir->create();        // Note that we don't need to check if the directory already exists because create() does.
   return XXX_dir;
};
//_____________________________________________________provide_XXXX_directory__/

#define PROVIDE_XXX_DIRECTORY(provide_XXX_directory,directory_name,XXX_dir)    \
const CORN::OS::Directory_name &Database_directory::provide_XXX_directory          \
(bool create_if_doesnt_exist)provision_                                         \
{  if (XXX_dir == NULL)                                                        \
   XXX_dir = provide_XXXX_directory(directory_name,create_if_doesnt_exist);    \
   return *XXX_dir;                                                            \
};
//_____________________________________________________provide_XXX_directory__/
PROVIDE_XXX_DIRECTORY(provide_crop_directory                ,"Crop"           ,crop_directory)
PROVIDE_XXX_DIRECTORY(provide_output_directory              ,"Output"         ,output_directory)
PROVIDE_XXX_DIRECTORY(provide_soil_directory                ,"Soil"           ,soil_directory)
PROVIDE_XXX_DIRECTORY(provide_weather_directory             ,"Weather"        ,weather_directory)
PROVIDE_XXX_DIRECTORY(provide_management_directory          ,"Management"     ,management_directory)
PROVIDE_XXX_DIRECTORY(provide_biomatter_directory           ,"Biomatter"      ,biomatter_directory)
PROVIDE_XXX_DIRECTORY(provide_rotation_directory            ,"Rotation"       ,rotation_directory)
PROVIDE_XXX_DIRECTORY(provide_format_directory              ,"Format"         ,format_directory)
PROVIDE_XXX_DIRECTORY(provide_recalibration_directory       ,"recalibration"  ,recalibration_directory)
PROVIDE_XXX_DIRECTORY(provide_water_table_directory         ,"water_table"    ,water_table_directory)
PROVIDE_XXX_DIRECTORY(provide_initialization_directory      ,"initialization" ,initialization_directory)
//_____________________________________________________________________________/
CORN::OS::Directory_name *Database_directory::provide_initialization_XXXX_directory                (const char *subdir_name,bool create_if_doesnt_exist)provision_
{  provide_initialization_directory(true);
   CORN::OS::Directory_name *XXX_dir = new CORN::OS::Directory_name(subdir_name);
   if (create_if_doesnt_exist)
      XXX_dir->create();        // Note that we don't need to check if the directory already exists because create() does.
   return XXX_dir;
};
//_____________________________________________________provide_XXXX_directory__/
#define PROVIDE_INITIALIZATION_XXX_DIRECTORY(provide_initialization_XXX_directory,directory_name,XXX_dir)    \
const CORN::OS::Directory_name &Database_directory::provide_initialization_XXX_directory          \
(bool create_if_doesnt_exist)provision_                                         \
{  if (XXX_dir == NULL)                                                        \
   XXX_dir = provide_initialization_XXXX_directory(directory_name,create_if_doesnt_exist);    \
   return *XXX_dir;                                                            \
};
//_____________________________________________________provide_XXX_directory__/
PROVIDE_INITIALIZATION_XXX_DIRECTORY(provide_initialization_H2O_directory ,"H2O",  initialization_H2O_directory)
PROVIDE_INITIALIZATION_XXX_DIRECTORY(provide_initialization_NO3_directory ,"NO3",  initialization_NO3_directory)
PROVIDE_INITIALIZATION_XXX_DIRECTORY(provide_initialization_NH4_directory ,"NH4",  initialization_NH4_directory)
PROVIDE_INITIALIZATION_XXX_DIRECTORY(provide_initialization_OM_directory  ,"OM",   initialization_OM_directory)
//_____________________________________________________provide_XXX_directory__/
const CORN::OS::Directory_name &Database_directory::provide_STATSGO_states_directory      (bool create_if_doesnt_exist)provision_
{
   if (STATSGO_states_directory == NULL)
   {  STATSGO_states_directory = new CORN::OS::Directory_name;
      subdirectory_path("STATSGO\\DOS\\arc\\data",*STATSGO_states_directory);
   };
   if (create_if_doesnt_exist)
      STATSGO_states_directory->create();        // Note that we don't need to check if the directory already exists because create() does.
   return *STATSGO_states_directory;
};
//___________________________________________provide_STATSGO_states_directory__/
#ifdef OBSOLETE
void Database_directory_paths::reset_root(const CORN::OS::Directory_name &simulation_project_or_scenario_dir)
{
   dir               .set_path(simulation_project_or_scenario_dir);
   crop_dir          .set_path(dir);
   output_dir        .set_path(dir);
   soil_dir          .set_path(dir);
   weather_dir       .set_path(dir);
   management_dir    .set_path(dir);
   biomatter_dir     .set_path(dir);
   rotation_dir      .set_path(dir);
   format_dir        .set_path(dir);
   recalibration_dir .set_path(dir);
   water_table_dir   .set_path(dir);
   initialization_dir.set_path(dir);
   initialization_H2O_dir.set_path(initialization_dir);
   initialization_NO3_dir.set_path(initialization_dir);
   initialization_NH4_dir.set_path(initialization_dir);
   initialization_OM_dir .set_path(initialization_dir);
   dir.subdirectory_path("STATSGO\\DOS\\arc\\data",STATSGO_states_directory);
};
//______________________________________________________________________________
void  Database_directory_paths::create_all_folders()
{  crop_dir.create();
   output_dir.create();
   soil_dir.create();
   weather_dir.create();
   management_dir.create();
   biomatter_dir.create();
   rotation_dir.create();
   recalibration_dir.create();
   water_table_dir.create();
   initialization_dir.create();
   initialization_H2O_dir.create();
   initialization_NO3_dir.create();
   initialization_NH4_dir.create();
   initialization_OM_dir.create();
   format_dir.create();
   STATSGO_states_directory.create();
};
//______________________________________________________________________________
void Database_directory_paths::set_drive(const char *drive_name)
{
   dir.set_drive(drive_name);
   crop_dir.set_drive(drive_name);
   output_dir.set_drive(drive_name);
   soil_dir.set_drive(drive_name);
   weather_dir.set_drive(drive_name);
   management_dir.set_drive(drive_name);
   biomatter_dir.set_drive(drive_name);
   rotation_dir.set_drive(drive_name);
   format_dir.set_drive(drive_name);
   recalibration_dir.set_drive(drive_name);
   water_table_dir.set_drive(drive_name);
   initialization_dir.set_drive(drive_name);
   STATSGO_states_directory.set_drive(drive_name);
};
//______________________________________________________________________________
#endif
#endif
