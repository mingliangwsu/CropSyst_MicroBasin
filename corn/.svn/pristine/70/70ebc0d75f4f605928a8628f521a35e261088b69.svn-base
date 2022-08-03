#include "corn/spreadsheet/Excel_OLE_early/Excel_OLE_early_workbook.h"
#include "corn/datetime/date.hpp"
#include "corn/string/strconv.hpp"
#  include "corn/OS/file_system_engine.h"
#if (__BCPLUSPLUS__ < 0x0570)
//101229 identifiers were renamed at some time after BC++5
// They are different in BDS and so far (at least RadStudio2010) they have not been modified.
#define get_Range Get_Range
#define get_Sheets Get_Sheets
#define get_Name   Get_Name
#endif
namespace CORN
{
//______________________________________________________________________________
Excel_OLE_earlybinding_workbook::Excel_OLE_earlybinding_workbook
(const CORN::OS::File_name&  _workbook_filename_XLS // usually fully qualified or relative to current directory
,TExcelApplication*     _excelapplication_known
,TComponent*            _owner)
: filename_XLS(_workbook_filename_XLS)
{  int lcid = LOCALE_USER_DEFAULT;
   owner = _owner;
   excelapplication_known = _excelapplication_known;
   excelworkbook = new TExcelWorkbook(NULL);
   excelworkbook->ConnectKind = ckAttachToInterface;                             //110704
   if (CORN::OS::file_system_engine.exists(filename_XLS))                        //130905
   {
      #define wworkbook_filename filename_XLS
      wchar_t *wkbkname= (wchar_t *)wworkbook_filename.c_str();
      excelworkbook->ConnectTo(excelapplication_known->Workbooks->Open(wkbkname, TNoParam(),
         Variant(false)/*TNoParam()*/, TNoParam(), TNoParam(), TNoParam(),
         TNoParam(), TNoParam(), TNoParam(), Variant(false)/*TNoParam()*/,
         TNoParam(), TNoParam(), TNoParam(), lcid));
   } else
   excelworkbook->ConnectTo(excelapplication_known->Workbooks->Add());
}
//______________________________________________________________________________
Excel_OLE_earlybinding_workbook::Worksheet::~Worksheet()
{  if (excelworksheet)
   {  excelworksheet->Disconnect();
      delete excelworksheet;
   }
   excelworksheet = 0;
}
//______________________________________________________________________________
Excel_OLE_earlybinding_workbook::~Excel_OLE_earlybinding_workbook()
{  excelworkbook->Disconnect();
   delete excelworkbook;
}
//______________________________________________________________________________
bool Excel_OLE_earlybinding_workbook::save(bool display_alerts)     performs_IO_
{  int lcid = LOCALE_USER_DEFAULT;
   TVariant workbook_filename(filename_XLS.c_str());
   if (excelapplication_known)                                                   //110918
      excelapplication_known->DisplayAlerts[lcid] = display_alerts;              //110918
   if (CORN::OS::file_system_engine.exists(filename_XLS))                        //130905_110712
        excelworkbook->Save(LOCALE_SYSTEM_DEFAULT);                              //110712
   else excelworkbook->SaveAs
         (workbook_filename
         ,TNoParam(),TNoParam(),TNoParam(),TNoParam(),TNoParam()
         ,1/*xlNoChange*/,TVariant(2)/*xlLocalSessionChanges*/
         ,TNoParam(),TNoParam(),TNoParam(),LOCALE_SYSTEM_DEFAULT);
   excelworkbook->Saved[lcid] = true;                                            //110918
   if (excelapplication_known)                                                   //110918
      excelapplication_known->DisplayAlerts[lcid] = true;                        //110920
   return true;
}
//_2011-01-05___________________________________________________________________
bool Excel_OLE_earlybinding_workbook::save_as_format(const std::wstring &filename,XlFileFormat format,bool display_alerts )                  performs_IO_
{  int lcid = LOCALE_USER_DEFAULT;
   std::string workbook_filename_as_string;                                      //140101
   CORN::wstring_to_string(filename,workbook_filename_as_string);                //140101
   //130103 apparently TVariant is not taking wchar_t*
   TVariant workbook_filename(workbook_filename_as_string.c_str());              //140101
   if (excelapplication_known)                                                   //110918
      excelapplication_known->DisplayAlerts[lcid] = display_alerts;              //110918
   TVariant V_format = format;
   excelworkbook->SaveAs
         (workbook_filename
         ,V_format,TNoParam(),TNoParam(),TNoParam(),TNoParam()
         ,1/*xlNoChange*/,TVariant(2)/*xlLocalSessionChanges*/
         ,TNoParam(),TNoParam(),TNoParam(),LOCALE_SYSTEM_DEFAULT);
   excelworkbook->Saved[lcid] = true;                                            //110918
   if (excelapplication_known)                                                   //110918
      excelapplication_known->DisplayAlerts[lcid] = true;                        //110920
   return true;
}
//_2011-11-15___________________________________________________________________
bool Excel_OLE_earlybinding_workbook::save_as(const std::wstring &filename,bool display_alerts ) performs_IO_
{  return save_as_format(filename,0xFFFFEFD1/*Excel_2k::xlWorkbookNormal*/,display_alerts);
}
//_2011-12-15___________________________________________________________________
Workbook::Sheet *Excel_OLE_earlybinding_workbook::provide_sheet
(const std::string &sheet_name)                                                  //110711
{
   // Sets the specified sheet as active (Create if necessary).
   // For spreadsheet formats that only support single sheets,
   // this may be the name of the file for the sheet.
   // Returns a pointer to the sheet.
   // The sheet is owned by the workbook.
   bool sheet_just_added_to_workbook = true;
   Workbook::Sheet * sheet = (Workbook::Sheet *)sheets.find_string(sheet_name);
   if (!sheet)
   {  TExcelWorksheet *new_worksheet = new TExcelWorksheet(owner);
      // I actually want to connect to a named sheet
      long num_sheets =  excelworkbook->get_Sheets()->get_Count();
      bool sheet_exists = false;
      for (int i_based = 1; (i_based <= num_sheets) && !sheet_exists; i_based++)
      {
         #if (__BCPLUSPLUS__ < 0x0570)
         new_worksheet->ConnectTo(excelworkbook->get_Sheets()->get_Item(i_based));
         #else
         //101229, not sure if this is still needed
         Variant item_index(i_based);
         new_worksheet->ConnectTo(excelworkbook->Worksheets->get_Item(item_index));
         #endif
         AnsiString existing_sheet_name;
         existing_sheet_name = new_worksheet->get_Name();
         if (existing_sheet_name == sheet_name.c_str())
            sheet_exists = true;
      }
      if (!sheet_exists)
      {
         //160823 long new_sheet_index_1based = 1; // It appears excel adds new sheets at index 1 (STUPID IDEA!)
         //  excelworkbook->Get_Sheets()->get_Count() +1;
         Excel_2k::_WorksheetPtr added_worksheet = excelworkbook->get_Sheets()->Add();    //160823
         // Note: I think Add returns the sheet index, it could return the sheet, I DONT KNOW!
         #if (__BCPLUSPLUS__ < 0x0570)
         TVariantInParam vsheet_name;
         // Now  set the sheet tab name to the sheet name
         vsheet_name = sheet_name.c_str();
         new_worksheet->Name = vsheet_name;
         #else
         new_worksheet->ConnectTo(added_worksheet);                              //160823
            //160823 (excelworkbook->Worksheets->get_Item(Variant(new_sheet_index_1based)));
         Variant vsheet_name (sheet_name.c_str());
         // Now  set the sheet tab name to the sheet name
         new_worksheet->Name = vsheet_name;
         #endif
         sheet_just_added_to_workbook = true;
      }
// This works for a given sheet number:      new_worksheet->ConnectTo(excelworkbook->Get_Sheets()->get_Item(1));
      sheet = new Worksheet(new_worksheet, sheet_just_added_to_workbook);
      sheets.append(sheet);
   }
   return sheet;
}
//______________________________________________________________________________
bool Excel_OLE_earlybinding_workbook::copy_sheet
(const std::string &from_sheet_name
,const std::string &to_sheet_name)                                 modification_
{
   Excel_OLE_earlybinding_workbook::Worksheet *from_sheet = (Excel_OLE_earlybinding_workbook::Worksheet *)sheets.find_string(from_sheet_name);
   Excel_OLE_earlybinding_workbook::Worksheet *to_sheet = (Excel_OLE_earlybinding_workbook::Worksheet *)sheets.find_string(to_sheet_name);
   bool copied =
         (from_sheet != NULL) && (from_sheet->excelworksheet != NULL)
      && (to_sheet != NULL)   && (to_sheet  ->excelworksheet != NULL);
   if (copied)
   {  TExcelWorksheet *from_excel_worksheet = from_sheet->excelworksheet;
      TExcelWorksheet *to_excel_worksheet = to_sheet->excelworksheet;
      int lcid = LOCALE_USER_DEFAULT;
      /* NYI
         need to select range to cut and paste
      */
   }
   return copied;
}
//_2011-07-11_______________________________________________________copy_sheet_/
const std::string &Excel_OLE_earlybinding_workbook::get_name(std::string &name) const
{  // I would actually like to return the workbook name property (I don't know what it is)
//   static AnsiString name;
   #if (__BCPLUSPLUS__ >= 0x0620)
      CORN::wstring_to_string(excelworkbook->Name,name);
   #else
      name = excelworkbook->Name;
   #endif
   return name;
}
//______________________________________________________________________________
Excel_OLE_earlybinding_workbook::Worksheet::Worksheet(TExcelWorksheet *i_excelworksheet
,bool _sheet_just_added_to_workbook)
: excelworksheet(i_excelworksheet)
, just_added_to_workbook(_sheet_just_added_to_workbook)
{}
//______________________________________________________________________________
char *Excel_OLE_earlybinding_workbook::Worksheet::cell_name(nat16 col_0, nat32 row_0,char *name) const
{  int col_1 = col_0 + 1;
   int row_1 = row_0 + 1;
   int k = 0;
   if (col_1 > 26)
   {  name[k++] = 64 + (col_1/26);
      name[k++] = 64 + (col_1%26);
   } else
      name[k++] = 64 + col_1;
   std::sprintf(name+k,"%d",row_1);
   return name;
}
//______________________________________________________________________________
bool Excel_OLE_earlybinding_workbook::Worksheet::clear_cell(nat16 col, nat32 row)
{ char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   clear_range(cell_coordinate);
   return true;
}
//_2011-08-31___________________________________________________________________
bool Excel_OLE_earlybinding_workbook::Worksheet::clear_range(const char *range)
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(range,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(range),TNoParam());
 #endif
   cells->Clear();
   return true;
}
//_2011-08-31___________________________________________________________________
bool Excel_OLE_earlybinding_workbook::Worksheet::set_cell_bool
   (nat16 col, nat32 row, bool value)
{
char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return set_range_bool(cell_coordinate, value);                                //110713
}
//_2011-09-22___________________________________________________________________
int32 Excel_OLE_earlybinding_workbook::Worksheet::set_cell_integer30
(nat16 col, nat32 row, int32 value)
{  char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return set_range_integer30(cell_coordinate, value);                           //110713
}
//______________________________________________________________________________
float64     Excel_OLE_earlybinding_workbook::Worksheet::set_cell_number
(nat16 col, nat32 row, float64 value,nat8 precision)
{  char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return set_range_number(cell_coordinate,value, precision);               //110713
}
//______________________________________________________________________________
const std::string &Excel_OLE_earlybinding_workbook::Worksheet::set_cell_label
(nat16 col, nat32 row, const std::string &value)
{  char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return set_range_label(cell_coordinate, value);                          //110713
}
//______________________________________________________________________________
const std::wstring &Excel_OLE_earlybinding_workbook::Worksheet::set_cell_label_wstring
(nat16 col, nat32 row, const std::wstring &value)
{  char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return set_range_label_wstring(cell_coordinate, value);
}
//_2014-01-02___________________________________________________________________
int32    Excel_OLE_earlybinding_workbook::Worksheet::set_cell_date
(nat16 col, nat32 row,const CORN::Date &date_value)
{  char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return set_range_date(cell_coordinate,date_value);                            //110713
}
//______________________________________________________________________________
int32 Excel_OLE_earlybinding_workbook::Worksheet::set_range_integer30
(const char *cell_coordinate, int32 value)
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->get_Range(cell_coordinate,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();
   cells->Activate();
   //Put an int in the activated cell
   Variant intValue; //110105 TVariantInParam intValue;
   intValue=value;
   cells->set_Value(intValue);
   return value;
}
//______________________________________________________________________________
bool Excel_OLE_earlybinding_workbook::Worksheet::set_range_bool
(const char *cell_coordinate, bool value)
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->get_Range(cell_coordinate,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();
   cells->Activate();
   //Put an int in the activated cell
   Variant boolValue;
   boolValue=value;
   cells->set_Value(boolValue);
   return value;
}
//______________________________________________________________________________
float64 Excel_OLE_earlybinding_workbook::Worksheet::set_range_number
(const char *cell_coordinate, float64 value,uint8 precision)
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(cell_coordinate,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();
   cells->Activate();
   //Put a number in the activated cell
   TVariantInParam fltValue;
   fltValue=value;
   cells->set_Value(fltValue);
   return value;
}
//______________________________________________________________________________
const std::string &Excel_OLE_earlybinding_workbook::Worksheet::set_range_label
(const char *cell_coordinate, const std::string &value)
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(cell_coordinate,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();
   cells->Activate();
 #if (__BCPLUSPLUS__ < 0x0570)
   TVariantInParam strValue;
   strValue=value;
  #else
    Variant strValue;
    strValue = value.c_str();
  #endif
   cells->set_Value(strValue);
   return value;
}
//______________________________________________________________________________
const std::wstring &Excel_OLE_earlybinding_workbook::Worksheet::set_range_label_wstring
(const char *cell_coordinate, const std::wstring &value)
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(cell_coordinate,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();
   cells->Activate();
 #if (__BCPLUSPLUS__ < 0x0570)
   TVariantInParam strValue;
   strValue=value;
  #else
    Variant strValue;
    strValue = value.c_str();
  #endif
   cells->set_Value(strValue);
   return value;
}
//_2013-09-05___________________________________________________________________
int32    Excel_OLE_earlybinding_workbook::Worksheet::set_range_date
(const char *cell_coordinate,const CORN::Date &date_value)
{  Year year; Month month; DOM dom;
   date_value.gregorian(year,month,dom);
   TDateTime builder_datevalue((unsigned short )year,(unsigned short )month,(unsigned short)dom);
 #if (__BCPLUSPLUS__ < 0x0570)
   TVariantInParam dateValue;
   dateValue = builder_datevalue;
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(cell_coordinate,TNoParam());
 #else
   TVariant dateValue(builder_datevalue);
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();

   cells->Activate();
   cells->set_Value(dateValue);
   return date_value.get_date32();
}
//______________________________________________________________________________
bool Excel_OLE_earlybinding_workbook::Worksheet::set_range_color
(const char *range,nat8 red,nat8 green, nat8 blue)
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(range,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(range),TNoParam());
 #endif
   //NYI   cells->Interior->Color = RGB(red,green,blue);
   cells->get_Interior()->set_Color(TVariant(RGB(red,green,blue)));
   return true;
}
//_2011-08-15___________________________________________________________________
bool Excel_OLE_earlybinding_workbook::Worksheet::set_cell_color(nat16 col, nat32 row,nat8 red,nat8 green, nat8 blue)
{
   char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return set_range_color(cell_coordinate, red, green,  blue);
}
//_2011-08-15___________________________________________________________________
const std::string &Excel_OLE_earlybinding_workbook::Worksheet::set_range_formula(const char *range, const std::string &formula)    //110815
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(range,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(range),TNoParam());
 #endif
 #if (__BCPLUSPLUS__ < 0x0570)
   TVariantInParam strFormula;
   strFormula=formula;
  #else
    Variant strFormula;
    strFormula = formula.c_str();
  #endif
   cells->set_Formula(strFormula);
   return formula;
}
//_2011-08-15___________________________________________________________________
const std::string &Excel_OLE_earlybinding_workbook::Worksheet::set_cell_formula
(nat16 col, nat32 row, const std::string &formula)  //110815
{  char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return set_range_formula(cell_coordinate,formula);
}
//_2011-08-15___________________________________________________________________
int32 Excel_OLE_earlybinding_workbook::Worksheet::get_cell_integer30
(nat16 col, nat32 row)                                                     const
{  char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return get_range_integer30(cell_coordinate);                                  //111001
}
//______________________________________________________________________________
bool Excel_OLE_earlybinding_workbook::Worksheet::get_cell_bool
(nat16 col, nat32 row)                                                     const //130506
{  char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return get_range_bool(cell_coordinate);
}
//_2013-03-28___________________________________________________________________
float64 Excel_OLE_earlybinding_workbook::Worksheet::get_cell_number
(nat16 col, nat32 row)                                                     const
{  char cell_coordinate[20];
   cell_name(col,row,cell_coordinate);
   return get_range_number(cell_coordinate);
}
//______________________________________________________________________________
float64 Excel_OLE_earlybinding_workbook::Worksheet::get_range_number
(const char *cell_coordinate)                                              const
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(cell_coordinate,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();
   cells->Activate();
   //Put a number in the activated cell
   TVariantInParam fltValue = cells->get_Value();
   float64 value = fltValue;
   return value;
}
//_2011-09-14___________________________________________________________________
int32 Excel_OLE_earlybinding_workbook::Worksheet::get_range_integer30(const char *cell_coordinate)          const
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(cell_coordinate,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();
   cells->Activate();
   //Put a number in the activated cell
   TVariantInParam Value = cells->get_Value();
   int32 value = Value;
   return value;
}
//_2011-11-01___________________________________________________________________
bool Excel_OLE_earlybinding_workbook::Worksheet::get_range_bool
(const char *cell_coordinate)                                              const //130506
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(cell_coordinate,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();
   cells->Activate();
   //Put a number in the activated cell
   TVariantInParam Value = cells->get_Value();
   bool value = Value;
   return value;
}
//_2013-03-28___________________________________________________________________
const std::wstring &Excel_OLE_earlybinding_workbook::Worksheet::get_cell_label(nat16 col, nat32 row,std::wstring &label)   const
{ char cell_coordinate[20];
  cell_name(col,row,cell_coordinate);
  return get_range_label(cell_coordinate,label);
}
//______________________________________________________________________________
const std::wstring &Excel_OLE_earlybinding_workbook::Worksheet::get_range_label (const char *cell_coordinate,std::wstring &label)      const
{
 #if (__BCPLUSPLUS__ < 0x0570)
   Excel_2k::RangePtr cells;
   cells=excelworksheet->Get_Range(cell_coordinate,TNoParam());
 #else
   Excel_2k::ExcelRangePtr cells;
   cells=excelworksheet->get_Range(TVariant(cell_coordinate),TNoParam());
 #endif
   excelworksheet->Activate();
   cells->Activate();
   //Put a number in the activated cell
   TVariantInParam fltValue = cells->get_Value();
   const wchar_t *value = fltValue;
   label.assign(value);
   return label; //130506 value;
}
//_2011-10-01___________________________________________________________________
      // Sheet attributes:
