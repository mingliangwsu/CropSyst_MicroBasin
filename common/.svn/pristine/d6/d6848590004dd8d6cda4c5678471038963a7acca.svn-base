#ifndef stoichiometry_compositionH
#define stoichiometry_compositionH
#include "chemistry/elements.h"

// Molar mass g/mol
#define ammonia_molar_mass          17.031
#define methane_molar_mass          16.042
#define carbon_dioxide_molar_mass   44.010
#define nitrous_oxide_molar_mass    44.013
#define     dinitrogen_monoxide_molar_mass nitrous_oxide_molar_mass
#define nitrogen_gas_molar_mass     (2.0*(nitrogen_atomic_mass))
#define potassium_oxide_molar_mass  94.20
#define diphosphorus_pentoxide_molar_mass      283.89
#define carbamide_molar_mass        60.06
   // carbamide is urea

// These calculation work for any units of mass (I.e. kg or g)
#define calc_CH4_C_mass(CH4_mass) ( (CH4_mass) * carbon_atomic_mass         / methane_molar_mass)
#define calc_CO2_C_mass(CO2_mass) ( (CO2_mass) * carbon_atomic_mass         / carbon_dioxide_molar_mass)
#define calc_NH3_N_mass(NH3_mass) ( (NH3_mass) * nitrogen_atomic_mass       / ammonia_molar_mass)
#define calc_N20_N_mass(N20_mass) ( (N20_mass) * nitrogen_atomic_mass * 2.0 / nitrous_oxide_molar_mass)
#define calc_N2_N_mass (N2_mass)  ( N2_mass )
   //For N2, the atomic mass and molar mass are the same.
#define calc_K2O_K_mass(K2O_mass) ( (K2O_mass) * 0.83011252653927813163481953290919 )
       //  K2O_mass * (potassium_automic_mass * 2.0) / potassium_oxide_molar_mass
#define calc_P2O5_P_mass(P2O5_mass)( (P2O5_mass) * 0.43641920462150833069146500405103)
       // P2O5_mass * 2.0 * ((phosphorus_atomic_mass * 2.0) / diphosphorus_pentoxide_molar_mass))
       // P2O5_mass * 2.0 * ((30.973762 * 2.0) / 283.89)  )
   //110726 Warning need to verify calc_K2O_K_mass and calc_P2O5_P_mass

#define calc_CH4N2O_N_mass(CH4N2O_mass) ((CH4N2O_mass) * ((nitrogen_atomic_mass) * 2.0) / carbamide_molar_mass)
   //110727 Warning need to verify  calc_CH4N2O_N_mass

#define calc_CH4_given_C_mass(CH4_C_mass) ( (CH4_C_mass) * methane_molar_mass / carbon_atomic_mass)
#define calc_CO2_given_C_mass(CO2_C_mass) ( (CO2_C_mass) * carbon_dioxide_molar_mass / carbon_atomic_mass)

#define calc_NH3_given_N_mass(NH3_N_mass) ( (NH3_N_mass) * ammonia_molar_mass / nitrogen_atomic_mass)
#define calc_N20_given_N_mass(N20_N_mass) ( (N20_N_mass) * nitrous_oxide_molar_mass /(nitrogen_atomic_mass * 2.0))

#define calc_CH4N2O_given_N_mass(CH4N2O_N_mass) ( (CH4N2O_N_mass) * carbamide_molar_mass /(nitrogen_atomic_mass * 2.0))
#define calc_urea_given_N_mass(CH4N2O_N_mass) calc_CH4N2O_given_N_mass(CH4N2O_N_mass)
   //110727 Warning need to verify  calc_CH4N2O_given_N_mass
//______________________________________________________________________________

#endif
