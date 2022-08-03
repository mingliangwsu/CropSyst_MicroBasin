#include "common/simulation/scenario_directory.h"
#include "corn/OS/file_system_engine.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <string.h>
using namespace std;
//______________________________________________________________________________
Common_scenario_directory::Common_scenario_directory
(const CORN::OS::Directory_name  &scenario_dir_name_given
,bool create_now_if_needed)                                                      //130126
:CORN::OS_FS::Parameters_directory
   (scenario_dir_name_given
   ,CORN::OS::directory_entry                                                    //130831
   ,create_now_if_needed)                                                        //130126_120204
,scenarios_directory(0)                                                          //120204
, backup_output(true)                                                            //131211
{}
//______________________________________________________________________________
bool Common_scenario_directory::purge_output()
{  bool purged = true;
   if (CORN::OS::file_system_engine.exists(Output()))
   {
      /* disabled this because creating too many backups
      // Any backup should be done by CS explorer and/or scenario editor
      if (backup_output)                                                         //131211
      {
      CORN::OS::File_name_concrete schedule_txt_filename(Output(),"schedule.txt");
      // Actually I should get any arbitrary file in the Output directory (schedule.txt might not always be present in other scenarios
      CORN::Date_time_64 original_date(CORN::OS::file_system_engine.get_modification_date_time(schedule_txt_filename));
      char datestr[20];
      original_date.set_format(D_YMD,D_YYYY|D_M|D_lead_zero,'-');

      strcpy(datestr,original_date.c_str());
      original_date.set_format_string(TF_HHMM);
      std::string no_colons(datestr);
      CORN::replace_character(no_colons,':','.');
      CORN::replace_character(no_colons,' ','T');
      std::string output_now_name("Output_"); output_now_name.append(no_colons);
      CORN::OS::File_name_concrete output_now_dirname(Output().get_parent_directory_name_qualifiedX(),output_now_name);;
      CORN::OS::file_system_engine.rename(Output(),output_now_dirname);
      #ifdef _WIN32
         Sleep(1000);
      #endif
      } else
      */
      CORN::OS::file_system_engine.delete_directory(Output(),true);
   }
   Output().create();                                                            //131010
   return purged;
}
//_2005-03-25___________________________________________________________________
Common_scenario_directory::~Common_scenario_directory()
{  reset();
}
//_2012-02-07___________________________________________________________________
void Common_scenario_directory::reset()                               provision_
{  delete scenarios_directory; scenarios_directory = 0;
}
//_2012-02-07___________________________________________________________________
const CORN::OS::File_system::Directory &Common_scenario_directory::Scenarios() provision_
{  if (!scenarios_directory)
   {
      // NYI Instead of searching for directory names
      // I should search for Scenarios context indicator
      std::wstring scenarios_name(L"Scenarios");
      CORN::OS::Directory_name *scenarios_dir_name = find_directory_name_in_path
         (scenarios_name,true,false);
      if (scenarios_dir_name)
         scenarios_directory = new CORN::OS::File_system_logical::Directory
            (*scenarios_dir_name,false);
   }
   return *scenarios_directory;
}
//_2012-02-07___________________________________________________________________

