#include "corn/measure/measures.h"

bool NO_MEASURE = 0; //No_Measure0;

double tn_ha_to_m(double amount , double  bulk_density )
{  return amount / (ha_to_m2(bulk_density));
}
//______________________________________________________________________________
double kg_ha_to_ppm(double value_kg_ha , double thickness , double bulk_density)
{  return value_kg_ha / (10.0 * thickness * bulk_density);
}
//______________________________________________________________________________
double kg_m2_to_ppm(double value_kg_m2 , double thickness , double bulk_density)
{  return (value_kg_m2 * 1000.0) / (thickness * bulk_density);
}
//______________________________________________________________________________
double ppm_to_kg_m2(double conc_ppm , double thickness , double bulk_density)
{  return (conc_ppm / 1000.0) * (thickness * bulk_density);
}
//______________________________________________________________________________






