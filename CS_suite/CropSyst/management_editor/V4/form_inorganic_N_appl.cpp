//______________________________________________________________________________
#include <vcl.h>
#include "management_param_V4.h"
#include "CropSyst/source/mgmt_param.h"
#pragma hdrstop
//130321 #include "CropSyst/source/cs_paths.h"
#include "CropSyst/GUI/help/management.h"
#include "GUI/parameter/form_param_file.h"
#include "form_inorganic_N_appl.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoCheckBox"
#pragma link "AutoFloat32EditBar"
#pragma link "AutoRadioGroup"
#pragma resource "*.dfm"
Tinorganic_N_application_form *inorganic_N_application_form;
//______________________________________________________________________________
__fastcall Tinorganic_N_application_form::Tinorganic_N_application_form(TComponent* Owner)
   : TForm(Owner)
   ,operation(0)
{}
//______________________________________________________________________________
void Tinorganic_N_application_form::bind_to
(CropSyst::Inorganic_nitrogen_operation_class *_operation
,Tparameter_file_form       *_parameter_file_form)
{  operation = _operation;
   parameter_file_form = _parameter_file_form;
   nitrate_edit               ->bind_to(&(operation->NO3_N),2                  ,0 /*NYI cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   ammonium_edit              ->bind_to(&(operation->NH4_N),2                  ,0 /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NH4_volatil_loss_edit      ->bind_to(&(operation->NH4_volatilization),2          ,0 /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NH4_volatil_loss_check     ->bind_to(&(operation->NH4_volatilization_calculated) ,0 /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NH4_source_radiogroup      ->bind_to(&(operation->NH4_source_cowl )            ,0 /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NH4_appl_method_radiogroup ->bind_to(&(operation->NH4_appl_method_cowl )       ,0 /*cs_suite_paths->get_cropsyst_parameter_help(HELP_P_xxxx)*/);
   NRCS_inorganic_field_op_number_combbox->Text = operation->NRCS_operation_description.c_str();
   show_hide_controls();
   NH4_volatil_loss_check->Update();
};
//______________________________________________________________________________
void __fastcall Tinorganic_N_application_form::NH4_volatil_loss_checkClick
(TObject *Sender)
{  show_hide_controls();
}
//______________________________________________________________________________
void Tinorganic_N_application_form::show_hide_controls()
{  if (operation)
   {  NH4_volatil_loss_edit->Enabled =!operation->NH4_volatilization_calculated;
      NH4_source_radiogroup->Visible = operation->NH4_volatilization_calculated;
      NH4_appl_method_radiogroup->Visible = operation->NH4_volatilization_calculated;
  };
};
//______________________________________________________________________________
void __fastcall Tinorganic_N_application_form::NRCS_inorganic_field_op_number_combboxChange(TObject *Sender)
{  if (!operation) return;
   operation->NRCS_operation_description.assign(NRCS_inorganic_field_op_number_combbox->Text.c_str());
}
//______________________________________________________________________________
void __fastcall Tinorganic_N_application_form::button_NRCS_helpClick(TObject *Sender)
{  parameter_file_form->view_manual("NRCS_field_operation.htm");
}
//______________________________________________________________________________

