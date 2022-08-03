//---------------------------------------------------------------------------

#ifndef form_eventH
#define form_eventH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "AutoContainerListBox.h"
#include "AutoRadioGroup.h"
#include <Buttons.hpp>
#include "AutoBitCheckListBox.h"
#include "AutoInt16Edit.h"
#include <CheckLst.hpp>
#include "AutoDateButton.h"
#include "AutoStringEdit.h"
#include "AutoCheckBox.h"
#include "AutoInt16EditBar.h"
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include "AutoFileEditBar.h"
//---------------------------------------------------------------------------
// Forward declarations
//class CANMS_event;
class Common_event;
class Tsync_form;
//---------------------------------------------------------------------------

class Tevent_editor_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *event_pagecontrol;
   TTabSheet *instructions_tabsheet;
   TTabSheet *start_tabsheet;
   TTabSheet *end_tabsheet;
   TTabSheet *event_repetition_tabsheet;
   TTabSheet *DSS_tabsheet;
   TCheckBox *CheckBox14;
   TCheckBox *CheckBox11;
   TLabel *Label11;
   TLabel *Label12;
   TCheckBox *CheckBox12;
   TCheckBox *CheckBox13;
   TLabel *Label7;
   TEdit *Edit4;
   TLabel *Label9;
   TLabel *Label8;
   TEdit *Edit5;
   TLabel *Label10;
   TLabel *Label20;
   TAutoDateButton *AutoDateButton1;
   TAutoDateButton *AutoDateButton2;
   TAutoDateButton *AutoDateButton3;
   TAutoDateButton *AutoDateButton4;
   TPanel *repetition_panel;
   TAutoRadioGroup *timestep_radiogroup;
   TAutoCheckBox *repeat_checkbox;
   TTabSheet *period_repetition_tabsheet;
   TGroupBox *annual_period_rep_groupbox;
   TPanel *Panel1;
   TPanel *period_repetitions_instructions_panel;
   TCppWebBrowser *event_repetition_webbrowser;
   TCppWebBrowser *period_repetition_instructions_webbrowser;
   TTabSheet *contingency_tabsheet;
   TAutoRadioGroup *contingency_radiogroup;
   TLabel *Label2;
   TLabel *Label3;
   TTabSheet *canms_tabsheet;
   TAutoRadioGroup *canms_options_radiogroup;
   TLabel *canms_note1;
   TLabel *canms_note2;
   TLabel *canms_note3;
   TLabel *can;
   TAutoFileEditBar *CANMS_operation_fileeditbar;
   TGroupBox *group_box_period_repetition_options;
   TAutoInt16EditBar *period_cycle_duration_edit;
   TCheckBox *unlimited_repeat_period_checkbox;
   TAutoInt16EditBar *period_repetitions_edit;
   TGroupBox *GroupBox1;
   TGroupBox *groupbox_max_repetitions;
   TAutoInt16Edit *max_repetitions_edit;
   TAutoCheckBox *unlimited_repetitions_checkbox;
   TPanel *panel_interval;
   TAutoInt16Edit *interval_edit;
   TCppWebBrowser *instructions_webbrowser;
   TGroupBox *seasonal_period_rep_groupbox;
   TLabel *label_rescheduled;
   TPanel *panel_period_repeat;
   TCheckBox *repeat_period_checkbox;
   TBitBtn *repeat_each_growing_season_button;
   void __fastcall repeat_checkbox_onclick(TObject *Sender);
   void __fastcall unlimited_repetitions_checkboxClick(TObject *Sender);
   void __fastcall show_hide_controls(TObject *Sender);

   void __fastcall repeat_each_growing_season_button_onclick(TObject *Sender);
   void __fastcall unlimited_repeat_period_checkbox_onclick(TObject *Sender);
   void __fastcall repeat_period_checkbox_onclick(TObject *Sender);


//   void __fastcall event_pagecontrolChange(TObject *Sender);

private:	// User declarations
   Common_event *event;
   Tsync_form     *start_sync_form;
   Tsync_form     *end_sync_form;
   bool            associated_with_crop;
   bool           unlimited_repetitions;

public:		// User declarations
        __fastcall Tevent_editor_form(TComponent* Owner);
   void __fastcall bind_to
   (Common_event *i_event
   ,bool i_associated_with_crop
   ,bool i_enable_decision_support
   ,bool _show_CANMS_page_for_CropSyst
   );

   void Xshow_hide_controls();
   virtual void __fastcall Update();                                             //120625
};
//---------------------------------------------------------------------------
extern PACKAGE Tevent_editor_form *event_editor_form;
//---------------------------------------------------------------------------
#endif
