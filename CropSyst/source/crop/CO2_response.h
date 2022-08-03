#ifndef CO2_responseH
#define CO2_responseH
#ifndef primitiveH
#   include "corn/primitive.h"
#endif
#include "crop_param_struct.h"
#include "common/weather/atmospheric_CO2_change.h"

class Vapor_pressure_saturation_slope;                                           //140507
class Psychrometric_constant;                                                    //140508
namespace CropSyst
{
   class Canopy_cover_reference;
   typedef struct Crop_parameters_struct::Canopy_growth_cover_based Canopy_parameters; //110903
//______________________________________________________________________________
class Crop_CO2_response
{
   const Crop_parameters_struct::CO2_Response  &CO2_response_parameters;
 private:
   // calculated once:
   float64 canopy_conductance_at_FAO_CO2_359;                                    //131205
   float64 canopy_conductance_at_saturation_CO2;                                 //131205
   float64 growth_at_CO2_when_TUE_was_determined_relative_to_baseline_CO2;       //131206
   float64 growth_at_CO2_when_RUE_was_determined_relative_to_baseline_CO2;       //131206
   mutable float64 actual_biomass_gain_ratio_in_response_to_CO2_TUE;             //131209
 private:
   contribute_ float64 atmospheric_CO2_conc_ppm_yesterday;                       //150311
 public:
   mutable float64 actual_biomass_gain_ratio_in_response_to_CO2_RUE;             //131209
   mutable float64 TUE_adjustment;                                               // CO2AdjustmentToTUE
   mutable float64 transpiration_adjustment_factor;                              //140709
 private: // external references
      // Eventually weather provider will go away as I will provide references to the 3 parameters
   const Vapor_pressure_saturation_slope &vapor_pressure_saturation_slope;       //140507
   const Psychrometric_constant          &psychrometric_constant;                //140507
   const float64                         &aerodynamic_resistance_ref_plants;     //140508
         // day/m
   const CS::CO2_atmospheric_concentration   &ref_atmospheric_CO2_conc;          //150507
 protected : // Initialized once
   float64 FAO56_canopy_resistance; // day/m                                     //WeatherState.UnstressedCanopyResistance;
 public: // Recalculated when CO2 changes
   mutable float64 CO2_adjusted_FAO56_canopy_resistance; // day/m
   mutable float64 canopy_cond_adj_relative_to_FAO56;
 public:
   Crop_CO2_response
      (const Crop_parameters_struct::CO2_Response
         &_CO2_response_parameters
      ,const Vapor_pressure_saturation_slope &vapor_pressure_saturation_slope    //140507
      ,const Psychrometric_constant          &psychrometric_constant             //140508
      ,const float64                         &aerodynamic_resistance_ref_plants  //140508 // day/m
      ,const CS::CO2_atmospheric_concentration &atmospheric_CO2_conc_ppm);       //150507
   bool initialize();                                                            //110628
   void update_with_new_atmphospheric_CO2()                       rectification_;//131209
   void update()                                                  rectification_;//131208
   inline float64 get_canopy_resistance()                                  const //110904
      { return CO2_adjusted_FAO56_canopy_resistance; } // day/m
   inline float64 get_TUE_adjustment()                                     const //110913
      {return TUE_adjustment;}
   inline float64 get_transpiration_adjustment_factor()                    const //140709
      { return transpiration_adjustment_factor; }
   inline float64 get_growth_at_CO2_when_RUE_was_determined_relative_to_baseline_CO2() const
      { return growth_at_CO2_when_RUE_was_determined_relative_to_baseline_CO2;}
   #ifdef __BCPLUSPLUS__
   // In gcc compiler the references to floats  sometimes get lost.              //160418
   inline const float64 &ref_transpiration_adjustment_factor()             const
      { return transpiration_adjustment_factor;}                                 //160314
   #endif
 private:
   float64 calc_canopy_conductance_at(float64 CO2_conc)                    const;//151028
};
//______________________________________________________________________________
} // namespace

#endif

