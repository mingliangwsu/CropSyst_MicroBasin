#include "corn/math/compare.hpp"
#include "pond.h"
//______________________________________________________________________________
namespace CropSyst                                                               //130308
{
// This is just a placed holder until the surface water storage capacity is known
//______________________________________________________________________________
Pond::Pond
(const CORN::date32 &today_
,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_)               //160717
: CS::Simulation_element_abstract(today_)                                        //160717
, CS::Evaporator_intervals       (evaporation_potential_)
, depth                          ()
, surface_water_storage_capacity (UNLIMITED_CAPACITY)                            //130308
{}
//_2016-04-08__2013-03-08_________________________________________constructor__/
float64 Pond::calc_evaporation_potential(nat8 interval)             calculation_
{  return std::min<float64>
      (evaporation_potential_remaining.get(interval)                             //160717
      ,depth.get_m());
}
//_2016-06-03__________________________________________________________________/
bool Pond::start_day()                                             modification_
{  bool started = true;
   started &= CS::Evaporator_intervals::start_day();
   started &= CS::Simulation_element_abstract::start_day();
   return started;
}
//_2016-04-08_______________________________________________________start_day__/
bool Pond::end_day()                                             modification_
{  bool ended = true;
   ended &= CS::Evaporator_intervals::end_day();
   ended &= CS::Simulation_element_abstract::end_day();
   return ended;
}
//_2016-04-08_______________________________________________________start_day__/
//_2016-04-08__2014-06-06_______________________________________________________
float64 Pond::evaporate_interval(nat8 interval)                    modification_
{
   float64 evap_pot = calc_evaporation_potential(interval);                      //160804
   float64 evap_act = 0.0;
   if (evap_pot <= depth.get_m() )
   {  // some of the pond will be evaporated
      depth.dec_m(evap_pot);
   } else
   {  depth.clear();
   }
   if (evap_pot > 0)
   {  evap_act = evap_pot;
      evaporation_potential.set(interval,evap_pot);
      evaporation_potential_remaining.deduct_at(interval,evap_pot);
   }
   evaporation_actual.set(interval,evap_act);
   return evap_act;
}
//_2016-07-19___________________________________________________________________
 float64 Pond::deduct(float64 amount_depth)
{  float64 act_deduction = amount_depth;
   if (act_deduction > depth.get_m())
      act_deduction = depth.get_m();
   depth.dec_m(act_deduction);
   return act_deduction;
}
//______________________________________________________________________________
float64 Pond::set_depth_with_runoff(float64 new_depth)
{  float64 depth_ = CORN::must_be_between<float64>
      (new_depth,0.0,surface_water_storage_capacity);                            //130308
   depth.set_m(depth_);
   float64 runoff = CORN::must_be_greater_or_equal_to<float64>(new_depth - depth_,0.0);
   return runoff;
}
//_1999-11-10___________________________________________________________________
float64 Pond::set_depth(float64 new_depth)                         modification_
{  return depth.set_m(new_depth);
}
//_2014-06-06___________________________________________________________________
float64 Pond::relinquish_depth()
{  float64 result = depth.get_m();
   depth.clear();
   return result;
}
//_2007-10-12___________________________________________________________________
} // namespace CropSyst

