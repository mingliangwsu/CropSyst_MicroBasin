//---------------------------------------------------------------------------

#ifndef irrig_mode_frmH
#define irrig_mode_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoFloat32EditBar.h"
//---------------------------------------------------------------------------
// forward decl
class Automatic_irrigation_mode;

class TAuto_irrigation_mode_form_obsolete : public TForm
{
__published:	// IDE-managed Components
   TAutoFloat32EditBar *max_allowable_depletion_editbar;
   TAutoFloat32EditBar *depletion_observe_depth_editbar;
   TAutoFloat32EditBar *net_irrigation_mult_editbar;
   TAutoFloat32EditBar *max_application_editbar;
   TAutoFloat32EditBar *salinity_editbar;
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
