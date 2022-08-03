#ifndef invocationH
#define invocationH
#include "corn/primitive.h"
//#include "corn/const.h"
#include "corn/container/text_list.h"
#include "corn/OS/directory_entry_name.h"
namespace CORN {
//______________________________________________________________________________
class Invocation
{
 protected:
   mutable std::wstring command;   // Record of the last shell command processed
 public:
   bool  abort_run;                                                              //180115
   int16 processes_max;                                                          //180326
      // can actually be nat16 once I rebuilt RNAutoControls 180326
   nat32 running_jobs_count;                                                     //180115

   contribute_ CORN::Text_list command_history;       // Records of all previous shell commands processed in this session.
      // command history should be optional, provided if needed
   //180115 contribute_ CORN::Text_list command_queue_sequential;                         //180115
   contribute_ CORN::Text_list command_queue;                                    //180114
   contribute_ CORN::Unidirectional_list processes;

 public:
   Invocation();

   nat32 run_program_multiple_DENS                                               //180110
      (const CORN::OS::File_name &program // fully qualified name of the program to run (unquoted)
      ,const CORN::Container     &DENs
      ,const std::wstring        &options
      ,bool                      parallel);
   bool run_program_with_DENs                                                    //140214_120411
      ( const CORN::OS::File_name &program            // fully qualified name of the program to run (unquoted)
      , const CORN::OS::Directory_entry_name *primary_DEN
      , const CORN::OS::Directory_entry_name *secondary_DEN
      , const std::wstring &options
      , bool  wait_for_termination     // True if this editor is held until the other program exits
      , bool  visible                  // if true, the program is run with an open visible window
                                       // Otherwise the run is hidden (if wait for termination is false, it may be run as a background process).
      , bool options_before_filenames = false)                            const;
   bool run_program_with_primary_DEN                                             //180128_140214_120411
      ( const CORN::OS::File_name &program            // fully qualified name of the program to run (unquoted)
      , const CORN::OS::Directory_entry_name &primary_DEN
      , const std::wstring &options
      , bool  wait_for_termination     // True if this editor is held until the other program exits
      , bool  visible                  // if true, the program is run with an open visible window
                                       // Otherwise the run is hidden (if wait for termination is false, it may be run as a background process).
      , bool options_before_filenames = false)                            const;
   bool run_program_with_primary_and_secondary_DEN                               //140214_120411
      ( const CORN::OS::File_name &program            // fully qualified name of the program to run (unquoted)
      , const CORN::OS::Directory_entry_name &primary_DEN
      , const CORN::OS::Directory_entry_name &secondary_DEN
      , const std::wstring &options
      , bool  wait_for_termination     // True if this editor is held until the other program exits
      , bool  visible                  // if true, the program is run with an open visible window
                                       // Otherwise the run is hidden (if wait for termination is false, it may be run as a background process).
      , bool options_before_filenames = false)                            const;
   bool run_program                                                              //120411
      ( const CORN::OS::File_name &program            // fully qualified name of the program to run (unquoted)
      , const std::wstring &options
      , bool  wait_for_termination     // True if this editor is held until the other program exits
      , bool  visible                  // if true, the program is run with an open visible window
                                       // Otherwise the run is hidden (if wait for termination is false, it may be run as a background process).
      )                                                                   const;
 public:
   nat32 update_run_queue();
   inline nat32 count_running_jobs()              { return running_jobs_count; } //180115
};
//_class_Invocation_________________________________________________2018-07-18_/
} // namespace CORN
#endif
