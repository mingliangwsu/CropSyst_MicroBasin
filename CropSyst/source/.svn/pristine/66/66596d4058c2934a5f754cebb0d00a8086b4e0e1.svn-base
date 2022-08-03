#include "arguments_CropSyst.h"
#include <string.h>

namespace CropSyst
{
bool LADSS_mode = false;
//______________________________________________________________________________
Arguments::Arguments
(CS::Identification &ID_)                                                        //160222
: CS::Arguments      (ID_)                                                       //160222
, scenario_directory (0)
{}
//_2015-04-15___________________________________________________________________
Arguments::Arguments
(CS::Identification &ID_                                                         //160222
,int32 cell_ID, int32 crop_index)
: CS::Arguments(ID_)
, scenario_directory(0)                                                          //150422
{ // Constructor of VIC_CropSyst
   char cell_ID_cstr[10];     int32_to_cstr(cell_ID,cell_ID_cstr);
   char crop_index_cstr[10];  int32_to_cstr(crop_index,crop_index_cstr);
   ID.set_number(cell_ID);                                                       //160222
   CORN::OS::Directory_name_concrete CWD;
   #ifdef VIC_CROPSYST_VERSION
   scenario_directory_name = new CORN::OS::Directory_name_concrete(CWD);         //160504LML
   #else
   CORN::OS::Directory_name_concrete cell_ID_directory                           //161029
      (CWD,cell_ID_cstr,CORN::OS::directory_entry);
   scenario_directory_name = new CORN::OS::Directory_name_concrete               //161029
      (cell_ID_directory,crop_index_cstr,CORN::OS::directory_entry);
   #endif
}
//_2015-04-15___________________________________________________________________
Arguments::~Arguments()
{  delete scenario_directory; scenario_directory = 0;
}
//_2015-04-15___________________________________________________________________
CropSyst::Scenario_directory &Arguments::provide_scenario_directory() provision_
{
   //std::clog << "provide_scenario_directory_name:\t"<<provide_scenario_directory_name() << std::endl;
   if (!scenario_directory)
      scenario_directory = new CropSyst::Scenario_directory(provide_scenario_directory_name(),false);
   return *scenario_directory;
}
//_2015-04-15___________________________________________________________________
bool Arguments::invalidate_scenario_directory()                    modification_
{  delete scenario_directory; scenario_directory = 0;
   return CS::Arguments::invalidate_scenario_directory();
}
//_2016-01-14___________________________________________________________________
bool Arguments::get_program_version(std::string &version)                  const
{  version.append("5 ");       // get from CS version
   CORN::Date_time_clad_64 now; // actually should be __Date__ ??
   now.append_to_string(version _ISO_FORMAT_DATE_TIME);
   return true;
}
//_2016-12-20___________________________________________________________________
bool Arguments::submit_DEN
(CORN::OS::Directory_entry_name *param_DEN)                          submission_
{  bool recognized = CS::Arguments::submit_DEN(param_DEN);
   if (recognized && !scenario_directory && scenario_directory_name)
   {  provide_scenario_directory();
      recognized = true;
   }
   return recognized;
}
//_2018-02-13___________________________________________________________________
Arguments_V4::Arguments_V4
(CS::Identification &ID_)                                                        //160222
: Arguments(ID_)
, format_filename(0)
{}
//_2015-04-15___________________________________________________________________
bool Arguments_V4::recognize
(const std::string &curr_arg)                                      modification_
{  bool recognized = true;
   if      (curr_arg == "LADSS")
   {  LADSS_mode = true;                                                         //021206
   }
   else if ((curr_arg == "NOGRAPH") || (curr_arg == "nograph"))
      verbose = 0;                                                               //170208_160311
   recognized = Arguments::recognize(curr_arg);
   return recognized;
}
//_2015-04-15___________________________________________________________________
bool Arguments_V4::submit_DEN
(CORN::OS::Directory_entry_name *param_DEN)                          submission_
{  bool recognized = true;
   if      (param_DEN->has_extension_ASCII("dbf",true))
   {  GIS_override_table = param_DEN;
   }
   else if (param_DEN->has_extension_ASCII("fmt",true))
   {  format_filename = param_DEN;
   } else recognized = Arguments::submit_DEN(param_DEN);
   return recognized;
}
//_2015-04-15___________________________________________________________________
bool Arguments_V4::get_program_version(std::string &version)               const
{
   version.append("4 ");
   // NYI would like to append major minor revision (or date)
   return true;
}
//_2016-12-20___________________________________________________________________
} // namespace CropSyst
