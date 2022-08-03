#ifndef OUTPUTGROWTHSEASONCLASS_H
#define OUTPUTGROWTHSEASONCLASS_H
#include <string>
#include "corn/chronometry/date_32.h"
/*#ifdef __linux__
//#include "corn/datetime/date.hpp"
#else
#include "CORN/datetime/date.hpp"
#endif
*/

class OutputGrowthSeasonClass
{
public:
    //Growth_Season
    std::string Crop_Name;
    //160415LML int Year_Planting;
    //160415LML int DOY_Planting;
    //160415LML int DOY_Emergence;
    //160415LML int DOY_Flowering;
    //160415LML int DOY_Begin_Yield_Formation;
    //160415LML int DOY_Physiological_Maturity;
    //160415LML int Year_Harvest;
    //160415LML int DOY_Harvest;
    CORN::Date_32_clad planting_date;                                                    //160415LML
    CORN::Date_32_clad emergence_date;                                                   //160415LML
    CORN::Date_32_clad flowering_date;                                                   //160415LML
    CORN::Date_32_clad begin_yield_formation_date;                                       //160415LML
    CORN::Date_32_clad physiological_maturity_date;                                      //160415LML
    CORN::Date_32_clad harvest_date;                                                     //160415LML
    double Potential_Cumulative_Biomass_At_Maturity;                //(kgDM/ha)
    double Cumulative_Biomass_At_Maturity;                          //(kgDM/ha)
    double Cumulative_Root_Biomass_At_Maturity;                     //(kgDM/ha)
    double Potential_Crop_Yield;                                    //(kgDM/ha)
    double Crop_Yield;                                              //(kgDM/ha)
    double Water_Stress_Index;                                      //(0-1) 161101LML
    double Nitrogen_Stress_Index;                                   //(0-1) 161101LML
    double Precipitation_mm;                                        //161101LML
    double Actual_Transpiration_mm;                                 //161101LML
    double Actual_ET_mm;                                            //161101LML
    double Cumulative_Crop_Potential_Transpiration_At_Maturity;     //(m)
    double Cumulative_Actual_Crop_Transpiration_At_Maturity;        //(m)
    double Cumulative_Nitrogen_Uptake_At_Maturity;                  //(kgN/ha)
    double Top_N_Mass_At_Maturity;                                  //(kgN/ha)
    double Root_N_Mass_At_Maturity;                                 //(kgN/ha)
    double Top_N_Mass_At_Emergence;                                 //(kgN/ha)
    double Root_N_Mass_At_Emergence;                                //(kgN/ha)
    double Crop_N_Balance_At_Maturity;                              //(kgN/ha) N_uptake+TopN_Emergence+RootN_Emergence-TopN_Matunity-RootN_Matunity
    double Soil_Total_Nitrate_N_Mass_At_Planting;                   //(kgN/ha)
    double Soil_Total_Nitrate_N_Mass_At_Maturity;                   //(kgN/ha)
    double Soil_Total_Nitrate_N_Mass_At_Harvest;                    //(kgN/ha) 170410LML
    double Soil_Total_Ammonium_N_Mass_At_Planting;                  //(kgN/ha)
    double Soil_Total_Ammonium_N_Mass_At_Maturity;                  //(kgN/ha)
    double Soil_Total_Ammonium_N_Mass_At_Harvest;                   //(kgN/ha) 170410LML

    double Surface_Nitrate_N_Mass_At_Planting;                      //(kgN/ha) 170510LML
    double Surface_Nitrate_N_Mass_At_Harvest;                       //(kgN/ha) 170510LML
    double Surface_Ammonium_N_Mass_At_Planting;                     //(kgN/ha) 170510LML
    double Surface_Ammonium_N_Mass_At_Harvest;                      //(kgN/ha) 170510LML

    double N_Applied;                                               //(kgN/ha) 170414LML note: inorganic N only
    double N_Mineralized;                                           //(kgN/ha)
    double N_Immobilized;                                           //(kgN/ha)
    double N_Leached;                                               //(kgN/ha)
    double N_runon;                                                 //(kgN/ha) 170417LML
    double N_runoff;                                                //(kgN/ha) 170417LML runoff N through overland and soil lateral flow. Doesn't include leaching (through drainage)
    double N_Volatilized;                                           //(kgN/ha)
    double N_Nitrfication;
    double N_Denitrified;                                           //(kgN/ha)
    double N_N2O_loss;                                              //(kgN/ha) 170207LML
    double N_N2O_loss_denitrification;                              //(kgN/ha) 170331LML
    double N_N2O_loss_nitrification;                                //(kgN/ha) 170331LML
    double N_Updake;                                                             //160115LML
    double N_Fixation;                                                           //160405LML
    double Soil_Growing_Season_N_Balance;                           //(kgN/ha)
    double Crop_Avg_Water_Stress_Index;
    double Crop_Avg_Top_Nitrogen_Stress_Index;
    double Crop_Avg_Root_Nitrogen_Stress_Index;
    double Overall_Crop_Nitrogen_Balance;                           //(kgN/ha)
public:
    OutputGrowthSeasonClass();
};

#endif // OUTPUTGROWTHSEASONCLASS_H
