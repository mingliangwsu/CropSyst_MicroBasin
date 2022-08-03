#ifndef CS_PATHSH
#define CS_PATHSH
#error
//130321 should now be obsolete
#ifdef USE_OLD_CS_PATHS
// 090629 This is being replaced with CS_Directory and CropSyst_Directory classes

// This class can be used to get paths to cropsyst support files and
// other subdirectory trees.

#include "database_dir.h"
#include <corn/file_sys/smart_filename.h>

using amespace ORN;

class  CS_suite_paths
{  // This is being replaced with CS_suite_directory  and CropSyst_directory
private:
   Directory_name       dir_init_buffer;
   mutable CORN::Smart_file_name      filename_return_buffer;
   mutable CORN::Directory_name       directory_return_buffer;

public:
   Smart_directory_name suite_dir_local;
   Smart_directory_name suite_dir_WWW;

   Directory_name suite_manual_dir;
   Directory_name common_dir;
   Directory_name common_weather_dir;
   Directory_name common_dll_dir;
   Directory_name common_manual_dir;
   Directory_name common_manual_parameters_dir;
   Directory_name common_manual_parameters_event_dir;
   Directory_name common_manual_whatnow_dir;
   Directory_name common_manual_TDF_dir;

   File_name   CS_suite_exe;
   File_name      common_manual_parameters_event_repetition_htm;
   File_name      common_manual_parameters_event_period_htm;
   File_name      common_manual_parameters_event_schedule_htm;
   File_name   CS_explorer_exe;

   File_name      common_manual_TDF_editor_htm;


   File_name bds501f_dll;
   File_name cw3220_dll;
   File_name owl501f_dll;

   Directory_name cropsyst_dir;
   Directory_name cropsyst_template_dir;
#ifdef NEW_CS_PATHS
   Directory_name cropsyst_manual_dir[2];
#else
   Directory_name cropsyst_manual_dir;
#endif
   Directory_name cropsyst_manual_whatnow_dir;
   Directory_name cropsyst_manual_editors_dir;
   Directory_name cropsyst_manual_parameters_dir;
   Directory_name cropsyst_manual_parameters_crop_dir;

   Directory_name cropsyst_manual_project_dir;
   Directory_name cropsyst_crop_calibrator_dir;

   Directory_name GIS_dir;
   Directory_name GIS_manual_dir;
   File_name      GIS_runner_exe;
   File_name      SOILPAR2_exe;

   Directory_name icon_dir;
   File_name icon_project;
   File_name icon_project_folder;
   File_name icon_CS_GIS_project;
   File_name icon_CS_GIS_project_folder;
   File_name icon_CS_WS_project;
   File_name icon_CS_WS_project_folder;

   Directory_name cropsyst_icon_dir;
   Directory_name cropsyst_icon_operation_dir;
   Directory_name cropsyst_icon_operation_48x24_dir;

   File_name cs_suite_instructions_htm;
   File_name create_simulation_directory_exe;

   File_name cs_suite_about_htm;
   File_name project_editor_instructions_htm;
   File_name scenario_editor_instructions_htm;
   File_name management_editor_instructions_htm;
   File_name database_editor_instructions_htm;
   File_name crop_calibrator_instructions_htm;

   File_name cs_suite_manual_edit_project_htm;
   Smart_file_name cs_suite_manual_projects_htm;
   File_name cs_suite_manual_utilities_htm;

   File_name project_CPF_instructions_htm;

   File_name cropsyst_model_exe;
   File_name crop_editor_exe;
   File_name crop_calibrator_exe;
   File_name soil_editor_exe;
   File_name weather_editor_exe;
   File_name location_editor_exe;
   File_name management_editor_exe;
   File_name biomatter_editor_exe;
   File_name rotation_editor_exe;
   File_name project_editor_exe;
   File_name scenario_editor_exe;
   File_name format_editor_exe;
   File_name database_editor_exe;
   File_name output_manager_exe;
   File_name output_manager_advanced_exe;
   File_name fastgraph_exe;
   File_name CPF_controller_exe;
   File_name schedule_viewer_exe;

   File_name soil_convertor_exe;

   File_name carbon_sequestration_optimizer_exe;
   File_name carbon_sequestration_viewer_exe;

   Directory_name climgen_dir;
   Directory_name climgen_manual_dir;
   Directory_name climgen_manual_validation_dir;
   Directory_name climgen_instructions_dir;

   Directory_name climgen_manual_whatnow_dir;
   File_name climgen_exe;

   Directory_name watershed_dir;
   Directory_name watershed_manual_dir;
   Directory_name watershed_manual_whatnow_dir;
   File_name watershed_edit_exe;

