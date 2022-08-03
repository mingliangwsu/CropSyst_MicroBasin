#ifndef CS_scenario_directoryH
#define CS_scenario_directoryH
#include "common/simulation/scenario_directory.h"
// This class organizes the directory structure of the scenario
// for both the database directory and the output directory.

// This is also used by the CropSyst sim run,
// The CropSyst scenario and CANMS output managers.
using namespace CORN;
#include "corn/OS/file_system_logical.h"
#include "CS_suite/file_system/CS_database_directory.h"
using namespace CS;

namespace CropSyst
{
// ______________________________________________________________________________
class Scenario_directory : public extends_ Common_scenario_directory
{
 protected:
   provided_ CS::Database_directory_logical *database_directory;                 //140124_090518
 public:
   CS::Database_directory_logical &Database(bool create_now_if_needed)provision_;//140124_130126_090520
   virtual void reset()                                               provision_;
   inline virtual const wchar_t *get_associated_file_extension()           const //120324
      { return L"CropSyst_scenario"; }
 public:
   // ___________________________________________________________________________
   class Output_directory : public CORN::OS::File_system_logical::Directory
  {protected:
     provided_ CORN::OS::File_name *daily_UED_filename;
     provided_ CORN::OS::File_name *season_UED_filename;
     provided_ CORN::OS::File_name *annual_UED_filename;
     provided_ CORN::OS::File_name *harvest_UED_filename;
     provided_ CORN::OS::File_name *totals_txt_filename;                         //121121
     provided_ CORN::OS::File_name *harvest_htm_filename;                        //121121
     provided_ CORN::OS::File_name *schedule_txt_filename;                       //130808

     #if (CROPSYST_VERSION == 4)
     // In V5 we do away with xls output
     provided_ CORN::OS::File_name *daily_xls_filename;                          //130827
     provided_ CORN::OS::File_name *annual_xls_filename;                         //130827
     provided_ CORN::OS::File_name *season_xls_filename;                         //130827
     provided_ CORN::OS::File_name *
        organic_matter_percents_dat_filename;                                    //130827
     provided_ CORN::OS::File_name *daily_N_xls_filename;                        //130827
     provided_ CORN::OS::File_name *annual_N_xls_filename;                       //130827
     provided_ CORN::OS::File_name *season_N_xls_filename;                       //130827
     provided_ CORN::OS::File_name *C_balance_dat_filename;                      //130827
     provided_ CORN::OS::File_name *detail_txt_filename;                         //130827
     provided_ CORN::OS::File_name *SCS_runoff_dat_filename;                     //131216
     #endif
     provided_ CORN::OS::File_name *crop_N_fate_txt_filename;                    //130827
     provided_ CORN::OS::Directory_name *Soil_dirname;                           //130827
     // Eventually I will probably want a class
     // Soil_directory derived from CORN::OS::File_system_logical::Directory
  public:
     Output_directory
        (const CORN::OS::File_system::Directory &_parent_directory
        // NYN          ,bool create_now_if_needed
        , const std::wstring &_name);
     virtual ~Output_directory();
     virtual void reset()                                            provision_;
     const CORN::OS::File_name &daily_UED()                          provision_;
     const CORN::OS::File_name &season_UED()                         provision_;
     const CORN::OS::File_name &annual_UED()                         provision_;
     const CORN::OS::File_name &harvest_UED()                        provision_;
     const CORN::OS::File_name &totals_txt()                         provision_; //121121
     const CORN::OS::File_name &harvest_htm()                        provision_; //121121
     const CORN::OS::File_name &schedule_txt()                       provision_; //130808

     #if (CROPSYST_VERSION == 4)
     // In V5 we do away with xls output
     const CORN::OS::File_name &daily_xls()                          provision_; //130827
     const CORN::OS::File_name &annual_xls()                         provision_; //130827
     const CORN::OS::File_name &season_xls()                         provision_; //130827
     const CORN::OS::File_name &organic_matter_percents_dat()        provision_; //130827
     const CORN::OS::File_name &daily_N_xls()                        provision_; //130827
     const CORN::OS::File_name &annual_N_xls()                       provision_; //130827
     const CORN::OS::File_name &season_N_xls()                       provision_; //130827
     const CORN::OS::File_name &C_balance_dat()                      provision_; //130827
     const CORN::OS::File_name &detail_txt()                         provision_; //130827
     const CORN::OS::File_name &SCS_runoff_dat()                     provision_; //131216
     #endif
     const CORN::OS::File_name &crop_N_fate_txt()                    provision_;

     const CORN::OS::Directory_name &Soil()                          provision_; //130827
  } ;
//_2012-02-02________________________________________________________________
 public: // but should be protected:
   provided_ Output_directory *output_dir;                                       //120202
 protected:
   provided_ CORN::OS::Directory_name *GIS_dirname;                              //140214
   struct
   {  struct
      {  provided_ CORN::OS::File_name_concrete *water_irrigation_management;
      } CPF;
      // This is when we are in a CPF adjusted irrigation scenario directory
      struct
      {  provided_ CORN::OS::File_name_concrete *initial;                        //150429
         provided_ CORN::OS::File_name_concrete *equilibirated;                  //150429
      } organic_matter;                                                          //150429
   } optional_resolved_filenames;
 public: // Common_scenario_directory reimplementation
   virtual const Output_directory &Output( /* NYN bool create_now_if_needed */ )provision_;
   virtual const Scenario_directory::Output_directory &CS_output()   provision_;
   virtual const CORN::OS::Directory_name &GIS()                     provision_;
 public: // 'structors
   Scenario_directory
      (const CORN::OS::Directory_name &scenario_dir_name
      , bool create_now_if_needed);                                              //130126

   #define CS_output_daily_UED_cstr    CS_output().daily_UED().c_str()
   #define CS_output_season_UED_cstr   CS_output().season_UED().c_str()
   #define CS_output_annual_UED_cstr   CS_output().annual_UED().c_str()
   #define CS_output_harvest_UED_cstr  CS_output().harvest_UED().c_str()
   #define CS_output_totals_txt_cstr   CS_output().totals_txt().c_str()
   #define CS_output_harvest_htm_cstr  CS_output().harvest_htm().c_str()
   #define CS_output_schedule_txt_cstr CS_output().schedule_txt().c_str()

   CORN::OS::File_name *
      provide_CPF_water_irrigation_management_filename_optional()     provision_;//150429
      // return 0 if no irrigation file.
   CORN::OS::Directory_name *render_crop_production_function_adjustment_percent  //150417
      (nat8 adjustment_percent)                                      rendition_;
   CORN::OS::Directory_name *render_crop_production_function_adjustment_schedule //150417
      (const std::wstring &irrigation_adjustment_file_name)          rendition_;
      // unqual no ext
   CORN::OS::File_name *
      provide_organic_matter_initial_filename_optional()              provision_;//150429
      // return 0 if no initial_organic_matter_file exists();
   CORN::OS::File_name &
      provide_organic_matter_equilibrated_filename()                  provision_;//150429
      // return 0 if no initial_organic_matter_file exists();
   CORN::OS::File_name &
      provide_organic_matter_initial_filename()                       provision_;//150429
      // return 0 if no initial_organic_matter_file exists();
   virtual ~Scenario_directory();
};
// ______________________________________________________________________________
} // namespace CropSyst
#endif
// CS_scenario_directoryH
