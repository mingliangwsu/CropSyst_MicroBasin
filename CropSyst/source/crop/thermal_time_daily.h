#ifndef thermal_time_dailyH
#define thermal_time_dailyH

#include "crop/thermal_time_common.h"

namespace CropSyst
{
//______________________________________________________________________________
class Thermal_time_daily_linear
: public Thermal_time_common // NYI Thermal_time_daily_common
{
public:
   virtual float64 calc_growing_degree_day_daily_resolution                      //000330
      (float64 adjusted_max_temp                                                 //030610
      ,float64 air_temp_min)                                       calculation_;
      // This function calculates the normal growing degree day                  //019723
      // not limited by vernalization or photoperiod                             //019723

 public: // Constructor
   Thermal_time_daily_linear
      (const CropSyst::Crop_parameters_class::Thermal_time    &_parameters       //110218_080605
      ,const Physical::Temperature     &_stress_adjusted_temperature_max         //140625
      ,const Air_temperature_minimum   &_air_temperature_min                     //140626
      ,const Physical::Temperature     &_temperature_with_est_night              //140626
      ,const float64      &_ref_day_length_hours                                 //140812
      ,bool                _cropsyst_fruit_model                                 //041212
      ,const CropSyst:: Crop_parameters_struct::Vernalization  *_vernalization_parameters_optional  //080605
      ,const CropSyst:: Crop_parameters_struct::Photoperiod    *_photoperiod_parameters_optional);  //080605
};
//_2002-06-28___________________________________________________________________
class Thermal_time_daily_nonlinear
: public Thermal_time_common // NYI Thermal_time_daily_common
{
 public:
   Thermal_time_daily_nonlinear
      (const CropSyst::Crop_parameters_class::Thermal_time    &_parameters       //110218_080605
      ,const Physical::Temperature     &_stress_adjusted_temperature_max         //140625
      ,const Air_temperature_minimum   &_air_temperature_min                     //140626
      ,const Physical::Temperature     &_temperature_with_est_night              //140626
      ,const float64      &_ref_day_length_hours                                 //140812
      ,bool                                          _cropsyst_fruit_model       //041212
      ,const CropSyst:: Crop_parameters_struct::Vernalization  *_vernalization_parameters_optional  //080605
      ,const CropSyst:: Crop_parameters_struct::Photoperiod    *_photoperiod_parameters_optional);  //080605
   virtual float64 calc_growing_degree_day_daily_resolution                      //000330
      (float64 adjusted_max_temp                                                 //030610
      ,float64 air_temp_min)                                        calculation_;
};
//_2015-11-09___________________________________________________________________
} // namespace CropSyst
#endif
// crop_thermal_time.h

