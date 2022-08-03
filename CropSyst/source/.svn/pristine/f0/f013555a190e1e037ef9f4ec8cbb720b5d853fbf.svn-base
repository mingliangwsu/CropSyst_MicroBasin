#ifndef salt_interfaceH
#define salt_interfaceH
#include "corn/primitive.h"
#include "corn/chronometry/time_types.hpp"
#include "corn/const.h"
//______________________________________________________________________________
class Soil_salt_interface
{
public:
   virtual float64 get_salt_stress_function
   (nat8 layer,float64 osmotic_pot_50,float64 salt_tolerance_P)            const = 0;
      // Derived classes can return 1.0 if not interested in salinity
   virtual float64 get_osmotic_pot_solution(uint8 layer)                   const = 0;
      // Derived classes can return 0.0 if not interested in salinity
   virtual void set_daily_irrig_salinity
      (float64 concentration
      ,float64 ECw_to_TDS
      ,float64 irrig_water_amount
      ,CORN::Hour    event_start_hour
      ,CORN::Hours   event_duration)                               modification_ = 0;
      // this should be renamed to apply_irrigation_salinity
   virtual float64 get_concentration_dSm(uint8 layer)                      const = 0;
   virtual bool start_day()                                        modification_ = 0;
};
//______________________________________________________________________________
#endif

