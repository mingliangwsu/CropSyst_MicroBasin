#ifndef management_param_V5H
#define management_param_V5H
//______________________________________________________________________________
#include "options.h"
#if (MANAGEMENT!=4)
#include "management/management_param_class.h"
#include "corn/parameters/parameter.h"
namespace CropSyst {
//______________________________________________________________________________
class Tillage_operation
: public Tillage_operation_class
{
 public:
   CORN::Parameter_number p_dust_mulch_depth_cm;
   CORN::Parameter_number p_dust_mulch_effective_days;
   CORN::Parameter_number p_dust_mulch_intensity;  // 0 to 1 where 0 is not effect and 1 is most intense value
   CORN::Parameter_number p_oxidation_effect_sand; // 1.5 is low  6.0 is high
   CORN::Parameter_number p_oxidation_effect_clay; // 0.5 is low  2.0 is high
 public:
   Tillage_operation();
   VIRTUAL_VOID_SETUP_PARAMETERS;
};
//_2011-01-13___________________________________________________________________
class Organic_nitrogen_operation_abstract
: public Organic_nitrogen_operation_abstract_class
{
public:
   CORN::Parameter_number p_org_N;                                               //060717
   CORN::Parameter_number p_NH3_N;
   CORN::Parameter_number p_dry_matter;                                          //060717
   CORN::Parameter_number p_long_term_org_N_volatilization_loss;                 //020525x
//NYI   CORN::Parameter_number p_total_solids;                                   //130406
 public: // constructor
   Organic_nitrogen_operation_abstract(CropSyst_Op cs_op);
   VIRTUAL_VOID_SETUP_PARAMETERS;
   void log(std::ostream &log_file) const;
};
//_2011-01-XX___________________________________________________________________
DECLARE_Biomatter_application_operation
//______________________________________________________________________________
class  Inorganic_nitrogen_operation
: public  Inorganic_nitrogen_operation_class  // CropSyst_field_operation may be sufficient
{
 public:
   CORN::Parameter_number p_NO3_N;
   CORN::Parameter_number p_NH4_N;
   CORN::Parameter_number p_NH4_volatilization;

   CORN::Parameter_number p_N_soil_critical;                                     //170705
   CORN::Parameter_number p_sampling_depth;                                      //170705
 public:
   Inorganic_nitrogen_operation() ;
   virtual void setup_parameters(CORN::Data_record &data_rec,bool for_write) modification_;   //970709x
   virtual void log(std::ostream &log_file)                               const; //020810
};
//_1998-12-12___________________________________________________________________
class Harvest_or_clipping_operation
: public virtual Harvest_or_clipping_operation_class                             //170704
{
public:
   CORN::Parameter_number p_min_LAI_required;                                    //020314
   CORN::Parameter_number p_min_biomass_required_kg_ha;                          //040628
   CORN::Parameter_number p_reserve_biomass_kg_ha;                               //040907
   CORN::Parameter_number p_remove_amount_kg_ha;                                 //040629
   CORN::Parameter_number p_min_retain_GAI;                                      //051103
   CORN::Parameter_number p_remove_for_use_percent;
   CORN::Parameter_number p_remove_for_grazing_percent;
   CORN::Parameter_number p_biomass_returned_as_manure;
   CORN::Parameter_number p_remove_for_disposal_percent;
   CORN::Parameter_number p_remain_as_residue_percent;
   CORN::Parameter_number p_remain_standing_live_percent;
   CORN::Parameter_number p_remain_standing_dead_percent;
   CORN::Parameter_number p_remain_roots_as_dead_residue_percent;
   CORN::Parameter_number p_remove_roots_as_loss_percent;
   CORN::Parameter_number p_remain_roots_live_percent;
   CORN::Parameter_number p_grazing_percent_N_as_OM;                             //040126
   CORN::Parameter_number p_grazing_percent_N_as_NH3;                            //040126
public:
   Harvest_or_clipping_operation(); // section setup constructor
#ifdef CHECK_OBSOLETE
   Harvest_or_clipping_operation(const Harvest_or_clipping_operation_class &to_be_copied); // <- This may be obsolete
#endif
   void setup_parameters(CORN::Data_record &data_rec,bool for_write);
};
//_2011-01-XX___________________________________________________________________
class Auto_clip_biomass_mode
: public virtual Auto_clip_biomass_mode_class
, public virtual Harvest_or_clipping_operation                                   //170704
{
 public:
   CORN::Parameter_number p_adjust_relative_growth_rate_for_clipping;
   CORN::Parameter_number p_LAI_forces_clipping;
   CORN::Parameter_number p_biomass_forces_clipping;
   CORN::Parameter_number p_flowering_forces_clipping;
 public:
   Auto_clip_biomass_mode();
   Auto_clip_biomass_mode(const Auto_clip_biomass_mode& to_be_copied);
   virtual void setup_parameters(CORN::Data_record &data_rec,bool for_write) modification_;   //970709x
   virtual void log(std::ostream &log_file)                                const;
};
//_2011-01-XX___________________________________________________________________
class Irrigation_operation_parameters_numeric
{public:
   CORN::Parameter_number p_max_allowable_depletion;
   CORN::Parameter_number p_depletion_observe_depth;
   CORN::Parameter_number p_depletion_observe_root_zone_fract;
   CORN::Parameter_number p_min_application;
   CORN::Parameter_number p_max_application;
   CORN::Parameter_number p_leaf_water_potential;
   CORN::Parameter_number p_amount;
   CORN::Parameter_number p_salinity;
   CORN::Parameter_number p_ECw_to_TDS;
   CORN::Parameter_number p_NO3_N_concentration;
   CORN::Parameter_number p_NH4_N_concentration;
   CORN::Parameter_number p_net_irrigation_mult;
   CORN::Parameter_number p_refill_point;
   CORN::Parameter_number p_surface_evaporation_area;
   CORN::Parameter_number p_profile_volume;
 public:
    Irrigation_operation_parameters_numeric(Irrigation_operation_struct &op);
};
//______________________________________________________________________________

// NYI CORN::Parameter_number p_chemical_concentration;  perhaps eventually for pesticides

class Irrigation_operation
: public /*virtual */ Irrigation_operation_class
{
 public:
   //170710 IRRIGATION_VALID_ENTRIES
   Irrigation_operation_parameters_numeric parameters;                                   //170710
   virtual void setup_parameters(CORN::Data_record &data_rec,bool for_write) modification_; //970709x
   virtual void log(std::ostream &log_file)                  const;  // temporarily abstract so I make sure to implement //020810_
 public: // constructor
   Irrigation_operation(CropSyst_Op  irrig_or_auto_irrig_code = CS_OP_MGMT_IRRIGATION) ;
};
//_2011-01-XX___________________________________________________________________
class Automatic_irrigation_mode
: public virtual Automatic_irrigation_mode_class
// Not compiling , public virtual Irrigation_operation //170706
   // Now derived from Irrigation operation so we can get the salinity and chemical values  020313
{  // When simulating salinity, the automatic irrigation with have a default concentration.
 public:
   Irrigation_operation_parameters_numeric parameters;                                   //170710
public: // constructor
   Automatic_irrigation_mode();                                                  //990224
public: // Common operation virtual methods
   virtual void log(std::ostream &log_file)                               const; //020810
   virtual void setup_parameters(CORN::Data_record &data_rec,bool for_write) modification_; //970709
};
//_2013-04-08_______________________________________Automatic_irrigation_mode__/
class N_application_soil_observation_mode
: public N_application_soil_observation_mode_class
{public:
   CORN::Parameter_number p_target_yield_N_uptake;// kg/ha  Crop N uptake for target yield
   CORN::Parameter_number p_estimatied_mineralization;
//120710 only in V4   CORN::Parameter_number p_critical_soil_NO3_for_no_response_kg_ha;// kg/ha
   CORN::Parameter_number p_soil_N_sampling_depth;      // m
   CORN::Parameter_number p_fertilizer_use_efficiency;  // % 0-100
public:
   N_application_soil_observation_mode();
   virtual void setup_parameters
      (CORN::Data_record &data_rec,bool for_write)                modification_; //970709
   virtual void log(std::ostream &log_file)                               const; //020810
};
//_2011-01-XX___________________________________________________________________
class Chemical_operation
: public Chemical_operation_class
{
 public: // public for parameter editor
   CORN::Parameter_number p_chemical_concentration;
 public:
   Chemical_operation() ;
   virtual void setup_parameters
      (CORN::Data_record &data_rec,bool for_write)                modification_; //970709
};
//_2011-01-XX___________________________________________________________________
class Management_parameters
: public Management_parameters_class
{
 public:  // validators
   CORN::Parameter_number p_soil_conservation_factor;
 public:
   Management_parameters();
   virtual bool expect_structure(bool for_write);                                //161025
   virtual nat32 fertilization_nitrogen_multiply_by(float multiplier)modification_;//070716
};
//_2011-01-15___________________________________________________________________
} // namespace CropSyst

#  define   org_N_appl_method_cowl_or_labeled      org_N_appl_method_cowl
#  define   org_N_source_cowl_or_labeled           organic_matter_source_cowl
#  define   automatic_N_mode_cowl_or_labeled       automatic_N_mode_cowl
#  define   NH4_source_cowl_or_labeled             NH4_source_cowl
#  define   NH4_appl_method_cowl_or_labeled        NH4_appl_method_cowl
#  define   harvest_amount_mode_cowl_or_labeled    harvest_amount_mode_cowl
#  define   application_mode_cowl_or_labeled       application_mode_cowl
#  define   consideration_mode_cowl_or_labeled     consideration_mode_cowl
//#  define   application_mode_cowl_or_labeled       application_mode_cowl
#  define   depletion_observation_depth_mode_cowl_or_labeled  depletion_observation_depth_mode_cowl
#  define   harvest_fate_mode_cowl_or_labeled      harvest_fate_mode_cowl

#endif
#endif
