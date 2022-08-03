#ifndef thermal_time_commonH
#define thermal_time_commonH
#include "options.h"
#include "crop/thermal_time.h"
#include "crop/crop_param_class.h"
#include "weather/parameter/WP_air_temperature.h"
#include "CS_suite/observation/CS_observation.h"

#define VERNALIZATION_NOT_APPLICABLE 0
#define PHOTOPERIOD_NOT_APPLICABLE   0

namespace CropSyst
{
//______________________________________________________________________________
class Thermal_time_common
: public implements_ Thermal_time
{
 public:
   //___________________________________________________________________________
   class Vernalization
   {
    private:
      const CropSyst::Crop_parameters_struct::Vernalization &parameters;         //080605
      contribute_ float64 vern_days;
      contribute_ float64 Vfactor;
    public:
      enum Status {VERNALIZATION_INACTIVE,VERNALIZATION_START,VERNALIZATION_ACTIVE,VERNALIZATION_END};
      contribute_ Status status;
    public:
      Vernalization(const Crop_parameters_struct::Vernalization &_parameters);
      inline bool is_satisfied()                                           const
         { return status == VERNALIZATION_END; }
      float64 update_factor(float64 temperature)                  rectification_;
   };
   //_2011-11-09________________________________________________________________
public:
   const CropSyst:: Crop_parameters_class::Thermal_time &parameters;             //080605
public:
   bool                        cropsyst_fruit_model;                             //041212
   const Crop_parameters_struct::Photoperiod *photoperiod_parameters;            //080605
   const Physical::Temperature   &stress_adjusted_temperature;                   //150217_140625
      // general maximum temperature (of air, or adjusted plant max temperature)
   const Air_temperature_minimum &air_temperature_min;                           //150217_140625
   const Physical::Temperature   &temperature_with_est_night;                    //150217_140625
      // This can be simply average daily temperature
      // Note that temperature_with_est_night is only used for vernalization
      // so it probably should be moved as member reference to vernalization submodel
   const float64     &ref_day_length_hours;                                      //140812
      // Note that day_length_hours is only used for photoperiod
      // so it probably should be moved as member reference to photoperiod submodel.

public: // Vernalization
   Vernalization *vernalization; // May be NULL if not applicabled               //111109
   float64        growing_degree_day;                                            //971122
   nat32          consecutive_days_no_accumulation;                              //030515
public: // Temporarily public until  I implement add_desired variables for this class
   float64        clipping_recovery_deg_days;                                    //040826
      // When a crop is clipped, set the clipping_recovery thermal time counter, //040826
      // this is decremented by growing_degree_day each day until < 0.           //040826
      // While clipping_recovery > 0, there is no accumulation.                  //040826
   float64        accum_degree_days_normal[2];
   float64        accum_degree_days_clipped[2];                                  //040823
      // Index 0 is today, 1 is yesterday
      // Adjusted for regrowth after clipping event.
      // When a perennial crop is clipped we reset this accumulator to emergence
      // (we may need to adjust this abit).
public:
   float64 calc_vernalization_factor
     (float64 temperature
     ,float64 &vern_days)                                           calculation_;
      // This function updates the days in vernalization factor                  //010723
      // and the in_vernalization flag                                           //010723
   float64 calc_photoperiod_factor()                                calculation_;//140812
   virtual float64 calc_growing_degree_day_daily_resolution                      //000330
      (float64 adjusted_max_temp                                                 //030610
      ,float64 air_temp_min)                                        calculation_=0;
      // This function calculates the normal growing degree day                  //019723
      // not limited by vernalization or photoperiod                             //019723
   float64 calc_growing_degree_day_hourly_resolution                             //021124
      (const CORN::Dynamic_array<float32> &stress_adj_hourly_temperature) calculation_;//030610
   float64 calc_limited_growing_degree_day                                       //010723
      (float64 growing_degree_day
      ,float64 vernalization_factor
      ,Normal_crop_event_sequence growth_stage_sequence)            calculation_;//130902
      // This function updates the normal calculation of growing_degree_day      //010723
      // (Growing degrees for the current date).
      // It returns the actual growing degrees that may be limited by
      // vernalization or photoperiod.
   virtual double accumulate_degree_days                                         //151110_010727
      (CORN::Dynamic_array<float32> *stress_adj_hourly_temperature_optional      //071127
      // The following are optional for unstressed crop mode                     //020630
      ,Normal_crop_event_sequence growth_stage_sequence);                        //130911
   void reset_to(float64 new_thermal_time)                         modification_;//040719
      // Some crops such as alfalfa we need to reset thermal time                //040719
      // (I.e. to emergence) when cut so they regrow.                            //040719
   void respond_to_clipping(float64 new_thermal_time)              modification_;//040823
      // When annuals crops are clipped the thermal time accumulation is delayed //040823
 public: // Constructor
   Thermal_time_common
      (const Crop_parameters_class::Thermal_time    &_parameters                 //110218_080605
      ,const Physical::Temperature     &_stress_adjusted_temperature             //140625
      ,const Air_temperature_minimum   &_air_temperature_min                     //140626
      ,const Physical::Temperature     &_temperature_with_est_night              //140626
      ,const float64      &_ref_day_length_hours                                 //140812
      ,bool                _cropsyst_fruit_model                                 //041212
      ,const Crop_parameters_struct::Vernalization  *_vernalization_parameters_optional  //080605
      ,const Crop_parameters_struct::Photoperiod    *_photoperiod_parameters_optional);  //080605
 public: // status accessors
   inline virtual float64 get_growing_degree_day()                         const //971122
      { return growing_degree_day;}
   virtual float64 get_accum_degree_days
      (bool adjusted_for_clipping                                                //080805
      ,bool for_yesterday = false)                                         const;//140619
   inline virtual const float64 &ref_degree_day()                          const //160101
      { return growing_degree_day; }
   inline virtual const float64 &ref_thermal_time_cumulative()             const //130613
      { return (accum_degree_days_clipped[0]);}
   virtual void clear_accum_degree_days();
   virtual bool enable_vernalization
      (const CropSyst::Crop_parameters_struct::Vernalization
         &vernalization_parameters)                                modification_;//111109
   virtual bool end_day()                                          modification_;//140619
   RENDER_INSPECTORS_DECLARATION;                                                //150916
};
//_2002-06-28___________________________________________________________________
} // namespace CropSyst
#endif

