#include "common/geodesy/geolocation.h"
#include "crop_orchard_Oyarzun_Stockle.h"
#include "common/weather/day/sun_days.h"
#include "common/weather/hour/sun_hours.h"
#include "common/weather/hour/weather_hours.h"
#include "common/weather/sun.h"
#include <math.h>
#ifndef moremathH
#  include "corn/math/moremath.h"
using namespace std;
#endif
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif

// Claudio question is row spacing along the same as column spacing
/*
ofstream debug_oyarzun("debug_oyarzun.dat");
*/
#ifdef DEBUG_OYARZUN_HOUR
ofstream debug_oyarzun_hour("debug_oyarzun_hour.dat");
#endif


namespace CropSyst {
//______________________________________________________________________________
Orchard_interception_Oyarzun_Stockle::Orchard_interception_Oyarzun_Stockle
( CropSyst::Crop_parameters_struct::Layout                            &layout_                 //110218
, CropSyst::Crop_parameters_struct::Canopy_characteristics_hedge_row  &canopy_characteristics_ //110218
, float64  slope_percent_
, float64  slope_aspect_N0_E90_degrees_
, const Sun_days           &sun_days_        // Provided by weather/meteorology
, const Sun                &sun_
, const Sun_hours          &sun_hours_
, const CS::Weather_hours  &weather_hours_
, const float64            &fract_cloud_cover_                                   //151027
, const CORN::Date_const   &today_)
: Orchard_common::Interception
   (layout_
   ,canopy_characteristics_
   ,slope_percent_
   ,slope_aspect_N0_E90_degrees_
   ,sun_days_
   ,fract_cloud_cover_
   ,today_)
,sun_position(sun_)
,sun_hours(sun_hours_)
,weather_hours(weather_hours_)
, solid_interception_daily          (0.0)
, row_spacing_along                 (layout_.spacing.col)                        //180109
//180109 , row_spacing_along                 (layout_.col_spacing)
// The following contributes are updated as needed (Initializing to a huge number to validate they are updated in the proper sequence
, declination_radians_daily         (99999.9)
, limited_plot_width                (99999.9)
, limited_plot_breadth              (99999.9)
, solar_zenith_angle_radians_hourly (99999.9)
, solar_azimuth_angle_radians_hourly(99999.9)
, shadow_correction_factor_hourly   (99999.9)
, A_Daily_Dif_transmit_Rs           (99999.9)
, solar_beam_irradiance_hour        (99999.9)
, solar_diffuse_irradiance_hour     (99999.9)
, hour(24)
//151029, doy(999)
{
#ifdef DEBUG_OYARZUN_HOUR
debug_oyarzun_hour
<< "doy" << '\t'
<< "hour" << '\t'
<< "solar_zenith_angle_radians"  << '\t'
<< "solar_azimuth_angle_radians" << '\t'
<< "shadow_correction_factor"    << '\t'
<< "A_Daily_Dif_transmit_Rs"     << '\t'
<< "solar_beam_irradiance"       << '\t'
<< "solar_diffuse_irradiance"    << '\t'
<< "solid_hourly_interception"   << '\t'
<< "solar_irradiance_fract"      << '\t'
<< endl;
#endif
};
//______________________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::update_solid_canopy_interception
//151027 now member references (CORN::DOY _doy, float64 fract_cloud_cover_unused_by_this_model)
()
modification_
{
   //151027 doy = _doy;
   CORN::DOY doy = today.get_DOY();                                                        //151027
   solid_interception_daily = 0.0;
   float64 plot_width    = tree_canopy->width.get();                             //071117
   float64 plot_breadth  = tree_canopy->breadth.get();                           //071117
   limited_plot_width = CORN::must_be_less_or_equal_to<float64>
      (plot_width,layout.spacing.row);                                           //180109
      //180109 (plot_width,layout.row_spacing);
   limited_plot_breadth = CORN::must_be_less_or_equal_to<float64>(plot_breadth ,row_spacing_along);
   declination_radians_daily =  sun_days.get_solar_declination_rad(doy);      // moved to sun_days: calc_solar_declination_daily(); // Note that we can probably get this from Sun
   Local_time &sun_rise_time = sun_position.get_sun_rise_time();                 //071115
   sunrise_hour = sun_rise_time.get_hour();                                      //071115
   Local_time &sun_set_time = sun_position.get_sun_set_time();                   //071115
   sunset_hour =  sun_set_time.get_hour();                                       //071115
   for (hour = 0; hour < 24; hour++)
   {   float64  solar_irradiance_fract_hour = weather_hours.
         get_insolation_fraction(hour);                                          //151224
      //151224 extraterrestrial_solar_irradiance.get_insolation_fraction(doy,hour); //150627
/*150627
   // next line replaced with above

       solar_irradiance_fract_hour =  weather_hours. get_solar_irradiance_fract(hour);
*/
       if ( solar_irradiance_fract_hour > 0.001)
       {
      solar_zenith_angle_radians_hourly  = sun_hours.get_solar_zenith_angle_rad(doy,hour);
      solar_azimuth_angle_radians_hourly = sun_hours.get_solar_azimuth_angle_radians(doy,hour); // was calc_solar_azimuth_angle_radians(hour, solar_zenith_angle_radians_hourly);
      shadow_correction_factor_hourly    = calc_shadow_correction_factor(); // dependency solar_azimuth_angle_radians_hourly , slope_radians
      A_Daily_Dif_transmit_Rs = calc_daily_diffuse_transmittance_of_Rs_for_hour(); // even though this says daily, it is an hourly
      solar_beam_irradiance_hour = weather_hours.get_solar_direct_irradiance_MJ_m2(hour);
      solar_diffuse_irradiance_hour =  weather_hours.get_solar_diffuse_irradiance_MJ_m2(hour);
      float64 solid_hourly_interception = calc_hourly_solid_interception();
#ifdef OBSOLETE
081103 decided we only need daily aggregation and it was working OK.
                  solid_canopy_interception[hour] = solid_hourly_interception;
#endif
#ifdef DEBUG_OYARZUN_HOUR
debug_oyarzun_hour
<< (int)doy << '\t'
<< (int)hour << '\t'
<< solar_zenith_angle_radians_hourly   << '\t'
<< solar_azimuth_angle_radians_hourly  << '\t'
<< shadow_correction_factor_hourly     << '\t'
<< A_Daily_Dif_transmit_Rs             << '\t'
<< solar_beam_irradiance_hour          << '\t'
<< solar_diffuse_irradiance_hour       << '\t'
<< solid_hourly_interception<< '\t'
<< solar_irradiance_fract_hour << '\t'
<< endl;
#endif
      solid_interception_daily +=  solar_irradiance_fract_hour * solid_hourly_interception;
            // solar_irradiance_fract should be 0 at night
            // solid_hourly_interception not relevent
      };
   };
   return solid_interception_daily;
};
//______________________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::calc_hourly_solid_interception() modification_
{
   // The following contributes should have already been updated before calling this method
   //    hour
   //    solar_beam_irradiance_hour
   //    solar_diffuse_irradiance_hour
   //    A_Daily_Dif_transmit_Rs

   // (T30)calculates, as main results, interception
   // for a hedgerow (fruit tree)and a given day and location.

   // Developed by R. Oyarzun; PhD (C), BSYSE Dept., WSU
   // (originally on September 2003, new version, March 2005)

   // Adapted for CropSyst C++ by Roger Nelson 2007

   // Daily values (day, total global radiation)
   // RLN unused:   Dim Rs As Double
#ifdef UNUSED
071114
   float64 alley_width = layout.row_spacing - limited_plot_width;
   float64 Shadow_Length_Across_Rows = (calc_shadow_length(solar_zenith_angle_radians_hourly,solar_azimuth_angle_radians_hourly)
         -
         calc_ghost_shadow_length(solar_zenith_angle_radians_hourly,solar_azimuth_angle_radians_hourly )) * shadow_correction_factor_hourly;
   float64 Corrected_Shadow_Length_Across_Rows
      = (Shadow_Length_Across_Rows < alley_width)
      ? Shadow_Length_Across_Rows
      : alley_width;
   float64 Alley_ALONG = row_spacing_along - limited_plot_breadth
   float64 Shadow_Length_Along_Rows = (calc_shadow_length_along() - _
    calc_ghost_shadow_length_along(  )) * shadow_correction_factor_hourly
   float64 Corrected_Shadow_Length_Along_Rows =
   (Shadow_Length_Along_Rows < Alley_ALONG)
    ? Shadow_Length_Along_Rows
    : Alley_ALONG;
#endif
 // fraction_shaded_orchard  the shadow of the tree excluding sun flecks   (as if the canopy were fully solid)
   float64 fraction_shaded_orchard = calc_fraction_of_shade(solar_zenith_angle_radians_hourly,solar_azimuth_angle_radians_hourly  );
   float64 total_irradiance_hour = (solar_beam_irradiance_hour + solar_diffuse_irradiance_hour);
   total_irradiance_hour = CORN::must_be_greater_or_equal_to<float64>(total_irradiance_hour,0.000001); // Avoid div0 //071117
   float64 hourly_fraction_of_beam_radiation    = solar_beam_irradiance_hour    / total_irradiance_hour;
   float64 hourly_fraction_of_diffuse_radiation = solar_diffuse_irradiance_hour / total_irradiance_hour;
   float64 solid_orchard_radiation_interception = fraction_shaded_orchard * hourly_fraction_of_beam_radiation + (1.0 - A_Daily_Dif_transmit_Rs) * hourly_fraction_of_diffuse_radiation;
/*
#ifdef DEBUG_OYARZUN_HOUR
debug_oyarzun_hour
<< (int)doy << '\t'
<< (int)hour << '\t'
<< solar_zenith_angle_radians_hourly << '\t'
<< solar_azimuth_angle_radians_hourly << '\t'
<< fraction_shaded_orchard << '\t'
<< total_irradiance_hour << '\t'
<< hourly_fraction_of_beam_radiation << '\t'
<< hourly_fraction_of_diffuse_radiation << '\t'
<< solid_orchard_radiation_interception << '\t'
<< A_Daily_Dif_transmit_Rs << '\t'
<< 'c'<<endl;
#endif
*/
   return solid_orchard_radiation_interception; // including sun fleck (porosity of the canopy).
}; // calc_hourly_interception
//_2007_________________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::calc_daily_diffuse_transmittance_of_Rs_for_hour() modification_ // of_solar_radiation?
{  float64 Daily_Dif_transmit_Rs = 0.0;
   CORN::DOY doy = today.get_DOY();                                              //151027
   // Calculate diffuse transmissivity by integration of beam transmissivity for daylight hours
   for (CORN::Hour local_hour = (sunrise_hour + 1 ) ; local_hour <= sunset_hour; local_hour += 1.0)
   {  float64 Local_Solar_Zenith_Angle =  sun_hours.get_solar_zenith_angle_rad(doy,local_hour);       //071115 calc_solar_zenith_angle(local_hour)
      float64 local_solar_azimuth_angle = sun_hours.get_solar_azimuth_angle_radians(doy,local_hour);  //071116 calc_solar_azimuth_angle_radians(local_hour,Local_Solar_Zenith_Angle, )
      float64 local_fraction_shaded_orchard = calc_fraction_of_shade(Local_Solar_Zenith_Angle, local_solar_azimuth_angle);
      // This value is not an "actual" transmittance for the hour. However, it is
      // assumed that PAR Transmittance does not change through the day, so an average value
      // will be assigned for each hour which results to be the summation of these
      // hourly "pseudo" values.
      float64 Local_Solar_Zenith_Angle_previous_hour = sun_hours.get_solar_zenith_angle_rad(doy,local_hour- 1.0 );
      float64 Pseudo_Hourly_Dif_transm_Rs
         = (1.0 - local_fraction_shaded_orchard)
         * sin(Local_Solar_Zenith_Angle) * cos(Local_Solar_Zenith_Angle)
         * (fabs(
               Local_Solar_Zenith_Angle_previous_hour - Local_Solar_Zenith_Angle));
      Daily_Dif_transmit_Rs += Pseudo_Hourly_Dif_transm_Rs;
   }; // for local_hour
   float64 A_Daily_Dif_transmit_Rs = 2.0 * Daily_Dif_transmit_Rs;
   A_Daily_Dif_transmit_Rs = CORN::must_be_less_or_equal_to<float64>(A_Daily_Dif_transmit_Rs,0.9);
   // This accounts for the "mathematical possibility" when a value of daily diff. transmit.
   // close to 1 is estimated. In that case, it is assigned an arbitrary value of 0.90,
   // and a message is given (as given below)
   return A_Daily_Dif_transmit_Rs;
};
//_2007-11-15___________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::calc_shadow_length
(float64 solar_zenith_angle_radians_hourly_param
, float64 solar_azimuth_angle_radians_hourly_param)                        const
{  //This function calculates the plant shadow length perpendicular
   // to the row, for a flat terrain condition
   // (so far, it does not account for slope effect)
   // For further details see Cohen et al., 1997, Ag. For. Met 86:225-234
   // The following contributes should have already been calculated:
   //    solar_azimuth_angle_radians_hourly
   //    row_azimuth_radians
   //    row_height           // from  Orchard_common
   float64 tree_height   = tree_canopy->height.get();                            //071117
   float64 SL1 = fabs(sin(solar_azimuth_angle_radians_hourly_param - row_azimuth_radians));
   float64 shadow_length = tree_height * (tan(solar_zenith_angle_radians_hourly_param)) * SL1;
   shadow_length = CORN::must_be_greater_or_equal_to<float64>(shadow_length,0.0);
   return shadow_length;
};
//______________________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::calc_ghost_shadow_length
( float64 solar_zenith_angle_radians_hourly_param
, float64 solar_azimuth_angle_radians_hourly_param)                        const
{  // This function calculates the "blank space" in the shadow length cast, perpendicular
   // to the row, for a flat terrain condition, given the insercion height of the
   // lower branches (using the same equation as for shaldow length
   // The following contributes should have already been calculated:
   //    row_azimuth_radians
   //    height_of_insertion_of_branches  // not sure if crop parameter or calculated daily
   float64 GSL1 = fabs(sin(solar_azimuth_angle_radians_hourly_param - row_azimuth_radians));
   float64 ghost_shadow_length = canopy_characteristics.branch_insertion_height * (tan(solar_zenith_angle_radians_hourly_param)) * GSL1;
   ghost_shadow_length         = CORN::must_be_greater_or_equal_to<float64>(ghost_shadow_length,0.0);
   return ghost_shadow_length;
};
//______________________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::calc_shadow_length_along
( float64 solar_zenith_angle_radians_hourly_param
, float64 solar_azimuth_angle_radians_hourly_param)                        const
{
   // The following contributes should have already been calculated:
   //    solar_azimuth_angle_radians_hourly
   //    row_azimuth_radians
   //    row_height           // from  Orchard_common
   //    solar_zenith_angle_radians_hourly
   float64 SL3 = fabs(cos(solar_azimuth_angle_radians_hourly_param - row_azimuth_radians));
   float64 tree_height   = tree_canopy->height.get();                            //071117
   float64 shadow_length_along = tree_height * (tan(solar_zenith_angle_radians_hourly_param)) * SL3;
   shadow_length_along = CORN::must_be_greater_or_equal_to<float64>(shadow_length_along,0.0);
   return shadow_length_along;
};
//______________________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::calc_ghost_shadow_length_along
( float64 solar_zenith_angle_radians_hourly_param
, float64 solar_azimuth_angle_radians_hourly_param)                        const
{
   // The following contributes should have already been calculated:
   //    solar_azimuth_angle_radians_hourly
   //    row_azimuth_radians
   //    height_of_insertion_of_branches
   //    solar_zenith_angle_radians_hourly
   float64 GSL4 = fabs(cos(solar_azimuth_angle_radians_hourly_param - row_azimuth_radians));
   float64 ghost_shadow_length_along = canopy_characteristics.branch_insertion_height * (tan(solar_zenith_angle_radians_hourly_param)) * GSL4;
   ghost_shadow_length_along = CORN::must_be_greater_or_equal_to<float64>(ghost_shadow_length_along,0.0);
   return ghost_shadow_length_along;
};
//______________________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::calc_shadow_correction_factor() const
{
   // The following contributes should already have been calculated:
   //    solar_azimuth_angle_radians_hourly
   //    slope_aspect_from_south_radians
   //    slope_radians
   // Corrects for the fact that the effective shadow length cast on a sloped
   // surface could be grater or smaller than the shadow cast on a horizontal plane
   float64 shadow_correction_fact = 0;
   float64 abs_solar_angle_minus_appect_slope_radians = fabs(solar_azimuth_angle_radians_hourly - slope_aspect_from_south_radians);
   if      (abs_solar_angle_minus_appect_slope_radians < (CORN_pi * 0.25))  shadow_correction_fact = cos(slope_radians);
   else if (abs_solar_angle_minus_appect_slope_radians < (CORN_pi * 0.75))  shadow_correction_fact = 1.0;
   else if (abs_solar_angle_minus_appect_slope_radians < (CORN_pi * 1.25))  shadow_correction_fact = 1.0 / cos(slope_radians);
   else if (abs_solar_angle_minus_appect_slope_radians < (CORN_pi * 1.75))  shadow_correction_fact = 1.0;
   else                                                                     shadow_correction_fact = cos(slope_radians);
   shadow_correction_fact = CORN::must_be_greater_or_equal_to<float64>(shadow_correction_fact,0.0);
   return shadow_correction_fact;
};
//______________________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::calc_fraction_of_shade
( float64 solar_zenith_angle_radians_hourly_param    // Must be a parameter not the member value
, float64 solar_azimuth_angle_radians_hourly_param)                        const
{
   // The following contributes should have already been calculated:
   //    shadow_correction_factor_hourly
   //    row_azimuth_radians
   //    row_height           // from  Orchard_common
   //    height_of_insertion_of_branches
   //    row_spacing          // crop layout parameter
   //    row_spacing_along    // crop layout parameter
   float64 Shlength_corr // This is the  correction for the length of the shadow due to slope
      = (   calc_shadow_length      (solar_zenith_angle_radians_hourly_param,solar_azimuth_angle_radians_hourly_param)
         -  calc_ghost_shadow_length(solar_zenith_angle_radians_hourly_param,solar_azimuth_angle_radians_hourly_param)) * shadow_correction_factor_hourly;
   float64 Shlength_corr_ALONG // This is the correction for the length of the shadow due to slope
      = (calc_shadow_length_along(solar_zenith_angle_radians_hourly_param,solar_azimuth_angle_radians_hourly_param)
         - calc_ghost_shadow_length_along(solar_zenith_angle_radians_hourly_param,solar_azimuth_angle_radians_hourly_param)) * shadow_correction_factor_hourly;
   float64 Term1 =
      ((Shlength_corr + limited_plot_width) * (limited_plot_breadth + Shlength_corr_ALONG)
       - (Shlength_corr * Shlength_corr_ALONG))
         / (layout.spacing.row/*180109 row_spacing*/ * row_spacing_along);
   Term1 = CORN::must_be_less_or_equal_to<float64>(Term1,1.0);
   return Term1;
};
//______________________________________________________________________________
#ifdef OBSOLETE
RLN solar declination is already available form Sun_days
float64 Orchard_interception_Oyarzun_Stockle::calc_solar_declination_daily( )
{  // This function calculates solar declination (radians) for a given day of year
   // The following contributes should have already been calculated:
   // day of the year (doy)
   float64 sindec = 0.39785 * sin(4.869 + 0.0172 * doy + 0.03345 * sin(6.224 + 0.0172 * doy))
   // RLN Note that  sindec is already available in SUN
   float64 cosdec = sqrt(1.0 - sindec * sindec);
   float64 solar_declination_daily = atan(sindec / cosdec);
   // solar_declination_daily also already be available in weather/Sun but it is calculated as asin(sindec) I am not sure if this function is one to one
   return solar_declination_daily;
};
#endif
//______________________________________________________________________________
#ifdef OBSOLETE
071115 RLN Using my own calculations for this  (dont delete this until I verify the differences)
float64 Orchard_interception_Oyarzun_Stockle::calc_solar_zenith_angle
(CORN::Hour hour_param)
{  // This function calculates solar zenith angle (radians)
   // The following contributes should have already been calculated:
   //    declination_radians_daily
   float64 t0 = sun_hours.get_solar_noon(doy); // was calc_solar_noon(doy, longitude_radians, standard_meridian_radians);
   // Estimate auxiliary trigonom. functions for calculation purposes
   float64 cosz = sin(latitude_radians) * sin(declination_radians_daily) + cos(latitude_radians)
        * cos(declination_radians_daily) * cos(0.2618 * (hour_param - t0));
   sinz = sqrt(1.0 - cosz * cosz);
   float64 solar_zenith_angle = M_PI_2 - atan(cosz / sinz);
   if (cosz < 0) solar_zenith_angle = M_PI_2
   return solar_zenith_angle;
};
#endif
//______________________________________________________________________________
#ifdef OBSOLETE
//071115 RLN Using my own calculations for this
// RLN can move this to sun_hours
float64 Orchard_interception_Oyarzun_Stockle::calc_half_day_length
( CORN::DOY  doy
, float64 latitude_radians )
{  // This function calculates the half daly length, returning
   // a value in radians (and not considering twilight)
   // The following contributes should have already been calculated:
   //    declination_radians_daily
   float64 coshs = (-sin(latitude_radians) * sin(declination_radians_daily)) /
        (cos(latitude_radians) * cos(declination_radians_daily));
   //Auxiliar trigonometric functions
   float64 sinhs = sqrt(1.0 - coshs * coshs);
   float64 half_day_length = M_PI_2 - atan(coshs / sinhs);
   return half_day_length;
};
#endif
//______________________________________________________________________________
#ifdef OBSOLETE
//071115 RLN Using my own calculations for this
float64 Orchard_interception_Oyarzun_Stockle::calc_hour_of_sunrise
( CORN::DOY  doy
, float64 latitude_radians
, float64 longitude_radians
, float64 standard_meridian_radians )
{ // This calculates the time (hour) of sunrise
   float64 noon = sun_position/*_hours*/.get_solar_noon(/*doy*/); // calc_solar_noon(doy, longitude_radians, standard_meridian_radians);
   float64 halfday = calc_half_day_length(doy, latitude_radians);
   float64 hour_of_sunrise = noon - ((halfday * 180 / CORN_pi) / 15);
   return hour_of_sunrise;
};
#endif
//______________________________________________________________________________
#ifdef OBSOLETE
//071115 RLN Using my own calculations for this
float64 Orchard_interception_Oyarzun_Stockle::calc_hour_of_sunset
( CORN::DOY doy
, float64 latitude_radians
, float64 longitude_radians
, float64 standard_meridian_radians)
{ // This calculates the time (hours) of sunset
   float64 noon = sun_position/*_hours*/.get_solar_noon(/*doy*/); // calc_solar_noon(doy, longitude_radians, standard_meridian_radians);
   float64 halfday = calc_half_day_length(doy, latitude_radians);
   float64 sunset = noon + ((halfday * 180.0 / CORN_pi) / 15.0);
   return sunset;
};
#endif
//______________________________________________________________________________
#ifdef CHECK_USED
//071114 RLN
Function Orchard_interception_Oyarzun_Stockle::BeamExtinctionCoeff(X As Double, ZenithAngle As Double, Absorptivity As Double) As Double
  This function calculates extinction coefficient for beam radiation of
  a canopy with Leaves angles distribution approximated using an ellipsoidal model.
  The extinction coefficient is for specified absorptivity value
  Dim Numerator As Double, Denominator As Double, z As Double
  Const dtr = 0.0174533  Convert degrees to radians

