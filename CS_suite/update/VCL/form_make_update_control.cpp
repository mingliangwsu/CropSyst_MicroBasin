//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_make_update_control.h"
#include "update_control_file_generator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvDirectoryEdit"
#pragma link "AdvEdBtn"
#pragma link "AdvEdit"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{};
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
   Update_control_file_generator update_gen;
   update_gen.create
      (edit_distribution_directory->Text.c_str() // This is the directory containing the files to be included in the installation.
      ,edit_installation_directory->Text.c_str() // This is the directory on the users computer where the application is to be installed.
      ,edit_application_installation_URL->Text.c_str()        // This is the URL of the web site where the files will be found by the updater program.
      );
}
//---------------------------------------------------------------------------
