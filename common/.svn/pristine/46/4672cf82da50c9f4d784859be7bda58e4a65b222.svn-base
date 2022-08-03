#include "common/weather/validator.h"
#include "UED/library/std_codes.h"
#include "UED/library/varrec.h"
#include "UED/library/variable_format.h"
#include "corn/measure/units.h"
#include "corn/string/strconv.h"
#include "corn/math/compare.hpp"

#define MAX_VALIDATED_VARIABLES 27

#define TIME_UNITS_ORDER_COUNT   18
//______________________________________________________________________________
CORN::Units_code time_units_order[TIME_UNITS_ORDER_COUNT][2] =
{{UT_millisecond  ,UT_millisecond   }
,{UM_second       ,UM_second        }
,{UT_0_seconds    ,UT_60_seconds    }
,{UM_minute       ,UM_minute        }
,{UT_0_minutes    ,UT_60_minutes    }
,{UM_hour         ,UM_hour          }
,{UT_0_hours      ,UT_24_hours      }
,{UM_day          ,UM_day           }
,{UT_week      ,UT_week       }
,{UT_fortnight ,UT_fortnight  }
,{UT_month     ,UT_month      }
,{UT_quarter   ,UT_quarter    }
,{UT_trimester ,UT_trimester  }
,{UT_biannum   ,UT_biannum    }
,{UM_year      ,        }
,{UT_decade    ,        }
,{UT_century   ,        }
,{UT_millenium ,        }
};
//______________________________________________________________________________
struct Validated_variable
{  UED::Variable_format_0 *variable_definition;   // Currently using format because it has
   CORN::Units_code       intended_timestep;                // This it the time step the variable format max/min range constants have been scaled for
   bool                   applies_also_to_shorter_timestep; // true if the range constants also apply to shorter timestep (than the intended time stamp)
   bool                   applies_also_to_longer_timestep;  // true if the range constants also apply to longer timestep (than the intended time stamp)
   bool                   simple_ratio_timestep_conversion;
   // If the intended timestep does not match the time step of the value to validate,
   // And either applies_also is false,
   // can the range values be adjusted with a simple ratio.
   // For example the max/min daily precipitation also applies to
   // shorter intervals (because there may be a single event with in 1 hour, for example,
   // comprising the entire dialy value
   // but for time steps longer than one day we need to accomodate
   // multiple days of maximum precipitation.
}
//______________________________________________________________________________
validated_variable[MAX_VALIDATED_VARIABLES] =
{ {&UED::STD_VD_precipitation                       ,UT_day,true ,false ,true}
, {&UED::STD_VD_avg_temperature                      ,UT_day,true ,true ,false}
, {&UED::STD_VD_obs_temperature                      ,UT_day,true ,true ,false}
, {&UED::STD_VD_max_temperature                      ,UT_day,true ,true ,false}
, {&UED::STD_VD_min_temperature                      ,UT_day,true ,true ,false}
, {&UED::STD_VD_max_dew_point_temperature            ,UT_day,true ,true ,false}
, {&UED::STD_VD_min_dew_point_temperature            ,UT_day,true ,true ,false}
, {&UED::STD_VD_avg_dew_point_temperature            ,UT_day,true ,true ,false}
, {&UED::STD_VD_max_relative_humidity                ,UT_day,true ,true ,false}
, {&UED::STD_VD_min_relative_humidity                ,UT_day,true ,true ,false}
, {&UED::STD_VD_avg_relative_humidity                ,UT_day,true ,true ,false}
//170901#if ((CS_VERSION >0) && (CS_VERSION <= 4))
///*171109 obsolete
//#if ((CS_VERSION >0) && (CS_VERSION < 6))
//, {&UED::STD_VD_solar_radiation_deprecate                      ,UT_day,false,false,true }
//#else
//*/
, {&UED::STD_VD_solar_radiation_global                ,UT_day,false,false,true }
//#endif

, {&UED::STD_VD_solar_radiation_ERRONEOUS            ,UT_day,false,false,true }

, {&UED::STD_VD_wind_speed                           ,UT_day,false,false,true }
, {&UED::STD_VD_wind_direction                       ,UT_day,false,false,true }
, {&UED::STD_VD_pan_evaporation                      ,UT_day,true ,false,true }
, {&UED::STD_VD_pot_evapotranspiration               ,UT_day,true ,false,true }
, {&UED::STD_VD_act_evapotranspiration               ,UT_day,true ,false,true }
, {&UED::STD_VD_ref_ET_Penman_Monteith               ,UT_day,true ,false,true }
, {&UED::STD_VD_ref_ET_Priestly_Taylor               ,UT_day,true ,false,true }
, {&UED::STD_VD_ref_ET_Hargreaves                     ,UT_day,true ,false,true }
, {&UED::STD_VD_avg_daytime_vapor_pressure_deficit   ,UT_day,false,false,false}
, {&UED::STD_VD_avg_fullday_vapor_pressure_deficit   ,UT_day,false,false,false}  // Not sure how this scales, so may be true
, {&UED::STD_VD_max_vapor_pressure_deficit           ,UT_day,false,false,false}  // I think this applies daily (that is only how I've seen it, need to check units
, {&UED::STD_VD_cloud_cover                          ,UT_day,true ,true ,false} // percentage/fraction (I am pretty sure  applies can be applied any time during the day or the daily average
, {&UED::STD_VD_snow_fall                            ,UT_day,true, false, true} //
, {&UED::STD_VD_snow_depth                           ,UT_day,true ,true ,false} // this is the depth at any given time.
// template , {UED::STD_VD_xxxx                     ,UT_day,applies_also_to_shorter_timestep,applies_also_to_longer_timestep,simple_ratio_timestep_conversion}
};
//______________________________________________________________________________
Weather_validator::Weather_validator()
: convertor()
, geolocated_solar_irradiance(0)
{}
//______________________________________________________________________________
int8 Weather_validator::compare_timestep_units
(CORN::Units_code timestep1,CORN::Units_code timestep2)                    const
{  // Return negative value if time_step1 < timestep2
   // 0  if they are the same
   // and positive value if time_step1 > timestep2
   int timestep1_index = 0;
   int timestep2_index = 0;
   for (int i = 0; i < TIME_UNITS_ORDER_COUNT; i++)
   {
      if ((timestep1 >= time_units_order[i][0]) && (timestep1 <= time_units_order[i][1]))
         timestep1_index = i;
      if ((timestep2 >= time_units_order[i][0]) && (timestep2 <= time_units_order[i][1]))
         timestep2_index = i;
   }
   return timestep1_index - timestep2_index;
}
//______________________________________________________________________________
void Weather_validator::set_geolocation(Geolocation *_geolocation)
{
   if (!geolocated_solar_irradiance && _geolocation)
      geolocated_solar_irradiance = new
         CS::Solar_irradiance_extraterrestrial_daily                             //150909
         (*_geolocation,date_unused);
}
//______________________________________________________________________________
Validated_variable
*Weather_validator::identify_variable_definition(UED::Variable_code variable) const
{  Validated_variable
   *identified = 0;
   for (int i = 0; i < MAX_VALIDATED_VARIABLES; i++)
   {  UED::Variable_format_0 *variable_definition = validated_variable[i].variable_definition;
      if (variable_definition->code_clad.get() == variable)
         //identified = variable_definition;
         identified = &(validated_variable[i]);
   }
   return identified;
}
//______________________________________________________________________________
float32 Weather_validator::validate_string
(CORN::DOY              doy
, const std::string    &value_string // Value represented as a string
, UED_variable_code     variable
, CORN::Units_code      units
, CORN::Units_code      timestep
, CORN::Quality_code file_quality   // This is the general expected quality of data in the file (I.e. is the entire file measured/generated etc..
, CORN::Quality_code column_quality // This is the general expected quality of data in the column (I.e. the file may be mostly measured but there might be an estimated column.
, CORN::Quality_cowl &validate_quality // return
, std::string        &quality_description)                                 const
{  float32 value = 99999.0;
   if (  (value_string.compare("999") ==0 )
      || (value_string.compare("9999") ==0 )
      || (value_string.compare("99999") ==0 )
      || (value_string.compare("999999") ==0 )
      || (value_string.find("MISSING") != std::string::npos)   || (value_string.find("missing") != std::string::npos) || (value_string.find("Missing") != std::string::npos)
      || (value_string.find("#VALUE!") != std::string::npos )  // probably only from Excel so probably always uppercase || (value_string.find("#value!") != CORN_npos )
      )
   {  Validated_variable *valid_var = identify_variable_definition(variable);
      if (valid_var)
         quality_description.append(valid_var->variable_definition->description);
      quality_description.append(" missing indicator found:");
      quality_description.append(value_string);
      validate_quality.assume_code(CORN::missing_quality);
      value = 99999;
   } else
   {  value = atof(value_string.c_str());
      value = validate_float32(doy,value,variable,units,timestep,file_quality,column_quality,validate_quality,quality_description);
   }
   return value;
}
//______________________________________________________________________________
float32 Weather_validator::validate_float32
( CORN::DOY          doy
, float32            value
, UED_variable_code  variable
, CORN::Units_code   units       // of the value
, CORN::Units_code   timestep    // of the value
, CORN::Quality_code  file_quality   // This is the general expected quality of data in the file (I.e. is the entire file measured/generated etc..
, CORN::Quality_code  column_quality // This is the general expected quality of data in the column (I.e. the file may be mostly measured but there might be an estimated column.
, CORN::Quality_cowl &validate_quality // return quality buffer (Note that the caller may
, std::string        &quality_description)                                 const
{  bool time_step_comparison;
   Validated_variable *identified_variable = identify_variable_definition(variable);
   if (!identified_variable)
      return  value;
   if (!identified_variable->variable_definition)
      return value;
   UED::Variable_format_0 &variable_definition = *(identified_variable->variable_definition);
         float32 adj_min_warn =  variable_definition.min_warning;
         float32 adj_max_warn =  variable_definition.max_warning;
         float32 adj_min_err  =  variable_definition.min_error;
         float32 adj_max_err  =  variable_definition.max_error;
         if (units == UC_watt_second_per_m2) // convert to MJ/m2
            value = (float32)value/1000000.0 * 86400.0;
         if (units == UC_watt_hour_per_m2) // convert to MJ/m2
            value = (float32)value/1000000.0 *  3600.0 *10.0;
            // Not sure why I am needed to multiply by 100.
         if (geolocated_solar_irradiance//150909 _MJ_m2
            //150909 may need to reimplement geocoord check &&geolocated_solar_irradiance_MJ_m2->has_valid_geocoordinates()
            #if ((CS_VERSION >0) && (CS_VERSION <= 4))
            && (variable == UED::STD_VC_solar_radiation.get())
            #else
            && (variable == UED::STD_VD_solar_radiation_global.get_key_nat32())
            #endif
            )
         {  // For solar radiation we can limit the maximum to the
            // potential extra terrestrial radiation  (about 77%)
//            if (!geolocated_solar_irradiance_MJ_m2)  // allocate as needed
//                geolocated_solar_irradiance_MJ_m2 = new Geolocated_solar_irradiance(geolocation);
            float32 extraterrestrial_irradiance_doy =
               (float32)geolocated_solar_irradiance->get_MJ_per_m2_day(doy);     //150909
            adj_max_warn = extraterrestrial_irradiance_doy * extraterrestrial_to_max_solar_irradiance_factor;
            adj_max_err =  extraterrestrial_irradiance_doy * 0.85;
            // the extra terrestrial solar irradiance is the absolute maximum
            // although solar irradiance should probably never go over 80% of
         }
         if (units !=  variable_definition.preferred_units_clad.get())
         {  // adjust the
            float32 adj_units_min_warn =  adj_min_warn;
            float32 adj_units_max_warn =  adj_max_warn;
            float32 adj_units_min_err  =  adj_min_err;
            float32 adj_units_max_err  =  adj_max_err;
            CORN::Units_code range_units = variable_definition.preferred_units_clad.get();
            if (!convertor.convert(adj_min_warn ,range_units,adj_units_min_warn,units))
               { validate_quality.assume_code(CORN::unknown_quality); goto cannot_validate_check; }
            if (!convertor.convert(adj_max_warn ,range_units,adj_units_max_warn,units)) { validate_quality.assume_code(CORN::unknown_quality); goto cannot_validate_check; }
            if (!convertor.convert(adj_min_err  ,range_units,adj_units_min_err,units))  { validate_quality.assume_code(CORN::unknown_quality); goto cannot_validate_check; }
            if (!convertor.convert(adj_max_err  ,range_units,adj_units_max_err,units))  { validate_quality.assume_code(CORN::unknown_quality); goto cannot_validate_check; }
            adj_min_warn = adj_units_min_warn ;
            adj_max_warn = adj_units_max_warn ;
            adj_min_err = adj_units_min_err  ;
            adj_max_err = adj_units_max_err  ;
         }
         time_step_comparison = compare_timestep_units(timestep,identified_variable->intended_timestep);
         if (time_step_comparison != 0)
         {  // May need do adjust for time step
            bool adjust_for_timestep = false;
            if (time_step_comparison < 0)
            {  if (identified_variable->applies_also_to_shorter_timestep) adjust_for_timestep = false;
               else                                                        adjust_for_timestep = identified_variable->simple_ratio_timestep_conversion;
            }
            if (time_step_comparison > 0)
            {  if (identified_variable->applies_also_to_longer_timestep) adjust_for_timestep = false;
               else                                                        adjust_for_timestep = identified_variable->simple_ratio_timestep_conversion;
            }
//            if ((timestep != validated_variable[i].intended_timestep) &&
//                (validated_variable[i].simple_ratio_timestep_conversion))
            if (adjust_for_timestep)
            {  float32 adj_TS_min_warn =  adj_min_warn;
               float32 adj_TS_max_warn =  adj_max_warn;
               float32 adj_TS_min_err  =  adj_min_err;
               float32 adj_TS_max_err  =  adj_max_err;
               // Here we set up units for UED conversion
               // We only convert the timestep part so the
               // numerator units are not specified
               // (Otherwise is will mess up the conversion)

               CORN::Units_code per_act_timestep = U_a_per_b(U_units_not_specified,timestep);
               CORN::Units_code per_intended_timestep = U_a_per_b(U_units_not_specified,identified_variable->intended_timestep);
               if (!convertor.convert(adj_min_warn,per_intended_timestep,adj_TS_min_warn,per_act_timestep)) {  validate_quality.assume_code(CORN::unknown_quality); goto cannot_validate_check; }
               if (!convertor.convert(adj_max_warn,per_intended_timestep,adj_TS_max_warn,per_act_timestep)) {  validate_quality.assume_code(CORN::unknown_quality); goto cannot_validate_check; }
               if (!convertor.convert(adj_min_err,per_intended_timestep,adj_TS_min_err,per_act_timestep))   {  validate_quality.assume_code(CORN::unknown_quality); goto cannot_validate_check; }
               if (!convertor.convert(adj_max_err,per_intended_timestep,adj_TS_max_err,per_act_timestep))   {  validate_quality.assume_code(CORN::unknown_quality); goto cannot_validate_check; }
               adj_min_warn = adj_TS_min_warn ;
               adj_max_warn = adj_TS_max_warn ;
               adj_min_err = adj_TS_min_err  ;
               adj_max_err = adj_TS_max_err  ;
            }
         }
         if (value < adj_min_warn) validate_quality.assume_code(CORN::out_of_range_low_warning_quality);
         if (value > adj_max_warn) validate_quality.assume_code(CORN::out_of_range_high_warning_quality);
         if (value < adj_min_err)  validate_quality.assume_code(CORN::out_of_range_low_error_quality);
         if (value > adj_max_err)  validate_quality.assume_code(CORN::out_of_range_high_error_quality);

         // we could probably check relative humidity
         // if it is rain then bump up minimum to close to 100%
         // (and dew point)
//091027      }
//091027   }
   if ((variable == UED::STD_VC_max_temperature           .code)
     ||(variable == UED::STD_VC_min_temperature           .code)
     ||(variable == UED::STD_VC_avg_temperature           .code)
     ||(variable == UED::STD_VC_obs_temperature           .code)
     ||(variable == UED::STD_VC_max_dew_point_temperature .code)
     ||(variable == UED::STD_VC_min_dew_point_temperature .code)
     ||(variable == UED::STD_VC_avg_dew_point_temperature .code)
     ||(variable == UED::STD_VC_max_relative_humidity     .code)
     ||(variable == UED::STD_VC_min_relative_humidity     .code)
     ||(variable == UED::STD_VC_wind_speed                .code)
     ||(variable == UED::STD_VC_solar_radiation_avg_hourly.code)
     ||(variable == UED::STD_VC_sunshine_hours            .code)
     ||(variable == UED::STD_VC_ref_ET_Penman_Monteith    .code)                            //180307
      )
      {  if (CORN::is_approximately<float32>(value,0.0,0.0000001))
            validate_quality.assume_code(CORN::missing_quality);
      }

/* Now use adjusted max/mins
   CORN::Quality_code validated_quality = UED_unknown_quality;
   for (int i = 0; i < MAX_VALIDATED_VARIABLES; i++)
   {
      UED_variable_format_0 &variable_definition = *(validated_variable[i].variable_definition);
      if (variable_definition.code.get() == variable)
      {
         float32 units_adj_value = value;
         if (units !=  variable_definition.preferred_units_code.get())
         {
            if (!convertor.convert(value,units,units_adj_value,variable_definition.preferred_units_code.get()))
               goto cannot_validate_check;
         }

         float32 adj_value = units_adj_value;
         if (timestep != validated_variable[i].intended_timestep)
         {
            // Here we set up units for UED conversion
            // We only convert the timestep part so the
            // numerator units are not specified
            // (Otherwise is will mess up the conversion)
            Units_code per_act_timestep = U_a_per_b(U_units_not_specified,timestep);
            Units_code per_intended_timestep = U_a_per_b(U_units_not_specified,validated_variable[i].intended_timestep);
            if (!convertor.convert(units_adj_value,per_act_timestep,adj_value,per_intended_timestep))
               goto cannot_validate_check;
         }

         if (adj_value < variable_definition.min_warning) validated_quality = UED_out_of_range_low_warning;
         if (adj_value > variable_definition.max_warning) validated_quality = UED_out_of_range_high_warning;
         if (adj_value < variable_definition.min_error)   validated_quality = UED_out_of_range_low_error;
         if (adj_value > variable_definition.max_error)   validated_quality = UED_out_of_range_high_error;


         if (variable == UED::STD_VC_solar_radiation.get())
         {  // For solar radiation we can limit the maximum to the
            // potential extra terrestrial radiation


         }

         // we could probably check relative humidity
         // if it is rain then bump up minimum to close to 100%
         // (and dew point)


      }
   }
*/
cannot_validate_check:
// NYI could provide common missing values table

   if (!validate_quality.is_valid())
   {  quality_description.append(variable_definition.description);
      quality_description.append(" ");
      quality_description.append(validate_quality.get_description());
      quality_description.append(" (");
      quality_description.append(CORN::float32_to_cstr( value, 5));
      quality_description.append(" )");
   }
   if (validate_quality.get_quality_code() == CORN::unknown_quality)
   {  // We were unable to check the quality of the value
      // Assume it is the same quality as the file or
      if (file_quality != CORN::unknown_quality)
         validate_quality.assume_code(file_quality); // = file_quality
      if (column_quality != CORN::unknown_quality)
         validate_quality.assume_code(column_quality);  // = column_quality;
   }
   return value;
}
//______________________________________________________________________________

