//---------------------------------------------------------------------------

#ifndef form_tillage_residueH
#define form_tillage_residueH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoCheckBox.h"
#include "AutoFloat32EditBar.h"
#include "AutoInt16EditBar.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
namespace CropSyst                                                               //120429
{                                                                                //120429
class Tillage_operation;
};                                                                               //120429
class Tparameter_file_form;
//---------------------------------------------------------------------------
class Ttillage_residue_form : public TForm
{
__published:	// IDE-managed Components
   TAutoCheckBox *terminate_crop_checkbox;
   TAutoCheckBox *dust_mulching_checkbox;
   TGroupBox *dust_mulch_groupbox;
   TAutoFloat32EditBar *dust_mulch_depth_edit;
   TAutoInt16EditBar *dust_mulch_days_edit;
   TAutoFloat32EditBar *dust_mulch_intensity_edit;
   TPanel *panel_NRCS_field_op;
   TSpeedButton *button_NRCS_help;
   TComboBox *NRCS_tillage_field_op_number_combbox;
   TGroupBox *groupbox_oxidation_effect;
   TAutoFloat32EditBar *edit_oxidation_effect_sand;
   TAutoFloat32EditBar *edit_oxidation_effect_clay;
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
   Tparameter_file_form       *parameter_file_form;

public:		// User declarations
   __fastcall Ttillage_residue_form(TComponent* Owner);
   void bind_to(CropSyst::Tillage_operation *i_tillage_op, unsigned char operation_kinds,   Tparameter_file_form       *_parameter_file_form);
};
//---------------------------------------------------------------------------
extern PACKAGE Ttillage_residue_form *tillage_residue_form;
//---------------------------------------------------------------------------
#endif
