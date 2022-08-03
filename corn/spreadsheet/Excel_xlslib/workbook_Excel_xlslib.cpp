#include "workbook_Excel_xlslib.h"
#include "corn/chronometry/date_32.h"
#include <assert.h>
#include "xlslib/range.h"
namespace CORN
{
//______________________________________________________________________________
Workbook_Excel_xlslib::Workbook_Excel_xlslib
(const char *_workbook_filename_XLS
,std::ios_base::openmode _openmode)                                              //130401
: CORN::Workbook()
, openmode(_openmode)
, workbook_out(_openmode == std::ios_base::out ? new xlslib_core::workbook : 0)  //130401
#if (__BCPLUSPLUS_ > 0x0600)
      // NYI for BDS
, workbook_in (_openmode == std::ios_base::in  ? new xls::WorkBook(_workbook_filename_XLS.c_str()) : 0)       //130401
#endif
, filename_XLS(_workbook_filename_XLS)
{}
//__________________________________________Workbook_Excel_xlslib_constructor__/
Workbook_Excel_xlslib::Sheet::Sheet(xlslib_core::worksheet *_worksheet_out,const std::string &_name)
: name(_name)
, index()      // Warning need to provide index
, worksheet_out(_worksheet_out)
#if (__BCPLUSPLUS_ > 0x0600)
      // NYI for BDS
, in_workbook(0)
#endif
{}
//___________________________________Workbook_Excel_xlslib::Sheet_constructor__/
#if (__BCPLUSPLUS_ > 0x0600)
      // NYI for BDS
Workbook_Excel_xlslib::Sheet::Sheet
(xls::WorkBook    *_in_workbook
,nat16                _index
,const std::string &_name)
: name(_name)
, index(_index)      // Warning need to provide index
, worksheet_out(0)
, in_workbook(_in_workbook)
{}
#endif
//_2013-04-01___________________________________________________________________
sint32    Workbook_Excel_xlslib::Sheet::set_cell_date
(nat16 col, nat32 row, const CORN::Date_const &date_value)
{  // warning, may need to use pxformat to format the date
   if (!worksheet_out) return 0; /* cannot set to readonly file */               //130401
   CORN::Date_clad_32 epoch((Year)1900,(DOY)1);
   nat32 epoch_offset = epoch.days_between(date_value);
   return worksheet_out->number((unsigned32_t)row,(unsigned32_t)col,(double)epoch_offset,xlslib_core::FMT_DATE1 ,/*& pxformat*/  NULL) != NULL;
/* http://www.gaia-gis.it/FreeXL/freexl-1.0.0a-doxy-doc/Format.html
Any Date is expressed as an Integer (number of days since the conventional reference day):

for Windows Excel the reference day (day 0) is 1900, January 1
for Mac Excel the reference day (day 0) is 1904, January 2
There is no possible ambiguity, because the DATEMODE metadata record specifies tells which reference day is to be used.

An odd bug affects Excel, which (incorrectly) treats 1900 as a leap year. Therefore, the non-existant 29 February 1900 has to be included in the days calculation so to get the expected Date value.

Any Time is expressed as a Fraction (percent of seconds since midnight). 0.5 corresponds to 12:00:00 (midday), 0.25 corresponds to 06:00:00, 0.75 corresponds to 18:00:00 and so on.

So a DateTime is simply the sum of a Date value and of a Time value. Dates can be represented by Integers: but Times and DateTimes require a floating point number.

The complication with Dates, DateTimes and Time values is that the data-type does not specify when a cell values has to be interpreted as a Date or Time - it is simply an Integer or Float numbers like any other. A further indirection has to applied so to correctly recognize Dates, DateTimes and Times:

each NUMBER, RK or MULRK value exposes an index referencing the XF (Extended Format) entry associated with the corresponding cell.
each XF record specifies an unique combination of font, alignment, color and so on, however a further indirection specifies the corresponding FORMAT entry
each FORMAT record specifies an output format, such as M/D/YY, h:mm:ss AM/PM or M/D/YY h:mm: and this finally give us a good chance to guess which cell values are intended to represent Date/Time values.
Both XF and FORMAT records are globally stored at the Workbook level, and represent ordered arrays.

If you haven't yet given up, if you aren't yet become totally mind-boggled, and if you are still awake and conscious, then you now know how .xls files are internally organized and structured.
*/
}
//______________________________________________________________________________
bool      Workbook_Excel_xlslib::Sheet::set_cell_bool     (nat16 col, nat32 row, bool value)
{  if (!worksheet_out) return 0; /* cannot set to readonly file */               //130401
   return worksheet_out->boolean((unsigned32_t)row, (unsigned32_t)col,value, /* pxformat */ NULL) != NULL;
}
//______________________________________________________________________________
sint32    Workbook_Excel_xlslib::Sheet::set_cell_integer30  (nat16 col, nat32 row, sint32 value)
{  if (!worksheet_out) return 0; /* cannot set to readonly file */               //130401
   return worksheet_out->number((unsigned32_t)row,(unsigned32_t)col
      ,(signed32_t) value, /* pxformat */NULL) != NULL;
}
//______________________________________________________________________________
float64   Workbook_Excel_xlslib::Sheet::set_cell_number   (nat16 col, nat32 row, float64 value,uint8 precision)
{  //NYI xlslib_core::xf_t pxformat();  will need the format to set the precision
   // it is unclear how to use the xf_t object
   if (!worksheet_out) return 0; /* cannot set to readonly file */               //130401
   xlslib_core::format_number_t format = precision == 2 ? xlslib_core::FMT_NUMBER2 : xlslib_core::FMT_GENERAL;
   return worksheet_out->number((unsigned32_t)row,(unsigned32_t)col,(double)value, format,/*& pxformat*/  NULL) != NULL;
}
//______________________________________________________________________________
int32     Workbook_Excel_xlslib::Sheet::set_range_date    (const char *range, const CORN::Date_const &date_value)
{  assert(false); // NYI  xlslib does not facilitate named ranges
   return 0;
}
//______________________________________________________________________________
bool      Workbook_Excel_xlslib::Sheet::set_range_bool    (const char *range, bool value)
{  assert(false); // NYI  xlslib does not facilitate named ranges
   return 0;
}
//______________________________________________________________________________
sint32    Workbook_Excel_xlslib::Sheet::set_range_integer30 (const char *range, sint32 value)
{  assert(false); // NYI  xlslib does not facilitate named ranges
   return 0;
}
//______________________________________________________________________________
float64   Workbook_Excel_xlslib::Sheet::set_range_number  (const char *range, float64 value,uint8 precision)
{  assert(false); // NYI xlslib does not facilitate named ranges
   return 0;
}
//______________________________________________________________________________
bool      Workbook_Excel_xlslib::Sheet::set_range_color   (const char *range,nat8 red,nat8 green, nat8 blue)
{  assert(false); // NYI  xlslib does not facilitate named ranges
   return 0;
}
//______________________________________________________________________________
const std::string &Workbook_Excel_xlslib::Sheet::set_cell_label   (nat16 col, nat32 row, const std::string &value)
{  if (worksheet_out)                                                            //130526
   worksheet_out->label((unsigned32_t)row, (unsigned32_t)col,value, /*pxformat */NULL);
   return  value;
}
//______________________________________________________________________________
const std::wstring &Workbook_Excel_xlslib::Sheet::set_cell_label_wstring
(nat16 col, nat32 row, const std::wstring &value)
{  if (worksheet_out)                                                            //130526
   worksheet_out->label((unsigned32_t)row, (unsigned32_t)col,value, /*pxformat */NULL);
   return  value;
}
//_2013-09-01__________________________________________________________________/
const std::string &Workbook_Excel_xlslib::Sheet::set_range_label  (const char *range, const std::string &value)
{  assert(false); // NYI xlslib does not facilitate named ranges
   return value;
}
//______________________________________________________________________________
const std::wstring &Workbook_Excel_xlslib::Sheet::set_range_label_wstring(const char *range, const std::wstring &value)
{  assert(false); // NYI xlslib does not facilitate named ranges
   return value;
}
//_2013-09-06__________________________________________________________________/
const std::string &Workbook_Excel_xlslib::Sheet::set_range_formula(const char *range, const std::string &formula)
{  assert(false); // NYI  xlslib does not facilitate named ranges
   return formula;
}
//______________________________________________________________________________
      // Note I am not sure precision was used in cell records (maybe on of the attributes)
      // In later versions of Excel there is a reference to XF records.
      // The following are for getting data in the sheet.
sint32 Workbook_Excel_xlslib::Sheet::get_cell_integer30(nat16 col, nat32 row) const
{
   #if (__BCPLUSPLUS_ > 0x0600)
      // NYI for BDS
   xls::cellContent cell_data = in_workbook->GetCell
      ((nat32)index,  row+1,  col+1);// uses 1 based indexing!
   return cell_data.val.e;
   #else
   return 0; /// NYI
   #endif
}
//_2013-04-01______________________________________________get_cell_integer30__/
sint32 Workbook_Excel_xlslib::Sheet::get_range_integer30(const char *range) const
{  assert(false); // NYI libxls does not implement reading ranges
   return 0;
}
//______________________________________________________________________________
float64 Workbook_Excel_xlslib::Sheet::get_cell_number(nat16 col, nat32 row) const
{
   #if (__BCPLUSPLUS_ > 0x0600)
      // NYI for BDS
   xls::cellContent cell_data = in_workbook->GetCell
      ((nat32)index,  row+1,  col+1);	// uses 1 based indexing!
   return cell_data.val.d;
   #else
   return 0; /// NYI
   #endif
}
//_2013-04-01_________________________________________________get_cell_number__/
float64 Workbook_Excel_xlslib::Sheet::get_range_number(const char *range)  const
{  assert(false); // NYI libxls does not implement reading ranges
   return 0;
}
//______________________________________________________________________________
bool Workbook_Excel_xlslib::Sheet::get_cell_bool(nat16 col, nat32 row)     const
{
   #if (__BCPLUSPLUS_ > 0x0600)
      // NYI for BDS
   xls::cellContent cell_data = in_workbook->GetCell
      ((nat32)index,  row+1,  col+1);	// uses 1 based indexing!
   return cell_data.val.b;
   #else
   return false; /// NYI
   #endif
}
//_2013-04-01___________________________________________________get_cell_bool__/
bool Workbook_Excel_xlslib::Sheet::get_range_bool(const char *range)       const
{  assert(false); // NYI libxls does not implement reading ranges

//cellContent			GetCell(uint32_t workSheetIndex, uint16_t row, const char *colStr);		// "A"...."Z" "AA"..."ZZ"

   return 0;
}
//______________________________________________________________________________
#define RGB(r,g,b)          ((nat32)(((nat8)(r)|((nat16)((nat8)(g))<<8))|(((nat32)(nat8)(b))<<16)))
bool      Workbook_Excel_xlslib::Sheet::set_cell_color    (nat16 col, nat32 row,nat8 red,nat8 green, nat8 blue)
{  if (!worksheet_out) return 0; /* cannot set to readonly file */               //130401
   xlslib_core::range* rng = worksheet_out->rangegroup((unsigned32_t) row, (unsigned32_t) col
      ,(unsigned32_t) row, (unsigned32_t) col);
   rng->fontcolor(RGB(red,green,blue));
   return true;
}
//______________________________________________________________________________
const std::wstring &Workbook_Excel_xlslib::Sheet::get_cell_label
(nat16 col, nat32 row, std::wstring &label)                                const
{
   #if (__BCPLUSPLUS_ > 0x0600)
      // NYI for BDS
   xls::cellContent cell_data = in_workbook->GetCell
      ((nat32)index,  row+1,  col+1);	// uses 1 based indexing!
   #if XLS_WIDE_STRINGS == 0
   string_to_wstring(cell_data.str,label);
   #else
   label = cell_data.str;
   #endif
   // NYI for BDS
   #endif
   return label; // warning I don't know exactly what xlsString is
}
//______________________________________________________________________________
const std::wstring &Workbook_Excel_xlslib::Sheet::get_range_label (const char *range,std::wstring &label)      const
//1300401 const wchar_t      *Workbook_Excel_xlslib::Sheet::get_range_label (const char *range)      const
{  assert(false); // NYI  xlslib does not facilitate named ranges
   return label;
}
//______________________________________________________________________________
const std::string  &Workbook_Excel_xlslib::Sheet::set_cell_formula(nat16 col, nat32 row, const std::string &formula)
{  assert(false); // NYI
   return formula;
}
//______________________________________________________________________________
bool Workbook_Excel_xlslib::Sheet::clear_cell(nat16 col, nat32 row)
{  return worksheet_out->blank((unsigned32_t)row,(unsigned32_t)col) != NULL;
}
//______________________________________________________________________________
bool Workbook_Excel_xlslib::Sheet::clear_range(const char *range)
{  assert(false); // NYI  xlslib does not facilitate named ranges
   return 0;
}
//______________________________________________________________________________
bool Workbook_Excel_xlslib::Sheet::is_just_added_to_workbook()             const
{  return false; // Not needed in this implementation assert(false); // NYI
}
//______________________________________________________________________________
      // Sheet attributes:
void Workbook_Excel_xlslib::Sheet::freeze_pane(nat16 left_most_column,nat32 top_most_row )
{
  //xlslib does not appear to have a freeze pane
  // we simply do nothing because pane does not preclude a valid sheet
  //NYI assert(false); // NYI
}
//______________________________________________________________________________
const std::string &Workbook_Excel_xlslib::Sheet::get_name(std::string &sheet_name) const
{  sheet_name.assign(name);
   return sheet_name;
}
//______________________________________________________________________________
      //NYI uint8 get_index() = 0;  // the sheet tab index (0 based).
      
replace with is_key      
const char *Workbook_Excel_xlslib::Sheet::get_key()                        const
{  return name.c_str();
}
//______________________________________________________________________________
nat32 Workbook_Excel_xlslib::Sheet::get_first_define_row()                 const
{  assert(false); // NYI xlslib does not implement reading files
   return 0;
}
//______________________________________________________________________________
nat32 Workbook_Excel_xlslib::Sheet::get_first_define_column()              const
{  assert(false); // NYI xlslib does not implement reading files
   return 0;
}
//______________________________________________________________________________
nat32 Workbook_Excel_xlslib::Sheet::get_last_define_row()                  const
{  assert(false); // NYI xlslib does not implement reading files
   return 0;
}
//______________________________________________________________________________
nat32 Workbook_Excel_xlslib::Sheet::get_last_define_column()               const
{  assert(false); // NYI xlslib does not implement reading files
   return 0;
}
//______________________________________________________________________________
Workbook::Sheet *Workbook_Excel_xlslib::provide_sheet(const std::string &sheet_name)
{  Workbook::Sheet * sheet = (Workbook::Sheet *)sheets.find_string(sheet_name);
   if (!sheet)
   {  Workbook_Excel_xlslib::Sheet *sheet_xlslib = 0;                            //130401
      if (openmode == std::ios_base::out)                                        //130401
      {  xlslib_core::worksheet *new_worksheet = workbook_out->sheet(sheet_name);
         sheet_xlslib = new Workbook_Excel_xlslib::Sheet(new_worksheet,sheet_name);
      }
      #if (__BCPLUSPLUS_ > 0x0600)
      // NYI for BDS
      else                                                                       //130401
      {  xls::xlsWorkSheet *new_worksheet = 0;
         for (nat32 s = 0; s < workbook_in->GetSheetCount() && (!sheet_xlslib); s++) //130401
         {  // Give the C example the sheets are indexed from 0
            //xlsString wb_sheet_name = workbook_in->GetSheetName(s);
            if (sheet_name == workbook_in->GetSheetName(s))                      //130401
               sheet_xlslib = new Workbook_Excel_xlslib::Sheet
                  (workbook_in,(nat16)s,sheet_name);                             //130401
         }
         // If
      }
      #endif
      CORN::Item /*180101 Association*/ *assos = sheet_xlslib;
      sheets.append(assos /*sheet_xlslib*/);
      sheet = sheet_xlslib;
   }
   return sheet;
}
//______________________________________________________________________________
const std::string &Workbook_Excel_xlslib::get_name(std::string &return_name) const
{  // I don't know how to get the workbook name using xlslib
   // so I simply return the unqualified filename
   CORN::wstring_to_string(filename_XLS.get_name(),return_name);
   return return_name;
}
//______________________________________________________________________________
Workbook_Excel_xlslib::~Workbook_Excel_xlslib()
{  delete workbook_out;
   #if (__BCPLUSPLUS_ > 0x0600)
      // NYI for BDS
   delete workbook_in;                                                           //130401
   #endif
}
//______________________________________________________________________________
bool Workbook_Excel_xlslib::save(bool display_alerts)                 stream_IO_
{  // display_alerts is not applicable in this implementation
   if (!workbook_out) return false;                                              //130401
   int errors = workbook_out->Dump(filename_XLS.c_str());
   return !errors;
}
//_2011-12-15___________________________________________________________________
bool Workbook_Excel_xlslib::save_as
(const std::wstring &filename,bool display_alerts)                    stream_IO_
{  // Saving as a different file type is not applicable in this implementation
   // display_alerts is not applicable in this implementation
   if (!workbook_out) return false;                                              //130401
   std::string filename_str; CORN::wstring_to_string(filename,filename_str);      //140516
   int errors = workbook_out->Dump(filename_str);
   return !errors;
}
//_2011-12-15___________________________________________________________________
// Methods in xlslib that are could be applicable to this implementation
// sheet::error
// sheet::note  (comment?)
//______________________________________________________________________________
} // namespace CORN

