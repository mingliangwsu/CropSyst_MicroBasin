#include "crop/thermal_time_hourly.h"
#include "corn/math/statistical/stats.h"
#include "corn/math/compare.hpp"
namespace CropSyst
{
//______________________________________________________________________________
Thermal_time_hourly::Thermal_time_hourly
( const CropSyst::Crop_parameters_class::Thermal_time    &_parameters            //110218
, const Physical::Temperature    &_stress_adjusted_temperature                   //150217
, const Air_temperature_minimum  &_air_temperature_min                           //150217
, const Physical::Temperature    &_temperature_with_est_night                    //150217
, const float64      &_ref_day_length_hours                                      //140812
, bool                        _cropsyst_fruit_model                              //041212
, const CropSyst::Crop_parameters_struct::Vernalization  *_vernalization_parameters
, const CropSyst::Crop_parameters_struct::Photoperiod    *_photoperiod_parameters)
: Thermal_time_common
   (_parameters
   ,_stress_adjusted_temperature
   ,_air_temperature_min
   ,_temperature_with_est_night
   ,_ref_day_length_hours
   ,_cropsyst_fruit_model
   ,_vernalization_parameters
   ,_photoperiod_parameters
   )
{}
//______________________________________________________________________________
float64 Thermal_time_common::calc_growing_degree_day_hourly_resolution
( const CORN::Dynamic_array<float32> &stress_adj_hourly_temperature)         calculation_
{  // Adapted from Environmental BioPhysics (Gaylon Campbell)
   Statistical_running_tally hourly_thermal_time; // deg hours
   for (int hr = 0; hr < 24; hr++)
   {
      float64  plant_temperature = stress_adj_hourly_temperature.get(hr);        //030610
      float64  thermal_time =   // Degree hours ?                                //130415
         (  (plant_temperature <= parameters.base_temperature)                   //130415
          ||(plant_temperature >= parameters.max_temperature) )                  //130415
         ? 0.0                                                                   //130415
         : (plant_temperature <= parameters.opt_temperature)                     //130415
            ? (plant_temperature - parameters.base_temperature)             
            :  (parameters.opt_temperature - parameters.base_temperature) *      //130415
               (1.0 - ( (plant_temperature - parameters.opt_temperature)         //130415
                       /(parameters.max_temperature - parameters.opt_temperature)));//130415
      thermal_time = CORN::must_be_0_or_greater<float64>(thermal_time);          //151110
      hourly_thermal_time.append(thermal_time);
   }
   // Warning we need to do senescence reduction etc...!!!
   float64 result_growing_degree_day = hourly_thermal_time.get_mean();
   return result_growing_degree_day;
}
//_2002-11-24___________________________________________________________________
} // namespace CropSyst

