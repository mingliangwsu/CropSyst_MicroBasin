#include "common/weather/database/common_weather_creators.h"
#include "UED/library/UED_codes.h"
//______________________________________________________________________________
Common_weather_creators::Common_weather_creators(CORN::Quality_code attribute)
:  max_temperature_creation                                                      //990902
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_Tmax, UC_Celcius, UT_day, UT_year, attribute)
    ,min_temperature_creation                                                    //990902
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_Tmin, UC_Celcius, UT_day, UT_year, attribute)
   ,avg_temperature_creation                                                     //070525
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_Tavg, UC_Celcius, UT_day, UT_year, attribute)
   ,instantaneous_temperature_creation                                           //050520
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_Tobs,UC_Celcius,UT_day,UT_year,attribute)
   ,solar_radiation_creation                                                     //990902
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    #if ((CS_VERSION >= 4) && (CS_VERSION <= 4))
    , UED_STD_VC_Srad_ERRONEOUS
    #else
    , UED_STD_VC_Srad_total //180808
    #endif
    , UC_MJ_per_m2_solar_radiation, UT_day, UT_year, attribute)
   ,max_relative_humidity_creation                                               //990902
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_RHmax, UC_percent, UT_day, UT_year, attribute)
   ,min_relative_humidity_creation                                               //990902
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_RHmin, UC_percent, UT_day, UT_year, attribute)
   ,avg_relative_humidity_creation                                               //990902
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_RHavg, UC_percent, UT_day, UT_year, attribute)
   ,precipitation_creation                                                       //990902
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_precip, UC_mm, UT_day, UT_year, attribute)
   ,max_dew_point_temperature_creation                                           //990902
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_Tdewmax, UC_Celcius, UT_day, UT_year, attribute)
   ,min_dew_point_temperature_creation                                           //990902
   ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_Tdewmin, UC_Celcius, UT_day, UT_year, attribute)
   ,avg_dew_point_temperature_creation                                           //990902
   ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_Tdewavg, UC_Celcius, UT_day, UT_year, attribute)
   ,wind_speed_creation                                                          //990902
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_ws, UC_meters_per_second, UT_day, UT_year, attribute)
   ,wind_direction_creation                                                      //050420
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_WindDir, UC_degree_from_north, UT_day, UT_year, attribute)
   ,cloud_cover_creation                                                         //000609
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_cloud_cover, UC_percent, UT_day, UT_year, attribute)
   ,isothermal_longwave_net_radiation_creation                                   //070204
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_isoLWnetrad, UC_MJ_m2, UT_day, UT_year, attribute)
   ,net_radiation_creation                                                       //070204
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_rad_net, UC_MJ_m2, UT_day, UT_year, attribute)
   ,pot_evapotranspiration_creation                                              //000609
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_ETpot, UC_mm, UT_day, UT_year, attribute)
   ,pot_evapotranspiration_FAO_Penman_Monteith_reference_creation                //070525
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_PMETref, UC_mm, UT_day, UT_year, attribute    )
   ,avg_daytime_vapor_pressure_deficit_creation                                  //000609
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_VPDdaytime, UC_kPa, UT_day, UT_year, attribute)
   ,avg_fullday_vapor_pressure_deficit_creation                                  //000609
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_VPDfullday , UC_kPa, UT_day, UT_year, attribute)
   ,avg_vapor_pressure_creation                                                  //110804
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_VP, UC_kPa, UT_day, UT_year, attribute)

#ifdef NYI
/*000609_*/    ,max_vapor_pressure_deficit_creator
/*_______*/     ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
/*_______*/     , UED_STD_VC_XXXXXX // 080311 checking initialization  UED::STD_VC_max_vapor_pressure_deficit.get()
/*040715_*/     , UC_kPa  // UC_kilo_pascal_atmospheric_pressure
/*_______*/     , UT_day   // Datum time_step
/*050415_*/     , UT_year  // Record time step
/*_______*/     , attribute
/*_______*/     )
#endif
   ,snow_depth_creation                                                          //000609
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_snow_depth,UC_mm,UT_day,UT_year,attribute)
   ,snow_fall_creation                                                           //000609
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_snow_fall, UC_mm , UT_day , UT_year , attribute)
   ,humidity_specific_creation                                                   //180808
    ( UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
    , UED_STD_VC_SH,UC_kg_kg , UT_day , UT_year , attribute)
{}
//______________________________________________________________________________
const UED::Data_record_creation_layout *Common_weather_creators::find_recognized_creation
(UED::Variable_code variable_code)
{  const UED::Data_record_creation_layout *recognized_creation = 0;
   switch (variable_code)
   {
      case UED_STD_VC_Tmax : recognized_creation =  &max_temperature_creation;                                       break;
      case UED_STD_VC_Tmin : recognized_creation =  &min_temperature_creation;                                       break;
      case UED_STD_VC_Tavg : recognized_creation =  &avg_temperature_creation;                                       break;
      case UED_STD_VC_Tobs : recognized_creation =  &instantaneous_temperature_creation;                             break;

      case
             #if ((CS_VERSION >= 4) || (CS_VERSION <= 4))
         UED_STD_VC_Srad_ERRONEOUS
         #else
         UED_STD_VC_Srad_total
         #endif
                            : recognized_creation =  &solar_radiation_creation;                                       break;
      case UED_STD_VC_isoLWnetrad : recognized_creation = & isothermal_longwave_net_radiation_creation;                     break;
      case UED_STD_VC_rad_net : recognized_creation =&  net_radiation_creation;                                         break;
      case UED_STD_VC_RHmax : recognized_creation = & max_relative_humidity_creation;                                 break;
      case UED_STD_VC_RHmin : recognized_creation = & min_relative_humidity_creation;                                break;
      case UED_STD_VC_RHavg : recognized_creation = & avg_relative_humidity_creation;                                 break;
      case UED_STD_VC_precip : recognized_creation = & precipitation_creation;                                         break;
      case UED_STD_VC_Tdewmax : recognized_creation =  &max_dew_point_temperature_creation;                             break;
      case UED_STD_VC_Tdewmin : recognized_creation =  &min_dew_point_temperature_creation;                             break;
      case UED_STD_VC_Tdewavg : recognized_creation =  &avg_dew_point_temperature_creation;                             break;
      case UED_STD_VC_ws : recognized_creation =  &wind_speed_creation;                                            break;
      case UED_STD_VC_WindDir : recognized_creation =  &wind_direction_creation;                                        break;
      case UED_STD_VC_cloud_cover : recognized_creation =  &cloud_cover_creation;                                           break;
      case UED_STD_VC_ETpot : recognized_creation =  &pot_evapotranspiration_creation;                                break;
      case UED_STD_VC_PMETref : recognized_creation =  &pot_evapotranspiration_FAO_Penman_Monteith_reference_creation;  break;
      case UED_STD_VC_VPDdaytime : recognized_creation =  &avg_daytime_vapor_pressure_deficit_creation;                    break;
   // case UED_STD_VC_VPDfullday : recognized_creation =  &avg_fullday_vapor_pressure_deficit_creation;                    break;
      case UED_STD_VC_snow_depth : recognized_creation =  &snow_depth_creation;                                            break;
      case UED_STD_VC_snow_fall : recognized_creation =  &snow_fall_creation;                                             break;
      case UED_STD_VC_VP         : recognized_creation = & avg_vapor_pressure_creation;   break; //110804
   } //switch
   return recognized_creation;
}
//_2010-01-25___________________________________________________________________

