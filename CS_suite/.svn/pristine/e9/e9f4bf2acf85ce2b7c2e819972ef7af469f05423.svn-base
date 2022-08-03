//______________________________________________________________________________
#include <vcl.h>
#pragma hdrstop
//150402 #include "CropSyst/source/mgmt_param.h"
#include "CropSyst/source/management/management_param_V4.h"

#include "form_management_editor.h"
#include "form_clipping.h"
#include "form_auto_clipping.h"
#include "form_auto_N_mode.h"
#include "form_irrig_appl.h"
#include "form_irrig_mode.h"
#include "form_auto_NO3_appl.h"
#include "form_tillage_residue.h"
#include "form_organic_N_appl.h"
#include "form_manure_appl.h"
#include "form_inorganic_N_appl.h"
#include "CropSyst/source/cs_till.h"
#include "form_operation_event.h"
#include "GUI/event/form_sync.h"
#include "corn/data_source/VV_File.h"
#include "CS_suite/application/CS_suite_directory.h"
#include "CropSyst/GUI/help/management.h"
#include "form_event.h"
#include "CropSyst/source/mgmtevnt.h"
#include "common/simulation/event.h"
#include <GUI/parameter/form_param_file.h>
#include "CS_Suite/CropSyst/form_common_editor_inc.h"

bool LADSS_mode = false;
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoFloat32EditBar"
#pragma link "AutoStringEdit"
#pragma link "AutoRadioGroup"
#pragma link "AutoContainerTreeView"
#pragma link "AutoInt16EditBar"
#pragma link "cdiroutl"
#pragma link "AutoContainerCheckListBox"
#pragma link "AutoContainerListBox"
#pragma link "SHDocVw_OCX"
#pragma link "AutoCheckBox"
#pragma link "AutoInt16Edit"
#pragma link "AutoFloat32Edit"
#pragma resource "*.dfm"
TManagement_editor_form *Management_editor_form;

extern CORN::OS_FS::Program_directory *management_editor_directory;
using namespace CropSyst;

//#define V4_HELP_URL(x) ,0

//______________________________________________________________________________
__fastcall TManagement_editor_form::TManagement_editor_form(TComponent* Owner)
   : TForm(Owner)
   TManagement_editor_form_CONSTRUCTOR_INITIALIZATION
