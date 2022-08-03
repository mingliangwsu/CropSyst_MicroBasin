//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_management_editor.h"
#include "form_clipping2.h"
#include "form_auto_clipping.h"
#include "form_tillage_residue.h"
#include "form_irrig_appl.h"
#include "form_irrig_mode.h"
#include "form_manure_appl.h"
#include "form_inorganic_N_appl.h"

#include "cs_till.h"

#include "corn/application/program_directory_OS_FS.h"

#pragma link "RNAutoCheckBox"
#pragma link "RNAutoContainerListBox"
#pragma link "RNAutoIntegerEdit"
#pragma link "RNAutoParameterEditBar"
#pragma link "AdvListV"
#pragma link "RNAutoRadioGroup"
//---------------------------------------------------------------------------
/*
#pragma package(smart_init)
#pragma link "AdvPanel"
#pragma link "RNAutoCheckBox"
#pragma link "RNAutoRadioGroup"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoParameterEditBar"
#pragma link "EasyListview"
#pragma link "MPCommonObjects"
#pragma link "RNAutoContainerListBox"
#pragma link "RNAutoIntegerEdit"
#pragma link "RNAutoContainerListBox"
*/
#pragma resource "*.dfm"
TManagement_editor_form *Management_editor_form;
#include "CropSyst/source/management/management_param_V5.h"
//---------------------------------------------------------------------------
__fastcall TManagement_editor_form::TManagement_editor_form(TComponent* Owner)
   : TForm(Owner)
   TManagement_editor_form_CONSTRUCTOR_INITIALIZATION
{
}
//---------------------------------------------------------------------------
//______________________________________________________________________________
void __fastcall TManagement_editor_form::bind_to
(CropSyst::Management_parameters *_management,Tparameter_file_form      *_parameter_file_form)
{
   bind_to_V4_and_V5(_management,_parameter_file_form);
   // Conservation
   edit_soil_conserve_factor  ->bind_to(&(management->p_soil_conservation_factor)/*NYI,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_conserv_soil_practice_factor).c_str()*/);
   radiogroup_land_treatment  ->bind_to(&(management->land_treatment_labeled)/*NYI,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_conserv_land_treatment).c_str()*/);

/* NYI

   edit_target_yield_N_uptake_kg_ha ->bind_to(&(management->N_application_soil_observation_event->p_target_yield_N_uptake_kg_ha)             ,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_N_uptake_target_yield).c_str());
   edit_critical_soil_NO3           ->bind_to(&(management->N_application_soil_observation_event->p_critical_soil_NO3_for_no_response_kg_ha) ,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_N_critical_NO3).c_str());
   edit_sampling_depth                  ->bind_to(&(management->N_application_soil_observation_event->p_soil_N_sampling_depth)                   ,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_N_sampling_depth).c_str());
   edit_fert_use_eff                    ->bind_to(&(management->N_application_soil_observation_event->p_fertilizer_use_efficiency)               ,parameter_file_form->compose_manual_subdirectory_filename(HELP_P_mgmt_N_fert_use_eff).c_str());
*/

   Update();
   show_hide_controls(0);
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::Update()
{
   if (!management) return;                                                      //170620
   Update_VCL_common();
   refill_operations_listview();
};
//______________________________________________________________________________
void __fastcall TManagement_editor_form::radiogroup_auto_NO3Click(TObject *Sender)
{  show_hide_auto_NO3_parameters(); }
//______________________________________________________________________________
void __fastcall TManagement_editor_form::show_hide_controls(TObject *Sender)
{
/*NYI

   In V5 we don't have the tabsheets, instead, remove clipping and residue
   from the add operations combobox

   clipping_tabsheet->TabVisible = management->crop_management;
   residue_tabsheet->TabVisible = management->crop_management;
*/
}
//______________________________________________________________________________
void __fastcall TManagement_editor_form::button_auto_NO3_appl_addClick(TObject *Sender)
{  handle_add_auto_NO3_appl(); }
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::button_auto_NO3_appl_deleteClick(TObject *Sender)
{  listbox_auto_NO3_split->delete_selected(); }
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::listbox_auto_NO3_splitDblClick(TObject *Sender)
{  handle_listbox_auto_NO3_splitDblClick(); }
//---------------------------------------------------------------------------
#define NO_HELP_YET ""
void __fastcall TManagement_editor_form::combobox_add_operationChange(TObject *Sender)
{  if (!management) return;
   Common_event *added_event = 0;
   switch (combobox_add_operation->ItemIndex)
   {
      case 0 : { added_event = add_auto_clipping_mode    (HELP_P_mgmt_clip_automatic);    } break;
      case 1 : { added_event = add_clipping_event        (HELP_P_mgmt_harvest);           } break;
      case 2 : { added_event = add_irrigation_event      (HELP_P_irrigation_spec);        } break;
      case 3 : { added_event = add_auto_irrigation_mode  (HELP_P_mgmt_irrig_automatic);   } break;
      case 4 : { added_event = add_inorganic_event       (HELP_P_mgmt_N_inorg_appl);      } break;
      //170705obscase 5 : { added_event = add_organic_matter_event  (HELP_P_mgmt_N_org_appl);        } break;
      case 5 : { added_event = add_biomatter_event       (HELP_P_mgmt_N_org_appl);        } break;
      case 6 : { added_event = add_tillage_event         (HELP_P_mgmt_tillage_residue);   } break;
      case 7 : { added_event = add_residue_event         (HELP_P_mgmt_tillage_residue);   } break;
   } // switch
   add_event_to_listview_operations(added_event);

}
//---------------------------------------------------------------------------
bool TManagement_editor_form::add_event_to_listview_operations(Common_event *added_event)
{
   if (!added_event) return false;
   TListItem *event_item = listview_operations->Items->Add();
   std::string op_description;
   std::string op_type;
   std::string event_schedule;
   added_event->append_to_string(event_schedule);

   Common_operation *op = (Common_operation  *)added_event->get_operation();     //170619
   if (op)
   {
      if (added_event->operation_type_label.empty())
          added_event->operation_type_label.assign(op->get_type_label());
      op_type = added_event->operation_type_label;
      CropSyst_Op op_type = (CropSyst_Op)op->get_type();

      CropSyst_Op_descriptive_labeled op_type_labeled(op_type);
      switch (op_type)
      {  case CS_OP_NONE : event_item->ImageIndex = 0; break;      // WARNING need other op image
         // Not currently in mgmt file case CS_OP_ROT_SOWING : event_item->ImageIndex = X; break;  // WARNING need other op image
         case CS_OP_MGMT_HARVEST_OR_CLIPPING    : event_item->ImageIndex = 1; break;
         case CS_OP_MGMT_TILLAGE                : event_item->ImageIndex = 6; break;
         case CS_OP_MGMT_RESIDUE                : event_item->ImageIndex = 7; break;
         case CS_OP_MGMT_IRRIGATION             : event_item->ImageIndex = 2; break;
         case CS_OP_MGMT_INORGANIC_NITROGEN     : event_item->ImageIndex = 4; break;
         case CS_OP_MGMT_ORGANIC_NITROGEN       : event_item->ImageIndex = 5; break;
         case CS_OP_MGMT_BIOMATTER_APPLICATION  : event_item->ImageIndex = 5; break; // need unique icon
         case CS_OP_MGMT_CHEMICAL               : event_item->ImageIndex = 5; break; // need unique icon
         case CS_OP_MGMT_AUTO_IRRIGATION        : event_item->ImageIndex = 3; break;
         case CS_OP_MGMT_AUTO_NITRO_OPTIMAL     : event_item->ImageIndex = 5; break; // need unique icon
         case CS_OP_MGMT_AUTO_N                 : event_item->ImageIndex = 5; break; // need unique icon
         case CS_OP_MGMT_AUTO_N_BALANCE_BASED   : event_item->ImageIndex = 6; break; // need unique icon
         #if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION <= 4))
         case CS_OP_MGMT_AUTO_N_LOCAL_CALIBRATION:event_item->ImageIndex = 6; break; // need unique icon
         #endif
         case CS_OP_MGMT_AUTO_N_APPL            : event_item->ImageIndex = 5; break; // need unique icon
         case CS_OP_MGMT_SOIL_N_SAMPLING        : event_item->ImageIndex = 5; break; // need unique icon
         case CS_OP_MGMT_AUTO_CLIP_BIOMASS      : event_item->ImageIndex = 0; break;
         // Not in mgmt file case CS_OP_RECALIBRATION : event_item->ImageIndex = x; break;  // WARNING need other op image
         // Not in mgmt file case CS_OP_PROFILE_PRINT : event_item->ImageIndex = X; break; // WARNING need other op image
         default : event_item->ImageIndex = 0; break; // WARNING need other op image
      } // switch
      op_description = op->description.brief;
      event_item->Caption = UnicodeString(op_type_labeled.get_description());
   }
   event_item->SubItems->Add(UnicodeString(event_schedule.c_str()));
   event_item->SubItems->Add(UnicodeString(op_description.c_str()));
   event_item->Data = added_event;

   event_item->Checked = added_event->is_enabled();

   return true;
}
//_2017-07-01___________________________________________________________________
void __fastcall TManagement_editor_form::button_operation_deleteClick(TObject *Sender)
{
   if (!management) return;
   listview_operations->DeleteSelected();
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::listview_operationsDblClick(TObject *Sender)
{
   TListItem *selected_item = listview_operations->Selected;
   if (selected_item)
   {
      Common_event *event_to_edit = (Common_event *)selected_item->Data;
      if (event_to_edit)
      {
         Common_operation *op = (Common_operation  *)event_to_edit->get_operation();        //170619
         if (op)
         {
            CropSyst_Op op_type = (CropSyst_Op)op->get_type();
            TForm *op_form = 0;
            const char *op_help = 0;

            switch (op_type)
            {
               case CS_OP_MGMT_HARVEST_OR_CLIPPING    :
               {  Tclipping_form *clipping_form = new Tclipping_form(this);
                  CropSyst::Harvest_or_clipping_operation *clipping_op
                  = dynamic_cast<CropSyst::Harvest_or_clipping_operation *>(op);
                  clipping_form->bind_to(clipping_op,parameter_file_form);
                  op_form = clipping_form; op_help = "";
               } break;
               case CS_OP_MGMT_TILLAGE                :
               {
                  Ttillage_residue_form *tillage_form = new Ttillage_residue_form(this);
                  CropSyst::Tillage_operation *tillage_op
                  = dynamic_cast<CropSyst::Tillage_operation *>(op);
                  tillage_form->bind_to
                     (tillage_op
                     ,PRIMARY_TILL|SECONDARY_TILL|PLANTING_TILL|NO_TILL_DRILL
                     ,parameter_file_form);
                  op_form = tillage_form;
                  //op_form = new Ttillage_residue_form(this);
                  op_help = "";
               } break;
               case CS_OP_MGMT_RESIDUE                :
               {
                  Ttillage_residue_form *residue_form = new Ttillage_residue_form(this);
                  CropSyst::Tillage_operation *residue_op
                  = dynamic_cast<CropSyst::Tillage_operation *>(op);
                  residue_form->bind_to(residue_op,RESIDUE,parameter_file_form);
                  op_form = residue_form;
                  //op_form = new Ttillage_residue_form(this);
                  op_help = "";
               } break;
               case CS_OP_MGMT_IRRIGATION             :
               {  TIrrigation_application_form *irrig_spec_form = new TIrrigation_application_form(this);
                  CropSyst::Irrigation_operation *irrig_spec_op
                  = dynamic_cast<CropSyst::Irrigation_operation *>(op);
                  irrig_spec_form->bind_to
                     (irrig_spec_op
                     ,&irrig_spec_op->parameters                                 //170710
                     ,false,0,parameter_file_form);
                     //(irrig_spec_op,parameter_file_form);
                  op_form = irrig_spec_form;
                  //op_form = new TIrrigation_application_form(this);
                  op_help = "";
               } break;
               case CS_OP_MGMT_INORGANIC_NITROGEN     :
               {  Tinorganic_N_application_form *inorganic_N_application_form = new Tinorganic_N_application_form(this);
                  CropSyst::Inorganic_nitrogen_operation *inorg_N_op
                  = dynamic_cast<CropSyst::Inorganic_nitrogen_operation *>(op);
                  inorganic_N_application_form->bind_to(inorg_N_op,parameter_file_form);
                  op_form = inorganic_N_application_form;
                  //op_form = new Tinorganic_N_application_form(this);
                  op_help = "";
               } break;
               #if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
               case CS_OP_MGMT_ORGANIC_NITROGEN       :
               {  Torganic_N_application_form *organic_N_application_form = new Torganic_N_application_form(this);
                  CropSyst::xxxx_operation *XX_op
                  = dynamic_cast<CropSyst::xxxx_operation *>(op);
                  organic_N_application_form->bind_to(XXX_op,parameter_file_form);
                  op_form = organic_N_application_form;
                  //op_form = new Torganic_N_application_form(this);
                  op_help = "";
               } break;
               #endif
               case CS_OP_MGMT_BIOMATTER_APPLICATION  :
               {  Tmanure_application_form *manure_application_form = new Tmanure_application_form(this);
                  CropSyst::Biomatter_application_operation *biomatter_appl_op
                  = dynamic_cast<CropSyst::Biomatter_application_operation *>(op);
                  manure_application_form->bind_to(biomatter_appl_op,parameter_file_form);
                  op_form = manure_application_form;
                  //op_form = new Tmanure_application_form(this);
                  op_help = "";
               } break;
               case CS_OP_MGMT_AUTO_IRRIGATION        :
               {  TIrrigation_application_form *irrigation_application_form = new TIrrigation_application_form(this);
                  CropSyst::Automatic_irrigation_mode *irrig_auto_op
                  = dynamic_cast<CropSyst::Automatic_irrigation_mode *>(op);
                  irrigation_application_form->bind_to
                     (irrig_auto_op
                     ,&(irrig_auto_op->parameters)                               //170710
                     ,true,0,parameter_file_form);
                  op_form = irrigation_application_form;
                  //op_form = new TIrrigation_application_form(this);
                  op_help = "";
               } break;
               case CS_OP_MGMT_AUTO_CLIP_BIOMASS      :
               {  Tauto_clipping_form *auto_clipping_form = new Tauto_clipping_form(this);
                  CropSyst::Auto_clip_biomass_mode *clip_auto_op
                  = dynamic_cast<CropSyst::Auto_clip_biomass_mode *>(op);
                  auto_clipping_form->bind_to(clip_auto_op,parameter_file_form);
                  op_form = auto_clipping_form;
                  //op_form = new Tauto_clipping_form(this);
                  op_help = "";
               } break;
               // op_form is deleted by edit_event
            } // switch op_type
            if (op_form)
            {

               TModalResult result = edit_event(event_to_edit,op_form,op_help);
               //NYN if (result == mrOk)  currently always updating

               std::string event_schedule;
               event_to_edit->append_to_string(event_schedule);
               selected_item->SubItems->Strings[0] = UnicodeString(event_schedule.c_str());
               selected_item->SubItems->Strings[1] = UnicodeString(op->description.brief.c_str());

            } // if op_form

         } // if op

      } // if event_to_edit
   } // if selected
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::listview_operationsCheckboxClick
(TObject *Sender,int iItem, bool State)
{
   //TListItem *checked_item = listview_operations->Selected;
      // I am not sure how to get the checked item
   TListItem *checked_item = listview_operations->Items->Item[iItem];
   Common_event *event_to_edit = (Common_event *)checked_item->Data;
   event_to_edit->checked = State;
   event_to_edit->enabled  = State;
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::listview_operationsDeletion
(TObject *Sender,TListItem *Item)
{
/* not needed now because FormDestroy clears management
   if
   (
        (parameter_file_form->ModalResult == mrOk)
    ||  (parameter_file_form->ModalResult == mrCancel)
   ) return ; // we are closing, the file has already been saved and
      // The Items data is invalid
*/
   if (!management) return;
   Common_event *event_to_delete = (Common_event *)Item->Data;
   management->delete_event(event_to_delete);
}
//---------------------------------------------------------------------------
nat16 TManagement_editor_form::refill_operations_listview()
{  return
     refill_operations(management->irrigation_operations)
   + refill_operations(management->auto_irrigation_mode_operations)
   + refill_operations(management->inorganic_nitrogen_operations)
   + refill_operations(management->biomatter_application_operations)
   + refill_operations(management->tillage_operations)
   + refill_operations(management->residue_operations)
   + refill_operations(management->chemical_operations)
   + refill_operations(management->harvest_or_clipping_operations)
   + refill_operations(management->auto_N_applications)
   + refill_operations(management->auto_clip_biomass_mode_operations);
}
//_2017-07-04___________________________________________________________________
nat16 TManagement_editor_form::refill_operations(const CORN::Unidirectional_list &operations_events)
{  nat16 added = 0;
   FOR_EACH_IN(operation_event,Common_event,operations_events,each_op_event)
   {
      added += add_event_to_listview_operations(operation_event);
   } FOR_EACH_END(each_op_event);
   return added;
}
//_2017-07-04___________________________________________________________________
void __fastcall TManagement_editor_form::FormDestroy(TObject *Sender)
{  management = 0;
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::action_add_clipping_automaticExecute(TObject *Sender)
{  add_event_to_listview_operations(add_auto_clipping_mode    (HELP_P_mgmt_clip_automatic));
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::action_add_harvest_specificExecute(TObject *Sender)
{  add_event_to_listview_operations(add_clipping_event        (HELP_P_mgmt_harvest));
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::action_add_irrigation_specificExecute(TObject *Sender)
{  add_event_to_listview_operations(add_irrigation_event      (HELP_P_irrigation_spec));
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::action_add_irrigation_automaticExecute(TObject *Sender)
{  add_event_to_listview_operations(add_auto_irrigation_mode  (HELP_P_mgmt_irrig_automatic));
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::action_add_N_inorganicExecute(TObject *Sender)
{  add_event_to_listview_operations(add_inorganic_event       (HELP_P_mgmt_N_inorg_appl));
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::action_add_biomatterExecute(TObject *Sender)
{  add_event_to_listview_operations(add_biomatter_event       (HELP_P_mgmt_N_org_appl));
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::action_add_tillageExecute(TObject *Sender)
{  add_event_to_listview_operations(add_tillage_event         (HELP_P_mgmt_tillage_residue));
}
//---------------------------------------------------------------------------
void __fastcall TManagement_editor_form::action_add_residueExecute(TObject *Sender)
{  add_event_to_listview_operations(add_residue_event         (HELP_P_mgmt_tillage_residue));
}
//---------------------------------------------------------------------------

