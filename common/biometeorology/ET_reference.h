//---------------------------------------------------------------------------
#ifndef ET_referenceH
#define ET_referenceH
//---------------------------------------------------------------------------
#include "corn/const.h"
#include "corn/quality.hpp"
#include "corn/measure/measures.h"
#include "biometeorology/ET_common.h"
#include "biometeorology/ET_model.h"
#include "biometeorology/ET_reference_interface.h"
#include "weather/parameter/WP_ET_reference.h"
#include "weather/parameter/WC_vapor_pressure_saturation_slope.h"
#include "weather/parameter/WC_psychrometric_const.h"
#include "weather/parameter/WP_latent_heat_vaporization.h"
#include "solar/irradiance_extraterrestrial.h"

#include <fstream>

// This class is replacing Reference_ET_FAO
class Wind_speed;
class Vapor_pressure_deficit_fullday;

class Weather_provider;
class Aerodynamics;
class Air_temperature_average;
namespace CORN
{  class Date;
}
//_____________________________________________________________________________
class Reference_evapotranspiration_model_set                                     //090928
: public virtual ET_reference_interface_obsolete                                          //100418
, public ET_common                                                               //090928
{
public:
   enum Include_term { NO_TERM = 0, include_radiation_term=0x01, include_aerodynamic_term=0x02, include_total_terms = 0x03 };
protected: friend class Weather_provider;                                        //041109
   const Air_temperature_average          &air_temperature_avg;
   const Wind_speed                       &wind_speed;
   const Vapor_pressure_deficit_fullday   &avg_fullday_vapor_pressure_deficit;
   
protected:
   float64 saturation_vapor_pressure_deficit; // kPa
   float64 reference_canopy_resistance; // day/m for reference grass
   // reference_canopy_resistance is allowed to be variable
   // because CO2 simulations will need to adjust this value
protected: // Current values used in more than one of the ET models.
   float64 wind_speed_at_standard_height_m_s;
   float64 avg_fullday_vapor_pressure_deficit_kPa;
   float64 soil_heat_flux_density;      // MJ/(m2 day)
   mutable float64 net_radiation;               // MJ/(m2 day) at crop surface  (Conventionally denoted as R sub n)
//   float64 slope_of_saturated_vapor_pressure_curve_obsolete;  // kPa/°C  (Conventionally denoted as delta)
//      mutable float64 psychrometric_const_obsolete;         // kPa/°C  (Conventionally denoted as gamma)
//      mutable float64 latent_heat_vaporization_obsolete;    // ???     (Conventionally denoted as lambda)  // 2001-10-09
   mutable float64 aerodynamic_resistance;                                       //011119
   float64 Penman_radiation_term;
 // Additional parameters for specific models:
 protected:  // Priestley-Taylor
   float64 Priestley_Taylor_constant;                                            //090928
   bool Priestley_Taylor_constant_is_adjusted_for_VPD;   // This is true in CropSyst
 protected:  // Hargreaves
   float64 Hargreaves_ET_slope;       // Currently I have these only available from ClimGen site analysis
   float64 Hargreaves_ET_intercept;   // These are available in ClimGen location file.             // 2009-09-28
   bool    Hargreaves_parameter_set;                                                    // 2009-09-29
 protected:
   provided_ Evapotranspiration_parameter ET_ref_raw[ET_Model_COUNT];            //110415
   provided_ uint16         provided;
 public:
   virtual bool start_day()                                       modification_;

   float64 provide_model
      (ET_Model         model
      ,CORN::Quality   &quality)                                     provision_;

   float64 provide_Penman                    (CORN::Quality &quality) /* 1948 */ provision_;
   float64 provide_Penman_Monteith           (CORN::Quality &quality) /* 1965 */ provision_;
   float64 provide_FAO_56                    (CORN::Quality &quality) /* 1998 */ provision_;
   float64 provide_ASCE                      (CORN::Quality &quality) /* 1990 */ provision_;
   float64 provide_ASCE_EWRI_short_crop      (CORN::Quality &quality) /* 1998 */ provision_;
   float64 provide_ASCE_EWRI_tall_crop       (CORN::Quality &quality) /* 1998 */ provision_;
   float64 provide_Priestly_Taylor           (CORN::Quality &quality) /* ???? */ provision_;
   float64 provide_Penman_Monteith_CropSyst4 (CORN::Quality &quality) /* 2001 */ provision_;
   #if (CS_VERSION!=4)
   float64 provide_Penman_Monteith_CropSyst_VB(CORN::Quality &quality) /* 2010 */ provision_;
   #endif
   float64 provide_Hargreaves_unadjusted     (CORN::Quality &quality)            provision_;
   float64 provide_Hargreaves_adjusted       (CORN::Quality &quality)            provision_;

   float64 provide_radiation_Penman_Monteith (CORN::Quality &quality) provision_;//100509
   float64 provide_aerodynamic_Penman_Monteith(CORN::Quality &quality)provision_;//100509
 public:
   float64 calc_FAO_56
                  (CORN::Quality &quality
                  ,uint8 include_terms = include_total_terms
                  ,float64 Cn = 900.0
                  ,float64 Cd = 0.34)                             /*1998*/ const;
 protected:
   float64 calc_Penman                   (CORN::Quality &quality) /*1948*/ const;
   float64 calc_Penman_Monteith          (CORN::Quality &quality) /*1965*/ const;
   float64 calc_ASCE                     (CORN::Quality &quality) /*1990*/ const;
   float64 calc_ASCE_EWRI_short_crop     (CORN::Quality &quality) /*1998*/ const;
   float64 calc_ASCE_EWRI_tall_crop      (CORN::Quality &quality) /*1998*/ const;
   float64 calc_Priestly_Taylor          (CORN::Quality &quality) /*????*/ const;
   float64 calc_Penman_Monteith_CropSyst4(CORN::Quality &quality) /*2001*/ const;
   float64 calc_Hargreaves_unadjusted    (CORN::Quality &quality)          const;
   float64 calc_Hargreaves_adjusted      (CORN::Quality &quality)          const;
#if (CS_VERSION!=4)
   float64 calc_Penman_Monteith_CropSyst_VB(CORN::Quality &quality)        const;//101215
#endif
   float64 calc_Penman_radiation_term()                                    const;
 public: // 'structors
   Reference_evapotranspiration_model_set
      (float32             _elevation                                            //160617
      ,const float64 &_day_length_hours_today                                    //150627
      ,Weather_provider                   &_weather
      ,bool Priestley_Taylor_constant_is_adjusted_for_VPD = true);
 public:  // Set upf Hargreaves
   void known_for_Hargreaves_model
      (float64 ET_slope,float64 ET_intercept)                      modification_;
 private:
   float64 calc_general_equation
                  (float64 radiation_term
                  ,float64 vapor_pressure_term
                  ,float64 slope_of_saturated_vapor_pressure_curve
                  ,float64 psycrometric_term   // kPa/ºC
                  ,float64 aerodynamic_resistance_term)                    const;
 public:
   inline virtual float64 get_m(ET_Model preferred_ET_model)               const
      { return ET_ref_raw[preferred_ET_model].get_m(); }                         //110415
   inline virtual float64 get_mm(ET_Model preferred_ET_model)              const
      { return ET_ref_raw[preferred_ET_model].get_mm(); }                        //110415
   virtual float64 get_vapor_pressure_plus_resistance(float64 bulk_resistance)   const { return 0.0; } // Not currently used in this model
 public:
   virtual float64 calc_daily_Priestley_Taylor_constant
      (/*CS_ET_Modelxxx using_ET_model  currently based only of FAO 56 model*/)                                     const;
      /**< The PT constant is a value typically between 1 and 2.
      This function is a daily value.  Typically this daily value
      would be averaged for a key period in in the year
      perhaps a summer month such as July, (perhaps for the growing season?)
      to derive the PT generalize PT constant (1.26 or higher for moister conditions)
      **/
public:
    virtual void dump_header(std::ofstream &strm);
    virtual void dump_detail(std::ofstream &strm);      
};
//______________________________________________________________________________
#endif
