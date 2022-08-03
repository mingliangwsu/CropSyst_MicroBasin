#ifndef cs_UED_dailyH
#define cs_UED_dailyH

#include "UED/library/UED_tuple_datasrc.h"
#include "corn/data_source/datarec.h"
#include "cs_vars.h"
#include "csvc.h"
#include "corn/measure/units.h"
//______________________________________________________________________________
namespace CS         { class Desired_variables; }
namespace CropSyst   { class Land_unit_simulation; }                             //141206
namespace CropSyst
{
//______________________________________________________________________________
class CS_UED_tuple_data_source
: public UED::Tuple_data_source
{
public:
   CS_UED_tuple_data_source(UED::Database_file_indexed *database );
   void register_fields
      (const CS::Desired_variables &desired_vars
      ,nat8 num_sublayers,Units_code time_stamp_step);
private:
   void register_layer_field                                                     //041002
      (UED_variable_code variable_code,nat8 num_sublayers
      ,const char *section,const char *base_field_name
      ,Units_code preferred_units,Units_code stored_units
      ,Units_code time_stamp_step);
};
//_2003-07-15___________________________________________________________________
class CS_daily_data_record
: public CORN::Data_record    // ? Data_source_abstract? probably not because don't need indexer or modified
{
   CropSyst::Land_unit_simulation    &land_unit_sim; // Owned by
   const CS::Desired_variables &desired_vars;                                    //170225
   float32 crop_act_root_biomass;
   float32 crop_water_stress_stats;
   float32 crop_temperature_stress_stats;
   float32 crop_growing_degree_days;
   float32 crop_seasonal_thermal_time;
   float32 crop_dry_biomass_kg_m2;
   float32 crop_live_biomass_kg_m2;
   float32 crop_fruit_biomass_kg_m2;
   float32 crop_fruit_canopy_biomass_kg_m2;
   float32 crop_leaf_area_index;
   float32 crop_green_area_index;
   float32 crop_root_depth_m;
   float32 crop_crop_water_stress_index;
   float32 crop_temperature_stress_index;
   float32 crop_VPD_daytime;
   float32 crop_intercepted_PAR;
   float32 crop_intercepted_PAR_accum;
   float32 crop_canopy_ground_cover;
   float32 crop_leaf_water_pot;
   float32 residue_ground_cover;
   float32 residue_water_storage_m;
   float32 residue_surface_biomass_kg_m2;
   float32 residue_plant_incorporated_kg_m2;
   float32 residue_manure_incorporated_kg_m2;
   float32 soil_clod_rate;
   float32 ET_pot_m;
   float32 ET_act_m;
   float32 ET_ref_m;                                                             //130723
   float32 crop_transp_pot_m;
   float32 crop_transp_act_m;
   float32 soil_evap_pot_m;
   float32 soil_evap_act_m;
   float32 residue_evap_pot_m;
   float32 residue_evap_act_m;
   float32 management_irrigation_m;
   float32 biomass_unsatisfied_kg_m2;

//NYI here I could output biomass_grazed

   float32 weather_precipitation_m;
   float32 weather_temperature_max;
   float32 weather_temperature_min;
   float32 weather_solar_rad_MJ_m2;
   float32 crop_water_inter_m;
   float32 residue_water_inter_m;
   float32 soil_surface_water_runoff_m;
   float32 soil_water_entering_m;
   float32 soil_water_drainage_m;
               // eventually we will have a water balance report which will use balance_drainage
               // we will restore here the reported drainage.
   float32 weather_snow_storage_m;
   float32 soil_water_depletion_balance_m;
   float32 soil_water_depletion_seasonal_m;
   //131001 float32 soil_water_depletion_m;
   float32 soil_water_balance_m;
#ifdef NITROGEN
   float32 nitrogen_applied_kg_m2;
   float32 nitrogen_uptake_kg_m2;
   float32 nitrogen_leached_kg_m2;
   float32 residue_mineralizated_straw_kg_m2;
   float32 residue_mineralizated_manure_kg_m2;
   float32 OM_mineralization_orig_kg_m2;  // was mineralizated_OM_kg_m2
   float32 OM_mineralization_new_kg_m2;
   float32 nitrogen_organic_N_applied_kg_m2;
   float32 nitrogen_N_immobilization_kg_m2;
   float32 nitrogen_stress_factor;
   float32 nitrogen_stress_index;
   float32 nitrogen_avg_stress_index;
   float32 nitrogen_uptake_accum_kg_m2;
   float32 nitrogen_mass_canopy_current_kg_m2;                                   //131006_110915
   float32 nitrogen_mass_canopy_production_kg_m2;                                //131006_110915
   float32 nitrogen_plant_N_concentration_deprecated;  // this used to be actually only the canopy
   float32 nitrogen_canopy_concentration;
   float32 nitrogen_root_concentration;
   float32 nitrogen_automatic_N_in_uptake_kg_m2;
   float32 nitrogen_fixation_kg_m2;
   float32 nitrogen_plant_N_concentration_min;
   float32 nitrogen_plant_N_concentration_max;
   float32 nitrogen_plant_N_concentration_critical;
#endif
// growth period accumulation
   float32 ET_pot_accum_GP_m;
   float32 ET_act_accum_GP_m;
   float32 ET_ref_accum_GP_m;                                                    //130723
   float32 crop_transp_pot_accum_GP_m;
   float32 crop_transp_act_accum_GP_m;
   float32 soil_evap_pot_accum_GP_m;
   float32 soil_evap_act_accum_GP_m;
   float32 residue_evap_pot_accum_GP_m;
   float32 residue_evap_act_accum_GP_m;
   float32 management_irrig_accum_GP_m;
   float32 weather_precip_accum_GP_m;
   float32 crop_water_intrcpt_accum_GP_m;
   float32 residue_water_intrcpt_accum_GP_m;
   float32 surface_water_runoff_accum_GP_m;
   float32 ponded_water_GP_m;
   float32 soil_water_enter_accum_GP_m;
   float32 soil_water_drain_accum_GP_m;
               // eventually we will have a water balance report which will use balance_drainage
               // we will restore here the reported drainage.
#ifdef NITROGEN
   float32 nitrogen_applied_accum_GP_kg_m2;
   float32 nitrogen_leached_accum_GP_kg_m2;
   float32 mineralizated_residue_accum_GP_kg_m2;
   float32 mineralizated_manure_accum_GP_kg_m2;
   float32 OM_mineralization_orig_accum_GP_kg_m2;
   float32 OM_mineralization_new_accum_GP_kg_m2;
   float32 N_immobilization_accum_GP_kg_m2;
   float32 automatic_N_in_uptake_accum_GP_kg_m2;
   float32 organic_N_applied_accum_GP_kg_m2;
   float32 N_Fixation_accum_GP_kg_m2;
#endif
// continuous is the default mode case CONTINUOUS_ACCUM :
   float32 ET_pot_accum_cont_m;
   float32 ET_act_accum_cont_m;
   float32 ET_ref_accum_cont_m;                                                  //130723
   float32 crop_transp_pot_accum_cont_m;
   float32 crop_transp_act_accum_cont_m;
   float32 soil_evap_pot_accum_cont_m;
   float32 soil_evap_act_accum_cont_m;
   float32 residue_evap_pot_accum_cont_m;
   float32 residue_evap_act_accum_cont_m;
   float32 management_irrig_accum_cont_m;
   float32 management_biomass_unsatisfied_accum_cont_m;
   float32 weather_precip_accum_cont_m;
   float32 crop_water_intrcpt_accum_cont_m;                                      //160414
   float32 residue_water_intrcpt_accum_cont_m;
   float32 surface_water_runoff_accum_cont_m;
   float32 ponded_water_cont_m;
   float32 water_table_depth_m;
   float32 soil_water_enter_accum_cont_m;
   float32 soil_water_drain_accum_cont_m;
#ifdef NITROGEN
   float32 nitrogen_applied_accum_cont_kg_m2;
   float32 nitrogen_leached_accum_cont_kg_m2;
   float32 OM_mineralization_orig_accum_cont_kg_m2;
   float32 OM_mineralization_new_accum_cont_kg_m2;
   //110918 float32 mineralizated_OM_accum_cont_kg_m2;
   float32 mineralizated_residue_accum_cont_kg_m2;
   float32 mineralizated_manure_accum_cont_kg_m2;
   float32 N_immobilization_accum_cont_kg_m2;
   float32 automatic_N_in_uptake_accum_cont_kg_m2;
   float32 organic_N_applied_accum_cont_kg_m2;
   float32 N_Fixation_accum_cont_kg_m2;
   float32 N_inorganic_gaseous_loss_GP;
   float32 N_inorganic_gaseous_loss_cont;                                        //110918
#endif
#ifdef PHOSPHORUS
   float32 phosphorus_applied_kg_m2;                                             //110801
   float32 phosphorus_uptake_kg_m2;                                              //110801
   float32 phosphorus_uptake_accum_kg_m2;                                        //110801
   float32 phosphorus_applied_accum_kg_m2;                                       //110801
#endif
#ifdef NITROGEN
 protected: // These are used to calculated daily values from cumulative
   float64 last_NO3_applied_E;
   float64 last_NH4_applied_E;
   float64 last_NO3_uptake_E;
   float64 last_NH4_uptake_E;
   float64 last_NO3_leached_E;
   float64 last_NH4_leached_E;
#endif
   float32 OM_gaseous_CO2_C_loss;                                                //160516
   float32 WUE;                                                                  //160522
   float32 DegHr_above_30;                                                       //160522
   float32 DegHr_above_34;                                                       //160522
 public:
   CS_daily_data_record
      (CropSyst::Land_unit_simulation &land_unit_sim
      ,const CS::Desired_variables &desired_vars);                               //170225
   virtual bool expect_structure(bool for_write);                                //161025
   virtual bool set_start();                                                     //161023_120426
};
//_2003-07-15__041021___________________________________________________________
}// namespace CropSyst
#endif

