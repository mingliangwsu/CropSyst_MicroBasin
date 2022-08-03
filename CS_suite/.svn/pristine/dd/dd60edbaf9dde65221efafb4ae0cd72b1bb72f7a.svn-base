//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "common/simulation/event.h"
#include "form_event.h"
#include "form_sync.h"
#include "CS_suite/application/CS_suite_directory.h"
#include "corn/OS/file_system_engine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoContainerListBox"
#pragma link "AutoRadioGroup"
#pragma link "AutoBitCheckListBox"
#pragma link "AutoInt16Edit"
#pragma link "AutoDateButton"
#pragma link "AutoStringEdit"
#pragma link "AutoCheckBox"
#pragma link "AutoInt16EditBar"
#pragma link "SHDocVw_OCX"
#pragma link "AutoFileEditBar"
#pragma resource "*.dfm"
Tevent_editor_form *event_editor_form;
//---------------------------------------------------------------------------
__fastcall Tevent_editor_form::Tevent_editor_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tevent_editor_form::bind_to
(Common_event *_event
,bool          _associated_with_crop
,bool          _enable_decision_support
,bool          _show_CANMS_page_for_CropSyst
)
{
   associated_with_crop = _associated_with_crop;
   event = _event;
   if (!event->period)
      ShowMessage("Event is missing the period events. Should always have a period in the parameter editor.");

//Crashes for some reason   DSS_tabsheet->TabVisible = enable_decision_support;

   contingency_radiogroup->bind_to(&(event->contingency_labeled),0);

   unlimited_repetitions = event->period->event_repetitions == MAX_REPETITIONS;
   unlimited_repetitions_checkbox->bind_to(&unlimited_repetitions,0);
   max_repetitions_edit->bind_to(&(event->period->event_repetitions),0); // no help yet
   repeat_checkbox->bind_to(&(event->period->repeat_event),0); // no help yet
   interval_edit->bind_to(&(event->period->interval),0); // no help yet
   timestep_radiogroup->bind_to(&(event->period->interval_timestep_labeled),0); // no help yet
   start_sync_form = new Tsync_form(start_tabsheet);
   start_sync_form->Parent = start_tabsheet;
   start_sync_form->Show();
   start_sync_form->Top = 0;
   start_sync_form->Left = 0;
   start_sync_form->Align = alClient;
   start_sync_form->BorderStyle = bsNone;

   uint32 sync_mode_bitmask =  associated_with_crop
   ?
   (  synchronization_mode_bitmask(RELATIVE_TO_SOWING_MODE)
   |  synchronization_mode_bitmask(BEFORE_PLANTING_MODE)
   |  synchronization_mode_bitmask(AFTER_NORMAL_CROP_GROWTH_STAGE_MODE)
   |  synchronization_mode_bitmask(AFTER_FRUIT_TREE_GROWTH_STAGE_MODE)
   |  synchronization_mode_bitmask(THERMAL_TIME_MODE))
   :
   (  synchronization_mode_bitmask(ACTUAL_DATE_MODE)
   |  synchronization_mode_bitmask(RELATIVE_TO_SIMULATION_EVENT_MODE)
   );
   start_sync_form->bind_to(&(event->begin_sync),sync_mode_bitmask);
   if (event->period) // this conditions should always be true                   //030606
   {
      end_sync_form = new Tsync_form(end_tabsheet);
      end_sync_form->Parent = end_tabsheet;
      end_sync_form->Show();
      end_sync_form->Top = 0;
      end_sync_form->Left = 0;
      end_sync_form->Align = alClient;
      end_sync_form->BorderStyle = bsNone;
      end_sync_form->bind_to(&(event->period->end_sync),sync_mode_bitmask);

      unlimited_repeat_period_checkbox->Checked = event->period->period_repetitions == MAX_REPETITIONS;
      period_repetitions_edit->bind_to(&(event->period->period_repetitions),0); // no help yet
      repeat_period_checkbox->Checked = event->period->period_repetitions > 0;
      period_cycle_duration_edit->bind_to(&(event->period->period_cycle_years),0);
   }
   event_pagecontrol->ActivePage = instructions_tabsheet;
// CORN::OS::File_name_concrete parameters_event_schedule_htm; CS::Suite_directory->find_file_name("schedule.htm",parameters_event_schedule_htm);
   CORN::OS::File_name *parameters_event_schedule_htm                            //150403
      = CORN::OS::file_system_engine.find_file_name(L"schedule.htm",CS::Suite_directory->common(),true); //150412
   if (parameters_event_schedule_htm)                                            //150403
   {  instructions_webbrowser->Navigate(WideString(parameters_event_schedule_htm->c_str() ));
      delete parameters_event_schedule_htm;
   }
//150403    CORN::OS::File_name_concrete  parameters_event_repetition_htm; CS::Suite_directory->find_file_name("repetition.htm",parameters_event_repetition_htm);
   CORN::OS::File_name *parameters_event_repetition_htm
      = CORN::OS::file_system_engine.find_file_name(L"repetition.htm",CS::Suite_directory->common(),true); //150412
   if (parameters_event_repetition_htm)
   {
      event_repetition_webbrowser->Navigate(WideString(parameters_event_repetition_htm->c_str()));
      delete parameters_event_repetition_htm;
   }
//150403   CORN::File_name parameters_event_period_htm; CS::Suite_directory->find_file_name("period.htm",parameters_event_period_htm);
   CORN::OS::File_name *parameters_event_period_htm
      = CORN::OS::file_system_engine.find_file_name(L"period.htm",CS::Suite_directory->common(),true); //150412
   if (parameters_event_period_htm)
   {
      period_repetition_instructions_webbrowser ->Navigate(WideString(parameters_event_period_htm->c_str()));
      delete parameters_event_period_htm;
   }
   canms_options_radiogroup->bind_to(&(event->enable_for_model_labeled),0); // no help yet
#ifdef DISABLED
I don't yet have editor for filename
   CANMS_operation_fileeditbar->bind_to(&(event->operation_filename),0); // No help yet
#endif
   DragAcceptFiles(CANMS_operation_fileeditbar->Handle,true);
   canms_tabsheet->TabVisible = _show_CANMS_page_for_CropSyst;

   show_hide_controls(0);
};

