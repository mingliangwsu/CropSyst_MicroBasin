//---------------------------------------------------------------------------

#ifndef form_tillage_residueH
#define form_tillage_residueH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RNAutoCheckBox.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoParameterEditBar.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
namespace CropSyst
{
class Tillage_operation;
}
class Tparameter_file_form;
//---------------------------------------------------------------------------
class Ttillage_residue_form : public TForm
{
__published:	// IDE-managed Components
   TRNAutoCheckBox *terminate_crop_checkbox;
   TRNAutoCheckBox *dust_mulching_checkbox;
   TGroupBox *dust_mulch_groupbox;
   TRNAutoParameterEditBar *dust_mulch_depth_edit;
   TRNAutoParameterEditBar *dust_mulch_days_edit;
   TRNAutoParameterEditBar *dust_mulch_intensity_edit;
   TPanel *panel_NRCS_field_op;
   TSpeedButton *button_NRCS_help;
   TComboBox *NRCS_tillage_field_op_number_combbox;
   TGroupBox *groupbox_oxidation_effect;
   TRNAutoParameterEditBar *edit_oxidation_effect_sand;
   TRNAutoParameterEditBar *edit_oxidation_effect_clay;
   TButton *button_tillage_oxidation_low;
   TButton *button_tillage_oxidation_high;
   void __fastcall FormKeyPress(TObject *Sender, char &Key);
   void __fastcall dust_mulching_checkboxClick(TObject *Sender);
   void __fastcall NRCS_tillage_field_op_number_combboxChange(TObject *Sender);
   void __fastcall button_NRCS_helpxClick(TObject *Sender);
   void __fastcall button_tillage_oxidation_lowClick(TObject *Sender);
   void __fastcall button_tillage_oxidation_highClick(TObject *Sender);
private:	// User declarations
   CropSyst::Tillage_operation *tillage_op;
   Tparameter_file_form        *parameter_file_form;

public:		// User declarations
   __fastcall Ttillage_residue_form(TComponent* Owner);
   void bind_to
      (CropSyst::Tillage_operation *tillage_op
      ,unsigned char                operation_kinds
      ,Tparameter_file_form        *parameter_file_form);
};
//---------------------------------------------------------------------------
extern PACKAGE Ttillage_residue_form *tillage_residue_form;
//---------------------------------------------------------------------------
#endif
