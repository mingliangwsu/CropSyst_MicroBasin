#ifndef pathsH
#define pathsH
#include "corn/const.h"
// This class can be used to get paths to cropsyst support files and
// other subdirectory trees.
#  ifndef database_directoryH
#     include "CS_suite/file_system/CS_database_directory.h"
#  endif
   using namespace CS;                                                           //121121
   using namespace CORN::OS;                                                     //121121
#ifndef parameters_datarecH
#  include "corn/parameters/parameters_datarec.h"
#endif
//______________________________________________________________________________
class  Simulation_paths
{
   class Master_simulation_parameters
   : public Common_parameters_data_record
   {
   public:
      CORN::OS::Directory_name_concrete master_simulation_dir;
   public:
      Master_simulation_parameters(nat8 _major,nat8 _release,nat8 _minor,const char *simulation_application_primary_section_name );
      inline virtual const char *get_primary_section_name()                const { return "CS_suite" ;}  // { return "-";};
      inline virtual const char *get_type_label()                          const { return "CropSyst Suite simulation paths";};
      virtual bool expect_structure(bool for_write = false);                     //170604
   };
   //___________________________________________________________________________
private:
   CORN::OS::Directory_name_concrete dir_init_buffer;  // temporary buffer used for setting up paths and filenames
public:
   CORN::OS::File_name_concrete application_ini_filename;  // I.e.    "CS_suite_4.ini"
   Master_simulation_parameters  master_simulation_parameters;
private:
   provided_ CS::Database_directory *database_directory; // 0 until setup_directory_tree Must come after directory declaration // Note: probably could go in Common_project class //090518_
   CORN::OS::Directory_name_concrete database_weather_NCDC_dir;
   CORN::OS::File_name_concrete      database_weather_NCDC_sodstn_txt;
   //   Directory_name database_weather_WMO_dir;
   CORN::OS::File_name_concrete      database_weather_NCDC_globalSOD_stnlist_sorted_txt;
   CORN::OS::Directory_name_concrete database_weather_UCAR_dir;
   CORN::OS::File_name_concrete      database_weather_UCAR_stationslib_txt;
   CORN::OS::Directory_name_concrete database_weather_Canadian_Climatological_dir;
   CORN::OS::File_name_concrete      database_weather_CC_StationCat_dbf;
   CORN::OS::Directory_name_concrete projects_dir;
public:
   Simulation_paths(nat8 _major,nat8 _release,nat8 _minor,const char *simulation_application_primary_section_name);
   void set_simulation_root(const char *);
   // I.e.   C:\Simulation
   inline const CORN::OS::Directory_name_concrete &get_simulation_dir()               { return master_simulation_parameters.master_simulation_dir;}
   inline const CORN::OS::Directory_name_concrete &get_projects_dir()                 { return projects_dir;}
   CS::Database_directory &provide_database_directory(bool create_if_necessary)provision_;
private:
   void find_and_correct_simulation_directories();
};
//______________________________________________________________________________
extern Simulation_paths *simulation_paths;
extern void setup_simulation_paths(nat8 _major,nat8 _release,nat8 _minor,const char *simulation_application_primary_section_name);
extern void setdown_simulation_paths();

#endif
//paths

