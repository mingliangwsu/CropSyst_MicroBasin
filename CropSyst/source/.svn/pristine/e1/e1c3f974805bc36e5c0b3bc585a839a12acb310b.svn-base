#ifndef CARBON_SEQUESTRATION_RESULTS_H
#define CARBON_SEQUESTRATION_RESULTS_H

#include "project/optimization/scenario_results.h"

/*
[scenario]
exit_code=success
days_not_viable=93
[optimization]
carbon_sequestration_profile=24603.8 kg/ha (organic soil and residue carbon in the soil profile at the end of the run)
carbon_sequestration_30cm=12410.6 kg/ha (organic soil and residue carbon in the first 30cm at the end of the run)

grazed_biomass=4516.67 kg/ha (total biomass grazed throughout the run)
(obsolete this is now neasonal_grazing_sum }



[seasonal_grazing]
units=kg/ha
mean=
sum=
1=
2=
3=
:
[seasonal_ungrazed]
units=kg/ha
mean=
sum=
1=
2=
3=
:

[seasonal_biomass_production]
units=kg/ha
mean=
sum=
1=
2=
3=
:
[seasonal_grazing_requirement]
units=kg/ha
mean=
sum=
1=
2=
3=


[grazing]
(This section obsolete)
mean_grazed_biomass=347.321 kg/ha (mean of all years)   Now use seasonal_grazing sum
mean_ungrazed_biomass=883.003 kg/ha (mean of all years) Now use seasonal_ungrazed sum

*/

//______________________________________________________________________________
struct Seasonal_tally
{
   float32 mean;
   float32 sum;
   float32 value[300]; // max 300 seasons
};

class Tcarbon_sequestration_viewer_form; // forward declaration
//______________________________________________________________________________
   class Carbon_sequestration_scenario_results_data_record
   : public Scenario_results_data_record
   {
   protected: // read from the scenario output
      friend class Tcarbon_sequestration_viewer_form;
      float32 carbon_sequestration_profile_kg_ha; // organic soil and residue carbon in soil profile at the end of the run
      float32 carbon_sequestration_30cm_kg_ha; // organic soil and residue carbon in first 30cm at the end of the run
//050110            float32 grazed_biomass_kg_ha;   replaced with seasonal_grazing_kg_ha.sum    // total (sum) biomass grazed throughout the run

//050110      float32 mean_grazed_biomass_kg_ha;  replaced with seasonal_grazing_kg_ha.mean   // Mean of seasonal biomass grazed throughout the turn
//050110      float32 mean_ungrazed_biomass_kg_ha; replaced seasonal_ungrazed_kg_ha.mean     // Mean of seasonal biomass not grazed (sent to residue).

      Seasonal_tally seasonal_grazing_kg_ha;
      Seasonal_tally seasonal_ungrazed_kg_ha;
      Seasonal_tally seasonal_biomass_production_kg_ha;
      Seasonal_tally seasonal_grazing_requirement_kg_ha;

   private:
      float32 pasture_size_ha;
      float32 plot_size_ha;
      float32 plot_number;

   public:
      virtual float32 get_result(int index) const;
      virtual void expect_structure(bool for_write);

   public: //constructor
      Carbon_sequestration_scenario_results_data_record
      (const char *i_scenario_name
      ,Simulation_run_result i_exit_code
      ,float32 i_plot_size_ha
      );
   private:
      void clear_seasonal_tally(Seasonal_tally &to_be_cleared);
   };
//______________________________________________________________________________

#endif