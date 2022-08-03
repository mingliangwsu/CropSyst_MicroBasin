#error check obsolete
#pragma hdrstop

#include "crop/canopy_portion.h>

#include <corn/math/compare.hpp>
//______________________________________________________________________________
/*_______*/ Canopy_portion::Canopy_portion //  Was Daily_history
/*_______*/    (float64 i_age
/*_______*/    ,float64 i_GAI                  // Initially area_index is always green area index
/*_______*/    ,float64 i_biomass
/*980226P*/    ,float64 i_GAI_related_biomass   // This is the GAI related canopy biomass. It is used for development calculation
CO2            ,float64 i_GAI_at_baseline_ppm //  distr renamed to daily_GAI
CO2            ,float64 i_GAI_related_biomass_at_baseline_ppm
/*_______*/    )
/*_______*/ : CORN::Item()
/*_______*/ ,age(i_age)
/*060824_*/ ,days_dead(0)
/*060911_*/ ,GAI(i_GAI)
/*050823_*/ ,dead_AI(0.0)
/*060601_*/ ,biomass_produced(i_biomass)
/*060601_*/ ,biomass_current(i_biomass)
/*_______*/ ,GAI_related_biomass(i_GAI_related_biomass)
CO2         ,GAI_at_baseline_ppm(i_GAI_at_baseline_ppm)
CO2         ,dead_AI_at_baseline_ppm(0.0)
CO2         ,GAI_related_biomass_at_baseline_ppm(i_GAI_related_biomass_at_baseline_ppm)
/*_______*/ {};
//______________________________________________________________________________
/*_______*/ Canopy_portion::Canopy_portion()
/*_______*/ : CORN::Item()
/*_______*/ ,age(0)
/*_______*/ ,GAI(0)
/*061031_*/ ,days_dead(0)
/*050823_*/ ,dead_AI(0.0)
/*060601_*/ ,biomass_produced(0)
/*060601_*/ ,biomass_current(0)
/*_______*/ ,GAI_related_biomass(0)
CO2         ,GAI_at_baseline_ppm(0)
CO2         ,dead_AI_at_baseline_ppm(0.0)
CO2         ,GAI_related_biomass_at_baseline_ppm(0)
/*_______*/ {};
//__________This constructor is used for accumulators___________________________
#ifdef CHECK_OBSOLETE
080806
/*070806_*/ void Canopy_portion::mark_as_deleted()
/*_______*/ {  age=(0);
/*_______*/    GAI=(0);
/*061031_*/    days_dead=(0);
/*050823_*/    dead_AI=(0.0);
/*060601_*/    biomass_produced=(0);
/*060601_*/    biomass_current=(0);
/*_______*/    GAI_related_biomass=(0);
CO2            GAI_at_baseline_ppm=(0);
CO2            dead_AI_at_baseline_ppm=(0.0);
CO2            GAI_related_biomass_at_baseline_ppm=(0);
/*_______*/ };
#endif
//______________________________________________________________________________
/*_______*/ int Canopy_portion::compare(const CORN::Item &other) const
/*_______*/ {  float64 other_age = ((const Canopy_portion &)(other)).age;
/*_______*/       return CORN::is_approximately<float64>(age,other_age,0.0000001) ? 0 : (age  < other_age) ? -1 : 1;
/*_______*/ };
//______________________________________________________________________________
/*_______*/ bool Canopy_portion::is_valid() const
/*060530_*/ { return (!(CORN::is_approximately<float64>(get_GAI()                ,0.0,0.00000001) &&
/*_______*/             CORN::is_approximately<float64>(biomass_produced   ,0.0,0.00000001) &&
/*060601_*/          //   Not sure if I need to look at biomass_current. Probably not because I think this was a check when adding new pool
/*_______*/             CORN::is_approximately<float64>(GAI_related_biomass,0.0,0.00000001))); };
//______________________________________________________________________________
/*050823_*/ bool Canopy_portion::age_by(float64 daily_age_deg_day,float64 leaf_duration_deg_day_f32)
/*_______*/ {  age += daily_age_deg_day;
/*060316_*/    bool senesce_now = (age > leaf_duration_deg_day_f32) && !is_dead();
/*_______*/    if (senesce_now) die();
/*060316_*/    return senesce_now;;
/*_______*/ };
//______________________________________________________________________________
/*060911_*/ CORN::Days Canopy_portion::inc_days_dead()                    modification_
/*_______*/ {  days_dead += 1;
/*_______*/    return days_dead;
/*_______*/ };
//______________________________________________________________________________
/*050823_*/ float64 Canopy_portion::die()    // replaces clear_GAI()
/*051105_*/ {  float64 GAI_reduced = GAI;
/*_______*/    dead_AI = GAI;
/*_______*/    GAI= 0.0;
CO2            dead_AI_at_baseline_ppm = GAI_at_baseline_ppm;
CO2            GAI_at_baseline_ppm = 0.0;
/*051105_*/    return GAI_reduced;
/*_______*/ };
//______________________________________________________________________________
/*_______*/ void Canopy_portion::increment_by(const Canopy_portion &addend)
/*_______*/ {  //Don't add age this method is used to get the current totals, the age has no meaning in this context.
/*970305p*/    GAI += addend.GAI;                  //  Area Index
/*970305p*/    dead_AI  += addend.dead_AI;                  //  Area Index
/*060601_*/    biomass_produced  += addend.biomass_produced;       // kg/m2 The biomass produced for the day.
/*060601_*/    biomass_current  += addend.biomass_current;       // kg/m2 The biomass produced for the day.
/*980226P*/    GAI_related_biomass  += addend.GAI_related_biomass;    // kg/m2 GAI related canopy biomass.  It is used for GAI/biomass development calculation.
CO2            GAI_at_baseline_ppm  += addend.GAI_at_baseline_ppm;   //  distr renamed to daily_GAI  (remove _X after we fixup the new biomass.}
CO2            dead_AI_at_baseline_ppm  += addend.dead_AI_at_baseline_ppm;   //  distr renamed to daily_GAI  (remove _X after we fixup the new biomass.}
CO2            GAI_related_biomass_at_baseline_ppm  += addend.GAI_related_biomass_at_baseline_ppm;
/*_______*/ };
//______________________________________________________________________________
/*060530_*/ float64 Canopy_portion::dec_green_area_index(float64 subtrahend_area_index)
/*_______*/ {  GAI -= subtrahend_area_index;
/*_______*/    return GAI;
/*_______*/ };
//______________________________________________________________________________
/*060530_*/ float64 Canopy_portion::inc_green_area_index(float64 addend_area_index)
/*_______*/ {  GAI += addend_area_index;
/*_______*/    return GAI;
/*_______*/ };
//______________________________________________________________________________
/*060911_*/ float64 /*100517 void*/ Canopy_portion::dec_biomass_current(float64 subtrahend_biomass)
/*_______*/ {
/*100517_*/    float64 act_subtrahend_biomass =
/*100517_*/       (biomass_current > subtrahend_biomass)
/*100517_*/       ? subtrahend_biomass
/*100517_*/       : biomass_current;
/*100517_*/    biomass_current -= act_subtrahend_biomass;
/*100517_*/    return act_subtrahend_biomass;
//100517 biomass_current -= subtrahend_biomass;
/*_______*/ };
//______________________________________________________________________________
/*080515_*/ void Canopy_portion::clear_GAI_related_biomass()           modification_
/*_______*/ {
/*_______*/    GAI_related_biomass = 0.0;                 // kg/m2 GAI related canopy biomass.  It is used for GAI/biomass development calculation.  // was  GAI_related_canopy_biomass
CO2            GAI_at_baseline_ppm = 0.0;                 // distr renamed to daily_GAI  (remove _X after we fixup the new biomass.}
CO2            GAI_related_biomass_at_baseline_ppm = 0.0; // was GAI_related_canopy_biomass_at_baseline_ppm
/*_______*/ };
//______________________________________________________________________________
/*060824_*/ float64  Canopy_portion::slough()
/*_______*/ {  // This invalidates the canopy portion the biomass amount is relinquished to the caller.
/*060824_*/    // Returns the biomass sloughed
/*_______*/    float64 sloughed_biomass = biomass_current;
/*_______*/    biomass_current = 0;    biomass_produced = 0;     GAI_related_biomass = 0;
/*_______*/    dead_AI = 0;
/*_______*/    GAI= 0;
/*_______*/    age = 0;   days_dead = 0;
/*_______*/    return sloughed_biomass;
/*_______*/ };
//______________________________________________________________________________
/*060825_*/ bool  Canopy_portion::dormancy()
/*_______*/ {  GAI_related_biomass = 0;
CO2            GAI_related_biomass_at_baseline_ppm = 0;
/*_______*/    return true;
/*_______*/ };
//______________________________________________________________________________
#define DUMP_PORTIONS
#ifdef DUMP_PORTIONS
/*_980511*/ void  Canopy_portion::write(STD_NS ostream &strm)       performs_IO_
{
   strm
      << '\t'<< age
      << '\t'<< days_dead
      << '\t'<< GAI
      << '\t'<< dead_AI
      << '\t'<< biomass_produced
      << '\t'<<  biomass_current
      << '\t'<< GAI_related_biomass
      << std::endl;
};
#endif

