#include "clscrop.h"
#include "util/pubtools.h"
#include <math.h>
#include <iostream>
//_____________________________________________________________________________/
clsCrop::clsCrop
(AllControlClass &_ControlRef
,const CORN::Date &_today                                                        //150630RLN
)
    :ControlRef(_ControlRef)
{
    pCropState = new CropStateClass;
    //pCropParameters = new CropInputClass(ControlRef);
    pCanopyCover = new CropCanopyGrowthClass(*pCropState);
    pRoot = new CropRootClass(*pCropState);
    pCropDevelopment = new CropDevelopmentClass(*pCropState);
    pPotTransp =  new CropPotentialTranspirationClass(*pCropState);
    pBiomass = new CropBiomassClass(*pCropState,_ControlRef,_today);             //150630RLN
    pWatUpt = new CropWaterUptakeClass(*pCropState);
    pCropNitrogenUptake = new CropActualNitrogenUptakeClass(*pCropState);
    pCropSoluteUptake = new CropPotSoluteUptakeClass(*pCropState);
    ClearStateForNextCropSeason();
}
//_____________________________________________________________________________/
void clsCrop::setWaitingForEmergence(bool X) {Waiting_For_Emergence = X;}
bool clsCrop::getWaitingForEmergence() {return Waiting_For_Emergence;}
double clsCrop::CalculateMinimum(double a,double b,double c) {
    return std::min<double>(std::min<double>(a,b),c);
}
//_____________________________________________________________________________/
void clsCrop::DetermineCO2Response(WeatherStateDailyClass &Weather)
{
    const double Canopy_Conductance_Reduction_Factor(0.6);  //Reduction from CO2 concentration at the time of FAO56 publication
    const double CO2_Concentration_FAO56(330.0);
    #ifdef LIU_ENGINE
    if (ControlRef.CO2_Run)
    #else
    if (ControlRef.simulate_CO2)
    #endif
    {
        double Current_CO2 = ControlRef.Current_CO2_Concentration;
        double Baseline_CO2_Concentration = pCropParameters->Baseline_CO2_Concentration;
        double Experimental_Elevated_CO2_Concentration = pCropParameters->Experimental_Elevated_CO2_Concentration;
        double Experimental_Biomass_Gain_Ratio_In_Response_To_CO2 = pCropParameters->Experimental_Biomass_Gain_Ratio_In_Response_To_CO2;
        //Determine biomass gain due to elevated CO2
        double CO2_Concentration_For_Half_Maximum_Biomass_Gain_Ratio = 
                (Experimental_Elevated_CO2_Concentration 
                 * Baseline_CO2_Concentration 
                 * (Experimental_Biomass_Gain_Ratio_In_Response_To_CO2 - 1)
                )
                / (Experimental_Elevated_CO2_Concentration 
                   - Experimental_Biomass_Gain_Ratio_In_Response_To_CO2 * Baseline_CO2_Concentration
                   );
        double Maximum_CO2_Driven_Biomass_Gain_Ratio = 
            (Baseline_CO2_Concentration + CO2_Concentration_For_Half_Maximum_Biomass_Gain_Ratio) 
            / Baseline_CO2_Concentration;
        double Actual_Biomass_Gain_Ratio_In_Response_To_CO2 = 
            Current_CO2 * Maximum_CO2_Driven_Biomass_Gain_Ratio 
            / (Current_CO2 + CO2_Concentration_For_Half_Maximum_Biomass_Gain_Ratio);
        //Determine canopy resistance adjusted for CO2
        double FAO56_Canopy_Resistance = Weather.getUnstressedCanopyResistance();
        double Current_CO2_Concentration = ControlRef.Current_CO2_Concentration;
        double CO2_Adjusted_FAO56_Canopy_Resistance = FAO56_Canopy_Resistance * (1.0 + (1.0 / Canopy_Conductance_Reduction_Factor - 1)
            * (Current_CO2_Concentration - CO2_Concentration_FAO56) / CO2_Concentration_FAO56);
        //TODO (LML 150110) XXX OJO Which approach will be used?
        CO2_Adjusted_FAO56_Canopy_Resistance = 
            FAO56_Canopy_Resistance 
            / (1.0 - (Current_CO2_Concentration - CO2_Concentration_FAO56) 
            * 0.001212);
        //Determine transpiration reduction due to CO2-induced increased canopy resistance
        double gamma = Weather.getPsychrometricConstant();
        double delta = Weather.getSlopeSaturationVaporPressureFunctionOfTemperature();
        double ra = Weather.getAerodynamicResistance();
        double Transpiration_Reduction_Factor_Due_To_CO2 = 
            (delta + gamma * (FAO56_Canopy_Resistance + ra) / ra)
            / (delta + gamma * (CO2_Adjusted_FAO56_Canopy_Resistance + ra) / ra);
        //Record outputs
        pCropState->CO2_Adjustment_To_RUE = Actual_Biomass_Gain_Ratio_In_Response_To_CO2;
        pCropState->CO2_Adjustment_To_TUE = Actual_Biomass_Gain_Ratio_In_Response_To_CO2 / Transpiration_Reduction_Factor_Due_To_CO2; //The denominator compensates for reduced transpiration to preserve the empirical biomass increase due to CO2
        pCropState->CO2_Adjustment_To_Transpiration = Transpiration_Reduction_Factor_Due_To_CO2;
    } else {
        pCropState->CO2_Adjustment_To_RUE = 1.;
        pCropState->CO2_Adjustment_To_TUE = 1.;
        pCropState->CO2_Adjustment_To_Transpiration = 1.;
    }
}
//_____________________________________________________________________________/
void clsCrop::DetermineClippedYield()
{
    double Actual_Crop_Cumulative_Biomass = pCropState->Cumulative_Biomass;
    double Potential_Crop_Cumulative_Biomass = pCropState->Potential_Cumulative_Biomass;
    double Harvest_Index = pCropParameters->Unstressed_Harvest_Index;
    pCropState->Potential_Yield = Potential_Crop_Cumulative_Biomass * Harvest_Index;
    pCropState->Yield = Actual_Crop_Cumulative_Biomass * Harvest_Index;
}
//_____________________________________________________________________________/
void clsCrop::DetermineTreeFruitYield()
{
    double Fress_Mass_Fruit_Load = pCropParameters->Fresh_Mass_Fruit_Load;
    double Fraction_Of_Solids = pCropParameters->Fraction_Solids_In_Fruits;
    double Maximum_Yield = Fress_Mass_Fruit_Load * Fraction_Of_Solids / 10000.0; //converted from kg/ha to kg/m2
    pCropState->Potential_Yield = Maximum_Yield;
    pCropState->Yield = CalculateMinimum(Maximum_Yield, 
                                         pCropState->Cumulative_Fruit_Biomass_Growth, 
                                         9999);
}
//_____________________________________________________________________________/
void clsCrop::DetermineAnnualCropYield()
{
    bool Root_Crop = pCropParameters->Root_Crop;
    double Unstressed_Harvest_Index = pCropParameters->Unstressed_Harvest_Index;
    double Maximum_Harvest_Index = Unstressed_Harvest_Index * 1.1;
    double Flowering_Stress_Factor = 1.0 - pCropState->Flowering_Water_Stress_Index;
    double Maximum_Translocation_Fraction = pCropParameters->Maximum_Translocation_Fraction;
    //Determine maximum possible yield
    //double Potential_Crop_Cumulative_Biomass = pCropState->Potential_Cumulative_Biomass;   // PotentialCumulativeBiomass(pCropState->DaysAfterCropExistsAtMaturity)
    double Actual_Crop_Cumulative_Biomass = pCropState->Cumulative_Biomass;                //(pCropState->DaysAfterCropExistsAtMaturity)
    //Determine maximum yield as affected by sink damage  XXX OJO: Consider sources of damage other than water stress
    double Sink_Damaged_Maximum_Harvest_Index(0.0);
    if (Flowering_Stress_Factor < 0.3)
        Sink_Damaged_Maximum_Harvest_Index = Unstressed_Harvest_Index * Flowering_Stress_Factor / 0.3;
    else
        Sink_Damaged_Maximum_Harvest_Index = Unstressed_Harvest_Index;
    //Determine HI asymptote and decay coefficient
    double Biomass_Produced_During_Yield_Formation = pCropState->Biomass_Produced_During_Yield_Formation;
    double Biomass_Produced_Before_Yield_Formation = pCropState->Biomass_Produced_Before_Yield_Formation;
    double Fraction_Biomass_Produced_During_Yield_Formation = 
        Biomass_Produced_During_Yield_Formation
        / (Biomass_Produced_During_Yield_Formation + Biomass_Produced_Before_Yield_Formation);
    double Maximum_Fraction_Biomass_Produced_During_Yield_Formation(0.0);
    if (Root_Crop)
        Maximum_Fraction_Biomass_Produced_During_Yield_Formation = 0.85;
    else
        Maximum_Fraction_Biomass_Produced_During_Yield_Formation = 0.6;
    double Decay_Coefficient(2.0); //initial value for iteration
    double Fraction_Near_Zero(0.00001);
    double HI_at_Fraction_Near_Zero = Fraction_Near_Zero + (1 - Fraction_Near_Zero) * Maximum_Translocation_Fraction;
    double Error(1.0);
    double Harvest_Index_Asymptote(0.0);
    while (Error > 0.0001) {
        Harvest_Index_Asymptote = (Maximum_Harvest_Index - Maximum_Translocation_Fraction * exp(-Decay_Coefficient * Maximum_Fraction_Biomass_Produced_During_Yield_Formation))
                / (1 - exp(-Decay_Coefficient * Maximum_Fraction_Biomass_Produced_During_Yield_Formation));
        double New_Decay_Coefficient = -log((Harvest_Index_Asymptote - HI_at_Fraction_Near_Zero)
            / (Harvest_Index_Asymptote - Maximum_Translocation_Fraction)) / Fraction_Near_Zero;
        Error = fabs(New_Decay_Coefficient - Decay_Coefficient);
        Decay_Coefficient = New_Decay_Coefficient;
    };
    double Harvest_Index = Harvest_Index_Asymptote 
                           - (Harvest_Index_Asymptote - Maximum_Translocation_Fraction)
                             * exp(-Decay_Coefficient 
                             * Fraction_Biomass_Produced_During_Yield_Formation);
    double Crop_Yield = Actual_Crop_Cumulative_Biomass 
                        * CalculateMinimum(Harvest_Index, 
                                           Sink_Damaged_Maximum_Harvest_Index, 
                                           99.99);
    pCropState->Yield = Crop_Yield; //This crop yield could be reduced if (not sufficient N is available to meet the minimum grain N concentration (see CalculateCropNitrogenPartitioning)
    pCropState->Potential_Yield = pCropState->Potential_Cumulative_Biomass * pCropParameters->Unstressed_Harvest_Index;
}
//_____________________________________________________________________________/
void clsCrop::PerformPotentialProcesses(clsSimulation &Simulation,
  WeatherStateDailyClass &Weather)
{
    //Calculate fraction of intercepted irradiance
    pCanopyCover->DetermineUnstressedCover(Simulation/*150601,*pCropParameters*/);
    //Calculate potential transpiration for potential crop growth
    pPotTransp->DeterminePotentialTranspiration(true, Weather, *pCropParameters);
    //Calculate potential biomass growth
    pBiomass->DeterminePotentialGrowth(true, Weather, Simulation,*pCropParameters);
}
//_____________________________________________________________________________/
void clsCrop::SetHarvest(clsSimulation &Simulation, WeatherStateDailyClass &Weather)
{
   /*140219 RLN unused
    int Year = Simulation.pTimeState->getToday().year();
    int DOY = Simulation.pTimeState->getToday().getDayOfYear();
    */
    //Clear TimeState crop-related properti.es
    Simulation.pTimeState->setDaysAfterCropExists(0);
    Simulation.pTimeState->setDaysAfterGrowingSeasonStarted(0);
    Simulation.pTimeState->setDaysAfterPhysiologicalMaturity(0);
    Weather.setDailyGreenCanopySolarInterceptionFraction(0);
    Weather.setDailyCanopySolarInterceptionFraction(0);
    ClearStateForNextCropSeason();
}
//_____________________________________________________________________________/
void clsCrop::StartCrop(clsSimulation &Simulation,clsSoil &Soil)
{
    //Calculate initial soil water profile
    pCropState->Initial_Soil_Profile_Water = 
        Simulation.pBalance->CalculateSoilWaterProfile_mm();
    pCropState->Potential_Current_ET_Crop_Coeff = 1;
    pCropState->Current_ET_Crop_Coeff = 1;
    pCropState->Days_After_Crop_Exist_At_Emergence = 
            Simulation.pTimeState->getDaysAfterCropExists();
    if (pCropParameters->Perennial_Crop) {
        pCropState->Cumulative_Thermal_Time = 0;
        pCropState->Yesterday_Cumulative_Thermal_Time = 0;
    }
    //Initialize day water stress factor
    pCropState->Yesterday_Water_Stress_Factor = 1.0;
    pCropState->Yesterday_Water_Stress_Index = 0.;
    pCropState->Water_Stress_Factor = 1.;
    pCropState->Water_Stress_Index = 0.;
    //Initialize cumulative state variables
    pCropState->Cumulative_Actual_Crop_Transpiration = 0.;
    pCropState->Cumulative_Crop_Potential_Transpiration = 0.;
    pCropState->Cumulative_Water_Stress_Index = 0.;
    //Initialize biomass
    //Assumes intial GAI = -ln(1-Fract Solar Interception)/0.5, where 0.5 is solar rad extinction coeff.
    //Also assumes leaf area density = 20 m2/kg
    double Initial_Biomass = (-log(1.0 - pCropParameters->Initial_Canopy_Cover) / 0.5) / 20.0;
    pCropState->Attainable_Biomass_Today = Initial_Biomass;
    pCropState->Biomass_Today = Initial_Biomass;
    pCropState->Cumulative_Attainable_Biomass = Initial_Biomass;
    pCropState->Cumulative_Biomass = Initial_Biomass;
    //150529 pCropState->Cumulative_Biomass_Yesterday = Initial_Biomass;         //LML 141006
    pCropState->Potential_Biomass_Today = Initial_Biomass;
    pCropState->Potential_Cumulative_Biomass = Initial_Biomass;
    //Initialize root depth
    pCropState->Root_Depth = pCropParameters->Root_Depth_At_Emergence;
    if (!pCropParameters->Perennial_Crop) pRoot->DetermineRootGrowth(true, Soil, *pCropParameters);
    //Initialize plant nitrogen
    pCropState->Root_N_Mass = pCropState->Cumulative_Root_Biomass
                              * pCropParameters->Root_N_Concentration;
    pCropState->Root_N_Mass_Yesterday = pCropState->Root_N_Mass;                 //150529LML
    pCropState->Root_N_Mass_At_Emergence = pCropState->Root_N_Mass;
    pCropState->Top_Crop_N_Concentration = pCropParameters->Max_Early_Growth_Plant_N_Conc;
    pCropState->Top_N_Mass = Initial_Biomass * pCropParameters->Max_Early_Growth_Plant_N_Conc;
    pCropState->Top_N_Mass_Yesterday = pCropState->Top_N_Mass;                   //150529LML
    pCropState->Top_N_Mass_At_Emergence = pCropState->Top_N_Mass;
    pCropState->Cumulative_Top_N_Mass = pCropState->Top_N_Mass;
    pCropState->Cumulative_Root_N_Mass = pCropState->Root_N_Mass;
    pCropState->Top_Nitrogen_Stress_Factor = 1;
    pCropState->Top_Nitrogen_Stress_Index = 0;
    pCropState->Cumulative_Nitrogen_Uptake = 0;
    pCropState->Cumulative_Water_Stress_Index = 0;
    pCropState->Cumulative_Root_Nitrogen_Stress_Index = 0;
    pCropState->Cumulative_Top_Nitrogen_Stress_Index = 0;
}
//_____________________________________________________________________________/
void clsCrop::initialize(clsSimulation &Simulation, WeatherStateDailyClass &Weather, clsSoil &Soil)
{
    std::string crop_name = Simulation.pSimulationRotation->getCurrentCropName();
    int crop_parameter_id = ControlRef.pCrop_Parameter_Collection->FindInnerID(crop_name);
    if (crop_parameter_id < 0) {
        char errormessage[200];
        sprintf(errormessage,"Can't find crop parameter file %s!",crop_name.c_str());
        nrerror(errormessage);
    }
    pCropParameters = &(ControlRef.pCrop_Parameter_Collection->parrCropParameter[crop_parameter_id]);
    pCanopyCover->pCropParameters = pCropParameters;                             //150601
    pCropState->Crop_Name = crop_name;
    pCropState->Year_Planting = Simulation.pTimeState->getToday().get_year();
    pCropState->DOY_Planting = Simulation.pTimeState->getToday().get_DOY();
    pCropState->Crop_Exist = true;                              //LML 140829 false;
    pCropState->Flowering = false;
    pCropState->Crop_Forming_Yield = false;
    pCropState->Mature = false;
    pCropState->Harvested = false;
    Simulation.pSimulationRotation->setCropSeasonStarted(false);
    Waiting_For_Emergence = true;
    Soil.pSoilState->Total_Nitrate_N_Mass_At_Planting = Soil.pSoilState->Total_Nitrate_N_Mass;
    Soil.pSoilState->Total_Ammonium_N_Mass_At_Planting = Soil.pSoilState->Total_Ammonium_N_Mass;
    Soil.pSoilState->Cumulative_Nitrate_N_Fertilization_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Ammonium_N_Fertilization_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Nitrate_N_Fertigation_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Ammonium_N_Fertigation_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Profile_OM_Mineralization_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Profile_Residue_Mineralization_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Profile_Nitrogen_Immobilization_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Nitrate_Leaching_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Ammonium_Leaching_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Ammonia_N_Mass_Volatilization_Since_Planting = 0.;
    Soil.pSoilState->Cumulative_Profile_Denitrification_Since_Planting = 0.;
    //For perennials, assume that the simulation starts when the crop is dormant
    if (pCropParameters->Perennial_Crop) {
        Simulation.pSimulationRotation->setCropSeasonStarted(false);
        pCropState->Harvested = false;
        pCropState->Crop_Dormant = true;
        pCropState->Dormancy_Broken = false;
        pCropState->First_Day_Of_Dormancy = true;
        if (pCropParameters->Tree_Fruit_Crop) {
            pCropState->Chill_Requirement_Satisfied = false;
            Weather.setAccumulateChillHours(true);
        }
    }
}
//_____________________________________________________________________________/
void clsCrop::PerformDailyProcesses(clsSoil &Soil, 
  WeatherStateDailyClass &Weather,clsSimulation &Simulation,clsManagement &Management)
{
    int DACE = Simulation.pTimeState->getDaysAfterCropExists();
    pCropState->Current_Year =  Simulation.pTimeState->getToday().get_year();
    pCropState->Current_DOY = Simulation.pTimeState->getToday().get_DOY();
    //Initialize crop at planting
    if (DACE == 0) {
        initialize(Simulation, Weather,Soil);
    }
    //Calculate crop development for actual crop
    pCropDevelopment->UpdateDevelopment(Weather, Simulation, Management,*pCropParameters);
    if (Simulation.pSimulationRotation->getCropSeasonStarted() == true) { //Beginning of calculate growing season processes (crop has emerged or out of dormancy)
        if (Waiting_For_Emergence) {   //(XXXOJO or waiting for budbreak or first day of growth)
            //Set crop state at the beginning of growing season
            StartCrop(Simulation, Soil);
            Waiting_For_Emergence = false;
        } else {
            //Calculate growing season processes
            DetermineCO2Response(Weather);
            //Calculate potential crop processes as reference
            PerformPotentialProcesses(Simulation, Weather);
            //Calculate fraction of intercepted irradiance
            pCanopyCover->DetermineActualCover(/*150601 *pCropParameters*/);
            //Calculate potential transpiration of actual crop
            pPotTransp->DeterminePotentialTranspiration(false, Weather, *pCropParameters);
            //Calculate attainable biomass growth
            pBiomass->DeterminePotentialGrowth(false, Weather, Simulation,*pCropParameters);
            //Calculate root growth
            pRoot->DetermineRootGrowth(false, Soil, *pCropParameters);
            if (/*150630RLN ControlRef.*/today.get_DOY()==90) {
                int debug = 1;
            }
            //Calculate water uptake (transpiration)
            if (pCropState->Fraction_Solar_Rad_Intercepted_Green_Canopy > 0) {
                pWatUpt->PerformWaterUptake(Soil, *pCropParameters);
            } else {
                pCropState->Actual_Crop_Transpiration = 0;
                //pCropState->CumulativeActualCropTranspiration(DACE) = pCropState->CumulativeActualCropTranspiration(DACE - 1);
            }
            //Calculate water limited growth (apply water stress effect if (any)
            pBiomass->DetermineWaterLimitedBiomassGrowth();
            //Calculate potential nitrogen uptake
            if (pCropState->Fraction_Solar_Rad_Intercepted_Green_Canopy > 0) {
                pCropSoluteUptake->PotentialNitrogenUptake(Soil, *pCropParameters);
            }
            //Calculate crop nitrogen demand and actual uptake
            //XXXXXXX OJO CHECK AT FLOWERING BOOLEAN
            pCropNitrogenUptake->PlantNProcesses(Simulation, Soil,*pCropParameters);  //XXXXXXX CHECK AT FLOWERING BOOLEAN
            //Extract nitrogen from soil
            Soil.pSoilState->UpdateSoilSoluteStateAfterUptake();
            //Calculate actual biomass growth
            pBiomass->DetermineActualBiomassGrowth(*pCropParameters);
            //Search for clipping events for perennial biomass crops
            if (pCropParameters->Perennial_Crop && !pCropParameters->Tree_Fruit_Crop) {
                Management.FindAndApplyClippingEvent(*this);
            }
            pBiomass->DetermineBiosynthesisAndMaintenanceRespiration(Weather,*pCanopyCover,Soil,*pCropParameters);   //FMS Jun 27, 2014
            //Cumulate soil state for growth season output M.Liu Feb. 8, 2014
            Soil.pSoilState->Cumulative_Nitrate_N_Fertilization_Since_Planting          += Soil.pSoilState->Daily_Nitrate_N_Fertilization;
            Soil.pSoilState->Cumulative_Ammonium_N_Fertilization_Since_Planting         += Soil.pSoilState->Daily_Ammonium_N_Fertilization;
            Soil.pSoilState->Cumulative_Nitrate_N_Fertigation_Since_Planting            += Soil.pSoilState->Daily_Nitrate_N_Fertigation;
            Soil.pSoilState->Cumulative_Ammonium_N_Fertigation_Since_Planting           += Soil.pSoilState->Daily_Ammonium_N_Fertigation;
            Soil.pSoilState->Cumulative_Profile_OM_Mineralization_Since_Planting        += Soil.pSoilState->Profile_OM_Mineralization;
            Soil.pSoilState->Cumulative_Profile_Residue_Mineralization_Since_Planting   += Soil.pSoilState->Profile_Residue_Mineralization;
            Soil.pSoilState->Cumulative_Profile_Nitrogen_Immobilization_Since_Planting  += Soil.pSoilState->Profile_Nitrate_Immobilization;
            Soil.pSoilState->Cumulative_Nitrate_Leaching_Since_Planting                 += Soil.pSoilState->Daily_Nitrate_Leaching;
            Soil.pSoilState->Cumulative_Ammonium_Leaching_Since_Planting                += Soil.pSoilState->Daily_Ammonium_Leaching;
            Soil.pSoilState->Cumulative_Ammonia_N_Mass_Volatilization_Since_Planting    += Soil.pSoilState->Ammonia_N_Mass_Volatilization;
            Soil.pSoilState->Cumulative_Profile_Denitrification_Since_Planting          += Soil.pSoilState->Profile_Denitrification;

            pCropState->Yesterday_Water_Stress_Factor = pCropState->Water_Stress_Factor; //150529
            pCropState->Yesterday_Water_Stress_Index  = pCropState->Water_Stress_Index;  //150529
        }
    }//End of calculate growing season processes
    if (!pCropParameters->Perennial_Crop && pCropState->Mature && Simulation.pTimeState->getDaysAfterPhysiologicalMaturity() == 1) {
            //Calculate Soil water profile at the end of the growing season
        pCropState->Final_Soil_Profile_Water = Simulation.pBalance->CalculateSoilWaterProfile_mm();
        //M.Liu moved here for calculating N balance Feb.8, 2014
        //Need check why not calculating N balance in the harvest event
        //LML 140904 if (ControlRef.bWrite_Growth_Season_Output) Simulation.pOutput->WriteGrowingSeasonOutput(Simulation,*this, Soil);
    }
    //Calculate yield, write outputs, and dispose crop at harvest for annual crops
    if (!pCropParameters->Perennial_Crop && pCropState->Harvested) {
        //Calculate yield
        DetermineAnnualCropYield();
        if (ControlRef.bWrite_Growth_Season_Output) 
            Simulation.pOutput->WriteGrowingSeasonOutput(*this, Soil);       //LML 140904 moved here
        //Calculate Soil water profile at the end of the growing season
        //pCropState->FinalSoilProfileWater = Balance.CalculateSoilWaterProfile(SoilState, TimeState, SoilParameters)
        //Write outputs
        //Calculate nitrogen harvest index
        CalculateCropNitrogenPartitioning(Simulation);      //FMS Jul 11, 2014
        Soil.pOrganicResidue->CropBiomassToResidue(Simulation,Management,*this);
        //Call Simulation.Output.WriteDailyGrowthOutputIntoWorksheet(Me, Soil) // FMS 8/27/2013
        //Clear TimeState and WeatherState crop-related properties
        SetHarvest(Simulation, Weather);
    }//End of calculate yield, write outputs, and dispose crop at harvest for annual crops
    //Calculate yield for tree fruit crops
    if (pCropParameters->Tree_Fruit_Crop && pCropState->Harvested) {
         DetermineTreeFruitYield();
    }//end of calculate yield for tree fruit crops
    //Write output for perennial crops at the onset of dormancy and calculate yield for clipped perennials (not fruit trees)
    if (pCropParameters->Perennial_Crop && pCropState->First_Day_Of_Dormancy) {
        //Calculate yield of clipped perennial biomass crops
        if (!pCropParameters->Tree_Fruit_Crop) {
            DetermineClippedYield();
        }
        //Calculate Soil water profile at the end of the growing season
        pCropState->Final_Soil_Profile_Water = Simulation.pBalance->CalculateSoilWaterProfile_mm();
        //Write outputs
        if (ControlRef.bWrite_Growth_Season_Output) Simulation.pOutput->WriteGrowingSeasonOutput(*this, Soil);
        if (ControlRef.bWrite_Growth_Daily_Output) Simulation.pOutput->WriteDailyGrowthOutput(Simulation,*this);
        //Call Simulation.Output.WriteDailyGrowthOutputIntoWorksheet(Me, Soil) // FMS 8/27/2013
    }//End of write output for perennial crops at the onset of dormancy
    //Calculate accumulation of chill hours for fruit trees
    if (pCropParameters->Tree_Fruit_Crop && Weather.getAccumulateChillHours()) {
        Weather.ProvideChillHours();
        if (Weather.getAccumulateChillHours() >= pCropParameters->Required_Chill_Hours) {
            pCropState->Chill_Requirement_Satisfied = true;
            pCropState->First_Day_Chill_Requirement_Satisfied = true;
            Weather.setAccumulateChillHours(false);
        }
    }//End of calculate accumulation of chill hours for fruit trees
    Simulation.pTimeState->setDaysAfterCropExists(Simulation.pTimeState->getDaysAfterCropExists() + 1);
    DetermineCropCover(Soil);               //FMS Aug 26, 2014
    if (!pCropParameters->Perennial_Crop && pCropState->Harvested) {
        SetHarvest(Simulation, Weather);    //M.Liu moved here!
    }
}
//_____________________________________________________________________________/
void clsCrop::NewCrop(clsSimulation &Simulation)
{
    Simulation.pTimeState->setDaysAfterCropExists(0);
    Simulation.pTimeState->setDaysAfterPlanting(0);             //LML 140829
    Simulation.pSimulationRotation->setNewCropFound(false);
    pCropState->Crop_Emerged = false;
    pCropState->Dormancy_Broken = false;
    pCanopyCover->setFirst(false);  //LML 140903
}
//_____________________________________________________________________________/
clsCrop::~clsCrop()
{
#ifdef Destruct_Monitor
    std::cout<<"~clsCrop:"<<std::endl;
#endif
    delete pCropSoluteUptake;
    delete pCropNitrogenUptake;
    delete pWatUpt;
    delete pBiomass;
    delete pPotTransp;
    delete pCropDevelopment;
    delete pRoot;
    delete pCanopyCover;
    delete pCropState;

#ifdef Destruct_Monitor
    std::cout<<"~clsCrop done."<<std::endl;
#endif
}
//_____________________________________________________________________________/
void clsCrop::ClearStateForNextCropSeason()
{
    //Implement later M.Liu Feb 12, 2014
    pCropState->ClearStateAndFluxes();
}
//_____________________________________________________________________________/
void clsCrop::CalculateCropNitrogenPartitioning(clsSimulation &Simulation)
{
    //int DAP_At_Maturity = pCropState->Days_After_Crop_Exist_At_Maturity;
    double Maximum_Grain_Nitrogen_Concentration = Simulation.pSimConstants->Maximum_Grain_Nitrogen_Concentration;
    double Minimum_Grain_Nitrogen_Concentration = Simulation.pSimConstants->Minimum_Grain_Nitrogen_Concentration;
    double Maximum_Straw_Nitrogen_Concentration = Simulation.pSimConstants->Maximum_Straw_Nitrogen_Concentration;
    double Minimum_Straw_Nitrogen_Concentration = Simulation.pSimConstants->Minimum_Straw_Nitrogen_Concentration;
    double Nitrogen_Power_Coefficient = pCropParameters->Grain_N_Coefficient;
    double Crop_Yield = pCropState->Yield;
    double Cumulative_Biomass = pCropState->Cumulative_Biomass;
    double Straw_Biomass = Cumulative_Biomass - Crop_Yield;
    double Top_N_Concentration = pCropState->Top_Crop_N_Concentration;
    double Top_N_Mass = Top_N_Concentration * Cumulative_Biomass;
    double Maximum_Grain_Nitrogen_Mass = Crop_Yield * Maximum_Grain_Nitrogen_Concentration;
    double Minimum_Grain_Nitrogen_Mass = Crop_Yield * Minimum_Grain_Nitrogen_Concentration;
    double Maximum_Straw_Nitrogen_Mass = Straw_Biomass * Maximum_Straw_Nitrogen_Concentration;
    double Minimum_Straw_Nitrogen_Mass = Straw_Biomass * Minimum_Straw_Nitrogen_Concentration;
    double Maximum_Top_N_Mass = Maximum_Grain_Nitrogen_Mass + Maximum_Straw_Nitrogen_Mass;
    double Minimum_Top_N_Mass = Minimum_Grain_Nitrogen_Mass + Minimum_Straw_Nitrogen_Mass;
    if (Top_N_Mass > Maximum_Top_N_Mass) Top_N_Mass = Maximum_Top_N_Mass;
    double Nitrogen_Available_for_Distribution = Top_N_Mass - Minimum_Grain_Nitrogen_Mass - Minimum_Straw_Nitrogen_Mass;
    if (Nitrogen_Available_for_Distribution < 0) {
        double Crop_Yield = (Cumulative_Biomass * Minimum_Straw_Nitrogen_Concentration - Top_N_Mass)
                    / (Minimum_Straw_Nitrogen_Concentration - Minimum_Grain_Nitrogen_Concentration);
        pCropState->Yield = Crop_Yield;
        Straw_Biomass = Cumulative_Biomass - Crop_Yield;
        Nitrogen_Available_for_Distribution = 0;
    }
    double Grain_Nitrogen_Demand = Maximum_Grain_Nitrogen_Mass - Minimum_Grain_Nitrogen_Mass;
    double Straw_Nitrogen_Demand = Maximum_Straw_Nitrogen_Mass - Minimum_Straw_Nitrogen_Mass;
    double Partitioning_Power = pow((Nitrogen_Available_for_Distribution / (Maximum_Top_N_Mass - Minimum_Top_N_Mass)), Nitrogen_Power_Coefficient);
    double Grain_Partitioning_Coefficient = pow((Grain_Nitrogen_Demand / (Grain_Nitrogen_Demand + Straw_Nitrogen_Demand)), Partitioning_Power);
    if (Grain_Partitioning_Coefficient > 1) Grain_Partitioning_Coefficient = 1;
    double Grain_Nitrogen_Mass = Minimum_Grain_Nitrogen_Mass + Nitrogen_Available_for_Distribution * Grain_Partitioning_Coefficient;
    double Straw_Nitrogen_Mass = Top_N_Mass - Grain_Nitrogen_Mass;
    double Grain_Nitrogen_Concentration(0.0);
    if (!CORN::is_approximately<double>(Crop_Yield,0.0,1e-12)) 
        Grain_Nitrogen_Concentration = Grain_Nitrogen_Mass / Crop_Yield;
    double Straw_Nitrogen_Concentration = Straw_Nitrogen_Mass / Straw_Biomass;
    pCropState->Grain_Nitrogen_Concentration = Grain_Nitrogen_Concentration;
    pCropState->Straw_Nitrogen_Concentration = Straw_Nitrogen_Concentration;
}
//______________________________________________________________________________
void clsCrop::DetermineCropCover(clsSoil &Soil)
{
    Surface_Soil_Cover_Type CropCover(SSC_Default);
    if (pCropParameters->Perennial_Crop)
        CropCover = SSC_PerennialCrop;
    else if (pCropParameters->Tree_Fruit_Crop) {
        CropCover = SSC_Orchard;
    } else {
        if (pCropParameters->Maximum_Crop_Height < 0.9)
            CropCover = SSC_SmallCrop;
        else
            CropCover = SSC_TallCrop;
    }
    Soil.pSoilState->Surface_Soil_Cover = CropCover;
}
//______________________________________________________________________________

