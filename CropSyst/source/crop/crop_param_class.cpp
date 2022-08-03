//#include "options.h"
#include "crop/crop_param_class.h"
#include "corn/math/compare.hpp"
#include "biomatter/decomposition_const.h"
#include "residue/residue_const.h"
#include "corn/metrology/units_code.hpp"
#include "static_phrases.h"

#ifndef VIC_CROPSYST
#include "common/simulation/event.h"
#endif


//______________________________________________________________________________
using namespace CORN;
extern bool LADSS_mode;
namespace CropSyst {
//#ifndef YAML_PARAM_VERSION
bool Crop_parameters_class::Adjustment::
setup_structure(CORN::Data_record &data_rec,bool for_write)
{  data_rec.expect_string("parameter",parameter,255);
   data_rec.expect_string("value",value,255);
   return true;
}
//#endif
//______________________________________________________________________________
const char *Crop_parameters_class::Adjustment_event::label_string(std::string &buffer) const
{
   begin_sync.append_to_string(buffer _ISO_FORMAT_DATE_TIME);
   buffer += ":";
   buffer += parameter;
   buffer += "=";
   buffer += value;
   return buffer.c_str();
}
//_2017-04-23___________________________________________________________________
// once I implement parameter adjustments idiom (V5) restore this back only V4
DECLARE_CONTAINER_ENUMERATED_SECTION(Crop_parameters_class::Adjustment_event, adjustment_section_VV,true);
//______________________________________________________________________________
//#endif
//______________________________________________________________________________
Crop_parameters_class::Thermal_time::Thermal_time()
: Crop_parameters_struct::Thermal_time()                                         //021124
, thermal_response_cowl(thermal_response,linear)                                 //151109
{  base_temperature     = 3.0;
   cutoff_temperature   = 22.0;                                                  //990227
   opt_temperature      = 22.0;                                                  //021124
   max_temperature      = 35.0;                                                  //021124
   thermal_response_cowl.set(linear);                                            //151109
}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Thermal_time::setup_structure(Data_record &record,bool for_write)    modification_
{  record.set_current_section("phenology");
   record.expect_enum("thermal_response",thermal_response_cowl);                      //151109
   return true;
}
//______________________________________________________________________________
Crop_parameters_class::Transpiration::Transpiration()
: Crop_parameters_struct::Transpiration()
{  normal_max_water_uptake_mm =10.0;
   LWP_wilt_point             =-1600.0;
   ET_coef              = 1.0;
   LWP_stomatal_closure = -700.0;                                                //020418 (110208 was stomatal_closure_leaf_water_pot)
   a1 = 0;  //121114 special temporary paramters for Jordi to test
   a2 = 0;  // 0.0 values disable this.
}
//_2011-02-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Transpiration::setup_structure(Data_record &record,bool for_write)    modification_
{  //121114 special temporary paramters for Jordi to test
   record.set_current_section("Jordi");
      record.expect_float32("a1",a1);
      record.expect_float32("a2",a2);
   record.set_current_section("transpiration");
   return true;
}
//______________________________________________________________________________
Crop_parameters_class::Biomass_production::Biomass_production()
: Crop_parameters_struct::Biomass_production()
,TUE_equation_cowl   (TUE_equation,TUE_Tanner_Sinclair)                          //080408
   // Default to the original model.
#if (CROPSYST_VERSION==4)
, RUE_basis_cowl   (RUE_basis,unspecified_RUE_basis)                             //080728
#endif

{  WUE_changes                   =false;                                         //080508
   min_tolerable_temp         =  3.0;                                            //130531
   max_tolerable_temp         = 45.0;                                            //130508
   low_threshold_limit_temp   = 10.0;                                            //130508
   high_threshold_limit_temp  = 25.0;                                            //130508

   RUE_global                 =4.0;                                        //110829_040428
   RUE_PAR_deprecated         =3.0;                                              //110829
   continuous_cultivation_impact_factor = 1.0;

   #ifdef YAML_PARAM_VERSION
   // eventually all all versions will use the new adjustments
   #else
   for (int j = 0; j < 2; j++)                                                   //080506
   {  for (int season = 0; season <= 5; season++)                                //080428
         season_biomass_adjustment[season] = 1.0;                                //080731
      TUE_at_1kPa_VPD                     [j] = 5.0;                             //080505
      water_productivity                  [j] =20.0;  /*this is not a good default use 20 for c3, 30 for c4*/  //080505
      reference_biomass_transpiration_coef[j] = 5.0;                             //040729
      TUE_scaling_coef                    [j] = 0.45;                            //091201
   }
   #endif
}
//_2011-02-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Biomass_production::setup_structure(Data_record &record,bool for_write)    modification_
{  record.set_current_section(LABEL_growth);                                     //020405
   record.expect_bool("WUE_changes",WUE_changes);                                //080508
      // Note that the thermal time for the WUE change is in thermal time parameters  080514
   record.expect_enum("TUE_equation",TUE_equation_cowl);                         //080505
   #if (CROPSYST_VERSION==4)
   record.expect_enum("RUE_basis",RUE_basis_cowl);                               //110825
   #endif

   #if ((CS_VERSION > 0) && (CS_VERSION < 5))
   if (!for_write)
   {  // renamed variables
      // previously there wasn't RUE total,
      record.expect_float32("RUE_max",RUE_global);                               //110825
        // was RUE_max
   }
   #endif
   return true;
}
//_2011-02-08___________________________________________________________________
Crop_parameters_class::Vernalization::Vernalization()
:Crop_parameters_struct::Vernalization()
{  low_temp    = 3.0;
   high_temp   =10.0;
   start       =10.0;                                                            //011016
   end         =50.0;
   min_factor  = 0.0;
   enabled     =false;                                                           //020718
}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Vernalization::setup_structure(Data_record &record,bool for_write)    modification_
{  record.set_current_section(LABEL_vernalization);                              //020405
   record.expect_bool(LABEL_enabled,enabled );                                   //021015
   return true;
}
//______________________________________________________________________________
Crop_parameters_class::Phenology::Phenology()
: Crop_parameters_struct::Phenology()
,begin_shoot_growth_deg_day        (initiation.emergence) // Alias               //020408
{
   initiation.emergence            =    (100);                                   //990228
   initiation.tuber                =   (1000);
   initiation.flowering            =   (1000);
   initiation.filling              =   (1020);
   initiation.maturity             = (1500.0);                                   //990228
   initiation.senescence           = (1080.0);                                   //080724

   culmination.accrescence           =   (1040);
   culmination.senescence      = (1501.0);                                       //131024
   culmination.root_depth       =   (1040);                                      //070321
   culmination.filling   =   (1300);                                             //030521

   #ifdef YAML_PARAM_VERSION
   // eventually all versions will use parameter adjustments
   #endif
   #if (CROPSYST_VERSION==4)
   /*initiation_thermal_time.*/WUE_change           =   (1000);                      //080514
   #endif
   phenologic_sensitivity_water_stress =           (1.0);                        //020410
   maturity_significant                =          (true);                        //080319
   clipping_resets                     =         (false);                        //040719
      // clipping_resets may be true for all crops, but I am
     // leaving it false for compatibility with old alfalfa.
}
//_2008-07-22_____________________Crop_parameters_class::Phenology::Phenology__/
void Crop_parameters_class::Phenology::offset_by(int16 offset_deg_day)
{  initiation.emergence            += offset_deg_day;
   // This is currently alias, dont increment begin_shoot_growth_deg_day        //020405
   initiation.tuber                += offset_deg_day;
   culmination.accrescence         += offset_deg_day;
   culmination.root_depth          += offset_deg_day;                            //070321
   initiation.flowering            += offset_deg_day;
   initiation.filling              += offset_deg_day;          // eventually remove the f32 suffix
   initiation.maturity             += (float32)offset_deg_day; // needs to be float to allow very larger numbers for long term perennials such as trees  //050511
  culmination.filling              += (float32)offset_deg_day; // needs to be float to allow very larger numbers for long term perennials such as trees
}
//_2003-05-21_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Phenology::setup_structure(Data_record &record,bool for_write)    modification_
{  record.set_current_section(LABEL_phenology);                                  //020405
   record.expect_bool("maturity_significant",maturity_significant);              //080319
   record.expect_bool("clipping_resets",     clipping_resets);                   //040719
   return true;
}
//______________________________________________________________________________
Crop_parameters_class::Photoperiod::Photoperiod()
: Crop_parameters_struct::Photoperiod()                                          //100512
, photoperiodism_cowl(photoperiodism)                                            //151122_100512
{  photoperiodism = no_photoperiod;                                              //151122_100512
   stop_day_length          = 0.0;                                               //120516
   unconstrained_day_length = 0.0;                                               //120516
}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Photoperiod::setup_structure(Data_record &record,bool for_write)    modification_
{  record.set_current_section(LABEL_photoperiod);                                //020405
   record.expect_enum("photoperiodism",photoperiodism_cowl);                     //151122_100513
   if (!for_write)
      // Support or old files
      record.expect_enum("consideration",photoperiodism_cowl);                       //100513
   return true;
}
//_2010-05-13___________________________________________________________________
Crop_parameters_class::Emergence_hydro_thermal::Emergence_hydro_thermal()
: emergence_model_cowl(emergence_model)
{  emergence_model = EMERGENCE_THERMAL_TIME;
   seedling_leaf_area_cm2        = 2;
   germination_base_temperature  = -1;  // WARNING need reasonable default
   mean_base_soil_water_pot_J_kg = -1000;  // WARNING need reasonable default
   stdev_base_soil_water_pot_J_kg= 100;  // WARNING need reasonable default
   a_slope                       = 22.35;
   b_intercept                   = 129.66;
}
//_2004-12-01____________Emergence_hydro_thermal_parameters_class:constructor__/
bool Crop_parameters_class::Emergence_hydro_thermal::setup_structure(Data_record &record,bool for_write) modification_
{  record.set_current_section("emergence");
   record.expect_enum("model",emergence_model_cowl);                             //100520
   return true;
}
//_2004-12-01_Crop_parameters_class::Emergence_hydro_thermal::setup_structure__/
Crop_parameters_class::Quiescence::Quiescence()
{  consider_inactive_days  =7;                                                   //080401
   inducement_temperature  =10;
   start_DOY = 0;                                                                //190516LML
   end_DOY = 0;                                                                  //190516LML
}
//_2008-04-01_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Quiescence::setup_structure(Data_record &record,bool for_write)    modification_
{  // End season or dormancy inactivity considieration
   record.set_current_section("inactive_period");                                //080331
   return true;
}
//_2010-05-11_________Crop_parameters_class::Inactive_period::setup_structure__/
Crop_parameters_class::Dormancy::Dormancy()
{  //050715 Note I eventually want to create a degree_day unit (see not in units.h)
   chill_hours                         = 400.0;
   senesce                             = 100.0;
   deg_day_bud_break_chill_req_sat     = 100;                                    //030515
   deg_day_bud_break_chill_req_not_sat = 150;                                    //030515
}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Dormancy::setup_structure(Data_record &record,bool for_write)    modification_
{  record.set_current_section(LABEL_dormancy);                                   //020408
   return true;
}
//_2010-06-10________________Crop_parameters_class::Dormancy::setup_structure__/
Crop_parameters_class::Root::Root()
: Crop_parameters_struct::Root()                                                 //100720
{  max_depth                        = 1.5;
   surface_density                  = 3.0;                                       //030722
   density_distribution_curvature   = 0.1;                                       //030722
   sensitivity_to_water_stress      = 0.0;                                       //061212
   #if (CS_VERSION==4)
   length_per_unit_mass_km_kg_V4    =90.0;                                       //060612
   length_at_emergence_cm           = 2.0;                                       //110218
   #else
   length_at_emergence_cm           = 1.2;                                       //110218
   #endif
   root_shoot_emergence_ratio       = 2.0;                                       //130624
   root_shoot_full_ratio            = 0.1;                                       //130624
//180727    sow_depth                        = 0.08;                                      //110218 currently only by VIC?
   initial_depth_deprecated         = 0; //180728 non 0 now indicates file uses deprecated value  = 0.2;  //120817 The depth of the roots at surface biomass emergence
}
//_2006-12-12_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Root::setup_structure(Data_record &record,bool for_write) modification_
{  record.set_current_section("root");                                           //020408
      record.expect_float32("initial_depth", initial_depth_deprecated);                     //120817
            // "cm (depth at emergence)"
   return true;
}
//_2010-06-10___________________________________________________________________
Crop_parameters_class::Morphology::Morphology()
: Crop_parameters_struct::Morphology()
,canopy_growth_cowl  (canopy_growth_model,leaf_area_index_based)                   //080725
{  max_canopy_height             =1.5;                                           //990213
   reduce_canopy_expansion_LWP   =-800.0;                                        //080506
   stop_canopy_expansion_LWP     =-1200.0;                                       //080506
   kc                            =0.5;                                           //110527_990228 was under transpiration
}
//_2010-02-19_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Morphology::setup_structure(Data_record &record,bool for_write) modification_
{  record.set_current_section("crop");
      record.expect_enum("canopy_growth",canopy_growth_cowl);                    //080725
   record.set_current_section("morphology");
   return true;
}
//_2010-02-19___________________________________________________________________
Crop_parameters_class::Canopy_growth_cover_based::Canopy_growth_cover_based()
: Crop_parameters_struct::Canopy_growth_cover_based()
{  cover_initial           = 0.01;                                               //080723
   cover_maximum_no_CO2_adj= 0.9;                                                //080723
   cover_total_season_end  = 0.1;                                                //171219_080723
   cover_green_season_end  = 0.0;                                                //171219_171009
   thermal_time_season_end = 1080.0;                                             //171009
      //to be compatible with previous crop file X was scenescence
   fract_season_to_reach_cover_max_half = 0.5;                                   //111206

   shape_coef_accrescent = 9.0;                                                  //171221
   shape_coef_senescent  = 9.0;                                                  //171221
}
//_2010-07-30_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Canopy_growth_cover_based::setup_structure(Data_record &record,bool for_write) modification_
{  record.set_current_section("canopy_cover");                                   //020408
   //moved to V4 and V5
   /*
   record.expect_float32("green_season_end",cover_green_season_end);             //171219
   record.expect_float32("thermal_time_season_end",thermal_time_season_end  ); //171219
      // Warning thermal_time_season_end may be moved to to phenology   171221
   */

   if (!for_write)
   { // These have been renamed (allow import from old files)
   record.expect_float32("CC_green_X",cover_green_season_end);                   //171219_171009
   record.expect_float32("TT_X",thermal_time_season_end);                                 //171009
   }
   return true;
}
//_2010-07-30___________________________________________________________________
Crop_parameters_class::Canopy_growth_LAI_based::Canopy_growth_LAI_based()
: Crop_parameters_struct::Canopy_growth_LAI_based()
{  initial_GAI                      =0.011;                                      //000207
   regrowth_GAI                     =0.011;                                      //080207
   max_LAI                          =5.0;                                        //990228
   specific_leaf_area               =22.0;
   fract_LAI_mature                 =0.8;
   stem_leaf_partition              =3.0;
   leaf_duration_deg_day            =800;                                        //050628
   leaf_duration_sensitivity_stress =1.0;
//141106   senescence_power_coef_obsolete   =1.0;
      // Default senescence_power_coef is linear (as prior to V 4.8.10)
   clipping_removes_newest_first    =true;                                       //071126
}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Canopy_growth_LAI_based::setup_structure(Data_record &record,bool for_write) modification_
{  record.set_current_section("leaf");                                           //020408
      record.expect_bool("clip_newest",clipping_removes_newest_first);           //071126
   return true;	
}
//_2010-07-30___________________________________________________________________
Crop_parameters_class::Harvest::Harvest()
{  index_unstressed          =(0.50);                                            //110218
//   #ifdef YAML_PARAM_VERSION
//   stress_sensitivity        =(0.0);                                           //150914
//   #else
   stress_sensitivity_growth        =(0.0);                                      //020419
   stress_sensitivity_tuber_init    =(0.0);
   tuber_growth_sensitivity  =(0.0);
//   #endif
   translocation_fraction_max = 0.4;                                             //110907
   apply_adjustment_to_unstressed_harvest_index = true;                          //110907
   apply_heat_extreme_adjustment_to_unstressed_harvest_index = false;            //150206
   editor_grain_stress_sensitivity.set_default();                                //130425
}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#if (VIC_CROPSYST_VERSION != 2)
bool Crop_parameters_class::Harvest::Grain_stress_sensitivity_period
::setup_structure(CORN::Data_record &data_rec,bool for_write)
{
   bool satup = Simple_event::setup_structure(data_rec,for_write);
   data_rec.expect_float32("cold_stress_no_stress_threshold_temperature"  ,cold.no_stress_threshold_temperature );
   data_rec.expect_float32("cold_stress_max_stress_threshold_temperature" ,cold.max_stress_threshold_temperature);
   data_rec.expect_float32("cold_stress_sensitivity"                      ,cold.sensitivity                     );
   data_rec.expect_float32("cold_stress_exposure_damaging_hours"          ,cold.exposure_damaging_hours         );
   data_rec.expect_int16  ("cold_stress_exposure_initial_hour"            ,cold.exposure_initial_hour           ); //130628

   data_rec.expect_float32("heat_stress_no_stress_threshold_temperature"  ,heat.no_stress_threshold_temperature );
   data_rec.expect_float32("heat_stress_max_stress_threshold_temperature" ,heat.max_stress_threshold_temperature);
   data_rec.expect_float32("heat_stress_sensitivity"                      ,heat.sensitivity                     );
   data_rec.expect_float32("heat_stress_exposure_damaging_hours"          ,heat.exposure_damaging_hours         );
   data_rec.expect_int16("heat_stress_exposure_initial_hour"              ,heat.exposure_initial_hour           ); //130628
   return satup;   
}
#endif
//_2013-04-29__________________________________________________________________
Crop_parameters_class::Fruit::Fruit()
: harvest_condition_mode_cowl(harvest_condition_mode,management_scheduled_harvest)
{  fract_total_solids                     =0.35;                                 //000635
   max_fruit_load_kg_ha                   =20000;                                //000616
   /*180601 was for Jordi but never implemented
   initial_fruit_mass                     =0.02;                                 //071127
   initial_reserves_release_rate          =0.02;                                 //071127
   clusters_per_vine                      =30;                                   //071127
   berries_per_cluster                    =25;                                   //071127
   fruits_per_tree                        =250;                                  //071127
   */
//moved above   harvest_condition_mode_labeled         =management_scheduled_harvest;         //081204
   harvest_temperature                    =15;                                   //081204
   harvest_temperature_days               =5;                                    //081204
   harvest_DOY_earliest                   =258;                                  //081204
   harvest_DOY_latest                     =275;                                  //081204
   #ifdef YAML_PARAM_VERSION
   growth_fraction_to_fruit       =0.9;                                          //150914
   #else
   initial_growth_fraction_to_fruit       =0.9;                                  //030521
   rapid_growth_fraction_to_fruit         =0.65;                                 //030521
   max_water_uptake_before_fruiting_mm       =10.0;                              //091202
   max_water_uptake_during_initial_fruit_mm  =10.0;                              //091202
   max_water_uptake_during_radid_fruit_mm    =10.0;
   max_water_uptake_during_veraison_mm       =10.0;                              //091202
   max_water_uptake_after_maturity_mm        =10.0;                              //091202
   #endif
   grape=false;                                                                  //021206
}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Fruit::setup_structure(Data_record &record,bool for_write) modification_
{  record.set_current_section(LABEL_fruit);                                      //020405
   return true;
}
//_2011-03-26___________________________________________________________________
#ifdef CHECK_NEEDED
110127 probably is not but dont delete yet
Crop_parameters::Fruit::Fruit(const Fruit &copy_from)
{
fract_total_solids                    =copy_from.fract_total_solids;
max_fruit_load_kg_ha                  =copy_from.max_fruit_load_kg_ha; // Warning need good value
grape                                 =copy_from.grape;
initial_fruit_mass                    =copy_from.initial_fruit_mass;
initial_reserves_release_rate         =copy_from.initial_reserves_release_rate;
clusters_per_vine                     =copy_from.clusters_per_vine;
berries_per_cluster                   =copy_from.berries_per_cluster;
fruits_per_tree                       =copy_from.fruits_per_tree;
initial_growth_fraction_to_fruit      =copy_from.initial_growth_fraction_to_fruit;
rapid_growth_fraction_to_fruit        =copy_from.rapid_growth_fraction_to_fruit;

harvest_condition_mode_labeled        =copy_from.harvest_condition_mode_labeled.get();
harvest_temperature_days              =copy_from.harvest_temperature_days)
harvest_temperature                   =copy_from.harvest_temperature)
harvest_DOY_earliest                  =copy_from.harvest_DOY_earliest)
harvest_DOY_latest                    =copy_from.harvest_DOY_latest)