  z = dtr * ZenithAngle
  Numerator = sqrt(X * X + (Tan(z)) ^ 2)
  Denominator = (X + 1.774 * (X + 1.182) ^ (-0.733))
  BeamExtinctionCoeff = (Numerator / Denominator) * sqrt(Absorptivity)
};
#endif
//______________________________________________________________________________
#ifdef CHECK_USED
//071114 RLN
Private Function Orchard_interception_Oyarzun_Stockle::DiffuseExtinctionCoeff(X As Double, LAI As Double, Absorptivity As Double) As Double
  This function calculates extinction coefficient for diffuse radiation of
  a canopy with Leaves angles distribution approximated using an ellipsoidal model.
  The extinction coefficient is for specified Leaves area index and absorptivity values
  Dim ZenithSolarAngle As Double, TauBeam As Double, TauDiffuse As Double, i As Double
  TauDiffuse = 0
  For i = 0.01 To 1.57 Step 0.01  Integrate beam transmissivity for all zenith solar angles (radians)
    ZenithSolarAngle = i
    TauBeam = Exp(-BeamExtinctionCoeff(X, ZenithSolarAngle * 180 / CORN_pi, Absorptivity) * LAI)
    TauDiffuse = TauDiffuse + TauBeam * sin(ZenithSolarAngle) * cos(ZenithSolarAngle) * 0.01
  Next i
  TauDiffuse = 2 * TauDiffuse
  DiffuseExtinctionCoeff = -Log(TauDiffuse) / LAI;
};
#endif
//______________________________________________________________________________
#ifdef CHECK_USED
//071114 RLN
Function SunlitLAI
(X As Double, , LAI As Double
,Beam_Black_Leaves_Transmissivity As Double, Black_Leaves_Beam_Extinction_Coeff As Double) As Double
SunlitLAI = (1.0 - Beam_Black_Leaves_Transmissivity) / Black_Leaves_Beam_Extinction_Coeff
};
#endif
//______________________________________________________________________________
#ifdef CHECK_USED
//071114 RLN
Private Function Orchard_interception_Oyarzun_Stockle::SolarReflectionCoefficient(Absorptivity As Double, LAI As Double,  , _
Canopy_X_Value As Double) As Double
Dim Horizontal_Reflection_Coefficient As Double
Dim K_Beam_Black_Leaves As Double
Dim K_Diffuse_Black_Leaves As Double
Dim Reflection_Coefficient As Double
Horizontal_Reflection_Coefficient = (1.0 - sqrt(Absorptivity)) / (1.0 + sqrt(Absorptivity))
K_Beam_Black_Leaves = BeamExtinctionCoeff(Canopy_X_Value,  1)
K_Diffuse_Black_Leaves = DiffuseExtinctionCoeff(Canopy_X_Value, LAI, 1)
Reflection_Coefficient = 2 * K_Beam_Black_Leaves * Horizontal_Reflection_Coefficient / _
    (K_Beam_Black_Leaves + K_Diffuse_Black_Leaves)
