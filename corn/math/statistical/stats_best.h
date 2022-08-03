#ifndef stats_bestH
#define stats_bestH

#error no longer used (I think this may have been used by ClimGen at one time.
// Dont delete this until I have resurrected ClimGen 180408

// If this is still needed   Use new Statistical_sample_with_dataset

#ifndef statsH
#  include "corn/math/statistical/stats.h"
#endif
// This statistical analysis is a normal statistical analysis
// but it only keeps a sample of items of a specified samples size or less
// only samples that are greater in value for 'highest' mode or less for 'lowest' mode
// the the specified sample size
namespace CORN {
//______________________________________________________________________________
class  Best_statistical_data_set
: public Statistical_data_set
{private:
   nat32   maximum_sample_size;
   bool     highest_mode;
 public:
   Best_statistical_data_set(nat32 _maximum_sample_size, bool _highest_mode = true);
 protected:
   virtual void recompute()                                         modification_;
};
//______________________________________________________________________________
}; // namespace CORN;
#endif

