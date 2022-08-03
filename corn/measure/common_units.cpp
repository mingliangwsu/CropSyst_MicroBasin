#include "corn/measure/common_units.h"

namespace CORN {

const Units_code common_mass_per_area_units[] =
{UC_kg_ha
,UC_kg_m2
//NYI ,UC_g_ha
//NYI ,UC_g_m2
,0};

const Units_code common_acreage_units[] =
{  UC_hectare
,  UC_are
,  UC_square_meter_area // UC_square_meter_surface_area
,  UE_acre
,0 };

const Units_code common_liquid_measure_units[] =
{  UC_liter
,  UC_cubic_meter_volume
,  UE_fluid_gallon_US
,  UE_fluid_gallon_Imperial
,0 };

const Units_code common_dry_measure_units[] =
{  UC_cubic_meter_volume
,  UE_avoirdupois_hundredweight_US
,  UE_dry_gallon_US
,  UE_dry_gallon_Imperial
,  UE_dry_bushel_US
,0 };

const Units_code common_count_units[] =
{  UC_count
,0 };

}; // namespace 
