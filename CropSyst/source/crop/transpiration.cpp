#include <math.h>
#include "corn/math/compare.hpp"
#include "cmmnopts.h"
#include "crop/crop_param.h"
#include "options.h"
#include "common/soil/txtrhydr.h"
#include "crop/transpiration.h"
#include <assert.h>
#include "soil/soil_interface.h"
#include "soil/hydrology_interface.h"
#include "soil/salinity_profile.h"
#include "corn/measure/measures.h"
#include "CS_suite/observation/CS_inspector.h"
#include "csvc.h"
#define CSVP_crop_base_transp_uptake_act                           0x21FFF9

//______________________________________________________________________________
Crop_transpiration_2::Crop_transpiration_2
(CropSyst::Crop_parameters_struct::Transpiration &parameters_
,const Soil_interface   *soil_                                                   //160415
,float64 param_salinity_osmotic_pot_50_                                          //160414
,float64 param_salinity_salt_tolerance_P_                                        //160415
,float64 param_dry_soil_root_activity_coef_                                      //170518
,float64 param_saturated_soil_root_activity_coef_)                               //170518
: Crop_transpiration()
, parameters(parameters_)                                                        //120724
, soil(soil_)
, soil_salinity(soil_->ref_salinity())                                           //160415
, soil_hydrology(soil->ref_hydrology())                                          //170501
, ref_soil_water_pot_at_FC(soil_->ref_hydraulic_properties()->ref_soil_water_pot_at_FC()) //170501
, param_salinity_osmotic_pot_50  (param_salinity_osmotic_pot_50_)                //160415
, param_salinity_salt_tolerance_P(param_salinity_salt_tolerance_P_)              //160415
#ifdef DIRECTED_IRRIGATION
, soil_wetting    (0)                                                            //141103
#endif
, leaf_water_pot  (0)                                                            //080228
, uptake_act_m    (0)                                                            //160420
, dry_soil_root_activity_coef(param_dry_soil_root_activity_coef_)                //170518
, saturated_soil_root_activity_coef(param_saturated_soil_root_activity_coef_)    //170518
{  clear_sublayer_array(Root_Activity_Factor);
   clear_sublayer_array(active_fract_root_length_output_only);
}
//_2004-03-31___________________________________________________________________
float64 Crop_transpiration_2::calc_transpiration
(float64 N_limited_pot_transpiration_CO2adjusted_m             // pot_ET_m       //050405
   // would be CO2 adjusted if CO2 enabled
,float64 yesterday_fract_green_canopy_solrad_interception_mm    // fract_green_canopy_cover
,float64 param_full_cover_crop_water_uptake_max_mm                               //091208
,modifiable_ float64 &interception_canopy_m                                      //160414
,const soil_sublayer_array_64(fract_root_length_)
,soil_sublayer_array_64(water_uptake_m)            // returned   (water uptake demand)
,float64 CO2_transpiration_adjustment_factor)                              const //160418
{
   float64 unconsumed_interception_canopy_m = interception_canopy_m;           //160414RLN
   nat8 soil_num_sublayers = soil ?soil->ref_layers()->get_number_layers():0;    //051028
   for (nat8  sublayer = 1 ; sublayer <= soil_num_sublayers ; sublayer++)        //050331
      // This is setup only for output
      active_fract_root_length_output_only[sublayer] = fract_root_length_ ? fract_root_length_[sublayer] : 0; //050331
   // This is used only for output, it is simply the current total_fract_root_length
   //_______//    Define soil water potential at field capacity

//std::cout << "MWU:" << param_full_cover_crop_water_uptake_max << std::endl;
//soil_sublayer_array_64( wu_mm); clear_sublayer_array( wu_mm);

   // Calculate potential transpiration rate (kg/m2/d = mm/d)
   // VB code does not have N limitations/*_______*/    float64 Pot_Transp_mm = pot_ET_mm * fract_green_canopy_interception_solrad;

   float64 interception_for_transpiration_m = 0.0;
   if (N_limited_pot_transpiration_CO2adjusted_m > interception_canopy_m)
   {  N_limited_pot_transpiration_CO2adjusted_m -= interception_canopy_m;
      interception_for_transpiration_m = interception_canopy_m;
      unconsumed_interception_canopy_m = 0;
   } else
   {  interception_for_transpiration_m = N_limited_pot_transpiration_CO2adjusted_m;
      if (N_limited_pot_transpiration_CO2adjusted_m > unconsumed_interception_canopy_m)
            unconsumed_interception_canopy_m = 0.0;
      else  unconsumed_interception_canopy_m -= N_limited_pot_transpiration_CO2adjusted_m;
      N_limited_pot_transpiration_CO2adjusted_m = 0;
   }
   float64 CO2_adjusted_Potential_Transpiration_m = N_limited_pot_transpiration_CO2adjusted_m ; //050405_130506
   float64 CO2_adjusted_Potential_Transpiration_mm = m_to_mm(CO2_adjusted_Potential_Transpiration_m) ; //050405_130506

   // Calculate crop maximum water uptake rate (kg/m2/d = mm/d)
   float64 pot_crop_water_uptake_mm                                              //160318
      = param_full_cover_crop_water_uptake_max_mm
      * yesterday_fract_green_canopy_solrad_interception_mm;
   float64 CO2_Adjusted_Pot_Crop_Water_Uptake_mm // atmospheric demand
      = pot_crop_water_uptake_mm                                                 //160318
      * CO2_transpiration_adjustment_factor;                                     //160314

   // Calculate maximum crop transpiration rate (kg/m2/d = mm/d)
   // Water intercepted by the canopy is substracted from CO2_adjusted_Potential_Transpiration //160318
   //    because intecepted water reduces the need for water uptake
   float64 max_crop_water_uptake_mm = std::min<float64>                          //160313
      ((CO2_adjusted_Potential_Transpiration_mm)                                 //160318COS
        // demand from atmosphere is reduced by canopy storage of water
      ,CO2_Adjusted_Pot_Crop_Water_Uptake_mm);
   float64 Act_Transp_m = 0.0;
   uptake_act_m =
      (max_crop_water_uptake_mm > 0)
      ? uptake_actual
         (soil_num_sublayers
         ,pot_crop_water_uptake_mm
         ,max_crop_water_uptake_mm
         ,fract_root_length_
         ,water_uptake_m)                                                        //160415
      : 0.0;
    Act_Transp_m = uptake_act_m + (interception_for_transpiration_m);            //160415RLN
   interception_canopy_m = unconsumed_interception_canopy_m;                     //160825_160414RLN
   return Act_Transp_m;
}
//______________________________________________________________________________
float64 Crop_transpiration_2::uptake_actual
(nat8  soil_num_sublayers
,float64 pot_crop_water_uptake_mm
,float64 max_crop_water_uptake_mm
,const soil_sublayer_array_64(fract_root_length_)
,soil_sublayer_array_64(water_uptake_m) ) /* returned */                         const
{
   float64 parameters_LWP_stomatal_closure = parameters.LWP_stomatal_closure;    //170518
   float64 parameters_LWP_wilt_point       = parameters.LWP_wilt_point;          //170518

   /*
//debug only
parameters_LWP_wilt_point = -1800;
parameters_LWP_stomatal_closure = -1300;
pot_crop_water_uptake_mm = 7;
max_crop_water_uptake_mm = 6;
*/

//soil_sublayer_array_64(fract_root_length);


   if (!soil) return pot_crop_water_uptake_mm; // This is a special case when running with no soil
   float64 SWP_for_max_plant_hydraul_cond = 0.0;
      // Soil Water Potential for maximum plant hydraulic conductance
      // assumes (max?) potential uptake takes plax at SWP=0
   // Next 4 lines used to be done by caller
   soil_layer_array64(soil_water_pot); clear_layer_array64(soil_water_pot);      //080125
   //170501 now member const Soil_hydrology_interface *soil_hydrology = soil->ref_hydrology();       //160412_080125
   for (nat8 layer = 1; layer <= soil_num_sublayers; layer++)                    //160603LML_080125
   {
      soil_water_pot[layer] = soil_hydrology->get_water_potential(layer);        //080125
//   fract_root_length[layer] = fract_root_length_[layer];


   }


//debug only
/*
   fract_root_length[1] = 0.189999998;
   fract_root_length[2] = 0.17000000;
   fract_root_length[3] = 0.150000006;
   fract_root_length[4] = 0.13000001;
   fract_root_length[5] = 0.110000007;
   fract_root_length[6] = 0.089999996;
   fract_root_length[7] = 0.069999993;
   fract_root_length[8] = 0.049999986;
   fract_root_length[9] = 0.029999981;
   fract_root_length[10] = 0.009999976;
*/

   #ifdef DIRECTED_IRRIGATION
   if (soil_wetting)
      max_crop_transpiration_CO2adjusted_mm                                      //160314
      /= soil_wetting->profile_volume_fraction;                                  //140605
   #endif
   // Calculate plant hydraulic conductivity ((kg^2)/(m2-J-d)

   // The plant hydraulic conductance,
   //  the capacity of the vascular system to conduct water,
   // is not affected by CO2-induced partial stomatal closure.                   //160318COS

   // Conductances (cond)
   float64 plant_hydraulic_cond =
      (pot_crop_water_uptake_mm                                                  //160318_160314
       / (SWP_for_max_plant_hydraul_cond - parameters_LWP_stomatal_closure));    //120724
       // Excel version has Plant_Hydraulic_Conductance_Factor which is 1.0
   // Adjust plant hydraulic conductance based on soil dryness

   float64 root_hydraulic_cond = plant_hydraulic_cond / 0.65;
   float64 top_hydraulic_cond = plant_hydraulic_cond / 0.35;
   float64 root_cond_adj = 0;
   soil_sublayer_array_64(layer_root_cond_adj); clear_sublayer_array(layer_root_cond_adj);
   soil_sublayer_array_64(layer_root_hydraulic_cond);
     clear_sublayer_array(layer_root_hydraulic_cond);
   //  This transpiration will now allow roots in layer 1. (previous version did not)

   for (nat8  sublayer = 1 ; sublayer <= soil_num_sublayers ; sublayer++)
   {
      float64 soil_WP_layer = soil_water_pot[sublayer];                          //051022
      float64 SWP_at_FC =
#ifdef VIC_CROPSYST_VERSION
              soil->ref_hydraulic_properties()->get_water_pot_at_FC(sublayer);   //180627LML
#else
              ref_soil_water_pot_at_FC[sublayer];
#endif


      /*170508 moved below
      float64 root_activity_factor_dry_sl
         = ((soil_WP_layer < parameters.LWP_wilt_point) ? 0 : 1.0)               //170413_150828LML
         - pow(((soil_WP_layer - SWP_FC)
            / (parameters.LWP_wilt_point - SWP_FC)),8.0);     //  050421 claudio changed to ^8  was ^4
      */
//170508       float64 root_activity_factor_wet_sl = 1.0;

      float64 root_activity_factor_sl = 1.0;
      if (soil_WP_layer <= SWP_at_FC) // less negative (dry or normal case)
      {  // When water content gets near PWP the layer becomes inactive.
         // the RAF is adjusted to account for this.
         root_activity_factor_sl
         = ((soil_WP_layer < parameters_LWP_wilt_point) ? 0 : 1.0)               //170413_150828LML
           - pow(((soil_WP_layer - SWP_at_FC)
                  / (parameters_LWP_wilt_point - SWP_at_FC)),dry_soil_root_activity_coef); // was 0.8
               //  050421 claudio changed to ^8  was ^4
      } else // wet case
      {  // In saturated conditions RAF is
      /*170623 COS
         root_activity_factor_sl
         = 1.0 - pow((soil_WP_layer-SWP_at_FC)/(0-SWP_at_FC),saturated_soil_root_activity_coef);
         static const float64 RAF_wet_minimum = 0.2;
            // 0.2 is arbitrary, representing max effect of saturated soil
         root_activity_factor_sl =CORN::must_be_greater_or_equal_to<float64>
            (root_activity_factor_sl,RAF_wet_minimum);
      */
      }
      root_activity_factor_sl = CORN::must_be_between<float64>(root_activity_factor_sl,0.0,1.0);
      float64 salt_stress_function
            = soil_salinity
            ? soil_salinity->get_salt_stress_function
               (sublayer
               // this could be the same as V5, I just haven't checked it yet
               ,param_salinity_osmotic_pot_50                                    //160415
               ,param_salinity_salt_tolerance_P)                                 //160415
            : 1.0;
       float64 salinity_reduction_factor_sl = // Always between 0 and 1
            1.0 / salt_stress_function; // (reduces conductance)
       layer_root_cond_adj[sublayer] = root_activity_factor_sl
         * fract_root_length_[sublayer] * salinity_reduction_factor_sl;
       root_cond_adj += layer_root_cond_adj[sublayer];
       layer_root_hydraulic_cond[sublayer]
       = root_hydraulic_cond * layer_root_cond_adj[sublayer];
   } // for sublayer
   uptake_act_m = 0;                                                             //160414 was total_water_uptake_m
   soil_sublayer_array_64(layer_plant_hydraulic_cond);  // Units ???
     clear_sublayer_array(layer_plant_hydraulic_cond);  // clear to 0
   if (root_cond_adj > 0.00001)                                                  //050331
   {  for (nat8  sublayer = 1 ; sublayer <= soil_num_sublayers ; sublayer++)     //050331
      {  float64 top_hydraulic_cond_sublayer  // VB Layer_Top_Hydraulic_Conductance
         = top_hydraulic_cond * layer_root_cond_adj[sublayer] / root_cond_adj;
         float64 root_plus_top_hydraulic_cond_SL
         = (layer_root_hydraulic_cond[sublayer] + top_hydraulic_cond_sublayer);
         layer_plant_hydraulic_cond[sublayer]
         = ((layer_root_cond_adj[sublayer] > 0) && (root_plus_top_hydraulic_cond_SL > 0.0))
         ? layer_root_hydraulic_cond[sublayer] * top_hydraulic_cond_sublayer
         / root_plus_top_hydraulic_cond_SL
         : 0.0;
      } // for sublayer
      root_hydraulic_cond *= root_cond_adj;
      float64 root_plus_top_hydraulic_cond
      = (root_hydraulic_cond + top_hydraulic_cond);
      plant_hydraulic_cond
      = (root_plus_top_hydraulic_cond > 0.0)                                     //050421
      ?  (root_hydraulic_cond * top_hydraulic_cond)
         / root_plus_top_hydraulic_cond                                          //050421
      : 0.0;                                                                     //050421
   // Calculate average soil water potential
   float64 soil_avg_water_pot = 0.0;      //VB   Average_Soil_WP = 0
   for (nat8  sublayer = 1 ; sublayer <= soil_num_sublayers ; sublayer++)
   {  float64 soil_osmotic_pot_sol_sl =
         soil_salinity ? soil_salinity->get_osmotic_pot_solution(sublayer)       //160415
         : 0.0;
      float64 soil_WP_layer = soil_water_pot[sublayer];                          //051022
      soil_avg_water_pot += (soil_WP_layer + soil_osmotic_pot_sol_sl )
         * layer_root_cond_adj[sublayer] / root_cond_adj;
   }
   if (plant_hydraulic_cond > 0.0)
   {  leaf_water_pot              // VB Leaf_Water_Pot   (actually local, but recorded for output)
      = calc_leaf_water_potential
      (plant_hydraulic_cond
      ,parameters_LWP_stomatal_closure                                           // VB was LeafWaterPot_OnsetofStress
      ,parameters_LWP_wilt_point                                                       // VB was LeafWaterPot_Wilt
      ,max_crop_water_uptake_mm                                                  //160318RLN
      ,soil_avg_water_pot);                                                      // VB was Average_Soil_WP
      // Reduce transpiration when leaf water potential is less than
      // the critical leaf water potential at the onset of stomatal closure
      float64 transpiration_ratio = 1.0;        // VB transpiration_ratio           //050316
      if ((leaf_water_pot < parameters_LWP_stomatal_closure)
          && (leaf_water_pot > parameters_LWP_wilt_point)
          && (!CORN::is_approximately<float64>(max_crop_water_uptake_mm,0.0,0.00000007)))
      {  // onset of stress
      // Reduce transpiration when leaf water potential is less than
      // the critical leaf water potential at the onset of stomatal closure.
      // Transpiration ratio is less than 1 when
      // the atmospheric evaporative demand (potential transpiration),
      // corrected by a nitrogen stress factor, is greater than
      // the maximum ability of the crop to uptake water from a well-watered soil.
         float64 Attainable_Transp_mm = max_crop_water_uptake_mm *
              (leaf_water_pot - parameters_LWP_wilt_point)
            / (parameters_LWP_stomatal_closure - parameters_LWP_wilt_point);
           transpiration_ratio = Attainable_Transp_mm / max_crop_water_uptake_mm;   //160316
      // RLN: I think this is the same as Potential_Crop_transpiration_2 * Top_Nitrogen_Stress_Factor
      }
      else if (leaf_water_pot < parameters_LWP_wilt_point)
      {
          //Attainable_Transp_mm = 0.0
          transpiration_ratio = 0.0;
      }
      //  else transpiration_ratio remains 1.0 and  Attainable_Transp remains as max_crop_transpiration_2
      //  Calculate crop water uptake (kg/m2/d = mm/d)
      for (nat8  sublayer = 1 ; sublayer <= soil_num_sublayers ; sublayer++)
      {     float64 soil_WP_layer = soil_water_pot[sublayer];
         // Check with Claudio, this was in CropSyst 3  probably should he here too.
         float64 soil_osmotic_pot_sol =                                          //981208
            soil_salinity ? soil_salinity->get_osmotic_pot_solution(sublayer)    //160415
            : 0.0;
         float64 water_uptake_sublayer_mm  = 0; //  (kg/m2/d = mm/d)  (VB Soil_Water_Extracted) //050331
         water_uptake_sublayer_mm =
         layer_plant_hydraulic_cond[sublayer]                                    //050331
            * (soil_WP_layer + soil_osmotic_pot_sol - leaf_water_pot)            //050331
            * transpiration_ratio;
            // layer_plant_hydraulic_cond can be negative dont limit to 0 //151014
         float64 water_uptake_sublayer_m = mm_to_m(water_uptake_sublayer_mm);    //050331
         // C++ Soil water content is not adjusted here.
         //     The extracted amount is passed to the soil by the caller
         water_uptake_m[sublayer] = water_uptake_sublayer_m;                     //050331
         uptake_act_m += water_uptake_sublayer_m;                                //050331
      } // each sublayer
   }  // else Plant_Hydraulic_Conductivity <= 0.0
      // so water_uptake is 0 for all layers (already initialized to 0.0).
   } // else no cannot calculate uptake yet because no fract root length        //050331

//std::clog << "ratio:" << m_to_mm(uptake_act_m) /  max_crop_water_uptake_mm << std::endl;

   return uptake_act_m;
}
//_2016-04-15___________________________________________________uptake_actual__/
float64 Crop_transpiration_2::calc_leaf_water_potential
(  float64 plant_hydraulic_cond              // conductance
,  float64 leaf_water_pot_onset_of_stress_
,  float64 leaf_water_pot_wilt_
,  float64 Max_Crop_Water_Uptake
,  float64 soil_avg_water_pot)                                             const
{
   float64 leaf_water_pot = soil_avg_water_pot
      - Max_Crop_Water_Uptake
      / plant_hydraulic_cond;
   if (leaf_water_pot < leaf_water_pot_onset_of_stress_ )
       leaf_water_pot
      = (plant_hydraulic_cond * soil_avg_water_pot
         * (leaf_water_pot_onset_of_stress_  - leaf_water_pot_wilt_)
        + leaf_water_pot_wilt_ * Max_Crop_Water_Uptake)
      / (plant_hydraulic_cond
           *  (leaf_water_pot_onset_of_stress_  - leaf_water_pot_wilt_)
         + Max_Crop_Water_Uptake);
   leaf_water_pot = CORN::must_be_greater_or_equal_to<float64>
      (leaf_water_pot,leaf_water_pot_wilt_);
      // stomates completely close so no potential for uptake
   #ifndef VIC_CROPSYST_VERSION
   if (leaf_water_pot < leaf_water_pot_wilt_)
       leaf_water_pot = leaf_water_pot_wilt_;
   #endif
   return leaf_water_pot;
}
//_2001-07-23___________________________________________________________________
RENDER_INSPECTORS_DEFINITION(Crop_transpiration_2)
{  // sharing parent's emanator
   inspectors.append(new CS::Inspector_scalar(leaf_water_pot ,UC_J_per_kg,*context,"leaf/water_potential"    ,value_statistic  ,CSVP_crop_base_leaf_water_pot));
   inspectors.append(new CS::Inspector_scalar(uptake_act_m   ,UC_m       ,*context,"transpiration/uptake/act",value_statistic/*171031 sum_statistic*/    ,CSVP_crop_base_transp_uptake_act/*171222CSVC_crop_base_transp_uptake_act_m*/));
   return 0;
}
//_2016-06-27___________________________________________________________________


