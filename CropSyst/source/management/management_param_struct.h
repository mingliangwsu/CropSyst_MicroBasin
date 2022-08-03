#ifndef management_param_struct2H
#define management_param_struct2H
//______________________________________________________________________________
#include "options.h"
#include "N_sources.h"
#include "corn/primitive.h"
#include "corn/math/compare.hpp"
#include "crop/crop_types.h"
//170225 #include "corn/datetime/date.hpp"
#include "mgmt_types.h"
#include "common/biomatter/manure_form.h"
#include "common/soil/SCS/SCS.h"
#include "common/residue/residue_const.h"
//______________________________________________________________________________
#define LABEL_org_N                 "org_N"
#define LABEL_NH3_amount            "NH3_amount"
#define LABEL_long_term_org_N_volatilization       "long_term_org_N_volatilization"
#define LABEL_decomposition_time                   "decomposition_time"
#define LABEL_decomposition_time_50                "decomposition_time_50"
#define LABEL_decomposition_time_calculated        "decomposition_time_calculated"
#define LABEL_org_N_volatilization_calculated      "org_N_volatilization_calculated"
#define LABEL_liquid                 "liquid"
#define LABEL_min_biomass              "min_biomass"
#define LABEL_percent_N_as_OM          "percent_N_as_OM"
#define LABEL_percent_N_as_NH3         "percent_N_as_NH3"
#define LABEL_min_LAI                  "min_LAI"
#define LABEL_soil_conservation_factor             "soil_conservation_factor"
#define LABEL_NH4_volatilization_calculated        "NH4_volatilization_calculated"
#define LABEL_percent                              "percent"
#define LABEL_salt                   "salt"
#define LABEL_NH4_amount            "NH4_amount"
#define LABEL_NO3_amount            "NO3_amount"
#define LABEL_NH4_volatilization                   "NH4_volatilization"
#define LABEL_max_biomass              "max_biomass"
#define LABEL_max_LAI                  "max_LAI"
#define LABEL_adj_rel_growth           "adj_rel_growth"

#define LABEL_automatic_N_mode                   "automatic_N_mode"
//120710 #define LABEL_automatic_NO3_mode                   "automatic_NO3_mode"

#define LABEL_amount                "amount"
#define LABEL_salinity               "salinity"

#define LABEL_land_treatment        "land_treatment"
#define LABEL_harvest                  "harvest"

/* check needed

#define LABEL_automatic_NO3_application_mode "automatic_NO3_application_mode"
*/
#define LABEL_automatic_irrigation  "automatic_irrigation"
/*
#define LABEL_chemicals              "chemicals"
#define LABEL_irrigations            "irrigations"
#define LABEL_tillages               "tillages"
#define LABEL_residues               "residues"
#define LABEL_fertilizations         "fertilizations"
#define LABEL_organic_fertilizations "organic_fertilizations"
*/
#define LABEL_concentration         "concentration"
#define LABEL_max_allowable_depletion              "max_allowable_depletion"
#define LABEL_depletion_observe_depth              "depletion_observe_depth"
#define LABEL_net_irrigation_mult                  "net_irrigation_mult"
#define LABEL_refill_point                         "refill_point"
#define LABEL_max_application                      "max_application"
#define LABEL_split_applications                   "split_applications"
#define LABEL_target_yield_N_uptake                "target_yield_N_uptake"
#define LABEL_critical_soil_N_for_no_response      "critical_soil_N_for_no_response"
#define LABEL_fertilizer_use_efficiency            "fertilizer_use_efficiency"
#define   LABEL_auto_clip_biomass      "auto_clip_biomass"
#define LABEL_trim_biomass_removed     "trim_biomass_removed"
#define LABEL_trim_removed_to_surface  "trim_removed_to_surface"
/*
#define LABEL_adjust_relative_growth_rate_for_clipping_obs   "adjust_relative_growth_rate_for_clipping"

//#define LABEL_minimum_biomass_required_for_clipping "minimum_biomass_required_for_clipping"

#define LABEL_biomass_forces_clipping_obs   "biomass_forces_clipping"

#define LABEL_harvest_wait             "harvest_wait"
#define LABEL_straw_to_residue         "straw_to_residue"

#define LABEL_earliest_date_to_clip    "earliest_date_to_clip"
#define LABEL_latest_date_to_clip      "latest_date_to_clip"
#define LABEL_minimum_LAI_required_for_clipping_obsolete "minimum_LAI_required_for_clipping"
#define LABEL_minimum_biomass_required_for_clipping_obsolete "minimum_biomass_required_for_clipping"
#define LABEL_V3_clipping_fate           "clipping_fate"
#define LABEL_row_layout      "row_layout"
#define LABEL_azimuth         "azimuth"
#define LABEL_spacing         "spacing"
#define LABEL_initial_width   "initial_width"
#define LABEL_initial_height  "initial_height"
#define LABEL_final_width     "final_width"
#define LABEL_final_height    "final_height"

*/
#define LABEL_sampling_depth                    "sampling_depth"
/*
#define LABEL_start_date      "start_date"
#define LABEL_start_phen_sync "start_phen_sync"
#define LABEL_start_offset    "start_offset"
#define LABEL_end_date        "end_date"
#define LABEL_end_phen_sync   "end_phen_sync"
#define LABEL_end_offset      "end_offset"
*/

