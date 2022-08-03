//---------------------------------------------------------------------------

#ifndef auto_N_mode_frmH
#define auto_N_mode_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoContainerListBox.h"
#include "AutoFloat32EditBar.h"
#include "AutoInt16EditBar.h"
#include "AutoRadioGroup.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Automatic_NO3_application_mode;
//---------------------------------------------------------------------------
class Tauto_N_appl_mode_form : public TForm
{
__published:	// IDE-managed Components
   void __fastcall auto_NO3_radio_group_onclick(TObject *Sender);
//040712 NYI currently there is only a single set of NO3 split applications
//040712   void __fastcall auto_NO3_appl_delete_button_onclick(TObject *Sender);

private:	// User declarations
   Automatic_NO3_application_mode *auto_N_app_mode_op;
// currently only allowing a single set of splits in management   int16                    auto_NO3_distribute_total; // This is the sum of the auot NO3 splits.
// currently only allowing a single set of splits in management   CORN::Valid_int16       *v_auto_NO3_distribute_total;
   bool                     crop_management;
//needed?   void sum_auto_N_distribute();

   void  show_hide_auto_NO3_parameters();
//040712 NYI currently there is only a single set of NO3 split applications
//040712 void __fastcall update_auto_NO3_application_controls();
//040712 void __fastcall auto_NO3_application_button_onclick(TObject *Sender);
//040712 void __fastcall auto_NO3_appl_delete_buttonClick(TObject *Sender);
public:		// User declarations
   __fastcall Tauto_N_appl_mode_form(TComponent* Owner);
   virtual __fastcall ~Tauto_N_appl_mode_form();
   void bind_to(Automatic_NO3_application_mode *i_auto_N_app_mode_op,bool i_crop_management);

};
//---------------------------------------------------------------------------
extern PACKAGE Tauto_N_appl_mode_form *auto_N_appl_mode_form;
//---------------------------------------------------------------------------
#endif
