//---------------------------------------------------------------------------

#ifndef form_CS_explorerH
#define form_CS_explorerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//090807#include "AutoFileEditBar.h"
//090807#include "AutoCheckBox.h"
//090807#include "AutoRadioGroup.h"
//090807#include "AutoViewFileButton.h"
#include "FlCtrlEx.hpp"
#include <CheckLst.hpp>
#include <FileCtrl.hpp>
//090807#include "AutoUnitsButton.h"
#include <ImgList.hpp>
#include <Graphics.hpp>
#include "AdvEdBtn.hpp"
#include "AdvEdit.hpp"
#include "AdvFileNameEdit.hpp"
#include "AdvCombo.hpp"
//090807#include "SsBase.hpp"
//090807#include "StShrtCt.hpp"
//---------------------------------------------------------------------------
#include <corn/application/program_directory.h>
#include <CS_suite/application/CS_suite_directory.h>
#include <CropSyst/cpp/output.h>

//---------------------------------------------------------------------------
class CS_Explorer_engine;
class CropSyst_scenario_output_options;
class Tnavigation_frame;
//______________________________________________________________________________
class Tform_CS_context : public TForm
{
__published:	// IDE-managed Components
   TPanel *panel_navigation;
   TPanel *panel_buttons;
   TBitBtn *button_close;
   TBitBtn *button_webpage;
   TPageControl *PageControl4;
   TTabSheet *tabsheet_context_current;
   TPageControl *pagecontrol_context;
   TTabSheet *tabsheet_arbitrary;
   TTabSheet *tabsheet_project;
   TBitBtn *button_project_cabon_sequestration;
   TBitBtn *button_project_GIS_simulation;
   TGroupBox *GroupBox9;
   TBitBtn *button_project_database;
   TTabSheet *tabsheet_scenario;
   TGroupBox *GroupBox2;
   TLabel *Label3;
   TLabel *Label4;
   TPanel *button_scenario_analysis;
   TTabSheet *tabsheet_database;
   TGroupBox *groupbox_database_parameter_file;
   TPanel *panel_database_add_weather;
   TPanel *panel_database_add_soil;
   TGroupBox *groupbox_database_secondary_files;
   TPanel *panel_database_add_biomatter;
   TPanel *panel_database_add_format;
   TTabSheet *tabsheet_scenarios;
   TPageControl *pagecontrol_scenarios;
   TTabSheet *tabsheet_scenarios_run;
   TGroupBox *groupbox_scenarios_crop_production_function;
   TTabSheet *tabsheet_scenarios_reset;
   TGroupBox *groupbox_scenarios_model_options;
   TCheckBox *checkbox_scenarios_reset_submodels;
   TCheckBox *checkbox_scenarios_reset_output;
   TCheckBox *checkbox_scenarios_reset_CPF;
   TCheckBox *checkbox_scenarios_reset_CO2;
   TGroupBox *groupbox_scenarios_initial;
   TCheckBox *checkbox_initial_reset_soil_profile;
   TCheckBox *checkbox_initial_reset_soil_N;
   TCheckBox *checkbox_initial_reset_residue;
   TCheckBox *checkbox_initial_reset_manure;
   TCheckBox *checkbox_initial_reset_organic_matter;
   TGroupBox *groupbox_scenarios_param_files;
   TCheckBox *checkbox_param_reset_weather;
   TCheckBox *checkbox_param_reset_soil;
   TCheckBox *checkbox_param_reset_rotation;
   TCheckBox *checkbox_param_reset_recalibration;
   TPanel *button_scenarios_reset;
   TTabSheet *tabsheet_scenarios_analysis;
   TLabel *Label12;
   TLabel *Label2;
   TLabel *Label13;
   TPanel *Panel8;
   TTabSheet *tabsheet_weather;
   TTabSheet *tabsheet_rotation;
   TTabSheet *tabsheet_management;
   TBitBtn *button_management_combinatorial_generation;
   TTabSheet *tabsheet_biomatter;
   TTabSheet *tabsheet_crop;
   TLabel *Label7;
   TBitBtn *create_generic_crop_button;
   TBitBtn *create_fruit_crop_button;
   TBitBtn *create_CROPGRO_crop_button;
   TTabSheet *tabsheet_soil;
   TBitBtn *button_soil_import;
   TTabSheet *tabsheet_format;
   TTabSheet *tabsheet_STATSGO;
   TLabel *Label6;
   TCheckListBox *installed_STATSGO_states_listbox;
   TPanel *panel_STATSGO_install_function;
   TDirectoryListBox *statsgo_directory_treelist;
   TFileListBoxEx *stats_go_filelist;
   TPanel *Panel9;
   TBitBtn *install_button;
   TBitBtn *remove_button;
   TTabSheet *tabsheet_scenario_output;
   TGroupBox *groupbox_reports_to_be_generated;
   TListBox *listbox_pending_reports;
   TPanel *panel_generate_reports;
   TBitBtn *output_reexport_button;
   TProgressBar *progress_bar;
   TPanel *panel_output_buttons;
   TBitBtn *button_documentation_help;
   TBitBtn *button_documentation_FAQ;
   TBitBtn *button_documentation_manual;
   TBitBtn *button_documentation_tutorial;
   TBitBtn *button_project_scenarios;
   TImageList *scenarios_pagecontrol_images;
   TImage *Image1;
   TImage *Image2;
   TImage *Image6;
   TImage *Image7;
   TPageControl *PageControl2;
   TTabSheet *tabsheet_scenario_output_hint_1;
   TGroupBox *groupbox_database_cropping_system_parameter_file;
   TImage *Image10;
   TPanel *panel_database_add_management;
   TImage *Image11;
   TPanel *panel_database_add_crop;
   TImage *Image12;
   TTabSheet *tabsheet_generated_scenarios;
   TLabel *Label5;
   TBitBtn *button_soil_new;
   TBitBtn *button_rotation_create;
   TBitBtn *button_crop_create;
   TBitBtn *button_project_scenario_create;
   TBitBtn *button_biomatter_create;
   TBitBtn *button_management_create;
   TBitBtn *button_format_create;
   TBitBtn *button_arbitrary_project_new;
   TBitBtn *BitBtn11;
   TEdit *edit_arbitrary_project_name;
   TTabSheet *tabsheet_commands;
   TLabel *Label15;
   TMemo *command_history_memo;
   TPanel *panel_database_add_rotation;
   TBitBtn *button_scenario_database;
   TEdit *edit_project_scenario_name;
   TEdit *edit_format_name;
   TEdit *edit_soil_name;
   TEdit *edit_rotation_name;
   TEdit *edit_crop_name;
   TEdit *edit_management_name;
   TEdit *edit_biomatter_name;
   TLabel *label_rotation_hint;
   TBitBtn *button_project_watershed_simulation;
   TButton *button_version;
   TPanel *panel_scenarios_report_format;
   TAdvFileNameEdit *edit_scenarios_report_filename;
   TRadioGroup *groupbox_scenarios_format;
   TLabel *label_scenarios_report_format;
   TBitBtn *fast_graph_button;
   TBitBtn *formated_schedule_button;
   TBitBtn *harvest_report_button;
   TBitBtn *text_schedule_button;
   TCheckBox *checkbox_scenarios_CPF_water;
   TBitBtn *button_soil_SOILPAR2;
   TGroupBox *groupbox_arbitrary_simulation_folder;
   TBitBtn *button_arbitrary_create_simulation_folder;
   TCheckBox *checkbox_scenario_display_runtime_graph;
   TBitBtn *button_scenario_run;
   TBitBtn *combinatorial_project_scenario_generation_button;
   TAdvFileNameEdit *filenameedit_project_combinatorial_scenario_template;
   TLabel *Label11;
   TButton *button_output_edit_report_generation;
   TRichEdit *RichEdit1;
   TRichEdit *RichEdit2;
   TRichEdit *RichEdit3;
   TBitBtn *button_scenario_edit;
   TPanel *panel_scenario_report_format;
   TLabel *label_scenario_report_format;
   TAdvFileNameEdit *edit_scenario_report_filename;
   TRadioGroup *groupbox_scenario_format;
   TPanel *panel_location;
   TEdit *edit_current_folder_path;
   TSpeedButton *button_command_prompt;
   TSpeedButton *button_restore_window_position;
   TSpeedButton *button_set_window_position;
   TButton *button_scenario_edit_CANMS;
   TButton *button_scenario_run_CANMS;
   TBitBtn *button_project_CANMS_enterprises;
   TTabSheet *tabsheet_enterprises;
   TRichEdit *RichEdit4;
   TEdit *edit_enterprise_name;
   TBitBtn *button_enterprise_create;
   TBitBtn *button_CANMS;
   TTabSheet *tabsheet_scenarios_create;
   TBitBtn *button_scenarios_create_CropSyst_scenario;
   TPanel *panel_scenarios_create;
   TEdit *edit_scenarios_scenario_name;
   TLabel *label_scenarios_create_hint;
   TBitBtn *BitBtn1;
   TPanel *panel_scenarios_run_options;
   TPanel *Panel1;
   TAdvFileNameEdit *filenameedit_simulation_model;
   TPanel *panel_scenarios_run;
   TBitBtn *button_senerios_run;
   TCheckBox *checkbox_scenarios_run_simultaneously;
   TCheckBox *checkbox_scenarios_run_statistical_analysis;
   TPanel *panel_scenarios_enterprise;
   TAdvFileNameEdit *filenameedit_enterprise;
   TComboBox *combobox_project_scenarios;
   TComboBox *combobox_project_database;
   TComboBox *combobox_project_enterprises;
   TComboBox *combobox_abritrary_simulation_folder_name;
   TComboBox *combobox_arbitrary_projects;
   TComboBox *combobox_scenario_database;
   TComboBox *combo_box_database_weather;
   TComboBox *combo_box_database_soil;
   TComboBox *combo_box_database_crop;
   TComboBox *combo_box_database_management;
   TComboBox *combo_box_database_rotation;
   TComboBox *combo_box_database_biomatter;
   TComboBox *combo_box_database_format;
   TComboBox *ComboBox1;
   TComboBox *combobox_arbitrary_database;
   TLabel *Label1;
   TLabel *Label8;
   TPanel *panel_arbitrary_assume_context;
   TAdvComboBox *combobox_arbitrary_assume_context;
   TSpeedButton *button_lauch_CS_explorer;
   TSpeedButton *button_launch_windows_explorer;
   TSpeedButton *SpeedButton1;
   TSpeedButton *button_lauch_CS_suite;
   TSpeedButton *button_launch_text_edit;
   TRichEdit *RichEdit5;
   TPanel *panel_weather_buttons;
   TBitBtn *button_create_weather;
   TEdit *edit_weather_name;
   TBitBtn *button_weather_UED_spatial;
   TBitBtn *button_weather_import_UED;
   TBitBtn *button_weather_export_UED;
   TBitBtn *button_weather_climgen;
   TBitBtn *button_weather_map_UED_locations;
   TBitBtn *UED_association_button;
   TBitBtn *button_UED_condense;
   TCheckBox *checkbox_UED_tools_mode;
   void __fastcall button_project_scenario_createClick(TObject *Sender);
   void __fastcall button_project_scenariosClick(TObject *Sender);
   void __fastcall button_project_databaseClick(TObject *Sender);
   void __fastcall button_project_GIS_simulationClick(TObject *Sender);
   void __fastcall button_project_watershed_simulationClick(TObject *Sender);
   void __fastcall button_project_cabon_sequestrationClick(TObject *Sender);
   void __fastcall button_project_statsClick(TObject *Sender);
   void __fastcall button_arbitrary_project_newClick(TObject *Sender);
   void __fastcall button_arbitrary_create_simulation_folderClick(TObject *Sender);
   void __fastcall button_format_createClick(TObject *Sender);
   void __fastcall panel_database_add_weatherClick(TObject *Sender);
   void __fastcall panel_database_add_soilClick(TObject *Sender);
   void __fastcall panel_database_add_rotationClick(TObject *Sender);
   void __fastcall panel_database_add_cropClick(TObject *Sender);
   void __fastcall panel_database_add_managementClick(TObject *Sender);
   void __fastcall panel_database_add_biomatterClick(TObject *Sender);
   void __fastcall panel_database_add_formatClick(TObject *Sender);
   void __fastcall button_scenario_databaseClick(TObject *Sender);
   void __fastcall button_create_weatherClick(TObject *Sender);
   void __fastcall button_weather_import_UEDClick(TObject *Sender);
   void __fastcall button_weather_export_UEDClick(TObject *Sender);
   void __fastcall button_weather_climgenClick(TObject *Sender);
   void __fastcall button_weather_UED_spatialClick(TObject *Sender);
   void __fastcall button_soil_newClick(TObject *Sender);
   void __fastcall button_biomatter_createClick(TObject *Sender);
   void __fastcall button_management_createClick(TObject *Sender);
   void __fastcall button_crop_createClick(TObject *Sender);
   void __fastcall button_rotation_createClick(TObject *Sender);
   void __fastcall fast_graph_button_Click(TObject *Sender);
   void __fastcall formated_schedule_button_Click(TObject *Sender);
   void __fastcall text_schedule_button_Click(TObject *Sender);
   void __fastcall harvest_report_button_Click(TObject *Sender);
   void __fastcall output_reexport_buttonClick(TObject *Sender);
   void __fastcall create_fruit_crop_buttonClick(TObject *Sender);
   void __fastcall create_CROPGRO_crop_buttonClick(TObject *Sender);
   void __fastcall create_generic_crop_buttonClick(TObject *Sender);
   void __fastcall button_soil_importClick(TObject *Sender);
   void __fastcall button_soil_SOILPAR2_Click(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall button_scenarios_create_CropSyst_scenarioClick(TObject *Sender);
   void __fastcall button_senerios_runClick(TObject *Sender);
   void __fastcall button_scenario_runClick(TObject *Sender);
   void __fastcall button_scenarios_resetClick(TObject *Sender);
   void __fastcall Panel8Click(TObject *Sender);
   void __fastcall combinatorial_project_scenario_generation_buttonClick(TObject *Sender);
   void __fastcall button_webpageClick(TObject *Sender);
   void __fastcall listbox_pending_reportsClick(TObject *Sender);
   void __fastcall button_output_edit_report_generationClick(TObject *Sender);
   void __fastcall button_documentation_manualClick(TObject *Sender);
   void __fastcall button_command_promptClick(TObject *Sender);
   void __fastcall button_set_window_positionClick(TObject *Sender);
   void __fastcall button_restore_window_positionClick(TObject *Sender);
   void __fastcall button_scenario_editClick(TObject *Sender);
   void __fastcall groupbox_scenario_formatClick(TObject *Sender);
   void __fastcall groupbox_scenarios_formatClick(TObject *Sender);
   void __fastcall button_documentation_helpClick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall button_scenario_edit_CANMSClick(TObject *Sender);
   void __fastcall button_project_CANMS_enterprisesClick(TObject *Sender);
   void __fastcall button_enterprise_createClick(TObject *Sender);
   void __fastcall button_scenario_run_CANMSClick(TObject *Sender);
   void __fastcall button_scenarios_create_CANMS_scenarioClick(TObject *Sender);
   void __fastcall combobox_arbitrary_assume_contextChange(TObject *Sender);
   void __fastcall button_launch_windows_explorerClick(TObject *Sender);
   void __fastcall button_lauch_CS_explorerClick(TObject *Sender);
   void __fastcall SpeedButton1Click(TObject *Sender);
   void __fastcall button_lauch_CS_suiteClick(TObject *Sender);
   void __fastcall button_weather_map_UED_locationsClick(TObject *Sender);
   void __fastcall button_launch_text_editClick(TObject *Sender);
   void __fastcall edit_current_folder_pathChange(TObject *Sender);
   void __fastcall checkbox_UED_tools_modeClick(TObject *Sender);
   void __fastcall UED_association_buttonClick(TObject *Sender);
   void __fastcall button_UED_condenseClick(TObject *Sender);
private:	// User declarations
   CS_Explorer_engine   *explorer_engine;
//   CS::Suite_directory  *CS_suite_directory;   // guarenteed to be setup and not null.
   CORN::Program_directory CS_explorer_directory;
   Tnavigation_frame *navigation_frame;
public:		// User declarations
   __fastcall Tform_CS_context(TComponent* Owner);
private:
   void show_hide_controls();
private: // The following methods are common to both CS_explorer and the output_manager_advanced
   // They are implemented in form_common_output_management.cpp
   void update_list_of_pending_reports();
   void output_convert_pending_report();
   bool report_out_of_sync(const CropSyst_scenario_output_options::Conversion *conversion);
   void show_context(int context);
public:  // Navigation event handlers
   void navigation_file_selected  (const CORN::Smart_file_name &selected_filename);
   void navigation_folder_selected(const CORN::Smart_directory_name &selected_folder);

   void navigation_command_processed(const std::string &command);
   void navigation_folder_changed(const char *folder_path);
   void navigation_current_directory_change();
};
//---------------------------------------------------------------------------
extern PACKAGE Tform_CS_context *form_CS_context;
//---------------------------------------------------------------------------
#endif
