#ifndef crop_orchard_commonH
#define crop_orchard_commonH
//---------------------------------------------------------------------------
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "options.h"
#include "model_options.h"
#include "crop/crop_param.h"
//180614 #include "crop/canopy_growth_LAI_based.h"
#include "crop/canopy_growth_cover_based.h"
#include "crop/thermal_time.h"

#define OLD_PROVIDE_CANOPY

//______________________________________________________________________________
class Sun;
class Sun_days;
class Sun_hours;
class Weather_hours;
//______________________________________________________________________________

namespace CropSyst {
class Crop_CO2_response;                                                         //130406
//______________________________________________________________________________
class Orchard_interface
{
public:
   interface_ Interception_interface
   {
      virtual float64 update_solid_canopy_interception
         (
         //151027 now member references CORN::DOY doy, float64 fract_cloud_cover
         )                 modification_= 0;
      virtual float64 get_solid_canopy_interception()                      const = 0;
   };
   //_________________________________class_Interception_interface_/
   virtual void expand_canopy(float64 deg_days_today)               modification_= 0; //000718
   virtual float64 update_solid_canopy_interception
      //151027 now member references (CORN::DOY doy, float64 fract_cloud_cover)
      ()                                                                         //151027
      modification_= 0;
   virtual float64 get_solid_canopy_interception()                         const = 0;
   virtual float64 get_canopy_porosity()                                   const = 0; //081103
   virtual float64 get_canopy_shaded_area_GAI()                            const = 0; //081103
   virtual  void set_deg_days_begin_canopy_development                           //071121
      (float64 deg_days_begin_canopy_development)                   modification_= 0 ;

#ifdef OLD_PROVIDE_CANOPY
   virtual Canopy_growth_interface *provide_canopy                               //081103_
      (const CropSyst::Crop_parameters                       &_crop_parameters      // Will be owned by this crop object
      ,const CropSyst::Crop_parameters_struct::Canopy_growth_cover_based     &_parameters
      ,const Thermal_time_immutable &_thermal_time                               //151106
      ,Residues_interface                 *_residues                             //060816
      ,Crop_nitrogen_interface            *_nitrogen                             //060816
      ,const CropSyst::Phenology_interface   &phenology_
      ,const float64                         &ref_water_stress_index_yesterday_
      ,const float64                         &water_canopy_expansion_factor_
      ,CropSyst::Crop_CO2_response        *_CO2_response
      )             provision_=0; //080728
/*
   virtual Canopy_growth_interface *provide_canopy                               //081103_
      (const CropSyst::Crop_parameters                       &_crop_parameters      // Will be owned by this crop object
      ,const CropSyst::Crop_parameters_struct::Canopy_growth_LAI_based     &_parameters
      ,const Thermal_time_immutable &_thermal_time                               //151106
      //151106 ,const Crop_thermal_time_interface_immutable &_thermal_time
      ,Residues_interface                 *_residues                             //060816
      ,Crop_nitrogen_interface            *_nitrogen                             //060816
      ,float64 &_reported_peak_LAI                                               //080725
      ,CropSyst::Crop_CO2_response        *_CO2_response)             provision_=0; //080728
*/
#else
/* now passed as parameter to constructor
   virtual Canopy_growth_interface *know_canopy(Canopy_growth_interface *canopy_) = 0; //180614
   // 180614 show allow user to select canopy model
*/
#endif

