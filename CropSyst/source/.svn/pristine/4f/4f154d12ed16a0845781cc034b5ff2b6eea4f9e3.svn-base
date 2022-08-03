#include <math.h>
#include "corn/math/compare.h"
#include "corn/measure/measures.h"
#include "crop/crop_param.h"
#include "crop/crop_orchard_Kemanian_Stockle.h"
#include "common/weather/day/sun_days.h"
#include <iostream>
// Warning hours have been entered as 1 to 24  not 0 to 23
/*
'Asin = Atn(SSE / Sqr(-SSE * SSE + 1))
'Acos = Atn(-CSA / Sqr(-CSA * CSA + 1)) + 2 * Atn(1)
'If Sin(Acos - row_azimuth_radians) = 0 Then SA = 1.570796 Else SA = Atn(Tan(Asin) / Sin(Acos - row_azimuth_radians))
'If SA < 0 Then SA = -SA
*/


/*
float64 debug_equiv_sol_elev = 0;
float64 debug_sin_equiv_sol_elev = 0;

float64 debug_sol_elev = 0;
float64 debug_sin_sol_elev = 0;

ofstream debug_rad_pot("rad_pot.dat");
*/

namespace CropSyst {
//______________________________________________________________________________
Orchard_interception_Kemanian_Stockle::Orchard_interception_Kemanian_Stockle
(CropSyst::Crop_parameters_struct::Layout                            &layout_    //110218
,CropSyst::Crop_parameters_struct::Canopy_characteristics_hedge_row  &canopy_characteristics_ //110218
,float64           slope_percent_
,float64           slope_aspect_N0_E90_degrees_
,const Sun_days   &sun_days_         // Provided by weather
,const float64    &fract_cloud_cover_                                            //151027
,const CORN::Date_const &today_
,float64           latitude_rad_)                                                //020410
: Orchard_common::Interception
   (layout_
   ,canopy_characteristics_
   ,slope_percent_
   ,slope_aspect_N0_E90_degrees_
   ,sun_days_
   ,fract_cloud_cover_
   ,today_
   )
, latitude_rad       (latitude_rad_)
, fract_cloud_cover  (fract_cloud_cover_)                                        //151027
, solid_canopy_interception(1.0)                                                 //071117
{}
//______________________________________________________________________________
float64 Orchard_interception_Kemanian_Stockle::calc_sine_solar_elevation
(float64 sine_solar_declination
,Hour hour)                                                                const
{  //Dim Radian As Single, Asin As Single, SSE1 As Single, SSE2 As Single
   float64 asin_SSD = asin(sine_solar_declination);
   float64 SSE1 = sin(latitude_rad) * sine_solar_declination
       + cos(latitude_rad) * cos(asin_SSD) * cos(deg_to_rad(15 * (hour - 11)));
   return CORN_must_be_between(SSE1,-0.9999,0.9999);
}
//______________________________________________________________________________
float64 Orchard_interception_Kemanian_Stockle::calc_cosine_solar_azimuth
(float64 sine_solar_declination
,float64 sin_solar_elev)                                                   const
{  float64 asin_SSE = asin(sin_solar_elev);
   float64 CSA1 = -(sine_solar_declination - sin_solar_elev * sin(latitude_rad))
                   / (cos(latitude_rad) * cos(asin_SSE));
   return CORN_must_be_between(CSA1,-0.9999,0.9999);
}
//______________________________________________________________________________
float64 Orchard_interception_Kemanian_Stockle::calc_shadow_angle
(float64 solar_elev_radians
,float64 solar_azimuth_radians)                                            const
{
   float64 Sine_Row_Solar_Az_Angle = fabs(sin(solar_azimuth_radians - row_azimuth_radians)); //020410
   float64 _SA = (Sine_Row_Solar_Az_Angle == 0)
   ? 1.570796
   : atan(tan(solar_elev_radians) / Sine_Row_Solar_Az_Angle);
   return _SA;
}
//______________________________________________________________________________
float64 Orchard_interception_Kemanian_Stockle::calc_shadow_length
(float64 shadow_angle_radians)                                             const
{  float64 row_height = tree_canopy->height.get();                               //071117
   float64 row_width  = tree_canopy->width.get();                                //071117
   float64 shadow_length = (row_height - row_width + row_width / cos(shadow_angle_radians))
                 / tan(shadow_angle_radians);
   return shadow_length;
}
//______________________________________________________________________________
float64 Orchard_interception_Kemanian_Stockle::RSRD             // this function is not currently used
(float64 sin_solar_elev
,float64  SA   // units? radians or sine?
)                                                                          const
{  float64 row_height = tree_canopy->height.get();                               //071117
   float64 row_width  = tree_canopy->width.get();                                //071117
   float64 asin_SSE = asin(sin_solar_elev);
   float64 ss = (asin_SSE <= 0.0)
   ? 0
   : fabs((row_height - row_width + row_width / cos(SA))
      / (tan(SA) * layout.spacing.row/*180109 row_spacing*/));                   //020410
   return CORN_must_be_between(ss,0.0,1.0);
}
//______________________________________________________________________________
 float64 Orchard_interception_Kemanian_Stockle::calc_hourly_incident_angle
 (float64 solar_elev_radians
 ,float64 solar_azimuth_radians )                                          const
{
 //This functions determines the cosine of the angle of incidence, defined as the
 //angle measured from a normal to the surface with given aspect and slope.  The
 //equivalent solar elevation angle for the inclined plane is obtained by substracting
 //the incident angle from 90 degrees or pi radians
   float64 Term1 = sin(slope_radians);
   float64 Term2 = cos(solar_elev_radians);
   float64 Term3 = cos(-(slope_aspect_from_south_radians - solar_azimuth_radians));
   float64 Term4 = cos(slope_radians);
   float64 Term5 = sin(solar_elev_radians);
   float64 Cos_I_A = Term1 * Term2 * Term3 + Term4 * Term5;
   float64 _IA = atan(-Cos_I_A / sqrt(-Cos_I_A * Cos_I_A + 1.0)) + 2.0 * atan(1.0);
   return _IA;
}
//______________________________________________________________________________
float64 Orchard_interception_Kemanian_Stockle::calc_corrected_shadow_length
(float64 Shadow_Length
,float64 solar_elev_radians
,float64 solar_azimuth_radians)                                            const
{
 // This function corrects shadow length for the effect of aspect and slope
   float64 Cos_Solar_Aspect_Az_Angle = cos(slope_aspect_from_south_radians - solar_azimuth_radians);
   // Determines slope component in the direction of the shadow
   float64 Slope_Comp = slope_radians * Cos_Solar_Aspect_Az_Angle;
   float64 Cor_Factor = sin(solar_elev_radians) / sin(3.14159 - solar_elev_radians - Slope_Comp);
   float64 _CorSL = Shadow_Length * Cor_Factor;
   float64 row_width  = tree_canopy->width.get();                                //071117
   if ((_CorSL < row_width) && (_CorSL > 0) )
       _CorSL = row_width;
   return  CORN_must_be_greater_or_equal_to(_CorSL,0.0);
}
//______________________________________________________________________________
// Warning not sure why this function was originally declared variant.
float64 Orchard_interception_Kemanian_Stockle::calc_hourly_direct_radiation_potential(float64 sin_solar_elev) const
{  float64 _POTRAD = 1360.0 * sin_solar_elev * pow(0.75,(1.0 / sin_solar_elev));
   return CORN_must_be_greater_or_equal_to(_POTRAD,0.0);
}
//______________________________________________________________________________
void Orchard_interception_Kemanian_Stockle::get_hourly_interception
(Hour        hour
,float64    &Hourly_Direct_Row_Int
,float64    &Hourly_Direct_Rad_Pot
,float64    &Hourly_Diffuse_Row_Int
,float64    &Hourly_Diffuse_Rad_Pot
,float64    Sine_Solar_Dec )                                               const
{  Hourly_Direct_Row_Int = 0.0;
   Hourly_Diffuse_Row_Int = 0.0;
   float64 Sine_Solar_Elev = calc_sine_solar_elevation(Sine_Solar_Dec, hour);
   float64 solar_elev_radians = CORN_must_be_greater_or_equal_to(asin(Sine_Solar_Elev),0.0);
     //this is arcsin: Atn(Sine_Solar_Elev / Sqr(-Sine_Solar_Elev * Sine_Solar_Elev + 1))
   if (Sine_Solar_Elev > 0)
   {
      float64 Cosine_Solar_Azimuth = calc_cosine_solar_azimuth( Sine_Solar_Dec, Sine_Solar_Elev);
      float64 solar_azimuth_radians = (hour <= 11)
         ? acos(Cosine_Solar_Azimuth)
         : (1.5 * 3.14159 + asin(Cosine_Solar_Azimuth));
      float64 Hourly_Incident_Angle = calc_hourly_incident_angle(solar_elev_radians, solar_azimuth_radians);
      float64 Equivalent_Hourly_Solar_Elev = 3.14159 / 2 - Hourly_Incident_Angle;
      float64 Shadow_Length = 0;
      float64 Corrected_Shadow_Length = 0.0;
      if (Equivalent_Hourly_Solar_Elev > 0)
      {
            float64 Shadow_Angle = calc_shadow_angle(solar_elev_radians, solar_azimuth_radians);
            Shadow_Length = calc_shadow_length(Shadow_Angle);
            Corrected_Shadow_Length = calc_corrected_shadow_length(Shadow_Length,solar_elev_radians,solar_azimuth_radians);
      }
      if (solar_elev_radians > 0)
      {
         float64 Shadow_Angle = calc_shadow_angle(solar_elev_radians, solar_azimuth_radians);
         Shadow_Length = calc_shadow_length(Shadow_Angle);
      }
      else
         Shadow_Length = 0;
      //         float64 Shadow_Angle = SA(solar_elev_radians, solar_azimuth_radians/*, row_azimuth_radians*/);
      //         float64 Shadow_Length = calc_shadow_length(/*row_width, row_height, */Shadow_Angle);
      //         float64 Corrected_Shadow_Length = calc_corrected_shadow_length(Shadow_Length, solar_elev_radians);
      float32 row_distance = layout.spacing.row/*180109 row_spacing*/;           //020410
      Hourly_Direct_Row_Int = CORN_must_be_between(Corrected_Shadow_Length / row_distance,0.0,1.0);
      Hourly_Diffuse_Row_Int = CORN_must_be_between(Shadow_Length / row_distance,0.0,1.0);
      Hourly_Direct_Rad_Pot =  (Equivalent_Hourly_Solar_Elev > 0)
      ? calc_hourly_direct_radiation_potential(sin(Equivalent_Hourly_Solar_Elev))
      : 0.0;
      Hourly_Diffuse_Rad_Pot =  (solar_elev_radians > 0)
      ? calc_hourly_direct_radiation_potential(sin(solar_elev_radians))
      : 0.0;
   }
}
//______________________________________________________________________________
void  Orchard_interception_Kemanian_Stockle::get_daily_interception
(
 float64 &Daily_Direct_Row_Int
,float64 &Daily_Diffuse_Row_Int)                                           const
{
   CORN::DOY doy = today.get_DOY();                                              //151027
   float64 Sine_Solar_Dec = sun_days.get_sine_solar_declination(doy);
   float64 Weighted_Direct_Row_Int = 0;
   float64 Weighted_Diffuse_Row_Int = 0;
   float64 Sum_Direct_Rad_Pot = 0;
   float64 Sum_Diffuse_Rad_Pot = 0;
   for (CORN::Hour standard_hour = 0; standard_hour <=23; standard_hour++)
   {
      // original basic code uses hours 1-24 we use 0 - 23 hours
      float64 Hourly_Direct_Rad_Pot = 0.0001;
      float64 Hourly_Direct_Row_Int = 0.0;
      float64 Hourly_Diffuse_Rad_Pot = 0.0001;
      float64 Hourly_Diffuse_Row_Int = 0.0;
      get_hourly_interception
         (standard_hour
         ,Hourly_Direct_Row_Int  //returned
         ,Hourly_Direct_Rad_Pot  //returned
         ,Hourly_Diffuse_Row_Int //returned
         ,Hourly_Diffuse_Rad_Pot //returned
         ,Sine_Solar_Dec);
      Weighted_Direct_Row_Int += Hourly_Direct_Row_Int * Hourly_Direct_Rad_Pot;
      Sum_Direct_Rad_Pot += Hourly_Direct_Rad_Pot;
      Weighted_Diffuse_Row_Int += Hourly_Diffuse_Row_Int * Hourly_Diffuse_Rad_Pot;
      Sum_Diffuse_Rad_Pot += Hourly_Diffuse_Rad_Pot;
   }
   Daily_Direct_Row_Int = Weighted_Direct_Row_Int / Sum_Direct_Rad_Pot;
   Daily_Diffuse_Row_Int = Weighted_Diffuse_Row_Int / Sum_Diffuse_Rad_Pot;
   // RLN The direct interception must be at least the diffuse ???
   //    Daily_Direct_Row_Int = CORN_max(Daily_Diffuse_Row_Int,Daily_Direct_Row_Int);
}
//______________________________________________________________________________
float64 Orchard_interception_Kemanian_Stockle::update_solid_canopy_interception
()                                                                 modification_
{  solid_canopy_interception = 1.0;                                              //000717
   float64 direct_row_int = 0;
   float64 diffuse_row_int = 0;
   get_daily_interception(direct_row_int,diffuse_row_int);
   float64 diffuse_rad_fract = CORN_must_be_between((0.3+0.7 * fract_cloud_cover),0.0,1.0);
   solid_canopy_interception = direct_row_int * (1.0 - diffuse_rad_fract) + diffuse_row_int * diffuse_rad_fract;
std::cout << "WARNING: Kemanian Stockle interception model is not currently functional, it needs to be setup to feed hourly interception to crop potential transpration - Roger Oct 22,2008" << std::endl;
// Refer to Oyarzun-Stockle version where Crop_fruit potential transpration is calculated.
   return  solid_canopy_interception;
}
//______________________________________________________________________________
} // namespace CropSyst



