#ifdef DETAILED_BALANCES


#ifndef residue_balancerH
#define residue_balancerH
#include "organic_matter/OM_types.h"
#include "common/biomatter/organic_biomatter_balance.h"
//______________________________________________________________________________
class Residue_balancer
: public Organic_biomatter_balancer
{protected:
   Organic_matter_position position;
 public: // These elements are pluses or minuses depending on the residue type
   float64 incorporated;   // minus for surface,  plus for subsurface
   float64 flattened;      // minus for standing, plus for flat, not applicatable to subsurface
//There is already current in Organic_biomatter_balancer
 public: //
   Residue_balancer(Organic_matter_position _position);
   virtual float32 get_final();
};
//_2009-04-07___________________________________________________________________
class Residue_balancer_surface_stubble_or_attached // also attached
: public Residue_balancer
{
public:
   inline Residue_balancer_surface_stubble_or_attached(Organic_matter_position _position)
      :  Residue_balancer(_position) {}
   virtual bool end_day();                                                       //150123
protected: // The following are used to write the balance to a stream
   //NYN  virtual bool get_caption_plus (nat32 plus_index ,std::string &plus_caption) const;
   virtual bool get_caption_minus(nat32 minus_index,std::string &minus_caption)const; //090409
};
//_2009-04-09___________________________________________________________________
class Residue_balancer_surface_flat
: public Residue_balancer
{
public:
   inline Residue_balancer_surface_flat()
      :  Residue_balancer(OM_flat_surface_position) {}
   virtual bool end_day();  // returns the balance which should be 0.0 (approximately)
protected: // The following are used to write the balance to a stream
   virtual bool get_caption_plus (nat32 plus_index ,std::string &plus_caption) const;
   virtual bool get_caption_minus(nat32 minus_index,std::string &minus_caption)const;
};
//_2009-04-09___________________________________________________________________
class Residue_balancer_subsurface
: public Residue_balancer
{
 public:
   inline Residue_balancer_subsurface()
      :  Residue_balancer(OM_subsurface_position) {}
   virtual bool end_day();  // returns the balance which should be 0.0 (approximately)  070220

 protected: // The following are used to write the balance to a stream
   virtual bool get_caption_plus (nat32 plus_index ,std::string &plus_caption) const; //090409
};
//_2009-04-09___________________________________________________________________
#if (REACCH_VERSION < 2)
#ifdef DETAILED_BALANCES
extern Residue_balancer *residue_mass_balance[OM_POSITION_COUNT];                //090407
#endif
#endif
#endif
#endif
