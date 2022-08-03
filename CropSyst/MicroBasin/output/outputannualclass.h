#ifndef OUTPUTANNUALCLASS_H
#define OUTPUTANNUALCLASS_H
#include "soil/soilprofileclass2.h"


class OutputAnnualClass
{
public:
    int Current_Year;
    double Nitrate_N_Fertilization;                 //(kg/ha)
    double Ammonium_N_Fertilization;                //(kg/ha)
    double Organic_N_Fertilization;                 //(kg/ha)
    //double Nitrate_N_Fertigation;                   //(kg/ha)
    //double Ammonium_N_Fertigation;                  //(kg/ha)
    double Nitrate_N_Leaching;                        //(kg/ha)
    double Ammonium_N_Leaching;                       //(kg/ha)
    //double Drainage;                                                           //(m)
    double Precipitation;                                                        //(m) 161101LML
    double Potential_ET;                                                         //(m)
    double Actual_ET;                                                            //(m)
    double Soil_Residue_Evap;                                                    //(m)
    double Transpiration;                                                        //(m)
    double Irrigation;                                                           //(m)
    double Drainage;                                                             //(m) 160404LML
    double Water_Balance;                           //(m)
    double Nitrate_Balance;
    double Ammonium_Balance;                        //(kg/ha)
    double Organic_Matter_Carbon_Balance;           //(kg/ha)
    double Organic_Matter_Nitrogen_Balance;         //(kg/ha)
    double Residue_Carbon_Balance;                  //(kg/ha)
    double Residue_Nitrogen_Balance;                //(kg/ha)
    double Profile_SOM_Carbon_Mass;                 //(kg/ha)
    double Profile_SOM_Nitrogen_Mass;                //(kg/ha)
    double Profile_NO3_Nitrogen_Mass;                                            //160115LML
    double Profile_NH4_Nitrogen_Mass;                                            //160115LML
    double Surface_NO3_N_Mass;                                                   //170510LML
    double Surface_NH4_N_Mass;                                                   //170510LML
    double Initial_Profile_NO3_N;                                              //(kgN/ha) 170413LML at the first day of year
    double Initial_Profile_NH4_N;                                              //(kgN/ha) 170413LML at the first day of year
    double Initial_Surface_NO3_N;                                              //(kgN/ha) 170510LML
    double Initial_Surface_NH4_N;                                              //(kgN/ha) 170510LML

    //150521 double Top5cm_SOM_Carbon_Mass;                  //(kg/ha)
    //150521 double Top30cm_Soil_Carbon_Mass;                //(kg/ha)
    double Profile_Residue_Carbon_Mass;             //(kg/ha)
    double Profile_Residue_Nitrogen_Mass;           //(kg/ha)
    double OM_Mineralization;                       //(kg/ha)
    double Residue_Mineralization;                  //(kg/ha)
    double N_Mineralization;
    double N_Immobilization;                        //(kg/ha)
    double Nitrification;                           //(kg/ha)
    double Denitrification;                         //(kg/ha)
    double Nuptake;                                 //(kg/ha)
    double N2O_Loss_denitrification;
    double N2O_Loss_nitrification;
    double N2O_Loss;                                //(kgN/ha)
    double Ammonia_N_Mass_Volatilization;           //(kg/ha)
    double Last_Day_Of_Year_Standing_Stubble_Carbon_Mass;                        //(kgC/ha)
    double Last_Day_Of_Year_Surface_Residue_Carbon_Mass;                         //(kgC/ha)
    double Last_Day_Of_Year_Total_Aboveground_Residue_Carbon_Mass;               //(kgC/ha) 160405LML
    double Last_Day_Of_Year_Total_Aboveground_Residue_Nitrogen_Mass;             //(kgN/ha) 160405LML
    double Last_Day_Of_Year_Soil_Residue_Carbon_Mass;       //(kg/ha)
    double Last_Day_Of_Year_Soil_Residue_Nitrogen_Mass;       //(kg/ha)
    double Last_Day_Of_Year_Cumulative_Decomposed_Standing_Stubble_Carbon_Mass;     //(kg/ha)
    double Last_Day_Of_Year_Cumulative_Decomposed_Surface_Residue_Carbon_Mass;      //(kg/ha)
    double Last_Day_Of_Year_Cumulative_Decomposed_Soil_Residue_Carbon_Mass;         //(kg/ha)
    double Last_Day_Of_Year_Layer_Water_Content[MAX_soil_layers_alloc];
    double Last_Day_Of_Year_Layer_Ice_Content[MAX_soil_layers_alloc];
    double Last_Day_Of_Year_Layer_Nitrate_N_Mass[MAX_soil_layers_alloc];                          //(kg/ha)
    double Last_Day_Of_Year_Layer_Ammonium_N_Mass[MAX_soil_layers_alloc];                         //(kg/ha)
    double SOM_Carbon_Lost_As_CO2;                  //(kg/ha)
    double Residue_Carbon_Lost_As_CO2;              //(kg/ha)
    double plant_Carbon_Mass_Canopy;
    double plant_Carbon_Mass_Root;
    double Surface_Runon_m3;
    double Lateral_Runon_m3;
    double Total_Runon_m3;
    double Surface_Runon_NO3_kgN_ha;
    double Surface_Runon_NH4_kgN_ha;
    double Lateral_Runon_NO3_kgN_ha;
    double Lateral_Runon_NH4_kgN_ha;
    double Total_Runon_NO3_kgN_ha;
    double Total_Runon_NH4_kgN_ha;
    double Surface_Runoff_m3;
    double Lateral_Runoff_m3;
    double Total_Runoff_m3;
    double Surface_Runoff_NO3_kgN_ha;
    double Surface_Runoff_NH4_kgN_ha;
    double Lateral_Runoff_NO3_kgN_ha;
    double Lateral_Runoff_NH4_kgN_ha;
    double Total_Runoff_NO3_kgN_ha;
    double Total_Runoff_NH4_kgN_ha;
    double Drainage_m3;
    //170414LML should_be_Nitrite_leaching double Drainage_NO3_kgN;
    //170414LML should_be_Ammonium_leaching double Darinage_NH4_kgN;

public:
    OutputAnnualClass();
};

#endif // OUTPUTANNUALCLASS_H
