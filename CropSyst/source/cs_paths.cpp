130321 should now be obsolete

#ifdef USE_OLD_CS_PATHS
// 090629 This is being replaced with CS_Directory and CropSyst_Directory classes

// Do not include CropSyst_sim_pch or use precompiled header
// because this is also used by ClimGen
// (and other CropSyst utilities) which can't load all that stuff

#include "cs_paths.h"
#ifdef _Windows
#include <shlobj.h>
#endif

CS_suite_paths *cs_suite_paths = 0;
//______________________________________________________________________________
CS_suite_paths::CS_suite_paths(const Directory_name &_suite_dir)
: suite_dir_local(_suite_dir)
, suite_dir_WWW("http://www.bsyse.wsu.edu/cs_suite")
, cropsyst_dir(suite_dir_local.subdirectory_path("CropSyst",dir_init_buffer,false),false)
, suite_manual_dir(suite_dir_local.subdirectory_path("manual",dir_init_buffer,false),false)
, common_dir(suite_dir_local.subdirectory_path("common",dir_init_buffer,false),false)
, common_dll_dir(common_dir.subdirectory_path("dll",dir_init_buffer,false),false)
, common_weather_dir(common_dir.subdirectory_path("weather",dir_init_buffer,false),false)
, common_manual_dir(common_dir.subdirectory_path("manual",dir_init_buffer,false),false)
, common_manual_TDF_dir(common_manual_dir.subdirectory_path("TDF",dir_init_buffer,false),false)
, common_manual_parameters_dir(common_manual_dir.subdirectory_path("parameters",dir_init_buffer,false),false)
, common_manual_parameters_event_dir(common_manual_parameters_dir.subdirectory_path("event",dir_init_buffer,false),false)
, common_manual_parameters_event_schedule_htm("schedule.htm")
, common_manual_parameters_event_repetition_htm("repetition.htm")
,common_manual_parameters_event_period_htm("period.htm")
, common_manual_whatnow_dir(common_manual_dir.subdirectory_path("whatnow",dir_init_buffer,false),false)
, common_manual_TDF_editor_htm("TDF_editor.htm")
, bds501f_dll("bds501f.dll")
, cw3220_dll("cw3220.dll")
, owl501f_dll("owl501f.dll")
, cropsyst_template_dir(cropsyst_dir.subdirectory_path("template",dir_init_buffer,false),false)
, cropsyst_manual_dir(cropsyst_dir.subdirectory_path("manual",dir_init_buffer,false),false)
, cropsyst_manual_whatnow_dir(cropsyst_manual_dir.subdirectory_path("whatnow",dir_init_buffer,false),false)
#ifndef NEW_CS_PATHS
, cropsyst_manual_editors_dir(cropsyst_manual_dir.subdirectory_path("editors",dir_init_buffer,false),false)
, cropsyst_manual_parameters_dir(cropsyst_manual_dir.subdirectory_path("parameters",dir_init_buffer,false),false)
, cropsyst_manual_parameters_crop_dir(cropsyst_manual_parameters_dir.subdirectory_path("crop",dir_init_buffer,false),false)
#endif
, cropsyst_crop_calibrator_dir(cropsyst_dir.subdirectory_path("crop_calibrator",dir_init_buffer,false),false)
, cropsyst_manual_project_dir(cropsyst_manual_dir.subdirectory_path("project",dir_init_buffer,false),false)
, cs_suite_instructions_htm("instructions.htm")
, cs_suite_about_htm("about.htm")
, cs_suite_manual_edit_project_htm("edit_project.htm")
, cs_suite_manual_projects_htm("projects.htm")
, cs_suite_manual_utilities_htm("utilities.htm")
, project_editor_instructions_htm("project.htm")
, management_editor_instructions_htm("management.htm")
, scenario_editor_instructions_htm("scenario.htm")
, database_editor_instructions_htm("manual.htm") // moved to C:\CS_suite_4\CropSyst\database_editor\manual.htm // ("database.htm")
, crop_calibrator_instructions_htm("manual.htm")
, project_CPF_instructions_htm("crop_production_function.htm")
, CS_suite_exe("CS_suite.exe")
, CS_explorer_exe("CS_explorer.exe")
, cropsyst_model_exe("cropsyst_4.exe")
, crop_editor_exe("crop_editor.exe")
, crop_calibrator_exe("crop_calibrator.exe")
, soil_editor_exe("soil_editor.exe")
, weather_editor_exe("weather_editor.exe")
, location_editor_exe("location_editor.exe")
, rotation_editor_exe("rotation_editor.exe")
, format_editor_exe("format_editor.exe")
, management_editor_exe("management_editor.exe")
, biomatter_editor_exe("biomatter_editor.exe")
, project_editor_exe("project_editor.exe")
, soil_convertor_exe("soil_convertor.exe")
, carbon_sequestration_optimizer_exe("carbon_sequestration_optimizer.exe")
, carbon_sequestration_viewer_exe("carbon_sequestration_viewer.exe")
, GIS_runner_exe("GIS_runner.exe")
, scenario_editor_exe("scenario_editor.exe")
, database_editor_exe("database_editor.exe")
, output_manager_exe("output_manager.exe")
, output_manager_advanced_exe("output_manager_advanced.exe")
, fastgraph_exe("fastgrph.exe")
, schedule_viewer_exe("schedule_viewer.exe")
, CPF_controller_exe("CPF_controller.exe")
, create_simulation_directory_exe("create simulation directory.exe")
, UED_dir(suite_dir_local.subdirectory_path("UED",dir_init_buffer,false),false)

