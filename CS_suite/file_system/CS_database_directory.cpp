#include "CS_suite/file_system/CS_database_directory.h"

namespace CS
{
//______________________________________________________________________________
Database_directory_context::Database_directory_context()
:crop_directory               (0)
,output_directory             (0)
,soil_directory               (0)
,weather_directory            (0)
,weather_scenarios_directory  (0)
,management_directory         (0)
,biomatter_directory          (0)
,rotation_directory           (0)
,format_directory             (0)
,recalibration_directory      (0)
,water_table_directory        (0)
,initialization_directory     (0)
,initialization_H2O_directory (0)
,initialization_NO3_directory (0)
,initialization_NH4_directory (0)
,initialization_OM_directory  (0)
,STATSGO_states_directory     (0)
{}
//______________________________________________________________________________
Database_directory_context::~Database_directory_context()
{  reset(); }
//______________________________________________________________________________
void Database_directory_context::reset()                                      provision_
{
   delete crop_directory;                 crop_directory                = 0;
   delete output_directory;               output_directory              = 0;
   delete soil_directory;                 soil_directory                = 0;
   delete weather_directory;              weather_directory             = 0;
   delete weather_scenarios_directory;    weather_scenarios_directory   = 0;
   delete management_directory;           management_directory          = 0;
   delete biomatter_directory;            biomatter_directory           = 0;
   delete rotation_directory;             rotation_directory            = 0;
   delete format_directory;               format_directory              = 0;
   delete recalibration_directory;        recalibration_directory       = 0;
   delete water_table_directory;          water_table_directory         = 0;
   delete initialization_directory;       initialization_directory      = 0;
   delete initialization_H2O_directory;   initialization_H2O_directory  = 0;
   delete initialization_NO3_directory;   initialization_NO3_directory  = 0;
   delete initialization_NH4_directory;   initialization_NH4_directory  = 0;
   delete initialization_OM_directory;    initialization_OM_directory   = 0;
   delete STATSGO_states_directory;       STATSGO_states_directory      = 0;
}
//______________________________________________________________________________
provide_directory_name_implementation(Database_directory_context,Crop              ,crop_directory         ,"Crop" )
provide_directory_name_implementation(Database_directory_context,Output            ,output_directory       ,"Output")
provide_directory_name_implementation(Database_directory_context,Soil              ,soil_directory         ,"Soil")
provide_directory_name_implementation(Database_directory_context,Weather           ,weather_directory      ,"Weather" )
provide_subdir_directory_name_implementation(Database_directory_context,Weather_Scenarios,weather_scenarios_directory,Weather(),"Scenarios")
provide_directory_name_implementation(Database_directory_context,Management        ,management_directory   ,"Management" )
provide_directory_name_implementation(Database_directory_context,Biomatter         ,biomatter_directory    ,"Biomatter")
provide_directory_name_implementation(Database_directory_context,Rotation          ,rotation_directory     ,"Rotation")
provide_directory_name_implementation(Database_directory_context,Format            ,format_directory       ,"Format")
provide_directory_name_implementation(Database_directory_context,Recalibration     ,recalibration_directory,"Recalibration")
provide_directory_name_implementation(Database_directory_context,Water_table       ,water_table_directory  ,"Water_table" )
provide_directory_name_implementation(Database_directory_context,Initialization    ,initialization_directory,"Initialization")
/* NYI
provide_directory_name_implementation(Database_directory,Initialization_H2O,initialization_H2O_directory,filename_literal)
provide_directory_name_implementation(Database_directory,Initialization_NO3,initialization_NO3_directory,filename_literal)
provide_directory_name_implementation(Database_directory,Initialization_NH4,initialization_NH4_directory,filename_literal)
provide_directory_name_implementation(Database_directory,Initialization_OM ,initialization_OM_directory,filename_literal)
*/
#if (CS_VERSION==5)
provide_directory_name_implementation(Database_directory_context,STATSGO2,STATSGO_states_directory,"STATSGO2")
#endif
//______________________________________________________________________________
} // namespace CS

