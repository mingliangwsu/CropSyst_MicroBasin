#ifndef WP_temperatureH
#define WP_temperatureH
#include "common/CS_parameter_float64.h"
#include "common/physics/property/P_temperature.h"
#include "corn/measure/measures.h"

// This class file should be moved to a more general location and not
// derived from Weather parameter

namespace CS
{
//______________________________________________________________________________
class Temperature
: public extends_interface_ Physical::Temperature
, public extends_ CS::Parameter_float64
{
 public:
   inline Temperature
      (float64 default_value = 0.0
      ,CORN::Quality_code  default_quality_code = CORN::unknown_quality)
         // Warning check probably not a reference
         // since were are providing the quality code here
      : CS::Parameter_float64 (INTENSIVE,default_value,UC_Celcius,default_quality_code)
      {}
   inline virtual ~Temperature() {}                                              //151204
   inline virtual CORN::Units_code get_units()                             const { return CS::Parameter_float64::get_units(); }
   inline Temperature &operator = (float64 new_amount)
      {  force_amount(new_amount);                                               //150125
         return *this;
      }
   inline float64 set_Celcius  (float64 celcius,   const CORN::Quality &_quality) const { return update_value_qualified(celcius,_quality);}
   inline float64 set_Farenheit(float64 farenheit, const CORN::Quality &_quality) const { return update_value_qualified(F_to_C(farenheit),_quality);}
   inline float64 set_Celcius  (float64 celcius,   CORN::Quality_code _quality)   const { return update_value_qualified_code(celcius,_quality);}
   inline float64 set_Farenheit(float64 farenheit, CORN::Quality_code _quality)   const { return update_value_qualified_code(F_to_C(farenheit),_quality);}
   inline float64 set_kelvin(float64 kelvin, CORN::Quality_code _quality)   const { return update_value_qualified_code(kelvin_to_C(kelvin),_quality);} //150529
   inline float64 set_kelvin(float64 kelvin, const CORN::Quality &_quality) const { return update_value_qualified(kelvin_to_C(kelvin),_quality);} //150529
};
//_2015-01-20___________________________________________________________________
} // namespace CS
#endif

