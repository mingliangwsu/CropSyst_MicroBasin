//---------------------------------------------------------------------------

#ifndef form_clippingH
#define form_clippingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoFloat32EditBar.h"
#include "AutoInt16EditBar.h"
#include "AutoRadioGroup.h"
#include <ExtCtrls.hpp>
#include "AutoCheckBox.h"
#include <ComCtrls.hpp>
#include "AutoFloat32Edit.h"
#include "AutoInt16Edit.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
//150402 #include "CropSyst/source/mgmt_param.h"
#include "CropSyst/source/management/management_param_V4.h"

/*
//031014obs class Clipping_operation;
namespace CropSyst
{
   class Harvest_or_clipping_operation;
};
*/
class Tparameter_file_form;
//---------------------------------------------------------------------------
class Tclipping_form : public TForm
{
__published:	// IDE-managed Components
   TScrollBox *scrollbox_removal_mode_and_constraints;
   TPanel *panel_NRCS_field_op;
   TSpeedButton *SpeedButton1;
   TComboBox *NRCS_harvest_field_op_number_combbox;
   TAutoRadioGroup *harvest_amount_mode_radiogroup;
   TPanel *panel_clipping_automatic_modes;
   TGroupBox *groupbox_remove_fixed_amount;
   TAutoFloat32EditBar *remove_fixed_amount_edit;
   TAutoCheckBox *accept_less_checkbox;
   TGroupBox *groupbox_retention;
   TAutoFloat32EditBar *reserve_biomass_editbar;
   TLabel *Label9;
   TAutoFloat32EditBar *min_retain_GAI_edit;
   TLabel *notea;
   TLabel *Label16;
   TLabel *remove_fixed_mode_note;
   TLabel *remove_percentage_note;
   TGroupBox *groupbox_termination;
   TGroupBox *groupbox_biomass_disposition;
   TAutoCheckBox *terminate_crop_checkbox;
   TLabel *terminate_crop_label;
   TPageControl *harvest_mode_page_control;
   TTabSheet *primary_yield_tabsheet;
   TLabel *Label2;
   TLabel *Label1;
   TLabel *Label14;
   TLabel *Label15;
   TBitBtn *suggested_harvest_button;
   TTabSheet *clipping_tabsheet;
   TLabel *Label3;
   TLabel *Label5;
   TLabel *Label12;
   TLabel *Label13;
   TLabel *clipping_fate_label;
   TBitBtn *suggest_clipping_button;
   TTabSheet *last_clipping_tabsheet;
   TLabel *Label4;
   TLabel *Label6;
   TLabel *last_clipping_fate_label;
   TBitBtn *suggest_last_clipping_button;
   TTabSheet *grazing_tabsheet;
   TLabel *Label7;
   TLabel *Label18;
   TAutoInt16EditBar *remove_for_grazing_edit;
   TGroupBox *grazing_groupbox;
   TAutoInt16EditBar *grazing_OM_editbar;
   TAutoInt16EditBar *grazing_NH3_editbar;
   TAutoInt16EditBar *biomass_returned_as_manure_editbar;
   TBitBtn *suggest_grazing_button;
   TTabSheet *defoliation_tabsheet;
   TLabel *Label8;
   TLabel *Label19;
   TBitBtn *suggest_defoliation_button;
   TMemo *select_one_mode_memo;
   TGroupBox *biomatter_fate_groupbox;
   TScrollBox *ScrollBox1;
   TAutoInt16EditBar *remove_for_use_edit;
   TAutoInt16EditBar *remain_as_residue_edit;
   TAutoInt16EditBar *remove_for_disposal_edit;
   TAutoInt16EditBar *remain_as_standing_dead_edit;
   TAutoInt16EditBar *remain_as_standing_live_edit;
   TPanel *panel_biomass_fate_terminate_crop;
   TLabel *Label11;
   TAutoInt16Edit *percent_total_out;
   TGroupBox *groupbox_clipping_required_conditions;
   TAutoFloat32EditBar *min_LAI_required_edit;
   TAutoFloat32EditBar *min_biomass_required_edit;
//050825obs    void __fastcall clipping_fate_radiogroupClick(TObject *Sender);
   void __fastcall grazing_OM_editbar_onexit(TObject *Sender);
   void __fastcall grazing_NH3_editbar_onexit(TObject *Sender);
   void __fastcall terminate_crop_checkboxClick(TObject *Sender);
   void __fastcall show_hide_controls(TObject *Sender);
   void __fastcall harvest_mode_onchange(TObject *Sender);
   void __fastcall update_total_percent(TObject *Sender);
   void __fastcall suggested_harvest_buttonClick(TObject *Sender);
   void __fastcall suggest_clipping_buttonClick(TObject *Sender);
   void __fastcall suggest_last_clipping_buttonClick(TObject *Sender);
   void __fastcall suggest_grazing_buttonClick(TObject *Sender);
   void __fastcall suggest_defoliation_buttonClick(TObject *Sender);
   void __fastcall harvest_amount_mode_radiogroup_onclick(TObject *Sender);
   void __fastcall obsolete_goto_biomass_fate_button_onclick(TObject *Sender);
   void __fastcall NRCS_harvest_field_op_number_combboxChange(
          TObject *Sender);
   void __fastcall button_NRCS_helpClick(TObject *Sender);

private:	// User declarations
   CropSyst::Harvest_or_clipping_operation  *clipping_op;
   int16    percents_total;
   bool     after_first_show_hide_controls; // this prevents the biomass fates message from being shown until after the user makes a change
   Tparameter_file_form       *parameter_file_form;
public:		// User declarations
   __fastcall Tclipping_form(TComponent* Owner);
   void __fastcall bind_to
      (CropSyst::
         //150413 Harvest_or_clipping_operation
         Harvest_or_clipping_operation//_class
         *_clipping_op

      ,Tparameter_file_form          *_parameter_file_form
      ,bool                           _automatic_clipping
      );
private:
   void __fastcall update_percents(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE Tclipping_form *clipping_form;
//---------------------------------------------------------------------------
#endif
