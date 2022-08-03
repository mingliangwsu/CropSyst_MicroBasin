#ifndef crop_interfacedH
#define crop_interfacedH
#include "corn/const.h"
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "common/soil/SCS/SCS.h"
#include "common/residue/residue_decomposition_param.h"
#include "mgmt_types.h"
#include "crop/crop_N_interface.h"                                               //170220LML

//______________________________________________________________________________
namespace CropSyst {
   class Phenology_interface;                                                    //130903
   class Auto_clip_biomass_mode;
   class Harvest_or_clipping_operation_struct;                                   //140811
   class Crop_nitrogen_mass_balancer;
} // namespace CropSyst
class Residues_interface;


#include "options.h"

#include "crop/crop_types.h"
#include "corn/chronometry/date_types.hpp"
#include "common/soil/SCS/SCS.h"
#include "crop/growth_stages.hpp"
#include "common/weather/parameter/WP_air_temperature.h"
#include "corn/chronometry/time_types.hpp"
#include "CS_suite/observation/CS_observation.h"

/* This class defines all the methods for
   connecting a crop model with CropSyst framework.                              031119

   In order to incorporate a new crop model into
   the CropSyst frame work, it must be derived from this
   class and provide overrides to all these methods.
*/
//______________________________________________________________________________
namespace CORN
{
   class Data_record;       // Forward declaration
}
//______________________________________________________________________________
class Residue_decomposition_parameters;                                          //060219
namespace CS {  // only V4
   class Desired_variables; // Forward declaration
}
class Crop_nitrogen_state_abstract;
class Common_simulation_log;                                                     //050725
class Residues_interface;                                                        //060331

namespace CropSyst {
//______________________________________________________________________________
class Crop_interfaced
{
 protected:  // The following are for clipping events
   nat16          consecutive_low_growth_days_for_clipping;                      //970219
   nat16          days_since_last_clipping;                                      //970305
   float64        max_daily_GAI_rate;                                            //970306
   bool           automatic_clipping_enabled;                                    //980724
 protected: // output control                                                     //000629
   bool           structure_defined;                                             //030715
 protected: // External objects frequently accessed.
   const Air_temperature_average *air_temperature_avg;                           //141208
 public:  // The following accessors are used for processing
   Crop_interfaced
      (const Air_temperature_average *air_temperature_avg);                      //141208
   inline virtual ~Crop_interfaced() {}                                          //070221
public:
   virtual bool get_name(modifiable_ std::wstring &active_crop_name)    const=0; //150720
   virtual void *get_association_for_events()                           const=0; //060411
      // Events associated with a crop are (In the case of CropSyst crops ) associated with the crop parameters object.
      // This is used as the ID to search in the events lists for synchronizations.
      // So this (at this time) doesn't need to return Crop_parameters (It could be a nat32 ) representation of the pointer.
   virtual CropSyst::Phenology_interface &mod_phenology()                    =0; //130903
   virtual const CropSyst::Phenology_interface &ref_phenology()         const=0; //130903
   virtual bool         is_terminate_pending()                          const=0; //040514
   #if (CROPSYST_VERSION == 4)
   virtual bool         is_fallow_deprecated()                          const=0;
   #endif
   virtual bool is_orchard()                                     affirmation_=0; //150720
//171006   virtual float64      get_fract_canopy_cover()                        const=0;
   virtual float64      get_fract_canopy_cover_total()                        const=0; //171006
   virtual float64      get_fract_canopy_cover_green()                        const=0; //171006
   virtual float64      get_leaf_water_pot()                            const=0; //071115
   virtual void        *get_unique_identifier()                         const=0;
   virtual Crop_model   get_crop_model()                                const=0;
   virtual float64      get_canopy_resistance()                         const=0;
public: // setters
   virtual bool         set_fallow_deprecated(bool fallow)                   =0;
   virtual bool         set_no_more_clippings_this_season()     modification_=0; //040721
   virtual bool         get_no_more_clippings_this_season()             const=0; //040721
   virtual bool         end_season_if_no_dormancy()                          =0; //050818
   virtual bool         end_season()                            modification_=0; //160629
      // This is provided for compatibility with CropGro
   virtual void         set_terminate_pending()                              =0; //040514
   virtual int16        get_days_after_flowering()                      const=0; //040830
public:  // The following accessors are used only for output
         // Some are report details, some are runtime etc.
   virtual float64      get_pot_transpiration_m(bool CO2_adjusted)      const=0; //151031
#ifdef VIC_CROPSYST_VERSION
   virtual float64      get_intercepted_precipitation_m_stored()        const=0; //180523LML
   inline virtual bool  set_intercepted_precipitation_m_stored(float64 intercepted_water_m)  modification_=0; //180523LML
#endif

