#ifndef crop_cropsystH
#define crop_cropsystH
#include "options.h"
#include "crop_N_interface.h"
#ifndef OLD_PHENOLOGY_SEQUENCER
#include "crop/phenology_sequencer.h"
#endif
#include "common/simulation/synchronization.h"
#include "mgmt_types.h"
#include "crop/crop_common.h"
#include "crop/quiescence.h"
#if (CROPSYST_VERSION == 4)
#  include "crop/crop_root_V4.h"
#endif
// root_V5 is in both V4 and V5
#  include "crop/crop_root_V5.h"

#include "crop/phenology_common.h"
#  define CROP_ROOT  roots_current->
#if ((CROPSYST_VERSION >=5 ) || defined(USE_CS_LAND_UNIT))
#include "common/weather/parameter/WP_air_temperature.h"
#include "common/weather/parameter/WP_solar_radiation.h"
#include "common/weather/parameter/WC_vapor_pressure_deficit.h"
#include "common/weather/any_timestep/temperature_est.h"
#else
#include "common/weather/wthrbase.h"
#endif
#include "common/weather/weather_interface.h"

#ifdef HOURLY_THERMAL_TIME
#include "common/weather/weather.h"
#endif

#ifdef YAML_PARAM_VERSION
#include "crop/event_scheduler_crop.h"
#endif

#ifdef OLD_ORCHARD
#include "crop/crop_orchard_common.h"
class Fruit_harvest_requirements;                                                 //170220LML
#endif

#ifdef YAML_PARAM_VERSION
#  include "crop/transpiration_dependent_growth.h"
#else
#  include "crop/transpiration_dependent_growth_V4.h"
#endif
#include "corn/container/bilist.h"
#include "corn/math/compare.hpp"
#include "corn/math/statistical/sample_cumulative_T.h"
#include "crop/crop_param.h"
#include "common/recorder/recorder.h"

#define vapor_def_limit  0.40

#ifdef OLD_PHENOLOGY_SEQUENCER
#include "crop/thermal_time_daily.h"
#else
#include "crop/phenology_sequencer.h"
#endif

#include "CS_suite/observation/CS_observation.h"
#define USE_WEATHER_PARAMETERS

#ifdef OLD_BIOMASS_GROWTH
#else
#include "crop/biomass_growth.h"
#endif

#ifdef NITROGEN
#include "common/biometeorology/parameter/slope_SVP_curve_psychrometric_resistance.h"
#endif

#include "corn/chronometry/time_conversion.h"
//______________________________________________________________________________
// forward declarations
namespace CORN {
class Data_record;
}
using namespace CORN;
namespace CS
{
   class Desired_variables;
   class Weather_hours;                                                          //131101
}
class Soil_nitrogen_interface;
class ET_reference_interface;
class Seeding_parameters;
class Crop_mass_fate;
class Residues_interface;
class Crop_emergence_thermal_time;
class Common_simulation_log;
class Vapor_pressure_saturation_slope;                                           //140507
class Psychrometric_constant;                                                    //140508
namespace CropSyst
{
   class Harvest_or_clipping_operation_struct;                                   //140811
   interface_ Yield;                                                             //150825
   class Crop_CO2_response;                                                      //020424
   #ifdef FRUIT_CROP_MODEL
   class Fruit_chill_requirement;
   class Fruit_bud_break_requirement;
   class Fruit_harvest_requirements;
   #endif
   class Canopy_growth_interface;
}
#if (CROPSYST_VERSION >= 5)
namespace CropSyst {
#endif
   class Crop_emergence_abstract;
   class Crop_emergence_hydrothermal_time;
   class Crop_nitrogen_interface;
   class Biomass_growth;
//______________________________________________________________________________
class Stress_adjusted_temperature_estimator      // rename to Stress_adjusted_maximum_temperature_estimator
: public  Temperature_estimator
{
   float64 stress_adjusted_temperature;  // degrees C     rename to stress_adjusted_max_temperature
public:
   inline Stress_adjusted_temperature_estimator(Minutes interval_minutes=60)
      : Temperature_estimator(interval_minutes)
      {}
   inline void set_stress_adjusted_temperature(float64 _stress_adjusted_temperature) //030610
      { stress_adjusted_temperature = _stress_adjusted_temperature;}             //030610
   inline virtual float64 get_max_today()                                  const
      { return stress_adjusted_temperature; }
};
//_2003-06-09___________________________________________________________________
// forward declarations
#if (CROPSYST_VERSION >= 5)
} // namespace CropSyst
#endif

#ifndef OLD_BIOMASS_GROWTH
namespace Liu_Xiao                                                               //180116
{  class Crop_parameters_struct;                                                 //180116
}
#endif

