#ifndef std_codesH
#define std_codesH
#include "UED/library/UED_types.h"
#include "UED/library/varcodes.h"
#include <string>
namespace UED {                                                                  //070718

// extern CORN::Units_clad UED_STD_UC_meters_per_sec;
// extern CORN::Units_clad UED_STD_UC_depth_meters;

// extern UED_units_definition UED_STD_UD_degrees_C;
// extern UED_units_definition UED_STD_UD_mm_water_depth;
// extern UED_units_definition UED_STD_UD_m_water_depth;
// extern UED_units_definition UED_STD_UD_solar_radiation_MJ_m2;
// extern UED_units_definition UED_STD_UD_percent;
// extern UED_units_definition UED_STD_UD_meters_per_sec;

extern Variable_code_clad STD_VC_date;  // Special for date dataset columns
// extern Variable_code_clad STD_VC_year;  // Special for date dataset columns
// extern Variable_code_clad STD_VC_DOY;  // Special for date dataset columns

extern Variable_code_clad STD_VC_precipitation;
extern Variable_code_clad STD_VC_max_temperature;
extern Variable_code_clad STD_VC_min_temperature;
extern Variable_code_clad STD_VC_avg_temperature;
extern Variable_code_clad STD_VC_obs_temperature;                               //020427
               // temperature observed at time step  (instantaneous)
extern Variable_code_clad STD_VC_max_dew_point_temperature;
extern Variable_code_clad STD_VC_min_dew_point_temperature;
extern Variable_code_clad STD_VC_avg_dew_point_temperature;
// We need an observed/instantaneous dewpoint  temperature                       //050515

//NYI /*050516*/ extern Variable_code_clad STD_VC_avg_dew_point_temperature;
extern Variable_code_clad STD_VC_max_relative_humidity;
extern Variable_code_clad STD_VC_min_relative_humidity;
extern Variable_code_clad STD_VC_avg_relative_humidity;                          //050419

extern Variable_code_clad STD_VC_humidity_specific;                              //050419

extern Variable_code_clad STD_VC_solar_radiation_global;
   // should rename this to irradiance_solar_global or insolation
extern Variable_code_clad STD_VC_isothermal_longwave_net_radiation;             //070203
extern Variable_code_clad STD_VC_net_radiation;                                 //070203
#if (CS_VERSION < 6)
extern Variable_code_clad STD_VC_solar_radiation_ERRONEOUS;   // rename this to irradiance_solar_global  or insolation
extern Variable_code_clad STD_VC_isothermal_longwave_net_radiation_ERRONEOUS;   //070203
extern Variable_code_clad STD_VC_net_radiation_ERRONEOUS;                       //070203
#endif
//050515             We need an observed/instantaneous relative humidity
extern Variable_code_clad STD_VC_solar_radiation_avg_hourly;   // rename this to irradiance_solar_global  //100222
extern Variable_code_clad STD_VC_sunshine_hours;   // rename this to              //100222
extern Variable_code_clad STD_VC_wind_speed;
 // Note: may need to distinguish wind speed  (per day) as the daily run  (total for time step
 // and average wind speed during timestep

// May need to add peak/max wind gust during the time step

extern Variable_code_clad STD_VC_wind_direction;                                 //050419
extern Variable_code_clad STD_VC_UAS; // zonal                                   //171022
extern Variable_code_clad STD_VC_VAS; // meridional                              //171022
extern Variable_code_clad STD_VC_pan_evaporation;
extern Variable_code_clad STD_VC_pot_evapotranspiration;
extern Variable_code_clad STD_VC_act_evapotranspiration;
extern Variable_code_clad STD_VC_ref_ET_Penman_Monteith;                        //000731
extern Variable_code_clad STD_VC_ref_ET_Priestly_Taylor;                        //000731
extern Variable_code_clad STD_VC_ref_ET_Hargreaves;                             //000731
extern Variable_code_clad STD_VC_ref_ET_ASCE_EWRI_short_crop;                   //091005
extern Variable_code_clad STD_VC_ref_ET_ASCE_EWRI_tall_crop;                    //091005

extern Variable_code_clad STD_VC_vapor_pressure_deficit;                        //101212

extern Variable_code_clad STD_VC_avg_daytime_vapor_pressure_deficit;
extern Variable_code_clad STD_VC_avg_fullday_vapor_pressure_deficit;            //011009
extern Variable_code_clad STD_VC_max_vapor_pressure_deficit;
extern Variable_code_clad STD_VC_vapor_pressure_actual;                         //101205
extern Variable_code_clad STD_VC_atmospheric_pressure;                          //101205
extern Variable_code_clad STD_VC_cloud_cover;
extern Variable_code_clad STD_VC_snow_fall;                                     //020427
extern Variable_code_clad STD_VC_snow_depth;                                    //020427
           // Not sure if water depth or snow cover (I think conver)

// Note, some of these are daily (because of the valid ranges check constants are for day

extern bool Compose_generalized_standard_description                             //990510
          (CORN::Units_code units_code
          ,std::string &description
          ,std::string &abbreviation);
extern UED_variable_code Identify_standard_variable_code(const char *variable_label);     //020906
//140615 extern char *Variable_abbreviation(UED_variable_code var_code,char *label_buffer);//020907
extern const std::string &standard_variable_abbreviation(UED_variable_code var_code);//140615

//D         Create a description and abbreviation for the given code.
//d         Returns true if the desc and abbr could be determined, false if not.

//struct UED_generalized_measure_definition
//{
// char *measure;      // I.e.  length, depth, temperature
// char *abbreviation; // Will be combined with units system abbreviation I.e. m for meters
//}

}; // namespace UED  070718
#endif
//std_codes

