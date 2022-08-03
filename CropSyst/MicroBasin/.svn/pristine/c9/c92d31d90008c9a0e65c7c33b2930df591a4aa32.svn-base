#include "croppotsoluteuptakeclass.h"
#include "util/pubtools.h"
#include <math.h>

CropPotSoluteUptakeClass::CropPotSoluteUptakeClass(CropStateClass &_CropStateRef)
    :CropStateRef(_CropStateRef)
{
}

void CropPotSoluteUptakeClass::PotentialNitrogenUptake(clsSoil &Soil
       , CropInputClass &CropParametersRef)
{
    double Total_Potential_Nitrate_N_Uptake(0.0);
    double Total_Potential_Ammonium_N_Uptake(0.0);
    int Number_Of_Layers = Soil.pSoilProfile->NumberOfLayers();
    int Max_Number_Of_Layer_Pot_Explored_By_Roots = Soil.pSoilProfile->Max_Number_Of_Layer_Pot_Explored_By_Roots; //FMS Mar 11, 2015
    double Water_Availability_Coefficient = CropParametersRef.Water_Availability_Coefficient;
    double N_Availability_Coefficient = CropParametersRef.N_Availability_Coefficient;
    double Residual_N_Conc_ppm = CropParametersRef.Residual_N_Not_Available_For_Uptake;
    double Root_Senescence_Factor = RootSenescenceFactor(CropParametersRef);
    double Maximum_N_Uptake_Per_Unit_Root_Length = 
            CropParametersRef.Maximum_Nitrogen_Uptake_Per_Unit_Root_Length 
            * Root_Senescence_Factor;
    for (int L = 1; L <= Max_Number_Of_Layer_Pot_Explored_By_Roots/*150520 Number_Of_Layers*/; L++) {
        double Layer_Nitrate_N_Mass = Soil.pSoilState->Layer_Nitrate_N_Mass[L];
        double Layer_Ammonium_N_Mass = Soil.pSoilState->Layer_Ammonium_N_Mass[L];
        double Layer_Mineral_Nitrogen_Mass = Layer_Nitrate_N_Mass + Layer_Ammonium_N_Mass;
        double Layer_Thickness = Soil.pSoilProfile->get_thickness_m(L);
        double Bulk_Density = Soil.pSoilProfile->get_bulk_density_g_cm3(L);
        double Layer_Potential_Nitrate_N_Uptake(0.0);
        double Layer_Potential_Ammonium_N_Uptake(0.0);
        if (Layer_Mineral_Nitrogen_Mass > 0) {
            double Root_Length = CropStateRef.Root_Length[L];
            double Plant_Available_Water = CurrentPAW(L, Soil);
            double Water_Availability_Adjustment = 1.0 - exp(-Water_Availability_Coefficient * Plant_Available_Water);
            double N_Conc_ppm = (Layer_Mineral_Nitrogen_Mass * 1000.0) / (Layer_Thickness * Bulk_Density);
            double N_Availability_Adjustment(0.0);
            if (N_Conc_ppm > Residual_N_Conc_ppm)
                N_Availability_Adjustment = (1.0 - exp(-(N_Conc_ppm - Residual_N_Conc_ppm) * N_Availability_Coefficient));
            else
                N_Availability_Adjustment = 0;
            double Layer_Potential_N_Uptake = Maximum_N_Uptake_Per_Unit_Root_Length * Root_Length
                * Root_Senescence_Factor * Water_Availability_Adjustment * N_Availability_Adjustment;
            Layer_Potential_Nitrate_N_Uptake = std::min<double>(Layer_Potential_N_Uptake * Layer_Nitrate_N_Mass / Layer_Mineral_Nitrogen_Mass, Layer_Nitrate_N_Mass);
            Layer_Potential_Ammonium_N_Uptake = std::min<double>(Layer_Potential_N_Uptake - Layer_Potential_Nitrate_N_Uptake, Layer_Ammonium_N_Mass);
        } else {
            Layer_Potential_Nitrate_N_Uptake = 0;
            Layer_Potential_Ammonium_N_Uptake = 0;
        }
        Soil.pSoilState->Layer_Potential_Nitrate_N_Uptake[L] = Layer_Potential_Nitrate_N_Uptake;
        Soil.pSoilState->Layer_Potential_Ammonium_N_Uptake[L] = Layer_Potential_Ammonium_N_Uptake;
        Total_Potential_Nitrate_N_Uptake += Layer_Potential_Nitrate_N_Uptake;
        Total_Potential_Ammonium_N_Uptake += Layer_Potential_Ammonium_N_Uptake;
    }//L
    Soil.pSoilState->Total_Potential_Nitrate_N_Uptake = Total_Potential_Nitrate_N_Uptake;
    Soil.pSoilState->Total_Potential_Ammonium_N_Uptake = Total_Potential_Ammonium_N_Uptake;
}

double CropPotSoluteUptakeClass::CurrentPAW(int layer, clsSoil &Soil)
{
    double Current_PAW = (Soil.pSoilState->get_liquid_water_content_volumetric(layer) 
                          - Soil.pSoilProfile->get_permanent_wilt_point_volumetric(layer))
                         / (Soil.pSoilProfile->get_field_capacity_volumetric(layer) 
                           - Soil.pSoilProfile->get_permanent_wilt_point_volumetric(layer));
    if (Current_PAW > 1) Current_PAW = 1;
    else if (Current_PAW < 0) Current_PAW = 0;
    return Current_PAW;
}

double CropPotSoluteUptakeClass::RootSenescenceFactor(CropInputClass &CropParametersRef)
{
    double Thermal_Time_Current = CropStateRef.Cumulative_Thermal_Time;
    double Thermal_Time_Flowering = CropParametersRef.Thermal_Time_for_Flowering;
    double Thermal_Time_Maturity = CropParametersRef.Thermal_Time_for_Maturity;
    //This accounts for root senescence after flowering
    double Root_Senescence_Factor(1.0);
    if (Thermal_Time_Current > Thermal_Time_Flowering) {  // Then 'ROGER: Use Peak LAI instead of flowering
        if (Thermal_Time_Current < Thermal_Time_Maturity)
            Root_Senescence_Factor = 1.0 - (Thermal_Time_Current - Thermal_Time_Flowering) 
                                           / (Thermal_Time_Maturity - Thermal_Time_Flowering);
        else Root_Senescence_Factor = 0.0;    // 'JAVIER MARCOS 082207 added line
    }
    //Need double check!! M.Liu Jan.28, 2014
    return Root_Senescence_Factor;
}
