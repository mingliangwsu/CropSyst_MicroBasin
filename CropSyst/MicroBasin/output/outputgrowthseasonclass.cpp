#include "outputgrowthseasonclass.h"

OutputGrowthSeasonClass::OutputGrowthSeasonClass()
:
Crop_Name(""),
//160415LML Year_Planting(-9999),
//160415LML DOY_Planting(-9999),
//160415LML DOY_Emergence(-9999),
//160415LML DOY_Flowering(-9999),
//160415LML DOY_Begin_Yield_Formation(-9999),
//160415LML DOY_Physiological_Maturity(-9999),
//160415LML DOY_Harvest(-9999),
planting_date(0,0),
emergence_date(0,0),
flowering_date(0,0),
begin_yield_formation_date(0,0),
physiological_maturity_date(0,0),
harvest_date(0,0),
Potential_Cumulative_Biomass_At_Maturity(-9999),
Cumulative_Biomass_At_Maturity(-9999),
Cumulative_Root_Biomass_At_Maturity(-9999),
Potential_Crop_Yield(-9999),
Crop_Yield(-9999),
Water_Stress_Index(-9999),
Nitrogen_Stress_Index(-9999),
Precipitation_mm(-9999),
Actual_Transpiration_mm(-9999),
Actual_ET_mm(-9999),
Cumulative_Crop_Potential_Transpiration_At_Maturity(-9999),
Cumulative_Actual_Crop_Transpiration_At_Maturity(-9999),
Cumulative_Nitrogen_Uptake_At_Maturity(-9999),
Top_N_Mass_At_Maturity(-9999),
Root_N_Mass_At_Maturity(-9999),
Top_N_Mass_At_Emergence(-9999),
Root_N_Mass_At_Emergence(-9999),
Crop_N_Balance_At_Maturity(-9999),
Soil_Total_Nitrate_N_Mass_At_Planting(-9999),
Soil_Total_Nitrate_N_Mass_At_Maturity(-9999),
Soil_Total_Nitrate_N_Mass_At_Harvest(-9999),
Soil_Total_Ammonium_N_Mass_At_Planting(-9999),
Soil_Total_Ammonium_N_Mass_At_Maturity(-9999),
Soil_Total_Ammonium_N_Mass_At_Harvest(-9999),
Surface_Nitrate_N_Mass_At_Planting(-9999),                                       //(kgN/ha) 170510LML
Surface_Nitrate_N_Mass_At_Harvest(-9999),                                        //(kgN/ha) 170510LML
Surface_Ammonium_N_Mass_At_Planting(-9999),                                      //(kgN/ha) 170510LML
Surface_Ammonium_N_Mass_At_Harvest(-9999),                                       //(kgN/ha) 170510LML
N_Applied(-9999),
N_Mineralized(-9999),
N_Immobilized(-9999),
N_Leached(-9999),
N_runon(-9999),
N_runoff(-9999),
N_Volatilized(-9999),
N_Denitrified(-9999),
N_N2O_loss(-9999),
N_Updake(-9999),
Soil_Growing_Season_N_Balance(-9999),
Crop_Avg_Water_Stress_Index(-9999),
Crop_Avg_Top_Nitrogen_Stress_Index(-9999),
Crop_Avg_Root_Nitrogen_Stress_Index(-9999),
Overall_Crop_Nitrogen_Balance(-9999)
{
}