max_water_uptake_before_fruiting_mm       =copy_from.max_water_uptake_before_fruiting_mm)
max_water_uptake_during_initial_fruit_mm  =copy_from.max_water_uptake_during_initial_fruit_mm)
max_water_uptake_during_radid_fruit_mm    =copy_from.max_water_uptake_during_radid_fruit_mm)
max_water_uptake_during_veraison_mm       =copy_from.max_water_uptake_during_veraison_mm)
max_water_uptake_after_maturity_mm        =copy_from.max_water_uptake_after_maturity_mm)
}

#endif
 //_____________________________________________________________________________
Crop_parameters_class::Crop_parameters_class()
:Common_parameters_data_record(NO_ASSOCIATED_DIRECTORY,LABEL_crop,CS_VERSION)    //180626 CS_VERSION_NUMBERS) //050323
, sowing_event_ID       ("") // Will be assigned for LADSS when parameters are instanciated for sowing event   //051129
//TEMP DISABLED /*031121_*/ ,cropgro                (new CropGro_parameters)
,crop_model_labeled     (CROPSYST_CROP_MODEL)                                    //020508
,harvested_part_labeled (UNKNOWN_PART) // Must be unknown else we can't load option parameters  //020508
,photosynthetic_pathway_labeled (C3)                                             //110504
,life_cycle_labeled     (annual_life_cycle)                                      //020716
,senesces               (true)                                                   //040808
,land_use_labeled       (ROW_CROPS)
// I think these defaults will be effectively the same as the original
//050715  Note, I haven't assigned units codes to all these.  It is not critical yet
// Warning I need a range of values from Claudio
,parameter_editor_mode(false)                                                    //030520
   //Note these are grams of biomass per kg water (NOT PPM)
