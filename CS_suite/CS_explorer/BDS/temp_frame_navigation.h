
#error check obsolete, I should now have common navigation frames in GUI\explorer (for specific shellview component packages)
//---------------------------------------------------------------------------

#ifndef frame_navigationH
#define frame_navigationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "ShellControls.hpp"
#include "ShellLink.hpp"


class CS_Explorer_engine;
class Tform_CS_context;
//---------------------------------------------------------------------------
class Tnavigation_frame : public TFrame
{
__published:	// IDE-managed Components
   TJamShellList *JamShellList1;
   TJamShellTree *JamShellTree1;
   TJamShellLink *JamShellLink1;
private:	// User declarations
   Tform_CS_context *CS_context_form;
   CS_Explorer_engine   *explorer_engine;

public:		// User declarations
   __fastcall Tnavigation_frame(TComponent* Owner);

   void bind_to(Tform_CS_context *_CS_context_form,CS_Explorer_engine *_explorer_engine);
   bool select_folder(const char *folder_to_select_dir);
   unsigned int get_list_of_selected_files(CORN::Text_list &selected_filenames);//110402 cannot be const ;
};
//---------------------------------------------------------------------------
extern PACKAGE Tnavigation_frame *navigation_frame;
//---------------------------------------------------------------------------
#endif