   virtual float64      get_adjusted_ET_crop_coefficient()              const=0; //150630RLN
   virtual float64     get_intercepted_precipitation_m()                const=0; //160419
   virtual const char  *get_description()                               const=0;
   virtual const char  *describe_growth_stage()                         const=0;
   virtual float64      get_recorded_root_depth_m()                     const=0;
   #ifdef NITROGEN
   virtual float64      get_N_mass_canopy_kg_m2(bool recorded_before_harvest) const=0; //070209
   #endif
   virtual float64      get_root_length_m()                             const=0;
   virtual float64      get_plant_height_m()                            const=0;
   virtual float64      get_active_fract_root_length_m(uint8 sublayer)  const=0;
   virtual float64 const *get_total_fract_root_length_m()               const=0;
   virtual float64      get_latest_yield_kg_m2()                        const=0;
   // This is the yield from the latest harvest event.
   virtual const CORN::Date_const &get_planting_date()                  const=0; //041205
   virtual const CORN::Date_const &get_restart_date()                   const=0; //041205
   virtual const CORN::Date_const &get_emergence_date()                 const=0;
   virtual const CORN::Date_const &get_flowering_date()                 const=0;
   virtual const CORN::Date_const &get_tuber_init_date()                const=0; //081111
   virtual const CORN::Date_const &get_grain_filling_date()             const=0;
   virtual const CORN::Date_const &get_maturity_date()                  const=0;
   virtual const CORN::Date_const &get_harvest_date()                   const=0;
   virtual const CORN::Date_const &ref_GAI_max_date()                   const=0; //180413
   //180413 renamed virtual const CORN::Date_const &get_largest_GAI_date()               const=0; //040211
   #ifdef OLD_ORCHARD
   virtual const CORN::Date_const &get_bud_break_date()                 const=0; //081013
   virtual const CORN::Date_const &get_initial_fruit_growth_date()      const=0; //081013
   virtual const CORN::Date_const &get_rapid_fruit_growth_date()        const=0; //081013
   virtual const CORN::Date_const &get_chill_requirement_satisfied_date()const=0; //081013
   #endif
   virtual const CORN::Date_const &get_inactive_begin_date()            const=0; //081013
   virtual const CORN::Date_const &get_inactive_end_date()              const=0; //081013
public:  // The following are for report details only,
         // Eventually they may be replaced by data_record I/O
   virtual float64 get_accum_degree_days
      (bool adjusted_for_clipping)                                      const=0; //040830
   #ifdef CROP_ORCHARD
   virtual int16 get_fruit_chill_hours_remaining()                      const=0; //080910
   virtual bool is_fruit_harvestable()                                  const=0; //081204
   virtual float64 get_fruit_dry_biomass_kg_ha()                        const=0;
   virtual float64 get_orchard_solid_canopy_interception()              const=0; //081020
   virtual float64 get_orchard_shaded_area_GAI()                        const=0; //081020
   virtual float64 get_orchard_canopy_porosity()                        const=0; //081020
   #endif
   virtual float64 get_dry_biomass_kg_ha()                              const=0;
   virtual float64 get_live_green_canopy_biomass_kg_ha()                const=0; //060313
   virtual float64 get_act_root_biomass_kg_ha()                         const=0;
   virtual float64 get_canopy_biomass_kg_ha()                           const=0;
   virtual float64 get_VPD_daytime()                                    const=0;
   virtual float64 get_VPD_daytime_mean()                               const=0;
   virtual float64 get_intercepted_PAR_MJ_m2()                          const=0;
   virtual float64 get_intercepted_PAR_accum_MJ_m2()                    const=0;
   virtual float64 get_intercepted_PAR_season_accum_MJ_m2()             const=0;
   virtual float64 get_peak_LAI(bool reported)                          const=0; //040929
   virtual float64 get_total_season_collected_biomass_kg_m2()           const=0; //040728
   virtual float64 get_total_season_biomass_production_kg_m2()          const=0; //040719
   virtual const Crop_nitrogen_interface *get_nitrogen()                const=0; //050722
   virtual float64 update_root_depth
      (float64 soil_rooting_depth,float64 total_soil_depth)     modification_=0; //981023
 public: // data record output
   #if (CROPSYST_VERSION==4)
   virtual bool setup_structure
      (CORN::Data_record &data_rec
      ,bool for_write
      ,const CS::Desired_variables &desired_vars)               modification_=0;
   #endif
 public:  // The following are used for accumulation and/or output
   virtual float64 get_act_transpiration_m()                            const=0;
   virtual float64 get_act_uptake_m()                                   const=0; //160414
   virtual float64 get_recorded_act_transpiration_m()                   const=0;
   virtual float64 get_reported_harvest_index()                         const=0; //120117
   virtual float64 get_reported_N_mass_yield()                          const=0; //160628
   virtual float64 get_canopy_biomass_kg_m2()                           const=0;
   virtual float64 get_act_root_biomass_kg_m2()                         const=0;
   virtual float64 calc_root_biomass
      (float64 *output_root_biomass_by_layer=0)                         const=0; //071215
   virtual float64 get_LAI(bool from_canopy)                            const=0;
   virtual float64 get_GAI(nat8 include_GAI)                            const=0;
   virtual float64 get_GAI_today()                                      const=0;
   virtual float64 get_temperature_stress()                             const=0;
   virtual float64 get_water_stress()                                   const=0;
   virtual float64 get_water_stress_index()                             const=0;
   virtual float64 get_water_stress_index_mean()                        const=0;
   virtual float64 get_temperature_stress_index()                       const=0;
   virtual float64 get_temperature_stress_index_mean()                  const=0;
   virtual float64 get_overall_growth_stress()                          const=0;
   virtual float64 get_C_mass_canopy()                                  const=0; //110915
   virtual float64 get_C_mass_roots()                                   const=0; //110915
 public:  // The following are parameter accessors
   inline virtual int32    param_LADSS_land_use_ID()            const{return 0;}  //040217
          virtual Land_use param_land_use()                             const=0;
          virtual float64  param_emergence_deg_day()                    const=0;
          virtual float64  param_max_canopy_deg_day()                   const=0; //140512
   inline virtual float64  param_wilt_leaf_water_pot()        const{return 0.0;}
          virtual float64  param_base_temp()                            const=0;
   #ifdef RESIDUES
          virtual Residue_decomposition_parameters &get_residue_decomposition_parameters() const=0; // Derived classes may return 0 if not simulating residue //060219
   #endif
 public: // The following parameters are used for scaling runtime graph
          virtual float64  param_max_LAI()                              const=0;
   inline virtual float64  param_max_root_depth_m()           const{return 2.0;}
      // Derived classes may override param_max_root_depth_m if available
      // it is used primarily for fastgraph scaling.
   virtual Harvested_part get_harvested_part()                          const=0; //170820
 public: // The following are for LADSS only
   virtual int32 get_LADSS_land_use_ID()                                const=0; //040923
   virtual const char *get_sowing_event_ID()                            const=0; //051129
 public:  // The following are used to implement operations and events that remove biomatter from the plant
   virtual                                                                       //040621
      Crop_mass_fate_biomass_and_nitrogen *                                      //070625
      process_biomass_fate
         (Biomass_fated_cause fated_cause
         ,Harvest_amount_mode harvest_amount_mode                                //050822
         ,float64 remove_amount_kg_m2                                            //050822
         ,float64 retain_GAI                                                     //050822
         ,float64 retain_biomass_kg_m2                                           //110603
         ,const Biomass_fate_parameters  &biomass_fate_parameters
         ,bool terminate                                                         //040817
         ,float64 yield_now // from harvest index, may be 0.0
         ) = 0;
      // This moves plant biomass to various pools, harvest yield, residue, loss etc..
      // Returns the fate of the material if processed otherwise 0 (call must delete the returned fate object)
   virtual void commit_biomass_fate() = 0;                                       //040610
      // This should be called daily, it checks if there is any biomatter fate and generates a log
   virtual const Crop_mass_fate *get_biomass_fate_today_record()        const=0; //040624
   virtual Crop_mass_fate *get_biomass_fate_season()                    const=0; //040624 //150803 was not const (GCC may complain)
public:  // The following are processes used by the calling program
   virtual float64 intercept_precipitation(float64 water_reaching_plant) modification_=0; //140320
      /// Deducts from the water reaching the plant, water intercepted
      /// by the plant.
      /// (I need to check the fate of this intercepted water
      //   is it just lost?)
      /// \return water not stored on plant.
   virtual                                                                       //991029
      Crop_mass_fate_biomass_and_nitrogen *                                      //070625
      clip_biomass
      (Harvest_amount_mode harvest_amount_mode                                   //050822
      ,float64 remove_amount_kg_m2                                               //050822
      ,float64 min_retain_GAI                                                    //051102
      ,float64 min_retain_biomass_kg_m2                                          //110603
      ,const Biomass_fate_parameters &biomass_fate_parameters
      ,Biomass_fated_cause fated_cause);                                         //040610
      // Returns the fate of the biomass (must be deleted by the caller)         //060323
   virtual bool respond_to_clipping()                           modification_=0; //051103
   bool check_for_automatic_clipping                                             //990913
      (const CropSyst::Auto_clip_biomass_mode &clip_biomass_op                   //970521
      ,float64 remove_amount_kg_m2                                               //050822
      ,bool   clip_now_or_never                                                  //980724
      #if (CS_VERSION==4)
      ,Common_simulation_log *log
      #else
      // eventually all versions will use explainations
      #endif
      );                                              //050929
      // Returns true if clipping actually performed.                            //990913
   virtual bool sow(bool fall_sowing) = 0;                                       //140813_020220
   virtual bool start_day()                                     modification_=0; //130903_040205
   virtual bool end_day()                                       modification_=0; //130903_070221
   virtual bool process_day()                                   modification_=0; //150611_020711
   #ifdef NITROGEN
   virtual void set_automatic_nitrogen_mode(bool enable) = 0;                    //040525
   #endif
   virtual Crop_mass_fate_biomass_and_nitrogen *harvest                          //070625
      (float64 remove_amount_kg_m2                                               //050822
      ,const CropSyst::Harvest_or_clipping_operation_struct *harvest_or_clipping_params
      ,bool terminate                                                            //140811
      ) = 0;     //051105
      // Returns the fate of the biomass if it could harvest                     //060323
      // otherwise 0 (must be deleted by the caller)
   virtual Crop_mass_fate_biomass_and_nitrogen *harvest_crop                     //070625
      (Harvest_amount_mode harvest_amount_mode                                   //050822
      ,float64 remove_amount_kg_m2                                               //050822
      ,float64 retain_GAI                                                        //050822
      ,const Biomass_fate_parameters &harvest_biomass_fate_parameters
      ,bool terminate) = 0;
      // Returns the fate of the biomass if it could harvest                     //060323
      // otherwise 0 (must be deleted by the caller)
      virtual float64 damage_GAI(float64 GAI_damage)            modification_=0; //151226
   virtual float64  update_pot_evapotranspiration(float64 pot_ref_evapotranspiration_m) = 0;     //010910
   virtual float64 est_degree_days_X_days_from_now                               //000330
      (const CORN::Date_const & today, CORN::Days days_from_now)        const=0; //010202
      // This returns an estimate (in this case the actual)
      // of the thermal time the crop will have in the specified
      // number of days from the current date.
   virtual bool initialize()                                    initialization_; //151005
   virtual bool track_nitrogen_mass_balance
      (CropSyst::Crop_nitrogen_mass_balancer *_mass_balance)            const=0; //070220
public: // optional setup
   inline virtual void know_event_log(Common_simulation_log *_event_log)      {} //050725
      // Use set_event_log if you want to record crop event and change of status.
      // This function is usually called once immediately after instanciating the crop object,
      // but it can be called at any time when you want to start logging events.
      // Pass 0 to disable logging.
      // Derived classes do not have to override this method if they don't want to support logging.
   inline virtual void know_residues(Residues_interface *residues)            {} //060531
      // This method allows the crop to interact and exchange material with residue pools.
      // This function is usually called once immediately after instanciating the crop object. //050725
      // This is optional, it allows the decomposing canopy submodel to be enabled.
      // In CropSyst, if the crop does not know about residues,
      // scenesced biomass in the plant canopy will not decompose while the plant is alive (I.e. for perennials)
      // (although biomass will be available for decomposition on crop termination.)
public:
   // The following methods provided daily parameters required by optional submodels
   // When using any of these models,
   // the respective methods must be called prior to calling process().

   #ifdef DIRECTED_IRRIGATION
   virtual bool know_directed_irrigation_soil_wetting
      (const Directed_irrigation_soil_wetting *_soil_wetting)      cognition_=0;
   #endif
   virtual float64 know_snow_pack_thickness(float64 snow_pack_thickness_) cognition_=0;  //161110
 public: // The following are added from intercropping
   inline virtual Crop_interfaced *get_predominant_crop() modification_{return this;} //130715
   inline virtual Crop_interfaced *get_secondary_crop() modification_{return 0;} //130715
 public: // The following are added for REACCH and OFOOT and will probably be in V5
  RENDER_INSPECTORS_DECLARATION_PURE;                                            //150929
};
//______________________________________________________________________________
} // namespace CropSyst
#endif

