//---------------------------------------------------------------------------
#ifndef component_structH
#define component_structH

#include "USDA/NRCS/soil/survey/database/STATSGO_SSURGO_types.h"
#include "USDA/NRCS/soil/survey/domains.h"

namespace USDA_NRCS
{
/* Eventually these strings will be enums
   I just haven't taken the time, or needed to define enums and
   label tables for all of these.                                                //150928RLN
*/

//typedef std::string Component_kind;
typedef std::string Runoff_class;
typedef std::string Wind_erodibility_index;
typedef std::string Wind_erodibility_group;
typedef std::string Erosion_class;
typedef std::string Earth_cover_kind_level_one;
typedef std::string Earth_cover_kind_level_two;
typedef std::string Hydric_condition;
typedef std::string Hydric_rating;
typedef std::string Drainage_class;
typedef std::string Vtext;   // Not sure what Vtext is
//defined in STATSGO_SSURGO_types typedef std::string Capability_class;
//defined in STATSGO_SSURGO_types typedef std::string Capability_subclass;
typedef std::string Conservation_tree_shrub_group;
typedef std::string Windbreak_suitability_group;
typedef std::string Soil_slippage_potential;
typedef std::string Potential_frost_action;
typedef std::string Wildlife_rating;
//typedef std::string Hydrologic_group;
typedef std::string Corrosion_concrete;
typedef std::string Corrosion_uncoated_steel;
typedef std::string Taxonomic_order;
typedef std::string Taxonomic_suborder;
typedef std::string Taxonomic_great_group;
typedef std::string Taxonomic_subgroup;
typedef std::string Taxonomic_family_particle_size;
typedef std::string Taxonomic_family_part_size_mod;
typedef std::string Taxonomic_family_c_e_act_class;
typedef std::string Taxonomic_family_reaction;
typedef std::string Taxonomic_family_temp_class;
typedef std::string Taxonomic_moisture_subclass;
typedef std::string Taxonomic_temp_regime;
typedef std::string Soil_taxonomy_edition;
typedef std::string FL_Soil_leaching_potential;
typedef std::string FL_Soil_runoff_potential;
typedef std::string MI_Soil_management_group;
typedef std::string VA_Soil_management_group;
typedef std::string Wildlife_rating;

//---------------------------------------------------------------------------
struct Component_struct
{
   nat8_lrh   comppct;          // Comp %   0 100 percent
   std::string compname;         // Component Name String No 60
   Component_kind_labeled compkind;      // Kind 254
   bool majcompflag;             // Major Component 3
   std::string otherph;          // SIR phase No 40
   std::string localphase;       // Local Phase   40
   float32_lrh slope;            // Slope Gradient (prcsn 1) 0 999, percent
   nat16_lrh   slopelenusle;     // Slope Length USLE    0 4000, meters
   Runoff_class runoff;          //  Runoff Class   254 runoff
   float32     tfact;            // T  (prcsn 1) 5 tons per acre per year
   Wind_erodibility_index wei;   // Wind Erodibility Index 254, tons per acre per year wind_erodibility_index
   Wind_erodibility_group weg;   // Wind Erodibility Group 254
   Erosion_class erocl;          // Erosion Class   254
   Earth_cover_kind_level_one earthcovkind1; // Cover Kind 1  254
   Earth_cover_kind_level_two earthcovkind2; // Cover Kind 2  254
   Hydric_condition           hydricon;      // Hydric Condition 254
   Hydric_rating              hydricrating;  // Hydric Rating 254
   Drainage_class             drainagecl;    // Drainage Class 254
   float32_lrh elev;             // Elevation   (prcsn 1) -300 8550 meters
   nat16 aspectccwise;           // Aspect Counter Clockwise   0 360 degrees
   nat16 aspectrep;              // Aspect Representative   0 360 degrees
   nat16 aspectcwise;            // Aspect Clockwise   0 360 degrees
   Vtext geomdesc;               //Geomorphic Description Vtext No
   float32_lrh albedodry;        // Albedo Dry  (prcsn 2) 0 1
   float32_lrh airtempa;         // MAAT  (prcsn 1) -50 50 degrees centigrade
   nat16_lrh   map;              // MAP  No 0 11500 millimeters
   nat16_lrh   reannualprecip;   // REAP No 0 11500 millimeters
   nat16_lrh   ffd;              // Frost Free Days  0 365 days
   USDA_NRCS::Capability_class_labeled     nirrcapcl;  // Nirr LCC 254
   USDA_NRCS::Capability_subclass_labeled  nirrcapscl; //  Nirr Subcl Choice No 254
   nat8 nirrcapunit;            // Nirr LCU  1 99
   USDA_NRCS::Capability_class_labeled irrcapcl;    // Irr LCC 254
   USDA_NRCS::Capability_subclass_labeled irrcapscl;// Irr Subcl Choice No 254
   nat8        irrcapunit;       // Irr LCU  No 1 99
   nat8        cropprodindex;    // Prod Index   0 100
   Conservation_tree_shrub_group constreeshrubgrp; //  Cons Tree Shrub Group   254
   Windbreak_suitability_group wndbrksuitgrp; // Windbreak Suitability (Obsolete)   254
   nat16_lrh   rsprod; // Range Prod  0 20000 pounds per acre per year
   std::string  foragesuitgrpid; // Forage Suitability Group ID 11
   Wildlife_rating            wlgrain;       // Grain Habitat   254
   Wildlife_rating            wlgrass;       // Grass Habitat   254
   Wildlife_rating            wlherbaceous;  // Herbaceous Habitat   254
   Wildlife_rating            wlshrub;       // Shrub Habitat   254
   Wildlife_rating            wlconiferous;  // Conifer Habitat   254
   Wildlife_rating            wlhardwood;    // Hardwood Habitat   254
   Wildlife_rating            wlwetplant;    // Wetland Habitat   254
   Wildlife_rating            wlshallowwat;  // Water Habitat   254
   Wildlife_rating            wlrangeland;   // Rangeland Wildlife   254
   Wildlife_rating            wlopenland;    // Openland Wildlife   254
   Wildlife_rating            wlwoodland;    // Woodland Wildlife   254
   Wildlife_rating            wlwetland;     // Wetland Wildlife   254
   Soil_slippage_potential    soilslippot;   // Soil Slip Pot Choice  254
   Potential_frost_action     frostact;      // Frost Action Choice  254
   nat16_lrh   initsub;                      // Init Subsid  0 999 centimeters
   nat16_lrh   totalsub;                     // Total Subsid  0 999 centimeters
   Hydrologic_group_labeled   hydgrp;        // Hydrologic Group   254
   Corrosion_concrete         corcon;        // Corrosion Concrete  254
   Corrosion_uncoated_steel   corsteel;      // Corrosion Steel   254
   std::string                taxclname;     // Taxonomic Class 120
   Taxonomic_order            taxorder;      // Order   254
   Taxonomic_suborder         taxsuborder;   // Suborder 254
   Taxonomic_great_group      taxgrtgroup;   // Great Group 254
   Taxonomic_subgroup         taxsubgrp;     // Subgroup 254
   Taxonomic_family_particle_size   taxpartsize;   // Particle Size 254
   Taxonomic_family_part_size_mod   taxpartsizemod;// Particle Size Mod 254
   Taxonomic_family_c_e_act_class   taxceactcl;    // CEC Activity Cl 254
   Taxonomic_family_reaction        taxreaction;   // Reaction 254
   Taxonomic_family_temp_class      taxtempcl;     // Temp Class 254
   Taxonomic_moisture_subclass      taxmoistscl;   // Moist Subclass   254
   Taxonomic_temp_regime            taxtempregime; // Temp Regime 254
   Soil_taxonomy_edition            soiltaxedition;// Keys to Taxonomy Edition Used 254
   int8        castorieindex;    // CA Storie Index   0 100
   std::string flecolcomnum;     // FL Ecol Comm #   5
   bool        flhe;             // FL HE  3
   bool        flphe;            // FL PHE 3
   FL_Soil_leaching_potential flsoilleachpot;   // FL Leach Pot 254
   FL_Soil_runoff_potential   flsoirunoffpot;   // FL Runoff Pot   254
   bool        fltemik2use;                     // FL Temik 3
   bool        fltriumph2use;                   // FL Triumph   3
   std::string indraingrp;                      // IN Drainage Grp 3
   int8        innitrateleachi;                 // IN NO3 Leach Index   0 99
   MI_Soil_management_group   misoimgmtgrp;     // MI Soil Mgmt Grp  254
   VA_Soil_management_group   vasoimgtgrp;      // VA Soil Mgmt Grp 254
   std::string mukey;   // Mapunit Key   30
   std::string cokey;  // Component Key   30
 public:
   Component_struct();
   void clear();
};
}
#endif