, sampling_date_form(0)                                                          //120625
{}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::bind_to(CropSyst_Management_parameters *_management,Tparameter_file_form      *_parameter_file_form)
{
   bind_to_V4_and_V5(_management,_parameter_file_form);

   // The following are either only in version 4 or are using valid edits
   #if (CS_VERSION == 4)
   CORN::OS::File_name_concrete composed_filename_buffer;
   #endif
   // Conservation
   edit_soil_conserve_factor            ->bind_to(&(management->v_soil_conservation_factor)
      V4_HELP_URL(HELP_P_mgmt_conserv_soil_practice_factor));
//       V4_HELP_URL(HELP_P_mgmt_conserv_soil_practice_factor));

   // Irrigation
   irrigation_spec_checklistbox  ->bind_to(&(management->irrigation_operations)           V4_HELP_URL(HELP_P_irrigation_spec));
   irrigation_auto_checklistbox  ->bind_to(&(management->auto_irrigation_mode_operations) V4_HELP_URL(HELP_P_mgmt_irrig_automatic));
   checklistbox_N_inorganic      ->bind_to(&(management->inorganic_nitrogen_operations)   V4_HELP_URL(HELP_P_mgmt_N_inorg_appl));
   N_organic_checklistbox        ->bind_to(&(management->organic_nitrogen_operations)     V4_HELP_URL(HELP_P_mgmt_N_org_appl));
   checklistbox_organic_matter_appl->bind_to(&(management->biomatter_application_operations) V4_HELP_URL(HELP_P_mgmt_N_org_appl/*eventually will have a separate manure op help*/));
   clipping_spec_checklistbox    ->bind_to(&(management->harvest_or_clipping_operations)     V4_HELP_URL(HELP_P_mgmt_harvest));
   clipping_auto_checklistbox    ->bind_to(&(management->auto_clip_biomass_mode_operations)  V4_HELP_URL(HELP_P_mgmt_clip_automatic));
   tillage_spec_checklistbox     ->bind_to(&(management->tillage_operations)                 V4_HELP_URL(HELP_P_mgmt_tillage_residue));
   residue_spec_checklistbox     ->bind_to(&(management->residue_operations)                 V4_HELP_URL(HELP_P_mgmt_tillage_residue));
//Returned to simply enabling automatic_nitrogen
//And the N application mode based on soil conditions is also simply enabled (once per season)
   // 040712 Need more specific help for these two editors

   edit_target_yield_N_uptake_kg_ha ->bind_to(&(management->N_application_soil_observation_event->v_target_yield_N_uptake)          V4_HELP_URL(HELP_P_mgmt_N_uptake_target_yield));
   edit_estimated_mineralization    ->bind_to(&(management->N_application_soil_observation_event->v_estimated_mineralization)       V4_HELP_URL(HELP_P_mgmt_N_uptake_target_yield));
   edit_critical_soil_NO3           ->bind_to(&(management->N_application_soil_observation_event->v_critical_soil_N_for_no_response)V4_HELP_URL(HELP_P_mgmt_N_critical_NO3));
   edit_sampling_depth              ->bind_to(&(management->N_application_soil_observation_event->v_soil_N_sampling_depth)          V4_HELP_URL(HELP_P_mgmt_N_sampling_depth));
   edit_fert_use_eff                ->bind_to(&(management->N_application_soil_observation_event->v_fertilizer_use_efficiency)      V4_HELP_URL(HELP_P_mgmt_N_fert_use_eff));

   edit_seasonal_carbon_footprint               ->bind_to(&(management->seasonal_carbon_footprint_kgCO2e_ha),2,0);
   edit_seasonal_irrigation_carbon_footprint    ->bind_to(&(management->seasonal_irrigation_carbon_footprint_kgCO2e_ha),2,0);
   edit_irrigation_application_carbon_footprint ->bind_to(&(management->irrigation_application_carbon_footprint_kgCO2e_ha_mm),2,0);

   //101216 NYI These NO3 split controls will be common to V5

   listbox_auto_NO3_split->bind_to(&(management->auto_N_applications)   V4_HELP_URL(HELP_P_mgmt_N_automatic));
   edit_auto_NO3_split->bind_to(&auto_NO3_split_total                   V4_HELP_URL(HELP_P_mgmt_N_automatic));

   sampling_date_form = new Tsync_form(this);                                    //120625
   sampling_date_form->Parent = tabsheet_sampling_date;                          //120625
   sampling_date_form->Show();                                                   //120625
   sampling_date_form->Top = 0;                                                  //120625
   sampling_date_form->Left = 0;                                                 //120625
   sampling_date_form->Align = alClient;                                         //120625
   sampling_date_form->BorderStyle = bsNone;                                     //120625
   nat32 sync_mode_bitmask                                                       //120625
      = (1 << ACTUAL_DATE_MODE)                                                  //120625
      | (1 << RELATIVE_TO_SIMULATION_EVENT_MODE)                                 //120625
      | (1 << RELATIVE_TO_SOWING_MODE)                                           //120625
      | (1 << BEFORE_PLANTING_MODE)                                              //120625
      | (1 << AFTER_NORMAL_CROP_GROWTH_STAGE_MODE)                               //120625
      | (1 << AFTER_FRUIT_TREE_GROWTH_STAGE_MODE)                                //120625
      | (1 << THERMAL_TIME_MODE);                                                //120625
   sampling_date_form->bind_to(&(management->N_application_soil_observation_event->begin_sync),sync_mode_bitmask); //120625
   show_hide_controls(0);
};
//______________________________________________________________________________
void __fastcall TManagement_editor_form::Update()
{
   Update_VCL_common();
/*101216 moved to Update_VCL_common
   TForm::Update();
   radiogroup_land_treatment    ->Update();
   edit_soil_conserve_factor      ->Update();
   checkbox_auto_N               ->Update();
   checkbox_crop_management      ->Update();
   checkbox_CANMS                ->Update();
*/
   irrigation_spec_checklistbox  ->Update();
   irrigation_auto_checklistbox  ->Update();
   checklistbox_N_inorganic      ->Update();
   N_organic_checklistbox        ->Update();
   checklistbox_organic_matter_appl      ->Update();
   clipping_spec_checklistbox    ->Update();
   clipping_auto_checklistbox    ->Update();
   tillage_spec_checklistbox     ->Update();
   residue_spec_checklistbox     ->Update();

   tabsheet_organic_nitrogen_deprecated->TabVisible = management->organic_nitrogen_operations.count() > 0;

   // Need to move these to common
   edit_seasonal_carbon_footprint               ->Update();
   edit_seasonal_irrigation_carbon_footprint    ->Update();
   edit_irrigation_application_carbon_footprint ->Update();


   /*101216 moved to Update_VCL_common
   listbox_auto_NO3_split        ->Update();
   auto_NO3_split_total = management->total_automatic_NO3_applications();
   if (auto_NO3_split_total == 100)
      edit_auto_NO3_split->Color = clLime;
   else
      edit_auto_NO3_split->Color = clRed;
   edit_auto_NO3_split->Update();
   */

   //120625   schedule_form->Update();                                                    //120625
   sampling_date_form->Update();                                                 //120625
      //start_sync_form->Update may need to be moved to common
};
//______________________________________________________________________________

