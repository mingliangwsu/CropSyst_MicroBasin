//---------------------------------------------------------------------------

#ifndef form_make_update_controlH
#define form_make_update_controlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvDirectoryEdit.hpp"
#include "AdvEdBtn.hpp"
#include "AdvEdit.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TLabel *Label1;
   TAdvDirectoryEdit *edit_distribution_directory;
   TBitBtn *BitBtn1;
   TLabel *Label2;
   TEdit *edit_application_installation_URL;
   TLabel *Label3;
   TEdit *edit_installation_directory;
   void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
