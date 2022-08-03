#if (CROPSYST_VERSION == 3)
#     include "cs_ET.h"
#     include "corn/bsysemod/weather/vp_wthr.h"
#     include <math.h>
#else
#     include <math.h>
#     include "corn/math/moremath.h"
#     include "cs_ET.h"
#     include "common/weather/weather_provider.h"
#     include "common/weather/database/weather_database.h"
#endif
#include "common/biometeorology/ET_reference_Priestley_Taylor.h"

#include "corn/math/compare.hpp"
#define reference_plant_height  0.12
//______________________________________________________________________________
CropSyst_ET::CropSyst_ET
(const Weather_provider &weather_provider_                                       //150122
,const Geocoordinate &geocoordinate_                                             //151118
,float64              screening_height_                                          //151022
,const float64       &day_length_hours_today_                                    //150627
//NYN,Aerodynamics &_aerodynamics                                                //150601
,ET_Model             preferred_ET_model                                         //011109
,const CS::Priestley_Taylor_Parameters &P_T_parameters_)                         //170808
:ET_Reference_FAO       (
   weather_provider_
   ,geocoordinate_                                                               //151118
   ,day_length_hours_today_
   ,preferred_ET_model)                                                          //150601_021016
,weather_provider(weather_provider_)                                             //151118
,screening_height(screening_height_)                                             //151022
,P_T_parameters         (P_T_parameters_)                                        //170808
#if (CO2_RESPONSE_VERSION!=4)
,daily_ratio_elevated_to_baseline_ppm_CO2_ET(1.0)
#endif
,wind_speed(weather_provider_.wind_speed)                                        //151022
,vapor_pressure_deficit_fullday_avg(weather_provider_.vapor_pressure_deficit_fullday_avg)     //151022
{}
//_constructor__________________________________________________________________
float64 CropSyst_ET::other_atmospheric_transmissivity(float64 pot_solar_rad)
{  return CORN::must_be_less_or_equal_to<float64>
      (solar_radiation.get_MJ_m2()/ pot_solar_rad,0.78);                         //151022
}   // m (short grass)
//_other_atmospheric_transmissivity_________________________________1999-03-29_/
float64 CropSyst_ET::calc_Priestley_Taylor_pot_ref_et_mm
(float64 slope_of_sat_vap_press
,float64 psychrometric
,float64 latent_heat
,float64 net_rad         // day time
,float64 soil_heat_flux  //{ MJ/m2/day }
,float64 fullday_VPD) const                                                      //180822_020212
{  // The PT constant adjusted for VPD was removed in 1998 and restored in 2002.
   float64 PT_const_adjusted  // Adjust PT constant for aridity                       //020212
   /*170808
      = (fullday_VPD <= 1.0)  // only apply correction when fullday_VPD > 1.0
      ? PT_const_param
      : 1.0 + 0.5 * fullday_VPD;                                                 //170804
//170804      : 1.0 + (PT_const_param - 1.0) * fullday_VPD;
   */
      = P_T_parameters.provide_P_T_constant_adjusted();                          //170808
   float64 numerator
      = PT_const_adjusted * (slope_of_sat_vap_press * (net_rad-soil_heat_flux)); //080908
   float64 denominator = (psychrometric + slope_of_sat_vap_press);               //080908
   float64 potential_mm = numerator / denominator;                               //020212_980311
#ifdef CO2_CHANGE
#if (CO2_RESPONSE_VERSION==4)
           potential_mm *= daily_ratio_elevated_to_baseline_ppm_CO2_ET;
#  endif
#endif
//in V4 Transpiration adjustment is handled by CO2_response
               // when CO2change is not simulated daily_ratio_elevated_to_baseline_ppm_CO2_ET is 1.0
   float64 ET_ref_pot = std::max<float64>(0.05, potential_mm/latent_heat);
   return ET_ref_pot;
}
//_calc_Priestley_Taylor_pot_ref_et_mm______________________________1998-03-10_/
float64 CropSyst_ET::aero_dynamic_resistance_vapor_exchange
(float64 height_m) const                                                         //180822
//I.e. plant height
{  // Note this is a special form for the PT calculation
   // Do not use this equation in future code,
   // instead use calc_aerodynamic_resistance_general_form in wind.h //011108_
   float64 wind_speed_md = wind_speed.get_m_d();                                 //151022
   if (CORN::is_approximately<float64>(wind_speed_md,0.0,0.000001))              //151208
      wind_speed_md = 0.01; // avoid div 0 error                                 //151208
   return
      ( CORN_ln((screening_height - 0.744 * height_m) / (0.026 * height_m))
       *CORN_ln((screening_height - 0.640 * height_m) / (0.130 * height_m)))
      / (0.16 * wind_speed_md);                                                  //990216
}
//_aero_dynamic_resistance_vapor_exchange______________________________________/
float64 CropSyst_ET::calc_pot_ref_evapotranspiration_mm()
mutation_ //180822
{  aero_dynamic_resistance_vapor_exchange(reference_plant_height);            //980310
//980801?      WARNING daily_ratio_elevated_to_350ppm_CO2_ET is not used in PT PET as in PM PET
//             I think this may be correct, but check with Claudio
   CORN::Quality_clad  VPDavg_fullday_qual;                                      //081106
   float64 ET_ref_Priestley_Taylor_mm                                            //180404
      = calc_Priestley_Taylor_pot_ref_et_mm(
          vapor_pressure_saturation_slope.get_kPa_per_C()                        //140507
         ,psychrometric_constant.get_kPa_per_C()                                 //140512
         ,latent_heat_vaporization.get_MJ_per_kg()                               //140512
         ,curr_net_radiation                                                     //980310
         ,curr_soil_heat_flux_density                                            //980310
         ,vapor_pressure_deficit_fullday_avg.get_kPa());                         //151022
   const CORN::Quality &min_temp_qual = air_temperature_min;                     //151022
   const CORN::Quality &sol_rad_qual  = solar_radiation;                         //151022
   CORN::Quality_code ET_Priestley_Taylor_quality_code =                         //150210
    quality_estimated_from(worst_quality
      (min_temp_qual.get_quality_code(),sol_rad_qual.get_quality_code()) );      //011018
      // look for the best ET quality
   ET_ref[ET_Priestley_Taylor].set_mm                                            //180404
      (ET_ref_Priestley_Taylor_mm,ET_Priestley_Taylor_quality_code);             //180404
   ET_model_selected =
      quality_is_same_or_better_than
         (ET_ref[ET_FAO_56_Penman_Monteith_CropSyst].get_quality_code()          //180404
         ,ET_Priestley_Taylor_quality_code)                                      //150122_040607
      ? ET_FAO_56_Penman_Monteith_CropSyst
      : ET_Priestley_Taylor;
   float64 reference_pet_mm = ET_ref[ET_model_selected].get_mm();                //180404
   set_mm(reference_pet_mm,ET_ref[ET_model_selected]);                           //180404
   return reference_pet_mm;                                                      //010910
}
//_calc_pot_ref_evapotranspiration_mm_____________________________________1998_/
//180822 void
const CORN::Quality &
CropSyst_ET::update() rectification_
{ // Update annual CO2 conc is done on change on new year.
   ET_Reference_FAO::update();                                                   //011016
   float64 best_ET_mm = calc_pot_ref_evapotranspiration_mm();                    //031009
   float64 desired_ET_mm = ET_ref[enabled_model].get_mm();                       //180404
   bool ET_quality_valid = ET_ref[enabled_model].is_valid();                     //180404
   float64 selected_ET_mm = ET_quality_valid ? desired_ET_mm : best_ET_mm;       //031009
   ET_model_selected = ET_quality_valid ? (ET_Model)enabled_model :              //040919
       (ET_Model)ET_model_selected;
   set_mm(selected_ET_mm,ET_ref[ET_model_selected]);                             //180404
   return ET_ref[ET_model_selected];                                             //180822
}
//______________________________________________________________________________

