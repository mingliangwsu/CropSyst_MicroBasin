#include "soil/infiltration_cascade_common.h"
#include "corn/math/moremath.h"
#include "corn/math/compare.h"
#include "common/physics/water_depth.h"
//______________________________________________________________________________
Soil_infiltration_cascade_common::Soil_infiltration_cascade_common
(const Soil_layers_interface      &_soil_layers                                  //140424
,const Soil_hydraulic_properties_interface &_soil_hydraulic_properties           //140423
,Soil_hydrology_interface  &_hydrology
/*//160804
#ifdef OLD_EVAPORATE
//160720 ,modifiable_ Physical::Water_depth           &evaporation_potential_remaining_   //160413
,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining_      //160720
#endif
*/
,CropSyst::Soil_runoff     *_runoff                                              //130308
,CropSyst::Pond            &_pond)                                               //130308
: Soil_infiltration                                                              //130308
   (_soil_layers                                                                 //140424
   ,_soil_hydraulic_properties                                                   //140423
   ,_hydrology
   //160523 #ifndef OLD_EVAP
//160525 moved to Evaporator   ,evaporation_potential_remaining_                                             //160413
   //160523 #endif
   ,_runoff
   ,_pond)
/*//160804
#ifdef OLD_EVAPORATE
, CS::Evaporator_intervals(evaporation_potential_remaining_)                     //160720_160525
#endif
*/
, hydrology(_hydrology)                                                          //060504
{  clear_layer_array64(water_flow);                                              //080208
}
//______________________________________________________________________________
/*//160804
#ifdef OLD_EVAPORATE
float64 Soil_infiltration_cascade_common::evaporate
(
//160523 #ifdef OLD_EVAP
//160523 float64 pot_evap,                                                                //140424,
//160523 #endif
 bool fallow
,bool summer_time
,float64 mulch_cover_fraction)                                     modification_ //100630
{  // This is called for cascade model only.
   // A couple of array index optimizations (Water content is modified)
   float64  perm_wilt_point_1 = soil_hydraulic_properties.get_permanent_wilt_point_volumetric(1);
   float64  perm_wilt_point_2 = soil_hydraulic_properties.get_permanent_wilt_point_volumetric(2);
   float64  thickness_1 = soil_layers.get_thickness_m(1);
   float64  thickness_2 = soil_layers.get_thickness_m(2);
   float64 FC_2 = soil_hydraulic_properties.get_field_capacity_volumetric(2);    //051204
   float64 mid_capacity = perm_wilt_point_2 + ((FC_2 - perm_wilt_point_2) * 0.75);
   //160523 #ifndef OLD_EVAP
   float64 pot_evap = evaporation_potential_remaining.get(0); //daily get_m();                   //160413
   //160523 #endif
   pot_evap *= (1.0-mulch_cover_fraction);                                       //100620
      // mulch here is material other than residue (i.e. plastic cover)

   float64 air_dry_water_content = perm_wilt_point_1 /3.0;
   float64 liquid_water_content_1 = soil_hydrology.get_liquid_water_content_volumetric(1);   //990311
   float64 soil_evaporation_1
      = (liquid_water_content_1 < perm_wilt_point_1)                             //990311
      ? (pot_evap * CORN_sqr((liquid_water_content_1 - air_dry_water_content)    //990311
        / (perm_wilt_point_1 - air_dry_water_content)))
      : pot_evap;
   if ((liquid_water_content_1-soil_evaporation_1/thickness_1)< air_dry_water_content) //990311
       soil_evaporation_1 = (liquid_water_content_1-air_dry_water_content)*thickness_1;
   if (soil_evaporation_1 < 0.0)                                                 //061205
      soil_evaporation_1 = 0;  // Dust mulching  may temporarily have one of the watercontent terms out of sync
   float64 evaporation_loss_volumetric =  - soil_evaporation_1 / thickness_1;  // Negative value   //070814
   soil_hydrology.change_liquid_water_content_by_volumetric(1,evaporation_loss_volumetric);  //070814
   // During fallow periods, the soil is assumed to dry deeper                   //960530
   // into second layer, but not as dry as the first layer.
   float64 soil_evaporation_2 = 0.0;
   if (fallow && summer_time)
   {
      pot_evap -= soil_evaporation_1;
      soil_evaporation_2 = pot_evap;                                             //981209
      // Can dry 25% of available water
      float64 liquid_water_content_2 = soil_hydrology.get_liquid_water_content_volumetric(2); //981209
      soil_evaporation_2 =
         ((liquid_water_content_2 - soil_evaporation_2 / thickness_2) < mid_capacity)
         ? CORN_must_be_greater_or_equal_to((liquid_water_content_2 - mid_capacity) * thickness_2,0.0)
         : pot_evap;
      float64 evaporation_loss_volumetric =  - soil_evaporation_2 / thickness_2;  // Negative value   //070814
      soil_hydrology.change_liquid_water_content_by_volumetric(2,evaporation_loss_volumetric);  //070814
   }
   if (soil_evaporation_2 < 0.0)                                                 //061205
   {  soil_evaporation_2 = 0;   // Normally this shouldn't happen
      // cerr << "Warning negative evaporation in soil layer 2, temporary artifact of dust mulching - automatically corrected" << endl;
   }
   float64 evaporation =  (soil_evaporation_1 + soil_evaporation_2)              //980730
   #ifdef DIRECTED_IRRIGATION
      * (soil_wetting ? soil_wetting->surface_evaporation_area_fraction : 1.0)   //140612
   #else
      ;
   #endif
   //160523 #ifndef OLD_EVAP
//160603    evaporation_potential_remaining.dec_m(evaporation);                           //160412
   //160523 #endif
   return evaporation;
}
#endif
*/
//______________________________________________________________________________
/*//160804
#ifdef OLD_EVAPORATE
//_2016-05-25___________________________________________________________________
float64 Soil_infiltration_cascade_common::evaporate_hour(CORN::Hour hour)   modification_
{  // This is needed because of multiple inheritence
   return CS::Evaporator_intervals::evaporate_hour(hour);
}
//_2016-06-03___________________________________________________________________
#endif
*/


