#include "canopy_growth_continuum.h"
#include "crop/canopy_cover_continuum.cpp"

#include "weather/weather_provider.h"
#include "weather/parameter/WP_air_temperature.h"
#include "weather/parameter/WP_solar_radiation.h"
#include "weather/parameter/WP_vapor_pressure_deficit.h"
#include "UED/library/std_codes.h"
#include "crop/CO2_response.h"
#include "crop/crop_param.h"

#include "crop/canopy_biomass_continuum.cpp"
#include <assert.h>
float64 unassigned_reference=999999.9;

using namespace CropSyst; // eventually this should be in CropSyst namespace
//______________________________________________________________________________
Canopy_growth_continuum::Canopy_growth_continuum
(const Crop_parameters  &_parameters
,const Phenology_interface          &_phenology
,const Transpiration_interface      &_transpiration
,const Weather_provider             &_weather
,const Crop_CO2_response            *_CO2_response_optional
)
: biomass_reference
   (_parameters.biomass_production, _parameters.canopy_growth_cover_based
   ,_parameters.thermal_time
   ,_weather)
, biomass_actual
   (_parameters.biomass_production, _parameters.canopy_growth_cover_based
   ,_parameters.thermal_time
   ,_parameters.is_fruit_tree()
   ,_weather)
, cover_reference
   (_parameters.canopy_growth_cover_based
   ,_parameters.morphology
   ,_parameters.phenology,_phenology
   ,_parameters.is_fruit_tree())
, cover_actual
   (_parameters.canopy_growth_cover_based
   ,_parameters.morphology
   ,_parameters.phenology
   ,_phenology
   ,_parameters.is_fruit_tree()
   ,cover_reference)
, phenology(_phenology)
{  biomass_reference.know
      (&cover_reference
      ,&_transpiration
      ,&_phenology
      ,_CO2_response_optional);
   biomass_actual.know
      (&cover_actual
      ,&_transpiration
      ,&_phenology
      ,_CO2_response_optional);
}
//_2011-08-24____________________________________________________________________
modifiable_ float64 &Canopy_growth_continuum::reference_fract_canopy_cover() modification_
{  return cover_actual.modifiable_ref_solar_rad_intercepted_fraction();
}
//_2011-08-24____________________________________________________________________
bool Canopy_growth_continuum::start_day()                          modification_
{  return cover_reference.start_day()
      &&  cover_actual   .start_day();
}
//_2011-08-24____________________________________________________________________
bool Canopy_growth_continuum::initialize()                         modification_
{  return cover_reference.initialize();
     // &&  cover_actual   .initialize();
}
//_2011-08-24____________________________________________________________________
bool Canopy_growth_continuum::invalidate()                         modification_
{ assert(false); return 0; /*NYI */ }
//_2011-08-24____________________________________________________________________
float64 Canopy_growth_continuum::know_LWP_yesterday(float64 _LWP_yesterday) cognition_
{  LWP_yesterday = _LWP_yesterday;
}
//_2009-09-01___________________________________________________________________
bool Canopy_growth_continuum::update()                                  updates_
{  return
         cover_reference.update_cover(LWP_yesterday)
      && cover_actual   .update_cover(LWP_yesterday);
}
//_2011-08-24____________________________________________________________________
bool Canopy_growth_continuum::process()                            modification_
{  if (phenology.get_days_since_start_of(NGS_RESTART) == 1)                      //110406
   {  biomass_reference.start_season();
      biomass_actual.start_season();
   }
   return update();
}
//_2011-08-24__2008-09-10_______________________________________________________
bool Canopy_growth_continuum::start()                              modification_
{  biomass_reference.start();
   biomass_actual.start();
}
//_2011-08-24__2008-08-11_______________________________________________________
bool Canopy_growth_continuum::restart_with
(float64 restart_biomass,float64 restart_GAI
,bool use_clumping_factor)                                         modification_
{ assert(false); return 0; /*NYI */ }
   // Temporal procession
//_2011-08-24___________________________________________________________________
bool Canopy_growth_continuum::emerge_coyledon
(float64 new_cotalydon_GAI                                                       //080728
,float64 new_cotalydon_BM)                                         modification_
{ assert(false); return 0; /*NYI */ }
//_2011-08-24__2008-07-28_______________________________________________________
bool Canopy_growth_continuum::end_season(bool apply_dormancy)      modification_
{  return (apply_dormancy)
      ?   cover_reference .start_dormancy()
        &&cover_actual    .start_dormancy()
        &&biomass_reference.start_dormancy()
        &&biomass_actual  .start_dormancy()

        // WARNING need to check cover or biomass needs to be called first.

      : true;
}
//_2011-08-24_//080401__________________________________________________________
bool Canopy_growth_continuum::respond_to_clipping()                modification_
{  return cover_reference.respond_to_clipping()
      &&  cover_actual   .respond_to_clipping()
      &&  biomass_reference.respond_to_clipping()
      &&  biomass_actual   .respond_to_clipping();
}
//_2011-08-24___________________________________________________________________
void Canopy_growth_continuum::die_back(float64 fraction_to_die)    modification_
{ assert(false);  /*NYI */ }
//_2011-08-24___________________________________________________________________
void Canopy_growth_continuum::terminate()                          modification_
{ assert(false);  /*NYI */ }
//_2011-08-24__2008-07-28_______________________________________________________
float64 Canopy_growth_continuum::remove_biomass
(float64 biomass_to_remove
,float64 retain_living // GAI or fCCg retain_GAI        // biomass won't be removed if it takes the GAI below this level. Use 0.0 for no limitation
,bool remove_newest_first
,bool reserve_todays_portion
,Crop_biomass &removed_biomass)                                    modification_
{ assert(false); return 0; /*NYI */ }
//_2011-08-24__2007-04-12_______________________________________________________
float64 Canopy_growth_continuum::remove_all_biomass
(Crop_biomass &removed_biomass)                                    modification_
{ assert(false); return 0; /*NYI */ }
   // status query
