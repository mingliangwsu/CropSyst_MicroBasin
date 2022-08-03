#ifndef erosion_RUSLEH
#define erosion_RUSLEH

// This options.h needs to be for the current program being compiled
// is should not necessarily be /cropsyst/cpp/options.h

#include "options.h"
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
//170525#include "corn/datetime/date.hpp"
#include "corn/math/statistical/sample_dataset_T.h"
#include "corn/math/statistical/sample_cumulative_T.h"
#include "cs_vars.h"
#include "CS_suite/simulation/CS_simulation_element.h"
#include "common/weather/parameter/WP_precipitation.h"
#  include "soil/soil_base.h"
//______________________________________________________________________________
// Forward declarations
class Soil_base;
class Soil_tillage_effect;
#ifdef XLS_OUTPUT
class CropSyst_GS_report;
class CropSyst_DLY_report;
class CropSyst_YLY_report;
class CropSyst_FLW_report;
#endif
class Season_data_record;
class Annual_data_record;
class CS_daily_data_record;
class Weather_spanning_interface;                                                //151130
namespace CORN
{  class Recorder_data_record;
   class Data_record;
}
namespace CS { namespace meteorology { interface_ Storms; }}                     //160506
namespace CS { class Desired_variables; }                                        //170225
class Soil_cropsyst_specific;                                                    //020527

namespace RUSLE {                                                                //160503
//_______________________________________________________Forward declarations__/
class Soil_erosion
: public extends_ CS::Simulation_element_abstract                                //160503
{
#ifdef XLS_OUTPUT
   friend class CropSyst_GS_report;
   friend class CropSyst_DLY_report;
   friend class CropSyst_YLY_report;
   friend class CropSyst_FLW_report;
#endif
   friend class Soil_cropsyst_specific;                                          //020527
   friend class Soil_tillage_effect;                                             //060929
   friend class Season_data_record;                                              //040921
   friend class Annual_data_record;                                              //040923
   friend class CS_daily_data_record;                                            //041022
 // RUSLE
 public:  // RUSLE_annual_C_factor temporarily public for special output for Manuel
   CORN::Statistical_sample_with_dataset<float64,float64,float32> C_factor_tally;//160616_160506
      // I think this is unitless 0-1   (I think this is actually cumulative cover factor (RLN: This may need to be average?)
 public:
   float64 soil_conservation_factor;                                             //160506
 public:  // Soil and soil management factors
   float64 total_soil_loss;  // tonne/ha for the year}
#ifdef TILLAGE
   float64 clod_factor_rate     ; // m     m/?  ?
   float64 clodding_factor      ; // m
#endif
   const Soil_base               &soil;                                          //160506_020527
 protected:  // Precipitation factor
   const Precipitation &precipitation_eff; // reference to meteorology (Currently only used for dump_output).
      // precipitation_eff will be obsolete when it is confirmed that
      // we need to accumulate daily storm energy from intervals (using new Storm_energy class).
   const float32       *month_mean_peak_halfhour_precipitation_check_units; /* provided */   //091130
   contribute_ float32 R_fract_contrib[367];                                     //160513
   float64  rainfall_energy_intensity;                                           //091130
 private: // current year
   CORN::Statistical_sample_with_dataset<float64,float32,float32> storm_energy;  //160616_160506
   CORN::Statistical_sample_with_dataset<float64,float64,float32> storm_R_tally; //160616
         // (MJ/ha) * (mm/hr)

   contribute_ float32 mulch_factor    [367];                                    //160506
   contribute_ float32 cover_factor    [367];                                    //160506
   contribute_ float32 moisture_factor [367];                                    //160506
 private: // for output only
   contribute_ float32 output_precip_eff_mm  [367];                              //160506
   contribute_ float32 output_peak_intensity [367];                              //160506
 public:
   Soil_erosion
      (Soil_base                       &soil_
      ,const CS::meteorology::Storms   &storms_                                  //160506
      ,const Precipitation             &precipitation_                           //160510
      ,const CORN::date32              &today_);                                 //160503
   void know_weather                                                             //091130
      (const float32 *_month_mean_peak_halfhour_precipitation_check_units); // contribution_;
   inline void know_soil_conservation_factor(float32 soil_conservation_factor_)  //160506
      { soil_conservation_factor = soil_conservation_factor_; }
   virtual bool start_year()                                      modification_; //160503
   virtual bool process_day()                                     modification_; //160506
   virtual bool end_day()                                         modification_; //160511
   virtual bool end_year()                                        modification_; //160506
   bool know_cover                                                               //160506
      (float64 crop_fract_canopy_cover
      ,float64 daily_residue_surface
      ,float64 daily_residue_shallow)                                cognition_;
      // Called daily
   float64 calc_cover_factor_annual();                                           //160506
   float64 calc_soil_erodibility_factor();
   float64 calc_daily_moisture_factor()                            calculation_; //980731
   float64 calc_steepness_factor();
   float64 calc_slope_length_factor();
   float64 calc_annual_soil_loss();                                              //160506
   bool setup_structure                                                          //030801
      (CORN::Data_record &data_rec,bool for_write,const CS::Desired_variables &desired_vars);
   float64 calc_rainfall_erosivity_factor(CORN::Year year)                const; //990317
 public: // output only
   bool dump_year_days(std::ostream &detail_text_file);                          //160506
};
//_1998-07-29________________________________________class:Soil_erosion_RUSLE__/
} // namespace RUSLE                                                             //160503
#endif
// soilersn.h

