#error This file is obsolete,  Replace with thermal_time thermal_time_daily and thermal_time_hourly

#include "crop/crop_thermal_time.h"
#include "crop/crop_param.h"
#include "corn/math/statistical/stats.h"
#include "corn/math/compare.hpp"
#include "crop/growth_stages.h"
#include "common/weather/parameter/WP_temperature.h"
//______________________________________________________________________________
Crop_thermal_time::Crop_thermal_time
( const CropSyst::Crop_parameters_class::Thermal_time    &_parameters            //110218
, const Physical::Temperature    &_stress_adjusted_temperature                   //150217
, const Air_temperature_minimum  &_air_temperature_min                           //150217
, const Physical::Temperature    &_temperature_with_est_night                    //150217
, const float64      &_ref_day_length_hours                                      //140812
, bool                        _cropsyst_fruit_model                              //041212
, const CropSyst::Crop_parameters_struct::Vernalization  *_vernalization_parameters
, const CropSyst::Crop_parameters_struct::Photoperiod    *_photoperiod_parameters)
:parameters                      (_parameters)
,cropsyst_fruit_model            (_cropsyst_fruit_model)                         //041212
,photoperiod_parameters          (_photoperiod_parameters)
,stress_adjusted_temperature     (_stress_adjusted_temperature)                  //140625
,air_temperature_min             (_air_temperature_min)                          //140625
,temperature_with_est_night      (_temperature_with_est_night)                   //140625
,ref_day_length_hours            (_ref_day_length_hours)                         //140812
,clipping_recovery_deg_days      (0)                                             //040826
,vernalization                   (0)                                             //111109
,growing_degree_day              (0)
,consecutive_days_no_accumulation(0)                                             //030515
{  clear_accum_degree_days();                                                    //140619
}
//______________________________________________________________________________
void Crop_thermal_time::clear_accum_degree_days()                  modification_
{
   for (int i = 0; i <= 1; i++)                                                  //140619
   {  accum_degree_days_normal [i] = 0.0;                                        //140619
      accum_degree_days_clipped[i] = 0.0;                                        //140619
   }
   //140619  accum_degree_days_normal = 0.0;
   //140619 accum_degree_days_clipped = 0.0;                                     //040823
   clipping_recovery_deg_days = 0.0;                                             //040826
   consecutive_days_no_accumulation = 0;                                         //030515
}
//______________________________________________________________________________
float64  Crop_thermal_time::Vernalization::update_factor
(float64 temperature)                                             rectification_
{  Vfactor =1.0;
   float64 temp_low   = parameters.low_temp;                                     //020628
   float64 temp_high  = parameters.high_temp;                                    //020628
   float64 vern_start = parameters.start;                                        //020628
   float64 vern_end   = parameters.end;                                          //020628
   float64 vern_day = (temperature > temp_high)
   ? (1.0 - (temperature - temp_high) / 7.0)
   : (temperature < temp_low)
      ? (1.0 - (temp_low - temperature) / 7.0)
      : 1.0;
   if (vern_day < 0.0)  vern_day = 0.0;
   vern_days += vern_day;
   if (vern_days > vern_start)
   {  Vfactor = (vern_days - vern_start) / (vern_end - vern_start);
      if (status != VERNALIZATION_ACTIVE)
      {   // output vernalization starts to log was here
          status  = VERNALIZATION_START;                                         //020628
      }
   }
   if ((vern_days >= vern_end) && (status == VERNALIZATION_ACTIVE))
   {  Vfactor = 1.0;
      vern_days = 0.0;                                                           //021204
      status = VERNALIZATION_END;                                                //020628
   }
   return Vfactor;
}
//_1997?________________________________________________________________________
float64 Crop_thermal_time::calc_photoperiod_factor
()
//140812 (float64 day_length_hours)
                                          calculation_
{
   float64 Pfactor =1.0;  // 1 has no effect
   if (photoperiod_parameters)
   {
   float64 stop_day_length          = photoperiod_parameters->stop_day_length;   // 0-24 hours
   float64 unconstrained_day_length = photoperiod_parameters->unconstrained_day_length; // 0-24 hours
   if (stop_day_length == unconstrained_day_length)
      return 1.0;     // Note: U = S not allowed
/*
Short-day crops
Daylength above which development towards flowering stops (hours)								14
Daylength below which development towards flowering is not constrained (hours)								10

Long-day crops
Daylength below which development towards flowering stops (hours)								10
Daylength above which development towards flowering is not constrained (hours)								14
*/
   float64 day_length_hours = ref_day_length_hours;                              //140812
   Pfactor =
            (unconstrained_day_length > stop_day_length)
            ?  // Long-day crop
               (day_length_hours <= stop_day_length)
               ? 0.0
               : day_length_hours > unconstrained_day_length
                  ? 1.0
                  : 1.0 - ((day_length_hours - unconstrained_day_length)
                          /(stop_day_length  - unconstrained_day_length))
            :  // Short-day crop
               (day_length_hours >  stop_day_length)
               ? 0.0
               : (day_length_hours < unconstrained_day_length)
                  ? 1.0
                  : 1.0 - ((day_length_hours - unconstrained_day_length )
                          /(stop_day_length - unconstrained_day_length));
  }
  return Pfactor;
}
//_2010-05-12___________________________________________________________________
float64 Crop_thermal_time::calc_growing_degree_day_hourly_resolution
( const CORN::Dynamic_array<float32> &stress_adj_hourly_temperature)         calculation_
{  // Adapted from Environmental BioPhysics (Gaylon Campbell)
   Statistical_running_tally hourly_thermal_time; // deg hours
   for (int hr = 0; hr < 24; hr++)
   {
      float64  plant_temperature = stress_adj_hourly_temperature.get(hr);        //030610
      float64  thermal_time =   // Degree hours ?                                //130415
         (  (plant_temperature <= parameters.base_temperature)                    //130415
          ||(plant_temperature >= parameters.max_temperature) )                    //130415
         ? 0.0                                                                   //130415
         : (plant_temperature <= parameters.opt_temperature)                     //130415
            ? (plant_temperature - parameters.base_temperature)             
            :  (parameters.opt_temperature - parameters.base_temperature) *      //130415
               (1.0 - ( (plant_temperature - parameters.opt_temperature)         //130415
                       /(parameters.max_temperature - parameters.opt_temperature)));//130415
      thermal_time = CORN::must_be_greater_or_equal_to<float64>(thermal_time,0.0);
      hourly_thermal_time.append(thermal_time);
   }
   // Warning we need to do senescence reduction etc...!!!
   float64 result_growing_degree_day = hourly_thermal_time.get_mean();
   return result_growing_degree_day;
}
//_2002-11-24___________________________________________________________________
float64 Crop_thermal_time::calc_growing_degree_day_daily_resolution
(float64 adjusted_max_temp                                                       //030610
,float64 air_temp_min)                                              calculation_
{  // value for a single day
   float64 deg_day_base_temp = parameters.base_temperature;
   float64 deg_day_cutoff_temp = parameters.cutoff_temperature;
   // During stress conditions the plant temperature may be a higher than air temperature
   float64 avg_plant_temp =
      (adjusted_max_temp
      + air_temp_min) /2.0;
   avg_plant_temp = (avg_plant_temp < deg_day_base_temp)
   ? deg_day_base_temp : avg_plant_temp;
   avg_plant_temp = (avg_plant_temp > deg_day_cutoff_temp)
   ? deg_day_cutoff_temp : avg_plant_temp;
   float64 result_growing_degree_day  = avg_plant_temp - deg_day_base_temp;
   return result_growing_degree_day;
 }
