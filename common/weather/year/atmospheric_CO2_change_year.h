#ifndef atmospheric_CO2_change_yearH
#define atmospheric_CO2_change_yearH
#include <common/weather/atmospheric_CO2_change_interface.h>
#include <corn/quality.hpp>
//______________________________________________________________________________
class Atmospheric_CO2_change_year    // abstract
: public Atmospheric_CO2_change_interface
{protected:
   float64        current_CO2_conc; // ppm
   CORN::Quality  current_CO2_conc_quality;
 public:
   Atmospheric_CO2_change_year
   (float64             initial_CO2_conc);
   inline virtual bool end_year()                                             not_const { return true;/* 090415 do nothing for this implementation? Need to check. I think nothing to do because the concentration is set from recalibration file for this model. */ };
//NYN   virtual bool    update()                                              updates;
   inline virtual float64 get_current_CO2_conc()                           const { return current_CO2_conc; } ;
   virtual float64 set_current_CO2_conc(float64 new_current_CO2_conc,const CORN::Quality &attribute)  not_const;
};
//______________________________________________________________________________
#endif

