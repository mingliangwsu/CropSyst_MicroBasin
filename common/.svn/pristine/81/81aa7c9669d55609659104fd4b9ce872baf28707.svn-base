#ifndef ET_ref_dayH
#define ET_ref_dayH
#ifndef WEATHER_ET_H
#  include <common/weather/ET_common.h>
#endif
#ifndef UED_CODES_H
#  include <UED/library/codes.h>
#endif
#ifndef COMMON_MEASURE_MEASURES_H
#  include <corn/measure/measures.h>
#endif
#define canopy_resistance_constant 0.00081
// From 980220 to 011108 we used a canopy resistance of 0.000787037

class Weather;
//______________________________________________________________________________
class Reference_ET_FAO
: public ET_common
, public ET_reference_interface                                                  //090929
{private:
   Weather &weather;                                                             //041109
 protected:
   ET_models enabled_model;
   float64              ET_ref_mm      [FAO_ET_MODEL_COUNT];
   CORN::Quality_code   ET_ref_quality [FAO_ET_MODEL_COUNT];
   float64 saturation_vapor_pressure_deficit; // kPa
   float64 reference_canopy_resistance; // day/m for reference grass
   // reference_canopy_resistance is allowed to be variable
   // because CO2 simulations will need to adjust this value
 protected: // Current values used in more than one of the ET models.
   float64 curr_avg_air_temperature;         // degrees C
   float64 curr_soil_heat_flux_density;      // MJ/(m2 day)
   float64 curr_net_radiation;               // MJ/(m2 day) at crop surface
   float64 curr_slope_vapor_pressure_curve;  // kPa/'C
   float64 curr_psychrometric_const;          // kPa/'C
   float64 curr_latent_heat_vaporization;                                        //011009
   float64 curr_aerodynamic_resistance;                                          //011009
 public:
   Reference_ET_FAO
      (Weather &weather, ET_models preferred_ET_model);   // Not currently used
   virtual void update();
   /*151104 ETref no longer adjusted for CO2, it is the perview of the crop
   inline float64 set_reference_canopy_resistance(float64 _reference_canopy_resistance)  //011107
      { return reference_canopy_resistance = _reference_canopy_resistance; };
      */
   inline virtual float64 get_reference_ET_m(ET_models preferred_ET_model) const
      { return mm_to_m(ET_ref_mm[preferred_ET_model]); };
   inline virtual float64 get_reference_ET_mm(ET_models preferred_ET_model)const
      { return ET_ref_mm[preferred_ET_model]; };
   inline virtual CORN::Quality_code get_reference_ET_quality(ET_models preferred_ET_model)
      { return ET_ref_quality[preferred_ET_model]; };
   inline virtual float64 get_saturation_vapor_pressure_deficit()
      { return saturation_vapor_pressure_deficit; };
   float64 calc_atmospheric_density(float64 temperature_kelvin)            const;
   inline virtual float64 get_vapor_pressure_plus_resistance                     //011117
      (float64 bulk_resistance)                                            const
      {  return calc_vapor_pressure_plus_resistance
         ( curr_slope_vapor_pressure_curve
         , curr_psychrometric_const
         , bulk_resistance
         , curr_aerodynamic_resistance);
      };
};
//______________________________________________________________________________
#endif

