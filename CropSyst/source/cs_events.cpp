#  include "cs_events.h"
#  include "corn/data_source/datarec.h"
namespace CropSyst {                                                             //131101
//______________________________________________________________________________
bool Event::process_matching_date
(Land_unit_simulation_VX &associated_sim,
const CORN::Date_const &process_date
,std::ostream          &log_stream)                                              //991130
{  bool processed = false;
   if (date_matches(process_date) && (! deleted))                                //000317
   {  if (process(associated_sim,process_date))
      {  processed = true;
         log(log_stream,false);
         if (!get_date().is_relative())                                          //170525
            deleted = true;  // check if reached
   }  }
   return processed;
}
//_2001-12-07___________________________________________________________________
void Event::synchronize_to  // check used
(const Synchronization  &from_sync
,const CORN::Date_const &to_date)                                                //020629
{
   if (begin_sync.sync_type_matches(from_sync))                                  //030608
      date.set_date32(begin_sync.determine(to_date));                            //170525_120314_030606
}
//_2001-12-07___________________________________________________________________
} // namespace CropSyst                                                          //131101
// line count
// 060810 136
// 100316  57
// 140126  41


