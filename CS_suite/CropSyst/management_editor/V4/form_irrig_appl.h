//---------------------------------------------------------------------------

#ifndef form_irrig_applH
#define form_irrig_applH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoFloat32EditBar.h"
#include "AutoRadioGroup.h"
#include <ExtCtrls.hpp>
#include "AutoCheckBox.h"
#include <ComCtrls.hpp>
//______________________________________________________________________________
namespace CropSyst
{
   class Irrigation_operation;
};
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
   TAutoRadioGroup *radiogroup_consideration;
   TGroupBox *groupbox_depletion_constraints;
   TAutoFloat32EditBar *max_allowable_depletion_editbar;
   TAutoFloat32EditBar *depletion_obs_fract_root_depth_edit;
   TAutoFloat32EditBar *depletion_observe_depth_editbar;
   TPanel *panel_observation_depth_model;
   TLabel *depletion_contigency_note;
   TAutoRadioGroup *radiobutton_depletion_observation_depth_mode;
   TAutoFloat32EditBar *editbar_leaf_water_potential;
   TPanel *panel_application_mode;
   TLabel *depletion_constraints_note;
   TAutoRadioGroup *application_mode_radiogroup;
   TAutoFloat32EditBar *amount_editbar;
   TPanel *panel_refill;
   TAutoFloat32EditBar *net_irrigation_mult_editbar;
   TAutoFloat32EditBar *max_application_editbar;
   TAutoFloat32EditBar *min_application_editbar;
   TAutoFloat32EditBar *refill_point_edit_bar;
   TTabSheet *TabSheet3;
   TAutoFloat32EditBar *salinity_editbar;
   TAutoFloat32EditBar *edit_NO3_N_conc;
   TAutoFloat32EditBar *edit_NH4_N_conc;
   TLabel *Label1;
   TLabel *Label3;
   TGroupBox *GroupBox1;
   TAutoFloat32EditBar *edit_irrig_wetted_surface_evap;
   TAutoFloat32EditBar *edit_irrig_wetted_soil_volume;
   void __fastcall application_mode_radiogroup_onclick(TObject *Sender);
   void __fastcall radiobutton_depletion_observation_depth_modeClick(TObject *Sender);
   void __fastcall radiobutton_depletion_observation_depth_modeExit(TObject *Sender);
   void __fastcall radiogroup_considerationClick(TObject *Sender);
private:	// User declarations
   #ifdef OLD_MGMT_PARAM
   #error check obsolete
   CropSyst::Irrigation_operation *irrig_op;
   #else

   CropSyst::Irrigation_operation_class  *irrig_op;
   #endif
   bool                  auto_irrig_mode;
//NYI   bool                  *fixed_periodic;
   Contingency_labeled   *contigency_labeled;   // may be 0 (I.e. for auto irrig mode)
public:		// User declarations
   __fastcall TIrrigation_application_form(TComponent* Owner);
      void __fastcall bind_to
         (CropSyst::
            #ifdef OLD_MGMT_PARAM
            #error check obsolete
            Irrigation_operation
            #else
            Irrigation_operation_class
            #endif
          *_irrig_op
         ,bool                    _auto_irrig_mode
         ,Contingency_labeled    *_contigency_labeled
         ,Tparameter_file_form   *_parameter_file_form);
      void  show_hide_controls();
};
//---------------------------------------------------------------------------
extern PACKAGE TIrrigation_application_form *Irrigation_application_form;
//---------------------------------------------------------------------------
#endif
