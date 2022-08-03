//---------------------------------------------------------------------------

#ifndef form_rotation_editorH
#define form_rotation_editorH
//______________________________________________________________________________
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RNAutoContainerCheckListBox.h"
#include "RNAutoIntegerEdit.h"
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
//______________________________________________________________________________
namespace CropSyst
{  class Rotation_parameters;
}
class Tparameter_file_form;
//______________________________________________________________________________
class Trotation_editor_form : public TForm
{
__published:	// IDE-managed Components
   TPanel *panel_edit;
   TGroupBox *GroupBox1;
   TBitBtn *button_planting;
   TBitBtn *button_edit;
   TBitBtn *button_delete;
   TBitBtn *button_sort;
   TLabel *label_years;
   TLabel *label_end_year;
   TButton *button_build;
   TRNAutoIntegerEdit *edit_end;
   TRNAutoIntegerEdit *edit_years;
   TRNAutoContainerCheckListBox *listbox_rotation;
   void __fastcall button_editClick(TObject *Sender);
   void __fastcall button_deleteClick(TObject *Sender);
//   void __fastcall listbox_rotationClick(TObject *Sender);
   void __fastcall button_plantingClick(TObject *Sender);
   void __fastcall button_sortClick(TObject *Sender);
   void __fastcall button_buildClick(TObject *Sender);
   void __fastcall listbox_rotationDblClick(TObject *Sender);
 private: // User declarations
   CropSyst::Rotation_parameters  *rotation;
   Tparameter_file_form           *parameter_form;
 public: // User declarations
   __fastcall Trotation_editor_form(TComponent* Owner);
   void __fastcall bind_to
   (CropSyst::Rotation_parameters   *rotation                                    //130415
   ,Tparameter_file_form            *parameter_form
   //,const char                      *master_database_dir
   //,const char                      *project_database_dir
   //,const char                      *scenario_database_dir
   );
   //Not sure if needed   virtual void __fastcall Update();
   inline virtual TPageControl *get_main_page_control() const { return 0;};
      // The new rotation editor doesn't have page control
};
//---------------------------------------------------------------------------
extern PACKAGE Trotation_editor_form *rotation_editor_form;
//---------------------------------------------------------------------------
#endif
