#ifndef units_cladH
#define units_cladH
#ifndef units_codeHPP
#   include "corn/metrology/units_code.hpp"
#endif
#include "corn/const.h"
#include <string>
namespace CORN {

//______________________________________________________________________________
class Units_component                                                            //990511
{
/** Standard generalized units codes are composed of two 16bit subcodes.
    The subcode in the upper 16bits is the secondary units.
    The code in the lower 16bits in the primary units.
    They both have the same format.
*/
 public:
   nat16   subcode;
 public:
   inline Units_component(nat16  _subcode)
      : subcode(_subcode)
      {}
   inline nat16  get()                                                     const //050607
      { return subcode; }
   inline nat16  set(nat16  _subcode)  { subcode = _subcode; return subcode; }   //061019
   bool  compose_common_description
      (char *component_description, char *component_abbr)                  const;//030922
      ///< both standard and non standard may use secondary (divided by) and time
   bool  compose_standard_description
      (char *component_description, char *component_abbr)                  const;//090511
   bool  compose_nonstandard_description
      (char *component_description, char *component_abbr)                  const;//030922
   sint8 get_metric_exponent()                                             const;
      ///< probably should return uint
   nat8  set_metric_exponent(nat8  metric_exponent);                             //050706
   inline nat8  get_measure_index() const
      { return (nat8 )((subcode & 0x7F00) >> 8); }
      ///< \return does not include non standard flag.
   inline void set_measure_index(nat8  measure)                                  //020503
      { subcode = (nat16 )(((nat16 )measure << 8) | (nat16 )(subcode &0x00FF)); }
   inline void set_denominator(bool denominator)                                 //061011
      { subcode = (nat16 )(((nat16 )denominator << 7) | (nat16 )(subcode &0xFF7F)); }
   inline nat8  get_submeasure_index()                                     const //020503
      { return (nat8 )(subcode & 0x007f); }
      ///< \return does not include denominator indicator
   const char *get_measure_quantity_description()                          const;//050707
   inline bool is_denominator()                                     affirmation_
      { return  (nat16 )(subcode & 0x0080) > 0; }
   float32 standard_conversion_to_factor
      (const Units_component &to_general_sub_units) const;
      ///< Standard_conversion_to_factor requires that both this and the to_sub_units
      /// are both standard (metric)
   void clear_metric_exponent();                                                 //050613
      ///< This is used by units convertor get get the normal units code
   inline bool is_standard()                                        affirmation_ //020503
      { return !(subcode & 0x8000); }
   inline bool is_imperial()                                        affirmation_ //021023
      { return (subcode & 0x8000) && (subcode & 0x0040);}
   bool is_temporal()                                              affirmation_; //170520
  private:
      float32 time_to_seconds_factor(nat8  time_measure, int8 base_10_exponent) const;
};
//______________________________________________________________________________
class Units_clad                                                                 //980624
{public:
    Units_code code;
 public:
   inline Units_clad(Units_code _code)
      : code(_code)
      {}
   inline Units_clad                                                             //050613
      (Units_component  primary_units
      ,Units_component  secondary_units)
      : code (((nat32)secondary_units.subcode << 16)
              |primary_units.subcode)
      {}
      ///< Generalized standard codes
   inline Units_clad
      (nat8   primary_quantity
      ,nat8   primary_units_system
      ,nat8   secondary_quantity
      ,nat8   secondary_units_system)
      : code (U_secondary(secondary_quantity,secondary_units_system)
             |U_primary(primary_quantity,primary_units_system))
      {}
      ///< Generalized standard codes
   inline Units_clad
      (nat8    primary_quantity
      ,nat8    primary_units_system
      ,nat16   secondary_units)
      : code (((nat32)secondary_units << 16)
              |U_primary(primary_quantity,primary_units_system))
      {}
      ///< Generalized standard codes
   inline Units_clad
      (nat16   primary_units
      ,nat8    secondary_quantity
      ,nat8    secondary_units_system)
      : code (primary_units
              |U_secondary(secondary_quantity,secondary_units_system))
      {}
      ///< Generalized standard codes
   inline Units_clad
      (nat32  physical_property_code
      ,nat8    units_system
      ,bool    non_standard = false)                                             //990510
      : code (((nat32)non_standard << 31)
               | (0x8000) // make sure it is a physical property
              |((nat32)physical_property_code << 8) | (nat32)units_system)
      {}
      ///< Constructor for physical properties derived code
   inline virtual ~Units_clad() {}                                               //130515
   inline nat32 get()                                                      const { return code; }
   inline nat32 set(Units_code _code)                                            { code = _code; return code; }
   nat32 set_label(const char *abbreviation_or_description);                     //060626
      ///< Sets the units code given abbreviation or descrition.
      /// \return 0 if not a recognized units code
public:  // Genereralized standard
   inline nat16  get_primary()                                             const
      { return (nat16 )((code & 0x0000FFFF)); }
   inline nat16  get_secondary() const
      { return (nat16 )((code & 0xFFFF0000) >> 16); }
   // Returns 0 if no secondary units
   inline nat16  set_primary(const Units_component &primary_component)           //050707
      {  code = (code & 0xFFFF0000) | primary_component.get();
         return (nat16 )code;
      }
   inline nat16  set_secondary(const Units_component &secondary_component)
      {  code = (code & 0x0000FFFF) | (secondary_component.get() << 16);
         return (nat16 )code;
      }
public:
   virtual const char *label_string(std::string &buffer)                  const; //170423
   bool  compose_description(char *component_descr, char *component_abbr) const; //030123
   bool  compose_description_str(std::string &component_descr, std::string &component_abbr)  const; //170114
      ///<  Composes a text description of the units
   bool  is_temporal()                                             affirmation_; //170520
   int16 has_definition()                                          affirmation_;
};
//______________________________________________________________________________
} // namespace CORN
#endif

