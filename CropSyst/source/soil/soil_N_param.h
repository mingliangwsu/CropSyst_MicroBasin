#ifndef soil_N_paramH
#define soil_N_paramH
#include "corn/primitive.h"
namespace CropSyst {
//______________________________________________________________________________
struct Denitrification_parameters
{
   float32 scale;     // shifts line up/down
   float32 rate_max;  // does have units   (same as potential_denitrification_rate)
   float32 alpha;
      // 1 indicates lower threshold (at field capacity)
      // 0 indicates lower threshold (at PWP)
      // mgC/kg Soil day
 public:
   inline Denitrification_parameters()
      : scale     (0.0)
      , rate_max  (1.0)
      , alpha     (1.0) // 170426 (0.5) // 160323(0.8)
      {}
   inline Denitrification_parameters(const Denitrification_parameters &copy_from)
      : scale(copy_from.scale)
      , rate_max(copy_from.rate_max)
      , alpha(copy_from.alpha)
      {}
};
//_2015-08-24___________________________________________________________________
} // namespace CropSyst
#endif

