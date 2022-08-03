#ifndef N_sourcesH
#define N_sourcesH

#include <corn/labeled_enum.h>

#define   LABEL_ammonium_source        "ammonium_source"
#define   LABEL_urea                   "urea"
#define   LABEL_urea_ammonium_nitrate  "urea_ammonium_nitrate"
#define   LABEL_ammonium_sulfate       "ammonium_sulfate"
#define   LABEL_ammonium_nitrate       "ammonium_nitrate"
#define   LABEL_anhydrous_ammonia      "anhydrous_ammonia"

#define LABEL_NH4_appl_method   "NH4_appl_method"
#define LABEL_surface_broadcast    "surface_broadcast"
#define LABEL_surface_dribble      "surface_dribble"
#define LABEL_incorporate          "incorporate"
#define LABEL_inject               "inject"

#define   LABEL_org_N_appl_method               "org_N_appl_method"
#define   LABEL_surface_broadcast_no_incorporation "surface_broadcast_no_incorporation"
#define   LABEL_surface_broadcast_incorporation    "surface_broadcast_incorporation"
#define   LABEL_knifed                             "knifed"
#define   LABEL_sprinkler                          "sprinkler"

// These residue source with be removed in V.5   (the user now creates organic matter / manure description files)
#define   LABEL_org_N_source           "org_N_source"
#define   LABEL_poultry_layers         "poultry_layers"
#define   LABEL_poultry_broilers_fresh "poultry_broilers_fresh"
#define   LABEL_poultry_broilers_aged  "poultry_broilers_aged"
#define   LABEL_swine                  "swine"
#define   LABEL_dairy_fresh            "dairy_fresh"
#define   LABEL_dairy_tank             "dairy_tank"
#define   LABEL_dairy_lagoon           "dairy_lagoon"
#define   LABEL_beef_fresh             "beef_fresh"
#define   LABEL_beef_aged_2_5          "beef_aged_2.5"
#define   LABEL_beef_aged_1_5          "beef_aged_1.5"
#define   LABEL_beef_aged_1_0          "beef_aged_1.0"

/*120315 now use organic_matter_source_label_table
// 080908 Residue_source is being replaced with Manure_residue_source
// in common/residue/residue_const.ch
//______________________________________________________________________________
enum  Residue_source
    {STRAW
      //  { The rest are manure organic matter }
    ,POULTRY_LAYERS
    ,POULTRY_FRESH_BROILERS_TURKEYS
    ,POULTRY_AGED_BROILERS_TURKEYS
    ,SWINE
    ,DAIRY_FRESH
    ,DAIRY_TANK_STORAGE
    ,DAIRY_ANAEROBIC_LAGOON_STORAGE
    ,BEEF_FRESH
    ,BEEF_AGED_2_5
    ,BEEF_AGED_1_5
    ,BEEF_AGED_1_0
     // Added 080908 data from
    ,MUNICIPLE_WASTE_COMPOSE
    ,SW
    ,residue_source_COUNT
};
//______________________________________________________________________________
extern const char *residue_source_label_table[];
DECLARE_LABELED_ENUM(Residue_source_labeled,Residue_source,residue_source_label_table)
*/
//_2002-03-22_1997?_____________________________________________________________
enum  NH4_Appl_method
     {SURFACE_BROADCAST,SURFACE_DRIBBLE,INCORPORATE,INJECT};
extern const char *NH4_appl_method_label_table[];
DECLARE_LABELED_ENUM(NH4_Appl_method_labeled,NH4_Appl_method,NH4_appl_method_label_table)
//_2002-03-22_1997?_____________________________________________________________
enum  Org_N_appl_method
     {SURFACE_BROADCAST_NO_INCORPORATION,SPRINKLER_IRRIGATED,SURFACE_BROADCAST_INCORPORATION,KNIFED};
extern const char *org_N_appl_method_label_table[];
DECLARE_LABELED_ENUM(Org_N_appl_method_labeled,Org_N_appl_method,org_N_appl_method_label_table)
//_2002-03-22_1997?_____________________________________________________________
enum  Ammonium_source {UREA,UREA_AMMONIUM_NITRATE,AMMONIUM_SULFATE,
        AMMONIUM_NITRATE,ANHYDROUS_AMMONIA,AMMONIUM_NITRO_SULFATE};
extern const char *ammonium_source_label_table[];
DECLARE_LABELED_ENUM(Ammonium_source_labeled,Ammonium_source,ammonium_source_label_table)
//_2002-03-22_1997-07-09________________________________________________________


#endif
