#include "crop/crop_param.h"
#include "crop/biomass_growth_RUE_TUE.h"
#include "crop/thermal_time_common.h"
#include "crop/CO2_response.h"
#include "crop/canopy_growth.h"

#include "common/weather/parameter/WP_solar_radiation.h"

namespace CropSyst
{
//______________________________________________________________________________
Biomass_growth_RUE_TUE::Biomass_growth_RUE_TUE
(bool                                orchard_model_
,const Crop_parameters              *parameters_
,const Normal_crop_event_sequence   &growth_stage_
,const nat8                         &season_
,const float64                      *pot_transpiration_m_//[2]
,const Thermal_time_common          *thermal_time_
,const Crop_CO2_response            *CO2_response_
,const Canopy_growth_interface      *canopy_
,const Air_temperature_average      &air_temperature_avg_
,const Solar_radiation              &solar_radiation_
,const float64                      &intercepted_radiation_
#ifdef YAML_PARAM_VERSION
// Using adjustable parameter idiom
,const CropSyst::Biomass_production_transpiration_dependent_V5 &transpiration_dependent_growth_
#else
,const CropSyst::Biomass_production_transpiration_dependent_V4 &transpiration_dependent_growth_
#endif
,CORN::Statistical_sample_cumulative<float64,float64>/*180408 Statistical_running_index*/
      &report_temperature_stress_stats_
,const bool                         &at_max_fruit_load_                          //180308
)
: Biomass_growth()
, orchard_model                                                 (orchard_model_)
, parameters                                                       (parameters_)
, growth_stage                                                   (growth_stage_)
, season                                                               (season_)
, pot_transpiration_m                                     (pot_transpiration_m_)
, thermal_time                                                   (thermal_time_)
, CO2_response                                                   (CO2_response_)
, canopy                                                               (canopy_)
, air_temperature_avg                                     (air_temperature_avg_)
, solar_radiation                                             (solar_radiation_)
, intercepted_radiation                                 (intercepted_radiation_)
, transpiration_dependent_growth               (transpiration_dependent_growth_)
, report_temperature_stress_stats             (report_temperature_stress_stats_)
//local, RUE_temperature_limitation_factor                                        (1.0)
, at_max_fruit_load                                         (at_max_fruit_load_) //180308
{}
//_2018-01-11______________________________________________________constructor_/
float64 Biomass_growth_RUE_TUE::calc_attainable_top_growth()        calculation_
// 180308 abandoned(  bool is_at_max_fruit_load)                                         calculation_ //180308
{
   float64 RUE_temperature_limitation_factor =
      orchard_model ? 1.0 : calc_RUE_temperature_limitation();                   //180111_130513

   float64 accum_deg_days_adjusted_for_clipping
      = thermal_time->get_accum_degree_days(true);  //151110_100730  //130822 confirmed
   // WUE = Water Use Efficiency
   #ifdef YAML_PARAM_VERSION
      // YAML version (and eventually V5) use parameter adjustment idiom         //150907
   #else
   bool before_WUE_change                                                             //080721
      = !parameters->has_leaf_senescence() // 100729 (Not sure if has_leaf_senescence is needed, it so probably should hide the WUE_changes checkbox in the crop editor.
         || (parameters->biomass_production.WUE_changes &&                       //110218_100729
             (accum_deg_days_adjusted_for_clipping <= parameters->phenology.WUE_change));  //100730
   #endif

#ifdef CROP_ORCHARD
#ifdef OLD_ORCHARD
#ifndef CROP_CALIBRATION
   if (at_max_fruit_load/*180308 ()*/ )                                       //180308_071103
      before_WUE_change = true;                                                  //071103
#endif
#endif
#endif

   float64 solar_rad = solar_radiation.get_MJ_m2();                              //140813_131104
   float64 radiation_dependent_growth = 0.0;                                     //080428
/*moved above
   if (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)           //080821
      RUE_temperature_limitation_factor = 1.0;                                   //080821
*/
   // This mode is for compatibility with previous versions
   #if (CROPSYST_VERSION < 5)
   // obsolete in version 5  (deprecated in V5)
   if (parameters->biomass_production.RUE_basis == photosynthetically_active_radiation)   //11080??_080428
   {  float64 RUE_PAR = g_to_kg(get_radiation_use_efficiency_PAR());             //110906
      float64 GAI_fract_canopy_cover_for_PAR
      = canopy->get_PAR_solar_rad_intercepted_green_canopy(phenology.growth_stage);//110902
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
      /*moved to crop::start_day()
      float64 GAI_fract_canopy_cover                                             //080428
         = canopy->get_global_solar_rad_intercepted_green_canopy(growth_stage);
      float64 global_radiation = (solar_rad);  // MJ/m2 ?                        //080428
      intercepted_radiation = global_radiation * GAI_fract_canopy_cover;         //080428
      */
      radiation_dependent_growth = intercepted_radiation * RUE_global;           //080428 kg/m2
   }
   /* moved to crop start_day
   intercepted_radiation_accum += intercepted_radiation;
   intercepted_radiation_season_accum += intercepted_radiation;
   */
    float64 temperature_corrected_intercepted_radiation_dependent_growth         //080428
       = radiation_dependent_growth * RUE_temperature_limitation_factor;         //080428
   /* move to caller
   vapor_pressure_deficit_stats.append(daytime_vapor_pressure_deficit.get_kPa());//030530
   */
   /* moved to caller
   #ifdef YAML_PARAM_VERSION
      // Transpiration dependent growth references these values.
   #else
   transpiration_dependent_growth.know_daily_parameters
      (season,before_WUE_change);
   #endif
   */
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

   report_temperature_stress_stats.append(temperature_stress);                          //010726

   return result_attainable_top_growth;                                          //011022
}
//_2018-01-11_2001-10-22__________________________________________________________________
float64 Biomass_growth_RUE_TUE::calc_RUE_temperature_limitation()                       const
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
//_2016-02-04__2013-05-13_______________________________________________________
float64 Biomass_growth_RUE_TUE::get_radiation_use_efficiency_global()      const
{
   // WUE = Water Use Efficiency
   #if (!defined(YAML_PARAM_VERSION) || (CROPSYST_VERSION==4))
   //170217 (CROPSYST_VERSION==4)
   float64 accum_deg_days = thermal_time->get_accum_degree_days(true);           //130822_080408
   bool before_WUE_change = (!parameters->has_leaf_senescence()
        || accum_deg_days < parameters->phenology.WUE_change);                   //150913_080514
   #endif
   #ifdef CROP_ORCHARD
   #ifndef CROP_CALIBRATION
   if (at_max_fruit_load/*180308()*/) before_WUE_change = true;  // for fruit switch  transpiration to WUE after reproductive growth parameter. //081103
   #endif
   #endif
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
//_2018-01-11__2008-04-29_______________________________________________________


//______________________________________________________________________________
} // namespace CropSyst

