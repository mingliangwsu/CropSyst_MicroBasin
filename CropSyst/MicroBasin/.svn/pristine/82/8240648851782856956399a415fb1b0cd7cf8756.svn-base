#ifndef ORGANICRESIDUESTATECLASS_H
#define ORGANICRESIDUESTATECLASS_H
#include "control/clssimulation.h"
#include <vector>
//class clsSimulation;
class OrganicResidueStateClass
{
public:
    //double *Standing_Stubble_Hourly_Temperature;    //(25);
    //double *Surface_Residues_Hourly_Temperature;    //(25);
    bool b_set_vector_size; //LML 150205
    double Standing_Stubble_Daily_Water_Evaporation;
    double Surface_Residues_Daily_Water_Evaporation;
    double Standing_Stubble_Mass;
    double Surface_Residue_Mass;
    double Total_Top_Residue_Mass;
    std::vector<double> Residue_Nitrogen_Immobilization_Demand;  //(30);
    std::vector<double> Residue_Nitrogen_Mineralization;  //(30);
    std::vector<double> Potential_Residue_Carbon_Decomposition;  //(30);
    std::vector<double> Potential_Fast_Cycling_Residue_Carbon_Decomposition;  //(30);
    std::vector<double> Potential_Slow_Cycling_Residue_Carbon_Decomposition;  //(30);
    std::vector<double> Potential_Lignified_Residue_Carbon_Decomposition;  //(30);
    double Potential_Standing_Stubble_Carbon_Decomposition;
    double Standing_Stubble_Nitrogen_Immobilization_Demand;
    double Standing_Stubble_Contact_Fraction;
    double Surface_Residue_Contact_Fraction;
    double Standing_Residue_Ground_Cover;
    double Surface_Residue_Ground_Cover;
    double Surface_Residue_Area_Index;
    double Standing_Residue_Area_Index;
    double Potential_Fast_Cycling_Standing_Stubble_Carbon_Decomposition;
    double Potential_Slow_Cycling_Standing_Stubble_Carbon_Decomposition;
    double Potential_Lignified_Standing_Stubble_Carbon_Decomposition;
    double Potential_Fast_Cycling_Surface_Residue_Carbon_Decomposition;
    double Potential_Slow_Cycling_Surface_Residue_Carbon_Decomposition;
    double Potential_Lignified_Surface_Residue_Carbon_Decomposition;
    // 'OJO Fidel add change of variable (delete matriz)
    std::vector<double> Decomposition_Reduction_Factor; //(30);
    double Standing_Stubble_Carbon_Mass;
    double Surface_Residue_Carbon_Mass;
    double Soil_Residue_Carbon_Mass;
    double Standing_Stubble_Nitrogen_Mass;
    double Surface_Residue_Nitrogen_Mass;
    double Soil_Residue_Nitrogen_Mass;
    double New_Standing_Stubble_Carbon_Mass;
    double New_Surface_Residue_Carbon_Mass;
    double New_Soil_Residue_Carbon_Mass;
    double New_Standing_Stubble_Nitrogen_Mass;
    double New_Surface_Residue_Nitrogen_Mass;
    double New_Soil_Residue_Nitrogen_Mass;
    double Decomposed_Standing_Stubble_Carbon_Mass;
    double Decomposed_Surface_Residue_Carbon_Mass;
    double Decomposed_Soil_Residue_Carbon_Mass;
    double Decomposed_Standing_Stubble_Nitrogen_Mass;
    double Decomposed_Surface_Residue_Nitrogen_Mass;
    double Decomposed_Soil_Residue_Nitrogen_Mass;
    double Cumulative_Decomposed_Standing_Stubble_Carbon_Mass;
    double Cumulative_Decomposed_Surface_Residue_Carbon_Mass;
    double Cumulative_Decomposed_Soil_Residue_Carbon_Mass;
    //'Fidel add new variables aug 21, 2013
    double LastDayOfYear_Standing_Stubble_Carbon_Mass;
    double LastDayOfYear_Surface_Residue_Carbon_Mass;
    double LastDayOfYear_Soil_Residue_Carbon_Mass;
    double LastDayOfYear_Standing_Stubble_Nitrogen_Mass;
    double LastDayOfYear_Surface_Residue_Nitrogen_Mass;
    double LastDayOfYear_Soil_Residue_Nitrogen_Mass;
    double LastDayOfYear_Decomposed_Standing_Stubble_Carbon_Mass;
    double LastDayOfYear_Decomposed_Surface_Residue_Carbon_Mass;
    double LastDayOfYear_Decomposed_Soil_Residue_Carbon_Mass;
    double LastDayOfYear_Decomposed_Standing_Stubble_Nitrogen_Mass;
    double LastDayOfYear_Decomposed_Surface_Residue_Nitrogen_Mass;
    double LastDayOfYear_Decomposed_Soil_Residue_Nitrogen_Mass;
    double LastDayOfYear_Cumulative_Decomposed_Standing_Stubble_Carbon_Mass;
    double LastDayOfYear_Cumulative_Decomposed_Surface_Residue_Carbon_Mass;
    double LastDayOfYear_Cumulative_Decomposed_Soil_Residue_Carbon_Mass;
    //'FMS 11/06/2013 add new variables
    double Cumulative_Final_Organic_Residue_Carbon_Mass;
    double Cumulative_Initial_Organic_Residue_Carbon_Mass;
    double Cumulative_New_Residue_Organic_Residue_Carbon_Mass;
    double Cumulative_Decomposed_Organic_Residue_Carbon_Mass;
    double Cumulative_Organic_Residue_Lost_As_CO2;
    //'FMS end added variables
public:
    OrganicResidueStateClass();
    ~OrganicResidueStateClass();

    void LastDayOfYearState(clsSimulation &Simulation);
};

#endif // ORGANICRESIDUESTATECLASS_H
