//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frame_CS_context_navigation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SsShlDlg"
#pragma link "StShlCtl"
#pragma link "StShrtCt"
#pragma link "SsBase"
#pragma link "StShrtCt"
#pragma resource "*.dfm"
#include <corn/file_sys/smart_filename.h>
#include "form_CS_explorer.h"
#include "../CS_explorer_engine.h"
#include <corn/container/text_list.h>

Tnavigation_frame *navigation_frame;
//---------------------------------------------------------------------------
__fastcall Tnavigation_frame::Tnavigation_frame(TComponent* Owner)
   : TFrame(Owner)
   , CS_context_form(0)
{}
//---------------------------------------------------------------------------
void Tnavigation_frame::bind_to
(Tform_CS_context    *_CS_context_form
,CS_Explorer_engine  *_explorer_engine
,const std::string   &_application_name
)
{
   CS_context_form = _CS_context_form;
   explorer_engine = _explorer_engine;
   shellnavigator_current_directory->Update();
   application_name = _application_name;
};
//---------------------------------------------------------------------------
void __fastcall Tnavigation_frame::shelllistview_current_directoryItemSelected(
      TObject *Sender, TStShellItem *Item)
{

   CORN::Smart_file_name selected_filename(Item->Path.c_str());
   Directory_entry_name::Directory_entry_type dir_entry_type =  selected_filename.identify_type();
   if (dir_entry_type == Directory_entry_name::file_entry)
   {  explorer_engine->navigator_single_clicked_file(selected_filename.c_str());
      CS_context_form->navigation_file_selected(selected_filename);
   }
   else if (dir_entry_type == Directory_entry_name::directory_entry)
   {
      CORN::Smart_file_name selected_dirname(Item->Path.c_str());
      CS_context_form->navigation_folder_selected(selected_dirname);
   };
};
//---------------------------------------------------------------------------
void __fastcall Tnavigation_frame::shelllistview_current_directoryItemDblClick(
      TObject *Sender, TStShellItem *Item, bool &DefaultAction)
{
   if (!Item->IsFolder)
   {  CORN::Smart_file_name clicked_file(Item->Path.c_str());                          //120412
      if (explorer_engine->navigator_double_clicked_file(clicked_file /*120412 Item->Path.c_str()*/))
      {
         CS_context_form->navigation_command_processed(explorer_engine->get_command());
         DefaultAction = false;
      }
   } else
      DefaultAction = true;
}
//---------------------------------------------------------------------------
void __fastcall Tnavigation_frame::recent_scenario_shelllistviewItemDblClick(
      TObject *Sender, TStShellItem *Item, bool &DefaultAction)
{
CORN::Smart_file_name filename( Item->Path.c_str());
   // Shellshock selects both directories and filenames
   // Here we allow the project directory to be selected
   // we append the csp extension to open the project
   // if either a directory or a project is made.
   if (filename.ext_is("lnk"))
   {  // If this is a link (I.e. from recent directory) then get the actual filename.
#ifdef StShrtCtHPP
// 090614   TStShortcut is provided by ShellShock VCL class library
//          This class is only available for BC C++ 5.0
      shortcutter->ShortcutFileName = Item->Path;
      if (shortcutter->ResolveShortcut())
         filename.set( shortcutter->FileName.c_str());
      else
#else
//090614  I need some other code to resolve short cuts
#endif
         return; // shortcut is no longer linked.
   }
   if (filename.exists())
   {
      if (explorer_engine->navigator_double_clicked_file(filename/*120412.c_str()*/))
      {  CS_context_form->navigation_command_processed(explorer_engine->get_command());
         DefaultAction = false;
      };
   };
}
//---------------------------------------------------------------------------
void __fastcall Tnavigation_frame
::shelltreeview_current_directoryFolderSelected(TObject *Sender, TStShellFolder *Folder)
{
   CS_context_form->navigation_folder_changed(Folder->Path.c_str());
}
//---------------------------------------------------------------------------
bool Tnavigation_frame
::select_folder(const char *folder_to_select_dir)
{  bool folder_selection_valid = false;
   shelltreeview_current_directory->Refresh(NULL);
   folder_selection_valid = folder_to_select_dir != NULL;
   if (folder_selection_valid) // 091207 (folder_to_select_dir)
         shelltreeview_current_directory->SelectFolder(folder_to_select_dir);
   return folder_selection_valid;
};
//---------------------------------------------------------------------------
void __fastcall Tnavigation_frame::shelllistview_current_directoryChange(
      TObject *Sender, TListItem *Item, TItemChange Change)
{ // 090911 check needed
  CS_context_form->navigation_current_directory_change();
}
//---------------------------------------------------------------------------
unsigned int Tnavigation_frame::get_list_of_selected_files(CORN::Text_list &selected_filenames) //110402 cannot be const
{
   uint32 select_items_count = shelllistview_current_directory->SelectedItems->Count;
   for (int i=0;i < (int) select_items_count;i++)
   {  // Items index is an int.
      selected_filenames.add(shelllistview_current_directory->SelectedItems->Items[i]->DisplayName.c_str());
   };
   return select_items_count;
};
//____________________________________________________________________________
void __fastcall Tnavigation_frame::button_launch_text_editClick(
      TObject *Sender)
{
command_history_memo->Lines->Append(explorer_engine->launch_notepad().c_str());
}
//---------------------------------------------------------------------------

