#ifndef OUTPUTGROWTHCLASS_H
#define OUTPUTGROWTHCLASS_H
#include <string>
class OutputGrowthClass
{
public:
    int Current_Year;
    int Current_DOY;
    std::string Crop_Name;
    int Days_After_Crop_Planting;
    std::string Development_Stage;              //
    double Cumulative_Thermal_Time;
    double Potential_Cumulative_Biomass;                //(t/ha)
    double Actual_Cumulative_Biomass;                   //(t/ha)
    double Fraction_Solar_Rad_Intercepted_Green_Canopy;/*LML 140826 Potential_Green_Area_Index;*/
    double Leaf_Area_Index;                                                      //150601
    double Green_Area_Index;
    double Potential_Crop_Potential_Transpiration;      //(mm)
    double Crop_Potential_Transpiration;                //(mm)
    double Actual_Crop_Transpiration;                   //(mm)
    double Actual_Nitrogen_Uptake;                      //(kgN/ha)
    double Water_Stress_Index;
    double Top_Nitrogen_Stress_Index;
    double Root_Nitrogen_Stress_Index;
    double Root_Depth;                                  //(m)
public:
    OutputGrowthClass();
};

#endif // OUTPUTGROWTHCLASS_H
