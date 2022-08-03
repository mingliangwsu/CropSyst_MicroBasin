//______________________________________________________________________________
#include <vcl.h>
#include "CropSyst/source/management/management_param_V5.h"
#pragma hdrstop

#include "form_clipping.h"
//#include <cropsyst/cpp/cs_paths.h>
#include "CropSyst/GUI/help/management.h"
#include "GUI/parameter/form_param_file.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoRadioGroup"
#pragma link "RNAutoCheckBox"
#pragma link "RNAutoFloatEdit"
#pragma resource "*.dfm"

Tclipping_form *clipping_form;
//______________________________________________________________________________
__fastcall Tclipping_form::Tclipping_form(TComponent* Owner)
   : TForm(Owner)
   , after_first_show_hide_controls(false)
{}
//______________________________________________________________________________
void __fastcall Tclipping_form::bind_to
(CropSyst::Harvest_or_clipping_operation *i_clipping_op
,   Tparameter_file_form       *_parameter_file_form)
{
   clipping_op = i_clipping_op;
   parameter_file_form = _parameter_file_form;

   terminate_crop_checkbox    ->bind_to(&(clipping_op->terminate_crop)                 /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_tillage_residue_terminate)*/);
   min_LAI_required_edit      ->bind_to(&(clipping_op->p_min_LAI_required)             /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_min_LAI)*/);
   min_biomass_required_edit  ->bind_to(&(clipping_op->p_min_biomass_required_kg_ha)   /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_min_biomass_req)*/);
   reserve_biomass_editbar    ->bind_to(&(clipping_op->p_reserve_biomass_kg_ha)        /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_reserve_biomass)*/);

   grazing_OM_editbar         ->bind_to(&(clipping_op->p_grazing_percent_N_as_OM)      /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_grazing_organic_and_NO3)*/);
   grazing_NH3_editbar        ->bind_to(&(clipping_op->p_grazing_percent_N_as_NH3)     /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_grazing_organic_and_NO3)*/);

   bool auto_clip_mode = (clipping_op->get_type() == CS_OP_MGMT_AUTO_CLIP_BIOMASS);

   remove_fixed_amount_edit            ->bind_to(&(clipping_op->p_remove_amount_kg_ha)          /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_remove_fixed_amount)*/);
   accept_less_checkbox                ->bind_to(&(clipping_op->accept_less)                    /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_accept_less)*/);
   harvest_amount_mode_radiogroup      ->bind_to(&(clipping_op->harvest_amount_mode_cowl_or_labeled)    /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_removal_mode)*/);
   min_retain_GAI_edit                 ->bind_to(&(clipping_op->p_min_retain_GAI)               /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_min_retain_GAI)*/);
   biomass_returned_as_manure_editbar  ->bind_to(&(clipping_op->p_biomass_returned_as_manure)   /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_grazing_returned)*/);
   remove_for_use_edit                 ->bind_to(&(clipping_op->p_remove_for_use_percent)       /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_fate)*/);
   remove_for_grazing_edit             ->bind_to(&(clipping_op->p_remove_for_grazing_percent)   /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_grazing)*/);
   remain_as_residue_edit              ->bind_to(&(clipping_op->p_remain_as_residue_percent)    /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_fate)*/);
   remove_for_disposal_edit            ->bind_to(&(clipping_op->p_remove_for_disposal_percent)  /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_fate)*/);
   remain_as_standing_dead_edit        ->bind_to(&(clipping_op->p_remain_standing_dead_percent) /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_fate)*/);
   remain_as_standing_live_edit        ->bind_to(&(clipping_op->p_remain_standing_live_percent) /*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_fate)*/);

//040628 we don't yet offer user the ability to adjust root biomass fate
// currently these are set during the run depending on the operation
// NYI v_remain_roots_as_dead_residue_percent;
// NYI v_remove_roots_as_loss_percent;
// NYI v_remain_roots_live_percent;

   percent_total_out->bind_to(&percents_total/*,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_clip_fate)*/);
   show_hide_controls(0);

   // The retain GAI group box is set below the remove_fixed_amount_groupbox
   // in the IDE editor.  When they are displayed in the actual dialog
   // box they are positioned in the same spot and hidden accordingly
