//---------------------------------------------------------------------------

#ifndef form_irrig_modeH
#define form_irrig_modeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RNAutoParameterEditBar.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
// forward decl
class Automatic_irrigation_mode;

class TAuto_irrigation_mode_form_obsolete : public TForm
{
__published:	// IDE-managed Components
   TRNAutoParameterEditBar *max_allowable_depletion_editbar;
   TRNAutoParameterEditBar *depletion_observe_depth_editbar;
   TRNAutoParameterEditBar *net_irrigation_mult_editbar;
   TRNAutoParameterEditBar *max_application_editbar;
   TRNAutoParameterEditBar *salinity_editbar;
   TLabel *Label1;

private:	// User declarations
   Automatic_irrigation_mode *auto_irrig_mode;
public:		// User declarations
   __fastcall TAuto_irrigation_mode_form_obsolete(TComponent* Owner);
   void __fastcall bind_to(Automatic_irrigation_mode *i_auto_irrig_mode);

};
//---------------------------------------------------------------------------
extern PACKAGE TAuto_irrigation_mode_form_obsolete *Auto_irrigation_mode_form_obsolete;
//---------------------------------------------------------------------------
#endif
