#include "corn/primitive.h"
#include <math.h>
#include "corn/math/moremath.h"

//______________________________________________________________________________
float64 friction_velocity
(float64 momentum_roughness_param   // m
,float64 zero_plane_displacement    // m
,float64 windspeed_m_s              // m/s
,float64 screening_height           // m
)
{
   #define von_karman_const   0.4
   float64 friction_velocity = (von_karman_const* windspeed_m_s)
              / CORN_ln ( (screening_height - zero_plane_displacement) / momentum_roughness_param);
   return friction_velocity;
}
//_1993-01-30__________________________________________________________friction_velocity_/
