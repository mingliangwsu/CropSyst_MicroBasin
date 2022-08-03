//---------------------------------------------------------------------------

#ifndef form_management_editorH
#define form_management_editorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <FileCtrl.hpp>
#include "cdiroutl.h"
#include <Grids.hpp>
#include <Outline.hpp>
#include <CheckLst.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#ifdef OLD_AUTOCONTROLS
#include "AutoCheckBox.h"
#include "AutoInt16Edit.h"
#include "AutoFloat32EditBar.h"
#include "AutoStringEdit.h"
#include "AutoRadioGroup.h"
#include "AutoContainerTreeView.h"
#include "AutoInt16EditBar.h"
#include "AutoContainerCheckListBox.h"
#include "AutoContainerListBox.h"
#include "AutoFloat32Edit.h"

#else

#endif


//---------------------------------------------------------------------------
// forward declarations
#include "form_management_editor_inc.h"
COMMON_EDITOR_INCLUDES_AND_FORWARD_DECLS
MANAGEMENT_EDITOR_INCLUDES_AND_FORWARD_DECLS
/*101216 moved to form_management_editor_inc
class Management_parameters;
class CropSyst_operation_X;
class Common_event_list;
class Common_event;
class Tparameter_file_form;
*/
//---------------------------------------------------------------------------
class TManagement_editor_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *management_pagecontrol;
   TTabSheet *irrigation_tabsheet;
   TTabSheet *clipping_tabsheet;
   TTabSheet *conservation_tabsheet;
   TTabSheet *tillage_tabsheet;
   TTabSheet *fertilization_tabsheet;
   TLabel *Label7;
   TLabel *Label10;
   TAutoFloat32EditBar *edit_soil_conserve_factor;
   TLabel *Label11;
   TLabel *Label12;
   TAutoRadioGroup *radiogroup_land_treatment;
   TLabel *Label19;
   TPageControl *PageControl2;
   TTabSheet *irrigation_spec_tabsheet;
   TTabSheet *irrigation_auto_tabsheet;
   TLabel *Label3;
   TBitBtn *irrigation_auto_delete_button;
   TAutoContainerCheckListBox *irrigation_auto_checklistbox;
   TLabel *Label2;
   TBitBtn *irrigation_spec_add_button;
   TBitBtn *irrigation_spec_delete_button;
   TPageControl *PageControl3;
   TLabel *Label18;
   TPageControl *PageControl4;
   TTabSheet *clipping_spec_tabsheet;
   TTabSheet *clipping_auto_tabsheet;
   TLabel *Label5;
   TBitBtn *clipping_auto_add_button;
   TBitBtn *clipping_auto_delete_button;
   TAutoContainerCheckListBox *clipping_auto_checklistbox;
   TLabel *Label4;
   TBitBtn *clipping_spec_add_button;
   TBitBtn *clipping_spec_delete_button;
   TAutoContainerCheckListBox *clipping_spec_checklistbox;
   TTabSheet *residue_tabsheet;
   TLabel *Label9;
   TBitBtn *residue_spec_add_button;
   TBitBtn *residue_spec_delete_button;
   TAutoContainerCheckListBox *residue_spec_checklistbox;
   TLabel *Label8;
   TBitBtn *tillage_spec_add_button;
   TBitBtn *tillage_spec_delete_button;
   TAutoContainerCheckListBox *tillage_spec_checklistbox;
   TBitBtn *irrigation_auto_add_button;
   TAutoContainerCheckListBox *irrigation_spec_checklistbox;
   TImage *Image3;
   TImage *Image4;
   TImage *Image5;
   TImage *Image6;
   TImage *Image7;
   TImage *Image8;
   TImage *Image10;
   TAutoCheckBox *checkbox_crop_management;
   TImage *Image9;
   TRadioGroup *radiogroup_contouring_factor;
   TRadioGroup *radiogroup_strip_cropping_factor;
   TRadioGroup *radiogroup_terrace_sedimentation_factor;
   TLabel *Label15;
   TAutoCheckBox *checkbox_CANMS;
   TTabSheet *Sp;
   TTabSheet *TabSheet2;
   TPageControl *pagecontrol_seasonal_N_appl;
   TTabSheet *tabsheet_sampling_date;
   TTabSheet *tabsheet_sampling_and_appl;
   TTabSheet *tabsheet_auto_N_appl_events;
   TAutoRadioGroup *radiogroup_auto_NO3;
   TAutoFloat32EditBar *edit_target_yield_N_uptake_kg_ha;
   TAutoFloat32EditBar *edit_critical_soil_NO3;
   TLabel *Label14;
   TAutoFloat32EditBar *edit_sampling_depth;
   TAutoFloat32EditBar *edit_fert_use_eff;
   TLabel *sampling_prior_sowing_note;
   TLabel *sampling_prior_appls_note;
   TLabel *NO3_appl_at_planting_note;
   TBitBtn *button_auto_NO3_appl_add;
   TBitBtn *button_auto_NO3_appl_delete;
   TAutoContainerListBox *listbox_auto_NO3_split;
   TAutoInt16Edit *edit_auto_NO3_split;
   TLabel *Label13;
   TLabel *Label1;
   TLabel *Label20;
   TImage *Image2;
   TPageControl *PageControl5;
   TTabSheet *TabSheet6;
   TTabSheet *tabsheet_organic_nitrogen_deprecated;
   TImage *Image11;
   TLabel *Label16;
   TBitBtn *N_inorganic_add_button;
   TBitBtn *N_inorganic_delete_button;
   TAutoContainerCheckListBox *checklistbox_N_inorganic;
   TImage *Image1;
   TLabel *Label17;
   TBitBtn *N_organic_add_button;
   TBitBtn *N_organic_delete_button;
   TAutoContainerCheckListBox *N_organic_checklistbox;
   TTabSheet *TabSheet1;
   TAutoCheckBox *checkbox_auto_N;
   TTabSheet *tabsheet_org_N_applications;
   TImage *Image12;
   TLabel *Label6;
   TBitBtn *button_organic_matter_add;
   TBitBtn *button_organic_matter_delete;
   TAutoContainerCheckListBox *checklistbox_organic_matter_appl;
   TTabSheet *tabsheet_LCA;
   TLabel *Label21;
   TGroupBox *GroupBox1;
   TPanel *panel_seasonal_carbon_footprint;
   TPanel *panel_seasonal_irrigation_carbon_footprint;
   TAutoFloat32Edit *edit_seasonal_carbon_footprint;
   TAutoFloat32Edit *edit_seasonal_irrigation_carbon_footprint;
   TLabel *Label22;
   TLabel *Label23;
   TPanel *Panel1;
   TLabel *Label24;
   TAutoFloat32Edit *edit_irrigation_application_carbon_footprint;
   TAutoFloat32EditBar *edit_estimated_mineralization;
   void __fastcall add_irrigation_appl_button_onclick(TObject *Sender);
   void __fastcall add_irrigation_mode_button_onclick(TObject *Sender);
   void __fastcall add_clipping_event_button_onclick(TObject *Sender);
   void __fastcall add_clipping_mode_button_onclick(TObject *Sender);
   void __fastcall add_tillage_event_button_onclick(TObject *Sender);
   void __fastcall add_residue_event_button_onclick(TObject *Sender);
   void __fastcall irrigation_spec_delete_button_onclick(TObject *Sender);
   void __fastcall irrigation_auto_delete_buttonClick(TObject *Sender);
   void __fastcall clipping_spec_delete_button_onclick(TObject *Sender);
   void __fastcall clipping_auto_delete_button_onclick(TObject *Sender);
   void __fastcall tillage_spec_delete_button_onclick(TObject *Sender);
   void __fastcall residue_spec_delete_button_onclick(TObject *Sender);
   void __fastcall N_inorganic_delete_button_onclick(TObject *Sender);
   void __fastcall N_organic_delete_button_onclick(TObject *Sender);
   void __fastcall irrigation_spec_checklistbox_ondblclick(TObject *Sender);
   void __fastcall N_organic_add_button_onclick(TObject *Sender);
   void __fastcall N_inorganic_add_button_onclick(TObject *Sender);
   void __fastcall irrigation_auto_checklistbox_ondblclick(TObject *Sender);
   void __fastcall checklistbox_N_inorganic_ondblclick(TObject *Sender);
   void __fastcall N_organic_checklistbox_ondblclick(TObject *Sender);
   void __fastcall clipping_spec_checklistbox_ondblclick(TObject *Sender);
   void __fastcall clipping_auto_checklistbox_dblclick(TObject *Sender);
   void __fastcall tillage_spec_checklistbox_dblclick(TObject *Sender);
   void __fastcall residue_spec_checklistbox_ondblclick(TObject *Sender);

   void __fastcall show_hide_controls(TObject *Sender);
   void __fastcall calc_soil_conserve_factor(TObject *Sender);
   void __fastcall button_auto_NO3_appl_add_onclick(TObject *Sender);
   void __fastcall auto_NO3_appl_delete_button_onclick(TObject *Sender);
   void __fastcall auto_NO3_split_listbox_ondblclick(TObject *Sender);
   void __fastcall radiogroup_auto_NO3Click(TObject *Sender);
   void __fastcall button_organic_matter_addClick(TObject *Sender);
   void __fastcall checklistbox_organic_matter_applDblClick(TObject *Sender);
   void __fastcall button_organic_matter_deleteClick(TObject *Sender);

