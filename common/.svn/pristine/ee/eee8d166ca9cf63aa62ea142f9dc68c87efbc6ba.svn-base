#include "common/biometeorology/ET_reference_Priestley_Taylor.h"
#include "common/weather/parameter/WP_vapor_pressure_deficit.h"
#include "corn/math/compare.hpp"
#include "corn/data_source/datarec.h"
#include "common/biometeorology/ET_model.h"
//______________________________________________________________________________
namespace CS
{
//______________________________________________________________________________
Priestley_Taylor_Parameters::Priestley_Taylor_Parameters
(CS::Parameter_float64 &VPDavg_seasonal_fullday_observed_)
: P_T_constant(DEF_PT_constant)
, P_T_alpha_fract(false,0.0,UC_fraction,CORN::missing_quality)
, VPDavg_seasonal_fullday_observed(VPDavg_seasonal_fullday_observed_)
, VPD_fullday(0)
{}
//_________________________________________________________________constructor_/
void Priestley_Taylor_Parameters::copy(const Priestley_Taylor_Parameters &from)
{
   P_T_constant   = from.P_T_constant;
   P_T_alpha_fract.copy(from.P_T_alpha_fract);
   VPD_fullday    = from.VPD_fullday;
   VPDavg_seasonal_fullday_observed.copy(from.VPDavg_seasonal_fullday_observed);
}
//_________________________________________________________________constructor_/
bool Priestley_Taylor_Parameters::get_end()                        modification_
{
   if (CORN::is_approximately(P_T_alpha_fract.in_prescribed_units(),0.0,0.00001)
       && P_T_alpha_fract.is_worse_than(CORN::measured_quality))
   {  // The user did not specify a value
      if (VPDavg_seasonal_fullday_observed.is_valid() &&
          VPDavg_seasonal_fullday_observed.is_better_than(P_T_alpha_fract))
      {  float64 P_T_alpha_fract_ =
            (0.2728 * (VPDavg_seasonal_fullday_observed.in_prescribed_units()) - 0.0007);
         P_T_alpha_fract.force_value_qualified_code
            (P_T_alpha_fract_,CORN::quality_calculated_from(VPDavg_seasonal_fullday_observed.get_quality_code()));
      }
      /*disabled because otherwise unable to determine if user specified value
      else
      {
         float64 P_T_alpha_fract_ = (P_T_constant-1.0); // This was original
         P_T_alpha_fract.force_value_qualified_code
            (P_T_alpha_fract_,CORN::estimated_quality);
      }
      */
   } else // The user specified a value, assume measured quality
      P_T_alpha_fract.modify_quality_code(CORN::measured_quality);

   return true;
}
//_________________________________________________________________constructor_/
/*calculation moved to get end
float32 Priestley_Taylor_Parameters::provide_alpha_fraction()         provision_
{
   P_T_alpha_fract =
         (!CORN::is_approximately<float32>
            (VPDavg_seasonal_fullday_observed,0.0,0.000001))
         ? (0.2728 * (VPDavg_seasonal_fullday_observed) - 0.0007)
         : (P_T_constant-1.0); // This was original
   return P_T_alpha_fract;
}
//______________________________________________________________________________
*/
float32 Priestley_Taylor_Parameters::provide_P_T_constant_adjusted()  provision_
{
   float64 alpha_fract = P_T_alpha_fract.in_prescribed_units(); //170811 provide_alpha_fraction();
   float64 VPDfullday = VPD_fullday->get_kPa();
   float64 PT_const_adjusted  =
   //170814 // Adjust PT constant for aridity                  //020212
   /*170714
      = (!VPD_fullday || VPDfullday <= 1.0)  // only apply correction when fullday_VPD > 1.0
      ? P_T_constant //170808 PT_const_param
      :
   */
      1.0 + alpha_fract * VPDfullday;                                         //170804
//170804      : 1.0 + (PT_const_param - 1.0) * fullday_VPD;


//std::clog << "VPDfd:" << VPD_fullday->get_kPa() << " PTconst:" << PT_const_adjusted << std::endl;


/*NYI


VPDmax_Adjustment =

P-T_Alpha_Fraction =

Calculations:

Estimated_VPDmax = (es(Tmax) - es(Tmin)) / VPDmax_Adjustment

Estimated_Daily_VPD = Estimated_VPDmax * 0.55

Estimated_Daily_VPD
*/


   return PT_const_adjusted;
}
//______________________________________________________________________________
bool Priestley_Taylor_Parameters::setup_structure
(CORN::Data_record &data_rec,bool for_write)                       modification_
{
   data_rec.expect_float32 ("PT_constant",P_T_constant);  // provided to support previous version
   data_rec.expect_float64 ("P_T_alpha_fract",P_T_alpha_fract.mod_amount());
   return true;
}
//______________________________________________________________________________
} // namespace CS
//______________________________________________________________________________