//---------------------------------------------------------------------------
void __fastcall Tevent_editor_form::show_hide_controls(TObject *Sender)
{
   bool is_period = event->is_period(false);
   end_tabsheet->TabVisible = is_period;
   CANMS_operation_fileeditbar->Visible =  event->enable_for_model_labeled.get() == SECONDARY_OVER_PRIMARY;
   // Operation modes are not repeatable the simulation will check
   // each day during the event period to see how the operation will be applied
   bool repetitions_visible = !event->operation_is_mode();
   event_repetition_tabsheet->TabVisible = repetitions_visible;
   repetition_panel->Visible = event->period->repeat_event;
   max_repetitions_edit->Visible = !unlimited_repetitions; // event->period->event_repetitions != MAX_REPETITIONS;
   period_repetition_tabsheet->TabVisible = is_period;
   // If there are no repetitions, we can hide the end sheet.
   start_tabsheet->Caption = is_period
   ? "Period begin"
   : "Single event";

   // Period repetitions page
   repeat_each_growing_season_button->Visible = associated_with_crop;

   // Repeat period annually groupbox
   annual_period_rep_groupbox->Visible = !associated_with_crop;
   bool event_repeatable_period = event->repeatable_period();
   repeat_period_checkbox->Enabled = event_repeatable_period;
   group_box_period_repetition_options->Visible = event_repeatable_period && (event->period->period_repetitions > 0);
   period_repetitions_edit->Visible = event_repeatable_period && !unlimited_repeat_period_checkbox->Checked;
   if (event->period_synchronized_to_growing_season() &&
         event->period_repeated_each_season())
      period_repetitions_edit->Enabled = false;
   period_cycle_duration_edit->Visible = event_repeatable_period && !associated_with_crop;
   period_cycle_duration_edit->Enabled = !associated_with_crop;
   CORN::OS::File_name *event_period_rep_instructions_file
      = CORN::OS::file_system_engine.find_file_name(L"period.htm",CS::Suite_directory->common(),true); //150412
      //150412 = CS::Suite_directory->common().find_file_name(L"period.htm",true);
   // Errors display has priority
   if (event_period_rep_instructions_file)
   {
   std::wstring event_period_rep_instructions_with_link(event_period_rep_instructions_file->w_str());
   if (!event->repeatable_period())
      event_period_rep_instructions_with_link.append(L"#repeat_simulation_synced_period");
   // the following are context sensitive instructions.
   else if (event->period_synchronized_to_actual_date())
      event_period_rep_instructions_with_link.append(L"#fixed_date_period_rep");
   else if (associated_with_crop)
      event_period_rep_instructions_with_link.append(L"#rot_mgmt_period_rep");

//temp disabled   period_repetition_instructions_webbrowser->Navigate(WideString(event_period_rep_instructions_with_link.c_str()));
   };
};
//---------------------------------------------------------------------------
void __fastcall Tevent_editor_form::repeat_checkbox_onclick(TObject *Sender)
{
  show_hide_controls(Sender);
   max_repetitions_edit->Update();
}
//---------------------------------------------------------------------------
void __fastcall Tevent_editor_form::unlimited_repetitions_checkboxClick(TObject *Sender)
{
   if (unlimited_repetitions)
      event->period->event_repetitions = MAX_REPETITIONS;
   max_repetitions_edit->Update();
   max_repetitions_edit->Visible = !unlimited_repetitions; // (unlimited_repetitions_checkbox->State == cbUnchecked);
}
//---------------------------------------------------------------------------
void __fastcall Tevent_editor_form::repeat_each_growing_season_button_onclick(TObject *Sender)
{
   if (event->period)
   {  //          set the begin and end period dates to repeat each season
      event->begin_sync.reschedule_mode_labeled.set(ONE_RESCHEDULE);
      event->period->end_sync.reschedule_mode_labeled.set(ONE_RESCHEDULE);
      label_rescheduled->Caption =
      "The phenology (crop or fruit tree) or thermal time options to reschedule"
      " this event in successive seasons have been set to schedule once per season."
      "To undo this selection click /Period start\ and /Period end\ select the desired reschedule option.";
      label_rescheduled->Visible = true;
   };
   show_hide_controls(Sender);
}
//---------------------------------------------------------------------------
void __fastcall Tevent_editor_form::unlimited_repeat_period_checkbox_onclick(TObject *Sender)
{
   event->period->period_repetitions = (unlimited_repeat_period_checkbox->Checked)
   ? MAX_REPETITIONS : 1;
   period_repetitions_edit->Update();
   show_hide_controls(Sender);
}
//---------------------------------------------------------------------------
void __fastcall Tevent_editor_form::repeat_period_checkbox_onclick(TObject *Sender)
{  if (event->period)
   {
      if (!repeat_period_checkbox->Checked)
         event->period->period_repetitions = 0;
      if (event->period->period_repetitions > 0)
         unlimited_repeat_period_checkbox->Checked =   event->period->period_repetitions == MAX_REPETITIONS;
      period_repetitions_edit->Update();
      show_hide_controls(Sender);
   };
}
//---------------------------------------------------------------------------
void __fastcall Tevent_editor_form::Update()
{
   start_sync_form->Update();

   event_pagecontrol->Update();
   start_tabsheet->Update();
   end_tabsheet->Update();
   event_repetition_tabsheet->Update();
   DSS_tabsheet->Update();
   CheckBox14->Update();
   CheckBox11->Update();
   CheckBox12->Update();
   CheckBox13->Update();
   Edit4->Update();
   Edit5->Update();
   AutoDateButton1->Update();
   AutoDateButton2->Update();
   AutoDateButton3->Update();
   AutoDateButton4->Update();
   timestep_radiogroup->Update();
   repeat_checkbox->Update();
//   TTabSheet *period_repetition_tabsheet->Update();
//   TGroupBox *annual_period_rep_groupbox;
   //TPanel *Panel1;
   //TPanel *period_repetitions_instructions_panel;
   //TCppWebBrowser *event_repetition_webbrowser;
   //TCppWebBrowser *period_repetition_instructions_webbrowser;
   contingency_tabsheet->Update();
   contingency_radiogroup->Update();
   //canms_tabsheet->Update();
   canms_options_radiogroup->Update();
   CANMS_operation_fileeditbar->Update();
   //group_box_period_repetition_options;
   period_cycle_duration_edit->Update();
   unlimited_repeat_period_checkbox->Update();
   period_repetitions_edit->Update();
   //TGroupBox *GroupBox1;
   //TGroupBox *groupbox_max_repetitions;
   max_repetitions_edit->Update();
   unlimited_repetitions_checkbox->Update();
   //panel_interval;
   interval_edit->Update();
   //instructions_webbrowser;
   seasonal_period_rep_groupbox->Update();
   //label_rescheduled;
   //panel_period_repeat;
   repeat_period_checkbox->Update();
   //repeat_each_growing_season_button;
   show_hide_controls(0);
};
//_2012-06-25__________________________________________________________Update__/