   Directory_name UED_dir;
   Smart_directory_name UED_convert_dir;
   Smart_directory_name UED_convert_formats_dir;
   File_name      UED_convert_canadian_climatological_exe;
   File_name      UED_convert_cropsyst_exe;
   File_name      UED_convert_LADSS_exe;
   File_name      UED_convert_layout_exe;
   File_name      UED_convert_export_exe;
   File_name      UED_convert_rzwqm_exe;
   File_name      UED_convert_noaa_met_exe;
   File_name      UED_convert_DYRESM_exe;
   File_name      UED_convert_LARS_WG_exe;
   File_name      UED_convert_SWAT_exe;
   File_name      UED_convert_VIC_exe;

   File_name      UED_convert_NCDC_daily_surface_data_exe;
   File_name      UED_convert_NCDC_summary_of_the_day_exe;
   File_name      UED_convert_INM_CHE_exe;
   File_name      UED_convert_EarthInfo_daily_binary_exe;
   File_name      UED_convert_UCAR_DS512_daily_exe;
   File_name      UED_convert_WPRO_exe;
   File_name      UED_convert_APSIM_exe;
   File_name      UED_convert_NCDC_NOAA_daily_global_surface_data_exe;
   File_name      UED_convert_IBSNAT_ICASA_DSSAT_exe;
   File_name      UED_convert_IRIMO_exe;

   File_name      UED_tabular_format_editor_exe;
   File_name      UED_convert_XLS_with_TDF_exe;
   File_name      UED_convert_with_TDF_exe;
   File_name      UED_import_wizard_exe;
   File_name      UED_export_wizard_exe;
   File_name      UED_compare_exe;
   File_name      UED_spatial_interpolator_exe;
   Smart_file_name      UED_import_export_format_editor_exe;
   File_name      pesticide_txt;
   File_name      phrasesc_lng;
public:
   CS_suite_paths(const Directory_name &i_CS_suite_app_dir);

#ifdef NEW_CS_PATHS
   const Directory_name &get_cropsyst_manual_parameters_dir(Directory_entry_name::Path_type);
   const CORN::Smart_file_name &get_cropsyst_manual_editors_dir(bool as_URL);
#else
   inline const Directory_name &get_cropsyst_manual_dir()   { return cropsyst_manual_dir;};
#endif

   inline const Smart_directory_name &get_suite_dir()             { return suite_dir_local; };
   inline const Directory_name &get_cropsyst_dir()          { return cropsyst_dir; };
   inline const Directory_name &get_cropsyst_template_dir() { return cropsyst_template_dir;};
   inline const Directory_name &get_common_manual_dir()     { return common_manual_dir;};
   inline const Directory_name &get_common_weather_dir()    { return common_weather_dir;};
   inline const Directory_name &get_watershed_manual_dir()  { return watershed_manual_dir;};
   inline const Directory_name &get_GIS_manual_dir()        { return GIS_manual_dir;};
   inline const Directory_name &get_cropsyst_manual_whatnow_dir()   { return cropsyst_manual_whatnow_dir;};
   inline const Directory_name &get_common_manual_whatnow_dir()     { return common_manual_whatnow_dir;};
   inline const Directory_name &get_common_manual_parameters_dir()     { return common_manual_parameters_dir;};
   inline const Directory_name &get_cropsyst_manual_parameters_crop_dir()     { return cropsyst_manual_parameters_crop_dir;};
   inline const Directory_name &get_watershed_manual_whatnow_dir()  { return watershed_manual_whatnow_dir;};
   inline const Directory_name &get_climgen_manual_dir()    { return climgen_manual_dir;};
   inline const Directory_name &get_climgen_manual_validation_dir()    { return climgen_manual_validation_dir;};
   inline const Directory_name &get_climgen_instructions_dir()    { return climgen_instructions_dir;};

   inline const Directory_name &get_climgen_manual_whatnow_dir()  { return climgen_manual_whatnow_dir;};

   inline const char *get_cs_suite_instructions_htm()          { return cs_suite_instructions_htm.c_str();};
   inline const char *get_cs_suite_about_htm()                 { return cs_suite_about_htm.c_str();};
   inline const char *get_project_editor_instructions_htm()    { return project_editor_instructions_htm.c_str();};
   inline const char *get_scenario_editor_instructions_htm()   { return scenario_editor_instructions_htm.c_str();};
   inline const char *get_management_editor_instructions_htm() { return management_editor_instructions_htm.c_str();};
   inline const char *get_database_editor_instructions_htm()   { return database_editor_instructions_htm.c_str();};
   inline const char *get_crop_calibrator_instructions_htm()   { return crop_calibrator_instructions_htm.c_str();};

   inline const char *get_parameters_event_period_htm()
   { return  common_manual_parameters_event_period_htm.c_str();};

   inline const char *get_parameters_event_schedule_htm()
   { return  common_manual_parameters_event_schedule_htm.c_str();};

