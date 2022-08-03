#  include "corn/math/statistical/stats_best.h"

#error no longer used (I think this may have been used by ClimGen at one time.
// Dont delete this until I have resurrected ClimGen 180408

namespace CORN {
//______________________________________________________________________________
Best_statistical_data_set::Best_statistical_data_set(nat32 _maximum_sample_size, bool _highest_mode)
: Statistical_data_set()
, maximum_sample_size(_maximum_sample_size)
, highest_mode(_highest_mode)
{
};
//______________________________________________________________________________
/* we will resized just before recompute
this way we don't have to sort as we fill up the dataset
float32 Best_statistical_data_set::append(float32 value)
{
   Statistical_data_set::append(value);
   sort(highest_mode);
   if (count > maximum_sample_size)
      reallocate_array(maximum_sample_size);
};
*/
//______________________________________________________________________________
void Best_statistical_data_set::recompute()                        modification_
{  sort(highest_mode ? DESCENDING : ASCENDING);
   // if highest mode, we want to sort (descending) keeping the
   // highest values at the bottom of the array,
   // then we can just resize which will simply eliminate the lowest values from the end of the array.
   if (get_count() > maximum_sample_size)
      reallocate_array(maximum_sample_size);
   Statistical_data_set::recompute();
};
//______________________________________________________________________________
}; // namespace CORN

