//---------------------------------------------------------------------------

#include <vcl.h>
#include <cropsyst/cpp/mgmt_param.h>

#pragma hdrstop
#include <cropsyst/cpp/cs_paths.h>
#include <CropSyst/GUI/help/management.h>

#include "auto_N_mode_frm.h"
#include "auto_NO3_appl_frm.h"
#include <cropsyst/gui/builder/operation_event/operation_event_frm.h>
//#include "mgmt_param.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoContainerListBox"
#pragma link "AutoFloat32EditBar"
#pragma link "AutoInt16EditBar"
#pragma link "AutoRadioGroup"
#pragma resource "*.dfm"
Tauto_N_appl_mode_form *auto_N_appl_mode_form;
//---------------------------------------------------------------------------
__fastcall Tauto_N_appl_mode_form::Tauto_N_appl_mode_form(TComponent* Owner)
   : TForm(Owner)
//040712 currently we only have a sing set of split applications in the management:
//040712 ,auto_NO3_distribute_total(100)
//040712 ,v_auto_NO3_distribute_total(new Valid_int16(auto_NO3_distribute_total,NO_KEY,100,100,100,100,100,"percent","Applications should sum to 100%"))

{
}
//---------------------------------------------------------------------------

__fastcall Tauto_N_appl_mode_form::~Tauto_N_appl_mode_form()
{
//040712 currently we only have a sing set of split applications in the management
//   if (v_auto_NO3_distribute_total) delete v_auto_NO3_distribute_total; v_auto_NO3_distribute_total = 0;
};
//---------------------------------------------------------------------------
void Tauto_N_appl_mode_form::bind_to(Automatic_NO3_application_mode *i_auto_N_app_mode_op,bool i_crop_management)
{
   auto_N_app_mode_op = i_auto_N_app_mode_op;
   crop_management = i_crop_management;
      // Automatic NO3



   auto_NO3_radio_group                ->bind_to(&(auto_N_app_mode_op->automatic_NO3_mode_labeled)                ,cs_suite_paths->get_cropsyst_parameter_help(HELP_P_mgmt_N_automatic).c_str());
   target_yield_N_uptake_kg_ha_editbar ->bind_to(&(auto_N_app_mode_op->v_target_yield_N_uptake_kg_ha)             ,cs_suite_paths->get_cropsyst_parameter_help(HELP_P_mgmt_N_uptake_target_yield).c_str());
   critical_soil_NO3_editbar           ->bind_to(&(auto_N_app_mode_op->v_critical_soil_NO3_for_no_response_kg_ha) ,cs_suite_paths->get_cropsyst_parameter_help(HELP_P_mgmt_N_critical_NO3).c_str());
   sampling_depth_bar                  ->bind_to(&(auto_N_app_mode_op->v_soil_N_sampling_depth)                   ,cs_suite_paths->get_cropsyst_parameter_help(HELP_P_mgmt_N_sampling_depth).c_str());
   fert_use_eff_bar                    ->bind_to(&(auto_N_app_mode_op->v_fertilizer_use_efficiency)               ,cs_suite_paths->get_cropsyst_parameter_help(HELP_P_mgmt_N_fert_use_eff).c_str());
/*040712
currently we only have a sing set of split applications in the management
   auto_NO3_split_bar->Visible = auto_N_app_mode_op->auto_NO3_applications.count();
   auto_NO3_split_bar->bind_to(v_auto_NO3_distribute_total        ,NO_HELP_YET);

   auto_NO3_appl_listbox->bind_to(&(auto_N_app_mode_op->auto_NO3_applications),NO_HELP_YET);
*/
//021001 obsolete   update_sampling_date_button();
   show_hide_auto_NO3_parameters();
//040712NYI
//040712   update_auto_NO3_application_controls();


};
//---------------------------------------------------------------------------


void Tauto_N_appl_mode_form::show_hide_auto_NO3_parameters()
{
   if (auto_N_app_mode_op)
   {
      bool show_AUTO_NO3 = auto_N_app_mode_op->automatic_NO3_mode_labeled.get() == AUTO_NITRO_BALANCE_BASED
                        || auto_N_app_mode_op->automatic_NO3_mode_labeled.get() == AUTO_NITRO_LOCAL_CALIBRATION;

      auto_NO3_panel->Visible = show_AUTO_NO3;
      target_yield_N_uptake_kg_ha_editbar->Visible = auto_N_app_mode_op->automatic_NO3_mode_labeled.get() == AUTO_NITRO_BALANCE_BASED;
      critical_soil_NO3_editbar->Visible = auto_N_app_mode_op->automatic_NO3_mode_labeled.get() == AUTO_NITRO_LOCAL_CALIBRATION;

/*021001  NYI,   but all I need to do is pass the event to bind_to, this will be easy
      {  // Make sure to highlight the fact that soil N sampling date must be
         // prior to sowing if any  application dates.


         bool sampling_date_before_planting = true;

actually it looks like we now allow sampling at any time.

         bool sampling_date_before_planting
         = management->automatic_NO3_application_mode_event->is_before_planting();

         TColor sampling_prior_sowing_note_color
         = (auto_N_app_mode_op->auto_NO3_applications.count() && ! sampling_date_before_planting)
         ? clRed
         : clWindowText;
         sampling_prior_sowing_note->Font->Color = sampling_prior_sowing_note_color;

      };
      {  // Make sure to highlight the fact that soil N sampling date must be
         // prior to application dates.
         TColor sampling_prior_appls_note_color
         = auto_N_app_mode_op->auto_NO3_applications.count()
         ? clRed
         : clWindowText;
         sampling_prior_appls_note->Font->Color = sampling_prior_appls_note_color;
      };
      {  // Make sure to highlight the fact that all NO3 will be applied
         // at planting of no application dates.
         TColor NO3_appl_at_planting_note_color
         = auto_N_app_mode_op->auto_NO3_applications.count()
         ? clRed
         : clWindowText;
         NO3_appl_at_planting_note->Font->Color = NO3_appl_at_planting_note_color;
      };
*/

   };
};

