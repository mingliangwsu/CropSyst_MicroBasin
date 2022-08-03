#ifndef crop_N_balancerH
#define crop_N_balancerH
#include "common/simulation/balancer.h"
namespace CropSyst {
//______________________________________________________________________________
class Crop_nitrogen_mass_balancer : public Simulation::Balancer
{
 public: // pluses
   float32 initial_seed_or_restart;
   float32 NO3_N_uptake;
   float32 NH4_N_uptake;
   float32 fixation;
   float32 fertilization_requirements;
 public: // minuses
   float32 gaseous_loss;
   float32 removed_canopy;
   float32 removed_root;
// current
   float32 current_canopy_vital;
   float32 current_canopy_effete;
   float32 current_root_vital;
   float32 current_root_effete;
 public:
   Crop_nitrogen_mass_balancer();
   virtual bool end_day();                                                       //150123
   virtual float32 get_final();
 protected: // The following are used to write the balance to a stream
   virtual bool get_caption_plus (nat32 plus_index ,std::string &plus_caption) const; //090409
   virtual bool get_caption_minus(nat32 minus_index,std::string &minus_caption)const; //090409
};
//_2007-02-20________________________________class:Crop_nitrogen_mass_balancer_/
}
#endif

