//---------------------------------------------------------------------------

#ifndef form_auto_clippingH
#define form_auto_clippingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RNAutoRadioGroup.h"
#include <ExtCtrls.hpp>
#include "RNAutoParameterEditBar.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoCheckBox.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
//Forward declarations
namespace CropSyst
{
class Auto_clip_biomass_mode;
}
class Tparameter_file_form;
//---------------------------------------------------------------------------

class Tauto_clipping_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl1;
   TTabSheet *condition_tabsheet;
   TTabSheet *operation_tabsheet;
   TRNAutoParameterEditBar *adjust_rate_clip_edit;
   TRNAutoParameterEditBar *biomass_forces_clip_edit;
   TRNAutoParameterEditBar *LAI_forces_clip_edit;
   TRNAutoParameterEditBar *flowering_forces_clip_edit;
   TRNAutoCheckBox *adjust_rate_clip_checkbox;
   TRNAutoCheckBox *LAI_forces_clip_checkbox;
   TRNAutoCheckBox *biomass_forces_clip_checkbox;
   TRNAutoCheckBox *flowering_forces_clip_checkbox;
   TLabel *Label1;
   void __fastcall show_hide_controls(TObject *Sender);
//   void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:	// User declarations
   CropSyst::Auto_clip_biomass_mode *auto_clipping_mode;
   Tparameter_file_form       *parameter_file_form;
public:		// User declarations
   __fastcall Tauto_clipping_form(TComponent* Owner);
      void __fastcall bind_to(CropSyst::Auto_clip_biomass_mode *i_auto_clipping_mode,   Tparameter_file_form       *_parameter_file_form);
      void __fastcall Update(void);
};
//---------------------------------------------------------------------------
extern PACKAGE Tauto_clipping_form *auto_clipping_form;
//---------------------------------------------------------------------------
#endif
