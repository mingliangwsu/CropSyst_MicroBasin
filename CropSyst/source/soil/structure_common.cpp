
#include "soil/structure_common.h"
#include "soil/soil_interface.h"
#include "soil/soil_param_class.h"
//______________________________________________________________________________
Soil_structure_common::Soil_structure_common(const Soil_layers_interface    &_layers)
// datamembers cleared below
: layers(_layers)
{  clear_layer_array64(bulk_density_g_cm3);                                      //070725
   bulk_density_stats_g_cm3.clear();                                             //061027
}
//______________________________________________________________________________
Soil_structure_common::Soil_structure_common
(const Soil_layers_interface &_layers
,const Soil_parameters_class &parameters)
: layers(_layers)
{  // This constructor is used by scrutinize infiltration
   // In this case the soil profile matches the soil file horizons
   clear_layer_array64(bulk_density_g_cm3);                                      //070725
   bulk_density_stats_g_cm3.clear();                                             //061027
   for (nat8 layer ; layer <= layers.get_number_layers(); layer ++)
   {
       set_bulk_density_g_cm3(layer,parameters.get_horizon_bulk_density_g_cm3(layer));
   }
};
//_2015-09-26___________________________________________________________________
Soil_structure_common::Soil_structure_common(const Soil_structure_common &copy_from)
: bulk_density_stats_g_cm3(copy_from.bulk_density_stats_g_cm3)
, layers(copy_from.layers)
{  layers.copy_array64(bulk_density_g_cm3 ,copy_from.bulk_density_g_cm3);
}
//_2007-07-25___________________________________________________________________
void Soil_structure_common::copy(const Soil_structure_common &copy_from)
{

assert(false);

/*180404 not sure if I am still using this

   bulk_density_stats_g_cm3.copy
      (copy_from.bulk_density_stats_g_cm3
      ,copy_from.bulk_density_stats_g_cm3.get_applicable());

*/

   //180408 bulk_density_stats_g_cm3.copy(copy_from.bulk_density_stats_g_cm3);
   layers.copy_array64(bulk_density_g_cm3 ,copy_from.bulk_density_g_cm3);
}
//______________________________________________________________________________
float64 Soil_structure_common::get_bulk_density_g_cm3( nat8 layer)  const
{  return  bulk_density_g_cm3[layer];
}
//_2005-12-09____________________________________________________________________
float64 Soil_structure_common::set_bulk_density_g_cm3( nat8 layer,float64 _bulk_density_g_cm3)
{  bulk_density_g_cm3[layer] =_bulk_density_g_cm3;
   bulk_density_stats_g_cm3.set(layer,_bulk_density_g_cm3);
   return (float64) _bulk_density_g_cm3;
}
//_2005-12-04___________________________________________________________________
float64 Soil_structure_common::set_bulk_density_kg_m3(nat8 layer,float64 bulk_density_kg_m3)
{  float64 _bulk_density_g_cm3 = kg_m3_to_g_cm3(bulk_density_kg_m3);
   bulk_density_g_cm3[layer] =_bulk_density_g_cm3;
   bulk_density_stats_g_cm3.set(layer,_bulk_density_g_cm3);
   return (float64) _bulk_density_g_cm3;
}
//_2014-12-07___________________________________________________________________
float64 Soil_structure_common::get_bulk_density_avg_g_cm3() const
{   //051205 RLN Warning I think this may need to be a weighted average!!!
    return  bulk_density_stats_g_cm3.get_mean();
}
//_2005-12-04___________________________________________________________________
// The following are units of mass coversions
float64 Soil_structure_common::kg_per_m2_to_micrograms_per_g( nat8 layer, float64 amount_kg_ha) const   // May want to put this in soil base, but so far it is only used here
{  return amount_kg_ha * ((layers.get_thickness_m(layer) /
         get_bulk_density_g_cm3(layer)) * 1000000.0);
}
//_2005-12-04___________________________________________________________________
float64 Soil_structure_common:: micrograms_per_g_to_kg_per_m2( nat8 layer, float64 amount_micrograms_per_g) const   // May want to put this in soil base, but so far it is only used here
{  // Warning I need to check this with Claudio
   return amount_micrograms_per_g
      / ((layers.get_thickness_m(layer) / get_bulk_density_g_cm3(layer)) * 1000000.0); //
}
//_2005-12-04___________________________________________________________________
void Soil_structure_common
::expand_last_layer_for_boundary_conditions( nat8 number_layers, nat8 number_expanded_layers)              modification_
{  for ( nat8 extend_layer = number_layers+1; extend_layer <= number_expanded_layers; extend_layer++) //080211
     bulk_density_g_cm3[extend_layer] = bulk_density_g_cm3[number_layers];
}
//_2008-01-30___________________________________________________________________
float64 Soil_structure_common::get_mass_kg_m2(nat8 layer)                  const
{  return  get_bulk_density_kg_m3(layer) *layers.get_thickness_m(layer); }
//_2011-09-27___________________________________________________________________
float64 Soil_structure_common::get_bulk_density_kg_m3(nat8 layer)       const
{return g_cm3_to_kg_m3(get_bulk_density_g_cm3(layer));
}
//_2015-05-26__LML______________________________________________________________




