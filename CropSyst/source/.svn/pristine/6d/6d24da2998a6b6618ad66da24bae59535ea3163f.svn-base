#ifndef phenology_adjustorH
#define phenology_adjustorH
#include "crop/phenology_common.h"
#include "corn/math/statistical/sample_cumulative_T.h"
#include "phenology_sequencer.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "CS_suite/simulation/CS_simulation_element.h"
#include "corn/const.h"

class Weather;
class Sun;
namespace CropSyst {
class Crop_parameters;
//______________________________________________________________________________
class Phenology_adjustor
: public extends_ CS::Simulation_element_abstract
{  // one for each crop
   //___________________________________________________________________________
   class Crop
   : public extends_ Phenology_sequencer
   , public extends_ CS::Simulation_element_abstract
   {
      const Air_temperature_maximum&     air_temperature_max;                    //150217
      const Air_temperature_average&     air_temperature_avg;                    //150217
      const Crop_parameters &crop_parameters;
      const CORN::Date             *typical_relative; //[NGS_COUNT]; //owned by caller
      const CORN::Date &            typical_relative_senescence;                 //160211
      const CORN::Date &            typical_relative_senescence_full;            //160211
    public:
      CORN::Date  date_relative;
         // This is the current date with year relative to sowing year
         // so the year will be 0 unless multi year crop.
         // Or crop crosses years.
         // date could be moved to phenology
      float64     start_deg_days[NGS_COUNT];
      float64     start_deg_days_senescence;                                     //160211
      float64     start_deg_days_senescence_full;                                //160211
    public:
      Crop
         (const Crop_parameters&          crop_parameters
         ,const CORN::Date&               today
         ,const CORN::Date*               typical_relative//[NGS_COUNT]
         ,const CORN::Date &              typical_relative_senescence            //160211
         ,const CORN::Date &              typical_relative_senescence_full       //160211
         ,const Air_temperature_maximum&  air_temperature_max                    //160201
         ,const Air_temperature_minimum&  air_temperature_min                    //160201
         ,const Air_temperature_average&  air_temperature_avg                    //160201
         ,const float64&                  ref_day_length_hours);                 //140812
      virtual bool start();                                                      //160205
      virtual bool start_day();
      virtual bool process_day(); //day                                          //150624
      virtual bool use_emergence_hydrothermal_time()                 affirmation_{ return false; }
      virtual bool has_leaf_senescence()                             affirmation_{ return crop_parameters.has_leaf_senescence(); }
      virtual bool has_maturity()                                    affirmation_{ return crop_parameters.phenology.maturity_significant; }

//      void trigger_synchronization(Normal_crop_event_sequence event);
   };
   //___________________________________________________________________________
 public:
   Crop_parameters*  crop_parameters_owned;
 private:
   std::wstring      unique_crop_identifier;
   CORN::Date        typical_planting_date_relative;
   CORN::Date        typical_relative[NGS_COUNT];
   CORN::Date        typical_relative_senescence;                                //160211
   CORN::Date        typical_relative_senescence_full;                           //160211

      // I think this should be const but that is not working.

//   ::Weather&                    weather;
      // The adjustor is taking control of the weather
   const Air_temperature_maximum    &air_temperature_max;                        //140813
   const Air_temperature_minimum    &air_temperature_min;                        //140813
   const Air_temperature_average    &air_temperature_avg;                        //140813
   const float64                    &day_length_hours;                           //140814
 public:
   CORN::Statistical_sample_cumulative<nat16,float64> *start_day_in_season_stats[NGS_COUNT];
   CORN::Statistical_sample_cumulative<nat16,float64> *start_deg_days_stats[NGS_COUNT];
   CORN::Statistical_sample_cumulative<nat16,float64> *start_day_in_season_stats_senescence; //160211
   CORN::Statistical_sample_cumulative<nat16,float64> *start_deg_days_stats_senescence; //160211
   CORN::Statistical_sample_cumulative<nat16,float64> *start_day_in_season_stats_senescence_full;//160211
   CORN::Statistical_sample_cumulative<nat16,float64> *start_deg_days_stats_senescence_full;//160211
 protected:
   Crop *crop_current;
 public:
   bool  adjust_mode;                                                             //160211
 public:
   Phenology_adjustor
      (const std::wstring         & unique_crop_identifier_
      ,const CORN::Date           & typical_planting_date_relative_
      ,const CORN::Date           * typical_relative_//[NGS_COUNT]
      ,const CORN::Date           & typical_senescence_date_relative_            //160211
      ,const CORN::Date           & typical_senescence_full_date_relative_       //160211
      ,const Air_temperature_maximum         &air_temperature_max_               //140813
      ,const Air_temperature_minimum         &air_temperature_min_               //140813
      ,const Air_temperature_average         &air_temperature_avg_               //140813
      ,const float64              &day_length_hours_                             //160201
      ,const CORN::Date           &today_);
   virtual ~Phenology_adjustor();                                                //141103
   inline bool take_crop_parameters(Crop_parameters* _crop_parameters_given)
      { return crop_parameters_owned = _crop_parameters_given; }
   virtual bool start_day();
   virtual bool process_day(); //day                                             //150624
   virtual int compare(const Item &other)                                 const;
//160201   bool know_day_length_hours(float64 day_length_hours)               cognition_;//160201
 public:
   bool commit_computed_phenology_parameters
      (modifiable_ CropSyst::Crop_parameters_struct::Phenology &phenology_parameters
//      ,Normal_crop_event_sequence   reference_point_growth_stage                 //160204
      )                                                                   const;
 protected:
   virtual const char *label_cstr_deprecated(char *buffer)                           const; //170423 deprecated
   virtual const char *label_string(std::string &buffer)                  const; //170423
   inline virtual bool is_key_wstring(const std::wstring &key)              affirmation_  //180820
      { return unique_crop_identifier == key; }

/*180820  was probably only used for find_cstr now using is_key
   
   inline virtual const wchar_t  *get_key_wide()                           const
      { return unique_crop_identifier.c_str();                                   //150211
      }
*/      
   bool Phenology_adjustor::apply_adjustments
      (const         CropSyst::Crop_parameters_struct::Phenology &unadjusted
      ,const         CropSyst::Crop_parameters_struct::Phenology &  average
      ,modifiable_   CropSyst::Crop_parameters_struct::Phenology &  adjusted) const;
   bool apply_averages
      (const         CropSyst::Crop_parameters_struct::Phenology &  average
      ,modifiable_   CropSyst::Crop_parameters_struct::Phenology &  adjusted) const;
};
//______________________________________________________________________________
#ifdef OFOOT_VERSION
class Phenology_adjustors
: public extends_ CS::Simulation_element_composite
{
 private:
   modifiable_ CORN::Date  &today_modifiable;
   Sun &sun;                                                                     //160201
   ::Weather&        weather;
   contribute_ bool adjustments_calculated;
 public:
   Phenology_adjustors
      (Sun &sun_                                                                     //160201
      ,::Weather               &weather_
      ,modifiable_ CORN::Date  &today_);

   Phenology_adjustor * add_crop
      (const CORN::OS::File_name & crop_filename
      ,const CORN::Date          & typical_planting_date_relative
      ,const CORN::Date          * typical_relative); //[NGS_COUNT]; //owned by caller
      // Adds the specified crop to the list of Phenology_adjustor
   /* Disabled/Obsolete because potentially relative crop filenames would need to be resolved
   nat16 add_crops_in_rotation(const CORN::OS::File_name &rotation_filename);
      // Calls add_crop for each crop file encountered in the rotation.
      // returns the number of crops added.
   */
   bool adjust_phenology_parameters
      (const std::wstring &data_source_URL                                      //140731
      ,modifiable_ CropSyst::Crop_parameters_struct::Phenology &phenology_parameters);
      // The filename is used to uniquely identify the crop adjustments.
      // The adjustments must have been previously calculated with a call to
      // calculate_adjustments().
      // This method does not open or modify the file.
      // We pass the phenology parameters to be modified.
   bool determine_adjustments();
      // Calculateds adjustments for all crops previously added
      // either with add_crop or add_crops_in_rotation.

   virtual bool start();
   virtual bool start_day()                                        modification_;
 protected:
    /*160201now just a C function
   float32 adjust_full_senescence
      (float32 full_senescence_unadjusted
      ,float32 max_canopy_unadjusted
      ,float32 mature_unadjusted
      ,float32 max_canopy_average
      ,float32 maturity_average
      ,bool    maturity_significant)                                       const;
   */
   /*160201now just a C function
   float32 adjust_generalized
      ( float32 calibrated  // specific phenology parameter to adjust
      , float32 early_unadjusted
      , float32 late_unadjusted
      , float32 early_average
      , float32 late_average)                                              const;
   */
   /*160102
   float32 adjust
      (float32 calibrated  // specific phenology parameter to adjust
      ,const CropSyst::Crop_parameters_struct::Phenology &unadjusted
      ,const CropSyst::Crop_parameters_struct::Phenology &average
      ,const CropSyst::Crop_parameters_struct::Phenology &adjusted
      ,bool  maturity_significant)                                         const;
   */

};
#endif
//______________________________________________________________________________

extern float32 adjust_full_senescence
      (float32 full_senescence_unadjusted
      ,float32 max_canopy_unadjusted
      ,float32 mature_unadjusted
      ,float32 max_canopy_average
      ,float32 maturity_average
      ,bool    maturity_significant);

extern float32 adjust_generalized
      ( float32 calibrated  // specific phenology parameter to adjust
      , float32 early_unadjusted
      , float32 late_unadjusted
      , float32 early_average
      , float32 late_average);
extern float32 adjust_given_emergence_accrescence_maturity // was adjust
      (float32 calibrated  // specific phenology parameter to adjust
      ,const CropSyst::Crop_parameters_struct::Phenology &unadjusted
      ,const CropSyst::Crop_parameters_struct::Phenology &average
      ,const CropSyst::Crop_parameters_struct::Phenology &adjusted
      ,bool  maturity_significant);
extern float32 adjust_given_planting_flowering_maturity // was adjust
      (float32 calibrated  // specific phenology parameter to adjust
      ,const CropSyst::Crop_parameters_struct::Phenology &unadjusted
      ,const CropSyst::Crop_parameters_struct::Phenology &average
      ,const CropSyst::Crop_parameters_struct::Phenology &adjusted
      ,bool  maturity_significant);

} // namespace CropSyst
#endif

