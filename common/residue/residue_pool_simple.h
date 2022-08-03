#ifndef residue_pool_simpleH
#define residue_pool_simpleH

#if defined(unix) || defined(linux)
// UNIX includes works a little different than DOS/Windows includes
#  include "options.h"
#else
#  include "options.h"
#endif
#include "common/residue/residue_biomatter_profile_simple.h"
#include "common/soil/layering.h"
#include "corn/container/unilist.h"
#ifdef NITROGEN
#  include "mgmt_param.h"
class Organic_matter_simple;                                                     //090416
#else
#  define Organic_matter_simple nat32
#endif

// Note units of N mass per unit area have been factored out of this classes!
// So these classes can be used as kg/m2 or kg/ha as long as they are used consitently
// I am not sure if they can be used as kg.
//______________________________________________________________________________
class Soil_interface;  // forward declaration                                    //060122
class Biomatter_residue_V41;                                                     //090416
class Soil_interface;                                                            //060122
class Soil_layers_interface;                                                     //060122
class Soil_hydrology_interface;                                                  //060122
class Soil_hydraulic_properties_interface;                                       //060122
class Soil_nitrogen_interface;                                                   //060122
class Soil_cropsyst_specific;                                                    //981029
class Residue_biomatter_profile_V41;                                             //090416
class Air_temperature_average;                                                   //150427
//______________________________________________________________________________
class Residue_pool_simple
: public implements_ CORN::Item                                                  //120316
{protected:
   Soil_interface                       &soil;                                   //060122
   const     Soil_layers_interface      &soil_layers;                            //060122
   const     Soil_hydrology_interface   &soil_hydrology;                         //060122
   const     Soil_hydraulic_properties_interface &soil_hydraulic_props;          //060122
   modifiable_ Soil_nitrogen_interface  *soil_nitrogen_modifiable;  // May be 0 if no nitrogen //060122
   const     Air_temperature_average    &temperature_air_avg;                    //150427
 public:
   // The following are for manure only:
#ifdef NITROGEN
   bool                  is_manure;
   Organic_matter_source OM_source;                                              //120316
#endif
   float64               decomposition_constant;                                 //060122
   float64               area_per_mass       ;   // m2/kg?
   float64               fract_ground_cover  ;
 private:
   Residue_biomatter_profile_simple biomatter_profile;                           //060214
 public:
#ifdef NITROGEN
   float64               mineralization      ; // Units of N mass per unit area have been factored out of this function
   float64               N_immobilization;
#endif
 public: // constructors
#ifdef NITROGEN
   Residue_pool_simple // CONSTRUCTOR init_manure
      (Organic_matter_source OM_source
      ,float64 new_shallow_N_content
      ,float64 new_deep_N_content
      ,float64 new_decomposition_constant                                        //060122
      ,float64 new_area_per_mass
      ,nat8  horizons[]
      ,Soil_interface &soil
      ,const Air_temperature_average &temperature_air_avg );                     //150427
#endif
   Residue_pool_simple //    CONSTRUCTOR init_straw
      (bool      standing_stubble
      ,float64 new_surface_mass
      ,soil_sublayer_array_64(new_subsurface_mass)
      #if (CROPSYST_VERSION < 5)
      ,float64 new_water_hold     // m3/kg
      #else
      // Not sure why I had removed this in V5
      #endif
      ,float64 new_N_surface_conc
      ,float64 new_N_subsurface_conc
      ,float64 new_decomposition_constant                                        //060122
      ,float64 new_area_per_mass
      ,nat8  horizons[]                                                          //970522
      ,Soil_interface &soil
      ,const Air_temperature_average &temperature_air_avg);                      //150427
   inline virtual int compare(const CORN::Item &other)        const { return 0;} // Don't currently sort //971213
   void redistribute
      (float64 fract_shallow_to_deep
      ,float64 fract_surface_to_deep
      ,float64 fract_surface_to_shallow
      ,float64 shallow_horizon_thickness                                         //990217
      ,float64 deep_horizon_thickness                                            //990217
      ,const nat8  horizons[]);
   Biomatter_residue_V41 *remove_from_surface(float64 fract_to_remove);          //050303
   void exhaust();                                                               //040523
   inline virtual Residue_biomatter_profile_simple &get_biomatter_profile()
      { return biomatter_profile;}

   #ifdef NITROGEN
   float64 mineralize_surface_residue                                            //981019
      (float64 net_residue_N_mineralized
      ,float64 &NH4_amount_M              //  { kg NH4/m2 }
      ,float64 &NH4_amount_change_M
      ,float64 &soil_ACC_NH4_released_to_atmosphere                              //981211
      ,float64 &mineralized_N_to_organic_matter);                                //011012
   float64 mineralize_subsurface_residue
          (                                                                      //980718
          float64 & residue                                                      //980304
          ,float64 & residue_N_content_SL // kg/m2                               //980304
          ,float64 & N_immobilized                                               //040207
          ,float64 & decomposed           // kg/m2
          ,float64 &soil_ACC_NH4_released_to_atmosphere                          //981211
          ,float64 &biomass_loss_as_CO2                                          //040207
          ,float64 &biomass_transfered_to_OM                                     //040207
          ,float64 & NO3_amount_M         // kg NO3/m2
          ,float64 & NH4_amount_M         // kg NH4/m2
          ,float64 & NO3_amount_change_M                                         //960902
          ,float64 & NH4_amount_change_M                                         //960902
          ,float64 &mineralized_N_to_organic_matter);   // kg/m2                 //011012
   void apportion_mineralized_N                                                  //981018
         (float64 net_residue_N_mineralized
         ,float64 fract_released_to_soil_ammonium
         ,float64 fract_released_to_OM
         ,float64 fract_released_to_atmosphere
         ,float64 &soil_ACC_NH4_released_to_atmosphere // to be modified         //981211
         ,float64 &NH4_amount_M             //{ kg NH4/m2 }
         ,float64 &mineralized_N_to_organic_matter);                             //011012
   #endif
   float64 decompose
      (float64                 water_hold
      ,float64                &decomposed_biomass_recalculated_from_C         //040207
      //170725 #ifdef NITROGEN
      ,Organic_matter_simple    *organic_matter_pool = 0
      //170725 #endif
      );
 public:
   float64 decompose_surface                                                     //040429
      (float64                 water_hold
      //170725 ifdef NITROGEN
      ,Organic_matter_simple *organic_matter_pool
      //170725 #endif
      );
   float64 decompose_subsurface                                                  //040429
      (float64                &decomposed_biomass_recalculated_from_C            //040207
      //170725 #ifdef NITROGEN
      ,Organic_matter_simple   *organic_matter_pool
      //170725 #endif
      );
   inline virtual float64 get_surface_mass()                                     //170104
      { return get_biomatter_profile().get_surface_mass();}
};
//_2005-07-26___________________________________________________________________
#endif
// 060530 330 lines
// 120316 156 lines

