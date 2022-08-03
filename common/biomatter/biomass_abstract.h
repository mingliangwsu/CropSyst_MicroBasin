#ifndef biomass_abstractH
#define biomass_abstractH
#include "physics/mass_common.h"
#include "common/biomatter/biomass.h"
#include "corn/container/enumlist.h"
#include "CS_suite/observation/CS_observation.h"
//______________________________________________________________________________
class Biomass_abstract
: public extends_interface_    Biomass                                           //100211
, public Physical::Mass_common                                                   //101019_100819
   /*virtual removed virtual because Mass_common constructor was not called */
, public CORN::Enumeration                                                       //090728
{
 protected:  // state (adjusts as mass changes) These could probably be moved to biomass abstract
   mutable   float64  carbon_fraction;          // intensive property  //070726
      // for most plants, this is about 0.5 with only slight variation (ref:Carbon inventory methods By N. H. Ravindranath, Madelene Ostwald pg 32) 070726
   provided_ float64  carbon_nitrogen_ratio;    // intensive property  //070726
      // (ratio of organic carbon and nitrogen. Does not include inorganic N such as TAN)
   mutable   float64  decomposition_constant;
                  // Note that the decomposition rate constants are different for each model and each organic matter type!

   // 100813 the decomposition constant should be a parameter/property (needs to be moved)
   // of the decomposition class which is separate from
   // the biomass.
   // The decompostion class either extends Biomass or has Biomass as a member.


/* Common C:N ratios
See http://weblife.org/humanure/chapter3_7.html
also:
Fresh compost     30:1
Finished compost  10:1
Bark 120:1
Paper 170:1
Coffee Grounds 20:1
Pine Needles 70:1
Cow Manure 20:1
Poultry Manure 10:1
Corn Stalks 60:1
Sawdust 500:1
Grass Clippings
20:1 Straw 40-100:1
Horse Manure 25:1
Vegetable Wastes 12-20:1
Leaves 60:1
Wood Chips 100-500:1
Leguminous 15:1

See also for various manure C:N ratios
http://www.klickitatcounty.org/solidwaste/ContentROne.asp?fContentIdSelected=313956151&fCategoryIdSelected=965105457

Bone meal and Meat scraps  6:1
source:  Gradening when it counts.  Steve Solomon
 http://books.google.com/books?id=lbohaJCxFnAC&pg=PA184&lpg=PA184&dq=carbon+nitrogen+ratio+meat&source=bl&ots=EG8t1_HWNx&sig=OocfIUSQcngVGmW1U3FUECVKdQs&hl=en&ei=JJmASq7mCJHSsQPQxs33CA&sa=X&oi=book_result&ct=result&resnum=3#v=onepage&q=carbon%20nitrogen%20ratio%20meat&f=false

*/

/* Common N:P Ratios
Total plant  6:1
Plant root   is lower than top
Woody plant roots may be higher that herbacious

Manure 6:1  (ranging from 5 to 7)
http://dairynutrient.wisc.edu/468/page.php?id=430

Boiler litter 2.2
Dairy manure  3.9
Swine slurry  2.3
source: Soil Phosphorus: Management and Recommendations (Univ. Arkansas, division of agriculture
http://www.uaex.edu/Other_Areas/publications/pdf/FSA-1029.pdf
*/
 public:
   Biomass_abstract();
   Biomass_abstract
      (float64 _mass_dry
      ,float64 _carbon_fraction        =0                                        //070726
      ,float64 _carbon_nitrogen_ratio  =0                                        //070726
      ,float64 _decomposition_constant=0.0);    // Decomposition constant can be 0 for living matter //070726
   Biomass_abstract(const Biomass_abstract &from_copy);
   Biomass_abstract(const Biomass &from_copy);                                   //100303
      // don't clear carbon_fraction and carbon_nitrogen_ratio, these are properties
   inline virtual ~Biomass_abstract() {}
      // Destructor added to enable virtual distruction //141104
   virtual Biomass_abstract *clone()                                       const;
   inline virtual bool is_key_nat32(nat32 key)              affirmation_;  //180820
   virtual nat32 get_key_nat32()                                           const;//020319

 public: // Accessors
   inline virtual float64 init_mass_dry(float64 new_mass_dry)      modification_ //090713
      {  return update_amount_in_preset_units(new_mass_dry);                     //150316_150121
      }
 public:  // Accessors for mass components
         // Derived classes may store component masses differently
         // for example:
         // The stable organic matter and residue store carbon fraction
         // and then carbon nitrogen ratio.
         // Whereas, the CropSyst crop stores nitrogen mass
         // so nitrogen concentration, carbon fraction and mass is calculated. 070412
   inline  virtual float64 get_carbon_fraction()                      provision_
      { return carbon_fraction; }
           virtual float64 get_carbon_nitrogen_ratio()                provision_;
   inline virtual float64 get_nitrogen_phosphorus_ratio()                  const //110731
      { return crop_nitrogen_phosphorus_ratio; }
   inline  virtual float64 get_decomposition_constant(Organic_matter_cycling cycling = OM_INTRINSIC_CYCLING) const //150629
      { return decomposition_constant; }
 public: // modifiers
   virtual float64 multiply_by(float64 multiplier)                 modification_;
   virtual float64 reset_mass(float64 new_mass)                    modification_;//070707
      // set_mass() is used by Organic_matter_pools_multiple::respond_to_field_operation()   //060727
      // This resets all mass amounts relative to the new_mass value.                        //060727
      // Care should be taken when using this method for biomasses as part of a mass balance.//060727
   virtual float64 add_similar_mass(const Biomass &similar_mass);                            //060727
              //100802 rename this to add_similar
              //100908 probably can be removed and use add(Mass)
   virtual float64 add(const Physical::Mass &addend)               modification_;//100908
   // return types can be covariant Biomass                                      //150325
   virtual Biomass_abstract *extract_fraction(float64 fraction)    modification_;//100228
   virtual Biomass_abstract *extract_mass_kg(float64 mass_kg)      modification_;//100303
   inline float64 set_carbon_nitrogen_ratio (float64 new_CN_ratio)  assignation_ { return carbon_nitrogen_ratio = new_CN_ratio; }
      // May return 0 if the biomass is empty
   inline float64 set_carbon_fraction (float64 new_C_fraction)      assignation_ { return carbon_fraction = new_C_fraction; }
   RENDER_INSPECTORS_DECLARATION;                                                //151020BRC
};
//_2006-03-16___________________________________________________________________
#endif


