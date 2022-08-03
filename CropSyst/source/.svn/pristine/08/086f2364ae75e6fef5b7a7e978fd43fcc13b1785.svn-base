#ifndef crop_commonH
#define crop_commonH
#include "crop/crop_element.h"
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "crop/crop_transpiration_interface.h"
#include "corn/math/statistical/sample_cumulative_T.h"
//180408 #include "corn/math/statistical/stats.h"
//171212 moved to crop_element.h #include "CS_suite/observation/CS_observation.h"
//171212 moved to crop_element.h #include "CS_suite/simulation/CS_simulation_element.h"
#include "crop/event_scheduler_crop.h"
#ifdef YAML_PARAM_VERSION
#  include "corn/math/numerical/interpolate.h"
#endif
// This class provides methods common to CropSyst and CropGro  based crops

#ifndef CROP_TYPES_H
#  include "crop/crop_types.h"
#endif
class Soil_interface;                                                            //050720
class Soil_layers_interface;                                                     //050720
class Soil_salt_interface;                                                       //051118
class Weather;                                                                   //130901
class Weather_for_crop_interface;                                                //121115
class Vapor_pressure_deficit_daytime;                                            //140812

namespace CropSyst {
   class Crop_parameters;
   class Crop_nitrogen_common;                                                   //151029
//190805 deprecated    class Crop_nitrogen_V4;                                                       //151029
   class Phenology_interface;                                                    //150914
   class Event_scheduler_crop_complete;                                          //151127
   class Crop_CO2_response;                                                      //160418
//______________________________________________________________________________
#ifdef YAML_PARAM_VERSION
class Parameter_adjustment_cowl
: public implements_ CORN::Item
{
   float32                       &value; // reference of value to be adjusted
   Phenology_interface           &phenology;
   //NYI Parameter_adjustment_settings &settings;
   CORN::Interpolation_temporal      interpolator;
      // Dates are relative (year 0 is sowing year).
 public:
   bool update()                                                 rectification_;
};
#endif
//_2015-09-04___________________________________________________________________
class Crop_common
: public extends_ Crop_element                                                   //171212
//171212 : public extends_ CS::Simulation_element_composite
// Composite because I may want to have submodels as simulation elements
{
 protected:
      friend class CropSyst::Crop_nitrogen_common;                               //151029
//180805 deprecated      friend class CropSyst::Crop_nitrogen_V4;                                   //151029
      friend class CropSyst::Event_scheduler_crop_complete;                      //151127
 public: //180805 protected: // external references
   Crop_parameters   *parameters;                                                //020409
   bool               owns_parameters;                                           //040121
      // Normally a crop will own it's own parameters
      // This is not the case for Crop Calibrator
      // Also simulators which shart parameter files will not be owned
 protected:
   modifiable_ Soil_interface *soil;                                             //160415
   const Vapor_pressure_deficit_daytime &daytime_vapor_pressure_deficit;         //140812

 protected: // submodels
   CropSyst::Crop_CO2_response *CO2_response; //will be 0 if not simulating CO2  //020409
      // Owned by this

 protected:
   float64 intercepted_precipitation_m_today;                                    //160416
   float64 intercepted_precipitation_m_stored;
      // now interception is carried over to next day
   // obsolete Intercepted precipitation is released back to the atmosphere (presumably evaporation)  //140320 moved from Crop_CropSyst
 protected: // Data needed from derived crop class
   virtual Normal_crop_event_sequence get_growth_stage_sequence()       const=0;
   virtual float64 get_GAI_vital()                                      const=0; //981207
   virtual float64 get_GAI_vital_plus_effete()                          const=0; //981207
   virtual float64 get_LAI(bool from_canopy)                            const=0; //981207
 public: // transpiration
   float64 ET_ref; // meter                                                      //171030_080501
   // Provided by the ET model, but we need to keep for   // in meter
   // 080721 This could be moved to Transpiration_dependent_growth_common class
   // because that is the only place where it is used.
   float64 pot_transpiration_m[2];
      // index 0 unadjusted
      // index 1 CO2 adjusted
   float64 act_transpiration_m; // This could become negative                    //011022
   float64 report_transpiration_act_m;                                           //000322
      // The reported act_transpriation is constrained to > 0.
      //171031 was record_act_transpiration_m
   float64 reported_ET_pot_m;                                                    //171031
   float64 reported_ET_act_m;                                                    //171031

 protected:                                                                      //050331
   Crop_transpiration  *transpiration;                                           //050331
 public: // Fract root length
   virtual const float64 *get_total_fract_root_length()                 const=0; //061208
 public: // Stress
   //180508  mutable CORN::Statistical_running_index
   mutable CORN::Statistical_sample_cumulative<float64,float64> water_stress_stats;                  //180408_010726
   //mutable float64 water_stress_index_test;
 protected:
   float64 process_transpiration_m
      (float64 &limited_pot_transpiration)                        modification_; //051118
      // returns act_transpiration
      // soil_salinity is not const because we update the osmotic potential
   virtual float64 global_solar_rad_intercepted_green_canopy()          const=0; //081105
   virtual float64 get_adjusted_ET_crop_coefficient()                   const=0; //080808
 public:  // 'structors
   Crop_common(Crop_parameters *parameters,bool owns_parameters
      ,const Vapor_pressure_deficit_daytime &daytime_vapor_pressure_deficit      //140812
         //now just providing daytime_vapor_pressure_deficit                     //140812
      ,Soil_interface *soil                                                      //160415
      ,modifiable_ Crop_CO2_response         *Crop_CO2_response_given_optional   //160418
      ,const CORN::date32 &today_                                                //170525
      ,CORN::Unidirectional_list &performable_operations
      ,float64 param_dry_soil_root_activity_coef_                                //170518
      ,float64 param_saturated_soil_root_activity_coef_);                        //170518
   virtual ~Crop_common();                                                       //040121
 public: // Simulation_element method implementation
   virtual bool start_day()                                       modification_; //130903_051028
   /*171212 Not needed, no specialization
   virtual bool initialize()                                    initialization_; //031130
   virtual bool start()                                           modification_; //130903_051028
   virtual bool end_day()                                         modification_; //150930
   */
   /*171212 Moved to Crop_element
   virtual bool start_period(nat8 period)                         modification_; //160613
   virtual bool end_period(nat8 period)                           modification_; //160613
   */
 public:
   virtual float64 update_pot_evapotranspiration                                 //010910
      (float64 pot_ref_evapotranspiration);                                      //121125
      // probably could be moved to Transpiration_dependent_growth_common
   float64 intercept_precipitation(float64 water_reaching_plant)  modification_; //140230
   RENDER_INSPECTORS_DECLARATION;                                                //150916

 protected:
//   virtual float64      get_fract_canopy_cover()                        const=0; //140320
   virtual float64      get_fract_canopy_cover_green()                        const=0; //140320
   virtual float64      get_fract_canopy_cover_total()                        const=0; //140320
};
//______________________________________________________________________________
} // namespace CropSyst
#endif

