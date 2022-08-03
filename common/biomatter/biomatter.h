#ifndef biomatterH
#define biomatterH
#ifndef biomassH
#  include "common/biomatter/biomass.h"
#endif
#include "physics/mass.h"
#include "corn/container/item.h"
#include <assert.h>
//______________________________________________________________________________
interface_ Biomatter                                                             //100820
: public  extends_interface_ Biomass
, public  extends_interface_ Physical::Matter_wet                                //150216_100820
{
   virtual const Physical::Mass &ref_mass()                                const { return *this; } //150215RLN
   inline virtual Biomatter *extract_mass_wet_kg(float64 mass_wet_kg) modification_
      {  assert(false);  //110804 temporary to work out inheritence issue
         return 0;
      }
      /**< \fn \brief Extracts the specifies mass on a wet basis including water mass.
      \details Derived classes should override with a covarient return type.
      \return Similar to extract_mass_kg() but using wet weight basis.
      \date 2010-03-03
       */
   inline virtual Biomatter *extract_volume_m3(float64 volume_to_extract) modification_
      {  assert(false);  //110804 temporary to work out inheritence issue
         return 0;
      }
   /** < \fn \brief Removes the specified volume.
   \details  All extensive
   properties are reduced proportional to the volume extracted.
   The returned biomass will be of the type of the
   derived instanciated class.
   The caller can use dynamic_cast if necessary to check/get the correct type.
   Although extract_volume could be applicable to Biomass,
   volume is usually only applicable to biomass that has
   some level of moisture, so it is only defined for Bimass_wet().
   \return The actual biomass extracted or all of it if the
   volume_to_extract exceeds the current volume.
   May return 0 if there is no volume or mass is 0.
   \date 2010-03-03
    */
   inline virtual float64  get_pH()                                        const   // From Situated_biomatter
      {  assert(false);  //110804 temporary to work out inheritence issue
         return 0;
      }
      ///< \return potential hydrogen
   inline virtual float64 add_similar_biomatter
      (const Biomatter &added_biomatter)                           modification_
      {  assert(false);  //110804 temporary to work out inheritence issue
         return 0;
      }
   inline virtual Biomatter *clone()                                       const
      {  assert(false);  //110804 temporary to work out inheritence issue
         return 0;
      }
};
//______________________________________________________________________________
// I decided to not to have Biomatter be derived from Item
// because I haven't needed these for CANMS or CropSyst
// Instead I provide the ability to have a list of referencing pointers.
/*150714
class Biomatter_item
: public extends_interface_ CORN::Item
{public:
   Biomatter *biomatter; bool owns_biomatter;
 public:
    inline Biomatter_item(Biomatter *_biomatter, bool _take_biomatter)
      : CORN::Item()
      , biomatter       (_biomatter)
      , owns_biomatter  (_take_biomatter)
      {}
    inline virtual ~Biomatter_item()
      {  if (owns_biomatter) delete biomatter;
      }
};
*/
//_2015-07-06___________________________________________________________________

#endif

