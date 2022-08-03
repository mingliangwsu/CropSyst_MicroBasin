#ifndef form_syncH
#define form_syncH
//______________________________________________________________________________
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoDateTimePicker.h"
#include "AutoFloat32EditBar.h"
#include "AutoInt16Edit.h"
#include "AutoRadioGroup.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "AutoInt16EditBar.h"
#include "AutoDateButton.h"
#include "AutoCheckBox.h"
//______________________________________________________________________________
//Forward declarations
//class Synchronization;
#include <common/simulation/synchronization.h>
//______________________________________________________________________________
class Tsync_form : public TForm
{
__published:	// IDE-managed Components
   TTabSheet *relative_to_sow_tabsheet;
   TAutoRadioGroup *relative_year_radiogroup;
   TAutoInt16Edit *relative_year_intedit;
   TTabSheet *normal_phenologic_tabsheet;
   TTabSheet *relative_to_sim_tabsheet;
   TAutoInt16Edit *crop_phen_sync_days_intedit;
   TLabel *phen_sync_days_label;
   TAutoInt16Edit *from_sim_event_days_edit;
   TLabel *Label2;
   TAutoRadioGroup *sim_event_radiogroup;
   TLabel *Label3;
   TTabSheet *fixed_date_tabsheet;
   TLabel *Label4;
   TAutoDateButton *relative_to_sowing_datebutton;
   TAutoDateButton *actual_datebutton;
   TTabSheet *before_planting_tabsheet;
   TLabel *before_planting_note;
   TTabSheet *fruit_tree_phenologic_tabsheet;
   TTabSheet *thermal_time_tabsheet;
   TAutoInt16EditBar *thermal_time_intedit;
   TLabel *Label1;
   TAutoInt16Edit *before_planting_days_intedit;
   TLabel *Label5;
   TAutoInt16Edit *fruit_phen_sync_days_intedit;
   TLabel *Label6;
   TAutoRadioGroup *fruit_phen_sync_radiogroup;
   TAutoRadioGroup *crop_phen_sync_radiogroup;
   TLabel *fixed_date_note;
   TLabel *Label7;
   TAutoCheckBox *normal_crop_phen_reschedule_checkbox;
   TLabel *Label8;
   TAutoCheckBox *fruit_tree_phen_reschedule_checkbox;
   TLabel *Label9;
   TAutoCheckBox *thermal_time_reschedule_checkbox;
   TLabel *Label10;
   TLabel *Label11;
   TLabel *Label12;
   TPageControl *sync_mode_pagecontrol;
   TAutoRadioGroup *fruit_tree_phen_reschedule_radio;
   TAutoRadioGroup *normal_crop_phen_reschedule_radio;
   TAutoRadioGroup *thermal_time_reschedule_radio;
   TLabel *Label13;
   TLabel *Label14;
   void __fastcall relative_year_radiogroup_onclick(TObject *Sender);
   void __fastcall sync_mode_pagecontrol_onchange(TObject *Sender);
   void __fastcall relative_year_intedit_onchange(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall crop_phen_sync_days_intedit_onchange(TObject *Sender);
 private:	// User declarations
   Synchronization  *synchronization;
   int8 /*enumXX*/   relative_year_option;
   int16             relative_year_number;
 public:		// User declarations
   __fastcall Tsync_form(TComponent* Owner);
   void __fastcall bind_to
      (Synchronization *synchronization
      ,nat32            permitted_sync_modes);
   virtual void __fastcall Update();                                             //120625
};
//______________________________________________________________________________
extern PACKAGE Tsync_form *sync_form;
//______________________________________________________________________________
#endif
