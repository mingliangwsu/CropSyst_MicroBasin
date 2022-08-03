#include "common/residue/residue_const.h"
//______________________________________________________________________________
nat16 manure_decomp_time_coef[12] =// POULTRY_LAYERS..BEEF_AGED_1_0]
{0    // <- This is reserved for plant matter
,158  //POULTRY_LAYERS,
,262  //POULTRY_FRESH_BROILERS_TURKEYS
,398  //POULTRY_AGED_BROILERS_TURKEYS
,158  //SWINE
,523  //DAIRY_FRESH
,640  //DAIRY_TANK_STORAGE
,994  //DAIRY_ANAEROBIC_LAGOON_STORAGE
,262  //BEEF_FRESH
,700  //BEEF_AGED_2_5
,828  //BEEF_AGED_1_5
,1657 //BEEF_AGED_1_0
};
// RLN - These values appear to be consistent with lignified material
// RLN - This is the number of days it takes the manure to reach 63% decomposition.
// Currently these are always convert to the time to reach 50% decomposition. 070123_
//______________________________________________________________________________
/* The following are approximations based on short term
   N fate  Meisinger & Randall N-budgets for soil-crop systems. */
  float32 Xfract_manure_to_deep[5][2] =
   //solid liquid}
   {
   //{0,0}, //{SPACER,SPACER},
    {0.800,0.830}, //broadcast no incororate
    {0.770,0.770}, //Sprinkler   (actually no solid sprinkler)
    {0.965,0.965}, //broadcast incorporated
    {0.980,0.980}  //Knifed      (actually no solid knifing
   };
