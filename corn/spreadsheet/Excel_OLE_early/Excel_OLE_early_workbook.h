#ifndef Excel_OLE_early_workbookH
#define Excel_OLE_early_workbookH
#include <vcl.h>
#pragma hdrstop
#include "corn/spreadsheet/workbook.h"
#include "Excel_2K_SRVR.h"
#include "corn/OS/directory_entry_name_concrete.h"
// Rows and columns are all 0 base indexed
namespace CORN
{
//______________________________________________________________________________
class Excel_OLE_earlybinding_workbook : public Workbook
{
   class Worksheet : public Workbook::Sheet
   {
//use Get_Name      AnsiString    name; // name of the workbook
      // (note this is only temporary, the name should be available from vWorksheet
   public: // public because can't seem to pass these STUPID variants
      TExcelWorksheet *excelworksheet;  // owned by this
      bool just_added_to_workbook;
   public:
      Worksheet(TExcelWorksheet *_excelworksheet,bool _just_added_to_workbook);
      virtual ~Worksheet();
      // The following are for setting data in the sheet
      virtual int32    set_cell_integer30  (nat16 col, nat32 row, int32 value) ;
      virtual bool   set_cell_bool(nat16 col, nat32 row, bool value) ;

      virtual float64  set_cell_number   (nat16 col, nat32 row, float64 value,uint8 precision) ;
      virtual const std::string &set_cell_label (nat16 col, nat32 row, const std::string &value) ;
      virtual const std::wstring &set_cell_label_wstring(nat16 col, nat32 row, const std::wstring &value); //130905
      virtual int32    set_cell_date(nat16 col, nat32 row, const CORN::Date &date_value) ;

      // Range can be either cell coded coordinate i.e A1, named cell, or coded range i.e. A1..Z999
      virtual const std::string &set_range_label(const char *range, const std::string &value);
      virtual const std::wstring &set_range_label_wstring (const char *range, const std::wstring &value); //130905
      virtual int32     set_range_date          (const char *range, const CORN::Date &date_value /* int32 value*/ );
      virtual bool      set_range_bool          (const char *range, bool value) ;
      virtual int32     set_range_integer30     (const char *range, int32 value) ;
      virtual float64   set_range_number        (const char *range, float64 value,nat8 precision);
      virtual bool      set_range_color         (const char *range,nat8 red,nat8 green, nat8 blue);  //110815
      virtual const std::string &set_range_formula(const char *range, const std::string &formula);   //110815
      // The following are for getting data in the sheet
      virtual int32        get_cell_integer30  (nat16 col, nat32 row)      const;
      virtual bool         get_cell_bool(nat16 col, nat32 row)             const;//130328
      virtual float64      get_cell_number   (nat16 col, nat32 row)        const;
      inline virtual int32        get_cell_date(nat16 col, nat32 row)             const { return 0;} ; // NYI!!!
      virtual int32        get_range_integer30(const char *range)          const;//111001
      virtual bool         get_range_bool(const char *range)               const;//130328
      virtual float64      get_range_number(const char *range)             const;
      virtual const std::wstring &get_cell_label  (nat16 col, nat32 row,std::wstring &label_return)   const;          //130402_111001
      virtual const std::wstring &get_range_label (const char *range,std::wstring &label_return)      const;          //130402_111001
      virtual bool set_cell_color(nat16 col, nat32 row,nat8 red,nat8 green, nat8 blue);  //110815
      virtual const std::string &set_cell_formula(nat16 col, nat32 row, const std::string &formula);  //110815
      inline virtual bool is_cell_empty(nat16 col, nat32 row)                   const
      {  assert(false);
         return false;
        // Note this is not yet implemented.
      }
      virtual bool clear_cell(nat16 col, nat32 row)                        ;
      virtual bool clear_range(const char *range)                          ;

      inline virtual bool is_just_added_to_workbook()                             const { return just_added_to_workbook;}
      // returns true if the cell has no data

      // Sheet attributes:
      virtual void freeze_pane(nat16 left_most_column,nat32 top_most_row ) ;
      virtual const std::string &get_name(std::string &sheet_name) const;   // the name of the sheet
      //NYI  uint8       get_index() ;  // the sheet tab index (0 based).
      virtual const char *get_key() const;  replace with is_key
      char *cell_name(nat16 col, nat32 row,char *name) const;
   private: //101229  These might not be needed in this class
      virtual nat32 get_first_define_row()     const {return 0; }
      virtual nat32 get_first_define_column()  const {return 0; }
      virtual nat32 get_last_define_row()      const {return 0; }
      virtual nat32 get_last_define_column()   const {return 0; }
   };
private:
   TComponent        *owner;
   TExcelApplication *excelapplication_known;  // not owned
   TExcelWorkbook    *excelworkbook;
public:
   CORN::OS::File_name_concrete filename_XLS;                                         //130328
public:
   Excel_OLE_earlybinding_workbook
      (const CORN::OS::File_name   &_workbook_filename_XLS// usually fully qualified or relative to current directory
      ,TExcelApplication      *_excelapplication_known
      ,TComponent             *_owner/* = 0*/);
   virtual ~Excel_OLE_earlybinding_workbook();
   virtual Sheet *provide_sheet(const std::string &sheet_name)    modification_; //110711
   virtual bool copy_sheet
      (const std::string &from_sheet_name
      ,const std::string &to_sheet_name)                          modification_; //110711
   virtual const std::string &get_name(std::string &return_name)          const;
   virtual bool save(bool display_alerts = false)                  performs_IO_;
   virtual bool save_as(const std::wstring &filename, bool display_alerts = false) performs_IO_;
   virtual bool save_as_format(const std::wstring &filename,XlFileFormat format,bool display_alerts = false) performs_IO_;
   virtual bool close()                                            performs_IO_;
};
//______________________________________________________________________________
} // namespace CORN
#endif

