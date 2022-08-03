#if (CROPSYST_VERSION < 5)
#ifdef USE_PCH
#  include "simulation/CropSyst_sim_pch.h"
#else
#  include "corn/string/strconv.hpp"
//#ifndef CORN_STRING_USTRING_H
//130919 #  include "corn/string/ustring.h"
//#endif
#  include "cs_till.h"
#endif
#include "static_phrases.h"
/*
#include "CropSyst/phrases/cs_crops.ph"
#include "CropSyst/phrases/cs_till.ph"
#include "CropSyst/phrases/cropsyst.ph"
#include "CropSyst/phrases/mgmtfile.ph"
*/

#define NOT_APPLICABLE ""
//______________________________________________________________________________
operation_practice_layout operation_practices_deprecated_V4_7[] =
      {{NO_OPERATION,  0,  0, 0, 0,0.0,NOT_APPLICABLE,NOT_APPLICABLE,NOT_APPLICABLE,0},
       {PRIMARY_TILL, 10, 65,20,10,2.3,TL_T_combination_chisel_disc  ,NOT_APPLICABLE        ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 11, 70,20, 7,2.3,TL_T_Chisel                   ,TL_T_straight              ,NOT_APPLICABLE      ,18},
       {PRIMARY_TILL,101, 75,15, 3,2.3,TL_T_Chisel                   ,TL_T_straight              ,NOT_APPLICABLE      ,24},
       {PRIMARY_TILL,125, 35,55, 7,2.3,TL_T_Chisel                   ,TL_T_straight              ,TL_T_with_legume  ,18},
       {PRIMARY_TILL,126, 40,50, 3,2.3,TL_T_Chisel                   ,TL_T_straight              ,TL_T_with_legume  ,24},
       {PRIMARY_TILL,127, 25,65, 8,2.3,TL_T_Chisel                   ,TL_T_twisted               ,TL_T_with_legume  ,18},
       {PRIMARY_TILL,128, 30,60, 4,2.3,TL_T_Chisel                   ,TL_T_twisted               ,TL_T_with_legume  ,24},
       {PRIMARY_TILL, 12, 50,40, 8,2.3,TL_T_Chisel                   ,TL_T_twisted               ,NOT_APPLICABLE      ,18},
       {PRIMARY_TILL,102, 55,35, 4,2.3,TL_T_Chisel                   ,TL_T_twisted               ,NOT_APPLICABLE      ,24},
       {PRIMARY_TILL, 13, 35,55, 6,2.3,TL_T_Chisel                   ,TL_T_after_chopped_stubble ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 14, 40,30, 7,1.8,TL_T_Disc_plow                ,TL_T_6_8_                  ,TL_T_deep         , 0},
       {PRIMARY_TILL, 15, 75,35, 8,1.8,TL_T_Disc_plow                ,TL_T_4_6_                  ,TL_T_shallow      , 0},
       {PRIMARY_TILL, 16, 40,30, 1,3.2,TL_T_Moldboard_plow           ,TL_T_uphill_furrow         ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 17, 25,40, 2,3.2,TL_T_Moldboard_plow           ,TL_T_early_shallow         ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 18, 10,20, 4,3.2,TL_T_Moldboard_plow           ,TL_T_mod                   ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 19,  5,10, 5,3.2,TL_T_Moldboard_plow           ,TL_T_late_fast_deep        ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 28,  5,20, 5,3.2,TL_T_Moldboard_plow           ,TL_T_after_flail           ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 21, 85, 5, 9,1.9,TL_T_Subsoil                  ,NOT_APPLICABLE        ,NOT_APPLICABLE      ,48},
       {PRIMARY_TILL,106, 85, 0, 4,1.9,TL_T_Subsoil                  ,NOT_APPLICABLE        ,NOT_APPLICABLE      ,36},
       {PRIMARY_TILL, 22, 15,80, 9,1.8,TL_T_Heavy_disc_plow          ,NOT_APPLICABLE        ,TL_T_with_legume  , 0},
       {PRIMARY_TILL, 23, 80,10,10,1.9,TL_T_Regular_sweep            ,NOT_APPLICABLE        ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 24, 90, 5, 9,1.9,TL_T_Regular_sweep            ,TL_T_wide_blade            ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL,107, 70, 0,19,1.9,TL_T_Landlord                 ,NOT_APPLICABLE        ,NOT_APPLICABLE      ,30},
       {PRIMARY_TILL,108, 75, 0,19,1.9,TL_T_Landlord                 ,NOT_APPLICABLE        ,NOT_APPLICABLE      ,40},
       {PRIMARY_TILL,109, 95, 0,13,1.9,TL_T_Paraplow                 ,NOT_APPLICABLE        ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 20, 55,30, 9,5.0,TL_T_Regular_offset           ,TL_T_disc                  ,NOT_APPLICABLE      , 0},
       {PRIMARY_TILL, 27, 15,80,11,5.0,TL_T_Regular_offset           ,NOT_APPLICABLE        ,TL_T_with_legume  , 0},

//#define num_secondary_operation_practices  25
       {SECONDARY_TILL, 33, 60,35,11,1.5,TL_T_Disc_harrow              ,TL_T_light        ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 26, 30,65,10,1.5,TL_T_Disc_harrow              ,NOT_APPLICABLE      ,TL_T_with_legume, 0},
       {SECONDARY_TILL, 32, 85,15,10,1.5,TL_T_Field_cultivator         ,NOT_APPLICABLE      ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 25, 95, 5,18,1.5,TL_T_Field_cultivator         ,NOT_APPLICABLE      ,TL_T_after_moldboard, 0},
       {SECONDARY_TILL,130, 45,55,10,1.5,TL_T_Field_cultivator         ,NOT_APPLICABLE      ,TL_T_with_legume  , 0},
       {SECONDARY_TILL, 36, 85,15,11,1.0,TL_T_Rod_weeder               ,NOT_APPLICABLE      ,TL_T_with_sweeps  , 0},
       {SECONDARY_TILL, 46, 95, 5,18,1.0,TL_T_Rod_weeder               ,TL_T_with_sweeps  ,TL_T_after_moldboard, 0},
       {SECONDARY_TILL, 37, 90,10,13,1.0,TL_T_Rod_weeder               ,TL_T_plain        ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 47,100, 0,18,1.0,TL_T_Rod_weeder               ,TL_T_plain        ,TL_T_after_moldboard, 0},
       {SECONDARY_TILL, 34, 75,20,14,1.5,TL_T_Rotary_hoe_or_cultivator ,NOT_APPLICABLE      ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 31, 30,50,17,1.5,TL_T_Rotary_tiller            ,NOT_APPLICABLE      ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 38, 30,50,17,1.5,TL_T_Spike_harrow             ,TL_T_10_bar       ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 48, 30,50,17,1.5,TL_T_Spike_harrow             ,TL_T_10_bar       ,TL_T_first      , 0},
       {SECONDARY_TILL, 29, 80,20,14,1.9,TL_T_Skew                     ,TL_T_backward     ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 30, 70,30,16,1.9,TL_T_Skew                     ,TL_T_treader      ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 43, 90,10,14,1.5,TL_T_Spike_harrow             ,TL_T_5_bar        ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 56,100, 0,18,1.5,TL_T_Spike_harrow             ,TL_T_5_bar        ,TL_T_first      , 0},
       {SECONDARY_TILL, 35, 85,10,12,0.9,TL_T_Spring_tooth             ,TL_T_cultivator   ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 45, 95, 0,18,0.9,TL_T_Spring_tooth             ,NOT_APPLICABLE      ,TL_T_after_moldboard, 0},
       {SECONDARY_TILL,110, 90, 0,14,1.5,TL_T_Swedish_harrow           ,NOT_APPLICABLE      ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 49, 95, 5,18,1.9,TL_T_Tandem_any_spiker_or_tine,NOT_APPLICABLE      ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 44, 90,10,14,1.5,TL_T_Tine_harrow              ,TL_T_5_bar        ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 58,100, 0,18,1.5,TL_T_Tine_harrow              ,TL_T_5_bar        ,TL_T_first      , 0},
       {SECONDARY_TILL, 39, 85,15,14,1.5,TL_T_Tine_harrow              ,TL_T_10_bar       ,NOT_APPLICABLE    , 0},
       {SECONDARY_TILL, 57, 95, 5,18,1.5,TL_T_Tine_harrow              ,TL_T_10_bar       ,TL_T_first      , 0},

       {SECONDARY_TILL,255,  0,100,18,0.9,"Pasture" /*TL_T_Pasture */,"grazing" /*TL_T_grazing */ ,"Trampling"   , 0},


//#define   num_planting_methods 18
       // Dry
       {PLANTING_TILL, 50, 85,10,10,1.9,TL_T_furrow_drill          ,TL_T_semi_deep ,NOT_APPLICABLE, 0},
       {PLANTING_TILL, 51, 80,15, 9,1.9,TL_T_furrow_drill          ,TL_T_deep      ,NOT_APPLICABLE, 0},
       {PLANTING_TILL, 52, 80,15, 9,1.9,TL_T_Hoe_drill             ,NOT_APPLICABLE   ,NOT_APPLICABLE, 0},
       {PLANTING_TILL, 53, 90, 5,11,1.9,TL_T_Double_disc_drill     ,NOT_APPLICABLE   ,NOT_APPLICABLE, 7},
       {PLANTING_TILL, 76, 90, 5,11,1.9,TL_T_Double_disc_drill     ,NOT_APPLICABLE   ,NOT_APPLICABLE, 0},
       {PLANTING_TILL, 54, 70,30,10,1.9,TL_T_Air_seeder_chisel_type,NOT_APPLICABLE   ,NOT_APPLICABLE, 0},
       {PLANTING_TILL, 55, 60,40,10,1.9,TL_T_Air_duck_foot         ,NOT_APPLICABLE   ,NOT_APPLICABLE, 0},
       {PLANTING_TILL, 40, 95, 5,18,1.9,TL_T_Roller_packer         ,NOT_APPLICABLE   ,NOT_APPLICABLE, 0},

       {PLANTING_TILL, 85,100, 0, 0,0.9,TL_T_Aerial_seeding        ,NOT_APPLICABLE   ,NOT_APPLICABLE, 0},
       {PLANTING_TILL, 86,100, 0, 0,0.9,TL_T_Brillion_seeder       ,NOT_APPLICABLE   ,NOT_APPLICABLE, 0},

       // Note: CropSyst reserves 89 for clipping with harvest

       // irrig
       {PLANTING_TILL,112, 95, 0, 0,0.9,TL_T_Irrig_planter         ,TL_Maize       ,NOT_APPLICABLE, 0},
       {PLANTING_TILL,132, 90, 0, 0,0.9,TL_T_Irrig_planter         ,TL_Maize       ,TL_T_ST     , 0},
       {PLANTING_TILL,113, 75, 0, 0,0.9,TL_T_Irrig_planter         ,TL_onion       ,NOT_APPLICABLE, 0},
       {PLANTING_TILL,133, 70, 0, 0,0.9,TL_T_Irrig_planter         ,TL_onion       ,TL_T_ST     , 0},
       {PLANTING_TILL,114, 60, 0, 0,0.9,TL_T_Irrig_planter         ,TL_Potato      ,NOT_APPLICABLE, 0},
       {PLANTING_TILL,134, 55, 0, 0,0.9,TL_T_Irrig_planter         ,TL_Potato      ,TL_T_ST     , 0},
       {PLANTING_TILL,115, 90, 0, 0,0.9,TL_T_Irrig_planter         ,TL_T_veg_seed  ,NOT_APPLICABLE, 0},
       {PLANTING_TILL,135, 85, 0, 0,0.9,TL_T_Irrig_planter         ,TL_T_veg_seed  ,TL_T_ST     , 0},

//#define num_no_till_drill_operation_practices  15
       {NO_TILL_DRILL, 63, 65,35, 9,2.9,TL_T_Chisel_point_or_hoe_opener  ,NOT_APPLICABLE   ,NOT_APPLICABLE  , 0},
       {NO_TILL_DRILL, 60, 75,25,10,1.8,TL_T_Light_double_disc           ,TL_T_drill     ,NOT_APPLICABLE    , 0},
       {NO_TILL_DRILL,116, 90, 0, 0,1.8,TL_T_Light_double_disc           ,TL_T_irrigator ,NOT_APPLICABLE    ,33},
       {NO_TILL_DRILL,117, 95, 0,18,1.8,TL_T_Light_double_disc           ,NOT_APPLICABLE   ,NOT_APPLICABLE    ,36},
       {NO_TILL_DRILL, 61, 60,40,11,1.8,TL_T_Heavy_double_disc           ,TL_T_drill     ,NOT_APPLICABLE    , 0},
       {NO_TILL_DRILL, 59, 30,70,11,1.8,TL_T_Heavy_double_disc           ,NOT_APPLICABLE   ,TL_T_with_legume, 0},
       {NO_TILL_DRILL, 64, 45,55,11,1.8,TL_T_Heavy_double_disc           ,TL_T_spring    ,TL_T_with_scuffer, 0},
       {NO_TILL_DRILL,118, 80, 0, 0,1.8,TL_T_Heavy_double_disc           ,TL_T_irrigator ,NOT_APPLICABLE    ,33},
       {NO_TILL_DRILL,119, 85, 0,18,1.8,TL_T_Heavy_double_disc           ,NOT_APPLICABLE   ,NOT_APPLICABLE    ,36},
       {NO_TILL_DRILL,120, 75, 0,18,1.8,TL_T_Heavy_double_disc           ,NOT_APPLICABLE   ,TL_T_with_corn_residue,36},

       {NO_TILL_DRILL, 62, 50,50,12,1.8,TL_T_Heavy_double_disc           ,NOT_APPLICABLE   ,TL_T_with_scuffer, 0},
       {NO_TILL_DRILL, 65, 45,55,12,1.8,TL_T_Heavy_double_disc           ,TL_T_spring    ,NOT_APPLICABLE    , 0},
       {NO_TILL_DRILL, 66, 30,70,12,1.8,TL_T_Heavy_double_disc           ,NOT_APPLICABLE   ,TL_T_with_legume, 0},

       {NO_TILL_DRILL, 77, 90,10,18,0.7,TL_T_No_till_drill_1             ,NOT_APPLICABLE   ,NOT_APPLICABLE    , 0},
       {NO_TILL_DRILL, 78, 75,15,10,0.7,TL_T_No_till_drill_2             ,NOT_APPLICABLE   ,NOT_APPLICABLE    , 0},

//#define num_residue_practices  5
//operation_practice_layout   residue_practices[] {
 //      {RESIDUE,  0,  0, 0, 0,NOT_APPLICABLE,NOT_APPLICABLE      ,NOT_APPLICABLE, 0},
       // sf is the percentage of material remaining on the surface.
       {RESIDUE, 80,100, 0,18,0.9,TL_T_Stubble   ,TL_T_flail_chop_bust ,NOT_APPLICABLE   , 0},
       {RESIDUE, 81, 65, 0,18,0.9,TL_T_Stubble   ,TL_T_grazing         ,NOT_APPLICABLE   , 0},
       {RESIDUE, 82, 35, 0,18,0.9,TL_T_Stubble   ,TL_T_baling          ,NOT_APPLICABLE   , 0},
       {RESIDUE, 83, 10 , 0,18,0.9,TL_T_Stubble   ,TL_T_burning         ,NOT_APPLICABLE   , 0},
       {RESIDUE,100, 50, 0,18,0.9,TL_T_Stubble   ,TL_T_grazing         ,TL_Maize       , 0},


// Need to add one with total removal!!!!

         // Special animal trampling added for Omaru 040126  SCS code is bogus
       // Special residue incorporation added for oumarou 040610 SCS code is bogus
       {RESIDUE,256, 20, 80,18,0.9,"Natural" ,"Low"     ,"incorporation"   , 0},
       {RESIDUE,257, 50, 50,18,0.9,"Natural" ,"Medium"  ,"incorporation"   , 0},
       {RESIDUE,258, 80, 20,18,0.9,"Natural" ,"High"    ,"incorporation"   , 0},

/* not implemented yet
   num_events = 10;
   events : ARRAY[1..num_events] of operation_practice_layout =
      {{  1,100, 0,18,'beginning of rotation year  '},
       {  7,100, 0,18,'Harvest of irr & dryland w/o'},
       {  9,100, 0,18,'End of rotation             '},
       {  2,100, 0,18,'Emergence                   '},
       {  3,100, 0,18,'Growth start                '},
       {  5,100, 0,18,'Growth end                  '},
       { 90,100, 0,18,'                            '},
*/
//fertilize}
       {FERTILIZATION, 41, 80,10,10,0.9,TL_Fertilization,TL_T_shank,NOT_APPLICABLE  ,0},
       {FERTILIZATION,135, 40,50,10,0.9,TL_Fertilization,TL_T_shank,TL_T_with_legume ,0},
       {FERTILIZATION, 42,100, 0,18,0.9,TL_Fertilization,TL_T_dry_or_drip,NOT_APPLICABLE  ,0},
       {FERTILIZATION,111, 70, 0,10,0.9,TL_Fertilization,TL_Injected,NOT_APPLICABLE   ,0},
/*
//pesticide
       { 84;description:'Herbicide                   ',100, 0,18},
       {111;description:'Fumigation {injection}      ', 70, 0,10},
       {137;description:'Other pesticide             ',100, 0,18},
*/
       // end of table marker
       {NO_OPERATION,  0,  0, 0, 0,0.0,NOT_APPLICABLE,NOT_APPLICABLE,NOT_APPLICABLE,0}
      };
