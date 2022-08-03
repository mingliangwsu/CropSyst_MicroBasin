#ifdef USE_PCH
#  include "simulation/CropSyst_sim_pch.h"
#else
#ifndef compareHPP
#  include <corn/math/compare.hpp>
#endif
#include "organic_matter/simple/OM_simple.h"
#endif
#include <corn/measure/measures.h>
//______________________________________________________________________________
Organic_matter_simple::Organic_matter_simple()
: initial_biomass(0)
, total_recalibration_difference(0)
, total_extracted(0.0)
, total_intromitted(0.0)
, total_from_residue_mineralization(0.0)
, constant(false)
{  for (nat8 sublayer = 0 ; sublayer <= MAX_soil_sublayers; sublayer++)
       biomass[sublayer] = 0;
};
//______________________________________________________________________________
Organic_matter_simple::Organic_matter_simple(soil_sublayer_array_64(initial_biomass_profile),bool is_constant)
: initial_biomass(0)
, total_recalibration_difference(0)
, total_extracted(0.0)
, total_intromitted(0.0)
, total_from_residue_mineralization(0.0)
, constant(is_constant)
{  initialize(initial_biomass_profile,is_constant);
};
//______________________________________________________________________________
void Organic_matter_simple::initialize(soil_sublayer_array_64(initial_biomass_profile),bool is_constant)
{  constant =is_constant;
   initial_biomass = 0;
   for (nat8 sublayer = 1 ; sublayer <= MAX_soil_sublayers; sublayer++)
   {  biomass[sublayer] = initial_biomass_profile[sublayer];
      initial_biomass += biomass[sublayer];
   };
};
//______________________________________________________________________________
void Organic_matter_simple::recalibrate(const soil_sublayer_array_64(actual_OM_biomass))
{  for (nat8 sublayer = 1; sublayer <= MAX_soil_sublayers; sublayer++)
   {  total_recalibration_difference +=
          biomass[sublayer] - actual_OM_biomass[sublayer];
       biomass[sublayer] = actual_OM_biomass[sublayer];
   };
};
//______________________________________________________________________________
void Organic_matter_simple::receive_mineralized_N(nat8 sublayer, float64 N_content)
{
   #define        C_N_ratio  10.0    /* C/N ratio of stable organic matter */
   if (!constant)
   {  //  increase the biomass respective to the N_content received
      float64 respective_biomass = N_content * C_N_ratio / fraction_carbon_OM;
      total_from_residue_mineralization += respective_biomass;
      biomass[sublayer] += respective_biomass;
   };
};
//______________________________________________________________________________
float64 Organic_matter_simple::total_profile_biomass() const
   /*             kg/m2 totals the biomass by sublayer */
{  float64 total = 0;
   for (nat8 sublayer = 1; sublayer <= MAX_soil_sublayers; sublayer++)
       total += biomass[sublayer];
   return total;
};
//______________________________________________________________________________
float64 Organic_matter_simple::balance() const
{  // Returns the organic matter balance
   float64 total_profile = total_profile_biomass();
   float64 bal =
        initial_biomass
      - total_extracted
      + total_intromitted
      + total_from_residue_mineralization
      - total_recalibration_difference
      - total_profile;
   if (CORN::is_approximately<float64>(bal,0.0,0.000001))
      bal = 0.0;
    return bal;
};
//______________________________________________________________________________
void Organic_matter_simple::get_molecular_N
        (soil_sublayer_array_64(molecular_N)  // <- Output results
        ,nat8  significant_sublayers) const
{  for (nat8 sublayer = 1; sublayer <= significant_sublayers; sublayer++)
      molecular_N[sublayer] = (N_fract_organic_matter * biomass[sublayer]);
};
//______________________________________________________________________________
void Organic_matter_simple::extract_active_molecular_N
(soil_sublayer_array_64(molecular_N))
{  // potential min. N does not store N (in molecular amount N)
   // it must be derived from organic_matter using this method
   for (nat8 sublayer = 1; sublayer <= MAX_soil_sublayers; sublayer++)
   {  // Determine the usable N available in the active biomass
      molecular_N[sublayer] =
         ((fraction_carbon_OM * N_C_ratio * active_OM_fraction) * biomass[sublayer]);
         // Now reduce the biomass by that respective amount
         float64 active_biomass_remaining = biomass[sublayer] * (1.0 - active_OM_fraction);
         float64 active_biomass_extracted = biomass[sublayer] - active_biomass_remaining;
         if (!constant)
         {  biomass[sublayer] =active_biomass_remaining;
            total_extracted += active_biomass_extracted;
         };
   };
};
//______________________________________________________________________________
void Organic_matter_simple::intromit_active_molecular_N(soil_sublayer_array_64( molecular_N))
{  for (nat8 sublayer = 1 ; sublayer <= MAX_soil_sublayers; sublayer++)
   {     float64 intromitted =  molecular_N[sublayer] / (fraction_carbon_OM * N_C_ratio );
         if (!constant)
         {  biomass[sublayer] += intromitted;
            total_intromitted += intromitted;
         };
         // The N is transfered to the biomass
         molecular_N[sublayer] = 0.0;
   };
};
//______________________________________________________________________________
float64 Organic_matter_simple::get_organic_carbon(nat8 sublayer , float64 layer_thickness )  const
{  return biomass[sublayer] / layer_thickness * fraction_carbon_OM;
};
//______________________________________________________________________________
float64  Organic_matter_simple::get_biomass(nat8 sublayer ) const
{  // Returns the O.M. biomass in the specified sublayer
   return biomass[sublayer];
};
//_1998-07-19___________________________________________________________________
float64 Organic_matter_simple::get_percent(nat8 sublayer, float64 thickness_sl, float64 bulk_density_sl)
{  return (get_biomass(sublayer) * 100.0) / (thickness_sl * tonne_to_kg(bulk_density_sl));
};
//_1999-02-10___________________________________________________________________

