#ifndef temperature_functionsH
#define temperature_functionsH
#include <corn/primitive.h>
//______________________________________________________________________________
extern    float64 calc_local_heat_capacity_J_m3_C   //  J/(m3 C)
      (float64 bulk_density_sl
      ,float64 water_content_sl
      ,float64 ice_content_sl = 0.0) ;
      // If 0.0 then assume everything is liquid water
//______________________________________________________________________________
extern  float64 DeVries_thermal_conductivity    //  J / (sec m C) DeVries
      (float64 water_content_sl
      ,float64 ice_content_sl
      ,float64 bulk_density_sl) ;
//______________________________________________________________________________
#endif