, UED_convert_layout_exe("layout.exe")
, UED_convert_export_exe("export.exe")
, UED_import_wizard_exe("import_wizard.exe")
, UED_export_wizard_exe("export_wizard.exe")
, UED_compare_exe("compare.exe")
, UED_spatial_interpolator_exe("spatial\\interpolation\\UED_spatial_interpolator.exe")
, UED_import_export_format_editor_exe("import_export_format_editor.exe")

, climgen_dir(suite_dir_local.subdirectory_path("climgen",dir_init_buffer,false),false)
, climgen_manual_dir(climgen_dir.subdirectory_path("manual",dir_init_buffer,false),false)
, climgen_manual_validation_dir(climgen_manual_dir.subdirectory_path("validation",dir_init_buffer,false),false)
, climgen_instructions_dir(climgen_dir.subdirectory_path("instructions",dir_init_buffer,false),false)
, climgen_manual_whatnow_dir(climgen_manual_dir.subdirectory_path("whatnow",dir_init_buffer,false),false)
, climgen_exe("climgen.exe")

, GIS_dir(suite_dir_local.subdirectory_path("GIS",dir_init_buffer,false),false)
, GIS_manual_dir(GIS_dir.subdirectory_path("manual",dir_init_buffer,false),false)

, watershed_dir(suite_dir_local.subdirectory_path("watershed",dir_init_buffer,false),false)
, watershed_manual_dir(watershed_dir.subdirectory_path("manual",dir_init_buffer,false),false)
, watershed_manual_whatnow_dir(watershed_manual_dir.subdirectory_path("whatnow",dir_init_buffer,false),false)
, watershed_edit_exe("watershed_edit.exe")
//obs, database_dir(suite_dir)
/*obsolete
, database_dir(suite_dir.subdirectory_path("Database",false).c_str())
, database_weather_dir(database_dir.subdirectory_path("weather",false))
, database_location_dir(database_dir.subdirectory_path("location",false).c_str())
, database_soil_dir(database_dir.subdirectory_path("soil",false).c_str())
, database_rotation_dir(database_dir.subdirectory_path("rotation",false).c_str())
, database_crop_dir(database_dir.subdirectory_path("crop",false))
*/
//obs, database_crop_default_dir(database_dir.crop_dir.subdirectory_path("default",false))
//obs, database_weather_NCDC_dir(database_dir.weather_dir.subdirectory_path("NCDC",false))
//obs, database_weather_NCDC_sodstn_txt("sodstn.txt")
//obs, projects_dir(suite_dir.subdirectory_path("Projects",false).c_str())
, pesticide_txt("pesticide.txt")
, phrasesc_lng("phrasesc.lng")
, icon_dir(suite_dir_local.subdirectory_path("icons",dir_init_buffer,false),false)
, icon_project("CS_project.ico")
, icon_project_folder("CS_project_folder.ico")
, icon_CS_GIS_project("CSGIS_project.ico")
, icon_CS_GIS_project_folder("CSGIS_project_folder.ico")
, icon_CS_WS_project("CS_WS_project.ico")
, icon_CS_WS_project_folder("CS_WS_project_folder.ico")
, cropsyst_icon_dir(cropsyst_dir.subdirectory_path("icons",dir_init_buffer,false),false)
, cropsyst_icon_operation_dir(cropsyst_icon_dir.subdirectory_path("operation",dir_init_buffer,false),false)
, cropsyst_icon_operation_48x24_dir(cropsyst_icon_operation_dir.subdirectory_path("48x24",dir_init_buffer,false),false)
, SOILPAR2_exe("Soilpar2.exe")
{
   common_manual_parameters_event_period_htm.set_path(common_manual_parameters_event_dir);
   common_manual_parameters_event_schedule_htm.set_path(common_manual_parameters_event_dir);
   common_manual_parameters_event_repetition_htm.set_path(common_manual_parameters_event_dir);
   common_manual_TDF_editor_htm.set_path(common_manual_TDF_dir);
   CS_suite_exe.set_path(suite_dir_local);
   CS_explorer_exe.set_path(suite_dir_local);
   cropsyst_model_exe.set_path(cropsyst_dir);
   crop_editor_exe.set_path(cropsyst_dir);
   crop_calibrator_exe.set_path(cropsyst_dir);
   soil_editor_exe.set_path(cropsyst_dir);
   weather_editor_exe.set_path(common_weather_dir);
   location_editor_exe.set_path(cropsyst_dir);
   rotation_editor_exe.set_path(cropsyst_dir);
   format_editor_exe.set_path(cropsyst_dir);
   management_editor_exe.set_path(cropsyst_dir);
   biomatter_editor_exe.set_path(cropsyst_dir);
   scenario_editor_exe.set_path(cropsyst_dir);
   database_editor_exe.set_path(cropsyst_dir);
   output_manager_exe.set_path(cropsyst_dir);
   output_manager_advanced_exe.set_path(cropsyst_dir);
   soil_convertor_exe.set_path(cropsyst_dir);

   project_editor_exe.set_path(cropsyst_dir);
   carbon_sequestration_optimizer_exe.set_path(cropsyst_dir);
   carbon_sequestration_viewer_exe.set_path(cropsyst_dir);

   GIS_runner_exe.set_path(cropsyst_dir);

   fastgraph_exe.set_path(cropsyst_dir);
   schedule_viewer_exe.set_path(cropsyst_dir);
   CPF_controller_exe.set_path(cropsyst_dir);

   bds501f_dll .set_path(common_dll_dir);
   cw3220_dll  .set_path(common_dll_dir);
   owl501f_dll .set_path(common_dll_dir);

   climgen_exe       .set_path(climgen_dir);
   watershed_edit_exe.set_path(watershed_dir);
   pesticide_txt     .set_path(cropsyst_dir);
   phrasesc_lng      .set_path(cropsyst_dir);

   UED_convert_canadian_climatological_exe.set_path(UED_convert_dir);
   UED_convert_DYRESM_exe                 .set_path(UED_convert_dir);
   UED_convert_LARS_WG_exe                .set_path(UED_convert_dir);
   UED_convert_VIC_exe                .set_path(UED_convert_dir);
   UED_convert_cropsyst_exe               .set_path(UED_convert_dir);
   UED_convert_layout_exe                 .set_path(UED_convert_dir);
   UED_convert_export_exe                 .set_path(UED_convert_dir);
   UED_convert_rzwqm_exe                  .set_path(UED_convert_dir);
   UED_convert_LADSS_exe                  .set_path(UED_convert_dir);
   UED_convert_noaa_met_exe               .set_path(UED_convert_dir);
   UED_convert_NCDC_daily_surface_data_exe.set_path(UED_convert_dir);
   UED_convert_NCDC_summary_of_the_day_exe.set_path(UED_convert_dir);
   UED_convert_INM_CHE_exe                .set_path(UED_convert_dir);
   UED_convert_EarthInfo_daily_binary_exe .set_path(UED_convert_dir);
   UED_convert_WPRO_exe                   .set_path(UED_convert_dir);
   UED_convert_APSIM_exe                  .set_path(UED_convert_dir);
   UED_convert_NCDC_NOAA_daily_global_surface_data_exe                   .set_path(UED_convert_dir);
   UED_convert_IBSNAT_ICASA_DSSAT_exe     .set_path(UED_convert_dir);
   UED_convert_IRIMO_exe                  .set_path(UED_convert_dir);
   UED_convert_SWAT_exe                   .set_path(UED_convert_dir);

   UED_convert_XLS_with_TDF_exe.set_path(UED_convert_dir);
   UED_convert_with_TDF_exe.set_path(UED_convert_dir);
   UED_tabular_format_editor_exe.set_path(UED_convert_dir);
   UED_import_wizard_exe.set_path(UED_dir);
   UED_export_wizard_exe.set_path(UED_dir);
   UED_compare_exe.set_path(UED_dir);

   UED_dir.qualify_to(Ustring("spatial\\interpolation\\UED_spatial_interpolator.exe"),UED_spatial_interpolator_exe,false) ;

   UED_import_export_format_editor_exe.set_path(UED_dir);

   cs_suite_instructions_htm        .set_path(suite_dir_local);
   cs_suite_about_htm               .set_path(suite_dir_local);
   cs_suite_manual_edit_project_htm .set_path(suite_manual_dir);
   cs_suite_manual_projects_htm     .set_path(suite_manual_dir);
   cs_suite_manual_utilities_htm    .set_path(suite_manual_dir);

   create_simulation_directory_exe.set_path(suite_dir_local);

   project_editor_instructions_htm     .set_path(cropsyst_manual_editors_dir);
   scenario_editor_instructions_htm    .set_path(cropsyst_manual_editors_dir);
   management_editor_instructions_htm  .set_path(cropsyst_manual_editors_dir);
   CORN::File_name database_editor_associated_dir(get_database_editor_exe());
   database_editor_associated_dir.set_ext("");
   database_editor_instructions_htm    .set_path(database_editor_associated_dir.c_str());
//070613   database_editor_instructions_htm    .set_path(cropsyst_manual_editors_dir);
   crop_calibrator_instructions_htm    .set_path(cropsyst_crop_calibrator_dir);
//080205    crop_calibrator_instructions_htm    .set_path(cropsyst_manual_parameters_crop_dir);

   project_CPF_instructions_htm        .set_path(cropsyst_manual_project_dir);

   icon_project               .set_path(icon_dir);
   icon_project_folder        .set_path(icon_dir);
   icon_CS_GIS_project        .set_path(icon_dir);
   icon_CS_GIS_project_folder .set_path(icon_dir);
   icon_CS_WS_project         .set_path(icon_dir);
   icon_CS_WS_project_folder  .set_path(icon_dir);

#ifdef _Windows
   // The following is only available in Windows (and only applied to the GUI)
   CORN::Smart_directory_name Programs_dir(CSIDL_PROGRAM_FILES);
   CORN::Directory_name Program_ISCI;
   CORN::Directory_name Program_ISCI_Soilpar;

   Programs_dir.subdirectory_path("ISCI",Program_ISCI,false);
   Program_ISCI.subdirectory_path("Soilpar",Program_ISCI_Soilpar,false);
   SOILPAR2_exe.set_path(Program_ISCI);
#endif
};
//______________________________________________________________________________
#ifdef NEW_CS_PATHS
const Directory_name &CS_suite_paths::get_cropsyst_manual_parameters_dir(Directory_entry_name::Path_type preferred_path_type)
{  Directory_name &found_cropsyst_manual_parameters_dir = ;
   switch (preferred_path_type)
   {  case Directory_entry_name::native_OS_path:
      case Directory_entry_name::URL_path      :

      break;
      case Directory_entry_name::prefer_native_otherwise_URL_path :
         Directory_name &native_dir = get_cropsyst_manual_dir(Directory_entry_name::native_OS_path);
         if (!native_dir.exists())

      break;
   };
};
#endif
//______________________________________________________________________________
const CORN::Smart_file_name &CS_suite_paths::Xget_cropsyst_parameter_help
(const char *file_htm)                                                     const
{  filename_return_buffer.assign(
#ifdef NEW_CS_PATHS
      get_cropsyst_manual_parameters_dir(Directory_entry_name::prefer_native_otherwise_URL_path)
#else
      cropsyst_manual_parameters_dir
#endif
      ); // 061204
   filename_return_buffer.append("\\");
   filename_return_buffer.append(file_htm);
   return filename_return_buffer;
};
//______________________________________________________________________________
const char *CS_suite_paths::get_cropsyst_parameter_help_cstr
(const char *file_htm) const
{  return   Xget_cropsyst_parameter_help(file_htm).c_str();
}
//______________________________________________________________________________
#ifdef NEW_CS_PATHS
const CORN::Smart_file_name &CS_suite_paths::get_cropsyst_manual_editors_dir(Directory_entry_name::Path_type preferred_path_type)
{  switch (preferred_path_type)
   {};
};
#endif
//______________________________________________________________________________
const CORN::Smart_file_name &CS_suite_paths::get_cropsyst_editor_help
(const char *file_htm) const
{
   // First see if the file is available locally
#ifdef NEW_CS_PATHS
   get_cropsyst_manual_editors_dir(preferred_path_type).qualify_to(file_htm,filename_return_buffer,prefer_native_otherwise_URL_path);
#else
   filename_return_buffer.assign(cropsyst_manual_editors_dir);
   filename_return_buffer.append("\\");
   filename_return_buffer.append(file_htm);
#endif
   return filename_return_buffer;
};
//______________________________________________________________________________
const char *CS_suite_paths::get_cropsyst_editor_help_cstr
(const char *file_htm) const
{  return   get_cropsyst_editor_help(file_htm).c_str();
}
//______________________________________________________________________________
const CORN::Smart_file_name &CS_suite_paths::get_UED_parameter_help
(const char *file_htm)                                                     const
{  filename_return_buffer.assign(UED_dir);
   filename_return_buffer.append("\\");
   filename_return_buffer.append(file_htm);
   return filename_return_buffer;
};
//______________________________________________________________________________
void setup_CS_suite_paths(const char *qualified_application_filename)
{
   // Here we presume the qualified_application_filename is in the CS_suite_X path
   // Where X is the major version number.
   CORN::File_name      this_exe_filename(qualified_application_filename);
   unsigned long suite_pos = this_exe_filename.find_substring("Suite");
   // I am looking simply for suite presuming I won't change this and it will be lowercase
   // But Windows 98 stupidly capitalizes the application filename!
   if (suite_pos == SUBSTRING_NOT_FOUND )
      suite_pos = this_exe_filename.find_substring("SUITE");
   if (suite_pos == SUBSTRING_NOT_FOUND )
      suite_pos = this_exe_filename.find_substring("suite");
   // Now search for first directory separator
   size_t first_dir_separator_pos = suite_pos;
   for (first_dir_separator_pos = suite_pos
       ; (this_exe_filename.c_str()[first_dir_separator_pos] !=  OS_DIRECTORY_SEPARATOR)
         && (first_dir_separator_pos < this_exe_filename.length())
       ; first_dir_separator_pos++);  // <- Yes the semicolon belongs here, we are just counting
   CORN::Directory_name cs_suite_dir(Ustring(this_exe_filename.c_str(),0,first_dir_separator_pos).c_str());
      cs_suite_paths = new CS_suite_paths(cs_suite_dir);
};
//______________________________________________________________________________
void setdown_CS_suite_paths()
{  if (cs_suite_paths) delete cs_suite_paths; cs_suite_paths = 0;
};
//______________________________________________________________________________
#endif
