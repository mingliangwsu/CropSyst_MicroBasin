#include <common/weather/database/common_weather_monthly_creators.h>
#include <UED/library/UED_codes.h>

#define UED_DS_Y_V_U  UED::Record_type_distinguisher_interface::UED_data_set_year_var_units
//______________________________________________________________________________
Common_weather_monthly_creators::Common_weather_monthly_creators(CORN::Quality_code attribute)
: max_air_temperature_creation             (UED_DS_Y_V_U  ,UED_STD_VC_Tmax        ,UC_celcius    ,UT_month,UT_year ,attribute)
, min_air_temperature_creation             (UED_DS_Y_V_U  ,UED_STD_VC_Tmin        ,UC_celcius    ,UT_month,UT_year ,attribute)
, precipitation_creation               (UED_DS_Y_V_U  ,UED_STD_VC_precip      ,UC_mm         ,UT_month,UT_year ,attribute)
#ifdef NYN
   ,solar_radiation_creation           (UED_DS_Y_V_U  ,UED_STD_VC_Srad        ,UC_MJ_per_m2_solar_radiation,UT_month,UT_year, attribute)
   ,avg_temperature_creation           (UED_DS_Y_V_U  ,UED_STD_VC_Tavg        ,UC_celcius    ,UT_month,UT_year ,attribute )
   ,max_relative_humidity_creation     (UED_DS_Y_V_U  ,UED_STD_VC_RHmax       ,UC_percent    ,UT_month,UT_year , attribute)
   ,min_relative_humidity_creation     (UED_DS_Y_V_U  ,UED_STD_VC_RHmin       ,UC_percent    ,UT_month,UT_year , attribute)
   ,avg_relative_humidity_creation     (UED_DS_Y_V_U  ,UED_STD_VC_RHavg       ,UC_percent    ,UT_month,UT_year , attribute)
   ,max_dew_point_temperature_creation (UED_DS_Y_V_U  ,UED_STD_VC_Tdewmax     ,UC_celcius    ,UT_month,UT_year , attribute)
   ,min_dew_point_temperature_creation (UED_DS_Y_V_U  ,UED_STD_VC_Tdewmin     ,UC_celcius    ,UT_month,UT_year , attribute)
   ,avg_dew_point_temperature_creation (UED_DS_Y_V_U  ,UED_STD_VC_Tdewavg     ,UC_celcius    ,UT_month,UT_year , attribute)
   ,wind_speed_creation                (UED_DS_Y_V_U  ,UED_STD_VC_ws          ,UC_meters_per_second,UT_month,UT_year, attribute)
   ,wind_direction_creation            (UED_DS_Y_V_U  ,UED_STD_VC_WindDir     ,UC_degree_from_north,UT_month,UT_year, attribute)
   ,cloud_cover_creation               (UED_DS_Y_V_U  ,UED_STD_VC_cloud_cover ,UC_percent    ,UT_month,UT_year, attribute)
   ,isothermal_longwave_net_radiation_creation(UED_DS_Y_V_U ,UED_STD_VC_isoLWnetrad,UC_MJ_m2 ,UT_month,UT_year, attribute)
   ,net_radiation_creation             (UED_DS_Y_V_U  ,UED_STD_VC_rad_net     ,UC_MJ_m2      ,UT_month,UT_year, attribute)
   ,pot_evapotranspiration_creation    (UED_DS_Y_V_U  ,UED_STD_VC_ETpot       ,UC_mm         ,UT_month,UT_year, attribute)
   ,pot_evapotranspiration_FAO_Penman_Monteith_reference_creation(UED_DS_Y_V_U ,UED_STD_VC_PMETref ,UC_mm ,UT_month,UT_year, attribute)
   ,avg_daytime_vapor_pressure_deficit_creation(UED_DS_Y_V_U,UED_STD_VC_VPDdaytime,UC_kPa    ,UT_month,UT_year, attribute)
   ,avg_fullday_vapor_pressure_deficit_creation(UED_DS_Y_V_U,UED_STD_VC_VPDfullday,UC_kPa    ,UT_month,UT_year, attribute)
#ifdef NYI
   ,max_vapor_pressure_deficit_creator (UED_DS_Y_V_U  ,UED_STD_VC_XXXXXX ,UC_kPa  ,UT_month,UT_year, attribute)
#endif
   ,snow_depth_creation                (UED_DS_Y_V_U ,UED_STD_VC_snow_depth ,UC_mm   ,UT_month,UT_year, attribute)
   ,snow_fall_creation                 (UED_DS_Y_V_U ,UED_STD_VC_snow_fall    ,UC_mm   ,UT_month,UT_year, attribute)
#endif
{};
//_2009-03-03___________________________________________________________________
