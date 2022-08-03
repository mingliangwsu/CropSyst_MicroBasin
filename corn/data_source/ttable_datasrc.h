#ifndef CORN_BUILDER_TABLE_DATASRC_H
#define CORN_BUILDER_TABLE_DATASRC_H

#if (__BCPLUSPLUS__ < 0x0570)
#error This class is written for C++ Builder
// For a dbase compatible class for any C++ development environment,
// use dbase_datasrc
#endif

#include "corn/format/datarec.h"
#include "corn/format/datasrc.h"
#include "dbtables.hpp"
// dbtables.hpp is  for C++ builder db table class class TTableType

namespace CORN {

class File_name;  // \corn\file_sys\filename.h CORN::File_name
//______________________________________________________________________________
class TTable_data_source
: public Data_table
{
   TTable *table;
public:
   TTable_data_source(TTable *table);

   virtual bool get(Data_record &data_rec);
// This reads data from the data source at it's current position
// (I.e. current record in the database)
// This abstract method must be provided by a derived class
// If the database is not in a state where is can read any data it returns false.
// If the database could be read, but there were not maching entries (fields)
// then it returns false.
// Returns true if any record entries could be read.
// Examine each data record entry to determine if it was encountered
// in the data source.

   virtual bool set(Data_record &data_rec);
// This writes data from data_rec to this data source.
// Classes derived from Data_record may provide information such
// as the position of the record in the data file an the Data_source
// may then need to position the file pointer before writing the record.
// In classes such as VV_file, a Data_record constitutes all the data in
// a file, consequently the data can be written out to the file.
// Returns true if the record could be written.
// Returns true if there was a problem.
// This abstract method must be provided by a derived class.

   virtual CORN_string label() const;
// This returns a text label that could be used to identify
// The data source being edited.
// It is left to the derived data source class how this text is formatted.
// For VV_file we simply use the fully qualified filename.
// For dBase we could use the filename and the record number  C:\path\file.dbf#123
protected:
   virtual bool create(Data_record &data_rec);
   // Creates the database using Data_record as the prototype
   // It contains VV_entries that have the information necessary to
   // create the fields of the target database
public: // Data_table required methods
   virtual bool   goto_first();
   virtual bool   goto_index(nat32 zero_based_index);
   virtual bool   goto_last();
   virtual bool   goto_next(int32 skip_records = 1);
   // skip records is allowed to be signed

/* 161013 field type is actually format specification,
This isn't actually used by anything anymore
   virtual uint8 get_field_type(const char *field_name);
   // returns the filed type corresponding to VV_entry types
*/

   virtual uint32 get_current_index();
   // returns the index value for the table's current position.
   // For database tables this is the record number
   // For memory tables, this is the memory location or object pointer);
};
//______________________________________________________________________________
} // namespace CORN
#endif

