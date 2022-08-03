
// Obsolete in V5 which only Outputs UED files
// but still used for GIS module variable selection
#  include "cs_variables.h"
#  include "cs_mod.h"
#  include "static_phrases.h"
#  include "rptoptns.h"
#include "UED/library/UED_codes.h"

#define TL_BLANKLINE ""

enum colors {WHITE,BLACK,GRAY,LIGHT_GRAY,BLUE,LIGHT_BLUE,RED,LIGHTRED,GREEN,LIGHT_GREEN,YELLOW,BROWN,CYAN,LIGHT_CYAN,MAGENTA,LIGHT_MAGENTA};

//UNIT rptoptns;

/*
  How to add entries to the available variables for output:

  Add the entry in the list for the respective DLY,YLY, or HRV report.

  Increment the respective MAX_xxx_entries (where xxx is dly,yly,or hrv).

  Renumber the ID: numbers. (yearly report variables are numbered starting
  at 0, yearly starts at 100, and harvest starts at 200). ID numbers
  0,100 and 200 should be blank.

  Make sure that the rpt: field has the correct DLY,YLY,or HRV designation.

  For daily report variables, you must specify either ,true or ,false
  depending whether the variable is to be available for graphing using
  the view graph utility.

  Variables which are text (ie crop_name) must have ,false and d:0.
  Variables which are integer must have d:0;
*/
//______________________________________________________________________________
group_report_var_layout NB_report_var_opts[MAX_NB_entries] =
{  {0,0,TL_BLANKLINE,0      ,TL_BLANKLINE,TL_BLANKLINE}
,  {8,3,TU__kgN_ha_,UC_kg_ha, "NH4 or NH3",    TL_applied}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_BLANKLINE,    TL_Organic_nitrogen_applied}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NH4,    "not implement_in this_version (mineralized_from_residues)"} // TL_Mineralized_from_residue}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NH4,    "not implement_in this_version (mineralized_from_organic_fertilizer)"} // TL_Mineralized_from_organic_fertilizer}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NH4,    TL_Mineralized_from_organic_matter}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NH4,    TL_leached}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NH4,    TL_uptake}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_BLANKLINE,    TL_NH3_with_manure_N_gaseous_loss}   // eventually add NH3
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NH4,    TL_Inorganic_N_gaseous_loss}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NH4,    TL_Initial_profile_content}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NH4,    TL_Final_profile_content}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NH4,    TL_balance}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NO3,    TL_applied}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NO3,    TL_Nitrification}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NO3,    TL_leached}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NO3,    TL_uptake}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NO3,    TL_Denitrification}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NO3,    TL_Initial_profile_content}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NO3,    TL_Final_profile_content}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_NO3,    TL_balance}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,TL_applied}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,TL_Organic_nitrogen_applied}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,TL_Mineralization}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,TL_gaseous_loss}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,TL_leached}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,TL_uptake}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,"immobilization"} // L_immobilization
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,TL_Initial_profile_content}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,TL_Final_profile_content}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,TL_balance}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,"N2O loss (portion_of denitrification)"}
,  {8,3,TU__kgN_ha_,UC_kg_ha, TL_Total_N,"N2O loss (portion_of nitrification)"}
};

