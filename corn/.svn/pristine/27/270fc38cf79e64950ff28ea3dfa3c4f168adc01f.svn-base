#ifndef data_tableH
#define data_tableH

// This is an abstract for working with with Data base tables
#ifndef datasrcH
#  include "corn/data_source/datasrc.h"
#endif
#ifndef primitiveH
#  include "corn/primitive.h"
#endif

namespace CORN {
//______________________________________________________________________________
class Data_table                 //Should be Data_table_data_source
:public Data_source_abstract
{
public:
   inline Data_table(Indexer *optional_indexer = 0)
      : Data_source_abstract(optional_indexer)                                {}
   inline virtual ~Data_table()                                               {}
   virtual bool   goto_first()                                               =0;
   virtual bool   goto_index(uint32 zero_based_index)                        =0;
   virtual bool   goto_last()                                                =0;
   virtual bool   goto_next(int32 skip_records = 1)                          =0;
      // skip records is allowed to be signed

/*161013 field type is actually format specification,
 it should not be a method of the table read/writer itself
 This actually doesn't appear to be used anywhere anymore so it should be safe to delete
   virtual nat8 get_field_type(const char *field_name)                       =0;
      // returns the field type corresponding to VV_entry types
*/

   virtual nat32 get_current_index()                                         =0;
      // returns the index value for the table's current position.
      // For database tables this is the record number
      // For memory tables, this is the memory location or object pointer);
   virtual nat32 get_record_count()                                          =0;  // cannot be const because we may need to initialize
      // Returns the number of records in the table
      // Includes only data lines, not any headers or pretext.
   virtual nat32 append(Data_record &data_rec)                               =0;
      // This creates a new record at the end of the table and sets data_rec.
      // Returns the record index of the new record that was appended.
   virtual nat32 delete_record()                                             =0;
      // This marks the current record as deleted.
      // usually only a flag is set in the record indicating it is deleted
      // so the record is not actually physically deleted.
   virtual bool reset()                                            stream_IO_=0; //111111
};
//______________________________________________________________________________
}; // namespace CORN

#endif

