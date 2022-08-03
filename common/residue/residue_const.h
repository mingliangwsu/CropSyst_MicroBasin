#ifndef residue_constH
#define residue_constH

#ifndef labeled_enumH
#include "corn/labeled_enum.h"
#endif
#include "corn/primitive.h"
#define  MAX_RESIDUE_HOLD_m3_kg  0.003  /* m3/kg */
#define  MAX_RESIDUE_HOLD_m3_kg  0.003  /* m3/kg */
#define  manure_water_hold    0.003   //120523 0.004   // WARNING check this }
#define  manure_area_per_mass 5.0

#define  default_straw_residue_fraction_carbon        0.46
#define  default_manure_fraction_carbon               0.5

#define  straw_carbon_nitrogen_ratio_V4_4          50.0
#define  straw_carbon_nitrogen_ratio_V4_9          50.0
// WARNING must rename this to   default_straw_carbon_nitrogen_ratio
#define DEFAULT_STANDING_STUBBLE_CONTACT_FRACTION           0.3
#define DEFAULT_SURFACE_ORGANIC_RESIDUE_CONTACT_FRACTION    0.7
#define DEFAULT_SURFACE_MANURE_CONTACT_FRACTION             1.0
//______________________________________________________________________________
enum Residue_horizons
{NULL_HORIZON
, SURFACE_HORIZON
, SHALLOW_HORIZON
, DEEP_HORIZON/*,DEEPER_HORIZON*/
, UNREACHABLE_HORIZON                                             //970418
,ALL_HORIZON
,ALL_SUBSURFACE_HORIZON};
//_1999-02-17___________________________________________________________________
enum RUSLE2_Residue_type
{UNKNOWN_RESIDUE_TYPE
, FRAGILE_RESIDUE_TYPE
, MODERATE_RESIDUE_TYPE
, NONFRAGILE_RESIDUE_TYPE
, TOUGH_RESIDUE_TYPE
, STONE_RESIDUE_TYPE
,RUSLE2_RESIDUE_TYPE_COUNT};
extern const char *RUSLE2_residue_type_label_table[];
DECLARE_LABELED_ENUM(RUSLE2_Residue_type_labeled,RUSLE2_Residue_type,RUSLE2_residue_type_label_table);
// RLN I a presuming manure is fragile (need to verify)
#define     RUSLE2_MANURE_RESIDUE_TYPE FRAGILE_RESIDUE_TYPE
//_2006-07-31___________________________________________________________________
enum  Organic_matter_source
{plant_residue  // Replace this with plant_residue
 //  The rest are manure organic matter 
,poultry_layers_manure
,poultry_fresh_broilers_turkeys_manure
,poultry_aged_broilers_turkeys_manure
,swine_manure
,dairy_fresh_manure
,dairy_tank_storage_manure
,dairy_anaerobic_lagoon_storage_manure
,beef_fresh_manure
,beef_aged_2_5_manure
,beef_aged_1_5_manure
,beef_aged_1_0_manure
 // Added 080908
,municiple_waste_compost
,sewage_sludges
,corn_stover
,sorghum_stover
,wheat_straw
,oat_straw
,soybean_residue
,default_source                                                                  //100216
,organic_matter_source_COUNT
};
extern const Label_description organic_matter_source_label_table[];              //060731
DECLARE_DESCRIPTIVE_LABELED_ENUM(Organic_matter_source_labeled,Organic_matter_source,organic_matter_source_label_table); //060731
DECLARE_LABELED_ENUM_COWL(Organic_matter_source_cowl,Organic_matter_source,organic_matter_source_label_table);
//_2008-09-08___________________________________________________________________
struct Organic_matter_composition_decomposition
{//   Residue_source source
   float32 nitrogen_percent_DryWt;     // Dry wt basis
   float32 carbon_percent_DryWt;       // Dry wt basis
   bool cycling_pools;
   float32 fraction_of_biomass             [5];  // fraction that is each cycling (values in this array must add to 1.0)
   float32 days_to_50_percent_decomposition[5];
public:
};
//______________________________________________________________________________
extern Organic_matter_composition_decomposition default_organic_matter_composition_decomposition[];
extern nat16 manure_decomp_time_coef     [12];
extern float32 N_in_manure_percent_dry_wt    [12];
extern float32 fract_manure_to_deep          [5][2];
extern float32 manure_incorporation_fraction [5];                                 //090224
//______________________________________________________________________________
#endif

