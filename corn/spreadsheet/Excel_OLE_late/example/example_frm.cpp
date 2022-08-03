//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <corn/format/datarec.h>
#include <corn/datetime/date.h>
#include <corn/spreadsheet/Excel_OLE_late/excel_ole_late_workbook.h>
#include <corn/spreadsheet/workbook_datasrc.h>
#include "example_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#include <corn/format/example/test_record.cpp>


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  Workbook *excel_wb  = new Excel_OLE_latebinding_workbook;
  Workbook_data_source *wb_datasrc = new Workbook_data_source
  (excel_wb
   ,0    // detail_line_col
   ,1    // detail_line_row
   ,true // expect_field_names
   ,0    // field_name_row
  );

   Test_record test_rec;
   wb_datasrc->set(test_rec);
}
//---------------------------------------------------------------------------