private:	// User declarations
   TManagement_editor_form_USER_DECLARATIONS
/*101216 moved to TManagement_editor_form_USER_DECLARATIONS
   Management_parameters      *management;   // now owned by calling program
   Tparameter_file_form       *parameter_file_form;
   int16 auto_NO3_split_total;
*/

//   Tevent_editor_form *schedule_form;                                            //120625

   Tsync_form *sampling_date_form;                                               //120625
      //120625  Rename to N_sampling_event_form

   void __fastcall   update_sampling_date_button();
private:	// User methods
//moved to    TModalResult edit_event(Common_event *event,TForm *op_form,const char *help_HTML_filename);
public:		// User declarations
   __fastcall TManagement_editor_form(TComponent* Owner);
/*101216 moved to TManagement_editor_form_CONSTRUCTOR_INITIALIZATION
   void __fastcall bind_to(Management_parameters   *_management,Tparameter_file_form      *_parameter_file_form);
   virtual void __fastcall Update();
   void show_hide_auto_NO3_parameters();
   TModalResult prompt_and_append_event(CropSyst_operation_X *op,TForm *op_form,Common_event_list &event_list,const char *help_HTML_filename);
*/
   void open_operation_event(const char *op_event_ID);
   inline virtual TPageControl *get_main_page_control() const { return management_pagecontrol;};
};
//---------------------------------------------------------------------------
extern PACKAGE TManagement_editor_form *Management_editor_form;
//---------------------------------------------------------------------------
#endif
