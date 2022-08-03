#include "organicresiduepoolclass.h"
#include "util/constants.h"
#include "util/pubtools.h"

OrganicResiduePoolClass::OrganicResiduePoolClass()
{
}
//______________________________________________________________________________
void OrganicResiduePoolClass::initialize(int Pos, double Mass, double Decomposition_Rate_Constant,
  double C_Fraction, double C_To_N_Ratio, double Area_To_Mass,
  double Standing_Stubble_Contact_Fraction, double Surface_Residue_Contact_Fraction)
{
    Position = Pos;
    Residue_Mass = Mass;
    Initial_Residue_Mass = Mass;
    Decomposition_Constant = Decomposition_Rate_Constant;
    Carbon_Fraction = C_Fraction;
    CN_Ratio = C_To_N_Ratio;
    Area_To_Mass_Ratio = Area_To_Mass;
    Carbon_Mass_In_Organic_Residue = Residue_Mass * Carbon_Fraction;
    Nitrogen_Mass_In_Organic_Residue = Carbon_Mass_In_Organic_Residue / CN_Ratio;
    if (Position == -1) Contact_Fraction = Standing_Stubble_Contact_Fraction;
    else if (Position == 0) Contact_Fraction = Surface_Residue_Contact_Fraction;
    else Contact_Fraction = 1;
}
//______________________________________________________________________________
void OrganicResiduePoolClass::PotentialDecompositionAndImmobilization(int Index,double Organic_Residue_CN_Ratio,
                                            clsSimulation &Simulation, clsSoil &Soil)
{
    //Calculate potential carbon decomposition
    int layer(0);
    if (Position > 0) layer = Position;
    else layer = 1;
    Potential_Residue_Carbon_Decomposition = PotentialCarbonDecomposition(layer, Soil);
    double Receiving_Pool_CN_Ratio(0.0);
    double C_Fraction_To_Receving_Pool(0.0);
    //Calculate nitrogen immobilization demand
    if (Index >= 1 && Index <= 60) {  //Indices 1 to 60 are reserved for slow cycling materials
            Receiving_Pool_CN_Ratio = Simulation.pSimConstants->Microbial_Biomass_CN_Ratio;
            C_Fraction_To_Receving_Pool = 
                (1 - Simulation.pSimConstants->C_Fraction_From_Slow_Cycling_Residue_To_CO2);
    } else if (Index >= 61 && Index <= 120) {   //Indices 61 to 120 are reserved for lignified materials
            Receiving_Pool_CN_Ratio = 
                Simulation.pSimConstants->Metastable_Active_SOM_CN_Ratio;
            C_Fraction_To_Receving_Pool = 
                (1 - Simulation.pSimConstants->C_Fraction_From_Lignified_Residue_To_CO2);
    } else {   //Fast cycling pools
            Receiving_Pool_CN_Ratio = Simulation.pSimConstants->Microbial_Biomass_CN_Ratio;
            C_Fraction_To_Receving_Pool = 
                (1 - Simulation.pSimConstants->C_Fraction_From_Fast_Cycling_Residue_To_CO2);
    }
    //Uses the same equation applied for SOM mineralization, but with a negative sign (i.e., negative quantities -> no immobilization requirement
    //M.Liu added a case for CN_Ratio = 0
    double Nitrogen_Net_Mineralization(0.0);
    if (!CORN::is_approximately<double>(Organic_Residue_CN_Ratio,0.0,1e-12)) 
        Nitrogen_Net_Mineralization = 
            NetNitrogenMineralization(Potential_Residue_Carbon_Decomposition,
                                      Organic_Residue_CN_Ratio, 
                                      C_Fraction_To_Receving_Pool, 
                                      Receiving_Pool_CN_Ratio, 
                                      0, 
                                      1);
    else Nitrogen_Net_Mineralization = 0.;
    if (Nitrogen_Net_Mineralization > 0) {
        Nitrogen_Mineralization = Nitrogen_Net_Mineralization;
        Nitrogen_Immobilization_Demand = 0;
    } else {
        Nitrogen_Immobilization_Demand = -Nitrogen_Net_Mineralization;
        Nitrogen_Mineralization = 0;
    }
}
//______________________________________________________________________________
double OrganicResiduePoolClass::PotentialCarbonDecomposition(int layer,clsSoil &Soil)
{
    double Water_Filled_Porosity = Soil.pSoilState->get_liquid_water_content_volumetric(layer) 
                                   / Soil.pSoilProfile->get_saturation_water_content_volumetric(layer,0.0);
    double Moisture_Function = Soil.pAbioticFunctions->MoistureFunction(0.6, Water_Filled_Porosity);
    double Tillage_Decomposition_Rate_Adjustment_Factor = 
        Soil.pSoilState->Tillage_Decomposition_Adjustment_Factor[layer];
    double Temperature_Function(0.0);
    for (int hour = 0; hour < 24; hour++) {
        double Hourly_Temperature = Soil.pSoilState->Soil_Temperature[hour][layer];
        Temperature_Function += Soil.pAbioticFunctions->TemperatureFunction(Hourly_Temperature);
    }
    Temperature_Function /= 24.0;
    if (Position == 0) 
        Contact_Fraction = Soil.pOrganicResidueState->Surface_Residue_Contact_Fraction;
    double Potential_Carbon_Decomposition = 
        Carbon_Mass_In_Organic_Residue 
        * Contact_Fraction
        * Tillage_Decomposition_Rate_Adjustment_Factor 
        * (1.0 - exp(-Decomposition_Constant * Temperature_Function)) 
        * Moisture_Function;
    return Potential_Carbon_Decomposition;
}
//______________________________________________________________________________
double OrganicResiduePoolClass::NetNitrogenMineralization(double Carbon_Decomposed,double CN_Decomposing_Pool,
  double C_Fraction_Transferred_To_Pool_1,double CN_Pool_1,double C_Fraction_Transferred_To_Pool_2,double CN_Pool_2)
{
    double Net_Nitrogen_Mineralization = 
        (1.0 / CN_Decomposing_Pool - C_Fraction_Transferred_To_Pool_1 / CN_Pool_1
         - C_Fraction_Transferred_To_Pool_2 / CN_Pool_2) 
        * Carbon_Decomposed;
    return Net_Nitrogen_Mineralization;
}
//______________________________________________________________________________
void OrganicResiduePoolClass::ActualResidueDecomposition(clsSoil &Soil)
{
    double Decomposition_Reduction_Factor(0.0);
    if (Position > 1)
        Decomposition_Reduction_Factor = 
            Soil.pOrganicResidueState->Decomposition_Reduction_Factor[Position];
    else
        Decomposition_Reduction_Factor = 
            Soil.pOrganicResidueState->Decomposition_Reduction_Factor[1];
    Actual_Residue_Carbon_Decomposition = 
        Potential_Residue_Carbon_Decomposition * Decomposition_Reduction_Factor;
    Actual_Residue_Nitrogen_Decomposition = Actual_Residue_Carbon_Decomposition / CN_Ratio;
    Carbon_Mass_In_Organic_Residue -= Actual_Residue_Carbon_Decomposition;
    if (Carbon_Mass_In_Organic_Residue < 0.0000001) Carbon_Mass_In_Organic_Residue = 0;
    Nitrogen_Mass_In_Organic_Residue = Carbon_Mass_In_Organic_Residue / CN_Ratio;
    Residue_Mass = Carbon_Mass_In_Organic_Residue / Carbon_Fraction;
}

