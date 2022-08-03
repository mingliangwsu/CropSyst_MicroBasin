//---------------------------------------------------------------------------

#ifndef form_updateH
#define form_updateH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "WUpdate.hpp"
#include "WUpdateWiz.hpp"
#include "WebCopy.hpp"
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tform_install_update : public TForm
{
__published:	// IDE-managed Components
   TPanel *panel_buttons;
   TBitBtn *button_update;
   TBitBtn *BitBtn2;
   TWebUpdateWizard *WebUpdateWizard_VX;
   TWebUpdate *WebUpdate_VX;
   TLabel *label_status;
   TWebCopy *webcopy_control_files;
   TWebCopy *webcopy_files;
   TPageControl *PageControl1;
   TTabSheet *TabSheet1;
   TTabSheet *tabsheet_setup;
   TGroupBox *groupbox_filesets;
   TLabel *Label2;
   TCheckBox *checkbox_programs;
   TCheckBox *checkbox_documentation;
   TCheckBox *checkbox_examples;
   TLabel *label_requires_internet;
   TLabel *label_additive;

   TGroupBox *GroupBox5;
   TLabel *Label3;
   TBitBtn *button_register_file_types;
   TGroupBox *GroupBox7;
   TButton *button_add_icons_all_desktop;
   TButton *button_add_icons_all_start;
   TLabel *Label5;
   TLabel *Label4;
   TTabSheet *tabsheet_installation_status;
   TListBox *listbox_installation_status;
   TWebUpdate *WebUpdate1;
   TPanel *panel_component_version;
   TRadioGroup *radio_group_version;
   TRadioGroup *radiogroup_components;
   TEdit *edit_source_URL;
   void __fastcall WebUpdate_VXGetFileList(TObject *Sender, TStringList *List);
   void __fastcall WebUpdate_VXProgressCancel(TObject *Sender, bool &Cancel);
   void __fastcall button_updateClick(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
   void __fastcall button_install_program_filesClick(TObject *Sender);
   void __fastcall button_install_CClick(TObject *Sender);
   void __fastcall radiogroup_componentsClick(TObject *Sender);
   void __fastcall button_register_file_typesClick(TObject *Sender);
   void __fastcall button_add_icons_all_desktopClick(TObject *Sender);
   void __fastcall button_add_icons_all_startClick(TObject *Sender);
   void __fastcall edit_source_URLChange(TObject *Sender);
   void __fastcall radio_group_versionClick(TObject *Sender);

private:	// User declarations
   AnsiString suite_path;       // I.e. C:\Program files\CS_suite_4
   AnsiString program_files_path;
   AnsiString installation_path;
   AnsiString windows_system_files_path;
   // The following files are identified for ShortCuts
   AnsiString CS_explorer_target_file;
   AnsiString CS_suite_target_file;
   AnsiString ClimGen_target_file;
   AnsiString UED_tools_target_file;
   // The following files are identified for filename associations
   AnsiString project_editor_target_file;       AnsiString project_ico_target_file; // V4 only
   AnsiString location_editor_target_file;      AnsiString location_ico_target_file; // V4 and ClimGen (In V5 we will have ClimGen_site) files.
   AnsiString format_editor_target_file;        AnsiString format_ico_target_file; // V4 only
   AnsiString scenario_editor_target_file;      AnsiString scenario_ico_target_file;
   AnsiString soil_editor_target_file;          AnsiString soil_ico_target_file;
   AnsiString rotation_editor_target_file;      AnsiString rotation_ico_target_file;
   AnsiString crop_editor_target_file;          AnsiString crop_ico_target_file;
   AnsiString management_editor_target_file;    AnsiString management_ico_target_file;
   AnsiString biomatter_editor_target_file;     AnsiString biomatter_ico_target_file;
   AnsiString schedule_viewer_target_file;      AnsiString schedule_ico_target_file;
   // The following files are identified for shortcuts and filename associations
   AnsiString UED_weather_editor_target_file;   AnsiString UED_ico_target_file;
   // The following files are for installation finalization
   AnsiString install_BPLs_exe;
   AnsiString update_exe;

public:		// User declarations
   __fastcall Tform_install_update(TComponent* Owner);
private:
   void backup_existing_installation();
   void download_files(const AnsiString &control_file_name);
   void create_short_cut
      (const AnsiString &target_file
      ,const char *szPath
      ,const char *caption
      ,const char *description
      );
   void add_buttons_to_desktop(bool all_users);
   void add_menus(bool all_users);
};
//---------------------------------------------------------------------------
extern PACKAGE Tform_install_update *form_install_update;
//---------------------------------------------------------------------------
#endif
