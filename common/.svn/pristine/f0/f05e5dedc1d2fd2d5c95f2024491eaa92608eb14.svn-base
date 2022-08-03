#ifndef propert_cowlH
#define propert_cowlH
#include "common/physics/property.h"
#include "corn/measure/unitconv.h"
#include "corn/math/compare.hpp"
namespace Physical
{
//______________________________________________________________________________
template <typename Real>
class Property_cowl
: public implements_ Property_interface
{
   bool extensive; // false is intensive
protected:                                                                       //151119
   contribute_ Real    *amount_ptr;                                              //100930 amount_kg;
   CORN::Units_code    &units_ref;   // units of the amount
public:
   Property_cowl                                                                 //150120
      (bool              extensive_
      ,Real             &amount_
      ,CORN::Units_code &units_)
      : extensive     (extensive_)
      , amount_ptr    (&amount_)                                                 //151119
      , units_ref     (units_)
      {}
      //_2015-01-20__________________________________________________________________/
   inline virtual ~Property_cowl() {}                                            //151204
   inline virtual bool clear()                                     modification_
      { force_amount(0.0); return true; }                                        //160126
   inline virtual Real reset_value_and_units
      (Real amount_
      ,CORN::Units_code units_)                                    modification_
      {  units_ref = units_;
         return set_amount(amount_);
      }
   //___________________________________________________________________________
   virtual bool update_value_with_units                                          //151124_150123
      (float64 _amount, CORN::Units_code _units)                  rectification_
   {  bool updated = true;                                                       //151124
      float64 new_amount_in_stored_units = _amount;
      if (units_ref != _units)
      {  updated = CORN::units_convertor.convert                                 //151124
            (_amount, _units,new_amount_in_stored_units, units_ref);
      } // else no need to convert
      set_amount(new_amount_in_stored_units);
      return updated;                                                            //151124
   }
   //_2015-03-16_______________________________________________________________/
   inline CORN::Units_code get_units()                                     const
      { return units_ref; }
   //___________________________________________________________________________
   virtual float64 get_with_units(CORN::Units_clad &return_units)          const //100930
   {  // Returns the value and the units
      return_units.set(units_ref);
      return (float64)(*amount_ptr);
   }
   //_2010-09-30_______________________________________________________________/
   virtual float64 get_in_units(CORN::Units_code desired_units)            const
   {  // Returns the value converted to the desired units
      float64 amount_in_desired_units = (*amount_ptr);
      if (units_ref != desired_units)
      {  CORN::units_convertor.convert((*amount_ptr), units_ref,amount_in_desired_units, desired_units);
      }
      return amount_in_desired_units;
   }
   //_2010-09-30_______________________________________________________________/
   inline virtual float64 multiply_by(float64 multiplier)          modification_
      {
         assert(extensive);
         return force_amount(get_amount() * multiplier);                         //150125

         //150126 Actually I think ref is working so try restoring

         //150125 ref is not working amount_ref *= multiplier;
         //150125 ref is not working          return amount_ref;  // Probably should return (*this) not float64;
      }
   operator Real const&()                                                  const
      { return (*amount_ptr); } // probably should call get_amount
   virtual bool is_empty()                                          affirmation_
   { return CORN::is_approximately<Real>((*amount_ptr),(Real)0.0,(Real)0.000001); }
   virtual bool is_extensive()                                      affirmation_ { return extensive; }   //150125
   virtual float64 in_prescribed_units()                                   const { return get_amount();} //150122
   virtual float64 update_amount_in_preset_units(float64 new_amount) rectification_ { return set_amount(new_amount); } //150122
   const Real& ref_amount()                                                const { return (*amount_ptr);  }  //160620
   Real& mod_amount()                                                      const { return (*amount_ptr);  }  //160620
   bool reset_amount_pointer(Real *new_amount_ptr)                rectification_ //151120
      { amount_ptr = new_amount_ptr; return true; }
 protected:
    // These are overridden by Physical::Parameter for quality control
   virtual float64 get_amount()                                            const { return (float64)(*amount_ptr); }     //150123
   virtual float64 set_amount(float64 new_amount)                 rectification_ { return force_amount(new_amount); }   //150122
 public: // These are temporary so that I am checking where I had previously used set_amount
   virtual float64 force_amount(float64 new_amount)               rectification_
      { return (float64)((*amount_ptr) = (Real)new_amount); }                    //150122
   float64 increment_by(float64 addend)                                          //150226
      {  assert(extensive);
          force_amount(get_amount() + addend);
          return get_amount();
      }
   float64 decrement_by(float64 subtrehend)                                      //150226
      {  assert(extensive);
         force_amount(get_amount() - subtrehend);
         return get_amount();
      }

/*150226 operator inheritence is proving to be problematic, now only using function
 public:
   inline Property_interface &operator += (float64 new_amount)
      {  assert(extensive);
         force_amount(get_amount() + new_amount);                                //150125
         return *this;
      }
   inline Property_interface &operator -= (float64 new_amount)                   //150215
      {  assert(extensive);
         force_amount(get_amount() - new_amount);
         return *this;
      }
   inline Property_interface &operator *= (float64 multiplier)
      {  multiply_by(multiplier);
         return *this;
      }
   inline Property_interface &operator = (float64 new_amount)
      {  force_amount(new_amount);                                               //150125
         return *this;
      }
      ///< Allows value to be set with =
*/
};
//_2011-08-18___________________________________________________________________
} // namespace physical
#endif
