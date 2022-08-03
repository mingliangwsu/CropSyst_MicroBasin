#include "std_variables.h"

#include "UED/library/std_codes.h"
#include "UED/library/variable_format.h"

namespace UED {
//______________________________________________________________________________

CORN::Units_clad STD_UC_meters_per_sec              (UM_linear ,U_metric_base,UT_second); //040715
CORN::Units_clad STD_UC_depth_meters                (UM_linear ,U_metric_base);           //040715
CORN::Units_clad STD_UC_depth_millimeters           (UM_linear ,U_metric_milli);          //040715

Variable_code_clad STD_VC_date                     (UED_temporal,                      UED_at_time_step,false);  //020907
// Note, for dates, the units will specify the date, I.e. Year and DOY, Year, DOY, month, DOM etc.
Variable_code_clad STD_VC_precipitation            (UED_climate_precipitation,         UED_total_for_time_step,  false);
Variable_code_clad STD_VC_max_temperature          (UED_climate_air_temperature,       UED_maximum_for_time_step,false);
Variable_code_clad STD_VC_min_temperature          (UED_climate_air_temperature,       UED_minimum_for_time_step,false);
Variable_code_clad STD_VC_avg_temperature          (UED_climate_air_temperature,       UED_average_for_time_step,false);  //000701
Variable_code_clad STD_VC_obs_temperature          (UED_climate_air_temperature,       UED_at_time_step         ,false);  //020427
Variable_code_clad STD_VC_max_dew_point_temperature(UED_climate_dew_point_temperature, UED_maximum_for_time_step,false);
Variable_code_clad STD_VC_min_dew_point_temperature(UED_climate_dew_point_temperature, UED_minimum_for_time_step,false);
Variable_code_clad STD_VC_avg_dew_point_temperature(UED_climate_dew_point_temperature, UED_average_for_time_step,false);  //050601
Variable_code_clad STD_VC_max_relative_humidity    (UED_climate_relative_humidity,     UED_maximum_for_time_step,false);
Variable_code_clad STD_VC_min_relative_humidity    (UED_climate_relative_humidity,     UED_minimum_for_time_step,false);
Variable_code_clad STD_VC_avg_relative_humidity    (UED_climate_relative_humidity,     UED_average_for_time_step,false);  //050419
Variable_code_clad STD_VC_solar_radiation_global   (UED_climate_solar_radiation,       UED_total_for_time_step,false);    //100222
Variable_code_clad STD_VC_isothermal_longwave_net_radiation(UED_climate_isothermal_longwave_net_radiation,       UED_total_for_time_step,false);                                   //100222
Variable_code_clad STD_VC_net_radiation                    (UED_climate_net_radiation,        UED_total_for_time_step,false);                                                      //100222

Variable_code_clad STD_VC_humidity_specific    (UED_climate_humidity_specific,         UED_average_for_time_step,false); //180808

#if (CS_VERSION < 6)
// I had incorrectly assumed the solar radiation was an average daily value
// It is actually a cumulative value totaled for the time step.
// I need to make sure that I can continue to recognize the old value
Variable_code_clad STD_VC_solar_radiation_ERRONEOUS              (UED_climate_solar_radiation,       UED_average_for_time_step,false); // Actually this is cumulative for the timestep!!!!  //100222
Variable_code_clad STD_VC_isothermal_longwave_net_radiation_ERRONEOUS(UED_climate_isothermal_longwave_net_radiation,       UED_average_for_time_step,false);                               //100222
Variable_code_clad STD_VC_net_radiation_ERRONEOUS                (UED_climate_net_radiation,        UED_average_for_time_step,false);                                                      //100222
#endif
Variable_code_clad STD_VC_solar_radiation_avg_hourly(UED_climate_solar_radiation_hourly,       UED_average_for_time_step,false);  // this is indeed average for time step (average of the hourly values for the day) //100222
// Normally the timestep corresponds to the timestep of a data record,
// this is for a special case where the the daily value is the average of the hourly values
// hopefully this was an aberation
Variable_code_clad STD_VC_sunshine_hours             (UED_climate_sunshine_hours,       UED_total_for_time_step,false); //100222
   // I have encountered an instance where the daily recorded solar radiation was the average of the hourly values (Watt-hours)
   // In this case the hours of sunshine are give
Variable_code_clad STD_VC_wind_speed               (UED_climate_wind_speed,            UED_average_for_time_step,false);
Variable_code_clad STD_VC_UAS                      (UED_climate_UAS,                   UED_average_for_time_step,false); //171022
Variable_code_clad STD_VC_VAS                      (UED_climate_VAS,                   UED_average_for_time_step,false); //171022
Variable_code_clad STD_VC_wind_direction           (UED_climate_wind_direction,        UED_average_for_time_step,false);  //050419

Variable_code_clad STD_VC_pot_evapotranspiration   (UED_climate_pot_evapotranspiration ,UED_total_for_time_step,  false);                        //000611
Variable_code_clad STD_VC_act_evapotranspiration   (UED_climate_act_evapotranspiration ,UED_total_for_time_step,  false);                        //000611
Variable_code_clad STD_VC_pan_evaporation          (UED_climate_pan_evaporation        ,UED_total_for_time_step,  false);                        //000611
Variable_code_clad STD_VC_ref_ET_Penman_Monteith   (UED_climate_ref_ET_Penman_Monteith ,UED_total_for_time_step,  false);                        //000731
Variable_code_clad STD_VC_ref_ET_Priestly_Taylor   (UED_climate_ref_ET_Priestly_Taylor ,UED_total_for_time_step,  false);                        //000731
Variable_code_clad STD_VC_ref_ET_Hargreaves          (UED_climate_ref_ET_Hargreaves       ,UED_total_for_time_step,  false);                     //000731
Variable_code_clad STD_VC_ref_ET_ASCE_EWRI_short_crop(UED_climate_ref_ET_ASCE_EWRI_short_crop   ,UED_total_for_time_step,  false);               //091005
Variable_code_clad STD_VC_ref_ET_ASCE_EWRI_tall_crop (UED_climate_ref_ET_ASCE_EWRI_tall_crop    ,UED_total_for_time_step,  false);               //091005

Variable_code_clad STD_VC_vapor_pressure_deficit(UED_climate_vapor_pressure_deficit,UED_average_for_time_step,  false);                          //101212
Variable_code_clad STD_VC_avg_daytime_vapor_pressure_deficit(UED_climate_vapor_pressure_deficit_daytime,UED_average_for_time_step,  false);      //000611
Variable_code_clad STD_VC_avg_fullday_vapor_pressure_deficit(UED_climate_vapor_pressure_deficit_fullday,UED_average_for_time_step,  false);      //011009
Variable_code_clad STD_VC_max_vapor_pressure_deficit(UED_climate_vapor_pressure_deficit,UED_maximum_for_time_step,  false);                      //000611
Variable_code_clad STD_VC_vapor_pressure_actual    (UED_climate_vapor_pressure_actual,UED_average_for_time_step,  false);                        //101205
Variable_code_clad STD_VC_atmospheric_pressure(UED_climate_atmospheric_pressure,UED_average_for_time_step,  false);                              //101205
                                                                                          // warning I am assuming atmospheric_vapor_pressure is the average for the day
Variable_code_clad STD_VC_cloud_cover              (UED_climate_cloud_cover            ,UED_average_for_time_step,false);                        //000611
Variable_code_clad STD_VC_snow_fall                (UED_climate_snow_fall    ,         UED_total_for_time_step,  false);                         //020427
Variable_code_clad STD_VC_snow_depth               (UED_climate_snow_depth   ,         UED_at_time_step       ,  false);                         //020427
//______________________________________________________________________________
Variable_format_0  STD_VD_date                      (STD_VC_date.get()                       ,UT_date                   ,0.0        ,9999999.0  ,0.0      ,9999999.0,"Date","date");   //020907
Variable_format_0  STD_VD_precipitation             (STD_VC_precipitation.get()              ,UC_mm                     ,0.0        ,1000.0     ,0.0      ,10000.0  ,"precipitation (liquid equivelent)","precip");

Variable_format_0  STD_VD_max_temperature           (STD_VC_max_temperature.get()            ,UC_Celcius                ,-50.0      ,50.0       ,-100.0   ,100.0    ,"max. air temperature","Tmax");
Variable_format_0  STD_VD_min_temperature           (STD_VC_min_temperature.get()            ,UC_Celcius                ,-50.0      ,50.0       ,-100.0   ,100.0    ,"min. air temperature","Tmin");
Variable_format_0  STD_VD_avg_temperature           (STD_VC_avg_temperature.get()            ,UC_Celcius                ,-50.0      ,50.0       ,-100.0   ,100.0    ,"avg. air temperature","Tavg");                   //000701
Variable_format_0  STD_VD_obs_temperature           (STD_VC_obs_temperature.get()            ,UC_Celcius                ,-50.0      ,50.0       ,-100.0   ,100.0    ,"observed air temperature","Tobs");               //020427
Variable_format_0  STD_VD_max_dew_point_temperature (STD_VC_max_dew_point_temperature.get()  ,UC_Celcius                ,-50.0      ,50.0       ,-100.0   ,100.0    ,"max. dew pt. temperature","Tdewmax");
Variable_format_0  STD_VD_min_dew_point_temperature (STD_VC_min_dew_point_temperature.get()  ,UC_Celcius                ,-50.0      ,50.0       ,-100.0   ,100.0    ,"min. dew pt. temperature","Tdewmin");
Variable_format_0  STD_VD_avg_dew_point_temperature (STD_VC_avg_dew_point_temperature.get()  ,UC_Celcius                ,-50.0      ,50.0       ,-100.0   ,100.0    ,"avg. dew pt. temperature","Tdewavg"); //050601

// We allow max relative humidity to slightly exceed 100                         001026
// Relative humidity should also be non 0 value, (we will use 1)
Variable_format_0  STD_VD_max_relative_humidity     (STD_VC_max_relative_humidity.get()      ,UC_percent                ,1.0     ,105.0   ,0.01    ,110.0    ,"max. relative humidity","RHmax");
Variable_format_0  STD_VD_min_relative_humidity     (STD_VC_min_relative_humidity.get()      ,UC_percent                ,1.0     ,100.0   ,0.01    ,100.0    ,"min. relative humidity","RHmin");
Variable_format_0  STD_VD_avg_relative_humidity     (STD_VC_avg_relative_humidity.get()      ,UC_percent                ,1.0     ,100.0   ,0.01    ,100.0    ,"avg. relative humidity","RHavg");
Variable_format_0  STD_VD_humidity_specific         (STD_VC_humidity_specific.get()          ,UC_kg_kg                  ,0.5     ,100.0   ,0.001    ,1.0    ,"humidity specific","huss"); //180808
Variable_format_0  STD_VD_solar_radiation_global    (STD_VC_solar_radiation_global.get()     ,UC_MJ_per_m2_solar_radiation  ,0.001   ,40.0    ,0.001   ,50.0     ,"solar radiation","Srad");
Variable_format_0  STD_VD_isothermal_longwave_net_radiation(STD_VC_isothermal_longwave_net_radiation.get()            ,UC_MJ_per_m2  ,0.001   ,40.0    ,0.001   ,50.0     ,"isothermal longwave net radiation","isoLWnetrad");//070203
Variable_format_0  STD_VD_net_radiation             (STD_VC_net_radiation.get()             ,UC_MJ_per_m2   ,0.001   ,40.0    ,0.001   ,50.0     ,"net radiation","rad_net"); //070203
#if (CS_VERSION<6)
// This is provided for reading version 4 files.
Variable_format_0  STD_VD_solar_radiation_ERRONEOUS           (STD_VC_solar_radiation_ERRONEOUS.get()            ,UC_MJ_per_m2_solar_radiation  ,0.001   ,40.0    ,0.001   ,50.0     ,"solar radiation","Srad");
Variable_format_0  STD_VD_isothermal_longwave_net_radiation_ERRONEOUS(STD_VC_isothermal_longwave_net_radiation_ERRONEOUS.get()            ,UC_MJ_per_m2  ,0.001   ,40.0    ,0.001   ,50.0     ,"isothermal longwave net radiation","isoLWnetrad"); //070203
Variable_format_0  STD_VD_net_radiation_ERRONEOUS             (STD_VC_net_radiation_ERRONEOUS.get()             ,UC_MJ_per_m2   ,0.001   ,40.0    ,0.001   ,50.0     ,"net radiation","rad_net");  //070203
#endif

Variable_format_0  STD_VD_solar_radiation_avg_hourly(STD_VC_solar_radiation_avg_hourly .get() ,UC_MJ_per_m2_solar_radiation  ,0.001   ,40.0    ,0.001   ,50.0     ,"solar radiation (avg hourly)","SradAvgHr");         //100222
Variable_format_0  STD_VD_sunshine_hours            (STD_VC_sunshine_hours             .get() ,UT_1_hour                     ,0.001   ,24.0  ,0.0   ,24.0     ,"sunshine hours","sunhours");                            //100222
Variable_format_0  STD_VD_wind_speed                (STD_VC_wind_speed                 .get() ,UC_meters_per_second      ,0.0     ,80.0   ,0.0     ,100.0   ,"wind speed","ws");
Variable_format_0  STD_VD_UAS                       (STD_VC_UAS                        .get() ,UC_meters_per_second      ,0.0     ,80.0   ,0.0     ,100.0   ,"zonal","uas"); //171022
Variable_format_0  STD_VD_VAS                       (STD_VC_VAS                        .get() ,UC_meters_per_second      ,0.0     ,80.0   ,0.0     ,100.0   ,"medidional","vas"); //171022
Variable_format_0  STD_VD_wind_direction            (STD_VC_wind_direction             .get() ,UC_degree_from_north      ,0.0     ,360.0   ,0.0     ,361.0    ,"wind direction","WindDir");
Variable_format_0  STD_VD_pot_evapotranspiration    (STD_VC_pot_evapotranspiration     .get() ,UC_mm          ,0.0,1000.0,0.0,10000.0,"pot.evapotranspiration","ETpot");                                               //000611
Variable_format_0  STD_VD_act_evapotranspiration    (STD_VC_act_evapotranspiration     .get() ,UC_mm          ,0.0,1000.0,0.0,10000.0,"act.evapotranspiration","ETact");                                               //000611
Variable_format_0  STD_VD_pan_evaporation           (STD_VC_pan_evaporation            .get() ,UC_mm          ,0.0,1000.0,0.0,10000.0,"pan evaporation","ETpan");                                                      //020505
Variable_format_0  STD_VD_ref_ET_Penman_Monteith    (STD_VC_ref_ET_Penman_Monteith     .get() ,UC_mm          ,0.0,1000.0,0.0,10000.0,"ref.evapotranspiration Penman-Monteith","PMETref");                             //000731
Variable_format_0  STD_VD_ref_ET_Priestly_Taylor    (STD_VC_ref_ET_Priestly_Taylor     .get() ,UC_mm          ,0.0,1000.0,0.0,10000.0,"ref.evapotranspiration Priestly-Taylor","PTETref");                             //000731
Variable_format_0  STD_VD_ref_ET_Hargreaves          (STD_VC_ref_ET_Hargreaves         .get() ,UC_mm          ,0.0,1000.0,0.0,10000.0,"ref.evapotranspiration Hargreaves","HarETref");                                 //000731
Variable_format_0  STD_VD_ref_ET_ASCE_EWRI_short_crop(STD_VC_ref_ET_ASCE_EWRI_short_crop.get(),UC_mm          ,0.0,1000.0,0.0,10000.0,"ref.evapotranspiration ASCE-EWRI short crop","EWRIETrefshort");      //091005
Variable_format_0  STD_VD_ref_ET_ASCE_EWRI_tall_crop (STD_VC_ref_ET_ASCE_EWRI_tall_crop.get() ,UC_mm          ,0.0,1000.0,0.0,10000.0,"ref.evapotranspiration ASCE-EWRI tall crop","EWRIETreftall");                   //091005
Variable_format_0  STD_VD_avg_daytime_vapor_pressure_deficit    (STD_VC_avg_daytime_vapor_pressure_deficit.get(),UC_kPa ,0.0,5.0,0.0,6.0,"daytime vapor pressure deficit","VPDdaytime");                               //000611
Variable_format_0  STD_VD_avg_fullday_vapor_pressure_deficit    (STD_VC_avg_fullday_vapor_pressure_deficit.get(),UC_kPa ,0.0,5.0,0.0,6.0,"fullday vapor pressure deficit","VPDfullday");                               //160214_011009
Variable_format_0  STD_VD_max_vapor_pressure_deficit    (STD_VC_max_vapor_pressure_deficit.get()                ,UC_kPa ,0.0,8.0,0.0,10.0,"vapor pressure deficit","VPD");                                             //000611

Variable_format_0  STD_VD_cloud_cover               (STD_VC_cloud_cover.get()                ,UC_percent      ,0.0,100.0   ,0.0,100.0,"cloud cover","cloud_cover");                                          //000611
Variable_format_0  STD_VD_snow_fall                 (STD_VC_snow_fall.get()                  ,UC_mm           ,0.0,10000.0 ,0.0,10000.0 ,"snow fall","snow_fall");                                                     //020427
Variable_format_0  STD_VD_snow_depth                (STD_VC_snow_depth.get()                 ,UC_mm           ,0.0,100000.0,0.0,100000.0,"snow depth","snow_depth");                                                   //020427
//Variable_format_0  STD_VD_                          (STD_VC_XX.get()                ,UED_STD_UD_XX            ,min_warning,max_warning,min_error,max_error,"XXX");
//Variable_format_0  STD_VD_                          (STD_VC_XX.get()                ,UED_STD_UD_XX            ,min_warning,max_warning,min_error,max_error,"XXX");
//______________________________________________________________________________
}; // namespace UED

