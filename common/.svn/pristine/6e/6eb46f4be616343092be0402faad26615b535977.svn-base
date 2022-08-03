#ifndef ET_reference_Priestley_TaylorH
#define ET_reference_Priestley_TaylorH
#include "corn/primitive.h"
#include "corn/const.h"
#include "common/CS_parameter_float64.h"
//_____________________________________________________________________
class Vapor_pressure_deficit_fullday;
namespace CORN
{  class Data_record;
}
//_____________________________________________________________________
namespace CS
{
//_____________________________________________________________________
class Priestley_Taylor_Parameters
{public:
   provided_ float32 P_T_constant;
   CS::Parameter_float64 P_T_alpha_fract; // 0.1 – 0.7
 protected:
   CS::Parameter_float64 &VPDavg_seasonal_fullday_observed;
   const Vapor_pressure_deficit_fullday *VPD_fullday; //kPa  (not owned)
 public:
   Priestley_Taylor_Parameters
      (CS::Parameter_float64 &VPDavg_seasonal_fullday_observed_);
   void copy(const Priestley_Taylor_Parameters &from);
   inline bool know_VPD_fullday(const Vapor_pressure_deficit_fullday *VPD_fullday_)
      { VPD_fullday = VPD_fullday_; return true; }
   float32 provide_P_T_constant_adjusted()                           provision_;
   virtual bool setup_structure
      (CORN::Data_record &data_rec,bool for_write)                modification_;
   virtual bool get_end()                                         modification_;
};
//_Priestley_Taylor_Parameters______________________________________2017-07-14_/
}
//_____________________________________________________________________
// namespace CS
//_____________________________________________________________________
#endif