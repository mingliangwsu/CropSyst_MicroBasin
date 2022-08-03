#if (CS_VERSION != 4)
#error This has been moved to biometeorology\aerodynamics.h
#endif
#  include <math.h>
#  include "corn/math/moremath.h"
#  include "corn/math/compare.hpp"
#  include "common/weather/wind.h"

/*
#  Ra = (ln((zu-d+zmn)/zmd)*ln((zt-d+zhn)/zhd))/(u*k^2)
#
#  where  zu = height of wind measurements (m)
#         zt = height of temperature measurements (m)
#         d  = height of zero plane displacement (m)
#         zmn = momentum roughness parameter in the numerator(m)
#         zmd = momentum roughness parameter in the denominator(m)
#         zhd = heat and vapor roughness parameter in the numerator(m)
#         zhn = heat and vapor roughness parameter in the denominator(m)
#         k  = von Karmon constant (0.41)
#         u  = windspeed (m/ts)
*/
//______________________________________________________________________________
Wind::Wind
(const Wind_speed &_wind_speed                                                   //150209
,float64  _temperature_measurement_height)
:wind_speed                      (_wind_speed)                                   //150209
,temperature_measurement_height  (_temperature_measurement_height)
,aerodynamic_resistance_of_snow_s_m(0)
,aerodynamic_resistance_quality  (CORN::unknown_quality)
{}
//______________________________________________________________________________
float64 Wind::calc_aerodynamic_resistance_general_form
(float64 aribtrary_wind_speed // any units
,float64 momentum_roughness_parameter_num          // usually meters
,float64 momentum_roughness_parameter_denom        // usually meters
,float64 heat_and_vapor_roughness_parameter_num    // usually meters
,float64 heat_and_vapor_roughness_parameter_denom  // usually meters
,float64 zero_plane_displacement_height            // usually meters
,float64 von_Karmon_constant)                                              const
{  float64 momentum_term = CORN_ln((
         wind_speed.get_reference_height_m() //154027 wind_measurement_height
          - zero_plane_displacement_height
          + momentum_roughness_parameter_num) / momentum_roughness_parameter_denom);
   float64 heat_and_vapor_term = CORN_ln((temperature_measurement_height - zero_plane_displacement_height
          + heat_and_vapor_roughness_parameter_num)
          / heat_and_vapor_roughness_parameter_denom);
   float64 num = ( momentum_term * heat_and_vapor_term);
   float64 aero_resist = 0.0;
   if (CORN::is_approximately<float64>(wind_speed,0.0,0.00001))
   { // Need to avoid division by zero //000120
      aero_resist = 0.000001;
      aerodynamic_resistance_quality.assume_code(CORN::interpolated_quality); // was UED_estimated;
   } else
   {  float64 denom = (aribtrary_wind_speed * CORN_sqr(von_Karmon_constant));
      aero_resist =  num / denom;
   }
   return aero_resist; // the returned units will vary
}
//_2001-10-09___________________________________________________________________
float64 Wind::calc_aerodynamic_resistance_of_plants
(float64 wind_speed_m_d // meters/day
,float64 plant_height_m )                                                  const
{  float64 zero_plane_displacement = 0.6666666 * plant_height_m;
   float64 momentum_rough_param = 0.123 * plant_height_m;// (Zom)
   float64 heat_vapor_rough_param = 0.1 * momentum_rough_param; // (Zoh)
   float64 aero_resist_plant = calc_aerodynamic_resistance_general_form(wind_speed_m_d,0.0,momentum_rough_param,0.0,heat_vapor_rough_param,zero_plane_displacement);
   return aero_resist_plant;
}
//_2001-10-09___________________________________________________________________
/*
#  wind_roughness = (ln((zu-d+zm)/zm)*ln((zt-d+zh)/zh))/(u*k^2)
#
#  where  zu = height of wind measurements (2 m)
#         zt = height of temperature measurements (2 m)
#         d  = height of zero plane displacement (0 m)
#         zm = momentum roughness parameter (0.001 m)
#         zh = heat and vapor roughness parameter (0.0002 m)
#         k  = von Karmon constant (0.41)
#         u  = windspeed (m/s)
*/
float64 Wind::calc_aerodynamic_resistance_of_snow
(float64 wind_speed_m_s
,float64 momentum_roughness_parameter
,float64 heat_and_vapor_roughness_parameter
,float64 von_Karmon_constant)                                              const
{  static const float64 zero_plane_displacement_for_snow_pack           = 0.0;   // m
   static const float64 momentum_roughness_parameter_for_snow_pack      = 0.001; // m
   static const float64 heat_and_vapor_roughness_parameter_for_snow_pack= 0.0002;// m
   if (CORN::is_approximately<float64>(wind_speed_m_s ,0,0.00001))
   { // Need to avoid division by zero
      wind_speed_m_s = 3.0;
      aerodynamic_resistance_quality.assume_code(CORN::estimated_quality);
   }
   float64 aero_resist_snow  // s/m
   =  calc_aerodynamic_resistance_general_form
      (wind_speed_m_s
      ,momentum_roughness_parameter_for_snow_pack,momentum_roughness_parameter_for_snow_pack
      ,heat_and_vapor_roughness_parameter_for_snow_pack,heat_and_vapor_roughness_parameter_for_snow_pack
      ,zero_plane_displacement_for_snow_pack);
   aero_resist_snow = CORN::must_be_greater_or_equal_to<float64>(aero_resist_snow,3.0);     //170104
   return aero_resist_snow;
}
//_2001-10-09__2000-01-20_______________________________________________________
void Wind::update_aerodynamic_resistance()                                                                 rectification_
{  aerodynamic_resistance_quality.assume(wind_speed); // must be done before calc //000210_
   aerodynamic_resistance_of_snow_s_m = calc_aerodynamic_resistance_of_snow(wind_speed.get_m_s());
}
//______________________________________________________________________________
float64 Wind::calc_normalized_wind_speed(float64 wind_speed_m_ts)          const
{  // This will work for any time step
   return wind_speed.calc_normalized(wind_speed_m_ts);                           //150427
/*150427
   float64 wind_measurement_height = wind_speed.get_reference_height_m();        //154027
   float64 normalized_WS_ts
      = is_approximately(wind_measurement_height,2.0,0.00001)                    //011009
      ? wind_speed_m_ts                                                          //011009
      : wind_speed_m_ts * (4.87 / CORN_ln(67.8 * wind_measurement_height - 5.42));
   return normalized_WS_ts;
*/
}
//______________________________________________________________________________

