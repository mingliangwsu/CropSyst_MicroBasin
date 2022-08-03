#include "cropactualnitrogenuptakeclass.h"
#include "math.h"
#include "util/pubtools.h"
#ifdef CHECK_MASS_BALANCE
#include "control/balanceitem.h"
#endif
CropActualNitrogenUptakeClass::CropActualNitrogenUptakeClass(CropStateClass &_CropStateRef)
    :CropStateRef(_CropStateRef)
{
}
//______________________________________________________________________________
double CropActualNitrogenUptakeClass::Quadratic(double a,double b,double c,double d)
{
    double Q = (-b + d * sqrt((b * b) - 4 * a * c)) / (2.0 * a);
    return Q;
}
//______________________________________________________________________________
double CropActualNitrogenUptakeClass::PotentialNitrogenUptakeUdjustmentFactor()
{
    //Thermal_Time_Current = CropStateRef.CumulativeThermalTime(DACE)
    //Thermal_Time_Flowering = CropParametersRef.GetThermalTimeForFlowering
    //Thermal_Time_Maturity = CropParametersRef.GetThermalTimeForPhysiologicalMaturity
    //
    ////This accounts for root senescence after flowering
    //if (Thermal_Time_Current > Thermal_Time_Flowering) {
    //    Root_Senescence_Factor = 1 - (Thermal_Time_Current - Thermal_Time_Flowering) / (Thermal_Time_Maturity - Thermal_Time_Flowering)
    //    Else
    //    Root_Senescence_Factor = 1
    //End If

    //This accounts for enhanced N uptake during early growth (selective root uptake from areas with higher N concentration)
    double Root_Activity_Factor(0.0);
    if (CropStateRef.Potential_Cumulative_Biomass < 0.15)
        Root_Activity_Factor = 
            1.0 + 2.0 * (1.0 - pow((CropStateRef.Potential_Cumulative_Biomass / 0.15),3.0));
    else
        Root_Activity_Factor = 1.0;
    return Root_Activity_Factor; //* Root_Senescence_Factor
}
//______________________________________________________________________________
void CropActualNitrogenUptakeClass::CalculateNLimitationToGrowth(CropInputClass &CropParametersRef)
{
    const int N = 2;  //XXX OJO Move to define constants
    const double Tolerable_Error = 0.0001;
    double Root_Nitrogen_Stress_Factor = 
        CropStateRef.Root_Nitrogen_Stress_Factor;
    double Daily_Crop_N_Crit_Concentration = 
        CropStateRef.Daily_Critical_N_Concentration;
    double Daily_Crop_Min_N_Concentration = 
        CropStateRef.Daily_Minimum_N_Concentration;
    double Water_Limited_Top_Biomass_Growth = 
        CropStateRef.Water_Limited_Biomass_Growth;
    double Water_Limited_Root_Biomass_Growth = 
        CropStateRef.Water_Limited_Root_Biomass_Growth;
    double Actual_Nitrogen_Uptake = CropStateRef.Actual_Nitrogen_Uptake;
    double N_Required_For_Water_Limited_Root_Growth = 
        CropStateRef.N_Required_For_Water_Limited_Root_Growth;
    double Cumulative_Top_Biomass = 
        CropStateRef.Cumulative_Biomass/*150529_Yesterday*/;//(DACE - 1)
    double Cumulative_Root_Biomass = 
        CropStateRef.Cumulative_Root_Biomass_Yesterday;//(DACE - 1)
    double Root_N_Mass = CropStateRef.Root_N_Mass_Yesterday;//(DACE - 1)
    double Root_N_Concentration = CropParametersRef.Root_N_Concentration;
    double Top_N_Mass = CropStateRef.Top_N_Mass;
    double Top_Crop_N_Concentration = 
        (Top_N_Mass) / (Cumulative_Top_Biomass + Water_Limited_Top_Biomass_Growth);

    double Top_Nitrogen_Stress_Factor(1.0);  //1: no stress; 0: full stress
    //double Top_Nitrogen_Stress_Index(0.0); //0: no stress; 1: full stress
    if ((Water_Limited_Top_Biomass_Growth > 0) && 
        (Top_Crop_N_Concentration < Daily_Crop_N_Crit_Concentration)) {
        //double Iterations As Integer
        double Old_Top_Crop_N_Concentration = Top_Crop_N_Concentration;
        double Hi = Daily_Crop_N_Crit_Concentration;
        double Lo = Top_Crop_N_Concentration;
        double Error(1.0);
        do{
            //0: no stress; 1: full stress
            double Top_Nitrogen_Stress_Index = 
                1.0 - (Top_Crop_N_Concentration - Daily_Crop_Min_N_Concentration)
                      / (Daily_Crop_N_Crit_Concentration - Daily_Crop_Min_N_Concentration);
            if (Top_Nitrogen_Stress_Index < 0) Top_Nitrogen_Stress_Index = 0;
            else if (Top_Nitrogen_Stress_Index > 1) Top_Nitrogen_Stress_Index = 1;
            //1: no stress; 0: full stress
            Top_Nitrogen_Stress_Factor = 1 - pow(Top_Nitrogen_Stress_Index,N);
            double Actual_Top_Biomass_Growth = 
                Water_Limited_Top_Biomass_Growth * Top_Nitrogen_Stress_Factor;
            Top_Crop_N_Concentration = 
                (Top_N_Mass) / (Cumulative_Top_Biomass + Actual_Top_Biomass_Growth);
            Error = Top_Crop_N_Concentration - Old_Top_Crop_N_Concentration;
            if (fabs(Error) > Tolerable_Error) {
                if (Error > 0) Hi = Top_Crop_N_Concentration;
                else Lo = Top_Crop_N_Concentration;
                Old_Top_Crop_N_Concentration = Top_Crop_N_Concentration;
                Top_Crop_N_Concentration = (Hi + Lo) / 2.0;
            }
        } while (fabs(Error) >= Tolerable_Error);
    }
    double Actual_Root_Biomass_Growth = Water_Limited_Root_Biomass_Growth * Root_Nitrogen_Stress_Factor;
    double Actual_Top_Biomass_Growth = Water_Limited_Top_Biomass_Growth * Top_Nitrogen_Stress_Factor;
    Root_N_Mass += N_Required_For_Water_Limited_Root_Growth * Root_Nitrogen_Stress_Factor;
    double Top_N_Balance = Top_N_Mass 
                           - (Cumulative_Top_Biomass + Actual_Top_Biomass_Growth) 
                             * Top_Crop_N_Concentration;
    double Root_N_Balance = Root_N_Mass 
                            - (Cumulative_Root_Biomass + Actual_Root_Biomass_Growth) 
                              * Root_N_Concentration;
    double Overall_Crop_N_Balance = Initial_Top_N_Mass 
                                    + Initial_Root_N_Mass 
                                    + Actual_Nitrogen_Uptake
                                    - (Cumulative_Top_Biomass + Actual_Top_Biomass_Growth) 
                                      * Top_Crop_N_Concentration
                                    - (Cumulative_Root_Biomass + Actual_Root_Biomass_Growth) 
                                      * Root_N_Concentration;
    CropStateRef.Top_Crop_N_Concentration = Top_Crop_N_Concentration;
    CropStateRef.Top_Nitrogen_Stress_Factor = Top_Nitrogen_Stress_Factor;
    CropStateRef.Root_Nitrogen_Stress_Factor = Root_Nitrogen_Stress_Factor;
    CropStateRef.Top_Nitrogen_Stress_Index = 1.0 - Top_Nitrogen_Stress_Factor;
    CropStateRef.Root_Nitrogen_Stress_Index = 1.0 - Root_Nitrogen_Stress_Factor;
    CropStateRef.Cumulative_Top_Nitrogen_Stress_Index += (1.0 - Top_Nitrogen_Stress_Factor);
    CropStateRef.Cumulative_Root_Nitrogen_Stress_Index += (1.0 - Root_Nitrogen_Stress_Factor);
    CropStateRef.Root_N_Mass = Root_N_Mass;
    CropStateRef.Root_N_Mass_Yesterday = Root_N_Mass;                            //150529LML
    CropStateRef.Top_Nitrogen_Balance = Top_N_Balance;
    CropStateRef.Root_Nitrogen_Balance = Root_N_Balance;
    CropStateRef.Overall_Crop_Nitrogen_Balance += Overall_Crop_N_Balance;
}
//______________________________________________________________________________
void CropActualNitrogenUptakeClass::ActualNitrogenUptakeAndCropNConcentration(clsSoil &Soil)
{
    double Potential_Nitrogen_Uptake = 
        Soil.pSoilState->Total_Potential_Nitrate_N_Uptake 
        + Soil.pSoilState->Total_Potential_Ammonium_N_Uptake;
    //double Adj;
    //Adj = PotentialNitrogenUptakeUdjustmentFactor(CropState, CropParametersRef, TimeState)
    //
    //Potential_Nitrogen_Uptake = Potential_Nitrogen_Uptake * PotentialNitrogenUptakeUdjustmentFactor(CropState, CropParametersRef, TimeState)
    double Top_N_Mass = CropStateRef.Top_N_Mass;
    //double Root_N_Mass = CropStateRef.Root_N_Mass;
    double Crop_Nitrogen_Demand = CropStateRef.Crop_Nitrogen_Demand;
    double N_Required_For_Water_Limited_Root_Growth = 
        CropStateRef.N_Required_For_Water_Limited_Root_Growth;
    double Actual_Nitrogen_Uptake = 
        std::min<double>(Potential_Nitrogen_Uptake, Crop_Nitrogen_Demand);
    double Available_Nitrogen = Actual_Nitrogen_Uptake + CropStateRef.N_Surplus;
    //Apportion N to roots (first priority) and calculate root N stress factor
    double Root_Nitrogen_Stress_Factor(0.0);
    if (N_Required_For_Water_Limited_Root_Growth > 0) {
        if (Available_Nitrogen > N_Required_For_Water_Limited_Root_Growth) {
            Root_Nitrogen_Stress_Factor = 1;
            Available_Nitrogen -= N_Required_For_Water_Limited_Root_Growth;
        } else {
            Root_Nitrogen_Stress_Factor = Available_Nitrogen / N_Required_For_Water_Limited_Root_Growth;
            Available_Nitrogen = 0;
        }
    } else {
        Root_Nitrogen_Stress_Factor = 1;
    }
    Top_N_Mass += Available_Nitrogen;
    CropStateRef.Actual_Nitrogen_Uptake = Actual_Nitrogen_Uptake;
    Soil.pSoilState->Total_Actual_Nitrogen_Uptake = Actual_Nitrogen_Uptake;
    CropStateRef.Cumulative_Nitrogen_Uptake += Actual_Nitrogen_Uptake;
    Soil.pSoilState->Cumulative_Nitrogen_Uptake += Actual_Nitrogen_Uptake; // FMS 11/05/2013
    CropStateRef.Root_Nitrogen_Stress_Factor = Root_Nitrogen_Stress_Factor;
    CropStateRef.Top_N_Mass = Top_N_Mass;
    CropStateRef.Top_N_Mass_Yesterday = Top_N_Mass;
}
//______________________________________________________________________________
void CropActualNitrogenUptakeClass::CalculateCropNitrogenDemand(CropInputClass &CropParametersRef)
{
    //LML 140924 note: 
    //1. Calculate N demand from soil 
    //2. Provide N surplus from plant N mass which depents on growth N demand
    double Cumulative_Top_Biomass = CropStateRef.Cumulative_Biomass;
    double Water_Limited_Top_Biomass_Growth = CropStateRef.Water_Limited_Biomass_Growth;
    //double Cumulative_Root_Biomass = CropStateRef.Cumulative_Root_Biomass;//(DACE - 1)
    double Water_Limited_Root_Biomass_Growth = CropStateRef.Water_Limited_Root_Biomass_Growth;
    double Root_N_Concentration = CropParametersRef.Root_N_Concentration;
    double Top_Crop_N_Concentration = CropStateRef.Top_Crop_N_Concentration;//(DACE - 1)
    double Daily_Crop_N_Max_Concentration = CropStateRef.Daily_Maximum_N_Concentration;
    double Top_N_Mass = CropStateRef.Top_N_Mass_Yesterday;
    double Root_N_Mass = CropStateRef.Root_N_Mass_Yesterday;                     //150529LML changed to Yesterday
    //Store initial top N mass
    Initial_Top_N_Mass = Top_N_Mass;
    //Store initial root N mass
    Initial_Root_N_Mass = Root_N_Mass;
    //NOTE: Top N Mass for current DACE will be temporary updated in this procedure before new growth for the day
    CropStateRef.Top_N_Mass = Top_N_Mass;
    //Determine if (there is plant N surplus or deficiency
    double N_Surplus(0.0);
    double N_Deficiency(0.0);
    if (Top_Crop_N_Concentration > Daily_Crop_N_Max_Concentration) {
        N_Surplus = Cumulative_Top_Biomass * (Top_Crop_N_Concentration - Daily_Crop_N_Max_Concentration);
        Top_N_Mass -= N_Surplus;
        CropStateRef.Top_N_Mass = Top_N_Mass;
    } else {
        N_Deficiency = Cumulative_Top_Biomass 
                       * (Daily_Crop_N_Max_Concentration - Top_Crop_N_Concentration);    //FMS 141001
    }
    double N_Required_For_Water_Limited_Top_Growth = 
        Water_Limited_Top_Biomass_Growth * Daily_Crop_N_Max_Concentration;
    double N_Required_For_Water_Limited_Root_Growth = 
        Water_Limited_Root_Biomass_Growth * Root_N_Concentration;
    double Crop_Nitrogen_Demand = N_Required_For_Water_Limited_Top_Growth 
                                  + N_Required_For_Water_Limited_Root_Growth
                                  + N_Deficiency 
                                  - N_Surplus;
    if (Crop_Nitrogen_Demand < 0) {
        Top_N_Mass -= Crop_Nitrogen_Demand;
        CropStateRef.Top_N_Mass = Top_N_Mass;
        N_Surplus += Crop_Nitrogen_Demand;      //LML 140924 i.e. N_Surplus = growth_demand+Ndeficiency
        Crop_Nitrogen_Demand = 0;
    }
    CropStateRef.N_Required_For_Attainable_Top_Growth = N_Required_For_Water_Limited_Top_Growth;
    CropStateRef.N_Required_For_Water_Limited_Root_Growth = N_Required_For_Water_Limited_Root_Growth;
    CropStateRef.Crop_Nitrogen_Demand = Crop_Nitrogen_Demand;
    CropStateRef.N_Surplus = N_Surplus;
}
//______________________________________________________________________________
void CropActualNitrogenUptakeClass::CalculateReferencePlantNConcentration(clsSimulation &Simulation,CropInputClass &CropParametersRef)
{
    bool C3_Crop(CropParametersRef.C3_Crop);
    int doy = Simulation.pTimeState->getToday().get_DOY();
    double N_Maximum_Concentration_At_Emergence(0.0);
    double Biomass_To_Start_Dilution_Maximum_N_Concentration(0.0);
    double Biomass_To_Start_Dilution_Critical_N_Concentration(0.0);
    double Biomass_To_Start_Dilution_Minimum_N_Concentration(0.0);
    double Scaling_Factor_Critical_N_Concentration(0.0);
    double Scaling_Factor_Minimum_N_Concentration(0.0);
    double Slope(0.0);
    double N_Maximum_Concentration_At_Maturity(0.0);
    double N_Critical_Concentration_At_Maturity(0.0);
    double N_Minimum_Concentration_At_Maturity(0.0);
    if (C3_Crop) {
        N_Maximum_Concentration_At_Emergence = 
            CropParametersRef.Max_Early_Growth_Plant_N_Conc; //it was 0.07
        Biomass_To_Start_Dilution_Maximum_N_Concentration = 1.5;
        Biomass_To_Start_Dilution_Critical_N_Concentration = 1.5;
        Biomass_To_Start_Dilution_Minimum_N_Concentration = 0.5;
        Scaling_Factor_Critical_N_Concentration = 0.65;
        Scaling_Factor_Minimum_N_Concentration = 0.45;
        Slope = -0.45;
        N_Maximum_Concentration_At_Maturity = 0.0235;
        N_Critical_Concentration_At_Maturity = 0.0152;
        N_Minimum_Concentration_At_Maturity = 0.0065;
    } else {
        N_Maximum_Concentration_At_Emergence = 
            CropParametersRef.Max_Early_Growth_Plant_N_Conc; //it was 0.055
        Biomass_To_Start_Dilution_Maximum_N_Concentration = 1.;
        Biomass_To_Start_Dilution_Critical_N_Concentration = 1.;
        Biomass_To_Start_Dilution_Minimum_N_Concentration = 0.5;
        Scaling_Factor_Critical_N_Concentration = 0.65;
        Scaling_Factor_Minimum_N_Concentration = 0.45;
        Slope = -0.38;
        N_Maximum_Concentration_At_Maturity = 0.018;
        N_Critical_Concentration_At_Maturity = 0.0117;
        N_Minimum_Concentration_At_Maturity = 0.005;
    }
    double N_Critical_Concentration_At_Emergence = 
        N_Maximum_Concentration_At_Emergence * Scaling_Factor_Critical_N_Concentration;
    double N_Minimum_Concentration_At_Emergence = 
        N_Maximum_Concentration_At_Emergence * Scaling_Factor_Minimum_N_Concentration;
    double Amax = N_Maximum_Concentration_At_Emergence 
                  / pow(Biomass_To_Start_Dilution_Maximum_N_Concentration,Slope);
    double Acrit = N_Critical_Concentration_At_Emergence 
                   / pow(Biomass_To_Start_Dilution_Critical_N_Concentration,Slope);
    double Amin = N_Minimum_Concentration_At_Emergence 
                  / pow(Biomass_To_Start_Dilution_Minimum_N_Concentration,Slope);
    double Cumulative_Degree_Days = CropStateRef.Cumulative_Thermal_Time;
    double Flowering_Degree_Days = CropParametersRef.Thermal_Time_for_Flowering;
    double Daily_Crop_N_Max_Concentration(0.0);
    double Daily_Crop_N_Crit_Concentration(0.0);
    double Daily_Crop_Min_N_Concentration(0.0);
    if (Cumulative_Degree_Days <= Flowering_Degree_Days || 
      doy == CropStateRef.DOY_Flowering) {
        double Potential_Cumulative_Top_Biomass = 
            CropStateRef.Potential_Cumulative_Biomass * 10.0;  //Converts kg/m2 to Mg/ha
        double temp = pow(Potential_Cumulative_Top_Biomass,Slope);
        Daily_Crop_N_Max_Concentration = 
            std::min<double>(N_Maximum_Concentration_At_Emergence, Amax * temp);
        Daily_Crop_N_Crit_Concentration = 
            std::min<double>(N_Critical_Concentration_At_Emergence, Acrit * temp);
        Daily_Crop_Min_N_Concentration = 
            std::min<double>(N_Minimum_Concentration_At_Emergence, Amin * temp);
        if (doy == CropStateRef.DOY_Flowering) {
            CropStateRef.Maximum_N_Concentration_At_Flowering = Daily_Crop_N_Max_Concentration;
            CropStateRef.Critical_N_Concentration_At_Flowering = Daily_Crop_N_Crit_Concentration;
            CropStateRef.Minimum_N_Concentration_At_Flowering = Daily_Crop_Min_N_Concentration;
        }
    } else {
        double N_Maximum_Concentration_At_Flowering = 
            CropStateRef.Maximum_N_Concentration_At_Flowering;
        double N_Critical_Concentration_At_Flowering = 
            CropStateRef.Critical_N_Concentration_At_Flowering;
        double N_Minimum_Concentration_At_Flowering = 
            CropStateRef.Minimum_N_Concentration_At_Flowering;
        double Maturity_Degree_Days = CropParametersRef.Thermal_Time_for_Maturity;
        double Degree_Days_Between_Flowering_And_Maturity = 
            Maturity_Degree_Days - Flowering_Degree_Days;
        double Degree_Days_Between_Flowering_And_Now = 
            Cumulative_Degree_Days - Flowering_Degree_Days;
        Daily_Crop_N_Max_Concentration = N_Maximum_Concentration_At_Flowering 
                                         - Degree_Days_Between_Flowering_And_Now 
                                           * (N_Maximum_Concentration_At_Flowering - N_Maximum_Concentration_At_Maturity)
                                           / Degree_Days_Between_Flowering_And_Maturity;
        Daily_Crop_N_Crit_Concentration = N_Critical_Concentration_At_Flowering 
                                         - Degree_Days_Between_Flowering_And_Now 
                                           * (N_Critical_Concentration_At_Flowering - N_Critical_Concentration_At_Maturity) 
                                           / Degree_Days_Between_Flowering_And_Maturity;
        Daily_Crop_Min_N_Concentration = N_Minimum_Concentration_At_Flowering 
                                         - Degree_Days_Between_Flowering_And_Now 
                                           * (N_Minimum_Concentration_At_Flowering - N_Minimum_Concentration_At_Maturity) 
                                           / Degree_Days_Between_Flowering_And_Maturity;
    }
    CropStateRef.Daily_Maximum_N_Concentration = Daily_Crop_N_Max_Concentration;
    CropStateRef.Daily_Critical_N_Concentration = Daily_Crop_N_Crit_Concentration;
    CropStateRef.Daily_Minimum_N_Concentration = Daily_Crop_Min_N_Concentration;
}

//______________________________________________________________________________
void CropActualNitrogenUptakeClass::PlantNProcesses(clsSimulation &Simulation,clsSoil &Soil,CropInputClass &CropParametersRef)
{
    #ifdef CHECK_MASS_BALANCE
    BalanceItem bal_planN;
    bal_planN.SetInitPool(CropStateRef.Top_N_Mass + CropStateRef.Root_N_Mass);
    #endif
    CalculateReferencePlantNConcentration(Simulation,CropParametersRef);
    CalculateCropNitrogenDemand(CropParametersRef);
    ActualNitrogenUptakeAndCropNConcentration(Soil);
    CalculateNLimitationToGrowth(CropParametersRef);
    #ifdef CHECK_MASS_BALANCE
    bal_planN.SetFinalPool(CropStateRef.Top_N_Mass + CropStateRef.Root_N_Mass);
    bal_planN.SetFluxIn(CropStateRef.Actual_Nitrogen_Uptake);
    if (!bal_planN.IsMassBalance())
        bal_planN.PrintMassBalanceTerms("PlantNProcess");
    #endif
}
