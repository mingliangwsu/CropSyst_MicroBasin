#ifndef evaporation_without_vapor_pathH
#define evaporation_without_vapor_pathH
#ifdef OLD_EVAPORATE
#include "soil/evaporation_abstract.h"
#else
#include "soil/soil_evaporator.h"
#endif
#include "soil/hydrology_finite_diff.h"
//______________________________________________________________________________
class Soil_evaporation_without_vapor_path
//160804#ifdef OLD_EVAPORATE
//160804: public Soil_evaporation_abstract
//160804#else
: public Evaporator_soil
//160804#endif

// 160525  I should not derived this from CS::Evaporator


{  // This class works with millimeter
 private:  // references
   modifiable_ Soil_hydrology_finite_difference &hydrology_FD;    // Owned by the soil class
/*//160804
   #ifdef OLD_EVAPORATE
   mutable const Soil_hydraulic_properties_interface   *soil_hydraulic_props;
      // Pointer because may change due to tillage etc.. (owned by soil)
      // Mutable because not an attribute of this evaporation model
      // which simply responds to the current properties.
       const Soil_layers_interface              &soil_layers;  // Not const because we adjust the number of effective layers
   const float64                                &atmospheric_water_potential;                        // kg.s/m^4   Maintained by infiltration model.

   #else
*/
   //160606 references moved to Evaporator_soil
   cognate_ float64  atmospheric_water_potential;           // kg.s/m^4   Maintained by infiltration model.
      //160606 atmospheric_water_potential should actually be a biometeorology element
//160804   #endif
 private:  //
   bool     first_day;                                                           //090417
   bool     period_evaporation_done;                                             //090417
   float64  evaporation_depth;                                                   //090504
   float64  sum_evaporation_mm_ts;             // needs units ?units? I am pretty sure this is for the current wetted period (it is not cummulative evaporation) 090417
   float64  max_current_period_evaporation;                                      //090417
   float64  absolute_max_evaporation;                                            //090417
   float64  old_WC;                                                              //090417
   float64  mulch_cover_fraction;                                                //100610
 public :
   Soil_evaporation_without_vapor_path
      (

      //160804#ifndef OLD_EVAPORATE
       //160717 modifiable_ Physical::Water_depth       &evaporation_potential_remaining_, //160609
      modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining_, //160717
      //160804#endif
       const Soil_layers_interface             &soil_layers
      ,const Soil_hydraulic_properties_interface   *soil_hydraulic_props
      ,Soil_hydrology_finite_difference        &hydrology
      //160804#ifdef OLD_EVAPORATE
      //160804,const float64                           &atmospheric_water_potential
      //160804#endif
      );
 public : // processing
   void initialize(uint8 number_real_plus_extended_layer)          modification_;
   inline void know_mulch_cover_fraction                                         //100610
      (float64 new_mulch_cover_fraction)                           modification_
      { mulch_cover_fraction = new_mulch_cover_fraction; }
   float64 evaporate
      (float64 &flux_mm                // modified
      , Seconds time_step
      , Hour    hour_0based
      , float64 pot_evap_mm_day /* mm/day */ )                     modification_;
      // Determine evaporation for the timestep and
      // deducts the water from the soil.
      // Sets up vapor_path
      // Returns actual evaporation in mm
      // Note that pot_evap_mm_day should be set to 0 if ponding or snow
   /*//160804
   #ifdef OLD_EVAPORATE
   inline void know_soil_hydraulic_properties                                    //090108
      (const Soil_hydraulic_properties_interface *_soil_hydraulic_props) mutates_
      { soil_hydraulic_props = _soil_hydraulic_props; }
      // Generally hydraulic properties (initial values provided by the constructor) don't change,
      // however events may change (perhaps temporarily) the soil properties. 090108_
   #else
   */
      void know_atmospheric_water_potential(float64 atmospheric_water_potential_) cognition_
         { atmospheric_water_potential = atmospheric_water_potential_; }
   //160804#endif
 private:
   float64 calc_actual
      ( Seconds time_step   /* May need to be integer */
      , Hour    hour
      , float64 daily_pot_evap_m_ts /* m/hr */ )                           const;
   void subtract_water_from_layer
      ( float64 &evaporation_to_subtract
      , nat8 i)                                                    modification_;
      /*appears to be layer but check that it's not node */
};
//_2009-01-06_______________________class_Soil_evaporation_without_vapor_path__/
#endif

