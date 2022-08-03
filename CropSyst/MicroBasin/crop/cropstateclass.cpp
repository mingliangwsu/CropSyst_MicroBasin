#include "cropstateclass.h"

CropStateClass::CropStateClass()
{
}
//______________________________________________________________________________
double CropStateClass::getFractionSolarRadInterceptedTotalCanopy() {
    return Fraction_Solar_Rad_Intercepted_Total_Canopy;
}
//______________________________________________________________________________
void CropStateClass::ClearStateAndFluxes()
{
    Crop_Name = "";
    Reference_ET = 0;
    CO2_Elevated_Reference_Crop_ET = 0;
    Cumulative_Reference_Crop_ET = 0;
    Cumulative_CO2_Elevated_Reference_Crop_ET = 0;
    Crop_Potential_Transpiration = 0;
    Potential_Crop_Potential_Transpiration = 0;
    Actual_Crop_Transpiration = 0;
    Cumulative_Crop_Potential_Transpiration = 0;
    Cumulative_Actual_Crop_Transpiration = 0;
    Potential_Soil_Evaporation = 0;
    Actual_Soil_Evaporation = 0;
    Cumulative_Potential_Soil_Evaporation = 0;
    Cumulative_Actual_Soil_Evaporation = 0;
    Initial_Soil_Profile_Water = 0;
    Final_Soil_Profile_Water = 0;
    Potential_Biomass_Today = 0;
    Attainable_Biomass_Today = 0;
    Biomass_Today = 0;
    Water_Limited_Biomass_Growth = 0;
    Cumulative_Biomass = 0;
    //150529 Cumulative_Biomass_Yesterday = 0;
    Cumulative_Attainable_Biomass = 0;
    Potential_Cumulative_Biomass = 0;
    Reserve_Biomass_Pool = 0;
    Cumulative_Fruit_Biomass_Growth = 0;
    Root_Depth = 0;
    Leaf_Area_Index = 0;
    //Green_Area_Index = 0;
    Crop_Height = 0;
    Potential_Crop_Height = 0;
    Potential_Green_Area_Index_Today = 0;
    Green_Area_Index_Today = 0;
    Potential_Leaf_Area_Index = 0;
    //LML 140826 Potential_Green_Area_Index = 0;
    Potential_Thermal_Time_Today = 0;
    Thermal_Time_Today = 0;
    Potential_Cumulative_Thermal_Time = 0;
    Yesterday_Cumulative_Thermal_Time = 0;
    Cumulative_Thermal_Time = 0;
    Potential_GAI_Thermal_Time_Elapsed = 0;
    GAI_Thermal_Time_Elapsed = 0;
    Potential_Development_Stage = "";
    Development_Stage = "";
    Cumulative_Biomass_Produced_During_Yield_Formation = 0.0;   //LML 140903
    Water_Stress_Index = 0;
    Yesterday_Water_Stress_Index = 0;
    Water_Stress_Factor = 0;
    Yesterday_Water_Stress_Factor = 1.0;
    Flowering_Water_Stress_Index = 0;
    Cumulative_Water_Stress_Index = 0;
    Leaf_Water_Potential = 0;
    Attainable_Biomass_During_Yield_Formation = 0;
    Biomass_Produced_During_Yield_Formation = 0;
    Water_Limited_Root_Biomass_Growth = 0;
    Cumulative_Root_Biomass = 0;
    Cumulative_Root_Biomass_Yesterday = 0;
    Biomass_Produced_Before_Yield_Formation = 0;
    Yield = 0;
    Potential_Yield = 0;
    Current_ET_Crop_Coeff = 0;
    Potential_Current_ET_Crop_Coeff = 0;
    Fraction_PAR_Intercepted = 0;
    Potential_Fraction_PAR_Intercepted = 0;
    Fraction_Solar_Rad_Intercepted_Green_Canopy = 0;
    Yesterday_Fraction_Solar_Rad_Intercepted_Green_Canopy = 0;
    Fraction_Solar_Rad_Intercepted_Total_Canopy = 0;
    Potential_Fraction_Solar_Rad_Intercepted = 0;
    PAR_Interception = 0;
    Solar_Rad_Interception = 0;
    for (int i = 0; i<30; i++) {
        Root_Fraction[i] = 0;
        Root_Density[i] = 0;
        Root_Length[i] = 0;
        Layer_Root_Mass[i] = 0;
    }
    CO2_Adjustment_To_RUE = 0;
    CO2_Adjustment_To_TUE = 0;
    CO2_Adjustment_To_Transpiration = 0;
    Year_Planting = -9999;
    DOY_Planting = -9999;
    DOY_Start_Growing_Season = -9999;
    DOY_Emergence = -9999;
    DOY_Flowering = -9999;
    Days_In_Flowering = -9999;
    DOY_Begin_Yield_Formation = -9999;
    DOY_Physiological_Maturity = -9999;
    DOY_Harvest = -9999;
    Potential_DOY_Emergence = -9999;
    Potential_DOY_Flowering = -9999;
    Potential_DOY_Begin_Yield_Formation = -9999;
    Potential_DOY_Physiological_Maturity = -9999;
    Potential_DOY_Harvest = -9999;
    Crop_Exist = false;
    Crop_Emerged = false;
    Crop_Dormant = false;
    Dormancy_Broken = false;
    First_Day_Of_Dormancy = false;
    First_Day_Of_Dormancy_Broken = false;
    First_Day_Of_Maturity = false;
    Flowering = false;
    Crop_Forming_Yield = false;
    Mature = false;
    Harvested = false;
    Chill_Requirement_Satisfied = false;
    First_Day_Chill_Requirement_Satisfied = false;
    Days_After_Crop_Exist_At_Emergence = 0;
    Days_After_Crop_Exist_At_Maturity = 0;
    Days_After_Crop_Exist_At_Dormancy = 0;
    Days_After_Crop_Exist_At_Start_Of_Season = 0;
    Days_After_Crop_Exist_At_End_Of_Season = 0;
    Current_Year = 0;
    Current_DOY = 0;
    Potential_Profile_Nitrogen_Uptake = 0;
    Actual_Profile_Nitrogen_Uptake = 0;
    Daily_Maximum_N_Concentration = 0;
    Daily_Critical_N_Concentration = 0;
    Daily_Minimum_N_Concentration = 0;
    Maximum_N_Concentration_At_Flowering = 0;
    Critical_N_Concentration_At_Flowering = 0;
    Minimum_N_Concentration_At_Flowering = 0;
    N_Required_For_Attainable_Top_Growth = 0;
    N_Required_For_Water_Limited_Root_Growth = 0;
    Crop_Nitrogen_Demand = 0;
    Top_Crop_N_Concentration = 0;
    Actual_Nitrogen_Uptake = 0;
    Cumulative_Nitrogen_Uptake = 0;
    Actual_Root_Biomass_Growth = 0;
    Top_Nitrogen_Stress_Factor = 0;
    Root_Nitrogen_Stress_Factor = 0;
    Top_Nitrogen_Stress_Index = 0;
    Root_Nitrogen_Stress_Index = 0;
    Cumulative_Top_Nitrogen_Stress_Index = 0;
    Cumulative_Root_Nitrogen_Stress_Index = 0;
    Top_N_Mass = 0;
    Top_N_Mass_Yesterday = 0;                                                    //150529LML
    Root_N_Mass = 0;
    Root_N_Mass_Yesterday = 0;                                                   //150529LML
    Top_N_Mass_At_Emergence = 0;
    Root_N_Mass_At_Emergence = 0;
    Cumulative_Top_N_Mass = 0;
    Cumulative_Root_N_Mass = 0;
    N_Surplus = 0;
    Top_Nitrogen_Balance = 0;
    Root_Nitrogen_Balance = 0;
    Overall_Crop_Nitrogen_Balance = 0;
    Grain_Nitrogen_Concentration = 0;
    Straw_Nitrogen_Concentration = 0;
    for (int i = 0; i <= 24; i++)
        Hourly_Canopy_Solar_Radiation_Interception_Fraction[i] = 0;
    Yesterday_Potential_Fraction_Solar_Rad_Intercepted = 0;
    Yesterday_Cumulative_Thermal_Time = 0;
}
//______________________________________________________________________________
