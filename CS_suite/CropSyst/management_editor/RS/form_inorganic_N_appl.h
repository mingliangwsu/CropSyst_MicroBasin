//______________________________________________________________________________

#ifndef form_inorganic_N_applH
#define form_inorganic_N_applH
//______________________________________________________________________________
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RNAutoCheckBox.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoRadioGroup.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//______________________________________________________________________________
namespace CropSyst
{
class Inorganic_nitrogen_operation;
}
class Tparameter_file_form;
//______________________________________________________________________________
class Tinorganic_N_application_form : public TForm
{
__published:	// IDE-managed Components
   TRNAutoParameterEditBar *nitrate_edit;
   TRNAutoParameterEditBar *ammonium_edit;
   TRNAutoParameterEditBar *NH4_volatil_loss_edit;
   TPanel *panel_NRCS_field_op;
   TSpeedButton *button_NRCS_help;
   TComboBox *NRCS_inorganic_field_op_number_combbox;
   TRNAutoCheckBox *NH4_volatil_loss_check;
   TPanel *Panel1;
   TRNAutoRadioGroup *NH4_source_radiogroup;
   TRNAutoRadioGroup *NH4_appl_method_radiogroup;
   TGroupBox *GroupBox1;
   TRNAutoParameterEditBar *edit_N_soil_critical;
   TRNAutoParameterEditBar *edit_sampling_depth;
   TLabel *Label1;
   void __fastcall NH4_volatil_loss_checkClick(TObject *Sender);
   void __fastcall NRCS_inorganic_field_op_number_combboxChange(
          TObject *Sender);
   void __fastcall button_NRCS_helpClick(TObject *Sender);
private:	// User declarations
   CropSyst::Inorganic_nitrogen_operation *operation;
   virtual void show_hide_controls();
   Tparameter_file_form       *parameter_file_form;
public:		// User declarations
   __fastcall Tinorganic_N_application_form(TComponent* Owner);
   void bind_to(CropSyst::Inorganic_nitrogen_operation *i_operation,   Tparameter_file_form       *_parameter_file_form);
};
//______________________________________________________________________________
extern PACKAGE Tinorganic_N_application_form *inorganic_N_application_form;
//______________________________________________________________________________
#endif
