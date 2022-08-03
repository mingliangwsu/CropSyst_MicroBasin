#ifndef database_dirH
#define database_dirH

//120309 
#if (CROPSYST_VERSION == 5)
//#error This is being replaced by CS_Suite/file_sysem/database_directory.h

#else
#include "corn/OS/directory_entry_name_concrete.h"
using namespace CORN;
//______________________________________________________________________________
class Database_directory
: public CORN::OS::Directory_name_concrete                                       //150912
{
private:
   provided_ CORN::OS::Directory_name *crop_directory;
   provided_ CORN::OS::Directory_name *output_directory;
   provided_ CORN::OS::Directory_name *soil_directory;
   provided_ CORN::OS::Directory_name *weather_directory;
   provided_ CORN::OS::Directory_name *management_directory;
   provided_ CORN::OS::Directory_name *biomatter_directory;
   provided_ CORN::OS::Directory_name *rotation_directory;
   provided_ CORN::OS::Directory_name *format_directory;
   provided_ CORN::OS::Directory_name *recalibration_directory;
   provided_ CORN::OS::Directory_name *water_table_directory;
   provided_ CORN::OS::Directory_name *initialization_directory;
   provided_ CORN::OS::Directory_name *initialization_H2O_directory;
   provided_ CORN::OS::Directory_name *initialization_NO3_directory;
   provided_ CORN::OS::Directory_name *initialization_NH4_directory;
   provided_ CORN::OS::Directory_name *initialization_OM_directory;
   provided_ CORN::OS::Directory_name *STATSGO_states_directory;
public:
   Database_directory(const CORN::OS::Directory_name &simulation_project_or_scenario_dir);
   virtual ~Database_directory();
protected:
    CORN::OS::Directory_name *provide_XXXX_directory                  (const char *subdir_name,bool create_if_doesnt_exist)provision_;
    CORN::OS::Directory_name *provide_initialization_XXXX_directory   (const char *subdir_name,bool create_if_doesnt_exist)provision_;
public:
   // will append drive separator if necessary (may be with or without colon :)

   const CORN::OS::Directory_name &provide_crop_directory                (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_output_directory              (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_soil_directory                (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_weather_directory             (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_management_directory          (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_biomatter_directory           (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_rotation_directory            (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_format_directory              (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_recalibration_directory       (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_water_table_directory         (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_initialization_directory      (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_initialization_H2O_directory  (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_initialization_NO3_directory  (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_initialization_NH4_directory  (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_initialization_OM_directory   (bool create_if_doesnt_exist)provision_;
   const CORN::OS::Directory_name &provide_STATSGO_states_directory(bool create_if_doesnt_exist)provision_;
};
//_2009-05-18___________________________________________________________________
#endif
#endif
//database_dir.h

