//---------------------------------------------------------------------------

#ifndef form_organic_N_applH
#define form_organic_N_applH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RNAutoCheckBox.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoRadioGroup.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "RNAutoFloatEdit.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
namespace CropSyst
{
class Organic_nitrogen_operation;
}
class Tparameter_file_form;
//---------------------------------------------------------------------------
class Torganic_N_application_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl1;
   TTabSheet *TabSheet1;
   TRNAutoRadioGroup *manure_type_radiogroup;
   TTabSheet *TabSheet2;
   TRNAutoParameterEditBar *NH3_volatil_loss_edit;
   TRNAutoParameterEditBar *NH3_ammonia_edit;
   TLabel *including_mineralized_org_n_label;
   TRNAutoCheckBox *NH3_volatil_loss_check;
   TPanel *panel_mass;
   TLabel *Label3;
   TRNAutoParameterEditBar *org_N_amount_edit;
   TLabel *org_drymatter_label;
   TLabel *Label4;
   TRNAutoFloatEdit *est_org_drymatter_out;
   TLabel *Label1;
   TPanel *panel_decomposition;
   TRNAutoCheckBox *org_N_decomp_time_check;
   TRNAutoParameterEditBar *org_N_decomp_time_50_edit;
   TRNAutoParameterEditBar *org_N_decomp_time_63_edit;
   TPanel *panel_NRCS_field_op;
   TComboBox *NRCS_org_N_field_op_number_combbox;
   TSpeedButton *button_NRCS_help;
   TRNAutoParameterEditBar *edit_carbon_fraction;
   TPanel *panel_volatilization_application;
   TRNAutoRadioGroup *orgN_form_radiogroup;
   TRNAutoRadioGroup *org_appl_method_radiogroup;
   void __fastcall org_N_decomp_time_checkClick(TObject *Sender);
   void __fastcall NH3_volatil_loss_check_onclick(TObject *Sender);
   void __fastcall NRCS_org_N_field_op_number_combboxChange(
          TObject *Sender);
   void __fastcall est_org_drymatter_outChange(TObject *Sender);
   void __fastcall org_N_amount_editExit(TObject *Sender);
   void __fastcall manure_type_radiogroupClick(TObject *Sender);
   void __fastcall button_NRCS_helpClick(TObject *Sender);
private:	// User declarations
   CropSyst::Organic_nitrogen_operation_abstract *operation;
   void show_hide_controls();
   float32 est_org_drymatter;
   Tparameter_file_form       *parameter_file_form;
public:		// User declarations
   __fastcall Torganic_N_application_form(TComponent* Owner);

   void bind_to(CropSyst::Organic_nitrogen_operation_abstract *peration,   Tparameter_file_form       *_parameter_file_form);
};
//---------------------------------------------------------------------------
extern PACKAGE Torganic_N_application_form *organic_N_application_form;
//---------------------------------------------------------------------------
#endif
