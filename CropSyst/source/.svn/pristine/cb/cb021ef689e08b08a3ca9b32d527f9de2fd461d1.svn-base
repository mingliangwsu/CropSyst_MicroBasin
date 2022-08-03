#ifndef crop_N_interfaceH
#define crop_N_interfaceH
#ifndef constH
#  include <corn/const.h>
#endif
#include "CS_suite/observation/CS_observation.h"
#include "CS_suite/simulation/CS_simulation_element.h"
namespace CORN { class Enumeration_list; }                                       //130730
#include "crop/crop_types.h"
#include "mgmt_types.h"
class Crop_mass_fate;
namespace CropSyst
{
class  Crop_nitrogen_mass_balancer;
}
namespace CropSyst {
class  Crop_biomass;
//______________________________________________________________________________
class Crop_nitrogen_state_interface
{
 public: // daily values
   virtual float64 get_expected_root_concentration()                       const = 0; // Currently used only to create root residue pools //061215
   virtual float64 get_canopy_concentration(nat8  vital_effete_or_dead)    const = 0; // should have units in name  kgN/kgBM     //070131
   virtual float64 get_root_concentration(nat8  vital_effete_or_dead)      const = 0; // should have units in name  kgN/kgBM     //070131
   virtual float64 get_concentration_min()                                 const = 0; // should have units in name  kgN/kgBM              //070126
   virtual float64 get_concentration_max()                                 const = 0; // should have units in name  kgN/kgBM              //070126
   virtual float64 get_concentration_critical()                            const = 0; // should have units in name  kgN/kgBM              //070126
   virtual float64 get_residue_concentration()                             const = 0; // should have units in name  kgN/kgBM              //061215
   virtual const Crop_mass_fate *get_fate()                                const = 0;                                                     //______
   virtual float64 get_mass_in_plant()                                     const = 0;                                                     //050722
   virtual float64 get_stress()                                            const = 0;
   virtual float32 &ref_stress()                                           const = 0;
   virtual float64 get_stress_index()                                      const = 0;
   virtual float64 get_mass_of_seedling()                                  const = 0;
   virtual float64 get_gaseous_loss()                                      const = 0;
   virtual float64 get_fertilization_requirements()                        const = 0;
   virtual float64 get_fixation()                                          const = 0;
 public:  // I think this is accumulated for the day
   virtual float64 get_mass_removed_seasonal()                             const = 0;
   virtual float64 get_mass_canopy_current()                               const = 0;//131007
   virtual float64 get_mass_canopy_production()                            const = 0;//131007_110915_070206
      // This includes current biomass plus any removed                          //070206
 public:  // stats counters and accumulators
   virtual float64 get_stress_index_mean()                                 const = 0;
};
//_2005-07-22___________________________________________________________________
class Crop_nitrogen_interface
: public Crop_nitrogen_state_interface
, public implements_ CS::Simulation_element                                      //150601
{
 public: // construction/destruction
   virtual ~Crop_nitrogen_interface()                                         {};//070221
 public: // processing
   virtual void restart
      (float64 initial_biomass
      ,float64 restart_GAI                                                       //070320
      ,bool use_clumping_factor
      , bool after_dormancy)                                        modification_= 0;
   virtual bool start_season()                                      modification_= 0;//061214
   virtual void start_dormancy()                                    modification_= 0;//070327
   virtual Crop_mass_fate * apportion_fate                                       //070625
      (const Crop_mass_fate &biomass_fate_now
      ,Crop_mass_fate *N_fate_now                                                //131005
         // should be a reference
      ,const Crop_biomass &canopy_biomass_removed                                //070412_20514_070412
      ,bool plant_part_N_concentrations_specified
      ,nat8 vital_or_effete)                                        modification_= 0;//070327
   virtual float64 process_any_gaseous_losses()                     modification_= 0;//070202
   virtual void know_start_senescence()                            modification_ = 0;//160408
 public: // accessors
   virtual float64 get_limited_growth()                             const = 0; //151105
   virtual bool get_automatic_mode()                                       const = 0;
   virtual void set_automatic_mode(bool enable)                     modification_= 0;
   virtual float64 update_limited_pot_transpiration()               modification_ /*151106 const*/ = 0;
   inline virtual float64 get_limited_pot_transpiration()                  const { return 0.0; }
   virtual float64 get_max_expected_concentration_at_change()              const = 0;//061213
            // Currently always at flowering
   virtual float64 get_max_expected_concentration_at_maturity()            const = 0;//061213
 public: // calculations
   virtual float64 get_season_uptake()                                     const = 0;//070209
   virtual float64 get_daily_uptake()                                      const = 0;//150723LML
   virtual float64 calc_uptake_excess_or_deficit()                         const = 0;//061213
   virtual float64 update_limited_growth /* update_attainable_growth */                                     //151030
      (float64 attainable_growth_transp_or_RUE
      ,float64 root_activity_factor)                               modification_ = 0;
   virtual float64 calc_leaf_stress_factor                                       //070224
      (Nitrogen_leaf_stress_mode calc_mode)                                const = 0;//070224
      // Used to adjust leaf explansion                                          //070224
      // Derived class may return 1.0 if not implemented.                        //070224
 public: // Mass balance tracking and outputs                                     //070220
   virtual bool track_mass_balance                                               //070220
      (CropSyst::Crop_nitrogen_mass_balancer *_mass_balance)        contribution_= 0;//070220
      // Returns true if the class will indeed track the nitrogen mass balance   //070220
 public: // operations                                                           //070412
   virtual float64 remove_canopy_nitrogen_for
      (float64 respective_biomass
      ,nat8 include_vital_or_effete)                                             = 0;
   virtual Crop_mass_fate *render_N_fate(Biomass_fated_cause cause,float64 canopy_before,float64 root_before) rendition_=0;//131005

 public: // Simulation_element implementations
   virtual bool is_valid()                                          affirmation_ { return true; } //150925
   RENDER_INSPECTORS_DECLARATION_PURE;                                           //150917
};
//______________________________________________________________________________
} // namespace CropSyst

#endif

