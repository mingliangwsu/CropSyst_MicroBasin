#ifndef workbook_ExcelH
#define workbook_ExcelH
#include "corn/const.h"
#include "corn/spreadsheet/workbook.h"
#include "corn/format/binary/binary_record_file.h"
#include "corn/format/excel/rec_set.h"
namespace CORN {
class Excel_worksheet;
//______________________________________________________________________________
class BIFF34578_rec_STYLE;
//______________________________________________________________________________
class Excel_workbook_global_records
: public BIFF_record_set
{};        // Not currently used, I think I intended this to include all records that were not associated with worksheets, charts, etc..
//______________________________________________________________________________
class Excel_workbook
: public Binary_record_file_dynamic_indexed
, public implements_ Workbook // Interface

{
private: // records
   BIFF_rec_BOF         *bof;       // beginning of workbook global section
   // NYI ADDIN (optional) if present it immediately follows the BOF of the workbook
   BIFF_Format           format;
   BIFF_rec_WINDOW1_common    *window1;                                       // nilable pointer to Binary_record_file_dynamic_indexed records
   BIFF_rec_FONT        *font[5];   // BIFF7 on require font records    // nilable pointer to Binary_record_file_dynamic_indexed records
   BIFF_rec_XF          *xf[22];    // BIFF7 on require XF records;     // nilable pointer to Binary_record_file_dynamic_indexed records
   BIFF34578_rec_STYLE  *style[6];  // NULL for BIFF2 ;  // nilable pointer to Binary_record_file_dynamic_indexed records
   Unidirectional_list   cell_extended_formats;
   Unidirectional_list   style_extended_formats;
   // boundsheets (BIFF5 and later) go here, but the reference to these are currently kept with the Excel_worksheet
   // since the go with the worksheet

   Unidirectional_list   FRT_records;   // FRT records for this workbook global section
      // For BIFF8 (Excel 97) or later Future record types.
      // When Excel 97 or later encounters unrecognized FRT records,
      // it writes them to the record stream at the end of the current record block.
      // (I am presuing the record block is the bof-eof)
      // (Presume continue records would be in this list)
   BIFF_rec_EOF         *eof;          // end of workbook global section
   Bidirectional_list /*180101 Association_list */     worksheets;
   Unidirectional_list   charts;
   Unidirectional_list   arbitrary_records;  // not yet implemented section including  Modules, PivotTable, CompObj, VBA stream, Sumary Info stream
private:  // contributes
   Excel_worksheet      *recent_sheet;  // not owned
   // This is the most recently provided or added sheet.
   // The reference is used to improve sheet lookup speeds because typically
public:
   Excel_workbook
      (const char    *_filename
      ,std::ios_base::openmode _openmode                                         //130401
      ,BIFF_Format    _format = BIFF8);
   // Constructor
   inline virtual ~Excel_workbook();
public:  // Current worksheet method
//NYI   virtual Excel_worksheet &activate(uint8 worksheet_index);
   // If the the specified index does not exists, a new worksheet will be appended.
   // (additional sheets will be created as necessary)
   virtual Workbook::Sheet *provide_sheet(const std::string &sheet_name);  // was get_sheet
      // Activates the named sheet, creating it if it doesn't exist.
   virtual const std::string &get_name(std::string &sheet_name)            const;
public: //
   virtual Excel_worksheet *take_sheet(Excel_worksheet *sheet_to_add);      // was add_sheet
   // Adds the worksheets and activates it.
   virtual void commit();
   // This essentially writes all the records for the workbook in the proper sequence.
public: // Pure methods provided
   virtual Binary_record *instanciate_record(Record_code code)             const;
      // This will create an instance of a record of type specified by code
      // and read the data from the file from the current file position.
      // The record is return
};
//______________________________________________________________________________
} // namespace CORN
#endif