,linger_days(90)
#ifndef VIC_CROPSYST
,has_max_water_uptake_adjustments(false)                                         //120725
#endif
#ifdef LIU_XIAO_CROP
,parameters_Liu_Xiao(0)                                                          //180116
#endif
{}
//______________________________________________________________________________
Crop_parameters_class::~Crop_parameters_class()
{
   #ifdef LIU_XIAO_CROP
   delete parameters_Liu_Xiao;
   #endif
}
//_2018-01-16__________________________________________________________________/
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
void Crop_parameters_class::initialize_fallow()
{
   description.brief = "Fallow"; //151121 TL_Fallow;                             //020330
   land_use_labeled.set(FALLOW);
   photosynthetic_pathway_labeled.set(C3);                                       //110504
   Crop_parameters_struct::Thermal_time &thermal_time = ref_thermal_time();
//   Crop_parameters_struct::Thermal_response &thermal_reponse = ref_thermal_response();//151109
   thermal_time.base_temperature                       =0.0;                     //021124
   thermal_time.cutoff_temperature                     =40.0;                    //021124
   thermal_time.opt_temperature                        =40.0;                    //021124
   thermal_time.max_temperature                        =40.0;                    //021124
   thermal_time.max_temperature                        =40.0;                    //021124
//NYI   thermal_time.resolution_time_step = DAILY; // Fallow does not need hourly resolution.   //021124_
/*
   virtual  Inactive_period_parameters_struct             &ref_inactive_period()const ;
   virtual  Thermal_time_parameters_struct                &ref_thermal_time()const ;

   virtual  Vernalization_parameters_struct               *ref_vernalization()const ;
   virtual  Photoperiod_parameters_struct                 *ref_photoperiod()const ;
   virtual  Emergence_hydro_thermal_parameters_struct     &ref_emergence()const ;

   virtual  Canopy_growth_cover_based_parameters_struct   &ref_canopy_growth_cover_based()const ;
   virtual  Root_parameters_struct                        &ref_root()const ;
*/
   Crop_parameters_struct::Phenology &phenology = ref_phenology();
   phenology.maturity_significant          =false;                               //080319
   phenology.initiation.emergence           =1;
   phenology.initiation.flowering           =1;
   phenology.initiation.tuber               =1;
   phenology.initiation.maturity            =1;
   phenology.culmination.filling            =1;                                  //030521
   phenology.culmination.accrescence        = 1000; //{???}
   phenology.culmination.root_depth         = 1000; //{???}                      //070321
   phenology.initiation.filling             = 1000; //{???}
   phenology.phenologic_sensitivity_water_stress         = 1.0;
   Crop_parameters_struct::Transpiration &transpiration = mod_transpiration();
   transpiration.normal_max_water_uptake_mm              = 0.0;
   transpiration.ET_coef                     =1.0;
   transpiration.LWP_stomatal_closure        = -1000.0; //         {PAW_root_impedes = 0.1;  <-   this must be added}
   transpiration.LWP_wilt_point              = -1500.0;

   Crop_parameters_struct::Canopy_growth_LAI_based     &canopy_growth_LAI_based = ref_canopy_growth_LAI_based();
   canopy_growth_LAI_based.max_LAI                          =0.011;
   canopy_growth_LAI_based.initial_GAI                      = 0.5;               //000207
   canopy_growth_LAI_based.regrowth_GAI                     = 0.5;               //080207
   canopy_growth_LAI_based.fract_LAI_mature                 = 0.8;
   canopy_growth_LAI_based.specific_leaf_area               = 1.0; //{???}
   canopy_growth_LAI_based.stem_leaf_partition              = 0.5; //{???}
   canopy_growth_LAI_based.leaf_duration_deg_day            = 1000;//{???}
   canopy_growth_LAI_based.leaf_duration_sensitivity_stress = 1.0; //{???}
   // Warning need defaults from Claudio
   Crop_parameters_struct::Morphology &morphology = ref_morphology();
   morphology.kc =0.0;                                                           /*110527 was in transpiration*/
   morphology.reduce_canopy_expansion_LWP = 0.8; // J/kg                         //080506
   morphology.stop_canopy_expansion_LWP   = 0.8; // J/kg                         //080506
   Crop_parameters_struct::Biomass_production &biomass_production = ref_biomass_production();
   biomass_production.continuous_cultivation_impact_factor = 1.0;                //151031
   #ifdef YAML_PARAM_VERSION
   // eventually all versions will used parameter adjustments
      biomass_production.TUE_at_1kPa_VPD_adjustable   = 5.0;                     //040729
      biomass_production.water_productivity_adjustable = 5.0;                    //080505
      biomass_production.reference_biomass_transpiration_coef_adjustable = 5.0;  //080428
      biomass_production.TUE_scaling_coef_adjustable = 0.45;                     //091201
   #endif
   #if ((CROPSYST_VERSION==4) || (!defined(YAML_PARAM_VERSION)))
   for (int j = 0; j < 2; j++)                                                   //080506
   {

      for (int season = 0; season <= 5; season++)                                //080428
         biomass_production.season_biomass_adjustment[season] = 1.0;             //080731

      biomass_production.TUE_at_1kPa_VPD   [j]= 5.0;                             //040729
      biomass_production.water_productivity[j] = 5.0;                            //080505
      biomass_production.reference_biomass_transpiration_coef[j]= 5.0;           //080428
      biomass_production.TUE_scaling_coef  [j] = 0.45;                           //091201
   }
   #endif
   biomass_production.RUE_global = 6.0;                                          //110905
   biomass_production.RUE_PAR_deprecated = 3.0;                                  //110905
}
//_1999-02-17___________________________________________________________________
int16 Crop_parameters_class::param_end_veg_growth_or_rapid_fruit_growth_deg_day() const
{  return (int16) ((crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)
   ?  ref_phenology().culmination.filling
   :  ref_phenology().culmination.accrescence);
}
//_2003-05-29___________________________________________________________________
#ifndef YAML_PARAM_VERSION
float64 Crop_parameters_class::param_TUE_at_1kPa_VPD( bool before_WUE_change ) const
{  int vegetative_growth_index =
      ref_biomass_production().WUE_changes && before_WUE_change ? 1 : 0;
   return ref_biomass_production().TUE_at_1kPa_VPD[vegetative_growth_index];
}
//_2008-5-28____________________________________________________________________
float64 Crop_parameters_class::param_TUE_scaling_coef( bool before_WUE_change ) const
{  int vegetative_growth_index =
      ref_biomass_production().WUE_changes && before_WUE_change ? 1 : 0;
   return ref_biomass_production().TUE_scaling_coef[vegetative_growth_index];
}
//_2009-12-01___________________________________________________________________
float64 Crop_parameters_class::param_water_productivity(bool before_WUE_change )  const
{  int vegetative_growth_index =                                                 //080506
      ref_biomass_production().WUE_changes && before_WUE_change ? 1 : 0;
   return ref_biomass_production().water_productivity[vegetative_growth_index];
}
//_2008-04-28___________________________________________________________________
float64 Crop_parameters_class::param_reference_biomass_transpiration_coef(bool before_WUE_change) const
{  int vegetative_growth_index =                                                 //080506
      ref_biomass_production().WUE_changes && before_WUE_change ? 1 : 0;
   return ref_biomass_production().reference_biomass_transpiration_coef[vegetative_growth_index];
} //(kg/m2)(kPa)/m
//_2004-07-29___________________________________________________________________
#endif
float64 Crop_parameters_class::param_base_temp()                           const
{ return  ref_thermal_time().base_temperature;
}
//_2011-08-23__________________________________________________________________/
#ifndef YAML_PARAM_VERSION
float64 Crop_parameters_class::param_RUE_global(bool before_WUE_change)    const
{  return ref_biomass_production().RUE_global;
}
//_2011-08-25___________________________________________________________________
float64 Crop_parameters_class::param_RUE_PAR_deprecated(bool before_WUE_change)       const
{  return ref_biomass_production().RUE_PAR_deprecated;
}
//_2011-08-25___________________________________________________________________
#endif
bool Crop_parameters_class::is_perennial()                                 const
{  Life_cycle life_cycle = (Life_cycle)life_cycle_labeled.get();
   return life_cycle >= perennial_life_cycle;                                    //080722
}
//_2002-07-16___________________________________________________________________
bool Crop_parameters_class::is_annual()                                    const
{  Life_cycle life_cycle = (Life_cycle)life_cycle_labeled.get();
   return (life_cycle == annual_life_cycle);
}
//_2002-07-16___________________________________________________________________
bool Crop_parameters_class::is_fruit_tree()                         affirmation_
{ return (crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);                   //130408
}
//_2011-08-24___________________________________________________________________
bool Crop_parameters_class::applies_harvest_index()                        const
{  bool apply = (crop_model_labeled.get() == CROPSYST_CROP_MODEL);
   if (harvested_part_labeled.get() >= HARVEST_CANOPY)   apply = false;
   if (land_use_labeled.get() == PASTURE)                apply = false;
   return apply;
}
//_2004-06-14___________________________________________________________________
bool Crop_parameters_class::has_leaf_senescence() const
{  bool any_senescence = is_deciduous() || senesces                              //040808
      || (life_cycle_labeled.get() == annual_life_cycle) ;
     // May move to parameter editor
   return any_senescence;
}
//_2003-05-21___________________________________________________________________

