#ifndef hydrology_finite_diffH
#define hydrology_finite_diffH
//______________________________________________________________________________
#include "soil/hydrology.h"
class Soil_infiltration_finite_difference; // forward declaration
//______________________________________________________________________________
class Soil_hydrology_finite_difference
: public Soil_hydrology_abstract
{protected: friend class Soil_infiltration_finite_difference;
   soil_node_array64(soil_volume_node);                                          //080130
      // These must be updated daily
      // (actually only when soil layering changes I.e. erosion and may be dust mulch)
   soil_layer_array64(upper_soil_volume);                                        //080130
   soil_layer_array64(lower_soil_volume);                                        //080130
   soil_layer_array64(upper_water_content_liquid); // upper calc_water_content in Finite Difference}  // I am pretty sure these are liquid only
   soil_layer_array64(lower_water_content_liquid); // lower calc_water_content at the end of the time step }
   float64 *node_depth;                                                          //080215
 public: // constructor
   Soil_hydrology_finite_difference
      (const Soil_layers_interface                 &_soil_layers_ref
      ,const Soil_hydraulic_properties_interface   &_hydraulic_properties_ref
      ,const Soil_structure_interface              &_soil_structure);
   Soil_hydrology_finite_difference
      (const Soil_hydrology_finite_difference &copy_from
      ,float32 fraction = 1.0);                                                  //140610
   inline virtual Soil_hydrology_finite_difference *copy(float32 fraction = 1.0) const //140610
      { return new Soil_hydrology_finite_difference(*this,fraction); }
   virtual void initialize(float64 *_node_depth);
   virtual void expand_last_layer_for_boundary_conditions                        //080212
      (nat8 number_layers,nat8 number_expanded_layers)             modification_;
 public: // processes
   virtual float64 extract_water
      (float64 water_uptake_m[]                                                  //070814
      ,nat8 start_layer);                                                        //070814
public:  // Calculated for today
   virtual bool    update_soil_volume                                            //080130
      (float64 number_expanded_layers
      ,float64 get_number_extended_nodes)                          modification_;
      // Currently this is called every day but only needs to be done when soil layering changes
   virtual float64 get_liquid_water_content_volumetric(nat8 layer)         const;//070814
   virtual float64 get_liquid_water_depth_profile()                        const;//080121
   virtual float64 set_water_content_volumetric_layer                            //070814
      (nat8    layer                                                             //070814
      ,float64 new_water_content) modification_;                                 //070814
   virtual float64 change_liquid_water_content_by_volumetric                     //070813
      (nat8   layer                                                              //070814
      ,float64 change_WC)                                          modification_;//070814
 public: // accessors
   float64 get_upper_water_content_liquid(nat8 layer)                      const;//071010
   float64 get_lower_water_content_liquid(nat8 layer)                      const;//071010
   float64 set_upper_water_content_liquid(nat8 layer,float64 new_WC)modification_;//090107
   float64 set_lower_water_content_liquid(nat8 layer,float64 new_WC)modification_;//090107
   float64 set_upper_and_lower_water_content_liquid                              //071010
      (nat8 layer,float64 new_upper_WC
      ,float64 new_lower_WC)                                       modification_;//070814
   virtual float64 calc_water_depth_profile                                      //130930_080314  //was get_water_depth_profile
      (bool liquid_and_ice)                                                const;//080121
   inline virtual float64 get_soil_volume(nat8 node)                       const { return soil_volume_node[node]; } //080130
   bool get_liquid_water_depth_nodes                                             //080201
      (soil_node_array64(water_depth_nodal)
      ,nat8 num_nodes_eff)                                                 const;
 protected: friend class Soil_freezing_profile_jumakis; // set state accessors
 private:
   virtual bool set_upper_and_lower_liquid_water_content_volumetric              //070827
      (nat8 layer, float64 layer_liquid_WC)                        modification_;
 public: // calculations
   float64 calc_liquid_water_content_layer                                       //080131
      (nat8 layer
      ,float64 upper_water_content
      ,float64 lower_water_content)                                        const;
   float64 calc_water_potential_with_respect_to_layer                            //090107
      (float64 water_content_volumetric,nat8 layer)                        const;
};
//_2006-05-05__________________________________________________________________/

#endif
