#ifndef P_temperatureH
#define P_temperatureH
#include "physics/property.h"
#include "corn/measure/measures.h"
namespace Physical
{
//_________________________________________________________________________________________
interface_ Temperature // eventually rename this to simply Temperature
: public extends_interface_ Property_interface
{
 public:
   inline float64 Celcius()                                                const { return in_prescribed_units(); }
   inline float64 kelvin()                                                 const { return C_to_kelvin(Celcius()); }
   inline float64 Farenheit()                                              const { return C_to_F(Celcius()); }
   inline float64 set_Celcius  (float64 celcius)                   modification_ { return update_value_with_units(celcius,UC_Celcius);}
   inline float64 set_Farenheit(float64 farenheit)                 modification_ { return set_Celcius(F_to_C(farenheit));             }
};
//_2015-01-21___________________________________________________________________
}
#endif
