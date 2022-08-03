#ifndef pondH
#define pondH

//   This is a class for storing ponded water
#include "corn/chronometry/time_types.hpp"
#include "CS_suite/simulation/CS_simulation_element.h"
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#ifndef constH
#  include "corn/const.h"
#endif
#include "common/evaporator.h"
#define UNLIMITED_CAPACITY 999999.9
//______________________________________________________________________________
namespace CropSyst                                                               //130308
{
//______________________________________________________________________________
class Pond
: public extends_ CS::Simulation_element_abstract
, public extends_ CS::Evaporator_intervals                                       //160717_160523
{private:
   Physical::Water_depth depth;                                                  //160408
 public:
   float64  surface_water_storage_capacity; // m                                 //130308
      // This is used/referenced by the water pond object.
      // A constant very large number indicates unlimited surface storage.
      // Optionally there may be a fixed depth,
      // or daily adjustment (due to tillage and subsequent ablation.)
 public:
   Pond
      (const CORN::date32 &today_
      ,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_);        //160717
 public: // Simulation_element implementations
   virtual bool start_day()                                        modification_;//160408
   virtual bool end_day()                                          modification_;//160719
   inline virtual bool is_valid()                                   affirmation_ //160408
      { return depth.get_m() >= 0.0; }
 public: // Pond methods
   const       Physical::Water_depth &ref_depth() const { return depth; }        //160411
   modifiable_ Physical::Water_depth &mod_depth()       { return depth; }        //160411
   inline bool exists() const { return depth.get_m() > 0.0000000001; }           //160408
   virtual float64 evaporate_interval(nat8 interval)               modification_;//160719
   inline float64 get_depth()              const { return depth.get_m(); }       //160408
   float64 relinquish_depth() ;                                                  //071012
   float64 deduct(float64 amount_depth)                            modification_;
   float64 set_depth_with_runoff(float64 new_depth);                             //991110
   float64 set_depth(float64 new_depth)                            modification_;//140606
   virtual float64 calc_evaporation_potential(nat8 interval)        calculation_;//160804
};
//______________________________________________________________________________
} // namespace CropSyst
#endif
//pond.h