   virtual bool is_orchard()                                         affirmation_{ return true; }
   virtual float64 calc_freezing_damage(float64 min_temperature)    calculation_=0;//160531
//_2012-09-09___________________________________________________________________
};
//_____________________________________________________class Orchard_interface_/
class Orchard_common
: public Orchard_interface
{
protected: // crop parameters
   class Tree_canopy_extent
   {
      float64 deg_days_begin_canopy_development;
      float64 deg_days_end_vegetative_growth;
      class Dimension
      {
      private:  // parameters
         float64 initial;
         float64 final;
         float64 &deg_days_begin_canopy_development;
         float64 &deg_days_end_vegetative_growth;
      public:  // state   Currently public, but should make accessors
         mutable float64 current;
      public:
         Dimension
            ( float64 initial_size
            , float64 final_size
            , float64 &deg_days_begin_canopy_development
            , float64 &deg_days_end_vegetative_growth);
         float64 expand(float64 deg_days_today)            modification_;
         inline float64 get()                                  const {return current;};
      }; //________________________________________class Dimension_/
   public: // Currently public, but should make accessors
      Dimension width;
      Dimension breadth;
      Dimension height;
   public: // constructor
      Tree_canopy_extent(CropSyst::Crop_parameters_struct::Canopy_characteristics_hedge_row &canopy_characteristics
         , float64 deg_days_begin_canopy_development
         , float64 deg_days_end_vegetative_growth
         );
      virtual void set_deg_days_begin_canopy_development(float64 deg_days_begin_canopy_development)     ;   //071121
   public:
      void expand(float64 deg_days_today)                  modification_;
   }; //_________________________________________class Tree_canopy_extent_/
public:
   class Interception
   : public Orchard_interface::Interception_interface
   {
   protected:
      float64 slope_radians;        // slope of soil surface
      float64 slope_aspect_from_south_radians; // aspect of the slope terrain  0 is south increasing to west north and east
      float64 row_azimuth_radians;  // 0 is south with west positive (converted from crop layout parameters)
    protected: // references
      const float64     &fract_cloud_cover;
      const CORN::Date_const &today;
   protected:
      CropSyst::Crop_parameters_struct::Layout                            &layout;                 //110218
      CropSyst::Crop_parameters_struct::Canopy_characteristics_hedge_row  &canopy_characteristics; //110218
   protected: // aliases
      Tree_canopy_extent *tree_canopy;
   protected:
      const Sun_days   &sun_days;         // Provided by weather/meteorology
   public:  // constructor
      Interception
         (CropSyst::Crop_parameters_struct::Layout &layout                       //110218
         ,CropSyst::Crop_parameters_struct::Canopy_characteristics_hedge_row
            &canopy_characteristics                                              //110218
         ,float64 slope_percent
         ,float64 slope_aspect_N0_E90_degrees
         ,const Sun_days   &sun_days         // Provided by weather/meteorology
         ,const float64    &fract_cloud_cover
         ,const CORN::Date_const &today);
   private:
      float64 convert_aspect_from_0_north_with_east_90_to_0_south_with_east_90(float64 aspect_N0_E90_degrees) const;
   public:
      virtual float64 update_solid_canopy_interception()        modification_=0;
      inline virtual void know_tree_canopy(Tree_canopy_extent *tree_canopy_)    modification_ {tree_canopy = tree_canopy_; };
   };
   //_________________________________________________Interception_/
public:

   class Canopy_growth_architectural                                             //180614
   #ifdef OLD_PROVIDE_CANOPY
   //180614 : public CropSyst::Canopy_growth_leaf_area_index_based              //081103
   : public CropSyst::Canopy_growth_cover_based  //180614
   #else
   //: public implements_ Canopy_growth_interface
   // Now using XXXX
   #endif
   {
    protected:
      #ifndef OLD_PROVIDE_CANOPY
      const Canopy_growth_interface               &canopy_growth;
         // Not sure yet if needs to be const
      float64 kc;
      #endif
    public: // The following could be local but are stored for output
      mutable float64 shaded_area_GAI; // daily
      mutable float64 porosity;
      mutable float64 solid_canopy_interception;
    public: //construtor
      Canopy_growth_architectural                                                //180614
         (
         #ifdef OLD_PROVIDE_CANOPY
          const CropSyst::Crop_parameters       &crop_parameters_      // Will be owned by this crop object
         ,const /*180614 modifiable_*/  CropSyst::Crop_parameters_struct::Canopy_growth_cover_based &parameters_
         ,const Thermal_time_immutable          &thermal_time_
         ,Residues_interface                    *residues_
         ,Crop_nitrogen_interface               *nitrogen_
         ,const CropSyst::Phenology_interface   &phenology_
         ,const float64                         &ref_water_stress_index_yesterday_
         ,const float64                         &water_canopy_expansion_factor_
         ,Crop_CO2_response                     *CO2_response_
         #else
          const Canopy_growth_interface         &canopy_growth_
         ,float64                                kc_
         #endif
         )     ;
      /*180614
      (const CropSyst::Crop_parameters    &crop_parameters      // Will be owned by this crop object
      ,const CropSyst::Crop_parameters_struct::Canopy_growth_LAI_based &parameters
      ,const Thermal_time_immutable       &thermal_time                          //151106
      //151106 ,const Crop_thermal_time_interface_immutable &_thermal_time
      ,Residues_interface                 *residues                              //060816
      ,Crop_nitrogen_interface            *nitrogen                              //060816
      ,float64 &_reported_peak_LAI                                               //080725
      ,CropSyst::Crop_CO2_response        *CO2_response);                        //080728
      */
    public: // Canopy_growth_leaf_area_index_based overrides
      virtual float64 calc_fract_cover                                           //081022
         (float64 xAI    // Either LAI or  GAI
         ,bool photosynthetic_active_rad_based
         ,bool use_clumping_factor = false
         ,bool record_shading_porosity_interception = true)               const; //081104
      inline virtual float64 get_shaded_area_GAI() const {return shaded_area_GAI;} //081103
      inline virtual float64 get_porosity()        const { return porosity;}     //081103
      inline float64 know_solid_canopy_interception
         (float64 solid_canopy_interception_)                         cognition_
         { return solid_canopy_interception = solid_canopy_interception_; }      //081103
      inline virtual float64 know_LWP_yesterday(float64 LWP_yesterday) cognition_ //110901
         { return 0; } // not used in this model
   };
   //_2008-11-03____________________________________________________

private:
   Tree_canopy_extent tree_canopy;                                               //071117
   Interception *interception; // owned by this provided by main model
   mutable Canopy_growth_architectural *canopy;
   //180614 mutable Canopy_growth *canopy;
   // conceptual, user should be able to select model
   //   mutable Canopy_growth_interface *canopy;                                      //180614_081103
private: // parameters
   const Crop_parameters_struct::Tolerance &tolerance_parameters;                //150913_130406
public:
   Orchard_common
      (const Crop_parameters_struct::Tolerance &tolerance_parameters             //150913_130406
      ,Interception  *interception
      ,Crop_parameters_struct::Canopy_characteristics_hedge_row &canopy_characteristics //110218
      ,float64 deg_days_flowering
      ,float64 deg_days_begin_rapid_fruit_growth);
   virtual void expand_canopy(float64 deg_days_today);                           //000718
   virtual float64 update_solid_canopy_interception()             modification_; //151027

#ifdef OLD_PROVIDE_CANOPY
   virtual Canopy_growth_interface *provide_canopy                               //180614
      (const CropSyst::Crop_parameters       &crop_parameters_      // Will be owned by this crop object
      ,const CropSyst::Crop_parameters_struct::Canopy_growth_cover_based &parameters_
      ,const Thermal_time_immutable          &thermal_time_
      ,Residues_interface                    *residues_
      ,Crop_nitrogen_interface               *nitrogen_
      ,const CropSyst::Phenology_interface   &phenology_
      ,const float64                         &ref_water_stress_index_yesterday_
      ,const float64                         &water_canopy_expansion_factor_
      ,CropSyst::Crop_CO2_response           *CO2_response_)         provision_;


/* 180614 now using canopy curve model
   virtual Canopy_growth_interface *provide_canopy                               //081103
      (const Crop_parameters                       &_crop_parameters
         // Will be owned by this crop object
      ,const Crop_parameters_struct::Canopy_growth_LAI_based &_parameters
      ,const Thermal_time_immutable &_thermal_time                               //151106
      ,Residues_interface                 *_residues                             //060816
      ,Crop_nitrogen_interface            *_nitrogen                             //060816
      ,float64 &_reported_peak_LAI                                               //080725
      ,Crop_CO2_response                  *_CO2_response) provision_;            //080728
*/
#else
/* Now passed to constructor
   virtual Canopy_growth_interface *know_canopy(Canopy_growth_interface *canopy_) //180614
      { canopy = canopy_; }
*/
#endif
   virtual float64 get_solid_canopy_interception()                        const;
   virtual void set_deg_days_begin_canopy_development(float64 deg_days_begin_canopy_development)     ;   //071121
   virtual float64 get_canopy_porosity()                                  const; //081103
   virtual float64 get_canopy_shaded_area_GAI()                           const; //081103
   virtual float64 calc_freezing_damage(float64 min_temperature)   calculation_; //150825_120117
         //130428  was calc_cold_damage
#ifdef NYN
   virtual bool process_day()                                     modification_;
#endif
};
//______________________________________________________________Orchard_common_/
} // namespace CropSyst

#endif

