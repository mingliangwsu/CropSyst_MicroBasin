//---------------------------------------------------------------------------

#ifndef project_name_frmH
#define project_name_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tproject_name_form : public TForm
{
__published:	// IDE-managed Components
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TEdit *project_name_edit;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
   __fastcall Tproject_name_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tproject_name_form *project_name_form;
//---------------------------------------------------------------------------
#endif
