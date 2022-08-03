//---------------------------------------------------------------------------

#ifndef form_planting_eventH
#define form_planting_eventH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvEdBtn.hpp"
#include "AdvEdit.hpp"
#include "AdvFileNameEdit.hpp"
#include "RNAutoDateButton.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoRadioGroup.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

namespace CropSyst
{  class Sowing_operation;
   class Sowing_event;
}
//needed? class Tparameter_file_form;
//---------------------------------------------------------------------------
class Tplanting_event_form : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *groupbox_planting;
   TGroupBox *groupbox_delay_conditions;
   TGroupBox *groupbox_seeding;
   TPanel *panel_planting_date;
   TRNAutoDateButton *planting_date_button;
   TRNAutoRadioGroup *radiogroup_mode;
   TAdvFileNameEdit *fileedit_crop;
   TAdvFileNameEdit *fileedit_management;
   TGroupBox *groupbox_moisture;
   TGroupBox *groupbox_temperature;
   TGroupBox *groupbox_delay_precipitation;
   TGroupBox *groupbox_PAW;
   TRNAutoParameterEditBar *edit_delay_after_precip;
   TRNAutoParameterEditBar *edit_appreciable_precip;
   TRNAutoParameterEditBar *edit_min_required_PAW;
   TRNAutoParameterEditBar *edit_max_required_PAW;
   TRNAutoRadioGroup *radiogroup_temperature_evaluation_mode;
   TRNAutoParameterEditBar *edit_temperature_days;
   TRNAutoParameterEditBar *edit_typical_days_emerge;
   TRNAutoParameterEditBar *edit_seeding_rate;
   TRNAutoParameterEditBar *edit_emergence_rate;
   TRNAutoParameterEditBar *edit_sowing_depth;
   TLabel *label_applicability;
   TPanel *panel_buttons;
   TBitBtn *button_OK;
   TBitBtn *button_cancel;
   TBitBtn *button_help;
   TBitBtn *BitBtn1;
   void __fastcall button_OKClick(TObject *Sender);
   void __fastcall button_helpClick(TObject *Sender);
   void __fastcall fileedit_cropChange(TObject *Sender);
   void __fastcall fileedit_managementChange(TObject *Sender);
   void __fastcall fileedit_cropDblClick(TObject *Sender);
   void __fastcall fileedit_cropLabelClick(TObject *Sender);
   void __fastcall fileedit_managementDblClick(TObject *Sender);
   void __fastcall fileedit_managementLabelClick(TObject *Sender);
   void __fastcall radiogroup_modeClick(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);

private:// User declarations
   CropSyst::Sowing_event *sowing_event;
   CropSyst::Sowing_operation *sowing_op;
public: // User declarations
   __fastcall Tplanting_event_form(TComponent* Owner);
   void bind_to
      (CropSyst::Sowing_event *sowing_event
      ,nat8                    CropSyst_version);                                //180525

};
//---------------------------------------------------------------------------
extern PACKAGE Tplanting_event_form *planting_event_form;
//---------------------------------------------------------------------------
#endif
