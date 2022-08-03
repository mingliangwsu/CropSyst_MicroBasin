#ifndef nitrogen_commonH
#define nitrogen_commonH
#  include "soil/nitrogen_interface.h"
#  include "soil/structure_interface.h"
#include <corn/const.h>
//______________________________________________________________________________
class Soil_nitrogen_common
: public Soil_nitrogen_interface
{
protected:
   unmodifiable_ Soil_structure_interface &structure;
public:
   inline Soil_nitrogen_common(unmodifiable_ Soil_structure_interface &_structure)
      : Soil_nitrogen_interface()
      , structure(_structure)
      {}
   inline Soil_nitrogen_common                                                   //140610
      (const Soil_nitrogen_common &copy_from,float64 fraction)
      : Soil_nitrogen_interface()
      , structure(copy_from.structure)
      {}
public: // Get accessors
   inline virtual float64 get_NH4_ugN_gSoil                  (nat8 layer)  const { return structure.kg_per_m2_to_micrograms_per_g(layer,get_NH4_N_mass_kg_m2(layer));}
   inline virtual float64 get_NO3_ugN_gSoil                  (nat8 layer)  const { return structure.kg_per_m2_to_micrograms_per_g(layer,get_NO3_N_mass_kg_m2(layer));}
   virtual float64 get_NO3_molecular_mass_kg_m2              (nat8 layer)  const = 0;
   virtual float64 get_NH4_molecular_mass_kg_m2              (nat8 layer)  const = 0;
   inline  virtual float64 get_N_mass_kg_m2                  (nat8 layer)  const { return get_NO3_N_mass_kg_m2(layer) + get_NH4_N_mass_kg_m2(layer); }
   virtual float64 get_NO3_N_mass_kg_m2                      (nat8 layer)  const = 0;
   virtual float64 get_NH4_N_mass_kg_m2                      (nat8 layer)  const = 0;
   #ifdef OLD_CHEMICAL_MASS
   virtual float64 set_NH4_molecular_mass_kg_m2              (nat8 layer,float64 new_amount) = 0;
      // This is only for output (I think) it applied only to V4.1
   #endif
   virtual float64 get_NH4_N_mass_mineralized_from_PMN_kg_m2_profile()     const = 0;
      // Should return 0 if not using V4.1 mode.

      // This is only for output (I think) it applied only to V4.1
   virtual float64 get_NH4_N_mass_mineralized_from_PMN_kg_m2(nat8 layer)   const = 0;
      // Should return 0 if not using V4.1 mode.
public: // Set accessors
   virtual float64 set_NO3_N_mass_kg_m2(nat8 layer,float64 NO3_N_mass_kg_m2) = 0;
   virtual float64 set_NH4_N_mass_kg_m2(nat8 layer,float64 NH4_N_mass_kg_m2) = 0;
public: // The following perform N uptake:
   virtual float64 uptake_N_mass(nat8 layer, float64 requested_pot_elemental_N_uptake_kg_m2) modification_;
   virtual float64 uptake_N_mass_from_NO3(nat8 layer, float64 requested_pot_elemental_N_uptake_kg_m2) modification_ = 0;
               // Attempts to remove the requested elemental N from the NO3 pool.
               // Returns the actual elemental N uptaken from the pool.
   virtual float64 uptake_N_mass_from_NH4(nat8 layer, float64 requested_pot_elemental_N_uptake_kg_m2) modification_ = 0;
               // Attempts to remove the requested elemental N from the NH4 pool.
               // Returns the actual elemental N uptaken from the pool.
public:
   // When you derive from Soil_nitrogen_common you will
   // store N values either as elemental or molecular amounts.
   // If you store as element amounts, then you must
   // you must override the elemental accumulator
   // otherwise you must override the molecular accumulators.
   // These accumulators as implemented here are provided as
   // a convenience they simply call the other set of accumulator methods
   // with the respective conversions.
   // You must override one set of these accumulators otherwise they go into an infinate loop.
   //
   // Elemental accumulators:
   virtual float64 add_NO3_N_mass(nat8 layer,float64 NO3_N_mass_addend)          modification_;
   virtual float64 add_NH4_N_mass(nat8 layer,float64 NH4_N_mass_addend)          modification_;
   // Molecular accumulators
   virtual float64 add_NO3_molecular_mass(nat8 layer,float64 NO3_mass_M_addend)  modification_;
   virtual float64 add_NH4_molecular_mass(nat8 layer,float64 NH4_mass_M_addend)  modification_;
//NYI   virtual float64 subtract_NO3_mass_molecular           (nat8 layer,float64 NO3_mass_M_subtrahend);
//NYI   virtual float64 subtract_NH4_mass_molecular           (nat8 layer,float64 NH4_mass_M_subtrahend);
public: // returns a reference to
   virtual float64 &ref_ACC_NH4_released_to_atmosphere() = 0;
   // This is to allow the residue class to update this value.
public: // The following are for balancing soil residue N in CropSyst only
   virtual void NO3_dec_residue(float64 NO3_amount_change_M)                     modification_ = 0;
   virtual void NH4_dec_residue(float64 NH4_amount_change_M)                     modification_ = 0;
public:  // Useful
   inline virtual float64 convert_NO3_N_to_molecular_mass(float64 NO3_N_mass)    const { return NO3_N_mass * N_to_NO3_conv; }
   inline virtual float64 convert_NH4_N_to_molecular_mass(float64 NH4_N_mass)    const { return NH4_N_mass * N_to_NH4_conv; }
   inline virtual float64 convert_NO3_molecular_to_N_mass(float64 NO3_mass)      const { return NO3_mass * NO3_to_N_conv; }
   inline virtual float64 convert_NH4_molecular_to_N_mass(float64 NH4_mass)      const { return NH4_mass * NH4_to_N_conv; }
};
//______________________________________________________________________________
#endif

