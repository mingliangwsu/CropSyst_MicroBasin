#ifdef OLD_YIELD
float64 sensitivity_effect(float64 mean_period_stress , float64 harvest_ndx_period_sensitivity_index)
{  static const float64  Stress_Threshold = 0.75;
   if (is_approximately(mean_period_stress, 0.0,0.0001)) // avoid overflow       //090514
      mean_period_stress = 0.0000001;                                            //010726
   return (CORN::is_approximately<float64>(harvest_ndx_period_sensitivity_index,0,0.00001) ||   //090514
           (mean_period_stress >= Stress_Threshold))
   ? 1.0   //then no stress effect
   : pow(mean_period_stress / Stress_Threshold,harvest_ndx_period_sensitivity_index);
}
//_1998-08-24___________________________________________________________________
float64 sensitivity_effect_B(float64 mean_period_stress , float64 harvest_ndx_period_sensitivity)
{  return (CORN::is_approximately<float64>(harvest_ndx_period_sensitivity,0,0.00001)) //090514
   ? 1.0   //then no stress effect
   : pow(mean_period_stress ,harvest_ndx_period_sensitivity);
}
//_1998-08-24___________________________________________________________________
float64 harvest_index_1_stress_period
(float64 harvest_ndx_unstressed
,float64 mean_period_stress
,float64 harvest_ndx_period_sensitivity)
{   return harvest_ndx_unstressed
          * sensitivity_effect(mean_period_stress,harvest_ndx_period_sensitivity);
}
//_1998-08-24___________________________________________________________________
#include "harvest_grain_asymptotic.c"
float64 Crop_complete::determine_yield()                                   const
{  float64 yield_now = 0.0;
   float64 canopy_biomass_kg_m2=get_canopy_biomass_kg_m2_including(include_vital);//031015
            // the current biomass of this season only
   Harvested_part harvested_part = parameters->harvested_part_labeled.get();     //040610
   float64 harvest_ndx_unstressed = parameters->
         harvest.index_unstressed;                                               //130406
         //130406 param_harvest_ndx_unstressed();  //981204
#ifdef OLD_ORCHARD
   if (parameters->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)           //060726
   {  yield_now                                                                  //060726
      = fruit_dry_biomass;                                                       //080912
      //080912          Now we stop partition when max fruit load is reached
      fruit_dry_biomass = 0.0;                                                   //080912
   }else                                                                         //080912
#endif
   switch (harvested_part)                                                       //980924
   {  case tuber_part/*TUBER_CROP*/ :                                            //980924
      {                                                                          //980924
         float64 stress_effect_initiation =  sensitivity_effect_B
            (tuber_init_temperature_stress_stats.get_mean()
            ,parameters->harvest.tuber_init_sensitivity);                        //130406
         float64 stress_effect_bulking = sensitivity_effect_B
            (tuber_growth_temperature_stress_stats .get_mean()
            ,parameters->harvest.tuber_growth_sensitivity);                      //130406
         yield_now = canopy_biomass_kg_m2 * harvest_ndx_unstressed *  stress_effect_initiation * stress_effect_bulking;
         reported_harvest_index =
            canopy_biomass_kg_m2 > 0.00001                                       //150211
            ? yield_now / canopy_biomass_kg_m2                                   //120117
            : 0.0;                                                               //150211
            // reported_harvest_index added by RLN for completeness,
            // Claudio originally intended it only for seed.
      } break;
      case HARVEST_CANOPY :                                                      //031015
      {  // used for silage
      } break;
      case grain_part :                                                          //990301
      {  float64 actual_yield = 0;                                               //010322
         float64 actual_harvest_index = harvest_ndx_unstressed;                  //110903
         if (parameters->harvest.apply_adjustment_to_unstressed_harvest_index)
// we already check for apply_adjustment_to_unstressed_harvest_index
// and instanciate harvest_temperature_stress_factor.
         {
            #if (CROPSYST_VERSION==4)
            if (!CORN::is_approximately<float32>(parameters->harvest.filling_sensitivity,0.0,0.0001)) //110908
            { // This is the older stress adjustment used for climate change scenarios
                  // It is provided only so users don't have to recalibrate if they used the
                  // this deprecated method
                  float64 harvest_ndx_flowering_sensitivity = parameters->harvest.flowering_sensitivity; //130406
                   flowering_temperature_stress_factor = calc_flowering_temperature_stress_factor();   //081121
                   float64 flowering_stress_effect_water_and_N = sensitivity_effect(flowering_stress_stats.get_mean(),harvest_ndx_flowering_sensitivity);
                   float64 stress_effect_flowering =
                      std::min<float64>(flowering_stress_effect_water_and_N
                             ,flowering_temperature_stress_factor);
                   float64 harvest_ndx_filling_sensitivity = parameters->param_harvest_ndx_filling_sensitivity();  //101018
                   float64 filling_stress_effect_water_and_N = sensitivity_effect(filling_stress_stats.get_mean(),harvest_ndx_filling_sensitivity); //101018
                   float64 duration_filling_factor =  filling_duration / (float64)parameters->harvest.filling_duration;   //fraction of days //150901  
                   duration_filling_factor = CORN_must_be_between(duration_filling_factor,0.0,1.0);
                   actual_harvest_index
                     =  harvest_ndx_unstressed
                        * stress_effect_flowering
                        * duration_filling_factor
                        * filling_stress_effect_water_and_N;                     //101018
               reported_harvest_index = actual_harvest_index;                    //120117
               actual_yield = canopy_biomass_kg_m2 * actual_harvest_index;       //110907
            }

            else                                                                 //110908
            #endif
            {

                  float64 temperature_stress_effect =
                     extreme_temperature_stress_factor
                     ? extreme_temperature_stress_factor->get_factor() : 1.0;


               float64 sink_strength_based_harvest_index
                     =  harvest_ndx_unstressed * temperature_stress_effect;      //130424
               float64 source_limited_harvest_index =                            //150519
                  calc_source_limited_harvest_index                              //130513
                  (biomass_at_maturity                                           //130510
                  ,biomass_at_filling                                            //131022
                  , sink_strength_based_harvest_index                            ////150519_130510
                        // under certain conditions the harvest index can be slightly above (upto 10%) the parameter
                  ,(float64)parameters->harvest.translocation_fraction_max);     //120117
               actual_yield  = canopy_biomass_kg_m2 * source_limited_harvest_index; //150519
            }
         }
         else
         {
            reported_harvest_index = actual_harvest_index;                       //120117
            actual_yield = canopy_biomass_kg_m2 * actual_harvest_index;          //110907

         }
         yield_now = actual_yield;                                               //081125
      } break;                                                                  //040910
      default :
      {  float64 stressed_harvest_biomass = canopy_biomass_kg_m2
                * harvest_index_1_stress_period(harvest_ndx_unstressed
                  ,stress_since_emergence_stats.get_mean()                       //010726
                  ,parameters->harvest.growth_sensitivity);
         yield_now =                                                             //030516
               CORN_min(canopy_biomass_kg_m2* harvest_ndx_unstressed,stressed_harvest_biomass);
         if (canopy_biomass_kg_m2 > 0.0)
            reported_harvest_index = yield_now / canopy_biomass_kg_m2;           //120117
         else
         {  reported_harvest_index = 0.0;
            std::cout << "No biomass production" << std::endl;
         }
            // reported_harvest_index added by RLN for completeness,
            // Claudio intended it only for seed.
      } break;                                                                   //981203
   } // switch (harvested_part)
   return yield_now;                                                             //071120
}
//_2007-11-20___________________________________________________________________
float64  Crop_complete::calc_flowering_temperature_stress_factor()         const
{  // Currently these coefficient apply only to Wheat may eventually make these parameters
   float64 stress_factor = 1.0 - 0.000174 * flowering_degree_minutes
      * parameters->harvest.temperature_stress_sensitivity;
   //081125           (770.0 - 0.134 * flowering_degree_minutes ) / 770.0; // linear regression
   stress_factor = CORN::must_be_between<float64>(stress_factor,0.0,1.0);
   // Ferris et al. Annals of Botany 82 : pp631-639 1998
   return  stress_factor; // 1 indicates no stress
}
//_2008-11-21________________________calc_flowering_temperature_stress_factor__/
float64 Crop_complete::accumulate_flowering_degree_minutes()       modification_
{
#ifdef HOURLY_THERMAL_TIME
   for (Hour hour= 0; hour <24; hour++)
   {  float64 air_temperature_hour = stress_adj_hourly_temperature.get(hour);    //130415
      if (air_temperature_hour > 31.0)
          flowering_degree_minutes +=
             hours_to_minutes(air_temperature_hour - 31.0);
   }
#endif
   return  flowering_degree_minutes;
}
//_2008-11-21______________________________accumulate_flowering_degree_minutes_/

#endif

