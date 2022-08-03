//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_Excel_with_TDF.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Excel_XP_srvr"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{

Button1->Tag = 1;
Button2->Tag = 2;
Button3->Tag = 3;
Button4->Tag = 4;
Button1->Caption = "Select File";
Button2->Caption = "Show Excel";
Button3->Caption = "Connect";
Button4->Caption = "Select Sheet";
FormStyle = fsStayOnTop;
Button3->Enabled = false;
Button4->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  HandleButtons(Button1->Tag);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  HandleButtons(Button2->Tag);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
HandleButtons(Button3->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  HandleButtons(Button4->Tag);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::HandleButtons(int ButtonNumber)
{
   switch (ButtonNumber)
   {
      case 1: OpenDialog1->Filter = "Excel files (*.xls)|*.XLS";
              OpenDialog1->Execute();
              if (OpenDialog1->FileName.Length()>0)
              {
                  Button1->Enabled = false;
                  Button3->Enabled = true;
                  Button4->Enabled = true;
              }
              break;
      case 2: if (Button2->Caption == "Show Excel")
              {
                  Button2->Caption = "Hide Excel";
                  ExcelApplication1->set_Visible(0, true);
              }
              else
              {
                  Button2->Caption = "Show Excel";
                  ExcelApplication1->set_Visible(0, false);
              }
              break;
      case 3: if (Button3->Caption == "Connect")
              {
                  Button3->Caption = "Disconnect";
                  Button4->Enabled = true;
                  ExcelApplication1->Connect();
                  Excel_xp::ExcelWorkbook** RHS;
                  ExcelWorkbook1->ConnectTo(ExcelApplication1->Workbooks->Open
                     (StringToOleStr(OpenDialog1->FileName)
                     , EmptyParam   // Update Links
                     , EmptyParam   // ReadOnly
                     , EmptyParam   // Format
                     , EmptyParam   // Password
                     , EmptyParam   // WriteResPassword
                     , EmptyParam   // IgnoreReadOnlyRecommended
                     , EmptyParam   // Origin
                     , EmptyParam   // Delimiter
                     , EmptyParam   // Editable
                     , EmptyParam   // Notify
                     , EmptyParam   // Converter
                     , EmptyParam   // AddToMru
                     , EmptyParam   // Local
                     , EmptyParam   // CorruptLoad
                     , LCID(LOCALE_USER_DEFAULT)
                     , 0 // RHS  // RHS
                     ));


#ifdef decl
  virtual HRESULT STDMETHODCALLTYPE Open(BSTR Filename/*[in]*/, VARIANT UpdateLinks/*[in,opt]*/,
                                         VARIANT ReadOnly/*[in,opt]*/, VARIANT Format/*[in,opt]*/,
                                         VARIANT Password/*[in,opt]*/,
                                         VARIANT WriteResPassword/*[in,opt]*/,
                                         VARIANT IgnoreReadOnlyRecommended/*[in,opt]*/,
                                         VARIANT Origin/*[in,opt]*/, VARIANT Delimiter/*[in,opt]*/,
                                         VARIANT Editable/*[in,opt]*/, VARIANT Notify/*[in,opt]*/,
                                         VARIANT Converter/*[in,opt]*/, VARIANT AddToMru/*[in,opt]*/,
                                         VARIANT Local/*[in,opt]*/, VARIANT CorruptLoad/*[in,opt]*/,
                                         long lcid/*[in]*/,
                                         Excel_xp::ExcelWorkbook** RHS/*[out,retval]*/) = 0; // [1923]


#endif
                  ExcelApplication1->set_DisplayAlerts(0, false);
                  for (int index=1; index<ExcelWorkbook1->Sheets->get_Count()+1; ++index)
                  {
                       ExcelWorksheet1->ConnectTo(ExcelWorkbook1->Sheets->get_Item(TVariant(index)));
                       ListBox1->Items->Add(ExcelWorksheet1->get_Name());
                  }
              }
              else
              {
                  Button2->Caption = "Show Excel";
                  Button3->Caption = "Connect";
                  Button4->Enabled = false;
                  ListBox1->Clear();
                  ExcelApplication1->Disconnect();
              }
              break;
      case 4: if (ListBox1->ItemIndex != -1)
              {
                  ExcelWorksheet1->ConnectTo(ExcelWorkbook1->Sheets->get_Item(TVariant(ListBox1->ItemIndex + 1)));
                  ExcelWorksheet1->Activate();
              }
              break;
      }
}
//---------------------------------------------------------------------------