bool Crop_parameters_class::expect_structure(bool for_write)
{  bool expected = Common_parameters_data_record::expect_structure(for_write);   //161023_021015
   structure_defined = false;                                                    //120314
   bool CROPSYST_ORCHARD = (crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL); //020715
   set_current_section(LABEL_crop);
#ifdef LADSS_MODE
   expect_int32(LABEL_LADSS_land_use_ID,LADSS_land_use_ID);                      //021220
#endif
   expect_string("feed_name_immature"  ,feed_name_immature_early,50);            //021114
   expect_string("feed_name_midmature" ,feed_name_midmature_headed_normal,50);   //021114
   expect_string("feed_name_mature"    ,feed_name_mature_normal,50);             //021114
   expect_enum("model",crop_model_labeled);                                      //020408
   expect_enum(LABEL_harvested_part,harvested_part_labeled);                     //020405
   expect_string("RUSLE2_name"  ,RUSLE2_name,100);                               //110831
   expect_string("RUSLE2_description"  ,RUSLE2_description,100);                 //110812
   expect_enum("abscission",abscission_labeled);                                 //141121

   // Options
   #if (CS_VERSION<6)
      // C_species label will be obsolete in V6
   #if (CS_VERSION==5)
      // Continue to recognized C_species when reading in V5
   if (!for_write)
   #endif
   expect_enum(LABEL_C_species,photosynthetic_pathway_labeled);                  //110504_020324
   #endif
      // Eventually rename to photosynthetic_pathway
   expect_enum("photosynthetic_pathway",photosynthetic_pathway_labeled);         //110504_020324
//170710 #ifdef V234
//170710    expect_bool(LABEL_perennial_obs,perennial_obsolete,CROPSYST_VV_BOOL_FORM);    //970123
//170710 #endif
   expect_enum(LABEL_life_cycle,life_cycle_labeled);                             //020716
   expect_enum(LABEL_land_use,land_use_labeled);                                 //020324
   expect_enum("season_dormancy_mode",season_dormancy_mode_labeled);             //080331
/*130526  moved to V4 because in V5 we will have adjustable parameters which can be on a curve
#ifndef VIC_CROPSYST
//130423 now permanent#ifdef CROP_PARAM_ADJUST
   EXPECT_ENUMERATED_SECTION("adjustment",adjustment_section_VV,adjustments);    //120726
//130423 now permanent#endif
#endif
*/
   #ifndef YAML_PARAM_VERSION
   // replaced with continuous_cultivation_impact_factor 151101
   set_current_section("water_use_efficiency");                                  //080818
      expect_float32("season2_adj",ref_biomass_production().season_biomass_adjustment[2],"");   //060720
      expect_float32("season3_adj",ref_biomass_production().season_biomass_adjustment[3],"");   //060720
      expect_float32("season4_adj",ref_biomass_production().season_biomass_adjustment[4],"");   //060720
      expect_float32("season5_adj",ref_biomass_production().season_biomass_adjustment[5],"");   //060720
   #endif

// In version 5 the season adjustments will be 0 indexed (season offset)  [Need to verify this ]

   set_current_section(LABEL_leaf);                                              //020405
      expect_bool(LABEL_senesces,senesces);                                      //040808
   ref_transpiration_class()     .setup_structure(*this,for_write);              //110327
   ref_biomass_production_class().setup_structure(*this,for_write);              //110327
   ref_morphology_class()        .setup_structure(*this,for_write);              //110325
//171124   #if (CROPSYST_VERSION == 4)
//171124   if (!for_write)
      // the harvest parameter section was previously named [harvest_index]
      ref_harvest_class()           .setup_structure                             //110606_110325
      (*this,for_write,harvested_part_labeled.get()
      //171124 abandoned ,LABEL_harvest_index
      );
//171124   #endif
//171124   ref_harvest_class()           .setup_structure
//171124      (*this,for_write,harvested_part_labeled.get(),"yield"/*171124 "harvest"*/);

   #ifdef CROPSYST_PROPER
   ref_emergence_class()         .setup_structure(*this,for_write);              //110327
   #else
   // if there is no emergence section the VV data source is
   // falling back to [crop] section when it is encountered in the file
   set_current_section("emergence");                                             //170307
   #endif
   ref_tolerance_class()         .setup_structure(*this,for_write,harvested_part_labeled.get()); //110606_110325_020717
   if ((!CROPSYST_ORCHARD || !for_write))                                        //020405
      ref_nitrogen_class().setup_structure(*this,for_write);                     //110325
   ref_fruit_class().setup_structure(*this,for_write);                           //110512
   ref_CO2_response_class().setup_structure(*this,for_write);                    //110606

#ifdef LADSS_MODE
   if (LADSS_mode)                                                               //021220
   {
      expect_int16("EMERGE_DD"         ,ref_phenology().emergence_deg_day);
      expect_int16("TUBER_INIT_DD"     ,ref_phenology().tuber_initiation_deg_day);
      expect_int16("FLOWER_DD"         ,ref_phenology().begin_flowering_deg_day);
      expect_int16("PEAK_LAI_DD"       ,ref_phenology().max_canopy_deg_day/*130429 end_vegetative_growth_deg_day*/);
      expect_int16("MAX_ROOT_DEPTH_DD" ,ref_phenology().max_root_depth_deg_day);
      expect_int16("FILLING_DD"        ,ref_phenology().begin_filling_deg_day);
      expect_float32("MATURITY_DD"     ,ref_phenology().begin_maturity_deg_day); //050628
      expect_float32("RAPID_GROWTH_DD" ,ref_phenology().begin_rapid_fruit_growth_deg_day);   //061006
   }
#endif
   if ( (CROPSYST_ORCHARD || !for_write))                                        //020405
   { // fruit trees and grape harvest parameters
      set_current_section(LABEL_fruit);
      expect_bool("grape",mod_fruit().grape);                                    //170524_021206
   }
   #ifndef YAML_PARAM_VERSION
   // adjustments and grain_stress_period will not be in V5
   // When I have implemented the parameter adjustment idiom this
   // will be enabled only in V4
   set_current_section(LABEL_crop);
   EXPECT_ENUMERATED_SECTION("adjustment",adjustment_section_VV,adjustments);    //120726
   #endif
   structure_defined = true;                                                     //120314
   return expected;                                                              //161023
}
//_2001-01-09______________________________________________________________________________
Crop_parameters_class::Nitrogen::Nitrogen()
: nitrogen_leaf_stress_mode_cowl(nitrogen_leaf_stress_mode,no_leaf_stress)
{  fixating                            =false;
   legume_fraction                     =1.0; //default must be 1.0 (non pasture) //070105
   max_uptake_daily_rate_kg_ha         =5.0;                                     //061129
   #if (CROPSYST_VERSION == 4)
   demand_adjust                       =1.0;                                     //061213
   if (dilution_curve_based_on_max_conc)                                         //121219
   {  demand_adjust                       =1.0;                                  //061213
      biomass_to_start_dilution_max_N_conc_T_ha = CropSyst::biomass_to_start_dilution_max_N_conc_default[C3];   //default for C3 species
   }
   #endif
   biomass_to_start_dilution_crit_N_conc_T_ha = CropSyst::biomass_to_start_dilution_crit_N_conc_default[C3];   //default for C3 species  121219
   emergence_max_conc = 0.007;
   emergence_crit_conc = 0.007;
   stubble_max_conc                    =0.007;                                   //061214
   root_conc                           =0.007;                                   //061214
   nitrogen_leaf_stress_mode           =no_leaf_stress; // default no_leaf_stress if for compatibility with previous version //070227
   residual_N_not_available_for_uptake =1.0;                                     //070209
   soil_N_conc_where_N_uptake_decreases=5.0;                                     //070209
   PAW_where_N_uptake_rate_decreases   =0.5;                                     //070209
   dilution_curve_max_conc_mature = CropSyst::N_mature_max_conc_default[C3];//default for C3 species
   dilution_curve_slope                = 0.45;                                   //150901_120620
   end_dilution_curve_deg_day          = 0;
   TUE_stress_sensitivity              = 0.5;                                    //151117
}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Nitrogen::setup_structure(Data_record &record,bool for_write)    modification_
{  record.set_current_section(LABEL_nitrogen);                                   //020405
   record.expect_bool(LABEL_fixation,fixating);
   record.expect_float32("legume_fraction",legume_fraction);                     //070105
   record.expect_enum("nitrogen_leaf_stress_mode",nitrogen_leaf_stress_mode_cowl);//070227
   record.expect_float32("TUE_stress_sensitivity",TUE_stress_sensitivity);       //151117
   return true;
}
//_2011-03-25_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
void Crop_parameters_class::Nitrogen::set_fallow_conditions()
{  max_uptake_daily_rate_kg_ha   = 0.0;                                          //061129
   // Currently fallow is not allowed to uptake
   stubble_max_conc              =0.007;
   root_conc                     =0.01;
}
//_2002-04-08___________________________________________________________________
float32 Crop_parameters_class::Nitrogen::provide_concentration_slope(Photosynthetic_pathway photosynthetic_pathway)         provision_
{  if (CORN::is_approximately<float32>(dilution_curve_slope,0.0,0.000001))       //121219
   {
#if (CROPSYST_VERSION == 4)
//121219 These became deprecated in version 4.17.00 because dilution curves are now based on critical curve not maximum curve. obsolete in V5
      if (dilution_curve_based_on_max_conc)                                      //121219
      {  float64 slope_adjustment  =  1.0 / demand_adjust;
         dilution_curve_slope = CropSyst::N_dilution_curve_slope_default[photosynthetic_pathway] * slope_adjustment;

      } else
#endif
         dilution_curve_slope = CropSyst::N_dilution_curve_slope_default[photosynthetic_pathway];//121219
   }
   return dilution_curve_slope;
}
//_2012-05-07___________________________________________________________________
Crop_parameters_class::Salinity::Salinity()
{  osmotic_pot_50      =-0.0000001; // was -200.0
   salt_tolerance_P    = 0.0000001;
}
//_2002-04-08___________________________________________________________________
Crop_parameters_class::CO2_Response::CO2_Response()
{
   CO2_concentration_when_measured.RUE = 350.0;                                  //131206
   CO2_concentration_when_measured.TUE = 350.0;                                  //131206
   non_rectagular_hyperbola_solution.alpha                  = 0.0032725;         //151028
   non_rectagular_hyperbola_solution.theta                  = 0.941574;          //151028
   non_rectagular_hyperbola_solution.growth_ratio_asymptotic= 1.2771338;         //151028

/* C3               C4
alpha 0.0032725     0.0038
theta 0.941574      0.977
GRA   1.2771338     1.0627
*/
}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::CO2_Response::setup_structure(Data_record &record,bool for_write)    modification_
{  record.set_current_section(LABEL_CO2);                                        //980223
   return true;
}
//_2011-03-26___________________________________________________________________
Crop_parameters_class::Canopy_characteristics_hedge_row::Canopy_characteristics_hedge_row()
{  initial_width                =1.0;                                            //040715
   final_width                  =1.0;                                            //040715
   initial_breadth              =2.0;                                            //071116
   final_breadth                =2.0;                                            //071116
   initial_height               =1.2;                                            //040715
   final_height                 =1.2;                                            //040715
   branch_insertion_height      =0.6;                                            //071116
}
//_2002-04-08___________________________________________________________________
Crop_parameters_class::Tolerance::Tolerance()
{  enabled                           =false;                                     //021016
   temperature_cold_leaf_damage     = -5;
   temperature_cold_leaf_lethal     =-10;
   temperature_cold_fruit_damage    = -5;                                        //081126
   temperature_cold_fruit_lethal    =-10;                                        //081126
   temperature_heat_tuber_critical  = 17;                                        //081109
}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters_class::Tolerance::setup_structure
(Data_record &record,bool for_write,Harvested_part harvested_part) modification_
{  record.set_current_section(LABEL_hardiness);                                  //000330
   record.expect_bool(LABEL_enabled,enabled);                                    //021015
   if ((harvested_part == tuber_part) || !for_write)
      record.expect_float32("tuber_crit_temperature",temperature_heat_tuber_critical);//081108
      // the remaining parameters are setup in the derived classes
   return true;	  
}
//_2011-03-25___________________________________________________________________
Crop_parameters_class::Layout::Layout()
{
   spacing.row =2.7;                                                             //180109
   spacing.col =2.5;                                                             //180109

   /*180109
   row_spacing  =2.7;
   col_spacing  =2.5;
   */
   row_azimuth_true_north_deg=0;
}
//_2002-04-08___________________________________________________________________
bool Crop_parameters_class::get_end()
{  bool ended = Common_parameters_data_record::get_end();                        //170524_161025_020408
#ifndef VIC_CROPSYST
   // Was in V4 but also applicable to V5

   //180702 This should be applicable to all versions


   FOR_EACH_IN(adjustment,Adjustment,adjustments,each_adj)
   {  if (adjustment->parameter==LABEL_max_water_uptake)
         has_max_water_uptake_adjustments = true;
   } FOR_EACH_END(each_adj)
#endif
   //170524 return Common_parameters_data_record::get_end();                              //161025_020408
   return ended;
}
//_2012-07-25_________________________________________________________get_end__/