#define DEFAULT_soil_conservation_factor  1.0
#define DEFAULT_land_treatment            STRAIGHT

#ifdef __cplusplus
// allow these struct to be available to VIC
namespace CropSyst {                                                             //120419
#endif
//______________________________________________________________________________
struct Tillage_operation_struct
{
   bool    dust_mulch_enable;                                                    //051206
   float32 dust_mulch_depth_cm;                                                  //051206
   int16   dust_mulch_effective_days;                                            //051206
   float32 dust_mulch_intensity;                                                 //051212
   struct Oxidation_effect                                                       //100121
   {  float32 sand;                                                              //100121
      float32 clay;                                                              //100121
    public:
      inline Oxidation_effect()
      : sand(1.5)
      , clay(0.5)
      {}
   } oxidation_effect;                                                           //100121
};
//_2011-01-13________________________________________Tillage_operation_struct__/
struct Organic_nitrogen_operation_abstract_struct
{
      Organic_matter_source   organic_matter_source;                             //110831
   // In the CropSyst model, kg/ha N converted to kg/m2 in the form of organic matter
   float32                    org_N_kg_ha;                                       //060717
      // Manure N is only from solid (organic) not including ureas
      // Managing Nitrogen for GroundWater QUality and Farm Profitability
      // R.F. Follett, D.R. Keeney, and R. M. Cruse (eds)
   float32                    NH3_N_kg_ha;                                       //060717
   Org_N_appl_method          org_N_appl_method;                                 //020322
   float32                    injection_depth_cm;                                //160119
   float32                    total_solids_kg_ha;                                //110818
      // total_solids_kg_ha currently used by CAFE_dairy but is generally applicable
      // currently CropSyst (parameter editor and the model)
      // calculates this from org_N
      // Eventually modify the parameter editor to continue to provide this
      // calculation, but save the value in the file.
   float32                    dry_matter_percent;                                //060717
   float32                    long_term_org_N_volatilization_loss_percent;       //020525
   float32                    water_depth_mm;                                    //110816 added for CAFE dairy
   float32                    water_volume_m3;                                   //110816 added for CAFE dairy
};
//_2011-01-13______________________Organic_nitrogen_operation_abstract_struct__/
struct Inorganic_nitrogen_operation_struct
{  Ammonium_source  NH4_source;                                                  //020322
   NH4_Appl_method  NH4_appl_method;                                             //020322
   float32  injection_depth_cm;                                                  //160119
   float32  NO3_N; /*kg/ha or % */                                               //060717
   float32  NH4_N; /*kg/ha or % */                                               //060717
      // For fixed inorganic nitrogen operation,                                 //120710
      // the N values are amounts kg/ha.                                         //120710
      // For auto N application, the N values are %.
      // N amounts are converted to kg/m2 when event table is generated
   bool     NH4_volatilization_calculated;                                       //990227
         // Force user supplied NH4_volatilization to be used overriding any
         // selections made by the radio buttons and computed by the model.}
   float32  NH4_volatilization; // % When NH4 is applied with no organic N
      // 0.0 is now a valid value (it used to disabled automatic calculation)
   struct Condition                                                              //170630
   {  // Eventually (V6) there will be a more generalized condition mechanism
      // for all managements 170706
      // only apply if soil N measured to the sample depth is less than critical
      float32 N_soil_critical;// kg/ha 0 indicates disable condition.
      float32 sampling_depth; // m     0 indicates entire profile.
    public:
      inline bool is_always_applicable()
         { return CORN::is_approximately<float32>(N_soil_critical,0.0); }
   } condition;
};
//_2011-01-15_____________________________Inorganic_nitrogen_operation_struct__/
struct Harvest_or_clipping_operation_struct
{
   // The following parameters apply to either specific or auto mode.
   Harvest_amount_mode     harvest_amount_mode;                                  //050822
   Harvest_fate_mode       harvest_fate_mode; // recorded only for parameter editor
   Biomass_fate_parameters biomass_fate_percents;
   float32  remove_amount_kg_ha;                                                 //050822
      // above ground biomass removed kg/ha (0.0 if not remove_fixed_amount)
   bool     accept_less;                                                         //050822
      // Applies only to fixed amount removed mode. If the canopy biomass - reserve is less than remove amount is less then do remove up to the reserve.
   float32  min_retain_GAI;                                                      //051103
      // Minimum amount of GAI m2/m2 to leave in the field after cutting. (for remove biomass mode)
   // The following parameters do not apply to auto clip biomass mode
   //110115 move to CropSyst_field_operation    bool           terminate_crop;   //031008
   float32  min_LAI_required;                                                    //020314
      // m2/m2 minimum_LAI_required_for_clipping  (0.0 disables this constraing)
   float32        min_biomass_required_kg_ha;                                    //040628
      // kg/ha  minimum biomass required for clipping
   float32        reserve_biomass_kg_ha;                                         //040807
      // This is an amount of biomass that can not or should not be removed
   float32       pasture_composition_legumes_percent;  // for grazing model      //040917
   // The following two are for grazing mode:
   int16         grazing_percent_N_as_OM;   // organic matter                    //040126
   int16         grazing_percent_N_as_NH3;  // ammonia                           //040126
};
//_2011-01-15____________________________Harvest_or_clipping_operation_struct__/
struct Auto_clip_biomass_mode_struct
{  // These parameters are in addition to those in Harvest_or_clipping_operation_struct
   float32  adj_relative_growth_rate;   bool consider_adjust_rate; // 0-2        //011208
   float32  LAI_forces_clipping;        bool consider_LAI;// m2/m2  If this LAI is reached clipping will occur  (0.0 disables this condition) //040830
   float32  biomass_forces_clipping;    bool consider_biomass;// kg/ha  function uses kg/m2  //970521
   int16    flowering_forces_clipping;  bool consider_flowering; // Days (0 = not considered)   //040830
 //Considerations are not saved to the file, they are updated based on selections. 040831
};
//_2011-01-15___________________________________Auto_clip_biomass_mode_struct__/
struct Irrigation_operation_struct
{
   Irrigation_application_mode   application_mode;                               //041028
   Irrigation_consideration_mode consideration_mode;                             //091201
   Depletion_observation_depth_mode depletion_observation_depth_mode;            //070606

