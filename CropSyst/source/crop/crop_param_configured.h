#ifndef crop_param_configuredH
#define crop_param_configuredH
#include "crop/crop_param_class.h"
#include "corn/container/association.h"
#include "CS_suite/parameters/CS_document.h"

#define APPLICABILITY(option,selections)  ((selections<<16) & option)


namespace CropSyst                                                               ///110208
{
//______________________________________________________________________________
class Observation
{
   Synchronization   sync;
   float32           value;
};
//______________________________________________________________________________
class Crop_parameters      // Move some of these to Crop_classification_parameters
: public extends_ Crop_parameters_class
{
 public:
   Crop_parameters();
 public:
   Crop_parameters_class::Thermal_time                thermal_time;
   Crop_parameters_class::Phenology                   phenology;
   Crop_parameters_class::Transpiration               transpiration;
   Crop_parameters_class::Biomass_production          biomass_production;
   Crop_parameters_class::Morphology                  morphology;
   Crop_parameters_class::Harvest                     harvest;
   Crop_parameters_class::Root                        root;

   // Optional elements:
   Crop_parameters_class::Canopy_growth_LAI_based     canopy_growth_LAI_based;
   Crop_parameters_class::Canopy_growth_cover_based   canopy_growth_cover_based;

   Crop_parameters_class::Quiescence                  quiescence;
   Crop_parameters_class::Dormancy                    dormancy;
   Crop_parameters_class::Tolerance                   tolerance;                 //150913 was
   Crop_parameters_class::Vernalization               vernalization;              //optional was pointer
   Crop_parameters_class::Photoperiod                 photoperiod;                //optional was pointer
   Crop_parameters_class::Emergence_hydro_thermal     emergence;                  // optional
   Crop_parameters_class::Salinity                    salinity;                   // optional was pointer
   Crop_parameters_class::Layout                      layout;                     //optional was pointer
   Crop_parameters_class::Canopy_characteristics_hedge_row canopy_characteristics_hedge_row; //optional was pointer

   Crop_parameters_class::Fruit                       fruit;
   Crop_parameters_class::Nitrogen                    nitrogen;
   Crop_parameters_class::CO2_Response                CO2_response;
   Residue_decomposition_parameters                   residue_decomposition;

 public: // reference accessors
   inline virtual Crop_parameters_struct::Quiescence                  &ref_quiescence()                { return quiescence;}
   inline virtual Crop_parameters_struct::Thermal_time                &ref_thermal_time()              { return thermal_time;}
   inline virtual Crop_parameters_struct::Phenology                   &ref_phenology()                 { return phenology;}
   inline virtual Crop_parameters_struct::Transpiration               &ref_transpiration()             { return transpiration; }
   inline virtual Crop_parameters_struct::Biomass_production          &ref_biomass_production()        { return biomass_production; }
   inline virtual Crop_parameters_struct::Morphology                  &ref_morphology()                { return morphology;}
   inline virtual Crop_parameters_struct::Canopy_growth_LAI_based     &ref_canopy_growth_LAI_based ()  { return canopy_growth_LAI_based;}
   inline virtual Crop_parameters_struct::Canopy_growth_cover_based   &ref_canopy_growth_cover_based() { return canopy_growth_cover_based;}
   inline virtual Crop_parameters_struct::Root                        &ref_root()                      { return root;}
   inline virtual Crop_parameters_struct::Fruit                       &ref_fruit()                     { return fruit; }
   inline virtual Crop_parameters_struct::Dormancy                    &ref_dormancy()                  { return dormancy;}

//NYN virtual const Crop_parameters_struct::Inactive_period            &ref_inactive_period() const=0;
   inline virtual const Crop_parameters_struct::Thermal_time          &ref_thermal_time()              const { return thermal_time;}
   inline virtual const Crop_parameters_struct::Phenology              &ref_phenology()                const { return phenology;}
//NYN virtual const       Crop_parameters_struct::Transpiration &transpiration = ref_transpiration() = 0;
   inline virtual const Crop_parameters_struct::Biomass_production     &ref_biomass_production()       const { return biomass_production; }
   inline virtual const Crop_parameters_struct::Morphology             &ref_morphology()               const { return morphology;}
//NYN virtual const Crop_parameters_struct::Canopy_growth_LAI_based    &ref_canopy_growth_LAI_based() const=0;
   inline virtual const Crop_parameters_struct::Canopy_growth_cover_based   &ref_canopy_growth_cover_based() const { return canopy_growth_cover_based;}
//NYN virtual const Crop_parameters_struct::Root                       &ref_root()const=0 ;
//NYN virtual const Crop_parameters_struct::Fruit                      &ref_fruit()const=0 ;

   inline virtual Crop_parameters_struct::Vernalization               &ref_vernalization ()            { return vernalization;}
   inline virtual Crop_parameters_struct::Photoperiod                 &ref_photoperiod ()              { return photoperiod;}
   inline virtual Crop_parameters_struct::Emergence_hydro_thermal     &ref_emergence ()                { return emergence;}
//NYN virtual const Crop_parameters_struct::Vernalization              *ref_vernalization() const=0;
//NYN virtual const Crop_parameters_struct::Photoperiod                *ref_photoperiod()const=0 ;
//NYN virtual const Crop_parameters_struct::Emergence_hydro_thermal    &ref_emergence() const=0;

   inline virtual Crop_parameters_class::Tolerance                    &ref_tolerance_class() { return tolerance; } //150913
   //150913 inline virtual Crop_parameters_class::Hardiness                    &ref_hardiness_class() { return hardiness; }
   virtual Crop_parameters_class::Nitrogen      &ref_nitrogen_class()  { return nitrogen;}
   virtual Crop_parameters_class::Emergence_hydro_thermal    &ref_emergence_class() { return emergence;}


   virtual Crop_parameters_class::Transpiration &ref_transpiration_class()          { return transpiration;}
   virtual Crop_parameters_class::Harvest       &ref_harvest_class()                { return harvest;}
   virtual Crop_parameters_class::Morphology    &ref_morphology_class()             { return morphology; }
   virtual Crop_parameters_class::CO2_Response  &ref_CO2_response_class()           { return CO2_response;}
   virtual Crop_parameters_class::Fruit         &ref_fruit_class()                  { return fruit; }
   virtual Crop_parameters_class::Biomass_production &ref_biomass_production_class(){ return biomass_production; }
};
//_2015-09-13___________________________________________________________________
class Crop_parameters_configured
: public extends_ CS::Document_configured
{
   modifiable_ Crop_parameters &parameters;                                      //151019
 public:
   Crop_parameters_configured(modifiable_ Crop_parameters &parameters_);
   //virtual bool initialize()                                    initialization_;
   virtual bool initialize_parameter_associations()             initialization_; //160630
   virtual bool initialize_parameter_pertinencies()             initialization_; //160630
   virtual bool initialize_parameter_essentials()             initialization_; //160630
 private:
   CORN::Unidirectional_list parameter_adjustments; // list of  Parameter_adjustment_settings

 private:
   void abstract_check() { new Crop_parameters_configured(parameters); }
};
//_2015-09-13___________________________________________________________________
} // namespace CropSyst

#endif
