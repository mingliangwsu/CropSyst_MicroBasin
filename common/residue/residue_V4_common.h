#ifndef residue_V4_commonH
#define residue_V4_commonH
#include "options.h"
#include "common/residue/residues_common.h"
#include "USDA/NRCS/RUSLE2/SDR_field_ops.h"
//______________________________________________________________________________
class Organic_biomatter_common;
class Organic_matter_pools_common;
class Soil_abiotic_environment_profile;
//______________________________________________________________________________
// These classes are common to residue and organic matter submodels created
// and/or used in CropSyst versions V4.1 V4.2 V4.3 and V4.4
// (4.2 and 4.3 are now permenantly defunct)
// V4.1 is works with the original single organic matter pool.
// V4.4 will probably be the only one carried on to version 5.
//______________________________________________________________________________

// Note, this is common for V4 and later versions
//______________________________________________________________________________
class Residues_V4_common
: public Residues_common
{
protected:
   Organic_matter_pools_common               &organic_matter_pools; // owned by ????
   Soil_abiotic_environment_profile          &soil_abiotic_environment_profile;
public: // structor
   Residues_V4_common
      (Organic_matter_pools_common        &organic_matter_pools                  //060122
      ,Soil_interface                     &soil                                  //060122
      ,Soil_abiotic_environment_profile   &soil_abiotic_environment_profile
      ,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining       //160719
      ,const Air_temperature_average      &temperature_air_avg                   //150427
      ,const Wind_speed                   &wind_speed                            //150427
      ,const CORN::date32                 &today                                 //170523
      ,std::ostream                       *detail_log);                          //020307
public: // event processing
   virtual bool respond_to_field_operation                                       //060727
      (float32  tillage_op_depth_m                                               //VB  T_Depth = ManagementState.TillageDepth
      ,USDA::NRCS::RUSLE2::Soil_disturbance_effect    operation_soil_disturbance_effect              // VB Operation_Soil_Disturbance_Effect
      ,const float32  residue_flatten_ratio[RUSLE2_RESIDUE_TYPE_COUNT]
      ,const float32  residue_burial_ratio_fraction[RUSLE2_RESIDUE_TYPE_COUNT]); // ManagementState.SurfaceResidueFractionRemainingAfterTillage
   virtual float64 remove_from_surface
      (float64    fract_to_remove // 0-1
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
      ,int16      SCS_code
#endif
      );
 public:
    virtual void update_totals_sum_pools();
 private:
    float64 get_subsurface_XXXX_biomass(soil_sublayer_array_64(layer_residues),Organic_matter_type residue_type); //000810
 public: // accessors
    virtual float64 get_surface_all_biomass()                              const;
    virtual float64 get_surface_plant_biomass(nat32 include_positions)     const;//170107_090311
    virtual float64 get_subsurface_all_biomass()                           const;//060116
    virtual float64 get_subsurface_plant_biomass(soil_sublayer_array_64(plant_residues) = 0);   //000810
    virtual float64 get_subsurface_manure_biomass(soil_sublayer_array_64(manure_residues) = 0); //000810
    virtual float64 get_total_surface_biomass()                            const;//011011
    virtual float64 get_biomass_output
      (nat32 include_positions,nat32 include_residue_types)                const;//050116
    virtual CORN::Unidirectional_list &get_pool_list();                          //060202
 public: // maintenance
    virtual void recalibrate_surface_residue                                     //000312
       (float64 surface_residue_param
       ,float64 incorp_residue_param                                             //010202
       ,const Residue_decomposition_parameters &residue_decomposition_params     //060219
       #ifdef NITROGEN
       ,float64 residue_N_conc_param
       #endif
       );
    virtual void redistribute_all
       (float64 fract_surface_to_surface
       ,float64 fract_surface_to_shallow);
   inline virtual void update_environment() {}                                   //040518
   virtual void decompose_all_without_N();                                       //040608
   virtual void exhaust_all() = 0;
   virtual void balance(bool run_nitrogen);                                      //990517
 public: // lookups
    Organic_biomatter_common *find                                               //060727
      (Organic_matter_type straw_or_manure
      ,Organic_matter_position flat_or_stubble
      ,Organic_matter_cycling fast_slow_or_lignified_cycling
      ,nat8 layer = 0);
 public: // calculations
   float64 calc_carbon_nitrogen_ratio
      (float64 _biomass                 //  any mass/area units
      ,float64 _nitrogen_concentration
      ,float64 _carbon_fraction
      ,float64 _default_carbon_nitrogen_ratio // incase N mass is unavailable
      ) const;         // fraction of biomass that is elemental carbon mass
 private:
   void redistribute                                                             //990217
      (CORN::Unidirectional_list &redistributed_pools                            //980924
      ,Organic_biomatter_common *pool_to_redistributed
      ,float64 fract_shallow_to_deeps
      ,float64 fract_surface_to_deeps                                            //980924
      ,float64 fract_surface_to_shallow
      ,float64 shallow_horizon_thickness                                         //990217
      ,float64 deep_horizon_thickness);                                          //990217
   virtual void setup_contribution(Organic_biomatter_common &residue)      const = 0; //060728
 protected:
   virtual Organic_matter_cycling get_first_OM_cycling()                   const = 0;//070707
   virtual Organic_matter_cycling get_last_OM_cycling()                    const = 0;//070707
};
//______________________________________________________________________________
#endif

