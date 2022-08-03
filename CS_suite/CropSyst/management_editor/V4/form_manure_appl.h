//---------------------------------------------------------------------------

#ifndef form_manure_applH
#define form_manure_applH
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
#include "AutoFileEditBar.h"
//---------------------------------------------------------------------------
#include <common/biomatter/biomass_decomposition_param.h>
namespace CropSyst
{
   class Biomatter_application_operation;
}
class Tparameter_file_form;
//---------------------------------------------------------------------------
class Tmanure_application_form : public TForm
{
__published:	// IDE-managed Components
   TPanel *panel_NRCS_field_op;
   TComboBox *NRCS_org_N_field_op_number_combbox;
   TSpeedButton *button_NRCS_help;
   TScrollBox *ScrollBox1;
   TAutoFileEditBar *fileeditbar_biomatter; 
   TPanel *Panel1;
   TGroupBox *groupbox_consistency;
   TAutoFloat32EditBar *edit_dry_matter;
   TListBox *listbox_form;
   TAutoRadioGroup *org_appl_method_radiogroup;
   TPanel *panel_mass;
   TLabel *Label3;
   TLabel *org_drymatter_label;
   TLabel *Label4;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *label_estimated;
   TAutoFloat32EditBar *org_N_amount_edit;
   TAutoFloat32Edit *edit_est_org_drymatter;
   TAutoFloat32Edit *edit_est_org_wetmatter;
   TAutoFloat32EditBar *NH3_ammonia_edit;
   TAutoFloat32EditBar *NH3_volatil_loss_edit;
   TLabel *including_mineralized_org_n_label;


   void __fastcall NRCS_org_N_field_op_number_combboxChange(
          TObject *Sender);
   void __fastcall org_N_amount_editExit(TObject *Sender);

   void __fastcall button_NRCS_helpClick(TObject *Sender);
   void __fastcall load_manure_description(TObject *Sender);
   void __fastcall edit_dry_matterExit(TObject *Sender);
   void __fastcall listbox_formClick(TObject *Sender);
   void __fastcall edit_est_org_wetmatterExit(TObject *Sender);
   void __fastcall org_appl_method_radiogroupClick(TObject *Sender);
   void __fastcall edit_est_org_drymatterExit(TObject *Sender);
private:	// User declarations
   CropSyst::Biomatter_application_operation *operation;
   void show_hide_controls();
   Biomass_decomposition_parameters decomposition_parameters;
   float32 est_org_drymatter;
   float32 est_org_wetmatter;
   Tparameter_file_form       *parameter_file_form;
public:		// User declarations
   __fastcall Tmanure_application_form(TComponent* Owner);
   void bind_to(CropSyst::Biomatter_application_operation *operation,   Tparameter_file_form       *_parameter_file_form);
private:
   void __fastcall recalculate_dry_biomass_from_Nmass();
   void __fastcall recalculate_wet_biomass_from_drybiomass();
   void __fastcall recalculate_Nmass_from_dry_biomass();
   void __fastcall recalculate_volatilization();
};
//---------------------------------------------------------------------------
extern PACKAGE Tmanure_application_form *manure_application_form;
//---------------------------------------------------------------------------
#endif
