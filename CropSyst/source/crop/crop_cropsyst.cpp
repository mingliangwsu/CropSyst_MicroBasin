
#include "crop/crop_cropsyst.h"
#  include "static_phrases.h"
#   include "corn/measure/measures.h"
#   include <math.h>
#   include "corn/math/moremath.h"
#   include "cs_dvlp.h"
#   include <float.h>
#include "crop/crop_biomass.h"
#include "crop/canopy_growth_LAI_based_V4.h"
#include "crop/canopy_growth_LAI_based_V5.h"

#ifndef CROP_CALIBRATION
#  include "crop/canopy_growth_cover_based.h"
#endif
#include "mgmt_param.h"

#ifndef SOIL_ABSTRACT_H
#  include "soil/soil_interface.h"
#endif
#include "soil/soil_evaporator.h"

#ifdef QND
#include <Q_N_D.h>
#endif

#  include "crop/crop_param.h"
#  include "crop/crop_emergence.h"

#ifdef OLD_ORCHARD
#include "common/weather/hour/weather_hours.h"
#include "crop/crop_orchard_common.h"
#ifdef FRUIT_CROP_MODEL
#  include "crop/crop_fruit.h"
#endif
#endif
#if (CROPSYST_VERSION==4)
#include "common/weather/hour/weather_hours.h"
#  include "common/weather/loc_param.h"
// loc_param has Season
#  include "common/weather/weather.h"
#endif
#  include "common/simulation/log.h"
#ifdef NITROGEN
#  include "crop/crop_N_V4.h"
#  include "crop/crop_N_V5.h"
#endif
#ifdef CO2_CHANGE
#  include "crop/CO2_response.h"
#endif
#   ifdef EVENT_PROCESSING
#      include "cs_event.h"
#   endif
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#include "crop/growth_stages.hpp"

#define common_translate(x) x

#ifndef ET_reference_FAOH
#  include "biometeorology/ET_reference_FAO.h"
//120406 included only for canopy_resistance_contant
// I should move that into an ET_type.h file
#endif
#include "crop/yield.h"
#include "corn/chronometry/date_32.h"

#ifdef OLD_BIOMASS_GROWTH
#else
#  include "crop/biomass_growth_RUE_TUE.h"
/*180403 Obsolete Claudio decided to not have this model in CropSyst
#  ifdef LIU_XIAO_CROP
#     include "Liu_Xiao/biomass_growth_Liu_Xiao.h"
#     include "Liu_Xiao/canopy_growth_Liu_Xiao.h"
#  endif
*/
#endif

#ifdef DEBUG_N_CONC
extern ofstream debug_N_conc_harvest_residue_root;
#endif
extern float64 CS_UED_max_root_biomass_encountered;
extern float64 CS_UED_max_canopy_biomass_encountered;

// Keep the LAI and biomass dumps for Mike
//debug ofstream dump_lAI("LAI.dat");
#ifdef DUMP_BIOMASS
ofstream dump_biomass("biomass.dat");
#endif
#include "crop/extreme_temperature_response.h"
#ifdef CS_INSPECTOR_VERSION
#  include "UED/library/database_file.h"
#  include "UED/library/datasetrec_creation.h"
#  include "UED/library/datasetrec.h"
#  include "UED/library/controls.h"
#  include "CS_suite/observation/CS_observation.h"
#  include "corn/quality.hpp"
#endif

#include "common/residue/residues_interface.h"

#include "csvc.h"
#include "csvc_special.h"


// For inspection:

#include "CS_suite/observation/CS_inspector.h"
#define CSVC_crop_degree_hours_above_30_today                        0x8021FFFE
#define CSVC_crop_degree_hours_above_34_today                        0x8021FFFD
#define CSVP_crop_transpiration_use_eff                              0x21FFFF
#define CSVP_crop_ET_act                                             0x21FFFC
#define CSVP_crop_ET_pot                                             0x21FFFB

#define CSVC_crop_duration_season                                    0x8021FFF8

#include "CS_suite/observation/CS_examination.h"

namespace CropSyst {
float64 no_CO2_adjustment = 1.0;                                                 //160314
//______________________________________________________________________________
float64 calc_stress_adjusted_temperature
(float64 crop_param_phenologic_sensitivity_water_stress
,float64 air_temp                // Could be max temperatue (or hourly temp?)    //030610
,float64 senescence_reduction_factor  // may be 0 if not yet achieved peak_LAI   //030610
,float64 water_stress_index
,float64 vapor_pressure_deficit_max   //check if this is VPD max
,Normal_crop_event_sequence growth_stage_sequence
,bool          has_leaf_senescence) /* was perennial but that didn't account for perennials that lost leaves */ //020628
{  float64 senescence_reduction =                                                //970123
      (has_leaf_senescence  && ((growth_stage_sequence < NGS_MATURITY)           //130902
         && !is_approximately(senescence_reduction_factor ,0.0,0.00001) ))       //030610
        ? senescence_reduction_factor  : 1.0;                                    //030609
   senescence_reduction = std::max<float64>(0.0,std::min<float64>(senescence_reduction,1.0)); // should not needed guarenteed to be between 0-1 //970123
   float64 stress_increase_temperature = air_temp
      + ((1.0 + 1.5
                * vapor_pressure_deficit_max                                     //010202
                * senescence_reduction)
          * water_stress_index)                                                  //010726
        * crop_param_phenologic_sensitivity_water_stress;                        //030610
   return stress_increase_temperature;
}
//_calc_stress_adjusted_temperature____________________________________________/
} // namespace CropSyst

