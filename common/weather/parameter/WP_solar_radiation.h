#ifndef WP_solar_radiationH
#define WP_solar_radiationH
#include "corn/measure/measures.h"
#include "common/CS_parameter_float64.h"
//______________________________________________________________________________
class Solar_radiation   // ?rename or alias Global_solar_irradiance ?
: public extends_ CS::Parameter_float64
// Eventually derive from Physical property  insolation or irradiance (insolation derived from irradiance)
{
public:
   inline Solar_radiation()                                                      //110910
      : CS::Parameter_float64
         (INTENSIVE,0.0,UC_MJ_per_m2,CORN::unknown_quality)
      {}
   inline float64 set_MJ_m2(float64 value_MJ_m2, CORN::Quality_code _quality)
      { assume_code(_quality); return force_amount(value_MJ_m2);}
   inline float64 set_MJ_m2(float64 value_MJ_m2,  const CORN::Quality &_quality)
      { assume     (_quality); return force_amount(value_MJ_m2);}
   inline float64 set_kJ_m2(float64 value_MJ_m2, CORN::Quality_code _quality)
      { assume_code(_quality); return force_amount(kJ_m2_to_MJ_m2(value_MJ_m2));}
   inline float64 set_kJ_m2(float64 value_MJ_m2, const CORN::Quality &_quality)
      { assume     (_quality); return force_amount(kJ_m2_to_MJ_m2(value_MJ_m2));}
   inline float64 get_MJ_m2()                                              const
      { return in_prescribed_units();}
   inline float64 get_kJ_m2()                                              const
      { return MJ_m2_to_kJ_m2(get_MJ_m2()); }                                    //141205
   inline float64 get_wattsec_m2()                                         const //150307
      { return get_MJ_m2() * 1000000.0 / 86400.0; }
};
//_2010-12-06___________________________________________________________________
#endif