// The four entry in the daily report variables must be JULIAN DAY
//______________________________________________________________________________
report_var_layout_with_graph DLY_report_var_opts[DLY_MAX_IDS]=
{{0/*DLY_ID*/                     , 0,0,TL_BLANKLINE       ,0          ,TL_BLANKLINE                           ,false,LAYOUT_NO_OPTIONS},
 {DLY_year                        , 5,0,TL_BLANKLINE       ,UT_year,"Year" /*T_date_Year */                    ,false,LAYOUT_NO_OPTIONS},
 {DLY_day_of_year                 , 4,0,TL_BLANKLINE       ,UT_day_of_year,"Day of year" /*T_date_Day_of_year*/,false,LAYOUT_NO_OPTIONS},
 {DLY_month                       , 4,0,TL_BLANKLINE       ,UT_month   ,"Month" /*T_date_Month  */             ,false,LAYOUT_NO_OPTIONS},
 {DLY_day                         , 4,0,TL_BLANKLINE       ,UT_day_of_month,"Day" /*T_date_Day  */             ,false,LAYOUT_NO_OPTIONS},
 {DLY_crop_name                   ,60,0,TL_BLANKLINE       ,0          ,TL_Crop_name                           ,false,LAYOUT_NO_OPTIONS},
 {DLY_growth_stage                ,30,0,TL_BLANKLINE       ,0          ,TL_Growth_stage                        ,false,LAYOUT_NO_OPTIONS},
 {CSVC_crop_base_growing_degree_days_period_accum         , 6,1,TL_BLANKLINE       ,UC_Celcius_degree_days          ,TL_Growing_degree_days                 ,true,RTG_Crop          ,BLACK,true},
 {CSVC_crop_base_seasonal_thermal_time_period_sum         , 6,1,TL_BLANKLINE       ,UC_Celcius_degree_days          ,"Seasonal thermal time"                ,true,RTG_Crop          ,BLACK,true},
 {CSVC_crop_biomass_canopy        , 7,1,TU__kg_ha_         ,UC_kg_ha   ,"Above ground biomass_(drywt)"         ,true,RTG_Crop          ,YELLOW,true},  // 070207 was DLY_dry_biomass
 {CSVC_crop_base_green_biomass    , 7,1,TU__kg_ha_         ,UC_kg_ha   ,"Live green biomass_(drywt)"           ,true,RTG_Crop          ,YELLOW,true},
 {CSVC_crop_base_root_biomass_current, 7,1,TU__kg_ha_         ,UC_kg_ha   ,TL_Root_biomass                     ,true,RTG_Crop          ,LIGHT_GRAY,true},

 {DLY_fruit_biomass               , 7,1,TU__kg_ha_         ,UC_kg_ha   ,"Fruit biomass"                        ,true,RTG_Crop          ,LIGHT_GRAY,true},
 {CSVC_crop_base_fruit_canopy_biomass, 7,1,TU__kg_ha_         ,UC_kg_ha   ,"Non-fruit above_ground biomass"       ,true,RTG_Crop          ,LIGHT_GRAY,true},

 {CSVC_crop_base_orchard_solid_canopy_interception  , 7,1,"(m2/m2)"   ,UC_m2_m2   ,"Orchard solid canopy interception",true,RTG_Crop          ,LIGHT_GRAY,true},
 {CSVC_crop_base_orchard_shaded_area_GAI                , 7,1,"(m2/m2)"   ,UC_m2_m2   ,"Orchard shaded area GAI"              ,true,RTG_Crop          ,LIGHT_GRAY,true},
 {CSVC_crop_base_orchard_canopy_porosity            , 7,1,"0-1"       ,UC_fraction,"Orchard canopy porosity"          ,true,RTG_Crop          ,LIGHT_GRAY,true},


{DLY_leaf_area_index             , 7,2,"(m2/m2)"          ,UC_m2_m2   ,TL_Leaf_area_index                     ,true,RTG_Crop          ,GREEN,true},
{DLY_green_area_index            , 7,2,"(m2/m2)"          ,UC_m2_m2   ,TL_Green_area_index                    ,true,RTG_Crop          ,LIGHT_GREEN ,true},
{DLY_root_depth                  , 7,2,TU__m_             ,UC_m       ,TL_Root_depth                          ,true,RTG_Crop          ,WHITE,true },

{DLY_crop_water_stress           , 6,2,TL_index           ,UC_index,TL_Crop_water_stress                   ,true,RTG_Stress        ,BLUE,true }, /*14*/
{DLY_temperature_stress          , 6,2,TL_index           ,UC_index,TL_Temperature_stress                  ,true,RTG_Stress        ,RED ,true}, /*15*/

{CSVC_crop_base_tuber_init_temp_stress_index, 6,2,TL_index,UC_index,"Tuber_init temperature stress"   ,true,RTG_Stress        ,BLUE,true }, /*14*/
{CSVC_crop_base_tuber_fill_temp_stress_index, 6,2,TL_index,UC_index,"Tuber_filling temperature stress",true,RTG_Stress        ,RED,true }, /*15*/


{DLY_VPD_daytime                 , 6,2,"(kPa)"            ,UC_kPa     ,"Daytime vapor pressure deficit",true,RTG_Crop,RED,true},
{DLY_intercepted_PAR             , 6,2,"(MJ/m²)"          ,UC_MJ_m2   ,"Intercepted photosynthetically_active solar_radiation",true,RTG_Crop,RED,true},
{CSVC_crop_base_leaf_water_pot   , 6,2,"(J/kg)"           ,UC_J_per_kg,"Leaf water potential"         ,true,RTG_Crop,RED},

{CSVC_crop_base_intercepted_PAR_accum_to_date_time        , 6,2,"accum (MJ/m²)"   ,UC_MJ_m2   ,"Intercepted solar_radiation (total_or_PAR_depending_on_crop_option)",true,RTG_Crop_accum,RED,true},
//080429              This may be either PAR or total radiation depending on the model used

{DLY_canopy_ground_cover         , 6,3,TU__percent_       ,UC_percent ,TL_Canopy_ground_cover                 ,true,RTG_Crop          ,BROWN,true}, /*16*/
{DLY_residue_ground_cover        , 6,3,TU__percent_       ,UC_percent ,TL_Residue_ground_cover                ,true,RTG_Residue       ,BROWN,true }, /*17*/
{DLY_residue_water_storage       , 6,2,TU__mm_            ,UC_mm      ,TL_Residue_water_storage               ,true,RTG_Residue       ,BLUE,true}, /*18*/

{CSVC_residue_surface_biomass    , 7,3,TU__kg_ha_         ,UC_kg_ha,"Residue (all) surface current"            ,true,RTG_Residue       ,MAGENTA,true},
{CSVC_residue_plant_surface      , 7,3,TU__kg_ha_         ,UC_kg_ha,"Residue plant surface current"            ,true,RTG_Residue       ,MAGENTA,true},
{CSVC_residue_manure_surface     , 7,3,TU__kg_ha_         ,UC_kg_ha,"Residue manure surface current"           ,true,RTG_Residue       ,MAGENTA,true},
{CSVC_residue_incorporated    	, 7,3,TU__kg_ha_         ,UC_kg_ha,"Residue (all) soil_profile current"       ,true,RTG_Residue       ,MAGENTA,true},
{CSVC_residue_plant_incorporated , 7,3,TU__kg_ha_         ,UC_kg_ha,"Residue plant soil_profile current"       ,true,RTG_Residue       ,MAGENTA,true},
{CSVC_residue_manure_incorporated, 7,3,TU__kg_ha_         ,UC_kg_ha,"Residue manure soil_profile current"      ,true,RTG_Residue       ,MAGENTA,true},

{DLY_soil_clod_rate              , 6,2,TU__m_             ,UC_m       ,TL_Soil_clod_factor_rate               ,true,RTG_Soil          ,YELLOW,true}, /*21*/
{DLY_soil_loss                   , 4,2,TU__tn_ha_         ,UC_tn_ha,TL_Soil_loss                           ,true,RTG_Soil          ,BROWN,true }, /*22*/

{DLY_ET_pot                      , 6,2,TU__mm_            ,UC_mm      ,TL_Potential_evapotranspiration        ,true,RTG_weather       ,MAGENTA ,true}, /*23*/
{DLY_ET_act                      , 6,2,TU__mm_            ,UC_mm      ,TL_Actual_evapotranspiration           ,true,RTG_weather       ,LIGHT_MAGENTA ,true}, /*24*/
{DLY_transp_pot                  , 6,2,TU__mm_            ,UC_mm      ,TL_Potential_transpiration             ,true,RTG_Crop          ,CYAN,true}, /*25*/
{DLY_transp_act                  , 6,2,TU__mm_            ,UC_mm      ,TL_Actual_transpiration                ,true,RTG_Crop          ,LIGHT_CYAN,true}, /*26*/
{DLY_evap_soil_pot               , 6,2,TU__mm_            ,UC_mm      ,TL_Potential_soil_evaporation          ,true,RTG_Soil          ,CYAN ,true}, /*27*/
{DLY_evap_soil_act               , 6,2,TU__mm_            ,UC_mm      ,TL_Actual_soil_evaporation             ,true,RTG_Soil          ,LIGHT_CYAN ,true}, /*28*/
{DLY_evap_residue_pot            , 6,2,TU__mm_            ,UC_mm      ,TL_Potential_residue_evaporation       ,true,RTG_Residue       ,CYAN ,true}, /*29*/
{DLY_evap_residue_act            , 6,2,TU__mm_            ,UC_mm      ,TL_Actual_residue_evaporation          ,true,RTG_Residue       ,LIGHT_CYAN,true}, /*30*/
{DLY_irrigation                  , 6,2,TU__mm_            ,UC_mm      ,TL_Irrigation                          ,true,RTG_Management    ,BLUE,true}, /*31*/
{UED_STD_VC_Tavg                 , 6,2,"°C"               ,UC_Celcius ,"Air temperature average"              ,true,RTG_weather       ,RED,true},
{DLY_precipitation               , 6,2,TU__mm_            ,UC_mm      ,TL_Precipitation                       ,true,RTG_weather       ,BLUE ,true}, /*32*/
{DLY_crop_water_inter            , 6,2,TU__mm_            ,UC_mm      ,TL_Crop_water_interception             ,true,RTG_Crop          ,LIGHT_GRAY,true}, /*33*/
{DLY_residue_water_inter         , 6,2,TU__mm_            ,UC_mm      ,TL_Residue_water_interception          ,true,RTG_Residue       ,GRAY,true}, /*34*/
{DLY_surface_water_runoff        , 6,2,TU__mm_            ,UC_mm      ,TL_Surface_water_runoff                ,true,RTG_Soil          ,LIGHT_GREEN ,true}, /*35*/
{DLY_water_entering_soil         , 6,2,TU__mm_            ,UC_mm      ,TL_Water_entering_soil                 ,true,RTG_Soil          ,GREEN,true}, /*36*/
{DLY_soil_water_drainage         , 6,2,TU__mm_            ,UC_mm      ,TL_Soil_water_drainage                 ,true,RTG_Soil          ,RED,true}, /*37*/
{DLY_ET_pot_accum                , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Potential_evapotranspiration        ,true,RTG_weather_accum ,MAGENTA,true},/*38*/
{DLY_ET_act_accum                , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Actual_evapotranspiration           ,true,RTG_weather       ,LIGHT_MAGENTA,true},/*39*/
{DLY_transp_pot_accum            , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Potential_transpiration             ,true,RTG_Crop          ,CYAN ,true},/*40*/
{DLY_transp_act_accum            , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Actual_transpiration                ,true,RTG_Crop          ,LIGHT_CYAN,true},/*41*/
{DLY_evap_soil_pot_accum         , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Potential_soil_evaporation          ,true,RTG_Soil          ,CYAN,true},/*42*/
{DLY_evap_soil_act_accum         , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Actual_soil_evaporation             ,true,RTG_Soil          ,LIGHT_CYAN,true},/*43*/
{DLY_evap_residue_pot_accum      , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Potential_residue_evaporation       ,true,RTG_Residue       ,CYAN,true},/*44*/
{DLY_evap_residue_act_accum      , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Actual_residue_evaporation          ,true,RTG_Residue       ,LIGHT_CYAN,true },/*45*/
{DLY_irrig_accum                 , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Irrigation                          ,true,RTG_Management    ,BLUE,true},/*46*/
{DLY_precip_accum                , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Precipitation                       ,true,RTG_weather       ,BLUE ,true},/*47*/
{DLY_crop_water_intrcpt_accum    , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Crop_water_interception             ,true,RTG_Crop_accum    ,LIGHT_GRAY,true},/*48*/
{DLY_residue_water_intrcpt_accum , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Residue_water_interception          ,true,RTG_Soil_accum    ,GRAY,true},/*49*/
{DLY_surface_water_runoff_accum  , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Surface_water_runoff                ,true,RTG_Soil_accum    ,LIGHT_GREEN,true},/*50*/
{DLY_ponded_water                , 7,2,TU__mm_            ,UC_mm      ,TL_Ponded_water                        ,true,RTG_Soil_accum    ,LIGHT_GREEN,true},/*51*/
{DLY_water_enter_soil_accum      , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Water_entering_soil                 ,true,RTG_Soil_accum    ,GREEN,true },/*52*/
{DLY_soil_water_drain_accum      , 7,2,TU_accum__mm_      ,UC_mm      ,TL_Soil_water_drainage                 ,true,RTG_Soil_accum    ,RED,true},/*53*/

{DLY_snow_storage                , 6,2,TU__mm_            ,UC_mm      ,TL_Snow_storage                         ,true,RTG_weather       ,WHITE ,true},
{CSVC_soil_base_water_depletion_balance_accum_to_date_time  , 7,2,TU__mm_,UC_mm,TL_Soil_water_depletion        ,true,LAYOUT_NO_OPTIONS },
{CSVC_soil_base_water_depletion_seasonal_period_sum         , 7,2,TU__mm_,UC_mm,"Soil water depletion seasonal",true,LAYOUT_NO_OPTIONS },  //131007
{DLY_soil_water_balance          , 7,2,TU__mm_            ,UC_mm      ,TL_Soil_water_balance                   ,true,LAYOUT_NO_OPTIONS },

{DLY_nitrogen_stress_index       , 7,3,TL_index           ,UC_index ,TL_Nitrogen_stress                     ,true,RTG_Stress        ,MAGENTA,true}, /*57*/
{DLY_avg_nitrogen_stress_index   , 7,3,TL_index           ,UC_index,TL_Average_nitrogen_stress             ,true,RTG_Stress        ,LIGHT_MAGENTA,true }, /*58*/

{DLY_nitrogen_applied            , 7,3,TU__kgN_ha_        ,UC_kg_ha,TL_Inorganic_nitrogen_applied          ,true,RTG_Management    , MAGENTA,true}, /*82*/
{DLY_nitrogen_uptake             , 7,3,TU__kgN_ha_        ,UC_kg_ha,TL_Total_nitrogen_uptake               ,true,RTG_Crop, MAGENTA,true}, /*83*/
{DLY_nitrogen_leached            , 7,3,TU__kgN_ha_        ,UC_kg_ha,TL_Nitrogen_leached                    ,true,RTG_Soil, MAGENTA,true}, /*85*/

{DLY_nitrogen_applied_accum      , 7,3,TU_accum__kgN_ha_  ,UC_kg_ha,TL_Inorganic_nitrogen_applied          ,true,RTG_Management_accum , MAGENTA,true}, /*86*/
{DLY_nitrogen_uptake_accum       , 7,3,TU_accum__kgN_ha_  ,UC_kg_ha,TL_Total_nitrogen_uptake               ,true,RTG_Crop_accum    , MAGENTA,true}, /*87*/
{CSVC_crop_N_mass_canopy_production_accum_to_date_time , 7,3,TU__kgN_ha_       ,UC_kg_ha,"N_Mass canopy production"                        ,true,RTG_Crop    , LIGHT_MAGENTA,true}, /*88*/ //110915
{CSVC_crop_N_mass_canopy_current , 7,3,TU__kgN_ha_       ,UC_kg_ha,"N_Mass current canopy"                        ,true,RTG_Crop    , LIGHT_MAGENTA,true}, /*88*/ //110915
{DLY_nitrogen_leached_accum      , 7,3,TU_accum__kgN_ha_  ,UC_kg_ha,TL_Nitrogen_leached                    ,true,RTG_Soil_accum    , MAGENTA,true}, /*89*/

{CSVC_crop_N_conc_canopy         , 7,3,TU__kg_kg_         ,UC_kg_kg  ,"N concentration canopy"             ,true,RTG_Crop          ,MAGENTA,true}, /*89*/
{DLY_mineralizated_residue       , 7,3,TU__kgN_ha_        ,UC_kg_ha  ,"Mineralization residue (obsolete_in_V4.2)"  ,true,RTG_Residue       ,MAGENTA,true}, /*90*/
{DLY_mineralizated_residue_accum , 7,3,TU_accum__kgN_ha_  ,UC_kg_ha  ,"Mineralization residue (obsolete_in_V4.2)" ,true,RTG_Residue_accum ,MAGENTA ,true},
{DLY_mineralizated_manure        , 7,3,TU__kgN_ha_        ,UC_kg_ha  ,"Mineralization organic fertilizer (obsolete_in_V4.2)" ,true,RTG_Residue       , MAGENTA,true},
{DLY_mineralizated_manure_accum  , 7,3,TU_accum__kgN_ha_  ,UC_kg_ha  ,"Mineralization organic fertilizer (obsolete_in_V4.2)",true,RTG_Residue_accum , MAGENTA,true},

{DLY_mineralizated_OM            , 7,3,TU__kgN_ha_        ,UC_kg_ha  ,"Mineralization soil organic matter" ,true,RTG_Residue       , MAGENTA,true},
{DLY_mineralizated_OM_accum      , 7,3,TU_accum__kgN_ha_  ,UC_kg_ha  ,"Mineralization soil organic matter" ,true,RTG_Residue_accum , MAGENTA,true},

{DLY_automatic_N_in_uptake       , 7,3,TU__kgN_ha_        ,UC_kg_ha,TL_Automatic_nitrogen_allocated_to_crop_tissues,true,RTG_Crop          ,MAGENTA,true},
{DLY_automatic_N_in_uptake_accum , 7,3,TU_accum__kgN_ha_  ,UC_kg_ha,TL_Automatic_nitrogen_allocated_to_crop_tissues,true,RTG_Crop_accum    ,MAGENTA,true},
{DLY_organic_N_applied           , 7,3,TU__kgN_ha_        ,UC_kg_ha,TL_Organic_nitrogen_applied            ,true,RTG_Management    ,MAGENTA,true},
{DLY_organic_N_applied_accum     , 7,3,TU_accum__kgN_ha_  ,UC_kg_ha,TL_Organic_nitrogen_applied            ,true,RTG_Management_accum, MAGENTA,true},
{DLY_N_Fixation                  , 6,3,TU__kgN_ha_        ,UC_kg_ha,TL_N_fixation                          ,true,RTG_Crop          , MAGENTA,true},
{DLY_N_Fixation_accum            , 6,3,TU_accum__kgN_ha_  ,UC_kg_ha,TL_N_fixation                          ,true,RTG_Crop_accum    , MAGENTA,true}

//   { 7,3,TL_NO3_budget                  ,TU__kg_ha_,TL_NO3_budget                   ,true},
//   { 7,3,TL_NH4_budget                  ,TU__kg_ha_,TL_NH4_budget                   ,true},
//   { 7,3,TL_P_budget                    ,TU__kg_ha_,TL_P_budget                     ,true},
//   { 7,3,TL_K_budget                    ,TU__kg_ha_,TL_K_budget                     ,true},
//   { 7,3,TL_Salinity_budget             ,TU__kg_ha_,TL_Salinity_budget              ,true},
//   { 7,3,TL_Pesticide_budgets           ,TU__kg_ha_,TL_Pesticide_budget             ,true},
};
//______________________________________________________________________________
#define YLY_YEAR_POS  1

