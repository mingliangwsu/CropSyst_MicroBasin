#error this file has been moved to the application directory
Delete this file after 2018

#include "CS_suite/application/CS_arguments.h"
#include "common/simulation/scenario.h"
#include "corn/data_source/vv_file.h"
#include "corn/OS/file_system_engine.h"
#include "corn/math/statistical/statistics_types.h"
#include <string.h>
namespace CS
{
const CS::Arguments *global_arguments = 0;                                       //180305
//______________________________________________________________________________
Arguments::Arguments
(modifiable_ CS::Identification   &ID_)
: CORN::Arguments()                                                              //160826
, ID                       (ID_)                                                 //160222
, scenario_directory_name  (0)
, scenario_file_name       (0)
, find_and_reset_missing_parameter_file_names(false)                             //170629
, desired_tally_statistics (STAT_BASIC_ELEMENTS_INIT_FINAL_bits)                 //170413
{
   //160222 moved for (int a = 0; a < 1000; a++) arg_recognized[a] = 0;
   // By default the CWD is assumed to be the scenario directory
   // If any directory name is specified on the command line
   // that will be assumed to be the scenario directory
     // When no command line arguments then use CWD as default scenario directory

}
//_2015-04-15___________________________________________________________________
/*180213
bool Arguments::recognize_DEN
(const CORN::OS::Directory_entry_name &potential_scenario_DEN)     modification_
{
   bool recognized = false;

      CORN::OS::Directory_entry_type arg_file_system_type
         = CORN::OS::file_system_engine.identify_type(potential_scenario_DEN);
      switch (arg_file_system_type)
      {  case CORN::OS::directory_entry :
         {
            delete scenario_directory_name; // overriding default (CWD)
            scenario_directory_name =
               new CORN::OS::Directory_name_concrete(potential_scenario_DEN);
            //170626 potential_scenario_DEN = 0;
            recognized = true;
         } break;
         case CORN::OS::file_entry :
         {
            bool is_scenario_filename
               = potential_scenario_DEN.has_extension_ASCII(get_scenario_filename_extension_cstr(),false)
               ||potential_scenario_DEN.has_extension_Unicode(get_scenario_filename_extension_wstr(),false);
            is_scenario_filename
               |= potential_scenario_DEN.get_name().find
                  (get_scenario_filename_extension_wstr())!=std::string::npos;
            if (is_scenario_filename)
            {
               //170626 scenario_file_name = potential_scenario_DEN;
               scenario_file_name = new CORN::OS::File_name_concrete(potential_scenario_DEN);
               delete scenario_directory_name;                                   //160312
               scenario_directory_name = new CORN::OS::Directory_name_concrete   //160312
                  (scenario_file_name->get_path_directory_name()->c_str()        //161201
                  ,CORN::OS::directory_entry);                                   //161029
               recognized = true;
            }
         } break;
      } // switch
   return recognized || CORN::Arguments::recognize_DEN(potential_scenario_DEN);
}
//_2017-06-26___________________________________________________________________
*/
bool Arguments::submit_DEN
( CORN::OS::Directory_entry_name *potential_scenario_DEN)            submission_
{
   bool recognized = false;
   CORN::OS::Directory_entry_type arg_file_system_type
      = CORN::OS::file_system_engine.identify_type(*potential_scenario_DEN);
   switch (arg_file_system_type)
   {  case CORN::OS::directory_entry :
      {
         delete scenario_directory_name; // overriding default (CWD)
         scenario_directory_name = potential_scenario_DEN;
         recognized = true;
      } break;
      case CORN::OS::file_entry :
      {
         bool is_scenario_filename
            = potential_scenario_DEN->has_extension_ASCII(get_scenario_filename_extension_cstr(),false)
            ||potential_scenario_DEN->has_extension_Unicode(get_scenario_filename_extension_wstr(),false);
         is_scenario_filename
            |= potential_scenario_DEN->get_name().find
               (get_scenario_filename_extension_wstr())!=std::string::npos;
         if (is_scenario_filename)
         {
            scenario_file_name = potential_scenario_DEN;
            delete scenario_directory_name;
            scenario_directory_name = new CORN::OS::Directory_name_concrete
               (scenario_file_name->get_path_directory_name()->c_str()
               ,CORN::OS::directory_entry);
            recognized = true;
         }
      } break;
   } // switch
   return recognized || CORN::Arguments::submit_DEN(potential_scenario_DEN);
}
//_2018-02-13___________________________________________________________________
Arguments::~Arguments()
{
   if(scenario_directory_name) delete scenario_directory_name;  scenario_directory_name                = 0;
   if(scenario_file_name) delete scenario_file_name;       scenario_file_name                     = 0;
}
//_2015-04-15___________________________________________________________________
const CORN::OS::Directory_name &Arguments::provide_scenario_directory_name() provision_
{  if (!scenario_directory_name)
   {  if (scenario_file_name)
      {  const CORN::OS::Directory_name *scenario_file_path = scenario_file_name->get_path_directory_name();
         if (scenario_file_path) // The scenario file is qualified
            scenario_directory_name = new CORN::OS::Directory_name_concrete(*scenario_file_path,CORN::OS::directory_entry); //161028
      } else
      // provide_scenario_file_name may identify the scenario directory if given the scenario filename
      if (!scenario_directory_name)
         // we still dont have the scenario directory name assume CWD
         scenario_directory_name = new CORN::OS::Directory_name_concrete(/*NYI CORN::OS::directory_entry*/); //161028
   }
   return *scenario_directory_name;
}
//_2015-04-15___________________________________________________________________
const CORN::OS::File_name &Arguments::provide_scenario_file_name()     provision_
{  if (!scenario_file_name)
   { // scenario file was not specified on the command line search update the directory tree
      scenario_file_name = dynamic_cast<CORN::OS::File_name_concrete*>(CORN::OS::file_system_engine.find_qualified_name_in_path
         (get_scenario_filename_extension_wstr()
         ,provide_scenario_directory_name()));
   // Now we search for the scenario file in the scenario directory
   // or any parent directory (this is used for GIS and/or
   // other multiple runs where the template scenarios may be in a parent
   // directory. 140210
      if (!scenario_file_name)                                                   //160120
         scenario_file_name = new CORN::OS::File_name_concrete
            (provide_scenario_directory_name()
            ,get_scenario_filename_extension_wstr());
   }
   return *scenario_file_name;
}
//_2015-04-15___________________________________________________________________
bool Arguments::invalidate_scenario_directory()                    modification_
{
   delete scenario_directory_name;  scenario_directory_name = 0;
   delete scenario_file_name;       scenario_file_name = 0;
   return true;
}
//_2016-01-14___________________________________________________________________
bool Arguments::is_scenario_file_named_or_found()                   affirmation_
{  provide_scenario_file_name();
   return CORN::OS::file_system_engine.exists(*scenario_file_name);
}
//_2015-04-15___________________________________________________________________
const CS::Identification &Arguments::ref_ID()                              const
{  return ID;                                                                    //160222
}
//_2015-10-28___________________________________________________________________


} // namespace CS


