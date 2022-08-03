#error obsolete  replaced with thermal_time*.* fle

#ifndef crop_thermal_timeH
#define crop_thermal_timeH

#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "corn/const.h"
#include "options.h"
#include "crop/crop_param_class.h"
#include "corn/dynamic_array/dynamic_array_T.h"
#include "weather/parameter/WP_air_temperature.h"
//#define Dynamic_float_array Dynamic_array<float32>

#include "CS_suite/simulation/CS_inspection.h"

/*
namespace Physical                                                               //150217
{ class Temperature;                                                             //140625
}
*/
#define TT_TODAY     0
#define TT_YESTERDAY 1
//______________________________________________________________________________
interface_ Crop_thermal_time_interface_immutable
{
   virtual float64 get_accum_degree_days
      (bool adjusted_for_clipping
      ,bool for_yesterday = false)                                         const = 0;//140619
   virtual const float64 &ref_thermal_time_cumulative()                    const = 0;
};
//_2008-08-05___________________________________________________________________
class Crop_thermal_time
: public Crop_thermal_time_interface_immutable
{
   public:
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
      Vernalization(const CropSyst:: Crop_parameters_struct::Vernalization   &_parameters);
      inline bool is_satisfied()                                           const { return status == VERNALIZATION_END; }
      float64 update_factor(float64 temperature)                  rectification_;
   };
   //_2011-11-09________________________________________________________________
public:
   const CropSyst:: Crop_parameters_class::Thermal_time &parameters;             //080605
public:
   bool                        cropsyst_fruit_model;                             //041212
   const CropSyst:: Crop_parameters_struct::Photoperiod *photoperiod_parameters; //080605
   const Physical::Temperature   &stress_adjusted_temperature;                   //150217_140625
   const Air_temperature_minimum &air_temperature_min;                           //150217_140625
   const Physical::Temperature   &temperature_with_est_night;                    //150217_140625
      // This can be simply average daily temperature
   const float64     &ref_day_length_hours;                                      //140812
public: // Vernalization
   Vernalization *vernalization; // May be NULL if not applicabled               //111109
   float64        growing_degree_day;                                            //971122
   nat32          consecutive_days_no_accumulation;                              //030515
public: // Temporarily public until  I implement add_desired variables for this class                                            //______
   float64        clipping_recovery_deg_days;                                    //040826
      // When a crop is clipped, we set the clipping_recovery thermal time counter,                                              //040826
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
//149=0812 now member reference       (float64 day_length_hours)        calculation_;
   float64 calc_growing_degree_day_daily_resolution                              //000330
      (float64 adjusted_max_temp                                                 //030610
      ,float64 air_temp_min)                                        calculation_;
      // This function calculates the normal growing degree day                  //019723
      // not limited by vernalization or photoperiod                             //019723
   float64 calc_growing_degree_day_hourly_resolution                             //021124
      (const CORN::Dynamic_array<float32> &stress_adj_hourly_temperature) calculation_;//030610
   float64 calc_limited_growing_degree_day                                       //010723
      (float64 growing_degree_day
      //149=0812 now member reference  ,float64 day_length_hours
      ,float64 vernalization_factor
      ,Normal_crop_event_sequence growth_stage_sequence)             calculation_;//130902

      // This function updates the normal calculation of growing_degree_day      //010723
      // (Growing degrees for the current date).
      // It returns the actual growing degrees that may be limited by
      // vernalization or photoperiod.

//NYI   float64 update ()                                                modification_ //140626

   double accumulate_degree_days                                                 //010727
      (CORN::Dynamic_array<float32> *stress_adj_hourly_temperature_optional         //071127
      // The following are optional for unstress crop mode                       //020630
      ,Normal_crop_event_sequence growth_stage_sequence);                        //130911
   void reset_to(float64 new_thermal_time)                         modification_;//040719
      // Some crops such as alfalfa we need to reset thermal time                //040719
      // (I.e. to emergence) when cut so they regrow.                            //040719
   void respond_to_clipping(float64 new_thermal_time)              modification_;//040823
      // When annuals crops are clipped the thermal time accumulation is delayed //040823
 public: // Constructor
   Crop_thermal_time
      (const CropSyst::Crop_parameters_class::Thermal_time    &_parameters       //110218_080605
      ,const Physical::Temperature     &_stress_adjusted_temperature             //140625
      ,const Air_temperature_minimum   &_air_temperature_min                     //140626
      ,const Physical::Temperature     &_temperature_with_est_night              //140626
      ,const float64      &_ref_day_length_hours                                 //140812
      ,bool                                          _cropsyst_fruit_model       //041212
      ,const CropSyst:: Crop_parameters_struct::Vernalization  *_vernalization_parameters_optional  //080605
      ,const CropSyst:: Crop_parameters_struct::Photoperiod    *_photoperiod_parameters_optional);  //080605
 public: // status accessors
   inline float64 get_growing_degree_day()                                 const { return growing_degree_day;}    //971122
   virtual float64 get_accum_degree_days
      (bool adjusted_for_clipping                                                //080805
      ,bool for_yesterday = false)                                         const;//140619
   inline virtual const float64 &ref_thermal_time_cumulative()             const { return (accum_degree_days_clipped[0]);} //130613
   void clear_accum_degree_days();
   bool enable_vernalization
      (const CropSyst:: Crop_parameters_struct::Vernalization &vernalization_parameters)
      modification_;                                                             //111109
   virtual bool end_day()                                          modification_;//140619
   RENDER_INSPECTORS_DECLARATION;                                                //150916
};
//_2002-06-28___________________________________________________________________
#endif
// crop_thermal_time.h