report_var_layout_with_graph YLY_report_var_opts[MAX_YLY_entries] =
{
  {0 /*YLY_ID*/,                 0,0,TL_BLANKLINE  ,0          ,TL_BLANKLINE,false,LAYOUT_NO_OPTIONS},
/* 1*/{YLY_year,                 5,0,TL_BLANKLINE  ,UT_year    ,"Year" /*T_date_Year */          ,false,LAYOUT_NO_OPTIONS},/* 1*/
/* 2*/{YLY_residue_ground_cover, 6,2,TU__percent_  ,UC_percent ,TL_Residue_ground_cover          ,true,LAYOUT_NO_OPTIONS}, /* 2*/
/* 3*/{YLY_soil_loss,            6,2,TU__tn_ha_    ,UC_tn_ha   ,TL_Soil_loss                     ,true,LAYOUT_NO_OPTIONS}, /* 3*/
/* 4*/{YLY_ET_pot,               7,2,TU__mm_       ,UC_mm      ,TL_Potential_evapotranspiration  ,true,LAYOUT_NO_OPTIONS}, /* 4*/
/* 5*/{YLY_ET_act,               7,2,TU__mm_       ,UC_mm      ,TL_Actual_evapotranspiration     ,true,LAYOUT_NO_OPTIONS}, /* 5*/
/* 6*/{YLY_transp_pot,           7,2,TU__mm_       ,UC_mm      ,TL_Potential_transpiration       ,true,LAYOUT_NO_OPTIONS}, /* 6*/
/* 7*/{YLY_transp_act,           7,2,TU__mm_       ,UC_mm      ,TL_Actual_transpiration          ,true,LAYOUT_NO_OPTIONS}, /* 7*/
/* 8*/{YLY_evap_soil_pot,        7,2,TU__mm_       ,UC_mm      ,TL_Potential_soil_evaporation    ,true,LAYOUT_NO_OPTIONS}, /* 8*/
/* 9*/{YLY_evap_soil_act,        7,2,TU__mm_       ,UC_mm      ,TL_Actual_soil_evaporation       ,true,LAYOUT_NO_OPTIONS}, /* 9*/
/*10*/{YLY_evap_residue_pot,     7,2,TU__mm_       ,UC_mm      ,TL_Potential_residue_evaporation ,true,LAYOUT_NO_OPTIONS}, /*10*/
/*11*/{YLY_evap_residue_act,     7,2,TU__mm_       ,UC_mm      ,TL_Actual_residue_evaporation    ,true,LAYOUT_NO_OPTIONS}, /*11*/
/*12*/{YLY_irrigation,           7,2,TU__mm_       ,UC_mm      ,TL_Irrigation                    ,true,LAYOUT_NO_OPTIONS}, /*12*/
/*13*/{YLY_precipitation,        7,2,TU__mm_       ,UC_mm      ,TL_Precipitation                 ,true,LAYOUT_NO_OPTIONS}, /*13*/
/*14*/{YLY_crop_water_intrcpt,   7,2,TU__mm_       ,UC_mm      ,TL_Crop_water_interception       ,true,LAYOUT_NO_OPTIONS}, /*14*/
/*15*/{YLY_residue_water_intrcpt,7,2,TU__mm_       ,UC_mm      ,TL_Residue_water_interception    ,true,LAYOUT_NO_OPTIONS}, /*15*/
/*16*/{xYLY_surface_water_runoff,7,2,TU__mm_       ,UC_mm      ,TL_Surface_water_runoff          ,true,LAYOUT_NO_OPTIONS}, /*16*/
/*17*/{YLY_ponded_water         ,7,2,TU__mm_       ,UC_mm      ,TL_Ponded_water                  ,true,LAYOUT_NO_OPTIONS}, /*17*/
/*18*/{YLY_water_enter_soil,     7,2,TU__mm_       ,UC_mm      ,TL_Water_entering_soil           ,true,LAYOUT_NO_OPTIONS}, /*18*/
/*19*/{YLY_soil_water_drainage,  7,2,TU__mm_       ,UC_mm      ,TL_Soil_water_drainage           ,true,LAYOUT_NO_OPTIONS}, /*19*/
/*20*/{YLY_soil_water_balance,   7,2,TU__mm_       ,UC_mm      ,TL_Soil_water_balance            ,true,LAYOUT_NO_OPTIONS},

/*21*/{YLY_nitrogen_applied_total,   7,3,TU__kgN_ha_,UC_kg_ha,TL_Inorganic_nitrogen_applied  ,true,LAYOUT_NO_OPTIONS},
/*22*/{YLY_nitrogen_leached_total,   7,3,TU__kgN_ha_,UC_kg_ha,TL_Nitrogen_leached            ,true,LAYOUT_NO_OPTIONS},
/*23*/{YLY_nitrogen_uptake_total,    7,3,TU__kgN_ha_,UC_kg_ha,TL_Total_nitrogen_uptake       ,true,LAYOUT_NO_OPTIONS},
/*24*/{YLY_added_auto_N_in_uptake,   7,3,TU__kgN_ha_,UC_kg_ha,TL_Automatic_nitrogen_allocated_to_crop_tissues, true,LAYOUT_NO_OPTIONS},

/*25*/{YLY_mineralized_from_residue ,7,3,TU__kgN_ha_,UC_kg_ha,"Mineralized_from residue (obsolete_in_V4.2)" ,true,LAYOUT_NO_OPTIONS},
/*26*/{YLY_mineralized_from_org_fert,7,3,TU__kgN_ha_,UC_kg_ha,"Mineralized_from organic_fertilizer (obsolete_in_V4.2)",true,LAYOUT_NO_OPTIONS},
/*27*/{YLY_mineralized_OM           ,7,3,TU__kgN_ha_,UC_kg_ha,TL_Mineralized_from_organic_matter,true,LAYOUT_NO_OPTIONS},
/*28*/{YLY_total_mineralization     ,7,3,TU__kgN_ha_,UC_kg_ha,TL_Mineralization /*160325 TL_Total_mineralization  */      ,true,LAYOUT_NO_OPTIONS},
/*29*/{YLY_organic_N_applied        ,7,3,TU__kgN_ha_,UC_kg_ha,TL_Organic_nitrogen_applied    ,true,LAYOUT_NO_OPTIONS},
/*30*/{YLY_organic_N_gaseous_loss   ,7,3,TU__kgN_ha_,UC_kg_ha,TL_NH3_with_manure_N_gaseous_loss,      true,LAYOUT_NO_OPTIONS},
/*31*/{YLY_inorganic_N_gaseous_loss ,7,3,TU__kgN_ha_,UC_kg_ha,TL_Inorganic_N_gaseous_loss    ,true,LAYOUT_NO_OPTIONS},
/*32*/{xYLY_N_fixation              ,6,3,TU__kgN_ha_,UC_kg_ha,TL_N_fixation                  ,true,LAYOUT_NO_OPTIONS},
/*33*/{CSVC_soil_C_all_profile      ,6,3,TU__kg_ha_ ,UC_kg_ha,TL_Carbon_profile              ,true,LAYOUT_NO_OPTIONS},
/*34*/{YLY_soil_carbon_30cm         ,6,3,TU__kg_ha_ ,UC_kg_ha,TL_Carbon_30cm                 ,true,LAYOUT_NO_OPTIONS},
/*35*/{YLY_biomass_grazed           ,6,3,TU__kg_ha_ ,UC_kg_ha,"Biomass grazed"               ,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_surface_biomass    ,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue (all) surface current"	,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_plant_surface      ,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue plant surface current"	,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_manure_surface     ,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue manure surface current"	,true,LAYOUT_NO_OPTIONS},

      {CSVC_residue_incorporated       ,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue (all) soil_profile current"	,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_plant_incorporated ,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue plant soil_profile current"	,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_manure_incorporated,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue manure soil_profile current",true,LAYOUT_NO_OPTIONS}
};
//______________________________________________________________________________
report_var_layout_with_graph GS_report_var_opts[GS_MAX_IDS] =
{     {0/*HRV_ID*/,                     0,0,TL_BLANKLINE ,0          ,TL_BLANKLINE            ,false,LAYOUT_NO_OPTIONS},
      {GS_crop_name,                  25,0,TL_BLANKLINE ,0          ,TL_Crop_name             ,false,LAYOUT_NO_OPTIONS},
      {GS_planting_date_YMD,          10,0,DF_YYYY_Mmm_DD ,UT_date    ,"Planting date",false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_inactive_end_date_YMD                    ,10,0,DF_YYYY_Mmm_DD ,UT_date    ,"Inactive_or dormancy end_date"    ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_base_chill_requirement_satisfied_date_YMD,10,0,DF_YYYY_Mmm_DD ,UT_date    ,"Chill requirement satisfied date" ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_bud_break_date_YMD                       ,10,0,DF_YYYY_Mmm_DD ,UT_date    ,"Bud break date"          ,false,LAYOUT_NO_OPTIONS},
      {GS_emergence_date_YMD,         10,0,DF_YYYY_Mmm_DD ,UT_date    ,TL_Emergence_date       ,false,LAYOUT_NO_OPTIONS},
      {GS_flowering_date_YMD,         10,0,DF_YYYY_Mmm_DD ,UT_date    ,TL_Flowering_date       ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_tuber_init_date_YMD,        10,0,DF_YYYY_Mmm_DD ,UT_date    ,"Tuber initiation date",false,LAYOUT_NO_OPTIONS},
      {GS_grain_filling_date_YMD,     10,0,DF_YYYY_Mmm_DD ,UT_date    ,"Grain_or Tuber filling"   ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_initial_fruit_growth_date_YMD            ,10,0,DF_YYYY_Mmm_DD ,UT_date    ,"Initial fruit growth"    ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_rapid_fruit_growth_date_YMD              ,10,0,DF_YYYY_Mmm_DD ,UT_date    ,"Rapid fruit growth"      ,false,LAYOUT_NO_OPTIONS},
      {GS_peak_LAI_date_YMD,          10,0,DF_YYYY_Mmm_DD ,UT_date    ,TL_Peak_LAI             ,false,LAYOUT_NO_OPTIONS},
      {GS_maturity_date_YMD,          10,0,DF_YYYY_Mmm_DD ,UT_date    ,TL_Maturity_date        ,false,LAYOUT_NO_OPTIONS},
      {GS_harvest_date_YMD,           10,0,DF_YYYY_Mmm_DD ,UT_date    ,TL_Harvest_date         ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_inactive_begin_date_YMD,10,0,DF_YYYY_Mmm_DD ,UT_date    ,"Inactive_or dormancy begin_date"           ,false,LAYOUT_NO_OPTIONS},

      {GS_planting_date_YD,            8,3,TL_YYYY_DDD  ,UT_date    ,"Planting date"                                       ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_inactive_end_date_YD               ,8,3,TL_YYYY_DDD  ,UT_date    ,"Inactive_or dormancy end_date"    ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_chill_requirement_satisfied_date_YD,8,3,TL_YYYY_DDD  ,UT_date    ,"Chill requirement satisfied date" ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_bud_break_date_YD                  ,8,3,TL_YYYY_DDD  ,UT_date    ,"Bud break date"                   ,false,LAYOUT_NO_OPTIONS},
      {GS_emergence_date_YD,           8,3,TL_YYYY_DDD  ,UT_date    ,TL_Emergence_date             ,false,LAYOUT_NO_OPTIONS},
      {GS_flowering_date_YD,           8,3,TL_YYYY_DDD  ,UT_date    ,TL_Flowering_date             ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_tuber_init_date_YD,       8,3,TL_YYYY_DDD  ,UT_date    ,"Tuber initiation"   ,false,LAYOUT_NO_OPTIONS},
      {GS_grain_filling_date_YD,       8,3,TL_YYYY_DDD  ,UT_date    ,"Grain_or Tuber filling"      ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_initial_fruit_growth_date_YD       ,8,3,TL_YYYY_DDD  ,UT_date    ,"Initial fruit growth" ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_rapid_fruit_growth_date_YD         ,8,3,TL_YYYY_DDD  ,UT_date    ,"Rapid fruit growth"   ,false,LAYOUT_NO_OPTIONS},
      {GS_peak_LAI_date_YD,            8,3,TL_YYYY_DDD  ,UT_date    ,TL_Peak_LAI               ,false,LAYOUT_NO_OPTIONS},
      {GS_maturity_date_YD,            8,3,TL_YYYY_DDD  ,UT_date    ,TL_Maturity_date          ,false,LAYOUT_NO_OPTIONS},
      {GS_harvest_date_YD,             8,3,TL_YYYY_DDD  ,UT_date    ,TL_Harvest_date           ,false,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_inactive_begin_date_YD             ,8,3,TL_YYYY_DDD  ,UT_date    ,"Inactive_or dormancy begin_date"           ,false,LAYOUT_NO_OPTIONS},

      {GS_peak_LAI,                    6,3,TU__m2_m2_   ,UC_m2_m2   ,TL_Peak_LAI                ,true,LAYOUT_NO_OPTIONS},
      {GS_yield,                       8,2,TU__kg_ha_   ,UC_kg_ha,TL_Yield                   ,true,LAYOUT_NO_OPTIONS},
	      {GS_used_biomass,                8,2,TU__kg_ha_   ,UC_kg_ha,"Biomass beneficial_use (secondary_yield)",true,LAYOUT_NO_OPTIONS},
	      {GS_grazed_biomass,              8,2,TU__kg_ha_   ,UC_kg_ha,"Biomass consumed_by animals",true,LAYOUT_NO_OPTIONS},
	      {GS_residue_biomass,             8,2,TU__kg_ha_   ,UC_kg_ha,"Biomass remained as residue",true,LAYOUT_NO_OPTIONS},
	      {GS_disposed_biomass,            8,2,TU__kg_ha_   ,UC_kg_ha,"Biomass removed_and disposed",true,LAYOUT_NO_OPTIONS},
      {CSVC_crop_biomass_produced_above_ground_period_sum,                 8,1,TU__kg_ha_   ,UC_kg_ha,"Total (above ground) biomass production" ,true,LAYOUT_NO_OPTIONS}, // 070207 was GS_dry_biomass

      {CSVC_crop_base_fruit_biomass       ,8,2,TU__kg_ha_   ,UC_kg_ha,"Fruit biomass"           ,true,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_fruit_canopy_biomass,8,2,TU__kg_ha_   ,UC_kg_ha,"Non-fruit biomass"       ,true,LAYOUT_NO_OPTIONS},

      {GS_daytime_VPD_avg,             8,2,"avg (kPa)"  ,UC_kPa     ,"Daytime vapor pressure deficit",true,LAYOUT_NO_OPTIONS},
      {GS_intercepted_PAR_accum      , 8,2,"accum (MJ/m²)",UC_MJ_m2 ,"Intercepted solar_radiation (total_or_PAR_depending_on_crop_option)",true,LAYOUT_NO_OPTIONS},
//080429              This may be either PAR or total radiation depending on the model used

      {GS_root_depth,                  7,2,TU__m_       ,UC_m       ,TL_Root_depth                 ,true,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_root_biomass_current,                7,1,TU__kg_ha_   ,UC_kg_ha   ,TL_Root_biomass               ,true,LAYOUT_NO_OPTIONS}, // 070207 was GS_root_biomass
#ifdef OBS
050116 added more residue outputs
/*20*/{GS_surface_residue_biomass,     7,2,TU__kg_ha_   ,UC_kg_ha   ,TL_Surface_residue_biomass ,true,LAYOUT_NO_OPTIONS},
/*21*/{GS_incorporated_plant_residue,  7,2,TU__kg_ha_   ,UC_kg_ha   ,TL_Incorporated_plant_residue    ,true,LAYOUT_NO_OPTIONS},
/*22*/{GS_incorporated_manure,         7,2,TU__kg_ha_   ,UC_kg_ha   ,TL_Incorporated_manure    ,true,LAYOUT_NO_OPTIONS},
#endif
      {CSVC_residue_surface_biomass   ,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue (all) surface current"       ,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_plant_surface     ,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue plant surface current"       ,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_manure_surface    ,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue manure surface current"      ,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_incorporated      ,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue (all) soil_profile current"	,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_plant_incorporated,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue plant soil_profile current"	,true,LAYOUT_NO_OPTIONS},
      {CSVC_residue_manure_incorporated,7,3,TU__kg_ha_ ,UC_kg_ha,"Residue manure soil_profile current",true,LAYOUT_NO_OPTIONS},
      {GS_erosion_index    // 091205 WARNING this is supposed to be the 'Cover (C) factor'
                           // I need to create a new variable code for this
                                       ,               7,3,TU__kg_ha_   ,UC_kg_ha,"RUSLE cover factor",true,LAYOUT_NO_OPTIONS},
      {GS_soil_loss,                   7,2,TU__tn_ha_   ,UC_tn_ha   ,TL_Soil_loss                  ,true,LAYOUT_NO_OPTIONS},
      {GS_ET_pot,                      7,2,TU__mm_      ,UC_mm      ,TL_Potential_evapotranspiration,true,LAYOUT_NO_OPTIONS},
/*26*/{GS_ET_act,                      7,2,TU__mm_      ,UC_mm      ,TL_Actual_evapotranspiration  ,true,LAYOUT_NO_OPTIONS},
/*27*/{GS_transp_pot,                  7,2,TU__mm_      ,UC_mm      ,TL_Potential_transpiration    ,true,LAYOUT_NO_OPTIONS},
/*28*/{GS_transp_act,                  7,2,TU__mm_      ,UC_mm      ,TL_Actual_transpiration       ,true,LAYOUT_NO_OPTIONS},
/*29*/{GS_evap_soil_pot,               7,2,TU__mm_      ,UC_mm      ,TL_Potential_soil_evaporation ,true,LAYOUT_NO_OPTIONS},
/*30*/{GS_evap_soil_act,               7,2,TU__mm_      ,UC_mm      ,TL_Actual_soil_evaporation    ,true,LAYOUT_NO_OPTIONS},
/*31*/{GS_evap_residue_pot,            7,2,TU__mm_      ,UC_mm      ,TL_Potential_residue_evaporation,true,LAYOUT_NO_OPTIONS},
/*32*/{GS_evap_residue_act,            7,2,TU__mm_      ,UC_mm      ,TL_Actual_residue_evaporation ,true,LAYOUT_NO_OPTIONS},
/*33*/{GS_irrig,                       7,2,TU__mm_      ,UC_mm      ,TL_Irrigation                 ,true,LAYOUT_NO_OPTIONS},
/*34*/{GS_precip,                      7,2,TU__mm_      ,UC_mm      ,TL_Precipitation              ,true,LAYOUT_NO_OPTIONS},
/*35*/{GS_crop_water_intrcpt,          7,2,TU__mm_      ,UC_mm      ,TL_Crop_water_interception    ,true,LAYOUT_NO_OPTIONS},
/*36*/{GS_residue_water_intrcpt,       7,2,TU__mm_      ,UC_mm      ,TL_Residue_water_interception ,true,LAYOUT_NO_OPTIONS},
/*37*/{GS_surface_water_runoff,        7,2,TU__mm_      ,UC_mm      ,TL_Surface_water_runoff       ,true,LAYOUT_NO_OPTIONS},
/*38*/{GS_ponded_water          ,      7,2,TU__mm_      ,UC_mm      ,TL_Ponded_water               ,true,LAYOUT_NO_OPTIONS},
/*39*/{GS_water_enter_soil,            7,2,TU__mm_      ,UC_mm      ,TL_Water_entering_soil        ,true,LAYOUT_NO_OPTIONS},
/*40*/{GS_soil_water_drainage,         7,2,TU__mm_      ,UC_mm      ,TL_Soil_water_drainage        ,true,LAYOUT_NO_OPTIONS},
/*41*/{GS_avg_water_stress_index,      7,3,TL_index     ,UC_index, TL_Average_water_stress         ,true,LAYOUT_NO_OPTIONS},
/*42*/{GS_avg_temperature_stress_index,7,3,TL_index     ,UC_index, "Avg. temperature stress early_growth",true,LAYOUT_NO_OPTIONS},


      {CSVC_crop_base_flower_temperature_stress_index_period_avg  ,7,3,TL_index     ,UC_index, "Temperature stress flowering" ,true,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_tuber_init_temp_stress_index,7,3,TL_index     ,UC_index, "Tuber_init (avg.)temperature stress"          ,true,LAYOUT_NO_OPTIONS},
      {CSVC_crop_base_tuber_fill_temp_stress_index,7,3,TL_index     ,UC_index, "Tuber_filling (avg.)temperature stress"       ,true,LAYOUT_NO_OPTIONS},

/*43*/{CSVC_crop_N_stress_index_period_avg,7,3,TL_index     ,UC_index, TL_Average_nitrogen_stress         ,true,LAYOUT_NO_OPTIONS},  // 070209 GS_avg_nitrogen_stress_index
/*44*/{GS_nitrogen_leached_total          ,7,3,TU__kgN_ha_  ,UC_kg_ha,TL_Nitrogen_leached                 ,true,LAYOUT_NO_OPTIONS},
/*45*/{CSVC_crop_N_uptake_period_sum      ,7,3,TU__kgN_ha_  ,UC_kg_ha,"Nitrogen uptake"               ,true,LAYOUT_NO_OPTIONS},
/*46*/{GS_nitrogen_applied_total          ,7,3,TU__kgN_ha_  ,UC_kg_ha,TL_Inorganic_nitrogen_applied   ,true,LAYOUT_NO_OPTIONS},
/*47*/{CSVC_crop_N_mass_canopy_current,7,3,TU__kgN_ha_  ,UC_kg_ha,"N_mass canopy current"                  ,true,LAYOUT_NO_OPTIONS},
/*47*/{CSVC_crop_N_mass_canopy_production_accum_to_date_time,7,3,TU__kgN_ha_  ,UC_kg_ha,"N_mass canopy production",true,LAYOUT_NO_OPTIONS},
/*48*/{CSVC_crop_N_automatic_uptake_period_sum        ,7,3,TU__kgN_ha_  ,UC_kg_ha,TL_Automatic_nitrogen_in_uptake ,true,LAYOUT_NO_OPTIONS},
/*49*/{CSVC_soil_N_available_period_sum               ,7,3,TU__kgN_ha_  ,UC_kg_ha,TL_Nitrogen_available           ,true,LAYOUT_NO_OPTIONS},
   // 960806P
/*50*/{CSVC_residue_mineralized_period_sum            ,7,3,TU__kgN_ha_  ,UC_kg_ha,"Mineralized_from residue (obsolete_in_V4.2)",true,LAYOUT_NO_OPTIONS},
/*41*/{CSVC_residue_manure_mineralized_period_sum     ,7,3,TU__kgN_ha_  ,UC_kg_ha,"Mineralized_from organic_fertilizer (obsolete_in_V4.2)",true,LAYOUT_NO_OPTIONS},
/*52*/{CSVC_organic_matter_mineralized_period_sum     ,7,3,TU__kgN_ha_  ,UC_kg_ha,TL_Mineralized_from_organic_matter  ,true,LAYOUT_NO_OPTIONS},
/*53*/{CSVC_soil_N_mineralization_period_sum          ,7,3,TU__kgN_ha_  ,UC_kg_ha,TL_Mineralization /*160326 TL_Total_mineralization          */   ,true,LAYOUT_NO_OPTIONS},
/*53*/{CSVC_soil_N_immobilization_period_sum          ,7,3,TU__kgN_ha_  ,UC_kg_ha,"Immobilization",true,LAYOUT_NO_OPTIONS}, //160326
/*54*/{CSVC_mgmt_N_organic_applied_period_sum         ,7,3,TU__kgN_ha_  ,UC_kg_ha,TL_Organic_nitrogen_applied         ,true,LAYOUT_NO_OPTIONS},
/*55*/{CSVC_mgmt_N_organic_gaseous_loss_period_sum    ,7,3,TU__kgN_ha_  ,UC_kg_ha,TL_NH3_with_manure_N_gaseous_loss   ,true,LAYOUT_NO_OPTIONS}, //990316
/*56*/{CSVC_mgmt_N_inorganic_gaseous_loss_period_sum  ,7,3,TU__kgN_ha_  ,UC_kg_ha,TL_Inorganic_N_gaseous_loss         ,true,LAYOUT_NO_OPTIONS},
/*57*/{CSVC_crop_N_fixation_period_sum                ,6,3,TU__kgN_ha_  ,UC_kg_ha,TL_N_fixation                       ,true,LAYOUT_NO_OPTIONS}
};
//______________________________________________________________________________
std::string &column_header(std::string CH, int16 num, int16 N, std::string &CHn)
{  //CH is modified locally because underscores are temporarily converted to spaced within this function only.
   std::string backwards("");
   int16 rev_word_order = N;
   int i;

//   There may be up to N substrings in the column header
//   the substrings are seperated by spaces.
//   column header N will be the right most substring.
//   column headers 1 and 2 may be empty.
//   Any _ is translated to space

   for (i = CH.length()-1; i>= 0 ;i--)
   {
      if (CH[i] == ' ')
         rev_word_order --;
      else
         if (rev_word_order == num)
         {
            if (CH[i] == '_') CH[i] = ' ';
            char ch_app[2];
            ch_app[0] = CH[i];
            ch_app[1] = 0;                                                       //001116
            backwards.append(ch_app);                                            //001116
         };
   };
   int j = backwards.length();
   CHn.assign("");
   for (i = 1; i<= j ; i++)
   {
      char ch_app[2];
      ch_app[0] = backwards[j-i];
      ch_app[1] = 0;
      CHn.append(ch_app);                                                        //001116
   }
   return CHn;
}
//______________________________________________________________________________
//000926 lookup_description is temporary until I make sure that CS_variables are all generating the correct description
//       This description is currently only used where we generate arc_CS 15 character abbreviations.
//       This will be replaced with abbreviations.
const char *lookup_description(report_var_layout_with_graph variable_set[], int set_count, CS_UED_variable_code var_code)
{  for (int i = 0 ; i < set_count; i++)
      if (variable_set[i].ID == var_code)
         return (variable_set[i].desc);
   return "";
}
//_2000-09-26___________________________________________________________________
uint16 lookup_variable_index(report_var_layout_with_graph variable_set[], int set_count, CS_UED_variable_code var_code)
{  for (uint16 i = 0 ; i < set_count; i++)
      if (variable_set[i].ID == var_code)
         return i;
   return 0;
}
//_2000-09-26___________________________________________________________________
report_var_layout_with_graph *lookup_report_var_layout(report_var_layout_with_graph variable_set[], int set_count, CS_UED_variable_code var_code)
{  for (uint16 i = 0 ; i < set_count; i++)
      if (variable_set[i].ID == var_code)
         return &variable_set[i];
   return 0;
}
//_2000-09-26___________________________________________________________________

