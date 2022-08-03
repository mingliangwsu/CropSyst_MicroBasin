#ifndef Soil_N_INTERFACE_H
#define Soil_N_INTERFACE_H
#include "corn/primitive.h"
#include "corn/const.h"
#include "corn/measure/measures.h"

#define   NH4_to_N_conv           (14.0 / 18.0)
#define   N_to_NH4_conv           (18.0 / 14.0)

#define   NO3_to_N_conv           (14.0 / 62.0)
#define   N_to_NO3_conv           (62.0 / 14.0)
//______________________________________________________________________________
interface_ Soil_nitrogen_interface
{
public:
   inline Soil_nitrogen_interface()  {}
public: // Get accessors
   virtual float64 get_NH4_ugN_gSoil                     (nat8  layer) const = 0;
   virtual float64 get_NO3_ugN_gSoil                     (nat8  layer) const = 0;
   inline virtual float64 get_NH4_mgN_MgSoil             (nat8  layer) const//150101
      { return   get_NH4_ugN_gSoil(layer) / 1000.0; }
   inline virtual float64 get_NO3_mgN_MgSoil             (nat8  layer) const//150101
      { return   get_NO3_ugN_gSoil(layer) / 1000.0; }

   virtual float64 get_NO3_molecular_mass_kg_m2          (nat8  layer) const = 0;
   virtual float64 get_NH4_molecular_mass_kg_m2          (nat8  layer) const = 0;

   virtual float64 get_N_mass_kg_m2                      (nat8  layer) const = 0;
   virtual float64 get_NO3_N_mass_kg_m2                  (nat8  layer) const = 0;
   virtual float64 get_NH4_N_mass_kg_m2                  (nat8  layer) const = 0;
   inline virtual float64 get_NO3_N_mass_kg_ha           (nat8  layer) const { return per_m2_to_per_ha(get_NO3_N_mass_kg_m2(layer)); } //150105
   inline virtual float64 get_NH4_N_mass_kg_ha           (nat8  layer) const { return per_m2_to_per_ha(get_NH4_N_mass_kg_m2(layer)); } //150105
#ifdef OLD_CHEMICAL_MASS
   virtual float64 set_NH4_molecular_mass_kg_m2          (nat8  layer,float64 new_amount) = 0;
#endif
   // This is only for output (I think) it applied only to V4.1
   virtual float64 get_NH4_N_mass_mineralized_from_PMN_kg_m2_profile() const = 0;
   // Should return 0 if not using V4.1 mode.

   // This is only for output (I think) it applied only to V4.1
   virtual float64 get_NH4_N_mass_mineralized_from_PMN_kg_m2(nat8  layer) const = 0;
   // Should return 0 if not using V4.1 mode.

public: // Set accessors
   virtual float64 set_NO3_N_mass_kg_m2                  (nat8  layer,float64 NO3_N_mass_kg_m2) modification_ = 0;
   virtual float64 set_NH4_N_mass_kg_m2                  (nat8  layer,float64 NH4_N_mass_kg_m2) modification_ = 0;
public:  // The following perform N uptake:
         // These are used for Crop N uptake and Microbe consumption for residue decomposition.
   virtual float64 uptake_N_mass(nat8  layer, float64 requested_pot_elemental_N_uptake_kg_m2) modification_ = 0;
   virtual float64 uptake_N_mass_from_NO3(nat8  layer, float64 requested_pot_elemental_N_uptake_kg_m2) modification_ = 0;
               // Attempts to remove the requested elemental N from the NO3 pool.
               // Returns the actual elemental N uptaken from the pool.
   virtual float64 uptake_N_mass_from_NH4(nat8  layer, float64 requested_pot_elemental_N_uptake_kg_m2) modification_ = 0;
               // Attempts to remove the requested elemental N from the NH4 pool.
               // Returns the actual elemental N uptaken from the pool.
public:
   // These functions add or removed amounts from the respective pools.
   // Derived classes may elect to store nitrogen as elemental amount
   // or the amount in molecular form.
   // The derived classes MUST implement one set of these accumulators
   // Either the elemental accumulators or the molecular accumulators
   // according to form the nitrogen is stored as.
   // The other set of accumulator methods should provided
   // that simply call the implemented accumulators passing the
   // converted values (using the respective convert_XXX() methods.
   // The derived class Soil_nitrogen_common provides default convertor methods.
   // Your nitrogen class can be derived from Soil_nitrogen_common
   // so you only need to override one set of these accumulators.

   // Elemental accumulators
   virtual float64 add_NO3_N_mass               (nat8  layer,float64 NO3_N_mass_addend) modification_ = 0;
   virtual float64 add_NH4_N_mass               (nat8  layer,float64 NH4_N_mass_addend) modification_ = 0;

   // Molecular accumulators
   virtual float64 add_NO3_molecular_mass       (nat8  layer,float64 NO3_mass_M_addend) modification_ = 0;
   virtual float64 add_NH4_molecular_mass       (nat8  layer,float64 NH4_mass_M_addend) modification_ = 0;
   virtual float64 subtract_NO3_molecular_mass  (nat8  layer,float64 NO3_mass_M_subtrahend) modification_ = 0;
   virtual float64 subtract_NH4_molecular_mass  (nat8  layer,float64 NH4_mass_M_subtrahend) modification_ = 0;
public: // returns a reference to
   virtual float64 &ref_ACC_NH4_released_to_atmosphere() = 0;
// check if still needed may be used in soil profile output,
// In that case it is necessary to read the values
   virtual float64 get_NO3_molecular_mass_kg_m2(nat8  layer) = 0;
   virtual float64 get_NH4_molecular_mass_kg_m2(nat8  layer) = 0;
   virtual float64 set_NO3_molecular_mass_kg_m2(nat8  layer,float64 new_mass) = 0;
   virtual float64 set_NH4_molecular_mass_kg_m2(nat8  layer,float64 new_mass) = 0;
   // This is to allow the residue class to update this value.
public: // The following are for balancing soil residue N in CropSyst only
   virtual void NO3_dec_residue                          (float64 NO3_amount_change_M) = 0;
   virtual void NH4_dec_residue                          (float64 NH4_amount_change_M) = 0;
public:  // Useful
   virtual float64 convert_NO3_N_to_molecular_mass(float64 NO3_N_mass)     const { return NO3_N_mass * N_to_NO3_conv; };
   virtual float64 convert_NH4_N_to_molecular_mass(float64 NH4_N_mass)     const { return NH4_N_mass * N_to_NH4_conv; };
   virtual float64 convert_NO3_molecular_to_N_mass(float64 NO3_mass)       const { return NO3_mass * NO3_to_N_conv; };
   virtual float64 convert_NH4_molecular_to_N_mass(float64 NH4_mass)       const { return NH4_mass * NH4_to_N_conv; };
public:  //
   virtual void commit_diffs()                                     modification_ = 0;
};
//______________________________________________________________________________
#endif

