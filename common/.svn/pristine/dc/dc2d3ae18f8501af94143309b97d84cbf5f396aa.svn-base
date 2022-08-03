#ifndef scenario_directoryH
#define scenario_directoryH
#include "corn/OS/file_system.h"
#ifndef parameters_directory_OS_FSH
#  include "corn/parameters/parameters_directory_OS_FS.h"
#endif

// NYI this should be in CS namespace
//______________________________________________________________________________
class Common_scenario_directory
: public extends_ CORN::OS_FS::Parameters_directory                              //120202
{
   protected: bool backup_output;                                                 //131211
 protected:
   provided_ CORN::OS::File_system::Directory *scenarios_directory;
      // eventually may eventually have a specialized Scenarios_directory class.
 public: //'structors
   Common_scenario_directory
      (const CORN::OS::Directory_name &scenario_dir_name
      ,bool create_now_if_needed);                                               //130126

   virtual ~Common_scenario_directory();
 public:
   virtual const CORN::OS::File_system::Directory &Scenarios()        provision_;
   virtual const CORN::OS::File_system::Directory &Output()           provision_=0;
      // May eventually want to have a common Simulation_scenario_output_directory
 public: // literate methods
   virtual void reset()                                               provision_;
   virtual bool purge_output();                                                  //050325
};
//_2003-02-05___________________________________________________________________

#endif

