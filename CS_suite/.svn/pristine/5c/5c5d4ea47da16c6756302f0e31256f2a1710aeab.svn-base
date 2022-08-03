//---------------------------------------------------------------------------

#ifndef form_irrig_applH
#define form_irrig_applH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RNAutoParameterEditBar.h"
#include "RNAutoRadioGroup.h"
#include "RNAutoCheckBox.h"
#include <ComCtrls.hpp>
#include "event_types.h"
//______________________________________________________________________________
namespace CropSyst
{
//170710 class Irrigation_operation;
class Irrigation_operation_class;                                                //170710
class Irrigation_operation_parameters_numeric;                                   //170710
}
class Tparameter_file_form;
//______________________________________________________________________________
class TIrrigation_application_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl1;
   TTabSheet *tabsheet_application_conditions;
   TTabSheet *TabSheet2;
   TPanel *panel_consideration_mode;
   TLabel *Label2;
   TRNAutoRadioGroup *radiogroup_consideration;
   TGroupBox *groupbox_depletion_constraints;
   TRNAutoParameterEditBar *max_allowable_depletion_editbar;
   TRNAutoParameterEditBar *depletion_obs_fract_root_depth_edit;
   TRNAutoParameterEditBar *depletion_observe_depth_editbar;
   TPanel *panel_observation_depth_model;
   TLabel *depletion_contigency_note;
   TRNAutoRadioGroup *radiobutton_depletion_observation_depth_mode;
   TRNAutoParameterEditBar *editbar_leaf_water_potential;
   TPanel *panel_application_mode;
   TLabel *depletion_constraints_note;
   TRNAutoRadioGroup *application_mode_radiogroup;
   TRNAutoParameterEditBar *amount_editbar;
   TPanel *panel_refill;
   TRNAutoParameterEditBar *net_irrigation_mult_editbar;
   TRNAutoParameterEditBar *max_application_editbar;
   TRNAutoParameterEditBar *min_application_editbar;
   TRNAutoParameterEditBar *refill_point_edit_bar;
   TTabSheet *TabSheet3;
   TRNAutoParameterEditBar *salinity_editbar;
   TRNAutoParameterEditBar *edit_NO3_N_conc;
   TRNAutoParameterEditBar *edit_NH4_N_conc;
   TLabel *Label1;
   TLabel *Label3;
   void __fastcall application_mode_radiogroup_onclick(TObject *Sender);
   void __fastcall radiobutton_depletion_observation_depth_modeClick(TObject *Sender);
   void __fastcall radiobutton_depletion_observation_depth_modeExit(TObject *Sender);
   void __fastcall radiogroup_considerationClick(TObject *Sender);
private:	// User declarations
   //170710 CropSyst::Irrigation_operation *irrig_op;
   CropSyst::Irrigation_operation_class *irrig_op;                               //170710
   CropSyst::Irrigation_operation_parameters_numeric *irrig_op_num;        //170710

   bool                  auto_irrig_mode;
//NYI   bool                  *fixed_periodic;
   Contingency_labeled   *contigency_labeled;   // may be 0 (I.e. for auto irrig mode)
public:		// User declarations
   __fastcall TIrrigation_application_form(TComponent* Owner);
      void __fastcall bind_to
         (
          //170710 CropSyst::Irrigation_operation   *_irrig_op
          CropSyst::Irrigation_operation_class *irrig_op                        //170710
         ,CropSyst::Irrigation_operation_parameters_numeric *irrig_op_num        //170710
         ,bool                    _auto_irrig_mode
         ,Contingency_labeled    *_contigency_labeled
         ,Tparameter_file_form   *_parameter_file_form);
      void  show_hide_controls();
};
//---------------------------------------------------------------------------
extern PACKAGE TIrrigation_application_form *Irrigation_application_form;
//---------------------------------------------------------------------------
#endif
