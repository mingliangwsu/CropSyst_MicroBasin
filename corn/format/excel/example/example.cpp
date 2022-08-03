#include <corn/format/biff.h>

void main()
{
   biff_file test_xls("test.xls",0,0,10,10);

   test_xls.write_label_cell(1,1,common_spreadsheet_file::CSS_justify_left,"A");
   test_xls.write_label_cell(1,2,common_spreadsheet_file::CSS_justify_center,"B");
   test_xls.write_label_cell(1,3,common_spreadsheet_file::CSS_justify_right,"C");

   test_xls.write_integer_cell(2,1,1);
   test_xls.write_integer_cell(2,2,2);
   test_xls.write_integer_cell(2,3,3);

   test_xls.write_number_cell(3,1,1.1,1);
   test_xls.write_number_cell(3,2,2.2,2);
   test_xls.write_number_cell(3,3,3.3,3);

   // Next sheet
   test_xls.write_BOF_record();
   test_xls.write_dimensions(0,0,10,10);

   test_xls.write_integer_cell(2,1,1);
   test_xls.write_integer_cell(2,2,2);
   test_xls.write_integer_cell(2,3,3);
   

};
