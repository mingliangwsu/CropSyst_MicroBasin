#ifndef temperature_interfaceH
#define temperature_interfaceH
#include "corn/primitive.h"
//______________________________________________________________________________
class Soil_temperature_interface
{
 public:  // Accessors
   inline virtual ~Soil_temperature_interface()                               {}
   virtual float64 get_temperature(nat8 layer)                        const = 0;
};
//______________________________________________________________________________
#endif
