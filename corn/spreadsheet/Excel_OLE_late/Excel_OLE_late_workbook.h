#ifndef EXCEL_OLE_LATE_WORKBOOKH
#define EXCEL_OLE_LATE_WORKBOOKH
#include <vcl.h>
#include <corn/spreadsheet/workbook.h>
#include <utilcls.h>
//______________________________________________________________________________
namespace CORN
{
class Excel_OLE_latebinding_workbook : public Workbook
{
   class Worksheet : public Workbook::Sheet
   {
      std::string    name; // name of the workbook
      // (note this is only temporary, the name should be available from vWorksheet
   public: // public because can't seem to pass these STUPID variants
      Variant vWorksheet;
   public:
      Worksheet(Variant &ivWorksheet,const char *i_name);
      // The following are for setting data in the sheet
      virtual int16    set_cell_integer  (uint16 col, uint32 row, sint16 value) ;
      virtual float64  set_cell_number   (uint16 col, uint32 row, float64 value) ;
      virtual const std::string &set_cell_label (uint16 col, uint32 row, const std::string &value) ;
      virtual int32    set_cell_date(uint16 col, uint16 row, const CORN::Date &date_value /*int32 value*/) { return 0;} ; // NYI!!!

      // The following are for getting data in the sheet
      virtual sint16    get_cell_integer  (uint16 col, uint32 row);
      virtual float64  get_cell_number   (uint16 col, uint32 row) ;
      virtual const std::wstring &get_cell_label  (nat16 col, nat32 row,std::wstring &label)   const;
      virtual const std::wstring &get_range_label (const char *range,std::wstring &label)      const;
      virtual int32 get_cell_date(uint16 col, uint32 row)  { return 0;} ; // NYI!!!
      virtual bool is_cell_empty(uint16 col, uint32 row) const
      { return false;
        // Note this is not yet implemented.
      }
      // returns true if the cell has no data

      // Sheet attributes:
      virtual void freeze_pane(uint16 left_most_column,uint32 top_most_row ) ;
      virtual const std::string &sheet_nameget_name(std::string &sheet_name) const;   // the name of the sheet
//NYI       uint8       get_index() ;  // the sheet tab index (0 based).
      char *cell_name(uint16 col, uint32 row);
   };
private:
   Variant vXLWorkbook;
   AnsiString    name; // name of the workbook
   //   (note this is only temporary, the name should be available from vXLWorkbook
public:
   Excel_OLE_latebinding_workbook();
   virtual ~Excel_OLE_latebinding_workbook();
   virtual Sheet *provide_sheet(const std::string &sheet_name);
   inline virtual const std::string &sheet_nameget_name(std::string &sheet_name) const;
};
//______________________________________________________________________________
} // namespace CORN
#endif

