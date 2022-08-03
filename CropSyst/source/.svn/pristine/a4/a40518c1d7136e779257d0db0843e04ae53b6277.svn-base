#include "nitrogen_common.h"
//______________________________________________________________________________
float64 Soil_nitrogen_common::uptake_N_mass(nat8 layer, float64 requested_pot_elemental_N_uptake_kg_m2) modification_
{  float64 act_NH4_uptake = 0;
   float64 act_NO3_uptake = uptake_N_mass_from_NO3(layer,requested_pot_elemental_N_uptake_kg_m2);
   if (act_NO3_uptake < requested_pot_elemental_N_uptake_kg_m2)
   {  float64 remaining_N_mass_to_uptake = requested_pot_elemental_N_uptake_kg_m2 - act_NO3_uptake;
      act_NH4_uptake =         uptake_N_mass_from_NH4( layer, remaining_N_mass_to_uptake);
               // Currently presuming that there is sufficient soil N
               // (we the imbobilization should be guarenteed not to exceed available N)
   };
   return act_NO3_uptake + act_NH4_uptake;
}
//______________________________________________________________________________
float64 Soil_nitrogen_common::add_NO3_N_mass(nat8 layer,float64 NO3_N_mass_addend) modification_
{  // Notice that this method calls add_NO3_mass_molecular and that method call this method
   // obviously an infinite loop, this is why derived classes MUST override either of these methods.
   float64 NO3_molecular_mass_addend = convert_NO3_N_to_molecular_mass(NO3_N_mass_addend);
   return convert_NO3_molecular_to_N_mass(add_NO3_molecular_mass(layer,NO3_molecular_mass_addend));
}
//______________________________________________________________________________
float64 Soil_nitrogen_common::add_NH4_N_mass(nat8 layer,float64 NH4_N_mass_addend) modification_
{  // Notice that this method calls add_NH4_mass_molecular and that method call this method
   // obviously an infinite loop, this is why derived classes MUST override either of these methods.
   float64 NH4_molecular_mass_addend = convert_NH4_N_to_molecular_mass(NH4_N_mass_addend);
   return convert_NH4_molecular_to_N_mass(add_NO3_molecular_mass(layer,NH4_molecular_mass_addend));
}
//______________________________________________________________________________
float64 Soil_nitrogen_common::add_NO3_molecular_mass(nat8 layer,float64 NO3_mass_M_addend) modification_
{  // Notice that this method calls add_NO3_N_mass and that method call this method
   // obviously an infinite loop, this is why derived classes MUST override either of these methods.
   float64 NO3_N_mass_addend = convert_NO3_molecular_to_N_mass(NO3_mass_M_addend);
   return convert_NO3_N_to_molecular_mass(add_NO3_N_mass(layer,NO3_N_mass_addend));
}
//______________________________________________________________________________
float64 Soil_nitrogen_common::add_NH4_molecular_mass(nat8 layer,float64 NH4_mass_M_addend)
{  // Notice that this method calls add_NH4_N_mass and that method call this method
   // obviously an infinite loop, this is why derived classes MUST override either of these methods.
   float64 NH4_N_mass_addend = convert_NH4_molecular_to_N_mass(NH4_mass_M_addend);
   return convert_NH4_N_to_molecular_mass(add_NH4_N_mass(layer,NH4_N_mass_addend));
}
//______________________________________________________________________________

#ifdef NYI
float64 Soil_nitrogen_common::subtract_NO3_mass_molecular(nat8 layer,float64 NO3_mass_M);
//______________________________________________________________________________
float64 Soil_nitrogen_common::subtract_NH4_mass_molecular           (nat8 layer,float64 NH4_mass_M);
//______________________________________________________________________________
#endif
