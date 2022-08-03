#ifndef __cplusplus
#include "CS_directory_contexts.h"
#endif
#include "CS_suite/file_system/CS_file_ext.hh"
#include "corn/string/strconv.hpp"
#ifdef _Windows
#  include <windows.h>
#endif
//______________________________________________________________________________
struct Context_strings

context_strings[CONTEXT_COUNT] =
{  // icon, editor, description
   { 0,false,"arbitrary"            ,""                       ,"CS_explorer.exe"                        ,""               ,""               ,"Arbitrary directory (not a CropSyst context)"} // arbitrary
,  { 3,true ,"project"              ,"folder_project.ico"     ,"CropSyst\\project_editor.exe"           ,".CS_project"    ,"csp"            ,"CropSyst project"}  // project_context            //  1
// In V4 CS_explorer now creates projects directory with the associated parameter file stored in the directory.
// but we continue to recognize .csp file
,  { 2,false,"database"             ,"database.ico"           ,"CropSyst\\database_editor.exe"          ,""               ,""               ,"CropSyst parameter database"}   //  2
,  { 3,false,"scenarios"            ,"folder_scenarios.ico"   ,"CS_explorer.exe"                        ,0                ,0                ,"CropSyst project scenarios"}    //  3
,  { 3,false,"enterprises"          ,"folder_enterpises.ico"  ,"CANMS\\scenario_editor.exe"             ,".CANMS_enterprise",0              ,"CANMS enterprise"}              //  4
         // Note that the CANMS scenario editor is the same for both enterprises and management scenarios
,  { 3,true ,"scenario"             ,"folder_scenario.ico"    ,"CropSyst\\scenario_editor.exe"          ,".CropSyst_scenario"   ,"CropSyst_scenario"/*180101 CS_scenario_EXT */ ,"CropSyst scenario"}       //  5
//170901 ,  { 3,false,"generated_scenarios"  ,"folder_scenario.ico"    ,"CS_explorer.exe"                        ,0                ,0                ,"CropSyst scenarios"}   //  6
,  { 3,false,"scenario_output"      ,"output.ico"             ,"CropSyst\\output_manager_advanced.exe"  ,0                ,"CS_output_options","CropSyst scenario output"}    //  7
,  { 3,true ,"weather"              ,"folder_weather.ico"     ,"common\\weather\\weather_editor.exe"    ,"UED"            ,"UED"            ,"UED weather"}                   //  8
,  { 3,true ,"soil"                 ,"folder_soil.ico"        ,"CropSyst\\soil_editor.exe"              ,CS_soil_EXT      ,CS_soil_EXT      ,"CropSyst soil"}                 //  9
,  { 3,true ,"rotation"             ,"folder_rotation.ico"    ,"CropSyst\\rotation_editor.exe"          ,CS_rotation_EXT  ,CS_rotation_EXT  ,"CropSyst rotation"}             // 10
,  { 3,true ,"crop"                 ,"folder_crop.ico"        ,"CropSyst\\crop_editor.exe"              ,CS_crop_EXT      ,CS_crop_EXT      ,"CropSyst crop"}                 // 11
,  { 3,true ,"management"           ,"folder_management.ico"  ,"CropSyst\\management_editor.exe"        ,CS_management_EXT,CS_management_EXT,"CropSyst management"}           // 12
,  { 3,true ,"biomatter"            ,"folder_biomatter.ico"   ,"CropSyst\\biomatter_editor.exe"         ,CS_biomatter_EXT ,CS_biomatter_EXT ,"CropSyst biomatter"}            // 13
,  { 3,true ,"initial"            ,"XXX.ico"   ,"CropSyst\\XXX.exe"         ,"" ,"" ,"CropSyst initialization"}                                               // 14

/* 171122
NYI add  scenario_output_comparison
This directory is created by scenario output compare
Any subdirectory of a Comparison has context functions
to export selected UED (to a specified format)

*/
#if (CS_VERSION==4)
,  { 3,true,"format"               ,"folder_format.ico"      ,"CropSyst\\format_editor.exe"            ,"fmt"             ,"fmt"             ,"CropSyst report format"}       // 15
//170901,  { 2,false,"STATSGO"              ,"database.ico"           ,0                              ,0                 ,0                ,"STATSGO database"}               // 14
#endif


#if (CS_VERSION==5)

#endif
// { 0, "xxxxxxxxxxxxxxxxx.ico"  ,"xxxxxxx_editor.exe"   ,".CS_xxxxxxx"    ,CS_xxxxxxx_EXT   ,"CropSyst xxxxxx"} // CONTEXT_COUNT
};
//______________________________________________________________________________
Directory_context get_directory_context_cstr(const char *dir_name_fully_qualified)
{
   char context_code[2048];
      // CS directory contexts can be identified by entries
      // in the directories desktop.ini (Windows) or .directory (Linux) files
   char desktop_context_file[2048];
   strcpy(desktop_context_file,dir_name_fully_qualified);
   strcat(desktop_context_file,DEFAULT_DIRECTORY_SEPARATORa_str);
   #ifdef _Windows
   strcat(desktop_context_file,"desktop.ini");
   GetPrivateProfileString
      ("CS","context","unknown",context_code,2048,desktop_context_file);
      // The project may be identified by having a context entry in desktop.ini
      // A project directory is identified by either:
      //    A directory containing a canonical project filename (I.e. for CropSyst .CS_project file)
      //    A directory containing a desktop.ini with an section and entry
      //       with a section [CS]
   #endif
   #ifdef __linux
      strcat(desktop_context_file,".directory");
      // The project may be identified by having a context entry in .directory file
      // this file conforms to freedesktop.org specification
      // and adds the section [CS] and entry context=project
      assert(false); //  NYI
   #endif
   for (int c = 0; c < CONTEXT_COUNT; c++)
      if (strcmp(context_strings[c].context,context_code) == 0)
         return (Directory_context)c;
   #if (CS_VERSION==4)
   // Older CS suite V4 did not have context entry
   // but did have a section [.ShellClassInfo] with IconFile
   strcpy(desktop_context_file,dir_name_fully_qualified);
   strcat(desktop_context_file,DEFAULT_DIRECTORY_SEPARATORa_str);
   char icon_file[2048];
   #ifdef _Windows
   GetPrivateProfileString
      (".ShellClassInfo","IconFile","",icon_file,2048,desktop_context_file);
         // An entry would be something like:
         // IconFile=C:\CS_Suite_4\Icons\folder_project.ico
      #endif
   #ifdef __linux
      // The project may be identified by having a context entry in .directory file
      // this file conforms to freedesktop.org specification
      // and adds then [?????] context=project
      assert(false); //  NYI
   #endif
   for (int c = 0; c < CONTEXT_COUNT; c++)
      if (strstr(icon_file,context_strings[c].icon) != 0)
         return (Directory_context)c;
   #endif
   return arbitrary_context;
}
//______________________________________________________________________________
