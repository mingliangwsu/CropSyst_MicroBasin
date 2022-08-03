
#include "soil/evaporation_vapor_path.h>
//#include "soil/hydraulic_properties.h>
#include "soil_interface.h"
//#include "soil_structure_common.h>
#include <corn/measure/measures.h>
#include <corn/datetime/date_types.h>
#include <iostream.h>

#define NL_alloc 15
int32    NLAYR = 14;         // Number of layers in soil profile
float32  DLAYR_m[NL_alloc] = {0.0, 0.05,	0.05,	0.05,	0.1,	0.1,	0.1,	0.1,	0.1,	0.1,	0.1,	0.1,	0.1,	0.1,	0.1}; // Thickness of soil layers (cm)
float32  DS_m[NL_alloc]    = {0.0, 0.05,	0.1 ,	0.15,	0.25,	0.35,	0.45,	0.55,	0.65,	0.75,	0.85,	0.95,	1.05,	1.15,	1.25};    // Depth to bottom of soil layer (cm)


class Test_soil_layers
: public Soil_layers_interface
{
public: // Soil parameter accessors
   virtual uint8  get_max_number_layers() const { return NLAYR; };
   // This is the absolute maximum number of layers
   // (array dimension) that are reserved to store soil profile data by layer.
   virtual uint8  get_number_layers()     const { return NLAYR; };
   // This is the number of layers identified in the soil profile.
   virtual uint8  get_number_uninundated_layers()                          const { return NLAYR; };
   virtual uint8 get_horizon_at_layer(uint8 layer)                         const { return layer;} ;
   // This returns the layer (horizon) in which the specified layer/sublayer occurs.
public:
   Test_soil_layers() {};;
public: // Soil profile parameter accessors (layer number is 1 based)
   inline virtual float64 get_thickness_mm                  (uint8 layer)  const { return m_to_mm(DLAYR_m[layer]); };
   inline virtual float64 get_thickness_cm                  (uint8 layer)  const { return m_to_cm(DLAYR_m[layer]); };
   inline virtual float64 get_thickness_m                  (uint8 layer)   const  { return (DLAYR_m[layer]); };
   inline virtual float64 get_depth_cm                      (uint8 layer)  const { return m_to_cm(DS_m[layer]); };
   inline virtual float64 get_depth_m                      (uint8 layer)   const { return (DS_m[layer]); };
   inline virtual float64 get_depth_profile_cm              ()             const { return m_to_cm(DS_m[NLAYR]); };
   virtual uint8  get_layer_at_depth
      (float64 a_given_depth_m
      /*, bool limit_to_MAX_trans_layers=false*/)                              const {return 0;}; // Not used
      // Returns the index of the layer at the specified depth.

      // Note  need to get ride of   bool limit_to_MAX_trans_layers=false
      // Instead, caller should take the min of the layer at depth
      // or layer at max_transformation_depth
   virtual uint8  get_layer_at_depth_or_last_layer
      (float64 a_given_depth_m
      /*, bool limit_to_MAX_trans_layers=false*/)                              const {return 0;}; // Not used
      // Returns the index of the layer at the specified depth.
      // if  a_given_depth_m is 0.0 (unspecified) the last layer is returned
public: // Soil profile parameter accessors (layer number is 1 based)
   virtual uint8   closest_layer_at(float64 a_given_depth)                 const {return 0;}; // Not used
      // Returns the closest layer at the specified depth.
   virtual float64 get_layer_center_depth(uint8 sublayer)                  const {return 0;}; // Not used
public: // set accessors
public: // Utilities for working with layer data
   virtual void copy_array64(soil_layer_array64(target),const soil_layer_array64(source)) const {return; }; // Not used
   virtual void copy_array32(soil_layer_array32(target),const soil_layer_array32(source)) const {return; } ; // Not used
   virtual float64 get_depth_profile_m                  ()                 const {return 0;}; // Not used
      // This returns the total depth of the soil profile in centimeters.
   virtual uint8 set_number_uninundated_layers(uint8 new_uninundated_layers)not_const {return 0;}; // Not used
};
//______________________________________________________________________________
class Test_soil_hydraulic_properties
: public  Soil_hydraulic_properties_interface
{
public: // may be computed by pedotransfer functions
   // The default units system is metric MKS unless otherwise noted in the variable name or code comments
   // Volumetric values  are  volume of water per volume of (soil + water)
   // in units of m3/m3 (Equivelent to cm3/cm3)
   virtual float64 get_field_capacity_volumetric               (uint8 layer)  const  { return 0.2863959; };
   virtual float64 get_permanent_wilt_point_volumetric         (uint8 layer)  const  { return 0.106; };
   virtual float64 get_drained_upper_limit_volumetric          (uint8 layer)  const  { return 999999.0; };
   // Note: I think this may be field capacity
   virtual float64 get_lower_limit_volumetric                  (uint8 layer)  const  { return 999999.0; };
   // Note: I think this may be PWP
   virtual float64 get_saturation_water_content_volumetric     (uint8 layer,float64 ice_water_content)  const  { return 0.46756; };
   //    Usually {  return 1.0 - get_bulk_density_g_cm3(layer) / 2.65;
   virtual float64 get_unsaturated_conductivity_function_slope (uint8 layer)  const  { return 999999     ; };
   virtual float64 get_bypass_coef                             (uint8 layer)  const  { return 1.0     ; };
   virtual float64 get_sat_hydraul_cond_kg_s_m3                (uint8 layer)  const  { return 0.000529     ; };
   virtual float64 get_Campbell_b         (uint8 layer,bool FC_PWP_based)     const  { return 3.84854; };
public: // Values for the entire profile
   virtual float64 get_air_entry_potential(uint8 layer,bool FC_PWP_based)     const  { return -5.0031967; };
};
//______________________________________________________________________________
class Unit_test_soil_evaporation_with_vapor_path
{
   Test_soil_layers                    soil_layers;
   Test_soil_hydraulic_properties      soil_hydraulic_props;
   Soil_hydrology_finite_difference    hydrology;
   float64                             atmospheric_water_potential;
//   Soil_structure_common               soil_structure;
   Soil_evaporation_with_vapor_path    evaporation;
public:
   Unit_test_soil_evaporation_with_vapor_path()
   : atmospheric_water_potential(0)
//   , soil_hydraulic_props(soil_layers)
   , hydrology(&soil_layers,&soil_hydraulic_props,0/*soil_structure*/)
   , evaporation(soil_layers,&soil_hydraulic_props,hydrology,atmospheric_water_potential,false /*multiple drying layers*/)
   {
      hydrology.set_water_content_volumetric_layer( 0, 0.0);   
      for (uint8 layer = 1; layer < NL_alloc ; layer ++)
      {
         hydrology.set_water_content_volumetric_layer( layer, 0.28);
      }
   };

// Warning, this is copied from Finite difference
/*_______*/ float64 calc_atmospheric_water_potential  // appears to be kg.s/m^4
/*_______*/ (float64 relative_humidity_TS_or_daily_min_percent)            const
/*_______*/ {  //    prefer relative humidity during the time step, but the daily minimum would suffice
/*_______*/    float64 relative_humidity_TS_or_daily_min                                           // Hourly_Relative_Humidity = 0.5 'Assume 50% RHmin; actual value probably not needed
/*_______*/       = relative_humidity_TS_or_daily_min_percent / 100.0;                             // The V.B. version uses this constant relative humidity, C++ we use the actual
/*_______*/    float64 atmospheric_water_pot  =                                                    // Atmospheric_Water_Potential = 137000# * (Hourly_Relative_Humidity - 1)
/*_______*/                137000.0   // This is an average value for 25'C probably should use hourly temperature Claudio has the equation.
/*_______*/                * (relative_humidity_TS_or_daily_min - 1);
/*_______*/    return atmospheric_water_pot;
/*_______*/ };


