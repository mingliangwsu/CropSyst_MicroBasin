
#include <corn/format/excel/workbook.h>


int main()
{
   Excel_workbook workbook("test.xls",false,BIFF5);


   Excel_worksheet *sheet1 = workbook.provide_sheet("sheet1");
   sheet1->set_label(0,0,"col A");
   sheet1->set_integer(1,1,1);
   sheet1->set_float(2,2,2.0,2);
/*
   sheet1->freeze_pane(1,1);


   Excel_worksheet *sheet2 = workbook.get_sheet("sheet2");

   sheet2->set_label(0,0,"col A");
   sheet2->set_integer(1,1,1);
   sheet2->set_float(2,2,2.0,2);
*/
};

