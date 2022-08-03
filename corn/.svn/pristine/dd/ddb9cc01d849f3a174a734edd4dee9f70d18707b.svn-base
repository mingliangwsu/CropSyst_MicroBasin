#include "invocation.h"
#include <vcl.h>
// Actually shouldn't include vcl.h but rather process stuff
#ifdef _Windows
#  include <winbase.h>
   // for SetFileAttributes
#endif
#include "corn/chronometry/date_time_64.h"
//______________________________________________________________________________
#if (__BCPLUSPLUS__ > 0x0600)
#define COMMAND_APPEND_DOUBLE_QUOTED_FILENAME(unquoted_filename)               \
   {command.append(L"\"");                                                     \
    command.append(unquoted_filename.w_str());                                 \
    command.append(L"\" "); }
#define COMMAND_APPEND_OPTIONS(options)                                        \
   {command.append(options); }
#else
#define COMMAND_APPEND_DOUBLE_QUOTED_FILENAME(unquoted_filename)               \
   {command.append("\"");                                                      \
    command.append(unquoted_filename.c_str());                                 \
    command.append("\" "); }
#define COMMAND_APPEND_OPTIONS(options)                                        \
   { CORN::append_wstring_to_string(options,command); }
#endif
//______________________________________________________________________________

namespace CORN {

//______________________________________________________________________________
class Process
: public implements_ CORN::Item
{
 public:
   //HANDLE hProc;
   PROCESS_INFORMATION  info;
   CORN::Item_wstring *queued_command; // given
 public:
   inline Process
      (CORN::Item_wstring *queued_command_)
      : CORN::Item()
      , queued_command(queued_command_)
      {}
   inline virtual ~Process()
   {
      CloseHandle(info.hProcess);
      CloseHandle(info.hThread);
   }
};
//_Process_____________________________________________________________________/
Invocation::Invocation()
: command                                                                     ()
, abort_run                                                              (false) //180114
, processes_max                                                             (16) //180326
, running_jobs_count                                                         (0) //180115
{
}
//______________________________________________________________________________
nat32 Invocation::run_program_multiple_DENS
( const CORN::OS::File_name   &program // fully qualified name of the program to run (unquoted)
, const CORN::Container       &DENs    // run program with each of the specified DENs
, const std::wstring          &options_wide
, bool                         parallel
)
{  nat32 processed_sequentially = 0;
   CORN::Date_time_clad_64 now;
   nat32 DEN_count = DENs.count();
   FOR_EACH_IN(DEN,CORN::OS::Directory_entry_name,DENs,each_DEN)
   {
      command.clear();
      command += L'"';
      program.append_components_to(command);
      command += L'"'; command += L' ';
      command.append(options_wide);
      command += L' ';
      command += L'"';
      DEN->append_components_to(command);
      command += L'"';
      if (parallel)
         command_queue.add_wstring(command);
      else
      {
         run_program_with_primary_DEN
            ( program, *DEN, options_wide
            , DEN_count > 1  // If there is only one item, just run it, don't wait
            , true, false);
         processed_sequentially++;
      }
   } FOR_EACH_END(each_DEN)
   return parallel ? DENs.count() : processed_sequentially;
}
//_run_program_multiple_DENS________________________________________2018-01-10_/


//______________________________________________________________________________
bool Invocation::run_program_with_DENs
( const CORN::OS::File_name &program            // fully qualified name of the program to run (unquoted)
, const CORN::OS::File_name *primary_file
, const CORN::OS::File_name *secondary_file
, const std::wstring &options
, bool  wait_for_termination     // True if this editor is held until the other program exits
, bool  visible
, bool options_before_filenames)                                           const
{
   command.clear();                                                              //120518
   COMMAND_APPEND_DOUBLE_QUOTED_FILENAME(program);                               //120518
   if (options_before_filenames)
      COMMAND_APPEND_OPTIONS(options);                                           //120518
   if (primary_file)
      COMMAND_APPEND_DOUBLE_QUOTED_FILENAME((*primary_file));                    //120518
   if (secondary_file)                                                           //140424
       // In the case of running scenarios,
       // if not report format is specified, the default option is
       // to use the format specified in the scenarios.
      COMMAND_APPEND_DOUBLE_QUOTED_FILENAME((*secondary_file));                  //120518
   if (!options_before_filenames)
      COMMAND_APPEND_OPTIONS(options);                                           //120518
#ifdef _Windows
   bool result = true;
   // Must save parameters after building command because secondary_file may be a temporary buffer that will get replaced.
   int nCmdShow =  visible ? SW_SHOWNORMAL	 : SW_HIDE;
      PROCESS_INFORMATION process_info;
      #if (__BCPLUSPLUS__ < 0x0600)
      STARTUPINFO startup_info;
      GetStartupInfo(&startup_info);
      startup_info.dwFlags |= STARTF_USESHOWWINDOW;
      startup_info.wShowWindow = nCmdShow;
      if (  CreateProcess
            (0
            ,(char *)command.c_str()
            ,0 // default security
            ,0 // default security
            ,true
            ,CREATE_SEPARATE_WOW_VDM|NORMAL_PRIORITY_CLASS
            ,0  // current environment block
            ,0  // pointer to current directory name  (should be current)
            ,&startup_info // pointer to STARTUPINFO
            ,&process_info // pointer to PROCESS_INFORMATION
            ))
      #else
      STARTUPINFOW startup_info;
      GetStartupInfoW(&startup_info);
      startup_info.dwFlags |= STARTF_USESHOWWINDOW;
      startup_info.wShowWindow = nCmdShow;
      if (CreateProcessW
            (0
            ,(wchar_t *)command.c_str()
            ,0 // default security
            ,0 // default security
            ,true
            ,CREATE_SEPARATE_WOW_VDM|NORMAL_PRIORITY_CLASS
            ,0  // current environment block
            ,0  // pointer to current directory name  (should be current)
            ,&startup_info // pointer to STARTUPINFO
            ,&process_info // pointer to PROCESS_INFORMATION
            ))
      #endif
      if (wait_for_termination)
      {  WaitForSingleObject(process_info.hProcess,INFINITE);
      } else result =  false;

      // Must close process and thread handles or you get a memory leak.
      CloseHandle(process_info.hProcess);
      CloseHandle(process_info.hThread);
#endif
   command_history.
#if (__BCPLUSPLUS__ > 0x0600)
      add_wstring(command);
#else
      add_string(command);
#endif
// NYI Unix
// NYI Linux
// NYI OSX   etc..
   //180128 return command;
   return result;
}
//_run_program_with_DENs____________________________________________2012-04-11_/
bool Invocation::run_program
( const CORN::OS::File_name &program            // fully qualified name of the program to run (unquoted)
, const std::wstring &options
, bool  wait_for_termination     // True if this editor is held until the other program exits
, bool  visible                  // if true, the program is run with an open visible window
                                       // Otherwise the run is hidden (if wait for termination is false, it may be run as a background process).
)                                                                          const
{  return  run_program_with_DENs
      (program, 0, 0, options, wait_for_termination, visible,false);
}
//_run_program______________________________________________________2011-04-11_/
bool Invocation
::run_program_with_primary_DEN                                                   //120411
( const CORN::OS::File_name &program            // fully qualified name of the program to run (unquoted)
, const CORN::OS::File_name &primary_file
, const std::wstring &options
, bool  wait_for_termination     // True if this editor is held until the other program exits
, bool  visible                  // if true, the program is run with an open visible window
                                       // Otherwise the run is hidden (if wait for termination is false, it may be run as a background process).
, bool options_before_filenames)                                           const
{  return  run_program_with_DENs
      (program,&primary_file,0,options,wait_for_termination,visible,options_before_filenames);
}
//_run_program_with_primary_file____________________________________2011-04-11_/
bool Invocation
::run_program_with_primary_and_secondary_DEN
( const CORN::OS::File_name &program            // fully qualified name of the program to run (unquoted)
, const CORN::OS::File_name &primary_file
, const CORN::OS::File_name &secondary_file
, const std::wstring &options
, bool  wait_for_termination     // True if this editor is held until the other program exits
, bool  visible                  // if true, the program is run with an open visible window
                                       // Otherwise the run is hidden (if wait for termination is false, it may be run as a background process).
, bool options_before_filenames)                                           const
{  return  run_program_with_DENs
      (program,&primary_file,&secondary_file,options,wait_for_termination,visible,options_before_filenames);
}
//_run_program_with_primary_and_secondary_file______________________2011-04-11_/
nat32 Invocation::update_run_queue()
{
   SYSTEM_INFO sysinfo;
   GetSystemInfo(&sysinfo);
   int CPU_count = sysinfo.dwNumberOfProcessors;

   if (abort_run)
      command_queue.delete_all();
   // http://www.informit.com/articles/article.aspx?p=1564827&seqNum=2
   nat16 started_count = 0;
   running_jobs_count = 0;

   FOR_EACH_IN(process,Process,processes,each_process)
   {  DWORD exitCode;
      bool got_exit_code = GetExitCodeProcess(process->info.hProcess, &exitCode);
      if (got_exit_code/* && exitCode==0 */)
      {  // process is finished
         if (exitCode == STILL_ACTIVE)
         {
            if (abort_run)
               TerminateProcess(process->info.hProcess,exitCode);
            else
               running_jobs_count++;
         }
         else
         {
            command_history.take(process->queued_command);
            each_process->delete_current();
         }
      }
   } FOR_EACH_END(each_process)

   nat16 process_count = processes.count();
   //nat32 free_CPU_count = numCPU - process_count;

   nat32 free_simultaneous_max  = std::min<nat32>(processes_max,(nat32)(CPU_count * 2)); //180326
      // doubling the number of processors should be an option
      // because there could be file contention (I.e. accessing NAS drive).
   nat32 free_simultaneous_count = free_simultaneous_max - process_count;


   while (free_simultaneous_count /*free_CPUS*/  && command_queue.count())
   {
      CORN::Item_wstring *command = dynamic_cast
         <CORN::Item_wstring *>(command_queue.pop_at_head());
      if (command)
      {

         Process *process = new Process(command);
         // moved to process       PROCESS_INFORMATION  process_info;
         STARTUPINFOW         startup_info;
         GetStartupInfoW(&startup_info);
         startup_info.dwFlags |= STARTF_USESHOWWINDOW;
         startup_info.wShowWindow = SW_SHOWMINIMIZED;
         if (CreateProcessW
               (0
               ,(wchar_t *)command->c_str()
               ,0 // default security
               ,0 // default security
               ,true
               ,CREATE_SEPARATE_WOW_VDM|NORMAL_PRIORITY_CLASS
               ,0  // current environment block
               ,0  // pointer to current directory name  (should be current)
               ,&startup_info // pointer to STARTUPINFO
               ,&process->info // pointer to PROCESS_INFORMATION
               ))
         {
            processes.append(process);
            started_count ++;
            free_simultaneous_count --;
            command_history.take(command);                                       //180128
         }
         else
         {  // This shouldnt occur
            delete process;  // closes handles
            delete command;
         }
      }
   }
   nat32 queued = command_queue.count();
   return started_count + queued;
}
//_update_run_queue_________________________________________________2018-01-13_/



} // namespace CORN