SolarReflectionCoefficient = Reflection_Coefficient
};
#endif
//______________________________________________________________________________
#ifdef CHECK_USED
//071114 RLN
float64 Orchard_interception_Oyarzun_Stockle::AverageDiffusePlusScatteredIrradiance(Absorptivity As Double, LAI As Double, , _
Beam_Irradiance As Double, Diffuse_Irradiance As Double, Canopy_X_Value As Double) As Double
{
Dim Horizontal_Reflection_Coefficient As Double
Dim K_Beam_Black_Leaves As Double
Dim K_Diffuse_Black_Leaves As Double
Dim Reflection_Coefficient As Double
Dim K_Beam_Green_Leaves As Double
Dim Beam_Transmitted_Black_Leaves As Double
Dim Beam_Transmitted_Green_Leaves As Double
Dim Scattered_Radiation As Double
Dim New_Scattered As Double
Dim Old_Scattered As Double
Dim Sum_LAI As Double
Dim Sum_Diffuse_Plus_Scattered As Double
Dim Diffuse_Transmitted_Green_Leaves As Double
Dim K_Diffuse_Green_Leaves As Double
Dim Count As Integer

Horizontal_Reflection_Coefficient = (1.0 - sqrt(Absorptivity)) / (1.0 + sqrt(Absorptivity))
K_Beam_Black_Leaves = BeamExtinctionCoeff(Canopy_X_Value,  1)
K_Beam_Green_Leaves = BeamExtinctionCoeff(Canopy_X_Value,  Absorptivity)
Sum_Diffuse_Plus_Scattered = 0
Sum_LAI = 0.1
Count = 0
Do
    Count = Count + 1
    K_Diffuse_Black_Leaves = DiffuseExtinctionCoeff(Canopy_X_Value, Sum_LAI, 1)
    K_Diffuse_Green_Leaves = DiffuseExtinctionCoeff(Canopy_X_Value, Sum_LAI, Absorptivity)
    Reflection_Coefficient = 2 * K_Beam_Black_Leaves * Horizontal_Reflection_Coefficient / _
        (K_Beam_Black_Leaves + K_Diffuse_Black_Leaves)
    Beam_Transmitted_Black_Leaves = Beam_Irradiance * (1.0 - Reflection_Coefficient) * Exp(-K_Beam_Black_Leaves * Sum_LAI)
    Beam_Transmitted_Green_Leaves = Beam_Irradiance * (1.0 - Reflection_Coefficient) * Exp(-K_Beam_Green_Leaves * Sum_LAI)
    Scattered_Radiation = Beam_Transmitted_Green_Leaves - Beam_Transmitted_Black_Leaves
    Diffuse_Transmitted_Green_Leaves = Diffuse_Irradiance * (1.0 - Reflection_Coefficient) * Exp(-K_Diffuse_Green_Leaves * Sum_LAI)
    Sum_Diffuse_Plus_Scattered = Sum_Diffuse_Plus_Scattered + Diffuse_Transmitted_Green_Leaves + Scattered_Radiation
    Sum_LAI = Sum_LAI + 0.2
Loop Until Sum_LAI > LAI
AverageDiffusePlusScatteredIrradiance = Sum_Diffuse_Plus_Scattered / Count
}
#endif
//______________________________________________________________________________
#ifdef CHECK_IF_USED
//Not sure if the following subroutine is needed
Dim Sunlit_Leaves_Solar_Interception As Double
Dim Shaded_Leaves_Solar_Interception As Double
Dim Sunlit_Leaves_Average_PAR_Irradiance As Double
Dim Shaded_Leaves_Average_PAR_Irradiance As Double
Dim Sunlit_Leaves_Average_Solar_Irradiance As Double
Dim Shaded_Leaves_Average_Solar_Irradiance As Double
Dim Sunlit_Leaves_Radiation_Interception_Fraction As Double
Dim Shaded_Leaves_Radiation_Interception_Fraction As Double
Dim Fraction_Solar_Interception As Double

