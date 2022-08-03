#include "CANMS_directory.h"
namespace CS
{
//______________________________________________________________________________
CANMS_Database_directory::CANMS_Database_directory
(const CANMS_Directory &CANMS_dir)
:  CORN::OS::File_system_logical::Directory(CANMS_dir,L"Database",false)          //140313
, equipment_directory   (0)//140313 (*this,"Equipment")
, facility_directory    (0)//140313 (*this,"Facility")
, feed_directory        (0)//140313 (*this,"Feed")
{}
//______________________________________________________________________________
CANMS_Directory::CANMS_Directory
(const CS::Suite_Directory &,
const wchar_t * directory_name)
: CS::Application_directory
   (directory_name)
, database_directory(*this) //L"Database")
{}
//______________________________________________________________________________
provide_directory_name_implementation(CANMS_Database_directory,Equipment,equipment_directory,"Equipment" )
provide_directory_name_implementation(CANMS_Database_directory,Facility ,facility_directory ,"Facility" )
provide_directory_name_implementation(CANMS_Database_directory,Feed     ,feed_directory     ,"Feed" )
} // namespace CS