//______________________________________________________________________________
float32 manure_incorporation_fraction[5] =
{ 0.0, //broadcast no incororation
  0.0, //Sprinkler   (actually no solid sprinkler)
  0.5, //broadcast incorporated
  1.0  //Knifed      (actually no solid knifing
};
//_2009-02-24___________________________________________________________________
float32 N_in_manure_percent_dry_wt[12]  =      // becoming obsolete replace with Organic_matter_composition_decomposition.nitrogen_percent_DryWt
{ 0, // <- This is reserved for plant matter
  4.5,    //POULTRY_LAYERS,                0.90
  3.8,    //POULTRY_FRESH_BROILERS_TURKEYS,0.75
  3.0,    //POULTRY_AGED_BROILERS_TURKEYS, 0.60
  2.8,    //SWINE,                         0.90
  3.5,    //DAIRY_FRESH,                   0.50
  3.0,    //DAIRY_TANK_STORAGE,            0.42
  2.0,    //DAIRY_ANAEROBIC_LAGOON_STORAGE,0.30
  3.5,    //BEEF_FRESH,                    0.75
  2.5,    //BEEF_AGED_2_5                  0.40
  1.5,    //BEEF_AGED_1_5                  0.35
  1.0     //BEEF_AGED_1_0                  0.20
};
//______________________________________________________________________________
const char *RUSLE2_residue_type_label_table[] =
{ "unknown"
, "fragile"
, "moderate"
, "nonfragil"
, "tough"
, "stone"
,0 };
//_2006-07-31___________________________________________________________________
const Label_description organic_matter_source_label_table[] =
{{"plant_residue"                             ,"plant_residue (generally)"}
//  { The rest are manure organic matter }
,{"poultry_layers_manure"                     ,"poultry layers fresh manure"}
,{"poultry_fresh_broilers_turkeys_manure"     ,"poultry broilers or turkeys fresh manure"}
,{"poultry_aged_broilers_turkeys_manure"      ,"poultry broilers or turkeys aged manure"}
,{"swine_manure"                              ,"swine manure"}
,{"dairy_fresh_manure"                        ,"dairy fresh manure"}
,{"dairy_tank_storage_manure"                 ,"dairy tank storage manure"}
,{"dairy_anaerobic_lagoon_storage_manure"     ,"dairy anaerobic lagoon storage manure"}
,{"beef_fresh_manure"                         ,"beef fresh manure"}
,{"beef_aged_2_5_manure"                      ,"beef aged manure 2.5% N"}
,{"beef_aged_1_5_manure"                      ,"beef aged manure 1.5% N"}
,{"beef_aged_1_0_manure"                      ,"beef aged manure 1.0% N"}
// Added 080908
,{"municiple_waste_compost"                   ,"municiple waste compost"}
,{"sewage_sludges"                            ,"sewage sludges"}
,{"corn_stover"                               ,"corn stover"}
,{"sorghum_stover"                            ,"sorghum stover"}
,{"wheat_straw"                               ,"wheat straw"}
,{"oat_straw"                                 ,"oat straw"}
,{"soybean_residue"                           ,"soybean residue"}
,{0,0} // residue_source_COUNT
};
//_2006-07-31___________________________________________________________________
Organic_matter_composition_decomposition default_organic_matter_composition_decomposition[organic_matter_source_COUNT] =
{
//          fraction biomass    Days to 50% decomposition
//  N     C,     ,{Sng Fast Slow LignInt},{sngFastSlowLignInt
  {1.0,10.0,false,{1,0.333,0.333,0.333,0},{555,555,555,555,0}}  //    plant_residue,  // Replace this with plant_residue
// Manure values adapted from Elliott and Swanson (1976) and U.S. EPA (1979) Land Use of animals wastes. p. 80-90 in Land applicaton of waste materials. Soil Conserv. Soc. Am., Ankeny. IA.
, {4.5,45.0,false,{1,0.333,0.333,0.333,0},{109,109,109,109,0}}  //     ,poultry_layers_manure
, {3.8,38.0,false,{1,0.333,0.333,0.333,0},{181,181,181,181,0}}  //     ,poultry_broilers_turkeys_fresh_manure
, {3.0,30.0,false,{1,0.333,0.333,0.333,0},{275,275,275,275,0}}  //     ,poultry_broilers_turkeys_aged_manure
, {2.8,28.0,false,{1,0.333,0.333,0.333,0},{109,109,109,109,0}}  //     ,swine_manure
, {3.5,35.0,false,{1,0.333,0.333,0.333,0},{362,362,362,362,0}}  //     ,dairy_fresh_manure
, {3.0,30.0,false,{1,0.333,0.333,0.333,0},{443,443,443,443,0}}  //     ,dairy_tank_storage_manure
, {2.0,20.0,false,{1,0.333,0.333,0.333,0},{688,688,688,688,0}}  //     ,dairy_anaerobic_lagoon_storage_manure
, {3.5,35.0,false,{1,0.333,0.333,0.333,0},{181,181,181,181,0}}  //     ,beef_fresh_manure
, {2.5,25.0,false,{1,0.333,0.333,0.333,0},{484,484,484,484,0}}  //     ,beef_aged_2_5_manure
, {1.5,15.0,false,{1,0.333,0.333,0.333,0},{573,573,573,573,0}}  //     ,beef_aged_1_5_manure
, {1.0,10.0,false,{1,0.333,0.333,0.333,0},{1148,1148,1148,1148,0}}  //     ,beef_aged_1_0_manure
// Residue values from Doran et al. 1977  Microbial concerns when wastes are applied to land (pg. 343-361) in Land as a waste management alternative Proc. Cornell Agric. Waste Mgt. Conf. Ann Arbor Science.
, {1.0,10.0,false,{1,0.333,0.333,0.333,0},{555,555,555,555,0}}  //     ,municiple_waste_compost
, {4.0,40.0,false,{1,0.333,0.333,0.333,0},{555,555,555,555,0}}  //     ,sewage_sludges   // N range 2.0-6.0
, {0.8, 8.0,false,{1,0.333,0.333,0.333,0},{555,555,555,555,0}}  //     ,corn_stover      // N range 0.6-1.0
, {0.8, 8.0,false,{1,0.333,0.333,0.333,0},{555,555,555,555,0}}  //     ,sorghum_stover   // N range 0.6-1.0
, {0.6, 6.0,false,{1,0.333,0.333,0.333,0},{555,555,555,555,0}}  //     ,wheat_straw      // N range 0.5-0.7
, {0.6, 6.0,false,{1,0.333,0.333,0.333,0},{555,555,555,555,0}}  //     ,oat_straw        // N range 0.5-0.7
, {1.6,16.0,false,{1,0.333,0.333,0.333,0},{555,555,555,555,0}}  //     ,soybean_residue  // N range 1.0-2.3
, {1.6,16.0,false,{1,0.333,0.333,0.333,0},{ 30,  3,  7, 70,0}}  // default_source for cropsyst
//residue_source_COUNT
};
//_2008-09-08_________________default_organic_matter_composition_decomposition_/

