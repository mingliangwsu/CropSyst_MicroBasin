#ifndef thermal_time_hourlyH
#define thermal_time_hourlyH

// This was removed from CropSyst 4  2015-11-09

#include "options.h"
#include "crop/thermal_time_common.h"
#include "CS_suite/observation/CS_inspection.h"
namespace CropSyst
{
//______________________________________________________________________________
class Thermal_time_hourly
: public implements_ Thermal_time_common
{
 public:
   float64 calc_growing_degree_day_hourly_resolution                             //021124
      (const CORN::Dynamic_array<float32> &stress_adj_hourly_temperature) calculation_;//030610
 public: // Constructor
   Thermal_time_hourly
      (const CropSyst::Crop_parameters_class::Thermal_time    &_parameters       //110218_080605
      ,const Physical::Temperature     &_stress_adjusted_temperature             //140625
      ,const Air_temperature_minimum   &_air_temperature_min                     //140626
      ,const Physical::Temperature     &_temperature_with_est_night              //140626
      ,const float64      &_ref_day_length_hours                                 //140812
      ,bool                                          _cropsyst_fruit_model       //041212
      ,const CropSyst:: Crop_parameters_struct::Vernalization  *_vernalization_parameters_optional  //080605
      ,const CropSyst:: Crop_parameters_struct::Photoperiod    *_photoperiod_parameters_optional
      );  //080605
};
//_2002-06-28___________________________________________________________________
} // namespace CropSyst
#endif

