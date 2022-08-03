#ifndef hydrology_cascadeH
#define hydrology_cascadeH
#include "soil/hydrology.h"
//______________________________________________________________________________
class Soil_hydrology_cascade
: public Soil_hydrology_abstract
{
   soil_layer_array64(liquid_water_content);   // m3/m3 volumetric               //070824
public: // constructor
   Soil_hydrology_cascade
      (const Soil_layers_interface               &_soil_layers_ref
      ,const Soil_hydraulic_properties_interface &_hydraulic_properties_ref
      ,const Soil_structure_interface            &_soil_structure);
   Soil_hydrology_cascade                                                        //140610
      (const Soil_hydrology_cascade &copy_from
      ,float32 fraction = 1.0);
   inline virtual Soil_hydrology_cascade *copy(float32 fraction = 1.0)     const //140610
      { return new Soil_hydrology_cascade(*this,fraction); }                     //140610
public: // processes
   virtual float64 extract_water(float64 amount_to_extract_m[] ,uint8 start_layer);
public:  // Calculators
   virtual float64 calc_water_depth_profile                                      //130930 was get_water_depth_profile
      (bool liquid_and_ice)                                                const;
   virtual float64 get_liquid_water_content_volumetric
      (uint8 layer)                                                        const;
   virtual float64 set_water_content_volumetric_layer
      (uint8 layer, float64 new_water_content)                     modification_;
   virtual float64 change_liquid_water_content_by_volumetric                     //070813
      (uint8 layer, float64 change_WC)                             modification_;
};
//_2006-05-05___________________________________________________________________

#endif
