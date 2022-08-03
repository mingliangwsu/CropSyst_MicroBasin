#ifndef atmospheric_CO2_change_linear_yearH
#define atmospheric_CO2_change_linear_yearH
#include "common/weather/year/atmospheric_CO2_change_year.h"
//______________________________________________________________________________
class Atmospheric_CO2_change_linear_year
: public Atmospheric_CO2_change_year
{
   float64             annual_CO2_conc_change;  // ppm/year
public:
   Atmospheric_CO2_change_linear_year
   (float64             _initial_CO2_conc  // ppm
   ,float64             _annual_CO2_conc_change  // ppm/year
   );
//NYN   virtual bool update()                                                 updates;
   virtual bool end_year()                                             not_const;
};
//______________________________________________________________________________

#endif