namespace CropSyst {                                                             //141206
//____________________________________________________________2002-11-25_1997?_/
Crop_complete::Crop_complete
(
 Crop_parameters     *parameters_                                                //020409
,float64 param_dry_soil_root_activity_coef_                                      //170518
,float64 param_saturated_soil_root_activity_coef_                                //170518
#ifdef OLD_ORCHARD
,Orchard_interface   *orchard_
#endif
,bool                                   owns_parameters_                         //040121
,const CORN::date32 &today_                                                      //170525
,CORN::Unidirectional_list             &performable_operations_                  //151004
,const CS::CO2_atmospheric_concentration *atmospheric_CO2_conc_ppm_optional      //180122
,modifiable_ Crop_CO2_response         *Crop_CO2_response_given_optional         //151201
,const Air_temperature_maximum         &air_temperature_max_                     //140813
,const Air_temperature_minimum         &air_temperature_min_                     //140813
,const Air_temperature_average         &air_temperature_avg_                     //140813
,const Solar_radiation                 &solar_radiation_                         //140813
,const Vapor_pressure_deficit_daytime  &daytime_vapor_pressure_deficit_          //140813
,const Vapor_pressure_deficit_max      &vapor_pressure_deficit_max_              //140813
,const Psychrometric_constant          &psychrometric_constant_                  //140508
,const Weather_spanning_interface      &weather_                                 //151201
,const CORN::Local_time                &sun_rise_time_                           //150907
,const float64                         &ref_day_length_hours_                    //140812
,Seeding_parameters                    *seeding_parameters_ // may be 0          //041201
,Soil_interface                        *soil_                                    //050721
,Crop_nitrogen_model                    nitrogen_model_                          //050722
#ifdef NITROGEN
,const Slope_saturated_vapor_pressure_plus_psychrometric_resistance            //referenced
      *slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference
#endif
)
:Crop_common
   (parameters_,owns_parameters_                                                 //040121
   ,daytime_vapor_pressure_deficit_                                              //140813
   ,soil_
   ,Crop_CO2_response_given_optional                                             //160418
   ,today_                                                                       //150915
   ,performable_operations_                                                      //151004
   ,param_dry_soil_root_activity_coef_                                           //170518
   ,param_saturated_soil_root_activity_coef_)                                    //170518
,weather                         (weather_)
,sun_rise_time                   (sun_rise_time_)                                //150907
,snow_pack_thickness             (0)                                             //161111_141205
#ifndef OLD_PHENOLOGY_SEQUENCER
,Phenology_sequencer
   (today_
   ,*parameters_
   ,air_temperature_min_
   ,ref_day_length_hours_)
#endif
, air_temperature_max       (air_temperature_max_)                               //140813
, air_temperature_min       (air_temperature_min_)                               //140813
, air_temperature_avg       (air_temperature_avg_)                               //140813
, solar_radiation           (solar_radiation_)                                   //140813
, vapor_pressure_deficit_max        (vapor_pressure_deficit_max_)                //140813
, psychrometric_constant            (psychrometric_constant_)                    //140508
, soil_salinity(soil_ ? soil_->ref_salinity():0)                                 //160412_140812
, canopy_growth(0) // set below                                                         //050823
, water_canopy_expansion_factor(1.00)                                            //080806
, stress_adj_hourly_temperature_estimator       (60) // 60 minute intervals
, stress_adj_hourly_temperature                 (24) // not sure best initialial size
, stress_adj_hourly_temperature_not_applicable  (24) // not sure best initialial size
, seeding_parameters    (seeding_parameters_)                                    //041202
, estimate_root_biomass (false)                                                  //060612
, fallow_deprecated     (false)                                                  //010110
, yesterday_deg_day     (0)                                                      //161110
, vapor_pressure_deficit_stats(STAT_arithmetic_mean_bit)                         //160803_030530
, intercepted_radiation             (0)                                          //084029
, intercepted_radiation_accum       (0)                                          //080429
, intercepted_radiation_season_accum(0)                                          //080429
, attainable_top_growth             (0)                                          //161110
#ifdef OLD_BIOMASS_GROWTH
, RUE_temperature_limitation_factor (0)
#else
, biomass_growth                    (0)                                          //180111
#endif
, biomass_at_filling                (0)                                          //161110
, biomass_at_maturity               (0)                                          //161110
, unclipped_biomass                 (0)                                          //071004

// Reporting and output
, reported_peak_LAI                 (0)                                          //161110
, reported_GAI                      (0)                                          //161110
, reported_LAI                      (0)                                          //161110
, reported_canopy_biomass           (0)                                          //161110
, reported_N_mass_yield             (0)                                          //161110
, reported_canopy_cover_green       (0)                                          //161110
, reported_canopy_cover_max         (0)                                          //180413
, recorded_root_depth               (0)                                          //070131
, total_season_biomass_production_output     (0)                                 //161110
, total_season_biomass_running_accum_output  (0)                                 //161110
, reported_LAI_for_self_shading_response(0.00001)                                //080728
, reported_GAI_max                  (0)                                          //161110
, GAI_max_date                      (0)                                          //180413
, plant_height                      (0)
, days_after_flowering              (0)                                          //040907
, roots_current                     (0)                                          //070131
#ifndef CROP_CALIBRATION
, roots_dormant                     (0)                                          //070131
#endif
, roots_vital                       (0)                                          //070131

, pot_root_biomass                  (0)                                          //161110
, act_root_biomass                  (0)                                          //161110

, report_temperature_stress_stats(STAT_arithmetic_mean_bit)                      //160803_010726
, overall_growth_stress             (0)                                          //161110
, yield                             (0)                                          //150825
, initialized                       (false)                                      //031121
, is_in_leaf_senescence             (0)                                          //161110
, season                            (1)                                          //030613
, fall_sowing                       (false)                                      //040914
, harvests_this_season              (0)                                          //161110
, no_more_clippings_this_season     (0)                                          //161110

, linger_sowing_label               (0)                                          //030521
, linger_budbreak_label             (0)                                          //030521
, linger_tuber_init_label           (0)                                          //081108
, linger_veraison_label             (0)                                          //030521
, linger_harvest_label              (0)                                          //030521
, linger_chill_satisfied_label      (0)                                          //030529
, inactive_end_date                 (0)                                          //170525
, limited_pot_transpiration_m       (0)                                          //161110
, transpiration_dependent_growth                                                 //080721
   (
   #ifdef YAML_PARAM_VERSION
    parameters_->ref_biomass_production()
   #else
   *parameters_
   #endif
   ,daytime_vapor_pressure_deficit
   ,ET_ref
   ,CO2_TUE_adjustment                                                           //151030
   ,season                                                                       //180111
   ,before_WUE_change                                                            //180111
   )

, latest_harvest_date        (0)                                                 //170525
, unexpected_termination_date(0) //must be 0                                     //170525

, biomass_fate_today                (0)                                          //NEW_BF
, biomass_fate_season               (0)                                          //NEW_BF

, deg_day_stop_root                 (0)                                          //161110
, terminate_pending                 (0)                                          //161110

, fruit_harvested                   (0)                                          //161110
, days_of_expected_dormancy_remaining  (0)                                       //161110

, C_mass_canopy_est                 (0)                                          //110915_060818
, C_mass_root_est                   (0)                                          //110915_060818

, CO2_current_conc_optional                                                      //161110
   (atmospheric_CO2_conc_ppm_optional)                                           //180119
, CO2_TUE_adjustment                (1.0)                                        //150907

#ifdef OLD_PHENOLOGY_SEQUENCER
, emerged                           (false)                                      //161110
, stress_adjusted_temperature       (0.0)                                        //161110
, thermal_time
  ( (parameters->thermal_time.thermal_response ==linear)                         //151109
    ? (Thermal_time_common *)(new Thermal_time_daily_linear
      (parameters_->thermal_time
      ,stress_adjusted_temperature                                               //140626
      ,air_temperature_min                                                       //140626
      ,temperature_with_est_night                                                //140626
      ,ref_day_length_hours_                                                     //140812
      ,parameters_->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL
      ,parameters_->vernalization.enabled ? &(parameters_->vernalization) : 0
      ,(parameters_->photoperiod.photoperiodism_cowl.get() > no_photoperiod)     //100513
         ?(&(parameters_->photoperiod)) : 0) )
   : (Thermal_time_common *)(new Thermal_time_daily_nonlinear
      (parameters_->thermal_time
      ,stress_adjusted_temperature                                               //140626
      ,air_temperature_min                                                       //140626
      ,temperature_with_est_night                                                //140626
      ,ref_day_length_hours_                                                     //140812
      ,parameters_->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL
      ,parameters_->vernalization.enabled ? &(parameters_->vernalization) : 0
      ,(parameters_->photoperiod.photoperiodism_cowl.get() > no_photoperiod)     //100513
         ?(&(parameters_->photoperiod)) : 0)))
, phenology                                                                      //130904
   (parameters_->phenology
   ,thermal_time->ref_thermal_time_cumulative()
   ,parameters_->is_fruit_tree()
   ,parameters_->is_perennial())
#endif
, emergence                   (0)                                                //041201
, emergence_hydrothermal_time (0)                                                //041201
, quiescence_start_requirement(0) // set below                                   //160326_080401
, quiescence_end_requirement  (0)   // will be set once dormancy (or end of season) start //160326_080401
#ifdef OLD_ORCHARD
, ref_hourly_weather          (0)                                                //080908
, orchard                     (orchard_)
, fruit_adjusted_parameters   (new Crop_parameters::Fruit(parameters_->fruit))   //081103
, fruit_harvest_requirements  (0)                                                //081204
, limit_max_LAI(false)                                                           //081103
, fruit_dry_biomass           (0)                                                //161110
, veraison_date               (0)                                                //170525
, bud_break_date              (0)                                                //170525
, initial_fruit_growth_date   (0)                                                //170525
, rapid_fruit_growth_date     (0)                                                //170525
, chill_requirement_satisfied_date(0)                                            //170525
#ifdef FRUIT_CROP_MODEL
, fruit_chill_requirement     (0)   // will be set at end of dormancy            //021125
, fruit_bud_break_requirement (0) // will be set when chill requiment satisfied. //021125
#endif
// , at_max_fruit_load           (false)                                            //180308
#endif
, at_max_fruit_load           (false)                                            //180308
, nitrogen(0)                                                                    //050722
, N_mass_canopy_recorded_before_harvest(0)                                       //070209
, ref_event_log(0)                                                               //021007
, ref_residues(0)  // Set by know residues (currently only applies to V4_4_ORGANIC_MATTER_AND_RESIDUE) //060531
, report_degree_hours_above_30_today   (0)                                       //161110
, report_degree_hours_above_34_today   (0)                                       //161110
, report_transpiration_use_eff         (0)                                       //161110
{
   #ifdef NITROGEN
   // We must instanciate nitrogen first because it is needed to instanciate canopy
   switch (nitrogen_model_)                                                      //050722
   {  case CROP_NITROGEN_ORIGINAL :                                              //050722
         nitrogen = new
            Crop_nitrogen_V5                                                     //151106
            ((parameters->nitrogen)
            ,*this,soil_,soil_->mod_nitrogen()                                   //160412
            ,slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference//150602
            ,transpiration_dependent_growth.ref_transpiration_use_efficiency_CO2_adjusted());   //151104
      break;
      default : break; // just leave nitrogen 0 (disabled)
   }
   #endif
   // Nitrogen must exist before we create canopy
   create_canopy();
   if (soil)                                                                     //061208
   {
      float64 initial_root_length                                                //180727
         = cm_to_m(parameters_->root.length_at_emergence_cm);                    //180727
      if (parameters_->root.initial_depth_deprecated > 0.00001)                  //180727
      {
         std::clog << "Warning: the crop parameter file uses old initial root depth, using old initial root length determination." << std::endl;

      float64 depth_emergence =
         parameters_->root.get_depth_emergence_m_deprecated();                   //170105
      float64 soil_thickness_1 = soil->ref_layers()->get_thickness_m(1);         //170105
      float64 initial_root_length                                                //120817
         = depth_emergence - soil_thickness_1;                                   //170105_120817
      if ( initial_root_length < 0) initial_root_length = depth_emergence;       //170105
      }                                                                          //180727
      canopy_growth->get_biomass_current(include_vital);                         //130624
      roots_current = roots_vital =
            dynamic_cast<Crop_root_vital *>                                      //130625
            (new Crop_root_vital_V5
            (parameters->root
            ,parameters->phenology
            ,(*thermal_time)                                                     //151110
            ,*soil->ref_layers()
            ,initial_root_length));
   }
   if (fallow_deprecated)
   {  parameters->life_cycle_labeled.set(UNKNOWN_LIFE_CYCLE); // perennial = false;
      parameters->land_use_labeled.set(FALLOW);
      emerged = false;
      parameters->initialize_fallow();                                           //010109
   }
   {
      CORN::Date_clad_32 yesterday(today.get_date32()); yesterday.dec_day();     //170525_030722
      float64 Tmax_yesterday  = weather.get_air_temperature_max_yesterday();     //151201
      float64 Tmin_tomorrow   = weather.get_air_temperature_min_tomorrow();      //151201
      // Must get yesterday first, it could have data quality different from today  //040510
      float64 Tmax_today      = air_temperature_max.Celcius();                   //151201
      float64 Tmin_today      = air_temperature_min.Celcius();                   //151201
      stress_adj_hourly_temperature_estimator.reset
         (Tmax_today, Tmax_yesterday, Tmin_today, Tmin_tomorrow);                //030610
   }
   if (parameters->season_dormancy_mode_labeled.get() > single_season)   // This should include both multiple_season and dormancy_season models
      quiescence_start_requirement = new Quiescence_start_requirement            //160326
         (parameters->quiescence
         ,(parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL));     //080401
   switch (parameters->harvested_part_labeled.get())
   {  case grain_part :
         yield = new Yield_grain
            (parameters->harvest.index_unstressed
            ,parameters->harvest.apply_adjustment_to_unstressed_harvest_index
            ,parameters->harvest.apply_heat_extreme_adjustment_to_unstressed_harvest_index
            ,parameters->harvest.translocation_fraction_max
            ,ref_phenology()
            ,sun_rise_time                                                       //150907
            ,stress_adj_hourly_temperature);
      break;
      case tuber_part :
         yield = new Yield_tuber
            (
/*180403 Obsolete Claudio decided to not have this model in CropSyst

   #ifdef LIU_XIAO_CROP
               (parameters->parameters_Liu_Xiao)                                 //180122
             ? parameters->parameters_Liu_Xiao->HI                               //180122
             :
   #endif
*/
            parameters->harvest.index_unstressed
            ,parameters->harvest.apply_adjustment_to_unstressed_harvest_index
            ,parameters->harvest.stress_sensitivity_tuber_init
            ,parameters->harvest.tuber_growth_sensitivity
            ,parameters->tolerance.temperature_heat_tuber_critical
            ,ref_phenology()
            ,air_temperature_avg);
               // currently just using air temperature to represent soil temperature
               // In version 5 soil temperature should be available
      break;
      case HARVEST_CANOPY :  // essentially all above (95%) ground biomass       //031015
         yield = new Yield_canopy
            (parameters->harvest.index_unstressed
            ,parameters->harvest.apply_adjustment_to_unstressed_harvest_index
            ,ref_phenology());
      break;
      case HARVEST_COMPLETE :
         // All biomass including roots                                          //031015
         std::clog << parameters->description.brief << std::endl;
         std::clog << "Harvest complete yield model not yet implemented." << std::endl;
         std::clog << "This is not necessarily an error, I.e. when harvest management is clipping." << std::endl;
         yield = new Yield_complete;                                           //140929
      break;
      case UNKNOWN_PART :
         std::cerr << parameters->description.brief << std::endl;
         std::cerr << "Crop parameter file harvest part unknown, part must be selected" << std::endl;
         assert(false); //NYI
      break;
      case fruit_part :
         #ifdef OLD_ORCHARD
         yield = new Yield_orchard_fruit(fruit_dry_biomass);                     //170221
         #else
         // fruit yield is setup in Crop_CropSyst_orchard_fruit::initialize()    //170221
         #endif
      break;
      case root_part :
         // NYI In the past this has been using the harvest index against above ground biomass
         // but is should be the root biomass.
      case bulb_part :  // NYI
         // The bulb is considered above ground biomass even though
         // it is mostly subsurface (it is not root).
      case leaf_part :  // NYI
      default:
         yield = new  Yield_simple_harvest_index
            (parameters->harvest.index_unstressed
            ,parameters->harvest.apply_adjustment_to_unstressed_harvest_index
            ,parameters->harvest.stress_sensitivity_growth
            ,ref_phenology());
      break;
   } // switch harvested_part
   event_scheduler = as_event_scheduler_crop = new Event_scheduler_crop_complete
      (*this,today,performable_operations_);
}
//_constructor_________________________________________________________________/
Crop_complete::~Crop_complete()
{
   if (emanator_known) emanator_known->set_status(CS::Emanator::deleted_status); //160614
#ifdef OLD_ORCHARD
   #ifdef FRUIT_CROP_MODEL
   delete fruit_chill_requirement;
   delete fruit_bud_break_requirement;
   #endif
   delete fruit_harvest_requirements;
#endif
   delete quiescence_start_requirement;
   delete quiescence_end_requirement;
   delete biomass_fate_today;
   delete biomass_fate_season;
   delete nitrogen;                                                              //070221
   delete canopy_growth;                                                         //070626
   delete roots_current;                                                         //141103
   delete CO2_response;
   delete thermal_time;                                                          //180522
}
//_destructor_______________________________________________________2002-04-09_/
bool Crop_complete::initialize()                                 initialization_
{
   bool initialized = Crop_common::initialize();                                 //031130
         #ifdef YAML_PARAM_VERSION
         // will be using new parameter adjustment idiom
         #else
         as_event_scheduler_crop->take_events(parameters->adjustments);          //151004
         as_event_scheduler_crop->take_events(parameters->harvest.grain_stress_sensitivity_periods); //151004
         #endif
         as_event_scheduler_crop->take_events(parameters->associated_events);    //151004

         // Warning this does not allow crop parameters to be
         // shared/referenced                                                    //160916


   emerged                                = false;                               //000808
   intercepted_radiation                  = 0;                                   //080428
   intercepted_radiation_accum            = 0;                                   //080428
   intercepted_radiation_season_accum     = 0;                                   //080428
   //180111 updated dailyattainable_top_growth                  = 0;                                   //011022
   N_mass_canopy_recorded_before_harvest  = 0;                                   //110915

   reported_peak_LAI                      = 0;                                   //040929
   recorded_root_depth                    = 0;                                   //000501
   reported_ET_act_m                      = 0;                                   //171031
   plant_height                           = 0;                                   //990201
   pot_root_biomass                       = 0;                                   //010713
   act_root_biomass                       = 0;                                   //010713
#ifdef OLD_ORCHARD
//071120
   fruit_dry_biomass                      = 0;                                   //000616
#endif
   act_transpiration_m                    = 0;                                   //011022
   report_transpiration_act_m             = 0;                                   //000323
   intercepted_precipitation_m_today      = 0;                                   //160414
   water_stress_stats                     .reset();                              //010726
   report_temperature_stress_stats        .reset();                              //010726
   // no need to reset because instanciated for each crop instance
   // however tubers could be perennial do may want to have Yield.reset()
   if (yield) yield->reset();                                                    //150825
   #ifdef OLD_BIOMASS_GROWTH
   RUE_temperature_limitation_factor      = 0;                                   //011016
   #endif
   overall_growth_stress                  = 0;
   biomass_at_filling                     = 0;                                   //131022
   biomass_at_maturity = 0;                                                      //130510
   phenology.growth_stage = NGS_NONE;
   is_in_leaf_senescence         =false;                                         //121221
   phenology.reset();                                                            //131202
   #ifdef OLD_ORCHARD
   initial_fruit_growth_date  .set_YD(Year(0),CORN::DOY(0));                     //030521
   veraison_date              .set_YD(Year(0),CORN::DOY(0));                     //030521
   rapid_fruit_growth_date    .set_YD(Year(0),CORN::DOY(0));                     //030521
   bud_break_date             .set_YD(Year(0),CORN::DOY(0));                     //081013
   inactive_end_date          .set_YD(Year(0),CORN::DOY(0));                     //081013
   chill_requirement_satisfied_date.set_YD(Year(0),CORN::DOY(0));                //081013
   #endif
   latest_harvest_date        .set_YD(Year(0),CORN::DOY(0));
   GAI_max_date               .set_YD(Year(0),CORN::DOY(0));                     //180413
   //180413 largest_GAI_date           .set_YD(Year(0),CORN::DOY(0));
   total_season_biomass_production_output = 0.0;                                 //040719
   delete biomass_fate_today;    biomass_fate_today = 0;  // note, should alway be 0
   delete biomass_fate_season;   biomass_fate_season = 0; // note, should alway be 0
   deg_day_stop_root = parameters->param_end_veg_growth_or_rapid_fruit_growth_deg_day(); //030529
   canopy_growth->invalidate();                                                         //050823
   //180413 largest_GAI_for_output  = 0;
   reported_GAI_max = 0;                                                         //180413
   days_of_expected_dormancy_remaining = 0;                                      //980723
   terminate_pending = false;                                                    //040514
   fruit_harvested = false;                                                      //030529
   pot_transpiration_m[1] = pot_transpiration_m[0] = 0.0;                        //151031
   #ifdef NITROGEN
   if (nitrogen) initialized &= nitrogen->initialize();
   #endif
      // set water stress to 0 because root caculation is occuring before stress
      // is calculated on first day.
   return initialized;
}
//_initialize__________________________________________________________________/
bool Crop_complete::start()
{  bool started = true;                                                          //140619
   #ifndef OLD_PHENOLOGY_SEQUENCER
   started = Phenology_sequencer::start();
   #endif
#ifdef OLD_ORCHARD
//071120 moved to Crop_CropSyst_fruit
   if (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)           //030523_080331 Actually should probably also check if season_dormancy_mode == dormancy_season
   {  phenology.growth_stage = NGS_DORMANT_or_INACTIVE;                          //130925
       // assuming fruit simulations start jan 1 today.get_DOY()
      quiescence_end_requirement = new Quiescence_end_requirement                //160326
         ((parameters->quiescence),1 );
#ifdef FRUIT_CROP_MODEL
      fruit_chill_requirement = new Fruit_chill_requirement(parameters->dormancy.chill_hours);  //030529
#endif
      roots_vital->root_length       = parameters->root.max_depth;               //061212
      plant_height      = parameters->morphology.max_canopy_height;              //990213
      // dont trigger sync because this will immediatly cause an end of season on the first day
      // 091119  /*030516_*/       trigger_synchronization(DORMANT_or_INACTIVE);
   }
   else
#endif
   {

      is_in_leaf_senescence =false;                                              //121221
      plant_height       = 0.0;                                                  //990213
      linger_sowing_label = 1; // 3;                                             //030521
      trigger_synchronization(NGS_PLANTING);                                     //030516
      #ifdef OLD_PHENOLOGY_SEQUENCER
      phenology.growth_stage = NGS_GERMINATION;                                  //130902
      trigger_synchronization(NGS_GERMINATION);                                  //170406
      #else
      event_start(NGS_PLANTING);                                                 //140620
      event_start(NGS_GERMINATION);                                              //140620
      #endif
      #if (CROPSYST_VERSION==4)
      switch (parameters->emergence.emergence_model_cowl.get())                  //041201
      {                                                                          //041201
         #ifdef SEED_EMERGENCE_MODEL
         case EMERGENCE_HYDROTHERMAL_TIME    :                                   //041201
            emergence = emergence_hydrothermal_time
            = new Crop_emergence_hydrothermal_time                               //041201
             (parameters->emergence
             ,parameters->canopy_growth_LAI_based.specific_leaf_area
             ,seeding_parameters);                                               //041201
         break;
       #endif
//conceptual I would like to make the original thermal time mode a separate model SEED /*041201_*/     default /*EMERGENCE_THERMAL_TIME*/  : emergence = emergence_thermal_time      = new Crop_emergence_thermal_time();      break;
      }
      #endif
   }
   return started;
}
//_start____________________________________________________________2007-11-20_/
bool Crop_complete::sow(bool _fall_sowing)   // was plant_crop
{
   harvests_this_season = 0;                                                     //040624
   no_more_clippings_this_season = false;                                        //040721
   //180413 largest_GAI_for_output       = 0;
   reported_GAI_max = 0;                                                         //180413
   //180413 largest_GAI_date.set(today);                                                  //001115
   GAI_max_date.set(today);                                                      //180413_001115
   phenology.start_date[NGS_PLANTING].set(today);                                //141202_001115
   phenology.start_date[NGS_RESTART] .set(today);                                //141202_130114
   terminate_pending = false;                                                    //070711
   start();                                                                      //071120
   #ifdef OLD_BIOMASS_GROWTH
   RUE_temperature_limitation_factor = 1.0;                                      //011016
   #endif
   as_event_scheduler_crop->synchronize                                          //151004
      (Synchronization(false, NGS_PLANTING),today);
   return true;                                                                  //020711
}
//_sow______________________________________________________________2002-02-22_/
bool Crop_complete::in_growing_season()                                    const
{  return phenology.is_in_growing_season() && (!biomass_fate_today);             //130903
}
//_in_growing_season___________________________________________________________/
const char *Crop_complete::describe_growth_stage()                         const
{  const char *growth_stage_phrase = get_growth_stage_description
      (phenology.growth_stage,parameters->is_fruit_tree());                      //120820
   if ((phenology.growth_stage == NGS_FILLING)
      && (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL) )
         { growth_stage_phrase = "Init. fruit growth"; }
#ifdef FRUIT_CROP_MODEL
   if (fruit_bud_break_requirement) {growth_stage_phrase = "Bud break evaluation"; }         //180701
   if (fruit_chill_requirement)     {growth_stage_phrase = "Chill requirments evaluation"; } //180701
#endif
   if (linger_sowing_label)   {growth_stage_phrase = "Sowing";    }
   if (linger_budbreak_label) {growth_stage_phrase = "Bud break"; }
   if (linger_tuber_init_label) {growth_stage_phrase = "Tuber init"; }
   if (linger_veraison_label) {growth_stage_phrase = "Veraison";  }
   if (linger_chill_satisfied_label)  {growth_stage_phrase = "Chill requirements satisfied";   }
   if (fruit_harvested)       {growth_stage_phrase = "Post fruit harvest"; }
   if (linger_harvest_label)  {growth_stage_phrase = "Harvest";   }  // must follow fruit_harvested check
   return (growth_stage_phrase);
}
//_describe_growth_stage____________________________________________2003-05-21_/
bool Crop_complete::start_inactive_period(bool apply_dormancy)                   //140625080401
{
   bool started = true;
   trigger_synchronization(NGS_DORMANT_or_INACTIVE);                             //130902_021217
   #ifdef OLD_PHENOLOGY_SEQUENCER
   phenology.start_date[NGS_DORMANT_or_INACTIVE].set(today);                     //081013
   phenology.growth_stage = NGS_DORMANT_or_INACTIVE; //080321  This may need to be INACTIVE_PERIOD    //970219


   //It is necessary to clear thermal time at the start of the inactive
   //period otherwise, for fruit crops, chilling evaluation uses thermal time
   //and if there is residual thermal time, the chilling requirement will be
   //immediately satisfied.

   thermal_time->clear_accum_degree_days();  // <- IMPORTANT TO DO THIS           //000719

   #else
   started = Phenology_sequencer::start_inactive_period(apply_dormancy);         //140625
   #endif
   // full_crop class with set biomass to residue basic crop doesn't do this     //970219
   intercepted_radiation = 0.0;                                                  //080429
   intercepted_radiation_accum = 0.0;                                            //080429
   bool dormancy_is_applicable
      = (parameters->season_dormancy_mode_labeled.get() == dormancy_season);     //080910
   float64 dormancy_senesce = (                                                  //970219
      dormancy_is_applicable ? parameters->dormancy.senesce : 0.0);              //080331
   if (CORN::is_approximately<float64>(dormancy_senesce,100.0,0.00001))          //060317
      create_canopy();                                                           //081103
   else canopy_growth->end_season(apply_dormancy);                                      //080401
//180615   #ifdef YAML_PARAM_VERSION
   started &= as_event_scheduler_crop->end_season();                             //150930
//   #endif
#ifdef NITROGEN
   if (nitrogen) nitrogen->start_dormancy();
      // This may need to apply to the inactive period, not just dormancy        //080321
#endif
   started &= end_season();                                                      //160618
   return started;
}
//_start_inactive_period____________________________________________1997-02-19_/
bool Crop_complete::is_orchard()                                     affirmation_
{  return
   #ifdef OLD_ORCHARD
      orchard != NULL;
   #else
      false;  // derived crop orchard will override and return true;
   #endif
}
//_is_orchard_______________________________________________________2012-09-09_/
bool Crop_complete::create_canopy()
{  bool is_continuous_grass =                                                    //080515
        (parameters->harvested_part_labeled.is(leaf_part))
      && (parameters->season_dormancy_mode_labeled.is(multiple_season) );

#ifdef OLD_ORCHARD
#ifdef OLD_PROVIDE_CANOPY
//180614 Now the user can select the canopy cover model
//081103 dont delete this until providing it in cropsyst_crop_fruit
         if (orchard)                                                            //081103
         {  if (canopy_growth)                                                          //081111
               canopy_growth->end_season(true);                                         //081111
            canopy_growth = orchard->provide_canopy                                     //081103
            (*parameters,parameters->canopy_growth_cover_based                   //1810614
            ,(*thermal_time)                                                     //151110
            ,ref_residues,nitrogen
            ,phenology
            ,water_stress_stats.index
            // WARNING need to check if this will be the previous days value when canopy cover is updated
            ,water_canopy_expansion_factor
            ,CO2_response) ;                                                     //081103
            /*180614
            (*parameters,parameters->canopy_growth_LAI_based                     //081103
            ,(*thermal_time)                                                     //151110
            ,ref_residues,nitrogen,reported_peak_LAI                             //081103
            ,CO2_response) ;                                                     //081103
            */

            // may need to be if deciduous                                       //081111
         } else                                                                  //081103
#endif
#endif

   {
       delete canopy_growth; canopy_growth = 0;

   switch (parameters->morphology.canopy_growth_model)                           //080725
   {  // NYI case  : canopy = new xxxxx(); break;
#ifndef CROP_CALIBRATION
      case canopy_cover_based_2017 :                                             //171219_080805
      //180601 obsolete case canopy_cover_based_2013 :                                             //080805
      {  Canopy_growth_cover_based *canopy_growth_cover_based =                  //110904
            new  Canopy_growth_cover_based
            (*parameters
            ,parameters->canopy_growth_cover_based
            ,(*thermal_time)                                                     //151110
            ,ref_residues,nitrogen
            ,phenology
            ,water_stress_stats.index
            // WARNING need to check if this will be the previous days value when canopy cover is updated
            ,water_canopy_expansion_factor
            #ifdef CO2_CHANGE
            , CO2_response
            #endif
            );                                                                   //080805
         canopy_growth = canopy_growth_cover_based;                              //110904
      } break;
#endif
      #if (CROPSYST_VERSION==4)
      case leaf_area_index_based_duration:                                       //080725
      {
         canopy_growth = new
            CropSyst::Canopy_growth_leaf_area_index_based_V4
            (*parameters
            ,parameters->canopy_growth_LAI_based
            ,(*thermal_time)                                                     //151110_080805
            ,ref_residues,nitrogen                                               //060816
            ,reported_peak_LAI                                                   //080725
            ,CO2_response                                                        //080728
            ,is_continuous_grass);                                               //081102
      } break;
      #endif
      case leaf_area_index_based : default:                                      //080725
      {
         canopy_growth = new
            CropSyst::Canopy_growth_leaf_area_index_based_V5
            (*parameters
            ,parameters->canopy_growth_LAI_based
            ,(*thermal_time)                                                     //151110
            ,ref_residues,nitrogen
            ,reported_peak_LAI
            ,CO2_response
            ,is_continuous_grass);
      } break;
     } // switch  canopy_growth_labeled
   }
   bool canopy_initialized = (canopy_growth!=NULL) && canopy_growth->initialize();             //080805

#ifndef OLD_PROVIDE_CANOPY
/*180618 now passed as parameter
   if (orchard) orchard->know_canopy(canopy);                                    //180614
*/
#endif

   return canopy_initialized;
}
//_create_canopy____________________________________________________2006-05-31_/
void Crop_complete::
#ifdef OLD_ORCHARD
      start_normal_crop_dormancy( )
#else
      senesce_at_dormancy()
#endif
 // This is truly only for dormancy, not inactive_period                         //080321
{
   float64 dormancy_senesce =                                                    //060317
      ((parameters->season_dormancy_mode_labeled.get() == dormancy_season)       //080331
         ? parameters->dormancy.senesce : 100.0);                                //080331
   {  Biomass_fate_parameters biomass_fate =                                     //040621
      { 0//remove_for_consumption                                                //040815
      , 0//remove_as_grazing                                                     //040610
      ,90//remain_as_residue                                                     //040610
      , 0//remove_for_disposal                                                   //040610
      ,10//remain_standing_dead                                                  //040610
      , 0//remain_standing_live                                                  //040610
      ,50//remain_roots_as_residue // Claudio says to use 50% for now,           //040621
      ,50//remain_roots_live                                                     //040621
      , 0//remove roots as loss                                                  //160830
      , 0//return_as_manure                                                      //040908
      };                                                                         //040621
      if (!CORN::is_approximately<float64>(dormancy_senesce,100.0,0.00001))      //070313
      {  biomass_fate.remain_as_dead = parameters->dormancy.senesce;             //070313
         biomass_fate.remain_as_residue = 0.0;                                   //070313
         biomass_fate.remain_as_live = 100.0 - parameters->dormancy.senesce;     //070313
      }                                                                          //070313
      Crop_mass_fate_biomass_and_nitrogen *fate =                                //070625
      process_biomass_fate                                                       //040621
         (DORMANCY_CAUSE
         ,OTHER_BIOMASS_FATE,0.0,0.0,0.0  // This is not a harvest event
         ,biomass_fate
         ,false,0.0);
//070626          WARNING need to check that fate is accounted for
//                (at least the fate that removes
//                Don't delete this message until this if verified.
      if (fate) delete fate;                                                     //060323
   }
}
//_start_dormancy___________________________________________________1997-02-19_/
float64 Crop_complete::est_root_biomass()                                  const
{  // Way want to revisit this, if we have an explicit daily total biomass
   // accumulation model with top and root partitioning.                         //010713
   float64 emergence_deg_day_param = parameters->phenology.initiation.emergence; //040120
   float64 accum_deg_days = thermal_time->get_accum_degree_days(false);          //151110_040830   //130820 confirmed not adjusted
   float64 root_to_top_ratio = (0.75 - 0.6 *
      ((accum_deg_days - emergence_deg_day_param)/
       (deg_day_stop_root - emergence_deg_day_param )));
  float64 ested_root_biomass // kg/m2
     = std::max<float64>(act_root_biomass,get_canopy_biomass_kg_m2_including
         (include_vital) * root_to_top_ratio);
      // RLN Warning I think this need to be canopy biomass_produced (including the amount decomposed) and actually produced during the season (or ever?)
      // Because I dont think roots senesce or diminish from clipping
  return ested_root_biomass;
}
//_est_root_biomass_________________________________________________2006-06-12_/
extern float64 debug_Daily_Direct_Row_Int ;
extern float64 debug_Daily_Diffuse_Row_Int ;
//______________________________________________________________________________
void Crop_complete::update_lingers()                               modification_ // augments adjuncts
{  if (linger_sowing_label)   linger_sowing_label--;                             //030521
   if (linger_budbreak_label) linger_budbreak_label--;                           //030521
   if (linger_harvest_label)  linger_harvest_label--;                            //030521
   if (linger_tuber_init_label) linger_tuber_init_label--;                       //081111
#ifdef OLD_ORCHARD
//071120 moved to Crop_CropSyst_fruit
   if (linger_budbreak_label) linger_budbreak_label--;                           //030521
   if (linger_veraison_label) linger_veraison_label--;                           //030521
   if (linger_chill_satisfied_label)  linger_chill_satisfied_label--;            //030529
#endif
}
//_update_lingers___________________________________________________2007-11-20_/
void Crop_complete::actual_growth()
{  update_lingers();
   float64 act_biomass_growth = 0.0;
   float64 GAI_related_biomass_growth = 0;                                       //980206
   canopy_growth->process_day();  // forces update even during dormancy    (probably should be inside (!fallow) //060818
   if (! fallow_deprecated)
   {
   /*180618 abandoned  Claudio decided not to put this in CropSyst
   #ifdef LIU_XIAO_CROP
   if (parameters->parameters_Liu_Xiao)                                          //180118
   {  if (canopy->develop_leaf(true,attainable_top_growth,attainable_top_growth,0)) //180118
         total_season_biomass_production_output += attainable_top_growth;        //080728
   }                                                                             //180118
   else
   #endif
   */
   {
   float64 evap_layer_thickness = soil ? soil->ref_layers()->get_thickness_m(1) : 0.05;
         // alias growth_stage here is just for convenience during my transition it should be growth_stage_sequence
      if (phenology.growth_stage >= FGS_BUD_BREAK)                               //070202
      {  bool allow_fruit_crop_growth_during_maturity
            =   (phenology.growth_stage == NGS_MATURITY)
            && (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL); //070202
         if ((phenology.growth_stage <= NGS_MATURITY) || allow_fruit_crop_growth_during_maturity)//011117
         { // For fruit model, we allow additional biomass growth during maturity 030523
            act_biomass_growth = calc_act_biomass_growth                         //011022
               (evap_layer_thickness                                             //010202
               ,GAI_related_biomass_growth);                                     //011022
            C_mass_canopy_est = act_biomass_growth * get_carbon_fraction();      //110915_060818
         } else
         {  overall_growth_stress = 1.0; // will be updated if we call
            #ifdef NITROGEN
            if (nitrogen && (phenology.growth_stage < NGS_DORMANT_or_INACTIVE))
                nitrogen->process_any_gaseous_losses();                          //120630
            #endif
            // Now N gaseous losses may continue throughout maturity (and dormancy)
            // Note that N gaseous loss during active growth is handled by actual biomass growth   //070202
         }
      }
      float32 min_water_or_N_stress =  (float32)get_min_water_N_stress();        //081109
         // use float32 because stats is float32
      if (yield) yield->know_stress(min_water_or_N_stress);                      //150825
         // This will use either the default straw_to_residue,
         // or the latest set by the management harvest operation 030808
      if (phenology.growth_stage > NGS_GERMINATION)                                          //040824
      {  bool not_dormant_or_inactive  = (phenology.growth_stage < NGS_DORMANT_or_INACTIVE); //080725
         float64 accum_deg_days = thermal_time->get_accum_degree_days(true);                  //151110_13022 confirmed adjusted

// std::clog << parameters->description.brief.c_str() << " degdays:" << accum_deg_days << std::endl;

         float64 thermal_time_growing_degree_day = thermal_time->get_growing_degree_day();    //080728
         canopy_growth->age_leaf(thermal_time_growing_degree_day,water_stress_stats.index);         //080726
         if (not_dormant_or_inactive)                                            //080725
         {  float64 GAI_vital = get_GAI_vital();                                 //170818

         if (GAI_vital > reported_GAI_max/*180413 largest_GAI_for_output*/)                                 //070320
         {
            GAI_max_date.set(today);                                             //180413
            //180413 largest_GAI_date.set(today);
            reported_GAI_max/*180413 largest_GAI_for_output*/ = GAI_vital;                                  //070320
         }
         float64 leaf_and_branch_growth
            // RLN - I think this should actually only be leaf                   //071120
            = distribute_todays_non_leaf_stem_growth(act_biomass_growth);        //071120

         /*std::clog << "act_biomass_growth:" << act_biomass_growth
                   << "\tleaf_and_branch_growth:" << leaf_and_branch_growth
                   <<std::endl;*/

         bool has_leaf_senescence = parameters->has_leaf_senescence();
         float64 max_canopy_deg_day  = parameters->phenology.culmination.accrescence; //081103
         bool continue_leaf_growth =                                             //000616
               ((accum_deg_days < max_canopy_deg_day)                            //040830
               || !has_leaf_senescence)                                          //030521
               && !get_limit_max_LAI();                                          //081103

         /*std::clog << "continue_leaf_growth:" << continue_leaf_growth
                   << "\tGAI_related_biomass_growth:" << GAI_related_biomass_growth
                   <<std::endl;*/


         //170316LML may need to consider the possibility that GAI_related_biomass_growth
         //is greater than leaf_and_branch_growth (e.g. fruit trees)

         if (canopy_growth->develop_leaf
               (continue_leaf_growth,                                            //000407
               leaf_and_branch_growth                                            //071120
               ,GAI_related_biomass_growth
               ,thermal_time_growing_degree_day))                                //080726
            total_season_biomass_production_output += act_biomass_growth;        //080728
         if (!continue_leaf_growth&&has_leaf_senescence&&is_in_leaf_senescence)  //121221
            initiate_senescence();                                               //121221
         }
      if (  (phenology.growth_stage < NGS_MATURITY)                              //991119
          &&parameters->tolerance.enabled)                                       //120117
         check_hardiness();
      //NYI else allow_natural_expiration(today);  Not sure how to setup natural expiration of plant
      }
      if (canopy_growth)                                                                //080725
         reported_LAI_for_self_shading_response =
         canopy_growth->update_LAI_for_self_shading_response((float32)(thermal_time->get_accum_degree_days(true))); //151110_13022 confirmed adjusted
   }
   thermal_time_event();                                                         //970514
   if (roots_vital)
   {  float64 canopy_biomass_vital = get_canopy_biomass_kg_m2_including(include_vital);
      roots_vital->know_above_ground_biomass(canopy_biomass_vital);
      roots_vital->update(terminate_pending);                                    //061208
   }
   // This is act_root_biomass because it is based on today's final canopy biomass.    //010713
     act_root_biomass                                                            //010713
         = soil                                                                  //060615
         ?  roots_current->get_biomass()                                         //060615
         : est_root_biomass();  // <- This is the case for the Crop Calibrator (actually root biomass is not used for Crop calibrator. //060615_
      // The following line allows fast graph to adapt the scale
     float64 root_biomass_produced_today  = roots_current ? roots_current->get_growth_biomass() : 0.0;      //070130
     C_mass_root_est = root_biomass_produced_today * get_carbon_fraction();      ///060818
     #if (defined (CROPSYST_PROPER) || defined(OFOOT_VERSION))
     CS_UED_max_root_biomass_encountered = std::max<float64>(CS_UED_max_root_biomass_encountered,act_root_biomass);
     #endif
   } // NOT FALLOW
}
//_actual_growth_______________________________________________________________/
#if !defined(OLD_ORCHARD) //180622 && !defined(CROPSYST_PROPER)
float64 Crop_complete::distribute_todays_non_leaf_stem_growth(float64 todays_growth) modification_
{
   return todays_growth;  // for normal crops everything goes to leaf stem(branch)
}
#endif
//_distribute_todays_non_leaf_stem_growth___________________________2007-11-20_/
void Crop_complete::check_hardiness()                                            //131104
{
   float64 snow_protection_factor = 0.0;                                         //140625
   #ifdef VIC_CROPSYST_VERSION
           // NYI Need snow pack thickness in weather provider
   #else
   float64 typical_canopy_height_m = 0.2; // could be calculated plant height or parameter
   snow_protection_factor = CORN::must_be_between<float64>
      ((1.0 - snow_pack_thickness / typical_canopy_height_m)
      ,0.0,1.0);
   #endif

   //std::cout << "SPF:" << snow_protection_factor << " SP:" << weather.get_snow_pack_thickness() <<std::endl;
   float64 leaf_damage_cold_temp = parameters->tolerance.temperature_cold_leaf_damage;  //130406
   float64 leaf_lethal_cold_temp = parameters->tolerance.temperature_cold_leaf_lethal;  //130406
   float64 min_temperature = air_temperature_min.Celcius();                      //140512
   if (min_temperature < leaf_damage_cold_temp)
      {  if (!parameters->is_perennial() && (min_temperature < leaf_lethal_cold_temp))
         {  if (!unexpected_termination_date.get_date32())                              //170525_000320
               unexpected_termination_date.set(today);                           //000320
            //180522 unused float64 accum_deg_days = thermal_time->get_accum_degree_days(true);  //151110_130502  //13022 confirmed  adjusted
            if (  (parameters->harvested_part_labeled.get() != grain_part) )     //130502_//000330
                //170524 obs  || (accum_deg_days<parameters->tolerance.salvageable_deg_day)

            {  log_event("Freezing death");
               terminate_pending=true;                                           //040514
               end_season();                                                     //160618
                 Biomass_fate_parameters freezing_fate =                         //040622
                 {  0 // remove for consumption                                  //040622
                 ,  0 // remove for grazing                                      //040815
                 ,  0 // remain_as_residue                                       //040622
                 ,  0 // remove_as_loss                                          //040622
                 ,  0 // remain_standing_dead                                    //040622
                 ,100 // remain_standing_live                                    //040622
                 ,100 // remain_roots_as_dead_residue                            //040622
                 ,  0 // remove_roots_as_loss                                    //040622
                 ,  0 // remain_roots_live                                       //040622
                 ,0 };
                  Crop_mass_fate_biomass_and_nitrogen * fate =                   //070625
                     process_biomass_fate(FREEZING_DEATH_CAUSE                   //040622
                        ,OTHER_BIOMASS_FATE,0,0,0,freezing_fate,true,0.0);
                  if (fate) delete fate;                                         //060323
                  trigger_synchronization(NGS_TERMINATED);                       //040506
                     growth_stage_at_harvest=phenology.growth_stage;             //040604
                     phenology.growth_stage = NGS_TERMINATED;                    //030516
               } else                                                            //000330
               { // Grain crops may still be salvagable, so we dont clear biomass
                  canopy_growth->die_back(1.0);  // kill green area index //000330
                  log_event("Freezing death (grain salvagable)");
               }                                                                 //000330
         } else // not killed but still damagable  (this is always the case for perennials)  //000330
         {
               static const float64 damage_curve_adj = 2.0; // Could make this a parameter.  //081103
               float64 fract_leaf_reduction_due_to_freezing = // 1.0 is full damage
                  (parameters->crop_model_labeled.get()==CROPSYST_ORCHARD_MODEL) //081103
                     // For fruit crops we do not kill  the plant
                     // (it would have to be really cold (I.e. -30 for pomes))
                     // but we do drop the leaves.
                     // We also reduce the maximum potential fruit load
                     // (accounting for the loss of flowers and early fruit growth).
                  ? std::min<float64>                                            //081103
                        (1.0                                                     //081103
                        ,(min_temperature < leaf_damage_cold_temp)               //081103
                           ?pow( (leaf_damage_cold_temp - min_temperature)       //081103
                                /(leaf_damage_cold_temp - leaf_lethal_cold_temp) //081103
                               ,damage_curve_adj)
                           :0.0)                                                 //081103
                  :                                                              //081103
                     ((leaf_damage_cold_temp - min_temperature)
                     /(leaf_damage_cold_temp - leaf_lethal_cold_temp));
               fract_leaf_reduction_due_to_freezing
                  = CORN::must_be_between<float64>(fract_leaf_reduction_due_to_freezing,0.0,1.0);
               fract_leaf_reduction_due_to_freezing *= snow_protection_factor;   //140625
               log_event("Freezing leaf damage");                                //020913
               canopy_growth->die_back(fract_leaf_reduction_due_to_freezing);           //050826
               // may want to remove dead canopy biomass and fate it.
         }
      }

   #if (CROPSYST_VERSION >= 5)
   /*160531 NYI
    #ifdef OLD_ORCHARD
   if (orchard)
      respond_to_freezing_damage(orchard->calc_freezing_damage(min_temperature));//150825
    #endif
    */
   #else
   if (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)
   {  float64 fruit_damage_cold_temp = parameters->param_fruit_damage_cold_temp();
      float64 fruit_lethal_cold_temp = parameters->param_fruit_lethal_cold_temp();
      static const float64 damage_curve_adj = 2.0; // Could make this a parameter. //081103
      float64 fract_fruit_reduction_due_to_freezing =
      // For fruit crops we do not kill  the plant
      // (it would have to be really cold (I.e. -30 for pomes))
      // but we do drop the leaves.
      // We also reduce the maximum potential fruit load
      // (accounting for the loss of flowers and early fruit growth).
      std::min<float64>                                                          //081103
         (1.0                                                                    //081103
         ,(min_temperature < fruit_damage_cold_temp)                             //081103
          ?pow((fruit_damage_cold_temp - min_temperature)                        //081103
            /(fruit_damage_cold_temp-fruit_lethal_cold_temp),damage_curve_adj)   //081103
          :0.0);                                                                 //081103
      fract_fruit_reduction_due_to_freezing
         = CORN::must_be_between<float64>(fract_fruit_reduction_due_to_freezing,0.0,1.0);

      respond_to_freezing_damage(fract_fruit_reduction_due_to_freezing);         //081103
   }
   #endif
}
//_check_hardiness__________________________________________________1999-11-19_/
float64 Crop_complete::damage_GAI(float64 GAI_damage)              modification_
{  return canopy_growth->damage_GAI(GAI_damage);
}
//_2015-12-26__________________________________________________________________/
#if (CROPSYST_VERSION == 4)
#include "yield_V4.cpp"
#endif
//______________________________________________________________________________
Crop_mass_fate_biomass_and_nitrogen *
Crop_complete::harvest_crop
(Harvest_amount_mode harvest_amount_mode                                         //031015
,float64 remove_amount_kg_m2  // if harvest_amount_mode=HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS  else 0.0  //050822
,float64 management_retain_GAI                       // if harvest_amount_mode=HARVEST_RETAIN_GAI else 0.0 //050822
,const Biomass_fate_parameters &harvest_biomass_fate_parameters
,bool terminate)
{  linger_harvest_label = 2; // 4;
   latest_harvest_date.set(today);                                               //171116
   fruit_harvested
      =  (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)
      && (parameters->harvested_part_labeled.get() == fruit_part);               //020409
      // needed to disable latest date to harvest when grapes were harvested
   growth_stage_at_harvest = phenology.growth_stage;                             //130920_040526
   phenology.growth_stage =NGS_HARVEST;                                          //030615
   trigger_synchronization(NGS_HARVEST);                                         //030516
   float64 biomass_for_harvest = biomass_at_maturity;                            //170817
   if (CORN::is_approximately(biomass_for_harvest,0.0,0.000001))                 //140211
   {  // This is for a case where the crop isn't reaching
      // maturity with normal thermal time accumulation and
      // management event has forced harvest before maturity occurs.
      biomass_for_harvest = get_canopy_biomass_kg_m2_including                   //140211
         (include_vital|include_effete);                                         //170817
         // include also effete because potatoes can have
   }

   float64 yield_now = 0.0;
   yield_now =                                                                   //040621
      ((harvest_amount_mode == HARVEST_CROP_PARAMETER_BASED)                     //101101
       && yield)
      ? yield->calculate(biomass_for_harvest)                                    //150825_071120
      : 0.0;
   float64 HI = yield->get_reported_harvest_index();                             //160628


   if (!CORN::is_approximately<float64>(HI,0.0,0.000001) && get_nitrogen())      //160711
   {  float64 HI_N  = pow(HI,(1.0 - 2.0 * (1.0 - HI) * HI));                     //160628
      float64 canopy_N_mass =  get_nitrogen()->get_mass_canopy_current();        //160628
      reported_N_mass_yield = canopy_N_mass * HI_N;                              //160628
   }
//   std::cout << yield_now <<  std::endl;
   Crop_mass_fate_biomass_and_nitrogen *fate =                                   //070625
   process_biomass_fate((Biomass_fated_cause)HARVEST_ONCE,harvest_amount_mode,remove_amount_kg_m2,management_retain_GAI,0.0,harvest_biomass_fate_parameters,terminate,yield_now);



   // total_season_yield is not biomass_fate_season.removed_as_harvest
   if (output_season_tally.transpiration_act > 0.0)                              //180117
   {  //160520 special output
      output_season_tally.water_use_efficiency =
            total_season_biomass_production_output
          / output_season_tally.transpiration_act;
   }
   return fate;                                                                  //060323
}
//_harvest_crop_____________________________________________________2007-06-25_/
bool Crop_complete::start_season(float64 initial_biomass,bool after_dormancy_or_non_dormant_crop)
{  // This is common both to restart (after dormancy)
   // the the apparent start of the season when the crop does not have dormancy.
   bool started = true;                                                          //140822
   delete biomass_fate_season; biomass_fate_season = 0;                          //170628
   if (canopy_growth) canopy_growth->start();                                    //080515
   #ifdef OLD_BIOMASS_GROWTH
   #else
   provide_biomass_growth().start();                                             //180612
   #endif
   water_stress_stats.reset();                                                   //100202
   water_stress_stats.ref_current() = 1.0;                                       //180410_160803
   water_stress_stats.index = 0.0;                                               //180410

   report_temperature_stress_stats.reset();                                      //100202
   report_temperature_stress_stats.ref_current() = 1.0;                          //180410
   report_temperature_stress_stats.index = 0.0;                                  //180410
   days_after_flowering = 0;                                                     //040907
   harvests_this_season = 0;                                                     //040624
   no_more_clippings_this_season = false;                                        //040721
   unclipped_biomass= 0.0;                                                       //010328
   #ifdef NITROGEN
   if (nitrogen) started &= nitrogen->start_season();                            //140822
   #endif
   total_season_biomass_production_output =initial_biomass;  // May need this in start season
   if (after_dormancy_or_non_dormant_crop)
      // Don't trigger this on start of planting because the GP accumulators will be cleared again.
      trigger_synchronization(NGS_RESTART);                                      //050826
   start_period(0);                                                              //160609
   return started;                                                               //140822
}
//_start_season_____________________________________________________2005-08-26_/
void Crop_complete::restart(float64 restart_biomass,float64 restart_GAI,bool use_clump_factor, bool after_dormancy)
{  bool restarted = true;                                                        //150825
   delete biomass_fate_today; biomass_fate_today = 0;                            //170628
   start_season(restart_biomass,after_dormancy);                                 //050826
   // Also note that canopy should have been deleted on onset of dormancy
   // we should not need to clear the canopy biomass
   if (after_dormancy)       // 050826 This line may actually be obsolete because done in start_season() with START_SEASON trigger
      trigger_synchronization(NGS_RESTART);                                      //030606
      // Don't trigger this on start of planting because the GP accumulators will be cleared again.
   trigger_synchronization(NGS_ACTIVE_GROWTH);                                   //030606
   phenology.growth_stage = NGS_ACTIVE_GROWTH;
   is_in_leaf_senescence = false;                                                //121221
   //   when restarting (I.e. after dormancy we now use a higher LAI)            //040908
   reported_LAI_for_self_shading_response = restart_GAI;                         //080728
   reported_peak_LAI = restart_GAI; // LAI_for_self_shading_response;            //040929
   canopy_growth->restart_with(restart_biomass, restart_GAI,use_clump_factor);          //080725
   overall_growth_stress = 1.0;
   restarted &= yield ? yield->reset() : false;                                  //170221_150925
   vapor_pressure_deficit_stats.reset();                                         //030530
   // warning may also want to reset:                                //010726
   //    stress_since_last_harvest_stats although initialized set at harvest
   //    stress_since_emergence_stats although initialized set at emergence
   fruit_harvested = false;                                                      //000626
   phenology.reset(NGS_EMERGENCE);                                               //141202
#ifdef OLD_ORCHARD
   if (fruit_adjusted_parameters) delete fruit_adjusted_parameters;              //081113
      fruit_adjusted_parameters = new Crop_parameters::Fruit(parameters->fruit); //081113
   initial_fruit_growth_date.set_YD(Year(0),CORN::DOY(0));                       //030521
   float64 deg_days_begin_canopy_development = thermal_time->get_accum_degree_days(false); //151110_071121
   if (orchard)
   orchard->set_deg_days_begin_canopy_development(deg_days_begin_canopy_development);//071121
   limit_max_LAI = false;                                                        //081101
#endif
   #ifdef NITROGEN
   if (nitrogen) nitrogen->restart( restart_biomass,restart_GAI, use_clump_factor, after_dormancy);   //020505
   #endif
   output_season_tally.transpiration_act = 0;
   if (parameters->life_cycle_labeled.get() != annual_life_cycle)                //180822
      thermal_time->clear_accum_degree_days();                                   //180522

   // NYI return restarted;                                                      //150825
}
//_restart_____________________________________________________________________/
bool Crop_complete::start_day()
{  bool started_day = true;                                                      //140717

   attainable_top_growth = 0;                                                    //180111
   #ifdef CO2_CHANGE
   // weather maintains the atmospheric CO2 concentration
   if (CO2_response)                                                             //090316
   {
      CO2_response->update();    // this should only be done when CO2 changes (and first day of simulation)
      //  Note that calc_responses really only need to be called when CO2 changes
   }
   #endif
   float64 LWP_yesterday = transpiration->get_leaf_water_pot();
   canopy_growth->know_LWP_yesterday(LWP_yesterday);                             //110901
   canopy_growth->start_day();                                                   //080801
   roots_current ? roots_current->start_day() : true;                            //150601
      // Nitrogen needs roots updated
   #ifdef NITROGEN
   if (nitrogen)
   {  nitrogen->start_day();
      N_mass_canopy_recorded_before_harvest= nitrogen->get_mass_canopy_current();//131007
   }
   #endif
   //  Biomatter fate is used for output, if nothing has
   //  used it by the end of the yesterday, we can dump it.                      //040623
   delete biomass_fate_today; biomass_fate_today = 0;                            //170628
   C_mass_canopy_est = 0;                                                        //110915
   C_mass_root_est = 0;                                                          //110915

   // Need to synchronize first so that the date is set
   // before going into scheduling (done in start day)
   as_event_scheduler_crop->synchronize_thermal_time                             //150930
      (thermal_time->get_accum_degree_days(false)                                //180615
         // Claudio says this should be the complete season DD.
         //160815 (true /*must be adjusted for clipping!*/)
      );

   started_day &= Crop_common::start_day();                                      //150930
   #ifdef OLD_PHENOLOGY_SEQUENCER
      started_day &= phenology.start_day();                                      //140717_130903
   #else
      started_day &= Phenology_sequencer::start_day();                           //140717
   #endif
   // Crop calibrator does not need roots                                          061212

   //Moved here 180111
   float64 accum_deg_days_adjusted_for_clipping = thermal_time->get_accum_degree_days(true);  //151110_100730  //130822 confirmed
   before_WUE_change                                                             //080721
      = !parameters->has_leaf_senescence() // 100729 (Not sure if has_leaf_senescence is needed, it so probably should hide the WUE_changes checkbox in the crop editor.
         || (parameters->biomass_production.WUE_changes &&                       //110218_100729
             (accum_deg_days_adjusted_for_clipping <= parameters->phenology.WUE_change));  //100730
   #ifdef CROP_ORCHARD
   #ifndef CROP_CALIBRATION
   if (is_at_max_fruit_load())                                                   //081103
      before_WUE_change = true;                                                  //081103
   #endif
   #endif
   act_transpiration_m        = 0.0;                                             //180404
   report_transpiration_act_m = 0.0;                                             //180404
   return started_day;
}
//_start_day________________________________________________________2004-02-06_/
bool Crop_complete::end_day()
{
   commit_biomass_fate();                                                        //180530
      // was called by land_unit_sim 180530
   reported_GAI = canopy_growth->get_GAI(include_vital|include_effete);                //050823
   reported_LAI = canopy_growth->get_LAI();                                             //160627
   reported_canopy_cover_green = (float32)get_fract_canopy_cover_green();        //160629
   //NYI reported_canopy_cover_total = (float32)get_fract_canopy_cover_total();  //160629
   reported_canopy_cover_max = std::max<float32>                                 //180413
      (reported_canopy_cover_green,reported_canopy_cover_max);                   //180403

   thermal_time->end_day();                                                      //140619
#ifdef NITROGEN
   if (nitrogen) nitrogen->end_day();
#endif
/*NYN
#ifndef OLD_PHENOLOGY_SEQUENCER
   Phenology_sequencer::end_day();
#endif
*/

   // Special output 10520
      output_season_tally.Srad.append(solar_radiation.get_MJ_m2());
      output_season_tally.Tmax.append(air_temperature_max.Celcius());
      output_season_tally.Tmin.append(air_temperature_min.Celcius());
      output_season_tally.Tavg.append(air_temperature_avg.Celcius());
      //already have in GS accum output_season_tally.VPD_daytime.append(daytime_vapor_pressure_deficit.get_kPa());
      output_season_tally.transpiration_act += act_transpiration_m; //This should be actual transpriation
      // Special outputs                                                         //160519
      nat16 days_since_start_of_flowering =  ref_phenology()
            .get_days_since_start_of(NGS_ANTHESIS) ;
   if (days_since_start_of_flowering <= 7)
   {
      if (!output_season_tally.window_14_days_achieved  )                        //160509
      {  // 7 day window on either side of start of flowering
         // (include period before and after start of flowering)
         //const CS::Weather_hours *hourly_weather = meteorology.provide_hourly();
         //if (hourly_weather)
         // stress_adj_hourly_temperature
         {
            report_degree_hours_above_30_today = 0;
            report_degree_hours_above_34_today = 0;
            for (CORN::Hour hour = 0; hour < 24; hour++)
            {

               float64 temperature_hour = 0;
               // temperature_hour = hourly_weather->get_air_temperature(hour);
               temperature_hour = stress_adj_hourly_temperature.get(hour);

//if (temperature_hour > 30.0)
//std::clog << "reached" << std::endl;

               float64 degree_hours_30 = (temperature_hour < 30.0) ? 0.0 : temperature_hour - 30.0;
               report_degree_hours_above_30_today += degree_hours_30;
               float64 degree_hours_34 = (temperature_hour < 34.0) ? 0.0 : temperature_hour - 34.0;
               report_degree_hours_above_34_today += degree_hours_34;
            }
//std::cout << "dh30:" << output_degree_hours_above_30_today << " dh34:" << output_degree_hours_above_34_today << std::endl;

            output_season_tally.degree_hours_above_30_flowering.append(report_degree_hours_above_30_today);
            output_season_tally.degree_hours_above_34_flowering.append(report_degree_hours_above_34_today);
            if (output_season_tally.degree_hours_above_30_flowering.get_count() >= 14)
            {
               output_season_tally.window_14_days_achieved = true;
// std::cout << "dh30:" << output_season_tally.degree_hours_above_30_flowering.sum_last(14) << std::endl;
// std::cout << "dh34:" << output_season_tally.degree_hours_above_34_flowering.sum_last(14) << std::endl;
            }
         }
      } else // continue to add values/days to the progressive.
        output_season_tally.degree_hours_above_30_flowering.append(0.0);
   }

   float64 soil_evap_act = soil->ref_evaporator()
      ? soil->ref_evaporator()->get_evaporation_actual_day() : 0;
   reported_ET_act_m                                                             //171031
   = soil_evap_act                                                               //171031
     + (ref_residues                                                             //171031
       ?ref_residues->get_act_evaporation() : 0.0)                               //171031
     + report_transpiration_act_m;                                               //171031

   // Update roots was previously specifically called by land_unit_sim           //180530
   #ifdef OLD_ROOTS
         CROP_ROOT update_root_depth(soil_rooting_depth,total_soil_depth );      //180530
   #else
   #ifndef CROP_CALIBRATION
         CROP_ROOT update_root_depth(terminate_pending);                         //180530
   #else
         0.0;
   #endif                                                                        //180530
   #endif
   return Crop_common::end_day();                                                //151016
}
//_end_day__________________________________________________________2007-02-27_/
void Crop_complete::consider_inactive_period
(float64 avg_temperature)       // daily temp with est. night time temps.
{
#ifdef OLD_ORCHARD
//071120 moved to Crop_fruit
#ifdef FRUIT_CROP_MODEL
   if (fruit_bud_break_requirement)                                              //021125
   { if (fruit_bud_break_requirement->satisfied                                  //040830
         (!fruit_chill_requirement,thermal_time->get_accum_degree_days(false)))  //151110
            // confirmed not adjusted                                            //13022
       {                                                                         //021125
         linger_budbreak_label = 3;                                              //030523
         phenology.growth_stage = NGS_ACTIVE_GROWTH;                             //030523
         is_in_leaf_senescence =false;                                           //121221
         trigger_synchronization(FGS_BUD_BREAK);                                 //030523
         restart_after_inactive_period();                                        //021202
         log_event("Bud break");
//180612 abandoned         initiate_emergence();                                                   //180608
         bud_break_date.set(today);                                              //081013
         delete fruit_bud_break_requirement;                                     //021125
         fruit_bud_break_requirement = 0;                                        //021125
       }                                                                         //021125
   }                                                                             //021125
#endif
#endif
   if (quiescence_end_requirement)                                               //021202
   {  if (quiescence_end_requirement->is_satisfied())                            //021202
      {                                                                          //030512
         if (quiescence_end_requirement)                                         //030512
            delete quiescence_end_requirement;                                   //030512
         quiescence_end_requirement = 0;
         inactive_end_date.set(today);                                           //081013
         is_in_leaf_senescence = false;                                          //121221
#ifdef FRUIT_CROP_MODEL
         if (parameters->harvested_part_labeled.get() == fruit_part)             //080910
         {  //fruit_harvested = false;
            // For fruit trees we dont go into active growth until bud break;
            phenology.growth_stage=NGS_RESTART;                                  //130925
            fruit_bud_break_requirement = new Fruit_bud_break_requirement        //030523
               (parameters->dormancy.deg_day_bud_break_chill_req_sat
               ,parameters->dormancy.deg_day_bud_break_chill_req_not_sat);       //030515
         } else                                                                  //030515
#endif                                                                           //030514
         {
            phenology.growth_stage=NGS_ACTIVE_GROWTH;                            //130902_030523
            restart_after_inactive_period();                                     //021202
         }
      }
      else { quiescence_end_requirement->add_daily_temperature(avg_temperature);      //021202
      }
   }
   if (quiescence_start_requirement                                              //021202
      && (phenology.growth_stage>=NGS_ACTIVE_GROWTH))                            //130902
      // ACTIVE_GROWTH check is needed otherwise we may start looking
      // for end season before we are even growing.                              //080401
   {  // We are at start of dormancy
      if (quiescence_start_requirement->is_satisfied())                          //021202
      {
         log_event("Dormancy or inactive period begins" );
         delete quiescence_start_requirement; quiescence_start_requirement = 0;  //030514
         bool dormancy_condition
            = (parameters->season_dormancy_mode_labeled.get()==dormancy_season); //080401
         #ifdef OLD_ORCHARD
         if (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)     //030523
         {  fruit_harvested =false;                                              //030529
            delete fruit_chill_requirement;// but just in case                   //030514
            fruit_chill_requirement = new Fruit_chill_requirement                //030514
               (parameters->dormancy.chill_hours);
         }                                                                       //030529
         /* now always
         else                                                                    //030523
            if (dormancy_condition)                                              //080331
               start_normal_crop_dormancy();                                     //030523
         #else
            if (dormancy_condition)                                              //080331
               senesce_at_dormancy();                                            //071120
         */
         #endif

         if (dormancy_condition)                                                //180701_080331
         #ifdef OLD_ORCHARD
               start_normal_crop_dormancy();                                     //030523
         #else
               senesce_at_dormancy();                                            //071120
         #endif
         start_inactive_period(dormancy_condition);                              //080401
         setup_quiescence_end_requirement(today.get_DOY());                      //071120
      }                                                                          //021202
      else                                                                       //021202
         quiescence_start_requirement->add_daily_temperature                     //160326_021202
            (today.get_DOY(),temperature_with_est_night.Celcius());              //150122
   };                                                                            //021202
#ifdef OLD_ORCHARD
//071120 moved to Crop_CropSyst_fruit
#ifdef FRUIT_CROP_MODEL
   if (fruit_chill_requirement)                                                  //021125
   {  if (fruit_chill_requirement->is_satisfied())                               //021125
      {
         log_event("Chill requirement satisfied");
         chill_requirement_satisfied_date.set(today);                            //081013
         linger_chill_satisfied_label = 2;                                       //030529
         delete fruit_chill_requirement;                                         //021125
         fruit_chill_requirement = 0;                                            //021125
         if (parameters->harvested_part_labeled.get() == fruit_part)                //190424
         {
            fruit_bud_break_requirement = new Fruit_bud_break_requirement
               (parameters->dormancy.deg_day_bud_break_chill_req_sat
               ,parameters->dormancy.deg_day_bud_break_chill_req_not_sat);

            thermal_time->clear_accum_degree_days();                            //190726LML
         }

      } else
      { //I still need to move est_temperature object to crop from thermal time class  //021125
         for (Hour hr = 0; hr < 24; hr++)                                        //050816
         {  float64 air_temperature_hour=ref_hourly_weather->get_air_temperature(hr);//080908
            fruit_chill_requirement->add_hour_temperature(air_temperature_hour); //050816
            //std::clog << " year:" << int(today.get_year()) << " doy: " << int(today.get_DOY())
            //          << " temp hr[" << int(hr) << "]:" << air_temperature_hour 
            //          << " fruit_chill_requirement:" <<  fruit_chill_requirement->get_chill_hours_remaining() 
            //          << " avg_temperature:" << avg_temperature << "\n";
         }
      }
   }
#endif
#endif
}
//_consider_inactive_period_________________________________________2002-06-26_/
void Crop_complete::restart_after_inactive_period()
{  // Set up conditions to check for start of next dormancy period.
   delete quiescence_start_requirement; // <- should not occur 021202            //160326
   quiescence_start_requirement = new Quiescence_start_requirement               //160326_021202
      ((parameters->quiescence)                                                  //160326_080331
      ,(parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL));
   intercepted_radiation_season_accum         = 0.0;                             //080429
   season += 1;                                                                  //030613
   harvests_this_season = 0;                                                     //040625
   no_more_clippings_this_season = false;                                        //040721
   phenology.start_date[NGS_RESTART].set(today);                                 //141202
      // we split the perennial growing period in to growing seasons (for output only).  990413
      log_event(TL_Dormancy_ends);

#ifndef CROP_CALIBRATION
// CropCalibrate currently does not handle perennials
   if (roots_dormant)  // 080401 Note that there are only roots_dormant in the case of dormancy 070131
   {  // This must be done before we call restart becase N restart uses the new vital roots
      // Send the dormant roots to biomass fate
      Crop_mass_fate *fate_now = new Crop_mass_fate
         (DORMANCY_CAUSE,0/*no canopy*/,roots_dormant->get_biomass());
      for (nat8 layer = 1; layer <= MAX_soil_layers; layer++)                    //070131
      {
         fate_now->roots_dead[layer] = roots_dormant->get_biomass_in_layer(layer);
         // all these effet roots are now considered dead, no live roots recorded in fate
      }
      Crop_biomass no_canopy_biomass_removed; // None in this case, just roots   //070412
      //dont currently do anything with the total biomass removed
      record_biomass_fate(*fate_now,0/*,false*/);
      #ifdef NITROGEN
      if (nitrogen) //180615
      {
      Crop_mass_fate *N_mass_fate_now = nitrogen->render_N_fate(DORMANCY_CAUSE,0,0); //131005
      //180615if (nitrogen)
      nitrogen->apportion_fate
         (*fate_now,N_mass_fate_now,no_canopy_biomass_removed,false,include_effete);
      }
      #endif
      delete fate_now;
      if (!roots_vital)                                                          //070131
      {
         // create a new roots_vital at the current dormant root depth.
         // Note that biomass will instantly be created in this case.
         // If we at some time we decide to have a detailed external mass balance of roots,
         // this will need to be adjusted here.
         // The root mass balance is otherwise maintained for the season only.
         roots_current = roots_vital =
            /*180626 obsolete
            #if (CROPSYST_VERSION == 4)
            (parameters->data_source_version.get_number() < 0x041200)            //130625
            ?  dynamic_cast<CropSyst::Crop_root_vital *>(new CropSyst::Crop_root_vital_V4
               (parameters->root
               ,parameters->phenology                                            //080722
               ,(*thermal_time)                                                  //151110
               ,*soil->ref_layers()
               ,roots_dormant->get_root_length()))                               //070214
            :
            #endif
            */
            dynamic_cast<CropSyst::Crop_root_vital *>(new CropSyst::Crop_root_vital_V5
               (parameters->root                                                 //130625
               ,parameters->phenology
               ,(*thermal_time)                                                  //151110
               ,*soil->ref_layers()
               ,roots_dormant->get_root_length()));
         roots_vital->update(false); // Needed to get the new biomass by layer   //070312
      }  // else we already have vital roots then just keep them.
      delete roots_dormant;
      roots_dormant = 0;
   }
#endif
   float64 restart_GAI = (fall_sowing && season == 1) ? 0.1 :  0.25;             //070320
   restart_GAI = std::max<float64>(restart_GAI,get_GAI_vital_plus_effete());     //070320
   restart(0.005,restart_GAI,false,true);                                        //040914
      // Thermal time is now cleared at start of dormancy,
      // it is accumulated during dormancy inorder to get bud break.
      // about 20 days of consecutive 0 thermal time will reset the thermal time.//030517
      // Claudio does want thermal time reset at end of dormancy.                //030521
   initiate_emergence();   
   if (parameters->harvested_part_labeled.get() == fruit_part)                   //000626
   {  thermal_time->clear_accum_degree_days();                                   //151110
   }
   trigger_synchronization(NGS_RESTART);                                         //030516
   //May need to trigger also active growth                                      //040512
}
//_restart_after_inactive_period____________________________________1997-02-19_/
bool Crop_complete::initiate_emergence()
{
   #ifdef OLD_BIOMASS_GROWTH
   // was hard method
   // preserved in V4 but could be replaced as in V5

   #else
/*180403 Obsolete Claudio decided to not have this model in CropSyst

   #ifdef LIU_XIAO_CROP
   // Currently I just replace the selected canopy model
   // with no selected option in the parameter file.
   if (parameters->parameters_Liu_Xiao)                                           //180118
   {
      delete canopy;
      Liu_Xiao::Canopy_growth *Liu_Xiao_canopy_growth = new Liu_Xiao::Canopy_growth
         ( (*parameters->parameters_Liu_Xiao)
         , parameters->morphology
         , air_temperature_avg, today);
      canopy  = Liu_Xiao_canopy_growth;
      Liu_Xiao::Biomass_growth *Liu_Xiao_biomass_growth = new Liu_Xiao::Biomass_growth
         (*parameters->parameters_Liu_Xiao
         ,*canopy
         ,air_temperature_max
         ,air_temperature_avg
         ,solar_radiation
         ,(CO2_current_conc_optional ? CO2_current_conc_optional->ppm() : 360)
         ,today);
      biomass_growth =Liu_Xiao_biomass_growth ;
   } else
   #endif
*/
/*180612 moved to provide_biomass_growth
   biomass_growth = new Biomass_growth_RUE_TUE                                   //180111
      (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL
      ,parameters
      ,phenology.growth_stage
      ,season
      ,pot_transpiration_m
      ,thermal_time
      ,CO2_response
      ,canopy
      ,air_temperature_avg
      ,solar_radiation
      ,intercepted_radiation
      #ifdef YAML_PARAM_VERSION
      // Using adjustable parameter idiom
      ,transpiration_dependent_growth
      #else
      ,transpiration_dependent_growth
      #endif
      ,report_temperature_stress_stats
      ,at_max_fruit_load                                                         //180308
      );
   biomass_growth->start();                                                      //180111
*/

   provide_biomass_growth().start();                                            //180612

   #endif

   #ifdef OLD_PHENOLOGY_SEQUENCER
   if (!emerged)                                                                 //000719
   {  log_event(TL_Active_Growth);                                               //000719
      float64 initial_biomass = parameters->canopy_growth_LAI_based.initial_GAI
         / parameters->canopy_growth_LAI_based.specific_leaf_area;               //000207
      restart(initial_biomass
             ,parameters->canopy_growth_LAI_based.initial_GAI,true,false);       //040909
      roots_vital->know_above_ground_biomass(initial_biomass);                   //130625
      phenology.start_date[NGS_EMERGENCE].set(today);                            //141202
      trigger_synchronization(NGS_EMERGENCE);
      trigger_synchronization(NGS_ACTIVE_GROWTH);
      if (parameters->vernalization.enabled)                                     //111109
         thermal_time->enable_vernalization(parameters->vernalization);          //151109_111109
   }
   emerged = true;
   return emerged;                                                               //140812
   #else
   bool just_emerged = Phenology_sequencer::initiate_emergence();                //140619
   if (just_emerged)                                                             //140619
   {
      float64 initial_biomass = parameters->canopy_growth_LAI_based.initial_GAI
         / parameters->canopy_growth_LAI_based.specific_leaf_area;               //000207
      restart(initial_biomass,parameters->canopy_growth_LAI_based.initial_GAI,true,false);   //040909
      roots_vital->know_above_ground_biomass(initial_biomass);                   //130625
      trigger_synchronization(NGS_EMERGENCE);
      trigger_synchronization(NGS_ACTIVE_GROWTH);
      if (parameters->vernalization.enabled)                                     //111109
      {
         thermal_time->enable_vernalization(parameters->vernalization);          //111109
      }
   }
   return just_emerged;
   #endif
}
//_initiate_emergence_____________________________________________________2000_/
bool Crop_complete::initiate_tuber()
{
   #ifdef OLD_PHENOLOGY_SEQUENCER
   if (parameters->harvested_part_labeled.get()  == tuber_part)
   {
      log_event(TL_Tuber_initiation);
      phenology.start_date_tuber_initiation.set(today);                          //141217
   }
   return true;
   #else
   return Phenology_sequencer::initiate_tuber();
   #endif
}
//_initiate_tuber______________________________________________________________/
bool Crop_complete::initiate_flowering()
{
   bool event_began = true;
   trigger_synchronization(NGS_ANTHESIS);                                        //151020
  #ifdef OLD_PHENOLOGY_SEQUENCER
   if (phenology.growth_stage != NGS_FILLING)                                    //081110
   {
      phenology.growth_stage = NGS_ANTHESIS;                                     //081110
      trigger_synchronization(NGS_ANTHESIS);
      phenology.start_day_in_season[NGS_ANTHESIS] = phenology.days_in_season;
   }
   // In the case of tuber, there could be filling before flowering
   log_event(TL_Begin_flowering);
   phenology.start_date[NGS_ANTHESIS].set(today);                                //141202
  #else
   event_began = Phenology_sequencer::initiate_flowering();
   #endif
   return event_began;
}
//_initiate_flowering__________________________________________________________/
bool Crop_complete::initiate_senescence()
{
   bool senesence_started = canopy_growth->start_senescence();                          //141121_130610

   if (nitrogen)                                                                 //160417
       nitrogen->know_start_senescence();                                        //160408
   //NYN senescence_date.set(today);                                             //001115 ?* NYI */
   #ifdef OLD_PHENOLOGY_SEQUENCER
   log_event("Begin senescence");
   return senesence_started;
   #else
   return senesence_started                                                      //141121
       && Phenology_sequencer::initiate_senescence();
   #endif
}
//_initiate_senescence______________________________________________2012-12-21_/
bool Crop_complete::initiate_max_canopy()
{
   canopy_growth->start_culminescence();                                                //141124
   trigger_synchronization(NGS_END_CANOPY_GROWTH);
   #ifdef OLD_PHENOLOGY_SEQUENCER
   log_event("Maximum canopy");
   return true;
   #else
   return Phenology_sequencer::initiate_max_canopy();
   #endif
}
//_initiate_max_canopy______________________________________________2013-04-49_/
bool Crop_complete::initiate_filling()
{
   biomass_at_filling = get_canopy_biomass_kg_m2_including(include_vital) ;      //131022
   yield->know_biomass_at_filling(biomass_at_filling);                           //150826
   trigger_synchronization(NGS_FILLING);                                         //130902
   #ifdef OLD_PHENOLOGY_SEQUENCER
   phenology.growth_stage = NGS_FILLING;                                         //130902
   log_event(TL_Grain_filling);
   phenology.start_date[NGS_FILLING].set(today);                                 //141202
   return true;
   #else
   return Phenology_sequencer::initiate_filling();                               //140620
   #endif
}
//_initiate_filling_________________________________________________2002-08-09_/
bool Crop_complete::initiate_maturity()
{
   biomass_at_maturity  =  get_canopy_biomass_kg_m2_including(include_vital) ;
   yield->know_biomass_at_maturity(biomass_at_maturity);                         //150826
   trigger_synchronization(NGS_MATURITY);                                        //130902
   #ifndef OLD_BIOMASS_GROWTH
   // preserved in V4 but could be replaced as in V5
   if (!(parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL))        //180111
   {  delete biomass_growth;                                                     //180111
      biomass_growth = 0;                                                        //180111
   }                                                                             //180111
   #endif
   #ifdef OLD_PHENOLOGY_SEQUENCER
   phenology.growth_stage = NGS_MATURITY;                                        //130902
   log_event(TL_Maturity);
   phenology.start_date[NGS_MATURITY].set(today);                                //141202
   return true;
   #else
   return Phenology_sequencer::initiate_maturity();                              //140620
   #endif
}
//_initiate_maturity___________________________________________________________/
Crop_mass_fate_biomass_and_nitrogen *
Crop_complete::harvest
(
 float64 remove_amount_kg_m2                                                     //050822
,const CropSyst::Harvest_or_clipping_operation_struct                            //140811
   *_harvest_or_clipping_params
,bool terminate                                                                  //140811
)
{  Crop_mass_fate_biomass_and_nitrogen *result_fate = 0;                         //070625
   CropSyst::Harvest_or_clipping_operation_struct                                //140811
      *harvest_or_clipping_params                                                //120419_060612
   =  _harvest_or_clipping_params
   ?  (CropSyst::Harvest_or_clipping_operation_struct *)                         //140811
      _harvest_or_clipping_params                                                //120419
   : new
      CropSyst::Harvest_or_clipping_operation_struct;                            //140811
   if (!_harvest_or_clipping_params)                                             //060612
   {  //  harvest_or_clipping_params were not specified, so use defaults
      harvest_or_clipping_params->biomass_fate_percents.remove_for_use                = 0;
      harvest_or_clipping_params->biomass_fate_percents.remove_for_grazing            = 0;
      harvest_or_clipping_params->biomass_fate_percents.remain_as_residue             = 0;
      harvest_or_clipping_params->biomass_fate_percents.remove_for_disposal           = 0;
      harvest_or_clipping_params->biomass_fate_percents.remain_as_dead                = 100.0;
      harvest_or_clipping_params->biomass_fate_percents.remain_as_live                = 0;
      harvest_or_clipping_params->biomass_fate_percents.remove_roots_to_dead_residue  = 100;
      harvest_or_clipping_params->biomass_fate_percents.remain_roots_live             = 0;
      harvest_or_clipping_params->biomass_fate_percents.remove_roots_as_loss          = 0;
      harvest_or_clipping_params->biomass_fate_percents.return_as_manure              = 0;
   }
   if (!fruit_harvested)                                                         //070711
   {
   Biomass_fated_cause biomass_fate_cause = (Biomass_fated_cause)HARVEST_CLIPPING;
   Harvest_amount_mode harvest_amount_mode
      = harvest_or_clipping_params->harvest_amount_mode;                         //051105
   float64 management_retain_GAI =
      (harvest_amount_mode== HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS)                //150223
         ? harvest_or_clipping_params->min_retain_GAI                            //051105
         : 0.0;                                                                  //150223
      if (terminate )                                                            //040914
          biomass_fate_cause = (Biomass_fated_cause)HARVEST_LAST_CLIPPING;
      if (harvest_or_clipping_params->biomass_fate_percents.remove_for_grazing >  0)
          biomass_fate_cause = (Biomass_fated_cause)HARVEST_GRAZE;
   result_fate =                                                                 //070625
    ((parameters->applies_harvest_index()
     && (biomass_fate_cause != (Biomass_fated_cause)HARVEST_GRAZE))
         ||  (harvest_amount_mode==HARVEST_CROP_PARAMETER_BASED) )               //090922_050822_ I had this as 'or'
      ?  harvest_crop(harvest_amount_mode,remove_amount_kg_m2,management_retain_GAI //980924
         ,harvest_or_clipping_params->biomass_fate_percents                      //051105
         ,terminate)
      :  process_biomass_fate
         (biomass_fate_cause
         ,harvest_amount_mode,remove_amount_kg_m2,management_retain_GAI          //050823
         ,per_ha_to_per_m2(harvest_or_clipping_params->reserve_biomass_kg_ha)    //110603
         ,harvest_or_clipping_params->biomass_fate_percents                      //051105
         ,terminate,0.0); // no harvest index
   if (terminate)                                                                //030516
   {  // just trigger termination                                                //040506
      end_season();                                                              //160618
      trigger_synchronization(NGS_TERMINATED);                                   //040506
      terminate_pending=true;                                                    //040514
      reported_LAI_for_self_shading_response = 0.0;
      // we dont need to respond  to clipping, because we are going to terminate.
   } else                                                                        //040506
      if (parameters->crop_model_labeled.get() != CROPSYST_ORCHARD_MODEL)        //041228
         //  Fruit crops dont loose leaves
         respond_to_clipping();                                                  //051103
   if (!_harvest_or_clipping_params)
   {
      delete harvest_or_clipping_params;                                         //060612
      harvest_or_clipping_params = 0;                                            //140430
   }
      // Delete these if we create a default set of parameters
   }
   return result_fate;                                                           //020311
}
//_harvest__________________________________________________________2007-06-25_/
bool Crop_complete::respond_to_clipping()                          modification_
{  harvests_this_season += 1;                                                    //040624
   latest_harvest_date.set(today);                                               //110824_001115
   trigger_synchronization(NGS_HARVEST);                                         //130902
   days_after_flowering = 0;
// Reseting to emergence deg day is not going to work.
// because if we clip every day, leaves will not accumulate thermal time
//                   float64 reset_thermal_time = parameters->thermal_time_parameters.emergence_deg_day;
      //trying to reset some time between flowering and emergence
       //(parameters->thermal_time_parameters.emergence_deg_day + parameters->thermal_time_parameters.begin_flowering_deg_day)/2.0;

   if (phenology.growth_stage < NGS_MATURITY)  // We dont activate  after maturity or dormancy //041221
   {  if (parameters->phenology.clipping_resets)                                 //041221
      {  float64 reset_thermal_time =parameters->phenology.initiation.emergence; //040830
         Canopy_growth_cover_based *canopy_growth_cover_based
            = dynamic_cast<Canopy_growth_cover_based *>(canopy_growth);          //130512
         if (canopy_growth_cover_based)                                          //130512
         {


canopy_growth->start(); //810718
// setting to 0 for test if GAI recovers, the make sure clipping sets these values accordingly
/*
canopy_growth_cover_based->cover_unstressed_green = 0;
canopy_growth_cover_based->global_soard_rad_intercepthed_green_canopy = 0;
canopy_growth_cover_based->global_soard_rad_intercepthed_green_canopy_yesterday = 0;
*/
//canopy_growth_cover_based->


            reset_thermal_time=canopy_growth_cover_based->get_thermal_time_for_reset();//130512
         }
         thermal_time->reset_to(reset_thermal_time);                             //151110_040830
         trigger_synchronization(NGS_ACTIVE_GROWTH);                             //130902
         phenology.growth_stage = NGS_ACTIVE_GROWTH;                             //130902_040719

         // make vital effete
         // This was added for Fabio's sugar cane where there is no dormancy.
         // We need to move vital to effete otherwise the recovery dynamics
         // show that there is vital GAI/biomass so recovery dynamics is low.

         canopy_growth->vital_becomes_effete(false);    //180718


         is_in_leaf_senescence = false;                                          //121221
      } else
      {  // if this is an annual (or biannual)
         thermal_time->respond_to_clipping                                       //151110
            (parameters->phenology.initiation.emergence);                        //080722
         //  and during flowering, then
         if ((phenology.growth_stage == NGS_ANTHESIS)
          || (phenology.growth_stage == NGS_FILLING))                            //130902
         {  // clear deg day for flowering and deg day for filling
            // the flowering part 040826
            parameters->phenology.initiation.filling = 0;                        //040826
            parameters->phenology.initiation.flowering = 0;                      //040826
            trigger_synchronization(NGS_ACTIVE_GROWTH);                          //130902
            phenology.growth_stage = NGS_ACTIVE_GROWTH;                          //130902_040719
         } // else perennials are allowed to remain in their current growth stage, but the stage may be extended. 040826
      }
   }
   return canopy_growth->respond_to_clipping();                                         //110824_080515
}
//_respond_to_clipping______________________________________________2004-07-19_/
#ifdef OLD_BIOMASS_GROWTH
   // preserved in V4 but could be replaced as in V5
float64 Crop_complete::calc_RUE_temperature_limitation()                       const
{  float64 TSF = 1.0; // RUE_temperature_limitation_factor
   float64 min_tolerable_temperature = parameters->biomass_production.min_tolerable_temp;
   float64 max_tolerable_temperature = parameters->biomass_production.max_tolerable_temp;
   float64 low_optimum_temperature   = parameters->biomass_production.low_threshold_limit_temp;
   float64 high_optimum_temperature  = parameters->biomass_production.high_threshold_limit_temp;
   if (   (air_temperature_avg <= min_tolerable_temperature)
       || (air_temperature_avg >= max_tolerable_temperature))
      TSF = 0.00000001 ; // full limitation (avoid div0)
   else if
      (   (air_temperature_avg >= low_optimum_temperature)
       || (air_temperature_avg <= high_optimum_temperature))
      TSF = 1.0;
   if (   (air_temperature_avg < low_optimum_temperature)
       && (air_temperature_avg > min_tolerable_temperature))
      TSF = 1.0 - (  (low_optimum_temperature - air_temperature_avg)
                   / (low_optimum_temperature - min_tolerable_temperature));
   if (   (air_temperature_avg > high_optimum_temperature)
       && (air_temperature_avg < max_tolerable_temperature))
      TSF = (max_tolerable_temperature - air_temperature_avg)
           /(max_tolerable_temperature - high_optimum_temperature);
   if (TSF > 1.0)      TSF = 1.0;       // No limitation   //011016
   if (TSF <= 0.01)    TSF = 0.00000001;// full limitation //011016
   return TSF;
}
//_calc_RUE_temperature_limitation______________________2016-02-04__2013-05-13_/

//180111 Moved to biomass_growth_RUE_TUE.cpp

float64 Crop_complete::calc_attainable_top_growth()
{
   #ifdef CO2_CHANGE
   // Move this to caller
   if (CO2_response)
   {
      CO2_TUE_adjustment
      =  (canopy_growth->global_solar_rad_intercepted_green_canopy() > 0.0000001)       //151030
         ? CO2_response->get_TUE_adjustment()                                    //151030
         : 1.0;
      float64 CO2_transpiration_adjustment_factor
         = CO2_response->get_transpiration_adjustment_factor();                  //110913
      pot_transpiration_m[1/*CO2_adjusted*/] *= CO2_transpiration_adjustment_factor;//151031
   } // else no adjustments applied
   #endif


   at_max_fruit_load = is_at_max_fruit_load();                                   //180308
   RUE_temperature_limitation_factor = calc_RUE_temperature_limitation();        //130513
   // WUE = Water Use Efficiency

   float64 solar_rad = solar_radiation.get_MJ_m2();                              //140813_131104
   float64 radiation_dependent_growth = 0.0;                                     //080428
   if (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)           //080821
      RUE_temperature_limitation_factor = 1.0;                                   //080821
   // This mode is for compatibility with previous versions
   #if (CROPSYST_VERSION < 5)
   // obsolete in version 5  (deprecated in V5)
   if (parameters->biomass_production.RUE_basis == photosynthetically_active_radiation)   //11080??_080428
   {  float64 RUE_PAR = g_to_kg(get_radiation_use_efficiency_PAR());             //110906
      float64 GAI_fract_canopy_cover_for_PAR
      = canopy_growth->get_PAR_solar_rad_intercepted_green_canopy(phenology.growth_stage);//110902
      float64 photosynthetic_active_radiation = (solar_rad/2.0);   // MJ/m2 ?
      intercepted_radiation = photosynthetic_active_radiation * GAI_fract_canopy_cover_for_PAR; //was intercepted_PAR
      float64 intercepted_PAR_dependent_growth = RUE_PAR * intercepted_radiation;
      radiation_dependent_growth = intercepted_PAR_dependent_growth;
   } else
   #endif
   {
      // based on global radiation
      float64 RUE_global = g_to_kg(get_radiation_use_efficiency_global());       //110906_080428
            // This is adjusted for CO2
            // actually converts from g/MJ to kg/MJ
      float64 GAI_fract_canopy_cover                                             //080428
         = canopy_growth->get_global_solar_rad_intercepted_green_canopy(phenology.growth_stage);
      float64 global_radiation = (solar_rad);  // MJ/m2 ?                        //080428
      intercepted_radiation = global_radiation * GAI_fract_canopy_cover;         //080428
      radiation_dependent_growth = intercepted_radiation * RUE_global;           //080428 kg/m2
   }
   intercepted_radiation_accum += intercepted_radiation;
   intercepted_radiation_season_accum += intercepted_radiation;
    float64 temperature_corrected_intercepted_radiation_dependent_growth         //080428
       = radiation_dependent_growth * RUE_temperature_limitation_factor;         //080428
   vapor_pressure_deficit_stats.append(daytime_vapor_pressure_deficit.get_kPa());//030530
   float64 pot_transpiration_dependent_growth                                    //080721
      = transpiration_dependent_growth.calc_potential_biomass_production
        (pot_transpiration_m[1 /*CO2_adj */ ]  );                                //151031_140813
   float64 result_attainable_top_growth =                                        //011022
      std::min<float64>                                                          //011022
      (temperature_corrected_intercepted_radiation_dependent_growth              //080428
      ,pot_transpiration_dependent_growth);                                      //011022
   float64 continuous_cultivation_impact_factor_local                            //160916
      = parameters->biomass_production.continuous_cultivation_impact_factor;
   #ifndef YAML_PARAM_VERSION
   if (parameters->is_perennial())                                               //080801
   {  int season_index = (season > 5) ? 5 : season;                              //080801
      continuous_cultivation_impact_factor_local =                               //151101
         parameters->biomass_production.season_biomass_adjustment[season_index]; //110218
   }
   #endif

/*std::cout << today.as_string() << "\tR:\t" << temperature_corrected_intercepted_radiation_dependent_growth
         << "\tT:\t"    << pot_transpiration_dependent_growth
         << "\tRad:\t"  << radiation_dependent_growth
         << "\tPOT_Trans:\t" << m_to_mm(pot_transpiration_m[0])
         << "\tPOT_Trans_CO2_adj:\t" << m_to_mm(pot_transpiration_m[1])
         //<< "\ttradj:\t" << CO2_transpiration_adjustment_factor
         << "\tTUEadj:\t" << CO2_TUE_adjustment
         << "\tRUE_T_factor:\t" << RUE_temperature_limitation_factor
         << "\tresult_attainable_top_growth_before_adjust:" << result_attainable_top_growth
         << "\tcontinuous_cultivation_impact_factor_local:" << continuous_cultivation_impact_factor_local
         << std::endl;*/

   result_attainable_top_growth *= continuous_cultivation_impact_factor_local;   //160916151101
   // Only consider temperature stress in when PAR conversion to biomass is the limiting factor
   float64 temperature_stress =                                                  //011022
   (temperature_corrected_intercepted_radiation_dependent_growth
    < pot_transpiration_dependent_growth)                                        //080428
   ? RUE_temperature_limitation_factor                                           //011022
   : 1.0;                                                                        //011022
   report_temperature_stress_stats.append(temperature_stress);                   //180118_010726
   return result_attainable_top_growth;                                          //011022
}
//_calc_attainable_top_growth_______________________________________2001-10-22_/
#else
Biomass_growth &Crop_complete::provide_biomass_growth()               provision_
{
   if (!biomass_growth)
      biomass_growth = new Biomass_growth_RUE_TUE                                   //180111
      (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL
      ,parameters
      ,phenology.growth_stage
      ,season
      ,pot_transpiration_m
      ,thermal_time
      ,CO2_response
      ,canopy_growth
      ,air_temperature_avg
      ,solar_radiation
      ,intercepted_radiation
      #ifdef YAML_PARAM_VERSION
      // Using adjustable parameter idiom
      ,transpiration_dependent_growth
      #else
      ,transpiration_dependent_growth
      #endif
      ,report_temperature_stress_stats

      ,at_max_fruit_load
      );
   return *biomass_growth;
}
//_provide_biomass_growth___________________________________________2018-06-12_/

#endif

void Crop_complete::set_automatic_nitrogen_mode(bool enable)
{
#ifdef NITROGEN
   if (nitrogen) nitrogen->set_automatic_mode(enable);
#endif
}
//_set_automatic_nitrogen_mode______________________________________2004-05-25_/
bool Crop_complete::process_day()
{  bool processed = true;

   /*180404 caller now check terminate pending status
      In any case eventually the crop will be in simulation subelements list
      and there will be a common consistent mechanism for
      handling termination where the crop is detached (or removed?) from the elements list.
   if (is_terminate_pending())                                                   //070627
   {
      // This is needed because there will be no transpiration processed today   //070627
      // 180404 now cleared in start_day
      // act_transpiration_m        = 0.0;                                          //070627
      // report_transpiration_act_m = 0.0;                                          //070627
      return true;                                                               //070627
   }                                                                             //070627
   */
   if (phenology.growth_stage == FGS_BUD_BREAK) phenology.growth_stage = FGS_ACTIVE_GROWTH;          //130902_030516
   if (phenology.growth_stage == FGS_VERAISON)                                   //130902_030521
        phenology.growth_stage = FGS_RAPID_FRUIT_DEVELOPMENT;
   // For fruits, we only allow one day of harvest indicator then we resume maturity //130902_030615
   if (phenology.growth_stage==NGS_HARVEST)                                      //130902_030615
   {
      phenology.growth_stage =
      #ifdef OLD_ORCHARD
          (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL) &&    //130408
          (parameters->harvested_part_labeled.get() == fruit_part)               //040514
      ?  NGS_MATURITY                                                            //130902
      :  // The crop was probably clipped (not necessarily a perennial continue where we were) //040526
      #endif
         growth_stage_at_harvest;                                                //040514
   }                                                                             //040514
   if (phenology.growth_stage >= NGS_ANTHESIS)                                   //130902_040830
         days_after_flowering += 1;                                              //040830
   temperature_with_est_night.set_Celcius
      (air_temperature_avg.Celcius(),air_temperature_avg.get_quality_code());    //140625_140507
   float64 senescence_reduction_factor=canopy_growth->get_senescence_reduction_factor();//080807
      stress_adjusted_temperature.set_Celcius                                    //140624
         (calc_stress_adjusted_temperature                                       //030610
          (parameters->phenology.phenologic_sensitivity_water_stress
          ,air_temperature_max
          ,senescence_reduction_factor
          ,water_stress_stats.index
          ,vapor_pressure_deficit_max.get_kPa()                                  //140813
          ,phenology.growth_stage
          ,parameters->has_leaf_senescence())
         ,CORN::calculated_quality);
   Date_clad_32 tomorrow(today.get_date32()); tomorrow.inc_day();                //170525_030713
   float64 min_temp_tomorrow = weather.get_air_temperature_min_tomorrow();       //151201
      // RLN note, this should now be done in the wthrbase//021124
   stress_adj_hourly_temperature_estimator.set_max_today_min_tomorrow(air_temperature_max, min_temp_tomorrow); //030610
   stress_adj_hourly_temperature_estimator.set_stress_adjusted_temperature( stress_adjusted_temperature);      //030610
   stress_adj_hourly_temperature_estimator.get_temperature_by_interval(stress_adj_hourly_temperature);         //030610
   processes(); // was potential_growth // was grow_crop                         //010723
   #ifdef FRUIT_CROP_MODEL
   if (!fruit_chill_requirement && !fruit_bud_break_requirement)                 //180701
   #endif
   actual_growth();
   reported_canopy_biomass = canopy_growth->get_biomass_current(include_vital|include_effete|include_canopy_dead); // for output only   //050823

//debugdump_lAI << today32 << '\t' << canopy->get_GAI(include_vital|include_effete) << '\t' << canopy->get_GAI(include_vital) << '\t'  << canopy->get_GAI(include_effete) << '\t' << canopy->get_LAI() << endl;
#ifdef DUMP_BIOMASS
dump_biomass << today32 << '\t'
         << canopy->get_live_and_or_dead_biomass(true ,true ,false) << '\t'   //vital_or_effete
         << canopy->get_live_and_or_dead_biomass(true ,false,false) << '\t'   //vital
         << canopy->get_live_and_or_dead_biomass(false,true ,false) << '\t'   //effete
         << canopy->get_live_and_or_dead_biomass(true ,true ,true) << endl;   //vital_or_effete_or_dead
#endif
#ifndef CROP_CALIBRATION
   recorded_root_depth = roots_current->get_apparent_root_depth();               //070131
#ifdef CROP_ORCHARD
   if ((parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)
       && (parameters->harvested_part_labeled.get() == fruit_part))              //081204
   {
      if ((latest_harvest_date.get_date32() == 0))                               //170525
      {  if (fruit_harvest_requirements)
         {  if (fruit_harvest_requirements->satisfied
                  (today.get_DOY(),air_temperature_min,air_temperature_avg )
               && fruit_dry_biomass > 1e-6)                                      //170309LML added biomass condition
            phenology.growth_stage = NGS_HARVESTABLE;                            //130925
         } else fruit_harvest_requirements
                  = new Fruit_harvest_requirements(parameters->fruit);
            // Actually only need harvest condition parameters
      }
   }
#endif
#endif
   return processed;                                                             //111121
}
//_process_day_________________________________________________________________/
float64 Crop_complete::no_nitrogen_calculate_limited_pot_transpiration() modification_
{
   float64 transpiration_use_eff                                                 //160521
      = transpiration_dependent_growth.ref_transpiration_use_efficiency_CO2_adjusted();
   #if (CROPSYST_VERSION==4)
   // special output
   report_transpiration_use_eff = (float32)transpiration_use_eff;                //150621
   #endif
   float64 pot_transpiration_mm
      =  attainable_top_growth
      / transpiration_use_eff;                                                   //160521
   float64 limited_pot_transpiration_m = mm_to_m(pot_transpiration_mm); // CO2 adjusted
   return limited_pot_transpiration_m;
}
//_no_nitrogen_calculate_limited_pot_transpiration__________________2016-03-21_/
void Crop_complete::processes()
{
   // 12114 This special for Jordi Marsal. it is intended for fruit tree
   // If we keep this, then move it to derived orchard crop.
/*
    pot_transpiration_m +=                                                       //121114
     (parameters->transpiration.a1                                               //121114
      + parameters->transpiration.a2                                             //121114
        * vapor_pressure_deficit_daytime_avg);                                   //121114
*/
   switch (parameters->season_dormancy_mode_labeled.get())                       //080401
   {                                                                             //080401
      case single_season   :                                                     //080401
      {  // Nothing special in this case                                         //080401
      } break;                                                                   //080401
      case multiple_season :                                                     //080401
      { //    need to check for start and end of season                          //080401
         consider_inactive_period(air_temperature_avg);                          //020626
            // may have been once temperature_with_est_night
      } break;                                                                   //080401
      case dormancy_season :                                                     //080401
      {  consider_inactive_period(air_temperature_avg);                          //020626
            // may have been once temperature_with_est_night
      } break;                                                                   //080401
   }                                                                             //080401
   #ifdef FRUIT_CROP_MODEL
   if (!fruit_chill_requirement && !fruit_bud_break_requirement)                 //180701
   #endif
   canopy_growth->update();                                                      //081105
   if (fallow_deprecated)
   {  report_transpiration_act_m = act_transpiration_m = 0.0;
      phenology.start_date[NGS_MATURITY].set_YD(Year(0),CORN::DOY(0));           //141202
       // For fallow we dont want to sow water stress in reports.                //010726
       water_stress_stats.reset();                                               //010726
       water_stress_stats.append(0.0);                                           //010726
       report_temperature_stress_stats.reset();
         report_temperature_stress_stats.append(0.0);                            //041112
   } else
   {  if (phenology.growth_stage >= NGS_GERMINATION)
      {
         if (roots_vital && (phenology.growth_stage >= NGS_ACTIVE_GROWTH))       //130902_061212
         {  if (is_orchard())                                                    //120808
            {
               roots_vital->root_length       = parameters->root.max_depth;      //120808
            } else                                                               //120808
               // Warning water stress hasn't been calculated yet
               // so using yesterday's                                           //160803
               roots_vital->update_root_length(get_water_stress());              //061212
         }
         // We now always accumulate degrees for fruit crop since this is used for bud break. 030515
         if (phenology.growth_stage == NGS_DORMANT_or_INACTIVE)                  //130902
         {
#ifdef NYN
081125 not really needed because these are only kept for output
            flowering_temperature_stress_factor = 0.0;
            flower_water_stress_stats        .reset();
            flower_N_stress_stats            .reset();
            //150901 now local duration_filling_factor   = 0.0;
#endif
            // Warning I have move the N_stress_stats reset to Nitrogen::process()
            // But I need to make sure the sequence is ok, because
            // it doesn't happen now until the end of this method. 041112
         } else
         {
            thermal_time->accumulate_degree_days
               (0
               ,phenology.growth_stage);                                         //020629
         }
         if (thermal_time->vernalization)
         {  if (thermal_time->vernalization->status == Thermal_time_common ::Vernalization::VERNALIZATION_START)   //020628
            {  log_event(TL_Vernalization_starts);                               //020628
               thermal_time->vernalization->status = Thermal_time_common   ::Vernalization::VERNALIZATION_ACTIVE;    //020711
            }                                                                    //020628
            if (thermal_time->vernalization->status == Thermal_time_common ::Vernalization::VERNALIZATION_END)     //020628
            {  log_event(TL_Vernalization_complete);                             //020628
               thermal_time->vernalization->status = Thermal_time_common   ::Vernalization::VERNALIZATION_INACTIVE;  //020628
               //advance to VERNALIZATION_ACTIVE
            }
         }
/*
#ifdef DEBUG_INTERCEPTION
debug_interception << today.c_str() << '\t'
<<  solid_canopy_interception << '\t'
<<  fract_canopy_cover<< '\t'
<<  fract_green_cover<< '\t'
<<  get_GAI_vital() << '\t'
<< endl;
#endif
*/
         plant_height = (phenology.growth_stage > NGS_GERMINATION)               //130902_990201
         ? canopy_growth->calc_plant_development(
                        #if (CROPSYST_VERSION == 4)
                        parameters->param_max_canopy_height()                    //990201
                        #else
                        parameters->morphology.max_canopy_height
                        #endif
                       ,plant_height ,overall_growth_stress)                     //080805
         : 0.0;                                                                  //990201

         //180111 move if CO2_response pot_transpiration_m adjustment here
         // and output of attainable_top_growth


         #ifdef OLD_BIOMASS_GROWTH
         // preserved in V4 but could be replaced as in V5
         attainable_top_growth
            = ((    (phenology.growth_stage > NGS_GERMINATION)
                 && (phenology.growth_stage < NGS_MATURITY)) //130902_011022
                ||((phenology.growth_stage == NGS_MATURITY)                      //130902
                   && (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)))   //030523
         ? calc_attainable_top_growth()                                          //011022
         : 0.0;
         #else
         // currently CO2_TUE_adjustment is needed for xxx
         //

         #ifdef CO2_CHANGE

         // 180111 this if statement should be moved
         if (CO2_response)
         {
            CO2_TUE_adjustment
            =  (canopy_growth->global_solar_rad_intercepted_green_canopy() > 0.0000001)       //151030
               ? CO2_response->get_TUE_adjustment()                                    //151030
            : 1.0;
            float64 CO2_transpiration_adjustment_factor
               = CO2_response->get_transpiration_adjustment_factor();                  //110913
            pot_transpiration_m[1/*CO2_adjusted*/] *= CO2_transpiration_adjustment_factor;//151031
         } // else no adjustments applied
         #endif

         // Move intercepted_radiation to start day
         float64 GAI_fract_canopy_cover                                          //080428
            = canopy_growth->get_global_solar_rad_intercepted_green_canopy(phenology.growth_stage);
         float64 global_radiation = (solar_radiation);  // MJ/m2 ?               //080428
         intercepted_radiation = global_radiation * GAI_fract_canopy_cover;      //080428
         intercepted_radiation_accum += intercepted_radiation;
         intercepted_radiation_season_accum += intercepted_radiation;

         if (biomass_growth)
         {
            biomass_growth->process_day();                                       //180111
            #ifdef OLD_ORCHARD
            at_max_fruit_load = is_at_max_fruit_load();
            #endif
            attainable_top_growth=biomass_growth->calc_attainable_top_growth();  //180111
            vapor_pressure_deficit_stats.append(daytime_vapor_pressure_deficit.get_kPa());//180111
         }
         #endif
         if (  (phenology.growth_stage >= NGS_ACTIVE_GROWTH) &&
               (phenology.growth_stage <= NGS_HARVESTABLE) &&                    //000625
               (get_GAI_vital() > 0.0))
         {
/*
180728 roots are already updated in active_growth()
            if (soil)  // Soil is now optional (if soil is 0 then we dont have limitations)
               if (roots_vital) roots_vital->update(terminate_pending);          //061208
            // WARNING it looks like this is being called twice see if can only need update once.
*/
         } else
         {
            pot_transpiration_m[0] = pot_transpiration_m[1] = 0.0;               //170217_151031_000625
            act_transpiration_m = 0.0;
            report_transpiration_act_m = 0.0;                                    //000323
         }

/*std::cout<<"Growth_Stage:"<<phenology.growth_stage
                  <<" plant_height:"<<plant_height
                  <<" attainable_top_growth:"<<attainable_top_growth
                  <<" GAI_vital:"<<get_GAI_vital()
                  <<" max_canopy_height:"<<parameters->morphology.max_canopy_height
                  <<" overall_growth_stress:"<<overall_growth_stress
                  <<" PET:"<<pot_transpiration_m[0]
                  <<std::endl;*/

      }
      float64 accum_degree_days= thermal_time->get_accum_degree_days(true);      //151030

      #ifdef SEED_EMERGENCE_MODEL
      //Update emergence last because we dont want to grow
      // what emerged today.
      if (emergence_hydrothermal_time)                                           //040112
      {  if (check_for_emergence())                                              //051205
         {  // adjust the phenology parameters if the hydrothermal time delayed longer than the target emergence thermal time //051205
            float64 accum_degree_days
               = thermal_time->get_accum_degree_days(true);                      //051205
                 // RLN not sure if should be adjusted for clipping need to check with Claudio
            int16 param_emergence_deg_day = parameters->phenology.initiation.emergence; //051205
            if (accum_degree_days > param_emergence_deg_day)                     //051205
            {  float64 deg_days_5_days_from_now = est_degree_days_X_days_from_now(today, 5);
               float64 adjustment = accum_degree_days
                  - param_emergence_deg_day + deg_days_5_days_from_now;
               parameters->phenology.offset_by(adjustment);
      }  }  }
      #endif
      #ifdef NITROGEN
      Crop_nitrogen_V5 *N_V5 = dynamic_cast<Crop_nitrogen_V5 *>(nitrogen);       //151030
      if (N_V5)                                                                  //151030
      N_V5->update_limited_growth                                                //151030
         (attainable_top_growth
         ,canopy_growth->get_influence_on_root_activity_factor
            (accum_degree_days > parameters->phenology.culmination.accrescence));
      #endif
   }
   if (! fallow_deprecated)
   {  limited_pot_transpiration_m =                                              //160321
      #ifdef NITROGEN
         nitrogen                                                                //020505
         ? nitrogen->update_limited_pot_transpiration() :                        //020505
      #endif
            no_nitrogen_calculate_limited_pot_transpiration();                   //160321
      // when constructing traspiration
      process_transpiration_m(limited_pot_transpiration_m);                      //031201
   }
}
//_processes________________________________________________________2001-07-23_/
float64  Crop_complete::calc_act_biomass_growth
(float64 planting_depth                                                          //010202
,float64 &GAI_related_biomass_growth)
// This method may be specific to the canopy growth model.                        //080805
{
   float64 act_biomass_growth = attainable_top_growth;                           //151030_011022
   if (limited_pot_transpiration_m > 0.0)                                        //160321
   {
      #if (defined(NITROGEN))
      float64 act_to_pot_transpiration_ratio  // name to water_stress_factor
         = report_transpiration_act_m
           / limited_pot_transpiration_m;
      float64 transpiration_limited_growth
         = attainable_top_growth                                                 //011117
         * act_to_pot_transpiration_ratio;                                       //011117
      act_biomass_growth                                                         //011022
         = std::min<float64>(transpiration_limited_growth,attainable_top_growth);//011117
      #if (CROPSYST_VERSION==4)
      deprecated::Crop_nitrogen_V4 *N_V4 = dynamic_cast<deprecated::Crop_nitrogen_V4 *>(nitrogen);
      if (N_V4)
      {
         float64 accum_degree_days= thermal_time->get_accum_degree_days(true);   //080728     //130822 confirmed adjusted
         bool after_max_canopy =  (accum_degree_days > parameters->phenology.culmination.accrescence); //080805
         float64 root_activity_factor = canopy_growth->get_influence_on_root_activity_factor(after_max_canopy); //080805
         float64 N_limited_growth = // could rename this to the final_limited_growth //011214
         N_V4->calc_limited_growth
            (transpiration_limited_growth
            ,act_to_pot_transpiration_ratio
            ,root_activity_factor);                                              //020505
         act_biomass_growth                                                      //011022
            = std::min<float64>( transpiration_limited_growth,N_limited_growth); //011117
      }
      if (!N_V4)
      #endif
      {
         if (nitrogen)
         {
            float64 N_limited_pot_transpiration = nitrogen->get_limited_pot_transpiration();
            float64 water_stress_factor
               = N_limited_pot_transpiration > 0.0
               ? report_transpiration_act_m
                  / N_limited_pot_transpiration
               : 1.0;
            // For N_V5 we use the N attainable growth previously calculated in processes
            float64 N_limited_growth = nitrogen->get_limited_growth();           //151105
            act_biomass_growth = water_stress_factor * N_limited_growth;         //151105
         }
      }
      #endif
   // This canopy expansion factor is needed only for LAI canopy it reduces canopy expansion . 110901

      float64 leaf_water_pot = transpiration->get_leaf_water_pot();              //080506
      water_canopy_expansion_factor =                                            //080506
         (leaf_water_pot - parameters->morphology.stop_canopy_expansion_LWP)     //080506_110218
        /(parameters->morphology.reduce_canopy_expansion_LWP
            // Once we are more negative than this value expansion is reduced    //110218
          - parameters->morphology.stop_canopy_expansion_LWP);                   //110218_080506
      water_canopy_expansion_factor = CORN::must_be_between<float64>(water_canopy_expansion_factor,0.0,1.0);   //080506
      GAI_related_biomass_growth =  act_biomass_growth * water_canopy_expansion_factor; //080506
      #ifdef NITROGEN

      // Check with Claudio if this is still needed/valid  151030

      /*std::clog << "act_biomass_growth:" << act_biomass_growth
                << "\tleaf_water_pot:" << leaf_water_pot
                << "\twater_canopy_expansion_factor:" << water_canopy_expansion_factor
                << "\ttranspiration_limited_growth:" << transpiration_limited_growth
                << "\trecorded_act_transpiration_m:" << recorded_act_transpiration_m
                << "\tact_to_pot_transpiration_ratio:" << act_to_pot_transpiration_ratio
                << "\tvital_root? " << (roots_vital ? "true" : "false")
                << std::endl;*/

      if (nitrogen)
         GAI_related_biomass_growth *=  nitrogen->calc_leaf_stress_factor(parameters->nitrogen.nitrogen_leaf_stress_mode);
      #endif
   }
   overall_growth_stress = (attainable_top_growth > 0.000001) ? act_biomass_growth / attainable_top_growth : 1.0;
   return act_biomass_growth;
}
//_calc_act_biomass_growth__________________________________________2001-10-23_/
#ifdef OLD_PHENOLOGY_SEQUENCER
// moving to Phenology_sequencer 140619
bool Crop_complete::thermal_time_matchs(float64 deg_day_event,bool clipping_adjusted) const
{
   return (thermal_time->get_accum_degree_days(clipping_adjusted,TT_YESTERDAY) < deg_day_event)
       && (thermal_time->get_accum_degree_days(clipping_adjusted,TT_TODAY) >= deg_day_event);
}
//______________________________________________________________________________
void Crop_complete::thermal_time_event()
{  if (phenology.growth_stage == NGS_DORMANT_or_INACTIVE) return;                //071113
   if (phenology.growth_stage == NGS_GERMINATION)                                //041201
      if (!emergence_hydrothermal_time)                                          //041201
       if (thermal_time_matchs(parameters->phenology.initiation.emergence,false))//041201
          initiate_emergence();
   if (parameters->has_leaf_senescence())                                        //970130
      if (thermal_time_matchs(parameters->phenology.initiation.tuber,true))      //970130
         initiate_tuber();                                                       //970130
   if (phenology.growth_stage >= NGS_ACTIVE_GROWTH)                              //121221
   {
      if ((parameters->phenology.initiation.flowering) // Clipping event may set this to 0 indicating flowering is cancelled
        && thermal_time_matchs(parameters->phenology.initiation.flowering,true)) //081102
         initiate_flowering();
      if (!CORN::is_approximately<float32>(parameters->phenology.initiation.senescence,0,0.000001)  //131024_121221
          && thermal_time_matchs(parameters->phenology.initiation.senescence,true)) //121221
         initiate_senescence();                                                  //121221
      if ((parameters->phenology.culmination.accrescence)                        //130429
          && thermal_time_matchs(parameters->phenology.culmination.accrescence,true)) //130429
         initiate_max_canopy();                                                  //130429
         // rename to initiate_culmanescence
   }
   if ((parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL) &&       //130408
       (parameters->harvested_part_labeled.get() == fruit_part))                 //030521
   {
#ifdef OLD_ORCHARD
      if (thermal_time_matchs(parameters->phenology.initiation.filling,true)) initiate_fruit_growth();  //030521
       if (thermal_time_matchs(parameters->phenology.initiation.rapid_fruit_growth,true)) initiate_rapid_fruit_growth( ); //130822_030521
#endif
   } else // Now all non fruit crops, not just those harvest for seed can have grain (seed) filling
       if ((parameters->phenology.initiation.filling) // Clipping event may set this to 0 indicating filling is cancelled  //030521
             && thermal_time_matchs(parameters->phenology.initiation.filling,true)) initiate_filling();
   if (parameters->phenology.maturity_significant                                //080319
       && thermal_time_matchs(parameters->phenology.initiation.maturity,true))   //970130
      initiate_maturity();
}
#endif
//_thermal_time_event_______________________________________________1997-05-14_/
bool Crop_complete::allow_natural_expiration()
{  bool ok_to_naturally_expire = true;
   if (parameters->is_annual() && CORN::is_approximately<float64>(get_GAI_vital_plus_effete(),0.0,0.01)  )
      natural_expiration();
   else ok_to_naturally_expire  =false;                                          //040824
   return ok_to_naturally_expire;                                                //040824
}
//_2004-08-05___________________________________________________________________
bool Crop_complete::natural_expiration()
{  bool expired = true;
   log_event("Natural expiration");
   terminate_pending=true;                                                       //040514
   expired &= end_season();                                                      //160618
   Biomass_fate_parameters freezing_fate =                                       //040622
      { 0 // remove_for_consumption
      ,  0 // remove_as_grazing
      ,  0 // remain_as_residue
      ,  0 // remove_as_loss
      ,100 // remain_standing_dead
      ,  0 // remain_standing_live
      ,100 // remain_roots_as_dead_residue
      ,  0 // remain_roots_live
      ,  0 // remove_roots_as_loss
      ,0 };
   Crop_mass_fate_biomass_and_nitrogen *fate =                                   //070625
   process_biomass_fate(NATURAL_EXPIRATION_CAUSE,OTHER_BIOMASS_FATE
                     ,0,0,0,freezing_fate,true,0.0);                             //110603_040622
   //070625  Warning need to make sure that all the fate is accounted for
   //        once checked, delete this message
   if (fate) delete fate;                                                        //060323
   trigger_synchronization(NGS_TERMINATED); // End of season                     //040506
   return expired;
}
//_natural_expiration_______________________________________________2004-08-05_/
// The following are daily_history total accessors
float64 Crop_complete::get_GAI_today_vital()                               const
{ return canopy_growth->get_GAI(include_vital); }
//_get_GAI_today_vital______________________________________________2005-08-23_/
float64 Crop_complete::get_GAI(nat8 include_GAI)                           const
{ return canopy_growth->get_GAI(include_GAI); }
//_2005-08-23___________________________________________________________________
float64 Crop_complete::get_GAI_vital_plus_effete()                         const
{  float64 sum_daily_GAI = canopy_growth->get_GAI(include_vital|include_effete);        //050824
   // Now have untouchable canopy portion so the check for must_be_greater_or_equal_to(sum_daily_GAI, 0.00001) is probably obsolete //080726
   return ((phenology.growth_stage > NGS_GERMINATION ))                          //980226
      ? CORN::must_be_greater_or_equal_to<float64>(sum_daily_GAI, 0.00001)
      : 0.0;
}
//______________________________________________________________________________
float64 Crop_complete::get_GAI_vital()                                     const
{  float64 sum_daily_GAI = canopy_growth->get_GAI(include_vital);                       //050824
   return ((phenology.growth_stage > NGS_GERMINATION ))                          //980226
      ? CORN::must_be_greater_or_equal_to<float64>(sum_daily_GAI, 0.00001)
      : 0.0;
}
//_get_GAI_vital________________________________________________________________
float64 Crop_complete::get_LAI(bool from_canopy)                           const
{  return canopy_growth->get_LAI(from_canopy);                                          //160627_060824
}
//______________________________________________________________________________
float64 Crop_complete::get_peak_LAI(bool reported)                         const
{ return reported
      ? canopy_growth->get_reported_peak_LAI()
      : canopy_growth->get_peak_LAI();
}
//_get_peak_LAI_____________________________________________________2014-12-03_/
float64 Crop_complete::get_canopy_biomass_kg_m2_including(nat8 include_biomass) const
{  float64 sum_daily_canopy_biomass=canopy_growth->get_biomass_current(include_biomass);//050823
   // The following line allows fastgraph to adapt the scale
   #if (defined (CROPSYST_PROPER) || defined(OFOOT_VERSION))
   if (include_biomass == (include_vital |include_effete))                       //070321
      CS_UED_max_canopy_biomass_encountered = std::max<float64>
         (CS_UED_max_canopy_biomass_encountered,sum_daily_canopy_biomass);
   #endif
  return sum_daily_canopy_biomass;
}
//_get_canopy_biomass_kg_m2_including__________________________________________/
float64 Crop_complete::get_live_green_canopy_biomass_kg_m2(nat8 include_biomass) const
{   // 070321 need to pass based on  include_biomass
   float64 sum_daily_live_canopy_biomass = canopy_growth->get_live_green_biomass(true,true);  //050823
  return sum_daily_live_canopy_biomass;
}
//_get_live_green_canopy_biomass_kg_m2_________________________________________/
#ifndef CROP_CALIBRATION
#ifdef CROP_ORCHARD
float64 Crop_complete::get_orchard_solid_canopy_interception()             const
{  return get_solid_canopy_interception();
}
//_get_orchard_solid_canopy_interception____________________________2008-10-20_/
float64 Crop_complete::get_orchard_shaded_area_GAI()                       const
{  return orchard ? orchard->get_canopy_shaded_area_GAI() : 0.0;
}
//_2008-10-20___________________________________________________________________
float64 Crop_complete::get_orchard_canopy_porosity()                       const
{  return orchard ? orchard->get_canopy_porosity() : 0.0;
}
//_get_orchard_canopy_porosity______________________________________2008-10-20_/
#endif
#endif
#ifdef OLD_BIOMASS_GROWTH
// this is used only by Biomass_growth_RUE_TUE
   // preserved in V4 but could be replaced as in V5

float64 Crop_complete::get_radiation_use_efficiency_global()               const
{
   // WUE = Water Use Efficiency
   float64 RUE_global =
      #ifdef YAML_PARAM_VERSION
      parameters->ref_biomass_production().RUE_global;                           //150907
      #else
      parameters->param_RUE_global(before_WUE_change);                           //110904
      #endif
   #ifdef CO2_CHANGE
   float64 CO2_RUE_adjustment = CO2_response
      ? CO2_response->actual_biomass_gain_ratio_in_response_to_CO2_RUE
      : 1.0;                                                                     //110904
   RUE_global *= CO2_RUE_adjustment;
   #endif
   return RUE_global;
}
//_get_radiation_use_efficiency_global______________________________2008-04-29_/
#endif
#if (CROPSYST_VERSION < 5)
float64 Crop_complete::get_radiation_use_efficiency_PAR()                  const
{
   //180522 unused float64 accum_deg_days = thermal_time->get_accum_degree_days(true);           //130822_080408
   float64 RUE_max =
      #ifdef YAML_PARAM_VERSION
      parameters->ref_biomass_production().RUE_PAR;                              //150907
      #else
      parameters->param_RUE_PAR_deprecated(before_WUE_change );                  //110904
      #endif
#ifdef CO2_CHANGE
   float64 CO2_RUE_adjustment = CO2_response ? CO2_response->
         actual_biomass_gain_ratio_in_response_to_CO2_RUE
      : 1.0;                                                                     //110904
   RUE_max *= CO2_RUE_adjustment;
#endif
   return RUE_max;
}
#endif
//_get_radiation_use_efficiency_PAR_________________________________2008-04-29_/
float64 Crop_complete::update_pot_evapotranspiration(float64 pot_ref_evapotranspiration)
{  // calculation of pot_crop_ET and GAI moved to Crop_common.
   float64 pot_crop_ET = Crop_common::update_pot_evapotranspiration              //031130
      (pot_ref_evapotranspiration);
   return pot_crop_ET;
}
//_update_pot_transpiration_________________________________________2001-09-10_/
float64 Crop_complete::get_canopy_resistance()                             const
{  return
   #ifdef CO2_CHANGE
      CO2_response ? CO2_response->get_canopy_resistance() :
   #endif
      canopy_resistance_constant_d_m;
}
//_get_canopy_resistance____________________________________________2002-04-09_/
float64 Crop_complete::get_min_water_N_stress()                            const
{  float64 min_water_or_n_stress = water_stress_stats.get_current();
#ifdef NITROGEN
   if (nitrogen && !nitrogen->get_automatic_mode())                              //050722
   {  float64 N_stress = nitrogen->get_stress();
      min_water_or_n_stress =
         std::min<float64>(water_stress_stats.get_current(),N_stress);
   }
#endif
   return  min_water_or_n_stress;
}
//_get_min_water_N_stress___________________________________________2001-07-26_/
// Moved to Phenology_sequencer
static nat16 crop_event_count = 0;
void Crop_complete::log_event(const char *description)                     const
{  crop_event_count++;
#ifndef OLD_PHENOLOGY_SEQUENCER
   Phenology_sequencer::log_event(description);
#endif
   #ifndef MICROBASIN_VERSION
   if (ref_event_log)                                                            //050725
   {  (*ref_event_log)
      << "[crop_event_" << crop_event_count << "]" << std::endl
      << "date=" << today.get_date32() << " (" << today.as_string() << ")" << std::endl //030108
      << "type=" << description << std::endl // Currently using description for the type
      << "description=" << description << std::endl
      << "model=CropSyst:" <<parameters->crop_model_labeled.get_label()<<std::endl
      << "RUSLE2_crop_name=" << parameters->RUSLE2_name << std::endl             //110831_110817
      << "RUSLE2_crop_description=" <<parameters->RUSLE2_description<<std::endl; //110831
   }
   #endif
}
//_log_event________________________________________________________2002-09-12_/
void Crop_complete::commit_biomass_fate()
{  if (biomass_fate_today)
   { log_event("biomass_fate");
      if (ref_event_log)
      {  biomass_fate_today->log(*ref_event_log);                                //050725
         (*ref_event_log) << "RUSLE2_crop_name=" << parameters->RUSLE2_name      //110831_110817
            << std:: endl;
      }
      if (biomass_fate_today->get_total_harvested() > 0.0)
      {  set_latest_harvest_date(today.get_date32());                            //130715
         trigger_synchronization(NGS_HARVEST);                                   //051021
         // Note this does not mark clipping events (may need to check get_total benificial use)
}  }  }
//_commit_biomass_fate______________________________________________2004-06-10_/
Crop_mass_fate_biomass_and_nitrogen *
Crop_complete::process_biomass_fate
(Biomass_fated_cause fated_cause
,Harvest_amount_mode harvest_amount_mode                                         //050822
,float64 remove_amount_kg_m2                                                     //050822
,float64 management_retain_GAI                                                   //050822
,float64 management_retain_biomass_kg_m2                                         //110603
,const Biomass_fate_parameters  &biomass_fate_parameters
,bool terminate                                                                  //040817
,float64 yield_now)
{  // returns the amount of material removed from the plant (for compatibility with remove_biomass_X)
   // This moves plant biomass to various pools, harvest yield, residue, loss etc.. //070802
   if (terminate) canopy_growth->terminate();                                           //080222
   canopy_growth->invalidate();                                                         //070802
   float64 curr_canopy_biomass_kg_m2 =  get_canopy_biomass_kg_m2_including
      (include_vital|include_effete|include_canopy_dead);                        //031015
#ifdef NITROGEN
   N_mass_canopy_recorded_before_harvest                                         //070209
      = nitrogen                                                                 //070209
      ? nitrogen->get_mass_canopy_current()                                      //131006_110915
      : 0.0;                                                                     //070209
   Crop_mass_fate *N_mass_fate_now = nitrogen ? nitrogen->render_N_fate(fated_cause,0,0) : 0; //131005
#endif
   Crop_mass_fate *fate_now = new Crop_mass_fate(fated_cause,curr_canopy_biomass_kg_m2,act_root_biomass);
   float64 unharvested_canopy_biomass_kg_m2 = curr_canopy_biomass_kg_m2;         //040610
   float32 total_act_biomass_removed = 0;
   Crop_biomass canopy_biomass_removed;                                          //070412
   if ((parameters->crop_model_labeled.get() != CROPSYST_ORCHARD_MODEL)          //130408
       && (yield_now > 0.0000001))                                               //060103
   {  // In fruit crops, the yield amount is deducted from the canopy biomass every day so dont double delete

//071120 Note that could probably moved this to determine_yield

      unharvested_canopy_biomass_kg_m2 -= yield_now;
      // first remove any biomass that was taken for yield.
      total_act_biomass_removed = (float32)
         canopy_growth->remove_biomass(yield_now,management_retain_GAI,true,!terminate,canopy_biomass_removed); //050823
   }
//cout  <<  get_canopy_biomass_kg_m2_including(include_vital|include_effete|include_canopy_dead) << endl;
   fate_now->yield = yield_now;
   #ifdef NITROGEN
   if (N_mass_fate_now)
   {
    N_mass_fate_now->yield = canopy_biomass_removed.get_nitrogen_mass();         //131006
   }
   #endif
   int32 actual_remove_to_standing_dead = (int32)biomass_fate_parameters.remain_as_dead;  //050720
   int32 actual_remain_as_standing_live = (int32)biomass_fate_parameters.remain_as_live;  //050720
   if (terminate)                                                                //040817
   {  // we terminate the crop, so everything goes
      actual_remove_to_standing_dead += actual_remain_as_standing_live;
      actual_remove_to_standing_dead = std::min<int32>(actual_remove_to_standing_dead,100);
      actual_remain_as_standing_live = 0;
   }
   // Determine biomass removed
   float64 act_biomass_removed = 0;                                              //050824
   float64 act_N_removed = 0;                                                    //131006
   float64 removable_biomass =  unharvested_canopy_biomass_kg_m2-management_retain_biomass_kg_m2; // 110613
   switch (harvest_amount_mode)                                                  //050822
   {  case HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS:                                  //050822
      {  remove_amount_kg_m2 = std::min<float64>(remove_amount_kg_m2,removable_biomass); // 110613
         act_biomass_removed +=
            canopy_growth->remove_biomass(remove_amount_kg_m2,management_retain_GAI
               ,parameters->canopy_growth_LAI_based.clipping_removes_newest_first
               ,!terminate,canopy_biomass_removed);                              //050823
         act_N_removed = canopy_biomass_removed.get_nitrogen_mass();             //131006
      } break;
      case HARVEST_CROP_PARAMETER_BASED:// also applies to OTHER_BIOMATTER_FATE  //050822
      case HARVEST_PERCENT_BIOMASS :                                             //051003
      default:
      {  fate_now->useful           = unharvested_canopy_biomass_kg_m2 * (float32)biomass_fate_parameters.remove_for_use/100.0;
         // Special option, all biomass grazed is converted to manure, but some is applied to the field and some is removed because the animal might not be on the field all the time
         fate_now->grazing_to_manure   = unharvested_canopy_biomass_kg_m2 * (float32)biomass_fate_parameters.remove_for_grazing/100.0 *((float32)(biomass_fate_parameters.return_as_manure)/100.0);
         fate_now->grazing_to_disposal = unharvested_canopy_biomass_kg_m2 * (float32)biomass_fate_parameters.remove_for_grazing/100.0 *(1.0-(float32)(biomass_fate_parameters.return_as_manure)/100.0);
         fate_now->disposal            = unharvested_canopy_biomass_kg_m2 * (float32)biomass_fate_parameters.remove_for_disposal/100.0;
         fate_now->chaff_or_leaf_litter             = unharvested_canopy_biomass_kg_m2 * (float32)biomass_fate_parameters.remain_as_residue/100.0;

         float64 canopy_biomass_to_remove = 0.0; // We have already removed the yielded canopy biomass 040610
         canopy_biomass_to_remove += fate_now->useful;
         canopy_biomass_to_remove += fate_now->grazing_to_manure;
         canopy_biomass_to_remove += fate_now->grazing_to_disposal;
         canopy_biomass_to_remove += fate_now->disposal;
         canopy_biomass_to_remove += fate_now->chaff_or_leaf_litter;
         // The killed by the harvest procedure is needed because the
         // user can specify a percent that goes to dead standing stubble. 070802
         // Note that additional residue may be accumulated if the crop is terminated.
         // For HARVEST_CROP_PARAMETER_BASED normally all the residues with be taken in this case here.
         float64 killed_by_harvest_procedure = unharvested_canopy_biomass_kg_m2
            * (float32)actual_remove_to_standing_dead/100.0;                     //070802
         canopy_biomass_to_remove += killed_by_harvest_procedure;                //070802
         fate_now->stubble_dead    = killed_by_harvest_procedure;
         fate_now->uncut_canopy    = unharvested_canopy_biomass_kg_m2
            * (float32)actual_remain_as_standing_live/100.0;                     //051203
         if (fate_now->uncut_canopy < management_retain_biomass_kg_m2)           //110613
         {  fate_now->uncut_canopy  = management_retain_biomass_kg_m2;
            canopy_biomass_to_remove = removable_biomass;
         }
         act_biomass_removed += (float32)
         canopy_growth->remove_biomass(canopy_biomass_to_remove,management_retain_GAI,parameters->canopy_growth_LAI_based.clipping_removes_newest_first,!terminate,canopy_biomass_removed);   //050823

         #ifdef NITROGEN
         if (N_mass_fate_now)
         {
            act_N_removed += canopy_biomass_removed.get_nitrogen_mass();         //131006
            N_mass_fate_now->useful                   = act_N_removed * (float64)biomass_fate_parameters.remove_for_use/100.0;
            N_mass_fate_now->grazing_to_manure        = act_N_removed * (float64)biomass_fate_parameters.remove_for_grazing/100.0 *((float64)(biomass_fate_parameters.return_as_manure)/100.0);
            N_mass_fate_now->grazing_to_disposal      = act_N_removed * (float64)biomass_fate_parameters.remove_for_grazing/100.0 *(1.0-(float64)(biomass_fate_parameters.return_as_manure)/100.0);
            N_mass_fate_now->disposal                 = act_N_removed * (float64)biomass_fate_parameters.remove_for_disposal/100.0;
            N_mass_fate_now->chaff_or_leaf_litter     = act_N_removed * (float64)biomass_fate_parameters.remain_as_residue/100.0;
            // NYIN_mass_fate_now->stubble_dead             = act_N_removed * (float64)
            // Any left over is presumed to be uncut canopy
            N_mass_fate_now->uncut_canopy             =  act_N_removed
               -  (N_mass_fate_now->useful
                  +N_mass_fate_now->grazing_to_manure
                  +N_mass_fate_now->grazing_to_disposal
                  +N_mass_fate_now->disposal
                  +N_mass_fate_now->chaff_or_leaf_litter
                  +N_mass_fate_now->yield);
         }
         #endif
      } break;
   } // end switch
   if ((harvest_amount_mode == HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS) || (harvest_amount_mode == HARVEST_RETAIN_GAI_obsolete)) //050824
   {  // Remove_biomass_history only removes as much as is available.
      fate_now->useful              = act_biomass_removed * (float32)biomass_fate_parameters.remove_for_use/100.0;   // additional harvested material that is not grain or fruit
      // Special option, all biomass grazed is converted to manure, but some is applied to the field and some is removed because the animal might not be on the field all the time
      float32 removed_for_grazing   = (float32)(act_biomass_removed * biomass_fate_parameters.remove_for_grazing/100.0);   //040806
      fate_now->grazing_to_manure   = removed_for_grazing * ((float32)(biomass_fate_parameters.return_as_manure)/100.0);       // will be available for the harvest model.
      // Note: grazing_to_manure is only used to determine the N that is cycled
      // in N_fate. Removed_for_grazing_to_manure in biomass fate otherwise has no meaning and should not be used for output
      fate_now->grazing_to_disposal = removed_for_grazing - fate_now->grazing_to_manure; // removed_for_grazing  // will be available for the harvest model. //040815
      fate_now->disposal            = act_biomass_removed * (float32)biomass_fate_parameters.remove_for_disposal/100.0;           // (I.e. from harvest or post harvest processing where material is not applied to the soil)
      fate_now->chaff_or_leaf_litter= act_biomass_removed * (float32)biomass_fate_parameters.remain_as_residue/100.0;
      fate_now->stubble_dead        = act_biomass_removed * actual_remove_to_standing_dead/100.0;
      fate_now->uncut_canopy        = unharvested_canopy_biomass_kg_m2 - act_biomass_removed;    // standing material //070221
      // Note that we dont set live standing to standing dead it terminate crop is specfied. 040806
      // The terminate crop will be triggered and processed latter.

      #ifdef NITROGEN
      if (N_mass_fate_now)                                                       //131006
      {
         N_mass_fate_now->useful              = act_N_removed * (float32)biomass_fate_parameters.remove_for_use/100.0;   // additional harvested material that is not grain or fruit
         // Special option, all biomass grazed is converted to manure, but some is applied to the field and some is removed because the animal might not be on the field all the time
         float32 removed_for_grazing   = (float32)(act_N_removed * biomass_fate_parameters.remove_for_grazing/100.0);   //040806
         N_mass_fate_now->grazing_to_manure   = removed_for_grazing * ((float32)(biomass_fate_parameters.return_as_manure)/100.0);       // will be available for the harvest model.
         // Note: grazing_to_manure is only used to determine the N that is cycled
         // in N_fate. Removed_for_grazing_to_manure in biomass fate otherwise has no meaning and should not be used for output
         N_mass_fate_now->grazing_to_disposal = removed_for_grazing - N_mass_fate_now->grazing_to_manure; // removed_for_grazing *((float32)(biomass_fate_parameters.manure_applied_to_field)/100.0);       // will be available for the harvest model. //040815
         N_mass_fate_now->disposal            = act_N_removed * (float32)biomass_fate_parameters.remove_for_disposal/100.0;           // (I.e. from harvest or post harvest processing where material is not applied to the soil)
         N_mass_fate_now->chaff_or_leaf_litter = act_N_removed * (float32)biomass_fate_parameters.remain_as_residue/100.0;
         N_mass_fate_now->stubble_dead         = act_N_removed * actual_remove_to_standing_dead/100.0;
         N_mass_fate_now->uncut_canopy         = unharvested_canopy_biomass_kg_m2 - act_N_removed;    // standing material //070221
         // Note that we dont set live standing to standing dead it terminate crop is specfied. 040806
         // The terminate crop will be triggered and processed latter.
      }
      #endif
   }  // else  HARVEST_CROP_PARAMETER_BASED and OTHER fate modes handled above
   total_act_biomass_removed += (float32)act_biomass_removed;
#ifdef QND
QND_daily_grazed_BM_kg_m2 += fate_now->grazing_to_manure;
QND_inc_ungrazed_BM_kg_m2 += fate_now->grazing_to_disposal + fate_now->removed_for_disposal;
#endif
   bool kill_everything
      = (fated_cause == FREEZING_DEATH_CAUSE)
      ||(fated_cause == NATURAL_EXPIRATION_CAUSE) || terminate;                  //060612
   if (kill_everything)
   {  float64 killed_biomass=canopy_growth->remove_all_biomass(canopy_biomass_removed); //070627
      fate_now->stubble_dead += killed_biomass;                                  //070626
      fate_now->uncut_canopy = 0;                                                //070201
      #ifdef NITROGEN
      if (N_mass_fate_now)                                                       //131006
      {  N_mass_fate_now->stubble_dead += canopy_biomass_removed.get_nitrogen_mass();  //070626
         N_mass_fate_now->uncut_canopy = 0;                                      //070201
      }
      #endif
      total_act_biomass_removed += (float32)killed_biomass;                      //070626
   }
   // The following are for roots
   if (estimate_root_biomass)                                                    //060612
      //  estimate_root_biomass is the old root biomass calculation
   {  float64 new_root_biomass = 0.0;                                            //040908
      for (short int sublayer = 1; sublayer <= MAX_soil_sublayers; sublayer++)   //980724
      {  float64 fract_roots_dead
         = (float64)biomass_fate_parameters.remove_roots_to_dead_residue/100.0;  //040908
         fate_now->roots_dead[sublayer]                                          //010713
            = CROP_ROOT get_total_fract_root_length_m()[sublayer]
             * act_root_biomass *fract_roots_dead;
         float64 fract_roots_live = 1.0 - fract_roots_dead;                      //040908
         float64 roots_live = fate_now->roots_live[sublayer]
            = CROP_ROOT get_total_fract_root_length_m()[sublayer]
             * act_root_biomass * fract_roots_live;                              //040908
         // NYI currently not accounting for root loss                           //040908
         new_root_biomass += roots_live;                                         //040908
      }
      act_root_biomass = new_root_biomass;                                       //040908
   } else
   {  soil_layer_array64(root_biomass_before);
      clear_layer_array64(root_biomass_before);                                  //060612
#ifndef CROP_CALIBRATION
      if (soil)   CROP_ROOT calc_root_biomass(root_biomass_before);              //060615
      else                                                                       //060615
#endif
         est_root_biomass(); // <- This is the case for the crop calibrator // But also if the crop is run with no soil (unlimited water) 060612
      if (kill_everything)                                                       //060612
      {  for (nat8 lyr = 1; lyr <= MAX_soil_sublayers; lyr++)                    //060612
            fate_now->roots_dead[lyr] = root_biomass_before[lyr];                //060612
            // note that fate_now->roots_live should already all be 0.           //070131
         roots_current->kill();                                                  //061208
         recorded_root_depth = 0;                                                //070131
         fate_now->root_after = 0.0;   // actually should recalc current root mass to make sure   //070221
         // Don't set act_root_biomass to zero otherwise we won't know the value for the season report                  //070221
      } else                                                                     //060612
      {  // In the case of dormancy where we have some dead roots                //060612
         // and some live roots                                                  //070131
         if ((biomass_fate_parameters.remove_roots_to_dead_residue > 0) && roots_vital && fated_cause==DORMANCY_CAUSE)  //070131
         {  float64 fract_roots_dead = (float32)biomass_fate_parameters.remove_roots_to_dead_residue/100.0; //070131
            float64 fract_roots_live = 1.0 - fract_roots_dead;                   //070131
            act_root_biomass = 0.0;                                              //070131
            for (nat8 layer = 1; layer <= MAX_soil_layers; layer++)              //070131
            {  fate_now->roots_live[layer] = root_biomass_before[layer] * fract_roots_live; //070131
               act_root_biomass += fate_now->roots_live[layer];                  //070131
               fate_now->roots_dead[layer] = root_biomass_before[layer] * fract_roots_dead; //070131
            }                                                                    //070131
            float64 dormant_root_length = roots_vital->get_apparent_root_depth();//070131
            delete roots_vital; roots_vital = 0;                                 //070131
            roots_current =                                                      //070131
#ifndef CROP_CALIBRATION
// Crop calibrator does not handle perennials                                    //070711
            roots_dormant =                                                      //070131
#endif
                  new CropSyst::Crop_root_dormant(dormant_root_length,act_root_biomass,fate_now->roots_live);   //070131
            fate_now->root_after = act_root_biomass;                             //070221
         } else                                                                  //070131
         { // else roots not touched.                                            //070205
            copy_layer_array64(fate_now->roots_live,root_biomass_before);        //070205
         }                                                                       //070205
      }                                                                          //060612
   }                                                                             //040908
/* debug
std::cout << "canopy_BM_before:" << curr_canopy_biomass_kg_m2 << std::endl;
float64 after_curr_canopy_biomass_kg_m2 =  get_canopy_biomass_kg_m2_including(include_vital|include_effete|include_canopy_dead);
std::cout << "canopy_BM_after:" << after_curr_canopy_biomass_kg_m2 << std::endl;
*/
#ifdef DEBUG_N_CONC
debug_N_conc_harvest_residue_root << biomass_fated_cause_label_table[fated_cause] << end;;
#endif
   fate_now->canopy_after -= (fate_now->useful + fate_now->grazing_to_manure
      +fate_now->grazing_to_disposal + fate_now->disposal
      + fate_now->chaff_or_leaf_litter + fate_now->stubble_dead);                //070221
   // Warning this canopy_biomass_after appears to be missing something,
   // So just setting it to the current biomass below
   fate_now->canopy_after =  get_canopy_biomass_kg_m2_including
      (include_vital|include_effete|include_canopy_dead);                        //070802
   record_biomass_fate(*fate_now,curr_canopy_biomass_kg_m2);
   #ifdef NITROGEN
   if (nitrogen)
   {
      N_mass_fate_now = nitrogen->apportion_fate
      (*fate_now
      ,N_mass_fate_now                                                           //131005
      ,canopy_biomass_removed
      ,harvest_amount_mode == HARVEST_CROP_PARAMETER_BASED
      ,include_vital/*roots*/ );
   }
   #endif

// WARNING!!!
// At this point the fate_now returned should have only masses that are
// to be redistributed, but I need to check every where this is returned to
// to make sure the fate returned is not used some other way.
// Before I add any code to clear fate

   return new Crop_mass_fate_biomass_and_nitrogen                                //060323
      #ifdef NITROGEN
      (fate_now,N_mass_fate_now);                                                //060323
      #else
      (fate_now,0);                                                              //140923
      #endif
}
//_process_biomass_fate_____________________________________________2007-06-25_/
float64 Crop_complete::record_biomass_fate
(const Crop_mass_fate &fate_now
,float64 curr_canopy_biomass_kg_m2)
{  if (!biomass_fate_today)  biomass_fate_today
      = new Crop_mass_fate(fate_now.cause,curr_canopy_biomass_kg_m2,get_act_root_biomass());
   biomass_fate_today->add(fate_now);
   if (!biomass_fate_season)  biomass_fate_season
      = new Crop_mass_fate(MULTIPLE_CAUSES,curr_canopy_biomass_kg_m2,get_act_root_biomass()); //040719
   biomass_fate_season->add(fate_now);                                           //040719
   return fate_now.get_total_removed_from_plant();
}
//_record_biomass_fate______________________________________________2004-08-09_/
#ifdef SEED_EMERGENCE_MODEL
bool Crop_complete::check_for_emergence()
{  bool first_day_of_emergence = emergence_hydrothermal_time->is_first_day(); // first cohort
   emergence_hydrothermal_time->process(*soil);
   if (first_day_of_emergence)
   {  log_event(TL_Emergence);
      trigger_synchronization(NGS_EMERGENCE);                                    //130925
      restart(emergence_hydrothermal_time->get_cotyledon_biomass()
             ,emergence_hydrothermal_time->get_cotyledon_GAI(),true,false);
      phenology.start_date[NGS_EMERGENCE].set(today);                            //141202
   } else
   {  float64 new_cotalydon_GAI = emergence_hydrothermal_time->get_cotyledon_GAI();
      if (new_cotalydon_GAI > 0.0)
      {  float64 new_cotalydon_BM =  emergence_hydrothermal_time->get_cotyledon_biomass();
         canopy_growth->emerge_cotyledon(new_cotalydon_GAI,new_cotalydon_BM);           //080728
         total_season_biomass_production_output += new_cotalydon_BM;             //040719
   }  }
   if (emergence_hydrothermal_time->is_complete())
   {  phenology.growth_stage = NGS_ACTIVE_GROWTH;                                //130925
      is_in_leaf_senescence = false;                                             //121221
      trigger_synchronization(NGS_ACTIVE_GROWTH);                                //130925
      delete emergence_hydrothermal_time; emergence_hydrothermal_time = 0;
      emergence = 0;
   }
   return first_day_of_emergence;                                                //051205
}
//_check_for_emergence______________________________________________2004-12-01_/
#endif
bool Crop_complete::end_season_if_no_dormancy()
{  // Usually perennial crops go into dormancy,
   // and the restart after dormancy increments the season counter.
   // But this is not necessarily the case that dormancy is enabled
   // for perennial crops (We saw this with Elisenda's Spanish alfalfa scenario).
   // [Guillaumes Cullell, Elisenda]
   // In this case we need to identify the end of the season.
   // This is triggered by the clipping management event marked as last clipping.

//080401 I have redone season processing for non dormancy crops using inactive_periods
// this method is now probably obsolete

   if (parameters->season_dormancy_mode_labeled.get() != dormancy_season)        //080331
   {  season += 1;                                                               //050826
      trigger_synchronization(NGS_DORMANT_or_INACTIVE);                          //050826
         // 130902 I have removed the END_SEASON growth stage
         // Now I am simply assuming the crop will go into an inactive period
         // which is essentially what we presumed for end of season
         // (which we didn't have at the time). 
   }
   return end_season();                                                          //160629
}
//_end_season_if_no_dormancy________________________________________2005-08-18_/
float64 Crop_complete::get_carbon_fraction()                               const
{  float64 carbon_fraction = default_straw_residue_fraction_carbon;
   carbon_fraction = parameters->residue_decomposition.carbon_fraction;
   return carbon_fraction;
}
//_get_carbon_fraction______________________________________________2006-08-18_/
#ifdef NITROGEN
float64 Crop_complete::get_N_mass_canopy_kg_m2(bool before_harvest)        const
{  float64 N_mass_canopy = 0;
   if (nitrogen)
      N_mass_canopy = before_harvest
      ?  N_mass_canopy_recorded_before_harvest
      : nitrogen->get_mass_canopy_current();                                     //131006
   return  N_mass_canopy;
}
//_get_N_mass_canopy_kg_m2__________________________________________2007-02-09_/
#endif
void Crop_complete::setup_quiescence_end_requirement(CORN::DOY doy)
{  // Note that this method is overridden for fruit crops
   quiescence_end_requirement = new Quiescence_end_requirement                   //030514
       ((parameters->quiescence),doy);                                           //080331
}
//_setup_quiescence_end_requirement_____________________2016-03-16__2007-11-20_/
float64 Crop_complete::get_fract_canopy_cover_total()                      const
{ return canopy_growth->get_fract_canopy_cover(); }
//______________________________________________________________________________
float64 Crop_complete::get_fract_canopy_cover_green()                      const
{ return canopy_growth->global_solar_rad_intercepted_green_canopy(); }
//______________________________________________________________________________
float64 Crop_complete::global_solar_rad_intercepted_green_canopy()         const
{ return canopy_growth->global_solar_rad_intercepted_green_canopy(); }
//______________________________________________________________________________
float64 Crop_complete::get_adjusted_ET_crop_coefficient()                  const
{  float64 param_ET_coef = parameters->transpiration.ET_coef;                    //110218
   float64 adjusted_ET_coef = (param_ET_coef == 0.0)
   ? 1.0  // <- If no crop
   :  (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)           //980311
      ? param_ET_coef  // Note that Claudio wants to look into just how to interpret the ET crop coef. for fruit trees //060808
      : canopy_growth->get_adjusted_ET_crop_coefficient(); // Other crops may be adjusted by LAI
   return adjusted_ET_coef;
}
//_get_adjusted_ET_crop_coefficient_________________________________2008-08-11_/
void Crop_complete::know_residues(Residues_interface *_residues)
{ ref_residues = _residues; canopy_growth->know_residues(_residues);}
//_know_residues____________________________________________________2006-05-31_/
#ifndef CROP_CALIBRATION
#ifdef CROP_ORCHARD
int16 Crop_complete::get_fruit_chill_hours_remaining()                     const // currently just for debugging
{  return fruit_chill_requirement
   ? fruit_chill_requirement->get_chill_hours_remaining()
   : 0;
}
#endif
#endif
//______________________________________________________________________________
float64 Crop_complete::get_thermal_time_cumulative(bool adj_for_clipping)  const
{  return thermal_time->get_accum_degree_days(adj_for_clipping);
}
//_get_thermal_time_cumulative______________________________________2011-09-02_/
void Crop_complete::trigger_synchronization(Normal_crop_event_sequence event)
{
   #ifdef OLD_PHENOLOGY_SEQUENCER
   phenology.days_since_start_of  [event] = 1;
   phenology.duration_of          [event] = 1;
   #endif
   bool fruit_crop_model =  get_parameters()->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL;
   Synchronization sync(fruit_crop_model,event);
   as_event_scheduler_crop->synchronize(sync,today);
}
//_trigger_synchronization__________________________________________2013-09-03_/
#ifdef CS_INSPECTOR_VERSION
bool Crop_complete::take_crop_ID_directory(CORN::OS::Directory_name *crop_ID_directory_)   //160609
{
   crop_ID_directory = crop_ID_directory_;
   return true;
}
//_take_crop_ID_directory___________________________________________2016-06-09_/
#endif
bool Crop_complete::end_season()
{
   bool ended = end_period(0);
   #ifdef CS_INSPECTOR_VERSION
   // continue here add inspectors  to examination_global.singles
   #endif
   return ended;
}
//_end_season_______________________________________________________2016-06-09_/
RENDER_INSPECTORS_DEFINITION(Crop_complete)
{
   CS::Emanator *emanator =
       Crop_common::render_inspectors(inspectors,context,instance);
   roots_current  ->render_inspectors(inspectors,emanator,"root");
   phenology       .render_inspectors(inspectors,emanator,"phenology");
   if (nitrogen) nitrogen->render_inspectors(inspectors,emanator,"nitrogen");

   inspectors.append(new CS::Inspector_scalar(reported_canopy_biomass,UC_kg_m2 ,*emanator,/*check ontology*/"canopy/biomass/cum"    ,sum_statistic/*171031 value_statistic*/,CSVC_crop_biomass_canopy));
      // biomass is already a cumulated value
/* NYI
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_green_biomass                                     ,PP_crop_base_green_biomass                                            ,));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_fruit_biomass                                     ,PP_crop_base_fruit_biomass                                            ,));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_fruit_canopy_biomass                              ,PP_crop_base_fruit_canopy_biomass                                     ,));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_orchard_solid_canopy_interception                 ,PP_crop_base_orchard_solid_canopy_interception                        ,));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_orchard_shaded_area_GAI                           ,PP_crop_base_orchard_shaded_area_GAI                                  ,));
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_orchard_canopy_porosity                           ,PP_crop_base_orchard_canopy_porosity                                  ,));
*/
   inspectors.append(new CS::Inspector_scalar(reported_LAI   ,UC_index   ,*emanator,/*check ontology*/"leaf/area/index/LAI"    ,value_statistic,CSVP_crop_base_leaf_area_index));
   inspectors.append(new CS::Inspector_scalar(reported_GAI   ,UC_index   ,*emanator,/*check ontology*/"leaf/area/index/GAI"    ,value_statistic,CSVP_crop_base_green_area_index));

   inspectors.append(new CS::Inspector_scalar(report_temperature_stress_stats.ref_current() ,UC_factor  ,*emanator,/*check ontology*/"stress/temperature/factor"  ,value_statistic,CSVP_crop_base_temperature_stress_factor));
   inspectors.append(new CS::Inspector_scalar(report_temperature_stress_stats.index         ,UC_index   ,*emanator,/*check ontology*/"stress/temperature/index"   ,value_statistic,CSVP_crop_base_water_stress_index));

/*NYI
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_index   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_tuber_init_temp_stress_index
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_index   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_tuber_fill_temp_stress_index
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_index   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_flower_temperature_stress_index
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_index   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_flower_water_stress_index
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_index   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_flower_N_stress_index
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_index   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_filling_duration_index
*/
   inspectors.append(new CS::Inspector_scalar(reported_canopy_cover_green      ,UC_fraction,*emanator,/*check ontology*/"ground_cover_green"        ,value_statistic,CSVC_canopy_cover_green));
   //NYI inspectors.append(new CS::Inspector_scalar(reported_canopy_cover      ,UC_fraction,*emanator,/*check ontology*/"ground_cover_green"        ,value_statistic,CSVP_crop_base_fract_canopy_cover));
   inspectors.append(new CS::Inspector_scalar(intercepted_precipitation_m_today,UC_meter   ,*emanator,/*check ontology*/"water/interception"  ,value_statistic /*171031 sum_statistic*/,CSVP_crop_base_water_intrcpt/*171222 CSVC_crop_base_water_intrcpt_time_step_sum*/));

   // NYI inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,/*check ontology*/"XXX/XXX"    ,XXX_statistic,CSVP_crop_base_growth_stage

   // seasonal

   //180111 using final_statistic because these dates are set one time and shouldn't be tallied daily

   inspectors.append(new CS::Inspector_scalar(phenology.start_date[NGS_PLANTING] .ref_date32()   ,UT_date   ,*emanator, /*need ontology*/"management/planting"        ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_planting_date_YD));
   inspectors.append(new CS::Inspector_scalar(phenology.start_date[NGS_EMERGENCE].ref_date32()   ,UT_date   ,*emanator,"phenology/emergence"          ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_emergence_date_YD));
   inspectors.append(new CS::Inspector_scalar(phenology.start_date[NGS_ANTHESIS] .ref_date32()   ,UT_date   ,*emanator,"phenology/anthesis"           ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_flowering_date_YD));

   if (parameters->harvested_part_labeled.get() == tuber_part)                   //171115
   inspectors.append(new CS::Inspector_scalar(phenology.start_date[NGS_FILLING]  .ref_date32()   ,UT_date   ,*emanator,"phenology/tuber"              ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_tuber_init_date_YD));
   else
   inspectors.append(new CS::Inspector_scalar(phenology.start_date[NGS_FILLING]  .ref_date32()   ,UT_date   ,*emanator,"phenology/filling"            ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_grain_filling_date_YD));

   inspectors.append(new CS::Inspector_scalar(GAI_max_date/*180413 largest_GAI_date*//*NYI phenology.culmination_date[NGS_ACTIVE_GROWTH]*/ .ref_date32()  ,UT_date   ,*emanator,"phenology/accrescence"        ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_peak_LAI_date_YD));
   if (parameters->phenology.maturity_significant)
   inspectors.append(new CS::Inspector_scalar(phenology.start_date[NGS_MATURITY] .ref_date32()   ,UT_date   ,*emanator,"phenology/maturity"           ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_maturity_date_YD));

   if (is_perennial())
   inspectors.append(new CS::Inspector_scalar(phenology.start_date[NGS_RESTART]  .ref_date32()   ,UT_date   ,*emanator,/*check ontology*/"phenology/restart"               ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_restart_date_YD));

   inspectors.append(new CS::Inspector_scalar(latest_harvest_date                .ref_date32()   ,UT_date   ,*emanator, /*need ontology*/"management/harvest"              ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_harvest_date_YD));

   #ifdef OLD_ORCHARD
   if (is_orchard())
   {
   inspectors.append(new CS::Inspector_scalar(bud_break_date                     .ref_date32()   ,UT_date   ,*emanator,/*check ontology*/"phenology/budding"               ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_bud_break_date_YD));
   inspectors.append(new CS::Inspector_scalar(initial_fruit_growth_date          .ref_date32()   ,UT_date   ,*emanator, /*need ontology*/"phenology/filling/initial"       ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_initial_fruit_growth_date_YD));
   inspectors.append(new CS::Inspector_scalar(rapid_fruit_growth_date            .ref_date32()   ,UT_date   ,*emanator, /*need ontology*/"phenology/filling/rapid"         ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_rapid_fruit_growth_date_YD));
   inspectors.append(new CS::Inspector_scalar(chill_requirement_satisfied_date   .ref_date32()   ,UT_date   ,*emanator,"phenology/chill/requirement"                       ,final_statistic/*180111 value_statistic*/,CSVP_crop_base_chill_requirement_satisfied_date_YD));
   }
   #endif
   /*NYI
   if (has_quiesence())
   {
   inspectors.append(new CS::Inspector_scalar(phenology.start_date[xxxx].ref_date32()   ,UT_date   ,*emanator, "phenology/quiescence/initiation" ,value_statistic,CSVP_crop_base_inactive_begin_date_YD));
   inspectors.append(new CS::Inspector_scalar(phenology.start_date[xxxx].ref_date32()   ,UT_date   ,*emanator, "phenology/quiescence/completion" ,value_statistic,CSVP_crop_base_inactive_end_date_YD));
   }
   */

   inspectors.append(new CS::Inspector_scalar(intercepted_radiation   ,UC_MJ_m2   ,*emanator,/*need ontology*/"biomass/production/RUE/PAR/intercepted"    ,value_statistic/*171030 sum_statistic*/,CSVP_crop_base_intercepted_PAR));
/* NYI
   // NYI inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_P_mass_uptake
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_C_mass_canopy
   inspectors.append(new CS::Inspector_scalar(member_variable   ,UC_xxxxx   ,emanator,"XXX/XXX"    ,XXX_statistic,CSVP_crop_C_mass_roots_live
*/

// BIG WARNING these are just quick and dirty codes
// They have not been derived using my derivation conventions
// because eventually variable definitions will be based on the new ontology
// system, but currently UED still needs

   // Special outputs
   inspectors.append(new CS::Inspector_scalar(report_transpiration_use_eff        ,UC_kg_kg                  ,*emanator,/*check ontology*/"WUE"               ,value_statistic,CSVP_crop_transpiration_use_eff         )); //CSVC_crop_WUE));
   inspectors.append(new CS::Inspector_scalar(report_degree_hours_above_30_today  ,UC_Celcius_degree_hours   ,*emanator,/*check ontology*/"DegHr_above_30"    ,sum_statistic  ,CSVC_crop_degree_hours_above_30_today   )); // already sum so use CVSC_
   inspectors.append(new CS::Inspector_scalar(report_degree_hours_above_34_today  ,UC_Celcius_degree_hours   ,*emanator,/*check ontology*/"DegHr_above_34"    ,sum_statistic  ,CSVC_crop_degree_hours_above_34_today   )); // already sum so use CVSC_

   inspectors.append(new CS::Inspector_scalar(reported_ET_act_m                   ,UC_m,*emanator,/*check ontology*/"ET/crop/act",value_statistic,CSVP_weather_ET_pot/*171223 CSVP_crop_ET_act*/ )); //171031
   inspectors.append(new CS::Inspector_scalar(reported_ET_pot_m                   ,UC_m,*emanator,/*check ontology*/"ET/crop/pot",value_statistic,CSVP_weather_ET_act/*171223 CSVP_crop_ET_pot*/)); //171031

//disabled to see why reported_ET_pot_m is not output
   inspectors.append(new CS::Inspector_scalar(ref_phenology().ref_day_of_season(),UT_day ,*emanator,/*check ontology*/"duration_season" ,count_statistic,CSVC_crop_duration_season)); // already statistice so use CSVC

   #ifdef OLD_PHENOLOGY_SEQUENCER
   thermal_time->render_inspectors(inspectors,emanator,/*check ontology*/"thermal_time");
   #else
   // NYI need to setup new phenology sequencer thermal time output
   #endif
   return emanator;
}
//_render_inspectors________________________________________________2013-07-30_/
} // namespace CropSyst

//2500 lines
//2200 lines (040623)
//2602 lines (050825)
//2380 lines (060730)
//2238 lines (070821)
//2440 lines (071004)
//2520 lines (080515)
//2771 lines (081013)
//2600 lines (100520)
//2944 (121221)

