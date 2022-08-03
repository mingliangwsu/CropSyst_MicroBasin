#include <vcl.h>
#pragma hdrstop
#include "form_sync.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoDateTimePicker"
#pragma link "AutoFloat32EditBar"
#pragma link "AutoInt16Edit"
#pragma link "AutoRadioGroup"
#pragma link "AutoInt16EditBar"
#pragma link "AutoDateButton"
#pragma link "AutoCheckBox"
#pragma resource "*.dfm"
Tsync_form *sync_form;
//______________________________________________________________________________
__fastcall Tsync_form::Tsync_form(TComponent* Owner)
   : TForm(Owner)
   ,synchronization(0)
{ }
//______________________________________________________________________________
void __fastcall Tsync_form::bind_to
(Synchronization *i_synchronization
,uint32 permitted_sync_modes
)
{  synchronization = i_synchronization;
   // Active page must be set first so that
   sync_mode_pagecontrol->ActivePageIndex = (int)synchronization->get_sync_mode(); // sync_mode_labeled.get_int32();

   fixed_date_tabsheet->TabVisible           = (1 << ACTUAL_DATE_MODE)                    &  permitted_sync_modes;
   relative_to_sim_tabsheet->TabVisible      = (1 << RELATIVE_TO_SIMULATION_EVENT_MODE)   &  permitted_sync_modes;
   relative_to_sow_tabsheet->TabVisible      = (1 << RELATIVE_TO_SOWING_MODE)             &  permitted_sync_modes;
   before_planting_tabsheet->TabVisible      = (1 << BEFORE_PLANTING_MODE)                &  permitted_sync_modes;
   normal_phenologic_tabsheet->TabVisible    = (1 << AFTER_NORMAL_CROP_GROWTH_STAGE_MODE) &  permitted_sync_modes;
   fruit_tree_phenologic_tabsheet->TabVisible= (1 << AFTER_FRUIT_TREE_GROWTH_STAGE_MODE)  &  permitted_sync_modes;
   thermal_time_tabsheet->TabVisible         = (1 << THERMAL_TIME_MODE)                   &  permitted_sync_modes;

   // If the current mode (which may be the default mode) is not
   // a permitted mode, we advance to a permitted mode
   if (!((1 << synchronization->get_sync_mode()) & permitted_sync_modes))
   {  bool sync_mode_accepted = false;
      for (int sync_mode = 0
          ;(sync_mode < SYNC_MODE_COUNT) && (!sync_mode_accepted)
          ;sync_mode++)
      {  sync_mode_accepted = (1 << sync_mode) & permitted_sync_modes;
         if (sync_mode_accepted)
            synchronization->sync_mode_labeled.set(sync_mode);
      }
   }
   relative_to_sowing_datebutton->bind_to(synchronization,"Relative to sowing date",false,0); // no help yet
   int16 sync_year = synchronization->get_year();
   if (sync_year == 0)  relative_year_option = 0;
   if (sync_year == 1)  relative_year_option = 1;
   if (sync_year > 1)   relative_year_option = 2;
   if (sync_year < 0)   relative_year_option = 3;
   relative_year_number = abs(sync_year);
   relative_year_radiogroup->bind_to(&relative_year_option,0);
   relative_year_intedit->bind_to(&relative_year_number,0); // no help yet
   relative_year_intedit->Visible = relative_year_radiogroup->ItemIndex >= 2;

   // cannot bind directly to synchronization->sync because
   // TRadioGroup limits then ItemIndex to available Strings
   // The syncs strings do not include phen sync 0  (no sync) so we need to adjust.
   crop_phen_sync_radiogroup->bind_to(&(synchronization->normal_crop_event_sequence_labeled/*130425 normal_crop_growth_stage_labeled*/),0); // no help yet;
   fruit_phen_sync_radiogroup->bind_to(&(synchronization->fruit_tree_event_sequence_labeled/*130425 fruit_tree_growth_stage_labeled*/),0); // no help yet;

   before_planting_days_intedit->bind_to(&(synchronization->days_offset),0); // no help yet;
   crop_phen_sync_days_intedit->bind_to(&(synchronization->days_offset),0); // no help yet
   fruit_phen_sync_days_intedit->bind_to(&(synchronization->days_offset),0); // no help yet

   thermal_time_intedit->bind_to(&(synchronization->thermal_time),0); // no help yet

   thermal_time_reschedule_radio    ->bind_to(&(synchronization->reschedule_mode_labeled),0); // no help yet
   normal_crop_phen_reschedule_radio->bind_to(&(synchronization->reschedule_mode_labeled),0); // no help yet;
   fruit_tree_phen_reschedule_radio ->bind_to(&(synchronization->reschedule_mode_labeled),0); // no help yet;

   // 060413 The following should be obsolete
//120315   thermal_time_reschedule_checkbox    ->bind_to(&(synchronization->repeat_each_season_obs_060413),0); // no help yet
//120315 normal_crop_phen_reschedule_checkbox->bind_to(&(synchronization->repeat_each_season_obs_060413),0); // no help yet;
//120315   fruit_tree_phen_reschedule_checkbox ->bind_to(&(synchronization->repeat_each_season_obs_060413),0); // no help yet;

   sim_event_radiogroup->bind_to(&(synchronization->simulation_event_labeled),0); // no help yet;
   from_sim_event_days_edit->bind_to(&(synchronization->days_offset),0); // no help yet;

   actual_datebutton->bind_to(synchronization,"Actual specific fixed date",true,0); // no help yet;
}
//______________________________________________________________________________
void __fastcall Tsync_form::relative_year_radiogroup_onclick(
      TObject *Sender)
{  switch (relative_year_radiogroup->ItemIndex)
   {  case 0   : synchronization->set_year(0); break;
      case 1   : synchronization->set_year(1); break;
      case 2   : synchronization->set_year(relative_year_number);  break;
      case 3   : synchronization->set_year(-relative_year_number); break;
   }
   relative_year_intedit->Visible = relative_year_radiogroup->ItemIndex >= 2;
   relative_year_intedit->Update();
   relative_to_sowing_datebutton->Update();
}
//______________________________________________________________________________
void __fastcall Tsync_form::sync_mode_pagecontrol_onchange(TObject *Sender)
{  synchronization->sync_mode_labeled.set_int32(sync_mode_pagecontrol->ActivePageIndex);
   if (synchronization->sync_mode_labeled.get() == RELATIVE_TO_SOWING_MODE)
      synchronization->set_relative(true);
   if (synchronization->sync_mode_labeled.get() == ACTUAL_DATE_MODE)
      synchronization->set_relative(false);
/*080809 NYI
  Claudio would like the "Whenever this phenologic stage is achieved"
  // to be the default for fruit tree mode
   if (synchronization->sync_mode_labeled.get() == AFTER_FRUIT_TREE_GROWTH_STAGE_MODE)
   {
      synchronization->reschedule_mode_labeled

   };
*/

   // 060413 the following are becoming obsolete
//120315   normal_crop_phen_reschedule_checkbox->Checked = synchronization->repeat_each_season_obs_060413;
//120315   fruit_tree_phen_reschedule_checkbox->Checked = synchronization->repeat_each_season_obs_060413;
//120315   thermal_time_reschedule_checkbox->Checked = synchronization->repeat_each_season_obs_060413;

   thermal_time_reschedule_radio    ->Update(); // 060413 bind_to(&(synchronization->reschedule_mode_labeled),0); // no help yet
   normal_crop_phen_reschedule_radio->Update(); // 060413 bind_to(&(synchronization->reschedule_mode_labeled),0); // no help yet;
   fruit_tree_phen_reschedule_radio ->Update(); // 060413 bind_to(&(synchronization->reschedule_mode_labeled),0); // no help yet;

   synchronization->validate();
   before_planting_days_intedit->Update();
   crop_phen_sync_days_intedit->Update();
   fruit_phen_sync_days_intedit->Update();
   from_sim_event_days_edit->Update();
   relative_to_sowing_datebutton->Update();
}
//______________________________________________________________________________
void __fastcall Tsync_form::Update()
{
   sync_mode_pagecontrol->ActivePageIndex = (int)synchronization->get_sync_mode(); 
   //TTabSheet *relative_to_sow_tabsheet;
   relative_year_radiogroup->Update();
   relative_year_intedit->Update();
   //TTabSheet *normal_phenologic_tabsheet;
   //TTabSheet *relative_to_sim_tabsheet;
   crop_phen_sync_days_intedit->Update();
   //TLabel *phen_sync_days_label;
   from_sim_event_days_edit->Update();
   //TLabel *Label2;
   sim_event_radiogroup->Update();
   //TLabel *Label3;
   //TTabSheet *fixed_date_tabsheet;
   //TLabel *Label4;
   relative_to_sowing_datebutton->Update();
   actual_datebutton->Update();
   //TTabSheet *before_planting_tabsheet;
   //TLabel *before_planting_note;
   //TTabSheet *fruit_tree_phenologic_tabsheet;
   //TTabSheet *thermal_time_tabsheet;
   thermal_time_intedit->Update();
   //TLabel *Label1;
   before_planting_days_intedit->Update();
   //TLabel *Label5;
   fruit_phen_sync_days_intedit->Update();
   //TLabel *Label6;
   fruit_phen_sync_radiogroup->Update();
   crop_phen_sync_radiogroup->Update();
   //TLabel *fixed_date_note;
   //TLabel *Label7;
   normal_crop_phen_reschedule_checkbox->Update();
   //TLabel *Label8;
   fruit_tree_phen_reschedule_checkbox->Update();
   //TLabel *Label9;
   thermal_time_reschedule_checkbox->Update();
   //TLabel *Label10;
   //TLabel *Label11;
   //TLabel *Label12;
   sync_mode_pagecontrol->Update();
   fruit_tree_phen_reschedule_radio->Update();
   normal_crop_phen_reschedule_radio->Update();
   thermal_time_reschedule_radio->Update();
   //TLabel *Label13;
   //TLabel *Label14;

};
//_2012-06-25___________________________________________________________Update_/
void __fastcall Tsync_form::relative_year_intedit_onchange(TObject *Sender)
{  int16 sync_year = relative_year_number;
   if (relative_year_option == 3)
      sync_year = -relative_year_number;
   synchronization->set_year(sync_year);
   relative_to_sowing_datebutton->Update();
}
//______________________________________________________________________________
void __fastcall Tsync_form::FormClose(TObject *Sender,TCloseAction &Action)
{  if (sync_mode_pagecontrol->ActivePage == relative_to_sow_tabsheet)
   {  int sync_year = relative_year_number;
      switch (relative_year_option)
      {  case 0 : case 1 : relative_year_number =  relative_year_option;   break;
         // case 2: it is the relative year number; break;
         case 3 :          sync_year = -relative_year_number;              break;
      }
      synchronization->set_year(sync_year);
   }
}
//______________________________________________________________________________
void __fastcall Tsync_form::crop_phen_sync_days_intedit_onchange(TObject *Sender)
{  if (!synchronization) return;
   if (synchronization->days_offset == 0)
       synchronization->days_offset = 1;  // Cannot be zero (event scheduler cannot process)
   crop_phen_sync_days_intedit->Update();
   fruit_phen_sync_days_intedit->Update();
}
//______________________________________________________________________________

