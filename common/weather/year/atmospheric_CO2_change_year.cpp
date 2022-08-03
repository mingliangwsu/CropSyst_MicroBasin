#include "common/weather/year/atmospheric_CO2_change_year.h"
//______________________________________________________________________________
Atmospheric_CO2_change_year::Atmospheric_CO2_change_year
(float64             initial_CO2_conc)
: current_CO2_conc(initial_CO2_conc)
{};
//______________________________________________________________________________
float64 Atmospheric_CO2_change_year::set_current_CO2_conc
(float64 new_current_CO2_conc
,const CORN::Quality &_attribute)                                  modification_
{  current_CO2_conc = new_current_CO2_conc;
   current_CO2_conc_quality.set(_attribute);
   return current_CO2_conc;
};
//______________________________________________________________________________

