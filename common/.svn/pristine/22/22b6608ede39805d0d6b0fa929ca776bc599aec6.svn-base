#ifndef organic_biomatter_balanceH
#define organic_biomatter_balanceH
#include <common/simulation/balancer.h>
//______________________________________________________________________________
class Organic_biomatter_balancer
 : public Simulation::Balancer
{
public:  // pluses
   float64 initial;
   float64 added;    // was 64bit not sure why
   float64 recalibration;
public:  // minuses
   float64 removed;              // I.e. from surface residue removal
   float64 decomposed;
   float64 exhausted;
public:  // current
   float64 current;
public:  //
   Organic_biomatter_balancer();
   virtual bool end_day();                                                       //150123
      // returns the balance which should be 0.0 (approximately)
   //150123 virtual float32 end_day(std::ostream *balance_file_daily);  // returns the balance which should be 0.0 (approximately)
   virtual float32 get_final();
protected: // The following are used to write the balance to a stream
   virtual bool get_caption_plus (nat32 plus_index ,std::string &plus_caption) const;
   virtual bool get_caption_minus(nat32 minus_index,std::string &minus_caption)const;
};
//_2009-04-07___________________________________________________________________
#endif

