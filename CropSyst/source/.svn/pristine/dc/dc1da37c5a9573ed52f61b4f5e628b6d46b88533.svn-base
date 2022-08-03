#ifndef crop_biomassH
#define crop_biomassH

#include "common/biomatter/biomass_abstract.h"

// Crop_biomass is used in transferring crop biomass for nitrogen fate
// Note that the CropSyst crop model stores nitrogen mass
// and nitrogen concentration and carbon mass are calculated.

namespace CropSyst {
//______________________________________________________________________________
 class Crop_biomass
: public Biomass_abstract
{
protected:
   float64 nitrogen_mass;
public: // constructors
   Crop_biomass(float64 _biomass = 0.0, float64 _nitrogen_mass = 0.0)            //070702
      : Biomass_abstract
         (_biomass                                                               //070702
         ,0  // Carbon(fraction) Not yet needed, we will have to to specify a carbon nitrogen ration or carbon fraction if we need Crop carbon in the future
         ,0  // Carbon nitrogen ratio is not yet needed, we currently store nitrogen_mass for this.
         ,1  // decomposition constant                                           //100215
         )
      , nitrogen_mass(_nitrogen_mass)                                            //070702
      {
         //070702_ NYN should fix up n conc and C/N ratio
      }
#ifdef NYN
Currently not copied
/*090702_*/    Crop_biomass(const Crop_biomass &copy_from);
/*090702_*/    inline virtual Crop_biomass *clone()                        const { return new Crop_biomass(*this); }
#endif
public: // Accessors for mass components
   inline float64 get_nitrogen_mass()                                      const { return nitrogen_mass; }
   inline virtual float64 get_nitrogen_concentration()                     const
      { return kg() ? nitrogen_mass/ kg() : 0.0; }                               //101012
public: // Accessors for mass components
   inline float64 reset_nitrogen_mass(float64 _nitrogen_mass)                    {nitrogen_mass = _nitrogen_mass; return nitrogen_mass; }
   inline float64 add_crop_biomass(const Crop_biomass &augend)
    { (*amount_ptr) += augend.kg(); nitrogen_mass += augend.nitrogen_mass; return kg();}   //101012 070802
};
//_2007-04-12___________________________________________________________________
}
//______________________________________________________________________________
#endif
