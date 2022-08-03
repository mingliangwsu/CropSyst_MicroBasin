#ifndef WP_precipitationH
#define WP_precipitationH
#include "common/CS_parameter_float64.h"
#include "corn/measure/measures.h"
//______________________________________________________________________________
class Precipitation
: public extends_ CS::Parameter_float64  // Eventually derive from Length property
{  // Liquid water equivelent (rain and/or snow)
public:
   inline Precipitation()                                                        //110910
      : CS::Parameter_float64(EXTENSIVE,0.0,UC_meter,CORN::unknown_quality)
      {}
   inline float64 get_m()                                                  const { return in_prescribed_units();}
   inline float64 get_mm()                                                 const { return m_to_mm(get_m()); }
   inline float64 set_m (float64 value_m  ,const CORN::Quality &_quality)        { return update_value_qualified(value_m      ,_quality);     } // const { return set_value_quality(value_m          ,_quality); }
   inline float64 set_mm(float64 value_mm ,const CORN::Quality &_quality)        { return set_m(mm_to_m(value_mm)             ,_quality); } //const { return set_value_quality(mm_to_m(value_mm),_quality); }
   inline float64 set_m (float64 value_m  ,CORN::Quality_code _quality)          { return update_value_qualified_code(value_m ,_quality);  } //const { return set_value_quality_code(value_m          ,_quality); }
   inline float64 set_mm(float64 value_mm ,CORN::Quality_code _quality)          { return set_m(mm_to_m(value_mm)             ,_quality); } //const { return set_value_quality_code(mm_to_m(value_mm),_quality); }
};
//______________________________________________________________________________
#endif
