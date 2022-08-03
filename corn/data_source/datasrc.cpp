#include "corn/data_source/datasrc.h"
#include "corn/data_source/datarec.h"
//______________________________________________________________________________
namespace CORN {
//______________________________________________________________________________
bool Data_source_abstract::get(modifiable_ Data_record &data_rec)
{
   data_rec.get_start();                                                         //010109
   if (!data_rec.has_structure())
      data_rec.expect_structure(false);                                          //161023
   return false;
   // We return false because this interface does not
   // actually fetch the data, it only set up the the structure.
}
//______________________________________________________________________________
bool Data_source::get_next(Data_record &data_rec)
{  if (!data_rec.has_structure())
      data_rec.expect_structure(false);
   return false;
   // We return false because this interface does not
   // actually fetch the data, it only set up the the structure.
}
//______________________________________________________________________________
bool Data_source_abstract::set
(Data_record &data_rec
,bool         append)                                                            //150502
{  modified = true;
   bool result = false;
   data_rec.set_start();
   if (!data_rec.has_structure())
      data_rec.expect_structure(true);
   result = set_data(data_rec,append);                                           //150502
   data_rec.set_end();
   // Not may want to delete structure here (set VV_File::set_data())
   if (indexer)
      data_rec.notify_indexer(*indexer);
   return result;
}
//______________________________________________________________________________
} // namespace CORN

