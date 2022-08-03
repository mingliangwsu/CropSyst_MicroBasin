#include "common/weather/weather_provider.h"
#include "weather/parameter/WC_ET_reference.h"
#include "biometeorology/aerodynamics.h"
#include "biometeorology/ET_reference.h"
//______________________________________________________________________________
ET_Reference_calculator::ET_Reference_calculator
(float32           elevation_                                                    //150617
,const float64    &day_length_hours_today_                                       //150627
,Weather_provider &weather_)
: ET_Reference()
, ET_reference_models
   (new Reference_evapotranspiration_model_set
      (elevation_
      ,day_length_hours_today_
      ,weather_
      ,true // may need to make this a parameter bool Priestley_Taylor_constant_is_adjusted_for_VPD = true
      ))
{}
//______________________________________________________________________________
const CORN::Quality &ET_Reference_calculator::update()            rectification_
{  static CORN::Quality_clad selected_quality;

   //double et_pm,et_Hargreaves,et_pt;

   float64 ET_ref_selected = 0.0;
   ET_reference_models->start_day();
   ET_ref_selected  =ET_reference_models->
//VB not yet validated   #if (CS_VERSION==4)
      provide_Penman_Monteith_CropSyst4(selected_quality);
/*160731 VB not yet validated
   #else
      provide_Penman_Monteith_CropSyst_VB(selected_quality);
   #endif
*/
   //et_pm = ET_ref_selected;

   CORN::Quality_clad measure_quality(get_quality());                            //150121
   if (!selected_quality.is_valid()) {
      ET_ref_selected = ET_reference_models->provide_Hargreaves_adjusted
         (measure_quality);                                                      //150120
      //et_Hargreaves = ET_ref_selected;
   }
   if (!selected_quality.is_valid()) {
      ET_ref_selected = ET_reference_models->provide_Priestly_Taylor
         (measure_quality);                                                      //150120
      //et_pt = ET_ref_selected;
   }
   selected_quality.assume_code(CORN::calculated_quality);                       //170516brc
   set_mm(ET_ref_selected,selected_quality);
   
   //std::clog << "et_pm:" << et_pm
   //          << "\tet_Hargreaves:" << et_Hargreaves
   //          << "\tet_pt:" << et_pt
   //          << "\tET_ref_selected:" << ET_ref_selected
   //          << std::endl;
   
   
   return selected_quality;                                                      //160731_150915
}
//______________________________________________________________________________
const Slope_saturated_vapor_pressure_plus_psychrometric_resistance &
ET_Reference_calculator::ref_slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference() const
{  return
   ET_reference_models->
   ref_slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference();
}
//_2016-07-31___________________________________________________________________
const float64 &ET_Reference_calculator::ref_aerodynamic_resistance_ref_plants()     const
{
   return ET_reference_models->ref_aerodynamic_resistance_ref_plants();
}
//_2016-07-31___________________________________________________________________
