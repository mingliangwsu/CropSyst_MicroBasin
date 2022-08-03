#ifdef USE_PCH
#  include "simulation/CropSyst_sim_pch.h"
#else
#include <math.h>
#include <corn/math/compare.h>
#include <corn/measure/measures.h>
#include "crop/crop_param.h"
#endif

#include "crop/crop_rows.h"

// Warning hours have been entered as 1 to 24  not 0 to 23
/*
'Asin = Atn(SSE / Sqr(-SSE * SSE + 1))
'Acos = Atn(-CSA / Sqr(-CSA * CSA + 1)) + 2 * Atn(1)
'If Sin(Acos - Row_Azimuth) = 0 Then SA = 1.570796 Else SA = Atn(Tan(Asin) / Sin(Acos - Row_Azimuth))
'If SA < 0 Then SA = -SA
*/

#define percent_slope_to_rad(x) atan(x/100)

namespace CropSyst
{
//______________________________________________________________________________

float64 debug_equiv_sol_elev = 0;
float64 debug_sin_equiv_sol_elev = 0;

float64 debug_sol_elev = 0;
float64 debug_sin_sol_elev = 0;

ofstream debug_rad_pot("rad_pot.dat");

#ifdef DEBUG1
#include <fstream.h>
bool distinguished_day = false;
ofstream hourly("hourly.txt");
#endif
//______________________________________________________________________________
float64 Crop_row_obsolete::calc_sine_solar_declination(CORN::DOY DOY)
{  float64 sin_solar_dec = 0.39785
   * sin(deg_to_rad(278.97 + 0.9856 * DOY
                    + 1.9165 * sin(deg_to_rad(356.6 + 0.9856 * DOY))));
   return sin_solar_dec;
}
//______________________________________________________________________________
float64 Crop_row_obsolete::calc_sine_solar_elevation
(float64 sin_solar_dec  // radians
,Hour hour)             // 24 hours
{
   //Dim Radian As Single, Asin As Single, SSE1 As Single, SSE2 As Single
   float64 asin_SSD = asin(sin_solar_dec);
   float64 SSE1 = sin(Latitude_rad) * sin_solar_dec
      + cos(Latitude_rad) * cos(asin_SSD) * cos(deg_to_rad(15 * (hour - 11)));
   return CORN_must_be_between(SSE1,-0.9999,0.9999);
}
//______________________________________________________________________________
float64 Crop_row_obsolete::calc_cosine_solar_azimuth
(float64 sin_solar_dec
,float64 sin_solar_elev)
{
   float64 asin_SSE = asin(sin_solar_elev);
   float64 CSA1 = -(sin_solar_dec - sin_solar_elev * sin(Latitude_rad))
                  / (cos(Latitude_rad) * cos(asin_SSE));
   return CORN_must_be_between(CSA1,-0.9999,0.9999);
}
//______________________________________________________________________________
float64 Crop_row_obsolete::calc_shadow_angle
(float64 Solar_Elev     // radians
,float64 Solar_Azimuth  // radians
)
{
   float64 Sine_Row_Solar_Az_Angle = fabs(sin(Solar_Azimuth - layout->get_row_azimuth_rad())); //020410
   float64 _SA = (Sine_Row_Solar_Az_Angle == 0)
   ? 1.570796
   : atan(tan(Solar_Elev) / Sine_Row_Solar_Az_Angle);
   return _SA;
}
//______________________________________________________________________________
float64 Crop_row_obsolete::calc_shadow_length
(float64 shadow_angle) // radians
{
   float64 _SL = (row_height - row_width + row_width / cos(shadow_angle))
                / tan(shadow_angle);
   return _SL;
}
//______________________________________________________________________________
float64 Crop_row_obsolete::RSRD             // this function is not currently used
(float64 sin_solar_elev   // radians
,float64  SA   // radians
)
{
   float64 asin_SSE = asin(sin_solar_elev);
   float64 ss = (asin_SSE <= 0.0)
   ? 0
   : fabs((row_height - row_width + row_width / cos(SA))
      / (tan(SA) * layout->row_spacing/*Row_Distance*/)); // 020410
   return CORN_must_be_between(ss,0.0,1.0);
}
//______________________________________________________________________________
float64 Crop_row_obsolete::calc_hourly_incident_angle
(float64 Solar_Elev
,float64 Solar_Azimuth )
{
//This functions determines the cosine of the angle of incidence, defined as the
//angle measured from a normal to the surface with given aspect and slope.  The
//equivalent solar elevation angle for the inclined plane is obtained by substracting
//the incident angle from 90 degrees or pi radians
   float64 Slope_radians = percent_slope_to_rad(Slope_percent);
   float64 Term1 = sin(Slope_radians);
   float64 Term2 = cos(Solar_Elev);
   float64 Term3 = cos(-(Aspect_radians - Solar_Azimuth));
   float64 Term4 = cos(Slope_radians);
   float64 Term5 = sin(Solar_Elev);
   float64 Cos_I_A = Term1 * Term2 * Term3 + Term4 * Term5;
   float64 _IA = atan(-Cos_I_A / sqrt(-Cos_I_A * Cos_I_A + 1.0)) + 2.0 * atan(1.0);
   return _IA;
}
//______________________________________________________________________________
float64 Crop_row_obsolete::calc_corrected_shadow_length
(float64 Shadow_Length
,float64 Solar_Elev
,float64 Solar_Azimuth
)
{
// This function corrects shadow length for the effect of aspect and slope

   float64 Slope_radians = percent_slope_to_rad(Slope_percent);
   float64 Cos_Solar_Aspect_Az_Angle = cos(Aspect_radians - Solar_Azimuth);
   // Determines slope component in the direction of the shadow
   float64 Slope_Comp = Slope_radians * Cos_Solar_Aspect_Az_Angle;
   float64 Cor_Factor = sin(Solar_Elev) / sin(3.14159 - Solar_Elev - Slope_Comp);
   float64 _CorSL = Shadow_Length * Cor_Factor;
   if ((_CorSL < row_width) && (_CorSL > 0) )
      _CorSL = row_width;
   return  CORN_must_be_greater_or_equal_to(_CorSL,0.0);
}
//______________________________________________________________________________
// Warning not sure why this function was originally declared variant.
float64 Crop_row_obsolete::calc_hourly_direct_radiation_potential(float64 sin_solar_elev)
{
   float64 _POTRAD = 1360.0 * sin_solar_elev * pow(0.75,(1.0 / sin_solar_elev));
   return CORN_must_be_greater_or_equal_to(_POTRAD,0.0);
}
//______________________________________________________________________________
void Crop_row_obsolete::get_hourly_interception
(Hour        hour
,float64    &Hourly_Direct_Row_Int
,float64    &Hourly_Direct_Rad_Pot
,float64    &Hourly_Diffuse_Row_Int
,float64    &Hourly_Diffuse_Rad_Pot
,float64    Sine_Solar_Dec
)
{
   Hourly_Direct_Row_Int = 0.0;
   Hourly_Diffuse_Row_Int = 0.0;
   float64 Sine_Solar_Elev = calc_sine_solar_elevation(Sine_Solar_Dec, hour);
   float64 Solar_Elev = CORN_must_be_greater_or_equal_to(asin(Sine_Solar_Elev),0.0);
      //this is arcsin: Atn(Sine_Solar_Elev / Sqr(-Sine_Solar_Elev * Sine_Solar_Elev + 1))

   if (Sine_Solar_Elev > 0)
   {
      float64 Cosine_Solar_Azimuth = calc_cosine_solar_azimuth( Sine_Solar_Dec, Sine_Solar_Elev);

      float64 Solar_Azimuth = (hour <= 11)
         ? acos(Cosine_Solar_Azimuth)
         : (1.5 * 3.14159 + asin(Cosine_Solar_Azimuth));

      float64 Hourly_Incident_Angle = calc_hourly_incident_angle(Solar_Elev, Solar_Azimuth);
      float64 Equivalent_Hourly_Solar_Elev = 3.14159 / 2.0 - Hourly_Incident_Angle;

      float64 Shadow_Length = 0;
      float64 Corrected_Shadow_Length = 0.0;
      if (Equivalent_Hourly_Solar_Elev > 0)
      {
            float64 Shadow_Angle = calc_shadow_angle(Solar_Elev, Solar_Azimuth);
            Shadow_Length = calc_shadow_length(Shadow_Angle);
            Corrected_Shadow_Length = calc_corrected_shadow_length(Shadow_Length,Solar_Elev,Solar_Azimuth);
      }
      Shadow_Length
         = (Solar_Elev > 0)
         ? calc_shadow_length(calc_shadow_angle(Solar_Elev, Solar_Azimuth));
         : 0;
      //         float64 Shadow_Angle = SA(Solar_Elev, Solar_Azimuth/*, Row_Azimuth*/);
      //         float64 Shadow_Length = calc_shadow_length(/*row_width, row_height, */Shadow_Angle);
      //         float64 Corrected_Shadow_Length = calc_corrected_shadow_length(Shadow_Length, Solar_Elev);
      float32 row_distance = layout->row_spacing;                                //020410
      Hourly_Direct_Row_Int = CORN_must_be_between(Corrected_Shadow_Length / row_distance,0.0,1.0);
      Hourly_Diffuse_Row_Int = CORN_must_be_between(Shadow_Length / row_distance,0.0,1.0);

#ifdef DEBUG1
   if (distinguished_day)
      hourly   << (int)hour <<','
               << rad_to_deg(Solar_Azimuth) <<','
               << rad_to_deg(Solar_Elev) << ','
               << rad_to_deg(Equivalent_Hourly_Solar_Elev) << ','
               << Shadow_Length << ','
               << Corrected_Shadow_Length << ','
               << Hourly_Direct_Row_Int << ','
               << Hourly_Diffuse_Row_Int << endl;
#endif

debug_equiv_sol_elev = Equivalent_Hourly_Solar_Elev;
debug_sin_equiv_sol_elev = sin(Equivalent_Hourly_Solar_Elev);

debug_sol_elev = Equivalent_Hourly_Solar_Elev;
debug_sin_sol_elev = sin(Equivalent_Hourly_Solar_Elev);

     Hourly_Direct_Rad_Pot =  (Equivalent_Hourly_Solar_Elev > 0)
        ? calc_hourly_direct_radiation_potential(sin(Equivalent_Hourly_Solar_Elev))
        : 0.0;
     Hourly_Diffuse_Rad_Pot =  (Solar_Elev > 0)
        ? calc_hourly_direct_radiation_potential(sin(Solar_Elev))
        : 0.0;
  }
}
//______________________________________________________________________________
void  Crop_row_obsolete::get_daily_interception
(CORN::DOY doy
,float64 &Daily_Direct_Row_Int
,float64 &Daily_Diffuse_Row_Int
)
{
   float64 Sine_Solar_Dec = calc_sine_solar_declination(doy);

   float64 Weighted_Direct_Row_Int = 0;
   float64 Weighted_Diffuse_Row_Int = 0;
   float64 Sum_Direct_Rad_Pot = 0;
   float64 Sum_Diffuse_Rad_Pot = 0;

   for (CORN_hour standard_hour = 0; standard_hour <=23; standard_hour++)
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

debug_rad_pot << (int)doy << '\t' << (int)standard_hour << '\t'
<< Hourly_Direct_Row_Int  << '\t'
<< Hourly_Diffuse_Row_Int  << '\t'
<< Hourly_Direct_Rad_Pot << '\t'
<< Hourly_Diffuse_Rad_Pot << '\t'
<< debug_equiv_sol_elev << '\t'
<< debug_sin_equiv_sol_elev << '\t'
<< debug_sol_elev << '\t'
<< debug_sin_sol_elev
<< endl;

   };

