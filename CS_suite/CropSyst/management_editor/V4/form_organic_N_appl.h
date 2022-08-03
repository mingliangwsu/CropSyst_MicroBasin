//---------------------------------------------------------------------------

#ifndef form_organic_N_applH
#define form_organic_N_applH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoCheckBox.h"
#include "AutoFloat32EditBar.h"
#include "AutoInt16EditBar.h"
#include "AutoRadioGroup.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "AutoFloat32Edit.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "residue/residue_const.h"
namespace CropSyst
{  class Organic_nitrogen_operation;
};
class Tparameter_file_form;
//---------------------------------------------------------------------------
class Torganic_N_application_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl1;
   TTabSheet *TabSheet1;
   TAutoRadioGroup *manure_type_radiogroup;
   TTabSheet *TabSheet2;
   TAutoFloat32EditBar *NH3_volatil_loss_edit;
   TAutoFloat32EditBar *NH3_ammonia_edit;
   TLabel *including_mineralized_org_n_label;
   TAutoCheckBox *NH3_volatil_loss_check;
   TAutoRadioGroup *org_appl_method_radiogroup;
   TAutoRadioGroup *orgN_form_radiogroup;
   TPanel *panel_mass;
   TLabel *Label3;
   TAutoFloat32EditBar *org_N_amount_edit;
   TLabel *org_drymatter_label;
   TLabel *Label4;
   TAutoFloat32Edit *est_org_drymatter_out;
   TLabel *Label1;
   TPanel *panel_decomposition;
   TAutoCheckBox *org_N_decomp_time_check;
   TAutoInt16EditBar *org_N_decomp_time_50_edit;
   TAutoInt16EditBar *org_N_decomp_time_63_edit;
   TPanel *panel_NRCS_field_op;
   TComboBox *NRCS_org_N_field_op_number_combbox;
   TSpeedButton *button_NRCS_help;
   TAutoFloat32EditBar *edit_carbon_fraction;
   void __fastcall org_N_decomp_time_checkClick(TObject *Sender);
   void __fastcall NH3_volatil_loss_check_onclick(TObject *Sender);
   void __fastcall NRCS_org_N_field_op_number_combboxChange(
          TObject *Sender);
   void __fastcall est_org_drymatter_outChange(TObject *Sender);
   void __fastcall org_N_amount_editExit(TObject *Sender);
   void __fastcall manure_type_radiogroupClick(TObject *Sender);
   void __fastcall button_NRCS_helpClick(TObject *Sender);
private:	// User declarations
   CropSyst::Organic_nitrogen_operation *operation;
   void show_hide_controls();
   float32 est_org_drymatter;
   Tparameter_file_form       *parameter_file_form;
public:		// User declarations
   __fastcall Torganic_N_application_form(TComponent* Owner);
   void bind_to(CropSyst::Organic_nitrogen_operation *operation,   Tparameter_file_form       *_parameter_file_form);
};
//---------------------------------------------------------------------------
extern PACKAGE Torganic_N_application_form *organic_N_application_form;
//---------------------------------------------------------------------------
#endif
