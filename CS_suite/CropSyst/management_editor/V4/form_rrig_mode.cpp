//---------------------------------------------------------------------------

#include <vcl.h>
#include <cropsyst/cpp/mgmt_param.h>
#pragma hdrstop
#include <CropSyst/cpp/cs_paths.h>
#include <CropSyst/GUI/help/management.h>

#include "irrig_mode_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoFloat32EditBar"
#pragma resource "*.dfm"
TAuto_irrigation_mode_form_obsolete *Auto_irrigation_mode_form_obsolete;
//---------------------------------------------------------------------------
__fastcall TAuto_irrigation_mode_form_obsolete::TAuto_irrigation_mode_form_obsolete(TComponent* Owner)
: TForm(Owner)
{}
//---------------------------------------------------------------------------
void __fastcall TAuto_irrigation_mode_form_obsolete::bind_to(Automatic_irrigation_mode *i_auto_irrig_mode)
{
   auto_irrig_mode = i_auto_irrig_mode;
   max_allowable_depletion_editbar  ->bind_to(&(auto_irrig_mode->v_max_allowable_depletion),cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_mgmt_irrig_max_allow_depl));
   depletion_observe_depth_editbar  ->bind_to(&(auto_irrig_mode->v_depletion_observe_depth),cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_mgmt_irrig_obs_depth_depl));
   net_irrigation_mult_editbar      ->bind_to(&(auto_irrig_mode->v_net_irrigation_mult)    ,cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_mgmt_irrig_net_multiplier));
   max_application_editbar          ->bind_to(&(auto_irrig_mode->v_max_application)        ,cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_mgmt_irrig_max_appl));
   salinity_editbar                 ->bind_to(&(auto_irrig_mode->v_salinity)               ,cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_mgmt_irrig_salinity));
};

