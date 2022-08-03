#ifndef property_completeH
#define property_completeH
#include "common/physics/property_cowl_T.h"
namespace Physical
{
//______________________________________________________________________________
class Property_complete
: public extends_ Property_cowl<float64>
{
 public:
   mutable Measure_datum datum;
 public:
   inline Property_complete(bool extensive,float64 default_value, CORN::Units_code units_code)
      : Property_cowl<float64>(extensive,datum.amount,datum.units)
      , datum(default_value,units_code)
      {}
   inline Property_complete(const Property_complete &from_copy)                  //150206
      : Property_cowl<float64>(from_copy.is_extensive(),datum.amount,datum.units)
      , datum(from_copy.get_amount(),from_copy.get_units())
      {}
   inline virtual float64 force_amount(float64 new_amount)        rectification_
      { return datum.amount = new_amount; }
};
//_2015-01-24___________________________________________________________________
} // namespace Physical
#endif
