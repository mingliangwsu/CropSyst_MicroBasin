#ifndef biomatter_abstractH
#define biomatter_abstractH
#include "common/biomatter/biomass_abstract.h"
#include "physics/mass_common.h"
#include "common/biomatter/biomatter.h"
#include "CS_suite/observation/CS_observation.h"
class Situation;
//______________________________________________________________________________
class Biomatter_abstract
: public extends_             Biomass_abstract    // Not sure if virtual or not
, public extends_interface_   Biomatter                                          //100228
{private:
   provided_ Situation *situation;                                               //110804
 public:  //100816 should be protected:
   float64 pH;
 public:
   Physical::Water water;                                                        //150215RLN_110630
      //   Note that the mass of the water is the same as to biomass itself (was kg)  //100930
   float64 volume_m3; // extensive  including water and solids
 public: // 'structors
   Biomatter_abstract
      (float64 _carbon_fraction      =0                                          //070726
      ,float64 _carbon_nitrogen_ratio=0);                                        //070726
   Biomatter_abstract(const Biomatter_abstract &from_copy);  // copy constructor
   Biomatter_abstract(const Biomatter &from_copy);  // copy constructor given an interface //100303
   virtual Biomatter_abstract *clone()                                    const;
 public: // reimplementation
   virtual bool clear()                                            modification_; //070726_160620
   virtual float64 multiply_by(float64 multiplier)                 modification_;
public:
   inline virtual float64 get_pH()                                         const { return pH; }
   float64  set_pH(float64 _pH)                                     modification_{ return pH = _pH; }
   inline virtual const Physical::Water &get_water()                       const { return water; } //150215
   virtual modifiable_  Physical::Water &mod_water()                             { return water; } //150215
      inline virtual float64 get_temperature_Celcius()                     const { return water.temperature.Celcius(); } //150529
   inline virtual const float64 &ref_temperature_Celcius()                 const { return (water.temperature.ref_amount()); } //150529
   inline virtual float64 set_temperature_Celcius(float64 temperature_C_) modification_ { return water.set_temperature_Celcius(temperature_C_); }
   virtual float64 set_mass_wet_at_percent_moisture                              //090729
      (float64 new_mass_wet,CORN::Units_code new_units,float64 at_moisture_percent) modification_;
      // NYI rename this to init_mass_wet_at_percent_moisture because it
      // should only be used for initialization
   inline virtual float64 get_volume_m3()                                  const { return volume_m3; };
      // Derived classes should reimplement get_volume_m3() if they maintain a volume.
   float64 set_moisture_percent
      (float64 new_moisture)                                      modification_;
   virtual float64 subtract_water_vol(float64 water_volume_m3)    modification_; //020815
      ///< \return the act vol subtracted.  May be limited by available water
      //100816  rename this to extract_water_vol
   virtual Biomatter *extract_mass_wet_kg(float64 mass_wet_kg)    modification_; //100303
      //100930 NYI modifiy this to take the desired units
   virtual Biomatter_abstract *extract_volume_m3(float64 vol_to_extract_m3) modification_;//150325_050303
      // This method removes the specified volume.
      // or all of it if the volume is not satisfied
      // Returns the actual volume extracted (incase there is not the requested amount).
   virtual float64 add_similar_biomatter(const Biomatter &added_biomatter) modification_; // 100901
   virtual float64 add(const Physical::Mass &addend)              modification_;//100908
   Situation &provide_situation()                                    provision_;//110804
   RENDER_INSPECTORS_DECLARATION;                                               //150917RLN
};
//_2010-08-20__________________________________________________________________/

#endif

