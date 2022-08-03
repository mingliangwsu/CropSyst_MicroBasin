#ifndef CS_directory_contextsH
#define CS_directory_contextsH
//______________________________________________________________________________
enum Directory_context        // Makesure the context tabsheet page indices match in pagecontrol_context
   {
    arbitrary_context            //  0
   ,project_context              //  1
   ,database_context             //  2
   ,scenarios_context            //  3
   ,enterprises_context          //  4
   ,scenario_context             //  5
   ,scenario_output_context      //  6  7
   ,weather_context              //  7  8
   ,soil_context                 //  8  9
   ,rotation_context             //  9 10
   ,crop_context                 // 10 11
   ,management_context           // 11 12
   ,biomatter_context            // 12 13
   ,initial_context              // 13
   #if (CS_VERSION==4)
   ,format_context               // 14
//170901   ,STATSGO_context              // 15    This is the older STATSGO ArcInfo format I may or may not support it in V5
   #endif
   #if (CS_VERSION==5)
   /*180101 NYI
   ,TDF_formt_context //180101 //  TDF output format           // 14
   ,geolocation_context
   ,climgen_context
   ,crop_fruit_context
   ,crop_CropGro_context
   */

   #endif
   ,CONTEXT_COUNT
};
#define UNKNOWN_context CONTEXT_COUNT
//_2014-01-25_(moved from CS_explorer_engine)___________________________________
struct Context_strings
{
   int         mode;   // 0 arbitrary, 1=UED, 2=CS_suite, 3=CropSyst
   bool        parameter_directory;  // In this case we create only parameter directory
   const char *context;                                                          //140125
   const char *icon;
   const char *editor;
   const char *parameter_file_ext_or_name;// For V5
   const char *parameter_file_ext;        // for V4
   const char *description;
};
//______________________________________________________________________________
extern Context_strings context_strings[];                                        //140214
//______________________________________________________________________________


#endif

