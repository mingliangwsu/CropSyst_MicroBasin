#ifndef biomass_growth_IH
#define biomass_growth_IH
#include "corn/const.h"
#include "corn/primitive.h"
namespace CropSyst
{
//______________________________________________________________________________
interface_ Biomass_growth
{
 public:
   inline virtual ~Biomass_growth()                                           {}
 public:
   virtual bool start()                                         modification_=0;
   virtual bool process_day()                                   modification_=0;
   virtual float64 calc_attainable_top_growth()                  calculation_=0;
};
//______________________________________________________________________________
} // namespace CropSyst
#endif
