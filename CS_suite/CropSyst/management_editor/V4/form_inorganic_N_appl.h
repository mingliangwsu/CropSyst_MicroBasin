//______________________________________________________________________________

#ifndef form_inorganic_N_applH
#define form_inorganic_N_applH
//______________________________________________________________________________
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoCheckBox.h"
#include "AutoFloat32EditBar.h"
#include "AutoRadioGroup.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//______________________________________________________________________________
namespace CropSyst
{
   class Inorganic_nitrogen_operation;
};
class Tparameter_file_form;
//______________________________________________________________________________
class Tinorganic_N_application_form : public TForm
{
__published:	// IDE-managed Components
   TAutoFloat32EditBar *nitrate_edit;
   TAutoFloat32EditBar *ammonium_edit;
   TAutoCheckBox *NH4_volatil_loss_check;
   TAutoRadioGroup *NH4_source_radiogroup;
   TAutoRadioGroup *NH4_appl_method_radiogroup;
   TAutoFloat32EditBar *NH4_volatil_loss_edit;
   TPanel *panel_NRCS_field_op;
   TSpeedButton *button_NRCS_help;
   TComboBox *NRCS_inorganic_field_op_number_combbox;
   void __fastcall NH4_volatil_loss_checkClick(TObject *Sender);
   void __fastcall NRCS_inorganic_field_op_number_combboxChange(
          TObject *Sender);
   void __fastcall button_NRCS_helpClick(TObject *Sender);
private:	// User declarations
   CropSyst::Inorganic_nitrogen_operation_class *operation;
   virtual void show_hide_controls();
   Tparameter_file_form       *parameter_file_form;
public:		// User declarations
   __fastcall Tinorganic_N_application_form(TComponent* Owner);
   void bind_to(CropSyst::Inorganic_nitrogen_operation_class *_operation,   Tparameter_file_form       *_parameter_file_form);
};
//______________________________________________________________________________
extern PACKAGE Tinorganic_N_application_form *inorganic_N_application_form;
//______________________________________________________________________________
#endif