   inline const char *get_TDF_editor_htm()
   { return  common_manual_TDF_editor_htm.c_str();};

   inline const char *get_parameters_event_repetition_htm()
   { return  common_manual_parameters_event_repetition_htm.c_str();};

   inline const char *get_cs_suite_manual_edit_project_htm()   { return cs_suite_manual_edit_project_htm.c_str();};
   inline const char *get_cs_suite_manual_projects_htm()       { return cs_suite_manual_projects_htm.c_str();};
   inline const char *get_cs_suite_manual_utilities_htm()      { return cs_suite_manual_utilities_htm.c_str();};

   inline const char *get_project_CPF_instructions_htm()       { return project_CPF_instructions_htm.c_str(); };

   // The following are for folder icons
   inline const Directory_name &get_icon_dir()              { return icon_dir;};
   inline const File_name      &get_icon_project()          { return icon_project; };
   inline const File_name      &get_icon_project_folder()   { return icon_project_folder; };
   inline const File_name      &get_icon_CS_GIS_project()         { return icon_CS_GIS_project; };
   inline const File_name      &get_icon_CS_GIS_project_folder()  { return icon_CS_GIS_project_folder; };
   inline const File_name      &get_icon_CS_WS_project()          { return icon_CS_WS_project; };
   inline const File_name      &get_icon_CS_WS_project_folder()   { return icon_CS_WS_project_folder; };

   inline const File_name      &get_CS_suite_exe()          { return CS_suite_exe; };
   inline const File_name      &get_CS_explorer_exe()       const { return CS_explorer_exe; };     
   inline const File_name      &get_cropsyst_model_exe()    { return cropsyst_model_exe;};
   inline const File_name      &get_crop_editor_exe()       { return crop_editor_exe;};
   inline const File_name      &get_crop_calibrator_exe()   { return crop_calibrator_exe;};
   inline const File_name      &get_soil_editor_exe()       { return soil_editor_exe;};
   inline const File_name      &get_weather_editor_exe()    { return weather_editor_exe;};
   inline const File_name      &get_location_editor_exe()   { return location_editor_exe;};
   inline const File_name      &get_rotation_editor_exe()   { return rotation_editor_exe;};
   inline const File_name      &get_format_editor_exe()   { return format_editor_exe;};
   inline const File_name      &get_management_editor_exe() { return management_editor_exe;};
   inline const File_name      &get_biomatter_editor_exe() { return biomatter_editor_exe;};
   inline const File_name      &get_project_editor_exe()    { return project_editor_exe;};
   inline const File_name      &get_scenario_editor_exe()   { return scenario_editor_exe;};
   inline const File_name      &get_database_editor_exe()   { return database_editor_exe;};
   inline const File_name      &get_output_manager_exe()    { return output_manager_exe;};
   inline const File_name      &get_output_manager_advanced_exe()    { return output_manager_advanced_exe;};
   inline const File_name      &get_CPF_controller_exe()    { return CPF_controller_exe;};
   inline const File_name      &get_carbon_sequestration_optimizer_exe(){ return carbon_sequestration_optimizer_exe;};
   inline const File_name      &get_carbon_sequestration_viewer_exe()   { return carbon_sequestration_viewer_exe;};

   inline const File_name      &get_GIS_runner_exe()        { return GIS_runner_exe;};
   inline const File_name      &get_SOILPAR_exe()           { return SOILPAR2_exe;};

   inline const Directory_name &get_cropsyst_icon_operation_dir() { return cropsyst_icon_operation_48x24_dir; };

   inline const File_name      &get_fastgraph_exe()         { return fastgraph_exe; };
   inline const File_name      &get_schedule_viewer_exe()   { return schedule_viewer_exe;};

   inline const Directory_name &get_UED_dir()               { return UED_dir;};
   inline const Smart_directory_name &get_UED_convert_dir()       { return UED_convert_dir;};
   inline const Smart_directory_name &get_UED_convert_formats_dir()       { return UED_convert_formats_dir;};
   inline const File_name      &get_UED_tabular_format_editor_exe() { return UED_tabular_format_editor_exe; }

