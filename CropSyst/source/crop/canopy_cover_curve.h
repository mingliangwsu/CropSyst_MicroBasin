#ifndef canopy_cover_curveH
#define canopy_cover_curveH
#include "corn/primitive.h"
#include "corn/const.h"
namespace CropSyst
{
//______________________________________________________________________________
interface_ Canopy_cover_curve
{

   virtual bool parameterize
      (float64 cover_maximum_CO2_adj
      ,float64 initial_cover)                                 initialization_=0;
   virtual bool start_senescence()                              modification_=0;
   virtual float64 calculate(float64 cumulative_thermal_time)    calculation_=0;
/*171221
   virtual float64 set_cover_at_max_canopy //171221 set_CC_at_max_canopy
      (float64 CC_at_max_canopy)assignation_=0;
*/
};
//_2017-12-20_____________________________________Canopy_cover_curve_|interface/
class Canopy_cover_curve_common   // rename to Canopy_cover_curve_abstract
: public implements_ Canopy_cover_curve
{protected:
   contribute_ float64 cumulative_thermal_time;                                  //130703
 protected: // parameters
   float64 thermal_time_end_vegetative_growth;
   float64 thermal_time_start_season;                                            //171219
   float64 thermal_time_beginning_senescence;
   const float32 &/*180713 float64 */thermal_time_season_end;  //was X                                     //171219
   const float32 &/*180713 float64 */canopy_cover_season_end;     // was X                                             //171009
   float64 cover_maximum_CO2_adj;                                                //141123
   float64 cover_initial;
 protected:
   bool in_senescence;                                                           //141124
 public: // structors
   Canopy_cover_curve_common
      (float64 thermal_time_end_vegetative_growth
      ,float64 thermal_time_beginning_senescence
      ,float64 thermal_time_start_season
      ,const float32 &/*180713 float64 */ thermal_time_season_end
      ,const float32 &/*180713 float64 */ canopy_cover_season_end
      );
 public:
   virtual bool parameterize
      (float64 cover_maximum_CO2_adj
      ,float64 cover_initial)                                   initialization_;
 public:
   virtual float64 calculate(float64 cumulative_thermal_time)      calculation_;
   virtual float64 calc_during_cresence()                        calculation_=0;
   virtual float64 calc_during_culminescence()                   calculation_=0;
   virtual float64 calc_during_senescence()                      calculation_=0;

};
//_2017-12-20__________________________________Canopy_cover_curve_common_|class/
/*180601 obsolete but dont delete until 2020
class Canopy_cover_curve_2013
: public extends_ Canopy_cover_curve_common                                      //171220
{
 protected: // parameters
      // some arbitrary point (was maturity)   actually disabled since 2011
   float64 fract_season_to_reach_half_max_cover;
 private: // calculated parameters
   float64 b_Coefficient;
   float64 asym_CC;
   float64 asym_CC_senescence;
   float64 shape_factor;
   float64 C_low;
   const float64 &cover_latest_vegetative;   // reference to Canopy_cover_abstract::cover_latest_vegetative
   float64 actual_CC_max;
public: // Canopy_cover_curve implementation
   virtual bool parameterize
      (float64 cover_maximum_CO2_adj
      ,float64 cover_initial)                                   initialization_;
   virtual bool start_senescence()                                modification_; //141124
 public: // Canopy_cover_curve_common implementation
   virtual float64 calc_during_cresence()                          calculation_; //141123 was calc_during_vegetative_growth
   virtual float64 calc_during_culminescence()                     calculation_;
   virtual float64 calc_during_senescence()                        calculation_;
 public: // structors
   Canopy_cover_curve_2013
      (float64 thermal_time_end_vegetative_growth
      ,float64 thermal_time_beginning_senescence
      ,float64 thermal_time_start_season
      ,float64 thermal_time_season_end                                           //171219_171009
      ,float64 canopy_cover_season_end                                           //171219_171009
      ,float64 fract_season_to_reach_half_max_cover
      ,const float64 &cover_latest_vegetative
      );
};
*/
//_2013-06-11____________________________________Canopy_cover_curve_2013_|class/
class Canopy_cover_curve_2017
//: public implements_ Canopy_cover_curve_common
: public extends_ Canopy_cover_curve_common
{
 protected:
   float64 B1;
   float64 B2;
   float64 shape_coef_vegetative;   // rename shape_coef_accrescent
   float64 shape_coef_senescent;
   float64 CCmax_asymptotic;
   float64 CCmax2_actual;
   float64 CCend_asymptotic; // at end season
 private:
   //float64 cover_gain;                                                           //171221
//   float64 cover_yesterday;                                                      //171221
//   float64 cover_cum;                                                            //171221
//   const float64 &stress_factor;                                                 //171221
 protected:
   mutable float64 cover_current;
 public: // structors
   Canopy_cover_curve_2017
      (
       float64 thermal_time_end_vegetative_growth
      ,float64 thermal_time_beginning_senescence
      ,float64 thermal_time_start_season
      ,const float32 &/*180713 float64 */ thermal_time_season_end
      /*NYN
      ,float64 canopy_cover_season_end
      ,float64 fract_season_to_reach_half_max_cover
      */
      ,const float32 &/*180713 float64 */ canopy_cover_season_end_
      ,float64 shape_coef_accrescent_
      ,float64 shape_coef_senescent_
//      ,float64 &stress_factor_
      );
 public: // Canopy_cover_curve implementation
   virtual bool parameterize
      (float64 cover_maximum_CO2_adj
      ,float64 cover_initial)                                   initialization_;

   virtual float64 set_cover_at_max_canopy
      (float64 CC_at_max_canopy)  assignation_
      {return 0.0;}
      // This class doesn't used cover_at_max_canopy
      // if Canopy_cover_curve_2013 is removed, this function can be removed

   virtual bool start_senescence()                                modification_;

 public: // Canopy_cover_curve_common implementation
//abandoned   virtual float64 calculate(float64 cumulative_thermal_time)      calculation_;
   virtual float64 calc_during_cresence()                          calculation_;
   virtual float64 calc_during_culminescence()                     calculation_;
   virtual float64 calc_during_senescence()                        calculation_;

};
//_2017-12-20___________________________________Canopy_cover_curve_2017_|class_/




} // namespace CropSyst
#endif

