//---------------------------------------------------------------------------

#ifndef form_auto_clippingH
#define form_auto_clippingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoRadioGroup.h"
#include <ExtCtrls.hpp>
#include "AutoFloat32EditBar.h"
#include "AutoInt16EditBar.h"
#include "AutoCheckBox.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
//150402 #include "CropSyst/source/mgmt_param.h"
#include "CropSyst/source/management/management_param_V4.h"

class Tparameter_file_form;
//---------------------------------------------------------------------------

class Tauto_clipping_form : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *groupbox_condition;
   TAutoCheckBox *adjust_rate_clip_checkbox;
   TAutoFloat32EditBar *adjust_rate_clip_edit;
   TLabel *Label1;
   TAutoCheckBox *LAI_forces_clip_checkbox;
   TAutoFloat32EditBar *LAI_forces_clip_edit;
   TAutoCheckBox *biomass_forces_clip_checkbox;
   TAutoFloat32EditBar *biomass_forces_clip_edit;
   TAutoCheckBox *flowering_forces_clip_checkbox;
   TAutoInt16EditBar *flowering_forces_clip_edit;
   TGroupBox *groupbox_constraints;
   void __fastcall show_hide_controls(TObject *Sender);
//   void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:	// User declarations
   CropSyst::Auto_clip_biomass_mode
   //CropSyst::Auto_clip_biomass_mode_class
      *auto_clipping_mode;
   Tparameter_file_form       *parameter_file_form;
public:		// User declarations
   __fastcall Tauto_clipping_form(TComponent* Owner);
      void __fastcall bind_to
         (CropSyst::Auto_clip_biomass_mode *_auto_clipping_mode
         ,Tparameter_file_form       *_parameter_file_form);
      void __fastcall Update(void);
};
//---------------------------------------------------------------------------
extern PACKAGE Tauto_clipping_form *auto_clipping_form;
//---------------------------------------------------------------------------
#endif
