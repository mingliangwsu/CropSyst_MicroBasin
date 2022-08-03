#include "aggregate_UEDs.h"

namespace UED
{
//______________________________________________________________________________
class Tally_record
: public CORN::Item
{public:
   Record_base *tally;
 public:
   Tally_record(Record_base *_tally)
      :Item()
      ,tally(_tally)
      {}
};
//______________________________________________________________________________
Aggregator::Aggregator(Mode _mode, const char *target_filename,bool _auto_float16)
: target(target_filename,std::ios::out,_auto_float16)
, mode(_mode)
{}
//______________________________________________________________________________
/* NYN
Aggregator::Aggregator()
: target()
{
}
*/
//______________________________________________________________________________
bool Aggregator::include_record(const Record_base *source_record)  modification_
{  bool included = false;
   switch (source_record->get_code())
   {  case UED_marker_BOF  :
      case UED_marker_EOF  :
      case UED_free_space  :
         // don't includes these special records.
      break;
      default:
         //140119 if (!source_record->deleted/free)
            included = tally_records.append(new Tally_record(source_record->clone()));
      break;
   }
   return included;
}
//______________________________________________________________________________
Record_count Aggregator::append_source(const UED::Database_file& source_const)
{  Record_count appended = 0;

//   source.copy_periods_to_database(target);
   UED::Database_file& source = const_cast<UED::Database_file&>(source_const);   //150804
      // source isn't actually modified, but it call's IO functions that
      // are not const

   for (Record_base* source_record = source.goto_BOF() //source.read_record(std::istream::beg) //150804 goto_BOF()
       ; source_record
       ; source_record = source.goto_next() // source.read_record(std::fstream::cur) //150804 goto_next()
       )
   {
      switch (mode)
      {
         case merge :
               appended += include_record(source_record);
         break;
         case add : case average :
         {  const Binary_data_record_cowl* source_data_record                    //151116
               = dynamic_cast<const Binary_data_record_cowl* >(source_record);
            if (source_data_record) // The UED record is a data record
            {  // search if we have already added a tally for this record type
               FIND_FOR_EACH_IN(found_tally_record,tally_record,Tally_record,tally_records,true,each_record)
               {
                  Binary_data_record_cowl* target_data_record = dynamic_cast<Binary_data_record_cowl* >(tally_record->tally);
                  if (source_data_record && target_data_record) // both are data records
                     if (target_data_record->add_corresponding(*source_data_record))
                        found_tally_record = tally_record;
               } FOR_EACH_END(each_record)
               if (!found_tally_record) // This is if the first such record so create a tally
                  appended += include_record(source_data_record);
            } else // This is a metadata record
               appended += include_record(source_record);
         } break;
      }
   }
   return appended;
}
//______________________________________________________________________________
Record_count Aggregator::append_source_file(const char *source_ued_filename)
{  Database_file source_file(source_ued_filename,std::ios_base::in,false);
   return append_source(source_file);
}
//______________________________________________________________________________
bool Aggregator::finalize()
{
   FOR_EACH_IN(tally_record,Tally_record,tally_records,each_record)
   {
      Binary_data_record_cowl* tally_data_record
         = dynamic_cast<Binary_data_record_cowl* >(tally_record->tally);         //151116
      if ((mode == average) && tally_data_record)
         tally_data_record->finalize_average();
      target.append_record(tally_record->tally,false); //Also include other records
      tally_record->tally = 0;
   } FOR_EACH_END(each_record)
   target.finish();                                                              //140227
   return true;
}
//______________________________________________________________________________
} //namespace UED