void Excel_OLE_earlybinding_workbook::Worksheet::freeze_pane(nat16 left_most_column,nat32 top_most_row )
{
//  Not yet implemented
}
//______________________________________________________________________________
const std::string &Excel_OLE_earlybinding_workbook::Worksheet::get_name(std::string &name)  const  // the name of the sheet
{  // I would actually like to return the workbook name property (I don't know what it is)
   #if (__BCPLUSPLUS__ >= 0x0620)
   CORN::wstring_to_string(excelworksheet->Name,name);
   #else
   name = excelworksheet->Name;
   #endif
   return name.c_str();
}
//______________________________________________________________________________
replace with is_key()
const char *Excel_OLE_earlybinding_workbook::Worksheet::get_key()          const
{  static std::string return_buffer;
   #if (__BCPLUSPLUS__ >= 0x0620)
   CORN::wstring_to_string(excelworksheet->Name,return_buffer);
   #else
      return_buffer.assign(excelworksheet->Name);
   #endif
   return return_buffer.c_str();
}
/*not yet needed
uint8       Excel_OLE_earlybinding_workbook::Worksheet::get_index() // the sheet tab index (0 based).
{
}
*/
//______________________________________________________________________________
bool Excel_OLE_earlybinding_workbook::close()                       performs_IO_
{  int lcid = LOCALE_USER_DEFAULT;
   VARIANT unused_filename;
   VARIANT unused_routeworkbook;
   //VARIANT save_changes = false;
   excelworkbook->Close(Variant(false),TNoParam(),TNoParam(),lcid);
   return true;
}
//______________________________________________________________________________
}