Dim Sunlit_LAI As Double
Dim Shaded_LAI As Double
Dim Total_Solar_Interception As Double
#endif
//______________________________________________________________________________
#ifdef CHECK_IF_USED
071115 RLN
Sub Orchard_interception_Oyarzun_Stockle::FractionSunlitShadedRadiationInterception(Canopy_X_Value As Double, LAI As Double, doy As Integer, _
solar_beam_irradiance_hour As Double, _
solar_diffuse_irradiance_hour As Double, Tree_Canopy As Boolean)
Dim K_Beam_Black_Leaves As Double
Dim K_Beam_Solar_Real_Leaves As Double
Dim Beam_Black_Leaves_Transmissivity As Double
Dim Beam_Real_Leaves_Solar_Transmissivity As Double
Dim K_Diffuse_Solar_Real_Leaves As Double
Dim Diffuse_Solar_Transmissivity As Double
Dim Diffuse_Solar_Interception As Double
Dim Beam_Solar_Interception As Double
Dim K_Beam_PAR_Real_Leaves As Double
Dim Beam_Real_Leaves_PAR_Transmissivity As Double
Dim K_Diffuse_PAR_Real_Leaves As Double
Dim Diffuse_PAR_Transmissivity As Double
Dim Sunlit_Leaves_Beam_PAR_Interception As Double
Dim Diffuse_PAR_Interception As Double
Dim Total_Solar_Irradiance As Double
Dim Solar_Reflection_Coefficient As Double

