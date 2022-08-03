#include "WP_wind_speed.h"
#include "corn/math/compare.hpp"
#include <math.h>
#include "corn/math/moremath.h"

//______________________________________________________________________________
float64 Wind_speed::calc_normalized(float64 wind_speed_m_ts)               const
{
   float64 normalized_WS_ts
      = CORN::is_approximately<float64>
         (reference_height_m
         ,measurement_height_wind_speed_standard_agronomic_m,0.00001)            //011009
      ? wind_speed_m_ts                                                          //011009
      : wind_speed_m_ts * (4.87 / CORN_ln(67.8 * reference_height_m - 5.42));
   return normalized_WS_ts;
}
//_2015-04-27__2002-10-09_______________________________________________________
float64 Wind_speed::normalized_m_per_timestep(CORN::Seconds time_step)                  const
{  float64 normalized_m_s = calc_normalized(get_m_s());
   return normalized_m_s / time_step;
}
//_2015-05-31___________________________________________________________________
float64 Wind_speed::get_at_height_m_per_s(float64 height)                  const
{  // From Environmental Modeling and Biophysics 2nd Edition, pages 66-71
   float64 d_coeff = 0.65; // for a crop  of plant area index of 0.6, this is not accurate!
   float64 zm_coeff = 0.1; // for a crop  of plant area index of 0.6, this is not accurate!
   float64 d = 0.65 * height; // zero plane displacement
   float64 zm = 0.1 * height; // momentum roughness parameter
   float64 von_Karman_constant = 0.4; // von Karman constant
   float64 u_star = get_m_s() * von_Karman_constant
      / log((get_reference_height_m() - d)/zm);   // friction velocity
   float64 wind_speed_m_per_s = (log((1.0 - d_coeff)/zm_coeff)/0.4) * u_star;
   return wind_speed_m_per_s;
}
//_2015-10-14BRC________________________________________________________________

