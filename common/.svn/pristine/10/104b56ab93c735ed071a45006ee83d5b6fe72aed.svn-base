#ifndef atmospheric_CO2_change_recalibrationH
#define atmospheric_CO2_change_recalibrationH
#include "common/weather/atmospheric_CO2_change.h"
#include "corn/math/numerical/interpolation/interpolator_temporal.h"
//______________________________________________________________________________
class Atmospheric_CO2_change_recalibration
: public Atmospheric_CO2_change_element
{
private:
   contribute_ CS::CO2_atmospheric_concentration curr_CO2_conc;                  //150507
   CORN::Interpolator_temporal *interpolator;
public:
   Atmospheric_CO2_change_recalibration
      (const char *CO2_recalibration_filename
      ,const CORN::Date_const &start_date
      ,const CORN::Date_const &end_date
      ,const CORN::date32 &today_raw_                                            //171207
      ,float32 initial_CO2_conc// used for default absissa in the interpolation
      ,bool &CO2_data_encountered);
   virtual ~Atmospheric_CO2_change_recalibration();
public:
   virtual bool start_day()                                       modification_; //171207
   virtual bool end_year()                                        modification_; //171207
   inline virtual float64 get_current_CO2_conc() const { return curr_CO2_conc; }
   inline virtual const CS::CO2_atmospheric_concentration &ref_CO2_current_conc() const
      { return curr_CO2_conc; }
};
//______________________________________________________________________________
#endif
