#include "component.h"
namespace USDA_NRCS
{
//______________________________________________________________________________
Component_struct::Component_struct()
{  clear();
}
//_2011-12-12___________________________________________________________________
void Component_struct::clear()
{
   comppct.clear();
   compname.clear();
   //Component_kind_labeled compkind;      // Kind 254
   majcompflag = false;
   otherph.clear();
   localphase.clear();
   slope.clear();
   slopelenusle.clear();
   //Runoff_class runoff;          //  Runoff Class   254 runoff
   tfact = 0;
   //Wind_erodibility_index wei;   // Wind Erodibility Index 254, tons per acre per year wind_erodibility_index
   //Wind_erodibility_group weg;   // Wind Erodibility Group 254
   //Erosion_class erocl;          // Erosion Class   254
   //Earth_cover_kind_level_one earthcovkind1; // Cover Kind 1  254
   //Earth_cover_kind_level_two earthcovkind2; // Cover Kind 2  254
   //Hydric_condition           hydricon;      // Hydric Condition 254
   //Hydric_rating              hydricrating;  // Hydric Rating 254
   //Drainage_class             drainagecl;    // Drainage Class 254
   elev.clear();
   aspectccwise = 0;
   aspectrep = 0;
   aspectcwise = 0;
   //Vtext geomdesc;               //Geomorphic Description Vtext No
   albedodry.clear();
   airtempa.clear();
   map.clear();
   reannualprecip.clear();
   ffd.clear();
   //USDA_NRCS::Capability_class_labeled     nirrcapcl;  // Nirr LCC 254
   //USDA_NRCS::Capability_subclass_labeled  nirrcapscl; //  Nirr Subcl Choice No 254
   nirrcapunit = 0;
   //USDA_NRCS::Capability_class_labeled irrcapcl;    // Irr LCC 254
   //USDA_NRCS::Capability_subclass_labeled irrcapscl;// Irr Subcl Choice No 254
   irrcapunit = 0;
   cropprodindex = 0;
   //Conservation_tree_shrub_group constreeshrubgrp; //  Cons Tree Shrub Group   254
   //Windbreak_suitability_group wndbrksuitgrp; // Windbreak Suitability (Obsolete)   254
   rsprod.clear();
   foragesuitgrpid.clear();
   //Wildlife_rating            wlgrain;       // Grain Habitat   254
   //Wildlife_rating            wlgrass;       // Grass Habitat   254
   //Wildlife_rating            wlherbaceous;  // Herbaceous Habitat   254
   //Wildlife_rating            wlshrub;       // Shrub Habitat   254
   //Wildlife_rating            wlconiferous;  // Conifer Habitat   254
   //Wildlife_rating            wlhardwood;    // Hardwood Habitat   254
   //Wildlife_rating            wlwetplant;    // Wetland Habitat   254
   //Wildlife_rating            wlshallowwat;  // Water Habitat   254
   //Wildlife_rating            wlrangeland;   // Rangeland Wildlife   254
   //Wildlife_rating            wlopenland;    // Openland Wildlife   254
   //Wildlife_rating            wlwoodland;    // Woodland Wildlife   254
   //Wildlife_rating            wlwetland;     // Wetland Wildlife   254
   //Soil_slippage_potential    soilslippot;   // Soil Slip Pot Choice  254
   //Potential_frost_action     frostact;      // Frost Action Choice  254
   initsub.clear();
   totalsub.clear();
   //Hydrologic_group_labeled   hydgrp;        // Hydrologic Group   254
   //Corrosion_concrete         corcon;        // Corrosion Concrete  254
   //Corrosion_uncoated_steel   corsteel;      // Corrosion Steel   254
   taxclname.clear();
   //Taxonomic_order            taxorder;      // Order   254
   //Taxonomic_suborder         taxsuborder;   // Suborder 254
   //Taxonomic_great_group      taxgrtgroup;   // Great Group 254
   //Taxonomic_subgroup         taxsubgrp;     // Subgroup 254
   //Taxonomic_family_particle_size   taxpartsize;   // Particle Size 254
   //Taxonomic_family_part_size_mod   taxpartsizemod;// Particle Size Mod 254
   //Taxonomic_family_c_e_act_class   taxceactcl;    // CEC Activity Cl 254
   //Taxonomic_family_reaction        taxreaction;   // Reaction 254
   //Taxonomic_family_temp_class      taxtempcl;     // Temp Class 254
   //Taxonomic_moisture_subclass      taxmoistscl;   // Moist Subclass   254
   //Taxonomic_temp_regime            taxtempregime; // Temp Regime 254
   //Soil_taxonomy_edition            soiltaxedition;// Keys to Taxonomy Edition Used 254
   castorieindex = 0;
   flecolcomnum.clear();
   flhe = false;
   flphe = false;
   //FL_Soil_leaching_potential flsoilleachpot;   // FL Leach Pot 254
   //FL_Soil_runoff_potential   flsoirunoffpot;   // FL Runoff Pot   254
   fltemik2use = false;
   fltriumph2use = false;
   indraingrp.clear();
   innitrateleachi=0;
   //MI_Soil_management_group   misoimgmtgrp;     // MI Soil Mgmt Grp  254
   //VA_Soil_management_group   vasoimgtgrp;      // VA Soil Mgmt Grp 254
   mukey.clear();
   cokey.clear();

}
//_2011-12-12___________________________________________________________________
} // namespace

