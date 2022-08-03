#ifndef phenology_sequencerH
#define phenology_sequencerH
#include "crop/crop_param.h"
#include "crop/phenology_common.h"
#include "crop/thermal_time_daily.h"
#include "common/weather/parameter/WP_temperature.h"

namespace CropSyst
{
//______________________________________________________________________________
class Phenology_sequencer
{
   const Crop_parameters_struct::Phenology       &phenology_parameters;
   bool                                           harvest_orchard_fruit_part;
 protected:
   CS::Temperature          stress_adjusted_temperature;
   CS::Temperature          temperature_with_est_night;
   const Air_temperature_minimum &air_temperature_min;
 public: // This should be protected, but there appears to be friend namespace issue
   Thermal_time_common  *thermal_time;                                           //151109

//   Thermal_time_daily_2segment   thermal_time; //_2segment;  // Phenology      //020628
//   Thermal_time_daily_Wang       thermal_time_Wang;  // Phenology              //151109
 public:
   CropSyst::Phenology_common phenology;                                         //130904
 public: //   dates, and special conditions  probably should be protected
   //140619 probably should be moved or already in phenology
   CORN::Date_clad_32 &planting_date;                                            //041205
   CORN::Date_clad_32 &restart_date;                                             //041205
                  // The start of the season (at planting) and
                  // season restart for multiple year crops.
   CORN::Date_clad_32 &emergence_date ;
   CORN::Date_clad_32 &flowering_date ;
   CORN::Date_clad_32 &tuber_init_date ;                                         //081111
   CORN::Date_clad_32 &grain_filling_date ;                                      //030521
   CORN::Date_clad_32 &maturity_date;                                            //141202
   CORN::Date_clad_32 &inactive_begin_date;                                      //081013
 protected:
   const CORN::Date_const &ref_today;                                            //130818_110824
   bool                  emerged ;                                               //000808
   bool                  is_tuber;
 public:
   Phenology_sequencer
      (const CORN::Date_const         &today
      ,const Crop_parameters          &parameters                                //020409
      ,const Air_temperature_minimum  &air_temperature_min                       //150217
      ,const float64                  &ref_day_length_hours);                    //140812
   inline virtual bool start_day() modification_{ return phenology.start_day();}
   virtual bool start();
   virtual bool start_season()  modification_{ return phenology.start_season();} //160205
// NYN  virtual bool update()                                          rectification_;
// NYN   virtual bool end_day();
   virtual bool use_emergence_hydrothermal_time()                affirmation_=0;
   virtual bool has_leaf_senescence()                            affirmation_=0;
   bool thermal_time_matchs(float64 deg_day_event,bool clipping_adjusted) const;
   virtual void thermal_time_event()                              modification_;
      // This function checks if the current thermal time matches the
      // thermal time needed to acheive and of the parameters for
      // phenology and if so, performs an update for
      // the respective growth stage initiation. 010723
 protected: // Synchronization
   virtual void trigger_synchronization(Normal_crop_event_sequence event);       //130903

   virtual void log_event(const char *description)                        const; //110824_020912
 public:
   bool event_start
      (Normal_crop_event_sequence event_seq
      ,const char *preferred_description = 0);
   virtual bool initiate_emergence     ();
   virtual bool initiate_tuber         ();
   virtual bool initiate_flowering     ();
   virtual bool initiate_filling       ();
   virtual bool initiate_senescence    ();
   virtual bool initiate_max_canopy    ();
   virtual bool initiate_maturity      ();
#ifdef OLD_ORCHARD
   virtual bool initiate_fruit_growth  ();
   virtual bool initiate_veraison      ();
   virtual bool initiate_rapid_fruit_growth();
#endif
   virtual bool start_inactive_period(bool apply_dormancy);
   inline bool  has_emerged()                    affirmation_{ return emerged; } //110824
};
//_2014-06-19______________________________________________phenology_sequencer_/
} // namespace CropSyst
#endif

