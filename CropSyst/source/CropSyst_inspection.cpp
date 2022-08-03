
// This module only needs to be included if using variable recorders

// This file uses 8 bit characters in literal text strings

#include "csvc.h"
#include "CS_suite/observation/CS_inspector.h"
#include "CS_suite/observation/CS_examination.h"

#include "crop/crop_cropsyst.h"
#include "soil/chemicals_profile.h"
#include "soil/nitrogen_profile.h"
#include "soil/infiltration.h"
#include "soil/hydrology.h"
#include "soil.h"
#include "organic_matter/OM_pools_common.h"
#include "cs_ET.h"
#include "UED/library/std_codes.h"
#include "land_unit_sim.h"
#include "soil/soil_evaporator.h"

#define CSVC_UNKNOWN 0

#define TS_VALUE value_statistic
// Representative value for timestep.
// It is may be the cumulative value for the time step (I.e. the current day)
// and/or total for components,
// but not considered a precalculated statistic.

// template
// inspectors.append(new CS::Inspector(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVC_XXXX));

/* NYI
Annual

[ ]CSVC_mgmt_N_organic_gaseous_loss_period_sum          ,UC_kg_ha}
[ ]CSVC_mgmt_N_inorganic_gaseous_loss_period_sum        ,UC_kg_ha}

[ ]CSVC_soil_C_SOM_profile                              ,UC_kg_ha}
[ ]CSVC_soil_C_SOM_30cm                                 ,UC_kg_ha}

Seasonal

[ ]Duration
*/

//_____________________________________________________________________________/

/*
nitrogen

   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_yield));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_useful));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_disposal));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_chaff));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_stubble));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_grazing_to_manure));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_grazing_to_disposal));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_uncut_canopy));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_canopy));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_removed_canopy));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_removed_non_yield));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_removed_residue));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_removed_grazing));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_roots_live));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_roots_dead));
*/
/*
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_removed_above_ground));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_removed_grazing));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_mass_removed_residue));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_yield));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_useful));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_disposal));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_chaff));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_stubble));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_grazing_to_manure));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_grazing_to_disposal));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_uncut_canopy));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_canopy));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_removed_canopy));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_removed_non_yield));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_removed_residue));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_removed_grazing));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_roots_live));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_roots_dead));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_produced_above_ground));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_removed_above_ground));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_removed_grazing));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_N_conc_removed_residue));
*/
//______________________________________________________________________________
/*template
namespace CropSyst {
RENDER_INSPECTORS_DEFINITION(XXXXX)
{
// inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_XXXX));
// inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_XXXX));
// inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_XXXX));
   return 0; // emanator;
}

//______________________________________________________________________________
} // namespace CropSyst
*/
//_2013-07-30_________________________________Crop_nitrogen::render_inspectors_/

