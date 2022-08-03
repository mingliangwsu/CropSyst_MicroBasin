#ifndef unitconvH
#define unitconvH
#include "corn/measure/units.h"
namespace CORN {
/*
This class was originally designed to take 32bit floats
and 64bit float were added as an option
It should be redone to take 64bit floats with 32bit floats as an option.
*/
// Forward declarations
class Units_component;
//______________________________________________________________________________
class Units_convertor
{
public:
   inline Units_convertor() {}
   virtual bool convert                                                          //971206
      (float32 from_value, Units_code from_units
      ,float32 &to_value,  Units_code to_units  ) const;
   virtual bool convert                                                          //100303
      (float64 from_value, Units_code from_units
      ,float64 &to_value,  Units_code to_units  ) const;
   virtual bool convert                                                          //100303
      (float32 from_value, Units_code from_units
      ,float64 &to_value,  Units_code to_units  ) const;
   virtual bool convert                                                          //100303
      (float64 from_value, Units_code from_units
      ,float32 &to_value,  Units_code to_units  ) const;
   virtual bool convert_with_time_step                                           //971206
      (Units_code   from_time_step
      ,float32 from_value, Units_code from_units
      ,Units_code    to_time_step
      ,float32 &to_value,  Units_code to_units  ) const;
      ///< Some units (such as solar radiation) have an implicit time step
      ///< in the time series where the time step units are not
      ///< part of the composed units.

   virtual bool convert_time                                                     //971206
      (float32  from_value, Units_code from_time_step
      ,float32 &to_value,   Units_code to_time_step  ) const;
      // Some units (such as solar radiation) have an implicit time step
      // in the time series where the time step units are not
      // part of the composed units.

   inline virtual bool convert                                                   // 971206
      (float32 from_value, Units_clad from_units
      ,float32 &to_value,  Units_clad to_units  ) const { return convert(from_value,from_units.get(),to_value,to_units.get()); }
   inline virtual bool convert                                                   //100303
      (float64 from_value, Units_clad from_units
      ,float64 &to_value,  Units_clad to_units  ) const { return convert(from_value,from_units.get(),to_value,to_units.get()); }
   inline virtual bool convert                                                   //100303
      (float32 from_value, Units_clad from_units
      ,float64 &to_value,  Units_clad to_units  ) const { return convert(from_value,from_units.get(),to_value,to_units.get()); }
   inline virtual bool convert                                                   //100303
      (float64 from_value, Units_clad from_units
      ,float32 &to_value,  Units_clad to_units  ) const { return convert(from_value,from_units.get(),to_value,to_units.get()); }
   inline virtual bool convert_with_time_step                                    //971206
      (Units_clad   from_time_step
      ,float32 from_value, Units_clad from_units
      ,Units_clad    to_time_step
      ,float32 &to_value,  Units_clad to_units  ) const { return convert_with_time_step(from_time_step.get(),from_value,from_units.get(),to_time_step.get(),to_value,to_units.get()); }
      ///< Some units (such as solar radiation) have an implicit time step
      ///< in the time series where the time step units are not
      ///< part of the composed units.

   inline virtual bool convert_time                                              //971206
      (float32  from_value, Units_clad from_time_step
      ,float32 &to_value,   Units_clad to_time_step  ) const { return convert_time(from_value,from_time_step.get(),to_value,to_time_step.get()); } ;
      // Some units (such as solar radiation) have an implicit time step
      // in the time series where the time step units are not
      // part of the composed units.

public:  // intended to be used locally but may have common use:
   uint32 get_seconds_in(Units_code time_units) const;                           //050421
protected:                                                                       //020804
   void normalize_customary_units_to_metric(float32 &from_value, Units_component &from_units) const;
   bool convert_subunit
      (float32 from_value  , Units_component from_units
      ,float32 &to_value   , Units_component to_units) const;
   bool convert_metric_to_customary(float32 from_value,Units_component &from_units,float32 &to_value,Units_component &to_units) const; // 050613_
private: // The following are called by convert_metric_to_customary
   void normalize_to_metric_base_units(float32 &from_value,Units_component &from_units) const;
   bool convert_meter_to_customary(float32 from_value/*in meters*/,float32 &to_value,Units_component & to_SUC) const ; //050613
   float32 get_english_length_to_yards_multiplier(Units_component english_linear_units ) const;
};
//______________________________________________________________________________
extern Units_convertor units_convertor;

} // namespace CORN
#endif
//unitconv