float64 Crop_parameters_class::param_max_water_uptake_m
(Normal_crop_event_sequence growth_stage)                                  const
{  float64 max_water_uptake_mm = ref_transpiration().normal_max_water_uptake_mm; //120724
   if ((crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)
      && !has_max_water_uptake_adjustments)                                      //120724
   {
      const Crop_parameters_struct::Fruit &fruit = ref_fruit();
      switch (growth_stage)
      {
         case NGS_FILLING        : max_water_uptake_mm  = fruit.max_water_uptake_during_initial_fruit_mm;break;
         case FGS_RAPID_FRUIT_DEVELOPMENT : max_water_uptake_mm  = fruit.max_water_uptake_during_radid_fruit_mm;  break;
         case FGS_VERAISON       : max_water_uptake_mm  = fruit.max_water_uptake_during_veraison_mm;     break;
         case NGS_MATURITY       :
         case NGS_HARVESTABLE    :
         case NGS_HARVEST        : max_water_uptake_mm  = fruit.max_water_uptake_after_maturity_mm;      break;
         case NGS_GERMINATION    :
         case NGS_EMERGENCE      :
         case NGS_RESTART        : // or FGS_BUD_BREAK

         case NGS_ACTIVE_GROWTH  :
         case NGS_ANTHESIS       :
         default                 : max_water_uptake_mm  = fruit.max_water_uptake_before_fruiting_mm;     break;
      }
   }
   return mm_to_m(max_water_uptake_mm);
}    // mm/day

//_1998-12-03___________________________________________________________________
} //namespace CropSyst

