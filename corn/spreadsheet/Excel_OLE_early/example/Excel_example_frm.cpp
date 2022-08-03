//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Excel_example_frm.h"
#include <corn/spreadsheet/excel_ole_early/excel_ole_early_workbook.h>
#include <corn/format/datarec.h>
#include <corn/datetime/date.h>
#include <corn/spreadsheet/workbook_datasrc.h>

using namespace CORN;
#include <corn/format/example/test_record.cpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Excel_2K_SRVR"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{




}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  Workbook *excel_wb  = new Excel_OLE_earlybinding_workbook(this);
  Workbook_data_source *wb_datasrc = new Workbook_data_source
  (excel_wb
   ,0    // detail_line_col
   ,1    // detail_line_row
   ,true // expect_field_names
   ,0    // field_name_row
  );

   Test_record test_rec;
   wb_datasrc->set(test_rec);
   wb_datasrc->goto_next(2);
   test_rec.inc();
   wb_datasrc->set(test_rec);

}
//---------------------------------------------------------------------------

