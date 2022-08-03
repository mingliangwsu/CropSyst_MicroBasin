#include "common/geodesy/geolocation.h"
#include "crop_orchard_common.h"
#include "crop_orchard_Kemanian_Stockle.h"
#include "crop_orchard_Oyarzun_Stockle.h"
#include "crop_param.h"
#include <math.h>
#include "corn/math/compare.h"
//---------------------------------------------------------------------------
#define percent_slope_to_rad(x) asin(x/100)
namespace CropSyst {
//______________________________________________________________________________
Orchard_common::Orchard_common
(const Crop_parameters_struct::Tolerance &_tolerance_parameters
,Interception *_interception
,CropSyst::Crop_parameters_struct::Canopy_characteristics_hedge_row   &_canopy_characteristics //110218
, float64 deg_days_flowering
, float64 deg_days_begin_rapid_fruit_growth)
: Orchard_interface()
, interception(_interception)
, canopy(0)                                                                      //081103
, tolerance_parameters(_tolerance_parameters)                                    //130406
, tree_canopy(_canopy_characteristics,deg_days_flowering,deg_days_begin_rapid_fruit_growth)
{  if (interception) interception->know_tree_canopy(&tree_canopy);
}
//______________________________________________________________________________
float64 Orchard_common::get_solid_canopy_interception()                    const
{  // If there is not interception model then interceptions is not a factor
   return interception ? interception->get_solid_canopy_interception() : 1.0 ;
}
//______________________________________________________________________________
float64 Orchard_common::get_canopy_porosity()                              const
{  return canopy->get_porosity();
}
//_2008-11-03___________________________________________________________________
float64 Orchard_common::get_canopy_shaded_area_GAI()                       const
{  return canopy->get_shaded_area_GAI();
}
//_2008-11-03___________________________________________________________________
float64 Orchard_common::update_solid_canopy_interception()         modification_
{  float64 solid_canopy_interception
   = (interception)
   ?  interception->update_solid_canopy_interception()                           //151027
   : 1.0;
   canopy->know_solid_canopy_interception(solid_canopy_interception);            //081103
   return solid_canopy_interception;
}
//______________________________________________________________________________
Orchard_common::Tree_canopy_extent::Tree_canopy_extent
(CropSyst::Crop_parameters_struct::Canopy_characteristics_hedge_row &canopy_characteristics // 110218
, float64 _deg_days_begin_canopy_development
, float64 _deg_days_end_vegetative_growth)
: deg_days_begin_canopy_development (_deg_days_begin_canopy_development)
, deg_days_end_vegetative_growth    (_deg_days_end_vegetative_growth)
, width  (canopy_characteristics.initial_width  ,canopy_characteristics.final_width  ,deg_days_begin_canopy_development,deg_days_end_vegetative_growth)
, breadth(canopy_characteristics.initial_breadth,canopy_characteristics.final_breadth,deg_days_begin_canopy_development,deg_days_end_vegetative_growth)
, height (canopy_characteristics.initial_height ,canopy_characteristics.final_height ,deg_days_begin_canopy_development,deg_days_end_vegetative_growth)
{
}
//______________________________________________________________________________
Orchard_common::Tree_canopy_extent::Dimension::Dimension
( float64 _initial_size
, float64 _final_size
, float64 &_deg_days_begin_canopy_development
, float64 &_deg_days_end_vegetative_growth)
: current            (_initial_size)
, initial            (_initial_size)
, final              (_final_size)
, deg_days_begin_canopy_development (_deg_days_begin_canopy_development)
, deg_days_end_vegetative_growth    (_deg_days_end_vegetative_growth)
{ }
//______________________________________________________________________________
float64 Orchard_common::Tree_canopy_extent::Dimension::expand(float64 deg_days_today) modification_
{
   if ((deg_days_today > deg_days_begin_canopy_development) && (deg_days_today < deg_days_end_vegetative_growth))  //071117_
   {  float64 change =                                                           //000717
        ((final - initial) *                                                     //000717
          (deg_days_today - deg_days_begin_canopy_development) /   // When leaf starts //000717
          (deg_days_end_vegetative_growth - deg_days_begin_canopy_development)); //000717
      current = initial + change;                                                //071117
   } // else keep current                                                       //071117
   return current;                                                               //000717
}
//______________________________________________________________________________
void Orchard_common::expand_canopy
(float64 deg_days_today)
{  tree_canopy.expand(deg_days_today);
}
//______________________________________________________________________________
void Orchard_common::Tree_canopy_extent::expand(float64 deg_days_today) modification_
{  width  .expand(deg_days_today);
   breadth.expand(deg_days_today);  // was col_width
   height .expand(deg_days_today);
}
//______________________________________________________________________________
void Orchard_common::Tree_canopy_extent::set_deg_days_begin_canopy_development(float64 _deg_days_begin_canopy_development)
{  deg_days_begin_canopy_development = _deg_days_begin_canopy_development;
}
//_2007-11-21___________________________________________________________________
void Orchard_common::set_deg_days_begin_canopy_development(float64 _deg_days_begin_canopy_development)
{  tree_canopy. set_deg_days_begin_canopy_development(_deg_days_begin_canopy_development);
}
//_2007-11-21____________________________set_deg_days_begin_canopy_development_/
Orchard_common::Interception::Interception
(CropSyst::Crop_parameters_struct::Layout &layout_                               //110218
,CropSyst::Crop_parameters_struct::Canopy_characteristics_hedge_row &canopy_characteristics_  //110218
,float64          slope_percent_
,float64          slope_aspect_N0_E90_degrees_
,const Sun_days   &sun_days_         // Provided by weather/meteorology
,const float64    &fract_cloud_cover_
,const CORN::Date_const &today_)
: layout                (layout_)
, canopy_characteristics(canopy_characteristics_)
, sun_days              (sun_days_)
, fract_cloud_cover     (fract_cloud_cover_)                                     //151027
, today                 (today_)                                                 //151027
{
   slope_radians = percent_slope_to_rad(slope_percent_);
   row_azimuth_radians =deg_to_rad(convert_aspect_from_0_north_with_east_90_to_0_south_with_east_90(layout_.row_azimuth_true_north_deg));  //071117
   // We need to convert Aspect_N0_E90_degrees
   // to the orientation use by this model.
   // Armen confirmed that this works for southern hemisphere                    //020614
   // When negative is used for southern hemisphere.
   float32 slope_aspect_S0_E90_degrees = convert_aspect_from_0_north_with_east_90_to_0_south_with_east_90(slope_aspect_N0_E90_degrees_);   //020612
   slope_aspect_from_south_radians = deg_to_rad(slope_aspect_S0_E90_degrees);
}
//______________________________________________________________________________
float64 Orchard_common::Interception
::convert_aspect_from_0_north_with_east_90_to_0_south_with_east_90(float64 aspect_N0_E90_degrees) const
{
   float32 aspect_S0_E90_degrees =                                               //020612
      (aspect_N0_E90_degrees < 180.0)   ? (180.0 - aspect_N0_E90_degrees)
   /* (aspect_N0_E90_degrees >=180.0)*/ : (540.0 - aspect_N0_E90_degrees);
   return aspect_S0_E90_degrees;
}
//______________________________________________________________________________
#ifdef NYN
bool Orchard_common::process_day()                               modification_
{
   expand_dimensions()
   if (orchard_interception) orchard_interception->update_day();
}
#endif
//______________________________________________________________________________
Orchard_common::Canopy_growth_architectural::Canopy_growth_architectural
(
#ifdef OLD_PROVIDE_CANOPY
 const CropSyst::Crop_parameters       &crop_parameters_      // Will be owned by this crop object
,const /*180614 modifiable_*/ CropSyst::Crop_parameters_struct::Canopy_growth_cover_based &parameters_
,const Thermal_time_immutable          &thermal_time_                            //151106
,Residues_interface                    *residues_                                //060816
,Crop_nitrogen_interface               *nitrogen_                                //060816
,const CropSyst::Phenology_interface   &phenology_
,const float64                         &ref_water_stress_index_yesterday_
,const float64                         &water_canopy_expansion_factor_
,Crop_CO2_response                     *CO2_response_
#else
 const Canopy_growth_interface         &canopy_growth_
,float64                                kc_
#endif
)                           //080728
/*  180615
Orchard_common::Canopy_growth::Canopy_growth
(const CropSyst::Crop_parameters       &crop_parameters_      // Will be owned by this crop object
,const  CropSyst::Crop_parameters_struct::Canopy_growth_cover_based &parameters_
,const Thermal_time_immutable          &thermal_time_                            //151106
,Residues_interface                    *residues_                                //060816
,Crop_nitrogen_interface               *nitrogen_                                //060816
,const CropSyst::Phenology_interface   &phenology_
,const float64                         &ref_water_stress_index_yesterday_
,const float64                         &water_canopy_expansion_factor_
,Crop_CO2_response                     *CO2_response_
)                           //080728
*/
/*
(const CropSyst::Crop_parameters                       &_crop_parameters      // Will be owned by this crop object
,const CropSyst::Crop_parameters_struct::Canopy_growth_LAI_based &_parameters
,const Thermal_time_immutable          &_thermal_time                            //151106
,Residues_interface                    *_residues                                //060816
,Crop_nitrogen_interface               *_nitrogen                                //060816
,float64                               &_reported_peak_LAI                       //080725
,Crop_CO2_response                     *_CO2_response
)                           //080728
*/
#ifdef OLD_PROVIDE_CANOPY
: CropSyst::Canopy_growth_cover_based                                //180614
(
 crop_parameters_      // Will be owned by this crop object
,parameters_
,thermal_time_
,residues_
,nitrogen_
,phenology_
, ref_water_stress_index_yesterday_
,water_canopy_expansion_factor_
#ifdef CO2_CHANGE
,CO2_response_
#endif
)
/*180614
: CropSyst::Canopy_growth_leaf_area_index_based
   (_crop_parameters      // Will be owned by this crop object
   ,_parameters
   ,_thermal_time
   ,_residues                                                                    //060816
   ,_nitrogen                                                                    //060816
   ,_reported_peak_LAI                                                           //080725
   ,_CO2_response                                                                //080728
   ,false // is not a continuous grass                                           //081108
   )                                                                             //081108
 */                                                                               //081108
#else
: canopy_growth                                                 (canopy_growth_) //180618
, kc                                                                       (kc_) //180618
#endif
, shaded_area_GAI                                                          (0.0) //081103
, porosity                                                                 (0.0) //081103
{}
//______________________________________________________________________________
float64 Orchard_common::Canopy_growth_architectural
//180614 Canopy_growth
::calc_fract_cover
(float64 xAI    // Either LAI or  GAI
,bool photosynthetic_active_rad_based
,bool use_clumping_factor
,bool record_shading_porosity_interception                                       //081104
) const
{
   float64 kc_local =
    #ifdef OLD_PROVIDE_CANOPY
      #if (CROPSYST_VERSION == 4)
         crop_parameters.param_kc();
      #else
         crop_parameters.morphology.kc;                                          //130406
      #endif
    #else
      kc;                                                                        //180618
    #endif
    //  Correct kc parameter which is total radiation based.                     //011022
    //  Kc based on photosynthetic active radiation is needed
   if (photosynthetic_active_rad_based)                                          //011108
      kc_local = std::min<float64>(kc_local * 1.4,0.9);                          //000716
   // kc will be total radiation based entered in the parameter editors.
   float64 local_shaded_area_GAI = (xAI / solid_canopy_interception);
      // Eventually move this to orchard submodel //081020_
   float64 local_porosity =   exp(-kc_local * local_shaded_area_GAI);            //071121
   if (record_shading_porosity_interception)                                     //081104
   {  shaded_area_GAI  = local_shaded_area_GAI;                                  //081104
      porosity         = local_porosity;                                         //081104
   }
   float64 canopy_interception  =
      (xAI > 0.00001)                                                            //071121
      ? (1.0 - local_porosity)                                                   //071121
      : 0.0;
   float64 result_fract_canopy_cover =  solid_canopy_interception *canopy_interception;
      // canopy_porosity really only applies to fruit canopy since solid_canopy_interception in 1.0 for field crops //071121_
   return  result_fract_canopy_cover;                                            //071121
}
//_2008-10-22_________________________________________________calc_fract_cover_/
#ifdef OLD_PROVIDE_CANOPY
Canopy_growth_interface *Orchard_common::provide_canopy
(const CropSyst::Crop_parameters       &crop_parameters_  // Will be owned by this crop object
,const CropSyst::Crop_parameters_struct::Canopy_growth_cover_based &parameters_
,const Thermal_time_immutable          &thermal_time_
,Residues_interface                    *residues_
,Crop_nitrogen_interface               *nitrogen_
,const CropSyst::Phenology_interface   &phenology_
,const float64                         &ref_water_stress_index_yesterday_
,const float64                         &water_canopy_expansion_factor_
,CropSyst::Crop_CO2_response           *CO2_response_)                provision_
{  if (!canopy)
   {    canopy = new Orchard_common::Canopy_growth_architectural
         //180614 Canopy_growth
         (crop_parameters_      // Will be owned by this crop object
         ,parameters_
         ,thermal_time_
         ,residues_
         ,nitrogen_
         ,phenology_
         ,ref_water_stress_index_yesterday_
         ,water_canopy_expansion_factor_
         ,CO2_response_  );
    }
    return canopy;
}
//_2016-06-14___________________________________________________________________
/*180614 now using canopy curve model
Canopy_growth_interface *Orchard_common::provide_canopy
(const CropSyst::Crop_parameters &_crop_parameters  // Will be owned by this crop object
,const CropSyst::Crop_parameters_struct::Canopy_growth_LAI_based &_parameters
,const Thermal_time_immutable       &_thermal_time                               //151106
,Residues_interface                 *_residues                                   //060816
,Crop_nitrogen_interface            *_nitrogen                                   //060816
,float64 &_reported_peak_LAI                                                     //080725
,CropSyst::Crop_CO2_response        *_CO2_response)                   provision_ //080728
{  if (!canopy)
   {    canopy = new Orchard_common::Canopy_growth
         (_crop_parameters      // Will be owned by this crop object
         ,_parameters
         ,_thermal_time
         ,_residues                                                              //060816
         ,_nitrogen                                                              //060816
         ,_reported_peak_LAI                                                     //080725
         ,_CO2_response  );                                                      //080728
    }
    return canopy;
}
//_2008-11-03___________________________________________________________________
*/
#endif
//______________________________________________________________________________
float64 Orchard_common::calc_freezing_damage(float64 min_temperature)   calculation_ //150825
{
   float64 fract_fruit_reduction_due_to_freezing = 0.0;
#if (CROPSYST_VERSION >= 5)
   float64 fruit_damage_cold_temp = tolerance_parameters.temperature_cold_fruit_damage;//150914
   float64 fruit_lethal_cold_temp = tolerance_parameters.temperature_cold_fruit_lethal;//150914
   //150914   float64 fruit_damage_cold_temp = hardiness_parameters.fruit_damage_cold_temp;
   //150914   float64 fruit_lethal_cold_temp = hardiness_parameters.fruit_lethal_cold_temp;
   static const float64 damage_curve_adj = 2.0; // Could make this a parameter. //081103
   fract_fruit_reduction_due_to_freezing =
   // For fruit crops we do not kill  the plant
   // (it would have to be really cold (I.e. -30 for pomes))
   // but we do drop the leaves.
   // We also reduce the maximum potential fruit load
   // (accounting for the loss of flowers and early fruit growth).
   std::min<float64>                                                       //081103
      (1.0                                                                 //081103
      ,(min_temperature < fruit_damage_cold_temp)                          //081103
       ?pow((fruit_damage_cold_temp - min_temperature)                     //081103
         /(fruit_damage_cold_temp - fruit_lethal_cold_temp),damage_curve_adj) //081103
       :0.0);                                                              //081103
   fract_fruit_reduction_due_to_freezing
      = CORN::must_be_between<float64>(fract_fruit_reduction_due_to_freezing,0.0,1.0);
   // respond_to_freezing_damage(fract_fruit_reduction_due_to_freezing);      //081103
   // Note may want to move respond_to_freezing_damage method to this class
#endif
   return fract_fruit_reduction_due_to_freezing;
}
//_1212-01-17___________________________________________________________________
} // namespace CropSyst

