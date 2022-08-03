//______________________________________________________________________________
#include <vcl.h>
#include "CropSyst/source/management/management_param_V5.h"
#pragma hdrstop
#include "CropSyst/GUI/help/management.h"
#include "GUI/parameter/form_param_file.h"
#include "form_inorganic_N_appl.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "RNAutoCheckBox"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoRadioGroup"
#pragma resource "*.dfm"
Tinorganic_N_application_form *inorganic_N_application_form;
//______________________________________________________________________________
__fastcall Tinorganic_N_application_form::Tinorganic_N_application_form(TComponent* Owner)
   : TForm(Owner)
   ,operation(0)
{}
//______________________________________________________________________________
void Tinorganic_N_application_form::bind_to(CropSyst::Inorganic_nitrogen_operation *operation_,   Tparameter_file_form       *_parameter_file_form)
{  operation = operation_;
   parameter_file_form = _parameter_file_form;
   nitrate_edit               ->bind_to(&(operation->p_NO3_N)                  /*NYI cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   ammonium_edit              ->bind_to(&(operation->p_NH4_N)                  /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NH4_volatil_loss_edit      ->bind_to(&(operation->p_NH4_volatilization)          /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NH4_volatil_loss_check     ->bind_to(&(operation->NH4_volatilization_calculated) /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NH4_source_radiogroup      ->bind_to(&(operation->NH4_source_cowl_or_labeled)            /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NH4_appl_method_radiogroup ->bind_to(&(operation->NH4_appl_method_cowl_or_labeled)       /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NRCS_inorganic_field_op_number_combbox->Text = operation->NRCS_operation_description.c_str();
   edit_N_soil_critical       ->bind_to(&(operation->p_N_soil_critical));        //170705
   edit_sampling_depth        ->bind_to(&(operation->p_sampling_depth));         //170705
   show_hide_controls();
   NH4_volatil_loss_check->Update();
}
//______________________________________________________________________________
void __fastcall Tinorganic_N_application_form::NH4_volatil_loss_checkClick
(TObject *Sender)
{  show_hide_controls();
}
//______________________________________________________________________________
void Tinorganic_N_application_form::show_hide_controls()
{
   if (operation)
   {
      NH4_volatil_loss_edit->Enabled =!operation->NH4_volatilization_calculated;
      NH4_source_radiogroup->Visible = operation->NH4_volatilization_calculated;
      NH4_appl_method_radiogroup->Visible = operation->NH4_volatilization_calculated;
  }
}
//______________________________________________________________________________
void __fastcall Tinorganic_N_application_form::NRCS_inorganic_field_op_number_combboxChange(TObject *Sender)
{
   if (!operation) return;
   CORN::UnicodeZ_to_string
   (NRCS_inorganic_field_op_number_combbox->Text.c_str()
   ,operation->NRCS_operation_description
   );
   //170701 operation->NRCS_operation_description.assign(NRCS_inorganic_field_op_number_combbox->Text.c_str());
}
//______________________________________________________________________________
void __fastcall Tinorganic_N_application_form::button_NRCS_helpClick(TObject *Sender)
{
   parameter_file_form->view_manual("NRCS_field_operation.htm");
}
//______________________________________________________________________________

