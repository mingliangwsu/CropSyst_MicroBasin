#ifndef OM_simpleH
#define OM_simpleH

#define N_fract_organic_matter  0.004  /* kg N / kg Org matter */
#define fraction_carbon_OM      0.4    /* Fraction of carbon in organic mat.*/
#define N_C_ratio               0.1    /* Mass Ratio of N to C  in organic mat.*/
#define active_OM_fraction      0.1    /* Fraction of OM that is active.*/

#include <common/soil/layering.h>
//______________________________________________________________________________
class Organic_matter_simple
{private:
   float64 initial_biomass ; // kg/m2 At the beginning of the simulation
   float64 total_recalibration_difference;
        // We need to store any different between simulated and actual
        // O.M. biomass when we recalibrate for the balance.
   float64 total_extracted;
   float64 total_intromitted;
   float64 total_from_residue_mineralization;
   soil_sublayer_array_64(biomass);  // kg/m2
   bool constant;
 public:
   Organic_matter_simple();
   Organic_matter_simple
      (soil_sublayer_array_64(initial_biomass_profile)
      ,bool is_constant = true);
      // This constructor takes a percent organic matter array and produces the biomass array.
   void initialize
      (soil_sublayer_array_64(initial_biomass_profile)
      ,bool is_constant = true);
   void recalibrate(const soil_sublayer_array_64(actual_OM_biomass));
   void receive_mineralized_N(nat8 sublayer, float64 N_content);
   float64 total_profile_biomass() const;
      // kg/m2 totals the biomass by sublayer
   float64 balance() const;
      // Returns the organic matter balance
   float64 get_biomass(nat8 sublayer)                                      const;//980719
      // Returns the O.M. biomass in the specified sublayer
   float64 get_percent(nat8 sublayer, float64 thickness_sl, float64 bulk_density_sl); //990210
   void get_molecular_N
      (soil_sublayer_array_64(molecular_N)  // <- Output results
      ,nat8  significant_sublayers) const;
      // Returns amount of elemental N in the biomass layers.
   float64 get_organic_carbon(nat8 sublayer, float64 layer_thickness)      const;
   void extract_active_molecular_N
      (soil_sublayer_array_64(molecular_N));   // <- Output results
      // Returns the active molecular N from the biomass. The biomass is reduced by the respective amount.
   void intromit_active_molecular_N(soil_sublayer_array_64( molecular_N));
      // Adds the molecular N to the biomass pool.  The biomass is incremented by the respective amount.
};
//______________________________________________________________________________
#endif

