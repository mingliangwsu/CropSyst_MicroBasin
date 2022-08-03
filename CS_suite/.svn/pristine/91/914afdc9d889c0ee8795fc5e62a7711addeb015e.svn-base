//______________________________________________________________________________
#include <vcl.h>
#pragma hdrstop
//150402 #include "CropSyst/source/mgmt_param.h"
#include "CropSyst/source/management/management_param_V4.h"
#include "CropSyst/GUI/help/management.h"
#include "GUI/parameter/form_param_file.h"
#include "form_tillage_residue.h"
#include "CropSyst/source/cs_till.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoCheckBox"
#pragma link "AutoFloat32EditBar"
#pragma link "AutoInt16EditBar"
#pragma resource "*.dfm"
Ttillage_residue_form *tillage_residue_form;
//______________________________________________________________________________
__fastcall Ttillage_residue_form::Ttillage_residue_form(TComponent* Owner)
   : TForm(Owner)
{}
//______________________________________________________________________________
void Ttillage_residue_form::bind_to
(CropSyst::Tillage_operation    *_tillage_op
,unsigned char          operation_kinds
,Tparameter_file_form *_parameter_file_form)
{  tillage_op = _tillage_op;
   parameter_file_form =_parameter_file_form;
   terminate_crop_checkbox->bind_to(&(tillage_op->terminate_crop)
      V4_HELP_URL(HELP_P_mgmt_tillage_residue_terminate));
//unused    string description_buf;
   char full_description[255]; // may need to be out of the stack
   char selected_full_description[255];
   selected_full_description[0] = 0;
   NRCS_tillage_field_op_number_combbox->Text = tillage_op->NRCS_operation_description.c_str();

   dust_mulching_checkbox  ->bind_to(&(tillage_op->dust_mulch_enable)            V4_HELP_URL(HELP_P_mgmt_tillage_dust_mulch_enable));
   dust_mulch_depth_edit   ->bind_to(&(tillage_op->v_dust_mulch_depth_cm)        V4_HELP_URL(HELP_P_mgmt_tillage_dust_mulch_depth));;
   dust_mulch_days_edit    ->bind_to(&(tillage_op->v_dust_mulch_effective_days)  V4_HELP_URL(HELP_P_mgmt_tillage_dust_mulch_days));;
   dust_mulch_intensity_edit->bind_to(&(tillage_op->v_dust_mulch_intensity)      V4_HELP_URL(HELP_P_mgmt_tillage_dust_mulch_intensity));;

   bool residue_mode = operation_kinds == RESIDUE;
   dust_mulching_checkbox->Visible = !residue_mode;
   dust_mulch_groupbox->Visible = !residue_mode && tillage_op->dust_mulch_enable;
   edit_oxidation_effect_sand->bind_to(&(tillage_op->v_oxidation_effect_sand),0  /*NO_HELP_YET V4_HELP_URL(xxx)*/);
   edit_oxidation_effect_clay->bind_to(&(tillage_op->v_oxidation_effect_clay),0  /*NO_HELP_YET V4_HELP_URL(xxx)*/);
}
//______________________________________________________________________________//______________________________________________________________________________
void __fastcall Ttillage_residue_form::FormKeyPress(TObject *Sender,char &Key)
{  if (Key == VK_RETURN)
   {  Key = 0;
      Perform(WM_NEXTDLGCTL,0,0);
   }
}
//______________________________________________________________________________
void __fastcall Ttillage_residue_form::dust_mulching_checkboxClick(TObject *Sender)
{  if (!tillage_op) return;
   dust_mulch_groupbox->Visible = tillage_op->dust_mulch_enable;
}
//______________________________________________________________________________
void __fastcall Ttillage_residue_form::NRCS_tillage_field_op_number_combboxChange(TObject *Sender)
{  if (!tillage_op) return;
//   tillage_op->NRCS_SDR_operation_number  = NRCS_field_op_number_combbox->ItemIndex;
   tillage_op->NRCS_operation_description.assign(NRCS_tillage_field_op_number_combbox->Text.c_str());
}
//______________________________________________________________________________
void __fastcall Ttillage_residue_form::button_NRCS_helpxClick(TObject *Sender)
{  parameter_file_form->view_manual("NRCS_field_operation.htm");
}
//______________________________________________________________________________
void __fastcall Ttillage_residue_form::button_tillage_oxidation_lowClick(TObject *Sender)
{  tillage_op->oxidation_effect.sand = 1.5; edit_oxidation_effect_sand->Update(); // This is needs to be renamed normalClick
   tillage_op->oxidation_effect.clay = 0.5; edit_oxidation_effect_clay->Update();
}
//---------------------------------------------------------------------------
void __fastcall Ttillage_residue_form::button_tillage_oxidation_highClick(TObject *Sender)
{  tillage_op->oxidation_effect.sand = 6.0; edit_oxidation_effect_sand->Update();
   tillage_op->oxidation_effect.clay = 2.0; edit_oxidation_effect_clay->Update();
}
//---------------------------------------------------------------------------