//---------------------------------------------------------------------------

#ifdef NYI
040712 currently only allowing a single set of splits in management
void __fastcall Tauto_N_appl_mode_form::update_auto_NO3_application_controls()
{
      auto_NO3_distribute_total = 0.0;
      bool split_appls = auto_N_app_mode_op->auto_NO3_applications.count();
      auto_NO3_split_bar->Visible = split_appls;

      if (split_appls)
      {
         auto_NO3_distribute_total = auto_N_app_mode_op->total_automatic_NO3_applications();
         auto_NO3_split_bar->Update();
         sampling_prior_sowing_note->Font->Color = clGray;
         sampling_prior_appls_note->Font->Color = clRed;
         NO3_appl_at_planting_note->Font->Color=clGray;
         auto_NO3_appl_listbox->Update();
      }
      else
      {
         auto_NO3_distribute_total = 100;
         sampling_prior_sowing_note->Font->Color = clRed;
         sampling_prior_appls_note->Font->Color = clGray;
         NO3_appl_at_planting_note->Font->Color=clRed;
      };
}

void __fastcall Tauto_N_appl_mode_form::auto_NO3_application_button_onclick(TObject *Sender)
{
//NYI   schedule_treeview->focus_level_node("Fertilization","Nitrate automatic");
   if (auto_N_app_mode_op)
   {
      Automatic_NO3_application_mode::Split_application /*Automatic_NO3_application*/ *auto_NO3_appl_op
      = new Automatic_NO3_application_mode::Split_application /*Automatic_NO3_application*/;
      TAuto_NO3_application_form *auto_NO3_appl_form = new TAuto_NO3_application_form(this);
      auto_NO3_appl_form->bind_to(auto_NO3_appl_op);
//      prompt_and_append_event(auto_NO3_appl_op,auto_NO3_appl_form,auto_N_app_mode_op->auto_NO3_applications);

{ // prompt and append event
   TModalResult result = mrCancel;
   Common_event *event = new Common_event(auto_NO3_appl_op,true);

   Toperation_event_form *op_event_form = new Toperation_event_form(this);
   op_event_form->bind_to(event,auto_NO3_appl_form,crop_management,false);

   result = op_event_form->ShowModal();
   if (result == mrOk)
   {
      auto_N_app_mode_op->auto_NO3_applications.append(event);
//NYI      TTreeNode *curr_level_node = schedule_treeview->get_current_level_node();
//NYI      if (curr_level_node) // We should always have a current node.
//NYI      {  CORN_string event_label_CORN;
//NYI         event->label(event_label_CORN);
//NYI         AnsiString event_label(event_label_CORN.c_str());
//NYI         schedule_treeview->set_current_item_node(schedule_treeview->Items->AddChildObject(curr_level_node,event_label,event));
//         current_event_node->ImageIndex = curr_level_node->ImageIndex;
//NYI      };
   }
   else
   {
      delete event;  event = 0;
      delete auto_NO3_appl_op;     auto_NO3_appl_op = 0;
//      current_event_node = 0;
   }
   delete auto_NO3_appl_form;
}


      update_auto_NO3_application_controls();
   };
}
void __fastcall Tauto_N_appl_mode_form::auto_NO3_appl_delete_button_onclick(
      TObject *Sender)
{
   auto_NO3_appl_listbox->delete_selected();
   update_auto_NO3_application_controls();

}
//---------------------------------------------------------------------------

#endif

//---------------------------------------------------------------------------


/* Obsolete the mode event date in version 4 corresponds to the sampling date
//-----------------------------------

void __fastcall TManagement_editor_form::update_sampling_date_button()
{
   if (management)
   {
      CORN_string sampling_date_str;
      management->automatic_NO3_application_mode_event->text_string(sampling_date_str);
      sampling_date_button->Caption = sampling_date_str.c_str();
   };
};
void __fastcall TManagement_editor_form::sampling_date_button_onclick(TObject *Sender)
{
   Tsync_form  *sync_form = new Tsync_form(this);
   sync_form->bind_to(management->automatic_NO3_application_mode_event,PERMIT_ALL);

   TModalResult result = sync_form->ShowModal();
   delete sync_form;
   if (result == mrOk)
      update_sampling_date_button();
}
*/
void __fastcall Tauto_N_appl_mode_form::auto_NO3_radio_group_onclick(TObject */*Sender*/)
{
   show_hide_auto_NO3_parameters();
}
//---------------------------------------------------------------------------




