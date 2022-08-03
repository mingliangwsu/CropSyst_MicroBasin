#ifndef biomassH
#define biomassH
#include "corn/primitive.h"
#include "corn/const.h"
#include "corn/math/compare.hpp"
#include "physics/mass.h"
#include "CropSyst/source/organic_matter/OM_types.h"
// ______________________________________________________________________________
#define crop_nitrogen_phosphorus_ratio  6.0
// ______________________________________________________________________________
interface_ Biomass
: public extends_interface_ Physical::Mass
{
   /// Note that mass includes only organic decomposable compounds.
   /// No TAN or gases that have under gone decomposition and are to be expelled.
   /// Bone, shell or other such biogenic material may be included
   /// in live body weight mass,
   /// but should be separate in decomposing carcasses.
   inline virtual float64 dry_kg()                                         const { return kg(); }
   inline virtual float64 get_total_solids_kg()                            const { return kg(); }

   // These methods have implementation, but are considered abstract
   // because they use abstract methods.
   /** Derived classes will either store elemental masses, molecular masses
   or elements or molecular amounts as fraction of the total mass
   thus, they must either reimplement get_XXX_mass()
   or get_XXX_fraction get_XXX_ratio() methods accordingly
    */
   inline virtual float64 get_carbon_total_kg()                            const
      {  return kg() * get_carbon_fraction(); }
   inline virtual float64 get_carbon_organic_kg()                          const //150508
      {  return get_carbon_total_kg() * get_carbon_organic_fraction(); }
   inline virtual float64 get_carbon_organic_cycling_kg(Organic_matter_cycling cycling) const //150629RLN
      { return get_carbon_organic_kg(); }
      // default assumes there is only one cycling.
      // This was added for NIFA manure, but probably applied to
      // all organic matter.
   inline virtual float64 get_carbon_inorganic_kg()                        const //150508
      {  return get_carbon_total_kg() * (1.0 - get_carbon_organic_fraction()); }
   inline virtual float64 get_carbon_organic_fraction()                   const  //150508
      { return 1.0; }
   inline virtual float64 get_nitrogen_organic_kg()                       const
      {  return get_carbon_total_kg() / get_carbon_nitrogen_ratio(); }           //150512BRC - may be get_carbon_organic_kg()
      // Note that this nitrogen is always organic
      // and must not include other nitrogen forms of nitrogen (I.e. ammonia)
   #define get_nitrogen_mass() get_nitrogen_organic_kg()
   inline virtual float64 get_nitrogen_inorganic_kg()                     const
      {  return get_nitrogen_Kjeldahl_kg() - get_nitrogen_organic_kg(); }
   inline virtual float64 get_nitrogen_Kjeldahl_kg()                       const
      {  return get_nitrogen_organic_kg();
         /* by default no TAN */ }
      // Kjeldahl_N is organic N + ammonical N
      // By default Biomass is organic matter
      // derived classes (I.e. Manure) may have ammonical nitrogen (TAN) and
      // should reimplement get_nitrogen_Kjeldahl() to include TAN.
   inline virtual float64 get_nitrogen_organic_fraction()                  const //150508BRC
      { return 1.0; }
   virtual float64 get_carbon_fraction()                                   const;
      // Derived classes may have a overide to provide a fixed carbon fraction
   inline virtual float64 get_volatile_solids_percent()                    const //110726
      { return 80.0;
         // Warning: Derived classes should reimplement
      } // source Dairy manure composition (Stafford, Hawkes etal. 1980);
   inline virtual float64 get_volatile_solids_kg()                         const
      { return get_total_solids_kg() * get_volatile_solids_percent()/100.0; }
   inline virtual float64 get_nitrogen_fraction()                          const
      {  return get_nitrogen_organic_kg() / kg(); }
   inline virtual float64 calc_carbon_nitrogen_ratio()                     const
      {
         //170228RLN return get_carbon_total_kg() / get_nitrogen_organic_kg();               //150512BRC - may be get_carbon_organic_kg()
         // Need to avoid div0                                                   //170228RLN
         float64 C = get_carbon_total_kg();
         float64 N = get_nitrogen_organic_kg();
         float64 CN
          = (CORN::is_approximately<float64>(C,0.0,0.000001) ||
             CORN::is_approximately<float64>(N,0.0,0.000001))
          ? 0.0 : C/N; return CN;
      }
   inline virtual float64 get_carbon_nitrogen_ratio()                 provision_
      { return calc_carbon_nitrogen_ratio(); }
      // Derived classes may have a fixed or variable carbon nitrogen ratio.
   inline virtual float64 get_nitrogen_phosphorus_ratio()                  const //110731
      { return calc_nitrogen_phosphorus_ratio(); }
   inline virtual float64 calc_nitrogen_phosphorus_ratio()                 const //110731
      { return get_nitrogen_Kjeldahl_kg() / get_phosphorus_total_kg(); }
   inline virtual float64 get_decomposition_constant(Organic_matter_cycling cycling = OM_INTRINSIC_CYCLING) const //150629
      {  return 0.0; }
   inline virtual float64 get_phosphorus_total_kg()                        const //110731
      { return get_nitrogen_mass() / get_nitrogen_phosphorus_ratio() ; }
   inline virtual float64 get_phosphorus_organic_kg()                      const //150508
      { return get_phosphorus_total_kg() * get_phosphorus_organic_fraction(); }
   inline virtual float64 get_phosphorus_inorganic_kg()                    const //150508
      { return get_phosphorus_total_kg() * (1 - get_phosphorus_organic_fraction()); }
   inline virtual float64 get_phosphorus_organic_fraction()                const //150511_100303
      { return 1; }
   virtual Biomass *extract_fraction(float64 fraction)             modification_ = 0; //100228
   virtual Biomass *extract_mass_kg(float64 mass_kg)               modification_ = 0; //100303

   // Methods required for derived classes to implement extraction methods.
   virtual Biomass *clone()                                                const = 0;
      /** < \fn \brief Creates a copy of the object's attributes.
      \details Derived classes should override copying extended attributes.
      Owned pointer references (if any) will be copied and ownership
      of the pointed to object (if owned by the original object)
      is left with the original object, they will not be owned by the copy.
      Copying of contributes is recommended, but not expected.
      \return The object copy derived classes should return the covarient type.
       */

  // arithmetic
   virtual float64 add_mass(float64 mass_dry_to_add)               modification_;
      /** < \fn \brief
      All extensive properties are increased proportionally
      by the increase in total dry mass.
      \details Becareful using add_mass and substract_mass methods,
      because this simply increases all extensive mass components proportionally.
      Often one will want to add different mass pools,
      in that case use add_similar_mass() or assimilate_mass()
      elsewhere defined in derived classes.
      \return the actual dry mass added
      (should always be able to add the specified amount)
       */
   virtual float64 subtract_mass(float64 mass_dry_to_subtract)     modification_;
      /** < \fn \brief All extensive properties are reduced proportionally
         by the reduction in total dry mass.
      \return the actual dry mass subtracted (may not be able to subtract all)
       */
   virtual float64 multiply_by(float64 multiplier)                 modification_ = 0;
      /** < \fn \brief Multiplies all extensive properties by the multiplier.
      \details Derived classes should reimplement the method to multiply
      any added extensive properties.
      The overridding method should call the immediate superclass's
      multiply_by method.
      \return the new dry mass
      \date 2010-03-03
       */
   virtual float64 divide_by(float64 divisor)                      modification_;
      /** < \fn \brief Divides all extensive properties by the divisor.
      \details This method is implemented by calling multiply() with 1.0/divisor
      Divisor should be greater than 0.0, but negative numbers are allowed.
      Does nothing if divisor is approximately 0.0 (to avoid div0)
      so it is not necessary to reimplement this method.
      \return The new dry mass.
      \date 2010-03-03
       */
   inline virtual bool process_day()                               modification_ //150611RLN
      {  return true; }
   virtual bool deduct_decomposition
         (float64 mass_decomposition
         ,float64 C_decomposition, float64 N_decomposition
         ,Organic_matter_cycling cycling = OM_SINGLE_CYCLING)      modification_ { assert(false); return false; } //150704RLN

   virtual const Physical::Mass &ref_mass()                                const { return *this; } //150711RLN

   // calculators (amounts of this biomass given specific properties or conditions)
   // These are valid interface methods because they are based on interface methods
   float64 calc_concentration_mass_fraction(float64 component_mass)        const;// 100802
   float64 calc_concentration_mass_percent(float64 component_mass)         const;// 100802
};
//_2006-03-16___________________________________________________________________
#endif

#define get_carbon_kg() get_carbon_total_kg()
#define get_phosphorus_kg() get_phosphorus_total_kg()
#define get_nitrogen_organic() get_nitrogen_organic_kg()
#define get_nitrogen_inorganic() get_nitrogen_inorganic_kg()