TModalResult TManagement_editor_form::prompt_and_append_event
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
// this event owns the op so no need to delete      delete op;     op = 0;
//      current_event_node = 0;
   }
   delete op_form;
   return result;
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
   delete op_form;
   return result;
};
//______________________________________________________________________________
void __fastcall TManagement_editor_form::add_irrigation_mode_button_onclick(TObject */*Sender*/)
{  if (management)
   { 
	  add_auto_irrigation_event(HELP_P_mgmt_irrig_automatic);
      /*17070   1
      CropSyst::Automatic_irrigation_mode *irrig_mode = new CropSyst::Automatic_irrigation_mode;
      TIrrigation_application_form *irrig_form = new TIrrigation_application_form(this);
      irrig_form->bind_to(irrig_mode,true,0,parameter_file_form);
      prompt_and_append_event(irrig_mode,irrig_form,management->auto_irrigation_mode_operations V4_HELP_URL(HELP_P_mgmt_irrig_automatic));
	  */
      irrigation_auto_checklistbox->Update();
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::irrigation_auto_checklistbox_ondblclick(TObject */*Sender*/)
{  if (management)
   {  int focused = irrigation_auto_checklistbox->ItemIndex;
      Common_event *auto_irrig_event = dynamic_cast<Common_event *>(management->auto_irrigation_mode_operations.get_at(focused));
      if (auto_irrig_event)
      {  CropSyst::Automatic_irrigation_mode *irrig_mode = (CropSyst::Automatic_irrigation_mode *)auto_irrig_event->get_operation();
         TIrrigation_application_form *irrig_form = new TIrrigation_application_form(this);
         irrig_form->bind_to(irrig_mode,true,0,parameter_file_form);
         edit_event(auto_irrig_event,irrig_form V4_HELP_URL(HELP_P_mgmt_irrig_automatic));
         irrigation_auto_checklistbox->Update();
      }
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::add_clipping_event_button_onclick(TObject */*Sender*/)
{  if (management)
   {  
	  add_clipping_event(parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_harvest));
	  /*
	  CropSyst::Harvest_or_clipping_operation *harvest_or_clipping_op = new CropSyst::Harvest_or_clipping_operation;
      Tclipping_form *clipping_form = new Tclipping_form(this);
      clipping_form->bind_to(harvest_or_clipping_op,parameter_file_form,false );
      prompt_and_append_event(harvest_or_clipping_op ,clipping_form,management->harvest_or_clipping_operations V4_HELP_URL(HELP_P_mgmt_harvest));
	  */
      clipping_spec_checklistbox->Update();
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::clipping_spec_checklistbox_ondblclick(TObject */*Sender*/)
{  if (management)
   {  int focused = clipping_spec_checklistbox->ItemIndex;
      Common_event *clipping_spec_event = dynamic_cast<Common_event *>(management->harvest_or_clipping_operations.get_at(focused));
      if (clipping_spec_event)
      {  CropSyst::Harvest_or_clipping_operation *clipping_op =
            //150404 (CropSyst::Harvest_or_clipping_operation *)
            dynamic_cast<CropSyst::Harvest_or_clipping_operation *>                //150404
            (clipping_spec_event->get_operation());
         Tclipping_form *clipping_form = new Tclipping_form(this);
         clipping_form->bind_to(clipping_op,parameter_file_form,false);
         edit_event(clipping_spec_event,clipping_form V4_HELP_URL(HELP_P_mgmt_harvest));
         clipping_spec_checklistbox->Update();
      }
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::add_clipping_mode_button_onclick(TObject */*Sender*/)
{  if (management)
   {  
	  add_auto_clipping_mode     (HELP_P_mgmt_clip_automatic);
	  /*170701
	  CropSyst::Auto_clip_biomass_mode *clipping_mode = new CropSyst::Auto_clip_biomass_mode;
      Tauto_clipping_form *clipping_mode_form = new Tauto_clipping_form(this);
      clipping_mode_form->bind_to(clipping_mode,parameter_file_form);
      prompt_and_append_event((clipping_mode)
         ,clipping_mode_form,management->auto_clip_biomass_mode_operations V4_HELP_URL(HELP_P_mgmt_clip_automatic));
	  */
      clipping_auto_checklistbox->Update();
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::clipping_auto_checklistbox_dblclick(TObject */*Sender*/)
{  if (management)
   {  int focused = clipping_auto_checklistbox->ItemIndex;
      Common_event *auto_clip_event = dynamic_cast<Common_event *>(management->auto_clip_biomass_mode_operations.get_at(focused));
      if (auto_clip_event)
      {  Auto_clip_biomass_mode *clipping_mode = dynamic_cast<Auto_clip_biomass_mode *>
         (auto_clip_event->get_operation());
         Tauto_clipping_form *clipping_mode_form = new Tauto_clipping_form(this);
         clipping_mode_form->bind_to(clipping_mode,parameter_file_form);
         edit_event(auto_clip_event,clipping_mode_form V4_HELP_URL(HELP_P_mgmt_clip_automatic));
         clipping_auto_checklistbox->Update();
      }
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::add_tillage_event_button_onclick(TObject */*Sender*/)
{  if (management)
   {  
      add_tillage_event(parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_tillage_residue));
	  /*170701
      Tillage_operation *tillage_op = new Tillage_operation;
      Ttillage_residue_form *tillage_form = new Ttillage_residue_form(this);
      tillage_form->bind_to(tillage_op,PRIMARY_TILL|SECONDARY_TILL|PLANTING_TILL|NO_TILL_DRILL,parameter_file_form);
      prompt_and_append_event(tillage_op,tillage_form,management->tillage_operations V4_HELP_URL(HELP_P_mgmt_tillage_residue));
	  */
      tillage_spec_checklistbox->Update();
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::tillage_spec_checklistbox_dblclick(TObject */*Sender*/)
{  if (management)
   {  int focused = tillage_spec_checklistbox->ItemIndex;
      Common_event *tillage_event = dynamic_cast<Common_event *>(management->tillage_operations.get_at(focused));
      if (tillage_event)
      {  Tillage_operation *tillage_op = (Tillage_operation *)tillage_event->get_operation();
         Ttillage_residue_form *tillage_form = new Ttillage_residue_form(this);
         tillage_form->bind_to(tillage_op,PRIMARY_TILL|SECONDARY_TILL|PLANTING_TILL|NO_TILL_DRILL,parameter_file_form);
         edit_event(tillage_event,tillage_form V4_HELP_URL/*130313 parameter_file_form->compose_manual_subdirectory_filename*/(HELP_P_mgmt_tillage_residue));
         tillage_spec_checklistbox->Update();
      }
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::add_residue_event_button_onclick(TObject */*Sender*/)
{
///nyi   schedule_treeview->focus_level_node("Residue","Specific");
   if (management)
   {
	  add_residue_event(parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_tillage_residue));
	  /*170701 
      Residue_operation *residue_op = new Residue_operation;
      Ttillage_residue_form *residue_form = new Ttillage_residue_form(this);
      residue_form->bind_to(residue_op,RESIDUE,parameter_file_form);
      prompt_and_append_event(residue_op,residue_form,management->residue_operations V4_HELP_URL(HELP_P_mgmt_tillage_residue));
	  */
      residue_spec_checklistbox->Update();
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::residue_spec_checklistbox_ondblclick(TObject */*Sender*/)
{
   if (management)
   {  int focused = residue_spec_checklistbox->ItemIndex;
      Common_event *residue_event = dynamic_cast<Common_event *>(management->residue_operations.get_at(focused));
      if (residue_event)
      {  Residue_operation *residue_op = (Residue_operation *)residue_event->get_operation();
         Ttillage_residue_form *residue_form = new Ttillage_residue_form(this);
         residue_form->bind_to(residue_op,RESIDUE,parameter_file_form);
         edit_event(residue_event,residue_form V4_HELP_URL(HELP_P_mgmt_tillage_residue));
         residue_spec_checklistbox->Update();
      }
   }
}
//============================================================================
void __fastcall TManagement_editor_form::add_irrigation_appl_button_onclick(TObject */*Sender*/)
{
   if (management)
   {  
      add_irrigation_event(parameter_file_form->compose_manual_subdirectory_filename(HELP_P_irrigation_spec));
	  /*170701 
	  Irrigation_operation *irrig_op = new Irrigation_operation;
      TIrrigation_application_form *irrig_appl_form = new TIrrigation_application_form(this);
      irrig_appl_form->bind_to(irrig_op,false,0,parameter_file_form);
      prompt_and_append_event(irrig_op,irrig_appl_form,management->irrigation_operations V4_HELP_URL(HELP_P_irrigation_spec));
	  */
      irrigation_spec_checklistbox->Update();
   };
};
//______________________________________________________________________________
void __fastcall TManagement_editor_form::irrigation_spec_checklistbox_ondblclick(TObject */*Sender*/)
{  if (management)
   {  int focused = irrigation_spec_checklistbox->ItemIndex;
      Common_event *irrig_event = dynamic_cast<Common_event *>(management->irrigation_operations.get_at(focused));
      if (irrig_event)
      {  Irrigation_operation *irrig_op = (Irrigation_operation *)irrig_event->get_operation();
         TIrrigation_application_form *irrig_appl_form = new TIrrigation_application_form(this);
         irrig_appl_form->bind_to(irrig_op,false,&(irrig_event->contingency_labeled),parameter_file_form);
         edit_event(irrig_event,irrig_appl_form V4_HELP_URL(HELP_P_irrigation_spec));
         irrigation_spec_checklistbox->Update();
      };
   };
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::irrigation_spec_delete_button_onclick(TObject */*Sender*/)
{  irrigation_spec_checklistbox->delete_selected(); }
//______________________________________________________________________________
void __fastcall TManagement_editor_form::irrigation_auto_delete_buttonClick(TObject */*Sender*/)
{  irrigation_auto_checklistbox->delete_selected(); }
//______________________________________________________________________________
void __fastcall TManagement_editor_form::clipping_spec_delete_button_onclick(TObject */*Sender*/)
{  clipping_spec_checklistbox->delete_selected(); }
//______________________________________________________________________________
void __fastcall TManagement_editor_form::clipping_auto_delete_button_onclick(TObject */*Sender*/)
{  clipping_auto_checklistbox->delete_selected(); }
//______________________________________________________________________________
void __fastcall TManagement_editor_form::tillage_spec_delete_button_onclick(TObject */*Sender*/)
{  tillage_spec_checklistbox->delete_selected(); }
//______________________________________________________________________________
void __fastcall TManagement_editor_form::residue_spec_delete_button_onclick(TObject */*Sender*/)
{  residue_spec_checklistbox->delete_selected(); }
//______________________________________________________________________________
void __fastcall TManagement_editor_form::N_inorganic_delete_button_onclick(TObject */*Sender*/)
{  checklistbox_N_inorganic->delete_selected(); }
//______________________________________________________________________________
void __fastcall TManagement_editor_form::N_organic_delete_button_onclick(TObject */*Sender*/)
{  N_organic_checklistbox->delete_selected(); }
//______________________________________________________________________________
void __fastcall TManagement_editor_form::button_organic_matter_deleteClick(TObject *Sender)
{   checklistbox_organic_matter_appl->delete_selected(); }
//==========================================================================

void __fastcall TManagement_editor_form::N_organic_add_button_onclick(TObject *)
{  // This is obsolete in V5
/*150403 obsolete
   if (management)
   {  CropSyst::Organic_nitrogen_operation *org_N_appl_op = new CropSyst::Organic_nitrogen_operation;
      Torganic_N_application_form *org_N_appl_form = new Torganic_N_application_form(this);
      org_N_appl_form->bind_to(org_N_appl_op,parameter_file_form);
      prompt_and_append_event(org_N_appl_op,org_N_appl_form,management->organic_nitrogen_operations V4_HELP_URL(HELP_P_mgmt_N_org_appl));
      N_organic_checklistbox->Update();
   }
*/
}//______________________________________________________________________________
void __fastcall TManagement_editor_form::button_organic_matter_addClick(TObject *Sender)
{
   if (management)
   {  
      add_organic_matter_event(HELP_P_mgmt_N_org_appl);   
	  /*170701
	  CropSyst::Biomatter_application_operation *biomatter_appl_op = new CropSyst::Biomatter_application_operation;
      Tmanure_application_form *manure_appl_form = new Tmanure_application_form(this);
      manure_appl_form->bind_to(biomatter_appl_op,parameter_file_form);
      prompt_and_append_event(biomatter_appl_op,manure_appl_form,management->biomatter_application_operations V4_HELP_URL(HELP_P_mgmt_N_org_appl));
	  */
      checklistbox_organic_matter_appl->Update();
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::N_organic_checklistbox_ondblclick(TObject */*Sender*/)
{  if (management)
   {  int focused = N_organic_checklistbox->ItemIndex;
      Common_event *org_N_event = dynamic_cast<Common_event *>(management->organic_nitrogen_operations.get_at(focused));
      if (org_N_event)
      {  Organic_nitrogen_operation *org_N_op = (Organic_nitrogen_operation *)org_N_event->get_operation();
         Torganic_N_application_form *org_N_appl_form = new Torganic_N_application_form(this);
         org_N_appl_form->bind_to(org_N_op,parameter_file_form);
         edit_event(org_N_event,org_N_appl_form V4_HELP_URL(HELP_P_mgmt_N_org_appl));
         N_organic_checklistbox->Update();
      }
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::checklistbox_organic_matter_applDblClick(TObject *Sender)
{  if (management)
   {  int focused = checklistbox_organic_matter_appl->ItemIndex;
      Common_event *biomatter_appl_event = dynamic_cast<Common_event *>(management->biomatter_application_operations.get_at(focused));
      if (biomatter_appl_event)
      {  Biomatter_application_operation *manure_op = (Biomatter_application_operation *)biomatter_appl_event->get_operation();
         Tmanure_application_form *manure_appl_form = new Tmanure_application_form(this);
         manure_appl_form->bind_to(manure_op,parameter_file_form);
         edit_event(biomatter_appl_event,manure_appl_form V4_HELP_URL(HELP_P_mgmt_N_org_appl/*eventual need manure op help*/));
         checklistbox_organic_matter_appl->Update();
      }
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::N_inorganic_add_button_onclick(TObject */*Sender*/)
{  if (management)
   {  add_inorganic_event(HELP_P_mgmt_N_inorg_appl);
      /*170701 
      Inorganic_nitrogen_operation *inorg_N_appl_op = new Inorganic_nitrogen_operation;
      Tinorganic_N_application_form *inorg_N_appl_form = new Tinorganic_N_application_form(this);
      inorg_N_appl_form->bind_to(inorg_N_appl_op,parameter_file_form);
      prompt_and_append_event(inorg_N_appl_op,inorg_N_appl_form,management->inorganic_nitrogen_operations V4_HELP_URL(HELP_P_mgmt_N_inorg_appl));
	  */
      checklistbox_N_inorganic->Update();
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::checklistbox_N_inorganic_ondblclick(TObject */*Sender*/)
{
   // continue here, call V4 V5 common function
   if (management)
   {  int focused = checklistbox_N_inorganic->ItemIndex;
      Common_event *inorg_N_event = dynamic_cast<Common_event *>(management->inorganic_nitrogen_operations.get_at(focused));
      if (inorg_N_event)
      {  Inorganic_nitrogen_operation *inorg_N_op = (Inorganic_nitrogen_operation *)inorg_N_event->get_operation();
         Tinorganic_N_application_form *inorg_N_appl_form = new Tinorganic_N_application_form(this);
         inorg_N_appl_form->bind_to(inorg_N_op,parameter_file_form);
         edit_event(inorg_N_event,inorg_N_appl_form V4_HELP_URL(HELP_P_mgmt_N_inorg_appl));
         checklistbox_N_inorganic->Update();
      }
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::auto_NO3_split_listbox_ondblclick(TObject *Sender)
{  handle_listbox_auto_NO3_splitDblClick();
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::show_hide_controls(TObject *Sender)
{  clipping_tabsheet->TabVisible = management->crop_management;
   residue_tabsheet->TabVisible = management->crop_management;
}
//______________________________________________________________________________

/*
#  define HELP_P_management                     "management\\general.htm"
#  define HELP_P_mgmt_harvest_wait              "management\\harvest.htm#wait"
#  define HELP_P_mgmt_planting                  "management\\planting.htm"
#  define HELP_P_mgmt_latest_date               "management\\harvest.htm#latest_date"
#  define HELP_P_mgmt_fract_straw_to_residue    "management\\harvest.htm#fract_straw_to_residue"
#  define HELP_P_mgmt_irrig_automatic           "management\\irrigation.htm#automatic"
#  define HELP_P_mgmt_irrig_period              "management\\irrigation.htm#period"
#  define HELP_P_mgmt_clip_season               "management\\clipping.htm#season"
#  define HELP_P_mgmt_clip_periodic             "management\\clipping.htm#periodic"
#  define HELP_P_mgmt_clip_period               "management\\clipping.htm#period"
#  define HELP_P_mgmt_clip_frequency            "management\\clipping.htm#frequency"
#  define HELP_P_mgmt_clip_specific             "management\\clipping.htm#specific"
#  define HELP_P_mgmt_conserv_land_treatment    "management\\conservation.htm#land_treatment"
#  define HELP_P_mgmt_tillage_residue           "management\\tillage_residue.htm"
#  define HELP_P_mgmt_N_optimal                 "management\\nitrogen.htm#optimal"
#  define HELP_P_mgmt_N_balance_based           "management\\nitrogen.htm#balance_based"
#  define HELP_P_mgmt_N_calibration_based       "management\\nitrogen.htm#calibration_based"
#  define HELP_P_mgmt_N_sampling_date           "management\\nitrogen.htm#sampling_date"
*/
//______________________________________________________________________________
void __fastcall TManagement_editor_form::button_auto_NO3_appl_add_onclick(TObject *Sender)
{  handle_add_auto_NO3_appl();                                                          //101221
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::auto_NO3_appl_delete_button_onclick(TObject *Sender)
{  listbox_auto_NO3_split->delete_selected(); }
//______________________________________________________________________________
void TManagement_editor_form::open_operation_event(const char *op_event_ID)
{  // This is used with the schedule viewer to view the parameters
   // for a specific operation.
 if (management)
   {
      {  Common_event *auto_irrig_event = dynamic_cast<Common_event *>(management->auto_irrigation_mode_operations.find_cstr(op_event_ID));
         if (auto_irrig_event)
         {  CropSyst::Automatic_irrigation_mode *irrig_mode = (CropSyst::Automatic_irrigation_mode *)auto_irrig_event->get_operation();
            TIrrigation_application_form *irrig_form = new TIrrigation_application_form(this);
            irrig_form->bind_to(irrig_mode,true,0/*contingency does not apply to auto mode */,parameter_file_form);
            edit_event(auto_irrig_event,irrig_form V4_HELP_URL(HELP_P_mgmt_irrig_automatic));
            irrigation_auto_checklistbox->Update();
      }  }
      {  Common_event *inorg_N_event = dynamic_cast<Common_event *>(management->inorganic_nitrogen_operations.find_cstr(op_event_ID));
         if (inorg_N_event)
         {  Tinorganic_N_application_form *inorg_N_appl_form = new Tinorganic_N_application_form(this);
            CropSyst::Inorganic_nitrogen_operation *inorg_N_op = (CropSyst::Inorganic_nitrogen_operation *)inorg_N_event->get_operation();
            inorg_N_appl_form->bind_to(inorg_N_op,parameter_file_form);
            edit_event(inorg_N_event,inorg_N_appl_form V4_HELP_URL(HELP_P_mgmt_N_inorg_appl));
            checklistbox_N_inorganic->Update();
      }; };
      {  Common_event *org_N_event = dynamic_cast<Common_event *>(management->organic_nitrogen_operations.find_cstr(op_event_ID));
         if (org_N_event)
         {  Torganic_N_application_form *org_N_appl_form = new Torganic_N_application_form(this);
            CropSyst::Organic_nitrogen_operation *org_N_op = (CropSyst::Organic_nitrogen_operation *)org_N_event->get_operation();
            org_N_appl_form->bind_to(org_N_op,parameter_file_form);
            edit_event(org_N_event,org_N_appl_form V4_HELP_URL(HELP_P_mgmt_N_org_appl));
            N_organic_checklistbox->Update();
      }  }
      {  Common_event *biomatter_application_event = dynamic_cast<Common_event *>(management->biomatter_application_operations.find_cstr(op_event_ID));
         if (biomatter_application_event)
         {  Tmanure_application_form *manure_appl_form = new Tmanure_application_form(this);
            CropSyst::Biomatter_application_operation *biomatter_appl_op = (CropSyst::Biomatter_application_operation *)biomatter_application_event->get_operation();
            manure_appl_form->bind_to(biomatter_appl_op,parameter_file_form);
            edit_event(biomatter_application_event,manure_appl_form V4_HELP_URL(HELP_P_mgmt_N_org_appl /*Eventually this will be manure application op help */));
            checklistbox_organic_matter_appl->Update();
      }  }
      {  Common_event *tillage_event = dynamic_cast<Common_event *>(management->tillage_operations.find_cstr(op_event_ID));
         if (tillage_event)
         {
            CropSyst::Tillage_operation *tillage_op = (CropSyst::Tillage_operation *)tillage_event->get_operation();
            Ttillage_residue_form *tillage_form = new Ttillage_residue_form(this);
            tillage_form->bind_to(tillage_op,PRIMARY_TILL|SECONDARY_TILL|PLANTING_TILL|NO_TILL_DRILL,parameter_file_form);
            edit_event(tillage_event,tillage_form V4_HELP_URL(HELP_P_mgmt_tillage_residue));
            tillage_spec_checklistbox->Update();
      }  }
      {  Common_event *residue_event = dynamic_cast<Common_event *>(management->residue_operations.find_cstr(op_event_ID));
         if (residue_event)
         {  Ttillage_residue_form *residue_form = new Ttillage_residue_form(this);
            CropSyst::Residue_operation *residue_op = (CropSyst::Residue_operation *)residue_event->get_operation();
            residue_form->bind_to(residue_op,RESIDUE,parameter_file_form);
            edit_event(residue_event,residue_form V4_HELP_URL(HELP_P_mgmt_tillage_residue));
            residue_spec_checklistbox->Update();
      }  }
/*NYI
      {  Common_event *xxxxx = (Common_event *)chemical_operations.find(op_event_ID);
         if (xxxxx)
         {  TXxxxxxxx_form *xxxxxx_form = new TXxxxxxxx_form(this);
            XXXX_op *xxxx_op = (XXXXX_op *)xxxxxx_event->get_operation();
            xxxxxx_form->bind_to(irrig_mode);
            edit_event(xxxxx,xxxxxx_form);
            XXXXXXXX_auto_checklistbox->Update();
      }; };
*/
      {  Common_event *harvest_or_clipping_event = dynamic_cast<Common_event *>(management->harvest_or_clipping_operations.find_cstr(op_event_ID));
         if (harvest_or_clipping_event)
         {  Tclipping_form *clipping_form = new Tclipping_form(this);
            CropSyst::Harvest_or_clipping_operation *clipping_op =
               dynamic_cast<CropSyst::Harvest_or_clipping_operation *>           //150404
               //150404(CropSyst::Harvest_or_clipping_operation *)
               (harvest_or_clipping_event->get_operation());
            clipping_form->bind_to(clipping_op,parameter_file_form,false);
            edit_event(harvest_or_clipping_event,clipping_form V4_HELP_URL(HELP_P_mgmt_harvest));
            clipping_spec_checklistbox->Update();
      }  }
      {  Common_event *auto_N_split_appl_event = dynamic_cast<Common_event *>(management->auto_N_applications.find_cstr(op_event_ID));
         if (auto_N_split_appl_event)
         {  Tform_auto_NO3_application *auto_N_appl_form = new Tform_auto_NO3_application(this);
            CropSyst::N_application_soil_observation_mode::Split_application *auto_N_split_appl_op = (CropSyst::N_application_soil_observation_mode::Split_application *)auto_N_split_appl_event->get_operation();
            auto_N_appl_form->bind_to(auto_N_split_appl_op,parameter_file_form);
            edit_event(auto_N_split_appl_event,auto_N_appl_form V4_HELP_URL(HELP_P_mgmt_N_automatic));
            Update();  //not sure if need to update entire form
      }  }
      {  Common_event *auto_clip_event = dynamic_cast<Common_event *>(management->auto_clip_biomass_mode_operations.find_cstr(op_event_ID));
         if (auto_clip_event)
         {  Tauto_clipping_form *clipping_mode_form = new Tauto_clipping_form(this);
            CropSyst::Auto_clip_biomass_mode *clipping_mode =
               dynamic_cast<CropSyst::Auto_clip_biomass_mode *>                  //120501
               (auto_clip_event->get_operation());
            clipping_mode_form->bind_to(clipping_mode,parameter_file_form);
            edit_event(auto_clip_event,clipping_mode_form V4_HELP_URL(HELP_P_mgmt_clip_automatic));
            clipping_auto_checklistbox->Update();
      }  }
      {  Common_event *irrig_event = dynamic_cast<Common_event *>(management->irrigation_operations.find_cstr(op_event_ID));
         if (irrig_event)
         {  TIrrigation_application_form *irrig_appl_form = new TIrrigation_application_form(this);
            CropSyst::Irrigation_operation *irrig_op = (CropSyst::Irrigation_operation *)irrig_event->get_operation();
            irrig_appl_form->bind_to(irrig_op,false,&(irrig_event->contingency_labeled),parameter_file_form);
            edit_event(irrig_event,irrig_appl_form V4_HELP_URL(HELP_P_irrigation_spec));
            irrigation_spec_checklistbox->Update();
      }  }
   }
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::radiogroup_auto_NO3Click(TObject *Sender)
{  // Same as V5
   show_hide_auto_NO3_parameters();
}
//______________________________________________________________________________

