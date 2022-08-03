#ifndef crop_param_NETH
#define crop_param_NETH
#pragma once
#define const_
#include "crop/crop_param_struct.h"
#include "crop/crop_param_V5.h"
//______________________________________________________________________________
namespace CropSyst
{	class Crop_parameters;
};
//______________________________________________________________________________
namespace CropSyst_parameters_NET
{
//______________________________________________________________________________
ref class Crop
{
private:
   CropSyst::Crop_parameters *crop;
public:
   const CropSyst::Crop_parameters_struct::Thermal_time               &ref_thermal_time() const_;
   const CropSyst::Crop_parameters_struct::Inactive_period            &ref_inactive_period() const_;
   const CropSyst::Crop_parameters_struct::Phenology                  &ref_phenology() const_;
   const CropSyst::Crop_parameters_struct::Transpiration              &ref_transpiration() const_;
   const CropSyst::Crop_parameters_struct::Biomass_production         &ref_biomass_production() const_;
   const CropSyst::Crop_parameters_struct::Morphology                 &ref_morphology() const_;
   const CropSyst::Crop_parameters_struct::Canopy_growth_LAI_based    &ref_canopy_growth_LAI_based() const_;
   const CropSyst::Crop_parameters_struct::Canopy_growth_cover_based  &ref_canopy_growth_cover_based()const_ ;
   const CropSyst::Crop_parameters_struct::Root                       &ref_root()const_ ;
   const CropSyst::Crop_parameters_struct::Fruit                      &ref_fruit()const_ ;
/*NYI
   const CropSyst::Crop_parameters_struct::Vernalization              *ref_vernalization() const_;
   //NYI   const CropSyst::Crop_parameters_struct::Photoperiod        *ref_photoperiod() const_;
   const CropSyst::Crop_parameters_struct::Emergence_hydro_thermal    &ref_emergence() const_;
   const CropSyst::Crop_parameters_struct::Hardiness                  *ref_hardiness() const_;
   const CropSyst::Crop_parameters_struct::Nitrogen                   &ref_nitrogen()  const_;
   const CropSyst::Crop_parameters_classs::Emergence_hydro_thermal    &ref_emergence_class() const_;
   const CropSyst::Crop_parameters_class::Harvest       *ref_harvest_class()   const_;
   const CropSyst::Crop_parameters_class::Morphology    &ref_morphology_class()const_;
   const CropSyst::Crop_parameters_class::CO2_Response  *ref_CO2_response_class()const_;
   const CropSyst::Crop_parameters_class::Fruit         &ref_fruit_class()   const_;
   const CropSyst::Crop_parameters_class::Biomass_production &ref_biomass_production_class() const_;
*/
public: // Properties

   property double RadiationUseEfficiency                      { double get() { return crop->ref_biomass_production          ().max_RUE_mode;}};
      //VB was GetRadiationUseEfficiency
   property double WaterUseEfficiency_at_1_kPa                 { double get() { return crop->ref_biomass_production          ().TUE_at_1kPa_VPD[0];}};
   property double SlopeOfWaterUseEfficiencyFunctionOfVPD      { double get() { return -crop->ref_biomass_production          ().TUE_scaling_coef[0];}};  //?
   property double OptimumMeanTemperatureForGrowth             { double get() { return crop->ref_biomass_production          ().early_growth_limit_temp;}};
      //VB was GetOptimumMeanTemperatureForGrowth
   property double InitialCanopyCover                          { double get() { return crop->ref_canopy_growth_cover_based          ().initial_cover;}};
   property double MaximumCanopyCover                          { double get() { return crop->ref_canopy_growth_cover_based          ().maximum_cover;}};
   property double GreenCanopyCoverAtMaturity                  { double get() { return crop->ref_canopy_growth_cover_based          ().mature_green_cover;}};
   property double TotalCanopyCoverAtMaturity                  { double get() { return crop->ref_canopy_growth_cover_based          ().mature_total_cover;}};
   /* These are compute parameters
   property double CanopybCoefficient                          { double get() { return crop->get_XXXX          ().xxxxxx;}};
   property double CanopyShapeFactor                           { double get() { return crop->get_XXXX          ().xxxxxx;}};
   property double CanopyAsymCC                                { double get() { return crop->get_XXXX          ().xxxxxx;}};
   property double CanopyActualCCMax                           { double get() { return crop->get_XXXX          ().xxxxxx;}};
   property double CanopyCLow                                  { double get() { return crop->get_XXXX          ().xxxxxx;}};
   property double CanopySenescenceAsymCC                      { double get() { return crop->get_XXXX          ().xxxxxx;}};
   */
   property double CriticalLeafWaterPotentialForCanopyExpansion{ double get() { return crop->ref_morphology    ().reduce_canopy_expansion_LWP;}}; 
   property double MinimumLeafWaterPotentialForCanopyExpansion { double get() { return crop->ref_morphology    ().stop_canopy_expansion_LWP;}};  //?reduce_canopy_expansion_LWP
   property double MaxRootDepth                                { double get() { return crop->ref_root          ().max_depth;}};
      //VB was GetMaxRootDepth
   property double MaximumCropHeight                           { double get() { return crop->ref_morphology    ().max_canopy_height;}};
   property double CurvatureRootDensityFunction                { double get() { return crop->ref_root          ().density_distribution_curvature;}};
      //VB was GetCurvatureRootDensityFunction
   property double BaseTemperatureForDevelopment               { double get() { return crop->ref_thermal_time  ().base_temperature;}};
      //VB was GetBaseTemperatureForDevelopment
   property double OptimumTemperatureForDevelopment            { double get() { return crop->ref_thermal_time  ().opt_temperature;}};
      //VB was GetOptimumTemperatureForDevelopment
   property double MaximumTemperatureForDevelopment            { double get() { return crop->ref_thermal_time  ().max_temperature;}};
      //VB was GetMaximumTemperatureForDevelopment
   property double ThermalTimeForEmergence                     { double get() { return crop->ref_phenology     ().emergence_deg_day;}};
      //VB was GetThermalTimeForEmergence
   property double ThermalTimeForBudbreakIfChillReached        { double get() { return crop->ref_dormancy      ().deg_day_bud_break_chill_req_sat;}};
   property double ThermalTimeForBudbreakIfChillNotReached     { double get() { return crop->ref_dormancy      ().deg_day_bud_break_chill_req_not_sat;}};
   property double ThermalTimeForFlowering                     { double get() { return crop->ref_phenology     ().begin_flowering_deg_day;}};
      //VB was GetThermalTimeForFlowering
   property double ThermalTimeForYieldFormation                { double get() { return crop->ref_phenology     ().begin_filling_deg_day;}};
      //VB was GetThermalTimeForYieldFormation
   property double ThermalTimeAtTheEndOfCanopyGrowth           { double get() { return crop->ref_phenology     ().end_vegetative_growth_deg_day;}};
   property double ThermalTimeAtTheBeginningOfCanopySenescence { double get() { return crop->ref_phenology     ().begin_senescence_deg_day;}};
   property double ThermalTimeForPhysiologicalMaturity         { double get() { return crop->ref_phenology     ().begin_maturity_deg_day;}};
   property double CropETCoeff100PercentCover                  { double get() { return crop->ref_transpiration ().ET_coef;}};
   property double MaxWaterUptake                              { double get() { return crop->ref_transpiration ().normal_max_water_uptake_mm;}};
      //VB was GetMaxWaterUptake
   property double LeafWaterPotentialForStomatalClosure        { double get() { return crop->ref_transpiration ().stomatal_closure_LWP;}};
      //VB was GetLeafWaterPotentialForStomatalClosure
   property double WiltingLeafWaterPotential                   { double get() { return crop->ref_transpiration ().wilt_LWP;}};
      //VB was GetWiltingLeafWaterPotential
   property double ATOverPTRatioThatLimitsRootGrowth           { double get() { return crop->ref_root().at_pt_root_limit;}};
      //VB was GetATOverPTRatioThatLimitsRootGrowth
   property double UnstressedHarvestIndex                      { double get() { return crop->ref_harvest_class ()->index_unstressed;}};
      //VB was  GetUnstressedHarvestIndex
   property double MaximumTranslocationFraction                { double get() { return crop->ref_harvest_class ()->translocation_fraction_max;}};
      //VB was GetMaximumTranslocationFraction
   property double FreshMassFruitLoad                          { double get() { return crop->ref_fruit         ().max_fruit_load_kg_ha;}};
   property double FractionSolidsInFruits                      { double get() { return crop->ref_fruit         ().fract_total_solids;}};
   property double RequiredChillHours                          { double get() { return crop->ref_dormancy      ().chill_hours;}};
   property double DOYStartDormancy                            { double get() { return crop->ref_inactive_period          ().start_DOY;}};
   property double DOYEndDormancy                              { double get() { return crop->ref_inactive_period          ().end_DOY;}};
   property double DormancyDuration                            { double get() { return crop->ref_inactive_period          ().min_duration;}};
   property double TemperatureForDormancy                      { double get() { return crop->ref_inactive_period          ().inducement_temperature;}};
   property double RootDepthAtEmergence                        { double get() { return crop->ref_root          ().get_depth_emergence_m();}};
      //VB was GetRootDepthAtEmergence
   property double PlantingDepth                               { double get() { return crop->ref_root          ().sow_depth;}};
      //VB was GetPlantingDepth
   property double RootGrowthSensitivityToStress               { double get() { return crop->ref_root          ().sensitivity_to_water_stress;}};
      //VB was GetRootGrowthSensitivityToStress
   /* WARNING NYI Curve numbers can be looked up from curve number table for  the hydologic group. */
   property double CropCurveNumberIIA                          { double get() { return 0; /* WARNING */}};
   property double CropCurveNumberIIB                          { double get() { return 0; /* WARNING */}};
   property double CropCurveNumberIIC                          { double get() { return 0; /* WARNING */}};
   property double CropCurveNumberIID                          { double get() { return 0; /* WARNING */}};

   property bool   RootCrop                                    { bool get() { return (crop->harvested_part_labeled.get() == tuber_part) || (crop->harvested_part_labeled.get() == root_part);};};
   property bool   C3Crop                                      { bool get() { return crop->photosynthetic_pathway_labeled.get() == C3;}};
   property bool   TreeFruitCrop                               { bool get() { return crop->harvested_part_labeled.get() == fruit_part;}};
   property bool   PerennialCrop                               { bool get() { return crop->is_perennial();}};
   property bool   GrainCrop                                   { bool get() { return crop->harvested_part_labeled.get() == grain_part;}};
   property bool   VegetativeCrop                              { bool get() { return !RootCrop && ! GrainCrop && !TreeFruitCrop;}};
   property double BaselineCO2Concentration                    { double get() { return crop->ref_CO2_response_class()->baseline_reference_conc;}};
   property double ExperimentalElevatedCO2Concentration        { double get() { return crop->ref_CO2_response_class()->growth_ratio_elevated_to_baseline_ppm;}};
   property double ExperimentalBiomassGainRatioInResponseToCO2 { double get() { return crop->ref_CO2_response_class()->elevated_reference_conc;}};

public:
   Crop(System::String ^crop_file_name);
   ~Crop();
};
//_2011-04-29__________________________________________________________________/
}; // namespace
#undef const_
#endif