void __fastcall Tnavigation_frame::button_launch_windows_explorerClick(
      TObject *Sender)
{
   explorer_engine->run_program_with_file
      ( "explorer.exe"
      , explorer_engine->get_directory_name_qualified().c_str()
      , ""
      , ""
      , false // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);
   
}
//---------------------------------------------------------------------------

void __fastcall Tnavigation_frame::button_command_promptClick(
      TObject *Sender)
{
  explorer_engine->run_program_with_file
      ( "cmd.exe"
      , explorer_engine->get_directory_name_qualified().c_str()
      , ""
      , "/K"
      , false // True if this editor is held until the other program exits
      , SW_SHOWNORMAL);   
}
//---------------------------------------------------------------------------

void __fastcall Tnavigation_frame::button_restore_window_positionClick(
      TObject *Sender)
{
  CORN::Smart_file_name desktop_ini("desktop.ini");
   desktop_ini.set_path(explorer_engine->get_directory_name_qualified());
   Top   = GetPrivateProfileInt(application_name.c_str()/*"CS_explorer"*/,"top"   ,Top     ,desktop_ini.c_str());
   Left  = GetPrivateProfileInt(application_name.c_str()/*"CS_explorer"*/,"left"  ,Left    ,desktop_ini.c_str());
   Height= GetPrivateProfileInt(application_name.c_str()/*"CS_explorer"*/,"height",Height  ,desktop_ini.c_str());
   Width = GetPrivateProfileInt(application_name.c_str()/*"CS_explorer"*/,"width" ,Width   ,desktop_ini.c_str());

}
//---------------------------------------------------------------------------
void __fastcall Tnavigation_frame::button_set_window_positionClick(TObject *Sender)
{
   CORN::Smart_file_name desktop_ini("desktop.ini");
   desktop_ini.set_path(explorer_engine->get_directory_name_qualified());
   char int_buffer[10];
   WritePrivateProfileString(application_name.c_str()/*"CS_explorer"*/,"top"   ,itoa(Top,int_buffer,10)     ,desktop_ini.c_str());
   WritePrivateProfileString(application_name.c_str()/*"CS_explorer"*/,"left"  ,itoa(Left,int_buffer,10)    ,desktop_ini.c_str());
   WritePrivateProfileString(application_name.c_str()/*"CS_explorer"*/,"height",itoa(Height,int_buffer,10)  ,desktop_ini.c_str());
   WritePrivateProfileString(application_name.c_str()/*"CS_explorer"*/,"width" ,itoa(Width,int_buffer,10)   ,desktop_ini.c_str());
   button_restore_window_position->Visible = true;
}
//---------------------------------------------------------------------------

