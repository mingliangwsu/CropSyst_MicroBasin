#ifndef mass_commonH
#define mass_commonH
#include "corn/metrology/units_code.hpp"
#include "physics/mass.h"
#include "physics/property.h"
#include "common/weather/parameter/WP_temperature.h"

namespace Physical
{
// ______________________________________________________________________________
class Mass_common
: public extends_interface_   Mass
, public extends_             Property_complete
{
 public:
   Mass_common();                                                                //110909
   Mass_common(float64 _amount /*=0.0*/, CORN::Units_code _units = UC_kg_mass);
   Mass_common(const Mass &from);
public: // arithmetic
   virtual float64 add(const Mass &addend)                         modification_;
      // Probably should return (*this) not float64;
   inline virtual float64 multiply_by(float64 multiplier)          modification_
      { return Physical::Property_cowl<float64>::multiply_by(multiplier); }
};
// ______________________________________________________________________________
class Water
: public extends_ Physical::Mass_common
, public extends_interface_  Matter
{public:
   CS::Temperature temperature;                                                  //150529
 public:
   Water();
   Water(float64 mass
      ,CORN::Units_code mass_units
      ,float64 _temperature_C = 60.0
      ,CORN::Units_code temperature_units = UC_Celcius);
   Water(float64 volume_m3
      ,float64 _temperature_C = 60.0
      ,CORN::Units_code temperature_units = UC_Celcius);
   Water(const Water &from_copy);
   virtual float64 add(const Physical::Mass &addend)               modification_;
   inline virtual float64 get_density_kg_m3()                              const { return water_density_kg_m3; }
   inline virtual float64 gallon()                                         const { return m3() * 264.172052358148; } // m^3 -> gallon
   inline virtual bool clear()                                     modification_ { return Physical::Mass_common::clear(); }
   inline virtual bool is_empty()                                          const { return Physical::Mass_common::is_empty(); }
   inline virtual const Physical::Mass &ref_mass()                         const { return *this; }
   inline virtual float64 get_temperature_Celcius()                        const { return temperature.Celcius(); } //150529
   inline virtual float64 set_temperature_Celcius(float64 _temperature_C)   modification_ { return temperature.set_Celcius(_temperature_C, CORN::estimated_quality); } //150529
   inline virtual const Water &get_water()                                 const { return (*this); }
};
//_2011-06-30___________________________________________________________________
class Constituent_of_mass
: public extends_ Physical::Mass_common      // might need to be a matter, but currently it is only used as a mass
{  // This is a mass that is part of something else
 protected:
   const Physical::Mass *whole_mass;     // reference to the whole mass
 public:
   Constituent_of_mass(float64 _amount, CORN::Units_code _units,const Physical::Mass &of_mass);
   Constituent_of_mass(float64 _amount, CORN::Units_code _units,const Physical::Mass *of_mass);
   Constituent_of_mass(const Constituent_of_mass &copy_from);
   inline virtual float64 concentration_percent()                          const
      {  return concentration_fraction() * 100.0; }
   inline virtual float64 concentration_fraction()                         const
      {  float64 whole_mass_kg =  whole_mass->kg();
         return whole_mass_kg > 0.0 ? (kg()/whole_mass_kg) : 0.0;
      }
   inline virtual float64 set_concentration_percent(float64 concentration_percent) modification_
      {  return set_concentration_fraction(concentration_percent/100.0); }
   inline virtual float64 set_concentration_fraction(float64 concentration_fraction) modification_
      {  float64 new_amount_kg =  whole_mass->kg() * concentration_fraction;
         set_kg(new_amount_kg);                                                  //150316_150121_RLN
         return concentration_fraction;
      }
   inline virtual const Physical::Mass *know_whole_mass(const Physical::Mass *_whole_mass) modification_ //110803
      {  return whole_mass = _whole_mass; }
 protected:  // This constructor is just to make the compiler happy
   inline Constituent_of_mass() : Physical::Mass_common() , whole_mass(0) {}  //110909
};
//______________________________________________________________________________
class Constituent_of_matter
: public extends_ Constituent_of_mass
{  // This is a mass that is part of something else
 protected:
   const Matter *whole_matter;   // reference to the whole matter (may be 0 if not matter based)
 public:
   Constituent_of_matter(float64 _amount, CORN::Units_code _units,const Matter &of_matter);
   Constituent_of_matter(float64 _amount, CORN::Units_code _units,const Matter *of_matter);
   Constituent_of_matter(const Constituent_of_matter &copy_from);
   //NYI virtual float64 concentration_ppm()
   // If of whole_matter
   inline virtual float64 concentration_kg_per_m3()                        const
      {  float64 whole_m3 = whole_matter->m3();
         return (whole_m3 > 0.0) ? (kg()/whole_m3) : 0.0;
      }
   inline virtual float64 concentration_g_per_m3()                         const
      {  float64 whole_m3 = whole_matter->m3();
         return (whole_m3 > 0.0) ? (g()/whole_m3) : 0.0;
      }
   inline virtual float64 concentration_g_per_liter()                      const
      {  float64  whole_liter = whole_matter->liter();
         return (whole_liter > 0.0) ? (g()/whole_liter) : 0.0;
      }
   /* NYI
      could provide set_concentration_XXXX()
   */
    inline const Matter *know_whole_matter(const Matter *_whole_matter) modification_ //110803
       { know_whole_mass(&_whole_matter->ref_mass());
         return whole_matter = _whole_matter;
       }
 protected:  // This constructor is just to make the compiler happy
    inline Constituent_of_matter()                                               //110909
       : Constituent_of_mass()
       , whole_matter (0)
       {}
};
//______________________________________________________________________________
class Mass_elemental             // use when talking about the elemental mass amount
: public extends_ Constituent_of_matter
{public:
   const float64 atomic_mass;
public:
   Mass_elemental
      (float64 _amount, CORN::Units_code _units,const Matter &of_matter,float64 _atomic_mass);
   Mass_elemental
      (float64 _amount, CORN::Units_code _units,const Matter *of_matter,float64 _atomic_mass);
   Mass_elemental
      (const Mass_elemental&copy_from);
};
//______________________________________________________________________________
} // namespace Physical
#endif

