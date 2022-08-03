#ifndef residue_constH
#define residue_constH

//#ifndef labeled_enumH
//#include <corn/labeled_enum.h>
//#endif
//#ifndef OM_typesH
//#include <cropsyst/cpp/organic_matter/yOM_types.h>
//#endif
#include <corn/primitive.h>


#define  MAX_RESIDUE_HOLD_m3_kg  0.003  /* m3/kg */
#define  MAX_RESIDUE_HOLD_m3_kg  0.003  /* m3/kg */
#define  manure_water_hold    0.004   // WARNING check this }
#define  manure_area_per_mass 5.0

//061101 renamed default_straw_residue_fraction_carbon #define  straw_fraction_carbon_residue        0.46
#define  default_straw_residue_fraction_carbon        0.46
#define  default_manure_fraction_carbon               0.5

#define  straw_carbon_nitrogen_ratio_V4_4          50.0
#define  straw_carbon_nitrogen_ratio_V4_9          50.0
// WARNING must rename this to   default_straw_carbon_nitrogen_ratio

#define DEFAULT_STANDING_STUBBLE_CONTACT_FRACTION  0.3
#define DEFAULT_SURFACE_ORGANIC_RESIDUE_CONTACT_FRACTION  0.7
#define DEFAULT_SURFACE_MANURE_CONTACT_FRACTION  1.0

/*990217P*/ enum Residue_horizons
/*_______*/    {NULL_HORIZON
/*_______*/    , SURFACE_HORIZON
/*_______*/    , SHALLOW_HORIZON
/*_______*/    , DEEP_HORIZON/*,DEEPER_HORIZON*/
/*970418P*/    , UNREACHABLE_HORIZON
/*_______*/    ,ALL_HORIZON
/*_______*/    ,ALL_SUBSURFACE_HORIZON};

/*060731_*/ enum RUSLE2_Residue_type
/*_______*/    {UNKNOWN_RESIDUE_TYPE
/*_______*/    , FRAGILE_RESIDUE_TYPE
/*_______*/    , MODERATE_RESIDUE_TYPE
/*_______*/    , NONFRAGILE_RESIDUE_TYPE
/*_______*/    , TOUGH_RESIDUE_TYPE
/*_______*/    , STONE_RESIDUE_TYPE
/*_______*/    ,RUSLE2_RESIDUE_TYPE_COUNT};
/*060731_*/ extern const char *RUSLE2_residue_type_label_table[];
/*060731_*/ DECLARE_LABELED_ENUM(RUSLE2_Residue_type_labeled,RUSLE2_Residue_type,RUSLE2_residue_type_label_table);
// RLN I a presuming manure is fragile (need to verify)
#define     RUSLE2_MANURE_RESIDUE_TYPE FRAGILE_RESIDUE_TYPE

/*_080908*/ enum  Organic_matter_source
/*_______*/ {  plant_residue  // Replace this with plant_residue
/*_______*/      //  { The rest are manure organic matter }
/*_______*/    ,poultry_layers_manure
/*_______*/    ,poultry_fresh_broilers_turkeys_manure
/*_______*/    ,poultry_aged_broilers_turkeys_manure
/*_______*/    ,swine_manure
/*_______*/    ,daily_fresh_manure
/*_______*/    ,daily_tank_storage_manure
/*_______*/    ,dairy_anaerobic_lagoon_storage_manure
/*_______*/    ,beef_fresh_manure
/*_______*/    ,beef_aged_2_5_manure
/*_______*/    ,beef_aged_1_5_manure
/*_______*/    ,beef_aged_1_0_manure
/*_______*/     // Added 080908
/*_______*/    ,municiple_waste_compost
/*_______*/    ,sewage_sludges
/*_______*/    ,corn_stover
/*_______*/    ,sorghum_stover
/*_______*/    ,wheat_straw
/*_______*/    ,oat_straw
/*_______*/    ,soybean_residue
/*_______*/    ,organic_matter_source_COUNT
/*_______*/ };

/*060731_*/ extern const Label_description organic_matter_source_label_table[];
/*060731_*/ DECLARE_DESCRIPTIVE_LABELED_ENUM(organic_matter_source_label_table_labeled,Organic_matter_source,organic_matter_source_label_table);



struct Organic_matter_composition_decomposition
{
//   Residue_source source
   float32 nitrogen_percent_DryWt;     // Dry wt basis
   float32 carbon_percent_DryWt;       // Dry wt basis
//,  float32 C_N_ratio       can be calculated
   bool cycling_pools;
  float32 fraction_of_biomass             [5/*090821 OM_CYCLING_COUNT*/];  // fraction that is each cycling (values in this array must add to 1.0)
  int16   days_to_50_percent_decomposition[5/*090821 OM_CYCLING_COUNT*/];
};
extern Organic_matter_composition_decomposition default_organic_matter_composition_decomposition[];


/*_______*/ extern short int manure_decomp_time_coef[12];
/*_______*/ extern float32 Xfract_manure_to_deep[5][2];
/*090224_*/ extern float32 manure_incorporation_fraction[5];
/*_______*/ extern float32 N_in_manure_percent_dry_wt[12];

#endif

