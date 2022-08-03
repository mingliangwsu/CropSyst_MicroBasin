#ifndef import_export_tableH
#define import_export_tableH
#include "corn/tabular/tabular_text.h"
#include "corn/OS/directory_entry_name.h"
//___________________________________________________________________________
namespace CORN { namespace MicroSoft { namespace Access {
struct Import_export_table_format
: public extends_ Common_tabular_file_format                                     //170328
{public:
   Import_export_table_format();
};
//_2016-10-13___________________________________________________________________
class Import_export_table
: public CORN::Tabular_text_file
{  CORN::Dynamic_array<nat32>    NA_column_widths; // Not applicable
   CORN::Dynamic_array<nat32>    NA_column_start;  // Not applicable
 public:
   Indexer           *indexer_known;
   CORN::Data_record *record_for_indexing_owned;
 public:
   Import_export_table
      (const CORN::OS::File_name &filename
      ,bool               keep_read_records_in_memory
      ,Indexer           *optional_indexer_known = 0
      ,CORN::Data_record *record_for_indexing_given = 0);                        //111024
   virtual ~Import_export_table();
   bool goto_file_position(nat32 file_pos)                          performs_IO_;
};
//___________________________________________________________________________
 } } } //namespace CORN MicroSoft Access
#endif
