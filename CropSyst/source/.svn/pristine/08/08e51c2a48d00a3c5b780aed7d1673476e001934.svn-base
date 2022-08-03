#ifndef biomass_growth_RUE_TUEH
#define biomass_growth_RUE_TUEH
#include "crop/biomass_growth.h"
#include "common/weather/parameter/WP_solar_radiation.h"
#ifdef YAML_PARAM_VERSION
#  include "crop/transpiration_dependent_growth.h"
#else
#  include "crop/transpiration_dependent_growth_V4.h"
#endif
#include "corn/math/statistical/stats.h"
#include "common/weather/parameter/WP_air_temperature.h"
namespace CropSyst
{
class Thermal_time_common;
class Crop_CO2_response;
class Canopy_growth_interface;
class Crop_parameters;
class Biomass_production_transpiration_dependent_V4;
class Biomass_production_transpiration_dependent_V5 ;

//class Solar_radiation;
//______________________________________________________________________________
class Biomass_growth_RUE_TUE
: public implements_ Biomass_growth
{
   bool                                 orchard_model;
   const Crop_parameters               *parameters;
   const Normal_crop_event_sequence    &growth_stage;
   const nat8                          &season;
   const float64                       *pot_transpiration_m; // [2];
   const bool                          &at_max_fruit_load;                       //180308

   //local float64  RUE_temperature_limitation_factor;
   const Thermal_time_common           *thermal_time; // from crop common
   const Crop_CO2_response             *CO2_response;
   const Canopy_growth_interface       *canopy;
   const Air_temperature_average       &air_temperature_avg;            //140225
   const Solar_radiation               &solar_radiation;
   const float64                       &intercepted_radiation;


   #ifdef YAML_PARAM_VERSION
   // Using adjustable parameter idiom
   const CropSyst::Biomass_production_transpiration_dependent_V5 &transpiration_dependent_growth;
   #else
   const CropSyst::Biomass_production_transpiration_dependent_V4 &transpiration_dependent_growth;
   #endif

   mutable CORN::Statistical_sample_cumulative<float64,float64> /*180408 Statistical_running_index*/
      &report_temperature_stress_stats;

 public:
   Biomass_growth_RUE_TUE
      (bool                                orchard_model_
      ,const Crop_parameters              *parameters_
      ,const Normal_crop_event_sequence   &growth_stage_
      ,const nat8                         &season_
      ,const float64                      *pot_transpiration_m_ //[2]
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
      ,CORN::Statistical_sample_cumulative<float64,float64>
         /*180408 Statistical_running_index */   &report_temperature_stress_stats
      ,const bool                         &is_at_max_fruit_load
      );

   inline virtual bool start()                       modification_{return true;}
   inline virtual bool process_day()                 modification_{return true;}

   virtual float64 calc_attainable_top_growth(/*abandoned bool is_at_max_fruit_load*/ )  calculation_; //180308

   // Note that calc_RUE_temperature_limitation is not applicable to Orchard model where it is always 1.0
   // so orchard model should have its own Biomass_growth
   // which overrides calc_RUE_temperature_limitation returning 1.0
 private:
   virtual float64 calc_RUE_temperature_limitation()               calculation_;
   float64 get_radiation_use_efficiency_global()                          const;

};
//_2018-01-11___________________________________________________________________
} // namespace CropSyst
#endif
