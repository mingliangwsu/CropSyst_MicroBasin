#ifndef SOILORGANICCARBONCLASS_H
#define SOILORGANICCARBONCLASS_H
#include "soil/clssoil.h"
#include "control/clssimulation.h"

class clsSoil;
class clsSimulation;

class SoilOrganicCarbonClass
{
private:
    double NetNMineralization(double Carbon_Decomposed, double CN_Decomposing_Pool,
        double C_Fraction_Transferred_To_Pool_1, double CN_Pool_1,
        double C_Fraction_Transferred_To_Pool_2, double CN_Pool_2,
        double C_Fraction_Transferred_To_Pool_3, double CN_Pool_3);
    void MineralizationAndImmobilizationDemand(double &Nitrogen_Immobilization_Demand,
                double &SOM_Nitrogen_Mineralization,clsSimulation &Simulation);
    double PotentialCarbonDecomposition(int layer, double Pool_Carbon_Mass, double Carbon_Decomposition_Constant,
                clsSoil &Soil);
    void PotentialOrganicCarbonDecomposition(int layer, clsSimulation &Simulation, clsSoil &Soil);
public:
    //'DEFINITIONS:
    //'MB = Microbial biomass (kg/m2)
    //'Labile_SOM = Labile (fast cycling) active soil organic matter (kg/m2)
    //'Metastable_SOM = Metastable (slow cycling) active soil organic matter (kg/m2)
    //'Passive_SOM = Passive soil organic matter (kg/m2)
    /*double Initial_SOM_Carbon_Mass;             //(kgC/m2) After decomposition process, it is updated with Final ...
    double Initial_MB_C_Mass;                   //(kgC/m2)
    double Initial_Labile_SOM_C_Mass;           //(kgC/m2)
    double Initial_Metastable_SOM_C_Mass;       //(kgC/m2)
    double Initial_Passive_SOM_C_Mass;          //(kgC/m2)
    double Initial_SOM_Nitrogen_Mass;
    double Initial_MB_N_Mass;
    double Initial_Labile_SOM_N_Mass;
    double Initial_Metastable_SOM_N_Mass;
    double Initial_Passive_SOM_N_Mass;
    double Final_SOM_Carbon_Mass;
    double Final_MB_C_Mass;
    double Final_Labile_SOM_C_Mass;
    double Final_Metastable_SOM_C_Mass;
    double Final_Passive_SOM_C_Mass;
    double Final_SOM_Nitrogen_Mass;
    double Final_MB_N_Mass;
    double Final_Labile_SOM_N_Mass;
    double Final_Metastable_SOM_N_Mass;
    double Final_Passive_SOM_N_Mass;*/
    //LML 141010
    double SOM_Carbon_Mass;
    double MB_C_Mass;
    double Labile_SOM_C_Mass;
    double Metastable_SOM_C_Mass;
    double Passive_SOM_C_Mass;
    double SOM_Nitrogen_Mass;
    double MB_N_Mass;
    double Labile_SOM_N_Mass;
    double Metastable_SOM_N_Mass;
    double Passive_SOM_N_Mass;
    //end LML 141010
    double C_Fraction_From_Fast_Cycling_Residue_To_CO2; //'New
    double C_Fraction_From_Fast_Cycling_Residue_To_MB; //'New
    double C_Fraction_From_Slow_Cycling_Residue_To_CO2; //'New
    double C_Fraction_From_Slow_Cycling_Residue_To_MB; //'New
    double C_Fraction_From_Lignified_Residue_To_CO2; //'New
    double C_Fraction_From_Lignified_Residue_To_Metastable_SOM; //'New
    double C_Fraction_From_MB_To_Labile_SOM;
    double C_Fraction_From_MB_To_Metastable_SOM;
    double C_Fraction_From_Labile_SOM_To_CO2;
    double C_Fraction_From_Labile_SOM_To_MB;
    double C_Fraction_From_Labile_SOM_To_Passive_SOM;
    double C_Fraction_From_Metastable_SOM_To_CO2;
    double C_Fraction_From_Metastable_SOM_To_MB;
    double C_Fraction_From_Metastable_SOM_To_Passive_SOM;
    double C_Fraction_From_Passive_SOM_To_CO2;
    double C_Fraction_From_Passive_SOM_To_MB;
    double Potential_C_Decomposition_MB;
    double Potential_C_Decomposition_Labile_SOM;
    double Potential_C_Decomposition_Metastable_SOM;
    double Potential_C_Decomposition_Passive_SOM;
    double Local_SOM_Nitrogen_Mineralization;
    double Net_Mineralization_MB;
    double Net_Mineralization_Labile_SOM;
    double Net_Mineralization_Metastable_SOM;
    double Net_Mineralization_Passive_SOM;
    double Decomposed_MB;                       //(kgC/m2)
    double Decomposed_Labile_SOM;               //(kgC/m2)
    double Decomposed_Metastable_SOM;           //(kgC/m2)
    double Decomposed_Passive_SOM;              //(kgC/m2)
public:
    SoilOrganicCarbonClass();
    void ActualCarbonDecomposition(double Decomposition_Reduction_Factor, double &Actual_Carbon_Mass_Decomposed);
    void CarbonTransferAndSOMPoolsUpdate(int layer, double &Soil_Organic_Matter_CO2_Loss,
                double &C_Transfer_From_Residue_To_CO2, double Decomposed_Fast_Cycling_Organic_Residue_Carbon,
                double Decomposed_Slow_Cycling_Organic_Residue_Carbon,
                double Decomposed_Lignified_Organic_Residue_Carbon, clsSimulation &Simulation, clsSoil &Soil);
    void PotentialDecompositionAndMineralization(int layer, double &Nitrogen_Immobilization_Demand,
                double &SOM_Nitrogen_Mineralization, clsSimulation &Simulation, clsSoil &Soil);
    void initialize(int layer, clsSoil &Soil,clsSimulation &Simulation);
    //void test(int layer,clsSoil &Soil, clsSimulation &Simulation);
};

#endif // SOILORGANICCARBONCLASS_H
