#ifndef residues_commonH
#define residues_commonH
#include "common/residue/residues_interface.h"

#ifndef statsH
#     include "corn/math/statistical/stats.h"
#endif
#include "common/weather/parameter/WP_air_temperature.h"
#include "common/weather/parameter/WP_wind_speed.h"

class Biomass_decomposition_parameters;
namespace Physical
{
   class Water_depth;                                                            //160412
}
//______________________________________________________________________________
class Residues_common
: public implements_ Residues_interface
// NYI public extends_ Simulation_element_abstract
, public extends_ CS::Evaporator_intervals                                       //160717_160523
{
 protected:
   Soil_interface                &soil;                                          //060122
   const Soil_layers_interface   &soil_layers;                                   //060330
   const Air_temperature_average &temperature_air_avg;                           //150427
   const Wind_speed              &wind_speed;                                    //150427
   // external references
   const CORN::date32                 &today;                                    //170525
      // today is currently only used for logging
   std::ostream                  *detail_log;                                    //020306
   // CropSyst has the option of recording details
   // such as when residue pools are exhausted.
   // This can be initialized with 0 if we don't want
   // this recording.
 private: // references to other objects
   cognate_ float64                   fract_canopy_cover;                        //160523
 public:
   float64  stubble_contact_fraction;                                            //060322
   float64  flat_surface_contact_fraction;                                       //060322
   float64  subsurface_contact_fraction; // Always 1.0                           //060322
   float64  manure_surface_contact_fraction;                                     //090225
   // The totals here are totals or current accumulated values for all the pools for the day  980718
   float64  total_residue_area_index_both_flat_and_standing;                     //000609
   float64  total_residue_area_index[OM_POSITION_COUNT];                         //000609
      // Actually only interested in flat and standing stubble. VB has this as Total_surface_residue_Area_index
   float64  total_fract_ground_cover[OM_POSITION_COUNT];   // Actually only interested in flat and standing stubble.
 public: // ??
   float64  curr_water_hold;      // m3/kg
      // curr_water_hold is probably obsolete although
      // it is used for soil abiotics layer 0, although I am not sure
      // if layer 0 (surface is actually used)
      // I am leaving this for now until I can check if this layer 0 is actually used anywhere
      // (microbasin?)
   float64  water_storage;          // m                                         //170104
   float64  report_ground_cover;    // fraction                                  //160627
   float64  report_surface_biomass; // kg/m2                                     //160627

   float64 report_plant [OM_POSITION_COUNT]; // subsurface flat stubble attach   //180108
   float64 report_manure[MANURE_POSITION_COUNT]; // subsurface surface           //180108
   float64 report_plant_surface;                                                 //180108

#ifdef RESIDUE_WC_FIX
090302 RLN Dont delete. This should be correct

   float64  water_from_change_in_biomass;                                        //090224
                  // m When residue is redistributed/removed by tillage/residue operation
                           // we need to account for the corresponding moisture loss
#endif
   float64 interception;               // m
   soil_layering(horizons);                                                      //9702??
   float64 shallow_horizon_thickness;                                            //990217
   float64 deep_horizon_thickness;                                               //990217
 public: // structors
   Residues_common
      (Soil_interface                     &soil                                  //060122
      ,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining_      //160717
      ,const Air_temperature_average      &temperature_air_avg                   //150427
      ,const Wind_speed                   &wind_speed                            //150427
      ,const CORN::date32                 &today                                 //170523
      ,std::ostream                       *detail_log);                          //020307
 public: // Simulation element implementation
   virtual bool start_day()                                        modification_;//160523
   virtual bool end_day()                                          modification_;//160628
      // Needed for multiple inheritence
 public:
   void identify_residue_horizons();                                             //981001
 protected:
      virtual bool clear_totals();                                               //060228
      virtual void update_totals_all();
   bool has_such_horizon(Residue_horizons search_for_horizon)       affirmation_;//981018
 public:
   virtual void update_totals_sum_pools() = 0;
   virtual bool clear_all()                                        modification_;//160126
 public: // Accessors implemented in derived classes
   virtual float64 get_total_surface_biomass()                             const = 0; //011011
   virtual float64 get_total_fract_ground_cover(nat32 include_position)    const;//060328
   virtual float64 get_biomass_output(nat32 include_positions,nat32 include_residue_types) const = 0;
 public: // Accessors from Residue abstract
   inline virtual float64 get_pot_evaporation()                            const
      { return evaporation_potential.sum(); }                                    //160719
   virtual float64 calc_evaporation_potential(nat8 interval)        calculation_;//160804_160603
   inline virtual float64 get_act_evaporation()                            const { return evaporation_actual.sum(); } //160523
   inline virtual float64 get_interception()                               const { return interception; }
   inline virtual float64 get_curr_water_hold()                            const { return curr_water_hold; }
   inline virtual float64 get_water_storage()                              const { return water_storage; }     //170104
   inline virtual float64 get_surface_depth()                              const { return get_depth(); }                                    //990216
   inline         float64 get_depth()                                      const { return (get_total_surface_biomass() > 0.0) ? 0.1 : 0.0; }//041108
   float64 get_total_area_index(nat32 include_position)                    const;
 public: //  processing
   float64 water_interception
      (float64 water_entering_residues_m)                          modification_;
   virtual float64 take_pool_water(float64 pool_water)            appropriation_;//170104
   inline virtual float64 know_fract_canopy_cover                                //160523
      (float64 fract_canopy_cover_)                                   cognition_
      { return fract_canopy_cover = fract_canopy_cover_; }
   virtual float64 evaporate_interval(nat8 interval)               modification_;//160719
   float64 evaporate_day()                                         modification_;//010910
   virtual float64 evaporate_hour(CORN::Hour hour)                 modification_;//160603
 public:
   float64 thermal_conductance
      (bool     snow_or_residue_cover);
 private: // thermal conductance locals methods
   float64 thermal_conductivity_conduction
      (float64  bulk_density);
   float64 convective_heat_transfer_coef
      ( float64 bulk_density
      , float64 depth
      , bool    snow_or_residue_cover);
   float64 wind_speed_within_residue
      ( float64 bulk_density
      , float64 depth);
   float64 wind_attenuation_coef
      (float64 bulk_density);
   float64 surface_windspeed( float64 depth);
 public: // inspection
   RENDER_INSPECTORS_DECLARATION;                                                //160627
};
//______________________________________________________________________________
#endif

