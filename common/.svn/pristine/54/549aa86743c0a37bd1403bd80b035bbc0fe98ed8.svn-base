#include <common/biomatter/organic_biomatter_balance.h>

//______________________________________________________________________________
Organic_biomatter_balancer::Organic_biomatter_balancer()
: Simulation::Balancer(UC_kg_m2,"biomass"/*,true*/)                              //070219
// pluses
, initial      (0.0)
, added        (0.0)
, recalibration(0.0)
// minuses
, removed      (0.0)
, decomposed   (0.0)
, exhausted    (0.0)
// current
, current      (0.0)
{};
//______________________________________________________________________________
//150123float32 Organic_biomatter_balancer::end_day(std::ostream *balance_file_daily)  // returns the balance which should be 0.0 (approximately)
bool Organic_biomatter_balancer::end_day()
{// pluses
   daily.pluses.set(0,initial);        initial       = 0.0;
   daily.pluses.set(1,added);          added         = 0.0;
   daily.pluses.set(2,recalibration);  recalibration = 0.0;
 // minuses
   daily.minuses.set(0,removed);       removed    = 0.0;
   daily.minuses.set(1,decomposed);    decomposed = 0.0;
   daily.minuses.set(2,exhausted);     exhausted  = 0.0;
   return Simulation::Balancer::end_day(/*150123 balance_file_daily*/);
};
//______________________________________________________________________________
float32 Organic_biomatter_balancer::get_final()
{  return current;
};
//______________________________________________________________________________
bool Organic_biomatter_balancer::get_caption_plus
(nat32 index ,std::string &caption)                                        const
{  bool set = true;
   //                                     0         1        2
   static const char *caption_plus[] = {"initial", "added", "recalibration" };
   if (index <= 2)
      caption.append(caption_plus[index]);
   else set = false;
   return set;
};
//_2009-04-09___________________________________________________________________
bool Organic_biomatter_balancer::get_caption_minus
(nat32 index,std::string &caption)                                         const
{  bool set = true;
   //                                     0          1             2
   static const char *caption_minus[] = {"removed", "decomposed", "exhausted" };
   if (index <= 2)
      caption.append(caption_minus[index]);
   else set = false;
   return set;
};
//_2009-04-09___________________________________________________________________


