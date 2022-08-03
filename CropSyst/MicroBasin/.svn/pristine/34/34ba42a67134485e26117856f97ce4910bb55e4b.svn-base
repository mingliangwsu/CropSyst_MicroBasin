#include "soilorganiccarbonclass.h"
#include "util/pubtools.h"
#ifndef CROPSYST_VERSION
SoilOrganicCarbonClass::SoilOrganicCarbonClass()
{
}
//______________________________________________________________________________
void SoilOrganicCarbonClass::initialize(int layer, clsSoil &Soil, clsSimulation &Simulation)
{
    double Carbon_Fraction_In_Organic_Matter = 
            Simulation.pSimConstants->Carbon_Fraction_In_Organic_Matter;
    double Microbial_Biomass_CN_Ratio = Simulation.pSimConstants->Microbial_Biomass_CN_Ratio;
    double Labile_Active_SOM_CN_Ratio = Simulation.pSimConstants->Labile_Active_SOM_CN_Ratio;
    double Metastable_Active_SOM_CN_Ratio = 
            Simulation.pSimConstants->Metastable_Active_SOM_CN_Ratio;
    double Passive_SOM_CN_Ratio = Simulation.pSimConstants->Passive_SOM_CN_Ratio;
    double Organic_Matter_Content = Soil.pSoilState->Initial_OM[layer];
    //Convert from g/cm3 to kg/m3
    double Bulk_Density = Soil.pSoilProfile->get_bulk_density_g_cm3(layer) * 1000.0;
    double Layer_Thickness = Soil.pSoilProfile->get_thickness_m(layer);
    double Initial_C_Fraction_To_Microbial_Biomass = 
            Soil.pSoilState->Initial_C_Fraction_To_Microbial_Biomass[layer];
    double Initial_C_Fraction_To_Active_Labile_SOM = 
            Soil.pSoilState->Initial_C_Fraction_To_Active_Labile_SOM[layer];
    double Initial_C_Fraction_To_Active_Metastable_SOM = 
            Soil.pSoilState->Initial_C_Fraction_To_Active_Metastable_SOM[layer];
    double Initial_C_Fraction_To_Passive_SOM = 
            Soil.pSoilState->Initial_C_Fraction_To_Passive_SOM[layer];
    double  Soil_Organic_Carbon_Mass = (Organic_Matter_Content / 100.0)
                                       * Carbon_Fraction_In_Organic_Matter 
                                       * Bulk_Density 
                                       * Layer_Thickness;
    //Initialize C and N mass for each conceptual model pool (kg/m2)
    //Microbial biomass pool
    MB_C_Mass = Soil_Organic_Carbon_Mass * Initial_C_Fraction_To_Microbial_Biomass;
    MB_N_Mass = MB_C_Mass / Microbial_Biomass_CN_Ratio;
    //Labile Active SOM pool
    Labile_SOM_C_Mass = 
            Soil_Organic_Carbon_Mass * Initial_C_Fraction_To_Active_Labile_SOM;
    Labile_SOM_N_Mass = Labile_SOM_C_Mass / Labile_Active_SOM_CN_Ratio;
    //Protected slow SOM pool
    Metastable_SOM_C_Mass = 
            Soil_Organic_Carbon_Mass * Initial_C_Fraction_To_Active_Metastable_SOM;
    Metastable_SOM_N_Mass = Metastable_SOM_C_Mass / Metastable_Active_SOM_CN_Ratio;
    //Passive SOM pool
    Passive_SOM_C_Mass = Soil_Organic_Carbon_Mass * Initial_C_Fraction_To_Passive_SOM;
    Passive_SOM_N_Mass = Passive_SOM_C_Mass / Passive_SOM_CN_Ratio;
    double Soil_Organic_Nitrogen_Mass = MB_N_Mass 
                                        + Labile_SOM_N_Mass 
                                        + Metastable_SOM_N_Mass 
                                        + Passive_SOM_N_Mass;
    //Set transfer coefficients for each pool
    // XXXXX OJO (EYE!) REDUNDANT!
    C_Fraction_From_Fast_Cycling_Residue_To_CO2 = 0.6; //New
    C_Fraction_From_Fast_Cycling_Residue_To_MB = 1 - C_Fraction_From_Fast_Cycling_Residue_To_CO2; //New
    C_Fraction_From_Slow_Cycling_Residue_To_CO2 = 0.7; //New
    C_Fraction_From_Slow_Cycling_Residue_To_MB = 1 - C_Fraction_From_Slow_Cycling_Residue_To_CO2; //New
    C_Fraction_From_Lignified_Residue_To_CO2 = 0.3; //New
    C_Fraction_From_Lignified_Residue_To_Metastable_SOM = 1 - C_Fraction_From_Lignified_Residue_To_CO2; //New
    //Microbial biomass pool
    double Sand_Fraction = Soil.pSoilProfile->get_sand_percent(layer) / 100.0;
    //ROGER This must be recalculated after soil mixing
    double Alpha = 0.5 / (1 + pow(Sand_Fraction / 0.4, 3.0)); // original is 0.5 and /0.4
    C_Fraction_From_MB_To_Metastable_SOM = Alpha;
    C_Fraction_From_MB_To_Labile_SOM = (1 - Alpha);
    //Labile Active SOM pool
    C_Fraction_From_Labile_SOM_To_Passive_SOM = 0.004; 
    //0.00001 / Simulation.pSimConstants->LabileActiveSOMDecompositionConstant
    C_Fraction_From_Labile_SOM_To_CO2 = 0.75 * (1 - C_Fraction_From_Labile_SOM_To_Passive_SOM);
    C_Fraction_From_Labile_SOM_To_MB = 0.25 * (1 - C_Fraction_From_Labile_SOM_To_Passive_SOM);
    //Metastable Active SOM pool
    C_Fraction_From_Metastable_SOM_To_Passive_SOM = 0.03; 
    //0.00001 / Simulation.pSimConstants->MetastableActiveSOMDecompositionConstant
    C_Fraction_From_Metastable_SOM_To_CO2 = 0.8 * (1 - C_Fraction_From_Metastable_SOM_To_Passive_SOM);
    C_Fraction_From_Metastable_SOM_To_MB = 0.2 * (1 - C_Fraction_From_Metastable_SOM_To_Passive_SOM);
    //Passive SOM pool
    C_Fraction_From_Passive_SOM_To_CO2 = 0.8;
    C_Fraction_From_Passive_SOM_To_MB = 1 - C_Fraction_From_Passive_SOM_To_CO2;
    //Store state variables of interest
    Soil.pSoilState->Layer_Organic_Matter_Content[layer] = Organic_Matter_Content;
    Soil.pSoilState->Layer_Carbon_Mass_In_Organic_Matter[layer] = Soil_Organic_Carbon_Mass;
    Soil.pSoilState->Layer_Nitrogen_Mass_In_Organic_Matter[layer] = Soil_Organic_Nitrogen_Mass;
    //Store carbon pool state variables for transition between consecutive days
    SOM_Carbon_Mass = Soil_Organic_Carbon_Mass;
    //MB_C_Mass = MB_C_Mass;
    //Labile_SOM_C_Mass = Labile_SOM_C_Mass;
    //Metastable_SOM_C_Mass = Metastable_SOM_C_Mass;
    //Passive_SOM_C_Mass = Passive_SOM_C_Mass;
    SOM_Nitrogen_Mass = Soil_Organic_Nitrogen_Mass;
    //MB_N_Mass = MB_N_Mass;
    //Labile_SOM_N_Mass = Labile_SOM_N_Mass;
    //Metastable_SOM_N_Mass = Metastable_SOM_N_Mass;
    //Passive_SOM_N_Mass = Passive_SOM_N_Mass;

    //std::cout<<"finish Layer:"<<Layer<<std::endl;
}
//______________________________________________________________________________
void SoilOrganicCarbonClass::ActualCarbonDecomposition(double Decomposition_Reduction_Factor, 
  double &Actual_Carbon_Mass_Decomposed)
{
    //double Net_Mineralization_MB;
    //double Net_Mineralization_Labile_SOM;
    //double Net_Mineralization_Metastable_SOM;
    //double Net_Mineralization_Passive_SOM;
    //'MB = Microbial biomass
    if (Net_Mineralization_MB < 0)
        Decomposed_MB = Potential_C_Decomposition_MB * Decomposition_Reduction_Factor;
    else
        Decomposed_MB = Potential_C_Decomposition_MB;
    //'Labile_SOM = Labile Active SOM
    if (Net_Mineralization_Labile_SOM < 0)
        Decomposed_Labile_SOM = Potential_C_Decomposition_Labile_SOM * Decomposition_Reduction_Factor;
    else
        Decomposed_Labile_SOM = Potential_C_Decomposition_Labile_SOM;
    //'Metastable_SOM = Metastable Active SOM
    if (Net_Mineralization_Metastable_SOM < 0)
        Decomposed_Metastable_SOM = Potential_C_Decomposition_Metastable_SOM * Decomposition_Reduction_Factor;
    else
        Decomposed_Metastable_SOM = Potential_C_Decomposition_Metastable_SOM;
    //'Passive_SOM = Passive SOM
    if (Net_Mineralization_Passive_SOM < 0)
        Decomposed_Passive_SOM = Potential_C_Decomposition_Passive_SOM * Decomposition_Reduction_Factor;
    else
        Decomposed_Passive_SOM = Potential_C_Decomposition_Passive_SOM;
    Actual_Carbon_Mass_Decomposed = Decomposed_MB + Decomposed_Labile_SOM + Decomposed_Metastable_SOM + Decomposed_Passive_SOM;
}
//______________________________________________________________________________
void SoilOrganicCarbonClass::CarbonTransferAndSOMPoolsUpdate(int layer, double &Soil_Organic_Matter_CO2_Loss,
            double &C_Transfer_From_Residue_To_CO2, double Decomposed_Fast_Cycling_Organic_Residue_Carbon,
            double Decomposed_Slow_Cycling_Organic_Residue_Carbon,
            double Decomposed_Lignified_Organic_Residue_Carbon, clsSimulation &Simulation, clsSoil &Soil)
{
    //'Load C/N ratios
    double MB_CN_Ratio = Simulation.pSimConstants->Microbial_Biomass_CN_Ratio;
    double Labile_SOM_CN_Ratio = Simulation.pSimConstants->Labile_Active_SOM_CN_Ratio;
    double Metastable_SOM_CN_Ratio = Simulation.pSimConstants->Metastable_Active_SOM_CN_Ratio;
    double Passive_SOM_CN_Ratio = Simulation.pSimConstants->Passive_SOM_CN_Ratio;
    double C_Transfer_From_Fast_Cycling_Residue_To_CO2 = 
            Decomposed_Fast_Cycling_Organic_Residue_Carbon * C_Fraction_From_Fast_Cycling_Residue_To_CO2; //'New
    double C_Transfer_From_Fast_Cycling_Residue_To_MB = 
            Decomposed_Fast_Cycling_Organic_Residue_Carbon * C_Fraction_From_Fast_Cycling_Residue_To_MB; //'New
    double C_Transfer_From_Slow_Cycling_Residue_To_CO2 = 
            Decomposed_Slow_Cycling_Organic_Residue_Carbon * C_Fraction_From_Slow_Cycling_Residue_To_CO2; //'New
    double C_Transfer_From_Slow_Cycling_Residue_To_MB = 
            Decomposed_Slow_Cycling_Organic_Residue_Carbon * C_Fraction_From_Slow_Cycling_Residue_To_MB; //'New
    double C_Transfer_From_Lignified_Residue_To_CO2 = 
            Decomposed_Lignified_Organic_Residue_Carbon * C_Fraction_From_Lignified_Residue_To_CO2; //'New
    double C_Transfer_From_Lignified_Residue_To_Metastable_SOM = 
            Decomposed_Lignified_Organic_Residue_Carbon * C_Fraction_From_Lignified_Residue_To_Metastable_SOM; //'New
    //double C_Transfer_From_MB_To_CO2 = 0;
    double C_Transfer_From_MB_To_Labile_SOM = 
            Decomposed_MB * C_Fraction_From_MB_To_Labile_SOM;
    double C_Transfer_From_MB_To_Metastable_SOM = 
            Decomposed_MB * C_Fraction_From_MB_To_Metastable_SOM;
    //double C_Transfer_From_MB_To_Passive_SOM = 0;
    double C_Transfer_From_Labile_SOM_To_CO2 = 
            Decomposed_Labile_SOM * C_Fraction_From_Labile_SOM_To_CO2;
    double C_Transfer_From_Labile_SOM_To_MB = 
            Decomposed_Labile_SOM * C_Fraction_From_Labile_SOM_To_MB;
    double C_Transfer_From_Labile_SOM_To_Passive_SOM = 
            Decomposed_Labile_SOM * C_Fraction_From_Labile_SOM_To_Passive_SOM;
    double C_Transfer_From_Metastable_SOM_To_CO2 = 
            Decomposed_Metastable_SOM * C_Fraction_From_Metastable_SOM_To_CO2;
    double C_Transfer_From_Metastable_SOM_To_MB = 
            Decomposed_Metastable_SOM * C_Fraction_From_Metastable_SOM_To_MB;
    double C_Transfer_From_Metastable_SOM_To_Passive_SOM = 
            Decomposed_Metastable_SOM * C_Fraction_From_Metastable_SOM_To_Passive_SOM;
    double C_Transfer_From_Passive_SOM_To_CO2 = 
            Decomposed_Passive_SOM * C_Fraction_From_Passive_SOM_To_CO2;
    double C_Transfer_From_Passive_SOM_To_MB = 
            Decomposed_Passive_SOM * C_Fraction_From_Passive_SOM_To_MB;
    //'Calculate carbon mass of each pool after transformation
    //'MB = Microbial biomass
    double old_SOM_C = MB_C_Mass 
                       + Labile_SOM_C_Mass 
                       + Metastable_SOM_C_Mass 
                       + Passive_SOM_C_Mass;
    MB_C_Mass += C_Transfer_From_Fast_Cycling_Residue_To_MB
                 + C_Transfer_From_Slow_Cycling_Residue_To_MB 
                 + C_Transfer_From_Labile_SOM_To_MB 
                 + C_Transfer_From_Metastable_SOM_To_MB
                 + C_Transfer_From_Passive_SOM_To_MB 
                 - Decomposed_MB;
    //'Labile_SOM = Labile Active SOM
    Labile_SOM_C_Mass += C_Transfer_From_MB_To_Labile_SOM 
                         - C_Transfer_From_Labile_SOM_To_MB
                         - C_Transfer_From_Labile_SOM_To_Passive_SOM 
                         - C_Transfer_From_Labile_SOM_To_CO2;
    //'Metastable_SOM = Metastable Active SOM
    Metastable_SOM_C_Mass += C_Transfer_From_MB_To_Metastable_SOM
                             + C_Transfer_From_Lignified_Residue_To_Metastable_SOM
                             - C_Transfer_From_Metastable_SOM_To_MB 
                             - C_Transfer_From_Metastable_SOM_To_Passive_SOM
                             - C_Transfer_From_Metastable_SOM_To_CO2;
    //'Passive_SOM = Passive SOM
    Passive_SOM_C_Mass += C_Transfer_From_Labile_SOM_To_Passive_SOM
                          + C_Transfer_From_Metastable_SOM_To_Passive_SOM 
                          - C_Transfer_From_Passive_SOM_To_MB
                          - C_Transfer_From_Passive_SOM_To_CO2;
    C_Transfer_From_Residue_To_CO2 = C_Transfer_From_Fast_Cycling_Residue_To_CO2 
                                     + C_Transfer_From_Slow_Cycling_Residue_To_CO2
                                     + C_Transfer_From_Lignified_Residue_To_CO2;
    
    Soil_Organic_Matter_CO2_Loss = C_Transfer_From_Labile_SOM_To_CO2 
                                   + C_Transfer_From_Metastable_SOM_To_CO2
                                   + C_Transfer_From_Passive_SOM_To_CO2;
    SOM_Carbon_Mass = MB_C_Mass 
                      + Labile_SOM_C_Mass 
                      + Metastable_SOM_C_Mass 
                      + Passive_SOM_C_Mass;
    double new_SOM_C = SOM_Carbon_Mass;
    //'Calculate organic nitrogen in all pools at the end of the time step
    double old_SOM_N = MB_N_Mass 
                       + Labile_SOM_N_Mass 
                       + Metastable_SOM_N_Mass 
                       + Passive_SOM_N_Mass;
    MB_N_Mass = MB_C_Mass / MB_CN_Ratio;
    Labile_SOM_N_Mass = Labile_SOM_C_Mass / Labile_SOM_CN_Ratio;
    Metastable_SOM_N_Mass = Metastable_SOM_C_Mass / Metastable_SOM_CN_Ratio;
    Passive_SOM_N_Mass = Passive_SOM_C_Mass / Passive_SOM_CN_Ratio;
    SOM_Nitrogen_Mass = MB_N_Mass 
                        + Labile_SOM_N_Mass
                        + Metastable_SOM_N_Mass 
                        + Passive_SOM_N_Mass;
    double new_SOM_N = SOM_Nitrogen_Mass;
    // 'Calculate new organic matter content (%)
    double Carbon_Fraction_In_Organic_Matter = 
            Simulation.pSimConstants->Carbon_Fraction_In_Organic_Matter;
    //'Convert from g/cm3 to kg/m3
    double Bulk_Density = Soil.pSoilProfile->get_bulk_density_g_cm3(layer) * 1000.0;
    double Layer_Thickness = Soil.pSoilProfile->get_thickness_m(layer);
    double Organic_Matter_Content = 
            (SOM_Carbon_Mass * 100.0) 
            / (Carbon_Fraction_In_Organic_Matter * Bulk_Density * Layer_Thickness);
    double C_Transfer_From_Residue_To_SOM = C_Transfer_From_Fast_Cycling_Residue_To_MB
                                            + C_Transfer_From_Slow_Cycling_Residue_To_MB
                                            + C_Transfer_From_Lignified_Residue_To_Metastable_SOM;
    double N_Transfer_From_Residue_To_SOM = C_Transfer_From_Fast_Cycling_Residue_To_MB / MB_CN_Ratio
                                            + C_Transfer_From_Slow_Cycling_Residue_To_MB / MB_CN_Ratio
                                            + C_Transfer_From_Lignified_Residue_To_Metastable_SOM / Metastable_SOM_CN_Ratio;
    double Carbon_Balance = new_SOM_C 
                            - old_SOM_C 
                            - C_Transfer_From_Fast_Cycling_Residue_To_MB
                            - C_Transfer_From_Slow_Cycling_Residue_To_MB 
                            - C_Transfer_From_Lignified_Residue_To_Metastable_SOM 
                            + Soil_Organic_Matter_CO2_Loss;
    double Nitrogen_Balance = new_SOM_N 
                              - old_SOM_N 
                              - C_Transfer_From_Fast_Cycling_Residue_To_MB / MB_CN_Ratio
                              - C_Transfer_From_Slow_Cycling_Residue_To_MB / MB_CN_Ratio 
                              - C_Transfer_From_Lignified_Residue_To_Metastable_SOM / Metastable_SOM_CN_Ratio
                              + Local_SOM_Nitrogen_Mineralization;
    //' Update soil layer state variables
    Soil.pSoilState->Layer_Carbon_Mass_In_Organic_Matter[layer] = SOM_Carbon_Mass;
    Soil.pSoilState->Layer_Nitrogen_Mass_In_Organic_Matter[layer] = SOM_Nitrogen_Mass;
    Soil.pSoilState->Layer_Carbon_Transfer_From_Residue_To_SOM[layer] = C_Transfer_From_Residue_To_SOM;
    Soil.pSoilState->Layer_Nitrogen_Transfer_From_Residue_To_SOM[layer] = N_Transfer_From_Residue_To_SOM;
    Soil.pSoilState->Layer_Mineralized_N_Mass_From_Organic_Matter[layer] = Local_SOM_Nitrogen_Mineralization;
    Soil.pSoilState->Layer_SOM_CO2_Loss[layer] = Soil_Organic_Matter_CO2_Loss;
    Soil.pSoilState->Layer_Residue_CO2_Loss[layer] = C_Transfer_From_Residue_To_CO2;
    Soil.pSoilState->Layer_Total_CO2_Loss[layer] = C_Transfer_From_Residue_To_CO2 + Soil_Organic_Matter_CO2_Loss;
    Soil.pSoilState->Layer_SOM_C_Balance[layer] = Carbon_Balance;
    Soil.pSoilState->Layer_SOM_N_Balance[layer] = Nitrogen_Balance;
    Soil.pSoilState->Layer_Organic_Matter_Content[layer] = Organic_Matter_Content;
    Soil.pSoilState->Profile_Carbon_Transferred_From_Residue_To_SOM += C_Transfer_From_Residue_To_SOM;
    Soil.pSoilState->Profile_Nitrogen_Transferred_From_Residue_To_SOM += N_Transfer_From_Residue_To_SOM;
}
//______________________________________________________________________________
double SoilOrganicCarbonClass::NetNMineralization(double Carbon_Decomposed, double CN_Decomposing_Pool,
    double C_Fraction_Transferred_To_Pool_1, double CN_Pool_1,
    double C_Fraction_Transferred_To_Pool_2, double CN_Pool_2,
    double C_Fraction_Transferred_To_Pool_3, double CN_Pool_3)
{
    double Net_N_Mineralization = (1.0 / CN_Decomposing_Pool 
                                   - C_Fraction_Transferred_To_Pool_1 / CN_Pool_1 
                                   - C_Fraction_Transferred_To_Pool_2 / CN_Pool_2
                                   - C_Fraction_Transferred_To_Pool_3 / CN_Pool_3
                                  ) * Carbon_Decomposed;
    return Net_N_Mineralization;
}
//______________________________________________________________________________
void SoilOrganicCarbonClass::MineralizationAndImmobilizationDemand(double &Nitrogen_Immobilization_Demand,
               double &SOM_Nitrogen_Mineralization,clsSimulation &Simulation)
{
    double MB_CN_Ratio = Simulation.pSimConstants->Microbial_Biomass_CN_Ratio;
    double Labile_SOM_CN_Ratio = Simulation.pSimConstants->Labile_Active_SOM_CN_Ratio;
    double Metastable_SOM_CN_Ratio = Simulation.pSimConstants->Metastable_Active_SOM_CN_Ratio;
    double Passive_SOM_CN_Ratio = Simulation.pSimConstants->Passive_SOM_CN_Ratio;
    SOM_Nitrogen_Mineralization = 0;
    //'MB = Microbial biomass
    Net_Mineralization_MB = NetNMineralization(Potential_C_Decomposition_MB,
                                               MB_CN_Ratio, 
                                               C_Fraction_From_MB_To_Labile_SOM, 
                                               Labile_SOM_CN_Ratio,
                                               C_Fraction_From_MB_To_Metastable_SOM, 
                                               Metastable_SOM_CN_Ratio,
                                               0, 
                                               1);
    if (Net_Mineralization_MB < 0)
        Nitrogen_Immobilization_Demand = Nitrogen_Immobilization_Demand - Net_Mineralization_MB;
    else
        SOM_Nitrogen_Mineralization = SOM_Nitrogen_Mineralization + Net_Mineralization_MB;
    //'Labile_SOM = Labile Active SOM
    Net_Mineralization_Labile_SOM = NetNMineralization(Potential_C_Decomposition_Labile_SOM,
                                                       Labile_SOM_CN_Ratio, 
                                                       C_Fraction_From_Labile_SOM_To_MB, 
                                                       MB_CN_Ratio,
                                                       C_Fraction_From_Labile_SOM_To_Passive_SOM, 
                                                       Passive_SOM_CN_Ratio, 
                                                       0, 
                                                       1);
    if (Net_Mineralization_Labile_SOM < 0)
        Nitrogen_Immobilization_Demand -= Net_Mineralization_Labile_SOM;
    else
        SOM_Nitrogen_Mineralization += Net_Mineralization_Labile_SOM;
    //'Metastable_SOM = Metastable Active SOM
    Net_Mineralization_Metastable_SOM = NetNMineralization(Potential_C_Decomposition_Metastable_SOM,
                                                           Metastable_SOM_CN_Ratio, 
                                                           C_Fraction_From_Metastable_SOM_To_MB, 
                                                           MB_CN_Ratio,
                                                           C_Fraction_From_Metastable_SOM_To_Passive_SOM, 
                                                           Passive_SOM_CN_Ratio, 
                                                           0, 
                                                           1);
    if (Net_Mineralization_Metastable_SOM < 0)
        Nitrogen_Immobilization_Demand -= Net_Mineralization_Metastable_SOM;
    else
        SOM_Nitrogen_Mineralization += Net_Mineralization_Metastable_SOM;
    //'Passive_SOM = Passive SOM
    Net_Mineralization_Passive_SOM = NetNMineralization(Potential_C_Decomposition_Passive_SOM,
                                                        Passive_SOM_CN_Ratio, 
                                                        C_Fraction_From_Passive_SOM_To_MB, 
                                                        MB_CN_Ratio, 
                                                        0, 
                                                        1, 
                                                        0, 
                                                        1);
    if (Net_Mineralization_Passive_SOM < 0)
        Nitrogen_Immobilization_Demand -= Net_Mineralization_Passive_SOM;
    else
        SOM_Nitrogen_Mineralization += Net_Mineralization_Passive_SOM;
    Local_SOM_Nitrogen_Mineralization = SOM_Nitrogen_Mineralization;
}
//______________________________________________________________________________
double SoilOrganicCarbonClass::PotentialCarbonDecomposition(int layer, 
  double Pool_Carbon_Mass, double Carbon_Decomposition_Constant,
  clsSoil &Soil)
{
    double Tillage_Decomposition_Rate_Adjustment_Factor = 
            Soil.pSoilState->Tillage_Decomposition_Adjustment_Factor[layer];
    double Water_Filled_Porosity = Soil.pSoilState->get_liquid_water_content_volumetric(layer) 
            / Soil.pSoilProfile->get_saturation_water_content_volumetric(layer,0.0);    //Saturation_Water_Content[layer];
    double Moisture_Function = 
            Soil.pAbioticFunctions->MoistureFunction(0.6, Water_Filled_Porosity);
    double Term = 0;
    for (int hour = 0; hour < 24; hour++) {
        double Hourly_Temperature = Soil.pSoilState->Soil_Temperature[hour][layer];
        double Temperature_Function = 
                Soil.pAbioticFunctions->TemperatureFunction(Hourly_Temperature);
        double Minimum_Factor = 
                std::min<double>(Temperature_Function,Moisture_Function);
        Term += Minimum_Factor / 24.0;    //  '(1 - Exp(-(Carbon_Decomposition_Constant / 24) * Temperature_Function))
    }
    double Potential_Carbon_Decomposition = 
        Pool_Carbon_Mass * Term * Tillage_Decomposition_Rate_Adjustment_Factor * Carbon_Decomposition_Constant;
    return Potential_Carbon_Decomposition;
}
//______________________________________________________________________________
void SoilOrganicCarbonClass::PotentialDecompositionAndMineralization(int layer, 
  double &Nitrogen_Immobilization_Demand, double &SOM_Nitrogen_Mineralization, 
  clsSimulation &Simulation, clsSoil &Soil)
{
    //'Calculate potential decomposition for all pools
    PotentialOrganicCarbonDecomposition(layer, Simulation, Soil);
    //'Calculate net mineralization for all pools
    MineralizationAndImmobilizationDemand(Nitrogen_Immobilization_Demand, 
                                          SOM_Nitrogen_Mineralization, 
                                          Simulation);
}
//______________________________________________________________________________
void SoilOrganicCarbonClass::PotentialOrganicCarbonDecomposition(int layer, 
  clsSimulation &Simulation, clsSoil &Soil)
{
    double Microbial_Biomass_Decomposition_Constant = 
            Simulation.pSimConstants->Microbial_Biomass_Decomposition_Constant;// '1/d
    double Labile_Active_SOM_Decomposition_Constant = 
            Simulation.pSimConstants->Labile_Active_SOM_Decomposition_Constant;//  '1/d
    double Metastable_Active_SOM_Decomposition_Constant = 
            Simulation.pSimConstants->Metastable_Active_SOM_Decomposition_Constant;// '1/d
    double Passive_SOM_Decomposition_Constant = 
            Simulation.pSimConstants->Passive_SOM_Decomposition_Constant;//  '1/d
    //'MB = Microbial biomass
    Potential_C_Decomposition_MB = PotentialCarbonDecomposition(layer, MB_C_Mass,
        Microbial_Biomass_Decomposition_Constant, Soil);
    //'LabileSOM = Labile Active SOM
    Potential_C_Decomposition_Labile_SOM = PotentialCarbonDecomposition(layer, Labile_SOM_C_Mass,
        Labile_Active_SOM_Decomposition_Constant, Soil);
    //'MetastableSOM = Metastable Active SOM
    Potential_C_Decomposition_Metastable_SOM = 
            PotentialCarbonDecomposition(layer, 
                                         Metastable_SOM_C_Mass,
                                         Metastable_Active_SOM_Decomposition_Constant, 
                                         Soil);
    //'PassiveSOM = Passive SOM
    Potential_C_Decomposition_Passive_SOM = 
            PotentialCarbonDecomposition(layer, 
                                         Passive_SOM_C_Mass,
                                         Passive_SOM_Decomposition_Constant, 
                                         Soil);
}
//______________________________________________________________________________
#endif
