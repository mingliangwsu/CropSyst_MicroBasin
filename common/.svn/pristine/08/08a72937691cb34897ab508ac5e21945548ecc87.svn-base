#ifndef CO2_atmospheric_concH
#define CO2_atmospheric_concH
#include "common/CS_parameter_float64.h"
namespace CS {
//_________________________________________________________________________________________
class CO2_atmospheric_concentration
: public extends_ CS::Parameter_float64
{
 public:
   inline CO2_atmospheric_concentration()
      : CS::Parameter_float64
         (INTENSIVE,0.0,UC_meters_per_second,CORN::unknown_quality)
      {}
   inline float64 ppm()                                                    const
      { return in_prescribed_units(); }
   inline float64 set_ppm
      (float64 value_ppm
      ,CORN::Quality &_quality)                                     assignation_
      { assume(_quality); return force_amount(value_ppm); }
   inline float64 set_ppm
      (float64 value_ppm
      ,CORN::Quality_code _quality)                                 assignation_
      { assume_code(_quality); return force_amount(value_ppm); }

 };
//_________________________________________________________________________________________
 } // namespace Physical
#endif
