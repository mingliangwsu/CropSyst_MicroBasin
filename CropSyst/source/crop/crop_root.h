#ifndef crop_rootH
#define crop_rootH
#include "corn/primitive.h"
#include "common/soil/layering.h"
#include "corn/const.h"
#include "crop/crop_param_struct.h"
#include "corn/dynamic_array/dynamic_array_T.h"
class Soil_layers_interface;
class Crop_CropSyst;
class Crop_CropSyst_orchard_fruit;
class Crop_interfaced_CropSyst;

#include "CS_suite/observation/CS_observation.h"
namespace CropSyst {
interface_ Thermal_time_immutable;                                               //151106

//______________________________________________________________________________
class Crop_root_interface
{
 public: // constructor
   inline Crop_root_interface()                                               {}
   inline virtual ~Crop_root_interface()                                      {} //170217
 public: // actions
   virtual bool start_day()                                                 = 0; //061212
   virtual void update(bool terminate_pending)                              = 0;
      // usually called daily
   virtual void initialize(float64 root_length_to_initialize_to)            = 0; //070314
      // Call once when crop is planted and at restart
   virtual void kill()                                                      = 0;         // Call when the crop is killed
 public: // accessors
   virtual float64 get_biomass()                                      const = 0; //070130
   virtual float64 get_growth_biomass()                               const = 0; //070130
   virtual float64 get_apparent_root_depth()                          const = 0; //061208
   virtual float64 get_root_length()                                  const = 0; //070131
   virtual const float64 *get_total_fract_root_length_m()             const = 0; //070131
   virtual float64 calc_root_biomass                                             //060612
      (float64 *output_root_biomass_by_layer=0)                       const = 0;
   virtual float64 update_root_depth(bool terminate_pending)   modification_= 0; //981023
      // returns the apparent root depth
   virtual float64 know_above_ground_biomass(float64 _above_ground_biomass_kg_m2)  cognition_ //130625
      { return _above_ground_biomass_kg_m2;  }
      //know_above_ground_biomass is currently needed only by Crop_root_vital_V5
      // For the default we don't do anything.
    RENDER_INSPECTORS_DECLARATION_PURE;                                          //150916
};
//_2007-01-31___________________________________________________________________
class Crop_root_common
: public CropSyst::Crop_root_interface                                           //070131
{
 public:                                                                         //131008
   float64  root_length;         // meter  This is the central axis root length from the top of the root to the tip as if the roots were unobstructed by shallow soil depth.
   float64  biomass;             // kg/m2 current biomass;                       //070130
 public:
   Crop_root_common();
   inline virtual float64 get_biomass()            const { return biomass;     } //070130
   inline virtual float64 get_root_length()        const { return root_length; } //070131
   RENDER_INSPECTORS_DECLARATION;                                                //150916
};
//_2013-09-10___________________________________________________________________
class Crop_root_vital
: public extends_ Crop_root_common
{
   friend class Crop_CropSyst;
   friend class Crop_CropSyst_orchard_fruit;
   friend class Crop_interfaced_CropSyst;
 protected:
   const Thermal_time_immutable &thermal_time;                                   //151106
   const Soil_layers_interface &soil_layers;
 protected: // parameters (from parameter file)
   const Crop_parameters_struct::Root      &parameters;              //061212
   const Crop_parameters_struct::Phenology &phenology_parameters;    //080722
 public: // Root length/depth
   float64  apparent_root_depth;  // meter  This is the root depth limited to the soil profile depth (was recorded_root_depth)
 protected:
   float64  growth_biomass;      // kg/m2 today's biomass production             //070130
private: // root length development working variables
   float64  normalized_thermal_time_today;                                       //061212
   float64  normalized_thermal_time_yesterday;                                   //061212
   float64  root_length_unstressed_today;       // meter
   float64  root_length_unstressed_yesterday;   // meter                         //061212
   float64  biomass_yesterday;                                                   //070410
protected: // Set once at the start of the Crop
   nat8           rooting_layer ;   // soil layer number. The layer the roots start in (currently always layer 2 (below the evaporative layer)) //990104
   float64        start_rooting_depth;                                           //981007
   float64  max_root_density;
      //120817 depth of top of roots
public: // state
   mutable soil_layer_array64(root_lengths);   // (I think m  but sometimes km) This is the length of all root pieces in each layer.  (used by new pot N uptake calculation)  //061129
   float64    total_root_lengths;            // sum of root lengths
   soil_layer_array64(root_density);        // Not sure units may be  cm/cm3???
   soil_layer_array64(total_fract_root_length);                                  //010322
   soil_layer_array64(root_distribution_unadjust); float64 root_distr_unadjust_sum; //180727
   //180727 CORN::Dynamic_array<float64> root_distribution_unadjust; // was L             //180726
   /*
   soil_layer_array64(L);                                                        //180726
   float64 L_sum;                                                                //180726
   */
public:
   Crop_root_vital
      (const Crop_parameters_struct::Root      &parameter                        //061212
      ,const Crop_parameters_struct::Phenology &phenology_parameters             //080722
      ,const Thermal_time_immutable            &thermal_time                     //151106
      ,const Soil_layers_interface &soil_layers
      ,float32                      initial_root_length);
      // initial_root_length is used by  calc_max_N_update_per_unit_root_length()

      // This requires a soil layering system.  If the crop model does not have soil available, it could provide a dummy soil
 public:
   virtual void update(bool terminate_pending);       // usually called daily
   virtual bool start_day();                                                     //061212
   virtual void initialize(float64 root_length_to_initialize_to);   // Call once when crop is planted
   virtual void kill();         // Call when the crop is killed
   virtual float64 update_root_length(float64 stress_factor);                    //061212
     // Currently only the water stress factor!
   virtual float64 calc_root_biomass
      (float64 *output_root_biomass_by_layer=0)                       const = 0; //060612
 public: // accessors  (must be called after update())
   inline float64 get_total_root_lengths()                                 const { return total_root_lengths; }
   inline virtual float64 get_apparent_root_depth()                        const { return apparent_root_depth; }       //061208
   inline virtual float64 get_lengths(nat8  layer)                         const { return root_lengths[layer]; }        //070131
   inline virtual float64 get_growth_biomass()                             const { return growth_biomass; }            //070130
   inline virtual const float64 *get_total_fract_root_length_m()           const { return total_fract_root_length;}   //070131
 private:                                                                                                    //061208
   virtual float64 update_root_fractions()                        modification_; //050720
   virtual float64 update_root_densities()                        modification_; //981023
   virtual float64 update_root_depth(bool terminate_pending)      modification_; //981023
      // returns the apparent root depth
   virtual float64 update_root_lengths()                          modification_; //061208
   RENDER_INSPECTORS_DECLARATION;                                                //150916
};
//_2006-12-08___________________________________________________________________
class Crop_root_dormant
: public extends_ Crop_root_common
{
   soil_layer_array64(biomass_by_layer);  // root biomass
 public: // constructor
   Crop_root_dormant(float64 _dormant_root_length,float64 _biomass,soil_layer_array64(_biomass_by_layer));
 public: // operations
   inline virtual void update(bool terminate_pending)                        { }
      // usually called daily // currently not applicable
   inline virtual bool start_day()                              { return true; } //061212
      // currently not applicable
   inline virtual void initialize(float64 root_length_to_initialize_to)      { }
      // Call once when crop is planted  // currently not applicable
   inline virtual void kill()                                                { }
      // Call when the crop is killed // currently not applicable
 public: // accessors
   inline virtual float64 get_biomass_in_layer(nat8 layer)                 const //070130
      { return biomass_by_layer[layer]; }
   inline virtual float64 get_growth_biomass()                             const //070130
      { return 0.0; } // Dormant roots don't grow
   inline virtual float64 get_apparent_root_depth() const { return root_length;} //061208
   inline virtual const float64 *get_total_fract_root_length_m()           const //070131
      { return 0;}; // Not applicable for dormant roots

   inline virtual float64 update_root_depth(bool terminate_pending) modification_{return  0; }                         //981023
      // returns the apparent root depth                                                                                //981023
   virtual float64 calc_root_biomass                                                                                    //060612
      (float64 *output_root_biomass_by_layer=0)                const;
};
//_2007-01-31___________________________________________________________________
} // namespace CropSyst
#endif

