#ifndef crop_emergenceH
#define crop_emergenceH
#include "corn/math/statistical/stats.h"
#include "corn/math/statistical/distribution_normal.h"
#ifdef _Windows
#  include <fstream>
#endif
#include "crop/crop_param_struct.h"

class Seeding_parameters;
class Soil_interface;
#if (CROPSYST_VERSION >= 5)
namespace CropSyst {
#endif
//______________________________________________________________________________
class Crop_emergence_abstract
{
public:
};
//______________________________________________________________________________
#ifdef NYI
class Crop_emergence_thermal_time
: public Crop_emergence_abstract
{  // original thermal time emergence model
};
#endif
//______________________________________________________________________________
class Crop_emergence_hydrothermal_time
: public Crop_emergence_abstract
{
private: // parameters
   CropSyst::Crop_parameters_struct::Emergence_hydro_thermal &parameters;               // 100325 Emergence_parameters
   Seeding_parameters   *seeding_parameters;
   bool                  owns_seeding_parameters; // will be true if using defaults
   float32               specific_leaf_area_m2_kg; // currently the same as the crop parameter (perhaps there may be a different one for cotyledons)
   float32               anticipated_pot_emergence_seeds_m2; // The
private: // state
   int  days_after_sowing;
   bool first_day;
   bool emerged;
   bool at_anticipated_pot_emergence;
   int p_i_pending;
   float32 cotyledon_GAI;
   float32 cotyledon_biomass;
private:
   CORN::Statistical_running_tally  TE[11]; // index 0 not used  // one for each p
   int  poor_conditions_delay[11];  // Number of days each p has its own history
   CORN::Distribution_normal        normal_distr;
   float32                    emerged_seeds_m2;  // #seeds/m2

#ifdef _Windows
   mutable std::ofstream *detail_txt_file;
#endif

public: // constructor
   Crop_emergence_hydrothermal_time
      (CropSyst::Crop_parameters_struct::Emergence_hydro_thermal/*110218 Emergence_hydro_thermal_parameters*/  &_parameters
      ,float32               _specific_leaf_area_m2_kg
      ,Seeding_parameters   *_seeding_parameters = 0); // may be zero if using defaults

   virtual ~Crop_emergence_hydrothermal_time();
public: // processing
   virtual  void     process( Soil_interface &soil);
public: // accessors
   virtual  float64  get_cotyledon_GAI()                                   const;
   virtual  float64  get_cotyledon_biomass()                               const;
   virtual  bool     is_first_day()                                        const;
      ///< \return true if this was the first day of emergence.
   virtual  bool     has_emerged()                                         const;
   virtual  bool     is_complete()                                         const;
      ///< \return true if all the seeds expected to emerged have germinated and emerged.
public: // supplimentary output
#ifdef _Windows
   inline void know_detail_txt_file(std::ofstream *_detail_txt_file)         mutates_ { detail_txt_file = _detail_txt_file; }
#endif
};
//______________________________________________________________________________
#if (CROPSYST_VERSION >= 5)
} // namespace CropSyst
#endif

#endif

