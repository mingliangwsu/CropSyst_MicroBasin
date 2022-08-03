#include "soil/hydrology_cascade.h"
#include "soil/soil_interface.h"
#include "corn/math/compare.h"
#include <iostream>
//______________________________________________________________________________
Soil_hydrology_cascade::Soil_hydrology_cascade
      (const Soil_layers_interface               &_soil_layers_ref
      ,const Soil_hydraulic_properties_interface &_hydraulic_properties_ref
      ,const Soil_structure_interface            &_soil_structure)
: Soil_hydrology_abstract(_soil_layers_ref,_hydraulic_properties_ref,_soil_structure)
{  clear_layer_array64(liquid_water_content);
}
//______________________________________________________________________________
Soil_hydrology_cascade::Soil_hydrology_cascade
(const Soil_hydrology_cascade &copy_from
,float32 fraction)
: Soil_hydrology_abstract(copy_from,fraction)
{  copy_layer_array64(liquid_water_content,copy_from.liquid_water_content);
}
//_2014-06-10___________________________________________________________________
float64 Soil_hydrology_cascade
::get_liquid_water_content_volumetric(uint8 layer)                         const
{  float64 WC = liquid_water_content[layer];                                     //070824
   return WC;
}
//______________________________________________________________________________
float64 Soil_hydrology_cascade
::set_water_content_volumetric_layer
(uint8 layer, float64 new_water_content)                           modification_
{  liquid_water_content[layer] = new_water_content;
   ice_water_content[layer] = 0;
   invalidate();                                                                 //130930
   return get_water_plus_ice_content_volumetric(layer);
}
//_2007-08-26__1999-03-15_______________________________________________________
float64 Soil_hydrology_cascade
::calc_water_depth_profile(bool liquid_and_ice)                            const
{  float64 water_depth_profile = 0.0;
   for (uint8 i = 1 ; i <= soil_layers_ref.get_number_layers(); i++)             //980724
   {  float64 wc_sl = liquid_and_ice
            ? get_water_plus_ice_content_volumetric(i)                           //990316
            : get_liquid_water_content_volumetric(i);                            //990316
      water_depth_profile += wc_sl * soil_layers_ref.get_thickness_m(i);
   }
   return water_depth_profile;
}
//_1999-03-15___________________________________________________________________
float64 Soil_hydrology_cascade::extract_water
(float64 amount_to_extract_m[] ,nat8 start_layer)                  modification_
{  float64 act_total_extraction_m = 0.0;
   for (uint8 layer = start_layer; layer <= soil_layers_ref.get_number_layers(); layer++)
   {  float64 volumetric_amount = amount_to_extract_m[layer] / soil_layers_ref.get_thickness_m(layer);
      float64 liquid_WC = get_liquid_water_content_volumetric(layer);            //070813
      float64 limited_volumetric_amount                                          //070813
         = std::min<float64>(liquid_WC,volumetric_amount);
      liquid_water_content[layer] -= limited_volumetric_amount;                  //990316
      float64 act_extraction_layer_m = limited_volumetric_amount
         * soil_layers_ref.get_thickness_m(layer);                               //070813
      act_total_extraction_m +=  act_extraction_layer_m;
      /*std::clog<<"L:"<<(int)layer
               <<"\tact_extract_mm:"<<m_to_mm(act_extraction_layer_m)
               <<"\tTotal_act_extract_mm:"<<m_to_mm(act_total_extraction_m)
               <<std::endl;*/
   }
   invalidate();                                                                 //130930
   return act_total_extraction_m;
}
//_2006-05-05___________________________________________________extract_water__/
float64 Soil_hydrology_cascade
::change_liquid_water_content_by_volumetric
(uint8 layer, float64 change_WC)                                   modification_
{  liquid_water_content[layer] += change_WC;                                     //070824
   invalidate();                                                                 //130930
   return liquid_water_content[layer] ;                                          //070824
}
//_2007-08-13_______________________change_liquid_water_content_by_volumetric__/
