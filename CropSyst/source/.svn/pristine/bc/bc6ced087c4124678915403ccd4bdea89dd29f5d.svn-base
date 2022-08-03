#include "crop/crop_N_balancer.h"
namespace CropSyst {
//______________________________________________________________________________
Crop_nitrogen_mass_balancer::Crop_nitrogen_mass_balancer()
: Simulation::Balancer(UC_kg_m2,"nitrogen"/*,true*/)
// pluses                        minuses
,initial_seed_or_restart   (0)   ,gaseous_loss     (0)
,NO3_N_uptake              (0)   ,removed_canopy   (0)
,NH4_N_uptake              (0)   ,removed_root     (0)
,fixation                  (0)   ,current_canopy_vital   (0)  ,current_canopy_effete   (0)
,fertilization_requirements(0)   ,current_root_vital     (0)  ,current_root_effete     (0)
{}
//_2007-02-20___________________________________________________________________
bool Crop_nitrogen_mass_balancer::end_day()
{
// pluses
   daily.pluses.set(0,initial_seed_or_restart   ); initial_seed_or_restart   =0;
   daily.pluses.set(1,NO3_N_uptake+NH4_N_uptake ); NO3_N_uptake              =0;  NH4_N_uptake =0;
   daily.pluses.set(2,fixation                  ); fixation                  =0;
   daily.pluses.set(3,fertilization_requirements); fertilization_requirements=0;
   //    daily.pluses.set(4,instantaneous_root_restoration_after_dormancy);
// minuses
   daily.minuses.set(0,gaseous_loss);              gaseous_loss              =0;
   daily.minuses.set(1,removed_canopy);            removed_canopy            =0;
   daily.minuses.set(2,removed_root);              removed_root              =0;
   return Simulation::Balancer::end_day
      ();
}
//_2007-02-20___________________________________________________________________
float32 Crop_nitrogen_mass_balancer::get_final()
{  return current_canopy_vital + current_canopy_effete + current_root_vital + current_root_effete;
}
//_2007-02-20___________________________________________________________________
bool Crop_nitrogen_mass_balancer::get_caption_plus
(uint32 index ,std::string &caption)                                const
{  bool set = true;
   //                                     0          1         2           3
   static const char *caption_plus[] = {"initial", "uptake", "fixation", "fertilization requirements" };
   if (index <= 3)
      caption.assign(caption_plus[index]);
   else set = false;
   return set;
}
//_2009-04-09___________________________________________________________________
bool Crop_nitrogen_mass_balancer::get_caption_minus
(uint32 index,std::string &caption)                                 const
{  bool set = true;
   //                                     0               1                 2
   static const char *caption_minus[] = {"gaseous loss", "removed canopy", "removed root" };
   if (index <= 2)
      caption.assign(caption_minus[index]);
   else set = false;
   return set;
}
//_2009-04-09___________________________________________________________________
}

