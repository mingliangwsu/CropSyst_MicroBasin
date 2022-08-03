#ifndef canopy_cover_continuumH
#define canopy_cover_continuumH
#include <ostream>
#include <assert.h>
#include "crop_param_struct.h"
#include "canopy_cover_curve.h"
#define Ref_to_const_float         const float64 *

namespace CropSyst
{  //forward decl
   class Canopy_growth_cover_based;
   class Phenology_interface;
//______________________________________________________________________________
class Canopy_cover_abstract
{protected:  // parameters these may need to be renamed to correspond with CropSyst crop parameters
   const Crop_parameters_struct::Phenology &phenology_parameter;
   float64 parameter_begin_maturity_deg_day;                                     //141106
   const float32 & /*float64*/ parameter_thermal_time_season_end;                                    //171221
   const Crop_parameters_struct::Canopy_growth_cover_based &canopy_parameter;
   const Crop_parameters_struct::Morphology  &canopy_growth_common_parameter;
 protected: // references to other objects
   const Phenology_interface &phenology;                                         //110824
   bool  is_fruit_tree;
 protected: // state maintained by this
   float64 global_solar_rad_intercepted_green_canopy;             //fraction     //110906 was solar_rad_intercepted_fraction
   float64 global_solar_rad_intercepted_green_canopy_yesterday;   //fraction     //110906 was solar_rad_intercepted_fraction_yesterday
   float64 PAR_solar_rad_intercepted_green_canopy;                //fraction
   float64 cover_latest_vegetative;                                              //171221
 public:
   Canopy_cover_abstract
      (const Crop_parameters_struct::Canopy_growth_cover_based  &_canopy_parameter
      ,const Crop_parameters_struct::Morphology &_canopy_growth_common_parameter
      ,const Crop_parameters_struct::Phenology  &_phenology_parameter
      ,const Phenology_interface                &_phenology                      //110824
      ,bool _is_fruit_tree);                                                     //120510
 public:
   virtual bool update_cover(float64 LWP_yesterday)             modification_=0;
   inline virtual float64 get_PAR_solar_rad_intercepted_green_canopy()     const { return PAR_solar_rad_intercepted_green_canopy; }
   inline Ref_to_const_float ref_global_solar_rad_intercepted_green_canopy() const { return &global_solar_rad_intercepted_green_canopy; }
   inline float64 &modifiable_ref_global_solar_rad_intercepted_green_canopy() modification_ { return global_solar_rad_intercepted_green_canopy; } //110824
   inline float64 get_global_solar_rad_intercepted_green_canopy()          const { return global_solar_rad_intercepted_green_canopy; }
   float64 set_global_solar_rad_intercepted_green_canopy(float64 global_solar_rad_intercepted_green_canopy)  modification_; //130520
   virtual bool start_dormancy()                                  modification_; //110406
   inline virtual bool start_season()                             modification_;
   virtual bool start_senescence()                modification_ { return true; } //141120
      // implemented in Canopy_cover_reference (not used in actual)
   virtual bool start_culminescence()             modification_ { return true; } //141124
   virtual bool respond_to_clipping()                             modification_; //110421
   virtual bool start_day()                                       modification_; //110601
   void dump_headers(std::ostream &strm,const char *prefix)               const;
   virtual void dump(std::ostream &strm)                                  const;
};
//______________________________________________________________________________
class Canopy_cover_reference
: public Canopy_cover_abstract
{protected:
   // In this case:
   //    solar_rad_intercepted_fraction            is PotentialFractionSolarRadiationIntercepted
   //    PAR_intercepted_fraction                        is PotentialFractionPARIntercepted
   //    solar_rad_intercepted_fraction_yesterday  is PotentialFractionSolarRadiationIntercepted(DAP - 1)
   #define unstressed_global_solar_rad_intercepted_green_canopy            global_solar_rad_intercepted_green_canopy
   #define unstressed_global_solar_rad_intercepted_green_canopy_yesterday  global_solar_rad_intercepted_green_canopy_yesterday
 public:
   Canopy_cover_curve *canopy_cover_curve;                                       //171220
   //171220 Canopy_cover_curve_2013 canopy_cover_curve;                          //130610
 protected:
   float64 canopy_senescence_rate;
   float64 cover_unstressed_green;
 public:
   float64 expansion_potential_today;                                            //110601
   float64 expansion_potential_yesterday;                                        //101030
 public:
   Canopy_cover_reference
      (const Crop_parameters_struct::Canopy_growth_cover_based &_canopy_parameter
      ,const Crop_parameters_struct::Morphology &_canopy_growth_common_parameter
      ,const Crop_parameters_struct::Phenology  &_phenology_parameter
      ,const Phenology_interface             &_phenology                         //110824
      ,bool                                   _is_fruit_tree);                   //120510_101030
   virtual bool update_cover
      (float64 leaf_water_potential_yesterday_NA_this_version =0) modification_;
 private:
   float64 calculate(float64 cumulative_thermal_time)                     const;
      // rename to calculate
 public:
   bool initialize()                                            initialization_; //131206_110628
      // value of 1.0 disables CO2 response
   virtual bool start_day()                                       modification_; //110601
   virtual bool start_season();
   inline virtual bool start_senescence()                         modification_  //141120
      {  return canopy_cover_curve->start_senescence();}
   virtual bool start_dormancy()                                  modification_; //110901
   void dump_headers(std::ostream &strm)                                  const;
   virtual void dump(std::ostream &strm)                                  const;
};
//______________________________________________________________________________
class Canopy_cover_actual
: public Canopy_cover_abstract
{
 protected:
   // In this case:
   //    solar_rad_intercepted_fraction   is FractionSolarRadInterceptedTotalCanopy
   //    PAR_solar_rad_intercepted_green_canopy               is FractionPARIntercepted
//   const Transpiration_actual &transpiration_actual;
 protected: // state maintained by this.
   float64 global_solar_rad_intercepted_total_canopy;                            //110906 // was FractionSolarRadInterceptedTotalCanopy
 protected: // References to other objects;
   Canopy_cover_reference &canopy_cover_reference;
   const float64 &water_stress_index_yesterday;                                  //110902
 protected: friend class Canopy_growth_cover_based;
   bool first;
 public:
   float64 cover_attained_max;                                                   //110825 was maximum_canopy_cover_reached
   float64 cover_to_lose_total;

 public:
   Canopy_cover_actual
      (const Crop_parameters_struct::Canopy_growth_cover_based &_canopy_parameter
      ,const Crop_parameters_struct::Morphology  &_canopy_growth_common_parameter
      ,const Crop_parameters_struct::Phenology   &_phenology_parameter
      ,const Phenology_interface             &_phenology                         //110824
         //In VIC, this should be Phenology_actual
      ,bool                                   _is_fruit_tree                     //110422
      ,const float64                         &_water_stress_index_yesterday      //110902
      , Canopy_cover_reference               &_canopy_cover_reference);

   virtual bool start_day()                                       modification_; //110601
   virtual bool start_season();
   virtual bool update_cover(float64 LWP_yesterday)               modification_;
   virtual bool start_dormancy()                                  modification_; //110406
   virtual bool respond_to_clipping()                             modification_;
   virtual bool start_culminescence()                             modification_  //141124
      // rename to initiate_culmination() 171221
      {
         /*171221
         return canopy_cover_reference.canopy_cover_curve->set_cover_at_max_canopy
            (cover_latest_vegetative); //171221
         */
         /*171221
         return canopy_cover_reference.canopy_cover_curve->set_CC_at_max_canopy
            (global_solar_rad_intercepted_green_canopy_yesterday);
         */
         return true;
      }
   inline float64 get_global_solar_rad_intercepted_green_canopy_yesterday()const { return global_solar_rad_intercepted_green_canopy_yesterday; }
   inline float64 get_global_solar_rad_intercepted_total_canopy()          const { return global_solar_rad_intercepted_total_canopy; }
   float64 calc_leaf_area_index()                                         const;
   float64 calc_green_area_index()                                        const; //110901
   float64 calc_peak_leaf_area_index()                                    const; //110901
   void dump_headers(std::ostream &strm)                                  const;
   virtual void dump(std::ostream &strm)                                  const;
 private:
   float64 calc_XXXX_area_index(float64 fract_intercept)                  const; //110901
};
//______________________________________________________________________________
} // namespace CropSyst
#endif

