#ifndef elementsHPP
#define elementsHPP
//---------------------------------------------------------------------------
#include "physics/mass_common.h"
#include "chemistry/elements.h"

#define declare_mass_elemental(Mass_class_name,element_atomic_mass)              \
class Mass_class_name                                                            \
: public Physical::Mass_elemental                                                \
{public:                                                                         \
   inline Mass_class_name(float64 _amount, CORN::Units_code _units,const Physical::Matter &of_matter)\
      : Physical::Mass_elemental(_amount,_units,of_matter,(element_atomic_mass)) \
      {};                                                                        \
   inline Mass_class_name(float64 _amount, CORN::Units_code _units,const Physical::Matter *of_matter)\
      : Physical::Mass_elemental(_amount,_units,of_matter,(element_atomic_mass)) \
      {};                                                                        \
   inline Mass_class_name(const Mass_class_name &copy_from)                      \
      : Physical::Mass_elemental(copy_from)                                      \
      {};                                                                        \
};
//_2011-07-31___________________________________________________________________
declare_mass_elemental(Mass_nitrogen      ,nitrogen_atomic_mass)
declare_mass_elemental(Mass_phosphorus    ,phosphorus_atomic_mass)
declare_mass_elemental(Mass_potassium     ,potassium_automic_mass)
declare_mass_elemental(Mass_carbon        ,carbon_atomic_mass)
#endif

