#ifndef transpiration_interfaceH
#define transpiration_interfaceH
#include "corn/const.h"
#include "corn/primitive.h"
interface_ Transpiration_interface
{
   virtual float64 get_potential_mm()                                      const=0;
   virtual float64 get_water_stress_factor_yesterday()                     const=0;
};
#endif
