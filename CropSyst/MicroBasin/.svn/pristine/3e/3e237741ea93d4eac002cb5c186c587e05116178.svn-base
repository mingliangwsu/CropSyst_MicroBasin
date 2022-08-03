#include "croprootclass.h"
#include <math.h>
//______________________________________________________________________________
CropRootClass::CropRootClass(CropStateClass &_CropStateRef)
    :CropStateRef(_CropStateRef)
{
}
//______________________________________________________________________________
void CropRootClass::DetermineRootGrowth(bool Emerging,clsSoil &Soil,
  CropInputClass &CropParametersRef)
{
    double Root_Depth_At_Emergence = CropParametersRef.Root_Depth_At_Emergence;
    double Max_Root_Depth = CropParametersRef.Max_Root_Depth;
    double Max_Seasonal_Root_Depth_Gain = Max_Root_Depth - Root_Depth_At_Emergence;
    double Current_Root_Depth(0.0);
    //Calculate root depth
    if (CropParametersRef.Perennial_Crop == true) {       //perennial crops have always root depth max
        Current_Root_Depth = Max_Root_Depth;
        CropStateRef.Root_Depth = Current_Root_Depth;
    } else {       //'It is an annual crop
        if (CropStateRef.Cumulative_Thermal_Time <= 
          CropParametersRef.Thermal_Time_At_The_End_Of_Canopy_Growth) {
            double Stress_Factor(0.0);
            if (CropStateRef.Potential_Cumulative_Biomass > 0)
                Stress_Factor = pow(CropStateRef.Yesterday_Water_Stress_Factor,
                                    CropParametersRef.Root_Growth_Sensitivity_To_Stress);
            else Stress_Factor = 1;
            //Calculate root depth gain today
            //If Simulation.TimeState.DaysAfterGrowingSeasonStarted > 1 Then
            if (Emerging == false) {
                double Normalized_Thermal_Time_Today = 
                    (CropStateRef.Cumulative_Thermal_Time 
                     - CropParametersRef.Thermal_Time_for_Emergence) 
                    / (CropParametersRef.Thermal_Time_At_The_End_Of_Canopy_Growth 
                       - CropParametersRef.Thermal_Time_for_Emergence);
                double Normalized_Thermal_Time_Yesterday = 
                    (CropStateRef.Yesterday_Cumulative_Thermal_Time 
                     - CropParametersRef.Thermal_Time_for_Emergence) 
                    / (CropParametersRef.Thermal_Time_At_The_End_Of_Canopy_Growth 
                       - CropParametersRef.Thermal_Time_for_Emergence);
                double Unstressed_Root_Depth_Today = 
                    Root_Depth_At_Emergence + Max_Seasonal_Root_Depth_Gain * Normalized_Thermal_Time_Today;
                double Unstressed_Root_Depth_Yesterday = 
                    Root_Depth_At_Emergence + Max_Seasonal_Root_Depth_Gain * Normalized_Thermal_Time_Yesterday;
                double Root_Depth_Growth_Today = 
                    (Unstressed_Root_Depth_Today - Unstressed_Root_Depth_Yesterday) * Stress_Factor;
                Current_Root_Depth = CropStateRef.Root_Depth + Root_Depth_Growth_Today;
            } else {
                Current_Root_Depth = Root_Depth_At_Emergence;
            }
            CropStateRef.Root_Depth = Current_Root_Depth;
        } else {
            Current_Root_Depth = CropStateRef.Root_Depth;
            CropStateRef.Root_Depth = Current_Root_Depth;
        }
    }
    double Max_Root_Density = CropParametersRef.Max_Root_Density  
                              * Current_Root_Depth / CropParametersRef.Max_Root_Depth;
    int Number_Of_Soil_Layers = Soil.pSoilProfile->NumberOfLayers();
    int Max_Number_Of_Layer_Pot_Explored_By_Roots = Soil.pSoilProfile->Max_Number_Of_Layer_Pot_Explored_By_Roots; //FMS Mar 11, 2015
    double Weigthing_Factor[30];
    double Thickness_With_Roots[30];    //LML 150111 be careful about the maximum soil layers!
    for (int L = 1; L <= Number_Of_Soil_Layers; L++) {
        Weigthing_Factor[L] = 0;
        Thickness_With_Roots[L] = Soil.pSoilProfile->get_thickness_m(L);
    }
    double Current_Layer_Bottom_Depth(0.0);
    double Planting_Depth = CropParametersRef.Planting_Depth;
    int Layer_Number_Of_Seeding_Depth(0);
    for (int L = 1; L <= Number_Of_Soil_Layers; L++) {
        Current_Layer_Bottom_Depth += Thickness_With_Roots[L];
        if (Current_Layer_Bottom_Depth > Planting_Depth) {
            Thickness_With_Roots[L] = Current_Layer_Bottom_Depth - Planting_Depth;
            Layer_Number_Of_Seeding_Depth = L;
            L = Number_Of_Soil_Layers+1;        //Need double check!! M.Liu Jan 29, 2014
        } else {
            CropStateRef.Root_Fraction[L] = 0;
            Thickness_With_Roots[L] = 0;
        }
    }
    double Root_Fraction_Weighting_Factor[30];
    double Sum_Root_Fraction_Weighting_Factor(0.0);
    double Sum_Weighting_Factor(0.0);
    double Mid_Soil_Layer_Depth(0.0);
    double Curvature = CropParametersRef.Curvature_Root_Density_Function;
    for (int L = Layer_Number_Of_Seeding_Depth; L <= Number_Of_Soil_Layers; L++) {
        //Determine mid layer depth
        if (L == Layer_Number_Of_Seeding_Depth)
            Mid_Soil_Layer_Depth += Thickness_With_Roots[L] / 2.0;
        else
            Mid_Soil_Layer_Depth += Thickness_With_Roots[L - 1] / 2.0
                              + Thickness_With_Roots[L] / 2.0;
        //Calculate exponential distribution function per soil layer
        if ((Current_Root_Depth - Planting_Depth) >= Mid_Soil_Layer_Depth) {
            Weigthing_Factor[L] = 
                - (1.0 - exp(Curvature * ((Current_Root_Depth - Planting_Depth) - Mid_Soil_Layer_Depth)));
            Root_Fraction_Weighting_Factor[L] = Weigthing_Factor[L] * Thickness_With_Roots[L];
        } else {
            Weigthing_Factor[L] = 0;
            Root_Fraction_Weighting_Factor[L] = 0;
        }
        Sum_Weighting_Factor += Weigthing_Factor[L];
        Sum_Root_Fraction_Weighting_Factor += Root_Fraction_Weighting_Factor[L];
    }
    //'Calculate root fraction and root density
    double Sum_Root_Fraction(0.0);  // 'this is just a check
    for (int L = Layer_Number_Of_Seeding_Depth; L <= Number_Of_Soil_Layers; L++) {
        //'Root fraction
        CropStateRef.Root_Fraction[L] = Root_Fraction_Weighting_Factor[L] 
                                        / Sum_Root_Fraction_Weighting_Factor;
        Sum_Root_Fraction += CropStateRef.Root_Fraction[L]; // 'this is just a check
        //'Root density is calculated by setting the density of the top layer = maximum root density
        CropStateRef.Root_Density[L] = Max_Root_Density 
                                       * Weigthing_Factor[L]
                                       / Weigthing_Factor[Layer_Number_Of_Seeding_Depth];
    }

    //New lines FMS Mar 13, 2015
    double Sum_Root_Fraction_Weighting_Factor_Over_Max_Layer(0);
    if (Max_Number_Of_Layer_Pot_Explored_By_Roots < Number_Of_Soil_Layers) {
        for (int i = Max_Number_Of_Layer_Pot_Explored_By_Roots + 1; i <= Number_Of_Soil_Layers; i++) {
            CropStateRef.Root_Fraction[i] = 0;
            Sum_Root_Fraction_Weighting_Factor_Over_Max_Layer += Root_Fraction_Weighting_Factor[i];
        }
        for (int i = Layer_Number_Of_Seeding_Depth; i <= Max_Number_Of_Layer_Pot_Explored_By_Roots; i++) //FMS Mar 11, 2015
            CropStateRef.Root_Fraction[i] *= Sum_Root_Fraction_Weighting_Factor /
                                             (Sum_Root_Fraction_Weighting_Factor - Sum_Root_Fraction_Weighting_Factor_Over_Max_Layer);
    }
    //ended FMS's lines  Mar 13, 2015
    double Total_Root_Biomass_Today(0.0);
    //'OJO: DO WE NEED TO adjust root fraction for shallow soils OR HOSPITALY FACTOR to 
    //ensure that the sum of root fraction of all layers
    //'is equal to 1?
    double Total_Root_Length(0.0);
    for (int L = Layer_Number_Of_Seeding_Depth; L <= Max_Number_Of_Layer_Pot_Explored_By_Roots/*FMS Mar 11, 2015 Number_Of_Soil_Layers*/; L++) {
        //'Root length is in m root/m2 ground.  Root density is converted from cm/cm3 to m/m3
        CropStateRef.Root_Length[L] = CropStateRef.Root_Density[L] 
                                      * 10000.0 
                                      * Thickness_With_Roots[L];
        Total_Root_Length += CropStateRef.Root_Length[L];
        //'Root mass is in kg/m2. Root mass density is in m root length / kg root mass
        double Layer_Root_Mass = CropStateRef.Root_Length[L] 
                                 / (CropParametersRef.Root_Length_Per_Unit_Root_Mass * 1000.0);  
        // '1000 is to convert km/kg to m/kg
        CropStateRef.Layer_Root_Mass[L] = Layer_Root_Mass;
        Total_Root_Biomass_Today += Layer_Root_Mass;
    }
    if (!Emerging) {
        double Total_Root_Biomass_Yesterday = CropStateRef.Cumulative_Root_Biomass;
        CropStateRef.Water_Limited_Root_Biomass_Growth = 
            Total_Root_Biomass_Today - Total_Root_Biomass_Yesterday;
    } else {
        CropStateRef.Water_Limited_Root_Biomass_Growth = 0;
        CropStateRef.Cumulative_Root_Biomass = Total_Root_Biomass_Today;
    }
}
//______________________________________________________________________________
