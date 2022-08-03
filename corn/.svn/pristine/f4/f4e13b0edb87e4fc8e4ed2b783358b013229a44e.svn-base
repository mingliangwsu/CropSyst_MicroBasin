#ifndef worksheet_ExcelH
#define worksheet_ExcelH

#include "corn/format/excel/workbook_Excel.h"
#include "corn/format/excel/rec_set.h"
#include "corn/format/excel/BIFF_record.h"
#include "corn/container/enumlist.h"
#include "corn/data_type_enum.h"
#include <assert.h>

// Cell rows and columns are 0-based indexed
// (although in Excel spreadsheets the are numbered from 1 and A).

namespace CORN {

class BIFF_cell_record;
class BIFF_rec_ROW_abstract;
//______________________________________________________________________________
class Excel_worksheet
: public implements_ CORN::Workbook::Sheet
{
private:
   //___________________________________________________________________________
   class Row_set
   : public CORN::Enumeration
   {
      BIFF_Format format;   // This is provided when the sheet is created
      BIFF_rec_ROW_abstract  *row_record;

      Enumeration_list    cell_records;    // list of cell records (actually Binary_record_index_node_dynamic)
/*    Cell records that appear in BIFF5/BIFF7/BIFF8 include (presumably in any order) as encountered by row.
      ARRAY    An array-entered formula
      BLANK    An empty cell
      BOOLERR  A Boolean or error value
      FORMULA  A cell formula, stored as parse tokens
      LABEL    A string constant
      LABELSST String constant that uses BIFF8 shared string table (new to BIFF8)
      NUMBER   An IEEE floating-point number
      MULBLANK Multiple empty cells (new to BIFF5)
      MULRK    Multiple RK numbers (new to BIFF5)
      RK       An RK number
      RSTRING  Cell with character formatting
      SHRFMLA  A shared formula (new to BIFF5)
      STRING   A string that represents the result of a formula
*/
   public:
       Row_set(nat32 row_number, BIFF_Format _format);
         // This constructor is used when creating new sheet
       Row_set(BIFF_rec_ROW_abstract  *_row_record);
         // This constructor is used when loading file
      inline virtual bool is_key_nat32(nat32 key)              affirmation_;  //180820
      virtual nat32 get_key_nat32() const;

      virtual void commit(Excel_workbook &workbook);
#ifdef DISABLED
101127
This class is deprecated and is not longer used for reading,
instead, use Cell_reader
      const BIFF_cell_record *get_cell(uint16 col)                         const;
#endif
   Cell_numeric *provide_numeric_record(uint16 col,Data_type intended_value_type)    provision_;
      // return 0 if the cell is not numeric
   Cell_textual *provide_textual_record(uint16 col) provision_;
   private:
      inline bool take_record_node(Binary_record_index_node_dynamic *rec_node)
      {  cell_records.append(rec_node);
         return true;
      }
   };
   //___________________________________________________________________________
public:
   BIFF_Format format;   // This is provided when the sheet is created
public:
   // The worksheet maintains the boundsheet until the data is commited.
   BIFF_rec_BOUNDSHEET_common *boundsheet; // Will be 0 for BIFF4<
   // Distinguished records that will appear in the sheet record set
   BIFF_rec_BOF         *bof;
   Unidirectional_list   arbitrary_records;
   // The list of records (actually Binary_record_index_node_dynamic)
   // specific to the worksheet which I haven't yet implemented as specific records
   // It appears that these records all fall between the bof record and
   // the dimensions
//NYI   BIFF_rec_INDEX       *index;    // immediately follows the bof record
//NYI    calcmode
//NYI    calccount
//NYI    refmode
//NYI    iteration
//NYI    delta
//NYI    saverecalc
//NYI    printheaders
//NYI    printgridlines
//NYI    guts
//NYI    defaultrowheight
//NYI    country
//NYI    wsbool
//NYI    header
//NYI    footer
//NYI    hcenter
//NYI    vcenter
//NYI    setup
//NYI    defcolwidth

   provided_ BIFF_rec_DIMENSIONS  *dimensions;
   contribute_ Enumeration_list row_sets;    // list of  Row_set
   Unidirectional_list   DBCELL_records;
      // This will be a list. I believe the ROW record was introduces in BIFF5 or BIFF7
      // Excel doesn't appear to need them
      // A ROW record describes a single row on an Excel sheet.
      // ROW records and their associated cell records occur in blocks of up to 32 rows.
      // Each block ends with a DBCELL record.
      // These records are not necessary (at least for early versions of Excel)
      // Excel stores cell records in blocks with no more than 32 rows.
      // Each row that contains cell records has a corresponding ROW record in the block,
      // and each block contains a DBCELL record at the end of the block.

      // This class will organize the cell records in these block when writing.
   provided_ BIFF_rec_WINDOW1_common    *window1;   // I am not sure if window1 occured in every sheet prior to BIFF7, In later versions, it appears that window1 only occurs in workbook global section
   provided_ BIFF_rec_WINDOW2_common    *window2;
   provided_ BIFF_rec_PANE                 *pane;
   provided_ BIFF_rec_SELECTION            *selection; // WARNING this should be a list There may be more than one selection
   Unidirectional_list            FRT_records;   // FRT records for this sheet
      // For BIFF8 (Excel 97) or later Future record types.
      // When Excel 97 or later encounters unrecognized FRT records,
      // it writes them to the record stream at the end of the current record block.
      // (I am presuing the record block is the bof-eof)
      // (Presume continue records would be in this list)
   BIFF_rec_EOF         *eof;          // Should remain 0 until commited.
protected:  // The following methods can be used to insure that required
            // records exist before attempting to set values they may contain or commit
   void create_bof();
//NYI   void create_index();
   void create_dimensions();
   void create_window1();
   BIFF_rec_PANE     &provide_pane()                                  provision_;
   BIFF_rec_WINDOW2_common  &provide_window2()                        provision_;
   void redimension_if_necessary(uint16 col, nat32 row);
   // This is used to make sure that an added cell will update the dimensions if necessary.
protected:
   Row_set *provide_row(nat32 row)                                   provision_;
   Row_set *get_row(nat32 row)                                                 ;
#ifdef DISABLED
101127
This class is deprecated and is no longer used for reading,
instead, use Cell_reader
   BIFF_cell_record *get_cell(uint16 col, nat32 row);
   // Returns the record as the specified cell.
   // Returns 0 if cell has not been set.
#endif
   inline bool is_in_workbook()
   { return boundsheet > 0;
   // Versions of excel with boundsheets support multiple sheets
   };
 public:  // Association implementation
   virtual const char *get_key()                                           const;
 public:  // Cell setting in current work sheet
   // Each of these cell setting methods will first see if there
   // is a record for the cell, if so, it will be deleted
   // Then the cell record will be created for the new value and set.
   //120115 virtual sint16 set_cell_integer(uint16 col, nat32 row, sint16 value);
   virtual int32 set_cell_integer30(uint16 col, nat32 row, int32 value);        //120115
   virtual const std::string &set_cell_label(uint16 col, nat32 row , const std::string &value);
   virtual const std::wstring &set_cell_label_wstring(nat16 col, nat32 row, const std::wstring &value); //131018
   virtual float64 set_cell_number(uint16 col, nat32 row, float64 value,uint8 precision);
   virtual int32   set_cell_date(uint16 col, nat32 row, const CORN::Date_const &date_value);
      virtual bool set_range_color(const char *range,nat8 red,nat8 green, nat8 blue) { assert(false); return false; }; //NYI //110815
      virtual const std::string &set_range_formula(const char *range, const std::string &formula){ assert(false); return formula; }; //NYI    //110815
      virtual bool set_cell_color(nat16 col, nat32 row,nat8 red,nat8 green, nat8 blue){ assert(false); return false; }; //NYI  //110815
      virtual const std::string &set_cell_formula(nat16 col, nat32 row, const std::string &formula){ assert(false); return formula; }; //NYI  //110815

   virtual bool   set_range_bool     (const char *range, bool value);
   virtual bool   set_cell_bool(nat16 col, nat32 row, bool value);

   virtual const std::string &set_range_label (const char *cell_name, const std::string &value) { assert(false); return value; }; //NYI
   virtual const std::wstring &set_range_label_wstring (const char *range, const std::wstring &value){ assert(false); return value; }; //NYI

   virtual int32    set_range_date(const char *cell_name, const CORN::Date_const &date_value) { assert(false); return 0; }; //NYI
   //120115 virtual sint16   set_range_integer  (const char *cell_name, sint16 value) { assert(false); return value; }; //NYI
   virtual int32   set_range_integer30  (const char *cell_name, int32 value) { assert(false); return value; }; //120115
   virtual float64  set_range_number   (const char *cell_name, float64 value,uint8 precision) { assert(false); return value; }; //NYI

   virtual bool is_just_added_to_workbook()                         affirmation_ { assert(false); return false; }; // NYN

   virtual int32       get_cell_integer30(uint16 col, nat32 row)          const;//120115
   //120115virtual sint16       get_cell_integer(uint16 col, nat32 row)           const;
   virtual float64      get_cell_number (nat16 col, nat32 row)             const;
   // virtual const char  *get_cell_label  (uint16 col, nat32 row)           const;
   virtual const std::wstring &get_cell_label  (nat16 col, nat32 row,std::wstring &label)   const;          //130402_111001
   virtual const std::wstring &get_range_label (const char *range,std::wstring &label)      const;          //130402_111001
   /*130402
   virtual const wchar_t *get_cell_label  (nat16 col, nat32 row)            const;          //111001
   */
   //120115 virtual sint16   get_range_integer     (const char *range)              const { assert(false); return 0; }; //NYI
   virtual int32   get_range_integer30    (const char *range)              const { assert(false); return 0; }; //NYI
   virtual const wchar_t *get_range_label (const char *range)              const { assert(false); return 0; }; //NYI
   virtual float64 get_range_number       (const char *range)              const { assert(false); return 0; }; //NYI

   virtual bool         get_cell_bool(nat16 col, nat32 row)                const;//130401
   virtual bool         get_range_bool(const char *range)                  const { assert(false); return 0; }; //NYI

   virtual bool clear_cell(nat16 col, nat32 row)                                 { assert(false); return 0; }; //NYI
   virtual bool clear_range(const char *range)                                   { assert(false); return 0; }; //NYI

#ifdef DISABLED
101127
This is dependent on get_cell which I needed to disable
This class is deprecated and is not longer used for reading,
instead, use Cell_reader
   virtual bool is_cell_empty(uint16 col, nat32 row) const;
      // returns true if the cell has no data
#endif
   virtual void freeze_pane(uint16 left_most_column,nat32 top_most_row );
   virtual const std::string &get_name(std::string &sheet_name)            const ;   // the name of the sheet
public: // Constructors
   Excel_worksheet
      (const std::string &sheet_name
      ,BIFF_rec_BOUNDSHEET_common::Sheet_type sheet_type = BIFF_rec_BOUNDSHEET_common::WORKSHEET
      ,BIFF_Format i_BIFF_version = BIFF8
      ,BIFF_rec_BOUNDSHEET_common::Hidden_state hidden_state = BIFF_rec_BOUNDSHEET_common::VISIBLE);
   inline BIFF_rec_BOUNDSHEET_common *relinquish_boundsheet()
      { return boundsheet; };
   /*
   virtual void relinquish_bof();
   virtual void relinquish_index();
   virtual void relinquish_dimensions();
   virtual void relinquish_window2();
   virtual void relinquish_eof();
   */
   virtual void commit(Excel_workbook &workbook);
public:  // Settings and operations
   void freeze_pane(uint16 i_left_most_column , uint16 i_top_most_row,BIFF_rec_PANE::Panes active_pane = BIFF_rec_PANE::lower_right);
   virtual nat32 get_first_define_row()                            const;
   virtual nat32 get_first_define_column()                         const;  //  Excel only has 16bit column indexes
   virtual nat32 get_last_define_row()                             const;
   virtual nat32 get_last_define_column()                          const;  //  Excel only has 16bit column indexes
   virtual uint16 get_row_count()                                          const;
// private:
//   bool write_cell_record(const Cell_common &BIFF_rec);                          //111011
   private:
      inline bool test_abstract() { return new Excel_worksheet("test"); }
};
//______________________________________________________________________________
} // namespace CORN
#endif

