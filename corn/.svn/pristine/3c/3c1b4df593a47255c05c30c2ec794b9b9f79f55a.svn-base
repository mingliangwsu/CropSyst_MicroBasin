#ifndef cell_reader_Excel_XLSH
#define cell_reader_Excel_XLSH
#include "corn/format/binary/binary_record_file.h"
#include "corn/format/spreadsheet/biffcode.h"
#include "corn/format/binary/CDBF.h"
#include "corn/OS/directory_entry_name.h"

// This version of Cell_reader reads  BIFF formated documents
// It should handle any BIFF file.
// Probably could also incorporate LOTUS 1-2-3 since it is very similar to BIFF2

// This class only reads data cells.
// It could be expanded to a more general purpose workbook reader for all BIFF records.

//______________________________________________________________________________
namespace CORN {
class File_name;
class Cell_receiver;
class BIFF8_rec_SST;
class BIFF_record;
//______________________________________________________________________________
class Cell_reader_Excel_XLS
: public Compound_file_binary_format
{
private:
   BIFF8_rec_SST  *shared_string_table;
   BIFF_Format format;   // Initially the format is unknown until we read the BOF record
   nat32 last_formula_string_row;
   nat32 last_formula_string_col;
   nat16 current_sheet_index;  bool sheet0_encountered;
public:
   bool dates_based_1904; // Set when the DATEMODE (AKA 1904) record is encountered
public:
   Cell_reader_Excel_XLS(const CORN::OS::File_name &file_name);
   virtual uint32 read(Cell_receiver &receiver);
private: // Binary_record_file_dynamic implementations
   virtual Binary_record *instanciate_record(Record_code code)             const; // PURE
   bool read_and_process_record(Cell_receiver &receiver, BIFF_record *record);
};
//______________________________________________________________________________
}; // namespace CORN
#endif
