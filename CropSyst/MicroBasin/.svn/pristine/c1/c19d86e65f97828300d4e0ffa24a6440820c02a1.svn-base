#ifndef CROPSTATECLASS_H
#define CROPSTATECLASS_H
#include <string>

class CropStateClass
{
public:
    std::string Crop_Name;                                      // As String
    double Reference_ET;                                        //(366)
    double CO2_Elevated_Reference_Crop_ET;                      //(366)
    double Cumulative_Reference_Crop_ET;                        //(366)
    double Cumulative_CO2_Elevated_Reference_Crop_ET;           //(366)
    double Crop_Potential_Transpiration;                        //(366)
    double Potential_Crop_Potential_Transpiration;              //(366)
    double Actual_Crop_Transpiration;                           //(mm/day)
    double Cumulative_Crop_Potential_Transpiration;             //(366)
    double Cumulative_Actual_Crop_Transpiration;                //(366)
    double Potential_Soil_Evaporation;                          //(366)
    double Actual_Soil_Evaporation;                             //(366)
    double Cumulative_Potential_Soil_Evaporation;               //(366)
    double Cumulative_Actual_Soil_Evaporation;                  //(366)
    double Initial_Soil_Profile_Water;                          //
    double Final_Soil_Profile_Water;                            //
    double Potential_Biomass_Today;                             //(kg DM/m2) DM: dry matter
    double Attainable_Biomass_Today;                            //(kg DM/m2)
    double Biomass_Today;                                       //(kg DM/m2) Actual_Top_Biomass_Growth
    double Water_Limited_Biomass_Growth;                        //(366)
    double Cumulative_Biomass;                                  //(kg DM/m2) Top_Biomass only
    //150529 double Cumulative_Biomass_Yesterday;                        //LML 140725
    double Cumulative_Attainable_Biomass;                       //(kg DM/m2)
    double Potential_Cumulative_Biomass;                        //(kg DM/m2)
    double Reserve_Biomass_Pool;                                //(kg DM/m2)
    double Cumulative_Fruit_Biomass_Growth;                     //(366)
    double Root_Depth;                                          //(366)
    double Leaf_Area_Index;                                     //(366)
    //LML 140826 double Green_Area_Index;                                    //(366)
    double Crop_Height;                                         //(366)
    double Potential_Crop_Height;                               //(366)
    double Potential_Green_Area_Index_Today;                    //(366)
    double Green_Area_Index_Today;                              //(366)
    double Potential_Leaf_Area_Index;                           //(366)
    //LML 140826 double Potential_Green_Area_Index;                          //(366)
    double Potential_Thermal_Time_Today;                        //(366)
    double Thermal_Time_Today;                                  //(366)
    double Potential_Cumulative_Thermal_Time;                   //(366)
    double Cumulative_Thermal_Time;                             //(366)
    double Potential_GAI_Thermal_Time_Elapsed;                  //(366)
    double GAI_Thermal_Time_Elapsed;                            //(366)
    std::string Potential_Development_Stage;                    //(366) As String
    std::string Development_Stage;                              //(366) As String
    double Water_Stress_Index;                                  //(366)
    double Water_Stress_Factor;                                 //(366)
    double Flowering_Water_Stress_Index;                        //
    double Cumulative_Water_Stress_Index;                       //(366)
    double Leaf_Water_Potential;                                //(366)
    double Attainable_Biomass_During_Yield_Formation;           //
    double Biomass_Produced_During_Yield_Formation;             //
    double Water_Limited_Root_Biomass_Growth;                   //(366)
    double Cumulative_Root_Biomass;                             //(kg DM/m2)
    double Cumulative_Root_Biomass_Yesterday;                   //LML 140725
    double Biomass_Produced_Before_Yield_Formation;             //
    double Cumulative_Biomass_Produced_During_Yield_Formation;  // FMS Jun 30, 2014
    double Yield;                                               //
    double Potential_Yield;                                     //
    double Current_ET_Crop_Coeff;                               //(366)
    double Potential_Current_ET_Crop_Coeff;                     //(366)
    double Fraction_PAR_Intercepted;                            //(366)
    double Potential_Fraction_PAR_Intercepted;                  //(366)
    double Fraction_Solar_Rad_Intercepted_Green_Canopy;         //(366)
    double Fraction_Solar_Rad_Intercepted_Total_Canopy;         //(366)
    double Potential_Fraction_Solar_Rad_Intercepted;            //(366)
    double PAR_Interception;                                    //(366)
    double Solar_Rad_Interception;                              //(366)
    double Root_Fraction[30];                                   //(366, 30)
    double Root_Density[30];                                    //(366, 30)
    double Root_Length[30];                                     //(366, 30)
    double Layer_Root_Mass[30];                                 //(366, 30)
    double CO2_Adjustment_To_RUE;                               //(366)
    double CO2_Adjustment_To_TUE;                               //(366)
    double CO2_Adjustment_To_Transpiration;                     //(366)
    int Year_Planting;
    int DOY_Planting;
    int DOY_Start_Growing_Season;
    int DOY_Emergence;
    int DOY_Flowering;
    int Days_In_Flowering;
    int DOY_Begin_Yield_Formation;
    int DOY_Physiological_Maturity;
    int DOY_Harvest;
    //Dim Days_After_Planting_At_Maturity
    //Dim Days_After_Planting_At_Emergence
    int Potential_DOY_Emergence;
    int Potential_DOY_Flowering;
    int Potential_DOY_Begin_Yield_Formation;
    int Potential_DOY_Physiological_Maturity;
    int Potential_DOY_Harvest;
    bool Crop_Exist;
    bool Crop_Emerged;
    bool Crop_Dormant;
    bool Dormancy_Broken;
    bool First_Day_Of_Dormancy;
    bool First_Day_Of_Dormancy_Broken;
    bool First_Day_Of_Maturity;
    bool Flowering;
    bool Crop_Forming_Yield;
    bool Mature;
    bool Harvested;
    bool Chill_Requirement_Satisfied;
    bool First_Day_Chill_Requirement_Satisfied;
    int Days_After_Crop_Exist_At_Emergence;
    int Days_After_Crop_Exist_At_Maturity;
    int Days_After_Crop_Exist_At_Dormancy;
    int Days_After_Crop_Exist_At_Start_Of_Season;
    int Days_After_Crop_Exist_At_End_Of_Season;
    int Current_Year;                       //(366)
    int Current_DOY;                       //(366)
    //NITROGEN DEMAND_RELATED ITEMS. CHECK FOR DUPLICATIONSXXXXXXXXXXXXXXX
    double Potential_Profile_Nitrogen_Uptake;                       //(366)
    double Actual_Profile_Nitrogen_Uptake;                       //(366)
    double Daily_Maximum_N_Concentration;                       //(366)
    double Daily_Critical_N_Concentration;                       //(366)
    double Daily_Minimum_N_Concentration;                       //(366)
    double Maximum_N_Concentration_At_Flowering;                       //
    double Critical_N_Concentration_At_Flowering;                       //
    double Minimum_N_Concentration_At_Flowering;                       //
    double N_Required_For_Attainable_Top_Growth;                       //(366)
    double N_Required_For_Water_Limited_Root_Growth;                       //(366)
    double Crop_Nitrogen_Demand;                       //(366)
    double Top_Crop_N_Concentration;                       //(366)
    double Actual_Nitrogen_Uptake;                       //(366)
    double Cumulative_Nitrogen_Uptake;                       //(366)
    double Actual_Root_Biomass_Growth;                       //(366) 'TEMPORARY: MOVE TO GROWTH
    double Top_Nitrogen_Stress_Factor;                       //(366)
    double Root_Nitrogen_Stress_Factor;                       //(366)
    double Top_Nitrogen_Stress_Index;                       //(366)
    double Root_Nitrogen_Stress_Index;                       //(366)
    double Cumulative_Top_Nitrogen_Stress_Index;                       //(366)
    double Cumulative_Root_Nitrogen_Stress_Index;                       //(366)
    double Top_N_Mass;                       //(366)
    double Top_N_Mass_Yesterday;                                                 //150529LML
    double Root_N_Mass;                       //(366)
    double Root_N_Mass_Yesterday;                                                //150529LML
    double Top_N_Mass_At_Emergence;                       //(366)
    double Root_N_Mass_At_Emergence;                       //(366)
    double Cumulative_Top_N_Mass;                       //(366)
    double Cumulative_Root_N_Mass;                       //(366)
    double N_Surplus;                       //(366)
    double Top_Nitrogen_Balance;                       //(366)
    double Root_Nitrogen_Balance;                       //(366)
    double Overall_Crop_Nitrogen_Balance;                       //(366)
    double Grain_Nitrogen_Concentration;                       //
    double Straw_Nitrogen_Concentration;                       //
    //RS added
    double Hourly_Canopy_Solar_Radiation_Interception_Fraction[25];                       //(25)
    //M.Liu added
    double Yesterday_Potential_Fraction_Solar_Rad_Intercepted;
    double Yesterday_Fraction_Solar_Rad_Intercepted_Green_Canopy;
    double Yesterday_Cumulative_Thermal_Time;
    double Yesterday_Water_Stress_Index;
    double Yesterday_Water_Stress_Factor;
    //double Yesterday_Leaf_Water_Potential;
    //double Yesterday_Fraction_Solar_Rad_Intercepted_Green_Canopy;
public:
    CropStateClass();
    void ClearStateAndFluxes();
    double getFractionSolarRadInterceptedTotalCanopy();
};

#endif // CROPSTATECLASS_H
