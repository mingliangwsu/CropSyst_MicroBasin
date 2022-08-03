#include "cropcanopygrowthclass.h"
#include "math.h"
//______________________________________________________________________________
CropCanopyGrowthClass::CropCanopyGrowthClass(CropStateClass& _CropStateRef)
:CropStateRef(_CropStateRef)
,First(false)
{
}
//______________________________________________________________________________
void CropCanopyGrowthClass::DetermineUnstressedCover(clsSimulation &Simulation/*150601,CropInputClass &CropParametersRef*/)
{
    double Unstressed_Canopy_Cover(0.0);
    if (CropStateRef.Mature) {
            if (/*150601 CropParametersRef.*/pCropParameters->Tree_Fruit_Crop) {
                if (CropStateRef.First_Day_Of_Maturity) {
                    //Reduce canopy 80% at the time of tree fruit maturity
                    CropStateRef.Potential_Fraction_Solar_Rad_Intercepted *= 0.2;
                }
            } else {
                CropStateRef.Potential_Fraction_Solar_Rad_Intercepted += Canopy_Senescence_Rate;        //M.Liu minus??
                if (CropStateRef.Potential_Fraction_Solar_Rad_Intercepted < 0) CropStateRef.Potential_Fraction_Solar_Rad_Intercepted = 0;
            }
    } else {
        double Cumulative_Thermal_Time = CropStateRef.Cumulative_Thermal_Time;
        Unstressed_Canopy_Cover = 
            CalculateCover(Cumulative_Thermal_Time, Simulation/*150601 ,CropParametersRef*/);
        CropStateRef.Yesterday_Potential_Fraction_Solar_Rad_Intercepted = 
            CropStateRef.Potential_Fraction_Solar_Rad_Intercepted;    
        CropStateRef.Potential_Fraction_Solar_Rad_Intercepted = Unstressed_Canopy_Cover;
        //CropStateRef.Yesterday_Potential_Fraction_Solar_Rad_Intercepted = CropStateRef.Potential_Fraction_Solar_Rad_Intercepted;    //LML 140826 moved here
        //Allow for continuation of canopy senescence between maturity and harvest or dormancy
        double old_Potential_Fraction_Solar_Rad_Intercepted = 
            CropStateRef.Potential_Fraction_Solar_Rad_Intercepted;
        if (Cumulative_Thermal_Time > /*150601 CropParametersRef.*/pCropParameters->Thermal_Time_At_The_Beginning_Of_Canopy_Senescence)
            Canopy_Senescence_Rate = CropStateRef.Potential_Fraction_Solar_Rad_Intercepted 
                                     - old_Potential_Fraction_Solar_Rad_Intercepted;  //M.Liu need check
   }
    //PAR canopy interception assume that PAR extinction coefficient is 1.4 times greater than solar extinction coefficient
    CropStateRef.Potential_Fraction_PAR_Intercepted = 1.0 - exp(1.4 * log(1.0 - Unstressed_Canopy_Cover));
}
//______________________________________________________________________________
void CropCanopyGrowthClass::DetermineActualCover(/*150601 CropInputClass &CropParametersRef*/)
{
    CropInputClass &CropParametersRef = *pCropParameters;                        //150601
    double Today_Potential_Canopy_Expansion(0.0);
    double Today_Actual_Canopy_Expansion(0.0);
    double Today_Leaf_Water_Potential(0.0);
    double Current_Thermal_Time = CropStateRef.Cumulative_Thermal_Time;
    double Thermal_Time_Beginning_Canopy_Senescence = CropParametersRef.Thermal_Time_At_The_Beginning_Of_Canopy_Senescence;
    //Determine green canopy cover
    if (CropStateRef.Mature) {
        if (CropParametersRef.Tree_Fruit_Crop) {
            if (CropStateRef.First_Day_Of_Maturity) {
                //Reduce canopy 80% at the time of tree fruit maturity
                Today_Actual_Canopy_Expansion = -CropStateRef.Yesterday_Fraction_Solar_Rad_Intercepted_Green_Canopy * 0.8;
                CropStateRef.First_Day_Of_Maturity = false;
            }
            else Today_Actual_Canopy_Expansion = 0;
         }
         else Today_Actual_Canopy_Expansion = Yesterday_Potential_Canopy_Expansion;
    } else {
        Today_Potential_Canopy_Expansion = CropStateRef.Potential_Fraction_Solar_Rad_Intercepted
                                           - CropStateRef.Yesterday_Potential_Fraction_Solar_Rad_Intercepted;
        Today_Leaf_Water_Potential = CropStateRef.Leaf_Water_Potential;
        if (Current_Thermal_Time > Thermal_Time_Beginning_Canopy_Senescence) {
            // Then ' negative canopy expansion - senescence
            Yesterday_Potential_Canopy_Expansion = Today_Potential_Canopy_Expansion;
            Today_Actual_Canopy_Expansion = Today_Potential_Canopy_Expansion;
        } else {
            double Leaf_Water_Potential_That_Reduces_Canopy_Expansion = 
                CropParametersRef.Critical_Leaf_Water_Potential_For_Canopy_Expansion;
            double Leaf_Water_Potential_That_Stops_Canopy_Expansion = 
                CropParametersRef.Minimum_Leaf_Water_Potential_For_Canopy_Expansion;
            if (Today_Potential_Canopy_Expansion > 0) {
                if (Today_Leaf_Water_Potential >= Leaf_Water_Potential_That_Reduces_Canopy_Expansion) {
                    Today_Actual_Canopy_Expansion = Today_Potential_Canopy_Expansion;
                } else {
                    if (Today_Leaf_Water_Potential > Leaf_Water_Potential_That_Stops_Canopy_Expansion)
                        Today_Actual_Canopy_Expansion = 
                            Today_Potential_Canopy_Expansion 
                            * (Today_Leaf_Water_Potential - Leaf_Water_Potential_That_Stops_Canopy_Expansion)
                            / (Leaf_Water_Potential_That_Reduces_Canopy_Expansion 
                               - Leaf_Water_Potential_That_Stops_Canopy_Expansion);
                    else
                        Today_Actual_Canopy_Expansion = 0;
                }
            } else {
                Today_Actual_Canopy_Expansion = Today_Potential_Canopy_Expansion 
                                                * (1.0 + CropStateRef.Yesterday_Water_Stress_Index);   //M.Liu revised
            }
       }
   }
    double Actual_Canopy_Cover = CropStateRef.Yesterday_Fraction_Solar_Rad_Intercepted_Green_Canopy
                                 + Today_Actual_Canopy_Expansion;
    /*
    std::cout<<" Fraction_Solar_Rad_Intercepted_Green_Canopy:"<<CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy
            <<" Today_Actual_Canopy_Expansion:"<<Today_Actual_Canopy_Expansion
            <<" Today_Potential_Canopy_Expansion:"<<Today_Potential_Canopy_Expansion
            <<" water_stress:"<<CropStateRef.Water_Stress_Index
            <<std::endl;
    */
    if (Actual_Canopy_Cover < 0) Actual_Canopy_Cover = 0;
    //else if (Actual_Canopy_Cover > 1.0) Actual_Canopy_Cover = 1.0;
    CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy = Actual_Canopy_Cover;
    CropStateRef.Fraction_Solar_Rad_Intercepted_Total_Canopy = Actual_Canopy_Cover;
    CropStateRef.Yesterday_Fraction_Solar_Rad_Intercepted_Green_Canopy = 
        CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy;  //LML 140826 recording today's status
    //PAR canopy interception assume that PAR extinction coefficient is 1.4 times greater than solar extinction coefficient
    CropStateRef.Fraction_PAR_Intercepted = 1 - exp(1.4 * log(1 - Actual_Canopy_Cover));
    //Determine total canopy cover
    if (Current_Thermal_Time > Thermal_Time_Beginning_Canopy_Senescence) {
        if (!First) {
            double Maximum_Canopy_Cover = CropParametersRef.Maximum_Canopy_Cover;
            double Canopy_Cover_At_Maturity = CropParametersRef.Total_Canopy_Cover_At_Maturity;
            double Actual_Total_Canopy_Cover_At_Maturity = 
                Actual_Canopy_Cover * Canopy_Cover_At_Maturity / Maximum_Canopy_Cover;
            Maximum_Canopy_Cover_Reached = Actual_Canopy_Cover;
            Total_Canopy_Cover_To_Lose = 
                Maximum_Canopy_Cover_Reached - Actual_Total_Canopy_Cover_At_Maturity;
            First = true;
            CropStateRef.Fraction_Solar_Rad_Intercepted_Total_Canopy = Actual_Canopy_Cover;
        } else {
            double Current_Total_Canopy_Cover;
            double Thermal_Time_At_Maturity;
            Thermal_Time_At_Maturity = CropParametersRef.Thermal_Time_for_Maturity;
            Current_Total_Canopy_Cover = 
                Maximum_Canopy_Cover_Reached 
                - Total_Canopy_Cover_To_Lose
                  * (Current_Thermal_Time - Thermal_Time_Beginning_Canopy_Senescence) 
                  / (Thermal_Time_At_Maturity - Thermal_Time_Beginning_Canopy_Senescence);
            if (Current_Total_Canopy_Cover > Actual_Canopy_Cover)
                CropStateRef.Fraction_Solar_Rad_Intercepted_Total_Canopy = Current_Total_Canopy_Cover;
            else
                CropStateRef.Fraction_Solar_Rad_Intercepted_Total_Canopy = Actual_Canopy_Cover;
        }
    } else {
        CropStateRef.Fraction_Solar_Rad_Intercepted_Total_Canopy = Actual_Canopy_Cover;
    }
    //std::cout<<" Actual_Canopy_Cover:"<<Actual_Canopy_Cover<<"FSRITP:"<<CropStateRef.Fraction_Solar_Rad_Intercepted_Total_Canopy<<std::endl;
}
//______________________________________________________________________________
double CropCanopyGrowthClass::CalculateCover(double Cumulative_Thermal_Time, clsSimulation &Simulation/*150601 ,CropInputClass &CropParametersRef*/)
{
    double Calculate_Cover(0.0);
    CropInputClass &CropParametersRef = *pCropParameters;                        //150601
    if (Simulation.pSimulationRotation->getCropSeasonStarted()) {
        double Canopy_Cover_At_Maturity = 
            CropParametersRef.Green_Canopy_Cover_At_Maturity;
        double Thermal_Time_To_End_Canopy_Growth = 
            CropParametersRef.Thermal_Time_At_The_End_Of_Canopy_Growth;
        double Thermal_Time_Beginning_Senescence = 
            CropParametersRef.Thermal_Time_At_The_Beginning_Of_Canopy_Senescence;
        double Thermal_Time_Maturity = CropParametersRef.Thermal_Time_for_Maturity;
        double Asym_CC = CropParametersRef.Asym_CC;
        double b_Coefficient = CropParametersRef.b_Coefficient;
        double Shape_Factor = CropParametersRef.Shape_Factor;
        double Senescence_Asym_CC = CropParametersRef.Senescence_Asym_CC;
        double C_low = CropParametersRef.C_low;
        double Actual_CC_Max = CropParametersRef.Actual_CC_Max;
        double Thermal_Time_To_Start_Growing_Season(0.0);
        if (CropParametersRef.Perennial_Crop) Thermal_Time_To_Start_Growing_Season = 0;
        else
            Thermal_Time_To_Start_Growing_Season = CropParametersRef.Thermal_Time_for_Emergence;
        double Relative_Thermal_Time(0.0);
        if (Cumulative_Thermal_Time >= Thermal_Time_To_Start_Growing_Season && 
          Cumulative_Thermal_Time <= Thermal_Time_To_End_Canopy_Growth) {
            Relative_Thermal_Time = 
                (Cumulative_Thermal_Time - Thermal_Time_To_Start_Growing_Season) 
                / (Thermal_Time_To_End_Canopy_Growth - Thermal_Time_To_Start_Growing_Season);
            Calculate_Cover = Asym_CC / (1.0 + b_Coefficient * exp(-Shape_Factor * Relative_Thermal_Time));
        } else {
            if (Cumulative_Thermal_Time <= Thermal_Time_Maturity && 
              Cumulative_Thermal_Time > Thermal_Time_Beginning_Senescence) {
                Relative_Thermal_Time = 
                    (Cumulative_Thermal_Time - Thermal_Time_Beginning_Senescence) 
                    / (Thermal_Time_Maturity - Thermal_Time_Beginning_Senescence);
                Calculate_Cover = Senescence_Asym_CC 
                                  - (Senescence_Asym_CC - C_low) 
                                    / (1.0 + b_Coefficient * exp(-Shape_Factor * Relative_Thermal_Time));
                if (Calculate_Cover < Canopy_Cover_At_Maturity) 
                    Calculate_Cover = Canopy_Cover_At_Maturity;
            } else {
                Calculate_Cover = Actual_CC_Max;
            }
        }
    } else {
        Calculate_Cover = 0.0;
    }
    return Calculate_Cover;
}
//______________________________________________________________________________
double CropCanopyGrowthClass::calc_leaf_green_area_index(std::string GAI_or_LAI)
{
    double fract_intercept(0.0);
    if (GAI_or_LAI.compare("GAI") == 0)
        fract_intercept = CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy;
    else
        fract_intercept = CropStateRef.Fraction_Solar_Rad_Intercepted_Total_Canopy;
    //FMS Apr 8, 2015 double Kc = CropStateRef.Current_ET_Crop_Coeff;
    double Kl = pCropParameters->Extinction_Coefficient_Crop_Of_Radiacion_Solar; //FMS Apr 8, 2015
    double out = -log(1 - fract_intercept) / Kl/*150601 Kc*/;
    if (out <= 0.01) out = 0.01;
    return out;
}

