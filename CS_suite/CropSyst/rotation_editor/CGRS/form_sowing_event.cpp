//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_sowing_event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvEdBtn"
#pragma link "AdvEdit"
#pragma link "AdvFileNameEdit"
#pragma link "AdvSmoothDatePicker"
#pragma link "AdvSmoothEdit"
#pragma link "AdvSmoothEditButton"
#pragma link "RNAutoParameterEditBar"
#pragma resource "*.dfm"
Tsowing_event_form *sowing_event_form;
//---------------------------------------------------------------------------
__fastcall Tsowing_event_form::Tsowing_event_form(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

