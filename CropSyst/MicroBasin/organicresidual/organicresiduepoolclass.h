#ifndef ORGANICRESIDUEPOOLCLASS_H
#define ORGANICRESIDUEPOOLCLASS_H
#include "control/clssimulation.h"
#include "soil/clssoil.h"

class clsSoil;
class clsSimulation;
class OrganicResiduePoolClass
{
private:
    double PotentialCarbonDecomposition(int layer,clsSoil &Soil);
    double NetNitrogenMineralization(double Carbon_Decomposed,double CN_Decomposing_Pool,
                double C_Fraction_Transferred_To_Pool_1,double CN_Pool_1,double C_Fraction_Transferred_To_Pool_2,double CN_Pool_2);
public:
    double Potential_Residue_Carbon_Decomposition;
    double Actual_Residue_Carbon_Decomposition;
    double Contact_Fraction;
    double Carbon_Mass_In_Organic_Residue;
    double Actual_Residue_Nitrogen_Decomposition;
    double Nitrogen_Mass_In_Organic_Residue;
    double Nitrogen_Immobilization_Demand;
    double Nitrogen_Mineralization;
    int Position;   //-1: Standing_Stubble; 0:Surface_Residue other: Soil_Residue
    double Initial_Residue_Mass;
    double Residue_Mass;
    double Area_To_Mass_Ratio;
    double Decomposition_Constant;
    double Carbon_Fraction;
    double CN_Ratio;
    double N_Mass_Mineralized_From_Residues;
    double Ammonium_N_Mass_Immobilized;
    double Nitrate_N_Mass_Immobilized;
    double Carbon_Decomposed_Transferred_To_Organic_Matter;
    double Change_In_Organic_Matter_Content;
    double Nitrogen_Transferred_To_Organic_Matter;
    double Organic_Residue_Carbon_Loss_As_CO2;
    double Initial_Carbon_Mass_In_Organic_Residue;
    double Initial_Nitrogen_Mass_In_Organic_Residue;
    double Daily_Carbon_Transferred_To_OM;
    double Daily_CO2_Loss;
    double Daily_Ammonium_N_Mass_Immobilized;
    double Daily_Nitrate_N_Mass_Immobilized;
    double Daily_N_Mass_Mineralized;
    double Daily_Nitrogen_Transferred_To_OM;
public:
    OrganicResiduePoolClass();
    void initialize(int Pos, double Mass, double Decomposition_Rate_Constant,
                   double C_Fraction, double C_To_N_Ratio, double Area_To_Mass,
                    double Standing_Stubble_Contact_Fraction, double Surface_Residue_Contact_Fraction);
    void PotentialDecompositionAndImmobilization(int Index,double Organic_Residue_CN_Ratio,
                                                clsSimulation &Simulation, clsSoil &Soil);
    void ActualResidueDecomposition(clsSoil &Soil);
};

#endif // ORGANICRESIDUEPOOLCLASS_H
