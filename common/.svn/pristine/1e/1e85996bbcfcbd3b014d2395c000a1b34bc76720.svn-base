#ifndef master_directoryH
#define master_directoryH
#if (CS_VERSION==4)
// This class can be used to get paths to cropsyst support files and
// other subdirectory trees.

//I think I will deprecated this in V5


#  include "corn/OS/file_system_logical.h"
#  ifndef database_directoryH
#     include "CS_suite/file_system/database_directory.h"
#  endif
#ifndef parameters_datarecH
#  include "corn/parameters/parameters_datarec.h"
#endif
namespace CS
{
class Database_directory;                                                        //120214
//______________________________________________________________________________
class  Simulation_master_directory
: public extends_ CORN::OS::File_system_logical::Directory
{
 private:
   provided_ CS::Database_directory *database_directory; // 0 until setup_directory_tree Must come after directory declaration // Note: probably could go in Common_project class //090518_
   provided_ CORN::OS::File_system::Directory *projects_dir;
 public:
   Simulation_master_directory();
   void set_simulation_root(const char *);
   // I.e.   C:\Simulation

   const CORN::OS::File_system::Directory &Projects()                 provision_;
   CS::Database_directory &Database()                                 provision_;
 private:
   void find_and_correct_simulation_directories();
};
//_2012-02-14__replaces Simulation_paths________________________________________
class Master_simulation_parameters
: public Common_parameters_data_record
{
 public:
   CORN::OS::Directory_name_concrete master_simulation_dir;
 public:
   Master_simulation_parameters
      (nat8 _major,nat8 _release,nat8 _minor
      ,const char *simulation_application_primary_section_name);
   inline virtual const char *get_primary_section_name()                   const { return "CS_suite" ;}  // { return "-";};
   inline virtual const char *get_type_label()                             const { return "CropSyst Suite simulation paths";}
   virtual void expect_structure(bool for_write = false);
};
//___________________________________________________________________________
//120214  extern Simulation_paths *simulation_paths;
Simulation_master_directory *simulation_master_directory;                        //120214
extern void setup_simulation_paths
   (nat8 _major,nat8 _release,nat8 _minor
   ,const char *simulation_application_primary_section_name);
extern void setdown_simulation_paths();
extern Master_simulation_parameters  master_simulation_parameters;
//______________________________________________________________________________
}; // namespace CS
#endif
#endif