    Daily_Direct_Row_Int = Weighted_Direct_Row_Int / Sum_Direct_Rad_Pot;
    Daily_Diffuse_Row_Int = Weighted_Diffuse_Row_Int / Sum_Diffuse_Rad_Pot;

    // RLN The direct interception must be at least the diffuse ???
   //    Daily_Direct_Row_Int = CORN_max(Daily_Diffuse_Row_Int,Daily_Direct_Row_Int);
}
//______________________________________________________________________________
float64 Crop_row_obsolete::expand_dimension
(float64 deg_days_today
,float64 initial_dim
,float64 final_dim
,float64 deg_days_flowering
,float64 deg_days_veraison)
{
   float64 change_dim =
      (deg_days_today > deg_days_flowering) && (deg_days_today < deg_days_veraison)
       ? ((final_dim - initial_dim) *
          (deg_days_today - deg_days_flowering) /
          (deg_days_veraison - deg_days_flowering))
       : 0.0;
   return initial_dim + change_dim;
}
//_2000-07-17___________________________________________________________________
void Crop_row_obsolete::expand_dimensions
(float64 deg_days_today
,float64 deg_days_flowering                                                        //000718
,float64 deg_days_veraison)                                                        //000718
{
   row_width = expand_dimension
      (deg_days_today
      ,canopy_characteristics->initial_width
      ,canopy_characteristics->final_width
      ,deg_days_flowering
      ,deg_days_veraison);
   row_height = expand_dimension
      (deg_days_today
      ,canopy_characteristics->initial_height
      ,canopy_characteristics->final_height
      ,deg_days_flowering,deg_days_veraison);
}
//______________________________________________________________________________
Crop_row_obsolete::Crop_row_obsolete
(float64  _Latitude_rad
,float64  _Slope_percent
,float64  _Aspect_N0_E90_degrees
,Crop_parameters::Layout                         *_layout                     //020410
,Crop_parameters::Canopy_characteristics_hedge_row *_canopy_characteristics   //020410
)
: Latitude_rad       (_Latitude_rad)
, Slope_percent      (_Slope_percent)
, Aspect_radians         (0)    // Calculated below
,layout(_layout)                                                              //020410
,canopy_characteristics(_canopy_characteristics)                              //020410
{
   // We need to convert Aspect_N0_E90_degrees
   // to the orientation use by this model.

   // Armen confirmed that this works for southern hemisphere                       //020614
   // When negative is used for southern hemisphere.
   float32 aspect_S0_E90_degrees =                                               //020612
      (_Aspect_N0_E90_degrees > 180.0)
      ? (360 - _Aspect_N0_E90_degrees) + 180
      : (180 - _Aspect_N0_E90_degrees);
   Aspect_radians = deg_to_rad(aspect_S0_E90_degrees);
};
//______________________________________________________________________________
} // namespace CropSyst