   //NYI add start hour (and duration)

   #if (CS_VERSION==5)
   bool    disable_when_precipitation;
   #endif

   float32 amount_mm;   //{ irrigation: amount (mm), converted to m when event table is generated}  value for fixed amount mode
   float32 salinity; //{ salt dS/m converted to kg chem/m3 soil. }
   float32 ECw_to_TDS;  // Usually about 0.64 Electrical Conductivity dS/m to Totals Dissolved Solids (kg/m3)  //080402_
   float32 NO3_N_concentration; // { concentration (kg chem/m3 soil) (With irrigation)} 080213
   float32 NH4_N_concentration; // { concentration (kg chem/m3 soil) (With irrigation)} 080213

      // Not in version 5 the concentration should be the concentration of the
      // water (percentage based)
      // not with respect to soil N concentation
      // (maybe it is the same, maybe users have been accuming water concentration).

   float32 net_irrigation_mult; // for simple irrigation event the default value is 1.0 this is overridden auto irrig events
   float32 refill_point;   // 0-1 0 refills to PWP  1 refills to FC 051228_
   // The following used to be only in auto irrig, but Luca pointed out they can also be useful
   // in the option when the specific date irrigation recharges soil profile. 041028_
   float32 max_allowable_depletion;
   float32 depletion_observe_depth_m;          //{ m this is the maximum depth we examine for automatic irrigaiton conditions }
   float32 depletion_observe_root_zone_fract;  // fraction 0 or greater (usually less than 1.0 and mostly less than 2.0, but unbounded 070606_
   float32 min_application_mm;  // mm   This was added because Rolf Sommer identified that with many irrigation systems it is not possible for equipment to provide trivial amounts 060719_
   float32 max_application_mm;  // mm
   float32 leaf_water_potential; // -J/kg                                        //091201

   Directed_irrigation_soil_wetting soil_wetting;                                //130313
   std::string chemical_name;
   nat16 irrigation_type;                                                        //150701LML
};
//________________________________________________Irrigation_operation_struct__/
struct N_application_soil_observation_mode_structX
{
   Automatic_N_mode automatic_N_mode;                                            //020322
   float32 target_yield_N_uptake_kg_ha;  // kg/ha  Crop N uptake for target yield  990208
   float32 estimated_mineralization_kg_ha;  // kg/ha                             //120710
   #if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION <=4))
   float32 critical_soil_N_for_no_response_kg_ha;// kg/ha                        //990208
   #endif
   float32 fertilizer_use_efficiency;    // % 0-100                              //990208
   float32 soil_N_sampling_depth;        // m                                    //990208
/*1706023 obsolete now Supplemental application is achieved with
normal fixed management but now condition for application is added
   struct Supplemental                                                           //161201
   {
      bool    enabled;
      float32 critical_soil_N_kg_ha;
      float32 fraction;  // 0 disables the supplemental application
      inline bool is_enabled() affirmation_ {return enabled && (fraction>0.0); } //161205
   };
   Supplemental supplemental;
*/
   // check obsolete
   bool    split_applications;                                                   //000510
   /* I should have a separate set of applications for each mode,
      but I would have to store the list for each section, and this was not how
   it was stored in V3, normally there will only be one mode entry anyway 040712
   */
};
//_2000-05-19______________________N_application_soil_observation_mode_struct__/
struct Chemical_operation_struct
{
   float32 chemical_concentration; // { concentration (kg chem/m3 soil) (With irrigation)}
   std::string chemical_name;
};
//_2011-01-XX_______________________________________Chemical_operation_struct__/
#ifdef __cplusplus
} // namespace CropSyst
#endif
#endif

//#endif
