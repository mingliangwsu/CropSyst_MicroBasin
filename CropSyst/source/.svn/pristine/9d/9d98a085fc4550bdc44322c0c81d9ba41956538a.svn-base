#include "soil/structure_interface.h"
#include "corn/measure/measures.h"
//______________________________________________________________________________
float64 Soil_structure_interface::get_bulk_density_kg_m3(uint8 layer)  const
{   // 1000 converts g/cm3 to kg/m3
   return g_cm3_to_kg_m3(get_bulk_density_g_cm3(layer));
}
//_2005-07-27___________________________________________________________________
float64 Soil_structure_interface::set_bulk_density_kg_m3( nat8 layer,float64 _bulk_density_kg_cm3)
{  float64 bulk_density_g_cm3 = kg_m3_to_g_cm3(_bulk_density_kg_cm3);
   return set_bulk_density_g_cm3(layer,bulk_density_g_cm3);
}
//_2015-04-11___________________________________________________________________
float64 Soil_structure_interface::set_bulk_density_Mg_m3
(uint8 layer,float64 _bulk_density_Mg_m3)
{ return set_bulk_density_g_cm3(layer,_bulk_density_Mg_m3) ;} // Equivelent
//_2005-07-26___________________________________________________________________
float64 Soil_structure_interface::get_bulk_density_Mg_m3
(uint8 layer)  const
{ return get_bulk_density_g_cm3(layer); } // equivelent
//_2005-12-04___________________________________________________________________

