#error check obsolete, I should now have common navigation frames in GUI\explorer (for specific shellview component packages)
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "../CS_explorer_engine.h"

#include "form_CS_explorer.h"

#include "frame_navigation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ShellControls"
#pragma link "ShellLink"

#pragma resource "*.dfm"
Tnavigation_frame *navigation_frame;
//---------------------------------------------------------------------------
__fastcall Tnavigation_frame::Tnavigation_frame(TComponent* Owner)
   : TFrame(Owner)
   , CS_context_form(0)
{
}
//---------------------------------------------------------------------------
void Tnavigation_frame::bind_to
(Tform_CS_context    *_CS_context_form
,CS_Explorer_engine  *_explorer_engine)
{
   CS_context_form = _CS_context_form;
   explorer_engine = _explorer_engine;
//NYI   shellnavigator_current_directory->Update();
};
//---------------------------------------------------------------------------
bool Tnavigation_frame
::select_folder(const char *folder_to_select_dir)
{  bool folder_selection_valid = false;
#ifdef NYI
   shelltreeview_current_directory->Refresh(NULL);
   folder_selection_valid = folder_to_select_dir != NULL;
   if (folder_selection_valid) // 091207 (folder_to_select_dir)
         shelltreeview_current_directory->SelectFolder(folder_to_select_dir);
#endif         
   return folder_selection_valid;
};
//---------------------------------------------------------------------------
unsigned int Tnavigation_frame::get_list_of_selected_files(CORN::Text_list &selected_filenames) //110402 cannot be const
{
#ifdef NYI
   uint32 select_items_count = shelllistview_current_directory->SelectedItems->Count;
   for (int i=0;i < (int) select_items_count;i++)
   {  // Items index is an int.
      selected_filenames.add(shelllistview_current_directory->SelectedItems->Items[i]->DisplayName.c_str());
   };
   return select_items_count;
#endif   
};

