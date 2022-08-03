#ifndef project_directory_CropSystH
#define project_directory_CropSystH
#include "common/simulation/simulation_project_directory.h"
#include "project_types.h"
#include "options.h"
namespace CS
{
   class Database_directory_paths;
   class Database_directory_logical;
}
namespace CropSyst {
//______________________________________________________________________________
class Project_directory
: public CS::Project_directory  
{
 public:
   #ifndef REACCH_VERSION
   Project_directory
      (const wchar_t *associated_parameters_filename,bool create_now_if_needed);
   #endif
   Project_directory                                                             //100209
      (const CORN::OS::Directory_name &dir_name,bool create_now_if_needed);
   virtual ~Project_directory();                                                 //090518
//NYI/*020411_*/    virtual uint16 get_section_entry_changes(Section_entry_change **changes) const;
   // If the derived class has a new version with renamed sections and entries
   // it should override this method to return the table of changes
   // The return value is the number of changes in the table.
 private: // directories                                                         //020426
   provided_ CS::Database_directory_logical *database_directory;                         //090518
               // 0 until setup_directory_tree Must come after directory declaration // Note: probably could go in Common_project class
 public: // directories
   const CS::Database_directory_logical &database(bool create_if_not_exists) provision_; //130118
   inline const CS::Database_directory_logical &provide_database_directory
      //deprecated, replaced with database()
      (bool create_if_not_exists)                                      provision_//090518
      { return database( create_if_not_exists); }
   inline virtual const wchar_t *get_associated_file_extension()           const { return L".CS_project"; } //120326
#ifndef LADSS_UNIX
// not needed for LADSS
 private: // GIS files/folders                                                   //040810
   provided_ CORN::OS::Directory_name_concrete *GIS_dirname;                      //050203
   provided_ CORN::OS::Directory_name_concrete *GIS_aggregation_dirname;          //050930
   provided_ CORN::OS::File_name_concrete      *selected_scenarios_fname;
      // This is the name of the files selected for batch run                    //060710
   provided_ CORN::OS::File_name_concrete      *GIS_polygon_scenarios_fname;
   provided_ const CORN::OS::File_name        *scenario_comparison_fname;        //050930
   provided_ CORN::OS::Directory_name_concrete *carbon_sequestration_optimization_dirname; //020426
   provided_ CORN::OS::File_name_concrete      *generate_scenarios_log_fname;
 public:                                                                         //040810
   const CORN::OS::Directory_name &GIS(bool create=true)               provision_;//120321_040810
      //was get_GIS_dir_qual()
   const CORN::OS::Directory_name &GIS_aggregation()                   provision_;//120321_050930
      //was get_GIS_aggregation_dir_qual
   const CORN::OS::File_name      &GIS_polygon_scenarios_filename()    provision_;//050206
   const CORN::OS::File_name  &generate_scenarios_log(const wchar_t *extension) provision_; //101118
 private: // Carbon sequestration files/folders
 public:                                                                         //040810
   const CORN::OS::Directory_name &carbon_sequestration_optimization() provision_;
   const CORN::OS::File_name      &selected_scenarios_filename()       provision_;//060710
   const CORN::OS::Directory_name &scenario_comparison_filename()      provision_;//070423
#endif
};
//______________________________________________________________________________
} // namespace CropSyst
#endif

