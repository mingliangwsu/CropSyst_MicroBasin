//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_rotation_editor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "BaseGrid"
#pragma link "RNAutoIntegerEdit"
#pragma resource "*.dfm"
Trotation_editor_form *rotation_editor_form;
//---------------------------------------------------------------------------
__fastcall Trotation_editor_form::Trotation_editor_form(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

