#include "crop_param_V4.h"
#include "static_phrases.h"
#include "corn/math/compare.hpp"
#include "corn/data_source/datarec.h"
#define  LABEL_light_to_biomass        "light_to_biomass"
#include "static_phrases.h"

#ifdef LADSS_MODE
extern bool LADSS_mode;                                                          //021220
#endif

// #ifndef VIC_CROPSYST
namespace CropSyst {                                                             //140318
//______________________________________________________________________________
/* temporarily moved to Crop_parameters_class until I have implemented
 * parameter adjustments idiom

bool Crop_parameters::Adjustment::
setup_structure(CORN::Data_record &data_rec,bool for_write)
{  data_rec.expect_string("parameter",parameter,255);
   data_rec.expect_string("value",value,255);
//moved    data_rec.expect_bool("enabled",enabled);                                      //130425
   return true;
}
//#endif
//______________________________________________________________________________
const char *Crop_parameters::Adjustment_event::label_cstr_deprecated(char *buffer) const  replace this with label_string
{
   std::string label;
   begin_sync.append_to_string(label _ISO_FORMAT_DATE_TIME);                                           //140616
   label += ":";
   label += parameter;
   label += "=";
   label += value;
   strcpy(buffer,label.c_str());
   return buffer;
}
//_2013-04-23___________________________________________________________________
const char *Crop_parameters::Adjustment_event::label_string(std::string &buffer) const  replace this with label_string
{

   begin_sync.append_to_string(buffer _ISO_FORMAT_DATE_TIME);                                           //140616
   buffer += ":"
      + parameter
      + "="
      + value;
   return buffer.c_str;
}
//_2017-04-23___________________________________________________________________

DECLARE_CONTAINER_ENUMERATED_SECTION(Crop_parameters::Adjustment_event, adjustment_section_VV,true);
*/
//______________________________________________________________________________
Crop_parameters::Thermal_time::Thermal_time()
: Crop_parameters_class::Thermal_time()
, resolution_labeled_deprecatedX(resolution_deprecatedX,DAILY)
//, resolution_labeled_deprecated(thermal_response,linear)
// This should allow old thermal time resolution to map to the new thermal response option 151109

,v_base_temperature                    (base_temperature                   ,UC_Celcius                ,LABEL_base_temp                 ,2 ,   3.0  , 0.0,10.0,  0.0,15.0      ,TU_degrees_C,TL_Base_temperature)
,v_cutoff_temperature                  (cutoff_temperature                 ,UC_Celcius                ,LABEL_cutoff_temp               ,2 ,  22.0  , 20.0,30.0,  0.0,40.0  ,TU_degrees_C,TL_Cutoff_temperature)
,v_opt_temperature                     (opt_temperature                    ,UC_Celcius                ,LABEL_optimal_temp                  ,2 ,  22.0  , 20.0,30.0,  0.0,40.0     ,TU_degrees_C,"Optimal temperature")
,v_max_temperature                     (max_temperature                    ,UC_Celcius                ,LABEL_maximum_temp                  ,2 ,  35.0  , 20.0,35.0,  0.0,40.0     ,TU_degrees_C,"Maximum temperature")
{ }
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Thermal_time::setup_structure
(Data_record &record,bool for_write)                               modification_
{
   bool satup = Crop_parameters_class::Thermal_time::setup_structure(record, for_write);
   record.set_current_section("phenology"); // Note in V5 this is moved to thermal_time
   if (!for_write)                                                               //171010
      record.expect_enum("resolution",resolution_labeled_deprecatedX);            //151109

   record.expect_valid_float32(v_base_temperature);
   record.expect_valid_float32(v_cutoff_temperature);
   record.expect_valid_float32(v_opt_temperature);
   record.expect_valid_float32(v_max_temperature);
//NYN   if (!for_write)    record.expect_valid_float32(v_opt_temperature_deprecated); //151207
   return true;
}
//_2010-05-13___________________________________________________________________
Crop_parameters::Phenology::Phenology()
: Crop_parameters_class::Phenology()
, v_emergence_deg_day                   (initiation.emergence     ,UC_Celcius_degree_days ,LABEL_emergence                  ,0  , 100    ,0,300, 0,MAXSHORT,"�C-days",TL_Emergence)
, v_tuber_initiation_deg_day            (initiation.tuber         ,UC_Celcius_degree_days ,LABEL_tuber_init                   ,0,1000    ,0,1000, 0,MAXSHORT,"�C-days",TL_Tuber_initiation)
, v_end_canopy_growth_deg_day           (culmination.accrescence  ,UC_Celcius_degree_days ,LABEL_peak_LAI                    ,0 ,1040    ,300,1500, 0,MAXSHORT,"�C-days","End canopy growth" ) // was LAI Peak
, v_max_root_depth_deg_day              (culmination.root_depth   ,UC_Celcius_degree_days ,LABEL_max_root_depth               ,0,1040    ,300,1500, 0,MAXSHORT,"�C-days","Maximum root depth")
, v_begin_flowering_deg_day             (initiation.flowering     ,UC_Celcius_degree_days ,LABEL_flowering                    ,0,1000    ,300,1500, 1,MAXSHORT,"�C-days",TL_Begin_flowering)
, v_begin_filling_deg_day               (initiation.filling       ,UC_Celcius_degree_days ,LABEL_filling                      ,0,1020    ,300,1500, 0,MAXSHORT,"�C-days","Begin filling (seed filling, or orchard fruit filling, or tuber bulking)" /*TL_Begin_grain_filling*/)
, v_begin_maturity_deg_day              (initiation.maturity      ,UC_Celcius_degree_days ,LABEL_maturity                  ,0 ,1500    ,1000,2500, 0,MAXSHORT,"�C-days",TL_Physiological_maturity)
, v_begin_senescence_deg_day            (initiation.senescence    ,UC_Celcius_degree_days ,"senescence" ,0                  ,1080.0    ,300.0,1500.0, 0.0,99999.9,"�C-days","Begin senescence (thermal time)" )  //080724
, v_full_senescence_deg_day             (culmination.senescence   ,UC_Celcius_degree_days ,"full_senescence" ,0             ,1501.0    ,1000.0,2500.0, 0.0,99999.9,"�C-days","Full senescence (thermal time)" )  //131024
//, v_begin_rapid_fruit_growth_deg_day    (culmination.filling      ,UC_Celcius_degree_days ,LABEL_rapid_fruit_growth        ,0 ,1300    ,1000,2500, 0,MAXSHORT,"�C-days","Begin rapid fruit growth")
, v_begin_rapid_fruit_growth_deg_day    (initiation.rapid_fruit_growth      ,UC_Celcius_degree_days ,LABEL_rapid_fruit_growth        ,0 ,1300    ,1000,2500, 0,MAXSHORT,"�C-days","Begin rapid fruit growth")
, v_WUE_change_deg_day                  (WUE_change               ,UC_Celcius_degree_days ,"WUE_change"                    ,0 ,1000    ,   0,3000, 0,MAXSHORT,"�C-days","Thermal time for change of water use efficiency")
, v_phenologic_sensitivity_water_stress (phenologic_sensitivity_water_stress        ,U_units_not_specified     ,LABEL_water_stress_sensitivity  ,2 ,1.0     , 0.0,1.0,  0.0,1.0 ,TU_0_1,"Adjustment factor for phenologic response to stress")
{ }
//_2008-07-22_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Phenology::setup_structure
(Data_record &record,bool for_write)                               modification_
{  bool satup = Crop_parameters_class::Phenology::setup_structure(record,for_write);//020408
   record.expect_valid_float32(v_emergence_deg_day);
   record.expect_valid_float32(v_begin_flowering_deg_day);
   record.expect_valid_float32(v_end_canopy_growth_deg_day);                     //071121
   record.expect_valid_float32(v_begin_filling_deg_day);
   record.expect_valid_float32(v_begin_maturity_deg_day);                        //050628
   record.expect_valid_float32(v_phenologic_sensitivity_water_stress);
   record.expect_valid_float32(v_WUE_change_deg_day);                            //080514
   record.expect_valid_float32(v_begin_senescence_deg_day);
   record.expect_valid_float32(v_full_senescence_deg_day);
//NYI   if (TUBER_ROOT_OR_UNKNOWN || !for_write)
      record.expect_valid_float32(v_tuber_initiation_deg_day);
//NYI    if (!CROPSYST_FRUIT || UNKNOWN|| !for_write)                // I need to restore not writing when not these special crop types
      record.expect_valid_float32(v_max_root_depth_deg_day);                     //070321
//NYI    if (CROPSYST_FRUIT_OR_UNKNOWN|| !for_write)                             //020405
      record.expect_valid_float32(v_begin_rapid_fruit_growth_deg_day);           //050719
   return satup;	  
}
//_2010-05-13___________________________________________________________________
Crop_parameters::Vernalization::Vernalization()
: Crop_parameters_class::Vernalization()
,v_low_temp   (low_temp  ,UC_Celcius            ,LABEL_low_temp  ,2, 3.0,-4.0,6.0,  -10.0, 10.0,TU_degrees_C,TL_Low_temp_for_opt_vern)
,v_high_temp  (high_temp ,UC_Celcius            ,LABEL_high_temp ,2,10.0, 5.0,15.0,   0.0, 20.0,TU_degrees_C,TL_High_temp_for_opt_vern)
,v_start      (start     ,UC_Celcius_degree_days,LABEL_start     ,2,10.0, 0.0,30.0,   0.0, 50.0,"�C-days",TL_Day_requirement_to_start) // 0 - vernReq C
,v_end        (end       ,UC_Celcius_degree_days,LABEL_end       ,2,50.0,30.0,80.0,   0.0,100.0,"�C-days",TL_Day_requirement_to_complete)
,v_min_factor (min_factor,UC_factor             ,LABEL_min_factor,2, 0.0, 0.0, 1.0,   0.0,  1.0,TU_0_1,TL_Min_vernalization_factor)
{}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Vernalization::setup_structure(Data_record &record,bool for_write)    modification_
{  bool satup = Crop_parameters_class::Vernalization::setup_structure(record,for_write);      //020408
   record.expect_valid_float32(v_low_temp);
   record.expect_valid_float32(v_high_temp);
   record.expect_valid_float32(v_start);
   record.expect_valid_float32(v_end);
   record.expect_valid_float32(v_min_factor);
   return satup;
}
//_2010-05-13___________________________________________________________________
Crop_parameters::Photoperiod::Photoperiod()
: Crop_parameters_class::Photoperiod()                                           //100512
,v_stop        (stop_day_length           ,UT_hour,"stop"         ,2,0.0, 0.0,24.0, 0.0,24.0 ,TL_hours,"development is stopped"        ,TL_Day_length_photo_period/*,"For short day crops this must be greater than the unconstrained value, for long day crops it must be less."*/)
,v_unconstrain (unconstrained_day_length  ,UT_hour,"unconstrain"  ,2,0.0, 0.0,24.0, 0.0,24.0 ,TL_hours,"development is not constrained",TL_Day_length_photo_period/*,"For short day crops this must be less than the stopped value, for long day crops it must be greater."*/)
{}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Photoperiod::setup_structure
(Data_record &record,bool for_write)                       modification_
{  bool satup = Crop_parameters_class::Photoperiod::setup_structure(record,for_write);        //020408
   record.expect_valid_float32(v_unconstrain);                                   //100513
   record.expect_valid_float32(v_stop);                                          //100513
   return satup;
}
//_2010-05-13___________________________________________________________________
Crop_parameters::Emergence_hydro_thermal::Emergence_hydro_thermal()
: Crop_parameters_class::Emergence_hydro_thermal()                               //100520
, v_seedling_leaf_area           (seedling_leaf_area_cm2          ,UC_square_cm_area,"seedling_leaf_area"            ,2, 2    ,0.01,10.0,0.0,20.0, "cm�"       ,"Leaf area of seedling","on first day of emergence")
, v_germination_base_temperature (germination_base_temperature    ,UC_Celcius       ,"germination_base_temperature"  ,1,-1    ,-5,5,-10,20,        TU_degrees_C,"Germination base temperature")    // degress 0
, v_mean_base_soil_water_pot     (mean_base_soil_water_pot_J_kg   ,UC_J_kg          ,"mean_base_soil_water_pot"      ,1,-1000 ,-3000,0,-4000,0,    "J/kg"      ,"Mean base soil water potential for 50% emergence")
, v_stdev_base_soil_water_pot    (stdev_base_soil_water_pot_J_kg  ,UC_J_kg          ,"stdev_base_soil_water_pot"     ,1,100   ,0,1000,0,1000,      "J/kg"      ,"Std deviation base soil water potential","?for 50% emergence?")
, v_a                            (a_slope                         ,UC_unitless      ,"a"                             ,2,22.35 ,-100,100,-1000,1000,"-"         ,"a slope? for hydrothermal time constant curve","Emperical constant")
, v_b                            (b_intercept                     ,UC_unitless      ,"b"                             ,2,129.66,-500,500,-1000,1000,"-"         ,"b intercept? for hydrothermal time constant curve","Emperical constant")
{ }
//_2004-12-01_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Emergence_hydro_thermal::setup_structure
(Data_record &record,bool for_write)      modification_
{
   bool satup = Crop_parameters_class::Emergence_hydro_thermal::setup_structure(record,for_write);
   record.expect_valid_float32(v_a);                              // Emperical constant for computing  hydrothermal time //041203
   record.expect_valid_float32(v_b);                              // Emperical constant for computing  hydrothermal time //041203
   record.expect_valid_float32(v_seedling_leaf_area);             // leaf area of seedling on first day of emergence in cm2 degress 0 //041201
   record.expect_valid_float32(v_mean_base_soil_water_pot);       // J/kg Mean base soil water potential (50% emergence) //041201
   record.expect_valid_float32(v_stdev_base_soil_water_pot);      // J/kg Std deviation base soil water potential (?for 50% emergence?) //041201
   return satup;
}
//_2010-05-20___________________________________________________________________
Crop_parameters::Transpiration::Transpiration()
: Crop_parameters_class::Transpiration()
, v_ET_coef                (ET_coef                      ,U_units_not_specified  ,LABEL_ET_crop_coef                          ,2,1.0, 0.8,1.4,  0.5,2.0,TU_0_8_1_4,TL_ET_crop_coefficient_at_full_canopy)
, v_max_water_uptake       (normal_max_water_uptake_mm   ,UC_mm_per_day          ,LABEL_max_water_uptake                      ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,TL_Maximum_water_uptake)  //040726
, v_LWP_stomatal_closure   (LWP_stomatal_closure         ,UC_J_kg                ,LABEL_stomatal_closure_leaf_water_pot       ,2,-1000.0,-2000,-500.0,  -3000.0,0.0 ,"J/kg"/*171029 TU__J_kg*/,TL_Critical_leaf_water_potential)
, v_LWP_wilt_point         (LWP_wilt_point               ,UC_J_kg                ,LABEL_wilt_leaf_water_pot                   ,2,-1600.0,-3000,-1100,-3500.0,-800.0,"J/kg"/*171029 TU__J_kg*/,TL_Wilting_leaf_water_potential)
{}
//_2011-02-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Transpiration::setup_structure(Data_record &record,bool for_write)    modification_
{
   bool satup = Crop_parameters_class::Transpiration::setup_structure(record,for_write);
   // [transpiration]
   //110528 moved to morphology   record.expect_valid_float32(v_kc);   //Extinction coefficient for solar radiation
   record.expect_valid_float32(v_ET_coef);
   record.expect_valid_float32(v_max_water_uptake);
   record.expect_valid_float32(v_LWP_stomatal_closure); // leaf water pot at onset of stomatal closure
   record.expect_valid_float32(v_LWP_wilt_point);
#ifdef LADSS_MODE
   if (LADSS_mode)                                                               //021220
      record.expect_float32(LABEL_critical_leaf_water_pot_obs,LWP_stomatal_closure); // for LADSS //021220
#endif
   return satup;
}
//_2011-02-08___________________________________________________________________
Crop_parameters::Biomass_production::Biomass_production()
: Crop_parameters_class::Biomass_production()
, v_season_biomass_adjustment_2(season_biomass_adjustment[2],UC_adjustment,"season2_adj"  ,2,1.0,0.0,1.0,0.0,1.0,"multiplier","Season 2","attainable biomass growth adjustment") //080731
, v_season_biomass_adjustment_3(season_biomass_adjustment[3],UC_adjustment,"season3_adj"  ,2,1.0,0.0,1.0,0.0,1.0,"multiplier","Season 3","attainable biomass growth adjustment") //080731
, v_season_biomass_adjustment_4(season_biomass_adjustment[4],UC_adjustment,"season4_adj"  ,2,1.0,0.0,1.0,0.0,1.0,"multiplier","Season 4","attainable biomass growth adjustment") //080731
, v_season_biomass_adjustment_5(season_biomass_adjustment[5],UC_adjustment,"season5_adj"  ,2,1.0,0.0,1.0,0.0,1.0,"multiplier","Season 5 and all following seasons","attainable biomass growth adjustment") //080731
, v_TUE_at_1kPa_VPD                        (TUE_at_1kPa_VPD                       [0],UC_g_per_kg,"TUE_at_1pKa_VPD"  ,2,5.0,3.0,10.0,0.0,10.0,"g BM/kg H2O","Transpiration Use Efficiency when VPD is at 1kPa","when VPD is at 1kPa") //080428
, v_TUE_at_1kPa_VPD_vegetative             (TUE_at_1kPa_VPD                       [1],UC_g_per_kg,"TUE_at_1pKa_VPD_veg"  ,2,5.0,3.0,10.0,0.0,10.0,"g BM/kg H2O","Transpiration Use Efficiency when VPD is at 1kPa","when VPD is at 1kPa") //080428
, v_TUE_scaling_coef                       (TUE_scaling_coef                      [0],UC_coefficient,"TUE_scaling_coef"      ,2,0.45,0.0,6.0, 0.0,10.0,"-","Scaling coefficient of TUE regression (power function)")
, v_TUE_scaling_coef_vegetative            (TUE_scaling_coef                      [1],UC_coefficient,"TUE_scaling_coef_veg"      ,2,0.45,0.0,6.0, 0.0,10.0,"-","Scaling coefficient of TUE regression (power function)") //091201
, v_water_productivity                     (water_productivity                    [0],UC_g_per_kg,"water_productivity"  ,2,5.0,3.0,10.0,0.0,10.0,"g BM/kg H2O","Water productivity","FAO AquaCrop water productivity during reproductive growth (or throughout the season depending on the WUE mode)") //080428
, v_water_productivity_vegetative          (water_productivity                    [1],UC_g_per_kg,"water_productivity_veg"  ,2,5.0,3.0,10.0,0.0,10.0,"g BM/kg H2O","Water productivity","as in AquaCrop") //080428
, v_biomass_transpiration_coef             (reference_biomass_transpiration_coef  [0],UC_pascal_pressure ,"biomass_transpiration_coef"           ,2,5,    1.0,15.0,  1.0,20.0 ,"Pa" /*080406 TU_kPa_kg_m3*/,"Above ground biomass transpiration coefficient (K) for annuals" /*TL_Biomass_transpiration_coefficient*/,"annual") //040729
, v_biomass_transpiration_coef_vegetative  (reference_biomass_transpiration_coef  [1],UC_pascal_pressure ,"biomass_transpiration_coef_veg"           ,2,5,    1.0,15.0,  1.0,20.0 ,"Pa" /*080406 TU_kPa_kg_m3*/,"Above ground biomass transpiration coefficient (K) for annuals" /*TL_Biomass_transpiration_coefficient*/,"annual") //040729
, v_RUE_global(RUE_global         ,UC_g_MJ    ,"RUE_global"          ,2,2.0,1.0, 7.0,  0.0,7.0,"g/MJ","Total radiation basis RUE"/*,"about twice RUE PAR basis"*/) //110825
, v_RUE_PAR_deprecated  (RUE_PAR_deprecated       ,UC_g_MJ    ,"RUE_PAR"            ,2,1.0,0.5, 7.0,  0.0,7.0,"g/MJ","Photosynthetically Active Radiation (PAR) basis"/*,"about half total radiation basis"*/) //110825
//170523obs, v_early_growth_limit_temp                  (early_growth_limit_temp_V4                ,UC_Celcius             ,LABEL_early_growth_limit_temp                    ,2,10.0,    0.0,25.0,  0.0,30.0 ,TU_degrees_C,"Mean daily temperature that limits early growth" /*080725 TL_Optimum_mean_daily_temperature_for_growth*/) //990228
,v_min_tolerable_temp         (min_tolerable_temp       ,UC_Celcius,"min_tolerable_temp"       ,1, 3.0, 0.0,10.0, 0.0,15.0,TU_degrees_C,"Minimum tolerable temperature")         //130531
,v_max_tolerable_temp         (max_tolerable_temp       ,UC_Celcius,"max_tolerable_temp"       ,1,45.0,40.0,50.0,30.0,55.0,TU_degrees_C,"Maximum tolerable temperature")          //130508
,v_low_threshold_limit_temp   (low_threshold_limit_temp ,UC_Celcius,"low_threshold_limit_temp" ,1,10.0, 8.0,14.0, 5.0,20.0,TU_degrees_C,"Low threshold limitation temperature")   //130508
,v_high_threshold_limit_temp  (high_threshold_limit_temp,UC_Celcius,"high_threshold_limit_temp",1,25.0,20.0,30.0,15.0,35.0,TU_degrees_C,"High threshold limitation temperature")  //130508
/*151122 moved to Crop_parameters_class::Biomass_production() because I have this for YAML, but it may be obsolete, need here need to check with Claudio if obsolete
#if (CROPSYST_VERSION==4)
, RUE_basis_cowl   (RUE_basis,unspecified_RUE_basis)                             //080728
#endif
*/
{
//170523obs   early_growth_limit_temp_V4_check_obsolete       = 0.0;  // 10.0;                                //130513_080726
      // the default used to be 10, but
      // now it is 0 which disables this for newly created parameter files

}
//_2011-02-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Biomass_production::setup_structure(Data_record &record,bool for_write)    modification_
{
   bool satup = Crop_parameters_class::Biomass_production::setup_structure(record,for_write);
   /*151122 moved to Crop_parameters_class::Biomass_production() because I have this for YAML, but it may be obsolete, need here need to check with Claudio if obsolete
   #if (CROPSYST_VERSION==4)
   record.expect_enum("RUE_basis",RUE_basis_cowl);                               //110825
   #endif
   */
   #if (CROPSYST_VERSION==4)
   if (!for_write)
      record.expect_enum("max_RUE_mode",RUE_basis_cowl);                         //080801
         // renamed, was max_RUE_mode
   #endif
   record.expect_valid_float32(v_TUE_scaling_coef);                              //080505
   record.expect_valid_float32(v_TUE_scaling_coef_vegetative);                   //110224
   {
      record.expect_valid_float32(v_TUE_at_1kPa_VPD);                            //080506
      record.expect_valid_float32(v_TUE_at_1kPa_VPD_vegetative);                 //080506
   }
   {
      record.expect_valid_float32(v_water_productivity);                         //080506
      record.expect_valid_float32(v_water_productivity_vegetative);              //080506
   }
   record.expect_valid_float32(v_RUE_global);                                    //040428
   record.expect_valid_float32(v_RUE_PAR_deprecated);                            //040428
   {
      record.expect_valid_float32(v_biomass_transpiration_coef);                 //040729
      record.expect_valid_float32(v_biomass_transpiration_coef_vegetative);      //040729
   }
   // NYI if (NOT_ANY_FRUIT_OR_UNKNOWN)                                                 //020405
   {
      /*170523 obsolete
      if (!for_write) // This parameter was renamed                              //080725
         record.expect_float32(LABEL_opt_temp_for_growth_obs,early_growth_limit_temp_V4_check_obsolete);  //080725
      record.expect_valid_float32(v_early_growth_limit_temp );
      */
      record.expect_valid_float32(v_min_tolerable_temp);                         //130531
      record.expect_valid_float32(v_max_tolerable_temp);                         //130509
      record.expect_valid_float32(v_low_threshold_limit_temp);
      record.expect_valid_float32(v_high_threshold_limit_temp);
   }
   return satup;
}
//_2011-02-08___________________________________________________________________
Crop_parameters::Quiescence::Quiescence()
: Crop_parameters_class::Quiescence()
, v_consider_inactive_days  (consider_inactive_days             ,"consider_inactive_days"      , 7,  0,100, 0,365,"days"      ,"at end or restart of growth activity")
, v_inducement_temperature  (inducement_temperature ,UC_Celcius ,LABEL_inducement_temperature,2,10,-10,25,-30,30 ,TU_degrees_C, "Average temperature over these consecutive days below which inactivity is induced" /*080401 obs TL_Average_temperature_to_induce_dormancy*/)  // 970521P
{
/*180601 Claudio says obsolete but dont delete yet
   #if (CS_VERSION==4)
   // In V4 I used date because I wanted to use the calendar control in the UI.
   start_valid_date.clear(); //180822 set_YD((Year)0,(CORN::DOY)365); //  this default should disable
   leave_valid_date.clear(); //180822 set_YD((Year)0,(CORN::DOY)365); //  this default should disable
   #endif
*/
}
//_2008-04-01_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Quiescence::setup_structure(Data_record &record,bool for_write)    modification_
{  bool satup = Crop_parameters_class::Quiescence::setup_structure(record,for_write);
   record.expect_valid_int16   (v_consider_inactive_days);                       //080401
   record.expect_valid_float32 (v_inducement_temperature);                       //080401

/*180601 Claudio says obsolete but dont delete yet

   #if (CS_VERSION==4)
   record.expect_int32       ("start_valid_date",start_valid_date.mod_date32()); //170525_080401
   record.expect_int32       ("end_valid_date"  ,leave_valid_date.mod_date32()); //170525_080401
   #else
   #if (CS_VERSION<6)
   if (!for_write)
   {  // support for V4 parameter files.
      record.expect_nat16         ("start_valid_date" ,start_DOY,10);            //170213
      record.expect_nat16         ("end_valid_date"   ,end_DOY,10);              //170213
   }
   #endif
   record.expect_nat16         ("start_DOY" ,start_DOY,10);                      //170213
   record.expect_nat16         ("end_DOY"   ,end_DOY,10);                        //170213
   #endif
      std::clog << " start_DOY:" << start_DOY
             << " end_DOY:" << end_DOY
             << std::endl;
*/
   return satup;
}
//_2010-05-10___________________________________________________________________
Crop_parameters::Dormancy::Dormancy()
:Crop_parameters_class::Dormancy()
,v_chill_hours                         (chill_hours                           ,UT_hour                ,LABEL_chill_requirement     ,1,400, 0,2000,0,3000,"Hours","Chill requirement")  //021202
,v_deg_day_bud_break_chill_req_sat     (deg_day_bud_break_chill_req_sat       ,U_units_not_specified  ,LABEL_deg_day_bud_break_chill_req_sat       ,1,100,0,1000,0,1500,TU_degrees_C,"Thermal time to bud break (Chill requirement satisfied)") //030515
,v_deg_day_bud_break_chill_req_not_sat (deg_day_bud_break_chill_req_not_sat   ,U_units_not_specified  ,LABEL_deg_day_bud_break_chill_req_not_sat   ,1,150,0,1500,0,2000,TU_degrees_C,"Thermal time to bud break (Chill requirement not satisfied)")   //030515
,v_senesce_percent                     (senesce                               ,UC_percent             ,"senesce"                  ,1,100,0,100,0,100,TU_percent,"Biomass that senesces at the onset of dormancy") //060317
{}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Dormancy::setup_structure(Data_record &record,bool for_write)    modification_
{  bool satup = Crop_parameters_class::Dormancy::setup_structure(record,for_write);
   /*140810
   record.expect_bool         ("enabled",dormancy_enabled_obsolete,CROPSYST_VV_BOOL_FORM);   //111013_021015
   */
   record.expect_valid_float32(v_senesce_percent);                               //060317
   record.expect_valid_float32(v_chill_hours);                                   //030515
   record.expect_valid_float32(v_deg_day_bud_break_chill_req_sat);               //030515
   record.expect_valid_float32(v_deg_day_bud_break_chill_req_not_sat);           //030515
   return satup;
}
//_2010-06-10___________________________________________________________________
Crop_parameters::Root::Root()
: Crop_parameters_class::Root()
,v_max_depth                     (max_depth                       ,UC_meter/*_depth*/     ,LABEL_max_root_depth                        ,2, 1.5, 0.1   ,  3.0,0.0  ,   4.0,TU_m,TL_Maximum_rooting_depth)
,v_surface_density               (surface_density                 ,U_units_not_specified  ,LABEL_surface_root_density                  ,2, 6.0, 0.0   , 10.0,0.0  ,  30.0,"cm/cm�","Maximum surface root density at full rooting depth" /*070926 "Surface root density"*/)
,v_density_distribution_curvature(density_distribution_curvature  ,U_units_not_specified  ,LABEL_root_density_distribution_curvature   ,3, 0.1, 0.001,  6.0,0.001,  10.0,"0.0001-6.0","Curvature of root density distribution")
,v_length_per_unit_mass	         (length_per_unit_mass_km_kg_V4      ,UC_km_kg               ,"root_length_per_unit_mass"                 ,2,90.0,70.0   ,110.0,0    ,1000.0,"km/kg","Root length per unit root mass")
,v_sensitivity_to_water_stress   (sensitivity_to_water_stress     ,UC_index               ,"root_sensitivity_water_stress"             ,2, 0.0, 0.0   ,  1.1,0    ,   1.0,"index","Root sensitivity to water stress")
,v_length_at_emergence           (length_at_emergence_cm          ,UC_cm                  ,"root_length_at_emergence"                  ,2, 2.0, 1.0   , 10.0,0    ,  20.0,"cm"   ,"Root length at emergence")
,v_root_shoot_emergence_ratio     (root_shoot_emergence_ratio      ,UC_ratio               ,"root_shoot_emergence_ratio"                ,2,2.0,0.1  ,5.0,0.0,10.0,"ratio","root/shoot (mass) ratio at emergence")
,v_root_shoot_full_ratio          (root_shoot_full_ratio           ,UC_ratio               ,"root_shoot_full_ratio"                     ,2,0.1,0.001,1.0,0.0,1.0 ,"ratio","root/shoot (mass) ratio at full extent")
{}
//_2006-12-12_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Root::setup_structure(Data_record &record,bool for_write)    modification_
{  bool satup = Crop_parameters_class::Root::setup_structure(record,for_write);
   record.expect_valid_float32(v_sensitivity_to_water_stress);                   //061212
   record.expect_valid_float32(v_max_depth);
   record.expect_valid_float32(v_surface_density);                               //030722
   record.expect_valid_float32(v_density_distribution_curvature);                //030722
   record.expect_valid_float32(v_length_per_unit_mass);                          //060612
   record.expect_valid_float32(v_length_at_emergence);                           //110224 restored for compatibility with VIC

   record.expect_valid_float32(v_root_shoot_emergence_ratio);                    //130624
   record.expect_valid_float32(v_root_shoot_full_ratio);                         //130624

      // Prior to version 4.06.03 root parameters were under morphology
      // Starting version 5 we will no longer import.
      // Morphology
   record.set_current_section(LABEL_morphology);                                 //020508
   if (!for_write) // only allow importing                                       //061212
   {                                                                             //061212
      record.expect_valid_float32(v_max_depth);
      record.expect_valid_float32(v_surface_density);                            //030722
      record.expect_valid_float32(v_density_distribution_curvature);             //030722
      record.expect_valid_float32(v_length_per_unit_mass);                       //060612
   }
   record.set_current_section("root");                                           //061212
   return satup;
}
//_2010-06-10____________________________________________Root::setup_structure_/
Crop_parameters::Morphology::Morphology()
: Crop_parameters_class::Morphology()
, v_kc                     (kc                           ,U_units_not_specified  ,LABEL_kc                                    ,2,0.5, 0.3,0.8, 0.0,1.0,TU_0_1,"Canopy extinction coefficient for total (global) solar radiation") //110528_990228
, v_reduce_canopy_expansion_LWP(reduce_canopy_expansion_LWP, UC_J_kg,"LWP_reduces_canopy_expansion" ,2,-800.0,-3000.0,0.0,-2000.0,0.0,"J/kg","Leaf water potential that begins reduction of canopy expansion")
, v_stop_canopy_expansion_LWP  (stop_canopy_expansion_LWP  , UC_J_kg,"LWP_stops_canopy_expansion"  ,2,-1200.0,-3000.0,0.0,-2000.0,0.0,"J/kg","Leaf water potential that stops canopy expansion")
, v_max_canopy_height                    (max_canopy_height                  ,UC_meter    ,LABEL_max_canopy_height                     ,2,1.5, 0.1, 3.0, 0.0, 4.0,TU_m,TL_Maximum_plant_height) //040715
{}
//_2011-02-19_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Morphology::setup_structure(Data_record &record,bool for_write)    modification_
{  bool satup = Crop_parameters_class::Morphology::setup_structure(record,for_write);
   record.set_current_section("morphology");
      record.expect_valid_float32(v_max_canopy_height); // Used by LADSS and VIC //030303
   record.set_current_section("growth");
      record.expect_valid_float32(v_reduce_canopy_expansion_LWP);                //080506
      record.expect_valid_float32(v_stop_canopy_expansion_LWP);                  //080506
   record.set_current_section("transpiration");                                  //110528 kc used to be under transpiration
      record.expect_valid_float32(v_kc);   //Extinction coefficient for solar radiation
   return satup;
}
//_2011-02-19___________________________________________________________________
Crop_parameters::Canopy_growth_cover_based::Canopy_growth_cover_based()
: Crop_parameters_class::Canopy_growth_cover_based()
, v_canopy_cover_initial      (cover_initial       ,UC_fraction,"initial"           ,2,0.01,0.0001,1.0,0.0001,1.0,"fraction","Initial canopy cover")
, v_canopy_cover_maximum      (cover_maximum_no_CO2_adj,UC_fraction,"maximum"           ,2,0.9 ,0.0001,1.0,0.0001,1.0,"fraction","Maximum canopy cover")
, v_canopy_cover_total_season_end(cover_total_season_end,UC_Celcius_degree_days
   ,"total_season_end" ,2,0.1 ,0.0,1.0,0.0,1.0,"�C-days","Total canopy cover at end of season (green and senesced)") //171219
   //171219 ,"CC_total_mature" ,2,0.1 ,0.0,1.0,0.0,1.0,"fraction","Total canopy cover at maturity (green and senesced)")
, v_relative_thermal_time_at_half_canopy_cover_maximum(fract_season_to_reach_cover_max_half,UC_fraction,"rel_TT_at_half_CC_max",2,0.5025,0.5,1.0,0.0,1.0,"fraction","Relative thermal time at half maximum canopy cover")
{}
//_2008-07-25_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Canopy_growth_cover_based::setup_structure(Data_record &record,bool for_write)    modification_
{  bool satup = Crop_parameters_class::Canopy_growth_cover_based::setup_structure(record,for_write);
      record.expect_valid_float32(v_canopy_cover_initial);                       //080725
      record.expect_valid_float32(v_canopy_cover_maximum);                       //080725
      record.expect_valid_float32(v_canopy_cover_total_season_end);              //171221
      record.expect_valid_float32(v_relative_thermal_time_at_half_canopy_cover_maximum); //080725

   record.expect_float32("green_season_end",cover_green_season_end);             //171219
   record.expect_float32("thermal_time_season_end",thermal_time_season_end /*rename to thermal_time_season_end*/ ); //171219

   record.expect_float32("shape_accrescent",shape_coef_accrescent);       //171221
   record.expect_float32("shape_senescent" ,shape_coef_senescent);        //171221

   // renamed:
   if (!for_write)
   {  record.expect_float32("initial_cover",cover_initial);
      record.expect_float32("CC_total_mature",cover_total_season_end);
      record.expect_float32("CC_initial",cover_initial);                         //171221
      record.expect_float32("CC_maximum",cover_maximum_no_CO2_adj);              //171221
   }
   // full_senescence_green_cover -> cover_green_senescence_full ???
   return satup;
}
//_2010-06-10___________________________________________________________________
Crop_parameters::Canopy_growth_LAI_based::Canopy_growth_LAI_based()
: Crop_parameters_class::Canopy_growth_LAI_based()
, v_initial_GAI          (initial_GAI         ,U_units_not_specified  ,LABEL_initial_GAI                           ,3,0.011, 0.0001,0.1, 0.0001,15.0,TU_m2_m2,"Initial",TL_Initial_green_area_index_LAI) //000207
, v_regrowth_GAI         (regrowth_GAI        ,U_units_not_specified  ,"regrowth_GAI"                              ,3,0.011, 0.0,0.1, 0.0,15.0,TU_m2_m2,"Min. green leaf area index for regrowth (perennial and/or clipped annuals)","When there are clipping events or the crop comes out stress or dormancy conditions.this is the minimal green leaf area index available to restart growth. Applies to perennial and/or clipped annuals")   //080207
, v_max_LAI              (max_LAI             ,U_units_not_specified  ,LABEL_max_LAI                               ,2,5.0, 2.0,10.0, 0.0,15.0,TU_m2_m2,TL_Maximum_leaf_area_index_LAI) //990228
, v_specific_leaf_area   (specific_leaf_area  ,UC_m2_kg               ,LABEL_specific_leaf_area                    ,2,22.0,15.0,30.0,10.0,40.0,TU_m2_kg,TL_Specific_leaf_area)
, v_fract_LAI_mature     (fract_LAI_mature    ,U_units_not_specified  ,LABEL_fract_LAI_mature                      ,2,0.8, 0.0,1.0,  0.0, 1.0,TU_0_1,TL_Fraction_of_max_LAI_at_physiological_maturity,"(green and senesced)")
, v_stem_leaf_partition  (stem_leaf_partition ,U_units_not_specified   ,LABEL_stem_leaf_partition                  ,2,3.0, 1.5,4.0, 0.0,10.0,"0-4",TL_Stem_leaf_partition)
, v_leaf_duration_deg_day                (leaf_duration_deg_day              ,UC_Celcius_degree_days ,LABEL_duration                            ,0,700 ,500,1500, 0,20000,TL_Degree_days,TL_Leaf_area_duration)  // 970521_050628
, v_leaf_duration_sensitivity_stress     (leaf_duration_sensitivity_stress   ,U_units_not_specified  ,LABEL_duration_stress_sensitivity           ,2,1.0,0.0,3.0, 0.0,4.0,TU_0_3,TL_Leaf_area_duration_sensitivity_to_water_stress)
{}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Canopy_growth_LAI_based::setup_structure(Data_record &record,bool for_write)    modification_
{  bool satup = Crop_parameters_class::Canopy_growth_LAI_based::setup_structure(record,for_write);
   record.expect_valid_float32(v_max_LAI); // now for all crops
   //100730 if (NOT_ANY_FRUIT_OR_UNKNOWN)  // not needed for fruit/orchard
   {  record.expect_valid_float32(v_fract_LAI_mature);
   }
   record.expect_valid_float32(v_initial_GAI);                                   //000413
   record.expect_valid_float32(v_regrowth_GAI);                                  //080207
   record.expect_valid_float32(v_specific_leaf_area);
   record.expect_valid_float32(v_stem_leaf_partition);
   record.expect_valid_float32(v_leaf_duration_deg_day);                         //050611
   record.expect_valid_float32(v_leaf_duration_sensitivity_stress);
   return satup;
}
//_2010-06-10___________________________________________________________________
Crop_parameters::Harvest::Harvest()
: Crop_parameters_class::Harvest()
,v_unstressed              (index_unstressed          ,UC_index               ,LABEL_unstressed,2,0.50, 0.0,1.0,  0.0,1.0 ,TU_0_1,TL_Unstress_harvest_index)
,v_growth_sensitivity      (stress_sensitivity_growth        ,U_units_not_specified  ,LABEL_growth_sensitivity,2,0.0, 0.5,1.5,  0.0,2.0 ,"0.5-1.5","Sensitivity to water and nitrogen stress during active growth"/*,"during active growth",TL_Sensitivity_to_water_stress*/) //020419
,v_tuber_init_sensitivity  (stress_sensitivity_tuber_init    ,U_units_not_specified  ,LABEL_tuber_init_sensitivity,2,0.0,  0.5,1.5,  0.0,2.0 ,"0.5-1.5",TL_during_tuber_init,TL_Sensitivity_to_water_stress)
,v_tuber_growth_sensitivity(tuber_growth_sensitivity  ,U_units_not_specified  ,LABEL_tuber_growth_sensitivity,2,0.0,  0.5,1.5,  0.0,2.0 ,"0.5-1.5",TL_during_tuber_growth,TL_Sensitivity_to_water_stress)
,v_translocation_fraction  (translocation_fraction_max,UC_fraction            ,"translocation_max",2,3.0,0.0,1.0,0.0,1.0,"0-1"," Biomass translocation to grain fraction (max)") //110907
,v_cold_stress_no_stress_threshold_temperature  (editor_grain_stress_sensitivity.cold.no_stress_threshold_temperature ,UC_Celcius       ,"cold_stress_no_stress_threshold_temperature"  ,1,-0.5,-10.0,1.0,-20.0,10.0,TU_degrees_C,"No stress threshold temperature")     //130416
,v_cold_stress_max_stress_threshold_temperature (editor_grain_stress_sensitivity.cold.max_stress_threshold_temperature,UC_Celcius       ,"cold_stress_max_stress_threshold_temperature" ,1,-2.0,-10.0,1.0,-20.0,10.0,TU_degrees_C,"Maximum stress threshold temperature")//130416
,v_cold_stress_sensitivity                      (editor_grain_stress_sensitivity.cold.sensitivity                     ,UC_factor        ,"cold_stress_sensitivity"                      ,2, 1.0, 0.0,1.0,0.0,1.0,"0-1","Sensitivity")                                    //130416
,v_cold_stress_exposure_damaging_hours          (editor_grain_stress_sensitivity.cold.exposure_damaging_hours         ,UT_hour          ,"cold_stress_exposure_damaging_hours"          ,1, 4.0, 0.0,12.0,0.0,24.0,"hours","Hours of stress exposure for damage")        //130416
,v_cold_exposure_initial_hour                   (editor_grain_stress_sensitivity.cold.exposure_initial_hour           ,"cold_stress_exposure_initial_hour"            ,0, 10,15,0,23,"hour","Initial hour cold stress exposure is relevent")           //130628

,v_heat_stress_no_stress_threshold_temperature  (editor_grain_stress_sensitivity.heat.no_stress_threshold_temperature ,UC_Celcius       ,"heat_stress_no_stress_threshold_temperature"  ,1,31.0,20.0,50,0.0,55.0,TU_degrees_C,"No stress threshold temperature")         //130416
,v_heat_stress_max_stress_threshold_temperature (editor_grain_stress_sensitivity.heat.max_stress_threshold_temperature,UC_Celcius       ,"heat_stress_max_stress_threshold_temperature" ,1,44.0,20.0,50.0,0.0,55.0,TU_degrees_C,"Maximum stress threshold temperature")  //130416
,v_heat_stress_sensitivity                      (editor_grain_stress_sensitivity.heat.sensitivity                     ,UC_factor        ,"heat_stress_sensitivity"                      ,2, 1.0, 0.0,1.0,0.0,1.0,"0-1","Sensitivity")                                    //130416
,v_heat_stress_exposure_damaging_hours          (editor_grain_stress_sensitivity.heat.exposure_damaging_hours         ,UT_hour         ,"heat_stress_exposure_damaging_hours"          ,1, 4.0, 0.0,12.0,0.0,24.0,"hours","Hours of stress exposure for damage")         //1320416
,v_heat_exposure_initial_hour                   (editor_grain_stress_sensitivity.heat.exposure_initial_hour             ,"heat_stress_exposure_initial_hour"           ,99, 4,12,0,23,"hour","Initial hour heat stress exposure is relevent")           //130628
{}
//_2011-03-25_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Harvest::setup_structure
(Data_record &record,bool for_write,Harvested_part harvested_part) modification_ //171122
{
   record.set_current_section(LABEL_harvest_index);
   bool UNKNOWN = !for_write || (harvested_part == UNKNOWN_PART);                //020715
      record.expect_valid_float32(v_unstressed);
      if ( UNKNOWN  // When reading crop
         ||(harvested_part == root_part)
         ||(harvested_part == tuber_part)
         ||(!for_write))                                                         //051207
      { // Tuber and root crops
         record.expect_valid_float32(v_tuber_init_sensitivity);
         record.expect_valid_float32(v_tuber_growth_sensitivity);
      }
      if ( UNKNOWN  // When reading crop
         ||(harvested_part==grain_part)
         ||(harvested_part==tuber_part)
         ||(!for_write))                                                         //051207
      { // Seed crops
         record.expect_valid_float32(v_translocation_fraction);                  //110907
      }
      if ( UNKNOWN  // When reading crop                                         //020419
         ||(harvested_part == leaf_part )
         ||(!for_write)  )                                                       //051207
      { // leaf and crops
         record.expect_valid_float32(v_growth_sensitivity);
      }
      record.expect_bool("adjust_HI",apply_adjustment_to_unstressed_harvest_index); //110913
      record.expect_bool("heat_extreme",apply_heat_extreme_adjustment_to_unstressed_harvest_index); //150206
   return true;
}
//_2002-04-05___________________________________________________________________
Crop_parameters::Crop_parameters
(bool nitrogen_simulation
,bool salinity_simulation
,bool residue_simulation
,bool CO2_simulation)
: Crop_parameters_class()
, thermal_time()
, phenology()
, canopy_growth_LAI_based()
, canopy_growth_cover_based()
, root()
, quiescence()                                                                   //160326
, dormancy()
, tolerance              ()
, residue_decomposition  ()
#ifdef CROPSYST
, vernalization          ()
, photoperiod            ()
, emergence()
, salinity               ()
, layout                 ()
#endif
, harvest                ()
, fruit()
, nitrogen               ()
, canopy_characteristics_hedge_row()
, CO2_response           ()
, cropgro                ()
, reference_light_to_biomass_kg_MJ_old(0.0)
      // non zero values will indicate we are reading old parameter files.       //110908
,deciduous_obsolete              (false)                                                   //040517 110603 was true
,senesced_biomass_fate_labeled_obsolete(senesced_biomass_shed)  // note that this will be incompatible with previous version (for perennials) //060817_
, v_linger_days(linger_days,/*UC_days*/"linger" ,90,0,365,0,9999,"days","Time that senesced leaves linger with the plant")  // Warning need default and ranges
{}
//_2001-01-09_____________________________________________________constructor__/
void Crop_parameters::initialize_fallow()
{
   Crop_parameters::initialize_fallow();
#ifdef OLD_ROOTS
   max_root_depth                   =0.001;
#endif
   reference_light_to_biomass_kg_MJ_old = 0.003;                                 //080428
   //170524obs biomass_production.early_growth_limit_temp_V4          = 10.0;                   //130513_080726
}
//_1999-02-17_______________________________________________initialize_fallow__/
/*180626 format upgrade now handled externally.
#define CROP_PARAMETER_CHANGE_COUNT   79
Section_entry_change crop_parameter_changes[CROP_PARAMETER_CHANGE_COUNT] =
{
// NC indicates no change yet.
//NC   {LABEL_crop,LABEL_description,LABEL_crop,LABEL_description}

   {CHANGE_V4,LABEL_crop,LABEL_class_obs,LABEL_crop,LABEL_harvested_part}
//NC,  {LABEL_crop,LABEL_C_species,
//NC,  {LABEL_crop,LABEL_perennial,
//NC,  {LABEL_crop,LABEL_land_use

//NC,  {LABEL_crop,LABEL_vernalization,  obsolete?
//NC,  {LABEL_crop,LABEL_photoperiod,    obsolete?
//NC,  {LABEL_crop,LABEL_stages,         obsolete
// Version 4 New section [growth]
,   {CHANGE_V4,LABEL_crop,LABEL_light_to_biomass             ,LABEL_growth,LABEL_light_to_biomass}
,   {CHANGE_V4,LABEL_crop,LABEL_at_pt_limit                  ,LABEL_growth,LABEL_at_pt_limit}
// Version 4 New section [transpiration]
,   {CHANGE_V4,LABEL_crop,LABEL_kc                           ,LABEL_transpiration,LABEL_kc}
,   {CHANGE_V4,LABEL_crop,LABEL_ET_crop_coef                 ,LABEL_transpiration,LABEL_ET_crop_coef}
,   {CHANGE_V4,LABEL_crop,LABEL_max_water_uptake             ,LABEL_transpiration,LABEL_max_water_uptake}
,   {CHANGE_V4,LABEL_crop,LABEL_critical_leaf_water_pot_obs  ,LABEL_transpiration,LABEL_stomatal_closure_leaf_water_pot}
,   {CHANGE_V4,LABEL_crop,LABEL_wilt_leaf_water_pot          ,LABEL_transpiration,LABEL_wilt_leaf_water_pot}
// Version 4 New section [leaf]
,   {CHANGE_V4,LABEL_crop,LABEL_max_LAI                   ,LABEL_leaf,LABEL_max_LAI}
,   {CHANGE_V4,LABEL_crop,LABEL_fract_LAI_mature          ,LABEL_leaf,LABEL_fract_LAI_mature}
,   {CHANGE_V4,LABEL_crop,LABEL_initial_GAI               ,LABEL_leaf,LABEL_initial_GAI}
,   {CHANGE_V4,LABEL_crop,LABEL_specific_leaf_area        ,LABEL_leaf,LABEL_specific_leaf_area}
,   {CHANGE_V4,LABEL_crop,LABEL_stem_leaf_partition       ,LABEL_leaf,LABEL_stem_leaf_partition}
,   {CHANGE_V4,LABEL_crop,LABEL_deg_day_leaf_duration_obs ,LABEL_leaf,LABEL_duration}
,   {CHANGE_V4,LABEL_crop,LABEL_leaf_duration_sensitivity_stress_obs,LABEL_leaf,LABEL_duration_stress_sensitivity}
// Version 4 New section [morphology]
,   {CHANGE_V4,LABEL_crop,LABEL_max_root_depth            ,LABEL_morphology,LABEL_max_root_depth}
,   {CHANGE_V4,LABEL_crop,LABEL_max_canopy_height         ,LABEL_morphology,LABEL_max_canopy_height}
// Version 4 New section [phenology]
,   {CHANGE_V4,LABEL_crop,LABEL_grain_filling_obs                ,LABEL_phenology,LABEL_filling}
,   {CHANGE_V4,LABEL_crop,LABEL_flowering                    ,LABEL_phenology,LABEL_flowers} //021203
// Version 4 New section [residue]
,   {CHANGE_V4,LABEL_crop,LABEL_decomposition_time           ,LABEL_residue,LABEL_decomposition_time}
,   {CHANGE_V4,LABEL_crop,LABEL_residue_area_mass_obs        ,LABEL_residue,LABEL_area_covered_to_mass_ratio}
// Version 4 New section [harvest_index]
,   {CHANGE_V4,LABEL_crop,LABEL_harvest_ndx_unstressed_obs               ,LABEL_harvest_index,LABEL_unstressed}
 // Version 4 New section [fruit]
,   {CHANGE_V4,LABEL_crop,LABEL_fract_total_solids                    ,LABEL_fruit,LABEL_fract_total_solids}
,   {CHANGE_V4,LABEL_crop,LABEL_max_fruit_load                        ,LABEL_fruit,LABEL_max_fruit_load}
,   {CHANGE_V4,LABEL_crop,LABEL_development_fraction_to_fruit_obs     ,LABEL_fruit,LABEL_initial_growth_fraction_to_fruit} //030521
,   {CHANGE_V4,LABEL_crop,LABEL_veraison_fraction_to_fruit_obs        ,LABEL_fruit,LABEL_rapid_growth_fraction_to_fruit}   //030521
 // Version 4 New section [vernalization]
,   {CHANGE_V4,LABEL_crop,LABEL_vernalization_low_temp_obs            ,LABEL_vernalization,LABEL_low_temp}
,   {CHANGE_V4,LABEL_crop,LABEL_vernalization_high_temp_obs           ,LABEL_vernalization,LABEL_high_temp}
,   {CHANGE_V4,LABEL_crop,LABEL_vernalization_start_obs               ,LABEL_vernalization,LABEL_start}
,   {CHANGE_V4,LABEL_crop,LABEL_vernalization_end_obs                 ,LABEL_vernalization,LABEL_end}
,   {CHANGE_V4,LABEL_crop,LABEL_vernalization_min_factor_obs          ,LABEL_vernalization,LABEL_min_factor}
 // LADSS
,   {1,0,0,LABEL_crop,LABEL_v_start                   ,LABEL_vernalization,LABEL_start}   //020610
,   {1,0,0,LABEL_crop,LABEL_v_end                     ,LABEL_vernalization,LABEL_end}     //020610
 // Version 4 New section [photoperiod]
,   {CHANGE_V4,LABEL_crop,LABEL_photoperiod_start_obs                ,LABEL_photoperiod,LABEL_start}
,   {CHANGE_V4,LABEL_crop,LABEL_photoperiod_end_obs                  ,LABEL_photoperiod,LABEL_end}
 // LADSS
,   {1,0,0,LABEL_crop,LABEL_pp_start                                 ,LABEL_photoperiod,LABEL_start}  //020610
,   {1,0,0,LABEL_crop,LABEL_pp_end                                   ,LABEL_photoperiod,LABEL_end} //020610
 // Version 4 New section [salinity]
,  {CHANGE_V4,LABEL_crop,LABEL_osmotic_pot_50                      ,LABEL_salinity,LABEL_osmotic_pot_50}
,   {CHANGE_V4,LABEL_hardiness,LABEL_salvagable_days_LADSS_alias           ,LABEL_hardiness     ,LABEL_salvageable_days_before_maturity}
,   {CHANGE_V4,LABEL_transpiration,LABEL_stomatal_closure_LWP_LADSS_alias  ,LABEL_transpiration ,LABEL_stomatal_closure_leaf_water_pot}   //061025
,   {CHANGE_V4,LABEL_transpiration,LABEL_wilt_LWP                          ,LABEL_transpiration,LABEL_wilt_leaf_water_pot} //061025
,   {CHANGE_V4,LABEL_growth,LABEL_root_density_distr_curv_LADSS_alias      ,LABEL_growth        ,LABEL_root_density_distribution_curvature}  //061025
};
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*/
/*180626 format upgrade now handled externally.
Section_entry_change * Crop_parameters::get_section_entry_changes(uint16 &count) const
{  count = CROP_PARAMETER_CHANGE_COUNT;
   {  // The the file read is the current version, no need to set up changes (return 0 count)
      uint8 option_version[3] = {  CS_VERSION_NUMBERS };
      if ((option_version[0] == data_source_version.major_)
          && (option_version[1] == data_source_version.release_)
          && (option_version[2] == data_source_version.minor_))
          count = 0;
   }
   return crop_parameter_changes;
}
//_2004-05-10_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*/
// This mode is for compatibility with previous versions
// These parameters are deprecated and will be removed in version 5
//#ifdef NYI

//______________________________________________________________________________
bool Crop_parameters::expect_structure(bool for_write)
{  bool expected = Crop_parameters_class::expect_structure(for_write);           //161023
   structure_defined = false;                                                    //120314
   set_current_section(LABEL_crop);
   bool UNKNOWN = !for_write || (harvested_part_labeled.get() == UNKNOWN_PART);  //020715
   //NYN bool NOT_ANY_FRUIT_OR_UNKNOWN     =(  !  (harvested_part_labeled.get() == fruit_part) ||UNKNOWN );   //020405
   bool CROPSYST_FRUIT = (crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);   //071121
   bool CROPSYST_FRUIT_OR_UNKNOWN = CROPSYST_FRUIT || UNKNOWN;                   //020715
   if (CROPSYST_FRUIT_OR_UNKNOWN)                                                //020405
      expect_bool(LABEL_deciduous,deciduous_obsolete);                           //020405
   if (!for_write)                                                               //141120
      expect_enum("senesced_biomass_fate",senesced_biomass_fate_labeled_obsolete);           //060817
   expect_valid_int16(v_linger_days);                                            //080910
   if (!for_write)                                                               //111006
   {
      set_current_section("growth");
         expect_float32(LABEL_light_to_biomass,reference_light_to_biomass_kg_MJ_old);      // kg/MJ    (entered as g/kg) Light to above ground biomass conversion. (Radiation use efficiency) //980220P
   }
   if ((!CROPSYST_FRUIT || !for_write))                                          //020405
   {  // Salinity
      set_current_section("salinity");
      expect_valid_float32(salinity.v_osmotic_pot_50);
      expect_valid_float32(salinity.v_salt_tolerance_P);
   }
   if (CROPSYST_FRUIT || !for_write)                                             //020405
   { //  canopy characteristics
      set_current_section(LABEL_canopy_characteristics);
      if ((CROPSYST_FRUIT || !for_write)) // ORCHARD_VINEYARD_MODEL_OR_UNKNOWN)
      {
         expect_valid_float32(canopy_characteristics_hedge_row.v_initial_width);
         expect_valid_float32(canopy_characteristics_hedge_row.v_final_width);
         expect_valid_float32(canopy_characteristics_hedge_row.v_initial_breadth);  // along the row
         expect_valid_float32(canopy_characteristics_hedge_row.v_final_breadth);
         expect_valid_float32(canopy_characteristics_hedge_row.v_initial_height);
         expect_valid_float32(canopy_characteristics_hedge_row.v_final_height);
         expect_valid_float32(canopy_characteristics_hedge_row.v_branch_insertion_height);
      }
      {  // layout
         set_current_section(LABEL_layout);                                      //020405
         expect_valid_float32(layout.v_row_spacing);                             //020405
         expect_valid_float32(layout.v_row_azimuth);                             //020405
         expect_valid_float32(layout.v_col_spacing);                             //020405
      }
   }
   // The following is only for the simple crop model
   canopy_growth_cover_based.setup_structure(*this,for_write);                   //100730
   canopy_growth_LAI_based.setup_structure(*this,for_write);                     //100730
   phenology.setup_structure(*this,for_write);                                   //100611
   thermal_time.setup_structure(*this,for_write);                                //100730
   // The following are actually thermal time accumulation parameters
   // in version 5 we will have a separate section

   root.setup_structure(*this,for_write);                                        //100730
   quiescence.setup_structure(*this,for_write);                                  //160326_100610
   if (CROPSYST_FRUIT || !for_write) // ORCHARD_VINEYARD_MODEL_OR_UNKNOWN        //020418
      dormancy       .setup_structure(*this,for_write);                          //100610
   // Residue
   residue_decomposition.setup_structure(*this,for_write);                       //020408
   if (!CROPSYST_FRUIT)                                                          //110606
   {  vernalization.setup_structure(*this,for_write);                            //100730
      photoperiod  .setup_structure(*this,for_write);                            //100513
   }
   if ( (CROPSYST_FRUIT || !for_write))                                          //020405
         // ORCHARD_VINEYARD_MODEL_OR_UNKNOWN)
   { // fruit trees and grape harvest parameters
      set_current_section(LABEL_fruit);
      expect_enum("harvest_condition",fruit.harvest_condition_mode_cowl);        //081204
   }
   if ((!for_write || (crop_model_labeled.get() == CROPGRO_MODEL)))              //031121
      expect_file_name("model_input",cropgro.model_input_file,255);
/*151016 I have temporarily moved this to Crop_param_class until
 * I have fully implemented parameter adjustments idiom
   set_current_section(LABEL_crop);
//151016 #ifndef VIC_CROPSYST
   EXPECT_ENUMERATED_SECTION("adjustment",adjustment_section_VV,adjustments);    //120726
//151016 #endif
*/
   EXPECT_ENUMERATED_SECTION("grain_stress_period",grain_stress_sensitivity_period_section_VV,harvest.grain_stress_sensitivity_periods); //130428
   structure_defined = true;                                                     //120314
   return expected;
}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
void Crop_parameters::setup_optional_parameters()
{
   if (parameter_editor_mode) return; // In parameter editor, we have already bound UI controls to these members so we can't delete them
   if (   (crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL))
   {  // the orchard and vineyard models the following parameters are unneeded
      land_use_labeled.set(FALLOW); // Presuming that fallow most closely describes orchard soil condition
      if (harvested_part_labeled.get() == UNKNOWN_PART)                          //020423
         harvested_part_labeled.set(fruit_part);                                 //020423
      life_cycle_labeled.set(perennial_life_cycle);                              //080722
      //151111unused stem_type_labeled.set(woody_stem);                                         //080722
   }
//031121       NYI  somethings could be deleted for CropGro model
   else
      if (harvested_part_labeled.get() == UNKNOWN_PART)
         harvested_part_labeled.set(grain_part);
}
//_2002-04-19_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::set_start()
{
   if (description.brief == "") description.brief = "-";                         //150112_990301
   #ifdef DISABLED
   bool fruit_tree_crop =
      crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL;                        //130418
   //110326 currently not optional
   if (nitrogen && fruit_tree_crop)                                              //020405
   {  delete nitrogen; nitrogen = 0; }                                           //020405
   #endif

   bool started = Common_parameters_data_record::set_start();                    //020408
   delete_entry("crop","C_species");                                             //110908
   delete_entry("growth","max_RUE_mode ");                                       //110908
   delete_entry("growth","RUE_max");                                             //110908
   return started;                                                               //161023
}
//_2001-01-09_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//______________________________________________________________________________
extern bool LADSS_mode;
#define  LABEL_salinity          "salinity"
//______________________________________________________________________________
bool Crop_parameters::get_end()
{
/*180626 format upgrade now handled externally.

   #if (CROPSYST_VERSION == 4)
   bool file_created_prior_to_N_conc_based_on_critical= (data_source_version.get_number() > 0x040000) && (data_source_version.get_number() < 0x041100);
   if (file_created_prior_to_N_conc_based_on_critical                            //130319
       || !was_entry_encountered("nitrogen","biomass_to_start_dilution_crit_N_conc"))
      nitrogen.dilution_curve_based_on_max_conc = true;
   #endif
*/
   Crop_parameters_class::get_end();                                             //120725
/*170524 moved to Crop_parameters_class
#ifndef VIC_CROPSYST
   FOR_EACH_IN(adjustment,Adjustment,adjustments,each_adj)
   {
      if (adjustment->parameter==LABEL_max_water_uptake)
         has_max_water_uptake_adjustments = true;
   }
   FOR_EACH_END(each_adj)
#endif
*/
   setup_optional_parameters();                                                  //020419
   if (crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)                       //020716
   {  // Need to make sure that the harvested part is fruit is selected, because it is not show in the parameter editor.
      if (fruit.grape)                                                           //030515
         deciduous_obsolete = true;                                              //030515
      harvested_part_labeled.set(fruit_part);                                    //030514
      // In the fruit crop model, the peak_LAI_deg_day is essentially the begin_rapid_fruit_growth_deg_day where LAI accumulation stops.  //030529
   } else                                                                        //030514
      deciduous_obsolete = false;                                                //040517
   if (land_use_labeled.get() == PASTURE)                                        //040525
      harvested_part_labeled.set(leaf_part);                                     //040525
   if (!parameter_editor_mode)                                                   //030520
   {
      {  // The following if is for version 3 file compatilibiity
         if (CORN::is_approximately<float32>(vernalization.end,0.0,0.000001))   //020718
            vernalization.enabled = false;                                      //020718
      }
   }
   initialize_after_load();                                                      //010109
   if (harvested_part_labeled.get() == UNKNOWN_PART) harvested_part_labeled.set(grain_part);   //060726
#ifdef NYI
080506
For compatibility with previous version
at_pt_limit has been replaced by these,

   ,reduce_canopy_expansion_LWP     (-1000.0), v_reduce_canopy_expansion_LWP(reduce_canopy_expansion_LWP, UC_J_kg,"LWP_reduces_canopy_expansion" ,2,) //080506_
   ,stop_canopy_expansion_LWP       (-1200.0), v_stop_canopy_expansion_LWP  (stop_canopy_expansion_LWP  , UC_J_kg,"LWP_stops_canopy_expansion"   ,2,) //080506_
#endif
   {
      if (!CORN::is_approximately<float32>(reference_light_to_biomass_kg_MJ_old, 0.0,0.0001))
      {
      biomass_production.RUE_PAR_deprecated = kg_to_g(reference_light_to_biomass_kg_MJ_old); // Convert from kg/MJ to g/MJ)
      // I believe reference_light_to_biomass_kg_MJ_deprecated was RUE_global
      // When upgrading, prefer PAR RUE basis as this will be the default in V5
      //110908 biomass_production.RUE_global   = biomass_production.RUE_PAR * 2.0;
      #if (CROPSYST_VERSION==4)
      biomass_production.RUE_basis = photosynthetically_active_radiation;
      #endif
      }
   }
  // When CO2 is not enabled, the CO2_adj_maximum_cover is simply the maximum_cover
  /*180626 now quite obsolete
   if ((data_source_version.get_number() > 0) && (data_source_version.get_number() < 0x040F13))                    //120505
   {
      //121219 These became deprecated in version 4.17.00 because dilution curves are now based on critical curve not maximum curve
      #if (CROPSYST_VERSION == 4)
      if (nitrogen.dilution_curve_based_on_max_conc)                             //121219
         nitrogen.biomass_to_start_dilution_max_N_conc_T_ha
            = CropSyst::biomass_to_start_dilution_max_N_conc_default
               [photosynthetic_pathway_labeled.get()];                           //120505
      #endif
      nitrogen.dilution_curve_max_conc_mature = CropSyst::N_mature_max_conc_default
               [photosynthetic_pathway_labeled.get()];                           //120505
   }
   */
   /*180626 now quite obsolete
   if ((data_source_version.get_number() > 0) &&
       (data_source_version.get_number() < 0x041300))                            //141120
   */
   if (version_code < 5)                                                         //180624
      switch (senesced_biomass_fate_labeled_obsolete.get())                      //141120
      {
         case senesced_biomass_endure   : abscission_labeled.set(abscission_not_applicable);break;
         case senesced_biomass_shed     : abscission_labeled.set(marcescent);               break;
         case senesced_biomass_linger   : abscission_labeled.set(semi_deciduous);           break;
         default: break;                                                         //170217
      }

   if (was_entry_encountered("phenology","resolution"))
      thermal_time.thermal_response_cowl.set                                     //151207
       ((thermal_time.resolution_labeled_deprecatedX.get() == HOURLY)
         ? nonlinear
         : linear);

   return true;                                                                  //161023
}
//_2001-01-09___________________________________________________________________
Crop_parameters::Nitrogen::Nitrogen()
:Crop_parameters_class::Nitrogen()
,v_max_uptake_daily_rate         (max_uptake_daily_rate_kg_ha      ,UC_kg_ha              ,"max_uptake_daily_rate" ,2,5.0  , 0.0  ,20.0 /*?*/ ,0.0,100.0/*?*/ ,"kg/ha/day","Maximum uptake during rapid linear growth") // Warning need valid ranges

//121219 Deprecated in V 4.17
#if (CROPSYST_VERSION == 4)
,v_demand_adjust                       (demand_adjust                         ,UC_adjustment       ,"demand_adjust"                       ,2,1.0  , 0.5  ,1.5 ,0.0,2.0,"adjustment" ,"Nitrogen demand adjustment")
,v_biomass_to_start_dilution_max_N_conc(biomass_to_start_dilution_max_N_conc_T_ha,UC_tn_per_ha  ,"biomass_to_start_dilution_max_N_conc",3,1.5 /*C3*/,0.00001,3.0,0.0,4.0,"tn/ha"      ,"Biomass to start dilution of maximum N concentration")
#endif
,v_emergence_max_conc                  (emergence_max_conc                      ,UC_kg_kg            ,"emergence_max_conc"                ,3,0.007, 0.003,0.1,0.0,0.3,TU_kgN_kgDM ,"Maximum N concentration of canopy at emergence")                                           //121219
,v_emergence_crit_conc                 (emergence_crit_conc                     ,UC_kg_kg            ,"emergence_crit_conc"               ,3,0.007, 0.003,0.1,0.0,0.3,TU_kgN_kgDM ,"Critical N concentration of canopy at emergence")                                          //121219
,v_biomass_to_start_dilution_crit_N_conc(biomass_to_start_dilution_crit_N_conc_T_ha,UC_tn_per_ha  ,"biomass_to_start_dilution_crit_N_conc",3,1.5 /*C3*/,0.00001,4.0,0.0,10.0,"T/ha"      ,"Biomass to start dilution of critical N concentration")                        //121219
,v_stubble_max_conc                    (stubble_max_conc                      ,UC_kg_kg            ,"stubble_max_conc"                    ,3,0.007, 0.003,0.01,0.0,0.03,TU_kgN_kgDM ,"Maximum N concentration of chaff and stubble"/*061214 TL_Maximum_N_content_of_standing_stubble*/)
,v_root_conc                           (root_conc                             ,UC_kg_kg            ,"root_conc"                           ,3,0.007, 0.001,0.10,0.0,0.03,TU_kgN_kgDM ,"Standard root N concentration" )
,v_residual_N_not_available_for_uptake (residual_N_not_available_for_uptake   ,UC_ppm              ,"residual_N_not_available_for_uptake" ,3,1.0  , 0.0  , 10 ,0.0, 100,"ppm"       ,"Residual N not available for uptake" )
,v_soil_N_conc_where_N_uptake_decreases(soil_N_conc_where_N_uptake_decreases  ,UC_ppm              ,"soil_N_conc_where_N_uptake_decreases",3,5.0  , 0.0  ,100 ,0.0,1000,"ppm"       ,"Soil N concentration at which N uptake starts decreasing" )
,v_PAW_where_N_uptake_rate_decreases   (PAW_where_N_uptake_rate_decreases     ,UC_decimal_percent  ,"PAW_where_N_uptake_rate_decreases"   ,3,0.5  , 0.0  ,1.0 ,0.0, 1.0,"0-1"       ,"Plant available water at which N uptake starts decreasing" )
,v_N_mature_max_conc                   (dilution_curve_max_conc_mature        ,UC_kg_kg            ,"N_mature_max_conc"                ,3,0.0235  ,0.0      ,1.0,0.0,1.0,TU_kgN_kgDM      ,"Maximum above ground concentration at maturity")
,v_dilution_curve_slope                (dilution_curve_slope                  ,UC_unitless         ,"dilution_curve_slope"                       ,3,0.45,0.0,2.0,0.0,2.0,"0-1","Concentration curve slope")  // need the valid range for this //121219
,v_end_dilution_curve                  (end_dilution_curve_deg_day    /*,UC_Celcius_degree_days */ ,"end_dilution_curve"      ,0 ,0,MAXSHORT,0,MAXSHORT,"�C-days","End dilution curve")                                        //130408                                          //130408
{
   #if (CROPSYST_VERSION==4)
   dilution_curve_based_on_max_conc  =false;                                     //121219
   #endif
}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Nitrogen::setup_structure(Data_record &record,bool for_write)    modification_
{
   bool satup = Crop_parameters_class::Nitrogen::setup_structure(record, for_write);
   record.expect_valid_float32(v_max_uptake_daily_rate);                         //061129
   record.expect_valid_float32(v_stubble_max_conc);                              //061214
   record.expect_valid_float32(v_root_conc);                                     //061216
   #if (CROPSYST_VERSION==4)
   record.expect_valid_float32(v_demand_adjust);                                 //061213
   record.expect_valid_float32(v_biomass_to_start_dilution_max_N_conc);          //120505
   #endif
//   if (dilution_curve_based_on_max_conc || !for_write)
//   {
      record.expect_valid_float32(v_emergence_max_conc);                            //121219
      record.expect_valid_float32(v_emergence_crit_conc);                           //121219
      record.expect_valid_float32(v_biomass_to_start_dilution_crit_N_conc);         //121219
//   }

   record.expect_valid_float32(v_PAW_where_N_uptake_rate_decreases);             //070209
   record.expect_valid_float32(v_residual_N_not_available_for_uptake);           //070209
   record.expect_valid_float32(v_soil_N_conc_where_N_uptake_decreases);          //070209
   record.expect_valid_float32(v_N_mature_max_conc);                             //120505
   record.expect_valid_float32(v_dilution_curve_slope);                          //120507
   #if (CROPSYST_VERSION==4)
   record.expect_bool("dilution_curve_based_on_max_conc",dilution_curve_based_on_max_conc); //130320
   #endif
   record.expect_valid_int16(v_end_dilution_curve);
#ifdef NYI
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
//080916#if (CROPSYST_VERSION < 5)
// 080818 these parameters were renamed
   if (!for_write)                                                               //080818
   {  expect_float32("uptake_adj",nitrogen->max_uptake_daily_rate);              //080818
availability_adj=0.6999999881 Nitrogen availability adjustment
residual=4.0000000000 Amount of residual nitrogen per soil layer
max_conc_emerge=0.0379999988 Maximum N concentration during early growth
min_conc_mature=0.0070000002 Minimum N concentration at maturity
max_conc_mature=0.0120000001 Maximum N concentration at maturity
max_stubble=0.0099999998 Maximum N content of standing stubble
   }                                                                            //080818
#endif
#endif
   return satup;
}
//_2002-04-08___________________________________________________________________
Crop_parameters::Fruit::Fruit()
:Crop_parameters_class::Fruit()
, v_fract_total_solids              (fract_total_solids                 ,UC_decimal_percent  ,LABEL_fract_total_solids              ,2,0.35,0.1,0.5  ,0.0,1.0   ,TU_0_1    ,TL_Fraction_of_total_solids)
, v_max_fruit_load_kg_ha            (max_fruit_load_kg_ha               ,UC_kg_ha            ,LABEL_max_fruit_load                  ,2,5000,0  ,20000,0  ,100000,TU_kg_ha  ,"Max. fruit load (fresh mass)" /*TL_Max_fruit_load*/)// Warning need good value
/*180601 never implemented
, v_initial_fruit_mass              (initial_fruit_mass           ,UC_kg_ha,"initial_fruit_mass"           ,2,0.02, 0.0,1000.0,  0.0,1000.0,TU_kg_ha,"Initial fruit mass",TL_Sensitivity_to_water_stress)
, v_initial_reserves_release_rate   (initial_reserves_release_rate,UC_kg_ha,"initial_reserves_release_rate",2,0.02, 0.0,1000.0,0.0,1000.0,TU_kg_ha,"Initial release rate of biomass reserves (per day)") // Warning need default and ranges
, v_clusters_per_vine               (clusters_per_vine                     ,"clusters_per_vine" ,30,10,100,0,1000,"clusters","Clusters per vine")  // Warning need default and ranges
, v_berries_per_cluster             (berries_per_cluster                   ,"berries_per_cluster",100,0,200,0,500,"berries","Berries per cluster")// Warning need default and ranges
, v_fruits_per_tree                 (fruits_per_tree                  ,"fruits_per_tree",250,0,500,0,1000,"fruits","Fruits per tree")// Warning need default and ranges
*/
, v_initial_growth_fraction_to_fruit(initial_growth_fraction_to_fruit   ,UC_decimal_percent  ,LABEL_initial_growth_fraction_to_fruit   ,2, 0.5,0  ,1    ,0  ,100   ,TU_0_1    ,"Fraction of above biomass apportioned to fruit after flowering")
, v_rapid_growth_fraction_to_fruit  (rapid_growth_fraction_to_fruit     ,UC_decimal_percent  ,LABEL_rapid_growth_fraction_to_fruit     ,2, 0.5,0  ,1    ,0  ,100   ,TU_0_1    ,"Fraction of above biomass apportioned to fruit during accelerated fruit growth")
, v_harvest_temperature             (harvest_temperature                ,UC_Celcius          ,"harvest_temperature",1,15.01,-10.0,20.0 ,-20.0,40.0,"�C","Low temperature for harvest")
, v_harvest_temperature_days        (harvest_temperature_days           /*,UT_days*/         ,"harvest_temperature_days",5,0,30,0,365,"Days","Consecutive days below the low temperature for to consider harvest")
, v_harvest_DOY_earliest            (harvest_DOY_earliest               /*,UT_day_of_year*/  ,"earliest_harvest"      ,258 ,1,365,1,365,"DOY","Day to start looking for harvest conditions")
, v_harvest_DOY_latest              (harvest_DOY_latest                 /*,UT_day_of_year*/  ,"latest_harvest"        ,275 ,1,365,1,365,"DOY","Day to force harvest (or fixed date)")
, v_max_water_uptake_before_fruiting      (max_water_uptake_before_fruiting_mm     ,UC_mm_per_day  ,"max_water_uptake_before_fruiting"      ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"before fruiting")
, v_max_water_uptake_during_initial_fruit (max_water_uptake_during_initial_fruit_mm ,UC_mm_per_day  ,"max_water_uptake_during_initial_fruit" ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"during intial fruit")
, v_max_water_uptake_during_radid_fruit   (max_water_uptake_during_radid_fruit_mm   ,UC_mm_per_day  ,"max_water_uptake_during_radid_fruit"   ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"during rapid fruit")
, v_max_water_uptake_during_veraison      (max_water_uptake_during_veraison_mm      ,UC_mm_per_day  ,"max_water_uptake_during_veraison"      ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"during veraison")
, v_max_water_uptake_after_maturity       (max_water_uptake_after_maturity_mm       ,UC_mm_per_day  ,"max_water_uptake_after_maturity"       ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"after maturity")
{}
//______________________________________________________________________________
bool Crop_parameters::Fruit::setup_structure(Data_record &record,bool for_write) modification_
{
   bool satup = Crop_parameters_class::Fruit::setup_structure(record,for_write);
   record.expect_valid_float32(v_fract_total_solids);                             //000630
   record.expect_valid_float32(v_max_fruit_load_kg_ha);                           //000616
   record.expect_valid_float32(v_initial_growth_fraction_to_fruit);               //030521
   record.expect_valid_float32(v_rapid_growth_fraction_to_fruit);   // grapes     //030521
   record.expect_valid_float32(v_harvest_temperature);                            //081204
   record.expect_valid_int16  (v_harvest_temperature_days);                       //081204
   record.expect_valid_int16  (v_harvest_DOY_earliest);                           //081204
   record.expect_valid_int16  (v_harvest_DOY_latest);                             //081204
   record.expect_valid_float32(v_max_water_uptake_before_fruiting);               //091202
   record.expect_valid_float32(v_max_water_uptake_during_initial_fruit);          //091202
   record.expect_valid_float32(v_max_water_uptake_during_radid_fruit);            //091202
   record.expect_valid_float32(v_max_water_uptake_during_veraison);               //091202
   record.expect_valid_float32(v_max_water_uptake_after_maturity);                //091202
   return satup;
}
//_2011-03-26___________________________________________________________________
#ifdef CHECK_NEEDED
110127 probably is but dont delete yet
Crop_parameters::Fruit::Fruit(const Fruit &copy_from)
: public Crop_parameters::Fruit(const Fruit &copy_from)

, v_initial_fruit_mass           (initial_fruit_mass           ,UC_kg_ha,"initial_fruit_mass"           ,2,0.02, 0.0,1000.0,  0.0,1000.0,TU_kg_ha,"Initial fruit mass",TL_Sensitivity_to_water_stress)
, v_initial_reserves_release_rate(initial_reserves_release_rate,UC_kg_ha,"initial_reserves_release_rate",2,0.02, 0.0,1000.0,0.0,1000.0,TU_kg_ha,"Initial release rate of biomass reserves (per day)") // Warning need default and ranges
, v_clusters_per_vine            (clusters_per_vine            /*count*/,"clusters_per_vine" ,30,10,100,0,1000,"clusters","Clusters per vine")  // Warning need default and ranges
, v_berries_per_cluster          (berries_per_cluster          /*count*/,"berries_per_cluster",100,0,200,0,500,"berries","Berries per cluster")// Warning need default and ranges
, v_fruits_per_tree              (fruits_per_tree              /*count*/,"fruits_per_tree",250,0,500,0,1000,"fruits","Fruits per tree")// Warning need default and ranges

, v_harvest_temperature_days        (harvest_temperature_days           /*,UT_days*/         ,"harvest_temperature_days",5,0,30,0,365,"Days","Consecutive days below the low temperature for to consider harvest")
, v_harvest_temperature (harvest_temperature ,UC_Celcius,"harvest_condition_mode",15,1,-10.0,20.0 ,-20.0,40.0,"�C","Low temperature")
, v_harvest_DOY_earliest(harvest_DOY_earliest/*,UT_DOY*/,"earliest_harvest"      ,258 ,1,365,1,365,"DOY","Day to start looking for harvest conditions")
, v_harvest_DOY_latest  (harvest_DOY_latest  /*,UT_DOY*/,"latest_harvest"        ,275 ,1,365,1,365,"DOY","Day to force harvest (or fixed date)")

, v_fract_total_solids                  (fract_total_solids                 ,UC_decimal_percent  ,LABEL_fract_total_solids              ,2,0.35,0.1,0.5  ,0.0,1.0   ,TU_0_1    ,TL_Fraction_of_total_solids)
, v_max_fruit_load_kg_ha                (max_fruit_load_kg_ha               ,UC_kg_ha            ,LABEL_max_fruit_load                  ,2,5000,0  ,20000,0  ,100000,TU_kg_ha  ,"Max. fruit load (fresh mass)" /*TL_Max_fruit_load*/)
, v_initial_growth_fraction_to_fruit    (initial_growth_fraction_to_fruit   ,UC_decimal_percent  ,LABEL_initial_growth_fraction_to_fruit   ,2, 0.5,0  ,1    ,0  ,100   ,TU_0_1    ,"Fraction of above biomass apportioned to fruit after flowering")
, v_rapid_growth_fraction_to_fruit      (rapid_growth_fraction_to_fruit     ,UC_decimal_percent  ,LABEL_rapid_growth_fraction_to_fruit      ,2, 0.5,0  ,1    ,0  ,100   ,TU_0_1    ,"Fraction of above biomass apportioned to fruit during accelerated fruit growth")

, v_max_water_uptake_before_fruiting      (max_water_uptake_before_fruiting_mm      ,UC_mm_per_day  ,"max_water_uptake_before_fruiting"      ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"before fruiting")
, v_max_water_uptake_during_initial_fruit (max_water_uptake_during_initial_fruit_mm ,UC_mm_per_day  ,"max_water_uptake_during_initial_fruit" ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"during intial fruit")
, v_max_water_uptake_during_radid_fruit   (max_water_uptake_during_radid_fruit_mm   ,UC_mm_per_day  ,"max_water_uptake_during_radid_fruit"   ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"during rapid fruit")
, v_max_water_uptake_during_veraison      (max_water_uptake_during_veraison_mm      ,UC_mm_per_day  ,"max_water_uptake_during_veraison"      ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"during veraison")
, v_max_water_uptake_after_maturity       (max_water_uptake_after_maturity_mm       ,UC_mm_per_day  ,"max_water_uptake_after_maturity"       ,2,10.0,    5.0,15.0,  3.0,20.0,TU_mm_day,"after maturity")
{}
#endif
//______________________________________________________________________________
Crop_parameters::Salinity::Salinity()
:Crop_parameters_class::Salinity()
,v_osmotic_pot_50    (osmotic_pot_50   ,UC_kPa               ,LABEL_osmotic_pot_50,1,-0.0000001, -500.0,-100.0,  -1000.0,0.0 ,TU_kPa,TL_Soil_solution_osmotic_pot_for_50_yield_reduction) //990605
,v_salt_tolerance_P  (salt_tolerance_P ,U_units_not_specified,LABEL_tolerance_P   ,3,0.0000001, 1.0,5.0,    0.0,10.0 ,TU_1_5,TL_Salt_tolerance)
{}
//_2002-04-08___________________________________________________________________
Crop_parameters::CO2_Response::CO2_Response()
:Crop_parameters_class::CO2_Response()
,v_TUE_reference_conc                  (CO2_concentration_when_measured.TUE     ,UC_parts_per_million ,"TUE_reference_conc"        ,1,350.0,0.0,1000.0,0.0,5000.0 ,TU_ppm     ,"transpiration use efficiency","CO2 concentration when measured") //131206
,v_RUE_reference_conc                  (CO2_concentration_when_measured.RUE     ,UC_parts_per_million ,"RUE_reference_conc"        ,1,350.0,0.0,1000.0,0.0,5000.0 ,TU_ppm      ,"radiation use efficiency"    ,"CO2 concentration when measured") //131206
,v_alpha                               (non_rectagular_hyperbola_solution.alpha ,UC_unitless ,"alpha"                              ,8,0.005,0.0,1.0   ,0.0,9999.9 ,TU_unitless ,"alpha"                      ,"Non-rectangular hyperbola solution for estimated relative growth")
,v_theta                               (non_rectagular_hyperbola_solution.theta ,UC_unitless ,"theta"                              ,8,0.8  ,0.0,1.0   ,0.0,9999.9 ,TU_unitless ,"theta"                      ,"Non-rectangular hyperbola solution for estimated relative growth")
,v_growth_ratio_asymptotic             (non_rectagular_hyperbola_solution.growth_ratio_asymptotic,UC_ratio    ,"growth_ratio_asymptotic"                   ,8,1.7  ,0.0,10.0  ,0.0,9999.9 ,TU_unitless ,"asymptotic growth ratio"       )

/* C3             C4
alpha 0.003836    0.00038
theta 0.9909      0.977
GRA   1.26025     1.0627
*/
{}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::CO2_Response::setup_structure(Data_record &record,bool for_write)    modification_
{  bool satup = Crop_parameters_class::CO2_Response::setup_structure(record,for_write);
   record.expect_valid_float32(v_TUE_reference_conc);                            //980223
   record.expect_valid_float32(v_RUE_reference_conc);                            //980223
   record.expect_valid_float32(v_alpha);                                         //131206
   record.expect_valid_float32(v_theta);                                         //131206
   record.expect_valid_float32(v_growth_ratio_asymptotic);                       //131206
   return satup;
}
//_2011-03-26___________________________________________________________________
Crop_parameters::Tolerance::Tolerance()
: Crop_parameters_class::Tolerance()
,v_leaf_damage_cold_temp            (temperature_cold_leaf_damage    ,UC_Celcius,LABEL_damage_cold_temp,2,-5.0,-20,20,-100,100,TU_degrees_C,"Cold temperature which begins to damage the plant (leaves)") //991116
,v_leaf_lethal_cold_temp            (temperature_cold_leaf_lethal    ,UC_Celcius,LABEL_lethal_cold_temp,2,-10,-20,20,-100,100,TU_degrees_C,"Cold temperature which is lethal to the plant (leaves)") //991116
,v_fruit_damage_cold_temp           (temperature_cold_fruit_damage   ,UC_Celcius,"fruit_damage_cold_temp",2,-5.0,-20,20,-100,100,TU_degrees_C,"Minimum daily air temperature which begins to damage flower/fruit")   //081126
,v_fruit_lethal_cold_temp           (temperature_cold_fruit_lethal   ,UC_Celcius,"fruit_lethal_cold_temp",2,-10,-20,20,-100,100,TU_degrees_C,"Minimum daily air temperature which is lethal to flower/fruit")  //081126
{}
//_2002-04-08_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
bool Crop_parameters::Tolerance ::setup_structure
(Data_record &record,bool for_write,Harvested_part harvested_part) modification_
{  bool satup = Crop_parameters_class::Tolerance::setup_structure(record,for_write,harvested_part);
   record.expect_valid_float32(v_leaf_damage_cold_temp);                         //990129
   record.expect_valid_float32(v_leaf_lethal_cold_temp);                         //991029
   if ((harvested_part == fruit_part) || !for_write)
   {  record.expect_valid_float32(v_fruit_damage_cold_temp);                     //081128
      record.expect_valid_float32(v_fruit_lethal_cold_temp);                     //081128
   }
   return satup;
}
//_2011-03-25___________________________________________________________________
Crop_parameters::Canopy_characteristics_hedge_row::Canopy_characteristics_hedge_row()
:Crop_parameters_class::Canopy_characteristics_hedge_row()
,v_initial_width              (initial_width          ,UC_meter   ,"initial_width"            ,2,1.0,0.0,10.0,0.0,10.0,TU_m,"Initial tree width") //040715
,v_final_width                (final_width            ,UC_meter   ,"final_width"              ,2,1.0,0.0,10.0,0.0,10.0,TU_m,"Final tree width") //040715
,v_initial_breadth            (initial_breadth        ,UC_meter   ,"initial_breadth"          ,2,2.0,0.0,10.0,0.0,10.0,TU_m,"Initial tree width along the row") //071116
,v_final_breadth              (final_breadth          ,UC_meter   ,"final_breadth"            ,2,2.0,0.0,10.0,0.0,10.0,TU_m,"Final tree width along along the row")  //071116
,v_initial_height             (initial_height         ,UC_meter   ,"initial_height"           ,2,1.2,0.0,10.0,0.0,10.0,TU_m,"Initial tree height") //040715
,v_final_height               (final_height           ,UC_meter   ,"final_height"             ,2,1.2,0.0,10.0,0.0,10.0,TU_m,"Final tree height") //040715
,v_branch_insertion_height    (branch_insertion_height,UC_meter   ,"branch_insertion_height"       ,2,0.5,0.0, 3.0,0.0,10.0,TU_m,"Branch insertion height") //071116
{}
//_2002-04-08___________________________________________________________________
Crop_parameters::Layout::Layout()
:Crop_parameters_class::Layout()
,v_row_spacing(spacing.row/*180109 row_spacing*/  ,UC_meter/*_width*/      ,LABEL_row_spacing    ,2,2.7,0.0, 10.0,0.0, 10.0,TU_m,"Spacing between rows") //040715
,v_col_spacing(spacing.col/*180109 col_spacing */ ,UC_meter/*_width*/      ,LABEL_col_spacing    ,2,2.5,0.0, 10.0,0.0, 10.0,TU_m,"Spacing along (within) rows")      //040715
,v_row_azimuth(row_azimuth_true_north_deg ,UC_degree_from_north,LABEL_row_azimuth        ,2,0.0,0.0,360.0,0.0,360.0,"degree(0=N,90=0)","Row azimuth")
{}
//______________________________________________________________________________
Crop_parameters::   ~Crop_parameters()
{
   #if (__BCPLUSPLUS__ > 0) && (__BCPLUSPLUS__ < 0x0570)
   //adjustments.delete_all();                                                     //140416
   //140416 There is a bug in the Crop parameter when it close, the adjustment cleanup is crashing ,so just ignoring the cleanup.

   while (adjustments.pop_at_head());

/*
   FOR_EACH_IN(adjustment,CORN::Item,adjustments,each_adj)
      //each_adj->detach_current();
      //each_adj->delete_current();

   FOR_EACH_END(each_adj)
adjustments.delete_all();                                                     //140416
*/
   while (harvest.grain_stress_sensitivity_periods.pop_at_head());
//harvest.grain_stress_sensitivity_periods.delete_all();
//   while (harvest.grain_stress_sensitivity_periods.pop_at_head());
//   while (adjustments.pop_at_head());
adjustments.delete_all();
//has_max_water_uptake_adjustments=false; //just a break point

   while (sections.pop_at_head());
//has_max_water_uptake_adjustments=false; //just a break point

   while (enumerated_sections_definitions.pop_at_head());
//has_max_water_uptake_adjustments=false; //just a break point


   #endif

}
//_2002-04-09___________________________________________________________________
Crop_parameters::CropGro::CropGro()
: model_input_file("filename.INP","INP","CropGro model input","*.INP")
{}
//_2003-05-21___________________________________________________________________
} // namespace CropSyst                                                          //140318

