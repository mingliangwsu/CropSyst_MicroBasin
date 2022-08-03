#ifndef WP_ET_referenceH
#define WP_ET_referenceH
#include "corn/measure/measures.h"
#include "common/CS_parameter_float64.h"
//______________________________________________________________________________
class ET_Reference
: public extends_ CS::Parameter_float64
{
public:
   inline ET_Reference()
      : CS::Parameter_float64(EXTENSIVE,0.0,UC_meter,CORN::unknown_quality)      //150123
      {}
   inline float64 get_mm() const { return m_to_mm(get_m()); }                    //140527_110910
   inline float64 get_m()  const { return in_prescribed_units(); }               //110910
   inline float64 set_mm(float64 millimeter, const CORN::Quality &quality_)const { return update_value_qualified(mm_to_m(millimeter),quality_);}
   inline float64 set_m(float64 meter, const CORN::Quality &quality_)      const { return update_value_qualified(meter,quality_);}
   inline float64 set_mm(float64 millimeter, CORN::Quality_code quality_)  const { return update_value_qualified_code(mm_to_m(millimeter),quality_);}
   inline float64 set_m(float64 meter, const CORN::Quality_code quality_)  const { return update_value_qualified_code(meter,quality_);}
};
//_2014-05-27___________________________________________________________________
#endif