/* NYI

   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_water_drainage));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_water_depletion));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_water_balance));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_erosion_clod_rate));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_erosion_loss));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_erosion_loss));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_erosion_index));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_erosion_RUSLE_C_factor));

   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_runoff_surface_water_runon));
CSVP_soil_C_SOM_profile
CSVP_soil_C_SOM_5cm
CSVP_soil_C_SOM_10cm
CSVP_soil_C_SOM_15cm
CSVP_soil_C_SOM_30cm
CSVP_soil_C_SOM_60cm
CSVP_soil_C_SOM_90cm
CSVP_soil_C_microbial_profile
CSVP_soil_C_microbial_5cm
CSVP_soil_C_microbial_10cm
CSVP_soil_C_microbial_15cm
CSVP_soil_C_microbial_30cm
CSVP_soil_C_microbial_60cm
CSVP_soil_C_microbial_90cm
CSVP_soil_C_labile_profile
CSVP_soil_C_labile_5cm
CSVP_soil_C_labile_10cm
CSVP_soil_C_labile_15cm
CSVP_soil_C_labile_30cm
CSVP_soil_C_labile_60cm
CSVP_soil_C_labile_90cm
CSVP_soil_C_metastable_profile
CSVP_soil_C_metastable_5cm
CSVP_soil_C_metastable_10cm
CSVP_soil_C_metastable_15cm
CSVP_soil_C_metastable_30cm
CSVP_soil_C_metastable_60cm
CSVP_soil_C_metastable_90cm
CSVP_soil_C_passive_profile
CSVP_soil_C_passive_5cm
CSVP_soil_C_passive_10cm
CSVP_soil_C_passive_15cm
CSVP_soil_C_passive_30cm
CSVP_soil_C_passive_60cm
CSVP_soil_C_passive_90cm
CSVP_soil_C_residues_surface
CSVP_soil_C_residues_profile
CSVP_soil_C_residues_5cm
CSVP_soil_C_residues_10cm
CSVP_soil_C_residues_15cm
CSVP_soil_C_residues_30cm
CSVP_soil_C_residues_60cm
CSVP_soil_C_residues_90cm
CSVP_soil_C_residues_surface
CSVP_soil_C_residues_profile
CSVP_soil_C_residues_5cm
CSVP_soil_C_residues_10cm
CSVP_soil_C_residues_15cm
CSVP_soil_C_residues_30cm
CSVP_soil_C_residues_60cm
CSVP_soil_C_residues_90cm
CSVP_soil_C_decomposed_residue_profile
CSVP_soil_C_decomposed_residue_5cm
CSVP_soil_C_decomposed_residue_10cm
CSVP_soil_C_decomposed_residue_15cm
CSVP_soil_C_decomposed_residue_30cm
CSVP_soil_C_decomposed_residue_60cm
CSVP_soil_C_decomposed_residue_90cm
CSVP_soil_C_decomposed_residue_flat
CSVP_soil_C_decomposed_residue_stubble
CSVP_soil_C_decomposed_residue_attached
CSVP_soil_C_incorporated_by_tillage
CSVP_soil_C_removed_by_harvest
CSVP_soil_C_decomposed_SOM_profile
CSVP_soil_C_decomposed_SOM_5cm
CSVP_soil_C_decomposed_SOM_10cm
CSVP_soil_C_decomposed_SOM_15cm
CSVP_soil_C_decomposed_SOM_30cm
CSVP_soil_C_decomposed_SOM_60cm
CSVP_soil_C_decomposed_SOM_90cm

// soil nitrogen

   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_N_available));

   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_N_input));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_N_output));
// Soil pond

   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_water_content)); 1-31
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_plant_avail_water)); 1-31
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_water_potential)); 1-31
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_lateral_in_flow_depth)); 1-31
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_lateral_out_flow_depth)); 1-31
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_temperature));   1-31

   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_N_mineralization)); 1-31));


   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_P_P_amount)); 1-31
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_salinity)); 1-31
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_soil_base_salt)); 1-31
*/
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
RENDER_INSPECTORS_DEFINITION(CropSyst::Soil)
{
   emanator_known
      = Soil_base::render_inspectors(inspectors,context,instance);
   if (chemicals) chemicals->render_inspectors(inspectors,emanator_known,"chemical");
   //NYI if (erosion) erosion->render_inspectors(inspectors,&emanator,"erosion");
   //NYI if (tillage_effect) tillage_effect->render_inspectors(inspectors,&emanator,"tillage_effect");
   return emanator_known; // emanator;
}
//_2013-09-11___________________________________________________________________
RENDER_INSPECTORS_DEFINITION(NO3_with_CO2_Profile)
{
   // uses soil emanator                                                         //160616
   inspectors.append(new CS::Inspector_scalar(N2O_N_loss_daily,UC_kg_m2,*context,"N_N2O_emission/denitrification",TS_VALUE,CSVP_soil_N_N2O_loss_denitrification /*171222 CSVC_soil_N_N2O_loss_denitrification_time_step_sum*/ ));
   return 0; // emanator;
}
//______________________________________________________________________________
RENDER_INSPECTORS_DEFINITION(NH4_Profile_with_pH)
{
   // uses soil emanator                                                         //160616
   inspectors.append(new CS::Inspector_scalar(N2O_N_loss_daily,UC_kg_m2,*context,"N_N2O_emission/nitrification", TS_VALUE,CSVP_soil_N_N2O_loss_nitrification/*171222 CSVC_soil_N_N2O_loss_nitrification_time_step_sum*/));
   return 0; // emanator;
}
//______________________________________________________________________________
namespace CropSyst {
RENDER_INSPECTORS_DEFINITION(Land_unit_simulation_VX)
{

/*At this time I am not using instance description because
 * in MicroBasin it generates a inspector label for every cell.
 *
 * I should add an optional disambituation label to inspector
 * (Which would also be used by Crop
 *
   if (!instance_description)
      instance_description = get_key();
*/
   char cycle_cstr[5];
   CORN::nat8_to_cstr(cycle_shift,cycle_cstr,10,1,0);
   std::string new_instance(cycle_cstr);
   CS::Emanator &emanator  = CS::get_emanators()                                 //171115_160612
      .know((nat32)this,new_instance,get_ontology(),false,context,today);        //170317
   emanator_known = &emanator;                                                   //160614

   if (runoff) // Eventually move this to runoff
      inspectors.append(new CS::Inspector_scalar(runoff->estimated_runoff                     ,UC_m       ,emanator,/*check ontology*/"runoff/surface_water"    ,TS_VALUE,CSVP_soil_runoff_surface_water_runoff/*171222 CSVC_soil_runoff_surface_water_runoff_time_step_sum*/ ));
      // WARNING  multiple entries are showing up in UED file with different values



   inspectors.append(new CS::Inspector_scalar(nitrogen_daily_output.volatilization_loss_NH3   ,UC_kg_m2   ,emanator,/*check ontology*/"volatilization/N_NH3"    ,TS_VALUE,CSVP_soil_N_NH3_volatilization/*171222 CSVC_soil_N_NH3_volatilization_time_step_sum*/));
   inspectors.append(new CS::Inspector_scalar(nitrogen_daily_output.volatilization_total      ,UC_kg_m2   ,emanator,/*check ontology*/"volatilization/N_total"  ,TS_VALUE,CSVP_soil_N_volatilization_total/*171222 CSVC_soil_N_volatilization_total_time_step_sum*/));
   inspectors.append(new CS::Inspector_scalar(nitrogen_daily_output.applied_total             ,UC_kg_m2   ,emanator,/*check ontology*/"application/N_total"     ,TS_VALUE,CSVP_mgmt_N_applied /*17122 CSVC_mgmt_N_applied_time_step_sum*/));

//NYI CSVP_soil_C_all_surface
   inspectors.append(new CS::Inspector_scalar(profile_carbon_output.sum_profile  ,UC_kg_m2   ,emanator,/*check ontology*/"OM:C/profile" ,sum_statistic,CSVP_soil_C_all_profile/*171222 CSVC_soil_C_all_profile*/));
//NYI inspectors.append(new CS::Inspector_scalar(XXXXX                           ,UC_kg_m2   ,emanator,//PP_C_5cm      ,UC_kg_ha,inspectors.&(STAT_sum_bit|STAT_value_bit),TS_VALUE));  // WARNING verify statistics to use
//NYI inspectors.append(new CS::Inspector_scalar(XXXXX                           ,UC_kg_m2   ,emanator,//PP_C_10cm     ,UC_kg_ha,inspectors.&(STAT_sum_bit|STAT_value_bit),TS_VALUE));  // WARNING verify statistics to use
//NYI inspectors.append(new CS::Inspector_scalar(XXXXX                           ,UC_kg_m2   ,emanator,/PP_C_15cm     ,UC_kg_ha,inspectors.&(STAT_sum_bit|STAT_value_bit),TS_VALUE));  // WARNING verify statistics to use
   inspectors.append(new CS::Inspector_scalar(profile_carbon_output.sum_30cm     ,UC_kg_m2   ,emanator,/*check ontology*/"OM:C/30cm"    ,sum_statistic,CSVP_soil_C_all_30cm/*171222 CSVC_soil_C_all_30cm*/));
//NYI CSVP_soil_C_all_60cm
//NYI CSVP_soil_C_all_90cm

//NYI CSVP_mgmt_N_organic_applied
//NYI CSVP_mgmt_N_inorganic_applied

#ifdef REDOTHIS
180416
   // Reference ET
   #if ((CROPSYST_PROPER == 4) && !defined(VIC_CROPSYST_VERSION))
   inspectors.append(new CS::Inspector_scalar(

       ET_ref->ref_applicable_mm()
      ,UC_mm   ,emanator,/*check ontology*/"biometeorology:ET/potential/reference"    ,TS_VALUE,CSVP_weather_ET_ref /*171222 CSVC_weather_ET_ref_time_step_sum*/));
   #else
   //160731 NYI
   #endif

#endif

   // These are ET adjusted for actual crop cover, moving to Crop
   inspectors.append(new CS::Inspector_scalar(output_act_crop_evapotransp_m,UC_m,emanator,/*check ontology*/"crop:ET/act",TS_VALUE,CSVP_weather_ET_act /*171222 CSVC_weather_ET_act*/));
   inspectors.append(new CS::Inspector_scalar(output_pot_crop_evapotransp_m,UC_m,emanator,/*check ontology*/"crop:ET/pot",TS_VALUE,CSVP_weather_ET_pot /*171222 CSVC_weather_ET_pot*/));

   // Management

   inspectors.append(new CS::Inspector_scalar(total_irrigation_today   ,UC_m    ,emanator,/*check ontology*/"management:irrigation/applied"    ,TS_VALUE,CSVP_mgmt_irrig_applied));
   /*
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_mgmt_biomass_grazed));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_mgmt_biomass_unsatisfied));
   */

   // Nitrogen management
   /* NYI
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_mgmt_P_applied));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_mgmt_N_organic_gaseous_loss));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_mgmt_N_inorganic_gaseous_loss));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_misc_N_total_mineralization));
   */

   // Water table
   /*NYI
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_water_table_depth));
   */

   // eventually move to pond
   //NYI inspectors.append(new CS::Inspector_scalar(pond.xxx   ,UC_m   ,emanator,/*check ontology*/"pond"    ,TS_VALUE,CSVP_soil_pond_water_depth));

   if (soil) soil->render_inspectors(inspectors,emanator_known,soil->get_ontology());//160616
   if (organic_matter_residues_profile_kg_m2) organic_matter_residues_profile_kg_m2->render_inspectors(inspectors,emanator_known,"OM_and_residues");//160626
   return emanator_known; //emanator;
}
} // namespace CropSyst
//______________________________________________________________________________
namespace CS
{
RENDER_INSPECTORS_DEFINITION(Land_unit_meteorological)
{
   CS::Emanator &emanator = CS::get_emanators().know                             //171115
      ((nat32)this,"meteorology",get_ontology(),CS_NOT_EPHEMERAL
      ,0 // Currently rendering is propogating though land unit sim but we dont want that as the context (otherwise it get replicated)
      // the Simulation
      ,today);                                                                   //170319
   inspectors.append(new CS::Inspector_scalar(ref_precipitation_actual()                ,emanator,/*check ontology*/"precipitation/actual"             ,TS_VALUE/*171031 sum_statistic */,UED::STD_VC_precipitation.get()));   // UED::STD_VC_precipitation
   inspectors.append(new CS::Inspector_scalar(ref_precipitation_liberated()             ,emanator,/*check ontology*/"precipitation/liberated"          ,TS_VALUE/*171031 sum_statistic */ ,GENERATE_VARIABLE_CODE));
   inspectors.append(new CS::Inspector_scalar(ref_vapor_pressure_deficit_max()          ,emanator,/*check ontology*/"vapor_pressure"                   ,TS_VALUE/*171031 max_statistic */,UED::STD_VC_vapor_pressure_actual.get()));
   inspectors.append(new CS::Inspector_scalar(ref_vapor_pressure_daytime()              ,emanator,/*check ontology*/"vapor_pressure/daytime"           ,TS_VALUE/*171031 mean_statistic*/,GENERATE_VARIABLE_CODE));  //avg? sum?
   inspectors.append(new CS::Inspector_scalar(ref_vapor_pressure_nighttime()            ,emanator,/*check ontology*/"vapor_pressure/nighttime"         ,TS_VALUE/*171031 mean_statistic*/,GENERATE_VARIABLE_CODE));  //avg? sum?
   inspectors.append(new CS::Inspector_scalar(ref_air_temperature_max()                 ,emanator,/*check ontology*/"temperature/air/maximum"          ,TS_VALUE/*171031 max_statistic*/ ,UED::STD_VC_max_temperature.get()));
   inspectors.append(new CS::Inspector_scalar(ref_air_temperature_min()                 ,emanator,/*check ontology*/"temperature/air/minimum"          ,TS_VALUE/*171031 min_statistic*/ ,UED::STD_VC_min_temperature.get()));
   inspectors.append(new CS::Inspector_scalar(ref_air_temperature_avg()                 ,emanator,/*check ontology*/"temperature/air/average"          ,TS_VALUE/*171031 mean_statistic*/,UED::STD_VC_avg_temperature.get()));
   inspectors.append(new CS::Inspector_scalar(ref_solar_radiation()                     ,emanator,/*check ontology*/"irradiance/solar/global"/*"solar_radiation"*/ ,TS_VALUE/*171031 sum_statistic */,UED::STD_VC_solar_radiation_global.get()));
   inspectors.append(new CS::Inspector_scalar(ref_dew_point_temperature_max()           ,emanator,/*check ontology*/"temperature/dew_point"            ,TS_VALUE/*171031 max_statistic */,UED::STD_VC_max_dew_point_temperature.get()));
   inspectors.append(new CS::Inspector_scalar(ref_dew_point_temperature_min()           ,emanator,/*check ontology*/"temperature/dew_point"            ,TS_VALUE/*171031 min_statistic */,UED::STD_VC_min_dew_point_temperature.get()));
   inspectors.append(new CS::Inspector_scalar(ref_dew_point_temperature_avg()           ,emanator,/*check ontology*/"temperature/dew_point"            ,TS_VALUE/*171031 mean_statistic*/,UED::STD_VC_avg_dew_point_temperature.get()));
   inspectors.append(new CS::Inspector_scalar(ref_relative_humidity_max()               ,emanator,/*check ontology*/"relative_humidity/maximum"        ,TS_VALUE/*171031 max_statistic */,UED::STD_VC_max_relative_humidity.get()));
   inspectors.append(new CS::Inspector_scalar(ref_relative_humidity_min()               ,emanator,/*check ontology*/"relative_humidity/minimum"        ,TS_VALUE/*171031 min_statistic */,UED::STD_VC_min_relative_humidity.get()));
   //NYN    inspectors.append(new CS::Inspector_scalar(ref_vapor_pressure_actual()      ,emanator,/*check ontology*/"vapor_pressure/actual",UNKNOWN_statistic));
   inspectors.append(new CS::Inspector_scalar(ref_vapor_pressure_deficit_fullday_avg()  ,emanator,/*check ontology*/"vapor_pressure_deficit/fullday"  ,TS_VALUE/*171031mean_statistic*/ ,UED::STD_VC_avg_daytime_vapor_pressure_deficit.get())); //avg? sum?
   inspectors.append(new CS::Inspector_scalar(ref_vapor_pressure_deficit_daytime()      ,emanator,/*check ontology*/"vapor_pressure_deficit/daytime"  ,TS_VALUE/*171031mean_statistic*/ ,UED::STD_VC_avg_fullday_vapor_pressure_deficit.get())); //avg? sum?
   inspectors.append(new CS::Inspector_scalar(ref_wind_speed()                          ,emanator,/*check ontology*/"wind_speed"                      ,TS_VALUE/*171031sum_statistic*/  ,UED::STD_VC_wind_speed.get()));
   inspectors.append(new CS::Inspector_scalar(ref_CO2_current_conc()                    ,emanator,/*check ontology*/"CO2/atmospheric"                 ,TS_VALUE/*171031sum_statistic*/  ,GENERATE_VARIABLE_CODE)); //171220

   #if (CS_VERSION==5)
   inspectors.append(new CS::Inspector_scalar(
       ref_ET_reference().amount
      ,UC_m   ,emanator,/*check ontology*/"biometeorology:ET/potential/reference"    ,TS_VALUE,CSVP_weather_ET_ref /*171222 CSVC_weather_ET_ref_time_step_sum*/));
   #endif
   inspectors.append(new CS::Inspector_scalar(reported_snow_storage                ,UC_m,emanator,/*check ontology*/"snow_storage"                    ,sum_statistic  ,GENERATE_VARIABLE_CODE));
      //snow storage is already cumulative
   return &emanator;
}
//_2016-06-26_____________________________________________________________________________
} // namespace CS
//______________________________________________________________________________

