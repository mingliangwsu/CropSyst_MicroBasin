#ifdef USE_PCH
#  include "simulation/CropSyst_sim_pch.h"
#else
#  include <corn/math/moremath.h>
#  ifndef compareHH
#     include <corn/math/compare.hpp>
#  endif
#endif
#include "soil/infiltration_cascade_daily.h"
#include "soil/chemicals_profile.h"
//______________________________________________________________________________
Soil_infiltration_cascade_daily::Soil_infiltration_cascade_daily
(const Soil_layers_interface  &_soil_layers                                      //140424
,const Soil_hydraulic_properties_interface &_soil_hydraulic_properties           //140423
,Soil_hydrology_cascade       &_hydrology                                        //060512
#ifdef OLD_EVAPORATE
//160720 ,modifiable_ Physical::Water_depth           &evaporation_potential_remaining_   //160413
,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining_      //160720
#endif
,CropSyst::Soil_runoff        *_runoff_unused                                    //130308
,CropSyst::Pond               &_pond_unused                                      //130308
)
: Soil_infiltration_cascade_common                                               //070116
   (_soil_layers                                                                 //140424
   ,_soil_hydraulic_properties                                                   //140423
   ,_hydrology
   #ifdef OLD_EVAPORATE
   ,evaporation_potential_remaining_                                             //160413
   #endif
   ,_runoff_unused,_pond_unused
   )
{ }
//______________________________________________________________________________
bool Soil_infiltration_cascade_daily::infiltrate
(float64                      total_water_entering_soil_pot_not_irrigation  // now includes both precip and irrigation
,float64                      management_irrigation_daily
,float64                       management_auto_irrigation_concentration_unused
   // this parameter used only be F.D. model
,Dynamic_water_entering_soil *non_runoff_water_entering_in_intervals_mm_unused
,Dynamic_water_entering_soil *irrigation_water_entering_in_intervals_mm_unused  // optional (may be 0)
,const Dynamic_array<float32>    & runon_in_intervals_unused
   // this parameter used only be F.D. model
,Dynamic_array<float32>          &runoff_in_intervals_unused)
   // this parameter used only by F.D. and CascadeHourly models
{  // Cascade never gives additional runoff.
   Soil_infiltration_cascade_common::infiltrate
      (total_water_entering_soil_pot_not_irrigation
      ,management_irrigation_daily
      ,management_auto_irrigation_concentration_unused
      ,non_runoff_water_entering_in_intervals_mm_unused
      ,irrigation_water_entering_in_intervals_mm_unused
      ,runon_in_intervals_unused
      ,runoff_in_intervals_unused);
   infiltration_cascade
      (total_water_entering_soil_pot_not_irrigation
      ,management_irrigation_daily);
   // Cascade model has drainage built in.
   // Cascade model has transport and exchange built in.
   return true; // always successful
}
//_2007-01-18______________________________________________________infiltrate__/
void Soil_infiltration_cascade_daily::cascade_pulse
(float64 pulse_water_entering_soil_not_irrigation
,float64 pulse_irrigation
,soil_sublayer_array_64(old_water_content))                        modification_
{float64 prev_water_flux = pulse_water_entering_soil_not_irrigation
      + pulse_irrigation;    // 070107 This was missing I did not see anywhere irrigation was entering the soil
   for (uint8 layer = 1; layer <= soil_layers.get_number_layers(); layer++)
   {    float64 layer_thickness = soil_layers.get_thickness_m(layer);
            // 070117 Note eventually move this to a new function soil.hydrology->get_current_field_capacity_volumetric
            // but I need to check every where that field capacity is used to determine if it is needed there
        float64 layer_field_capacity = soil_hydraulic_properties.get_field_capacity_volumetric(layer);
        if (hydrology.get_ice_content_volumetric(layer) > 0.0)                   //990315
        {   float64 sat_WC = soil_hydraulic_properties.get_saturation_water_content_volumetric //051204
               (layer,hydrology.get_ice_content_volumetric(layer));              //140822
            layer_field_capacity =  std::min<float64>(layer_field_capacity,(sat_WC/*140822  - hydrology.get_ice_content_volumetric(layer)*/));  //990315
        }
      float64 curr_liquid_water_content = hydrology.get_liquid_water_content_volumetric(layer); //070813
        if (curr_liquid_water_content == 0.0)
            curr_liquid_water_content = 0.0000001;  //To avoid div by zero  (May occur in freezing conditions)
        old_water_content[layer] = curr_liquid_water_content;                    //990311
        // determine water flow (070117 was flux) into the next layer
        water_flow[layer]= (prev_water_flux - layer_thickness * (layer_field_capacity - curr_liquid_water_content)); //990311
        if (water_flow[layer] < 0.0)
            water_flow[layer] = 0.0;
        // contribution of portion of total area to the water reaching next layer
        //**** Why is bypass  coef not use before this point?????
      float64 contribution_WC = (prev_water_flux - water_flow[layer])/ layer_thickness ;  //070813
      hydrology.change_liquid_water_content_by_volumetric(layer,contribution_WC);//070813
        // m3 H2O/m3 soil
        if (override_leaching_depth && (layer == soil_layers.get_layer_at_depth_or_last_layer(leaching_depth))) //990106
             reported_drainage += water_flow[layer];                             //030128
        prev_water_flux = water_flow[layer];
   }
   balance_drainage += water_flow[soil_layers.get_number_layers()] ;             //990106
   if (!  override_leaching_depth)                                               //990106
        reported_drainage = balance_drainage;
}
//_1998-11-19___________________________________________________cascade_pulse__/
float64 Soil_infiltration_cascade_daily::infiltration_cascade
(float64 water_pot_entering_soil_daily_not_irrigation                            //070107
,float64 irrigation)                      // will be 0.0 if no management        //980730
// 071019 Note that it is no longer necessary to have the irrigation separate
// because the chemical transport model has been modified to allow mixing
// of all waters.
{  soil_layer_array64(old_liquid_water_content); clear_layer_array64(old_liquid_water_content);
   float64 total_water_pot_entering_soil_daily =water_pot_entering_soil_daily_not_irrigation + irrigation;        //070107
   if (!CORN::is_approximately<float64>(total_water_pot_entering_soil_daily,0.0,0.000001))                        //991204
   {   int16 num_pulses = 1;

/*120516 now only using 1 puls
      float64 FC_2 = hydrology.hydraulic_properties_ref->get_field_capacity_volumetric(2);                        //051204
      num_pulses =                                                                                                //960119
      std::max<xxxx>(5,(int16)(total_water_pot_entering_soil_daily  / (soil_layers.get_thickness_m(2) * FC_2)) + 1.0);  //990716



//Nconc_dump << endl << today.c_str() << "\t";

num_pulses = 5.0; // Currently disables the calculated number of pulses for debugging.

*/

//cout << "Cascade infiltration determination of pulses disabled" << endl;
#ifdef DISABLED
this doesnt appear to be working

float64 FC_1 = hydrology.hydraulic_properties_ref->get_field_capacity_volumetric(1);
        float64 Water_Depth_Equivalent_Of_One_Pore_Volume = soil_layers.get_thickness_m(1) * FC_1; // Water density not needed because thickness is in meters
          num_pulses = 1 + (int)(total_water_pot_entering_soil_daily / (0.2 * Water_Depth_Equivalent_Of_One_Pore_Volume));
       num_pulses = std::max<xxxx>(10,num_pulses );
#endif
      float64 pulse_water_entering_soil_not_irrig = water_pot_entering_soil_daily_not_irrigation      //990716
             / num_pulses;
      float64 pulse_irrigation = irrigation/num_pulses;
      Seconds pseudo_time = 0;                                                   //071019
      float64 pseudo_duration = 86400 / num_pulses; // Here we simply split up the seconds in the day by the pulses to get a pseudo-duration.   071019
      for (int16 pulse = 1; pulse <= num_pulses ; pulse++)
      {  cascade_pulse
            (pulse_water_entering_soil_not_irrig
            ,pulse_irrigation
            ,old_liquid_water_content);
         if (chemicals)                                                          //070119
         {  soil_layer_array64(liquid_water_content); clear_layer_array64(liquid_water_content);   //080127
            hydrology.get_liquid_water_content_layers_volumetric(liquid_water_content);            //080127
            chemicals->chemical_transport_and_exchange                                             //070119
               (CASCADE_DAILY_INFILTRATION                                                         //080114
               ,soil_layers.get_number_layers()
               ,soil_layers.get_number_layers() // this parameter is dummy it is used only for F.D. 080219
               ,pseudo_time                                                      //071015
               ,pseudo_duration                                                  //071015
               ,old_liquid_water_content                                         //070813  Warning (I dont know if this should be only liquid water content or total water content - was liquid only)
               ,liquid_water_content                                             //070813_990311  Warning (I dont know if this should be only liquid water content or total water content - was liquid only)
               ,pulse_water_entering_soil_not_irrig + pulse_irrigation
               ,water_flow                                                       //080208
               ,0.0 // No deferment in cascade model                             //071016
               ,override_leaching_depth                                          //981230
               ,soil_layers.get_layer_at_depth_or_last_layer(leaching_depth));   //981230
         }
         pseudo_time += pseudo_duration;                                         //071019
      }
      // update chemical concentrations is moved to  start day 071015
  }
  infiltration = balance_drainage;                                               //980730
  return infiltration;
}
//______________________________________________________________________________
//060306 190 lines
//060606 257 lines
//060731 150 lines
//070813 182 lines

