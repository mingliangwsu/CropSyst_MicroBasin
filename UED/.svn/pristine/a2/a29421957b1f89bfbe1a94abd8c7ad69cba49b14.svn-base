
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#ifndef units_cladH
#   include "corn/metrology/units_clad.h"
#endif
#include "UED/library/std_codes.h"
#include "corn/string/strconv.hpp"

// for MSC
#   ifdef _MSC_VER
#      define stricmp(x,y) _stricmp(x,y)
#   endif
namespace UED {
//______________________________________________________________________________
UED_variable_code Identify_standard_variable_code(const char *variable_label)
{
   // Convert to lower case to reduce comparisons
   char var_lc[255];
   strcpy(var_lc,variable_label);
   if (stricmp(var_lc,"date") == 0)
     return STD_VC_date.get();
   if ((stricmp(var_lc ,"precip")==0)
     ||(stricmp(var_lc ,"prcp")==0)
     ||(stricmp(var_lc , "precipitation")==0))
     return STD_VC_precipitation.get();
   if ((stricmp(var_lc, "tmax")==0)
     ||(stricmp(var_lc, "temperature(max)")==0)
     ||(stricmp(var_lc, "temperature_max")==0))
     return STD_VC_max_temperature.get();
   if ((stricmp(var_lc, "tmin")==0)
     ||(stricmp(var_lc, "temperature(min)")==0)
     ||(stricmp(var_lc, "temperature_min")==0))
     return STD_VC_min_temperature.get();
   if ((stricmp(var_lc, "tavg")==0)
     ||(stricmp(var_lc, "temperature(avg)")==0)
     ||(stricmp(var_lc, "temperature_avg")==0))
     return STD_VC_avg_temperature.get();
   if ((stricmp(var_lc, "tobs")==0)
     ||(stricmp(var_lc, "temperature(obs)")==0)
     ||(stricmp(var_lc, "temperature_obs")==0))
     return STD_VC_obs_temperature.get();  // temperature observed at time step
   if ((stricmp(var_lc, "tdewmax")==0)
     ||(stricmp(var_lc, "dptmax")==0)
     ||(stricmp(var_lc, "dew_point(max)")==0)
     ||(stricmp(var_lc, "dew_point_temperature(max)")==0)
     ||(stricmp(var_lc, "max_dew_point_temperature")==0))
     return STD_VC_max_dew_point_temperature.get();
   if ((stricmp(var_lc, "tdewmin")==0)
     ||(stricmp(var_lc, "dptmin")==0)
     ||(stricmp(var_lc, "dew_point(min)")==0)
     ||(stricmp(var_lc, "dew_point_temperature(min)")==0)
     ||(stricmp(var_lc, "min_dew_point_temperature")==0))
     return STD_VC_min_dew_point_temperature.get();
    if ((stricmp(var_lc, "tdewavg")==0)                                           //050601
      ||(stricmp(var_lc, "dptavg")==0)
      ||(stricmp(var_lc, "dew_point(avg)")==0)
      ||(stricmp(var_lc, "dew_point_temperature(avg)")==0)
      ||(stricmp(var_lc, "avg_dew_point_temperature")==0))
      return STD_VC_avg_dew_point_temperature.get();
    if ((stricmp(var_lc, "rhmax")==0)
      ||(stricmp(var_lc, "relhumidmax")==0)
      ||(stricmp(var_lc, "relative_humidity(max)") ==0)
      ||(stricmp(var_lc, "max_relative_humidity")==0))
      return STD_VC_max_relative_humidity.get();
    if ((stricmp(var_lc, "rhmin")==0)
      ||(stricmp(var_lc, "relhumidmin") ==0)
      ||(stricmp(var_lc, "relative_humidity(min)")==0)
      ||(stricmp(var_lc, "min_relative_humidity")==0))
      return STD_VC_min_relative_humidity.get();
    if ((stricmp(var_lc, "rhavg")==0)
      ||(stricmp(var_lc, "relhumidavg") ==0)
      ||(stricmp(var_lc, "relative_humidity(avg)")==0)
      ||(stricmp(var_lc, "avg_relative_humidity")==0))
      return STD_VC_avg_relative_humidity.get();

   //180808 NYI huss  humidity specific


    if ((stricmp(var_lc, "srad")==0)
      ||(stricmp(var_lc, "solar_radiation")==0))
#if ((CS_VERSION >0) && (CS_VERSION <= 4))
      return STD_VC_solar_radiation_ERRONEOUS.get();
#else
      return STD_VC_solar_radiation_global.get();
#endif
    if ((stricmp(var_lc, "ws")==0)
      ||(stricmp(var_lc, "wind_speed")==0)
      ||(stricmp(var_lc, "wind_velocity")==0))
      return STD_VC_wind_speed.get();

    if ((stricmp(var_lc, "uas")==0)                                              //171022
      //||(stricmp(var_lc, "zonal")==0)
      ||(stricmp(var_lc, "zonal")==0))
      return STD_VC_UAS.get();

    if ((stricmp(var_lc, "vas")==0)                                              //171022
      //||(stricmp(var_lc, "meridional")==0)
      ||(stricmp(var_lc, "meridional")==0))
      return STD_VC_VAS.get();


    if ((stricmp(var_lc, "winddir")==0)
      ||(stricmp(var_lc, "wind_direction")==0)
      ||(stricmp(var_lc, "wind_dir")==0))
      return STD_VC_wind_direction.get();
#ifdef NYI
      return STD_VC_pan_evaporation;
      return STD_VC_pot_evapotranspiration;
      return STD_VC_act_evapotranspiration;
      return STD_VC_ref_ET_Penman_Monteith;
      return STD_VC_ref_ET_Priestly_Taylor;
      return STD_VC_ref_ET_Hargreaves;
      return STD_VC_avg_daytime_vapor_pressure_deficit;
      return STD_VC_avg_fullday_vapor_pressure_deficit;
      return STD_VC_max_vapor_pressure_deficit;
      return STD_VC_cloud_cover;
      return STD_VC_snow_fall;
      return STD_VC_snow_depth;
#endif
      return 0;                                                                  //030710
/*______*/  };
//_2002-09-06___________________________________________Identify_variable_code_/
/*070718_*/ }; // namespace UED

