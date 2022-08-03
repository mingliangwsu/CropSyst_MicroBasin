#include "Project/Optimization/carbon_sequestration/carbon_sequestration_results.h"
//______________________________________________________________________________
Carbon_sequestration_scenario_results_data_record::Carbon_sequestration_scenario_results_data_record
(const char *i_scenario_name
,Simulation_run_result i_exit_code
,float32 i_plot_size_ha)
: Scenario_results_data_record(i_scenario_name,i_exit_code)
, carbon_sequestration_profile_kg_ha(0.0)
, carbon_sequestration_30cm_kg_ha(0.0)
, plot_size_ha(i_plot_size_ha)
{  clear_seasonal_tally(seasonal_grazing_kg_ha);
   clear_seasonal_tally(seasonal_ungrazed_kg_ha);
   clear_seasonal_tally(seasonal_biomass_production_kg_ha);
   clear_seasonal_tally(seasonal_grazing_requirement_kg_ha);
};
//______________________________________________________________________________
void  Carbon_sequestration_scenario_results_data_record::clear_seasonal_tally(Seasonal_tally &to_be_cleared)
{  to_be_cleared.mean=0;
   to_be_cleared.sum=0;
   for (int i = 0; i < 300; i++)
      to_be_cleared.value[i] = 0;
};
//______________________________________________________________________________
float32 Carbon_sequestration_scenario_results_data_record::get_result(int index) const
{  float32 result = 0.0;
   switch (index)
   {  case  0  /* was 0 */: result = seasonal_grazing_kg_ha.sum /*grazed_biomass_kg_ha*/ ; break;
      case  1             : result = seasonal_grazing_requirement_kg_ha.sum; break; // added 050110
      case  2  /* was 1 */: result = carbon_sequestration_profile_kg_ha; break;
      case  3  /* was 2 */: result = carbon_sequestration_30cm_kg_ha; break;

      case  4  /* was 3 */: result = seasonal_grazing_kg_ha.mean  /*mean_grazed_biomass_kg_ha*/ ;   break;   // Mean of seasonal biomass grazed throughout the turn
      case  5             : result = seasonal_grazing_requirement_kg_ha.mean; break; // add 050110
      case  6  /* was 4 */: result = seasonal_ungrazed_kg_ha.mean  /*mean_ungrazed_biomass_kg_ha*/ ; break;   // Mean of seasonal biomass not grazed (sent to residue).

      case  7  /* was 5 */: result = seasonal_grazing_kg_ha.sum /*grazed_biomass_kg_ha*/  * plot_size_ha;   break;
      case  8             : result = seasonal_grazing_requirement_kg_ha.sum * plot_size_ha;   break;  // add 050110
      case  9  /* was 6 */: result = carbon_sequestration_profile_kg_ha * plot_size_ha;   break;
      case 10  /* was 7 */: result = carbon_sequestration_30cm_kg_ha * plot_size_ha;   break;
      case 11  /* was 8 */: result = seasonal_grazing_kg_ha.mean  /*mean_grazed_biomass_kg_ha*/ * plot_size_ha;   break;
      case 12             : result = seasonal_grazing_requirement_kg_ha.mean * plot_size_ha;   break;
      case 13  /* was 9 */: result = seasonal_ungrazed_kg_ha.mean  /*mean_ungrazed_biomass_kg_ha*/ * plot_size_ha;   break;
      default : result = 0.0; break;
   };
   return result;
};
//______________________________________________________________________________
void Carbon_sequestration_scenario_results_data_record::expect_structure(bool for_write)
{
   Scenario_results_data_record::expect_structure(for_write);
   structure_defined = true; //120314   
   set_current_section("optimization");
      expect_float32("carbon_sequestration_profile",carbon_sequestration_profile_kg_ha);
      expect_float32("carbon_sequestration_30cm",carbon_sequestration_30cm_kg_ha);
//050110obs   expect_float32("grazed_biomass",grazed_biomass_kg_ha);
//050110obs   set_current_section("grazing");
//050110obs   expect_float32("mean_grazed_biomass",mean_grazed_biomass_kg_ha);
//050110obs   expect_float32("mean_ungrazed_biomass",mean_ungrazed_biomass_kg_ha);

   set_current_section("seasonal_grazing");
      expect_float32("mean",seasonal_grazing_kg_ha.mean);
      expect_float32("sum",seasonal_grazing_kg_ha.sum);
      expect_float32_array_with_units_code_fixed("seasonal_grazing", UC_kg_ha,seasonal_grazing_kg_ha.value   ,0 , 299,false);
//070418      expect_float32_array_with_units("seasonal_grazing", "kg/ha",seasonal_grazing_kg_ha.value   ,0 , 299,false);
   set_current_section("seasonal_ungrazed");
      expect_float32("mean",seasonal_ungrazed_kg_ha.mean);
      expect_float32("sum",seasonal_ungrazed_kg_ha.sum);
      expect_float32_array_with_units_code_fixed("seasonal_ungrazed", UC_kg_ha,seasonal_ungrazed_kg_ha.value   ,0 , 299,false);
//070418      expect_float32_array_with_units("seasonal_ungrazed", "kg/ha",seasonal_ungrazed_kg_ha.value   ,0 , 299,false);
   set_current_section("seasonal_biomass_production");
      expect_float32("mean",seasonal_biomass_production_kg_ha.mean);
      expect_float32("sum",seasonal_biomass_production_kg_ha.sum);
      expect_float32_array_with_units_code_fixed("seasonal_biomass_production", UC_kg_ha,seasonal_biomass_production_kg_ha.value   ,0 , 299,false);
//070418      expect_float32_array_with_units("seasonal_biomass_production", "kg/ha",seasonal_biomass_production_kg_ha.value   ,0 , 299,false);
   set_current_section("seasonal_grazing_requirements");
      expect_float32("mean",seasonal_grazing_requirement_kg_ha.mean);
      expect_float32("sum",seasonal_grazing_requirement_kg_ha.sum);
      expect_float32_array_with_units_code_fixed("seasonal_grazing_requirements",UC_kg_ha,seasonal_grazing_requirement_kg_ha.value   ,0 , 299,false);
//070418      expect_float32_array_with_units("seasonal_grazing_requirements","kg/ha",seasonal_grazing_requirement_kg_ha.value   ,0 , 299,false);
};
//______________________________________________________________________________
