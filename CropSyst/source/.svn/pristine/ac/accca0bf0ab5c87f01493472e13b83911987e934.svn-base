#ifndef soil_interfaceH
#define soil_interfaceH

/* 031111
This class provides an interface for working with soil objects
for various crop models (CropSyst)

This class presumes a layering system has been established for the
soil profile as implemented in the derived class.

For example in CropSyst there are data available both for both
a soil horizon profile and a profile system subdividing the
soil horizons, CropSyst uses the soil sublayers.

*/

#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "corn/const.h"
#include "soil/layering.h"
#include "corn/chronometry/time_types.hpp"
#include "soil/layers_interface.h"

#if ((CS_VERSION >= 5) || (REACCH_VERSION >= 2) || defined(OFOOT_VERSION))
#  include "CS_suite/simulation/CS_simulation_element.h"
#endif

#include "CS_suite/observation/CS_observation.h"

namespace CORN
{
   class Enumeration_list;
}
using namespace CORN;

#define ENTIRE_PROFILE_DEPTH 0.0
//______________________________________________________________________________
class Soil_salt_interface;
class Soil_nitrogen_interface;
class Soil_texture_interface;
class Soil_hydraulic_properties_interface;
class Soil_hydrology_interface;
class Soil_temperature_profile_hourly_interface;
class Soil_temperature_interface;                                                //141212
class Soil_structure_interface;
class Soil_erosion_RUSLE;
class Evaporator_soil;                                                           //160606
//______________________________________________________________________________
class Soil_properties_sublayers_interface
{
public:
   virtual unmodifiable_ Soil_layers_interface *ref_layers()            const=0; //160412
   virtual   modifiable_ Soil_layers_interface *mod_layers()    modification_=0; //160412
      // Returns the soil layering system.
      // This is required in derived classes.
      // It should never return 0.
   virtual unmodifiable_ Soil_texture_interface *ref_texture()          const=0; //160412
   virtual   modifiable_ Soil_texture_interface *mod_texture()  modification_=0; //160412
      // Returns the soil texture parameters object.
      // 160412 was get_texture_modifiable
   virtual unmodifiable_ Soil_hydraulic_properties_interface *
      ref_hydraulic_properties()                                        const=0; //160412
      // Returns the soil properties that are commonly derived from soil survey data
      // and/or pedo transfer functions.
   virtual   modifiable_ Soil_hydraulic_properties_interface *
      mod_hydraulic_properties()                                modification_=0; //160412
      // Returns the soil properties that are commonly derived from soil survey data
      // and/or pedo transfer functions.
};
//_2010-11-04___________________________________________________________________
class Soil_interface
: public virtual Soil_properties_sublayers_interface                             //101104
#if (CROPSYST_VERSION == 5)
, public implements_ CS::Simulation_element                                      //150724
#endif
{
public:  // Status
   inline virtual float64 get_albedo()                                     const
      { return 0.1; }
      // Returns the current albedo of the soil surface.
      // You may return a designated constant or a user specified soil parameter.
      // Often this value is adjusted for soil moisture
      // This default value is for a slightly wet typical soil.
   inline virtual float64 get_SLPF()                                       const
      { return 1.0; }
      // This is used by the CropGro submodel.
      // If never using the CropGro model, simply return 1.0.
      // SLPF is both a soil and a crop specific parameter.
      // It reflects the combined effects on crop growth of various soil-related
      // parameters which are not modeled directly, such as aluminum toxicity or nematode damage.
      // This sounds like an adjustment parameter that should go in simulation control
public:
   inline virtual bool take_erosion_submodel(Soil_erosion_RUSLE *_erosion_submodel)    //130328_111108
      { return false; }
   virtual unmodifiable_ Soil_structure_interface *ref_structure()      const=0;
      //160412 was get_structure_unmodifiable
   virtual   modifiable_ Soil_structure_interface *mod_structure() modification_=0;
      // Returns the soil structure (bulk density)
      //160412 was get_structure_modifiable
   virtual unmodifiable_ Soil_hydrology_interface *ref_hydrology()      const=0; //160412
      // Returns the current soil hydrology state and process object.
      // Generally this is required in derived classes.
      // Generally derived classes will return the object.
      // 160412 was get_hydrology_constant
   virtual   modifiable_ Soil_hydrology_interface *mod_hydrology() modification_=0;
      // Returns the current soil hydrology state and process object.
      // Generally this is required in derived classes.
      // Generally derived classes will return the object.
      // 160412 was get_hydrology_modifiable
   inline virtual unmodifiable_ Soil_hydrology_interface *ref_hydrology_at(nat16 seconds) const
      { return 0; }
      // Returns the soil hydrology state at the specified number of seconds into the day.
      // For example, if the hydrology model is running at an hourly time step.
      // passing second 0 to 3600 will return the hydrology of the first hour.
      // If the model is running at a daily time step any value 0 to 86399 will return
      // the daily hydrology.
   virtual const       Evaporator_soil *ref_evaporator()                const=0; //160606
   virtual modifiable_ Evaporator_soil *mod_evaporator()        modification_=0; //160606
   virtual bool submit_evaporator(Evaporator_soil *evaporator_)   submission_=0; //160606
   inline virtual modifiable_ Soil_nitrogen_interface *mod_nitrogen() modification_  //160412
      { return 0; }
      // This returns the soil nitrogen object that can be modified.
      // This is not required in derived classes.
      // Derived classes may return 0 indicating there is no nitrogen submodel
      // or the nitrogen simulation is not enabled.
      // 160412 was get_nitrogen_modifiable
   inline virtual unmodifiable_ Soil_nitrogen_interface  *ref_nitrogen()   const //160412
      { return 0; }
      // This returns the soil nitrogen object not intended for modification.
      // This is not required in derived classes.
      // Derived classes may return 0 indicating there is no nitrogen submodel
      // or the nitrogen simulation is not enabled.
      // 160412 was get_nitrogen_constant
   inline virtual unmodifiable_ Soil_temperature_profile_hourly_interface *provide_temperature_profile_hourly() provision_  //150424 161104LML added the first unmodifiable
      { return 0; }
      // Returns the hourly soil temperature profile object.
      // May return 0 if this soil does not provide a hourly soil temperature profile
      // or if hourly simulation not enabled.

   inline virtual unmodifiable_ Soil_temperature_profile_hourly_interface *ref_temperature_profile_hourly() const
      { return provide_temperature_profile_hourly(); }                           //150424
      // Returns the hourly soil temperature profile object.
      // May return 0 if this soil does not provide a hourly soil temperature profile
      // or if hourly simulation not enabled.

   inline virtual unmodifiable_ Soil_temperature_interface *ref_temperature_profile() const//141212
      { return 0; }
   inline virtual unmodifiable_ Soil_salt_interface *ref_salinity()        const //160412
      // not const because caller can do anything with the salinity
      { return 0; }
      // Returns the soil salinity object.
      // May return 0 if this soil does not provide a soil salinity submodel
      // or salinity simulation is not enabled.
      // 160412 was get_salinity_constant
   inline virtual   modifiable_ Soil_salt_interface *mod_salinity() modification_//160412
      { return 0; }
      // Returns the soil salinity object.
      // May return 0 if this soil does not provide a soil salinity submodel
      // or salinity simulation is not enabled.
      // 160412 was get_salinity_modifiable
   inline virtual   modifiable_ bool set_salinity
      (Soil_salt_interface *salinity,bool keep_it = true)          modification_
      { return 0; }
      // Returns true if salinity was successfully set up.
      // returns false if could not be set
      // Pass 0 to clear the salinity submodel.
      // If keep_it is true then ownership of the salinity object
      // is passed to the soil object and it will be responsible for deleting it.
      // Note: if you relinquish ownership, then it is possible that
      // the salinity object is deleted at any time by the soil object;
      // so from this point on always use get_salinity().

      // Derived soil class may provide the salinity model by default
      // In this case override set_salinity to simply return false;

   inline virtual float64 get_pH(nat8  layer)              const { return 7.0; } //150415
public: // Soil profile state accessors  (May eventually move to a Soil_temperature_interface
   virtual float64 get_temperature_C                   (nat8 layer)     const=0;
public: // Soil plant parameters  // Not sure where to put this.
   inline virtual float64 get_root_hospitality_factor(nat8 layer) const {return 1.0;}
      // This is used by the CropGro submodel.
      // If never using the CropGro model, simply return 1.0.
public:
   virtual float64  get_act_water_entering_soil()                       const=0;
   virtual modifiable_ float64 &mod_act_water_entering_soil()   modification_=0; //160412_150930
public:
   #if (CROPSYST_VERSION == 5)
   // This can actually be all versions
   #else
   virtual bool start_day()                                     modification_=0;
         // should return bool;
   virtual bool end_day()                            modification_{return true;} //130911
   virtual bool process_day()                                   modification_=0; //150611
   #endif
   virtual Seconds   get_hydrology_timestep_resolution_today()          const=0;
      // Returns the number of seconds in the hydrology timestep
      // Usually this is the timestep of the infiltration model that was used today.
      // The timestep may be variable.
      // I.e. in CropSyst the finite difference could run at daily, hourly or half hour
      // interval on any given day as deemed necessary to handle the water flux.
      // There should be a corresponding soil profile hydrology record for each
      // timestep retrieved with get_hydrology_at().
   virtual bool reinitialize_for_crop(float64 wilt_leaf_water_pot)  modification_{ return true;}
      // 140926, I am not sure if reinitialize_for_crop is still needed, check with Claudio
      // If it is then probably would be start_season()

public: // The following are functions (valid for interfaces)
   virtual float64 get_mass_kg_m2(nat8 layer)                             const;
   virtual float64 distribute_amount
      (const soil_horizon_array32(from_horizon_amount)
      ,soil_sublayer_array_64(to_layer_amount))                         const=0; //150424
   RENDER_INSPECTORS_DECLARATION_PURE;                                           //150929
};
//______________________________________________________________________________
#endif

