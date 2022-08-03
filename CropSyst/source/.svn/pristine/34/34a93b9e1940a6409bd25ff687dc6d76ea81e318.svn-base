#ifndef crop_typesH
#define crop_typesH

#include "options.h"
// This file and the enumerations where not used in version 3.
//______________________________________________________________________________
/*
NYI Cropping system classifications
agronomic (field) crop (grains forages oilseeds fiber crops_
horicultural crop

Stem type
 herbaceous  A herbaceous plant (or in botanical use, a herb) is a plant that has leaves and stems that die down at the end of the growing season to the soil level. A herbaceous plant may be annual, biennial or perennial.
 woody plant is any vascular plant that has a perennial stem that is above ground and covered by a layer of thickened bark
*/
//______________________________________________________________________________
enum Crop_model
{  CROPSYST_CROP_MODEL
,  CROPSYST_ORCHARD_MODEL   // Actually Fruit tree and vine  rename this to CROPSYST_ORCHARD_FRUIT_MODEL
,  CROPGRO_MODEL
,  NWHEATS_MODEL                                                                 //140716
,  CROP_MODEL_UNKNOWN
,  CROP_MODEL_COUNT
};
extern const char *crop_model_label_table[];
//_020408_______________________________________________________________________
enum Harvested_part
{
 grain_part // Grain include Seed and Achene                                     //110218
,root_part
,tuber_part
,bulb_part
,leaf_part
,fruit_part //FRUIT                                                              //020405
,HARVEST_CANOPY               // essentially all above (95%) ground biomass      //031015
,HARVEST_COMPLETE              // All biomass including roots                    //031015
,HARVEST_PART_COUNT
,UNKNOWN_PART
};
extern const char *harvested_part_label_table[];
//_2002-04-05___________________________________________________________________
enum Life_cycle
{ UNKNOWN_LIFE_CYCLE    // indeterminate_life_cycle
, annual_life_cycle
, biennial_life_cycle
, perennial_life_cycle                                                           //080722
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
// Included for compatibility
, PERENNIAL_HERBACEOUS
, PERENNIAL_WOODY
#endif
};
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
// Included for compatibility
#define ANNUAL    annual_life_cycle
#define BIENNIAL  biennial_life_cycle
#define PERENNIAL perennial_life_cycle
#endif
extern const char *life_cycle_label_table[];
//_2002-07-16___________________________________________________________________
enum Stem_type
{ herbaceous_stem
, woody_stem
};
extern const char *stem_type_label_table[];
//_2008-07-21___________________________________________________________________
enum Metatopy    // the placement of floral organs out of their normally expected position
{  subtendescent
,  concaulescent
,  recaulescent
};
//_2013-04-24___________________________________________________________________
enum Abscission
{  abscission_not_applicable  // Leaves are retained throughout the growth of the plant I.e. annuals and monocots
,  deciduous        // All leaves are shed at the end of the season.
,  semi_deciduous   // Similar to marcescent, but leaves may completely shed and not be replaced for a short time.
                    //     all leaves will be shed at the start of the season.
                    //     There will be no effette leaves coexisting with vital leaves.  (was lingers)
,  marcescent       // Leaves may scenese but are not shed until new growth replaces (knock the leaves off?)
                    //     usually as the start of the new season, leaves may persist into successive seasons.
                    //     There may be effette leaves coexisting with vital leaves.
                    //     May be knocked off by wind.
,  semi_evergreen   // Leaves are shed as new replacement growth occurs (continously, not seasonally)
,  evergreen        // Persistent year round but individual leaves may senesce
                    //     these are generally shed immediately or may be attached to the plant for some specified period.
                    //     (individual leaves are not replaced)
};
extern const char *abscission_label_table[];
//_2008-11-13___________________________________________________________________
enum Photosynthetic_pathway {C3,C4,CAM,C2,PHOTOSYNTHETIC_PATHWAY_COUNT};                       // was C_Species  090715_110504
extern const char *photosynthetic_pathway_label_table[];
// Warning, if you change the photosynthentic pathway  enumeration, dont forget to change the arrays in Crop_nitrogen::find_concentration_range() //061212
// Photosynthetic pathway for carbon fixation
// CAM (Crassulacean Acid Metabolism is not currently used by CropSyst
// However, some agricultural plants such as Pinapple, Aloe, Yucca use CAM
// CAM is used by plants in extreme environments or primitive plants such as cactus //090309
// Unlike any other type of plant, they can close their stomates during the day to conserve water.
// They also use PEPCase to fix carbon dioxide at night, instead of using RuBP.
// http://wiki.answers.com/Q/How_do_C4_plants_and_CAM_plants_differ#ixzz1tqkzLD3P
//______________________________________________________________________________
enum Emergence_model
{  EMERGENCE_THERMAL_TIME
,  EMERGENCE_HYDROTHERMAL_TIME
//NYI /*_______*/ ,  EMERGENCE_TRANSPLANT
//NYI /*_______*/ ,  EMERGENCE_EXISTING_STAND
};
extern const char *emergence_model_label_table[];
//_2004-12-01___________________________________________________________________
enum Crop_nitrogen_model
{  CROP_NITROGEN_DISABLED
,  CROP_NITROGEN_ORIGINAL
};
//_2005-07-23___________________________________________________________________
enum Canopy_growth_model
{ leaf_area_index_based
, canopy_cover_based_2017                                                        //171219
, leaf_area_index_based_duration
//180601 obsolete ,  canopy_cover_based_2013                                     //171219
, canopy_architecture                                                            //180601
};
extern const char *canopy_growth_label_table[];
//_2008-07-25___________________________________________________________________
enum Nitrogen_leaf_stress_mode
{  no_leaf_stress
,  minimum_to_critical_conc
,  straddle_critical_conc
};
extern const char *nitrogen_leaf_stress_model_label_table[];
//_2007-02-24___________________________________________________________________
enum Season_dormancy_mode   // rename to Continuation
{  single_season
,  multiple_season
,  dormancy_season
};
extern const char *season_dormancy_mode_label_table[];
//_2008-03-31___________________________________________________________________
enum Harvest_condition_mode
{  management_scheduled_harvest
,  consider_fixed_date_harvest
,  consider_min_temperature_harvest
,  consider_avg_temperature_harvest
};
extern const char *harvest_condition_mode_label_table[];
//_2008-12-04___________________________________________________________________
enum TUE_Equation
{   // TUE is Transpiration use efficiency
   TUE_Tanner_Sinclair
,  TUE_water_productivity   //  as in FAO AquaCrop
,  TUE_curve
};
extern const char *TUE_equation_label_table[];
//_2008-05-05___________________________________________________________________
enum RUE_Basis
{ // RUE is radiation use efficiency
 total_radiation
,photosynthetically_active_radiation
,unspecified_RUE_basis
};
extern const char *RUE_basis_label_table[];
//_2008-07-31___________________________________________________________________
enum  Thermal_time_resolution { HOURLY ,  DAILY };
extern const char *Thermal_time_resolution_label_table_deprecated[];
//_2002-11-24___________________________________________________________________
enum  Thermal_response { nonlinear ,  linear};
extern const char *Thermal_response_label_table[];
//_2015-11-09___________________________________________________________________
enum Photoperiodism // Photoperiod_consideration
{  no_photoperiod
,  short_day_photoperiod
,  long_day_photoperiod
,  intermediate_day_photoperiod
,  day_neutral_photoperiod
};
// REF:http://www.cliffsnotes.com/sciences/biology/plant-biology/growth-of-plants/photoperiodism
extern const char *photoperiodism_label_table[]; // photoperiod_consideration_label_table[];
//_2010-05-12___________________________________________________________________
//160531 This is actually obsolete in V5 but V5 is at the momemnt reading V4 files
//160531 #if (CROPSYST_VERSION==4)
// Replaced by Absission
enum Senesced_biomass_fate_obsolete
{  senesced_biomass_endure    // Senesced biomass is retained permanently (this was the original model, only worked for annuals, not recommended for perennials)
                              // to be replaced with no_abscission, evergreeen
,  senesced_biomass_shed      // Senesced biomass is retained until dormancy (or harvest) then becomes stubble residue. After dormancy scenesced biomass (from previous season) is sloughed_immediately. //060825_
                              // to be replaced by deciduous
,  senesced_biomass_linger    // Remains lingers with the plant (still available for clipping grazing) contributes to canopy LAI but eventually sloughs off becoming stubble residue (at some rate?)
                              // to be replaced by semi-deciduous
,  senesced_biomass_decompose_obsolete  // decomposes similar to stubble   (I.e. for perennial grass, grazing fodder) If carbon model decomposition submodel not enabled, this behaves like senesced_biomass_slough.
};
extern const char *senesced_biomass_fate_label_table[];
//_2006-08-17___________________________________________________________________
enum  Potential_N_uptake_model
{ ROOT_WATER_AND_N_AVAILABILITY_FACTOR   // <- This (original) model is deprecated in V 4.6 and will be obsolete in V5
, ROOT_FACTOR_ONLY };
extern const char *potential_N_uptake_model_label_table[];
//_2006-12-01___________________________________________________________________
enum Transpiration_model
{ LEAF_AND_ROOT_TRANSPIRATION_MODEL,ORIGINAL_TRANSPIRATION_MODEL};
extern const char *transpiration_model_label_table[];
//_2005-03-31___________________________________________________________________
enum Nitrogen_fixation
{ none
, leguminous
, non_leguminous
};
//_2017-01-17___________________________________________________________________
#endif

