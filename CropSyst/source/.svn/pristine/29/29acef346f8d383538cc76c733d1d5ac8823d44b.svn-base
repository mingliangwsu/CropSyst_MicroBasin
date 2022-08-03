#ifndef OM_typesH
#define OM_typesH
#ifndef labeled_enumH
#  include "corn/labeled_enum.h"
#endif
//______________________________________________________________________________
enum Organic_matter_partitioning_mode {OMPM_user_specified,OMPM_previously_crop_land,OMPM_cultivated_grass_land};
extern const char *organic_matter_partitioning_mode_label_table[];
DECLARE_LABELED_ENUM(Organic_matter_partitioning_mode_labeled,Organic_matter_partitioning_mode ,organic_matter_partitioning_mode_label_table)

#define SOM_C_INITIAL_plus                   0
#define SOM_C_TRANSFERED_FROM_RESIDUE_plus   1
#define SOM_C_LOSS_AS_CO2_minus              2
#define SOM_C_FINAL_minus                    3
#define SOM_C_BALANCE_COUNT                  4

#define RESIDUE_C_INITIAL_plus               0
#define RESIDUE_C_NEW_plus                   1
#define RESIDUE_C_DECOMPOSED_minus           2
#define RESIDUE_C_FINAL_minus                3
#define RESIDUE_C_BALANCE_COUNT              4

// N balance NYI
// #define RESIDUE_N_INITIAL_plus            0
// #define RESIDUE_N_NEW_plus							1
// #define RESIDUE_N_DECOMPOSED_minus           2
// #define RESIDUE_N_FINAL_minus                3
// #define RESIDUE_N_BALANCE_COUNT					4
// extern Balancer  residue_N_balancer;

//______________________________________________________________________________
enum Organic_matter_type
   {STRAW_RESIDUE
   ,MANURE_RESIDUE
   ,MICROBIAL_BM_OR_SINGLE_SOM
   ,LABILE_ACTIVE_SOM
   ,METASTABLE_ACTIVE_SOM
   ,PASSIVE_SOM
   ,ORGANIC_MATTER_TYPE_COUNT };
#define        FIRST_ORGANIC_MATTER_TYPE (Organic_matter_type)0
#  define   SOM_INDEX_FIRST   ((nat8)MICROBIAL_BM_OR_SINGLE_SOM)
#  define   SINGLE_SOM        MICROBIAL_BM_OR_SINGLE_SOM
#  define   MICROBIAL_BM      MICROBIAL_BM_OR_SINGLE_SOM
// In the case of the Single organic matter pool model, there is not microbial, labile, metastable, nor passive pools

#define        RESIDUE_TYPE_COUNT (MANURE_RESIDUE+1)
// RESIDUE_TYPE_COUNT  is only for version 4.1

			// The following bits identify the organic matter type
// Residue
#define     INCLUDE_STRAW_RESIDUE_OM         1
#define     INCLUDE_MANURE_RESIDUE_OM        2
//Multiple pools (MLMP)
#define     INCLUDE_MICROBIAL_BM             4
#define     INCLUDE_LABILE_ACTIVE_SOM        8
#define     INCLUDE_METASTABLE_ACTIVE_SOM   16
#define     INCLUDE_PASSIVE_SOM             32

#define     INCLUDE_RESIDUE_OM               (INCLUDE_STRAW_RESIDUE_OM | INCLUDE_MANURE_RESIDUE_OM)
#define     INCLUDE_SOM_AND_MICROBIAL        (INCLUDE_MICROBIAL_BM|INCLUDE_LABILE_ACTIVE_SOM|INCLUDE_METASTABLE_ACTIVE_SOM|INCLUDE_PASSIVE_SOM)
#define     INCLUDE_SOM_ONLY                 (INCLUDE_MICROBIAL_BM|INCLUDE_LABILE_ACTIVE_SOM|INCLUDE_METASTABLE_ACTIVE_SOM|INCLUDE_PASSIVE_SOM)
#define     INCLUDE_ALL_ORGANIC_MATTER       0xFF

#define RESIDUE_OM  MANURE_RESIDUE
// This define is for V4.2 where there was a single residue organic matter type declaration
//______________________________________________________________________________
enum Organic_matter_cycling
{
//080729  OM_ORIGINAL_CYCLING    // Prior to version 4.3 there was a single cycling rate (I think this was lignin based)
                           // OM_ORIGINAL_CYCLING is also used for single pool.  //070707
 OM_SINGLE_CYCLING      // Now, for manure, the user has the option of having a single cycling pool for //080729
,OM_FAST_CYCLING        // After 4.3 we have these
,OM_SLOW_CYCLING
,OM_LIGNEOUS_CYCLING    // was OM_LIGNIFIED_CYCLING
,OM_INTRINSIC_CYCLING   // cycling does not apply (is already accounted for?) in Microbial and SOM types
,OM_CYCLING_COUNT       // just the count of enums
};
#define        FIRST_OM_CYCLING           OM_SINGLE_CYCLING
#define        OM_CYCLING_NOT_APPLICABLE  OM_INTRINSIC_CYCLING
#define        OM_LIGNIFIED_CYCLING       OM_LIGNEOUS_CYCLING
#define        OM_RECALCITRANT_CYCLING    OM_LIGNEOUS_CYCLING

// OM_ORIGINAL_CYCLING obsolete renaming to  OM_SINGLE_CYCLING
#define        OM_ORIGINAL_CYCLING        OM_SINGLE_CYCLING
//_2006-02-19___________________________________________________________________
enum Organic_matter_position
   {OM_subsurface_position
   ,OM_flat_surface_position
   ,OM_stubble_surface_position
   ,OM_attached_to_plant_position
   ,OM_POSITION_COUNT
   };
#define MANURE_POSITION_COUNT 2
#define        FIRST_OM_POSITION   OM_subsurface_position
#define        IRRELEVENT_POSITION OM_subsurface_position

extern const char *organic_matter_position_label_table[];                        //070606

#define     INCLUDE_POSITION_SUBSURFACE            1
#define     INCLUDE_POSITION_FLAT_SURFACE          2
#define     INCLUDE_POSITION_STUBBLE_SURFACE       4
#define     INCLUDE_POSITION_ATTACHED_TO_PLANT     8
#define     LAYER_NOT_APPLICABLE_TO_SURFACE_RESIDUE 0
//_2006-03-28___________________________________________________________________
enum Mass_total{BIOMASS_TOTAL,N_MASS_TOTAL,C_MASS_TOTAL,xMASS_TOTAL_COUNT
   , N_MINERALIZATION_TOTAL = xMASS_TOTAL_COUNT,N_IMMOBILIZATION_TOTAL,xMASS_DAILY_TOTAL_COUNT};
//_2006-11-16___________________________________________________________________
#define     LABEL_microbial_biomass_decomposition_constant          "microbial_biomass_decomposition_constant"
#define     LABEL_labile_SOM_decomposition_constant                 "labile_SOM_decomposition_constant"
#define     LABEL_metastable_SOM_decomposition_constant             "metastable_SOM_decomposition_constant"
#define     LABEL_passive_SOM_decomposition_constant                "passive_SOM_decomposition_constant"

#endif

