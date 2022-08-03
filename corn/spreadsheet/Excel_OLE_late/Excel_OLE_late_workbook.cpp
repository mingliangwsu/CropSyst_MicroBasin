#include "corn/spreadsheet/Excel_OLE_late/Excel_OLE_late_workbook.h"
namespace CORN
{
//______________________________________________________________________________
Excel_OLE_latebinding_workbook::Excel_OLE_latebinding_workbook()
{
   Variant vMSExcel;
   vMSExcel = Variant::CreateObject("Excel.Application");
   vMSExcel.OlePropertySet("Visible", true);

   Variant vXLWorkbooks;
   vXLWorkbooks = vMSExcel.OlePropertyGet("Workbooks");
   vXLWorkbook = vXLWorkbooks.OleFunction("Add");
}
//______________________________________________________________________________
Excel_OLE_latebinding_workbook::~Excel_OLE_latebinding_workbook()
{
   Variant vSaveChanges, vFileName;
   vSaveChanges = true;
   char filename[255];
   strcpy(filename,name.c_str());
   strcat(filename,".xls");
   vFileName = filename;
   vXLWorkbook.OleFunction("Close", vSaveChanges, vFileName);
}
//______________________________________________________________________________
Workbook::Sheet *Excel_OLE_latebinding_workbook::provide_sheet(const std::string &sheet_name)
{
   // Sets the specified sheet as active (Create if necessary).
   // For spreadsheet formats that only support single sheets,
   // this may be the name of the file for the sheet.
   // Returns a pointer to the sheet.
   // The sheet is owned by the workbook.

   Workbook::Sheet * sheet = (Workbook::Sheet *)sheets.find(sheet_name.c_str());
   if (!sheet)
   {
      Variant vWorksheet;
      Variant vSheetName;
      vSheetName = sheet_name;
      try
      {
         vWorksheet = vXLWorkbook.OlePropertyGet("Worksheets",vSheetName);
      }
      catch (Exception &exception)
      {
         vWorksheet = vXLWorkbook.OleFunction("Add");
         vWorksheet.OlePropertySet("Name",sheet_name); 
      }
      sheet = new Worksheet(vWorksheet,sheet_name);
      sheets.append(sheet);
   }
   return sheet;
}
//______________________________________________________________________________
const std::string &Excel_OLE_latebinding_workbook::get_name(std::string &return_name) const
{  // I would actually like to return the workbook name property (I don't know what it is)
   return_name.assign(name);
   return return_name;
}
//______________________________________________________________________________
Excel_OLE_latebinding_workbook::Worksheet::Worksheet(Variant &ivWorksheet,const char *i_name)
: vWorksheet(ivWorksheet)
, name(i_name)
{}
//______________________________________________________________________________
char *Excel_OLE_latebinding_workbook::Worksheet::cell_name(uint16 col, uint32 row)
{
   int k = 0;
   static char name[10];
   if (col > 26)
   {
      name[k++] = 64 + (col/26);
      name[k++] = 65 + (col%26);
   }
   else
      name[k++] = 64 + col;
   sprintf(name+k,"%d",row);
   return name;
}
//______________________________________________________________________________
sint16       Excel_OLE_latebinding_workbook::Worksheet::set_cell_integer  (uint16 col, uint32 row, sint16 value)
{
   Variant vRange;
   vRange = cell_name(col,row);
   Variant vCell;
   vCell = vWorksheet.OlePropertyGet("Range",vRange);
   Variant vValue;
   vValue = value;
   vCell.OlePropertySet("Value",vValue);
   return value;
}
//______________________________________________________________________________
float64     Excel_OLE_latebinding_workbook::Worksheet::set_cell_number   (uint16 col, uint32 row, float64 value)
{
   Variant vRange;
   vRange = cell_name(col,row);
   Variant vCell;
   vCell = vWorksheet.OlePropertyGet("Range",vRange);
   Variant vValue;
   vValue = value;
   vCell.OlePropertySet("Value",vValue);
   return value;
}
//______________________________________________________________________________
const std::string &Excel_OLE_latebinding_workbook::Worksheet::set_cell_label (uint16 col, uint32 row, const std::string &value)
{
   Variant vRange;
   vRange = cell_name(col,row);
   Variant vCell;
   vCell = vWorksheet.OlePropertyGet("Range",vRange);
   Variant vValue;
   vValue = value;
   vCell.OlePropertySet("Value",vValue);
   return value;
}
//______________________________________________________________________________
      // The following are for getting data in the sheet
sint16       Excel_OLE_latebinding_workbook::Worksheet::get_cell_integer  (uint16 col, uint32 row)
{
   Variant vRange;
   vRange = cell_name(col,row);
   Variant vCell;
   vCell = vWorksheet.OlePropertyGet("Range",vRange);
   Variant vValue;
   vCell.OlePropertyGet("Value",vValue);
   return vValue;
}
//______________________________________________________________________________
float64     Excel_OLE_latebinding_workbook::Worksheet::get_cell_number   (uint16 col, uint32 row)
{
   Variant vRange;
   vRange = cell_name(col,row);
   Variant vCell;
   vCell = vWorksheet.OlePropertyGet("Range",vRange);
   Variant vValue;
   vCell.OlePropertyGet("Value",vValue);
   return vValue;

}
//______________________________________________________________________________
const char *Excel_OLE_latebinding_workbook::Worksheet::get_cell_label (uint16 col, uint32 row)
{
   Variant vRange;
   vRange = cell_name(col,row);
   Variant vCell;
   vCell = vWorksheet.OlePropertyGet("Range",vRange);
   static AnsiString result;
   Variant vValue;
   vCell.OlePropertyGet("Value",vValue);
   result = vValue;
   return result.c_str();
}
//______________________________________________________________________________
// Sheet attributes:
void        Excel_OLE_latebinding_workbook::Worksheet::freeze_pane(uint16 left_most_column,uint32 top_most_row )
{
//NYI
}
//______________________________________________________________________________
const std::string &sheet_nameExcel_OLE_latebinding_workbook::Worksheet::get_name(std::string &sheet_name)  const  // the name of the sheet
{
 //  return name.c_str();
   sheet_name = name;
   return sheet_name;
}
//______________________________________________________________________________
/*not yet needed
uint8       Excel_OLE_latebinding_workbook::Worksheet::get_index() // the sheet tab index (0 based).
{

}
*/

} // namespace CORN