K_Beam_Black_Leaves = BeamExtinctionCoeff(Canopy_X_Value,  1)
Beam_Black_Leaves_Transmissivity = Exp(-K_Beam_Black_Leaves * LAI)
Sunlit_LAI = SunlitLAI(Canopy_X_Value,  LAI, Beam_Black_Leaves_Transmissivity, _
    K_Beam_Black_Leaves)
Shaded_LAI = LAI - Sunlit_LAI
Calculations for total solar radiation
Solar_Reflection_Coefficient = SolarReflectionCoefficient(0.5, LAI,  Canopy_X_Value)
K_Beam_Solar_Real_Leaves = BeamExtinctionCoeff(Canopy_X_Value,  0.5)
Beam_Real_Leaves_Solar_Transmissivity = Exp(-K_Beam_Solar_Real_Leaves * LAI)
K_Diffuse_Solar_Real_Leaves = DiffuseExtinctionCoeff(Canopy_X_Value, LAI, 0.5)
Diffuse_Solar_Transmissivity = Exp(-K_Diffuse_Solar_Real_Leaves * LAI)
Beam_Solar_Interception = (1.0 - Beam_Real_Leaves_Solar_Transmissivity) * solar_beam_irradiance_hour
Diffuse_Solar_Interception = (1.0 - Diffuse_Solar_Transmissivity) * solar_diffuse_irradiance_hour
W/m2 ground intercepted by sunlit leaves
Sunlit_Leaves_Solar_Interception = Beam_Solar_Interception + Diffuse_Solar_Interception * Sunlit_LAI / LAI
W/m2 ground intercepted by shaded leaves
Shaded_Leaves_Solar_Interception = Diffuse_Solar_Interception * Shaded_LAI / LAI
Total_Solar_Interception = Sunlit_Leaves_Solar_Interception + Shaded_Leaves_Solar_Interception
Total_Solar_Irradiance = solar_beam_irradiance_hour + solar_diffuse_irradiance_hour
Sunlit_Leaves_Radiation_Interception_Fraction = Sunlit_Leaves_Solar_Interception / Total_Solar_Irradiance
Shaded_Leaves_Radiation_Interception_Fraction = Shaded_Leaves_Solar_Interception / Total_Solar_Irradiance
Fraction_Solar_Interception = Total_Solar_Interception / Total_Solar_Irradiance
Substract reflected radiation before calculating transpiration
Sunlit_Leaves_Solar_Interception = Sunlit_Leaves_Solar_Interception * (1.0 - Solar_Reflection_Coefficient)
Shaded_Leaves_Solar_Interception = Shaded_Leaves_Solar_Interception * (1.0 - Solar_Reflection_Coefficient)
Calculations for solar irradiance

