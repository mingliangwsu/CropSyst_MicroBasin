#pragma hdrstop
#include "CropSyst/source/mgmt_param.h"
#include "CropSyst/source/mgmtevnt.h"
#if (CS_VERSION==4)
//#include <../../help/management.h>
#include "CropSyst/GUI/help/management.h"
//170618 #  include "CropSyst/gui/builder/operation_event/operation_event_frm.h"
#  include "form_operation_event.h"
#define V4_HELP_URL(x) ,0

#else
#define V4_HELP_URL(x)

#endif
#include "form_management_editor.h"
#include "form_operation_event.h"
#include "form_auto_NO3_appl.h"
#include "form_clipping2.h"
#include "form_tillage_residue.h"
#include "form_irrig_appl.h"
#include "form_organic_N_appl.h"
#include "form_inorganic_N_appl.h"
#include "form_manure_appl.h"
#include "form_irrig_mode.h"
#include "form_auto_clipping.h"

#include "form_event.h"
//#include "GUI/event/form_sync.h"

#include "cs_till.h"

//170618#include "form_param_file.h"
#include "form_param_file_RS.h"

#pragma package(smart_init)
//______________________________________________________________________________
void __fastcall TManagement_editor_form::bind_to_V4_and_V5
(CropSyst_Management_parameters *_management,Tparameter_file_form      *_parameter_file_form)
{  management = _management;
   parameter_file_form = _parameter_file_form;
   radiogroup_land_treatment  ->bind_to(&(management->land_treatment_labeled) V4_HELP_URL(HELP_P_mgmt_conserv_land_treatment));
   radiogroup_auto_NO3        ->bind_to(&(management->N_application_soil_observation_event->automatic_N_mode_cowl_or_labeled)/* V4_HELP_URL(HELP_P_mgmt_N_automatic)*/);
   checkbox_auto_N            ->bind_to(&(management->automatic_nitrogen) /* V4_HELP_URL(HELP_P_mgmt_N_automatic)*/);
   checkbox_crop_management   ->bind_to(&(management->crop_management) /*    V4_HELP_URL(HELP_P_mgmt_crop_mode)*/);
   checkbox_CANMS->bind_to(&(management->CANMS_support));

   listbox_auto_NO3_split->bind_to(&(management->auto_N_applications)   /*V4_HELP_URL(HELP_P_mgmt_N_automatic)*/);
   edit_auto_NO3_split->bind_to(&auto_NO3_split_total                   /*V4_HELP_URL(HELP_P_mgmt_N_automatic)*/);

   Tevent_editor_form *schedule_form = new Tevent_editor_form(this);  // relinqished to this form
   schedule_form->Parent = tabsheet_sampling_date;
   schedule_form->Show();
   schedule_form->Top = 0;
   schedule_form->Left = 0;
   schedule_form->BorderStyle = bsNone;
   schedule_form->Align = alClient;
   schedule_form->bind_to(management->N_application_soil_observation_event
   ,management->crop_management
   ,false
   ,management->CANMS_support);

/* Don't delete yet, Not sure which is more recent
   N_sampling_event_form = new Tsync_form(this);
   N_sampling_event_form->Parent = tabsheet_sampling_date;
   N_sampling_event_form->Show();
   N_sampling_event_form->Top = 0;
   N_sampling_event_form->Left = 0;
   N_sampling_event_form->Align = alClient;
   N_sampling_event_form->BorderStyle = bsNone;
   nat32 sync_mode_bitmask
      = (1 << ACTUAL_DATE_MODE)
      | (1 << RELATIVE_TO_SIMULATION_EVENT_MODE)
      | (1 << RELATIVE_TO_SOWING_MODE)
      | (1 << BEFORE_PLANTING_MODE)
      | (1 << AFTER_NORMAL_CROP_GROWTH_STAGE_MODE)
      | (1 << AFTER_FRUIT_TREE_GROWTH_STAGE_MODE)
      | (1 << THERMAL_TIME_MODE);
   N_sampling_event_form->bind_to
      (&(management->N_application_soil_observation_event->begin_sync)
      ,sync_mode_bitmask);
*/


}
//______________________________________________________________________________
void TManagement_editor_form::Update_VCL_common()
{
   TForm::Update();
   radiogroup_land_treatment     ->Update();
   edit_soil_conserve_factor     ->Update();
   edit_target_yield_N_uptake_kg_ha->Update();
   edit_estimated_mineralization->Update();                                      //120711
   /*170705 obsolete
   edit_critical_soil_NO3        ->Update();
   */
   edit_sampling_depth           ->Update();
   edit_fert_use_eff             ->Update();
   checkbox_auto_N               ->Update();
   checkbox_crop_management      ->Update();
   checkbox_CANMS                ->Update();
   listbox_auto_NO3_split        ->Update();
   radiogroup_auto_NO3           ->Update();
   auto_NO3_split_total = management->total_automatic_N_applications();
   edit_auto_NO3_split->Update();
   edit_auto_NO3_split->Color = (auto_NO3_split_total == 100) ? clLime : clRed;
   show_hide_auto_NO3_parameters();                                              //120720
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::calc_soil_conserve_factor(TObject *Sender)
{
   if (!management) return;
   float32 contour_factor = 1.0;
   float32 strip_factor = 1.0;
   float32 terrace_factor = 1.0;
   switch (radiogroup_contouring_factor->ItemIndex)
   {
      case 0 : contour_factor = 0.6; break;
      case 1 : contour_factor = 0.5; break;
      case 2 : contour_factor = 0.5; break;
      case 3 : contour_factor = 0.6; break;
      case 4 : contour_factor = 0.7; break;
      case 5 : contour_factor = 0.8; break;
      case 6 : contour_factor = 0.9; break;
   }
   switch (radiogroup_strip_cropping_factor->ItemIndex)
   {
      case 0 : strip_factor = 1.0;  break;
      case 1 : strip_factor = 0.75; break;
      case 2 : strip_factor = 0.5;  break;
   }
   switch (radiogroup_terrace_sedimentation_factor->ItemIndex)
   {
      case 0 : terrace_factor = 1.0; break;
      case 1 : terrace_factor = 0.2; break;
      case 2 : terrace_factor = 0.1; break;
   }
   management->soil_conservation_factor = contour_factor * strip_factor * terrace_factor;
   edit_soil_conserve_factor->Update();
}
//______________________________________________________________________________
void TManagement_editor_form::show_hide_auto_NO3_parameters()
{
   if (management)
   {
      bool show_AUTO_NO3 = management ->N_application_soil_observation_event->automatic_N_mode_cowl_or_labeled.get() == AUTO_NITRO_BALANCE_BASED
                        || management ->N_application_soil_observation_event->automatic_N_mode_cowl_or_labeled.get() == AUTO_NITRO_LOCAL_CALIBRATION;

      pagecontrol_seasonal_N_appl->Visible = show_AUTO_NO3;
      edit_target_yield_N_uptake_kg_ha->Visible = management ->N_application_soil_observation_event->automatic_N_mode_cowl_or_labeled.get() == AUTO_NITRO_BALANCE_BASED;
      edit_estimated_mineralization->Visible =  management ->N_application_soil_observation_event->automatic_N_mode_cowl_or_labeled.get() == AUTO_NITRO_BALANCE_BASED;
/*170705 obsolete this mode is obsolete, now handled by specific inorg which
has condition N_soil_critical
      edit_critical_soil_NO3->Visible = management ->N_application_soil_observation_event->automatic_N_mode_cowl_or_labeled.get() == AUTO_NITRO_LOCAL_CALIBRATION;
*/
   }
}
//______________________________________________________________________________
void TManagement_editor_form::handle_add_auto_NO3_appl()
{
   if (management)
   {  CropSyst::N_application_soil_observation_mode::Split_application   *auto_N_split_op  = new CropSyst::N_application_soil_observation_mode::Split_application;
      Tform_auto_NO3_application *auto_N_split_form = new Tform_auto_NO3_application(this);
      auto_N_split_form->bind_to(auto_N_split_op,parameter_file_form);



      prompt_and_append_event(auto_N_split_op,auto_N_split_form,management->auto_N_applications,
         0 //NYI V4_HELP_URL(HELP_P_mgmt_N_automatic)
         //110113         parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_N_automatic).c_str()
         );
      Update(); // Just update everything this will recalc total
   }
}
//______________________________________________________________________________
void TManagement_editor_form::handle_listbox_auto_NO3_splitDblClick()
{
   if (management)
   {  int focused = listbox_auto_NO3_split->ItemIndex;
      Common_event *auto_N_split_appl_event = dynamic_cast<Common_event *>(management->auto_N_applications.get_at(focused));
      if (auto_N_split_appl_event)
      {  CropSyst::N_application_soil_observation_mode::Split_application *auto_N_split_appl_op
            = ( CropSyst::N_application_soil_observation_mode::Split_application *)auto_N_split_appl_event->get_operation();
         Tform_auto_NO3_application *auto_N_appl_form = new Tform_auto_NO3_application(this);
         auto_N_appl_form->bind_to(auto_N_split_appl_op,parameter_file_form);
         edit_event(auto_N_split_appl_event,auto_N_appl_form,
                     0 //NYI V4_HELP_URL(HELP_P_mgmt_N_automatic)
            //110113 parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_N_automatic).c_str()
            );
         Update();
      }
   }
}
//______________________________________________________________________________
TModalResult TManagement_editor_form::edit_event
(Common_event *event
,TForm *op_form
,const char          *help_HTML_filename
)
{  TModalResult result = mrCancel;
   Toperation_event_form *op_event_form = new Toperation_event_form(this);
   op_event_form->bind_to(event,op_form,management->crop_management,false,management->CANMS_support,help_HTML_filename);
   result = op_event_form->ShowModal();
   // dont delete op_event_form because give to op_form
   delete op_form;
   return result;
}
//_2017-07-01_moved_____________________________________________________________
Common_event * TManagement_editor_form::prompt_and_append_event
(CropSyst::Operation  *op
,TForm               *op_form
,Common_event_list   &event_list
,const char          *help_HTML_filename
)
{
   TModalResult result = mrCancel;
   Common_event *event = new Common_event(op,true);
   Toperation_event_form *op_event_form = new Toperation_event_form(this);
   op_event_form->bind_to(event,op_form,management->crop_management,false,management->CANMS_support,help_HTML_filename);
   result = op_event_form->ShowModal();
   if (result == mrOk)
   {
      event_list.append(event);
   }
   else
   {
      delete event;  event = 0;
// this event owns the op so no need to delete      delete op;     op = 0;
//      current_event_node = 0;
   }
   delete op_form;
   return event; //170701 result;
}
//_2017-07-01_moved_____________________________________________________________
Common_event * TManagement_editor_form::add_clipping_event(const char *help_URL)
{
   if (!verify_crop_associated_event()) return 0;
   CropSyst::Harvest_or_clipping_operation *harvest_or_clipping_op = new CropSyst::Harvest_or_clipping_operation;
   Tclipping_form *clipping_form = new Tclipping_form(this);
   clipping_form->bind_to(harvest_or_clipping_op,parameter_file_form);
   return prompt_and_append_event
      (harvest_or_clipping_op ,clipping_form
      ,management->harvest_or_clipping_operations
      ,help_URL);
}
//_2017-07-01___________________________________________________________________
Common_event * TManagement_editor_form::add_tillage_event(const char *help_URL)
{  CropSyst::Tillage_operation *tillage_op = new CropSyst::Tillage_operation;
   Ttillage_residue_form *tillage_form = new Ttillage_residue_form(this);
   tillage_form->bind_to(tillage_op,PRIMARY_TILL|SECONDARY_TILL|PLANTING_TILL|NO_TILL_DRILL,parameter_file_form);
   return prompt_and_append_event
      (tillage_op,tillage_form
      ,management->tillage_operations
      ,help_URL);
}
//_2017-07-01___________________________________________________________________
Common_event * TManagement_editor_form::add_residue_event(const char *help_URL)
{
   if (!verify_crop_associated_event()) return 0;
   CropSyst::Tillage_operation *residue_op = new CropSyst::Tillage_operation;
   residue_op->op_labeled.set(CS_OP_MGMT_RESIDUE);
   Ttillage_residue_form *residue_form = new Ttillage_residue_form(this);
   residue_form->bind_to(residue_op,RESIDUE,parameter_file_form);
   return prompt_and_append_event
      (residue_op,residue_form
      ,management->residue_operations
      ,help_URL);
}
//_2017-07-01___________________________________________________________________
Common_event *TManagement_editor_form::add_irrigation_event(const char *help_URL)
{
   CropSyst::Irrigation_operation *irrig_op = new CropSyst::Irrigation_operation;
   TIrrigation_application_form *irrig_appl_form = new TIrrigation_application_form(this);
   irrig_appl_form->bind_to
      (irrig_op
      ,&irrig_op->parameters                                                      //170710
      ,false,0,parameter_file_form);
   return prompt_and_append_event
      (irrig_op
      ,irrig_appl_form,management->irrigation_operations
      ,help_URL);
}
//_2017-07-01___________________________________________________________________
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
Common_event *TManagement_editor_form::add_organic_matter_event   (const char *help_URL)
{
   CropSyst::Organic_nitrogen_operation *org_N_appl_op = new CropSyst::Organic_nitrogen_operation;
   Torganic_N_application_form *org_N_appl_form = new Torganic_N_application_form(this);
   org_N_appl_form->bind_to(org_N_appl_form,parameter_file_form);
   return prompt_and_append_event
      (org_N_appl_op
      ,org_N_appl_form,management->org_N_application_operations
      ,help_URL);
}
//_2017-07-01___________________________________________________________________
#endif
Common_event *TManagement_editor_form::add_biomatter_event   (const char *help_URL)
{
   CropSyst::Biomatter_application_operation *biomatter_appl_op = new CropSyst::Biomatter_application_operation;
   Tmanure_application_form *manure_appl_form = new Tmanure_application_form(this);
   manure_appl_form->bind_to(biomatter_appl_op,parameter_file_form);
   return prompt_and_append_event
      (biomatter_appl_op
      ,manure_appl_form,management->biomatter_application_operations
      ,help_URL);
}
//_2017-07-04___________________________________________________________________
Common_event * TManagement_editor_form::add_inorganic_event(const char *help_URL)
{
   CropSyst::Inorganic_nitrogen_operation *inorg_N_appl_op = new CropSyst::Inorganic_nitrogen_operation;
   Tinorganic_N_application_form *inorg_N_appl_form = new Tinorganic_N_application_form(this);
   inorg_N_appl_form->bind_to(inorg_N_appl_op,parameter_file_form);
   return prompt_and_append_event
      (inorg_N_appl_op,inorg_N_appl_form
      ,management->inorganic_nitrogen_operations
      ,help_URL);
}
//_2017-07-01___________________________________________________________________
Common_event * TManagement_editor_form::add_auto_irrigation_mode  (const char *help_URL)
{
   CropSyst::Automatic_irrigation_mode *irrig_mode = new CropSyst::Automatic_irrigation_mode;
   TIrrigation_application_form *irrig_form = new TIrrigation_application_form(this);

   /*170710
   CropSyst::Automatic_irrigation_mode_class *irrig_mode_class = irrig_mode;               //170710

   CropSyst::Irrigation_operation_class *irrg_op_class = irrig_mode_class;       //170710

   CropSyst::Irrigation_operation   *irrg_op = irrg_op_class; // irrig_mode_class; // irrig_mode;                       //170710
   irrig_form->bind_to(irrg_op,true,0,parameter_file_form);
   */

   irrig_form->bind_to
      (irrig_mode
      ,&irrig_mode->parameters                                                   //170710
      ,true,0,parameter_file_form);

   return prompt_and_append_event
      (irrig_mode,irrig_form
      ,management->auto_irrigation_mode_operations,help_URL);
}
//_2017-07-01___________________________________________________________________
Common_event * TManagement_editor_form::add_auto_clipping_mode     (const char *help_URL)
{
   if (!verify_crop_associated_event()) return 0;
   CropSyst::Auto_clip_biomass_mode *clipping_mode = new CropSyst::Auto_clip_biomass_mode;
   Tauto_clipping_form *clipping_mode_form = new Tauto_clipping_form(this);
   clipping_mode_form->bind_to(clipping_mode,parameter_file_form);
   return prompt_and_append_event((clipping_mode)
         ,clipping_mode_form,management->auto_clip_biomass_mode_operations
      ,help_URL);
}
//_2017-07-01___________________________________________________________________
bool TManagement_editor_form::verify_crop_associated_event()        affirmation_
{  bool proceed = true;
   if (!management->crop_management)
   {
      int result = Application->MessageBox
         (L"This operation is specifically intended\n"
           "to be applied to crop management,"
           "however management schedule is marked\n"
           "as not intended for use with crop management\n\n"
           "The operation would not be applied."
         , L"Add the operation anyway?"
         ,MB_YESNOCANCEL  );
      proceed = result == IDYES;

   }
   return proceed;
}
//_2017-07-07___________________________________________________________________
