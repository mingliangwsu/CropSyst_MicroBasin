#ifdef USE_PCH
   #include <common/weather/weather_pch.h>
#else
   #include <math.h>
   #include <corn/math/moremath.h>
   #include <common/weather/loc_param.h>
   #include <common/weather/day/ET_ref_day.h>

// Eventually will only need to include one of the following
   #include <common/weather/wthr_vp.h>
#endif
   #include <common/weather/weather.h>
//______________________________________________________________________________
Reference_ET_FAO::Reference_ET_FAO
(Weather &_weather                                                               //050802
,ET_models preferred_ET_model)   // Not currently used
:ET_common(_weather)
,weather(_weather)                                                   //041108
,enabled_model(preferred_ET_model)
,reference_canopy_resistance(canopy_resistance_constant)             //011107
{  for (int i = 0; i < FAO_ET_MODEL_COUNT; i++)
   {  ET_ref_mm[i] = 0.0;
      ET_ref_quality[i] = UED_measured;  // Just clearing, may need to be unknown but it was 0 before
   };
};
//_2003-10-09___________________________________________________________________
float64 Reference_ET_FAO::calc_atmospheric_density(float64 temperature_kelvin) const
{  float64 virtual_temperature // Kelvin
   = 1.01 * (temperature_kelvin);
   float64  atmospheric_pressure = weather.get_atmospheric_pressure_est_kPa();
   float64 atmospheric_density // kg/m3
   = 3.486 * (atmospheric_pressure / virtual_temperature);
   return atmospheric_density;
};  // check 011010
//_2001-10-08___________________________________________________________________
void Reference_ET_FAO::update()
{  for (int i = 0; i < FAO_ET_MODEL_COUNT; i++)                                  //011018
   {  ET_ref_mm[i] = 0.0;                                                        //031009
      ET_ref_quality[i] = UED_measured;  // Just clearing, may need to be unknown but it was 0 before //031009_
   };
   CORN::Quality_code max_temp_qual = weather.get_max_temperature_quality();
   CORN::Quality_code min_temp_qual = weather.get_min_temperature_quality();
   CORN::Quality_code sol_rad_qual = weather.get_solar_radiation_quality();
   CORN::Quality_code windspeed_qual = weather.get_wind_speed_quality();
   CORN::Quality_code max_rel_humid_qual = weather.get_max_relative_humidity_quality();
   CORN::Quality_code PM_quality =                                               //040511
      UED_worst_quality(max_temp_qual
     ,UED_worst_quality(min_temp_qual
     ,UED_worst_quality(sol_rad_qual
     ,UED_worst_quality(windspeed_qual,max_rel_humid_qual))));
   if (UED_is_valid(PM_quality))                                                 //040511
      PM_quality = UED_estimated_from(PM_quality);                               //040511
   // If we have not selected all models or not penman monteith model            //011018
   curr_avg_air_temperature         = weather.get_curr_avg_air_temperature();  // 'C
   curr_soil_heat_flux_density      = 0.0; //MJ/(m2 day) 0.0 when full day  (if daylight, a value of 1.0) would be used.
   curr_net_radiation               = net_radiation(false);// MJ/(m2 day) at crop surface
   curr_slope_vapor_pressure_curve  = weather.calc_slope_of_saturated_vapor_pressure(curr_avg_air_temperature); // kPa/'C
   curr_psychrometric_const         = calc_psychrometric_constant(curr_avg_air_temperature); // kPa/'C
   curr_latent_heat_vaporization    = latent_heat_vaporization(curr_avg_air_temperature); //011009
   Quality max_vpd_qual; float64 curr_avg_fullday_vapor_pressure_deficit_kPa  = weather.calc_avg_vapor_pressure_deficit(false,max_vpd_qual); //020212
	weather.set_avg_fullday_vapor_pressure_deficit_kPa(curr_avg_fullday_vapor_pressure_deficit_kPa,max_vpd_qual);  //020212
   float64 wind_speed_m_d           =   weather.get_curr_wind_speed_m_d();
   float64 wind_speed_at_standard_height_m_d = weather.normalize_wind_speed(wind_speed_m_d);
               //*011117x     Although aero resistance is only used by P.M. it is also used by limited growth calculations
   curr_aerodynamic_resistance                                                   //011008
      = weather.calc_aerodynamic_resistance_of_plants
      (wind_speed_at_standard_height_m_d
      ,0.12 // meters reference crop plant height
      );
   if (UED_is_valid(PM_quality) && ((enabled_model == ALL_ET_MODELS) || (enabled_model ==PENMAN_MONTEITH_MODEL )))
   {
      // Actual vapor pressure computed by common_et
      // (it is used also for isothermal longwave net radiation).
      // Warning psychrometric_constant is not the same as FAO (data not available) using CropSyst
      float64 vapor_pressure_plus_resistance                                     //011008
      =get_vapor_pressure_plus_resistance(reference_canopy_resistance);          //011117
      float64  atmospheric_density  // kg/m3                                     //011008
      = calc_atmospheric_density(C_to_Kelvin(curr_avg_air_temperature));
      static const float64 spec_heat_cap_moist_air = 0.001013; // MJ/(kg C)                                                                     //011009
      float64 vol_heat_cap                         = atmospheric_density * spec_heat_cap_moist_air;                                             //011009
      float64 vapor_pressure_component             = (curr_avg_fullday_vapor_pressure_deficit_kPa * vol_heat_cap) / curr_aerodynamic_resistance;//011008
      float64 radiation_component                  =  curr_slope_vapor_pressure_curve * (curr_net_radiation - curr_soil_heat_flux_density);     //011008
#ifdef ANOTHER_WAY
011008 This is another way of computing the P.M. terms
These should be functionally equivelent to the ones currently use,
but are factored a different way.

      float64 wind_speed_at_standard_height_m_s
      = weather.normalize_wind_speed(wind_speed_m_d/seconds_per_day);
      float64 denominator
      = curr_slope_vapor_pressure_curve
         + curr_psycrometric_const * (1.0 + 0.34 * wind_speed_at_standard_height_m_s);
      float64  radiation_component
      = 0.408 * slope_vapor_pressure_curve
         * (curr_net_radiation - curr_soil_heat_flux_density);
      float64 mean_saturation_vapor_pressure // kPa  (es)
      = (weather.get_sat_VP_at_max_temp() + weather.get_sat_VP_at_min_temp()) / 2.0;
      saturation_vapor_pressure_deficit = mean_saturation_vapor_pressure -
      //100421                     weather.get_curr_act_vapor_pressure();// kPa
         curr_vapor_pressure_actual.value;

      float64  vapor_pressure_component
      = psycrometric_const
      * (900.0 /C_to_Kelvin(avg_air_temperature))
        * wind_speed_at_standard_height_m_s
        * curr_saturation_vapor_pressure_deficit;
#endif
      float64 Rad_term_num = curr_slope_vapor_pressure_curve * curr_net_radiation / vapor_pressure_plus_resistance;  //011009
      float64 Rad_term = Rad_term_num / curr_latent_heat_vaporization;                                               //011009
      float64 Aero_term_num =  vapor_pressure_component / vapor_pressure_plus_resistance;                            //011009
      float64 Aero_term = Aero_term_num / curr_latent_heat_vaporization;                                             //011009
      float64 ET_ref_penman_monteith = Rad_term + Aero_term;                                                         //011009
      ET_ref_mm[FAO_PENMAN_MONTEITH_ET] = ET_ref_penman_monteith;
   } else PM_quality = UED_not_valid;
   ET_ref_quality[FAO_PENMAN_MONTEITH_ET] = PM_quality;
   float64 ET_hargreaves_unadjusted = 0.0;
   CORN::Quality_code  ET_hargreaves_unadjusted_quality = UED_not_valid;               //011018
   if (((enabled_model == ALL_ET_MODELS) || (enabled_model == FAO_HARGREAVES_ET_UNADJ))//011018
         && UED_is_valid(PM_quality))                                               //020401
   {  static const MJ_M2_day_to_mm_day = 0.408;
      ET_hargreaves_unadjusted = 0.0023 * (curr_avg_air_temperature + 17.8)
         * sqrt(weather.get_curr_max_temperature() -  weather.get_curr_min_temperature())
         * MJ_M2_day_to_mm_day * weather.Solar_irradiance::get_extraterrestrial_radiation_today(); //011009
      ET_hargreaves_unadjusted_quality = ET_ref_quality[FAO_HARGREAVES_ET_ADJ]
         = UED_estimated_from(
            UED_worst_quality(weather.get_max_temperature_quality(),weather.get_min_temperature_quality()));
   };
   ET_ref_mm[FAO_HARGREAVES_ET_UNADJ] = ET_hargreaves_unadjusted;
   ET_ref_quality[FAO_HARGREAVES_ET_UNADJ] = ET_hargreaves_unadjusted_quality;
   float64 ET_hargreaves_adjusted = 0.0;
   CORN::Quality_code  ET_hargreaves_adjusted_quality = UED_not_valid;                 //011018
   if ((enabled_model == ALL_ET_MODELS) || (enabled_model == FAO_HARGREAVES_ET_ADJ))   //011018
   {  ET_hargreaves_adjusted         = ET_hargreaves_unadjusted * weather.location.ET_slope + weather.location.ET_intercept;
      ET_hargreaves_adjusted_quality = ET_hargreaves_unadjusted_quality;
   };
   ET_ref_mm[FAO_HARGREAVES_ET_ADJ] = ET_hargreaves_adjusted;
   ET_ref_quality[FAO_HARGREAVES_ET_UNADJ] = ET_hargreaves_adjusted_quality;
};
//______________________________________________________________________________
