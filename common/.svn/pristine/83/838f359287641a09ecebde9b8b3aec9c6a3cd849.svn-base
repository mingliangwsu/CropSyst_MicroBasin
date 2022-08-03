#ifndef windH
#define windH

#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#ifndef constH
#  include "corn/const.h"
#endif
/*170525
#ifndef  timeH
#  include "corn/datetime/time.h"
#endif
*/
/*170525
#ifndef dateHPP
#  include "corn/datetime/date.hpp"
#endif
*/
#ifndef codesH
#  include "UED/library/codes.h"
#endif

#include "common/weather/parameter/WP_wind_speed.h"

#define SECONDS_PER_METER  1
#define DAYS_PER_METER     86400

using namespace CORN;

class Wind
{
 private: // Forcing element references
   const Wind_speed  &wind_speed;                                                //150209
 private: // constant parameters
//150427 moved to wind_speed   float64  wind_measurement_height;       // m  Usually 2 meters above surface
   float64  temperature_measurement_height;// m  Usually 2 meters above surface
 protected: // Daily calculated variables
//             The following are stored in different units, because
//             the original equations were different and they are used different
//             eventually I would like to store in a single units
   updatable_ float64 aerodynamic_resistance_of_snow_s_m;   // sec/meter
   contribute_ CORN::Quality_clad aerodynamic_resistance_quality;
 private:
   float64 calc_aerodynamic_resistance_general_form                              //011009
      (float64 wind_speed // any units
      ,float64 momentum_roughness_parameter_num
      ,float64 momentum_roughness_parameter_denom
      ,float64 heat_and_vapor_roughness_parameter_num
      ,float64 heat_and_vapor_roughness_parameter_denom
      ,float64 zero_plane_displacement_height = 0.0    // m usualy 0 meters
      ,float64 von_Karmon_constant = 0.41)                                 const;
   float64 calc_aerodynamic_resistance_of_snow  // s/m
      (float64 wind_speed_m_s
      ,float64 momentum_roughness_parameter        = 0.001  // m
      ,float64 heat_and_vapor_roughness_parameter  = 0.0002 // m
      ,float64 von_Karmon_constant                 = 0.41)                 const;
 public:
   float64 calc_aerodynamic_resistance_of_plants                                 //011009
      (float64 wind_speed_m_d // meters/day
      ,float64 plant_height_m = 0.12)                                      const;
      // meters default plant height is reference crop
 protected:
   virtual void update_aerodynamic_resistance()                   rectification_;//150209
   inline virtual void invalidate(bool absolutely) // was invalidate_date(const Date &date)  091216
      {  aerodynamic_resistance_quality.invalidate(absolutely);
      }
 public:  // accessors
   inline float64 get_aerodynamic_resistance_of_snow(Seconds time_step = SECONDS_PER_METER) const
      { return aerodynamic_resistance_of_snow_s_m / time_step; }
    // timestep/meter or def: seconds/meter

   inline float64 set_aerodynamic_resistance_of_snow_s_m(float64 aero_resist_s_m) assignation_//011009
       { return aerodynamic_resistance_of_snow_s_m = aero_resist_s_m;}

// The following are not implemented because there could be a.r. for different kinds of plants
//NYI/*______*/    inline float64 get_aerodynamic_resistance_of_plants(CORN_seconds time_step = DAYS_PER_METER) const
//NYI/*______*/    { return aerodynamic_resistance_of_plants_d_m * 86400.0 / time_step; };  // WARNING need to check if this works for SECONDS_PER_METER
   // timestep/meter or def: seconds/meter

//NYI/*______*/     inline float64 set_aerodynamic_resistance_of_plants_d_m(float64 aero_resist_d_m) { return aerodynamic_resistance_of_plants_d_m = aero_resist_d_m;};
 public: // constructors
    Wind
       (const Wind_speed &curr_wind_speed                                        //150209
       ,float64 _temperature_measurement_height = 2.0);
   inline virtual ~Wind() {}                                                     //151204
   float64 calc_normalized_wind_speed(float64 wind_speed_m_ts)             const;//011008
      // This will work for any time step                                        //011008
};
//______________________________________________________________________________
#endif

