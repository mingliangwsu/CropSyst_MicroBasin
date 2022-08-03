
// I want to rename this file to CropSyst_arguments (namespace first)

#ifndef arguments_CropSystH
#define arguments_CropSystH
#include "CS_suite/application/CS_arguments.h"
#include "cs_scenario_directory.h"
#include "CS_suite/simulation/CS_simulation_control.h"
namespace CropSyst
{
extern bool LADSS_mode;
extern bool batch_mode;                                                          //010202
class Scenario;
//______________________________________________________________________________
class Arguments
: public extends_ CS::Arguments
{
 protected: // Optional filenames found in the scenario directory.
   // The files may either be actual files or symbolic links.
   // If symbolic links then resolve the filename.

   provided_ CropSyst::Scenario_directory *scenario_directory;

 public: // structors
   Arguments
      (CS::Identification &ID_);                                                 //160222
   Arguments
      (CS::Identification &ID_                                                   //160222
      ,int32 cell_ID, int32 crop_index); // Constructor of VIC_CropSyst
   virtual ~Arguments();
 public: // accessors
   inline virtual const char    *get_scenario_filename_extension_cstr()    const { return  "CropSyst_scenario";}
   inline virtual const wchar_t *get_scenario_filename_extension_wstr()    const { return L"CropSyst_scenario";}
   CropSyst::Scenario_directory &provide_scenario_directory()        provision_;
   bool invalidate_scenario_directory()                           modification_;//160114
      // This should force reset of scenario_directory
   inline virtual bool get_author_mailto_URI(std::string &email_URI)       const { email_URI.assign("rnelson@wsu.edu"); return true;};
   virtual bool get_program_version(std::string &version)                 const;
 protected:
   /*180213
   virtual bool recognize_DEN                                                    //160626
      (const CORN::OS::Directory_entry_name &param_DEN)           modification_;
   */
   virtual bool submit_DEN
      (CORN::OS::Directory_entry_name *param_DEN)                   submission_; //180213
};
//_2015-04-15___________________________________________________________________
class Arguments_V4
: public extends_ Arguments
{
   CORN::OS::File_name/*180213 _concrete*/ *format_filename;                     //050325
   //180213 std::string
   CORN::OS::File_name *GIS_override_table;                                      //180213
      // In V5 we now use scenario generator
 public: // structors
   Arguments_V4(CS::Identification &ID_);                                        //160222
 public:
   inline const CORN::OS::File_name /*180213 _concrete*/ *
      get_override_format_file_name()                                 provision_
      { return format_filename; }
   virtual bool get_program_version(std::string &version)                 const;
 protected:
   virtual bool recognize
      (const std::string &curr_arg)                               modification_;
   /*180213
   virtual bool recognize_DEN
      (const CORN::OS::Directory_entry_name &param_DEN)           modification_;
   */
   virtual bool submit_DEN
      (CORN::OS::Directory_entry_name *param_DEN)                   submission_; //180213
};
//_2015-04-15___________________________________________________________________
} // namespace CropSyst

#endif



