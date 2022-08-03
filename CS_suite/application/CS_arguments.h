#ifndef CS_argumentsH
#define CS_argumentsH
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/OS/file_system_logical.h"
#include "corn/data_source/vv_datasrc.h"
//#include "cs_scenario.h"
#include "CS_suite/simulation/CS_identification.h"
#include "corn/application/arguments.h"
namespace CS
{
//______________________________________________________________________________
class Arguments               // Probably should rename to Arguments_scenario
: public extends_ CORN::Arguments
{
 protected:
   modifiable_ CS::Identification   &ID;
      // ref to Simulation_control::ID
 protected: // Canonical directories and filenames

   // These probably should be generalized as parameter_directory_name and parameter_file_name
   provided_ CORN::OS::Directory_name *scenario_directory_name;
   provided_ CORN::OS::File_name      *scenario_file_name;
 public:
   bool find_and_reset_missing_parameter_file_names;                             //170629
 public:
   nat16 desired_tally_statistics;                                               //170318
 public:
   Arguments(modifiable_ CS::Identification &ID_);
   virtual ~Arguments();
 public:
   virtual const CORN::OS::Directory_name &provide_scenario_directory_name()     provision_;
   virtual const CORN::OS::File_name      &provide_scenario_file_name()          provision_;
   virtual bool invalidate_scenario_directory()                   modification_; //160114
   bool is_scenario_file_named_or_found()                          affirmation_;
   const CS::Identification &ref_ID()                                     const; //151028
 private:
   inline virtual const char    *get_scenario_filename_extension_cstr()   const { return 0; }
   inline virtual const wchar_t *get_scenario_filename_extension_wstr()   const { return 0; }
 protected:
   virtual bool submit_DEN
      (CORN::OS::Directory_entry_name *param_DEN)                   submission_; //180213
};
//_2015-04-15_____________________________________________class_CS::Arguments__/
extern const CS::Arguments *global_arguments;
} // namespace CS
#endif