namespace CropSyst {                                                             //141206
//______________________________________________________________________________
class Crop_complete
: public extends_ Crop_common                                                    //031131
#ifndef OLD_PHENOLOGY_SEQUENCER
, public extends_ Phenology_sequencer
#endif
{  // parameters have been moved to Crop_common

 protected:
   const Weather_spanning_interface &weather;
   CropSyst::Event_scheduler_crop_complete *as_event_scheduler_crop;
      // alias to event_scheduler cast as Event_scheduler_crop so
      // we have access to crop specific event operations.
   const CORN::Local_time &sun_rise_time;                                        //150907
   //snow pack is ephermeral we cannot reference it                              //141205
   cognate_ float64 snow_pack_thickness; // meter                                //161110
   friend class Crop_nitrogen_interface;                                         //050816
   #ifdef NITROGEN
   friend class Crop_nitrogen_common;         // eventually obsolete because using interface
//NYN   friend class Crop_nitrogen;         // eventually obsolete because using interface
   #endif
   friend class CropSyst_DLY_report;
   friend class CropSyst_GS_report;                                              //030530
   friend class Biomass_yield_calibrator;
protected: // External objects frequently accessed.
   const Air_temperature_maximum                &air_temperature_max;            //140225
   const Air_temperature_minimum                &air_temperature_min;            //140225
   const Air_temperature_average                &air_temperature_avg;            //140225
   const Solar_radiation                        &solar_radiation;                //140813
   const Psychrometric_constant                 &psychrometric_constant;         //140508
   const Vapor_pressure_deficit_max             &vapor_pressure_deficit_max;     //140225
   Air_temperature_average                       temperature_with_est_night;
      // daily temp with est. night time temps.
 public: // Soil interfaces
   // These soil pointers may be 0 indicating the crop is not limited by the soil.
   // This is the case with the Crop calibrator and the simulation option.
   const Soil_salt_interface  *soil_salinity;                                    //051118
public:  // temporary public for debugging
   Canopy_growth_interface    *canopy_growth;                                    //080725
protected: // state provided to canopy                                           //080506
   float64 water_canopy_expansion_factor;                                        //080506
      // value between 0 and 1.
private :
   Stress_adjusted_temperature_estimator stress_adj_hourly_temperature_estimator;//030609
      //071127 Actually this should be optional if hourly thermal time is selected
   CORN::Dynamic_array<float32> stress_adj_hourly_temperature;                   //030610
      //071127 Actually this should be optional if hourly thermal time is selected
   CORN::Dynamic_array<float32> stress_adj_hourly_temperature_not_applicable;    //150826
private:
   Seeding_parameters *seeding_parameters; // may be 0 if not using that model   //041201
   bool estimate_root_biomass;                                                   //060612
public: // Options
   bool     fallow_deprecated;                                                   //970305
protected:
   float64  yesterday_deg_day;
   mutable  CORN::Statistical_sample_cumulative<float64,float64>/*180408 Statistical_running_index*/
            vapor_pressure_deficit_stats;              // used only for output  //030530
   float64  intercepted_radiation;                                               // MJ/m2 ?  (may be PAR or total radiation based depending on the mode)   //030530
   float64  intercepted_radiation_accum;                                         // MJ/m2 ? // used only for output                                        //030530
   float64  intercepted_radiation_season_accum;                                  //030602
      // MJ/m2 ? // used only for output to season report,
      // it is actually the same as intercepted_PAR_accum but that is
      // currently cleared before the season report is generate,
      // this is not cleared until after the report detail is output.
 //  The following are daily computed variables:
 protected: // Growth limitations passed from potential growth to actual growth
 #if (CROPSYST_VERSION == 5)
 public: // This should be protected, but there appears to be friend namespace issue
 #endif
 protected:
   float64  attainable_top_growth;                                               //011022
   #ifdef OLD_BIOMASS_GROWTH
   float64  RUE_temperature_limitation_factor;
   #else
   provided_ Biomass_growth *biomass_growth;                                     //180111
   #endif

 protected:
   float64 biomass_at_filling;                                                   //131022
   float64 biomass_at_maturity; // kg/m2  130510
 #if (CROPSYST_VERSION == 5)
 public: // This should be protected, but there appears to be friend namespace issure
 #endif
   float64  unclipped_biomass;                                                   //010329
   // unclipped_biomass used for clipped perennials otherwise always 0.0  in crop nitrogen
 public: // Reported values for output only
   // Do not use the reported for any calculations,
   // they are provided only because the data record requires fixed members to record the values
   float64  reported_peak_LAI;// The actual peak_LAI gets adjusted at the harvest event //040929
   float64  reported_GAI;     // Green area index for output only                //050823
   float64  reported_LAI;     // Leaf area index for output only                 //160627
   float64  reported_canopy_biomass;                                             //050823
   float64  reported_N_mass_yield;                                               //160628
   float32  reported_canopy_cover_green;  // fraction                            //160629
   float32  reported_canopy_cover_max;    // fraction                            //180413
      // reported_canopy_cover_max is just a temporary hack
      // because I already have and inspector, but Claudio want this
      // in the old season report
   float64  recorded_root_depth; // Used for output only                         //000322
   float64  total_season_biomass_production_output;                              //040719
      // kg/m2  This is essentially the current canopy biomass plus any biomass removed. (used only for output)
   float64  total_season_biomass_running_accum_output;                           //040719
      // kg/m2  This is essentially the current canopy biomass plus any biomass removed. (used only for output)
 private: // Leafs and canopy
   float64 reported_LAI_for_self_shading_response;                               //080728
 public: // Leafs and canopy
   float64 reported_GAI_max; //was  largest_GAI_for_output;                      //180413
      // used only to identify the largest_GAI_date
   CORN::Date_32_clad GAI_max_date /*180413 largest_GAI_date*/;                  //180413_171115
      // was Date_time_clad_64
   float64  plant_height;                                                        //990201
   int16    days_after_flowering;                                                //040830
      // check if days_after_flowering is obsolete because should already be available in phenology class
 #if (CROPSYST_VERSION == 5)
 public: // This should be protected, but there appears to be friend namespace issure
 #else
 protected: // root related variables
 #endif
   // should be local to limited_growth but it is needed by nitrogen
   CropSyst::Crop_root_interface  *roots_current; // 0 if there is no soil       //061208
#ifndef CROP_CALIBRATION
   CropSyst::Crop_root_dormant    *roots_dormant; // 0 if there is no soil       //061208
#endif
   #if (CROPSYST_VERSION==4)
   CropSyst::
   #endif
   Crop_root_vital      *roots_vital; // May be 0 if there is no soil            //061208
 public: // root related variables
   float64  pot_root_biomass           ;  // used for N limited growth           //010713
   float64  act_root_biomass           ;  // used for output and roots           //010713
 public:// Stress
   //180408 mutable Statistical_running_index
   mutable CORN::Statistical_sample_cumulative<float64,float64>                  //180408
            report_temperature_stress_stats;            //010726
   float64  overall_growth_stress;  //  This is the light purple stress curve in the runtime display
 protected:
   public: Yield *yield;                                                         //150825
      // public so parameter scheduler can access
 public: // Growth stages, dates, and special conditions
   bool     initialized;                                                         //031121
   Normal_crop_event_sequence growth_stage_at_harvest;                           //040526
   bool     is_in_leaf_senescence;                                               //121221
   nat8     season;        // This is the count of seasons  for perennials  (1 based) incremented on end of dormancy.   //030613
   bool     fall_sowing;   // true if sown in the fall, used for perennials to not give too high restart GAI the season after fall sowing.   //040114
   int16    harvests_this_season;                                                //040625
   bool     no_more_clippings_this_season;  // when a latest clipping event is encountered, we stop any postponed clippings   //040721

 protected: // The following are used only to show the respective growth stage labels on the reports for a few days
   Days linger_sowing_label ;                                                    //030521
   Days linger_tuber_init_label ;                                                //030521
   Days linger_budbreak_label ;                                                  //030521
   Days linger_veraison_label ;                                                  //030521
   Days linger_harvest_label;                                                    //030521
   Days linger_chill_satisfied_label;                                            //030529
   CORN::Date_time_clad_64 inactive_end_date;                                    //081013
   float64 limited_pot_transpiration_m;                                          //160821
 public:


   // transpiration_dependent_growth is sort of only used by
   // biomass growth, it probably could be moved

   bool before_WUE_change;
   #ifdef YAML_PARAM_VERSION
   // Using adjustable parameter idiom
   CropSyst::Biomass_production_transpiration_dependent_V5 transpiration_dependent_growth; //120614 100729
   #else
   CropSyst::Biomass_production_transpiration_dependent_V4 transpiration_dependent_growth; //120614 100729
   #endif




   CORN::Date_clad_32 latest_harvest_date;
   CORN::Date_clad_32 unexpected_termination_date;                               //000428
      // Due to lethal freezing or latest date to harvest

   Crop_mass_fate *biomass_fate_today;                                           //050822
      // 0 unless harvest or biomatter loss today relenquished to owner.
   Crop_mass_fate *biomass_fate_season;                                          //050822
      // 0 until any biomatter fate processed
   float64  deg_day_stop_root;
   bool     terminate_pending;                                                   //040514
      // The crop will set terminate_pending flag to indicate self induced termination conditions occurred, state variables are suitable for output
 protected: // Special events and conditions
   bool           fruit_harvested;                                               //030529_000626
   int16          days_of_expected_dormancy_remaining;                           //980723
 protected:  // Estimated carbon assimilation for output only
   float64  C_mass_canopy_est;                                                   //110915_060818
   float64  C_mass_root_est;                                                     //110915_060818
 public:
   const CS::CO2_atmospheric_concentration *CO2_current_conc_optional;           //151201
      // Can be 0 if not simulating CO2
   float64 CO2_TUE_adjustment;                                                   //150907
 #ifdef OLD_PHENOLOGY_SEQUENCER
 protected: // Synchronization
   // moved to phenology_sequencer
   bool           emerged ;                                                      //000808
   CS::Temperature               stress_adjusted_temperature;                    //150217_140625
   Thermal_time_common          *thermal_time;
   CropSyst::Phenology_common    phenology;                                      //130904
 #endif
   virtual void trigger_synchronization(Normal_crop_event_sequence event);       //130903
 protected: // Emergence models
   Crop_emergence_abstract *emergence; // Will be 0 before and after emergence   //041201
   Crop_emergence_hydrothermal_time *emergence_hydrothermal_time;                //041201

   CropSyst::Quiescence_start_requirement    *quiescence_start_requirement;      //160326_021202
   CropSyst::Quiescence_end_requirement      *quiescence_end_requirement;        //160326_021202
 #ifdef OLD_ORCHARD
 public:   // Old orchard   orchard stuff is being moved
   const CS::Weather_hours     *ref_hourly_weather;  // this is optional, only needed for hydrothermaltime emergence //080908
   Orchard_interface *orchard;
   CropSyst::Crop_parameters::Fruit *fruit_adjusted_parameters;                  //081103
      // NULL when no fruit
   Fruit_harvest_requirements       *fruit_harvest_requirements;                 //081204
   bool limit_max_LAI;                                                           //081103
   mutable float64  fruit_dry_biomass; // kg/m2  dry basis                       //000616

   CORN::Date_clad_32 veraison_date;                                             //030521
   CORN::Date_clad_32 bud_break_date;                                            //081013
   CORN::Date_clad_32 initial_fruit_growth_date;                                 //030521
   CORN::Date_clad_32 rapid_fruit_growth_date;                                   //030521
   CORN::Date_clad_32 chill_requirement_satisfied_date;                          //081013
 protected:
   bool at_max_fruit_load;                                                       //180308
   virtual bool is_at_max_fruit_load()                                    const; //081103
 private:
   #ifdef FRUIT_CROP_MODEL
   //071120 moved to Crop_CropSyst_fruit
   Fruit_chill_requirement       *fruit_chill_requirement;                       //021125
      // This is 0 when the crop does not have chill requirement
      // (applies only to fruit crops)
   Fruit_bud_break_requirement   *fruit_bud_break_requirement;                   //021125
      // This is 0 when the crop does not have bud_break_requirement
      // (applies only to fruit crops)
   #endif
 #else
  private:
    bool at_max_fruit_load;                                                       //180308
 #endif
 protected: // Fruit virtual methods (may eventually be moved to fruit crop
   virtual bool get_limit_max_LAI()                                        const //081103
      #ifdef OLD_ORCHARD
               ;
      #else
               { return false; } // only applies to fruit crops (which will override)
      #endif
 public: // public so reports can  access
   Crop_nitrogen_interface  *nitrogen;  // currently assume kg_m2 (may be able to factor out units, haven't checked) //050722
   float64                   N_mass_canopy_recorded_before_harvest;               //110915_070209
 public: // external object references
   Common_simulation_log    *ref_event_log;    // The event log is optional, it is owned by caller   //030624
   Residues_interface       *ref_residues;     // Residues is optional (used by the canopy decomposition submodel);
   // In V5 will use inspectors
 public: // Special reported output output these are not used by the model itself
   float32 report_degree_hours_above_30_today;
   float32 report_degree_hours_above_34_today;
   float32 report_transpiration_use_eff; // transpiration_dependent_growth.ref_transpiration_use_efficiency_CO2_adjusted()
   struct Season_tally
   {
      bool window_14_days_achieved;
      CORN::Dynamic_array<float32> degree_hours_above_30_flowering;
      CORN::Dynamic_array<float32> degree_hours_above_34_flowering;
      CORN::Statistical_sample_cumulative<float32,float32> Srad;
      CORN::Statistical_sample_cumulative<float32,float32> Tmax;
      CORN::Statistical_sample_cumulative<float32,float32> Tmin;
      CORN::Statistical_sample_cumulative<float32,float32> Tavg;
      float32 transpiration_act; // cumulative used for calculation
      // Calculated at end of season
      float32 water_use_efficiency; // kg biomass/kg water
         // (season biomass/ season transpiration)
    public:
      inline Season_tally()
         : window_14_days_achieved  (false)
         , water_use_efficiency     (0)
         , transpiration_act        (0)
         {}
   } output_season_tally;
 public: // structors
   Crop_complete
      (CropSyst::Crop_parameters             *parameters                         //010110
      ,float64 param_dry_soil_root_activity_coef_                                //170518
      ,float64 param_saturated_soil_root_activity_coef_                          //170518
      #ifdef OLD_ORCHARD
      ,Orchard_interface                     *orchard
      #endif
      ,bool                                   owns_parameters                    //040121
      ,const CORN::date32 &today_                                                //170525
      ,CORN::Unidirectional_list             &performable_operations             //151004
      ,const CS::CO2_atmospheric_concentration *atmospheric_CO2_conc_ppm_optional//180122
      ,modifiable_ Crop_CO2_response         *Crop_CO2_response_given_optional   //151201
      ,const Air_temperature_maximum         &air_temperature_max                //140813
      ,const Air_temperature_minimum         &air_temperature_min                //140813
      ,const Air_temperature_average         &air_temperature_avg                //140813
      ,const Solar_radiation                 &solar_radiation                    //140813
      ,const Vapor_pressure_deficit_daytime  &daytime_vapor_pressure_deficit     //140813
      ,const Vapor_pressure_deficit_max      &vapor_pressure_deficit_max         //140813
      ,const Psychrometric_constant          &psychrometric_constant             //140508
      ,const Weather_spanning_interface      &weather                            //151130
      ,const CORN::Local_time                &sun_rise_time                      //150907
      ,const float64                         &ref_day_length_hours               //140812
      ,Seeding_parameters                    *seeding_parameters = 0             //041201
      ,Soil_interface                        *soil = 0                           //050721
      ,Crop_nitrogen_model              nitrogen_model = CROP_NITROGEN_DISABLED  //050722
      #ifdef NITROGEN
      ,const Slope_saturated_vapor_pressure_plus_psychrometric_resistance            //referenced
       *slope_saturated_vapor_pressure_plus_psychrometric_resistance_reference = 0
      #endif
      );                        //170518
   virtual ~Crop_complete();                                                     //020409
 public: // Simulation_element method implementations
   virtual bool initialize()                                    initialization_;
   virtual bool start()                                           modification_; //071120
   virtual bool start_day()                                       modification_; //040205
   virtual bool process_day()                                     modification_; //110824_020711
   virtual bool end_day()                                         modification_; //070221
 public: // optional setup
   inline virtual void know_event_log(Common_simulation_log *_event_log)         //170315_050725
      { ref_event_log = _event_log; }
   //   Use set_event_log if you want to record crop event and change of status. //050725
   virtual void know_residues(Residues_interface *_residues) ;                   //060531
   inline virtual float64 know_snow_pack_thickness(float64 snow_pack_thickness_) cognition_ //161110
      { return snow_pack_thickness = snow_pack_thickness_; }
 public:
   bool in_growing_season()                                        affirmation_;
   virtual bool end_season_if_no_dormancy()                       modification_; //050818
   virtual bool end_season()                                      modification_; //160629
 public: // The following functions are used in cases where the
   // plant dies or operations that removed parts of the plant
   virtual void commit_biomass_fate()                             modification_; //040610
   virtual
      Crop_mass_fate_biomass_and_nitrogen *
      process_biomass_fate                                                       //070625
      (Biomass_fated_cause fated_cause
      ,Harvest_amount_mode harvest_amount_mode                                   //050822
      ,float64 remove_amount_kg_m2                                               //050822
      ,float64 retain_GAI                                                        //050822
      ,float64 retain_biomass                                                    //110603
      ,const Biomass_fate_parameters  &biomass_fate_parameters
      ,bool terminate                                                            //040817
      ,float64 yield_now); // from harvest index, may be 0.0
   // This moves plant biomass to various pools, harvest yield, residue, loss etc..
   // Returns the fate of the material (call must delete the returned fate object)  //060323
 private:
   float64 record_biomass_fate(const Crop_mass_fate &fate_now,float64 curr_canopy_biomass_kg_m2);  //040809
 public: // Leaf biomass uptake
   virtual float64 distribute_todays_non_leaf_stem_growth(float64 todays_growth) modification_;    //071120
      // returns todays growth that is available to goto leaf and stem
      // For normal crops this simply returns todays_growth
      // For orchard fruits, the biomass will be distributed
   float64 est_root_biomass()                                             const; //060612
      // This was the old way of calculating root biomass using a fraction of canopy biomass
                                       // this is deprecated, now use calc_root_biomass();
   void update_root_density_and_root_fractions();
 public: // Special conditions and events
   virtual void check_hardiness();                                               //131104
   bool start_season(float64 initial_biomass,bool after_dormancy_or_non_dormant_crop);//050826
   virtual bool start_inactive_period(bool apply_dormancy);                      //140625_030523


   #ifdef OLD_ORCHARD
   inline virtual void know_weather_hourly(const CS::Weather_hours *_hourly_weather) //151212_080908
      { ref_hourly_weather = _hourly_weather; }
   virtual void start_normal_crop_dormancy();                                    //030522
   #else
   virtual void senesce_at_dormancy();                                           //071120
   #endif
   virtual void restart_after_inactive_period();                                 //970219
   virtual void consider_inactive_period                                         //020626
      (float64 avg_temperature
      //131106,float64 temperature_with_est_night
      ); // was daily temp with est. night time temps.
   virtual void setup_quiescence_end_requirement(CORN::DOY doy);                 //160326_080401
   virtual void restart(float64 initial_biomass,float64 restart_GAI,bool use_clumping_factor, bool after_dormancy);
         // this should return bool 150825
   inline virtual float64 get_solid_canopy_interception()                  const //021211
      { return
         #ifdef OLD_ORCHARD
         orchard? orchard->get_solid_canopy_interception():
         #endif
         0.0;}
   inline virtual float64 est_degree_days_X_days_from_now                        //000330
      (const CORN::Date_const &today, Days days_from_now)                  const //010202
      { return 0.0; }
   // This is currently overridden by Crop_interfaced_CropSyst
   // Probably want to move this to Crop_common
   virtual float64 get_adjusted_ET_crop_coefficient()                     const; //080808


public: // Growth
   #ifdef OLD_BIOMASS_GROWTH
   float64 calc_RUE_temperature_limitation()                              const; //130513
   virtual float64 calc_attainable_top_growth();
   #else
   Biomass_growth &provide_biomass_growth()                          provision_; //180612
   #endif
   virtual float64 calc_act_biomass_growth                                       //011023
      (float64 planting_depth                                                    //010202
      ,float64 &LAI_related_growth);

public: // Phenology / Growth stage functions
   const char *describe_growth_stage()                                    const;
   inline virtual bool has_leaf_senescence()                        affirmation_ //140619
      { return parameters->has_leaf_senescence();}
   inline virtual bool is_perennial()                               affirmation_ //140810
      { return parameters->is_perennial(); }
   #ifdef OLD_PHENOLOGY_SEQUENCER
   //140619 moving to Phenology_sequencer
   bool thermal_time_matchs(float64 deg_day_event,bool clipping_adjusted) const;
   virtual void thermal_time_event()                              modification_;
      // This function checks if the current thermal time matches the
      // thermal time needed to acheive and of the parameters for
      // phenology and if so, performs an update for
      // the respective growth stage initiation. 010723
   #endif
   #ifdef SEED_EMERGENCE_MODEL
   bool check_for_emergence();                                                   //041201
      // Returns true if this was the first day (first cohorts)
      // Note returns false after the first day event if aditional cohorst
      // (so this doesn't return true if any emergence, it return true only the first day).
   #endif
   virtual bool initiate_emergence  ();
   virtual bool initiate_tuber      ();
   virtual bool initiate_flowering  ();
   virtual bool initiate_filling    ();
   virtual bool initiate_senescence ();                                          //121224
   virtual bool initiate_max_canopy ();                                          //130429
   virtual bool initiate_maturity   ();
   #ifdef OLD_ORCHARD
   //071120
   virtual bool initiate_fruit_growth();                                         //030521
   virtual bool initiate_veraison();                                             //000625
   virtual bool initiate_rapid_fruit_growth();                                   //030521
   #endif
   virtual
      Crop_mass_fate_biomass_and_nitrogen *                                      //070625
      harvest                                                                    //051105
      (float64 remove_amount_kg_m2                                               //050822
      ,const CropSyst::Harvest_or_clipping_operation_struct                      //140811
      *harvest_or_clipping_params
      ,bool terminate);                                                          //140811
      // \return fate of biomass if could harvest otherwise 0 caller must delete //020311
   bool natural_expiration()                                      modification_; //040805
   virtual bool allow_natural_expiration()                        modification_; //040805
   virtual bool respond_to_clipping()                             modification_; //051103
public: // Daily leaf history methods
   // The following are daily_history total accessors
   // The daily history will be tallied if not yet done today.
   float64 get_GAI(uint8 include_GAI)                                     const;
   float64 get_GAI_vital()                                                const;
   float64 get_GAI_vital_plus_effete()                                    const; //070320
   float64 get_canopy_biomass_kg_m2_including(nat8 include_biomass)       const; //120614
   #ifndef CROP_CALIBRATION
   float64 get_orchard_solid_canopy_interception()                        const; //081020
   float64 get_orchard_shaded_area_GAI()                                  const; //081020
   float64 get_orchard_canopy_porosity()                                  const; //081020
   #endif
   float64 get_live_green_canopy_biomass_kg_m2(uint8 include_biomass)     const;
 public: // Virtual methods to be supplied by derived classes
   // Related to nitrogen
   virtual float64 get_min_water_N_stress()                               const; //010726
      // Probably no longer needs to be virtual
 protected:
   float64 get_water_productivity(bool before_WUE_change)                 const; //080428
 #if (CROPSYST_VERSION == 5)
 public: // This should be protected, but there appears to be friend namespace issue
 #endif
   #ifdef OLD_BIOMASS_GROWTH
   float64 get_radiation_use_efficiency_global()                          const; //080429
   #endif
   #if (CROPSYST_VERSION < 5)
   float64 get_radiation_use_efficiency_PAR()                             const; //080429
   #endif
      // Returns the maximum radiation use efficiency for the season which may be adjusted
      // for C02 simulations.                                                    //010723
 public: // Interface operations called by external calling routine (for setup or daily loop)
   virtual bool sow(bool fall_sowing);                                           //140813_110824_020220
   virtual void log_event(const char *description)                        const; //110824_020912
   virtual Crop_mass_fate_biomass_and_nitrogen *harvest_crop                     //070625
      (Harvest_amount_mode harvest_amount_mode                                   //031015
      ,float64 remove_amount_kg_m2                                               //050822
      ,float64 retain_GAI                                                        //050822
      ,const Biomass_fate_parameters &harvest_biomass_fate_parameters
      ,bool terminate);                                                          //050822
      // Returns the fate of biomass if if could harvest otherwise 0 caller must delete
   virtual void set_automatic_nitrogen_mode(bool enable);                        //040525
   virtual float64 damage_GAI(float64 GAI_damage)                 modification_; //151226
      ///< kills the specified GAI_damage.
      ///  \returns the amount of live GAI remaining.
 protected:
   void processes();                                                             //010723
   float64 tuber_initiation_temperature_stress_factor(float64 min_air_temperature) const; //081109
   float64 tuber_bulking_temperature_stress_factor(float64 min_air_temperature) const;    //081109
   virtual void actual_growth();                                                 //991029
   virtual void update_lingers()                                  modification_; //071120
   virtual bool respond_to_freezing_damage                                       //081103
      (float64 fract_reduction_due_to_freezing)                   modification_  //081103
         #ifdef OLD_ORCHARD
                  ;
         #else
                  { return true; }  // Currently normal crops simply die_back (done by caller) this is overridden by fruit crops
         #endif
 private:
   bool create_canopy();                                                         //060531
public: // State variable accessors that are actually used by CropSyst
   virtual float64 get_canopy_resistance()                                const; //020409
      // The following accessors are not necessarily currently used by CropSyst.
      // They are provided for use by other models or output
          float64 get_carbon_fraction()                                   const; //060818
 public: // State variable accessors
   inline virtual const float64 *get_total_fract_root_length()             const { return roots_vital? roots_vital->get_total_fract_root_length_m()  : 0; } //061208
   inline float64 get_total_fract_root_length(uint8 sublayer)              const { return roots_vital? roots_vital->get_total_fract_root_length_m()[sublayer] : 0; }
   inline float64 get_active_fract_root_length(uint8 sublayer)             const { return transpiration->get_active_fract_root_length(sublayer); }
   // Stress
   inline float64 get_water_stress()                                       const { return water_stress_stats.get_current(); }
   inline float64 get_water_stress_index()                                 const { return water_stress_stats.index; }
   inline float64 get_temperature_stress()                                 const { return report_temperature_stress_stats.get_current(); }
   inline float64 get_temperature_stress_index()                           const { return report_temperature_stress_stats.index; }
   inline float64 water_stress_stats_append(float64 value)                       { return water_stress_stats.append(value); }
   inline float64 temperature_stress_stats_append(float64 value)                 { return report_temperature_stress_stats.append(value); }
   // Used for stress harvest index
   // Options
   inline bool    get_fallow_deprecated()                                  const { return fallow_deprecated; } //130415 obsolete
   // Growth limitations passed from potential growth to actual growth
   inline float64 get_attainable_top_growth()                              const { return attainable_top_growth; } //011023
   // Canopy cover
   float64 get_fract_canopy_cover_green()                                 const;
   float64 get_fract_canopy_cover_total()                                 const;
   float64 global_solar_rad_intercepted_green_canopy()                    const;
   // Leafs and canopy
   float64 get_peak_LAI(bool reported )                                   const; //141203
          float64 get_LAI(bool from_canopy)                               const; //060824
          float64 get_GAI_today_vital()                                   const; //050823
   inline const CORN::Date_const &ref_GAI_max_date()                      const  { return GAI_max_date; }
   //180413 inline const CORN::Date_const &get_largest_GAI_date()                   const { return largest_GAI_date; }
   inline float64 get_plant_height()                                       const { return plant_height; }
   // Root related variables
   inline float64 get_root_length()                                        const { return CROP_ROOT get_root_length() ;}
   inline float64 get_recorded_root_depth()                                const { return roots_current ? roots_current->get_apparent_root_depth() : 0.0; }   //061208
#ifdef NITROGEN
   virtual float64 get_N_mass_canopy_kg_m2(bool recorded_before_harvest)  const; //070209
#endif
   inline float64 get_pot_root_biomass             ()                      const { return pot_root_biomass; }
   inline float64 get_act_root_biomass             ()                      const { return act_root_biomass; }
   // Transpiration
   inline float64 get_pot_transpiration            (bool CO2_adjusted)     const { return pot_transpiration_m[CO2_adjusted]; } //151031
   inline float64 get_act_transpiration            ()                      const { return act_transpiration_m; } //011023
   inline float64 get_recorded_act_transpiration   ()                      const { return report_transpiration_act_m; }
   inline float64 get_act_uptake                   ()                     const; //NYI  { return act_uptake_m; } //011023
   // Stress
   inline float64 get_overall_growth_stress        ()                      const { return overall_growth_stress; }
   // Daily phenology data:
   // Growth stages, dates, and special conditions
   inline virtual CropSyst::Phenology_interface &mod_phenology()                 { return phenology; } //130903
   inline virtual const CropSyst::Phenology_interface &ref_phenology()     const { return phenology; } //130903
   inline virtual Normal_crop_event_sequence get_growth_stage_sequence()   const { return ref_phenology().get_growth_stage_sequence(); }//120820_110902
   inline const CORN::Date_const &get_planting_date             () const { return phenology.start_date[NGS_PLANTING]; }
   inline const CORN::Date_const &get_restart_date              () const { return phenology.start_date[NGS_RESTART]; }
   inline const CORN::Date_const &get_emergence_date            () const { return phenology.start_date[NGS_EMERGENCE]; }
   inline const CORN::Date_const &get_tuber_init_date           () const { return phenology.start_date_tuber_initiation; } //141217_081111
   inline const CORN::Date_const &get_flowering_date            () const { return phenology.start_date[NGS_ANTHESIS]; }
   inline const CORN::Date_const &get_grain_filling_date        () const { return phenology.start_date[NGS_FILLING]; }
   inline const CORN::Date_const &get_inactive_begin_date       () const { return phenology.start_date[NGS_DORMANT_or_INACTIVE]; }  //081013

   #ifdef OLD_ORCHARD
   //071120
   inline const CORN::Date_const &get_fruit_filling_date        ()         const { return initial_fruit_growth_date; }       //021202
   inline const CORN::Date_const &get_bud_break_date            ()         const { return bud_break_date; }                  //081013
   inline const CORN::Date_const &get_initial_fruit_growth_date ()         const { return initial_fruit_growth_date; }       //081013
   inline const CORN::Date_const &get_rapid_fruit_growth_date   ()         const { return rapid_fruit_growth_date; }         //081013
   inline const CORN::Date_const &get_chill_requirement_satisfied_date()   const { return chill_requirement_satisfied_date; }//081013
   #endif
   inline const CORN::Date_const &get_inactive_end_date         ()         const { return inactive_end_date.ref_date(); }    //081013
   inline const CORN::Date_const &get_maturity_date             ()         const
      #ifndef OLD_PENOLOGY_SEQUENCER
      { return phenology.start_date[NGS_MATURITY]; }
      #else
      { return maturity_date.ref_date; }
      #endif
   inline const CORN::Date_const &get_harvest_date              ()         const { return latest_harvest_date; }
   inline const CORN::Date_const &get_unexpected_termination_date()        const { return unexpected_termination_date; }
   inline float64    get_deg_day_stop_root         ()                      const { return deg_day_stop_root; }
   virtual inline bool is_terminate_pending        ()               affirmation_ { return terminate_pending; }    //040514
   // Special events and conditions
   virtual bool is_orchard()                                       affirmation_; //120909
   #ifdef CROP_ORCHARD
   #ifdef OLD_ORCHARD
   //071120
   inline bool             get_fruit_harvested()                           const { return fruit_harvested; }  // was grapes_harvested
   virtual bool is_fruit_harvestable()                             affirmation_; //081204
   #endif
   #endif
   inline int16 get_days_of_expected_dormancy_remaining()                  const { return days_of_expected_dormancy_remaining; }
   inline bool  has_emerged()                                        affirmation_{ return emerged; } //110824
   virtual inline bool use_emergence_hydrothermal_time()             affirmation_{ return emergence_hydrothermal_time != 0; } //140619
   inline const Crop_nitrogen_interface *get_nitrogen    ()                const { return nitrogen; }   //050722
   // Growth limitations passed from potential growth to actual growth
   inline float64 set_attainable_top_growth (float64 _attainable_top_growth)     { return attainable_top_growth = _attainable_top_growth; } //011023
   // Leafs and canopy
   /*171020 never used, in any case new talling inspection will give this value
   inline float64 set_largest_GAI(float64 _largest_GAI)                          { largest_GAI_for_output = _largest_GAI ; return largest_GAI_for_output; }
   */
   /*180413 Never used
  inline const CORN::Date_const &set_GAI_max_date(const CORN::Date_const &GAI_max_date_) //180413
      { GAI_max_date.set(GAI_max_date_) ; return GAI_max_date; }                 //171115
   */
   /*180413
   inline const CORN::Date_const &set_largest_GAI_date(const CORN::Date_const &_largest_GAI_date)
      { largest_GAI_date.set(_largest_GAI_date) ; return largest_GAI_date; }     //171115
   */
//171115    inline const CORN::Date_const &set_largest_GAI_date(const CORN::Date_const &_largest_GAI_date)   { largest_GAI_date.set(_largest_GAI_date) ; return largest_GAI_date.ref_date(); }
   inline float64 set_plant_height(float64 _plant_height)
      { plant_height = _plant_height ; return plant_height; }
   // Root related variables
/*171031 unused
   inline float64 set_recorded_root_depth       (float64 _recorded_root_depth);
   inline float64 set_pot_root_biomass          (float64 _pot_root_biomass)      { pot_root_biomass = _pot_root_biomass ; return pot_root_biomass; }
   inline float64 set_act_root_biomass          (float64 _act_root_biomass)      { act_root_biomass = _act_root_biomass ; return act_root_biomass; }
*/
   // Transpiration
/*171031 unused
          float64 set_pot_pot_transpiration     (float64 _pot_pot_transp);       //010910
          float64 set_pot_transpiration         (float64 _pot_transpiration);    //010910
   inline float64 set_act_transpiration         (float64 _act_transpiration)     { return act_transpiration_m = _act_transpiration ;  } //011023
   inline float64 set_recorded_act_transpiration(float64 report_transpiration_act_m_) { return report_transpiration_act_m = report_transpiration_act_m_ ;  }
*/
   virtual float64 update_pot_evapotranspiration(float64 _pot_ref_evapotranspiration);//010910

   // //             Calculates the pot_ET for this crop
   // //             Updates the pot_transpiration
   // //             Returns the pot ET for this crop.
   // Stress
   inline float64 set_overall_growth_stress(float64 overall_growth_stress_)
      { return overall_growth_stress = overall_growth_stress_ ; }
   // Daily phenology data:
   // Growth stages, dates, and special conditions
   inline const CORN::Date_const &set_latest_harvest_date(date32 harvest_date_)  //040624
      { latest_harvest_date.set_date32(harvest_date_); return latest_harvest_date; }
   inline const CORN::Date_const &set_unexpected_termination_date
      (const CORN::Date_const &unexpected_termination_date_)
      {  unexpected_termination_date.set(unexpected_termination_date_);
         return unexpected_termination_date; }
   inline float64 set_deg_day_stop_root(float64 _deg_day_stop_root)
      { deg_day_stop_root = _deg_day_stop_root ;  return deg_day_stop_root; }
   inline virtual void set_terminate_pending()    { terminate_pending = true; }  //040514
   // Special events and conditions
   inline int16 set_days_of_expected_dormancy_remaining
      (int16 days_of_expected_dormancy_remaining_)
      { days_of_expected_dormancy_remaining = days_of_expected_dormancy_remaining_ ;
        return days_of_expected_dormancy_remaining; }

   #ifdef CROP_ORCHARD
   #ifndef CROP_CALIBRATION
   virtual int16 get_fruit_chill_hours_remaining() const; // currently just for debugging
   #endif
   #endif
   virtual float64 get_thermal_time_cumulative(bool adjusted_for_clipping) const;
 public: // Parameter data source house keeping
   #if (!defined(CROP_CALIBRATION))
   // This is output not needed for CropCalibration.
   // I probably will eventually create a subclass which includes these two function
   // since they the recording option is probably only applicated to CropSyst
   #if (CROPSYST_VERSION==4)
   virtual bool setup_structure
      (CORN::Data_record &data_rec,bool for_write
      ,const CS::Desired_variables &desired_vars);
   #endif
   inline virtual const char *get_record_section_label()                   const { return "crop_base"; }
   #endif
   inline CropSyst::Crop_parameters   *get_parameters()                    const { return parameters;} //020409
                  // Will be owned by the crop object
   inline virtual void      *get_unique_identifier()                       const { return parameters;}
 protected:
   inline virtual void initialize_after_load()                     modification_ { initialize(); }  //010109
 protected:
   float64 no_nitrogen_calculate_limited_pot_transpiration()       modification_ ;//160321
 protected: // asbract check
    #ifdef REACCH_VERSION
    Local_time dummy_sun_rise_time;                                              //130711
    // For some unknown reason ref_sun_rise_time() is not referening correctly
    // We are currently using the sun_rise_time option for the exteme temperature response so this is disabled
    // This will be obsolete when I implement Weather_provider
    #endif
   Crop_complete();
   RENDER_INSPECTORS_DECLARATION;                                                //150916
   CORN::OS::Directory_name *crop_ID_directory; //owned                          //160609
   bool take_crop_ID_directory(CORN::OS::Directory_name *crop_ID_directory);     //160609
};
//______________________________________________________________________________
} // namespace CropSyst
#endif
//060730  720 lines
//080909  650 lines
//140619  820 lines

