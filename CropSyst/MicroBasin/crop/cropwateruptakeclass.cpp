#include "cropwateruptakeclass.h"
/* RLN temp disabled to find icomplete header
#include "util/pubtools.h"
#include "util/constants.h"
*/
#include "util/pubtools.h"
#include <math.h>
#include "corn/math/compare.hpp"
#ifdef CHECK_MASS_BALANCE
#include "control/balanceitem.h"
#endif

//______________________________________________________________________________
CropWaterUptakeClass::CropWaterUptakeClass(CropStateClass &_CropStateRef)
    :CropStateRef(_CropStateRef)
{
}
//______________________________________________________________________________
void CropWaterUptakeClass::PerformWaterUptake(clsSoil &Soil, 
  CropInputClass &CropParametersRef)
{
    //Need double-check!!
    //M.Liu Jan 29, 2014
    //#ifdef CHECK_MASS_BALANCE
    //BalanceItem bal_water;
    //bal_water.SetInitPool(Soil.pSoilState->getTotalSoilLiqWaterContent_m());
    //#endif
    //if (Simulation.pTimeState->getToday().get_DOY() == 190) {
        //int btest = 1;
    //}
    double Fract_Green_Canopy_Interception_SolRad = 
        CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy;
    int Max_Number_Of_Layer_Pot_Explored_By_Roots = Soil.pSoilProfile->Max_Number_Of_Layer_Pot_Explored_By_Roots; //FMS Mar 11, 2015
    double WSI(0.0);
    double Crop_Water_Uptake(0.0);
    if (Fract_Green_Canopy_Interception_SolRad > 0) {
        //Define soil water potential at field capacity
        //Soil_Water_Potential_At_Field_Capacity = -33;
        double Soil_Water_Potential_At_Field_Capacity = 
            Soil.pSoilProfile->get_water_pot_at_FC(1); //FMS 140930
        double Leaf_Water_Potential_At_Onset_Of_Stress = 
            CropParametersRef.Leaf_Water_Pot_for_Stomatal_Closure;
        double Full_Cover_Crop_Water_Uptake_Max = CropParametersRef.Max_Water_Uptake;
        double Leaf_Water_Potential_At_Wilt = CropParametersRef.Wilting_Leaf_Water_Pot;
        int Number_Of_Layers = Soil.pSoilProfile->NumberOfLayers();
        double Soil_Water_Potential[30];
        double Root_Fraction[30];
        for (int layer = 1; layer <= Number_Of_Layers; layer++) {
            Soil_Water_Potential[layer] =
                //140603 #ifndef CROPSYST_HYDROLOGY
               Soil.get_hydrology_constant()->get_water_potential(layer);
               #ifdef MBVB_FD
               Soil.pSoilState->Water_Potential[layer];
               #endif
            Root_Fraction[layer] = CropStateRef.Root_Fraction[layer];
        }
        //Calculate potential transpiration rate (kg/m2/d = mm/d)
        double Crop_Potential_Transpiration = CropStateRef.Crop_Potential_Transpiration;
        //Calculate crop maximun water uptake rate (kg/m2/d = mm/d)
        double Max_Crop_Water_Uptake = Full_Cover_Crop_Water_Uptake_Max 
                                       * Fract_Green_Canopy_Interception_SolRad;
        //Calculate maximum crop transpiration rate (kg/m2/d = mm/d). 
        //This includes nitrogen stress reduction of transpiration
        double Max_Crop_Transpiration = 
            std::min<double>(Crop_Potential_Transpiration, Max_Crop_Water_Uptake);
        if (Max_Crop_Transpiration < 0.0001) Max_Crop_Transpiration = 0.0001;
        //Calculate plant hydraulic conductivity ((kg^2)/(m2-J-d)
        double Plant_Hydraulic_Conductance = 
                Max_Crop_Water_Uptake / (Soil_Water_Potential_At_Field_Capacity 
                                         - Leaf_Water_Potential_At_Onset_Of_Stress);
        //Adjust plant hydraulic conductivity based on soil dryness
        double Root_Hydraulic_Conductance = Plant_Hydraulic_Conductance / 0.65;
        double Top_Hydraulic_Conductance = Plant_Hydraulic_Conductance / 0.35;
        double Root_Conductance_Adjustment(0.0);
        //This constant should be calculated for (each layer to account for 
        //(salinity reduction of layer root permeability, currently not implemented
        double Salinity_Reduction_Factor = 1; //value between 0 and 1
        double Root_Activity_Factor[30];
        double Layer_Salinity_Reduction_Factor[30];
        double Layer_Root_Conductance_Adjustment[30];
        double Layer_Root_Hydraulic_Conductance[30];
        for (int layer = 1; layer <= Max_Number_Of_Layer_Pot_Explored_By_Roots /*150520 Number_Of_Layers*/; layer++) {
            Root_Activity_Factor[layer] = 
                1.0 - pow(((Soil_Water_Potential[layer] - Soil_Water_Potential_At_Field_Capacity)
                            / (Leaf_Water_Potential_At_Wilt - Soil_Water_Potential_At_Field_Capacity)),
                          8.0);
            if (Root_Activity_Factor[layer] > 1) Root_Activity_Factor[layer] = 1;
            else if (Root_Activity_Factor[layer] < 0) Root_Activity_Factor[layer] = 0;
            Layer_Salinity_Reduction_Factor[layer] = Salinity_Reduction_Factor;
            Layer_Root_Conductance_Adjustment[layer] = 
                    Root_Activity_Factor[layer] 
                    * Root_Fraction[layer] 
                    * Layer_Salinity_Reduction_Factor[layer];
            Root_Conductance_Adjustment += Layer_Root_Conductance_Adjustment[layer];
            Layer_Root_Hydraulic_Conductance[layer] = 
                Root_Hydraulic_Conductance * Layer_Root_Conductance_Adjustment[layer];
        }
        double Layer_Top_Hydraulic_Conductance[30];
        double Layer_Plant_Hydraulic_Conductance[30];
        for (int layer = 1; layer <= Max_Number_Of_Layer_Pot_Explored_By_Roots /*150520 Number_Of_Layers*/; layer++) {
            if (Layer_Root_Conductance_Adjustment[layer] > 0) {
                Layer_Top_Hydraulic_Conductance[layer] = 
                    Top_Hydraulic_Conductance * Layer_Root_Conductance_Adjustment[layer] 
                    / Root_Conductance_Adjustment;
                Layer_Plant_Hydraulic_Conductance[layer] = 
                    Layer_Root_Hydraulic_Conductance[layer] 
                    * Layer_Top_Hydraulic_Conductance[layer]
                    / (Layer_Root_Hydraulic_Conductance[layer] + Layer_Top_Hydraulic_Conductance[layer]);
            }
            else Layer_Plant_Hydraulic_Conductance[layer] = 0;
        }
        Root_Hydraulic_Conductance *= Root_Conductance_Adjustment;
        Plant_Hydraulic_Conductance = (Root_Hydraulic_Conductance * Top_Hydraulic_Conductance) 
                                      / (Root_Hydraulic_Conductance + Top_Hydraulic_Conductance);
        if (Plant_Hydraulic_Conductance > 0) {
            //Calculate average soil water potential (J/kg)
            double Average_Soil_WP(0.0);
            for (int layer = 1; layer <= Max_Number_Of_Layer_Pot_Explored_By_Roots/*150528 Number_Of_Layers*/; layer++) {
                Average_Soil_WP += Soil_Water_Potential[layer] 
                                   * Layer_Root_Conductance_Adjustment[layer]
                                   / Root_Conductance_Adjustment;
            }
            //Calculate leaf water potential
            double Leaf_Water_Potential = 
                Average_Soil_WP - Crop_Potential_Transpiration / Plant_Hydraulic_Conductance;

            if (Leaf_Water_Potential < Leaf_Water_Potential_At_Onset_Of_Stress) {
                Leaf_Water_Potential = 
                        (Plant_Hydraulic_Conductance * Average_Soil_WP 
                         * (Leaf_Water_Potential_At_Onset_Of_Stress - CropParametersRef.Wilting_Leaf_Water_Pot)
                         + Leaf_Water_Potential_At_Wilt * Crop_Potential_Transpiration
                         )
                         / (Plant_Hydraulic_Conductance 
                            * (Leaf_Water_Potential_At_Onset_Of_Stress - Leaf_Water_Potential_At_Wilt) 
                            + Crop_Potential_Transpiration);
            }
            if (Leaf_Water_Potential < Leaf_Water_Potential_At_Wilt) 
                Leaf_Water_Potential = Leaf_Water_Potential_At_Wilt;
            CropStateRef.Leaf_Water_Potential = Leaf_Water_Potential;
                //Reduce transpiration when leaf water potential is less than the critical leaf water
                //potential at the onset of stomatal closure
            double Attainable_Transp(0.0);
            double Transpiration_Ratio(0.0);
            if (Leaf_Water_Potential < Leaf_Water_Potential_At_Onset_Of_Stress) {
                //Attainable transpiration is just a check. It should be equal to actual transpiration in all cases
                Attainable_Transp = Max_Crop_Transpiration 
                                    * (Leaf_Water_Potential - Leaf_Water_Potential_At_Wilt) 
                                    / (Leaf_Water_Potential_At_Onset_Of_Stress - Leaf_Water_Potential_At_Wilt);
                //Transpiration ratio is less than 1 when the atmospheric evaporative demand (potential transpiration),
                //corrected by a nitrogen stress factor, is greater than the maximum ability of the crop to uptake water
                //from a well-watered soil
                Transpiration_Ratio = Max_Crop_Transpiration / Crop_Potential_Transpiration;
            } else {
                Attainable_Transp = Max_Crop_Transpiration;
                Transpiration_Ratio = 1;
            }
            //Calculate crop water uptake (kg/m2/d = mm/d)
            Crop_Water_Uptake = 0.0;  //Initialize crop water uptake = 0
            for (int layer = 1; layer <= Max_Number_Of_Layer_Pot_Explored_By_Roots /*150520 Number_Of_Layers*/; layer++) {
                double Soil_Water_Extracted = Layer_Plant_Hydraulic_Conductance[layer] 
                                              * (Soil_Water_Potential[layer] - Leaf_Water_Potential)
                                              * Transpiration_Ratio;
                //Record layer water uptake
                Soil.pSoilState->Layer_Soil_Water_Uptake[layer] = Soil_Water_Extracted;
                //Update soil water content
                //FMS 140821 just get the total change, not update the soil state. The soil moisture will be updated hourly in next day
                //LML 150310 NEED IMPROVE
                //Soil.pSoilState->change_liquid_water_content_by_volumetric(layer,
                //    - Soil_Water_Extracted / (Soil.pSoilProfile->get_thickness_m(layer) * WaterDensity_kg_m3));
                Soil.pSoilState->Delta_Water_Content[layer] = Soil_Water_Extracted / (Soil.pSoilProfile->get_thickness_m(layer) * WaterDensity_kg_m3);

                Crop_Water_Uptake += Soil_Water_Extracted;
            }
        }//end if
        WSI = std::max<double>(0,1.0 - Crop_Water_Uptake / Max_Crop_Transpiration);
        if (WSI > 1) WSI = 1;
        else if (CORN::is_approximately<double>(WSI,0.0,1.0e-8)) WSI = 0;              //140429
    } else { //Fraction of green area is zero
        WSI = 1;
        Crop_Water_Uptake = 0;
    }
    //std::cout<<" Crop_Water_Uptake:"<<Crop_Water_Uptake<<std::endl;
    //WeatherStateRef.ActualCropTranspiration(Year_Count, DOY) = Crop_Water_Uptake
    CropStateRef.Actual_Crop_Transpiration = Crop_Water_Uptake;
    CropStateRef.Cumulative_Actual_Crop_Transpiration += Crop_Water_Uptake;
    Soil.pSoilState->Cumulative_Actual_Crop_Transpiration_m += Crop_Water_Uptake / 1000.0; //FMS add 11/05/2013
    Soil.pSoilState->Profile_Soil_Water_Uptake = Crop_Water_Uptake;
    //CropStateRef.Yesterday_Water_Stress_Index = CropStateRef.Water_Stress_Index;
    CropStateRef.Water_Stress_Index = WSI;
    //150529 CropStateRef.Yesterday_Water_Stress_Index = CropStateRef.Water_Stress_Index;    //LML 140826
    //CropStateRef.Yesterday_Water_Stress_Factor = CropStateRef.Water_Stress_Factor;
    CropStateRef.Water_Stress_Factor = 1.0 - WSI;
    //150529 CropStateRef.Yesterday_Water_Stress_Factor = CropStateRef.Water_Stress_Factor;  //LML 140826
    CropStateRef.Cumulative_Water_Stress_Index += WSI;
    bool Crop_Flowering = CropStateRef.Flowering;
    bool Crop_In_Yield_Formation = CropStateRef.Crop_Forming_Yield;
    int Days_In_Flowering = CropStateRef.Days_In_Flowering;
    if (Crop_Flowering == true && Crop_In_Yield_Formation == false) {
        if (Days_In_Flowering > 0)
            CropStateRef.Flowering_Water_Stress_Index = 
                (CropStateRef.Flowering_Water_Stress_Index * Days_In_Flowering + WSI) 
                / (Days_In_Flowering + 1);
        else CropStateRef.Flowering_Water_Stress_Index = WSI;
        CropStateRef.Days_In_Flowering += 1;
    }
    //#ifdef CHECK_MASS_BALANCE
    //bal_water.SetFinalPool(Soil.pSoilState->getTotalSoilLiqWaterContent_m());
    //bal_water.SetFluxOut(Crop_Water_Uptake/1000.0);
    //if (!bal_water.IsMassBalance())
    //    bal_water.PrintMassBalanceTerms("PerformWaterUptake");
    //#endif
}
//______________________________________________________________________________
