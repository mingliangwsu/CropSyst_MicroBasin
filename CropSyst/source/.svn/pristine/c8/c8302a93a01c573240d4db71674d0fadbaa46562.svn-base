#ifndef structure_interfaceH
#define structure_interfaceH
#include "corn/primitive.h"
#include "corn/const.h"
//______________________________________________________________________________
interface_ Soil_structure_interface
{
 // NYN particles/granularity
 // bulk density
   virtual float64 get_bulk_density_g_cm3       ( nat8 layer)              const = 0;  //051204
   virtual float64 set_bulk_density_g_cm3       ( nat8 layer,float64 _bulk_density_g_cm3) = 0 ;
   virtual float64 get_bulk_density_kg_m3       ( nat8 layer)              const;      //050727
   virtual float64 set_bulk_density_kg_m3       ( nat8 layer,float64 _bulk_density_kg_cm3); //150411
   virtual float64 set_bulk_density_Mg_m3       ( nat8 layer,float64 _bulk_density_Mg_m3) ; // Equivelent to set_bulk_density_g_cm3//070726_
   virtual float64 get_bulk_density_Mg_m3       ( nat8 layer)              const; // equivelent to get_bulk_density_g_cm3 //051204_
 // values for the entire profile
   virtual float64 get_bulk_density_avg_g_cm3()                            const = 0; //051204_
 // Units of mass conversion tht used bulk density
   virtual float64 kg_per_m2_to_micrograms_per_g( nat8 layer, float64 amount_kg_ha) const = 0;
   virtual float64 micrograms_per_g_to_kg_per_m2( nat8 layer, float64 amount_micrograms_per_g) const = 0;
   virtual void expand_last_layer_for_boundary_conditions( nat8 number_layers, nat8 number_expanded_layers) modification_ = 0;   //080130
//   virtual float64 get_mass_kg_ha(nat8 layer)                              const = 0; //110927
   virtual float64 get_mass_kg_m2(nat8 layer)                              const = 0; //110927
};
//______________________________________________________________________________
#endif

