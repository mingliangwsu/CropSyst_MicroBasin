//______________________________________________________________________________
#include <vcl.h>
//150402 #include "CropSyst/source/mgmt_param.h"
#include "CropSyst/source/management/management_param_V4.h"
#pragma hdrstop
#include "form_irrig_appl.h"
//130321 #include "CropSyst/source/cs_paths.h"
#include "CropSyst/GUI/help/management.h"
#include "GUI/parameter/form_param_file.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoFloat32EditBar"
#pragma link "AutoRadioGroup"
#pragma link "AutoCheckBox"
#pragma resource "*.dfm"
TIrrigation_application_form *Irrigation_application_form;
//______________________________________________________________________________
__fastcall TIrrigation_application_form::TIrrigation_application_form(TComponent* Owner)
   : TForm(Owner)
//NYI ,fixed_periodic(0)
{}
//______________________________________________________________________________
void __fastcall TIrrigation_application_form::bind_to
(CropSyst::
#ifdef OLD_MGMT_PARAM
Irrigation_operation
#else
Irrigation_operation_class
#endif
*_irrig_op

,bool                   _auto_irrig_mode
, Contingency_labeled  *_contigency_labeled
,Tparameter_file_form  *parameter_file_form)
{
   irrig_op = _irrig_op;
   contigency_labeled = _contigency_labeled;
   auto_irrig_mode = _auto_irrig_mode;
#define NO_HELP_YET 0
   { // auto irrig parameters now provided here as well
      application_mode_radiogroup      ->bind_to(&
         (irrig_op->application_mode_cowl) //150403 application_mode_cowl_or_labeled
//         #ifdef OLD_MGMT_PARAM
//         (irrig_op->application_mode_labeled)
//         #else
//         (irrig_op->application_mode_cowl)
//         #endif
          ,NO_HELP_YET); //cs_suite_paths->get_cropsyst_parameter_help(HELP_P_irrigation_xxx).c_str());
      max_allowable_depletion_editbar  ->bind_to
//150403         #ifdef OLD_MGMT_PARAM
//150403         (&(irrig_op->v_max_allowable_depletion)    V4_HELP_URL(HELP_P_mgmt_irrig_max_allow_depl));
//150403         #else
         (&(irrig_op->max_allowable_depletion),2 V4_HELP_URL(HELP_P_mgmt_irrig_max_allow_depl));
//150403         #endif
      radiobutton_depletion_observation_depth_mode->bind_to(&
         (irrig_op->depletion_observation_depth_mode_cowl) //depletion_observation_depth_mode_cowl_or_labeled
         ,NO_HELP_YET);
/*
      #ifdef OLD_MGMT_PARAM
      depletion_observe_depth_editbar     ->bind_to(&(irrig_op->v_depletion_observe_depth)            V4_HELP_URL(HELP_P_mgmt_irrig_obs_depth_depl));
      depletion_obs_fract_root_depth_edit ->bind_to(&(irrig_op->v_depletion_observe_root_zone_fract)  V4_HELP_URL(HELP_P_mgmt_irrig_obs_depth_depl));
      net_irrigation_mult_editbar         ->bind_to(&(irrig_op->v_net_irrigation_mult)                V4_HELP_URL(HELP_P_mgmt_irrig_net_multiplier));
      refill_point_edit_bar               ->bind_to(&(irrig_op->v_refill_point)                      ,NO_HELP_YET); // V4_HELP_URL(HELP_P_irrigation_xxx).c_str());
      max_application_editbar             ->bind_to(&(irrig_op->v_max_application)                    V4_HELP_URL(HELP_P_mgmt_irrig_max_appl));
      min_application_editbar             ->bind_to(&(irrig_op->v_min_application)                    V4_HELP_URL(HELP_P_mgmt_irrig_min_appl));
      #else
*/
      depletion_observe_depth_editbar     ->bind_to(&(irrig_op->depletion_observe_depth_m),2          V4_HELP_URL(HELP_P_mgmt_irrig_obs_depth_depl));
      depletion_obs_fract_root_depth_edit ->bind_to(&(irrig_op->depletion_observe_root_zone_fract),2  V4_HELP_URL(HELP_P_mgmt_irrig_obs_depth_depl));
      net_irrigation_mult_editbar         ->bind_to(&(irrig_op->net_irrigation_mult),2             V4_HELP_URL(HELP_P_mgmt_irrig_net_multiplier));
      refill_point_edit_bar               ->bind_to(&(irrig_op->refill_point)    ,2               ,NO_HELP_YET); // V4_HELP_URL(HELP_P_irrigation_xxx).c_str());
      max_application_editbar             ->bind_to(&(irrig_op->max_application_mm) ,2                V4_HELP_URL(HELP_P_mgmt_irrig_max_appl));
      min_application_editbar             ->bind_to(&(irrig_op->min_application_mm) ,2                V4_HELP_URL(HELP_P_mgmt_irrig_min_appl));
//150403      #endif
   };
/*150403
   #ifdef OLD_MGMT_PARAM
   amount_editbar    ->bind_to(&(irrig_op->v_amount)                        V4_HELP_URL(HELP_P_mgmt_irrig_specific));
   salinity_editbar  ->bind_to(&(irrig_op->v_salinity)                      V4_HELP_URL(HELP_P_mgmt_irrig_salinity));
   edit_NO3_N_conc   ->bind_to(&(irrig_op->v_NO3_N_concentration)           V4_HELP_URL(HELP_P_mgmt_irrig_salinity));
   edit_NH4_N_conc   ->bind_to(&(irrig_op->v_NH4_N_concentration)            V4_HELP_URL(HELP_P_mgmt_irrig_salinity));
   editbar_leaf_water_potential->bind_to(&(irrig_op->v_leaf_water_potential) V4_HELP_URL(HELP_P_mgmt_irrig_leaf_water_potential));
   edit_irrig_wetted_surface_evap->bind_to(&(irrig_op->v_surface_evaporation_area_fraction)  V4_HELP_URL("management\\irrigation.htm#wet_soil_surface_evap"));
   edit_irrig_wetted_soil_volume ->bind_to(&(irrig_op->v_profile_volume_fraction)             V4_HELP_URL("management\\irrigation.htm#wet_soil_profile_volume"));
   #else
*/
   amount_editbar    ->bind_to(&(irrig_op->amount_mm)                   ,2 V4_HELP_URL(HELP_P_mgmt_irrig_specific));
   salinity_editbar  ->bind_to(&(irrig_op->salinity)                    ,2 V4_HELP_URL(HELP_P_mgmt_irrig_salinity));
   edit_NO3_N_conc   ->bind_to(&(irrig_op->NO3_N_concentration)            ,2 V4_HELP_URL(HELP_P_mgmt_irrig_salinity));
   edit_NH4_N_conc   ->bind_to(&(irrig_op->NH4_N_concentration)            ,2 V4_HELP_URL(HELP_P_mgmt_irrig_salinity));
   editbar_leaf_water_potential->bind_to(&(irrig_op->leaf_water_potential) ,2 V4_HELP_URL(HELP_P_mgmt_irrig_leaf_water_potential));
   /* soil wetting for directed irrigation NYI
   edit_irrig_wetted_surface_evap->bind_to(&(irrig_op->surface_evaporation_area_fraction)  V4_HELP_URL("management\\irrigation.htm#wet_soil_surface_evap"));
   edit_irrig_wetted_soil_volume ->bind_to(&(irrig_op->profile_volume_fraction             V4_HELP_URL("management\\irrigation.htm#wet_soil_profile_volume"));
*/

//150403   #endif
   radiogroup_consideration    ->bind_to(&
      (irrig_op->consideration_mode_cowl) //consideration_mode_cowl_or_labeled
       V4_HELP_URL(HELP_P_mgmt_irrig_consideration_mode));
//NYI   fixed_periodic = &_fixed_periodic;


   show_hide_controls();
};
//______________________________________________________________________________
void __fastcall TIrrigation_application_form::application_mode_radiogroup_onclick(TObject *Sender)
{  show_hide_controls();
}
//______________________________________________________________________________
void  TIrrigation_application_form::show_hide_controls()
{  if (!irrig_op) return;
   tabsheet_application_conditions->TabVisible = auto_irrig_mode; // NYI  | fixed_periodic;
   bool consideration_leaf_water_potential_mode =
      (irrig_op->consideration_mode_cowl.get() == consider_leaf_water_potential);
   groupbox_depletion_constraints->Visible = !consideration_leaf_water_potential_mode;
   editbar_leaf_water_potential->Visible = consideration_leaf_water_potential_mode;
   if (consideration_leaf_water_potential_mode)
   {
   } else
   {  // Soil water depletion consideration mode
      bool soil_cond_mode =  (irrig_op->application_mode_cowl/*150403 application_mode_cowl_or_labeled*/
         .get() == irrigate_soil_condition);
      groupbox_depletion_constraints->Visible = soil_cond_mode || auto_irrig_mode;
      groupbox_depletion_constraints->Visible
         = auto_irrig_mode
            || (contigency_labeled && (contigency_labeled->get() == POSTPONE_CONTINGENCY));
      switch (radiobutton_depletion_observation_depth_mode->ItemIndex)
      {  case constant_fixed_depth_mode:
         {   depletion_observe_depth_editbar->Description_label = "Depletion observation depth";
            depletion_observe_depth_editbar->Visible = true;
            depletion_obs_fract_root_depth_edit->Visible = false;
         }break;
         case fraction_of_root_depth_mode :
         {   depletion_observe_depth_editbar->Description_label = "Depletion observation depth when no crop";
            depletion_observe_depth_editbar->Visible = true;
            depletion_obs_fract_root_depth_edit->Visible = true;
         }break;
         case soil_profile_depth_mode :
         {   depletion_observe_depth_editbar->Visible = false;
            depletion_obs_fract_root_depth_edit->Visible = false;
         }break;
      }; // switch depletion depth mode
   }; // end else soil water depletion consideraton model
   bool fixed_amount_mode =  irrig_op->
      application_mode_cowl//150403 application_mode_cowl_or_labeled
      .get() == irrigate_fixed_amount;
   panel_refill->Visible = !fixed_amount_mode;
   amount_editbar->Visible = fixed_amount_mode;
   panel_application_mode->Visible = true;
};
//______________________________________________________________________________
void __fastcall TIrrigation_application_form::radiobutton_depletion_observation_depth_modeClick(TObject *Sender)
{  radiobutton_depletion_observation_depth_mode->Update();
   show_hide_controls();
}
//______________________________________________________________________________
void __fastcall TIrrigation_application_form::radiobutton_depletion_observation_depth_modeExit(TObject *Sender)
{  show_hide_controls();
}
//______________________________________________________________________________
void __fastcall TIrrigation_application_form::radiogroup_considerationClick(TObject *Sender)
{  show_hide_controls();
}
//---------------------------------------------------------------------------


