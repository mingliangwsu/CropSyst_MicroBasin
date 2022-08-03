#ifndef WP_psychrometric_constH
#define WP_psychrometric_constH
#include "common/CS_parameter_float64.h"
//---------------------------------------------------------------------------
/**< The psychrometric constant (kPa/°C)
   represents a balance between the sensible heat gained
   from air flowing past a wet bulb thermometer and the sensible heat
   transformed into latent heat (Brunt, 1952).
   It varies directly with air pressure.
   It is represented mathmatically by gamma.
**/
class Psychrometric_constant
: public extends_ CS::Parameter_float64   // not sure if intensive ?
{
 public:
   inline Psychrometric_constant()
      : CS::Parameter_float64(INTENSIVE,0.0,UC_kPa_per_C,CORN::calculated_quality) //150531
      {}  // This may be EXTENSIVE, need to check
   inline float64 get_kPa_per_C()                                          const { return in_prescribed_units(); }
   inline float64 set_kPa_per_C(float64 value_kPa_C)               modification_
      {  return update_value_with_units(value_kPa_C,UC_kPa_per_C);
      }
   inline float64 update_kPa_per_C(float64 value_kPa_C)           rectification_
      {  return update_value_with_units(value_kPa_C,UC_kPa_per_C);               //150123
      }
};
//_2014-05-07___________________________________________________________________
#endif

