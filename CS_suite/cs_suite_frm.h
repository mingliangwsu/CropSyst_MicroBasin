//---------------------------------------------------------------------------

#ifndef cs_suite_frmH
#define cs_suite_frmH
//---------------------------------------------------------------------------
#include <Registry.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SHDocVw_OCX.h"
#include <ComCtrls.hpp>
#include <OleCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Graphics.hpp>
#include "AutoRadioGroup.h"
#include "FlCtrlEx.hpp"
#include "SsShlDlg.hpp"
#include "StShlCtl.hpp"
#include "SsBase.hpp"
#include "StShrtCt.hpp"
#include "AdvDirectoryEdit.hpp"
#include "AdvEdBtn.hpp"
#include "AdvEdit.hpp"
#include "AutoViewFileButton.h"
#include "AutoUnitsButton.h"
#include "corn/string/strconv.h"
#include "corn/parameters/parameters.h"
#include "CropSyst/source/options.h"
#include "CropSyst/source/project_types.h"
//---------------------------------------------------------------------------
//Forward declarations:
class Database_directory_paths;
//---------------------------------------------------------------------------
class TCS_suite_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *cs_suite_pagecontrol;
   TTabSheet *instructions_sheet;
   TCppWebBrowser *instructions_webbrowser;
   TTabSheet *utilities_tabsheet;
   TOpenDialog *project_open_dialog;
   TTabSheet *projects_tabsheet;
   TTabSheet *about_tabsheet;
   TCppWebBrowser *about_webbrowser;
   TPanel *cropsyst_button_panel;
   TImage *cropsyst_image;
   TPanel *arccs_button_panel;
   TPanel *watershed_button_panel;
   TImage *arccs_image;
   TImage *watershed_image;
   TAutoRadioGroup *project_type_radiobuttons;
   TBitBtn *climgen_button;
   TPanel *utilities_instruction_panel;
   TCppWebBrowser *utilities_webbrowser;
   TPanel *climgen_button_panel;
   TImage *climgen_image;
   TLabel *climgen_button_label;
   TBitBtn *register_file_type_button;
   TPanel *calib_panel;
   TImage *crop_calibrator_image;
   TLabel *crop_calibrator_button_label;
   TBitBtn *project_help_button;
   TStShortcut *shortcutter;
   TLabel *Label1;
   TAdvDirectoryEdit *master_sim_diredit;
   TLabel *watershed_not_yet_implement;
   TPageControl *pagecontrol_projects_list;
        TTabSheet *simulation_projects_tabsheet;
        TTabSheet *recent_projects_tabsheet;
        TStShellNavigator *simulation_project_shelllistnag;
        TStShellListView *recent_project_shelllistview;
        TStShellListView *simulation_projects_shelllistview;
        TBitBtn *project_open_button;
   TBitBtn *location_edit_button;
   TLabel *Label2;
   TLabel *Label3;
   TPanel *Panel1;
   TBitBtn *close_button;
   TBitBtn *database_button;
   TAutoUnitsButton *button_version;
   TBitBtn *help_button;
   TPanel *panel_lauch_CS_explorer;
   TImage *image_CS_explorer;
   void __fastcall project_open_button_onclick(TObject *Sender);
   void __fastcall change_display(TObject *Sender);
   void __fastcall watershed_image_onclick(TObject *Sender);
   void __fastcall cropsyst_image_onclick(TObject *Sender);
   void __fastcall arccs_image_onclick(TObject *Sender);
   void __fastcall cropsyst_image_ondblclick(TObject *Sender);
   void __fastcall arccs_image_ondblclick(TObject *Sender);
   void __fastcall watershed_image_ondblclick(TObject *Sender);

   void __fastcall database_button_panel_onclick(TObject *Sender);

   void __fastcall climgen_image_onclick(TObject *Sender);
   void __fastcall help_button_onclick(TObject *Sender);
   void __fastcall register_file_types(TObject *Sender);
   void __fastcall crop_calib_image_onclick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall project_help_button_onclick(TObject *Sender);
   void __fastcall recent_project_shelllistviewItemDblClick(
          TObject *Sender, TStShellItem *Item, bool &DefaultAction);

   void __fastcall master_sim_diredit_onchange(TObject *Sender);
        void __fastcall simulation_projects_shelllistviewItemDblClick(
          TObject *Sender, TStShellItem *Item, bool &DefaultAction);
   void __fastcall location_edit_button_onclick(TObject *Sender);
   void __fastcall pagecontrol_projects_listChange(TObject *Sender);
   void __fastcall simulation_project_shelllistnagFolderSelected(
          TObject *Sender, TStShellFolder *Folder);
   void __fastcall button_versionClick(TObject *Sender);
   void __fastcall panel_lauch_CS_explorerClick(TObject *Sender);

private:	// User declarations
   Database_directory_paths  *common_database;
   CropSyst_project_type_labeled    curr_project_mode_labeled;
   AnsiString  target_project_directory;
      // When the user changes the simulation project shell list navigator
      // Then we need to remember

   void setup_mode(CropSyst_project_type mode);
   void update_buttons();
   void  show_hide_register_file_types_button();
   void register_extension
      (TRegIniFile *reginifile
      ,const char *extension
      ,const char *description
      ,const char *program
      ,const char *icon
      );

   bool show_master_sim_note_on_create;

public:		// User declarations
   __fastcall TCS_suite_form(TComponent* Owner);
   void  load_settings();
   void  save_settings();
};
//---------------------------------------------------------------------------
extern PACKAGE TCS_suite_form *CS_suite_form;
//---------------------------------------------------------------------------
#endif

