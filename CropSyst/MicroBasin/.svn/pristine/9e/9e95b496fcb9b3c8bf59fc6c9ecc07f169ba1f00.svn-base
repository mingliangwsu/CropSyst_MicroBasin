#ifndef CROPINPUTCLASS_H
#define CROPINPUTCLASS_H

//#include "control/clssimulation.h"
//#include "control/allcontrolclass.h"
#include <string>

class clsSimulation;
class AllControlClass;
//______________________________________________________________________________
class CropInputClass
{
private:
    double WaterAvailabilityFactor(double PAW_Where_N_Upake_Rate_Decreases);
    double NAvailabilityFactor(double Soil_N_Conc_Where_N_Uptake_Decreases
                               ,double Residual_N_Not_Available_For_Uptake);
    double MaximumNitrogenUptakePerUnitRootLength(double planting_depth,double maximum_nitrogen_uptake);
    void DetermineCanopyGrowthParameters(double Initial_Canopy_Cover, double Maximum_Canopy_Cover);
    void DetermineSenescenceCanopyGrowthParameters(double Canopy_Cover_At_Maturity);
    //std::string getCropParameterFileName(clsSimulation &Simulation);
    std::string getCropParameterFileName(const std::string &cropname, AllControlClass &ControlRef); //150709RLN
public:
    std::string Crop_Name;
    double Radiation_Use_Efficiency;                                            //(g/MJ PAR)
    double Water_Use_Efficiency_at_1_kPa;                                       //(g/kg)
    double Slope_of_Water_Use_Efficiency_Function_of_VPD;                       //(negative)
    double Optimum_Growth_Mean_Temperature;                                     //(°C)
    double Initial_Canopy_Cover;                                                //(0-1)
    double Maximum_Canopy_Cover;                                                //(0-1)
    double Green_Canopy_Cover_At_Maturity;                                      //(0-1)
    double Total_Canopy_Cover_At_Maturity;                                      //(0-1)
    double Maximum_Crop_Height;                                                 //(m)
    double Critical_Leaf_Water_Potential_For_Canopy_Expansion;                  //(J/kg)
    double Minimum_Leaf_Water_Potential_For_Canopy_Expansion;                   //(J/kg)
    double Max_Root_Depth;                                                      //(m)
    double Max_Root_Density;                                                    //(cm/cm3)
    double Curvature_Root_Density_Function;
    double Root_Length_Per_Unit_Root_Mass;                                      //(km/kg DM)
    double Root_Growth_Sensitivity_To_Stress;
    double Base_Temperature_for_Development;                                    //(°C)
    double Optimum_Temperature_for_Development;                                 //(°C)
    double Maximum_Temperature_for_Development;                                 //(°C)
    double Thermal_Time_for_Emergence;                                          //(°C-days)
    double Thermal_Time_For_Budbreak_If_Chill_Reached;                          //(°C-days)
    double Thermal_Time_For_Budbreak_If_Chill_Not_Reached;                      //(°C-days)
    double Thermal_Time_for_Flowering;                                          //(°C-days)
    double Thermal_Time_for_Yield_Formation;                                    //(°C-days)
    double Thermal_Time_At_The_End_Of_Canopy_Growth;                            //(°C-days)
    double Thermal_Time_At_The_Beginning_Of_Canopy_Senescence;                  //(°C-days)
    double Thermal_Time_for_Maturity;                                           //(°C-days)
    double Crop_ET_Coeff_100_Percent_Cover;
    double Max_Water_Uptake;                                                    //(mm/day)
    double Leaf_Water_Pot_for_Stomatal_Closure;                                 //(J/kg)
    double Wilting_Leaf_Water_Pot;                                              //(J/kg)
    double Maximum_Nitrogen_Uptake_Per_Unit_Root_Length;                        //(kg/ha/day)
    double Water_Availability_Coefficient;                                      //(0-1) Plant Available Water at which N Uptake Limitation Begins
    double N_Availability_Coefficient;                                          //(ppm) Soil N Concentration at which N Uptake Limitation Begins
    double Residual_N_Not_Available_For_Uptake;                                 //(ppm)
    double Root_N_Concentration;                                                //(kgN/kg DM)
    double Grain_N_Coefficient;
    double Max_Early_Growth_Plant_N_Conc;
    double Unstressed_Harvest_Index;
    double Maximum_Translocation_Fraction;
    double Fresh_Mass_Fruit_Load;
    double Fraction_Solids_In_Fruits;
    double Required_Chill_Hours;
    int DOY_Start_Dormancy;
    int DOY_End_Dormancy;
    double Root_Depth_At_Emergence;
    double Planting_Depth;
    bool C3_Crop;
    bool Perennial_Crop;
    bool Root_Crop;
    bool Tree_Fruit_Crop;
    bool Grain_Crop;
    bool Vegetable_Crop;
    double Baseline_CO2_Concentration;                                          //(ppm)
    double Experimental_Elevated_CO2_Concentration;                             //(ppm)
    double Experimental_Biomass_Gain_Ratio_In_Response_To_CO2;
    double Crop_CN_IIA;
    double Crop_CN_IIB;
    double Crop_CN_IIC;
    double Crop_CN_IID;
    double b_Coefficient;
    double Shape_Factor;
    double Asym_CC;
    double Actual_CC_Max;
    double C_low;
    double Senescence_Asym_CC;
    //RS added
    double AT_PT_Ratio_that_Limits_Root_Growth;
    //Liu added
    double Initial_Green_Area_Index;    //Seems not used
    //FMS added Jun 25, 2014
    double Maintenance_Coef_leaves;                                             //(g glucose / g dry weight biomass / d)
    double Maintenance_Coef_stems;                                              //(g glucose / g dry weight biomass / d)
    double Maintenance_Coef_roots;                                              //(g glucose / g dry weight biomass / d)
    double Biosynthesis_Coef_leaves;                                            //(g dry weight biomass / g glucose (i.e. net photosynthesis - maintenance respiration))
    double Biosynthesis_Coef_stems;                                             //(g dry weight biomass / g glucose)
    double Biosynthesis_Coef_roots;                                             //(g dry weight biomass / g glucose)
    double Temperature_At_Maintenance_Are_Reported;                             //(°C)
    bool Leguminous_Crop;
    double Extinction_Coefficient_Crop_Of_Radiacion_Solar;                       //FMS Apr 8, 2015
    // ended FMS new lines
    //AllControlClass &ControlRef;
public:
    CropInputClass();//AllControlClass &_ControlRef);
    //void ReadCropParameters(clsSimulation &Simulation);
    void ReadCropParameters(std::string cropname, AllControlClass &ControlRef);
};
//_2014-02-xx___________________________________________________________________
#endif // CROPINPUTCLASS_H
