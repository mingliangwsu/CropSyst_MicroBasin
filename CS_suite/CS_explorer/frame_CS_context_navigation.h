//---------------------------------------------------------------------------


#ifndef frame_CS_context_navigationH
#define frame_CS_context_navigationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SsShlDlg.hpp"
#include "StShlCtl.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "SsBase.hpp"
#include "StShrtCt.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------

class Tform_CS_context;
class CS_Explorer_engine;
namespace CORN
{
   class Text_list;
};

class Tnavigation_frame : public TFrame
{
__published:	// IDE-managed Components
   TPageControl *pagecontrol_navigation;
   TTabSheet *tabsheet_expore;
   TTabSheet *TabSheet2;
   TSplitter *Splitter1;
   TPanel *panel_location;
   TEdit *edit_current_folder_path;
   void __fastcall shelllistview_current_directoryItemSelected(
          TObject *Sender, TStShellItem *Item);
   void __fastcall shelllistview_current_directoryItemDblClick(
          TObject *Sender, TStShellItem *Item, bool &DefaultAction);
   void __fastcall recent_scenario_shelllistviewItemDblClick(
          TObject *Sender, TStShellItem *Item, bool &DefaultAction);
   void __fastcall shelltreeview_current_directoryFolderSelected(
          TObject *Sender, TStShellFolder *Folder);
   void __fastcall shelllistview_current_directoryChange(TObject *Sender,
          TListItem *Item, TItemChange Change);
   void __fastcall button_launch_text_editClick(TObject *Sender);
   void __fastcall button_launch_windows_explorerClick(TObject *Sender);
   void __fastcall button_command_promptClick(TObject *Sender);
   void __fastcall button_restore_window_positionClick(TObject *Sender);
   void __fastcall button_set_window_positionClick(TObject *Sender);
private:
   Tform_CS_context     *CS_context_form;
   CS_Explorer_engine   *explorer_engine;
   std::string          &application_name;
public:		// User declarations
   __fastcall Tnavigation_frame(TComponent* Owner);
   void bind_to
      (Tform_CS_context    *_CS_context_form
      ,CS_Explorer_engine  *_explorer_engine
      ,const std::string   &_application_name
      );
   bool select_folder(const char *folder_to_select_dir);
   unsigned int get_list_of_selected_files(CORN::Text_list &selected_filenames)//110402 cannot be const ;
};
//---------------------------------------------------------------------------
extern PACKAGE Tnavigation_frame *navigation_frame;
//---------------------------------------------------------------------------
#endif
