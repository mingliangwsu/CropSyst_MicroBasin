#ifndef abiotic_environmentH
#define abiotic_environmentH
#include "soil/soil_interface.h"
#include "corn/chronometry/time_types.hpp"
//180408 #include "corn/math/statistical/stats.h"
#include "corn/math/statistical/sample_dataset_T.h"
//______________________________________________________________________________
extern float64 calc_moisture_function
(float64 water_filled_porosity
,float64 value_at_saturation   // 0.0 for nitrification otherwise 0.6
);
//______________________________________________________________________________
enum Temperature_function_mode
{ decomposition_temperature_function
, nitrification_temperature_function
, denitrification_temperature_function   // this line is obsolete
, Temperature_function_mode_COUNT
};
//______________________________________________________________________________
extern float64 calc_temperature_function
               (float64 air_temperature_avg // For the time step  (actually I think this is soil temperature)
               ,float64 T_min, float64 T_opt, float64 T_max);
               // It appears this function works for any time step
               // May be the case that different time steps use different T_min, T_opt, T_max
               // but I don't see a time factor in this, the time factor appears
               // to be applied in the potential decomposition function that calls this
//______________________________________________________________________________
class Soil_abiotic_environment_layer
{protected:  friend class Soil_abiotic_environment_profile; friend class Organic_matter_V4_3;
   //180408 Statistical_data_set
   CORN::Statistical_sample_with_dataset<float32,float32,float32>                //180408
      // original Statistical_data_set was float32 but could now be float64
      temperature_function_hourly[Temperature_function_mode_COUNT];              //060510
      // Using stats because we need both the daily mean and daily sum (sum of the hours)
   //180408 Statistical_data_set
   CORN::Statistical_sample_with_dataset<float32,float32,float32>                //180408
      // original Statistical_data_set was float32 but could now be float64
      minimized_temperature_moisture_function_for_mode[Temperature_function_mode_COUNT]; //060510
      // Note we only actually need to store  minimized_temperature_moisture_function for decomposition mode (denitrification is obsolete)
   float64 moisture_function;
   float64 minimized_temperature_moisture_function_for_decomp;  // From VB SoilOrganicCarbonClass::PotentialCarbonDecomposition.Term
 public:
   contribute_ nat16 layer_informational; // This is not used, it simply identifies the layer for debugging //090827
 public:
   inline Soil_abiotic_environment_layer()
      : moisture_function(0)
      , minimized_temperature_moisture_function_for_decomp(0)
      , layer_informational(0)                                                      //090827
      {}
   bool update(float64 _moisture_function,float64 _minimized_temperature_moisture_function);
   virtual float64 get_temperature_function_daily_mean(Temperature_function_mode TF_mode)        const;
   virtual float64 get_temperature_function_daily_sum(Temperature_function_mode TF_mode)         const;
   virtual float64 get_temperature_function_at(Hour hour,Temperature_function_mode TF_mode )      const; //060510
   virtual float64 get_moisture_function()                      const;
   virtual float64 get_minimized_temperature_moisture_function()const;
   inline virtual float64 get_weighted_minimized_temperature_moisture_function(Hour hour,Temperature_function_mode TF_mode) const //081024
      { return minimized_temperature_moisture_function_for_mode[TF_mode].get_weighted_value(hour); }
};
//_2006-02-16__________________________________Soil_abiotic_environment_layer__/
class Soil_abiotic_environment_profile
{
/*080704
        // V4.2    V4.3
T_min; //   0       -5
T_opt; //  25       35
T_max; //  40       50
*/
 private:
   const Soil_layers_interface                     *soil_layers;
   const Soil_temperature_profile_hourly_interface *soil_temperature_profile_hourly;
   const Soil_hydrology_interface                  *soil_hydrology;
   Soil_abiotic_environment_layer                   soil_abiotic_environment_layer[MAX_soil_layers_alloc];
 public:
   Soil_abiotic_environment_profile
      (Soil_interface *                _soil);
   bool update(float64 residue_water_hold);
   inline const Soil_abiotic_environment_layer &ref_soil_abiotic_environment_layer(nat8  layer) const {return soil_abiotic_environment_layer[layer] ;} //060216
   inline Soil_abiotic_environment_layer *point_soil_abiotic_environment_layer(nat8  layer)  {return &soil_abiotic_environment_layer[layer] ;} //060216
};
//_2006-02-16________________________________Soil_abiotic_environment_profile__/
#endif

