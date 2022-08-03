#ifndef WP_humidity_specificH
#define WP_humidity_specificH
#include "common/CS_parameter_float64.h"
//______________________________________________________________________________
class Humidity_specific
: public extends_ CS::Parameter_float64
{
 public:
   inline Humidity_specific()
      : CS::Parameter_float64(false,0.0,UC_kg_kg,CORN::unknown_quality)
      {}
   inline float64 kg_kg()                                                 const
      { return in_prescribed_units(); }
   inline float64 set_kg_kg(float64 in_kg_kg)                      assignation_
      { return set_amount(in_kg_kg); }
   inline float64 calc_mixing_ratio_kg_kg()                        calculation_
      {  float64 humid_spec = kg_kg();
         return humid_spec / (1.0 + humid_spec);
      }
};
//_class_Humidity_specific__________________________________________2018-08-08_/

#endif