//_2000-03-30___________________________________________________________________
float64 Crop_thermal_time::calc_limited_growing_degree_day
(float64 growing_deg_day
,float64 vernalization_factor
,Normal_crop_event_sequence  growth_stage_sequence                               //130902
)                                       calculation_
{  float64 photofactor =
      photoperiod_parameters                                                     //020505
      ? calc_photoperiod_factor()                                                //140812
      : 1.0;
   float64 limit_factor = std::min<float64>(photofactor,vernalization_factor);
   if ((growth_stage_sequence == NGS_GERMINATION)                                //130902
   ||  (growth_stage_sequence >  NGS_ANTHESIS))      limit_factor = 1.0;         //130902_041213
   float64 limited_growing_degree_day =  growing_deg_day * limit_factor;
   return  limited_growing_degree_day;
}
//_2000-03-30___________________________________________________________________
double Crop_thermal_time::accumulate_degree_days
(Dynamic_array<float32> *stress_adj_hourly_temperature                           //071127
,Normal_crop_event_sequence growth_stage_sequence                                //130911
)
{  float64 vernalization_factor = 1.0;                                           //111109
   if (vernalization)                                                            //111109
   {  vernalization_factor = vernalization->update_factor(temperature_with_est_night.Celcius()); //150122_111109
      if (vernalization->is_satisfied())                                         //111109
      { delete vernalization; vernalization = 0; }                               //111109
   }
   growing_degree_day =                                                          //010723
   (parameters.is_hourly_resolution() && stress_adj_hourly_temperature)          //021125
   ? calc_growing_degree_day_hourly_resolution                                   //021125
      (*stress_adj_hourly_temperature)                                           //021125
   :   calc_growing_degree_day_daily_resolution                                  //021125
     (stress_adjusted_temperature.Celcius()                                      //140625
     ,air_temperature_min.Celcius());                                            //140625_021125
   float64 limited_grow_deg_day = calc_limited_growing_degree_day                //010723
      (growing_degree_day
      //140812 ,day_length_hours
      ,vernalization_factor, growth_stage_sequence); //130911
      //not sure if this is correct, it wasn't set up right, need to check if we still want to do this
   if (clipping_recovery_deg_days > 0.0)                                         //040826
   {  accum_degree_days_normal[TT_TODAY] += 0.001;                               //040826
         // Only slight accumulation to prevent any consecutive days of no accumulation problems
      if  (clipping_recovery_deg_days < 0.0) clipping_recovery_deg_days = 0.0;   //040826
         // Shouldn't be necessary, but just to keep it clean;
      else clipping_recovery_deg_days -= limited_grow_deg_day;                   //040826
         // I think use limited_grow_deg_day
   } else                                                                        //040826
      accum_degree_days_normal[TT_TODAY] += limited_grow_deg_day;
   accum_degree_days_clipped[TT_TODAY] += limited_grow_deg_day;                  //040830
   if (                                                                          //041213
   //041213_         Claudio says now use this only for the fruit model.
   //050720 decided not to do this:
       cropsyst_fruit_model &&   // Claudio decided again to restore this only for fruit, may need to eliminate it completely  //050816
     CORN::is_approximately<float64>(growing_degree_day,0.0,0.001))
   {  // If there are a number of consecutive days of no thermal time accum,     //030515
      // then we throw away the accumulation (happens during winter).            //030515
      consecutive_days_no_accumulation +=1;                                      //030515
      if (consecutive_days_no_accumulation == 10)                                //030515
      {  clear_accum_degree_days();                                              //030515
         consecutive_days_no_accumulation = 0;                                   //030515
      }
   } else                                                                        //030515
   {   consecutive_days_no_accumulation = 0; }                                   //030523
   return growing_degree_day;                                                    //010727
}
//______________________________________________________________________________
/* NYI
float64 Crop_thermal_time::update ()                               modification_
{
this would do what accumulate_degree_days does
but with member variables
}
//_2014-06-26___________________________________________________________________
*/
void Crop_thermal_time::respond_to_clipping(float64 new_thermal_time) modification_
{
#ifdef disabled
this may be too long a period
clipping_recovery_deg_days = 1.5 * new_thermal_time ;
#else
clipping_recovery_deg_days = 0.0;
#endif
   accum_degree_days_clipped[TT_TODAY] = new_thermal_time;
}
//_2004-08-23___________________________________________________________________
void Crop_thermal_time::reset_to(float64 new_thermal_time)
{  accum_degree_days_clipped[TT_TODAY] = new_thermal_time ;
}
//_2004-07-19___________________________________________________________________
float64 Crop_thermal_time::get_accum_degree_days
(bool adjusted_for_clipping
,bool for_yesterday
) const
{  return adjusted_for_clipping
      ? accum_degree_days_clipped[for_yesterday]
      : accum_degree_days_normal [for_yesterday];
}
//______________________________________________________________________________
Crop_thermal_time::Vernalization::Vernalization
(const CropSyst::Crop_parameters_struct::Vernalization &_parameters)
:parameters(_parameters)
,status(VERNALIZATION_INACTIVE)
,vern_days(0)
,Vfactor(1.0)
{}
//_2011-11-09___________________________________________________________________
bool Crop_thermal_time::enable_vernalization
(const CropSyst::Crop_parameters_struct::Vernalization &vernalization_parameters)
modification_
{  vernalization = new Vernalization(vernalization_parameters);
   return true;                                                                  //120804
}
//_2011-11-09___________________________________________________________________
bool Crop_thermal_time::end_day()                                  modification_
{  accum_degree_days_normal  [TT_YESTERDAY] = accum_degree_days_normal [TT_TODAY];
   accum_degree_days_clipped [TT_YESTERDAY] = accum_degree_days_clipped[TT_TODAY];//040823
   return true;
}
//_2014-06-19___________________________________________________________________

