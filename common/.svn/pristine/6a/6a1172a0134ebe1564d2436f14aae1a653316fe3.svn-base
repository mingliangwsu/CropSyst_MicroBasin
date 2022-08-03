#include "common/physics/property/P_vapor_pressure.h"
#include <math.h>
#include "corn/math/moremath.h"
namespace Physical
{
//______________________________________________________________________________
float64 calc_saturation_kPa(float64 at_temperature_C  ,float64 air_temp_C, bool over_water_only)  //kPa
{  // at_temperature_C and air_temp_C should at this point be valid
   //  Ref: Murray, F.W. 1966 "On the computation  of Saturation Vapor Pressure" J. Appl. Meteor. 6 p 204
   bool over_water_only_or_above_freezing = over_water_only || (air_temp_C >= -2.0 ); //040114

   //over_water_only_or_above_freezing = true; // uncomment this to match Claudio's equations.over_water_only_or_above_freezing = true; // This is to match Claudio's equations.


   // Use different coefficients for above freezing (over water) and below freezing (over ice)  //040112_
   //                                temperature:  above        below  freezing
   //                                   or  over:  water        ice
   float64 b = over_water_only_or_above_freezing ? 35.86      : 7.66;
   float64 a = over_water_only_or_above_freezing ? 17.2693882 : 21.8745584;
   float64 denominator = (C_to_kelvin(at_temperature_C) - b);
   float64 exp_term = (a * at_temperature_C) / denominator;
   float64 satVP = 0.6108 * exp(exp_term);
      // Note that the 0.6108 kPa
      // was 6.108  Millibars in the original papers
   //original  float64 svp = 0.6108 * exp((17.27 * airtemp) / (airtemp + 237.3));    // denominator (C_to_K(air_temp) - b)
   return satVP;   // kiloPascals
} // checked 011008, 081020
//_2015-03-03________________________________________________________________________________________
float64 Vapor_pressure_interface::calc_saturation_kPa(float64 at_temperature_C  ,float64 air_temp_C, bool over_water_only) const //kPa
{
   return Physical::calc_saturation_kPa(at_temperature_C,air_temp_C,over_water_only);

/* moved to Physical::calc_saturation_kPa
   // at_temperature_C and air_temp_C should at this point be valid
   //  Ref: Murray, F.W. 1966 "On the computation  of Saturation Vapor Pressure" J. Appl. Meteor. 6 p 204
   bool over_water_only_or_above_freezing = over_water_only || (air_temp_C >= -2.0 ); //040114

   //over_water_only_or_above_freezing = true; // uncomment this to match Claudio's equations.over_water_only_or_above_freezing = true; // This is to match Claudio's equations.


   // Use different coefficients for above freezing (over water) and below freezing (over ice)  //040112_
   //                                temperature:  above        below  freezing
   //                                   or  over:  water        ice
   float64 b = over_water_only_or_above_freezing ? 35.86      : 7.66;
   float64 a = over_water_only_or_above_freezing ? 17.2693882 : 21.8745584;
   float64 denominator = (C_to_kelvin(at_temperature_C) - b);
   float64 exp_term = (a * at_temperature_C) / denominator;
   float64 satVP = 0.6108 * exp(exp_term);
      // Note that the 0.6108 kPa
      // was 6.108  Millibars in the original papers
   //original  float64 svp = 0.6108 * exp((17.27 * airtemp) / (airtemp + 237.3));    // denominator (C_to_K(air_temp) - b)
   return satVP;   // kiloPascals
*/
} // checked 011008, 081020
//______________________________________________________________________________
float64 Vapor_pressure_interface::saturation_temperature // C  // rename this to
(float64 saturation_vapor_pressure // kPa
,float64 airtemp
,bool over_water_only)                                                     const
{ // Warning, dont know why generated values are sometimes < 0.

  float64 VP_sat = CORN_must_be_greater_or_equal_to(saturation_vapor_pressure,0.001);  //980318
   bool over_water_only_or_above_freezing = over_water_only || (airtemp >= -2.0); //040114

//over_water_only_or_above_freezing = true; // This uncomment this to match Claudio's equations.

// Note that this code is replicated in vapor_pressure_day.
// The inverse of this function is in VP_vapor_pressure this probably should be moved there

   // Use different coefficients for above freezing (over water) and below freezing (over ice) 040112
   //                                temperature:  above        below  freezing
   //                                   or  over:  water        ice
   float64 b = over_water_only_or_above_freezing ? 35.86      : 7.66;            //040112
   float64 a = over_water_only_or_above_freezing ? 17.2693882 : 21.8745584;      //040112
   float64 x = CORN_ln(VP_sat/0.6108);                                           //021125
   return (273.16 - b) * x / (a - x);
}
//_1998-03-05___________________________________________________________________
float64 Vapor_pressure_interface::calc_slope_of_saturation(float64 avg_air_temp) const
{ // slope in kPa/C ; aritemp in degrees celcius }
   // RLN check with Claudio: I dont know if we will want to consider over ice here, we originally only had OVER_WATER_ONLY!!!! 040114_
   float64 svp =  calc_saturation_kPa(avg_air_temp,avg_air_temp,OVER_WATER_ONLY);//040114
   float64 num = svp * 4098.0;
   float64 denum = avg_air_temp + 237.3;   // WARNING I think this needs to be  avg_air_temp + kelvin - b  from saturation_vapor_pressure
   float64 sqr_denum = CORN_sqr(denum);
   float64 ssvp = num/sqr_denum;
   return ssvp;
}
//______________________________________________________________________________
} // namespace physical