//060310    retain_GAI_groupbox->Top =remove_fixed_amount_groupbox->Top;
//060310    percentage_biomass_groupbox->Top =remove_fixed_amount_groupbox->Top;

   retain_GAI_mode_note  ->Top = remove_fixed_amount_groupbox->Top;
   remove_percentage_note->Top = remove_fixed_amount_groupbox->Top;
   GAI_groupbox->Left = remove_fixed_amount_groupbox->Left;

   NRCS_harvest_field_op_number_combbox->Text = clipping_op->NRCS_operation_description.c_str();
}
//______________________________________________________________________________
void __fastcall Tclipping_form::grazing_OM_editbar_onexit(TObject *Sender)
{  if (clipping_op)
   {  clipping_op->grazing_percent_N_as_NH3 = 100 - clipping_op->grazing_percent_N_as_OM;
      grazing_NH3_editbar->Update();
   }
}
//______________________________________________________________________________
void __fastcall Tclipping_form::grazing_NH3_editbar_onexit(TObject *Sender)
{  if (clipping_op)
   {  clipping_op->grazing_percent_N_as_OM = 100 - clipping_op->grazing_percent_N_as_NH3;
      grazing_OM_editbar->Update();
   }
}
//______________________________________________________________________________
void __fastcall Tclipping_form::terminate_crop_checkboxClick(TObject *Sender)
{
   show_hide_controls(Sender);
}
//______________________________________________________________________________
void __fastcall Tclipping_form::show_hide_controls(TObject *Sender)
{  if (clipping_op)
   {  harvest_mode_page_control->ActivePageIndex = (clipping_op->harvest_fate_mode_cowl_or_labeled.get());
      GAI_groupbox->Visible= false;
      remove_fixed_amount_groupbox->Visible  = false;
//060310 obsolete       retain_GAI_groupbox->Visible           = false;
//      percentage_biomass_groupbox->Visible   = false;
      remove_percentage_note ->Visible = false;
      retain_GAI_mode_note ->Visible = false;
      clipping_fate_label->Caption = "All of the clipped (actually removed from the plant)";
      last_clipping_fate_label->Caption = "All of the clipped (actually removed from the plant)";
      select_one_mode_memo->Visible = true;

      Harvest_fate_mode harvest_fate_mode = clipping_op->harvest_amount_mode_cowl_or_labeled.get(); //170701

      switch (harvest_fate_mode)
      {  case HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS  :
            remove_fixed_amount_groupbox->Visible =  true;
            GAI_groupbox->Visible= true;
            select_one_mode_memo->Visible = false;
            break;
         case HARVEST_RETAIN_GAI_obsolete                  :
//060310            retain_GAI_groupbox->Visible = true;
//060327obs            max_retain_GAI_edit_obsolete->Visible = false;
            GAI_groupbox->Visible= true;
            retain_GAI_mode_note ->Visible = true;
            break;
         case HARVEST_PERCENT_BIOMASS              :
//060310            percentage_biomass_groupbox->Visible = true;
//            remove_fixed_amount_groupbox->Visible = false; already set false above
//            GAI_groupbox->Visible= false;           already set false above
            remove_percentage_note ->Visible = true;
            clipping_fate_label->Caption = "All above ground";
            last_clipping_fate_label->Caption = "All above ground";
            break;
      } // both are hidden in all other cases (HARVEST_CROP_PARAMETER_BASED, OTHER_BIOMATTER_FATE)

      // remove_for_grazing_edit->Visible = !show_fixed_amount;
      // We do show fixed amount.
      terminate_crop_checkbox->Visible = true;
      terminate_crop_label->Visible    = true;

      // if not grazing, biomatter grazed = 0
      switch (harvest_fate_mode)
      {
         case HARVEST_ONCE             :
            // Not currently forcing terminate.
//            clipping_op->biomass_fate_percents.remove_for_grazing = 0;
         break;
         case HARVEST_CLIPPING         :
            clipping_op->terminate_crop      = false;
            terminate_crop_checkbox->Visible = false;
            terminate_crop_label->Visible    = false;
            terminate_crop_checkbox->Update();
//            clipping_op->biomass_fate_percents.remove_for_grazing = 0;
         break;
         case HARVEST_LAST_CLIPPING  :
            // does not necessarily terminate
//            clipping_op->biomass_fate_percents.remove_for_grazing = 0;
         break;
         case HARVEST_GRAZE            :
            clipping_op->terminate_crop      = false;
            terminate_crop_checkbox->Visible = false;
            terminate_crop_label->Visible    = false;
            terminate_crop_checkbox->Update();
//            clipping_op->biomass_fate_percents.remove_to_residue = 0;
//            clipping_op->biomass_fate_percents.remove_as_loss = 0;
         break;
         case DEFOLIATION              :
            // does not necessarily terminate
//            clipping_op->biomass_fate_percents.remove_for_use = 0;
//            clipping_op->biomass_fate_percents.remove_for_grazing = 0;
//            clipping_op->biomass_fate_percents.remove_to_residue = 10;
//            clipping_op->biomass_fate_percents.remove_as_loss = 0;
//            clipping_op->biomass_fate_percents.remove_to_standing_dead = 85;
//            clipping_op->biomass_fate_percents.remain_as_live = 5;
         break;
      }
      terminate_crop_checkbox->Update();
      
      if (clipping_op->terminate_crop)
      {  // make sure that percents remaining live are zero and hide live standing tissue.
            clipping_op->biomass_fate_percents.remain_as_dead += clipping_op->biomass_fate_percents.remain_as_live;
            clipping_op->biomass_fate_percents.remain_as_live = 0;
            remain_as_standing_live_edit->Enabled = false;
            remain_as_standing_live_edit->Update();
            remain_as_standing_dead_edit->Update();
      }
      if ((harvest_fate_mode == HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS)
        ||(harvest_fate_mode == HARVEST_RETAIN_GAI_obsolete)
        )
      {  // In both these modes the plant remains alive
         // The amount of material remain alive is determined based on removal rate.
         remain_as_standing_live_edit->Enabled = false;
         remain_as_standing_dead_edit->Enabled = false;
         remain_as_standing_live_edit->Visible = false;
         remain_as_standing_dead_edit->Visible = false;
         clipping_op->biomass_fate_percents.remain_as_live = 0;
         clipping_op->biomass_fate_percents.remain_as_dead = 0;
         remain_as_standing_live_edit->Update();
         remain_as_standing_dead_edit->Update();
      } else
      {  remain_as_standing_live_edit->Visible = true;
         remain_as_standing_dead_edit->Visible = true;
      }
      update_total_percent(0);

      biomatter_fate_groupbox->Caption
      =((harvest_fate_mode == HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS)
      ||(harvest_fate_mode == HARVEST_RETAIN_GAI_obsolete))
      ? "biomass removed is distributed in the following proportions (remove fixed amount or retain GAI mode)"
      : "biomass has the following disposition (considering the current amount of above ground biomass)";

      bool harvest_once_mode = (harvest_fate_mode == HARVEST_CROP_PARAMETER_BASED);
      if (harvest_once_mode)
         harvest_fate_mode = HARVEST_ONCE;                                       //170701
      else
         if (harvest_fate_mode == HARVEST_ONCE)
         {  // We need to have one of the other harvest fate modes selected
              harvest_fate_mode = HARVEST_CLIPPING;
         }
      clipping_op->harvest_fate_mode_cowl_or_labeled.set(harvest_fate_mode);             //170701
      primary_yield_tabsheet->TabVisible  =  harvest_once_mode;
      clipping_tabsheet     ->TabVisible  = !harvest_once_mode;
      last_clipping_tabsheet->TabVisible  = !harvest_once_mode;
      grazing_tabsheet      ->TabVisible  = !harvest_once_mode;
      defoliation_tabsheet  ->TabVisible  = !harvest_once_mode;
      if (harvest_once_mode)
         harvest_mode_page_control->ActivePage = primary_yield_tabsheet;
      //050824obs !show_fixed_amount;
      bool grazing_or_clipping_mode =
        (harvest_fate_mode == HARVEST_CLIPPING)
      ||(harvest_fate_mode == HARVEST_LAST_CLIPPING)
      ||(harvest_fate_mode == HARVEST_GRAZE);
      constraints_tabsheet->TabVisible = grazing_or_clipping_mode;
      after_first_show_hide_controls = true;
   }
}
//______________________________________________________________________________
void __fastcall Tclipping_form::harvest_mode_onchange(TObject *Sender)
{ if (clipping_op)
      clipping_op->harvest_fate_mode_cowl_or_labeled
         .set(harvest_mode_page_control->ActivePageIndex);
   show_hide_controls(Sender);
}
//______________________________________________________________________________
void __fastcall Tclipping_form::update_total_percent(TObject *Sender)
{  percents_total
      = clipping_op->biomass_fate_percents.remove_for_use
      + clipping_op->biomass_fate_percents.remove_for_grazing
      + clipping_op->biomass_fate_percents.remain_as_residue
      + clipping_op->biomass_fate_percents.remove_for_disposal
      + clipping_op->biomass_fate_percents.remain_as_dead
      + clipping_op->biomass_fate_percents.remain_as_live;
      percent_total_out->Update();
      percent_total_out->Color = (percents_total == 100) ? clLime : clRed;
      remain_as_standing_live_edit->Enabled = true;
      remain_as_standing_dead_edit->Enabled = true;
      if (clipping_op->terminate_crop)
         remain_as_standing_live_edit->Enabled = false;
   Harvest_fate_mode harvest_fate_mode = clipping_op->harvest_fate_mode_cowl_or_labeled.get(); //170701
      if ((harvest_fate_mode == HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS)
        ||(harvest_fate_mode == HARVEST_RETAIN_GAI_obsolete))
      {
         remain_as_standing_live_edit->Enabled = false;
         remain_as_standing_dead_edit->Enabled = false;
      }
}
//______________________________________________________________________________
void __fastcall Tclipping_form::update_percents(TObject *Sender)
{  remove_for_use_edit           ->Update();
   remove_for_grazing_edit       ->Update();
   remain_as_residue_edit        ->Update();
   remove_for_disposal_edit      ->Update();
   remain_as_standing_dead_edit  ->Update();
   remain_as_standing_live_edit  ->Update();
   terminate_crop_checkbox       ->Update();
   min_retain_GAI_edit           ->Update();
//090730obs   max_retain_GAI_edit_obsolete  ->Update();
   update_total_percent(Sender);
}
//______________________________________________________________________________
void __fastcall Tclipping_form::suggested_harvest_buttonClick(TObject *Sender)
{  clipping_op->terminate_crop = true;
   terminate_crop_checkbox->Update();
   clipping_op->biomass_fate_percents.remove_for_use = 0;
   clipping_op->biomass_fate_percents.remove_for_grazing = 0;
   clipping_op->biomass_fate_percents.remain_as_residue = 90;
   clipping_op->biomass_fate_percents.remove_for_disposal = 0;
   clipping_op->biomass_fate_percents.remain_as_dead = 10;
   clipping_op->biomass_fate_percents.remain_as_live = 0;
   update_percents(Sender);
}
//______________________________________________________________________________
void __fastcall Tclipping_form::suggest_clipping_buttonClick(TObject *Sender)
{  clipping_op->terminate_crop = false;
   terminate_crop_checkbox->Update();
   clipping_op->biomass_fate_percents.remove_for_grazing = 0;
   clipping_op->biomass_fate_percents.remain_as_residue = 0;
   clipping_op->biomass_fate_percents.remove_for_disposal = 0;
   clipping_op->biomass_fate_percents.remain_as_dead = 0;
   if (clipping_op->harvest_fate_mode_cowl_or_labeled.get() == HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS)
   {  clipping_op->biomass_fate_percents.remove_for_use = 100;
      clipping_op->biomass_fate_percents.remain_as_live = 0;
   }  else
   {  clipping_op->biomass_fate_percents.remove_for_use = 90;
      clipping_op->biomass_fate_percents.remain_as_live = 10;
   }
   update_percents(Sender);
}
//______________________________________________________________________________
void __fastcall Tclipping_form::suggest_last_clipping_buttonClick(TObject *Sender)
{
   clipping_op->terminate_crop = false;
   terminate_crop_checkbox->Update();
   clipping_op->biomass_fate_percents.remove_for_grazing = 0;
   clipping_op->biomass_fate_percents.remain_as_residue = 0;
   clipping_op->biomass_fate_percents.remove_for_disposal = 0;
   clipping_op->biomass_fate_percents.remain_as_dead = 0;
   if (clipping_op->harvest_fate_mode_cowl_or_labeled.get() == HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS)
   {  clipping_op->biomass_fate_percents.remove_for_use = 100;
      clipping_op->biomass_fate_percents.remain_as_live = 0;
   } else
   {  clipping_op->biomass_fate_percents.remove_for_use = 90;
      clipping_op->biomass_fate_percents.remain_as_live = 10;
   }
   update_percents(Sender);
}
//______________________________________________________________________________
void __fastcall Tclipping_form::suggest_grazing_buttonClick(TObject *Sender)
{
   clipping_op->terminate_crop = false;
   terminate_crop_checkbox->Update();
   clipping_op->biomass_fate_percents.remove_for_grazing = 0;
   clipping_op->biomass_fate_percents.remain_as_residue = 0;
   clipping_op->biomass_fate_percents.remove_for_disposal = 0;
   clipping_op->biomass_fate_percents.remain_as_dead = 0;
   if (clipping_op->harvest_fate_mode_cowl_or_labeled.get() == HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS)
   {  clipping_op->biomass_fate_percents.remove_for_use = 100;
      clipping_op->biomass_fate_percents.remain_as_live = 0;
   } else
   {  clipping_op->biomass_fate_percents.remove_for_use = 70;
      clipping_op->biomass_fate_percents.remain_as_live = 30;
   }
   update_percents(Sender);
}
//______________________________________________________________________________
void __fastcall Tclipping_form::suggest_defoliation_buttonClick(TObject *Sender)
{
   clipping_op->terminate_crop = false;
   terminate_crop_checkbox->Update();
   clipping_op->biomass_fate_percents.remove_for_grazing = 0;
   clipping_op->biomass_fate_percents.remain_as_residue = 0;
   clipping_op->biomass_fate_percents.remove_for_disposal = 0;
   clipping_op->biomass_fate_percents.remain_as_dead = 0;
   if (clipping_op->harvest_fate_mode_cowl_or_labeled.get() == HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS)
   {  clipping_op->biomass_fate_percents.remove_for_use = 100;
      clipping_op->biomass_fate_percents.remain_as_live = 0;
   } else
   {  clipping_op->biomass_fate_percents.remain_as_residue = 10;
      clipping_op->biomass_fate_percents.remain_as_dead = 85;
      clipping_op->biomass_fate_percents.remain_as_live = 5;
   }

   update_percents(Sender);
} //______________________________________________________________________________
void __fastcall Tclipping_form::harvest_amount_mode_radiogroup_onclick(TObject *Sender)
{  show_hide_controls(Sender);
//too annoying   if (after_first_show_hide_controls)
//      Application->MessageBox("When you change the biomass removal mode you need to make sure biomass fate sums to 100%","Verify biomass fate",MB_OK);

}
//______________________________________________________________________________

/*
Previous Harvest mode selection options
Single harvest event with primary yield  based harvest index, or harvestable biomatter such as fruits
Remove fixed about of biomass (suitable for clipping, grazing).
Hidden:   Remove biomass based on a percentage of current biomass (suitable for clipping)
Obsolete: Remove biomass retaining a minimal green leaf area index of living plants (suitable for clipping)
*/
void __fastcall Tclipping_form::goto_biomass_fate_button_onclick(TObject *Sender)
{
   harvest_clipping_pagecontrol->ActivePage = biomass_fate_tabsheet;
}
//______________________________________________________________________________
void __fastcall Tclipping_form::NRCS_harvest_field_op_number_combboxChange(TObject *Sender)
{  if (!clipping_op) return;
   CORN::UnicodeZ_to_string                                                      //170701
      (NRCS_harvest_field_op_number_combbox->Text.c_str()
      ,clipping_op->NRCS_operation_description);
}
//______________________________________________________________________________
void __fastcall Tclipping_form::button_NRCS_helpClick(TObject *Sender)
{  parameter_file_form->view_manual("NRCS_field_operation.htm");
}
//---------------------------------------------------------------------------