//_2011-08-24____________________________________________________________________
float64 Canopy_growth_continuum::get_biomass_current(uint8 include_biomass)const
{ assert(false); return 0; /*NYI */ } // The current biomass (Some may have decomposed)
//_2011-08-24____________________________________________________________________
float64 Canopy_growth_continuum::get_influence_on_root_activity_factor(bool after_end_of_vegetative_growth)      const
{ assert(false); return 0; /*NYI */ }
//_2011-08-24__2006-06-01_______________________________________________________
float64 Canopy_growth_continuum::get_fract_canopy_cover()                  const
{ assert(false); return 0; /*NYI */ } // eventually rename to get_fract_canopy_cover_total
//_2011-08-24____________________________________________________________________
void Canopy_growth_continuum::know_residues(Residues_interface *_residues)
{ assert(false);  /*NYI */ }
//______________________________________________________________________________
#ifdef CO2_CHANGE
float64 Canopy_growth_continuum::get_GAI_at_baseline_conc()                const
{ assert(false); return 0; /*NYI */ }
      // get_GAI_at_baseline_conc is used only for calc_water_use_efficiency_CO2_response_adjustment
#endif
//_2011-08-24__2008-07-28_______________________________________________________
float64 Canopy_growth_continuum::get_fract_green_cover()                   const
{ assert(false); return 0; /*NYI */ }  // Appears to be used only for CO2
   // The following will require something equivelent in the canopy based model
//_2011-08-24____________________________________________________________________
float64 Canopy_growth_continuum::calc_fract_cover
(float64 xAI
,bool photosynthetic_active_rad_based
,bool use_clumping_factor                                                        //080801
,bool record_shading_porosity_interception)
                                                                           const
{  return cover_actual.modifiable_ref_solar_rad_intercepted_fraction();
   // Warning we don't have this in this canopy growth model
   // so returning the solar radiation interception;
}
//_2011-08-24__2000-06-23_______________________________________________________
float64 Canopy_growth_continuum::get_senescence_reduction_factor()         const
{ assert(false); return 0; /*NYI */ }
//_2011-08-24__2008-08-07_______________________________________________________
float64 Canopy_growth_continuum::get_adjusted_ET_crop_coefficient()        const
{ assert(false); return 0; /*NYI */ }
//_2011-08-24__2008-08-11_______________________________________________________
float64 Canopy_growth_continuum::calc_plant_development
      (float64 length_max
      ,float64 last_length
      ,float64 overall_growth_stress)                                      const
{ assert(false); return 0; /*NYI */ }
// probably only for output, canopy cover based will probaby not need this
//_2011-08-24__2008-08-05__1999-02-15___________________________________________
float64 Canopy_growth_continuum::get_GAI(uint8 include_GAI)                const
{ assert(false); return 0; /*NYI */ }
//_2011-08-24___________________________________________________________________
float64 Canopy_growth_continuum::get_LAI()                                 const
{ assert(false); return 0; /*NYI */ }
//_2011-08-24__2006-08-24_______________________________________________________
float64 Canopy_growth_continuum::get_LAI(bool from_canopy)                 const
{ assert(false); return 0; /*NYI */ }
   // probably used elsewhere in the model
//_2011-08-24__2008-07-28_______________________________________________________
float64 Canopy_growth_continuum::get_live_green_biomass(bool include_vital,bool include_effete) const
{ assert(false); return 0; /*NYI */ }
   // The following only apply the LAI based mode
//_2011-08-24___________________________________________________________________
bool Canopy_growth_continuum::age_leaf
      (float64  thermal_time_growing_degree_day
      ,float64 water_stress_index)                                  modification_
{ assert(false); return 0; /*NYI */ }
//_2011-08-24__2007-03-28_______________________________________________________
bool Canopy_growth_continuum::develop_leaf
     (bool continue_leaf_growth
     ,float64 canopy_growth
     ,float64 LAI_related_growth  // Today's LAI related growth
     ,float64  thermal_time_growing_degree_day)                     modification_
{ assert(false); return 0; /*NYI */ }
//_2011-08-24__2008-07-28_______________________________________________________
float64 Canopy_growth_continuum::update_LAI_for_self_shading_response(float32 accum_deg_days) modification_
{ assert(false); return 0; /*NYI */ }
//_2011-08-24____________________________________________________________________