   inline const File_name      &get_UED_convert_canadian_climatological_exe() { return UED_convert_canadian_climatological_exe; }
   inline const File_name      &get_UED_convert_DYRESM_exe() { return UED_convert_DYRESM_exe; }
   inline const File_name      &get_UED_convert_LARS_WG_exe() { return UED_convert_LARS_WG_exe; }
   inline const File_name      &get_UED_convert_cropsyst_exe() { return UED_convert_cropsyst_exe; }
   inline const File_name      &get_UED_convert_LADSS_exe() { return UED_convert_LADSS_exe; }
   inline const File_name      &get_UED_convert_rzwqm_exe() { return UED_convert_rzwqm_exe; }
   inline const File_name      &get_UED_convert_noaa_met_exe() { return UED_convert_noaa_met_exe; }
   inline const File_name      &get_UED_convert_NCDC_daily_surface_data_exe() { return UED_convert_NCDC_daily_surface_data_exe; }
   inline const File_name      &get_UED_convert_NCDC_summary_of_the_day_exe() { return UED_convert_NCDC_summary_of_the_day_exe; }
   inline const File_name      &get_UED_convert_INM_CHE_exe() { return UED_convert_INM_CHE_exe; }
   inline const File_name      &get_UED_convert_EarthInfo_daily_binary_exe() { return UED_convert_EarthInfo_daily_binary_exe; }
   inline const File_name      &get_UED_convert_UCAR_DS512_daily_exe() { return UED_convert_UCAR_DS512_daily_exe; }
   inline const File_name      &get_UED_convert_WPRO_exe() { return UED_convert_WPRO_exe; }
   inline const File_name      &get_UED_convert_APSIM_exe() { return UED_convert_APSIM_exe; }
   inline const File_name      &get_UED_convert_NCDC_NOAA_daily_global_surface_data_exe() { return UED_convert_NCDC_NOAA_daily_global_surface_data_exe; }
   inline const File_name      &get_UED_convert_IBSNAT_ICASA_DSSAT_exe() { return UED_convert_IBSNAT_ICASA_DSSAT_exe; }
   inline const File_name      &get_UED_convert_IRIMO_exe() { return UED_convert_IRIMO_exe; }
   inline const File_name      &get_UED_convert_SWAT_exe() { return    UED_convert_SWAT_exe; }
   inline const File_name      &get_UED_convert_VIC_exe() { return UED_convert_VIC_exe; }



   inline const File_name      &get_UED_convert_XLS_with_TDF_exe()   { return UED_convert_XLS_with_TDF_exe;};
   inline const File_name      &get_UED_convert_with_TDF_exe()       { return UED_convert_with_TDF_exe;};
   inline const File_name      &get_UED_convert_layout_exe()         { return UED_convert_layout_exe; };
   inline const File_name      &get_UED_convert_export_exe()         { return UED_convert_export_exe; };
   inline const File_name      &get_UED_import_wizard_exe()          { return UED_import_wizard_exe; };
   inline const File_name      &get_soil_convertor_exe()             { return soil_convertor_exe; };
   inline const File_name      &get_UED_export_wizard_exe()          { return UED_export_wizard_exe; };
   inline const File_name      &get_UED_compare_exe()                { return UED_compare_exe; };
   inline const File_name      &get_UED_spatial_interpolator_exe()   { return UED_spatial_interpolator_exe; };
   inline const Smart_file_name &get_UED_import_export_format_editor_exe() { return UED_import_export_format_editor_exe;};

   inline const File_name      &get_bds501f_dll()           { return bds501f_dll;};
   inline const File_name      &get_cw3220_dll()            { return cw3220_dll;};
   inline const File_name      &get_owl501f_dll()           { return owl501f_dll;};

   inline const Directory_name &get_climgen_dir()           { return climgen_dir;};
   inline const File_name      &get_climgen_exe()           { return climgen_exe;};

   inline const Directory_name &get_watershed_dir()         { return watershed_dir; };
   inline const File_name      &get_watershed_edit_exe()    { return watershed_edit_exe; };

   inline const File_name      &get_pesticide_txt()         { return pesticide_txt; };
   inline const File_name      &get_phrasesc_lng()          { return phrasesc_lng; };

   // Setup utilities
   inline const File_name     &get_create_simulation_directory_exe()
   { return create_simulation_directory_exe; };

   // Help file locations
//051031   const char *get_cropsyst_parameter_help(const char *partially_qualified_file_htm) const;
   const Smart_file_name      &Xget_cropsyst_parameter_help(const char *partially_qualified_file_htm) const;
   const char                 *get_cropsyst_parameter_help_cstr(const char *partially_qualified_file_htm) const;
   const Smart_file_name      &get_cropsyst_editor_help(const char *partially_qualified_file_htm) const;
   const char                 *get_cropsyst_editor_help_cstr(const char *partially_qualified_file_htm) const;

   const Smart_file_name      &get_UED_parameter_help(const char *partially_qualified_file_htm) const;
};

extern CS_suite_paths *cs_suite_paths;

extern void setup_CS_suite_paths(const char *qualified_application_filename);
// 051030 qualified_application_filename is now any file in CS_suite_X directory tree
// It used to be only file in CS_suite_X\CropSyst directory tree

extern void setdown_CS_suite_paths();


#define CS_SUITE_4_Web_root_dir "http:\/\/www.bsyse.wsu.edu\/CS_suite"

#endif
// end obsolete

#endif
//paths.h

