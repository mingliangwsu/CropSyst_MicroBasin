#ifndef OM_residues_profile_simple_V4H
#define OM_residues_profile_simple_V4H
#include "organic_matter/OM_residues_profile_common.h"
#include "common/soil/layering.h"

#if ((CS_VERSION > 0) && (CS_VERSION <= 4))

//040429 This Organic matter pool was used up to version 4.1
// In version 4.2 we have a new organic matter decomposition and mineralization.

// Forward declarations
class Soil_chemical_profile_abstract;
class Residue_pools_simple;
class Organic_matter_simple;
class Pot_mineralizable_N_profile;
class Chemical_pool;                                                             //170502
//______________________________________________________________________________
class Organic_matter_residues_profile_simple   // was Organic_matter_residues_profile_V41
: public Organic_matter_residues_profile_abstract                                //070707
{
   Organic_matter_simple         *organic_matter;
   Residue_pools_simple          *residue_pools_kg_m2;
   Pot_mineralizable_N_profile   *pot_mineralizable_N;  // if nitrogen enabled
   // external refs
   const Air_temperature_average &air_temperature_avg;                           //140507
   const Wind_speed             &wind_speed;                                     //150427
 public: // Constructors and Destructors
   Organic_matter_residues_profile_simple
      (Soil_interface                    *soil
      #ifndef OLD_N_XFER
      ,Chemical_pool                     &receiver_NO3                           //170502
      #endif
      ,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining //160720
      ,Infiltration_model                 infiltration_model                     //080117 default CASCADE_MODEL
      ,soil_sublayer_array_64            (sublayer_percent_organic_matter)
      ,bool                               constant_organic_matter
      ,nat8                               trans_sublayers                        //060116
      ,float64                            V3_adjust_mineralize                   //060116
      ,bool                               enable_nitrogen
      ,const Air_temperature_average      &air_temperature_avg                   //140507
      ,const Wind_speed                   &wind_speed                            //150427
      ,const CORN::date32 &today_raw_);                                                //170524_140507
      //170525,const CORN::Date                   &today);                               //140507
   virtual ~Organic_matter_residues_profile_simple();
   inline virtual Organic_matter_and_residue_model get_model()             const { return V4_1_ORGANIC_MATTER_AND_RESIDUE;} //070730
 public: // Residue
      virtual const Residues_interface *ref_residues() ;                         //160720
 public: // Specifically organic matter
   inline virtual float64 get_organic_matter_mass(nat8 layer)              const;//060401
 public: // carbon
   virtual float64 get_organic_carbon(nat8 sublayer, nat8 include_OM )     const;
   virtual float64 sum_carbon_to_depth_kg_m2
      (nat8 include_OM
      ,float64 to_depth_m//=ENTIRE_PROFILE_DEPTH_as_9999   // To depth of soil
      ,bool include_surface/*=false*/ )                                    const;
   inline virtual float64 sum_N_mineralization_to_depth                          //061116
      (nat8 include_OM
      ,float64 to_depth_m   // To depth of soil
      ,bool include_surface )                                              const  {return 0.0; } // Not applicable to this version. This was added for version 4.4
   inline virtual float64 sum_N_immobilization_to_depth                          //061116
      (nat8 include_OM
      ,float64 to_depth_m   // To depth of soil
      ,bool include_surface )                                              const  {return 0.0; } // Not applicable to this version. This was added for version 4.4
      // defaults to the entire profile
   inline virtual float64 sum_C_decomposition_to_depth                           //090520
      (nat8 include_OM
      ,float64 to_depth_m)   // To depth of soil
      const  { return 0.0; /*This model does not have C decomposition*/  }
   virtual inline float64 get_gaseous_CO2_C_loss_reported_daily(nat8 include_OM) const { return 0.0; } //060426
      //NA  Added to V4.4 this model does not have CO2 loss
   virtual inline float64 get_C_decomposed_from_residue(Organic_matter_position from_position) const { return 0.0; } //060817
      //NA  Added to V4.4 this model does not have C decomposition
   virtual inline float64 get_C_incorporated_by_tillage()                  const { return 0.0; } //060817
 public: // The following are for the Nitrogen model return 0 if not simulating nitrogen
   virtual float64 get_N_immobilization_profile()                          const;
   inline virtual float64 get_soil_organic_matter_immobilization_profile_N() const //110918
      { return get_N_immobilization_profile(); }

   virtual float64 get_soil_organic_matter_mineralization_profile_N()      const;
   virtual float64 get_soil_organic_matter_mineralization_N(nat8 layer)    const;
   virtual float64 get_total_straw_mineralization()                        const;
   virtual float64 get_total_manure_mineralization()                       const;
   virtual float64 get_NH4_mineralization()                                const;
   inline virtual Pot_mineralizable_N_profile *get_pot_mineralizable_N_profile() { return pot_mineralizable_N; }
   // get_pot_mineralizable_N_profile is applies only to V 4.1.xx
 public: // processing
   virtual bool process_day();
   inline virtual bool start_day()                                               { return true; } //150611_060817 Currently doesnt need to do anything, but maybe process_day() has things it clears for the day
   inline virtual bool start_year()                                              { return true; } //070510 Corrently doesn't need to do anything.
 public:
   inline virtual void decompose_all_without_N
      (float64 avg_air_temperature
      ,Soil_interface &soil)                                                     //040608
      {
      //Do nothing, this is for V4.2 V4.1 has its own decomposition
      //  Although I think the code is similar and probably could be merged eventually
      }
   inline virtual float64 *get_CO2_C_loss_profile_residue_and_OM()               {return 0;}  //060504 not applicable to this model
   inline virtual float64 *get_CO2_C_loss_profile_residue()                      {return 0;}  //080902 not applicable to this model
   inline virtual float64 *get_CO2_C_loss_profile_OM()                           {return 0;}  //080902 not applicable to this model
   inline virtual float64 get_mass_from_layer_to_layer(Mass_total mass_total,uint32 include_organic_matter_types,nat8 from_layer,nat8 to_layer,float64 prorate_fraction_bottom_layer)  const { return 0.0; /* not available in this version */ } //071214
 public: // Event processing
   inline virtual bool respond_to_field_operation                                //060726
      (float32 tillage_op_depth_m
      ,float32 tillage_op_mixing_fraction
      ,USDA::NRCS::RUSLE2::Soil_disturbance_effect   operation_soil_disturbance_effect                           // VB Operation_Soil_Disturbance_Effect
      ,const Soil_disturbance *_soil_disturbance // This model doesn't use this  //060807
      ,const float32  residue_flatten_ratio[]
      ,const float32  residue_burial_ratio[]                          // ManagementState.SurfaceResidueFractionRemainingAfterTillage
      ) { return true; };  // This model doesn't currently do anything with organic matter (residue is currently redistributed separately)
   inline virtual const Soil_disturbance *know_soil_disturbance
      (const Soil_disturbance *_soil_disturbance)                   modification_//070801
      { return _soil_disturbance; } // Do nothing, this model does not response to soil disturbance.
   inline virtual bool /*160628 nat32*/ write(std::ostream &)                        performs_IO_{ return 0;/* NYN */ } //120912
   inline virtual bool read(std::istream &stream)                    performs_IO_{ return false;/* NYN */ } //140213_120912
};
//_2005-07-26___________________________________________________________________
#endif
#endif

