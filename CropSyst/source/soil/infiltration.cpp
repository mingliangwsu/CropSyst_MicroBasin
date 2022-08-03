#include "soil/infiltration.h"
#include <math.h>
#include "corn/math/moremath.h"
#include "physics/standard_constants.h"
#include "corn/chronometry/time_types.hpp"
#include "CS_suite/observation/CS_inspector.h"
#include "csvc.h"
//______________________________________________________________________________
Soil_infiltration::Soil_infiltration
(const Soil_layers_interface                 &_soil_layers                       //140424
,const Soil_hydraulic_properties_interface   &_soil_hydraulic_properties         //140423
,Soil_hydrology_interface                    &_soil_hydrology
,CropSyst::Soil_runoff                       *_runoff                            //130308
,CropSyst::Pond                              &_pond)                             //131001
: Soil_infiltration_nominal()
, soil_layers              (_soil_layers)                                        //140424
, soil_hydrology           (_soil_hydrology)                                     //071012
, soil_hydraulic_properties
   (_soil_hydraulic_properties)                                                  //140423
, pond                     (_pond)                                               //130308
, runoff                   (_runoff)                                             //130308
, chemicals                (0)                                                   //070117
, daily_error              (0)
, soil_wetting             (0)                                                   //130313
, override_leaching_depth  (false)                                               //020620
, leaching_depth           (0.0)                                                 //020620
, layer_at_reported_drainage_depth(0)                                            //071012
{}
//_2007-01-19______________________________________________________constructor_/
bool Soil_infiltration::initialize()                               modification_
{  bool inited = Soil_infiltration_nominal::initialize();                        //080610
   if (!override_leaching_depth)
      layer_at_reported_drainage_depth =
         soil_layers.get_layer_at_depth(soil_layers.get_depth_profile_m());      //140424
   return inited;
}
//______________________________________________________________________________
bool Soil_infiltration::infiltrate
(float64               water_entering_soil_not_irrigation
,float64               management_irrigation
,float64               management_auto_irrigation_concentration
,Dynamic_water_entering_soil *non_runoff_water_entering_in_intervals_mm          //990204
,Dynamic_water_entering_soil *irrigation_water_entering_in_intervals_mm          //070119
,const CORN::Dynamic_array<float32> &runon_in_intervals                          //990409
,CORN::Dynamic_array<float32> &runoff_in_intervals)                modification_ //990409
{
   balance_drainage = 0;
   reported_drainage = 0;
   infiltration = 0;
   return true;
}
//______________________________________________________________________________
void Soil_infiltration::set_override_leaching_depth(float64 leaching_depth_)
{  override_leaching_depth = true;
   leaching_depth = leaching_depth_;
   layer_at_reported_drainage_depth = soil_layers.get_layer_at_depth(leaching_depth);
}
//_2002-06-20_____________________________________set_override_leaching_depth__/
float64 Soil_infiltration::redistribute_water // V.B.  SoilWaterRedistribution
(Layer first_redistribution_layer
,Layer last_redistribution_layer
,soil_layer_array64(water_flow)                                                  //080208
   // may be layer or node based depending on the infiltration model
,float64 hours_to_field_capacity                                                 //080311
,CORN::Seconds time_step)     // RLN presuming time step is seconds                    //080311
{
   float64 water_potential_after_drainage = 0.0; // Note that this is set up for the first encountered layer.
   float64 flow_out = 0;

//Once flow_out is 0,
//continue looking the soil profile for a layer
//above field capacity

   for (Layer layer =first_redistribution_layer ; layer <= last_redistribution_layer; layer++)
   {  // Determine hydraulic conductivity that matches field capacity characteristics   (080311 RLN: This comment may be obsolete, need to check)
      float64 thickness_layer = soil_layers.get_thickness_m(layer);
      float64 FC_layer =  get_field_capacity_ice_corrected(layer);
      float64 WC_layer_curr   = soil_hydrology.get_liquid_water_content_volumetric(layer);
      float64 WC_layer_new    = WC_layer_curr;
      float64 WC_sat_layer    = soil_hydraulic_properties.get_saturation_water_content_volumetric(layer,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822);
      float64 b_value_layer   = soil_hydraulic_properties.get_Campbell_b(layer,false);
      float64 m_layer         = 2.0 * b_value_layer + 3.0; // RLN note I may already have this in hydraulic properties //080311
   float64 K_Sat_layer
      =  thickness_layer * water_density * pow(WC_sat_layer,m_layer)
       * (pow(FC_layer,1.0 - m_layer) - pow(WC_sat_layer , 1.0 - m_layer)  )
       / (standard_gravity * hours_to_field_capacity * 3600.0 * (m_layer - 1));
   float64 air_entry_pot   = soil_hydraulic_properties.get_air_entry_potential(layer,false/* not FC_PWP_based*/);
   if (layer == first_redistribution_layer)
   {  // Set redistribution conditions and drain first layer to redistribute                                                                                                                                              'Set redistribution conditions and drain first layer to redistribute
      float64 one_hour_water_content_change = 0.0;
      if (WC_layer_curr > FC_layer)
      {
         one_hour_water_content_change
         = WC_layer_curr - pow((pow(WC_layer_curr , (1.0 - m_layer))
                            + (standard_gravity * K_Sat_layer * (m_layer - 1.0) * time_step)
                           / (thickness_layer * water_density * pow(WC_sat_layer , m_layer)) ), (1.0 / (1.0 - m_layer)));
         if (one_hour_water_content_change > WC_layer_curr - FC_layer)
             one_hour_water_content_change = WC_layer_curr - FC_layer;
      }  // else  default one_hour_water_content_change to 0.0
      //{    one_hour_water_content_change = 0
      //}  /* (WC_layer_curr > FC_layer) */
       WC_layer_new = WC_layer_curr - one_hour_water_content_change;
       flow_out = one_hour_water_content_change * thickness_layer;
       water_potential_after_drainage =
         air_entry_pot * pow((WC_layer_new / WC_sat_layer) , (-b_value_layer));
   } else   // Redistribute deeper layers
   {  float64 water_potential_layer  =
         air_entry_pot * pow((WC_layer_curr / WC_sat_layer) , (-b_value_layer));
      if (water_potential_layer > water_potential_after_drainage)
      {  float64 available_to_redistribute = 0.0;
         float64 WC_at_water_potential_after_drainage =
            WC_sat_layer * pow((water_potential_after_drainage / air_entry_pot)
                              , (-1.0 / b_value_layer));
         if (WC_at_water_potential_after_drainage > FC_layer )
            available_to_redistribute =
               (WC_layer_curr - WC_at_water_potential_after_drainage)
               * thickness_layer;
         else if (WC_layer_curr > FC_layer )
         {  float64 one_hour_water_content_change
               = WC_layer_curr
                  - pow(( pow(WC_layer_curr , (1.0 - m_layer))
                           + (standard_gravity * K_Sat_layer * (m_layer - 1.0) * time_step)
                         / (thickness_layer * water_density * pow(WC_sat_layer , m_layer)))
                       , (1.0 / (1.0 - m_layer)));
            if (one_hour_water_content_change > WC_layer_curr - FC_layer)
                one_hour_water_content_change = WC_layer_curr - FC_layer;
                // Avoid draining soil below FC
            available_to_redistribute =
               one_hour_water_content_change * thickness_layer;
         } /* else  defaults to 0.0 as initialized above */
         //{   available_to_redistribute = 0;
         //}
         WC_layer_new =
            WC_layer_curr - available_to_redistribute / thickness_layer;
         flow_out = flow_out + available_to_redistribute;
      } else /* (water_pot_layer <= water_pot_after_drainage) */
      {  float64 WC_at_water_potential_after_drainage =
            WC_sat_layer * pow((water_potential_after_drainage / air_entry_pot) , (-1.0 / b_value_layer));

// RLN Warning, the following line seems suspicious, it does not appear Flow_Out has yet been computed for this layer.
// I presume it is the flow_out of the previous layer.
// I dont like this it looks wrong.
// Should have flow in from previous layer.


         WC_layer_new = WC_layer_curr + flow_out / thickness_layer;
         flow_out = 0.0;
         if ((WC_layer_new > WC_at_water_potential_after_drainage)
              && (WC_at_water_potential_after_drainage > FC_layer) )
         {  // target content is above field capacity this will have extra water above the target
           flow_out =
               (WC_layer_new - WC_at_water_potential_after_drainage) * thickness_layer;
            WC_layer_new = WC_at_water_potential_after_drainage;
         } else
         {  float64 one_hour_water_content_change = 0.0;
            if (WC_layer_new > FC_layer)
            {

               one_hour_water_content_change
               = WC_layer_new - pow((pow(WC_layer_new , (1.0 - m_layer))
                                    + (standard_gravity * K_Sat_layer * (m_layer - 1.0) * time_step)
                                    / (thickness_layer * water_density * pow(WC_sat_layer , m_layer)))
                                   , (1.0 / (1.0 - m_layer)));
               if (one_hour_water_content_change > WC_layer_new - FC_layer)
                   one_hour_water_content_change = WC_layer_new - FC_layer;
            } // else one_hour_water_content_change defaults to 0.0
            //{    one_hour_water_content_change = 0.0
            //}

            WC_layer_new = WC_layer_new - one_hour_water_content_change;

// RLN Warning, the following line looks suspicious.
//Flow_out is being accumulated, but it is 0 at this point

               flow_out =
                  flow_out + one_hour_water_content_change * thickness_layer;
               water_potential_after_drainage =
                  air_entry_pot * pow((WC_layer_new / WC_sat_layer) , ( - b_value_layer));
            }
         }  /* (Water_Pot_layer > water_pot_after_drainage) */
      }  /* Layer = First_Redistribution_Layer */


//      WC_layer_new = WC_layer_curr + water_in / thickness_layer;
//      float64 air_entry_pot_layer = soil_hydraulic_properties.get_air_entry_potential(layer,false/* not FC_PWP_based*/);
//      float64 WC_at_water_potential_after_drainage =
//            WC_sat_layer * pow((water_potential_after_drainage/ air_entry_pot_layer),(-1.0/b_value_layer));
//      if ((WC_layer_new > WC_at_water_potential_after_drainage) && (WC_layer_new > FC_layer))  //070318
//      {  float64 WC_above_FC =  (WC_layer_new - FC_layer);
//         float64  available_to_redistribute = 0.0;                                             //070318
//         if (WC_above_FC < 0.005)                                                              //070318
//         {  available_to_redistribute = WC_above_FC * thickness_layer;
//            WC_layer_new = FC_layer;
//         } else
//         { available_to_redistribute
//            = std::min<xxxx>(WC_above_FC, WC_layer_new - WC_at_water_potential_after_drainage) * thickness_layer;
//            WC_layer_new -= available_to_redistribute / thickness_layer;
//         }
//         water_out = available_to_redistribute;
//         // This was added to track the penetration of the redistribution front,               //070319
//         // to be used to calculate hours to field capacity each hour (may change if limiting layers encountered)
//         last_redistribution_layer_for_current_pulse = layer + 1;                              //070319
//      } else
//         water_out = 0.0;
//   //Note that set liquid water content should automatically update water potential

      // Update hydrology water content with WC_layer_new!

      float64 WC_change = WC_layer_new - WC_layer_curr;
      soil_hydrology.change_liquid_water_content_by_volumetric(layer,WC_change);
      water_flow[layer] = flow_out;                                              //080208
      if (override_leaching_depth && (layer == layer_at_reported_drainage_depth))
            reported_drainage += flow_out;
   } // Next Layer
   // RLN Note that water flows are updated by caller                            //080311
   //Note that the water balance is not updated here because current F.D. calculated drainage a different way  //071024
   return flow_out;
}
//_2008-03-11_2007-03-16___________________________________redistribute_water__/
float64 Soil_infiltration::get_field_capacity_ice_corrected(Layer layer)   const
{  // eventually move to hydrology;
   float64 field_capacity_layer =  soil_hydraulic_properties.get_field_capacity_volumetric(layer);
   if (soil_hydrology.get_ice_content_volumetric(layer) > 0.0)                   //990315
   {  float64 ice_content_layer=soil_hydrology.get_ice_content_volumetric(layer);//051204
      float64 sat_WC =  soil_hydraulic_properties
         .get_saturation_water_content_volumetric(layer,ice_content_layer);      //140822_051204
      field_capacity_layer = std::min<float64>(field_capacity_layer,(sat_WC));   //990315
   }
   return field_capacity_layer;
}
//___________________________________________get_field_capacity_ice_corrected__/
RENDER_INSPECTORS_DEFINITION(Soil_infiltration_nominal)
{
   // uses soil emanator
   inspectors.append(new CS::Inspector_scalar(reported_drainage       ,UC_meter   ,*context,"drainage"  ,value_statistic,CSVP_soil_base_water_drainage/*171222 CSVC_soil_base_water_drainage_time_step_sum*/ )); // accum
   inspectors.append(new CS::Inspector_scalar(act_water_entering_soil ,UC_meter   ,*context,"entering"  ,value_statistic,CSVP_soil_base_water_entering/*171222 CSVC_soil_base_water_entering_time_step_sum*/ )); // accum
   return 0; // emanator;
}
//_2013-07-30_______________________________________render_variable_recorders__/