   bool run_test()
   {
      float64 pot_evap_mm_day[] =
      {0
      ,5.035667553
      ,4.065355195
      ,4.13087426
      ,2.243883463
      ,5.01487762
      ,5.943145121
      ,5.935650038
      ,2.244491239
      ,2.283867644
      ,2.652619161
      ,9.073315302
      ,9.073281503
      ,9.073247826
      ,9.073214275
      ,9.073180858
      ,9.07314758
      ,9.073114448
      ,9.07308147
      ,9.073048651
      ,9.073015998
      ,9.072983521
      ,9.072951225
      ,9.072919119
      ,9.072887211
      ,9.072855508
      ,9.07282402
      ,9.072792755
      ,9.072761721
      ,9.072730929
      ,9.072700387
      ,9.072670104
      };

      evaporation.initialize(17);
      Seconds time_step = 3600;
      for (int day = 1; day < 30; day++)
      {
         float64 precip_today = (day == 1) ? 50.0 : 0.0; // mm

precip_today = 0.0;

         atmospheric_water_potential = calc_atmospheric_water_potential(50.0);

         float64  water_depth_in_mm_hour = precip_today/24.0; // evenly distribute precipitation into hours
         for (CORN::Hour hour = 0;  hour < 24; hour++)
         {
            float64 evap_mm_hour = evaporation.evaporate
                  (water_depth_in_mm_hour
                  ,time_step
                  ,hour
                  ,pot_evap_mm_day[day]
                  );
            cout << (int)day << '\t' << (int)hour << '\t' << evap_mm_hour;
            for (uint8 layer = 1; layer < 5 ; layer ++)
            {
               cout
               << '\t' << hydrology.get_upper_water_content_liquid( layer)
               << ' '  << hydrology.get_lower_water_content_liquid( layer);
            };
            cout << endl;

         };
            cout << "_____________________________________________________" << endl;

      };
      return true;
   };

private:
//______________________________________________________________________________


};

int main()
{
   Unit_test_soil_evaporation_with_vapor_path unit_test;
   return unit_test.run_test() ? 0 : 1;   // Return 0 on success.
};
