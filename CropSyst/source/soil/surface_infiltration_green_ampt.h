#ifndef surface_infiltration_green_amptH
#define surface_infiltration_green_amptH
#include "corn/primitive.h"                                                      //150929RLN_150219LML
#include "soil/layering.h"                                                       //150219LML
#include "soil/runoff.h"                                                         //150219LML
#include "pond.h"                                                                //150219LML
//_____________________________________________________________________________/
class Soil_hydraulic_properties_interface;                                       //150219LML
class Soil_hydrology_interface;                                                  //150219LML
//_____________________________________________________________________________/
class Soil_surface_infiltration_Green_Ampt
{
 public:
   bool    first_hour_of_watering;
 public:
   float64 wetting_front_depth;
   nat8    wetting_front_layer;                                                  //170426
 protected:
   float64 Saturated_Hydraulic_Conductivity_For_Infiltration;
   float64 WP_m_wetting_front_avg;                                  //130325
   float64 water_potential_top_m ;                                               //130325
   soil_layer_array64(initial_water_potential_m);                                //140819
      // Not sure if initial_water_potential_m is reset every day
 protected:
   const Soil_layers_interface               &layers;                            //170428
   const Soil_hydraulic_properties_interface &soil_hydraulic_properties;         //071012
   const Soil_hydrology_interface            &hydrology;                         //140820
 public:
   Soil_surface_infiltration_Green_Ampt
      (const Soil_layers_interface                 &layers_                      //170428
      ,const Soil_hydraulic_properties_interface   &soil_hydraulic_properties_   //140424
      ,const Soil_hydrology_interface              &hydrology_                   //140820_060512
      ,CropSyst::Soil_runoff                       *runoff_                      //131101
      ,CropSyst::Pond                              &pond_);
   float64 update
      (Hour hour                                                                 //140814
      ,float64  water_input_hourly
      ,float64  water_content_layer_1
      //170426 ,float64 &hydraulic_conductivity_saturated_min
      ,float64 &runoff_amount
      ,nat8     number_layers  );                                                //140820
   /*170426
   bool update_wetting_front_when_water_depth_to_infiltrate_exceeds_available_storage_to_saturation
      (nat8 layer,float64 depth_layer,bool last_layer);
   */
   bool update_wetting_front
      (nat8 layer
      ,bool is_bottom_layer
      ,float64 _wetting_front_depth
      ,float64 water_content_below);
   bool clear_wetting_front();
};
//_2013-05-03__________________________________________________________________/




#endif
