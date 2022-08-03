#ifndef aggregate_UEDsH
#define aggregate_UEDsH
#include "UED/library/database_file.h"

namespace UED
{
typedef nat32 Record_count;
//______________________________________________________________________________
class Aggregator
{public:

   enum Mode {merge, add, average };

      // Merge copies all records from the source to the target.
      // Subsequent calls will append all records from the source
      // For CropSyst, this is used to combined season and harvest files

      // Add copies all records from the source to the target.
      // If the record with matching record header signature already exists
      // in the target, the corresponding source's time step value is added to the target

      // Average works like add,
      // however when the finalize() method is called, the average of each
      // timestep value is set in the target (replacing the added value.
      // where we want to included both sets of records.
      // Note that the finalize method is called automatically
      // when the database file is closed/saved.
      // For CropSyst This is used to aggregate annual files.

 protected:
   CORN::Unidirectional_list tally_records;
   Mode mode ;
   UED::Database_file        target;
 public: // These methods are for existing files
   Aggregator(Mode mode = merge, const char *target_filename = 0,bool _auto_float16=true);
   Record_count append_source(const UED::Database_file& source);
   Record_count append_source_file (const char *source_ued_filename);
   bool finalize();
      // This is used with average mode.
      // The target data records has sums of each of the data values.
      // The target data values are each divided by the count
      // of each data value added from all the appended sources
      // to give an average value.
      // The destructor // will automatically call the finalize()
      // method before saving all the data values.
      // The finalize method is provided to allow the average to be used/provided
      // before the target is closed.
      // This should only be called once after all the sources have been appended.
 protected:
   bool include_record(const Record_base *source_record)            modification_;
};
//_2014-01-14___________________________________________________________________
} //namespace UED

#endif