/*
|20||"Dorchester"|"Series"|"Yes"|"MAAT<50"||0|1|2|||||5||"4L"|||||"No"|"Well drained"|213|335|457||||||||7|9|11|762|813|864||||145|160|175|"2"|"w"||||||||||||"Fair"|"Fair"|"Fair"||"Poor"|"Fair"|"Poor"|"Poor"||"Fair"|"Poor"|"Poor"||"High"|||||||"B"|"Low"|"High"|"TYPIC UDIFLUVENTS, FINE-SILTY, MIXED (CALCAREOUS), MESIC"|"Entisols"|"Fluvents"|"Udifluvents"|"Typic Udifluvents"|"fine-silty"|"not used"|"superactive"|"calcareous"|"mesic"||"mesic"|"ninth edition"|||||||||||||"1017218"|"1017218:991195"
|20||"Chaseburg"|"Series"|"Yes"|"HIGH PPT"||0|1|2|||||5||"5"|||||"No"|"Moderately well drained"|||||||||||||||||||||||"1"|||||||||||||"Good"|"Good"|"Good"||"Good"|"Good"|"Poor"|"Poor"||"Good"|"Good"|"Poor"||"High"|||||||"B"|"Moderate"|"Moderate"|"TYPIC UDIFLUVENTS, COARSE-SILTY, MIXED, NONACID, MESIC"|"Entisols"|"Fluvents"|"Udifluvents"|"Typic Udifluvents"|"coarse-silty"|"not used"|"superactive"|"nonacid"|"mesic"||"mesic"|"ninth edition"|||||||||||||"1017218"|"1017218:991196"
|9||"Caneek"|"Series"||"MAAT<50"||0|1|2|||||5||"4L"|||||"Yes"|"Somewhat poorly drained"|198|297|396||||||||7|9|10|762|813|864||||145|160|175|"2"|"w"||||||||||||"Fair"|"Fair"|"Fair"||"Poor"|"Fair"|"Good"|"Good"||"Fair"|"Poor"|"Good"||"High"|||||||"B"|"Low"|"High"|"AERIC FLUVAQUENTS, FINE-SILTY, MIXED (CALCAREOUS), MESIC"|"Entisols"|"Aquents"|"Fluvaquents"|"Aeric Fluvaquents"|"fine-silty"|"not used"|"superactive"|"calcareous"|"mesic"||"mesic"|"ninth edition"|||||||||||||"1017218"|"1017218:991200"
|8||"Water"|"Miscellaneous area"||||||||||||||||||"No"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"1017218"|"1017218:991202"
|4||"Fayette"|"Series"||"MAAT<50, ERODED"|"moderately eroded"|5|7|9||84||"Medium"|5|"48"|"6"|||||"No"|"Well drained"|213|335|457||||||0.23||7|10|12|736|851|965||||145|163|180|"3"|"e"|||||||"3"|||||"Fair"|"Good"|"Good"||"Good"|"Good"|"Very poor"|"Very poor"||"Good"|"Good"|"Very poor"||"High"|0|0|0||||"B"|"Moderate"|"Moderate"|"TYPIC HAPLUDALFS, FINE-SILTY, MIXED, MESIC"|"Alfisols"|"Udalfs"|"Hapludalfs"|"Typic Hapludalfs"|"fine-silty"|"not used"|"superactive"|"not used"|"mesic"||"mesic"|"ninth edition"|||||||||||||"1017218"|"1017218:1199496"
|7||"Rock outcrop"|"Miscellaneous area"||||25|43|60||61||"Very high"||"0"|"8"|||||"Unranked"|"Well drained"|152|381|610||||||||6|9|12|660|813|965||||140|165|190|"8"|"s"||||||||||||"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"||"None"|0|0|0||||"D"||||||||||||||||||||||||||||"1017218"|"1017218:1199497"
*/



