//______________________________________________________________________________
#include <vcl.h>
#include "CropSyst/source/management/management_param_V5.h"
#pragma hdrstop
#include "CropSyst/GUI/help/management.h"
#include "GUI/parameter/form_param_file.h"
#include "form_auto_clipping.h"
#include "form_clipping2.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "RNAutoRadioGroup"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoCheckBox"
#pragma resource "*.dfm"
Tauto_clipping_form *auto_clipping_form;
//______________________________________________________________________________
__fastcall Tauto_clipping_form::Tauto_clipping_form(TComponent* Owner)
   : TForm(Owner)
{}
//______________________________________________________________________________
void __fastcall Tauto_clipping_form::bind_to(CropSyst::Auto_clip_biomass_mode *i_auto_clipping_mode,   Tparameter_file_form       *_parameter_file_form)
{
   parameter_file_form = _parameter_file_form;
   auto_clipping_mode = i_auto_clipping_mode;
   auto_clipping_mode->update_considerations();

   Tclipping_form *common_clipping_form = new Tclipping_form(this);
   common_clipping_form->bind_to(i_auto_clipping_mode,parameter_file_form);
   common_clipping_form->Parent = operation_tabsheet;
   common_clipping_form->Show();
   common_clipping_form->Top = 0;
   common_clipping_form->Left = 0;
   common_clipping_form->BorderStyle = bsNone;

   adjust_rate_clip_edit      ->bind_to(&(auto_clipping_mode->p_adjust_relative_growth_rate_for_clipping)/*,parameter_file_form->compose_manual_subdirectory_filename_cstr (HELP_P_mgmt_clip_rel_growth_rate_adj)*/);
   LAI_forces_clip_edit       ->bind_to(&(auto_clipping_mode->p_LAI_forces_clipping)                     /*,parameter_file_form->compose_manual_subdirectory_filename_cstr (HELP_P_mgmt_clip_max_LAI_forces)*/);
   biomass_forces_clip_edit   ->bind_to(&(auto_clipping_mode->p_biomass_forces_clipping)                 /*,parameter_file_form->compose_manual_subdirectory_filename_cstr (HELP_P_mgmt_clip_max_biomass_forces)*/);
   flowering_forces_clip_edit   ->bind_to(&(auto_clipping_mode->p_flowering_forces_clipping)             /*,parameter_file_form->compose_manual_subdirectory_filename_cstr (HELP_P_mgmt_clip_flowering_forces)*/);

   adjust_rate_clip_checkbox     ->bind_to(&(auto_clipping_mode->consider_adjust_rate) /*,parameter_file_form->compose_manual_subdirectory_filename_cstr (HELP_P_mgmt_clip_rel_growth_rate_adj)*/);
   LAI_forces_clip_checkbox      ->bind_to(&(auto_clipping_mode->consider_LAI)         /*,parameter_file_form->compose_manual_subdirectory_filename_cstr (HELP_P_mgmt_clip_max_LAI_forces)*/);
   biomass_forces_clip_checkbox  ->bind_to(&(auto_clipping_mode->consider_biomass)     /*,parameter_file_form->compose_manual_subdirectory_filename_cstr (HELP_P_mgmt_clip_max_biomass_forces)*/);
   flowering_forces_clip_checkbox->bind_to(&(auto_clipping_mode->consider_flowering)   /*,parameter_file_form->compose_manual_subdirectory_filename_cstr (HELP_P_mgmt_clip_flowering_forces)*/);
   show_hide_controls(0);
};
//______________________________________________________________________________
void __fastcall Tauto_clipping_form::show_hide_controls(TObject *Sender)
{  auto_clipping_mode->set_considerations();
   adjust_rate_clip_edit->Visible      = auto_clipping_mode->consider_adjust_rate;
   LAI_forces_clip_edit->Visible       = auto_clipping_mode->consider_LAI;
   biomass_forces_clip_edit->Visible   = auto_clipping_mode->consider_biomass;
   flowering_forces_clip_edit->Visible = auto_clipping_mode->consider_flowering;
   Update();
} ;
//______________________________________________________________________________
void __fastcall Tauto_clipping_form::Update(void)
{
   adjust_rate_clip_edit      ->Update();
   LAI_forces_clip_edit       ->Update();
   biomass_forces_clip_edit   ->Update();
   flowering_forces_clip_edit ->Update();
};
//______________________________________________________________________________

