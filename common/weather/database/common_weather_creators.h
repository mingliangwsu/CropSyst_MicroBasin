#ifndef common_weather_creatorsH
#define common_weather_creatorsH

#include "UED/library/datasetrec_creation.h"
//______________________________________________________________________________
class Common_weather_creators
{
public:
   UED::Data_record_creation_layout  max_temperature_creation;                   //990902
   UED::Data_record_creation_layout  min_temperature_creation;                   //990902
   UED::Data_record_creation_layout  avg_temperature_creation;                   //070525
   UED::Data_record_creation_layout  instantaneous_temperature_creation;         //050520
   #define obs_temperature_creation  instantaneous_temperature_creation
   UED::Data_record_creation_layout  solar_radiation_creation;//solar irradiance //990902
   UED::Data_record_creation_layout  isothermal_longwave_net_radiation_creation; //070204
   UED::Data_record_creation_layout  net_radiation_creation;                     //070204

      //180808 renamed XXX_relative_humidity_creation to humidity_relative_creationg

   UED::Data_record_creation_layout  max_relative_humidity_creation;             //990902
   UED::Data_record_creation_layout  min_relative_humidity_creation;             //990902
   UED::Data_record_creation_layout  avg_relative_humidity_creation;             //990902
   UED::Data_record_creation_layout  precipitation_creation;   // Liquid water equivelent //990902
   UED::Data_record_creation_layout  max_dew_point_temperature_creation;         //990902
   UED::Data_record_creation_layout  min_dew_point_temperature_creation;         //990902
   UED::Data_record_creation_layout  avg_dew_point_temperature_creation;         //990902
   UED::Data_record_creation_layout  wind_speed_creation;                        //990902
   UED::Data_record_creation_layout  wind_direction_creation;                    //990902
   UED::Data_record_creation_layout  cloud_cover_creation;                       //991022
   UED::Data_record_creation_layout  pot_evapotranspiration_creation;            //990902
   UED::Data_record_creation_layout  pot_evapotranspiration_FAO_Penman_Monteith_reference_creation; //070525
      //180806 rename  actually these are ET_reference_creation;
   UED::Data_record_creation_layout  avg_daytime_vapor_pressure_deficit_creation;//000612
   UED::Data_record_creation_layout  avg_fullday_vapor_pressure_deficit_creation;//011009
   UED::Data_record_creation_layout  avg_vapor_pressure_creation;                //110805
   UED::Data_record_creation_layout  snow_depth_creation;
   UED::Data_record_creation_layout  snow_fall_creation;

   UED::Data_record_creation_layout  humidity_specific_creation;                 //180808

public:
   Common_weather_creators(CORN::Quality_code attribute);
   const UED::Data_record_creation_layout *find_recognized_creation(UED::Variable_code variable_code);   //100125
};
//______________________________________________________________________________
#endif

