This is obsolete
#include "common/weather/year/atmospheric_CO2_change_linear_year.h"
//______________________________________________________________________________
Atmospheric_CO2_change_linear_year::Atmospheric_CO2_change_linear_year
(float64             _initial_CO2_conc  // ppm
,float64             _annual_CO2_conc_change  // ppm/year
)
: Atmospheric_CO2_change_year(_initial_CO2_conc)
, annual_CO2_conc_change(_annual_CO2_conc_change)
{};
//______________________________________________________________________________
bool Atmospheric_CO2_change_linear_year::end_year()        not_const
{  current_CO2_conc += annual_CO2_conc_change;
   return true;
};
//______________________________________________________________________________

