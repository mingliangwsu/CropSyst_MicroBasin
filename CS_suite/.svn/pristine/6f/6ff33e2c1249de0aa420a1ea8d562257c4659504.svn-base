// ---------------------------------------------------------------------------

#ifndef form_management_editorH
#define form_management_editorH
#include "RNAutoCheckBox.h"
#include "RNAutoContainerListBox.h"
#include "RNAutoIntegerEdit.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoRadioGroup.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <StdCtrls.hpp>

// ---------------------------------------------------------------------------
/*
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvPanel.hpp"
#include "RNAutoCheckBox.h"
#include "RNAutoRadioGroup.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "RNAutoParameterEditBar.h"
#include <jpeg.hpp>

// ---------------------------------------------------------------------------
#include "EasyListview.hpp"
#include "MPCommonObjects.hpp"
#include "RNAutoContainerCheckListBox.h"
#include "RNAutoIntegerEdit.h"
#include "RNAutoContainerListBox.h"
#include <ImgList.hpp>
//class Management_parameters;
//class Tparameter_file_form;

*/
#include "form_management_editor_inc.h"
#include <ImgList.hpp>
#include "AdvListV.hpp"
#include <CategoryButtons.hpp>
#include <ActnList.hpp>
#include <ButtonGroup.hpp>
MANAGEMENT_EDITOR_INCLUDES_AND_FORWARD_DECLS

class TManagement_editor_form : public TForm
{
__published: // IDE-managed Components
   TPanel *panel_mode;
   TRNAutoCheckBox *checkbox_crop_management;
   TRNAutoCheckBox *checkbox_CANMS;
   TPageControl *pagecontrol_management;
   TTabSheet *TabSheet1;
   TTabSheet *TabSheet2;
   TTabSheet *TabSheet3;
   TPanel *panel_auto_N_top;
   TRNAutoRadioGroup *radiogroup_auto_NO3;
   TRNAutoRadioGroup *radiogroup_land_treatment;
   TRadioGroup *radiogroup_contouring_factor;
   TRadioGroup *radiogroup_strip_cropping_factor;
   TRadioGroup *radiogroup_terrace_sedimentation_factor;
   TLabel *Label18;
   TPanel *panel_operation_list;
   TPanel *panel_operation_list_edit;
   TBitBtn *button_operation_delete;
   TPageControl *pagecontrol_seasonal_N_appl;
   TTabSheet *tabsheet_sampling_date;
   TTabSheet *tabsheet_sampling_and_appl;
   TTabSheet *tabsheet_auto_N_appl_events;
   TLabel *sampling_prior_sowing_note;
   TLabel *Label14;
   TLabel *sampling_prior_appls_note;
   TRNAutoParameterEditBar *edit_target_yield_N_uptake_kg_ha;
   TRNAutoParameterEditBar *edit_sampling_depth;
   TRNAutoParameterEditBar *edit_fert_use_eff;
   TRNAutoParameterEditBar *edit_soil_conserve_factor;
   TRNAutoCheckBox *checkbox_auto_N;
   TLabel *Label1;
   TPanel *panel_split_N_list;
   TPanel *panel_split_N_list_edit;
   TBitBtn *button_auto_NO3_appl_delete;
   TBitBtn *button_auto_NO3_appl_add;
   TRNAutoContainerListBox *listbox_auto_NO3_split;
   TPanel *panel_N_auto_NO3_split;
   TRNAutoIntegerEdit *edit_auto_NO3_split;
   TComboBoxEx *combobox_add_operation;
   TImageList *imagelist_operations_48x24;
   TAdvListView *listview_operations;
   TRNAutoParameterEditBar *edit_estimated_mineralization;
   TImage *Image1;
   TButtonGroup *buttongroup_add_operation_event;
   TActionList *add_operation_event;
   TAction *action_add_clipping_automatic;
   TAction *action_add_harvest_specific;
   TAction *action_add_irrigation_specific;
   TAction *action_add_irrigation_automatic;
   TAction *action_add_N_inorganic;
   TAction *action_add_biomatter;
   TAction *action_add_tillage;
   TAction *action_add_residue;
   void __fastcall show_hide_controls(TObject *Sender);
   void __fastcall radiogroup_auto_NO3Click(TObject *Sender);
   void __fastcall calc_soil_conserve_factor(TObject *Sender);
   void __fastcall button_auto_NO3_appl_addClick(TObject *Sender);
   void __fastcall button_auto_NO3_appl_deleteClick(TObject *Sender);
   void __fastcall listbox_auto_NO3_splitDblClick(TObject *Sender);
   void __fastcall combobox_add_operationChange(TObject *Sender);
   void __fastcall button_operation_deleteClick(TObject *Sender);
   void __fastcall listview_operationsCheckboxClick(TObject *Sender, int iItem, bool State);
   void __fastcall listview_operationsDblClick(TObject *Sender);
   void __fastcall listview_operationsDeletion(TObject *Sender, TListItem *Item);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall action_add_clipping_automaticExecute(TObject *Sender);
   void __fastcall action_add_harvest_specificExecute(TObject *Sender);
   void __fastcall action_add_irrigation_specificExecute(TObject *Sender);
   void __fastcall action_add_irrigation_automaticExecute(TObject *Sender);
   void __fastcall action_add_N_inorganicExecute(TObject *Sender);
   void __fastcall action_add_biomatterExecute(TObject *Sender);
   void __fastcall action_add_tillageExecute(TObject *Sender);
   void __fastcall action_add_residueExecute(TObject *Sender);
public: // User declarations
   __fastcall TManagement_editor_form(TComponent* Owner);
   inline virtual TPageControl *get_main_page_control() const { return pagecontrol_management;};
public:
   bool add_event_to_listview_operations(Common_event *added_event);
   nat16 refill_operations_listview();                                           //170704
   nat16 refill_operations(const CORN::Unidirectional_list &operations_events);  //170704

   TManagement_editor_form_USER_DECLARATIONS
   /*
public:
   Management_parameters      *management;
   Tparameter_file_form       *parameter_file_form;
   void __fastcall bind_to(Management_parameters   *_management,Tparameter_file_form      *_parameter_file_form);
   void __fastcall bind_to_V4_and_V5(Management_parameters   *_management,Tparameter_file_form      *_parameter_file_form);
   virtual void __fastcall Update();
   void show_hide_auto_NO3_parameters();
   void Update_VCL_common();
   */
};
//---------------------------------------------------------------------------
extern PACKAGE TManagement_editor_form *Management_editor_form;
//---------------------------------------------------------------------------
#endif