Dim Diffuse_Plus_Scattered_Solar_Irradiance As Double

Diffuse_Plus_Scattered_Solar_Irradiance = AverageDiffusePlusScatteredIrradiance(0.5, LAI,  solar_beam_irradiance_hour, _
    solar_diffuse_irradiance_hour, Canopy_X_Value)

Sunlit_Leaves_Average_Solar_Irradiance = K_Beam_Black_Leaves * solar_beam_irradiance_hour + Diffuse_Plus_Scattered_Solar_Irradiance

Shaded_Leaves_Average_Solar_Irradiance = Diffuse_Plus_Scattered_Solar_Irradiance

Calculations for photosynthetically active irradiance

Dim Beam_PAR_Irradiance As Double
Dim Diffuse_PAR_Irradiance As Double
Dim Diffuse_Plus_Scattered_PAR_Irradiance As Double
Dim K_Beam_PAR_Black_Leaves As Double

Beam_PAR_Irradiance = solar_beam_irradiance_hour * 0.5
Diffuse_PAR_Irradiance = solar_diffuse_irradiance_hour * 0.5

K_Beam_PAR_Black_Leaves = BeamExtinctionCoeff(Canopy_X_Value,  1)

Diffuse_Plus_Scattered_PAR_Irradiance = AverageDiffusePlusScatteredIrradiance(0.8, LAI,  Beam_PAR_Irradiance, _
    Diffuse_PAR_Irradiance, Canopy_X_Value)

   Sunlit_Leaves_Average_PAR_Irradiance = K_Beam_PAR_Black_Leaves * Beam_PAR_Irradiance + Diffuse_Plus_Scattered_PAR_Irradiance

   Shaded_Leaves_Average_PAR_Irradiance = Diffuse_Plus_Scattered_PAR_Irradiance
};
#endif
//______________________________________________________________________________
#ifdef UNUSED
RLN
float64 Orchard_interception_Oyarzun_Stockle::calc_beta
()
{  // This function allows the correction for a slope_radians surface
   // considering  the beam component of the incoming radiation (ratio between incidence and
   // zenith angle) (see Bonan, 2000)
   // The following contributes should have already been calculated:
   //    solar_azimuth_angle_radians_hourly
   //    slope_radians
   //    solar_zenith_angle_radians_hourly
   float64 Cosine_incidence = calc_cosine_incidence_angle(   )
   float64 Acf = Cosine_incidence / cos(solar_zenith_angle_radians_hourly);
   Acf = CORN_must_be_between_f64(Acf,0.0,1000.0);
   return Acf;
};
//______________________________________________________________________________
float64 Orchard_interception_Oyarzun_Stockle::calc_cosine_incidence_angle()
{  // This function calculates the incidence angle, defined as the angle between the suns beam
   // and an imaginary line perpendicular to the slope_radians
   // The following contributes should have already been calculated:
   //    solar_azimuth_angle_radians_hourly
   //    slope_radians
   //    slope_aspect_from_south_radians
   //    solar_zenith_angle_radians_hourly
   //
   float64 cosine_incidence_angle
      = cos(slope_radians) * cos(solar_zenith_angle_radians_hourly)
      + sin(slope_radians) * sin(solar_zenith_angle_radians_hourly)
         * cos(solar_azimuth_angle_radians_hourly - slope_aspect_from_south_radians);
   cosine_incidence_angle = CORN::must_be_greater_or_equal_to<float64>(cosine_incidence_angle,0.0);
   return cosine_incidence_angle;
};
//______________________________________________________________________________
#endif
//______________________________________________________________________________
} // namespace CropSyst

// V.B. had 680 lines

