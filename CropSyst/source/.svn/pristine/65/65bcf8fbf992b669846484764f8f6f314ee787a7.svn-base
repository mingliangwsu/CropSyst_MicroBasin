#ifndef crop_elementH
#define crop_elementH
#include "CS_suite/simulation/CS_simulation_element.h"
#include "CS_suite/observation/CS_observation.h"
//______________________________________________________________________________
namespace CropSyst {
//______________________________________________________________________________
class Crop_element
: public extends_ CS::Simulation_element_composite
{
 public:
   contribute_ CS::Emanator *emanator_known;                                     //160613
      // emanator_known is not_owned, don't delete
      // emanator_known is actually an aspect
 public:
   Crop_element(const CORN::date32 &today_);
   virtual bool start_period(nat8 period)                         modification_;
   virtual bool end_period(nat8 period)                           modification_;

   inline virtual const CS::Emanator *get_emanator_annual()  const { return 0; }
      // No annual emanation because crops have their own period
      // irrespective of year
   inline const char *get_ontology()                    const { return "crop"; }

};
//_2017-12-12____________________________________________________Crop_element__/
} // namespace CropSyst


#endif



