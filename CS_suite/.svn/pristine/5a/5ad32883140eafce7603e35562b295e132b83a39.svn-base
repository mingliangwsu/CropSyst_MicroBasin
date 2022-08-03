#error this file has been moved to the application directory
Delete this file after 2018


#include "CS_suite_directory.h"
#include "CS_suite/CS_application_directory.h"
namespace CS
{
Suite_Directory *Suite_directory;
//______________________________________________________________________________
Suite_Directory::Suite_Directory
(const CORN::OS::Directory_entry_name &directory_or_subdir_file_name)
: CORN::OS_FS::Suite_directory(directory_or_subdir_file_name)
, CropSyst_directory       (0)   //("CropSyst" )
, UED_directory            (0)   //("UED"      )
, ClimGen_directory        (0)   //("ClimGen"  )
, CANMS_directory          (0)   //("CANMS")
, CAFE_directory           (0)   //("CAFE")
, NIFA_directory           (0)                                                   //141110
, Database_directory       (0)                                                   //140630
, CS_Explorer_directory    (0)                                                   //141116
, ClimGen_exe_file         (0)
, CS_explorer_exe_file     (0)   //("CS_explorer.exe")
, CS_suite_exe_file        (0)
, common_weather_directory (0)   //("weather")
, weather_editor_exe_file  (0)   //("weather_editor.exe")
, Database_REACCH_to_CS_soil_weather_exe_file(0)                                 //140630
{}
//________________________________________________Suite_directory_constructor__/
Suite_Directory::~Suite_Directory()
{  reset();
}
//_________________________________________________Suite_directory destructor__/
bool Suite_Directory::is_valid()                                           const
{  return ClimGen().exists()
      ||  CropSyst().exists();
}
//___________________________________________________________________is_valid__/
void Suite_Directory::reset()                                         provision_ // provides because only modifies provided contributes;
{  CORN::OS_FS::Suite_directory::reset();
   delete CropSyst_directory;          CropSyst_directory = 0;
   delete UED_directory;               UED_directory=0;
   delete ClimGen_directory;           ClimGen_directory = 0;
   delete ClimGen_exe_file;            ClimGen_exe_file = 0;
   delete CANMS_directory;             CANMS_directory = 0;
   delete CAFE_directory;              CAFE_directory = 0;
   delete NIFA_directory;              NIFA_directory = 0;                       //141110
   delete CS_explorer_exe_file;        CS_explorer_exe_file = 0;
   delete CS_suite_exe_file;           CS_suite_exe_file = 0;
   delete common_weather_directory; common_weather_directory = 0;
   delete Database_directory; Database_directory = 0;
   delete CS_Explorer_directory;       CS_Explorer_directory = 0;
   delete weather_editor_exe_file;  weather_editor_exe_file = 0;
}
//___________________________________________________________reset_subentries__/
provide_suite_application_directory_name_implementation  (CS::Suite_Directory,UED::Application_directory ,UED      ,UED_directory ,L"UED");
provide_file_name_implementation                         (CS::Suite_Directory,CS_explorer_executable     ,CS_suite_exe_file,"CS_explorer.exe");
provide_suite_application_directory_name_implementation  (CS::Suite_Directory,CAFE_Directory             ,CAFE     ,CAFE_directory,L"CAFE"); //130906
provide_suite_application_directory_name_implementation  (CS::Suite_Directory,NIFA_Directory             ,NIFA     ,NIFA_directory,L"NIFA"); //130906
provide_specialized_directory_name_implementation        (CS::Suite_Directory,CANMS_Directory            ,CANMS    ,CANMS_directory,L"CANMS"); //131006
provide_directory_name_implementation                    (CS::Suite_Directory,Database         ,Database_directory      ,L"Database"); //140630
provide_subdir_file_name_implementation                  (CS::Suite_Directory,Database_REACCH_to_CS_soil_weather_executable,       Database_REACCH_to_CS_soil_weather_exe_file     ,Database(),L"REACCH_to_CS_soil_weather.exe"); //140630

//______________________________________________________________________________
const CropSyst_Directory &Suite_Directory
::CropSyst()                                                           provision_
{  if (!CropSyst_directory)
   {  CORN::OS::Directory_name_concrete dir(*this,"CropSyst",CORN::OS::directory_entry);//161029
      CropSyst_directory = new CS::CropSyst_Directory(*this,L"CropSyst");
   }
   return *CropSyst_directory;
}
//_2014-11-19___________________________________________________________________
const ClimGen_Directory &Suite_Directory
::ClimGen()                                                           provision_
{  if (!ClimGen_directory)
   {  CORN::OS::Directory_name_concrete dir(*this,"ClimGen",CORN::OS::directory_entry );  //161029
      ClimGen_directory = new CS::ClimGen_Directory(dir);
   }
   return *ClimGen_directory;
}
//____________________________________________________________________ClimGen__/
const CORN::OS::Directory_name &Suite_Directory
::common_weather()                                                    provision_
{  if (!common_weather_directory)
   {  common_weather_directory = new CORN::OS::Directory_name_concrete
         (common(),L"Weather",CORN::OS::directory_entry);                        //161029
   }
   return *common_weather_directory;
}
//_____________________________________________________________common_weather__/
const CORN::OS::File_name      &Suite_Directory
::weather_editor_executable()                                         provision_
{  if (!weather_editor_exe_file)
   {  weather_editor_exe_file = new CORN::OS::File_name_concrete(
      #if (CS_VERSION==4)
         common_weather()
      #else
         UED()
      #endif
         ,"weather_editor.exe");
   }
   return *weather_editor_exe_file;
}
//_________________________________________________________weather_editor_exe__/
const CORN::OS_FS::Program_directory &Suite_Directory
:: CS_Explorer()                                                      provision_
{  if (!CS_Explorer_directory)
   {  CS_Explorer_directory = new CORN::OS_FS::Program_directory
         (CS_explorer_executable());
   }
   return * CS_Explorer_directory;
}
//_2014-11-16  _________________________________________________________________
} // namespace CS