//______________________________________________________________________________
operation_practice_layout &lookup_SCS_code_deprecated_V4_7(int code)
{  for (nat16 i = 1; operation_practices_deprecated_V4_7[i].kind; i++)
       if (operation_practices_deprecated_V4_7[i].SCS_code == code)
          return operation_practices_deprecated_V4_7[i];
   return operation_practices_deprecated_V4_7[0];
};
//______________________________________________________________________________
std::string /*130513 CORN::Ustring*/ SCS_description_buffer;
//______________________________________________________________________________
const char *lookup_SCS_description_deprecated_V4_7(int code)
{  int i;
   for (i = 1; operation_practices_deprecated_V4_7[i].kind && (operation_practices_deprecated_V4_7[i].SCS_code != code); i++);

   SCS_description_buffer.assign(//common_translate
   ((operation_practices_deprecated_V4_7[i].kind == PRIMARY_TILL)   ?TL_Primary
	 :(operation_practices_deprecated_V4_7[i].kind == SECONDARY_TILL)?TL_secondary
	 :(operation_practices_deprecated_V4_7[i].kind == PLANTING_TILL) ?TL_Planting
	 :(operation_practices_deprecated_V4_7[i].kind == NO_TILL_DRILL) ?TL_No_till_drill
	 :(operation_practices_deprecated_V4_7[i].kind == RESIDUE)       ?TL_Residue
//	 :(operation_practices_deprecated_V4_7[i].kind == EVENT)         ?TL_Operation
//	 :(operation_practices_deprecated_V4_7[i].kind == FERTILIZATION) ?TL_Fertilization
    : NOT_APPLICABLE
   ));

   SCS_description_buffer.append(" ");
   SCS_description_buffer.append((operation_practices_deprecated_V4_7[i].desc1));
   if (operation_practices_deprecated_V4_7[i].desc2 != NOT_APPLICABLE)
   {
     SCS_description_buffer.append(" (");
     SCS_description_buffer.append((operation_practices_deprecated_V4_7[i].desc2));
     SCS_description_buffer.append(")");
   };
   if (operation_practices_deprecated_V4_7[i].withX != NOT_APPLICABLE)
   { SCS_description_buffer.append(" ");
     SCS_description_buffer.append((operation_practices_deprecated_V4_7[i].withX));
   };
   if (operation_practices_deprecated_V4_7[i].sp)
   {
      char buff[10];
      CORN::int16_to_cstr((int16)operation_practices_deprecated_V4_7[i].sp,buff,10);
      SCS_description_buffer.append(" spacing:\"");
      SCS_description_buffer.append(buff);
   };
   return SCS_description_buffer.c_str();
};
//______________________________________________________________________________
#endif
